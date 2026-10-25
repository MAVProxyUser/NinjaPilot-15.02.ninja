# PixRacer (FMUv4) target — work in progress

mRo / AUAV PixRacer R12, STM32F427VIT6, 24 MHz HSE, 168 MHz. Same MCU and the
same PX4-bootloader flash layout as the Cube Purple target, so it links at
`0x08004000` and ships as a `.apj` the stock PX4 bootloader flashes
(`PX4_BOARD_ID = 11`, `BOARD_TYPE 0x0B`).

## Status (2026-10-24)

This target was **ported from the PixracerOpenPilot fork's `pixracer-port`
branch**, which brought the board up to *telemetry over USB*. That fork is the **same
OpenPilot 15.02 lineage** as this tree, on the official `RELEASE-15.02.02`
tag (plus 2025 Qt6/Python-3 build-compat commits); NinjaPilot branched earlier
in the same series (`fe04a9b6`, pre-CC3D-removal). The port onto this tree (NinjaPilot, FreeRTOS
11.3.0, this tree's PiOS and UAVObject set) is **not finished** and the target
is deliberately **excluded from `ALL_BOARDS`** so the default build stays
green. To work on it, add `pixracer` back to `ALL_BOARDS` in the top-level
`Makefile` (the short name, BL/BU/EF filter-outs and `_short` entry are
already in place) and run `make fw_pixracer`.

What already works:

- Board identity, flash layout and `.apj` packaging (`board-info.mk`).
- Build wiring in NinjaPilot's make system; the bring-up module set
  (FirmwareIAP + Telemetry + System) matching the source's maturity.
- `pixracer.c` (board bring-up/init task) compiles against FreeRTOS 11.3.
- `pios_board.h` pin map and `pios_usb_board_data.c` are in place.

What remains — a **driver-API rewrite**, because the source was written against
a newer-generation PiOS whose driver interfaces differ from this tree's:

1. **Invensense IMU** (`pios_board.c`, `board_hw_defs.c`): the source uses a
   `pios_invensense.c` hand-written on that fork's `pixracer-port` branch
   (stock 15.02.02 ships `pios_mpu6000.c`, not this driver). It
   configures the MPU9250 + ICM-20608-G through a `pios_invensense_t` /
   `pios_invensense_cfg` with `exti_cfg`, `gyro_range`, `pwr_mgmt_clk`,
   `PIOS_INVENSENSE_*` enums and a `PIOS_INVENSENSE_IRQHandler`. This tree's
   `flight/pios/common/pios_invensense.c` (the one the Cube Purple target uses
   for its MPU9250) has a different config struct and init signature. Rewrite
   the Pixracer sensor init against this tree's API, using the Cube Purple
   target's MPU9250 init as the reference, and decide how the second IMU
   (ICM-20608-G) is wired — the Cube only brings up one.
2. **LED** (`board_hw_defs.c`): this tree's `pios_led_cfg` uses a different
   layout (no `leds` / `num_leds` members as the source expects).
3. **USB** (`board_hw_defs.c`): `pios_usb_cfg` has no `vsense_ignore` member
   in this tree.
4. **UART7** (`board_hw_defs.c`): `UART7_IRQn` is referenced but this tree's
   F4 CMSIS/startup does not expose UART7 yet.

None of this is hardware-verifiable without a PixRacer on the bench, so the
driver rewrite should be done alongside a board to flash and watch. Until
then this directory is the staged groundwork, not a flashable image.

## Why this is separate from the old PixracerOpenPilot fork

`../PixracerOpenPilot` is the **same OpenPilot 15.02 lineage** as this tree
(based on the official `RELEASE-15.02.02` tag), but it keeps the stock
OpenPilot directory layout (`flight/PiOS`, `flight/targets/Pixracer/System`)
whereas this tree was restructured (`flight/pios`,
`flight/targets/boards/<board>`), and its board drivers are fork-local. Those
two differences, not a different upstream, are why it cannot be git-merged;
the board is brought across by hand, which is what this directory is.
