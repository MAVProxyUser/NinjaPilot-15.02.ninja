#!/usr/bin/env python3
"""Per-waypoint arrival accuracy: did we actually get ON the point, and did we
sit there?

The cross-track score in score.py answers "were the legs straight", which is a
different question from "did we touch the corners". A run can have beautiful
legs and still cut every corner by a metre. This tool answers, for each
waypoint:

  closest   - minimum distance to the planned point at any time (m)
  at_retire - distance at the instant the plan advanced to the next waypoint
  dwell     - seconds spent inside 0.5 m of the point
  overshoot - max distance PAST the point along the inbound leg direction (m),
              i.e. how far we sailed through it

usage: wp_arrival.py <fclog.jsonl> [wp_radius]
"""
import json
import math
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from star_geom import ORDER as STAR


def main():
    recs = [json.loads(l) for l in open(sys.argv[1])]
    t0 = recs[0]["t_us"] / 1e6
    pos = [(r["t_us"] / 1e6 - t0, r["data"]["North"], r["data"]["East"], -r["data"]["Down"])
           for r in recs if r.get("object") == "PositionState"]
    wpa = [(r["t_us"] / 1e6 - t0, int(r["data"]["Index"]))
           for r in recs if r.get("object") == "WaypointActive"]
    if not wpa or not pos:
        print("  (no waypoint/position data)")
        return

    # Collapse WaypointActive to transitions: when index N becomes active, the
    # vehicle is flying TOWARD waypoint N, and it retires when N+1 activates.
    trans = []
    for t, idx in wpa:
        if not trans or trans[-1][1] != idx:
            trans.append((t, idx))

    print("  wp   closest  at_retire   dwell<0.5m  overshoot")
    tot_close = 0.0
    tot_over = 0.0
    n = 0
    for k, (t_on, idx) in enumerate(trans):
        if idx >= len(STAR):
            continue
        t_off = trans[k + 1][0] if k + 1 < len(trans) else pos[-1][0]
        tgt = STAR[idx]
        seg = [p for p in pos if t_on <= p[0] <= t_off]
        if len(seg) < 3:
            continue
        # inbound leg direction, for the overshoot projection
        prev = STAR[idx - 1] if idx > 0 else (seg[0][1], seg[0][2])
        dn, de = tgt[0] - prev[0], tgt[1] - prev[1]
        L = math.hypot(dn, de) or 1.0
        un, ue = dn / L, de / L

        best = min(math.hypot(p[1] - tgt[0], p[2] - tgt[1]) for p in seg)
        last = seg[-1]
        at_ret = math.hypot(last[1] - tgt[0], last[2] - tgt[1])
        dwell = 0.0
        for a, b in zip(seg, seg[1:]):
            if math.hypot(a[1] - tgt[0], a[2] - tgt[1]) < 0.5:
                dwell += b[0] - a[0]
        # positive = travelled beyond the waypoint along the inbound direction
        over = max((p[1] - tgt[0]) * un + (p[2] - tgt[1]) * ue for p in seg)
        print("  wp%d   %5.2f m   %5.2f m    %5.1f s     %+5.2f m"
              % (idx, best, at_ret, dwell, over))
        tot_close += best
        tot_over += max(0.0, over)
        n += 1
    if n:
        print("  mean closest approach %.2f m   mean overshoot %.2f m  (n=%d)"
              % (tot_close / n, tot_over / n, n))


if __name__ == "__main__":
    main()
