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
import random
import struct
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
# Pure configuration module. This used to be board_orientation_viz, which
# also ran a web viewer with its OWN UAVTalk client on this same telemetry
# port - it stole the bridge's packets and produced unexplained flyaways.
# The viewer is gone; only the configuration survives.
import flight_config as bov
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "tools"))
from star_geom import fillet_plan

# The [dbg]/[piddbg]/[posdbg]/[navsatdbg]/[barodbg]/[gyrodbg]/[sendtiming]/
# [latency] prints below fire at up to ~500Hz combined (every ActuatorCommand,
# every sensor sample) - terminal I/O at that rate measurably slows down the
# sender_loop, which is timing-sensitive (see CLAUDE.md's notes on gyro feed
# gaps from scheduling jitter). Off by default; set NINJAPILOT_VERBOSE=1 to
# get them back for an actual debugging session. [test]/crash/land messages
# are unaffected - those are low-frequency and always worth seeing.
VERBOSE = os.environ.get("NINJAPILOT_VERBOSE", "0") == "1"

# Force flush on every print in this module: with stdout redirected to a log
# file Python block-buffers, and unflushed PASS/FAIL/abort lines sat in the
# buffer for many minutes while monitors watched the file for exactly those
# lines (mission 14's ground-contact abort was invisible for 19 minutes).
_print = print
def print(*args, **kwargs):  # noqa: A001 - deliberate module-wide shadow
    kwargs.setdefault("flush", True)
    _print(*args, **kwargs)

# NINJAPILOT_TEST_MODE=manual_hover runs manual_hover_test() instead of the
# scripted run_test_sequence() - see manual_hover_test()'s own docstring for
# why this exists (isolating "can the physical vehicle actually be flown to
# and held at a real height at all" from "does the flight controller's own
# state estimator/hold-mode logic work", since the latter was found to be
# broken independent of which vertical-channel filter algorithm is used).
TEST_MODE = os.environ.get("NINJAPILOT_TEST_MODE", "scripted")
# NINJAPILOT_MISSION=star flies ONLY the 5-point star at 8m + land -
# a ~90s iteration loop for corner/yaw tuning instead of the 4.5min
# full star/octagon/KF mission.
MISSION_SHAPE = os.environ.get("NINJAPILOT_MISSION", "full")

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
        self._pose_t_last = 0.0
        self.pose_vel_d = 0.0
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
            # Pose-derived vertical rate (lightly low-passed) - the pose
            # topic is the FASTEST ground-truth feed available. The navsat
            # velocity (gps_vel_ned) only updates at 10Hz, and using it as
            # the damping/rate feedback in the manual-hover controller
            # produced a classic delayed-feedback oscillation (vehicle
            # yo-yoing 0.7-11.5m with correct-per-sample commands).
            if self.have_pose and t > self._pose_t_last:
                dt = t - self._pose_t_last
                raw = (pos_ned[2] - self.pos_ned[2]) / dt
                self.pose_vel_d = 0.7 * self.pose_vel_d + 0.3 * raw
            self._pose_t_last = t
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

    def pose_alt_climb(self):
        """(have_pose, altitude_up_m, climb_rate_up_mps) - both derived
        from the fast pose topic (climb rate low-passed), NOT the 10Hz
        navsat velocity. Use this for any closed-loop control done bridge-
        side; the navsat feed's latency destabilizes rate feedback."""
        with self.lock:
            return (self.have_pose, -self.pos_ned[2], -self.pose_vel_d)


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
    # Unconditional (no 0.5s print-throttle) call counter - confirmed via a
    # real run that the THROTTLED [barodbg] print landed at an almost
    # exactly-0.5s cadence for the entire ~6 minute test, every single
    # time, which only tells us the print gate works, not how often this
    # callback itself actually fires or whether msg.pressure is tracking
    # real altitude. A real run also showed this printed altitude frozen
    # bit-for-bit (pressure_pa=101324.34 repeated 5x) for 2+ real seconds
    # while ActuatorCommand was pegged near-max and ground-truth pose
    # (ground truth /pose/info topic, separate subscription) showed the
    # vehicle actually climbing toward an 8m runaway - i.e. the flight
    # code's own baro-driven altitude estimate was stuck reporting ground
    # level while the real vehicle kept climbing under the resulting
    # sustained high thrust. This counter plus an un-throttled periodic
    # comparison against ground-truth pose altitude (state.snapshot(), the
    # SAME independent pose subscription used for climb_rate/check_crash)
    # is here to determine whether that's (a) this callback genuinely not
    # firing often/at all during sustained climbs (a Gazebo transport/
    # threading stall specific to this topic), or (b) firing normally but
    # with a msg.pressure value that itself isn't tracking real altitude
    # (a Gazebo air_pressure sensor plugin bug) - the existing 0.5s-gated
    # print alone can't distinguish these.
    _baro_call_count[0] += 1
    if now - _last_baro_diag[0] > 1.0:
        _last_baro_diag[0] = now
        have_pose, pos_ned, _, _, _, _ = state.snapshot()
        truth_alt = -pos_ned[2] if have_pose else float("nan")
        if VERBOSE:
            print(f"[barodiag] t={now:.2f} calls_since_last={_baro_call_count[0] - _baro_call_count[1]} "
                  f"pressure_pa={msg.pressure:.2f} baro_alt={altitude:.4f} truth_alt={truth_alt:.4f} "
                  f"delta={altitude - truth_alt:.4f}", flush=True)
        _baro_call_count[1] = _baro_call_count[0]
    if now - _last_baro_dbg[0] > 0.5:
        if VERBOSE:
            print(f"[barodbg] t={now:.2f} pressure_pa={msg.pressure:.2f} altitude={altitude:.4f}", flush=True)
        _last_baro_dbg[0] = now


_last_baro_dbg = [0.0]
_last_baro_diag = [0.0]
_baro_call_count = [0, 0]  # [total, count at last diag print]



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
        # See reset_estimator()'s own docstring for why this exists: a
        # plain disarm/rearm does NOT reset filteraltitude.c's internal
        # altitudeState/velocityState/accelBiasState - only a real
        # RevoSettings.FusionAlgorithm value CHANGE (while disarmed) does,
        # confirmed by reading stateestimation.c's own reinit gate.
        self.request_estimator_reset = False

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
# FEET_TO_M/vario_climb_and_hold() calls in run_test_sequence). Confirmed via a real
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


def reset_estimator(timeout=3.0):
    """Disarm, force a real state-estimator reinit, leave disarmed (caller
    re-arms). A plain disarm/rearm does NOT do this on its own: confirmed
    by reading stateestimation.c's own StateEstimationCb() - the filter
    chain only reinitializes (which is what actually zeros
    filteraltitude.c's accumulated altitudeState/velocityState/
    accelBiasState) when RevoSettings.FusionAlgorithm's VALUE changes
    while disarmed, not merely on an arm-state transition. Confirmed
    necessary by direct evidence: a real run had PositionState.Down stuck
    at -5.444 (VelocityState.Down stuck at -1.633, motionless) for the
    ENTIRE 10s "5ft hold" while real GPS/pose showed the vehicle sitting
    stationary on the ground the whole time - the estimate had diverged
    and, unlike a real gust or maneuver, was never going to correct
    itself. Toggles through Basic (Complementary) and back rather than
    just re-sending the target algorithm, since sending the SAME value
    twice never produces the `!=` this depends on."""
    control.armed = False
    time.sleep(0.3)  # let the disarm actually land before requesting reinit
    control.request_estimator_reset = True
    deadline = time.time() + timeout
    while control.request_estimator_reset and time.time() < deadline:
        time.sleep(0.05)


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


def _wait_for_vertical_settle(mode_label, timeout=7.0):
    """Poll until vertical velocity is near zero (or timeout), aborting via
    emergency_land() on a crash. Shared by hold_at() and
    enter_altitude_vario(): engaging a mode with real residual velocity
    still present means stabilizationAltitudeHold()'s reinit captures a
    real target position but zeros the PIDs (pid_zero(&pid0);
    pid_zero(&pid1)) with no bumpless transfer for velocity at all - the
    vehicle keeps moving under its own real momentum while the
    freshly-zeroed PID has no idea, the same class of bug flagged for
    PIDControlDown::Activate() elsewhere in this file. Returns
    (ok, vel_down) - ok is False only if a crash was handled (caller
    should stop the sequence)."""
    print(f"[test] waiting for vertical velocity to settle before {mode_label}...")
    settled = False
    vel_down = 0.0
    for _ in range(int(timeout / 0.1)):
        _, _, _, vel_ned, _, _ = state.snapshot()
        vel_down = vel_ned[2]
        if abs(vel_down) < 0.3:
            settled = True
            break
        crashed, reason = check_crash()
        if crashed:
            emergency_land(f"waiting to settle before {mode_label}: {reason}")
            return False, vel_down
        time.sleep(0.1)
    print(f"[test] vertical velocity wait ended: settled={settled} vel_down={vel_down:.3f}")
    return True, vel_down


def hold_at(mode_position, mode_label, hold_seconds):
    """Wait for vertical velocity to settle, then switch flight mode and
    hold. For mode transitions where the destination mode's own reinit is
    responsible for capturing whatever it needs (e.g. PositionHold's
    PathFollower auto-captures position on entry). Returns True if the
    hold completed normally, False if a crash was handled (caller should
    stop the sequence)."""
    ok, _ = _wait_for_vertical_settle(mode_label)
    if not ok:
        return False
    print(f"[test] switching to {mode_label}")
    control.mode_position = mode_position
    return wait_with_crash_check(hold_seconds, f"{mode_label} hold")


DEADBAND_CENTER = 0.5  # altitudeloop.c: stick centered here = hold, not climb/descend
VARIO_CLIMB_THROTTLE = 0.8  # comfortably above altitudeloop.c's DEADBAND_HIGH (0.6)


def enter_altitude_vario(mode_position, mode_label):
    """Switch into an AltitudeVario-thrust flight mode at deadband-center
    throttle (0.5), so outerloop.c's reinit (which fires exactly once, on
    this actual StabilizationMode transition - see outerloop.c's
    `reinit = (...OuterLoop... != previous_mode[t])`) captures the CURRENT
    PositionState.Down and holds it immediately, rather than inheriting
    whatever control.throttle happened to be last set to. That matters
    because if control.throttle was left above the ~0.6 deadband (e.g.
    HOVER_THRUST=0.68, the value another flight mode like PositionHold's
    CruiseControl thrust doesn't touch or reset), entering this mode would
    make altitudeloop.c read it as a climb command instead of a hold the
    instant it engages. Returns True normally, False if a crash was
    handled while waiting to settle (caller should stop the sequence)."""
    ok, _ = _wait_for_vertical_settle(mode_label)
    if not ok:
        return False
    control.throttle = DEADBAND_CENTER
    print(f"[test] switching to {mode_label}")
    control.mode_position = mode_position
    return True


def vario_climb_and_hold(target_alt_m, mode_position, mode_label, hold_seconds, max_climb_time=25.0):
    """Climb to target_alt_m and hold using the REAL flight-code altitude
    control the entire time (flight/modules/Stabilization/altitudeloop.c's
    stabilizationAltitudeHold(), STABILIZATIONDESIRED_STABILIZATIONMODE_
    ALTITUDEVARIO) instead of a hand-rolled bridge-side throttle
    controller. Engages the mode once via enter_altitude_vario() (deadband-
    center throttle, captures current altitude and holds it), then pushes
    the raw Thrust setpoint above the ~0.6 deadband to command a real
    closed-loop climb, and brings it back to center once close to target
    so the SAME flight code (still in the same StabilizationMode -
    outerloop.c's reinit only fires on an actual mode transition, never on
    this internal thrustMode toggle) captures the new altitude and holds
    it, with continuous, bumpless PID state the whole time.

    This replaces the old climb_to()/hold_at() pair, which did the ENTIRE
    climb in a separate Thrust=Manual mode using hand-rolled Python
    throttle math with no connection to the real altitude-hold PID at all
    - meaning every climb-phase crash this test harness ever hit was a bug
    in that bridge-side math, not in the flight code, and the flight
    code's actual climb behavior was never being exercised, only its
    ability to latch a static point it was handed already-reached. See
    board_orientation_viz.py's Stabilization2Settings/Stabilization3Settings
    comments for the AltitudeHold->AltitudeVario mode change this depends
    on. Returns True if the hold completed normally, False if a crash was
    handled (caller should stop the sequence)."""
    if not enter_altitude_vario(mode_position, mode_label):
        return False
    time.sleep(1.5)  # let pid1's I-term find real hover thrust before commanding a climb
    crashed, reason = check_crash()
    if crashed:
        emergency_land(f"stabilizing hover before climbing via {mode_label}: {reason}")
        return False

    print(f"[test] climbing to {target_alt_m:.2f}m via {mode_label} (real AltitudeVario)...")
    start_time = time.time()
    control.throttle = VARIO_CLIMB_THROTTLE
    alt = climb_rate = 0.0
    reached = False
    while time.time() - start_time < max_climb_time:
        have_pose, pos_ned, _, vel_ned, _, _ = state.snapshot()
        alt = -pos_ned[2] if have_pose else 0.0
        climb_rate = -vel_ned[2] if have_pose else 0.0  # positive = climbing
        crashed, reason = check_crash()
        if crashed:
            emergency_land(f"climbing to {target_alt_m:.2f}m via {mode_label}: {reason}")
            return False
        # altitudeloop.c's own VelocityDesired ceiling is bounded to 1.5
        # m/s (see its SIMPOSIX ALTITUDEHOLD_MAX_VELOCITY comment) - a
        # modest stopping margin gives its real PID deceleration room
        # instead of relying on this loop's 0.1s poll interval alone.
        stopping_margin = max(0.0, climb_rate) * 0.5
        if alt + stopping_margin >= target_alt_m:
            reached = True
            break
        if VERBOSE:
            print(f"[climbdbg] alt={alt:.3f} climb_rate={climb_rate:.3f} throttle={control.throttle:.3f}", flush=True)
        time.sleep(0.1)

    control.throttle = DEADBAND_CENTER
    print(f"[test] centering thrust stick: reached={reached} alt={alt:.3f} climb_rate={climb_rate:.3f} "
          f"- real AltitudeHold PID takes over")
    return wait_with_crash_check(hold_seconds, f"{mode_label} hold")


def wait_for_attitude_ok(timeout=90.0, stable_seconds=1.0):
    """Block until SystemAlarms.Attitude reads 'OK' and stays there for
    stable_seconds. This is the arming gate a real pilot gets for free
    from the GCS alarm display and okToArm(): filtercf.c deliberately
    suppresses ALL AttitudeState output for CALIBRATION_DELAY_MS (4s,
    returns ERROR) + CALIBRATION_DURATION_MS (6s of gyro-bias zeroing,
    returns CRITICAL) after every filter-chain init - and chain inits
    STACK (boot default chain, then the RevoSettings fusion-algorithm
    change from send_config(), then the HomeLocation write re-init each
    restart the clock). With no AttitudeState updates, outerloop.c is
    never dispatched (it is AttitudeState-event-driven), RateDesired
    stays stale, and ActuatorCommand sits at idle regardless of throttle
    - arming and commanding a climb inside that window is what produced
    the "vehicle ignores throttle for ~12s then snaps to near-max"
    behavior. This bridge force-arms via Arming="Always Armed", which
    bypasses okToArm()'s alarm check - so the contract real hardware
    enforces must be honored here explicitly instead.

    Returns True when ready, False on timeout (callers should abort the
    test rather than arm blind)."""
    deadline = time.time() + timeout
    ok_since = None
    last_progress = 0.0
    att_idx = ALARM_NAMES.index("Attitude")
    while time.time() < deadline:
        alarms = _last_alarms[0]
        att = alarms[att_idx] if alarms is not None else None
        if att == "OK":
            if ok_since is None:
                ok_since = time.time()
            elif time.time() - ok_since >= stable_seconds:
                print(f"[test] attitude estimator ready (Attitude alarm OK for {stable_seconds:.0f}s)")
                return True
        else:
            ok_since = None
        now = time.time()
        if now - last_progress > 5.0:
            last_progress = now
            print(f"[test] waiting for attitude estimator... (Attitude alarm: {att})", flush=True)
        time.sleep(0.25)
    alarms = _last_alarms[0]
    att = alarms[att_idx] if alarms is not None else "never reported"
    print(f"[test] ERROR: attitude estimator not ready after {timeout:.0f}s (Attitude alarm: {att}) - aborting")
    return False


