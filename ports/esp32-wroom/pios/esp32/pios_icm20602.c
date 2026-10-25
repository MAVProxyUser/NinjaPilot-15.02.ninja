/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core haoftware; you can rnedtt
 * @{
 * @addtogroup PIOS_ICM20602 ICM20602 Functions
 * @brief Deals with the hardware interface to the 3-axis gyro
 * @{
 *
 * @file       pios_mpu000.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @brief      ICM20602 6-axis gyro and accel chip
 * @see        The GNU Public License (GPL) Version 3
 *
 ******************************************************************************
 */
/*istribu
 * This program is free software; you can rnedtt ad/oe ir modify
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
#include "esp_timer.h"
#include <pios_icm20602.h>
#ifdef PIOS_INCLUDE_ICM20602
#include <stdint.h>
#include <pios_constants.h>
#include <pios_sensors.h>

/* Global Variables */

enum pios_icm20602_dev_magic {
    PIOS_ICM20602_DEV_MAGIC = 0x9da9b3ed,
};

// sensor driver interface
bool PIOS_ICM20602_driver_Test(uintptr_t context);
void PIOS_ICM20602_driver_Reset(uintptr_t context);
void PIOS_ICM20602_driver_get_scale(float *scales, uint8_t size, uintptr_t context);
QueueHandle_t PIOS_ICM20602_driver_get_queue(uintptr_t context);

const PIOS_SENSORS_Driver PIOS_ICM20602_Driver = {
    .test      = PIOS_ICM20602_driver_Test,
    .poll      = NULL,
    .fetch     = NULL,
    .reset     = PIOS_ICM20602_driver_Reset,
    .get_queue = PIOS_ICM20602_driver_get_queue,
    .get_scale = PIOS_ICM20602_driver_get_scale,
    .is_polled = false,
};
//


struct icm20602_dev {
    uint32_t spi_id;
    uint32_t slave_num;
    QueueHandle_t queue;
    const struct pios_icm20602_cfg *cfg;
    enum pios_icm20602_range gyro_range;
    enum pios_icm20602_accel_range accel_range;
    enum pios_icm20602_filter filter;
    enum pios_icm20602_dev_magic   magic;
};

#define PIOS_ICM20602_SAMPLES_BYTES    14
#define PIOS_ICM20602_SENSOR_FIRST_REG PIOS_ICM20602_ACCEL_X_OUT_MSB

typedef union {
    uint8_t buffer[1 + PIOS_ICM20602_SAMPLES_BYTES];
    struct {
        uint8_t dummy;
        uint8_t Accel_X_h;
        uint8_t Accel_X_l;
        uint8_t Accel_Y_h;
        uint8_t Accel_Y_l;
        uint8_t Accel_Z_h;
        uint8_t Accel_Z_l;
        uint8_t Temperature_h;
        uint8_t Temperature_l;
        uint8_t Gyro_X_h;
        uint8_t Gyro_X_l;
        uint8_t Gyro_Y_h;
        uint8_t Gyro_Y_l;
        uint8_t Gyro_Z_h;
        uint8_t Gyro_Z_l;
    } data;
} icm20602_data_t;

#define GET_SENSOR_DATA(mpudataptr, sensor) (mpudataptr.data.sensor##_h << 8 | mpudataptr.data.sensor##_l)

// ! Global structure for this device device
static struct icm20602_dev *dev;
volatile bool icm20602_configured = false;
/* WHO_AM_I of the part actually found. Selects the temperature slope, which is
 * part-specific across this otherwise register-compatible family. 0 until
 * PIOS_ICM20602_ReadID() has run. */
static uint8_t icm_whoami;
static icm20602_data_t icm20602_data;

/* ---------------------------------------------------------------------------
 * Optional I2C transport.
 *
 * This part family is register-compatible across MPU6000 / MPU6050 / MPU6500 /
 * ICM-20602 for everything this driver touches -- the same WHO_AM_I gate, the
 * same config registers, the same 14-byte burst from ACCEL_XOUT_H. Only the
 * bus differs. LiteWing carries an MPU6050 on I2C0 (SCL 10 / SDA 11) where the
 * Thing Plus has an ICM-20602 on SPI, so rather than fork 770 lines of
 * data-ready task, queue handling, scaling and sanity checks, the three
 * functions that actually touch the bus dispatch on a transport flag.
 *
 * Blocking I2C here is fine: the data-ready path on this port runs in a TASK,
 * not an ISR (see pios/esp32/pios_exti.c for why).
 * ------------------------------------------------------------------------- */
#ifdef PIOS_INCLUDE_I2C
static bool     icm_use_i2c;
static uint32_t icm_i2c_id;
static uint8_t  icm_i2c_addr;

static int32_t PIOS_ICM20602_I2C_Write(uint8_t reg, uint8_t data)
{
    uint8_t buf[2] = { reg, data };
    const struct pios_i2c_txn txn_list[] = {
        { .info = __func__, .addr = icm_i2c_addr, .rw = PIOS_I2C_TXN_WRITE,
          .len = sizeof(buf), .buf = buf },
    };

    return PIOS_I2C_Transfer(icm_i2c_id, txn_list, NELEMENTS(txn_list));
}

static int32_t PIOS_ICM20602_I2C_Read(uint8_t reg, uint8_t *dst, uint8_t len)
{
    const struct pios_i2c_txn txn_list[] = {
        { .info = __func__, .addr = icm_i2c_addr, .rw = PIOS_I2C_TXN_WRITE,
          .len = 1, .buf = &reg },
        { .info = __func__, .addr = icm_i2c_addr, .rw = PIOS_I2C_TXN_READ,
          .len = len, .buf = dst },
    };

    return PIOS_I2C_Transfer(icm_i2c_id, txn_list, NELEMENTS(txn_list));
}
#else  /* !PIOS_INCLUDE_I2C -- SPI-only target; no I2C symbols to link against */
/* The transport branches below are compiled but never taken: icm_use_i2c is a
 * constant false, so the optimiser drops them. They still have to PARSE, so
 * the helpers need declarations that resolve to nothing. */
#define icm_use_i2c false
static inline int32_t PIOS_ICM20602_I2C_Write(uint8_t reg, uint8_t data)
{
    (void)reg; (void)data;
    return -1;
}
static inline int32_t PIOS_ICM20602_I2C_Read(uint8_t reg, uint8_t *dst, uint8_t len)
{
    (void)reg; (void)dst; (void)len;
    return -1;
}
#endif /* PIOS_INCLUDE_I2C */

static PIOS_SENSORS_3Axis_SensorsWithTemp *queue_data = 0;
#define SENSOR_COUNT     2
#define SENSOR_DATA_SIZE (sizeof(PIOS_SENSORS_3Axis_SensorsWithTemp) + sizeof(Vector3i16) * SENSOR_COUNT)
// ! Private functions
static struct icm20602_dev *PIOS_ICM20602_alloc(const struct pios_icm20602_cfg *cfg);
static int32_t PIOS_ICM20602_Validate(struct icm20602_dev *dev);
static void PIOS_ICM20602_Config(struct pios_icm20602_cfg const *cfg);
static int32_t PIOS_ICM20602_SetReg(uint8_t address, uint8_t buffer);
static int32_t PIOS_ICM20602_GetReg(uint8_t address);
static void PIOS_ICM20602_SetSpeed(const bool fast);
static bool PIOS_ICM20602_HandleData();
static bool PIOS_ICM20602_ReadSensor(bool *woken);

static int32_t PIOS_ICM20602_Test(void);

void PIOS_ICM20602_Register()
{
    PIOS_SENSORS_Register(&PIOS_ICM20602_Driver, PIOS_SENSORS_TYPE_3AXIS_GYRO_ACCEL, 0);
}
/**
 * @brief Allocate a new device
 */
static struct icm20602_dev *PIOS_ICM20602_alloc(const struct pios_icm20602_cfg *cfg)
{
    struct icm20602_dev *icm20602_dev;

    icm20602_dev = (struct icm20602_dev *)pios_malloc(sizeof(*icm20602_dev));
    PIOS_Assert(icm20602_dev);

    icm20602_dev->magic = PIOS_ICM20602_DEV_MAGIC;

    icm20602_dev->queue = xQueueCreate(cfg->max_downsample + 1, SENSOR_DATA_SIZE);
    PIOS_Assert(icm20602_dev->queue);

    queue_data = (PIOS_SENSORS_3Axis_SensorsWithTemp *)pios_malloc(SENSOR_DATA_SIZE);
    PIOS_Assert(queue_data);
    queue_data->count = SENSOR_COUNT;
    return icm20602_dev;
}

/**
 * @brief Validate the handle to the spi device
 * @returns 0 for valid device or -1 otherwise
 */
static int32_t PIOS_ICM20602_Validate(struct icm20602_dev *vdev)
{
    if (vdev == NULL) {
        return -1;
    }
    if (vdev->magic != PIOS_ICM20602_DEV_MAGIC) {
        return -2;
    }
    if (vdev->spi_id == 0) {
        return -3;
    }
    return 0;
}

/**
 * @brief Initialize the ICM20602 3-axis gyro sensor.
 * @return 0 for success, -1 for failure
 */
#ifdef PIOS_INCLUDE_I2C
/**
 * @brief Initialise this part over I2C instead of SPI (MPU6050 on LiteWing).
 * @param[in] i2c_id   the I2C adapter the part sits on
 * @param[in] i2c_addr 0x68 with AD0 low, 0x69 with AD0 high
 */
int32_t PIOS_ICM20602_InitI2C(uint32_t i2c_id, uint8_t i2c_addr, const struct pios_icm20602_cfg *cfg)
{
    icm_use_i2c  = true;
    icm_i2c_id   = i2c_id;
    icm_i2c_addr = i2c_addr ? i2c_addr : 0x68;

    dev = PIOS_ICM20602_alloc(cfg);
    if (dev == NULL) {
        return -1;
    }
    dev->cfg = cfg;
    PIOS_ICM20602_Config(cfg);
    return 0;
}
#endif /* PIOS_INCLUDE_I2C */

int32_t PIOS_ICM20602_Init(uint32_t spi_id, uint32_t slave_num, const struct pios_icm20602_cfg *cfg)
{
    dev = PIOS_ICM20602_alloc(cfg);
    if (dev == NULL) {
        return -1;
    }

    dev->spi_id    = spi_id;
    dev->slave_num = slave_num;
    dev->cfg = cfg;

    /* Configure the ICM20602 Sensor */
    PIOS_ICM20602_Config(cfg);

    /* Set up EXTI line */
    PIOS_EXTI_Init(cfg->exti_cfg);
    return 0;
}

/**
 * @brief Initialize the ICM20602 3-axis gyro sensor
 * \return none
 * \param[in] PIOS_ICM20602_ConfigTypeDef struct to be used to configure sensor.
 *
 */

/*
 * Bounded register write.
 *
 * PIOS_ICM20602_Config() originally retried each write with an unbounded
 * `PIOS_ICM20602_SetRegBounded(...);`. SetReg reports failure when
 * the byte clocked back on MISO is non-zero, so a miswired or absent device
 * (MISO floating high = 0xFF) makes every write "fail" and board init hangs
 * forever, before telemetry ever starts. The board then looks completely
 * dead: no console output, no core dump, no reset.
 */
#define PIOS_ICM20602_SETREG_RETRIES 10

static bool PIOS_ICM20602_SetRegBounded(uint8_t reg, uint8_t data)
{
    for (uint8_t i = 0; i < PIOS_ICM20602_SETREG_RETRIES; i++) {
        if (PIOS_ICM20602_SetReg(reg, data) == 0) {
            return true;
        }
    }
    return false;
}

/*
 * Is the accelerometer producing usable numbers?
 *
 * A reset reloads the factory offset trim out of the part's OTP. If that
 * reload is cut short, one axis comes back with a garbage trim and its output
 * sits at exactly INT16_MIN for as long as the part stays powered -- observed
 * on an ICM-20602 as YA_OFFS reading 0x8020 instead of 0xFE20, pinning chip Y
 * at -32768 while X, Z and all three gyro axes stayed correct.
 *
 * Nothing in the configuration registers reflects this, so the only way to
 * catch it is to look at the data. Saturation on a board that is merely
 * sitting still is not a real reading.
 */
static bool PIOS_ICM20602_AccelSane(void)
{
    static const uint8_t msb[3] = {
        PIOS_ICM20602_ACCEL_X_OUT_MSB,
        PIOS_ICM20602_ACCEL_Y_OUT_MSB,
        PIOS_ICM20602_ACCEL_Z_OUT_MSB,
    };

    for (uint8_t a = 0; a < 3; a++) {
        int32_t h = PIOS_ICM20602_GetReg(msb[a]);
        int32_t l = PIOS_ICM20602_GetReg(msb[a] + 1);

        if (h < 0 || l < 0) {
            return false;
        }
        if ((int16_t)((h << 8) | l) == INT16_MIN) {
            return false;
        }
    }
    return true;
}

/* How many reset/configure passes it took to get sane accel data. Left
 * visible so a board that only just scraped in can be told from one that
 * came up first time. */
uint8_t icm20602_config_attempts;

#define PIOS_ICM20602_CONFIG_ATTEMPTS 6

static void PIOS_ICM20602_ConfigOnce(struct pios_icm20602_cfg const *cfg)
{
    PIOS_ICM20602_Test();

    // Reset chip
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_PWR_MGMT_REG, PIOS_ICM20602_PWRMGMT_IMU_RST);

    /* Wait for DEVICE_RESET to actually self-clear rather than assuming a
     * fixed delay covers it, then give the OTP trim reload time to finish.
     * The original 50ms flat wait lost this race on roughly half of all
     * boots -- see PIOS_ICM20602_AccelSane() for what that looks like. */
    for (uint16_t i = 0; i < 250; i++) {
        int32_t pm = PIOS_ICM20602_GetReg(PIOS_ICM20602_PWR_MGMT_REG);

        if (pm >= 0 && !(pm & PIOS_ICM20602_PWRMGMT_IMU_RST)) {
            break;
        }
        PIOS_DELAY_WaitmS(1);
    }
    PIOS_DELAY_WaitmS(100);

    // Reset chip and fifo
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_USER_CTRL_REG,
                               PIOS_ICM20602_USERCTL_GYRO_RST |
                               PIOS_ICM20602_USERCTL_SIG_COND |
                               PIOS_ICM20602_USERCTL_FIFO_RST);

    // Wait for reset to finish
    /* Bounded for the same reason as the writes above. */
    for (uint8_t i = 0; i < PIOS_ICM20602_SETREG_RETRIES; i++) {
        int32_t uc = PIOS_ICM20602_GetReg(PIOS_ICM20602_USER_CTRL_REG);

        if (uc < 0 || !(uc & (PIOS_ICM20602_USERCTL_GYRO_RST |
                              PIOS_ICM20602_USERCTL_SIG_COND |
                              PIOS_ICM20602_USERCTL_FIFO_RST))) {
            break;
        }
        PIOS_DELAY_WaitmS(1);
    }
    PIOS_DELAY_WaitmS(10);
    // Power management configuration
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_PWR_MGMT_REG, cfg->Pwr_mgmt_clk);

    // Interrupt configuration
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_INT_CFG_REG, cfg->interrupt_cfg);

    // Interrupt configuration
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_INT_EN_REG, cfg->interrupt_en);

    // FIFO storage
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_FIFO_EN_REG, cfg->Fifo_store);
    PIOS_ICM20602_ConfigureRanges(cfg->gyro_range, cfg->accel_range, cfg->filter);
    // Interrupt configuration
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_USER_CTRL_REG, cfg->User_ctl);

    // Interrupt configuration
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_PWR_MGMT_REG, cfg->Pwr_mgmt_clk);

    // Interrupt configuration
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_INT_CFG_REG, cfg->interrupt_cfg);

    // Interrupt configuration
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_INT_EN_REG, cfg->interrupt_en);
    if ((PIOS_ICM20602_GetReg(PIOS_ICM20602_INT_EN_REG)) != cfg->interrupt_en) {
        return;
    }

    icm20602_configured = true;
}

