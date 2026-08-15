#!/bin/bash
# Write the Octavo Debian v3.0 SD image to a microSD card, safely.
#
# This is the RECOMMENDED bring-up path for this board:
#   - it writes NOTHING to eMMC, so it cannot make the current situation worse
#   - it needs no STM32CubeProgrammer (and therefore no ST account)
#   - it sidesteps Octavo's eMMC deploy tarball, which is currently TRUNCATED
#     on their server (exactly 80 MiB; `xz -t` says "Unexpected end of input")
#
# After writing: set the 3-bit boot switch beside the USB host port to 1,0,1
# (SD card) and power-cycle. Expect the HRTBT LED to blink and an RNDIS
# interface at 192.168.7.1 (login debian / tmppwd).
#
# SAFETY: this script refuses to run unattended. It lists candidate disks and
# makes you type the device name AND the word ERASE. `dd` to the wrong
# /dev/diskN destroys that disk - and this machine has two large SanDisk SSDs
# attached, so the wrong answer here is expensive.
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"
ZIP="$HERE/osd32mp1-red-debian-sdcard-v3.0.zip"
RAW="$HERE/osd32mp1-red-trusted-debian-sdcard-v3.0.raw"

if [ ! -f "$RAW" ]; then
    [ -f "$ZIP" ] || { echo "error: neither the .raw nor the .zip is present in $HERE"; exit 1; }
    echo "Extracting the image (8.6 GB raw, needs ~8.6 GB free)..."
    unzip -o "$ZIP" -d "$HERE"
fi
ls -lh "$RAW"

echo
echo "=== external / removable disks ==="
diskutil list external physical
cat <<'EOT'

Identify your microSD card above by SIZE. It will be a small disk (8-128 GB),
NOT the 1 TB or 2 TB SanDisk SSDs. If you see no small disk, the card or the
reader is not attached - stop and fix that first.
EOT

echo
read -r -p "Target disk (e.g. disk8), or blank to abort: " DEV
[ -n "${DEV:-}" ] || { echo "aborted."; exit 0; }
DEV="${DEV#/dev/}"
[ -b "/dev/$DEV" ] || [ -c "/dev/$DEV" ] || { echo "error: /dev/$DEV does not exist"; exit 1; }

echo
echo "About to COMPLETELY ERASE /dev/$DEV :"
diskutil info "/dev/$DEV" 2>/dev/null | grep -E "Device / Media Name|Disk Size|Removable Media|Protocol" || true
echo
read -r -p "Type ERASE to confirm: " OK
[ "$OK" = "ERASE" ] || { echo "aborted."; exit 0; }

diskutil unmountDisk "/dev/$DEV"
# /dev/rdiskN (raw) is an order of magnitude faster than /dev/diskN on macOS.
echo "Writing... (several minutes; ctrl-T shows progress)"
sudo dd if="$RAW" of="/dev/r$DEV" bs=4m status=progress conv=sync
sync
diskutil eject "/dev/$DEV" || true

cat <<'EOT'

DONE. Next:
  1. Put the card in the board.
  2. Set the 3-bit boot switch to 1,0,1 (SD card).
  3. Power-cycle.
  4. Watch the HRTBT LED - it should blink once Linux is up.
  5. ./detect.sh   -> expect an RNDIS interface and 192.168.7.1 answering
  6. ssh debian@192.168.7.1   (password: tmppwd)
EOT
