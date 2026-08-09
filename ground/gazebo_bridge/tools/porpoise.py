#!/usr/bin/env python3
"""Quantify porpoising from the board log's high-rate state records.

"Porpoising" is oscillation, so the useful measures are amplitude and
FREQUENCY, not mean error. Needs mission logging at 100ms (see
FC_LOG_OBJECTS_MISSION) - at 500ms anything above 1Hz aliases into noise
and the oscillation becomes invisible.

Reports, per channel (altitude, horizontal speed, roll, pitch, yaw):
  - detrended RMS (oscillation energy, ignoring slow drift)
  - dominant period via zero-crossing counting on the detrended signal
  - peak-to-peak

usage: porpoise.py <fclog.jsonl> [t_start t_end]
"""
import json
import math
import sys


def series_stats(name, ts, vs, unit="m"):
    if len(vs) < 8:
        print("  %-10s (too few samples: %d)" % (name, len(vs)))
        return
    # Detrend with a moving average so slow, legitimate changes (a climb,
    # a leg-to-leg move) do not masquerade as oscillation.
    win = max(3, int(len(vs) / 40))
    trend = []
    for i in range(len(vs)):
        lo, hi = max(0, i - win), min(len(vs), i + win + 1)
        trend.append(sum(vs[lo:hi]) / (hi - lo))
    osc = [v - t for v, t in zip(vs, trend)]

    rms = math.sqrt(sum(o * o for o in osc) / len(osc))
    p2p = max(osc) - min(osc)

    # Zero crossings of the detrended signal -> dominant period
    crossings = 0
    for i in range(1, len(osc)):
        if (osc[i - 1] <= 0.0 < osc[i]) or (osc[i - 1] >= 0.0 > osc[i]):
            crossings += 1
    span = ts[-1] - ts[0]
    period = (2.0 * span / crossings) if crossings else 0.0

    print("  %-10s RMS %6.3f %-5s  p2p %6.3f  period %5.2fs (%4.2f Hz)"
          % (name, rms, unit, p2p, period, 1.0 / period if period > 0.01 else 0.0))


def main():
    recs = [json.loads(l) for l in open(sys.argv[1])]
    t0 = recs[0]["t_us"] / 1e6
    lo = float(sys.argv[2]) if len(sys.argv) > 2 else 0.0
    hi = float(sys.argv[3]) if len(sys.argv) > 3 else 1e9

    def grab(obj, field, xform=lambda d, f: d[f]):
        ts, vs = [], []
        for r in recs:
            if r.get("object") != obj:
                continue
            t = r["t_us"] / 1e6 - t0
            if not (lo <= t <= hi):
                continue
            ts.append(t)
            vs.append(xform(r["data"], field))
        return ts, vs

    pt, pv = grab("PositionState", "Down", lambda d, f: -d[f])
    rate = len(pt) / max(pt[-1] - pt[0], 1e-6) if len(pt) > 1 else 0
    print("samples: %d over %.1fs (%.1f Hz)%s"
          % (len(pt), (pt[-1] - pt[0]) if len(pt) > 1 else 0, rate,
             "  <-- TOO SLOW to see porpoising, need >=5Hz" if rate < 4 else ""))

    print("oscillation (detrended):")
    series_stats("altitude", pt, pv, "m")

    vt, vv = grab("VelocityState", "North",
                  lambda d, f: math.hypot(d["North"], d["East"]))
    series_stats("horiz spd", vt, vv, "m/s")

    for ax in ("Roll", "Pitch", "Yaw"):
        at, av = grab("AttitudeState", ax)
        if ax == "Yaw" and av:
            # unwrap yaw so a +-180 wrap is not read as a huge oscillation
            un = [av[0]]
            for v in av[1:]:
                d = v - un[-1]
                while d > 180:
                    d -= 360
                while d < -180:
                    d += 360
                un.append(un[-1] + d)
            av = un
        series_stats(ax.lower(), at, av, "deg")


if __name__ == "__main__":
    main()
