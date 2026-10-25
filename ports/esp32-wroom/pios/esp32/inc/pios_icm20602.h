/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_ICM20602 ICM20602 Functions
 * @brief Deals with the hardware interface to the 3-axis gyro
 * @{
 *
 * @file       PIOS_ICM20602.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @brief      ICM20602 3-axis gyro function headers
 * @see        The GNU Public License (GPL) Version 3
 *
 ******************************************************************************
 */
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

#ifndef PIOS_ICM20602_H
#define PIOS_ICM20602_H
#include <pios_sensors.h>

/* ICM20602 Addresses */
#define PIOS_ICM20602_SMPLRT_DIV_REG           0X19
#define PIOS_ICM20602_DLPF_CFG_REG             0X1A
#define PIOS_ICM20602_GYRO_CFG_REG             0X1B
#define PIOS_ICM20602_ACCEL_CFG_REG            0x1C
/*
 * Accelerometer DLPF. This register does not exist on the MPU6000, which is
 * why the driver this came from never wrote it and left the accel filtered
 * differently from the gyro. A_DLPF_CFG bits [2:0]:
 *   0,1 -> 218.1Hz    2 -> 99Hz   3 -> 44.8Hz   4 -> 21.2Hz
 *     5 ->  10.2Hz    6 ->  5.1Hz  7 -> 420Hz
 */
#define PIOS_ICM20602_ACCEL_CFG2_REG           0x1D
#define PIOS_ICM20602_FIFO_EN_REG              0x23
#define PIOS_ICM20602_INT_CFG_REG              0x37
#define PIOS_ICM20602_INT_EN_REG               0x38
#define PIOS_ICM20602_INT_STATUS_REG           0x3A
#define PIOS_ICM20602_ACCEL_X_OUT_MSB          0x3B
#define PIOS_ICM20602_ACCEL_X_OUT_LSB          0x3C
#define PIOS_ICM20602_ACCEL_Y_OUT_MSB          0x3D
#define PIOS_ICM20602_ACCEL_Y_OUT_LSB          0x3E
#define PIOS_ICM20602_ACCEL_Z_OUT_MSB          0x3F
#define PIOS_ICM20602_ACCEL_Z_OUT_LSB          0x40
#define PIOS_ICM20602_TEMP_OUT_MSB             0x41
#define PIOS_ICM20602_TEMP_OUT_LSB             0x42
#define PIOS_ICM20602_GYRO_X_OUT_MSB           0x43
#define PIOS_ICM20602_GYRO_X_OUT_LSB           0x44
#define PIOS_ICM20602_GYRO_Y_OUT_MSB           0x45
#define PIOS_ICM20602_GYRO_Y_OUT_LSB           0x46
#define PIOS_ICM20602_GYRO_Z_OUT_MSB           0x47
#define PIOS_ICM20602_GYRO_Z_OUT_LSB           0x48
#define PIOS_ICM20602_USER_CTRL_REG            0x6A
#define PIOS_ICM20602_PWR_MGMT_REG             0x6B
#define PIOS_ICM20602_FIFO_CNT_MSB             0x72
#define PIOS_ICM20602_FIFO_CNT_LSB             0x73
#define PIOS_ICM20602_FIFO_REG                 0x74
#define PIOS_ICM20602_WHOAMI                   0x75
/* The only value this driver accepts. MPU6000 answers 0x68, MPU6500 0x70. */
#define PIOS_ICM20602_WHOAMI_ID                0x12
/* Same driver, other parts on the same register map. PIOS_Board_Init() and
 * PIOS_ICM20602_Test() both accept all three. */
#define PIOS_MPU6000_WHOAMI_ID                 0x68
#define PIOS_MPU6500_WHOAMI_ID                 0x70

/* FIFO enable for storing different values */
#define PIOS_ICM20602_FIFO_TEMP_OUT            0x80
#define PIOS_ICM20602_FIFO_GYRO_X_OUT          0x40
#define PIOS_ICM20602_FIFO_GYRO_Y_OUT          0x20
#define PIOS_ICM20602_FIFO_GYRO_Z_OUT          0x10
#define PIOS_ICM20602_ACCEL_OUT                0x08

/* Interrupt Configuration */
#define PIOS_ICM20602_INT_ACTL                 0x80
#define PIOS_ICM20602_INT_OPEN                 0x40
#define PIOS_ICM20602_INT_LATCH_EN             0x20
#define PIOS_ICM20602_INT_CLR_ANYRD            0x10

#define PIOS_ICM20602_INTEN_OVERFLOW           0x10
#define PIOS_ICM20602_INTEN_DATA_RDY           0x01

/* Interrupt status */
#define PIOS_ICM20602_INT_STATUS_FIFO_FULL     0x80
#define PIOS_ICM20602_INT_STATUS_FIFO_OVERFLOW 0x10
#define PIOS_ICM20602_INT_STATUS_IMU_RDY       0X04
#define PIOS_ICM20602_INT_STATUS_DATA_RDY      0X01

/* User control functionality */
#define PIOS_ICM20602_USERCTL_FIFO_EN          0X40
#define PIOS_ICM20602_USERCTL_I2C_MST_EN       0x20
#define PIOS_ICM20602_USERCTL_DIS_I2C          0X10
#define PIOS_ICM20602_USERCTL_FIFO_RST         0X04
#define PIOS_ICM20602_USERCTL_SIG_COND         0X02
#define PIOS_ICM20602_USERCTL_GYRO_RST         0X01

/* Power management and clock selection */
#define PIOS_ICM20602_PWRMGMT_IMU_RST          0X80
#define PIOS_ICM20602_PWRMGMT_INTERN_CLK       0X00
#define PIOS_ICM20602_PWRMGMT_PLL_X_CLK        0X01
#define PIOS_ICM20602_PWRMGMT_PLL_Y_CLK        0X02
#define PIOS_ICM20602_PWRMGMT_PLL_Z_CLK        0X03
#define PIOS_ICM20602_PWRMGMT_STOP_CLK         0X07

enum pios_icm20602_range {
    PIOS_ICM20602_SCALE_250_DEG  = 0x00,
    PIOS_ICM20602_SCALE_500_DEG  = 0x08,
    PIOS_ICM20602_SCALE_1000_DEG = 0x10,
    PIOS_ICM20602_SCALE_2000_DEG = 0x18
};

/*
 * Gyro DLPF, CONFIG register (0x1A) bits [2:0] = DLPF_CFG.
 *
 * Named by REGISTER ENCODING, not by bandwidth, deliberately. The MPU6000
 * driver this was derived from called 0x01 "188Hz" because that is the
 * MPU6000 figure; on the ICM-20602 the same encoding is 176Hz. Naming the
 * constants after a bandwidth that belongs to a different part is how the
 * two got confused in the first place. The bandwidth is documentation here;
 * the encoding is the contract.
 *
 * Note DLPF_CFG 0 and 7 BOTH bypass the filter and put the gyro output at
 * 8kHz rather than 1kHz, which also changes whether SMPLRT_DIV does
 * anything -- see PIOS_ICM20602_ConfigureRanges(). Selecting 0 by accident
 * is what produced an 8000/s interrupt storm on this board during bring-up.
 */
enum pios_icm20602_filter {
    PIOS_ICM20602_DLPF_BYPASS_250HZ = 0x00, /* 250Hz BW, 8kHz gyro ODR  */
    PIOS_ICM20602_DLPF_176HZ        = 0x01, /* 176Hz BW, 1kHz gyro ODR  */
    PIOS_ICM20602_DLPF_92HZ         = 0x02, /*  92Hz BW, 1kHz gyro ODR  */
    PIOS_ICM20602_DLPF_41HZ         = 0x03, /*  41Hz BW, 1kHz gyro ODR  */
    PIOS_ICM20602_DLPF_20HZ         = 0x04, /*  20Hz BW, 1kHz gyro ODR  */
    PIOS_ICM20602_DLPF_10HZ         = 0x05, /*  10Hz BW, 1kHz gyro ODR  */
    PIOS_ICM20602_DLPF_5HZ          = 0x06  /*   5Hz BW, 1kHz gyro ODR  */
};

enum pios_icm20602_accel_range {
    PIOS_ICM20602_ACCEL_2G  = 0x00,
    PIOS_ICM20602_ACCEL_4G  = 0x08,
    PIOS_ICM20602_ACCEL_8G  = 0x10,
    PIOS_ICM20602_ACCEL_16G = 0x18
};

enum pios_icm20602_orientation { // clockwise rotation from board forward
    PIOS_ICM20602_TOP_0DEG   = 0x00,
    PIOS_ICM20602_TOP_90DEG  = 0x01,
    PIOS_ICM20602_TOP_180DEG = 0x02,
    PIOS_ICM20602_TOP_270DEG = 0x03
};

struct pios_icm20602_cfg {
    const struct pios_exti_cfg *exti_cfg; /* Pointer to the EXTI configuration */

    uint8_t Fifo_store; /* FIFO storage of different readings (See datasheet page 31 for more details) */

    /* Sample rate divider to use (See datasheet page 32 for more details).*/
    uint8_t Smpl_rate_div_no_dlp; /* used when no dlp is applied (fs=8KHz)*/
    uint8_t Smpl_rate_div_dlp; /* used when dlp is on (fs=1kHz)*/
    uint8_t interrupt_cfg; /* Interrupt configuration (See datasheet page 35 for more details) */
    uint8_t interrupt_en; /* Interrupt configuration (See datasheet page 35 for more details) */
    uint8_t User_ctl; /* User control settings (See datasheet page 41 for more details)  */
    uint8_t Pwr_mgmt_clk; /* Power management and clock selection (See datasheet page 32 for more details) */
    enum pios_icm20602_accel_range accel_range;
    enum pios_icm20602_range gyro_range;
    enum pios_icm20602_filter filter;
    enum pios_icm20602_orientation orientation;
    SPIPrescalerTypeDef fast_prescaler;
    SPIPrescalerTypeDef std_prescaler;
    uint8_t max_downsample;
};

/* Public Functions */
/* MPU6050 on LiteWing sits on I2C0; same register map, different bus. */
extern int32_t PIOS_ICM20602_InitI2C(uint32_t i2c_id, uint8_t i2c_addr, const struct pios_icm20602_cfg *cfg);
extern int32_t PIOS_ICM20602_Init(uint32_t spi_id, uint32_t slave_num, const struct pios_icm20602_cfg *new_cfg);
extern int32_t PIOS_ICM20602_ConfigureRanges(enum pios_icm20602_range gyroRange, enum pios_icm20602_accel_range accelRange, enum pios_icm20602_filter filterSetting);
extern int32_t PIOS_ICM20602_ReadID();
extern void PIOS_ICM20602_Register();
extern bool PIOS_ICM20602_IRQHandler(void);

extern const PIOS_SENSORS_Driver PIOS_ICM20602_Driver;
#endif /* PIOS_ICM20602_H */

/**
 * @}
 * @}
 */
