#!/usr/bin/env python3
"""hwpage_check.py: drive the GCS (NINJAPILOT_GCS_AUTOMATION=1) through the
Cube hardware page: values match the board, a change saves both ways, the
page survives a disconnect/reconnect. Captures of the GCS window only land
in the current directory (gcs_shot.sh, window-id based)."""
import sys, os, time, json, subprocess
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "..", "..", "..", "..", "ground", "pyuavtalk"))
from gcs_client import GcsClient
S = os.getcwd()   # captures land here
TOOLS = HERE
c = GcsClient(); c.connect(retries=10)
def press(name, role="button"):
    for h in c.find(name=name, role=role, mx=20).get("hits", []):
        if c._cmd(cmd="do", path=h["path"], action="Press", window="NinjaPilotGCS").get("ok"): return True
    return False
def linked(): return bool(c.find(name="Disconnect", role="button", mx=3).get("hits"))
def open_hardware():
    c.workspace("Configuration"); time.sleep(1)
    for h in c.find(name="Hardware", mx=5).get("hits", []):
        if c._cmd(cmd="do", path=h["path"], action="Press", window="NinjaPilotGCS").get("ok"): break
    time.sleep(2)
def page():
    """the page's combos in layout order: TELEM1 fn, t1 telem speed, t1 com speed, TELEM2 fn, t2 telem, t2 com, GPS1 fn, g1 telem, g1 gps, g1 com, g1 proto, GPS2 fn, g2 telem, g2 gps, g2 com, g2 proto, RC IN, USB HID, USB VCP, VCP speed"""
    combos = c.find(role="combobox", mx=300).get("hits", []); names = [h.get("name") for h in combos]
    for i in range(len(names) - 19):
        if names[i + 16] in ("Disabled", "PWM") and names[i + 17] in ("USBTelemetry", "RCTransmitter", "Disabled") and names[i + 1] in ("2400", "4800", "9600", "19200", "38400", "57600", "115200"):
            return dict(zip(["TELEM1", "T1telem", "T1com", "TELEM2", "T2telem", "T2com", "GPS1", "G1telem", "G1gps", "G1com", "G1proto", "GPS2", "G2telem", "G2gps", "G2com", "G2proto", "RCIN", "USBHID", "USBVCP", "VCPspeed"], combos[i:i + 20]))
    return None
def shot(tag): print(subprocess.run([TOOLS + "/gcs_shot.sh", "%s/hwpage_%s.png" % (S, tag)], capture_output=True, text=True).stdout.strip())
print("linked:", linked()); open_hardware(); p = page()
assert p, "hardware page combos not found"
vals = {k: v.get("name") for k, v in p.items()}
print("page:", {k: vals[k] for k in ("TELEM1", "TELEM2", "GPS1", "GPS2", "RCIN", "USBHID", "USBVCP")}, "| speeds", vals["T1telem"], vals["G2gps"], vals["G2proto"])
if os.path.exists(S + "/hw_board.json"):   # optional: a HwSettings dump taken over HID before the GCS linked
    board = json.load(open(S + "/hw_board.json"))
    print("board (before this run):", {k: board[k] for k in ("RV_TelemetryPort", "RV_AuxPort", "RV_GPSPort", "CUBE_GPS2Port", "RV_RcvrPort", "USB_HIDPort", "USB_VCPPort")})
shot("1_asfound")
# round trip: TELEM1 to ComBridge and back, each saved, so the Save path is exercised both ways
orig = vals["TELEM1"]; other = "ComBridge" if orig != "ComBridge" else "Telemetry"
print("TELEM1 -> %s:" % other, c.set(p["TELEM1"]["path"], other).get("ok"), "| Save pressed:", press("Save")); time.sleep(4)
print("TELEM1 -> %s:" % orig, c.set(p["TELEM1"]["path"], orig).get("ok"), "| Save pressed:", press("Save")); time.sleep(4)
# reconnect cycle: the page must come back, with the saved value
print("Disconnect:", press("Disconnect")); time.sleep(3); print("Connect:", press("Connect")); time.sleep(6); print("linked again:", linked())
open_hardware(); p2 = page(); print("page after reconnect:", "present" if p2 else "MISSING", "| TELEM1 reads", p2 and p2["TELEM1"].get("name"), "(expected %s)" % orig)
shot("2_after_reconnect")
press("Disconnect"); time.sleep(2)
