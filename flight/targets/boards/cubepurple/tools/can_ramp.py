#!/usr/bin/env python3
"""can_ramp.py: slow simultaneous spool of all DroneCAN ESCs through the
bench path (DroneCANESCCommand) while logging what the bus and the ESCs
report once a second: per-ESC volts/amps/rpm/temperature/errors/telemetry
rate, CAN frame rates, drops, error counters, bus-off, CPU load, alarms.
Aborts on supply sag, ESC temperature, bus-off or a climbing error counter.
NO PROPS.  usage: can_ramp.py [--top 1600] [--step 100] [--hold 3] [--rate 200]
[--minvolts 11.0] [--count 4]"""
import sys, time
from hidlink import open_client

def opt(name, default):
    if name in sys.argv: return type(default)(sys.argv[sys.argv.index(name) + 1])
    return default
top = opt("--top", 1600); step = opt("--step", 100); hold = opt("--hold", 3.0); rate = opt("--rate", 200)
minvolts = opt("--minvolts", 11.0); count = opt("--count", 4)
client = open_client(); got = {}; S = {"t0": None, "last_send": 0, "last_print": 0, "abort": None, "cmd": 0, "prev": None, "vmin": 99.0, "amax": 0.0, "mode": "str"}
def cmd(value, enabled):
    for mode in ((S["mode"], "int") if S["mode"] == "str" else ("int",)):
        try:
            flag = (lambda b: ("True" if b else "False")) if mode == "str" else (lambda b: 1 if b else 0)
            client.send_object("DroneCANESCCommand", {"Command": [value] * count + [0] * (8 - count), "Count": count, "Rate": rate, "Enabled": flag(enabled), "Arm": flag(enabled)})
            S["mode"] = mode; return
        except Exception:
            if mode == "int": raise
# timeline: zeros 8 s (ESC application start + arm), ramp up, hold top 5 s, ramp down fast, zeros 3 s
ramp = list(range(0, top + 1, step))
steps = [(0, 8.0)] + [(v, hold) for v in ramp[1:]] + [(top, 5.0)] + [(v, 0.5) for v in reversed(ramp[:-1])] + [(0, 3.0)]
def target(t):
    acc = 0
    for v, d in steps:
        if t < acc + d: return v
        acc += d
    return None
def on_object(od, inst, dec):
    if od.name in ("DroneCANESCStatus", "DroneCANStatus", "SystemStats", "SystemAlarms"): got[od.name] = dec
    now = time.time()
    if S["t0"] is None: S["t0"] = now
    t = now - S["t0"]; v = target(t)
    if S["abort"]: v = 0 if t - S["abort"] < 3 else None
    if v is None:
        if S["cmd"] != -1: cmd(0, False); S["cmd"] = -1; print("%5.1fs  disabled" % t)
        return
    if v != S["cmd"] or now - S["last_send"] >= 0.5:
        if v != S["cmd"]: print("%5.1fs  -> all %d motors at %d/8191 (%.0f%%)" % (t, count, v, 100.0 * v / 8191))
        S["cmd"] = v; S["last_send"] = now; cmd(v, True)
    if now - S["last_print"] >= 1.0 and "DroneCANESCStatus" in got:
        S["last_print"] = now
        client.request_object("DroneCANStatus"); client.request_object("SystemStats"); client.request_object("SystemAlarms")
        esc = got["DroneCANESCStatus"]; st = got.get("DroneCANStatus"); ss = got.get("SystemStats"); al = got.get("SystemAlarms")
        rows = []; volts = []; amps = 0.0
        for i in range(8):
            if esc["NodeId"][i]:
                upd = esc["Updates"][i] - (S["prev"]["upd"][i] if S["prev"] else esc["Updates"][i])
                rows.append("m%d %.1fV %.2fA %5drpm %2dC e%d %2dHz" % (esc["Index"][i], esc["Voltage"][i], esc["Current"][i], esc["RPM"][i], esc["Temperature"][i], esc["ErrorCount"][i], upd))
                volts.append(esc["Voltage"][i]); amps += esc["Current"][i]
                if esc["Temperature"][i] > 70 and not S["abort"]: S["abort"] = t; print("ABORT: ESC %d at %d C" % (esc["Index"][i], esc["Temperature"][i]))
        if volts:
            S["vmin"] = min(S["vmin"], min(volts)); S["amax"] = max(S["amax"], amps)
            if min(volts) < minvolts and not S["abort"]: S["abort"] = t; print("ABORT: supply sagged to %.2f V" % min(volts))
        bus = ""
        if st:
            p = S["prev"]
            rx = st["RxFrames"] - (p["rx"] if p else st["RxFrames"]); tx = st["TxFrames"] - (p["tx"] if p else st["TxFrames"])
            bus = "bus rx %4d/s tx %4d/s drop %d/%d TEC %d REC %d%s" % (rx, tx, st["RxDropped"], st["TxDropped"], st["TxErrorCounter"], st["RxErrorCounter"], " BUSOFF" if st["BusOff"] not in (0, "False") else "")
            if (st["BusOff"] not in (0, "False") or st["TxErrorCounter"] > 96) and not S["abort"]: S["abort"] = t; print("ABORT: CAN errors")
        cpu = " cpu %d%%" % ss["CPULoad"] if ss else ""
        bad = {i: a for i, a in enumerate(al["Alarm"]) if a in ("Error", "Critical")} if al else {}
        bad.pop(20, None)  # GPS is not part of this test
        print("%5.1fs  %s | %s%s | %.1fA total%s" % (t, " | ".join(rows), bus, cpu, amps, (" ALARMS %s" % bad) if bad else ""))
        S["prev"] = {"upd": list(esc["Updates"]), "rx": st["RxFrames"] if st else 0, "tx": st["TxFrames"] if st else 0}
total = sum(d for _, d in steps) + 4
client.run(duration=total, on_object=on_object, on_connected=lambda: [client.request_object(n) for n in ("DroneCANESCStatus", "DroneCANStatus", "SystemStats", "SystemAlarms")])
st = got.get("DroneCANStatus")
print("summary: lowest ESC volts %.2f | highest total current %.2f A | bus rx %d tx %d rxdrop %d txdrop %d TEC %d REC %d busoff %s | commands sent %d" % (S["vmin"], S["amax"], st["RxFrames"], st["TxFrames"], st["RxDropped"], st["TxDropped"], st["TxErrorCounter"], st["RxErrorCounter"], st["BusOff"], st["CommandsSent"]) if st else "summary: no bus status")
