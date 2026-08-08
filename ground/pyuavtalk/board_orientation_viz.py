#!/usr/bin/env python3
#
# board_orientation_viz - a tiny local web page showing which way the
# simulated flight controller board is pointing, and letting you shove it.
#
# It connects to a running fw_simposix.elf over UAVTalk/UDP, reads the live
# AttitudeState quaternion, and works out which of the seven canonical
# orientations from the old GCS sensor-calibration wizard it's closest to
# (NED/DWN/WDS/ENU/USE/SUW/SWD - see sixpointcalibrationmodel.cpp and
# levelcalibrationmodel.cpp). It then shows the matching 3D-rendered board
# photo from ground/openpilotgcs/.../images/calibration/board-*.png, served
# straight from that directory - no assets are copied.
#
# It also drives a virtual receiver (GCSReceiver, the same object real HITL
# radio input rides in on) so the real ManualControl/Stabilization/Actuator
# flight code actually runs: an Arm switch and flight-mode picker control
# FlightModeSettings.Arming and the flight-mode channel, and three Roll/
# Pitch/Yaw sliders apply an external rate disturbance (see sensors.c's
# addExternalRateDisturbance) - literally grabbing the simulated board and
# twisting it, same as old HITL let an external simulator do. Release a
# slider and the real Stabilization loop fights to bring it back level, the
# same way a real self-leveling multirotor would.
#
# A live table of key UAVObjects (FlightStatus, SystemAlarms,
# StabilizationDesired, RateDesired, ActuatorDesired) shows what the flight
# code is doing about it.
#
# Usage:
#   python3 board_orientation_viz.py
#   (then open http://127.0.0.1:8765 in a browser)
#
# The OpenPilot Team, http://www.openpilot.org, Copyright (C) 2011.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

import argparse
import http.server
import json
import os
import threading
import time
import webbrowser

import uavtalk
from uavtalk_client import UdpTransport, UAVTalkClient, default_xml_dir

HERE = os.path.dirname(os.path.abspath(__file__))
IMAGES_DIR = os.path.join(HERE, "..", "openpilotgcs", "src", "plugins", "config", "images", "calibration")
# The real 3D board model+texture the GCS's own modelview gadget renders
# (share/openpilotgcs/models/boards/Revolution/) - an actual mesh, not a
# baked photo, so it can be rotated live instead of only snapped between
# fixed poses.
MODEL_DIR = os.path.join(HERE, "..", "openpilotgcs", "share", "openpilotgcs", "models", "boards", "Revolution")
# The GCS's own System Health gadget (a grid of per-alarm colored boxes) and
# its telemetry Tx/Rx rate meter - both are just SVGs with per-state layers
# toggled by element id, so the browser can drive the exact same artwork.
DIAGRAM_DIR = os.path.join(HERE, "..", "openpilotgcs", "share", "openpilotgcs", "diagrams", "default")
TELEMETRY_IMG_DIR = os.path.join(HERE, "..", "openpilotgcs", "src", "plugins", "telemetry", "images")

FLIGHT_MODE_NUMBER = 4  # Stabilized1 (configurable below), Stabilized2/3 (fixed presets), PositionHold
FLIGHT_MODE_NAMES = ["Stabilized1", "Stabilized2", "Stabilized3", "PositionHold"]

# The full set of per-axis stabilization modes real hardware offers
# (stabilizationdesired.xml's StabilizationMode enum) - exposed so
# Stabilized1's Roll/Pitch/Yaw axes can each be set independently instead
# of only offering fixed presets.
STABILIZATION_MODE_OPTIONS = [
    "Manual", "Rate", "Attitude", "AxisLock", "WeakLeveling", "VirtualBar",
    "Acro+", "Rattitude", "AltitudeHold", "AltitudeVario", "CruiseControl",
]

# The table just shows whatever fields these objects decode to - no need to
# hardcode field names, describe() already resolves enums to readable text.
WATCHED_OBJECTS = ["FlightStatus", "SystemAlarms", "StabilizationDesired", "RateDesired", "ActuatorDesired", "ActuatorCommand", "FlightTelemetryStats", "GPSPositionSensor"]

# UAVTalk writes are whole-object overwrites, not sparse patches - any field
# left out of a send_object() call gets zeroed, not "left alone". So writing
# FlightModeSettings to flip Arming has to restate every other field too, or
# it silently wipes FlightModePosition/Stabilization*Settings back to zero
# ("Manual" mode on every switch position). These are flightmodesettings.xml's
# own <field defaultvalue=...> values - a fresh board would boot with exactly
# this, so restating it changes nothing except Arming.
FLIGHT_MODE_SETTINGS_DEFAULTS = {
    "ReturnToBaseAltitudeOffset": 10.0,
    "LandingVelocity": 0.6,
    "PositionHoldOffset": [30.0, 15.0],
    "VarioControlLowPassAlpha": 0.98,
    "ArmedTimeout": 30000,
    "ArmingSequenceTime": 1000,
    "DisarmingSequenceTime": 1000,
    "Stabilization1Settings": ["Attitude", "Attitude", "AxisLock", "Manual"],
    # Repurposed as a "pure baro alt hold" test slot: Roll/Pitch=Attitude
    # (leveling), Thrust=AltitudeVario (flight/modules/Stabilization/
    # altitudeloop.c - a real, separate, fast Stabilization-loop-rate PID
    # against PositionState.Down/VelocityState.Down, activated via
    # STABILIZATIONDESIRED_STABILIZATIONMODE_ALTITUDEVARIO, distinct from
    # PathFollower's CruiseControl-based thrust used by PositionHold).
    # Was AltitudeHold: that mode's own stabilizationAltitudeHold() only
    # ever captures whatever PositionState.Down happens to be at the
    # instant the mode is entered/re-armed and locks onto it - it never
    # reads the Thrust setpoint at all once locked, so it CANNOT climb.
    # gazebo_bridge.py was doing the entire climb itself in a separate
    # Thrust=Manual mode with hand-rolled Python throttle math before
    # switching into this slot only to hold what was already reached -
    # meaning this flight code's actual altitude control was only ever
    # being asked to latch a static point, never to track a moving
    # setpoint, the whole time this was "AltitudeHold". AltitudeVario's
    # deadband convention (see altitudeloop.c) gives the real thing: stick
    # above ~0.6 commands a real closed-loop climb via the position/
    # velocity PID cascade, centering it (~0.5) captures the current
    # PositionState.Down and holds it - same PID chain, same PositionState/
    # VelocityState feedback, but now actually exercised for the climb,
    # not just the hold. Lets alt-hold be tested in isolation from GPS
    # horizontal position hold and from PathFollower entirely.
    "Stabilization2Settings": ["Attitude", "Attitude", "AxisLock", "AltitudeVario"],
    # "2D position hold" test slot: baro altitude vario/hold (same as
    # Stabilization2, see its comment) plus magnetometer-referenced yaw
    # heading hold instead of AxisLock's rate-integral drift-and-hold -
    # Yaw=Attitude uses AttitudeState.Yaw directly (outerloop.c's
    # quaternion-attitude error path), which is mag-corrected now that
    # HomeLocation.Be is measured from a real sensor reading (see
    # gazebo_bridge.py's send_config()). Roll/Pitch=Attitude only levels
    # the craft - nothing here corrects horizontal drift (that's
    # PositionHold/PathFollower's job, a separate flight mode), so
    # wind-driven horizontal drift is expected and acceptable, matching a
    # real 2D hold (heading + altitude only, no GPS lateral correction).
    "Stabilization3Settings": ["Attitude", "Attitude", "Attitude", "AltitudeVario"],
    "Stabilization4Settings": ["Attitude", "Attitude", "AxisLock", "CruiseControl"],
    "Stabilization5Settings": ["Attitude", "Attitude", "Rate", "CruiseControl"],
    "Stabilization6Settings": ["Rate", "Rate", "Rate", "Manual"],
    # Position 4 (0-indexed 3) is PositionHold, matching FLIGHT_MODE_NUMBER/
    # FLIGHT_MODE_NAMES above and the dropdown's 4th option - the flight
    # code's own pathFollowerHandler() auto-captures the current position
    # as the hold point on entry (plan_setup_positionHold()), no PathDesired
    # write needed from here.
    "FlightModePosition": ["Stabilized1", "Stabilized2", "Stabilized3", "PositionHold", "Stabilized5", "Stabilized6"],
    "DisableSanityChecks": "FALSE",
    "ReturnToBaseNextCommand": "Hold",
}


