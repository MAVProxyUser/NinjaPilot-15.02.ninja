/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_BMP388 BMP388 Functions
 * @brief Hardware functions to deal with the Bosch BMP388 barometer
 * @{
 *
 * @file       pios_bmp388.c
 * @author     NinjaPilot, 2026
 * @brief      BMP388 barometer driver
 *
 * Structurally the BMP280 driver next door, but the two parts share almost
 * nothing below the surface: different register map, different calibration
 * block, different compensation. The similar names are a trap, so the
 * datasheet section is cited at each place it matters.
 *
 * Registered as a polled PIOS_SENSORS_TYPE_1AXIS_BARO, which is what
 * modules/AltFilter looks for. It publishes BaroSensor and runs the altitude
 * Kalman; nothing here needs to know about either.
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

#ifdef PIOS_INCLUDE_BMP388

#include <pios_bmp388.h>
#include <string.h>

/* Registers (datasheet 4.3) */
#define BMP388_REG_CHIPID    0x00
#define BMP388_REG_ERR       0x02
#define BMP388_REG_STATUS    0x03
#define BMP388_REG_DATA      0x04   /* 6 bytes: press XLSB/LSB/MSB, temp XLSB/LSB/MSB */
#define BMP388_REG_PWR_CTRL  0x1B
#define BMP388_REG_OSR       0x1C
#define BMP388_REG_ODR       0x1D
#define BMP388_REG_CONFIG    0x1F
#define BMP388_REG_CALIB0    0x31   /* NVM_PAR_T1 .. NVM_PAR_P11, 21 bytes */
#define BMP388_REG_CMD       0x7E

#define BMP388_CHIPID_VALUE  0x50   /* BMP388. The BMP390 answers 0x60: same
                                     * register map and compensation, so it is
                                     * accepted too and reported separately. */
#define BMP390_CHIPID_VALUE  0x60
#define BMP388_CMD_SOFTRESET 0xB6

/* PWR_CTRL (datasheet 4.3.18) */
#define BMP388_PWR_PRESS_EN  (1 << 0)
#define BMP388_PWR_TEMP_EN   (1 << 1)
#define BMP388_PWR_MODE_NORMAL (0x03 << 4)

/* ERR_REG (datasheet 4.3.2). conf_err latches when the ODR is too fast for
 * the selected oversampling -- the part then quietly repeats stale samples,
 * which looks exactly like a healthy but unresponsive barometer. */
#define BMP388_ERR_FATAL     (1 << 0)
#define BMP388_ERR_CMD       (1 << 1)
#define BMP388_ERR_CONF      (1 << 2)

#define BMP388_CALIB_LEN     21

static int32_t i2c_id;
static uint8_t bmp_addr;
static uint8_t bmp_chipid;

/* Factory calibration, quantized the way Bosch's reference API does it: the
 * raw NVM integers are scaled once here so the per-sample compensation is
 * plain arithmetic.
 *
 * double, not float, deliberately. The pressure polynomial cubes a 24-bit
 * reading, so the intermediate terms reach ~1e21 -- far past the ~7 significant
 * digits a single-precision float carries, and the error lands in the low
 * pascals, which is tens of centimetres of altitude. This runs at 50 Hz in a
 * low-priority module, so the soft-double cost is irrelevant next to being
 * right.
 */
static struct {
    double par_t1, par_t2, par_t3;
    double par_p1, par_p2, par_p3, par_p4, par_p5, par_p6;
    double par_p7, par_p8, par_p9, par_p10, par_p11;
    double t_lin;
} cal;

static PIOS_SENSORS_1Axis_SensorsWithTemp results;

static int32_t PIOS_BMP388_Read(uint8_t address, uint8_t *buffer, uint8_t len)
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

static int32_t PIOS_BMP388_Write(uint8_t address, uint8_t value)
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

/* Scale the NVM trim values (datasheet 3.11.1). The divisors are powers of
 * two straight from the datasheet table; they are written as literals rather
 * than shifts so each line can be read against it.
 *
 * Two of them DIVIDE BY a negative power of two, i.e. multiply -- par_t1 by
 * 2^8 and par_p5 by 2^3. Getting either backwards still produces plausible
 * room-temperature numbers that drift badly with temperature. */
static void parse_calib(const uint8_t *d)
{
    uint16_t nvm_t1 = (uint16_t)(d[0] | (d[1] << 8));
    uint16_t nvm_t2 = (uint16_t)(d[2] | (d[3] << 8));
    int8_t   nvm_t3 = (int8_t)d[4];
    int16_t  nvm_p1 = (int16_t)(d[5] | (d[6] << 8));
    int16_t  nvm_p2 = (int16_t)(d[7] | (d[8] << 8));
    int8_t   nvm_p3 = (int8_t)d[9];
    int8_t   nvm_p4 = (int8_t)d[10];
    uint16_t nvm_p5 = (uint16_t)(d[11] | (d[12] << 8));
    uint16_t nvm_p6 = (uint16_t)(d[13] | (d[14] << 8));
    int8_t   nvm_p7 = (int8_t)d[15];
    int8_t   nvm_p8 = (int8_t)d[16];
    int16_t  nvm_p9 = (int16_t)(d[17] | (d[18] << 8));
    int8_t   nvm_p10 = (int8_t)d[19];
    int8_t   nvm_p11 = (int8_t)d[20];

    cal.par_t1  = (double)nvm_t1 * 256.0;                    /* / 2^-8  */
    cal.par_t2  = (double)nvm_t2 / 1073741824.0;             /* / 2^30  */
    cal.par_t3  = (double)nvm_t3 / 281474976710656.0;        /* / 2^48  */
    cal.par_p1  = ((double)nvm_p1 - 16384.0) / 1048576.0;    /* / 2^20  */
    cal.par_p2  = ((double)nvm_p2 - 16384.0) / 536870912.0;  /* / 2^29  */
    cal.par_p3  = (double)nvm_p3 / 4294967296.0;             /* / 2^32  */
    cal.par_p4  = (double)nvm_p4 / 137438953472.0;           /* / 2^37  */
    cal.par_p5  = (double)nvm_p5 * 8.0;                      /* / 2^-3  */
    cal.par_p6  = (double)nvm_p6 / 64.0;                     /* / 2^6   */
    cal.par_p7  = (double)nvm_p7 / 256.0;                    /* / 2^8   */
    cal.par_p8  = (double)nvm_p8 / 32768.0;                  /* / 2^15  */
    cal.par_p9  = (double)nvm_p9 / 281474976710656.0;        /* / 2^48  */
    cal.par_p10 = (double)nvm_p10 / 281474976710656.0;       /* / 2^48  */
    cal.par_p11 = (double)nvm_p11 / 36893488147419103232.0;  /* / 2^65  */
}

/* Datasheet 3.11.3. Must run before the pressure pass: it sets t_lin, which
 * the pressure polynomial needs. Returns degrees C. */
static double bmp388_compensate_T(uint32_t adc_T)
{
    double d1 = (double)adc_T - cal.par_t1;
    double d2 = d1 * cal.par_t2;

    cal.t_lin = d2 + (d1 * d1) * cal.par_t3;
    return cal.t_lin;
}

/* Datasheet 3.11.3. Returns pascals. */
static double bmp388_compensate_P(uint32_t adc_P)
{
    double t  = cal.t_lin;
    double t2 = t * t;
    double t3 = t2 * t;
    double p  = (double)adc_P;
    double p2 = p * p;
    double p3 = p2 * p;

    double out1 = cal.par_p5
                  + cal.par_p6 * t
                  + cal.par_p7 * t2
                  + cal.par_p8 * t3;

    double out2 = p * (cal.par_p1
                       + cal.par_p2 * t
                       + cal.par_p3 * t2
                       + cal.par_p4 * t3);

    double out3 = p2 * (cal.par_p9 + cal.par_p10 * t)
                  + p3 * cal.par_p11;

    return out1 + out2 + out3;
}

int32_t PIOS_BMP388_Init(const struct pios_bmp388_cfg *cfg, int32_t i2c_device)
{
    uint8_t buf[BMP388_CALIB_LEN];

    PIOS_Assert(cfg);
    i2c_id   = i2c_device;
    bmp_addr = cfg->i2c_addr ? cfg->i2c_addr : 0x76;

    /* Identify before touching anything: a wrong address or an empty footprint
     * must fail here rather than produce plausible-looking altitudes. */
    if (PIOS_BMP388_Read(BMP388_REG_CHIPID, buf, 1) != 0) {
        return -1;
    }
    if (buf[0] != BMP388_CHIPID_VALUE && buf[0] != BMP390_CHIPID_VALUE) {
        return -2;
    }
    bmp_chipid = buf[0];

    if (PIOS_BMP388_Write(BMP388_REG_CMD, BMP388_CMD_SOFTRESET) != 0) {
        return -3;
    }
    /* Datasheet 1.2: 2 ms start-up. The reset also reloads the NVM trim, so
     * the calibration read below must come after it, not before. */
    PIOS_DELAY_WaitmS(10);

    if (PIOS_BMP388_Read(BMP388_REG_CALIB0, buf, BMP388_CALIB_LEN) != 0) {
        return -4;
    }
    parse_calib(buf);

    if (PIOS_BMP388_Write(BMP388_REG_OSR,
                          (uint8_t)((cfg->oversampling_temperature << 3)
                                    | cfg->oversampling_pressure)) != 0) {
        return -5;
    }
    if (PIOS_BMP388_Write(BMP388_REG_ODR, (uint8_t)cfg->odr) != 0) {
        return -6;
    }
    if (PIOS_BMP388_Write(BMP388_REG_CONFIG, (uint8_t)(cfg->filter << 1)) != 0) {
        return -7;
    }
    /* Enable both channels and go to NORMAL last: the part converts
     * continuously from here, so configuration comes first. */
    if (PIOS_BMP388_Write(BMP388_REG_PWR_CTRL,
                          BMP388_PWR_PRESS_EN | BMP388_PWR_TEMP_EN
                          | BMP388_PWR_MODE_NORMAL) != 0) {
        return -8;
    }

    /* One ODR period, then ask the part whether it liked the configuration.
     * conf_err means the ODR is too fast for this oversampling; the readings
     * would then be stale repeats rather than an obvious failure. */
    PIOS_DELAY_WaitmS(20);
    if (PIOS_BMP388_Read(BMP388_REG_ERR, buf, 1) == 0
        && (buf[0] & (BMP388_ERR_FATAL | BMP388_ERR_CONF))) {
        return -9;
    }

    results.temperature = 0.0f;
    results.sample      = 0.0f;
    return 0;
}

uint8_t PIOS_BMP388_GetChipID(void)
{
    return bmp_chipid;
}

void PIOS_BMP388_Register(void)
{
    PIOS_SENSORS_Register(&PIOS_BMP388_Driver, PIOS_SENSORS_TYPE_1AXIS_BARO, 0);
}

static bool PIOS_BMP388_driver_Test(__attribute__((unused)) uintptr_t context)
{
    uint8_t id;

    return PIOS_BMP388_Read(BMP388_REG_CHIPID, &id, 1) == 0
           && (id == BMP388_CHIPID_VALUE || id == BMP390_CHIPID_VALUE);
}

static void PIOS_BMP388_driver_Reset(__attribute__((unused)) uintptr_t context) {}

static void PIOS_BMP388_driver_get_scale(float *scales, uint8_t size,
                                         __attribute__((unused)) uintptr_t context)
{
    PIOS_Assert(size > 0);
    scales[0] = 1;
}

static void PIOS_BMP388_driver_fetch(void *data, __attribute__((unused)) uint8_t size,
                                     __attribute__((unused)) uintptr_t context)
{
    PIOS_Assert(data);
    memcpy(data, (void *)&results, sizeof(PIOS_SENSORS_1Axis_SensorsWithTemp));
}

static bool PIOS_BMP388_driver_poll(__attribute__((unused)) uintptr_t context)
{
    uint8_t buf[6];

    /* NORMAL mode converts continuously, so there is nothing to command and
     * nothing to wait for -- take the latest result. Unlike the BMP280 the
     * data registers are LITTLE endian and pressure comes first. */
    if (PIOS_BMP388_Read(BMP388_REG_DATA, buf, sizeof(buf)) != 0) {
        return false;
    }

    uint32_t adc_P = ((uint32_t)buf[2] << 16) | ((uint32_t)buf[1] << 8) | buf[0];
    uint32_t adc_T = ((uint32_t)buf[5] << 16) | ((uint32_t)buf[4] << 8) | buf[3];

    /* All-zero is what the data registers hold before the first conversion
     * completes. Compensating it yields a large negative pressure. */
    if (adc_P == 0 || adc_T == 0) {
        return false;
    }

    double T = bmp388_compensate_T(adc_T);   /* must precede P: sets t_lin */
    double P = bmp388_compensate_P(adc_P);

    /* A sane troposphere is roughly 1 kPa (Everest, and then some) to 110 kPa.
     * Anything outside that is a bus or maths fault, not weather, and must not
     * reach the altitude filter. */
    if (!(P > 1000.0 && P < 110000.0)) {
        return false;
    }

    results.temperature = (float)T;   /* degrees C */
    results.sample      = (float)P;   /* pascals   */
    return true;
}

const PIOS_SENSORS_Driver PIOS_BMP388_Driver = {
    .test      = PIOS_BMP388_driver_Test,
    .poll      = PIOS_BMP388_driver_poll,
    .fetch     = PIOS_BMP388_driver_fetch,
    .reset     = PIOS_BMP388_driver_Reset,
    .get_queue = NULL,
    .get_scale = PIOS_BMP388_driver_get_scale,
    .is_polled = true,
};

#endif /* PIOS_INCLUDE_BMP388 */

/**
 * @}
 * @}
 */
