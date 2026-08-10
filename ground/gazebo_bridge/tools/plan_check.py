#!/usr/bin/env python3
"""Did the vehicle fly the mission the scorers are grading it against?

Every other tool here compares the flown path to a shape hard-coded in
star_geom.py. That is a silent single point of failure: change the mission
without changing that file and the scorers keep measuring the OLD shape,
reporting confident nonsense. It has already happened once - a mission change
read as 1.76m of cross-track error that was purely a stale planned path.

PathDesired is now logged on change, so the legs the follower was ACTUALLY
given are in the board log. This reconstructs them and checks them against
star_geom.ORDER, so a drifted planned path is caught by the analysis instead
of being reported as flight error.

It also prints the per-leg parameters, which answer questions that have cost
real time before:
  - ModeParameters[1] - is a leg cruise speed actually reaching the follower,
    or is the leg silently pinned to its endpoint velocities?
  - ModeParameters[2]/[3] - is the next-leg bearing being published at all?
    (A block gated on [3] never executed for the entire project because
    nothing set it.)
  - EndingVelocity - do corners arrive at a true stop?

usage: plan_check.py <fclog.jsonl>
"""
import json
import math
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from star_geom import ORDER, fillet_plan


def main():
    recs = [json.loads(l) for l in open(sys.argv[1])]
    pd = [r for r in recs if r.get("object") == "PathDesired"]
    if not pd:
        print("  (no PathDesired in log - add it to FC_LOG_OBJECTS_MISSION; "
              "without it the scorers are trusting star_geom.py blindly)")
        return

    # One entry per distinct leg, in flown order. Skip GoToEndpoint: that is
    # the PositionHold staging leg the harness flies BEFORE engaging the path
    # planner, not part of the mission, and counting it shifts every leg by
    # one and makes the comparison below cry wolf on a perfectly good run.
    legs = []
    for r in pd:
        d = r["data"]
        if d.get("Mode") not in ("FollowVector", "Land", "CircleRight", "CircleLeft"):
            continue
        # decode_fcwd emits vector fields as LISTS (N, E, D), not dicts.
        end = tuple(d["End"])
        start = tuple(d["Start"])
        if legs and legs[-1][0] == start and legs[-1][1] == end:
            continue
        legs.append((start, end, d))

    print("  leg  end (N,E,Down)          startV  endV   cruise  bearing  mode")
    for i, (start, end, d) in enumerate(legs):
        mp = d.get("ModeParameters", [0, 0, 0, 0])
        brg = ("%6.1f" % mp[2]) if len(mp) > 3 and mp[3] > 0.5 else "     -"
        print("  %3d  %7.2f %7.2f %7.2f  %5.2f  %5.2f  %5.2f  %s  %s"
              % (i, end[0], end[1], end[2],
                 d.get("StartingVelocity", 0), d.get("EndingVelocity", 0),
                 mp[1] if len(mp) > 1 else 0, brg, d.get("Mode", "?")))

    # Does the flown plan match what the scorers assume? Two known shapes:
    # the default stop-corner star (ORDER) and the experimental fillet plan
    # (NINJAPILOT_STAR_ARCS=1). Match whichever fits; warn only if NEITHER.
    flown = [(round(e[0], 2), round(e[1], 2)) for _, e, _ in legs]
    cand_plain = [(round(q[0], 2), round(q[1], 2)) for q in ORDER]
    cand_arcs = [(round(w["pos"][0], 2), round(w["pos"][1], 2))
                 for w in fillet_plan()]

    def fits(cand):
        return (len(flown) == len(cand)
                and all(math.hypot(f[0] - c[0], f[1] - c[1]) <= 0.05
                        for f, c in zip(flown, cand)))
    if fits(cand_plain):
        assumed = cand_plain
    elif fits(cand_arcs):
        assumed = cand_arcs
    else:
        assumed = cand_plain  # report the mismatch against the default
    mismatch = [(i, f, a) for i, (f, a) in enumerate(zip(flown, assumed)) if
                math.hypot(f[0] - a[0], f[1] - a[1]) > 0.05]
    if len(flown) != len(assumed) or mismatch:
        print("  !!! PLANNED PATH MISMATCH - every score in this run is being")
        print("      measured against the WRONG shape. Fix tools/star_geom.py")
        print("      to match build_mission() before believing any number.")
        print("      logged legs %d, expected waypoints %d" % (len(flown), len(assumed)))
        for i, f, a in mismatch[:5]:
            print("      leg %d: flown to (%.2f, %.2f), star_geom says (%.2f, %.2f)"
                  % (i, f[0], f[1], a[0], a[1]))
    else:
        print("  planned path matches tools/star_geom.py (%d legs) - scores are "
              "against the right shape" % len(flown))

    # Cheap sanity checks on things that have silently been zero before.
    cruise = [d.get("ModeParameters", [0, 0])[1] for _, _, d in legs
              if len(d.get("ModeParameters", [])) > 1]
    if cruise and max(cruise) <= 0.0:
        print("  !!! no leg cruise speed reaching the follower (ModeParameters[1] "
              "all zero) - legs are pinned to their endpoint velocities")
    valid = [d.get("ModeParameters", [0, 0, 0, 0])[3] for _, _, d in legs
             if len(d.get("ModeParameters", [])) > 3]
    if valid and max(valid) <= 0.5:
        print("  !!! next-leg bearing never published (ModeParameters[3] all "
              "zero) - anything gated on it is dead code")


if __name__ == "__main__":
    main()
