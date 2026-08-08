# Working on this repo

This is `NinjaPilot-15.02.ninja`, an OpenPilot-derived flight controller
codebase (SimPosix SITL target + a Python UAVTalk/UAVObjects ground tool
under `ground/pyuavtalk/` and `ground/gazebo_bridge/`). Rules below exist
because they were each learned the hard way in earlier sessions - read
them before making changes, not after something breaks.

## Source of truth

- **This repo's own C source is the only source of truth for flight-code
  behavior.** Do not reason from LibrePilot documentation, general
  OpenPilot/PX4/ArduPilot community knowledge, or "how I remember this
  working elsewhere." This tree forked before/around the LibrePilot split
  and has its own module set - check `flight/targets/boards/<target>/firmware/Makefile`'s
  `MODULES` list before assuming a module (e.g. `Attitude` vs
  `StateEstimation`) is even compiled in for the target you're testing.
- When a GCS-side Python helper (`board_orientation_viz.py`,
  `gazebo_bridge.py`) needs to match a flight-code convention (mixer
  layout, sign convention, units), trace it through the actual `.c`/`.h`
  files in `flight/`, not from memory or by analogy to another project.

## Verify claims, don't just derive them

- A hand-derived formula (quaternion transform, sign convention, physics
  relationship) is a hypothesis, not a fact, until it's checked against
  either (a) the actual C source's own convention, or (b) an empirical
  test with concrete numbers. Say "verified via X" only when X actually
  happened in this session - don't imply verification that didn't occur.
- When a fix changes behavior but doesn't produce the *expected* new
  behavior, don't reach for a second, unrelated hypothesis before
  checking whether the fix and the previous investigation are still
  both true. Re-examine what you just changed first.

## SimPosix / Gazebo bridge debugging patterns

- **Stale ELF binary**: the repo's own `build/fw_simposix/fw_simposix.elf`
  goes stale - all testing/rebuilding happens against the rsynced copy at
  `~/ninjapilot-build`. `run_gazebo_bridge.sh`'s `ELF` path must point
  there. Symptom of testing a stale binary: `StabilizationDesired.Thrust`
  ramps correctly but `ActuatorDesired.Thrust` stays stuck at exactly
  `0.0` - check `ls -la` timestamps on the ELF vs the source file with
  the fix before assuming a C-code regression.
- **`NINJAPILOT_EXTERNAL_PHYSICS=1`** disables `sensors.c`'s own simulated
  sensor generation entirely. When set, the ONLY source of new
  `GyroSensor`/`AccelSensor`/etc data is whatever a bridge script sends
  over UAVTalk - nothing else drives it.
- **`stabilizationInnerloopTask()` in `innerloop.c` is a callback directly
  triggered by `GyroState` updates**, not a free-running timer (see
  `GyroStateConnectCallback(GyroStateUpdatedCb)`). If a bridge script's
  sensor feed stalls or drops, the whole inner stabilization loop stops
  computing new `ActuatorDesired` values - this looks like a flight-code
  freeze but is actually a starved input.
- **`PIOS_SENSOR_RATE` is defined per-target** in
  `flight/targets/boards/<target>/firmware/inc/pios_config.h` (500.0f for
  simposix) - this is the actual rate the Stabilization timing model
  (`UPDATE_EXPECTED`, the `gyroupdates` watchdog counter in
  `innerloop.c`) assumes. Don't guess at a "reasonable" sensor-publish
  rate; check this constant.
- **Prefer one deterministically-paced sender loop over multiple
  independently-timed threads sharing one UDP socket.** Two GIL-scheduled
  threads writing to the same socket can burst against each other
  unpredictably; if the firmware's UDP receive buffer can't drain a
  burst, the OS silently drops the overflow (no error, just gaps in the
  gyro feed) - this produces erratic, hard-to-diagnose instability that
  looks like a control-loop or sign bug but isn't one. A single loop with
  a fixed send order and interval removes the race entirely.
- When a fix changes the failure mode instead of fixing the problem,
  that's data, not proof the original hypothesis was wrong - but also
  check what else changed between test runs before forming a new
  hypothesis (rate change vs threading-structure change are different
  bugs with different fixes).

## Testing workflow

- `ground/gazebo_bridge/run_gazebo_bridge.sh` launches Gazebo
  server+GUI (separate processes - macOS can't run `gz sim -r` combined,
  see the script's own comment), `fw_simposix.elf`, and the bridge
  together. Always `pkill` all four process names
  (`gz sim`, `fw_simposix.elf`, `gazebo_bridge.py`, `run_gazebo_bridge.sh`)
  and confirm clean via `ps aux` before relaunching - stale processes
  from a previous run cause confusing cross-talk.
- For independent ground-truth verification of vehicle attitude/position
  during a test (separate from what the bridge's own debug prints claim),
  subscribe directly to Gazebo's `/world/<world>/pose/info` topic with a
  short standalone script using the same `gz.transport13`/`gz.msgs10`
  Python bindings - don't only trust the bridge's self-reported state.
