"""Pilot-in-the-loop test modes for the SIM_WROOM target (the posix twin of
the ESP32 Thing Plus, board id 0x1202).

The wroom stack has NO StateEstimation, NO PathFollower, NO PathPlanner --
the flight controller only stabilizes attitude (CC-style Attitude module)
and passes manual thrust through. Everything a Revo would do with position
is therefore done HERE, the way a human pilot would do it: reading the GPS
and moving the sticks. That is the point -- these modes answer "what can
THIS board's stack actually fly", not "what can a Revo fly".

Feedback source is GPS BY DEFAULT (NINJAPILOT_WROOM_FEEDBACK=truth for the
ground-truth escape hatch): the user's question is precisely whether hover
and RTH work on GPS only. GPS here is the same gz navsat feed the bridge
publishes to the FC as GPSPositionSensor/GPSVelocitySensor -- 10 Hz, which
is exactly the latency a real GPS-only pilot loop would fight. The bridge's
own history warns that navsat-rate feedback destabilized the (much hotter)
manual-hover vertical loop; the gains here are derated for 10 Hz from the
start, and the run report shows what that costs.

Modes (NINJAPILOT_TEST_MODE=):
  wroom_hover   arm, take off to 4m, hold 30s on GPS feedback, land.
  wroom_sticks  hover at 3.5m, scripted roll/pitch/yaw stick pokes,
                verify the FC's attitude tracks the commanded angles.
  wroom_rth     hover, fly out ~15m, then return-to-home on GPS only:
                climb to 8m, fly home, descend, touch down, disarm.
                Structurally a single-waypoint mission, flown by the pilot.

A controlled backflip (Rate-mode parlor trick) is deliberately NOT here
yet: it needs a Rate/Rate/Rate bank on a second flight-mode position and
belongs after hover is trusted.

Every mode records a CSV track (logs/wroom_<label>_<ts>.csv) that
tools/wroom_report.py turns into the planned-vs-flown picture.
"""
import csv
import math
import os
import threading
import time

gb = None  # the live gazebo_bridge module, injected via bind()


def bind(bridge_module):
    global gb
    gb = bridge_module


# --- geometry -------------------------------------------------------------

M_PER_DEG_LAT = 111320.0


def gps_ned():
    """(have, n, e, alt_rel_up, vel_ned) from the GPS feed ONLY."""
    have, lat, lon, alt, vel = gb.state.gps_snapshot()
    n = (lat - gb.HOME_LATITUDE) * M_PER_DEG_LAT
    e = (lon - gb.HOME_LONGITUDE) * M_PER_DEG_LAT * math.cos(math.radians(gb.HOME_LATITUDE))
    return have, n, e, alt - gb.HOME_ALTITUDE, vel


def truth_ned():
    have, pos, _q, _gv, _a, _g = gb.state.snapshot()
    return have, pos[0], pos[1], -pos[2]


def truth_rpy():
    """Ground-truth attitude (deg) from the Gazebo pose quaternion - the
    referee between "the vehicle really rotated" and "the FC's estimate
    says it rotated"."""
    _have, _pos, q, _gv, _a, _g = gb.state.snapshot()
    w, x, y, z = q
    roll = math.degrees(math.atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y)))
    sp = max(-1.0, min(1.0, 2 * (w * y - z * x)))
    pitch = math.degrees(math.asin(sp))
    yaw = math.degrees(math.atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z)))
    return roll, pitch, yaw


# --- the pilot ------------------------------------------------------------

class Pilot(object):
    """Closes altitude and position loops through the sticks, like a human.

    Vertical: cascaded (alt error -> desired climb rate -> throttle about
    hover), the structure manual_hover_test settled on after its flat PID
    bang-banged -- but derated for 10 Hz GPS feedback and with a throttle
    slew limit, because a hot gain into 100ms-stale rate feedback is the
    documented yo-yo failure.

    Horizontal: position error -> velocity command -> tilt command ->
    roll/pitch stick, rotated into the body frame by the FC's OWN yaw
    (the pilot's OSD heading, not ground truth).
    """

    RATE_KP = 0.35          # (m/s) desired climb per m of altitude error
    MAX_CLIMB = 1.2
    MAX_DESCENT = 0.6
    THR_PER_MPS = 0.10      # throttle per m/s of climb-rate error
    # 0.45/0.80 assume gb.HOVER_THRUST's stock-X3 anchor (0.68). On the custom "interceptor" airframe, whose real
    # equilibrium measures ~0.20-0.25 (thrprobe_test), a THR_MIN this high is already ~2x true hover thrust - the
    # controller can never command less, so it cannot arrest a climb once above target (see gazebo_bridge.py's
    # HOVER_THRUST comment for the full story). Overridable per-run so the stock-X3 defaults stay intact elsewhere.
    THR_MIN = float(os.environ.get("NINJAPILOT_PILOT_THR_MIN", "0.45"))
    THR_MAX = float(os.environ.get("NINJAPILOT_PILOT_THR_MAX", "0.80"))
    THR_SLEW = 0.6          # throttle units per second, max
    CLIMB_LPF = 0.5         # extra low-pass on the GPS climb rate

    POS_KP = 0.4            # (m/s) per m of horizontal error
    HVEL_MAX = 1.5
    TILT_PER_MPS = 6.0      # deg of tilt per m/s of velocity error
    TILT_MAX = 12.0         # deg
    STICK_FULL_DEG = 42.0   # RollMax/PitchMax in the stab bank

    # Sign conventions (verified live by wroom_sticks): positive roll stick
    # = bank right = +East at yaw 0; positive pitch stick = nose UP = -N,
    # so forward flight needs a NEGATIVE pitch stick.
    ROLL_SIGN = +1.0
    PITCH_SIGN = -1.0

    CEILING_M = 20.0        # truth-checked hard ceiling (safety, not control)
    TILT_OVER_DEG = 65.0

    TRIM_KI = 0.05          # throttle trim per (m/s of standing rate error) per s
    TRIM_MAX = 0.08

    def __init__(self, feedback, rec):
        self.feedback = feedback
        self.rec = rec
        self.climb_f = 0.0
        self.last_thr = 0.0
        self.trim = 0.0     # slow hover-thrust trim, the pilot's throttle trim:
                            # first flight hovered at 0.702 against the assumed
                            # 0.68 and parked 0.64m below target - exactly the
                            # standing error a P-only cascade leaves for a
                            # hover-point bias. The trim integrates it away.
        self.phase = "init"
        self.fail_reason = None
        self.tilt_check = True   # flip phases suspend this - a backflip IS a tilt-over
        self.min_alt_seen = 99.0  # truth, tracked through raw phases (flip depth)

    # feedback selection ---------------------------------------------------
    def nav(self):
        """(ok, n, e, alt_up, vn, ve, climb_up) from the selected source."""
        if self.feedback == "truth":
            have, n, e, alt = truth_ned()
            havep, _alt2, climb = gb.state.pose_alt_climb()
            _hg, _n2, _e2, _a2, gvel = gb.state.gps_snapshot()
            return have and havep, n, e, alt, gvel[0], gvel[1], climb
        have, n, e, alt, vel = gps_ned()
        return have, n, e, alt, vel[0], vel[1], -vel[2]

    # safety ---------------------------------------------------------------
    def check_safety(self):
        _h, _n, _e, alt_truth = truth_ned()
        if alt_truth > self.CEILING_M:
            self.fail_reason = "hard ceiling %.0fm exceeded (truth %.1fm)" % (self.CEILING_M, alt_truth)
        have_att, roll, pitch, _ha, _acc = gb.fc_state.snapshot()
        if self.tilt_check and have_att and (abs(roll) > self.TILT_OVER_DEG or abs(pitch) > self.TILT_OVER_DEG):
            self.fail_reason = "tilt-over roll=%.0f pitch=%.0f" % (roll, pitch)
        if self.fail_reason:
            print("[wroom] SAFETY: %s - cutting throttle, disarming" % self.fail_reason, flush=True)
            gb.control.throttle = 0.0
            gb.control.roll = gb.control.pitch = gb.control.yaw = 0.0
            gb.control.armed = False
            return False
        return True

    # control laws ---------------------------------------------------------
    def vertical(self, target_alt, alt, climb, dt):
        self.climb_f += self.CLIMB_LPF * (climb - self.climb_f)
        desired = max(-self.MAX_DESCENT, min(self.MAX_CLIMB, self.RATE_KP * (target_alt - alt)))
        rate_err = desired - self.climb_f
        thr = gb.HOVER_THRUST + self.trim + self.THR_PER_MPS * rate_err
        if self.THR_MIN < thr < self.THR_MAX:  # anti-windup: trim only unsaturated
            self.trim = max(-self.TRIM_MAX, min(self.TRIM_MAX, self.trim + self.TRIM_KI * rate_err * dt))
        thr = max(self.THR_MIN, min(self.THR_MAX, thr))
        step = self.THR_SLEW * dt
        thr = max(self.last_thr - step, min(self.last_thr + step, thr))
        self.last_thr = thr
        return thr

    def horizontal(self, tgt_n, tgt_e, n, e, vn, ve, vmax=None):
        vmax = vmax or self.HVEL_MAX
        cn = self.POS_KP * (tgt_n - n)
        ce = self.POS_KP * (tgt_e - e)
        mag = math.hypot(cn, ce)
        if mag > vmax:
            cn, ce = cn * vmax / mag, ce * vmax / mag
        return self.velocity(cn, ce, vn, ve)

    def velocity(self, cmd_n, cmd_e, vn, ve):
        """Velocity command -> roll/pitch sticks (body frame via FC yaw)."""
        tn = self.TILT_PER_MPS * (cmd_n - vn)
        te = self.TILT_PER_MPS * (cmd_e - ve)
        mag = math.hypot(tn, te)
        if mag > self.TILT_MAX:
            tn, te = tn * self.TILT_MAX / mag, te * self.TILT_MAX / mag
        yaw = math.radians(gb.fc_state.yaw)
        fwd = math.cos(yaw) * tn + math.sin(yaw) * te      # tilt toward +body-x
        right = -math.sin(yaw) * tn + math.cos(yaw) * te   # tilt toward +body-y
        pitch_stick = self.PITCH_SIGN * fwd / self.STICK_FULL_DEG
        roll_stick = self.ROLL_SIGN * right / self.STICK_FULL_DEG
        return (max(-1.0, min(1.0, roll_stick)), max(-1.0, min(1.0, pitch_stick)))

    # one control tick -----------------------------------------------------
    def tick(self, target_alt, tgt_n=None, tgt_e=None, dt=0.05, sticks=None, vel=None):
        ok, n, e, alt, vn, ve, climb = self.nav()
        if not ok:
            return False
        gb.control.throttle = self.vertical(target_alt, alt, climb, dt)
        if sticks is not None:
            gb.control.roll, gb.control.pitch = sticks
        elif vel is not None:
            gb.control.roll, gb.control.pitch = self.velocity(vel[0], vel[1], vn, ve)
        elif tgt_n is not None:
            gb.control.roll, gb.control.pitch = self.horizontal(tgt_n, tgt_e, n, e, vn, ve)
        else:
            gb.control.roll = gb.control.pitch = 0.0
        self.rec.row(self.phase, n, e, alt, vn, ve, climb)
        return self.check_safety()

    def fly_until(self, seconds, target_alt, tgt_n=None, tgt_e=None, label=None,
                  done=None, sticks=None, vel=None):
        """Run the pilot loop at 20 Hz until `seconds` pass or done() says so.
        Returns True unless safety tripped."""
        if label:
            self.phase = label
        t0 = time.time()
        last = t0
        last_log = 0.0
        while time.time() - t0 < seconds:
            now = time.time()
            dt = min(0.2, now - last)
            last = now
            if not self.tick(target_alt, tgt_n, tgt_e, dt, sticks=sticks, vel=vel):
                return False
            if done is not None and done():
                return True
            if now - last_log > 2.0:
                last_log = now
                ok, n, e, alt, vn, ve, climb = self.nav()
                print("[wroom] %-10s alt=%5.2f pos=(%6.2f,%6.2f) climb=%5.2f thr=%.3f sticks=(%+.2f,%+.2f)"
                      % (self.phase, alt, n, e, climb, gb.control.throttle,
                         gb.control.roll, gb.control.pitch), flush=True)
            time.sleep(0.05)
        return True

    def raw(self, seconds, thr, roll, pitch, label, until=None, floor=None):
        """Raw stick phase at 50 Hz - no closed loops, the maneuver IS the
        command. Records every tick. Stops early when until() returns True
        or truth altitude drops below floor (abort). Returns "done", 
        "until", "floor", or "safety"."""
        self.phase = label
        t0 = time.time()
        while time.time() - t0 < seconds:
            t_now = thr() if callable(thr) else thr
            gb.control.throttle = t_now
            self.last_thr = t_now   # keep the slew limiter's memory honest
            gb.control.roll = roll() if callable(roll) else roll
            gb.control.pitch = pitch() if callable(pitch) else pitch
            ok, n, e, alt, vn, ve, climb = self.nav()
            self.rec.row(label, n, e, alt, vn, ve, climb)
            if not self.check_safety():
                return "safety"
            _h, _tn, _te, talt = truth_ned()
            self.min_alt_seen = min(self.min_alt_seen, talt)
            if floor is not None and talt < floor:
                return "floor"
            if until is not None and until():
                return "until"
            time.sleep(0.02)
        return "done"

    # composite maneuvers --------------------------------------------------
    def takeoff(self, target_alt, timeout=25.0):
        self.phase = "takeoff"
        print("[wroom] takeoff to %.1fm (%s feedback)" % (target_alt, self.feedback), flush=True)
        reached = {"ok": False}

        def arrived():
            ok, _n, _e, alt, _vn, _ve, _c = self.nav()
            if ok and abs(alt - target_alt) < 0.6:
                reached["ok"] = True
                return True
            return False
        if not self.fly_until(timeout, target_alt, tgt_n=0.0, tgt_e=0.0, done=arrived):
            return False
        if not reached["ok"]:
            self.fail_reason = "takeoff never reached %.1fm" % target_alt
            print("[wroom] FAIL: %s" % self.fail_reason, flush=True)
            gb.control.throttle = 0.0
            gb.control.armed = False
            return False
        return True

    def descend_and_land(self, tgt_n=0.0, tgt_e=0.0):
        self.phase = "land"
        print("[wroom] descending to touchdown", flush=True)
        down_since = [None]

        def touched():
            ok, _n, _e, alt, _vn, _ve, climb = self.nav()
            if ok and alt < 0.35 and abs(climb) < 0.25:
                if down_since[0] is None:
                    down_since[0] = time.time()
                elif time.time() - down_since[0] > 0.8:
                    return True
            else:
                down_since[0] = None
            return False
        # timeout scales with the altitude actually being descended from - the fixed 40s here was sized for this
        # test suite's usual 4-8m staging altitudes; shape_test's 30m+ cruise altitude regularly cut the descent off
        # at 13m still up (2026-09-19, star15: all 5 legs flew clean, the mission still reported FAIL because this
        # timeout alone expired) - MAX_DESCENT (~0.6 m/s, see vertical()) at only 40s covers ~24m, not enough headroom.
        _ok0, _n0, _e0, alt0, _vn0, _ve0, _climb0 = self.nav()
        timeout = max(40.0, (alt0 if _ok0 else 30.0) / max(self.MAX_DESCENT * 0.7, 0.1) + 10.0)
        ok = self.fly_until(timeout, -0.5, tgt_n=tgt_n, tgt_e=tgt_e, done=touched)
        gb.control.throttle = 0.0
        gb.control.roll = gb.control.pitch = 0.0
        time.sleep(0.5)
        gb.control.armed = False
        if ok and down_since[0]:
            print("[wroom] touchdown - disarmed", flush=True)
        return ok and down_since[0] is not None


# --- recording ------------------------------------------------------------

class Recorder(object):
    COLS = ["t", "phase", "nav_n", "nav_e", "nav_alt", "nav_vn", "nav_ve", "nav_climb",
            "truth_n", "truth_e", "truth_alt", "fc_roll", "fc_pitch", "fc_yaw",
            "true_roll", "true_pitch",
            "stick_thr", "stick_roll", "stick_pitch", "stick_yaw"]

    def __init__(self, mode):
        label = os.environ.get("NINJAPILOT_RUN_LABEL", mode)
        ts = time.strftime("%Y%m%d_%H%M%S")
        d = os.path.join(os.path.dirname(os.path.abspath(__file__)), "logs")
        os.makedirs(d, exist_ok=True)
        self.path = os.path.join(d, "wroom_%s_%s.csv" % (label, ts))
        self.f = open(self.path, "w", newline="")
        self.w = csv.writer(self.f)
        self.w.writerow(self.COLS)
        self.t0 = time.time()

    def row(self, phase, n, e, alt, vn, ve, climb):
        _h, tn, te, talt = truth_ned()
        _ha, roll, pitch, _hacc, _acc = gb.fc_state.snapshot()
        troll, tpitch, _tyaw = truth_rpy()
        self.w.writerow(["%.3f" % (time.time() - self.t0), phase,
                         "%.3f" % n, "%.3f" % e, "%.3f" % alt,
                         "%.3f" % vn, "%.3f" % ve, "%.3f" % climb,
                         "%.3f" % tn, "%.3f" % te, "%.3f" % talt,
                         "%.2f" % roll, "%.2f" % pitch, "%.2f" % gb.fc_state.yaw,
                         "%.2f" % troll, "%.2f" % tpitch,
                         "%.3f" % gb.control.throttle, "%.3f" % gb.control.roll,
                         "%.3f" % gb.control.pitch, "%.3f" % gb.control.yaw])

    def close(self):
        self.f.flush()
        self.f.close()
        print("[wroom] track written: %s" % self.path, flush=True)


# --- mode entry points ----------------------------------------------------

def _start(mode):
    feedback = os.environ.get("NINJAPILOT_WROOM_FEEDBACK", "gps")
    print("[wroom] %s starting (feedback=%s)" % (mode, feedback), flush=True)
    time.sleep(3.0)  # let config land
    if not gb.wait_for_attitude_ok():
        return None
    rec = Recorder(mode)
    pilot = Pilot(feedback, rec)
    gb.control.mode_position = 0   # Stabilized1: Attitude/Attitude/AxisLock/Manual
    gb.control.throttle = 0.0
    gb.control.roll = gb.control.pitch = gb.control.yaw = 0.0
    gb.control.armed = True
    time.sleep(2.0)
    return pilot


def _finish(pilot, verdict):
    gb.control.throttle = 0.0
    gb.control.armed = False
    pilot.rec.close()
    print("[wroom] VERDICT: %s" % verdict, flush=True)
    print("[wroom] run complete", flush=True)


def hover_test():
    pilot = _start("wroom_hover")
    if pilot is None:
        return
    ok = pilot.takeoff(4.0)
    stats = {"n": 0, "alt_err2": 0.0, "drift_max": 0.0, "alt_min": 99.0, "alt_max": -99.0}
    if ok:
        def sample():
            okn, n, e, alt, _vn, _ve, _c = pilot.nav()
            if okn:
                stats["n"] += 1
                stats["alt_err2"] += (alt - 4.0) ** 2
                stats["alt_min"] = min(stats["alt_min"], alt)
                stats["alt_max"] = max(stats["alt_max"], alt)
                stats["drift_max"] = max(stats["drift_max"], math.hypot(n, e))
            return False
        ok = pilot.fly_until(30.0, 4.0, tgt_n=0.0, tgt_e=0.0, label="hold", done=sample)
    landed = pilot.descend_and_land() if ok else False
    if stats["n"]:
        rms = math.sqrt(stats["alt_err2"] / stats["n"])
        print("[wroom] hold stats: alt rms %.2fm band [%.2f, %.2f], max horiz drift %.2fm"
              % (rms, stats["alt_min"], stats["alt_max"], stats["drift_max"]), flush=True)
    _finish(pilot, "PASS - hover held and landed" if (ok and landed)
            else "FAIL - %s" % (pilot.fail_reason or "landing did not confirm"))


def thrprobe_test():
    """Open-loop hover-thrust probe: no altitude control at all, just a ladder of FIXED raw throttle values (each
    held level for a few seconds) with climb-rate telemetry printed at ~5Hz. Exists to answer, directly and without
    any PID in the loop, "what throttle actually holds this airframe level" - because hover_test/takeoff() started
    climbing away uncontrollably (climb pinned near +8-12 m/s at gb.HOVER_THRUST's floor of 0.45, see
    INTERCEPTOR_FLIGHT_LOG.md) and the fastest way to tell a bad PID anchor (gb.HOVER_THRUST=0.68, tuned for the
    stock "X3" test vehicle, comment: "the X3 hovers at 68% PWM") apart from a real firmware/sim regression is to
    remove the PID from the picture entirely. NINJAPILOT_PROBE_LEVELS="0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,0.60"
    (default) sets the ladder; NINJAPILOT_PROBE_STEP_S (default 3.0) sets seconds per step."""
    pilot = _start("wroom_thrprobe")
    if pilot is None:
        return
    levels = [float(x) for x in os.environ.get(
        "NINJAPILOT_PROBE_LEVELS", "0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,0.60").split(",")]
    step_s = float(os.environ.get("NINJAPILOT_PROBE_STEP_S", "3.0"))
    pilot.CEILING_M = 40.0
    pilot.tilt_check = False
    gb.control.armed = True
    print("[wroom] thrprobe: ladder=%s step=%.1fs" % (levels, step_s), flush=True)
    aborted = False
    for lvl in levels:
        t0 = time.time()
        prev_t, prev_alt = None, None
        while time.time() - t0 < step_s:
            now = time.time()
            gb.control.throttle = lvl
            gb.control.roll = gb.control.pitch = gb.control.yaw = 0.0
            pilot.last_thr = lvl
            ok, n, e, alt, vn, ve, climb = pilot.nav()
            _h, _tn, _te, talt = truth_ned()
            climb_est = 0.0
            if prev_t is not None:
                climb_est = (talt - prev_alt) / max(now - prev_t, 1e-3)
            prev_t, prev_alt = now, talt
            print("[wroom] thrprobe thr=%.2f t=%4.1f alt=%6.2f climb(gps)=%+6.2f climb(truth)=%+6.2f"
                  % (lvl, time.time() - t0, talt, climb, climb_est), flush=True)
            if not pilot.check_safety():
                aborted = True
                break
            time.sleep(0.2)
        if aborted:
            break
    gb.control.throttle = 0.0
    gb.control.armed = False
    pilot.rec.close()
    print("[wroom] VERDICT: %s - throttle ladder %s" % ("ABORTED (ceiling/tilt)" if aborted else "completed", levels), flush=True)
    print("[wroom] run complete", flush=True)


def sticks_test():
    pilot = _start("wroom_sticks")
    if pilot is None:
        return
    ok = pilot.takeoff(3.5)
    results = []
    POKES = [("roll", +0.30, 0), ("roll", -0.30, 0), ("pitch", +0.30, 1), ("pitch", -0.30, 1)]
    if ok:
        for axis, mag, idx in POKES:
            peak = {"v": 0.0}

            def watch():
                _h, r, p, _ha, _a = gb.fc_state.snapshot()
                v = (r, p)[idx]
                if abs(v) > abs(peak["v"]):
                    peak["v"] = v
                return False
            sticks = (mag, 0.0) if axis == "roll" else (0.0, mag)
            ok = pilot.fly_until(1.5, 3.5, label="poke_%s%+.1f" % (axis, mag),
                                 sticks=sticks, done=watch)
            expected = mag * Pilot.STICK_FULL_DEG
            results.append((axis, mag, expected, peak["v"]))
            print("[wroom] poke %s %+0.2f: expected %+0.1f deg, FC reported peak %+0.1f deg"
                  % (axis, mag, expected, peak["v"]), flush=True)
            if not ok:
                break
            # recover position before the next poke
            ok = pilot.fly_until(4.0, 3.5, tgt_n=0.0, tgt_e=0.0, label="recover")
            if not ok:
                break
    landed = pilot.descend_and_land() if ok else False
    good = all(abs(got) > 0.5 * abs(exp) and (got * exp) > 0 for _a, _m, exp, got in results) if results else False
    _finish(pilot, "PASS - attitude tracks the sticks" if (ok and landed and good)
            else "FAIL - %s" % (pilot.fail_reason or "tracking off (see poke lines)"))


def rth_test():
    pilot = _start("wroom_rth")
    if pilot is None:
        return
    RTH_ALT = 8.0
    OUT_N, OUT_E = 15.0, 0.0
    ok = pilot.takeoff(4.0)
    if ok:
        ok = pilot.fly_until(4.0, 4.0, tgt_n=0.0, tgt_e=0.0, label="settle")
    if ok:
        print("[wroom] flying out to (%.0f, %.0f)" % (OUT_N, OUT_E), flush=True)
        arrived = {"ok": False}

        def out_done():
            okn, n, e, _alt, _vn, _ve, _c = pilot.nav()
            if okn and math.hypot(n - OUT_N, e - OUT_E) < 1.5:
                arrived["ok"] = True
                return True
            return False
        ok = pilot.fly_until(30.0, 4.0, tgt_n=OUT_N, tgt_e=OUT_E, label="flyout", done=out_done)
        ok = ok and arrived["ok"]
        if ok and not arrived["ok"]:
            pilot.fail_reason = "never reached the flyout point"
    if ok:
        print("[wroom] RTH engaged: climb to %.0fm, return, land - GPS only" % RTH_ALT, flush=True)
        ok = pilot.fly_until(12.0, RTH_ALT, tgt_n=OUT_N, tgt_e=OUT_E, label="rth_climb",
                             done=lambda: pilot.nav()[3] > RTH_ALT - 0.6)
    home = {"ok": False}
    if ok:
        def home_done():
            okn, n, e, _alt, _vn, _ve, _c = pilot.nav()
            if okn and math.hypot(n, e) < 1.5:
                home["ok"] = True
                return True
            return False
        ok = pilot.fly_until(40.0, RTH_ALT, tgt_n=0.0, tgt_e=0.0, label="rth_home", done=home_done)
        ok = ok and home["ok"]
    landed = pilot.descend_and_land() if ok else False
    _h, tn, te, _ta = truth_ned()
    if landed:
        print("[wroom] touchdown at truth (%.2f, %.2f) - %.2fm from the pad"
              % (tn, te, math.hypot(tn, te)), flush=True)
    _finish(pilot, "PASS - returned home and landed %.2fm from the pad" % math.hypot(tn, te)
            if (ok and landed) else "FAIL - %s" % (pilot.fail_reason or "did not complete"))


