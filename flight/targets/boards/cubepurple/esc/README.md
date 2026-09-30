# ESC firmware for the Vimdrones S50 (AM32, DroneCAN)

* `AM32-v2.20-BeepCommand.patch`: our change on top of AM32 v2.20 (the release
  the ESCs ship with). Adds `uavcan.equipment.indication.BeepCommand` (1080):
  the ESC plays the note on the motor from its main loop while stopped, on the
  same footing as its beacon tones, capped at 400 ms.
* `AM32_VIMDRONES_S50_L431_CAN_2.20-beep.bin`: that patch built for the
  `VIMDRONES_S50_L431_CAN` target, bootloader signature and CRCs included.

Rebuild: clone https://github.com/am32-firmware/AM32 at tag `v2.20`
(`lineage/AM32` here), `git am AM32-v2.20-BeepCommand.patch`,
`make arm_sdk_install` (AM32's pinned gcc 10.3; Homebrew gcc 13 fails on
`-Werror=array-bounds`), then `make VIMDRONES_S50_L431_CAN`.

Flash over CAN from the Cube, bench powered, disarmed, no props:
`python3 ../tools/esc_flash.py AM32_VIMDRONES_S50_L431_CAN_2.20-beep.bin --node N`.
The bootloader stays; it verifies the image before jumping. Untested so far.
