#!/usr/bin/env python3
"""
litewing_bridge - close the loop between Gazebo and the fw_simlitewing twin.

Gazebo owns the physics of a LiteWing-shaped airframe (55 g, 99 mm diagonal,
T/W 1.6). The flight controller is the real simlitewing firmware: it gets the
IMU, it runs the CC complementary filter and the Stabilization loop, and its
ActuatorCommand -- BRUSHED duty, 0..1000 = 0..100 % -- drives the rotors.

Duty is mapped to rotor speed through sqrt(), because Gazebo's motor model
makes thrust quadratic in omega (thrust = kf * omega^2) while the mixer adds
its roll/pitch/yaw corrections linearly. sqrt() makes duty->THRUST linear,
which is the assumption the mixer is actually built on.

Only the collective is ours: a small altitude PD holds a target height. Every
attitude correction comes from the firmware.
"""
import math, os, sys, threading, time

HERE = os.path.dirname(os.path.abspath(__file__))
NJP = os.environ.get("NINJAPILOT_ROOT", "/tmp/njp")
sys.path.insert(0, os.path.join(NJP, "ground", "pyuavtalk"))
import uavtalk
from uavtalk_client import UdpTransport, UAVTalkClient, default_xml_dir

import gz.transport13 as transport
from gz.msgs10.actuators_pb2 import Actuators
from gz.msgs10.imu_pb2 import IMU
from gz.msgs10.pose_v_pb2 import Pose_V
from gz.msgs10.marker_pb2 import Marker
from gz.msgs10.empty_pb2 import Empty
from gz.msgs10.world_control_pb2 import WorldControl
from gz.msgs10.boolean_pb2 import Boolean

MAX_RAD   = 3000.0        # must match worlds/litewing.sdf maxRotVelocity
DUTY_FULL = 1000.0        # ActuatorCommand full scale = 100.0 % duty
HOVER     = 0.624         # predicted from the model's own numbers
TARGET_Z  = float(os.environ.get("LITEWING_ALT", "1.5"))
RAD2DEG   = 57.2957795

state = {"z": 0.0, "vz": 0.0, "last_z": None, "last_t": None,
         "roll": 0.0, "pitch": 0.0, "imu": 0, "armed": False, "ialt": 0.0,
         "x": 0.0, "y": 0.0}
thr = [0.0]; yaw = [1500]
lock = threading.Lock()

db = uavtalk.UAVObjectDB(default_xml_dir())
client = UAVTalkClient(UdpTransport("127.0.0.1", 9000), db)
latest = {}
threading.Thread(target=lambda: client.run(
    on_object=lambda o, i, d: latest.__setitem__(o.name, dict(d)), duration=1e9),
    daemon=True).start()
time.sleep(2)

def fetch(n, t=5.0):
    latest.pop(n, None); o = db[n]; end = time.time() + t
    while time.time() < end:
        client.transport.send(uavtalk.build_packet(uavtalk.TYPE_OBJ_REQ, o.obj_id, 0))
        for _ in range(8):
            if n in latest: return latest[n]
            time.sleep(0.05)
    return None

node = transport.Node()
motor_pub = node.advertise("/litewing/gazebo/command/motor_speed", Actuators)
gyro_o, acc_o, gcs_o = db["GyroSensor"], db["AccelSensor"], db["GCSReceiver"]

def on_imu(msg):
    """Gazebo body frame is x-fwd y-LEFT z-UP; OpenPilot is x-fwd y-RIGHT
    z-DOWN, so y and z flip. At rest Gazebo reads +9.81 on z (proper
    acceleration, upward); OpenPilot expects -9.81. The flip gives that."""
    w, a = msg.angular_velocity, msg.linear_acceleration
    client.transport.send(uavtalk.build_packet(uavtalk.TYPE_OBJ, gyro_o.obj_id, 0,
        gyro_o.pack({"x": w.x * RAD2DEG, "y": -w.y * RAD2DEG, "z": -w.z * RAD2DEG,
                     "temperature": 25.0})))
    client.transport.send(uavtalk.build_packet(uavtalk.TYPE_OBJ, acc_o.obj_id, 0,
        acc_o.pack({"x": a.x, "y": -a.y, "z": -a.z, "temperature": 25.0})))
    with lock: state["imu"] += 1

