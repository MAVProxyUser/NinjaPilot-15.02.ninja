#!/bin/bash
# The ONLY supported way to run an intercept test.
#
# Exists for the same reason run_star.sh does: launching the pieces by hand
# skips the scene reset, and a test that throws mid-flight then leaves an
# armed vehicle chasing a stale PathDesired. That happened - the quad drifted
# 190m from the pad and landed in a field, and the next three runs started
# from that state without anyone noticing.
set -u
LABEL="${1:-intercept}"
BR="$(cd "$(dirname "$0")" && pwd)"
SCRATCH="${TMPDIR:-/tmp}"
LOG="$SCRATCH/${LABEL}.log"

# Every 25 runs (shared counter with run_wroom.sh): full gz-sim restart - see
# maybe_restart_gazebo.sh's own comment for why.
HERE="$BR"
# shellcheck source=maybe_restart_gazebo.sh
source "$HERE/maybe_restart_gazebo.sh"

# gazebo_bridge.py's MOTOR_BOOST defaults to 1.0 (full, un-boosted rated power)
# when this is unset - see INTERCEPTOR_FLIGHT_LOG.md section 14: every
# InterceptorHoverThrust/InterceptorClimbThrust constant in
# stabilizationsettings.xml was measured with this at 0.55, and flying without
# it makes the same commanded thrust ~2-3x too powerful (looks exactly like a
# runaway control-law bug - pinned/aggressive commands, altitude blowing
# through any target/ceiling). run_wroom.sh and run_star.sh callers have been
# passing this by hand every time; this script never got that habit, so every
# intercept_test run to date flew unboosted. Defaulted here so it can't be
# silently dropped again, still overridable via the environment.
: "${NINJAPILOT_MOTOR_BOOST:=0.55}"
export NINJAPILOT_MOTOR_BOOST

pkill -f gazebo_bridge.py 2>/dev/null
pkill -f fw_simposix 2>/dev/null
for _ in $(seq 1 20); do pgrep -f fw_simposix >/dev/null || break; sleep 0.5; done

# Remove any target left over from a previous run, then reset the world so the
# vehicle starts on the pad rather than wherever it ended up.
# NOTE THE COMMA. Without it the request silently fails to parse, the stale
# ball stays in the world, and the NEXT run's spawn returns ok=False - which
# is how icpt07 died with "could not spawn target" while the log showed a
# perfectly healthy climb.
#
# BOTH NAMES, not just "target_ball" (2026-09-24, real reproduced failure):
# a hit renames the ball to "target_ball_debris" (see gazebo_bridge.py's
# real_contact handling) before releasing it to free-fall - the `grep -q
# target_ball` checks below match that as a SUBSTRING and correctly detect
# it, but the remove SERVICE CALL only ever asked for the exact name
# "target_ball", which a literal "target_ball_debris" entity never matches.
# The result was a detect-but-never-fix loop: both retry loops below ran
# their full 10+8=18s, then the outer check printed "stale target could not
# be removed" (first block) or hard-exited the whole run (second block) -
# reproduced directly this session, losing a full run with zero [intercept]
# output at all after a preceding run's hit left debris behind.
gz service -s /world/quadcopter/remove --reqtype gz.msgs.Entity \
  --reptype gz.msgs.Boolean --timeout 3000 \
  --req 'name: "target_ball", type: MODEL' >/dev/null 2>&1
gz service -s /world/quadcopter/remove --reqtype gz.msgs.Entity \
  --reptype gz.msgs.Boolean --timeout 3000 \
  --req 'name: "target_ball_debris", type: MODEL' >/dev/null 2>&1
# VERIFY, do not assume. A crashed run leaves the ball in the world and the
# next spawn then returns ok=False, wasting a whole cycle - which it did.
for _ in $(seq 1 10); do
    gz model --list 2>/dev/null | grep -q target_ball || break
    gz service -s /world/quadcopter/remove --reqtype gz.msgs.Entity \
      --reptype gz.msgs.Boolean --timeout 2000 \
      --req 'name: "target_ball", type: MODEL' >/dev/null 2>&1
    gz service -s /world/quadcopter/remove --reqtype gz.msgs.Entity \
      --reptype gz.msgs.Boolean --timeout 2000 \
      --req 'name: "target_ball_debris", type: MODEL' >/dev/null 2>&1
    sleep 1
