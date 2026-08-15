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

## RULE: purge the previous flight's slots before every run

Use `ground/gazebo_bridge/run_star.sh <label>` rather than hand-typing the
launch sequence. It kills the previous processes, WAITS for them to actually
exit, deletes `~/ninjapilot-build/fcwd/233CDC*.o*`, verifies the directory is
empty, resets the scene, flies, and analyses - and it refuses to run if any
of that fails.

The slot files persist between runs, and `decode_fcwd.py` can only tell
flights apart by the low nibble of the filename, so flight N and flight N+16
alias onto each other and merge. A merged pair does not look broken: it
decodes cleanly and reports a flight containing two missions, with a 4162s
"dwell" and a 0.3Hz sample rate (star100). decode_fcwd now warns when the
kept flight spans more than 600s, but the warning is a backstop - the purge
is the fix.

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

Use `ground/gazebo_bridge/run_star.sh <label>`. It is the only supported way
to fly: it waits for the previous processes to actually exit, purges the flash
slot files, verifies the directory is empty, resets the scene, flies, and runs
the full three-log analysis - and refuses to run if any of that fails.

```bash
cd ground/gazebo_bridge
TMPDIR=/tmp ./run_star.sh star42
```

Hand-rolling the sequence is how stale slots got merged into an analysis (see
the purge rule above).

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

Added 2026-08-09:

- `wp_arrival.py <fclog>` - per-waypoint closest approach, distance at the
  moment the plan retired it, dwell inside 0.5 m, and overshoot PAST the point
  along the inbound leg. Cross-track answers "were the legs straight", which is
  a different question from "did we touch the corners" - a run can score
  beautiful legs and still cut every waypoint by a metre.
- `corner_probe.py <fclog>` - commanded velocity swing, `fractional_progress`
  regression, and command reversals per corner. Answers "is the orbit COMMANDED
  or FLOWN". Needs VelocityDesired in the log.
