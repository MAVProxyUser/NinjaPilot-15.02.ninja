"""Persistent DroneCAN dynamic-node-ID allocator. The old script was a
session tool that EXITED after its report - every "allocator died" mystery
was it finishing. This one runs forever under systemd."""
import dronecan
node = dronecan.make_node("can0", node_id=127, bitrate=1000000)
monitor = dronecan.app.node_monitor.NodeMonitor(node)
server = dronecan.app.dynamic_node_id.CentralizedServer(
    node, monitor, database_storage="/home/root/dronecan_alloc.db")
print("allocator up as node 127", flush=True)
while True:
    node.spin(1)
