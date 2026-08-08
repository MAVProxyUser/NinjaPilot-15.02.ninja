#!/usr/bin/env python3
#
# gazebo_bridge.py - drives fw_simposix.elf's sensor inputs from a real
# Gazebo physics simulation instead of sensors.c's hand-rolled point-mass
# model, and drives Gazebo's motors from the flight code's real mixer
# output (ActuatorCommand). The flight code itself is unmodified - it only
# ever talks UAVTalk to whatever is publishing GyroSensor/AccelSensor/
# GPSPositionSensor/BaroSensor/MagSensor, exactly as it does with sensors.c.
#
# Requires: gz-harmonic (Gazebo Sim 8) with its Python bindings, running
# under the venv in this directory (see run_gazebo_bridge.sh). sensors.c's
# own internal physics must be disabled by setting
# NINJAPILOT_EXTERNAL_PHYSICS=1 before launching fw_simposix.elf, or this
# bridge and sensors.c will fight over the same UAVObjects every tick.
#
# Run:
#   ./run_gazebo_bridge.sh
#
import json
import math
import os
import sys
import time
import threading

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "pyuavtalk"))
import uavtalk
from uavtalk_client import UAVTalkClient, UdpTransport
# Reuse the already-verified flight-config values (QuadX mixer, RevoSettings
# mag fusion, etc.) instead of duplicating/re-deriving them here - pure
# Python, no version-specific syntax, safe to import under a different
# interpreter than the one board_orientation_viz.py itself normally runs
# under.
import board_orientation_viz as bov

# The [dbg]/[piddbg]/[posdbg]/[navsatdbg]/[barodbg]/[gyrodbg]/[sendtiming]/
# [latency] prints below fire at up to ~500Hz combined (every ActuatorCommand,
# every sensor sample) - terminal I/O at that rate measurably slows down the
# sender_loop, which is timing-sensitive (see CLAUDE.md's notes on gyro feed
# gaps from scheduling jitter). Off by default; set NINJAPILOT_VERBOSE=1 to
# get them back for an actual debugging session. [test]/crash/land messages
# are unaffected - those are low-frequency and always worth seeing.
VERBOSE = os.environ.get("NINJAPILOT_VERBOSE", "0") == "1"

import gz.transport13 as transport
from gz.msgs10.pose_v_pb2 import Pose_V
from gz.msgs10.actuators_pb2 import Actuators
from gz.msgs10.imu_pb2 import IMU
from gz.msgs10.navsat_pb2 import NavSat
from gz.msgs10.magnetometer_pb2 import Magnetometer
from gz.msgs10.fluid_pressure_pb2 import FluidPressure

GRAV = 9.81

# A real reference point instead of simposix's usual (0,0) "Null Island"
# default - this is what GPSPositionSensor/HomeLocation will report as
# "home". Change to wherever you want to pretend to be flying.
HOME_LATITUDE = 37.7749
HOME_LONGITUDE = -122.4194
HOME_ALTITUDE = 30.0

GAZEBO_WORLD = "quadcopter"
GAZEBO_MODEL = "x3"
POSE_TOPIC = "/world/%s/pose/info" % GAZEBO_WORLD
IMU_TOPIC = "/X3/imu"
NAVSAT_TOPIC = "/X3/navsat"
MAGNETOMETER_TOPIC = "/X3/magnetometer"
AIR_PRESSURE_TOPIC = "/X3/air_pressure"
MOTOR_TOPIC = "/X3/gazebo/command/motor_speed"
MOTOR_MAX_RAD_S = 800.0  # matches quadcopter.sdf's maxRotVelocity per rotor

UDP_HOST = "127.0.0.1"
UDP_PORT = 9000


# ---------------------------------------------------------------------------
# Quaternion helpers (w, x, y, z order throughout)
# ---------------------------------------------------------------------------

def q_mul(a, b):
    aw, ax, ay, az = a
    bw, bx, by, bz = b
    return (
        aw * bw - ax * bx - ay * by - az * bz,
        aw * bx + ax * bw + ay * bz - az * by,
        aw * by - ax * bz + ay * bw + az * bx,
        aw * bz + ax * by - ay * bx + az * bw,
    )


def q_conj(q):
    w, x, y, z = q
    return (w, -x, -y, -z)


def q_normalize(q):
    w, x, y, z = q
    n = math.sqrt(w * w + x * x + y * y + z * z)
    if n < 1e-9:
        return (1.0, 0.0, 0.0, 0.0)
    return (w / n, x / n, y / n, z / n)


def q_rotate(q, v):
    """Rotate vector v (body->world if q is body-to-world) by quaternion q."""
    vq = (0.0, v[0], v[1], v[2])
    rw, rx, ry, rz = q_mul(q_mul(q, vq), q_conj(q))
    return (rx, ry, rz)


# Fixed frame-change quaternions (see the derivation in the commit message /
# session notes: both are 180 degree rotations, so each is its own inverse).
# ENU world -> NED world (swap X/Y, negate Z): 180 deg about (1,1,0)/sqrt(2).
Q_ENU2NED = (0.0, 0.70710678, 0.70710678, 0.0)
# FLU body -> FRD body (X unchanged, negate Y/Z): 180 deg about X.
Q_FLU2FRD = (0.0, 1.0, 0.0, 0.0)


def gazebo_to_ned_quat(q_gazebo):
    """q_gazebo: (w,x,y,z) FLU-body-to-ENU-world, as published by Gazebo.
    Returns (w,x,y,z) FRD-body-to-NED-world, as the flight code expects."""
    return q_normalize(q_mul(q_mul(Q_ENU2NED, q_gazebo), Q_FLU2FRD))


def gazebo_pos_to_ned(p):
    """Gazebo ENU (x=E, y=N, z=U) meters -> NED (x=N, y=E, z=D) meters."""
    return (p[1], p[0], -p[2])


# ---------------------------------------------------------------------------
# Shared state, updated by the Gazebo pose callback, read by the UAVTalk loop
# ---------------------------------------------------------------------------

class VehicleState(object):
    """Every sensor value here comes from a real Gazebo sensor plugin - no
    hand-computed/derived fallback for any of them:

    - Position/orientation: pose topic (ground truth).
    - Gyro AND accel: gz-sim-imu-system (model.sdf). An earlier revision
      replaced accel with a gravity-only projection computed from pose
      orientation, after finding Gazebo's own linear_acceleration ~10x too
      small on the Y axis during a confirmed 20deg roll - but that
      approximation had a worse, unintended side effect: it fed
      filteraltitude.c's velocity integrator zero real dynamic
      acceleration, starving VelocityState.Down and causing the
      PositionHold altitude overshoot investigated at length this session.
      Reverted to real IMU accel once the actual root causes (mag fusion,
      PIDControlDown::Activate(), outerloop.c's array-bounds/thrust-discard
      bugs, altitudeloop.c's unbounded PID output) were found and fixed -
      the original Y-axis concern did not reproduce afterward.
    - Mag: gz-sim-magnetometer-system (model.sdf/world SDF). HomeLocation.Be
      is measured from this same sensor at spawn (see send_config()) rather
      than assumed, so filtermag.c's validity check always compares against
      what Gazebo is actually reporting.
    - Baro: gz-sim-air-pressure-system (model.sdf), converted via the
      standard ISA barometric formula (on_air_pressure()).
    - GPS lat/lon/altitude and velocity: gz-sim-navsat-system (model.sdf/
      quadcopter_ninjapilot.sdf) - a real sensor reading has none of the
      lag a position-derivative would introduce, which matters directly
      for PositionHold's velocity-error feedback loop.

    publish_baro()/publish_mag()/publish_gps_velocity()/publish_gps_position()
    each skip sending until their real sensor has reported at least once,
    rather than ever synthesizing a placeholder value."""

    def __init__(self):
        self.lock = threading.Lock()
        self.have_pose = False
        self.have_imu = False
        self.have_navsat = False
        self.pos_ned = (0.0, 0.0, 0.0)
        self.quat_ned = (1.0, 0.0, 0.0, 0.0)
        self.accel_body = (0.0, 0.0, -GRAV)
        self.gyro_body_dps = (0.0, 0.0, 0.0)
        self.gps_lat = HOME_LATITUDE
        self.gps_lon = HOME_LONGITUDE
        self.gps_alt = HOME_ALTITUDE
        self.gps_vel_ned = (0.0, 0.0, 0.0)
        self.have_mag = False
        self.mag_body = (400.0, 0.0, 0.0)
        self.have_baro = False
        self.baro_alt = HOME_ALTITUDE

    def update_from_pose(self, t, pos_ned, quat_ned):
        with self.lock:
            self.pos_ned = pos_ned
            self.quat_ned = quat_ned
            self.have_pose = True

    def update_from_imu(self, gyro_body_dps, accel_body):
        with self.lock:
            self.gyro_body_dps = gyro_body_dps
            self.accel_body = accel_body
            self.have_imu = True

    def update_from_navsat(self, lat, lon, alt, vel_ned):
        with self.lock:
            self.gps_lat = lat
            self.gps_lon = lon
            self.gps_alt = alt
            self.gps_vel_ned = vel_ned
            self.have_navsat = True

    def update_from_mag(self, mag_body):
        with self.lock:
            self.mag_body = mag_body
            self.have_mag = True

    def update_from_baro(self, baro_alt):
        with self.lock:
            self.baro_alt = baro_alt
            self.have_baro = True

    def snapshot(self):
        with self.lock:
            return (self.have_pose and self.have_imu, self.pos_ned, self.quat_ned,
                    self.gps_vel_ned, self.accel_body, self.gyro_body_dps)

    def gps_snapshot(self):
        with self.lock:
            return (self.have_navsat, self.gps_lat, self.gps_lon, self.gps_alt, self.gps_vel_ned)

    def mag_snapshot(self):
        with self.lock:
            return (self.have_mag, self.mag_body)

    def baro_snapshot(self):
        with self.lock:
            return (self.have_baro, self.baro_alt)