def run_test_sequence():
    """Simple scripted acceptance test: arm, ramp to a hover throttle, hold,
    then hand off to PositionHold (Alt via CruiseControl + GPS position)."""
    print("[test] waiting 3s for link + config to settle...")
    time.sleep(3.0)

    # Do not arm during filtercf.c's calibration window - see
    # wait_for_attitude_ok's docstring for the whole story.
    if not wait_for_attitude_ok():
        return

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
    # altitude vario/hold, no PathFollower - see its own comment below) for
    # both stages, since it's the simpler, more fundamental thing to verify
    # before layering GPS/PathFollower on top in the PositionHold/2D-hold
    # stages that follow.
    #
    # Testing PURE baro altitude hold in isolation first, per the actual
    # architecture: PositionHold (flight mode index 3) routes through
    # PathFollower/VtolFlyController for BOTH horizontal AND vertical
    # (CruiseControl-based thrust) - but flight/modules/Stabilization/
    # altitudeloop.c provides a real, separate, fast-loop-native altitude
    # control (STABILIZATIONDESIRED_STABILIZATIONMODE_ALTITUDEVARIO) that
    # has nothing to do with PathFollower at all. "Stabilized2" (index 1,
    # see board_orientation_viz.py's Stabilization2Settings) is repurposed
    # to Roll/Pitch=Attitude (leveling) + Thrust=AltitudeVario. The climb
    # itself now runs through this same real flight-code PID via
    # vario_climb_and_hold() - see its own docstring for why the earlier
    # climb_to()/hold_at() pair never actually exercised this code at all
    # during the climb, only during the hold.
    print("[test] climbing to 5ft...")
    if not vario_climb_and_hold(5 * FEET_TO_M, 1, "5ft hold (Stabilized2, baro altitude, no PathFollower)", 10.0):
        return

    # Confirmed directly necessary, not precautionary: a real run had
    # PositionState.Down stuck at -5.444 (VelocityState.Down stuck at
    # -1.633, i.e. claiming continuous motion) for the entire 10s "5ft
    # hold" while real GPS/pose showed the vehicle sitting stationary on
    # the ground the whole time - a diverged estimate that was never
    # going to self-correct. See reset_estimator()'s own docstring for
    # why a plain disarm/rearm doesn't fix this on its own.
    print("[test] resetting state estimator before climbing further...")
    reset_estimator()
    # reset_estimator() toggles FusionAlgorithm, which re-inits the whole
    # filter chain - filtercf.c restarts its full calibration window
    # (4s silent + 6s bias zeroing, NO AttitudeState output the whole
    # time, so outerloop/thrust are dead - see wait_for_attitude_ok).
    # Re-arming and climbing before that window closes is flying blind
    # into the exact dead-zone this gate exists to prevent.
    if not wait_for_attitude_ok():
        # NEVER bare-return with the vehicle armed and airborne: an
        # earlier version did, and the abandoned vehicle held on the
        # throttle deadband for a while, drifted laterally with nothing
        # correcting it, and crashed - watched live. land() only needs
        # ground-truth height and manual Attitude mode, so it works even
        # with the estimator degraded (which is exactly when this abort
        # path runs).
        print("[test] estimator not ready after reset - landing instead of abandoning the vehicle")
        land()
        return
    control.mode_position = 0  # Stabilization1Settings = Thrust=Manual, for the arm gesture below
    control.throttle = 0.0
    control.armed = True
    time.sleep(2.0)

    print("[test] climbing to 10ft...")
    if not vario_climb_and_hold(10 * FEET_TO_M, 1, "10ft hold (Stabilized2, baro altitude, no PathFollower)", 10.0):
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

    # "2D" test: baro altitude vario/hold (altitudeloop.c, same as
    # Stabilized2) plus magnetometer-referenced yaw heading hold (Attitude
    # mode uses AttitudeState.Yaw directly) instead of GPS lateral position
    # hold - Roll/Pitch=Attitude only levels the craft, so horizontal drift
    # is expected/acceptable here (no PathFollower/GPS involvement at all,
    # matches board_orientation_viz.py's Stabilization3Settings).
    # enter_altitude_vario() (not hold_at()) because this mode's Thrust
    # axis is AltitudeVario now: it must force control.throttle to the
    # deadband center before switching, or it would inherit whatever
    # control.throttle was last set to (PositionHold's CruiseControl thrust
    # doesn't touch it, so it's still whatever vario_climb_and_hold() left
    # it at) and, if that's above the ~0.6 deadband, read it as a climb
    # command instead of a hold the instant this mode engages.
    mode_label = "2D hold (baro altitude + magnetometer yaw, no GPS/PathFollower)"
    if not enter_altitude_vario(2, mode_label) or not wait_with_crash_check(20.0, f"{mode_label} hold"):
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
# Waypoint mission support (NINJAPILOT_TEST_MODE=mission)
# ---------------------------------------------------------------------------

# CRC-8 poly 0x07 (MSB-first), init 0 - byte-identical to
# flight/pios/common/pios_crc.c's table. pathplanner.c's checkPathPlan()
# validates PathPlan.Crc as this CRC over the PACKED instance bytes of
# every Waypoint instance 0..WaypointCount-1, then every PathAction
# instance 0..PathActionCount-1, in that order. The bridge's
# objdef.pack() produces exactly the firmware's packed instance layout
# (proven by every UAVTalk send round-tripping), so computing the same
# CRC here is just packing in the same order.
def _crc8_07(crc, data):
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = ((crc << 1) ^ 0x07) & 0xFF if (crc & 0x80) else (crc << 1) & 0xFF
    return crc


# m/s, straight-line leg cruise. 1.5 -> 2.5. The old note here said 2.0
# "raced corners hard enough to dip into the ground" - that was when leg speed
# and corner speed were the same number and the vehicle arrived at a corner
# still carrying cruise momentum. They are now separate: this is the speed
# BETWEEN corners (paths.c reads it from ModeParameters[0]), while the corner
# itself is entered at _corner_speed() and confirmed stopped before the plan
# advances.
#
# 2.5 was tried (star83) and is past what this tune can hold: roll RMS 1.1 ->
# 8.0 deg with 77deg peak-to-peak, altitude swinging 9.6m, 4.5m of overshoot
# at the first corner, and the plan stalled. The velocity loop is the limit -
# HorizontalVelPID Kp is already at its measured ceiling of 4.0 (6.5 tumbled
# the vehicle outright), so a faster leg just means a larger velocity error
# feeding the same gain and a bigger tilt demand.
#
# 1.5 failed once (star85) but that was against a very different corner: a
# 0.5 m/s arrival speed that guaranteed overshoot, a sqrt braking curve the
# velocity loop could not track, and a yaw turn ramped at a fixed rate. All
# three are gone - corners are true stops, the arrival is a linear settle,
# and the turn is blended by distance - so the old ceiling is worth
# re-testing rather than inheriting. Retested at 1.4 (star93): overshoot came
# back at 0.60m mean and cross-track went 0.13 -> 0.28m, for six seconds saved
# on a 153s mission. CourseFeedForward is already 1.0s, so that overshoot is
# the velocity loop's own tracking lag and there is no lead left to buy. 1.2
# 1.2 was no better (star94): overshoot 0.53m, cross-track 0.27m, and 164s -
# slower than the 153s it was meant to beat, because every corner it overshot
# had to be re-approached. Higher cruise costs more at the corner than it
# saves on the leg - but that was measured when a corner cost 8-10s and any
# overshoot was expensive. Corners now cost 1-4s, so the trade is worth
# re-running. Re-ran it at 1.3 with cheap corners (star100): still worse -
# 147s against 126s, cross-track 0.18 -> 0.27m, overshoot 0.16 -> 0.40m. The
# limit is the velocity loop, whose Kp is already at its measured ceiling of
# 4.0, so above ~1 m/s the vehicle simply cannot track the braking profile
# and every corner pays for it.
#
# That loop then GOT faster (HorizontalVelPID Kd 0 -> 0.9, Kp 4 -> 7), which
# is precisely the condition those tests were waiting on: every one of them
# failed by overshooting the corner, and overshoot fell 0.18m -> 0.03m. So the
# ceiling is worth re-measuring rather than inherited. 1.5.
MISSION_SPEED = 1.5
# Waypoint acceptance radius (m). Level legs use a 2D horizontal check
# (ConditionParameters[1]=0), vertical-transition legs use 3D ([1]=1).
# Mission 12 flew a 3D check on LEVEL legs with radius 1.0 and flew away:
# a vertical estimator wobble >1m at the moment of horizontal arrival makes
# the 3D sphere unreachable, and a missed sphere is fatal under FollowVector
# - paths.c projects onto the INFINITE line, so past the endpoint nothing
# ever pulls back along-track; the vehicle sailed the wp0->wp1 line
# extension 30+ meters at EndingVelocity until the stall timeout. 2D
# acceptance makes level-leg advance immune to vertical wobble; the climb
# legs keep 3D (their 2D distance is ~0 from the start - they would trip
# immediately and skip the climb).
MISSION_WP_RADIUS = 1.0

# Arrival policy. A 1.0m acceptance sphere is a FLY-THROUGH rule: the plan
# advances the instant the vehicle clips the boundary, so at a corner the
# vehicle turns away 1m short and never visits the point at all. Measured on
# star75/76: closest approach to every one of the 6 star points was
# 0.86-1.15m, i.e. exactly the radius, with 0.0s spent inside 0.5m and
# never once passing the point. That is the "dwelling in the waypoint spot
# is off, sometimes short clearly a meter" the eye picks up in the trail.
#
# So corners get a PRECISE policy instead: a tight sphere plus the
# confirm-speed/dwell arrival test (pathplanner.c conditionDistanceToTarget
# ConditionParameters[2]/[3]) that was already implemented but left off.
# Fly-through waypoints keep the historic rule - clipping the sphere at
# cruise is the correct behaviour there, and demanding a slow arrival on a
# waypoint whose own leg velocity is 1.5 m/s would stall the plan forever.
# 0.5 -> 0.3. With the arrival cap in place the vehicle no longer overshoots
# (0.45m mean overshoot -> 0.09m), but it now approaches asymptotically, so a
# 0.5m sphere let the plan confirm while it was still 0.32-0.45m short at
# three of the corners. A tighter sphere is what asks it to actually finish
# the arrival, and is only affordable BECAUSE the overshoot is gone.
# 0.3 -> 0.15. The sphere is now the thing that decides how close it gets:
# with the arrival tapered there is no overshoot to carry it through the
# point, so it stops the moment the plan is satisfied. star89 confirmed at
# 0.20-0.26m from every corner and at_retire equalled closest approach at all
# of them - it was not failing to arrive, it was being told it had arrived.
# 0.15 -> 0.06. The vehicle retires at whatever distance first satisfies the
# sphere, so the sphere IS the parking distance: every waypoint in star114-118
# retired at 0.13-0.15m, i.e. it dwelled ALONGSIDE the point rather than on it.
# Tightening only became affordable once path_endpoint stopped capping its
# feed-forward at EndingVelocity=0 (PATH_ARRIVAL_MIN_CAP) - before that the
# last 0.1m closed at ~0.01 m/s and a tighter sphere would simply have stalled.
# 0.15 -> 0.60. This is the APEX radius of a swept corner, not a "how close
# did we get" tolerance.
#
# With a tight sphere the only thing commanding the vehicle near the vertex is
# endpoint homing, and that has NO outbound component until the waypoint
# retires - so the commanded heading just alternates between "forward to the
# vertex" (+146 deg) and "back to the vertex" (-25 deg) and the vehicle bounces
# across the point along the inbound line until the plan lets go. It never
# turns while moving; it stops, wobbles, then leaves. That bounce is the loop
# visible at every corner.
#
# Releasing the waypoint at 0.6m means the outbound leg becomes active while
# the vehicle is still inbound and still carrying speed, so it TRANSLATES
# through the corner on an arc - which is what a multirotor should do, and
# what a stop-and-pivot cannot. It passes within ~0.6m of the point instead of
# balancing on it, which is the trade that was explicitly accepted
# ("overshooting a little is fine").
# 0.20 -> 0.13. The stop point sits at roughly the sphere radius, so this is
# the vertex-touch distance: at 0.20 the corners read as clipping ~0.15m
# inside the star's tips ("a bit boxy"). 0.13 targets ~0.10m. The settle-wait
# risk that made tight spheres expensive is gone with yaw-following off - the
# vehicle now parks cleanly on first approach (star133/136).
MISSION_WP_RADIUS_PRECISE = 0.13  # m, corner acceptance sphere
MISSION_WP_RADIUS_3D = 0.35       # m, sphere for legs that move vertically
# 0.4 -> 0.6 m/s. This gate decides WHICH pass through the waypoint counts as
# an arrival, and 0.4 was rejecting the best one. The vehicle's first approach
# puts it within ~0.3m of the point at ~0.5 m/s - closer than it manages
# afterwards - but 0.5 > 0.4, so the plan declined it and waited, and what it
# waited through was the lead-term cycle swinging the vehicle back out to
# ~0.9m and in again. Every corner cost 8-10s of that. Accepting the first
# pass is also nearer what was asked for: slide into the corner already
# pointing down the next leg, touch the point, accelerate out - a racing line
# rather than a full stop and pivot.
MISSION_CONFIRM_SPEED = 0.9       # m/s, at-or-below counts as arrived
MISSION_DWELL_S = 0.1             # s it must hold that before advancing
# 0.3 -> 0.8 -> 0.5s. The dwell was widened when the corner turn still had to
# finish while parked. It does not any more: PRETURN_DIST starts the rotation
# 3.5m out and the vehicle now arrives already pointing down the next leg, so
# the dwell is back to being pure arrival confirmation. Every 0.1s here costs
# 0.8s of mission time across the 8 waypoints.


def _corner_speed(theta_deg):
    """Arrival speed at a waypoint as a function of how sharply the path
    turns there. paths.c's FollowVector interpolates leg speed linearly from
    StartingVelocity (= previous waypoint's Velocity) to EndingVelocity
    (= this waypoint's Velocity), so a low Velocity on a sharp corner makes
    the vehicle decelerate INTO the turn and re-accelerate out of it - the
    momentum that GoToEndpoint carried straight through the corner (2-4m of
    overshoot at 1.5 m/s) never builds up."""
    # These are ARRIVAL speeds - the speed the leg profile brakes to AT the
    # waypoint - and for a real corner the right answer is zero.
    #
    # They used to be small-but-nonzero (0.5 at a hairpin) on the theory that
    # the vehicle only had to arrive "slow enough to stop cleanly". It does not
    # work: paths.c brakes to exactly this speed at the waypoint, so the
    # vehicle reaches the point still moving and sails through it. Measured on
    # star86 with a 0.5 m/s hairpin arrival: every one of the 8 waypoints
    # overshot, by 0.58-0.86m, and then spent 7-20s recovering - which is why
    # RAISING the cruise speed made the mission SLOWER overall (252s against
    # 122s). The overshoot, not the cruise, was the time sink.
    #
    # A full stop (0.0) was flown for many runs and is the WRONG shape. Coming
    # to a standstill forces the vehicle to satisfy a tight acceptance sphere
    # while slow, and because the arrival oscillates between roughly 0.06m and
    # 0.35m it ends up waiting for the coincidence of "close enough AND slow
    # enough" - 10-14s of circling the point at every corner, which is 49-72%%
    # of the entire mission clock and is exactly the "toilet bowling" seen from
    # the Gazebo trail. Raising the velocity gain does not fix it (star124: the
    # loop just oscillates), because the problem is the demand, not the
    # authority.
    #
    # A nonzero corner speed asks for the shape actually wanted: turn INTO the
    # corner, let the tail come round while still moving, and accelerate out -
    # a racing line rather than a stop-and-pivot. The vehicle still passes
    # through the point; it simply never has to balance on it.
    if theta_deg < 25.0:
        return MISSION_SPEED         # straight-through: keep cruising
    if theta_deg < 70.0:
        return 0.4                   # gentle turn (octagon vertices, 45deg)
    if theta_deg < 115.0:
        return 0.15                  # right-angle turns (letter strokes)
    return 0.0                       # hairpin: STOP. The full dataset says
                                     # turn handedness is correct when the
                                     # vehicle is slow at the vertex (star122
                                     # full stops: 5/6 right) and a COIN FLIP
                                     # when it carries speed through (every
                                     # sweep variant: 0-2/6 with ~+200 deg
                                     # left loops). The sweep experiments
                                     # traded the corner's direction for
                                     # speed without knowing it.


