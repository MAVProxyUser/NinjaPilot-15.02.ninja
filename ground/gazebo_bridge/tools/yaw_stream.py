import math, time, sys
import gz.transport13 as transport
from gz.msgs10.pose_v_pb2 import Pose_V
samples = []
def on_pose(msg):
    for p in msg.pose:
        if p.name == "x3":
            q = (p.orientation.w, p.orientation.x, p.orientation.y, p.orientation.z)
            # ENU yaw
            siny = 2*(q[0]*q[3]+q[1]*q[2]); cosy = 1-2*(q[2]*q[2]+q[3]*q[3])
            yaw_enu = math.degrees(math.atan2(siny, cosy))
            heading = (90 - yaw_enu) % 360
            samples.append((time.time(), heading))
node = transport.Node()
node.subscribe(Pose_V, "/world/quadcopter/pose/info", on_pose)
time.sleep(15)
if samples:
    t0 = samples[0][0]
    keep = []
    last = 0
    for t, h in samples:
        if t - t0 >= last:
            keep.append((t-t0, h)); last += 0.5
    for t, h in keep:
        print("t=%5.1f heading=%7.2f" % (t, h))
    hs = [h if h < 180 else h-360 for _, h in samples]
    import statistics
    print("mean=%.1f min=%.1f max=%.1f span=%.1f deg  stdev=%.2f" %
          (statistics.mean(hs), min(hs), max(hs), max(hs)-min(hs), statistics.pstdev(hs)))
