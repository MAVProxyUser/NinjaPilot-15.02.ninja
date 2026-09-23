#!/usr/bin/env bash
# Shared by run_wroom.sh and run_intercept.sh: source this near the top of
# each, after computing $HERE. Every 25 calls (across BOTH scripts, via one
# shared counter file) OR every 60 minutes of server uptime, whichever comes
# first, does a full gz-sim server+GUI restart before the caller's own test
# proceeds.
#
# WHY: a Gazebo server left running for 5h22m across 14+ consecutive test
# cycles produced a real, reproduced anomaly (wroom_icept21, 2026-09-20) -
# pitch frozen at +65 deg, altitude flatlined at exactly 9.37m for 40+
# seconds straight - almost certainly server staleness (a known risk class
# this project has hit before: INTERCEPTOR_FLIGHT_LOG.md's "gz server is
# likely stale" guard in this same run_intercept.sh already existed for a
# DIFFERENT staleness symptom). A clean restart made the anomaly disappear on
# an otherwise-identical retest. Rather than wait for another one-off,
# ugly-looking failure to notice staleness by eye, this restarts on a fixed
# schedule automatically.
#
# THE TIME CHECK, not just the run count (2026-09-20, added after a second
# staleness hit): a run of many short tests can rack up 25 runs slowly, or a
# server can sit idle-but-running between short bursts of runs - either way
# real wall-clock uptime, not just call count, is what seems to matter (a
# second staleness incident this session hit at 2h26m uptime, well under 25
# runs since the prior restart). Whichever threshold is reached first wins.
set -u
HERE="${HERE:?maybe_restart_gazebo.sh must be sourced after HERE is set}"
SCRATCH="${TMPDIR:-/tmp}"
COUNT_FILE="$SCRATCH/.gz_run_count"
RESTART_EVERY=25
RESTART_AFTER_SECONDS=3600

count=0
[ -f "$COUNT_FILE" ] && count="$(cat "$COUNT_FILE" 2>/dev/null || echo 0)"
case "$count" in ''|*[!0-9]*) count=0 ;; esac   # corrupt/missing counter -> treat as 0, don't crash the run
count=$((count + 1))

