#!/usr/bin/env python3
"""Measure CAN bus load and per-message timing. RUNS ON THE BOARD.

Answers two different questions that are easy to conflate:

  1. BANDWIDTH - how much of the 1 Mbit/s is spent, i.e. how much headroom is
     left for adding sensors.
  2. TIMING QUALITY - at what rate and with what JITTER does each message
     actually arrive, which is what decides whether a navigation filter can use
     it. A high average rate with occasional 200 ms holes is worse for an
     estimator than a lower, even rate.

METHOD NOTE: timestamps come from the KERNEL via SO_TIMESTAMP, not from
time.time() in the read loop. Python's own scheduling jitter on a 2-core
armv7 is easily milliseconds, which is the same order as the jitter being
measured - timing the loop instead of the frame would measure this script.

On-wire bit cost, CAN 2.0B extended (29-bit id):
    SOF 1 + id 11 + SRR 1 + IDE 1 + id 18 + RTR 1 + r1r0 2 + DLC 4
    + data 8*n + CRC 15 + CRCdelim 1 + ACK 2 + EOF 7 + IFS 3
    = 67 + 8n bits before stuffing.
Bit stuffing applies to SOF..CRC (34 + 8n bits) and adds at most
floor((34 + 8n - 1)/4) bits, so both bounds are reported rather than a single
number pretending to a precision the protocol does not have.

usage (on the board):
    ./can_bandwidth.py --seconds 300
"""
import argparse
import collections
import socket
import struct
import sys
import time

CAN_FRAME_FMT = "<IB3x8s"      # can_id, can_dlc, pad, data
CAN_FRAME_SIZE = struct.calcsize(CAN_FRAME_FMT)
SO_TIMESTAMP = 29
CAN_EFF_FLAG = 0x80000000

MSG_TYPES = {341: "NodeStatus",
             1000: "ahrs.Solution",
             1001: "ahrs.MagneticFieldStrength",   # NOT 1002 - that is the "2" variant
             1002: "ahrs.MagneticFieldStrength2",
             1003: "ahrs.RawIMU",
             1028: "gnss.Fix",
             1061: "gnss.Auxiliary",               # DOP values, rides with Fix2
             1063: "gnss.Fix2",
             20003: "ardupilot vendor-specific"}
ANON_TYPES = {1: "dynamic_node_id.Allocation"}


def frame_bits(dlc):
    """(nominal, worst-case-with-stuffing) on-wire bits for an extended frame."""
    nominal = 67 + 8 * dlc
    stuffable = 34 + 8 * dlc
    return nominal, nominal + (stuffable - 1) // 4