state = VehicleState()
sim_start_wall = time.time()


def on_pose(msg):
    for pose in msg.pose:
        if pose.name != GAZEBO_MODEL:
            continue
        t = msg.header.stamp.sec + msg.header.stamp.nsec / 1e9
        p = (pose.position.x, pose.position.y, pose.position.z)
        q = (pose.orientation.w, pose.orientation.x, pose.orientation.y, pose.orientation.z)
        pos_ned = gazebo_pos_to_ned(p)
        quat_ned = gazebo_to_ned_quat(q)
        state.update_from_pose(t, pos_ned, quat_ned)


def on_imu(msg):
    # Gazebo's IMU reports in the link's own FLU body frame - rotate into
    # FRD to match the flight code's convention (same fixed transform used
    # for the world/body frame change elsewhere in this file). gyro
    # (angular_velocity) was independently confirmed correct by direct
    # comparison against ground-truth pose rotation.
    #
    # linear_acceleration was previously replaced with a gravity-only
    # projection computed from pose orientation, because Gazebo's own IMU
    # accel was found ~10x too small on the Y axis during a confirmed 20deg
    # roll. That fix had an unintended side effect: filteraltitude.c (the
    # active altitude filter for Basic-Complementary fusion) integrates
    # VelocityState.Down mostly from accel (the baro correction term is
    # BaroKp^2-scaled, i.e. deliberately weak) - a gravity-only accel
    # reading has zero real thrust-induced dynamics, so VelocityState.Down
    # stayed near-zero regardless of how fast the vehicle actually climbed
    # (measured ~8x mismatch against PositionState.Down's real rate of
    # change), starving PIDControlDown's velocity feedback and producing
    # the PositionHold altitude overshoot. Reverting to Gazebo's real
    # linear_acceleration to restore real vertical dynamics - re-test
    # whether the original Y-axis roll issue still reproduces now that
    # mag fusion and PIDControlDown::Activate() are both independently
    # fixed (gyro already dominates short-term attitude per filtercf.c's
    # own design, so a slightly-imperfect accel Y-component may no longer
    # be able to reproduce the old tumble).
    w_flu = (msg.angular_velocity.x, msg.angular_velocity.y, msg.angular_velocity.z)
    w_frd = q_rotate(Q_FLU2FRD, w_flu)
    gyro_dps = tuple(math.degrees(w) for w in w_frd)
    a_flu = (msg.linear_acceleration.x, msg.linear_acceleration.y, msg.linear_acceleration.z)
    a_frd = q_rotate(Q_FLU2FRD, a_flu)
    state.update_from_imu(gyro_dps, a_frd)


_last_navsat_dbg = [0.0]
_navsat_count = [0]


def on_navsat(msg):
    # navsat_pb2.NavSat: latitude_deg/longitude_deg/altitude directly, plus
    # velocity_east/velocity_north/velocity_up in the local ENU tangent
    # frame - convert straight to NED, no differentiation needed.
    vel_ned = (msg.velocity_north, msg.velocity_east, -msg.velocity_up)
    state.update_from_navsat(msg.latitude_deg, msg.longitude_deg, msg.altitude, vel_ned)
    _navsat_count[0] += 1
    now = time.time()
    if now - _last_navsat_dbg[0] > 1.0:
        if VERBOSE:
            rate = _navsat_count[0] / (now - _last_navsat_dbg[0]) if _last_navsat_dbg[0] else 0.0
            print(f"[navsatdbg] t={now:.2f} rate={rate:.1f}Hz lat={msg.latitude_deg:.7f} lon={msg.longitude_deg:.7f} alt={msg.altitude:.3f}", flush=True)
        _last_navsat_dbg[0] = now
        _navsat_count[0] = 0


MAG_SCALE = 1e5  # arbitrary but fixed - see comment below


def on_mag(msg):
    # gz.msgs.Magnetometer.field_tesla is body-frame (FLU, same convention
    # as the IMU) - rotate to FRD the same way on_imu() does. Using
    # Gazebo's own magnetometer plugin (real sensor, driven directly by the
    # vehicle's authoritative orientation) instead of a Python-side
    # q_conj(quat_ned) rotation of HomeLocation.Be eliminates any
    # quaternion-convention mismatch between this bridge and
    # filtercf.c's own Quaternion2R-based rotation of the same reference
    # vector - that mismatch was slowly driving mag_err/gyroBias[2] and
    # injecting a spurious, growing yaw torque (see CLAUDE.md/session
    # notes). This build's magnetometer-system plugin does NOT report the
    # magnitude a real Earth field in Tesla would have for this world's
    # <spherical_coordinates> location (measured ~0.487, not ~4.8e-5) -
    # this world's own <magnetic_field> override apparently isn't what's
    # actually driving it (likely an internal WMM-derived value instead).
    # Rather than guess at a Tesla/Gauss/nT conversion, send_config() reads
    # state.mag_snapshot() (this same field_frd, via update_from_mag())
    # once at startup - right after the vehicle spawns level, so body-frame
    # FRD == world-frame NED at that instant - and sends it AS
    # HomeLocation.Be directly, instead of a separately-assumed constant.
    # That keeps filtermag.c's checkMagValidity() (magnitude AND direction)
    # always comparing against whatever Gazebo is really reporting.
    # MAG_SCALE is just for readable magnitudes (both sides use it
    # identically, so it's otherwise arbitrary).
    field_flu = tuple(v * MAG_SCALE for v in (msg.field_tesla.x, msg.field_tesla.y, msg.field_tesla.z))
    field_frd = q_rotate(Q_FLU2FRD, field_flu)
    state.update_from_mag(field_frd)


def on_air_pressure(msg):
    # gz.msgs.FluidPressure.pressure is in Pascals: the air_pressure
    # sensor's own <reference_altitude> (30.0, matching HOME_ALTITUDE - see
    # model.sdf) is already baked in, so the standard ISA barometric
    # formula on this reading directly gives true MSL altitude, matching
    # what BaroSensor.Altitude expects (same convention the old
    # meters_to_latlon()-based computation used).
    altitude = 44330.0 * (1.0 - (msg.pressure / 101325.0) ** (1.0 / 5.255))
    state.update_from_baro(altitude)
    now = time.time()
    if now - _last_baro_dbg[0] > 0.5:
        if VERBOSE:
            print(f"[barodbg] t={now:.2f} pressure_pa={msg.pressure:.2f} altitude={altitude:.4f}", flush=True)
        _last_baro_dbg[0] = now


_last_baro_dbg = [0.0]



def quat_to_euler_deg(q):
    w, x, y, z = q
    roll = math.degrees(math.atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y)))
    sinp = 2 * (w * y - z * x)
    sinp = max(-1.0, min(1.0, sinp))
    pitch = math.degrees(math.asin(sinp))
    yaw = math.degrees(math.atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z)))
    return roll, pitch, yaw


# ---------------------------------------------------------------------------
# Autonomous test sequence: arm -> ramp throttle -> hover -> PositionHold.
# ---------------------------------------------------------------------------

class ControlState(object):
    def __init__(self):
        self.armed = False
        self.throttle = 0.0
        self.mode_position = 0  # Stabilized1

    def gcs_channels(self):
        throttle_us = int(round(1000 + self.throttle * 1000))
        return [
            throttle_us,
            1500, 1500, 1500,                      # Roll/Pitch/Yaw sticks - neutral
            bov.flight_mode_channel(self.mode_position),
            1500, 1500, 1500,                      # unused disturbance channels
        ]


control = ControlState()


class FCState(object):
    """The flight controller's OWN telemetry (AttitudeState/AccelState) -
    distinct from `state` (VehicleState), which holds Gazebo ground truth.
    Used for crash detection: a real crash shows up in the FC's own estimate
    as a non-level attitude and/or an accel impact spike. A purely
    velocity-based "settled" check (abs(vel_ned[2]) < threshold) can't tell a
    stable hover apart from a crashed, motionless vehicle - both read as
    near-zero velocity - so this checks what the real hardware would actually
    see instead."""

    def __init__(self):
        self.lock = threading.Lock()
        self.have_attitude = False
        self.roll = 0.0
        self.pitch = 0.0
        self.yaw = 0.0
        self.have_accel = False
        self.accel_xyz = (0.0, 0.0, -GRAV)

    def update_attitude(self, roll, pitch, yaw):
        with self.lock:
            self.roll = roll
            self.pitch = pitch
            self.yaw = yaw
            self.have_attitude = True

    def update_accel(self, xyz):
        with self.lock:
            self.accel_xyz = xyz
            self.have_accel = True

    def snapshot(self):
        with self.lock:
            return (self.have_attitude, self.roll, self.pitch, self.have_accel, self.accel_xyz)


