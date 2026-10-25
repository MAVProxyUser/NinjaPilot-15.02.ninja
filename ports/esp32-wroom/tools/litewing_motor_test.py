#!/usr/bin/env python3
"""
Spin ONE LiteWing motor at a chosen duty, briefly.

              !!  PROPS OFF BEFORE RUNNING THIS  !!

Nothing is armed. ActuatorCommand is switched to flight-read-only, which is the
same mechanism the GCS output tab uses: actuator.c computes its mixer output,
calls ActuatorCommandSet(), has that write REFUSED because the object is
read-only, then immediately re-reads the object --

    ActuatorCommandSet(&command);   // refused
    ActuatorCommandGet(&command);   // gets ours

-- and pushes what it read to the pins. So our value goes straight out with no
mixer, no stabilization and no arming anywhere in the path.

Units are BRUSHED: 0..1000 is 0..100% duty, not microseconds. 250 is a quarter
throttle.

On USB power alone the motor rail (+BATT) is fed by the TP4056's BAT pin, and
R5 = 1.2k sets 1100/1.2 = ~917 mA for all four motors combined. One motor at a
quarter duty is well inside that. Do not expect this to prove thrust -- it
proves the pin, the MOSFET and the motor are alive.

Access and channel values are restored on ANY exit, including Ctrl+C and an
exception.

    python3 tools/litewing_motor_test.py --motor 1 --duty 250 --seconds 2
"""
import argparse
import os
import struct
import sys
import time

_HERE = os.path.dirname(os.path.abspath(__file__))
NINJAPILOT_ROOT = os.environ.get(
    "NINJAPILOT_ROOT",
    os.path.abspath(os.path.join(_HERE, "..", "..", "NinjaPilot-15.02.ninja")))
sys.path.insert(0, os.path.join(NINJAPILOT_ROOT, "ground", "pyuavtalk"))

import uavtalk                                                # noqa: E402
import uavtalk_client                                         # noqa: E402

ACCESS_SHIFT = 0          # flags bit 0: 1 = readonly for the flight side
PINS = {1: "GPIO5", 2: "GPIO6", 3: "GPIO3", 4: "GPIO4"}


class Tester(object):
    def __init__(self, client):
        self.client = client
        self.command = None
        self.saved_meta = None
        self.link_drops = 0
        self._last_status = None
        self.meta_id = client.db["ActuatorCommand"].obj_id + 1

    def _on_object(self, objdef, _inst, values):
        if objdef.name == "ActuatorCommand":
            self.command = values
        elif objdef.name == "FlightTelemetryStats":
            # A board that browns out and reboots comes back through the
            # handshake. Counting that is how "the rail sagged" shows up as
            # evidence instead of a guess.
            status = values.get("Status")
            if status != self._last_status:
                if self._last_status == "Connected" and status != "Connected":
                    self.link_drops += 1
                self._last_status = status

    def pump(self, seconds):
        self.client.run(duration=seconds, on_object=self._on_object)

    def fetch_meta(self):
        self.client.send_raw(uavtalk.TYPE_OBJ_REQ, self.meta_id)
        deadline = time.time() + 3.0
        while time.time() < deadline and self.meta_id not in self.client.meta_payloads:
            self.pump(0.2)
        return self.client.meta_payloads.get(self.meta_id)

    def set_flight_readonly(self, readonly):
        meta = self.saved_meta
        flags = struct.unpack_from("<H", meta, 0)[0]
        if readonly:
            flags |= (1 << ACCESS_SHIFT)
        else:
            flags &= ~(1 << ACCESS_SHIFT)
        self.client.send_raw(uavtalk.TYPE_OBJ, self.meta_id,
                             payload=struct.pack("<H", flags) + meta[2:])
        self.pump(0.3)

    def drive(self, channels):
        values = dict(self.command)
        values["Channel"] = channels
        self.client.send_object("ActuatorCommand", values)


