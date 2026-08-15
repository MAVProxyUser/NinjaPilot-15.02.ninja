#!/usr/bin/env python3
"""Speak Klipper's MCU protocol far enough to fetch a board's data dictionary.

RUNS ON THE BOARD (the device is /dev/ttyACM0 there).

WHY THIS IS NOT JUST A SERIAL READ
----------------------------------
Klipper firmware is silent until spoken to and has no ASCII mode. Everything
is a length/CRC-framed binary block carrying VLQ-encoded integers, and command
IDs are not fixed - they are assigned per build and published in a zlib
compressed JSON "data dictionary" that the host must download FIRST, using the
one command whose ID is guaranteed constant (`identify` = 1). Until you have
the dictionary you cannot issue any other command, which is exactly why
"open the port and read" returns nothing.

PROTOCOL, as specified by Klipper's docs/Protocol.md and klippy/msgproto.py
(Klipper is GPLv3; this is an independent implementation of the wire format,
not a copy of its source):

  block = [length][sequence][payload...][crc16_hi][crc16_lo][sync 0x7E]
    length   : whole block length, 5..64
    sequence : 0x10 | (seq & 0x0f)
    crc16    : CCITT over block[0 : length-3]
  ints are VLQ, 7 bits/byte, high bit = continue, sign-extended from the
  first byte's 0x60 bits. Strings/buffers are [len][bytes].

  identify(offset, count) -> identify_response(offset, data)
    command id 1, response id 0, both fixed by definition.

usage (on the board):
    ./klipper_probe.py                 # fetch + summarise the dictionary
    ./klipper_probe.py --dump-json out.json
"""
import argparse
import json
import os
import select
import sys
import termios
import time
import zlib

SYNC = 0x7E
MSG_MIN, MSG_MAX = 5, 64
POS_LEN, POS_SEQ = 0, 1
TRAILER_CRC, TRAILER_SYNC = 3, 1
SEQ_MASK, DEST = 0x0F, 0x10


def crc16_ccitt(buf):
    crc = 0xFFFF
    for b in buf:
        b ^= crc & 0xFF
        b ^= (b & 0x0F) << 4
        crc = ((b << 8) | (crc >> 8)) ^ (b >> 4) ^ (b << 3)
    return crc & 0xFFFF


def enc_vlq(out, v):
    """Klipper's signed VLQ. Ranges below mirror the reference encoder."""
    sv = v
    if sv < (3 << 5) and sv >= -(1 << 5):
        pass
    elif sv < (3 << 12) and sv >= -(1 << 12):
        out.append((sv >> 7) & 0x7F | 0x80)
    elif sv < (3 << 19) and sv >= -(1 << 19):
        out.append((sv >> 14) & 0x7F | 0x80)
        out.append((sv >> 7) & 0x7F | 0x80)
    elif sv < (3 << 26) and sv >= -(1 << 26):
        out.append((sv >> 21) & 0x7F | 0x80)
        out.append((sv >> 14) & 0x7F | 0x80)
        out.append((sv >> 7) & 0x7F | 0x80)
    else:
        out.append((sv >> 28) & 0x7F | 0x80)
        out.append((sv >> 21) & 0x7F | 0x80)
        out.append((sv >> 14) & 0x7F | 0x80)
        out.append((sv >> 7) & 0x7F | 0x80)
    out.append(v & 0x7F)


def dec_vlq(s, pos):
    c = s[pos]; pos += 1
    v = c & 0x7F
    if (c & 0x60) == 0x60:          # sign-extend negatives
        v |= -0x20
    while c & 0x80:
        c = s[pos]; pos += 1
        v = (v << 7) | (c & 0x7F)
    return v & 0xFFFFFFFF if v >= 0 else v, pos


