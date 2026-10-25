#!/usr/bin/env python3
"""
motor_watch - live per-motor commands while you arm and raise throttle.

Answers one question: when a motor doesn't spin, is the FLIGHT CODE holding
it back, or is the command identical and the problem downstream (ESC
calibration, wiring, motor)?

Shows, twice a second:

    Armed  throttle  attitude(roll/pitch)  M1..M4 commanded us  verdict

The verdict column flags any motor commanded >=50us below the highest one,
names its airframe position, and -- because Stabilized mode is ACTIVE on the
bench -- says whether the attitude correction explains it: a frame the board
believes is tilted gets one corner pinned at minimum and its diagonal pushed
harder. That is stabilization doing its job, not a fault.

If all four commands are equal and one motor still does not spin, the flight
code is exonerated: look at that ESC's calibration, its signal lead, or the
motor itself.

Attaches WITHOUT resetting the board, so you can start it before or after
arming. PROPS OFF.

Usage:
    python3 tools/motor_watch.py [--serial DEV] [--baud N]
"""

import argparse
import os
import struct
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

# Mixer channel -> airframe position (Quad X, matches board_hw_defs.c)
POS = {0: "M1 front-left/p15", 1: "M2 front-right/p33",
       2: "M3 rear-right/p27", 3: "M4 rear-left/p12"}
# A commanded difference this big is a deliberate control action, not noise.
SPREAD_US = 50


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

    print("opening %s (board keeps running -- attach does not reset it)..."
          % args.serial, flush=True)
    client = UAVTalkClient(Locked(Esp32SerialTransport(args.serial, args.baud)), db)
    got = {}
    connected = threading.Event()

    def on_object(objdef, inst_id, decoded):
        got[objdef.name] = decoded

    threading.Thread(target=client.run,
                     kwargs=dict(duration=100000, on_object=on_object,
                                 on_connected=connected.set),
                     daemon=True).start()
    if not connected.wait(30):
        sys.exit("no link -- is something else holding the port?")
    print("[link] up\n", flush=True)

    original_meta = {}

    def set_period(name, period_ms):
        metaid = db[name].obj_id + 1
        client.meta_payloads.pop(metaid, None)
        client.send_raw(uavtalk.TYPE_OBJ_REQ, metaid)
        end = time.time() + 3.0
        while time.time() < end and metaid not in client.meta_payloads:
            time.sleep(0.02)
        meta = client.meta_payloads.get(metaid)
        if not meta or len(meta) < 8:
            return False
        original_meta[name] = meta
        new = bytearray(meta)
        struct.pack_into("<H", new, 2, period_ms)
        client.send_raw(uavtalk.TYPE_OBJ, metaid, 0, bytes(new))
        time.sleep(0.15)
        return True

    set_period("ActuatorCommand", 100)
    set_period("AttitudeState", 200)
    set_period("ManualControlCommand", 200)

    print("Arm and raise throttle slowly. PROPS OFF. Ctrl+C to stop.\n")
    print("  Armed      thr   roll   pitch   M1     M2     M3     M4    verdict")
    try:
        while True:
            time.sleep(0.5)
            f = got.get("FlightStatus")
            m = got.get("ManualControlCommand")
            ac = got.get("ActuatorCommand")
            at = got.get("AttitudeState")
            if not ac:
                continue
            ch = [int(v) for v in ac["Channel"][:4]]
            hi = max(ch)
            armed = f.get("Armed") if f else "?"
            roll = at.get("Roll", 0.0) if at else 0.0
            pitch = at.get("Pitch", 0.0) if at else 0.0

            verdict = ""
            if armed == "Armed" and hi > 1005:
                low = [i for i, v in enumerate(ch) if hi - v >= SPREAD_US]
                if low:
                    names = ", ".join(POS[i] for i in low)
                    # Which way is the board leaning? Attitude explains a
                    # held-back motor if it sits on the "high" side.
                    tilt = []
                    if abs(roll) > 1.5:
                        tilt.append("roll %+.1f" % roll)
                    if abs(pitch) > 1.5:
                        tilt.append("pitch %+.1f" % pitch)
                    if tilt:
                        verdict = "HELD BACK: %s  <- stab correcting %s" % (
                            names, ", ".join(tilt))
                    else:
                        # Level board with a big sustained spread is USUALLY
                        # integral windup, not hardware: on a bench the craft
                        # cannot rotate, the correction never succeeds, and
                        # the PID integrators accumulate until motors
                        # saturate. Verified on this airframe: chopping
                        # throttle (integral reset) brought all four back to
                        # equal. Only suspect the ESC/motor if commands stay
                        # equal and it still will not spin.
                        verdict = "HELD BACK: %s  <- level board: likely " \
                                  "INTEGRAL WINDUP (normal on bench). Chop " \
                                  "throttle 2s, re-raise: equal=windup, " \
                                  "still split=hardware" % names
                else:
                    verdict = "all four equal -- if one is still not " \
                              "spinning, it is the ESC/motor, not the code"
            print("  %-9s %+5.2f  %+5.1f  %+5.1f  %4d   %4d   %4d   %4d   %s" % (
                armed, m.get("Throttle", 0) if m else 0, roll, pitch,
                ch[0], ch[1], ch[2], ch[3], verdict), flush=True)
    except KeyboardInterrupt:
        print("\nrestoring telemetry rates...", flush=True)
    finally:
        for name, meta in original_meta.items():
            client.send_raw(uavtalk.TYPE_OBJ, db[name].obj_id + 1, 0, meta)
            time.sleep(0.15)
    return 0


if __name__ == "__main__":
    sys.exit(main())
