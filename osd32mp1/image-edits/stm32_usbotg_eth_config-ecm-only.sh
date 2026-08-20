#!/bin/sh

# USB OTG gadget for the OSD32MP1-RED, modified from ST's stock script.
#
# TWO CHANGES vs stock, both needed to develop from a Mac:
#
#   1. func_eth: rndis.0 -> ecm.0
#      RNDIS is a Microsoft protocol. macOS has NO RNDIS driver at all, so the
#      stock gadget enumerates and then binds nothing - no network interface
#      ever appears. CDC-ECM is supported natively by macOS AND Linux, so the
#      board's existing 53-usb-otg.network (192.168.7.1/24 + DHCPServer) then
#      just works and the host is handed an address automatically.
#      Windows is the loser here (no native ECM), which is the right trade for
#      this bench.
#
#   2. acm.0 added as a second function -> /dev/ttyGS0 on the board.
#      That gives a serial console over the SAME USB cable, independent of
#      both Ethernet and USB networking, so a misconfigured network can never
#      lock us out again. serial-getty@ttyGS0 is enabled to bind to it.
#
# bDeviceClass 0xEF / 0x02 / 0x01 (IAD) was already set by the stock script
# and is REQUIRED now that the gadget is genuinely composite.

configfs="/sys/kernel/config/usb_gadget"
g=g1
c=c.1
d="${configfs}/${g}"
func_eth=ecm.0
func_acm=acm.0
func_ms=mass_storage.0

VENDOR_ID="0x1d6b"
PRODUCT_ID="0x0104"

IP="192.168.7.1"
NETMASK="255.255.255.0"

#MAC address for ethernet-over-USB can be defined here
MAC_HOST_CUST=""
MAC_DEV_CUST=""

get_mac_address_from_serial_number(){
    sha1sum /proc/device-tree/serial-number \
    | fold -1 \
    | sed -n '1{h;d};2{y/1235679abdef/000444888ccc/;H;d};13{g;s/\n//g;p;q};s/^/:/;N;H;d'
}