def build_mission():
    """The requested flight: a 5-point star at 5m inside the visible grid,
    up 10m to an octagon at 15m, up 10m more to trace the letters K F at
    25m, then return to center and land. All NED, Down negative = up.
    Returns (waypoints, actions) as lists of plain dicts (enums as
    strings - resolved at send/pack time)."""
    pts = []  # ordered (n, e, d) mission geometry; velocities derived after

    def wp(n, e, d):
        pts.append((round(n, 3), round(e, 3), float(d)))

    # --- Climb straight up over the pad to mission altitude BEFORE going
    # anywhere. The first waypoint used to be the star's first point, so the
    # leg out of the 4m staging hover was a diagonal that climbed 4m and
    # translated 6m at the same time. It works, but it looks wrong and it
    # mixes the vertical transient into the first leg's tracking. A dedicated
    # vertical waypoint separates the two: climb here, then fly the star
    # level.
    wp(0.0, 0.0, -8.0)

    # --- Star at 5m: radius 6m, outer points every 72deg from North,
    # visited in 0-2-4-1-3 order (that ORDER is what draws a star), then
    # close back at the first point. The traversal still both starts and ends
    # at star point 0 - that is what closes the shape - but point 0 is now
    # reached by a level leg from the centre rather than by the climb.
    star_pts = []
    for k in range(5):
        a = math.radians(72 * k)
        star_pts.append((6.0 * math.cos(a), 6.0 * math.sin(a)))
    for k in [0, 2, 4, 1, 3, 0]:
        wp(star_pts[k][0], star_pts[k][1], -8.0)

    if MISSION_SHAPE == "star" and os.environ.get("NINJAPILOT_STAR_ARCS") == "1":
        # ARC CORNERS - EXPERIMENTAL, and the first flight FAILED (star131:
        # cross-track 6.56m mean, closest approach 4.65m, 254s, handedness
        # forced at only 3/6). The fillet radii the geometry allows at these
        # corner angles (0.09-0.22m for a 0.5m vertex miss) need 2-11 m/s^2
        # of centripetal acceleration at real arrival speeds - untrackable,
        # so the vehicle spirals hunting the ring and the 12 deg exit window
        # releases it at a random azimuth. Usable only if entry speed is
        # genuinely enforced AND a much larger miss is accepted. Kept for
        # that future, off by default.
        # Each vertex is a (tangent-entry, CircleRight-centre)
        # pair from tools/star_geom.fillet_plan() - the single source of
        # truth, shared with every scorer. The handedness of each corner is
        # now a property of the PATH: the follower is handed a clockwise arc
        # and exits it when the velocity points down the next leg
        # (PointingTowardsNext). This replaces every prior attempt to coax a
        # point-attractor into turning the right way, which star130 proved is
        # a coin flip (yaw disabled: identical corners split 2 right / 4
        # left).
        plan = fillet_plan()
        actions = [
            # [0] climb: 3D acceptance, confirmed arrival
            {"Mode": "FollowVector", "ModeParameters": [0, MISSION_SPEED, 0, 0],
             "EndCondition": "DistanceToTarget",
             "ConditionParameters": [MISSION_WP_RADIUS_3D, 1.0,
                                     MISSION_CONFIRM_SPEED, MISSION_DWELL_S],
             "Command": "OnConditionNextWaypoint",
             "JumpDestination": 0, "ErrorDestination": 0},
            # [1] leg to a tangent-entry: plain fly-through (the arc, not the
            # entry point, owns the corner)
            {"Mode": "FollowVector", "ModeParameters": [0, MISSION_SPEED, 0, 0],
             "EndCondition": "DistanceToTarget",
             "ConditionParameters": [0.45, 0, 0, 0],
             "Command": "OnConditionNextWaypoint",
             "JumpDestination": 0, "ErrorDestination": 0},
            # [2] the arc itself: clockwise, exit when velocity is within
            # 12 deg of the bearing to the next waypoint (= the next leg)
            {"Mode": "CircleRight", "ModeParameters": [0, 0, 0, 0],
             "EndCondition": "PointingTowardsNext",
             "ConditionParameters": [12, 0, 0, 0],
             "Command": "OnConditionNextWaypoint",
             "JumpDestination": 0, "ErrorDestination": 0},
            # [3] land (same parameters as ever)
            {"Mode": "Land", "ModeParameters": [0, 0, 0.6, 1],
             "EndCondition": "None", "ConditionParameters": [0, 0, 0, 0],
             "Command": "OnConditionNextWaypoint",
             "JumpDestination": 0, "ErrorDestination": 0},
        ]
        act_for = {"climb": 0, "entry": 1, "arc": 2, "home": 1, "land": 3}
        wps = []
        for w in plan:
            if w["kind"] == "arc" and w["dir"] != "CircleRight":
                raise AssertionError("star corner generated a LEFT arc - "
                                     "geometry bug, do not fly this")
            wps.append({"Position": [w["pos"][0], w["pos"][1], w["pos"][2]],
                        "Velocity": w["vel"], "Action": act_for[w["kind"]],
                        "_arc": w["kind"] == "arc"})
        return wps, actions

    if MISSION_SHAPE == "star":
        wp(0.0, 0.0, -8.0)
        wp(0.0, 0.0, -8.0)
        return _finish_mission(pts)

    # --- Octagon at 15m: radius 6m, 8 vertices + close. The first vertex
    # also carries the 10m climb (the paths are followed in 3D, so the
    # altitude ramps along the leg).
    for k in list(range(8)) + [0]:
        a = math.radians(45 * k)
        wp(6.0 * math.cos(a), 6.0 * math.sin(a), -18.0)

    # --- Letters K F at 25m, viewed from above: North = the letters' "up",
    # East = reading direction. Strokes are retraced where a pen-lift
    # would be (a flying quad has no pen to lift).
    # K: spine E=-6, arms out to E=-2.
    for n, e in [(4, -6), (-4, -6), (0, -6), (4, -2), (0, -6), (-4, -2)]:
        wp(n, e, -28.0)
    # F: spine E=1, bars out to E=5 (top) and E=4 (middle).
    for n, e in [(-4, 1), (4, 1), (4, 5), (4, 1), (0, 1), (0, 4)]:
        wp(n, e, -28.0)

    # --- Return to center, descend to 6m, then a Land action (plans wrap
    # around at the end in pathplanner.c, so the mission MUST terminate in
    # a Land action or it would loop back to the star forever).
    wp(0.0, 0.0, -8.0)
    wp(0.0, 0.0, -8.0)
    return _finish_mission(pts)


def _finish_mission(pts):
    # Per-waypoint arrival speed from the turn angle at that waypoint (3D:
    # the ring-to-ring climbs count as direction changes too).
    def leg(a, b):
        return (b[0] - a[0], b[1] - a[1], b[2] - a[2])

    def turn_angle(i):
        v_in = leg(pts[i - 1], pts[i])
        v_out = leg(pts[i], pts[i + 1])
        li = math.sqrt(sum(c * c for c in v_in))
        lo = math.sqrt(sum(c * c for c in v_out))
        if li < 1e-6 or lo < 1e-6:
            return 180.0  # degenerate (duplicate waypoint): treat as hairpin
        dot = sum(a * b for a, b in zip(v_in, v_out)) / (li * lo)
        return math.degrees(math.acos(max(-1.0, min(1.0, dot))))

    # FollowVector instead of GoToEndpoint: tracks the LINE between
    # waypoints (correction_vector = cross-track error only) and honors the
    # Starting->EndingVelocity speed ramp along the leg. GoToEndpoint flew at
    # constant EndingVelocity until the acceptance radius tripped, then
    # swapped legs with 1.5+ m/s of momentum - that momentum was the 2-4m
    # corner overshoot.
    #
    # Actions are generated per arrival policy rather than hard-coded, so a
    # waypoint that wants a precise confirmed stop and one that wants a
    # fly-through can coexist in the same plan. Identical policies share an
    # action (PathAction slots are a limited resource on real hardware).
    actions = []
    _seen = {}

    def _action(mode3d, radius, confirm, dwell):
        key = (bool(mode3d), round(radius, 3), round(confirm, 3), round(dwell, 3))
        if key not in _seen:
            _seen[key] = len(actions)
            actions.append(
                {"Mode": "FollowVector",
                 # [0] = leg cruise speed (paths.c). Without it a leg is capped
                 # at its own endpoint speeds, and in the star both endpoints
                 # are slow hairpins, so every leg crawled at the corner
                 # speed. [2]/[3] are filled in by the planner with the next
                 # leg's bearing.
                 # [1] = leg cruise speed. NOT [0]: slot 0 aliases
                 # GoToEndpoint's NEXTCOMMAND, and a 1.5 there casts to 1 ==
                 # RETURNTOBASENEXTCOMMAND_LAND, which lands the aircraft
                 # mid-mission (star84). [2]/[3] are filled in by the planner
                 # with the next leg's bearing.
                 "ModeParameters": [0, MISSION_SPEED, 0, 0],
                 "EndCondition": "DistanceToTarget",
                 "ConditionParameters": [radius, 1.0 if mode3d else 0.0,
                                         confirm, dwell],
                 "Command": "OnConditionNextWaypoint",
                 "JumpDestination": 0, "ErrorDestination": 0})
        return _seen[key]

    wps = []
    last = len(pts) - 1
    for i, (n, e, d) in enumerate(pts):
        theta = 180.0 if (i == 0 or i >= last - 1) else turn_angle(i)
        # theta is 180 for the entry waypoint and for the pre-land pair, so
        # all three come out as full stops - which is what they want.
        vel = _corner_speed(theta)

        # 3D acceptance for legs that MOVE vertically (climbs between rings,
        # the pre-land descent - their horizontal distance check would trip at
        # the start); 2D for level legs (immune to vertical estimator wobble -
        # see MISSION_WP_RADIUS comment). wp0's leg climbs in from the ~4m
        # staging hover, so it counts as vertical too.
        prev_d = -4.0 if i == 0 else pts[i - 1][2]
        mode3d = abs(d - prev_d) > 2.0

        if i == last:
            act = None  # Land, resolved below once its index is known
        elif theta < 25.0:
            # Fly-through: clip the sphere at cruise, keep the momentum.
            act = _action(mode3d, MISSION_WP_RADIUS, 0.0, 0.0)
        else:
            # A real corner. Require the vehicle to BE on the point and be
            # stopped there. The confirm speed must not be below what the
            # leg profile can deliver or the plan stalls (pathplanner.c says
            # so) - the corner controller's ARRIVE park is what actually
            # brings the speed down inside ARRIVE_DIST, well under this.
            confirm = max(MISSION_CONFIRM_SPEED, 0.0)
            # Vertical legs keep the wide sphere: a tight 3D sphere is
            # unreachable when the vertical estimator wobbles, and a missed
            # sphere used to be fatal. The confirm/dwell test is what makes
            # the arrival precise there, not the radius.
            # Vertical legs used a 1.0m sphere because a tight 3D sphere is
            # unreachable if the vertical estimator wobbles, and a missed
            # sphere used to be fatal. Neither still holds: the estimator
            # tracks its own GPS to ~0.02m and paths.c falls back to endpoint
            # homing rather than sailing away. Meanwhile 1.0m of slack on the
            # climb waypoint meant the vehicle started the star a metre low -
            # it confirmed the climb at 7.02m of an 8.00m target and spent the
            # whole first leg still climbing, which is the entire 0.90m
            # altitude peak-to-peak of star98 (the star's own legs held
            # 7.96-7.99m). Still looser than the horizontal sphere, out of
            # respect for the original lesson.
            radius = MISSION_WP_RADIUS_3D if mode3d else MISSION_WP_RADIUS_PRECISE
            act = _action(mode3d, radius, confirm, MISSION_DWELL_S)
        wps.append({"Position": [n, e, d], "Velocity": vel, "Action": act})

    # Land ModeParameters = [velN, velE, velDOWN, options] (plans.h
    # PATHDESIRED_MODEPARAMETER_LAND_*): velDown 0.6 m/s (matches the
    # FlightModeSettings.LandingVelocity default - all-zero parameters left
    # vtollandfsm's targetDescentRate at ~0.065 m/s, a 2.5-minute landing),
    # options=1 = LAND_OPTION_HORIZONTAL_PH (hold horizontal position during
    # the descent - without it the vehicle drifted ~9m downwind while
    # landing).
    land_idx = len(actions)
    actions.append(
        {"Mode": "Land", "ModeParameters": [0, 0, 0.6, 1],
         "EndCondition": "None", "ConditionParameters": [0, 0, 0, 0],
         "Command": "OnConditionNextWaypoint",
         "JumpDestination": 0, "ErrorDestination": 0})
    for w in wps:
        if w["Action"] is None:
            w["Action"] = land_idx
    return wps, actions


def poshold_test():
    """Fast-iteration 3D PositionHold test (NINJAPILOT_TEST_MODE=poshold):
    gate on estimator readiness, arm, real AltitudeVario climb to ~3m,
    engage PositionHold, then judge a 60s hold against GROUND TRUTH with
    real pass criteria - unlike wait_with_crash_check, sitting on the
    floor or drifting away scores a FAIL, not a timeout-pass. ~2min per
    iteration vs ~6min for the full scripted sequence."""
    print("[test] poshold_test: waiting 3s for link + config to settle...")
    time.sleep(3.0)
    if not wait_for_attitude_ok():
        return
    print("[test] poshold_test: arming")
    control.mode_position = 0
    control.throttle = 0.0
    control.armed = True
    time.sleep(2.0)

    if not vario_climb_and_hold(3.0, 1, "3m staging hold (Stabilized2)", 5.0):
        print("[test] poshold_test: FAIL - never reached staging altitude")
        return
    ok, _ = _wait_for_vertical_settle("PositionHold engage")
    if not ok:
        return
    have_pose, pos_ned, _, _, _, _ = state.snapshot()
    engage_alt = -pos_ned[2] if have_pose else 0.0
    engage_n, engage_e = pos_ned[0], pos_ned[1]
    print(f"[test] poshold_test: engaging PositionHold at alt={engage_alt:.2f}m "
          f"N={engage_n:.2f} E={engage_e:.2f}")
    control.mode_position = 3  # PositionHold

    start = time.time()
    last_log = 0.0
    max_alt_err = 0.0
    max_lat_err = 0.0
    while time.time() - start < 60.0:
        have_pose, pos_ned, _, vel_ned, _, _ = state.snapshot()
        alt = -pos_ned[2] if have_pose else 0.0
        lat_err = math.sqrt((pos_ned[0] - engage_n) ** 2 + (pos_ned[1] - engage_e) ** 2)
        alt_err = abs(alt - engage_alt)
        max_alt_err = max(max_alt_err, alt_err)
        max_lat_err = max(max_lat_err, lat_err)
        crashed, reason = check_crash()
        if crashed:
            emergency_land(f"poshold_test hold: {reason}")
            print(f"[test] poshold_test: FAIL - crashed ({reason})")
            return
        if alt < 0.3:
            print(f"[test] poshold_test: FAIL - sagged to ground (alt={alt:.2f}m "
                  f"at t+{time.time() - start:.0f}s) - landing")
            land()
            return
        if lat_err > 8.0:
            print(f"[test] poshold_test: FAIL - lateral flyaway ({lat_err:.1f}m "
                  f"at t+{time.time() - start:.0f}s) - landing")
            land()
            return
        now = time.time()
        if now - last_log > 2.0:
            last_log = now
            print(f"[test] poshold_test: t+{now - start:.0f}s alt={alt:.2f}m "
                  f"(err {alt_err:.2f}) lateral_err={lat_err:.2f}m", flush=True)
        time.sleep(0.1)

    print(f"[test] poshold_test: PASS - 60s hold complete. max_alt_err={max_alt_err:.2f}m "
          f"max_lateral_err={max_lat_err:.2f}m")
    land()
    print("[test] poshold_test: sequence done")


_waypoint_active = [None]   # latest WaypointActive.Index from telemetry
_mission_client = [None]    # set by on_connected for mission upload
_last_log_status = [None]   # latest DebugLogStatus (flight-periodic, 1Hz)
_vtol_pf_values = [None]    # resolved VtolPathFollowerSettings (for live YawControl flips)
_last_log_entry = [None]    # latest DebugLogEntry decoded dict


# --- On-board DebugLog: enable + pull over telemetry -------------------------
# The Logging module on simposix is the SAME code real boards run: entries go
# through PIOS_DEBUGLOG into the PIOS_FLASHFS logfs (on simposix that's
# pios_dosfs_logfs.c - one host file per slot, named from DebugLogEntry's
# objid with the flight number in the low byte, in the firmware's CWD - but
# we deliberately pull them over UAVTalk exactly like GCS does on hardware).
#
# Protocol (flight/modules/Logging/Logging.c):
#   enable   : DebugLogSettings.LoggingEnabled = OnlyWhenArmed
#              -> each arm..disarm span becomes one "flight"; the disarm
#              callback's Printf flushes the pending buffer, so flights are
#              always well terminated.
#   what     : per-object logging metadata (UAVObjMetadata flags bits 8-9 +
#              loggingUpdatePeriod), written over UAVTalk to the metaobject
#              (id = object id + 1). telemetry.c re-registers the object's
#              logging timer on metadata change, same as GCS's log settings.
#   pull     : write DebugLogControl{Operation=Retrieve, Flight, Entry};
#              Logging.c loads that slot into DebugLogEntry (Type=Empty when
#              past the end); DebugLogEntry is flight-telemetry "manual" so
#              it must be explicitly OBJ_REQ'd after each Retrieve.
#
# Slot payload: DebugLogEntryData is FlightTime u32, ObjectID u32, Flight
# u16, Entry u16, InstanceID u16, Size u16, Type u8, Data u8[200] (fields
# size-sorted like every UAVObject). UAVObject slots pack FOLLOW-ON records
# inside Data: after the first object's Size bytes, each subsequent record
# is a fresh 17-byte header + payload (pios_debuglog.c enqueue_data). The
# outer Type only says MultipleUAVObjects when the buffer overflowed - a
# Printf flush leaves it saying UAVObject even with several packed records -
# so the decoder always walks the tail regardless of the outer Type.

_META_STRUCT = struct.Struct("<HHHH")  # flags, telPeriod, gcsPeriod, logPeriod
_LOG_SUBHDR = struct.Struct("<IIHHHHB")  # sub-record header inside Data
_UAVOBJ_LOGGING_SHIFT = 8
_LOGMODE = {"manual": 0, "periodic": 1, "onchange": 2, "throttled": 3}

