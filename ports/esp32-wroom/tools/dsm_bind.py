#!/usr/bin/env python3
"""
dsm_bind - pair the Spektrum satellite on a LiteWing, and pick which radio
flies it (the satellite, or a GCS/phone streaming GCSReceiver).

    dsm_bind.py status                 what the board has now
    dsm_bind.py verify                 after the bind power-cycle: frames arriving?
    dsm_bind.py use dsm|gcs            switch the five control channels
    dsm_bind.py bind [--pulses 9]      only for firmware that reads HwSettings.DSMxBind

How binding actually works on LiteWing: the bind pulses have to be driven on
the satellite's signal pin (IO15) by the ESP32 inside the satellite's own
power-up window, and only a POWER CYCLE (not a reset) drops the 3.3V that
feeds it. No host-side script can do that part. The pulse count is the
compile-time `.bind_pulses` in targets/litewing/board_hw_defs.c:

    1. set .bind_pulses = 9 (DSMX 2048/11ms, right for an SPM9745), build, flash
    2. power the board OFF; put the transmitter in bind mode
    3. power the board ON -- ~250 ms after boot it pulses IO15; the satellite
       LED blinks fast, then goes solid when the transmitter answers
    4. take the TX out of bind mode, leave it ON, run `dsm_bind.py verify`
    5. set .bind_pulses back to 0, build, flash. Leaving it at 9 is a trap: a
       bound satellite is silent when the TX is off, and the firmware cannot
       tell that from never having been bound, so every TX-off power-up would
       put it straight back into bind mode.

`bind` sets HwSettings.DSMxBind for a firmware that honours that field at DSM
init; the current LiteWing firmware does not, so on it the command is a no-op.

`use gcs` parks Collective/Accessory on None while the GCS has the sticks --
an Accessory left on DSM with the TX off times out and invalidates the whole
input (Connected=False, Receiver=Warning) even though the GCS sticks are fine.
It also swaps endpoints: DSM speaks 2048 counts, GCS speaks microseconds. The
DSM set is stashed in ~/NinjaPilot-logs/dsm_endpoints.json and restored by
`use dsm`, so a measured rc_calibrate travel survives the round trip.
Throttle neutral is always kept ABOVE its minimum: receiver.c scales a stick
at neutral to 0.0 and armhandler.c only treats Throttle < 0 as "low".

One UAVTalk client at a time on the UDP port -- the board latches a single
peer. Close the phone app / GCS first, or use --serial.
"""
import argparse
import json
import os
import sys
import time

_HERE = os.path.dirname(os.path.abspath(__file__))
NINJAPILOT_ROOT = os.path.abspath(os.path.join(_HERE, "..", "..", "NinjaPilot-15.02.ninja"))
sys.path.insert(0, os.path.join(NINJAPILOT_ROOT, "ground", "pyuavtalk"))
sys.path.insert(0, _HERE)
import uavtalk                                                    # noqa: E402
from uavtalk_client import UAVTalkClient, UdpTransport, default_xml_dir  # noqa: E402

STASH = os.path.expanduser("~/NinjaPilot-logs/dsm_endpoints.json")
FUNCS = ["Throttle", "Roll", "Pitch", "Yaw", "FlightMode", "Collective",
         "Accessory0", "Accessory1", "Accessory2"]
DSM_GROUP = "DSM (MainPort)"
GCS_GROUP = "GCS"


