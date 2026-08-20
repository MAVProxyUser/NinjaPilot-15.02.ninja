#!/usr/bin/env python3
"""gcs_fuzz.py - crash-hunt the GCS through its QAccessible automation surface.

Launch the GCS with NINJAPILOT_GCS_AUTOMATION=1 first (see SKILLS.md
"Drive the GCS from Python"). Then:  python3 gcs_fuzz.py

It cycles every workspace, walks the accessible tree, enumerates + (safely)
exercises menus, clicks non-destructive buttons, hammers rapid workspace
switching, and sweeps the map zoom across big jumps - every operation
watched for a dropped socket (= crash). It never clicks destructive
controls (Save/Apply/Arm/Connect/Wizard/Calibrate/...) and does not touch
the board. Run the GCS ISOLATED (XDG_CONFIG_HOME=/tmp/x) so it cannot
disturb your real config.

Exit code = number of crashes observed.
"""
import sys, time, collections
sys.path.insert(0, "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/ground/pyuavtalk")
from gcs_client import GcsClient

DESTRUCTIVE = ("save", "apply", "erase", "delete", "wipe", "reboot", "halt",
               "upgrade", "rescue", "start", "calibrate", "wizard", "boot",
               "flash", "arm", "connect", "default", "reset", "quit", "exit")


def safe(name):
    n = (name or "").lower()
    return not any(d in n for d in DESTRUCTIVE)


def main():
    c = GcsClient()
    if not c.connect():
        print("FAIL: no GCS automation port (launch with NINJAPILOT_GCS_AUTOMATION=1)")
        return 99
    crashes = 0
    ws = [w["name"] for w in c.workspaces().get("workspaces", [])]
    print("workspaces:", ws)

    # 1. every workspace + accessible tree
    roles = collections.Counter()
    def walk(n):
        roles[n.get("role", "?")] += 1
        for k in n.get("children", []):
            walk(k)
    for w in ws:
        try:
            c.workspace(w); time.sleep(1.0)
            t = c.tree(depth=14)
            if t.get("ok"):
                walk(t["tree"]); print("  [%s] %d nodes" % (w, t.get("nodes")))
        except ConnectionError as e:
            crashes += 1; print("  *** CRASH on workspace %s: %s" % (w, e)); return crashes
    print("  roles:", dict(roles.most_common(10)))

    # 2. menus
    try:
        for m in c.menus().get("menus", []):
            print("  menu '%s': %d items" % (m["text"], len(m.get("items", []))))
    except ConnectionError as e:
        crashes += 1; print("  *** CRASH on menus: %s" % e)

    # 3. rapid workspace cycling (mode-change race)
    try:
        for i in range(60):
            c.workspace(ws[i % len(ws)]); time.sleep(0.05)
        print("  rapid-cycle x60 OK")
    except ConnectionError as e:
        crashes += 1; print("  *** CRASH on rapid cycle: %s" % e)

    # 4. click safe buttons (stale-path fuzzing exercises odd states)
    try:
        btns = [b for b in c.find(role="button", mx=200).get("hits", []) if safe(b.get("name"))]
        n = 0
        for b in btns[:40]:
            try:
                c.do(b["path"], "Press"); n += 1; time.sleep(0.15)
            except ConnectionError as e:
                crashes += 1; print("  *** CRASH clicking '%s': %s" % (b.get("name"), e)); break
        print("  clicked %d safe buttons" % n)
    except ConnectionError as e:
        crashes += 1; print("  *** CRASH finding buttons: %s" % e)

    # 5. map zoom big-jump sweep (needs a connected board with a home for the
    #    map to render; harmless if not - the slider just may not be present)
    try:
        c.workspace("Flight data"); time.sleep(1.0)
        sl = [s for s in c.find(role="slider", mx=25).get("hits", []) if not s.get("name")]
        if sl:
            path = sl[0]["path"]
            for z in (2, 19, 3, 18, 5, 17, 2, 15, 8, 19, 2, 12, 6, 17, 3):
                c.set(path, str(z)); time.sleep(0.4)
            print("  map zoom big-jump sweep OK")
    except ConnectionError as e:
        crashes += 1; print("  *** CRASH on map zoom: %s" % e)

    print("=== FUZZ DONE, crashes=%d ===" % crashes)
    return crashes


if __name__ == "__main__":
    sys.exit(main())
