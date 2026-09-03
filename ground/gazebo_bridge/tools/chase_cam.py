#!/usr/bin/env python3
"""GPU chase cam -> mp4, for the wroom flip videos (or any flight).

Borrowed from the Cheetah port's stm32mp1/gazebo/record_video.py (the
camera-sensor-into-ffmpeg pipe), with the camera made a free-flying CHASE
rig instead of a body mount: a backflipping vehicle would take a mounted
camera around with it. A static model carrying a 1280x720@30 camera sensor
is spawned into the world and teleported every 50ms via /world/.../set_pose
along a low-passed follow path, aimed at the vehicle's raw position - the
motion floats, the aim stays locked. Runs in its OWN process for the same
reason trail_daemon.py does: a big image subscription must never share a
GIL with anything feeding the firmware.

  chase_cam.py <out.mp4> <seconds> [east] [north] [up]

east/north/up: camera offset from the vehicle in gazebo world axes
(default 7, 0, 1.2 - due east, slightly above: a backflip rotates about
the east axis, so this sees the loop in full profile).
"""
import math
import subprocess
import sys
import threading
import time

import os

import gz.transport13 as transport
from gz.msgs10.boolean_pb2 import Boolean
from gz.msgs10.entity_pb2 import Entity
from gz.msgs10.entity_factory_pb2 import EntityFactory
from gz.msgs10.image_pb2 import Image
from gz.msgs10.pose_v_pb2 import Pose_V
from gz.msgs10.twist_pb2 import Twist

WORLD = "quadcopter"
MODEL = "x3"
# UNIQUE name AND topic per session. gz's create service auto-renames a
# duplicate model instead of failing, so re-running with a fixed name
# quietly accumulates rigs - and every one of their cameras publishes
# onto the shared topic, so the recorder ends up pulling frames from a
# stale camera parked at the spawn pose while set_pose moves a different
# one. Two shoots were all-grass for exactly this reason.
RIG = "chase_rig_%d" % os.getpid()
TOPIC = "/chase_%d" % os.getpid()
FPS = 30

out_path = sys.argv[1] if len(sys.argv) > 1 else "chase.mp4"
duration = float(sys.argv[2]) if len(sys.argv) > 2 else 60.0
OFF = (float(sys.argv[3]) if len(sys.argv) > 3 else 7.0,
       float(sys.argv[4]) if len(sys.argv) > 4 else 0.0,
       float(sys.argv[5]) if len(sys.argv) > 5 else 1.2)

veh = {"p": None}
rig = {"p": None, "q": None}
rec = {"proc": None, "n": 0, "lock": threading.Lock()}


def on_pose(msg):
    for p in msg.pose:
        if p.name == MODEL:
            veh["p"] = (p.position.x, p.position.y, p.position.z)
        elif p.name == RIG:
            rig["p"] = (p.position.x, p.position.y, p.position.z)
            rig["q"] = (p.orientation.w, p.orientation.x,
                        p.orientation.y, p.orientation.z)


def on_image(msg):
    with rec["lock"]:
        if rec["proc"] is None:
            rec["proc"] = subprocess.Popen(
                ["ffmpeg", "-y", "-f", "rawvideo", "-pix_fmt", "rgb24",
                 "-s", f"{msg.width}x{msg.height}", "-r", str(FPS), "-i", "-",
                 "-c:v", "libx264", "-pix_fmt", "yuv420p", "-crf", "21",
                 out_path],
                stdin=subprocess.PIPE,
                stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            print(f"[chase] {msg.width}x{msg.height}@{FPS} -> {out_path}", flush=True)
        try:
            rec["proc"].stdin.write(msg.data)
            rec["n"] += 1
        except (BrokenPipeError, ValueError):
            pass


def remove_legacy_rigs(node):
    """Remove rigs left by earlier sessions (fixed-name era and unique-name
    era alike) so their cameras stop rendering and nothing else publishes
    stale frames. Removal is by name; auto-renamed dupes of the old fixed
    name got _0/_1 suffixes."""
    names = ["chase_cam_rig", "chase_cam_rig_0", "chase_cam_rig_1", "chase_cam_rig_2"]
    for n in names:
        ent = Entity()
        ent.name = n
        ent.type = Entity.MODEL
        try:
            node.request(f"/world/{WORLD}/remove", ent, Entity, Boolean, 1000)
        except Exception:
            pass


def spawn_rig(node):
    # spawn AT the follow point if the vehicle is already known - no
    # fly-in transient at the top of the recording
    vp = veh["p"] or (0.0, 0.0, 0.0)
    sx, sy, sz = vp[0] + OFF[0], vp[1] + OFF[1], vp[2] + OFF[2]
    sdf = f"""<?xml version="1.0"?>
<sdf version="1.6">
  <model name="{RIG}">
    <pose>{sx} {sy} {sz} 0 0 3.1416</pose>
    <link name="link">
      <gravity>false</gravity>
      <inertial><mass>0.1</mass>
        <inertia><ixx>0.001</ixx><iyy>0.001</iyy><izz>0.001</izz>
                 <ixy>0</ixy><ixz>0</ixz><iyz>0</iyz></inertia>
      </inertial>
      <sensor name="chase" type="camera">
        <topic>{TOPIC}</topic>
        <update_rate>{FPS}</update_rate>
        <camera>
          <horizontal_fov>1.05</horizontal_fov>
          <image><width>1280</width><height>720</height></image>
          <clip><near>0.1</near><far>400</far></clip>
        </camera>
        <always_on>1</always_on>
      </sensor>
    </link>
    <plugin filename="gz-sim-velocity-control-system"
            name="gz::sim::systems::VelocityControl"/>
  </model>
</sdf>"""
    req = EntityFactory()
    req.sdf = sdf
    ok, rep = node.request(f"/world/{WORLD}/create", req, EntityFactory, Boolean, 3000)
    print(f"[chase] rig spawned: {ok}", flush=True)


def look_at_quat(d):
    """Quaternion pointing the camera's +x (optical axis) along d: yaw about
    world z, then pitch about the new y."""
    yaw = math.atan2(d[1], d[0])
    pitch = -math.atan2(d[2], math.hypot(d[0], d[1]))
    cy, sy = math.cos(yaw / 2), math.sin(yaw / 2)
    cp, sp = math.cos(pitch / 2), math.sin(pitch / 2)
    # q = Rz(yaw) * Ry(pitch)
    return (cy * cp, -sy * sp, cy * sp, sy * cp)  # w, x, y, z


def q_mul(a, b):
    return (a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3],
            a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2],
            a[0] * b[2] - a[1] * b[3] + a[2] * b[0] + a[3] * b[1],
            a[0] * b[3] + a[1] * b[2] - a[2] * b[1] + a[3] * b[0])