# --- the parlor trick -----------------------------------------------------

def _zdot():
    """cos(tilt) from the FC's OWN attitude: R33 = cos(pitch)*cos(roll).
    +1 upright, -1 inverted. Works straight off the euler telemetry - no
    quaternion plumbing needed."""
    _h, roll, pitch, _ha, _a = gb.fc_state.snapshot()
    return (math.cos(math.radians(pitch)) * math.cos(math.radians(roll)), roll, pitch)


# The energy budget is the whole game on this airframe: it hovers at 0.70
# throttle, so full-throttle braking only buys ~4.2 m/s^2 of net upward
# acceleration - arresting the ~7 m/s the rotation costs takes ~6-8m of
# sky on top of the ~3.5m the rotation itself eats. A 7m perch put it in
# the dirt (wf02: floor abort at 0.14m); the perch must clear the WHOLE
# budget. Rotation is torque-limited at ~320 deg/s (raising ManualRate
# 450->540 changed nothing), and differential torque scales with
# collective - hence thrust DURING the flip, not a pure chop.
PERCH_ALT = 11.0   # lows run entry-minus-3-to-5m; 11m keeps >4m over the floor
# The flip throws the vehicle ~4-6m SOUTH (thrust sweeps backward through
# the first half of the rotation). Perching 2.5m NORTH of the pad centers
# that arc on the pad instead of hanging it all off one side.
PERCH_N = 2.5


def _do_flip(pilot, idx):
    """One backflip: punch, rate-mode rotation, two-stage attitude-mode
    catch (level first, then full-throttle arrest), closed-loop recovery.
    Returns (completed, min_alt, loss, flip_s)."""
    # -- punch: vertical energy first. Still in Attitude mode, level -
    # level flight needs no differential headroom, so the punch may use
    # nearly everything.
    PUNCH_THR, PUNCH_S = 0.95, 0.9
    FLIP_STICK = 1.0         # +pitch rate = nose up and over backward
    FLOOR_M = 1.5            # truth-checked abort floor
    # NO runup pre-drift: tried (cr01-cr05) and retired on measurement.
    # Entering with +2 m/s north does cancel the flip's southward fling at
    # the catch, but the carried velocity rides THROUGH the maneuver and
    # relocates the same excursion instead of removing it - and the extra
    # phase time deepened the lows. The flip's throw is dealt with where
    # it is cheap: a gentle velocity-null in the brakeout stage.
    ok0, _n0, _e0, alt0, _v0, _v1, _c0 = pilot.nav()
    print("[wroom] flip %d: punch (alt %.1fm)" % (idx, alt0), flush=True)
    pilot.tilt_check = False
    r = pilot.raw(PUNCH_S, PUNCH_THR, 0.0, 0.0, "punch%d" % idx, floor=FLOOR_M)
    if r != "done":
        return False, 0.0, 0.0, 0.0

    # -- rotate, CLOSED-LOOP ON ANGLE. wf08's board+bridge logs settled
    # the physics: the airframe tracks the commanded 540 deg/s almost
    # exactly, and an open-loop "slam stick, brake on a trigger angle"
    # cannot work - braking from 550 deg/s eats ~200 deg, so the stop
    # point is wherever momentum ran out (wf08 parked INVERTED, 200 deg
    # into a second revolution, with rate mode contentedly holding zero
    # rate upside down). Instead the commanded rate is a function of the
    # angle REMAINING to upright: full rate far out, tapering as level
    # approaches, so the rotation lands on level by construction - the
    # rate-mode equivalent of how ArduCopter's flip recovery targets the
    # original attitude rather than "stop rotating".
    seen_up = [False]
    seen_inv = [False]
    gb.control.mode_position = 5   # Stabilized6 = Rate/Rate/Rate on Bank2 (piloted-flip slot)
    t_flip = time.time()

    def flip_angle():
        """Rotation angle phi (deg, 0..360) of the backflip, from the FC's
        euler telemetry: 0=level start, 90=nose straight up, 180=inverted,
        270=nose straight down, 360=level again."""
        _h, roll, pitch, _ha, _a = gb.fc_state.snapshot()
        if abs(roll) > 90.0:
            return 180.0 - pitch
        if seen_inv[0]:
            # far side: pitch climbs from -90 back to 0 = 270..360
            return 360.0 + pitch if pitch < 0.0 else 360.0
        # near side, not yet inverted: a slightly NEGATIVE pitch is still
        # the start line, not a completed flip - without this clamp a
        # -0.6 deg entry read as phi=359.4 and the taper commanded zero
        # stick for the entire "rotation" (wf12 flip 2).
        return max(0.0, pitch)

    # COMMAND LATENCY is the governing constant of the endgame. wf10's
    # truth-vs-belief trace proved the estimator honest and the physics
    # obedient - but the vehicle blew through a perfectly-shaped taper at
    # 400+ deg/s because a stick command takes ~0.25s to travel
    # control.pitch -> GCSReceiver -> ManualControl -> rate loop. At
    # 500 deg/s that is 125 DEGREES of rotation. So the taper and the
    # mode switch are computed against the angle the vehicle WILL be at
    # when the command lands, using a rate estimate from consecutive
    # attitude samples.
    CMD_LAG_S = float(os.environ.get("NINJAPILOT_FLIP_LAG", "0.25"))
    rate_est = {"t": None, "phi": None, "rate": 0.0}

    def phi_predicted():
        phi = flip_angle()
        now = time.time()
        if rate_est["phi"] is not None and phi != rate_est["phi"] and now > rate_est["t"]:
            r_new = (phi - rate_est["phi"]) / (now - rate_est["t"])
            if -100.0 < r_new < 900.0:  # discard wrap glitches
                rate_est["rate"] = 0.7 * rate_est["rate"] + 0.3 * r_new
        if phi != rate_est["phi"]:
            rate_est["t"], rate_est["phi"] = now, phi
        return min(360.0, phi + rate_est["rate"] * CMD_LAG_S)

    def rot_cmd():
        phi = flip_angle()
        if phi > 55.0:
            seen_up[0] = True
        if 140.0 < phi < 220.0:
            seen_inv[0] = True
        err = 360.0 - phi_predicted()
        # 3 deg/s of commanded rate per deg PREDICTED remaining: full
        # stick early, a ramp that reaches zero when the vehicle - not
        # the telemetry - reaches level.
        rate = max(0.0, min(540.0, 3.0 * err))
        return rate / 540.0

    def flip_thr():
        z, _r2, _p2 = _zdot()
        return 0.60 if z > 0.35 else 0.10

    def rotation_done():
        # Hand over EARLY (predicted 322, not 335): the exit prediction
        # carries variance, and its two error signs are NOT symmetric. An
        # under-rotated stop parks nose-DOWN, where the catch collective
        # pushes north+up - against the flip's southward drift, benign. An
        # over-rotated stop parks nose-UP and thrusts south while falling:
        # that is the 12-16m outlier (cr07-cr09). Biasing the exit early
        # makes every stop land on the benign side of level.
        return seen_inv[0] and phi_predicted() > 322.0
    r = pilot.raw(3.0, flip_thr, 0.0, rot_cmd, "flip%d" % idx,
                  until=rotation_done, floor=FLOOR_M)
    flip_s = time.time() - t_flip
    if r not in ("until", "done"):
        gb.control.mode_position = 0
        pilot.tilt_check = True
        return False, pilot.min_alt_seen, 0.0, flip_s

    # -- catch: Attitude mode from a small error, thrust up to arrest.
    # Not higher than 0.90: wf03 arrested at 0.97 and TUMBLED - at full
    # collective the mixer has no differential left and the attitude
    # loop is a passenger.
    caught = [False]

    def arrested():
        z, _roll, _pitch = _zdot()
        _ok, _n, _e, _alt, _vn, _ve, climb = pilot.nav()
        # Exit while still sinking a little (-1.5): the recover loop keeps
        # arresting, and every extra second spent here at dead-neutral
        # sticks used to be pure horizontal COASTING - the flip flings the
        # vehicle sideways at several m/s, and vid04 measured it carried
        # up to 32m off-station during catches that only watched vertical.
        if z > 0.85 and climb > -1.2:
            caught[0] = True
        return caught[0]

    # Stage 0 - SPIN-KILL, still in the flip slot: the rotation exit is a
    # lag-PREDICTION, and when it is wrong the vehicle crosses level still
    # rotating hundreds of deg/s. The gyro-rate inner loop (stick zero)
    # kills residual spin in a fraction of a second at any collective;
    # Attitude mode at arrest collective cannot (cr04 flips 1 and 3 fell
    # 13m half-caught, drifting 16-20m, and only the sport recovery saved
    # them at 1-2m).
    # Rate-zero beat, 0.3s fixed - the cr06 recipe. Two smarter versions
    # were measured and retired: an adaptive hold-until-still never fired
    # inside its cap (cr08/09), and a level-seeking P-law oscillated at
    # the stability edge of the ~0.25s command lag (K*delay ~ 0.6, cr10
    # put one flip on the floor). The residual stopping-angle variance is
    # handled where it is harmless: the catch throttle below is
    # TILT-GATED, so a tilted stop no longer becomes a horizontal
    # thruster.
    pilot.raw(0.3, 0.70, 0.0, 0.0, "spinkill%d" % idx, floor=FLOOR_M)
    gb.control.mode_position = 0

    # Stage A - PURE VERTICAL arrest, sticks dead level. Commanding brake
    # tilt during the arrest porpoised (+/-40 deg pitch swings at 0.90
    # collective through laggy GPS velocity - cr03 fell to 2.06m without
    # ever arresting). One demand at a time, the same law the flip
    # recovery already learned. The runup pre-compensation means there is
    # barely any slide left to brake anyway.
    partial = [False]

    def part_arrested():
        z, _r, _p = _zdot()
        _ok, _n, _e, _alt, _vn, _ve, climb = pilot.nav()
        if z > 0.88 and climb > -2.5:
            partial[0] = True
        return partial[0]
    # (a tilt-gated arrest throttle was tried here and FLOORED a flip in
    # one run - easing collective while tilted starves the arrest, and
    # the energy budget has no room for that. Fixed 0.90.)
    r3 = pilot.raw(3.0, 0.90, 0.0, 0.0, "catch%d" % idx, until=part_arrested, floor=1.0)
    if r3 != "until" or not partial[0]:
        # a TIMED-OUT arrest is a failure, not a success - cr04 fell
        # through this as "done" and proceeded half-caught
        pilot.tilt_check = True
        return False, pilot.min_alt_seen, 0.0, flip_s
    # Stage B - finish the arrest while gently (12 deg cap) nulling any
    # residual slide, at a collective that leaves attitude headroom.

    def brake_sticks():
        _ok, _n, _e, _alt, vn, ve, _c = pilot.nav()
        return pilot.velocity(0.0, 0.0, vn, ve)
    r3b = pilot.raw(2.0, 0.85, lambda: brake_sticks()[0], lambda: brake_sticks()[1],
                    "brakeout%d" % idx, until=arrested, floor=1.0)
    if r3b not in ("until", "done"):
        pilot.tilt_check = True
        return False, pilot.min_alt_seen, 0.0, flip_s


    # -- stabilize: a beat at hover thrust with the tilt check still off,
    # so the attitude transient finishes before anything may call it a
    # crash. Only then does the closed-loop pilot get the aircraft back.
    pilot.raw(0.5, gb.HOVER_THRUST + pilot.trim, 0.0, 0.0, "stab%d" % idx)
    pilot.tilt_check = True

    # -- recover: hand back to the closed-loop pilot, and WAIT until the
    # perch is actually re-reached - a time-boxed recovery let later flips
    # punch from 11m instead of 13 and their low points paid the 2m
    # (wf13: lowest 2.96m from an 11.0m entry vs 8.11m from 13m).
    at_perch = [False]

    def perched():
        okp, n, e, alt, _vn, _ve, climb = pilot.nav()
        # BOTH axes, or the next flip launches from wherever this one
        # slid to - vid04's flip 3 punched from 14m off-station because
        # this gate only watched altitude.
        if okp and alt > PERCH_ALT - 0.6 and abs(climb) < 0.6 and math.hypot(n - PERCH_N, e) < 2.5:
            at_perch[0] = True
        return at_perch[0]
    # sport caps for the comeback: the hover numbers are derated for calm
    # station-keeping on laggy GPS, but post-flip there are tens of meters
    # to make up and the video reads every extra second as a struggle.
    pilot.MAX_CLIMB, pilot.HVEL_MAX, pilot.THR_MAX = 2.0, 2.5, 0.85
    try:
        ok = pilot.fly_until(20.0, PERCH_ALT, tgt_n=PERCH_N, tgt_e=0.0,
                             label="recover%d" % idx, done=perched)
    finally:
        pilot.MAX_CLIMB, pilot.HVEL_MAX, pilot.THR_MAX = Pilot.MAX_CLIMB, Pilot.HVEL_MAX, Pilot.THR_MAX
    ok = ok and at_perch[0]

    completed = seen_up[0] and seen_inv[0] and caught[0] and r == "until" and ok
    _h, _tn, _te, talt = truth_ned()
    min_alt = min(pilot.min_alt_seen, talt)
    loss = alt0 - pilot.min_alt_seen
    print("[wroom] flip %d: %s - rotation %.2fs, lowest %.2fm (%.2fm below entry), catch %s"
          % (idx, "COMPLETE" if completed else "INCOMPLETE (up=%s inv=%s r=%s)"
             % (seen_up[0], seen_inv[0], r),
             flip_s, pilot.min_alt_seen, loss, "clean" if caught[0] else "TIMEOUT"), flush=True)
    return completed, min_alt, loss, flip_s


def flip_test():
    pilot = _start("wroom_flip")
    if pilot is None:
        return
    n_flips = int(os.environ.get("NINJAPILOT_WROOM_FLIPS", "1"))
    ok = pilot.takeoff(PERCH_ALT)
    if ok:
        # settle long enough for the throttle trim to learn the true hover
        # point - the punch/catch math leans on it - while sliding to the
        # racetrack's south perch
        ok = pilot.fly_until(8.0, PERCH_ALT, tgt_n=PERCH_N, tgt_e=0.0, label="settle")
    results = []
    if ok:
        for i in range(1, n_flips + 1):
            pilot.min_alt_seen = 99.0
            done = _do_flip(pilot, i)
            results.append(done)
            if not done[0]:
                break
    landed = pilot.descend_and_land() if (ok and results and results[-1][0]) else False
    n_ok = sum(1 for rr in results if rr[0])
    _finish(pilot, "PASS - %d/%d backflips completed, landed" % (n_ok, len(results))
            if (landed and n_ok == len(results) and n_ok == n_flips)
            else "FAIL - %d/%d flips (%s)" % (n_ok, len(results),
                                              pilot.fail_reason or "see flip lines"))


def _do_onboard_flip(pilot, idx):
    """One BOARD-side flip: switch to the flip slot, write
    FlipStatus.Command, and watch the module fly the maneuver. The bridge's
    only jobs are the trigger and the closed-loop recovery afterward - the
    sequencing lag that dominated the piloted flip's tuning is gone.
    Returns (completed, min_alt, loss, flip_s)."""
    client = gb._mission_client[0]
    ok0, _n0, _e0, alt0, _v0, _v1, _c0 = pilot.nav()
    print("[wroom] oflip %d: engaging onboard sequencer (alt %.1fm)" % (idx, alt0), flush=True)
    pilot.tilt_check = False
    gb.control.mode_position = 1     # flip slot: Attitude flying, Bank2 active
    gb.control.roll = gb.control.pitch = 0.0
    time.sleep(0.4)                  # let the mode/bank switch land
    gb._last_flipstatus[0] = None
    client.send_object("FlipStatus", {"Command": "Flip", "State": "Idle",
                                      "Flips": 0, "LastAngle": 0.0})
    t0 = time.time()
    seen = set()
    last_angle = 0.0
    terminal = None
    while time.time() - t0 < 8.0:
        fs = gb._last_flipstatus[0]
        if fs is not None:
            state = fs["State"]
            if state not in seen:
                seen.add(state)
                print("[wroom] oflip %d: board reports %s" % (idx, state), flush=True)
            if state in ("Done", "Abort"):
                terminal = state
                last_angle = fs.get("LastAngle", 0.0)
                break
        okn, n, e, alt, vn, ve, climb = pilot.nav()
        pilot.rec.row("oflip%d" % idx, n, e, alt, vn, ve, climb)
        _h, _tn, _te, talt = truth_ned()
        pilot.min_alt_seen = min(pilot.min_alt_seen, talt)
        if talt > pilot.CEILING_M:
            terminal = "ceiling"
            break
        time.sleep(0.04)
    gb.control.mode_position = 0
    # dead-stick beat at hover, then the sport position loop. A
    # velocity-null brakeout stage here was measured WORSE (ob10): tilting
    # against the slide while residual sink remains starves the vertical
    # and one flip bottomed at 0.17m - the same lesson as the onboard
    # tilt-gate. The position loop brakes the slide fine once climbing.
    pilot.raw(0.4, gb.HOVER_THRUST + pilot.trim, 0.0, 0.0, "obstab%d" % idx)
    pilot.tilt_check = True
    at_perch = [False]

    def perched():
        okp, n, e, alt, _vn, _ve, climb = pilot.nav()
        if okp and alt > PERCH_ALT - 0.6 and abs(climb) < 0.6 and math.hypot(n - PERCH_N, e) < 2.5:
            at_perch[0] = True
        return at_perch[0]
    pilot.MAX_CLIMB, pilot.HVEL_MAX, pilot.THR_MAX = 2.0, 2.5, 0.85
    try:
        ok = pilot.fly_until(20.0, PERCH_ALT, tgt_n=PERCH_N, tgt_e=0.0,
                             label="obrecover%d" % idx, done=perched)
    finally:
        pilot.MAX_CLIMB, pilot.HVEL_MAX, pilot.THR_MAX = Pilot.MAX_CLIMB, Pilot.HVEL_MAX, Pilot.THR_MAX
    completed = terminal == "Done" and ok and at_perch[0]
    loss = alt0 - pilot.min_alt_seen
    print("[wroom] oflip %d: %s - board angle %.0f deg, lowest %.2fm (%.2fm below entry)"
          % (idx, "COMPLETE" if completed else "INCOMPLETE (%s)" % terminal,
             last_angle, pilot.min_alt_seen, loss), flush=True)
    return completed, pilot.min_alt_seen, loss, 0.0


def onboard_flip_test():
    pilot = _start("wroom_oflip")
    if pilot is None:
        return
    n_flips = int(os.environ.get("NINJAPILOT_WROOM_FLIPS", "1"))
    ok = pilot.takeoff(PERCH_ALT)
    if ok:
        ok = pilot.fly_until(8.0, PERCH_ALT, tgt_n=PERCH_N, tgt_e=0.0, label="settle")
    results = []
    if ok:
        for i in range(1, n_flips + 1):
            pilot.min_alt_seen = 99.0
            done = _do_onboard_flip(pilot, i)
            results.append(done)
            if not done[0]:
                break
    landed = pilot.descend_and_land() if (ok and results and results[-1][0]) else False
    n_ok = sum(1 for rr in results if rr[0])
    _finish(pilot, "PASS - %d/%d ONBOARD backflips completed, landed" % (n_ok, len(results))
            if (landed and n_ok == len(results) and n_ok == n_flips)
            else "FAIL - %d/%d onboard flips" % (n_ok, len(results)))


def creep_test():
    """Replicate the 2026-09-01 real-flight profile: arm, then CREEP the
    collective to ~8% over ten seconds with sticks dead neutral, exactly
    the working-up-to-hover regime the crash lived in. With ideal motors
    the sim should sit level; with NINJAPILOT_MOTOR_EFF simulating the
    real quad's weak corner it should reproduce the lean-and-tip."""
    pilot = _start("wroom_creep")
    if pilot is None:
        return
    pilot.tilt_check = False
    t0 = time.time()
    tipped = [False]

    def watch():
        troll, tpitch, _ty = truth_rpy()
        if abs(troll) > 30.0 or abs(tpitch) > 30.0:
            tipped[0] = True
            return True
        return False

    def creep_thr():
        # ramp to just past light-on-legs: the regime that matters is
        # thrust ~ weight, not any particular stick percentage - the
        # first version crept to 8.5% and proved only that a quad
        # pressed into the ground by 60% of its weight cannot tip
        cap = float(os.environ.get("NINJAPILOT_CREEP_MAX", "0.74"))
        return min(cap, cap * (time.time() - t0) / 12.0)
    pilot.raw(16.0, creep_thr, 0.0, 0.0, "creep", until=watch)
    troll, tpitch, _ty = truth_rpy()
    gb.control.throttle = 0.0
    gb.control.armed = False
    pilot.rec.close()
    print("[wroom] VERDICT: %s - final truth attitude roll %.1f pitch %.1f"
          % ("TIPPED OVER" if tipped[0] else "stayed level", troll, tpitch), flush=True)
    print("[wroom] run complete", flush=True)


INTERCEPTOR_MAX_TILT_GAIN = 6.0


def interceptor_level_thrust(hover_thrust, theta_off_deg):
    """MUST mirror outerloop.c's interceptor_level_thrust() exactly (same constant, same clamp) - this is what lets
    Python seed the throttle stick at the value the firmware's own auto thrust already holds, so the CRUISE capture
    latch (stabilizationOuterloopTask's OUTERLOOP_INTERCEPTOR thrust case) fires on the first tick at ANY cruise
    pitch, not just whatever angle a fixed constant happened to be tuned for."""
    cos_tilt = math.cos(math.radians(theta_off_deg))
    gain = 1.0 / max(cos_tilt, 1.0 / INTERCEPTOR_MAX_TILT_GAIN)
    return hover_thrust * gain


class ClimbTrim(object):
    """Closed-loop climb-rate-to-throttle trim for INTERCEPTOR CRUISE.

    The FIRMWARE'S auto thrust (interceptor_level_thrust() in outerloop.c) is
    open-loop feedforward: a physically-reasoned estimate, but with no
    altitude feedback and no per-angle calibration (a single calibrated
    constant was tried and tuned - and tuning it for one angle broke every
    other angle, see TRANSITION_THEORY.md #8). This closes the loop the same
    way Pilot.vertical() already does for hover (rate error -> throttle, slow
    integral trim), proving the platform DOES have full climb authority via
    thrust alone at any cruise pitch - no fins needed, no more firmware
    changes needed either: this is a GUIDANCE-layer fix, exactly where the
    wroom stack already does all its position/altitude closure (no
    StateEstimation/PathFollower on this board - see this file's own module
    docstring).

    Anchored at the firmware's own auto thrust at the moment CRUISE starts,
    not at gb.HOVER_THRUST: hover's trim range (+-0.08) cannot span the gap
    to a steep cruise pitch's thrust need, but the geometric estimate is
    already close, so a wider trim range here only has to correct the
    RESIDUAL model error (aero body-lift at speed, motor curve non-linearity),
    not walk the whole hover-to-cruise distance.
    """
    RATE_KP = 0.35
    # Overridable (2026-09-21, see TRANSITION_THEORY.md section 19): seed 4 of the visual-lock/
    # altitude-tracking regression closed to 1.3m horizontally before flying past, still missing on
    # 3D distance - even with section 19's target-altitude-tracking fix mechanically working (altitude
    # visibly moved the correct direction), a genuinely fast-diving target in a ~2s CRUISE-to-closest-
    # approach window can accumulate more vertical error than a 1.0 m/s cap can erase in time. Default
    # unchanged so cruisecontrol_test/speedcorridor_test/etc. (all tuned against 1.0) are unaffected.
    MAX_CLIMB = float(os.environ.get("NINJAPILOT_CLIMBTRIM_MAX_RATE", "1.0"))
    MAX_DESCENT = float(os.environ.get("NINJAPILOT_CLIMBTRIM_MAX_RATE", "1.0"))
    THR_PER_MPS = 0.15
    TRIM_KI = 0.08
    TRIM_MAX = 0.35
    THR_MIN, THR_MAX = 0.10, 0.98
    # Overridable (2026-09-21, see TRANSITION_THEORY.md section 19's rate-cap experiment): raising
    # MAX_CLIMB/MAX_DESCENT alone did NOT improve seed 4 (0.7-1.3m horizontal near-miss regardless of
    # 1x/2x/3x rate cap) - a real negative result that argues the DESIRED rate isn't the bottleneck.
    # This slew limit governs how fast the THROTTLE ITSELF can move regardless of how large the desired
    # rate error is - a real candidate for the actual bottleneck the rate-cap experiment couldn't have
    # found, since raising MAX_DESCENT changes the TARGET, not how fast thrust can get there. Default
    # unchanged so other callers (cruisecontrol_test, speedcorridor_test) are unaffected.
    THR_SLEW = float(os.environ.get("NINJAPILOT_CLIMBTRIM_THR_SLEW", "0.6"))
    CLIMB_LPF = 0.5

    def __init__(self, base_thrust, target_alt):
        self.base = base_thrust
        self.target_alt = target_alt
        self.trim = 0.0
        self.climb_f = 0.0
        self.last_thr = base_thrust

    def update(self, alt, climb, dt):
        self.climb_f += self.CLIMB_LPF * (climb - self.climb_f)
        desired = max(-self.MAX_DESCENT, min(self.MAX_CLIMB, self.RATE_KP * (self.target_alt - alt)))
        rate_err = desired - self.climb_f
        thr = self.base + self.trim + self.THR_PER_MPS * rate_err
        if self.THR_MIN < thr < self.THR_MAX:  # anti-windup: trim only unsaturated, same rule as Pilot.vertical()
            self.trim = max(-self.TRIM_MAX, min(self.TRIM_MAX, self.trim + self.TRIM_KI * rate_err * dt))
        thr = max(self.THR_MIN, min(self.THR_MAX, thr))
        step = self.THR_SLEW * dt
        thr = max(self.last_thr - step, min(self.last_thr + step, thr))
        self.last_thr = thr
        return thr


