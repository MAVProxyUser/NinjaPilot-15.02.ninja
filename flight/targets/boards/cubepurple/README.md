# CubePilot Cube Purple (FMUv3) on this tree

STM32F427 at 168 MHz from a 24 MHz crystal, MPU9250 (gyro/accel + AK8963
compass) and MS5611 on SPI1, FRAM on SPI2 for settings, an IO co-processor
on USART6 for MAIN OUT 1-8 and RC IN, AUX OUT 1-5 on TIM1/TIM4, TELEM1 on
USART2, TELEM2 on USART3, the GPS connector on UART4, USB HID+CDC.  Board
type 0x0C, revision 1 (`getBoardModel()` = 0x0C01).

## Building and flashing

    make fw_cubepurple                # build/fw_cubepurple/fw_cubepurple.apj

The board keeps its ArduPilot bootloader (16 KB at 0x08000000, .apj board
id 9); the firmware links at 0x08004000 with the board-info blob inline and
is wrapped as an .apj.  Never write the bootloader or the IO firmware.
Flash with ArduPilot's uploader while the bootloader listens (~5 s after
power-up):

    tools/flash.sh build/fw_cubepurple/fw_cubepurple.apj    # arms uploader.py, power-cycles via uhubctl

Set `UPLOADER=` to `Tools/scripts/uploader.py` of an ArduPilot checkout if it
is not in `../lineage/ardupilot`, and `HUB`/`HUB_PORT` to the board's
uhubctl location.  The GCS uploader gadget cannot flash this board (no
OpenPilot DFU bootloader); telemetry, configuration and the setup wizard
work over `USB: CubePurple` (HID).  The virtual serial port is disabled
by default (HwSettings USB_VCPPort).

When something else powers the board as well (a CAN BEC back-feeds the
5 V rail through the CAN port), a USB power cycle does not reset it, and a
plain soft reset is no use either: the bootloader boots the application
straight back after one (0.35 s USB gap, no window).  Use the IAP route:

    FLASH_REBOOT=iap tools/flash.sh build/fw_cubepurple/fw_cubepurple.apj

It sends FirmwareIAP 1122/2233/6677 (`tools/iap_reboot.py --hold`): the
third step is the tree's STEP_3 with a board hook that leaves the
bootloader's "hold" signature in RTC BKP0R, so the bootloader waits for the
uploader (its own USB device, 2dae:1005, appears and stays) and boots the
new firmware when it is done.  Two things had to be handled for that to
work, both in `cube_bootloader_hold()`: the bootloader's HAL resets the
whole backup domain when the RTC clock source is not the LSI it configures
(PIOS_RTC_Init selects HSE/24), which wiped the signature before it was
read, so the hook restores the source the bootloader left at boot; and the
reset-cause flags in RCC_CSR are sticky until a power-on and the bootloader
boots the application at once after any watchdog reset, signature or not,
so the hook clears them.  The firmware on the board must already have the
hook (commit d9272ee75 or later); before that, cut the other supply once
and use the USB path.  The GCS reboot (1122/2233/3344) is unchanged: it
comes back as the application.

## DroneCAN on CAN2

CAN2 (PB12/PB6, 1 Mbit/s) runs a small DroneCAN v0 node (`MODULE DroneCAN`,
`flight/modules/DroneCAN`): it broadcasts NodeStatus (node id 10), answers
dynamic node-id allocation for anonymous nodes, keeps a census of the
nodes it hears (`DroneCANStatus`: counters, error counters, bus-off, node
table with health/mode/uptime, the first eight data type ids seen with
frame counts) and decodes `uavcan.equipment.esc.Status` (1034) into
`DroneCANESCStatus` (one row per ESC node, with the index each reports) and
keeps the ESCs' last LogMessage in `DroneCANLog` (its own object: the GCS
drops any UAVTalk payload over 256 bytes, and the status had grown past
that).

