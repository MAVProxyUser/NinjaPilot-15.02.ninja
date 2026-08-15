#!/usr/bin/env python3
"""Draw the three trails from a SEPARATE PROCESS.

WHY A PROCESS AND NOT A THREAD - the whole point.

Every /marker call is a BLOCKING gz service request. Doing four per iteration
inside the guidance loop is what produced the 9Hz loop bug that silently
corrupted hours of tuning. Moving them to a background THREAD was not enough
either, and the reason is the GIL: the marker thread still has to marshal
protobuf and hold the interpreter to do it, so the guidance loop stalls
behind it anyway. Measured at the time: 5/5 contacts at 0.58-0.60m with
trails off, versus 0.58 / 1.91 / 2.19 with them on even off-thread. The
mitigation then was to cut the trail to an eighth of its traffic - which
worked, but paid for guidance with visibility.

None of that was ever a shortage of CPU. It is one interpreter serialising
work that has no reason to be serialised. A separate PROCESS has its own GIL
and lands on its own core, so the trails can be drawn at full rate and the
guidance loop never sees them at all.

It also needs nothing from the bridge. The drone and the ball are both in
Gazebo's own pose stream, so this subscribes directly and derives everything
itself - including the target velocity (by differencing) and therefore the
planned lead solution. Zero coupling, zero shared state, nothing to starve.

usage: trail_daemon.py [world]     (default: quadcopter)
"""
import math
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))

# Reuse the bridge's marker helpers rather than re-deriving them - they carry
# hard-won details (the /marker reply is Empty and reports ok=False even on
# success; LINE_STRIP renders at 1px and is invisible, so trails are tubes).
from gazebo_bridge import (            # noqa: E402
    _marker_send, _marker_tube, gazebo_pos_to_ned, lead_solution,
    INTERCEPT_SPEED, TRAIL_DIAMETER,
)

WORLD = sys.argv[1] if len(sys.argv) > 1 else "quadcopter"
SEG_MIN = 0.35          # m between trail segments
RATE_HZ = 20.0

FLOWN_RGBA = (0.10, 0.75, 0.95, 0.55)   # cyan  - where the interceptor went
PLAN_RGBA = (1.00, 0.72, 0.00, 0.45)    # amber - where guidance was aiming
TGT_RGBA = (0.95, 0.15, 0.10, 0.55)     # red   - the object's own track


class Trail:
    def __init__(self, node, base_id, rgba):
        self.node = node
        self.id = base_id
        self.rgba = rgba
        self.last = None
        self.n = 0
        self.err = None

    def tick(self, p):
        if p is None:
            return
        if self.last is None:
            self.last = p
            return
        if math.dist(self.last, p) < SEG_MIN:
            return
        try:
            # _marker_tube expects GAZEBO ENU - the bridge's own TargetTrail
            # converts NED first (pt = (ned[1], ned[0], -ned[2])). Handing it
            # NED drew every segment mirrored and UNDERGROUND (z = -altitude),
            # invisible in flight and briefly clipping through the surface as
            # the ball fell to z~0 - which is exactly what was observed.
            a_enu = (self.last[1], self.last[0], -self.last[2])
            p_enu = (p[1], p[0], -p[2])
            m = _marker_tube(self.id, a_enu, p_enu, self.rgba,
                             diameter=TRAIL_DIAMETER)
            # OWN NAMESPACE. _marker_base stamps every marker
            # "ninjapilot_trail", and the bridge issues DELETE_ALL on exactly
            # that namespace at mission start to clear the previous run's
            # trails - which silently wiped everything this process drew.
            m.ns = "ninjapilot_daemon"
            _marker_send(self.node, m)
            self.n += 1
        except Exception as e:
            self.err = repr(e)
        self.id += 1
        self.last = p


def main():
    import gz.transport13 as gzt
    from gz.msgs10.pose_v_pb2 import Pose_V

    state = {"drone": None, "ball": None, "t": 0.0, "prev": None}

    def on_pose(msg):
        for p in msg.pose:
            if p.name.lower() == "x3":
                state["drone"] = gazebo_pos_to_ned(
                    (p.position.x, p.position.y, p.position.z))
            elif p.name == "target_ball":
                state["ball"] = gazebo_pos_to_ned(
                    (p.position.x, p.position.y, p.position.z))
                state["t"] = time.time()

    node = gzt.Node()
    node.subscribe(Pose_V, f"/world/{WORLD}/pose/info", on_pose)
    print(f"[trails] daemon up on /world/{WORLD}/pose/info (own process, "
          f"own GIL) - flown=cyan planned=amber target=red")

    flown = Trail(node, 10000, FLOWN_RGBA)
    planned = Trail(node, 20000, PLAN_RGBA)
    target = Trail(node, 30000, TGT_RGBA)

    hb = [0.0]
    period = 1.0 / RATE_HZ
    while True:
        t0 = time.time()
        d, b = state["drone"], state["ball"]
        flown.tick(d)
        target.tick(b)
        # Planned = the lead solution the guidance is chasing. Derived here
        # from the ball's own differenced velocity, so this process needs
        # nothing from the bridge.
        if d is not None and b is not None:
            pv = state["prev"]
            if pv is not None and state["t"] > pv[0] + 1e-3:
                dt = state["t"] - pv[0]
                vel = tuple((b[i] - pv[1][i]) / dt for i in range(3))
                if any(abs(v) > 1e-3 for v in vel):
                    try:
                        planned.tick(lead_solution(d, b, vel, INTERCEPT_SPEED))
                    except Exception:
                        pass
            if pv is None or state["t"] > pv[0] + 1e-3:
                state["prev"] = (state["t"], b)
        if int(time.time()) % 5 == 0 and time.time() - hb[0] > 4.5:
            hb[0] = time.time()
            print("[trails] flown=%d target=%d planned=%d  drone=%s ball=%s %s"
                  % (flown.n, target.n, planned.n,
                     "yes" if d is not None else "NO",
                     "yes" if b is not None else "no",
                     flown.err or ""), flush=True)
        slp = period - (time.time() - t0)
        if slp > 0:
            time.sleep(slp)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass
