#!/usr/bin/env python3
"""
Accelerometer calibration over UAVTalk -- USB serial or WiFi UDP.

Two modes:

  --flip   Two poses, level and inverted. Answers one question: is the error a
           zero-g OFFSET or a GAIN error? A board sitting still in ONE
           orientation cannot tell you, because both are perfectly steady, so
           "the reading is stable" proves nothing. Flipping separates them,
           since a bias keeps its sign while gravity changes its own:

               upright   z = -g*s + b        b = (z_up + z_dn) / 2
               inverted  z = +g*s + b        s = (z_dn - z_up) / (2g)

  --six    The full six-point calibration, the same one the GCS wizard runs.
           Solves for per-axis scale and bias against a constant field
           magnitude. This is the port of CalibrationUtils::
           SixPointInConstFieldCal() from calibrationutils.cpp; the comments
           there explain the difference-in-magnitude formulation.

Poses are recognised from the accelerometer itself, not from AttitudeState, so
they are yaw-invariant -- which matters because a board with no magnetometer
has a free-running yaw and would never match a yaw-bearing pose. Put the board
in the pose it asks for and it starts sampling on its own.

Results are printed. They are only written to the board with --apply, and only
persisted to flash with --save. Nothing here ever arms anything.

  accel_calibrate.py --serial /dev/cu.wchusbserial8320 --six
  accel_calibrate.py --udp 192.168.4.1:9000 --flip
  accel_calibrate.py --serial /dev/cu.wchusbserial8320 --six --apply --save
"""
import argparse
import os
import sys
import time

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import uavtalk               # noqa: E402
import uavtalk_client        # noqa: E402

GRAV = 9.80665

# Poses, identified from the ACCELEROMETER rather than from AttitudeState.
#
# The GCS wizard keys its poses off attitude, including yaw, because the same
# pass also calibrates the magnetometer. That does not transfer here: a board
# with no magnetometer has a free-running yaw (this one sat at -48 deg on the
# bench), so a yaw-bearing pose would never match. It is also unnecessary --
# gravity is yaw-invariant, so all that matters for an accel calibration is
# which body axis is pointing down.
#
# Body frame is X forward, Y right, Z down, and an accelerometer at rest reads
# specific force, i.e. MINUS the gravity vector. So a level board reads
# (0, 0, -g), which is exactly what the bench shows.
#
#   name              axis  sign   instruction
POSES = [
    ("level",           2,   -1,   "Level, right way up"),
    ("nose_down",       0,   -1,   "Nose down, standing on its front"),
    ("right_side_down", 1,   -1,   "Right side down"),
    ("inverted",        2,   +1,   "Upside down"),
    ("nose_up",         0,   +1,   "Nose up, standing on its tail"),
    ("left_side_down",  1,   +1,   "Left side down"),
]
POSE_BY_NAME = {p[0]: p for p in POSES}

SIX = [p[0] for p in POSES]
FLIP = ["level", "inverted"]

# An axis counts as "down" only when it holds most of gravity and the other two
# hold little of it -- otherwise a board resting at 45 degrees would be accepted.
ALIGNED = 0.85 * GRAV
OFF_AXIS = 0.35 * GRAV


def classify(vec):
    """Return the pose name a measured accel vector corresponds to, or None."""
    dominant = max(range(3), key=lambda i: abs(vec[i]))
    if abs(vec[dominant]) < ALIGNED:
        return None
    if any(abs(vec[i]) > OFF_AXIS for i in range(3) if i != dominant):
        return None
    sign = 1 if vec[dominant] > 0 else -1
    for name, axis, want_sign, _desc in POSES:
        if axis == dominant and want_sign == sign:
            return name
    return None


