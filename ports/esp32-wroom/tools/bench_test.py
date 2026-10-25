#!/usr/bin/env python3
"""
bench_test - supervised props-OFF bench characterization, driven by the tool.

You hold the quad and tilt/roll it gently in all directions; this tool owns
the throttle: it applies the recommended settings, temporarily takes control
(GCS receiver mapping, in RAM ONLY - a power cycle restores your DSM no
matter what), arms with the yaw-right gesture, walks the throttle from idle to max
over ~2 minutes with periodic HOLD-STILL windows, and samples the whole
chain: gyro, attitude, accel, and per-motor PWM.

What it grades:
  gyro vs attitude     the estimate must follow the gyro (sign + gain)
  accel vs attitude    the estimate must agree with gravity (a vibration-
                       walked estimate shows up here, live)
  motor response       tilt a side down -> that side's motors must rise
                       (pitch: front pair vs rear; roll: left pair vs right)
  vibration vs rpm     gyro/accel high-frequency noise per throttle step,
                       measured in the HOLD-STILL windows (flags resonant
                       throttle bands; with the 41Hz DLPF this stays low)

  Before arming it runs an ORIENTATION GATE: tip the airframe's nose down
  and press Enter - the board must read NOSE DOWN (same for the left arm).
  A board that reads the opposite is mounted 180 deg from the airframe and
  would flip at liftoff; the tool refuses to arm and tells you the fix.

  Rows are labeled from the moment each prompt is actually SPOKEN plus a
  1 s reaction allowance, so a slow `say` queue cannot mislabel your hands.
  Your radio can be on or off: every non-GCS channel group is parked on
  None for the run. Afterwards: python3 bench_report.py <the jsonl>.

  PROPS OFF. Battery power (never USB with battery). No GCS, no
  flight_monitor running. Type PROPS OFF at the prompt to begin.

    python3 bench_test.py [--host 192.168.0.45] [--max 0.90] [--time 100]
    python3 bench_test.py --paced        # you press Enter to start each phase
    python3 bench_test.py --quick        # one cycle at 15%: which motor pair rises per tilt
"""

import argparse
import json
import math
import os
import queue
import subprocess
import sys
import threading
import time

# --- voice guidance (macOS `say`): your hands are on the quad ---------------
_say_q = queue.Queue()
_say_enabled = [True]


_spoken_at = {}   # tag -> wall time the worker actually STARTED speaking it


def _say_worker():
    while True:
        item = _say_q.get()
        if item is None:
            return
        msg, tag = item
        if tag is not None:
            _spoken_at[tag] = time.time()
        if _say_enabled[0]:
            try:
                subprocess.run(["say", msg], timeout=15)
            except Exception:
                _say_enabled[0] = False


def say(msg, tag=None):
    """Queue a prompt. A `tag` lets the caller learn when the words really
    started (_spoken_at[tag]). `say` takes 1-3 s per prompt and the queue
    runs behind the scheduler; the 2026-09-01 23:54 log showed the pilot's
    hands ~2 s behind the row labels for exactly that reason, which graded
    a perfectly good estimator as FAIL on two axes."""
    print("[voice] %s" % msg, flush=True)
    _say_q.put((msg, tag))


threading.Thread(target=_say_worker, daemon=True).start()

_HERE = os.path.dirname(os.path.abspath(__file__))
NINJAPILOT_ROOT = os.environ.get(
    "NINJAPILOT_ROOT",
    os.path.abspath(os.path.join(_HERE, "..", "..", "NinjaPilot-15.02.ninja")))
sys.path.insert(0, os.path.join(NINJAPILOT_ROOT, "ground", "pyuavtalk"))
import uavtalk  # noqa: E402
from uavtalk_client import UdpTransport, UAVTalkClient, default_xml_dir  # noqa: E402
import flight_config as bov  # noqa: E402


ALARM_NAMES = ["SystemConfiguration", "BootFault", "OutOfMemory", "StackOverflow",
               "CPUOverload", "EventSystem", "Telemetry", "Receiver", "ManualControl",
               "Actuator", "Attitude", "Sensors", "Magnetometer", "Airspeed",
               "Stabilization", "Guidance", "PathPlan", "Battery", "FlightTime",
               "I2C", "GPS"]


