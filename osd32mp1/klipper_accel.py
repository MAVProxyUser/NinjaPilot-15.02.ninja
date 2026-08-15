#!/usr/bin/env python3
"""Stream ADXL345 samples from a KUSBA (Klipper firmware) over USB.

RUNS ON THE BOARD. Builds on klipper_probe.py for the wire layer.

The command IDs are NOT fixed - they are assigned per firmware build and
published in the data dictionary, so everything here is driven by the
dictionary fetched at connect time rather than hardcoded numbers.

Sequence, mirroring what Klipper's host does:
    get_config                      is the MCU already configured?
    allocate_oids count=2
    config_spi oid=0 pin=CS cs_active_high=0
    spi_set_bus oid=0 spi_bus=spi0 mode=3 rate=5000000
    config_adxl345 oid=1 spi_oid=0
    finalize_config crc=<crc32 of the config commands>
    spi_transfer  -> read DEVID (0x00), must be 0xE5
    spi_send      -> POWER_CTL/DATA_FORMAT/BW_RATE/FIFO_CTL init
    query_adxl345 oid=1 clock=... rest_ticks=...
    <- adxl345_data oid sequence data   (5 bytes per sample, packed)

ADXL345 register values and the packed-sample layout follow the ADXL345
datasheet and Klipper's documented format (Klipper is GPLv3; this is an
independent implementation of the same wire behaviour).
"""
import argparse
import importlib.util
import json
import os
import sys
import time
import zlib

_spec = importlib.util.spec_from_file_location(
    "kp", os.path.join(os.path.dirname(os.path.abspath(__file__)),
                       "klipper_probe.py"))
kp = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(kp)

# ---- ADXL345 registers (datasheet) ----
REG_DEVID, DEVID = 0x00, 0xE5
REG_BW_RATE, REG_POWER_CTL, REG_DATA_FORMAT, REG_FIFO_CTL = 0x2C, 0x2D, 0x31, 0x38
REG_MOD_READ, REG_MOD_MULTI = 0x80, 0x40
FIFO_STREAM = 0x90          # stream mode, no trigger
DATA_FORMAT_FULLRES_16G = 0x0B
POWER_CTL_MEASURE = 0x08
RATES = {25: 0x8, 50: 0x9, 100: 0xA, 200: 0xB, 400: 0xC,
         800: 0xD, 1600: 0xE, 3200: 0xF}
# full-resolution mode is 3.9 mg/LSB on every range
SCALE = 0.0039 * 9.80665    # m/s^2 per LSB
BYTES_PER_SAMPLE = 5


class Codec:
    """Encode/decode Klipper messages from the build's data dictionary."""

    def __init__(self, d):
        self.d = d
        self.cmd = {}       # name -> (id, [(argname, type)])
        self.resp = {}      # id -> (name, [(argname, type)])
        for fmt, mid in d.get("commands", {}).items():
            n, a = self._parse(fmt)
            self.cmd[n] = (mid, a)
        for fmt, mid in d.get("responses", {}).items():
            n, a = self._parse(fmt)
            self.resp[mid] = (n, a)
        self.enums = d.get("enumerations", {})

    @staticmethod
    def _parse(fmt):
        parts = fmt.split()
        name, args = parts[0], []
        for p in parts[1:]:
            k, _, t = p.partition("=")
            args.append((k, t))
        return name, args

    def enum(self, kind, key):
        if isinstance(key, int):
            return key
        return self.enums[kind][key]

    def encode(self, name, **kw):
        mid, args = self.cmd[name]
        out = bytearray()
        kp.enc_vlq(out, mid)
        for k, t in args:
            v = kw[k]
            if t in ("%*s", "%.*s"):
                b = bytes(v)
                out.append(len(b))
                out += b
            else:
                kp.enc_vlq(out, int(v))
        return bytes(out)

    def decode_all(self, payload):
        """A block may carry SEVERAL messages back to back, and may carry
        none at all (a bare ack block, payload length 0). Decoding only the
        first message silently drops data; assuming at least one raises
        IndexError on every ack. Walk the whole payload."""
        out, p = [], 0
        while p < len(payload):
            try:
                mid, p = kp.dec_vlq(payload, p)
            except IndexError:
                break
            if mid not in self.resp:
                break               # unknown id: rest of block is unparseable
            name, args = self.resp[mid]
            vals = {}
            try:
                for k, t in args:
                    if t in ("%*s", "%.*s"):
                        n = payload[p]
                        vals[k] = bytes(payload[p + 1:p + 1 + n])
                        p += 1 + n
                    else:
                        v, p = kp.dec_vlq(payload, p)
                        if t == "%hu":
                            v &= 0xFFFF
                        elif t == "%c":
                            v &= 0xFF
                        vals[k] = v
            except IndexError:
                break               # truncated trailing message
            out.append((name, vals))
        return out


