#!/usr/bin/env python3
"""End-to-end mixer test: configure Mixer7 as Servo over UAVTalk and sweep
ChannelNeutral[6] - the disarmed failsafe path then drives OUT6 (pin 33)."""
import sys, time
sys.path.insert(0, "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/ground/pyuavtalk")
import uavtalk
from uavtalk_client import UAVTalkClient, UdpTransport

XML = "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/shared/uavobjectdefinition"
db = uavtalk.UAVObjectDB(XML)
client = UAVTalkClient(UdpTransport("192.168.0.90", 9000), db)

state = {"mixer": None, "act": None, "phase": "fetch"}

def on_object(objdef, inst, decoded):
    if objdef.name == "MixerSettings" and state["mixer"] is None:
        state["mixer"] = decoded
        print("[got] MixerSettings (Mixer7Type=%s)" % decoded.get("Mixer7Type"))
    if objdef.name == "ActuatorSettings" and state["act"] is None:
        state["act"] = decoded
        print("[got] ActuatorSettings neutral[6]=%s" % decoded["ChannelNeutral"][6])

def on_connected():
    print("[link] requesting settings")
    client.request_object("MixerSettings")
    client.request_object("ActuatorSettings")

client.run(duration=8, on_object=on_object, on_connected=on_connected)
if not (state["mixer"] and state["act"]):
    print("FAILED to fetch settings"); sys.exit(1)

mix = dict(state["mixer"]); act = dict(state["act"])
mix["Mixer7Type"] = "Servo"
act["ChannelMin"] = list(act["ChannelMin"]); act["ChannelMin"][6] = 1000
act["ChannelMax"] = list(act["ChannelMax"]); act["ChannelMax"][6] = 2000
act["ChannelNeutral"] = list(act["ChannelNeutral"]); act["ChannelNeutral"][6] = 1500

client.send_object("MixerSettings", mix, msg_type=uavtalk.TYPE_OBJ_ACK)
client.send_object("ActuatorSettings", act, msg_type=uavtalk.TYPE_OBJ_ACK)
print("[sent] Mixer7Type=Servo, neutral[6]=1500 - center")
client.run(duration=3, on_object=lambda *a: None)

for target in (1100, 1900, 1500, 1100, 1900, 1500):
    act["ChannelNeutral"][6] = target
    client.send_object("ActuatorSettings", act, msg_type=uavtalk.TYPE_OBJ_ACK)
    print("[sweep] neutral[6] -> %d us" % target)
    client.run(duration=2.0, on_object=lambda *a: None)

print("done - servo parked at 1500 via the MIXER path")
