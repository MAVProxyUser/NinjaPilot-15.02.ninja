#!/usr/bin/env python3
"""Dump the STM32MP1 Linux gadget's USB descriptors.

Before writing any userspace RNDIS driver, find out what the composite gadget
ACTUALLY offers. macOS binding nothing does not prove RNDIS-only: a CDC-ACM
(serial) function may be sitting there unclaimed, and a serial console is
three orders of magnitude less work than an RNDIS stack + utun bridge.

Class codes that matter here:
  0x02 CDC Communications  subclass 0x02 = ACM (serial), 0x06 = ECM, 0x0e = NCM
  0x0a CDC Data            (bulk endpoints for the above)
  0xe0 Wireless            subclass 0x01 proto 0x03 = RNDIS
  0x08 Mass storage
"""
import sys
import usb.core
import usb.util

CLS = {0x00: "per-interface", 0x02: "CDC-Comm", 0x03: "HID", 0x08: "MassStorage",
       0x0a: "CDC-Data", 0x0e: "Video", 0xe0: "Wireless", 0xff: "VendorSpecific"}
CDC_SUB = {0x02: "ACM (serial)", 0x06: "ECM (macOS-native!)", 0x0e: "NCM (macOS-native!)",
           0x0d: "EEM", 0x01: "DLCM"}


def main():
    devs = list(usb.core.find(find_all=True, idVendor=0x1d6b))
    devs += list(usb.core.find(find_all=True, idVendor=0x0483))
    if not devs:
        print("no STM32MP1 gadget / STMicro device found")
        return 1
    for d in devs:
        print(f"=== {d.idVendor:04x}:{d.idProduct:04x} bus {d.bus} addr {d.address} ===")
        try:
            print(f"    manufacturer : {usb.util.get_string(d, d.iManufacturer)}")
            print(f"    product      : {usb.util.get_string(d, d.iProduct)}")
        except Exception as e:
            print(f"    (string descriptors unreadable: {e})")
        for cfg in d:
            print(f"  config {cfg.bConfigurationValue}  "
                  f"({cfg.bNumInterfaces} interfaces, {cfg.bMaxPower*2} mA)")
            for intf in cfg:
                c, s, p = (intf.bInterfaceClass, intf.bInterfaceSubClass,
                           intf.bInterfaceProtocol)
                desc = CLS.get(c, f"0x{c:02x}")
                extra = ""
                if c == 0x02:
                    extra = "  <- " + CDC_SUB.get(s, f"subclass 0x{s:02x}")
                if c == 0xe0 and s == 0x01 and p == 0x03:
                    extra = "  <- RNDIS control (macOS will NOT bind this)"
                print(f"    intf {intf.bInterfaceNumber} alt {intf.bAlternateSetting}: "
                      f"class 0x{c:02x} {desc} sub 0x{s:02x} proto 0x{p:02x}{extra}")
                for ep in intf:
                    tt = usb.util.endpoint_type(ep.bmAttributes)
                    tn = {0: "control", 1: "iso", 2: "BULK", 3: "interrupt"}.get(tt, "?")
                    d_ = "IN " if usb.util.endpoint_direction(ep.bEndpointAddress) else "OUT"
                    print(f"        ep 0x{ep.bEndpointAddress:02x} {d_} {tn:9s} "
                          f"maxpkt {ep.wMaxPacketSize}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
