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

pkill -f gazebo_bridge.py 2>/dev/null
pkill -f fw_simposix 2>/dev/null
for _ in $(seq 1 20); do pgrep -f fw_simposix >/dev/null || break; sleep 0.5; done

# Remove any target left over from a previous run, then reset the world so the
# vehicle starts on the pad rather than wherever it ended up.
gz service -s /world/quadcopter/remove --reqtype gz.msgs.Entity \
  --reptype gz.msgs.Boolean --timeout 2000 \
  --req 'name: "target_ball" type: MODEL' >/dev/null 2>&1
"$BR/venv/bin/python3" "$BR/tools/reset_world.py" >/dev/null 2>&1
sleep 1

rm -f ~/ninjapilot-build/fcwd/233CDC*.o* 2>/dev/null
( cd ~/ninjapilot-build/fcwd && NINJAPILOT_EXTERNAL_PHYSICS=1 \
    ~/ninjapilot-build/build/fw_simposix/fw_simposix.elf > "$SCRATCH/${LABEL}_fw.log" 2>&1 & )
sleep 6

NINJAPILOT_TEST_MODE=intercept NINJAPILOT_RUN_LABEL="$LABEL" \
  "$BR/venv/bin/python3" "$BR/gazebo_bridge.py" > "$LOG" 2>&1

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
