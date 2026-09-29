#!/bin/bash
# gcs_shot.sh OUT.png: capture ONLY the NinjaPilotGCS main window by its window id (never a screen region)
S=$(dirname "$0"); ID=$(swift "$S/gcs_winid.swift" 2>/dev/null) || { echo "no GCS window"; exit 1; }
screencapture -x -o -l "$ID" "$1" && echo "captured GCS window id $ID -> $1"
