#!/usr/bin/env python3
"""
imu_bringup - check an IMU on the esp32wroom board, over UAVTalk.

Runs the sensor half of the bring-up list in README.md and says plainly which
step you are on. Nothing here writes to the board except the GCS handshake.

  1. link          UAVTalk is up and the flight side reports Connected
  2. detect        SystemAlarms.BootFault is clear (the board found an IMU)
  3. gyro at rest  GyroState mean ~0 deg/s, and the noise is sane
  4. accel at rest |AccelState| ~9.81 m/s^2, and which axis holds gravity
  5. attitude      AttitudeState Roll/Pitch near level

With --tilt it then streams Roll/Pitch live so you can tip the board and watch
the complementary filter track. Keep props OFF for all of this.

Usage:
    python3 tools/imu_bringup.py [--serial DEV] [--baud N] [--tilt]
"""

import argparse
import math
import os
import sys
import threading
import time

_HERE = os.path.dirname(os.path.abspath(__file__))
NINJAPILOT_ROOT = os.environ.get(
    "NINJAPILOT_ROOT",
    os.path.abspath(os.path.join(_HERE, "..", "..", "NinjaPilot-15.02.ninja")))
_PYUAVTALK = os.path.join(NINJAPILOT_ROOT, "ground", "pyuavtalk")

if not os.path.isdir(_PYUAVTALK):
    sys.exit("pyuavtalk not found at %s\n"
             "Set NINJAPILOT_ROOT to your NinjaPilot checkout." % _PYUAVTALK)

sys.path.insert(0, _PYUAVTALK)
import uavtalk                                             # noqa: E402
from uavtalk_client import SerialTransport, UAVTalkClient, default_xml_dir  # noqa: E402


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
        # Deliberately NOT calling super().__init__: it opens the port in its
        # constructor, and pyserial asserts DTR/RTS during open -- which
        # pulses EN and REBOOTS the board before we can deassert anything.
        # Deasserting after open (the previous approach here) un-wedges the
        # boot but the reset has already happened: every tool attach cost a
        # reboot, ~2s of boot, the boot-window alarms, and whatever state the
        # board was in -- including ARMED.
        #
        # Setting the line states on an UNOPENED port makes pyserial apply
        # them at open, and measured on this adapter the board streams on
        # uninterrupted (first bytes 0.11s after open, no boot gap). Tools
        # now attach to a running -- even armed -- board without touching it.
        import serial as _serial
        try:
            ser = _serial.Serial()
            ser.port = port
            ser.baudrate = baud
            ser.timeout = 0
            ser.dtr = False
            ser.rts = False
            ser.open()
        except Exception:
            # Some adapter/driver states reject the pre-configured open with
            # termios EINVAL. Fall back to the classic open -- this DOES
            # reset the board (DTR pulse), which is worse but works; the
            # deassert after keeps it out of the bootloader.
            ser = _serial.Serial(port, baud, timeout=0)
            try:
                ser.dtr = False
                ser.rts = False
            except (OSError, IOError):
                pass
            print("  (note: no-reset open failed; board was reset by this "
                  "attach)", flush=True)
        self.ser = ser


GRAVITY = 9.80665


def stats(vals):
    n = len(vals)
    if n == 0:
        return 0.0, 0.0
    mean = sum(vals) / n
    var = sum((v - mean) ** 2 for v in vals) / n
    return mean, math.sqrt(var)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--serial", default="/dev/cu.usbserial-210")
    ap.add_argument("--baud", type=int, default=57600)
    ap.add_argument("--sample", type=float, default=8.0,
                    help="seconds of at-rest sampling (default 8)")
    ap.add_argument("--tilt", action="store_true",
                    help="after the checks, stream Roll/Pitch until Ctrl+C")
    args = ap.parse_args()

    db = uavtalk.UAVObjectDB(default_xml_dir())

    class LockedTransport(object):
        """Serialise writes -- the client heartbeats from its own thread."""

        def __init__(self, inner):
            self.inner = inner
            self.lock = threading.Lock()

        def send(self, data):
            with self.lock:
                self.inner.send(data)

        def poll_recv(self, timeout):
            return self.inner.poll_recv(timeout)

    client = UAVTalkClient(LockedTransport(Esp32SerialTransport(args.serial, args.baud)), db)
    print("[link]     %s @ %d" % (args.serial, args.baud))

    latest = {}
    samples = {"GyroState": [], "AccelState": []}
    connected = threading.Event()
    lock = threading.Lock()
    collecting = {"on": False}

    def on_object(objdef, inst_id, decoded):
        with lock:
            latest[objdef.name] = decoded
            if collecting["on"] and objdef.name in samples:
                samples[objdef.name].append(decoded)

    threading.Thread(target=client.run,
                     kwargs=dict(duration=600, on_object=on_object,
                                 on_connected=connected.set),
                     daemon=True).start()

    if not connected.wait(timeout=25):
        print("[link]     FAIL - never reached Connected. Is the board powered "
              "and on the right baud?")
        return 1
    print("[link]     connected")

    # --- 2. did the board find an IMU? ----------------------------------
    time.sleep(2.0)
    with lock:
        alarms = latest.get("SystemAlarms")
    if alarms is None:
        print("[detect]   no SystemAlarms yet - cannot tell")
    else:
        arr = alarms.get("Alarm")
        # SystemAlarms.Alarm is a 21-element array; pyuavtalk's Field keeps the
        # enum options but not the element NAMES, so read those from the XML.
        boot = None
        try:
            import xml.etree.ElementTree as ET
            xml = os.path.join(default_xml_dir(), "systemalarms.xml")
            for fel in ET.parse(xml).getroot().iter("field"):
                if fel.get("name") != "Alarm":
                    continue
                names = fel.get("elementnames")
                names = (names.split(",") if names else
                         [e.text for e in (fel.find("elementnames") or [])])
                names = [n.strip() for n in names]
                boot = arr[names.index("BootFault")]
                break
        except Exception:
            boot = None
        if boot is None:
            print("[detect]   SystemAlarms present (BootFault index unknown); "
                  "relying on sensor data below")
        elif boot in ("OK", "Uninitialised"):
            print("[detect]   BootFault = %s  (board is happy with the IMU)" % boot)
        else:
            print("[detect]   BootFault = %s  <-- the board did NOT accept an IMU" % boot)
            print("           Expect WHO_AM_I 0x12 for an ICM-20602. Check SDO->GPIO19,")
            print("           CS->GPIO5, SCLK->18, MOSI->23, and 3V3 not 5V.")

    # --- 3/4. sample at rest --------------------------------------------
    print("[sample]   hold the board STILL for %.0fs ..." % args.sample)
    with lock:
        samples["GyroState"] = []
        samples["AccelState"] = []
        collecting["on"] = True
    time.sleep(args.sample)
    with lock:
        collecting["on"] = False
        g = list(samples["GyroState"])
        a = list(samples["AccelState"])

    ok = True

    if not g:
        print("[gyro]     FAIL - no GyroState received. The IMU is not producing data.")
        ok = False
    else:
        for axis in "xyz":
            m, sd = stats([s[axis] for s in g])
            flag = "" if abs(m) < 5.0 else "   <-- large bias, is it moving?"
            print("[gyro]     %s  mean %+8.3f deg/s   noise %.3f%s" % (axis, m, sd, flag))
        if all(abs(stats([s[ax] for s in g])[1]) < 1e-9 for ax in "xyz"):
            print("[gyro]     FAIL - perfectly zero noise means the values are not real")
            ok = False

    if not a:
        print("[accel]    FAIL - no AccelState received.")
        ok = False
    else:
        mags = [math.sqrt(s["x"] ** 2 + s["y"] ** 2 + s["z"] ** 2) for s in a]
        mm, msd = stats(mags)
        means = {ax: stats([s[ax] for s in a])[0] for ax in "xyz"}
        for ax in "xyz":
            print("[accel]    %s  mean %+8.3f m/s^2" % (ax, means[ax]))
        dom = max(means, key=lambda k: abs(means[k]))
        print("[accel]    magnitude %.3f m/s^2 (expect ~%.2f), gravity on %s"
              % (mm, GRAVITY, dom))
        if abs(mm - GRAVITY) > 1.5:
            print("[accel]    FAIL - magnitude is off; scaling or wiring is wrong")
            ok = False

    # --- 5. attitude -----------------------------------------------------
    with lock:
        att = latest.get("AttitudeState")
    if att:
        print("[attitude] Roll %+7.2f  Pitch %+7.2f  Yaw %+7.2f"
              % (att["Roll"], att["Pitch"], att["Yaw"]))
        if abs(att["Roll"]) > 15 or abs(att["Pitch"]) > 15:
            print("           (not level - either the board is tilted, or the "
                  "sensor orientation needs setting in AttitudeSettings)")
    else:
        print("[attitude] no AttitudeState received")
        ok = False

    print()
    print("RESULT: %s" % ("sensor path looks healthy" if ok else "something is wrong above"))

    if args.tilt:
        print("\nTilt the board - Ctrl+C to stop.\n")
        try:
            while True:
                with lock:
                    att = latest.get("AttitudeState")
                    gy = latest.get("GyroState")
                if att and gy:
                    sys.stdout.write("\r  Roll %+7.2f  Pitch %+7.2f   gyro %+7.1f %+7.1f %+7.1f deg/s    "
                                     % (att["Roll"], att["Pitch"], gy["x"], gy["y"], gy["z"]))
                    sys.stdout.flush()
                time.sleep(0.1)
        except KeyboardInterrupt:
            print()

    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
