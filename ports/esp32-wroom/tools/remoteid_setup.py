#!/usr/bin/env python3
"""
remoteid_setup - write the Remote ID identity into the board and turn it on.

    python3 remoteid_setup.py --id-type CAARegistrationID --uas-id FA3XXXXXXXXX \
        --operator-id FA3XXXXXXXXX --self-id "4in quad, hobby" --enable
    python3 remoteid_setup.py --disable
    python3 remoteid_setup.py --status          # read back RemoteIDSettings/Status

IDType: SerialNumber (ANSI/CTA-2063-A serial), CAARegistrationID (e.g. your
FAA registration number), UTMAssignedUUID. Strings are ASCII, max 20 chars
(UASID/OperatorID) and 23 (SelfIDText). Settings persist in NVS.

Honesty: without a GPS the board broadcasts identity + status with UNKNOWN
position. That is not compliant Remote ID on its own; add a GPS on the spare
UART2 and the Location message fills itself in.
"""
import argparse
import os
import sys
import threading
import time

_HERE = os.path.dirname(os.path.abspath(__file__))
NINJAPILOT_ROOT = os.environ.get("NINJAPILOT_ROOT",
                                 os.path.abspath(os.path.join(_HERE, "..", "..", "NinjaPilot-15.02.ninja")))
sys.path.insert(0, os.path.join(NINJAPILOT_ROOT, "ground", "pyuavtalk"))
import uavtalk  # noqa: E402
from uavtalk_client import UdpTransport, UAVTalkClient, default_xml_dir  # noqa: E402


def to_field(text, n):
    b = (text or "").encode("ascii", "replace")[:n]
    return list(b) + [0] * (n - len(b))


def from_field(vals):
    return bytes(int(v) & 0xFF for v in vals).split(b"\0")[0].decode("ascii", "replace")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--host", default="192.168.0.45")
    ap.add_argument("--port", type=int, default=9000)
    ap.add_argument("--id-type", choices=["None", "SerialNumber", "CAARegistrationID", "UTMAssignedUUID"])
    ap.add_argument("--uas-id")
    ap.add_argument("--ua-type", default=None, help="e.g. HelicopterOrMultirotor")
    ap.add_argument("--operator-id")
    ap.add_argument("--self-id")
    ap.add_argument("--enable", action="store_true")
    ap.add_argument("--disable", action="store_true")
    ap.add_argument("--status", action="store_true")
    args = ap.parse_args()

    db = uavtalk.UAVObjectDB(default_xml_dir())
    client = UAVTalkClient(UdpTransport(args.host, args.port), db)
    latest, lock = {}, threading.Lock()

    def on_object(objdef, inst_id, decoded):
        with lock:
            latest[objdef.name] = dict(decoded)
    threading.Thread(target=lambda: client.run(on_object=on_object, duration=100000), daemon=True).start()
    time.sleep(1.5)

    def fetch(name, timeout=5.0):
        with lock:
            latest.pop(name, None)
        o = db[name]
        end = time.time() + timeout
        while time.time() < end:
            client.transport.send(uavtalk.build_packet(uavtalk.TYPE_OBJ_REQ, o.obj_id, 0))
            for _ in range(8):
                with lock:
                    v = latest.get(name)
                if v is not None:
                    return v
                time.sleep(0.05)
        sys.exit("could not read %s - board on? nothing else connected?" % name)

    def show():
        s = fetch("RemoteIDSettings")
        st = fetch("RemoteIDStatus")
        print("RemoteIDSettings: Enabled=%s IDType=%s UAType=%s UASID='%s' OperatorID='%s' SelfID='%s'" % (
            s["Enabled"], s["IDType"], s["UAType"], from_field(s["UASID"]), from_field(s["OperatorID"]), from_field(s["SelfIDText"])))
        print("RemoteIDStatus:   State=%s PositionSource=%s Messages=%s TxCount=%s" % (
            st["State"], st["PositionSource"], st["Messages"], st["TxCount"]))

    if args.status or not any([args.id_type, args.uas_id, args.ua_type, args.operator_id, args.self_id, args.enable, args.disable]):
        show()
        return

    s = fetch("RemoteIDSettings")
    if args.id_type:
        s["IDType"] = args.id_type
    if args.uas_id is not None:
        s["UASID"] = to_field(args.uas_id, 20)
    if args.ua_type:
        s["UAType"] = args.ua_type
    if args.operator_id is not None:
        s["OperatorID"] = to_field(args.operator_id, 20)
    if args.self_id is not None:
        s["SelfIDText"] = to_field(args.self_id, 23)
    if args.enable:
        s["Enabled"] = "TRUE"
    if args.disable:
        s["Enabled"] = "FALSE"
    client.send_object("RemoteIDSettings", s)
    time.sleep(0.3)
    back = fetch("RemoteIDSettings")
    for k in ("Enabled", "IDType", "UAType", "UASID", "OperatorID", "SelfIDText"):
        if list(back[k]) != list(s[k]) if isinstance(s[k], list) else back[k] != s[k]:
            sys.exit("write of %s did not stick (wanted %s got %s)" % (k, s[k], back[k]))
    client.send_object("ObjectPersistence", {"Operation": "Save", "Selection": "SingleObject",
                                             "ObjectID": db["RemoteIDSettings"].obj_id, "InstanceID": 0})
    time.sleep(1.0)
    print("saved.")
    time.sleep(2.0)
    show()


if __name__ == "__main__":
    main()
