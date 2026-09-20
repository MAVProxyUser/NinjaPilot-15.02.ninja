#!/usr/bin/env bash
#
# Build NinjaPilot Mobile and install it on the USB-attached iPhone using a
# free ("personal team") 7-day provisioning profile.
#
# Prerequisite, one time, and it cannot be scripted because it needs your
# Apple ID password:
#     Xcode -> Settings -> Accounts -> "+" -> Apple ID -> sign in
# That creates the Apple Development certificate this script signs with.
#
# The resulting build expires after 7 days. Re-run this to reinstall.

set -e
cd "$(dirname "$0")/.."

BUNDLE_ID="${BUNDLE_ID:-com.digitalmunition.ninjapilotmobile}"
SYM="${SYM:-$PWD/build}"
export PATH="/opt/homebrew/bin:$PATH"

# --- device -----------------------------------------------------------------
# USB via usbmuxd (ios-deploy) by default. WIFI=1, or no USB phone at all,
# switches to devicectl over the network -- the only way onto a phone whose
# USB port is dead. devicectl needs iOS 17+ and Developer Mode on the phone.
UDID="${UDID:-$(idevice_id -l 2>/dev/null | head -1)}"
WIFI_ID=""
if [ -n "${WIFI:-}" ] || [ -z "$UDID" ]; then
    J=$(mktemp)
    xcrun devicectl list devices --json-output "$J" >/dev/null 2>&1 || true
    WIFI_ID=$(python3 - "$J" <<'PY'
import json, sys
try:
    d = json.load(open(sys.argv[1]))
except Exception:
    sys.exit()
for x in d.get("result", {}).get("devices", []):
    c = x.get("connectionProperties", {})
    if c.get("pairingState") == "paired" and c.get("tunnelState") in ("connected", "disconnected"):
        print(x.get("identifier", "")); break
PY
)
    rm -f "$J"
    if [ -z "$WIFI_ID" ]; then
        echo "No USB iPhone and no paired network device. Plug one in, or pair over Wi-Fi in Xcode." >&2
        exit 1
    fi
    NAME=$(xcrun devicectl device info details --device "$WIFI_ID" 2>/dev/null | grep -o 'name: .*' | head -1 | cut -c7-)
    echo "Device : ${NAME:-$WIFI_ID} (over the network)"
    # The profile must list this device's UDID (00008140-... form), which
    # is what Xcode registers for network-paired devices.
    UDID=$(xcrun devicectl device info details --device "$WIFI_ID" 2>/dev/null | grep -o 'udid: .*' | head -1 | cut -c7-)
else
    NAME=$(ideviceinfo -u "$UDID" -k DeviceName 2>/dev/null || echo "?")
    IOSVER=$(ideviceinfo -u "$UDID" -k ProductVersion 2>/dev/null || echo "?")
    echo "Device : $NAME (iOS $IOSVER)"
fi

# --- signing --------------------------------------------------------------
# Two paths.
#
# MANUAL: if an Apple Development identity and a matching provisioning profile
# are already present, use them directly. This needs no Apple ID signed into
# Xcode on THIS Mac -- import a .p12 and a .mobileprovision from a machine that
# already has them and you are done. The profile must list this phone's UDID.
#
# AUTOMATIC: otherwise fall back to letting Xcode mint them, which does require
# an account and a team.

IDENT=$(security find-identity -v -p codesigning 2>/dev/null \
    | grep "Apple Development" | head -1 | sed -n 's/.*"\(.*\)"/\1/p')

