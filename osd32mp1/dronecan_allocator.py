#!/usr/bin/env python3
"""DroneCAN dynamic node-ID allocation server + live sensor monitor.

RUNS ON THE BOARD (needs SocketCAN and the `dronecan` package).

Why this exists: AP_Periph nodes boot anonymous and broadcast
`uavcan.protocol.dynamic_node_id.Allocation` until something grants them an
ID. Until then they publish NOTHING - no NodeStatus, no GNSS, no sensor data
at all. On an aircraft the flight controller is the allocator; on this bench
there is no flight controller, so the nodes retry forever and the bus looks
"alive but useless". This fills that role.

Allocations are stored in a small database file so a node keeps the same ID
across reboots, which is what you want once anything downstream starts
referring to nodes by number.

usage (on the board):
    ./dronecan_allocator.py                 # 60s, then report
    ./dronecan_allocator.py --seconds 0     # run forever
"""
import argparse
import collections
import sys
import time

import dronecan

DB = "/home/root/dronecan_alloc.db"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iface", default="can0")
    ap.add_argument("--bitrate", type=int, default=1000000)
    ap.add_argument("--node-id", type=int, default=127)
    ap.add_argument("--seconds", type=int, default=60,
                    help="0 = run forever")
    ap.add_argument("--db", default=DB)
    a = ap.parse_args()

    node = dronecan.make_node(a.iface, node_id=a.node_id, bitrate=a.bitrate)
    monitor = dronecan.app.node_monitor.NodeMonitor(node)
    allocator = dronecan.app.dynamic_node_id.CentralizedServer(
        node, monitor, database_storage=a.db)

    seen = collections.defaultdict(collections.Counter)
    latest = {}

    def track(kind):
        def cb(ev):
            nid = ev.transfer.source_node_id
            seen[nid][kind] += 1
            latest[(nid, kind)] = ev.message
        return cb

    # NodeStatus is the "I exist and I am healthy" heartbeat, ~1 Hz.
    node.add_handler(dronecan.uavcan.protocol.NodeStatus, track("NodeStatus"))
    # GNSS is the first real payload we expect, via the GPS on the L431's UART.
    for name, path in (("gnss.Fix2", "uavcan.equipment.gnss.Fix2"),
                       ("gnss.Fix", "uavcan.equipment.gnss.Fix"),
                       ("air_data.StaticPressure",
                        "uavcan.equipment.air_data.StaticPressure"),
                       ("ahrs.MagneticFieldStrength",
                        "uavcan.equipment.ahrs.MagneticFieldStrength"),
                       ("ahrs.RawIMU", "uavcan.equipment.ahrs.RawIMU")):
        try:
            obj = dronecan.TYPENAMES[path]
        except KeyError:
            continue          # not in this dronecan version; skip quietly
        node.add_handler(obj, track(name))

    print(f"[allocator] node {a.node_id} on {a.iface} @ {a.bitrate} bit/s, db={a.db}")
    print("[allocator] granting node IDs; waiting for devices to come up...\n")

    t0 = time.time()
    try:
        while a.seconds == 0 or time.time() - t0 < a.seconds:
            node.spin(1)
    except KeyboardInterrupt:
        pass
    finally:
        try:
            allocator.close()
        except Exception:
            pass

    print(f"\n=== after {int(time.time() - t0)}s ===")
    if not seen:
        print("""  No node ever completed allocation.
  If can_poll.py still shows Allocation frames, the requests are arriving but
  the grant is not being accepted - check that this allocator's own node id
  (127) does not collide, and that the bus still reads ~60 ohm.""")
        return 1

    for nid in sorted(seen):
        entry = monitor.exists(nid) and monitor.get(nid) or None
        name = ""
        if entry is not None and getattr(entry, "info", None) is not None:
            name = f"  {entry.info.name.decode() if isinstance(entry.info.name, bytes) else entry.info.name}"
        print(f"  node {nid}{name}")
        for kind, n in seen[nid].most_common():
            print(f"      {n:5d}  {kind}")
        fix = latest.get((nid, "gnss.Fix2")) or latest.get((nid, "gnss.Fix"))
        if fix is not None:
            try:
                print(f"        lat {fix.latitude_deg_1e8 / 1e8:.7f}  "
                      f"lon {fix.longitude_deg_1e8 / 1e8:.7f}  "
                      f"alt {fix.height_msl_mm / 1000.0:.1f} m  "
                      f"sats {fix.sats_used}")
            except AttributeError:
                pass
    return 0


if __name__ == "__main__":
    sys.exit(main())
