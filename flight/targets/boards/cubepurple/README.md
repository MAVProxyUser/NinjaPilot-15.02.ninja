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

## Bring-up aids (off by default)

The board has no console.  Two knobs, passed as `CUBE_CDEFS=...` on the
make line, replace it:

* `-DCUBE_BOOT_STOP=n` resets into the bootloader at init stage n (stages
  100/101/102 in main, 1..9 through `PIOS_Board_Init`).  The bootloader's
  own USB device appearing and staying is the signal, so this works before
  the firmware's USB exists.
* `-DCUBE_MARKS=1` programs progress markers into spare internal flash at
  0x080FFF00 (one word per slot): boot progress, reset cause (slots 36-39),
  a fault handler that records the faulting PC (slot 29/30 + 40-58), and a
  tick-hook hang catcher that fires when the watchdog flags stop changing
  for 200 ms (slot 29, kicked flags in 59-63, interrupted PC in 40-58).
  `tools/blcrc.py fw.apj --cycle --solve` asks the bootloader for the
  flash CRC and solves the slots from it (the CRC is linear over GF(2)).
  The bootloader erases the region on every flash.

## What it took (for the next port)

* The ArduPilot bootloader hands over from a ChibiOS thread: in thread mode,
  on its process stack, with USB/UART/timer interrupts still enabled and
  pending.  `_main` (stm32f4xx/startup.c) now switches to the vector-table
  main stack first thing; `main()` here stops SysTick and clears every NVIC
  enable/pending bit before the kernel starts.
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
