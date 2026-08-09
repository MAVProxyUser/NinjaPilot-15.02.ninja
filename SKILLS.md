# SKILLS.md - operational recipes for this repo

## RULE: analyse all three logs on EVERY run

Board log (what the FC believed) + bridge log (ground truth + harness) +
Gazebo server log (physics/plugin complaints). The bridge runs this
automatically at the end of every flight; give it the bridge log path so
the comparison is complete:

```bash
cd ground/gazebo_bridge
NINJAPILOT_BRIDGE_LOG=/tmp/star_NN.log NINJAPILOT_RUN_LABEL=starNN \
  NINJAPILOT_TEST_MODE=mission NINJAPILOT_MISSION=star \
  ./venv/bin/python3 gazebo_bridge.py > /tmp/star_NN.log 2>&1
```

Or after the fact:

```bash
GZLOG=/tmp/gzserver.log tools/analyze_run.sh starNN /tmp/star_NN.log
```

One log is not enough to tell a controller fault from an estimator fault
from a harness fault - all three have masqueraded as each other here (see
CLAUDE.md for the specific cases).


Concrete, copy-pasteable workflows. CLAUDE.md has the *why*; this has
the *how*. Keep both in sync when workflows change.

## Build (simposix)

All builds happen in `~/ninjapilot-build` (rsynced copy), never in the
repo tree directly.

```bash
# sync just the files you changed (fast path):
rsync -a --exclude='.git' \
  "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/flight/path/to/file.c" \
  ~/ninjapilot-build/flight/path/to/file.c
cd ~/ninjapilot-build && make -j4 ARM_SDK_PREFIX=arm-none-eabi- simposix
```

- `ARM_SDK_PREFIX=arm-none-eabi-` is required (Homebrew toolchain isn't
  auto-detected).
- Full-tree sync for a *worktree* build dir must INCLUDE `.git` (it's a
  gitfile pointer version-info.py needs): `rsync -a <worktree>/ ~/ninjapilot-build-vN/`
  then `rm -rf build` before the first build (stale build dirs from
  another tree produce `invalid suffix 'xNone'` in firmware_info.c).
- Variant build trees: `~/ninjapilot-build-v1..v4` ↔ worktrees
  `../NinjaPilot-alt-{v1-bb,v2-adaptive,v3-kalman,v4-ekf13i}`.

## Run a SITL test

```bash
cd "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/ground/gazebo_bridge"
NINJAPILOT_TEST_MODE=manual_hover NINJAPILOT_VERBOSE=1 \
  nohup ./run_gazebo_bridge.sh > /tmp/gazebo_run_X.log 2>&1 & disown
```

- `NINJAPILOT_TEST_MODE`: `manual_hover` (ground-truth raw-throttle
  10m/20m foundation test) or unset/`scripted` (estimator-based staged
  test). `NINJAPILOT_VERBOSE=1` for high-rate debug prints.
- The test auto-runs on UAVTalk connect; watch the log, don't wait blind:

```bash
timeout 200 bash -c 'until grep -q "sequence done\|CRASH DETECTED\|HARD CEILING" /tmp/gazebo_run_X.log 2>/dev/null; do sleep 3; done'
grep -n "\[test\]" /tmp/gazebo_run_X.log
```

(`sleep N` chained with other commands is blocked by the environment;
use the `timeout N bash -c 'until ...'` polling pattern.)

## Reset instead of relaunch (PREFERRED iteration loop)

Do NOT kill/restart Gazebo between runs. Keep `gz sim -s` and
`gz sim -g` alive; only restart the firmware + bridge, and reset the
world state:

```bash
# 1) stop only firmware + bridge (leave gz sim running):
pkill -f fw_simposix.elf ; pkill -f gazebo_bridge.py ; pkill -f run_gazebo_bridge.sh

# 2) reset the Gazebo world (vehicle back to spawn, sim time zeroed):
gz service -s /world/quadcopter/control \
  --reqtype gz.msgs.WorldControl --reptype gz.msgs.Boolean \
  --timeout 3000 --req 'reset: {all: true}'

# 3) relaunch firmware + bridge only:
cd .../ground/gazebo_bridge
NINJAPILOT_EXTERNAL_PHYSICS=1 ~/ninjapilot-build/build/fw_simposix/fw_simposix.elf & 
NINJAPILOT_TEST_MODE=manual_hover NINJAPILOT_VERBOSE=1 ./venv/bin/python3 -u gazebo_bridge.py > /tmp/run.log 2>&1 &
```

