#!/usr/bin/env python3
"""Three-log comparison for an INTERCEPT run - the analogue of score.py.

score.py / wp_arrival.py / star_plot.py all grade against the star mission
geometry in star_geom.py, so running them on an intercept produces confident
nonsense (CLAUDE.md records a mission change read as 1.76m of cross-track
error that was purely a stale planned path). An intercept has no fixed
planned shape at all - the "plan" is a commanded aim point that moves every
tick - so it needs its own comparison.

The three sources and the question each one answers:

  BOARD log   what the FC believed and what it commanded
  BRIDGE      Gazebo ground truth, and the aim point the harness sent
  GZ server   whether the simulator itself was unhappy (handled by
              analyze_run.sh directly)

The comparisons, in the order that isolates a miss:

  1. VERTICAL COMMAND vs ACHIEVED (board log alone, one clock). Separates
     "guidance never asked for the climb" from "asked and could not get it".
     These are opposite fixes - the first is a guidance-law bug, the second
     is thrust/tilt/limit starvation - and no scalar miss distance can tell
     them apart.
  2. ESTIMATOR vs TRUTH. If the FC's own position disagrees with Gazebo,
     every guidance conclusion above it is void.
  3. COMMANDED AIM vs FLOWN. What the harness asked for versus where the
     vehicle went - the guidance execution error proper.

CLOCK PAIRING: the board log's t_us is the FC's own microsecond clock, with
no fixed relation to the bridge's t0. Rather than assume an offset, the
altitude traces are cross-correlated to find it, and the residual fit is
REPORTED - if the alignment is poor the pairing is untrustworthy and the
comparison says so instead of quietly producing a number. This project has
already invented a 0.4m "estimator bias" by comparing two differently-sampled
sets; alignment quality is not optional.

usage: intercept_three_log.py <flash.jsonl> <track.json>
"""
import json
import math
import sys


def load_board(path):
    """{object: [(t_s, data), ...]} from the decoded flash log."""
    out = {}
    with open(path) as fh:
        for line in fh:
            try:
                j = json.loads(line)
            except Exception:
                continue
            if j.get("kind") != "uavobject":
                continue
            name = j.get("object")
            if not name:
                continue
            out.setdefault(name, []).append((j["t_us"] / 1e6, j.get("data") or {}))
    for v in out.values():
        v.sort(key=lambda r: r[0])
    return out


def vertical_command_vs_achieved(board):
    """The decisive one: did the path layer ASK for the climb it needed?"""
    vd = board.get("VelocityDesired") or []
    vs = board.get("VelocityState") or []
    if not vd or not vs:
        print("  (need VelocityDesired + VelocityState in the board log)")
        return
    # WINDOW ON THE ENGAGEMENT. After break-off the vehicle is deliberately
    # commanded to descend and stabilise, so those samples say nothing about
    # the merge - scoring them made a run whose climb tracked fine during the
    # approach report "did NOT track the vertical command" on the strength of
    # a post-breakoff descent 8 seconds later. Only samples where a CLIMB was
    # actually being asked for are part of the question.
    t0 = vd[0][0]
    pairs = []
    for t, d in vd:
        best = min(vs, key=lambda r: abs(r[0] - t))
        if abs(best[0] - t) > 0.15:
            continue
        cmd = -float(d.get("Down", 0.0))          # +ve = climbing
        act = -float(best[1].get("Down", 0.0))
        pairs.append((t - t0, cmd, act, cmd - act))
    climb = [p for p in pairs if p[1] > 0.25]
    if not climb:
        print("  (no climb was ever commanded)")
        return
    # BREAK-OFF TRIM. At break-off the harness commands a descent, but the
    # last Intercept PathDesired can still be sitting in VelocityDesired for
    # a few samples - so the log shows "climb commanded, vehicle descending
    # hard" purely as an artefact of the transition. The vehicle descending
    # at >0.5 m/s while a climb is commanded is that transition, never the
    # merge; everything from there on is dropped.
    for i, p in enumerate(climb):
        if p[2] < -0.5 and p[1] > 0.0:
            climb = climb[:i]
            break
    if not climb:
        print("  (engagement ended before any climb was tracked)")
        return
    t_end = climb[-1][0]
    print("  climb commanded from t+%.1fs to t+%.1fs (%d samples)"
          % (climb[0][0], t_end, len(climb)))
    print("  %-8s %-12s %-12s %s" % ("t(s)", "cmd_climb", "actual", "shortfall"))
    show = climb[-14:] if len(climb) > 14 else climb
    for tt, cmd, act, short in show:
        print("  %-8.2f %-12.2f %-12.2f %+.2f" % (tt, cmd, act, short))
    worst = max(climb, key=lambda p: abs(p[3]))
    mean_short = sum(abs(p[3]) for p in climb) / len(climb)
    print("  shortfall over the climb: mean %.2f m/s, worst %+.2f at t+%.1fs"
          % (mean_short, worst[3], worst[0]))
    print("  commanded climb: peak %.2f m/s, last %.2f m/s"
          % (max(p[1] for p in climb), climb[-1][1]))
    # The verdict. These are OPPOSITE fixes, which is the whole point of
    # separating them.
    if mean_short < 0.35:
        print("  -> vehicle TRACKED the vertical command."
              " If it finished low, GUIDANCE UNDER-ASKED.")
    else:
        print("  -> vehicle did NOT track the vertical command."
              " Thrust/tilt/limit starvation, not guidance.")


