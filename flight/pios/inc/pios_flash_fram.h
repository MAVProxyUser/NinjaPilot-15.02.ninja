/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_FLASH_FRAM SPI FRAM presented as a flash device
 * @brief Cypress FM25V / Fujitsu MB85RS ferroelectric RAM behind the
 *        pios_flash_driver interface, so the log-structured settings
 *        filesystem can live in a part that a firmware flash never touches.
 * @{
 *
 * @file       pios_flash_fram.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2026.
 * @brief      SPI FRAM driver header
 * @see        The GNU Public License (GPL) Version 3
 *
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef PIOS_FLASH_FRAM_H
#define PIOS_FLASH_FRAM_H

#include <stdint.h>
#include "pios_flash.h"

/*
 * An FRAM has no erase: every byte is writable at any time.  The flash
 * interface still wants erase_sector(), so the driver emulates it by
 * writing 0xFF over sector_size bytes, and the caller picks a sector_size
 * that matches the filesystem configuration it will mount on top.
 *
 * Returns 0 when a known part answered the RDID command.  size, name and
 * the raw id bytes are available afterwards for the console.
 */
extern int32_t PIOS_Flash_Fram_Init(uintptr_t *flash_id, uint32_t spi_id, uint32_t slave_num, uint32_t sector_size);
extern uint32_t PIOS_Flash_Fram_Size(uintptr_t flash_id);	/* bytes */
extern const char *PIOS_Flash_Fram_Name(uintptr_t flash_id);
extern void PIOS_Flash_Fram_LastId(uint8_t id[9]);		/* raw RDID reply of the last Init, for diagnostics */

extern const struct pios_flash_driver pios_fram_flash_driver;

#endif	/* PIOS_FLASH_FRAM_H */

/**
 * @}
 * @}
 */
