#!/usr/bin/env python3
"""
wedge_hunt - catch the cpu=100 wedge in the act and name the task doing it.

Reproduced twice now: hold the arming gesture for ~4-5 seconds and the board
pegs CPU at 100%, ManualControlCommand freezes at zeros, the actuator drops
to failsafe (ESCs lose signal and beep), and CPUOverload+Actuator latch
Critical. Telemetry keeps running throughout -- which means TaskInfo is
still readable DURING the wedge, and TaskInfo carries per-task runtime.
Whoever is spinning will be wearing the CPU.

This recreates the exact conditions of rc_monitor (same push rates), streams
raw and scaled receiver values, and the moment CPU crosses 90 or a blocking
alarm appears it starts dumping TaskInfo snapshots.

Run it, then when told, hold throttle DOWN + yaw FULL RIGHT until told to
stop. PROPS OFF.

Usage:
    python3 tools/wedge_hunt.py [--serial DEV] [--baud N]
"""

import argparse
import os
import struct
import sys
import threading
import time
import xml.etree.ElementTree as ET

_HERE = os.path.dirname(os.path.abspath(__file__))
NINJAPILOT_ROOT = os.environ.get(
    "NINJAPILOT_ROOT",
    os.path.abspath(os.path.join(_HERE, "..", "..", "NinjaPilot-15.02.ninja")))
sys.path.insert(0, os.path.join(NINJAPILOT_ROOT, "ground", "pyuavtalk"))
sys.path.insert(0, _HERE)

import uavtalk                                                # noqa: E402
from uavtalk_client import UAVTalkClient, default_xml_dir     # noqa: E402
from imu_bringup import Esp32SerialTransport                  # noqa: E402