# ---------------------------------------------------------------------------
# Interceptor tail-sitter transition: NINJAPILOT_TEST_MODE=wroom_transition
# Flies the FIRMWARE's Interceptor mode (switch position 2 = Stabilized3, all four
# axes "Interceptor"). The pilot only does what a human would: take off in
# Stabilized1, flick the switch, leave the sticks alone while the mode climbs
# and pitches over, then fly it a little once the mode hands control back,
# flick back to Stabilized1 to recover to hover, and land.
#
# NINJAPILOT_INTERCEPTOR_CLIMB_TRIM=1: once CRUISE starts, immediately cross
# the stick through the firmware's auto thrust (captures it - a one-way latch
# in outerloop.c, see stabilizationOuterloopTask's OUTERLOOP_INTERCEPTOR
# thrust case) and drive throttle from ClimbTrim instead of holding the fixed
# cruise_thr constant for the rest of the flight. Demonstrates that ANY
# cruise pitch can hold altitude given closed-loop throttle - the sim run
# that matters for "does this need fins" (it does not, for climb control).
# ---------------------------------------------------------------------------
def transition_test():
    pilot = _start("wroom_transition")
    if pilot is None:
        return
    # A healthy climb + transition + several seconds of cruise + roll L/R genuinely gains real altitude from a 4m
    # staging point; the old default 20.0 ceiling leaves little margin once NINJAPILOT_MOTOR_BOOST is correctly set
    # (see INTERCEPTOR_FLIGHT_LOG.md section 14 - a missing/wrong motor-boost setting, not a bad thrust constant,
    # was this session's real "climbs away uncontrollably" bug).
    pilot.CEILING_M = 60.0
    cruise_pitch = float(os.environ.get("NINJAPILOT_INTERCEPTOR_CRUISE_PITCH", "-45"))
    hover_thrust = float(os.environ.get("NINJAPILOT_INTERCEPTOR_HOVER_THRUST", "0.65"))
    # Matches outerloop.c's own interceptor_level_thrust(CruisePitch) exactly - NOT the (now-unused-by-firmware)
    # NINJAPILOT_INTERCEPTOR_CRUISE_THRUST constant, which only matched the firmware's real auto thrust at whatever
    # one angle it was tuned against. Computing it here is what makes the CRUISE capture latch fire cleanly at ANY
    # cruise pitch (see interceptor_level_thrust()'s docstring above).
    cruise_thr = interceptor_level_thrust(hover_thrust, cruise_pitch)
    climb_s = float(os.environ.get("NINJAPILOT_INTERCEPTOR_CLIMB_TIME", "3.0"))
    rate = float(os.environ.get("NINJAPILOT_INTERCEPTOR_TRANSITION_RATE", "15"))
    use_climb_trim = os.environ.get("NINJAPILOT_INTERCEPTOR_CLIMB_TRIM", "0") == "1"
    stats = {"pitch_min": 0.0, "alt_min": 99.0, "alt_max": -99.0, "vfwd_max": 0.0,
             "cruise_pitch_ok": False, "recovered": False}
    climb_trim = [None]   # boxed so watch() (defined once, called many times) can see it set mid-flight

    def watch(label, seconds, sticks=(0.0, 0.0), thr=None, yaw=0.0, hold_altitude=False):
        """Hold given sticks for `seconds`, log truth attitude/altitude/speed at 2 Hz. Returns False on safety trip.
        hold_altitude=True: ignore `thr`, drive throttle from climb_trim[0] (created on first call if absent)."""
        pilot.phase = label
        t0 = time.time(); last_log = 0.0; last_t = t0
        while time.time() - t0 < seconds:
            now = time.time()
            dt = max(1e-3, now - last_t)
            last_t = now
            ok, n, e, alt, vn, ve, climb = pilot.nav()
            if hold_altitude:
                if climb_trim[0] is None:
                    # first tick: match the firmware's own thrust_auto EXACTLY (the same value the non-trim path
                    # would hold) so the one-way capture latch in outerloop.c fires cleanly on this cycle, same as
                    # the always-worked hand-over; every tick after this one is Python's, not the firmware's
                    seed = thr if thr is not None else gb.control.throttle
                    gb.control.throttle = seed
                    pilot.last_thr = seed
                    climb_trim[0] = ClimbTrim(seed, alt)
                else:
                    gb.control.throttle = climb_trim[0].update(alt, climb, dt)
                    pilot.last_thr = gb.control.throttle
            elif thr is not None:
                gb.control.throttle = thr
                pilot.last_thr = thr
            gb.control.roll, gb.control.pitch = sticks
            gb.control.yaw = yaw
            r, p, y = truth_rpy()
            _h, _tn, _te, talt = truth_ned()
            stats["pitch_min"] = min(stats["pitch_min"], p)
            stats["alt_min"] = min(stats["alt_min"], talt)
            stats["alt_max"] = max(stats["alt_max"], talt)
            vfwd = math.hypot(vn, ve)
            stats["vfwd_max"] = max(stats["vfwd_max"], vfwd)
            if label == "cruise" and abs(p - cruise_pitch) < 10.0:
                stats["cruise_pitch_ok"] = True
            if ok:
                pilot.rec.row(label, n, e, alt, vn, ve, climb)
            if time.time() - last_log > 0.5:
                last_log = time.time()
                print("[wroom] %-11s t=%5.1f alt=%5.2f pitch=%6.1f roll=%6.1f yaw=%6.1f vfwd=%5.2f thr=%.2f sticks=(%+.2f,%+.2f)"
                      % (label, time.time() - t0, talt, p, r, y, vfwd, gb.control.throttle, gb.control.roll, gb.control.pitch), flush=True)
            if talt > 80.0 or talt < 0.3:   # sim-only bound: a transition test legitimately climbs well past the hover ceiling
                pilot.fail_reason = "%s: altitude %.1f out of bounds" % (label, talt)
                print("[wroom] FAIL: %s" % pilot.fail_reason, flush=True)
                return False
            time.sleep(0.05)
        return True

    ok = pilot.takeoff(4.0)
    if ok:
        ok = pilot.fly_until(4.0, 4.0, tgt_n=0.0, tgt_e=0.0, label="settle")
    if ok:
        # the switch: from here on the firmware's Interceptor mode owns climb, transition and the throttle
        pilot.tilt_check = False
        hover_thr = gb.control.throttle
        gb.control.mode_position = 2   # Stabilized3 = Interceptor/Interceptor/Interceptor/Interceptor
        print("[wroom] >>> switch to INTERCEPTOR (Stabilized3): climb %.1fs, then pitch to %.0f deg at %.0f deg/s" % (climb_s, cruise_pitch, rate), flush=True)
        transition_s = abs(cruise_pitch) / max(rate, 1.0)
        ok = watch("interceptor_climb", climb_s, thr=hover_thr)
    if ok:
        ok = watch("transition", transition_s + 1.0, thr=hover_thr)
    if ok:
        # hand-over: the mode keeps the auto throttle until our stick passes through it; put it there. With climb
        # trim enabled the very first tick's stick write IS that crossing (gb.control.throttle already equals the
        # firmware's auto value from the previous phase), so the latch and the trim start on the same cycle.
        ok = watch("cruise", 6.0, thr=cruise_thr, hold_altitude=use_climb_trim)
    if ok:
        # the pilot flies it: a gentle roll left, then right, about the cruise attitude
        ok = watch("cruise_roll_L", 3.0, sticks=(-0.25, 0.0), thr=cruise_thr, hold_altitude=use_climb_trim) and \
             watch("cruise_roll_R", 3.0, sticks=(+0.25, 0.0), thr=cruise_thr, hold_altitude=use_climb_trim) and \
             watch("cruise", 2.0, thr=cruise_thr, hold_altitude=use_climb_trim)
    if ok:
        # back to hover: Stabilized1 (Attitude) pulls the nose up at the bank's MaximumRate; throttle back to hover
        gb.control.mode_position = 0
        print("[wroom] <<< switch back to Stabilized1 (recover to hover)", flush=True)
        ok = watch("recover", 6.0, thr=hover_thr)
        _r, p, _y = truth_rpy()
        stats["recovered"] = abs(p) < 15.0
        pilot.tilt_check = True
    landed = False
    if ok:
        _h, _tn, _te, talt = truth_ned()
        ok = pilot.fly_until(10.0, max(4.0, min(talt, 12.0)), tgt_n=None, tgt_e=None, label="brake")
        landed = pilot.descend_and_land(tgt_n=None, tgt_e=None) if ok else False
    print("[wroom] transition stats: pitch min %.1f deg (target %.0f) cruise_pitch_ok=%s vfwd max %.2f m/s alt [%.1f, %.1f] recovered=%s"
          % (stats["pitch_min"], cruise_pitch, stats["cruise_pitch_ok"], stats["vfwd_max"], stats["alt_min"], stats["alt_max"], stats["recovered"]), flush=True)
    verdict = ("PASS - climbed, transitioned to cruise, flew on sticks, recovered and landed"
               if (ok and landed and stats["cruise_pitch_ok"] and stats["recovered"])
               else "FAIL - %s" % (pilot.fail_reason or ("cruise_pitch_ok=%s recovered=%s landed=%s" % (stats["cruise_pitch_ok"], stats["recovered"], landed))))
    _finish(pilot, verdict)


# ---------------------------------------------------------------------------
# Shape missions: NINJAPILOT_TEST_MODE=wroom_shape, NINJAPILOT_SHAPE=star|oval
#
# Negotiates a whole flight plan by ALTERNATING modes: hover (Stabilized1,
# GPS position hold + a yaw-to-heading turn) at every corner, interceptor
# mode (Stabilized3, climb-trim ON) for every straight leg. This is the
# "pre-planner" question directly: can the two modes hand a mission back and
# forth cleanly, leg after leg, rather than just once. Steering during a
# cruise leg is bank-to-turn on the ROLL stick (TRANSITION_THEORY.md #2: in
# forward flight the ROLL axis is the flight-path's yaw, the actual YAW axis
# is a weak roll-about-the-interceptor's-own-axis driven only by prop torque) -
# proportional heading error -> roll stick, no fins, no new actuators.
#
# Trail visualisation reuses mission_test's already-solved CPU answer
# (gazebo_bridge.py's own comment on this: markers are BLOCKING gz service
# calls; a naive per-tick send from the guidance thread once starved the
# firmware's sensor feed and flew a vehicle into the ground). FlownTrail
# self-throttles internally (0.25s / 0.5m minimum), so calling .tick() once
# per pilot-loop iteration costs nothing extra; the planned trail is sent
# ONCE, not per tick.
# ---------------------------------------------------------------------------

def _heading_error(target_deg, current_deg):
    """Shortest signed error target-current, wrapped to [-180, 180]."""
    e = (target_deg - current_deg + 180.0) % 360.0 - 180.0
    return e


def _star_waypoints(radius, n_points=5):
    """Outer points every (360/n_points) deg from North, then the
    skip-two traversal that actually draws a star (visiting the ring in
    order draws a polygon, not a star) - same idea as tools/star_geom.py,
    recomputed here at whatever radius this airframe needs rather than
    coupled to that module's small-radius X3 mission."""
    pts = [(radius * math.cos(math.radians(360.0 / n_points * k)),
            radius * math.sin(math.radians(360.0 / n_points * k))) for k in range(n_points)]
    skip = n_points // 2 if n_points % 2 else n_points // 2 - 1
    order = []
    idx = 0
    for _ in range(n_points):
        order.append(pts[idx % n_points])
        idx += skip if skip > 0 else 1
    order.append(order[0])
    return order


def _oval_waypoints(semi_major, semi_minor, n_points=12):
    return [(semi_major * math.cos(math.radians(360.0 / n_points * k)),
             semi_minor * math.sin(math.radians(360.0 / n_points * k))) for k in range(n_points + 1)]


def _turn_to_heading(pilot, target_heading_deg, hold_n, hold_e, hold_alt, timeout=10.0, hold_settle_s=2.5,
                      tolerance_deg=6.0):
    """Hover in place (GPS position hold) while yawing to face target_heading_deg, THEN KEEP holding
    it - actively, stick-corrected - for hold_settle_s more seconds before returning.

    tolerance_deg (2026-09-20): shape_test's own callers are fine with the original 6 deg default -
    a corner-to-corner star/oval leg is long enough that a few degrees of residual heading error is
    lost in the noise. intercept_test() is not: found via [pndbg] instrumentation that a real
    engagement's ~3.8m residual near-miss (repeatable across 3 separate runs on the same seed, after
    the blind-window lead fix eliminated the much larger original overshoot) tracked almost exactly
    to `range * sin(6 deg)` for this airframe's typical ~35-40m engagement distance - i.e. the OLD
    fixed 6 deg tolerance itself, not the lead calculation, was the last real source of the residual
    miss. Exposed as a parameter rather than just lowering the shared default so shape_test's own
    proven, already-validated behavior is untouched.

    The settle time used to be a separate plain pilot.fly_until() call with the yaw stick left at
    whatever _turn_to_heading last set it to (neutral). That is the bug that put a ~20 deg heading
    error into interceptor_enter()'s ONE-TIME psi_ref capture on leg 4 of a star mission
    (2026-09-19): hover's YAW axis is Stabilization1's "Rate" mode, which has NO angle-hold
    authority at a neutral stick - once the corrective stick let go, heading was free to drift with
    nothing pinning it until the settle window ended and interceptor mode captured whatever it found.
    Interceptor mode's own psi_ref IS then actively PID-held via the quaternion path once locked in
    - the problem was never holding a captured heading, it was capturing the wrong one because
    nothing was holding it in the gap between the turn finishing and the capture happening.
    Precise heading entry is cheap here (full active correction in hover) and expensive in cruise
    (weak, slow prop-torque-only yaw, see TRANSITION_THEORY.md #8) - so ALL of it happens here now,
    turn AND settle, continuously, right up to the instant interceptor mode takes over."""
    pilot.phase = "turn"
    t0 = time.time()
    reached_at = None
    while True:
        now = time.time()
        if reached_at is None and now - t0 >= timeout:
            print("[wroom] turn: timed out %.0f deg short of %.0f" % (abs(err), target_heading_deg), flush=True)
            gb.control.yaw = 0.0
            return True   # not fatal - the leg's own steering will keep correcting
        if reached_at is not None and now - reached_at >= hold_settle_s:
            gb.control.yaw = 0.0
            return True
        dt = 0.05
        ok, n, e, alt, vn, ve, climb = pilot.nav()
        gb.control.throttle = pilot.vertical(hold_alt, alt, climb, dt)
        gb.control.roll, gb.control.pitch = pilot.horizontal(hold_n, hold_e, n, e, vn, ve, vmax=1.0)
        err = _heading_error(target_heading_deg, gb.fc_state.yaw)
        gb.control.yaw = max(-0.6, min(0.6, err / 45.0))
        if ok:
            pilot.rec.row("turn" if reached_at is None else "leg_settle", n, e, alt, vn, ve, climb)
        if not pilot.check_safety():
            return False
        if reached_at is None and abs(err) < tolerance_deg:
            reached_at = now
        elif reached_at is not None and abs(err) >= tolerance_deg:
            reached_at = None   # drifted back out of tolerance during the hold - keep correcting, restart the hold clock
        time.sleep(dt)


def _fly_interceptor_leg(pilot, tgt_n, tgt_e, staging_alt, cruise_pitch, cruise_thr,
                          climb_s, rate, flown=None, arrive_radius=25.0, max_leg_s=45.0):
    """One hover->interceptor->cruise->hover cycle, steered at tgt_n/tgt_e.

    arrive_radius default raised 12m -> 25m 2026-09-19: at ~9 m/s cruise with a weak/slow yaw
    axis, this airframe's effective turn radius on final approach is real, not a tuning slop - a
    star mission (star14/star15) repeatedly closed to 20-30m and then legitimately overshot before
    the (correctly working) divergence check aborted it, forcing an unnecessary full retry (fresh
    climb+transition) for what was actually a near-miss, not a failure to converge. 25m is still
    tight relative to the 90m leg lengths flown so far and nowhere near the distances (60-170m)
    that were genuine divergence, not overshoot.

    Returns a status string, never a bare bool - "flying a clean line to nowhere" is not an
    acceptable outcome to fold into a generic False (2026-09-19 directive: every leg must be
    judged by what the position sensor actually says, continuously, not by "did it stay stable
    for max_leg_s"). Every return means something the caller can act on:
      "arrived"    - closed to within arrive_radius of the real target, sensor-confirmed
      "diverging"  - distance-to-target GREW over a short window - never let this ride out the
                     clock; a stable, well-controlled flight in the wrong direction is a worse
                     failure than an obviously unstable one, because nothing else catches it
      "stalled"    - distance-to-target did not meaningfully shrink over a longer window - still
                     "flying a clean line to nowhere" even if it never technically diverges
      "safety"     - tilt/roll safety trip (see below)
      "timeout"    - reached max_leg_s while still closing on the target, just not fast enough
    "diverging" and "stalled" both abort the LEG (back to hover) well before max_leg_s; they are
    not softer than "timeout", they are treated as equally serious by the caller, which retries
    from the vehicle's REAL position rather than advancing to the next waypoint regardless.
    """
    hover_thr = gb.control.throttle
    gb.control.mode_position = 2
    pilot.tilt_check = False
    transition_s = abs(cruise_pitch) / max(rate, 1.0)
    t0 = time.time()
    phase = "leg_climb"
    trim = None
    status = "timeout"
    last_log = 0.0
    # divergence/stall monitor state - populated once cruise starts, since only cruise steers
    cruise_dist0 = None      # distance to target at the instant cruise steering began
    cruise_t0 = None
    dist_hist = []           # [(t, dist), ...] trimmed to DIVERGE_WINDOW_S for the short-horizon check
    DIVERGE_WINDOW_S = 4.0
    DIVERGE_MARGIN_M = 3.0   # allow GPS/steering noise; growth beyond this over the window is real divergence
    STALL_WINDOW_S = 12.0
    STALL_MIN_PROGRESS_FRAC = 0.10  # must close at least 10% of the entry distance every STALL_WINDOW_S
    # roll/yaw RATE (finite difference, not just angle) - added to instrument the still-unexplained ~20 deg
    # bank-and-reverse plateau (see TRANSITION_THEORY.md/INTERCEPTOR_FLIGHT_LOG.md section 11/12 item 1): angle alone
    # could not distinguish "slow convergence" from "an active opposing effect while the actuator holds steady",
    # which is what the data actually looked like. A real negative yaw_rate while roll is HELD (not still
    # increasing) at max stick is the smoking gun for a coupling effect rather than a slow response.
    prev_rpy_t = None
    prev_roll = None
    prev_yaw = None
    roll_rate = 0.0
    yaw_rate = 0.0
    while time.time() - t0 < max_leg_s:
        now = time.time()
        elapsed = now - t0
        ok, n, e, alt, vn, ve, climb = pilot.nav()
        dist = math.hypot(tgt_n - n, tgt_e - e)
        if phase == "leg_climb":
            gb.control.throttle = hover_thr
            gb.control.roll = gb.control.pitch = 0.0
            if elapsed >= climb_s:
                phase, t_phase0 = "leg_transition", now
        elif phase == "leg_transition":
            gb.control.throttle = hover_thr
            gb.control.roll = 0.0
            gb.control.pitch = 0.0
            if now - t_phase0 >= transition_s + 1.0:
                phase = "leg_cruise"
                gb.control.throttle = cruise_thr    # one tick to trip the firmware's capture latch, same as transition_test
                trim = ClimbTrim(cruise_thr, staging_alt)
                cruise_dist0, cruise_t0 = dist, now
                dist_hist = [(now, dist)]
                steer_int = 0.0   # fresh integral state for THIS attempt - see the leg_cruise branch for why it exists
        else:  # leg_cruise: steer toward the target with the roll stick, hold altitude with the throttle
            dt = 0.05
            gb.control.throttle = trim.update(alt, climb, dt) if trim else cruise_thr
            bearing = math.degrees(math.atan2(tgt_e - e, tgt_n - n))
            # STEER BY GROUND TRACK, NOT NOSE YAW - the actual fix for the "plateau", found 2026-09-19 by logging
            # both during a rollstep test (wroom_hoverstep/rollstep comparison, then a direct nose-yaw-vs-track
            # instrumentation pass): the SAME 6s/0.30-stick bank that only ever bought ~3.8 deg of nose-yaw
            # correction (and gave half of it back once the bank stopped changing - section 12's gyroscopic-
            # precession finding) bent the GROUND TRACK (atan2(ve, vn), the actual velocity-vector heading) by
            # ~25 deg and HELD it there - a real, held, coordinated-turn effect from tilting the thrust vector,
            # completely different from and much larger than the nose-yaw correction this steering law was
            # measuring against the whole time. Below ~1.5 m/s the track angle is noisy/undefined (near-zero
            # vector), so fall back to nose yaw only in that narrow low-speed regime (leg entry, near a stall).
            vfwd = math.hypot(vn, ve)
            current_heading = math.degrees(math.atan2(ve, vn)) if vfwd > 1.5 else gb.fc_state.yaw
            err = _heading_error(bearing, current_heading)
            # NEGATIVE roll stick raises yaw (right turn), POSITIVE lowers it (left turn) - measured 2026-09-19,
            # see TRANSITION_THEORY.md #8's roll test. Small P gain: this axis is a slow, weak lever (prop-torque
            # yaw only), so a large gain overshoots and hunts rather than tracking.
            #
            # INTEGRAL TERM added 2026-09-19 after repeated star-mission legs plateaued at a ~20-25 deg RESIDUAL
            # heading error and then drifted away rather than closing it (star16: legs stalled at consistent
            # non-zero error across multiple different bearings, textbook steady-state offset). Root cause: bank
            # angle drives a YAW RATE (weak prop-torque authority), not a yaw ANGLE directly - a pure-P law on
            # angle error against a plant whose OWN output is itself rate-coupled settles wherever the commanded
            # bank's rate contribution stops shrinking the error fast enough to keep the proportional term honest,
            # not necessarily at zero error. The integral accumulates exactly the persistent, low-level error a
            # P-only term cannot resolve. Bounded (STEER_I_MAX) so a single leg's integral cannot itself run away
            # the way an unclamped one could; reset fresh every attempt (never carries between retries).
            # 0.02/0.15 (first try) never moved the needle: at a typical 20-22 deg plateau (steer_p ~= -0.22-0.24)
            # the integral had only reached ~0.06 of its 0.15 cap by the time divergence aborted the leg (~15s in) -
            # the SAME plateau reproduced almost identically across three different attempts/bearings in star17
            # with that gain, meaning it was too weak to be tested at all, not tested-and-failed. Raised an order of
            # magnitude; I_MAX now matches the outer stick clamp so a fully wound integral can hold max deflection
            # on its own once it gets there, rather than topping out below what the plant can actually take.
            STEER_KI = 0.1
            STEER_I_MAX = 0.35
            steer_p = -err / 90.0
            steer_int = max(-STEER_I_MAX, min(STEER_I_MAX, steer_int + steer_p * dt * STEER_KI))
            gb.control.roll = max(-0.35, min(0.35, steer_p + steer_int))
            gb.control.pitch = 0.0
            # TRIED AND REVERTED 2026-09-19: a fixed-period "pump" (oscillate the commanded bank between a floor and
            # the full P+I target instead of letting it settle static) - motivated by real data (star22: yaw_rate
            # tracked ROLL RATE, not angle, peaking at -0.8 deg/s while roll climbed at +2.5 deg/s and collapsing to
            # ~0 the instant roll flattened - the signature of gyroscopic precession from the spinning rotors
            # coupling a CHANGING bank into yaw, not a static one). The diagnosis is very likely still correct; this
            # specific fix was not - re-testing (star23) with the pump active gave INCONSISTENT roll-rate/yaw-rate
            # correlation, sometimes matching the predicted sign and sometimes not, once the commanded bank was
            # itself oscillating rather than one smooth ramp. Most likely cause: the actual airframe's roll response
            # has inertia/lag this fixed 2.5s period never accounted for, so commanded and actual dRoll/dt drifted
            # out of the relationship the fix assumed. Needs real system identification of the roll-axis bandwidth
            # before another attempt, not another guessed waveform - see INTERCEPTOR_FLIGHT_LOG.md section 12 item 1.
            if dist < arrive_radius:
                status = "arrived"
                break
            # continuous sensor-fed convergence check - see docstring. Never let a stable, well-controlled
            # flight in the wrong direction ride out max_leg_s just because nothing LOOKS wrong.
            dist_hist.append((now, dist))
            dist_hist = [(t, d) for t, d in dist_hist if now - t <= DIVERGE_WINDOW_S]
            if now - dist_hist[0][0] >= DIVERGE_WINDOW_S - 0.5 and dist > dist_hist[0][1] + DIVERGE_MARGIN_M:
                print("[wroom] leg_cruise: DIVERGING - dist %.1fm now vs %.1fm %.1fs ago - aborting to hover"
                      % (dist, dist_hist[0][1], now - dist_hist[0][0]), flush=True)
                status = "diverging"
                break
            if now - cruise_t0 >= STALL_WINDOW_S:
                progress = (cruise_dist0 - dist) / max(cruise_dist0, 1.0)
                if progress < STALL_MIN_PROGRESS_FRAC:
                    print("[wroom] leg_cruise: STALLED - only %.0f%% closed in %.0fs (dist %.1f -> %.1fm) - aborting to hover"
                          % (progress * 100.0, now - cruise_t0, cruise_dist0, dist), flush=True)
                    status = "stalled"
                    break
                # reset the stall window from here, so it is judged over EVERY 12s slice, not cumulatively
                cruise_dist0, cruise_t0 = dist, now
        if flown is not None:
            flown.tick()
        if ok:
            pilot.rec.row(phase, n, e, alt, vn, ve, climb)
        if not pilot.check_safety():
            return "safety"
        # pilot.tilt_check is OFF for this whole leg (interceptor mode's own pitch is deliberately > TILT_OVER_DEG),
        # so this is the ONLY thing left watching for a genuine tumble. Roll should sit near zero except a small
        # cruise-steering deflection (+-0.35 stick, measured ~+-15 deg actual - see TRANSITION_THEORY.md #8's roll
        # test) and CLIMB's entry-blend fades any inherited roll to zero within 0.6s regardless - so ANY roll beyond
        # 50 deg here is not this mode operating normally, it is a loss of control. Added 2026-09-19 after a star
        # mission tumbled on leg 1 with nothing catching it until it hit the ground.
        r, p, y = truth_rpy()
        if abs(r) > 50.0:
            print("[wroom] SAFETY: leg roll=%.0f deg exceeds 50 - cutting throttle, disarming" % r, flush=True)
            gb.control.throttle = 0.0
            gb.control.roll = gb.control.pitch = gb.control.yaw = 0.0
            gb.control.armed = False
            pilot.fail_reason = "leg tumbled: roll %.0f deg" % r
            return "safety"
        if now - last_log > 1.0:
            # rate over the ~1s since the last print - smoothed enough to be readable, fast enough to catch the
            # plateau's onset. A negative yaw_rate while stick_r is PINNED at max is the signature to watch for.
            if prev_rpy_t is not None:
                rdt = max(now - prev_rpy_t, 0.01)
                roll_rate = (r - prev_roll) / rdt
                yaw_rate = (_heading_error(y, prev_yaw)) / rdt   # wrap-safe delta
            prev_rpy_t, prev_roll, prev_yaw = now, r, y
            last_log = now
            print("[wroom] %-14s t=%5.1f alt=%5.2f roll=%6.1f(%+5.1f/s) pitch=%6.1f yaw=%6.1f(%+5.1f/s) dist=%6.1f thr=%.2f stick_r=%+.2f"
                  % (phase, elapsed, alt, r, roll_rate, p, y, yaw_rate, dist, gb.control.throttle, gb.control.roll), flush=True)
        time.sleep(0.05)
    # back to hover for the corner regardless of how the leg ended
    gb.control.mode_position = 0
    gb.control.roll = gb.control.pitch = 0.0
    gb.control.throttle = hover_thr
    pilot.tilt_check = True
    # recover IN PLACE (current position), not toward the original target - a leg that aborted for diverging or
    # stalling should not spend its vulnerable hover-recovery phase still lunging at the same point that steering
    # just failed to reach; the caller decides whether/how to re-approach, using the real position this leaves it at.
    ok_recover, rn, re_, ralt, _rvn, _rve, _rclimb = pilot.nav()
    recover_n, recover_e = (rn, re_) if ok_recover else (tgt_n, tgt_e)
    if not pilot.fly_until(8.0, staging_alt, tgt_n=recover_n, tgt_e=recover_e, label="leg_recover"):
        return "safety"
    if status != "arrived":
        print("[wroom] leg: %s, %.1fm from target (%.1f,%.1f)" % (status, dist, tgt_n, tgt_e), flush=True)
    return status


