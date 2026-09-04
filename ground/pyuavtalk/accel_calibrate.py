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

  --six    The six fixed poses, solved the way the GCS wizard solves them --
           with EllipsoidCalibration(fitAlongXYZ=true). (calibrationutils.cpp
           also carries SixPointInConstFieldCal, ported here as well, but the
           accel wizard does not call it.)

  --cloud N
           The same fit over N free-form orientations instead of six named
           poses. Note you cannot WAVE an accelerometer the way you wave a
           magnetometer: a mag reads the same field moving or not, while an
           accel reads gravity plus whatever you are doing to it, so a sample
           taken mid-swing is not a gravity measurement. What generalises is
           the ellipsoid fit, not the waving -- hold the board still in as many
           attitudes as you like and every one of them feeds the fit.

Poses are recognised from the accelerometer itself, not from AttitudeState, so
they are yaw-invariant -- which matters because a board with no magnetometer
has a free-running yaw and would never match a yaw-bearing pose. Put the board
in the pose it asks for and it starts sampling on its own.

Results are printed. They are only written to the board with --apply, and only
persisted to flash with --save. Nothing here ever arms anything.

  accel_calibrate.py --serial /dev/cu.wchusbserial8320 --six
  accel_calibrate.py --udp 192.168.4.1:9000 --flip
  accel_calibrate.py --serial /dev/cu.wchusbserial8320 --cloud 30
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


def ellipsoid_calibration(nominal, x, y, z):
    """Port of CalibrationUtils::EllipsoidCalibration(fitAlongXYZ=true).

    This is what the GCS accel wizard actually runs -- not
    SixPointInConstFieldCal, which is also in calibrationutils.cpp but unused by
    that path. The difference that matters is the sample count: the six-point
    solver needs EXACTLY six, because it writes five difference equations
    between consecutive poses. This one least-squares-fits an ellipsoid to an
    arbitrary point cloud, so more orientations simply make it better
    conditioned.

    fitAlongXYZ=true constrains the fit to axis-aligned (no cross-axis terms).
    That is not a simplification we are choosing -- AccelGyroSettings can only
    store three scales and three biases, with no calibration matrix, so a
    rotated ellipsoid has nowhere to go for the accel.

    Returns (scale[3], center[3], radii[3]) with center in RAW sensor units.
    """
    x = np.asarray(x, dtype=float)
    y = np.asarray(y, dtype=float)
    z = np.asarray(z, dtype=float)

    D = np.column_stack([x * x, y * y, z * z, 2 * x, 2 * y, 2 * z])
    v = np.linalg.solve(D.T @ D, D.T @ np.ones(len(x)))

    center = -v[3:6] / v[0:3]
    gam = 1.0 + (v[3] ** 2 / v[0] + v[4] ** 2 / v[1] + v[5] ** 2 / v[2])
    radii = np.sqrt(gam / v[0:3])
    scale = nominal / radii
    return scale, center, radii


