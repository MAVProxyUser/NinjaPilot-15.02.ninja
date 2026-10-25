#!/usr/bin/env python3
"""
bench_report - offline deep pass over a bench_test.py jsonl log.

Re-runs the same grades bench_test prints at the end of a run, then goes
further: it de-duplicates the ~6 Hz gyro/accel polls (bench_test writes rows
at 25 Hz, so most rows repeat the last poll), grades the estimate against
gravity per THROTTLE BAND (the 2026-09-01 flip signature was the estimate
walking away from the accelerometer as vibration rose), checks for a gyro
bias that grows with throttle (vibration rectification), and reports PWM
saturation, which with props off is expected: the attitude integrator winds
up because the airframe never answers the correction.

    python3 bench_report.py ~/NinjaPilot-logs/bench_YYYY-MM-DD_HH-MM-SS.jsonl
"""
import json
import math
import sys
from collections import defaultdict


def corr(xs, ys):
    n = len(xs)
    if n < 10:
        return None
    mx, my = sum(xs) / n, sum(ys) / n
    sxx = sum((x - mx) ** 2 for x in xs)
    syy = sum((y - my) ** 2 for y in ys)
    if sxx <= 0 or syy <= 0:
        return None
    return sum((x - mx) * (y - my) for x, y in zip(xs, ys)) / math.sqrt(sxx * syy)


def mag(v):
    return math.sqrt(sum(a * a for a in v))


def acc_angles(acc):
    """(roll, pitch) in degrees from the gravity vector, OP body frame:
    level reads (0, 0, -9.81); nose down -> acc.x negative; roll right ->
    acc.y negative."""
    a = mag(acc)
    if a < 1e-3:
        return None
    pitch = math.degrees(math.asin(max(-1.0, min(1.0, acc[0] / a))))
    roll = math.degrees(math.atan2(-acc[1], -acc[2]))
    return roll, pitch