static void PIOS_ICM20602_Config(struct pios_icm20602_cfg const *cfg)
{
    for (uint8_t attempt = 1; attempt <= PIOS_ICM20602_CONFIG_ATTEMPTS; attempt++) {
        icm20602_config_attempts = attempt;
        PIOS_ICM20602_ConfigOnce(cfg);

        if (icm20602_configured && PIOS_ICM20602_AccelSane()) {
            return;
        }
    }
    /* Out of attempts. Leave icm20602_configured as the last pass set it and
     * let the board-level WHO_AM_I/alarm reporting carry the bad news --
     * refusing to configure at all would hang module init. */
}
/**
 * @brief Configures Gyro, accel and Filter ranges/setings
 * @return 0 if successful, -1 if device has not been initialized
 */
int32_t PIOS_ICM20602_ConfigureRanges(
    enum pios_icm20602_range gyroRange,
    enum pios_icm20602_accel_range accelRange,
    enum pios_icm20602_filter filterSetting)
{
    if (dev == NULL) {
        return -1;
    }

    // update filter settings
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_DLPF_CFG_REG, filterSetting);

    /*
     * SMPLRT_DIV only divides anything while the DLPF is engaged. DLPF_CFG 0
     * and 7 BOTH bypass it and run the gyro at 8kHz, where the divider is
     * ignored. The MPU6000 driver tested only for 0, so selecting 7 would
     * have quietly produced an 8kHz sample stream.
     */
    bool dlpf_bypassed = ((uint8_t)filterSetting == 0x00) ||
                         ((uint8_t)filterSetting == 0x07);

    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_SMPLRT_DIV_REG,
                                dlpf_bypassed ? dev->cfg->Smpl_rate_div_no_dlp
                                              : dev->cfg->Smpl_rate_div_dlp);

    /*
     * Accel DLPF (0x1D). This register does not exist on the MPU6000, so that
     * driver never wrote it and left the accelerometer at a different
     * bandwidth from the gyro. Match them.
     */
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_ACCEL_CFG2_REG,
                                dlpf_bypassed ? 0x00 : (uint8_t)filterSetting);

    dev->filter = filterSetting;

    // Gyro range
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_GYRO_CFG_REG, gyroRange);

    dev->gyro_range = gyroRange;
    // Set the accel range
    PIOS_ICM20602_SetRegBounded(PIOS_ICM20602_ACCEL_CFG_REG, accelRange);

    dev->accel_range = accelRange;
    return 0;
}

