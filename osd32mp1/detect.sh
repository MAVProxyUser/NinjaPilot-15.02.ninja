#!/bin/bash
# OSD32MP1-RED connection detector for macOS.
#
# The board should appear in ONE of three ways once it boots (default image is
# Debian on eMMC, per Octavo's getting-started guide):
#
#   1. RNDIS USB network gadget  -> board at 192.168.7.1, host gets 192.168.7.x
#   2. USB serial console        -> /dev/cu.usbmodem* or /dev/cu.usbserial*
#   3. Wired Ethernet            -> DHCP address on the LAN
#
# Seeing NONE of them, with the board powered, is almost always one of:
#   - a CHARGE-ONLY USB-A -> USB-C cable (the single most common cause)
#   - insufficient power: the board wants 5V @ 2A; a bus-powered hub may not
#     deliver it. The 5.5mm/2.5mm barrel jack bypasses this entirely.
#   - boot switches: the 3-bit switch by the USB host port must be 0,1,0 for
#     eMMC (1,0,1 selects SD card).
set -u

echo "=== 1. USB devices that look like the board ==="
found_usb=0
found_dfu=0
# 0x0483/0xdf11 = STM32 ROM bootloader in USB-DFU. 57105 = 0xdf11 decimal.
if ioreg -p IOUSB -w0 -l 2>/dev/null | grep -q '"idProduct" = 57105'; then
    echo "  *** STM32 ROM BOOTLOADER (DFU, 0483:df11) present"
    dfu-util -l 2>/dev/null | grep -oE 'alt=[0-9]+, name="[^"]*"' | sed 's/^/      /'
    found_usb=1
    found_dfu=1
elif ioreg -p IOUSB -w0 -l 2>/dev/null | grep -q '"kUSBProductString" = "STM32MP1"'; then
    # BOOTED LINUX. The gadget enumerates under the LINUX FOUNDATION vid
    # 0x1D6B (7531) / 0x0104 "Multifunction Composite Gadget", NOT ST's
    # 0x0483 - so searching for the ST id makes a correctly-booted board
    # look absent. That bug cost a debugging round; do not reintroduce it.
    echo "  *** STM32MP1 LINUX USB GADGET present (board is BOOTED)"
    found_usb=1
    found_booted=1
elif ioreg -p IOUSB -w0 -l 2>/dev/null | grep -qiE '"idVendor" = (1155|1027|1259)'; then
    # 1155=0x0483 STMicro, 1027=0x0403 FTDI, 1259=0x04EB
    ioreg -p IOUSB -w0 -l | grep -iE '"USB Product Name"|"idVendor"|"idProduct"' | sed 's/^ *//'
    found_usb=1
else
    echo "  no STM32MP1 gadget, no STMicro (0x0483) / FTDI (0x0403) device"
fi

echo
echo "=== 2. serial consoles ==="
ls /dev/cu.usb* 2>/dev/null || echo "  none (no /dev/cu.usb*)"

echo
echo "=== 3. RNDIS / USB-network interface (expect 192.168.7.x) ==="
found_net=0
for i in $(ifconfig -l); do
    ip=$(ipconfig getifaddr "$i" 2>/dev/null || true)
    if [ -n "${ip:-}" ]; then
        case "$ip" in
            192.168.7.*) echo "  *** $i -> $ip  (board should be 192.168.7.1)"; found_net=1 ;;
            *)           echo "      $i -> $ip" ;;
        esac
    fi
done
[ "$found_net" = 0 ] && echo "  no 192.168.7.x interface"

echo
echo "=== 4. is the board answering? ==="
if ping -c 1 -W 1500 192.168.7.1 >/dev/null 2>&1; then
    echo "  *** 192.168.7.1 IS UP - connect with:  ssh debian@192.168.7.1   (pw tmppwd)"
else
    echo "  192.168.7.1 not answering (expected on macOS - RNDIS unsupported)"
fi

