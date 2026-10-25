#!/usr/bin/env python3
"""
remoteid_listen - decode ASTM F3411 Remote ID as a receiver would see it.

Listens on UDP :9020 for the beacon vendor element the posix twin emits
(pios_rid_sim.c) and prints every message in the pack. Also decodes a hex
string of the same element (e.g. copied from a sniffer) with --hex.

    python3 remoteid_listen.py                # sim twin, UDP :9020
    python3 remoteid_listen.py --hex DD3AFA0BBC0D01F0190...

On real hardware the receiver is a phone: the OpenDroneID app (Android) or
any F3411 WiFi-beacon scanner; look for SSID RID-xxxxxx.
"""
import argparse
import socket
import struct
import sys

UATYPE = ["None", "Aeroplane", "Helicopter/Multirotor", "Gyroplane", "HybridLift", "Ornithopter",
          "Glider", "Kite", "FreeBalloon", "CaptiveBalloon", "Airship", "FreeFallParachute",
          "Rocket", "TetheredPowered", "GroundObstacle", "Other"]
IDTYPE = ["None", "SerialNumber", "CAARegistrationID", "UTMAssignedUUID", "SpecificSessionID"]
STATUS = ["Undeclared", "Ground", "Airborne", "Emergency", "RemoteIDSystemFailure"]
OPLOC = ["Takeoff", "LiveGNSS", "Fixed"]
HACC = ["Unknown", "10NM", "4NM", "2NM", "1NM", "0.5NM", "0.3NM", "0.1NM", "0.05NM", "30m", "10m", "3m", "1m"]
VACC = ["Unknown", "150m", "45m", "25m", "10m", "3m", "1m"]
SACC = ["Unknown", "10m/s", "3m/s", "1m/s", "0.3m/s"]


def alt(u16):
    return None if u16 == 0 else u16 / 2.0 - 1000.0