- `star_geom.py` - THE mission geometry. score.py, wp_arrival.py, star_plot.py
  and analyze_run.sh all import it. It used to be copy-pasted into four places,
  and changing the mission silently invalidated the copies: the scorers kept
  measuring the OLD shape and reported 1.76 m of cross-track that was purely a
  stale planned path. Keep it in step with `build_mission()`.

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
- **Trails now draw from a SEPARATE PROCESS (tools/trail_daemon.py)** so the
  blocking /marker calls cost the flight loop nothing - launched by
  run_intercept.sh and (with NINJAPILOT_MISSION_TRAIL_INPROC=0) run_star.sh.
  It subscribes to the pose stream directly. If trails do not appear:
    - check its heartbeat log ($LABEL_trails.log): "flown=N target=N
      planned=N" with N climbing means it IS drawing; "drone=NO" means it is
      not seeing the model (it matches "x3" lowercase - Gazebo's name).
    - daemon markers use ns="ninjapilot_daemon" so the bridge's DELETE_ALL on
      "ninjapilot_trail" does not wipe them.
    - it feeds _marker_tube GAZEBO ENU (converts NED first); handing it NED
      draws everything underground.
  Manual: `./venv/bin/python3 tools/trail_daemon.py [world]`.
- **Whole-farm GUI view**: the world's <camera_pose> is set for an overview
  with the barn at the top; run_intercept.sh points the camera there via
  /gui/move_to/pose. NINJAPILOT_FOLLOW=1 restores vehicle-chase instead.
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

## Intercept: run it, score it, tune it (2026-08-10)

`run_intercept.sh` is the ONLY supported way, same reason as run_star.sh. It
kills and waits, removes any stale target BOTH before and after the world
reset, purges slots, flies, analyses all three logs, and plots.

```bash
cd ground/gazebo_bridge
./run_intercept.sh icpt01
```

If it aborts with `target_ball STILL present after reset`, restart the
Gazebo server - a knocked-down ball occasionally survives both the remove
service and the reset, and every run after it fails to spawn.

Batch several runs, reporting the miss decomposed (which is the only useful
form - a scalar separation hides whether the error is horizontal or vertical):

```bash
for r in a1 a2 a3; do NINJAPILOT_VISION=0 ./run_intercept.sh $r; done
```

Env knobs, no rebuild needed:

| var | default | what it does |
|---|---|---|
| `NINJAPILOT_VISION` | 1 | 0 disables the camera bearing channel (EKF then runs on position only) |
| `NINJAPILOT_LAG_S` | 0.20 | seconds the EKF predicts ahead; 0 = no lag compensation. NOTE it is engagement-specific: 0.48 was right at DETECT_RANGE 34, 0.20 at 46 - re-measure if the geometry changes |
| `NINJAPILOT_ISPEED` | 2.6 | interceptor speed override, no rebuild |
| `NINJAPILOT_TRAILS` | 1 | 0 drops the trails (drawn by tools/trail_daemon.py) |
| `NINJAPILOT_FOLLOW` | 0 | 1 makes the GUI chase the vehicle; default is the whole-farm overview |
| `TARGET_SPEED` | 1.2 | target m/s |

### Settled intercept values (the COMMITTED baseline)

At 2.6 m/s this strikes 7-8 of 8 first-pass, 0.45-0.58m against 0.582m
geometry. `felt=True` (physics contact) is the criterion; a sampled 0.58m IS
the corner-on contact distance, so it cannot go lower once the ball deflects.

| knob | value | note |
|---|---|---|
| `INTERCEPT_LEVEL_BAND` | 0.10 m | **the load-bearing one.** Climb to level BEFORE committing horizontally. 1.5 -> 0.10 took the miss 1.2m -> 0.5m |
| `INTERCEPT_SPEED` | 2.6 m/s | see the speed warning below |
| `DETECT_RANGE` | 46 m | earlier detection = more time; the only lever the shared budget allows |
| `INTERCEPT_HIT_DIST` | 0.485 m | score ONLY guaranteed contact (face-on); real contact comes from the ball's sensor |
| `TRACK_LAG_S` | 0.20 s | EKF forward prediction; replaced a firmware constant that made things WORSE |
| `INTERCEPT_AIM_HIGH_M` | 0.0 | tested twice, buys nothing - shared-budget |
| `INTERCEPT_CLIMB_FRAC` | 0.6 | 0.9 is worse and noisier |

**SPEED IS CAPPED AT 2.6 UNTIL THE VERTICAL PID IS FIXED - do not just raise
INTERCEPT_SPEED.** 3.0 was pushed and proved a STOCHASTIC knife-edge
(~40-50% strike): the vehicle sometimes overshoots the target's altitude by
+0.7m at level-off. The overshoot is a position-P term in pidcontroldown.cpp
added DOWNSTREAM of guidance, so no guidance-side cap (cmd[2], VerticalVelMax)
bounds it. The airframe itself flies 4.0 m/s stably - it is NOT the limit.
Full analysis and the list of measured-and-reverted attempts is in CLAUDE.md
("CORRECTION to TEN consecutive first-pass"). Fix the vertical PID first.

**Do not spend runs re-splitting the error budget.** Horizontal and vertical
trade ~1:1 and their sum is conserved near 0.5m because `vmax` is shared
(`horizontal = sqrt(vmax^2 - v_climb^2)`). More capability or more time is
the only way below that floor.

**Restart the gz server between comparison batches.** A long-lived server
eventually no-flies (estimator never inits), and marginal results spread
across spawn/reset cycles are not comparable - a fresh-server A/B is what
distinguished real variance from an apparent server-age effect this session.

## Barn trial: does the balloon get stopped, or reach the barn?

`tools/barn_trial.py` runs a scripted matrix of one-shot engagements and
tallies STOPPED vs BARN HIT. Success requires **felt=True** (the vehicle's
own IMU), never a separation number - see the contact-geometry note below
for why separation alone scores false positives.

```bash
cd ground/gazebo_bridge
cat > /tmp/plan.json <<'EOF'
{"minutes": 40, "runs": [
  {"label":"a1","ispeed":3.0,"tspeed":1.2,"vposp":0.10,"vveld":0.08}
]}
EOF
cp /tmp/plan.json "$TMPDIR/barn_trial_plan.json"
./venv/bin/python3 tools/barn_trial.py          # writes barn_trial_results.json
./venv/bin/python3 tools/barn_tally.py          # tally, invalid runs excluded
```

It restarts the gz server every 6 runs and after any timeout/no-fly, hard-
kills a run's whole process group at 300s, and reaps stragglers between runs
- all three were needed; this rig has produced three distinct hangs.

`barn_tally.py` separates INVALID runs (no-fly, spawn failure, timeout) from
real barn hits. A run where the ball never spawned is a harness fault, not a
guidance outcome; scoring it as a miss understates the guidance and hides
harness bugs. Headline rate is over valid engagements only, with the invalid
count printed alongside.

### Measured envelope (2026-08-10, 18 valid engagements, tools/barn_trial_2026-08-10.json)

| interceptor | balloon | stopped | vert at merge |
|---|---|---|---|
| 2.6 | 1.2 | 2/2 | -0.09 / -0.18 |
| 3.0 (vP 0.10) | 1.2 | **2/2** | -0.06 / +0.01 |
| 3.0 (vP 0.05) | 1.2 | **2/2** | +0.03 / +0.03 |
| 3.0 | 1.6 | 1/2 | +0.31 / +0.46 |
| 3.0 | 2.0 | 0/4 | +0.65 .. +0.83 |
| 3.5 | 1.6 | 0/2 | +0.56 / +0.61 |

**Recommended intercept config: INTERCEPT_SPEED 3.0 with
NINJAPILOT_VPOSP=0.10.** 4/4 stopped with vertical inside +/-0.06, versus a
~40-50% coin-flip at the stock 0.25. NOT made the default: `VerticalPosP` is
shared with the star, and 0.10 has not been flown on a mission. Set it
per-batch until someone runs the star at 0.10.

**Balloon >= 1.6 m/s is where it breaks**, and NOT because of VerticalPosP -
0.05 vs 0.10 at balloon 2.0 is statistically identical. Both speeds shorten
time-to-intercept, which grows path_intercept's own `v_time = vgap/t_use`
climb demand, which overshoots. Next lever is the climb cap in paths.c,
re-tested against balloon 1.6-2.0 (it was previously tested at 1.2, where
that term never binds). Full mechanism in CLAUDE.md.

**CONTACT IS NOT SPHERICAL.** The frame is a flat box: ~+/-0.32m vertical
tolerance vs ~+/-0.58 horizontal. A run at sampled separation **0.40m**
scored felt=False because vert was +0.33 - it flew over the ball. Never
score an intercept on separation.

## Validate estimator/filter changes OFFLINE before flying them

```bash
./venv/bin/python3 tools/test_target_ekf.py
```

0.2s instead of a 90s flight. Checks convergence, that bearing updates
cannot corrupt range (the rank-2 Jacobian property), and that
`predict_ahead(tau)` lands on truth tau seconds later. Several guidance
constants that cost multiple flights each could have been rejected here.

## Three-log analysis for an intercept run

`analyze_run.sh` branches on `NINJAPILOT_RUN_KIND` because score.py /
wp_arrival.py / star_plot.py all grade against the star geometry and report
confident nonsense on an intercept. `run_intercept.sh` sets it. Manually:

```bash
NINJAPILOT_RUN_KIND=intercept tools/analyze_run.sh icpt01 "$TMPDIR/icpt01.log"
# or just the intercept-specific comparison:
./venv/bin/python3 tools/intercept_three_log.py \
    "$TMPDIR/icpt01_flash.jsonl" "$TMPDIR/icpt01_track.json"
```

The one output that matters most: **"vehicle TRACKED the vertical command"
vs "did NOT track"**. Those are opposite fixes - the first is a guidance
bug, the second is thrust/tilt starvation - and no separation number
distinguishes them. It is what identified the vertical miss as guidance
under-asking rather than an airframe limit.

## Star mission: current settled values (2026-08-09, corner saga closed)

Best verified: **star136 - cross-track 0.05m mean / 0.12m MAX, zero
overshoot, 109s** (and star133 at 0.06/0.19 before it). The single biggest
factor is that PathFollower yaw stays in AxisLock: yawing while translating
corrupts position ~0.3-0.5m per corner through attitude-lag frame rotation
(see CLAUDE.md "cursive-l" section for mechanism + isolation table).

| knob | value | note |
|---|---|---|
| Yaw during missions | AxisLock (default) | NINJAPILOT_YAW_MODE=pathdirection opts into nose-following at ~3x tracking cost |
| Corner style | FULL STOP | carry-through corners flip a coin on turn direction |
| MISSION_SPEED | 1.5 m/s | leg cruise, ModeParameters[1] |
| MISSION_WP_RADIUS_PRECISE | 0.13 m | vertex-touch distance; half-plane backstop |
| MISSION_CONFIRM_SPEED / DWELL | 0.9 / 0.1s | instant release - the anti-toilet-bowl half |
| MISSION_WP_RADIUS_3D | 0.35 m | vertical legs |
| HorizontalVelPID | [5.5, 0.5, 1.4, 15] | Kd is the load-bearing part |
| HorizontalPosP | 0.35 | 0.60 fights the arrival |
| PATH_LEG_ACCEL / ARRIVAL_GAIN | 0.8 / 0.85 | leg profile / linear arrival taper |
| YAW_LAG_COMP_S | 0.26 | predicted-yaw conversion; helps, incomplete |
| NINJAPILOT_STAR_ARCS=1 | experimental | CircleRight fillet corners; failed at these angles, kept for future |

Analysis additions: `corner_handedness.py` (vertex-centred turn direction -
read its docstring for the three broken metrics it replaced), `plan_check.py`
(logged plan vs star_geom, matches either mission shape), `wp_arrival.py`,
`corner_probe.py`. run_star.sh purges slots after decode and caps kept logs.

Change ONE variable per run; repeat before believing < 0.05m differences.

## Git hygiene for experiments

- Experiment branches live in separate worktrees
  (`git worktree add ../NinjaPilot-alt-X -b branch-name <base-commit>`)
  so the main tree stays clean. Baseline for the V1-V4 comparison was
  `ede77d77b` on branch `claude`.
- Commit messages that keep failing via heredoc: write to a scratch
  file and use `git commit -F <file>`.
- Nothing is pushed anywhere; local branches only.

## Current fix status (as of 2026-08-09, end of session)

Committed on branch `claude` (local only), built into ~/ninjapilot-build:

- Onboard DebugLog enable/pull mechanism (99621b0b4).
- filteraltitude.c V3 (1ab94cd69): GPS vertical-velocity Kalman update +
  process noise 1e-2 -> 1.0. Fixed the inert/wrong-sign vertical velocity
  state AND the covariance collapse that flew missions 12-14 into the ground.
- **Mission-owned corner arrivals** (74a344b16, 218c0cb0b): tight acceptance
  sphere + confirm-speed/dwell for corners, fly-through rule kept for
  fly-through waypoints. The never-executed corner controller was removed.
  Mean closest approach 1.05 m -> 0.11 m.
- **Leg cruise speed as a mission property** (675b74132) + the
  ModeParameters slot-0 union trap, guarded on path mode.
- **The velocity loop had no damping** (14ed55332, d02051cd1):
  HorizontalVelPID [4.0, 0.5, 0.0, 15] -> [5.5, 0.5, 1.4, 15]. This was the
  corner "orbit". Cross-track 0.20 -> 0.12 m, overshoot 0.18 -> 0.03 m.
- Vertical takeoff waypoint; distance-blended corner yaw; farm scenery world
  (Clearpath cpr_agriculture, ported from Gazebo Classic).
- Harness: `run_star.sh` (purge + verify + fly + analyse), `corner_probe.py`,
  `wp_arrival.py`, `star_geom.py`, VelocityDesired logging, uint32
  timestamp-wrap filtering, and decode warnings no longer swallowed by
  `tail -1`.

Open / known:
- MISSION_SPEED 1.5 with Kp 5.5 is only three runs old - good but young.
- Residual ~0.13 m cross-track is CONTROLLER error; the estimator tracks its
  own GPS to 0.015 m, so there is no sensing headroom left there.
- outerloop ~12s AttitudeState startup gap; throttle-cut lag mechanism;
  SIMPOSIX debug print cleanup.
- Task #42 real-UBX path - deliberately sidelined, do not start unasked.
