"""Reset the Gazebo world AND wipe any leftover flight trails.

Every test run goes through this script, so clearing markers here (rather
than only at mission upload) guarantees a clean scene even when the
previous run was killed mid-flight and never got to clear its own trail.
"""
import gz.transport13 as transport
from gz.msgs10.world_control_pb2 import WorldControl
from gz.msgs10.boolean_pb2 import Boolean
from gz.msgs10.marker_pb2 import Marker
from gz.msgs10.empty_pb2 import Empty
from gz.msgs10.marker_v_pb2 import Marker_V

node = transport.Node()

req = WorldControl()
req.reset.all = True
ok, rep = node.request("/world/quadcopter/control", req, WorldControl, Boolean, 5000)
print("reset ok:", ok, "reply:", rep.data if ok else "n/a")

# Wipe every marker namespace present (ours plus any left by ad-hoc probes).
found, lst = node.request("/marker/list", Empty(), Empty, Marker_V, 3000)
namespaces = {m.ns for m in lst.marker} if found else set()
namespaces.add("ninjapilot_trail")
for ns in namespaces:
    d = Marker()
    d.ns = ns
    d.action = Marker.DELETE_ALL
    node.request("/marker", d, Marker, Empty, 500)
found, lst = node.request("/marker/list", Empty(), Empty, Marker_V, 3000)
print("trails cleared: %d marker(s) remaining" % (len(lst.marker) if found else -1))
