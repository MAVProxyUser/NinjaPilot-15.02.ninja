#!/usr/bin/env python3
"""Upload a small demo flight plan so PLAN goes orange -> green.

A 5-waypoint square (15 m sides, 30 m AGL, NED relative to HomeLocation)
sent exactly the way the GCS does it: multi-instance Waypoint/PathAction
objects, then PathPlan carrying the counts + CRC-8 (poly 0x07) that the
FLIGHT side recomputes in pathplanner.c's checkPathPlan(). The PLAN tile
goes green only when the firmware itself validates the upload.

NOTE: plans are RAM-ONLY UAVObjects - a firmware restart wipes them and
PLAN returns to orange. Nothing lands on the filesystem.

Usage: python3 upload_demo_plan.py [board-ip]
"""
import sys
import time

sys.path.insert(0, "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/ground/pyuavtalk")
import uavtalk  # noqa: E402
import flight_config  # noqa: E402
from uavtalk_client import UAVTalkClient, UdpTransport  # noqa: E402

TARGET = sys.argv[1] if len(sys.argv) > 1 else "192.168.0.14"
XML = "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/shared/uavobjectdefinition"

ALARM_ELEMENTS = ["SystemConfiguration", "BootFault", "OutOfMemory", "StackOverflow",
                  "CPUOverload", "EventSystem", "Telemetry", "Receiver", "ManualControl",
                  "Actuator", "Attitude", "Sensors", "Magnetometer", "Airspeed",
                  "Stabilization", "Guidance", "PathPlan", "Battery", "FlightTime",
                  "I2C", "GPS"]
PLAN_IDX = ALARM_ELEMENTS.index("PathPlan")


def crc8_07(crc, data):
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = ((crc << 1) ^ 0x07) & 0xFF if (crc & 0x80) else (crc << 1) & 0xFF
    return crc


db = uavtalk.UAVObjectDB(XML)
client = UAVTalkClient(UdpTransport(TARGET, 9000), db)
state = {}


def grab(o, i, d):
    state[o.name] = d


client.run(duration=2, on_object=grab)

# one FollowVector action, confirmed-arrival corners (the star recipe)
actions = [{"Mode": "FollowVector", "ModeParameters": [0, 1.5, 0, 0],
            "EndCondition": "DistanceToTarget",
            "ConditionParameters": [1.0, 1.0, 0.6, 0.3],
            "Command": "OnConditionNextWaypoint",
            "JumpDestination": 0, "ErrorDestination": 0}]

# square, 15 m sides at 30 m AGL (NED down = -30), closing on the start
square = [(0.0, 0.0), (15.0, 0.0), (15.0, 15.0), (0.0, 15.0), (0.0, 0.0)]
wps = [{"Position": [n, e, -30.0], "Velocity": 1.5, "Action": 0}
       for (n, e) in square]

wp_def, act_def = db["Waypoint"], db["PathAction"]
crc = 0
for i, w in enumerate(wps):
    resolved = flight_config.resolve_enum_values(wp_def, w)
    client.send_object("Waypoint", resolved, inst_id=i)
    time.sleep(0.02)
    client.send_object("Waypoint", resolved, inst_id=i)  # loss hedge
    time.sleep(0.02)
    crc = crc8_07(crc, wp_def.pack(resolved))
for i, a in enumerate(actions):
    resolved = flight_config.resolve_enum_values(act_def, a)
    client.send_object("PathAction", resolved, inst_id=i)
    time.sleep(0.02)
    client.send_object("PathAction", resolved, inst_id=i)
    time.sleep(0.02)
    crc = crc8_07(crc, act_def.pack(resolved))

plan = {"WaypointCount": len(wps), "PathActionCount": len(actions), "Crc": crc}
client.send_object("PathPlan", plan)
time.sleep(0.05)
client.send_object("PathPlan", plan)
print(f"uploaded {len(wps)} waypoints + {len(actions)} actions, crc={crc}")

deadline = time.time() + 15
verdict = None
while time.time() < deadline:
    state.pop("SystemAlarms", None)
    client.request_object("SystemAlarms")
    t0 = time.time()
    while time.time() - t0 < 3 and "SystemAlarms" not in state:
        client.run(duration=0.5, on_object=grab)
    a = state.get("SystemAlarms")
    if a:
        verdict = a["Alarm"][PLAN_IDX]
        if verdict == "OK":
            break
    time.sleep(1)
print(f"PLAN alarm: {verdict}  ({'GREEN - flight side validated the plan' if verdict == 'OK' else 'not green'})")
