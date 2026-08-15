#!/usr/bin/env python3
"""Serial console to the OSD32MP1 over USB, in userspace. No kext, no signing.

WHY THIS WORKS WHERE macOS DOES NOT
-----------------------------------
The stock OpenSTLinux image ships an RNDIS-only gadget, which macOS cannot use
at all. Our edited image (see README) makes it composite instead:

    ecm.0  -> CDC-ECM   macOS binds this natively -> usb0, board 192.168.7.1
    acm.0  -> CDC-ACM   serial console -> /dev/ttyGS0 on the board

MEASURED on the board 2026-08-15, and it is the OPPOSITE way round from the
Debian image - do not reason from the older notes:

  * The ACM half binds NATIVELY. This gadget advertises bInterfaceProtocol
    0x01 (AT-command set), exactly what AppleUSBACM requires, so macOS creates
    /dev/cu.usbmodem* on its own. The Debian image advertised 0xff and was
    refused; this one is not.
  * The ECM half does NOT fully bind while ACM is present. AppleUSBECMControl
    attaches but AppleUSBECMData stays at 0, no network interface appears, and
    the board's usb0 sits at "no-carrier (configuring)". Removing acm.0 makes
    ECM work instantly (host gets 192.168.7.x, board answers on 192.168.7.1);
    re-adding it breaks ECM again, in EITHER interface order. NCM+ACM attaches
    both drivers but never negotiates carrier either.

So on macOS this gadget is EITHER a network device OR a serial console, not
both. The shipped config picks the console: Ethernet already covers
networking, and the console is the one channel that survives every network
failure.

=> Day to day you do NOT need this script. Use board_cmd.py, or just
   `screen /dev/cu.usbmodem* 115200`. It stays as the fallback for an image
   whose ACM function advertises protocol 0xff (the stock build), where macOS
   binds nothing and libusb has to drive the bulk endpoints directly.

Interface numbers are discovered at runtime, never hardcoded - adding the ECM
function shifted ACM from interfaces 0/1 to 2/3.

HoRNDIS is unnecessary: with ECM in place RNDIS is not in play at all, and a
kext would need signing plus reduced-security boot. This needs neither.

usage:
    ./usb_console.py            interactive console (ctrl-] to quit)
    ./usb_console.py --probe    just read for 3s and show what arrives
"""
import sys
import termios
import threading
import time
import tty

import usb.core
import usb.util

VID, PID = 0x1d6b, 0x0104

CDC_COMM, CDC_DATA = 0x02, 0x0a
SUBCLASS_ACM = 0x02


def find_acm(dev):
    """Locate the ACM function's DATA interface and its bulk endpoints.

    These must NOT be hardcoded. The gadget is composite (ecm.0 + acm.0), so
    ECM takes interfaces 0/1 and ACM lands on 2/3 - but flipping the order in
    stm32_usbotg_eth_config.sh, or dropping ECM, renumbers everything. Walk
    the descriptors instead: find the CDC-Comm interface whose subclass is ACM
    (0x02, as opposed to ECM's 0x06), then the next CDC-Data interface after
    it, and read the endpoint addresses off that.
    """
    cfg = dev.get_active_configuration()
    ifaces = sorted(cfg, key=lambda i: (i.bInterfaceNumber, i.bAlternateSetting))
    acm_ctrl = None
    for intf in ifaces:
        if (intf.bInterfaceClass == CDC_COMM
                and intf.bInterfaceSubClass == SUBCLASS_ACM):
            acm_ctrl = intf.bInterfaceNumber
            break
    if acm_ctrl is None:
        sys.exit("no CDC-ACM function on this gadget - is acm.0 in the config?\n"
                 "(run usb_descriptors.py to see what it actually offers)")
    for intf in ifaces:
        if intf.bInterfaceClass == CDC_DATA and intf.bInterfaceNumber > acm_ctrl:
            ep_in = ep_out = None
            for ep in intf:
                if usb.util.endpoint_type(ep.bmAttributes) != usb.util.ENDPOINT_TYPE_BULK:
                    continue
                if usb.util.endpoint_direction(ep.bEndpointAddress) == usb.util.ENDPOINT_IN:
                    ep_in = ep.bEndpointAddress
                else:
                    ep_out = ep.bEndpointAddress
            if ep_in is not None and ep_out is not None:
                return acm_ctrl, intf.bInterfaceNumber, ep_in, ep_out
    sys.exit(f"found ACM control interface {acm_ctrl} but no matching CDC-Data "
             "interface with bulk endpoints")


