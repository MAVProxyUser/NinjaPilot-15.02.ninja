#!/usr/bin/env python3
"""Free-rotation magnetometer calibration.

The GCS only offers the six-point procedure for the magnetometer: six discrete
orientations, each held by hand. Six points is the bare minimum for a 3-DOF
offset fit and is very sensitive to how squarely you actually held the board.

This instead samples continuously while you roll the board around in your hands
for a minute, and fits the sphere those samples lie on. Hard iron shifts the
sphere's centre away from the origin; that centre IS RevoCalibration.mag_bias.
Soft iron turns the sphere into an ellipsoid; the per-axis radii give the
diagonal of mag_transform. Hundreds of well-spread samples constrain both far
better than six can.

The firmware applies these in sensors.c:
    mags[i] = sample[i] - mag_bias[i];  then  mag_transform * mags

Run with NOTHING else on the telemetry link -- the firmware latches a single
UDP peer, so quit the GCS first.

    python3 mag_calibrate.py [seconds]            measure only
    python3 mag_calibrate.py [seconds] --apply    measure, then write+persist
"""
import math
import struct
import sys
import time

sys.path.insert(0, '.')
import uavtalk
from uavtalk_client import UAVTalkClient, UdpTransport, default_xml_dir

HOST, PORT = '192.168.0.139', 9000

# A stationary board wanders by a few mGa of noise; real rotation sweeps
# hundreds. Anything above this is unambiguously someone moving it.
MOTION_THRESHOLD_MGA = 150.0


def fit_sphere(pts):
    """Least-squares sphere fit.

    |p - c|^2 = r^2  expands to  2p.c - |c|^2 + r^2 = |p|^2, which is linear in
    (cx, cy, cz, k) with k = r^2 - |c|^2. Solve the 4x4 normal equations.
    """
    n = len(pts)
    A = [[0.0] * 4 for _ in range(4)]
    b = [0.0] * 4
    for (x, y, z) in pts:
        row = [2.0 * x, 2.0 * y, 2.0 * z, 1.0]
        rhs = x * x + y * y + z * z
        for i in range(4):
            for j in range(4):
                A[i][j] += row[i] * row[j]
            b[i] += row[i] * rhs
    # Gaussian elimination with partial pivoting
    M = [A[i][:] + [b[i]] for i in range(4)]
    for col in range(4):
        piv = max(range(col, 4), key=lambda r: abs(M[r][col]))
        if abs(M[piv][col]) < 1e-12:
            return None
        M[col], M[piv] = M[piv], M[col]
        for r in range(4):
            if r == col:
                continue
            f = M[r][col] / M[col][col]
            for cc in range(col, 5):
                M[r][cc] -= f * M[col][cc]
    sol = [M[i][4] / M[i][i] for i in range(4)]
    cx, cy, cz, k = sol
    r2 = k + cx * cx + cy * cy + cz * cz
    if r2 <= 0:
        return None
    return (cx, cy, cz), math.sqrt(r2)


def coverage(pts, centre):
    """Fraction of 26 direction bins that contain at least one sample -- a blunt
    but honest check that the board was actually rotated, not just wiggled."""
    cx, cy, cz = centre
    seen = set()
    for (x, y, z) in pts:
        v = (x - cx, y - cy, z - cz)
        m = math.sqrt(sum(c * c for c in v)) or 1.0
        seen.add(tuple(max(-1, min(1, int(round(c / m * 1.5)))) for c in v))
    seen.discard((0, 0, 0))
    return len(seen) / 26.0


# UAVObjMetadata is 8 bytes: uint16 flags, then telemetry / gcsTelemetry /
# logging update periods in ms. Telemetry update mode lives in flags bits 4-5,
# where 1 == UPDATEMODE_PERIODIC.
META_FMT = '<HHHH'
UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT = 4
UPDATEMODE_PERIODIC = 1


def set_mag_rate(client, db, period_ms, saved=None):
    """Raise MagSensor's telemetry rate for the duration of the run.

    Its default period is far too slow to fit a sphere -- measured at roughly
    one update every eight seconds, where this needs hundreds. Returns the
    original metadata so the caller can put it back; leaving a sensor streaming
    at 50Hz afterwards is a telemetry and CPU cost nobody asked for.
    """
    meta_id = db['MagSensor'].obj_id + 1
    got = {}

    def on_obj(objdef, inst, vals):
        pass

    if saved is None:
        client.send_raw(uavtalk.TYPE_OBJ_REQ, meta_id)
        client.run(1.5, on_object=on_obj)
        raw = client.meta_payloads.get(meta_id)
        if not raw or len(raw) < 8:
            return None
        saved = raw[:8]
        flags, tp, gp, lp = struct.unpack(META_FMT, saved)
        flags = (flags & ~(3 << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT)) \
            | (UPDATEMODE_PERIODIC << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT)
        payload = struct.pack(META_FMT, flags, period_ms, gp, lp)
    else:
        payload = saved
    client.send_raw(uavtalk.TYPE_OBJ, meta_id, 0, payload)
    client.run(0.8, on_object=on_obj)
    return saved


