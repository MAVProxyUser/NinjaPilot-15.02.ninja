#!/usr/bin/env python3
"""Poll the DroneCAN bus on the OSD32MP1 and report which nodes are alive.

Runs candump on the board over ssh and decodes the DroneCAN (UAVCAN v0)
29-bit extended CAN ID, which is enough to answer the only question that
matters early on: is anything actually talking, and who?

    priority          = (id >> 24) & 0x1F
    message type id   = (id >> 8)  & 0xFFFF     (messages only)
    service-not-msg   = (id >> 7)  & 1
    source node id    =  id        & 0x7F        (0 = anonymous)

usage:
    ./can_poll.py                # 6s at 1 Mbit
    ./can_poll.py --seconds 15
    ./can_poll.py --bitrate 500000
    ./can_poll.py --raw          # also print every frame
"""
import argparse
import collections
import re
import subprocess
import sys

HOST = "osd32mp1"

# Only IDs worth naming with confidence. Anything else prints as a raw number
# rather than a guess - a wrong label here would send debugging sideways.
MSG_TYPES = {
    341: "uavcan.protocol.NodeStatus",
    1063: "uavcan.equipment.gnss.Fix2",
}

# Anonymous frames use a DIFFERENT ID layout, and decoding them as normal
# messages yields plausible-looking garbage (it reported "msg 12537" for what
# is actually message type 1). With no source node ID yet, there is no room
# for a 16-bit type, so the field is only 2 bits and bits 10-23 carry a
# discriminator derived from the sender's unique ID:
#
#   normal     bits 8-23 = message type id (16 bits)
#   anonymous  bits 8-9  = message type id (2 bits, so ids 0-3 only)
#              bits 10-23 = discriminator
ANON_MSG_TYPES = {
    1: "uavcan.protocol.dynamic_node_id.Allocation",
}

# candump default format: "  can0  18F00000   [8]  00 11 22 ..."
LINE = re.compile(r"^\s*(\S+)\s+([0-9A-Fa-f]+)\s+\[(\d+)\]\s*(.*)$")


def decode(can_id):
    node = can_id & 0x7F
    service = (can_id >> 7) & 1
    d = {"priority": (can_id >> 24) & 0x1F, "service": service, "node": node,
         "anon": False, "discriminator": None}
    if not service and node == 0:
        d["anon"] = True
        d["msg_type"] = (can_id >> 8) & 0x03
        d["discriminator"] = (can_id >> 10) & 0x3FFF
    else:
        d["msg_type"] = (can_id >> 8) & 0xFFFF
    return d


def label(d):
    if d["service"]:
        return f"svc {d['msg_type']}"
    if d["anon"]:
        return ANON_MSG_TYPES.get(d["msg_type"], f"anon msg {d['msg_type']}")
    return MSG_TYPES.get(d["msg_type"], f"msg {d['msg_type']}")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--seconds", type=int, default=6)
    ap.add_argument("--bitrate", type=int, default=1000000)
    ap.add_argument("--host", default=HOST)
    ap.add_argument("--raw", action="store_true")
    a = ap.parse_args()

    remote = (
        "export PATH=/usr/sbin:/sbin:$PATH; "
        "ip link set can0 down 2>/dev/null; "
        f"ip link set can0 up type can bitrate {a.bitrate} restart-ms 100 || exit 3; "
        f"timeout {a.seconds + 1} candump -T {a.seconds * 1000} can0; "
        "echo '---STATE---'; ip -details link show can0 | grep -oE "
        "'can state [A-Z-]+|berr-counter tx [0-9]+ rx [0-9]+'"
    )
    p = subprocess.run(["ssh", "-o", "BatchMode=yes", a.host, remote],
                       capture_output=True, text=True, timeout=a.seconds + 90)
    if p.returncode == 3:
        sys.exit(f"could not bring can0 up at {a.bitrate}")

    frames, state = [], []
    tail = False
    for ln in p.stdout.splitlines():
        if ln.startswith("---STATE---"):
            tail = True
            continue
        if tail:
            state.append(ln.strip())
            continue
        m = LINE.match(ln)
        if m:
            frames.append((int(m.group(2), 16), m.group(4).strip()))
            if a.raw:
                print("   ", ln.strip())

    print(f"\n=== {len(frames)} frames in {a.seconds}s @ {a.bitrate} bit/s ===")
    for s in state:
        print(f"    {s}")

    if not frames:
        print("""
    NOTHING DECODED. In order of likelihood:
      1. TERMINATION. The board's R48 (120R) is DNP and the Matek '120R'
         jumpers ship open - a bus with zero terminators shows exactly this:
         line activity, no valid frames, rx error counter pinned at 127.
         Need 120R at EACH END; measure ~60R across CANH-CANL, power off.
      2. Bitrate. Try --bitrate 500000 / 250000 / 125000.
      3. CANH/CANL swapped (harmless, but nothing decodes).
    The controller itself is known good if 'ip link set can0 up ... loopback on'
    plus a cansend echoes frames back.""")
        return

    # Anonymous senders all report node 0, so group them by discriminator -
    # that is derived from the unique ID and therefore separates the devices.
    seen = collections.defaultdict(collections.Counter)
    uniq = {}
    for can_id, data in frames:
        d = decode(can_id)
        key = ("anon", d["discriminator"]) if d["anon"] else ("node", d["node"])
        seen[key][label(d)] += 1
        if d["anon"] and d["msg_type"] == 1 and data:
            b = data.split()
            # byte0 = (requested node_id << 1) | first_part_of_unique_id;
            # the rest is unique-ID bytes, minus the trailing tail byte.
            if len(b) > 2:
                uniq.setdefault(d["discriminator"], " ".join(b[1:-1]))

    print(f"\n=== {len(seen)} device(s) seen ===")
    allocating = False
    for kind, ident in sorted(seen, key=str):
        key = (kind, ident)
        if kind == "anon":
            allocating = True
            u = uniq.get(ident)
            print(f"  ANONYMOUS  discriminator 0x{ident:04X}"
                  + (f"   unique-id starts {u}" if u else ""))
        else:
            print(f"  node {ident}")
        for k, n in seen[key].most_common():
            print(f"      {n:5d}  {k}")

    if allocating:
        print("""
    These devices are ALIVE and healthy - they are broadcasting dynamic
    node-ID allocation requests and getting no reply, so they never leave
    the anonymous state and never start publishing sensor data.

    Nothing on this bus is an allocation server. Normally the flight
    controller plays that role. Two ways forward:
      * run an allocator on the board (python 'dronecan' package), or
      * give each Matek node a STATIC node ID in its own parameters.
    Until then you will only ever see Allocation frames.""")


if __name__ == "__main__":
    main()
