#!/usr/bin/env python3
"""flight_config.py - flight configuration shared by the bridge and tools.

This is what remains of board_orientation_viz.py, whose VIEWER was removed.
That viewer opened a second UAVTalk client on the SAME UDP telemetry port
as the Gazebo bridge. The firmware answers whichever client contacted it
last, so the two silently stole each other's packets: missions that flew
fine alone failed with runaways and ground contact whenever the viewer was
open, and the cause is invisible in the flight logs - it reads as a control
bug. Three consecutive runs were lost to it.

Nothing here opens a socket. It is configuration data plus the helpers that
turn it into UAVObject field values.
"""
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

FLIGHT_MODE_NUMBER = 5  # Stabilized1 (configurable), Stabilized2/3 (presets), PositionHold, PathPlanner
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
    "FlightModePosition": ["Stabilized1", "Stabilized2", "Stabilized3", "PositionHold", "PathPlanner", "Stabilized6"],
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
