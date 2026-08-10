#!/usr/bin/env python3
"""Plot an intercept attempt: both tracks, the separation, and the strike.

The scalars ("min separation 1.8m") do not say WHY a run missed, and the two
failure modes need completely different fixes:

  - a CROSS-TRACK miss means the guidance is aiming wrong (bad lead angle,
    stale target velocity, a sign error)
  - a TIMING miss means the guidance is aiming right and we simply are not
    there yet - the interceptor is too slow, or it committed to the chase
    too late

On the top-down those look nothing alike: a cross-track miss shows the two
paths crossing with a gap at the crossing; a timing miss shows our path
arriving at the right place but behind the target's position at that moment.
The separation-vs-time panel separates them further - a timing miss has a
sharp V (we sweep past the point after it has gone), a cross-track miss has
a rounded floor.

usage: intercept_plot.py <label>_track.json <out.png>
"""
import json
import math
import sys

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt


def main():
    d = json.load(open(sys.argv[1]))
    out = sys.argv[2]
    tr = d["track"]
    if not tr:
        print("  (empty track - the run never entered the intercept loop)")
        return

    t = [r[0] for r in tr]
    dn = [r[1][0] for r in tr]
    de = [r[1][1] for r in tr]
    dd = [-r[1][2] for r in tr]
    tn = [r[2][0] for r in tr]
    te = [r[2][1] for r in tr]
    td = [-r[2][2] for r in tr]
    sep = [r[4] for r in tr]
    gs = [r[5] for r in tr]

    imin = min(range(len(sep)), key=lambda i: sep[i])
    hit = d.get("hit_gz")
    hitd = d.get("hit_dist", 0.55)

    fig = plt.figure(figsize=(15, 5.2))

    # --- top-down: plot frame is x=East, y=North (mirrored vs NED order;
    #     getting this backwards inverted every turn-direction verdict for
    #     most of a session, so it is spelled out here)
    ax = fig.add_subplot(1, 3, 1)
    ax.plot(te, tn, "-", color="#e8541e", lw=2.2, label="target track")
    ax.plot(de, dn, "-", color="#12a4c8", lw=2.2, label="interceptor")
    ax.plot(te[0], tn[0], "o", color="#e8541e", ms=7)
    ax.plot(de[0], dn[0], "o", color="#12a4c8", ms=7)
    ax.plot([de[imin], te[imin]], [dn[imin], tn[imin]], "-",
            color="0.35", lw=1.2)
    ax.plot(te[imin], tn[imin], "x", color="k", ms=9)
    circ = plt.Circle((te[imin], tn[imin]), hitd, fill=False,
                      color="0.45", ls="--", lw=1.0)
    ax.add_patch(circ)
    ax.annotate("closest %.2fm" % sep[imin],
                (te[imin], tn[imin]), textcoords="offset points",
                xytext=(8, 8), fontsize=8)
    ax.set_aspect("equal", "datalim")
    ax.set_xlabel("East (m)")
    ax.set_ylabel("North (m)")
    ax.set_title("%s - top down%s" % (d.get("label", "intercept"),
                                      "  *** CONTACT ***" if hit else ""))
    ax.grid(alpha=0.3)
    ax.legend(fontsize=8)

    # --- altitude
    ax = fig.add_subplot(1, 3, 2)
    ax.plot(t, td, "-", color="#e8541e", lw=2, label="target")
    ax.plot(t, dd, "-", color="#12a4c8", lw=2, label="interceptor")
    ax.axvline(t[imin], color="0.5", ls="--", lw=1)
    ax.set_xlabel("time (s)")
    ax.set_ylabel("altitude (m)")
    ax.set_title("altitude")
    ax.grid(alpha=0.3)
    ax.legend(fontsize=8)

    # --- separation + the IMU trace that confirms a strike
    ax = fig.add_subplot(1, 3, 3)
    ax.plot(t, sep, "-", color="#333333", lw=2, label="separation")
    ax.axhline(hitd, color="#c0392b", ls="--", lw=1.2,
               label="contact radius %.2fm" % hitd)
    ax.plot(t[imin], sep[imin], "o", color="#c0392b", ms=7)
    ax.set_xlabel("time (s)")
    ax.set_ylabel("separation (m)")
    ax.set_ylim(0, max(6.0, min(40.0, max(sep))))
    ax2 = ax.twinx()
    ax2.plot(t, gs, "-", color="#7a9a01", lw=1.0, alpha=0.75)
    ax2.set_ylabel("IMU |a| (g)", color="#7a9a01")
    ax2.tick_params(axis="y", labelcolor="#7a9a01")
    ax.set_title("closure  (min %.2fm)" % sep[imin])
    ax.grid(alpha=0.3)
    ax.legend(fontsize=8, loc="upper right")

    fig.tight_layout()
    fig.savefig(out, dpi=110)
    print("  wrote %s  (%d samples, min sep %.2fm%s)"
          % (out, len(tr), sep[imin], ", CONTACT" if hit else ""))


if __name__ == "__main__":
    main()
