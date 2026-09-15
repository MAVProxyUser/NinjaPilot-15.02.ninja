#!/usr/bin/env python3
"""Regression test: the setup wizard must be navigable on a board reached
over the network.

The bug this exists to catch: ControllerPage::isComplete() decided whether a
connection was real by testing the VISIBLE connection name for a "USB:",
"Serial:", "UDP:" or "TCP:" prefix. That prefix is presentation -- it is
shortName() + ": " + displayName -- and an entry whose displayName already
identifies the board is shown without it. A board found by the ESP32 discovery
beacon therefore reads "ESP32 192.168.0.139 (WiFi)", matched none of the four,
and the Next button stayed disabled forever on a page that had correctly
identified both the device and the board type. The wizard could not be
completed at all over WiFi.

Run:  python3 test_gcs_wizard.py
"""
import os
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from gcs_client import GcsClient

GCS = os.environ.get(
    "NINJAPILOT_GCS_BIN",
    "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/build/"
    "openpilotgcs_release/bin/NinjaPilotGCS.app/Contents/MacOS/NinjaPilotGCS")

WIZARD_BUTTON = [1, 0, 2, 0, 0, 1, 0, 1, 1, 2]   # "Vehicle Setup Wizard..."
NEXT   = [0, 1]
CANCEL = [0, 5]
PAGES  = 5     # welcome, firmware, board id, vehicle type, ... -- stop well
               # short of the output-calibration pages, which spin motors


def pressable(c, path):
    """Disabled widgets do not offer a Press action."""
    for hit in c.find(role="button", mx=200).get("hits", []):
        if list(hit.get("path", [])) == list(path):
            return "Press" in (hit.get("actions") or [])
    return False


def main():
    if not os.path.exists(GCS):
        print("SKIP: no GCS binary at", GCS)
        return 0

    # Ask it to quit rather than SIGKILL: a -9 here once left the user's GCS
    # config half-written (scope curves lost, system-health diagram showing
    # "Unknown"). Fall back to a kill only if it will not go.
    subprocess.run(["osascript", "-e", 'quit app "NinjaPilotGCS"'], capture_output=True)
    time.sleep(4)
    subprocess.run(["pkill", "-f", "MacOS/NinjaPilotGCS"], capture_output=True)
    time.sleep(2)
    env = dict(os.environ)
    env["NINJAPILOT_GCS_AUTOMATION"] = "1"
    log = open(os.path.join(os.environ.get("TMPDIR", "/tmp"), "gcs_wizard_test.log"), "wb")
    proc = subprocess.Popen([GCS], stdout=log, stderr=subprocess.STDOUT,
                            stdin=subprocess.DEVNULL, start_new_session=True,
                            env=env, cwd=os.path.dirname(GCS))
    failures = []
    try:
        c = GcsClient()
        c.connect(retries=120)
        time.sleep(10)          # let it discover and connect to the board

        if not c.do(WIZARD_BUTTON, "Press").get("ok"):
            print("FAIL  could not open the setup wizard")
            return 1
        time.sleep(3)

        names = [h.get("name") for h in c.find(role="dialog", mx=5).get("hits", [])]
        if not any("Setup Wizard" in (n or "") for n in names):
            failures.append("wizard dialog did not open (dialogs=%r)" % names)
        else:
            print("PASS  wizard opened")

        for step in range(1, PAGES + 1):
            if not pressable(c, NEXT):
                failures.append("Next disabled at page %d -- the wizard cannot "
                                "be completed on this connection" % step)
                break
            c.do(NEXT, "Press")
            time.sleep(2.5)
        else:
            print("PASS  Next stayed enabled through %d pages" % PAGES)

        c.do(CANCEL, "Press")   # never leave it somewhere that writes settings
    finally:
        subprocess.run(["osascript", "-e", 'quit app "NinjaPilotGCS"'], capture_output=True)
        time.sleep(4)
        subprocess.run(["pkill", "-f", "MacOS/NinjaPilotGCS"], capture_output=True)

    for f in failures:
        print("FAIL ", f)
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