class Mcu:
    def __init__(self, port, baud=250000):
        self.link = kp.Link(port, baud)
        raw = self.link.identify()
        self.dict = json.loads(zlib.decompress(raw).decode())
        self.codec = Codec(self.dict)
        self.clock_freq = int(self.dict["config"]["CLOCK_FREQ"])
        self.pending = []

    def close(self):
        self.link.close()

    def send(self, name, **kw):
        self.link.send(self.codec.encode(name, **kw))

    def pump(self, timeout=0.3):
        """Collect any decoded messages that arrived."""
        got = []
        end = time.time() + timeout
        while time.time() < end:
            m = self.link.recv(max(0.02, end - time.time()))
            if m is None:
                break
            seq, payload = m
            self.link.seq = seq
            got += self.codec.decode_all(payload)
        self.pending += got
        return got

    def request(self, name, want, tries=12, **kw):
        """Send a command and wait for a specific response name."""
        for _ in range(tries):
            self.send(name, **kw)
            for _ in range(4):
                for n, v in self.pump(0.25):
                    if n == want:
                        return v
            self.link.seq = (self.link.seq + 1) & kp.SEQ_MASK
        return None


def spi_reg_write(mcu, spi_oid, reg, val):
    mcu.send("spi_send", oid=spi_oid, data=bytes([reg, val]))
    mcu.pump(0.05)


def spi_reg_read(mcu, spi_oid, reg, n=1):
    mod = REG_MOD_READ | (REG_MOD_MULTI if n > 1 else 0)
    r = mcu.request("spi_transfer", "spi_transfer_response",
                    oid=spi_oid, data=bytes([reg | mod] + [0x00] * n))
    return r["response"][1:] if r else None


