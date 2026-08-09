#!/usr/bin/env python3
"""Corner-quality analysis for a mission run.

Inputs:
  argv[1] = bridge mission log (the [test] t+..s alt=..m N=.. E=.. lines are
            ground truth at 2s cadence)
  argv[2] = pulled FC log JSONL (PathStatus records carry the flight
            controller's own cross-track error + active waypoint UID;
            PositionState carries the estimator position at 500ms)
  argv[3] = output PNG path

Outputs: per-waypoint overshoot table (truth), per-leg PathStatus.error
stats (FC's own view), and a 3-panel PNG (3D, top-down, altitude profile).
"""
import json
import math
import re
import sys


def build_planned():
    """Same geometry as gazebo_bridge.build_mission()."""
    pts = []
    star = []
    for k in range(5):
        a = math.radians(72 * k)
        star.append((6.0 * math.cos(a), 6.0 * math.sin(a)))
    for k in [0, 2, 4, 1, 3, 0]:
        pts.append((star[k][0], star[k][1], -8.0))
    for k in list(range(8)) + [0]:
        a = math.radians(45 * k)
        pts.append((6.0 * math.cos(a), 6.0 * math.sin(a), -18.0))
    for n, e in [(4, -6), (-4, -6), (0, -6), (4, -2), (0, -6), (-4, -2)]:
        pts.append((float(n), float(e), -28.0))
    for n, e in [(-4, 1), (4, 1), (4, 5), (4, 1), (0, 1), (0, 4)]:
        pts.append((float(n), float(e), -28.0))
    pts.append((0.0, 0.0, -8.0))
    pts.append((0.0, 0.0, -8.0))
    return pts


TRUTH_RE = re.compile(
    r"\[test\] mission_test: t\+(\d+)s alt=([-\d.]+)m N=([-\d.]+) E=([-\d.]+)"
    r"(?: -> wp(\d+))?")


def load_truth(path):
    rows = []  # (t, alt, n, e, wp or None)
    for line in open(path):
        m = TRUTH_RE.search(line)
        if m:
            t, alt, n, e = float(m[1]), float(m[2]), float(m[3]), float(m[4])
            wp = int(m[5]) if m[5] is not None else None
            rows.append((t, alt, n, e, wp))
    return rows


def load_fc(path):
    ps, pos = [], []
    for line in open(path):
        r = json.loads(line)
        if r.get("object") == "PathStatus":
            d = r["data"]
            ps.append((r["t_us"] / 1e6, d["UID"], d["error"], d["Status"]))
        elif r.get("object") == "PositionState":
            d = r["data"]
            pos.append((r["t_us"] / 1e6, d["North"], d["East"], d["Down"]))
    return ps, pos


def overshoot_per_corner(truth, planned):
    """Max penetration past the plane through each corner, perpendicular to
    the incoming leg (the signature of carrying momentum through the turn).
    Uses the truth rows tagged with the FOLLOWING waypoint index: once wp
    advances to i+1, distance past corner i along leg i's direction."""
    out = {}
    for i in range(1, len(planned) - 1):
        a, b = planned[i - 1], planned[i]
        d = (b[0] - a[0], b[1] - a[1])
        L = math.hypot(*d)
        if L < 1e-6:
            continue
        u = (d[0] / L, d[1] / L)
        worst = 0.0
        for (t, alt, n, e, wp) in truth:
            if wp == i + 1:  # flying the NEXT leg - past corner i
                past = (n - b[0]) * u[0] + (e - b[1]) * u[1]
                worst = max(worst, past)
        out[i] = worst
    return out


def main():
    bridge_log, fc_jsonl, png = sys.argv[1], sys.argv[2], sys.argv[3]
    planned = build_planned()
    truth = load_truth(bridge_log)
    ps, fc_pos = load_fc(fc_jsonl)

    print("== corner overshoot (truth, m past corner along incoming leg) ==")
    ov = overshoot_per_corner(truth, planned)
    bad = 0
    for i, v in sorted(ov.items()):
        flag = "  <-- " + ("BAD" if v > 2.0 else "meh") if v > 1.0 else ""
        if v > 1.0:
            bad += 1
        print("  wp%-2d  %5.2f m%s" % (i, v, flag))
    vals = list(ov.values())
    print("  max %.2f m   mean %.2f m   corners >1m: %d/%d" %
          (max(vals), sum(vals) / len(vals), bad, len(vals)))

    print("== FC PathStatus.error by leg (UID): mean/max (m) ==")
    from collections import defaultdict
    agg = defaultdict(list)
    for (t, uid, err, st) in ps:
        agg[uid].append(err)
    worst_legs = sorted(agg.items(), key=lambda kv: -max(kv[1]))[:8]
    for uid, errs in worst_legs:
        print("  wp%-2d  mean %5.2f  max %5.2f  (n=%d)" %
              (uid, sum(errs) / len(errs), max(errs), len(errs)))

    # ---- PNG ----
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt

    fig = plt.figure(figsize=(16, 5.5))
    pn = [p[0] for p in planned]
    pe = [p[1] for p in planned]
    pd = [-p[2] for p in planned]
    tn = [r[2] for r in truth]
    te = [r[3] for r in truth]
    ta = [r[1] for r in truth]
    tt = [r[0] for r in truth]

    ax = fig.add_subplot(1, 3, 1, projection="3d")
    ax.plot(pe, pn, pd, "-", color="orange", alpha=0.5, lw=1.5, label="planned")
    ax.plot(te, tn, ta, "-", color="deepskyblue", lw=1.2, label="flown (truth)")
    if fc_pos:
        ax.plot([p[2] for p in fc_pos], [p[1] for p in fc_pos],
                [-p[3] for p in fc_pos], ":", color="magenta", lw=1.0,
                label="FC estimate (onboard log)")
    ax.set_xlabel("East"); ax.set_ylabel("North"); ax.set_zlabel("Alt m")
    ax.legend(loc="upper left", fontsize=8)
    ax.set_title("3D")

    ax2 = fig.add_subplot(1, 3, 2)
    ax2.plot(pe, pn, "o-", color="orange", alpha=0.5, ms=3, label="planned")
    sc = ax2.scatter(te, tn, c=ta, cmap="viridis", s=8, label="flown")
    fig.colorbar(sc, ax=ax2, label="alt m")
    ax2.set_xlabel("East"); ax2.set_ylabel("North"); ax2.axis("equal")
    ax2.grid(alpha=0.3); ax2.set_title("top-down (color = altitude)")

    ax3 = fig.add_subplot(1, 3, 3)
    ax3.plot(tt, ta, color="deepskyblue", label="alt (truth)")
    for ring in (8, 18, 28):
        ax3.axhline(ring, ls="--", color="gray", alpha=0.4)
    if ps:
        t0 = ps[0][0]
        ax3.plot([p[0] - t0 for p in ps], [p[2] for p in ps],
                 color="crimson", alpha=0.7, label="FC cross-track err (m)")
    ax3.set_xlabel("t s"); ax3.legend(fontsize=8); ax3.grid(alpha=0.3)
    ax3.set_title("altitude + FC path error")

    fig.tight_layout()
    fig.savefig(png, dpi=110)
    print("wrote", png)


if __name__ == "__main__":
    main()
