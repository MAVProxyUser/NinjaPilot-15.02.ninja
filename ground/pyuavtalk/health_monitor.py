#!/usr/bin/env python3
"""Standalone System Health monitor for the realposix board.

Reports exactly what the GCS System Health gadget paints - same SystemAlarms
fields, same tile names - without the GCS running. Modes:

  python3 health_monitor.py                     one snapshot table
  python3 health_monitor.py --watch 120         timeline: print every tile
                                                transition for 120s (0=forever)
  python3 health_monitor.py --watch 60 --log health.jsonl
  python3 health_monitor.py --enable-fclogs     turn on onboard DebugLog
                                                (Always) + SystemAlarms/
                                                FlightStatus onchange logging

Tile colors in the GCS map to alarm severities:
  greyed + X = Uninitialised (no module ever set the alarm)
  green = OK, orange = Warning, red = Error/Critical.
Master Caution lights when anything is >= Warning.
"""
import argparse
import json
import struct
import sys
import time

sys.path.insert(0, "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/ground/pyuavtalk")
import uavtalk  # noqa: E402
from uavtalk_client import UAVTalkClient, UdpTransport  # noqa: E402
import flight_config  # noqa: E402

XML = "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/shared/uavobjectdefinition"
HOST, PORT = "192.168.0.90", 9000

# GCS tile label -> SystemAlarms.Alarm element (order matches systemalarms.xml)
ALARM_ELEMENTS = ["SystemConfiguration", "BootFault", "OutOfMemory", "StackOverflow",
                  "CPUOverload", "EventSystem", "Telemetry", "Receiver", "ManualControl",
                  "Actuator", "Attitude", "Sensors", "Magnetometer", "Airspeed",
                  "Stabilization", "Guidance", "PathPlan", "Battery", "FlightTime",
                  "I2C", "GPS"]
TILE = {"SystemConfiguration": "CONFIG", "BootFault": "BOOT", "OutOfMemory": "MEM",
        "StackOverflow": "STACK", "CPUOverload": "CPU", "EventSystem": "EVENT",
        "Telemetry": "LINK", "Receiver": "INPUT", "ManualControl": "MANUAL",
        "Actuator": "OUTPUT", "Attitude": "ATTI", "Sensors": "SENSOR",
        "Magnetometer": "MAG", "Airspeed": "AIRSPD", "Stabilization": "STAB",
        "Guidance": "PATH", "PathPlan": "PLAN", "Battery": "BATT",
        "FlightTime": "TIME", "I2C": "CAN", "GPS": "GPS"}

# Established causes on THIS bench (realposix on the OSD32MP1). Keep these in
# step with osd32mp1/CLAUDE.md - they are diagnoses, not guesses.
WHY = {
    ("Attitude", "Warning"): "estimator staleness watchdog: woke on 10ms timeout with no "
                             "fresh sensor sample (stateestimation.c TIMEOUT_MS) - open thread",
    ("Attitude", "Error"): "state-estimation filter chain init error",
    ("Attitude", "Critical"): "filtercf calibration/zeroing window (boot or chain re-init)",
    ("Stabilization", "Warning"): "inner loop below ~120 Hz (gyroupdates>8/pass) or outer "
                                  "loop >2 passes behind",
    ("Stabilization", "Critical"): "inner loop below ~60 Hz or outer loop >4 passes behind",
    ("Receiver", "Warning"): "no GCSReceiver stream - GCS Control gadget idle / no joystick",
    ("Receiver", "Error"): "receiver configured but signal lost mid-stream",
    ("PathPlan", "Warning"): "no valid path plan uploaded (normal outside missions)",
    ("GPS", "Warning"): "GPS data arriving but no usable fix",
    ("GPS", "Critical"): "no 3D fix (normal indoors) or no GPS data from CAN node",
    ("EventSystem", "Warning"): "event error in the last 1s: callback error, queue-full drop "
                                "or late periodic event - IDs in SystemStats",
    ("ManualControl", "Warning"): "manualcontrol running without valid input",
    ("CPUOverload", "Warning"): "CPULoad above CPULOAD_LIMIT_WARNING (80%)",
    ("CPUOverload", "Critical"): "CPULoad above CPULOAD_LIMIT_CRITICAL (95%)",
    ("Magnetometer", "Uninitialised"): "RM3100 never seen on CAN (transport monitor waits for "
                                       "first data)",
    ("Magnetometer", "Warning"): "mag delivery below half its native 25 Hz",
    ("Magnetometer", "Error"): "mag was streaming and has gone silent >3s",
    ("Guidance", "Uninitialised"): "PathFollower not active",
    ("Airspeed", "Uninitialised"): "Airspeed module not running",
    ("Battery", "Uninitialised"): "power source not yet read (OTG registers unavailable)",
    ("Battery", "OK"): "power good, AC/jack source (GCS: BATT green + AC box lit)",
    ("Battery", "Warning"): "power good, USB VBUS source (GCS: BATT green + USB box lit; "
                            "USB cannot fly motors; a data cable also raises VBUS)",
    ("FlightTime", "Uninitialised"): "no flight-time limit configured",
    ("I2C", "Uninitialised"): "CAN0 never delivered a frame",
    ("I2C", "Warning"): "CAN0 over 50% of the 1 Mbit wire (kinda saturated)",
    ("I2C", "Error"): "CAN0 over 80% of the 1 Mbit wire (oversaturated)",
    ("I2C", "Critical"): "CAN0 died after first contact (no frames in the last second)",
}

