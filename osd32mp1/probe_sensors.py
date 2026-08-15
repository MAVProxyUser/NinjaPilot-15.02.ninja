#!/usr/bin/env python3
"""Identify what is actually on an I2C bus. RUNS ON THE BOARD.

An address ACK only proves SOMETHING answered - it does not say what. Every
check here reads an identity register (or, for the MS5611 which has none,
validates the factory PROM CRC), so a positive result means the part is really
there and really talking.

    MPU-9150/6050   0x68/0x69   WHO_AM_I  0x75 == 0x68
    MS5611 (GY-63)  0x76/0x77   PROM 0xA0..0xAE, 4-bit CRC in the last word
    HMC5883L        0x1E        ID_A/B/C 0x0A..0x0C == 'H','4','3'
    QMC5883L        0x0D        (HMC's clone - DIFFERENT part, different regs)

usage (on the board):
    ./probe_sensors.py                # default bus 3 = I2C5 on the RPi header
    ./probe_sensors.py --bus 3 --scan
"""
import argparse
import fcntl
import os
import struct
import sys
import time

I2C_SLAVE = 0x0703


class Bus:
    def __init__(self, n):
        self.fd = os.open(f"/dev/i2c-{n}", os.O_RDWR)
        self.addr = None

    def to(self, addr):
        if addr != self.addr:
            fcntl.ioctl(self.fd, I2C_SLAVE, addr)
            self.addr = addr

    def rd(self, addr, reg, n=1):
        self.to(addr)
        os.write(self.fd, bytes([reg]))
        return os.read(self.fd, n)

    def wr(self, addr, reg, val):
        self.to(addr)
        os.write(self.fd, bytes([reg, val]))

    def cmd(self, addr, c):
        self.to(addr)
        os.write(self.fd, bytes([c]))

    def present(self, addr):
        try:
            self.to(addr)
            os.read(self.fd, 1)
            return True
        except OSError:
            return False

    def close(self):
        os.close(self.fd)


def ms5611_crc4(prom):
    """Datasheet AN520 CRC-4. The CRC lives in the low nibble of word 7."""
    n_rem = 0
    crc_read = prom[7]
    prom = list(prom)
    prom[7] = 0xFF00 & prom[7]
    for cnt in range(16):
        if cnt % 2 == 1:
            n_rem ^= prom[cnt >> 1] & 0x00FF
        else:
            n_rem ^= prom[cnt >> 1] >> 8
        for _ in range(8):
            n_rem = ((n_rem << 1) ^ 0x3000) & 0xFFFF if n_rem & 0x8000 \
                else (n_rem << 1) & 0xFFFF
    n_rem = (n_rem >> 12) & 0x000F
    return n_rem, crc_read & 0x000F


def probe_mpu(bus, addr):
    try:
        who = bus.rd(addr, 0x75)[0]
    except OSError:
        return None
    names = {0x68: "MPU-9150 / MPU-6050", 0x70: "MPU-6500", 0x71: "MPU-9250",
             0x73: "MPU-9255", 0x75: "ICM-20789", 0x47: "ICM-42688-P"}
    if who not in names:
        return f"unknown Invensense WHO_AM_I 0x{who:02X}"
    pwr = bus.rd(addr, 0x6B)[0]
    state = "ASLEEP (write 0x6B=0x01 to wake)" if pwr & 0x40 else "awake"
    return f"{names[who]}  WHO_AM_I=0x{who:02X}  PWR_MGMT_1=0x{pwr:02X} [{state}]"


def probe_bosch(bus, addr):
    """Bosch baros answer with a chip id; the MS5611 has no such register.

    Check this BEFORE the MS5611 PROM test. A BMP388 returns 0x00 for the
    MS5611's PROM addresses, and a CRC-4 over all zeros validates as zero -
    so the PROM test reports a confident, completely wrong "MS5611 CRC OK".
    Ask a question only the real part can answer.
    """
    known = {0x50: "BMP388", 0x60: "BMP390 / BME280", 0x58: "BMP280",
             0x55: "BMP180 / BMP085"}
    for reg in (0x00, 0xD0):                # BMP388 uses 0x00, BMP280 uses 0xD0
        try:
            v = bus.rd(addr, reg)[0]
        except OSError:
            continue
        if v in known:
            return f"{known[v]}  CHIP_ID(0x{reg:02X})=0x{v:02X}"
    return None


def probe_ms5611(bus, addr):
    try:
        bus.cmd(addr, 0x1E)                 # reset
        time.sleep(0.005)
        prom = []
        for i in range(8):
            w = bus.rd(addr, 0xA0 + i * 2, 2)
            prom.append(struct.unpack(">H", w)[0])
    except OSError:
        return None
    # A real MS5611 has non-zero factory coefficients. All zeros means the part
    # simply does not implement these registers - do not let the CRC bless it.
    if not any(prom):
        return None
    calc, read = ms5611_crc4(prom)
    ok = "CRC OK" if calc == read else f"CRC MISMATCH calc={calc} read={read}"
    if calc != read:
        return f"something at 0x{addr:02X} but PROM {ok} - not an MS5611?"
    return (f"MS5611 (GY-63)  PROM {ok}  "
            f"C1..C6 = {prom[1]},{prom[2]},{prom[3]},{prom[4]},{prom[5]},{prom[6]}")


def probe_hmc(bus, addr):
    try:
        ida = bus.rd(addr, 0x0A, 3)
    except OSError:
        return None
    if bytes(ida) == b"H43":
        return "HMC5883L  ID='H43'"
    return f"0x{addr:02X} answered but ID={bytes(ida)!r} (QMC5883L has no such ID)"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--bus", type=int, default=3,
                    help="3 = I2C5 on the RPi header JP20 (the free one)")
    ap.add_argument("--scan", action="store_true", help="also list every ACK")
    a = ap.parse_args()

    try:
        bus = Bus(a.bus)
    except OSError as e:
        sys.exit(f"cannot open /dev/i2c-{a.bus}: {e}")

    print(f"=== identifying parts on /dev/i2c-{a.bus} ===")
    found = 0
    for addr in (0x68, 0x69):
        if bus.present(addr):
            r = probe_mpu(bus, addr)
            if r:
                print(f"  0x{addr:02X}  {r}"); found += 1
    for addr in (0x76, 0x77):
        if bus.present(addr):
            r = probe_bosch(bus, addr) or probe_ms5611(bus, addr)
            if r:
                print(f"  0x{addr:02X}  {r}"); found += 1
            else:
                print(f"  0x{addr:02X}  answered but identified as nothing known"); found += 1
    for addr in (0x1E,):
        if bus.present(addr):
            r = probe_hmc(bus, addr)
            if r:
                print(f"  0x{addr:02X}  {r}"); found += 1
    if not found:
        print("  nothing identified")

    if a.scan:
        print(f"\n=== every address that ACKs on bus {a.bus} ===")
        hits = [x for x in range(0x08, 0x78) if bus.present(x)]
        print("  " + (" ".join(f"0x{x:02X}" for x in hits) if hits else "(none)"))

    print("\n=== what the flight code still needs ===")
    need = {"GyroSensor": "MPU9150 0x68", "BaroSensor": "MS5611 0x76/0x77"}
    for obj, src in need.items():
        print(f"  {obj:<12} <- {src}")
    bus.close()
    return 0


if __name__ == "__main__":
    sys.exit(main())
