#!/usr/bin/env python3
"""
orientation_check - does the board's idea of "nose" match the airframe's?

Read-only, no arming, no throttle, no settings written. Default is a guided
run: it SAYS "Nose up", you tip the airframe and press Enter, it reads what
the board believes (estimate AND raw accelerometer), five moves, then a
verdict:

    nose up     board: NOSE UP    31 deg   accel x -5.0 y +0.2 z -8.4   ok
    ...
    VERDICT: pitch and roll BOTH inverted -> board yaw is 180 deg from the
             airframe. Fix: AttitudeSettings.BoardRotation Yaw = 180, save,
             power cycle, re-run this. Flying like this flips at liftoff.

"Nose" always means the AIRFRAME's nose - the end you fly forward. "Left" is
the left arm as seen from behind, flying forward.

    python3 orientation_check.py [--host 192.168.0.45] [--quiet]
    python3 orientation_check.py --live [--seconds 60]   # continuous readout
"""
import argparse
import os
import subprocess
import sys
import threading
import time

_HERE = os.path.dirname(os.path.abspath(__file__))
NINJAPILOT_ROOT = os.environ.get(
    "NINJAPILOT_ROOT",
    os.path.abspath(os.path.join(_HERE, "..", "..", "NinjaPilot-15.02.ninja")))
sys.path.insert(0, os.path.join(NINJAPILOT_ROOT, "ground", "pyuavtalk"))
import uavtalk  # noqa: E402
from uavtalk_client import UdpTransport, UAVTalkClient, default_xml_dir  # noqa: E402

TILT = 8.0   # deg: below this the board saw no tilt


