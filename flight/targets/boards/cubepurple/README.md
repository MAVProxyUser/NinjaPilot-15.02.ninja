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

**GPS connector.** HwSettings RV_GPSPort = GPS is the Cube's **GPS 1**
connector (UART4).  GPS 2 is UART8, which the STM32F4 USART driver in this
tree does not drive (USART1-6 and UART4/5 only), so a receiver on GPS 2 is
invisible to the firmware whatever the speed setting says.  Move it to
GPS 1, or add UART7/8 to `pios_usart.c` and a GPS2 port option.

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
