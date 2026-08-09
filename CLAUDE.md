# Working on this repo

## RULE: every flight is judged on THREE logs, never one

Every single run compares:

1. **the flight controller's own log** (simposix DebugLog) - what the FC
   believed and commanded
2. **the bridge log** - Gazebo ground truth and what the harness did
3. **the Gazebo server log** - physics/plugin complaints

`tools/analyze_run.sh` does all three and the bridge now runs it
automatically as each flight ends, so it cannot be skipped:

```bash
NINJAPILOT_BRIDGE_LOG=/tmp/star_NN.log NINJAPILOT_RUN_LABEL=starNN \
  NINJAPILOT_TEST_MODE=mission ./venv/bin/python3 gazebo_bridge.py
```

This is not ceremony. Judging a run on one log has produced wrong
conclusions repeatedly in this project:

- a phantom "0.4m estimator bias" that was a statistics artifact of
  comparing two different sample sets, and which sent tuning down a blind
  alley until the board log's GPS-vs-filtered pairing disproved it
- a "vertical channel destabilisation" blamed on a controller constant that
  was really tilt costing lift (and, for three runs, a second telemetry
  client stealing the bridge's packets)
- corner "control bugs" that were the harness starving the sensor thread

Truth says where it flew; the board log says what the FC believed; the
server log says whether the simulator itself was unhappy. Disagreement
between them IS the diagnosis.

Note the board log does NOT come over telemetry by default - on simposix
the same slots are files on disk and decode in ~0.2s (see SKILLS.md). The
telemetry path is real-hardware-only and is exercised on request.


This is `NinjaPilot-15.02.ninja`, an OpenPilot-derived flight controller
codebase (SimPosix SITL target + a Python UAVTalk/UAVObjects ground tool
under `ground/pyuavtalk/` and `ground/gazebo_bridge/`). Rules below exist
because they were each learned the hard way in earlier sessions - read
them before making changes, not after something breaks.

## RULE: SHOW the top-down plot after every run

Analysing the three logs is not finished until the planned-vs-flown picture
has been put in front of the user. `tools/analyze_run.sh` writes it to
`$TMPDIR/<label>.png` (top-down planned vs actual, plus the altitude profile
with waypoint transitions marked) and the path is printed at the end of the
run; send that file, every time, without being asked.

Numbers and picture answer different questions. A rounded corner, a bowed
leg, an altitude sag and a yaw-induced S all score similarly in a mean
cross-track figure and look nothing alike on the plot - and the altitude
trace is the fastest way to catch a vertical regression that a horizontal
score cannot see at all. Several conclusions this session came from the
shape, not the number.

One more trap the plot cannot save you from: the analysis tools score
against the mission geometry in `tools/star_geom.py`. If the mission changes
and that file does not, every tool keeps scoring the OLD shape and reports
confident nonsense - a mission change once read as 1.76m of cross-track
error that was purely a stale planned path. It is the single source of
truth for all of score.py, wp_arrival.py, star_plot.py and analyze_run.sh;
keep it in step with `build_mission()`.

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

RESOLVED in the 2026-08-08 evening session (commits 7fb5b9ab1,
d45aa42f5, b8999ec7f carry full detail):
- The ~12s AttitudeState gap = filtercf.c's DELIBERATE calibration
  windows (4s ERROR + 6s CRITICAL, zero attitude output until init
  completes), stacked/restarted by config-driven chain re-inits. Handled
  by the bridge's wait_for_attitude_ok() arming gate (the "Always Armed"
  force-arm bypasses okToArm's alarm check, so the harness must enforce
  the contract real hardware enforces via the alarm).
- The throttle-cut lag AND "estimator randomly freezes" = UDP RX thread
  at bottom priority (kernel-queue backlog holding SECONDS of stale
  in-order data) PLUS a com-layer 16-byte-chunked-read corruption
  destroying ~99% of the last-in-burst object at ~350 pkt/s (perfectly
  framed packets failing CRC against a constant stale byte; the 65-byte
  TELEM_USB fifo was exactly one byte short of the 65-byte per-tick
  burst). Fixed: non-blocking drain-per-tick RX at top priority (a
  BLOCKING syscall at high priority wedges the whole Posix-port
  scheduler - learned the hard way), big com buffers, one-read burst
  consumption in telemetryRxTask, telemetry tasks at sensor-bus priority
  on SIMPOSIX only. Verified: rxErrors=0, gyro/accel exact 1:1 lockstep
  at ~510/s.
