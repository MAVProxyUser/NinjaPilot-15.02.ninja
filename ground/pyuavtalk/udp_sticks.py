#!/usr/bin/env python3
"""PPM-format stick input over UDP for the NinjaPilot realposix board.

Streams stick frames to the firmware's UDP receiver (port 9003), which is
registered as the PPM channel group - so with ManualControlSettings
ChannelGroups=PPM this IS the radio. Frame format (see pios_udp_rcvr.h):

    "PPM1" + seq(u8) + count(u8) + count x uint16le microseconds

Channel map (matches the persisted ManualControlSettings):
    ch1 Throttle   ch2 Roll   ch3 Pitch   ch4 Yaw   ch5 FlightMode

Modes:
  --center          neutral sticks, throttle low (arms nothing, INPUT green)
  --pattern         slow sinusoid sweeps on roll/pitch/yaw (visible motion)
  --arm             center, then hold throttle-low + yaw-right for ~3s
                    (arming gesture), then back to center
  --joystick        gamepad via pygame (Xbox: LY=throttle LX=yaw RX=roll
                    RY=pitch, A/B/X = flight mode positions 1/2/3)
                    pip install pygame
  --lossy P         drop P% of frames randomly (INPUT orange demo)
  --stop-after S    exit after S seconds (INPUT red demo follows)

One client per PORT: this uses 9003 and coexists with a GCS on 9000.
"""
import argparse
import math
import random
import socket
import struct
import sys
import time

DEF_TARGET = "192.168.0.90"
DEF_PORT = 9003
RATE_HZ = 50.0

MID, LOW, HIGH = 1500, 1000, 2000


def clamp(v):
    return max(900, min(2100, int(v)))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--target", default=DEF_TARGET)
    ap.add_argument("--port", type=int, default=DEF_PORT)
    ap.add_argument("--rate", type=float, default=RATE_HZ)
    ap.add_argument("--center", action="store_true")
    ap.add_argument("--pattern", action="store_true")
    ap.add_argument("--arm", action="store_true")
    ap.add_argument("--joystick", action="store_true")
    ap.add_argument("--lossy", type=float, default=0.0, metavar="PCT")
    ap.add_argument("--stop-after", type=float, default=0.0, metavar="SEC")
    args = ap.parse_args()

    js = None
    if args.joystick:
        try:
            import pygame
            pygame.init()
            pygame.joystick.init()
            if pygame.joystick.get_count() == 0:
                sys.exit("no gamepad found (pygame sees 0 joysticks)")
            js = pygame.joystick.Joystick(0)
            js.init()
            print(f"gamepad: {js.get_name()} ({js.get_numaxes()} axes)")
        except ImportError:
            sys.exit("--joystick needs pygame: pip install pygame")
    elif not (args.center or args.pattern or args.arm):
        args.center = True

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    seq = 0
    t0 = time.time()
    period = 1.0 / args.rate
    mode_us = LOW  # flight mode position 1

    print(f"streaming {args.rate:.0f} Hz PPM frames to {args.target}:{args.port}"
          + (f" with {args.lossy:.0f}% synthetic loss" if args.lossy else ""))

    try:
        while True:
            t = time.time() - t0
            if args.stop_after and t > args.stop_after:
                print(f"stopping after {t:.1f}s (failsafe/red demo)")
                break

            thr, roll, pitch, yaw = LOW, MID, MID, MID

            if js is not None:
                import pygame
                pygame.event.pump()
                # Xbox-style: axis1 LY (up=-1), axis0 LX, axis2 RX, axis3 RY
                thr = MID - js.get_axis(1) * 500  # up = more throttle
                yaw = MID + js.get_axis(0) * 500
                naxes = js.get_numaxes()
                roll = MID + (js.get_axis(2) * 500 if naxes > 2 else 0)
                pitch = MID + (js.get_axis(3) * 500 if naxes > 3 else 0)
                if js.get_numbuttons() >= 3:
                    if js.get_button(0):
                        mode_us = LOW      # A -> position 1
                    elif js.get_button(1):
                        mode_us = MID      # B -> position 2
                    elif js.get_button(2):
                        mode_us = HIGH     # X -> position 3
            elif args.pattern:
                roll = MID + 300 * math.sin(t * 0.8)
                pitch = MID + 300 * math.sin(t * 0.6 + 1.0)
                yaw = MID + 200 * math.sin(t * 0.4 + 2.0)
            elif args.arm:
                # 0-2s center, 2-5s arming gesture (thr low + yaw right),
                # then hold center
                if 2.0 < t < 5.0:
                    yaw = HIGH - 50
            # --center: defaults already right

            ch = [clamp(thr), clamp(roll), clamp(pitch), clamp(yaw), mode_us]
            pkt = b"PPM1" + struct.pack("<BB", seq & 0xFF, len(ch)) \
                + struct.pack("<%dH" % len(ch), *ch)
            seq += 1
            if args.lossy <= 0 or random.random() * 100.0 >= args.lossy:
                sock.sendto(pkt, (args.target, args.port))

            if int(t * args.rate) % int(args.rate * 5) == 0:
                pass  # quiet steady-state
            time.sleep(period)
    except KeyboardInterrupt:
        print("\nstopped")


if __name__ == "__main__":
    main()
