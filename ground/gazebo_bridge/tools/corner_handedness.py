#!/usr/bin/env python3
"""Which way does the ground track curl at each star vertex - and does it
match the direction of the corner?

This is the measurement of the user-visible "cursive-l loop": at a right-hand
corner the track should curl RIGHT (clockwise on the plot); a LEFT curl means
the vehicle looped over itself to get onto the next leg.

Three earlier attempts at this measurement were wrong, each differently, and
each wrongness cost real argument time - recorded here so none is repeated:

  1. Cross product computed in (North, East) order. That frame is MIRRORED
     relative to the plot (x=East, y=North), so every verdict was inverted -
     "agrees with the turn" while the user watched it hook the wrong way.
  2. Path-length / straight-line ratio. Confounded by arrival quality: a
     tighter arrival spends longer in the window and shrinks the denominator,
     so the metric got WORSE as the corner visually improved.
  3. Windowing by leg time span. Once the waypoint started retiring early,
     the corner samples fall in the NEXT leg's time window, so the corners
     silently vanished from the measurement ("0 of 0 correct").

This version is vertex-centred and time-clustered: for each geometric vertex,
take ALL position samples within RADIUS of it, split into visits (shared
vertices like (6,0) are visited twice), pick the visit whose entry direction
matches the inbound leg, and integrate the SIGNED heading change of the track
in the PLOT frame (x=East, y=North; positive = counter-clockwise = LEFT).

usage: corner_handedness.py <fclog.jsonl>
"""
import json
import math
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from star_geom import ORDER

RADIUS = 2.0


def ang(a, b):
    return math.degrees(math.atan2(a[0] * b[1] - a[1] * b[0],
                                   a[0] * b[0] + a[1] * b[1]))


def main():
    recs = [json.loads(l) for l in open(sys.argv[1])]
    if not recs:
        print("  (empty log)")
        return
    t0 = recs[0]["t_us"] / 1e6
    pos = sorted((r["t_us"] / 1e6 - t0, r["data"]["North"], r["data"]["East"])
                 for r in recs if r.get("object") == "PositionState")

    print("  plot frame: + = LEFT (counter-clockwise on screen)")
    print("  vertex   corner needs      track did     verdict")
    good = tot = 0
    for vi in range(1, len(ORDER) - 1):
        a, b, c = ORDER[vi - 1], ORDER[vi], ORDER[vi + 1]
        if (math.hypot(b[0] - a[0], b[1] - a[1]) < 0.5
                or math.hypot(c[0] - b[0], c[1] - b[1]) < 0.5):
            continue
        need = ang((b[1] - a[1], b[0] - a[0]), (c[1] - b[1], c[0] - b[0]))
        near = [(t, n, e) for t, n, e in pos
                if math.hypot(n - b[0], e - b[1]) < RADIUS]
        if not near:
            continue
        visits = [[near[0]]]
        for s in near[1:]:
            if s[0] - visits[-1][-1][0] > 4.0:
                visits.append([s])
            else:
                visits[-1].append(s)
        din = (b[1] - a[1], b[0] - a[0])
        L = math.hypot(*din)
        din = (din[0] / L, din[1] / L)
        best = None
        for v in visits:
            if len(v) < 6:
                continue
            e0, n0 = v[0][2], v[0][1]
            ref = None
            for t2, n2, e2 in v[1:]:
                if math.hypot(e2 - e0, n2 - n0) >= 0.5:
                    ref = (e2 - e0, n2 - n0)
                    break
            if not ref:
                continue
            m = math.hypot(*ref)
            match = (ref[0] * din[0] + ref[1] * din[1]) / m
            if best is None or match > best[0]:
                best = (match, v)
        if not best:
            continue
        v = best[1]
        w = [(v[i + 1][2] - v[i][2], v[i + 1][1] - v[i][1])
             for i in range(len(v) - 1)]
        w = [x for x in w if math.hypot(*x) > 0.005]
        if len(w) < 3:
            continue
        got = sum(ang(p, q) for p, q in zip(w, w[1:]))
        ok = need * got > 0
        good += ok
        tot += 1
        print("   v%d      %+5.0f (%s)      %+6.0f (%s)    %s"
              % (vi, need, "LEFT " if need > 0 else "RIGHT",
                 got, "LEFT " if got > 0 else "RIGHT",
                 "OK" if ok else "*** WRONG WAY ***"))
    if tot:
        print("  -> %d of %d corners turn the correct way" % (good, tot))
    else:
        print("  (no corners measurable)")


if __name__ == "__main__":
    main()