fc_state = FCState()

# Order matches systemalarms.xml's <elementnames> exactly - shared by
# on_object()'s SystemAlarms handler and status_writer_loop() below so the
# health_widget.py's alarm indices always line up with the real field names.
ALARM_NAMES = ["SystemConfiguration", "BootFault", "OutOfMemory", "StackOverflow",
               "CPUOverload", "EventSystem", "Telemetry", "Receiver", "ManualControl",
               "Actuator", "Attitude", "Sensors", "Magnetometer", "Airspeed",
               "Stabilization", "Guidance", "PathPlan", "Battery", "FlightTime",
               "I2C", "GPS"]

# Sustained tilt beyond this, ON THE GROUND, is a crash - a tumble or a
# tip-over, not a landed-and-resting vehicle. Airborne, this same tilt is
# just an attitude upset: Attitude mode's own Roll/Pitch stabilization is
# already actively fighting to level it out (same as it would for any
# other disturbance), same as a real aircraft recovering from a hard gust
# - it is NOT a crash yet, and treating it as one while still up in the
# air was the actual bug: it made check_crash() itself the thing dropping
# the vehicle (an instant motor cut mid-air is a freefall, not a rescue).
CRASH_TILT_DEG = 60.0
# Ground impact produces a brief accel magnitude spike well above steady 1G
# hover; 3G is comfortably above normal maneuvering thrust changes.
CRASH_ACCEL_G = 3.0
# Real (Gazebo ground-truth) height below which the vehicle counts as "on
# the ground" for crash-gating purposes. Deliberately NOT the flight
# controller's own PositionState.Down estimate - that's the value with the
# confirmed divergence bug (see filteraltitude.c investigation), so using
# it here would let a bad estimate either mask a real crash or manufacture
# a fake one.
CRASH_HEIGHT_M = 0.5
# This test profile only ever intentionally targets 10ft (~3.05m, see
# FEET_TO_M/climb_to() calls in run_test_sequence). Confirmed via a real
# incident: PositionHold drove the vehicle to a genuine, ground-truth
# 116m before losing control and crashing - this happened because nothing
# was watching real altitude at all while airborne, only the on-the-ground
# crash gate above. That's a different failure class from a tip-over: a
# runaway climb, most likely the same PositionState.Down divergence bug
# (filteraltitude.c) investigated elsewhere in this session, just swinging
# the other direction than the "phantom underground" version seen before.
# Comfortable margin above the highest intentional test target.
RUNAWAY_ALTITUDE_M = 8.0


def check_crash():
    """Returns (tripped, reason) for either of two distinct safety
    conditions - a real crash (on the ground, tipped over or an impact
    spike, judged from the flight controller's OWN AttitudeState/AccelState
    rather than tilt/accel alone regardless of altitude, which flagged
    ordinary in-air upsets as "crashes"), or a runaway climb (real
    ground-truth altitude past RUNAWAY_ALTITUDE_M, which nothing else in
    this test harness was watching for before the 116m incident this was
    added after). Both call emergency_land() the same way - see its own
    docstring for why a runaway needs the same real-height-checked descent
    a genuine crash does, not a blind cut."""
    have_pose, pos_ned, _, _, _, _ = state.snapshot()
    alt = -pos_ned[2] if have_pose else 999.0
    if alt > RUNAWAY_ALTITUDE_M:
        return True, f"runaway altitude {alt:.1f}m exceeds {RUNAWAY_ALTITUDE_M:.0f}m ceiling"
    if alt > CRASH_HEIGHT_M:
        return False, ""
    have_att, roll, pitch, have_acc, accel_xyz = fc_state.snapshot()
    if have_att and (abs(roll) > CRASH_TILT_DEG or abs(pitch) > CRASH_TILT_DEG):
        return True, f"on ground (alt={alt:.2f}m) tilted roll={roll:.1f} pitch={pitch:.1f}"
    if have_acc:
        mag_g = math.sqrt(sum(v * v for v in accel_xyz)) / GRAV
        if mag_g > CRASH_ACCEL_G:
            return True, f"on ground (alt={alt:.2f}m) impact spike |a|={mag_g:.1f}G"
    return False, ""


def _controlled_descent():
    """Shared by land() and emergency_land(): switch to manual-throttle
    Attitude mode (lets stabilization keep leveling while we drive thrust
    directly), hold near hover thrust briefly, then ease throttle down
    watching REAL measured height (not the flight controller's own
    estimate - see the PositionState divergence bug this was built
    alongside) until it's actually on the ground, then disarm. An earlier
    version just did control.armed = False with no height check at all -
    an instant, total motor cut is a dead-stick freefall at any real
    altitude, which is exactly what a human pilot would never do.

    A LATER version of this fixed that but capped the descent loop at a
    flat 15s regardless of actual height - harmless for a normal test
    landing from a few meters, but confirmed by a real incident to be the
    same bug wearing a disguise: PositionHold drove the vehicle to a
    genuine 116m before crashing, and a real recovery from that height
    could never have finished descending in 15s - the loop would have run
    out of iterations and cut power anyway, just 15s later than an instant
    cut instead of never. The time budget below scales with how far there
    actually is to descend instead of assuming it's always a few meters."""
    control.mode_position = 0  # Stabilization1Settings = Attitude/Attitude/AxisLock/Manual
    hover_thrust = 0.68
    control.throttle = hover_thrust
    time.sleep(0.5)  # let Attitude mode's leveling actually start working before touching thrust

    have_pose, pos_ned, _, _, _, _ = state.snapshot()
    start_alt = -pos_ned[2] if have_pose else 0.0
    # Budget for a slow ~0.3 m/s minimum descent rate plus a flat margin,
    # not a fixed cap - see this function's own docstring for why a fixed
    # cap is the exact bug being avoided here.
    max_time = max(15.0, start_alt / 0.3 + 10.0)
    deadline = time.time() + max_time

    while time.time() < deadline:
        have_pose, pos_ned, _, vel_ned, _, _ = state.snapshot()
        alt = -pos_ned[2] if have_pose else 0.0
        if alt <= 0.15:
            break
        # Proportional ease-down: a touch below hover, more aggressive the
        # higher it still is, gentler as it nears the ground - not a fixed
        # ramp that doesn't know or care how high it actually is.
        control.throttle = max(0.3, hover_thrust - 0.03 - 0.02 * min(alt, 10.0))
        time.sleep(0.1)
    else:
        have_pose, pos_ned, _, _, _, _ = state.snapshot()
        alt = -pos_ned[2] if have_pose else 0.0
        print(f"[test] WARNING: controlled descent timed out after {max_time:.0f}s, "
              f"still at alt={alt:.2f}m - cutting throttle anyway")

    control.throttle = 0.0
    time.sleep(0.5)
    control.armed = False


def land():
    """Planned, normal end-of-test landing - not a crash response. Called
    once the scripted test sequence is done rather than leaving the
    vehicle armed in an autonomous hold mode with nobody supervising it,
    which given the PositionState divergence bug could wander or descend
    unpredictably with no one watching."""
    print("[test] landing (controlled descent, watching real height)...")
    _controlled_descent()
    print("[test] landed, disarmed on the ground.")


def emergency_land(reason):
    """Called the instant check_crash() trips one of its two conditions:
    already on the ground in a bad state (tipped over or an impact spike -
    an in-air tilt/upset alone is NOT a crash, Attitude mode's own
    stabilization is already fighting to recover it same as for any other
    disturbance), or a runaway climb past RUNAWAY_ALTITUDE_M (added after
    a real 116m flyaway - see that constant's own comment). The first case
    is already at/near the ground by the time this runs, so a gentle,
    height-checked landing is mostly just a formality; the second case is
    NOT near the ground at all, which is exactly why _controlled_descent()
    scales its time budget to actual height instead of assuming a fixed
    cap is enough."""
    print(f"[test] CRASH DETECTED: {reason} - cushioning final descent + disarming")
    _controlled_descent()
    print("[test] recovery/descent finished, disarmed on the ground.")


# health_widget.py polls this file rather than sharing a UAVTalk connection -
# fw_simposix's posix telemetry link is a single UDP peer, so a second
# independent client can't just attach alongside gazebo_bridge.py without
# fighting it for the same socket. Writing a small JSON snapshot here (this
# process already has every value the widget needs, via fc_state/_last_alarms/
# control) and having the widget be a totally separate process/mainloop is
# simpler and avoids a real constraint besides: Tkinter's mainloop has to
# run on the main thread on macOS, which this process's main thread is
# already committed to the UAVTalk client loop.
STATUS_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), ".fc_status.json")


