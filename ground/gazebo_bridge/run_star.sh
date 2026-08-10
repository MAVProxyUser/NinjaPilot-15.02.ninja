#!/usr/bin/env bash
# One star run, end to end: purge, reset, fly, analyse.
#
# This exists because the sequence was being hand-typed each time and the
# purge step is easy to leave out - which silently corrupts the analysis
# rather than failing. The on-'flash' slot files live in the firmware's CWD
# and PERSIST between runs; decode_fcwd tells flights apart by the low nibble
# of the filename, so flight N and flight N+16 alias onto each other and get
# merged. That produced a "flight" containing two missions, with a 4162s
# dwell and a 0.3Hz sample rate (star100) - numbers that look like data.
#
#   usage: ./run_star.sh <label> [mission]
set -u
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LABEL="${1:?usage: run_star.sh <label> [mission]}"
MISSION="${2:-star}"
SCRATCH="${TMPDIR:-/tmp}"
FCWD="$HOME/ninjapilot-build/fcwd"
ELF="$HOME/ninjapilot-build/build/fw_simposix/fw_simposix.elf"
LOG="$SCRATCH/${LABEL}.log"

# 1. Stop anything still running, and WAIT for it to actually die. A firmware
#    process that outlives the purge writes fresh slots into the directory we
#    just cleaned.
pkill -f gazebo_bridge.py >/dev/null 2>&1 || true
pkill -f fw_simposix.elf  >/dev/null 2>&1 || true
for _ in $(seq 1 20); do
    pgrep -f fw_simposix.elf >/dev/null 2>&1 || break
    sleep 0.5
done
if pgrep -f fw_simposix.elf >/dev/null 2>&1; then
    echo "error: previous fw_simposix.elf will not exit - refusing to run" >&2
    exit 1
fi

# 2. Purge the previous flight's slots, and verify. Never analyse a directory
#    that still holds someone else's data.
rm -f "$FCWD"/233CDC*.o* 2>/dev/null || true
left=$(ls "$FCWD"/233CDC*.o* 2>/dev/null | wc -l | tr -d ' ')
if [ "$left" != "0" ]; then
    echo "error: $left stale slot files remain in $FCWD" >&2
    exit 1
fi

# 3. Reset the scene rather than relaunching Gazebo (see SKILLS.md).
"$HERE/venv/bin/python3" "$HERE/tools/reset_world.py" >/dev/null || true

# 4. Fly.
( cd "$FCWD" && NINJAPILOT_EXTERNAL_PHYSICS=1 "$ELF" > "$SCRATCH/fw_${LABEL}.txt" 2>&1 & )
sleep 3
( cd "$HERE" && NINJAPILOT_BRIDGE_LOG="$LOG" NINJAPILOT_RUN_LABEL="$LABEL" \
    TMPDIR="$SCRATCH" NINJAPILOT_TEST_MODE=mission NINJAPILOT_MISSION="$MISSION" \
    "$HERE/venv/bin/python3" gazebo_bridge.py > "$LOG" 2>&1 & )

# 5. Bounded wait. Never block indefinitely on a log line - a hung run has to
#    report as hung, not as a session that never comes back.
for _ in $(seq 1 130); do
    grep -q "wrote .*png" "$LOG" 2>/dev/null && break
    sleep 3
done
grep -q "wrote .*png" "$LOG" 2>/dev/null || echo "!!! TIMEOUT after ~390s - run did not finish"

sed -n "/=== ${LABEL} ===/,\$p" "$LOG"

# 6. The flash slots have been decoded by now, so delete them. Purging only at
#    the START of the next run leaves a full set of another flight's slots
#    sitting on disk in between, which is what makes the flight-number-mod-16
#    aliasing possible in the first place. Delete them as soon as they have
#    been read.
rm -f "$FCWD"/233CDC*.o* 2>/dev/null || true

# 7. The decoded .jsonl is the thing worth keeping, and it is ~2MB a run.
#    Keep the most recent 12 and drop the rest so this cannot grow without
#    bound (110MB had accumulated before this existed).
ls -t "$SCRATCH"/*_flash.jsonl 2>/dev/null | tail -n +13 | xargs rm -f 2>/dev/null || true

echo "  [cleanup] flash slots deleted; keeping the 12 most recent decoded logs"
