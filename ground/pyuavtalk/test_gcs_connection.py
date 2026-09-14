#!/usr/bin/env python3
"""Regression tests for the GCS Connections dropdown, driven through the
accessibility automation server (coreplugin/gcsautomation.cpp).

Run:  NINJAPILOT_BOARD_IP=192.168.0.139 python3 test_gcs_connection.py

Needs a board on the LAN advertising itself. Launches its own GCS with
NINJAPILOT_GCS_AUTOMATION=1 and kills it again.

The bug this exists to catch: the firmware advertises only while nobody is
connected, so 30 s after connecting the discovered entry aged out of the
GCS device list, ConnectionManager::updateConnectionList() found the in-use
device missing and called disconnectDevice(), and the GCS dropped the
aircraft mid-session -- then fell back to the manually configured entry and
never reconnected. A test that only checks the first few seconds passes
happily while that happens, which is why HOLD_SECS is past the expiry.
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
BOARD_IP   = os.environ.get("NINJAPILOT_BOARD_IP", "192.168.0.139")
CONNECT_BY = 25.0    # seconds to first show the discovered board
HOLD_SECS  = 75.0    # must outlast the 30 s beacon expiry, twice over


def _combo_value(c):
    """Current text of the Connections combobox.

    Located by NAME rather than by walking every combobox: a role-only walk
    returns the widgets in tree order and this one sits late, so it fell off
    the end of any sane result cap and the test reported it missing when it
    was merely position 80-something. Name search is content-addressed and
    does not care where the toolbar puts it."""
    for query in ("ESP32", "UDP:", "TCP:", "Serial:", "USB"):
        for hit in c.find(name=query, mx=20).get("hits", []):
            if hit.get("role") == "combobox":
                return hit.get("name"), hit.get("path")
    return None, None


def _socket_to_board(pid):
    out = subprocess.run(["lsof", "-nP", "-p", str(pid)],
                         capture_output=True, text=True).stdout
    return any(BOARD_IP + ":9000" in ln for ln in out.splitlines())


def main():
    if not os.path.exists(GCS):
        print("SKIP: no GCS binary at", GCS)
        return 0

    subprocess.run(["pkill", "-9", "-f", "MacOS/NinjaPilotGCS"],
                   capture_output=True)
    time.sleep(3)

    env = dict(os.environ)
    env["NINJAPILOT_GCS_AUTOMATION"] = "1"
    log = open(os.path.join(os.environ.get("TMPDIR", "/tmp"), "gcs_test.log"), "wb")
    proc = subprocess.Popen([GCS], stdout=log, stderr=subprocess.STDOUT,
                            stdin=subprocess.DEVNULL, start_new_session=True,
                            env=env, cwd=os.path.dirname(GCS))
    failures = []
    try:
        c = GcsClient()
        c.connect(retries=120)

        # 1. the discovered board is selected, without anyone clicking
        t0 = time.time()
        selected = None
        while time.time() - t0 < CONNECT_BY:
            val, _ = _combo_value(c)
            if val and "ESP32" in val:
                selected = val
                break
            time.sleep(0.5)
        if selected:
            print("PASS  discovered board selected after %.1fs: %r"
                  % (time.time() - t0, selected))
        else:
            val, _ = _combo_value(c)
            failures.append("never selected the discovered board within %.0fs "
                            "(showing %r)" % (CONNECT_BY, val))

        # 2. ...and it STAYS selected and connected past the beacon expiry
        if selected:
            t1 = time.time()
            while time.time() - t1 < HOLD_SECS:
                val, _ = _combo_value(c)
                if not val or "ESP32" not in val:
                    failures.append("selection reverted to %r after %.1fs"
                                    % (val, time.time() - t1))
                    break
                if not _socket_to_board(proc.pid):
                    failures.append("socket to %s dropped after %.1fs"
                                    % (BOARD_IP, time.time() - t1))
                    break
                time.sleep(2.0)
            else:
                print("PASS  stayed selected and connected for %.0fs "
                      "(past the 30s beacon expiry)" % HOLD_SECS)
    finally:
        subprocess.run(["pkill", "-9", "-f", "MacOS/NinjaPilotGCS"],
                       capture_output=True)

    for f in failures:
        print("FAIL ", f)
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