def six_point_in_const_field_cal(const_mag, x, y, z):
    """Port of CalibrationUtils::SixPointInConstFieldCal().

    Writes five difference-in-magnitude equations between consecutive poses,
    which cancels the unknown field magnitude, then recovers Sx from a single
    magnitude equation. Returns (scale[3], bias[3]).
    """
    A = np.zeros((5, 5))
    f = np.zeros(5)
    for i in range(5):
        A[i][0] = 2.0 * (x[i + 1] - x[i])
        A[i][1] = y[i + 1] ** 2 - y[i] ** 2
        A[i][2] = 2.0 * (y[i + 1] - y[i])
        A[i][3] = z[i + 1] ** 2 - z[i] ** 2
        A[i][4] = 2.0 * (z[i + 1] - z[i])
        f[i] = x[i] ** 2 - x[i + 1] ** 2

    c = np.linalg.solve(A, f)      # c0=bx/Sx, c1=Sy^2/Sx^2, c2=Sy*by/Sx^2, ...

    xp, yp, zp = x[0], y[0], z[0]
    denom = (xp * xp + 2 * c[0] * xp + c[0] * c[0]
             + c[1] * yp * yp + 2 * c[2] * yp + c[2] * c[2] / c[1]
             + c[3] * zp * zp + 2 * c[4] * zp + c[4] * c[4] / c[3])
    Sx = np.sqrt(const_mag * const_mag / denom)

    S = np.zeros(3)
    b = np.zeros(3)
    S[0] = Sx
    b[0] = Sx * c[0]
    S[1] = np.sqrt(c[1] * Sx * Sx)
    b[1] = c[2] * Sx * Sx / S[1]
    S[2] = np.sqrt(c[3] * Sx * Sx)
    b[2] = c[4] * Sx * Sx / S[2]

    # SIGN CONVENTION -- the one trap in this function.
    #
    # The solver's own model is  corrected = S*raw + b. That is what the
    # magnitude equation above expands to, since
    #     Sx^2 * (x^2 + 2*c0*x + c0^2) == (Sx*x + Sx*c0)^2 == (Sx*x + b0)^2
    #
    # The firmware applies the OPPOSITE sign. attitude.c does
    #     accels[i] *= accel_scale[i]
    #     accelState[i] = accels[i] - accel_bias[i]
    # so what it wants stored is accel_bias = -b.
    #
    # Return firmware convention, so callers can write these straight into
    # AccelGyroSettings without having to remember this.
    return S, -b


class Session(object):
    """Runs the client loop while letting the caller drive pose by pose."""

    def __init__(self, client):
        self.client = client
        self.accel = None
        self.updates = 0

    def _on_object(self, objdef, _inst, values):
        if objdef.name == "AccelState":
            self.accel = (values["x"], values["y"], values["z"])
            self.updates += 1

    def pump(self, seconds):
        # Always pass on_object: without it the client prints every decoded
        # object, which buries the prompts.
        self.client.run(duration=seconds, on_object=self._on_object)

    def gather(self, pose, want, settle=1.5):
        """Wait for `pose`, let it settle, then average `want` AccelState samples."""
        _name, _axis, _sign, desc = POSE_BY_NAME[pose]
        print("\n  Pose: %s" % desc)
        print("    waiting...", end="", flush=True)

        held_since = None
        deadline = time.time() + 180.0
        while time.time() < deadline:
            self.pump(0.2)
            if self.accel is not None and classify(self.accel) == pose:
                if held_since is None:
                    held_since = time.time()
                    print(" detected, hold still...", end="", flush=True)
                elif time.time() - held_since >= settle:
                    break
            else:
                held_since = None
        else:
            print("\n    timed out waiting for this pose.")
            return None
        print()

        samples = []
        while len(samples) < want:
            seen = self.updates
            self.pump(0.05)
            if self.updates == seen or self.accel is None:
                continue
            if classify(self.accel) != pose:
                print("\n    board moved -- re-place it.")
                return self.gather(pose, want, settle)
            samples.append(self.accel)
            if len(samples) % 10 == 0 or len(samples) == want:
                print("\r    %d/%d samples" % (len(samples), want), end="", flush=True)
        print()
        return np.array(samples).mean(axis=0)