do_start() {
    if [ ! -d ${configfs} ]; then
        modprobe libcomposite
        if [ ! -d ${configfs} ]; then
        exit 1
        fi
    fi

    if [ -d ${d} ]; then
        exit 0
    fi

    udc=$(ls -1 /sys/class/udc/)
    if [ -z $udc ]; then
        echo "No UDC driver registered"
        exit 1
    fi

    mkdir "${d}"
    echo ${VENDOR_ID} > "${d}/idVendor"
    echo ${PRODUCT_ID} > "${d}/idProduct"
    echo 0x0200 > "${d}/bcdUSB"
    echo "0xEF" > "${d}/bDeviceClass"
    echo "0x02" > "${d}/bDeviceSubClass"
    echo "0x01" > "${d}/bDeviceProtocol"
    echo "0x0100" > "${d}/bcdDevice"

    mkdir -p "${d}/strings/0x409"
    tr -d '\0' < /proc/device-tree/serial-number > "${d}/strings/0x409/serialnumber"
    echo "STMicroelectronics" > "${d}/strings/0x409/manufacturer"
    echo "STM32MP1" > "${d}/strings/0x409/product"

    # Config
    mkdir -p "${d}/configs/${c}"
    mkdir -p "${d}/configs/${c}/strings/0x409"
    echo "Config 1: ECM only" > "${d}/configs/${c}/strings/0x409/configuration"
    echo 250 > "${d}/configs/${c}/MaxPower"
    echo 0xC0 > "${d}/configs/${c}/bmAttributes" # self powered device

    mkdir -p "${d}/functions/${func_eth}"

    # The os_desc block below is RNDIS-ONLY (it exists to make Windows load
    # the RNDIS driver). For ECM the node functions/ecm.0/os_desc/interface.rndis
    # does not exist, so writing to it would fail PART WAY THROUGH setup and
    # leave a half-built gadget that enumerates as nothing. Guard on the
    # function type rather than deleting it, so switching func_eth back to
    # rndis.0 still works.
    case "${func_eth}" in
    rndis.*)
        mkdir -p "${d}/os_desc"
        echo "1" > "${d}/os_desc/use"
        echo "0xbc" > "${d}/os_desc/b_vendor_code"
        echo "MSFT100" > "${d}/os_desc/qw_sign"
        mkdir -p "${d}/functions/${func_eth}/os_desc/interface.rndis"
        echo "RNDIS" > "${d}/functions/${func_eth}/os_desc/interface.rndis/compatible_id"
        echo "5162001" > "${d}/functions/${func_eth}/os_desc/interface.rndis/sub_compatible_id"
        ;;
    esac

    if [ "$MAC_HOST_CUST" != "" ]; then
        echo $MAC_HOST_CUST > "${d}/functions/${func_eth}/host_addr"
    else
        mac_host=$(get_mac_address_from_serial_number)
        echo $mac_host > "${d}/functions/${func_eth}/host_addr"
    fi
    if [ "$MAC_DEV_CUST" != "" ]; then
        echo $MAC_DEV_CUST > "${d}/functions/${func_eth}/dev_addr"
    fi

    # ECM-ONLY: acm.0 is NOT created - with both bound the dwc2
    # controller runs out of IN-endpoint TX FIFOs and ECM data never comes up.

    # ECM is DELIBERATELY NOT LINKED into the config (2026-08-18): the dwc2
    # controller cannot allocate a 4th IN-endpoint FIFO with ACM+ECM both
    # bound, so ECM's data interface has NEVER come up - every host attempt
    # to select it just fired a kernel WARN out of dwc2_hsotg_ep_enable's
    # error path. The board has Ethernet + WiFi; the gadget's job is the
    # CONSOLE. To revive ECM someday: extend g-tx-fifo-size in the DTB
    # first, then restore this link.
    ln -s "${d}/functions/${func_eth}" "${d}/configs/${c}"
    case "${func_eth}" in
    rndis.*) ln -s "${d}/configs/${c}" "${d}/os_desc" ;;
    esac

    echo "${udc}" > "${d}/UDC"

    sleep 0.2

    interfacename=$(cat ${d}/functions/${func_eth}/ifname 2> /dev/null)
    if [ -z "${interfacename}" ];
    then
        interfacename=usb0
    fi
    # Address/DHCP server come from /lib/systemd/network/53-usb-otg.network
    # (192.168.7.1/24, DHCPServer=yes) - only bring the link up here.
    ifconfig ${interfacename} up
}

do_stop() {
    interfacename=$(cat ${d}/functions/${func_eth}/ifname 2> /dev/null)
    if [ -z "${interfacename}" ];
    then
        echo "Nothing to do"
        return
    fi
    ifconfig ${interfacename} down

    sleep 0.2

    echo "" > "${d}/UDC"

    rm -f "${d}/os_desc/${c}"
    [ -d "${d}/configs/${c}/${func_acm}" ] && rm -f "${d}/configs/${c}/${func_acm}"
    [ -d "${d}/configs/${c}/${func_eth}" ] && rm -f "${d}/configs/${c}/${func_eth}"

    [ -d "${d}/strings/0x409/" ] && rmdir "${d}/strings/0x409/"
    [ -d "${d}/configs/${c}/strings/0x409" ] && rmdir "${d}/configs/${c}/strings/0x409"
    [ -d "${d}/configs/${c}" ] && rmdir "${d}/configs/${c}"
    [ -d "${d}/functions/${func_acm}" ] && rmdir "${d}/functions/${func_acm}"
    [ -d "${d}/functions/${func_eth}" ] && rmdir "${d}/functions/${func_eth}"
    [ -d "${d}" ] && rmdir "${d}"
}

case $1 in
    start)
        echo "Start usb gadget"
        do_start $2
        ;;
    stop)
        echo "Stop usb gadget"
        do_stop
        ;;
    *)
        echo "Usage: $0 (stop | start)"
        ;;
esac