# Real, measured, repeatable altitude excursion above `staging_alt` at the moment CRUISE begins -
# independent of guidance law, cruise_pitch=-45, seen identically across every wroom_icept run this
# session (cruise-entry alt lands at ~39.5-40m from a 30m staging_alt). Shared by intercept_test()
# (spawns/drives the target at staging_alt + this, instead of at staging_alt) and _fly_intercept_leg()
# (ClimbTrim's own hold target below, matched to the same value) - see intercept_test()'s own comment
# on gb.TARGET_ALT for the full story of why this exists.
_INTERCEPT_TRANSITION_OVERSHOOT_M = 9.5

# ADAPTIVE CLIMB DURATION (2026-09-23, direct user instruction to build the plumbing this file's own
# section 22.5 had scoped but deferred): sections 19-22's whole altitude-tracking history kept
# correcting a vertical gap REACTIVELY, during CRUISE - the one phase with the least time budget left,
# since horizontal (bank-based) closing finishes faster than vertical (throttle-based) closing can (the
# precise mechanism section 22.4 confirmed identically on three separate seeds). Climb duration is the
# lever that already, directly, controls how much altitude the interceptor gains BEFORE cruise even
# starts - adapting it per engagement, using _solve_intercept_lead()'s own precise predicted altitude,
# means cruise can start already close to where the target will be, instead of always starting from the
# SAME fixed ~9.5m overshoot regardless of what this specific engagement actually needs.
#
# _CLIMB_ADAPTIVE_RATE_MPS: the CLIMB PHASE'S OWN average climb rate (not the combined climb+transition
# overshoot rate) - measured directly from this session's own traces (e.g. 30.05->32.4m over the ~2.1s
# climb_s=3.0 phase covers before transition begins), used to back out how much of the DEFAULT 9.5m
# total overshoot is attributable to climb duration itself vs. transition's own (climb_s-independent)
# pitch-over dynamics, so a NEW climb_s can be solved for a NEW desired overshoot with the same simple
# linear model, not a second guessed constant.
_CLIMB_ADAPTIVE_RATE_MPS = float(os.environ.get("NINJAPILOT_CLIMB_ADAPTIVE_RATE_MPS", "1.3"))
_CLIMB_ADAPTIVE_DEFAULT_CLIMB_S = 3.0   # the climb_s _INTERCEPT_TRANSITION_OVERSHOOT_M was measured at
_CLIMB_ADAPTIVE_TRANSITION_FIXED_M = (_INTERCEPT_TRANSITION_OVERSHOOT_M
                                       - _CLIMB_ADAPTIVE_RATE_MPS * _CLIMB_ADAPTIVE_DEFAULT_CLIMB_S)
# Conservative bounds (2026-09-23): only the DEFAULT climb_s=3.0 has been extensively validated this
# session - clamped to a modest range around it rather than an untested extreme, pending real
# measurement of how far this can safely be pushed either way.
_CLIMB_ADAPTIVE_MIN_S = float(os.environ.get("NINJAPILOT_CLIMB_ADAPTIVE_MIN_S", "1.5"))
_CLIMB_ADAPTIVE_MAX_S = float(os.environ.get("NINJAPILOT_CLIMB_ADAPTIVE_MAX_S", "5.0"))


def _solve_adaptive_climb_s(desired_overshoot_m):
    """Solve for the climb_s that should leave the interceptor's post-transition altitude closest to
    `staging_alt + desired_overshoot_m`, using the linear model described in the module comment above.
    Clamped to a conservative, only-modestly-different-from-the-validated-default range."""
    raw_climb_s = (desired_overshoot_m - _CLIMB_ADAPTIVE_TRANSITION_FIXED_M) / max(_CLIMB_ADAPTIVE_RATE_MPS, 0.1)
    return max(_CLIMB_ADAPTIVE_MIN_S, min(_CLIMB_ADAPTIVE_MAX_S, raw_climb_s))


# Ported from flight/libraries/paths.c's path_intercept() - the SAME guidance structure the Revo
# target's onboard PathFollower flies, not a second invented algorithm (2026-09-20 correction: an
# earlier version of this steering law used gb.lead_solution(), which its own docstring says is a
# "DISPLAY ONLY" trail mirror that "must never become something the flight code depends on" - using
# it as real guidance was itself part of the bug. This block replaces that with the real algorithm).
# WROOM has no onboard PathFollower to run this in C, so the ground side has to do the job the
# firmware does for Revo - the two should differ only by SETTINGS (vmax, endgame distance scaled for
# this airframe's cruise speed), not by using a different guidance approach.
#
# What's ported: constant-bearing steering (cancel the target's cross-line-of-sight velocity, spend
# the remaining speed budget closing range - the actual collision condition, not "point at the
# target") with an ENDGAME short-horizon lead once close (pure constant-bearing is ill-conditioned as
# range->0), plus a rate limit on how fast the commanded DIRECTION may swing per tick - exactly the
# mechanism paths.c uses to stop "a jittery tracker from overloading the airframe", which is the
# in-code term for precisely what caused the earlier overshoot (10.0m -> 22.9m in ~1s, the aim
# direction swinging faster than steering could track it).
#
# What's deliberately NOT ported: paths.c's "speed" logic (loiter/full-effort easing and the removed
# terminal-deceleration taper) - this airframe has no independent forward-speed axis in cruise, speed
# is a function of cruise_pitch, already fixed before the leg starts. That is an actuation-reality
# difference (this airframe cannot vary cruise speed the way an omnidirectional multirotor can), not
# a guidance-algorithm difference; the constant-bearing/endgame-lead/rate-limit steering above is
# reused exactly. INTERCEPT_ENDGAME_DIST (4.0m in paths.c) was tuned for the Revo target's ~2.2 m/s
# vmax against a 1.2 m/s object - initially scaled here by the SAME time-to-endgame (4.0/2.2 =~ 1.8s)
# at this airframe's own cruise_speed. That value (endgame triggering at ~10.9m for a 6 m/s cruise)
# measurably did not give enough time to correct: wroom_rollstep (2026-09-20, run at this same -45 deg
# cruise pitch) measured only ~9 deg/s average achievable ground-track change at a held 0.30 stick,
# degrading further as roll saturates near 19 deg past t=2s - correcting a typical 30-40 deg residual
# needs ~4-5s, not the ~1.8s the Revo-derived scaling provided. Re-derived from THIS airframe's own
# measured turn authority instead of the reference vehicle's time-to-endgame: ~4.5s, chosen to give one
# real correction opportunity for a mid-size heading error rather than none.
_INTERCEPT_ENDGAME_TIME_S = 4.5            # re-derived from this airframe's measured turn-rate (see
                                            # above), not paths.c's 4.0/2.2 Revo-scaled value
_INTERCEPT_ENDGAME_LEAD_K = 1.0            # paths.c INTERCEPT_ENDGAME_LEAD_K
_INTERCEPT_LAG_COMP_S = 0.0                 # paths.c INTERCEPT_LAG_COMP_S. TRIED 1.0 (2026-09-20),
                                            # reasoning from wroom_icept12's measured ~1s bank-response
                                            # delay at the endgame boundary - RESULT: WORSE, not better
                                            # (wroom_icept13: closed to only 12.0m, vs 9.9m at 0.0, then
                                            # diverged to 25.3m vs 23.6m). Reverted. See
                                            # TRANSITION_THEORY.md section 13 - the overshoot at this
                                            # airframe's cruise speed looks like a genuine turn-authority
                                            # limit, not a lead-time tuning gap, and guessing a third
                                            # value without a principled reason is exactly the pattern
                                            # to stop doing.
_INTERCEPT_ENDGAME_MAX_LEAD_S = _INTERCEPT_ENDGAME_TIME_S   # REAL BUG, found by direct user
                                            # feedback ("not leading hard enough") - paths.c's 2.5s cap
                                            # is a non-binding safety value for ITS OWN 1.8s endgame
                                            # window (4.0m / 2.2 m/s), never meant to be a meaningful
                                            # constraint. Copied verbatim here without checking it
                                            # against the RE-DERIVED 4.5s endgame window: at endgame
                                            # entry (rng=endgame_dist), t_lead = rng/vmax = 4.5s, but was
                                            # being silently clamped to 2.5s - flat, under-scaled lead for
                                            # the entire upper half of the endgame (27m down to ~15m at
                                            # 6 m/s), only behaving as designed inside 15m. Tying this cap
                                            # to the endgame time itself (rather than a separately-chosen
                                            # constant) means it can never again silently under-cut
                                            # whatever endgame window is actually configured.
_INTERCEPT_MAX_TURN_RATE_DEG_S = 60.0      # paths.c INTERCEPT_MAX_TURN_RATE


def _solve_intercept_lead(n0, e0, alt0, tn0, te0, talt0, tvn, tve, tvalt, blind_s, cruise_speed, iters=8):
    """Solve for the FULL intercept time T (not just the blind-window duration) and the target's exact
    predicted 3D position at that moment - the fix for a real, direct user correction (2026-09-21):
    "if you'd lead properly, set a proper predictive angle for takeoff, then transition into forward
    flight there is ZERO reason to not nail the intercept" - and a real gap this file's own prior
    one-shot aim had: it extrapolated the target only to the END of the blind window (climb+transition
    duration), then aimed the nose at THAT point - not at the target's position at the moment of ACTUAL
    intercept, which is LATER still (by however long cruise then takes to close the remaining
    distance). That remaining gap was never fed back into the aim at all - the initial heading was
    computed as if the intercept happened the instant cruise began, when a real, still-open cruise
    closing time (often several more seconds, comparable to or longer than the blind window itself)
    remained.

    Model: the interceptor makes ~zero net horizontal progress during `blind_s` (climb+transition -
    consistent with every trace this session has logged, roll/PN correction aside), then closes the
    remaining distance at a constant `cruise_speed` (this airframe's own real cruise speed, not the
    Dubins-vehicle constant-speed-from-t=0 model the referenced papers assume - a deliberate, honest
    adaptation to what this specific two-phase VTOL-to-cruise vehicle actually does, not a claim that a
    Dubins vehicle's own math applies unmodified). Solved by fixed-point iteration - the same
    root-finding spirit as Zheng & Chen 2021's own bisection/polynomial approach, adapted to this
    vehicle's speed profile instead of solving their quartic directly: each iteration's predicted
    intercept time refines the NEXT iteration's target extrapolation, converging quickly since target
    speed is always less than cruise_speed (this project's own established assumption, matching
    `path_intercept()`'s speed-ratio requirement) - a contraction mapping, not a guess-and-hope loop.

    Returns (T, lead_n, lead_e, lead_alt) - T is the total time from now until intercept; the lead point
    is the target's real predicted 3D position at exactly that moment, using its own known-constant
    velocity (fully known in this simulation, not estimated - see the user's own "you KNOW the heading
    of the ball, and its speed at ALL times" correction elsewhere this session)."""
    t_total = blind_s + 5.0   # initial guess, refined below
    for _ in range(iters):
        lead_n = tn0 + tvn * t_total
        lead_e = te0 + tve * t_total
        dist = math.hypot(lead_n - n0, lead_e - e0)
        cruise_time_needed = dist / max(cruise_speed, 0.1)
        t_total = blind_s + cruise_time_needed
    lead_n = tn0 + tvn * t_total
    lead_e = te0 + tve * t_total
    lead_alt = talt0 + tvalt * t_total
    return t_total, lead_n, lead_e, lead_alt


def _intercept_bearing_deg(n, e, tn, te, tvn, tve, vmax, last_heading_deg, dt):
    """One tick of paths.c's path_intercept() direction logic (2D - this leg doesn't steer
    altitude), returning a heading in degrees, already rate-limited against last_heading_deg.
    last_heading_deg=None on the first call (no limiting yet, matching paths.c's `haveLast`)."""
    Rn, Re = tn - n, te - e
    rng = math.hypot(Rn, Re)
    if rng < 1e-3:
        return last_heading_deg if last_heading_deg is not None else 0.0
    un, ue = Rn / rng, Re / rng
    endgame_dist = vmax * _INTERCEPT_ENDGAME_TIME_S
    if rng < endgame_dist:
        t_lead = min((rng / vmax) * _INTERCEPT_ENDGAME_LEAD_K + _INTERCEPT_LAG_COMP_S,
                     _INTERCEPT_ENDGAME_MAX_LEAD_S)
        ln, le = Rn + tvn * t_lead, Re + tve * t_lead
        ll = math.hypot(ln, le)
        dn, de = (ln / ll, le / ll) if ll > 1e-3 else (un, ue)
    else:
        vt_along = tvn * un + tve * ue
        vperp_n, vperp_e = tvn - vt_along * un, tve - vt_along * ue
        vperp_mag = math.hypot(vperp_n, vperp_e)
        if vperp_mag >= vmax:
            bn, be = vperp_n, vperp_e   # unwinnable cross-range geometry - see paths.c comment
        else:
            closing = math.sqrt(max(vmax * vmax - vperp_mag * vperp_mag, 0.0))
            bn, be = vperp_n + closing * un, vperp_e + closing * ue
        bl = math.hypot(bn, be)
        dn, de = (bn / bl, be / bl) if bl > 1e-3 else (un, ue)
    heading = math.degrees(math.atan2(de, dn))
    if last_heading_deg is not None:
        max_step = _INTERCEPT_MAX_TURN_RATE_DEG_S * dt
        step = _heading_error(heading, last_heading_deg)
        if abs(step) > max_step:
            heading = last_heading_deg + math.copysign(max_step, step)
    return heading


# Proportional Navigation (2026-09-20, user-supplied references: Zheng & Chen 2021 "Time-Optimal
# Guidance for Intercepting Moving Targets" - the optimal law for a constant-speed, bounded-turn-rate
# (Dubins) vehicle is bang-bang CURVATURE control, not a soft heading-error correction to a recomputed
# aim point; Yoon 2008 "Relative Circular Navigation Guidance" - a real-time curvature-feedback law
# that closes the loop on line-of-sight geometry directly. Both point at the same structural fix: this
# airframe in cruise IS a constant-speed, bank-to-turn-rate vehicle (not an omnidirectional platform
# path_intercept()'s constant-bearing law implicitly assumes), and the right control variable is a
# commanded TURN RATE driven by the LOS rotation rate, not a snapshot bearing tracked by a P+I stick
# law. This is classical PN, `turn_rate_cmd = N * los_rate` - since this test doesn't need a specific
# impact angle (RCNG's extra feature over plain PN), full RCNG's added complexity isn't needed.
#
# _intercept_bearing_deg() (above) is kept for the one-time pre-engagement/retry re-aim (a rough initial
# heading before the pitch-over, not a continuous control law) - PN replaces it as the actual CRUISE
# steering law below, since PN's whole point is closing the loop on LOS rate continuously, not chasing
# a periodically-recomputed target heading through a second, separate heading-error P+I stage.
_PN_GAIN_N = float(os.environ.get("NINJAPILOT_PN_GAIN_N", "8.0"))
                                 # classical PN navigation constant. 4.0 (textbook-standard 3-5 range)
                                 # measured (wroom_icept20, 2026-09-20) real, stable, but weak: commanded
                                 # bank never exceeded ~6 deg (the stick clamp is +-0.45, equivalent to
                                 # ~28 deg - most of the available authority went unused), and the closest
                                 # approach (7.4m, this session's best) still diverged afterward rather
                                 # than converging. Raised to use more of the margin the range-floor fix
                                 # already made safe, not a blind guess - this airframe's real weak/slow
                                 # turn authority (measured ~9 deg/s, section 13) is exactly the case
                                 # classical guidance texts note needs a HIGHER N to compensate for slow
                                 # actuator response, not a lower one.
_PN_BANK_PER_STICK_DEG = 19.0 / 0.30   # measured directly: wroom_rollstep's own 0.30-stick -> ~19 deg
                                        # steady bank at this cruise pitch - not an assumed/guessed
                                        # stick-to-angle scale


_PN_RANGE_FLOOR_M = 5.0          # real, reproduced failure (wroom_icept19, 2026-09-20): LOS_rate's
                                  # R^2 denominator blows up as R->0 for ANY nonzero cross-track relative
                                  # velocity, regardless of how small the actual miss distance is - a
                                  # textbook PN pathology, not a gain-tuning mistake. Tripped a real tumble
                                  # (roll -51 deg, safety cutoff) at ~9.4m range. Standard practical fix:
                                  # floor the range used in the denominator so LOS_rate stays bounded at
                                  # close range instead of diverging, same idea as terminal-guidance laws
                                  # that switch strategy or cap gain inside some minimum range.


_pn_debug_last_print = [0.0]


def _intercept_pn_roll(n, e, vn, ve, tn, te, tvn, tve, vfwd, dist=None):
    """Command roll stick via classical Proportional Navigation: turn_rate_cmd = N * LOS_rate,
    converted to a bank angle via the standard coordinated-turn relation (bank = atan(V*turn_rate/g)),
    then to a stick fraction via this airframe's own measured bank-per-stick calibration. LOS_rate is
    computed directly from relative position/velocity (the textbook 2D cross-product form), not
    finite-differenced, so it is exact every tick rather than lagging by one sample. The R^2 denominator
    is floored at _PN_RANGE_FLOOR_M to prevent the classic close-range LOS-rate blowup (see that
    constant's own comment) - a real, reproduced tumble, not a hypothetical concern."""
    Rn, Re = tn - n, te - e
    r2_raw = Rn * Rn + Re * Re
    r2 = max(r2_raw, _PN_RANGE_FLOOR_M * _PN_RANGE_FLOOR_M)
    Vrn, Vre = tvn - vn, tve - ve   # relative velocity, target minus pursuer
    los_rate = (Rn * Vre - Re * Vrn) / r2   # rad/s: LOS line's own rotation rate
    turn_rate_cmd = _PN_GAIN_N * los_rate
    bank_rad = math.atan2(max(vfwd, 1.0) * turn_rate_cmd, 9.81)
    bank_deg = math.degrees(bank_rad)
    stick = max(-0.45, min(0.45, bank_deg / _PN_BANK_PER_STICK_DEG))
    if os.environ.get("NINJAPILOT_VERBOSE") == "1":
        now = time.time()
        if now - _pn_debug_last_print[0] > 0.5:
            _pn_debug_last_print[0] = now
            print("[wroom] pndbg dist=%.2f los_rate=%+7.4f rad/s turn_rate_cmd=%+7.4f bank_deg=%+6.1f "
                  "(pre-clamp) stick=%+.3f floored=%s"
                  % (dist if dist is not None else -1.0, los_rate, turn_rate_cmd, bank_deg, stick,
                     r2_raw < _PN_RANGE_FLOOR_M * _PN_RANGE_FLOOR_M), flush=True)
    return stick


# EXACT-LEAD-POINT STEERING - a direct, testable answer to a fair challenge (2026-09-21): "how the
# f*** are you missing when you have full numbers for both objects? the interceptor and the ball!"
# Correct and sharp - this sim has PERFECT state for both vehicles, no sensor noise, no estimation lag.
# PN was chosen deliberately (see the section above this one, from the Zheng & Chen / Yoon papers) as
# the right control variable for a bank-to-turn vehicle - but it is still a FEEDBACK law that reacts to
# current relative geometry rather than explicitly using the target's known-constant velocity to solve
# the intercept directly. With perfect state and a non-maneuvering target, the intercept point and time
# ARE exactly solvable (this file already does exactly that solve, `_intercept_bearing_deg` - the
# quadratic closing-speed lead-point math ported from paths.c's path_intercept()) - it's just only ever
# called ONCE, for the pre-engagement aim, then abandoned in favor of PN for everything after. This
# steers by that SAME exact solve, called every tick with the real current state (a continuously
# updated lead point, not a stale one-shot guess), converted to bank via a plain heading-error P
# controller - not a claim that this is definitely better than PN, a real, honest, run-the-numbers
# comparison of the two on the same seeds. `NINJAPILOT_GUIDANCE_LAW=exact` selects this in place of PN;
# default stays "pn" (unchanged behavior) until the comparison says otherwise.
_EXACT_HEADING_KP = float(os.environ.get("NINJAPILOT_EXACT_HEADING_KP", "1.0"))
                            # deg of bank per deg of heading error, clamped below - a plain P law, the
                            # same shape _turn_to_heading already uses (err/45.0-style), not tuned yet.
_EXACT_MAX_BANK_DEG = float(os.environ.get("NINJAPILOT_EXACT_MAX_BANK_DEG", "35.0"))

_exact_last_heading = [None]
_exact_debug_last_print = [0.0]


def _intercept_exact_roll(n, e, vn, ve, tn, te, tvn, tve, vfwd, dist=None, dt=0.05):
    """Command roll stick by aiming directly at the exact, continuously-recomputed intercept point
    (`_intercept_bearing_deg`'s own quadratic lead-point solve, called every tick instead of once) via a
    plain heading-error P controller - see the module comment above for what this tests and why."""
    heading = _intercept_bearing_deg(n, e, tn, te, tvn, tve, max(vfwd, 1.0), _exact_last_heading[0], dt)
    _exact_last_heading[0] = heading
    # FIXED (2026-09-21, first version caused wild +-35 deg bank chattering during CLIMB, confirmed via
    # [exactdbg]): atan2(ve, vn) is numerically meaningless noise at near-zero horizontal speed, which
    # is exactly the climb-phase regime. `_fly_interceptor_leg` already established the right guarded
    # pattern for this same problem (line ~1363 in this file) - reuse it rather than inventing a
    # different threshold.
    own_heading = math.degrees(math.atan2(ve, vn)) if vfwd > 1.5 else gb.fc_state.yaw
    err = _heading_error(heading, own_heading)
    bank_deg = max(-_EXACT_MAX_BANK_DEG, min(_EXACT_MAX_BANK_DEG, _EXACT_HEADING_KP * err))
    stick = max(-0.45, min(0.45, bank_deg / _PN_BANK_PER_STICK_DEG))
    if os.environ.get("NINJAPILOT_VERBOSE") == "1":
        now = time.time()
        if now - _exact_debug_last_print[0] > 0.5:
            _exact_debug_last_print[0] = now
            print("[wroom] exactdbg dist=%.2f lead_heading=%+6.1f own_heading=%+6.1f err=%+6.1f "
                  "bank_deg=%+6.1f stick=%+.3f"
                  % (dist if dist is not None else -1.0, heading, own_heading, err, bank_deg, stick),
                  flush=True)
    return stick


def _intercept_roll(n, e, vn, ve, tn, te, tvn, tve, vfwd, dist=None, dt=0.05):
    """Selects between PN (default) and the exact-lead-point alternative via NINJAPILOT_GUIDANCE_LAW,
    so both `_fly_intercept_leg` call sites (climb and cruise) stay in sync with one switch."""
    if os.environ.get("NINJAPILOT_GUIDANCE_LAW", "pn") == "exact":
        return _intercept_exact_roll(n, e, vn, ve, tn, te, tvn, tve, vfwd, dist=dist, dt=dt)
    return _intercept_pn_roll(n, e, vn, ve, tn, te, tvn, tve, vfwd, dist=dist)