- **2D BARO ALTITUDE HOLD NOW PASSES** - both scripted stages (real
  AltitudeVario climb to 5ft/10ft + holds, estimator tracking truth to
  centimeters). The manual ground-truth hover foundation test also fully
  passes (45s holds at 10m and 20m, clean landing).
- The V2 sustained-gap heuristic (filteraltitude.c) and the bridge's
  AccelDriftKi=0.05 override were both REMOVED - each was a compensation
  for the broken transport that became actively harmful on clean data
  (absorbing real climb acceleration into the bias estimate within
  ~56ms-2s, blinding the velocity fast-path and causing the vario
  overshoot they were meant to prevent).

**3D GPS POSITIONHOLD: WORKING** (commit 77ac78e73, 2026-08-08 late
session). 60s dedicated hold: max lateral error 0.04m, steady-state
altitude +/-0.05m; full scripted sequence passes end-to-end genuinely
airborne (ground-truth-verified). The three fixes that got there, in
order of discovery:
- V3 Kalman vertical filter ported to main (covariance-derived baro
  gain replacing BaroKp/BaroKp^2).
- **The 90-degree yaw frame error** (the lateral-spiral root cause):
  Gazebo ENU zero-rotation spawn faces EAST; measuring HomeLocation.Be
  in the body frame at spawn defined yaw=0 as east while GPS/NED uses
  true north - PathFollower rotated every correction ~90deg (positive
  feedback, gain-independent divergence). Fixed: world SDF spawns
  facing true north AND Be now derives from the world <magnetic_field>
  ENU->NED (never trust spawn attitude for a world reference).
- VtolPathFollowerSettings.FlyawayEmergencyFallback DISABLED for sim
  (course-error criterion is numerical noise at zero-velocity hover;
  false-tripped a commanded 2.3 m/s descent after 35s of perfect hold).
  Plus: neutral thrust 0.70 (measured), VerticalVelPID 0.6/0.45,
  horizontal cascade detuned for 10Hz GPS feedback, attitude P back to
  stock 2.5.
- `NINJAPILOT_TEST_MODE=poshold` = fast (~2min) PositionHold iteration
  test with real ground-truth pass criteria.

## GPS fidelity: the sim GPS is idealized-ublox-grade, not NMEA-grade

Facts confirmed in this fork's source (relevant whenever GPS behavior is
questioned, per feedback from a former OpenPilot project founder):
- **GPSVelocitySensor is published ONLY by flight/modules/GPS/UBX.c**
  (parse_ubx_nav_velned, NAV-PVT on newer receivers). NMEA.c publishes
  no velocity objects at all - NMEA course/speed-over-ground has no
  vertical velocity. The outdoor EKF fuses GPS velocity as a measurement
  (filterekf.c vel import -> HORIZ_SENSORS|VERT_SENSORS), so on real
  hardware it REQUIRES ublox binary protocol. ubx_autoconfig.c handles
  UBX_HW_VERSION_7/8 explicitly (per-version max nav rates).
- **The SITL bridge bypasses the protocol layer entirely**: it injects
  the POST-parser UAVObjects (GPSPositionSensor with Fix3D/PDOP/sats
  passing filterlla's gates, GPSVelocitySensor with full 3D NED velocity
  from gz-navsat's velocity_north/east/up) at 10Hz. In substance the
  filters receive exactly what a ublox-8 delivers after UBX.c parses it
  - which is why sim PositionHold can hit 4cm. Gazebo itself has NO UBX
  serial-protocol emulation (navsat is protobuf-only); the only mature
  open-source simulated-UBX-byte-stream generator known is ArduPilot
  SITL's GPS backend (SIM_GPS_TYPE can emit real u-blox binary).

SIDELINED FUTURE TASK - "real UBX path" fidelity milestone: the
injection shortcut skips GPS.c/UBX.c/ubx_autoconfig.c completely
(parser timing, status transitions, DOP behavior, autoconfig dance all
unexercised). The clean implementation path already exists: the
firmware's SECOND UDP socket is the GPS port (bound at boot, currently
receiving zero traffic - "udp dev 1" in the boot log), so a small UBX
encoder in the bridge (SOL/POSLLH/VELNED/DOP set, or a single NAV-PVT,
built from the same navsat data) would exercise the REAL GPS module
end-to-end. Reference implementation: ArduPilot's sim_gps. Deliberately
sidelined on 2026-08-08 - do not start it without being asked.

