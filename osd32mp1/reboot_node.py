#!/usr/bin/env python3
"""Reboot a DroneCAN node via RestartNode, WITHOUT running an allocator.

Used to exercise the in-firmware DNA allocator (pios_sensors_hub.c): after the
reboot the node goes anonymous and must be re-allocated by whatever allocator
is on the bus - which, since 2026-08-20, is fw_realposix itself. This helper
is a plain node (id 126), so it does NOT allocate and cannot mask a broken
firmware allocator.
"""
import sys, time, dronecan
target = int(sys.argv[1]) if len(sys.argv) > 1 else 124
node = dronecan.make_node("can0", node_id=126, bitrate=1000000)
done = {}
node.request(dronecan.uavcan.protocol.RestartNode.Request(magic_number=0xACCE551B1E),
             target, lambda e: done.__setitem__('ok', e is not None))
t = time.time()
while time.time() - t < 3:
    node.spin(0.2)
print("restart request sent to node", target, "resp:", done.get('ok'))
