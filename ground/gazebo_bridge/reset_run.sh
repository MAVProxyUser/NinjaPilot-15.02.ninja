#!/usr/bin/env bash
#
# reset_run.sh - fast test-iteration cycle: reset the already-running Gazebo
# world in place (no server/GUI restart) and restart only the two cheap,
# stateful processes (fw_simposix.elf, gazebo_bridge.py) so each test starts
# from clean flight-code state (gyroBias, arm status, calibration timers)
# without paying Gazebo's ~10s server+GUI startup cost every iteration.
#
# Requires run_gazebo_bridge.sh to already be running (gz sim server+GUI up).
#
set -u

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_ROOT="$HOME/ninjapilot-build"
ELF="$BUILD_ROOT/build/fw_simposix/fw_simposix.elf"
VENV_PY="$HERE/venv/bin/python3"
LOG="${1:-/tmp/gazebo_reset_run.log}"

echo "Killing run_gazebo_bridge.sh's watchdog wrapper first (SIGKILL, so its EXIT" \
     "trap can't cascade-kill gz sim) ..."
pkill -9 -f "run_gazebo_bridge.sh" 2>/dev/null

echo "Killing fw_simposix.elf and gazebo_bridge.py (leaving gz sim server+GUI up) ..."
pkill -f "fw_simposix.elf" 2>/dev/null
pkill -f "gazebo_bridge.py" 2>/dev/null
sleep 1

echo "Resetting Gazebo world state (time + model poses) ..."
# Fire-and-forget here was the bug: if the reset silently failed or raced
# with the previous run's teardown, the next test would start against a
# vehicle still airborne/tumbling from the PREVIOUS run - looks exactly
# like a fresh-run failure but isn't. Retry the reset + verify against
# real ground-truth pose (not the bridge's own self-reported state) before
# ever starting fw_simposix/the bridge.
RESET_OK=0
for attempt in 1 2 3; do
    gz service -s /world/quadcopter/control \
        --reqtype gz.msgs.WorldControl --reptype gz.msgs.Boolean \
        --timeout 2000 --req 'reset: {all: true}'
    sleep 1
    if "$VENV_PY" "$HERE/verify_reset.py"; then
        RESET_OK=1
        break
    fi
    echo "Reset verification failed (attempt $attempt/3), retrying ..."
done
if [ "$RESET_OK" -ne 1 ]; then
    echo "ERROR: Gazebo world reset could not be verified after 3 attempts - aborting." >&2
    echo "The vehicle may still be airborne/tumbling from a previous run. Check the GUI." >&2
    exit 1
fi

echo "Starting fw_simposix.elf (internal sensor sim disabled) ..."
NINJAPILOT_EXTERNAL_PHYSICS=1 "$ELF" > "$LOG.simposix" 2>&1 &
SIM_PID=$!
sleep 1

echo "Starting gazebo_bridge.py ..."
"$VENV_PY" -u "$HERE/gazebo_bridge.py" > "$LOG" 2>&1 &
BRIDGE_PID=$!

# health_widget.py: tabled for now (wanted embedded in Gazebo's own GUI,
# not a separate pinned window - see its own file for the standalone
# version this isn't launching). Run it manually if wanted:
#   "$VENV_PY" -u "$HERE/health_widget.py"

echo "fw_simposix.elf pid=$SIM_PID, gazebo_bridge.py pid=$BRIDGE_PID, log=$LOG"
