# Working on this repo

This is `NinjaPilot-15.02.ninja`, an OpenPilot-derived flight controller
codebase (SimPosix SITL target + a Python UAVTalk/UAVObjects ground tool
under `ground/pyuavtalk/` and `ground/gazebo_bridge/`). Rules below exist
because they were each learned the hard way in earlier sessions - read
them before making changes, not after something breaks.

## Lineage: OpenPilot -> NinjaPilot (NOT LibrePilot)

- **OpenPilot** was the original project; 15.02 was its final-era
  release line before the project shut down (mid-2015). **LibrePilot**
  is the community fork that continued from OpenPilot's end-state.
  **NinjaPilot (this tree)** is its own independent fork of
  OpenPilot 15.02 - it branched before/around the LibrePilot split and
  shares NO history with LibrePilot's later changes. LibrePilot docs,
  fixes, and code layout may LOOK applicable but frequently aren't:
  this tree has its own module set, its own bug surface, and (as of
  these sessions) its own heavy local modifications (FreeRTOS upgrade,
  callback-scheduler priority restructure, SimPosix revival, filter
  fixes). Treat LibrePilot strictly as an occasionally-useful reference,
  never as ground truth.
- A separate **`../OpenPilot` checkout sits alongside this repo** (same
  parent dir, "OP Revo Redux"). It's upstream reference material - e.g.
  `../OpenPilot/matlab/ins/` holds the original MATLAB/MEX validation
  harness for the same insgps EKF C code this tree carries in
  `flight/libraries/insgps13state.c`. Useful for provenance/comparison;
  do not edit it as part of NinjaPilot work.

## FreeRTOS: kernel was REPLACED (V8.0.1 -> V11.3.0), and the rule about it

- The vendored kernel under `flight/pios/common/libraries/FreeRTOS/Source/`
  is **FreeRTOS V11.3.0** (upgraded from the 2014-era V8.0.1 this tree
  shipped with; commit 30ba00007). The Posix port is V11.3.0's
  ThirdParty event-based port (`utils/wait_for_event.c`) - it replaced
  the old SIGUSR1+threadStatus port, which had a confirmed missed-wakeup
  race. ARM_CM3 (coptercontrol/oplinkmini) swapped too, compile-verified.
  The ONE deliberate local patch reapplied on top of stock V11.3.0:
  `uxTaskGetRunTime()` (read-and-clear counter for pios_task_monitor.c),
  in tasks.c + include/task.h.
- Known upgrade fallout already handled (pattern for future targets):
  `vApplicationStackOverflowHook` signature (`TaskHandle_t, char*`),
  `vPortYieldFromISR()` -> `portYIELD_FROM_ISR(x)`, plain-integer
  `configMAX_PRIORITIES` (no cast wrappers), and
  `configCHECK_HANDLER_INSTALLATION 0` where configASSERT is undefined.
  `configMAX_PRIORITIES` history: 5 (stock) -> 7 (STATEESTIMATION/
  ALTITUDEHOLD tasks) -> 8 (STABILIZATIONOUTERLOOP), across all five
  FreeRTOSConfig.h files.
- **DURABLE USER RULE - do not violate:** never patch FreeRTOS kernel
  internals as the first-choice fix for a scheduling/race symptom.
  FreeRTOS is used by a billion devices; a genuine kernel bug would
  manifest everywhere. Wrap around it at the PiOS/application layer
  (task structure, priorities, mutexes) instead. A temporary kernel
  patch is allowed ONLY as a sanity-check experiment and MUST always be
  reverted afterward - the wholesale version upgrade above was the
  sanctioned path precisely because it avoids hand-patched kernel code.

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
- **Disprove your own hypothesis out loud when the data does.** This
  session's outerloop-starvation theory was real but self-healing;
  saying so explicitly (instead of quietly pivoting) is what kept the
  investigation honest and led to the actual cause.

## Architecture facts (confirmed this session, save re-derivation time)

- **Control chain for thrust**: bridge GCSReceiver channel →
  `ManualControlCommand.Throttle` → `StabilizationDesired.Thrust` →
  (outerloop.c `stabilizationOuterloopTask`) → `RateDesired.Thrust` →
  (innerloop.c `stabilizationInnerloopTask`, CRITICAL, gyro-triggered)
  → `ActuatorDesired.Thrust` → (actuator.c mixer) → `ActuatorCommand`
  PWM 1000..2000 → bridge `publish_motor_speeds()` → Gazebo motors.