done
gz model --list 2>/dev/null | grep -q target_ball && \
    echo "!!! stale target could not be removed - spawn will fail"
"$BR/venv/bin/python3" "$BR/tools/reset_world.py" >/dev/null 2>&1
sleep 1

# RE-CHECK AFTER THE RESET, not just before it. A knocked-down ball survives
# both the remove service and the reset often enough to matter: lc1 scored a
# hit, and lc2 AND lc3 were then lost to "could not spawn target" - two runs
# thrown away by one stale entity, which is exactly the icpt07 failure this
# script was written to prevent. Removing before the reset is not sufficient,
# because the reset itself can put the entity back into a state where the
# next spawn collides with it.
for _ in $(seq 1 8); do
    gz model --list 2>/dev/null | grep -q target_ball || break
    gz service -s /world/quadcopter/remove --reqtype gz.msgs.Entity \
      --reptype gz.msgs.Boolean --timeout 2000 \
      --req 'name: "target_ball", type: MODEL' >/dev/null 2>&1
    gz service -s /world/quadcopter/remove --reqtype gz.msgs.Entity \
      --reptype gz.msgs.Boolean --timeout 2000 \
      --req 'name: "target_ball_debris", type: MODEL' >/dev/null 2>&1
    sleep 1
done
if gz model --list 2>/dev/null | grep -q target_ball; then
    echo "!!! target_ball STILL present after reset - this run will fail to spawn."
    echo "!!! restart the Gazebo server (run_gazebo_bridge.sh) before continuing."
    exit 1
fi

# TRAILS, in their own process. Blocking /marker calls cost the guidance
# loop nothing from here - separate GIL, separate core - so plan/flown/target
# can be drawn at full rate instead of the eighth-rate compromise the
# in-process version needed. NINJAPILOT_TRAILS=0 disables.
pkill -f trail_daemon.py 2>/dev/null
if [ "${NINJAPILOT_TRAILS:-1}" != "0" ]; then
    ( "$BR/venv/bin/python3" "$BR/tools/trail_daemon.py" \
        > "$SCRATCH/${LABEL}_trails.log" 2>&1 & )
fi

rm -f ~/ninjapilot-build/fcwd/233CDC*.o* 2>/dev/null
( cd ~/ninjapilot-build/fcwd && NINJAPILOT_EXTERNAL_PHYSICS=1 \
    ~/ninjapilot-build/build/fw_simposix/fw_simposix.elf > "$SCRATCH/${LABEL}_fw.log" 2>&1 & )
sleep 6

# Run the bridge in the BACKGROUND and poll the log for the verdict, exactly
# as run_star.sh does. The bridge does not self-terminate when a test
# function returns - client.run() keeps pumping packets forever - so waiting
# on the process in the foreground hangs the whole batch. It did: icpt05
# finished, its bridge stayed up for 82 minutes, and icpt06/07 never started.
# THREE LOGS, exactly as run_star.sh does it - see the rule at the top of
# CLAUDE.md. NINJAPILOT_BRIDGE_LOG is what upgrades analyze_run.sh from
# "board-log analysis only" to the full cross-comparison; without it the run
# is judged on the FC's own account of itself, which is precisely the failure
# this project has repeated. GZLOG is the Gazebo server's stderr, the third
# log - it says whether the simulator itself was unhappy.
NINJAPILOT_TEST_MODE=intercept NINJAPILOT_RUN_LABEL="$LABEL" \
  NINJAPILOT_BRIDGE_LOG="$LOG" NINJAPILOT_RUN_KIND=intercept \
  GZLOG="${GZLOG:-${TMPDIR:-/tmp}/gzserver.log}" \
  "$BR/venv/bin/python3" "$BR/gazebo_bridge.py" > "$LOG" 2>&1 &
BRIDGE_PID=$!

