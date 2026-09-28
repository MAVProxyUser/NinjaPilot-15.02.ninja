#!/bin/bash
# flash.sh <fw_cubepurple.apj> [log]
#
# Flash the Cube through its ArduPilot bootloader: arm the uploader, then
# power-cycle the board's USB hub port so the bootloader's 5 s window opens.
# UPLOADER defaults to the lineage checkout next to this tree; HUB is the
# uhubctl location/port of the Cube (never the port a charger sits on).
# FLASH_REBOOT=iap resets the board through FirmwareIAP instead of a USB
# power cycle (needed when the CAN BEC keeps the Cube powered).
set -u
APJ="$1"; LOG="${2:-/tmp/cube_flash.log}"
HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/../../../../.." && pwd)"
UPLOADER="${UPLOADER:-$ROOT/../lineage/ardupilot/Tools/scripts/uploader.py}"
HUB="${HUB:-8-3}"; HUB_PORT="${HUB_PORT:-1}"
[ -f "$UPLOADER" ] || { echo "uploader.py not found: $UPLOADER (set UPLOADER=)"; exit 1; }
if [ "${FLASH_REBOOT:-usb}" = "iap" ]; then
    # The board is powered from elsewhere too (CAN BEC): reset it through the
    # firmware's IAP command, then start the uploader at once - the bootloader
    # only waits ~5 s, and an uploader that is already probing the running
    # firmware's serial port misses that window.
    python3 "$HERE/iap_reboot.py" || exit 1
    nohup python3 "$UPLOADER" "$APJ" > "$LOG" 2>&1 &
    UP=$!
else
    nohup python3 "$UPLOADER" "$APJ" > "$LOG" 2>&1 &
    UP=$!
    sleep 2
    uhubctl -l "$HUB" -p "$HUB_PORT" -a cycle -d 2 > /dev/null 2>&1
fi
for i in $(seq 1 120); do kill -0 $UP 2>/dev/null || break; sleep 1; done
kill $UP 2>/dev/null
grep -E "Found board|Verif|Error|error|Rebooting" "$LOG" | tail -4