def flight_mode_settings(armed, stab1_modes=None):
    values = dict(FLIGHT_MODE_SETTINGS_DEFAULTS)
    values["Arming"] = "Always Armed" if armed else "Always Disarmed"
    if stab1_modes:
        values["Stabilization1Settings"] = [stab1_modes[0], stab1_modes[1], stab1_modes[2], "Manual"]
    return values


# The rest of these clear SystemAlarms entries that otherwise sit at
# Uninitialised forever on a fresh board - not because anything is broken,
# but because the modules that would clear them never got the config (or,
# for GPS/Airspeed, never even got *enabled*) to run in the first place.
# Same whole-object-write caveat as FLIGHT_MODE_SETTINGS_DEFAULTS above:
# these restate every field at its own XML-declared default except the one
# or two we actually care about.

HWSETTINGS_DEFAULTS = {
    "CC_RcvrPort": "PWM+NoOneShot",
    "CC_MainPort": "Telemetry",
    "CC_FlexiPort": "Disabled",
    "RV_RcvrPort": "PWM",
    "RV_AuxPort": "Disabled",
    "RV_AuxSBusPort": "Disabled",
    "RV_FlexiPort": "Disabled",
    "RV_TelemetryPort": "Telemetry",
    "RV_GPSPort": "GPS",
    "RM_RcvrPort": "PWM",
    "RM_MainPort": "Disabled",
    "RM_FlexiPort": "Disabled",
    "TelemetrySpeed": "57600",
    "GPSSpeed": "57600",
    "ComUsbBridgeSpeed": "57600",
    "USB_HIDPort": "USBTelemetry",
    "USB_VCPPort": "Disabled",
    # CameraStab,GPS,Fault,Altitude,Airspeed,TxPID,Battery,Overo,MagBaro,OsdHk
    "OptionalModules": ["Disabled", "Enabled", "Disabled", "Disabled", "Enabled",
                         "Disabled", "Disabled", "Disabled", "Disabled", "Disabled"],
    "ADCRouting": ["Disabled", "Disabled", "Disabled", "Disabled"],
    "DSMxBind": 0,
    "WS2811LED_Out": "Disabled",
}

REVOSETTINGS_DEFAULTS = {
    # No mag in the default "Basic (Complementary)" chain, so filtermag.c's
    # checkMagValidity() never runs and the alarm sits at Uninitialised
    # forever regardless of how good the simulated compass reading is.
    # Mag fusion instability (see filtermag.c/filtercf.c history in
    # CLAUDE.md/session notes) traced to HomeLocation.Be not actually
    # matching what Gazebo's magnetometer plugin reports (magnitude AND
    # direction) - gazebo_bridge.py's send_config() now MEASURES Be from a
    # real reading at spawn (vehicle level, Yaw=0) instead of assuming a
    # fixed value, so the two are always self-consistent. Re-test before
    # reverting to "Basic (Complementary)" if instability returns.
    # PositionHold's own controller (VtolFlyController/PathFollower) owns
    # a full 3D target (PathDesired.End.North/East/Down, all captured
    # together in plan_setup_positionHold()) and directly sets
    # stabDesired.Thrust via controlDown.GetDownCommand() - vertical hold
    # genuinely is part of PositionHold's job in this codebase, not a
    # separate system underneath it. "Complementary+Mag" (baro-only
    # altitude, no GPS/lla fusion) was a holdover from working around the
    # since-fixed magnetometer bug - now that mag fusion works and we have
    # a real navsat GPS feed (see gazebo_bridge.py), fuse it in too via
    # Complementary+Mag+GPSOutdoor (adds llaFilter to the chain -
    # filterlla.c requires HomeLocation.Set + GPS Fix3D/PDOP/satellite
    # thresholds, all already satisfied by publish_slow_sensors()).
    # Complementary+Mag+GPSOutdoor: Mahony attitude (filtercf.c) + the
    # 3-state Kalman vertical filter (filteraltitude.c) + GPS lla/vel.
    # The full outdoor EKF ("GPS Navigation (INS13)") was tried on the
    # clean transport (2026-08-08): its attitude estimate degraded in
    # flight (Attitude alarm Warning->Critical mid-air, covariance sanity
    # resets in filterekf.c), porpoising the vehicle laterally into a
    # crash during a plain baro-hold stage - its EKFConfiguration Q/R
    # defaults are tuned for real-sensor noise, not this sim's near-zero
    # noise, and need their own tuning pass before it's flyable here.
    # The Mahony+KF stack flew every stage rock-solid on the same day.
    "FusionAlgorithm": "Complementary+Mag+GPSOutdoor",
    "BaroGPSOffsetCorrectionAlpha": 0.9993335555062,
    "MagnetometerMaxDeviation": [0.05, 0.15],
    "BaroTempCorrectionPolynomial": [0, 0, 0, 0],
    "BaroTempCorrectionExtent": [0, 0],
    "VelocityPostProcessingLowPassAlpha": 0.999,
}

HOMELOCATION_DEFAULTS = {
    "Set": "TRUE",
    "Latitude": 0,
    "Longitude": 0,
    "Altitude": 0.0,
    # sensors.c's simulated mag reading is a pure rotation of this vector
    # into body frame (Be -> Rbe*Be, no noise/offset added) - matching the
    # magnitude filtermag.c expects exactly, rather than picking an
    # arbitrary field strength that would just fail its own deviation
    # check. Values are sensors.c's own commented-out example default.
    "Be": [26000.0, 400.0, 40000.0],
    "g_e": 9.81,
}

AIRSPEEDSETTINGS_DEFAULTS = {
    "SamplePeriod": 100,
    "ZeroPoint": 0,
    "Scale": 1.0,
    # Works entirely off AttitudeState/VelocityState, which are already
    # simulated - no fake ADC/pitot pressure needed, unlike the other
    # sensor types this field offers.
    "AirspeedSensorType": "GroundSpeedBasedWindEstimation",
    "IMUBasedEstimationLowPassPeriod1": 0.5,
    "IMUBasedEstimationLowPassPeriod2": 10.0,
}

# QuadX motor mixer, values lifted straight from vehicleconfigurationhelper.cpp's
# own setupQuadCopter() preset (percent -> +-127 via ceil/floor(pct*127/100)):
# motor0 roll=50,pitch=50,yaw=-50; motor1 roll=-50,pitch=50,yaw=50;
# motor2 roll=-50,pitch=-50,yaw=-50; motor3 roll=50,pitch=-50,yaw=50.
_QUADX_MOTOR_VECTORS = [
    [127, 0, 64, 64, -64],
    [127, 0, -64, 64, 64],
    [127, 0, -64, -64, -64],
    [127, 0, 64, -64, 64],
]


def mixer_settings():
    values = {}
    for i in range(1, 11):
        if i <= len(_QUADX_MOTOR_VECTORS):
            values["Mixer%dType" % i] = "Motor"
            values["Mixer%dVector" % i] = _QUADX_MOTOR_VECTORS[i - 1]
        else:
            values["Mixer%dType" % i] = "Disabled"
            values["Mixer%dVector" % i] = [0, 0, 0, 0, 0]
    # Stock default is all-zero (a fresh board won't spin motors until you
    # run the GCS Output wizard) - the Actuator module's Motor mixer reads
    # curve1 straight from this table (actuator.c's MixerCurveFullRangeProportional),
    # so a zero curve means throttleDesired never reaches the motors at all,
    # no matter what the stick says. A linear pass-through is what that
    # wizard would leave you with for a simple sim - matches ThrottleCurve2's
    # own default shape.
    values["ThrottleCurve1"] = [0, 0.25, 0.5, 0.75, 1]
    values["ThrottleCurve2"] = [0, 0.25, 0.5, 0.75, 1]
    values["MixerValueRoll"] = 50
    values["MixerValuePitch"] = 50
    values["MixerValueYaw"] = 50
    # These four were missing from this whole-object-safe dict (see the
    # WATCHED_OBJECTS comment on send_object being an overwrite, not a
    # patch), which silently zeroed them - MaxAccel=0 in particular is not
    # "unlimited", it's actuator.c's ProcessMixer() acceleration limiter
    # reading "0 units/sec allowed", which permanently clamps every motor's
    # output to its starting value (0) no matter what curve1/desired say.
    # Real default is 1000 (units/sec) - fast enough that a full 0->1
    # sweep clears in ~1ms, effectively unbounded for this demo.
    values["MaxAccel"] = 1000.0
    values["FeedForward"] = 0.0
    values["AccelTime"] = 0.0
    values["DecelTime"] = 0.0
    values["Curve2Source"] = "Throttle"
    return values


