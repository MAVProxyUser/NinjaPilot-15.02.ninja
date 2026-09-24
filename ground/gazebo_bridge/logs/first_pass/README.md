# First-ever PASS verdict: 2026-09-24, seed 2

The first `intercept_test: PASS` (both `hit_gz` AND `hit_imu`, not `PARTIAL`)
this project has ever logged, immediately after fixing the reaction-wrench
mechanism so the interceptor's own IMU genuinely feels a real collision.

```
[intercept] *** TARGET KNOCKED DOWN ***
[intercept] reaction wrench held 20ms: force_ned=[18.3, 17.4, 0.07] rel_vel_ned=[2.44, 2.32, 0.01]
[intercept] *** GAZEBO CONTACT *** t+13.6s sep=0.37m
[intercept]   IMU strike         : YES t+16.6s 19.89g (peak 19.89g)
[intercept] intercept_test: PASS - intercepted=True, felt=True, min_sep=0.37m, track_frac=0.32
```

## Why this needed fixing at all

Every real physical hit before this always read a flat "IMU strike: no
(peak 1.43g)" - the giveaway that nothing was ever being physically felt,
not that the vehicle wasn't really being hit. `target_ball`'s
`VelocityControl` plugin re-asserts its own velocity every physics step
(needed for its own ballistic behavior), which suppresses whatever native
DART collision response would otherwise reach the interceptor's side of a
contact too - only the target's own post-impact velocity was ever scripted.

## Why the first fix attempt still didn't work

Added `gz-sim-apply-link-wrench-system` to `worlds/interceptor.sdf` and
published a momentum-conserving one-shot wrench via its "instantaneous"
`/wrench` topic at the moment of real contact. Confirmed mechanically real
via two isolated tests (a paused-single-step test, and a real-time static
test on the resting vehicle) - but still read flat on every actual in-flight
hit. Root cause, found via a direct IMU-subscriber isolation test: the
one-shot topic's real-time application window is shorter than the IMU
sensor's own ~4ms (250Hz) sample spacing, so it can land entirely between
two samples and simply never get caught.

## The actual fix

Switched to the PERSISTENT `/wrench/persistent` topic, held for a fixed
20ms (`HOLD_S`, comfortably longer than several IMU samples) and then
explicitly cleared via `/wrench/clear`. The force magnitude is scaled down
proportionally (`F = m_target * v_rel / HOLD_S`) so the TOTAL IMPULSE
delivered is identical to the original one-shot calculation - only the
shape changed (longer and gentler, not strictly instantaneous), which is
what makes it unmissable by the sampler. See `gazebo_bridge.py`'s
`_intercept_run()` (search `HOLD_S`) and `TRANSITION_THEORY.md` section
25.4-25.5 in the HamzasWetDream project for the full investigation.

## Artifacts in this directory

- `first_pass_<timestamp>_seed2.log` - full bridge/intercept log
- `first_pass_<timestamp>_seed2_track.json` - raw track for replotting
- `first_pass_<timestamp>_seed2_plot.png` - intercept_plot.py's rendering
