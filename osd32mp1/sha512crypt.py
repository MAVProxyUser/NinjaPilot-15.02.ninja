#!/usr/bin/env python3
"""SHA-512 crypt ($6$), per Ulrich Drepper's specification.

macOS crypt(3) has no $6$ support and LibreSSL's `openssl passwd` has no -6,
so generate it here. Correctness is NOT assumed - main() checks the official
test vector from the spec before the hash is used for anything.
"""
import hashlib, sys

B64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"


def _b64(b, order):
    """Drepper's custom base64.

    b64_from_24bit(B2, B1, B0, n) packs w = B2<<16 | B1<<8 | B0 and then emits
    n chars from the LOW end. So within a group the FIRST index is the most
    significant byte - encoding it as least-significant (the intuitive
    little-endian reading) produces a plausible-looking but wrong hash, which
    is exactly what the spec test vector caught.
    """
    out = []
    for grp in order:
        v = 0
        last = len(grp) - 1
        for i, idx in enumerate(grp):
            v |= b[idx] << (8 * (last - i))
        for _ in range(4 if len(grp) == 3 else len(grp) + 1):
            out.append(B64[v & 0x3F]); v >>= 6
    return "".join(out)


def sha512_crypt(password, salt, rounds=5000):
    pw = password.encode(); sa = salt.encode()[:16]

    B = hashlib.sha512(pw + sa + pw).digest()
    A = hashlib.sha512()
    A.update(pw + sa)
    A.update(B * (len(pw) // 64) + B[:len(pw) % 64])
    n = len(pw)
    while n:
        A.update(B if n & 1 else pw)
        n >>= 1
    A = A.digest()

    DP = hashlib.sha512(pw * len(pw)).digest()
    P = DP * (len(pw) // 64) + DP[:len(pw) % 64]
    DS = hashlib.sha512(sa * (16 + A[0])).digest()
    S = DS * (len(sa) // 64) + DS[:len(sa) % 64]

    C = A
    for i in range(rounds):
        h = hashlib.sha512()
        h.update(P if i & 1 else C)
        if i % 3: h.update(S)
        if i % 7: h.update(P)
        h.update(C if i & 1 else P)
        C = h.digest()

    order = [(0, 21, 42), (22, 43, 1), (44, 2, 23), (3, 24, 45), (25, 46, 4),
             (47, 5, 26), (6, 27, 48), (28, 49, 7), (50, 8, 29), (9, 30, 51),
             (31, 52, 10), (53, 11, 32), (12, 33, 54), (34, 55, 13),
             (56, 14, 35), (15, 36, 57), (37, 58, 16), (59, 17, 38),
             (18, 39, 60), (40, 61, 19), (62, 20, 41), (63,)]
    return f"$6${salt}${_b64(C, order)}"


if __name__ == "__main__":
    # Official test vector from the specification.
    want = ("$6$saltstring$svn8UoSVapNtMuq1ukKS4tPQd8iKwSMHWjl/O817G3uBnIFNjnQJu"
            "esI68u4OTLiBFdcbYEdFCoEOfaS35inz1")
    got = sha512_crypt("Hello world!", "saltstring")
    if got != want:
        print("SELF-TEST FAILED - not using this hash", file=sys.stderr)
        print(f"  want {want}\n  got  {got}", file=sys.stderr)
        sys.exit(1)
    print("self-test: PASS (matches spec test vector)")
    print(sha512_crypt(sys.argv[1], sys.argv[2]))