# PathPlan.Crc must match a CRC-8 the flight side computes itself over the
# raw packed bytes of the live Waypoint/PathAction instances (pathplanner.c's
# checkPathPlan(), via UAVObjUpdateCRC -> PIOS_CRC_updateCRC) - a mismatch
# just reads as "bad CRC" and PathPlan never clears. This table is copied
# exactly from flight/pios/posix/pios_crc.c (CRC-8, poly 0x07, no reflection,
# table-driven) so the same bytes our own pack() produces hash identically.
_CRC8_TABLE = [
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15, 0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,
    0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65, 0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,
    0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5, 0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
    0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85, 0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
    0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2, 0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
    0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2, 0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
    0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32, 0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
    0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42, 0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
    0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c, 0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
    0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec, 0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
    0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c, 0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
    0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c, 0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
    0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b, 0x76, 0x71, 0x78, 0x7f, 0x6a, 0x6d, 0x64, 0x63,
    0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b, 0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
    0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb, 0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8d, 0x84, 0x83,
    0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb, 0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3,
]


def _crc8_update(crc, data):
    for b in data:
        crc = _CRC8_TABLE[crc ^ b]
    return crc


WAYPOINT_DEFAULTS = {
    "Position": [0.0, 0.0, -5.0],  # 5m above home
    "Velocity": 2.0,
    "Action": 0,  # references PathAction instance 0
}

PATHACTION_DEFAULTS = {
    "Mode": "GoToEndpoint",
    "ModeParameters": [0.0, 0.0, 0.0, 0.0],
    "EndCondition": "None",
    "ConditionParameters": [0.0, 0.0, 0.0, 0.0],
    "Command": "OnConditionNextWaypoint",
    "JumpDestination": 0,
    "ErrorDestination": 0,
}


def pathplan_setup(db):
    """A minimal one-waypoint, one-action plan, with the matching CRC
    computed the same way the flight side will - so PathPlan.WaypointCount
    a client sends isn't enough on its own; the flight side independently
    recomputes the CRC from whatever Waypoint/PathAction instance 0 it has
    and only clears the alarm if it matches what we claim here."""
    waypoint_objdef = db["Waypoint"]
    pathaction_objdef = db["PathAction"]
    waypoint_values = resolve_enum_values(waypoint_objdef, WAYPOINT_DEFAULTS)
    pathaction_values = resolve_enum_values(pathaction_objdef, PATHACTION_DEFAULTS)
    crc = 0
    crc = _crc8_update(crc, waypoint_objdef.pack(waypoint_values))
    crc = _crc8_update(crc, pathaction_objdef.pack(pathaction_values))
    return waypoint_values, pathaction_values, crc


def resolve_enum_values(objdef, values):
    """pack() needs the raw wire integer for enum fields, not the option name -
    translate any human-readable strings in `values` using the field's own
    <option> list so callers (and the defaults above) can stay readable."""
    fields_by_name = {f.name: f for f in objdef.fields}
    resolved = {}
    for key, val in values.items():
        field = fields_by_name.get(key)
        if field and field.type == "enum" and field.options:
            if isinstance(val, list):
                resolved[key] = [field.options.index(v) if isinstance(v, str) else v for v in val]
            elif isinstance(val, str):
                resolved[key] = field.options.index(val)
            else:
                resolved[key] = val
        else:
            resolved[key] = val
    return resolved


# systemalarms.xml's Alarm field element order - used to label the table.
ALARM_NAMES = [
    "SystemConfiguration", "BootFault", "OutOfMemory", "StackOverflow", "CPUOverload",
    "EventSystem", "Telemetry", "Receiver", "ManualControl", "Actuator", "Attitude",
    "Sensors", "Magnetometer", "Airspeed", "Stabilization", "Guidance", "PathPlan",
    "Battery", "FlightTime", "I2C", "GPS",
]

# Each pose's 3-letter code names the NED-world direction (North/South/East/
# West/Down/Up) that the board's nose (Xb), right side (Yb) and belly (Zb)
# axes point to - exactly the convention used by sixpointcalibrationmodel.cpp
# and levelcalibrationmodel.cpp to choose which board-*.png to show.
_DIR_VECTORS = {
    "N": (1, 0, 0), "S": (-1, 0, 0),
    "E": (0, 1, 0), "W": (0, -1, 0),
    "D": (0, 0, 1), "U": (0, 0, -1),
}

# name -> (instruction text lifted from the calibration wizard, 3-letter code)
POSES = {
    "ned": ("Level, nose north", "NED"),
    "dwn": ("Nose down, right side west", "DWN"),
    "wds": ("Right side down, nose west", "WDS"),
    "enu": ("Upside down, nose east", "ENU"),
    "use": ("Nose up, left side north", "USE"),
    "suw": ("Left side down, nose south", "SUW"),
    "swd": ("Level, nose south (yawed 180)", "SWD"),
}

_POSE_MATRICES = {name: tuple(_DIR_VECTORS[letter] for letter in code) for name, (_desc, code) in POSES.items()}


def _quat_to_rbe(w, x, y, z):
    """Earth-to-body rotation matrix - same formula as CoordinateConversions.c's Quaternion2R."""
    ws, xs, ys, zs = w * w, x * x, y * y, z * z
    return (
        (ws + xs - ys - zs, 2 * (x * y + w * z), 2 * (x * z - w * y)),
        (2 * (x * y - w * z), ws - xs + ys - zs, 2 * (y * z + w * x)),
        (2 * (x * z + w * y), 2 * (y * z - w * x), ws - xs - ys - zs),
    )


def nearest_pose(w, x, y, z):
    """Return the name of the reference pose closest to the given attitude quaternion."""
    rbe = _quat_to_rbe(w, x, y, z)
    best_name, best_score = "ned", -4.0
    for name, ref in _POSE_MATRICES.items():
        score = sum(rbe[i][j] * ref[i][j] for i in range(3) for j in range(3))
        if score > best_score:
            best_score, best_name = score, name
    return best_name


def flight_mode_channel(position, n=FLIGHT_MODE_NUMBER):
    """us value landing in the middle of receiver.c's bin for the given position."""
    norm = ((2.0 * position + 1) / n) - 1.0  # -1..1, centered in its bin
    return int(round(1500 + norm * 500))


def slider_channel(value):
    """value in -1..1 -> 1000..2000us, clamped."""
    value = max(-1.0, min(1.0, value))
    return int(round(1500 + value * 500))


class ControlState(object):
    """What the UI wants the virtual receiver to be sending right now."""

    def __init__(self):
        self.lock = threading.Lock()
        self.armed = False
        self.mode_position = 0
        self.throttle = 0.0
        self.disturbance = {"roll": 0.0, "pitch": 0.0, "yaw": 0.0}
        self.stab1_modes = ["Attitude", "Attitude", "AxisLock"]

    def update(self, fields):
        with self.lock:
            if "armed" in fields:
                self.armed = bool(fields["armed"])
            if "mode_position" in fields:
                self.mode_position = max(0, min(FLIGHT_MODE_NUMBER - 1, int(fields["mode_position"])))
            if "throttle" in fields:
                self.throttle = max(0.0, min(1.0, float(fields["throttle"])))
            if "disturbance" in fields:
                for axis in ("roll", "pitch", "yaw"):
                    if axis in fields["disturbance"]:
                        self.disturbance[axis] = float(fields["disturbance"][axis])
            if "stab1_modes" in fields:
                modes = fields["stab1_modes"]
                if isinstance(modes, list) and len(modes) == 3 and all(m in STABILIZATION_MODE_OPTIONS for m in modes):
                    self.stab1_modes = list(modes)

    def snapshot(self):
        with self.lock:
            return {
                "armed": self.armed, "mode_position": self.mode_position, "throttle": self.throttle,
                "disturbance": dict(self.disturbance), "stab1_modes": list(self.stab1_modes),
            }

    def gcs_channels(self):
        s = self.snapshot()
        return [
            int(round(1000 + s["throttle"] * 1000)),  # 0 Throttle - 0 by default (idle); Output Channels panel
                                                        # needs some lift baseline before roll/pitch/yaw correction
                                                        # can show up as anything but "all motors clamped at floor"
            1500,                                       # 1 Roll stick - neutral, disturbance rides on ch5 instead
            1500,                                       # 2 Pitch stick - neutral
            1500,                                       # 3 Yaw stick - neutral
            flight_mode_channel(s["mode_position"]),    # 4 Flight mode switch
            slider_channel(s["disturbance"]["roll"]),   # 5 external roll rate disturbance
            slider_channel(s["disturbance"]["pitch"]),  # 6 external pitch rate disturbance
            slider_channel(s["disturbance"]["yaw"]),    # 7 external yaw rate disturbance
        ]


