#!/usr/bin/env python3
"""PPM-format stick input over UDP for the NinjaPilot realposix board.

Streams stick frames to the firmware's UDP receiver (port 9003), registered
as the PPM channel group - so with ManualControlSettings ChannelGroups=PPM
this IS the radio. Frame format (see pios_udp_rcvr.h):

    "PPM1" + seq(u8) + count(u8) + count x uint16le microseconds

CHANNEL MAP (9 channels) - the firmware interprets each PPM channel by the
function assigned to it in ManualControlSettings.ChannelNumber. Run
setup_udp_sticks.py to assign all nine:

    PPM ch | function     | Xbox source              | rest -> range
    -------+--------------+--------------------------+----------------
      1    | Throttle     | Left stick  Y (up=high)  | 1500 (springs)
      2    | Roll         | Right stick X            | 1500 center
      3    | Pitch        | Right stick Y (up=high)  | 1500 center
      4    | Yaw          | Left stick  X            | 1500 center
      5    | FlightMode   | LB / RB cycle 6 pos      | 1000..2000 step
      6    | Collective   | Left trigger  (0..full)  | 1000 -> 2000
      7    | Accessory0   | Right trigger (0..full)  | 1000 -> 2000
      8    | Accessory1   | A button (toggle)        | 1000 <-> 2000
      9    | Accessory2   | X button (toggle)        | 1000 <-> 2000

ARM gesture on a gamepad: hold the LEFT stick DOWN + RIGHT (throttle low +
yaw right). Disarm: throttle low + yaw left. (Left stick springs to center,
so throttle rests at mid - hold it down to keep throttle low for arming.)

Modes:
  --center          neutral sticks, throttle low, accessories neutral
  --pattern         slow sinusoid sweeps on roll/pitch/yaw
  --arm             center, then throttle-low + yaw-right ~3s, back to center
  --joystick        gamepad via pygame (SDL GameController; pip install pygame)
  --lossy P         drop P% of frames randomly (INPUT orange demo)
  --stop-after S    exit after S seconds (INPUT red demo)

One client per PORT: 9003 coexists with a GCS on 9000.
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
NUM_CH = 9
MID, LOW, HIGH = 1500, 1000, 2000
DEADZONE = 0.08          # ignore tiny stick noise around center
FLIGHTMODE_POSITIONS = 6  # LB/RB cycle 1..6 across 1000..2000


def clamp(v):
    return max(900, min(2100, int(v)))


def dz(v):
    """apply a small deadzone to a -1..1 axis value"""
    return 0.0 if abs(v) < DEADZONE else v


class Pad:
    """Xbox pad via SDL's GameController API (named axes, controller-agnostic),
    falling back to raw joystick axis indices if the mapping is unavailable."""
    def __init__(self):
        import pygame
        self.pygame = pygame
        pygame.init()
        self.ctrl = None
        self.js = None
        try:
            from pygame._sdl2 import controller
            controller.init()
            if controller.get_count() > 0 and controller.is_controller(0):
                self.ctrl = controller.Controller(0)
                self.name = self.ctrl.name
        except Exception:
            self.ctrl = None
        if self.ctrl is None:
            pygame.joystick.init()
            if pygame.joystick.get_count() == 0:
                raise SystemExit("no gamepad found (pygame sees 0 joysticks)")
            self.js = pygame.joystick.Joystick(0)
            self.js.init()
            self.name = self.js.get_name()
        self.acc1 = False   # A-button toggle
        self.acc2 = False   # X-button toggle
        self.mode_pos = 0   # 0..FLIGHTMODE_POSITIONS-1
        self._lb_prev = self._rb_prev = self._a_prev = self._x_prev = False

    def api(self):
        return "SDL GameController (named axes)" if self.ctrl else "raw joystick axes"

    def _caxis(self, name):
        # GameController axes are int16 (-32768..32767); triggers 0..32767
        pg = self.pygame
        idx = getattr(pg, "CONTROLLER_AXIS_" + name)
        return self.ctrl.get_axis(idx) / 32768.0

    def _cbtn(self, name):
        pg = self.pygame
        idx = getattr(pg, "CONTROLLER_BUTTON_" + name)
        return bool(self.ctrl.get_button(idx))

    def read(self):
        """return dict of normalized inputs regardless of backend."""
        self.pygame.event.pump()
        if self.ctrl:
            lx, ly = self._caxis("LEFTX"), self._caxis("LEFTY")
            rx, ry = self._caxis("RIGHTX"), self._caxis("RIGHTY")
            lt = (self._caxis("TRIGGERLEFT") + 1) / 2.0 if False else max(0.0, self._caxis("TRIGGERLEFT"))
            rt = max(0.0, self._caxis("TRIGGERRIGHT"))
            lb, rb = self._cbtn("LEFTSHOULDER"), self._cbtn("RIGHTSHOULDER")
            a, x = self._cbtn("A"), self._cbtn("X")
        else:
            # raw fallback: common Xbox order LX0 LY1 LT2 RX3 RY4 RT5
            g = self.js
            n = g.get_numaxes()
            lx = g.get_axis(0) if n > 0 else 0.0
            ly = g.get_axis(1) if n > 1 else 0.0
            rx = g.get_axis(3) if n > 3 else 0.0
            ry = g.get_axis(4) if n > 4 else 0.0
            lt = max(0.0, g.get_axis(2)) if n > 2 else 0.0
            rt = max(0.0, g.get_axis(5)) if n > 5 else 0.0
            nb = g.get_numbuttons()
            lb = bool(g.get_button(4)) if nb > 4 else False
            rb = bool(g.get_button(5)) if nb > 5 else False
            a = bool(g.get_button(0)) if nb > 0 else False
            x = bool(g.get_button(2)) if nb > 2 else False
        # edge-triggered toggles / cyclers
        if lb and not self._lb_prev:
            self.mode_pos = max(0, self.mode_pos - 1)
        if rb and not self._rb_prev:
            self.mode_pos = min(FLIGHTMODE_POSITIONS - 1, self.mode_pos + 1)
        if a and not self._a_prev:
            self.acc1 = not self.acc1
        if x and not self._x_prev:
            self.acc2 = not self.acc2
        self._lb_prev, self._rb_prev, self._a_prev, self._x_prev = lb, rb, a, x
        return dict(lx=dz(lx), ly=dz(ly), rx=dz(rx), ry=dz(ry), lt=lt, rt=rt)

    def channels(self):
        v = self.read()
        thr = MID - v["ly"] * 500          # left Y up (=-1) -> high
        roll = MID + v["rx"] * 500
        pitch = MID - v["ry"] * 500         # right Y up (=-1) -> high pitch
        yaw = MID + v["lx"] * 500
        fm = LOW + int(self.mode_pos * (1000.0 / (FLIGHTMODE_POSITIONS - 1)))
        collective = LOW + int(v["lt"] * 1000)
        acc0 = LOW + int(v["rt"] * 1000)
        acc1 = HIGH if self.acc1 else LOW
        acc2 = HIGH if self.acc2 else LOW
        return [clamp(thr), clamp(roll), clamp(pitch), clamp(yaw), fm,
                clamp(collective), clamp(acc0), acc1, acc2]


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
    ap.add_argument("--show", action="store_true", help="print live channel values")
    args = ap.parse_args()

    pad = None
    if args.joystick:
        try:
            pad = Pad()
        except ImportError:
            sys.exit("--joystick needs pygame: pip install pygame")
        print(f"gamepad: {pad.name}  [{pad.api()}]")
        print("  ch1 Throttle=LeftY  ch2 Roll=RightX  ch3 Pitch=RightY  ch4 Yaw=LeftX")
        print("  ch5 FlightMode=LB/RB(6pos)  ch6 Collective=LT  ch7 Acc0=RT")
        print("  ch8 Acc1=A(toggle)  ch9 Acc2=X(toggle)")
        print("  ARM: hold LEFT stick DOWN+RIGHT (thr low + yaw right); DISARM: DOWN+LEFT")
        args.show = True
    elif not (args.center or args.pattern or args.arm):
        args.center = True

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    seq = 0
    t0 = time.time()
    period = 1.0 / args.rate
    last_show = 0.0

    print(f"streaming {args.rate:.0f} Hz PPM ({NUM_CH} ch) to {args.target}:{args.port}"
          + (f" with {args.lossy:.0f}% synthetic loss" if args.lossy else ""))

    try:
        while True:
            t = time.time() - t0
            if args.stop_after and t > args.stop_after:
                print(f"stopping after {t:.1f}s (failsafe/red demo)")
                break

            if pad is not None:
                ch = pad.channels()
            else:
                thr, roll, pitch, yaw = LOW, MID, MID, MID
                if args.pattern:
                    roll = MID + 300 * math.sin(t * 0.8)
                    pitch = MID + 300 * math.sin(t * 0.6 + 1.0)
                    yaw = MID + 200 * math.sin(t * 0.4 + 2.0)
                elif args.arm and 2.0 < t < 5.0:
                    yaw = HIGH - 50
                # 9 channels; accessories/collective neutral
                ch = [clamp(thr), clamp(roll), clamp(pitch), clamp(yaw),
                      LOW, LOW, LOW, LOW, LOW]

            pkt = b"PPM1" + struct.pack("<BB", seq & 0xFF, len(ch)) \
                + struct.pack("<%dH" % len(ch), *ch)
            seq += 1
            if args.lossy <= 0 or random.random() * 100.0 >= args.lossy:
                sock.sendto(pkt, (args.target, args.port))

            if args.show and t - last_show > 0.2:
                last_show = t
                labels = ["Thr", "Roll", "Pit", "Yaw", "FM", "Col", "A0", "A1", "A2"]
                line = "  ".join(f"{l}:{v}" for l, v in zip(labels, ch))
                print("\r" + line + "   ", end="", flush=True)

            time.sleep(period)
    except KeyboardInterrupt:
        print("\nstopped")


if __name__ == "__main__":
    main()
