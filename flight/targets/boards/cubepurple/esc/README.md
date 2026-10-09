# ESC firmware for the Vimdrones S50 (AM32, DroneCAN)

* `AM32-v2.20-0001-BeepCommand.patch`, `AM32-v2.20-0002-...patch`: our changes
  on top of AM32 v2.20 (the release the ESCs ship with). Adds
  `uavcan.equipment.indication.BeepCommand` (1080): the ESC plays the note on
  the motor from its main loop while stopped, interrupts masked like its own
  beacon tones (the 10 kHz routine would otherwise zero the duty cycle and cut
  the note to a click), capped at 400 ms.
* `AM32_VIMDRONES_S50_L431_CAN_2.20-beep.bin`: that patch built for the
  `VIMDRONES_S50_L431_CAN` target, bootloader signature and CRCs included.

Rebuild: clone https://github.com/am32-firmware/AM32 at tag `v2.20`
(`lineage/AM32` here), `git am AM32-v2.20-000*.patch`,
`make arm_sdk_install` (AM32's pinned gcc 10.3; Homebrew gcc 13 fails on
`-Werror=array-bounds`), then `make VIMDRONES_S50_L431_CAN`.

Flash over CAN from the Cube, bench powered, disarmed, no props:
`python3 ../tools/esc_flash.py AM32_VIMDRONES_S50_L431_CAN_2.20-beep.bin --node N`.
The bootloader stays; it verifies the image before jumping. Verified 2026-10-09
on all four Vimdrones S50: about 55 s per ESC, one bootloader read per 256-byte
block, the ESC back on the bus within a second, and `DroneCANBeep` notes audible
on the motors.