# CONTINUOUS CLIMB-PITCH-TOWARD-TARGET (2026-09-21, direct user correction while watching a live run:
# "you still aren't transitioning until you are ABOVE the incursion drone path... just fly at a 45
# degree angle pre-transition toward the incoming orange ball"; "you made a weird non-organic path...
# not a real world logical way to get from path A to path B with a spline curve"). Root cause: firmware
# outerloop.c's INTERCEPTOR_CLIMB case computes `theta_off` ENTIRELY internally - a fade from
# whatever attitude the vehicle had at engagement down to LEVEL (0 deg) over INTERCEPTOR_ENTRY_BLEND_TIME,
# then holds level for the rest of ClimbTime - with no knowledge of where the target actually is. This
# file's own `_fly_intercept_leg` then hardcoded `gb.control.pitch = 0.0` on top of that during climb,
# reasoning (2026-09-20) that "the pitch-over schedule is the firmware's own, not something to fight
# from the ground side" - true for the FIRMWARE's internal theta_off, but ground pitch is not a fight
# with it: `rpy_desired[PITCH] = theta_off + live_frac * stabilizationDesiredAxis[PITCH]` (outerloop.c)
# is a straight ADDITION, and live_frac has ramped to 1.0 well before climb ends since the 2026-09-20
# live-steer fix. Sending 0.0 there was a leftover, unexamined assumption, not a real constraint -
# exactly the pattern of "a false constraint" this whole session has repeatedly found (see the
# live_frac fix itself, and the blind-window-lead work before it). The result before this fix: the
# vehicle climbed near-VERTICALLY for the whole ClimbTime while only correcting bearing (roll), then
# pitched over sharply once TRANSITION began - a vertical segment followed by a separate flat dive, not
# a continuously curving path toward the target, and if the interceptor's climb happens to carry it
# above the target's actual altitude before that dive starts, the dive can fly it clean over the top
# ("shanks it").
#
# FIRST ATTEMPT AT THIS FIX WAS WRONG (2026-09-21, caught by the user from a live screenshot the SAME
# morning: "the take off was almost completely vertical NOT angled toward the target intercept" - and
# they were right, confirmed directly from the log: pitch peaked at 6-8 deg then fell back, invisible
# against a 90-degree vertical-to-dive range). The original version below commanded pitch proportional
# to the LOS ELEVATION ANGLE to the target's current position - mathematically guaranteed to be shallow
# at a normal ~30-40m engagement range with only a few meters of altitude difference (this project's own
# design keeps interceptor and target roughly co-altitude, see gb.TARGET_ALT), regardless of how far
# away the target is horizontally. That is the wrong quantity: the user asked for a real forward LEAN
# toward the target (closing horizontal distance during climb, not just aiming level thrust at a
# shallow-looking point), not a small correction toward however the geometry happens to look at range.
#
# Fix: ramp pitch toward a real FRACTION of `cruise_pitch` (the eventual dive angle transition/cruise
# already uses) over the climb duration, the same way TRANSITION's own firmware schedule ramps theta_off
# from 0 to the full `cruise_pitch` - just starting that ramp during CLIMB instead of waiting for
# TRANSITION to begin it. This makes climb and dive one continuously-steepening arc (climb ends already
# leaning NINJAPILOT_CLIMB_PITCH_FRAC of the way toward cruise attitude; TRANSITION's own schedule then
# carries it the rest of the way) instead of two disconnected regimes - the literal "45 degree angle
# pre-transition" and "spline curve, not vertical-then-flat" the user asked for. Time-ramped (not
# geometry-driven): this is a deliberate simplification, not a hidden bug - a straight time ramp is
# exactly what TRANSITION's own proven schedule already is, and is far more predictable to reason about
# and validate than a geometry term that (as this section's own history shows) can look reasonable and
# still be numerically wrong at the ranges this actually runs at.
_CLIMB_PITCH_FRAC = float(os.environ.get("NINJAPILOT_CLIMB_PITCH_FRAC", "0.6"))
                            # 60% of cruise_pitch by the end of climb (e.g. -27 deg of a -45 deg
                            # cruise_pitch default) - a real, visible lean, not the full angle: some
                            # margin is kept for TRANSITION's own schedule to still do recognizable work,
                            # and to leave headroom against InterceptorClimbThrust's real (unmeasured
                            # against a large added ground tilt) vertical-lift margin - see this file's
                            # own thrprobe_test/ClimbTrim history on how easily an assumed thrust margin
                            # turns out to be wrong when actually measured.


_CLIMB_ALT_BIAS_DEG_PER_M = float(os.environ.get("NINJAPILOT_CLIMB_ALT_BIAS_PER_M", "1.5"))
_CLIMB_ALT_BIAS_MAX_DEG = float(os.environ.get("NINJAPILOT_CLIMB_ALT_BIAS_MAX_DEG", "15.0"))


def _intercept_climb_pitch(elapsed_climb_s, climb_s, cruise_pitch, alt, tgt_alt_predicted):
    """Ramp pitch toward `_CLIMB_PITCH_FRAC * cruise_pitch` over the climb duration (a real,
    aerodynamically-grounded forward lean - see the module comment above for why this replaced the
    original elevation-angle version) PLUS a bias toward the target's predicted altitude at intercept.

    `tgt_alt_predicted` (2026-09-22, direct user correction: "if you'd lead properly... there is ZERO
    reason to not nail the intercept") is now the PRECISELY SOLVED altitude from
    `_solve_intercept_lead()` - the target's real predicted position at the actual, self-consistently-
    solved intercept time, computed ONCE before takeoff-turn, not re-estimated reactively every tick off
    a fluctuating "time left" guess (the prior version of this function did that, per its own now-
    superseded docstring history - see git blame / TRANSITION_THEORY.md section 21 for that story). This
    keeps the time-ramp (a real, aerodynamically-grounded forward lean - section 21.1) and biases it
    toward the ONE precomputed answer, in the spirit of the referenced Zheng & Chen 2021 paper this
    session was supposed to be applying all along: solve the intercept geometry exactly once, then trust
    it, rather than soft-correct forever."""
    ramp = min(1.0, elapsed_climb_s / max(climb_s, 0.1))
    base_deg = cruise_pitch * _CLIMB_PITCH_FRAC * ramp
    alt_gap = tgt_alt_predicted - alt   # + = target predicted above the interceptor's current altitude
    bias_deg = max(-_CLIMB_ALT_BIAS_MAX_DEG, min(_CLIMB_ALT_BIAS_MAX_DEG, alt_gap * _CLIMB_ALT_BIAS_DEG_PER_M))
    target_deg = base_deg + bias_deg
    return max(-0.45, min(0.45, target_deg / _PN_BANK_PER_STICK_DEG))


# VISUAL-LOCK / MATCHED-PURSUIT REFRAMING (2026-09-20, user's own proposed mission concept): "the goal
# of the intercept should be to try to obtain a visual of the orange ball in the cameras, and clearly
# be maintaining that visual because you are matching speed, heading, etc. to converge at a near future
# point" - i.e. success as a SUSTAINED, CONVERGING visual track, not solely a precise kinematic
# collision distance. Motivated directly by section 17's finding that 3 of 4 randomized crossing
# geometries never reach hit_dist=1.5m even with every guidance/firmware fix tried, apparently due to a
# genuine turn-rate/closing-speed limit rather than a remaining bug - this asks whether those same
# "misses" are nonetheless functionally successful engagements by a visual-pursuit standard, which may
# be the more honest fit for what this airframe (fast fixed-wing cruise, weak/slow turn authority) can
# actually deliver against a maneuvering target.
#
# No camera sensor is modeled in this world, so this is a geometric proxy: the interceptor's own
# horizontal velocity vector stands in for its camera boresight (a fair proxy in cruise - this airframe
# flies nose-first, unlike a hover-capable quad that could point a gimbal independent of travel
# direction), checked against a configurable cone half-angle and max range - exactly what a real
# fixed-camera FOV gate reduces to. ADDITIVE, not a replacement: `_fly_intercept_leg`'s existing
# hit_dist/diverging/stalled/timeout scoring is untouched; this only adds a second, alternate way for a
# leg_cruise attempt to end in "visual_lock" status, so every existing regression result in sections
# 14-17 remains exactly reproducible.
_VISUAL_FOV_DEG = float(os.environ.get("NINJAPILOT_VISUAL_FOV_DEG", "40.0"))
                                  # total cone angle (not half-angle) - +-20 deg off boresight, a
                                  # plausible narrow-ish stabilized gimbal/FPV camera FOV, not a guess
                                  # at a specific real lens.
_VISUAL_MAX_RANGE_M = float(os.environ.get("NINJAPILOT_VISUAL_MAX_RANGE_M", "60.0"))
                                  # deliberately >= gb.DETECT_RANGE (46m) so a lock can in principle be
                                  # acquired as early as detection itself, not artificially capped
                                  # tighter than the range this guidance already operates at.
_VISUAL_LOCK_HOLD_S = float(os.environ.get("NINJAPILOT_VISUAL_LOCK_HOLD_S", "2.5"))
                                  # "clearly be maintaining that visual" - a single in-FOV tick is not a
                                  # track, it is a flash. 2.5s (well over half of PN's own DIVERGE_WINDOW_S
                                  # in _fly_intercept_leg) is long enough that a lock surviving it reflects
                                  # real, sustained geometry, not a lucky instantaneous crossing of the cone.
_VISUAL_CONVERGE_MARGIN_M = float(os.environ.get("NINJAPILOT_VISUAL_CONVERGE_MARGIN_M", "2.0"))
                                  # "converge at a near future point" is the whole point of the
                                  # reframing - a stable stand-off that never closes range is not a
                                  # pursuit, it's formation flying alongside an unrelated track. Requires
                                  # range at lock-hold-satisfied to be at least this much LESS than range
                                  # at lock start, or the hold does not count as a genuine intercept.

_fov_debug_last_print = [0.0]
_yaw_debug_last_print = [0.0]


def _visual_lock_check(n, e, vn, ve, tn, te):
    """'Is the target ball currently in the interceptor's camera frame' - tries REAL image-based
    detection first (2026-09-23, direct user request: "wait till there is a visual in FOV of the ball,
    then attempt to keep the ball in the FOV of the RGB camera"), falling back to the geometric proxy
    this function used before. `gb.get_camera_ball_bearing()` runs the same red-dominant-pixel rule
    tools/ball_detect.py already validated, live, on every real rendered `/interceptor/cam_rgb/image`
    frame.

    THE FALLBACK IS LOAD-BEARING, NOT DECORATIVE (2026-09-23): built the real path, then discovered -
    by literally saving and looking at camera frames mid-flight, not guessing - that the camera's
    rendered view is uniform empty sky through an ENTIRE successful engagement, climb through the
    actual hit, never once showing ground or target. This is a real, pre-existing bug in the camera's
    body-mount transform (model.sdf: "both looking out of the nose along body +z... pitch -90 deg" -
    predates tonight, this is just the first code that ever actually read the feed and noticed), not
    something introduced tonight and not a detection-rule problem (confirmed with a second,
    independent, standalone watcher process - 899 frames, 0 hits, during a run that closed to 1.07m).
    Until that mounting bug is found and fixed, real detection will simply never fire - falling back
    keeps the visual-lock/matched-pursuit criterion (section 18) working exactly as before rather than
    silently regressing every seed that used to pass it. Once the mounting bug is fixed, real
    detections will simply start winning over the fallback automatically - no further change needed
    here.
    Returns (in_fov, angle_off_boresight_deg, horiz_range_m)."""
    horiz_range = math.hypot(tn - n, te - e)
    real = gb.get_camera_ball_bearing()
    if real is not None:
        az_deg, _el_deg, _npix = real
        in_fov = horiz_range <= _VISUAL_MAX_RANGE_M   # sanity cap - the camera's own far-clip is 300m,
                                                       # much further than a tactically meaningful "lock"
        return in_fov, az_deg, horiz_range
    own_heading = math.degrees(math.atan2(ve, vn)) if math.hypot(vn, ve) > 1.5 else gb.fc_state.yaw
    bearing_to_tgt = math.degrees(math.atan2(te - e, tn - n))
    angle_off = _heading_error(bearing_to_tgt, own_heading)
    in_fov = abs(angle_off) <= _VISUAL_FOV_DEG / 2.0 and horiz_range <= _VISUAL_MAX_RANGE_M
    return in_fov, angle_off, horiz_range


def _fly_intercept_leg(pilot, get_target, staging_alt, cruise_pitch, cruise_thr,
                        climb_s, rate, cruise_speed, hit_dist=1.5, max_leg_s=30.0, lead_alt=None):
    """The long-range half of mode-adaptive intercept guidance: the SAME climb->transition->cruise
    mechanics as _fly_interceptor_leg (copied, not rewritten - see that function's own extensive
    tuning history), but steered every tick by _intercept_bearing_deg() - a direct port of
    path_intercept()'s own constant-bearing/endgame-lead/rate-limited guidance (see that function's
    docstring for what's ported and why) - instead of a fixed waypoint. This is the piece the
    existing intercept guidance never had: a way to use this airframe's actual fast-cruise capability
    against a moving target, instead of being limited to the ~1.5-2.6 m/s hover-translate speed the
    Revo intercept test was built and tuned around.

    get_target() must return (tgt_n, tgt_e, tgt_vn, tgt_ve) in the same NED frame as pilot.nav(), or
    None if the target is currently untracked (steering holds its last command that tick rather than
    guessing). "arrived" means within hit_dist of the TARGET's real position, not the lead point -
    the lead point is where to aim, not where a hit is scored.

    See TRANSITION_THEORY.md section 12 for why this exists and what it does not yet do: the target's
    altitude is not tracked (ClimbTrim holds `staging_alt` throughout - fine if the target is roughly
    level with the interceptor, wrong otherwise), and there is no retry-from-real-position logic on a
    miss yet (that is the natural next step, reusing shape_test's own retry pattern)."""
    hover_thr = gb.control.throttle
    gb.control.mode_position = 2
    pilot.tilt_check = False
    transition_s = abs(cruise_pitch) / max(rate, 1.0)
    t0 = time.time()
    phase = "leg_climb"
    trim = None
    status = "timeout"
    last_log = 0.0
    cruise_dist0 = None
    cruise_t0 = None
    dist_hist = []
    # CLOSEST-APPROACH INSTRUMENTATION (2026-09-21, see TRANSITION_THEORY.md section 19's "Update, same
    # night": raising ClimbTrim's rate cap 2x/3x did NOT monotonically improve seed 4's outcome, which
    # argues against a simple closing-rate limit but was only inferable from the once-a-second summary
    # print plus separate 0.5s-cadence [fovdbg] horizontal-only range - never the same tick, and never
    # the actual vertical component. This records the TRUE minimum 3D distance and its horizontal/
    # vertical split every tick (not just once a second), independent of hit/diverge/stall/lock
    # decisions, so the next run of a near-miss seed answers directly whether the residual gap at
    # closest approach is horizontal, vertical, or both - instead of requiring another guess-and-test
    # cycle like this one.
    closest = {"dist": 1e9, "t": 0.0, "horiz": 0.0, "vert": 0.0}
    DIVERGE_WINDOW_S = 4.0
    DIVERGE_MARGIN_M = 3.0
    STALL_WINDOW_S = 12.0
    STALL_MIN_PROGRESS_FRAC = 0.10
    last_tgt = None   # last known (tn, te, tvn, tve) - held over a momentary tracking gap
    dist = 1e9
    lock_start_t = None      # visual-lock/matched-pursuit tracking - see _visual_lock_check's own
    lock_start_dist = None   # module-level comment for what this reframing is and why
    while time.time() - t0 < max_leg_s:
        now = time.time()
        elapsed = now - t0
        ok, n, e, alt, vn, ve, climb = pilot.nav()
        if phase in ("leg_climb", "leg_transition"):
            # REAL STEERING DURING CLIMB/TRANSITION (2026-09-20, firmware fix: outerloop.c's
            # live_frac now ramps from engagement, not from CRUISE - see that file's own comment on
            # interceptor_run() for the full story). Before this fix, the firmware hard-ignored
            # roll/pitch/yaw for the entire climb+transition duration regardless of what was sent
            # here, so intercept_test() had to pre-compute a single aim point and fly blind on it
            # for ~7-10s with no way to correct for a moving target or for its own timing estimate
            # being wrong - the actual root cause of this whole session's crossing-geometry misses.
            # Now that the firmware listens from t=0 (ramping to full authority over
            # INTERCEPTOR_LIVE_BLEND_TIME, ~0.8s), send the SAME PN correction used in cruise here
            # too, continuously tracking the target's real current position instead of a
            # precomputed prediction. Throttle stays at hover_thr (still firmware-ignored until
            # CRUISE captures it - unrelated to this fix, thrust capture was deliberately left
            # CRUISE-only).
            gb.control.throttle = hover_thr
            tstate = get_target()
            if tstate is not None:
                last_tgt = tstate
            if last_tgt is not None:
                tn, te, tgt_alt, tvn, tve, tgt_valt = last_tgt
                vfwd = math.hypot(vn, ve)
                gb.control.roll = _intercept_roll(n, e, vn, ve, tn, te, tvn, tve, vfwd)
                # CONTINUOUS PITCH DURING CLIMB (2026-09-21, see _intercept_climb_pitch's own module
                # comment for the full story, including the first, WRONG version of this fix - direct
                # user correction while watching a live miss): CLIMB only, not TRANSITION, where
                # firmware's own theta_off is already actively ramping through its own large intentional
                # dive. `elapsed` is time since this LEG started, which is also time-in-climb-phase
                # since leg_climb is always the first phase (t0 marks the leg's own start).
                # `time_to_cruise`: remaining time until CRUISE actually begins, for predicting the
                # target's real altitude at that moment (see _intercept_climb_pitch's own comment).
                if phase == "leg_climb":
                    # PRECISE, PRE-SOLVED lead altitude (2026-09-22, direct user correction: "if you'd
                    # lead properly... there is ZERO reason to not nail the intercept" - see
                    # _solve_intercept_lead's own docstring). Falls back to the OLD reactive per-tick
                    # estimate only if the caller didn't pass one (defensive - `intercept_test()`
                    # always does now).
                    if lead_alt is not None:
                        tgt_alt_predicted = lead_alt
                    else:
                        time_to_cruise = max((climb_s - elapsed) + transition_s + 1.0, 0.1)
                        tgt_alt_predicted = tgt_alt + tgt_valt * time_to_cruise
                    # Ablation switch (2026-09-21, TRANSITION_THEORY.md section 20.5 item 1, same
                    # reasoning as NINJAPILOT_CLIMB_YAW_ENABLE above): default on (1), debugging knob.
                    if os.environ.get("NINJAPILOT_CLIMB_PITCH_ENABLE", "1") == "1":
                        gb.control.pitch = _intercept_climb_pitch(elapsed, climb_s, cruise_pitch, alt,
                                                                   tgt_alt_predicted)
                    else:
                        gb.control.pitch = 0.0
                    # CONTINUOUS YAW ("corkscrew") DURING CLIMB (2026-09-21, direct user correction:
                    # "'stop and turn to face a precomputed bearing' is dumb considering how this
                    # aircraft is built. It can literally corkscrew itself in the air... yaw is a
                    # spline curve and maybe a twist on the way to the point of interest"). Firmware's
                    # own interceptor_heading() already couples yaw and roll for this airframe's turns
                    # (`Yaw - sin(pitch)*Roll`, outerloop.c) - bank-and-twist together IS the designed
                    # turn mechanism, not something layered on top of it. psi_ref (the quadshot's own
                    # heading reference) used to be set ONCE, before climb even starts, by the
                    # separate blocking `_turn_to_heading()` call, then left frozen for the rest of the
                    # engagement while only roll did any further correcting. Now nudged continuously
                    # toward the target's REAL current bearing throughout climb too - `yaw_stick_rate`
                    # already integrates into psi_ref unconditionally from t=0 (the live_frac fix), so
                    # this was reachable, just never used. NOT calibrated against a measured
                    # interceptor-mode yaw-rate constant (no equivalent of `_PN_BANK_PER_STICK_DEG` or
                    # a "yawstep"-under-Interceptor test exists yet, unlike roll/pitch above) -
                    # deliberately conservative (small P-gain, tight clamp) and logged every tick via
                    # [yawdbg] so the first live run doubles as that missing measurement, honest about
                    # not yet being validated the way roll and pitch now are.
                    bearing_to_tgt = math.degrees(math.atan2(te - e, tn - n))
                    yaw_err = _heading_error(bearing_to_tgt, gb.fc_state.yaw)
                    # Ablation switch (2026-09-21, TRANSITION_THEORY.md section 20.5 item 1): lets a
                    # regression-hunt run isolate this yaw term from the pitch term above without
                    # another edit. Default on (1) - this is a debugging knob, not a tuning default.
                    if os.environ.get("NINJAPILOT_CLIMB_YAW_ENABLE", "1") == "1":
                        gb.control.yaw = max(-0.20, min(0.20, yaw_err / 90.0))
                    else:
                        gb.control.yaw = 0.0
                    if os.environ.get("NINJAPILOT_VERBOSE") == "1":
                        now_yaw = time.time()
                        if now_yaw - _yaw_debug_last_print[0] > 0.5:
                            _yaw_debug_last_print[0] = now_yaw
                            print("[wroom] yawdbg fc_yaw=%+6.1f bearing=%+6.1f err=%+6.1f stick=%+.3f"
                                  % (gb.fc_state.yaw, bearing_to_tgt, yaw_err, gb.control.yaw), flush=True)
                else:
                    gb.control.pitch = 0.0
                    gb.control.yaw = 0.0
            else:
                gb.control.roll = 0.0
                gb.control.pitch = 0.0
                gb.control.yaw = 0.0
        if phase == "leg_climb":
            if elapsed >= climb_s:
                phase, t_phase0 = "leg_transition", now
        elif phase == "leg_transition":
            if now - t_phase0 >= transition_s + 1.0:
                phase = "leg_cruise"
                gb.control.throttle = cruise_thr
                # Hold at the altitude the transition ACTUALLY, LIVE reaches (the real `alt` read this
                # same tick), not a computed staging_alt+constant - see intercept_test()'s own comment on
                # _INTERCEPT_TRANSITION_OVERSHOOT_M for why forcing a descent back to staging_alt is
                # wrong (fights a real, repeatable climb overshoot this airframe cannot correct within an
                # engagement's own time budget - this session's actual dominant miss factor, measured
                # directly via [pndbg], not a horizontal-steering problem). Self-measuring here (rather
                # than trusting the same fixed constant twice) means this holds correctly even if the real
                # overshoot varies run to run or if cruise_pitch/climb_s/rate/staging_alt ever change -
                # gb.TARGET_ALT still uses the constant (the target has to be spawned/moving well before
                # this point, so it can't self-measure the same way), so this refinement narrows, rather
                # than eliminates, how far apart the two can drift.
                trim = ClimbTrim(cruise_thr, alt)
        else:  # leg_cruise: steer via Proportional Navigation (_intercept_pn_roll), recomputed every tick
            dt = 0.05
            tstate = get_target()
            if tstate is not None:
                last_tgt = tstate
            if last_tgt is None:
                time.sleep(dt)
                continue
            tn, te, talt, tvn, tve, _tgt_valt = last_tgt
            # TARGET-ALTITUDE TRACKING (2026-09-21, found via [fovdbg] on seed 4 of the visual-lock
            # regression - see TRANSITION_THEORY.md section 18.3): ClimbTrim was built to hold the
            # interceptor's OWN post-transition altitude, frozen once at CRUISE entry (see that
            # assignment's own comment above) - a fine approximation ONLY if the target stays at
            # that same altitude for the whole engagement. A target with any nonzero AoA (climbing or
            # diving) does not: seed 4's real trace closed to 1.0m HORIZONTALLY (tighter than the one
            # confirmed hit) with the target still centered in the FOV, then still missed on 3D
            # distance and flew past - because ClimbTrim kept holding its stale CRUISE-entry snapshot
            # while the (AoA=-13.9 deg, i.e. diving) target had actually descended meaningfully by
            # then. Re-targeting every tick to the target's REAL, CURRENT altitude (already tracked
            # right above for horizontal guidance) closes this gap the same way PN already closes the
            # horizontal one - ClimbTrim's own docstring already frames it as "a GUIDANCE-layer fix,
            # exactly where the wroom stack already does all its position/altitude closure", so this
            # is that same idea, just no longer frozen at one instant.
            if trim is not None:
                trim.target_alt = talt
            gb.control.throttle = trim.update(alt, climb, dt) if trim else cruise_thr
            # 3D distance for scoring/divergence/stall (a purely horizontal check let a real ~11m
            # vertical miss get reported as "arrived" once - see TRANSITION_THEORY.md section 12).
            # Steering itself stays 2D - bearing is inherently a horizontal-plane concept here, since
            # this leg does not steer altitude (ClimbTrim owns that separately).
            dist = math.sqrt((tn - n) ** 2 + (te - e) ** 2 + (talt - alt) ** 2)
            if dist < closest["dist"]:
                closest["dist"] = dist
                closest["t"] = elapsed
                closest["horiz"] = math.hypot(tn - n, te - e)
                closest["vert"] = talt - alt   # signed: positive = target ABOVE the interceptor
            vfwd = math.hypot(vn, ve)
            # Proportional Navigation (2026-09-20, see _intercept_pn_roll's own docstring for the
            # references and reasoning) - commands roll DIRECTLY from LOS rotation rate via a
            # coordinated-turn conversion, replacing the old bearing-to-a-recomputed-aim-point plus a
            # SEPARATE heading-error P+I stage. That old approach chased a snapshot target heading
            # through its own P+I integrator on TOP OF path_intercept()'s own lead/rate-limit logic -
            # two control stages fighting the same job. PN closes the loop on the LOS rate directly, the
            # textbook right variable for a constant-speed, bank-to-turn vehicle.
            gb.control.roll = _intercept_roll(n, e, vn, ve, tn, te, tvn, tve, vfwd, dist=dist)
            # ADAPTIVE CRUISE-PITCH SHALLOWING - TRIED AND REVERTED (2026-09-21, see
            # TRANSITION_THEORY.md section 22 for the full story). Hypothesis: shallowing the dive would
            # give ClimbTrim's throttle loop more real authority to close a persistent vertical gap.
            # Tested on seed 4 (the hard case this was built for): no improvement, vertical gap got
            # marginally WORSE (6.02m vs 5.5-5.9m) despite pitch shallowing to -33/-35 deg. Tested on
            # seed 3 (a previously reliable hit, 6 consecutive clean hits this session): a REAL
            # regression - roll grew to 33 deg, throttle crashed toward THR_MIN (0.76 -> 0.22), and
            # altitude CLIMBED anyway (37.97 -> 42.64m) while the bias kept increasing trying to correct
            # a "target below" gap it was making worse, not better. This is the SAME nonlinear
            # aerodynamic signature the throttle-slew experiment already found (section 20.4): at this
            # cruise speed/attitude regime, reducing dive angle OR reducing thrust both tend to INCREASE
            # net altitude, not decrease it - a real physical effect no linear ClimbTrim-style model
            # will fix, and this session's second independent confirmation of it. Reverted to the plain
            # `gb.control.pitch = 0.0` this file used throughout every one of its actual hits.
            gb.control.pitch = 0.0
            # VISUAL-LOCK / MATCHED-PURSUIT (2026-09-20, user's reframing - see _visual_lock_check's
            # own module-level comment): tracked ADDITIVELY alongside the existing hit_dist scoring
            # below, not instead of it - a sustained, converging visual track is a SEPARATE way this
            # attempt can end in success, checked after the (stronger) kinematic hit_dist check so an
            # actual hit is never downgraded to a mere lock.
            in_fov, ang_off, horiz_range = _visual_lock_check(n, e, vn, ve, tn, te)
            if in_fov:
                if lock_start_t is None:
                    lock_start_t, lock_start_dist = now, dist
            else:
                lock_start_t, lock_start_dist = None, None
            if os.environ.get("NINJAPILOT_VERBOSE") == "1":
                now_fov = time.time()
                if now_fov - _fov_debug_last_print[0] > 0.5:
                    _fov_debug_last_print[0] = now_fov
                    print("[wroom] fovdbg in_fov=%s angle_off=%+6.1f range=%6.1f lock_s=%.1f"
                          % (in_fov, ang_off, horiz_range,
                             (now - lock_start_t) if lock_start_t is not None else 0.0), flush=True)
            if cruise_dist0 is None:
                cruise_dist0, cruise_t0 = dist, now
                dist_hist = [(now, dist)]
            if dist < hit_dist:
                status = "arrived"
                break
            if (lock_start_t is not None and now - lock_start_t >= _VISUAL_LOCK_HOLD_S
                    and lock_start_dist - dist >= _VISUAL_CONVERGE_MARGIN_M):
                print("[wroom] intercept leg_cruise: VISUAL LOCK sustained %.1fs, converged %.1fm -> "
                      "%.1fm (matched-pursuit criterion met - user's reframing, see wroom_pilot.py's "
                      "own comment on _visual_lock_check)"
                      % (now - lock_start_t, lock_start_dist, dist), flush=True)
                status = "visual_lock"
                break
            dist_hist.append((now, dist))
            dist_hist = [(t, d) for t, d in dist_hist if now - t <= DIVERGE_WINDOW_S]
            if now - dist_hist[0][0] >= DIVERGE_WINDOW_S - 0.5 and dist > dist_hist[0][1] + DIVERGE_MARGIN_M:
                print("[wroom] intercept leg_cruise: DIVERGING - dist %.1fm now vs %.1fm %.1fs ago - aborting"
                      % (dist, dist_hist[0][1], now - dist_hist[0][0]), flush=True)
                status = "diverging"
                break
            if now - cruise_t0 >= STALL_WINDOW_S:
                progress = (cruise_dist0 - dist) / max(cruise_dist0, 1.0)
                if progress < STALL_MIN_PROGRESS_FRAC:
                    print("[wroom] intercept leg_cruise: STALLED - only %.0f%% closed in %.0fs - aborting"
                          % (progress * 100.0, now - cruise_t0), flush=True)
                    status = "stalled"
                    break
                cruise_dist0, cruise_t0 = dist, now
        if ok:
            pilot.rec.row(phase, n, e, alt, vn, ve, climb)
        if not pilot.check_safety():
            return "safety", dist
        r, p, y = truth_rpy()
        if abs(r) > 50.0:
            print("[wroom] SAFETY: intercept leg roll=%.0f deg exceeds 50 - cutting throttle, disarming" % r, flush=True)
            gb.control.throttle = 0.0
            gb.control.roll = gb.control.pitch = gb.control.yaw = 0.0
            gb.control.armed = False
            pilot.fail_reason = "intercept leg tumbled: roll %.0f deg" % r
            return "safety", dist
        if now - last_log > 1.0:
            last_log = now
            print("[wroom] intercept %-14s t=%5.1f alt=%5.2f roll=%6.1f pitch=%6.1f dist=%6.1f thr=%.2f"
                  % (phase, elapsed, alt, r, p, dist, gb.control.throttle), flush=True)
        time.sleep(0.05)
    if closest["dist"] < 1e9:
        print("[wroom] intercept closest approach: 3d=%.2fm horiz=%.2fm vert=%+.2fm (target %s "
              "interceptor) at t=%.1fs"
              % (closest["dist"], closest["horiz"], closest["vert"],
                 "above" if closest["vert"] > 0 else "below", closest["t"]), flush=True)
    gb.control.mode_position = 0
    gb.control.roll = gb.control.pitch = 0.0
    gb.control.throttle = hover_thr
    pilot.tilt_check = True
    ok_recover, rn, re_, ralt, _rvn, _rve, _rclimb = pilot.nav()
    if ok_recover:
        pilot.fly_until(6.0, staging_alt, tgt_n=rn, tgt_e=re_, label="intercept_recover")
    return status, dist


