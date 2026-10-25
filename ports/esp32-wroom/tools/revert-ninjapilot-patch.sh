#!/usr/bin/env bash
# Remove this port's flight-tree changes again, leaving the checkout clean.
set -euo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ROOT="${1:-$HERE/../NinjaPilot-15.02.ninja}"
PATCH="$HERE/patches/ninjapilot-shared-changes.patch"

[ -f "$ROOT/flight/pios/pios.h" ] || { echo "not a NinjaPilot checkout: $ROOT" >&2; exit 1; }
cd "$ROOT"
git apply -R "$PATCH"
echo "reverted; $ROOT is clean again"
