BOARD_TYPE          := 0x12
# MUST be 0x02. modules/Attitude/attitude.c derives its sensor path from this:
#   #define BOARDISCC3D (bdinfo->board_rev == 0x02)
# 0x02 selects updateSensorsCC3D() (MPU6000 over SPI); anything else selects
# updateSensors(), the CopterControl analog-gyro + ADXL345 path, which this
# board does not have. Getting this wrong compiles fine and then never
# produces a sample.
BOARD_REVISION      := 0x02
BOOTLOADER_VERSION  := 0x00
HW_TYPE             := 0x00

MCU                 := xtensa-lx6
CHIP                := ESP32-D0WD-V3
# NOTE: the build defines USE_$(BOARD), and pios.h keys the architecture
# selection off that. USE_ESP32 selects flight/pios/esp32/pios_esp32.h.
# Renaming this drops the target into the STM32 include path, exactly as the
# comment in realposix/board-info.mk warns. Leave it as ESP32.
BOARD               := ESP32
MODEL               :=
MODEL_SUFFIX        :=

OPENOCD_JTAG_CONFIG :=
OPENOCD_CONFIG      :=

# There is no PiOS bootloader on this target. ESP-IDF's own second-stage
# bootloader owns the boot path, the partition table defines the layout, and
# esptool does the flashing. The BL_/FW_BANK values the STM32 targets use to
# carve up internal flash have no analogue here -- see esp-idf/partitions.csv
# for the real layout.
BL_BANK_BASE        :=
BL_BANK_SIZE        :=
FW_BANK_BASE        :=
FW_BANK_SIZE        :=

FW_DESC_SIZE        := 0x00000064

OSCILLATOR_FREQ     :=  40000000
SYSCLK_FREQ         := 240000000
