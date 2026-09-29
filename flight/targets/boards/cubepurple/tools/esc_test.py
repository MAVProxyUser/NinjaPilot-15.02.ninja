#!/usr/bin/env python3
"""esc_test.py: spin DroneCAN ESCs one at a time through DroneCANESCCommand
and print what they report back (DroneCANESCStatus, by the esc_index each
ESC carries).  NO PROPS.  usage: esc_test.py [--throttle 700] [--seconds 4]
[--count 4] [motor indexes, default 0..count-1]"""
import sys, time
from hidlink import open_client

def opt(name, default):
    if name in sys.argv:
        return type(default)(sys.argv[sys.argv.index(name) + 1])
    return default
throttle = opt("--throttle", 700); seconds = opt("--seconds", 4); count = opt("--count", 4)
motors = [int(a) for a in sys.argv[1:] if a.isdigit()] or list(range(count))

client = open_client(); got = {}; state = {"t0": None, "step": -1, "last_send": 0, "last_print": 0, "mode": "str"}
def cmd(values, enabled):
    vals = list(values) + [0] * (8 - len(values))
    for mode in ((state["mode"], "int") if state["mode"] == "str" else ("int",)):
        try:
            client.send_object("DroneCANESCCommand", {"Command": vals, "Count": count, "Rate": 50,
                               "Enabled": ("True" if enabled else "False") if mode == "str" else (1 if enabled else 0)})
            state["mode"] = mode; return
        except Exception as e:
            if mode == "int": raise
def esc_table(esc):
    rows = []
    for i in range(8):
        if esc["Updates"][i]:
            rows.append("idx%d<-node%d %.1fV %.2fA %drpm %dC upd%d" % (i, esc["NodeId"][i], esc["Voltage"][i], esc["Current"][i], esc["RPM"][i], esc["Temperature"][i], esc["Updates"][i]))
    return " | ".join(rows) if rows else "(no esc.Status yet)"
# timeline: zeros for 3 s (arming), then each motor for `seconds`, then zeros 3 s, then disable
steps = [("zeros", None, 3.0)] + [("motor %d" % m, m, float(seconds)) for m in motors] + [("zeros", None, 3.0)]
def on_object(od, inst, dec):
    if od.name in ("DroneCANESCStatus", "DroneCANStatus"): got[od.name] = dec
    now = time.time()
    if state["t0"] is None:
        state["t0"] = now
    t = now - state["t0"]; acc = 0; cur = None
    for i, (name, m, dur) in enumerate(steps):
        if t < acc + dur: cur = i; break
        acc += dur
    if cur is None:
        if state["step"] != len(steps):
            cmd([0] * count, False); state["step"] = len(steps); print("%5.1fs  disabled" % t)
        return
    if cur != state["step"]:
        state["step"] = cur; state["last_send"] = 0
        print("%5.1fs  -> %s%s" % (t, steps[cur][0], "" if steps[cur][1] is None else " at %d/8191" % throttle))
    if now - state["last_send"] >= 0.5:
        state["last_send"] = now; m = steps[cur][1]
        cmd([throttle if (m is not None and i == m) else 0 for i in range(count)], True)
    if now - state["last_print"] >= 1.0 and "DroneCANESCStatus" in got:
        state["last_print"] = now; print("%5.1fs     %s" % (t, esc_table(got["DroneCANESCStatus"])))
total = sum(d for _, _, d in steps) + 3
client.run(duration=total, on_object=on_object, on_connected=lambda: [client.request_object(n) for n in ("DroneCANESCStatus", "DroneCANStatus")])
st = got.get("DroneCANStatus")
if st:
    print("bus: rx %d tx %d txdrop %d TEC %d | commands sent %d | nodes %d | data types %s" % (st["RxFrames"], st["TxFrames"], st["TxDropped"], st["TxErrorCounter"], st["CommandsSent"], st["NodeCount"], [(st["DataTypeId"][i], st["DataTypeCount"][i]) for i in range(8) if st["DataTypeCount"][i]]))
esc = got.get("DroneCANESCStatus")
if esc: print("final:", esc_table(esc))
