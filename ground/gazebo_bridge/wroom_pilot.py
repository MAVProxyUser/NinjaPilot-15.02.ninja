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
    THR_MIN, THR_MAX = 0.45, 0.80
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
        # target altitude 0.5m below ground: keeps a steady descent command on
        ok = self.fly_until(40.0, -0.5, tgt_n=tgt_n, tgt_e=tgt_e, done=touched)
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
