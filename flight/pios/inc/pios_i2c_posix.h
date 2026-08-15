/**
 ******************************************************************************
 *
 * @file       pios_i2c_posix.h
 * @author     NinjaPilot, 2026
 * @brief      Posix/Linux backing for the PIOS I2C API (i2c-dev)
 * @see        The GNU Public License (GPL) Version 3
 * @defgroup   PIOS_I2C I2C Functions
 * @{
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
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef PIOS_I2C_POSIX_H
#define PIOS_I2C_POSIX_H

#include <stdint.h>

/**
 * @brief Bind a PIOS I2C adapter to a Linux i2c-dev node.
 *
 * On an STM32 target the equivalent call programs a peripheral. Here the
 * kernel already owns the controller, so all this does is open the character
 * device and build the little bookkeeping struct that PIOS_I2C_Transfer()
 * needs. Bus speed is NOT settable from userspace - it comes from the
 * device tree ("clock-frequency" on the i2c node). See osd32mp1/CLAUDE.md:
 * leaving that property out silently gives you the 100 kHz default, which
 * costs 84 % of a 500 Hz sensor period on this board.
 *
 * @param[out] i2c_id  opaque handle to pass to PIOS_I2C_Transfer()
 * @param[in]  devpath e.g. "/dev/i2c-3"
 * @return 0 on success, -1 on bad argument / no free adapter slot,
 *         -2 if the device node could not be opened
 */
extern int32_t PIOS_I2C_Posix_Init(uint32_t *i2c_id, const char *devpath);

/**
 * @brief Per-adapter transfer counters, for health reporting.
 * Any pointer may be NULL if that counter is not wanted.
 */
extern void PIOS_I2C_Posix_GetCounters(uint32_t i2c_id, uint32_t *ok,
                                       uint32_t *err, int32_t *last_errno);

#endif /* PIOS_I2C_POSIX_H */

/**
 * @}
 */
