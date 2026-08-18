#!/usr/bin/env python3
"""Configure + verify PPM-over-UDP stick input end to end.

1. RMW ManualControlSettings -> PPM group on Thr/Roll/Pitch/Yaw/FlightMode,
   persist onboard.
2. RMW FlightModeSettings.Arming -> Yaw Right, persist.
3. Walk the link-health matrix with udp_sticks.py as a subprocess:
      no stream        -> INPUT Warning (never-active baseline)
      clean 50 Hz      -> INPUT OK (green), Connected
      60% loss         -> INPUT Warning (orange) while still connected
      stream stopped   -> INPUT Error (red)
      stream restored  -> OK again, then arm gesture -> Armed -> disarm.

Run on the bench Mac. One UAVTalk client (this) on :9000; sticks on :9003.
"""
import subprocess
import sys
import time

sys.path.insert(0, "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/ground/pyuavtalk")
import uavtalk  # noqa: E402
from uavtalk_client import UAVTalkClient, UdpTransport  # noqa: E402

TARGET = sys.argv[1] if len(sys.argv) > 1 else "192.168.0.14"
XML = "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/shared/uavobjectdefinition"
STICKS = "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/ground/pyuavtalk/udp_sticks.py"

db = uavtalk.UAVObjectDB(XML)
client = UAVTalkClient(UdpTransport(TARGET, 9000), db)
state = {}


def grab(objdef, inst, d):
    state[objdef.name] = d


def fetch(name, timeout=8):
    state.pop(name, None)
    client.request_object(name)
    deadline = time.time() + timeout
    while time.time() < deadline and name not in state:
        client.run(duration=0.5, on_object=grab)
    return state.get(name)


def persist(name):
    client.send_object("ObjectPersistence", {
        "Operation": "Save", "Selection": "SingleObject",
        "ObjectID": db[name].obj_id, "InstanceID": 0,
    }, msg_type=uavtalk.TYPE_OBJ_ACK)
    client.run(duration=2, on_object=grab)


def sticks(*args):
    return subprocess.Popen([sys.executable, STICKS, "--target", TARGET] + list(args),
                            stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)


# element order matches systemalarms.xml (same list health_monitor.py uses)
RECEIVER_IDX = 7  # ["SystemConfiguration","BootFault","OutOfMemory","StackOverflow",
                  #  "CPUOverload","EventSystem","Telemetry","Receiver",...]


def receiver_alarm():
    a = fetch("SystemAlarms")
    return a["Alarm"][RECEIVER_IDX] if a else None


results = []


def check(label, want, got):
    ok = (want == got)
    results.append((label, want, got, ok))
    print(f"  [{'PASS' if ok else 'FAIL'}] {label}: want {want}, got {got}")


print(f"== configuring against {TARGET} ==")
client.run(duration=2, on_object=grab)

mcs = fetch("ManualControlSettings")
if not mcs:
    sys.exit("no ManualControlSettings readback - is the firmware up?")
mcs["ChannelGroups"] = ["PPM", "PPM", "PPM", "PPM", "PPM",
                        "None", "None", "None", "None"]
mcs["ChannelNumber"] = [1, 2, 3, 4, 5, 0, 0, 0, 0]
mcs["ChannelMin"] = [1000] * 9
mcs["ChannelNeutral"] = [1025, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500]
mcs["ChannelMax"] = [2000] * 9
client.send_object("ManualControlSettings", mcs, msg_type=uavtalk.TYPE_OBJ_ACK)
client.run(duration=1, on_object=grab)
persist("ManualControlSettings")
rb = fetch("ManualControlSettings")
print("ChannelGroups readback:", rb["ChannelGroups"][:5] if rb else "NONE")

fms = fetch("FlightModeSettings")
if fms:
    fms["Arming"] = "Yaw Right"
    client.send_object("FlightModeSettings", fms, msg_type=uavtalk.TYPE_OBJ_ACK)
    client.run(duration=1, on_object=grab)
    persist("FlightModeSettings")
    rb = fetch("FlightModeSettings")
    print("Arming readback:", rb["Arming"] if rb else "NONE")

print("== link-health matrix ==")
time.sleep(1)
check("baseline (no stream)", "Warning", receiver_alarm())

p = sticks("--center")
time.sleep(4)
check("clean stream -> green", "OK", receiver_alarm())
mcc = fetch("ManualControlCommand")
check("connected", "True", str(mcc["Connected"]) if mcc else None)
p.terminate(); p.wait()

p = sticks("--center", "--lossy", "60")
time.sleep(5)
check("60% loss -> orange", "Warning", receiver_alarm())
p.terminate(); p.wait()

time.sleep(4)
check("stream dead -> red", "Error", receiver_alarm())

p = sticks("--arm")
time.sleep(4)
check("restored -> green", "OK", receiver_alarm())
time.sleep(4)   # arm gesture window is 2-5s into the sender's life
fs = fetch("FlightStatus")
check("armed via UDP yaw-right", "Armed", fs["Armed"] if fs else None)
p.terminate(); p.wait()

# disarm: throttle low + yaw LEFT via a short inline stream
import socket, struct  # noqa: E402
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
for i in range(150):  # 3s at 50Hz
    ch = [1000, 1500, 1500, 1050, 1000]
    pkt = b"PPM1" + struct.pack("<BB", i & 0xFF, 5) + struct.pack("<5H", *ch)
    s.sendto(pkt, (TARGET, 9003))
    time.sleep(0.02)
s.close()
fs = fetch("FlightStatus")
check("disarmed via yaw-left", "Disarmed", fs["Armed"] if fs else None)

print("== GPS object enrichment ==")
sat = fetch("GPSSatellites")
print("GPSSatellites.SatsInView:", sat["SatsInView"] if sat else "(no readback)")
gt = fetch("GPSTime")
print("GPSTime:", (f"{gt['Year']}-{gt['Month']:02d}-{gt['Day']:02d} "
                   f"{gt['Hour']:02d}:{gt['Minute']:02d}:{gt['Second']:02d}") if gt else "(no readback)")
ext = fetch("GPSExtendedStatus")
if ext:
    tag = bytes(b for b in ext["FirmwareTag"] if b).decode("ascii", "replace")
    print("GPSExtendedStatus.FirmwareTag:", repr(tag), "BoardType:", ext["BoardType"])

print("== summary ==")
fails = [r for r in results if not r[3]]
for label, want, got, ok in results:
    print(f"  {'PASS' if ok else 'FAIL'}  {label}")
print(f"{len(results) - len(fails)}/{len(results)} passed")
sys.exit(1 if fails else 0)