def grade(rows):
    ok = lambda c: "ok".center(4)
    print("===== bench report (offline) ===== %d rows, t %.1f..%.1f s, thr max %.2f"
          % (len(rows), rows[0]["t"], rows[-1]["t"], max(r["thr"] for r in rows)))

    # ---- unique sensor samples (bench_test polls gyro/acc round-robin) ----
    uniq = []
    for r in rows:
        if not uniq or r["gyro"] != uniq[-1]["gyro"] or r["acc"] != uniq[-1]["acc"]:
            uniq.append(r)
    print("  %d unique gyro/accel samples (%.1f Hz effective)"
          % (len(uniq), len(uniq) / max(1e-3, rows[-1]["t"] - rows[0]["t"])))

    # ---- 1. per-stimulus estimate response, lag-aware ----------------------
    # Logs written before 2026-09-02 label rows from the scheduler, not from
    # when the prompt was spoken, so the pilot's hands trail the labels by
    # the say-queue backlog (~2 s on the 23:54 log). Find the label lag that
    # best explains the data, then grade each window by its EXTREME in the
    # commanded direction (a hand still moving at window start must not
    # drag a mean grade down). Newer logs are already reaction-aligned and
    # come out with lag ~0.
    print("\n[1] estimate follows the commanded tilt (windows shifted by the best label lag):")
    inst, cur = [], None
    for r in rows:
        if cur is None or r["phase"] != cur[0]:
            cur = (r["phase"], r["t"], r["t"]); inst.append(cur)
        cur = (cur[0], cur[1], r["t"]); inst[-1] = cur
    checks = (("nose_down", 1, "<", -8, "estimate sees nose down"),
              ("nose_up", 1, ">", 8, "estimate sees nose up (above level)"),
              ("roll_left", 0, "<", -8, "estimate sees roll left"),
              ("roll_right", 0, ">", 8, "estimate sees roll right"))
    def excursions(ph, idx, op, lag):
        ext = []
        for name, t0, t1 in inst:
            if name != ph:
                continue
            w = [s["att"][idx] for s in rows if t0 + lag <= s["t"] <= t1 + lag and 0.10 < s["thr"] < 0.90]
            if len(w) > 5:
                ext.append(min(w) if op == "<" else max(w))
        return ext
    def score(lag):
        tot = 0.0
        for ph, idx, op, th, _ in checks:
            e = excursions(ph, idx, op, lag)
            if e:
                m = sum(e) / len(e); tot += (-m if op == "<" else m)
        return tot
    lags = [x * 0.5 for x in range(0, 11)]
    best = max(lags, key=score)
    print("  best label lag %.1f s (score %.0f; lag 0 scores %.0f)" % (best, score(best), score(0)))
    for ph, idx, op, th, desc in checks:
        e = excursions(ph, idx, op, best)
        if not e:
            print("  [ ?? ] %-34s no windows" % desc); continue
        m = sum(e) / len(e)
        good = m < th if op == "<" else m > th
        print("  [ %s ] %-34s mean extreme %+6.1f deg over %d windows" % ("ok".center(4) if good else "FAIL", desc, m, len(e)))

    # ---- 2. gyro vs d(att)/dt on unique samples ---------------------------
    print("\n[2] estimate integrates the gyro (unique samples, |tilt| < 60 deg):")
    d = []
    for a, b in zip(uniq, uniq[1:]):
        dt = b["t"] - a["t"]
        if 0.05 < dt < 0.5 and abs(a["att"][0]) < 60 and abs(a["att"][1]) < 60:
            d.append(((b["att"][1] - a["att"][1]) / dt, (a["gyro"][1] + b["gyro"][1]) / 2,
                      (b["att"][0] - a["att"][0]) / dt, (a["gyro"][0] + b["gyro"][0]) / 2))
    for name, xi, yi in (("gyro.y vs d(pitch)/dt", 1, 0), ("gyro.x vs d(roll)/dt", 3, 2)):
        xs = [x[xi] for x in d]; ys = [x[yi] for x in d]
        c = corr(xs, ys)
        if c is None:
            print("  [ ?? ] %-24s insufficient motion" % name); continue
        # gain: least-squares slope d(att)/dt per deg/s of gyro (1.0 ideal)
        mx, my = sum(xs) / len(xs), sum(ys) / len(ys)
        slope = sum((x - mx) * (y - my) for x, y in zip(xs, ys)) / max(1e-9, sum((x - mx) ** 2 for x in xs))
        lvl = "ok" if c > 0.5 else ("FAIL" if c < -0.2 else "WARN")
        print("  [ %s ] %-24s r=%+.2f  gain %.2f (1.0 ideal)  n=%d" % (lvl.center(4), name, c, slope, len(xs)))

    # ---- 3. accel vs estimate, slow motion, per throttle band ------------
    print("\n[3] estimate agrees with gravity (slow motion: |gyro| < 30 deg/s, 8.5 < |a| < 11):")
    pa = []
    for s in uniq:
        if max(abs(g) for g in s["gyro"]) < 30 and 8.5 < mag(s["acc"]) < 11.0:
            ang = acc_angles(s["acc"])
            if ang:
                pa.append((s["thr"], ang[0], s["att"][0], ang[1], s["att"][1]))
    c_r = corr([p[1] for p in pa], [p[2] for p in pa]); c_p = corr([p[3] for p in pa], [p[4] for p in pa])
    for name, c in (("accel-roll vs est-roll", c_r), ("accel-pitch vs est-pitch", c_p)):
        if c is None:
            print("  [ ?? ] %-24s insufficient clean samples" % name); continue
        lvl = "ok" if c > 0.7 else ("FAIL" if c < 0.3 else "WARN")
        print("  [ %s ] %-24s r=%+.2f %s" % (lvl.center(4), name, c,
              "(no vibration divergence)" if c > 0.7 else "(THE FLIP SIGNATURE)"))
    bands = defaultdict(list)
    for thr, ar, er, ap, ep in pa:
        bands[int(thr * 100 // 20) * 20].append((abs(ar - er), abs(ap - ep)))
    print("  mean |accel-angle - estimate| per throttle band (deg; a growing trend = vibration walking the estimate):")
    for k in sorted(bands):
        v = bands[k]
        mr = sum(x[0] for x in v) / len(v); mp = sum(x[1] for x in v) / len(v)
        flag = "" if max(mr, mp) < 8 else "  <-- diverging"
        print("    %2d-%2d%% thr: roll %5.1f  pitch %5.1f  (n=%d)%s" % (k, k + 19, mr, mp, len(v), flag))

    # ---- 4. motor response direction --------------------------------------
    print("\n[4] mixer raises the dropped side (0.15 < thr < 0.85, no motor at floor):")
    mr_ = [(s["att"][1], (s["pwm"][0] + s["pwm"][1]) - (s["pwm"][2] + s["pwm"][3]),
            s["att"][0], (s["pwm"][0] + s["pwm"][3]) - (s["pwm"][1] + s["pwm"][2]))
           for s in rows if 0.15 < s["thr"] < 0.85 and all(p > 900 for p in s["pwm"]) and s["phase"] != "still"]
    for name, xi, yi, note in (("pitch vs front-rear PWM", 0, 1, "front pair (M1,M2) minus rear (M3,M4)"),
                               ("roll vs left-right PWM", 2, 3, "left pair (M1,M4) minus right (M2,M3)")):
        c = corr([x[xi] for x in mr_], [x[yi] for x in mr_])
        if c is None:
            print("  [ ?? ] %-24s insufficient data" % name); continue
        lvl = "ok" if c < -0.3 else ("FAIL" if c > 0.3 else "WARN")
        print("  [ %s ] %-24s r=%+.2f %s  [%s]" % (lvl.center(4), name, c,
              "(raises the dropped side)" if c < -0.3 else "(WRONG DIRECTION)" if c > 0.3 else "(weak)", note))
    sat = sum(1 for s in rows if s["thr"] > 0.15 and any(p >= 1899 for p in s["pwm"]))
    n_mv = sum(1 for s in rows if s["thr"] > 0.15)
    print("  PWM saturation (>=1899) in %d/%d rows above 15%% thr (%.0f%%) - expected props-off: the"
          % (sat, n_mv, 100.0 * sat / max(1, n_mv)))
    print("  attitude integrator winds up because the airframe never answers the correction.")

    # ---- 5. vibration + rectified bias in HOLD-STILL windows -------------
    print("\n[5] HOLD-STILL windows (unique samples): noise and gyro bias per throttle band:")
    still = [s for s in uniq if s["phase"] == "still"]
    b = defaultdict(list)
    for a, c in zip(still, still[1:]):
        if c["t"] - a["t"] < 0.5:
            b[int(a["thr"] * 100 // 20) * 20].append(
                (max(abs(c["gyro"][i] - a["gyro"][i]) for i in range(3)),
                 abs(mag(c["acc"]) - mag(a["acc"])), a["gyro"],
                 (c["att"][0], c["att"][1]), a["t"], c["t"], (a["att"][0], a["att"][1])))
    for k in sorted(b):
        v = b[k]
        mg = sum(x[0] for x in v) / len(v); ma = sum(x[1] for x in v) / len(v)
        bias = [sum(x[2][i] for x in v) / len(v) for i in range(3)]
        # a gyro mean is BIAS only if the estimate did not actually rotate
        # that fast - otherwise the pilot was still moving during "still"
        droll = sum((x[3][0] - x[6][0]) / max(1e-3, x[5] - x[4]) for x in v) / len(v)
        dpitch = sum((x[3][1] - x[6][1]) / max(1e-3, x[5] - x[4]) for x in v) / len(v)
        flag = "" if mg < 15 else "  <-- noisy band"
        if abs(bias[0] - droll) > 5 or abs(bias[1] - dpitch) > 5:
            flag += "  <-- gyro mean not matched by estimate motion: RECTIFIED BIAS"
        elif max(abs(bias[0]), abs(bias[1])) > 5:
            flag += "  (pilot still moving, estimate tracked it)"
        print("    %2d-%2d%% thr: gyro delta ~%5.1f deg/s  |a| delta ~%4.2f m/s2  gyro mean (%+5.1f,%+5.1f,%+5.1f) vs est rate (%+5.1f,%+5.1f)  n=%d%s"
              % (k, k + 19, mg, ma, bias[0], bias[1], bias[2], droll, dpitch, len(v), flag))


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    rows = [json.loads(l) for l in open(sys.argv[1]) if l.strip()]
    grade(rows)