def on_pose(msg):
    for p in msg.pose:
        if p.name == "litewing":
            now = time.time()
            with lock:
                z = p.position.z
                if state["last_t"] is not None:
                    dt = now - state["last_t"]
                    if dt > 1e-3:
                        state["vz"] = 0.7 * state["vz"] + 0.3 * (z - state["last_z"]) / dt
                state["last_z"], state["last_t"], state["z"] = z, now, z
                state["x"], state["y"] = p.position.x, p.position.y
                q = p.orientation
                sinr = 2 * (q.w * q.x + q.y * q.z); cosr = 1 - 2 * (q.x * q.x + q.y * q.y)
                state["roll"] = math.degrees(math.atan2(sinr, cosr))
                sinp = max(-1.0, min(1.0, 2 * (q.w * q.y - q.z * q.x)))
                state["pitch"] = math.degrees(math.asin(sinp))
            return

node.subscribe(IMU, "/litewing/imu", on_imu)
node.subscribe(Pose_V, "/world/litewing/pose/info", on_pose)

def unpause():
    """A GUI connecting to a running server can leave the world PAUSED, and a
    paused world publishes no IMU and steps no physics -- the aircraft sits at
    its spawn pose looking like a firmware failure while the flight log claims
    a perfect hover. That exact confusion cost a session. Force it running."""
    req = WorldControl(); req.pause = False
    try:
        node.request("/world/litewing/control", req, WorldControl, Boolean, 2000)
    except Exception:
        pass


# --- flight trail ----------------------------------------------------------
# gz renders LINE_STRIP at 1px regardless of scale, invisible at scene
# distance, so each segment is a translucent CYLINDER instead -- the same
# lesson gazebo_bridge.py records. 40 mm tube suits a 100 mm airframe.
TRAIL_D = 0.04
_trail = {"last": None, "n": 0}

def trail_clear():
    m = Marker(); m.ns = "litewing_trail"; m.action = Marker.DELETE_ALL
    try:
        node.request("/marker", m, Marker, Empty, 100)
    except Exception:
        pass

def trail_add(a, b):
    dx, dy, dz = b[0]-a[0], b[1]-a[1], b[2]-a[2]
    length = math.sqrt(dx*dx + dy*dy + dz*dz)
    if length < 0.005:
        return
    _trail["n"] += 1
    m = Marker(); m.ns = "litewing_trail"; m.id = 100 + _trail["n"]
    m.action = Marker.ADD_MODIFY; m.type = Marker.CYLINDER
    for tgt in (m.material.ambient, m.material.diffuse, m.material.emissive):
        tgt.r, tgt.g, tgt.b, tgt.a = (0.1, 0.9, 1.0, 0.65)
    m.scale.x = m.scale.y = TRAIL_D; m.scale.z = length
    m.pose.position.x = (a[0]+b[0])/2.0
    m.pose.position.y = (a[1]+b[1])/2.0
    m.pose.position.z = (a[2]+b[2])/2.0
    ux, uy, uz = dx/length, dy/length, dz/length
    if uz > 0.99999:      q = (1.0, 0.0, 0.0, 0.0)
    elif uz < -0.99999:   q = (0.0, 1.0, 0.0, 0.0)
    else:
        ax, ay, az = -uy, ux, 0.0
        n = math.sqrt(ax*ax + ay*ay) or 1.0
        ang = math.acos(max(-1.0, min(1.0, uz))); sh = math.sin(ang/2.0)
        q = (math.cos(ang/2.0), ax/n*sh, ay/n*sh, az*sh)
    m.pose.orientation.w, m.pose.orientation.x = q[0], q[1]
    m.pose.orientation.y, m.pose.orientation.z = q[2], q[3]
    try:
        node.request("/marker", m, Marker, Empty, 50)   # reply is Empty, not Boolean
    except Exception:
        pass

