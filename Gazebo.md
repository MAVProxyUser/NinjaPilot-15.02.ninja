# Gazebo.md — stand up the sim and fly the ball-intercept example

A self-contained starting point for an agent that has never touched this
repo. Goal by the end: a Gazebo world running, the NinjaPilot firmware
flying in it as software-in-the-loop (SITL), and one scored run of the
**ball-intercept** example — an interceptor quad that must strike a moving
ball *before the ball reaches the barn*.

`CLAUDE.md` and `SKILLS.md` are the deep references (the *why* and the full
recipe set). This file is the *how do I start* for the Gazebo half only.

---

## 1. What this is

- **`fw_simposix`** — the actual flight-controller firmware built as a
  native binary. It runs the real control stack (attitude, path follower,
  the `PATHDESIRED_MODE_INTERCEPT` guidance in `flight/libraries/paths.c`).
  It has **no sensors of its own** in SITL — the bridge feeds it everything.
- **`ground/gazebo_bridge/gazebo_bridge.py`** — the harness. It bridges
  Gazebo ⇄ firmware over UAVTalk/UDP: it reads ground-truth pose from
  Gazebo and injects IMU/baro/GPS UAVObjects into the firmware, reads the
  firmware's motor commands back out, and drives Gazebo's rotors. It also
  scripts each test, spawns the target, and scores the run.
- **Gazebo** (`gz sim`) — the physics world and renderer.

Division of labour for intercept is deliberate: **the bridge supplies only
the target's position and velocity** (what an external tracker or a second
GPS would give). *All* guidance runs in the firmware, at the follower rate.

---

## 2. The ball-vs-barn scenario (the example you're running)

A ball (`target_ball`) is launched across the farm and flies a diagonal
that passes overhead:

| thing | value | env override |
|---|---|---|
| target model | `target_ball` | — |
| start → end (N,E) | `(-34,-34) → (34,34)`, via overhead | — |
| target altitude | `11.0 m` (above the 8 m mission height) | — |
| target speed | `1.2 m/s` | `NINJAPILOT_TARGET_SPEED` |
| **the barn** | strikes the farm at `BARN_AT = (20,20)` N,E | — |
| interceptor speed cap | `2.6 m/s` (handed to firmware as EndingVelocity) | `NINJAPILOT_ISPEED` |
| lag compensation | `0.20 s` (propagated in the target EKF) | `NINJAPILOT_LAG_S` |
| vision tracking | on | `NINJAPILOT_VISION=0` to disable |

The ball's run **ends by hitting the barn** at `(20,20)`. So the whole
challenge — *"the ball can't hit the barn"* — is: reach and strike the ball
**before** it gets there. The run is scored against that hard deadline
(`t_barn` = time the ball reaches the barn along its own track), and against
*how early* along the track the hit landed. Earliest is best; a "hit" after
the barn deadline is not a hit.

Why the target is slow: the airframe delivers ~1.5 m/s usable cruise, and a
target much faster than that has **no intercept solution** (the lead
quadratic in `path_intercept()` goes non-positive and it degenerates to a
tail chase). 1.2 m/s target vs 2.6 m/s interceptor is the tuned, working
regime.

### How a hit is scored (do not trust a distance number alone)

- **Ground truth is the ball's own physics contact sensor** (`felt=True`) —
  and the vehicle's IMU spike (`IMU_HIT_G = 2.0 g`; hover is ~1.0 g). These
  are the real verdict.
- `INTERCEPT_HIT_DIST = 0.485 m` centre-to-centre is only a *backstop* for a
  strike the 20 Hz sampler stepped over. **Contact is not spherical**: the
  frame is a flat box (±0.235 m horizontal, corner-on ±0.332 m, but only
  ~0.05 m vertical), so a 0.40 m sampled miss can still be `felt=False`
  because it passed *over* the ball. Vertical accuracy matters ~2× horizontal.

---

## 3. Prerequisites (one-time)

1. **Gazebo** — this tree uses `gz sim` with `gz-transport13` bindings
   (Gazebo Harmonic-era). You need the `gz sim`, `gz service`, `gz model`,
   `gz topic` CLIs on `PATH`. Physics is `gz-physics-dartsim` (the default).
2. **ARM/host toolchain for the firmware** — build uses
   `ARM_SDK_PREFIX=arm-none-eabi-` (the Homebrew toolchain is not
   auto-detected). See `SKILLS.md` §Build.
3. **The bridge venv** — already present at
   `ground/gazebo_bridge/venv/` (Python 3 with `gz.transport13`, numpy,
   matplotlib). Every bridge/tool command runs under
   `ground/gazebo_bridge/venv/bin/python3`. If you must recreate it,
   install those into a fresh venv at that path.