def decode(can_id):
    cid = can_id & 0x1FFFFFFF
    node = cid & 0x7F
    service = (cid >> 7) & 1
    if service:
        return node, f"svc {(cid >> 8) & 0xFF}"
    if node == 0:
        t = (cid >> 8) & 0x03
        return 0, ANON_TYPES.get(t, f"anon msg {t}")
    t = (cid >> 8) & 0xFFFF
    return node, MSG_TYPES.get(t, f"msg {t}")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iface", default="can0")
    ap.add_argument("--seconds", type=float, default=300.0)
    ap.add_argument("--bitrate", type=int, default=1000000)
    a = ap.parse_args()

    s = socket.socket(socket.AF_CAN, socket.SOCK_RAW, socket.CAN_RAW)
    s.bind((a.iface,))
    s.setsockopt(socket.SOL_SOCKET, SO_TIMESTAMP, 1)
    s.settimeout(1.0)

    # per (node, kind): arrival timestamps; plus global bit/byte totals
    arrivals = collections.defaultdict(list)
    counts = collections.Counter()
    bits_nom = bits_max = 0
    payload = 0
    first = last = None

    print(f"[can_bandwidth] sampling {a.iface} for {a.seconds:.0f}s "
          f"at {a.bitrate} bit/s ...")
    t_stop = time.time() + a.seconds
    try:
        while time.time() < t_stop:
            try:
                data, anc, _flags, _addr = s.recvmsg(
                    CAN_FRAME_SIZE, socket.CMSG_SPACE(16))
            except socket.timeout:
                continue
            if len(data) < CAN_FRAME_SIZE:
                continue
            ts = None
            for lvl, typ, cdata in anc:
                if lvl == socket.SOL_SOCKET and typ == SO_TIMESTAMP:
                    sec, usec = struct.unpack("@ll", cdata[:16])
                    ts = sec + usec / 1e6
            if ts is None:
                ts = time.time()

            can_id, dlc, blob = struct.unpack(CAN_FRAME_FMT, data)
            n, m = frame_bits(dlc)
            bits_nom += n
            bits_max += m
            payload += dlc
            node, kind = decode(can_id)
            counts[(node, kind)] += 1

            # TIME TRANSFERS, NOT FRAMES. A multi-frame DroneCAN transfer emits
            # its frames back to back (~0.1 ms apart) and then nothing until the
            # next message. Timing raw frames mixes those two populations and
            # reports enormous jitter that is pure artifact - a 5 Hz Fix2 split
            # over 10 frames looks like "50 Hz, sd 59 ms".
            # The tail byte is the last payload byte; bit 7 = start_of_transfer.
            if dlc >= 1:
                tail = blob[dlc - 1]
                if tail & 0x80:                 # start of a new transfer
                    arrivals[(node, kind)].append(ts)
            if first is None:
                first = ts
            last = ts
    except KeyboardInterrupt:
        pass
    s.close()

    if not counts:
        print("  no frames seen")
        return 1
    span = max(1e-6, last - first)
    total = sum(counts.values())

    print(f"\n=== BANDWIDTH over {span:.1f}s ===")
    print(f"  frames            {total}   ({total/span:.1f} frames/s)")
    print(f"  payload           {payload} bytes  ({payload/span/1024:.2f} KiB/s)")
    print(f"  on-wire nominal   {bits_nom/span:8.0f} bit/s  "
          f"= {100.0*bits_nom/span/a.bitrate:5.2f} % of {a.bitrate//1000} kbit")
    print(f"  on-wire w/ stuff  {bits_max/span:8.0f} bit/s  "
          f"= {100.0*bits_max/span/a.bitrate:5.2f} % (worst case)")
    print(f"  headroom          ~{100.0 - 100.0*bits_max/span/a.bitrate:.1f} % "
          f"of the bus is free")

    print(f"\n=== TIMING per TRANSFER (what a filter actually cares about) ===")
    print(f"  {'node/kind':<34} {'msgs':>6} {'Hz':>7} {'mean':>8} {'sd':>7} "
          f"{'max gap':>8} {'fr/msg':>7}")
    rows = []
    for key in sorted(counts, key=lambda k: -counts[k]):
        node, kind = key
        ts = arrivals[key]
        if len(ts) < 3:
            continue
        d = [(ts[i + 1] - ts[i]) * 1000.0 for i in range(len(ts) - 1)]
        mean = sum(d) / len(d)
        sd = (sum((x - mean) ** 2 for x in d) / len(d)) ** 0.5
        label = f"{node if node else 'anon':>4} {kind}"
        fpm = counts[key] / len(ts)
        print(f"  {label:<34} {len(ts):>6} {len(ts)/span:7.2f} "
              f"{mean:7.1f}m {sd:6.1f}m {max(d):7.1f}m {fpm:6.1f}")
        rows.append((label, len(ts) / span, mean, sd, max(d)))

    print(f"\n=== NAVIGATION SUITABILITY ===")
    for label, hz, mean, sd, mx in rows:
        if "NodeStatus" in label or "Allocation" in label or "svc" in label:
            continue
        jit = 100.0 * sd / mean if mean else 0.0
        stall = mx / mean if mean else 0.0
        verdict = "OK"
        notes = []
        if jit > 20:
            notes.append(f"jitter {jit:.0f}% of period")
        if stall > 3:
            notes.append(f"worst gap {stall:.1f}x nominal")
        if notes:
            verdict = "CHECK: " + ", ".join(notes)
        print(f"  {label:<34} {hz:6.2f} Hz  sd {sd:5.1f} ms   {verdict}")
    print("""
  Reading these: an estimator tolerates a LOW rate far better than an uneven
  one, because a known cadence can be modelled and a surprise hole cannot.
  Jitter well under the sample period, and no gap much beyond one period, is
  what makes a source usable for navigation.""")
    return 0


if __name__ == "__main__":
    sys.exit(main())
