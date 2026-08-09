#!/usr/bin/env python3
"""Prove which axes the relay actually drove, from ActuatorDesired logged at
50ms. The relay outputs a +/-Amplitude (0.25) square wave on exactly the axis
being tuned, so counting sign flips per axis per time window is direct,
unambiguous evidence - unlike AttitudeState at 500ms, which aliases a 9Hz
limit cycle into meaningless noise.

argv[1] = fclog jsonl (or flash-decoded jsonl)
"""
import json
import sys
from collections import defaultdict


def main():
    recs = [json.loads(l) for l in open(sys.argv[1])]
    act = [(r["t_us"] / 1e6, r["data"]) for r in recs if r.get("object") == "ActuatorDesired"]
    fs = [(r["t_us"] / 1e6, r["data"]["FlightMode"]) for r in recs if r.get("object") == "FlightStatus"]
    if not act:
        print("no ActuatorDesired records - was high-rate logging enabled?")
        return

    at_start = next((t for t, m in fs if m == "Autotune"), None)
    if at_start is None:
        print("FC was NEVER in Autotune mode. Modes seen:", sorted({m for _, m in fs}))
        return
    print("Autotune engaged at FC t=%.1fs" % at_start)
    print("ActuatorDesired samples: %d over %.1fs (%.1f Hz effective)"
          % (len(act), act[-1][0] - act[0][0],
             len(act) / max(act[-1][0] - act[0][0], 1e-6)))

    def window(lo, hi, label):
        rows = [(t - at_start, d) for t, d in act if lo <= t - at_start < hi]
        if not rows:
            print("  %-12s NO DATA" % label)
            return
        out = ["  %-12s n=%3d" % (label, len(rows))]
        for ax in ("Roll", "Pitch", "Yaw"):
            vals = [d[ax] for _, d in rows]
            amp = max(abs(v) for v in vals)
            # count sign flips = relay toggles
            flips = 0
            prev = None
            for v in vals:
                sgn = 1 if v > 0.02 else (-1 if v < -0.02 else 0)
                if sgn and prev and sgn != prev:
                    flips += 1
                if sgn:
                    prev = sgn
            span = hi - lo
            out.append("%s: |max| %.3f flips %2d (~%.0fms period)"
                       % (ax, amp, flips, 2000.0 * span / flips if flips else 0))
        print("  " + " | ".join(out))

    print("relay square-wave activity per window (>=0.2 |max| + many flips = "
          "THIS axis is being relay-driven):")
    window(0, 2, "prepare")
    window(2, 22, "ROLL win")
    window(22, 42, "PITCH win")
    window(42, 62, "YAW win")
    window(62, 72, "landing")

    print()
    print("raw ActuatorDesired samples at each window boundary (eyeball the square wave):")
    for lo, label in ((3.0, "roll"), (23.0, "pitch"), (43.0, "yaw")):
        rows = [(t - at_start, d) for t, d in act if lo <= t - at_start < lo + 1.0]
        print("  %s window, 1 second of samples:" % label)
        for tt, d in rows[:12]:
            print("    t+%6.2f  roll %+.3f  pitch %+.3f  yaw %+.3f"
                  % (tt, d["Roll"], d["Pitch"], d["Yaw"]))


if __name__ == "__main__":
    main()
