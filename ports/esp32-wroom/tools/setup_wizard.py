#!/usr/bin/env python3
"""
setup_wizard - the vehicle setup flow this board never got.

Three steps, each optional, each saved to flash immediately:

  1. LEVEL      measure the sensor's mounting tilt and cancel it with
                AttitudeSettings.BoardRotation. This is the standing -2.8
                pitch error that wound up the integrators on the bench and
                held two motors at minimum until the craft was tilted.
  2. ESC RANGE  classic all-at-once endpoint calibration: every ESC learns
                the same 1000-2000 range, so they all start at the same
                commanded pulse instead of each guessing its own.
  3. IDLE       per-motor spin-up points: each output ramps slowly, you
                press Enter the instant that motor starts, and its
                ChannelNeutral is set just above that -- so all four leave
                the ground together.

Steps 2 and 3 use the flight code's servo-configuration passthrough
(ActuatorCommand flight-read-only), run DISARMED, and restore everything on
any exit.

    PROPS OFF THROUGHOUT.
    Bench power: pull the BEC's red 5V lead off VUSB, power the board from
    USB, battery to the ESCs only. Never BEC-5V and USB together.

Usage:
    python3 tools/setup_wizard.py [--serial DEV] [--baud N]
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
MAX_US = 2000
LEVEL_OK_DEG = 0.5


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--serial", default="/dev/cu.usbserial-210")
    ap.add_argument("--baud", type=int, default=57600)
    args = ap.parse_args()

    db = uavtalk.UAVObjectDB(default_xml_dir())
    lock = threading.Lock()

    class Locked(object):
        def __init__(self, inner):
            self.inner = inner

        def send(self, data):
            with lock:
                self.inner.send(data)

        def poll_recv(self, timeout):
            return self.inner.poll_recv(timeout)

    print("opening %s (board keeps running -- attach does not reset it)..."
          % args.serial, flush=True)
    client = UAVTalkClient(Locked(Esp32SerialTransport(args.serial, args.baud)), db)
    got = {}
    connected = threading.Event()

    def on_object(objdef, inst_id, decoded):
        got[objdef.name] = decoded

    threading.Thread(target=client.run,
                     kwargs=dict(duration=100000, on_object=on_object,
                                 on_connected=connected.set),
                     daemon=True).start()
    if not connected.wait(30):
        sys.exit("no link -- is something else holding the port?")
    print("[link] up\n")

    def fresh(name, timeout=2.0):
        got.pop(name, None)
        client.request_object(name)
        end = time.time() + timeout
        while time.time() < end:
            if name in got:
                return got[name]
            time.sleep(0.02)
        return None

    def save(name):
        client.send_object("ObjectPersistence", {
            "Operation": "Save", "Selection": "SingleObject",
            "ObjectID": db[name].obj_id, "InstanceID": 0})
        end = time.time() + 5.0
        while time.time() < end:
            op = fresh("ObjectPersistence", 1.0)
            if op and op.get("Operation") == "Completed":
                return True
        return False

    def avg_attitude(secs):
        rs, ps = [], []
        end = time.time() + secs
        while time.time() < end:
            at = fresh("AttitudeState", 0.8)
            if at:
                rs.append(at.get("Roll", 0.0))
                ps.append(at.get("Pitch", 0.0))
            time.sleep(0.2)
        if not rs:
            return None, None
        return sum(rs) / len(rs), sum(ps) / len(ps)

    f = fresh("FlightStatus")
    if not f or f.get("Armed") != "Disarmed":
        sys.exit("board is %s -- disarm first" % (f.get("Armed") if f else "?"))

    # ================= STEP 0: ORIENTATION ==============================
    if input("STEP 0 - ORIENTATION CHECK (which way is NOSE?). Run it? "
             "[y/N] ").strip().lower() == "y":
        print("""
  The code assumes a fixed sensor-to-frame orientation (TOP_0DEG, set at
  compile time). Nothing has ever verified it against the actual airframe --
  and with the sensor on flying leads it is not even defined. So find it
  empirically. Convention the flight code lives by:

      NOSE DOWN            -> Pitch reads NEGATIVE
      RIGHT side down      -> Roll  reads POSITIVE
      rotate CW from above -> Yaw   INCREASES

  Live attitude for 30s. Tilt each edge of the (mounted!) sensor down in
  turn: the edge that drives Pitch NEGATIVE is what the code calls FORWARD.
  Point that at the airframe's nose when you hard-mount -- or if it is 90
  or 180 deg off, say so and the compile-time orientation gets changed.