def intercept_test():
    """NINJAPILOT_TEST_MODE=wroom_intercept: intercept a moving target using THIS airframe's actual
    fast-cruise capability for long-range closure, not the Revo-target intercept_test's hover-only
    ~1.5-2.6 m/s translate (that guidance was built and proven on a different, slower-cruise reference
    airframe - see TRANSITION_THEORY.md section 12). Reuses gazebo_bridge's own proven target-spawn/
    tracking/lead-solution code (gb.spawn_target/drive_target/lead_solution - the same math already
    validated on the Revo target) rather than inventing new guidance, and _fly_intercept_leg's climb/
    transition/cruise mechanics (copied from the star/oval mission's own proven _fly_interceptor_leg)
    rather than a new flight-control path.

    NOT yet mode-adaptive by range/speed (always engages interceptor mode once detected) - a hover-
    translate terminal phase for short-range/slow targets is the one open item from TRANSITION_THEORY.md
    section 13 this does not yet cover. Retry-from-real-position on a miss IS now covered (2026-09-20),
    reusing shape_test's own proven pattern (re-aim from the vehicle's REAL position, not a fictitious
    intended one - see that function's own comment on how skipping this once cost a 174m/277m miss)."""
    pilot = _start("wroom_intercept")
    if pilot is None:
        return
    import gz.transport13 as gztransport
    node = gztransport.Node()

    # 30m default, matching shape_test's own staging altitude - NOT the Revo intercept test's 11m
    # (that number is sized for a slow hover-translate engagement close to the pad; a real
    # interceptor-mode climb+transition was only ever validated at ~30m+ elsewhere in this project,
    # and a first pass at this default (11) never got the vehicle more than ~0.3m off the ground
    # during transition/cruise - staged too low for this maneuver, not a steering bug).
    staging_alt = float(os.environ.get("NINJAPILOT_INTERCEPT_ALT", "30"))
    cruise_pitch = float(os.environ.get("NINJAPILOT_INTERCEPTOR_CRUISE_PITCH", "-45"))
    hover_thrust = float(os.environ.get("NINJAPILOT_INTERCEPTOR_HOVER_THRUST", "0.65"))
    cruise_thr = interceptor_level_thrust(hover_thrust, cruise_pitch)
    climb_s = float(os.environ.get("NINJAPILOT_INTERCEPTOR_CLIMB_TIME", "3.0"))
    rate = float(os.environ.get("NINJAPILOT_INTERCEPTOR_TRANSITION_RATE", "15"))
    # This airframe's own measured cruise speed range (4-13 m/s, TRANSITION_THEORY.md section 2) - NOT
    # the Revo intercept test's INTERCEPT_SPEED=2.6, which is sized for a hover-only reference quad and
    # would throw away the entire point of engaging interceptor mode at all.
    cruise_speed = float(os.environ.get("NINJAPILOT_INTERCEPT_SPEED", "6.0"))
    pilot.CEILING_M = staging_alt + 20.0

    # BLIND-WINDOW LEAD (2026-09-20, found via [pndbg] on a randomized-geometry regression - see
    # TRANSITION_THEORY.md section 16/17): outerloop.c's own interceptor.live_frac is zero for the
    # entire CLIMB+TRANSITION duration (it only starts ramping once phase==CRUISE), meaning NO
    # steering correction of any kind reaches the airframe from the moment _turn_to_heading hands
    # off until cruise actually begins - roughly climb_s+transition_s+1.0 (7.0s at the defaults)
    # PLUS _turn_to_heading's own yaw+settle time (not knowable in advance, since it depends on how
    # far this very bearing calculation turns out to be from the vehicle's current heading -
    # estimated, not measured, at a fixed padding below). The FIXED-geometry validation set (section
    # 14's 6-hit streak) never exposed this: a near-zero-closest-approach collision course has an
    # aim direction that barely changes over 7-10s, so a stale one-shot aim happened to stay valid.
    # Any genuine crossing geometry (every randomized trial in section 16, closest-approach 0.9-8.9m)
    # does NOT have that property - the correct aim direction evolves meaningfully over the blind
    # window, and aiming at the target's CURRENT position/velocity (as this code did before) leaves
    # the vehicle badly mis-aimed by the time it can finally steer, confirmed directly: the very
    # first post-cruise [pndbg] tick in a reproduced failure showed los_rate=-1.33 rad/s (~76 deg/s)
    # - already a near-unrecoverable sweep rate before any correction had a chance to act. Fix:
    # extrapolate the target's position forward by the estimated blind-window duration (using its
    # own known constant velocity - the same physics `_intercept_bearing_deg`'s endgame lead already
    # relies on) before computing the initial aim, so the vehicle enters cruise already pointed
    # close to where the target will actually be, not where it was when the decision was made.
    _TURN_TO_HEADING_ESTIMATE_S = float(os.environ.get("NINJAPILOT_TURN_ESTIMATE_S", "3.0"))
    pre_cruise_blind_s = climb_s + abs(cruise_pitch) / max(rate, 1.0) + 1.0 + _TURN_TO_HEADING_ESTIMATE_S

    # SPAWN AND START DRIVING THE TARGET BEFORE TAKEOFF (2026-09-23, direct user finding from watching
    # the live GUI trail: "the ball starts traversing the screen AFTER the interceptor launches. Talk
    # about the dumbest mistake ever" - confirmed directly from trail_daemon's own log, not just a
    # visual impression: `flown=78 target=0 ... ball=no` lines showed the interceptor's own trail
    # already well underway before the ball model even existed in the world). Root cause: this block
    # used to run AFTER `pilot.takeoff()`+settle, so the target was spawned only once the interceptor
    # was already airborne and holding - backwards for what this is supposed to represent (an
    # incoming threat already inbound while the interceptor scrambles), not a fundamental miss cause
    # (detection is a real-time distance check regardless of spawn order) but a real scenario-realism
    # bug worth fixing on its own terms. Moved to BEFORE takeoff. The target's own velocity command
    # needs to keep being republished for it to keep moving (the same `_pub.publish(_tw)` the
    # detection-wait loop below already does every tick) - a background thread covers the
    # takeoff+settle window this block now precedes, stopping cleanly once the detection-wait loop's
    # own per-tick publish takes over, so there is never a gap OR a double-publish race.
    #
    # REAL ROOT CAUSE of this session's persistent ~7-10m "miss" ceiling, found 2026-09-20 by adding
    # [pndbg] diagnostics: at closest approach, horizontal separation was only ~2.7m (PN's own steering
    # working fine) while the ALTITUDE gap was ~7m - the interceptor was 7+ meters ABOVE the target the
    # entire cruise, not off to the side. Climb+transition consistently overshoots staging_alt by a
    # repeatable ~9.5-10m before cruise even starts (measured directly: cruise entry alt lands at
    # ~39.5-40m from a 30m staging_alt, across every single guidance law tried this session - not a
    # fluke of any one steering approach). `ClimbTrim` (this function's own docstring) is a throttle-only
    # closed loop; at this pitch/speed its real achievable descent rate is far slower than the ~1 m/s its
    # own math assumes (aerodynamic lift from forward airspeed fights the throttle reduction), so closing
    # a 9-10m altitude hole takes far longer than an engagement's own divergence/stall/timeout window
    # allows - every "miss" this session was mostly this gap never closing in time, not a horizontal
    # steering failure. Fix: spawn/drive the target at the altitude the interceptor actually settles at
    # after transition (measured directly, not guessed), not at the nominal staging_alt - this removes
    # the need for ClimbTrim to correct a large hole at all, letting the (already working) horizontal
    # guidance actually convert its own convergence into a real hit. ClimbTrim's OWN hold target is
    # matched to the same altitude below (_fly_intercept_leg), not left at raw staging_alt, or it would
    # fight to descend AWAY from the (now correctly relocated) target instead of holding at it.
    gb.TARGET_ALT = staging_alt + _INTERCEPT_TRANSITION_OVERSHOOT_M
    if not gb.spawn_target(node):
        print("[wroom] intercept: FAIL - could not spawn target", flush=True)
        _finish(pilot, "FAIL - could not spawn target")
        return
    # Real Gazebo contact -> real physics response (2026-09-20, user request): without this, a
    # hit ball just keeps flying its programmed track forever, untouched. gb.subscribe_contact()
    # was already built for the Revo path (_intercept_run) but this WROOM path never called it,
    # relying only on a software distance check to score "arrived" - which still works for
    # scoring, but the ball itself never physically reacted. subscribe_contact()'s own callback
    # calls gb.release_target_to_gravity() on the real sensor's first report, swapping the
    # kinematic ball for a free (gravity-on, no velocity control) dynamic body at that pose -
    # real physics then computes the actual equal-and-opposite reaction (the interceptor is
    # still overlapping it at that instant) and gravity takes over from there.
    gb.subscribe_contact(node)
    time.sleep(0.5)
    tvel, _pub, _tw = gb.drive_target(node)
    print("[wroom] intercept: target spawned and moving - now taking off", flush=True)
    _target_drive_stop = threading.Event()

    def _keep_driving_target():
        while not _target_drive_stop.is_set():
            _pub.publish(_tw)
            time.sleep(0.1)
    threading.Thread(target=_keep_driving_target, daemon=True).start()

    ok = pilot.takeoff(staging_alt, timeout=60.0)
    if ok:
        ok = pilot.fly_until(3.0, staging_alt, tgt_n=0.0, tgt_e=0.0, label="settle")
    _target_drive_stop.set()   # hand off to the detection-wait loop's own per-tick publish below
    if not ok:
        _finish(pilot, "FAIL - %s" % (pilot.fail_reason or "did not get airborne"))
        return

    def get_target():
        st = gb._target_state[0]
        if st is None:
            return None
        _, tned = st
        # 6th element added (2026-09-21, direct user correction: "you KNOW the heading of the ball,
        # and its speed at ALL times... just assume you always have perfect tracking" - the target's
        # real vertical velocity was already known (gb.TARGET_CLIMB_MPS, real and constant per engagement,
        # not estimated) but this tuple discarded it. tvel[2] is NED-down (drive_target()'s own
        # convention); negated back to +up to match talt's own +up sign here.
        return (tned[0], tned[1], -tned[2], tvel[0], tvel[1], -tvel[2])

    print("[wroom] intercept: watching for inbound within %.0fm..." % gb.DETECT_RANGE, flush=True)
    # Real, reproduced bug (2026-09-20): this loop used to only READ pilot.nav() and never called
    # pilot.tick()/anything that commands the vehicle - it just left whatever stick values `settle`
    # last set frozen for up to 60s while watching for the target. That is flying blind, the exact
    # thing this project's own steering loops elsewhere refuse to do (see _fly_interceptor_leg's
    # continuous divergence/stall checks). It happened to go unnoticed while detection was fast in
    # earlier runs; the run where detection took ~48s crashed hard (30m -> 0.2m, pitch 73 deg) with
    # a 50s gap of zero logged control activity right before the tilt-over trip. Fixed by holding
    # position/altitude with pilot.tick() every iteration, exactly like every other wait loop here.
    ok0, hold_n, hold_e, _hold_alt, _hvn, _hve, _hclimb = pilot.nav()
    if not ok0:
        _finish(pilot, "FAIL - lost nav before detection wait")
        return
    t_watch = time.time()
    detected = False
    # Real visual-acquisition logging (2026-09-23, direct user request - see _visual_lock_check's own
    # docstring for the real camera-detection plumbing this reuses): does NOT gate engagement - this
    # airframe holds a fixed attitude during the passive detection wait rather than actively scanning,
    # so requiring real visual to trigger the engagement itself could hang indefinitely for any
    # geometry that doesn't happen to cross this camera's ~69 deg FOV during that hold. Distance-based
    # detection stays the actual trigger (a reasonable stand-in for "a cueing sensor with its own,
    # wider field of regard" - a radar/RWR cue, not the terminal camera). This just reports the honest
    # answer to "did we actually SEE it (not just get cued to it) before engaging" for every run.
    visual_acquired_at = [None]
    while time.time() - t_watch < 60.0:
        _pub.publish(_tw)
        if not pilot.tick(staging_alt, tgt_n=hold_n, tgt_e=hold_e, dt=0.1):
            _finish(pilot, "FAIL - %s" % (pilot.fail_reason or "safety trip during detection wait"))
            return
        ok2, n, e, alt, _vn, _ve, _climb = pilot.nav()
        if visual_acquired_at[0] is None and gb.get_camera_ball_bearing() is not None:
            visual_acquired_at[0] = time.time() - t_watch
            print("[wroom] intercept: real camera visual acquired at t=%.1fs into detection wait"
                  % visual_acquired_at[0], flush=True)
        tstate = get_target()
        if ok2 and tstate is not None:
            d = math.hypot(tstate[0] - n, tstate[1] - e)
            if d < gb.DETECT_RANGE:
                print("[wroom] intercept: *** CONTACT DETECTED at %.1fm - engaging interceptor mode "
                      "(real visual %s) ***"
                      % (d, ("acquired at t=%.1fs" % visual_acquired_at[0]) if visual_acquired_at[0]
                         is not None else "NOT yet acquired"), flush=True)
                detected = True
                break
        time.sleep(0.1)
    if not detected:
        print("[wroom] intercept: FAIL - target never came within detection range", flush=True)
        _finish(pilot, "FAIL - no detection")
        return

    # max_leg_s raised 30 -> 60: the first working run (2026-09-20) was still closing steadily
    # (32.5m -> 16.1m, ~0.76 m/s net) when it timed out at 30s, not diverging or stalling - it just
    # needed more time, not a different steering law.
    max_leg_s = float(os.environ.get("NINJAPILOT_INTERCEPT_MAX_LEG_S", "60.0"))

    # RETRY-FROM-REAL-POSITION, ported from shape_test's own proven pattern (2026-09-20): a miss
    # (diverging/stalled/timeout) re-attacks from wherever the vehicle actually ended up, re-aimed at
    # the target's CURRENT (moved) position - not the original engagement geometry, and not a fictitious
    # "should have arrived" position. shape_test's own comment on this exact pattern: skipping it once
    # cost a 174m miss on leg 2 and a 277m miss on leg 3 of one star mission, in a straight line, because
    # the retry started from where the vehicle was SUPPOSED to be rather than where it REALLY was.
    # "safety" (a tumble/disarm) is not retried - there is no vehicle left in a state worth re-aiming.
    # Temporarily forced to 1 (2026-09-20, explicit direction): the first-pass engagement is what
    # matters right now - retry masked how well/badly a single pass performs by averaging it with
    # follow-up attempts at different geometry. Revisit once first-pass reliability itself is solid.
    MAX_INTERCEPT_ATTEMPTS = int(os.environ.get("NINJAPILOT_INTERCEPT_MAX_ATTEMPTS", "1"))
    status, final_dist = "timeout", 1e9
    for attempt in range(1, MAX_INTERCEPT_ATTEMPTS + 1):
        # REQUIRED handoff step, copied from shape_test's own proven pattern (it is NEVER skipped there -
        # every _fly_interceptor_leg call is immediately preceded by _turn_to_heading). Missing this the
        # first time round caused a real, reproduced crash: the vehicle plummeted 30m -> 0.3m within the
        # first ~4s of leg_climb/leg_transition, twice, identically. _turn_to_heading actively holds
        # altitude (a real closed loop, not a stale throttle value) AND yaws the nose to face the intended
        # travel direction before interceptor mode's pitch-over engages - without it, the pitch-over
        # rotates the vehicle nose-first into whatever direction it happened to be facing after a passive
        # detection-wait loop (or a prior failed attempt), not the direction it is about to fly.
        ok3, n0, e0, alt0, _vn0, _ve0, _climb0 = pilot.nav()
        tstate0 = get_target()
        if not (ok3 and tstate0 is not None):
            print("[wroom] intercept attempt %d: FAIL - lost nav or target track before re-aiming"
                  % attempt, flush=True)
            status = "safety"
            break
        # REPLACED (2026-09-21, direct user correction: "if you'd lead properly, set a proper
        # predictive angle for takeoff, then transition into forward flight there is ZERO reason to
        # not nail the intercept" - and separately, the referenced Zheng & Chen 2021 paper's own actual
        # point, which this file cited but never fully applied: solve the exact intercept geometry
        # once, precisely, rather than soft-correct afterward). The PRIOR version of this block
        # extrapolated the target only to the END of the blind window (climb+transition duration), then
        # aimed the nose at THAT point - not at the target's position at the moment intercept actually
        # happens, which is LATER (by however long cruise then takes to close the remaining distance,
        # often several more seconds). That remaining gap was never fed back into the initial aim at
        # all. `_solve_intercept_lead()` (see its own docstring) fixes this: it solves for the FULL
        # intercept time (blind window + cruise-closing time, self-consistently, not just the first
        # piece), and now ALSO the target's predicted ALTITUDE at that exact moment - the vertical
        # component of leading, which the file's whole altitude-tracking history (sections 19-21) had to
        # keep correcting REACTIVELY, tick by tick, because it was never part of the INITIAL aim to
        # begin with. `lead_alt0` is stashed for the climb to aim at directly (see its own use in
        # `_fly_intercept_leg` below) instead of only reacting to the gap once airborne.
        t_intercept, tgt_n0, tgt_e0, lead_alt0 = _solve_intercept_lead(
            n0, e0, alt0, tstate0[0], tstate0[1], tstate0[2], tstate0[3], tstate0[4], tstate0[5],
            pre_cruise_blind_s, cruise_speed)
        bearing0 = math.degrees(math.atan2(tgt_e0 - e0, tgt_n0 - n0))
        print("[wroom] intercept attempt %d/%d: re-aiming from (%.1f,%.1f,%.1f) at t+%.1fs (full "
              "intercept solve, not just blind-window) predicted (%.1f,%.1f,%.1f), bearing %.0f deg"
              % (attempt, MAX_INTERCEPT_ATTEMPTS, n0, e0, alt0, t_intercept, tgt_n0, tgt_e0, lead_alt0,
                 bearing0), flush=True)
        # ADAPTIVE CLIMB DURATION (2026-09-23, see _solve_adaptive_climb_s's own module comment for the
        # full reasoning): solve for a climb_s that leaves post-transition altitude near lead_alt0
        # instead of the fixed ~9.5m overshoot every prior engagement used regardless of need. Pushed to
        # firmware via gb.push_stabilization_update() (new plumbing this same session, see its own
        # docstring for the whole-object-write hazard it is careful to avoid) BEFORE _turn_to_heading,
        # so it lands well before this attempt's climb begins - and the GROUND's own `climb_s` is
        # updated to match, so _fly_intercept_leg's phase-tracking stays synchronized with what firmware
        # is actually now doing (a real, previously-identified failure mode if these two ever disagree -
        # see this file's own comments on why _turn_to_heading is a REQUIRED handoff).
        if os.environ.get("NINJAPILOT_ADAPTIVE_CLIMB_ENABLE", "1") == "1":
            desired_overshoot = lead_alt0 - staging_alt
            adaptive_climb_s = _solve_adaptive_climb_s(desired_overshoot)
            print("[wroom] intercept attempt %d: adaptive climb_s %.2f -> %.2f (desired overshoot %.1fm)"
                  % (attempt, climb_s, adaptive_climb_s, desired_overshoot), flush=True)
            gb.push_stabilization_update("InterceptorClimbTime", adaptive_climb_s)
            time.sleep(0.3)   # let uavtalk_thread's own loop notice and send it before climb begins
            climb_s = adaptive_climb_s
        # Measures _TURN_TO_HEADING_ESTIMATE_S's real accuracy (2026-09-20) - that estimate is the one
        # un-measured piece of pre_cruise_blind_s (climb_s/rate/transition math are all known exactly
        # in advance; how long the actual yaw+settle takes is not). Logged so it can be calibrated
        # against real data instead of left as a guessed constant.
        # LOOSENED (2026-09-21, direct user correction: "how late to the party the interceptor is
        # after literally being there first, hovering"): tolerance_deg=1.0 + the default 2.5s
        # hold_settle_s were sized back when climb+transition were FULLY BLIND (zero ground steering
        # reached the airframe until CRUISE) - the one-shot pre-engagement aim had to be as precise as
        # physically achievable because nothing could correct it for the next ~7-10s. That is no
        # longer true: the live_frac fix (2026-09-20) plus this session's own continuous climb-pitch
        # fix (_intercept_pitch_to_target, right above) mean BOTH bearing (roll) and elevation (pitch)
        # are corrected continuously throughout climb now. Paying a slow, "weak, prop-torque-only yaw"
        # (this file's own _turn_to_heading docstring) rotation down to within 1 degree, THEN holding
        # that for a flat 2.5s more, before even starting to move, was measured costing 3.7-10.1s of
        # pure dead time on every single engagement - often longer than climb_s itself. Loosened to the
        # shared 6 deg default (shape_test's own proven tolerance) and a much shorter 0.5s settle -
        # good enough to fix psi_ref's one-time capture in the right ballpark, with climb's own
        # continuous correction now doing the fine work that _turn_to_heading used to have to do alone.
        # Overridable (2026-09-21, see TRANSITION_THEORY.md section 20.5 item 1): the loosened 6.0/0.5
        # defaults above cut latency a lot but regressed seed 1/2's visual-lock convergence quality -
        # exposed here rather than hardcoded so a middle ground can be tried without another edit.
        _turn_tol_deg = float(os.environ.get("NINJAPILOT_TURN_TOLERANCE_DEG", "6.0"))
        _turn_settle_s = float(os.environ.get("NINJAPILOT_TURN_SETTLE_S", "0.5"))
        _turn_t0 = time.time()
        if not _turn_to_heading(pilot, bearing0, n0, e0, staging_alt, tolerance_deg=_turn_tol_deg,
                                 hold_settle_s=_turn_settle_s):
            _finish(pilot, "FAIL - %s" % (pilot.fail_reason or "turn-to-heading failed"))
            return
        print("[wroom] intercept attempt %d: _turn_to_heading took %.1fs (estimate was %.1fs)"
              % (attempt, time.time() - _turn_t0, _TURN_TO_HEADING_ESTIMATE_S), flush=True)

        status, final_dist = _fly_intercept_leg(pilot, get_target, staging_alt, cruise_pitch, cruise_thr,
                                                 climb_s, rate, cruise_speed, hit_dist=1.5, max_leg_s=max_leg_s,
                                                 lead_alt=lead_alt0)
        print("[wroom] intercept attempt %d: %s at %.2fm" % (attempt, status, final_dist), flush=True)
        if status in ("arrived", "visual_lock", "safety"):
            # visual_lock is treated as a terminal success here too (2026-09-20, user's reframing) -
            # a sustained, converging visual track is a real engagement outcome, not a failed attempt
            # worth re-aiming and trying again from scratch.
            break
        if attempt < MAX_INTERCEPT_ATTEMPTS:
            print("[wroom] intercept attempt %d: %s - retrying from the real position above"
                  % (attempt, status), flush=True)

    # FIXED (2026-09-21, reversing the 2026-09-20 "deliberately not fixed" call above - superseded by
    # watching a live miss): descend_and_land() defaulted to tgt_n=0, tgt_e=0 - the ORIGIN PAD, not the
    # vehicle's real position - so on anything short of a hit, the vehicle flew all the way back toward
    # the pad before landing, regardless of where the engagement actually left it. The earlier reasoning
    # ("a real interception is terminal, so this doesn't matter") only holds when every run hits; misses
    # are still a real fraction of outcomes (section 17/18/19), and on a miss this produced exactly the
    # confusing behavior it looks like from the outside: the vehicle appears to fly back toward the
    # target's OWN flight path (every randomized track passes within 0-12m of the pad by construction -
    # see randomize_target_track()) and land there, long after the real target has moved on - which
    # reads as "chasing a stale point" even though it was actually just going home. Landing at the
    # vehicle's REAL current position (already recovered to, by _fly_intercept_leg's own
    # "intercept_recover" leg above) removes that dead, purposeless leg entirely, on a hit OR a miss.
    ok_land0, land_n, land_e, _land_alt, _land_vn, _land_ve, _land_climb = pilot.nav()
    landed = pilot.descend_and_land(tgt_n=land_n, tgt_e=land_e) if ok_land0 else pilot.descend_and_land()
    if status == "arrived":
        verdict = ("PASS - closed to %.2fm (hit_dist 1.5m)" % final_dist if landed
                   else "FAIL - arrived, closed to %.2fm, but landing failed" % final_dist)
    elif status == "visual_lock":
        # Separate PASS wording, deliberately not reusing the "closed to Xm (hit_dist)" phrasing - a
        # visual-lock success is NOT a kinematic hit, and the verdict line should say so plainly rather
        # than let a hit_dist-shaped string imply a collision occurred.
        verdict = ("PASS (visual lock, matched pursuit) - sustained visual track, converged to %.2fm "
                   "without a direct hit" % final_dist if landed
                   else "FAIL - visual lock achieved (%.2fm) but landing failed" % final_dist)
    else:
        verdict = "FAIL - %s, closed to %.2fm" % (status, final_dist)
    _finish(pilot, verdict)