def status_writer_loop():
    while True:
        have_att, roll, pitch, have_acc, accel_xyz = fc_state.snapshot()
        crashed, crash_reason = check_crash()
        alarms = _last_alarms[0]
        status = {
            "t": time.time(),
            "armed": control.armed,
            "mode_position": control.mode_position,
            "have_attitude": have_att,
            "roll": roll,
            "pitch": pitch,
            "yaw": fc_state.yaw,
            "alarm_names": ALARM_NAMES,
            "alarms": alarms,
            "crashed": crashed,
            "crash_reason": crash_reason,
        }
        try:
            tmp = STATUS_FILE + ".tmp"
            with open(tmp, "w") as f:
                json.dump(status, f)
            os.replace(tmp, STATUS_FILE)
        except OSError:
            pass
        # Was 0.1s - suspiciously exactly PIOS_GCSRCVR_TIMEOUT_MS (100ms,
        # pios_board.h). Confirmed real: a ~12s stretch where the flight
        # controller saw ManualControlCommand.Throttle=-1.0 (PIOS_RCVR_TIMEOUT
        # exactly - pios_rcvr.h) despite the bridge continuously commanding
        # real throttle, meaning PIOS_gcsrcvr_Supervisor() (pios_gcsrcvr.c)
        # kept deciding no fresh GCSReceiver update had arrived within its
        # own 100ms window. This thread's own blocking file I/O (json.dump +
        # os.replace) on the exact same 100ms cadence is a real candidate for
        # GIL-contending the sender_loop thread out of that window often
        # enough to matter - slowing it well clear of 100ms to test.
        time.sleep(0.5)


def wait_with_crash_check(duration, label):
    """Poll in 0.1s steps for `duration` seconds, calling emergency_land()
    (recover + controlled descent, not an instant motor cut) the instant
    check_crash() trips. Returns True if the full duration elapsed
    normally, False if a crash cut it short - callers should stop the test
    sequence rather than pushing further mode switches once emergency_land
    has already taken over control."""
    steps = max(1, int(duration / 0.1))
    for _ in range(steps):
        crashed, reason = check_crash()
        if crashed:
            emergency_land(f"during '{label}': {reason}")
            return False
        time.sleep(0.1)
    return True


FEET_TO_M = 0.3048
HOVER_THRUST = 0.68  # X3 hover point - see run_test_sequence's own comment on the 14.9N/21.9N math


def climb_to(target_alt_m, max_time=20.0):
    """Manual-throttle climb (mode_position must already be a Thrust=Manual
    mode - Stabilization1Settings, the default) to target_alt_m of REAL
    (ground-truth) altitude, actively braking (not just coasting at hover
    thrust) as it nears the target so it doesn't overshoot under momentum.

    An earlier version eased straight to HOVER_THRUST (zero net
    acceleration - NOT deceleration) the instant it reached target
    altitude, then just handed off to hold_at()'s settle-wait. That
    doesn't stop a climb already in progress: real climb momentum built up
    under the aggressive ramp-up throttle just carries the vehicle upward
    in a straight line afterward (Newton's first law - hover thrust holds
    velocity constant, it doesn't arrest it), and it can coast for meters
    past the target before hold_at()'s settle-wait ever gets a chance to
    matter. Confirmed directly: real GPS-confirmed altitude kept climbing
    well past target while control.mode_position was STILL 0 (Manual),
    before any hold mode had even engaged - which ruled out every
    altitude-hold/state-estimator theory this investigation had chased up
    to that point. Now brakes below hover thrust once real
    vertical velocity indicates it's approaching the target, then holds
    that brake until velocity is actually near zero, not just "target
    altitude reached, hope it stops in time."
    Returns True on success, False if a crash was handled mid-climb (caller
    should stop the sequence)."""
    start_time = time.time()
    control.throttle = HOVER_THRUST
    braking = False
    while time.time() - start_time < max_time:
        have_pose, pos_ned, _, vel_ned, _, _ = state.snapshot()
        alt = -pos_ned[2] if have_pose else 0.0
        climb_rate = -vel_ned[2] if have_pose else 0.0  # positive = climbing
        crashed, reason = check_crash()
        if crashed:
            emergency_land(f"climbing to {target_alt_m:.2f}m: {reason}")
            return False

        # Predictive: start braking once current altitude + a stopping-
        # distance margin (proportional to climb rate) would carry it past
        # target, not only once it's already there.
        stopping_margin = max(0.0, climb_rate) * 0.5
        if not braking and alt + stopping_margin >= target_alt_m:
            braking = True

        if braking:
            if alt >= target_alt_m and climb_rate < 0.15:
                break
            # Below hover thrust - actual deceleration, not just "stop
            # adding more climb throttle." A bit harder the faster it's
            # still climbing.
            control.throttle = max(0.55, HOVER_THRUST - 0.05 - 0.01 * max(0.0, climb_rate))
        else:
            # A bit more aggressive the further below target, easing off
            # near it - not the fixed-ramp-then-hope-it's-airborne approach
            # the original single-stage liftoff used, since this needs to
            # reliably reach two different specific heights, not just
            # clear the ground.
            control.throttle = min(0.72, HOVER_THRUST + 0.04 + 0.02 * max(0.0, target_alt_m - alt))
        if VERBOSE:
            print(f"[climbdbg] alt={alt:.3f} climb_rate={climb_rate:.3f} braking={braking} throttle={control.throttle:.3f}", flush=True)
        time.sleep(0.1)

    ease_steps = 20
    start_throttle = control.throttle
    for i in range(ease_steps):
        control.throttle = start_throttle + (HOVER_THRUST - start_throttle) * (i + 1) / ease_steps
        time.sleep(0.1)
    return True


def hold_at(mode_position, mode_label, hold_seconds):
    """Wait for vertical velocity to settle BEFORE engaging a hold mode,
    then hold it. Engaging with real residual velocity still present means
    stabilizationAltitudeHold()'s reinit captures a real target position
    but zeros the PIDs (pid_zero(&pid0); pid_zero(&pid1)) with no bumpless
    transfer for velocity at all - the vehicle keeps climbing under its own
    real momentum while the freshly-zeroed PID has no idea, exactly the
    "~150m+ climb-and-crash overshoot" class of bug already flagged for
    PIDControlDown::Activate() elsewhere in this file. An earlier version
    of this function switched modes FIRST and waited after - which this
    docstring already claimed not to do - so every hold_at() call this
    whole staged-altitude test made was hitting exactly that bug. Returns
    True if the hold completed normally, False if a crash was handled
    (caller should stop the sequence)."""
    print(f"[test] waiting for vertical velocity to settle before {mode_label}...")
    settled = False
    for _ in range(70):  # up to 7s
        _, _, _, vel_ned, _, _ = state.snapshot()
        if abs(vel_ned[2]) < 0.3:
            settled = True
            break
        crashed, reason = check_crash()
        if crashed:
            emergency_land(f"waiting to settle before {mode_label}: {reason}")
            return False
        time.sleep(0.1)
    print(f"[test] vertical velocity wait ended: settled={settled} vel_down={vel_ned[2]:.3f}")

    print(f"[test] switching to {mode_label}")
    control.mode_position = mode_position
    return wait_with_crash_check(hold_seconds, f"{mode_label} hold")


def run_test_sequence():
    """Simple scripted acceptance test: arm, ramp to a hover throttle, hold,
    then hand off to PositionHold (Alt via CruiseControl + GPS position)."""
    print("[test] waiting 3s for link + config to settle...")
    time.sleep(3.0)

    print("[test] arming (throttle must be at idle for the arm gesture)")
    control.throttle = 0.0
    control.armed = True
    time.sleep(2.0)

    # Staged altitude profile: climb to 5ft and hold, then step up to 10ft
    # and hold, rather than the old single arbitrary-height liftoff (just
    # "clear the ground by 0.15m") going straight into whatever hold mode
    # was under test. Gives real step-response data at two known heights
    # instead of one incidental one, and matches what a real bench test of
    # an alt-hold controller would actually do. Uses Stabilized2 (pure baro
    # altitude hold, no PathFollower - see its own comment below) as the
    # hold mode for both stages, since it's the simpler, more fundamental
    # thing to verify before layering GPS/PathFollower on top in the
    # PositionHold/2D-hold stages that follow.
    #
    # Testing PURE baro altitude hold in isolation first, per the actual
    # architecture: PositionHold (flight mode index 3) routes through
    # PathFollower/VtolFlyController for BOTH horizontal AND vertical
    # (CruiseControl-based thrust) - but flight/modules/Stabilization/
    # altitudeloop.c provides a real, separate, fast-loop-native altitude
    # hold (STABILIZATIONDESIRED_STABILIZATIONMODE_ALTITUDEHOLD) that has
    # nothing to do with PathFollower at all. "Stabilized2" (index 1, see
    # board_orientation_viz.py's Stabilization2Settings) is repurposed to
    # Roll/Pitch=Attitude (leveling) + Thrust=AltitudeHold.
    print("[test] climbing to 5ft...")
    if not climb_to(5 * FEET_TO_M):
        return
    if not hold_at(1, "5ft hold (Stabilized2, baro altitude, no PathFollower)", 10.0):
        return

    print("[test] climbing to 10ft...")
    control.mode_position = 0  # back to Stabilization1Settings (Thrust=Manual) to climb further
    if not climb_to(10 * FEET_TO_M):
        return
    if not hold_at(1, "10ft hold (Stabilized2, baro altitude, no PathFollower)", 10.0):
        return

    # PIDControlDown::Activate() (pidcontroldown.cpp) does
    # `u0 = currentThrust - mNeutral; pid2_transfer(&PID, u0);` for
    # PositionHold's bumpless transfer - but pid2_apply()'s reconfigure math
    # (pid.c) makes the NEXT output exactly equal u0, so u0 needs to be the
    # actual desired output value, not an offset from neutral (confirmed by
    # PIDControlDown::UpdateNeutralThrust(), a few lines below in the same
    # file, calling pid2_transfer(&PID, mDownCommand) - the raw value, no
    # subtraction). Engaging PositionHold mid-descent (currentThrust well
    # below mNeutral) makes u0 strongly negative, clamped to ulow, and the
    # PID starts at min thrust regardless of what it should bumplessly
    # continue from - directly matching the ~150m+ climb-and-crash
    # overshoot seen engaging PositionHold while Stabilized2 was still
    # actively arresting a descent. hold_at()'s own settle-wait before
    # switching modes works around it without touching shared flight code -
    # flagging the Activate() asymmetry itself for a real fix.
    if not hold_at(3, "PositionHold (GPS position + CruiseControl altitude, PathFollower)", 25.0):
        return

    # "2D" test: baro altitude hold (altitudeloop.c, same as Stabilized2)
    # plus magnetometer-referenced yaw heading hold (Attitude mode uses
    # AttitudeState.Yaw directly) instead of GPS lateral position hold -
    # Roll/Pitch=Attitude only levels the craft, so horizontal drift is
    # expected/acceptable here (no PathFollower/GPS involvement at all,
    # matches board_orientation_viz.py's Stabilization3Settings).
    if not hold_at(2, "2D hold (baro altitude + magnetometer yaw, no GPS/PathFollower)", 20.0):
        print("[test] sequence done (landed via crash handler)")
        return

    # Leaving the vehicle armed in an autonomous hold mode with nobody
    # supervising it once the scripted test is over is exactly the
    # "nobody's landing it" gap being fixed here - land() takes over with
    # manual throttle and a real height check, same controlled-descent
    # logic as emergency_land(), just without the "crashed" framing since
    # this is a normal, planned end of test.
    land()
    print("[test] sequence done")