/**
 * @brief Claim the SPI bus for the accel communications and select this chip
 * @return 0 if successful, -1 for invalid device, -2 if unable to claim bus
 */
static int32_t PIOS_ICM20602_ClaimBus(bool fast_spi)
{
    if (PIOS_ICM20602_Validate(dev) != 0) {
        return -1;
    }
    if (PIOS_SPI_ClaimBus(dev->spi_id) != 0) {
        return -2;
    }
    PIOS_ICM20602_SetSpeed(fast_spi);
    PIOS_SPI_RC_PinSet(dev->spi_id, dev->slave_num, 0);
    return 0;
}


static void PIOS_ICM20602_SetSpeed(const bool fast)
{
    if (fast) {
        PIOS_SPI_SetClockSpeed(dev->spi_id, dev->cfg->fast_prescaler);
    } else {
        PIOS_SPI_SetClockSpeed(dev->spi_id, dev->cfg->std_prescaler);
    }
}

/**
 * @brief Claim the SPI bus for the accel communications and select this chip
 * @return 0 if successful, -1 for invalid device, -2 if unable to claim bus
 * @param woken[in,out] If non-NULL, will be set to true if woken was false and a higher priority
 *                      task has is now eligible to run, else unchanged
 */
static int32_t PIOS_ICM20602_ClaimBusISR(bool *woken, bool fast_spi)
{
    if (PIOS_ICM20602_Validate(dev) != 0) {
        return -1;
    }
    if (PIOS_SPI_ClaimBusISR(dev->spi_id, woken) != 0) {
        return -2;
    }
    /* Select the slave BEFORE the speed, the same order PIOS_ICM20602_ClaimBus()
     * uses. A PIOS_SPI back end that tracks speed per slave cannot honour
     * SetSpeed until it knows which slave is being addressed; called the other
     * way round it silently keeps whatever speed the previous transfer left
     * behind, which on the ESP32 port made the streaming reads run at the
     * configuration clock instead of the fast one. */
    PIOS_SPI_RC_PinSet(dev->spi_id, dev->slave_num, 0);
    PIOS_ICM20602_SetSpeed(fast_spi);
    return 0;
}