server_pid="$(pgrep -f 'gz sim -s' 2>/dev/null | head -1 || true)"
server_uptime_s=0
if [ -n "$server_pid" ]; then
    # `ps -o etimes=` (GNU-style, seconds-only) does NOT exist on macOS/BSD ps - it silently prints
    # its own "unknown keyword" usage text instead of erroring, which the sanitizer below then
    # swallowed as "not numeric" and quietly fell back to 0 EVERY call, on EVERY run, since this
    # script was written (found 2026-09-21: a server left running 1h05m, well past
    # RESTART_AFTER_SECONDS, was never restarted - the run-count leg alone was the only trigger that
    # ever actually fired on this machine). Fixed by using the portable `ps -o etime=` (a
    # [[dd-]hh:]mm:ss STRING, supported on both BSD and GNU ps) and parsing it by hand instead.
    etime_raw="$(ps -o etime= -p "$server_pid" 2>/dev/null | tr -d ' ')"
    if [ -n "$etime_raw" ]; then
        days=0
        rest="$etime_raw"
        case "$rest" in
            *-*) days="${rest%%-*}"; rest="${rest#*-}" ;;
        esac
        h=0
        case "$rest" in
            *:*:*) h="${rest%%:*}"; rest="${rest#*:}" ;;
        esac
        m="${rest%%:*}"
        s="${rest#*:}"
        case "$days$h$m$s" in ''|*[!0-9]*) days=0; h=0; m=0; s=0 ;; esac   # any parse surprise -> 0, don't crash the run
        server_uptime_s=$(( ((10#$days * 24 + 10#$h) * 60 + 10#$m) * 60 + 10#$s ))
    fi
fi

if [ "$count" -ge "$RESTART_EVERY" ] || [ "$server_uptime_s" -ge "$RESTART_AFTER_SECONDS" ]; then
    echo "=== maybe_restart_gazebo: $count runs / ${server_uptime_s}s uptime since last restart - restarting Gazebo fresh ==="

    # Capture the world file the CURRENT server is running, so the restart
    # brings back the same one (interceptor.sdf for wroom/intercept work,
    # possibly quadcopter_ninjapilot.sdf for star/generic-quad work) rather
    # than guessing. Falls back to interceptor.sdf - the world every wroom_*
    # and intercept test in this project actually uses - if nothing was
    # running to inspect (e.g. the very first run of a fresh session).
    WORLD_ARG="$(ps -Ao command 2>/dev/null | grep -m1 'gz sim -s' | grep -oE '[^ ]*\.sdf' || true)"
    if [ -z "$WORLD_ARG" ]; then
        WORLD_ARG="worlds/interceptor.sdf"
    fi

    pkill -f fw_simwroom  >/dev/null 2>&1 || true
    pkill -f fw_simposix  >/dev/null 2>&1 || true
    pkill -f gazebo_bridge.py >/dev/null 2>&1 || true
    pkill -f trail_daemon.py  >/dev/null 2>&1 || true
    pkill -f "gz sim" >/dev/null 2>&1 || true
    for _ in $(seq 1 20); do
        pgrep -f "gz sim" >/dev/null 2>&1 || break
        sleep 0.5
    done

    # Same two env vars run_gazebo_bridge.sh sets, and the same reason: the
    # world's model:// includes and the GUI's WindControl/GpsNoise panels
    # both need them, and a Bash tool call's shell never inherits an export
    # from any earlier call.
    export GZ_SIM_RESOURCE_PATH="$HERE/models${GZ_SIM_RESOURCE_PATH:+:$GZ_SIM_RESOURCE_PATH}"
    export GZ_GUI_PLUGIN_PATH="$HERE/gui_plugins/WindControl/build${GZ_GUI_PLUGIN_PATH:+:$GZ_GUI_PLUGIN_PATH}"

    # NO --headless-rendering (2026-09-23): this flag is the actual root
    # cause of the long-standing frozen-camera bug. On this machine's
    # gz-sim 8.14.0 it produces a real offscreen render context that
    # initializes once and never re-renders on subsequent ticks - frames
    # arrive at the right rate, right size, non-empty, and are accepted by
    # every "did a frame arrive" check, but are byte-for-byte identical
    # forever regardless of vehicle attitude. Proved in isolation with a
    # standalone script (no bridge code, no GUI) that subscribed directly
    # to /interceptor/cam_rgb/image and teleported the model through six
    # very different orientations via /world/quadcopter/set_pose: WITH the
    # flag, 1 unique MD5 across 800 frames through a real roll bank; the
    # exact same test WITHOUT it produced 128 distinct MD5s across 186
    # frames with the mean pixel value tracking each pose change. The
    # MAVProxyUser/MITCheetahSTM31MP1-Claude reference project's own working
    # chase_cam never uses this flag either. An earlier comment here claimed
    # "verified the cameras still publish real frames with it" - true, but
    # that check only confirmed non-emptiness, never dynamism, which is
    # exactly the gap this bug lived in. Checked: dropping it does not open
    # a visible on-screen window on this gz-sim version (no window/Ogre
    # entries in gzserver.log, no gz/gazebo process registered with System
    # Events) - the "OgreWindow" worry that flag was originally added for
    # does not reproduce here.
    ( cd "$HERE" && nohup gz sim -s -r "$WORLD_ARG" > "$SCRATCH/gzserver.log" 2>&1 & )
    sleep 6
    ( cd "$HERE" && nohup gz sim -g > "$SCRATCH/gz_gui.log" 2>&1 & )
    sleep 3

    if ! pgrep -f "gz sim -s" >/dev/null 2>&1; then
        echo "!!! maybe_restart_gazebo: server did not come back up - check $SCRATCH/gzserver.log" >&2
    fi

    count=0
fi

echo "$count" > "$COUNT_FILE"