def element_names(xml_dir, obj_xml, field):
    for fel in ET.parse(os.path.join(xml_dir, obj_xml)).getroot().iter("field"):
        if fel.get("name") == field:
            en = fel.get("elementnames")
            if en:
                return [n.strip() for n in en.split(",")]
            sub = fel.find("elementnames")
            return [e.text for e in sub] if sub is not None else []
    return []


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--serial", default="/dev/cu.usbserial-210")
    ap.add_argument("--baud", type=int, default=57600)
    args = ap.parse_args()

    xml_dir = default_xml_dir()
    db = uavtalk.UAVObjectDB(xml_dir)
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
    alarm_names_ev = element_names(xml_dir, "systemalarms.xml", "Alarm")
    t_start = [None]
    prev_ev = {"Armed": None, "act": None, "alarms": {}}

    def on_object(objdef, inst_id, decoded):
        got[objdef.name] = decoded
        # Timestamped event log. The wedge sequence is: receiver freezes at
        # first big stick movement, cpu pegs ~4s later -- ordering between
        # activity detection, Armed changes and alarm latches is exactly what
        # a 0.3s display loop can blur, so record transitions at arrival.
        if t_start[0] is None:
            return
        t = time.time() - t_start[0]
        if objdef.name == "FlightStatus":
            a = decoded.get("Armed")
            if a != prev_ev["Armed"]:
                print("  >> %5.1fs Armed: %s -> %s" % (t, prev_ev["Armed"], a),
                      flush=True)
                prev_ev["Armed"] = a
        elif objdef.name == "ReceiverActivity":
            key = (decoded.get("ActiveGroup"), decoded.get("ActiveChannel"))
            if key != prev_ev["act"]:
                print("  >> %5.1fs ReceiverActivity: group=%s ch=%s" %
                      (t, key[0], key[1]), flush=True)
                prev_ev["act"] = key
        elif objdef.name == "SystemAlarms" and alarm_names_ev:
            for n, v in zip(alarm_names_ev, decoded["Alarm"]):
                pv = prev_ev["alarms"].get(n)
                if pv != v and (v in ("Critical", "Error") or
                                (pv in ("Critical", "Error"))):
                    print("  >> %5.1fs ALARM %s: %s -> %s" % (t, n, pv, v),
                          flush=True)
                prev_ev["alarms"][n] = v

    threading.Thread(target=client.run,
                     kwargs=dict(duration=300, on_object=on_object,
                                 on_connected=connected.set),
                     daemon=True).start()
    if not connected.wait(30):
        sys.exit("no link (is something else holding the port?)")

    def fresh(name, timeout=1.5):
        got.pop(name, None)
        client.request_object(name)
        end = time.time() + timeout
        while time.time() < end:
            if name in got:
                return got[name]
            time.sleep(0.02)
        return None

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

    alarm_names = element_names(xml_dir, "systemalarms.xml", "Alarm")
    task_names = element_names(xml_dir, "taskinfo.xml", "StackRemaining")

    # Same conditions as rc_monitor, since that is where the wedge shows.
    set_period("ManualControlCommand", 100)
    set_period("ActuatorCommand", 250)
    set_period("SystemAlarms", 200)
    set_period("SystemStats", 500)

    def taskinfo_dump(tag):
        ti = fresh("TaskInfo", timeout=2.5)
        if not ti:
            print("    [%s] TaskInfo: NO REPLY" % tag, flush=True)
            return
        # RunningTime is percent per task; the spinner owns the CPU.
        rt = ti.get("RunningTime")
        sr = ti.get("StackRemaining")
        rn = ti.get("Running")
        names = task_names if task_names else \
            ["task%d" % i for i in range(len(rt or sr or []))]
        if rt:
            pairs = sorted(zip(names, rt), key=lambda x: -x[1])
            tops = ["%s=%s%%" % (n, v) for n, v in pairs[:8] if v]
            print("    [%s] runtime: %s" % (tag,
                  "  ".join(tops) if tops else "ALL ZERO (DIAG_TASKS off?)"),
                  flush=True)
        if rn:
            dead = [n for n, v in zip(names, rn)
                    if str(v) in ("False", "0") and n not in ("", None)]
            # Tasks never started on this target also read False; what
            # matters is one that WAS running at baseline and stops.
            print("    [%s] not-running: %s" % (tag, ",".join(dead) or "none"),
                  flush=True)
        if sr:
            lows = sorted(zip(names, sr), key=lambda x: x[1])
            lows = ["%s=%s" % (n, v) for n, v in lows[:6] if v]
            print("    [%s] lowest stacks: %s" % (tag, "  ".join(lows)),
                  flush=True)

    print("\nBaseline TaskInfo (healthy):", flush=True)
    taskinfo_dump("baseline")

    set_period("ReceiverActivity", 300)

    print("\n>>> HOLD throttle DOWN + yaw FULL RIGHT now, and KEEP HOLDING <<<\n",
          flush=True)

    t0 = time.time()
    t_start[0] = t0
    wedged_at = None
    dumps = 0
    while time.time() - t0 < 40:
        time.sleep(0.3)
        m = got.get("ManualControlCommand")
        st = got.get("SystemStats")
        al = got.get("SystemAlarms")
        cpu = st.get("CPULoad") if st else None
        blockers = []
        if al and alarm_names:
            blockers = [n for n, v in zip(alarm_names, al["Alarm"])
                        if v in ("Critical", "Error") and n not in ("GPS", "Telemetry")]
        raw = [int(v) for v in m["Channel"][:5]] if m else []
        print("  %5.1fs cpu=%-3s thr=%+5.2f yaw=%+5.2f raw=%-30s %s" % (
            time.time() - t0, cpu, m.get("Throttle", 0) if m else 0,
            m.get("Yaw", 0) if m else 0, raw,
            "WEDGED: " + ",".join(blockers) if blockers else ""), flush=True)

        if (cpu is not None and cpu >= 90) or blockers:
            if wedged_at is None:
                wedged_at = time.time() - t0
                print("\n  == wedge detected at %.1fs -- dumping TaskInfo ==" %
                      wedged_at, flush=True)
            if dumps < 6:
                taskinfo_dump("wedge+%d" % dumps)
                dumps += 1

    print("\nrestoring telemetry rates...", flush=True)
    for name, meta in original_meta.items():
        client.send_raw(uavtalk.TYPE_OBJ, db[name].obj_id + 1, 0, meta)
        time.sleep(0.15)
    if wedged_at is None:
        print("no wedge occurred in this window.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
