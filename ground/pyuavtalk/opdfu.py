#!/usr/bin/env python3
"""opdfu.py - the OpenPilot USB bootloader protocol, in Python (hidapi).

Flashes an .opfw onto any board that runs the OpenPilot bootloader (OPLink
Mini, CopterControl, Revolution class): halt the running firmware into its
bootloader over UAVTalk, upload the image and its 100-byte description,
then jump back to the firmware.  This is the GCS uploader's op_dfu protocol,
nothing more, so the GCS keeps working on whatever this flashes.

  opdfu.py list                               every OpenPilot USB device (+FW / +BL)
  opdfu.py info    [--serial 51FF...]         bootloader capabilities (board id, size, CRC)
  opdfu.py flash   IMAGE.opfw [--serial ..]   halt -> upload -> describe -> jump (+ verify CRC)
  opdfu.py halt    [--serial ..]              firmware -> bootloader (IAP 1122 / 2233 / 3344)
  opdfu.py jump    [--serial ..]              bootloader -> firmware
  opdfu.py rescue  IMAGE.opfw                 plug the board in while this waits: the
                                              bootloader gives 6 s before it boots the app

One HID holder at a time: quit the GCS (or Disconnect) before using this.

Wire format (64-byte HID reports, id 2 out / id 1 in):
  [id][cmd][count: 4 bytes BE][data0..]       data words go out byte-reversed
  commands: 1 Req_Capabilities  3 EnterDFU  4 JumpFW  5 Reset  7 Upload (|0x20 = start)
            8 Op_END  11 Status_Request  -> 2 Rep_Capabilities / 12 Status_Rep
  status:   1 uploading  5 Last_operation_Success  11 CRC_Fail  (see STATUS)
"""
import argparse, os, struct, sys, time
import hid

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

VID = 0x20A0
REPORT_OUT, REPORT_IN = 2, 1

CMD = dict(Req_Capabilities=1, Rep_Capabilities=2, EnterDFU=3, JumpFW=4, Reset=5,
           Abort_Operation=6, Upload=7, Op_END=8, Download_Req=9, Download=10,
           Status_Request=11, Status_Rep=12)
STATUS = ["DFUidle", "uploading", "wrong_packet_received", "too_many_packets",
          "too_few_packets", "Last_operation_Success", "downloading", "idle",
          "Last_operation_failed", "uploadingStarting", "outsideDevCapabilities",
          "CRC_Fail", "failed_jump", "abort"]
TRANSFER_FW, TRANSFER_DESC = 0, 1
DESC_LEN = 100

BOARD_NAMES = {0x03: "OPLinkMini", 0x04: "CopterControl", 0x09: "Revolution", 0x0C: "CubePurple"}


# ----------------------------------------------------------------------------- USB
def enumerate_boards(serial=None, suffix=None):
    """OpenPilot-vendor HID interfaces, newest first. suffix '+FW' or '+BL'."""
    out, seen = [], set()
    for d in hid.enumerate(VID, 0):
        sn = d["serial_number"] or ""
        if suffix and not sn.endswith(suffix):
            continue
        if serial and not sn.startswith(serial):
            continue
        if sn in seen:
            continue  # macOS lists one entry per HID collection; one open per board
        seen.add(sn)
        out.append(d)
    return out


def wait_for(suffix, serial=None, timeout=20.0, gone_first=False):
    """Wait for a +BL / +FW interface to appear (optionally after it disappears)."""
    t0 = time.time()
    if gone_first:
        while time.time() - t0 < timeout and enumerate_boards(serial, suffix):
            time.sleep(0.1)
    while time.time() - t0 < timeout:
        devs = enumerate_boards(serial, suffix)
        if devs:
            return devs[0]
        time.sleep(0.1)
    return None


class RawHid(object):
    def __init__(self, info):
        self.info = info
        self.h = hid.device()
        self.h.open_path(info["path"])
        self.h.set_nonblocking(False)

    def close(self):
        try:
            self.h.close()
        except Exception:
            pass

    def write(self, payload):
        """payload = up to 63 bytes following the report id."""
        buf = bytes([REPORT_OUT]) + bytes(payload)
        buf = buf + b"\0" * (64 - len(buf))
        return self.h.write(buf)

    def read(self, timeout):
        r = self.h.read(64, max(1, int(timeout * 1000)))
        return bytes(r) if r else b""


