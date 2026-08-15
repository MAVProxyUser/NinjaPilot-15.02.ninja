#!/usr/bin/env python3
"""Parse the GPT of a raw disk image. No privileges needed - it is just a file."""
import struct, sys

img = sys.argv[1]
SEC = 512
with open(img, "rb") as f:
    f.seek(1 * SEC)
    hdr = f.read(92)
    assert hdr[:8] == b"EFI PART", "not a GPT image"
    (_sig, _rev, _hsz, _crc, _r, _mylba, _altlba, first, last,
     _guid1, _guid2, ptlba, npart, psz, _pcrc) = struct.unpack(
        "<8sIII I QQQQ QQ QIII", hdr)
    f.seek(ptlba * SEC)
    raw = f.read(npart * psz)

print(f"{'#':>2}  {'name':<12} {'start_sector':>13} {'sectors':>10} {'offset_bytes':>14} {'size':>10}")
for i in range(npart):
    e = raw[i*psz:(i+1)*psz]
    tguid = e[0:16]
    if tguid == b"\x00" * 16:
        continue
    slba, elba = struct.unpack("<QQ", e[32:48])
    name = e[56:128].decode("utf-16-le").rstrip("\x00")
    nsec = elba - slba + 1
    print(f"{i+1:>2}  {name:<12} {slba:>13} {nsec:>10} {slba*SEC:>14} "
          f"{nsec*SEC/1048576:>9.1f}M")
