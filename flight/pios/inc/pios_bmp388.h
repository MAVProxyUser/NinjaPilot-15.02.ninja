/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_BMP388 BMP388 Functions
 * @brief Hardware functions to deal with the Bosch BMP388 barometer
 * @{
 *
 * @file       pios_bmp388.h
 * @author     NinjaPilot, 2026
 * @brief      BMP388 barometer driver
 * @see        The GNU Public License (GPL) Version 3
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

#ifndef PIOS_BMP388_H
#define PIOS_BMP388_H

#include <pios_sensors.h>

/* Oversampling (datasheet 3.4.4). The BMP388 selectors are NOT the BMP280's:
 * this part counts 0..5 as x1,x2,x4,x8,x16,x32, where the BMP280 starts at
 * "skip". Do not copy a BMP280 config across. */
enum pios_bmp388_osr {
    BMP388_OSR_1  = 0,
    BMP388_OSR_2  = 1,
    BMP388_OSR_4  = 2,
    BMP388_OSR_8  = 3,
    BMP388_OSR_16 = 4,
    BMP388_OSR_32 = 5,
};

/* IIR filter coefficient (datasheet 3.4.3), applied in hardware. Worth having
 * on a brushed nano: prop wash into an open port is broadband noise that the
 * Kalman downstream would otherwise have to carry. */
enum pios_bmp388_filter {
    BMP388_FILTER_OFF = 0,
    BMP388_FILTER_1   = 1,
    BMP388_FILTER_3   = 2,
    BMP388_FILTER_7   = 3,
    BMP388_FILTER_15  = 4,
    BMP388_FILTER_31  = 5,
    BMP388_FILTER_63  = 6,
    BMP388_FILTER_127 = 7,
};

/* Output data rate = 200 Hz / 2^odr (datasheet 4.3.20). The ODR must be slow
 * enough for the chosen oversampling to finish, or the part sets the
 * configuration error bit and keeps the last sample. */
enum pios_bmp388_odr {
    BMP388_ODR_200_HZ = 0x00,
    BMP388_ODR_100_HZ = 0x01,
    BMP388_ODR_50_HZ  = 0x02,
    BMP388_ODR_25_HZ  = 0x03,
    BMP388_ODR_12_5_HZ = 0x04,
};

struct pios_bmp388_cfg {
    enum pios_bmp388_osr    oversampling_pressure;
    enum pios_bmp388_osr    oversampling_temperature;
    enum pios_bmp388_filter filter;
    enum pios_bmp388_odr    odr;
    /* 0x76 with SDO low, 0x77 with SDO high. Breakouts differ, and several
     * sold as "BMP388" tie SDO high. Zero means 0x76. */
    uint8_t                 i2c_addr;
};

/* Public Functions */
extern int32_t PIOS_BMP388_Init(const struct pios_bmp388_cfg *cfg, int32_t i2c_device);
extern void PIOS_BMP388_Register(void);
/* 0x50 for a BMP388, 0x60 for a BMP390. Valid only after a successful Init. */
extern uint8_t PIOS_BMP388_GetChipID(void);
extern const PIOS_SENSORS_Driver PIOS_BMP388_Driver;

#endif /* PIOS_BMP388_H */

/**
 * @}
 * @}
 */
