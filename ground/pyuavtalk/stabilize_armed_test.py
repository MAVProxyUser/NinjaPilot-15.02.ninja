#!/usr/bin/env python3
"""Armed stabilize demo: GCS receiver stream (throttle low) + Always Armed,
Mixer7 = Servo slaved to roll. Rotate the IMU -> the servo on pin 33 chases."""
import sys, time
sys.path.insert(0, "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/ground/pyuavtalk")
import uavtalk
from uavtalk_client import UAVTalkClient, UdpTransport

XML = "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/shared/uavobjectdefinition"
db = uavtalk.UAVObjectDB(XML)
client = UAVTalkClient(UdpTransport("192.168.0.90", 9000), db)

state = {}
def grab(objdef, inst, d):
    state.setdefault(objdef.name, d)
def on_connected():
    for w in ("MixerSettings", "ActuatorSettings", "FlightModeSettings"):
        client.request_object(w)
deadline = time.time() + 25
client.run(duration=5, on_object=grab, on_connected=on_connected)
while time.time() < deadline and not all(w in state for w in ("MixerSettings", "ActuatorSettings", "FlightModeSettings")):
    for w in ("MixerSettings", "ActuatorSettings", "FlightModeSettings"):
        if w not in state:
            client.request_object(w)
    client.run(duration=2, on_object=grab)
for w in ("MixerSettings", "ActuatorSettings", "FlightModeSettings"):
    if w not in state:
        print("FAILED to fetch", w); sys.exit(1)

# receiver mapping: GCS group on channels 1-5 = Throttle/Roll/Pitch/Yaw/Mode
client.send_object("ManualControlSettings", {
    "ChannelGroups": [5, 5, 5, 5, 5, 7, 7, 7, 7],
    "ChannelNumber": [1, 2, 3, 4, 5, 0, 0, 0, 0],
    "ChannelMin": [1000] * 9,
    "ChannelNeutral": [1050, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500],
    "ChannelMax": [2000] * 9,
    "ResponseTime": [0] * 7, "Deadband": 0.02, "DeadbandAssistedControl": 0.08,
    "FlightModeNumber": 5, "FailsafeFlightModeSwitchPosition": -1,
    "FailsafeChannel": [-1, 0, 0, 0, 0, 0, 0, 0],
}, msg_type=uavtalk.TYPE_OBJ_ACK)

mix = dict(state["MixerSettings"]); act = dict(state["ActuatorSettings"]); fms = dict(state["FlightModeSettings"])
mix["Mixer7Type"] = "Servo"
vec = list(mix["Mixer7Vector"]); vec[2] = 127; mix["Mixer7Vector"] = vec
act["ChannelMin"] = list(act["ChannelMin"]); act["ChannelMin"][6] = 1000
act["ChannelMax"] = list(act["ChannelMax"]); act["ChannelMax"][6] = 2000
act["ChannelNeutral"] = list(act["ChannelNeutral"]); act["ChannelNeutral"][6] = 1500
act["LowThrottleZeroAxis"] = ["FALSE", "FALSE", "FALSE"]
fms["Arming"] = "Always Armed"
for bank in ("Stabilization1Settings", "Stabilization2Settings", "Stabilization3Settings"):
    st = list(fms[bank]); st[0] = "Attitude"; st[1] = "Attitude"; st[2] = "AxisLock"
    fms[bank] = st
client.send_object("MixerSettings", mix, msg_type=uavtalk.TYPE_OBJ_ACK)
client.send_object("ActuatorSettings", act, msg_type=uavtalk.TYPE_OBJ_ACK)
client.send_object("FlightModeSettings", fms, msg_type=uavtalk.TYPE_OBJ_ACK)
print("[sent] receiver map + Mixer7=Servo(roll) + Always Armed")

nch = None
for f in db["GCSReceiver"].fields:
    if f.name == "Channel":
        nch = f.count
rx = [1000, 1500, 1500, 1500, 1500] + [1500] * (nch - 5)   # throttle LOW, sticks centered

last = {"t": 0}
def watch(objdef, inst, d):
    if objdef.name == "FlightStatus" and time.time() - last["t"] > 0.9:
        print("[status] Armed=%s" % d["Armed"])
    if objdef.name == "AttitudeState" and time.time() - last["t"] > 0.9:
        last["t"] = time.time()
        print("[att] roll %+7.2f pitch %+7.2f" % (d["Roll"], d["Pitch"]))
    if objdef.name == "ActuatorCommand" and time.time() - last["t"] > 0.9:
        print("[out] ch6 = %d us" % d["Channel"][6])
    if objdef.name == "StabilizationDesired":
        print("[stabdes] roll %+6.1f thrust %+5.2f modes %s" % (d["Roll"], d["Thrust"], d["StabilizationMode"][:2]))
    if objdef.name == "ActuatorDesired":
        print("[actdes] roll %+6.3f thrust %+5.2f" % (d["Roll"], d["Thrust"]))

# force a flight-mode TRANSITION so the stabilized-bank settings re-latch
# (they are only re-read on mode change - the StabilizationBank-mirror family)
for chan5 in (2000, 1000):
    t0 = time.time()
    while time.time() - t0 < 2:
        client.send_object("GCSReceiver", {"Channel": [1000, 1500, 1500, 1500, chan5] + [1500] * (nch - 5)})
        client.run(duration=0.04, on_object=lambda *a: None)
print("[stream] GCSReceiver at 25 Hz - ROTATE THE IMU NOW")
t0 = time.time(); nreq = 0
while time.time() - t0 < 40:
    client.send_object("GCSReceiver", {"Channel": rx})
    if nreq % 12 == 0:
        client.request_object("FlightStatus")
        client.request_object("AttitudeState")
        client.request_object("ActuatorCommand")
        client.request_object("StabilizationDesired")
        client.request_object("ActuatorDesired")
    nreq += 1
    client.run(duration=0.04, on_object=watch)
print("done - reverting arming")
fms["Arming"] = "Always Disarmed"
client.send_object("FlightModeSettings", fms, msg_type=uavtalk.TYPE_OBJ_ACK)
client.run(duration=2, on_object=lambda *a: None)
