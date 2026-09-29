"""hidlink.py: the tree's own pyuavtalk over the Cube's HID interface (hidapi).
open_client() returns a connected-on-demand UAVTalkClient for the tools here."""
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

def open_client(wait=10.0):
    db = uavtalk.UAVObjectDB(os.path.join(ROOT, "shared", "uavobjectdefinition"))
    return UAVTalkClient(HidTransport(wait=wait), db)