def shape_test():
    """NINJAPILOT_TEST_MODE=wroom_shape, NINJAPILOT_SHAPE=star|oval (default star).
    Flies the shape's straight legs in interceptor mode (climb-trim on),
    corners in hover, transitioning between the two modes at every vertex."""
    pilot = _start("wroom_shape")
    if pilot is None:
        return
    shape = os.environ.get("NINJAPILOT_SHAPE", "star")
    staging_alt = float(os.environ.get("NINJAPILOT_SHAPE_ALT", "30"))
    cruise_pitch = float(os.environ.get("NINJAPILOT_INTERCEPTOR_CRUISE_PITCH", "-45"))
    hover_thrust = float(os.environ.get("NINJAPILOT_INTERCEPTOR_HOVER_THRUST", "0.65"))
    cruise_thr = interceptor_level_thrust(hover_thrust, cruise_pitch)   # matches the firmware's own auto thrust - see transition_test
    # MUST equal gazebo_bridge.py's own InterceptorClimbTime default (3.0) - this is Python's guess at when the
    # FIRMWARE'S internal phase (CLIMB -> TRANSITION -> CRUISE) advances, and the two diverging is exactly what made
    # the first star attempt hang stuck on the ground at max throttle: Python moved on to "leg_cruise" steering
    # (sending roll/thrust the firmware was still ignoring because IT was still in CLIMB/TRANSITION by its own,
    # longer clock) 2026-09-19.
    climb_s = float(os.environ.get("NINJAPILOT_INTERCEPTOR_CLIMB_TIME", "3.0"))
    rate = float(os.environ.get("NINJAPILOT_INTERCEPTOR_TRANSITION_RATE", "15"))
    pilot.CEILING_M = staging_alt + 25.0
    if shape == "oval":
        radius = float(os.environ.get("NINJAPILOT_SHAPE_RADIUS", "120"))
        waypoints = _oval_waypoints(radius, radius * 0.55, n_points=int(os.environ.get("NINJAPILOT_SHAPE_POINTS", "10")))
    else:
        radius = float(os.environ.get("NINJAPILOT_SHAPE_RADIUS", "90"))
        waypoints = _star_waypoints(radius, n_points=int(os.environ.get("NINJAPILOT_SHAPE_POINTS", "5")))
    print("[wroom] shape_test: flying %s, %d legs, radius %.0fm, staging alt %.0fm, cruise %.0f deg / thr %.2f"
          % (shape, len(waypoints) - 1, radius, staging_alt, cruise_pitch, cruise_thr), flush=True)

    trail_node = gb.transport.Node()
    plan_wps = [{"Position": [wn, we, -staging_alt]} for wn, we in waypoints]
    try:
        gb.publish_planned_trail(trail_node, plan_wps)
        gb.gui_follow(trail_node)
    except Exception as exc:
        print("[wroom] shape_test: trail/GUI setup skipped (%s)" % exc, flush=True)
    flown = gb.FlownTrail(trail_node)

    ok = pilot.takeoff(staging_alt, timeout=max(25.0, staging_alt * 2.0))
    if ok:
        ok = pilot.fly_until(4.0, staging_alt, tgt_n=0.0, tgt_e=0.0, label="settle")
    legs_flown = 0
    cur_n, cur_e = 0.0, 0.0
    # 2026-09-19 directive: a leg that doesn't sensor-confirm arrival is NEVER silently treated as done. It is
    # retried - fresh turn, fresh settle, fresh interceptor engagement, from wherever the vehicle REALLY is - up to
    # MAX_LEG_RETRIES times. Exhausting retries on one waypoint stops the whole mission and lands; the mission does
    # not press on to later legs pretending an unreached one worked.
    MAX_LEG_RETRIES = 3
    if ok:
        for i in range(1, len(waypoints)):
            tgt_n, tgt_e = waypoints[i]
            attempt = 0
            leg_status = "timeout"
            while attempt < MAX_LEG_RETRIES:
                attempt += 1
                bearing = math.degrees(math.atan2(tgt_e - cur_e, tgt_n - cur_n))
                print("[wroom] === leg %d/%d attempt %d/%d: (%.1f,%.1f) -> (%.1f,%.1f), bearing %.0f deg ==="
                      % (i, len(waypoints) - 1, attempt, MAX_LEG_RETRIES, cur_n, cur_e, tgt_n, tgt_e, bearing), flush=True)
                # DIAGNOSTIC 2026-09-19: NINJAPILOT_SHAPE_SKIP_TURN=1 skips the hover yaw-to-heading turn entirely
                # (whole star, not just leg 1), to isolate whether _turn_to_heading's yaw-stick usage destabilizes
                # the very next interceptor engagement, versus a bug independent of it. _turn_to_heading now holds
                # the settle time itself (actively yaw-corrected the whole way, see its own docstring for why a
                # separate plain fly_until() settle used to let heading drift right before capture) - the fallback
                # plain settle here only exists for the skip-turn diagnostic path, which has no active yaw hold at all.
                if os.environ.get("NINJAPILOT_SHAPE_SKIP_TURN", "0") != "1":
                    if not _turn_to_heading(pilot, bearing, cur_n, cur_e, staging_alt):
                        ok = False
                        break
                else:
                    if not pilot.fly_until(2.5, staging_alt, tgt_n=cur_n, tgt_e=cur_e, label="leg_settle"):
                        ok = False
                        break
                leg_status = _fly_interceptor_leg(pilot, tgt_n, tgt_e, staging_alt, cruise_pitch, cruise_thr,
                                                   climb_s, rate, flown=flown)
                # the ACTUAL position, not the intended target - retrying (or moving on) from a fictitious position
                # is exactly how a star flight 2026-09-19 missed leg 2 by 174m and leg 3 by 277m in a straight line.
                _leg_ok, cur_n, cur_e, _leg_alt, _vn, _ve, _climb = pilot.nav()
                if not _leg_ok:
                    cur_n, cur_e = tgt_n, tgt_e
                if leg_status == "arrived":
                    break
                if leg_status == "safety":
                    ok = False
                    break
                print("[wroom] leg %d attempt %d: %s - %s"
                      % (i, attempt, leg_status,
                         "retrying from the real position above" if attempt < MAX_LEG_RETRIES else "retries exhausted"),
                      flush=True)
            if not ok:
                break
            if leg_status != "arrived":
                ok = False
                pilot.fail_reason = ("leg %d never arrived after %d attempts (last: %s)"
                                      % (i, MAX_LEG_RETRIES, leg_status))
                print("[wroom] MISSION ABORT: %s - landing now, not continuing to later legs" % pilot.fail_reason,
                      flush=True)
                break
            legs_flown += 1
    landed = False
    if True:   # land from wherever this ended, success or failure - never leave it airborne on an abort
        landed = pilot.descend_and_land(tgt_n=cur_n, tgt_e=cur_e)
    verdict = ("PASS - flew all %d legs of the %s and landed" % (legs_flown, shape)
               if (ok and landed and legs_flown == len(waypoints) - 1)
               else "FAIL - %s (%d/%d legs)" % (pilot.fail_reason or "did not complete", legs_flown, len(waypoints) - 1))
    _finish(pilot, verdict)


# ---------------------------------------------------------------------------
# NINJAPILOT_TEST_MODE=wroom_cruisecontrol
#
# Does OpenPilot's existing CruiseControl thrust mode (its bank-angle boost
# factor - see flight/modules/Stabilization/cruisecontrol.c) measurably help
# THIS top-heavy airframe hold altitude during an aggressive hover bank,
# compared to plain Manual thrust? Switch positions 3 and 4 already default,
# upstream and unmodified by this project, to Stabilized4/5 with CruiseControl
# on the thrust axis - this test exercises that stock config directly, no new
# firmware. See INTERCEPTOR_FLIGHT_LOG.md section 8's "novel hover-mode use"
# open item.
# ---------------------------------------------------------------------------
def cruisecontrol_test():
    pilot = _start("wroom_cruisecontrol")
    if pilot is None:
        return
    staging_alt = float(os.environ.get("NINJAPILOT_SHAPE_ALT", "20"))
    pilot.CEILING_M = staging_alt + 15.0   # default 20.0 == this test's own staging_alt default - any recovery
                                            # overshoot past that tripped the hard-ceiling safety trap immediately
                                            # (cc01: manual_thrust's altitude LOSS was the real, useful data; the
                                            # verdict FAIL came only from its recovery climb touching the ceiling)
    bank_stick = float(os.environ.get("NINJAPILOT_CC_BANK_STICK", "0.7"))
    bank_s = float(os.environ.get("NINJAPILOT_CC_BANK_S", "6.0"))
    ok = pilot.takeoff(staging_alt)
    results = {}
    # (label, mode_position, StabilizationNSettings thrust axis)
    trials = [("manual_thrust", 0, "Manual (Stabilized1)"),
              ("cruisecontrol_thrust", 3, "CruiseControl (Stabilized4)")]
    for label, mode_pos, desc in trials:
        if not ok:
            break
        ok = pilot.fly_until(4.0, staging_alt, tgt_n=0.0, tgt_e=0.0, label="%s_settle" % label)
        if not ok:
            break
        baseline_thr = gb.control.throttle   # whatever just hovered it - held FIXED through the bank on purpose,
        gb.control.mode_position = mode_pos  # so any altitude difference between trials is the thrust MODE's doing,
        t0 = time.time()                     # not a closed loop quietly correcting for both
        alt0 = None
        alt_min = 99.0
        while time.time() - t0 < bank_s:
            gb.control.throttle = baseline_thr
            gb.control.roll = bank_stick
            gb.control.pitch = 0.0
            okn, n, e, alt, vn, ve, climb = pilot.nav()
            if okn:
                if alt0 is None:
                    alt0 = alt
                alt_min = min(alt_min, alt)
                pilot.rec.row(label, n, e, alt, vn, ve, climb)
            if not pilot.check_safety():
                ok = False
                break
            time.sleep(0.05)
        gb.control.roll = 0.0
        gb.control.mode_position = 0
        drop = (alt0 - alt_min) if alt0 is not None else float("nan")
        results[label] = drop
        print("[wroom] %-22s (%s): alt %.2f -> min %.2f, dropped %.2fm at stick=%.2f, baseline_thr=%.2f"
              % (label, desc, alt0 or -1, alt_min, drop, bank_stick, baseline_thr), flush=True)
        if ok:
            ok = pilot.fly_until(6.0, staging_alt, tgt_n=0.0, tgt_e=0.0, label="%s_recover" % label)
    landed = pilot.descend_and_land() if ok else False
    if "manual_thrust" in results and "cruisecontrol_thrust" in results:
        better = "cruisecontrol_thrust" if results["cruisecontrol_thrust"] < results["manual_thrust"] else "manual_thrust"
        print("[wroom] cruisecontrol_test: %s held altitude better (dropped %.2fm vs %.2fm)"
              % (better, results[better], results["manual_thrust" if better == "cruisecontrol_thrust" else "cruisecontrol_thrust"]),
              flush=True)
    verdict = ("PASS - compared manual vs cruisecontrol thrust during a %.0f-deg-stick bank" % (bank_stick * 100)
               if (ok and landed and len(results) == 2)
               else "FAIL - %s" % (pilot.fail_reason or "did not complete"))
    _finish(pilot, verdict)


# ---------------------------------------------------------------------------
# NINJAPILOT_TEST_MODE=wroom_rollstep
#
# A clean roll STEP response in CRUISE (not a proportional ramp like the mission steering law produces) - measures
# the roll axis's actual rise time/overshoot/settling, and roll-rate vs yaw-rate together through it, so a future
# gyroscopic-precession-exploiting "pump" steering law (see INTERCEPTOR_FLIGHT_LOG.md section 12) can be built
# SYNCHRONIZED to what this airframe actually does, instead of guessed. The first pump attempt used a blind 2.5s
# period and gave inconsistent results - this is the missing measurement that attempt needed first.
# ---------------------------------------------------------------------------
def rollstep_test():
    pilot = _start("wroom_rollstep")
    if pilot is None:
        return
    cruise_pitch = float(os.environ.get("NINJAPILOT_INTERCEPTOR_CRUISE_PITCH", "-45"))
    hover_thrust = float(os.environ.get("NINJAPILOT_INTERCEPTOR_HOVER_THRUST", "0.65"))
    cruise_thr = interceptor_level_thrust(hover_thrust, cruise_pitch)
    climb_s = float(os.environ.get("NINJAPILOT_INTERCEPTOR_CLIMB_TIME", "3.0"))
    rate = float(os.environ.get("NINJAPILOT_INTERCEPTOR_TRANSITION_RATE", "15"))
    step_stick = float(os.environ.get("NINJAPILOT_ROLLSTEP_STICK", "0.30"))
    pilot.CEILING_M = 55.0   # staging at 30m + climb + cruise excursion needs real headroom above the 20.0 default
    ok = pilot.takeoff(30.0, timeout=60.0)   # default 25s is sized for ~4m staging, not 30m (same bug as shape_test's)
    if ok:
        ok = pilot.fly_until(4.0, 30.0, tgt_n=0.0, tgt_e=0.0, label="settle")
    hover_thr_capture = gb.control.throttle
    if ok:
        pilot.tilt_check = False
        gb.control.mode_position = 2
        transition_s = abs(cruise_pitch) / max(rate, 1.0)
        t0 = time.time()
        while time.time() - t0 < climb_s:
            gb.control.throttle = hover_thr_capture
            gb.control.roll = gb.control.pitch = 0.0
            time.sleep(0.05)
        t0 = time.time()
        while time.time() - t0 < transition_s + 1.0:
            gb.control.throttle = hover_thr_capture
            gb.control.roll = gb.control.pitch = 0.0
            time.sleep(0.05)
        gb.control.throttle = cruise_thr   # trip the capture latch
        trim = ClimbTrim(cruise_thr, 30.0)
        # 3s settled at zero roll BEFORE the step - a clean baseline, no residual transition transient
        t0 = time.time()
        while time.time() - t0 < 3.0:
            ok2, _n, _e, alt, _vn, _ve, climb = pilot.nav()
            gb.control.throttle = trim.update(alt, climb, 0.05) if ok2 else cruise_thr
            gb.control.roll = 0.0
            gb.control.pitch = 0.0
            time.sleep(0.05)
        # THE STEP: snap to step_stick and hold. Log at full tick rate (not the usual 1Hz) - this needs resolution.
        print("[wroom] rollstep: applying step=%.2f, logging at ~20Hz for 6s" % step_stick, flush=True)
        t0 = time.time()
        prev_t, prev_roll, prev_yaw = None, None, None
        samples = []
        while time.time() - t0 < 6.0:
            now = time.time()
            ok2, n, e, alt, vn, ve, climb = pilot.nav()
            gb.control.throttle = trim.update(alt, climb, 0.05) if ok2 else cruise_thr
            gb.control.roll = step_stick
            gb.control.pitch = 0.0
            r, p, y = truth_rpy()
            # Ground-TRACK heading (from GPS velocity, atan2(ve, vn)) vs body YAW - a real, previously untested
            # distinction: outerloop.c's CRUISE steering banks the vehicle to curve the flight path (a real
            # thrust-vector-tilt turn, independent of yaw authority), while the YAW ANGLE plateau (section 12) is
            # about the NOSE direction specifically, via a separate gyroscopic-precession mechanism. If the ground
            # track curves substantially more than the nose does, that's a real, actionable distinction for
            # guidance (steer by velocity vector, not nose heading) even though yaw authority itself stays weak.
            track = math.degrees(math.atan2(ve, vn)) if math.hypot(vn, ve) > 0.3 else float("nan")
            roll_rate = yaw_rate = 0.0
            if prev_t is not None:
                rdt = max(now - prev_t, 0.01)
                roll_rate = (r - prev_roll) / rdt
                yaw_rate = _heading_error(y, prev_yaw) / rdt
            prev_t, prev_roll, prev_yaw = now, r, y
            samples.append((now - t0, r, roll_rate, y, yaw_rate, track, math.hypot(vn, ve)))
            if not pilot.check_safety():
                ok = False
                break
            time.sleep(0.05)
        for st, r, rr, y, yr, trk, vfwd in samples:
            print("[wroom] rollstep t=%5.2f roll=%6.1f roll_rate=%+6.1f/s yaw=%7.2f yaw_rate=%+6.2f/s track=%7.2f vfwd=%5.2f"
                  % (st, r, rr, y, yr, trk, vfwd), flush=True)
        # release, recover to hover
        gb.control.roll = 0.0
        gb.control.mode_position = 0
        pilot.tilt_check = True
        if ok:
            ok = pilot.fly_until(8.0, 30.0, tgt_n=None, tgt_e=None, label="recover")
    landed = pilot.descend_and_land() if ok else False
    verdict = ("PASS - logged roll step response at stick=%.2f" % step_stick
               if (ok and landed) else "FAIL - %s" % (pilot.fail_reason or "did not complete"))
    _finish(pilot, verdict)


def hoverstep_test():
    """The plain-hover (Attitude/Bank1) twin of rollstep_test's cruise (Interceptor/Bank3) roll step response -
    SAME stick, SAME logging, so the two can be compared directly. This is the concrete data point item 2 in
    INTERCEPTOR_FLIGHT_LOG.md's open items (Bank3 gain tuning) has been missing: Bank3 is currently just a copy of
    Bank1, and nobody has actually checked whether Bank1's gains are wrong for cruise, or just happen to already
    work - "the plumbing exists, the numbers are untuned" was an assumption, not a measurement.
    NINJAPILOT_ROLLSTEP_STICK (default 0.30, matching rollstep_test's own default so the two runs are directly
    comparable without extra arguments).
    """
    pilot = _start("wroom_hoverstep")
    if pilot is None:
        return
    staging_alt = float(os.environ.get("NINJAPILOT_SHAPE_ALT", "10"))
    pilot.CEILING_M = staging_alt + 15.0
    step_stick = float(os.environ.get("NINJAPILOT_ROLLSTEP_STICK", "0.30"))
    ok = pilot.takeoff(staging_alt)
    if ok:
        ok = pilot.fly_until(3.0, staging_alt, tgt_n=0.0, tgt_e=0.0, label="settle")
    if ok:
        print("[wroom] hoverstep: applying step=%.2f, logging at ~20Hz for 6s" % step_stick, flush=True)
        baseline_thr = gb.control.throttle
        t0 = time.time()
        prev_t, prev_roll, prev_yaw = None, None, None
        samples = []
        while time.time() - t0 < 6.0:
            now = time.time()
            gb.control.throttle = baseline_thr
            gb.control.roll = step_stick
            gb.control.pitch = 0.0
            r, p, y = truth_rpy()
            roll_rate = yaw_rate = 0.0
            if prev_t is not None:
                rdt = max(now - prev_t, 0.01)
                roll_rate = (r - prev_roll) / rdt
                yaw_rate = _heading_error(y, prev_yaw) / rdt
            prev_t, prev_roll, prev_yaw = now, r, y
            samples.append((now - t0, r, roll_rate, y, yaw_rate))
            if not pilot.check_safety():
                ok = False
                break
            time.sleep(0.05)
        for st, r, rr, y, yr in samples:
            print("[wroom] hoverstep t=%5.2f roll=%6.1f roll_rate=%+6.1f/s yaw=%7.2f yaw_rate=%+6.2f/s"
                  % (st, r, rr, y, yr), flush=True)
        gb.control.roll = 0.0
        if ok:
            ok = pilot.fly_until(4.0, staging_alt, tgt_n=None, tgt_e=None, label="recover")
    landed = pilot.descend_and_land() if ok else False
    verdict = ("PASS - logged hover roll step response at stick=%.2f" % step_stick
               if (ok and landed) else "FAIL - %s" % (pilot.fail_reason or "did not complete"))
    _finish(pilot, verdict)


