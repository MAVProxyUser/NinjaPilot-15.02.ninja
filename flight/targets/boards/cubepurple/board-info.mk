BOARD_TYPE          := 0x0C
BOARD_REVISION      := 0x01
BOOTLOADER_VERSION  := 0x05
HW_TYPE             := 0x00

MCU                 := cortex-m4
CHIP                := STM32F427VIT
BOARD               := STM32F4xx_CUBE
MODEL               := HD
MODEL_SUFFIX        :=

OPENOCD_JTAG_CONFIG := stlink-v2.cfg
OPENOCD_CONFIG      := stm32f4xx.stlink.cfg

# The Cube keeps its stock ArduPilot bootloader in the first 16 KB and never
# gets an OpenPilot one; the application starts right after it.  There is no
# EEPROM bank: settings live in the FRAM (SPI2), the internal flash sectors
# 10-11 are only a fallback (the bootloader erases them on every flash).
BL_BANK_BASE        := 0x08000000  # Start of the (ArduPilot) bootloader
BL_BANK_SIZE        := 0x00004000  # 16 KB
FW_BANK_BASE        := 0x08004000  # Start of firmware flash
FW_BANK_SIZE        := 0x000BC000  # Should include FW_DESC_SIZE (sectors 1-9)
FW_DESC_SIZE        := 0x00000064
FS_BANK_BASE        := 0x080C0000  # fallback settings, sectors 10-11
FS_BANK_SIZE        := 0x00040000

# The ArduPilot bootloader flashes .apj images and checks this id (fmuv3 /
# TARGET_HW_CUBE_F4).
PX4_BOARD_ID        := 9

OSCILLATOR_FREQ     :=  24000000
SYSCLK_FREQ         := 168000000