class SharedState(object):
    def __init__(self):
        self.lock = threading.Lock()
        self.connected = False
        self.roll = self.pitch = self.yaw = 0.0
        self.q = (1.0, 0.0, 0.0, 0.0)
        self.pose = "empty"
        self.objects = {}  # name -> decoded dict, for WATCHED_OBJECTS
        self._pending_pose = None
        self._pending_count = 0

    def update_attitude(self, roll, pitch, yaw, q, pose):
        with self.lock:
            self.roll, self.pitch, self.yaw = roll, pitch, yaw
            self.q = q
            # The board photo is a fixed set of 8 static images, not a live
            # 3D model, so it can only ever snap between poses - it can't be
            # smoothly animated. What we *can* fix is single-sample noise
            # flipping it back and forth near a boundary between two poses:
            # require two consecutive AttitudeState reads (~200ms) to agree
            # on a new pose before actually switching the displayed image.
            if pose == self.pose:
                self._pending_pose = None
                self._pending_count = 0
            elif pose == self._pending_pose:
                self._pending_count += 1
                if self._pending_count >= 2:
                    self.pose = pose
                    self._pending_pose = None
                    self._pending_count = 0
            else:
                self._pending_pose = pose
                self._pending_count = 1
            self.connected = True

    def update_object(self, name, decoded):
        with self.lock:
            self.objects[name] = decoded
            self.connected = True

    def mark_disconnected(self):
        with self.lock:
            self.connected = False
            self.pose = "empty"

    def snapshot(self):
        with self.lock:
            alarms = []
            alarms_full = []
            sa = self.objects.get("SystemAlarms")
            if sa and "Alarm" in sa:
                for name, level in zip(ALARM_NAMES, sa["Alarm"]):
                    alarms_full.append({"name": name, "level": level})
                    if level not in ("OK",):
                        alarms.append({"name": name, "level": level})
            return {
                "connected": self.connected,
                "roll": self.roll,
                "pitch": self.pitch,
                "yaw": self.yaw,
                "q": list(self.q),
                "pose": self.pose,
                "description": POSES.get(self.pose, ("No link",))[0],
                "alarms": alarms,
                "alarms_full": alarms_full,
                # ActuatorCommand and GPSPositionSensor each get their own
                # dedicated panel instead of the generic per-object table dump.
                "objects": {k: v for k, v in self.objects.items() if k not in ("SystemAlarms", "ActuatorCommand", "GPSPositionSensor")},
                "actuator_command": self.objects.get("ActuatorCommand"),
                "gps": self.objects.get("GPSPositionSensor"),
            }


def uavtalk_thread(state, control, host, port, xml_dir):
    db = uavtalk.UAVObjectDB(xml_dir)
    transport = UdpTransport(host, port)
    client = UAVTalkClient(transport, db)
    configured = {"done": False}

    def on_object(objdef, inst_id, decoded):
        if objdef.name == "AttitudeState":
            q = (decoded["q1"], decoded["q2"], decoded["q3"], decoded["q4"])
            pose = nearest_pose(*q)
            state.update_attitude(decoded["Roll"], decoded["Pitch"], decoded["Yaw"], q, pose)
        elif objdef.name in WATCHED_OBJECTS:
            state.update_object(objdef.name, decoded)

    def on_connected():
        # Route Throttle/Roll/Pitch/Yaw/FlightMode through our virtual receiver.
        # ManualControlSettings.ChannelNumber is 1-indexed (see PIOS_RCVR_Read).
        client.send_object("ManualControlSettings", {
            "ChannelGroups": [5, 5, 5, 5, 5, 7, 7, 7, 7],  # GCS=5, None=7
            "ChannelNumber": [1, 2, 3, 4, 5, 0, 0, 0, 0],
            # receiver.c's scaleChannel() is a 3-point Min/Neutral/Max scale,
            # symmetric -1..1 around Neutral - fine for Roll/Pitch/Yaw
            # (spring-centered sticks) but Throttle (element 0, this array's
            # order is Throttle,Roll,Pitch,Yaw,FlightMode,...) is a ratchet
            # throttle with no spring center. Leaving it at 1500 like the
            # others pinned the whole bottom half of the throttle slider to
            # Throttle<0 (clamped to 0 thrust downstream) and put exactly 0.5
            # slider - dead center of the 1000-2000us range - precisely on
            # the neutral point, always reading Throttle=0.0.
            #
            # Setting Neutral == Min (1000) "fixes" that but breaks arming
            # outright: armhandler.c's lowThrottle = cmd.Throttle < 0 can
            # never be true again once Throttle can't go negative, so the
            # arm gesture (which requires throttle to read "low" first)
            # never completes. Real transmitters solve this by calibrating
            # a small below-idle deadband: Neutral sits a little above Min,
            # so the bottom slice of stick travel still reads negative
            # (arm-safe), and the rest scales smoothly and monotonically up
            # to Throttle=1.0 with no dead zone in the middle.
            "ChannelMin": [1000] * 9, "ChannelNeutral": [1050, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500], "ChannelMax": [2000] * 9,
            "ResponseTime": [0] * 7, "Deadband": 0.02, "DeadbandAssistedControl": 0.08,
            "FlightModeNumber": FLIGHT_MODE_NUMBER, "FailsafeFlightModeSwitchPosition": -1,
            "FailsafeChannel": [-1, 0, 0, 0, 0, 0, 0, 0],
        })
        time.sleep(0.2)

        # Clear the sensor/subsystem alarms that only sit at Uninitialised
        # because nothing ever enabled/configured them - not because
        # anything is actually broken. Sequential sends with real gaps,
        # same reason as above (see the comment on extra_queue below).
        #
        # HwSettings itself is deliberately NOT resent here: GPS/Airspeed's
        # OptionalModules gate is only ever read once, in GPSInitialize()/
        # AirspeedInitialize() via MODULE_INITCALL, long before any UAVTalk
        # connection is possible - a write from here is far too late to
        # matter and is pios_board.c's job now (it sets OptionalModules
        # directly during boot, before MODULE_INITIALISE_ALL runs). Keeping
        # a redundant HwSettings write here was also a live suspect for an
        # intermittent GPS-task crash (a second write racing GPS's own
        # HwSettings-triggered callback on a different thread).
        client.send_object("RevoSettings", resolve_enum_values(db["RevoSettings"], REVOSETTINGS_DEFAULTS))
        time.sleep(0.2)
        client.send_object("HomeLocation", resolve_enum_values(db["HomeLocation"], HOMELOCATION_DEFAULTS))
        time.sleep(0.2)
        client.send_object("AirspeedSettings", resolve_enum_values(db["AirspeedSettings"], AIRSPEEDSETTINGS_DEFAULTS))
        time.sleep(0.2)
        client.send_object("MixerSettings", resolve_enum_values(db["MixerSettings"], mixer_settings()))
        time.sleep(0.2)
        # ActuatorSettings (Channel Min/Max/Neutral) is NOT sent from here -
        # a from-scratch investigation found writes to this specific object
        # never land over this link (isolated, byte-verified-correct packets
        # confirmed sent and confirmed never reaching the flight side's
        # UAVTalk state machine, for reasons not fully root-caused) even
        # though identical-pattern writes to every other settings object
        # here work fine. It's set directly in C instead, in simposix's
        # pios_board.c, at boot - see the comment there.

        # A trivial one-waypoint plan so PathPlan can clear regardless of
        # which flight mode is active (pathplanner.c checks its CRC every
        # cycle independent of the current mode) - Guidance itself still
        # only clears while actually flying a PathFollower-driven mode
        # (PositionHold etc, see the mode dropdown), since that alarm is
        # tied to FlightStatus.ControlChain, not to having a plan loaded.
        waypoint_values, pathaction_values, plan_crc = pathplan_setup(db)
        client.send_object("Waypoint", waypoint_values, inst_id=0)
        time.sleep(0.2)
        client.send_object("PathAction", pathaction_values, inst_id=0)
        time.sleep(0.2)
        client.send_object("PathPlan", {"WaypointCount": 1, "PathActionCount": 1, "Crc": plan_crc})
        time.sleep(0.2)  # let it land before control_loop starts streaming GCSReceiver
        configured["done"] = True

    # Sending two different UAVTalk objects back-to-back with no gap reliably
    # corrupts/drops one of them on this link (verified empirically). So all
    # writes/requests besides the continuous GCSReceiver stream go through
    # this queue, and the main loop always leaves a real gap around them
    # instead of firing them from separate threads at arbitrary times.
    extra_queue = []

    def queue_extra(name, values=None):
        extra_queue.append((name, values))

    def control_loop():
        last_arm_state = None
        last_stab1_modes = None
        last_watch_poll = 0.0
        watch_idx = 0
        while True:
            if configured["done"] and client.connected:
                snap = control.snapshot()
                armed = snap["armed"]
                stab1_modes = snap["stab1_modes"]
                if armed != last_arm_state or stab1_modes != last_stab1_modes:
                    fms = resolve_enum_values(db["FlightModeSettings"], flight_mode_settings(armed, stab1_modes))
                    queue_extra("FlightModeSettings", fms)
                    last_arm_state = armed
                    last_stab1_modes = stab1_modes

                now = time.time()
                if now - last_watch_poll > 0.3:
                    queue_extra(WATCHED_OBJECTS[watch_idx])
                    watch_idx = (watch_idx + 1) % len(WATCHED_OBJECTS)
                    last_watch_poll = now

                if extra_queue:
                    name, values = extra_queue.pop(0)
                    if values is None:
                        client.request_object(name)
                    else:
                        client.send_object(name, values)
                    time.sleep(0.2)  # let it land before anything else goes out
                else:
                    client.send_object("GCSReceiver", {"Channel": control.gcs_channels()})
            time.sleep(0.05)

    threading.Thread(target=control_loop, daemon=True).start()

    while True:
        try:
            client.run(on_object=on_object, on_connected=on_connected)
        except OSError:
            state.mark_disconnected()
            time.sleep(1.0)