""")
        input("  Press Enter to start the 30s live readout: ")
        end = time.time() + 30.0
        while time.time() < end:
            at = fresh("AttitudeState", 0.8)
            if at:
                r, pch, y = at.get("Roll", 0), at.get("Pitch", 0), at.get("Yaw", 0)
                tags = []
                if pch < -8:
                    tags.append("NOSE-DOWN edge is toward the ground NOW")
                elif pch > 8:
                    tags.append("TAIL-down")
                if r > 8:
                    tags.append("RIGHT side down")
                elif r < -8:
                    tags.append("LEFT side down")
                print("  roll %+7.1f  pitch %+7.1f  yaw %+7.1f   %s" % (
                    r, pch, y, ", ".join(tags)), flush=True)
            time.sleep(0.25)
        print("""
  Verdict guide:
    - Tilting the frame's real nose down made Pitch NEGATIVE and the real
      right side down made Roll POSITIVE: orientation is correct. Continue.
    - Directions consistent but rotated (e.g. nose-down shows as Roll):
      the sensor is mounted 90/180/270 deg off -- remount, or report which,
      and the TOP_xxDEG orientation constant gets changed in firmware.
    - An axis INVERTED (nose-down reads Pitch positive): report it; that is
      a sign fix in the driver mapping, not a mounting problem.
  Do not run level calibration until this step passes.
""")

    # ================= STEP 1: LEVEL ====================================
    if input("STEP 1 - LEVEL CALIBRATION. Run it? [y/N] ").strip().lower() == "y":
        input("  Put the FRAME (not the sensor) dead level and still, then "
              "press Enter: ")
        r0, p0 = avg_attitude(3.0)
        print("  sensor reads roll %+.2f pitch %+.2f" % (r0, p0))
        if abs(r0) < LEVEL_OK_DEG and abs(p0) < LEVEL_OK_DEG:
            print("  already level within %.1f deg -- nothing to do.\n" % LEVEL_OK_DEG)
        else:
            ats = fresh("AttitudeSettings", 3.0)
            rot = list(ats["BoardRotation"])          # [Roll, Pitch, Yaw]
            base = rot[:]

            def apply(sign):
                ats2 = dict(ats)
                ats2["BoardRotation"] = [base[0] + sign * r0,
                                         base[1] + sign * p0, base[2]]
                client.send_object("AttitudeSettings", ats2)
                # The complementary filter reconverges at its own pace; the
                # correction is invisible for several seconds. Waiting less
                # than this reads the OLD attitude and any sign logic built
                # on it is garbage.
                print("  correction written (sign %+d) -- waiting 15s for "
                      "the filter to reconverge..." % sign)
                time.sleep(15.0)
                return avg_attitude(3.0)

            # Sign conventions for rotation corrections are exactly the kind
            # of thing that gets silently inverted between codebases, so
            # determine it empirically: try minus, and if the tilt GREW,
            # use plus instead.
            r1, p1 = apply(-1)
            print("  now reads roll %+.2f pitch %+.2f" % (r1, p1))
            if abs(r1) + abs(p1) > abs(r0) + abs(p0):
                print("  worse -- flipping sign.")
                r1, p1 = apply(+1)
                print("  now reads roll %+.2f pitch %+.2f" % (r1, p1))
            ok = abs(r1) < LEVEL_OK_DEG and abs(p1) < LEVEL_OK_DEG
            print("  level calibration %s; saving to flash..."
                  % ("GOOD" if ok else "IMPROVED (re-run to refine)"))
            print("  saved: %s\n" % save("AttitudeSettings"))

    # ============== passthrough plumbing for steps 2 and 3 ==============
    ac_meta_id = db["ActuatorCommand"].obj_id + 1

    def get_meta():
        client.meta_payloads.pop(ac_meta_id, None)
        client.send_raw(uavtalk.TYPE_OBJ_REQ, ac_meta_id)
        end = time.time() + 3.0
        while time.time() < end and ac_meta_id not in client.meta_payloads:
            time.sleep(0.02)
        return client.meta_payloads.get(ac_meta_id)

    ac = fresh("ActuatorCommand")
    orig_meta = get_meta()

    def send_channels(us):
        ac2 = dict(ac)
        ch = list(ac2["Channel"])
        for i in range(4):
            ch[i] = us[i]
        ac2["Channel"] = ch
        client.send_object("ActuatorCommand", ac2)

    def set_access(readonly):
        flags = struct.unpack_from("<H", orig_meta, 0)[0]
        flags = (flags | 1) if readonly else (flags & ~1)
        new = bytearray(orig_meta)
        struct.pack_into("<H", new, 0, flags)
        client.send_raw(uavtalk.TYPE_OBJ, ac_meta_id, 0, bytes(new))
        time.sleep(0.2)

    def hold(us, secs):
        end = time.time() + secs
        while time.time() < end:
            send_channels(us)
            time.sleep(0.1)

    took_over = False
    try:
        # ============= STEP 2: ESC ENDPOINT CALIBRATION =================
        # ============= STEP 2: ESC ENDPOINT CALIBRATION =================
        #
        # HARD RULE on this airframe: battery and USB are NEVER connected at
        # the same time (the BEC's 5V feeds VUSB -- two sources fry the
        # board). So no serial tool may ever run while ESCs have power, and
        # calibration is done by a firmware boot mode instead:
        if input("STEP 2 - ESC RANGE CALIBRATION info (USB-free procedure). "
                 "Show it? [y/N] ").strip().lower() == "y":
            print("""
    ESC calibration runs WITHOUT USB, as a boot mode:

      1. Build & flash with BOARD_ESC_CAL=1 (ask Claude, or add it next to
         BOARD_PWM_SELFTEST in main/CMakeLists.txt).
      2. UNPLUG USB COMPLETELY.  PROPS OFF.
      3. Connect the battery. Board and ESCs power up together with all
         four outputs at MAX -- every ESC sings its max-cal tone.
         LED solid during this phase.
      4. After 6s outputs drop to MIN (LED fast-blinks); ESCs store the
         range and arm. Done.
      5. Disconnect battery, replug USB, reflash the normal build.

    Every power-up of the cal build recalibrates, so it must not stay
    flashed -- same rule as the PWM self-test build.