def open_device():
    dev = usb.core.find(idVendor=VID, idProduct=PID)
    if dev is None:
        sys.exit("STM32MP1 gadget not found (is the board booted and plugged in?)")
    try:
        dev.set_configuration()
    except usb.core.USBError:
        pass                    # already configured is fine

    ctrl_iface, data_iface, ep_in, ep_out = find_acm(dev)

    # Claim ONLY the DATA interface. Claiming the CDC-Comm interface too used
    # to return ENODEV on every subsequent transfer: macOS may have bound the
    # ECM function on this same device, and the control interface is not
    # needed to move bytes anyway.
    try:
        if dev.is_kernel_driver_active(data_iface):
            dev.detach_kernel_driver(data_iface)
    except (NotImplementedError, usb.core.USBError):
        pass
    try:
        usb.util.claim_interface(dev, data_iface)
    except usb.core.USBError as e:
        sys.exit(f"could not claim CDC-Data interface {data_iface}: {e}")

    # NO CDC CONTROL REQUESTS. The ACM functional descriptor reports
    # bmCapabilities=0x00 - the device advertises no line-control support,
    # so SET_LINE_CODING / SET_CONTROL_LINE_STATE are STALLed, and the stall
    # wedges the pipe into ENODEV on the next transfer. This gadget is a raw
    # bulk pipe; treat it as one.
    print(f"[console] ACM ctrl intf {ctrl_iface}, data intf {data_iface}, "
          f"ep IN 0x{ep_in:02x} / OUT 0x{ep_out:02x}\r")
    return dev, data_iface, ep_in, ep_out


def reader(dev, ep_in, stop):
    """Bulk-IN -> stdout. Timeouts are normal when the board is quiet."""
    while not stop.is_set():
        try:
            data = dev.read(ep_in, 512, timeout=500)
            if data:
                sys.stdout.write(bytes(data).decode("utf-8", "replace"))
                sys.stdout.flush()
        except usb.core.USBError as e:
            if e.errno not in (60, None) and "timeout" not in str(e).lower():
                sys.stderr.write(f"\r\n[read error: {e}]\r\n")
                return


def main():
    dev, data_iface, ep_in, ep_out = open_device()
    probe = "--probe" in sys.argv
    stop = threading.Event()

    if probe:
        print("[probe] reading 3s - press ENTER on the board's console to see a prompt")
        t = threading.Thread(target=reader, args=(dev, ep_in, stop), daemon=True)
        t.start()
        # A bare newline usually makes getty/login redraw its prompt.
        try:
            dev.write(ep_out, b"\r\n", timeout=1000)
        except usb.core.USBError as e:
            print(f"[probe] write failed: {e}")
        time.sleep(3)
        stop.set()
        print("\n[probe] done")
        try: usb.util.release_interface(dev, data_iface)
        except Exception: pass
        return

    print("[console] connected. ctrl-] to quit.\r")
    t = threading.Thread(target=reader, args=(dev, ep_in, stop), daemon=True)
    t.start()
    fd = sys.stdin.fileno()
    old = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        while True:
            ch = sys.stdin.read(1)
            if ch == "\x1d":          # ctrl-]
                break
            try:
                dev.write(ep_out, ch.encode(), timeout=1000)
            except usb.core.USBError as e:
                sys.stderr.write(f"\r\n[write error: {e}]\r\n")
                break
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old)
        stop.set()
        time.sleep(0.6)      # let the reader exit before releasing
        try: usb.util.release_interface(dev, data_iface)
        except Exception: pass
        print("\r\n[console] closed")


if __name__ == "__main__":
    main()
