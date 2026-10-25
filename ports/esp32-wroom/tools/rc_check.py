#!/usr/bin/env python3
"""
rc_check - verify stick DIRECTIONS, and reverse any channel that is backwards.

Calibration (rc_calibrate.py) measures how far each stick travels. It says
nothing about which way. A channel can be perfectly calibrated and still
reversed, and a reversed roll or pitch is not a nuisance -- stabilization
drives the airframe the wrong way and it flips on takeoff.

OpenPilot's convention, which the flight code assumes everywhere:

    Roll      right      -> positive
    Pitch     nose UP    -> positive       (stick back / toward you)
    Yaw       right      -> positive
    Throttle  up         -> positive

This asks for one movement at a time, reports the sign it actually sees, and
offers to fix any channel that disagrees. Reversal is stored as ChannelMax <
ChannelMin -- scaleChannel() handles min > max explicitly; there is no
separate "reverse" flag in ManualControlSettings.

    PROPS OFF.

Usage:
    python3 tools/rc_check.py [--serial DEV] [--baud N] [--apply]
"""

import argparse
import os
import sys
import threading
import time

_HERE = os.path.dirname(os.path.abspath(__file__))
NINJAPILOT_ROOT = os.environ.get(
    "NINJAPILOT_ROOT",
    os.path.abspath(os.path.join(_HERE, "..", "..", "NinjaPilot-15.02.ninja")))
sys.path.insert(0, os.path.join(NINJAPILOT_ROOT, "ground", "pyuavtalk"))
sys.path.insert(0, _HERE)

import uavtalk                                                # noqa: E402
from uavtalk_client import UAVTalkClient, default_xml_dir     # noqa: E402
from imu_bringup import Esp32SerialTransport                  # noqa: E402

