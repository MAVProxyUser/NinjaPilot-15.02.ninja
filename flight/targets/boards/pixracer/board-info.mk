BOARD_TYPE          := 0x0B
BOARD_REVISION      := 0x01
BOOTLOADER_VERSION  := 0x01
HW_TYPE             := 0x00

MCU                 := cortex-m4
CHIP                := STM32F427VIT
BOARD               := STM32F4xx_PXR
MODEL               := HD
MODEL_SUFFIX        :=

OPENOCD_JTAG_CONFIG := stlink-v2.cfg
OPENOCD_CONFIG      := stm32f4xx.stlink.cfg

# mRo / AUAV PixRacer R12 (FMUv4): STM32F427VIT6, 24 MHz HSE, 168 MHz.
# Like the Cube Purple it keeps its stock PX4/ArduPilot bootloader in the first
# 16 KB and never gets an OpenPilot one; the application starts at 0x08004000.
# Settings live in internal flash sectors 10-11 (there is no FRAM on this board),
# which the PX4 bootloader leaves alone (it only erases the firmware bank).
BL_BANK_BASE        := 0x08000000  # Start of the (PX4) bootloader
BL_BANK_SIZE        := 0x00004000  # 16 KB - PX4 APP_LOAD_ADDRESS is 0x08004000
FW_BANK_BASE        := 0x08004000  # Start of firmware flash
FW_BANK_SIZE        := 0x000BC000  # Should include FW_DESC_SIZE (sectors 1-9)
FW_DESC_SIZE        := 0x00000064
FS_BANK_BASE        := 0x080C0000  # settings filesystem, sectors 10-11
FS_BANK_SIZE        := 0x00040000

# The PX4/ArduPilot bootloader flashes .apj images and checks this id
# (fmuv4 / TARGET_HW_PX4_FMU_V4, board id 11 in AP_Bootloader/board_types.txt).
PX4_BOARD_ID        := 11

OSCILLATOR_FREQ     :=  24000000
SYSCLK_FREQ         := 168000000