# ---------------------------------------------------------------------------
# UAVTalk <-> flight code
# ---------------------------------------------------------------------------

def uavtalk_thread():
    db = uavtalk.UAVObjectDB(bov.default_xml_dir())
    xport = UdpTransport(UDP_HOST, UDP_PORT)
    client = UAVTalkClient(xport, db)
    configured = {"done": False}
    last_arm_state = {"armed": None}
    # Latency instrumentation (see sender_loop's ActuatorCommand request and
    # on_object's ActuatorCommand branch): last_request_ts is stamped right
    # before each request_object("ActuatorCommand") send, so the response
    # handler can compute the raw wire round-trip time. last_actuator_value/
    # last_change_ts track whether the VALUE actually changed between
    # responses, to distinguish "fast responses" from "fast responses that
    # keep re-reading the same stale cached value" - the latter is what
    # would actually explain the instability, not raw ping time.
    latency_stats = {
        "last_request_ts": None, "samples": [], "last_value": None,
        "last_change_ts": None, "change_intervals": [],
    }

    def send_reliable(name, values):
        # client.send_object() is a single fire-and-forget UDP datagram
        # (plain TYPE_OBJ, no ack/retry) - during send_config()'s startup
        # burst of 8 settings objects sent within ~2s, right as Gazebo/
        # fw_simposix/this bridge are all still spinning up, a single
        # dropped packet silently leaves that one object at its firmware
        # default with no error and nothing in this bridge's own logs to
        # show it happened. Observed directly: a run where every other
        # object landed fine but ActuatorDesired.Thrust stayed at exactly
        # 0.0 the entire flight despite StabilizationDesired.Thrust ramping
        # correctly - consistent with FlightModeSettings or StabilizationBank
        # silently not landing. Sending twice with a short gap is a cheap
        # hedge against a single lost packet without needing full
        # ack-tracking/retry machinery.
        client.send_object(name, values)
        time.sleep(0.05)
        client.send_object(name, values)

    def send_config():
        home = dict(bov.HOMELOCATION_DEFAULTS)
        home["Latitude"] = int(HOME_LATITUDE * 1e7)
        home["Longitude"] = int(HOME_LONGITUDE * 1e7)
        home["Altitude"] = HOME_ALTITUDE
        # The vehicle spawns level with Yaw=0 (model.sdf has no initial
        # rotation), so body-frame FRD == world-frame NED at this instant -
        # measuring Gazebo's own magnetometer reading right now and using
        # it AS Be guarantees filtermag.c's checkMagValidity() compares
        # against whatever Gazebo is actually reporting, not a separately
        # assumed reference (see on_mag()'s comment for why that mismatch
        # mattered - it caused a fast, severe attitude tumble when mag
        # fusion was re-enabled with a mismatched Be). Falls back to the
        # static default only if no mag reading arrived in time.
        for _ in range(20):  # up to 2s
            have_mag, mag_body = state.mag_snapshot()
            if have_mag:
                home["Be"] = list(mag_body)
                break
            time.sleep(0.1)
        send_reliable("RevoSettings", bov.resolve_enum_values(db["RevoSettings"], bov.REVOSETTINGS_DEFAULTS))
        time.sleep(0.2)
        send_reliable("HomeLocation", bov.resolve_enum_values(db["HomeLocation"], home))
        time.sleep(0.2)
        send_reliable("MixerSettings", bov.resolve_enum_values(db["MixerSettings"], bov.mixer_settings()))
        time.sleep(0.2)
        # firmware default AccelDriftKi=0.0005 is far too slow to track a
        # real, fast accel transient (measured swinging ~0.25 to -9.81 and
        # back within about a second during a PositionHold runaway) -
        # accelBiasState stays stranded far from accelState for seconds,
        # and the resulting "corrected acceleration" error double-integrates
        # into a real runaway (see filteraltitude.c's own comment on this).
        # Testing whether a much faster bias-tracking rate closes that gap.
        send_reliable("AltitudeFilterSettings", {
            "AccelLowPassKp": 0.04, "AccelDriftKi": 0.05,
            "InitializationAccelDriftKi": 0.2, "BaroKp": 0.04,
        })
        time.sleep(0.2)
        # Without this, the flight side has no idea GCSReceiver's channels
        # are meant to be Throttle/Roll/Pitch/Yaw/FlightMode - nothing ever
        # reaches ManualControlCommand/StabilizationDesired at all.
        send_reliable("ManualControlSettings", {
            "ChannelGroups": [5, 5, 5, 5, 5, 7, 7, 7, 7],  # GCS=5, None=7
            "ChannelNumber": [1, 2, 3, 4, 5, 0, 0, 0, 0],
            "ChannelMin": [1000] * 9,
            "ChannelNeutral": [1050, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500],
            "ChannelMax": [2000] * 9,
            "ResponseTime": [0] * 7, "Deadband": 0.02, "DeadbandAssistedControl": 0.08,
            "FlightModeNumber": 4, "FailsafeFlightModeSwitchPosition": -1,
            "FailsafeChannel": [-1, 0, 0, 0, 0, 0, 0, 0],
        })
        time.sleep(0.2)
        fms = bov.flight_mode_settings(control.armed, ["Attitude", "Attitude", "Attitude"])
        send_reliable("FlightModeSettings", bov.resolve_enum_values(db["FlightModeSettings"], fms))
        time.sleep(0.2)
        # This bridge exists to unit-test real flight-code changes, so it
        # should run PathFollower with the same gains/timing real hardware
        # runs. An earlier round of speculative tuning here (documented in
        # git history) didn't fix a lateral instability and was reverted to
        # stock defaults - but that was BEFORE the real root causes were
        # found and fixed this session (mag fusion drift from a mismatched
        # HomeLocation.Be, PIDControlDown::Activate()'s bumpless-transfer
        # bug, gravity-only accel starving filteraltitude.c's velocity
        # integrator). With those fixed, the remaining PositionHold
        # overshoot/drift looks like genuine underdamping for this specific
        # airframe (1.5kg, low inertia): VerticalVelPID had Kd=0.0 - no
        # derivative term at all to damp the correction, only P (how hard)
        # and I (windup), nothing controlling how it settles. Added modest
        # damping and backed off VerticalPosP's aggressiveness - re-test
        # against stock defaults if this doesn't hold up, since
        # vehicleconfigurationhelper.cpp's setup wizard never touches
        # VtolPathFollowerSettings for a real vehicle (grep confirms zero
        # references), so these numbers have no real-hardware precedent to
        # compare against, only physical/control-theory reasoning.
        # ThrustLimits.Neutral (X3's actual hover point, see the ramp
        # comment) and ThrustControl=auto (without it PositionHold never
        # runs real altitude-hold at all, see send_config()'s CruiseControl
        # comment) remain physical/functional necessities, not tuning.
        # VerticalVelMax=4.0 (stock default) lets the outer position loop
        # demand up to 4 m/s vertical velocity - on this light (1.5kg)
        # airframe, chasing that via bounded thrust [0.2,0.9] means
        # saturating at min/max thrust, and a thrust deficit that large
        # produces a real, violent acceleration (F=ma with small m) -
        # confirmed via PIDStatus/PositionState/VelocityState trace:
        # VelocityState.Down reversed from +1.13 m/s to -6.6 m/s in ~3s
        # right as command saturated at ulow=0.2, a real freefall, not a
        # control-math bug. Capping how large a velocity change the outer
        # loop can ever request keeps the inner loop's job achievable
        # without saturating thrust in the first place.
        vtol_pf = {
            "TreatCustomCraftAs": "VTOL",
            "HorizontalVelMax": 3.0, "VerticalVelMax": 1.5, "CourseFeedForward": 1.0,
            "HorizontalPosP": 0.25, "VerticalPosP": 0.25,
            "HorizontalVelPID": [8.0, 0.5, 1.0, 15], "VerticalVelPID": [0.3, 0.15, 0.08, 1.0],
            # ThrustLimits.Neutral is the altitude-hold PID's hover-point
            # baseline (vtolflycontroller.cpp: controlDown.UpdateNeutralThrust
            # uses it directly) - the XML's 0.5 default assumes a much
            # higher-thrust-margin airframe than X3's real ~0.68 thrust-
            # fraction hover point (see the ramp comment below). This is a
            # physical fact about this specific airframe, the same way a
            # real vehicle's actual weight/thrust ratio would be
            # calibrated in, not a tuning choice.
            "ThrustLimits": [0.2, 0.68, 0.9], "VelocityFeedforward": 2,
            "ThrustControl": "auto", "YawControl": "manual",
            "FlyawayEmergencyFallback": "enabled", "FlyawayEmergencyFallbackTriggerTime": 10.0,
            "EmergencyFallbackAttitude": [0, -20.0], "EmergencyFallbackYawRate": [2.0, 30.0],
            "MaxRollPitch": 25.0, "UpdatePeriod": 50, "BrakeRate": 2.5, "BrakeMaxPitch": 25.0,
            "BrakeHorizontalVelPID": [12.0, 0.0, 0.03, 15], "BrakeVelocityFeedforward": 0,
            "LandVerticalVelPID": [0.35, 3.0, 0.05, 0.9],
        }
        send_reliable("VtolPathFollowerSettings", bov.resolve_enum_values(db["VtolPathFollowerSettings"], vtol_pf))
        time.sleep(0.2)
        # Note: VtolPathFollowerSettings.YawControl="manual" (set above)
        # makes vtolflycontroller.cpp's UpdateStabilizationDesired() take
        # the yaw_attitude=false branch (flight/modules/PathFollower/
        # vtolflycontroller.cpp:274-280), which forces Yaw into
        # STABILIZATIONMODE_AXISLOCK the moment PositionHold activates -
        # regardless of the plain "Attitude,Attitude,Attitude"
        # FlightModeSettings sent above. That's real, hardcoded flight-code
        # behavior for PositionHold, not a bridge misconfiguration.
        # AxisLockKp/MaxAxisLock below are back at stock documented
        # defaults - a prior attempt at halving them (to compensate for
        # X3's smaller Izz vs whatever real airframe this was tuned
        # against) didn't fix the instability either, and per the user this
        # code has flown correctly on real hardware for years unmodified -
        # this bridge exists to unit-test real flight-code changes, so it
        # should run the same gains real hardware runs unless there's
        # concrete evidence a specific value needs to differ.
        stab_settings = {
            "FlightModeMap": ["Bank1"] * 6,
            "VbarSensitivity": [0.5, 0.5, 0.5],
            "VbarRollPI": [0.005, 0.002], "VbarPitchPI": [0.005, 0.002], "VbarYawPI": [0.005, 0.002],
            "VbarTau": 0.5, "VbarGyroSuppress": 30, "VbarPiroComp": "FALSE", "VbarMaxAngle": 10,
            "GyroTau": 0.005, "DerivativeCutoff": 20, "DerivativeGamma": 1,
            "AxisLockKp": 2.5, "MaxAxisLock": 30, "MaxAxisLockRate": 2,
            "WeakLevelingKp": 0.1, "MaxWeakLevelingRate": 5,
            "RattitudeModeTransition": 80,
            # vtolflycontroller.cpp hardcodes StabilizationMode.Thrust =
            # CRUISECONTROL for PositionHold (not something this bridge
            # chooses) - cruisecontrol.c boosts thrust by 1/cos(tilt_angle),
            # clamped at CruiseControlMaxPowerFactor. That's fine for brief
            # aggressive maneuvers on a well-tuned real aircraft, but once
            # a lean has already turned into a real tumble it just pours
            # more thrust into an out-of-control rotation instead of
            # helping recover - observed thrust jumping right as Roll blew
            # past the commanded lean angle during every crash this
            # session. cruisecontrol.c's own comment: "set MaxPowerFactor
            # to 1.0 to effectively disable boost" - doing that here.
            "CruiseControlMinThrust": 5, "CruiseControlMaxThrust": 90, "CruiseControlMaxAngle": 105,
            "CruiseControlMaxPowerFactor": 1.0, "CruiseControlPowerTrim": 100.0,
            "CruiseControlPowerDelayComp": 0.25,
            "CruiseControlFlightModeSwitchPosEnable": ["FALSE"] * 6,
            "CruiseControlInvertedThrustReversing": "Unreversed",
            "CruiseControlInvertedPowerOutput": "Zero",
            "LowThrottleZeroIntegral": "TRUE",
            "ScaleToAirspeed": 0, "ScaleToAirspeedLimits": [0.05, 3],
            "FlightModeAssistMap": ["None"] * 6,
        }
        send_reliable("StabilizationSettings", bov.resolve_enum_values(db["StabilizationSettings"], stab_settings))
        time.sleep(0.2)
        # StabilizationBank is the actual "currently active" gains
        # stabSettings.stabBank reads at runtime (flight/modules/Stabilization/
        # innerloop.c, outerloop.c) - settings="false" in stabilizationbank.xml
        # (it's normally a mirror the flight side copies into from whichever
        # StabilizationSettingsBankN is selected), but it's readwrite over
        # UAVTalk so sending it directly overrides the active gains without
        # having to worry about which bank is selected.
        #
        # This bridge exists to unit-test real flight-code changes against
        # something as close to real hardware as possible - the previous
        # version of this comment spent a whole session speculatively
        # scaling RollPI/RollRatePID/YawPI down from their shared/
        # uavobjectdefinition/stabilizationsettingsbank1.xml documented
        # defaults (all reduced to compensate for X3's per-axis moment of
        # inertia / weaker yaw authority) chasing a lateral instability -
        # none of it actually fixed the instability, and
        # vehicleconfigurationhelper.cpp's setup wizard never touches these
        # per-axis gains away from the XML defaults for any real vehicle
        # either. Reverted to stock documented defaults across the board -
        # if the sim is unstable with real gains, that's a simulation
        # fidelity bug to find, not something to tune away from what real
        # hardware actually runs.
        stab_bank = {
            "ManualRate": [150, 150, 175], "MaximumRate": [300, 300, 50],
            "StickExpo": [0, 0, 0],
            "RollRatePID": [0.0030, 0.0065, 0.000033, 0.3],
            "PitchRatePID": [0.0030, 0.0065, 0.000033, 0.3],
            "YawRatePID": [0.00620, 0.01000, 0.00005, 0.3],
            "RollPI": [2.5, 0, 50], "PitchPI": [2.5, 0, 50],
            "YawPI": [2.5, 0, 50],
            "AcroInsanityFactor": 0.4,
            "ThrustPIDScaleCurve": [0.3, 0.15, 0, -0.15, -0.3],
            "RollMax": 42, "PitchMax": 42, "YawMax": 42,
            "EnablePiroComp": "TRUE", "EnableThrustPIDScaling": "FALSE",
            "ThrustPIDScaleSource": "ActuatorDesiredThrust", "ThrustPIDScaleTarget": "PID",
            "ThrustPIDScaleAxes": "Roll Pitch",
        }
        send_reliable("StabilizationBank", bov.resolve_enum_values(db["StabilizationBank"], stab_bank))
        time.sleep(0.2)

    def on_connected():
        send_config()
        configured["done"] = True
        threading.Thread(target=run_test_sequence, daemon=True).start()

    def on_object(objdef, inst_id, decoded):
        ts = time.time()
        if objdef.name == "ActuatorCommand":
            publish_motor_speeds(decoded["Channel"])
            ch = tuple(decoded["Channel"][:4])
            if latency_stats["last_request_ts"] is not None:
                latency_stats["samples"].append(ts - latency_stats["last_request_ts"])
            if ch != latency_stats["last_value"]:
                if latency_stats["last_change_ts"] is not None:
                    latency_stats["change_intervals"].append(ts - latency_stats["last_change_ts"])
                latency_stats["last_value"] = ch
                latency_stats["last_change_ts"] = ts
            if VERBOSE:
                print(f"[dbg] t={ts:.2f} ActuatorCommand", decoded["Channel"][:4])
        elif objdef.name == "FlightStatus":
            if VERBOSE:
                print(f"[dbg] t={ts:.2f} FlightStatus.Armed =", decoded["Armed"])
        elif objdef.name == "ActuatorDesired":
            if VERBOSE:
                print(f"[dbg] t={ts:.2f} ActuatorDesired", decoded["Roll"], decoded["Pitch"], decoded["Yaw"], decoded["Thrust"])
        elif objdef.name == "ManualControlCommand":
            if VERBOSE:
                print(f"[dbg] t={ts:.2f} ManualControlCommand.Throttle =", decoded["Throttle"], "Thrust =", decoded["Thrust"], "Channel[0] =", decoded["Channel"][0])
        elif objdef.name == "StabilizationDesired":
            if VERBOSE:
                print(f"[dbg] t={ts:.2f} StabilizationDesired.Thrust =", decoded["Thrust"], "Mode =", decoded["StabilizationMode"])
        elif objdef.name == "AttitudeState":
            if VERBOSE:
                print(f"[dbg] t={ts:.2f} AttitudeState(estimated) rpy=", decoded["Roll"], decoded["Pitch"], decoded["Yaw"])
            fc_state.update_attitude(decoded["Roll"], decoded["Pitch"], decoded["Yaw"])
        elif objdef.name == "GyroState":
            if VERBOSE:
                print(f"[dbg] t={ts:.2f} GyroState(firmware-internal) xyz=", decoded["x"], decoded["y"], decoded["z"])
        elif objdef.name == "AccelState":
            if VERBOSE:
                print(f"[dbg] t={ts:.2f} AccelState(firmware-internal) xyz=", decoded["x"], decoded["y"], decoded["z"])
            fc_state.update_accel((decoded["x"], decoded["y"], decoded["z"]))
        elif objdef.name == "SystemAlarms":
            cur = decoded["Alarm"]
            prev = _last_alarms[0]
            if prev is None or cur != prev:
                if VERBOSE:
                    changed = {ALARM_NAMES[i]: cur[i] for i in range(len(ALARM_NAMES))
                               if prev is None or cur[i] != prev[i]}
                    print(f"[dbg] t={ts:.2f} SystemAlarms changed:", changed)
                _last_alarms[0] = list(cur)
        elif objdef.name == "PIDStatus":
            if VERBOSE:
                print(f"[piddbg] t={ts:.2f} setpoint={decoded['setpoint']:.3f} actual={decoded['actual']:.3f} "
                      f"error={decoded['error']:.3f} ulow={decoded['ulow']:.3f} uhigh={decoded['uhigh']:.3f} "
                      f"command={decoded['command']:.3f} P={decoded['P']:.3f} I={decoded['I']:.3f} D={decoded['D']:.3f}")
        elif objdef.name == "PositionState":
            if VERBOSE:
                print(f"[posdbg] t={ts:.2f} PositionState NED=({decoded['North']:.3f},{decoded['East']:.3f},{decoded['Down']:.3f})")
        elif objdef.name == "VelocityState":
            if VERBOSE:
                print(f"[posdbg] t={ts:.2f} VelocityState NED=({decoded['North']:.3f},{decoded['East']:.3f},{decoded['Down']:.3f})")

    def sender_loop():
        # A SINGLE deterministically-paced loop, not two independently
        # GIL-scheduled threads. An earlier version split sensor sends into
        # their own thread (targeting simposix's actual PIOS_SENSOR_RATE of
        # 500Hz, from pios_config.h - so 500Hz was the right number) running
        # alongside a second thread for GCSReceiver/ActuatorCommand-request.
        # Both threads share the one UDP socket but are scheduled
        # independently by Python's GIL, so their sends can burst against
        # each other unpredictably; if the firmware's UDP receive buffer
        # can't drain a burst in time, the OS silently drops the overflow -
        # no error, just gaps in the gyro feed. That fit both odd failure
        # modes better than an actual sign/gain bug: an uneven feed causing
        # erratic control response in one run, and what looked like
        # sustained drops (AttitudeState frozen at exactly 0.0 the whole
        # flight) in another. A single loop sending everything in a fixed,
        # deterministic order removes the inter-thread race entirely.
        # ~500Hz for sensors (matches PIOS_SENSOR_RATE). ActuatorCommand is
        # requested every iteration too - this is NOT just a debug readout,
        # publish_motor_speeds() in on_object() uses it to drive Gazebo's
        # actual simulated motors. Its own UAVObject definition
        # (shared/uavobjectdefinition/actuatorcommand.xml) declares
        # <telemetryflight updatemode="periodic" period="1000"/> - a 1Hz
        # default push - and this bridge was previously only explicitly
        # requesting it every 0.3s on top of that. So Gazebo's motors were
        # being driven by up to ~1-second-stale commands the whole time,
        # regardless of how fast sensors went in or how the sender loop was
        # threaded - a full second of open-loop drift is more than enough
        # to destabilize an axis with as little rotational inertia as Yaw
        # (Izz=0.0977 in the X3 model.sdf). uavtalk.c's TYPE_OBJ_REQ handler
        # (line ~654) always answers immediately regardless of an object's
        # periodic schedule, so requesting it every tick is safe and gets a
        # fresh value each time. GCSReceiver (stick input) doesn't need
        # this rate - every 10th tick (~50Hz) is plenty.
        # One distinct UAVTalk object per (throttled) slot, round-robin -
        # see the comment at this list's use site below for the full
        # investigation into why these need real spacing on this link.
        # GCSReceiver appears twice so it gets refreshed roughly twice as
        # often as the others - it directly gates flight safety, the
        # others are just telemetry/status.
        extra_actions = [
            lambda c: c.send_object("GCSReceiver", {"Channel": control.gcs_channels()}),
            lambda c: c.request_object("GyroState"),
            lambda c: c.send_object("GCSReceiver", {"Channel": control.gcs_channels()}),
            lambda c: c.request_object("SystemAlarms"),
            lambda c: c.request_object("FlightStatus"),
            lambda c: c.request_object("AccelState"),
            lambda c: c.request_object("PIDStatus"),
            lambda c: c.request_object("PositionState"),
            lambda c: c.request_object("VelocityState"),
            lambda c: c.request_object("ActuatorDesired"),
            lambda c: publish_baro(c),
            lambda c: publish_mag(c),
            lambda c: publish_gps_velocity(c),
            lambda c: publish_gps_position(c),
        ]
        i = 0
        send_intervals = []
        last_send_ts = [None]
        while True:
            if configured["done"] and client.connected:
                if control.armed != last_arm_state["armed"]:
                    fms = bov.flight_mode_settings(control.armed, ["Attitude", "Attitude", "Attitude"])
                    send_reliable("FlightModeSettings", bov.resolve_enum_values(db["FlightModeSettings"], fms))
                    last_arm_state["armed"] = control.armed

                have_pose, pos_ned, quat_ned, _, accel_body, gyro_dps = state.snapshot()
                if have_pose:
                    now_send = time.time()
                    if last_send_ts[0] is not None:
                        send_intervals.append(now_send - last_send_ts[0])
                    last_send_ts[0] = now_send
                    if len(send_intervals) >= 500:
                        if VERBOSE:
                            s = sorted(send_intervals)
                            n = len(s)
                            print(f"[sendtiming] n={n} gyro_send_interval_ms "
                                  f"min={s[0]*1000:.3f} p50={s[n//2]*1000:.3f} "
                                  f"p95={s[int(n*0.95)]*1000:.3f} max={s[-1]*1000:.3f}", flush=True)
                        send_intervals = []
                    publish_fast_sensors(client, accel_body, gyro_dps)

                latency_stats["last_request_ts"] = time.time()
                client.request_object("ActuatorCommand")
                # CORRECTION to an earlier theory in this investigation:
                # PIOS_gcsrcvr_Supervisor (the GCSReceiver staleness
                # watchdog) is confirmed a DEAD mechanism on posix -
                # PIOS_RTC_RegisterTickCallback() is a documented no-op
                # there (pios_rtc.c: "no periodic RTC tick to drive
                # registered callbacks from on posix... holding the last
                # commanded value forever is the behavior we want"). Direct
                # C-side tracing (gcsreceiver_updated()/receiver.c
                # instrumentation) confirmed cmd.Connected stays TRUE and
                # valid_input_detected stays TRUE throughout the stuck
                # window - the -1.0 seen was never the failsafe branch, it
                # was the NORMAL scaled output of a genuinely stale raw
                # channel value (1000, coincidentally scaling to -1.0 same
                # as our own FailsafeChannel.Throttle config - a red
                # herring, not evidence of failsafe). gcsreceiver_updated()
                # itself fires steadily (~36/s) throughout, meaning
                # fw_simposix's UAVTalk dispatch isn't stalled either - so
                # the backlog has to be BELOW that: PIOS_UDP_RxThread's
                # recvfrom() loop (pios_udp.c) has no local buffering ("if
                # the com buffer can't receive, data is discarded"), but
                # the OS kernel's own socket receive queue is a separate,
                # lower layer that drains in strict FIFO order - if that
                # thread's own processing (uavobjectmanager.c's
                # xSemaphoreTakeRecursive, contended by the main flight
                # task) falls behind our send rate for any stretch, a
                # kernel-level backlog of stale-but-valid packets would
                # explain every symptom seen: steady processing, no drops,
                # but multi-second-stale data. Neither ~50Hz nor ~400Hz
                # GCSReceiver rates fixed it, so trying the opposite:
                # throttling ALL the non-critical "extra" traffic well
                # below the 400Hz Gyro/Accel/ActuatorCommand-request
                # stream those three stay on (an established hard
                # requirement - PIOS_SENSOR_RATE, CLAUDE.md), giving the RX
                # thread real headroom instead of adding to what may
                # already be saturating it.
                if i % 20 == 0:
                    extra_actions[(i // 20) % len(extra_actions)](client)
                if i % 500 == 0 and latency_stats["samples"]:
                    if VERBOSE:
                        s = latency_stats["samples"]
                        c = latency_stats["change_intervals"]
                        s_sorted = sorted(s)
                        print(f"[latency] n={len(s)} wire_rtt_ms min={min(s)*1000:.2f} "
                              f"median={s_sorted[len(s)//2]*1000:.2f} max={max(s)*1000:.2f} | "
                              f"value_changes n={len(c)} " +
                              (f"median_interval_ms={sorted(c)[len(c)//2]*1000:.2f} "
                               f"implied_hz={1.0/(sum(c)/len(c)):.1f}" if c else "(none yet)"))
                    latency_stats["samples"] = []
                    latency_stats["change_intervals"] = []
                i += 1
            time.sleep(0.002)

    threading.Thread(target=sender_loop, daemon=True).start()
    threading.Thread(target=status_writer_loop, daemon=True).start()

    while True:
        try:
            client.run(on_object=on_object, on_connected=on_connected)
        except OSError:
            time.sleep(1.0)


_last_gyro_dbg = [0.0]
_last_alarms = [None]


def publish_fast_sensors(client, accel_body, gyro_dps):
    # Gyro/Accel are the only sensors that actually need to go out every
    # tick - stabilizationInnerloopTask (innerloop.c) is triggered directly
    # off GyroState updates, so this is on the critical control path.
    client.send_object("GyroSensor", {"x": gyro_dps[0], "y": gyro_dps[1], "z": gyro_dps[2], "temperature": 25.0})
    client.send_object("AccelSensor", {"x": accel_body[0], "y": accel_body[1], "z": accel_body[2], "temperature": 25.0})
    now = time.time()
    if now - _last_gyro_dbg[0] > 0.1:
        _last_gyro_dbg[0] = now
        if VERBOSE:
            print(f"[gyrodbg] t={now:.2f} gyro_dps=({gyro_dps[0]:.2f},{gyro_dps[1]:.2f},{gyro_dps[2]:.2f}) "
                  f"accel=({accel_body[0]:.2f},{accel_body[1]:.2f},{accel_body[2]:.2f})", flush=True)


# Baro/Mag/GPS are real hardware sensors that natively sample at tens of
# Hz, not gyro-rate hundreds of Hz - real Revolution firmware never asks
# StateEstimation to process Baro/Mag/GPS updates 500 times a second. Each
# is its own function (rather than one publish_slow_sensors() bundling all
# four) so sender_loop's round-robin can put a real gap between them - see
# its own "ROOT CAUSE" comment for why that gap actually matters on this
# link.
#
# Every sensor here is sourced from a real Gazebo sensor plugin - no
# hand-computed fallback. Earlier versions fell back to
# meters_to_latlon()-derived values for the brief window before the first
# real message arrived, but a "safety net" computed value is exactly the
# class of bug (mismatched reference, wrong convention) this whole session
# was spent hunting down - simply skip sending an object until its real
# sensor has reported at least once, rather than ever synthesizing one.
# send_config()'s wait_for_mag/HomeLocation.Be step already blocks briefly
# at startup for the same reason.
def publish_baro(client):
    have_baro, baro_alt = state.baro_snapshot()
    if have_baro:
        client.send_object("BaroSensor", {"Altitude": baro_alt, "Temperature": 25.0, "Pressure": 101.3})


def publish_mag(client):
    have_mag, mag_body = state.mag_snapshot()
    if have_mag:
        client.send_object("MagSensor", {"x": mag_body[0], "y": mag_body[1], "z": mag_body[2], "temperature": 25.0})


def publish_gps_velocity(client):
    have_navsat, lat, lon, alt, vel_ned = state.gps_snapshot()
    if have_navsat:
        client.send_object("GPSVelocitySensor", {"North": vel_ned[0], "East": vel_ned[1], "Down": vel_ned[2]})


def publish_gps_position(client):
    # Real navsat sensor data (gz-sim-navsat-system, see model.sdf/
    # quadcopter_ninjapilot.sdf) - a real sensor reading has none of the
    # lag a position-derivative introduces, which matters directly for
    # PositionHold's velocity-error feedback loop.
    have_navsat, lat, lon, alt, vel_ned = state.gps_snapshot()
    if have_navsat:
        groundspeed = math.sqrt(vel_ned[0] ** 2 + vel_ned[1] ** 2)
        heading = math.degrees(math.atan2(vel_ned[1], vel_ned[0]))
        client.send_object("GPSPositionSensor", bov.resolve_enum_values(client.db["GPSPositionSensor"], {
            "Status": "Fix3D",
            "Latitude": int(lat * 1e7),
            "Longitude": int(lon * 1e7),
            "Altitude": alt,
            "GeoidSeparation": 0.0,
            "Heading": heading,
            "Groundspeed": groundspeed,
            "Satellites": 7,
            "PDOP": 1.0,
            "HDOP": 0.8,
            "VDOP": 1.2,
            "SensorType": "Unknown",
            "AutoConfigStatus": "DISABLED",
        }))


# ---------------------------------------------------------------------------
# Gazebo motor command output
# ---------------------------------------------------------------------------

gz_motor_pub = None

# The QuadX mixer vectors (_QUADX_MOTOR_VECTORS in board_orientation_viz.py)
# assume, by their Roll/Pitch/Yaw coefficient signs: M1(Ch0)=Front-Left/cw,
# M2(Ch1)=Front-Right/ccw, M3(Ch2)=Back-Right/cw, M4(Ch3)=Back-Left/ccw.
# The X3 model's actual rotor_0..3 links (models/x3_ninjapilot/model.sdf)
# sit at completely different physical slots: rotor_0=Front-Right/ccw,
# rotor_1=Back-Left/ccw, rotor_2=Front-Left/cw, rotor_3=Back-Right/cw. Both
# position AND spin direction have to match or a roll/pitch/yaw correction
# lands on the wrong physical motor and fights itself. Matching each mixer
# motor to the rotor that's actually in its assumed slot gives a complete,
# unambiguous remap: M1->rotor_2, M2->rotor_0, M3->rotor_3, M4->rotor_1.
CHANNEL_TO_ROTOR = [2, 0, 3, 1]


def publish_motor_speeds(channels):
    if gz_motor_pub is None:
        return
    # ActuatorCommand channels 0-3 are the QuadX motors (see mixer_settings()
    # in board_orientation_viz.py). The mixer adds/subtracts Roll/Pitch/Yaw
    # corrections directly in PWM units, which only produces the intended
    # torque if PWM maps linearly to THRUST. But quadcopter.sdf's
    # MulticopterMotorModel plugin makes thrust quadratic in commanded
    # angular velocity (thrust = motorConstant * omega^2), so a naive linear
    # PWM->omega mapping put hover at omega_frac~0.825 (since sqrt(14.9N /
    # 21.9N max) ~ 0.825) while only being 68% of max thrust - leaving just
    # ~17.5% of PWM range as headroom before a motor saturates at 2000us,
    # which caused stabilization corrections to saturate/windup and flip
    # the vehicle. Mapping PWM->omega via sqrt() instead makes PWM->thrust
    # linear (hover moves to frac~0.68, ~32% headroom), matching what the
    # mixer's linear addition actually assumes.
    speeds = [0.0, 0.0, 0.0, 0.0]
    for ch_idx, rotor_idx in enumerate(CHANNEL_TO_ROTOR):
        frac = max(0.0, min(1.0, (channels[ch_idx] - 1000) / 1000.0))
        speeds[rotor_idx] = math.sqrt(frac) * MOTOR_MAX_RAD_S
    msg = Actuators()
    msg.velocity.extend(speeds)
    gz_motor_pub.publish(msg)


def main():
    global gz_motor_pub

    node = transport.Node()
    node.subscribe(Pose_V, POSE_TOPIC, on_pose)
    node.subscribe(IMU, IMU_TOPIC, on_imu)
    node.subscribe(NavSat, NAVSAT_TOPIC, on_navsat)
    node.subscribe(Magnetometer, MAGNETOMETER_TOPIC, on_mag)
    node.subscribe(FluidPressure, AIR_PRESSURE_TOPIC, on_air_pressure)
    gz_motor_pub = node.advertise(MOTOR_TOPIC, Actuators)

    print("Subscribed to %s, %s, %s, publishing motor commands on %s" % (POSE_TOPIC, IMU_TOPIC, NAVSAT_TOPIC, MOTOR_TOPIC))
    print("HomeLocation: %.6f, %.6f, %.1fm" % (HOME_LATITUDE, HOME_LONGITUDE, HOME_ALTITUDE))
    print("Verbose per-object/per-sample debug prints: %s (set NINJAPILOT_VERBOSE=1 to enable)" %
          ("ON" if VERBOSE else "off"))

    t = threading.Thread(target=uavtalk_thread, daemon=True)
    t.start()

    try:
        while True:
            time.sleep(1.0)
    except KeyboardInterrupt:
        pass


if __name__ == "__main__":
    main()