**PATHPLANNER WAYPOINT MISSIONS: WORKING** (commit ba13c9b45). Full
GCS-style autonomous mission flies end-to-end: 29-waypoint star (8m) ->
octagon (18m) -> letters 'KF' (28m) -> Land action (0.6 m/s, horizontal
PH) to auto-disarm, 177s. Upload path is exactly the GCS interface:
multi-instance Waypoint/PathAction objects + PathPlan CRC-8 (poly 0x07
over packed instance bytes, waypoints then actions) validated by the
FLIGHT side before engaging. Engage sequence: upload -> arm -> vario
staging climb -> PositionHold (activates PathFollower) -> switch
position 4 = PathPlanner (FlightModeNumber is 5 now - at 4, the
position-4 channel value silently clamped into the PositionHold bin).
Key flight-code fix: pidcontroldown.cpp RateLimit() clamp was
`accel *= rateLimit/accel` == "always +rateLimit", sign discarded -
any large DOWNWARD setpoint change ramped UPWARD forever (confirmed in
exact +2 m/s^2 steps). It was upstream dead code activated by an
earlier session's smoothing fix. Translucent planned(amber)/flown(cyan)
trails render via Gazebo's /marker LINE_STRIP service.
`NINJAPILOT_TEST_MODE=mission` runs the whole thing supervised with
real ground-truth pass/fail. Known polish item: corner tracking is
loose (+/-2-4m overshoots); 5m-altitude rings clip the ground during
aggressive corners - keep shape rings >= 8m until PathFollower
horizontal tuning gets its own pass.

STILL OPEN (quality-of-life, not blockers):
- The full outdoor EKF (INS13) attitude degrades in flight on sim-clean
  sensors (covariance sanity resets; EKFConfiguration Q/R expect real
  sensor noise) - its own tuning project if ever wanted here.
- The exact defective line in the 16-byte multi-read path (com fifo
  boundary handling) was bypassed by the big single read, not isolated -
  worth a targeted dig someday.
- Extensive `[SIMPOSIX-IFDEF-MARKER]` debug prints remain scattered in
  stateestimation.c, filteraltitude.c, altitudeloop.c, innerloop.c,
  outerloop.c, uavobjectmanager.c, pios_callbackscheduler.c, uavtalk.c,
  pios_udp.c — now eligible for cleanup (3D hold is green).

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

## On-board DebugLog: the FC's own flight recorder (added 2026-08-08)

- The Logging module compiles on simposix (same code as real boards).
  The bridge enables it around EVERY test flight (OnlyWhenArmed - each
  arm..disarm span is one "flight") and pulls/decodes the log after,
  into `ground/gazebo_bridge/logs/fclog_<ts>_flight<N>.jsonl/.txt`.
  `NINJAPILOT_TEST_MODE=pull_logs` downloads without flying. Full
  recipes in SKILLS.md "On-board FC logs".
- What gets logged is driven by per-object logging METADATA written over
  UAVTalk to the metaobject (id = objid+1, 8-byte struct, logging mode
  bits 8-9) - see FC_LOG_OBJECTS in gazebo_bridge.py. Raw sensors
  (BaroSensor, GPSVelocitySensor) are logged ALONGSIDE fused states
  precisely so post-crash analysis can separate "estimator diverged
  from its sensors" from "sensors were wrong".
- Slot decode gotcha: pios_debuglog.c packs FOLLOW-ON records into a
  slot's Data (17-byte sub-headers) and only labels the slot
  MultipleUAVObjects when it overflowed - a Printf flush leaves it
  saying UAVObject with multiple records inside. Always walk the tail.
- On simposix the flashfs backend is pios_dosfs_logfs.c: slots are ALSO
  host files `233CDC00.oNN` in the firmware process CWD (we launch from
  `~/ninjapilot-build/fcwd`; `rm` them pre-session for clean flight
  numbering). The telemetry pull never touches them - it's the same
  DebugLogControl/DebugLogEntry protocol GCS uses on hardware.

## Mission corner smoothing + the estimator bugs it flushed out (2026-08-09)

- Missions 12-16 chronology matters if touching FollowVector or the
  vertical filter; the onboard log pull was the diagnostic tool for all
  of it. Final state: mission 16 PASS - star hairpin overshoot 0.00m on
  all five points (was 2-4m with GoToEndpoint@1.5m/s), yaw locked to
  +/-0.1 deg (was +/-20 deg limit cycle).
