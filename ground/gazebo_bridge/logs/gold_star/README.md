# Gold-star reference run: 2026-09-23, seed 1, 0.42m hit

First fully-confirmed intercept run captured **after** the frozen-camera root
cause (`--headless-rendering`) was found and fixed, with a real camera-based
RGB/thermal pipeline actually rendering live frames for the first time. Kept
as a known-good reference point per direct user request ("save everything,
commit this as a gold star reference point") after watching it live in the
GUI.

## Result

```
[intercept] *** CONTACT DETECTED at 45.9m - SCRAMBLE ***
[intercept] airborne 11.9s after detection - engaging intercept immediately
[intercept] *** TARGET KNOCKED DOWN ***
[intercept] *** GAZEBO CONTACT *** t+12.0s sep=0.42m
```

`min sep 0.42m`, real physics contact (`hit_gz`), target physically knocked
down and released to free-fall debris physics - not a proximity heuristic.

## Config

- `NINJAPILOT_GZ_MODEL=interceptor`
- `NINJAPILOT_MOTOR_BOOST=0.55`
- `NINJAPILOT_INTERCEPT_SEED=1`
- Launched via `run_intercept.sh batch1_seed1` (label kept in the artifact
  filenames below)

## What was different about this run vs. every earlier one

The camera panels actually showed live, changing content for the first time
(RGB: real ground/sky texture; Thermal: a distinct hot blob, not solid
black) - see `TRANSITION_THEORY.md` section 24 in the HamzasWetDream project
for the full root-cause writeup (the `--headless-rendering` gz-sim launch
flag silently froze every camera sensor's render target after its first
frame; removing it from `run_gazebo_bridge.sh`, `maybe_restart_gazebo.sh`,
and `tools/barn_trial.py` is the fix that made this run's live camera feed
possible). This run is evidence that fix is real and load-bearing, not just
a synthetic-teleport isolated test - the same run that produced this hit is
the one shown live in the GUI with a visibly dynamic RGB/thermal feed.

## Artifacts in this directory

- `gold_star_20260923_155739_seed1_HIT.log` - full bridge/intercept log
- `gold_star_20260923_155739_seed1_HIT_track.json` - raw N/E/alt track for
  both the interceptor and the target, for replotting
- `gold_star_20260923_155739_seed1_HIT_plot.png` - `intercept_plot.py`'s
  rendering of the same track

The GUI screenshot for this exact run (live 3D trail view, RGB/Thermal
panels visible and populated) is at
`../screenshots/batch1_seed1_HIT_20260923_155414.png`.
