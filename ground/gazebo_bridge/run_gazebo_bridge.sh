#!/usr/bin/env bash
#
# run_gazebo_bridge.sh - launch Gazebo (headless), fw_simposix.elf (with its
# own internal sensor simulation disabled), and gazebo_bridge.py together as
# one unit, same lifetime-tying pattern as run_simposix_viz.sh.
#
set -u

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$HERE/../.." && pwd)"
# NOTE: this session's testing/rebuilding all happens against the rsynced
# copy at ~/ninjapilot-build (see the earlier run_simposix_viz.sh for the
# same convention), NOT the repo's own build/ dir, which goes stale.
BUILD_ROOT="$HOME/ninjapilot-build"
ELF="$BUILD_ROOT/build/fw_simposix/fw_simposix.elf"
WORLD="$HERE/worlds/quadcopter_ninjapilot.sdf"
VENV_PY="$HERE/venv/bin/python3"

# Lets the world's "model://x3_ninjapilot" include find our locally-patched
# copy of the X3 model (adds a real IMU sensor - see models/x3_ninjapilot).
export GZ_SIM_RESOURCE_PATH="$HERE/models${GZ_SIM_RESOURCE_PATH:+:$GZ_SIM_RESOURCE_PATH}"

# Lets the world's <gui> block find our Wind and GPS-noise panels. Without
# this the GUI still comes up, but silently minus those two plugins
# ("Failed to load plugin [WindControl] : couldn't find shared library") -
# which looked like the panels had broken rather than simply not been found.
export GZ_GUI_PLUGIN_PATH="$HERE/gui_plugins/WindControl/build${GZ_GUI_PLUGIN_PATH:+:$GZ_GUI_PLUGIN_PATH}"

if [ ! -x "$ELF" ]; then
    echo "error: $ELF not found." >&2
    echo "Build it first: cd \"$REPO_ROOT\" && make fw_simposix" >&2
    exit 1
fi
if [ ! -x "$VENV_PY" ]; then
    echo "error: $VENV_PY not found - see this directory's setup notes." >&2
    exit 1
fi

GZ_SERVER_PID=""
GZ_GUI_PID=""
SIM_PID=""
BRIDGE_PID=""

cleanup() {
    trap - EXIT INT TERM
    for pid in "$BRIDGE_PID" "$SIM_PID" "$GZ_GUI_PID" "$GZ_SERVER_PID"; do
        if [ -n "$pid" ] && kill -0 "$pid" 2>/dev/null; then
            kill "$pid" 2>/dev/null
        fi
    done
    for pid in "$BRIDGE_PID" "$SIM_PID" "$GZ_GUI_PID" "$GZ_SERVER_PID"; do
        if [ -n "$pid" ]; then
            for _ in 1 2 3 4 5; do
                kill -0 "$pid" 2>/dev/null || break
                sleep 0.2
            done
            kill -0 "$pid" 2>/dev/null && kill -9 "$pid" 2>/dev/null
        fi
    done
}
trap cleanup EXIT INT TERM

# macOS `gz sim` can't run server+GUI combined in one process (errors out
# immediately - https://github.com/gazebosim/gz-sim/issues/44), so this is
# two separate processes: a headless server driving the actual simulation,
# and a GUI client that just renders whatever the server is doing.
echo "Starting Gazebo server with $WORLD ..."
# --headless-rendering: camera sensors make the server open a visible
# "OgreWindow (0)_0" render window on macOS. This keeps the context
# offscreen - verified the cameras still publish real frames with it.
# Redirect the server's output to a KNOWN path. It was previously left on the
# terminal, so analyze_run.sh's third log defaulted to a stale empty
# /tmp/gzserver.log and the "physics/plugin complaints" leg of the three-log
# rule was silently absent from every run.
gz sim -s -r --headless-rendering "$WORLD" > "${TMPDIR:-/tmp}/gzserver.log" 2>&1 &
GZ_SERVER_PID=$!
sleep 6

echo "Starting Gazebo GUI (this is the window you should see) ..."
gz sim -g &
GZ_GUI_PID=$!
sleep 3

echo "Starting fw_simposix.elf (internal sensor sim disabled) ..."
NINJAPILOT_EXTERNAL_PHYSICS=1 "$ELF" &
SIM_PID=$!
sleep 1

echo "Starting gazebo_bridge.py ..."
"$VENV_PY" -u "$HERE/gazebo_bridge.py" &
BRIDGE_PID=$!

# health_widget.py: tabled for now - see reset_run.sh's comment.

while true; do
    if ! kill -0 "$GZ_SERVER_PID" 2>/dev/null; then
        echo "gz sim server exited - shutting down."
        exit 1
    fi
    if ! kill -0 "$SIM_PID" 2>/dev/null; then
        echo "fw_simposix.elf exited - shutting down."
        exit 1
    fi
    if ! kill -0 "$BRIDGE_PID" 2>/dev/null; then
        echo "gazebo_bridge.py exited - shutting down."
        exit 0
    fi
    sleep 0.5
done