Full `run_gazebo_bridge.sh` relaunch (which restarts Gazebo too) is only
needed when the world/model SDF changed or the gz server is wedged.
If you DO fully relaunch: pkill all four process names and confirm clean
with `ps aux` first - stale processes cause cross-talk.

## Point the launcher at a variant build

`run_gazebo_bridge.sh` hardcodes `BUILD_ROOT="$HOME/ninjapilot-build"`.
For a variant test, sed it (and `git checkout -- run_gazebo_bridge.sh`
afterward), or run the ELF/bridge manually as in the reset recipe:

```bash
sed -i '' 's|BUILD_ROOT="\$HOME/ninjapilot-build"|BUILD_ROOT="$HOME/ninjapilot-build-v3"|' run_gazebo_bridge.sh
```

Worktree copies of the launcher also have a stale `VENV_PY` path - point
it at the main tree's `ground/gazebo_bridge/venv/bin/python3`.

## Log-analysis idioms

- C-side prints are tagged `[SIMPOSIX-IFDEF-MARKER]` and wall-clock
  stamped (`t=<unix seconds>`); Python-side `[test]`/`[dbg]`/`[barodiag]`
  are `time.time()` stamped. Correlate ONLY by `t=`, never line order.
- Key traces and what they prove:
  - `[dbg] ... ActuatorCommand [....]` - real motor PWM (1000=idle).
    Snap vs ramp here is the ground truth for thrust behavior.
  - `[dbg] ... ManualControlCommand.Throttle` / `StabilizationDesired.Thrust`
    - what the flight code *received* (input side OK?).
  - `[dbg] ... ActuatorDesired ... <thrust>` - post-inner-loop output.
  - `innerloop.c watchdog: gyroupdates=X rateupdates=Y` - gyro feed
    health and whether outerloop is running (rateupdates at -64 floor =
    outerloop not executing).
  - `outerloop.c AttitudeStateUpdatedCb: callCount=N` - AttitudeState
    publish cadence; the ~12s gap between callCount 1 and 2 is the
    open dead-zone thread.
  - `[barodiag] baro_alt vs truth_alt delta` - baro pipeline health
    (confirmed good: delta ~0.01-0.03m through a real climb).
  - `[althold] mode=... posDown=... thrustDemand=...` - altitudeloop.c
    state machine; frozen zeros = it never engaged.
- Filter chronological windows with awk on the `t=` field:

```bash
grep "accel integrator" /tmp/run.log | awk -F'[= ]' \
  '{for(i=1;i<=NF;i++){if($i=="t"){t=$(i+1)}}; if (t+0>=T1 && t+0<=T2) print}'
```


## Analysis tools (ground/gazebo_bridge/tools/)

These survive sessions - do NOT recreate them in a scratchpad. All run
under the bridge venv (`ground/gazebo_bridge/venv/bin/python3`).

| tool | what it answers |
|---|---|
| `reset_world.py` | reset the Gazebo scene AND wipe stale flight trails (every run goes through this) |
| `accuracy.py <bridge.log> <fclog.jsonl>` | fused scorecard: truth cross-track per leg, FC's own PathStatus error, estimator bias, yaw-vs-bearing |
| `decode_fcwd.py <fcwd_dir> <out.jsonl>` | decode on-"flash" log slots directly (fallback when a telemetry pull was interrupted, or to peek MID-flight) |
| `relay_proof.py <fclog.jsonl>` | which axis the autotune relay actually drove, per window, from the raw square wave |
| `mission_corners.py` / `star_report.py` | corner overshoot + per-leg stats for full/star missions |
| `yaw_stream.py` | 15s of ground-truth heading (span/stdev) - quantifies yaw limit cycles |

**The iteration loop that actually works:**

```bash
cd ground/gazebo_bridge && ./venv/bin/python3 tools/accuracy.py \
  /tmp/star_NN.log logs/fclog_<newest>_flight0.jsonl
```

Truth says where it flew; the board log says what the FC believed. When
they disagree the problem is the ESTIMATOR; when they agree but both are
off the plan, it is the CONTROLLER. Never tune without checking which.

**Peeking mid-flight** (the FC writes slots continuously; no need to wait
for the post-flight pull):

