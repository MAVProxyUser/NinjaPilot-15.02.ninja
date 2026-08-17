#!/usr/bin/env python3
"""Persist ManualControlSettings with the GCS receiver group so the INPUT
health tile responds to GCS Control / joystick input (GCSReceiver over
UAVTalk). Saves via ObjectPersistence and verifies by readback."""
import sys, time
sys.path.insert(0, "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/ground/pyuavtalk")
import uavtalk
from uavtalk_client import UAVTalkClient, UdpTransport

XML = "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/shared/uavobjectdefinition"
db = uavtalk.UAVObjectDB(XML)
client = UAVTalkClient(UdpTransport("192.168.0.90", 9000), db)

MCS = {
    "ChannelGroups": [5, 5, 5, 5, 5, 7, 7, 7, 7],   # GCS on Thr/Roll/Pitch/Yaw/Mode
    "ChannelNumber": [1, 2, 3, 4, 5, 0, 0, 0, 0],
    "ChannelMin": [1000] * 9,
    "ChannelNeutral": [1050, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500],
    "ChannelMax": [2000] * 9,
    "ResponseTime": [0] * 7, "Deadband": 0.02, "DeadbandAssistedControl": 0.08,
    "FlightModeNumber": 5, "FailsafeFlightModeSwitchPosition": -1,
    "FailsafeChannel": [-1, 0, 0, 0, 0, 0, 0, 0],
}

state = {}
def grab(objdef, inst, d):
    state[objdef.name] = d

client.run(duration=3, on_object=grab)
client.send_object("ManualControlSettings", MCS, msg_type=uavtalk.TYPE_OBJ_ACK)
client.run(duration=1, on_object=grab)

mcs_id = db["ManualControlSettings"].obj_id
client.send_object("ObjectPersistence", {
    "Operation": "Save", "Selection": "SingleObject",
    "ObjectID": mcs_id, "InstanceID": 0,
}, msg_type=uavtalk.TYPE_OBJ_ACK)
client.run(duration=2, on_object=grab)

state.pop("ManualControlSettings", None)
client.request_object("ManualControlSettings")
deadline = time.time() + 10
while time.time() < deadline and "ManualControlSettings" not in state:
    client.run(duration=1, on_object=grab)

rb = state.get("ManualControlSettings")
if not rb:
    print("FAILED: no readback"); sys.exit(1)
print("readback ChannelGroups:", rb["ChannelGroups"])
print("readback ChannelNumber:", rb["ChannelNumber"])
op = state.get("ObjectPersistence")
print("ObjectPersistence state:", op.get("Operation") if op else "(not seen)")