/**
 * @brief Release the SPI bus for the accel communications and end the transaction
 * @return 0 if successful
 */
static int32_t PIOS_ICM20602_ReleaseBus()
{
    if (PIOS_ICM20602_Validate(dev) != 0) {
        return -1;
    }
    PIOS_SPI_RC_PinSet(dev->spi_id, dev->slave_num, 1);
    return PIOS_SPI_ReleaseBus(dev->spi_id);
}

/**
 * @brief Release the SPI bus for the accel communications and end the transaction
 * @return 0 if successful
 * @param woken[in,out] If non-NULL, will be set to true if woken was false and a higher priority
 *                      task has is now eligible to run, else unchanged
 */
static int32_t PIOS_ICM20602_ReleaseBusISR(bool *woken)
{
    if (PIOS_ICM20602_Validate(dev) != 0) {
        return -1;
    }
    PIOS_SPI_RC_PinSet(dev->spi_id, dev->slave_num, 1);
    return PIOS_SPI_ReleaseBusISR(dev->spi_id, woken);
}

/**
 * @brief Read a register from ICM20602
 * @returns The register value or -1 if failure to get bus
 * @param reg[in] Register address to be read
 */
static int32_t PIOS_ICM20602_GetReg(uint8_t reg)
{
    uint8_t data;

    if (icm_use_i2c) {
        if (PIOS_ICM20602_I2C_Read(reg, &data, 1) != 0) {
            return -1;
        }
        return data;
    }
    if (PIOS_ICM20602_ClaimBus(false) != 0) {
        return -1;
    }

    PIOS_SPI_TransferByte(dev->spi_id, (0x80 | reg)); // request byte
    data = PIOS_SPI_TransferByte(dev->spi_id, 0); // receive response

    PIOS_ICM20602_ReleaseBus();
    return data;
}

