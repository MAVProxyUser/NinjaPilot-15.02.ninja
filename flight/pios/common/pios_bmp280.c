/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_BMP280 BMP280 Barometer Functions
 * @brief Hardware functions to deal with the Bosch BMP280 pressure sensor
 * @{
 *
 * @file       pios_bmp280.c
 * @brief      BMP280 barometer driver (I2C)
 *
 * Written for the LiteWing ESP32-S3 nano, where a ~1 g barometer buys altitude
 * hold for a fraction of the mass a GPS module costs (a Matek M9N-5883 is
 * 14.5 g on a 55 g airframe -- it takes thrust-to-weight from 1.60 to 1.24).
 *
 * Deliberately simpler than pios_ms5611.c. The MS5611 needs a state machine
 * because temperature and pressure are separate commanded conversions with a
 * wait in between; the BMP280 in NORMAL mode converts both continuously in the
 * background, so a poll is just "read six bytes and compensate" and there is
 * no FSM to get wrong.
 *
 * UNITS, and this one is a trap: handleBaro() in modules/Sensors/sensors.c
 * compares the sample against PIOS_CONST_MKS_STD_ATMOSPHERE_F, which is
 * 1.01325e5, so the sample must be in PASCALS -- despite barosensor.xml
 * labelling the field "kPa". Bosch's compensation returns Q24.8 fixed point,
 * hence the divide by 256.
 *
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

#include "pios.h"

#ifdef PIOS_INCLUDE_BMP280

#include <pios_bmp280.h>
#include <string.h>

/* Registers (datasheet 4.2) */
#define BMP280_REG_CALIB0     0x88
#define BMP280_REG_CHIPID     0xD0
#define BMP280_REG_RESET      0xE0
#define BMP280_REG_STATUS     0xF3
#define BMP280_REG_CTRL_MEAS  0xF4
#define BMP280_REG_CONFIG     0xF5
#define BMP280_REG_PRESS_MSB  0xF7

#define BMP280_CHIPID_VALUE   0x58   /* BMP280. BME280 answers 0x60 and has an
                                      * extra humidity block -- it will read
                                      * pressure fine but is a different part,
                                      * so the ID gate below is deliberate. */
#define BMP280_RESET_VALUE    0xB6
#define BMP280_MODE_NORMAL    0x03
#define BMP280_STATUS_MEASURING 0x08

static int32_t i2c_id;
static uint8_t bmp_addr;

/* Factory calibration (datasheet 3.11.2) */
static struct {
    uint16_t T1;
    int16_t  T2, T3;
    uint16_t P1;
    int16_t  P2, P3, P4, P5, P6, P7, P8, P9;
} cal;

static int32_t t_fine;
static PIOS_SENSORS_1Axis_SensorsWithTemp results;

static int32_t PIOS_BMP280_Read(uint8_t address, uint8_t *buffer, uint8_t len)
{
    const struct pios_i2c_txn txn_list[] = {
        {
            .info = __func__,
            .addr = bmp_addr,
            .rw   = PIOS_I2C_TXN_WRITE,
            .len  = 1,
            .buf  = &address,
        },
        {
            .info = __func__,
            .addr = bmp_addr,
            .rw   = PIOS_I2C_TXN_READ,
            .len  = len,
            .buf  = buffer,
        }
    };

    return PIOS_I2C_Transfer(i2c_id, txn_list, NELEMENTS(txn_list));
}

static int32_t PIOS_BMP280_Write(uint8_t address, uint8_t value)
{
    uint8_t buf[2] = { address, value };
    const struct pios_i2c_txn txn_list[] = {
        {
            .info = __func__,
            .addr = bmp_addr,
            .rw   = PIOS_I2C_TXN_WRITE,
            .len  = sizeof(buf),
            .buf  = buf,
        },
    };

    return PIOS_I2C_Transfer(i2c_id, txn_list, NELEMENTS(txn_list));
}

/* Bosch's reference compensation, datasheet 3.11.3, verbatim in structure so
 * it can be diffed against the datasheet rather than trusted. Returns
 * temperature in hundredths of a degree C and sets t_fine for the pressure
 * pass, which MUST run first. */
static int32_t bmp280_compensate_T(int32_t adc_T)
{
    int32_t var1, var2;

    var1   = ((((adc_T >> 3) - ((int32_t)cal.T1 << 1))) * ((int32_t)cal.T2)) >> 11;
    var2   = (((((adc_T >> 4) - ((int32_t)cal.T1)) * ((adc_T >> 4) - ((int32_t)cal.T1))) >> 12)
              * ((int32_t)cal.T3)) >> 14;
    t_fine = var1 + var2;
    return (t_fine * 5 + 128) >> 8;
}

/* Returns pressure in Q24.8 Pa (i.e. Pa * 256). */
static uint32_t bmp280_compensate_P(int32_t adc_P)
{
    int64_t var1, var2, p;

    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)cal.P6;
    var2 = var2 + ((var1 * (int64_t)cal.P5) << 17);
    var2 = var2 + (((int64_t)cal.P4) << 35);
    var1 = ((var1 * var1 * (int64_t)cal.P3) >> 8) + ((var1 * (int64_t)cal.P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)cal.P1) >> 33;

    if (var1 == 0) {
        return 0; /* avoid divide by zero on a garbage calibration */
    }

    p    = 1048576 - adc_P;
    p    = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)cal.P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)cal.P8) * p) >> 19;
    p    = ((p + var1 + var2) >> 8) + (((int64_t)cal.P7) << 4);

    return (uint32_t)p;
}

