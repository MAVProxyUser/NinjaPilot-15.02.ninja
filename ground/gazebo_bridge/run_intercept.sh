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
# NOTE THE COMMA. Without it the request silently fails to parse, the stale
# ball stays in the world, and the NEXT run's spawn returns ok=False - which
# is how icpt07 died with "could not spawn target" while the log showed a
# perfectly healthy climb.
gz service -s /world/quadcopter/remove --reqtype gz.msgs.Entity \
  --reptype gz.msgs.Boolean --timeout 3000 \
  --req 'name: "target_ball", type: MODEL' >/dev/null 2>&1
# VERIFY, do not assume. A crashed run leaves the ball in the world and the
# next spawn then returns ok=False, wasting a whole cycle - which it did.
for _ in $(seq 1 10); do
    gz model --list 2>/dev/null | grep -q target_ball || break
    gz service -s /world/quadcopter/remove --reqtype gz.msgs.Entity \
      --reptype gz.msgs.Boolean --timeout 2000 \
      --req 'name: "target_ball", type: MODEL' >/dev/null 2>&1
    sleep 1
done
gz model --list 2>/dev/null | grep -q target_ball && \
    echo "!!! stale target could not be removed - spawn will fail"
"$BR/venv/bin/python3" "$BR/tools/reset_world.py" >/dev/null 2>&1
sleep 1

rm -f ~/ninjapilot-build/fcwd/233CDC*.o* 2>/dev/null
( cd ~/ninjapilot-build/fcwd && NINJAPILOT_EXTERNAL_PHYSICS=1 \
    ~/ninjapilot-build/build/fw_simposix/fw_simposix.elf > "$SCRATCH/${LABEL}_fw.log" 2>&1 & )
sleep 6

# Run the bridge in the BACKGROUND and poll the log for the verdict, exactly
# as run_star.sh does. The bridge does not self-terminate when a test
# function returns - client.run() keeps pumping packets forever - so waiting
# on the process in the foreground hangs the whole batch. It did: icpt05
# finished, its bridge stayed up for 82 minutes, and icpt06/07 never started.
NINJAPILOT_TEST_MODE=intercept NINJAPILOT_RUN_LABEL="$LABEL" \
  "$BR/venv/bin/python3" "$BR/gazebo_bridge.py" > "$LOG" 2>&1 &
BRIDGE_PID=$!

for _ in $(seq 1 90); do
    grep -q "intercept_test: " "$LOG" 2>/dev/null && break
    kill -0 "$BRIDGE_PID" 2>/dev/null || break     # died early
    sleep 3
done
grep -q "intercept_test: " "$LOG" 2>/dev/null || echo "!!! TIMEOUT - no verdict after ~270s"

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