COLOR = {"Uninitialised": "greyed/X", "OK": "green", "Warning": "ORANGE",
         "Error": "RED", "Critical": "RED"}
SEV = {"Uninitialised": -1, "OK": 0, "Warning": 1, "Error": 2, "Critical": 3}

_META_STRUCT = struct.Struct("<HHHH")  # flags, telPeriod, gcsPeriod, logPeriod
_UAVOBJ_LOGGING_SHIFT = 8
_LOGMODE = {"manual": 0, "periodic": 1, "onchange": 2, "throttled": 3}


def now_str():
    t = time.time()
    return time.strftime("%H:%M:%S", time.localtime(t)) + ".%03d" % int((t % 1) * 1000)


def snapshot_table(alarms, stats):
    rows = []
    caution = False
    for el in ALARM_ELEMENTS:
        st = alarms.get(el, "?")
        if SEV.get(st, 0) >= 1:
            caution = True
        why = WHY.get((el, st), "")
        rows.append((TILE[el], el, st, COLOR.get(st, "?"), why))
    out = [f"{'TILE':8s} {'alarm':20s} {'status':13s} {'gcs color':9s} why"]
    for r in rows:
        out.append(f"{r[0]:8s} {r[1]:20s} {r[2]:13s} {r[3]:9s} {r[4]}")
    out.append(f"MASTER CAUTION: {'ON' if caution else 'off'}")
    pwr = {"Warning": "USB (VBUS present)", "OK": "AC/jack (no VBUS)"}.get(
        alarms.get("Battery"), "unknown (OTG regs unreadable)")
    out.append(f"POWER SOURCE: {pwr}")
    if stats:
        out.append(f"CPULoad {stats.get('CPULoad')}%  heap {stats.get('HeapRemaining')}  "
                   f"EventWarnID 0x{int(stats.get('EventSystemWarningID', 0)):08X}  "
                   f"CbErrID 0x{int(stats.get('ObjectManagerCallbackID', 0)):08X}  "
                   f"QErrID 0x{int(stats.get('ObjectManagerQueueID', 0)):08X}")
    return "\n".join(out)


def obj_name_for_id(db, objid):
    o = db.by_id.get(objid)
    return o.name if o else ("0x%08X" % objid) if objid else "-"


class Monitor(object):
    def __init__(self, client, logfile=None):
        self.client = client
        self.alarms = {}
        self.stats = {}
        self.log = open(logfile, "a") if logfile else None
        self.transitions = 0
        self.incidence = {}   # el -> {state: seconds}
        self.last_sample_t = None

    def _accumulate(self):
        t = time.time()
        if self.last_sample_t is not None and self.alarms:
            dt = t - self.last_sample_t
            for el, st in self.alarms.items():
                self.incidence.setdefault(el, {}).setdefault(st, 0.0)
                self.incidence[el][st] += dt
        self.last_sample_t = t

    def on_object(self, objdef, inst, d):
        if objdef.name == "SystemStats":
            self.stats = d
            return
        if objdef.name != "SystemAlarms":
            return
        self._accumulate()
        new = dict(zip(ALARM_ELEMENTS, d["Alarm"]))
        for el in ALARM_ELEMENTS:
            old = self.alarms.get(el)
            if old is not None and new[el] != old:
                self.transitions += 1
                why = WHY.get((el, new[el]), "")
                extra = ""
                if el == "EventSystem" and SEV.get(new[el], 0) >= 1 and self.stats:
                    ids = [obj_name_for_id(self.client.db, int(self.stats.get(k, 0)))
                           for k in ("EventSystemWarningID", "ObjectManagerCallbackID",
                                     "ObjectManagerQueueID")]
                    extra = f" [lastErrIDs ev={ids[0]} cb={ids[1]} q={ids[2]}]"
                line = f"{now_str()} {TILE[el]:7s} {old} -> {new[el]:12s} {why}{extra}"
                print(line, flush=True)
                if self.log:
                    self.log.write(json.dumps({"t": time.time(), "tile": TILE[el],
                                               "alarm": el, "from": old, "to": new[el],
                                               "why": why}) + "\n")
                    self.log.flush()
        self.alarms = new

    def summary(self, dur):
        print(f"\n--- {dur:.0f}s watch summary: {self.transitions} transitions ---")
        for el in ALARM_ELEMENTS:
            inc = self.incidence.get(el, {})
            total = sum(inc.values()) or 1.0
            parts = ", ".join(f"{st} {100 * v / total:.1f}%"
                              for st, v in sorted(inc.items(), key=lambda kv: -kv[1]))
            interesting = len(inc) > 1 or any(SEV.get(s, 0) >= 1 for s in inc)
            if interesting:
                print(f"  {TILE[el]:8s} {parts}")