def trail_pump():
    while True:
        if state["armed"]:
            with lock:
                pt = (state["x"], state["y"], state["z"])
            if _trail["last"] is None or math.dist(pt, _trail["last"]) > 0.03:
                if _trail["last"] is not None:
                    trail_add(_trail["last"], pt)
                _trail["last"] = pt
        time.sleep(0.15)


def stick_pump():
    while True:
        us = int(1000 + max(0.0, min(1.0, thr[0])) * 1000)
        client.transport.send(uavtalk.build_packet(uavtalk.TYPE_OBJ, gcs_o.obj_id, 0,
            gcs_o.pack({"Channel": [us, 1500, 1500, yaw[0], 1000, 1500, 1500, 1500]})))
        time.sleep(0.02)

def motor_pump():
    """ActuatorCommand's flight telemetry is periodic at 1000 ms (see
    actuatorcommand.xml). Publishing whatever happened to be in the cache
    therefore drove Gazebo's rotors at 1 Hz while physics ran at 1 kHz: the
    airframe pogoed floor-to-6 m and eventually flipped, which looks exactly
    like a tuning problem and is not one. Poll the object explicitly so the
    motors get fresh values at loop rate."""
    ac_o = db["ActuatorCommand"]
    while True:
        client.transport.send(uavtalk.build_packet(uavtalk.TYPE_OBJ_REQ, ac_o.obj_id, 0))
        ac = latest.get("ActuatorCommand")
        if ac:
            m = Actuators()
            for i in range(4):
                frac = max(0.0, min(1.0, float(ac["Channel"][i]) / DUTY_FULL))
                m.velocity.append(math.sqrt(frac) * MAX_RAD)
            motor_pub.publish(m)
        time.sleep(0.01)

unpause(); trail_clear()
threading.Thread(target=stick_pump, daemon=True).start()
threading.Thread(target=motor_pump, daemon=True).start()
threading.Thread(target=trail_pump, daemon=True).start()
time.sleep(3)

print("[bridge] IMU frames received: %d" % state["imu"], flush=True)
if state["imu"] == 0:
    sys.exit("ABORT: no IMU from Gazebo -- world paused or not running. "
             "Nothing below would have been a real flight.")
# ---- nano gains -----------------------------------------------------------
# Bank1 ships with 4-inch-class values (rate Kp 0.0032 / Ki 0.0075, attitude
# Kp 3.2) tuned for a ~500 g quad. A 55 g airframe has a fraction of the
# inertia for comparable control authority, so those gains over-drive it: the
# first flight held a rock-steady hover for ten seconds and then diverged into
# the rails. Scaling the rate loop down by ~2.7x is the retune LITEWING.md
# says this port needs; set LITEWING_STOCK_GAINS=1 to reproduce the divergence.
if os.environ.get("LITEWING_STOCK_GAINS") != "1":
    b = fetch("StabilizationSettingsBank1")
    b["RollRatePID"]  = [0.0012, 0.0022, 0.00002, 0.3]
    b["PitchRatePID"] = [0.0012, 0.0022, 0.00002, 0.3]
    b["RollPI"]       = [2.5, 0.0, 50.0]
    b["PitchPI"]      = [2.5, 0.0, 50.0]
    client.send_object("StabilizationSettingsBank1", b); time.sleep(0.5)
    chk = fetch("StabilizationSettingsBank1")
    print("[bridge] nano gains: rate Kp %.4f (was 0.0032), attitude Kp %.1f (was 3.2)"
          % (chk["RollRatePID"][0], chk["RollPI"][0]), flush=True)

fms = fetch("FlightModeSettings"); fms["Arming"] = "Yaw Right"
client.send_object("FlightModeSettings", fms); time.sleep(0.6)
fs = fetch("FlightStatus"); print("[bridge] flight mode: %s" % fs["FlightMode"], flush=True)