4. **macOS note** — `gz sim` cannot run server+GUI in one process on macOS,
   so the launcher starts them as two processes. Camera sensors force an
   offscreen render context (`--headless-rendering`), which still publishes
   real frames.

---

## 4. Directory map (`ground/gazebo_bridge/`)

```
gazebo_bridge.py         the harness (bridge + all test modes + scoring)
run_gazebo_bridge.sh     START: launch gz server + GUI + firmware + bridge
reset_run.sh             fast iteration: reset world, restart fw+bridge only
run_intercept.sh         run ONE scored intercept (the example here)
run_star.sh              run the autonomous star mission (reference)
run_wroom.sh             ESP32-WROOM SITL variant pilot
worlds/quadcopter_ninjapilot.sdf   the world (farm, barn, spawn facing N)
models/                  x3_ninjapilot (the quad, with a real IMU sensor), etc.
gui_plugins/WindControl/  Gazebo GUI panels (wind + GPS noise sliders)
tools/                   analysis + scoring (intercept_plot, intercept_summary,
                         intercept_three_log, target_ekf, trail_daemon, ...)
logs/                    onboard-FC log pulls + run CSVs
venv/                    the Python env everything runs under
```

Builds do **not** happen in the repo tree — they happen in a synced copy at
`~/ninjapilot-build`, which the launchers point to. (This keeps the source
tree clean and matches every recipe in `SKILLS.md`.)

---

## 5. Build the firmware

```bash
# from the repo root, sync the tree into the build dir and build simposix:
rsync -a --exclude='.git' ./ ~/ninjapilot-build/
cd ~/ninjapilot-build && make -j4 ARM_SDK_PREFIX=arm-none-eabi- simposix
```

Result: `~/ninjapilot-build/build/fw_simposix/fw_simposix.elf` — this is
what the launchers run. If a `build/` dir carried over from a different tree
causes a `0xNone`/`invalid suffix 'xNone'` firmware_info error, `rm -rf
~/ninjapilot-build/build` and rebuild. (For day-to-day edits you only rsync
the changed files, not the whole tree — see `SKILLS.md` §Build.)

---

## 6. START and STOP

### Start the world (leave this running)

```bash
cd ground/gazebo_bridge
./run_gazebo_bridge.sh
```

This launches, as lifetime-tied processes: the headless `gz sim -s` server
(world = `worlds/quadcopter_ninjapilot.sdf`, server log → `$TMPDIR/gzserver.log`),
the `gz sim -g` GUI window (what you watch), `fw_simposix.elf` with
`NINJAPILOT_EXTERNAL_PHYSICS=1` (its internal sensor sim off), and
`gazebo_bridge.py`. It sets `GZ_SIM_RESOURCE_PATH`/`GZ_GUI_PLUGIN_PATH` so
the world finds the local model and GUI panels. If any child dies it tears
the rest down.

### Stop everything

```bash
pkill -f run_gazebo_bridge.sh ; pkill -f gazebo_bridge.py ; pkill -f fw_simposix ; pkill -f "gz sim"
```

Then confirm with `ps aux | grep -E "gz sim|fw_simposix|gazebo_bridge"` —
**stale processes cause cross-talk** and have faked "bugs" more than once.

### Iterate WITHOUT restarting Gazebo (preferred)

Restarting `gz sim` costs ~10 s and is almost never needed. Between runs,
reset the world in place and restart only the two cheap processes:

```bash
cd ground/gazebo_bridge && ./reset_run.sh
```

Full `run_gazebo_bridge.sh` relaunch is only needed when the world/model
SDF changed or the gz server has wedged.

---

## 7. Run the ball-intercept example

**Use the script — it is the only supported way**, for a hard-won reason:
launching by hand once skipped the scene reset and left an armed vehicle
chasing a stale path — it drifted 190 m and wrecked the next three runs.

```bash
cd ground/gazebo_bridge
TMPDIR=/tmp ./run_intercept.sh icpt01      # "icpt01" = your run label
```

`run_intercept.sh` does the whole safe cycle: kills+waits for old
processes, **removes any leftover `target_ball` and re-checks after the
world reset** (a knocked-down ball survives both the remove and the reset
and then blocks the next spawn), starts the trail daemon in its own
process, purges the FC flash slots, launches the firmware + bridge with
`NINJAPILOT_TEST_MODE=intercept`, polls the log for the verdict (with early
aborts for the two known dead-run signatures), then plots. It sets the
three-log env (`NINJAPILOT_BRIDGE_LOG`, `NINJAPILOT_RUN_KIND=intercept`,
`GZLOG`) so the run is judged on all three logs, not just the FC's own.

### What you'll see

- The quad arms, climbs, and enters intercept guidance
  (`PATHDESIRED_MODE_INTERCEPT`). The bridge feeds it the ball's position +
  velocity (smoothed by `tools/target_ekf.py`, optionally sharpened by the
  upward camera when `NINJAPILOT_VISION=1`).
