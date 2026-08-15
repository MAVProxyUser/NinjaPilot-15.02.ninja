#!/usr/bin/env python3
"""Measure scheduling jitter at flight-loop rates. RUNS ON THE BOARD.

The question this answers: if FreeRTOS is a set of pthreads on Linux, how late
does a task actually wake up? OpenPilot's stabilizationInnerloopTask is
gyro-triggered at PIOS_SENSOR_RATE (500 Hz = 2 ms), and its own watchdog wants
exactly ONE gyro update per run - it warns at 2 and calls 3 critical. So a
wake-up 3 periods late is, by the firmware's own definition, a critical event.

What is measured is the LATENESS of a periodic wake-up: ask to sleep until
t0+n*period, then see what the clock really says. That is exactly the error a
FreeRTOS tick or a task wake-up inherits from the host scheduler.

Run it at normal priority and again under SCHED_FIFO to see what RT priority
buys:

    ./rt_jitter.py --hz 500 --seconds 20
    chrt -f 50 ./rt_jitter.py --hz 500 --seconds 20
    ./rt_jitter.py --hz 500 --seconds 20 --load 2     # with CPU contention
"""
import argparse
import os
import sys
import time


def percentile(xs, p):
    if not xs:
        return 0.0
    s = sorted(xs)
    k = min(len(s) - 1, max(0, int(round((p / 100.0) * (len(s) - 1)))))
    return s[k]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--hz", type=float, default=500.0)
    ap.add_argument("--seconds", type=float, default=20.0)
    ap.add_argument("--load", type=int, default=0,
                    help="spawn N busy processes to create contention")
    a = ap.parse_args()

    kids = []
    for _ in range(a.load):
        pid = os.fork()
        if pid == 0:
            end = time.time() + a.seconds + 2
            x = 0
            while time.time() < end:
                x = (x * 1103515245 + 12345) & 0xFFFFFFFF
            os._exit(0)
        kids.append(pid)

    period = 1.0 / a.hz
    n = int(a.seconds * a.hz)
    late = []
    t0 = time.perf_counter()
    for i in range(1, n + 1):
        target = t0 + i * period
        now = time.perf_counter()
        if target > now:
            time.sleep(target - now)
        late.append((time.perf_counter() - target) * 1000.0)   # ms late

    for pid in kids:
        try:
            os.waitpid(pid, 0)
        except OSError:
            pass

    try:
        pol = os.sched_getscheduler(0)
        polname = {0: "SCHED_OTHER", 1: "SCHED_FIFO", 2: "SCHED_RR"}.get(pol, str(pol))
        prio = os.sched_getparam(0).sched_priority
    except Exception:
        polname, prio = "?", "?"

    mean = sum(late) / len(late)
    print(f"=== {a.hz:.0f} Hz ({period*1000:.2f} ms period), {len(late)} wake-ups, "
          f"{polname} prio {prio}, load={a.load} ===")
    print(f"  mean late   {mean:8.3f} ms")
    print(f"  median      {percentile(late,50):8.3f} ms")
    print(f"  p99         {percentile(late,99):8.3f} ms")
    print(f"  p99.9       {percentile(late,99.9):8.3f} ms")
    print(f"  WORST       {max(late):8.3f} ms   = {max(late)/(period*1000):.1f} periods")
    over = [x for x in late if x > period * 1000]
    print(f"  wake-ups later than one full period: {len(over)} "
          f"({100.0*len(over)/len(late):.2f} %)")
    # The firmware's own thresholds: >1 gyro update missed = warn, >3 = critical
    crit = [x for x in late if x > 3 * period * 1000]
    print(f"  later than THREE periods (firmware calls this critical): {len(crit)} "
          f"({100.0*len(crit)/len(late):.3f} %)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
