# PixRacer (FMUv4) target

mRo / AUAV PixRacer R12, STM32F427VIT6, 24 MHz HSE, 168 MHz. Same MCU and the
same PX4-bootloader flash layout as the Cube Purple target, so it links at
`0x08004000` and ships as a `.apj` the stock PX4 bootloader flashes
(`PX4_BOARD_ID = 11`, `BOARD_TYPE 0x0B`).

## Status (2026-10-25)

**Builds** from a clean tree with `arm-none-eabi-gcc` 13.3 (`make fw_pixracer`
through a space-free path, like the other F4 targets), producing
`fw_pixracer.apj` (board id 11). Ported from the PixracerOpenPilot fork's
`pixracer-port` branch, which brought the board up to *telemetry over USB*.
That fork is the **same OpenPilot 15.02 lineage** as this tree, on the official
`RELEASE-15.02.02` tag (plus 2025 Qt6/Python-3 build-compat commits);
NinjaPilot branched earlier in the same series (`fe04a9b6`, pre-CC3D-removal).

It carries the bring-up module set it was developed with - FirmwareIAP +
Telemetry + System - not the full Revolution flight stack. As with the Cube
Purple before it, growing it to a full flight firmware is a
hardware-in-the-loop follow-on.

### What the port needed (and how it was resolved)

Everything that differs from this tree's PiOS was handled without disturbing
the other boards:

- **Invensense IMU** - the fork's `pios_invensense.c` is a *superset* of this
  tree's (it drives the second IMU, the ICM-20608/20602, a DRDY EXTI and a
  `pios_invensense_t` handle). It is carried as the Pixracer target's own copy
  (`firmware/pios_invensense.c` + `firmware/inc/pios_invensense.h`, put first
  on this target's include path via `EXTRAINCDIRS += inc`), so the Cube Purple
  target keeps its flight-proven single-IMU copy untouched.
- **USB `vsense_ignore`** - added to this tree's shared `pios_usb` (one bool,
  defaults false, so no other board changes behaviour).
- **LED** - adapted from the fork's `pios_led_cfg {leds,num_leds}` to this
  tree's generic `pios_gpio_cfg {gpios,num_gpios}`.
- **HMC5983 / MS5611 / DSM** - this tree already has the same drivers; the
  board files just needed the explicit includes and this tree's init
  signatures (no `spi_prescaler` on MS5611, no protocol arg on `PIOS_DSM_Init`).
- **UART7** - this tree's F4 CMSIS predates the F427 and omits the `UART7_IRQn`
  enum, though the F427 startup and `vectors_stm32f4xx.c` already wire the
  vector slots (IRQ 82/83); defined for this board only in `board_hw_defs.c`.
- **CMSIS system source** - a `Source/pixracer/system_stm32f4xx.c` was added
  (identical F427 24 MHz/168 MHz clock as the Cube Purple).

### Not hardware-verified, and sensors are staged OFF

This has **not** been flashed to a PixRacer in this tree. The bring-up's own
`PIXRACER_ENABLE_SENSORS` is left undefined, exactly as it was on the fork:
the two IMU data-ready EXTIs and the sensor probe stay off until the board is
confirmed to enumerate and talk over USB, because every hang during the fork's
bring-up was at or after the sensor probe. The sensor drivers and their configs
are all in place; turning that macro on is the first thing to do with a board
on the bench.

## Why it is a hand port, not a git merge

`../PixracerOpenPilot` is the **same OpenPilot 15.02 lineage** as this tree
(based on the official `RELEASE-15.02.02` tag), but it keeps the stock
OpenPilot directory layout (`flight/PiOS`, `flight/targets/Pixracer/System`)
whereas this tree was restructured (`flight/pios`,
`flight/targets/boards/<board>`), and some of its board drivers are fork-local.
Those differences, not a different upstream, are why it cannot be git-merged;
the board is brought across by hand, which is what this directory is.
