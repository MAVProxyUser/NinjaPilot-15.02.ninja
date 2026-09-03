/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_BMP280 BMP280 Barometer Functions
 * @brief Hardware functions to deal with the Bosch BMP280 pressure sensor
 * @{
 *
 * @file       pios_bmp280.h
 * @brief      BMP280 barometer driver (I2C)
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

#ifndef PIOS_BMP280_H
#define PIOS_BMP280_H

#include <pios_sensors.h>

/* BMP280 oversampling selectors (datasheet 3.3.1/3.3.2). Higher is quieter
 * and slower; x16 pressure with x2 temperature is Bosch's own "indoor
 * navigation" recommendation and is what a small multirotor wants. */
enum pios_bmp280_osr {
    BMP280_OSR_SKIP = 0,
    BMP280_OSR_1    = 1,
    BMP280_OSR_2    = 2,
    BMP280_OSR_4    = 3,
    BMP280_OSR_8    = 4,
    BMP280_OSR_16   = 5,
};

/* IIR filter coefficient (datasheet 3.3.3). The part filters in hardware,
 * which matters on a brushed nano where prop wash is broadband. */
enum pios_bmp280_filter {
    BMP280_FILTER_OFF = 0,
    BMP280_FILTER_2   = 1,
    BMP280_FILTER_4   = 2,
    BMP280_FILTER_8   = 3,
    BMP280_FILTER_16  = 4,
};

struct pios_bmp280_cfg {
    enum pios_bmp280_osr    oversampling_pressure;
    enum pios_bmp280_osr    oversampling_temperature;
    enum pios_bmp280_filter filter;
    /* 0x76 with SDO low, 0x77 with SDO high. Breakouts differ; if the chip
     * ID read fails, this is the first thing to try flipping. */
    uint8_t                 i2c_addr;
};

/* Public Functions */
extern int32_t PIOS_BMP280_Init(const struct pios_bmp280_cfg *cfg, int32_t i2c_device);
extern void PIOS_BMP280_Register(void);
extern const PIOS_SENSORS_Driver PIOS_BMP280_Driver;

#endif /* PIOS_BMP280_H */

/**
 * @}
 * @}
 */