/**
 * @brief Writes one byte to the ICM20602
 * \param[in] reg Register address
 * \param[in] data Byte to write
 * \return 0 if operation was successful
 * \return -1 if unable to claim SPI bus
 * \return -2 if unable to claim i2c device
 */
static int32_t PIOS_ICM20602_SetReg(uint8_t reg, uint8_t data)
{
    if (icm_use_i2c) {
        return PIOS_ICM20602_I2C_Write(reg, data);
    }
    if (PIOS_ICM20602_ClaimBus(false) != 0) {
        return -1;
    }

    if (PIOS_SPI_TransferByte(dev->spi_id, 0x7f & reg) != 0) {
        PIOS_ICM20602_ReleaseBus();
        return -2;
    }

    if (PIOS_SPI_TransferByte(dev->spi_id, data) != 0) {
        PIOS_ICM20602_ReleaseBus();
        return -3;
    }

    PIOS_ICM20602_ReleaseBus();

    return 0;
}

/**
 * @brief Perform a dummy read in order to restart interrupt generation
 * \returns 0 if succesful
 */
int32_t PIOS_ICM20602_DummyReadGyros()
{
    // THIS FUNCTION IS DEPRECATED AND DOES NOT PERFORM A ROTATION
    uint8_t buf[7] = { PIOS_ICM20602_GYRO_X_OUT_MSB | 0x80, 0, 0, 0, 0, 0, 0 };
    uint8_t rec[7];

    if (PIOS_ICM20602_ClaimBus(true) != 0) {
        return -1;
    }

    if (PIOS_SPI_TransferBlock(dev->spi_id, &buf[0], &rec[0], sizeof(buf), NULL) < 0) {
        return -2;
    }

    PIOS_ICM20602_ReleaseBus();

    return 0;
}