def q_conj(q):
    return (q[0], -q[1], -q[2], -q[3])


def q_rotate_inv(q, v):
    """Rotate world vector v into the body frame of orientation q."""
    p = (0.0, v[0], v[1], v[2])
    r = q_mul(q_mul(q_conj(q), p), q)
    return (r[1], r[2], r[3])


def follow_loop(node, stop):
    """Velocity-servo the rig instead of teleporting it. set_pose is a
    SERVICE round-trip and about half the calls time out under flight load
    - the camera stepped at ~10Hz and the footage was visibly choppy. The
    VelocityControl plugin integrates a commanded velocity every physics
    step (same machinery as the intercept ball), so motion between the
    30Hz commands is continuous, and topic publishes cannot time out.

    Position: P-chase toward vehicle+offset. Orientation: P on the
    quaternion error toward a look-at of the vehicle, commanded as world
    angular velocity."""
    pub = node.advertise(f"/model/{RIG}/cmd_vel", Twist)
    time.sleep(1.0)  # discovery: publish-after-advertise goes into the void
    KP_POS, VMAX = 2.2, 12.0
    KP_ANG, WMAX = 3.0, 3.0
    while not stop.is_set():
        vp, rp, rq = veh["p"], rig["p"], rig["q"]
        if vp is not None and rp is not None and rq is not None:
            # VelocityControl reads cmd_vel in the model's BODY frame (a
            # cmd_vel convention). The ball never showed this because it
            # spawns unrotated; this rig spawned facing the pad (yaw pi)
            # and world-frame commands sign-flipped into a P-loop runaway
            # straight into the barn. Rotate everything into body frame.
            vw = tuple(max(-VMAX, min(VMAX, KP_POS * (vp[i] + OFF[i] - rp[i])))
                       for i in range(3))
            vb = q_rotate_inv(rq, vw)
            tw = Twist()
            tw.linear.x, tw.linear.y, tw.linear.z = vb
            d = tuple(vp[i] - rp[i] for i in range(3))
            qt = look_at_quat(d)
            qe = q_mul(qt, q_conj(rq))
            if qe[0] < 0.0:
                qe = tuple(-c for c in qe)
            sin_half = math.sqrt(max(0.0, 1.0 - qe[0] * qe[0]))
            if sin_half > 1e-6:
                angle = 2.0 * math.asin(min(1.0, sin_half))
                scale = KP_ANG * angle / sin_half / 2.0
                ww = tuple(max(-WMAX, min(WMAX, scale * qe[i + 1])) for i in range(3))
                wb = q_rotate_inv(rq, ww)
                tw.angular.x, tw.angular.y, tw.angular.z = wb
            pub.publish(tw)
        time.sleep(1.0 / 30.0)


def main():
    node = transport.Node()
    remove_legacy_rigs(node)
    time.sleep(0.5)
    # GATE on the pose feed before anything records: gz discovery is
    # multicast and occasionally a subscription silently never matches its
    # publisher - one whole shoot came back as 95s of barn planks because
    # the camera never learned where the vehicle was. Verify poses are
    # actually ARRIVING; if not, burn the node and resubscribe fresh.
    for attempt in range(3):
        node.subscribe(Pose_V, f"/world/{WORLD}/pose/info", on_pose)
        deadline = time.time() + 5.0
        while time.time() < deadline and veh["p"] is None:
            time.sleep(0.1)
        if veh["p"] is not None:
            break
        print(f"[chase] no vehicle poses after 5s (attempt {attempt + 1}) - resubscribing", flush=True)
        node = transport.Node()
    if veh["p"] is None:
        print("[chase] pose feed never arrived - aborting rather than filming scenery", flush=True)
        sys.exit(3)
    spawn_rig(node)
    time.sleep(1.0)
    if not node.subscribe(Image, TOPIC, on_image):
        print("[chase] image subscribe failed", flush=True)
        sys.exit(1)
    stop = threading.Event()
    t = threading.Thread(target=follow_loop, args=(node, stop), daemon=True)
    t.start()
    print(f"[chase] recording {duration:.0f}s", flush=True)
    time.sleep(duration)
    stop.set()
    with rec["lock"]:
        p = rec["proc"]
        n = rec["n"]
    if p:
        p.stdin.close()
        p.wait(timeout=30)
        print(f"[chase] wrote {n} frames to {out_path}", flush=True)
    else:
        print("[chase] NO FRAMES - sensors system running? world loaded?", flush=True)
        sys.exit(2)
    # remove our rig so it never feeds anyone stale frames
    ent = Entity()
    ent.name = RIG
    ent.type = Entity.MODEL
    try:
        node.request(f"/world/{WORLD}/remove", ent, Entity, Boolean, 2000)
    except Exception:
        pass


if __name__ == "__main__":
    main()
