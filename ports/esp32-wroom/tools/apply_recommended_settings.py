#!/usr/bin/env python3
"""
apply_recommended_settings - one-shot: write the 2026-09-01 recommended
configuration to the board, verify by readback, and SAVE it to NVS.

Why this exists: the board's saved settings override new firmware defaults
(by design - that is what persistence means), so flashing the fixed
firmware leaves old saved values in charge. This applies, verifies, and
persists:

  StabilizationSettingsBank1  Roll/PitchRatePID 0.0032/0.0075/0.00005,
                              Roll/PitchPI Kp 3.2 (4-inch-class defaults)
  FlightModeSettings          Yaw = Rate on Stabilized1/2/3 (no AxisLock
                              arming-gesture windup)
  ActuatorSettings            MotorsSpinWhileArmed = TRUE
                              (optionally --neutral N: set all four
                              ChannelNeutral equal - do this AFTER ESC cal)

Everything else in each object is read from the board first and preserved.
Run it with NOTHING else connected (no GCS, no flight_monitor - one
UAVTalk client at a time), board DISARMED, props off.

    python3 apply_recommended_settings.py [--host 192.168.0.45] [--neutral 1165]
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
import uavtalk  # noqa: E402
from uavtalk_client import UdpTransport, UAVTalkClient, default_xml_dir  # noqa: E402


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--host", default="192.168.0.45")
    ap.add_argument("--port", type=int, default=9000)
    ap.add_argument("--board-rotation", default=None, metavar="ROLL,PITCH,YAW",
                    help="write AttitudeSettings.BoardRotation (deg) and persist it, "
                         "e.g. 0,0,180 when orientation_check.py reports both axes "
                         "inverted (board nose at the airframe tail)")
    ap.add_argument("--neutral", type=int, default=None,
                    help="set all four ChannelNeutral to this (AFTER ESC cal)")
    args = ap.parse_args()

    db = uavtalk.UAVObjectDB(default_xml_dir())
    client = UAVTalkClient(UdpTransport(args.host, args.port), db)

    latest = {}

    def on_object(objdef, inst_id, decoded):
        latest[objdef.name] = decoded

    done = {"connected": False}

    def on_connected():
        done["connected"] = True

    import threading
    t = threading.Thread(target=lambda: client.run(on_object=on_object,
                                                   on_connected=on_connected,
                                                   duration=3600), daemon=True)
    t.start()
    deadline = time.time() + 10
    while not done["connected"] and time.time() < deadline:
        time.sleep(0.1)
    if not done["connected"]:
        sys.exit("no link to the flight side - is the board up? is the GCS closed?")
    print("[link] connected")

    def fetch(name, timeout=5.0):
        latest.pop(name, None)
        o = db[name]
        end = time.time() + timeout
        while time.time() < end:
            client.transport.send(uavtalk.build_packet(uavtalk.TYPE_OBJ_REQ, o.obj_id, 0))
            for _ in range(10):
                if name in latest:
                    return dict(latest[name])
                time.sleep(0.05)
        sys.exit("could not read %s from the board" % name)

    def _approx(a, b):
        # values round-trip through float32 on the wire; compare numerically
        if isinstance(a, (list, tuple)) and isinstance(b, (list, tuple)):
            return len(a) == len(b) and all(_approx(x, y) for x, y in zip(a, b))
        try:
            fa, fb = float(a), float(b)
            return abs(fa - fb) <= max(1e-9, 1e-4 * max(abs(fa), abs(fb)))
        except (TypeError, ValueError):
            return str(a) == str(b)

    def write_verify(name, values, check_keys):
        client.send_object(name, values)
        time.sleep(0.15)
        client.send_object(name, values)  # single-datagram hedge
        time.sleep(0.25)
        back = fetch(name)
        for k in check_keys:
            if not _approx(back.get(k), values.get(k)):
                sys.exit("VERIFY FAILED %s.%s: wrote %r, board has %r"
                         % (name, k, values.get(k), back.get(k)))
        print("[ ok ] %s written and verified" % name)
        return back

    def save(name):
        o = db[name]
        op = {"Operation": "Save", "Selection": "SingleObject",
              "ObjectID": o.obj_id, "InstanceID": 0}
        latest.pop("ObjectPersistence", None)
        client.send_object("ObjectPersistence", op)
        end = time.time() + 5.0
        while time.time() < end:
            got = latest.get("ObjectPersistence")
            if got and got.get("Operation") in ("Completed", "Error"):
                if got["Operation"] == "Error":
                    sys.exit("board reported ERROR saving %s" % name)
                print("[ ok ] %s saved to NVS" % name)
                return
            time.sleep(0.1)
        sys.exit("no save confirmation for %s" % name)

    # -- Bank1: the 4-inch-class gains ------------------------------------
    bank = fetch("StabilizationSettingsBank1")
    bank["RollRatePID"] = [0.0032, 0.0075, 0.00005, bank["RollRatePID"][3]]
    bank["PitchRatePID"] = [0.0032, 0.0075, 0.00005, bank["PitchRatePID"][3]]
    bank["RollPI"] = [3.2, bank["RollPI"][1], bank["RollPI"][2]]
    bank["PitchPI"] = [3.2, bank["PitchPI"][1], bank["PitchPI"][2]]
    write_verify("StabilizationSettingsBank1", bank, ["RollRatePID", "PitchPI"])
    save("StabilizationSettingsBank1")

    # -- FlightModeSettings: Rate yaw on the stabilized slots --------------
    fms = fetch("FlightModeSettings")
    for slot in (1, 2, 3):
        key = "Stabilization%dSettings" % slot
        modes = list(fms[key])
        if modes[2] == "AxisLock":
            modes[2] = "Rate"
        fms[key] = modes
    write_verify("FlightModeSettings", fms,
                 ["Stabilization1Settings", "Stabilization3Settings"])
    save("FlightModeSettings")

    # -- ActuatorSettings: spin while armed (+ optional equal neutrals) ----
    act = fetch("ActuatorSettings")
    act["MotorsSpinWhileArmed"] = "TRUE"
    if args.board_rotation is not None:
        rot = [float(x) for x in args.board_rotation.split(",")]
        assert len(rot) == 3, "--board-rotation wants ROLL,PITCH,YAW"
        att_s = fetch("AttitudeSettings")
        print("[note] AttitudeSettings.BoardRotation %s -> %s" % (att_s.get("BoardRotation"), rot))
        att_s["BoardRotation"] = rot
        write_verify("AttitudeSettings", att_s, ["BoardRotation"])
        save("AttitudeSettings")
        print("[note] BoardRotation persisted - POWER CYCLE, then re-run orientation_check.py")
    if args.neutral is not None:
        act["ChannelNeutral"] = [args.neutral] * 4 + list(act["ChannelNeutral"][4:])
        print("[note] all four ChannelNeutral -> %d" % args.neutral)
    write_verify("ActuatorSettings", act, ["MotorsSpinWhileArmed"])
    save("ActuatorSettings")

    print("\nall applied, verified, and persisted. POWER-CYCLE the board and")
    print("re-run flight_monitor.py - the preflight should now be GO with at")
    print("most the board-rotation notice (your 1-degree leveling trim).")
    print("NOTE: MotorsSpinWhileArmed=TRUE means props turn at idle the")
    print("moment you arm. Props off on the bench, always.")


if __name__ == "__main__":
    main()