PAGE = """<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>simposix board orientation</title>
<style>
  body { background: #202124; color: #e8eaed; font-family: -apple-system, sans-serif; margin: 0; padding: 24px; }
  h1 { font-weight: 500; font-size: 18px; opacity: 0.85; text-align: center; }
  .layout { display: flex; gap: 32px; flex-wrap: wrap; justify-content: center; align-items: flex-start; }
  #objtables-row { margin-top: 32px; }
  #objtables-row .panel { width: 300px; }
  .col { flex: 0 0 auto; }
  #boardcol { text-align: center; }
  #scene3d { width: 420px; height: 340px; border-radius: 8px; overflow: hidden; background: #16181a; }
  #scene3d canvas { display: block; }
  #modelstatus { font-size: 12px; opacity: 0.55; margin-top: 4px; min-height: 14px; }
  #readout { font-size: 15px; margin-top: 16px; opacity: 0.9; }
  #readout span { display: inline-block; min-width: 90px; }
  #desc { font-size: 14px; opacity: 0.6; margin-top: 4px; }
  #status { font-size: 12px; margin-top: 12px; }
  .ok { color: #81c995; }
  .bad { color: #f28b82; }
  .warn { color: #fdd663; }
  .panel { background: #292a2d; border-radius: 8px; padding: 16px 20px; width: 320px; }
  .panel h2 { font-size: 14px; opacity: 0.8; margin: 0 0 12px; font-weight: 600; }
  .slider-row { margin-bottom: 14px; }
  .slider-row label { display: flex; justify-content: space-between; font-size: 13px; opacity: 0.85; margin-bottom: 4px; }
  .slider-row input[type=range] { width: 100%; }
  .arm-row { display: flex; align-items: center; justify-content: space-between; margin-bottom: 14px; }
  .arm-row span { font-size: 13px; opacity: 0.85; }
  #armToggle { position: relative; width: 44px; height: 24px; border-radius: 12px; cursor: pointer; flex: 0 0 auto;
    background: #3c4043; user-select: none; transition: background 0.15s ease; }
  #armToggle.armed { background: #1e8e3e; }
  #armToggle .toggle-knob { position: absolute; top: 2px; left: 2px; width: 20px; height: 20px; border-radius: 50%;
    background: #ffffff; box-shadow: 0 1px 2px rgba(0,0,0,0.5); transition: left 0.15s ease; }
  #armToggle.armed .toggle-knob { left: calc(100% - 22px); }
  select { width: 100%; padding: 8px; border-radius: 6px; background: #3c4043; color: #e8eaed; border: none; font-size: 13px; }
  .axis-modes { display: flex; gap: 6px; }
  .axis-mode-col { flex: 1; min-width: 0; }
  .axis-mode-col span { display: block; font-size: 11px; opacity: 0.6; margin-bottom: 2px; text-align: center; }
  .axis-mode-col select { font-size: 11px; padding: 6px 2px; }
  table { width: 100%; border-collapse: collapse; font-size: 12px; }
  table caption { text-align: left; font-size: 13px; opacity: 0.8; margin: 14px 0 6px; font-weight: 600; }
  td { padding: 3px 4px; border-bottom: 1px solid #3c4043; vertical-align: top; word-break: break-word; }
  td.k { opacity: 0.65; white-space: nowrap; padding-right: 8px; }
  #alarms div { padding: 2px 0; }
  #healthsvg { width: 100%; background: #16181a; border-radius: 6px; overflow: hidden; }
  #healthsvg svg { width: 100%; height: auto; display: block; }
  #txrxsvg { width: 100%; background: #16181a; border-radius: 6px; overflow: hidden; }
  #txrxsvg svg { width: 100%; height: auto; display: block; }
  .outch-row { display: flex; align-items: center; gap: 8px; margin-bottom: 6px; font-size: 12px; }
  .outch-label { width: 42px; opacity: 0.65; flex: 0 0 auto; }
  .outch-track { position: relative; flex: 1 1 auto; height: 10px; background: #16181a; border-radius: 5px; overflow: hidden; }
  .outch-fill { position: absolute; top: 0; bottom: 0; left: 0; background: #8ab4f8; }
  .outch-center { position: absolute; top: -2px; bottom: -2px; left: 50%; width: 1px; background: #5f6368; }
  .outch-val { width: 44px; text-align: right; flex: 0 0 auto; opacity: 0.8; font-variant-numeric: tabular-nums; }
  .outch-row.idle .outch-fill { background: #3c4043; }
</style>
</head>
<body>
<h1>fw_simposix.elf &mdash; live board orientation</h1>
<div class="layout">

  <div class="panel">
    <h2>Controls</h2>
    <div class="arm-row">
      <span>Motors Armed</span>
      <div id="armToggle" role="switch" aria-checked="false" tabindex="0">
        <div class="toggle-knob"></div>
      </div>
    </div>
    <div class="slider-row">
      <label>Flight mode</label>
      <select id="mode">
        <option value="0">Stabilized1</option>
        <option value="1">Stabilized2</option>
        <option value="2">Stabilized3</option>
        <option value="3">PositionHold</option>
      </select>
    </div>
    <div class="slider-row">
      <label>Stabilized1 axes</label>
      <div class="axis-modes">
        <div class="axis-mode-col"><span>Roll</span><select id="stab1Roll">__STAB_ROLL_OPTIONS__</select></div>
        <div class="axis-mode-col"><span>Pitch</span><select id="stab1Pitch">__STAB_PITCH_OPTIONS__</select></div>
        <div class="axis-mode-col"><span>Yaw</span><select id="stab1Yaw">__STAB_YAW_OPTIONS__</select></div>
      </div>
    </div>
    <div class="slider-row"><label>Throttle <span id="throttlev">0</span></label>
      <input type="range" id="throttle" min="0" max="1" step="0.02" value="0"></div>
    <div class="slider-row"><label>Roll disturbance <span id="rollv">0</span></label>
      <input type="range" id="roll" min="-1" max="1" step="0.02" value="0"></div>
    <div class="slider-row"><label>Pitch disturbance <span id="pitchv">0</span></label>
      <input type="range" id="pitch" min="-1" max="1" step="0.02" value="0"></div>
    <div class="slider-row"><label>Yaw disturbance <span id="yawv">0</span></label>
      <input type="range" id="yaw" min="-1" max="1" step="0.02" value="0"></div>
  </div>

  <div id="boardcol" class="col">
    <div id="scene3d"></div>
    <div id="modelstatus">loading 3D model...</div>
    <div id="readout">
      <span>Roll: <b id="rroll">-</b></span>
      <span>Pitch: <b id="rpitch">-</b></span>
      <span>Yaw: <b id="ryaw">-</b></span>
    </div>
    <div id="desc">Waiting for AttitudeState...</div>
    <div id="status" class="bad">not connected</div>
  </div>

  <div class="panel">
    <h2>System Health</h2>
    <div id="healthsvg"></div>
    <h2 style="margin-top:16px">Telemetry</h2>
    <div id="txrxsvg"></div>
    <div id="alarms"></div>
  </div>

  <div class="panel">
    <h2>Output Channels</h2>
    <div style="font-size:11px; opacity:0.55; margin-bottom:10px">ActuatorCommand - post-mixer PWM, where the Stabilization loop's correction actually lands</div>
    <div id="outputch"></div>
  </div>

</div>

<div class="layout" id="objtables-row"></div>

<script src="https://unpkg.com/three@0.128.0/build/three.min.js"></script>
<script src="https://unpkg.com/three@0.128.0/examples/js/loaders/TDSLoader.js"></script>
<script>
// The GCS's own modelview gadget shows this exact mesh - a real 3D model,
// not a photo - and rotates it live from AttitudeState's quaternion. Reuse
// the same asset here instead of approximating it with a CSS box.
let modelRoot = null;
let targetQuat = new THREE.Quaternion();
let haveTarget = false;

const scene3dEl = document.getElementById("scene3d");
const renderer = new THREE.WebGLRenderer({antialias: true, alpha: true});
renderer.setSize(scene3dEl.clientWidth, scene3dEl.clientHeight);
renderer.setPixelRatio(window.devicePixelRatio || 1);
scene3dEl.appendChild(renderer.domElement);

const scene3d = new THREE.Scene();
const camera3d = new THREE.PerspectiveCamera(35, scene3dEl.clientWidth / scene3dEl.clientHeight, 0.1, 100);
camera3d.position.set(0, 3.4, 5.6);
camera3d.lookAt(0, 0.3, 0);

scene3d.add(new THREE.AmbientLight(0xffffff, 0.55));
const dirLight1 = new THREE.DirectionalLight(0xffffff, 0.9);
dirLight1.position.set(3, 5, 2);
scene3d.add(dirLight1);
const dirLight2 = new THREE.DirectionalLight(0xffffff, 0.35);
dirLight2.position.set(-3, 2, -2);
scene3d.add(dirLight2);

modelRoot = new THREE.Group();
scene3d.add(modelRoot);

// This particular .3ds file has one corrupted vertex in its "board" mesh
// (coordinate in the hundreds of trillions - a bad chunk somewhere in a
// 20-year-old export, verified by dumping the raw position buffer). A plain
// Box3.setFromObject() bounding box is dominated by that single outlier and
// collapses the computed scale to ~0. Trim outliers by percentile instead of
// trusting min/max so the one bad vertex can't wreck the fit - the mesh
// itself is left untouched, so any degenerate triangle through that vertex
// just ends up far outside the camera's far plane and is naturally clipped.
function robustBox(root) {
  const xs = [], ys = [], zs = [];
  root.traverse((c) => {
    if (c.isMesh && c.geometry && c.geometry.attributes.position) {
      const pos = c.geometry.attributes.position;
      for (let i = 0; i < pos.count; i++) {
        xs.push(pos.getX(i)); ys.push(pos.getY(i)); zs.push(pos.getZ(i));
      }
    }
  });
  const pct = (arr, p) => {
    const s = arr.slice().sort((a, b) => a - b);
    return s[Math.max(0, Math.min(s.length - 1, Math.floor(s.length * p)))];
  };
  return new THREE.Box3(
    new THREE.Vector3(pct(xs, 0.01), pct(ys, 0.01), pct(zs, 0.01)),
    new THREE.Vector3(pct(xs, 0.99), pct(ys, 0.99), pct(zs, 0.99))
  );
}

const modelStatusEl = document.getElementById("modelstatus");
new THREE.TDSLoader().load("/models/Revolution.3DS", (obj) => {
  const box = robustBox(obj);
  const size = new THREE.Vector3();
  box.getSize(size);
  const center = new THREE.Vector3();
  box.getCenter(center);
  const scale = 2.4 / Math.max(size.x, size.y, size.z, 1e-6);
  obj.position.sub(center);
  const inner = new THREE.Group();
  inner.add(obj);
  inner.scale.setScalar(scale);
  // The raw .3ds mesh's own axes don't come in level/Y-up - at the live
  // attitude's identity quaternion the model was sitting tilted, not flat.
  // This fixed mounting correction defines what "identity" looks like
  // before the live quaternion rotates from there.
  inner.rotation.x = -Math.PI / 2;
  modelRoot.add(inner);

  new THREE.TextureLoader().load("/models/TEXTURE.PNG", (tex) => {
    obj.traverse((child) => {
      if (child.isMesh && child.material) {
        child.material.map = tex;
        child.material.needsUpdate = true;
      }
    });
  });
  modelStatusEl.textContent = "";
}, undefined, (err) => {
  modelStatusEl.textContent = "failed to load 3D model - see console";
  console.error(err);
});

function setTargetQuat(q) {
  // q = [q1,q2,q3,q4] = [w,x,y,z] in flight-code convention, where q2/q3/q4
  // are the roll/pitch/yaw axis components respectively. The GCS's own
  // ModelViewGadgetWidget mapping (x=q3,y=q2,z=q4,w=q1) doesn't hold for
  // this scene's camera/mounting setup - verified by hand: with that
  // mapping, a pure-roll quaternion produces a rotation about this scene's
  // vertical (Y) axis, which reads as yaw/spin, not banking, and pure yaw
  // produces a Z-axis rotation, which reads as banking, not spin - roll and
  // yaw were swapped. Pitch (q3 -> Three.js X) was already correct, which
  // is why only-pitch input always looked right on its own. Put roll on Z
  // (banks, verified) and yaw on Y (spins, verified) instead.
  targetQuat.set(q[2], q[3], q[1], q[0]);
  haveTarget = true;
}

function animate3d() {
  requestAnimationFrame(animate3d);
  if (haveTarget) modelRoot.quaternion.slerp(targetQuat, 0.3);
  renderer.render(scene3d, camera3d);
}
animate3d();

// System Health gadget and telemetry Tx/Rx meter - both lifted directly
// from the GCS's own SVG assets (per-state layers toggled by element id,
// same trick the real GCS's QSvgRenderer uses, just done with plain DOM
// visibility here instead of Qt's render-by-id).
function autoCropViewBox(svg) {
  // These SVGs were authored full-page in Inkscape with the actual gadget
  // artwork occupying a small corner of a much larger canvas. Fit the
  // viewBox to the rendered content's real bounding box instead of hauling
  // all that blank canvas into a small panel.
  try {
    const box = svg.getBBox();
    if (box.width > 0 && box.height > 0) {
      const pad = Math.max(box.width, box.height) * 0.03;
      svg.setAttribute("viewBox",
        (box.x - pad) + " " + (box.y - pad) + " " + (box.width + pad * 2) + " " + (box.height + pad * 2));
    }
  } catch (e) { /* getBBox can throw if the svg isn't in a rendered document yet */ }
}

const ALARM_STATE_SUFFIXES = ["OK", "Warning", "Critical", "Error"];
let healthSvgRoot = null;
fetch("/diagrams/system-health.svg").then(r => r.text()).then(svgText => {
  const container = document.getElementById("healthsvg");
  container.innerHTML = svgText;
  healthSvgRoot = container.querySelector("svg");
  if (healthSvgRoot) {
    healthSvgRoot.removeAttribute("width");
    healthSvgRoot.removeAttribute("height");
    // Two cells in the I/O row past TELEMETRY (ids "rect-1"/"rect-2" -
    // auto-generated, unlike every real alarm box's deliberate name) were
    // never wired to any SystemAlarms field even in the original GCS.
    // They're already the plain dark "uninitialised" fill and nothing here
    // ever targets those ids to light them up, so they stay inert/blacked
    // out on their own - no action needed. The stray "?" is different: a
    // leftover glyph sitting in the locked decorative Foreground layer
    // (not in any per-alarm state group) that visibly overlaps the grid
    // and reads as a status indicator when it isn't one - hide just that.
    healthSvgRoot.querySelectorAll("text").forEach((t) => {
      if (t.textContent.trim() === "?") t.style.display = "none";
    });
    // These three map to SystemAlarms.ExtendedAlarmStatus (a separate
    // field this tool never populates), not the base Alarm level, and are
    // authoring bugs in the source asset itself: two of the three <g>
    // layers have no display:none default at all (only
    // UnsupportedConfig_OneShot does), so they render permanently visible
    // regardless of live data, stacked on top of each other at the same
    // position - whichever is drawn last (FlightMode) wins and shows red
    // by default on every load. Hide all three explicitly.
    for (const id of ["BootFault-RebootRequired", "SystemConfiguration-BadThrottleOrCollectiveInputRange", "SystemConfiguration-FlightMode"]) {
      const el = healthSvgRoot.getElementById ? healthSvgRoot.getElementById(id) : null;
      if (el && el.parentElement) el.parentElement.style.display = "none";
    }
    autoCropViewBox(healthSvgRoot);
  }
}).catch(() => {
  document.getElementById("healthsvg").textContent = "(system-health.svg not available)";
});

let txrxSvgRoot = null;
let txNodes = [], rxNodes = [];
fetch("/telemetry-img/tx-rx.svg").then(r => r.text()).then(svgText => {
  const container = document.getElementById("txrxsvg");
  container.innerHTML = svgText;
  txrxSvgRoot = container.querySelector("svg");
  if (!txrxSvgRoot) return;
  txrxSvgRoot.removeAttribute("width");
  txrxSvgRoot.removeAttribute("height");
  // The tx/rx "lit segment" layers are authored offset by translate(0,-100)
  // from their _bg track counterparts - the original Qt widget compensates
  // for this itself when it positions each QGraphicsSvgItem by hand. Reset
  // it here so the lit segments land directly on top of their tracks.
  for (const gid of ["tx", "rx"]) {
    const g = txrxSvgRoot.querySelector("#" + gid);
    if (g) g.removeAttribute("transform");
  }
  autoCropViewBox(txrxSvgRoot);
  for (let i = 0; ; i++) {
    const el = txrxSvgRoot.querySelector("#tx" + i);
    if (!el) break;
    txNodes.push(el);
  }
  for (let i = 0; ; i++) {
    const el = txrxSvgRoot.querySelector("#rx" + i);
    if (!el) break;
    rxNodes.push(el);
  }
}).catch(() => {
  document.getElementById("txrxsvg").textContent = "(tx-rx.svg not available)";
});

function updateHealthSvg(alarmsFull) {
  if (!healthSvgRoot || !alarmsFull) return;
  for (const a of alarmsFull) {
    for (const suf of ALARM_STATE_SUFFIXES) {
      const el = healthSvgRoot.getElementById ? healthSvgRoot.getElementById(a.name + "-" + suf)
                                                : healthSvgRoot.querySelector("#" + CSS.escape(a.name + "-" + suf));
      if (el && el.parentElement) {
        el.parentElement.style.display = (suf === a.level) ? "inline" : "none";
      }
    }
  }
}

function updateTxRx(txRate, rxRate) {
  if (!txrxSvgRoot) return;
  const maxV = 1200;
  const txIdx = Math.max(0, Math.min(txNodes.length, Math.round((txRate / maxV) * txNodes.length)));
  const rxIdx = Math.max(0, Math.min(rxNodes.length, Math.round((rxRate / maxV) * rxNodes.length)));
  txNodes.forEach((n, i) => n.style.display = i < txIdx ? "inline" : "none");
  rxNodes.forEach((n, i) => n.style.display = i < rxIdx ? "inline" : "none");
  let label = document.getElementById("txrxLabel");
  if (!label) {
    label = document.createElement("div");
    label.id = "txrxLabel";
    label.style.cssText = "font-size:11px;opacity:0.6;margin-top:4px;text-align:center;";
    document.getElementById("txrxsvg").after(label);
  }
  label.textContent = "Tx: " + txRate.toFixed(0) + " B/s   Rx: " + rxRate.toFixed(0) + " B/s";
}

let dragging = {roll:false, pitch:false, yaw:false};

function postControl(fields) {
  fetch("/control", {method: "POST", headers: {"Content-Type": "application/json"}, body: JSON.stringify(fields)});
}

const armToggle = document.getElementById("armToggle");
function setArmToggleVisual(armed) {
  armToggle.className = armed ? "armed" : "";
  armToggle.setAttribute("aria-checked", armed ? "true" : "false");
}
function toggleArmed() {
  const wantArmed = armToggle.className !== "armed";
  // Optimistic update: flip the switch immediately instead of waiting for a
  // poll to confirm - actually arming/disarming on the flight side and
  // seeing it echoed back takes a few hundred ms, and without this the
  // toggle looked unresponsive enough that it read as needing two clicks.
  setArmToggleVisual(wantArmed);
  postControl({armed: wantArmed});
}
armToggle.onclick = toggleArmed;
armToggle.onkeydown = (e) => {
  if (e.key === " " || e.key === "Enter") { e.preventDefault(); toggleArmed(); }
};

document.getElementById("mode").onchange = (e) => {
  postControl({mode_position: parseInt(e.target.value, 10)});
};

function sendStab1Modes() {
  postControl({stab1_modes: [
    document.getElementById("stab1Roll").value,
    document.getElementById("stab1Pitch").value,
    document.getElementById("stab1Yaw").value,
  ]});
}
document.getElementById("stab1Roll").onchange = sendStab1Modes;
document.getElementById("stab1Pitch").onchange = sendStab1Modes;
document.getElementById("stab1Yaw").onchange = sendStab1Modes;

const throttleEl = document.getElementById("throttle");
const throttleLabel = document.getElementById("throttlev");
throttleEl.addEventListener("input", () => {
  // Unlike the disturbance sliders this is a real throttle stick, not a
  // spring-loaded "push then let go" control - it stays where you leave it.
  throttleLabel.textContent = parseFloat(throttleEl.value).toFixed(2);
  postControl({throttle: parseFloat(throttleEl.value)});
});

for (const axis of ["roll", "pitch", "yaw"]) {
  const el = document.getElementById(axis);
  const label = document.getElementById(axis + "v");
  const send = () => {
    label.textContent = parseFloat(el.value).toFixed(2);
    postControl({disturbance: {[axis]: parseFloat(el.value)}});
  };
  el.addEventListener("input", send);
  el.addEventListener("mousedown", () => dragging[axis] = true);
  el.addEventListener("touchstart", () => dragging[axis] = true);
  window.addEventListener("mouseup", () => {
    if (dragging[axis]) { dragging[axis] = false; el.value = 0; send(); }
  });
  window.addEventListener("touchend", () => {
    if (dragging[axis]) { dragging[axis] = false; el.value = 0; send(); }
  });
}

function updateOutputChannels(channels) {
  // PWM channels idle at 1500us neutral when nothing is mixed to them (same
  // convention as GCSReceiver) - fill left-to-right over the standard
  // 1000-2000us servo/ESC range, with a tick at the 1500us center so a
  // channel sitting dead-center reads as visibly idle rather than "half".
  const el = document.getElementById("outputch");
  let html = "";
  for (let i = 0; i < channels.length; i++) {
    const us = channels[i];
    const pct = Math.max(0, Math.min(100, (us - 1000) / 1000 * 100));
    const idle = Math.abs(us - 1500) < 2;
    html += "<div class='outch-row" + (idle ? " idle" : "") + "'>" +
      "<div class='outch-label'>Ch " + i + "</div>" +
      "<div class='outch-track'><div class='outch-fill' style='width:" + pct + "%'></div>" +
      "<div class='outch-center'></div></div>" +
      "<div class='outch-val'>" + us + "</div></div>";
  }
  el.innerHTML = html;
}

function renderTable(name, obj) {
  let html = "<table><caption>" + name + "</caption>";
  for (const k in obj) {
    let v = obj[k];
    if (Array.isArray(v)) v = v.map(x => (typeof x === "number") ? x.toFixed(2) : x).join(", ");
    else if (typeof v === "number") v = v.toFixed(3);
    html += "<tr><td class='k'>" + k + "</td><td>" + v + "</td></tr>";
  }
  return html + "</table>";
}

// Fixed left-to-right order for the bottom row, independent of whatever
// order the objects happen to arrive from the server in.
const OBJTABLE_ORDER = ["FlightTelemetryStats", "RateDesired", "ActuatorDesired", "StabilizationDesired", "FlightStatus"];

function renderGPSPanel(gps) {
  // Latitude/Longitude are int32 degrees x 10^-7 on the wire - raw they're
  // an unreadable huge integer, not a coordinate.
  const lat = (gps.Latitude / 1e7).toFixed(7);
  const lon = (gps.Longitude / 1e7).toFixed(7);
  let html = "<table><caption>GPSPositionSensor</caption>";
  html += "<tr><td class='k'>Status</td><td>" + gps.Status + "</td></tr>";
  html += "<tr><td class='k'>Latitude</td><td>" + lat + "&deg;</td></tr>";
  html += "<tr><td class='k'>Longitude</td><td>" + lon + "&deg;</td></tr>";
  html += "<tr><td class='k'>Altitude</td><td>" + gps.Altitude.toFixed(2) + " m</td></tr>";
  html += "<tr><td class='k'>Heading</td><td>" + gps.Heading.toFixed(1) + "&deg;</td></tr>";
  html += "<tr><td class='k'>Groundspeed</td><td>" + gps.Groundspeed.toFixed(2) + " m/s</td></tr>";
  html += "<tr><td class='k'>Satellites</td><td>" + gps.Satellites + "</td></tr>";
  html += "<tr><td class='k'>PDOP</td><td>" + gps.PDOP.toFixed(2) + "</td></tr>";
  html += "<tr><td class='k'>HDOP</td><td>" + gps.HDOP.toFixed(2) + "</td></tr>";
  html += "<tr><td class='k'>VDOP</td><td>" + gps.VDOP.toFixed(2) + "</td></tr>";
  return html + "</table>";
}

async function poll() {
  try {
    const r = await fetch("/state.json");
    const s = await r.json();
    document.getElementById("rroll").textContent = s.roll.toFixed(1) + "\\u00b0";
    document.getElementById("rpitch").textContent = s.pitch.toFixed(1) + "\\u00b0";
    document.getElementById("ryaw").textContent = s.yaw.toFixed(1) + "\\u00b0";
    document.getElementById("desc").textContent = s.description;
    const st = document.getElementById("status");
    st.textContent = s.connected ? "connected" : "not connected";
    st.className = s.connected ? "ok" : "bad";

    // Drive the real 3D model's rotation from the raw quaternion (same
    // approach ModelViewGadgetWidget::updateAttitude uses), not from
    // separately-composed roll/pitch/yaw CSS rotations - composing three
    // ordered axis rotations is inherently coupled (rotating "roll" first
    // changes what "pitch" even means for the next rotation), which is
    // exactly the two-faces-moving-at-once artifact. A single quaternion
    // has no such ordering problem.
    if (s.q) setTargetQuat(s.q);

    const fs = s.objects && s.objects.FlightStatus;
    if (fs) {
      const isArmed = fs.Armed === "Armed" || fs.Armed === "Arming";
      setArmToggleVisual(isArmed);
      armToggle.title = fs.Armed;
    }

    updateHealthSvg(s.alarms_full);
    const fts = s.objects && s.objects.FlightTelemetryStats;
    if (fts) updateTxRx(fts.TxDataRate || 0, fts.RxDataRate || 0);

    if (s.actuator_command) updateOutputChannels(s.actuator_command.Channel);

    const alarmsEl = document.getElementById("alarms");
    if (s.alarms && s.alarms.length) {
      alarmsEl.innerHTML = s.alarms.map(a =>
        "<div class='" + (a.level === "Critical" || a.level === "Error" ? "bad" : "warn") + "'>" +
        a.name + ": " + a.level + "</div>").join("");
    } else {
      alarmsEl.innerHTML = "<div class='ok'>No active alarms</div>";
    }

    const tablesRow = document.getElementById("objtables-row");
    let html = "";
    for (const name of OBJTABLE_ORDER) {
      if (s.objects && s.objects[name]) html += "<div class='panel'>" + renderTable(name, s.objects[name]) + "</div>";
      if (name === "FlightStatus" && s.gps) html += "<div class='panel'>" + renderGPSPanel(s.gps) + "</div>";
    }
    tablesRow.innerHTML = html;
  } catch (e) {
    // server not up yet - keep trying
  }
  setTimeout(poll, 100);
}
poll();
</script>
</body>
</html>
"""