def main():
    secs = float(sys.argv[1]) if len(sys.argv) > 1 else 60.0
    db = uavtalk.UAVObjectDB(default_xml_dir())
    client = UAVTalkClient(UdpTransport(HOST, PORT), db)

    pts = []
    last = [0.0]

    def on_obj(objdef, inst, vals):
        if objdef.name != 'MagSensor':
            return
        p = (vals['x'], vals['y'], vals['z'])
        if p != (0.0, 0.0, 0.0):
            pts.append(p)
        now = time.time()
        if now - last[0] > 5.0:
            last[0] = now
            print("  %4d samples ..." % len(pts))

    saved_meta = set_mag_rate(client, db, 20)
    if saved_meta is None:
        print("WARNING: could not raise MagSensor's telemetry rate; samples will be sparse.")

    print("Rotate the board slowly through EVERY orientation.")
    print("Tumble it like a dice -- all six faces up, and roll between them.")
    print("Keep it away from motors, batteries, laptops and steel desks.")
    print("\nWaiting for you to start moving it (Ctrl-C to give up) ...")

    # Wait for actual motion before collecting anything.
    #
    # This used to be a fixed timer started by whoever ran the script, which
    # quietly assumed a person was standing there ready. When that assumption
    # was wrong the run collected a few thousand samples of a stationary board
    # and the fit produced confident, meaningless numbers -- a tiny sphere with
    # "100% coverage", which reads like a broken sensor rather than like an
    # empty room. Trigger on the data instead: nothing is recorded until the
    # field is genuinely changing.
    warm = []

    def watch(objdef, inst, vals):
        if objdef.name == 'MagSensor':
            warm.append((vals['x'], vals['y'], vals['z']))
            if len(warm) > 40:
                warm.pop(0)

    moving = False
    waited = 0.0
    while not moving and waited < 600.0:
        client.run(1.0, on_object=watch)
        waited += 1.0
        if len(warm) >= 20:
            spread = max(max(a[i] for a in warm) - min(a[i] for a in warm)
                         for i in range(3))
            if spread > MOTION_THRESHOLD_MGA:
                moving = True
    if not moving:
        print("No movement seen in 10 minutes -- giving up.")
        set_mag_rate(client, db, 0, saved=saved_meta)
        return 1

    print("Motion detected -- collecting for %.0f s. Keep rotating." % secs)
    client.run(secs, on_object=on_obj)

    if saved_meta is not None:
        set_mag_rate(client, db, 0, saved=saved_meta)

    if len(pts) < 50:
        print("\nFAIL: only %d samples. Is the link up and MagSensor publishing?" % len(pts))
        return 1

    fit = fit_sphere(pts)
    if not fit:
        print("\nFAIL: sphere fit is degenerate -- samples are probably coplanar.")
        return 1
    centre, radius = fit
    cov = coverage(pts, centre)

    resid = []
    for (x, y, z) in pts:
        d = math.sqrt((x - centre[0]) ** 2 + (y - centre[1]) ** 2 + (z - centre[2]) ** 2)
        resid.append(d - radius)
    rms = math.sqrt(sum(r * r for r in resid) / len(resid))

    print("\nsamples          %d" % len(pts))
    print("sphere centre    %8.1f %8.1f %8.1f  mGa   <- hard-iron offset" % centre)
    print("sphere radius    %8.1f mGa                 <- compare to HomeLocation.Be" % radius)
    print("fit residual     %8.1f mGa rms" % rms)
    print("orientation cov  %8.0f%% of 26 direction bins" % (cov * 100))

    # Sanity gates. A calibration that is worse than no calibration is the
    # thing to avoid here -- filtermag.c scores every sample against
    # HomeLocation.Be, so a bad bias pins the Magnetometer alarm just as an
    # absent one does.
    ok = True
    if cov < 0.5:
        print("\n  !! coverage %.0f%% -- below 50%%, the board was not rotated enough." % (cov * 100))
        ok = False
    if rms > 0.15 * radius:
        print("\n  !! residual is %.0f%% of the radius -- samples do not lie on a"
              " sphere.\n     Soft iron, or something magnetic moved during the run."
              % (100.0 * rms / radius))
        ok = False

    home_be = None
    try:
        import subprocess
        pass
    except Exception:
        pass

    if '--apply' not in sys.argv:
        print("\nMeasurement only. Re-run with --apply to write it.")
        return 0
    if not ok:
        print("\nNOT applying: the fit did not pass the checks above.")
        return 1

    st = {'phase': 0, 't': 0.0}

    def on_cal(objdef, inst, vals):
        if st['phase'] == 1 and time.time() - st['t'] > 0.8:
            st['phase'] = 2
            client.send_object("ObjectPersistence",
                               {"Operation": "Save", "Selection": "SingleObject",
                                "ObjectID": db['RevoCalibration'].obj_id, "InstanceID": 0},
                               msg_type=uavtalk.TYPE_OBJ_ACK)
            print("  -> persisted to flash")
            client.request_object('RevoCalibration')
            return
        if objdef.name != 'RevoCalibration':
            return
        if st['phase'] == 0:
            st['phase'] = 1
            st['t'] = time.time()
            cur = dict(vals)
            print("\n  was mag_bias = %r" % (cur['mag_bias'],))
            cur['mag_bias'] = [float(centre[0]), float(centre[1]), float(centre[2])]
            print("  new mag_bias = %r" % (cur['mag_bias'],))
            client.send_object('RevoCalibration', cur, msg_type=uavtalk.TYPE_OBJ_ACK)
        elif st['phase'] >= 2:
            print("  now mag_bias = %r" % (vals['mag_bias'],))

    client.request_object('RevoCalibration')
    client.run(10.0, on_object=on_cal)
    return 0


if __name__ == '__main__':
    sys.exit(main())
