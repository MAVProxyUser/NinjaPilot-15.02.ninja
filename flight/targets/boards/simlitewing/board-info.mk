BOARD_TYPE          := 0x13
BOARD_REVISION      := 0x02
BOOTLOADER_VERSION  := 0x01
HW_TYPE             := 0x00

MCU                 :=
CHIP                := 
# BOARD_REVISION MUST STAY 0x02. attitude.c has
#     #define BOARDISCC3D (bdinfo->board_rev == 0x02)
# and keys the MPU6000-family sensor path off it. Any other revision silently
# drops this target onto the ADXL345/analog-gyro path, which is not compiled
# in here, so updateSensors() returns -1 forever and Attitude sits at Error
# with no sample ever reaching the filter. The ESP32 target documents the
# same trap. 0x13 is the LiteWing TYPE; 0x02 is not a LiteWing revision
# number, it is a sensor-path selector.
#
# NOTE: this stays SIM_POSIX on purpose. The build defines USE_$(BOARD), and
# pios.h keys the whole POSIX-vs-STM32 architecture selection off USE_SIM_POSIX -
# renaming it here silently drops this target into the STM32 include path
# (realposix documents the same trap). BOARD names the ARCHITECTURE;
# PIOS_SIMLITEWING (set in inc/pios_config.h) names the VARIANT: the posix
# simulation twin of the LiteWing ESP32-S3 brushed nano quad (board id 0x1302).
BOARD               := SIM_POSIX
MODEL               := 
MODEL_SUFFIX        := 

OPENOCD_JTAG_CONFIG := 
OPENOCD_CONFIG      := 

# Note: These must match the values in link_$(BOARD)_memory.ld
BL_BANK_BASE        := 0x08000000  # Start of bootloader flash
BL_BANK_SIZE        := 0x00008000  # Should include BD_INFO region
FW_BANK_BASE        := 0x08008000  # Start of firmware flash
FW_BANK_SIZE        := 0x00038000  # Should include FW_DESC_SIZE

FW_DESC_SIZE        := 0x00000064

OSCILLATOR_FREQ     :=   8000000
SYSCLK_FREQ         := 168000000
