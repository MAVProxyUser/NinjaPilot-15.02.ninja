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
positional = [a for i, a in enumerate(sys.argv[1:]) if a.isdigit() and not sys.argv[i].startswith("--")]
motors = [int(a) for a in positional] or list(range(count))

client = open_client(); got = {}; state = {"t0": None, "step": -1, "last_send": 0, "last_print": 0, "mode": "str"}
def cmd(values, enabled):
    vals = list(values) + [0] * (8 - len(values))
    for mode in ((state["mode"], "int") if state["mode"] == "str" else ("int",)):
        try:
            flag = (lambda b: ("True" if b else "False")) if mode == "str" else (lambda b: 1 if b else 0)
            client.send_object("DroneCANESCCommand", {"Command": vals, "Count": count, "Rate": 50,
                               "Enabled": flag(enabled), "Arm": flag(enabled)})
            state["mode"] = mode; return
        except Exception as e:
            if mode == "int": raise
def esc_table(esc):
    rows = []
    for i in range(8):
        if esc["NodeId"][i]:
            rows.append("node%d[idx%d] %.1fV %.2fA %drpm %d%% %dC err%d" % (esc["NodeId"][i], esc["Index"][i], esc["Voltage"][i], esc["Current"][i], esc["RPM"][i], esc["PowerPct"][i], esc["Temperature"][i], esc["ErrorCount"][i]))
    return " | ".join(rows) if rows else "(no esc.Status yet)"
# timeline: zeros for 3 s (arming), then each motor for `seconds`, then zeros 3 s, then disable
# The AM32 application only starts about 3 s into the stream (the ESCs idle in
# their bootloader) and then wants a second of zero throttle before it arms,
# so the first zeros phase is long.
steps = [("zeros (ESCs start their application and arm)", None, 8.0)] + [("motor %d" % m, m, float(seconds)) for m in motors] + [("zeros", None, 3.0)]
def on_object(od, inst, dec):
    if od.name in ("DroneCANESCStatus", "DroneCANStatus"): got[od.name] = dec
    if od.name == "DroneCANStatus" and time.time() - state.get("last_req", 0) > 1.0:
        state["last_req"] = time.time(); client.request_object("DroneCANStatus")
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
        st = got.get("DroneCANStatus")
        modes = " | nodes: " + ", ".join("%d %s" % (st["NodeId"][i], st["NodeMode"][i]) for i in range(16) if st["NodeId"][i]) if st else ""
        print("%5.1fs  -> %s%s%s" % (t, steps[cur][0], "" if steps[cur][1] is None else " at %d/8191" % throttle, modes))
    if now - state["last_send"] >= 0.5:
        state["last_send"] = now; m = steps[cur][1]
        cmd([throttle if (m is not None and i == m) else 0 for i in range(count)], True)
    if now - state["last_print"] >= 1.0 and "DroneCANESCStatus" in got:
        state["last_print"] = now; print("%5.1fs     %s" % (t, esc_table(got["DroneCANESCStatus"])))
total = sum(d for _, _, d in steps) + 3
client.run(duration=total, on_object=on_object, on_connected=lambda: [client.request_object(n) for n in ("DroneCANESCStatus", "DroneCANStatus")])
st = got.get("DroneCANStatus")
if st:
    print("bus: rx %d tx %d txdrop %d TEC %d REC %d | commands sent %d | nodes %d | data types %s" % (st["RxFrames"], st["TxFrames"], st["TxDropped"], st["TxErrorCounter"], st["RxErrorCounter"], st["CommandsSent"], st["NodeCount"], [(st["DataTypeId"][i], st["DataTypeCount"][i]) for i in range(8) if st["DataTypeCount"][i]]))
esc = got.get("DroneCANESCStatus")
if esc: print("final:", esc_table(esc))
