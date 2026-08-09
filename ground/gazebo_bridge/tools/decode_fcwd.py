#!/usr/bin/env python3
"""Decode on-'flash' DebugLog slot files (233CDC00.oNN in the firmware CWD)
directly - the fallback when the telemetry pull was interrupted.
argv[1]=fcwd dir, argv[2]=output jsonl"""
import glob, json, os, struct, sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "pyuavtalk"))
import uavtalk
import board_orientation_viz as bov

HDR = struct.Struct("<IIHHHHB")  # FlightTime, ObjectID, Flight, Entry, InstanceID, Size, Type
db = uavtalk.UAVObjectDB(bov.default_xml_dir())

def decode_slot(raw):
    ft, oid, flight, entry, inst, size, typ = HDR.unpack_from(raw, 0)
    data = raw[HDR.size:]
    out = []
    if typ == 1:  # Text
        out.append({"kind": "text", "t_us": ft, "text": data[:size].decode("utf-8", "replace")})
        return out
    def add(oid, inst, ft, payload):
        od = db.by_id.get(oid)
        if od is None or len(payload) < od.size:
            return False
        out.append({"kind": "uavobject", "t_us": ft, "object": od.name,
                    "inst": inst, "data": od.describe(od.unpack(payload))})
        return True
    if not add(oid, inst, ft, data[:size]):
        return out
    off = size
    while off + HDR.size <= len(data):
        ft2, oid2, _f, _e, inst2, size2, typ2 = HDR.unpack_from(data, off)
        if oid2 in (0xFFFFFFFF, 0) or typ2 != 2:
            break
        if not add(oid2, inst2, ft2, data[off + HDR.size: off + HDR.size + size2]):
            break
        off += HDR.size + size2
    return out

recs = []
files = sorted(glob.glob(os.path.join(sys.argv[1], "233CDC*.o*")),
               key=lambda f: int(f.rsplit(".o", 1)[1], 16))
for f in files:
    raw = open(f, "rb").read()
    if len(raw) >= HDR.size:
        # pios_dosfs_logfs.c objectFilename():
        #     prefix = obj_id + (slot / 256) * 16,  suffix = slot & 0xff
        # and obj_id = 0x233CDC00 | flight (pios_debuglog.c). So the
        # prefix's low byte is flight + 16*(slot/256) - NOT the flight.
        # Decoding it as the flight made slot blocks look like separate
        # flights (0, 16, 32, 48) and silently discarded 3/4 of the data.
        base = os.path.basename(f)
        low = int(base.split(".o")[0][-2:], 16)
        flight = low % 16
        for rec in decode_slot(raw):
            rec["flight"] = flight
            recs.append(rec)
# Slots from DIFFERENT FLIGHTS live side by side in the same directory
# (the filename's low byte is the flight number), and merging them produces
# nonsense: one analysis showed corner timestamps of t=11s and t=4270s in
# the same "flight". Keep only the flight with the most records unless one
# is named explicitly as argv[3].
from collections import Counter
if recs:
    want = int(sys.argv[3]) if len(sys.argv) > 3 else Counter(
        r["flight"] for r in recs).most_common(1)[0][0]
    kept = [r for r in recs if r["flight"] == want]
    print("flights present: %s -> keeping flight %d (%d of %d records)"
          % (sorted({r["flight"] for r in recs}), want, len(kept), len(recs)))
    recs = kept
recs.sort(key=lambda r: r["t_us"])
with open(sys.argv[2], "w") as out:
    for r in recs:
        out.write(json.dumps(r) + "\n")
print("decoded %d slot files -> %d records -> %s" % (len(files), len(recs), sys.argv[2]))