- The verdict lines: `grep -E '^\[intercept\]' /tmp/icpt01.log`. Look for
  `felt=True`, the closest-approach distance, the closing-speed collapse,
  the **barn margin** (`object reaches the barn N.Ns into its run`), and
  how far along the track the hit landed.
- A picture at `/tmp/icpt01.png` (both tracks, altitude, separation-with-IMU).
  **A cross-track miss and a timing miss score the same number and look
  nothing alike** — always look at the plot.

### Useful knobs (no rebuild — all env vars)

| var | default | effect |
|---|---|---|
| `NINJAPILOT_ISPEED` | 2.6 | interceptor speed cap (m/s). 3.0 was unstable on the stock velocity tune |
| `NINJAPILOT_TARGET_SPEED` | 1.2 | ball speed. Faster ⇒ harder; ≥1.6 starts hitting the barn |
| `NINJAPILOT_LAG_S` | 0.20 | target-state lead. Re-measure if the geometry changes — it's a property of vehicle *and* engagement |
| `NINJAPILOT_VISION` | 1 | fuse the upward camera bearing (sharpens direction, cannot corrupt range) |
| `NINJAPILOT_VPOSP` | — | vertical position P (0.10 tames the level-off overshoot at higher speeds) |
| `NINJAPILOT_TARGET_MANEUVER` | 0 | ball turns mid-flight (the honest hard case) |
| `NINJAPILOT_TRAILS` | 1 | plan/flown/target trails via the separate daemon (0 to disable) |

---

## 8. The THREE-LOG rule (non-negotiable)

Every run is judged on three logs, never one:

1. **board log** — what the FC believed and commanded (the onboard
   DebugLog; on simposix these are also files in the firmware CWD and decode
   in ~0.2 s — no telemetry needed).
2. **bridge log** — Gazebo ground truth + what the harness did.
3. **Gazebo server log** — physics/plugin complaints (`$TMPDIR/gzserver.log`).

`run_intercept.sh` wires all three automatically. To re-analyse after the
fact:

```bash
cd ground/gazebo_bridge
GZLOG=/tmp/gzserver.log NINJAPILOT_RUN_KIND=intercept \
  tools/analyze_run.sh icpt01 /tmp/icpt01.log
```

Judging on one log has produced *wrong conclusions repeatedly here* — a
phantom estimator bias, a "control bug" that was the harness starving the
sensor thread, a "destabilisation" that was a second UAVTalk client stealing
packets. Disagreement between the three logs **is** the diagnosis.

Intercept-specific analysis: `tools/intercept_plot.py` (separates
cross-track vs timing misses), `tools/intercept_summary.py` (hit rate,
decomposes each miss into horizontal + vertical), `tools/intercept_three_log.py`
(the intercept version of the three-log cross-check). Validate any
`target_ekf.py` change **offline first** with `tools/test_target_ekf.py`
(~0.2 s) before spending a 60–90 s flight on it.

---

## 9. Gotchas that will cost you a run (all learned the hard way)

- **Stale target blocks the next spawn.** A crashed/knocked-down ball
  survives both `/world/quadcopter/remove` *and* the world reset. The next
  run then dies on "could not spawn target". `run_intercept.sh` removes and
  **re-checks after the reset** — if it still can't clear it, restart the gz
  server. (Note the comma in the remove request; without it the request
  silently no-ops.)
- **A long-lived gz server goes stale.** After hours of spawn/remove/reset
  the attitude estimator can stop initialising ("waiting for attitude
  estimator… Critical" forever, vehicle sits on the pad). Restart the server
  between comparison **batches**, and never trust a single marginal run —
  run-to-run variance here is real; re-run before believing a result.
- **Never send two UAVTalk objects back-to-back with no gap** — one gets
  corrupted/dropped. The bridge paces its senders deterministically; keep it
  that way.
- **Don't open a second UAVTalk client on the telemetry port** while the
  bridge runs — the firmware answers whichever client contacted it last, and
  the two silently steal each other's packets. Healthy-solo / breaks-together
  is the signature.
- **Trails must run in their own process** (`tools/trail_daemon.py`, which
  `run_intercept.sh` starts) — a blocking `/marker` call on the guidance
  thread stalls it through the GIL and measurably wrecks the run.

---

## 10. Where to go deeper

- `CLAUDE.md` — the intercept design in full (barrage-not-chase, the
  conserved horizontal/vertical error budget, every measured dead end),
  plus the star-mission and estimator history.
- `SKILLS.md` — copy-pasteable build/run/reset/log-pull recipes.
- `flight/libraries/paths.c` — `path_intercept()`, the actual guidance.
- `ground/gazebo_bridge/gazebo_bridge.py` — `intercept_test()`,
  `spawn_target()`, and the scoring, all near the config block at the top.