# What to log on the flight side, at what cadence. Periods in ms; "onchange"
# entries log every genuine update (SystemAlarms/WaypointActive only Set on
# real transitions, so they are cheap).
FC_LOG_OBJECTS = [
    ("PositionState", "periodic", 500),
    ("VelocityState", "periodic", 500),
    ("AttitudeState", "periodic", 500),
    ("GPSPositionSensor", "periodic", 1000),
    ("PathStatus", "periodic", 1000),
    ("FlightStatus", "periodic", 2000),
    ("WaypointActive", "onchange", 0),
    ("SystemAlarms", "onchange", 0),
    # Raw sensor inputs alongside the fused states: lets a post-flight
    # analysis separate "estimator diverged from its sensors" from "sensors
    # were wrong" (mission 12's vertical runaway analysis needed exactly
    # this and didn't have it).
    ("GPSVelocitySensor", "periodic", 1000),
    ("BaroSensor", "periodic", 1000),
]

# Extra high-rate objects used only by the autotune run: ActuatorDesired
# carries the relay's raw +/-Amplitude square wave, so logging it at 50ms
# is direct proof of WHICH axis the relay is driving and at what period
# (AttitudeState at 500ms aliases a 9Hz roll/pitch limit cycle into noise).
FC_LOG_OBJECTS_MISSION = [
    ("PositionState", "periodic", 100),
    ("VelocityState", "periodic", 100),
    ("AttitudeState", "periodic", 100),
    ("PathStatus", "periodic", 200),
    ("StabilizationDesired", "periodic", 200),
    # VelocityDesired is what the path layer ASKED for, as opposed to
    # VelocityState which is what the vehicle did. Without both you cannot
    # tell a path that commands a bad shape from a vehicle that fails to fly
    # a good one - which is exactly the question at a corner, where the
    # vehicle was seen swinging back and forth around the waypoint. Logged at
    # the same 100ms as VelocityState so the two can be compared sample for
    # sample.
    ("VelocityDesired", "periodic", 100),

    # --- added after the corner investigation, chosen by insight-per-byte ---

    # THE LEG THE VEHICLE WAS ACTUALLY GIVEN: Start, End, Starting/Ending
    # velocity, Mode and ModeParameters. On change only - about a dozen
    # records for a whole mission, ~0.4% of the log - and it is the single
    # most valuable thing here.
    #
    # It makes the analysis SELF-DESCRIBING. Every scorer currently compares
    # the flown path against a mission shape hard-coded in star_geom.py, and
    # when the mission changed and that file did not, the scorers kept
    # measuring the old shape and confidently reported 1.76m of cross-track
    # that was purely a stale planned path.
    #
    # It would also have collapsed the longest investigation of the session
    # into one glance: the corner controller was gated on ModeParameters[3],
    # nothing ever set it, and the block had therefore never executed. One
    # look at a logged PathDesired showing ModeParameters = [0,0,0,0] says
    # that immediately. The same record shows the slot-0 aliasing bug that
    # landed the aircraft mid-mission.
    ("PathDesired", "onchange", 0),

    # What the follower hands the MIXER (roll/pitch/yaw/thrust, normalised).
    # The saturation budget - "yaw command ~ Kp * MaximumRate.Yaw, keep it
    # under ~0.5 or yaw STEALS THRUST" - is currently enforced by arithmetic
    # and verified by crashing. This makes it a measurement. 200ms is ample
    # for sustained saturation, which is the failure mode that matters (a
    # corner turn lasts seconds); the autotune profile uses 50ms because it
    # is detecting a relay square wave, which is a different question.
    ("ActuatorDesired", "periodic", 200),

    # Is the flight controller itself starving? CPU load, stack remaining,
    # IRQ stack, event-system errors. We have repeatedly guessed at this
    # (the outerloop startup gap, the marker-publishing thread starvation)
    # and never once measured it. 2s costs ~1% of the log.
    ("SystemStats", "periodic", 2000),

    # NeutralThrustOffset - the hover-thrust baseline the altitude loop
    # self-tunes. Drift here shows up as altitude error with no obvious
    # cause in the vertical PIDs.
    ("VtolSelfTuningStats", "periodic", 2000),

    # The INPUT side, at 1s. Everything else here records what the FC did;
    # this records what it was TOLD. Three consecutive runs were once lost to
    # a second UAVTalk client stealing the bridge's packets, and the signature
    # was invisible in the flight logs precisely because the commanded input
    # was not among them - it read as a control bug. A gap or a frozen value
    # here separates "the harness never said it" from "the FC ignored it".
    ("ManualControlCommand", "periodic", 1000),

    # Mag at 1s. A 90 deg yaw frame error (spawn attitude used as a world
    # reference) once caused gain-independent lateral spiral divergence, and
    # yaw rotates the NE->body mapping for every horizontal correction, so
    # the field the FC believes in is worth recording cheaply.
    ("MagState", "periodic", 1000),
]

# Opt-in via NINJAPILOT_DEEP_LOG=1. Closes the control cascade at the rate
# loop: position -> velocity -> attitude -> RATE -> actuator. Kept OUT of the
# default profile because the pair costs ~16% of the log bandwidth and only
# earns it when the question is specifically about the inner loop - yaw
# hunting, attitude oscillation, tumbles. RateDesired alone is half a
# picture, so GyroState (the actual rate) comes with it or not at all.
FC_LOG_OBJECTS_DEEP = [
    ("RateDesired", "periodic", 200),
    ("GyroState", "periodic", 200),
    ("AccelState", "periodic", 200),
]

FC_LOG_OBJECTS_AUTOTUNE = [
    ("ActuatorDesired", "periodic", 50),
    ("AttitudeState", "periodic", 50),
    ("RelayTuning", "periodic", 500),
]

FC_LOG_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "logs")


def _set_logging_metadata(client, name, mode, period_ms, timeout=5.0):
    """Read-modify-write one object's UAVObjMetadata over UAVTalk: set the
    logging update mode bits and loggingUpdatePeriod, preserve everything
    else. Returns True on success."""
    objdef = client.db[name]
    meta_id = objdef.obj_id + 1
    client.meta_payloads.pop(meta_id, None)
    deadline = time.time() + timeout
    payload = None
    while time.time() < deadline:
        client.send_raw(uavtalk.TYPE_OBJ_REQ, meta_id)
        time.sleep(0.15)
        payload = client.meta_payloads.get(meta_id)
        if payload is not None and len(payload) >= _META_STRUCT.size:
            break
    if payload is None or len(payload) < _META_STRUCT.size:
        print(f"[fclog] WARN: no metadata reply for {name} - skipping", flush=True)
        return False
    flags, tel_p, gcs_p, _ = _META_STRUCT.unpack(payload[:_META_STRUCT.size])
    flags = (flags & ~(0x3 << _UAVOBJ_LOGGING_SHIFT)) | (_LOGMODE[mode] << _UAVOBJ_LOGGING_SHIFT)
    client.send_raw(uavtalk.TYPE_OBJ, meta_id, 0,
                    _META_STRUCT.pack(flags, tel_p, gcs_p, period_ms & 0xFFFF))
    return True


def setup_fc_logging(client, extra=()):
    """Enable OnlyWhenArmed on-board logging and mark the FC_LOG_OBJECTS for
    flight-side logging. Runs from the test thread (the client pump must be
    live in parallel for the metadata read-backs)."""
    ok = 0
    for name, mode, period in list(FC_LOG_OBJECTS) + list(extra):
        if _set_logging_metadata(client, name, mode, period):
            ok += 1
        time.sleep(0.05)
    client.send_object("DebugLogSettings",
                       bov.resolve_enum_values(client.db["DebugLogSettings"],
                                               {"LoggingEnabled": "OnlyWhenArmed"}))
    print(f"[fclog] on-board logging enabled (OnlyWhenArmed), "
          f"{ok}/{len(FC_LOG_OBJECTS) + len(extra)} objects marked for logging")


def _retrieve_log_entry(client, flight, entry, timeout=4.0):
    """Ask the flight side to load slot (flight, entry) into DebugLogEntry and
    pull it. Returns the decoded dict, or None on timeout. Matches on the
    entry's own Flight/Entry fields so a stale DebugLogEntry (from a previous
    slot, or from the Retrieve racing our OBJ_REQ) is never accepted."""
    deadline = time.time() + timeout
    last_send = 0.0
    _last_log_entry[0] = None
    # Retry cadence starts tight and only backs off if the flight side is
    # genuinely slow: at 0.4s unconditional this loop set a floor of ~2
    # minutes to pull a 300-slot flight, most of it spent waiting rather
    # than transferring.
    retry_after = 0.12
    while time.time() < deadline:
        now = time.time()
        if now - last_send > retry_after:
            client.send_object("DebugLogControl",
                               bov.resolve_enum_values(client.db["DebugLogControl"],
                                                       {"Operation": "Retrieve",
                                                        "Flight": flight, "Entry": entry}))
            client.request_object("DebugLogEntry")
            last_send = now
            retry_after = min(retry_after * 1.8, 0.6)
        got = _last_log_entry[0]
        if got is not None and got.get("Flight") == flight and got.get("Entry") == entry:
            return got
        time.sleep(0.005)
    return None


def _decode_log_slot(raw, db):
    """Decode one DebugLogEntry into a list of records. Text slots yield one
    {"kind": "text"} record; UAVObject slots yield one record per packed
    object, each with its own FlightTime timestamp."""
    records = []
    data = bytes(raw["Data"])
    kind = raw["Type"]
    if kind == "Text":
        size = min(raw["Size"], len(data))
        records.append({"kind": "text", "t_us": raw["FlightTime"],
                        "text": data[:size].decode("utf-8", "replace")})
        return records

    def add_object(objid, instid, t_us, payload):
        objdef = db.by_id.get(objid)
        if objdef is None and (objid - 1) in db.by_id:
            parent = db.by_id[objid - 1]
            records.append({"kind": "metadata", "t_us": t_us,
                            "object": parent.name + ".meta", "inst": instid,
                            "data": {"raw": payload.hex()}})
            return True
        if objdef is None or len(payload) < objdef.size:
            return False
        records.append({"kind": "uavobject", "t_us": t_us,
                        "object": objdef.name, "inst": instid,
                        "data": objdef.describe(objdef.unpack(payload))})
        return True

    # First record uses the outer header; follow-ons are packed in the tail.
    size0 = raw["Size"]
    if not add_object(raw["ObjectID"], raw["InstanceID"], raw["FlightTime"], data[:size0]):
        return records
    off = size0
    while off + _LOG_SUBHDR.size <= len(data):
        t_us, objid, _f, _e, instid, size, sub_type = _LOG_SUBHDR.unpack_from(data, off)
        if objid in (0xFFFFFFFF, 0) or sub_type != 2:  # 0xff filler / not UAVObject
            break
        payload = data[off + _LOG_SUBHDR.size: off + _LOG_SUBHDR.size + size]
        if not add_object(objid, instid, t_us, payload):
            break
        off += _LOG_SUBHDR.size + size
    return records


def download_fc_logs(client, max_entries_per_flight=2000):
    """Pull every on-board log flight over telemetry after the flight is
    over, decode, and write JSONL + a human-readable transcript under
    ground/gazebo_bridge/logs/. Returns the list of files written."""
    # Finalize: dropping to Disabled makes Logging.c Printf-then-disable,
    # which flushes any partly-filled buffer into its slot first. (After a
    # disarm under OnlyWhenArmed this is a no-op - already flushed.)
    client.send_object("DebugLogSettings",
                       bov.resolve_enum_values(client.db["DebugLogSettings"],
                                               {"LoggingEnabled": "Disabled"}))
    time.sleep(1.0)

    status = _last_log_status[0]
    if status is None:
        print("[fclog] no DebugLogStatus seen - cannot download", flush=True)
        return []
    top_flight = status["Flight"]
    print(f"[fclog] downloading: DebugLogStatus Flight={top_flight} "
          f"UsedSlots={status['UsedSlots']} FreeSlots={status['FreeSlots']}")

    os.makedirs(FC_LOG_DIR, exist_ok=True)
    stamp = time.strftime("%Y%m%d_%H%M%S")
    written = []
    for flight in range(top_flight + 1):
        slots = []
        for entry in range(max_entries_per_flight):
            got = _retrieve_log_entry(client, flight, entry)
            if got is None:
                print(f"[fclog] flight {flight}: timeout at slot {entry} - stopping this flight", flush=True)
                break
            if got["Type"] == "Empty":
                break
            slots.append(got)
        if not slots:
            continue
        records = []
        for raw in slots:
            for rec in _decode_log_slot(raw, client.db):
                rec["flight"] = flight
                rec["slot"] = raw["Entry"]
                records.append(rec)
        base = os.path.join(FC_LOG_DIR, f"fclog_{stamp}_flight{flight}")
        with open(base + ".jsonl", "w") as f:
            for rec in records:
                f.write(json.dumps(rec) + "\n")
        with open(base + ".txt", "w") as f:
            for rec in records:
                t = rec["t_us"] / 1e6
                if rec["kind"] == "text":
                    f.write(f"t={t:10.3f}s  TEXT  {rec['text']}\n")
                else:
                    vals = rec.get("data", {})
                    f.write(f"t={t:10.3f}s  {rec.get('object', '?'):24s} {vals}\n")
        n_obj = sum(1 for r in records if r["kind"] == "uavobject")
        n_txt = sum(1 for r in records if r["kind"] == "text")
        print(f"[fclog] flight {flight}: {len(slots)} slots -> {len(records)} records "
              f"({n_obj} uavobject, {n_txt} text) -> {base}.jsonl/.txt")
        written.append(base + ".jsonl")
    if not written:
        print("[fclog] no non-empty flights found on board", flush=True)
    return written


def set_yaw_control(client, mode):
    vals = _vtol_pf_values[0]
    if not vals:
        return
    vals = dict(vals)
    vals["YawControl"] = {"manual": 0, "tailin": 1, "movementdirection": 2,
                          "pathdirection": 3, "poi": 4}[mode]
    client.send_object("VtolPathFollowerSettings", vals)
    print(f"[test] YawControl -> {mode}")


_last_relay = [None]   # latest RelayTuning (periodic 1Hz while tuning)
_last_bank1 = [None]   # latest StabilizationSettingsBank1 (pushed on change)
_last_flightstatus = [None]  # latest FlightStatus (mode verification)
_fms_position_override = [None]  # FlightModePosition override (autotune remaps slot 4)