# element index, name, the movement to ask for, expected sign
AXES = [
    (0, "Throttle", "throttle all the way DOWN",              -1),
    (1, "Roll",     "roll RIGHT  (right stick to the right)", +1),
    (2, "Pitch",    "pitch NOSE UP (right stick toward you)", +1),
    (3, "Yaw",      "yaw RIGHT   (left stick to the right)",  +1),
]
# Throttle is checked too, and deliberately first. rc_calibrate ASSUMES the
# stick-down end produces the low raw value -- it never verifies it. A
# transmitter with a servo-reversed throttle channel sails through
# calibration and comes out reading +1 with the stick DOWN, which is the most
# dangerous reversal there is: arming at the bottom becomes impossible, and
# "fixing" that by arming at the top puts full thrust one instinctive
# pull-to-idle away. Down-expect-negative also leaves the stick in the safe
# position when the check ends.
# Fraction of throttle travel reserved below neutral; must match
# rc_calibrate.THROTTLE_NEUTRAL_MARGIN so a reversal fix here reproduces the
# same zero-thrust reference calibration would have set.
THROTTLE_NEUTRAL_MARGIN = 0.05
# Below this a stick clearly was not moved, and calling a direction on noise
# would be worse than saying nothing.
MOVED = 0.40


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--serial", default="/dev/cu.usbserial-210")
    ap.add_argument("--baud", type=int, default=57600)
    ap.add_argument("--apply", action="store_true",
                    help="reverse any channel found backwards, and save it")
    args = ap.parse_args()

    db = uavtalk.UAVObjectDB(default_xml_dir())
    lock = threading.Lock()

    class Locked(object):
        def __init__(self, inner):
            self.inner = inner

        def send(self, data):
            with lock:
                self.inner.send(data)

        def poll_recv(self, timeout):
            return self.inner.poll_recv(timeout)

    print("opening %s (board keeps running -- attach does not reset it; "
          "link typically up in ~2s)..." % args.serial, flush=True)
    client = UAVTalkClient(Locked(Esp32SerialTransport(args.serial, args.baud)), db)
    got = {}
    connected = threading.Event()

    def on_object(objdef, inst_id, decoded):
        got[objdef.name] = decoded

    threading.Thread(target=client.run,
                     kwargs=dict(duration=600, on_object=on_object,
                                 on_connected=connected.set),
                     daemon=True).start()
    if not connected.wait(30):
        sys.exit("no link to the board")

    def fresh(name, timeout=1.5):
        """Clear, request, wait. Never returns a cached value -- reading a
        stale object at speed looks exactly like a stick held still, which
        is how a frozen sample once got mistaken for real data."""
        got.pop(name, None)
        client.request_object(name)
        end = time.time() + timeout
        while time.time() < end:
            if name in got:
                return got[name]
            time.sleep(0.02)
        return None

    print("\nPROPS OFF. Transmitter on.\n")
    findings = {}
    for idx, name, prompt in [(a[0], a[1], a[2]) for a in AXES]:
        input("  Hold %-42s then press Enter: " % prompt)
        peak = 0.0
        for _ in range(6):
            m = fresh("ManualControlCommand")
            if m and abs(m.get(name, 0.0)) > abs(peak):
                peak = m.get(name, 0.0)
        expect = dict((a[1], a[3]) for a in AXES)[name]
        if abs(peak) < MOVED:
            print("      %-6s did not move (%.2f) -- skipped\n" % (name, peak))
            continue
        ok = (peak > 0) == (expect > 0)
        findings[name] = (peak, ok)
        print("      %-6s reads %+.2f  ->  %s\n" % (name, peak,
              "correct" if ok else "REVERSED"))

    bad = [n for n, (p, ok) in findings.items() if not ok]
    if not bad:
        print("All checked axes are the right way round.")
        return 0

    print("Reversed: %s" % ", ".join(bad))
    if not args.apply:
        print("Re-run with --apply to reverse them and save to flash.")
        return 1

    mcs = fresh("ManualControlSettings")
    if not mcs:
        sys.exit("could not read ManualControlSettings")
    mn = list(mcs["ChannelMin"])
    mx = list(mcs["ChannelMax"])
    nu = list(mcs["ChannelNeutral"])
    for idx, name, _prompt, _exp in AXES:
        if name in bad:
            mn[idx], mx[idx] = mx[idx], mn[idx]   # reversal IS max < min
            print("  %-8s min/max swapped -> %d/%d" % (name, mn[idx], mx[idx]))
            if idx == 0:
                # Throttle's neutral is the zero-thrust reference sitting a
                # margin above the idle end. Swapping min/max moved the idle
                # end, so recompute it -- signed arithmetic makes this
                # correct in both directions. Roll/pitch/yaw neutrals are the
                # measured stick centre, which a swap does not move.
                nu[idx] = mn[idx] + int(round(THROTTLE_NEUTRAL_MARGIN *
                                              (mx[idx] - mn[idx])))
                print("  %-8s neutral recomputed -> %d" % (name, nu[idx]))
    mcs["ChannelMin"], mcs["ChannelMax"] = mn, mx
    mcs["ChannelNeutral"] = nu
    client.send_object("ManualControlSettings", mcs)
    time.sleep(1.5)
    client.send_object("ObjectPersistence", {
        "Operation": "Save", "Selection": "SingleObject",
        "ObjectID": db["ManualControlSettings"].obj_id, "InstanceID": 0})

    # Do NOT just sleep and exit. Closing the port resets the board, and an
    # earlier version returned about two seconds after asking for the save --
    # early enough that the write never reached flash. It printed "Saved" and
    # the reversal silently evaporated on the next boot. Wait for the flight
    # side to actually report Completed, then read the values back.
    op = None
    for _ in range(15):
        op = fresh("ObjectPersistence", timeout=1.0)
        if op and op.get("Operation") in ("Completed", "Error"):
            break
    if not op or op.get("Operation") != "Completed":
        print("\nSAVE DID NOT COMPLETE (%s) -- settings are in RAM only and will"
              % (op.get("Operation") if op else "no reply"))
        print("be lost on the next power cycle. Re-run.")
        return 1

    back = fresh("ManualControlSettings", timeout=3.0)
    if not back or list(back["ChannelMin"]) != mn or list(back["ChannelMax"]) != mx:
        print("\nREADBACK MISMATCH -- the board did not take the reversal.")
        return 1
    print("\nSaved and verified on the board. Power-cycle and re-run without")
    print("--apply to confirm it survived.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
