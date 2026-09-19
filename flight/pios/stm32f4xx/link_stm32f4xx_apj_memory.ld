/*
 * Memory map of a board that boots through the ArduPilot / PX4 bootloader
 * (Cube, Pixhawk): the bootloader owns the first 16 KB and knows nothing
 * about OpenPilot's board-info blob, so the application carries the blob
 * inline (see link_stm32f4xx_apj_sections.ld) and starts at 0x08004000.
 * STM32F427: 192 KB SRAM, 64 KB CCM.
 */
MEMORY
{
	FLASH (rx)    : ORIGIN = 0x08004000,        LENGTH = 0x0bc000
	SRAM (rwx)    : ORIGIN = 0x20000000,        LENGTH = 0x030000
	CCSRAM (rw)   : ORIGIN = 0x10000000,        LENGTH = 0x010000
}
