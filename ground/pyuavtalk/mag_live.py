#!/usr/bin/env python3
"""Live dual-compass viewer: prints the primary mag (RM3100 via CAN node 125)
and the aux mag (QMC5883P on the GPS module, node 124) once per second, plus
fused yaw. Wave a magnet or steel tool near each physical unit to identify
which sensor is which - the touched one swings by hundreds of mGauss.

Run:  python3 ground/pyuavtalk/mag_live.py     (Ctrl-C to stop)
NOTE: one UDP client at a time - close the GCS connection first (or expect
both to flap)."""
import sys
import time

sys.path.insert(0, "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/ground/pyuavtalk")
import uavtalk  # noqa: E402
from uavtalk_client import UAVTalkClient, UdpTransport  # noqa: E402

XML = "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/shared/uavobjectdefinition"
db = uavtalk.UAVObjectDB(XML)
client = UAVTalkClient(UdpTransport("192.168.0.90", 9000), db)

state = {}
prev = {}


def on_object(objdef, inst, d):
    state[objdef.name] = d


client.run(duration=2, on_object=on_object)
print(f"{'time':8s} {'RM3100 (primary, node 125)':>32s} {'QMC (aux, GPS module)':>32s} {'yaw':>8s}")
try:
    while True:
        for w in ("MagSensor", "AuxMagSensor", "AttitudeState"):
            client.request_object(w)
        client.run(duration=1.0, on_object=on_object)
        ms = state.get("MagSensor", {})
        am = state.get("AuxMagSensor", {})
        at = state.get("AttitudeState", {})
        rm = (ms.get("x", 0), ms.get("y", 0), ms.get("z", 0))
        qm = (am.get("x", 0), am.get("y", 0), am.get("z", 0))
        # flag movement vs the previous second so a swing is unmissable
        moved_rm = "*" if prev.get("rm") and max(abs(a - b) for a, b in zip(rm, prev["rm"])) > 20 else " "
        moved_qm = "*" if prev.get("qm") and max(abs(a - b) for a, b in zip(qm, prev["qm"])) > 20 else " "
        prev["rm"], prev["qm"] = rm, qm
        print(f"{time.strftime('%H:%M:%S'):8s} "
              f"({rm[0]:7.1f},{rm[1]:7.1f},{rm[2]:7.1f}){moved_rm} "
              f"({qm[0]:7.1f},{qm[1]:7.1f},{qm[2]:7.1f}){moved_qm} "
              f"{at.get('Yaw', 0):7.2f}")
except KeyboardInterrupt:
    pass