def align(board, track):
    """Find the board->bridge time offset by matching altitude. Returns
    (offset, rms_fit) or (None, None)."""
    ps = board.get("PositionState") or []
    if not ps or not track:
        return (None, None)
    b = [(t, -float(d.get("Down", 0.0))) for t, d in ps]
    g = [(r[0], -r[1][2]) for r in track]
    if len(b) < 5 or len(g) < 5:
        return (None, None)
    # Coarse search over plausible offsets; the flight is short so this is
    # cheap and beats assuming a fixed relationship.
    best = (None, 1e9)
    lo = b[0][0] - g[-1][0] - 5.0
    hi = b[0][0] - g[0][0] + 5.0
    steps = 400
    for k in range(steps + 1):
        off = lo + (hi - lo) * k / steps
        res, n = 0.0, 0
        for tg, ag in g:
            tb = tg + off
            if tb < b[0][0] or tb > b[-1][0]:
                continue
            nb = min(b, key=lambda r: abs(r[0] - tb))
            if abs(nb[0] - tb) > 0.15:
                continue
            res += (nb[1] - ag) ** 2
            n += 1
        if n >= 10:
            rms = math.sqrt(res / n)
            if rms < best[1]:
                best = (off, rms)
    return best


def estimator_vs_truth(board, track, off):
    ps = board.get("PositionState") or []
    errs = []
    for tg, dn, _tn, _v, _s, _g, _aim in (r + [None] * 0 for r in track):
        tb = tg + off
        nb = min(ps, key=lambda r: abs(r[0] - tb))
        if abs(nb[0] - tb) > 0.15:
            continue
        d = nb[1]
        errs.append((math.hypot(float(d.get("North", 0.0)) - dn[0],
                                float(d.get("East", 0.0)) - dn[1]),
                     abs(float(d.get("Down", 0.0)) - dn[2])))
    if not errs:
        print("  (no paired samples)")
        return
    mh = sum(e[0] for e in errs) / len(errs)
    mv = sum(e[1] for e in errs) / len(errs)
    print("  paired %d samples | horiz mean %.3f m max %.3f | vert mean %.3f m max %.3f"
          % (len(errs), mh, max(e[0] for e in errs), mv, max(e[1] for e in errs)))
    print("  -> %s" % ("estimator OK; error is CONTROLLER/GUIDANCE"
                       if mh < 0.25 and mv < 0.25 else "ESTIMATOR SUSPECT"))


def aim_vs_flown(track):
    """What we asked for versus where it went."""
    if not track or len(track[0]) < 7:
        print("  (this run predates the commanded-aim field in the track)")
        return
    rows = []
    for r in track:
        t, dn, tn, _v, sep, _g, aim = r[:7]
        rows.append((t, math.dist(dn, aim), sep))
    late = [r for r in rows if r[0] > rows[-1][0] - 3.0]
    print("  distance from the vehicle to its COMMANDED aim point:")
    print("    start %.2f m -> end %.2f m; last 3s mean %.2f m"
          % (rows[0][1], rows[-1][1], sum(r[1] for r in late) / max(1, len(late))))
    imin = min(range(len(rows)), key=lambda i: rows[i][2])
    print("    at closest approach (t+%.1fs): %.2f m from the aim point,"
          " %.2f m from the ball"
          % (rows[imin][0], rows[imin][1], rows[imin][2]))
    print("  -> %s" % ("guidance was ASKING for the right place; the vehicle"
                       " got there" if rows[imin][1] < 0.6 else
                       "the vehicle did NOT reach its own commanded aim point"))


def main():
    board = load_board(sys.argv[1])
    track = json.load(open(sys.argv[2])).get("track") or []

    print("--- vertical: commanded climb vs achieved (board log, one clock) ---")
    vertical_command_vs_achieved(board)

    print("--- estimator: FC belief vs Gazebo truth ---")
    off, rms = align(board, track)
    if off is None:
        print("  (could not align the two clocks)")
    elif rms > 1.0:
        print("  alignment poor (altitude rms %.2f m) - NOT pairing these logs" % rms)
    else:
        print("  clocks aligned to %.2fs (altitude rms %.2f m)" % (off, rms))
        estimator_vs_truth(board, track, off)

    print("--- guidance: commanded aim vs flown ---")
    aim_vs_flown(track)


if __name__ == "__main__":
    main()
