#!/usr/bin/env python3
"""Extract / inject a partition by byte offset. Regular files only - no sudo."""
import sys, os
CHUNK = 8 << 20
mode, img, path, off, size = sys.argv[1], sys.argv[2], sys.argv[3], int(sys.argv[4]), int(sys.argv[5])
if mode == "out":
    with open(img, "rb") as s, open(path, "wb") as d:
        s.seek(off); left = size
        while left:
            b = s.read(min(CHUNK, left))
            if not b: break
            d.write(b); left -= len(b)
    print(f"extracted {size} bytes -> {path}")
else:
    assert os.path.getsize(path) == size, f"size mismatch: {os.path.getsize(path)} vs {size}"
    with open(path, "rb") as s, open(img, "r+b") as d:
        d.seek(off)
        while True:
            b = s.read(CHUNK)
            if not b: break
            d.write(b)
        d.flush(); os.fsync(d.fileno())
    print(f"injected {size} bytes <- {path}")
