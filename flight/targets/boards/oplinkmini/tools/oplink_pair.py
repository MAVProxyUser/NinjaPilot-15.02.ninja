#!/usr/bin/env python3
"""oplink_pair.py - talk to OPLink Mini / PipXtreme modems over USB and pair them.

  oplink_pair.py status [--serial 51FF..]        identity, settings and link state of every modem
  oplink_pair.py configure --serial 51FF.. [--coordinator | --coord-id ID]
                 [--power 1.25] [--speed 57600] [--min 0] [--max 250]
                 [--main Telemetry] [--flexi Disabled] [--vcp Disabled] [--save]
  oplink_pair.py pair [--power 1.25] [--speed 57600] [--coordinator SERIAL]
                 one modem becomes the coordinator, the other binds to its DeviceID; both saved
  oplink_pair.py watch [--seconds 20]           stream LinkState / RSSI / rates from every modem

Settings are read at boot (pios_board.c), so 'configure --save' is followed by a
reboot (FirmwareIAP halt + bootloader jump, firmware from this tree) or, on an
older firmware, a replug.  One HID holder at a time: quit the GCS first.
"""
import argparse, os, sys, time
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, "..", "..", "..", "..", ".."))
sys.path.insert(0, os.path.join(ROOT, "ground", "pyuavtalk"))
import uavtalk, opdfu

OPLINK_BOARD_TYPE = 0x03


class Modem(object):
    """One modem on USB, driven through its own UAVTalk link."""

    def __init__(self, info):
        self.info = info
        self.serial = info["serial_number"][:-3]
        self.client, self.raw, _ = opdfu.open_uavtalk(self.serial, wait=5.0)
        self.seen = {}
        self.unknown = set()

    def close(self):
        self.raw.close()

    def _grab(self, objdef, inst, d):
        self.seen[objdef.name] = d

    def run(self, secs):
        # quiet the "unknown object id" prints an old firmware would cause
        real_print = __builtins__.print if hasattr(__builtins__, "print") else print
        def quiet(*a, **k):
            s = " ".join(str(x) for x in a)
            if s.startswith("[recv] unknown object id"):
                self.unknown.add(s.split()[4])
                return
            real_print(*a, **k)
        import uavtalk_client
        uavtalk_client.print = quiet
        try:
            self.client.run(duration=secs, on_object=self._grab)
        finally:
            uavtalk_client.print = real_print

    def fetch(self, name, secs=3.0):
        self.seen.pop(name, None)
        t = time.time() + secs
        while time.time() < t and name not in self.seen:
            self.client.request_object(name)
            self.run(0.5)
        return self.seen.get(name)

    def write_settings(self, values, save=True):
        self.client.send_object("OPLinkSettings", values, msg_type=uavtalk.TYPE_OBJ_ACK)
        self.run(0.5)
        if save:
            self.client.send_object("ObjectPersistence", {
                "Operation": "Save", "Selection": "SingleObject",
                "ObjectID": self.client.db["OPLinkSettings"].obj_id, "InstanceID": 0,
            }, msg_type=uavtalk.TYPE_OBJ_ACK)
            t = time.time() + 4.0
            while time.time() < t:
                self.run(0.5)
                op = self.seen.get("ObjectPersistence")
                if op and op.get("Operation") == "Completed":
                    return True
            return False
        return True


def describe(desc_bytes):
    b = bytes(int(x) & 0xFF for x in desc_bytes)
    if b[:4] != b"OpFw":
        return "no OpFw description (%s)" % b[:4].hex()
    tag = b[14:40].split(b"\0")[0].decode("ascii", "replace")
    hashes = ("  fw %s  uavo %s" % (b[40:60].hex()[:8], b[60:80].hex()[:8])) if len(b) >= 80 else ""
    return "board 0x%02X rev %d  tag %s%s" % (b[12], b[13], tag, hashes)