def set_stream_rate(client, obj_name, period_ms):
    """Switch an object to PERIODIC at period_ms. Returns the previous metadata.

    Metadata lives in RAM unless something calls UAVObjSave, which this does
    not, so a reboot undoes it even if the restore is missed.
    """
    import struct
    objdef = client.db[obj_name]
    meta_id = objdef.obj_id + 1
    client.send_raw(uavtalk.TYPE_OBJ_REQ, meta_id)
    deadline = time.time() + 3.0
    while time.time() < deadline and meta_id not in client.meta_payloads:
        client.run(duration=0.2, on_object=lambda *a: None)
    saved = client.meta_payloads.get(meta_id)
    if not saved or len(saved) < 8:
        return None
    flags = struct.unpack_from("<H", saved, 0)[0]
    flags = (flags & ~(0x3 << 4)) | (1 << 4)      # telemetryUpdateMode = PERIODIC
    client.send_raw(uavtalk.TYPE_OBJ, meta_id,
                    payload=struct.pack("<HH", flags, period_ms) + saved[4:])
    time.sleep(0.3)
    return saved


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--serial", metavar="PORT")
    ap.add_argument("--baud", type=int, default=57600)
    ap.add_argument("--udp", metavar="HOST:PORT")
    ap.add_argument("--xmldir", default=None)
    ap.add_argument("--six", action="store_true", help="full six-point calibration")
    ap.add_argument("--flip", action="store_true", help="two-pose bias vs gain check")
    ap.add_argument("--samples", type=int, default=100, help="samples per pose")
    ap.add_argument("--apply", action="store_true",
                    help="write the result to AccelGyroSettings (RAM)")
    ap.add_argument("--save", action="store_true",
                    help="with --apply, also persist it to flash")
    args = ap.parse_args()

    if not (args.six or args.flip):
        ap.error("pick --six or --flip")
    if args.save and not args.apply:
        ap.error("--save needs --apply")

    if args.udp:
        host, _, port = args.udp.partition(":")
        transport = uavtalk_client.UdpTransport(host, int(port or 9000))
    elif args.serial:
        transport = uavtalk_client.SerialTransport(args.serial, args.baud)
    else:
        ap.error("pick --serial or --udp")

    db = uavtalk.UAVObjectDB(args.xmldir or uavtalk_client.default_xml_dir())
    client = uavtalk_client.UAVTalkClient(transport, db)
    session = Session(client)

    print("Linking...")
    session.pump(2.0)

    saved_meta = set_stream_rate(client, "AccelState", 20)
    if saved_meta:
        print("AccelState raised to 20 ms for this run (restored at the end).")

    poses = SIX if args.six else FLIP
    means = {}
    try:
        for pose in poses:
            m = session.gather(pose, args.samples)
            if m is None:
                return 1
            means[pose] = m
            print("    mean  x=%+8.3f  y=%+8.3f  z=%+8.3f" % tuple(m))
    finally:
        if saved_meta:
            client.send_raw(uavtalk.TYPE_OBJ, db["AccelState"].obj_id + 1,
                            payload=saved_meta)
            time.sleep(0.2)

    print("\n" + "=" * 62)
    if args.flip:
        z_up = means["level"][2]
        z_dn = means["inverted"][2]
        bias = (z_up + z_dn) / 2.0
        gain = (z_dn - z_up) / (2.0 * GRAV)
        off_mg = 1000.0 * bias / GRAV
        gain_pct = 100.0 * (gain - 1.0)
        print("  mean z level    %+8.3f m/s^2" % z_up)
        print("  mean z inverted %+8.3f m/s^2" % z_dn)
        print("\n  Z zero-g offset  %+.3f m/s^2  (%+.0f mg)" % (bias, off_mg))
        print("  Z gain           %.4f  (%+.1f%%)" % (gain, gain_pct))
        print()
        if abs(gain_pct) < 3.0 and abs(off_mg) > 40.0:
            print("  -> Plain zero-g OFFSET. Gain is inside the +/-3% datasheet")
            print("     tolerance, so the part is fine. Run --six to correct it;")
            print("     AltFilter integrates accel, so an uncorrected offset")
            print("     walks the altitude estimate.")
        elif abs(gain_pct) >= 5.0:
            print("  -> Real GAIN error, outside datasheet tolerance. Confirm")
            print("     ACCEL_CONFIG holds the range the driver scales for --")
            print("     a mismatch there is a clean factor of 2 or 4, not a")
            print("     few percent.")
        else:
            print("  -> Both terms small.")
        return 0

    x = [means[p][0] for p in SIX]
    y = [means[p][1] for p in SIX]
    z = [means[p][2] for p in SIX]
    S, b = six_point_in_const_field_cal(GRAV, x, y, z)
    print("  accel_scale  X=%.5f  Y=%.5f  Z=%.5f" % tuple(S))
    print("  accel_bias   X=%+.4f  Y=%+.4f  Z=%+.4f  m/s^2" % tuple(b))
    print("               (%+.0f  %+.0f  %+.0f mg)"
          % tuple(1000.0 * v / GRAV for v in b))

    resid = []
    for p in SIX:
        v = means[p]
        c = [S[i] * v[i] - b[i] for i in range(3)]
        resid.append(np.linalg.norm(c))
    print("\n  corrected |a| per pose: %s" % " ".join("%.3f" % r for r in resid))
    print("  worst error vs %.3f: %.3f m/s^2"
          % (GRAV, max(abs(r - GRAV) for r in resid)))

    if not args.apply:
        print("\n  Not written. Re-run with --apply to store it (--save to persist).")
        return 0

    client.request_object("AccelGyroSettings")
    session.pump(1.0)
    values = {
        "accel_scale": {"X": float(S[0]), "Y": float(S[1]), "Z": float(S[2])},
        "accel_bias": {"X": float(b[0]), "Y": float(b[1]), "Z": float(b[2])},
    }
    client.send_object("AccelGyroSettings", values, msg_type=uavtalk.TYPE_OBJ_ACK)
    session.pump(1.0)
    print("\n  Written to AccelGyroSettings.")
    if args.save:
        client.send_object("ObjectPersistence",
                           {"Operation": "Save", "Selection": "SingleObject",
                            "ObjectID": db["AccelGyroSettings"].obj_id, "InstanceID": 0},
                           msg_type=uavtalk.TYPE_OBJ_ACK)
        session.pump(1.5)
        print("  Persisted to flash.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
