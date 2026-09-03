#!/usr/bin/env python3
"""Turn a wroom pilot track CSV into the planned-vs-flown picture:
top-down GPS vs truth, altitude profile, attitude + sticks timeline.

  usage: wroom_report.py <track.csv> <out.png>
"""
import csv
import sys

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt


def main():
    path, out = sys.argv[1], sys.argv[2]
    rows = list(csv.DictReader(open(path)))
    if not rows:
        print("empty track", file=sys.stderr)
        return 1
    t = [float(r["t"]) for r in rows]
    gn = [float(r["nav_n"]) for r in rows]
    ge = [float(r["nav_e"]) for r in rows]
    ga = [float(r["nav_alt"]) for r in rows]
    tn = [float(r["truth_n"]) for r in rows]
    te = [float(r["truth_e"]) for r in rows]
    ta = [float(r["truth_alt"]) for r in rows]
    roll = [float(r["fc_roll"]) for r in rows]
    pitch = [float(r["fc_pitch"]) for r in rows]
    thr = [float(r["stick_thr"]) for r in rows]
    sroll = [float(r["stick_roll"]) for r in rows]
    spitch = [float(r["stick_pitch"]) for r in rows]

    # phase-change markers
    phases = []
    for i, r in enumerate(rows):
        if i == 0 or r["phase"] != rows[i - 1]["phase"]:
            phases.append((t[i], r["phase"]))

    fig, axes = plt.subplots(1, 3, figsize=(16, 5))
    ax = axes[0]
    ax.plot(te, tn, color="c", lw=1.5, label="truth")
    ax.plot(ge, gn, color="orange", lw=1.0, alpha=0.8, label="GPS (nav feed)")
    ax.plot([0], [0], "k^", ms=10, label="home")
    ax.set_xlabel("East (m)")
    ax.set_ylabel("North (m)")
    ax.set_title("top-down")
    ax.axis("equal")
    ax.grid(True, alpha=0.3)
    ax.legend(fontsize=8)

    ax = axes[1]
    ax.plot(t, ta, color="c", lw=1.5, label="truth alt")
    ax.plot(t, ga, color="orange", lw=1.0, alpha=0.8, label="GPS alt")
    for tx, name in phases:
        ax.axvline(tx, color="gray", alpha=0.3, lw=0.7)
        ax.text(tx, ax.get_ylim()[1] * 0.02, name, rotation=90, fontsize=6, va="bottom")
    ax.set_xlabel("t (s)")
    ax.set_ylabel("altitude (m)")
    ax.set_title("altitude profile")
    ax.grid(True, alpha=0.3)
    ax.legend(fontsize=8)

    ax = axes[2]
    ax.plot(t, roll, "r", lw=0.8, label="FC roll")
    ax.plot(t, pitch, "b", lw=0.8, label="FC pitch")
    ax.plot(t, [s * 42 for s in sroll], "r--", lw=0.8, alpha=0.6, label="cmd roll")
    ax.plot(t, [s * 42 for s in spitch], "b--", lw=0.8, alpha=0.6, label="cmd pitch")
    ax2 = ax.twinx()
    ax2.plot(t, thr, "g", lw=0.8, alpha=0.5, label="throttle")
    ax2.set_ylabel("throttle", color="g")
    ax2.set_ylim(0, 1)
    ax.set_xlabel("t (s)")
    ax.set_ylabel("deg")
    ax.set_title("attitude vs command")
    ax.grid(True, alpha=0.3)
    ax.legend(fontsize=7, loc="upper left")

    fig.suptitle(path.split("/")[-1])
    fig.tight_layout()
    fig.savefig(out, dpi=110)
    print("report: %s" % out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