def yaw_authority_test():
    """Hover (Attitude/Bank1) yaw step response - the direct A/B harness for comparing yaw-authority
    hardware changes (motor toe/cant angle, swirl-recovery vanes) against the unmodified airframe.
    Applies a fixed yaw stick and holds it, logging yaw rate (the actual authority metric - yaw has no
    settled angle to compare, unlike roll/pitch) plus roll/pitch/altitude to catch any coupling side
    effects a thrust-vector change could introduce (that's the "general controllability" question, not
    just "does yaw rate go up"). Same stick/logging shape as hoverstep_test/rollstep_test so results are
    directly comparable: run once against the baseline model.sdf, once against a modified one (e.g.
    toed rotor joint axes), diff the steady-state yaw rate and the roll/pitch/altitude excursions.
    NINJAPILOT_YAWSTEP_STICK (default 0.30).
    """
    pilot = _start("wroom_yawauth")
    if pilot is None:
        return
    staging_alt = float(os.environ.get("NINJAPILOT_SHAPE_ALT", "10"))
    pilot.CEILING_M = staging_alt + 15.0
    step_stick = float(os.environ.get("NINJAPILOT_YAWSTEP_STICK", "0.30"))
    bank_stick = float(os.environ.get("NINJAPILOT_YAWAUTH_ROLL", "0.0"))
    hold_s = float(os.environ.get("NINJAPILOT_YAWAUTH_HOLD_S", "6.0"))
    # Default takeoff timeout (25s) is sized for ~4m staging, not this test's higher altitudes -
    # same gotcha rollstep_test already documents. Scale it so a 30m+ staging climb doesn't spuriously FAIL.
    ok = pilot.takeoff(staging_alt, timeout=max(25.0, staging_alt * 2.0))
    if ok:
        ok = pilot.fly_until(3.0, staging_alt, tgt_n=0.0, tgt_e=0.0, label="settle")
    if ok and bank_stick:
        # Bank first, closed-loop altitude hold (ClimbTrim - same mechanism CruiseControl uses), THEN add yaw on
        # top once the bank has settled: this reproduces "yaw authority while banked hard" (the mixer headroom
        # squeeze from a large roll command competing with throttle-for-altitude), not an artificial fixed
        # high-throttle hover that just climbs uncontrolled.
        print("[wroom] yawauth: banking to roll=%.2f first (closed-loop altitude hold)" % bank_stick, flush=True)
        trim = ClimbTrim(gb.control.throttle, staging_alt)
        t0 = time.time()
        while time.time() - t0 < 3.0:
            ok2, _n, _e, alt, _vn, _ve, climb = pilot.nav()
            gb.control.throttle = trim.update(alt, climb, 0.05) if ok2 else gb.control.throttle
            gb.control.roll = bank_stick
            gb.control.pitch = 0.0
            if not pilot.check_safety():
                ok = False
                break
            time.sleep(0.05)
    else:
        trim = None
    if ok:
        print("[wroom] yawauth: applying yaw step=%.2f (bank=%.2f), logging at ~20Hz for %.1fs"
              % (step_stick, bank_stick, hold_s), flush=True)
        baseline_thr = gb.control.throttle
        t0 = time.time()
        prev_t, prev_yaw = None, None
        samples = []
        while time.time() - t0 < hold_s:
            now = time.time()
            ok2, n, e, alt, vn, ve, climb = pilot.nav()
            if trim is not None:
                gb.control.throttle = trim.update(alt, climb, 0.05) if ok2 else baseline_thr
            else:
                gb.control.throttle = baseline_thr
            gb.control.roll = bank_stick
            gb.control.pitch = 0.0
            gb.control.yaw = step_stick
            r, p, y = truth_rpy()
            yaw_rate = 0.0
            if prev_t is not None:
                ydt = max(now - prev_t, 0.01)
                yaw_rate = _heading_error(y, prev_yaw) / ydt
            prev_t, prev_yaw = now, y
            samples.append((now - t0, r, p, y, yaw_rate, alt))
            if not pilot.check_safety():
                ok = False
                break
            time.sleep(0.05)
        for st, r, p, y, yr, alt in samples:
            print("[wroom] yawauth t=%5.2f roll=%6.1f pitch=%6.1f yaw=%7.2f yaw_rate=%+6.2f/s alt=%5.2f"
                  % (st, r, p, y, yr, alt), flush=True)
        if samples:
            window_s = min(2.0, hold_s / 2.0)
            steady = [s for s in samples if s[0] > hold_s - window_s]  # past the spin-up transient
            if steady:
                mean_yaw_rate = sum(s[4] for s in steady) / len(steady)
                mean_roll = sum(abs(s[1]) for s in steady) / len(steady)
                mean_pitch = sum(abs(s[2]) for s in steady) / len(steady)
                alt_excursion = max(s[5] for s in samples) - min(s[5] for s in samples)
                print("[wroom] yawauth STEADY-STATE (last %.1fs): yaw_rate=%+6.2f deg/s  "
                      "|roll|=%5.2f deg  |pitch|=%5.2f deg  alt_excursion=%5.2fm"
                      % (window_s, mean_yaw_rate, mean_roll, mean_pitch, alt_excursion), flush=True)
        gb.control.yaw = 0.0
        gb.control.roll = 0.0
        if ok:
            ok = pilot.fly_until(4.0, staging_alt, tgt_n=None, tgt_e=None, label="recover")
    landed = pilot.descend_and_land() if ok else False
    verdict = ("PASS - logged hover yaw step response at stick=%.2f" % step_stick
               if (ok and landed) else "FAIL - %s" % (pilot.fail_reason or "did not complete"))
    _finish(pilot, verdict)


def speedcorridor_test():
    """Transition-corridor test on the SPEED axis (the open item next to the RATE sweep in
    INTERCEPTOR_FLIGHT_LOG.md sec 11): does ENGAGING or DISENGAGING interceptor mode while the vehicle is already
    carrying forward ground speed - not standing still at the moment of the switch - behave any differently than
    the from-a-clean-hover baseline transition_test always uses.

    NINJAPILOT_ENTRY_SPEED (m/s, default 0.0): ground speed built up in hover, via pilot.velocity()'s sign-safe
    earth-frame controller (not a hand-picked raw stick), BEFORE flipping to interceptor - models a pilot who
    flicks the switch mid-cruise-in-hover rather than from a dead stop.
    NINJAPILOT_DISENGAGE ("instant"|"brake", default "instant"): "instant" snaps straight back to Stabilized1 from
    full cruise speed with no deceleration phase - the harder, more realistic stick-flick case; "brake" adds a 3s
    nose-up bleed-off first, for comparison.
    """
    pilot = _start("wroom_speedcorridor")
    if pilot is None:
        return
    cruise_pitch = float(os.environ.get("NINJAPILOT_INTERCEPTOR_CRUISE_PITCH", "-45"))
    hover_thrust = float(os.environ.get("NINJAPILOT_INTERCEPTOR_HOVER_THRUST", "0.65"))
    cruise_thr = interceptor_level_thrust(hover_thrust, cruise_pitch)
    climb_s = float(os.environ.get("NINJAPILOT_INTERCEPTOR_CLIMB_TIME", "3.0"))
    rate = float(os.environ.get("NINJAPILOT_INTERCEPTOR_TRANSITION_RATE", "15"))
    entry_speed = float(os.environ.get("NINJAPILOT_ENTRY_SPEED", "0.0"))
    disengage = os.environ.get("NINJAPILOT_DISENGAGE", "instant")
    stats = {"pitch_min": 0.0, "alt_min": 99.0, "alt_max": -99.0, "vfwd_entry": 0.0, "vfwd_max": 0.0,
             "vfwd_disengage": 0.0, "cruise_pitch_ok": False, "recovered": False,
             "recover_pitch_max": 0.0, "recover_alt_excursion": 0.0}
    climb_trim = [None]

    def watch(label, seconds, sticks=(0.0, 0.0), thr=None, yaw=0.0, hold_altitude=False, track_recovery=False):
        pilot.phase = label
        t0 = time.time(); last_log = 0.0; last_t = t0; alt0 = None
        while time.time() - t0 < seconds:
            now = time.time()
            dt = max(1e-3, now - last_t)
            last_t = now
            ok, n, e, alt, vn, ve, climb = pilot.nav()
            if alt0 is None:
                alt0 = alt
            if hold_altitude:
                if climb_trim[0] is None:
                    seed = thr if thr is not None else gb.control.throttle
                    gb.control.throttle = seed
                    pilot.last_thr = seed
                    climb_trim[0] = ClimbTrim(seed, alt)
                else:
                    gb.control.throttle = climb_trim[0].update(alt, climb, dt)
                    pilot.last_thr = gb.control.throttle
            elif thr is not None:
                gb.control.throttle = thr
                pilot.last_thr = thr
            gb.control.roll, gb.control.pitch = sticks
            gb.control.yaw = yaw
            r, p, y = truth_rpy()
            _h, _tn, _te, talt = truth_ned()
            stats["pitch_min"] = min(stats["pitch_min"], p)
            stats["alt_min"] = min(stats["alt_min"], talt)
            stats["alt_max"] = max(stats["alt_max"], talt)
            vfwd = math.hypot(vn, ve)
            stats["vfwd_max"] = max(stats["vfwd_max"], vfwd)
            if track_recovery:
                stats["recover_pitch_max"] = max(stats["recover_pitch_max"], abs(p))
                stats["recover_alt_excursion"] = max(stats["recover_alt_excursion"], abs(talt - alt0))
            if label == "cruise" and abs(p - cruise_pitch) < 10.0:
                stats["cruise_pitch_ok"] = True
            if ok:
                pilot.rec.row(label, n, e, alt, vn, ve, climb)
            if time.time() - last_log > 0.5:
                last_log = time.time()
                print("[wroom] %-11s t=%5.1f alt=%5.2f pitch=%6.1f roll=%6.1f yaw=%6.1f vfwd=%5.2f thr=%.2f sticks=(%+.2f,%+.2f)"
                      % (label, time.time() - t0, talt, p, r, y, vfwd, gb.control.throttle, gb.control.roll, gb.control.pitch), flush=True)
            if talt > 80.0 or talt < 0.3:
                pilot.fail_reason = "%s: altitude %.1f out of bounds" % (label, talt)
                print("[wroom] FAIL: %s" % pilot.fail_reason, flush=True)
                return False
            time.sleep(0.05)
        return True

    # Staging at 4.0m, matching transition_test's own well-proven baseline, rather than the 30m used by
    # shape_test/rollstep_test - nothing about the speed-corridor question needs 30m of headroom. CEILING_M=60
    # matches transition_test's own (a healthy climb+transition+cruise from 4m genuinely reaches ~35m; see
    # INTERCEPTOR_FLIGHT_LOG.md section 14 - this test's early runs chased a phantom "30m staging is broken" theory
    # that was actually just a missing NINJAPILOT_MOTOR_BOOST=0.55).
    STAGING_ALT = 4.0
    pilot.CEILING_M = 60.0
    ok = pilot.takeoff(STAGING_ALT)
    if ok:
        ok = pilot.fly_until(4.0, STAGING_ALT, tgt_n=0.0, tgt_e=0.0, label="settle")
    hover_thr = gb.control.throttle
    if ok and entry_speed > 0.0:
        # Build the carried-in ground speed in HOVER (Stabilized1, velocity-hold via pilot.velocity()) BEFORE the
        # mode switch - the realistic case is a pilot flicking the switch while already moving, not from a dead
        # stop. Reuses the same sign-safe body/earth-frame controller poshold/rth already trust, rather than
        # guessing a raw pitch stick's sign for "forward" on this airframe.
        print("[wroom] >>> building entry speed to %.1f m/s in hover before the switch" % entry_speed, flush=True)
        # TILT_MAX=12deg (the class default, tuned for gentle poshold/rth station-keeping) saturates the velocity
        # controller's authority at only ~2 m/s of standing error (TILT_MAX/TILT_PER_MPS) - a real speedcorridor_test
        # limitation found 2026-09-19 (sc06: only reached 1.46 of a 3.0 m/s target in the old 12s window), not an
        # airframe limit. Widened here, for this build phase only, and restored immediately after.
        _saved_tilt_max = pilot.TILT_MAX
        pilot.TILT_MAX = max(pilot.TILT_MAX, entry_speed * pilot.TILT_PER_MPS * 1.2)
        t0 = time.time()
        while time.time() - t0 < 18.0:
            ok2, n, e, alt, vn, ve, climb = pilot.nav()
            if not ok2:
                ok = False
                break
            gb.control.throttle = pilot.vertical(STAGING_ALT, alt, climb, 0.05)
            gb.control.roll, gb.control.pitch = pilot.velocity(entry_speed, 0.0, vn, ve)
            if math.hypot(vn, ve) >= entry_speed * 0.9:
                break
            if not pilot.check_safety():
                ok = False
                break
            time.sleep(0.05)
        pilot.TILT_MAX = _saved_tilt_max
        _ok2, _n, _e, _alt, vn, ve, _climb = pilot.nav()
        stats["vfwd_entry"] = math.hypot(vn, ve)
        print("[wroom] entry speed at switch: %.2f m/s (target %.1f)" % (stats["vfwd_entry"], entry_speed), flush=True)
    if ok:
        pilot.tilt_check = False
        gb.control.mode_position = 2
        transition_s = abs(cruise_pitch) / max(rate, 1.0)
        print("[wroom] >>> switch to INTERCEPTOR carrying %.2f m/s: climb %.1fs, pitch to %.0f deg at %.0f deg/s"
              % (stats["vfwd_entry"], climb_s, cruise_pitch, rate), flush=True)
        ok = watch("interceptor_climb", climb_s, thr=hover_thr)
    if ok:
        ok = watch("transition", transition_s + 1.0, thr=hover_thr)
    if ok:
        ok = watch("cruise", 6.0, thr=cruise_thr, hold_altitude=True)
    if ok and disengage == "brake":
        print("[wroom] braking before disengage", flush=True)
        ok = watch("cruise_brake", 3.0, sticks=(0.0, 0.4), thr=cruise_thr, hold_altitude=True)
    if ok:
        _ok2, _n, _e, _alt, vn, ve, _climb = pilot.nav()
        stats["vfwd_disengage"] = math.hypot(vn, ve)
        print("[wroom] <<< switch back to Stabilized1 at %.2f m/s (%s disengage)"
              % (stats["vfwd_disengage"], disengage), flush=True)
        gb.control.mode_position = 0
        ok = watch("recover", 8.0, thr=hover_thr, track_recovery=True)
        _r, p, _y = truth_rpy()
        stats["recovered"] = abs(p) < 15.0
        pilot.tilt_check = True
    landed = False
    if ok:
        _h, _tn, _te, talt = truth_ned()
        ok = pilot.fly_until(10.0, max(4.0, min(talt, 12.0)), tgt_n=None, tgt_e=None, label="brake_final")
        landed = pilot.descend_and_land() if ok else False
    print("[wroom] speedcorridor stats: entry_v=%.2f disengage_v=%.2f vfwd_max=%.2f pitch_min=%.1f "
          "recover_pitch_max=%.1f recover_alt_excursion=%.2f recovered=%s"
          % (stats["vfwd_entry"], stats["vfwd_disengage"], stats["vfwd_max"], stats["pitch_min"],
             stats["recover_pitch_max"], stats["recover_alt_excursion"], stats["recovered"]), flush=True)
    verdict = ("PASS - engaged at %.1fm/s target, %s-disengaged at %.1fm/s, recovered and landed"
               % (entry_speed, disengage, stats["vfwd_disengage"])
               if (ok and landed and stats["cruise_pitch_ok"] and stats["recovered"])
               else "FAIL - %s" % (pilot.fail_reason or ("cruise_pitch_ok=%s recovered=%s landed=%s"
                                                          % (stats["cruise_pitch_ok"], stats["recovered"], landed))))
    _finish(pilot, verdict)


def reengage_test():
    """The genuinely-high-speed half of the transition-corridor question that `speedcorridor_test` couldn't reach:
    that test's hover-frame velocity-build helper tops out around 2.5 m/s (a controller tuned for gentle
    poshold/rth station-keeping, not high-speed dashes - see INTERCEPTOR_FLIGHT_LOG.md section 13 item 3). Real
    interceptor tactics also include a missed pass followed by an immediate re-attack, which is a cleaner, more
    realistic way to get genuine high entry speed anyway: fly a normal cruise leg (reaches 8-9 m/s on this
    airframe), disengage, then re-engage interceptor mode again almost immediately while most of that speed is
    still real, physical, carried momentum - not something built by fighting a weak hover controller.

    NINJAPILOT_REENGAGE_DELAY_S (default 0.0 - the hardest case: flip back to interceptor on literally the next
    tick after disengaging, mid-pitch-recovery, whatever attitude/speed that catches the vehicle at) controls how
    long Stabilized1 gets before the second engage.
    """
    pilot = _start("wroom_reengage")
    if pilot is None:
        return
    cruise_pitch = float(os.environ.get("NINJAPILOT_INTERCEPTOR_CRUISE_PITCH", "-45"))
    hover_thrust = float(os.environ.get("NINJAPILOT_INTERCEPTOR_HOVER_THRUST", "0.65"))
    cruise_thr = interceptor_level_thrust(hover_thrust, cruise_pitch)
    climb_s = float(os.environ.get("NINJAPILOT_INTERCEPTOR_CLIMB_TIME", "3.0"))
    rate = float(os.environ.get("NINJAPILOT_INTERCEPTOR_TRANSITION_RATE", "15"))
    reengage_delay = float(os.environ.get("NINJAPILOT_REENGAGE_DELAY_S", "0.0"))
    bank_stick = float(os.environ.get("NINJAPILOT_REENGAGE_BANK_STICK", "0.0"))
    STAGING_ALT = float(os.environ.get("NINJAPILOT_REENGAGE_STAGING_ALT", "4.0"))
    pilot.CEILING_M = max(70.0, STAGING_ALT + 60.0)
    stats = {"pitch_min": 0.0, "alt_min": 99.0, "alt_max": -99.0, "vfwd_max": 0.0,
             "vfwd_disengage1": 0.0, "vfwd_reengage": 0.0, "pitch_reengage": 0.0,
             "cruise2_pitch_ok": False, "recovered": False}
    climb_trim = [None]

    def watch(label, seconds, sticks=(0.0, 0.0), thr=None, hold_altitude=False, cruise_check=False):
        pilot.phase = label
        t0 = time.time(); last_log = 0.0; last_t = t0
        while time.time() - t0 < seconds:
            now = time.time()
            dt = max(1e-3, now - last_t)
            last_t = now
            ok, n, e, alt, vn, ve, climb = pilot.nav()
            if hold_altitude:
                if climb_trim[0] is None:
                    seed = thr if thr is not None else gb.control.throttle
                    gb.control.throttle = seed
                    pilot.last_thr = seed
                    climb_trim[0] = ClimbTrim(seed, alt)
                else:
                    gb.control.throttle = climb_trim[0].update(alt, climb, dt)
                    pilot.last_thr = gb.control.throttle
            elif thr is not None:
                gb.control.throttle = thr
                pilot.last_thr = thr
            gb.control.roll, gb.control.pitch = sticks
            r, p, y = truth_rpy()
            _h, _tn, _te, talt = truth_ned()
            stats["pitch_min"] = min(stats["pitch_min"], p)
            stats["alt_min"] = min(stats["alt_min"], talt)
            stats["alt_max"] = max(stats["alt_max"], talt)
            vfwd = math.hypot(vn, ve)
            stats["vfwd_max"] = max(stats["vfwd_max"], vfwd)
            if cruise_check and abs(p - cruise_pitch) < 10.0:
                stats["cruise2_pitch_ok"] = True
            if ok:
                pilot.rec.row(label, n, e, alt, vn, ve, climb)
            if time.time() - last_log > 0.5:
                last_log = time.time()
                print("[wroom] %-12s t=%5.1f alt=%5.2f pitch=%6.1f roll=%6.1f vfwd=%5.2f thr=%.2f"
                      % (label, time.time() - t0, talt, p, r, vfwd, gb.control.throttle), flush=True)
            if talt > 80.0 or talt < 0.3:
                pilot.fail_reason = "%s: altitude %.1f out of bounds" % (label, talt)
                print("[wroom] FAIL: %s" % pilot.fail_reason, flush=True)
                return False
            time.sleep(0.05)
        return True

    ok = pilot.takeoff(STAGING_ALT)
    if ok:
        ok = pilot.fly_until(4.0, STAGING_ALT, tgt_n=0.0, tgt_e=0.0, label="settle")
    hover_thr = gb.control.throttle
    transition_s = abs(cruise_pitch) / max(rate, 1.0)
    if ok:
        pilot.tilt_check = False
        gb.control.mode_position = 2
        print("[wroom] >>> FIRST engage: climb %.1fs, pitch to %.0f deg at %.0f deg/s" % (climb_s, cruise_pitch, rate), flush=True)
        ok = watch("climb1", climb_s, thr=hover_thr)
    if ok:
        ok = watch("transition1", transition_s + 1.0, thr=hover_thr)
    if ok:
        ok = watch("cruise1", 3.0, thr=cruise_thr, hold_altitude=True)
    if ok and bank_stick != 0.0:
        # Disengage/re-engage while actively banked/turning, not wings-level - a meaningfully harder, asymmetric
        # initial condition than every reengage_test run so far (rg01/rg02 both disengaged level, roll ~0).
        ok = watch("cruise1_bank", 2.0, sticks=(bank_stick, 0.0), thr=cruise_thr, hold_altitude=True)
    if ok:
        _ok2, _n, _e, _alt, vn, ve, _climb = pilot.nav()
        stats["vfwd_disengage1"] = math.hypot(vn, ve)
        print("[wroom] <<< disengage 1 at %.2f m/s, re-engaging after %.1fs" % (stats["vfwd_disengage1"], reengage_delay), flush=True)
        gb.control.mode_position = 0
        if reengage_delay > 0.0:
            ok = watch("gap", reengage_delay, thr=hover_thr)
    if ok:
        r, p, y = truth_rpy()
        _ok2, _n, _e, _alt, vn, ve, _climb = pilot.nav()
        stats["vfwd_reengage"] = math.hypot(vn, ve)
        stats["pitch_reengage"] = p
        print("[wroom] >>> RE-engage carrying %.2f m/s, pitch %.1f deg, roll %.1f deg"
              % (stats["vfwd_reengage"], p, r), flush=True)
        climb_trim[0] = None   # fresh capture for the second cruise hold
        gb.control.mode_position = 2
        ok = watch("climb2", climb_s, thr=hover_thr)
    if ok:
        ok = watch("transition2", transition_s + 1.0, thr=hover_thr)
    if ok:
        ok = watch("cruise2", 5.0, thr=cruise_thr, hold_altitude=True, cruise_check=True)
    if ok:
        gb.control.mode_position = 0
        pilot.tilt_check = True
        ok = watch("recover", 8.0, thr=hover_thr)
        _r, p, _y = truth_rpy()
        stats["recovered"] = abs(p) < 15.0
    landed = False
    if ok:
        _h, _tn, _te, talt = truth_ned()
        ok = pilot.fly_until(10.0, max(4.0, min(talt, 12.0)), tgt_n=None, tgt_e=None, label="brake_final")
        landed = pilot.descend_and_land() if ok else False
    print("[wroom] reengage stats: vfwd_disengage1=%.2f vfwd_reengage=%.2f pitch_reengage=%.1f vfwd_max=%.2f "
          "pitch_min=%.1f cruise2_pitch_ok=%s recovered=%s"
          % (stats["vfwd_disengage1"], stats["vfwd_reengage"], stats["pitch_reengage"], stats["vfwd_max"],
             stats["pitch_min"], stats["cruise2_pitch_ok"], stats["recovered"]), flush=True)
    verdict = ("PASS - re-engaged at %.1fm/s (delay=%.1fs), second transition/cruise/recovery clean"
               % (stats["vfwd_reengage"], reengage_delay)
               if (ok and landed and stats["cruise2_pitch_ok"] and stats["recovered"])
               else "FAIL - %s" % (pilot.fail_reason or ("cruise2_pitch_ok=%s recovered=%s landed=%s"
                                                          % (stats["cruise2_pitch_ok"], stats["recovered"], landed))))
    _finish(pilot, verdict)


def rattitude_test():
    """A/B: Attitude (switch position 0) vs Rattitude (position 5, carved out for this test only - no stock switch
    position ships Rattitude on Roll/Pitch, see gazebo_bridge.py's _fms_values comment) in HOVER, on this specific
    airframe's twitchy-yaw/slow-roll-pitch characteristics. Both trials hold the SAME roll stick for the SAME
    duration; Attitude caps at RollMax (42 deg, a bounded angle no matter how long the stick is held), Rattitude
    blends toward direct rate control above RattitudeModeTransition% stick (80% here) and keeps rotating for as
    long as the stick is held - the qualitative difference this test exists to show and measure directly, not just
    assert. NINJAPILOT_RATT_STICK (default 0.6, above 80% is where Rattitude's blend is dominated by rate) and
    NINJAPILOT_RATT_PULSE_S (default 1.0) control the pulse.
    """
    pilot = _start("wroom_rattitude")
    if pilot is None:
        return
    staging_alt = float(os.environ.get("NINJAPILOT_SHAPE_ALT", "10"))
    pilot.CEILING_M = staging_alt + 15.0
    stick = float(os.environ.get("NINJAPILOT_RATT_STICK", "0.6"))
    pulse_s = float(os.environ.get("NINJAPILOT_RATT_PULSE_S", "1.0"))
    ok = pilot.takeoff(staging_alt)
    results = {}
    trials = [("attitude", 0), ("rattitude", 5)]
    for label, mode_pos in trials:
        if not ok:
            break
        ok = pilot.fly_until(3.0, staging_alt, tgt_n=0.0, tgt_e=0.0, label="%s_settle" % label)
        if not ok:
            break
        baseline_thr = gb.control.throttle
        gb.control.mode_position = mode_pos
        # A committed pulse this large is exactly what Rattitude is FOR - disable the generic tilt-over safety trip
        # for the pulse itself (same pattern flip tests use), not because the vehicle is out of control, but because
        # exceeding TILT_OVER_DEG=65 is the expected, intended outcome for the Rattitude trial.
        pilot.tilt_check = False
        t0 = time.time()
        peak_roll = 0.0
        peak_rate = 0.0
        prev_t, prev_roll = None, None
        while time.time() - t0 < pulse_s:
            now = time.time()
            gb.control.throttle = baseline_thr
            gb.control.roll = stick
            gb.control.pitch = 0.0
            r, _p, _y = truth_rpy()
            peak_roll = max(peak_roll, abs(r))
            if prev_t is not None:
                peak_rate = max(peak_rate, abs((r - prev_roll) / max(now - prev_t, 1e-3)))
            prev_t, prev_roll = now, r
            if not pilot.check_safety():
                ok = False
                break
            time.sleep(0.02)
        gb.control.roll = 0.0
        results[label] = (peak_roll, peak_rate)
        print("[wroom] %-10s stick=%.2f for %.1fs -> peak roll %.1f deg, peak rate %.1f deg/s"
              % (label, stick, pulse_s, peak_roll, peak_rate), flush=True)
        gb.control.mode_position = 0
        # A pulse this large can leave roll well past TILT_OVER_DEG=65 the instant the stick releases (rattitude's
        # own peak was 87 deg) - re-enabling the safety check immediately trips it on the very first post-pulse
        # tick, failing a run that never actually lost control. Bleed roll back under a safe margin on neutral
        # stick, tilt_check still off, BEFORE handing off to the normal fly_until recovery (which re-enables it).
        if ok:
            t0 = time.time()
            while time.time() - t0 < 3.0:
                r, _p, _y = truth_rpy()
                if abs(r) < 30.0:
                    break
                gb.control.throttle = baseline_thr
                gb.control.roll = gb.control.pitch = 0.0
                time.sleep(0.02)
        pilot.tilt_check = True
        if ok:
            ok = pilot.fly_until(5.0, staging_alt, tgt_n=0.0, tgt_e=0.0, label="%s_recover" % label)
    landed = pilot.descend_and_land() if ok else False
    if "attitude" in results and "rattitude" in results:
        print("[wroom] rattitude_test: attitude capped at %.1f deg (%.1f deg/s); rattitude reached %.1f deg (%.1f deg/s) "
              "on the SAME %.2f stick for %.1fs" % (results["attitude"][0], results["attitude"][1],
                                                     results["rattitude"][0], results["rattitude"][1], stick, pulse_s),
              flush=True)
    verdict = ("PASS - compared attitude vs rattitude response to a %.2f-stick, %.1fs pulse" % (stick, pulse_s)
               if (ok and landed and len(results) == 2)
               else "FAIL - %s" % (pilot.fail_reason or "did not complete"))
    _finish(pilot, verdict)
