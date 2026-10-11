# OPLink Mini / PipXtreme on this tree

The OPLink Mini (board type 0x03, STM32F103CB, RFM22B radio) is the 433 MHz
telemetry modem for the flight controllers in this tree.  One modem is the
*coordinator* on the ground (GCS over USB), the other the *remote* on the
vehicle (its main port on the flight controller's telemetry UART).  A
PipXtreme is the same board under its first name and takes the same firmware.

Everything below was done on 2026-10-11 from a Mac with four modems on USB,
without the GCS uploader: the bootloader protocol and the pairing live in two
Python tools.

## Build

    make fw_oplinkmini          # build/fw_oplinkmini/fw_oplinkmini.opfw (~58 KB of the 100 KB bank)

Three things had to be fixed for the F1 target to build and run again after
the tree's FreeRTOS 8 -> 11 upgrade and the move to GCC 13:

* `firmware/Makefile` carries the same GCC 13 warning block as the Cube Purple
  target (`-Wno-address-of-packed-member`, `-fno-strict-aliasing`, ...) and
  turns `-Wunsuffixed-float-constants` back off after `common-defs.mk` enables it.
* `heap_1.c` is the OpenPilot flavour again (restored from before the
  upgrade): the F1 startup code (`Stack_Change` in `startup_stm32f10x_*.S`)
  donates the early-init stack to the heap through `xPortIncreaseHeapSize`,
  which stock FreeRTOS does not have.  `portmacro.h` (ARM_CM3) gained the
  `portBYTE_HEAP_ALIGNMENT` define that file needs, as the tree's own
  `howto_upgrade.txt` describes.
* `MODULES += FirmwareIAP`: the modem now answers the GCS "Halt" sequence
  (FirmwareIAPObj 1122 / 2233 / 3344) and reboots into its bootloader, so
  reflashing and applying saved settings no longer needs a replug.  Because a
  modem relays every FirmwareIAPObj towards the flight controller behind it, it
  only obeys the sequence when `BoardType` is its own (3); the GCS sends 0 for
  the flight controller (`PIOS_IAP_OWN_BOARD_TYPE_ONLY` in `pios_config.h`,
  guard in `flight/modules/FirmwareIAP/firmwareiap.c`, and the USB-side case in
  `RadioComBridge.c` that receives the object locally *and* relays it).

## Flashing: `ground/pyuavtalk/opdfu.py`

The OpenPilot USB bootloader protocol (the GCS uploader's `op_dfu`) in
Python over hidapi, for any board that runs that bootloader:

    opdfu.py list                                  # +FW / +BL devices on USB
    opdfu.py --serial 51FF7006 --board-type 3 halt # firmware -> bootloader (this tree's firmware)
    opdfu.py flash build/fw_oplinkmini/fw_oplinkmini.opfw --serial 51FF7006 --board-type 3
    opdfu.py rescue IMAGE.opfw --count 3 --skip 51FF7006   # for firmware without FirmwareIAP: replug each board
    opdfu.py --serial 51FF7006 info --jump         # capabilities, then boot the firmware
    opdfu.py jump --erase-settings --wait 60       # boot with the settings-erase command (bootloader >= v4)

What the protocol needs that is easy to get wrong:

* A freshly powered bootloader sits in `BLidle` for 6 s with an *empty*
  device table and silently ignores `EnterDFU`.  Send `Abort_Operation`
  (forces `DFUidle`) and `Req_Capabilities` (fills the table) first, as the
  GCS rescue does; `enter_dfu()` loops on that until the status leaves `idle`.
* Data words go out byte-reversed, 14 words per 64-byte report; the CRC is the
  STM32 hardware CRC over the whole code bank padded with 0xFF, and the
  bootloader checks it itself at `Op_END`.  The 100-byte description at the end
  of the `.opfw` is uploaded separately (transfer type 1).
* Halting a board by its own `BoardType` makes the FirmwareIAP module refresh
  the object on every write with a stale `crc`; that self-update re-enters the
  state machine and cancels the sequence.  The tool reads the object once and
  echoes its `crc`, so the three commands arrive alone.
* Bootloader **v2** (2012 boards) reports a 117660-byte code bank: its memory
  map predates the 16 KB settings area, so a flash erases the saved settings
  and the firmware description lands inside the settings area.  Bootloader
  **v4** reports 102300 bytes and leaves settings alone; use
  `jump --erase-settings` when a board must start from defaults.  v2 ignores
  that command.
* macOS lists one HID entry per collection; `enumerate_boards()` dedupes by
  serial, otherwise the second open of the same board fails.

## Pairing: `flight/targets/boards/oplinkmini/tools/oplink_pair.py`

    oplink_pair.py status                          # identity, settings, link, pair table of every modem
    oplink_pair.py pair --power 1.25 --speed 57600 --coordinator 51FF7006
    oplink_pair.py --serial 49FF6E06 configure --coord-id 0x08C17BA1 --power 1.25 --speed 57600 --main Telemetry --save
    oplink_pair.py watch --seconds 30              # LinkState / quality / rates / who it hears, both modems
    oplink_pair.py --serial 49FF6E06 snoop --seconds 40   # catch a modem that only lives a few seconds after boot

Settings are read once at boot (`pios_board.c`), so `configure --save` and
`pair` finish with a FirmwareIAP halt and a bootloader jump.  Quit the GCS
first: it grabs every OpenPilot HID device on arrival, and only one holder works.

What "paired" looks like in `OPLinkStatus` (stock 15.02 driver semantics):

* the **remote** says `LinkState = Connected` and lists the coordinator's
  `DeviceID` in `PairIDs` with its RSSI;
* the **coordinator never says Connected**: `pios_rfm22b.c` only sets that
  state on a non-coordinator.  It stays `Enabled` and shows the remote's
  packets in its pair table (the id there is its own, because remotes address
  packets to the coordinator's id).  `watch` treats a heard pair as linked.
* a remote that cannot hear its coordinator re-initialises its radio every
  150 ms (`PIOS_RFM22B_SUPERVISOR_TIMEOUT`), so `Resets` climbs at ~6.7/s.
  That stops the moment the coordinator is in range; it is not a fault.
* `MaxRFPower = 0` (the default) leaves the radio off: `DeviceID`, heap and
  `PairIDs` are then not filled (`0`, `0`, `0xA5A5A5A5`), which looks broken
  and is not.

LEDs: green = USB; blue = link (lit on a connected remote, used as heartbeat
otherwise); orange = radio traffic.  A linked pair shows green+blue+orange on
the remote and green+orange on the coordinator.

## Bench result

| modem | serial | bootloader | role | result |
|---|---|---|---|---|
| OPLinkMini | 51FF7006... | v2 | coordinator, 1.25 mW, 57600, ch 0..250 | `Enabled`, hears the remote at -76 dBm |
| OPLinkMini | 49FF6E06... | v4 | remote, CoordID 0x08C17BA1, MainPort Telemetry | `Connected`, hears the coordinator at -73 dBm |
| PipXtreme | 51FF6D06... | v2 | flashed, defaults | not yet paired |

The remote's main port is set for the Cube Purple's TELEM1 (`RV_TelemetryPort
= Telemetry`, 57600): TX, RX, GND and 5 V between the two, then the GCS talks
to the Cube through the coordinator's USB.

## In the GCS (2026-10-11)

* **A modem with no flight controller behind it jumps to Configuration -> OPLink.**
  The GCS telemetry layer only passed OPLinkSettings and ObjectPersistence to a
  modem that never completes the handshake; it now also passes OPLinkLinkTest
  and FirmwareIAPObj (`telemetry.cpp`), so the page can test the link and
  reboot the modem.
* **Link test** on the OPLink page: 20 `OPLinkLinkTest` requests go through the
  connected modem; the modem at the far end of the radio answers each one
  (`RadioComBridge.c`) with its identity, link state and settings, so the page
  shows round trips, loss, RTT and the far modem's configuration.  No flight
  controller needed.  Firmware echo at 57600 measures ~35 ms per round trip.
* **Two or more modems on USB: the OPLink entry becomes the modems page.**
  Every modem gets a panel (status, role, pair table with RSSI, firmware, the
  settings form, Apply / Save / Reboot / Test link) and an "include" box;
  *Auto-configure* makes one the coordinator (the GCS's own modem unless you
  pick one) and binds every other checked modem to it as a remote, same power,
  speed and channels, Main port = Telemetry, Flexi and VCP off, then saves and
  reboots them all.  The modem the GCS is connected to keeps using that
  connection; the others get a private UAVTalk session over their own HID
  (`oplinkmodemswidget.cpp`).  Hot-plugging rebuilds the panels.
* **Boards of one kind are told apart** in the Connections box (`USB: OPLinkMini
  2387`), and the HID layer opens the board with the requested serial through
  the USB monitor's device reference instead of "the first one hidapi finds"
  (`ophid.cpp`, `hid_open_ref` in the bundled hidapi): the old behaviour always
  opened the same modem and failed while the GCS held it.
* Modem reboot from the GCS or the tools is `FirmwareIAPObj` 1122 / 2233 /
  **4455** (a plain reset back into the firmware); 3344 still parks the modem in
  its bootloader for a flash.  The IAP module ignores a repeated identical
  command (its own description refresh re-enters the callback), and a
  FirmwareIAPObj *read* over USB is answered by the near modem only.

Traps met on the way: the GCS telemetry transmits a settings object the moment
`setData` runs and ignores a second write while that one is in flight, so a
page must build the whole `DataFields` and write it once; a panel must not mark
its settings "seen" before the modem has sent them.

## What a coordinator is (stock 15.02 radio protocol)

One coordinator per network.  Its Device ID seeds the frequency-hopping
sequence (`rfm22_gen_channels`) and its clock is the time base; remotes bind to
that ID, synchronise to its packets and report `Connected`.  Each hop period is
split in two: the coordinator transmits in the first half, *every* remote in
the second (`rfm22_timeToSend`).  Consequences:

* the coordinator's downlink is a broadcast all remotes hear (PPM, GCS traffic);
* several remotes share one uplink slot and contend for it, so a second or
  third remote costs the others their uplink air time (no per-remote slots);
* no meshing or relaying: a remote that cannot hear the coordinator is simply
  disconnected (and re-initialises its radio every 150 ms until it can);
* nothing is routed per node: the GCS's objects reach every remote's main port,
  every remote's objects come back to the coordinator.
