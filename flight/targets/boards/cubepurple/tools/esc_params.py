#!/usr/bin/env python3
"""esc_params.py: DroneCAN parameters of the AM32 ESCs through DroneCANParam.
The Vimdrones ESCs idle in their bootloader (node name AM32_BOOTLOADER_*, which
has no parameters) and only run the application while a RawCommand stream is
on the bus, so this tool keeps a zero-throttle stream going, waits for the
application nodes (com.vimdrones.esc_s50#Mn) and talks to those.
  esc_params.py nodes                     application nodes and their names
  esc_params.py NODE list                 every parameter of one application node
  esc_params.py NODE get NAME
  esc_params.py NODE set NAME VALUE       type taken from a preceding get
  esc_params.py NODE save                 ExecuteOpcode SAVE (persist in the ESC)
  esc_params.py 0 assign                  ESC_INDEX 0..3 by ascending node id, saved
NODE is an application node id from `nodes` (they change whenever an ESC restarts)."""
import sys, time
from hidlink import open_client

client = open_client(); got = {}; state = {"last": 0}
STREAM = {"Command": [0] * 8, "Count": 4, "Rate": 50, "Enabled": "True", "Arm": "True"}
def on_object(od, inst, dec):
    if od.name in ("DroneCANStatus", "DroneCANParam"): got[od.name] = dec
    if time.time() - state["last"] > 0.5:
        state["last"] = time.time(); client.send_object("DroneCANESCCommand", STREAM)
def run(d): client.run(duration=d, on_object=on_object)
def census():
    client.request_object("DroneCANStatus"); run(0.8); st = got["DroneCANStatus"]
    return [(st["NodeId"][i], st["NodeMode"][i]) for i in range(16) if st["NodeId"][i] and st["NodeLastSeen"][i] < 3]
def rpc(node, fields, timeout=2.5):
    req = {"NodeId": node, "Index": 0, "Name": [0] * 32, "ValueType": "Empty", "IntValue": 0, "RealValue": 0.0, "Op": "None",
           "Result": "Idle", "ResponseName": [0] * 32, "ResponseType": "Empty", "ResponseInt": 0, "ResponseReal": 0.0,
           "DefaultInt": 0, "DefaultReal": 0.0, "MinInt": 0, "MaxInt": 0, "RawLen": 0, "Raw": [0] * 64}
    req.update(fields); got.pop("DroneCANParam", None); client.send_object("DroneCANParam", req); t0 = time.time()
    while time.time() - t0 < timeout:
        run(0.2); p = got.get("DroneCANParam")
        if p and p["Result"] not in ("Idle", "Pending"): return p
    return got.get("DroneCANParam")
def name_bytes(s): b = s.encode()[:31]; return list(b) + [0] * (32 - len(b))
def name_str(a): return bytes(a).split(b"\0")[0].decode(errors="replace")
def fmt(p):
    t = p["ResponseType"]
    val = {"Integer": str(p["ResponseInt"]), "Real": "%g" % p["ResponseReal"], "Boolean": str(bool(p["ResponseInt"])), "String": "(string)", "Empty": "(empty)"}[t]
    rng = " [%d..%d]" % (p["MinInt"], p["MaxInt"]) if t in ("Integer", "Real") else ""
    return "%-22s = %-8s (%s, default %s%s)" % (name_str(p["ResponseName"]), val, t, p["DefaultInt"] if t != "Real" else "%g" % p["DefaultReal"], rng)
def wait_for_apps(seconds=10):
    t0 = time.time()
    while time.time() - t0 < seconds:
        apps = [n for n, m in census() if m == "Operational"]
        if len(apps) >= 4: return apps
    return apps
op = sys.argv[1] if len(sys.argv) > 1 else "nodes"
run(2.0); apps = wait_for_apps()
if op == "nodes":
    for n in apps:
        p = rpc(n, {"Op": "Info"})
        print("node %3d  %s  sw %d.%d" % (n, name_str(p["ResponseName"]), p["ResponseInt"] >> 8, p["ResponseInt"] & 255) if p and p["Result"] == "OK" else "node %3d  no answer" % n)
    sys.exit(0)
node = int(sys.argv[1]); op = sys.argv[2]; args = sys.argv[3:]
if node and node not in apps: print("node %d is not an application node right now (%s)" % (node, apps)); sys.exit(1)
if op == "list":
    for idx in range(0, 200):
        p = rpc(node, {"Index": idx, "Op": "Get"})
        if not p or p["Result"] != "OK": print("index %d: %s" % (idx, p["Result"] if p else "no answer")); break
        if not name_str(p["ResponseName"]): break
        print("%3d  %s" % (idx, fmt(p)))
elif op == "get":
    p = rpc(node, {"Name": name_bytes(args[0]), "Op": "Get"}); print(fmt(p) if p and p["Result"] == "OK" else p)
elif op == "set":
    p = rpc(node, {"Name": name_bytes(args[0]), "Op": "Get"})
    if not p or p["Result"] != "OK" or not name_str(p["ResponseName"]): print("cannot read %s first: %s" % (args[0], p and p["Result"])); sys.exit(1)
    t = p["ResponseType"]; f = {"Name": name_bytes(args[0]), "Op": "Set", "ValueType": t}
    if t == "Real": f["RealValue"] = float(args[1])
    else: f["IntValue"] = int(args[1])
    p = rpc(node, f); print(fmt(p) if p and p["Result"] == "OK" else p)
elif op == "save":
    p = rpc(node, {"Op": "Save"}); print("save:", "ok" if p and p["Result"] == "OK" and p["ResponseInt"] else p)
elif op == "assign":
    # ESC_INDEX 0..3 to the application nodes in ascending node-id order, saved; the
    # names then read #M1..#M4 and each RawCommand element drives one ESC
    for i, n in enumerate(sorted(apps)):
        p = rpc(n, {"Name": name_bytes("ESC_INDEX"), "Op": "Set", "ValueType": "Integer", "IntValue": i})
        ok = p and p["Result"] == "OK" and p["ResponseInt"] == i
        q = rpc(n, {"Op": "Save"}) if ok else None
        print("node %3d -> ESC_INDEX %d: %s, save %s" % (n, i, "ok" if ok else (p and p["Result"]), "ok" if q and q["Result"] == "OK" and q["ResponseInt"] else q and q["Result"]))
