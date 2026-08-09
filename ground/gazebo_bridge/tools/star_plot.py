#!/usr/bin/env python3
"""Render planned vs flown for the star mission - the same comparison the
Gazebo trails show, but as a PNG that can be inspected frame-by-frame.

Uses the BOARD log for the flown path (100ms PositionState, far denser
than the bridge's 2s prints, so oscillation is actually visible) and the
known star geometry for the plan.

usage: star_plot.py <fclog.jsonl> <out.png>
"""
import json
import math
import os
import sys

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from star_geom import ORDER, OUTLINE

# Planned path as flown: climb at centre, the star, then home.
STAR = ORDER


def main():
    recs = [json.loads(l) for l in open(sys.argv[1])]
    out = sys.argv[2]
    t0 = recs[0]["t_us"] / 1e6

    pos = [(r["t_us"] / 1e6 - t0, r["data"]["North"], r["data"]["East"], -r["data"]["Down"])
           for r in recs if r.get("object") == "PositionState"]
    wpa = [(r["t_us"] / 1e6 - t0, r["data"]["Index"])
           for r in recs if r.get("object") == "WaypointActive"]
    # Restrict to the star portion: from first waypoint activity to the
    # last sample above 6m (excludes climb-in and the landing descent).
    if wpa:
        tstart = wpa[0][0]
    else:
        tstart = 0.0
    cruise = [p for p in pos if p[0] >= tstart and p[3] > 6.0]
    if len(cruise) < 10:
        cruise = [p for p in pos if p[0] >= tstart]

    pn = [s[0] for s in STAR] + [STAR[0][0]]
    pe = [s[1] for s in STAR] + [STAR[0][1]]
    fn = [p[1] for p in cruise]
    fe = [p[2] for p in cruise]
    fa = [p[3] for p in cruise]
    ft = [p[0] for p in cruise]

    fig = plt.figure(figsize=(16, 7))

    ax = fig.add_subplot(1, 2, 1)
    ax.plot(pe, pn, "-", color="orange", lw=3, alpha=0.55, label="planned", zorder=1)
    ax.scatter([s[1] for s in STAR], [s[0] for s in STAR], color="orange",
               s=90, zorder=3, marker="o", edgecolors="k", label="waypoints")
    ax.plot(fe, fn, "-", color="deepskyblue", lw=1.4, label="flown (board log)", zorder=2)
    for i, s in enumerate(STAR[:6]):
        ax.annotate("wp%d" % i, (s[1], s[0]), fontsize=9,
                    xytext=(5, 5), textcoords="offset points")
    ax.set_xlabel("East (m)")
    ax.set_ylabel("North (m)")
    ax.axis("equal")
    ax.grid(alpha=0.3)
    ax.legend(loc="upper right", fontsize=9)
    ax.set_title("planned vs flown (top-down)")

    ax2 = fig.add_subplot(1, 2, 2)
    ax2.plot(ft, fa, color="deepskyblue", lw=1.2, label="altitude")
    ax2.axhline(8.0, ls="--", color="orange", alpha=0.8, label="target 8m")
    for t, idx in wpa:
        if tstart <= t <= (ft[-1] if ft else 0):
            ax2.axvline(t, color="gray", alpha=0.35, lw=0.8)
    ax2.set_xlabel("t (s, board clock)")
    ax2.set_ylabel("altitude (m)")
    ax2.grid(alpha=0.3)
    ax2.legend(fontsize=9)
    ax2.set_title("altitude (grey lines = waypoint changes)")

    fig.tight_layout()
    fig.savefig(out, dpi=100)
    print("wrote %s  (%d flown samples over %.0fs)"
          % (out, len(cruise), (ft[-1] - ft[0]) if ft else 0))


if __name__ == "__main__":
    main()
