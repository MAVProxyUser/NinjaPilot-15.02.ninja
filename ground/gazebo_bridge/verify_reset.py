"""
verify_reset.py - confirm the Gazebo world reset actually took effect before
declaring a test iteration "clean". reset_run.sh previously fired the reset
service call and moved on unconditionally - if the reset silently failed (or
raced with a still-in-flight previous run), the next test would start against
a vehicle that was still airborne/tumbling from the PREVIOUS run, producing
results that looked like a fresh-run failure but weren't. Subscribes to the
real pose topic (same ground-truth source used elsewhere in this session, not
the bridge's own self-reported state) and checks position/attitude are back
at the model's spawned rest pose before exiting 0.
"""
import sys
import time
from gz.transport13 import Node
from gz.msgs10.pose_v_pb2 import Pose_V

WORLD = "quadcopter"
MODEL = "x3"
# model.sdf spawns at <pose>0 0 0.053302 0 0 0</pose> - small XY tolerance
# for float noise, generous Z tolerance since resting height varies slightly
# with collision settling.
POS_XY_TOL = 0.05
POS_Z_MAX = 0.5
RPY_TOL_DEG = 2.0

result = {"got": False, "ok": False, "pos": None, "rpy": None}


def quat_to_euler_deg(w, x, y, z):
    import math
    sinr_cosp = 2 * (w * x + y * z)
    cosr_cosp = 1 - 2 * (x * x + y * y)
    roll = math.degrees(math.atan2(sinr_cosp, cosr_cosp))
    sinp = max(-1.0, min(1.0, 2 * (w * y - z * x)))
    pitch = math.degrees(math.asin(sinp))
    siny_cosp = 2 * (w * z + x * y)
    cosy_cosp = 1 - 2 * (y * y + z * z)
    yaw = math.degrees(math.atan2(siny_cosp, cosy_cosp))
    return roll, pitch, yaw


def cb(msg):
    for pose in msg.pose:
        if pose.name != MODEL:
            continue
        result["got"] = True
        p = pose.position
        r, pi, y = quat_to_euler_deg(pose.orientation.w, pose.orientation.x,
                                      pose.orientation.y, pose.orientation.z)
        result["pos"] = (p.x, p.y, p.z)
        result["rpy"] = (r, pi, y)
        ok_pos = abs(p.x) < POS_XY_TOL and abs(p.y) < POS_XY_TOL and 0 <= p.z < POS_Z_MAX
        ok_rpy = abs(r) < RPY_TOL_DEG and abs(pi) < RPY_TOL_DEG
        result["ok"] = ok_pos and ok_rpy


node = Node()
node.subscribe(Pose_V, f"/world/{WORLD}/pose/info", cb)

deadline = time.time() + 3.0
while time.time() < deadline:
    if result["got"]:
        break
    time.sleep(0.05)

if not result["got"]:
    print("[verify_reset] FAIL: no pose message received within 3s", flush=True)
    sys.exit(1)

if result["ok"]:
    print(f"[verify_reset] OK: pos={result['pos']} rpy={result['rpy']}", flush=True)
    sys.exit(0)
else:
    print(f"[verify_reset] FAIL: pos={result['pos']} rpy={result['rpy']} "
          f"(expected near origin, level)", flush=True)
    sys.exit(1)
