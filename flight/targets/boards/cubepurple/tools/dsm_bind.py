#!/usr/bin/env python3
"""dsm_bind.py: bind a Spektrum satellite plugged into the Cube's SPKT/DSM port.
The IO co-processor does the work (power-cycle the satellite, nine bind
pulses) when the firmware boots with HwSettings.DSMxBind set, so this tool
sets it, reboots the board, waits, clears it again and reports what the
receiver delivers.  Put the transmitter into bind mode BEFORE the reboot
(the satellite's bind window opens a few seconds after reset).
usage: dsm_bind.py [--now]     (--now skips the "press Enter" prompt)"""
import sys, time, subprocess
from hidlink import open_client
def hw(client, got, **fields):
    h = got["HwSettings"]; h.update(fields); client.send_object("HwSettings", h); client.run(duration=0.8)
    client.send_object("ObjectPersistence", {"Operation": "Save", "Selection": "SingleObject", "ObjectID": client.db["HwSettings"].obj_id, "InstanceID": 0}); client.run(duration=1.5)
got = {}
def on_object(od, inst, dec):
    if od.name in ("HwSettings", "ManualControlCommand", "ReceiverActivity", "SystemAlarms"): got[od.name] = dec
client = open_client(wait=30); client.run(duration=3, on_object=on_object, on_connected=lambda: client.request_object("HwSettings"))
hw(client, got, DSMxBind=1); client.transport.h.close(); del client
if "--now" not in sys.argv:
    input("Transmitter in bind mode?  Press Enter to reboot the board and bind the satellite... ")
print("rebooting; the satellite should start blinking fast within ~5 s"); subprocess.run([sys.executable, "iap_reboot.py"], capture_output=True); time.sleep(25)
client = open_client(wait=30); client.run(duration=3, on_object=on_object, on_connected=lambda: [client.request_object(n) for n in ("HwSettings", "ManualControlCommand", "SystemAlarms")])
hw(client, got, DSMxBind=0); print("bind request cleared and saved")
for i in range(6):
    client.request_object("ManualControlCommand"); client.run(duration=1.5, on_object=on_object); m = got.get("ManualControlCommand", {})
    print("  receiver connected %s | channels %s" % (m.get("Connected"), m.get("Channel", [])[:8]))
    if m.get("Connected") == "True": break