**The flight path.** ActuatorSettings ChannelType `DroneCAN` makes the
actuator module hand a channel to the CAN module instead of a PWM pin:
ChannelMin..ChannelMax (us) maps to esc.RawCommand 0..8191, the element is
ChannelAddr, and one RawCommand goes out per actuator update (500 Hz here)
with zeros while disarmed, so the ESC applications stay up.  ArmingStatus
FULLY_ARMED goes out when the board is armed or when the operator has taken
the outputs over (ActuatorCommand read-only: the GCS Output tab and the
wizard's motor test); otherwise DISARMED, and the AM32s will not run.  The
setup wizard treats a Cube Purple as "DroneCAN ESCs on CAN2": no ESC page,
no ESC calibration page, the motor channels come out of the wizard as
DroneCAN 1000/2000 us.  Verified on the bench through the wizard's own
read-only output path, one motor per element, about 3700 rpm at 1100 us.

`DroneCANESCCommand` is a bench tool, not the flight path (it yields
whenever the actuator is streaming): while Enabled the module broadcasts
`uavcan.equipment.esc.RawCommand` (1030) with its values at Rate Hz and
falls back to zeros when nobody refreshes it for 2 s;
`tools/esc_test.py` uses it to spin the motors one at a time (no props)
and prints the telemetry that comes back.  `DroneCANParam` is a one-shot
parameter client (GetSet, ExecuteOpcode, GetNodeInfo, a Raw payload for
experiments) behind `tools/esc_params.py` (nodes, list, get, set, save,
assign).  CAN1 is not brought up.

What the Vimdrones S50 (AM32 2.20, `com.vimdrones.esc_s50`) does on this
bus, all measured here:

* At rest it sits in its DroneCAN bootloader (`AM32_BOOTLOADER_L431` 16.0,
  NodeStatus mode Maintenance, log "no signal"), which answers GetNodeInfo
  but has no parameters.  The application starts about 3 s into a
  RawCommand stream, allocates a node id of its own (so ids change at
  every transition; the bootloader and application both take one), reports
  Operational, sends esc.Status at TELEM_RATE (25 Hz), and hands back to the
  bootloader a few seconds after the stream stops.  Parameter work therefore
  needs the stream running, which esc_params.py does.
* REQUIRE_ARMING is on by default: it only runs after hearing
  uavcan.equipment.safety.ArmingStatus FULLY_ARMED, and it wants a second
  of zero throttle after its application starts before it arms.
* All four shipped with ESC_INDEX 0 (every one obeys RawCommand element 0
  and their names all read #M1).  `esc_params.py 0 assign` gave them 0..3
  in ascending node-id order and saved it; the names then read #M1..#M4
  and each element drives one motor.
* Parameter encoding: a GetSet request is accepted with the 3-bit Value
  tag the v0 spec describes; the responses carry byte-wide union tags.
  The client encodes and decodes exactly that.
* Current telemetry has 10 mV/A resolution (0.07 A steps); rpm is
  electrical rpm scaled by the ESC's MOTOR_POLES setting.

**GPS connectors.** HwSettings RV_GPSPort is the 8-pin **GPS 1** connector
(UART4); `CUBE_GPS2Port` is the 6-pin **GPS 2** connector (UART8, PE0/PE1),
with the same functions (GPS, Telemetry, ComBridge).  UART7/8 were added to
`pios_usart.c` and to the vector table for this (the CMSIS header in the
tree stops at the F40x interrupt set; the F427's UART7/8 are vectors 82/83,
defined in `board_hw_defs.c`).  The wizard puts a serial GPS on GPS 2 and
leaves GPS 1 disabled, at 230400 UBX with UbxAutoConfig Configure.  The
GPS module has no auto-baud, so HwSettings.GPSSpeed must match the
receiver: the Matek M9N-5883 here talks 230400 (u-blox receivers that have
run under ArduPilot are left there), and with that it gives a 3D fix on
the bench.  To find a receiver's speed, set CUBE_GPS2Port and USB_VCPPort
to ComBridge and read the USB serial port on the host at each
ComUsbBridgeSpeed (that bridge stops at 115200, so 230400 has to be tried
through the GPS module itself).

## Building the GCS for this tree

The recipe in the repository notes applies (qmake straight from
`ground/openpilotgcs/openpilotgcs.pro`, an empty `opfw_resource.qrc`,
`make uavobjects_gcs` first).  Two things bit here: a fresh checkout lacks
`ground/openpilotgcs/src/libs/eigen/Eigen/src/Core/util` (Eigen's own
`.gitignore` hides it on a case-insensitive filesystem; copy it from a
built tree), and a UAVObject over 256 bytes is silently dropped by the
GCS's UAVTalk ("incorrect packet size" in the log), so keep the objects
small.  The wizard was driven end to end over the automation port
(`NINJAPILOT_GCS_AUTOMATION=1`, `ground/pyuavtalk/gcs_client.py`; commands
take a `window` hint so a dialog stays addressable while the main window
has focus, and a client that gives up mid-command no longer crashes the
server).

**Spektrum satellite.** Plug it into the SPKT/DSM socket (3.3 V, the port
the IO co-processor can power-cycle); IO decodes DSM and serves it as the
PWM channel group, so no wizard choice is needed.  To bind:
`tools/dsm_bind.py` sets HwSettings DSMxBind, reboots the board (the
firmware then asks IO for its bind sequence: power-cycle, nine pulses),
waits and clears the setting again.  Put the transmitter in bind mode
before pressing Enter.

**Sensors alarm every 3-4 s (fixed).** With the MPU9250 at 500 Hz and the
sensors task at 500 Hz there was one sample per window, and the part's own
clock beat against the RTOS tick: every few seconds a window closed just
before its sample landed, the sensors task reset the IMU and tripped the
alarm.  The IMU now runs at 1 kHz (two samples per window): no trips, CPU
48 %.  DIAG_TASKS is off in the flight build for the same reason (the
task monitor suspends the scheduler; use CUBE_CDEFS=-DDIAG_TASKS to
measure stacks).

**GPS "NoGPS" with a receiver that is talking (fixed).** The UBX
auto-configuration gave up (INIT_STEP_ERROR) when the M9N rejected a
message it no longer supports (the deprecated NAV-SOL/SVINFO family), and
GPS.c folded that error into its "timed out" test, so a receiver with a 3D
fix showed NoGPS.  A NAK now just skips that message, and only silence on
the port means NoGPS; a failed auto-configuration is a GPS *warning*.

**GPS status flapping at 230400 (fixed).** With a 3D fix and 12+ satellites
the status still dropped to NoGPS every second or two: bytes were being
lost on UART8.  At 230400 a byte lasts 43 us, the F4 UART buffers exactly
one, and the port's interrupt sat at MID behind the IMU DMA, USB and
IO-link interrupts at HIGH, so every long packet failed its checksum and
the MON-VER reply the auto-config waits for (280 bytes on an M9N) never
got through - auto-config stuck RUNNING, NoGPS after any 500 ms without a
complete packet.  The GPS 2 UART interrupt is now HIGHEST (its handler is
a byte into a ring buffer), the receive buffer is 1 KB, and the parser
skips a message larger than its buffer instead of resetting mid-payload
(a false sync inside the leftover bytes used to jam it for seconds).
`GPSRxStats` (packets, checksum failures, oversize, resyncs, once a
second) shows the link's health; a rising checksum count with a fix means
lost bytes.

**System health panel, for the record:** the slot labelled CAN is the I2C
alarm, which the DroneCAN module now drives (green with live nodes, amber
when the error counters climb or the bus is empty, red when bus-off);
TIME is the battery module's remaining-flight-time estimate (not GPS time,
which lives in GPSTime); USB has no alarm behind it; MAG is the
Magnetometer alarm, lifted to OK by the sensors module as soon as the
compass delivers samples (the mag-using attitude filters own it after
that).  The GCS itself used to crash when the board vanished
for a flash (hidapi removal callback on a freed device; fixed in
`ophid/hidapi/mac/hid.c`).

## Bring-up aids (off by default)

The board has no console.  Two knobs, passed as `CUBE_CDEFS=...` on the
make line, replace it:

* `-DCUBE_BOOT_STOP=n` resets into the bootloader at init stage n (stages
  100/101/102 in main, 1..9 through `PIOS_Board_Init`).  The bootloader's
  own USB device appearing and staying is the signal, so this works before
  the firmware's USB exists.
* `-DCUBE_MARKS=1` programs progress markers (single-shot: slot 26 says a
  record exists, later boots stay quiet) into spare internal flash at
  0x080FFF00 (one word per slot): boot progress, reset cause (slots 36-39),
  a fault handler that records the faulting PC (slot 29/30 + 40-58), and a
  tick-hook hang catcher that fires when the watchdog flags stop changing
  for 200 ms (slot 29, kicked flags in 59-63, interrupted PC in 40-58), and
  a TIM6 catcher at NVIC priority 0 that fires when the kernel tick stops
  advancing, i.e. the CPU is stuck with SysTick masked (slot 29, PC in
  40-58, interrupted exception number in 59-63 + 27/30).  `-DCUBE_ASSERTS=1`
  on top routes `configASSERT` (and list integrity bytes) into the markers.
  `tools/blcrc.py fw.apj --cycle --solve` asks the bootloader for the
  flash CRC and solves the slots from it (the CRC is linear over GF(2)).
  The bootloader erases the region on every flash.

## What it took (for the next port)

* The ArduPilot bootloader hands over from a ChibiOS thread: in thread mode,
  on its process stack, with USB/UART/timer interrupts still enabled and
  pending.  `_main` (stm32f4xx/startup.c) now switches to the vector-table
  main stack first thing; `main()` here stops SysTick and clears every NVIC
  enable/pending bit before the kernel starts.
* GCC 13 miscompiles the FreeRTOS V11 kernel's pending-ready drain loop in
  `xTaskResumeAll` under strict aliasing when the list end is a mini list
  item: the head pointer is hoisted out of the loop, so with two tasks made
  ready while the scheduler was suspended (a telemetry connect burst does
  it) the loop never terminates inside its critical section and the
  watchdog resets the board 20-100 s later, always right after a GCS
  connect/disconnect.  `configUSE_MINI_LIST_ITEM 0` (the kernel's documented
  remedy) plus `-fno-strict-aliasing` for this GCC-4-era code base.
* 192 KB SRAM needs `HEAP_SUPPORT_LARGE`: msheap's default 15-bit block
  sizes cannot describe the heap, its "heap too large" assertion is a no-op,
  and the first allocation from the main heap bus-faulted.
* GCC 13 task/callback stacks: Stabilization 800, ManualControl 1200,
  Receiver 1000 bytes (measured with TaskInfo/CallbackInfo).
* GCS (macOS): the HID monitor matched every HID device and bailed out when
  `IOHIDManagerOpen` refused that; it now matches OpenPilot's vendor id only
  and survives a failed open.  The wizard's final reboot uses the
  bootloader-less path (IAP reset, wait for telemetry).
* Building the GCS from a fresh checkout needs two git-ignored directories
  copied from an existing tree: `ground/openpilotgcs/src/libs/qwt/designer`
  and Eigen's `Eigen/src/Core` (ignored by Eigen's own `.gitignore` rule
  `core` on a case-insensitive filesystem).