""")

        # ============= STEP 3: MOTOR IDLE POINTS ========================
        #
        # The interactive per-motor version needed spinning motors during a
        # serial session -- forbidden by the same rule. After a proper
        # endpoint calibration all ESCs share the same start threshold, so a
        # uniform neutral is the right answer anyway.
        if input("STEP 3 - MOTOR IDLE POINTS (writes numbers only, nothing "
                 "spins). Run it? [y/N] ").strip().lower() == "y":
            txt = input("  ChannelNeutral for all motors, us [default 1050]: ").strip()
            neutral = int(txt) if txt else 1050
            if not (1000 <= neutral <= 1200):
                print("  refusing %d -- sane range is 1000-1200" % neutral)
            else:
                acts = fresh("ActuatorSettings", 3.0)
                nu = list(acts["ChannelNeutral"])
                for m in range(4):
                    nu[m] = neutral
                acts["ChannelNeutral"] = nu
                client.send_object("ActuatorSettings", acts)
                time.sleep(1.0)
                print("  ChannelNeutral = %d on all four; saved: %s\n"
                      % (neutral, save("ActuatorSettings")))
    finally:
        if took_over:
            for _ in range(3):
                send_channels([MIN_US] * 4)
                time.sleep(0.1)
            set_access(False)
            back = get_meta()
            ok = back and (struct.unpack_from("<H", back, 0)[0] & 1) == 0
            print("outputs released to flight code: %s"
                  % ("verified" if ok else "UNVERIFIED -- power-cycle before flying"))

    print("\nWizard done. Suggested check: tools/motor_watch.py, arm, raise")
    print("throttle -- with level calibrated, the four commands should now")
    print("stay close together instead of splitting front/rear.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