def corr(xs, ys):
    n = len(xs)
    if n < 8:
        return None
    mx, my = sum(xs) / n, sum(ys) / n
    sx = math.sqrt(sum((x - mx) ** 2 for x in xs))
    sy = math.sqrt(sum((y - my) ** 2 for y in ys))
    if sx < 1e-9 or sy < 1e-9:
        return None
    return sum((x - mx) * (y - my) for x, y in zip(xs, ys)) / (sx * sy)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--host", default="192.168.0.45")
    ap.add_argument("--port", type=int, default=9000)
    ap.add_argument("--max", type=float, default=0.90)
    ap.add_argument("--time", type=float, default=100.0)
    ap.add_argument("--skip-apply", action="store_true",
                    help="skip applying the recommended settings first")
    ap.add_argument("--quiet", action="store_true", help="no voice prompts")
    ap.add_argument("--paced", action="store_true",
                    help="Enter-paced: stepped throttle (15/35/55/75/max %%), each "
                         "phase starts when YOU press Enter and is sampled for its "
                         "full duration - labels cannot lag your hands and the "
                         "still windows are truly still (--time is ignored)")
    ap.add_argument("--quick", action="store_true",
                    help="one paced cycle at 15%% throttle only (~1 min after arming): "
                         "confirms which motor PAIR rises for each tilt, spoken, so you "
                         "can see that the mixer's 'front' is the airframe's nose")
    ap.add_argument("--sim-sensors", action="store_true",
                    help="SIM ONLY: also feed level GyroSensor/AccelSensor so the "
                         "simwroom twin's attitude converges and it outputs PWM "
                         "(real hardware has real sensors - do not use there)")
    args = ap.parse_args()
    if args.quick:
        args.paced = True
    if args.quiet:
        _say_enabled[0] = False

    print(__doc__.split("What it grades")[0])
    if input("type PROPS OFF to begin: ").strip().upper() != "PROPS OFF":
        sys.exit("aborted - props confirmation not given")
    _enter_q = queue.Queue()   # every later Enter lands here (orientation gate, --paced)

    def _stdin_reader():
        for _line in sys.stdin:
            _enter_q.put(1)
    threading.Thread(target=_stdin_reader, daemon=True).start()

    def wait_enter(timeout):
        while not _enter_q.empty():          # only presses AFTER the prompt count
            _enter_q.get()
        t_end = time.time() + timeout
        while time.time() < t_end:
            if not _enter_q.empty():
                while not _enter_q.empty():
                    _enter_q.get()
                return True
            time.sleep(0.05)
        return False

    db = uavtalk.UAVObjectDB(default_xml_dir())
    client = UAVTalkClient(UdpTransport(args.host, args.port), db)
    latest = {}
    lock = threading.Lock()
    connected = {"ok": False}

    def on_object(objdef, inst_id, decoded):
        with lock:
            latest[objdef.name] = (time.time(), decoded)

    threading.Thread(target=lambda: client.run(on_object=on_object,
                                               on_connected=lambda: connected.update(ok=True),
                                               duration=100000), daemon=True).start()
    deadline = time.time() + 10
    while not connected["ok"] and time.time() < deadline:
        time.sleep(0.1)
    if not connected["ok"]:
        sys.exit("no link - board up? GCS closed?")
    print("[link] connected")

    def get(name):
        with lock:
            e = latest.get(name)
        return dict(e[1]) if e else None

    def fetch(name, timeout=5.0):
        with lock:
            latest.pop(name, None)
        o = db[name]
        end = time.time() + timeout
        while time.time() < end:
            client.transport.send(uavtalk.build_packet(uavtalk.TYPE_OBJ_REQ, o.obj_id, 0))
            for _ in range(10):
                v = get(name)
                if v is not None:
                    return v
                time.sleep(0.05)
        sys.exit("could not read %s" % name)

    def _approx(a, b):
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
        client.send_object(name, values)
        time.sleep(0.25)
        back = fetch(name)
        for k in check_keys:
            if not _approx(back.get(k), values.get(k)):
                sys.exit("VERIFY FAILED %s.%s: wrote %r, board has %r"
                         % (name, k, values.get(k), back.get(k)))
        return back

    def save(name):
        o = db[name]
        with lock:
            latest.pop("ObjectPersistence", None)
        client.send_object("ObjectPersistence", {"Operation": "Save",
                                                 "Selection": "SingleObject",
                                                 "ObjectID": o.obj_id, "InstanceID": 0})
        end = time.time() + 5.0
        while time.time() < end:
            got = get("ObjectPersistence")
            if got and got.get("Operation") in ("Completed", "Error"):
                if got["Operation"] == "Error":
                    sys.exit("board ERROR saving %s" % name)
                return
            time.sleep(0.1)
        sys.exit("no save confirmation for %s" % name)

    # ---- 1. apply the recommended settings (persisted) -------------------
    if not args.skip_apply:
        print("[apply] recommended settings...")
        bank = fetch("StabilizationSettingsBank1")
        bank["RollRatePID"] = [0.0032, 0.0075, 0.00005, bank["RollRatePID"][3]]
        bank["PitchRatePID"] = [0.0032, 0.0075, 0.00005, bank["PitchRatePID"][3]]
        bank["RollPI"] = [3.2, bank["RollPI"][1], bank["RollPI"][2]]
        bank["PitchPI"] = [3.2, bank["PitchPI"][1], bank["PitchPI"][2]]
        write_verify("StabilizationSettingsBank1", bank, ["RollRatePID", "PitchPI"])
        save("StabilizationSettingsBank1")
        fms0 = fetch("FlightModeSettings")
        for slot in (1, 2, 3):
            m = list(fms0["Stabilization%dSettings" % slot])
            if m[2] == "AxisLock":
                m[2] = "Rate"
            fms0["Stabilization%dSettings" % slot] = m
        write_verify("FlightModeSettings", fms0, ["Stabilization1Settings"])
        save("FlightModeSettings")
        act = fetch("ActuatorSettings")
        act["MotorsSpinWhileArmed"] = "TRUE"
        write_verify("ActuatorSettings", act, ["MotorsSpinWhileArmed"])
        save("ActuatorSettings")
        print("[apply] done (persisted)")

    # ---- 2. take control: GCS receiver mapping, RAM ONLY -----------------
    mcs_orig = fetch("ManualControlSettings")
    fms_orig = fetch("FlightModeSettings")
    print("[ctrl] remapping receiver to GCS, other groups parked on None (RAM")
    print("       only - a power cycle restores your DSM unconditionally)")
    mcs = dict(mcs_orig)
    # Every group past the first five (Collective, Accessory0-2) is parked on
    # None for the duration. receiver.c range-checks ANY channel whose group
    # is not None, so leaving an Accessory on DSM with the transmitter off
    # returns PIOS_RCVR_TIMEOUT for it and invalidates the whole input
    # (Connected=False, Receiver=Warning) even though the GCS sticks are
    # fine. That is exactly what happened on the 2026-09-01 23:4x run.
    n_ch = len(mcs_orig["ChannelGroups"])
    mcs["ChannelGroups"] = ["GCS"] * 5 + ["None"] * (n_ch - 5)
    mcs["ChannelNumber"] = [1, 2, 3, 4, 5] + [0] * (n_ch - 5)
    mcs["ChannelMin"] = [1000] * 5 + list(mcs_orig["ChannelMin"][5:])
    mcs["ChannelNeutral"] = [1050, 1500, 1500, 1500, 1500] + list(mcs_orig["ChannelNeutral"][5:])
    mcs["ChannelMax"] = [2000] * 5 + list(mcs_orig["ChannelMax"][5:])
    write_verify("ManualControlSettings", mcs, ["ChannelGroups"])

    outpath = os.path.expanduser("~/NinjaPilot-logs/bench_%s.jsonl"
                                 % time.strftime("%Y-%m-%d_%H-%M-%S"))
    out = open(outpath, "w")
    t0 = time.time()
    throttle = [0.0]
    stop = threading.Event()
    n_modes = 6 if True else 5

    yaw_cmd = [1500]   # 2000 = full yaw right (arming gesture), 1500 = neutral

    def gcs_channels():
        thr_us = int(1000 + max(0.0, throttle[0]) * 1000)
        return [thr_us, 1500, 1500, yaw_cmd[0], bov.flight_mode_channel(0, 6), 1500, 1500, 1500]

    def stick_pump():
        # GCSReceiver keepalive at 20Hz (the 100ms receiver supervisor) with
        # sensor polls interleaved, never back-to-back
        polls = ["GyroState", "AccelState", "ActuatorCommand", "FlightStatus"]
        i = 0
        while not stop.is_set():
            client.send_object("GCSReceiver", {"Channel": gcs_channels()})
            time.sleep(0.02)
            o = db[polls[i % len(polls)]]
            client.transport.send(uavtalk.build_packet(uavtalk.TYPE_OBJ_REQ, o.obj_id, 0))
            i += 1
            time.sleep(0.02)

    sim_tilt = {"roll": 0.0, "pitch": 0.0}  # deg, set by the choreography

    def sensor_pump():
        # SIM ONLY: GyroSensor/AccelSensor at ~400Hz so the attitude queue
        # (5x sensor period timeout) stays fed and the CC filter converges.
        # Same client as everything else - no peer-latch fight. When the
        # choreography sets sim_tilt, the accel gravity vector tilts with it
        # so the grader's tilt->motor checks exercise for real in sim.
        import math as _m
        gyro_o, acc_o = db["GyroSensor"], db["AccelSensor"]
        # The synthetic airframe slews toward sim_tilt at a hand-like rate and
        # the gyro reports THAT rate, so the complementary filter integrates
        # into the tilt within half a second the way it does on real hands
        # (accel alone, at AccelKp 0.05, only crawls there over ~10 s - the
        # 2026-09-02 00:33 sim self-test scored 'nose up' +5.7 deg for that
        # reason). Signs match the real 23:54 log: gyro.y > 0 raises pitch,
        # gyro.x > 0 raises roll; nose down -> acc.x < 0; roll right -> acc.y < 0.
        cur = {"roll": 0.0, "pitch": 0.0}
        SLEW = 60.0   # deg/s
        last_t = time.time()
        while not stop.is_set():
            now_t = time.time()
            dt = max(1e-4, now_t - last_t)
            last_t = now_t
            rate = {}
            for ax_name in ("roll", "pitch"):
                err = sim_tilt[ax_name] - cur[ax_name]
                step = max(-SLEW * dt, min(SLEW * dt, err))
                cur[ax_name] += step
                rate[ax_name] = step / dt
            r = _m.radians(cur["roll"])
            p_ = _m.radians(cur["pitch"])
            ax = _m.sin(p_) * 9.81
            ay = -_m.sin(r) * 9.81
            az = -_m.cos(r) * _m.cos(p_) * 9.81
            client.transport.send(uavtalk.build_packet(uavtalk.TYPE_OBJ, gyro_o.obj_id, 0,
                gyro_o.pack({"x": rate["roll"], "y": rate["pitch"], "z": 0.0, "temperature": 25.0})))
            client.transport.send(uavtalk.build_packet(uavtalk.TYPE_OBJ, acc_o.obj_id, 0,
                acc_o.pack({"x": ax, "y": ay, "z": az, "temperature": 25.0})))
            time.sleep(0.0025)
    pump = threading.Thread(target=stick_pump, daemon=True)
    pump.start()
    if args.sim_sensors:
        threading.Thread(target=sensor_pump, daemon=True).start()
    time.sleep(1.0)

    # ---- 3. the ramp, voice-directed --------------------------------------
    samples = []
    say("Bench test ready.")
    time.sleep(2.5)
    say("Hold the quad level. Props off?")
    time.sleep(3.5)

    # Confirm the GCS receiver is actually feeding control BEFORE arming -
    # this is the check whose absence let the old version narrate a state
    # that never happened. If throttle is not reaching the flight side the
    # yaw-right arming gesture cannot be seen either.
    mcc = fetch("ManualControlCommand")
    thr_in = mcc.get("Throttle")
    conn = mcc.get("Connected")
    print("[check] ManualControlCommand: Throttle=%s Connected=%s" % (thr_in, conn), flush=True)
    if conn not in ("True", True) or thr_in is None or float(thr_in) >= 0:
        alarms = fetch("SystemAlarms").get("Alarm", [])
        bad = [ALARM_NAMES[i] + "=" + v for i, v in enumerate(alarms)
               if i < len(ALARM_NAMES) and v not in ("OK", "Uninitialised")]
        say("Stop. The board is not receiving my throttle. Aborting.")
        print("[ABORT] GCS control not reaching the flight side.")
        print("        Throttle=%s (need < 0), Connected=%s" % (thr_in, conn))
        print("        alarms: %s" % (", ".join(bad) or "none"))
        # raw per-channel codes say WHICH channel the flight side rejects
        codes = {65535: "INVALID(no mapping)", 65534: "TIMEOUT(no data)",
                 65533: "NODRIVER(group unbound)"}
        raw = mcc.get("Channel", [])
        names = ["Throttle", "Roll", "Pitch", "Yaw", "FlightMode", "Collective",
                 "Accessory0", "Accessory1", "Accessory2"]
        for i, v in enumerate(raw[:len(names)]):
            grp = mcs["ChannelGroups"][i] if i < len(mcs["ChannelGroups"]) else "?"
            print("        %-10s group=%-5s raw=%s" % (names[i], grp, codes.get(int(v), v)))
        print("        TIMEOUT = the flight side never got a fresh value for that")
        print("        channel; INVALID/NODRIVER = firmware lacks the GCS receiver")
        print("        binding (firmware_normal_41hz.bin from 2026-09-01 or later).")
        try:
            write_verify("ManualControlSettings", mcs_orig, ["ChannelGroups"])
            print("        (your radio mapping has been restored)")
        except SystemExit:
            print("        (restore failed - power cycle to get your radio back)")
        raise SystemExit(1)

    # mixer/curve must be real or arming spins nothing (the simwroom sim's
    # own failure mode - a zero mixer produces zero PWM regardless)
    mix = fetch("MixerSettings")
    curve = mix.get("ThrottleCurve1", [])
    m1 = mix.get("Mixer1Vector", [0, 0, 0, 0, 0])
    if not any(float(c) > 0 for c in curve) or not any(v != 0 for v in m1[2:5]):
        say("Stop. The mixer is not configured. Aborting.")
        print("[ABORT] MixerSettings not usable - ThrottleCurve1=%s Mixer1Vector=%s"
              % ([round(float(c), 2) for c in curve], list(m1)))
        write_verify("ManualControlSettings", mcs_orig, ["ChannelGroups"])
        raise SystemExit(1)

    say("Receiver check good.")
    # Wait for the attitude estimator to finish calibrating - okToArm() (which
    # the real arm gesture runs) blocks while Attitude is Error/Critical, and
    # filtercf holds ~10s of calibration windows after boot. Same contract the
    # flight side enforces on a real transmitter arm.
    att_idx = ALARM_NAMES.index("Attitude")
    said_wait = False
    aend = time.time() + 20.0
    while time.time() < aend:
        al = get("SystemAlarms")
        if al and al.get("Alarm") and al["Alarm"][att_idx] == "OK":
            break
        if not said_wait:
            say("Waiting for the sensors to settle. Hold it still and level.")
            said_wait = True
        time.sleep(0.2)
    else:
        alv = (get("SystemAlarms") or {}).get("Alarm", [])
        att = alv[att_idx] if alv else "?"
        bad = [ALARM_NAMES[i] + "=" + v for i, v in enumerate(alv)
               if i < len(ALARM_NAMES) and v not in ("OK", "Uninitialised")]
        g = fetch("GyroState")
        gz = all(abs(float(g.get(k, 0.0))) < 1e-6 for k in ("x", "y", "z"))
        up_s = float(fetch("SystemStats").get("FlightTime", 0)) / 1000.0
        say("The attitude estimator did not become ready. Aborting.")
        print("[ABORT] Attitude alarm stuck at %s after 20s. alarms: %s (board up %.0f s)"
              % (att, ", ".join(bad) or "none", up_s))
        if gz:
            print("        GyroState is EXACTLY zero: the IMU has produced no samples since boot.")
            print("        Not vibration, not you. The ICM-20602 did not come up on this boot.")
        if any(b.startswith("BootFault") for b in bad):
            print("        BootFault=Critical: on THIS board that means the ICM-20602 did not answer")
            print("        WHO_AM_I over SPI at boot (4 tries), or its data-ready task/DSM failed to")
            print("        start (pios_board.c). The board boots anyway, reports it, refuses to arm.")
        print("        Fix: unplug the battery, wait 5 s, plug it in ONCE firmly (a lead that scrapes")
        print("        and bounces can catch the IMU mid-power-up), hands off 10 s, re-run. If it")
        print("        repeats on a clean boot: SPI3 leads SCLK=5 MOSI=18 MISO=19 CS=14 to the IMU.")
        write_verify("ManualControlSettings", mcs_orig, ["ChannelGroups"])
        raise SystemExit(1)
    time.sleep(1.0)

    # ---- gyro-bias gate: a board that moved in its first ~7 s after power-up
    # has LEARNED that motion as gyro bias (CC attitude init: accelKp 1,
    # bias rate 0.01/iter) and will drift its estimate for the whole session.
    # The 2026-09-02 01:28 bench had gyro.x -54 deg/s in every window: the
    # roll estimate wandered past 90 deg while the accel read the truth.
    # Only a power cycle with the quad MOTIONLESS clears it. Refuse to arm.
    say("Hold it still and level for three seconds.")
    time.sleep(1.0)
    gsum = [0.0, 0.0, 0.0]
    gn = 0
    for _ in range(8):
        g = fetch("GyroState")
        for i, k in enumerate(("x", "y", "z")):
            gsum[i] += float(g.get(k, 0.0))
        gn += 1
        time.sleep(0.25)
    gbias = [v / gn for v in gsum]
    up_ms = float(fetch("SystemStats").get("FlightTime", 0))
    print("[check] gyro at rest: x %+.1f y %+.1f z %+.1f deg/s   (board up %.0f s)"
          % (gbias[0], gbias[1], gbias[2], up_ms / 1000.0), flush=True)
    if max(abs(v) for v in gbias) > 4.0:
        # Not an abort: this is a STALE bias - learned at the end of the boot
        # window or at the last arming, then only trickled away by AccelKi
        # (0.0001: tens of minutes). It is not you moving it now. The arming
        # second re-zeros the gyros against the resting reading, and this
        # tool now arms with the quad flat and hands-off, so it is cured
        # below; the post-arm check is the one that enforces.
        say("The gyro carries %d degrees per second of old bias. Not a problem yet - "
            "arming will re-zero it while the quad sits flat." % int(max(abs(v) for v in gbias)))
        print("[WARN] stale gyro bias %s deg/s after %.0f s of uptime - learned earlier (boot"
              % ([round(v, 1) for v in gbias], up_ms / 1000.0))
        print("       window or last arming), NOT current motion. Arming flat/hands-off re-zeros it;")
        print("       the post-arm check below aborts if it does not.")

    # ---- orientation gate: the board's nose must be the AIRFRAME's nose ----
    # The 2026-09-02 00:59 paced run read every commanded tilt with the
    # opposite sign on both axes; the 23:54 run on the same board read them
    # right. Only the human reference can have changed between the two, and
    # the difference is not academic: a board whose +x points at the tail is
    # positive feedback on both axes on a correct mixer - it flips the instant
    # the wheels get light. Physical truth beats inference: ask, read, refuse.
    ORIENT = (("pitch", "Pitch", "NOSE DOWN", "NOSE UP",
               "Orientation check. Tip the airframe's nose down - the end you fly "
               "forward, where the old arrow pointed. Press Enter while holding it."),
              ("roll", "Roll", "LEFT SIDE DOWN", "RIGHT SIDE DOWN",
               "Now dip the left arm - left as seen from behind, flying forward. "
               "Press Enter while holding it."))
    for axis, key, name_neg, name_pos, prompt in ORIENT:
        say(prompt)
        if not wait_enter(60.0):
            say("No Enter. Skipping the orientation check.")
            print("[WARN] orientation check skipped on %s (no Enter)" % axis)
            break
        time.sleep(0.4)
        # gravity from the accelerometer, not the estimate: a stale gyro bias
        # walks the estimate (01:28 run: roll past 90 deg) but not the accel
        a = fetch("AccelState")
        ax, ay, az = float(a.get("x", 0)), float(a.get("y", 0)), float(a.get("z", -9.81))
        amag = max(1e-3, math.sqrt(ax * ax + ay * ay + az * az))
        if key == "Pitch":
            v = math.degrees(math.asin(max(-1.0, min(1.0, ax / amag))))
        else:
            v = math.degrees(math.atan2(-ay, -az))
        seen = name_neg if v < -8 else name_pos if v > 8 else "LEVEL"
        print("[check] orientation %s: you tipped %s, board reads %s (%+.0f deg)"
              % (axis, name_neg.lower(), seen, v), flush=True)
        if v > 8:
            say("Stop. The board reads %s. Its nose is not your nose. Aborting." % name_pos.lower())
            print("[ABORT] board orientation does not match the airframe on %s." % axis)
            print("        A board whose forward axis points at the tail is positive feedback")
            print("        on both axes and flips at liftoff. Fix the mount, or set")
            print("        AttitudeSettings.BoardRotation Yaw=180 (both axes inverted) /")
            print("        Roll or Pitch=180 (one axis inverted), save, power cycle, re-run.")
            print("        BoardRotation now: %s" % (fetch("AttitudeSettings").get("BoardRotation"),))
            write_verify("ManualControlSettings", mcs_orig, ["ChannelGroups"])
            raise SystemExit(1)
        if abs(v) <= 8:
            say("I did not see a tilt. Continuing, but check the orientation line.")
            print("[WARN] orientation %s: no clear tilt (%+.0f deg) - check it by hand" % (axis, v))
    say("Orientation good. Back to level.")
    time.sleep(1.0)

    # Real arm gesture: throttle low + yaw right held for ArmingSequenceTime
    # (~1s). This runs the SAME path a transmitter uses, including okToArm()'s
    # alarm gate - a better test than the Always-Armed bypass.
    fms = dict(fms_orig)
    fms["Arming"] = "Yaw Right"
    write_verify("FlightModeSettings", fms, ["Arming"])
    throttle[0] = 0.0
    # ZeroDuringArming (TRUE on this tree) re-learns gyro bias DURING the ~1 s
    # arming window with a 0.2 s time constant: whatever rate the quad has at
    # that moment becomes "bias" for the whole session. The 2026-09-02 01:28
    # run armed two seconds after the orientation gate's left-arm dip, while
    # the pilot was still rolling it back to level -> gyro.x -54 deg/s bias,
    # roll estimate past 90 deg all run. So: wait for a QUIET gyro first, tell
    # the pilot to freeze, and verify the bias again right after arming.
    say("Place the quad flat on the bench, hands off, then press Enter.")
    if not wait_enter(120.0):
        say("No Enter. Aborting.")
        print("[ABORT] no Enter after 'place it flat' - not arming")
        write_verify("ManualControlSettings", mcs_orig, ["ChannelGroups"])
        raise SystemExit(1)
    say("Do not touch it while I arm.")
    quiet_since = None
    q_end = time.time() + 30.0
    while time.time() < q_end:
        g = fetch("GyroState")
        if max(abs(float(g.get(k, 0.0))) for k in ("x", "y", "z")) < 3.0:
            quiet_since = quiet_since or time.time()
            if time.time() - quiet_since > 2.0:
                break
        else:
            quiet_since = None
        time.sleep(0.2)
    else:
        say("It never held still. Aborting.")
        print("[ABORT] gyro never quiet (< 3 deg/s for 2 s) within 30 s before arming")
        write_verify("ManualControlSettings", mcs_orig, ["ChannelGroups"])
        raise SystemExit(1)
    say("Arming. Stay still.")
    yaw_cmd[0] = 2000   # full yaw right; pump sends it every cycle
    armed = False
    end = time.time() + 6.0
    while time.time() < end:
        fs = get("FlightStatus")
        if fs and fs.get("Armed") == "Armed":
            armed = True
            break
        time.sleep(0.1)
    yaw_cmd[0] = 1500   # release the gesture the instant it arms
    if not armed:
        alarms = fetch("SystemAlarms").get("Alarm", [])
        bad = [ALARM_NAMES[i] + "=" + v for i, v in enumerate(alarms)
               if i < len(ALARM_NAMES) and v not in ("OK", "Uninitialised")]
        say("The board did not arm. Aborting.")
        print("[ABORT] yaw-right gesture did not arm within 6s. "
              "okToArm() blocks on any Critical alarm. alarms: %s"
              % (", ".join(bad) or "none"))
        write_verify("FlightModeSettings", fms_orig, ["Arming"])
        write_verify("ManualControlSettings", mcs_orig, ["ChannelGroups"])
        raise SystemExit(1)

    # confirm motors actually idle (MotorsSpinWhileArmed) before ramping
    time.sleep(0.5)
    # post-arm: did the arming window learn a bias anyway?
    time.sleep(0.5)
    gsum = [0.0, 0.0, 0.0]
    for _ in range(6):
        g = fetch("GyroState")
        for i, k in enumerate(("x", "y", "z")):
            gsum[i] += float(g.get(k, 0.0))
        time.sleep(0.2)
    gbias = [v / 6.0 for v in gsum]
    print("[check] gyro at rest after arming: x %+.1f y %+.1f z %+.1f deg/s" % tuple(gbias), flush=True)
    if max(abs(v) for v in gbias[:2]) > 4.0:
        say("Stop. The gyro learned %d degrees per second of bias while arming. Disarming."
            % int(max(abs(v) for v in gbias[:2])))
        print("[ABORT] gyro bias after arming %s deg/s (limit 4): the quad moved during the"
              % [round(v, 1) for v in gbias])
        print("        arming window (ZeroDuringArming). Disarming; hold it still next time.")
        try:
            dfms = dict(fms_orig)
            dfms["Arming"] = "Always Disarmed"
            write_verify("FlightModeSettings", dfms, ["Arming"])
            dend = time.time() + 3.0
            while time.time() < dend:
                fs = get("FlightStatus")
                if fs and fs.get("Armed") == "Disarmed":
                    break
                time.sleep(0.1)
            stop.set()
            time.sleep(0.2)
            write_verify("FlightModeSettings", fms_orig, ["Arming"])
            write_verify("ManualControlSettings", mcs_orig, ["ChannelGroups"])
            say("Disarmed. Your radio is back.")
        except SystemExit:
            say("Warning. Restore failed. Power cycle the board.")
        raise SystemExit(1)
    ac = fetch("ActuatorCommand").get("Channel", [0] * 4)[:4]
    print("[check] armed. idle ActuatorCommand: %s" % ac, flush=True)
    if not any(c > 1050 for c in ac):
        say("Armed, but motors are not idling. Continuing, watch closely.")
        print("[WARN] no idle PWM > 1050 - MotorsSpinWhileArmed may be off, "
              "or outputs disabled. PWM: %s" % ac)
    else:
        say("Armed. Motors idling. Beginning the ramp.")
    say("Follow my directions. Gentle tilts.")

    # repeating voice-directed motion cycle; each phase labels its samples
    CYCLE = [("nose_down", "Nose down.", 3.5),
             ("nose_up", "Nose up. Above level.", 3.5),
             ("roll_left", "Roll left.", 3.5),
             ("roll_right", "Roll right.", 3.5),
             ("level", "Level.", 2.0),
             ("still", None, 4.0)]  # announced with throttle percentage
    dur_of = {name: dur for name, _, dur in CYCLE}
    REACTION_S = 1.0    # hands need about this long after the words START
    paced = None
    if args.paced:
        lv = [0.15] if args.quick else sorted({round(x, 2) for x in (0.15, 0.35, 0.55, 0.75, args.max) if x <= args.max + 1e-6})
        paced = {"levels": lv, "level_i": 0, "step_i": 0, "mode": "announce",
                 "wait_t0": 0.0, "hold_until": 0.0}
        say("Paced mode. Each step waits for you to press Enter.")
    ramp_t0 = time.time()
    phase = ["level"]   # the label written to each row
    pending = [None]    # (name, tag, queued_at): spoken/queued, not yet reacted to
    cyc_i = [0]
    phase_until = [0.0]
    try:
        last_status = 0.0
        while True:
            now = time.time()
            el = now - ramp_t0
            if args.paced:
                # ---- Enter-paced: stepped throttle; each phase begins when
                # the pilot presses Enter and is sampled for its full
                # duration, so the label can never lead or lag the hands.
                if paced["mode"] == "done":
                    break
                tgt = paced["levels"][paced["level_i"]]
                throttle[0] += max(-0.01, min(0.01, tgt - throttle[0]))   # ~0.25/s glide
                name, prompt, dur = CYCLE[paced["step_i"]]
                if paced["mode"] == "announce":
                    if paced["step_i"] == 0:
                        say("Throttle %d percent." % int(tgt * 100))
                    if name == "still":
                        say("Next: hold still. Press Enter, then keep it still.")
                    else:
                        say("Next: %s Press Enter when you are there." % prompt)
                    phase[0] = "transition"
                    while not _enter_q.empty():      # only presses AFTER this prompt count
                        _enter_q.get()
                    paced["mode"], paced["wait_t0"] = "wait_enter", now
                elif paced["mode"] == "wait_enter":
                    pressed = False
                    while not _enter_q.empty():
                        _enter_q.get()
                        pressed = True
                    if pressed or now - paced["wait_t0"] > 45.0:
                        if not pressed:
                            say("No Enter. Moving on.")
                        phase[0] = name
                        paced["hold_until"] = now + dur
                        paced["mode"] = "hold"
                        say("Hold.")
                        if args.sim_sensors:
                            sim_tilt["roll"] = {"roll_left": -20.0, "roll_right": 20.0}.get(name, 0.0)
                            sim_tilt["pitch"] = {"nose_down": -20.0, "nose_up": 20.0}.get(name, 0.0)
                elif paced["mode"] == "hold" and now >= paced["hold_until"]:
                    # say which motor PAIR was high during this window, so the
                    # pilot can look at the airframe and confirm the mixer's
                    # idea of "front" is the nose (QuadX: M1 NW, M2 NE, M3 SE,
                    # M4 SW). Expected: nose down -> front, nose up -> rear,
                    # roll left -> left pair, roll right -> right pair.
                    win = [r for r in samples if r["phase"] == name and r["t"] > now - t0 - dur - 0.5]
                    if win and name in ("nose_down", "nose_up", "roll_left", "roll_right"):
                        mp = [sum(r["pwm"][i] for r in win) / len(win) for i in range(4)]
                        fr = (mp[0] + mp[1]) - (mp[2] + mp[3])
                        lr = (mp[0] + mp[3]) - (mp[1] + mp[2])
                        if name.startswith("nose"):
                            seen = "front" if fr > 40 else "rear" if fr < -40 else "no clear"
                            want = "front" if name == "nose_down" else "rear"
                        else:
                            seen = "left" if lr > 40 else "right" if lr < -40 else "no clear"
                            want = "left" if name == "roll_left" else "right"
                        verdict = "as expected" if seen == want else "NOT what the mixer expects" if seen != "no clear" else "too small to call"
                        print("[motors] %-10s %s pair high (M1 %.0f M2 %.0f M3 %.0f M4 %.0f) - %s"
                              % (name, seen, mp[0], mp[1], mp[2], mp[3], verdict), flush=True)
                        say("%s motors were high. %s." % (seen.capitalize(), verdict.replace("NOT", "not")))
                    phase[0] = "transition"
                    paced["step_i"] += 1
                    if paced["step_i"] >= len(CYCLE):
                        paced["step_i"] = 0
                        paced["level_i"] += 1
                        if paced["level_i"] >= len(paced["levels"]):
                            paced["mode"] = "done"
                            say("All levels done.")
                    if paced["mode"] != "done":
                        paced["mode"] = "announce"
            else:
                if el > args.time + 4.0:
                    break
                throttle[0] = min(args.max, args.max * el / args.time)
                # A prompt becomes the row label only REACTION_S after the words
                # actually started (the say queue may be seconds behind us), and
                # its window is timed from then. Rows in between are labeled
                # "transition" and excluded from the per-phase grades.
                if pending[0] is not None:
                    name, tag, queued_at = pending[0]
                    spoken = _spoken_at.get(tag)
                    if spoken is None and now - queued_at > 10.0:
                        spoken = now      # speech wedged: never stall the ramp
                    if spoken is not None and now - spoken >= REACTION_S:
                        phase[0] = name
                        phase_until[0] = spoken + REACTION_S + dur_of[name]
                        pending[0] = None
                        if args.sim_sensors:
                            sim_tilt["roll"] = {"roll_left": -20.0, "roll_right": 20.0}.get(name, 0.0)
                            sim_tilt["pitch"] = {"nose_down": -20.0, "nose_up": 20.0}.get(name, 0.0)
                if pending[0] is None and now >= phase_until[0]:
                    name, prompt, dur = CYCLE[cyc_i[0] % len(CYCLE)]
                    cyc_i[0] += 1
                    tag = "phase%d" % cyc_i[0]
                    pending[0] = (name, tag, now)
                    phase[0] = "transition"
                    if name == "still":
                        say("Hold still. %d percent." % int(throttle[0] * 100), tag=tag)
                    else:
                        say(prompt, tag=tag)
            att = get("AttitudeState") or {}
            gyro = get("GyroState") or {}
            acc = get("AccelState") or {}
            pwm = (get("ActuatorCommand") or {}).get("Channel", [0] * 4)[:4]
            row = {"t": round(now - t0, 3), "thr": round(throttle[0], 3),
                   "phase": phase[0],
                   "att": [att.get("Roll", 0), att.get("Pitch", 0), att.get("Yaw", 0)],
                   "gyro": [gyro.get("x", 0), gyro.get("y", 0), gyro.get("z", 0)],
                   "acc": [acc.get("x", 0), acc.get("y", 0), acc.get("z", 0)],
                   "pwm": pwm}
            samples.append(row)
            out.write(json.dumps(row) + "\n")
            if now - last_status > 2.0:
                last_status = now
                print("[%5.1fs] thr %4.0f%% att(%6.1f,%6.1f) gyro(%6.1f,%6.1f,%6.1f) pwm %s"
                      % (el, throttle[0] * 100, row["att"][0], row["att"][1],
                         row["gyro"][0], row["gyro"][1], row["gyro"][2], pwm), flush=True)
            time.sleep(0.04)
    except KeyboardInterrupt:
        say("Interrupted. Shutting down safely.")
    finally:
        say("Ramp complete. Throttle down.")
        throttle[0] = 0.0
        time.sleep(1.0)
        say("Disarming.")
        try:
            # force disarm explicitly, then hand the radio back
            dfms = dict(fms_orig)
            dfms["Arming"] = "Always Disarmed"
            write_verify("FlightModeSettings", dfms, ["Arming"])
            dend = time.time() + 3.0
            while time.time() < dend:
                fs = get("FlightStatus")
                if fs and fs.get("Armed") == "Disarmed":
                    break
                time.sleep(0.1)
        except SystemExit:
            pass
        stop.set()
        time.sleep(0.2)
        try:
            write_verify("FlightModeSettings", fms_orig, ["Arming"])
            write_verify("ManualControlSettings", mcs_orig, ["ChannelGroups"])
            say("Disarmed. Your radio is back. Test done. You can put the quad down.")
        except SystemExit:
            say("Warning. Restore failed. Power cycle the board to get your radio back.")
        out.close()
        time.sleep(4.0)  # let the last voice prompts finish

    # ---- 4. grades --------------------------------------------------------
    print("\n===== bench report ===== (%d samples, log %s)" % (len(samples), outpath))
    move = [s for s in samples if s["phase"] not in ("still",) and s["thr"] > 0.05]
    # per-stimulus compliance + mixer direction, from the labeled phases
    def phase_excursion(ph, fn, op):
        """Per labeled window, how far the estimate went in the commanded
        direction; mean over windows. Extremes, not means: a hand that is
        still moving at the start of the window must not drag the grade."""
        ext, cur = [], None
        for s in samples + [{"phase": None, "thr": 0}]:
            if s["phase"] == ph and 0.10 < s["thr"] < 0.90:
                cur = (cur or []) + [fn(s)]
            elif cur is not None:
                if len(cur) > 5:
                    ext.append(min(cur) if op == "<" else max(cur))
                cur = None
        return (sum(ext) / len(ext), len(ext)) if ext else (None, 0)
    checks = [
        ("nose_down", lambda s: s["att"][1], "<", -8, "estimate sees nose down"),
        ("nose_up", lambda s: s["att"][1], ">", 8, "estimate sees nose up (above level)"),
        ("roll_left", lambda s: s["att"][0], "<", -8, "estimate sees roll left"),
        ("roll_right", lambda s: s["att"][0], ">", 8, "estimate sees roll right"),
    ]
    # (mixer-response DIRECTION is graded robustly below by correlation over
    # all motion - "pitch vs front-rear PWM" / "roll vs left-right PWM" -
    # rather than per-phase absolute PWM deltas, which are confounded by the
    # throttle-dependent baseline and the estimate's lag behind fast tilts)
    for ph, fn, op, thresh, desc in checks:
        m, n = phase_excursion(ph, fn, op)
        if m is None:
            print("  [ ?? ] %-38s insufficient samples" % desc)
        else:
            good = (m < thresh) if op == "<" else (m > thresh)
            print("  [ %s ] %-38s mean extreme %+.1f deg over %d '%s' windows"
                  % ("ok".center(4) if good else "FAIL", desc, m, n, ph))
    if len(move) > 50:
        d_att = []
        for a, b in zip(move, move[1:]):
            dt = b["t"] - a["t"]
            if 0.01 < dt < 0.2:
                d_att.append(((b["att"][1] - a["att"][1]) / dt, a["gyro"][1],
                              (b["att"][0] - a["att"][0]) / dt, a["gyro"][0]))
        c_pg = corr([x[1] for x in d_att], [x[0] for x in d_att])
        c_rg = corr([x[3] for x in d_att], [x[2] for x in d_att])
        for name, c in (("gyro.y vs d(pitch)/dt", c_pg), ("gyro.x vs d(roll)/dt", c_rg)):
            if c is None:
                print("  [ ?? ] %-24s insufficient motion" % name)
            else:
                lvl = "ok" if c > 0.5 else ("FAIL" if c < -0.2 else "WARN")
                print("  [ %s ] %-24s r=%+.2f %s" % (lvl.center(4), name, c,
                      "(estimate follows gyro)" if c > 0.5 else "(SIGN/COUPLING PROBLEM)" if c < -0.2 else "(weak - tilt more next run)"))
        # accel agreement: pitch-from-accel vs estimate, in slow motion only
        pa = [(math.degrees(math.asin(max(-1, min(1, s["acc"][0] / 9.81)))), s["att"][1])
              for s in move if abs(s["gyro"][1]) < 30 and 8.5 < math.sqrt(sum(v * v for v in s["acc"])) < 11.0]
        c_aa = corr([p[0] for p in pa], [p[1] for p in pa]) if len(pa) > 30 else None
        if c_aa is None:
            print("  [ ?? ] %-24s insufficient clean samples" % "accel vs estimate")
        else:
            lvl = "ok" if c_aa > 0.7 else ("FAIL" if c_aa < 0.3 else "WARN")
            print("  [ %s ] %-24s r=%+.2f %s" % (lvl.center(4), "accel vs estimate", c_aa,
                  "(no vibration-divergence)" if c_aa > 0.7 else "(THE FLIP SIGNATURE - estimate not tracking gravity)"))
        # motor response: does the mixer raise the dropped side
        mr = [(s["att"][1], (s["pwm"][0] + s["pwm"][1]) - (s["pwm"][2] + s["pwm"][3]),
               s["att"][0], (s["pwm"][0] + s["pwm"][3]) - (s["pwm"][1] + s["pwm"][2]))
              for s in move if 0.14 <= s["thr"] < 0.85 and all(p > 900 for p in s["pwm"])]
        c_pm = corr([x[0] for x in mr], [x[1] for x in mr])
        c_rm = corr([x[2] for x in mr], [x[3] for x in mr])
        for name, c in (("pitch vs front-rear PWM", c_pm), ("roll vs left-right PWM", c_rm)):
            if c is None:
                print("  [ ?? ] %-24s insufficient data" % name)
            else:
                lvl = "ok" if c < -0.3 else ("FAIL" if c > 0.3 else "WARN")
                print("  [ %s ] %-24s r=%+.2f %s" % (lvl.center(4), name, c,
                      "(raises the dropped side)" if c < -0.3 else "(WRONG DIRECTION - would amplify a tilt!)" if c > 0.3 else "(weak)"))
    else:
        print("  not enough motion samples for direction grades")

    still = [s for s in samples if s["phase"] == "still"]
    if still:
        print("  vibration in HOLD-STILL windows (sample-to-sample deltas):")
        buckets = {}
        for a, b in zip(still, still[1:]):
            if b["t"] - a["t"] < 0.2:
                key = int(a["thr"] * 100 // 20) * 20
                dg = max(abs(b["gyro"][i] - a["gyro"][i]) for i in range(3))
                da = abs(math.sqrt(sum(v * v for v in b["acc"])) - math.sqrt(sum(v * v for v in a["acc"])))
                buckets.setdefault(key, []).append((dg, da))
        for key in sorted(buckets):
            vals = buckets[key]
            mg = sum(v[0] for v in vals) / len(vals)
            ma = sum(v[1] for v in vals) / len(vals)
            flag = "" if mg < 15 else "  <-- noisy band"
            print("    %2d-%2d%% thr: gyro delta ~%5.1f deg/s, |a| delta ~%4.2f m/s2%s"
                  % (key, key + 19, mg, ma, flag))
    print("\nsend me the jsonl for the deep pass: %s" % outpath)


if __name__ == "__main__":
    main()