/*
 * @brief Read the identification bytes from the ICM20602 sensor
 * \return ID read from ICM20602 or -1 if failure
 */
int32_t PIOS_ICM20602_ReadID()
{
    int32_t icm20602_id = PIOS_ICM20602_GetReg(PIOS_ICM20602_WHOAMI);

    if (icm20602_id >= 0) {
        icm_whoami = (uint8_t)icm20602_id;
    }

    if (icm20602_id < 0) {
        return -1;
    }
    return icm20602_id;
}

/**
 * \brief Reads the queue handle
 * \return Handle to the queue or null if invalid device
 */
xQueueHandle PIOS_ICM20602_GetQueue()
{
    if (PIOS_ICM20602_Validate(dev) != 0) {
        return (xQueueHandle)NULL;
    }

    return dev->queue;
}


static float PIOS_ICM20602_GetScale()
{
    switch (dev->gyro_range) {
    case PIOS_ICM20602_SCALE_250_DEG:
        return 1.0f / 131.0f;

    case PIOS_ICM20602_SCALE_500_DEG:
        return 1.0f / 65.5f;

    case PIOS_ICM20602_SCALE_1000_DEG:
        return 1.0f / 32.8f;

    case PIOS_ICM20602_SCALE_2000_DEG:
        return 1.0f / 16.4f;
    }
    return 0;
}

static float PIOS_ICM20602_GetAccelScale()
{
    switch (dev->accel_range) {
    case PIOS_ICM20602_ACCEL_2G:
        return PIOS_CONST_MKS_GRAV_ACCEL_F / 16384.0f;

    case PIOS_ICM20602_ACCEL_4G:
        return PIOS_CONST_MKS_GRAV_ACCEL_F / 8192.0f;

    case PIOS_ICM20602_ACCEL_8G:
        return PIOS_CONST_MKS_GRAV_ACCEL_F / 4096.0f;

    case PIOS_ICM20602_ACCEL_16G:
        return PIOS_CONST_MKS_GRAV_ACCEL_F / 2048.0f;
    }
    return 0;
}

/**
 * @brief Run self-test operation.
 * \return 0 if test succeeded
 * \return non-zero value if test succeeded
 */
/*
 * This driver is for the ICM-20602 and nothing else.
 *
 * It was derived from PiOS's MPU6000 driver because the two share enough of
 * the register map to have made that work: the 14-byte burst from
 * ACCEL_XOUT_H (0x3B) has the same AX/AY/AZ/TEMP/GX/GY/GZ layout, and CONFIG
 * (0x1A) / GYRO_CONFIG (0x1B) / ACCEL_CONFIG (0x1C) / SMPLRT_DIV (0x19) /
 * INT_ENABLE (0x38) / USER_CTRL (0x6A) / PWR_MGMT_1 (0x6B) agree, with
 * identical LSB-per-unit scaling for every full-scale code.
 *
 * They are NOT the same part, and the differences are exactly what bit us:
 *
 *   - temperature has a different slope and offset (326.8 LSB/degC at
 *     +25degC here; 340 and +36.53degC there)
 *   - ACCEL_CONFIG2 (0x1D) exists here and not there, so the accel bandwidth
 *     was never set at all
 *   - the same DLPF encoding means different bandwidths: 0x01 is 176Hz here,
 *     188Hz there
 *
 * So the ID gate accepts one value. A part answering 0x68 or 0x70 is an
 * MPU6000 or MPU6500 and wants the shared-tree driver; accepting it here is
 * the "compatible enough" reasoning that produced a wrong temperature nobody
 * noticed for weeks.
 */