- **outerloop.c is dispatched ONLY from `AttitudeStateUpdatedCb`**
  (1 in `OUTERLOOP_SKIPCOUNT`=4 AttitudeState updates). No AttitudeState
  publishes → outerloop never runs → `RateDesired` goes stale → whatever
  thrust was last computed persists downstream. innerloop keeps running
  off gyro regardless and faithfully forwards the stale value.
- **AttitudeState is published by StateEstimationCb** only when a filter
  in the active chain sets `SENSORUPDATES_attitude` (cfmFilter for the
  Complementary+Mag chains — see filtercf.c's gyro+accel gating).
- **stabilization.c `StabilizationDesiredUpdatedCb`** maps per-axis
  StabilizationMode → StabilizationStatus.OuterLoop/InnerLoop. "Manual"
  thrust = OUTERLOOP_DIRECT + INNERLOOP_DIRECT (passthrough) — a quad CAN
  fly with Thrust=Manual here; Roll/Pitch stay Attitude-stabilized
  (this is OpenPilot's per-axis scheme, not full-vehicle "Manual" mode).
- **armhandler.c `okToArm()`** blocks arming while thrust mode is
  ALTITUDEHOLD/ALTITUDEVARIO, and any alarm ≥ Critical (except
  GPS/Telemetry) blocks arming.
- **Fusion algorithms** (`RevoSettings.FusionAlgorithm`, set from
  `board_orientation_viz.py` REVOSETTINGS_DEFAULTS): test setup uses
  Complementary+Mag+GPSOutdoor (`cfmQueue`: mag→air→lla→baro→altitude→cfm).
  Attitude = Mahony complementary filter (filtercf.c — verified by P+I
  cross-product structure, Mahony/Hamel/Pflimlin 2008). Vertical channel
  = filteraltitude.c, an alpha-beta (g-h / Benedict-Bordner 1962 family)
  accel+baro filter with BaroKp / BaroKp² gains. INS13 modes instead use
  filterekf.c → insgps13state.c (EKF per Grewal & Andrews, cited in
  source). A MATLAB/MEX validation harness for the same insgps C code
  lives in the sibling checkout `../OpenPilot/matlab/ins/`.

## THE BIG ONE - startup thrust dead-zone / snap (root cause chain, all confirmed)

Every "runaway climb past the 8m ceiling" crash this whole investigation
chased — across FOUR independently tested vertical-filter algorithms —
was dominated by this, not by estimator math:

1. There is a **~9-12s one-time gap between the 1st and 2nd AttitudeState
   publish** near boot/config/arm (exact cause of the gap NOT yet found —
   open thread; filtercf init? config-burst stall of the sensor feed?).
2. During the gap outerloop.c never runs (see dispatch fact above), so
   `RateDesired.Thrust` sits at stale -1.0 while ActuatorCommand sits at
   1000 (idle) — vehicle ignores all throttle commands, sits on ground.
3. When AttitudeState resumes, everything snaps to the live commanded
   value in ONE tick (idle → near-max instantly). Meanwhile the test
   harness / any integrator upstream has wound up during the stall.
4. Vehicle rockets, blows through the ceiling, "crash".

Verification of the chain: `[dbg]` traces of ManualControlCommand /
StabilizationDesired (correct, on time) vs ActuatorDesired/-Command
(stale then snapping); innerloop.c `rateupdates` watchdog collapsing to
-64 then recovering to -6 in one sample the instant AttitudeState
resumed; `AttitudeStateUpdatedCb` callCount trace showing the 12s gap.
NOT the cause: cchain.Stabilization gate (open from boot), arming
(Armed on time), UAVObject event queue (0 drops), scheduler priority of
outerloop (starvation was real early-boot but self-heals; see below).

Fixes landed (in main tree, ALL SYNCED TO ~/ninjapilot-build and built):
- **actuator.c: asymmetric thrust slew-rate limiter** (rising only,
  3.0/s full-range ≈0.67s, never limits a drop). Verified: ActuatorCommand
  now ramps 1007→1013→1025… instead of 1000→1939 in one tick.
- **outerloop.c moved to its own dedicated
  `CALLBACK_TASK_STABILIZATIONOUTERLOOP` (tskIDLE_PRIORITY+4)**, above
  FLIGHTCONTROL — producer-above-consumer, same pattern as
  STATEESTIMATION/ALTITUDEHOLD. `configMAX_PRIORITIES` bumped 7→8 in all
  5 FreeRTOSConfig.h files (simposix/coptercontrol/oplinkmini/osx/win32).

Open threads left mid-stream when this session ended:
- The **~12s AttitudeState gap itself is unexplained and still happens
  every run** (slew limiter only softens the release; the dead window
  remains). Next lead: instrument filtercf.c's first publish and the
  bridge's sensor-send during send_config().
- **Throttle-CUT lag** seen in last run: bridge commanded throttle 0.000
  while ActuatorCommand stayed 1731 for seconds (AttitudeState WAS
  flowing then — so it's a different mechanism, possibly GCSReceiver/
  ManualControl update path). Discovered at the very end, uninvestigated.
- The scripted (estimator-based) test still crashes; retest it only
  after the dead-zone threads above are closed.
- Extensive `[SIMPOSIX-IFDEF-MARKER]` debug prints are scattered in
  stateestimation.c, filteraltitude.c, altitudeloop.c, innerloop.c,
  outerloop.c, uavobjectmanager.c, pios_callbackscheduler.c — promised
  cleanup once the crash is fully fixed.

## Estimator findings that ARE real (fixed earlier, keep)

- filterbaro.c unconditionally clears SENSORUPDATES_baro before
  filteraltitude.c (next in chain) could use it → filteraltitude's
  first_run never cleared → its whole body was dead code. Fixed via
  `IS_REAL(state->baro[0])` gate. VelocityState went ~3/s → thousands/s.
- Cross-thread races created by splitting modules onto own tasks:
  `updatedSensorsMutex` (stateestimation.c), `altitudeMutex`
  (altitudeloop.c). Producer-above-consumer priority ordering in
  pios_callbackscheduler.h (STATEESTIMATION > ALTITUDEHOLD > OUTERLOOP >
  FLIGHTCONTROL) — its comment block is the authoritative history.
- gazebo_bridge.py: never send two UAVTalk objects back-to-back with no
  gap (corrupts/drops one) — gyro every tick, accel alternate ticks.

## Algorithm-variant worktrees (V1-V4 comparison, all crashed pre-fix)

Context: the stock vertical channel (filteraltitude.c) is a fixed-gain
accel+baro complementary filter - alpha-beta / g-h family (canonical
critically-damped form: Benedict & Bordner 1962, "Synthesis of an
Optimal Set of Radar Track-While-Scan Smoothing Equations"), using
BaroKp on altitude and BaroKp^2 on velocity (defaults 0.04/0.0016 from
altitudefiltersettings.xml). Its structural weakness: it cannot
distinguish "accel bias drifted" from "real sustained acceleration" -
both look identical to the slow AccelDriftKi=0.0005 bias tracker, and
the fixed weak baro gain can't out-pull an accumulated integration
error. Four alternatives were implemented and tested independently,
each in its own worktree/branch/build tree so nothing pollutes main.

Branches off ede77d77b (branch `claude`), worktrees in
`../NinjaPilot-alt-*`, isolated build trees `~/ninjapilot-build-v1..v4`:

- **V1 `alt-v1-benedict-bordner`** (worktree `../NinjaPilot-alt-v1-bb`):
  one-line change in filteraltitude.c - velocity-correction gain from
  the approximate `BaroKp^2` to the canonical critically-damped
  Benedict-Bordner relation `beta = BaroKp^2/(2-BaroKp)`. Numerically
  tiny at BaroKp=0.04 (0.0016 vs 0.001633); tested to confirm rather
  than assume. Result: crashed at the same point/altitude as baseline.
- **V2 `alt-v2-sagehusa-adaptive`**: innovation-adaptive bias tracking
  (informal Sage-Husa / Mohamed & Schwarz 1999 style) in
  filteraltitude.c - when |accelState-accelBiasState| stays >1.0 m/s^2
  for >2s (a sustained divergence, not sensor noise), switch bias
  tracking to the fast InitializationAccelDriftKi rate until it
  re-converges. New struct fields gapActive/gapStartTimer +
  SUSTAINED_GAP_THRESHOLD_MPS2/SUSTAINED_GAP_DURATION_MS constants.
  Result: crashed identically.
- **V3 `alt-v3-kalman`**: full rewrite of filteraltitude.c's body into a
  real 3-state Kalman filter - state [altitude, velocity, accelBias],
  3x3 covariance P propagated per predict step (F/B strapdown model,
  accel as control input, Q from accel noise + bias random walk), scalar
  baro measurement update with gain K = P*H'/(H*P*H'+R) derived from
  live covariance instead of any fixed constant. Noise constants:
  ACCEL_NOISE_VAR 1e-2, BIAS_NOISE_VAR 1e-7/s, BARO_NOISE_VAR 0.25 m^2.
  Result: crashed identically.
- **V4 `alt-v4-ekf13i`** (branch `alt-v4-ekf13indoor`): NO C changes -
  config-only switch of RevoSettings.FusionAlgorithm to "INS13Indoor"
  (in `ground/pyuavtalk/board_orientation_viz.py` REVOSETTINGS_DEFAULTS),
  routing everything through the already-in-tree 13-state EKF
  (filterekf.c -> insgps13state.c, Grewal & Andrews; filterstationary.c
  injects the soft pos=0/vel=0 pseudo-measurement indoors). Result: no
  ceiling crash BUT the vehicle never left the ground (alt=0.055m
  through both "climbs") - the test sequence "passed" vacuously. That is
  a FAIL, not a success (per user: "sitting on the ground not climbing
  to height is a fail").

Verdict: V1-V3 failing at the nearly identical moment despite three
structurally different filters is what proved the dominant failure was
upstream of ALL filter math -> led to the manual_hover ground-truth test
-> which exposed the startup thrust dead-zone/snap (see THE BIG ONE).
**The four algorithms were never actually exercised in-flight** - re-run
this comparison after the dead-zone threads are closed to get a real
ranking. When re-running V4, note its worktree launcher needs the
VENV_PY path fix and BUILD_ROOT pointed at ~/ninjapilot-build-v4 (see
SKILLS.md).

## SimPosix / Gazebo bridge debugging patterns

- **DO NOT restart Gazebo server+GUI for every test run.** Reset the
  scene/world instead (see SKILLS.md "Reset instead of relaunch") and
  restart only fw_simposix.elf + gazebo_bridge.py. Full Gazebo restarts
  waste ~10s+ per iteration, add GUI churn, and are almost never needed.
  (Restart Gazebo only if the world SDF/model itself changed or the
  server is wedged.)
- **Stale ELF binary**: all testing/rebuilding happens against the
  rsynced copy at `~/ninjapilot-build` (repo tree does not build
  directly). `run_gazebo_bridge.sh`'s `ELF` points there. rsync changed
  files in, then `make -j4 ARM_SDK_PREFIX=arm-none-eabi- simposix`.
  A `build/` dir carried over from a different tree causes the
  `0xNone commit_hash_prefix` firmware_info error — `rm -rf build` then
  rebuild (version-info.py needs the worktree's `.git` file present,
  rsync WITHOUT `--exclude='.git'` for worktree-based build dirs).
- **`NINJAPILOT_EXTERNAL_PHYSICS=1`** disables sensors.c's own simulated
  sensors; bridge UAVTalk traffic is then the ONLY sensor source.
- **`stabilizationInnerloopTask()` is GyroState-triggered**, not timed;
  a stalled gyro feed looks like a flight-code freeze but isn't.
- **`PIOS_SENSOR_RATE`** is per-target in pios_config.h (500.0f simposix).
- **One deterministically-paced sender loop** per UDP socket; two
  GIL-scheduled threads bursting on one socket silently drop packets.
- When a fix changes the failure mode instead of fixing the problem,
  that's data - but check what else changed between runs first.
- The X3 model accelerates HARD (≈7 m/s gained in ~1s at 0.95 throttle,
  hover ≈0.68). Test controllers need velocity damping and saturation-
  aware anti-windup or they will overshoot any ceiling. Physics engine
  is gz-sim default DART (gz-physics-dartsim-plugin).

## Testing workflow

- `ground/gazebo_bridge/run_gazebo_bridge.sh` launches Gazebo server
  (headless) + GUI (separate processes - macOS can't combine), the ELF,
  and the bridge, lifetimes tied. Before any relaunch: `pkill` all four
  (`gz sim`, `fw_simposix.elf`, `gazebo_bridge.py`,
  `run_gazebo_bridge.sh`) and confirm via `ps aux` - stale processes
  cause cross-talk. But prefer scene-reset iteration (above) over full
  relaunches.
- `NINJAPILOT_TEST_MODE=manual_hover` runs `manual_hover_test()` in
  gazebo_bridge.py: raw-throttle (no hold mode) climb-and-hold at
  10m/20m using GROUND-TRUTH pose feedback only, bypassing the estimator
  entirely. This is the foundation-block test: if it fails, the problem
  is thrust/physics/transport, not estimation. Default (scripted) mode
  is the estimator-based staged test. `NINJAPILOT_VERBOSE=1` enables
  the high-rate [dbg]/[barodiag]/etc prints.
- For ground-truth verification independent of the bridge's own prints,
  subscribe directly to `/world/<world>/pose/info` with gz.transport13.
- C-side (`[SIMPOSIX-IFDEF-MARKER]`, wall-clock stamped) and Python-side
  logs land in the SAME combined logfile - correlate by `t=` wall-clock,
  never by line order.
