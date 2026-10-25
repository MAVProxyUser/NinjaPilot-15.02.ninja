#!/usr/bin/env python3
"""
flight_monitor - passive telemetry recorder + live watch for a REAL flight.

Connects to the board over UDP as the ONE UAVTalk client (close the GCS
before launching this - the firmware latches a single UDP peer, and two
clients silently steal each other's replies; that trap has burned this
project before). Then it mostly LISTENS: the flight side already pushes
AttitudeState at 25Hz, ManualControlCommand at 4Hz, SystemAlarms on
change, SystemStats at 1Hz. A gentle round-robin poll (one single-frame
request every 150ms, never back-to-back) fills in the objects telemetry
does not push: FlightStatus, StabilizationDesired, RateDesired,
ActuatorDesired, ActuatorCommand, GyroState.

Everything received is recorded to ~/NinjaPilot-logs/flightmon_<ts>.jsonl
with wall-clock timestamps, and a 1Hz status line shows the flight live.
When an alarm is raised, the objects that explain it (ALARM_CONTEXT, e.g.
Attitude -> AttitudeState/GyroState/AccelState/AttitudeSettings) are pulled at
once and every 5 s while it stays up, printed as CTX lines and logged in full:
arm state, mode, attitude, throttle, worst alarm, packet rate, and LINK
STALL warnings whenever the AttitudeState stream gaps >1s (the signature
of WiFi trouble, distinct from anything the vehicle does).

Usage:
    python3 flight_monitor.py [--host 192.168.0.45] [--port 9000]

Fly, land, disarm, then Ctrl+C: a post-flight summary prints arm/disarm
events, every alarm transition, attitude extremes, and stall windows.
The jsonl holds the full record for deeper analysis.
"""

import argparse
import json
import math
import os
import select
import socket
import sys
import time

_HERE = os.path.dirname(os.path.abspath(__file__))
NINJAPILOT_ROOT = os.environ.get(
    "NINJAPILOT_ROOT",
    os.path.abspath(os.path.join(_HERE, "..", "..", "NinjaPilot-15.02.ninja")))
_PYUAVTALK = os.path.join(NINJAPILOT_ROOT, "ground", "pyuavtalk")
if not os.path.isdir(_PYUAVTALK):
    sys.exit("pyuavtalk not found at %s (set NINJAPILOT_ROOT)" % _PYUAVTALK)
sys.path.insert(0, _PYUAVTALK)
import uavtalk  # noqa: E402

GCS_DISCONNECTED, GCS_HANDSHAKEREQ, GCS_HANDSHAKEACK, GCS_CONNECTED = 0, 1, 2, 3

# One request per POLL_GAP, cycling this list: ~6.7 single frames per second
# total - far below anything that could crowd the telemetry loop, and never
# two sends back-to-back (that corrupts/drops one; learned the hard way).
POLL_OBJECTS = ["FlightStatus", "StabilizationDesired", "RateDesired",
                "ActuatorDesired", "ActuatorCommand", "GyroState"]
POLL_GAP = 0.15

ALARM_NAMES = ["SystemConfiguration", "BootFault", "OutOfMemory", "StackOverflow",
               "CPUOverload", "EventSystem", "Telemetry", "Receiver", "ManualControl",
               "Actuator", "Attitude", "Sensors", "Magnetometer", "Airspeed",
               "Stabilization", "Guidance", "PathPlan", "Battery", "FlightTime",
               "I2C", "GPS"]
ALARM_RANK = {"OK": 0, "Uninitialised": 0, "Warning": 1, "Error": 2, "Critical": 3}