for _ in $(seq 1 90); do
    grep -q "intercept_test: " "$LOG" 2>/dev/null && break
    kill -0 "$BRIDGE_PID" 2>/dev/null || break     # died early
    # EARLY ABORT on the two known dead-run signatures, so a doomed run
    # costs ~60s instead of the full 270s. s35b sat "waiting for attitude
    # estimator" for its entire window - the vehicle never left the pad -
    # because the settle wait loops unboundedly when the gz server has gone
    # stale after hours of spawn/remove cycles. The fix for the CAUSE is a
    # server restart; this guard just stops the harness paying full price.
    # grep -c already prints "0" (and exits 1) on no match, so `|| echo 0` doubled up into
    # "0\n0" and broke the numeric test every cycle with no matches yet (i.e. almost always) -
    # harmless (the poll loop just kept going) but noisy on every run's stderr.
    if [ "$(grep -c 'waiting for attitude estimator' "$LOG" 2>/dev/null)" -gt 20 ]; then
        echo "!!! ESTIMATOR STUCK (never initialised) - aborting run early."
        echo "!!! The gz server is likely stale - restart run_gazebo_bridge.sh."
        break
    fi
    if grep -q "FAIL - could not spawn target" "$LOG" 2>/dev/null; then
        echo "!!! spawn failed - aborting run early."
        break
    fi
    sleep 3
done
grep -q "intercept_test: " "$LOG" 2>/dev/null || echo "!!! TIMEOUT - no verdict after ~270s"

# GUI SCREENSHOT, same as run_wroom.sh's step 5.5 and for the same reason
# (direct user request: a screenshot per attempt to see how/why it failed).
# run_intercept.sh never had this - captured here, before disarm/cleanup
# touches the scene, tagged from the real GAZEBO CONTACT / closest-separation
# lines rather than the overall PASS/FAIL wrapper (a hit whose post-hit
# landing runs long must not look identical to an outright miss).
if [ "${NINJAPILOT_GUI_SCREENSHOT:-1}" != "0" ]; then
    SHOT_DIR="$HERE/logs/screenshots"
    mkdir -p "$SHOT_DIR"
    SHOT_TMP="$SCRATCH/gz_screenshot_tmp_${LABEL}"
    mkdir -p "$SHOT_TMP"
    if gz service -s /gui/screenshot --reqtype gz.msgs.StringMsg --reptype gz.msgs.Boolean \
        --timeout 3000 --req "data: \"$SHOT_TMP\"" >/dev/null 2>&1; then
        SHOT_RAW=""
        for _ in $(seq 1 10); do
            SHOT_RAW=$(ls -t "$SHOT_TMP"/*.png 2>/dev/null | head -1)
            [ -n "$SHOT_RAW" ] && break
            sleep 0.3
        done
        if [ -n "${SHOT_RAW:-}" ]; then
            if grep -q "GAZEBO CONTACT" "$LOG" 2>/dev/null; then
                INTERCEPT_TAG="HIT"
            elif grep -q "intercept_test: PARTIAL" "$LOG" 2>/dev/null; then
                INTERCEPT_TAG="PARTIAL"
            elif grep -q "intercept_test: CRASH" "$LOG" 2>/dev/null; then
                INTERCEPT_TAG="CRASH"
            elif grep -q "intercept_test: FAIL" "$LOG" 2>/dev/null; then
                INTERCEPT_TAG="MISS"
            else
                INTERCEPT_TAG="UNKNOWN"
            fi
            SHOT_DEST="$SHOT_DIR/${LABEL}_${INTERCEPT_TAG}_$(date +%Y%m%d_%H%M%S).png"
            mv "$SHOT_RAW" "$SHOT_DEST" && echo "[intercept] GUI screenshot: $SHOT_DEST"
        else
            echo "!!! GUI screenshot: service reported success but no file appeared in $SHOT_TMP"
        fi
    else
        echo "!!! GUI screenshot: /gui/screenshot service call failed (is the gz sim GUI running?)"
    fi
    rm -rf "$SHOT_TMP"
fi

# The verdict is written before the disarm completes; give it a moment, then
# stop the bridge and the firmware so the next run starts clean.
sleep 4
kill "$BRIDGE_PID" 2>/dev/null
pkill -f fw_simposix 2>/dev/null
for _ in $(seq 1 20); do pgrep -f fw_simposix >/dev/null || break; sleep 0.5; done

echo "=== $LABEL ==="
grep -E "^\[intercept\]" "$LOG" | tail -20

# The picture, every run - a cross-track miss and a timing miss score the
# same and look nothing alike.
TRACK="$SCRATCH/${LABEL}_track.json"
if [ -f "$TRACK" ]; then
    "$BR/venv/bin/python3" "$BR/tools/intercept_plot.py" "$TRACK" "$SCRATCH/${LABEL}.png"
else
    echo "  !!! no track file - the run never reached the intercept loop"
fi
