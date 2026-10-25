#!/usr/bin/env python3
"""
Write the LiteWing airframe to a live board and persist it.

Needed because board_apply_default_airframe() deliberately returns early on a
provisioned board -- it will not overwrite settings someone saved. That is the
right behaviour, and it means firmware defaults reach a board exactly once, on
its first ever boot. Any later correction has to come over the link, which is
what this does.

What it sets, and why each value is what it is:

  ChannelAddr    3, 0, 1, 2
        Mixer row -> output pin. Read off the PCB (LieWingV2.6.C.kicad_pcb),
        where the motor connectors sit at (KiCad coords, Y down):
            J7  MOT_1 GPIO5  x 177.7 y  62.3   right, top
            J8  MOT_2 GPIO6  x 179.1 y 124.4   right, bottom
            J9  MOT_3 GPIO3  x 117.1 y 125.9   left,  bottom
            J10 MOT_4 GPIO4  x 115.6 y  63.9   left,  top
        The PCB gives relative geometry but does not say which EDGE is the
        nose, and the first guess (top = front) was 180 degrees out. Confirmed
        on the bench: driving mixer row 1 spun the back-right motor, so GPIO4 --
        PCB left+top -- is physically rear-right, meaning PCB-top is the rear
        and PCB-left is the right. So:
            MOT_1 GPIO5  rear-left     row 4 -> 0
            MOT_2 GPIO6  front-left    row 1 -> 1
            MOT_3 GPIO3  front-right   row 2 -> 2
            MOT_4 GPIO4  rear-right    row 3 -> 3
        Self-checks against the silkscreen: A falls on front-left and
        rear-right, B on front-right and rear-left -- opposite diagonals, which
        is what quad X requires. The IMU is NOT rotated; the HUD tracks the
        airframe correctly, so only the output map was wrong.
        Prop rotation is on the silkscreen: J7/J9 are B (black/white), J8/J10
        are A (red/blue), which puts A and B on opposite diagonals exactly as
        quad X requires.

  ChannelMin/Neutral/Max   0 / 0 / 1000
        BRUSHED duty in tenths of a percent, NOT microseconds. 1000 here is
        full throttle, so the usual 1000/1000/2000 would mean every motor at
        100% on a disarmed board.

The mixer table itself is left alone -- reordering outputs rather than
rewriting the mixer keeps the GCS showing the conventional quad X.

    apply_litewing_airframe.py --serial /dev/cu.wchusbserial8320
    apply_litewing_airframe.py --udp 192.168.4.1:9000
"""
import argparse
import os
import sys
import time

_HERE = os.path.dirname(os.path.abspath(__file__))
NINJAPILOT_ROOT = os.environ.get(
    "NINJAPILOT_ROOT",
    os.path.abspath(os.path.join(_HERE, "..", "..", "NinjaPilot-15.02.ninja")))
sys.path.insert(0, os.path.join(NINJAPILOT_ROOT, "ground", "pyuavtalk"))

import uavtalk                                                # noqa: E402
import uavtalk_client                                         # noqa: E402

MOTOR_ADDR = [1, 2, 3, 0]      # mixer row -> output pin index


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--serial", metavar="PORT")
    ap.add_argument("--baud", type=int, default=57600)
    ap.add_argument("--udp", metavar="HOST:PORT")
    args = ap.parse_args()

    if args.serial:
        transport = uavtalk_client.SerialTransport(args.serial, args.baud)
    elif args.udp:
        host, _, port = args.udp.partition(":")
        transport = uavtalk_client.UdpTransport(host, int(port or 9000))
    else:
        ap.error("pick --serial or --udp")

    db = uavtalk.UAVObjectDB(uavtalk_client.default_xml_dir())
    client = uavtalk_client.UAVTalkClient(transport, db)

    state = {}

    def grab(objdef, _inst, values):
        state[objdef.name] = values

    client.run(duration=2.0, on_object=grab)
    client.request_object("ActuatorSettings")
    deadline = time.time() + 8.0
    while time.time() < deadline and "ActuatorSettings" not in state:
        client.run(duration=0.3, on_object=grab)

    act = state.get("ActuatorSettings")
    if not act:
        print("No ActuatorSettings from the board; is anything else holding the link?")
        return 1

    print("  before: ChannelAddr=%s Min=%s Neutral=%s Max=%s"
          % (act["ChannelAddr"][:4], act["ChannelMin"][:4],
             act["ChannelNeutral"][:4], act["ChannelMax"][:4]))

    for i in range(4):
        act["ChannelAddr"][i] = MOTOR_ADDR[i]
        act["ChannelType"][i] = "PWM"
        act["ChannelMin"][i] = 0
        act["ChannelNeutral"][i] = 0
        act["ChannelMax"][i] = 1000
    act["MotorsSpinWhileArmed"] = "FALSE"

    client.send_object("ActuatorSettings", act, msg_type=uavtalk.TYPE_OBJ_ACK)
    client.run(duration=1.0, on_object=grab)

    client.send_object("ObjectPersistence", {
        "Operation": "Save", "Selection": "SingleObject",
        "ObjectID": db["ActuatorSettings"].obj_id, "InstanceID": 0,
    }, msg_type=uavtalk.TYPE_OBJ_ACK)
    client.run(duration=2.0, on_object=grab)

    state.pop("ActuatorSettings", None)
    client.request_object("ActuatorSettings")
    deadline = time.time() + 8.0
    while time.time() < deadline and "ActuatorSettings" not in state:
        client.run(duration=0.3, on_object=grab)

    rb = state.get("ActuatorSettings")
    if not rb:
        print("  no readback -- NOT confirmed")
        return 1
    print("  after:  ChannelAddr=%s Min=%s Neutral=%s Max=%s"
          % (rb["ChannelAddr"][:4], rb["ChannelMin"][:4],
             rb["ChannelNeutral"][:4], rb["ChannelMax"][:4]))
    ok = (list(rb["ChannelAddr"][:4]) == MOTOR_ADDR
          and all(rb["ChannelMin"][i] == 0 and rb["ChannelMax"][i] == 1000 for i in range(4)))
    op = state.get("ObjectPersistence")
    print("  persistence: %s" % (op.get("Operation") if op else "(not seen)"))
    print("  -> %s" % ("applied and saved" if ok else "*** MISMATCH ***"))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