def show(m):
    st = m.fetch("OPLinkStatus")
    se = m.fetch("OPLinkSettings")
    print("modem %s (%s)" % (m.serial, m.info["product_string"]))
    if not st:
        print("  OPLinkStatus: not answered (unknown ids seen: %s) -> older firmware, flash it first"
              % ", ".join(sorted(m.unknown)) if m.unknown else "  OPLinkStatus: not answered")
        return None, None
    print("  firmware:  %s" % describe(st["Description"]))
    print("  DeviceID:  0x%08X   heap %d   resets %d   timeouts %d" % (st["DeviceID"], st["HeapRemaining"], st["Resets"], st["Timeouts"]))
    print("  link:      %s   RSSI %d dBm   quality %d   tx %d B/s   rx %d B/s" % (
        st["LinkState"], st["RSSI"], st["LinkQuality"], st["TXRate"], st["RXRate"]))
    pairs = ["0x%08X" % p for p in st["PairIDs"] if p]
    print("  pairs:     %s" % (", ".join(pairs) if pairs else "none"))
    if se:
        print("  settings:  Coordinator %s  CoordID 0x%08X  power %s mW  speed %s  channels %d..%d" % (
            se["Coordinator"], se["CoordID"], se["MaxRFPower"], se["ComSpeed"], se["MinChannel"], se["MaxChannel"]))
        print("             MainPort %s  FlexiPort %s  VCPPort %s  OneWay %s  PPM %s  PPMOnly %s" % (
            se["MainPort"], se["FlexiPort"], se["VCPPort"], se["OneWay"], se["PPM"], se["PPMOnly"]))
    return st, se


def modems(serial=None):
    out = []
    for info in opdfu.enumerate_boards(serial, "+FW"):
        if info["product_id"] != 0x415C:
            continue
        out.append(Modem(info))
    if not out:
        raise SystemExit("no OPLink / PipXtreme running firmware on USB")
    return out


def apply(m, a, coordinator, coord_id):
    se = m.fetch("OPLinkSettings")
    if not se:
        raise SystemExit("%s: no OPLinkSettings from the modem" % m.serial)
    new = dict(se)
    new["Coordinator"] = "TRUE" if coordinator else "FALSE"
    new["CoordID"] = 0 if coordinator else coord_id
    if a.power is not None:
        new["MaxRFPower"] = a.power
    if a.speed is not None:
        new["ComSpeed"] = a.speed
    if a.min is not None:
        new["MinChannel"] = a.min
    if a.max is not None:
        new["MaxChannel"] = a.max
    for k, v in (("MainPort", a.main), ("FlexiPort", a.flexi), ("VCPPort", a.vcp)):
        if v is not None:
            new[k] = v
    ok = m.write_settings(new, save=a.save)
    rb = m.fetch("OPLinkSettings")
    print("%s: %s -> Coordinator %s CoordID 0x%08X power %s speed %s ch %d..%d main %s%s" % (
        m.serial, "saved" if ok else "written (save NOT confirmed)", rb["Coordinator"], rb["CoordID"],
        rb["MaxRFPower"], rb["ComSpeed"], rb["MinChannel"], rb["MaxChannel"], rb["MainPort"],
        "" if a.save else " (not saved)"))
    return ok


def reboot(m):
    """Settings live in flash until the modem boots: halt into the bootloader
    (this tree's firmware answers the IAP sequence for its own board type), then jump."""
    serial = m.serial
    m.close()
    bl = opdfu.halt_to_bootloader(serial, board_type=OPLINK_BOARD_TYPE, timeout=12.0)
    if not bl:
        print("%s: no bootloader after the halt (older firmware?) -> replug it to apply the settings" % serial)
        return False
    time.sleep(0.3)
    dfu = opdfu.open_bootloader(serial)
    dfu.jump()
    dfu.hid.close()
    fw = opdfu.wait_for("+FW", serial, timeout=15.0)
    print("%s: rebooted%s" % (serial, "" if fw else " (did not re-enumerate yet)"))
    return bool(fw)


def cmd_status(a):
    for m in modems(a.serial):
        show(m)
        m.close()


def cmd_configure(a):
    if a.serial is None:
        raise SystemExit("configure needs --serial")
    ms = modems(a.serial)
    m = ms[0]
    for other in ms[1:]:
        other.close()
    apply(m, a, a.coordinator, a.coord_id or 0)
    if a.save and not a.no_reboot:
        reboot(m)
    else:
        m.close()


