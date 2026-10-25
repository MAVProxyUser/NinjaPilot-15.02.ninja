#!/usr/bin/env python3
"""actuator_ramp.py: slow simultaneous spool of the motors through the
actuator path (ActuatorCommand in output-test mode, exactly what the GCS
Output tab and the wizard motor test do) while logging what the bus and the
ESCs report once a second.  Aborts on supply sag, ESC temperature, bus-off
or a climbing error counter.  NO PROPS.
usage: actuator_ramp.py [--top 1200] [--step 20] [--hold 3] [--minvolts 11.0] [--motors 4]"""
import sys, time, struct
from hidlink import open_client
import uavtalk

def opt(name, default):
    if name in sys.argv: return type(default)(sys.argv[sys.argv.index(name) + 1])
    return default
top = opt("--top", 1200); step = opt("--step", 20); hold = opt("--hold", 3.0); minvolts = opt("--minvolts", 11.0); motors = opt("--motors", 4)
client = open_client(); got = {}
S = {"prev": None, "vmin": 99.0, "amax": 0.0, "abort": None, "rpm_at": {}}
def on_object(od, inst, dec):
    if od.name in ("DroneCANESCStatus", "DroneCANStatus", "SystemStats", "SystemAlarms", "FlightStatus"): got[od.name] = dec
def run(d): client.run(duration=d, on_object=on_object)
client.run(duration=4, on_object=on_object, on_connected=lambda: [client.request_object(n) for n in ("DroneCANESCStatus", "DroneCANStatus", "SystemStats", "SystemAlarms", "FlightStatus")])
fs = got.get("FlightStatus")
if fs and fs["Armed"] != "Disarmed":
    print("board is %s: not running an output test on an armed board" % fs["Armed"]); sys.exit(1)
oid = client.db["ActuatorCommand"].obj_id; mid = oid + 1
client.send_raw(uavtalk.TYPE_OBJ_REQ, mid); run(1.0); meta = client.meta_payloads[mid]
flags = struct.unpack("<H", meta[:2])[0]
client.send_raw(uavtalk.TYPE_OBJ, mid, payload=struct.pack("<H", flags | 1) + meta[2:]); run(0.5)
print("output-test mode on (ActuatorCommand read-only for the flight side)")
cmd = {"Channel": [1000] * 12, "UpdateTime": 0, "MaxUpdateTime": 0, "NumFailedUpdates": 0}
def send(us):
    cmd["Channel"] = [us] * motors + [1000] * (12 - motors); client.send_object("ActuatorCommand", cmd)
def report(t, us):
    client.request_object("DroneCANStatus"); client.request_object("SystemStats"); client.request_object("SystemAlarms"); client.request_object("DroneCANESCStatus"); run(0.4)
    esc = got.get("DroneCANESCStatus"); st = got.get("DroneCANStatus"); ss = got.get("SystemStats"); al = got.get("SystemAlarms")
    rows = []; volts = []; amps = 0.0
    if esc:
        for i in range(8):
            if esc["NodeId"][i]:
                upd = esc["Updates"][i] - (S["prev"]["upd"][i] if S["prev"] else esc["Updates"][i])
                rows.append("m%d %.1fV %.2fA %5drpm %2dC e%d %2dHz" % (esc["Index"][i], esc["Voltage"][i], esc["Current"][i], esc["RPM"][i], esc["Temperature"][i], esc["ErrorCount"][i], upd))
                volts.append(esc["Voltage"][i]); amps += esc["Current"][i]
                if esc["RPM"][i] > 0: S["rpm_at"].setdefault(us, {})[esc["Index"][i]] = esc["RPM"][i]
                if esc["Temperature"][i] > 70 and not S["abort"]: S["abort"] = t; print("ABORT: ESC %d at %d C" % (esc["Index"][i], esc["Temperature"][i]))
    if volts:
        S["vmin"] = min(S["vmin"], min(volts)); S["amax"] = max(S["amax"], amps)
        if min(volts) < minvolts and not S["abort"]: S["abort"] = t; print("ABORT: supply sagged to %.2f V" % min(volts))
    bus = ""
    if st:
        p = S["prev"]; dt = (time.time() - p["at"]) if p else 1.0
        rx = (st["RxFrames"] - (p["rx"] if p else st["RxFrames"])) / dt; tx = (st["TxFrames"] - (p["tx"] if p else st["TxFrames"])) / dt
        busoff = st["BusOff"] not in (0, "False")
        bus = "bus rx %4.0f/s tx %4.0f/s drop %d/%d TEC %d REC %d%s" % (rx, tx, st["RxDropped"], st["TxDropped"], st["TxErrorCounter"], st["RxErrorCounter"], " BUSOFF" if busoff else "")
        if (busoff or st["TxErrorCounter"] > 96) and not S["abort"]: S["abort"] = t; print("ABORT: CAN errors")
    bad = {i: a for i, a in enumerate(al["Alarm"]) if a in ("Error", "Critical")} if al else {}; bad.pop(20, None)
    print("%5.1fs %4d us | %s | %s | cpu %s%% | %.2f A total%s" % (t, us, " | ".join(rows), bus, ss["CPULoad"] if ss else "?", amps, (" ALARMS %s" % bad) if bad else ""), flush=True)
    S["prev"] = {"upd": list(esc["Updates"]) if esc else [0] * 8, "rx": st["RxFrames"] if st else 0, "tx": st["TxFrames"] if st else 0, "at": time.time()}
t0 = time.time()
def phase(us, secs):
    end = time.time() + secs; nxt = 0
    while time.time() < end:
        send(us); run(0.5)
        if time.time() >= nxt: report(time.time() - t0, us); nxt = time.time() + 1.0
        if S["abort"]: return False
    return True
try:
    ok = phase(1000, 3.0)                       # ESCs hear FULLY_ARMED, arm on zero throttle
    levels = list(range(1000 + step, top + 1, step))
    for us in levels:
        if not ok: break
        print("-> %d us (%.0f%%)" % (us, (us - 1000) / 10.0)); ok = phase(us, hold)
    if ok: print("-> hold %d us" % top); ok = phase(top, 5.0)
    for us in reversed(levels[:-1]):
        send(us); run(0.4)
finally:
    phase(1000, 2.0)
    client.send_raw(uavtalk.TYPE_OBJ, mid, payload=meta); run(0.5); print("output-test mode off (metadata restored)")
st = got.get("DroneCANStatus")
print("summary: lowest ESC volts %.2f | highest total current %.2f A | rpm per level %s | bus rx %d tx %d rxdrop %d txdrop %d TEC %d REC %d busoff %s" % (S["vmin"], S["amax"], {k: sorted(v.items()) for k, v in sorted(S["rpm_at"].items())}, st["RxFrames"], st["TxFrames"], st["RxDropped"], st["TxDropped"], st["TxErrorCounter"], st["RxErrorCounter"], st["BusOff"]) if st else "summary: no bus status")
