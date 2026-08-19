#!/bin/bash
# uavo_sync.sh - THE one command to sync the UAVObject set across the
# firmware and the GCS so the "GCS and firmware versions ... do not match"
# warning never appears from a step you forgot.
#
# Run this after ANY edit under shared/uavobjectdefinition/. It:
#   1. regenerates the synthetics on the Mac (the board's generator is a stub)
#   2. rebuilds the GCS object library AND libVersionInfo (the hash lib)
#   3. ships junk-free XML + generated sources to the board
#   4. rebuilds fw_realposix and restarts it
#   5. verifies Mac / board-XML / GCS / running-ELF hashes are ALL equal
#   6. reminds you to RELAUNCH THE GCS - the #1 cause of the warning is a
#      stale RUNNING gcs that predates the rebuild; the binary is fine but
#      the process in memory still carries the old compiled-in hash.
#
# Usage:  osd32mp1/uavo_sync.sh [board-ip]     (default 192.168.0.14)
set -e
REPO="/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja"
GCS="$HOME/NinjaPilot-15.02.ninja/ground/openpilotgcs"     # build symlink
BOARD="${1:-192.168.0.14}"
SSH="ssh -o ConnectTimeout=15 -o HostKeyAlgorithms=+ssh-rsa -o PubkeyAcceptedKeyTypes=+ssh-rsa root@$BOARD"
export DEVELOPER_DIR=/Library/Developer/CommandLineTools
export PATH="/opt/homebrew/Cellar/qt@5/5.15.19/bin:$PATH"

hash_of() {  # hash a uavodefinition dir with the project's own function
  python3 -c "
import importlib.util
s=importlib.util.spec_from_file_location('v','$REPO/make/scripts/version-info.py')
m=importlib.util.module_from_spec(s); s.loader.exec_module(m)
print(m.get_hash_of_dirs('$1', verbose=0, raw=1, n=8))"
}

echo '== 1/6 regenerating synthetics on the Mac =='
( cd "$REPO/ground/uavobject-synthetics" && \
  ../uavobjgenerator/uavobjgenerator ../../shared/uavobjectdefinition ../.. >/dev/null )

echo '== 2/6 rebuilding GCS uavobjects + libVersionInfo (hash) =='
( cd "$GCS/src/plugins/uavobjects" && qmake uavobjects.pro >/dev/null 2>&1 && make -j8 >/dev/null 2>&1 )
( cd "$GCS/src/libs/version_info" && rm -f ../../../openpilotgcs-synthetics/version_info.cpp && make >/dev/null 2>&1 )

echo '== 3/6 shipping junk-free XML + synthetics to the board =='
( cd "$REPO/shared/uavobjectdefinition" && COPYFILE_DISABLE=1 tar czf /tmp/xml.tgz *.xml )
( cd "$REPO/ground/uavobject-synthetics/flight" && COPYFILE_DISABLE=1 tar czf /tmp/synth.tgz *.c *.h Makefile.inc )
scp -qO -o HostKeyAlgorithms=+ssh-rsa -o PubkeyAcceptedKeyTypes=+ssh-rsa /tmp/xml.tgz /tmp/synth.tgz "$REPO/flight/targets/boards/realposix/firmware/UAVObjects.inc" root@$BOARD:/tmp/
$SSH 'cd /usr/local/ninja/src/shared/uavobjectdefinition && tar xzf /tmp/xml.tgz && rm -f ._*; \
      cd /usr/local/ninja/src/build/uavobject-synthetics/flight && tar xzf /tmp/synth.tgz && rm -f ._*; \
      cp /tmp/UAVObjects.inc /usr/local/ninja/src/flight/targets/boards/realposix/firmware/; \
      chown -R build:build /usr/local/ninja/src/shared /usr/local/ninja/src/build/uavobject-synthetics /usr/local/ninja/src/flight/targets'

echo '== 4/6 rebuilding fw_realposix on the board (may take ~15 min) =='
$SSH 'cd /usr/local/ninja/src && systemd-run --wait --pipe --property=User=build --property=WorkingDirectory=/usr/local/ninja/src /usr/bin/make QMAKE=true fw_realposix >/tmp/fwbuild.log 2>&1; tail -1 /tmp/fwbuild.log; systemctl restart ninjapilot; sleep 12; systemctl is-active ninjapilot'

echo '== 5/6 verifying all four hashes are identical =='
MAC=$(hash_of "$REPO/shared/uavobjectdefinition")
BRDH=$($SSH 'cd /usr/local/ninja/src && python3 -c "
import importlib.util
s=importlib.util.spec_from_file_location(\"v\",\"make/scripts/version-info.py\")
m=importlib.util.module_from_spec(s); s.loader.exec_module(m)
print(m.get_hash_of_dirs(\"shared/uavobjectdefinition\", verbose=0, raw=1, n=8))"')
GCSH=$(grep -o '0x[0-9a-f][0-9a-f]' "$REPO/ground/openpilotgcs-synthetics/version_info.cpp" | head -4 | sed 's/0x//' | tr -d '\n')
# the RUNTIME artifact is the compiled dylib, not the .cpp - verify the
# actual bundle libVersionInfo carries the hash STRING (stored as ASCII,
# not raw bytes; searching raw bytes gives a false "absent").
DYLIB=$(find "$GCS/bin/NinjaPilotGCS.app" -name "libVersionInfo.1.0.0.dylib" | head -1)
DYLOK=no
if [ -n "$DYLIB" ] && strings "$DYLIB" | grep -q "^$MAC"; then DYLOK=yes; fi
ELFOK=$($SSH "python3 -c \"
d=open('/usr/local/ninja/src/build/fw_realposix/fw_realposix.elf','rb').read()
b=bytes.fromhex('$MAC')
print('yes' if b in d else 'NO')\"")
echo "  Mac XML     : $MAC"
echo "  Board XML   : $BRDH"
echo "  GCS lib     : $GCSH"
echo "  running ELF embeds Mac hash: $ELFOK"
if [ "$MAC" = "$BRDH" ] && [ "$MAC" = "$GCSH" ] && [ "$ELFOK" = "yes" ] && [ "$DYLOK" = "yes" ]; then
  echo "== 6/6 ALL HASHES MATCH ($MAC) =="
  echo ">>> NOW RELAUNCH THE GCS. The mismatch warning is a stale RUNNING gcs;"
  echo ">>> the rebuilt binary carries the new hash but the process in memory does not."
else
  echo "!! HASH MISMATCH - do NOT ship. Diff the dir contents (ls -A, watch for ._* dotfiles)."
  exit 1
fi