- Corner design (all in gazebo_bridge.py build_mission): FollowVector
  mode + per-waypoint arrival speed from the 3D turn angle
  (_corner_speed: 1.5 straight / 0.8 gentle / 0.6 right-angle / 0.45
  hairpin); LEVEL legs use 2D acceptance, vertical-transition legs 3D
  (a 3D sphere is unreachable when the vertical estimate wobbles >1m,
  and FollowVector projects onto the INFINITE line - a missed sphere
  sails away forever at EndingVelocity; mission supervision now has a
  flyaway guard for exactly that).
- filteraltitude.c V3 fixes (commit 1ab94cd69, flight code): (1)
  kfCorrectVel() - GPS vertical velocity was received and DISCARDED;
  without it the velocity state was inert (stale accel + tiny baro
  K[1]) and read WRONG-SIGN during real climbs. (2) process noise
  1e-2 -> 1.0 (m/s^2)^2 - at 1e-2 the covariance collapsed after ~20s
  of agreeing measurements and the filter went deaf (ignored a real
  1 m/s descent straight into the ground). Both invisible in
  PositionHold, where vertical velocity is ~0 - which is where the
  filter had been validated. Full forensics in the commit message.
- Yaw in PathFollower modes is FORCED to AXISLOCK (vtolflycontroller
  yaw_attitude=false branch). AxisLockKp 2.5 demanded 50 deg/s at 20
  deg error = exactly the MaximumRate.Yaw cap, which the X3's weak
  rotor-drag yaw torque can't track -> saturation limit cycle at ~3.7s
  period. AxisLockKp 1.0 (bridge config) kills it.
- Gazebo GUI niceties (bridge does these automatically at mission
  start): camera follow via `/gui/follow` + `/gui/follow/offset`
  services; planned/flown trails as craft-width translucent CYLINDER
  markers (gz renders LINE_STRIP at 1px - invisible; user-confirmed).
  /marker service quirks: reply type is Empty, the call often reports
  ok=False YET the marker registers (verify via /marker/list);
  DELETE_ALL per-namespace clears stale trails.

## Yaw-following waypoints, autotune, and the tuning traps (2026-08-09)

Goal: fly waypoint legs with the nose pointed along the leg. What that
took, and the traps that cost the most time:

- **`StabilizationBank` is a VOLATILE MIRROR.** stabilization.c's
  SettingsBankUpdatedCb re-copies StabilizationSettingsBank1/2/3 (per
  FlightModeMap) over it on EVERY flight-mode change. The bridge wrote
  only the mirror for months, so every stab-bank value silently reverted
  to XML defaults at the first mode switch. Caught only when an onboard
  log showed yaw slewing at ~118 deg/s under a "20 deg/s" cap. ALWAYS
  write `StabilizationSettingsBank1`. Any pre-2026-08-09 conclusion of
  the form "we tuned bank value X and it helped" is suspect.
- **Whole-object writes stomp each other.** The bridge re-sends the
  entire FlightModeSettings on every arm/disarm transition; that wiped a
  custom FlightModePosition mapping the instant the test armed (two
  autotune runs flew their whole window in the WRONG FLIGHT MODE).
  `_fms_position_override` now survives the re-send. Lesson: after
  writing any settings object, VERIFY via readback or FlightStatus, do
  not assume the write stuck.
- **`updatePathBearing()` must use the LEG direction, not
  `progress.path_vector`.** path_vector is a velocity vector that points
  from the vehicle AT the endpoint (GoToEndpoint, and FollowVector once
  past the endpoint), so it swings wildly - and spins - as the vehicle
  passes near a waypoint. Feeding it to the yaw attitude loop whipped the
  nose around at every waypoint and wrecked path tracking (leg reversals,
  32s crawls). Using `End - Start` is constant per leg. This single fix
  turned an oscillating mess into monotonic legs.
- **Point-turn**: UpdateVelocityDesired scales `path_vector` (the
  along-track feed-forward) to zero while the yaw error exceeds 30 deg,
  ramping back in by 10 deg. The vehicle holds its place on the line,
  rotates, THEN flies the leg - which also removes the yaw/translation
  coupling (the NE->body rotation used by UpdateStabilizationDesired was
  previously changing under the velocity controller mid-leg).
- **Yaw command must be SLEWED, never stepped.** A hairpin steps the leg
  bearing ~144 deg; as a step it saturates the yaw loop for seconds and
  starves the mixer of roll/pitch authority - three consecutive
  tip-overs (65-81 deg) traced to exactly this, at several MaximumRate
  caps. vtolflycontroller slews the yaw COMMAND at 20 deg/s.
