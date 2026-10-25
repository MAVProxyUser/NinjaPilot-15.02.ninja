/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_INVENSENSE Invensense MPU9250 / ICM2060x gyro+accel (+ AK8963 compass)
 * @brief SPI driver for the newer Invensense parts, registered with the
 *        sensor subsystem as a gyro/accel queue and an optional polled
 *        magnetometer (the AK8963 behind the MPU9250's I2C master).
 * @{
 *
 * @file       pios_invensense.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2026.
 * @brief      Invensense MPU9250 / ICM2060x driver header
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

#ifndef PIOS_INVENSENSE_H
#define PIOS_INVENSENSE_H

#include <pios_stm32.h>
#include <pios_spi.h>
#include <pios_sensors.h>

/* Registers shared by the MPU9250 and the ICM2060x family */
#define PIOS_INVENSENSE_SMPLRT_DIV_REG      0x19
#define PIOS_INVENSENSE_CONFIG_REG          0x1A  /* gyro DLPF */
#define PIOS_INVENSENSE_GYRO_CFG_REG        0x1B
#define PIOS_INVENSENSE_ACCEL_CFG_REG       0x1C
#define PIOS_INVENSENSE_ACCEL_CFG2_REG      0x1D  /* accel DLPF */
#define PIOS_INVENSENSE_INT_CFG_REG         0x37
#define PIOS_INVENSENSE_INT_EN_REG          0x38
#define PIOS_INVENSENSE_INT_STATUS_REG      0x3A
#define PIOS_INVENSENSE_ACCEL_X_OUT_MSB     0x3B  /* start of the burst */
#define PIOS_INVENSENSE_TEMP_OUT_MSB        0x41
#define PIOS_INVENSENSE_GYRO_X_OUT_MSB      0x43
#define PIOS_INVENSENSE_USER_CTRL_REG       0x6A
#define PIOS_INVENSENSE_PWR_MGMT_REG        0x6B
#define PIOS_INVENSENSE_PWR_MGMT2_REG       0x6C
#define PIOS_INVENSENSE_WHOAMI              0x75

#define PIOS_INVENSENSE_SPI_READ_FLAG       0x80

#define PIOS_INVENSENSE_WHOAMI_MPU9250      0x71
#define PIOS_INVENSENSE_WHOAMI_MPU9255      0x73
#define PIOS_INVENSENSE_WHOAMI_ICM20608     0xAF
#define PIOS_INVENSENSE_WHOAMI_ICM20602     0x12

/* INT_PIN_CFG */
#define PIOS_INVENSENSE_INT_ACTL            0x80
#define PIOS_INVENSENSE_INT_OPEN            0x40
#define PIOS_INVENSENSE_INT_LATCH_EN        0x20
#define PIOS_INVENSENSE_INT_CLR_ANYRD       0x10
/* INT_ENABLE */
#define PIOS_INVENSENSE_INTEN_DATA_RDY      0x01
#define PIOS_INVENSENSE_INT_STATUS_DATA_RDY 0x01
/* USER_CTRL */
#define PIOS_INVENSENSE_USERCTL_FIFO_EN     0x40
#define PIOS_INVENSENSE_USERCTL_I2C_MST_EN  0x20
#define PIOS_INVENSENSE_USERCTL_DIS_I2C     0x10  /* SPI-only mode; set this */
#define PIOS_INVENSENSE_USERCTL_FIFO_RST    0x04
#define PIOS_INVENSENSE_USERCTL_SIG_COND    0x01
/* PWR_MGMT_1 */
#define PIOS_INVENSENSE_PWRMGMT_IMU_RST     0x80
#define PIOS_INVENSENSE_PWRMGMT_SLEEP       0x40
#define PIOS_INVENSENSE_PWRMGMT_INTERN_CLK  0x00
#define PIOS_INVENSENSE_PWRMGMT_PLL_BEST    0x01  /* auto-select best clock */

enum pios_invensense_type {
    PIOS_INVENSENSE_ANY = 0, /* accept any recognised part */
    PIOS_INVENSENSE_MPU9250,
    PIOS_INVENSENSE_ICM20608,
};

enum pios_invensense_gyro_range {
    PIOS_INVENSENSE_SCALE_250_DEG  = 0x00,
    PIOS_INVENSENSE_SCALE_500_DEG  = 0x08,
    PIOS_INVENSENSE_SCALE_1000_DEG = 0x10,
    PIOS_INVENSENSE_SCALE_2000_DEG = 0x18,
};

enum pios_invensense_accel_range {
    PIOS_INVENSENSE_ACCEL_2G  = 0x00,
    PIOS_INVENSENSE_ACCEL_4G  = 0x08,
    PIOS_INVENSENSE_ACCEL_8G  = 0x10,
    PIOS_INVENSENSE_ACCEL_16G = 0x18,
};

enum pios_invensense_filter {
    PIOS_INVENSENSE_LOWPASS_250_HZ = 0x00,
    PIOS_INVENSENSE_LOWPASS_184_HZ = 0x01,
    PIOS_INVENSENSE_LOWPASS_92_HZ  = 0x02,
    PIOS_INVENSENSE_LOWPASS_41_HZ  = 0x03,
    PIOS_INVENSENSE_LOWPASS_20_HZ  = 0x04,
    PIOS_INVENSENSE_LOWPASS_10_HZ  = 0x05,
    PIOS_INVENSENSE_LOWPASS_5_HZ   = 0x06,
};

/* Same meaning as the MPU6000 driver's orientations: how the package sits on
 * the board, TOP_0DEG being the Revolution's mounting. */
enum pios_invensense_orientation {
    PIOS_INVENSENSE_TOP_0DEG      = 0x00,
    PIOS_INVENSENSE_TOP_90DEG     = 0x01,
    PIOS_INVENSENSE_TOP_180DEG    = 0x02,
    PIOS_INVENSENSE_TOP_270DEG    = 0x03,
    PIOS_INVENSENSE_BOTTOM_0DEG   = 0x04,
    PIOS_INVENSENSE_BOTTOM_90DEG  = 0x05,
    PIOS_INVENSENSE_BOTTOM_180DEG = 0x06,
    PIOS_INVENSENSE_BOTTOM_270DEG = 0x07,
};

struct pios_invensense_cfg {
    const struct pios_exti_cfg *exti_cfg; /* data-ready line */

    enum pios_invensense_type type; /* expected part, or ANY */

    uint8_t smpl_rate_div; /* SMPLRT_DIV */
    uint8_t int_cfg; /* INT_PIN_CFG */
    uint8_t int_en; /* INT_ENABLE */
    uint8_t user_ctl; /* USER_CTRL */
    uint8_t pwr_mgmt_clk; /* PWR_MGMT_1 clock select */
    /* MPU9250 only: bring up the AK8963 behind the I2C master and read it
     * with every burst.  Off for the ICM parts. */
    bool    mag_ak8963;

    enum pios_invensense_accel_range accel_range;
    enum pios_invensense_gyro_range  gyro_range;
    enum pios_invensense_filter      filter;
    enum pios_invensense_orientation orientation;

    SPIPrescalerTypeDef slow_prescaler; /* register access, <= 1 MHz */
    SPIPrescalerTypeDef fast_prescaler; /* sensor bursts, <= 20 MHz */
};

typedef uintptr_t pios_invensense_t;

extern int32_t PIOS_INVENSENSE_Init(pios_invensense_t *handle, uint32_t spi_id,
                                    uint32_t slave_num, const struct pios_invensense_cfg *cfg);
/* Register the gyro/accel (queue) and, when it answered, the AK8963 (polled)
 * with the sensor subsystem. */
extern void PIOS_INVENSENSE_Register(pios_invensense_t handle);
extern int32_t PIOS_INVENSENSE_ReadID(pios_invensense_t handle);
extern int32_t PIOS_INVENSENSE_Test(pios_invensense_t handle);
extern float PIOS_INVENSENSE_GetGyroScale(pios_invensense_t handle);
extern float PIOS_INVENSENSE_GetAccelScale(pios_invensense_t handle);
extern bool PIOS_INVENSENSE_IRQHandler(pios_invensense_t handle);
/* Diagnostics */
extern void PIOS_INVENSENSE_GetStats(pios_invensense_t handle, uint32_t *irqs, uint32_t *bus_fails, uint32_t *queue_full);
extern void PIOS_INVENSENSE_GetMagStats(pios_invensense_t handle, uint32_t *samples, uint32_t *overflow, int32_t *init_rc);

extern const PIOS_SENSORS_Driver PIOS_INVENSENSE_Driver;
extern const PIOS_SENSORS_Driver PIOS_INVENSENSE_Mag_Driver;

#endif /* PIOS_INVENSENSE_H */

/**
 * @}
 * @}
 */
