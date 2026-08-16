#!/usr/bin/env python3
"""Grade a soak run for flight readiness from the shmlog ring dump.

Buckets [hub-health] checkpoints (10 s deltas) and innerloop watchdog lines
into the requested windows, applies EXPLICIT go/no-go thresholds, prints one
verdict per window and an overall ruling. Thresholds are written down here so
a pass means something:

    imu   >= 495 Hz   baro >= 49 Hz   hmc >= 49 Hz   rm3100 >= 24 Hz
    fix2/aux ~ 5 Hz   sensor errors == 0   gps decode rejects == 0
    watchdog ~2/s present to window end,  rateupdates > -64 (outer loop ran)
    i2c bus  < 50 %   can bus < 10 %

usage: flight_readiness.py <ring-dump.txt> <run-seconds>
"""
import re, sys

dump = open(sys.argv[1]).read().splitlines()
dur = int(sys.argv[2]) if len(sys.argv) > 2 else 360
WINDOWS = [(0, 30), (30, 60), (60, 90), (90, 180), (180, 360)]
WINDOWS = [(a, b) for a, b in WINDOWS if b <= dur]

def stamp(line):
    m = re.match(r"(\d+):(\d+):(\d+)\.(\d+)", line)
    return int(m[1])*3600 + int(m[2])*60 + int(m[3]) + int(m[4])/1000 if m else None

t0 = None
health, wd = [], []
for ln in dump:
    ts = stamp(ln)
    if ts is None: continue
    if t0 is None: t0 = ts
    rel = ts - t0
    if "[hub-health]" in ln:
        health.append((rel, dict(re.findall(r"(\w+)=(\d+)", ln))))
    m = re.search(r"gyroupdates=(\d+) rateupdates=(-?\d+)", ln)
    if m:
        wd.append((rel, int(m[1]), int(m[2])))

overall_ok = True
print("%-9s %6s %5s %5s %5s %5s %4s %4s %5s %5s %6s  %s" %
      ("window", "imu", "baro", "hmc", "mag", "gps", "err", "gbad",
       "i2c%", "can%", "wd/s", "verdict"))
for a, b in WINDOWS:
    hs = [h for t, h in health if a < t <= b]
    ws = [w for w in wd if a < w[0] <= b]
    if not hs:
        print("%-9s  NO HEALTH DATA -> NO-GO" % ("%d-%ds" % (a, b))); overall_ok = False; continue
    n = len(hs)
    f = lambda k: sum(int(h.get(k, 0)) for h in hs)
    imu, baro, hmc = f("imu")/(10*n), f("baro")/(10*n), f("hmc")/(10*n)
    mag, fix2 = f("mag")/(10*n), f("fix2")/(10*n)
    errs, gbad = f("ierr")+f("berr"), f("gbad")
    i2c = f("i2c_pm")/(10.0*n); can = f("can_pm")/(10.0*n)
    wr = len(ws)/(b-a)
    worst_rate = min((w[2] for w in ws), default=-64)
    checks = [imu >= 495, baro >= 49, hmc >= 49, mag >= 24,
              4.5 <= fix2 <= 5.5, errs == 0, gbad == 0,
              wr >= 1.5, worst_rate > -64, i2c < 50, can < 10]
    ok = all(checks)
    overall_ok &= ok
    print("%-9s %6.1f %5.1f %5.1f %5.1f %5.1f %4d %4d %5.1f %5.1f %6.2f  %s" %
          ("%d-%ds" % (a, b), imu, baro, hmc, mag, fix2, errs, gbad, i2c, can, wr,
           "GO" if ok else "NO-GO " + ",".join(
               nm for nm, c in zip(["imu","baro","hmc","mag","gps","err","gbad","wd","outer","i2c","can"], checks) if not c)))

print()
print("SENSOR/LOOP/BUS RULING: %s" % ("GO" if overall_ok else "NO-GO"))
print("GPS FIX GATE: NO-GO until outdoor fix (sats_visible=0 indoors - antenna suspect).")
print("=> flyable envelope if GO above: attitude / AxisLock / AltHold. No GPS modes.")