# ----------------------------------------------------------------------------- CRC
_TABLE = [0x00000000, 0x04C11DB7, 0x09823B6E, 0x0D4326D9, 0x130476DC, 0x17C56B6B, 0x1A864DB2, 0x1E475005,
          0x2608EDB8, 0x22C9F00F, 0x2F8AD6D6, 0x2B4BCB61, 0x350C9B64, 0x31CD86D3, 0x3C8EA00A, 0x384FBDBD]


def stm32_crc(data, size):
    """The bootloader's CRC: STM32 hardware CRC (poly 0x04C11DB7, init 0xFFFFFFFF)
    over little-endian 32-bit words, image padded with 0xFF to the full bank."""
    data = bytes(data) + b"\xff" * (size - len(data))
    crc = 0xFFFFFFFF
    for (w,) in struct.iter_unpack("<I", data[:size - size % 4]):
        crc ^= w
        for _ in range(8):
            crc = ((crc << 4) & 0xFFFFFFFF) ^ _TABLE[crc >> 28]
    return crc


# ----------------------------------------------------------------------------- DFU
class Device(object):
    def __init__(self, idx, id_, bl_version, size_of_desc, fw_crc, size_of_code, readable, writable):
        self.index, self.id, self.bl_version = idx, id_, bl_version
        self.size_of_desc, self.fw_crc, self.size_of_code = size_of_desc, fw_crc, size_of_code
        self.readable, self.writable = readable, writable

    def __str__(self):
        name = BOARD_NAMES.get(self.id >> 8, "board 0x%02X" % (self.id >> 8))
        return ("%s rev %d  bootloader v%d  code bank %d bytes  desc %d  fw CRC 0x%08X  %s%s"
                % (name, self.id & 0xFF, self.bl_version, self.size_of_code, self.size_of_desc,
                   self.fw_crc, "R" if self.readable else "-", "W" if self.writable else "-"))


