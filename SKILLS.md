# SKILLS.md - operational recipes for this repo

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

## Git hygiene for experiments

- Experiment branches live in separate worktrees
  (`git worktree add ../NinjaPilot-alt-X -b branch-name <base-commit>`)
  so the main tree stays clean. Baseline for the V1-V4 comparison was
  `ede77d77b` on branch `claude`.
- Commit messages that keep failing via heredoc: write to a scratch
  file and use `git commit -F <file>`.
- Nothing is pushed anywhere; local branches only.

## Current fix status (as of 2026-08-08 session end)

Landed in main tree AND ~/ninjapilot-build (built, ELF verified):
- actuator.c rising-only thrust slew limiter (3.0/s).
- outerloop.c on dedicated CALLBACK_TASK_STABILIZATIONOUTERLOOP;
  configMAX_PRIORITIES 7→8 in all five FreeRTOSConfig.h.
- gazebo_bridge.py manual_hover_test with P+I+D + saturation-aware
  anti-windup + MAX_CLIMB_THROTTLE=0.75.

Verified working: ActuatorCommand ramps smoothly instead of snapping.
NOT yet fixed (open): the ~12s AttitudeState startup gap (dead window
remains, slew only softens the exit); the end-of-session discovery that
a commanded throttle CUT lagged (ActuatorCommand stuck at 1731 while
bridge commanded 0.0, with AttitudeState flowing - separate mechanism,
uninvestigated); scripted estimator test still crashes; SIMPOSIX debug
prints pending cleanup. Uncommitted changes sit in the main tree - see
`git status`.