def autotune_test():
    """NINJAPILOT_TEST_MODE=autotune: relay-feedback autotune against the
    real Gazebo physics. Protocol (matches flight/modules/Autotune/
    autotune.c - the ORDER matters):
      1. RelayTuningSettings + map switch position 4 to the Autotune mode.
      2. Arm and climb to a manual-throttle hover (Stabilized1, thrust
         passes through from our virtual stick for the ENTIRE tune).
      3. Flip to Autotune WHILE AIRBORNE with thrust > 0 (AT_INIT refuses
         to start on the ground).
      4. Module runs relay on roll -> pitch -> yaw (20s each) while the
         bridge holds altitude with the proven ground-truth cascade.
      5. Land and DISARM while STILL IN Autotune mode - gains are computed
         and written to Bank1 only on the armed->disarmed edge (AT_SET).
      6. Read back RelayTuning + StabilizationSettingsBank1, print + save."""
    print("[test] autotune_test: waiting 3s for link + config to settle...")
    time.sleep(3.0)
    if not wait_for_attitude_ok():
        return
    client = _mission_client[0]

    client.send_object("RelayTuningSettings",
                       bov.resolve_enum_values(client.db["RelayTuningSettings"],
                                               {"Mode": "Rate", "Behavior": "Compute",
                                                "Amplitude": 0.25, "HysteresisThresh": 5,
                                                "RateGain": 0.3333, "AttitudeGain": 0.2}))
    fms = dict(bov.flight_mode_settings(False, ["Attitude", "Attitude", "Attitude"]))
    fmp = list(fms["FlightModePosition"])
    fmp[4] = "Autotune"
    fms["FlightModePosition"] = fmp
    _fms_position_override[0] = fmp  # keep the arming re-send from stomping it
    # Plain OBJ sends can drop on the UDP link - autotune run 1 flew its
    # whole relay window in PATHPLANNER because this patch never landed.
    # Send it a few times, then VERIFY the mode engages before relying on it.
    for _ in range(3):
        client.send_object("FlightModeSettings",
                           bov.resolve_enum_values(client.db["FlightModeSettings"], fms))
        time.sleep(0.3)

    print("[test] autotune_test: arming, manual-throttle climb to 12m")
    control.mode_position = 0
    control.throttle = 0.0
    control.armed = True
    time.sleep(2.0)

    # Ground-truth altitude cascade (same structure/limits as
    # manual_hover_test - see its comment block for the failure analysis
    # behind the asymmetric limits and the narrow throttle envelope).
    RATE_KP = 0.4
    MAX_CLIMB_MPS = 1.5
    MAX_DESCENT_MPS = 0.8
    THR_PER_MPS = 0.15
    THR_MIN, THR_MAX = 0.45, 0.80
    HOVER = 0.68

    def hold_tick(target_m):
        have, alt, climb = state.pose_alt_climb()
        if not have:
            return None
        want_rate = max(-MAX_DESCENT_MPS, min(MAX_CLIMB_MPS, RATE_KP * (target_m - alt)))
        thr = HOVER + THR_PER_MPS * (want_rate - climb)
        control.throttle = max(THR_MIN, min(THR_MAX, thr))
        return alt

    def abort(reason):
        print(f"[test] autotune_test: FAIL - {reason} - cutting")
        control.mode_position = 0
        control.throttle = 0.0
        control.armed = False

    # climb to hover
    t0 = time.time()
    while time.time() - t0 < 30.0:
        alt = hold_tick(12.0)
        if alt is not None and abs(alt - 12.0) < 0.6:
            break
        time.sleep(0.05)
    else:
        abort("never reached the 12m staging hover")
        return
    print("[test] autotune_test: hover established, engaging Autotune mode")
    control.mode_position = 4  # Autotune (mapped above)
    t0 = time.time()
    while time.time() - t0 < 4.0:
        fs = _last_flightstatus[0]
        if fs and fs.get("FlightMode") == "Autotune":
            break
        hold_tick(12.0)
        time.sleep(0.05)
    else:
        abort(f"flight mode never became Autotune (stuck at "
              f"{(_last_flightstatus[0] or {}).get('FlightMode')}) - check FlightModePosition mapping")
        return
    print("[test] autotune_test: FlightStatus confirms Autotune mode")

    # 2s prepare + 3 x 20s relay axes + margin. Supervise with truth.
    TUNE_TIME = 2.0 + 3 * 20.0 + 6.0
    start = time.time()
    last_report = 0.0
    while time.time() - start < TUNE_TIME:
        alt = hold_tick(12.0)
        have_att, roll, pitch, _, _ = fc_state.snapshot()
        have_pose, pos_ned, _, _, _, _ = state.snapshot()
        if alt is not None and (alt < 1.0 or alt > 30.0):
            abort(f"altitude excursion {alt:.1f}m during relay")
            return
        if have_att and (abs(roll) > 55 or abs(pitch) > 55):
            abort(f"tilt-over roll={roll:.0f} pitch={pitch:.0f} during relay")
            return
        if have_pose and (pos_ned[0] ** 2 + pos_ned[1] ** 2) > 30.0 ** 2:
            abort("drifted >30m from home during relay")
            return
        now = time.time()
        if now - last_report > 5.0:
            last_report = now
            r = _last_relay[0]
            if r:
                print(f"[test] autotune t+{now - start:4.0f}s "
                      f"period(ms) R/P/Y = {r['Period'][0]:.0f}/{r['Period'][1]:.0f}/{r['Period'][2]:.0f} "
                      f"gain = {r['Gain'][0]:.3f}/{r['Gain'][1]:.3f}/{r['Gain'][2]:.3f}", flush=True)
        time.sleep(0.05)

    # Land WITHOUT leaving Autotune mode (AT_FINISHED needs disarm+zero
    # thrust while the mode is still Autotune, or nothing is written).
    print("[test] autotune_test: relay complete - landing in Autotune mode")
    t0 = time.time()
    while time.time() - t0 < 40.0:
        have, alt, _ = state.pose_alt_climb()
        if have and alt < 0.3:
            break
        hold_tick(0.0)
        time.sleep(0.05)
    control.throttle = 0.0
    time.sleep(1.0)
    control.armed = False
    print("[test] autotune_test: disarmed in Autotune mode - waiting for AT_SET")
    time.sleep(3.0)

    # Harvest: Bank1 is pushed on change (acked settings object); also
    # request it explicitly in case the push raced the disarm.
    client.request_object("StabilizationSettingsBank1")
    time.sleep(1.5)
    relay = _last_relay[0]
    bank = _last_bank1[0]
    print("[test] ===== AUTOTUNE RESULTS =====")
    if relay:
        for i, ax in enumerate(("Roll", "Pitch", "Yaw")):
            wu = 2 * math.pi * 1000.0 / relay["Period"][i] if relay["Period"][i] > 1 else 0.0
            print(f"[test]  {ax:5s}: period {relay['Period'][i]:7.1f} ms  gain {relay['Gain'][i]:7.3f}  wu {wu:5.1f} rad/s")
    if bank:
        for ax in ("Roll", "Pitch", "Yaw"):
            print(f"[test]  {ax}RatePID = {bank[ax + 'RatePID']}  {ax}PI = {bank[ax + 'PI']}")
        out = os.path.join(FC_LOG_DIR, time.strftime("autotune_%Y%m%d_%H%M%S.json"))
        os.makedirs(FC_LOG_DIR, exist_ok=True)
        with open(out, "w") as f:
            json.dump({"relay": relay, "bank1": bank}, f, indent=2)
        print(f"[test] autotune_test: results saved -> {out}")
    else:
        print("[test] autotune_test: WARNING - no Bank1 push seen; gains may not have been written")
    print("[test] autotune_test: PASS - tune complete")


def run_post_flight_analysis():
    """Compare ALL THREE logs at the end of every run, automatically.

    A run judged on the bridge log alone cannot tell a controller problem
    from an estimator problem from a physics/plugin problem - and each of
    those has been misdiagnosed as another during this project. So this is
    not left to whoever is driving: the board log is decoded from the
    firmware's own flash, scored against the plan, and cross-checked
    against bridge ground truth and the Gazebo server log, as the flight
    ends.
    """
    import subprocess
    here = os.path.dirname(os.path.abspath(__file__))
    script = os.path.join(here, "tools", "analyze_run.sh")
    if not os.path.exists(script):
        print("[analyze] tools/analyze_run.sh missing - skipping")
        return
    label = os.environ.get("NINJAPILOT_RUN_LABEL", "run")
    bridge_log = os.environ.get("NINJAPILOT_BRIDGE_LOG", "")
    if not bridge_log:
        print("[analyze] set NINJAPILOT_BRIDGE_LOG=<this run's log> for the full comparison;"
              " running board-log analysis only")
        bridge_log = "/dev/null"
    try:
        out = subprocess.run([script, label, bridge_log], capture_output=True,
                             text=True, timeout=180)
        print(out.stdout)
        if out.stderr.strip():
            print(out.stderr.strip())
    except Exception as exc:
        print("[analyze] failed (%s)" % exc)


def pull_logs_only():
    """NINJAPILOT_TEST_MODE=pull_logs: no flying - just download whatever the
    on-board log currently holds (useful after a crash or a manual run)."""
    print("[test] pull_logs: waiting 3s for link + config to settle...")
    time.sleep(3.0)
    download_fc_logs(_mission_client[0])


# --- Translucent flight-path trails via Gazebo's Marker API ------------------
# gz-sim's GUI runs a MarkerManager listening on the /marker service:
# LINE_STRIP markers with an RGBA material render as persistent translucent
# polylines in the 3D scene. Two markers: id=1 the PLANNED path (amber),
# id=2 the ACTUAL flown path (cyan), so plan-vs-flight is visible at a
# glance. NED -> Gazebo ENU: x=E, y=N, z=-D.

def _marker_base(marker_id, rgba):
    from gz.msgs10.marker_pb2 import Marker
    m = Marker()
    m.ns = "ninjapilot_trail"
    m.id = marker_id
    m.action = Marker.ADD_MODIFY
    m.type = Marker.LINE_STRIP
    for tgt in (m.material.ambient, m.material.diffuse, m.material.emissive):
        tgt.r, tgt.g, tgt.b, tgt.a = rgba
    return m


def _marker_send(node, m):
    # NOTE: the /marker service acknowledges with gz.msgs.Empty and the call
    # frequently reports ok=False even though the marker IS registered
    # (verified via /marker/list) - so the return value is deliberately
    # ignored. The original version asked for a Boolean reply; that mismatch
    # made every call "fail" silently and nobody noticed the trails were
    # missing from the GUI until a user actually looked for them.
    from gz.msgs10.empty_pb2 import Empty
    try:
        # Short timeout: these are cosmetic, and a blocking call here
        # competes with the threads that actually keep the vehicle flying.
        node.request("/marker", m, type(m), Empty, 50)
    except Exception:
        pass  # trail is cosmetic - never let it interfere with flight


def _marker_sphere(marker_id, x, y, z, rgba, diameter=0.5):
    from gz.msgs10.marker_pb2 import Marker
    m = _marker_base(marker_id, rgba)
    m.type = Marker.SPHERE
    m.scale.x = m.scale.y = m.scale.z = diameter
    m.pose.position.x, m.pose.position.y, m.pose.position.z = x, y, z
    return m


# Trail tubes are as wide as the craft (X3 is ~0.45m across) - gz renders
# LINE_STRIP at 1px regardless of scale, which is invisible at scene
# distances (user-confirmed), so every trail segment is a translucent
# CYLINDER instead: "fairly opaque, but still transparent".
TRAIL_DIAMETER = 0.22


def _marker_tube(marker_id, a, b, rgba, diameter=TRAIL_DIAMETER):
    """A cylinder marker spanning points a->b (gz cylinders are axis-Z, so
    rotate +Z onto the segment direction)."""
    from gz.msgs10.marker_pb2 import Marker
    dx, dy, dz = b[0] - a[0], b[1] - a[1], b[2] - a[2]
    length = math.sqrt(dx * dx + dy * dy + dz * dz)
    m = _marker_base(marker_id, rgba)
    m.type = Marker.CYLINDER
    m.scale.x = m.scale.y = diameter
    m.scale.z = max(length, 0.01)
    m.pose.position.x = (a[0] + b[0]) / 2.0
    m.pose.position.y = (a[1] + b[1]) / 2.0
    m.pose.position.z = (a[2] + b[2]) / 2.0
    if length > 1e-6:
        ux, uy, uz = dx / length, dy / length, dz / length
        if uz > 0.99999:
            q = (1.0, 0.0, 0.0, 0.0)
        elif uz < -0.99999:
            q = (0.0, 1.0, 0.0, 0.0)
        else:
            # axis = normalize(z cross u), angle = acos(z dot u)
            ax, ay = -uy, ux
            n = math.sqrt(ax * ax + ay * ay)
            ax, ay = ax / n, ay / n
            half = math.acos(uz) / 2.0
            s = math.sin(half)
            q = (math.cos(half), ax * s, ay * s, 0.0)
        m.pose.orientation.w, m.pose.orientation.x, m.pose.orientation.y, m.pose.orientation.z = q
    return m


def _marker_clear(node):
    """Delete every marker in our namespace (stale trails from the previous
    mission would otherwise stack up in the scene)."""
    from gz.msgs10.marker_pb2 import Marker
    m = Marker()
    m.ns = "ninjapilot_trail"
    m.action = Marker.DELETE_ALL
    _marker_send(node, m)


def publish_planned_trail(node, wps):
    # Amber tube per leg + a translucent sphere at each waypoint.
    _marker_clear(node)
    pts = [(w["Position"][1], w["Position"][0], -w["Position"][2]) for w in wps]
    for i in range(len(pts) - 1):
        _marker_send(node, _marker_tube(1000 + i, pts[i], pts[i + 1],
                                        (1.0, 0.7, 0.0, 0.28)))
    for i, p in enumerate(pts):
        _marker_send(node, _marker_sphere(100 + i, p[0], p[1], p[2],
                                          (1.0, 0.6, 0.0, 0.3), 0.35))


def gui_follow(node, model=GAZEBO_MODEL, offset=(-14.0, -14.0, 9.0)):
    """Make the Gazebo GUI camera follow the vehicle (same as right-click ->
    Follow) so nobody has to re-click it every run. Idempotent; errors are
    cosmetic and ignored.

    OFF by request when NINJAPILOT_GUI_FOLLOW=0. While follow is active,
    gz-rendering eases the camera toward target+offset EVERY frame, so it
    overwrites manual pan/zoom on the next frame - the camera appears to snap
    back to the chase view as soon as you scroll out. Continuous follow and
    free manual zoom are the same control, so this has to be a choice; the
    chase cam is still one right-click away when it is off."""
    if os.environ.get("NINJAPILOT_GUI_FOLLOW", "1") == "0":
        print("[gui] camera follow disabled (NINJAPILOT_GUI_FOLLOW=0) - "
              "pan/zoom freely, right-click the vehicle -> Follow to chase")
        return
    from gz.msgs10.stringmsg_pb2 import StringMsg
    from gz.msgs10.boolean_pb2 import Boolean
    from gz.msgs10.vector3d_pb2 import Vector3d
    try:
        s = StringMsg()
        s.data = model
        node.request("/gui/follow", s, StringMsg, Boolean, 1000)
        off = Vector3d()
        off.x, off.y, off.z = offset
        node.request("/gui/follow/offset", off, Vector3d, Boolean, 1000)
        print(f"[gui] camera following '{model}' offset={offset}")
    except Exception:
        pass


class FlownTrail(object):
    """Extends a cyan craft-width tube behind the vehicle: one cylinder
    segment per ~1m of travel, appended incrementally (never re-sends the
    whole trail)."""

    SEG_MIN_M = 0.5

    def __init__(self, node):
        self.node = node
        self.last = 0.0
        self._seg_id = 2000
        self._last_pt = None

    def tick(self):
        now = time.time()
        if now - self.last < 0.25:
            return
        self.last = now
        have_pose, pos_ned, _, _, _, _ = state.snapshot()
        if not have_pose:
            return
        pt = (pos_ned[1], pos_ned[0], -pos_ned[2])
        if self._last_pt is None:
            self._last_pt = pt
            return
        a = self._last_pt
        if (pt[0] - a[0]) ** 2 + (pt[1] - a[1]) ** 2 + (pt[2] - a[2]) ** 2 < self.SEG_MIN_M ** 2:
            return
        _marker_send(self.node, _marker_tube(self._seg_id, a, pt,
                                             (0.1, 0.9, 1.0, 0.33)))
        self._seg_id += 1
        self._last_pt = pt


def upload_mission(client):
    """Send PathActions + Waypoints as multi-instance objects (firmware
    auto-creates instances on unpack), then PathPlan with counts + the
    CRC pathplanner.c will recompute. Returns the (waypoints, actions)
    lists. Validation is confirmed by the flight side itself: the
    PathPlan alarm goes OK only when checkPathPlan() passes."""
    wps, actions = build_mission()
    db = client.db
    wp_def = db["Waypoint"]
    act_def = db["PathAction"]

    crc = 0
    for i, w in enumerate(wps):
        resolved = bov.resolve_enum_values(wp_def, w)
        client.send_object("Waypoint", resolved, inst_id=i)
        time.sleep(0.02)
        client.send_object("Waypoint", resolved, inst_id=i)  # cheap loss hedge
        time.sleep(0.02)
        crc = _crc8_07(crc, wp_def.pack(resolved))
    for i, a in enumerate(actions):
        resolved = bov.resolve_enum_values(act_def, a)
        client.send_object("PathAction", resolved, inst_id=i)
        time.sleep(0.02)
        client.send_object("PathAction", resolved, inst_id=i)
        time.sleep(0.02)
        crc = _crc8_07(crc, act_def.pack(resolved))

    plan = {"WaypointCount": len(wps), "PathActionCount": len(actions), "Crc": crc}
    client.send_object("PathPlan", plan)
    time.sleep(0.05)
    client.send_object("PathPlan", plan)
    print(f"[test] mission uploaded: {len(wps)} waypoints, {len(actions)} actions, crc={crc}")
    return wps, actions


def wait_for_pathplan_ok(timeout=15.0):
    """PathPlan alarm OK == the FLIGHT side validated instance counts and
    recomputed the same CRC - the authoritative 'mission accepted'."""
    idx = ALARM_NAMES.index("PathPlan")
    deadline = time.time() + timeout
    while time.time() < deadline:
        alarms = _last_alarms[0]
        if alarms is not None and alarms[idx] == "OK":
            print("[test] flight side validated the path plan (PathPlan alarm OK)")
            return True
        time.sleep(0.25)
    alarms = _last_alarms[0]
    print(f"[test] ERROR: path plan not accepted "
          f"(PathPlan alarm: {alarms[idx] if alarms else 'never reported'})")
    return False