def cmd_pair(a):
    ms = modems()
    if len(ms) != 2:
        raise SystemExit("pair needs exactly two modems on USB, found %d" % len(ms))
    ids = {}
    for m in ms:
        st, _ = show(m)
        if not st:
            raise SystemExit("%s does not answer OPLinkStatus: flash it with this tree's firmware first" % m.serial)
        ids[m.serial] = st["DeviceID"]
    if a.coordinator:
        coord = next((m for m in ms if m.serial.startswith(a.coordinator)), None)
        if not coord:
            raise SystemExit("no modem with serial %s" % a.coordinator)
    else:
        coord = ms[0]
    remote = ms[1] if coord is ms[0] else ms[0]
    print("\ncoordinator %s (DeviceID 0x%08X), remote %s binds to it" % (coord.serial, ids[coord.serial], remote.serial))
    a.save = True
    a.main = a.coord_main
    ok1 = apply(coord, a, True, 0)
    a.main = a.remote_main
    ok2 = apply(remote, a, False, ids[coord.serial])
    if not (ok1 and ok2):
        print("a save was not confirmed; not rebooting")
        for m in ms:
            m.close()
        return
    rebooted = [reboot(m) for m in ms]
    if all(rebooted):
        time.sleep(2.0)
        cmd_watch(argparse.Namespace(serial=None, seconds=a.seconds))


def cmd_snoop(a):
    """Catch a modem that only lives a few seconds: wait for its firmware to
    enumerate, then dump everything it says until it drops off USB."""
    t_end = time.time() + a.wait
    skip = [x for x in (a.skip or "").split(",") if x]
    while time.time() < t_end:
        info = None
        while time.time() < t_end and info is None:
            for d in opdfu.enumerate_boards(a.serial, "+FW"):
                if not any(d["serial_number"].startswith(x) for x in skip):
                    info = d
                    break
            if info is None:
                time.sleep(0.1)
        if not info:
            break
        t0 = time.time()
        print("[%.1fs] %s %s is up" % (0.0, info["product_string"], info["serial_number"]), flush=True)
        try:
            m = Modem(info)
        except Exception as e:
            print("  open failed: %s" % e, flush=True)
            time.sleep(0.3)
            continue
        last = {}
        try:
            while time.time() - t0 < a.seconds:
                for name in ("OPLinkSettings", "OPLinkStatus", "RadioComBridgeStats"):
                    m.client.request_object(name)
                m.run(0.4)
                for name, d in list(m.seen.items()):
                    if last.get(name) != d:
                        last[name] = d
                        if name == "OPLinkStatus":
                            print("[%.1fs] %s: heap %s link %s DeviceID 0x%08X resets %s timeouts %s desc %s" % (
                                time.time() - t0, name, d["HeapRemaining"], d["LinkState"], d["DeviceID"], d["Resets"], d["Timeouts"],
                                describe(d["Description"])), flush=True)
                        else:
                            print("[%.1fs] %s: %s" % (time.time() - t0, name, d), flush=True)
        except Exception as e:
            print("[%.1fs] link lost: %s" % (time.time() - t0, e), flush=True)
        finally:
            m.close()
        if m.unknown:
            print("  unknown object ids: %s" % ", ".join(sorted(m.unknown)))
        if a.once:
            break
    print("snoop done", flush=True)


def cmd_watch(a):
    ms = modems(a.serial)
    t_end = time.time() + a.seconds
    connected = {m.serial: False for m in ms}
    while time.time() < t_end:
        line = []
        for m in ms:
            st = m.fetch("OPLinkStatus", secs=1.5)
            if not st:
                line.append("%s: -" % m.serial[-6:])
                continue
            pairs = ["%08X@%ddBm" % (p, r) for p, r in zip(st["PairIDs"], st["PairSignalStrengths"]) if p]
            heard = any(p and r > -127 for p, r in zip(st["PairIDs"], st["PairSignalStrengths"]))
            # the 15.02 driver only ever marks the *remote* Connected (pios_rfm22b.c); a
            # coordinator stays "Enabled" and shows who it hears in its pair table instead
            connected[m.serial] = st["LinkState"] == "Connected" or heard
            line.append("%s: %-10s q %3d tx %4d rx %4d hears %s" % (
                m.serial[-6:], st["LinkState"], st["LinkQuality"], st["TXRate"], st["RXRate"], ",".join(pairs) or "-"))
        print("  " + "   |   ".join(line), flush=True)
        time.sleep(1.0)
    for m in ms:
        m.close()
    print("result: %s" % ("BOTH MODEMS LINKED (remote Connected, coordinator hears it)" if all(connected.values()) else "not linked: %s" % connected))