def bias_for_firmware(center, scale, path):
    """Convert an ellipsoid centre into the accel_bias the FIRMWARE expects.

    The two flight paths disagree, and it is not cosmetic:

      sensors.c  (Revo)   accels = (raw - accel_bias) * accel_scale
      attitude.c (CC3D)   accels =  raw * accel_scale - accel_bias

    The ellipsoid fit gives a centre in RAW units, which is what sensors.c
    wants directly. attitude.c scales BEFORE subtracting, so it needs
    centre * scale instead. The GCS writes the raw centre either way, which is
    right for Revo and off by a factor of scale on a CC3D-path board -- a few
    percent of the bias, small but real.

    The ESP32/LiteWing targets take the attitude.c path (BOARDISCC3D), so that
    is the default here.
    """
    if path == "sensors":
        return np.asarray(center, dtype=float)
    return np.asarray(center, dtype=float) * np.asarray(scale, dtype=float)


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


    def gather_rotating(self, need_buckets=16, quiet_axes=0.85,
                        band=(0.70, 1.30), steady=0.15, window=8):
        """Collect gravity samples while the board is slowly turned by hand.

        This is the magnetometer-style flow, and it does work for an accel --
        with one filter. A magnetometer reads the same field whether or not it
        is moving; an accelerometer reads gravity PLUS whatever you are doing to
        it, so samples taken mid-jerk have to go.

        The obvious filter is "keep it if the magnitude is 1 g", and it is
        WRONG here: the whole reason to run a calibration is that the magnitude
        is not 1 g yet. This board reads 10.91 where gravity is 9.807, so a
        tight band around g threw away every single sample and the tool sat
        there collecting nothing.

        So the test is STEADINESS, not correctness. A hand rotating a board
        smoothly changes the reading slowly; a jerk shows up as a spike in the
        magnitude over a few samples. Keep anything whose magnitude is steady
        across a short window and merely in the right ballpark -- the band is
        deliberately wide enough to admit a badly offset sensor, because that is
        the case being fixed.

        Turning it slowly gives more keepers; jerking it just wastes samples.
        Nothing has to be held still and nothing has to be counted.
        """
        buckets = {}
        kept = 0
        seen_total = 0
        recent = []
        print("\n  Slowly rotate the board through every attitude -- like")
        print("  turning a ball over in your hands. It stops on its own.\n")

        deadline = time.time() + 300.0
        last_draw = 0.0
        while time.time() < deadline:
            n = self.updates
            self.pump(0.05)
            if self.updates == n or self.accel is None:
                continue
            seen_total += 1
            vec = np.array(self.accel, dtype=float)
            mag = np.linalg.norm(vec)
            recent.append(mag)
            if len(recent) > window:
                recent.pop(0)
            if len(recent) < window:
                continue
            if not (band[0] * GRAV < mag < band[1] * GRAV):
                continue                       # not a plausible 1g reading at all
            if float(np.std(recent)) > steady:
                continue                       # magnitude lurching: being jerked
            kept += 1
            unit = vec / mag
            key = tuple(int(round(c)) for c in np.clip(unit * 1.3, -1, 1))
            buckets.setdefault(key, []).append(vec)

            covered = self._axis_coverage(buckets, quiet_axes)
            if time.time() - last_draw > 0.25:
                last_draw = time.time()
                print("\r    %d samples, %d/26 directions, %s        "
                      % (kept, len(buckets), self._missing_text(covered)),
                      end="", flush=True)
            if len(buckets) >= need_buckets and all(covered.values()):
                break
        print()

        if not all(self._axis_coverage(buckets, quiet_axes).values()):
            print("    Not enough coverage to fit. Missing: %s"
                  % self._missing_text(self._axis_coverage(buckets, quiet_axes)))
            return None
        if seen_total and kept * 4 < seen_total:
            print("    (note: %d%% of samples were dropped as movement -- "
                  "turning it more slowly helps)" % (100 - 100 * kept // seen_total))
        print("    fitting %d averaged directions from %d samples"
              % (len(buckets), kept))
        # one averaged point per direction, so a slow patch cannot outvote a fast one
        return np.array([np.mean(v, axis=0) for v in buckets.values()])

    @staticmethod
    def _axis_coverage(buckets, thresh):
        """Has each of the six faces been pointed down at some point?"""
        got = {p[0]: False for p in POSES}
        for vecs in buckets.values():
            unit = np.mean(vecs, axis=0)
            unit = unit / np.linalg.norm(unit)
            for name, axis, sign, _desc in POSES:
                if unit[axis] * sign > thresh:
                    got[name] = True
        return got

    @staticmethod
    def _missing_text(covered):
        missing = [n for n, ok in covered.items() if not ok]
        if not missing:
            return "coverage complete"
        return "still need: " + ", ".join(
            POSE_BY_NAME[m][3].split(",")[0].lower() for m in missing[:3])


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
    ap.add_argument("--rotate", action="store_true",
                    help="just turn the board over in your hands (default)")
    ap.add_argument("--convention", choices=("attitude", "sensors"), default="attitude",
                    help="which firmware path applies the terms (default attitude.c, "
                         "which is what the ESP32/LiteWing targets use)")
    ap.add_argument("--samples", type=int, default=100, help="samples per pose")
    ap.add_argument("--apply", action="store_true",
                    help="write the result to AccelGyroSettings (RAM)")
    ap.add_argument("--save", action="store_true",
                    help="with --apply, also persist it to flash")
    args = ap.parse_args()

    if not (args.six or args.flip):
        args.rotate = True
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

    cloud_points = None
    poses = [] if args.rotate else (SIX if args.six else FLIP)
    means = {}
    try:
        if args.rotate:
            cloud_points = session.gather_rotating()
            if cloud_points is None:
                return 1
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

    if cloud_points is not None:
        pts = cloud_points
    else:
        pts = np.array([means[p] for p in SIX])

    # EllipsoidCalibration, not SixPointInConstFieldCal: this is the solver the
    # GCS wizard actually calls, and it accepts any number of points.
    S, centre, radii = ellipsoid_calibration(GRAV, pts[:, 0], pts[:, 1], pts[:, 2])
    b = bias_for_firmware(centre, S, args.convention)
    print("  fitted radii  %.4f %.4f %.4f  (from %d points)"
          % (radii[0], radii[1], radii[2], len(pts)))
    print("  accel_scale  X=%.5f  Y=%.5f  Z=%.5f" % tuple(S))
    print("  accel_bias   X=%+.4f  Y=%+.4f  Z=%+.4f  m/s^2" % tuple(b))
    print("               (%+.0f  %+.0f  %+.0f mg)"
          % tuple(1000.0 * v / GRAV for v in b))

    resid = []
    for v in pts:
        if args.convention == "sensors":
            c = [(v[i] - b[i]) * S[i] for i in range(3)]
        else:
            c = [S[i] * v[i] - b[i] for i in range(3)]
        resid.append(np.linalg.norm(c))
    print("\n  corrected |a|: %s" % " ".join("%.3f" % r for r in resid[:8]))
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