```bash
./venv/bin/python3 tools/decode_fcwd.py ~/ninjapilot-build/fcwd /tmp/peek.jsonl
```

## Run the relay Autotune

```bash
cd ground/gazebo_bridge && NINJAPILOT_TEST_MODE=autotune ./venv/bin/python3 gazebo_bridge.py
```

Protocol is strict and ORDER MATTERS (autotune.c's state machine):
1. RelayTuningSettings (Mode=Rate, Behavior=Compute|Save) + map a switch
   position to the Autotune flight mode.
2. Arm, climb to hover on MANUAL throttle (thrust passes through the whole
   tune).
3. Switch to Autotune WHILE AIRBORNE with thrust > 0 - AT_INIT refuses to
   start on the ground. VERIFY FlightStatus.FlightMode actually became
   Autotune (two runs silently flew the window in PathPlanner).
4. Relay runs roll -> pitch -> yaw, ~20s each in FIRMWARE TICKS (which lag
   wall clock in this sim - budget ~24s/axis and give yaw extra time or it
   will not converge).
5. Land and DISARM while STILL in Autotune mode - gains are written only
   on the armed->disarmed edge. Leaving the mode first discards everything.

Results land in `logs/autotune_<ts>.json`. **Treat the derived gains as a
diagnostic, not a drop-in**: the ZN recipe is too aggressive for this
airframe (see CLAUDE.md).

## Ground-truth verification (independent of the bridge)

```python
# same venv as the bridge; subscribe directly:
import gz.transport13 as transport
from gz.msgs10.pose_v_pb2 import Pose_V
node = transport.Node()
node.subscribe(Pose_V, "/world/quadcopter/pose/info", on_pose_cb)
```

Never trust only the bridge's self-reported state for crash/altitude
claims.


## On-board FC logs (DebugLog): enable + pull + analyze

The bridge does this automatically around every TEST_MODE flight:
enables DebugLogSettings=OnlyWhenArmed + writes per-object logging
metadata (FC_LOG_OBJECTS in gazebo_bridge.py), then after the flight
pulls every slot over UAVTalk (DebugLogControl Retrieve -> OBJ_REQ
DebugLogEntry) and writes:

    ground/gazebo_bridge/logs/fclog_<ts>_flight<N>.jsonl   # machine
    ground/gazebo_bridge/logs/fclog_<ts>_flight<N>.txt     # readable

Manual pull without flying (after a crash, or of an old session):

```bash
cd ground/gazebo_bridge && NINJAPILOT_TEST_MODE=pull_logs ./venv/bin/python3 gazebo_bridge.py
```

- Objects logged: Position/Velocity/AttitudeState @500ms,
  GPSPositionSensor/PathStatus/GPSVelocitySensor/BaroSensor @1s,
  FlightStatus @2s, WaypointActive/SystemAlarms on-change, plus Text
  entries (arm/disarm markers flush the slot buffer).
- Analysis idiom - estimator vs its own sensors (this is how the
  mission 12-14 vertical bugs were found): load the JSONL, bucket by
  rounded t_us, print BaroSensor.Altitude / PositionState.Down /
  VelocityState.Down / GPSVelocitySensor.Down side by side. Estimator
  healthy = estDown tracks -baroAlt and estVelD tracks gpsVelD.
- Timestamps are FC-side FlightTime (us since boot); t0 = first record
  (the "Armed" text entry). Bridge-log t+ starts at PathPlanner engage,
  ~25-30s later - align by matching the N coordinate, not by clock.
- simposix flashfs = pios_dosfs_logfs.c host files (233CDC00.oNN, one
  per slot) in the firmware CWD (~/ninjapilot-build/fcwd). rm them
  before a session or old flights inflate the flight number. The pull
  path never reads them - same telemetry protocol as real hardware.

## Gazebo GUI: camera follow + mission trails

- Camera follow (no more right-click -> Follow): bridge calls
  `/gui/follow` {x3} + `/gui/follow/offset` at mission start
  (gui_follow() in gazebo_bridge.py). Manual one-off:

```bash
cd ground/gazebo_bridge && ./venv/bin/python3 -c "
import gz.transport13 as t
from gz.msgs10.stringmsg_pb2 import StringMsg
from gz.msgs10.boolean_pb2 import Boolean
n=t.Node(); s=StringMsg(); s.data='x3'
print(n.request('/gui/follow', s, StringMsg, Boolean, 1000))"
```

- Trails: planned (amber) and flown (cyan) are craft-width translucent
  CYLINDER markers (TRAIL_DIAMETER 0.22, alpha ~0.3) - gz renders
  LINE_STRIP at 1px which is invisible at scene distance. Flown tube
  extends one segment per ~1m of travel.
- /marker quirks (cost a lot of debugging): ack type is gz.msgs.Empty;
  the request often returns ok=False even though the marker REGISTERED
  - verify with `/marker/list` (Marker_V), never trust the ok flag.
  DELETE_ALL with ns="ninjapilot_trail" clears stale trails (bridge
  does this at each mission upload).
- Entity tree "Atmosphere"/"Scene" items are world-level components
  (inspect-only physics/render config), not selectable objects.
- Truth heading sampler (yaw limit-cycle measurement):
  scratchpad yaw_stream.py pattern - subscribe pose, extract yaw,
  print span/stdev over 15s.


## NEVER wait unbounded on a log

Waiting loops must have a deadline and must report what they gave up on.
An unbounded `until grep ...; do sleep 2; done` hangs forever when the
expected line never arrives (a crashed run, a changed message, a typo in
the pattern) and looks identical to a slow run:

```bash
# WRONG - hangs forever if the string never appears
until grep -q PASS /tmp/run.log; do sleep 3; done

# RIGHT - bounded, and says why it stopped
for i in $(seq 1 100); do
  grep -qE "PASS|FAIL" /tmp/run.log && break
  sleep 3
done
grep -qE "PASS|FAIL" /tmp/run.log || echo "TIMEOUT: no verdict after 300s - check the run"
```

Nothing in this project should take more than a few seconds to produce a
log: the board log is decoded from disk in ~0.2s and the analysis runs
automatically as the flight ends. If a wait is taking minutes, something is
wrong - do not sit through it.

Also verify edits actually landed. A `python3 - <<EOF` patch script that
asserts AFTER a `.replace()` but BEFORE `open(...,"w")` throws away the
whole edit on failure while looking like it half-worked - which has
produced a commit whose message described a fix that was not in the tree.
Assert first, write once, then `grep` the file to confirm.

## Getting the board log (do NOT wait for a telemetry pull)

On simposix the flashfs backend is pios_dosfs_logfs.c, so the log slots are
already files in the firmware's CWD (`~/ninjapilot-build/fcwd`). Decoding
all of them takes ~0.2s:

```bash
./venv/bin/python3 tools/decode_fcwd.py ~/ninjapilot-build/fcwd out.jsonl
```

The post-flight TELEMETRY pull is therefore OFF by default - it fetches the
same data one DebugLogControl request at a time and costs minutes of dead
time after every flight. To exercise that path (it is the only way to get a
log off REAL hardware, so it must not rot):

```bash
NINJAPILOT_PULL_LOGS=1 NINJAPILOT_TEST_MODE=mission ./venv/bin/python3 gazebo_bridge.py
# or the dedicated mode, which pulls without flying:
NINJAPILOT_TEST_MODE=pull_logs ./venv/bin/python3 gazebo_bridge.py
```

`rm -f ~/ninjapilot-build/fcwd/*.o*` before each run, or slots from the
previous flight are still sitting there.

## Analyse EVERY run (bridge + board + gazebo)

```bash
cd ground/gazebo_bridge
TMPDIR=/tmp tools/analyze_run.sh <label> /tmp/<bridge>.log
```

Prints, in one shot: mission outcome, board-log decode, cross-track score,
oscillation spectrum, estimator health (filtered position vs its own GPS
input, paired on the board's clock) and a gazebo-vs-board sanity check. A
score without the board log cannot separate controller error from estimator
error - the estimator has measured 0.006-0.044m throughout, so path error
has been controller error every time.

Individual tools: `score.py` (one line per run, stackable into a table),
`star_plot.py` (planned vs flown PNG - the same picture the Gazebo trails
show), `porpoise.py` (detrended RMS + dominant period per channel),
`decode_fcwd.py` (decode the FC's own flash slots directly - instant, no
telemetry pull needed, and works mid-flight).

## Do NOT run a second UAVTalk client during a mission

There is no longer a viewer to trip over (it was deleted), but the failure
mode is worth knowing: any second client on UDP 9000 steals the bridge's
packets, because the firmware answers whichever client contacted it last.
Symptom is a mission that flies fine alone and then fails - runaway, ground
contact - with nothing in the logs to explain it.

Same class of hazard: marker publishing is a BLOCKING gz request. Do not
raise the mission supervision loop rate or the trail density much; at 20Hz
with 0.35m segments it starved the sensor-feed thread and crashed the
vehicle. Current safe values: 10Hz loop, 0.5m segments, 50ms marker timeout.

## Wind

Sliders live in the Gazebo window (`gui_plugins/WindControl`, built with
`cmake .. -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qt@5`). Launch the GUI with:

```bash
export GZ_GUI_PLUGIN_PATH="$PWD/gui_plugins/WindControl/build:$GZ_GUI_PLUGIN_PATH"
gz sim -g
```

## GPS noise

The panel LEFT of the wind panel injects GPS noise, so the estimator can be
tested against a degraded fix instead of Gazebo's effectively perfect one:
position sigma 0-5 m, velocity sigma 0-2 m/s, plus a "Clean fix" button.

The noise is NOT applied in Gazebo. The GPS the flight controller sees is
synthesised by the bridge from truth, so the panel only publishes the
requested sigmas on `/ninjapilot/gps_noise` (gz.msgs.Vector3d: x = position
sigma in metres, y = velocity sigma) and `gazebo_bridge.py` adds the noise
as it builds GPSPositionSensor/GPSVelocitySensor. Position noise is applied
in METRES and converted to degrees per-sample, because a fixed degree
offset is a different distance north/south than east/west.

Without the GUI:

```bash
gz topic -t /ninjapilot/gps_noise -m gz.msgs.Vector3d -p "x: 1.5, y: 0.3"
```

Worth knowing when reading results: with a clean fix the estimator tracks
its GPS input to ~0.02m, so path error is controller error. Turn this up
and that stops being true - which is the point of the slider.

To publish wind without the GUI (speed v m/s FROM bearing B):
`linear_velocity.x = -v*sin(B)`, `.y = -v*cos(B)`, and `enable_wind: true`
or WindEffects applies nothing. Links need `<enable_wind>` to be pushed.

## Star mission: current settled values

| knob | value | note |
|---|---|---|
| MISSION_SPEED | 1.5 m/s | 3-4 m/s flew but bought wavy legs and tip-overs |
| MaxRollPitch | 25 deg | 40 overshot to 61 deg and tipped |
| MISSION_WP_RADIUS | 0.8 m | must be SMALLER than ARRIVE_DIST |
| ARRIVE_DIST | 1.2 m | corner hold window; larger than the radius |
| HorizontalVelPID Kp | 4.0 | 6.5 tumbles it into the ground |
| CruiseControl | 1.25 / 40 deg | compensates tilt-lift; off = 2.5x worse altitude |

Change ONE variable per run, and repeat a config before believing a 0.05m
difference - that is inside the noise.

## Git hygiene for experiments

- Experiment branches live in separate worktrees
  (`git worktree add ../NinjaPilot-alt-X -b branch-name <base-commit>`)
  so the main tree stays clean. Baseline for the V1-V4 comparison was
  `ede77d77b` on branch `claude`.
- Commit messages that keep failing via heredoc: write to a scratch
  file and use `git commit -F <file>`.
- Nothing is pushed anywhere; local branches only.

## Current fix status (as of 2026-08-09)

Committed on branch `claude` (local only), built into ~/ninjapilot-build:
- Onboard DebugLog enable/pull mechanism (commit 99621b0b4).
- filteraltitude.c V3: GPS vertical-velocity Kalman update +
  process-noise raise 1e-2 -> 1.0 (commit 1ab94cd69) - fixed the
  inert/wrong-sign vertical velocity state AND the covariance collapse
  that flew missions 12-14 into the ground/away.
- Mission corner smoothing (bridge): FollowVector + per-corner arrival
  speeds + 2D/3D acceptance split + flyaway guard; AxisLockKp 2.5->1.0
  (yaw limit cycle +/-20deg -> +/-0.1deg); craft-width tube trails +
  auto camera follow. Verified: missions 15 & 16 PASS end-to-end
  (233s/256s), star hairpin overshoot 0.00m (was 2-4m).

Open: outerloop ~12s AttitudeState startup gap; throttle-cut lag
mechanism; SIMPOSIX debug print cleanup; corner metric for shallow
turns over-counts legitimate continuation; task #42 real-UBX path
(deliberately sidelined - do not start unasked).