def modem_tty(serial):
    """The CDC serial port of the modem with this CPU serial (macOS: tty name carries the USB location)."""
    import subprocess, re, glob
    out = subprocess.run(["ioreg", "-p", "IOUSB", "-l", "-w0"], capture_output=True, text=True).stdout
    cur = {}
    loc = None
    for line in out.splitlines():
        m = re.search(r'"(USB Serial Number|locationID)" = (.*)', line)
        if m:
            cur[m.group(1)] = m.group(2).strip().strip('"')
        if re.match(r'^\s*[|\s]*\+-o ', line):
            if cur.get("USB Serial Number", "").startswith(serial):
                loc = int(cur["locationID"])
                break
            cur = {}
    if loc is None and cur.get("USB Serial Number", "").startswith(serial):
        loc = int(cur["locationID"])
    if loc is None:
        return None
    key = "%x" % (loc >> 16)
    for dev in sorted(glob.glob("/dev/cu.usbmodem*")):
        if key in dev:
            return dev
    return None


def cmd_linktest(a):
    """Prove the radio carries data both ways with no flight controller: the remote's
    USB serial port (VCPPort = Serial) stands in for the flight controller, this tool
    stands in for the GCS on the coordinator's HID, and UAVTalk packets go round."""
    import serial as pyserial
    ms = modems()
    coord = remote = None
    for m in ms:
        se = m.fetch("OPLinkSettings")
        if se and se["Coordinator"] == "TRUE":
            coord = m
        elif se:
            remote = m
    if not (coord and remote):
        raise SystemExit("need one coordinator and one remote on USB (found %d modems)" % len(ms))
    print("coordinator %s, remote %s" % (coord.serial, remote.serial))
    se = remote.fetch("OPLinkSettings")
    if se["VCPPort"] != "Serial":
        print("remote: VCPPort -> Serial for the test (saved, reboot)")
        new = dict(se); new["VCPPort"] = "Serial"
        remote.write_settings(new, save=True)
        reboot(remote)
        time.sleep(1.5)
        remote = None
    else:
        remote.close()
    tty = modem_tty(a.remote or [m.serial for m in ms if m is not coord][0])
    if not tty:
        raise SystemExit("could not find the remote's USB serial port")
    print("remote serial port: %s" % tty)
    port = pyserial.Serial(tty, 57600, timeout=0)
    client, db = coord.client, coord.client.db
    parser = uavtalk.UAVTalkParser()
    down = {"GCSTelemetryStats": 0, "other": 0}
    up_seen = {"n": 0}
    rtts = []
    pending = {}
    req_id = db["SystemStats"].obj_id

    def on_obj(objdef, inst, d):
        if objdef.name == "FlightTelemetryStats":
            up_seen["n"] += 1
        elif objdef.name == "SystemStats":
            seq = d.get("CPULoad", 0)
            t0 = pending.pop(seq, None)
            if t0 is not None:
                rtts.append(time.time() - t0)

    t_end = time.time() + a.seconds
    seq = 0
    last_send = 0.0
    print("running %.0fs: GCS side sends GCSTelemetryStats + SystemStats requests, the serial side answers and pushes FlightTelemetryStats" % a.seconds)
    while time.time() < t_end:
        now = time.time()
        if now - last_send > 0.25:
            seq = (seq + 1) % 100
            pending[seq] = now
            client.send_raw(uavtalk.TYPE_OBJ_REQ, req_id)
            client.send_object("GCSTelemetryStats", {"Status": "Connected"})
            # the fake flight controller pushes an object of its own, unsolicited
            port.write(uavtalk.build_packet(uavtalk.TYPE_OBJ, db["FlightTelemetryStats"].obj_id, 0,
                                            db["FlightTelemetryStats"].pack({"Status": "Connected"})))
            last_send = now
        client.run(duration=0.05, on_object=on_obj)
        data = port.read(4096)
        if data:
            parser.feed(data)
            for msg_type, obj_id, inst_id, payload in parser.packets():
                objdef = db.by_id.get(obj_id)
                name = objdef.name if objdef else "0x%08X" % obj_id
                if msg_type == uavtalk.TYPE_OBJ_REQ and obj_id == req_id:
                    # answer like a flight controller would, tagging the reply with the sequence
                    port.write(uavtalk.build_packet(uavtalk.TYPE_OBJ, req_id, 0, db["SystemStats"].pack({"CPULoad": seq})))
                    down["other"] += 1
                elif name == "GCSTelemetryStats":
                    down["GCSTelemetryStats"] += 1
                else:
                    down["other"] += 1
    port.close()
    sent = seq if seq else 0
    print("\ncoordinator -> remote (over the air, out of the remote's serial port):")
    print("  GCSTelemetryStats seen %d, requests/other %d" % (down["GCSTelemetryStats"], down["other"]))
    print("remote -> coordinator (into the remote's serial port, out of the coordinator's USB):")
    print("  FlightTelemetryStats seen %d" % up_seen["n"])
    if rtts:
        print("round trips answered %d/%d, mean %.0f ms, max %.0f ms" % (len(rtts), len(rtts) + len(pending), 1000 * sum(rtts) / len(rtts), 1000 * max(rtts)))
    else:
        print("round trips answered 0/%d" % len(pending))
    ok = down["GCSTelemetryStats"] > 0 and up_seen["n"] > 0 and rtts
    print("result: %s" % ("DATA FLOWS BOTH WAYS" if ok else "FAILED"))
    coord.close()
    if not a.keep:
        m = Modem(opdfu.wait_for("+FW", [x.serial for x in ms if x is not coord][0], timeout=10.0))
        se = m.fetch("OPLinkSettings")
        if se and se["VCPPort"] != "Disabled":
            print("remote: VCPPort -> Disabled again (saved, reboot)")
            new = dict(se); new["VCPPort"] = "Disabled"
            m.write_settings(new, save=True)
            reboot(m)
        else:
            m.close()


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--serial")
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("status").set_defaults(f=cmd_status)
    p = sub.add_parser("watch"); p.add_argument("--seconds", type=float, default=20.0); p.set_defaults(f=cmd_watch)
    p = sub.add_parser("linktest"); p.add_argument("--seconds", type=float, default=10.0)
    p.add_argument("--remote", help="serial prefix of the remote (default: the non-coordinator)")
    p.add_argument("--keep", action="store_true", help="leave the remote's VCPPort = Serial afterwards"); p.set_defaults(f=cmd_linktest)
    p = sub.add_parser("snoop"); p.add_argument("--seconds", type=float, default=30.0, help="how long to follow one boot")
    p.add_argument("--wait", type=float, default=600.0, help="how long to wait for the modem to appear")
    p.add_argument("--once", action="store_true"); p.add_argument("--skip", help="comma-separated serial prefixes to ignore")
    p.set_defaults(f=cmd_snoop)
    for name, f in (("configure", cmd_configure), ("pair", cmd_pair)):
        p = sub.add_parser(name)
        p.add_argument("--power", help="MaxRFPower in mW: 0 1.25 1.6 3.16 6.3 12.6 25 50 100 (0 = radio off)")
        p.add_argument("--speed", help="ComSpeed: 4800 9600 19200 38400 57600 115200")
        p.add_argument("--min", type=int); p.add_argument("--max", type=int)
        p.add_argument("--main"); p.add_argument("--flexi"); p.add_argument("--vcp")
        p.set_defaults(f=f)
        if name == "configure":
            p.add_argument("--coordinator", action="store_true")
            p.add_argument("--coord-id", type=lambda x: int(x, 0))
            p.add_argument("--save", action="store_true")
            p.add_argument("--no-reboot", action="store_true")
        else:
            p.add_argument("--coordinator", metavar="SERIAL", help="which modem coordinates (default: first found)")
            p.add_argument("--coord-main", default="Disabled", help="coordinator MainPort (GCS side talks USB; default Disabled)")
            p.add_argument("--remote-main", default="Telemetry", help="remote MainPort (default Telemetry: the flight controller's TELEM port)")
            p.add_argument("--seconds", type=float, default=20.0, help="how long to watch the link afterwards")
    a = ap.parse_args()
    a.f(a)


if __name__ == "__main__":
    main()