int32_t PIOS_BMP280_Init(const struct pios_bmp280_cfg *cfg, int32_t i2c_device)
{
    uint8_t buf[24];

    PIOS_Assert(cfg);
    i2c_id   = i2c_device;
    bmp_addr = cfg->i2c_addr ? cfg->i2c_addr : 0x76;

    /* Identify before touching anything: a wrong address or an unpopulated
     * footprint should fail here, not produce plausible-looking altitudes. */
    if (PIOS_BMP280_Read(BMP280_REG_CHIPID, buf, 1) != 0) {
        return -1;
    }
    if (buf[0] != BMP280_CHIPID_VALUE) {
        return -2;
    }

    if (PIOS_BMP280_Write(BMP280_REG_RESET, BMP280_RESET_VALUE) != 0) {
        return -3;
    }
    PIOS_DELAY_WaitmS(5); /* datasheet: start-up time 2 ms */

    if (PIOS_BMP280_Read(BMP280_REG_CALIB0, buf, sizeof(buf)) != 0) {
        return -4;
    }
    cal.T1 = (uint16_t)(buf[0] | (buf[1] << 8));
    cal.T2 = (int16_t)(buf[2] | (buf[3] << 8));
    cal.T3 = (int16_t)(buf[4] | (buf[5] << 8));
    cal.P1 = (uint16_t)(buf[6] | (buf[7] << 8));
    cal.P2 = (int16_t)(buf[8] | (buf[9] << 8));
    cal.P3 = (int16_t)(buf[10] | (buf[11] << 8));
    cal.P4 = (int16_t)(buf[12] | (buf[13] << 8));
    cal.P5 = (int16_t)(buf[14] | (buf[15] << 8));
    cal.P6 = (int16_t)(buf[16] | (buf[17] << 8));
    cal.P7 = (int16_t)(buf[18] | (buf[19] << 8));
    cal.P8 = (int16_t)(buf[20] | (buf[21] << 8));
    cal.P9 = (int16_t)(buf[22] | (buf[23] << 8));

    /* config first, then ctrl_meas: writes to config are ignored while the
     * part is in normal mode (datasheet 3.6.3). */
    if (PIOS_BMP280_Write(BMP280_REG_CONFIG, (uint8_t)(cfg->filter << 2)) != 0) {
        return -5;
    }
    if (PIOS_BMP280_Write(BMP280_REG_CTRL_MEAS,
                          (uint8_t)((cfg->oversampling_temperature << 5)
                                    | (cfg->oversampling_pressure << 2)
                                    | BMP280_MODE_NORMAL)) != 0) {
        return -6;
    }

    results.temperature = 0.0f;
    results.sample      = 0.0f;
    return 0;
}

void PIOS_BMP280_Register(void)
{
    PIOS_SENSORS_Register(&PIOS_BMP280_Driver, PIOS_SENSORS_TYPE_1AXIS_BARO, 0);
}

static bool PIOS_BMP280_driver_Test(__attribute__((unused)) uintptr_t context)
{
    uint8_t id;

    return PIOS_BMP280_Read(BMP280_REG_CHIPID, &id, 1) == 0 && id == BMP280_CHIPID_VALUE;
}

static void PIOS_BMP280_driver_Reset(__attribute__((unused)) uintptr_t context) {}

static void PIOS_BMP280_driver_get_scale(float *scales, uint8_t size,
                                         __attribute__((unused)) uintptr_t context)
{
    PIOS_Assert(size > 0);
    scales[0] = 1;
}

static void PIOS_BMP280_driver_fetch(void *data, __attribute__((unused)) uint8_t size,
                                     __attribute__((unused)) uintptr_t context)
{
    PIOS_Assert(data);
    memcpy(data, (void *)&results, sizeof(PIOS_SENSORS_1Axis_SensorsWithTemp));
}

static bool PIOS_BMP280_driver_poll(__attribute__((unused)) uintptr_t context)
{
    uint8_t buf[6];

    /* NORMAL mode converts continuously, so there is nothing to command and
     * nothing to wait for -- just take the latest result. */
    if (PIOS_BMP280_Read(BMP280_REG_PRESS_MSB, buf, sizeof(buf)) != 0) {
        return false;
    }

    int32_t adc_P = ((int32_t)buf[0] << 12) | ((int32_t)buf[1] << 4) | ((int32_t)buf[2] >> 4);
    int32_t adc_T = ((int32_t)buf[3] << 12) | ((int32_t)buf[4] << 4) | ((int32_t)buf[5] >> 4);

    /* 0x80000 is the reset/skipped value: the part has not produced a
     * conversion yet. Reporting it would compensate to nonsense. */
    if (adc_P == 0x80000 || adc_T == 0x80000) {
        return false;
    }

    int32_t T = bmp280_compensate_T(adc_T);   /* must precede P: sets t_fine */
    uint32_t P = bmp280_compensate_P(adc_P);

    if (P == 0) {
        return false;
    }

    results.temperature = (float)T / 100.0f;  /* 0.01 C -> C  */
    results.sample      = (float)P / 256.0f;  /* Q24.8 -> Pa  */
    return true;
}

const PIOS_SENSORS_Driver PIOS_BMP280_Driver = {
    .test      = PIOS_BMP280_driver_Test,
    .poll      = PIOS_BMP280_driver_poll,
    .fetch     = PIOS_BMP280_driver_fetch,
    .reset     = PIOS_BMP280_driver_Reset,
    .get_queue = NULL,
    .get_scale = PIOS_BMP280_driver_get_scale,
    .is_polled = true,
};

#endif /* PIOS_INCLUDE_BMP280 */

/**
 * @}
 * @}
 */
