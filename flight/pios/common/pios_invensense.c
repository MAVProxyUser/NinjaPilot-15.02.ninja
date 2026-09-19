/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_INVENSENSE Invensense MPU9250 / ICM2060x gyro+accel (+ AK8963 compass)
 * @{
 *
 * @file       pios_invensense.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2026.
 * @brief      SPI driver for the newer Invensense parts, sensor-subsystem style
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

#include "pios.h"
#include <string.h>

#if defined(PIOS_INCLUDE_INVENSENSE)

#include "pios_invensense.h"
#include <pios_mem.h>

#define GRAV 9.81f

/* ACCEL(6) TEMP(2) GYRO(6) EXT_SENS_DATA_00..07(8): the AK8963's ST1, HXL..HZH,
 * ST2 land in the external sensor registers right after the gyro. */
#define PIOS_INVENSENSE_BURST_LEN  22
#define PIOS_INVENSENSE_MAG_OFFSET 14
#define PIOS_INVENSENSE_QUEUE_LEN  2

/* I2C master and slave registers (MPU9250) */
#define REG_I2C_MST_CTRL         0x24
#define REG_I2C_SLV0_ADDR        0x25
#define REG_I2C_SLV0_REG         0x26
#define REG_I2C_SLV0_CTRL        0x27
#define REG_I2C_SLV4_ADDR        0x31
#define REG_I2C_SLV4_REG         0x32
#define REG_I2C_SLV4_DO          0x33
#define REG_I2C_SLV4_CTRL        0x34
#define REG_I2C_SLV4_DI          0x35
#define REG_I2C_MST_STATUS       0x36
#define REG_I2C_MST_DELAY_CTRL   0x67
#define I2C_MST_CLK_400KHZ       0x0D
#define I2C_SLV_EN               0x80
#define I2C_SLV4_DONE            0x40
#define I2C_SLV4_NACK            0x10
#define I2C_READ_FLAG            0x80

/* AK8963 magnetometer inside the MPU9250 */
#define AK8963_I2C_ADDR          0x0C
#define AK8963_REG_WIA           0x00
#define AK8963_REG_ST1           0x02
#define AK8963_REG_CNTL1         0x0A
#define AK8963_REG_CNTL2         0x0B
#define AK8963_REG_ASAX          0x10
#define AK8963_WHO_AM_I          0x48
#define AK8963_CNTL1_FUSE_16BIT  0x1F
#define AK8963_CNTL1_CONT2_16BIT 0x16 /* continuous, 100 Hz, 16-bit */
#define AK8963_CNTL1_POWERDOWN   0x00
#define AK8963_CNTL2_RESET       0x01
#define AK8963_ST1_DRDY          0x01
#define AK8963_ST2_HOFL          0x08
#define AK8963_READ_LEN          8 /* ST1, HXL..HZH, ST2 */
#define AK8963_MGAUSS_PER_LSB    1.5f /* 16-bit mode: 0.15 uT */

/* What goes down the queue: temperature + accel + gyro, as the sensors
 * module expects from a gyro/accel instance. */
#define SENSOR_COUNT     2
#define SENSOR_DATA_SIZE (sizeof(PIOS_SENSORS_3Axis_SensorsWithTemp) + sizeof(Vector3i16) * SENSOR_COUNT)

enum pios_invensense_dev_magic {
    PIOS_INVENSENSE_DEV_MAGIC = 0x9250a1f1,
};

struct invensense_dev {
    uint32_t spi_id;
    uint32_t slave_num;
    QueueHandle_t queue;
    const struct pios_invensense_cfg *cfg;
    enum pios_invensense_gyro_range  gyro_range;
    enum pios_invensense_accel_range accel_range;
    uint8_t whoami;
    bool    configured;
    enum pios_invensense_dev_magic   magic;

    /* When the interrupt finds SPI busy (the baro shares the bus) it hands
     * the read to this task, which waits for the bus like any task. */
    SemaphoreHandle_t deferred;
    TaskHandle_t reader;

    /* diagnostics */
    uint32_t irqs;
    uint32_t bus_fails;
    uint32_t queue_full;

    /* AK8963 behind the I2C master */
    bool     has_mag;
    int32_t  mag_init_rc;
    float    mag_asa[3];
    uint32_t mag_samples;
    uint32_t mag_overflow;
    uint8_t  last_mag[AK8963_READ_LEN];
    volatile bool mag_new;
    Vector3i16 mag_sample; /* body frame, factory adjustment applied */
};

/* One instance: the sensor-subsystem callbacks carry no handle. */
static struct invensense_dev *dev;

/* Queue item, built in the interrupt and in the reader task. */
static PIOS_SENSORS_3Axis_SensorsWithTemp *queue_data;

static int32_t PIOS_INVENSENSE_Validate(struct invensense_dev *d);
static int32_t PIOS_INVENSENSE_Config(struct invensense_dev *d);
static int32_t PIOS_INVENSENSE_SetReg(struct invensense_dev *d, uint8_t reg, uint8_t data);
static int32_t PIOS_INVENSENSE_GetReg(struct invensense_dev *d, uint8_t reg);
static void PIOS_INVENSENSE_ReaderTask(void *parameters);

/* sensor subsystem glue */
static bool PIOS_INVENSENSE_driver_Test(uintptr_t context);
static void PIOS_INVENSENSE_driver_Reset(uintptr_t context);
static void PIOS_INVENSENSE_driver_get_scale(float *scales, uint8_t size, uintptr_t context);
static QueueHandle_t PIOS_INVENSENSE_driver_get_queue(uintptr_t context);
static bool PIOS_INVENSENSE_mag_poll(uintptr_t context);
static void PIOS_INVENSENSE_mag_fetch(void *data, uint8_t size, uintptr_t context);
static void PIOS_INVENSENSE_mag_get_scale(float *scales, uint8_t size, uintptr_t context);

const PIOS_SENSORS_Driver PIOS_INVENSENSE_Driver = {
    .test      = PIOS_INVENSENSE_driver_Test,
    .poll      = NULL,
    .fetch     = NULL,
    .reset     = PIOS_INVENSENSE_driver_Reset,
    .get_queue = PIOS_INVENSENSE_driver_get_queue,
    .get_scale = PIOS_INVENSENSE_driver_get_scale,
    .is_polled = false,
};

const PIOS_SENSORS_Driver PIOS_INVENSENSE_Mag_Driver = {
    .test      = NULL,
    .poll      = PIOS_INVENSENSE_mag_poll,
    .fetch     = PIOS_INVENSENSE_mag_fetch,
    .reset     = NULL,
    .get_queue = NULL,
    .get_scale = PIOS_INVENSENSE_mag_get_scale,
    .is_polled = true,
};

static struct invensense_dev *PIOS_INVENSENSE_alloc(void)
{
    struct invensense_dev *d = (struct invensense_dev *)pios_malloc(sizeof(*d));

    if (!d) {
        return NULL;
    }
    memset(d, 0, sizeof(*d));
    d->magic = PIOS_INVENSENSE_DEV_MAGIC;
    d->queue = xQueueCreate(PIOS_INVENSENSE_QUEUE_LEN, SENSOR_DATA_SIZE);
    if (d->queue == NULL) {
        return NULL;
    }
    queue_data = (PIOS_SENSORS_3Axis_SensorsWithTemp *)pios_malloc(SENSOR_DATA_SIZE);
    if (!queue_data) {
        return NULL;
    }
    memset(queue_data, 0, SENSOR_DATA_SIZE);
    queue_data->count = SENSOR_COUNT;
    d->deferred = xSemaphoreCreateBinary();
    return d;
}

static int32_t PIOS_INVENSENSE_Validate(struct invensense_dev *d)
{
    if (d == NULL) {
        return -1;
    }
    if (d->magic != PIOS_INVENSENSE_DEV_MAGIC) {
        return -2;
    }
    if (d->spi_id == 0) {
        return -3;
    }
    return 0;
}

static int32_t PIOS_INVENSENSE_ClaimBus(struct invensense_dev *d, bool fast, bool from_isr, bool *woken)
{
    if (PIOS_INVENSENSE_Validate(d) != 0) {
        return -1;
    }
    if (from_isr) {
        if (PIOS_SPI_ClaimBusISR(d->spi_id, woken) != 0) {
            return -2;
        }
    } else {
        if (PIOS_SPI_ClaimBus(d->spi_id) != 0) {
            return -2;
        }
    }
    PIOS_SPI_SetClockSpeed(d->spi_id, fast ? d->cfg->fast_prescaler : d->cfg->slow_prescaler);
    PIOS_SPI_RC_PinSet(d->spi_id, d->slave_num, 0);
    return 0;
}

static int32_t PIOS_INVENSENSE_ReleaseBus(struct invensense_dev *d, bool from_isr, bool *woken)
{
    if (PIOS_INVENSENSE_Validate(d) != 0) {
        return -1;
    }
    PIOS_SPI_RC_PinSet(d->spi_id, d->slave_num, 1);
    if (from_isr) {
        return PIOS_SPI_ReleaseBusISR(d->spi_id, woken);
    }
    return PIOS_SPI_ReleaseBus(d->spi_id);
}

static int32_t PIOS_INVENSENSE_GetReg(struct invensense_dev *d, uint8_t reg)
{
    uint8_t data;

    if (PIOS_INVENSENSE_ClaimBus(d, false, false, NULL) != 0) {
        return -1;
    }
    PIOS_SPI_TransferByte(d->spi_id, PIOS_INVENSENSE_SPI_READ_FLAG | reg);
    data = PIOS_SPI_TransferByte(d->spi_id, 0);
    PIOS_INVENSENSE_ReleaseBus(d, false, NULL);
    return data;
}

/* The MPU9250 echoes on MISO during a write, which is not an error. */
static int32_t PIOS_INVENSENSE_SetReg(struct invensense_dev *d, uint8_t reg, uint8_t data)
{
    if (PIOS_INVENSENSE_ClaimBus(d, false, false, NULL) != 0) {
        return -1;
    }
    if (PIOS_SPI_TransferByte(d->spi_id, reg & 0x7f) < 0) {
        PIOS_INVENSENSE_ReleaseBus(d, false, NULL);
        return -2;
    }
    if (PIOS_SPI_TransferByte(d->spi_id, data) < 0) {
        PIOS_INVENSENSE_ReleaseBus(d, false, NULL);
        return -3;
    }
    PIOS_INVENSENSE_ReleaseBus(d, false, NULL);
    return 0;
}

/*
 * One AK8963 register transaction through slave 4, which has a done flag.
 * The master runs slave transactions at the sample rate, so a few ms.
 */
static int32_t PIOS_INVENSENSE_MagXfer(struct invensense_dev *d, uint8_t reg, uint8_t *val, bool read)
{
    if (PIOS_INVENSENSE_SetReg(d, REG_I2C_SLV4_ADDR, AK8963_I2C_ADDR | (read ? I2C_READ_FLAG : 0)) != 0 ||
        PIOS_INVENSENSE_SetReg(d, REG_I2C_SLV4_REG, reg) != 0) {
        return -1;
    }
    if (!read && PIOS_INVENSENSE_SetReg(d, REG_I2C_SLV4_DO, *val) != 0) {
        return -1;
    }
    if (PIOS_INVENSENSE_SetReg(d, REG_I2C_SLV4_CTRL, I2C_SLV_EN) != 0) {
        return -1;
    }
    for (int i = 0; i < 25; i++) {
        PIOS_DELAY_WaitmS(1);
        int32_t st = PIOS_INVENSENSE_GetReg(d, REG_I2C_MST_STATUS);
        if (st < 0) {
            return -2;
        }
        if (st & I2C_SLV4_NACK) {
            return -3;
        }
        if (st & I2C_SLV4_DONE) {
            if (read) {
                int32_t v = PIOS_INVENSENSE_GetReg(d, REG_I2C_SLV4_DI);
                if (v < 0) {
                    return -4;
                }
                *val = (uint8_t)v;
            }
            return 0;
        }
    }
    return -5; /* timed out: no master activity */
}

static int32_t PIOS_INVENSENSE_MagWrite(struct invensense_dev *d, uint8_t reg, uint8_t val)
{
    return PIOS_INVENSENSE_MagXfer(d, reg, &val, false);
}

static int32_t PIOS_INVENSENSE_MagRead(struct invensense_dev *d, uint8_t reg, uint8_t *val)
{
    return PIOS_INVENSENSE_MagXfer(d, reg, val, true);
}

/*
 * Bring up the AK8963 behind the MPU9250's I2C master: reset, identify,
 * read the factory sensitivity adjustment from the fuse ROM, put it in
 * 100 Hz 16-bit continuous mode, then let slave 0 copy ST1..ST2 into
 * EXT_SENS_DATA every fifth sample (500 Hz / 5 = the part's own rate).
 */
static int32_t PIOS_INVENSENSE_MagInit(struct invensense_dev *d)
{
    uint8_t v;
    int32_t rc;

    if (PIOS_INVENSENSE_SetReg(d, PIOS_INVENSENSE_USER_CTRL_REG, d->cfg->user_ctl | PIOS_INVENSENSE_USERCTL_I2C_MST_EN) != 0 ||
        PIOS_INVENSENSE_SetReg(d, REG_I2C_MST_CTRL, I2C_MST_CLK_400KHZ) != 0) {
        return -10;
    }
    PIOS_DELAY_WaitmS(10);
    (void)PIOS_INVENSENSE_MagWrite(d, AK8963_REG_CNTL2, AK8963_CNTL2_RESET);
    PIOS_DELAY_WaitmS(10);
    if ((rc = PIOS_INVENSENSE_MagRead(d, AK8963_REG_WIA, &v)) != 0) {
        return -20 + rc;
    }
    if (v != AK8963_WHO_AM_I) {
        return -30;
    }
    if (PIOS_INVENSENSE_MagWrite(d, AK8963_REG_CNTL1, AK8963_CNTL1_FUSE_16BIT) != 0) {
        return -40;
    }
    PIOS_DELAY_WaitmS(10);
    for (int i = 0; i < 3; i++) {
        if (PIOS_INVENSENSE_MagRead(d, AK8963_REG_ASAX + i, &v) != 0) {
            return -50 - i;
        }
        d->mag_asa[i] = ((float)v - 128.0f) / 256.0f + 1.0f;
    }
    if (PIOS_INVENSENSE_MagWrite(d, AK8963_REG_CNTL1, AK8963_CNTL1_POWERDOWN) != 0) {
        return -60;
    }
    PIOS_DELAY_WaitmS(10);
    if (PIOS_INVENSENSE_MagWrite(d, AK8963_REG_CNTL1, AK8963_CNTL1_CONT2_16BIT) != 0) {
        return -70;
    }
    PIOS_DELAY_WaitmS(10);
    /* slave 0: read 8 bytes from ST1 into EXT_SENS_DATA_00, every 5th sample */
    if (PIOS_INVENSENSE_SetReg(d, REG_I2C_SLV4_CTRL, 4) != 0 || /* I2C_MST_DLY = 4 */
        PIOS_INVENSENSE_SetReg(d, REG_I2C_MST_DELAY_CTRL, 0x01) != 0 || /* slave 0 obeys the delay */
        PIOS_INVENSENSE_SetReg(d, REG_I2C_SLV0_ADDR, AK8963_I2C_ADDR | I2C_READ_FLAG) != 0 ||
        PIOS_INVENSENSE_SetReg(d, REG_I2C_SLV0_REG, AK8963_REG_ST1) != 0 ||
        PIOS_INVENSENSE_SetReg(d, REG_I2C_SLV0_CTRL, I2C_SLV_EN | AK8963_READ_LEN) != 0) {
        return -80;
    }
    d->has_mag = true;
    return 0;
}

static int32_t PIOS_INVENSENSE_Config(struct invensense_dev *d)
{
    const struct pios_invensense_cfg *cfg = d->cfg;
    int32_t id;

    if (PIOS_INVENSENSE_SetReg(d, PIOS_INVENSENSE_PWR_MGMT_REG, PIOS_INVENSENSE_PWRMGMT_IMU_RST) != 0) {
        return -1;
    }
    PIOS_DELAY_WaitmS(100);
    if (PIOS_INVENSENSE_SetReg(d, PIOS_INVENSENSE_PWR_MGMT_REG, cfg->pwr_mgmt_clk) != 0) {
        return -2;
    }
    PIOS_DELAY_WaitmS(10);

    id = PIOS_INVENSENSE_GetReg(d, PIOS_INVENSENSE_WHOAMI);
    if (id < 0) {
        return -3;
    }
    d->whoami = (uint8_t)id;
    switch (d->whoami) {
    case PIOS_INVENSENSE_WHOAMI_MPU9250:
    case PIOS_INVENSENSE_WHOAMI_MPU9255:
        if (cfg->type == PIOS_INVENSENSE_ICM20608) {
            return -4;
        }
        break;
    case PIOS_INVENSENSE_WHOAMI_ICM20608:
    case PIOS_INVENSENSE_WHOAMI_ICM20602:
        if (cfg->type == PIOS_INVENSENSE_MPU9250) {
            return -4;
        }
        break;
    default:
        return -5;
    }

    if (PIOS_INVENSENSE_SetReg(d, PIOS_INVENSENSE_USER_CTRL_REG, cfg->user_ctl) != 0) {
        return -6;
    }
    if (PIOS_INVENSENSE_SetReg(d, PIOS_INVENSENSE_CONFIG_REG, (uint8_t)cfg->filter) != 0) {
        return -7;
    }
    if (PIOS_INVENSENSE_SetReg(d, PIOS_INVENSENSE_SMPLRT_DIV_REG, cfg->smpl_rate_div) != 0) {
        return -8;
    }
    if (PIOS_INVENSENSE_SetReg(d, PIOS_INVENSENSE_GYRO_CFG_REG, (uint8_t)cfg->gyro_range) != 0) {
        return -9;
    }
    d->gyro_range = cfg->gyro_range;
    if (PIOS_INVENSENSE_SetReg(d, PIOS_INVENSENSE_ACCEL_CFG_REG, (uint8_t)cfg->accel_range) != 0) {
        return -10;
    }
    d->accel_range = cfg->accel_range;
    if (PIOS_INVENSENSE_SetReg(d, PIOS_INVENSENSE_ACCEL_CFG2_REG, (uint8_t)cfg->filter) != 0) {
        return -11;
    }
    if (PIOS_INVENSENSE_SetReg(d, PIOS_INVENSENSE_INT_CFG_REG, cfg->int_cfg) != 0) {
        return -12;
    }
    if (PIOS_INVENSENSE_SetReg(d, PIOS_INVENSENSE_INT_EN_REG, cfg->int_en) != 0) {
        return -13;
    }
    d->configured = true;
    if (cfg->mag_ak8963) {
        /* Optional: a failure leaves the IMU running without a compass. */
        d->mag_init_rc = PIOS_INVENSENSE_MagInit(d);
    }
    return 0;
}

int32_t PIOS_INVENSENSE_Init(pios_invensense_t *handle, uint32_t spi_id,
                             uint32_t slave_num, const struct pios_invensense_cfg *cfg)
{
    PIOS_Assert(handle);
    PIOS_Assert(cfg);

    dev = PIOS_INVENSENSE_alloc();
    if (dev == NULL) {
        return -1;
    }
    dev->spi_id    = spi_id;
    dev->slave_num = slave_num;
    dev->cfg = cfg;

    if (PIOS_INVENSENSE_Config(dev) != 0) {
        return -2;
    }
    *handle = (pios_invensense_t)dev;

    xTaskCreate(PIOS_INVENSENSE_ReaderTask, "imuRd", 256, dev, tskIDLE_PRIORITY + 4, &dev->reader);

    if (cfg->exti_cfg != NULL) {
        if (PIOS_EXTI_Init(cfg->exti_cfg) != 0) {
            return -3;
        }
    }
    return 0;
}

void PIOS_INVENSENSE_Register(pios_invensense_t handle)
{
    struct invensense_dev *d = (struct invensense_dev *)handle;

    if (PIOS_INVENSENSE_Validate(d) != 0) {
        return;
    }
    PIOS_SENSORS_Register(&PIOS_INVENSENSE_Driver, PIOS_SENSORS_TYPE_3AXIS_GYRO_ACCEL, handle);
    if (d->has_mag) {
        PIOS_SENSORS_Register(&PIOS_INVENSENSE_Mag_Driver, PIOS_SENSORS_TYPE_3AXIS_MAG, handle);
    }
}

int32_t PIOS_INVENSENSE_ReadID(pios_invensense_t handle)
{
    struct invensense_dev *d = (struct invensense_dev *)handle;

    if (PIOS_INVENSENSE_Validate(d) != 0) {
        return -1;
    }
    return PIOS_INVENSENSE_GetReg(d, PIOS_INVENSENSE_WHOAMI);
}

int32_t PIOS_INVENSENSE_Test(pios_invensense_t handle)
{
    struct invensense_dev *d = (struct invensense_dev *)handle;
    int32_t id;

    if (PIOS_INVENSENSE_Validate(d) != 0) {
        return -1;
    }
    id = PIOS_INVENSENSE_GetReg(d, PIOS_INVENSENSE_WHOAMI);
    if (id < 0) {
        return -2;
    }
    if ((uint8_t)id != d->whoami) {
        return -3;
    }
    return 0;
}

float PIOS_INVENSENSE_GetGyroScale(pios_invensense_t handle)
{
    struct invensense_dev *d = (struct invensense_dev *)handle;

    if (PIOS_INVENSENSE_Validate(d) != 0) {
        return 0.0f;
    }
    switch (d->gyro_range) {
    case PIOS_INVENSENSE_SCALE_250_DEG:
        return 1.0f / 131.0f;
    case PIOS_INVENSENSE_SCALE_500_DEG:
        return 1.0f / 65.5f;
    case PIOS_INVENSENSE_SCALE_1000_DEG:
        return 1.0f / 32.8f;
    case PIOS_INVENSENSE_SCALE_2000_DEG:
        return 1.0f / 16.4f;
    }
    return 0.0f;
}

float PIOS_INVENSENSE_GetAccelScale(pios_invensense_t handle)
{
    struct invensense_dev *d = (struct invensense_dev *)handle;

    if (PIOS_INVENSENSE_Validate(d) != 0) {
        return 0.0f;
    }
    switch (d->accel_range) {
    case PIOS_INVENSENSE_ACCEL_2G:
        return GRAV / 16384.0f;
    case PIOS_INVENSENSE_ACCEL_4G:
        return GRAV / 8192.0f;
    case PIOS_INVENSENSE_ACCEL_8G:
        return GRAV / 4096.0f;
    case PIOS_INVENSENSE_ACCEL_16G:
        return GRAV / 2048.0f;
    }
    return 0.0f;
}

/* Degrees Celsius * 100, as the sensors module expects. */
static int16_t PIOS_INVENSENSE_TemperatureCenti(const struct invensense_dev *d, int16_t raw)
{
    switch (d->whoami) {
    case PIOS_INVENSENSE_WHOAMI_ICM20608:
    case PIOS_INVENSENSE_WHOAMI_ICM20602:
        return (int16_t)(2500 + ((int32_t)raw * 100) / 327);
    default:
        return (int16_t)(2100 + ((int32_t)raw * 100) / 334);
    }
}

/*
 * Chip axes to body axes, the same mapping and sign convention as the
 * MPU6000 driver: TOP_0DEG is body (chip_y, chip_x, -chip_z).
 */
static void PIOS_INVENSENSE_MapAxes(const struct invensense_dev *d, int16_t cx, int16_t cy, int16_t cz, Vector3i16 *out)
{
    switch (d->cfg->orientation) {
    case PIOS_INVENSENSE_TOP_0DEG:
        out->x = cy;
        out->y = cx;
        break;
    case PIOS_INVENSENSE_TOP_90DEG:
        out->x = cx;
        out->y = -1 - cy;
        break;
    case PIOS_INVENSENSE_TOP_180DEG:
        out->x = -1 - cy;
        out->y = -1 - cx;
        break;
    case PIOS_INVENSENSE_TOP_270DEG:
        out->x = -1 - cx;
        out->y = cy;
        break;
    /* Bottom mounts: the TOP mapping with body Y negated (Z handled below). */
    case PIOS_INVENSENSE_BOTTOM_0DEG:
        out->x = cy;
        out->y = -1 - cx;
        break;
    case PIOS_INVENSENSE_BOTTOM_90DEG:
        out->x = cx;
        out->y = cy;
        break;
    case PIOS_INVENSENSE_BOTTOM_180DEG:
        out->x = -1 - cy;
        out->y = cx;
        break;
    case PIOS_INVENSENSE_BOTTOM_270DEG:
        out->x = -1 - cx;
        out->y = -1 - cy;
        break;
    default:
        out->x = cy;
        out->y = cx;
        break;
    }
    if (d->cfg->orientation >= PIOS_INVENSENSE_BOTTOM_0DEG) {
        out->z = cz; /* upside down: chip Z already points along body Z (down) */
    } else {
        out->z = -1 - cz;
    }
}

/*
 * Turn a burst into the queue item, and keep the magnetometer sample.
 * The AK8963 sits in the same package with its axes at chip
 * (x, y, z) = mag (y, x, -z) (MPU-9250 datasheet, orientation of axes);
 * it is little-endian, unlike the gyro/accel registers.  EXT_SENS_DATA
 * keeps one transfer for five bursts, so only a changed block counts.
 */
static void PIOS_INVENSENSE_HandleData(struct invensense_dev *d, const uint8_t *raw)
{
    int16_t accel_x = (int16_t)(raw[0] << 8 | raw[1]);
    int16_t accel_y = (int16_t)(raw[2] << 8 | raw[3]);
    int16_t accel_z = (int16_t)(raw[4] << 8 | raw[5]);
    int16_t temp    = (int16_t)(raw[6] << 8 | raw[7]);
    int16_t gyro_x  = (int16_t)(raw[8] << 8 | raw[9]);
    int16_t gyro_y  = (int16_t)(raw[10] << 8 | raw[11]);
    int16_t gyro_z  = (int16_t)(raw[12] << 8 | raw[13]);

    PIOS_INVENSENSE_MapAxes(d, accel_x, accel_y, accel_z, &queue_data->sample[0]);
    PIOS_INVENSENSE_MapAxes(d, gyro_x, gyro_y, gyro_z, &queue_data->sample[1]);
    queue_data->temperature = PIOS_INVENSENSE_TemperatureCenti(d, temp);

    if (d->has_mag) {
        const uint8_t *m = &raw[PIOS_INVENSENSE_MAG_OFFSET];
        if (memcmp(m, d->last_mag, AK8963_READ_LEN) != 0) {
            memcpy(d->last_mag, m, AK8963_READ_LEN);
            uint8_t st1 = m[0], st2 = m[7];
            if ((st1 & AK8963_ST1_DRDY) && !(st2 & AK8963_ST2_HOFL)) {
                int16_t hx = (int16_t)(m[2] << 8 | m[1]);
                int16_t hy = (int16_t)(m[4] << 8 | m[3]);
                int16_t hz = (int16_t)(m[6] << 8 | m[5]);
                /* factory sensitivity, then into the chip frame, then the body */
                int16_t cx = (int16_t)((float)hy * d->mag_asa[1]);
                int16_t cy = (int16_t)((float)hx * d->mag_asa[0]);
                int16_t cz = (int16_t)(-1 - (int16_t)((float)hz * d->mag_asa[2]));
                PIOS_INVENSENSE_MapAxes(d, cx, cy, cz, &d->mag_sample);
                d->mag_new = true;
                d->mag_samples++;
            } else if (st2 & AK8963_ST2_HOFL) {
                d->mag_overflow++;
            }
        }
    }
}

/* Task-context read of one burst; used for the deferred path and resets. */
static int32_t PIOS_INVENSENSE_ReadSensors(struct invensense_dev *d)
{
    uint8_t tx[1 + PIOS_INVENSENSE_BURST_LEN];
    uint8_t rx[1 + PIOS_INVENSENSE_BURST_LEN];

    if (PIOS_INVENSENSE_Validate(d) != 0) {
        return -1;
    }
    memset(tx, 0, sizeof(tx));
    tx[0] = PIOS_INVENSENSE_SPI_READ_FLAG | PIOS_INVENSENSE_ACCEL_X_OUT_MSB;
    if (PIOS_INVENSENSE_ClaimBus(d, true, false, NULL) != 0) {
        return -2;
    }
    if (PIOS_SPI_TransferBlock(d->spi_id, tx, rx, sizeof(tx), NULL) < 0) {
        PIOS_INVENSENSE_ReleaseBus(d, false, NULL);
        return -3;
    }
    PIOS_INVENSENSE_ReleaseBus(d, false, NULL);
    PIOS_INVENSENSE_HandleData(d, &rx[1]);
    return 0;
}

/*
 * The interrupt could not read the part (SPI held by another driver):
 * read it here, blocking on the bus mutex, which lends the holder this
 * task's priority, so the sample is only microseconds late instead of
 * lost and the sensors task never sees a hole.
 */
static void PIOS_INVENSENSE_ReaderTask(void *parameters)
{
    struct invensense_dev *d = (struct invensense_dev *)parameters;

    while (1) {
        if (xSemaphoreTake(d->deferred, portMAX_DELAY) != pdTRUE) {
            continue;
        }
        if (PIOS_INVENSENSE_ReadSensors(d) == 0) {
            if (xQueueSendToBack(d->queue, (void *)queue_data, 0) != pdTRUE) {
                d->queue_full++;
            }
        }
    }
}

/**
 * @brief Data-ready interrupt: burst-read the part and queue the sample.
 */
bool PIOS_INVENSENSE_IRQHandler(pios_invensense_t handle)
{
    struct invensense_dev *d = (struct invensense_dev *)handle;
    static uint8_t tx[1 + PIOS_INVENSENSE_BURST_LEN];
    static uint8_t rx[1 + PIOS_INVENSENSE_BURST_LEN];
    bool woken = false;
    BaseType_t task_woken = pdFALSE;

    if (PIOS_INVENSENSE_Validate(d) != 0 || !d->configured || !queue_data) {
        return false;
    }
    tx[0] = PIOS_INVENSENSE_SPI_READ_FLAG | PIOS_INVENSENSE_ACCEL_X_OUT_MSB;

    bool bus_ok = (PIOS_INVENSENSE_ClaimBus(d, true, true, &woken) == 0);
    if (bus_ok) {
        if (PIOS_SPI_TransferBlock(d->spi_id, tx, rx, sizeof(tx), NULL) < 0) {
            bus_ok = false;
        }
        PIOS_INVENSENSE_ReleaseBus(d, true, &woken);
    }
    if (!bus_ok) {
        d->bus_fails++;
        xSemaphoreGiveFromISR(d->deferred, &task_woken);
        return woken || (task_woken == pdTRUE);
    }
    PIOS_INVENSENSE_HandleData(d, &rx[1]);
    if (xQueueSendToBackFromISR(d->queue, (void *)queue_data, &task_woken) != pdTRUE) {
        d->queue_full++;
    }
    d->irqs++;
    return woken || (task_woken == pdTRUE);
}

void PIOS_INVENSENSE_GetStats(pios_invensense_t handle, uint32_t *irqs, uint32_t *bus_fails, uint32_t *queue_full)
{
    struct invensense_dev *d = (struct invensense_dev *)handle;

    if (PIOS_INVENSENSE_Validate(d) != 0) {
        return;
    }
    if (irqs) {
        *irqs = d->irqs;
    }
    if (bus_fails) {
        *bus_fails = d->bus_fails;
    }
    if (queue_full) {
        *queue_full = d->queue_full;
    }
}

void PIOS_INVENSENSE_GetMagStats(pios_invensense_t handle, uint32_t *samples, uint32_t *overflow, int32_t *init_rc)
{
    struct invensense_dev *d = (struct invensense_dev *)handle;

    if (PIOS_INVENSENSE_Validate(d) != 0) {
        return;
    }
    if (samples) {
        *samples = d->mag_samples;
    }
    if (overflow) {
        *overflow = d->mag_overflow;
    }
    if (init_rc) {
        *init_rc = d->mag_init_rc;
    }
}

/**********************************
 * sensor subsystem glue
 **********************************/

static bool PIOS_INVENSENSE_driver_Test(uintptr_t context)
{
    return PIOS_INVENSENSE_Test((pios_invensense_t)context) == 0;
}

/* Nothing arrived in time: a read clears the interrupt line and gets the
 * data-ready edges going again. */
static void PIOS_INVENSENSE_driver_Reset(uintptr_t context)
{
    struct invensense_dev *d = (struct invensense_dev *)context;

    if (PIOS_INVENSENSE_Validate(d) == 0) {
        PIOS_INVENSENSE_ReadSensors(d);
    }
}

static void PIOS_INVENSENSE_driver_get_scale(float *scales, uint8_t size, uintptr_t context)
{
    PIOS_Assert(size >= 2);
    scales[0] = PIOS_INVENSENSE_GetAccelScale((pios_invensense_t)context);
    scales[1] = PIOS_INVENSENSE_GetGyroScale((pios_invensense_t)context);
}

static QueueHandle_t PIOS_INVENSENSE_driver_get_queue(uintptr_t context)
{
    struct invensense_dev *d = (struct invensense_dev *)context;

    if (PIOS_INVENSENSE_Validate(d) != 0) {
        return NULL;
    }
    return d->queue;
}

static bool PIOS_INVENSENSE_mag_poll(uintptr_t context)
{
    struct invensense_dev *d = (struct invensense_dev *)context;

    if (PIOS_INVENSENSE_Validate(d) != 0) {
        return false;
    }
    return d->mag_new;
}

static void PIOS_INVENSENSE_mag_fetch(void *data, uint8_t size, uintptr_t context)
{
    struct invensense_dev *d = (struct invensense_dev *)context;
    PIOS_SENSORS_3Axis_SensorsWithTemp *tmp = data;

    PIOS_Assert(size > 0);
    if (PIOS_INVENSENSE_Validate(d) != 0) {
        return;
    }
    tmp->count = 1;
    tmp->temperature = 0;
    tmp->sample[0]   = d->mag_sample;
    d->mag_new = false;
}

static void PIOS_INVENSENSE_mag_get_scale(float *scales, uint8_t size, __attribute__((unused)) uintptr_t context)
{
    PIOS_Assert(size > 0);
    scales[0] = AK8963_MGAUSS_PER_LSB;
}

#endif /* PIOS_INCLUDE_INVENSENSE */

/**
 * @}
 * @}
 */
