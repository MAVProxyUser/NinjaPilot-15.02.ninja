#!/usr/bin/env python3
"""Run a command on the OSD32MP1 over the USB serial console and print output.

The edited image gives the ACM function bInterfaceProtocol 0x01, so macOS binds
it natively as /dev/cu.usbmodem* - no libusb, no kext, no network. That makes
this the ONE channel that keeps working when Ethernet, DHCP, sshd or the USB
network are all misconfigured, which is exactly when it is needed.

serial-getty runs with --autologin root, so there is no login prompt to script
around: the port comes up already at a root shell.

usage:
    ./board_cmd.py "ip -brief addr"
    ./board_cmd.py --shell        # dump whatever the console is showing
"""
import glob
import os
import select
import sys
import termios
import time

BAUD = termios.B115200
MARKER = "__BOARD_CMD_DONE__"


def open_console(path=None):
    if path is None:
        path = os.environ.get("BOARD_CMD_DEV")   # e.g. /dev/cu.usbmodem3101 (BRK)
    if path is None:
        cands = sorted(glob.glob("/dev/cu.usbmodem*"))
        if not cands:
            sys.exit("no /dev/cu.usbmodem* - is the board booted with the edited image?\n"
                     "(the stock image's ACM proto is 0xff and macOS will not bind it)")
        if len(cands) > 1:
            sys.stderr.write("[board_cmd] WARNING: multiple boards: %s ; using %s "
                             "(set BOARD_CMD_DEV to choose)\n" % (cands, cands[-1]))
        path = cands[-1]
    fd = os.open(path, os.O_RDWR | os.O_NOCTTY | os.O_NONBLOCK)
    a = termios.tcgetattr(fd)
    a[4] = a[5] = BAUD
    a[0] &= ~(termios.IXON | termios.IXOFF | termios.ICRNL)
    a[1] &= ~termios.OPOST
    a[2] = ((a[2] & ~(termios.CSIZE | termios.PARENB | termios.CRTSCTS))
            | termios.CS8 | termios.CLOCAL | termios.CREAD)
    a[3] &= ~(termios.ICANON | termios.ECHO | termios.ISIG)
    termios.tcsetattr(fd, termios.TCSANOW, a)
    return fd, path


def drain(fd, secs=0.4):
    end = time.time() + secs
    while time.time() < end:
        r, _, _ = select.select([fd], [], [], 0.1)
        if r:
            try:
                os.read(fd, 4096)
            except OSError:
                pass


def run(fd, cmd, timeout=25):
    """Send cmd, read until the marker echoes back. Returns (output, rc)."""
    drain(fd)
    os.write(fd, f"{cmd}; echo {MARKER}$?\n".encode())
    buf = b""
    end = time.time() + timeout
    while time.time() < end:
        r, _, _ = select.select([fd], [], [], 0.3)
        if r:
            try:
                d = os.read(fd, 4096)
            except OSError:
                continue
            if d:
                buf += d
                # The marker appears twice: once as the shell echoes the command
                # line back, once as the actual output. Wait for the second.
                if buf.count(MARKER.encode()) >= 2:
                    break
    text = buf.decode("utf-8", "replace")
    rc = None
    lines, out = text.splitlines(), []
    for ln in lines:
        if MARKER in ln:
            tail = ln.split(MARKER)[-1].strip()
            if tail and tail[0].isdigit():
                rc = int("".join(c for c in tail if c.isdigit()) or 0)
            continue
        if ln.strip().endswith(f"echo {MARKER}$?") or cmd in ln and "echo" in ln:
            continue
        out.append(ln)
    # strip the trailing shell prompt
    while out and out[-1].strip().endswith("#"):
        out.pop()
    return "\n".join(out).strip("\r\n"), rc


def main():
    args = [a for a in sys.argv[1:] if a != "--shell"]
    fd, path = open_console()
    print(f"[board_cmd] {path}", file=sys.stderr)
    try:
        if not args:
            os.write(fd, b"\n")
            time.sleep(1.0)
            drain(fd, 0.1)
            return
        for cmd in args:
            out, rc = run(fd, cmd)
            print(f"$ {cmd}")
            if out:
                print(out)
            print(f"[rc={rc}]")
    finally:
        os.close(fd)


if __name__ == "__main__":
    main()
