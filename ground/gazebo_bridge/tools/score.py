#!/usr/bin/env python3
"""One-line score for a star run, computed from the BOARD log alone.

Dense (100ms) flown path vs the planned star geometry: this is the numeric
form of the planned-vs-flown trail comparison in the Gazebo view. Prints a
single line so runs can be stacked into a table and compared.

usage: score.py <label> <fclog.jsonl>
"""
import json, math, sys

import os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from star_geom import ORDER as STAR

def xtrack(p, a, b):
    dn, de = b[0]-a[0], b[1]-a[1]
    L = math.hypot(dn, de)
    if L < 1e-6:
        return math.hypot(p[0]-a[0], p[1]-a[1])
    t = max(0.0, min(1.0, ((p[0]-a[0])*dn + (p[1]-a[1])*de)/(L*L)))
    return math.hypot(p[0]-(a[0]+t*dn), p[1]-(a[1]+t*de))

def main():
    label, path = sys.argv[1], sys.argv[2]
    recs = [json.loads(l) for l in open(path)]
    t0 = recs[0]["t_us"]/1e6
    pos = [(r["t_us"]/1e6-t0, r["data"]["North"], r["data"]["East"], -r["data"]["Down"])
           for r in recs if r.get("object")=="PositionState"]
    wpa = [(r["t_us"]/1e6-t0, r["data"]["Index"])
           for r in recs if r.get("object")=="WaypointActive"]
    if not pos or not wpa:
        print("%-10s NO DATA" % label); return
    # active waypoint at each position sample
    errs, alts = [], []
    wi = 0
    for (t, n, e, a) in pos:
        while wi+1 < len(wpa) and wpa[wi+1][0] <= t:
            wi += 1
        idx = wpa[wi][1]
        if idx < 1 or idx > 5 or a < 6.0:
            continue           # star legs only, at altitude
        errs.append(xtrack((n,e), STAR[idx-1], STAR[idx]))
        alts.append(a-8.0)
    if not errs:
        print("%-10s NO STAR-LEG SAMPLES" % label); return
    errs_sorted = sorted(errs)
    p95 = errs_sorted[int(0.95*len(errs_sorted))-1]
    rate = len(pos)/max(pos[-1][0]-pos[0][0], 1e-6)
    print("%-10s xtrack mean %5.2f  p95 %5.2f  max %5.2f m | alt err mean %+5.2f p2p %5.2f m | n=%4d @%4.1fHz"
          % (label, sum(errs)/len(errs), p95, max(errs),
             sum(alts)/len(alts), max(alts)-min(alts), len(errs), rate))

if __name__ == "__main__":
    main()
