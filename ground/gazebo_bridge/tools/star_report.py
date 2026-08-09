#!/usr/bin/env python3
"""Star-mission scorecard: onboard FC log vs bridge truth log.
argv[1] = bridge star log, argv[2] = fclog jsonl
Reports corner overshoot (truth), FC cross-track per leg, altitude band,
yaw vs leg bearing (pathdirection check), duration."""
import json
import math
import re
import sys
from collections import defaultdict

STAR = []
_s = [(6 * math.cos(math.radians(72 * k)), 6 * math.sin(math.radians(72 * k))) for k in range(5)]
for k in [0, 2, 4, 1, 3, 0]:
    STAR.append((_s[k][0], _s[k][1], -8.0))
STAR.append((0.0, 0.0, -8.0))
STAR.append((0.0, 0.0, -8.0))

TRUTH_RE = re.compile(
    r"t\+(\d+)s alt=([-\d.]+)m N=([-\d.]+) E=([-\d.]+)(?: -> wp(\d+))?")


def main():
    truth = []
    for line in open(sys.argv[1]):
        m = TRUTH_RE.search(line)
        if m:
            truth.append((float(m[1]), float(m[2]), float(m[3]), float(m[4]),
                          int(m[5]) if m[5] is not None else None))
    recs = [json.loads(l) for l in open(sys.argv[2])]

    print("== corner overshoot at star hairpins (truth, m past corner) ==")
    worst = 0.0
    for i in range(1, 6):
        a, b = STAR[i - 1], STAR[i]
        d = (b[0] - a[0], b[1] - a[1])
        L = math.hypot(*d)
        u = (d[0] / L, d[1] / L)
        w = 0.0
        for (t, alt, n, e, wp) in truth:
            if wp == i + 1:
                w = max(w, (n - b[0]) * u[0] + (e - b[1]) * u[1])
        worst = max(worst, w)
        print("  wp%d  %5.2f m" % (i, w))
    print("  worst: %.2f m" % worst)

    print("== FC PathStatus.error per leg ==")
    agg = defaultdict(list)
    for r in recs:
        if r.get("object") == "PathStatus":
            agg[r["data"]["UID"]].append(r["data"]["error"])
    for uid in sorted(agg):
        errs = agg[uid]
        print("  wp%-2d mean %5.2f  max %5.2f" % (uid, sum(errs) / len(errs), max(errs)))

    alts = [alt for (t, alt, n, e, wp) in truth if wp is not None and 1 <= (wp or 0) <= 5]
    if alts:
        print("== altitude during star legs: min %.2f max %.2f (target 8.0) ==" % (min(alts), max(alts)))

    print("== yaw vs leg bearing (pathdirection check) ==")
    bearings = {}
    for i in range(1, len(STAR)):
        a, b = STAR[i - 1], STAR[i]
        if math.hypot(b[0] - a[0], b[1] - a[1]) > 0.1:
            bearings[i] = math.degrees(math.atan2(b[1] - a[1], b[0] - a[0]))
    # active waypoint from WaypointActive records; yaw from AttitudeState
    events = []
    for r in recs:
        if r.get("object") == "WaypointActive":
            events.append((r["t_us"] / 1e6, "wp", r["data"]["Index"]))
        elif r.get("object") == "AttitudeState":
            events.append((r["t_us"] / 1e6, "yaw", r["data"]["Yaw"]))
    events.sort(key=lambda x: x[0])
    cur = None
    yaw_by_wp = defaultdict(list)
    for (t, kind, v) in events:
        if kind == "wp":
            cur = v
        elif cur is not None:
            yaw_by_wp[cur].append(v)
    for wp in sorted(yaw_by_wp):
        if wp in bearings and yaw_by_wp[wp]:
            ys = yaw_by_wp[wp][len(yaw_by_wp[wp]) // 2:]  # settled half
            mean = sum(ys) / len(ys)
            err = (mean - bearings[wp] + 180) % 360 - 180
            print("  wp%-2d bearing %7.1f  yaw(settled) %7.1f  err %6.1f" %
                  (wp, bearings[wp], mean, err))

    ts = [t for (t, alt, n, e, wp) in truth]
    print("== duration: %ds (engage->last sample) ==" % (ts[-1] - ts[0]))


if __name__ == "__main__":
    main()
