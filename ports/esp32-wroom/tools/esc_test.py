#!/usr/bin/env python3
"""
esc_test - drive each ESC directly over UAVObjects, one at a time.

Uses the flight code's own servo-configuration mechanism (the same one the
GCS output tab uses): ActuatorCommand is switched to flight-read-only, at
which point actuator.c's own writes are refused and it passes OUR channel
values straight to the pins -- no mixer, no stabilization, no arming.
That is the point: the last session proved stabilization reshapes motor
commands on the bench (integral windup), so a fair per-ESC test must bypass
the flight controller entirely.

Each channel in turn: hold min so the ESC arms, ramp to peak, hold, ramp
back down. Then the next. Watch each motor; they should all behave
identically. One that stays silent while its position is announced -- with
the identical command its neighbours spun on -- is a hardware fault.

         !!  PROPS OFF. THIS SPINS MOTORS TO FULL THROTTLE.  !!

ActuatorCommand access and channel values are restored on ANY exit,
including Ctrl+C.

Usage:
    python3 tools/esc_test.py [--serial DEV] [--peak US] [--motor N]
"""

import argparse
import os
import struct
import sys
import threading
import time

_HERE = os.path.dirname(os.path.abspath(__file__))
NINJAPILOT_ROOT = os.environ.get(
    "NINJAPILOT_ROOT",
    os.path.abspath(os.path.join(_HERE, "..", "..", "NinjaPilot-15.02.ninja")))
sys.path.insert(0, os.path.join(NINJAPILOT_ROOT, "ground", "pyuavtalk"))
sys.path.insert(0, _HERE)

import uavtalk                                                # noqa: E402
from uavtalk_client import UAVTalkClient, default_xml_dir     # noqa: E402
from imu_bringup import Esp32SerialTransport                  # noqa: E402

POS = {0: "M1 front-left  (pin 15)", 1: "M2 front-right (pin 33)",
       2: "M3 rear-right  (pin 27)", 3: "M4 rear-left   (pin 12)"}
MIN_US = 1000


def main():
    sys.exit(
        "RETIRED: this tool required the flight battery while a USB serial\n"
        "session was open. On this airframe the BEC's 5V feeds VUSB, so\n"
        "battery + USB together can destroy the board -- hard rule, never.\n"
        "Use the USB-free boot modes instead:\n"
        "  ESC range calibration : BOARD_ESC_CAL build (see setup_wizard step 2)\n"
        "  per-motor spin check  : BOARD_PWM_SELFTEST build\n"
        "  command-level checks  : tools/motor_watch.py with motors UNPOWERED\n"
        "    (commanded PWM is fully observable without ESC power)")


if __name__ == "__main__":
    sys.exit(main())
