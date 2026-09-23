#!/usr/bin/env bash
# One wroom-twin run, end to end: purge, reset, fly, report.
#
# Flies the SIM_WROOM target (the posix twin of the ESP32 Thing Plus) with
# the pilot-in-the-loop modes from wroom_pilot.py. Same discipline as
# run_star.sh: kill and WAIT, purge the slot files, reset the scene, fly,
# then put the picture in front of the user. Gazebo server+GUI must already
# be running (start once with run_gazebo_bridge.sh's gz lines or reuse a
# star session's instance).
#
#   usage: ./run_wroom.sh <label> [hover|sticks|rth|flip]
set -u
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LABEL="${1:?usage: run_wroom.sh <label> [hover|sticks|rth|flip|oflip]}"
MODE="${2:-hover}"
SCRATCH="${TMPDIR:-/tmp}"
FCWD="$SCRATCH/wroom_fcwd"
ELF="${NINJAPILOT_WROOM_ELF:-/tmp/njp/build/fw_simwroom/fw_simwroom.elf}"
LOG="$SCRATCH/wroom_${LABEL}.log"

# Gated default, "interceptor" airframe only (2026-09-21): NINJAPILOT_GZ_MODEL=interceptor needs
# NINJAPILOT_MOTOR_BOOST=0.55 alongside it (INTERCEPTOR_FLIGHT_LOG.md's own "real root cause" section
# on this exact regression - a motor-power multiplier the interceptor model's thrust constants were
# measured against, not a bug in those constants themselves). run_intercept.sh already defaults this
# unconditionally since it only ever flies that one airframe; run_wroom.sh is shared with the stock X3
# tests, so this only fires when GZ_MODEL says "interceptor" - it must never change X3 test behavior.
# Confirmed needed again TODAY, not just historically: this tool harness does not persist `export`s
# across tool calls or a context-window compaction (documented in that same section), so the exact
# same silent-drop regression (climb pinned at THR_MIN, straight through the safety ceiling) reproduced
# again this session before this default existed - an explicit override still wins over this default.
if [ "${NINJAPILOT_GZ_MODEL:-x3}" = "interceptor" ]; then
    : "${NINJAPILOT_MOTOR_BOOST:=0.55}"
    export NINJAPILOT_MOTOR_BOOST
fi

# Every 25 runs (shared counter with run_intercept.sh): full gz-sim restart -
# see maybe_restart_gazebo.sh's own comment for why (a real, reproduced
# staleness anomaly after 5h22m/14+ runs with no restart).
# shellcheck source=maybe_restart_gazebo.sh
source "$HERE/maybe_restart_gazebo.sh"

if [ ! -x "$ELF" ]; then
    echo "error: $ELF not found - build with: cd /tmp/njp && make ROOT_DIR=\$PWD fw_simwroom" >&2
    exit 1
fi

# 1. Stop anything still running and WAIT for it - a firmware process that
#    outlives the purge writes fresh slots into the directory just cleaned,
#    and a leftover bridge steals UAVTalk packets from the new one.
pkill -f gazebo_bridge.py >/dev/null 2>&1 || true
pkill -f fw_simwroom.elf  >/dev/null 2>&1 || true
pkill -f fw_simposix.elf  >/dev/null 2>&1 || true
for _ in $(seq 1 20); do
    pgrep -f 'fw_sim(wroom|posix)\.elf' >/dev/null 2>&1 || break
    sleep 0.5
done
if pgrep -f 'fw_sim(wroom|posix)\.elf' >/dev/null 2>&1; then
    echo "error: previous firmware process will not exit - refusing to run" >&2
    exit 1
fi

# 2. Purge the previous flight's slots, and verify.
mkdir -p "$FCWD"
rm -f "$FCWD"/233CDC*.o* 2>/dev/null || true
left=$(ls "$FCWD"/233CDC*.o* 2>/dev/null | wc -l | tr -d ' ')
if [ "$left" != "0" ]; then
    echo "error: $left stale slot files remain in $FCWD" >&2
    exit 1
fi

# 3. Reset the scene rather than relaunching Gazebo.
"$HERE/venv/bin/python3" "$HERE/tools/reset_world.py" >/dev/null || true

# 3.5 TRAILS, in their own process - same discipline as run_intercept.sh/run_star.sh, and for the
# same reason it matters here just as much: trail_daemon.py subscribes directly to Gazebo's own pose
# stream and runs independently of any single test's lifecycle, so a copy left running from an
# earlier wroom_* run just keeps extending its OWN amber "planned" trail from wherever it left off -
# this script never restarted it, so every run since whenever it was first started shared one
# continuous, ever-growing trail. Visually: two (or more) runs launched from the same pad, aiming at
# different bearings, look exactly like the planned trail forking into a Y right at the pad, which is
# not a rendering bug in CameraView/the GUI plugin, it is stale data from a daemon this script forgot
# to restart. NINJAPILOT_TRAILS=0 disables.
pkill -f trail_daemon.py >/dev/null 2>&1 || true
if [ "${NINJAPILOT_TRAILS:-1}" != "0" ]; then
    ( "$HERE/venv/bin/python3" "$HERE/tools/trail_daemon.py" \
        > "$SCRATCH/wroom_${LABEL}_trails.log" 2>&1 & )
fi

