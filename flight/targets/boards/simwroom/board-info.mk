BOARD_TYPE          := 0x12
BOARD_REVISION      := 0x02
BOOTLOADER_VERSION  := 0x01
HW_TYPE             := 0x00

MCU                 :=
CHIP                := 
# NOTE: this stays SIM_POSIX on purpose. The build defines USE_$(BOARD), and
# pios.h keys the whole POSIX-vs-STM32 architecture selection off USE_SIM_POSIX -
# renaming it here silently drops this target into the STM32 include path
# (realposix documents the same trap). BOARD names the ARCHITECTURE;
# PIOS_SIMWROOM (set in inc/pios_config.h) names the VARIANT: the posix
# simulation twin of the ESP32 Thing Plus (board id 0x1202).
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
