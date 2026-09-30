#!/usr/bin/env python3
"""esc_flash.py: load new firmware into a DroneCAN ESC through the flight
controller.  The flight side sends BeginFirmwareUpdate, the ESC reboots into
its bootloader and reads the image back from the flight controller 256 bytes
at a time (uavcan.protocol.file.Read); every read shows up here as
DroneCANFileRequest and this tool answers it with DroneCANFileChunk objects.
A read shorter than 256 bytes ends the update; the bootloader checks the
image signature before it jumps.  The GCS must be disconnected (HID).

usage: esc_flash.py IMAGE.bin --node N        one ESC
       esc_flash.py IMAGE.bin --all           every ESC reporting esc.Status, one after the other
NO PROPS, DISARMED.  Bench power on (the ESCs must be up)."""
import sys, os, time
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from hidlink import open_client
import uavtalk

def opt(name):
    return sys.argv[sys.argv.index(name) + 1] if name in sys.argv else None
image = open(sys.argv[1], "rb").read()
client = open_client(); st = {}
def grab(od, inst, d): st[od.name] = d
def run(d): client.run(duration=d, on_object=grab)
def fetch(name, secs=5):
    st.pop(name, None); client.request_object(name); t = time.time() + secs
    while time.time() < t and name not in st: run(0.3)
    return st.get(name)

def flash(node):
    print("node %d: %d bytes" % (node, len(image)))
    client.send_object("DroneCANUpdate", {"NodeId": node, "ImageSize": len(image), "Command": "Begin", "State": "Idle", "Offset": 0, "Reads": 0}, msg_type=uavtalk.TYPE_OBJ_ACK)
    t0 = time.time(); last_seq = None; last_pct = -1; state = "?"
    while time.time() - t0 < 180:
        run(0.05)
        u = st.get("DroneCANUpdate")
        if u:
            state = u["State"]
            if state in ("Done", "Failed", "Refused"): break
        r = st.get("DroneCANFileRequest")
        if r and r["Seq"] != last_seq:
            last_seq = r["Seq"]; off = r["Offset"]; ln = r["Length"]
            for o in range(off, off + ln, 128):
                piece = image[o:min(o + 128, off + ln)]
                client.send_object("DroneCANFileChunk", {"Seq": r["Seq"], "Offset": o, "Length": len(piece), "Data": list(piece) + [0] * (128 - len(piece))})
            pct = 100 * (off + ln) // len(image)
            if pct // 10 != last_pct // 10: print("   %3d%%  (offset %d, read #%d)" % (pct, off, r["Seq"]), flush=True); last_pct = pct
    print("node %d: %s after %.1f s" % (node, state, time.time() - t0))
    return state == "Done"

run(3)
if "--all" in sys.argv:
    e = fetch("DroneCANESCStatus"); nodes = sorted(set(e["NodeId"][i] for i in range(8) if e["NodeId"][i])) if e else []
    print("ESC nodes:", nodes)
else:
    nodes = [int(opt("--node"))]
ok = 0
for n in nodes:
    if flash(n):
        ok += 1
        # the ESC reboots, redoes its node id and comes back with esc.Status
        t = time.time(); back = False
        while time.time() - t < 20 and not back:
            client.request_object("DroneCANStatus"); run(1.0); s = st.get("DroneCANStatus")
            back = bool(s and any(s["NodeId"][i] and s["NodeMode"][i] == "Operational" and s["NodeLastSeen"][i] < 2 for i in range(16)))
        print("   application back on the bus: %s (%.0f s)" % (back, time.time() - t))
print("%d of %d updated" % (ok, len(nodes)))
