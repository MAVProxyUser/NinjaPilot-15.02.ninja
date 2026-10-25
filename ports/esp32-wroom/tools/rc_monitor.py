#!/usr/bin/env python3
"""
rc_monitor - live view of everything that decides whether the board arms.

Run this in one window and work the sticks in the other hand. It shows, once
a second, exactly what the flight code sees and what it is commanding to the
motors -- so an arming refusal names its own cause instead of being guessed at.

The ARM column spells out which precondition is failing:

    thr    throttle is not below neutral      (armhandler: cmd.Throttle < 0)
    yaw    the arming gesture is not being held hard enough
    alarm  Receiver or Guidance is CRITICAL   (forces disarm)
    OK     everything the arm check wants is true -- hold it for 1s

    PROPS OFF.

Usage:
    python3 tools/rc_monitor.py [--serial DEV] [--baud N]
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

ARMED_THRESHOLD = 0.50          # armhandler.c
# Arming gesture -> (field, sign that ARMS). armingInputLevel is negated for
# the "Right"/"Aft" cases and arming triggers on <= -threshold, so the sign
# that actually arms is the one below.
GESTURE = {
    "Yaw Right":     ("Yaw",   +1),
    "Yaw Left":      ("Yaw",   -1),
    "Roll Right":    ("Roll",  +1),
    "Roll Left":     ("Roll",  -1),
    "Pitch Aft":     ("Pitch", +1),
    "Pitch Forward": ("Pitch", -1),
}


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

    # SystemAlarms element names, from the same XML the ids come from.
    import xml.etree.ElementTree as ET
    alarm_names = []
    for fel in ET.parse(os.path.join(default_xml_dir(),
                                     "systemalarms.xml")).getroot().iter("field"):
        if fel.get("name") == "Alarm":
            en = fel.get("elementnames")
            alarm_names = [n.strip() for n in
                           (en.split(",") if en else
                            [e.text for e in fel.find("elementnames")])]
            break

    # Severity order is Uninitialised, OK, Warning, Critical, Error -- ERROR
    # OUTRANKS CRITICAL in this scheme, and okToArm() refuses on anything
    # >= Critical. So both block. GPS and Telemetry are exempted, exactly as
    # okToArm() exempts them.
    BLOCKING = ("Critical", "Error")
    EXEMPT = ("GPS", "Telemetry")

    start_t = time.time()
    prev_state = {"Armed": None, "alarms": {}}

    def on_object(objdef, inst_id, decoded):
        got[objdef.name] = decoded
        # Event prints, timestamped at arrival. A brief Arming state or a
        # one-second alarm latch can fall between display rows; these cannot.
        t = time.time() - start_t
        if objdef.name == "FlightStatus":
            a = decoded.get("Armed")
            if a != prev_state["Armed"]:
                print("  >> %6.1fs  Armed: %s -> %s" % (t, prev_state["Armed"], a),
                      flush=True)
                prev_state["Armed"] = a
        elif objdef.name == "SystemAlarms" and alarm_names:
            for n, v in zip(alarm_names, decoded["Alarm"]):
                pv = prev_state["alarms"].get(n)
                was = pv in BLOCKING
                now = v in BLOCKING
                if was != now and n not in EXEMPT:
                    print("  >> %6.1fs  ALARM %s: %s -> %s%s" % (
                        t, n, pv, v,
                        "   << BLOCKS ARMING" if now else "   (cleared)"),
                        flush=True)
                prev_state["alarms"][n] = v

    threading.Thread(target=client.run,
                     kwargs=dict(duration=100000, on_object=on_object,
                                 on_connected=connected.set),
                     daemon=True).start()
    if not connected.wait(30):
        sys.exit(
            "no link to the board after 30s.\n"
            "  The port exists but nothing answered. Most often that means\n"
            "  something else already has it open -- only one process can hold\n"
            "  %s at a time. Close any other tool talking\n"
            "  to the board and try again. If nothing else is running, check\n"
            "  the board is powered and try python3 tools/imu_bringup.py."
            % args.serial)

    def fresh(name, timeout=1.0):
        """Always a new reply. Reading a cached object at speed looks exactly
        like a stick held perfectly still, which is how a frozen sample once
        got mistaken for real data."""
        got.pop(name, None)
        client.request_object(name)
        end = time.time() + timeout
        while time.time() < end:
            if name in got:
                return got[name]
            time.sleep(0.02)
        return None

    # ---- make the board PUSH, instead of polling it -----------------------
    #
    # This used to do four request/response round trips per row. That is
    # fragile: when the board gets busier -- which is exactly what happens
    # while the arm gesture is held and okToArm() runs configuration_check()
    # every cycle -- a round trip exceeds the timeout and the display stalls,
    # which looks alarmingly like the link dropping. It is not; it is polling
    # losing a race.
    #
    # ManualControlCommand is already PERIODIC (2000ms), so only the period
    # needs lowering. FlightStatus is ONCHANGE and pushes the moment Armed
    # changes, which is exactly what is wanted. Metadata is 8 packed bytes:
    # flags, telemetryUpdatePeriod, gcsTelemetryUpdatePeriod,
    # loggingUpdatePeriod -- little endian. Only bytes [2:4] are touched, so
    # the update MODE is left exactly as the firmware shipped it.
    import struct

    original_meta = {}

    def set_period(name, period_ms):
        objid = db[name].obj_id
        metaid = objid + 1
        client.meta_payloads.pop(metaid, None)
        client.send_raw(uavtalk.TYPE_OBJ_REQ, metaid)
        end = time.time() + 3.0
        while time.time() < end:
            if metaid in client.meta_payloads:
                break
            time.sleep(0.02)
        meta = client.meta_payloads.get(metaid)
        if not meta or len(meta) < 8:
            return False
        original_meta[name] = meta
        new = bytearray(meta)
        struct.pack_into("<H", new, 2, period_ms)
        client.send_raw(uavtalk.TYPE_OBJ, metaid, 0, bytes(new))
        time.sleep(0.2)
        return True

    def restore_periods():
        for name, meta in original_meta.items():
            client.send_raw(uavtalk.TYPE_OBJ, db[name].obj_id + 1, 0, meta)
            time.sleep(0.15)

    pushed = set_period("ManualControlCommand", 100) and \
             set_period("ActuatorCommand", 250)
    set_period("SystemAlarms", 200)
    set_period("SystemStats", 500)
    if not pushed:
        print("  (could not raise the push rate; falling back to polling)")

    fms = fresh("ManualControlSettings", 3.0)
    fmset = fresh("FlightModeSettings", 3.0)
    gesture = fmset.get("Arming") if fmset else "?"
    field, sign = GESTURE.get(gesture, (None, 0))
    print("\narming gesture: %s" % gesture, end="")
    print("   (needs %s %s %+.2f, throttle < 0, held 1s)\n"
          % (field, ">=" if sign > 0 else "<=", sign * ARMED_THRESHOLD)
          if field else "   (not a stick gesture)\n")
    print("  Armed      thr    roll   pitch    yaw   motors            ARM",
          flush=True)
    misses = 0
    try:
        while True:
            # Read whatever the board last pushed. No request/response in
            # the hot path, so a busy board slows the display down instead of
            # stalling it.
            f = got.get("FlightStatus") if pushed else fresh("FlightStatus")
            m = got.get("ManualControlCommand") if pushed else fresh("ManualControlCommand")
            ac = got.get("ActuatorCommand") if pushed else fresh("ActuatorCommand")
            if pushed and not f:
                f = fresh("FlightStatus")
            if not (f and m):
                # Silence here is the worst possible output: an earlier
                # version just looped on `continue` and printed nothing at
                # all, which is indistinguishable from a hung tool.
                misses += 1
                print("  ...waiting for telemetry (%d) -- board busy or link "
                      "flaky" % misses, flush=True)
                time.sleep(0.5)
                continue
            misses = 0
            al = got.get("SystemAlarms")
            thr = m.get("Throttle", 0.0)
            val = m.get(field, 0.0) if field else 0.0
            gesture_ok = (val >= ARMED_THRESHOLD) if sign > 0 else (val <= -ARMED_THRESHOLD)

            why = []
            if thr >= 0:
                why.append("thr")
            if field and not gesture_ok:
                why.append("yaw" if field == "Yaw" else field.lower())
            if not m.get("Connected"):
                why.append("nolink")

            # Alarms outrank stick problems: okToArm() refuses on any alarm
            # at Critical or Error (except GPS/Telemetry), and an earlier
            # version of this tool fetched SystemAlarms and then never looked
            # at it -- it printed "OK - hold 1s" while the flight code was
            # refusing. The one lie a diagnostic tool must not tell.
            blockers = []
            if al and alarm_names:
                blockers = [n for n, v in zip(alarm_names, al["Alarm"])
                            if v in BLOCKING and n not in EXEMPT]

            if blockers:
                verdict = "BLOCKED alarm: " + ",".join(blockers)
            elif why:
                verdict = "need: " + ",".join(why)
            else:
                verdict = "OK - hold 1s"
                if field and abs(val) < 0.70:
                    # 0.50 is the threshold; a hair above it resets the 1s
                    # hold on every jitter. Full stick used to read 0.98.
                    verdict += "  (MARGINAL %.2f - FULL stick!)" % val
            if f.get("Armed") == "Armed":
                verdict = "*** ARMED ***"

            st = got.get("SystemStats")
            cpuload = st.get("CPULoad") if st else None

            ch = [int(v) for v in ac["Channel"][:4]] if ac else []
            print("  %-9s %+5.2f  %+5.2f  %+5.2f  %+5.2f  cpu=%-3s %-17s %s" % (
                f.get("Armed"), thr, m.get("Roll", 0), m.get("Pitch", 0),
                m.get("Yaw", 0), str(cpuload) if cpuload is not None else "?",
                str(ch), verdict), flush=True)
            time.sleep(0.4)
    except KeyboardInterrupt:
        print("\nrestoring telemetry rates...", flush=True)
    finally:
        # Leave the board as we found it. A forgotten 100ms push rate would
        # quietly eat the 57600 link for whatever runs next.
        restore_periods()
    return 0


if __name__ == "__main__":
    sys.exit(main())
