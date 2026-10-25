# Experiments (preserved as tags, not merged)

These are investigations that are **not** part of the flying default. Each is
kept reachable as an annotated git tag so it can be checked out, compared, or
revived without living as a stray branch. None of them changes the default
build; the committed vertical estimator (`flight/libraries/`,
`flight/modules/StateEstimation/filters/filteraltitude.c`) is unchanged.

Check one out with, e.g., `git checkout experiment/alt-v3-kalman`.

## Vertical-estimator alternatives (alt-v1 … alt-v4)

All four branch from the same base and are **mutually exclusive** — each is a
different replacement for the fixed-gain accel+baro vertical filter. They were
implemented to rank filter math, but the dominant failure they were chasing
turned out to be upstream of all filter math (the startup thrust dead-zone /
snap documented in `CLAUDE.md` → "THE BIG ONE"), so a clean in-flight ranking
was never completed. Revive this comparison only after that thread is closed.

| Tag | Idea | One-line result |
|-----|------|-----------------|
| `experiment/alt-v1-benedict-bordner` | velocity-correction gain set to the canonical critically-damped alpha-beta relation instead of the approximate `BaroKp²` | numerically tiny at `BaroKp=0.04`; behaved as baseline |
| `experiment/alt-v2-sagehusa` | innovation-adaptive bias tracking: switch to a fast accel-bias rate when a sustained divergence is seen | behaved as baseline |
| `experiment/alt-v3-kalman` | full 3-state Kalman filter (altitude, velocity, accel-bias) with a covariance-derived baro gain replacing the fixed constant | behaved as baseline; parts of this (covariance-derived gain, GPS-vel correction) were later folded into the committed filter — see `CLAUDE.md` |
| `experiment/alt-v4-ekf13indoor` | config-only: route baro+mag hold through the in-tree 13-state EKF (INS13Indoor) | no ceiling crash, but the vehicle never left the ground — a vacuous pass, i.e. a fail |

Full forensics live in `CLAUDE.md` ("Algorithm-variant worktrees (V1–V4
comparison)").

## CC3D memory-save (2015)

| Tag | What | Status |
|-----|------|--------|
| `experiment/cc3d-mem-save-2015` | a 2015 attempt to reduce CC3D RAM use, plus related GCS changes | kept for reference only; its own commit message flags it as likely to break things, so it is **not** merged |

## Archive tags (pre-consolidation snapshots)

The 2026-10-24 consolidation advanced `master` to hold every active line of
work. The prior tips are preserved so nothing is lost:

| Tag | Was |
|-----|-----|
| `archive/master-2015` | the original 2015 OpenPilot 15.02 baseline of `master` |
| `archive/litewing-pre-unify` | `litewing` tip before the merge |
| `archive/cubepurple-pre-unify` | `cubepurple` tip before the merge |
| `archive/brk-i2c-pre-unify` | `brk-i2c-sensors` tip before the merge |
| `archive/claude-2026-09-02` | the `claude` branch (fully contained in litewing) |
| `archive/recovered-brk-docs-2026-08-20` | a recovered dangling BRK-docs commit |