yaw[0] = 2000; t0 = time.time()
while time.time() - t0 < 8:
    fs = fetch("FlightStatus", 1.0)
    if fs and fs["Armed"] == "Armed": state["armed"] = True; break
    time.sleep(0.3)
yaw[0] = 1500
print("[bridge] armed: %s" % state["armed"], flush=True)
if not state["armed"]:
    sys.exit("did not arm")

print("\n  t     alt      vz     roll   pitch   duty   ActuatorCommand")
t0 = time.time(); last = 0
while time.time() - t0 < float(os.environ.get("LITEWING_SECONDS", "22")):
    with lock:
        z, vz, r, p = state["z"], state["vz"], state["roll"], state["pitch"]
    # Gentle: T/W is 1.6, so a hot gain here bang-bangs the collective and
    # the airframe pogos between the floor and 6 m. Error is clamped before
    # it reaches the gain, and the authority band is deliberately narrow --
    # the firmware owns attitude, this only owns height.
    err = max(-1.0, min(1.0, TARGET_Z - z))
    # small integral so it actually settles ON the commanded height instead of
    # drooping to wherever P alone balances gravity; clamped so it cannot wind
    # up while the airframe is still on the ground.
    if state["armed"]:
        state["ialt"] = max(-0.08, min(0.08, state["ialt"] + 0.010 * err * 0.02))
    thr[0] = max(0.35, min(0.80, HOVER + 0.10 * err + state["ialt"] - 0.16 * vz))
    now = time.time() - t0
    if now - last >= 1.0:
        last = now
        ac = latest.get("ActuatorCommand", {}).get("Channel", [0, 0, 0, 0])[:4]
        print(" %4.1f  %6.3f  %+6.2f  %+6.1f  %+6.1f   %4.0f   %s"
              % (now, z, vz, r, p, thr[0] * 1000, [int(x) for x in ac]), flush=True)
    time.sleep(0.02)

# ---- commanded descent and touchdown, not a throttle cut -------------------
# Dropping thr to 0 from hover is a free fall: 1.5 m is ~0.55 s and lands at
# about 5.4 m/s, which on real hardware is how you break arms. Walk the
# altitude setpoint down at a fixed rate, let the same PD fly it, and only
# cut power once the airframe is actually resting on the ground.
DESCENT_RATE = 0.35          # m/s
TOUCHDOWN_Z  = 0.012         # body half-thickness is 0.006; allow a margin
print("\n[bridge] commanded descent at %.2f m/s" % DESCENT_RATE, flush=True)
with lock:
    tgt = state["z"]
t_land = time.time(); last = 0.0; touched = 0
while time.time() - t_land < 25.0:
    dt = 0.02
    tgt = max(0.0, tgt - DESCENT_RATE * dt)
    with lock:
        z, vz = state["z"], state["vz"]
    err = max(-1.0, min(1.0, tgt - z))
    state["ialt"] = max(-0.08, min(0.08, state["ialt"] + 0.010 * err * dt))
    thr[0] = max(0.30, min(0.80, HOVER + 0.10 * err + state["ialt"] - 0.16 * vz))
    now = time.time() - t_land
    if now - last >= 0.5:
        last = now
        print("  land %4.1f  alt %6.3f  vz %+5.2f  tgt %5.3f  duty %4.0f"
              % (now, z, vz, tgt, thr[0] * 1000), flush=True)
    # touchdown: resting on the ground and not moving, for several samples
    if z < TOUCHDOWN_Z and abs(vz) < 0.05:
        touched += 1
        if touched > 25:
            break
    else:
        touched = 0
    time.sleep(dt)

thr[0] = 0.0
time.sleep(0.5)
with lock:
    print("[bridge] touchdown at %.3f m, vz %+.2f m/s" % (state["z"], state["vz"]), flush=True)
fms = fetch("FlightModeSettings"); fms["Arming"] = "Always Disarmed"
client.send_object("FlightModeSettings", fms); time.sleep(1.0)
fs = fetch("FlightStatus")
print("[bridge] disarmed: %s" % (fs["Armed"] if fs else "?"), flush=True)