static int32_t PIOS_ICM20602_Test(void)
{
    int32_t id = PIOS_ICM20602_ReadID();

    if (id < 0) {
        return -1;
    }
    /* Accept the whole MPU/ICM family this driver actually drives, not just
     * the ICM-20602 it is named after. LiteWing's part answers 0x68, and
     * PIOS_Board_Init() has always accepted 0x68/0x70/0x12 -- keep the two
     * lists saying the same thing.
     *
     * Nothing called this until modules/Sensors replaced modules/Attitude.
     * When it did, the mismatch did not present as "IMU test failed": a
     * failing sensor makes SensorsTask park in a `while (1) vTaskDelay(10)`
     * that never reloads its watchdog flag, so the board became a silent
     * watchdog reboot loop with both cores idle and no mention of the IMU. */
    return (id == PIOS_ICM20602_WHOAMI_ID
            || id == PIOS_MPU6000_WHOAMI_ID
            || id == PIOS_MPU6500_WHOAMI_ID) ? 0 : -2;
}

/**
 * @brief EXTI IRQ Handler.  Read all the data from onboard buffer
 * @return a boleoan to the EXTI IRQ Handler wrapper indicating if a
 *         higher priority task is now eligible to run
 */

bool PIOS_ICM20602_IRQHandler(void)
{
    bool woken = false;

    if (!icm20602_configured) {
        return false;
    }

    bool read_ok = false;
    read_ok = PIOS_ICM20602_ReadSensor(&woken);

    if (read_ok) {
        bool woken2 = PIOS_ICM20602_HandleData();
        woken |= woken2;
    }

    return woken;
}

static bool PIOS_ICM20602_HandleData()
{
    if (!queue_data) {
        return false;
    }

    // Rotate the sensor to OP convention.  The datasheet defines X as towards the right
    // and Y as forward.  OP convention transposes this.  Also the Z is defined negatively
    // to our convention

    // Currently we only support rotations on top so switch X/Y accordingly
    switch (dev->cfg->orientation) {
    case PIOS_ICM20602_TOP_0DEG:
        queue_data->sample[0].y = GET_SENSOR_DATA(icm20602_data, Accel_X); // chip X
        queue_data->sample[0].x = GET_SENSOR_DATA(icm20602_data, Accel_Y); // chip Y
        queue_data->sample[1].y = GET_SENSOR_DATA(icm20602_data, Gyro_X); // chip X
        queue_data->sample[1].x = GET_SENSOR_DATA(icm20602_data, Gyro_Y); // chip Y
        break;
    case PIOS_ICM20602_TOP_90DEG:
        // -1 to bring it back to -32768 +32767 range
        queue_data->sample[0].y = -1 - (GET_SENSOR_DATA(icm20602_data, Accel_Y)); // chip Y
        queue_data->sample[0].x = GET_SENSOR_DATA(icm20602_data, Accel_X); // chip X
        queue_data->sample[1].y = -1 - (GET_SENSOR_DATA(icm20602_data, Gyro_Y)); // chip Y
        queue_data->sample[1].x = GET_SENSOR_DATA(icm20602_data, Gyro_X); // chip X
        break;
    case PIOS_ICM20602_TOP_180DEG:
        queue_data->sample[0].y = -1 - (GET_SENSOR_DATA(icm20602_data, Accel_X)); // chip X
        queue_data->sample[0].x = -1 - (GET_SENSOR_DATA(icm20602_data, Accel_Y)); // chip Y
        queue_data->sample[1].y = -1 - (GET_SENSOR_DATA(icm20602_data, Gyro_X)); // chip X
        queue_data->sample[1].x = -1 - (GET_SENSOR_DATA(icm20602_data, Gyro_Y)); // chip Y
        break;
    case PIOS_ICM20602_TOP_270DEG:
        queue_data->sample[0].y = GET_SENSOR_DATA(icm20602_data, Accel_Y); // chip Y
        queue_data->sample[0].x = -1 - (GET_SENSOR_DATA(icm20602_data, Accel_X)); // chip X
        queue_data->sample[1].y = GET_SENSOR_DATA(icm20602_data, Gyro_Y); // chip Y
        queue_data->sample[1].x = -1 - (GET_SENSOR_DATA(icm20602_data, Gyro_X)); // chip X
        break;
    }
    queue_data->sample[0].z = -1 - (GET_SENSOR_DATA(icm20602_data, Accel_Z));
    queue_data->sample[1].z = -1 - (GET_SENSOR_DATA(icm20602_data, Gyro_Z));
    const int16_t temp = GET_SENSOR_DATA(icm20602_data, Temperature);
    /*
     * Temperature in centidegrees C. The slope and offset are PART-SPECIFIC,
     * and this driver now serves three of them:
     *
     *   ICM-20602 (0x12)  degC = raw/326.8  + 25.00
     *   MPU6500   (0x70)  degC = raw/333.87 + 21.00
     *   MPU6000   (0x68)  degC = raw/340    + 36.53
     *   MPU6050   (0x68)  ditto
     *
     * Using one formula for all of them is wrong by up to 11.5 degC in offset
     * and 4% in slope. It LOOKS harmless because every temp coefficient
     * defaults to zero so nothing reads this. It stops being harmless the
     * moment someone runs a temperature calibration: attitude.c fits
     * gyro_temp_bias against this value and stores temp_calibrated_extent in
     * the same units, so the whole fit would be anchored to a wrong axis,
     * silently. Pick by WHO_AM_I rather than by transport -- the bus a part
     * sits on says nothing about which part it is.
     */
    switch (icm_whoami) {
    case 0x68:  /* MPU6000 / MPU6050 */
        queue_data->temperature = 3653 + (float)temp * (100.0f / 340.0f);
        break;
    case 0x70:  /* MPU6500 */
        queue_data->temperature = 2100 + (float)temp * (100.0f / 333.87f);
        break;
    default:    /* 0x12 ICM-20602 */
        queue_data->temperature = 2500 + (float)temp * (100.0f / 326.8f);
        break;
    }

    BaseType_t higherPriorityTaskWoken;
    /* Producer-side gap tracking. modules/Sensors waits exactly one sensor
     * period for a sample and calls anything longer a sensor failure, so the
     * question "is the producer late, or is the consumer late?" decides where
     * that fault actually lives. Record the worst gap between pushes. */
    {
        extern uint32_t pios_icm20602_push_gap_max_us;
        extern uint32_t pios_icm20602_push_gaps_over_4ms;
        extern uint32_t pios_icm20602_pushes;
        static uint32_t last_push_us;
        uint32_t now_us = (uint32_t)esp_timer_get_time();
        if (last_push_us) {
            uint32_t gap = now_us - last_push_us;
            if (gap > pios_icm20602_push_gap_max_us) {
                pios_icm20602_push_gap_max_us = gap;
            }
            if (gap > 4000) {
                pios_icm20602_push_gaps_over_4ms++;
            }
        }
        last_push_us = now_us;
        pios_icm20602_pushes++;
    }
    xQueueSendToBackFromISR(dev->queue, (void *)queue_data, &higherPriorityTaskWoken);
    return higherPriorityTaskWoken == pdTRUE;
}