PROFILE=""
for dir in ~/Library/Developer/Xcode/UserData/"Provisioning Profiles" \
           ~/Library/MobileDevice/"Provisioning Profiles"; do
    [ -d "$dir" ] || continue
    for f in "$dir"/*.mobileprovision; do
        [ -e "$f" ] || continue
        # The plist is wrapped in CMS; strip it to read the app ID and devices.
        PLIST=$(security cms -D -i "$f" 2>/dev/null) || continue
        APPID=$(printf '%s' "$PLIST" \
            | plutil -extract Entitlements.application-identifier raw - 2>/dev/null)
        case "$APPID" in
            *".$BUNDLE_ID") ;;
            *) continue ;;
        esac
        printf '%s' "$PLIST" | grep -q "$UDID" || {
            echo "note: profile $(basename "$f") does not list this phone, skipping" >&2
            continue
        }
        PROFILE="$f"
        PROFUUID=$(printf '%s' "$PLIST" | plutil -extract UUID raw - 2>/dev/null)
        break
    done
    [ -n "$PROFILE" ] && break
done

if [ -n "$IDENT" ] && [ -n "$PROFILE" ]; then
    MODE=manual
    echo "Signing: MANUAL"
    echo "  identity : $IDENT"
    echo "  profile  : $(basename "$PROFILE")  ($PROFUUID)"
else
    MODE=automatic
    TEAM="${DEVELOPMENT_TEAM:-}"
    if [ -z "$TEAM" ]; then
        TEAM=$(grep -o 'DEVELOPMENT_TEAM = [A-Z0-9]*;' NinjaPilotMobile.xcodeproj/project.pbxproj 2>/dev/null \
            | head -1 | awk '{print $3}' | tr -d ';')
    fi
    if [ -z "$TEAM" ]; then
        TEAM=$(defaults read com.apple.dt.Xcode IDEProvisioningTeams 2>/dev/null \
            | grep -o '"teamID" = "[^"]*"' | head -1 | cut -d'"' -f4)
    fi
    if [ -z "$TEAM" ]; then
        echo "" >&2
        echo "No signing material and no development team." >&2
        echo "" >&2
        echo "Either (a) copy an Apple Development identity (.p12) and a matching" >&2
        echo ".mobileprovision from a Mac that already has them:" >&2
        echo "    security import theCert.p12 -k ~/Library/Keychains/login.keychain-db" >&2
        echo "    cp the.mobileprovision ~/Library/MobileDevice/'Provisioning Profiles'/" >&2
        echo "  The profile must list UDID $UDID and match $BUNDLE_ID." >&2
        echo "" >&2
        echo "Or (b) pick a team once in Xcode's Signing & Capabilities tab," >&2
        echo "or pass DEVELOPMENT_TEAM=XXXXXXXXXX." >&2
        exit 1
    fi
    echo "Signing: AUTOMATIC (team $TEAM)"
fi
echo "Bundle : $BUNDLE_ID"
echo ""

# --- build ------------------------------------------------------------------
# -target rather than -scheme on purpose: this Xcode's destination resolver
# reports "iOS 26.4 is not installed" even though the SDK is complete and
# compiles, and a target build skips destination resolution entirely.
if [ "$MODE" = manual ]; then
    xcodebuild \
        -project NinjaPilotMobile.xcodeproj \
        -target NinjaPilotMobile \
        -sdk iphoneos \
        -configuration Release \
        ARCHS=arm64 \
        SYMROOT="$SYM" OBJROOT="$SYM/obj" \
        PRODUCT_BUNDLE_IDENTIFIER="$BUNDLE_ID" \
        CODE_SIGN_STYLE=Manual \
        CODE_SIGN_IDENTITY="$IDENT" \
        PROVISIONING_PROFILE_SPECIFIER="$PROFUUID" \
        build
else
    # -target rather than -scheme on purpose: this Xcode's destination resolver
    # reports "iOS 26.4 is not installed" even though the SDK is complete and
    # compiles, and a target build skips destination resolution entirely.
    xcodebuild \
        -project NinjaPilotMobile.xcodeproj \
        -target NinjaPilotMobile \
        -sdk iphoneos \
        -configuration Release \
        ARCHS=arm64 \
        SYMROOT="$SYM" OBJROOT="$SYM/obj" \
        PRODUCT_BUNDLE_IDENTIFIER="$BUNDLE_ID" \
        DEVELOPMENT_TEAM="$TEAM" \
        CODE_SIGN_STYLE=Automatic \
        -allowProvisioningUpdates \
        -allowProvisioningDeviceRegistration \
        build
fi

APP="$SYM/Release-iphoneos/NinjaPilotMobile.app"
[ -d "$APP" ] || { echo "Build produced no .app at $APP" >&2; exit 1; }

echo ""
echo "Signed with:"
codesign -dv "$APP" 2>&1 | grep -E "Authority|TeamIdentifier" || true

# --- install ----------------------------------------------------------------
echo ""
if [ -n "$WIFI_ID" ]; then
    echo "Installing over the network ..."
    xcrun devicectl device install app --device "$WIFI_ID" "$APP" 2>&1 | grep -vE "provisioning paramter|manage create"
    xcrun devicectl device process launch --terminate-existing --device "$WIFI_ID" "$BUNDLE_ID" 2>&1 \
        | grep -vE "provisioning paramter|manage create" | head -3 || true
else
    # devicectl is not an option here: it requires iOS 17+, and this phone is on 16.
    echo "Installing to $NAME ..."
    ios-deploy --id "$UDID" --bundle "$APP" --no-wifi
fi

echo ""
echo "Done. First launch will fail until you trust the developer on the phone:"
echo "  Settings -> General -> VPN & Device Management -> Developer App -> Trust"
