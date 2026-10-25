#!/usr/bin/env python3
"""
rc_calibrate - measure your transmitter's real stick travel and store it.

The seeded endpoints (342/1024/1706) are the textbook DSM 2048 range. Your
transmitter almost certainly does not match them exactly: travel adjust,
sub-trim and dual rates all move the ends, and a channel whose stored range is
wider than its real one will never reach full deflection, while a narrower one
saturates early and feels twitchy off centre.

This measures what your sticks actually produce, then writes it to the board
and saves it to flash.

    PROPS OFF. Nothing here arms the aircraft, but you will be moving the
    throttle stick through its full range.

Usage:
    python3 tools/rc_calibrate.py [--serial DEV] [--baud N]
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

import uavtalk                                                    # noqa: E402
from uavtalk_client import UAVTalkClient, default_xml_dir         # noqa: E402
from imu_bringup import Esp32SerialTransport                      # noqa: E402

# ManualControlCommand.Channel is indexed by the same element order as
# ManualControlSettings, so one list names both.
ELEMS = ["Throttle", "Roll", "Pitch", "Yaw", "FlightMode"]
# Below this much travel a channel clearly was not moved, and writing it would
# leave a stick that does nothing or a switch stuck on one mode.
MIN_TRAVEL = 200
# Fraction of throttle travel reserved below neutral, so the bottom of the
# stick reads negative. See the note where it is applied.
THROTTLE_NEUTRAL_MARGIN = 0.05


def countdown(msg, secs):
    for left in range(secs, 0, -1):
        sys.stdout.write("\r  %s ... %2ds " % (msg, left))
        sys.stdout.flush()
        time.sleep(1)
    sys.stdout.write("\r" + " " * 70 + "\r")


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--serial", default="/dev/cu.usbserial-210")
    ap.add_argument("--baud", type=int, default=57600)
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
                     kwargs=dict(duration=300, on_object=on_object,
                                 on_connected=connected.set),
                     daemon=True).start()

    if not connected.wait(30):
        sys.exit("no link to the board")
    print("linked.\n")

    def fetch(name, tries=12):
        got.pop(name, None)
        for _ in range(tries):
            client.request_object(name)
            time.sleep(0.7)
            if name in got:
                return got[name]
        return None

    def sample(secs):
        """Collect raw channel values for a while.

        Deliberately gentle. An earlier version polled at ~8Hz and that alone
        was enough to starve the flight stack into raising CPUOverload,
        Actuator and Stabilization alarms mid-calibration -- measuring the
        thing was breaking the thing. ManualControlCommand is already sent
        periodically, so mostly just listen, and nudge it occasionally in case
        the periodic update is slower than this window.
        """
        seen = []
        end = time.time() + secs
        last_poke = 0.0
        while time.time() < end:
            now = time.time()
            if now - last_poke > 1.0:
                client.request_object("ManualControlCommand")
                last_poke = now
            time.sleep(0.05)
            mcc = got.get("ManualControlCommand")
            if mcc and mcc.get("Channel"):
                seen.append([int(v) for v in mcc["Channel"][:len(ELEMS)]])
        return seen

    print("PROPS OFF. Transmitter on and bound.\n")
    print("1. Centre the sticks and pull the throttle all the way DOWN.")
    countdown("hold still", 5)
    rest = sample(4)
    if not rest:
        sys.exit("no receiver data -- is the transmitter on?")
    neutral = [sorted(c[i] for c in rest)[len(rest) // 2] for i in range(len(ELEMS))]
    print("   centre/idle: %s\n" % dict(zip(ELEMS, neutral)))

    print("2. Move EVERY stick through its full travel, corner to corner,")
    print("   and flip the flight-mode switch through all its positions.")
    countdown("starting", 3)
    moved = sample(20)
    print("   captured %d samples\n" % len(moved))

    lo = [min(c[i] for c in moved) for i in range(len(ELEMS))]
    hi = [max(c[i] for c in moved) for i in range(len(ELEMS))]

    bad = [ELEMS[i] for i in range(len(ELEMS)) if (hi[i] - lo[i]) < MIN_TRAVEL]
    for i, name in enumerate(ELEMS):
        print("   %-11s min %4d  neutral %4d  max %4d  travel %4d%s" % (
            name, lo[i], neutral[i], hi[i], hi[i] - lo[i],
            "   <-- barely moved" if name in bad else ""))
    if bad:
        print("\nNot writing anything: %s did not move enough to measure." % ", ".join(bad))
        print("Re-run and make sure every stick reaches both stops.")
        return 1

    mcs = fetch("ManualControlSettings")
    if not mcs:
        sys.exit("could not read ManualControlSettings")
    mn = list(mcs["ChannelMin"])
    nu = list(mcs["ChannelNeutral"])
    mx = list(mcs["ChannelMax"])
    for i in range(len(ELEMS)):
        mn[i], mx[i] = lo[i], hi[i]
        if i == 0:
            # Throttle neutral is the zero-thrust reference, and it must sit
            # ABOVE min -- not equal to it.
            #
            # scaleChannel() divides by (neutral - min) below neutral, and
            # returns a flat 0 when neutral == min. Throttle would then only
            # ever range 0.0..1.0. armhandler.c requires cmd.Throttle < 0
            # STRICTLY for a multirotor (the fabsf() < 0.01 branch is
            # ground-frame only), so a throttle that cannot go negative is a
            # board that can never arm -- with nothing to indicate why.
            #
            # Lifting it a few percent gives the bottom of stick travel a
            # region that reads negative, which is exactly the "throttle is
            # definitely down" the arming check is asking about.
            nu[i] = lo[i] + int(round(THROTTLE_NEUTRAL_MARGIN * (hi[i] - lo[i])))
        else:
            nu[i] = neutral[i]
    mcs["ChannelMin"], mcs["ChannelNeutral"], mcs["ChannelMax"] = mn, nu, mx

    client.send_object("ManualControlSettings", mcs)
    time.sleep(1.5)
    client.send_object("ObjectPersistence", {
        "Operation": "Save", "Selection": "SingleObject",
        "ObjectID": db["ManualControlSettings"].obj_id, "InstanceID": 0})
    time.sleep(2.0)

    back = fetch("ManualControlSettings")
    ok = back and list(back["ChannelMin"])[:len(ELEMS)] == lo
    print("\nstored and saved to flash: %s" % ("yes" if ok else "READBACK MISMATCH"))

    mcc = fetch("ManualControlCommand")
    if mcc:
        print("Connected=%s  Throttle=%+.2f Roll=%+.2f Pitch=%+.2f Yaw=%+.2f" % (
            mcc.get("Connected"), mcc.get("Throttle", 0), mcc.get("Roll", 0),
            mcc.get("Pitch", 0), mcc.get("Yaw", 0)))
        print("\nCentred sticks should read about 0.00, and full deflection about")
        print("+/-1.00. If they do, the calibration is good.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