def set_logging_metadata(client, name, mode, period_ms, timeout=5.0):
    objdef = client.db[name]
    meta_id = objdef.obj_id + 1
    client.meta_payloads.pop(meta_id, None)
    deadline = time.time() + timeout
    payload = None
    while time.time() < deadline:
        client.send_raw(uavtalk.TYPE_OBJ_REQ, meta_id)
        client.run(duration=0.3)
        payload = client.meta_payloads.get(meta_id)
        if payload is not None and len(payload) >= _META_STRUCT.size:
            break
    if payload is None or len(payload) < _META_STRUCT.size:
        print(f"WARN: no metadata reply for {name}")
        return False
    flags, tel_p, gcs_p, _ = _META_STRUCT.unpack(payload[:_META_STRUCT.size])
    flags = (flags & ~(0x3 << _UAVOBJ_LOGGING_SHIFT)) | (_LOGMODE[mode] << _UAVOBJ_LOGGING_SHIFT)
    client.send_raw(uavtalk.TYPE_OBJ, meta_id, 0,
                    _META_STRUCT.pack(flags, tel_p, gcs_p, period_ms & 0xFFFF))
    return True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--watch", type=float, default=None,
                    help="monitor for N seconds (0 = forever), print transitions")
    ap.add_argument("--log", default=None, help="append transitions to JSONL file")
    ap.add_argument("--enable-fclogs", action="store_true",
                    help="enable onboard DebugLog (Always) + alarm logging metadata")
    ap.add_argument("--host", default=HOST)
    args = ap.parse_args()

    db = uavtalk.UAVObjectDB(XML)
    client = UAVTalkClient(UdpTransport(args.host, PORT), db)
    mon = Monitor(client, args.log)

    if args.enable_fclogs:
        client.run(duration=2, on_object=mon.on_object)
        ok = 0
        for name, mode, period in (("SystemAlarms", "onchange", 0),
                                   ("FlightStatus", "onchange", 0),
                                   ("SystemStats", "periodic", 1000)):
            if set_logging_metadata(client, name, mode, period):
                ok += 1
        client.send_object("DebugLogSettings",
                           flight_config.resolve_enum_values(db["DebugLogSettings"],
                                                             {"LoggingEnabled": "Always"}),
                           msg_type=uavtalk.TYPE_OBJ_ACK)
        client.run(duration=0.5, on_object=mon.on_object)
        # persist so it survives firmware restarts
        client.send_object("ObjectPersistence",
                           flight_config.resolve_enum_values(
                               db["ObjectPersistence"],
                               {"Operation": "Save", "Selection": "SingleObject",
                                "ObjectID": db["DebugLogSettings"].obj_id, "InstanceID": 0}),
                           msg_type=uavtalk.TYPE_OBJ_ACK)
        client.run(duration=1, on_object=mon.on_object)
        print(f"onboard DebugLog enabled Always, {ok}/3 objects marked; "
              f"slots land in the firmware CWD (233CDC*.o*)")
        return

    # both modes need a first full sample
    deadline = time.time() + 20
    while time.time() < deadline and (not mon.alarms or not mon.stats):
        client.request_object("SystemAlarms")
        client.request_object("SystemStats")
        client.run(duration=1.0, on_object=mon.on_object)

    if not mon.alarms:
        print("FAILED: no SystemAlarms from the board")
        sys.exit(1)

    if args.watch is None:
        print(snapshot_table(mon.alarms, mon.stats))
        return

    print(snapshot_table(mon.alarms, mon.stats))
    print(f"\n--- watching (every tile transition prints; Ctrl-C to stop) ---")
    start = time.time()
    last_poll = 0.0
    try:
        while args.watch == 0 or (time.time() - start) < args.watch:
            if time.time() - last_poll > 0.5:
                client.request_object("SystemAlarms")
                if time.time() - last_poll > 2.0 or not mon.stats:
                    client.request_object("SystemStats")
                last_poll = time.time()
            client.run(duration=0.5, on_object=mon.on_object)
    except KeyboardInterrupt:
        pass
    mon.summary(time.time() - start)


if __name__ == "__main__":
    main()