class Board(object):
    def __init__(self, args):
        self.db = uavtalk.UAVObjectDB(default_xml_dir())
        if args.serial:
            from imu_bringup import Esp32SerialTransport
            tr = Esp32SerialTransport(args.serial, args.baud)
            print("serial %s @ %d" % (args.serial, args.baud))
        else:
            tr = UdpTransport(args.host, args.port)
            print("udp %s:%d" % (args.host, args.port))
        self.client = UAVTalkClient(tr, self.db)
        self.got = {}

    def _on(self, objdef, inst, decoded):
        self.got[objdef.name] = decoded

    def fetch(self, name, tries=8, wait=0.6):
        self.got.pop(name, None)
        for _ in range(tries):
            self.client.request_object(name)
            self.client.run(duration=wait, on_object=self._on)
            if name in self.got:
                return self.got[name]
        return None

    def write(self, name, data):
        self.client.send_object(name, data, msg_type=uavtalk.TYPE_OBJ_ACK)
        self.client.run(duration=0.5, on_object=self._on)

    def save(self, name):
        self.client.send_object("ObjectPersistence", {
            "Operation": "Save", "Selection": "SingleObject",
            "ObjectID": self.db[name].obj_id, "InstanceID": 0,
        }, msg_type=uavtalk.TYPE_OBJ_ACK)
        deadline = time.time() + 3.0
        while time.time() < deadline:
            self.client.run(duration=0.3, on_object=self._on)
            op = self.got.get("ObjectPersistence", {})
            if op.get("Operation") in (5, 6, "Completed", "Error"):
                return self.db["ObjectPersistence"].describe(op)["Operation"] == "Completed"
        return False

    def describe(self, name, data):
        return self.db[name].describe(data)


def show_status(b):
    mcs = b.fetch("ManualControlSettings")
    hw = b.fetch("HwSettings")
    mcc = b.fetch("ManualControlCommand")
    if not mcs:
        sys.exit("no reply from the board (off? another client holding the UDP latch?)")
    d = b.describe("ManualControlSettings", mcs)
    print("\nReceiver mapping (ManualControlSettings):")
    for i, f in enumerate(FUNCS):
        print("  %-11s group=%-14s ch=%d  min/neutral/max %4d/%4d/%4d" % (
            f, d["ChannelGroups"][i], d["ChannelNumber"][i],
            d["ChannelMin"][i], d["ChannelNeutral"][i], d["ChannelMax"][i]))
    if hw:
        print("HwSettings.DSMxBind = %s  (%s)" % (
            hw.get("DSMxBind"), "ARMED - next power-up binds" if hw.get("DSMxBind") else "disarmed"))
    if mcc:
        dd = b.describe("ManualControlCommand", mcc)
        ch = mcc.get("Channel", [])
        print("ManualControlCommand: Connected=%s  Thr=%+.2f Roll=%+.2f Pitch=%+.2f Yaw=%+.2f" % (
            dd.get("Connected"), mcc.get("Throttle", 0), mcc.get("Roll", 0),
            mcc.get("Pitch", 0), mcc.get("Yaw", 0)))
        print("  raw channels:", " ".join(
            ("%5d" % c) if c < 60000 else ("  TMO" if c == 65535 else "  INV") for c in ch))
    return d, hw, mcc


def cmd_status(b, args):
    show_status(b)


def cmd_bind(b, args):
    print("NOTE: the current LiteWing firmware takes its bind pulse count from the\n"
          "      compile-time .bind_pulses in board_hw_defs.c, not from this field.\n"
          "      Setting it anyway, for a firmware that reads HwSettings.DSMxBind.\n")
    hw = b.fetch("HwSettings")
    if not hw:
        sys.exit("no reply from the board")
    hw["DSMxBind"] = int(args.pulses)
    b.write("HwSettings", hw)
    ok = b.save("HwSettings")
    back = b.fetch("HwSettings")
    if not ok or not back or int(back.get("DSMxBind", 0)) != int(args.pulses):
        sys.exit("could not persist HwSettings.DSMxBind=%d (got %s)" % (
            args.pulses, back and back.get("DSMxBind")))
    print("""
HwSettings.DSMxBind = %d saved. Now, in this order:

  1. Power the board OFF (battery out / USB out). A reset is not enough --
     the satellite only opens its bind window as its own 3.3V comes up.
  2. Put the transmitter in bind mode (hold its bind control while
     switching it on) and keep it there.
  3. Power the board ON. About a quarter second after boot the firmware
     sends %d bind pulses down IO15; the satellite's LED goes to a fast
     blink, then solid when the transmitter answers.
  4. Take the transmitter out of bind mode, and with it switched ON, run:

         dsm_bind.py verify

     which checks frames are arriving and sets DSMxBind back to 0.
     Do not skip that: while it is armed, every TX-off power-up will drop
     the satellite back into bind mode.
""" % (args.pulses, args.pulses))