# 4. Fly.
( cd "$FCWD" && "$ELF" > "$SCRATCH/fw_wroom_${LABEL}.txt" 2>&1 & )
sleep 3
( cd "$HERE" && NINJAPILOT_BRIDGE_LOG="$LOG" NINJAPILOT_RUN_LABEL="$LABEL" \
    TMPDIR="$SCRATCH" NINJAPILOT_TARGET=wroom NINJAPILOT_TEST_MODE="wroom_${MODE}" \
    NINJAPILOT_FCWD="$FCWD" NINJAPILOT_WROOM_FLIPS="${NINJAPILOT_WROOM_FLIPS:-1}" \
    "$HERE/venv/bin/python3" -u gazebo_bridge.py > "$LOG" 2>&1 & )

# 5. Bounded wait for the run to complete. NINJAPILOT_RUN_TIMEOUT_S raises this for multi-leg missions (shape_test's
# star/oval can run several minutes across 5+ legs, each with its own climb/transition/cruise/recover) - 240s was
# sized for a single hover/sticks/transition run and cut a real, in-progress star mission off mid-flight (2026-09-19).
WAIT_ITERS=$(( ${NINJAPILOT_RUN_TIMEOUT_S:-240} / 3 ))
for _ in $(seq 1 "$WAIT_ITERS"); do
    grep -q "run complete" "$LOG" 2>/dev/null && break
    sleep 3
done
grep -q "run complete" "$LOG" 2>/dev/null || echo "!!! TIMEOUT after ~$((WAIT_ITERS * 3))s - run did not finish"

# 5.5 GUI SCREENSHOT (2026-09-22, direct user request: "make a screen shot of the intercept attempt
# every run too so we can talk about how they failed" - the actual live 3D trail view, not just the
# CSV-driven wroom_report.py plot). Captured HERE, before any cleanup/reset touches the scene, so the
# trail is still exactly as the run left it. `/gui/screenshot` takes a directory (gz.msgs.StringMsg) and
# writes its own auto-timestamped filename into it - moved into a per-label, PASS/FAIL-tagged name right
# after so a failed run is identifiable at a glance without opening the log. A screenshot failing (no
# GUI running, service timeout) is reported but never fails the run itself - this is observability, not
# a test requirement.
if [ "${NINJAPILOT_GUI_SCREENSHOT:-1}" != "0" ]; then
    SHOT_DIR="$HERE/logs/screenshots"
    mkdir -p "$SHOT_DIR"
    SHOT_TMP="$SCRATCH/gz_screenshot_tmp_${LABEL}"
    mkdir -p "$SHOT_TMP"
    if gz service -s /gui/screenshot --reqtype gz.msgs.StringMsg --reptype gz.msgs.Boolean \
        --timeout 3000 --req "data: \"$SHOT_TMP\"" >/dev/null 2>&1; then
        # The service can return success before the PNG is fully flushed to disk - a real,
        # reproduced race (2026-09-22: "service reported success but no file appeared"), not a
        # hypothetical. Poll briefly rather than checking once.
        SHOT_RAW=""
        for _ in $(seq 1 10); do
            SHOT_RAW=$(ls -t "$SHOT_TMP"/*.png 2>/dev/null | head -1)
            [ -n "$SHOT_RAW" ] && break
            sleep 0.3
        done
        if [ -n "${SHOT_RAW:-}" ]; then
            # Tag reflects the INTERCEPT outcome, not the overall PASS/FAIL wrapper - a hit whose
            # post-hit landing failed was still showing up as a "FAIL" screenshot, exactly the
            # HIT/landing conflation the user called out (2026-09-22: "we should never be landing,
            # because we should be hitting our target - 'landing' controlled on purpose is a failure").
            # Derived straight from wroom_pilot.py's own "intercept attempt N: <status> at Xm" line,
            # which is independent of whatever descend_and_land() did afterward.
            ATTEMPT_STATUS=$(grep -o 'intercept attempt [0-9]*: [a-z_]*' "$LOG" 2>/dev/null | tail -1 | awk '{print $NF}')
            case "$ATTEMPT_STATUS" in
                arrived)     INTERCEPT_TAG="HIT" ;;
                visual_lock) INTERCEPT_TAG="LOCK" ;;
                diverging|stalled|timeout|safety) INTERCEPT_TAG="MISS_${ATTEMPT_STATUS}" ;;
                *)           INTERCEPT_TAG="UNKNOWN" ;;
            esac
            SHOT_DEST="$SHOT_DIR/${LABEL}_${INTERCEPT_TAG}_$(date +%Y%m%d_%H%M%S).png"
            mv "$SHOT_RAW" "$SHOT_DEST" && echo "[wroom] GUI screenshot: $SHOT_DEST"
        else
            echo "!!! GUI screenshot: service reported success but no file appeared in $SHOT_TMP"
        fi
    else
        echo "!!! GUI screenshot: /gui/screenshot service call failed (is the gz sim GUI running?)"
    fi
    rm -rf "$SHOT_TMP"
fi

pkill -f gazebo_bridge.py >/dev/null 2>&1 || true
pkill -f fw_simwroom.elf  >/dev/null 2>&1 || true

# 6. Report: pilot track -> picture, plus the wroom lines from the log.
grep "\[wroom\]" "$LOG" | tail -30
CSV=$(ls -t "$HERE"/logs/wroom_${LABEL}_*.csv 2>/dev/null | head -1)
if [ -n "${CSV:-}" ]; then
    "$HERE/venv/bin/python3" "$HERE/tools/wroom_report.py" "$CSV" "$SCRATCH/wroom_${LABEL}.png" \
        && echo "wrote $SCRATCH/wroom_${LABEL}.png"
fi
rm -f "$FCWD"/233CDC*.o* 2>/dev/null || true