def _stab_mode_options_html(selected):
    return "".join(
        '<option value="%s"%s>%s</option>' % (m, ' selected' if m == selected else '', m)
        for m in STABILIZATION_MODE_OPTIONS
    )


PAGE = (PAGE
        .replace("__STAB_ROLL_OPTIONS__", _stab_mode_options_html("Attitude"))
        .replace("__STAB_PITCH_OPTIONS__", _stab_mode_options_html("Attitude"))
        .replace("__STAB_YAW_OPTIONS__", _stab_mode_options_html("AxisLock")))


def make_handler(state, control):
    class Handler(http.server.BaseHTTPRequestHandler):
        def log_message(self, fmt, *args):
            pass  # keep the console quiet

        def do_GET(self):
            if self.path == "/" or self.path.startswith("/?"):
                body = PAGE.encode("utf-8")
                self.send_response(200)
                self.send_header("Content-Type", "text/html; charset=utf-8")
                self.send_header("Content-Length", str(len(body)))
                self.end_headers()
                self.wfile.write(body)
            elif self.path == "/state.json":
                body = json.dumps(state.snapshot()).encode("utf-8")
                self.send_response(200)
                self.send_header("Content-Type", "application/json")
                self.send_header("Content-Length", str(len(body)))
                self.send_header("Cache-Control", "no-store")
                self.end_headers()
                self.wfile.write(body)
            elif self.path.startswith("/images/"):
                safe_name = os.path.basename(self.path.split("?", 1)[0])
                path = os.path.join(IMAGES_DIR, safe_name)
                if not os.path.isfile(path):
                    self.send_error(404)
                    return
                with open(path, "rb") as f:
                    body = f.read()
                self.send_response(200)
                self.send_header("Content-Type", "image/png")
                self.send_header("Content-Length", str(len(body)))
                self.end_headers()
                self.wfile.write(body)
            elif self.path.startswith("/models/"):
                safe_name = os.path.basename(self.path.split("?", 1)[0])
                path = os.path.join(MODEL_DIR, safe_name)
                if not os.path.isfile(path):
                    self.send_error(404)
                    return
                with open(path, "rb") as f:
                    body = f.read()
                self.send_response(200)
                self.send_header("Content-Type", "application/octet-stream")
                self.send_header("Content-Length", str(len(body)))
                self.end_headers()
                self.wfile.write(body)
            elif self.path.startswith("/diagrams/"):
                safe_name = os.path.basename(self.path.split("?", 1)[0])
                path = os.path.join(DIAGRAM_DIR, safe_name)
                if not os.path.isfile(path):
                    self.send_error(404)
                    return
                with open(path, "rb") as f:
                    body = f.read()
                self.send_response(200)
                self.send_header("Content-Type", "image/svg+xml")
                self.send_header("Content-Length", str(len(body)))
                self.end_headers()
                self.wfile.write(body)
            elif self.path.startswith("/telemetry-img/"):
                safe_name = os.path.basename(self.path.split("?", 1)[0])
                path = os.path.join(TELEMETRY_IMG_DIR, safe_name)
                if not os.path.isfile(path):
                    self.send_error(404)
                    return
                with open(path, "rb") as f:
                    body = f.read()
                self.send_response(200)
                self.send_header("Content-Type", "image/svg+xml")
                self.send_header("Content-Length", str(len(body)))
                self.end_headers()
                self.wfile.write(body)
            else:
                self.send_error(404)

        def do_POST(self):
            if self.path != "/control":
                self.send_error(404)
                return
            length = int(self.headers.get("Content-Length", 0))
            try:
                fields = json.loads(self.rfile.read(length) or b"{}")
            except (ValueError, TypeError):
                self.send_error(400)
                return
            control.update(fields)
            self.send_response(204)
            self.end_headers()

    return Handler


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--host", default="127.0.0.1", help="simposix telemetry UDP host (default 127.0.0.1)")
    ap.add_argument("--port", type=int, default=9000, help="simposix telemetry UDP port (default 9000)")
    ap.add_argument("--http-port", type=int, default=8765, help="local web page port (default 8765)")
    ap.add_argument("--xml-dir", default=default_xml_dir(), help="path to shared/uavobjectdefinition")
    ap.add_argument("--open", action="store_true", help="open the page in a browser on startup")
    args = ap.parse_args()

    if not os.path.isdir(IMAGES_DIR):
        raise SystemExit("Can't find calibration images at %s" % IMAGES_DIR)

    state = SharedState()
    control = ControlState()
    t = threading.Thread(target=uavtalk_thread, args=(state, control, args.host, args.port, args.xml_dir), daemon=True)
    t.start()

    server = http.server.ThreadingHTTPServer(("127.0.0.1", args.http_port), make_handler(state, control))
    url = "http://127.0.0.1:%d" % args.http_port
    print("Serving board orientation viewer at %s" % url)
    print("Talking UDP to %s:%d for AttitudeState" % (args.host, args.port))
    if args.open:
        webbrowser.open(url)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass


if __name__ == "__main__":
    main()