def decode_samples(data):
    """5 packed bytes -> (x, y, z) in m/s^2. Layout per ADXL345/Klipper."""
    out = []
    for i in range(len(data) // BYTES_PER_SAMPLE):
        xl, yl, zl, xzh, yzh = data[i * 5:(i + 1) * 5]
        if yzh & 0x80:          # firmware flags a lost/invalid sample
            continue
        rx = (xl | ((xzh & 0x1F) << 8)) - ((xzh & 0x10) << 9)
        ry = (yl | ((yzh & 0x1F) << 8)) - ((yzh & 0x10) << 9)
        rz = ((zl | ((xzh & 0xE0) << 3) | ((yzh & 0xE0) << 6))
              - ((yzh & 0x40) << 7))
        out.append((rx * SCALE, ry * SCALE, rz * SCALE))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", default="/dev/ttyACM0")
    ap.add_argument("--rate", type=int, default=800, choices=sorted(RATES))
    ap.add_argument("--seconds", type=float, default=5.0)
    ap.add_argument("--bus", default=None, help="spi0/spi1 (default: autodetect)")
    a = ap.parse_args()

    mcu = Mcu(a.port)
    print(f"  MCU {mcu.dict['config']['MCU']}, clock {mcu.clock_freq} Hz")

    cfg = mcu.request("get_config", "config")
    if cfg is None:
        sys.exit("  no reply to get_config")
    print(f"  get_config: is_config={cfg['is_config']} crc={cfg['crc']} "
          f"is_shutdown={cfg['is_shutdown']}")
    if cfg["is_shutdown"]:
        sys.exit("  MCU is shut down - unplug/replug the KUSBA and retry")

    buses = [a.bus] if a.bus else list(mcu.codec.enums.get("spi_bus", {"spi0": 0}))
    SPI_OID, ACC_OID = 0, 1

    if cfg["is_config"]:
        print("  already configured by a previous run; reusing oids 0/1")
        chosen = buses[0]
    else:
        chosen = None
        for bus in buses:
            cmds = [
                ("allocate_oids", dict(count=2)),
                ("config_spi", dict(oid=SPI_OID,
                                    pin=mcu.codec.enum("pin", "CS"),
                                    cs_active_high=0)),
                ("spi_set_bus", dict(oid=SPI_OID,
                                     spi_bus=mcu.codec.enum("spi_bus", bus),
                                     mode=3, rate=5000000)),
                ("config_adxl345", dict(oid=ACC_OID, spi_oid=SPI_OID)),
            ]
            for n, kw in cmds:
                mcu.send(n, **kw)
                mcu.pump(0.05)
            crc = zlib.crc32(repr(cmds).encode()) & 0xFFFFFFFF
            mcu.send("finalize_config", crc=crc)
            mcu.pump(0.3)

            devid = spi_reg_read(mcu, SPI_OID, REG_DEVID)
            print(f"  bus {bus}: DEVID = "
                  f"{devid.hex() if devid else 'no response'}")
            if devid and devid[0] == DEVID:
                chosen = bus
                break
        if chosen is None:
            sys.exit(f"  ADXL345 not found (expected DEVID 0x{DEVID:02X}). "
                     f"Tried buses: {buses}")
    print(f"  ADXL345 confirmed on {chosen}")

    # --- put the chip into streaming mode ---
    spi_reg_write(mcu, SPI_OID, REG_POWER_CTL, 0x00)
    spi_reg_write(mcu, SPI_OID, REG_DATA_FORMAT, DATA_FORMAT_FULLRES_16G)
    spi_reg_write(mcu, SPI_OID, REG_FIFO_CTL, 0x00)
    spi_reg_write(mcu, SPI_OID, REG_BW_RATE, RATES[a.rate])
    spi_reg_write(mcu, SPI_OID, REG_FIFO_CTL, FIFO_STREAM)
    spi_reg_write(mcu, SPI_OID, REG_POWER_CTL, POWER_CTL_MEASURE)

    clk = mcu.request("get_clock", "clock")
    if clk is None:
        sys.exit("  no clock response")
    start = (clk["clock"] + mcu.clock_freq // 10) & 0xFFFFFFFF
    rest = max(1, int(mcu.clock_freq * 4.0 / a.rate))
    print(f"  starting query: rate={a.rate}Hz rest_ticks={rest}")
    mcu.send("query_adxl345", oid=ACC_OID, clock=start, rest_ticks=rest)

    samples, blocks, end = [], 0, time.time() + a.seconds
    while time.time() < end:
        for n, v in mcu.pump(0.2):
            if n == "adxl345_data":
                blocks += 1
                samples += decode_samples(v["data"])

    mcu.send("query_adxl345", oid=ACC_OID, clock=0, rest_ticks=0)   # stop
    mcu.pump(0.2)
    st = mcu.request("query_adxl345_status", "adxl345_status", oid=ACC_OID)
    mcu.close()

    print(f"\n=== {len(samples)} samples in {blocks} blocks "
          f"over {a.seconds:.0f}s ===")
    if st:
        print(f"  status: fifo={st['fifo']} limit_count={st['limit_count']} "
              f"next_sequence={st['next_sequence']}")
    if not samples:
        print("  no data - chip configured but FIFO produced nothing")
        return 1
    for s in samples[:8]:
        print("   x=% 8.3f  y=% 8.3f  z=% 8.3f  m/s^2" % s)
    n = len(samples)
    mx = sum(s[0] for s in samples) / n
    my = sum(s[1] for s in samples) / n
    mz = sum(s[2] for s in samples) / n
    mag = (mx * mx + my * my + mz * mz) ** 0.5
    print(f"  mean: x={mx:+.3f} y={my:+.3f} z={mz:+.3f}  |a|={mag:.3f} m/s^2"
          f"  ({mag / 9.80665:.3f} g)")
    print(f"  effective rate: {n / a.seconds:.0f} Hz")
    return 0


if __name__ == "__main__":
    sys.exit(main())