static bool PIOS_ICM20602_ReadSensor(bool *woken)
{
    const uint8_t icm20602_send_buf[1 + PIOS_ICM20602_SAMPLES_BYTES] = { PIOS_ICM20602_SENSOR_FIRST_REG | 0x80 };

    if (icm_use_i2c) {
        /* SPI leaves buffer[0] as the address-echo dummy and the samples land
         * at [1..]; I2C has no such byte, so read straight into [1] to keep
         * GET_SENSOR_DATA's offsets identical for both transports. */
        return PIOS_ICM20602_I2C_Read(PIOS_ICM20602_SENSOR_FIRST_REG,
                                      &icm20602_data.buffer[1],
                                      PIOS_ICM20602_SAMPLES_BYTES) == 0;
    }
    if (PIOS_ICM20602_ClaimBusISR(woken, true) != 0) {
        return false;
    }
    if (PIOS_SPI_TransferBlock(dev->spi_id, &icm20602_send_buf[0], &icm20602_data.buffer[0], sizeof(icm20602_data_t), NULL) < 0) {
        PIOS_ICM20602_ReleaseBusISR(woken);
        return false;
    }
    PIOS_ICM20602_ReleaseBusISR(woken);
    return true;
}

// Sensor driver implementation
bool PIOS_ICM20602_driver_Test(__attribute__((unused)) uintptr_t context)
{
    return !PIOS_ICM20602_Test();
}

/* Counts how often modules/Sensors found the queue empty at its deadline and
 * declared a primary-sensor miss. Each one raises SYSTEMALARMS_ALARM_SENSORS
 * Critical, which armhandler.c treats as arm-blocking. Read by the board's
 * CPU report. */
uint32_t pios_icm20602_driver_resets;
uint32_t pios_icm20602_push_gap_max_us;
uint32_t pios_icm20602_push_gaps_over_4ms;
uint32_t pios_icm20602_pushes;

void PIOS_ICM20602_driver_Reset(__attribute__((unused)) uintptr_t context)
{
    pios_icm20602_driver_resets++;
    PIOS_ICM20602_DummyReadGyros();
}

void PIOS_ICM20602_driver_get_scale(float *scales, uint8_t size, __attribute__((unused)) uintptr_t contet)
{
    PIOS_Assert(size >= 2);
    scales[0] = PIOS_ICM20602_GetAccelScale();
    scales[1] = PIOS_ICM20602_GetScale();
}

QueueHandle_t PIOS_ICM20602_driver_get_queue(__attribute__((unused)) uintptr_t context)
{
    return dev->queue;
}
#endif /* PIOS_INCLUDE_ICM20602 */

/**
 * @}
 * @}
 */
