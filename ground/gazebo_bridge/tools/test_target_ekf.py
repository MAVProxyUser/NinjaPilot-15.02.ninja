#!/usr/bin/env python3
"""Offline checks on TargetEKF - no Gazebo, no firmware, no 40s flight.

Every claim this filter makes is checkable against a synthetic truth track,
and checking it here costs 0.2s instead of a sim run. The three things worth
proving before the filter is allowed anywhere near a flight:

  1. it converges on position AND velocity from noisy fixes
  2. a bearing-only update cannot corrupt RANGE (the structural claim in the
     module docstring - if this fails, the Jacobian is wrong)
  3. predict_ahead(tau) actually lands on the truth tau seconds later, which
     is the entire lag-compensation argument

usage: ./venv/bin/python3 tools/test_target_ekf.py
"""
import math
import os
import sys

import numpy as np

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from target_ekf import TargetEKF


TRUE_P0 = np.array([25.0, -18.0, -12.0])
TRUE_V = np.array([-1.05, 0.58, 0.0])       # ~1.2 m/s, like the balloon
OWN = np.array([0.0, 0.0, -8.0])
OWN_V = np.array([1.4, -0.8, -0.5])


def truth(t):
    return TRUE_P0 + TRUE_V * t


def run(seed=1, use_bearing=True, use_pos=True, lag=0.48, n=400, dt=0.05):
    rng = np.random.default_rng(seed)
    ekf = TargetEKF(sigma_pos=0.35, sigma_ang_deg=1.2)
    ekf.init(0.0, truth(0.0) + rng.normal(0, 0.35, 3))

    lag_err, pos_err, vel_err = [], [], []
    for k in range(1, n):
        t = k * dt
        ekf.predict(t)
        own = OWN + OWN_V * t

        # position fixes at 10Hz, bearings at 20Hz - the real rates
        if use_pos and k % 4 == 0:
            ekf.update_position(truth(t) + rng.normal(0, 0.35, 3))
        if use_bearing and k % 2 == 0:
            R = truth(t) - own
            u = R / np.linalg.norm(R)
            # perturb the direction by ~1.2 deg, then renormalise
            u = u + rng.normal(0, math.radians(1.2), 3)
            ekf.update_bearing(own, u / np.linalg.norm(u))

        if t > 4.0:                      # after convergence
            p, v = ekf.state()
            pos_err.append(np.linalg.norm(np.array(p) - truth(t)))
            vel_err.append(np.linalg.norm(np.array(v) - TRUE_V))
            pl, _ = ekf.predict_ahead(lag)
            lag_err.append(np.linalg.norm(np.array(pl) - truth(t + lag)))
    return (float(np.mean(pos_err)), float(np.mean(vel_err)),
            float(np.mean(lag_err)), ekf)


def main():
    ok = True

    print("1. convergence from noisy position + bearing")
    p, v, l, ekf = run()
    print(f"   position error   {p:.3f} m")
    print(f"   velocity error   {v:.3f} m/s  (truth |V| = {np.linalg.norm(TRUE_V):.2f})")
    print(f"   updates          {ekf.n_pos} position, {ekf.n_brg} bearing")
    if p > 0.25 or v > 0.25:
        print("   FAIL - filter did not converge"); ok = False
    else:
        print("   PASS")

    print("\n2. bearing-only updates must not corrupt range")
    # Deliberately seed the RANGE wrong by 5m along the sightline and feed
    # ONLY bearings. A correct rank-2 update cannot fix it - and, critically,
    # must not make it worse or wander.
    rng = np.random.default_rng(7)
    ekf2 = TargetEKF()
    R0 = truth(0.0) - OWN
    u0 = R0 / np.linalg.norm(R0)
    ekf2.init(0.0, truth(0.0) + u0 * 5.0, TRUE_V)
    before = float(np.linalg.norm(np.array(ekf2.state()[0]) - truth(0.0)))
    for k in range(1, 200):
        t = k * 0.05
        ekf2.predict(t)
        own = OWN + OWN_V * t
        R = truth(t) - own
        u = R / np.linalg.norm(R)
        u = u + rng.normal(0, math.radians(1.2), 3)
        ekf2.update_bearing(own, u / np.linalg.norm(u))
    p2 = np.array(ekf2.state()[0])
    after = float(np.linalg.norm(p2 - truth(10.0)))
    # decompose the surviving error along vs across the sightline
    Rf = truth(10.0) - (OWN + OWN_V * 10.0)
    uf = Rf / np.linalg.norm(Rf)
    err = p2 - truth(10.0)
    along = abs(float(np.dot(err, uf)))
    across = float(np.linalg.norm(err - np.dot(err, uf) * uf))
    print(f"   seeded 5.00 m of pure range error, fed bearings only")
    print(f"   total error {before:.2f} -> {after:.2f} m")
    print(f"   decomposed: along-sightline {along:.2f} m, cross {across:.2f} m")
    if across > 0.6:
        print("   FAIL - bearings failed to control the cross-sightline error"); ok = False
    elif after > before + 1.0:
        print("   FAIL - bearing update actively corrupted the estimate"); ok = False
    else:
        print("   PASS - error stayed along the sightline, where a camera is blind")

    print("\n3. predict_ahead is the lag compensation")
    ok3 = True
    for lag in (0.0, 0.30, 0.48):
        _, _, l, _ = run(seed=3, lag=lag)
        # what a NAIVE feed would give: aim at the current estimate, be late
        naive = np.linalg.norm(TRUE_V) * lag
        print(f"   lag {lag:4.2f}s: predicted-vs-truth {l:.3f} m   "
              f"(uncompensated would be {naive:.2f} m behind)")
        # The bar that matters is the contact geometry: 0.25m ball + 0.332m
        # frame half-diagonal = 0.582m. A prediction inside that can still hit.
        if lag > 0.1 and l > 0.582:
            print("   FAIL - prediction error exceeds the contact radius")
            ok3 = False; ok = False
    print("   PASS - every horizon predicts inside the 0.582m contact radius"
          if ok3 else "   FAIL")

    print("\n4. vision contribution: bearing on vs off")
    for tag, ub in (("position only", False), ("position + bearing", True)):
        p, v, l, _ = run(seed=11, use_bearing=ub)
        print(f"   {tag:20s} pos {p:.3f} m  vel {v:.3f} m/s  lag-pred {l:.3f} m")

    print("\n%s" % ("ALL CHECKS PASSED" if ok else "*** FAILURES ABOVE ***"))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
