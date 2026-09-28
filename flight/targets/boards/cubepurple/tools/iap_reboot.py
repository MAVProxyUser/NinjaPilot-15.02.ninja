#!/usr/bin/env python3
"""iap_reboot.py: reset a running Cube through FirmwareIAPObj (1122/2233/3344),
exactly what the GCS uploader sends.  The ArduPilot bootloader then waits
about five seconds for an uploader before restarting the firmware, which is
the window flash.sh uses when a USB power cycle cannot reset the board (the
CAN BEC back-feeds the Cube's 5 V rail).  Uses the tree's own pyuavtalk over
the board's HID interface (hidapi)."""
import os, sys, time, hid
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, "..", "..", "..", "..", ".."))
sys.path.insert(0, os.path.join(ROOT, "ground", "pyuavtalk"))
import uavtalk
from uavtalk_client import UAVTalkClient

VID, PID = 0x20A0, 0x415E

class HidTransport(object):
    """OpenPilot HID: 64-byte reports, id 2 out / 1 in, byte 1 = payload length."""
    def __init__(self, wait=10.0):
        t0 = time.time(); dev = None
        while time.time() - t0 < wait and not dev:
            devs = hid.enumerate(VID, PID)
            if devs: dev = devs[0]
            else: time.sleep(0.2)
        if not dev: raise RuntimeError("no HID device %04x:%04x" % (VID, PID))
        self.h = hid.device(); self.h.open_path(dev["path"]); self.h.set_nonblocking(False)
    def send(self, data):
        for i in range(0, len(data), 62):
            chunk = data[i:i + 62]
            self.h.write(bytes([2, len(chunk)]) + chunk + b"\0" * (62 - len(chunk)))
    def poll_recv(self, timeout):
        r = self.h.read(64, max(1, int(timeout * 1000)))
        if not r or len(r) < 2: return b""
        n = r[1]
        return bytes(r[2:2 + n])

db = uavtalk.UAVObjectDB(os.path.join(ROOT, "shared", "uavobjectdefinition"))
tr = HidTransport(wait=float(sys.argv[1]) if len(sys.argv) > 1 else 10); client = UAVTalkClient(tr, db); state = {}
def on_object(od, inst, dec):
    if od.name == "FirmwareIAPObj" and "iap" not in state: state["iap"] = dec
client.run(duration=3, on_object=on_object, on_connected=lambda: client.request_object("FirmwareIAPObj"))
iap = state.get("iap")
if not iap:
    print("no FirmwareIAPObj answer (is the firmware up and the GCS disconnected?)"); sys.exit(1)
for cmd in (1122, 2233, 3344):
    iap["Command"] = cmd
    client.send_object("FirmwareIAPObj", iap)
    time.sleep(0.6)
print("IAP reset sent")