echo
echo "=== 5. board on the LAN via Ethernet? ==="
# The OSD32MP1 Ethernet MAC comes from the Octavo/ST pool. Rather than guess
# OUIs, look for hosts that answer SSH and are not already known - cheap and
# reliable on a small LAN.
LAN=$(ipconfig getifaddr en0 2>/dev/null || ipconfig getifaddr en1 2>/dev/null)
if [ -n "${LAN:-}" ]; then
    SUB=$(echo "$LAN" | cut -d. -f1-3)
    echo "  scanning $SUB.0/24 for port 22 (a few seconds)..."
    if command -v nmap >/dev/null 2>&1; then
        nmap -n -p22 --open -T4 "$SUB.0/24" 2>/dev/null \
          | awk '/Nmap scan report/{ip=$NF} /22\/tcp *open/{print "    ssh-capable: " ip}'
        echo "  (try:  ssh debian@<address>   password tmppwd)"
    else
        echo "  (install nmap for the scan: brew install nmap)"
    fi
else
    echo "  no LAN address on en0/en1"
fi

echo
if [ "${found_booted:-0}" = 1 ] && [ "$found_net" = 0 ]; then
    cat <<'EOT'
=== VERDICT: board is BOOTED, but macOS will not use its USB network ===
The gadget is present and Linux is running (HRTBT blinking confirms it). The
problem is protocol, not hardware: the STM32MP1 gadget presents **RNDIS**,
which is a Microsoft protocol that **macOS does not support at all**. macOS
speaks CDC-ECM / CDC-NCM only, so it enumerates the device and then binds no
driver to any function - which is exactly what ioreg shows (no child
interfaces). Linux and Windows hosts would get 192.168.7.1 here; a Mac never
will, with the stock gadget config.

USE ETHERNET INSTEAD (fastest route in):
  1. Plug the board's 1Gbit Ethernet port into your router/switch.
  2. Re-run this script - it scans the LAN for the new host.
  3. ssh debian@<address>   (password: tmppwd)

Then, ONCE YOU HAVE A SHELL, you can switch the gadget to CDC-ECM so USB
networking works on macOS too - on the board:
    sudo sed -i 's/rndis/ecm/g' /etc/default/usb-gadget   # path varies by image
  or drive it via configfs / systemd unit, then reboot.

Other options if Ethernet is not available:
  - UART console at 115200 on the board's serial header (needs a USB-TTL
    adapter; the USB-C port does NOT provide a serial console here - no
    /dev/cu.usb* was created).
  - HDMI + USB keyboard: the image is Debian LXQt, so it has a desktop.
EOT
elif [ "$found_dfu" = 1 ] && [ "$found_net" = 0 ]; then
    cat <<'EOT'
=== VERDICT: board is in ROM USB-BOOT (RECOVERY) mode, NOT running Debian ===
The STM32MP1 ROM exposes DFU when it cannot (or is not told to) boot from
eMMC. Debian would instead appear as an RNDIS network gadget at 192.168.7.1.

Fix, in order:
  1. Set the 3-bit boot switch beside the USB host port to 0,1,0 (eMMC).
     All-zeros selects USB/UART recovery, which is what this is.
  2. Power-cycle the board (DFU state persists across a mere replug).
  3. Re-run this script - expect a 192.168.7.x interface within ~30s of boot.

If it STILL lands in DFU after that, the eMMC image is likely missing or
corrupt, and the board needs reflashing with STM32CubeProgrammer (or
dfu-util driven by the image's flashlayout.tsv). Do NOT write to these DFU
partitions blind - a wrong FSBL write is how these boards get bricked.
EOT
elif [ "$found_usb" = 0 ] && [ "$found_net" = 0 ]; then
    cat <<'EOT'
=== VERDICT: board not visible ===
Work through these in order - the first two account for most cases:
  1. Swap the USB cable for one you KNOW carries data (e.g. the cable you use
     for an external SSD). Charge-only cables are the usual culprit.
  2. Power it from the barrel jack (5V, >=2A) instead of the USB bus, then
     reconnect USB for data.
  3. Plug the USB-C directly into the Mac, not through a hub.
  4. Check the 3-bit boot switch by the USB host port = 0,1,0 (eMMC).
  5. Watch the board's power/user LEDs - no LED activity means it is not
     booting, which is a power or boot-switch problem, not a host problem.
EOT
fi