## Receiver on the Mini Carrier (2026-09-29 findings)

* The Mini Carrier has no SPKT/DSM socket. Its RC IN pin row is, by factory
  solder jumpers, the IO's PPM/S.Bus pulse input with the 5 V "RCIN power
  rail" on the middle pin. CubePilot's docs describe re-jumpering it for a
  Spektrum satellite: cut the two default links, bridge 3V3 to the power pad
  and SPKT to the signal pad. Only that configuration reaches the IO's DSM
  UART, so only that configuration makes the IO's bind sequence
  (`HwSettings.DSMxBind`, `tools/dsm_bind.py`) do anything.
* The servo rail (MAIN OUT +/-) is a separate rail; `IOMCUStatus.ServoRail`
  reading ~80 mV does not mean RC IN is unpowered.
* IO firmware built after 2020-08 decodes NO receiver protocol until the
  flight side writes the RC protocol allow-mask (PAGE_SETUP registers 23/24,
  bit 0 = all). ArduPilot's FMU always sends it; `pios_iomcu.c` now sends it
  in the handshake and `IOMCUStatus.RcMaskAck` reports whether the IO took
  it (older IO firmware rejects the register and needs no mask).
  `IOMCUStatus.ProtocolVersion2` dates the IO firmware.
* Spektrum channel order out of the IO decoder is 1 throttle, 2 roll,
  3 pitch, 4 yaw, 5 gear, 6 aux1; the ArduPilot DSM decoder scales sticks to
  about 1100..1900 us around 1500.

