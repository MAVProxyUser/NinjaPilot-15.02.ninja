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

# 4. Fly.
( cd "$FCWD" && "$ELF" > "$SCRATCH/fw_wroom_${LABEL}.txt" 2>&1 & )
sleep 3
( cd "$HERE" && NINJAPILOT_BRIDGE_LOG="$LOG" NINJAPILOT_RUN_LABEL="$LABEL" \
    TMPDIR="$SCRATCH" NINJAPILOT_TARGET=wroom NINJAPILOT_TEST_MODE="wroom_${MODE}" \
    NINJAPILOT_FCWD="$FCWD" NINJAPILOT_WROOM_FLIPS="${NINJAPILOT_WROOM_FLIPS:-1}" \
    "$HERE/venv/bin/python3" -u gazebo_bridge.py > "$LOG" 2>&1 & )

# 5. Bounded wait for the run to complete.
for _ in $(seq 1 80); do
    grep -q "run complete" "$LOG" 2>/dev/null && break
    sleep 3
done
grep -q "run complete" "$LOG" 2>/dev/null || echo "!!! TIMEOUT after ~240s - run did not finish"
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
