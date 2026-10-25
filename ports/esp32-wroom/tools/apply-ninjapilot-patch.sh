#!/usr/bin/env bash
# Apply the flight-tree changes this port needs, to a NinjaPilot checkout.
#
# The port deliberately lives outside that tree, but a HAL port cannot avoid
# touching the architecture dispatch point in pios.h. Everything in the patch
# is additive and guarded on USE_ESP32 or an #ifndef, so existing targets
# (coptercontrol, simposix, realposix) compile to the same code as before.
#
# Usage: tools/apply-ninjapilot-patch.sh [/path/to/NinjaPilot-15.02.ninja]
set -euo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ROOT="${1:-$HERE/../NinjaPilot-15.02.ninja}"
PATCH="$HERE/patches/ninjapilot-shared-changes.patch"

[ -f "$ROOT/flight/pios/pios.h" ] || { echo "not a NinjaPilot checkout: $ROOT" >&2; exit 1; }
cd "$ROOT"
git apply --check "$PATCH"
git apply "$PATCH"
echo "applied to $ROOT"
echo "revert with: tools/revert-ninjapilot-patch.sh \"$ROOT\""