# When an alarm is raised (and every ALARM_CTX_PERIOD while it stays up), pull
# the objects that explain it, one frame per POLL_GAP ahead of the round-robin.
# Each arrives as a CTX line on screen and as a full record in the jsonl, so a
# post-flight read has the evidence next to the alarm instead of a name only.
ALARM_CONTEXT = {
    "SystemConfiguration": ["SystemSettings", "MixerSettings", "HwSettings", "ManualControlSettings"],
    "BootFault": ["SystemStats", "FirmwareIAPObj", "GyroState", "AccelState"],
    "OutOfMemory": ["SystemStats", "TaskInfo"],
    "StackOverflow": ["SystemStats", "TaskInfo"],
    "CPUOverload": ["SystemStats", "TaskInfo", "CallbackInfo"],
    "EventSystem": ["SystemStats", "TaskInfo"],
    "Telemetry": ["FlightTelemetryStats", "GCSTelemetryStats"],
    "Receiver": ["ManualControlCommand", "ManualControlSettings", "GCSReceiver", "ReceiverActivity"],
    "ManualControl": ["ManualControlCommand", "ManualControlSettings", "FlightStatus", "FlightModeSettings"],
    "Actuator": ["ActuatorCommand", "ActuatorDesired", "ActuatorSettings", "MixerStatus"],
    "Attitude": ["AttitudeState", "GyroState", "AccelState", "AttitudeSettings", "SystemStats"],
    "Sensors": ["GyroSensor", "AccelSensor", "GyroState", "AccelState"],
    "Magnetometer": ["MagState", "MagSensor"],
    "Airspeed": ["AirspeedSensor", "AirspeedState"],
    "Stabilization": ["StabilizationDesired", "StabilizationStatus", "RateDesired", "ActuatorDesired",
                      "AttitudeState", "GyroState", "StabilizationSettings"],
    "Guidance": ["PathDesired", "PathStatus", "VelocityState", "PositionState", "VelocityDesired"],
    "PathPlan": ["PathPlan", "PathStatus", "WaypointActive", "PathAction"],
    "Battery": ["FlightBatteryState", "FlightBatterySettings"],
    "FlightTime": ["FlightStatus", "FlightBatteryState"],
    "I2C": ["I2CStats"],
    "GPS": ["GPSPositionSensor", "GPSSatellites", "GPSTime"],
}
ALARM_CTX_PERIOD = 5.0

# ---------------------------------------------------------------------------
# Preflight: confirm the board is configured the way the 2026-09-01
# investigation says it must be, BEFORE takeoff. Every check encodes a
# lesson that was paid for in a crash or a debugging afternoon.
# ---------------------------------------------------------------------------

PREFLIGHT_OBJECTS = ["FirmwareIAPObj", "MixerSettings", "ActuatorSettings",
                     "FlightModeSettings", "StabilizationSettingsBank1",
                     "ManualControlSettings", "SystemSettings", "AttitudeSettings",
                     "GyroState", "SystemAlarms"]

# Build time of the firmware that first carried the 41Hz gyro DLPF (and the
# GCS receiver binding). The DLPF was believed to be the 2026-09-01 flip fix;
# the real cause was the IMU mounted yaw-180 (see the BoardRotation check
# below). The 41Hz filter stays as good practice for a 4-inch frame.
DLPF_FIX_BUILD_UNIX = 1788044400  # 2026-09-01 ~17:00 local

QUADX_MIXER = {1: [64, 64, -64], 2: [-64, 64, 64], 3: [-64, -64, -64], 4: [64, -64, 64]}


def _local_uavo_sha():
    """sha1 over the XML dir, byte-identical to make/scripts/version-info.py's
    get_hash_of_dirs (sorted walk, file bytes only)."""
    import hashlib
    d = os.path.join(NINJAPILOT_ROOT, "shared", "uavobjectdefinition")
    if not os.path.isdir(d):
        return None
    h = hashlib.sha1()
    for root, dirs, files in os.walk(d):
        files.sort()
        for name in files:
            try:
                fh = hashlib.sha1()
                with open(os.path.join(root, name), "rb") as f:
                    while True:
                        buf = f.read(4096)
                        if not buf:
                            break
                        fh.update(buf)
                # the original folds each file's HEX digest into the
                # cumulative hash, not the file bytes - match it exactly
                h.update(fh.hexdigest().encode("utf-8"))
            except OSError:
                return None
    return h.hexdigest()


