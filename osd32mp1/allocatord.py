"""Persistent DroneCAN dynamic-node-ID allocator. The old script was a
session tool that EXITED after its report - every "allocator died" mystery
was it finishing. This one runs forever under systemd.

KERNEL-FILTERED (2026-08-18): dronecan-python hands EVERY bus frame to the
interpreter - at the sensor firehose's ~1200-1400 fr/s that cost 30-40% of
a core in pure parse-and-discard. The allocator only needs three slivers
of the traffic, so those are selected with SocketCAN CAN_RAW_FILTERs and
the kernel drops everything else before userspace ever wakes:

  1. anonymous frames (source node 0)     - the whole allocation handshake
                                            rides on these
  2. NodeStatus broadcasts (type 341)     - NodeMonitor's liveness table
  3. service frames addressed to node 127 - GetNodeInfo requests TO us
                                            (tooling polls the allocator)
                                            and responses FROM nodes we
                                            query for the uniqueness check

DroneCAN v0 29-bit ID layout - message frames: [28:24]=priority
[23:8]=type [7]=0 [6:0]=source (source 0 = anonymous, where [9:8] is a
2-bit type and [23:10] a discriminator). Service frames: [28:24]=priority
[23:16]=type [15]=request-not-response [14:8]=destination [7]=1
[6:0]=source.
"""
import socket
import struct

import dronecan

CAN_EFF_FLAG = 0x80000000
CAN_RTR_FLAG = 0x40000000
# python 3.8 (this image) lacks the CAN_RAW option constants
SOL_CAN_RAW = getattr(socket, "SOL_CAN_RAW", 101)      # SOL_CAN_BASE + CAN_RAW
CAN_RAW_FILTER = getattr(socket, "CAN_RAW_FILTER", 1)
AF_CAN = getattr(socket, "AF_CAN", 29)

NODE_ID = 127
NODESTATUS_TYPE = 341

FILTERS = [
    # 1. anonymous frames: source == 0, service bit clear (any type/priority)
    (CAN_EFF_FLAG,
     CAN_EFF_FLAG | CAN_RTR_FLAG | 0xFF),
    # 2. NodeStatus broadcasts: type == 341, service bit clear (any source)
    (CAN_EFF_FLAG | (NODESTATUS_TYPE << 8),
     CAN_EFF_FLAG | CAN_RTR_FLAG | (0xFFFF << 8) | 0x80),
    # 3. service frames to us: destination == 127, service bit set.
    #    Requests AND responses - we must keep ANSWERING GetNodeInfo, so
    #    the request bit stays out of the mask.
    (CAN_EFF_FLAG | (NODE_ID << 8) | 0x80,
     CAN_EFF_FLAG | CAN_RTR_FLAG | (0x7F << 8) | 0x80),
]


def install_kernel_filters(root):
    """Find the raw AF_CAN socket(s) inside dronecan's driver stack and
    attach the filter list. Fails OPEN by design: an unfiltered allocator
    is merely hot; a deaf one strands every node at its next power-up."""
    payload = b"".join(struct.pack("=II", fid, fmask) for fid, fmask in FILTERS)
    hits = 0
    seen = set()
    stack = [root]
    while stack:
        obj = stack.pop()
        if id(obj) in seen:
            continue
        seen.add(id(obj))
        if isinstance(obj, socket.socket):
            try:
                if obj.family == AF_CAN:
                    obj.setsockopt(SOL_CAN_RAW, CAN_RAW_FILTER, payload)
                    hits += 1
            except OSError as exc:
                print("filter refused on a socket:", exc, flush=True)
            continue
        if isinstance(obj, dict):
            stack.extend(obj.values())
        elif isinstance(obj, (list, tuple, set, frozenset)):
            stack.extend(obj)
        elif hasattr(obj, "__dict__"):
            stack.extend(vars(obj).values())
    return hits


node = dronecan.make_node("can0", node_id=NODE_ID, bitrate=1000000)
monitor = dronecan.app.node_monitor.NodeMonitor(node)
server = dronecan.app.dynamic_node_id.CentralizedServer(
    node, monitor, database_storage="/home/root/dronecan_alloc.db")

# THE DOCUMENTED dronecan-python TRAP (see can_flash.py / osd32mp1
# CLAUDE.md): a transfer the library cannot decode RAISES out of
# node.spin() and kills the process - Restart=always was silently
# absorbing those deaths. Wrap PER-FRAME (a spin-level try/except drops
# the whole batch, service responses included). Log the offender's CAN
# id, rate-limited, so the malformed traffic is identifiable.
_orig_recv_frame = node._recv_frame
_bad = {"n": 0, "last": 0.0}


def _safe_recv_frame(frame):
    try:
        _orig_recv_frame(frame)
    except Exception as exc:
        import time
        _bad["n"] += 1
        now = time.monotonic()
        if now - _bad["last"] > 5.0:
            _bad["last"] = now
            print("dropped undecodable transfer #%d (can_id=0x%08X): %s"
                  % (_bad["n"], getattr(frame, "id", 0), exc), flush=True)


node._recv_frame = _safe_recv_frame

nfilt = install_kernel_filters(node.can_driver)
print("allocator up as node 127; kernel filters on %d socket(s)" % nfilt,
      flush=True)
if nfilt == 0:
    print("WARNING: no AF_CAN socket found - running UNFILTERED (hot but alive)",
          flush=True)
while True:
    try:
        node.spin(1)
    except Exception as exc:
        # belt over the braces: nothing recoverable may kill the allocator
        print("spin error (continuing):", exc, flush=True)
