#!/usr/bin/env python3
"""Is the CORNER being commanded badly, or flown badly?

Cross-track and arrival distance both answer "where did it end up". Neither
distinguishes a path layer that asks for an orbit from a vehicle that cannot
fly a clean request - and at a corner that is the whole question. This
compares, per corner:

  cmd swing   - peak-to-peak of |VelocityDesired| while inside the corner.
                A commanded orbit shows up here as a large swing; a tracking
                failure does not.
  fprog back  - how far fractional_progress ran BACKWARDS. Progress is a
                property of the path; if it regresses, the profile is being
                driven by the vehicle's own speed (the lead term closes that
                loop) and the result is a relaxation oscillator.
  reversals   - sign changes of the commanded along-track velocity.
  approach    - distance samples, to see the swing directly.

usage: corner_probe.py <fclog.jsonl> [radius_m]
"""
import json
import math
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from star_geom import ORDER


def main():
    recs = [json.loads(l) for l in open(sys.argv[1])]
    R = float(sys.argv[2]) if len(sys.argv) > 2 else 2.0
    t0 = recs[0]["t_us"] / 1e6

    def series(name, fn):
        return sorted((r["t_us"] / 1e6 - t0, fn(r["data"]))
                      for r in recs if r.get("object") == name)

    pos = series("PositionState", lambda d: (d["North"], d["East"]))
    vd = series("VelocityDesired", lambda d: (d["North"], d["East"]))
    ps = series("PathStatus", lambda d: d.get("fractional_progress"))
    wpa = series("WaypointActive", lambda d: int(d["Index"]))
    if not vd:
        print("  (no VelocityDesired in log - enable it in FC_LOG_OBJECTS_MISSION)")
        return

    tr = []
    for t, i in wpa:
        if not tr or tr[-1][1] != i:
            tr.append((t, i))

    def at(seq, t, w=0.4):
        best, bd = None, w
        for tt, v in seq:
            d = abs(tt - t)
            if d < bd:
                bd, best = d, v
        return best

    print("  wp   cmd swing   fprog back   reversals   dist swing in %.1fm" % R)
    tot_swing = tot_back = tot_rev = 0.0
    n = 0
    for k, (ton, idx) in enumerate(tr):
        if k + 1 >= len(tr) or idx >= len(ORDER):
            continue
        toff = tr[k + 1][0]
        tgt = ORDER[idx]
        # samples while inside the corner radius
        inside = [(t, p) for t, p in pos
                  if ton <= t <= toff
                  and math.hypot(p[0] - tgt[0], p[1] - tgt[1]) < R]
        if len(inside) < 5:
            continue
        t_in, t_out = inside[0][0], inside[-1][0]

        mags, alongs = [], []
        for t, p in inside:
            v = at(vd, t)
            if v is None:
                continue
            mags.append(math.hypot(*v))
            dn, de = tgt[0] - p[0], tgt[1] - p[1]
            L = math.hypot(dn, de) or 1.0
            alongs.append(v[0] * dn / L + v[1] * de / L)
        if not mags:
            continue
        swing = max(mags) - min(mags)
        rev = sum(1 for a, b in zip(alongs, alongs[1:]) if a > 0.05 and b < -0.05)

        fp = [v for t, v in ps if t_in <= t <= t_out and v is not None]
        back = 0.0
        peak = -1e9
        for v in fp:
            if v > peak:
                peak = v
            back = max(back, peak - v)

        ds = [math.hypot(p[0] - tgt[0], p[1] - tgt[1]) for _, p in inside]
        print("  wp%d   %6.2f m/s    %6.3f       %3d        %.2f..%.2f m"
              % (idx, swing, back, rev, min(ds), max(ds)))
        tot_swing += swing
        tot_back += back
        tot_rev += rev
        n += 1
    if n:
        print("  mean cmd swing %.2f m/s   mean fprog regression %.3f   "
              "total reversals %d" % (tot_swing / n, tot_back / n, int(tot_rev)))


if __name__ == "__main__":
    main()