def run_preflight(cfg):
    """cfg: dict name->decoded object. Returns list of (level, name, detail);
    level in OK/WARN/FAIL."""
    import struct as _struct
    out = []

    def add(level, name, detail):
        out.append((level, name, detail))

    fw = cfg.get("FirmwareIAPObj")
    if fw:
        ok_id = fw.get("BoardType") == 18 and fw.get("BoardRevision") == 2
        add("OK" if ok_id else "FAIL", "board identity",
            "type 0x%02X rev %d (ESP32 Thing Plus)" % (fw.get("BoardType", 0), fw.get("BoardRevision", 0)))
        desc = bytes(bytearray(int(b) & 0xFF for b in fw.get("Description", [])[:100]))
        if desc[:4] == b"OpFw":
            btime = _struct.unpack_from("<I", desc, 8)[0]
            when = time.strftime("%Y-%m-%d %H:%M", time.localtime(btime))
            board_uavo = desc[60:80].hex()
            local_uavo = _local_uavo_sha()
            # Two independent proofs of currency: a build stamp after the
            # DLPF fix landed, OR a UAVO-set hash matching this tree (any
            # firmware built from the current tree carries today's XML
            # changes, which postdate the fix). The posix sim stamps
            # commit-time rather than build-time, so it needs the second.
            if btime >= DLPF_FIX_BUILD_UNIX or (local_uavo and board_uavo == local_uavo):
                add("OK", "firmware age", "built %s (has the 41Hz DLPF vibration fix)" % when)
            else:
                add("FAIL", "firmware age",
                    "built %s, UAVO set %s... != tree %s... - PREDATES the 41Hz DLPF fix; "
                    "this is the firmware that flips. Flash firmware_normal_41hz.bin"
                    % (when, board_uavo[:8], (local_uavo or "?")[:8]))
        else:
            add("WARN", "firmware age", "no OpFw description blob - cannot date the firmware")
    else:
        add("WARN", "board identity", "FirmwareIAPObj not received")

    mix = cfg.get("MixerSettings")
    if mix:
        bad = []
        for m, want in QUADX_MIXER.items():
            if mix.get("Mixer%dType" % m) != "Motor":
                bad.append("Mixer%d not Motor" % m)
            vec = mix.get("Mixer%dVector" % m, [])
            if list(vec[2:5]) != want:
                bad.append("Mixer%d vector %s != %s" % (m, list(vec[2:5]), want))
        add("FAIL" if bad else "OK", "QuadX mixer table",
            "; ".join(bad) if bad else "all four motors, stock geometry")
        curve = mix.get("ThrottleCurve1", [])
        if not any(float(c) > 0 for c in curve):
            add("FAIL", "throttle curve", "ThrottleCurve1 is all zeros - motors will never spin")
        elif list(curve) != sorted(curve):
            add("WARN", "throttle curve", "not monotonic: %s" % [round(float(c), 2) for c in curve])
        else:
            add("OK", "throttle curve", "%s" % [round(float(c), 2) for c in curve])
    else:
        add("FAIL", "QuadX mixer table", "MixerSettings not received")

    act = cfg.get("ActuatorSettings")
    if act:
        neut = [int(n) for n in act.get("ChannelNeutral", [])[:4]]
        spread = max(neut) - min(neut) if neut else 999
        if spread <= 10:
            add("OK", "neutral symmetry", "%s (spread %dus)" % (neut, spread))
        else:
            add("WARN", "neutral symmetry",
                "%s - spread %dus. Unequal spool points made one corner weak at idle; after ESC cal set all four EQUAL" % (neut, spread))
        spin = act.get("MotorsSpinWhileArmed")
        add("OK" if spin == "TRUE" else "WARN", "spin while armed",
            str(spin) + ("" if spin == "TRUE" else " - recommended TRUE: symmetric idle floor keeps the couple two-sided from arming"))
    else:
        add("FAIL", "neutral symmetry", "ActuatorSettings not received")

    fms = cfg.get("FlightModeSettings")
    if fms:
        for slot in (1, 2, 3):
            modes = fms.get("Stabilization%dSettings" % slot, [])
            if len(modes) >= 4:
                r, p_, y, t = modes[0], modes[1], modes[2], modes[3]
                if r != "Attitude" or p_ != "Attitude":
                    add("FAIL" if slot == 3 else "WARN", "Stabilized%d" % slot,
                        "%s/%s/%s/%s - roll/pitch not self-leveling (Rate here is the original tumble config)" % (r, p_, y, t))
                elif y == "AxisLock":
                    add("WARN", "Stabilized%d" % slot,
                        "%s/%s/%s/%s - AxisLock yaw winds up during the arming gesture; Rate recommended" % (r, p_, y, t))
                else:
                    add("OK", "Stabilized%d" % slot, "%s/%s/%s/%s" % (r, p_, y, t))
    else:
        add("FAIL", "flight modes", "FlightModeSettings not received")

    bank = cfg.get("StabilizationSettingsBank1")
    if bank:
        rp = [float(x) for x in bank.get("RollRatePID", [0] * 4)]
        ap = [float(x) for x in bank.get("RollPI", [0] * 3)]
        sane = 0.001 <= rp[0] <= 0.01 and 1.0 <= ap[0] <= 6.0
        add("OK" if sane else "WARN", "Bank1 gains",
            "rate Kp/Ki/Kd %.4f/%.4f/%.5f, attitude Kp %.1f%s"
            % (rp[0], rp[1], rp[2], ap[0],
               "" if sane else " - outside sane range for this class"))
    else:
        add("WARN", "Bank1 gains", "StabilizationSettingsBank1 not received")

    mcs = cfg.get("ManualControlSettings")
    if mcs:
        groups = mcs.get("ChannelGroups", [])[:4]
        unmapped = [i for i, g in enumerate(groups) if g in ("None", None)]
        add("FAIL" if unmapped else "OK", "receiver mapping",
            ("Thr/Roll/Pitch/Yaw groups: %s" % groups) + (" - UNMAPPED axes!" if unmapped else ""))
    else:
        add("FAIL", "receiver mapping", "ManualControlSettings not received")

    att = cfg.get("AttitudeSettings")
    if att:
        rot = [float(r) for r in att.get("BoardRotation", [0, 0, 0])]
        # This airframe's IMU is mounted with its +x at the TAIL (orientation_check
        # 2026-09-02: nose down read NOSE UP 45 deg, left arm read RIGHT SIDE DOWN
        # 48 deg, raw accel agreed). Yaw=180 is the fix; Yaw=0 is the
        # 2026-09-01 flip: positive feedback on both axes at liftoff.
        if abs(abs(rot[2]) - 180.0) > 0.5:
            add("FAIL", "board rotation", "BoardRotation %s - Yaw must be 180 on this frame "
                "(IMU +x points at the tail; Yaw 0 flips at liftoff). Run orientation_check.py." % rot)
        elif any(abs(r) > 3.0 for r in rot[:2]):
            add("WARN", "board rotation", "BoardRotation %s - Yaw 180 ok, roll/pitch trim > 3 deg" % rot)
        else:
            add("OK", "board rotation", "Yaw 180 (IMU +x at tail, corrected) trims %s" % rot[:2])
    al = cfg.get("SystemAlarms")
    if al:
        alv = al.get("Alarm", [])
        crit = [ALARM_NAMES[i] + "=" + v for i, v in enumerate(alv)
                if i < len(ALARM_NAMES) and v in ("Error", "Critical")]
        if crit:
            hint = ""
            if any(c.startswith("BootFault") for c in crit):
                hint = " - BootFault on this board = IMU did not answer WHO_AM_I at boot (or DRDY/DSM task failed); blocks arming; clean power cycle, else SPI leads"
            if any(c.startswith("Attitude") for c in crit):
                hint += " - Attitude: IMU not producing samples; clean power cycle, then check GyroState"
            add("FAIL", "alarms", ", ".join(crit) + hint)
        else:
            add("OK", "alarms", "no Error/Critical alarms")
    gy = cfg.get("GyroState")
    if gy:
        gb = [float(gy.get(k, 0.0)) for k in ("x", "y", "z")]
        if all(abs(v) < 1e-6 for v in gb):
            add("FAIL", "gyro stream", "GyroState exactly zero - IMU produced no samples since boot; clean power cycle")
        # CC attitude learns gyro bias with a 0.2 s time constant during the
        # first ~7 s after power-up AND during the arming second
        # (ZeroDuringArming). A quad that was moving then carries that rate as
        # bias all session: 2026-09-02 01:28 bench, gyro.x -54 deg/s, roll
        # estimate wandering past 90 deg while the accel read the truth.
        if max(abs(v) for v in gb[:2]) > 4.0:
            add("FAIL", "gyro bias", "at rest x %+.1f y %+.1f deg/s - board moved during its startup "
                "calibration; power cycle and keep it STILL for 10 s, and still while arming" % (gb[0], gb[1]))
        else:
            add("OK", "gyro bias", "at rest x %+.1f y %+.1f z %+.1f deg/s" % tuple(gb))
    sysx = cfg.get("SystemSettings")
    if sysx:
        af = sysx.get("AirframeType")
        add("OK" if af == "QuadX" else "WARN", "airframe type", str(af))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--host", default="192.168.0.45")
    ap.add_argument("--port", type=int, default=9000)
    args = ap.parse_args()

    db = uavtalk.UAVObjectDB(os.path.join(NINJAPILOT_ROOT, "shared", "uavobjectdefinition"))
    gcs_stats = db["GCSTelemetryStats"]
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setblocking(False)
    addr = (args.host, args.port)
    parser = uavtalk.UAVTalkParser()

    outdir = os.path.expanduser("~/NinjaPilot-logs")
    os.makedirs(outdir, exist_ok=True)
    outpath = os.path.join(outdir, "flightmon_%s.jsonl" % time.strftime("%Y-%m-%d_%H-%M-%S"))
    out = open(outpath, "w")

    print("flight_monitor: %s:%d -> %s" % (args.host, args.port, outpath))
    print("close the GCS if it is open (one UAVTalk client at a time), then fly.")
    print("Ctrl+C after landing for the summary.\n")

    state = {
        "gcs": GCS_HANDSHAKEREQ, "connected_at": None,
        "last_handshake": 0.0, "last_poll": 0.0, "poll_i": 0,
        "last_status": 0.0, "n_rx": 0, "n_rx_win": 0,
        "last_att": None, "att": (0.0, 0.0, 0.0), "thr": None, "pwm": None,
        "armed": None, "mode": None, "alarms": None,
        "stall_open": None,
        "pf_cfg": {}, "pf_req_i": 0, "pf_last_req": 0.0, "pf_done": False, "pf_deadline": None,
        "extra_req": [], "ctx_last": {}, "ctx_pending": {},
    }
    events = []          # (wall, kind, text)
    stalls = []          # (start, end)
    att_min = [1e9, 1e9]
    att_max = [-1e9, -1e9]
    t0 = time.time()

    def record(name, inst, d, now):
        out.write(json.dumps({"t": round(now - t0, 3), "o": name, "i": inst, "d": d}) + "\n")

    def event(now, kind, text):
        events.append((now - t0, kind, text))
        print("[%7.1fs] %s: %s" % (now - t0, kind, text), flush=True)

    def note(now, kind, text):
        # on screen and in the jsonl (via record) but not in the end-of-run
        # event summary - alarm context repeats every few seconds
        print("[%7.1fs] %s: %s" % (now - t0, kind, text), flush=True)

    def queue_ctx(alarm, now, force=False):
        objs = ALARM_CONTEXT.get(alarm)
        if not objs:
            return
        if not force and now - state["ctx_last"].get(alarm, 0.0) < ALARM_CTX_PERIOD:
            return
        state["ctx_last"][alarm] = now
        for n in objs:
            try:
                od = db[n]
            except Exception:
                continue
            # settings objects do not change under an alarm: pull them once per
            # episode (force), re-pull only the dynamic ones every period
            if not force and (getattr(od, "is_settings", False) or getattr(od, "settings", False) is True):
                continue
            if n not in state["extra_req"]:
                state["extra_req"].append(n)
            state["ctx_pending"].setdefault(n, set()).add(alarm)

    def digest(d, limit=7):
        parts = []
        for k, v in d.items():
            if len(parts) >= limit:
                parts.append("...")
                break
            if isinstance(v, float):
                parts.append("%s=%.2f" % (k, v))
            elif isinstance(v, list):
                vv = ["%.1f" % x if isinstance(x, float) else str(x) for x in v[:4]]
                parts.append("%s=[%s%s]" % (k, ",".join(vv), ",.." if len(v) > 4 else ""))
            else:
                parts.append("%s=%s" % (k, v))
        return " ".join(parts)

    def send_gcs(status):
        payload = gcs_stats.pack({"Status": status})
        sock.sendto(uavtalk.build_packet(uavtalk.TYPE_OBJ, gcs_stats.obj_id, 0, payload), addr)

    try:
        while True:
            now = time.time()
            # handshake keepalive (also holds the firmware's UDP peer latch)
            if now - state["last_handshake"] > 1.0:
                state["last_handshake"] = now
                send_gcs(state["gcs"])
            # PREFLIGHT phase: request each settings object (one frame per
            # gap, never back-to-back), evaluate when all are in or 8s pass
            if state["gcs"] == GCS_CONNECTED and not state["pf_done"]:
                if state["pf_deadline"] is None:
                    state["pf_deadline"] = now + 8.0
                    print("\n--- preflight: reading board configuration ---", flush=True)
                if now - state["pf_last_req"] > POLL_GAP:
                    state["pf_last_req"] = now
                    missing = [n for n in PREFLIGHT_OBJECTS if n not in state["pf_cfg"]]
                    if missing:
                        o = db[missing[state["pf_req_i"] % len(missing)]]
                        state["pf_req_i"] += 1
                        sock.sendto(uavtalk.build_packet(uavtalk.TYPE_OBJ_REQ, o.obj_id, 0), addr)
                if not [n for n in PREFLIGHT_OBJECTS if n not in state["pf_cfg"]] or now > state["pf_deadline"]:
                    state["pf_done"] = True
                    results = run_preflight(state["pf_cfg"])
                    n_fail = sum(1 for l, _, _ in results if l == "FAIL")
                    n_warn = sum(1 for l, _, _ in results if l == "WARN")
                    mark = {"OK": " ok ", "WARN": "WARN", "FAIL": "FAIL"}
                    for level, name, detail in results:
                        print("  [%s] %-18s %s" % (mark[level], name, detail), flush=True)
                    if n_fail:
                        print("--- preflight: NO-GO (%d FAIL, %d WARN) - fix before flying ---\n" % (n_fail, n_warn), flush=True)
                    elif n_warn:
                        print("--- preflight: GO with %d warning(s) ---\n" % n_warn, flush=True)
                    else:
                        print("--- preflight: GO - board configured as expected ---\n", flush=True)
            # round-robin poll, one frame at a time
            if state["gcs"] == GCS_CONNECTED and state["pf_done"] and now - state["last_poll"] > POLL_GAP:
                state["last_poll"] = now
                # alarms that are still up get their context re-pulled slowly
                for i, v in enumerate(state["alarms"] or []):
                    if ALARM_RANK.get(v, 0) >= 1 and i < len(ALARM_NAMES):
                        queue_ctx(ALARM_NAMES[i], now)
                if state["extra_req"]:
                    name = state["extra_req"].pop(0)
                else:
                    name = POLL_OBJECTS[state["poll_i"] % len(POLL_OBJECTS)]
                    state["poll_i"] += 1
                o = db[name]
                sock.sendto(uavtalk.build_packet(uavtalk.TYPE_OBJ_REQ, o.obj_id, 0), addr)

            r, _, _ = select.select([sock], [], [], 0.05)
            if r:
                try:
                    data, _from = sock.recvfrom(65536)
                except OSError:
                    data = b""
                if data:
                    parser.feed(data)
            for mt, oid, iid, payload in parser.packets():
                if mt in (uavtalk.TYPE_ACK, uavtalk.TYPE_NACK, uavtalk.TYPE_OBJ_REQ):
                    continue
                o = db.by_id.get(oid)
                if o is None:
                    continue
                try:
                    d = o.describe(o.unpack(payload))
                except Exception:
                    continue
                # acked pushes (settings etc.) BLOCK the flight side's telemetry
                # until we reply; a client that stays silent turns the link into
                # a retry storm (measured: packet counts climbing without bound)
                if mt in (uavtalk.TYPE_OBJ_ACK, uavtalk.TYPE_OBJ_ACK_TS):
                    sock.sendto(uavtalk.build_packet(uavtalk.TYPE_ACK, oid, iid), addr)
                now = time.time()
                state["n_rx"] += 1
                state["n_rx_win"] += 1
                record(o.name, iid, d, now)

                if o.name in state["ctx_pending"] and state["ctx_pending"][o.name]:
                    for_alarms = "/".join(sorted(state["ctx_pending"].pop(o.name)))
                    note(now, "CTX", "%s (for %s): %s" % (o.name, for_alarms, digest(d)))

                # armed-bias watchdog: ZeroDuringArming re-learns gyro bias in
                # the arming second; average the resting gyro 0.5-3 s after
                # arming and shout if the quad moved during that window.
                if o.name == "FlightStatus":
                    if d.get("Armed") == "Armed":
                        if state.get("armed_at") is None:
                            state["armed_at"] = now
                            state["arm_bias"] = []
                            state["arm_bias_done"] = False
                    else:
                        state["armed_at"] = None
                if o.name == "GyroState" and state.get("armed_at") and not state.get("arm_bias_done"):
                    dt_arm = now - state["armed_at"]
                    if 0.5 < dt_arm < 3.0:
                        state["arm_bias"].append((float(d.get("x", 0.0)), float(d.get("y", 0.0))))
                    elif dt_arm >= 3.0 and state["arm_bias"]:
                        state["arm_bias_done"] = True
                        bx = sum(b[0] for b in state["arm_bias"]) / len(state["arm_bias"])
                        by = sum(b[1] for b in state["arm_bias"]) / len(state["arm_bias"])
                        if max(abs(bx), abs(by)) > 4.0:
                            event(now, "GYRO BIAS", "learned during arming: x %+.1f y %+.1f deg/s - "
                                  "DISARM NOW, hold the quad still, re-arm" % (bx, by))
                        else:
                            event(now, "gyro", "bias after arming ok: x %+.1f y %+.1f deg/s" % (bx, by))

                if not state["pf_done"] and o.name in PREFLIGHT_OBJECTS:
                    state["pf_cfg"][o.name] = d

                if o.name == "FlightTelemetryStats":
                    fl = d.get("Status")
                    if fl == "HandshakeAck" and state["gcs"] != GCS_CONNECTED:
                        state["gcs"] = GCS_CONNECTED
                        send_gcs(state["gcs"])
                    elif fl == "Connected":
                        if state["connected_at"] is None:
                            state["connected_at"] = now
                            event(now, "LINK", "connected to flight side")
                    elif fl == "Disconnected" and state["gcs"] == GCS_CONNECTED:
                        state["gcs"] = GCS_HANDSHAKEREQ
                        event(now, "LINK", "flight side dropped to Disconnected")
                elif o.name == "AttitudeState":
                    if state["last_att"] is not None and now - state["last_att"] > 1.0:
                        stalls.append((state["last_att"] - t0, now - t0))
                        event(now, "STALL", "AttitudeState gap %.1fs" % (now - state["last_att"]))
                    state["last_att"] = now
                    state["att"] = (d["Roll"], d["Pitch"], d["Yaw"])
                    for i in range(2):
                        v = (d["Roll"], d["Pitch"])[i]
                        att_min[i] = min(att_min[i], v)
                        att_max[i] = max(att_max[i], v)
                elif o.name == "ManualControlCommand":
                    state["thr"] = d.get("Throttle")
                elif o.name == "ActuatorCommand":
                    state["pwm"] = d.get("Channel", [])[:4]
                elif o.name == "FlightStatus":
                    if d["Armed"] != state["armed"]:
                        event(now, "ARM", "%s (mode %s)" % (d["Armed"], d["FlightMode"]))
                        state["armed"] = d["Armed"]
                    if d["FlightMode"] != state["mode"]:
                        if state["mode"] is not None:
                            event(now, "MODE", str(d["FlightMode"]))
                        state["mode"] = d["FlightMode"]
                elif o.name == "SystemAlarms":
                    al = d.get("Alarm")
                    if al != state["alarms"]:
                        prev = state["alarms"]
                        for i, v in enumerate(al):
                            pv = prev[i] if prev else None
                            if pv is not None and v != pv and ALARM_RANK.get(v, 0) != ALARM_RANK.get(pv, 0):
                                nm = ALARM_NAMES[i] if i < len(ALARM_NAMES) else str(i)
                                event(now, "ALARM", "%s: %s -> %s" % (nm, pv, v))
                                if ALARM_RANK.get(v, 0) >= 1:
                                    queue_ctx(nm, now, force=True)
                            elif pv is None and ALARM_RANK.get(v, 0) >= 1:
                                # already up when we connected: pull its context once now
                                queue_ctx(ALARM_NAMES[i] if i < len(ALARM_NAMES) else str(i), now, force=True)
                        state["alarms"] = al

            now = time.time()
            # live status line
            if now - state["last_status"] > 1.0:
                state["last_status"] = now
                al = state["alarms"]
                worst = ""
                if al:
                    bad = [(ALARM_NAMES[i] if i < len(ALARM_NAMES) else str(i)) + "=" + v
                           for i, v in enumerate(al) if ALARM_RANK.get(v, 0) >= 1]
                    worst = " ".join(bad[:4]) if bad else "all-OK"
                r_, p_, y_ = state["att"]
                pwm = state["pwm"]
                pwm_s = ("[" + " ".join("%4d" % c for c in pwm) + "]") if pwm else "[---- ---- ---- ----]"
                print("[%7.1fs] %s rp(%6.1f,%6.1f) yaw %6.1f thr %s pwm %s pkts/s %3d  %s"
                      % (now - t0,
                         "LINK" if state["gcs"] == GCS_CONNECTED else "....",
                         r_, p_, y_,
                         ("%.2f" % state["thr"]) if state["thr"] is not None else "  - ",
                         pwm_s, state["n_rx_win"], worst), flush=True)
                state["n_rx_win"] = 0
                # stall detection also from the quiet side
                if state["last_att"] and now - state["last_att"] > 1.0 and state["stall_open"] is None:
                    state["stall_open"] = state["last_att"]
                    event(now, "STALL", "AttitudeState silent since t=%.1fs" % (state["last_att"] - t0))
                if state["stall_open"] and state["last_att"] and now - state["last_att"] < 1.0:
                    state["stall_open"] = None
    except KeyboardInterrupt:
        pass
    finally:
        out.close()

    dur = time.time() - t0
    print("\n===== flight_monitor summary =====")
    print("duration %.1fs, %d packets, log: %s" % (dur, state["n_rx"], outpath))
    if att_min[0] < 1e8:
        print("attitude extremes: roll [%.1f, %.1f]  pitch [%.1f, %.1f]"
              % (att_min[0], att_max[0], att_min[1], att_max[1]))
    if stalls:
        print("link stalls (>1s AttitudeState gaps):")
        for a, b in stalls:
            print("  t=%.1fs -> %.1fs (%.1fs)" % (a, b, b - a))
    else:
        print("no link stalls")
    print("events:")
    for t, kind, text in events:
        print("  [%7.1fs] %-6s %s" % (t, kind, text))
    print("analyze with: the jsonl above (wall-stamped, every object received)")


if __name__ == "__main__":
    main()