def mission_test():
    """NINJAPILOT_TEST_MODE=mission: upload the star/octagon/KF/land plan,
    arm, climb to a staging hover, hand the vehicle to PathPlanner, and
    supervise against ground truth until the Land action puts it on the
    floor. Aborts land() on ceiling breach, crash, or stalled progress."""
    print("[test] mission_test: waiting for link + config to settle...")
    time.sleep(1.0)  # config burst only needs to land; the estimator gate below is the real wait
    if not wait_for_attitude_ok():
        return
    client = _mission_client[0]
    wps, _ = upload_mission(client)
    if not wait_for_pathplan_ok():
        return
    last_idx = len(wps) - 1

    # Translucent trails in the Gazebo scene: planned path (amber) now,
    # flown path (cyan) appended live during the flight. Camera follows the
    # vehicle so the user never has to right-click -> Follow manually.
    trail_node = transport.Node()
    subscribe_gps_noise(trail_node)
    # Arc-centre waypoints are control points, not places the vehicle goes -
    # drawing lines through them would show a jagged phantom path.
    publish_planned_trail(trail_node, [w for w in wps if not w.get("_arc")])
    gui_follow(trail_node)
    flown = FlownTrail(trail_node)

    print("[test] mission_test: arming")
    control.mode_position = 0
    control.throttle = 0.0
    control.armed = True
    time.sleep(0.6)  # just long enough for the arm to be acked and applied
    if not vario_climb_and_hold(4.0, 1, "mission staging hover (Stabilized2)", 1.5):
        print("[test] mission_test: FAIL - staging climb failed")
        return
    ok, _ = _wait_for_vertical_settle("PathPlanner engage")
    if not ok:
        return

    # Engage PositionHold FIRST: its activation path (pathfollowerhandler ->
    # plan_setup_positionHold -> controller Activate()) is proven solid by
    # the dedicated poshold test. Switching to PathPlanner from a stable,
    # already-activated PathFollower means the mode change only swaps the
    # PathDesired source. Engaging PathPlanner straight from Stabilized2
    # left the vehicle translating toward wp0 while slowly sinking to the
    # ground - consistent with the fly-controller's thrust path not being
    # activated by that direct transition.
    print("[test] mission_test: engaging PositionHold to activate PathFollower...")
    control.mode_position = 3
    # PositionHold only has to ACTIVATE the PathFollower controllers, which
    # happens on the first callback - it does not need to settle here (the
    # vertical settle gate above already ran). 4s of hovering was dead time.
    time.sleep(1.2)
    print(f"[test] mission_test: engaging PathPlanner - {len(wps)} waypoints, "
          f"star@8m -> octagon@18m -> 'KF'@28m -> land")
    control.mode_position = 4  # PathPlanner
    # Yaw faces the flight direction WHILE FLYING LEGS ONLY. pathdirection
    # during a hold is unstable: path_vector there is just the position-
    # error direction, so the yaw target is noise and the vehicle chases it
    # at MaximumRate.Yaw (star 20 fell out of the PositionHold activation
    # phase doing exactly that). Flip it on after PathPlanner engages,
    # revert in the test wrapper when the mission is over.
    time.sleep(0.5)
    # NINJAPILOT_YAW_MODE=manual is the isolation experiment for the left
    # loop at every corner: the lateral drift that seeds the loop builds
    # EXACTLY during the nose sweep (cross-track 0.04 -> 0.67m while yaw
    # slews -54 -> +90 deg), every corner, always leftward - and every star
    # corner turns right, so the nose always sweeps the same way. If the
    # loop vanishes with yaw-following off, the cause is translate-while-
    # yawing coupling, not path geometry.
    # DEFAULT IS "manual" (yaw-following OFF), decided by controlled
    # experiment on 2026-08-09. Identical stop-corner missions:
    #
    #   yaw OFF  (star133)              xtrack 0.06m mean / 0.19m MAX -
    #                                   cleanest run of the project, corners
    #                                   are sharp points, 107s
    #   yaw ON                (star132) 0.19 / 0.78m, +570 deg left mills
    #   yaw ON + 0.13s comp   (star134) 0.17 / 0.50m
    #   yaw ON + 0.26s comp   (star135) 0.14 / 0.45m - better but the drift
    #                                   did NOT flip sign, so the frame-lag
    #                                   model is incomplete and further blind
    #                                   tuning is not justified
    #
    # Yawing the nose while translating measurably corrupts position by
    # ~0.3-0.5m per corner even with predicted-yaw compensation. Until the
    # residual mechanism is identified, nose-following costs 3x the tracking
    # accuracy - set NINJAPILOT_YAW_MODE=pathdirection to accept that trade.
    set_yaw_control(client, os.environ.get("NINJAPILOT_YAW_MODE", "manual"))

    start = time.time()
    last_log = 0.0
    last_progress = time.time()
    last_seen_idx = None
    landed_grace = None
    leg_entry_dist = None
    while True:
        now = time.time()
        flown.tick()
        have_pose, alt, _climb = state.pose_alt_climb()
        have_pose2, pos_ned, _, _, _, _ = state.snapshot()
        n, e = (pos_ned[0], pos_ned[1]) if have_pose2 else (0.0, 0.0)
        idx = _waypoint_active[0]
        if idx != last_seen_idx:
            last_seen_idx = idx
            last_progress = now
            leg_entry_dist = None
        # Flyaway guard (mission 12: a missed acceptance sphere under
        # FollowVector means nothing ever pulls back toward the waypoint -
        # the vehicle sailed the leg line's infinite extension 30+ m until
        # the 90s stall timeout). If we are getting FARTHER from the active
        # waypoint than when the leg began, plus margin, cut immediately.
        if have_pose and have_pose2 and idx is not None and 0 <= idx <= last_idx:
            tgt_p = wps[idx]["Position"]
            # HORIZONTAL distance only. A 3D measure false-alarms on the
            # landing leg: the final waypoint sits at 8m, so simply
            # descending to land grows the 3D distance by construction
            # (observed 0.7m at leg entry -> 8.7m at touchdown, aborting a
            # flight that scored 0.23m mean / 0.89m max). The guard also
            # never arms on the final land waypoint for the same reason.
            dist = math.sqrt((n - tgt_p[0]) ** 2 + (e - tgt_p[1]) ** 2)
            if leg_entry_dist is None:
                leg_entry_dist = dist
            if idx != last_idx and dist > leg_entry_dist + 8.0:
                print(f"[test] mission_test: FAIL - flying AWAY from wp{idx} "
                      f"(dist {dist:.1f}m vs {leg_entry_dist:.1f}m at leg entry) - landing",
                      flush=True)
                land()
                return
        # During the final Land action the waypoint index CANNOT advance -
        # progress there is the descent itself. An earlier version timed
        # out and aborted a perfectly healthy landing at 4m for "no
        # waypoint progress".
        if idx == last_idx and _climb < -0.05:
            last_progress = now
        if alt > 40.0:
            print(f"[test] mission_test: FAIL - ceiling breach alt={alt:.1f}m - landing")
            land()
            return
        have_att, roll, pitch, _, _ = fc_state.snapshot()
        if have_att and (abs(roll) > 60 or abs(pitch) > 60) and alt > 0.5:
            print(f"[test] mission_test: FAIL - tilt-over roll={roll:.0f} pitch={pitch:.0f} - cutting")
            control.throttle = 0.0
            control.armed = False
            return
        if idx is not None and idx != last_idx and alt < 0.25:
            if not hasattr(mission_test, "_grounded_since") or mission_test._grounded_since is None:
                mission_test._grounded_since = now
            elif now - mission_test._grounded_since > 5.0:
                print(f"[test] mission_test: FAIL - unplanned ground contact at wp{idx} - aborting")
                control.throttle = 0.0
                control.armed = False
                return
        else:
            mission_test._grounded_since = None
        if now - last_progress > 90.0:
            print(f"[test] mission_test: FAIL - no waypoint progress for 90s "
                  f"(stuck at index {idx}) - landing")
            land()
            return
        # Success: the final Land-action waypoint is active and the vehicle
        # is genuinely on the floor (ground truth), stably (2s grace).
        if idx == last_idx and alt < 0.25:
            if landed_grace is None:
                landed_grace = now
            elif now - landed_grace > 2.0:
                control.throttle = 0.0
                control.armed = False
                dur = now - start
                print(f"[test] mission_test: PASS - mission complete in {dur:.0f}s, "
                      f"landed at N={n:.2f} E={e:.2f}, disarmed")
                return
        else:
            landed_grace = None
        if now - last_log > 2.0:
            last_log = now
            tgt = wps[idx]["Position"] if (idx is not None and 0 <= idx <= last_idx) else None
            tgt_s = f" -> wp{idx} N={tgt[0]:.1f} E={tgt[1]:.1f} alt={-tgt[2]:.0f}m" if tgt else ""
            print(f"[test] mission_test: t+{now - start:.0f}s alt={alt:.2f}m "
                  f"N={n:.2f} E={e:.2f}{tgt_s}", flush=True)
        # 10Hz. The trail is drawn from this loop, so this sleep caps how
        # fluid the flown line can be - but do NOT push it to 20Hz: with
        # marker sends being blocking gz requests, that starved the thread
        # feeding sensors to the firmware and the vehicle hit the ground.
        time.sleep(0.1)