- **Saturation budget is the real yaw constraint**: yaw command ~=
  RateKp * MaximumRate.Yaw. Autotune's yaw Kp of 0.0416 at 90 deg/s
  demands 3.7x full actuator range. Keep RateKp * MaxRate <~ 0.4 so the
  mixer always retains roll/pitch headroom.

### Relay Autotune (resurrected - see SKILLS.md for how to run it)

flight/modules/Autotune + relay_tuning.c were amputated upstream in
Nov 2014 (OP-1588, present in the OpenPilot checkout's history). Both are
restored and modernized for 15.02 (banks, named-field structs, plus a YAW
relay state the original never had). Findings:

- Measured X3 (reproducible across two independent flights): roll
  113ms/77.2, pitch 155ms/37.5, yaw 560ms/10.2. The roll:pitch period
  ratio 1.37 matches sqrt(Iyy/Ixx)=1.42 from the model's own inertia
  tensor - an independent physics check that the numbers are real.
- **Yaw authority is ~8x weaker than roll** and ~5x slower. This is the
  root physical reason yaw-facing flight is hard on this airframe, and it
  is a property of the MODEL (momentConstant 0.016), not of the firmware.
- **The ZN gain derivation is too aggressive to use as-is.** Applying the
  autotuned rate gains wholesale (Ki 5-8x stock) produced violent
  along-leg oscillation and leg reversals. Reverted to stock rate PIDs.
  The DIAGNOSTIC value of the tune was the win, not its gain recipe.
- **Firmware ticks != wall clock.** The autotune state machine advances
  on FreeRTOS ticks while the bridge times windows on wall clock; the sim
  runs slower than real time, so each relay axis actually ran ~24s
  starting ~4-6s later than the bridge assumed. Consequence: the YAW
  measurement never converged (its gain was still climbing when the
  bridge landed) - treat the yaw numbers as a lower bound.


## Star-mission tuning: what is settled, and the measured ceilings (2026-08-09)

Best config, verified over four runs (score.py, dense 100ms board log):
xtrack **mean 0.20-0.26 m, p95 0.52-0.74, max 0.70-1.21**. Run-to-run
noise is +/-0.03 m on the mean, so DO NOT read a 0.05 m "improvement" as
real without repeating the run.

Settled values (all re-tested against a clean airframe, i.e. after the
yaw frame error and the yaw saturation budget were both fixed):

| knob | value | why not higher/lower |
|---|---|---|
| MISSION_SPEED | 1.5 m/s | 3.0-4.0 flew but bought wavy lines and tip-overs |
| MaxRollPitch | 25 deg | at 40 the attitude loop overshot to 61 and tipped |
| MISSION_WP_RADIUS | 0.8 m | 0.4 scored 0.27 - inside noise, no gain |
| PATH_LEG_ACCEL | 0.6 | 0.35 (with r0.4) scored 0.30, worse |
| HorizontalVelPID Kp | 4.0 | **6.5 tumbles it into the ground (roll p2p 192 deg)** |
| HOLD_GAIN (corner) | 2.5 | the single biggest win: 0.42 -> 0.25 mean |

The corner architecture that works: FollowVector legs + per-corner
arrival speed + point-turn gate + a FIRM hold at the waypoint during the
turn. The hold must apply ONLY above ALIGN_STOP - blending it across the
whole gate band pulls the vehicle backwards on any mid-leg yaw wander
and makes the legs visibly curved.

Known residual: the vehicle still bulges ~0.5-0.7m past each star point.
Cause is structural, not a gain: the plan advances at the acceptance
radius, which is BEFORE the waypoint, so the hold target is still ahead
of the vehicle and briefly commands it forward. Fixing this properly
needs lookahead to the next leg (decide the turn before arriving), which
the fly controller does not currently have.

### Measurement discipline (three separate false conclusions came from this)

- decode_fcwd.py: the log filename packs `flight + 16*(slot/256)` in one
  byte. Misreading it as the flight discarded 3/4 of every log; one run
  "scored" 1.92 m on a 23s fragment that actually scored 0.25 m.
- accuracy.py: comparing mean radius across two DIFFERENT sample sets
  (bridge vs board) invented a 0.4 m "estimator bias" that does not
  exist. Paired on a shared clock the filter tracks its GPS input to
  0.020 m. Remaining path error is CONTROLLER error.
- A zero-length final leg (plan ends on two identical centre waypoints)
  reported landing drift as cross-track error.
- Change ONE variable per run. Star 38 changed radius AND accel together
  and the result was uninterpretable until both were isolated.

## Corner controller, tilt-lift, and the harness bug that faked a control bug (2026-08-09, later)

Best measured star: **0.23m mean / 0.68 p95 / 0.85m max cross-track, altitude
0.20m peak-to-peak, 108s** (star70). Run-to-run noise is +/-0.03m on the mean.

### The harness bug FIRST - it invalidates any run it touched

`board_orientation_viz.py` opened a second UAVTalk client on the SAME UDP
telemetry port as the bridge. The firmware answers whichever client
contacted it last, so the two silently stole each other's packets: missions
that flew fine alone failed with runaways and ground contact whenever the
viewer was open, and NOTHING in the flight logs points at it - it reads as
a control bug. Three consecutive runs were lost, and a "vertical channel
destabilisation" was wrongly blamed on a controller constant.

The viewer is DELETED. Its configuration data survives as
`ground/pyuavtalk/flight_config.py`, which opens no sockets. If anything
ever reintroduces a second UAVTalk client on port 9000, expect exactly this
signature: healthy solo runs, inexplicable failures when the other tool is
open.

Related, same class: **marker publishing is a BLOCKING gz request**. Running
the mission supervision loop at 20Hz with 0.35m trail segments starved the
thread feeding sensors to the firmware and flew the vehicle into the ground.
The trail is cosmetic; it must never compete with flight-critical threads.
Settled at 10Hz / 0.5m / 50ms marker timeout.

### Corner controller (vtolflycontroller.cpp)

ONE block owns the whole corner - approach, arrival, turn, departure.
Splitting the job (yaw-gated translation lock in one place, lookahead yaw
steering in another) is what produced loops and boxy spirals: the two pulled
against each other. Sequence:

  APPROACH  cap along-track speed at sqrt(2*a*(d - ARRIVE_DIST)), keeping
            the feed-forward pointing ALONG THE LEG so the slide-in stays
            on the drawn line
  ARRIVE    park on the waypoint with a BOUNDED command (bounded is what
            keeps it stable through a dwell; the earlier unbounded 2.5x
            hold diverged - a leg entered at 11.3m ended 25.6m out)
  TURN      rotate on the spot
  DEPART    release to normal leg following

**Yaw NEVER gates translation.** A quad is omnidirectional; a hover plus a
rotation cannot move it sideways. If it spirals, translation is being driven
by the turn - that coupling was the original sin behind every spiral.

ARRIVE_DIST (1.2m) must EXCEED the mission acceptance radius (0.8m), or the
plan retires the waypoint before the hold can pull the vehicle onto it and
corners get cut.

### Tilt costs lift - CruiseControl is the missing term

`controlDown` reads only `path_vector[2]`/`correction_vector[2]`, which the
corner controller never writes, so vertical coupling is NOT in the code. It
is physical: braking into a corner needs tilt, and tilt costs lift by
cos(angle). A wider braking window means more time tilted:

    ARRIVE 0.6, CC off : 0.26 mean xtrack, alt p2p 0.59m
    ARRIVE 1.2, CC off : 0.23 mean xtrack, alt p2p 1.53m
    ARRIVE 1.2, CC on  : 0.23 mean xtrack, alt p2p 0.20m

CruiseControl multiplies thrust by 1/cos(tilt). Bounded at MaxPowerFactor
1.25 (covers ~37 deg, above the 25 deg MaxRollPitch) and MaxAngle 40 - past
that the vehicle is tumbling, not manoeuvring, and boosting thrust into a
tumble is why it was disabled originally.

### Lookahead: plumbed, deliberately unused

pathplanner publishes the next leg's bearing in PathDesired
ModeParameters[2]/[3]. iNav (nextTurnAngle) and ArduPilot (next_destination
splines) both steer with it - but on controllers that own the ENTIRE corner
(position, velocity and acceleration through it). Bolted onto a follower
that only owns the current leg, every variant was worse: 0.27-0.51m mean
versus 0.23m without. Useful foundation if a full S-curve corner controller
is ever written; not wired in until then.

### Gazebo GUI

Declaring `<gui>` in the world **REPLACES** Gazebo's defaults, it does not
add to them. A hand-written short list dropped MarkerManager and the flight
trails vanished; a single-plugin block left the wind panel filling the whole
window. The world now embeds gz-sim's own `gui.config` verbatim and appends
only the wind panel (anchored top-right).