def describe(pitch, roll):
    p = ("NOSE DOWN %2.0f deg" % -pitch) if pitch < -TILT else ("NOSE UP   %2.0f deg" % pitch) if pitch > TILT else "pitch level      "
    r = ("LEFT SIDE DOWN  %2.0f deg" % -roll) if roll < -TILT else ("RIGHT SIDE DOWN %2.0f deg" % roll) if roll > TILT else "roll level          "
    return p, r


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--host", default="192.168.0.45")
    ap.add_argument("--port", type=int, default=9000)
    ap.add_argument("--live", action="store_true", help="continuous readout instead of the guided asks")
    ap.add_argument("--seconds", type=float, default=60.0, help="--live duration")
    ap.add_argument("--quiet", action="store_true", help="no voice")
    args = ap.parse_args()

    def say(msg):
        print("[voice] %s" % msg, flush=True)
        if not args.quiet:
            try:
                subprocess.run(["say", msg], timeout=15)
            except Exception:
                pass

    db = uavtalk.UAVObjectDB(default_xml_dir())
    client = UAVTalkClient(UdpTransport(args.host, args.port), db)
    latest = {}
    lock = threading.Lock()

    def on_object(objdef, inst_id, decoded):
        with lock:
            latest[objdef.name] = dict(decoded)
    threading.Thread(target=lambda: client.run(on_object=on_object, duration=100000),
                     daemon=True).start()
    time.sleep(1.5)

    def fetch(name, timeout=4.0):
        with lock:
            latest.pop(name, None)
        o = db[name]
        end = time.time() + timeout
        while time.time() < end:
            client.transport.send(uavtalk.build_packet(uavtalk.TYPE_OBJ_REQ, o.obj_id, 0))
            for _ in range(8):
                with lock:
                    v = latest.get(name)
                if v is not None:
                    return v
                time.sleep(0.05)
        sys.exit("could not read %s - is the board on and nothing else connected?" % name)

    rot = fetch("AttitudeSettings").get("BoardRotation")
    print("AttitudeSettings.BoardRotation (Roll,Pitch,Yaw) = %s" % (rot,))

    if args.live:
        t_end = time.time() + args.seconds
        while time.time() < t_end:
            att = fetch("AttitudeState")
            p, r = describe(float(att["Pitch"]), float(att["Roll"]))
            print("board says: %s   %s" % (p, r), flush=True)
            time.sleep(0.25)
        return

    # ---- guided: five asks, Enter after each, then the verdict --------------
    MOVES = [("nose up", "Nose up. Tip the airframe's nose up, above level.", "Pitch", +1),
             ("nose down", "Nose down. Tip the airframe's nose down.", "Pitch", -1),
             ("left", "Left. Dip the left arm, left as seen from behind.", "Roll", -1),
             ("right", "Right. Dip the right arm.", "Roll", +1),
             ("level", "Level. Hold it flat.", None, 0)]
    say("Orientation check. No motors. Hold the quad the way it flies.")
    results = []
    for name, prompt, key, want in MOVES:
        say(prompt)
        try:
            input("   ... press Enter when you are there: ")
        except EOFError:
            pass
        time.sleep(0.3)
        att = fetch("AttitudeState")
        acc = fetch("AccelState")
        pitch, roll = float(att["Pitch"]), float(att["Roll"])
        ptxt, rtxt = describe(pitch, roll)
        if key is None:
            ok = abs(pitch) < TILT and abs(roll) < TILT
            seen = 0
        else:
            v = pitch if key == "Pitch" else roll
            seen = 1 if v > TILT else -1 if v < -TILT else 0
            ok = seen == want
        results.append((name, key, want, seen, pitch, roll, float(acc["z"])))
        print("  %-9s board: %s  %s   accel x %+5.1f y %+5.1f z %+5.1f   %s"
              % (name, ptxt, rtxt, acc["x"], acc["y"], acc["z"],
                 "ok" if ok else ("NO TILT SEEN" if seen == 0 and key else "INVERTED" if key else "not level")), flush=True)
        say("Board says " + (ptxt if key == "Pitch" else rtxt if key == "Roll" else ptxt + ", " + rtxt).replace("deg", "degrees").lower())

    pitch_r = [r for r in results if r[1] == "Pitch"]
    roll_r = [r for r in results if r[1] == "Roll"]
    def axis_state(rs):
        seen = [r[3] for r in rs]
        want = [r[2] for r in rs]
        if all(s == w for s, w in zip(seen, want)):
            return "ok"
        if all(s == -w for s, w in zip(seen, want)):
            return "inverted"
        if all(s == 0 for s in seen):
            return "no tilt"
        return "mixed"
    ps, rs_ = axis_state(pitch_r), axis_state(roll_r)
    lvl = [r for r in results if r[1] is None]
    z_up = lvl and lvl[0][6] > 5.0
    print("\nVERDICT: pitch %s, roll %s%s" % (ps, rs_, ", accel z POSITIVE at level (board upside down?)" if z_up else ""))
    if ps == "ok" and rs_ == "ok":
        msg = "Board frame matches the airframe. Orientation is good."
        print("  " + msg)
    elif ps == "inverted" and rs_ == "inverted":
        msg = "Both axes inverted. The board's nose points at the tail: yaw 180 from the airframe."
        print("  " + msg)
        print("  Fix: AttitudeSettings.BoardRotation Yaw = 180 (Roll 0, Pitch 0), save, power")
        print("  cycle, run this again. Do NOT fly like this - on a correct mixer it is positive")
        print("  feedback on both axes and flips the moment the wheels get light.")
    elif ps == "inverted" or rs_ == "inverted":
        msg = "One axis inverted only - a 180 roll or pitch mount (check accel z sign at level)."
        print("  " + msg)
        print("  Fix: BoardRotation Roll=180 if roll is the inverted one and z is positive at level,")
        print("  Pitch=180 for pitch. Re-run after saving.")
    elif ps == "mixed" or rs_ == "mixed":
        msg = "Axes look swapped or mixed - a 90 degree mount. Check which way the board sits."
        print("  " + msg + "  Fix: BoardRotation Yaw = 90 or -90; re-run after saving.")
    else:
        msg = "I did not see clear tilts. Tilt further, about 30 degrees, and run again."
        print("  " + msg)
    say(msg)


if __name__ == "__main__":
    main()
