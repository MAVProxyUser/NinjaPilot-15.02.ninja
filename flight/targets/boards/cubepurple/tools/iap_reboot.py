#!/usr/bin/env python3
"""iap_reboot.py: reset a running Cube through FirmwareIAPObj (1122/2233/3344,
exactly what the GCS sends: the firmware comes straight back).  With --hold
the third step is 6677: the firmware leaves the ArduPilot bootloader's hold
signature and the bootloader waits for an uploader instead - what flash.sh
uses when a USB power cycle cannot reset the board (the CAN BEC back-feeds
the Cube's 5 V rail)."""
import sys, time
from hidlink import open_client

args = [a for a in sys.argv[1:] if not a.startswith("--")]
client = open_client(wait=float(args[0]) if args else 10); state = {}
def on_object(od, inst, dec):
    if od.name == "FirmwareIAPObj" and "iap" not in state: state["iap"] = dec
client.run(duration=3, on_object=on_object, on_connected=lambda: client.request_object("FirmwareIAPObj"))
iap = state.get("iap")
if not iap:
    print("no FirmwareIAPObj answer (is the firmware up and the GCS disconnected?)"); sys.exit(1)
# --hold: third step 6677 keeps the ArduPilot bootloader resident (uploader window)
hold = "--hold" in sys.argv
for cmd in (1122, 2233, 6677 if hold else 3344):
    iap["Command"] = cmd
    client.send_object("FirmwareIAPObj", iap)
    time.sleep(0.6)
print("IAP reset sent" + (" (bootloader hold)" if hold else ""))