def cmd_verify(b, args):
    d, hw, mcc = show_status(b)
    if d["ChannelGroups"][0] != DSM_GROUP:
        print("\nNote: Throttle is mapped to %s, not the satellite, so the sticks above"
              " do not reflect it. Run `use dsm` to fly on the satellite." % d["ChannelGroups"][0])
    else:
        ch = (mcc or {}).get("Channel", [])
        live = bool(ch) and all(c < 60000 for c in ch[:5])
        print("\nSatellite frames: %s" % ("YES - bound and talking" if live else
              "NONE - is the transmitter on? did the LED go solid?"))
    if hw and int(hw.get("DSMxBind", 0)) != 0:
        hw["DSMxBind"] = 0
        b.write("HwSettings", hw)
        ok = b.save("HwSettings")
        print("HwSettings.DSMxBind cleared to 0: %s" % ("saved" if ok else "SAVE FAILED - retry"))
    else:
        print("HwSettings.DSMxBind already 0.")


def cmd_use(b, args):
    mcs = b.fetch("ManualControlSettings")
    if not mcs:
        sys.exit("no reply from the board")
    d = b.describe("ManualControlSettings", mcs)
    n = len(d["ChannelGroups"])
    mn, nu, mx = list(mcs["ChannelMin"]), list(mcs["ChannelNeutral"]), list(mcs["ChannelMax"])
    if args.which == "gcs":
        if d["ChannelGroups"][0] == DSM_GROUP:
            os.makedirs(os.path.dirname(STASH), exist_ok=True)
            json.dump({"groups": d["ChannelGroups"], "min": mn, "neutral": nu, "max": mx,
                       "saved": time.strftime("%Y-%m-%d %H:%M:%S")}, open(STASH, "w"), indent=1)
            print("stashed DSM endpoints to %s" % STASH)
        groups = [GCS_GROUP] * 5 + ["None"] * (n - 5)
        for i in range(5):
            mn[i], mx[i] = 1000, 2000
            nu[i] = 1050 if i == 0 else 1500
    else:
        st = None
        if os.path.exists(STASH):
            st = json.load(open(STASH))
            print("restoring DSM endpoints stashed %s" % st.get("saved", "?"))
        if st and len(st.get("groups", [])) == n:
            groups, mn, nu, mx = st["groups"], st["min"], st["neutral"], st["max"]
        else:
            print("no stash - seeding textbook DSM 2048 endpoints (run rc_calibrate.py after)")
            groups = [DSM_GROUP] * 5 + ["None"] * (n - 5)
            for i in range(5):
                mn[i], mx[i] = 342, 1706
                nu[i] = 410 if i == 0 else 1024
    if nu[0] <= mn[0]:
        nu[0] = mn[0] + max(8, (mx[0] - mn[0]) // 20)
        print("throttle neutral raised to %d (must sit above min to arm)" % nu[0])
    mcs = dict(mcs)
    mcs["ChannelGroups"] = groups
    mcs["ChannelNumber"] = [1, 2, 3, 4, 5] + [0] * (n - 5)
    mcs["ChannelMin"], mcs["ChannelNeutral"], mcs["ChannelMax"] = mn, nu, mx
    b.write("ManualControlSettings", mcs)
    ok = b.save("ManualControlSettings")
    print("ManualControlSettings -> %s: %s" % (args.which.upper(), "saved" if ok else "SAVE FAILED"))
    show_status(b)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--host", default="192.168.0.139")
    ap.add_argument("--port", type=int, default=9000)
    ap.add_argument("--serial", metavar="DEVICE", help="use USB serial instead of UDP")
    ap.add_argument("--baud", type=int, default=57600)
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("status")
    pb = sub.add_parser("bind")
    pb.add_argument("--pulses", type=int, default=9,
                    help="9 = DSMX 2048/11ms (SPM9745). See pios_esp32_priv.h for the table.")
    sub.add_parser("verify")
    pu = sub.add_parser("use")
    pu.add_argument("which", choices=["dsm", "gcs"])
    args = ap.parse_args()
    b = Board(args)
    {"status": cmd_status, "bind": cmd_bind, "verify": cmd_verify, "use": cmd_use}[args.cmd](b, args)


if __name__ == "__main__":
    main()
