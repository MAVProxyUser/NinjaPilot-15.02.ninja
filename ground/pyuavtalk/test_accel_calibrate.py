#!/usr/bin/env python3
"""Check the six-point solver against synthetic data with a known answer.

The sign of the bias is the whole reason this test exists. The solver's own
model is corrected = S*raw + b, while the firmware computes raw*scale - bias,
so the two disagree by a negation. That mistake is invisible on a bench -- the
magnitude still looks plausible -- and it would double the offset in flight
instead of removing it.

    python3 test_accel_calibrate.py
"""
import sys

import numpy as np

from accel_calibrate import six_point_in_const_field_cal

GRAV = 9.80665
# Poses matching the wizard: level, nose down, right side down, inverted, ...
DIRS = [(0, 0, -1), (1, 0, 0), (0, 1, 0), (0, 0, 1), (-1, 0, 0), (0, -1, 0)]


def run_case(true_S, true_b, tol=1e-9):
    x, y, z = [], [], []
    for d in DIRS:
        # invert the firmware model true = raw*S - b to get what the part reports
        raw = (GRAV * np.array(d, dtype=float) + true_b) / true_S
        x.append(raw[0])
        y.append(raw[1])
        z.append(raw[2])

    S, b = six_point_in_const_field_cal(GRAV, x, y, z)

    worst = 0.0
    for i in range(len(DIRS)):
        corrected = np.array([S[j] * [x, y, z][j][i] - b[j] for j in range(3)])
        worst = max(worst, abs(np.linalg.norm(corrected) - GRAV))

    ok = (np.allclose(S, true_S, atol=tol)
          and np.allclose(b, true_b, atol=tol)
          and worst < tol)
    print("  scale %s vs %s" % (np.round(S, 6), true_S))
    print("  bias  %s vs %s" % (np.round(b, 6), true_b))
    print("  worst |a| error %.2e  ->  %s" % (worst, "ok" if ok else "FAILED"))
    return ok


def main():
    cases = [
        ("pure Z offset, the LiteWing case",
         np.array([1.0, 1.0, 1.0]), np.array([0.0, 0.0, -0.99])),
        ("offset and gain on every axis",
         np.array([1.017, 0.994, 1.031]), np.array([0.21, -0.35, -0.99])),
        ("already perfect",
         np.array([1.0, 1.0, 1.0]), np.array([0.0, 0.0, 0.0])),
    ]
    ok = True
    for name, S, b in cases:
        print(name)
        ok &= run_case(S, b)
        print()
    print("PASS" if ok else "FAIL")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