## Spektrum satellite: TELEM2, not RC IN (2026-09-29, verified)

* This Cube's IO co-processor runs the PX4IO-generation firmware
  (`IOMCUStatus.ProtocolVersion2` = 3; ArduPilot's ChibiOS IO answers 10).
  That generation decodes Spektrum only on its own DSM UART, never on the
  PPM pin, and it ignores the newer RC-protocol mask register. With the
  Mini Carrier's RC IN re-jumpered to SPKT it still delivered nothing, so
  the IO path is parked. `pios_iomcu.c` now decodes that generation's RC
  page layout (channels from register 6, RC OK = flags bit 4), drives its
  DSM register 7 (power-up at handshake, five-step bind), and reads the
  status page as before.
* What works: the satellite on **TELEM2** (pin 1 = 5 V, pin 3 = RX, pin 6 =
  GND), `HwSettings.RV_AuxPort = DSM`, channel groups `DSM (MainPort)`,
  decoded by the FMU's own driver (`pios_dsm`, `PIOS_INCLUDE_DSM`). The
  raw values are 11-bit (342..1706, centre 1024 on the test radio), not
  microseconds. Throttle neutral must sit above the minimum (372 vs 342)
  so idle reads negative, or the arming handler never sees "throttle low".
  Yaw came in reversed on this radio (min/max swapped). Arming = throttle
  low + yaw right for 1 s, verified from the transmitter.
* Motor tests once `ActuatorSettings.ChannelType` is DroneCAN: the actuator
  module streams RawCommand at 500 Hz whether armed or not, so the bench
  path (`DroneCANESCCommand`, `esc_test.py`, `can_ramp.py`) is out-voted.
  Use `tools/actuator_ramp.py` (ActuatorCommand in output-test mode, the
  GCS Output tab mechanism). Measured on the bench, no props, 4 x EMAX
  ECO II 2207: 4 % = 1780 rpm, 8 % = 3060, 12 % = 4300, 16 % = 5520,
  matched within 2 %; 0.5 A per ESC at 16 %; bus 300 rx / 520 tx frames/s,
  0 drops, TEC/REC 0, CPU 48 %. A 3 A bench limit sagged to 9.8 V at the
  16 -> 20 % step; the tool aborts below 11 V.
* Battery sweep (4S, no props, 10 % steps to full, `actuator_ramp.py --top
  2000 --step 100 --minvolts 12.5`): 10 % = 4.5 k, 20 % = 8.3 k, 30 % =
  11.8 k, 40 % = 15.3 k, 50 % = 18.6 k, 60 % = 21.7 k, 70 % = 24.9 k, 80 % =
  28.7 k, 90 % = 31.6 k, 100 % = 33.9 k rpm; 2.1 A per ESC and 8.5 A total at
  full, pack 14.6 -> 13.2 V, ESCs 39..46 C, zero errors, bus 800 frames/s
  (~11 % of 1 Mbit/s), CPU 47 %. Nothing on the bus or the ESCs limited it.

## GCS hardware page (2026-09-29)

`ConfigCubeHWWidget` replaces the Revolution page for board type 0x0C: the
Mini Carrier's photo with only its connectors around it (TELEM 1/2, GPS 1/2,
RC IN, USB; CAN 2, I2C 2 and MAIN OUT as notes), bound to the same HwSettings
fields the firmware reads. `tools/hwpage_check.py` scripts the check: page
values equal the board, TELEM1 changed and saved both ways, page rebuilt
after a disconnect/reconnect (the config gadget's "same board" guard used to
leave the placeholder page in place; fixed). `tools/gcs_shot.sh` captures the
GCS window by window id, never a screen region.

## Arming tune (2026-09-30)

`TuneSettings` (System category) picks a short motif the ESCs play when the
aircraft arms: Imperial March, Beethoven's 5th, Ode to Joy, Korobeiniki or
the ballpark "Charge". Two ways to play it, chosen by `ArmSource`:

* **ESCStartupMelody** (works with stock AM32): the tune is written into every
  ESC as its startup melody (AM32's `STARTUP_TUNE` string parameter, BlueJay
  layout: header, then (pulses, period) pairs, `(0,0)` ends it) together with
  `BEEP_VOLUME`, and saved there. Set `WriteESC = Write` once to do that;
  DroneCANLog reports each ESC. While disarmed the module then holds the
  RawCommand stream, so the AM32 application exits to its bootloader and
  starts, melody first, the moment the aircraft arms (or an output test takes
  the outputs). Cost: the arm-to-motor latency of that start-up.
* **BeepCommand**: each note goes out as `uavcan.equipment.indication.
  BeepCommand` (1080). AM32 2.20 does not implement it; other ESCs do.
* **Both**.

`flight/modules/DroneCAN/tunes.c` holds the note tables and the melody
encoder; `tools/np_tune_test.py` (scratch) writes the tune and times the
gated start.