class OpDfu(object):
    def __init__(self, hid_dev, verbose=True):
        self.hid = hid_dev
        self.verbose = verbose
        self.devices = []

    def log(self, msg):
        if self.verbose:
            print(msg, flush=True)

    @staticmethod
    def _pkt(cmd, count=0, data=b""):
        return bytes([cmd]) + struct.pack(">I", count) + bytes(data)

    def _cmd(self, cmd, count=0, data=b""):
        self.hid.write(self._pkt(cmd, count, data))

    def _reply(self, expect, timeout=15.0):
        t0 = time.time()
        while time.time() - t0 < timeout:
            r = self.hid.read(timeout - (time.time() - t0))
            if len(r) >= 2 and r[1] == expect:
                return r
        raise RuntimeError("no reply (expected command %d)" % expect)

    # protocol -----------------------------------------------------------------
    def enter_dfu(self, dev=0, tries=12):
        """BLidle -> DFUidle, the way the GCS rescue does it.

        A freshly powered bootloader has an empty device table (numberOfDevices
        is 0 until Req_Capabilities runs OPDfuIni), and in BLidle it only accepts
        EnterDFU for a device index below that count: so a bare EnterDFU is
        silently ignored.  Abort_Operation moves it to DFUidle unconditionally,
        Req_Capabilities fills the table, then EnterDFU selects device 0."""
        for _ in range(tries):
            self._cmd(CMD["Abort_Operation"])
            time.sleep(0.05)
            self._cmd(CMD["Req_Capabilities"])
            try:
                self._reply(CMD["Rep_Capabilities"], timeout=1.0)
            except RuntimeError:
                continue
            self._cmd(CMD["EnterDFU"], 0, bytes([dev, 1, 1, 1]))
            time.sleep(0.15)
            try:
                st = self.status(timeout=1.0)
            except RuntimeError:
                continue
            if st != "idle":
                return st
        raise RuntimeError("bootloader stayed in BLidle after %d attempts" % tries)

    def status(self, timeout=15.0):
        self._cmd(CMD["Status_Request"])
        r = self._reply(CMD["Status_Rep"], timeout)
        s = r[6]
        return STATUS[s] if s < len(STATUS) else "status %d" % s

    def capabilities(self):
        self._cmd(CMD["Req_Capabilities"])
        r = self._reply(CMD["Rep_Capabilities"])
        n = r[7]
        rw = (r[8] << 8) | r[9]
        self.devices = []
        for x in range(n):
            self._cmd(CMD["Req_Capabilities"], 0, bytes([x + 1]))
            r = self._reply(CMD["Rep_Capabilities"])
            self.devices.append(Device(
                x, (r[14] << 8) | r[15], r[7], r[8], struct.unpack(">I", r[10:14])[0],
                struct.unpack(">I", r[2:6])[0], bool(rw >> (2 * x) & 1), bool(rw >> (2 * x + 1) & 1)))
        return self.devices

    def _start_upload(self, nbytes, kind, crc):
        packets, rem = divmod(nbytes // 4, 14)
        last = 14 if rem == 0 else rem
        if rem:
            packets += 1
        self._cmd(CMD["Upload"] | 0x20, packets, bytes([kind, last]) + struct.pack(">I", crc))
        time.sleep(1.0)

    def _upload_data(self, data):
        words = len(data) // 4
        packets = (words + 13) // 14
        t0 = time.time()
        last_pct = -1
        for p in range(packets):
            chunk = data[p * 56:(p + 1) * 56]
            # each 32-bit word goes out byte-reversed (the GCS's CopyWords)
            swapped = b"".join(chunk[i:i + 4][::-1] for i in range(0, len(chunk), 4))
            self._cmd(CMD["Upload"], p, swapped)
            pct = (p + 1) * 100 // packets
            if self.verbose and pct // 10 != last_pct // 10:
                print("\r  uploading %3d%% (%d/%d packets, %.1fs)" % (pct, p + 1, packets, time.time() - t0),
                      end="", flush=True)
                last_pct = pct
        if self.verbose:
            print()

    def _end(self):
        self._cmd(CMD["Op_END"])

    def upload(self, data, kind, crc=0, what="firmware"):
        if len(data) % 4:
            data = bytes(data) + (b"\xff" if kind == TRANSFER_FW else b" ") * (4 - len(data) % 4)
        self.log("  %s: %d bytes%s" % (what, len(data), ("  CRC 0x%08X" % crc) if kind == TRANSFER_FW else ""))
        self._start_upload(len(data), kind, crc)
        if kind == TRANSFER_FW:
            # the bank erase runs inside the bootloader's command handler
            for _ in range(3):
                st = self.status(timeout=20.0)
                if st == "uploading":
                    break
                self.log("  erase status: %s" % st)
            else:
                raise RuntimeError("bootloader never entered 'uploading' (%s)" % st)
        self._upload_data(data)
        self._end()
        st = self.status()
        if st != "Last_operation_Success":
            raise RuntimeError("%s upload failed: %s" % (what, st))
        self.log("  %s: %s" % (what, st))
        return data

    def jump(self, safeboot=False, erase_settings=False):
        data = bytes([0, 0]) + (b"\x5a\xfe" if safeboot else b"\0\0")
        if erase_settings:
            data += bytes([0x00, 0x00, 0xFA, 0x5F, 0x00, 0x00, 0x00, 0x01, 0, 0, 0, 0])
        self._cmd(CMD["JumpFW"], 0, data)

    def reset(self):
        self._cmd(CMD["Reset"])


# ----------------------------------------------------------------------------- .opfw
def parse_opfw(path):
    blob = open(path, "rb").read()
    if len(blob) <= DESC_LEN:
        raise SystemExit("%s: too small for an .opfw" % path)
    desc = blob[-DESC_LEN:]
    if desc[:4] != b"OpFw":
        raise SystemExit("%s: no 'OpFw' description at the end of the file" % path)
    info = dict(board_type=desc[12], board_rev=desc[13],
                tag=desc[14:40].split(b"\0")[0].decode("ascii", "replace"),
                fw_hash=desc[40:60].hex(), uavo_hash=desc[60:80].hex(),
                timestamp=struct.unpack("<I", desc[8:12])[0])
    return blob, desc, info


# ----------------------------------------------------------------------------- UAVTalk over HID
class HidUavtalkTransport(object):
    """UAVTalk over the firmware's HID interface: 64-byte reports, id 2 out / 1 in,
    byte 1 = payload length."""

    def __init__(self, raw):
        self.raw = raw

    def send(self, data):
        for i in range(0, len(data), 62):
            chunk = data[i:i + 62]
            self.raw.write(bytes([len(chunk)]) + chunk)

    def poll_recv(self, timeout):
        r = self.raw.read(timeout)
        if len(r) < 2:
            return b""
        return r[2:2 + r[1]]


def open_uavtalk(serial=None, wait=10.0):
    """(client, raw, info) for the first +FW board (optionally by serial prefix).
    The OPLink never completes the GCS handshake (it has no telemetry module), so
    do not wait for client.connected: send_object/request_object work regardless."""
    import uavtalk
    from uavtalk_client import UAVTalkClient
    info = wait_for("+FW", serial, timeout=wait)
    if not info:
        raise RuntimeError("no OpenPilot board running firmware on USB")
    raw = RawHid(info)
    db = uavtalk.UAVObjectDB(os.path.join(HERE, "..", "..", "shared", "uavobjectdefinition"))
    return UAVTalkClient(HidUavtalkTransport(raw), db), raw, info


def halt_to_bootloader(serial=None, timeout=25.0, board_type=0):
    """Firmware -> bootloader: the GCS's 'Halt' (FirmwareIAPObj 1122, 2233, 3344).
    board_type: 0 is what the GCS sends; the OPLink only obeys its own type (3).
    Returns the +BL device info, or None if the board never came back as one."""
    import uavtalk
    try:
        client, raw, info = open_uavtalk(serial, wait=2.0)
    except RuntimeError:
        return None
    sn = info["serial_number"][:-3]
    print("halting %s (%s)" % (info["product_string"], info["serial_number"]), flush=True)
    quiet = lambda *a: None
    client.run(duration=0.5, on_object=quiet)
    fields = {"BoardRevision": 0, "BoardType": board_type}
    if board_type:
        # Addressing the board by its own type makes the FirmwareIAP module refresh
        # the object (description, crc) on every write whose crc is stale, and that
        # self-update re-enters its state machine and cancels the sequence.  Read the
        # object once and echo its crc so the three commands arrive alone.
        got = {}
        client.send_object("FirmwareIAPObj", dict(fields, Command=0), msg_type=uavtalk.TYPE_OBJ_ACK)
        client.run(duration=0.3, on_object=quiet)
        for _ in range(6):
            client.request_object("FirmwareIAPObj")
            client.run(duration=0.5, on_object=lambda o, i, d: got.update(d) if o.name == "FirmwareIAPObj" else None)
            if got:
                break
        if got:
            fields = {"BoardRevision": got["BoardRevision"], "BoardType": got["BoardType"], "crc": got["crc"],
                      "Description": got["Description"], "CPUSerial": got["CPUSerial"],
                      "BootloaderRevision": got["BootloaderRevision"]}
            print("  board type %d rev %d, bootloader rev %d" % (got["BoardType"], got["BoardRevision"], got["BootloaderRevision"]))
        else:
            print("  (no FirmwareIAPObj readback; sending the sequence blind)")
    for cmd in (1122, 2233, 3344):
        client.send_object("FirmwareIAPObj", dict(fields, Command=cmd), msg_type=uavtalk.TYPE_OBJ_ACK)
        try:
            client.run(duration=0.7, on_object=quiet)
        except Exception:
            break  # the board is already gone
    raw.close()
    bl = wait_for("+BL", sn, timeout=timeout, gone_first=True)
    print("  bootloader %s" % ("is up: %s" % bl["serial_number"] if bl else "did not appear"), flush=True)
    return bl


def reboot_firmware(serial=None, board_type=3, timeout=20.0):
    """Firmware -> firmware: 1122, 2233, 4455 (plain reset, no bootloader stop).
    Returns the +FW device info once the board is back on USB, or None."""
    import uavtalk
    try:
        client, raw, info = open_uavtalk(serial, wait=2.0)
    except RuntimeError:
        return None
    sn = info["serial_number"][:-3]
    quiet = lambda *a: None
    client.run(duration=0.5, on_object=quiet)
    for cmd in (1122, 2233, 4455):
        client.send_object("FirmwareIAPObj", {"Command": cmd, "BoardRevision": 0, "BoardType": board_type},
                           msg_type=uavtalk.TYPE_OBJ_ACK)
        try:
            client.run(duration=0.7, on_object=quiet)
        except Exception:
            break
    raw.close()
    return wait_for("+FW", sn, timeout=timeout, gone_first=True)


def open_bootloader(serial=None, wait=20.0, rescue=False):
    """Grab a +BL interface and put it in DFU mode. rescue=True waits for one to appear."""
    devs = enumerate_boards(serial, "+BL")
    if not devs:
        if not rescue:
            return None
        print("waiting %.0fs for a board in bootloader mode (plug it in now)..." % wait, flush=True)
        d = wait_for("+BL", serial, timeout=wait)
        if not d:
            return None
        devs = [d]
    raw = RawHid(devs[0])
    dfu = OpDfu(raw)
    dfu.enter_dfu(0)
    return dfu


# ----------------------------------------------------------------------------- commands
def cmd_list(_):
    devs = enumerate_boards()
    if not devs:
        print("no OpenPilot USB devices")
    for d in devs:
        print("  pid 0x%04X  %-14s %s" % (d["product_id"], d["product_string"], d["serial_number"]))


def cmd_info(a):
    dfu = open_bootloader(a.serial, rescue=a.wait > 0, wait=a.wait)
    if not dfu:
        raise SystemExit("no board in bootloader mode (use 'halt' first, or 'rescue')")
    for d in dfu.capabilities():
        print("  device %d: %s" % (d.index + 1, d))
    print("  status: %s" % dfu.status())
    if a.jump:
        dfu.jump()
        print("  jumped to firmware")


def cmd_halt(a):
    if not halt_to_bootloader(a.serial, board_type=a.board_type):
        raise SystemExit("halt failed")


def cmd_jump(a):
    dfu = open_bootloader(a.serial, rescue=a.wait > 0, wait=a.wait)
    if not dfu:
        raise SystemExit("no board in bootloader mode")
    sn = dfu.hid.info["serial_number"]
    dfu.jump(safeboot=a.safeboot, erase_settings=a.erase_settings)
    print("%s: jumped to firmware%s%s" % (sn, " (safe boot)" if a.safeboot else "",
                                          " with the erase-settings boot command" if a.erase_settings else ""), flush=True)


def flash(dfu, image_path, verify=True, jump=True):
    blob, desc, info = parse_opfw(image_path)
    print("image %s: %s rev %d  tag %s  uavo %s..." % (
        os.path.basename(image_path), BOARD_NAMES.get(info["board_type"], "board 0x%02X" % info["board_type"]),
        info["board_rev"], info["tag"], info["uavo_hash"][:8]), flush=True)
    devs = dfu.capabilities()
    if not devs:
        raise RuntimeError("bootloader reports no devices")
    dev = devs[0]
    print("target: %s" % dev, flush=True)
    if (dev.id >> 8) != info["board_type"]:
        raise RuntimeError("image is for board type 0x%02X, bootloader says 0x%02X: refusing"
                           % (info["board_type"], dev.id >> 8))
    if len(blob) > dev.size_of_code:
        raise RuntimeError("image (%d) larger than the code bank (%d)" % (len(blob), dev.size_of_code))
    padded = blob + b"\xff" * ((-len(blob)) % 4)
    crc = stm32_crc(padded, dev.size_of_code)
    t0 = time.time()
    dfu.upload(padded, TRANSFER_FW, crc, what="firmware")
    dfu.upload(desc, TRANSFER_DESC, what="description")
    if verify:
        # the bootloader compared our CRC with the flashed bank at Op_END already
        # (Last_operation_Success); this re-reads what it now reports
        again = dfu.capabilities()[0]
        ok = again.fw_crc == crc
        print("verify: bootloader reports CRC 0x%08X %s" % (again.fw_crc, "= ours" if ok else "(ours 0x%08X; bank CRC includes the description area on this bootloader)" % crc))
    print("flashed in %.1fs" % (time.time() - t0), flush=True)
    if jump:
        dfu.jump()
        print("booting firmware", flush=True)


def cmd_flash(a):
    dfu = None
    if not a.no_halt:
        bl = halt_to_bootloader(a.serial, board_type=a.board_type)
        if bl:
            time.sleep(0.5)
    dfu = open_bootloader(a.serial, rescue=a.no_halt, wait=a.wait)
    if not dfu:
        raise SystemExit("no board in bootloader mode")
    try:
        flash(dfu, a.image, verify=not a.no_verify, jump=not a.no_jump)
    finally:
        dfu.hid.close()
    if not a.no_jump:
        fw = wait_for("+FW", a.serial, timeout=15.0)
        print("firmware %s" % ("is back on USB: %s" % fw["serial_number"] if fw else "did not re-enumerate"))


def cmd_rescue(a):
    """Flash every board that shows up in bootloader mode until --count boards are done."""
    done = []
    skip = [x for x in (a.skip or "").split(",") if x]
    deadline = time.time() + a.wait
    print("waiting up to %.0fs for boards in bootloader mode: plug each one in, wait for 'firmware back on USB', then the next (%d to flash%s)"
          % (a.wait, a.count, ("; skipping " + ", ".join(skip)) if skip else ""), flush=True)
    while len(done) < a.count and time.time() < deadline:
        d = wait_for("+BL", a.serial, timeout=max(1.0, deadline - time.time()))
        if not d:
            break
        sn = d["serial_number"][:-3]
        if sn in done or any(sn.startswith(x) for x in skip):
            if sn not in done:
                print("[%s] already on this firmware, leaving it alone" % sn, flush=True)
                done.append(sn)
                a.count += 1
            time.sleep(0.5)
            continue
        print("\n[%s] bootloader on USB" % sn, flush=True)
        raw = None
        try:
            raw = RawHid(d)
            dfu = OpDfu(raw)
            dfu.enter_dfu(0)
            flash(dfu, a.image, verify=not a.no_verify, jump=not a.no_jump)
            raw.close()
            raw = None
            fw = wait_for("+FW", sn, timeout=15.0)
            print("[%s] %s" % (sn, "firmware back on USB" if fw else "did not re-enumerate (yet)"), flush=True)
            done.append(sn)
        except Exception as e:
            print("[%s] FAILED: %s" % (sn, e), flush=True)
            if raw:
                raw.close()
            time.sleep(2.0)
    print("\nflashed %d/%d: %s" % (len(done), a.count, ", ".join(done) or "-"), flush=True)
    if len(done) < a.count:
        raise SystemExit(1)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--serial", help="CPU serial prefix to pick one board when several are plugged in")
    ap.add_argument("--board-type", type=int, default=0,
                    help="BoardType sent with the halt sequence (0 = any flight controller, 3 = OPLink)")
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("list").set_defaults(f=cmd_list)
    p = sub.add_parser("info"); p.add_argument("--wait", type=float, default=0); p.add_argument("--jump", action="store_true"); p.set_defaults(f=cmd_info)
    p = sub.add_parser("halt"); p.set_defaults(f=cmd_halt)
    p = sub.add_parser("reboot"); p.set_defaults(f=lambda a: print("rebooted: %s" % (reboot_firmware(a.serial, a.board_type or 3) or "did not come back")))
    p = sub.add_parser("jump"); p.add_argument("--safeboot", action="store_true"); p.add_argument("--erase-settings", action="store_true")
    p.add_argument("--wait", type=float, default=0, help="wait this long for a board to show up in bootloader mode"); p.set_defaults(f=cmd_jump)
    for name, f in (("flash", cmd_flash), ("rescue", cmd_rescue)):
        p = sub.add_parser(name)
        p.add_argument("image")
        p.add_argument("--no-halt", action="store_true", help="board is already in its bootloader")
        p.add_argument("--no-jump", action="store_true")
        p.add_argument("--no-verify", action="store_true")
        p.add_argument("--wait", type=float, default=30.0, help="seconds to wait for a +BL device")
        if name == "rescue":
            p.add_argument("--count", type=int, default=1, help="how many boards to flash as they are replugged")
            p.add_argument("--skip", help="comma-separated serial prefixes to leave alone (already flashed)")
        p.set_defaults(f=f)
    a = ap.parse_args()
    a.f(a)


if __name__ == "__main__":
    main()