def decode_message(m):
    typ, ver = m[0] >> 4, m[0] & 0x0F
    if typ == 0:   # Basic ID
        idt, uat = m[1] >> 4, m[1] & 0x0F
        uid = m[2:22].rstrip(b"\0").decode("ascii", "replace")
        return "BasicID     v%d  IDType=%s UAType=%s UASID='%s'" % (ver, IDTYPE[idt] if idt < len(IDTYPE) else idt,
                                                                    UATYPE[uat] if uat < len(UATYPE) else uat, uid)
    if typ == 1:   # Location/Vector
        st = m[1] >> 4
        flags = m[1] & 0x0F
        ew = (flags >> 0) & 1
        speed_mult = (flags >> 1) & 1
        height_type = (flags >> 2) & 1
        direction = m[2] + (180 if ew else 0)
        sh = m[3]
        speed_h = None if (sh == 255 and speed_mult) else (sh * 0.25 if speed_mult == 0 else sh * 0.75 + 255 * 0.25)
        sv = struct.unpack_from("<b", m, 4)[0]
        speed_v = None if sv * 0.5 >= 63 else sv * 0.5   # 63 m/s is the "unknown" sentinel
        lat, lon = struct.unpack_from("<ii", m, 5)
        alt_baro, alt_geo, height = struct.unpack_from("<HHH", m, 13)
        acc1, acc2 = m[19], m[20]
        ts = struct.unpack_from("<H", m, 21)[0]
        tsacc = m[23] & 0x0F
        pos = "UNKNOWN" if (lat == 0 and lon == 0) else "%.6f,%.6f" % (lat * 1e-7, lon * 1e-7)
        return ("Location    v%d  status=%s pos=%s dir=%s speedH=%s speedV=%s altBaro=%s altGeo=%s height=%s(%s) "
                "hAcc=%s vAcc=%s sAcc=%s ts=%s" % (
                    ver, STATUS[st] if st < len(STATUS) else st, pos,
                    "unknown" if direction > 360 else "%d" % direction,
                    "unknown" if speed_h is None else "%.2f m/s" % speed_h,
                    "unknown" if speed_v is None else "%.1f m/s" % speed_v,
                    alt(alt_baro), alt(alt_geo), alt(height), "aboveGround" if height_type else "aboveTakeoff",
                    HACC[acc1 & 0x0F] if (acc1 & 0x0F) < len(HACC) else acc1 & 0x0F,
                    VACC[acc1 >> 4] if (acc1 >> 4) < len(VACC) else acc1 >> 4,
                    SACC[acc2 & 0x0F] if (acc2 & 0x0F) < len(SACC) else acc2 & 0x0F,
                    "unknown" if ts == 0xFFFF else "%.1fs past the hour" % (ts / 10.0)))
    if typ == 3:   # Self-ID
        return "SelfID      v%d  type=%d '%s'" % (ver, m[1], m[2:25].rstrip(b"\0").decode("ascii", "replace"))
    if typ == 4:   # System
        flags = m[1]
        oploc = flags & 0x03
        cls = (flags >> 2) & 0x07
        olat, olon = struct.unpack_from("<ii", m, 2)
        area_count, area_radius, ceiling, floor = struct.unpack_from("<HBHH", m, 10)
        catclass = m[17]
        op_alt = struct.unpack_from("<H", m, 18)[0]
        ts = struct.unpack_from("<I", m, 20)[0]
        opos = "UNKNOWN" if (olat == 0 and olon == 0) else "%.6f,%.6f" % (olat * 1e-7, olon * 1e-7)
        return ("System      v%d  operatorLoc=%s(%s) class=%d areaCount=%d radius=%dm ceiling=%s floor=%s opAlt=%s "
                "ts=%s" % (ver, OPLOC[oploc] if oploc < 3 else oploc, opos, cls, area_count, area_radius * 10,
                           alt(ceiling), alt(floor), alt(op_alt), "0 (unknown)" if ts == 0 else "%ds since 2019-01-01" % ts))
    if typ == 5:   # Operator ID
        return "OperatorID  v%d  type=%d '%s'" % (ver, m[1], m[2:22].rstrip(b"\0").decode("ascii", "replace"))
    if typ == 2:
        return "Auth        v%d  (not decoded)" % ver
    return "type %d (unknown) %s" % (typ, m.hex())


def decode_element(b):
    """b = vendor element bytes: DD len FA 0B BC 0D counter pack..."""
    if len(b) < 7 or b[0] != 0xDD or b[2:5] != b"\xfa\x0b\xbc" or b[5] != 0x0D:
        return ["not a Remote ID vendor element: %s" % b[:8].hex()]
    counter = b[6]
    pack = b[7:7 + b[1] - 5]
    out = ["vendor element: %d bytes, counter %d" % (len(b), counter)]
    if (pack[0] >> 4) != 0x0F:
        out.append("  single message:")
        out.append("  " + decode_message(pack))
        return out
    size, n = pack[1], pack[2]
    out.append("  MessagePack v%d: %d messages of %d bytes" % (pack[0] & 0x0F, n, size))
    for i in range(n):
        m = pack[3 + i * size: 3 + (i + 1) * size]
        if len(m) == size:
            out.append("  " + decode_message(m))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", type=int, default=9020)
    ap.add_argument("--hex", help="decode this vendor element instead of listening")
    ap.add_argument("--count", type=int, default=0, help="stop after N packs (0 = forever)")
    args = ap.parse_args()
    if args.hex:
        print("\n".join(decode_element(bytes.fromhex(args.hex.replace(" ", "")))))
        return
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind(("127.0.0.1", args.port))
    print("listening on udp:%d for Remote ID beacon elements..." % args.port, flush=True)
    n = 0
    while True:
        data, _ = s.recvfrom(2048)
        n += 1
        print("\n".join(decode_element(data)), flush=True)
        if args.count and n >= args.count:
            break


if __name__ == "__main__":
    main()
