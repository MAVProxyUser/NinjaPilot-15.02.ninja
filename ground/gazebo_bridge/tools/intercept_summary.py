#!/usr/bin/env python3
"""Tabulate every intercept attempt in a directory.

One successful intercept proves the mechanism works; it does not prove the
guidance is any good. This project has already been burned by believing a
single run (three consecutive clean flights preceded the star113 tumble, and
a 0.05m "improvement" turned out to be inside run-to-run noise). A hit rate
and a spread across runs is the claim worth making.

Reports, per run and in aggregate:
  min_sep     closest centre-to-centre approach
  horiz/vert  how the closest approach decomposed - a vertical miss and a
              horizontal miss have completely different causes (the first
              intercept missed vertically by 28cm because correction_vector[2]
              was zeroed, which no scalar separation number would reveal)
  peak_g      what the vehicle's own IMU felt
  contact     Gazebo ground truth

usage: intercept_summary.py <dir-with-*_track.json>
"""
import glob
import json
import math
import os
import sys


def main():
    d = sys.argv[1] if len(sys.argv) > 1 else "."
    files = sorted(glob.glob(os.path.join(d, "*_track.json")))
    if not files:
        print("no *_track.json in %s" % d)
        return

    print("  %-10s %8s %8s %8s %7s %8s  %s"
          % ("run", "min_sep", "horiz", "vert", "peak_g", "t_hit", "result"))
    seps, hits, gs = [], 0, []
    for f in files:
        try:
            j = json.load(open(f))
        except Exception:
            continue
        tr = j.get("track") or []
        if not tr:
            print("  %-10s %8s %8s %8s %7s %8s  no track"
                  % (os.path.basename(f).replace("_track.json", ""),
                     "-", "-", "-", "-", "-"))
            continue
        i = min(range(len(tr)), key=lambda k: tr[k][4])
        t, dn, tn, _vel, sep, _g = tr[i]
        # True closest approach, not the closest SAMPLE. Both objects move
        # roughly linearly between samples, so the minimum of |r(t)| over the
        # interval has a closed form; sampling alone under-reports contact
        # (icpt04: sampled 0.58m, IMU felt 4.0g).
        for k in range(len(tr) - 1):
            p0 = [tr[k][2][j] - tr[k][1][j] for j in range(3)]
            p1 = [tr[k + 1][2][j] - tr[k + 1][1][j] for j in range(3)]
            dv = [p1[j] - p0[j] for j in range(3)]
            dd = sum(x * x for x in dv)
            if dd < 1e-9:
                continue
            u = -sum(p0[j] * dv[j] for j in range(3)) / dd
            if 0.0 < u < 1.0:
                cp = [p0[j] + u * dv[j] for j in range(3)]
                s_ = math.sqrt(sum(x * x for x in cp))
                if s_ < sep:
                    sep = s_
        horiz = math.hypot(tn[0] - dn[0], tn[1] - dn[1])
        vert = tn[2] - dn[2]
        peak = max(r[5] for r in tr)
        hit = bool(j.get("hit_gz"))
        imu = bool(j.get("hit_imu"))
        res = ("HIT+FELT" if (hit and imu) else
               "HIT" if hit else "miss")
        print("  %-10s %8.3f %8.3f %+8.3f %7.2f %8.1f  %s"
              % (os.path.basename(f).replace("_track.json", ""),
                 sep, horiz, vert, peak, t, res))
        seps.append(sep)
        gs.append(peak)
        hits += hit
    n = len(seps)
    if n:
        seps_s = sorted(seps)
        print()
        print("  %d runs | contact %d/%d (%.0f%%) | min_sep median %.3f  best %.3f  worst %.3f"
              % (n, hits, n, 100.0 * hits / n,
                 seps_s[n // 2], seps_s[0], seps_s[-1]))
        print("  peak IMU across runs: %.2f g (hover baseline is ~1.0)" % max(gs))


if __name__ == "__main__":
    main()
