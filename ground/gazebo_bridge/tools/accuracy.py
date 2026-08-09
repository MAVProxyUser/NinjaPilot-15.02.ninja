#!/usr/bin/env python3
"""Star-mission accuracy scorecard fusing BOTH log sources.

  bridge log  -> ground truth (where the vehicle really was)
  board log   -> what the FC believed (PositionState) and what it was
                 tracking against (PathStatus.error, WaypointActive,
                 AttitudeState.Yaw)

Reports, per leg: cross-track error from truth (the real accuracy number),
the FC's own reported error (does the FC KNOW it is off?), estimator bias
(truth vs FC position = the accuracy ceiling no controller can beat), and
yaw alignment vs the leg bearing.

usage: accuracy.py <bridge.log> <fclog.jsonl>
"""
import json
import math
import re
import sys
from collections import defaultdict

STAR = []
_pts = [(6 * math.cos(math.radians(72 * k)), 6 * math.sin(math.radians(72 * k))) for k in range(5)]
for _k in [0, 2, 4, 1, 3, 0]:
    STAR.append((_pts[_k][0], _pts[_k][1]))
STAR.append((0.0, 0.0))
STAR.append((0.0, 0.0))

TRUTH_RE = re.compile(r"t\+(\d+)s alt=([-\d.]+)m N=([-\d.]+) E=([-\d.]+)(?: -> wp(\d+))?")


def cross_track(p, a, b):
    """Perpendicular distance from p to segment a->b (2D)."""
    dn, de = b[0] - a[0], b[1] - a[1]
    L = math.hypot(dn, de)
    if L < 1e-6:
        return math.hypot(p[0] - a[0], p[1] - a[1])
    t = ((p[0] - a[0]) * dn + (p[1] - a[1]) * de) / (L * L)
    t = max(0.0, min(1.0, t))
    cn, ce = a[0] + t * dn, a[1] + t * de
    return math.hypot(p[0] - cn, p[1] - ce)


def main():
    truth = []
    for line in open(sys.argv[1]):
        m = TRUTH_RE.search(line)
        if m:
            truth.append(dict(t=float(m[1]), alt=float(m[2]), n=float(m[3]),
                              e=float(m[4]), wp=int(m[5]) if m[5] else None))
    recs = [json.loads(l) for l in open(sys.argv[2])]

    print("=== TRUTH: cross-track error per leg (the real accuracy) ===")
    by_leg = defaultdict(list)
    for r in truth:
        wp = r["wp"]
        if wp is None or wp == 0 or wp > len(STAR) - 1:
            continue
        a, b = STAR[wp - 1], STAR[wp]
        by_leg[wp].append(cross_track((r["n"], r["e"]), a, b))
    allerr = []
    for wp in sorted(by_leg):
        errs = by_leg[wp]
        allerr += errs
        print("  leg->wp%-2d  mean %5.2f m  max %5.2f m  (n=%d)"
              % (wp, sum(errs) / len(errs), max(errs), len(errs)))
    if allerr:
        print("  OVERALL   mean %5.2f m  max %5.2f m" % (sum(allerr) / len(allerr), max(allerr)))

    alts = [r["alt"] for r in truth if r["wp"] not in (None, 0)]
    if alts:
        print("  altitude  min %5.2f  max %5.2f  (target 8.00, spread %.2f m)"
              % (min(alts), max(alts), max(alts) - min(alts)))

    print("=== BOARD: what the FC thought it was doing ===")
    ps = [(r["t_us"] / 1e6, r["data"]) for r in recs if r.get("object") == "PathStatus"]
    if ps:
        agg = defaultdict(list)
        for _t, d in ps:
            agg[d["UID"]].append(d["error"])
        for uid in sorted(agg):
            errs = agg[uid]
            print("  FC leg%-2d  mean %5.2f m  max %5.2f m" % (uid, sum(errs) / len(errs), max(errs)))

    # Estimator bias: truth vs FC position, time-aligned by nearest sample.
    pos = [(r["t_us"] / 1e6, r["data"]) for r in recs if r.get("object") == "PositionState"]
    if pos and truth:
        fc_t0 = pos[0][0]
        # align by matching the flight's own N-extremes is fragile; instead
        # compare distributions (bias in position magnitude over the flight)
        fc_r = [math.hypot(d["North"], d["East"]) for _t, d in pos]
        tr_r = [math.hypot(r["n"], r["e"]) for r in truth]
        print("=== ESTIMATOR: truth vs FC position (accuracy ceiling) ===")
        print("  radius-from-home  truth mean %5.2f m   FC mean %5.2f m   bias %+.2f m"
              % (sum(tr_r) / len(tr_r), sum(fc_r) / len(fc_r),
                 sum(fc_r) / len(fc_r) - sum(tr_r) / len(tr_r)))

    # Yaw alignment vs leg bearing
    wpa = [(r["t_us"] / 1e6, r["data"]["Index"]) for r in recs if r.get("object") == "WaypointActive"]
    yaw = [(r["t_us"] / 1e6, r["data"]["Yaw"]) for r in recs if r.get("object") == "AttitudeState"]
    if wpa and yaw:
        print("=== YAW: heading vs leg bearing (point-turn quality) ===")
        events = sorted([(t, "wp", v) for t, v in wpa] + [(t, "yaw", v) for t, v in yaw])
        cur = None
        per = defaultdict(list)
        for t, kind, v in events:
            if kind == "wp":
                cur = v
            elif cur is not None:
                per[cur].append((t, v))
        for wp in sorted(per):
            if wp == 0 or wp > len(STAR) - 1:
                continue
            a, b = STAR[wp - 1], STAR[wp]
            bearing = math.degrees(math.atan2(b[1] - a[1], b[0] - a[0]))
            samples = per[wp]
            if not samples:
                continue
            errs = []
            for _t, y in samples:
                e = (y - bearing + 180) % 360 - 180
                errs.append(abs(e))
            settled = errs[len(errs) // 2:] or errs
            print("  leg->wp%-2d bearing %7.1f  yaw err: first %5.1f  settled-mean %5.1f"
                  % (wp, bearing, errs[0], sum(settled) / len(settled)))


if __name__ == "__main__":
    main()
