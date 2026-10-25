#!/usr/bin/env python3
"""
wifi_setup - store, erase, or test the board's WiFi telemetry credentials.

Credentials live in the DEFAULT nvs partition (0x9000), written OFFLINE with
esptool -- deliberately not over UAVTalk, so this also works on a board whose
firmware predates WiFi. The settings partition PIOS_FLASHFS owns is never
touched.

    set    write ssid/password        (board on USB; reboots it)
    erase  remove credentials         = WiFi OFF -- do this before flight
    check  find the board's beacon on the LAN and do a UAVTalk handshake
           over TCP (no USB needed -- that is the whole point)

Usage:
    python3 tools/wifi_setup.py set --ssid NAME --password SECRET
    python3 tools/wifi_setup.py erase
    python3 tools/wifi_setup.py check
"""

import argparse
import os
import glob
import socket
import struct
import subprocess
import sys
import tempfile
import time

IDF = os.path.expanduser("~/esp/esp-idf")
NVS_GEN = os.path.join(IDF, "components/nvs_flash/nvs_partition_generator",
                       "nvs_partition_gen.py")


def idf_python():
    """The generator imports IDF-installed packages, so it must run under
    the espressif python env, not whatever python3 happens to be first in
    PATH -- invoked from a bare shell that was Xcode's, which knows nothing
    of esp_idf_nvs_partition_gen."""
    cands = sorted(glob.glob(os.path.expanduser(
        "~/.espressif/python_env/*/bin/python")))
    return cands[-1] if cands else sys.executable
NVS_OFFSET = "0x9000"
NVS_SIZE = "0x6000"


def autodetect_port():
    """First USB-serial device that looks like a board, or None."""
    for pattern in ("/dev/cu.wchusbserial*", "/dev/cu.usbserial-*", "/dev/ttyUSB*"):
        hits = sorted(glob.glob(pattern))
        if hits:
            return hits[0]
    return None


def esptool(args, port, chip="auto"):
    """Run esptool against `port`.

    chip defaults to "auto" rather than a hardcoded "esp32". The original
    hardcoded it, which silently made this tool ESP32-only: on a LiteWing --
    an ESP32-S3 -- every write ended in "flash write failed" with nothing
    saying the chip was wrong. Detection costs one extra handshake and removes
    a whole class of confusing failure.
    """
    cmd = [idf_python(), "-m", "esptool", "--chip", chip,
           "--port", port, "-b", "115200"] + args
    return subprocess.call(cmd)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("mode", choices=["set", "erase", "check"])
    ap.add_argument("--ssid")
    ap.add_argument("--password", default="")
    ap.add_argument("--serial", default=None,
                    help="serial port; autodetected if omitted")
    ap.add_argument("--chip", default="auto",
                    help="esp32 / esp32s3 / auto (default: auto)")
    args = ap.parse_args()

    if not args.serial:
        args.serial = autodetect_port()
        if not args.serial and args.mode != "check":
            sys.exit("no USB-serial port found; pass --serial explicitly")
        if args.serial:
            print("using %s" % args.serial)

    if args.mode == "set":
        if not args.ssid:
            sys.exit("set needs --ssid")
        if not args.password:
            # Prompted entry sidesteps shell quoting entirely. A password
            # with ! passed in double quotes arrives with a literal
            # backslash (bash keeps \ before !), and the board then offers
            # the wrong password forever -- found the hard way.
            import getpass
            args.password = getpass.getpass("  WiFi password (typed, no "
                                            "shell quoting involved): ")
        with tempfile.TemporaryDirectory() as td:
            csv = os.path.join(td, "wifi.csv")
            bin_ = os.path.join(td, "wifi.bin")
            with open(csv, "w") as f:
                f.write("key,type,encoding,value\n")
                f.write("wifi,namespace,,\n")
                f.write("ssid,data,string,%s\n" % args.ssid)
                f.write("pass,data,string,%s\n" % args.password)
            if subprocess.call([idf_python(), NVS_GEN, "generate",
                                csv, bin_, NVS_SIZE]) != 0:
                sys.exit("nvs image generation failed")
            print("writing credentials to nvs @ %s (board will reboot)..."
                  % NVS_OFFSET)
            if esptool(["write_flash", NVS_OFFSET, bin_], args.serial) != 0:
                sys.exit("flash write failed")
        print("\ndone. On boot the board joins '%s' and moves telemetry to"
              % args.ssid)
        print("TCP :9000. Run '%s check' (no USB needed) to verify."
              % sys.argv[0])
        return 0

    if args.mode == "erase":
        print("erasing credentials (WiFi OFF; telemetry back to UART0)...")
        if esptool(["erase_region", NVS_OFFSET, NVS_SIZE], args.serial) != 0:
            sys.exit("erase failed")
        print("done -- board is flight-clean.")
        return 0

    # ---- check: beacon -> TCP -> UAVTalk handshake ------------------------
    print("listening for the board's beacon on udp:9999 (up to 15s)...")
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(("", 9999))
    s.settimeout(15)
    try:
        data, peer = s.recvfrom(256)
    except socket.timeout:
        sys.exit("no beacon. Board powered? Credentials set? Same LAN?")
    parts = data.decode(errors="replace").split()
    if len(parts) < 3 or parts[0] != "NINJAPILOT":
        sys.exit("unexpected beacon: %r" % data)
    host, port = parts[1], int(parts[2])
    print("found board at %s:%d (beacon from %s)" % (host, port, peer[0]))

    NP = os.environ.get("NINJAPILOT_ROOT", os.path.abspath(
        os.path.join(os.path.dirname(os.path.abspath(__file__)),
                     "..", "..", "NinjaPilot-15.02.ninja")))
    sys.path.insert(0, os.path.join(NP, "ground", "pyuavtalk"))
    import select as _select
    import threading
    import uavtalk
    from uavtalk_client import UAVTalkClient, default_xml_dir

    class TcpTransport(object):
        def __init__(self, host, port):
            self.sock = socket.create_connection((host, port), timeout=5)
            self.sock.setblocking(False)

        def send(self, data):
            try:
                self.sock.sendall(data)
            except (BlockingIOError, OSError):
                pass

        def poll_recv(self, timeout):
            r, _, _ = _select.select([self.sock], [], [], timeout)
            if not r:
                return b""
            try:
                return self.sock.recv(65536)
            except OSError:
                return b""

    db = uavtalk.UAVObjectDB(default_xml_dir())
    c = UAVTalkClient(TcpTransport(host, port), db)
    got = {}
    connected = threading.Event()

    def on_object(objdef, inst_id, decoded):
        got[objdef.name] = decoded

    threading.Thread(target=c.run,
                     kwargs=dict(duration=30, on_object=on_object,
                                 on_connected=connected.set),
                     daemon=True).start()
    if not connected.wait(20):
        sys.exit("TCP connected but UAVTalk handshake failed")
    print("[link] UAVTalk over WiFi is UP")
    end = time.time() + 6
    while time.time() < end and "AttitudeState" not in got:
        c.request_object("AttitudeState")
        time.sleep(0.8)
    at = got.get("AttitudeState")
    if at:
        print("AttitudeState over WiFi: Roll %+.1f Pitch %+.1f Yaw %+.1f"
              % (at.get("Roll", 0), at.get("Pitch", 0), at.get("Yaw", 0)))
    print("\nWiFi telemetry verified end to end.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
