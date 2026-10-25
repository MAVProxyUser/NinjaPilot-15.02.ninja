/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_INVENSENSE Invensense 6/9-axis IMU driver
 * @brief Driver for the Invensense parts fitted to the PixRacer: an MPU9250
 *        and an ICM-20608-G, both on SPI1.
 * @{
 *
 * @file       pios_invensense.h
 * @brief      Invensense MPU9250 / ICM-20608-G functions header
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

/*
 * Why one driver for two parts:
 *
 * The MPU9250 and the ICM-20608-G share the Invensense register map for
 * everything this driver touches - sample rate, DLPF, ranges, interrupt
 * config, and the 14-byte accel/temp/gyro burst at 0x3B.  They differ only in
 * WHO_AM_I and in how fast the SPI bus may be driven.  Keeping them in one
 * driver means the second IMU costs a config struct rather than a second copy
 * of the same code.
 *
 * Unlike PiOS's older single-instance drivers this one is handle-based,
 * because the PixRacer genuinely has two of these chips on the same bus.
 */

/* Register map (identical on both parts for everything used here) */
#define PIOS_INVENSENSE_SMPLRT_DIV_REG      0x19
#define PIOS_INVENSENSE_CONFIG_REG          0x1A	/* gyro DLPF */
#define PIOS_INVENSENSE_GYRO_CFG_REG        0x1B
#define PIOS_INVENSENSE_ACCEL_CFG_REG       0x1C
#define PIOS_INVENSENSE_ACCEL_CFG2_REG      0x1D	/* accel DLPF */
#define PIOS_INVENSENSE_INT_CFG_REG         0x37
#define PIOS_INVENSENSE_INT_EN_REG          0x38
#define PIOS_INVENSENSE_INT_STATUS_REG      0x3A
#define PIOS_INVENSENSE_ACCEL_X_OUT_MSB     0x3B	/* start of the 14-byte burst */
#define PIOS_INVENSENSE_TEMP_OUT_MSB        0x41
#define PIOS_INVENSENSE_GYRO_X_OUT_MSB      0x43
#define PIOS_INVENSENSE_USER_CTRL_REG       0x6A
#define PIOS_INVENSENSE_PWR_MGMT_REG        0x6B
#define PIOS_INVENSENSE_PWR_MGMT2_REG       0x6C
#define PIOS_INVENSENSE_WHOAMI              0x75

/* SPI framing */
#define PIOS_INVENSENSE_SPI_READ_FLAG       0x80

/* WHO_AM_I values */
#define PIOS_INVENSENSE_WHOAMI_MPU9250      0x71
#define PIOS_INVENSENSE_WHOAMI_MPU9255      0x73
#define PIOS_INVENSENSE_WHOAMI_ICM20608     0xAF
#define PIOS_INVENSENSE_WHOAMI_ICM20602     0x12

/* Interrupt pin configuration */
#define PIOS_INVENSENSE_INT_ACTL            0x80
#define PIOS_INVENSENSE_INT_OPEN            0x40
#define PIOS_INVENSENSE_INT_LATCH_EN        0x20
#define PIOS_INVENSENSE_INT_CLR_ANYRD       0x10

#define PIOS_INVENSENSE_INTEN_DATA_RDY      0x01

#define PIOS_INVENSENSE_INT_STATUS_DATA_RDY 0x01

/* User control */
#define PIOS_INVENSENSE_USERCTL_FIFO_EN     0x40
#define PIOS_INVENSENSE_USERCTL_I2C_MST_EN  0x20
#define PIOS_INVENSENSE_USERCTL_DIS_I2C     0x10	/* SPI-only mode; set this */
#define PIOS_INVENSENSE_USERCTL_FIFO_RST    0x04
#define PIOS_INVENSENSE_USERCTL_SIG_COND    0x01

/* Power management */
#define PIOS_INVENSENSE_PWRMGMT_IMU_RST     0x80
#define PIOS_INVENSENSE_PWRMGMT_SLEEP       0x40
#define PIOS_INVENSENSE_PWRMGMT_INTERN_CLK  0x00
#define PIOS_INVENSENSE_PWRMGMT_PLL_BEST    0x01	/* auto-select best clock */

enum pios_invensense_type {
	PIOS_INVENSENSE_ANY = 0,	/* accept any recognised part */
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

/* Gyro DLPF, CONFIG register.  With DLPF_CFG != 0 the gyro output rate is
 * 1 kHz; with 0 or 7 it is 8 kHz. */
enum pios_invensense_filter {
	PIOS_INVENSENSE_LOWPASS_250_HZ = 0x00,
	PIOS_INVENSENSE_LOWPASS_184_HZ = 0x01,
	PIOS_INVENSENSE_LOWPASS_92_HZ  = 0x02,
	PIOS_INVENSENSE_LOWPASS_41_HZ  = 0x03,
	PIOS_INVENSENSE_LOWPASS_20_HZ  = 0x04,
	PIOS_INVENSENSE_LOWPASS_10_HZ  = 0x05,
	PIOS_INVENSENSE_LOWPASS_5_HZ   = 0x06,
};

/*
 * Clockwise rotation of the chip relative to board forward.
 *
 * PixRacer note: ArduPilot describes both of this board's IMUs as
 * ROTATION_ROLL_180_YAW_90, which maps (x,y,z)chip -> (y,x,-z)body.  OpenPilot's
 * own convention already transposes X/Y and negates Z relative to the
 * Invensense datasheet frame, so those two cancel out exactly and the correct
 * setting here is TOP_0DEG.  See pios_board.c.
 */
enum pios_invensense_orientation {
	PIOS_INVENSENSE_TOP_0DEG   = 0x00,
	PIOS_INVENSENSE_TOP_90DEG  = 0x01,
	PIOS_INVENSENSE_TOP_180DEG = 0x02,
	PIOS_INVENSENSE_TOP_270DEG = 0x03,
	/* Chip mounted upside down (its Z axis points along body Z, i.e. down).
	 * BOTTOM_n is TOP_n rolled 180 degrees about the body X axis: body Y and
	 * body Z change sign.  The Cube's non-isolated IMU is BOTTOM_0DEG. */
	PIOS_INVENSENSE_BOTTOM_0DEG   = 0x04,
	PIOS_INVENSENSE_BOTTOM_90DEG  = 0x05,
	PIOS_INVENSENSE_BOTTOM_180DEG = 0x06,
	PIOS_INVENSENSE_BOTTOM_270DEG = 0x07,
};

/* One sample, already rotated into OpenPilot body axes */
struct pios_invensense_data {
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	int16_t temperature;
	/* AK8963 field in the same body frame as the accel/gyro (raw LSB, 16-bit
	 * mode, before the factory sensitivity adjustment); mag_valid is set
	 * when the part flagged fresh, non-overflowed data. */
	int16_t mag_x;
	int16_t mag_y;
	int16_t mag_z;
	uint8_t mag_valid;
	/* Set by the interrupt handler when it could not read the part (SPI bus
	 * held by another driver): the fields above are empty and the consumer
	 * must fetch the sample with PIOS_INVENSENSE_ReadSensors() instead. */
	uint8_t deferred;
};

struct pios_invensense_cfg {
	const struct pios_exti_cfg *exti_cfg;	/* data-ready line */

	enum pios_invensense_type type;		/* expected part, or ANY */

	uint8_t smpl_rate_div;			/* SMPLRT_DIV */
	uint8_t int_cfg;			/* INT_PIN_CFG */
	uint8_t int_en;				/* INT_ENABLE */
	uint8_t user_ctl;			/* USER_CTRL */
	/* MPU9250 only: bring up the AK8963 behind the I2C master and read it
	 * with every burst (EXT_SENS_DATA).  Off for the MPU6000/ICM parts. */
	bool mag_ak8963;
	uint8_t pwr_mgmt_clk;			/* PWR_MGMT_1 clock select */

	enum pios_invensense_accel_range accel_range;
	enum pios_invensense_gyro_range gyro_range;
	enum pios_invensense_filter filter;
	enum pios_invensense_orientation orientation;

	/*
	 * These parts allow only ~1 MHz for configuration register access but
	 * up to 20 MHz for reading the sensor and interrupt registers, so the
	 * driver changes bus speed depending on what it is doing.  Both buses
	 * are shared with other chips, so the speed is re-applied on every
	 * claim rather than set once.
	 */
	SPIPrescalerTypeDef slow_prescaler;
	SPIPrescalerTypeDef fast_prescaler;
};

/* Opaque per-chip handle */
typedef uintptr_t pios_invensense_t;

extern int32_t PIOS_INVENSENSE_Init(pios_invensense_t *handle, uint32_t spi_id,
				    uint32_t slave_num, const struct pios_invensense_cfg *cfg);
extern xQueueHandle PIOS_INVENSENSE_GetQueue(pios_invensense_t handle);
extern int32_t PIOS_INVENSENSE_ReadID(pios_invensense_t handle);
extern int32_t PIOS_INVENSENSE_Test(pios_invensense_t handle);
extern int32_t PIOS_INVENSENSE_ReadSensors(pios_invensense_t handle, struct pios_invensense_data *data);
void PIOS_INVENSENSE_GetStats(pios_invensense_t handle, uint32_t *irqs, uint32_t *bus_fails, uint32_t *queue_full);
/* AK8963: 0 when it answered at init; asa[] is the factory sensitivity adjustment. */
int32_t PIOS_INVENSENSE_GetMagAdjust(pios_invensense_t handle, float asa[3]);
void PIOS_INVENSENSE_GetMagStats(pios_invensense_t handle, uint32_t *samples, uint32_t *overflow, int32_t *init_rc);
extern float PIOS_INVENSENSE_GetGyroScale(pios_invensense_t handle);
extern float PIOS_INVENSENSE_GetAccelScale(pios_invensense_t handle);
extern float PIOS_INVENSENSE_GetTemperature(pios_invensense_t handle, int16_t raw);
extern bool PIOS_INVENSENSE_IRQHandler(pios_invensense_t handle);

#endif /* PIOS_INVENSENSE_H */

/**
  * @}
  * @}
  */