class Link:
    def __init__(self, port, baud=250000):
        self.fd = os.open(port, os.O_RDWR | os.O_NOCTTY | os.O_NONBLOCK)
        a = termios.tcgetattr(self.fd)
        spd = getattr(termios, "B%d" % baud, termios.B115200)
        a[4] = a[5] = spd
        a[0] &= ~(termios.IXON | termios.IXOFF | termios.ICRNL)
        a[1] &= ~termios.OPOST
        a[2] = ((a[2] & ~(termios.CSIZE | termios.PARENB | termios.CRTSCTS))
                | termios.CS8 | termios.CLOCAL | termios.CREAD)
        a[3] &= ~(termios.ICANON | termios.ECHO | termios.ISIG)
        termios.tcsetattr(self.fd, termios.TCSANOW, a)
        self.buf = b""
        # A freshly-attached MCU expects sequence 0. Starting at 1 (the
        # intuitive "first message") makes it silently ignore every block,
        # which looks identical to a dead device - that cost a debugging round.
        self.seq = 0

    def close(self):
        os.close(self.fd)

    def sync_flush(self):
        """Align the MCU's block parser before the first real command.

        The MCU discards input until it sees a sync byte, so if its receive
        parser is part-way through a stale/garbage block our first well-formed
        block gets eaten as that block's tail. A run of bare sync bytes is
        inert as a message but guarantees a clean parse boundary.
        """
        os.write(self.fd, bytes([SYNC]) * 16)
        time.sleep(0.3)
        try:
            os.read(self.fd, 4096)
        except OSError:
            pass
        self.buf = b""

    def send(self, payload):
        n = len(payload) + MSG_MIN
        blk = bytearray([n, DEST | (self.seq & SEQ_MASK)])
        blk += payload
        crc = crc16_ccitt(blk)
        blk += bytes([(crc >> 8) & 0xFF, crc & 0xFF, SYNC])
        os.write(self.fd, bytes(blk))

    def _pump(self, timeout):
        r, _, _ = select.select([self.fd], [], [], timeout)
        if r:
            try:
                self.buf += os.read(self.fd, 4096)
            except OSError:
                pass

    def recv(self, timeout=0.5):
        """Return (seq, payload) for the next valid block, else None."""
        end = time.time() + timeout
        while True:
            while len(self.buf) >= MSG_MIN:
                n = self.buf[POS_LEN]
                if n < MSG_MIN or n > MSG_MAX or \
                        (self.buf[POS_SEQ] & ~SEQ_MASK) != DEST:
                    self.buf = self.buf[1:]         # resync
                    continue
                if len(self.buf) < n:
                    break
                blk, rest = self.buf[:n], self.buf[n:]
                crc = (blk[n - TRAILER_CRC] << 8) | blk[n - TRAILER_CRC + 1]
                if blk[n - TRAILER_SYNC] != SYNC or \
                        crc != crc16_ccitt(blk[:n - TRAILER_CRC]):
                    self.buf = self.buf[1:]
                    continue
                self.buf = rest
                return blk[POS_SEQ] & SEQ_MASK, blk[2:n - TRAILER_CRC]
            if time.time() >= end:
                return None
            self._pump(min(0.2, max(0.0, end - time.time())))

    def _request(self, offset, count=40, timeout=0.5):
        """One identify() at the current sequence. Returns bytes, or None."""
        pl = bytearray()
        enc_vlq(pl, 1)              # command id 1 = identify (fixed by spec)
        enc_vlq(pl, offset)
        enc_vlq(pl, count)
        self.send(pl)
        end = time.time() + timeout
        while time.time() < end:
            m = self.recv(max(0.05, end - time.time()))
            if m is None:
                return None
            mseq, payload = m
            self.seq = mseq         # MCU echoes the sequence it wants next
            try:
                mid, p = dec_vlq(payload, 0)
                if mid != 0:        # not identify_response
                    continue
                roff, p = dec_vlq(payload, p)
                if roff != offset:  # stale chunk, keep waiting
                    continue
                dlen = payload[p]
                return bytes(payload[p + 1:p + 1 + dlen])
            except IndexError:
                continue
        return None

    def identify(self, verbose=False):
        """Download the compressed data dictionary via identify (command 1).

        The MCU's expected sequence number PERSISTS across host connections -
        it is whatever the last client left it at, not 0. Guessing wrong means
        every block is silently ignored, which is indistinguishable from a dead
        device. So sweep 0..15 to discover it, then track the value the MCU
        echoes back in each reply.
        """
        self.sync_flush()
        chunk = None
        for s in range(16):
            self.seq = s
            chunk = self._request(0)
            if chunk is not None:
                if verbose:
                    sys.stderr.write(f"  synced at sequence {s}\n")
                break
        if chunk is None:
            raise RuntimeError("no identify_response at any sequence 0..15 "
                               "- is this Klipper firmware?")
        data, offset = chunk, len(chunk)
        while True:
            c = None
            for _ in range(17):     # re-sweep if it ever falls out of step
                c = self._request(offset)
                if c is not None:
                    break
                self.seq = (self.seq + 1) & SEQ_MASK
            if c is None:
                raise RuntimeError(f"stalled at offset {offset} "
                                   f"({len(data)} bytes so far)")
            if not c:               # zero-length chunk = end of dictionary
                return data
            data += c
            offset += len(c)
            if verbose:
                sys.stderr.write(f"\r  identify: {offset} bytes")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", default="/dev/ttyACM0")
    ap.add_argument("--baud", type=int, default=250000)
    ap.add_argument("--dump-json")
    a = ap.parse_args()

    link = Link(a.port, a.baud)
    try:
        raw = link.identify(verbose=True)
    finally:
        link.close()
    sys.stderr.write("\n")

    d = json.loads(zlib.decompress(raw).decode())
    print(f"=== dictionary: {len(raw)} compressed -> {len(json.dumps(d))} bytes ===")
    for k in ("version", "build_versions", "app"):
        if k in d:
            print(f"  {k}: {d[k]}")
    cfg = d.get("config", {})
    for k in ("MCU", "CLOCK_FREQ", "STATS_SUMSQ_BASE", "ADC_MAX", "PWM_MAX",
              "RESERVE_PINS_USB", "BUS_PINS_spi1", "BUS_PINS_spi2"):
        if k in cfg:
            print(f"  config.{k}: {cfg[k]}")

    cmds = sorted(d.get("commands", {}))
    resps = sorted(d.get("responses", {}))
    print(f"\n=== {len(cmds)} commands, {len(resps)} responses ===")

    KEY = ("adxl345", "lis2dw", "lis3dh", "mpu9250", "icm20948",
           "bulk", "spi", "i2c", "sensor", "trsync", "clock", "uptime")
    hits = {k: [c for c in cmds + resps if k in c.lower()] for k in KEY}
    for k in KEY:
        if hits[k]:
            print(f"  {k}:")
            for c in hits[k]:
                print(f"      {c}")

    accel = [k for k in ("adxl345", "lis2dw", "lis3dh", "mpu9250") if hits[k]]
    print("\n=== verdict ===")
    if accel:
        print(f"  accelerometer support present: {', '.join(accel)}")
        print("  -> streaming is implementable: configure the bus, then")
        print("     query_<sensor> and consume the bulk data responses.")
    else:
        print("  NO accelerometer commands in this build. Whatever this")
        print("  firmware is for, it cannot report acceleration as built.")

    if a.dump_json:
        with open(a.dump_json, "w") as f:
            json.dump(d, f, indent=1, sort_keys=True)
        print(f"\n  full dictionary written to {a.dump_json}")


if __name__ == "__main__":
    main()