def burst(t, channels, motors, seconds, duty):
    """Drive `motors` at `duty` for `seconds`, then report what the board saw."""
    live = list(channels)
    for m in motors:
        live[m - 1] = duty
    label = "+".join("M%d" % m for m in motors)
    print("  %-12s driving %d/1000 ..." % (label, duty), end="", flush=True)

    drops_before = t.link_drops
    seen = {m: set() for m in motors}
    started = time.time()
    while time.time() - started < seconds:
        t.drive(live)
        t.pump(0.1)
        if t.command:
            for m in motors:
                seen[m].add(t.command["Channel"][m - 1])

    t.drive(channels)
    t.pump(0.2)

    got = {m: (duty in seen[m]) for m in motors}
    dropped = t.link_drops - drops_before
    ok = all(got.values()) and dropped == 0
    detail = " ".join("M%d=%s" % (m, "ok" if got[m] else "NOT SET") for m in motors)
    print("  %s%s" % (detail,
                      "" if dropped == 0 else "   LINK DROPPED x%d (rail sagged)" % dropped))
    return ok


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--serial", default="/dev/cu.wchusbserial8320")
    ap.add_argument("--baud", type=int, default=57600)
    ap.add_argument("--motor", type=int, default=1, choices=(1, 2, 3, 4))
    ap.add_argument("--duty", type=int, default=250,
                    help="per mille, 0..1000 (default 250 = 25%%)")
    ap.add_argument("--seconds", type=float, default=2.0)
    ap.add_argument("--all", action="store_true",
                    help="each motor in turn, then all four together")
    args = ap.parse_args()

    if not 0 <= args.duty <= 1000:
        ap.error("--duty is 0..1000 per mille")

    transport = uavtalk_client.SerialTransport(args.serial, args.baud)
    db = uavtalk.UAVObjectDB(uavtalk_client.default_xml_dir())
    client = uavtalk_client.UAVTalkClient(transport, db)
    t = Tester(client)

    print("PROPS OFF. Motor %d (%s), %d/1000 duty = %.1f%%, %.1fs."
          % (args.motor, PINS[args.motor], args.duty, args.duty / 10.0, args.seconds))
    print("Linking...")
    t.pump(2.0)

    client.request_object("ActuatorCommand")
    deadline = time.time() + 4.0
    while time.time() < deadline and t.command is None:
        t.pump(0.2)
    if t.command is None:
        print("No ActuatorCommand from the board; aborting.")
        return 1

    t.saved_meta = t.fetch_meta()
    if not t.saved_meta or len(t.saved_meta) < 8:
        print("Could not read ActuatorCommand metadata; aborting.")
        return 1

    zeros = [0] * len(t.command["Channel"])
    try:
        t.set_flight_readonly(True)
        t.drive(zeros)
        t.pump(0.3)

        if args.all:
            results = []
            for m in (1, 2, 3, 4):
                results.append((("M%d" % m), burst(t, zeros, [m], args.seconds, args.duty)))
                t.pump(0.8)          # let it settle and the rail recover
            print()
            print("  all four together -- this is the one that can outrun the")
            print("  TP4056's ~917 mA ceiling on USB power:")
            results.append(("all four", burst(t, zeros, [1, 2, 3, 4],
                                              args.seconds, args.duty)))
            print()
            bad = [n for n, ok in results if not ok]
            print("  RESULT: %s" % ("all passed" if not bad
                                    else "problems on " + ", ".join(bad)))
        else:
            burst(t, zeros, [args.motor], args.seconds, args.duty)
    finally:
        # belt and braces: zero first, THEN hand control back
        for _ in range(5):
            try:
                t.drive(zeros)
                t.pump(0.05)
            except Exception:
                pass
        try:
            t.set_flight_readonly(False)
        except Exception:
            pass
        t.pump(0.4)
        transport_close = getattr(transport, "close", None)
        if transport_close:
            transport_close()
        print("  channels zeroed, flight control restored.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
