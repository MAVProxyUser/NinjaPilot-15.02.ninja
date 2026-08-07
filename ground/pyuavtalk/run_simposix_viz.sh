#!/usr/bin/env bash
#
# run_simposix_viz.sh - launch fw_simposix.elf and board_orientation_viz.py
# together as one unit: killing this script kills both, and either one
# dying on its own (crash, Ctrl+C in another terminal, closed) takes the
# other down with it.
#
# Usage:
#   ./run_simposix_viz.sh [extra args passed straight to board_orientation_viz.py]
#   ./run_simposix_viz.sh --open
#
# The OpenPilot Team, http://www.openpilot.org, Copyright (C) 2011.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

set -u

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$HERE/../.." && pwd)"
ELF="$REPO_ROOT/build/fw_simposix/fw_simposix.elf"

if [ ! -x "$ELF" ]; then
    echo "error: $ELF not found." >&2
    echo "Build it first:" >&2
    echo "  cd \"$REPO_ROOT\" && make fw_simposix" >&2
    exit 1
fi

SIM_PID=""
VIZ_PID=""

cleanup() {
    trap - EXIT INT TERM
    for pid in "$VIZ_PID" "$SIM_PID"; do
        if [ -n "$pid" ] && kill -0 "$pid" 2>/dev/null; then
            kill "$pid" 2>/dev/null
        fi
    done
    # Give them a moment to exit cleanly, then make sure they're gone.
    for pid in "$VIZ_PID" "$SIM_PID"; do
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

echo "Starting fw_simposix.elf..."
"$ELF" &
SIM_PID=$!

echo "Starting board_orientation_viz.py..."
python3 "$HERE/board_orientation_viz.py" "$@" &
VIZ_PID=$!

# Whichever of the two dies first ends the whole run; the EXIT trap above
# takes the other one down with it.
while true; do
    if ! kill -0 "$SIM_PID" 2>/dev/null; then
        echo "fw_simposix.elf exited - shutting down."
        exit 1
    fi
    if ! kill -0 "$VIZ_PID" 2>/dev/null; then
        echo "board_orientation_viz.py exited - shutting down."
        exit 0
    fi
    sleep 0.5
done
