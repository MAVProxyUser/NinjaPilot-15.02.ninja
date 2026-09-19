#!/usr/bin/env python3
"""blcrc.py <flashed.apj> [--cycle] [--solve]

Read back the CUBE_MARKS bring-up markers of a Cube Purple that has no
working console: the firmware programs single words to zero at 0x080FFF00
(slot n at +4n), the ArduPilot bootloader's GET_CRC command returns the CRC
of the whole flash bank, and because that CRC is GF(2)-linear the set of
programmed slots can be solved from one number.

--cycle power-cycles the board through uhubctl (HUB/HUB_PORT env, default
8-3 port 1) so the bootloader answers; --solve assumes a complete boot and
solves the fault / reset-cause / watchdog / PC slots exactly.  UPLOADER
env var points at ArduPilot's Tools/scripts/uploader.py (default: the
lineage checkout next to this tree)."""
import sys, glob, time, json, base64, zlib, os, importlib.util, subprocess
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, "..", "..", "..", "..", ".."))
UPL = os.environ.get("UPLOADER", os.path.join(ROOT, "..", "lineage", "ardupilot", "Tools", "scripts", "uploader.py"))
HUB = os.environ.get("HUB", "8-3"); HUB_PORT = os.environ.get("HUB_PORT", "1")
spec = importlib.util.spec_from_file_location("uploader", UPL); U = importlib.util.module_from_spec(spec); spec.loader.exec_module(U)

def crc_upl(data):  # uploader.crc32(data, 0) == ~zlib.crc32(data, 0xffffffff)
    return (~zlib.crc32(data, 0xFFFFFFFF)) & 0xFFFFFFFF
rnd = os.urandom(1024); assert crc_upl(rnd) == U.crc32(rnd, 0), "crc model mismatch"

apj = sys.argv[1]
if "--cycle" in sys.argv:
    subprocess.Popen(["bash", "-c", "sleep 1.5; uhubctl -l %s -p %s -a cycle -d 2 >/dev/null 2>&1" % (HUB, HUB_PORT)])
t0 = time.time(); up = None
while time.time() - t0 < 30 and up is None:
    for port in glob.glob("/dev/tty.usbmodem*"):
        try:
            u = U.uploader(port, 115200, 57600); u.open(); u.identify(); up = u; break
        except Exception as e:
            try: u.close()
            except Exception: pass
            time.sleep(0.2)
    time.sleep(0.2)
if up is None:
    print("no bootloader answered"); sys.exit(1)
up._uploader__send(U.uploader.GET_CRC + U.uploader.EOC)
meas = up._uploader__recv_int(); up._uploader__getSync()
fwmax = up.fw_maxsize
print("bootloader rev %d fw_maxsize 0x%x measured crc 0x%08x" % (up.bl_rev, fwmax, meas))
d = json.load(open(apj)); img = bytearray(zlib.decompress(base64.b64decode(d["image"])))
base = bytes(img) + b"\xff" * (fwmax - len(img))
c0 = crc_upl(base); print("base image crc 0x%08x (%s)" % (c0, "MATCH = no marks" if c0 == meas else "differs -> marks present"))
MARK_OFF = 0x080FFF00 - 0x08004000
contrib = {}
for i in range(64):
    off = MARK_OFF + 4 * i
    v = bytearray(fwmax); v[off:off+4] = b"\xff\xff\xff\xff"
    contrib[i] = crc_upl(bytes(v))
r = meas ^ c0
progress = [22, 23, 24, 25, 0, 1, 5, 6, 14, 15, 7, 8, 9, 10, 11, 12, 13, 20, 21]
pcbits = list(range(40, 59))
def solve(fixed):
    """residual after fixed slots must be an XOR of a subset of pcbits (if fault) -> gaussian elim"""
    res = r
    for s in fixed: res ^= contrib[s]
    # eliminate over pc bit columns
    rows = [(contrib[b], 1 << k) for k, b in enumerate(pcbits)]
    basis = []  # (value, mask) reduced
    for val, m in rows:
        for bv, bm in basis:
            if val ^ bv < val: val ^= bv; m ^= bm
        if val:
            basis.append((val, m)); basis.sort(reverse=True)
    x = res; sel = 0
    for bv, bm in basis:
        if x ^ bv < x: x ^= bv; sel ^= bm
    return (x == 0), sel
sols = []
for k in range(len(progress) + 1):
    for fault in (None, 30, 29):
        for m27 in (False, True):
            for mk in ([], [2], [2, 3], [2, 3, 4]):
                fixed = progress[:k] + mk + ([fault] if fault else []) + ([27] if m27 else [])
                ok, sel = solve(fixed)
                if fault is None and sel:  # no fault -> no pc bits allowed
                    ok = False
                if ok:
                    sols.append((k, fault, m27, sel, mk))
for k, fault, m27, sel, mk in sols:
    pc = 0x08004000 + (sel << 1) if fault else None
    print("CONSISTENT: progress marks %s malloc-marks %s%s%s%s" % (progress[:k], mk, " +fault slot %d" % fault if fault else "", " +mallocfail" if m27 else "", " pc~0x%08x" % pc if pc else ""))
if not sols: print("no consistent decode (unknown marks written?)")
if "--solve" in sys.argv:
    # full boot assumed: known set = all progress marks; solve the remaining bits exactly (GF(2))
    known = [22, 23, 24, 25, 0, 1, 5, 6, 14, 15, 7, 8, 9, 10, 11, 12, 13, 20, 21]
    unknown = [27, 29, 36, 37, 38, 39] + list(range(40, 59)) + list(range(59, 64))
    if "--with30" in sys.argv: unknown = [30] + unknown
    res = r
    for s_ in known: res ^= contrib[s_]
    rows = [(contrib[b], 1 << k) for k, b in enumerate(unknown)]
    basis = []
    for val, m in rows:
        for bv, bm in basis:
            if val ^ bv < val: val ^= bv; m ^= bm
        if val: basis.append((val, m)); basis.sort(reverse=True)
    x = res; sel = 0
    for bv, bm in basis:
        if x ^ bv < x: x ^= bv; sel ^= bm
    print("rank %d of %d unknowns; residual after solve 0x%08x (%s)" % (len(basis), len(unknown), x, "exact" if x == 0 else "INCONSISTENT"))
    setbits = [unknown[k] for k in range(len(unknown)) if sel & (1 << k)]
    names = {27: "malloc-failed", 29: "fault(mem/bus/usage)", 30: "hardfault", 36: "reset:IWDG", 37: "reset:SOFT", 38: "reset:PIN", 39: "reset:POR", 59: "wdg-kicked:ACTUATOR", 60: "wdg-kicked:STABILIZATION", 61: "wdg-kicked:ATTITUDE", 62: "wdg-kicked:MANUAL", 63: "wdg-kicked:SENSORS"}
    print("set slots:", [(b, names.get(b, "pcbit%d" % (b - 40))) for b in setbits])
    pcbits = [b - 40 for b in setbits if 40 <= b < 59]
    if pcbits: print("fault pc ~ 0x%08x" % (0x08004000 + (sum(1 << b for b in pcbits) << 1)))
try: up.close()
except Exception: pass
