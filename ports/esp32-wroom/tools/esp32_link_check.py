#!/usr/bin/env python3
"""
esp32_link_check - prove a UAVTalk link to the esp32wroom board end to end.

Built on the same UAVTalkClient the other tools use, so the handshake, the
retry/ACK behaviour and the object database are all the tested ones -- this
script only drives them and reports.

Checks, in order:

  1. framing    CRC-valid UAVTalk packets decode to known objects
  2. handshake  the board moves to Connected with a GCS present
  3. read       a settings object can be REQUESTED and comes back
  4. write      a settings field can be SET and reads back changed
                (the original value is restored before exiting)

Usage:
    python3 esp32_link_check.py [--serial DEV] [--baud N]

Baud: 57600, matching HwSettings.TelemetrySpeed. (An earlier revision of the
port landed on 38400 because pios_usart.c inherited whatever UART source
clock IDF's console had left selected; pinning UART_SCLK_APB fixed it.)
"""

import argparse
import os
import sys
import threading
import time

# pyuavtalk lives in the NinjaPilot tree, not in this repo -- this port
# consumes that code rather than duplicating it. Point NINJAPILOT_ROOT at your
# checkout if it is not a sibling directory.
_HERE = os.path.dirname(os.path.abspath(__file__))
NINJAPILOT_ROOT = os.environ.get(
    "NINJAPILOT_ROOT",
    os.path.abspath(os.path.join(_HERE, "..", "..", "NinjaPilot-15.02.ninja")))
_PYUAVTALK = os.path.join(NINJAPILOT_ROOT, "ground", "pyuavtalk")

if not os.path.isdir(_PYUAVTALK):
    sys.exit("pyuavtalk not found at %s\n"
             "Set NINJAPILOT_ROOT to your NinjaPilot checkout." % _PYUAVTALK)

sys.path.insert(0, _PYUAVTALK)
import uavtalk
from uavtalk_client import SerialTransport, UAVTalkClient, default_xml_dir


class Esp32SerialTransport(SerialTransport):
    """SerialTransport that does not hold the board in reset.

    On the USB-serial adapters used with ESP32 boards, DTR and RTS drive
    EN/RESET and GPIO0 -- that is how esptool reboots the chip. pyserial
    asserts both when it opens a port, so a stock SerialTransport wedges the
    board: zero bytes at every baud, while esptool still talks to it fine.

    Upstream pyuavtalk has the same fix, but this port must work against an
    UNPATCHED NinjaPilot checkout, so do it here too rather than depend on it.
    """

    def __init__(self, port, baud):
        super().__init__(port, baud)
        try:
            self.ser.dtr = False
            self.ser.rts = False
        except (OSError, IOError):
            pass  # not every adapter exposes the modem lines



def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--serial", default="/dev/cu.usbserial-210")
    ap.add_argument("--baud", type=int, default=57600)
    ap.add_argument("--settle", type=float, default=8.0,
                    help="seconds to watch the stream before probing")
    args = ap.parse_args()

    db = uavtalk.UAVObjectDB(default_xml_dir())

    class LockedTransport(object):
        """Serialise writes.

        The client's run loop pushes a GCSTelemetryStats heartbeat once a
        second from its own thread while this script issues requests from the
        main one. Two unsynchronised ser.write() calls can interleave in the
        middle of a UAVTalk frame; the board then fails CRC and silently drops
        the request, which looks exactly like "the board ignores requests".
        """

        def __init__(self, inner):
            self.inner = inner
            self.lock = threading.Lock()

        def send(self, data):
            with self.lock:
                self.inner.send(data)

        def poll_recv(self, timeout):
            return self.inner.poll_recv(timeout)

    client = UAVTalkClient(LockedTransport(Esp32SerialTransport(args.serial, args.baud)), db)
    print("[link]      %s @ %d, %d object definitions" % (args.serial, args.baud, len(db.by_name)))

    seen = {}
    connected = threading.Event()
    inbox = {}
    lock = threading.Lock()

    def on_object(objdef, inst_id, decoded):
        with lock:
            seen[objdef.name] = seen.get(objdef.name, 0) + 1
            inbox[objdef.name] = decoded

    def on_connected():
        connected.set()

    # The client owns the socket and the handshake state machine, so it has to
    # run continuously in ONE call -- slicing it into repeated short run()s
    # restarts the handshake every time and the reply window never stays open.
    t = threading.Thread(target=client.run,
                         kwargs=dict(duration=90, on_object=on_object,
                                     on_connected=on_connected),
                         daemon=True)
    t.start()

    def fetch(name, timeout=15.0):
        """Request an object and wait for a fresh copy of it."""
        with lock:
            inbox.pop(name, None)
        client.request_object(name)
        end = time.time() + timeout
        while time.time() < end:
            with lock:
                if name in inbox:
                    return inbox[name]
            time.sleep(0.05)
        return None

    failures = []

    connected.wait(timeout=args.settle + 15)
    time.sleep(args.settle)

    # --- 1. framing ------------------------------------------------------
    with lock:
        total, distinct = sum(seen.values()), len(seen)
        top = sorted(seen.items(), key=lambda kv: -kv[1])[:5]
    if total:
        print("[framing]   %d objects received, %d distinct" % (total, distinct))
        for n, c in top:
            print("              %-28s x%d" % (n, c))
    else:
        failures.append("framing: nothing decoded (wrong baud?)")
        print("[framing]   FAIL - nothing decoded")

    # --- 2. handshake ----------------------------------------------------
    if connected.is_set():
        print("[handshake] flight side reached Connected")
    else:
        failures.append("handshake: never reached Connected")
        print("[handshake] FAIL - never reached Connected")

    # --- 3. read ---------------------------------------------------------
    hw = fetch("HwSettings")
    if hw is None:
        failures.append("read: HwSettings never answered")
        print("[read]      FAIL - HwSettings request unanswered")
    else:
        print("[read]      HwSettings.TelemetrySpeed = %s (the board's own view)"
              % hw.get("TelemetrySpeed"))

    # --- 4. write --------------------------------------------------------
    name, field = "StabilizationSettingsBank1", "RollRatePID"
    before = fetch(name)
    if before is None:
        failures.append("write: could not read %s first" % name)
        print("[write]     SKIP - could not read %s" % name)
    else:
        original = list(before[field])
        changed = list(original)
        changed[0] = round(float(original[0]) + 0.001, 6)
        client.send_object(name, dict(before, **{field: changed}),
                           msg_type=uavtalk.TYPE_OBJ_ACK)
        time.sleep(1.0)
        after = fetch(name)
        got = after[field][0] if after else None
        ok = got is not None and abs(float(got) - changed[0]) < 1e-6
        print("[write]     %s.%s[0]: %.6f -> %.6f, read back %s  %s"
              % (name, field, original[0], changed[0],
                 ("%.6f" % got) if got is not None else "None",
                 "OK" if ok else "MISMATCH"))
        if not ok:
            failures.append("write: %s did not take" % name)
        client.send_object(name, dict(before, **{field: original}),
                           msg_type=uavtalk.TYPE_OBJ_ACK)
        time.sleep(0.8)
        print("[write]     original value restored")

    print()
    if failures:
        print("RESULT: %d check(s) FAILED" % len(failures))
        for f in failures:
            print("  - %s" % f)
        return 1
    print("RESULT: link OK - framing, handshake, read and write all verified")
    return 0


if __name__ == "__main__":
    sys.exit(main())