def manual_hover_test():
    """Foundation-block sanity check, deliberately independent of the flight
    controller's own state estimator/hold-mode logic: arm in raw-manual-
    throttle mode (Stabilization1Settings = Attitude/Attitude/AxisLock/
    Manual, control.mode_position=0 - self-leveling only, no altitude
    logic in the flight code at all), then run a simple P+I controller
    HERE, in Python, using Gazebo's own ground-truth pose (state.snapshot())
    as feedback - never PositionState/VelocityState - to climb to and hold
    10m, then 20m.

    This exists because run_test_sequence()'s AltitudeVario/AltitudeHold-
    based climbs all crash the same way regardless of which of the 4
    vertical-channel estimator algorithms is running (see the V1-V4
    comparison), and filteraltitude.c's own altitudeState was independently
    confirmed to sit near 0 while ground truth climbed well past it - i.e.
    the estimator, not the vehicle/physics/motor pipeline, is suspect. If
    this manual/ground-truth-driven hover ALSO can't hold height, the bug is
    in thrust/physics, not the estimator, and every hour spent on filter
    algorithms this session was pointed at the wrong layer. If it CAN hold
    height cleanly, that's confirmed and isolated: the actuator/physics
    chain is sound, and 100% of the remaining problem is state estimation."""
    print("[test] manual_hover_test: waiting 3s for link + config to settle...")
    time.sleep(3.0)

    # Same arming gate as run_test_sequence - see wait_for_attitude_ok's
    # docstring. Manual thrust mode doesn't need the estimator to FLY,
    # but outerloop.c (which forwards even Manual thrust into RateDesired)
    # is AttitudeState-event-driven and never runs while filtercf.c is
    # calibrating - throttle is dead until this gate opens.
    if not wait_for_attitude_ok():
        return

    print("[test] manual_hover_test: arming (raw manual throttle, no hold mode)")
    control.mode_position = 0  # Stabilization1Settings = Attitude/Attitude/AxisLock/Manual
    control.throttle = 0.0
    control.armed = True
    time.sleep(2.0)

    # Safety net independent of RUNAWAY_ALTITUDE_M (that 8m ceiling is
    # calibrated for the scripted test's much lower targets - it would
    # immediately misfire against a deliberate 10m/20m target here).
    HARD_CEILING_M = 25.0

    # Cascaded altitude controller - the standard structure, replacing an
    # earlier flat P+I+D that was confirmed unstable in a real run (bang-
    # bang throttle between its cap and mid-range, one deep descent
    # excursion it could not arrest because the same cap that limited
    # climb also limited RECOVERY authority - the vehicle hit the ground
    # at 3.8 m/s with throttle pinned at the cap, bounced, tilted, and
    # flipped). Outer loop: altitude error -> desired climb rate,
    # asymmetric limits (climb gently, never command a fast descent).
    # Inner loop: climb-rate error -> throttle about hover. Naturally
    # damped (rate feedback IS the damping), no integrator to wind up,
    # and full 0.90 authority available whenever arresting a descent.
    RATE_KP        = 0.4    # (m/s) desired per meter of altitude error
    MAX_CLIMB_MPS  = 1.5
    MAX_DESCENT_MPS = 0.8
    THR_PER_MPS    = 0.15   # throttle per (m/s) of climb-rate error
    # Throttle envelope [0.45, 0.80], deliberately narrow around hover
    # (0.68): at 0.90 collective the mixer has almost no differential
    # headroom left for roll/pitch torque - confirmed live, every violent
    # excursion in the previous run coincided with a 0.90-throttle
    # command, ending in a 70-degree pitch-over the firmware SAW (its own
    # AttitudeState reported it) but physically could not correct.
    # Attitude authority beats vertical tracking speed, always.
    THR_MIN = 0.45
    THR_MAX = 0.80

    def hold_altitude(target_m, hold_seconds, label, climb_timeout=30.0):
        """Climb to target_m, then hold for hold_seconds. FAILS (returns
        False, cuts throttle, disarms) on: hard ceiling, a crash/tilt-over
        (flight controller's own attitude - a flipped vehicle 'holding'
        0m forever was scored as a pass by an earlier version of this
        test), or not reaching the target within climb_timeout (a
        vacuous timeout is a FAIL, not a hold)."""
        start = time.time()
        reached_at = None
        print(f"[test] manual_hover_test: climbing to {target_m:.0f}m via cascaded rate controller "
              f"(ground-truth feedback only)...")
        last_log = 0.0
        while True:
            now = time.time()
            have_pose, alt, climb_rate = state.pose_alt_climb()
            if not have_pose:
                alt = climb_rate = 0.0
            if alt > HARD_CEILING_M:
                print(f"[test] manual_hover_test: FAIL - hard ceiling {HARD_CEILING_M:.0f}m exceeded "
                      f"(alt={alt:.2f}m) - cutting throttle and disarming")
                control.throttle = 0.0
                control.armed = False
                return False
            have_att, roll, pitch, _, _ = fc_state.snapshot()
            if have_att and (abs(roll) > 60.0 or abs(pitch) > 60.0):
                print(f"[test] manual_hover_test: FAIL - tilt-over roll={roll:.1f} pitch={pitch:.1f} "
                      f"at alt={alt:.2f}m - cutting throttle and disarming")
                control.throttle = 0.0
                control.armed = False
                return False
            if reached_at is None:
                if abs(target_m - alt) < 1.0:
                    reached_at = now
                    print(f"[test] manual_hover_test: {label} reached {alt:.2f}m - holding {hold_seconds:.0f}s")
                elif now - start > climb_timeout:
                    print(f"[test] manual_hover_test: FAIL - never reached {target_m:.0f}m within "
                          f"{climb_timeout:.0f}s (alt={alt:.2f}m) - cutting throttle and disarming")
                    control.throttle = 0.0
                    control.armed = False
                    return False
            elif now - reached_at >= hold_seconds:
                print(f"[test] manual_hover_test: {label} hold complete (alt={alt:.2f}m)")
                return True

            desired_rate = max(-MAX_DESCENT_MPS, min(MAX_CLIMB_MPS, RATE_KP * (target_m - alt)))
            control.throttle = max(THR_MIN, min(THR_MAX, HOVER_THRUST + THR_PER_MPS * (desired_rate - climb_rate)))
            if now - last_log > 1.0:
                last_log = now
                print(f"[test] manual_hover_test: {label} alt={alt:.3f}m target={target_m:.1f}m "
                      f"climb_rate={climb_rate:.3f} desired_rate={desired_rate:.3f} "
                      f"throttle={control.throttle:.3f}", flush=True)
            # 20Hz - every 100ms of pure loop latency was measurable phase
            # lag in the earlier oscillating versions of this controller.
            time.sleep(0.05)

    if not hold_altitude(10.0, 45.0, "10m hover"):
        return
    if not hold_altitude(20.0, 45.0, "20m hover"):
        return

    print("[test] manual_hover_test: both holds completed - landing")
    land()
    print("[test] manual_hover_test: sequence done")


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
        # HomeLocation.Be must be the Earth's field in the WORLD NED frame,
        # NOT the body-frame reading at spawn. The old measured-at-spawn
        # approach assumed "body FRD == world NED at spawn since the model
        # has no initial rotation" - but Gazebo's world frame is ENU, where
        # a zero-rotation spawn faces +X = EAST. Measuring Be through the
        # body frame therefore DEFINED the spawn heading (east!) as yaw=0,
        # while the GPS/NED position frame uses true north - a standing
        # ~90deg yaw frame error, invisible to attitude leveling and both
        # baro-hold modes (yaw-agnostic), but fatal to PathFollower: every
        # NED position/velocity correction got rotated ~90deg before
        # becoming a roll/pitch command, pushing orthogonal to the error -
        # measured as a gain-independent lateral spiral divergence
        # (commanded amplitude ~tripling per cycle) in three consecutive
        # PositionHold tests across three different gain sets.
        #
        # Correct reference: the world SDF's <magnetic_field> vector
        # (ENU x=E,y=N,z=U) converted to NED, scaled into the magnetometer
        # plugin's own units via the measured field MAGNITUDE (direction
        # from the world truth, scale from the sensor - keeps
        # filtermag.c's magnitude-validity checks consistent with what the
        # plugin actually reports).
        WORLD_MAG_ENU_T = (0.0000004, 0.000026, -0.00004)  # quadcopter_ninjapilot.sdf
        world_ned_t = (WORLD_MAG_ENU_T[1], WORLD_MAG_ENU_T[0], -WORLD_MAG_ENU_T[2])
        world_mag_norm = math.sqrt(sum(v * v for v in world_ned_t))
        for _ in range(20):  # up to 2s
            have_mag, mag_body = state.mag_snapshot()
            if have_mag:
                meas_norm = math.sqrt(sum(v * v for v in mag_body))
                scale = meas_norm / world_mag_norm
                home["Be"] = [v * scale for v in world_ned_t]
                print(f"[test] HomeLocation.Be set from WORLD field (NED, plugin units): "
                      f"{home['Be'][0]:.4f} {home['Be'][1]:.4f} {home['Be'][2]:.4f}", flush=True)
                break
            time.sleep(0.1)
        send_reliable("RevoSettings", bov.resolve_enum_values(db["RevoSettings"], bov.REVOSETTINGS_DEFAULTS))
        time.sleep(0.2)
        send_reliable("HomeLocation", bov.resolve_enum_values(db["HomeLocation"], home))
        time.sleep(0.2)
        send_reliable("MixerSettings", bov.resolve_enum_values(db["MixerSettings"], bov.mixer_settings()))
        time.sleep(0.2)
        # STOCK values, deliberately. An earlier session set
        # AccelDriftKi=0.05 (100x the stock 0.0005) chasing a runaway that
        # was ACTUALLY caused by the transport layer feeding the estimator
        # seconds-stale sensor data (UDP RX starvation + a com-layer
        # chunked-read bug killing ~99% of AccelSensor packets - both
        # since fixed at the root). With clean 500Hz sensors, 0.05/sample
        # is catastrophic: the bias tracker absorbs any REAL sustained
        # acceleration within ~56ms, zeroing correctedAccel and blinding
        # the filter's velocity fast-path exactly when it matters -
        # measured: velocityState read 0.2 m/s during a real 3 m/s climb,
        # so AltitudeVario's rate PID pinned thrust at max and ran away.
        # The stock slow rate is slow BY DESIGN: real accel bias drifts
        # over minutes, and everything faster than that is real motion the
        # integrator needs to see.
        send_reliable("AltitudeFilterSettings", {
            "AccelLowPassKp": 0.04, "AccelDriftKi": 0.0005,
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
            "FlightModeNumber": 5, "FailsafeFlightModeSwitchPosition": -1,
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
            "HorizontalVelMax": 3.0, "VerticalVelMax": 1.5,
            # CourseFeedForward 1.0 -> 0.25 s. The follower does not hand
            # path_progress the vehicle's position - it hands it
            # position + velocity*CourseFeedForward, a lead term meant to damp
            # line following. At 1.0s and a 1.0 m/s leg that lead is a whole
            # METRE, which is the entire length of the final approach, so on
            # the way into a waypoint the PREDICTED point crosses the target
            # while the vehicle is still a metre short. fractional_progress
            # goes past 1, path_vector falls through to endpoint homing from
            # the far side, and the commanded velocity reverses. The vehicle
            # slows, the lead shrinks with it, the prediction falls short
            # again, and it accelerates - a self-sustaining cycle, measured at
            # wp3 in star95 as 0.99m -> 0.32m -> 0.67m -> 0.94m over 5s.
            #
            # Shortening the lead to 0.25s (star96) is the WRONG fix: the lead
            # is also what brakes the vehicle for the waypoint at all, and
            # without it every corner overshot by 0.95m and the mission took
            # 286s. The lead stays at 1.0s and vtolflycontroller clamps it to
            # half the remaining distance instead, so it cannot predict past
            # the target.
            #
            # Settled at 0.4s. The lead only has to damp line-following now;
            # it is no longer doing the braking, because PATH_LEG_DECEL brakes
            # from 1.43m out instead of 0.63m. Keeping it small is what stops
            # v*kFF from ever approaching the remaining distance, which is the
            # condition that lets progress run past the endpoint and start the
            # oscillation.
            "CourseFeedForward": 1.0,
            # HorizontalPosP 0.25->0.15 and HorizontalVelPID P 8->4, D 1->0:
            # measured divergent oscillation in PositionHold (commanded
            # roll/pitch amplitude tripling per cycle, 0.04->5.4deg in ~8s,
            # ending in an accelerating lateral flyaway at ~4.6 m/s). The
            # horizontal cascade's feedback is a 10Hz GPS staircase
            # (VelocityState horizontal passes raw GPS velocity through on
            # this fusion chain) - a D-term on a staircase produces a kick
            # at every step, and P=8deg/(m/s) against 100ms-stale velocity
            # is exactly the delayed-feedback instability the manual hover
            # test hit vertically with navsat-derived rate. Softer gains
            # trade response speed for stability against that latency.
            # (That 0.15 was tuned BEFORE the 90-degree yaw frame error was
            # found - the "oscillation" it was softening was actually the
            # rotated-correction spiral. Post-fix, hold is solid at 0.01m.)
            # HorizontalPosP 0.15->0.35 for FollowVector missions: there the
            # correction_vector is pure cross-track error, and 0.15 (a ~7s
            # correction time constant) let the vehicle sag meters off the
            # line in corners before pulling back.
            # 0.35, and 0.60 was tried and is worse (star112). It bought 0.01m
            # of cross-track (0.15 -> 0.14m) and cost everything else: mission
            # 98s -> 119s, mean overshoot 0.00 -> 0.15m, command reversals per
            # corner 9 -> 24, roll RMS 1.15 -> 2.34 deg. Cross-track is a
            # perpendicular error so a stiffer line-hold looked free, but the
            # correction vector rotates as the vehicle passes a waypoint, and
            # near the point a high gain on it fights the arrival instead of
            # the line.
            "HorizontalPosP": 0.35, "VerticalPosP": 0.25,
            # VerticalVelPID Kp 0.3->0.6, Ki 0.15->0.45: measured in a real
            # PositionHold sag (truth 2.4m -> ground in ~10s), the vertical
            # velocity PID's output hovered at ~0.69 against a true hover
            # point of ~0.70 (confirmed by the manual ground-truth hover
            # test holding steady at 0.70) - a standing few-percent thrust
            # deficit that Ki=0.15 needed ~7-10s to integrate away, longer
            # than the vehicle took to reach the floor. Double P for
            # authority against velocity error, triple Ki so a standing
            # deficit is closed in ~2s, not ~10.
            # Kp 4.0 is a measured ceiling, not a leftover workaround: 6.5 was
            # re-tested after the yaw frame error and yaw saturation were
            # both fixed (i.e. against a clean airframe) and it still
            # tumbled the vehicle into the ground at wp6 - roll p2p 192deg.
            # Do not raise it without changing something else first.
            # Ki stays 0.5. Zeroing it (star107) was a clean test of integrator
            # windup as the cause of the velocity loop overrunning its command,
            # and it is NOT the cause: commanded still peaked at 1.51 m/s on a
            # 1.0 cruise and actual at 2.25, essentially unchanged.
            # Kp 4.0 -> 7.0 and Kd 0.0 -> 0.9.
            #
            # The loop was not short of AUTHORITY, it was short of GAIN. In
            # the braking zone (within 3m of a waypoint) the follower was
            # commanding a median tilt of 3.4 deg and a maximum of 9.0 deg
            # against a 25 deg limit - not one sample within 15 deg of the
            # limit, on runs where the vehicle was overshooting waypoints by
            # up to 0.8m. It had ~2.7x the braking authority it was asking
            # for, so it arrived carrying speed the path never commanded, sailed
            # through the point and got pulled back. That is the orbit.
            #
            # Kp alone cannot be raised: 6.5 tumbled the vehicle outright
            # (roll peak-to-peak 192 deg). That is the signature of a P-only
            # loop pushed past its stability margin, and Kd is exactly 0 here -
            # so the fix is to add the damping first and then take the gain.
            # ILimit stays 15; windup was tested and ruled out (star107, Ki=0
            # changed nothing).
            #
            # Kd 0.9 -> 1.4 with the cruise raised to 1.5 m/s. At the higher
            # leg speed the same loop works harder to hold the line - pitch
            # RMS went 2.34 -> 4.34 deg and cross-track 0.09 -> 0.17m (star110)
            # - which is the loop running closer to its margin, exactly what
            # more derivative is for.
            #
            # Kp 7.0, restored. It was reduced to 5.5 on the strength of a
            # star113 "tumble" - roll peak-to-peak 170deg - that NEVER HAPPENED:
            # that reading came from 1045 timestamp-outlier records, and with
            # them filtered the run's real attitude was roll p2p 7.0deg and
            # pitch 19.7deg, i.e. ordinary flight. star113 was the same
            # unexplained wp3 flyaway that later recurred at Kp 5.5 (star123),
            # so it is not gain-related at all.
            #
            # The reason to want 7.0 back is measured: at 5.5 the vehicle
            # arrives at 0.2m from the waypoint still doing 0.5 m/s against a
            # 0.17 m/s commanded profile, overshoots to 0.35m, is pulled back,
            # and takes 10-14s to settle - which is BOTH the visible loop at
            # every corner and 49-72%% of the mission's total time. The
            # tracking error is loop-lag x ramp-slope, and the lead term is
            # already commanding ~0; what is missing is braking authority.
            # (Note the codebase's own dedicated brake controller runs Kp 12.)
            #
            # Tested (star124) and it is NOT the lever: at 7.0 the loop is past
            # its own stability margin - pitch RMS 2.4 -> 6.0 deg, peak-to-peak
            # 41 deg, and overshoot 0.00 -> 0.13m. More gain just oscillates.
            # The settling problem is not solvable by pushing this loop.
            "HorizontalVelPID": [5.5, 0.5, 1.4, 15], "VerticalVelPID": [0.6, 0.45, 0.08, 1.0],
            # ThrustLimits.Neutral is the altitude-hold PID's hover-point
            # baseline (vtolflycontroller.cpp: controlDown.UpdateNeutralThrust
            # uses it directly) - the XML's 0.5 default assumes a much
            # higher-thrust-margin airframe than X3's real ~0.68 thrust-
            # fraction hover point (see the ramp comment below). This is a
            # physical fact about this specific airframe, the same way a
            # real vehicle's actual weight/thrust ratio would be
            # calibrated in, not a tuning choice.
            # Neutral 0.70, not 0.68: the manual ground-truth hover test's
            # converged steady-state hold throttle was 0.70 at both 10m and
            # 20m - that IS this airframe's measured hover point in this
            # sim. Starting the vertical PID 0.02 low costs a slow sink
            # the (previously weak) I-term had to fight.
            "ThrustLimits": [0.2, 0.70, 0.9], "VelocityFeedforward": 2,
            "ThrustControl": "auto", "YawControl": "manual",
            # DISABLED for sim: this real-hardware safety heuristic decides
            # "flyaway" partly from course-vs-velocity direction error, and
            # at a genuinely perfect zero-velocity hover the course angle
            # of a ~0 m/s velocity vector is numerical noise - it false-
            # tripped after ~35s of a flawless hold (lateral_err 0.00m the
            # whole time) and COMMANDED the 2.3 m/s descent-to-ground that
            # looked like a thrust failure (verified: PIDControlDown
            # setpoint ramped 1.6->2.3 m/s down with the vehicle healthy
            # and armed).
            "FlyawayEmergencyFallback": "disabled", "FlyawayEmergencyFallbackTriggerTime": 10.0,
            "EmergencyFallbackAttitude": [0, -20.0], "EmergencyFallbackYawRate": [2.0, 30.0],
            # MaxRollPitch 25 -> 32 deg: tilt IS lateral acceleration
            # (a = g*tan(theta)): 25deg caps accel at ~4.6 m/s^2, 32deg
            # gives ~6.1. NOT higher - at 40 deg the attitude loop
            # OVERSHOT its own limit to 61 deg while braking into the
            # first hairpin and tipped the vehicle over (star 29). The
            # commanded limit must stay inside what the attitude loop can
            # actually track during a hard stop, not just what the
            # airframe can theoretically hold.
            "MaxRollPitch": 25.0, "UpdatePeriod": 50, "BrakeRate": 2.5, "BrakeMaxPitch": 30.0,
            "BrakeHorizontalVelPID": [12.0, 0.0, 0.03, 15], "BrakeVelocityFeedforward": 0,
            "LandVerticalVelPID": [0.35, 3.0, 0.05, 0.9],
        }
        _vtol_pf_values[0] = bov.resolve_enum_values(db["VtolPathFollowerSettings"], vtol_pf)
        send_reliable("VtolPathFollowerSettings", _vtol_pf_values[0])
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
            # AxisLockKp 2.5 -> 1.0: yaw porpoised +/-20deg at a 3.7s period
            # through mission 15 (truth AND AttitudeState agree - the FC saw
            # the oscillation and couldn't damp it). At Kp 2.5 a 20deg
            # heading error demands 50deg/s - exactly the MaximumRate.Yaw
            # cap - and the X3 model's weak rotor-drag yaw torque can't
            # track that, so the axis-lock outer loop limit-cycled against
            # rate saturation. 1.0 keeps demands inside trackable range.
            "AxisLockKp": 1.0, "MaxAxisLock": 30, "MaxAxisLockRate": 2,
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
            "CruiseControlMinThrust": 5, "CruiseControlMaxThrust": 90, "CruiseControlMaxAngle": 40,
            # Tilt-compensated thrust, RE-ENABLED and bounded. Braking into a
            # corner requires tilt, and tilt costs lift (cos of the tilt
            # angle) - that is why widening the corner braking window
            # improved the PATH but doubled altitude error (0.59 -> 1.53m
            # p2p). CruiseControl multiplies thrust by 1/cos(tilt), which is
            # exactly the missing term.
            #   MaxPowerFactor 1.25 covers tilts to ~37 deg, above our 25 deg
            #   MaxRollPitch, so the whole normal envelope is compensated.
            #   MaxAngle 40 is the safety: beyond that the vehicle is not
            #   manoeuvring, it is tumbling, and boosting thrust into a
            #   tumble is what got this disabled in the first place.
            "CruiseControlMaxPowerFactor": 1.25, "CruiseControlPowerTrim": 100.0,
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
            # Sane authority limits for a mission vehicle (were 300/300/175
            # XML defaults - acro territory): 90 deg/s roll/pitch is plenty
            # for waypoint flight and stops the inner loop wrenching the
            # frame. Yaw 90 gives the loop TRACKING HEADROOM above the fly
            # controller's 30 deg/s slewed yaw command - star 24 set the cap
            # EQUAL to the slew rate and the loop rode the saturation
            # boundary (standing ~12deg error at P=2.5 commands exactly the
            # cap), porpoising yaw and chopping the flight path. The slew
            # is what bounds yaw aggressiveness now, not the rate cap. NOTE these only apply because
            # send_config writes StabilizationSettingsBank1 (persistent) -
            # writing the StabilizationBank mirror alone gets stomped on
            # every mode change.
            # MaximumRate.Yaw stays 45. Raised to 90 in star80 to allow a
            # 60deg/s heading slew; the slew itself proved to be the problem
            # (yaw RMS 8.4 -> 15.3 deg) and was reverted, so the higher ceiling
            # has nothing left to buy and only widens the saturation budget
            # Kp * MaximumRate that stars 21-23 and 32 crashed against.
            "ManualRate": [150, 150, 175], "MaximumRate": [180, 180, 45],
            "StickExpo": [0, 0, 0],
            # AUTOTUNED against the Gazebo X3 (relay identification,
            # 2026-08-09, logs/autotune_20260809_013638.json). Measured
            # ultimate period/gain: roll 114ms/77.6, pitch 156ms/37.8,
            # yaw 560ms/10.2 - i.e. yaw's ultimate gain is ~8x roll's and
            # its natural period ~5x longer: this airframe has very little
            # yaw authority, which is exactly why hand-tuned yaw kept
            # destabilizing it. Kd/ILimit keep their XML defaults (the
            # relay method derives Kp/Ki only).
            "RollRatePID": [0.0030, 0.0065, 0.000033, 0.3],
            "PitchRatePID": [0.0030, 0.0065, 0.000033, 0.3],
            # Yaw deliberately NOT at its autotuned 0.0416: that measurement
            # never converged (its gain was still climbing when the window
            # closed, biasing Kp high), and more importantly the saturation
            # math forbids it - yaw command = Kp * MaximumRate, so 0.0416 at
            # 90 deg/s demands 3.7x full actuator range, leaving the mixer
            # nothing for roll/pitch. That is precisely how stars 21-23
            # tipped over. 0.015 x 25 deg/s = 0.37 peak: meaningfully
            # stronger than the 0.0062 stock gain, with headroom preserved.
            # SATURATION BUDGET (violated once, cost a crash): the yaw rate
            # command is ~ Kp * MaximumRate.Yaw, and the mixer normalizes
            # whatever it is handed - so an over-budget yaw demand does not
            # just yaw badly, it STEALS THRUST. At Kp 0.025 x 90 deg/s =
            # 2.25x full range the vehicle dropped 7.4m -> 0m in 4s the
            # moment a 144 deg hairpin turn started (star 32). Keep
            # Kp * MaximumRate <~ 0.5: 0.010 x 45 = 0.45.
            # Kd 0.00005 -> 0.0006. The yaw rate loop had essentially NO
            # damping, and the board log shows yaw oscillating at ~10 deg
            # RMS (3.5s period) while roll and pitch sit at 1.6-2.3 deg.
            # That wander matters beyond looking untidy: yaw rotates the
            # NE->body mapping in UpdateStabilizationDesired, so it pushes
            # the vehicle laterally off the line and BOWS the long legs.
            # Ki 0.020 -> 0.008. With Kp 0.010 the old pair is an integral time of
            # Kp/Ki = 0.5s, and relay autotune measured this airframe's yaw
            # ultimate period at 560ms - so the integrator was being asked to
            # act about as fast as the loop itself can respond, which is the
            # textbook recipe for a limit cycle rather than for damping. The
            # vehicle duly limit-cycled +/-6 deg at ~3s while PARKED on a
            # waypoint with a constant heading target (star90). That is not
            # cosmetic: yaw rotates the NE->body mapping, so a nose wandering
            # +/-6 deg swings the position correction with it and walks the
            # vehicle around the point - the "orbiting" visible at every
            # corner. 0.008 puts the integral time at 1.25s, comfortably
            # slower than the loop.
            "YawRatePID": [0.010, 0.008, 0.0006, 0.3],
            # STOCK 2.5 restored. This was halved to 1.2 mid-investigation
            # when a divergent ~0.5Hz pitch oscillation appeared during
            # sustained hover - but that oscillation was observed while the
            # transport layer was still destroying ~99% of AccelSensor
            # packets (the com chunked-read bug, since fixed at the root):
            # filtercf.c was running on gyro-dominated data with accel
            # corrections arriving in ~4Hz bursts, so the "attitude
            # instability" was estimator wobble, not a control-gain
            # problem. The halved P then became its own bug one level up:
            # PathFollower's horizontal cascade assumes the attitude loop
            # tracks its roll/pitch commands promptly, and a ~2x-slower
            # attitude response inserted enough lag to make PositionHold
            # laterally divergent (commanded amplitude tripling per cycle)
            # at ANY horizontal gain tried.
            # Attitude-loop PIs from the same autotune. Yaw's 0.75 (vs the
            # stock 2.5) is the headline result: the relay measured that this
            # airframe cannot deliver the yaw acceleration a 2.5 gain asks
            # for, which is the same conclusion the hand-tuned AxisLockKp
            # 2.5->1.0 reached - now backed by measured physics rather than
            # guesswork. Ki left at 0 (the autotuned Ki risks windup on an
            # axis this weak, and roll/pitch hold fine without it).
            "RollPI": [2.5, 0, 50], "PitchPI": [2.5, 0, 50],
            # 0.75 is the AUTOTUNED value. It was doubled to 1.5 during a speed
            # push, and that is what made yaw HUNT: the board log showed
            # +/-9 deg oscillation at ~3.5s period along every leg. Putting
            # it back cut yaw direction-reversals from 0.33/s to 0.08/s and
            # tightened altitude hold from ~1.8m to 0.27m peak-to-peak.
            # Ki stays 0. Tried 0.6 to chase the ~5 deg steady-state yaw lag on
            # a leg (star76): it made things WORSE, 5.03 -> 7.88 deg on-leg
            # error. The integrator winds up across the commanded 144 deg
            # corner turn - which is a slew, not a disturbance - and then has
            # to bleed that charge off over the first seconds of the new leg.
            # An integral term only helps against a *persistent* offset; here
            # the offset is just slew lag, so it charges on exactly the wrong
            # signal.
            "YawPI": [1.5, 0, 50],
            "AcroInsanityFactor": 0.4,
            "ThrustPIDScaleCurve": [0.3, 0.15, 0, -0.15, -0.3],
            "RollMax": 42, "PitchMax": 42, "YawMax": 42,
            "EnablePiroComp": "TRUE", "EnableThrustPIDScaling": "FALSE",
            "ThrustPIDScaleSource": "ActuatorDesiredThrust", "ThrustPIDScaleTarget": "PID",
            "ThrustPIDScaleAxes": "Roll Pitch",
        }
        # CRITICAL: StabilizationBank is a VOLATILE MIRROR - stabilization.c's
        # SettingsBankUpdatedCb re-copies StabilizationSettingsBank1/2/3 (per
        # FlightModeMap) over it on every flight-mode change. Writing only
        # the mirror meant every stab-bank value here silently reverted to
        # XML defaults at the first mode switch after config: star 21/22
        # tip-overs traced to yaw slewing at ~118 deg/s in flight - the XML
        # default MaximumRate.Yaw of 175, not our capped value. The
        # PERSISTENT bank object is what must be written; the mirror send
        # below is kept only so values apply before the first mode change.
        send_reliable("StabilizationSettingsBank1", bov.resolve_enum_values(db["StabilizationSettingsBank1"], stab_bank))
        send_reliable("StabilizationBank", bov.resolve_enum_values(db["StabilizationBank"], stab_bank))
        time.sleep(0.2)

    def on_connected():
        send_config()
        configured["done"] = True
        _mission_client[0] = client
        target = {"manual_hover": manual_hover_test,
                  "poshold": poshold_test,
                  "mission": mission_test,
                  "pull_logs": pull_logs_only,
                  "autotune": autotune_test}.get(TEST_MODE, run_test_sequence)

        def run_with_fc_logging():
            # Runs in its own thread while client.run() keeps pumping packets
            # (setup needs metadata read-backs, download needs DebugLogEntry
            # replies - both dead-lock if attempted from on_connected itself).
            if TEST_MODE != "pull_logs":
                setup_fc_logging(client,
                                 FC_LOG_OBJECTS_AUTOTUNE if TEST_MODE == "autotune"
                                 else (FC_LOG_OBJECTS_MISSION + (
                                     FC_LOG_OBJECTS_DEEP
                                     if os.environ.get("NINJAPILOT_DEEP_LOG") == "1" else [])
                                     if TEST_MODE == "mission" else ()))
                time.sleep(1.0)  # let metadata writes land before arming
            target()
            if TEST_MODE != "pull_logs":
                set_yaw_control(client, "manual")
                # The post-flight TELEMETRY pull is off by default. On
                # simposix the flashfs backend is pios_dosfs_logfs.c, so the
                # very same log slots are already sitting on disk in the
                # firmware's CWD, and tools/decode_fcwd.py reads all of them
                # in ~0.2s. Pulling them back one DebugLogControl request at
                # a time instead costs MINUTES of dead time after every
                # flight, for identical data.
                #
                # It is kept, and still exercised by NINJAPILOT_TEST_MODE=
                # pull_logs, because on real hardware telemetry is the only
                # way to get the log off the board - that path must not rot.
                if os.environ.get("NINJAPILOT_PULL_LOGS") == "1":
                    download_fc_logs(client)
                else:
                    print("[fclog] telemetry pull skipped (data is already on disk)")
                run_post_flight_analysis()

        threading.Thread(target=run_with_fc_logging, daemon=True).start()

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
            _last_flightstatus[0] = decoded
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
        elif objdef.name == "WaypointActive":
            _waypoint_active[0] = decoded["Index"]
        elif objdef.name == "DebugLogStatus":
            _last_log_status[0] = decoded
        elif objdef.name == "RelayTuning":
            _last_relay[0] = decoded
        elif objdef.name == "StabilizationSettingsBank1":
            _last_bank1[0] = decoded
        elif objdef.name == "DebugLogEntry":
            _last_log_entry[0] = decoded
        elif objdef.name == "PathDesired":
            if VERBOSE:
                e = decoded["End"]
                print(f"[pathdbg] t={ts:.2f} PathDesired End=({e[0]:.2f},{e[1]:.2f},{e[2]:.2f}) "
                      f"Mode={decoded['Mode']} UID={decoded['UID']}", flush=True)
        elif objdef.name == "PathStatus":
            if VERBOSE:
                print(f"[pathdbg] t={ts:.2f} PathStatus Status={decoded['Status']} UID={decoded['UID']} "
                      f"fractional={decoded.get('fractional_progress', '?')}", flush=True)
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
        #
        # Split into two groups at two different rates - an earlier,
        # single-group version throttled EVERYTHING (including
        # Baro/Mag/GPS) down to fix a GCSReceiver staleness bug, which
        # fixed that but broke something else: Baro/Mag/GPS dropped to
        # ~1.5Hz, and filteraltitude.c's state estimate (which only
        # updates on SENSORUPDATES_baro/accel) effectively froze between
        # updates - confirmed directly, PositionState.Down/VelocityState.Down
        # stuck at fixed nonzero values for a full 10s hold while real
        # GPS/pose showed the vehicle stationary on the ground the whole
        # time. Baro/Mag/GPS feed the estimator directly and need to stay
        # reasonably fast; SystemAlarms/PIDStatus/etc are pure
        # debug/status readouts this bridge's own on_object() print
        # handlers use, never consumed by any flight-code decision, so
        # they can stay at the very slow rate that fixed GCSReceiver
        # without costing anything real.
        fast_extra_actions = [
            lambda c: c.send_object("GCSReceiver", {"Channel": control.gcs_channels()}),
            lambda c: publish_baro(c),
            lambda c: c.send_object("GCSReceiver", {"Channel": control.gcs_channels()}),
            lambda c: publish_mag(c),
            lambda c: c.send_object("GCSReceiver", {"Channel": control.gcs_channels()}),
            lambda c: publish_gps_velocity(c),
            lambda c: c.send_object("GCSReceiver", {"Channel": control.gcs_channels()}),
            lambda c: publish_gps_position(c),
        ]
        slow_extra_actions = [
            lambda c: c.request_object("GyroState"),
            lambda c: c.request_object("WaypointActive"),
            lambda c: c.request_object("PathDesired"),
            lambda c: c.request_object("PathStatus"),
            lambda c: c.request_object("SystemAlarms"),
            lambda c: c.request_object("FlightStatus"),
            lambda c: c.request_object("AccelState"),
            lambda c: c.request_object("PIDStatus"),
            lambda c: c.request_object("PositionState"),
            lambda c: c.request_object("VelocityState"),
            lambda c: c.request_object("ActuatorDesired"),
        ]
        i = 0
        send_intervals = []
        last_send_ts = [None]
        while True:
            if configured["done"] and client.connected:
                if control.armed != last_arm_state["armed"]:
                    fms = bov.flight_mode_settings(control.armed, ["Attitude", "Attitude", "Attitude"])
                    # The arming toggle re-sends the WHOLE FlightModeSettings
                    # (UAVTalk writes are whole-object) - without honoring
                    # this override it silently stomps any custom switch
                    # mapping: autotune run 2 lost its Autotune slot the
                    # instant the test armed, and the FC sat in PathPlanner
                    # through the entire relay window.
                    if _fms_position_override[0]:
                        fms = dict(fms)
                        fms["FlightModePosition"] = _fms_position_override[0]
                    send_reliable("FlightModeSettings", bov.resolve_enum_values(db["FlightModeSettings"], fms))
                    last_arm_state["armed"] = control.armed

                if control.request_estimator_reset:
                    # See reset_estimator()'s docstring - caller is
                    # responsible for having already disarmed and waited
                    # for that to land before setting this flag. Toggling
                    # FusionAlgorithm to a different value and back forces
                    # stateestimation.c's real reinit condition
                    # (fusionAlgorithm != revoSettings.FusionAlgorithm),
                    # which is the only thing that actually clears
                    # filteraltitude.c's accumulated altitudeState/
                    # velocityState/accelBiasState.
                    other = dict(bov.REVOSETTINGS_DEFAULTS)
                    other["FusionAlgorithm"] = "Basic (Complementary)"
                    send_reliable("RevoSettings", bov.resolve_enum_values(db["RevoSettings"], other))
                    time.sleep(0.3)
                    send_reliable("RevoSettings", bov.resolve_enum_values(db["RevoSettings"], bov.REVOSETTINGS_DEFAULTS))
                    time.sleep(0.3)
                    control.request_estimator_reset = False

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
                    publish_gyro(client, gyro_dps)

                latency_stats["last_request_ts"] = time.time()
                client.request_object("ActuatorCommand")

                # AccelSensor - split from the Gyro send above (see
                # publish_accel's own docstring for the full "back-to-back
                # different-object sends corrupt this link" investigation).
                # Deliberately placed here, after the ActuatorCommand
                # request rather than immediately after publish_gyro, so a
                # real send happens in between even within the same tick -
                # genuine separation, not just a different modulo on
                # otherwise-adjacent calls.
                # Every tick, not alternate ticks: the transport fix that
                # matters is the SEPARATED send position (a real send sits
                # between Gyro and Accel), not the halved rate - and the
                # halved rate had real collateral damage: filtercf.c only
                # publishes AttitudeState on gyro ticks where accel was
                # ALSO seen, so accel at 250Hz halved AttitudeState to
                # ~250Hz, which (a) halves the outerloop dispatch rate
                # (AttitudeState-gated, 1-in-OUTERLOOP_SKIPCOUNT) and
                # (b) sits innerloop.c's rateupdates watchdog exactly at
                # its warn/critical edge (its thresholds assume attitude
                # tracks the 500Hz gyro rate), producing a constantly
                # flapping Stabilization alarm. The firmware-side UDP RX
                # drain-per-tick fix (pios_udp.c) removed the backlog
                # concern that motivated rate reduction in the first place.
                if have_pose:
                    publish_accel(client, accel_body)

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
                # already be saturating it. Split into fast_extra_actions
                # (GCSReceiver + Baro/Mag/GPS - feed the estimator/control
                # loop directly, need real rate) and slow_extra_actions
                # (pure debug/status requests - see the split's own
                # comment above for why an even-slower rate there is free).
                if i % 20 == 0:
                    fast_extra_actions[(i // 20) % len(fast_extra_actions)](client)
                if i % 100 == 0:
                    slow_extra_actions[(i // 100) % len(slow_extra_actions)](client)
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


def publish_gyro(client, gyro_dps):
    # GyroSensor goes out every tick, unconditionally, and from a point in
    # the loop with real separation from AccelSensor's own send (see
    # publish_accel's docstring) - stabilizationInnerloopTask (innerloop.c)
    # is triggered directly off GyroState updates, so this is on the
    # critical control path and shouldn't be delayed or bundled with
    # anything else.
    client.send_object("GyroSensor", {"x": gyro_dps[0], "y": gyro_dps[1], "z": gyro_dps[2], "temperature": 25.0})
    now = time.time()
    if now - _last_gyro_dbg[0] > 0.1:
        _last_gyro_dbg[0] = now
        if VERBOSE:
            print(f"[gyrodbg] t={now:.2f} gyro_dps=({gyro_dps[0]:.2f},{gyro_dps[1]:.2f},{gyro_dps[2]:.2f})", flush=True)


def publish_accel(client, accel_body):
    # Split from the old publish_fast_sensors(), which sent GyroSensor and
    # AccelSensor back-to-back in the same tick with zero gap between them
    # - exactly the pattern already documented elsewhere in this codebase
    # (board_orientation_viz.py) as reliably corrupting/dropping one of a
    # pair of back-to-back different-object sends on this link. Confirmed
    # directly this was happening here too, and getting WORSE over time
    # (not a fixed drop rate): a SIMPOSIX-gated counter in
    # stateestimation.c's sensorUpdatedCb showed gyroMatches and
    # accelMatches starting in lockstep (654/653) but diverging
    # continuously as a real test ran (48863/41859 by the end, a growing
    # ~7000-sample gap) - AccelSensor was being progressively lost at the
    # transport layer, which is what was actually starving
    # filteraltitude.c's velocity integration (gated on a fresh
    # SENSORUPDATES_accel bit) and, transitively, altitudeHoldTask - not
    # any FreeRTOS scheduling issue, despite how deep that investigation
    # went before this was found. Called from a separate tick than
    # publish_gyro (see the sender_loop call site) so the two sends are
    # genuinely separated by real time (a full loop iteration, including
    # its own sleep), not just by other code running in between within
    # the same tick.
    client.send_object("AccelSensor", {"x": accel_body[0], "y": accel_body[1], "z": accel_body[2], "temperature": 25.0})
    _accel_send_count[0] += 1
    now = time.time()
    if now - _accel_send_count[1] > 1.0:
        _accel_send_count[1] = now
        if VERBOSE:
            print(f"[acceldbg] t={now:.2f} total_accel_sends={_accel_send_count[0]}", flush=True)


_accel_send_count = [0, 0.0]  # [total sends, last debug print time]


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


# --- GPS noise injection (driven by the GpsNoise panel in the Gazebo GUI) --
# Gazebo's navsat is effectively a perfect fix, which flatters the
# estimator. These sigmas let a real degraded fix be simulated so the
# filter and the controllers can be tested against one. Applied HERE
# because the GPS the flight controller sees is synthesised by this
# bridge - the panel only states the requested standard deviations.
_gps_noise = {"pos": 0.0, "vel": 0.0}


def _on_gps_noise(msg):
    _gps_noise["pos"] = float(msg.x)
    _gps_noise["vel"] = float(msg.y)


def subscribe_gps_noise(node):
    try:
        from gz.msgs10.vector3d_pb2 import Vector3d
        node.subscribe(Vector3d, "/ninjapilot/gps_noise", _on_gps_noise)
        print("[gpsnoise] listening on /ninjapilot/gps_noise")
    except Exception as exc:
        print("[gpsnoise] not subscribed (%s)" % exc)


def _noisy(value, sigma):
    return value if sigma <= 0.0 else value + random.gauss(0.0, sigma)


def publish_gps_velocity(client):
    have_navsat, lat, lon, alt, vel_ned = state.gps_snapshot()
    if have_navsat:
        sv = _gps_noise["vel"]
        client.send_object("GPSVelocitySensor", {"North": _noisy(vel_ned[0], sv),
                                                 "East": _noisy(vel_ned[1], sv),
                                                 "Down": _noisy(vel_ned[2], sv)})


def publish_gps_position(client):
    # Real navsat sensor data (gz-sim-navsat-system, see model.sdf/
    # quadcopter_ninjapilot.sdf) - a real sensor reading has none of the
    # lag a position-derivative introduces, which matters directly for
    # PositionHold's velocity-error feedback loop.
    have_navsat, lat, lon, alt, vel_ned = state.gps_snapshot()
    if have_navsat:
        # Requested position noise, applied in METRES and converted back to
        # degrees here - a fixed degree offset would be a different distance
        # north/south than east/west.
        sp = _gps_noise["pos"]
        if sp > 0.0:
            lat = lat + random.gauss(0.0, sp) / 111320.0
            lon = lon + random.gauss(0.0, sp) / (111320.0 * math.cos(math.radians(lat)))
            alt = alt + random.gauss(0.0, sp)
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
