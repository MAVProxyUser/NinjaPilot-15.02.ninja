/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_INVENSENSE Invensense 6/9-axis IMU driver
 * @{
 *
 * @file       pios_invensense.c
 * @brief      Driver for the MPU9250 and ICM-20608-G on the PixRacer's SPI1.
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

/* This tree has no shared physical-constants header; pios_mpu6000.c defines
 * the same constant locally. */
#define GRAV	9.81f

/* Depth of the sample queue handed to the Sensors module */
#define PIOS_INVENSENSE_QUEUE_LEN	2

/* Bytes in the ACCEL_XOUT_H..GYRO_ZOUT_L burst: 6 accel, 2 temp, 6 gyro */
/* ACCEL(6) TEMP(2) GYRO(6) EXT_SENS_DATA_00..07(8): the AK8963's ST1, HXL..HZH,
 * ST2 land in the external sensor registers right after the gyro. */
#define PIOS_INVENSENSE_BURST_LEN	22
#define PIOS_INVENSENSE_MAG_OFFSET	14

/* I2C master and slave registers (MPU9250) */
#define REG_I2C_MST_CTRL	0x24
#define REG_I2C_SLV0_ADDR	0x25
#define REG_I2C_SLV0_REG	0x26
#define REG_I2C_SLV0_CTRL	0x27
#define REG_I2C_SLV4_ADDR	0x31
#define REG_I2C_SLV4_REG	0x32
#define REG_I2C_SLV4_DO		0x33
#define REG_I2C_SLV4_CTRL	0x34
#define REG_I2C_SLV4_DI		0x35
#define REG_I2C_MST_STATUS	0x36
#define REG_I2C_MST_DELAY_CTRL	0x67
#define I2C_MST_CLK_400KHZ	0x0D
#define I2C_SLV_EN		0x80
#define I2C_SLV4_DONE		0x40
#define I2C_SLV4_NACK		0x10
#define I2C_READ_FLAG		0x80

/* AK8963 magnetometer inside the MPU9250 */
#define AK8963_I2C_ADDR		0x0C
#define AK8963_REG_WIA		0x00
#define AK8963_REG_ST1		0x02
#define AK8963_REG_CNTL1	0x0A
#define AK8963_REG_CNTL2	0x0B
#define AK8963_REG_ASAX		0x10
#define AK8963_WHO_AM_I		0x48
#define AK8963_CNTL1_FUSE_16BIT	0x1F
#define AK8963_CNTL1_CONT2_16BIT 0x16	/* continuous, 100 Hz, 16-bit */
#define AK8963_CNTL1_POWERDOWN	0x00
#define AK8963_CNTL2_RESET	0x01
#define AK8963_ST1_DRDY		0x01
#define AK8963_ST2_HOFL		0x08
#define AK8963_READ_LEN		8	/* ST1, HXL..HZH, ST2 */

enum pios_invensense_dev_magic {
	PIOS_INVENSENSE_DEV_MAGIC = 0x9250a1f0,
};

struct invensense_dev {
	uint32_t spi_id;
	uint32_t slave_num;
	xQueueHandle queue;
	const struct pios_invensense_cfg *cfg;
	enum pios_invensense_gyro_range gyro_range;
	enum pios_invensense_accel_range accel_range;
	uint8_t whoami;
	bool configured;
	enum pios_invensense_dev_magic magic;

	/* diagnostics, useful over the debug console during bring-up */
	uint32_t irqs;
	uint32_t bus_fails;
	uint32_t queue_full;

	/* AK8963 behind the I2C master */
	bool has_mag;
	int32_t mag_init_rc;
	float mag_asa[3];
	uint32_t mag_samples;
	uint32_t mag_overflow;
	/* EXT_SENS_DATA keeps the last transfer until the next one (every 5th
	 * sample), so the same field shows up in five bursts: only a changed
	 * block counts as a new sample. */
	uint8_t last_mag[AK8963_READ_LEN];
};

static struct invensense_dev *PIOS_INVENSENSE_alloc(void);
static int32_t PIOS_INVENSENSE_Validate(struct invensense_dev *dev);
static int32_t PIOS_INVENSENSE_Config(struct invensense_dev *dev);
static int32_t PIOS_INVENSENSE_SetReg(struct invensense_dev *dev, uint8_t reg, uint8_t data);
static int32_t PIOS_INVENSENSE_GetReg(struct invensense_dev *dev, uint8_t reg);

static struct invensense_dev *PIOS_INVENSENSE_alloc(void)
{
	struct invensense_dev *dev;

	dev = (struct invensense_dev *)pvPortMalloc(sizeof(*dev));
	if (!dev) {
		return NULL;
	}

	memset(dev, 0, sizeof(*dev));
	dev->magic = PIOS_INVENSENSE_DEV_MAGIC;

	dev->queue = xQueueCreate(PIOS_INVENSENSE_QUEUE_LEN, sizeof(struct pios_invensense_data));
	if (dev->queue == NULL) {
		vPortFree(dev);
		return NULL;
	}

	return dev;
}

static int32_t PIOS_INVENSENSE_Validate(struct invensense_dev *dev)
{
	if (dev == NULL) {
		return -1;
	}
	if (dev->magic != PIOS_INVENSENSE_DEV_MAGIC) {
		return -2;
	}
	if (dev->spi_id == 0) {
		return -3;
	}
	return 0;
}

/**
 * @brief Claim the SPI bus, select this chip and set the bus speed.
 *
 * The speed has to be set on every claim, not once at init: SPI1 is shared
 * with the other IMU and the magnetometer, and they do not agree on a rate.
 * These parts also want two different rates themselves - roughly 1 MHz for
 * configuration registers but up to 20 MHz for the sensor registers - so the
 * caller says which it needs.
 */
static int32_t PIOS_INVENSENSE_ClaimBus(struct invensense_dev *dev, bool fast, bool from_isr, bool *woken)
{
	if (PIOS_INVENSENSE_Validate(dev) != 0) {
		return -1;
	}

	if (from_isr) {
		if (PIOS_SPI_ClaimBusISR(dev->spi_id, woken) != 0) {
			return -2;
		}
	} else {
		if (PIOS_SPI_ClaimBus(dev->spi_id) != 0) {
			return -2;
		}
	}

	PIOS_SPI_SetClockSpeed(dev->spi_id, fast ? dev->cfg->fast_prescaler
						: dev->cfg->slow_prescaler);
	PIOS_SPI_RC_PinSet(dev->spi_id, dev->slave_num, 0);
	return 0;
}

static int32_t PIOS_INVENSENSE_ReleaseBus(struct invensense_dev *dev, bool from_isr, bool *woken)
{
	if (PIOS_INVENSENSE_Validate(dev) != 0) {
		return -1;
	}

	PIOS_SPI_RC_PinSet(dev->spi_id, dev->slave_num, 1);

	if (from_isr) {
		return PIOS_SPI_ReleaseBusISR(dev->spi_id, woken);
	}
	return PIOS_SPI_ReleaseBus(dev->spi_id);
}

static int32_t PIOS_INVENSENSE_GetReg(struct invensense_dev *dev, uint8_t reg)
{
	uint8_t data;

	if (PIOS_INVENSENSE_ClaimBus(dev, false, false, NULL) != 0) {
		return -1;
	}

	PIOS_SPI_TransferByte(dev->spi_id, PIOS_INVENSENSE_SPI_READ_FLAG | reg);
	data = PIOS_SPI_TransferByte(dev->spi_id, 0);

	PIOS_INVENSENSE_ReleaseBus(dev, false, NULL);
	return data;
}

/*
 * NOTE on the transfers below: PIOS_SPI_TransferByte returns the byte the
 * device clocked out, not a status.  During the address byte an MPU9250 (unlike
 * the MPU6000 the original driver was written for) drives whatever it likes on
 * MISO, so "!= 0" was reporting every successful write as a failure and the
 * driver never got past the device reset.  Only a negative return is an error.
 */
static int32_t PIOS_INVENSENSE_SetReg(struct invensense_dev *dev, uint8_t reg, uint8_t data)
{
	if (PIOS_INVENSENSE_ClaimBus(dev, false, false, NULL) != 0) {
		return -1;
	}

	if (PIOS_SPI_TransferByte(dev->spi_id, reg & 0x7f) < 0) {
		PIOS_INVENSENSE_ReleaseBus(dev, false, NULL);
		return -2;
	}

	if (PIOS_SPI_TransferByte(dev->spi_id, data) < 0) {
		PIOS_INVENSENSE_ReleaseBus(dev, false, NULL);
		return -3;
	}

	PIOS_INVENSENSE_ReleaseBus(dev, false, NULL);
	return 0;
}

/**
 * @brief Verify the part is one we know, then bring it up.
 */
/* Bring-up: the last configuration step that failed, and the WHO_AM_I the
 * driver read, so a board can say why an init failed. */
volatile int32_t pios_invensense_dbg_rc;
volatile int32_t pios_invensense_dbg_id;

/*
 * One AK8963 register transaction through slave 4, which has a done flag.
 * The master runs slave transactions at the sample rate, so a few ms.
 */
static int32_t PIOS_INVENSENSE_MagXfer(struct invensense_dev *dev, uint8_t reg, uint8_t *val, bool read)
{
	if (PIOS_INVENSENSE_SetReg(dev, REG_I2C_SLV4_ADDR, AK8963_I2C_ADDR | (read ? I2C_READ_FLAG : 0)) != 0 ||
	    PIOS_INVENSENSE_SetReg(dev, REG_I2C_SLV4_REG, reg) != 0) {
		return -1;
	}
	if (!read && PIOS_INVENSENSE_SetReg(dev, REG_I2C_SLV4_DO, *val) != 0) {
		return -1;
	}
	if (PIOS_INVENSENSE_SetReg(dev, REG_I2C_SLV4_CTRL, I2C_SLV_EN) != 0) {
		return -1;
	}
	for (int i = 0; i < 25; i++) {
		PIOS_DELAY_WaitmS(1);
		int32_t st = PIOS_INVENSENSE_GetReg(dev, REG_I2C_MST_STATUS);
		if (st < 0) {
			return -2;
		}
		if (st & I2C_SLV4_NACK) {
			return -3;
		}
		if (st & I2C_SLV4_DONE) {
			if (read) {
				int32_t v = PIOS_INVENSENSE_GetReg(dev, REG_I2C_SLV4_DI);
				if (v < 0) {
					return -4;
				}
				*val = (uint8_t)v;
			}
			return 0;
		}
	}
	return -5;	/* timed out: no master activity */
}

static int32_t PIOS_INVENSENSE_MagWrite(struct invensense_dev *dev, uint8_t reg, uint8_t val)
{
	return PIOS_INVENSENSE_MagXfer(dev, reg, &val, false);
}

static int32_t PIOS_INVENSENSE_MagRead(struct invensense_dev *dev, uint8_t reg, uint8_t *val)
{
	return PIOS_INVENSENSE_MagXfer(dev, reg, val, true);
}

/* After Rotate(): drop the repeats of one slave-0 transfer and keep the counters. */
static void PIOS_INVENSENSE_MagBookkeeping(struct invensense_dev *dev, const uint8_t *raw, struct pios_invensense_data *data)
{
	if (!dev->has_mag) {
		return;
	}
	const uint8_t *m = &raw[PIOS_INVENSENSE_MAG_OFFSET];
	if (memcmp(m, dev->last_mag, AK8963_READ_LEN) == 0) {
		data->mag_valid = 0;
		return;
	}
	memcpy(dev->last_mag, m, AK8963_READ_LEN);
	if (data->mag_valid) {
		dev->mag_samples++;
	} else if (m[7] & AK8963_ST2_HOFL) {
		dev->mag_overflow++;
	}
}

/*
 * Bring up the AK8963 behind the MPU9250's I2C master: reset, identify,
 * read the factory sensitivity adjustment from the fuse ROM, put it in
 * 100 Hz 16-bit continuous mode, then let slave 0 copy ST1..ST2 into
 * EXT_SENS_DATA every fifth sample (500 Hz / 5 = the part's own rate).
 */
static int32_t PIOS_INVENSENSE_MagInit(struct invensense_dev *dev)
{
	uint8_t v;
	int32_t rc;

	if (PIOS_INVENSENSE_SetReg(dev, PIOS_INVENSENSE_USER_CTRL_REG, dev->cfg->user_ctl | PIOS_INVENSENSE_USERCTL_I2C_MST_EN) != 0 ||
	    PIOS_INVENSENSE_SetReg(dev, REG_I2C_MST_CTRL, I2C_MST_CLK_400KHZ) != 0) {
		return -10;
	}
	PIOS_DELAY_WaitmS(10);
	(void)PIOS_INVENSENSE_MagWrite(dev, AK8963_REG_CNTL2, AK8963_CNTL2_RESET);
	PIOS_DELAY_WaitmS(10);
	if ((rc = PIOS_INVENSENSE_MagRead(dev, AK8963_REG_WIA, &v)) != 0) {
		return -20 + rc;
	}
	if (v != AK8963_WHO_AM_I) {
		return -30;
	}
	if (PIOS_INVENSENSE_MagWrite(dev, AK8963_REG_CNTL1, AK8963_CNTL1_FUSE_16BIT) != 0) {
		return -40;
	}
	PIOS_DELAY_WaitmS(10);
	for (int i = 0; i < 3; i++) {
		if (PIOS_INVENSENSE_MagRead(dev, AK8963_REG_ASAX + i, &v) != 0) {
			return -50 - i;
		}
		dev->mag_asa[i] = ((float)v - 128.0f) / 256.0f + 1.0f;
	}
	if (PIOS_INVENSENSE_MagWrite(dev, AK8963_REG_CNTL1, AK8963_CNTL1_POWERDOWN) != 0) {
		return -60;
	}
	PIOS_DELAY_WaitmS(10);
	if (PIOS_INVENSENSE_MagWrite(dev, AK8963_REG_CNTL1, AK8963_CNTL1_CONT2_16BIT) != 0) {
		return -70;
	}
	PIOS_DELAY_WaitmS(10);
	/* slave 0: read 8 bytes from ST1 into EXT_SENS_DATA_00, every 5th sample */
	if (PIOS_INVENSENSE_SetReg(dev, REG_I2C_SLV4_CTRL, 4) != 0 ||			/* I2C_MST_DLY = 4 */
	    PIOS_INVENSENSE_SetReg(dev, REG_I2C_MST_DELAY_CTRL, 0x01) != 0 ||		/* slave 0 obeys the delay */
	    PIOS_INVENSENSE_SetReg(dev, REG_I2C_SLV0_ADDR, AK8963_I2C_ADDR | I2C_READ_FLAG) != 0 ||
	    PIOS_INVENSENSE_SetReg(dev, REG_I2C_SLV0_REG, AK8963_REG_ST1) != 0 ||
	    PIOS_INVENSENSE_SetReg(dev, REG_I2C_SLV0_CTRL, I2C_SLV_EN | AK8963_READ_LEN) != 0) {
		return -80;
	}
	dev->has_mag = true;
	return 0;
}

static int32_t PIOS_INVENSENSE_Config(struct invensense_dev *dev)
{
	const struct pios_invensense_cfg *cfg = dev->cfg;
	int32_t id;

	/*
	 * Reset the device.  The datasheet asks for 100 ms after DEVICE_RESET
	 * before the part is usable again; the sensor rail on this board has
	 * only just come up too, so do not shorten this.
	 */
	if (PIOS_INVENSENSE_SetReg(dev, PIOS_INVENSENSE_PWR_MGMT_REG,
				   PIOS_INVENSENSE_PWRMGMT_IMU_RST) != 0) {
		{ pios_invensense_dbg_rc = -1; return -1; }
	}
	PIOS_DELAY_WaitmS(100);

	/* Wake up and select the best available clock source (the PLL when the
	 * gyro is running, the internal oscillator otherwise). */
	if (PIOS_INVENSENSE_SetReg(dev, PIOS_INVENSENSE_PWR_MGMT_REG, cfg->pwr_mgmt_clk) != 0) {
		{ pios_invensense_dbg_rc = -2; return -2; }
	}
	PIOS_DELAY_WaitmS(10);

	/* Identify the part before configuring it. */
	id = PIOS_INVENSENSE_GetReg(dev, PIOS_INVENSENSE_WHOAMI);
	pios_invensense_dbg_id = id;
	if (id < 0) {
		{ pios_invensense_dbg_rc = -3; return -3; }
	}
	dev->whoami = (uint8_t)id;

	switch (dev->whoami) {
	case PIOS_INVENSENSE_WHOAMI_MPU9250:
	case PIOS_INVENSENSE_WHOAMI_MPU9255:
		if (cfg->type == PIOS_INVENSENSE_ICM20608) {
			{ pios_invensense_dbg_rc = -4; return -4; }
		}
		break;
	case PIOS_INVENSENSE_WHOAMI_ICM20608:
	case PIOS_INVENSENSE_WHOAMI_ICM20602:
		if (cfg->type == PIOS_INVENSENSE_MPU9250) {
			{ pios_invensense_dbg_rc = -4; return -4; }
		}
		break;
	default:
		/* Not a part we know.  On this board the usual cause is that
		 * VDD_SENSORS_EN was never driven high, in which case every
		 * read comes back 0x00 or 0xFF. */
		{ pios_invensense_dbg_rc = -5; return -5; }
	}

	/*
	 * Force SPI-only operation.  On the MPU9250 the I2C slave interface is
	 * live out of reset and will happily interpret bus noise; the datasheet
	 * requires I2C_IF_DIS for SPI use.
	 */
	if (PIOS_INVENSENSE_SetReg(dev, PIOS_INVENSENSE_USER_CTRL_REG, cfg->user_ctl) != 0) {
		{ pios_invensense_dbg_rc = -6; return -6; }
	}

	/* Gyro DLPF (CONFIG), then sample rate divider.  SMPLRT_DIV only has an
	 * effect when the DLPF is enabled, i.e. DLPF_CFG is neither 0 nor 7. */
	if (PIOS_INVENSENSE_SetReg(dev, PIOS_INVENSENSE_CONFIG_REG, (uint8_t)cfg->filter) != 0) {
		{ pios_invensense_dbg_rc = -7; return -7; }
	}
	if (PIOS_INVENSENSE_SetReg(dev, PIOS_INVENSENSE_SMPLRT_DIV_REG, cfg->smpl_rate_div) != 0) {
		{ pios_invensense_dbg_rc = -8; return -8; }
	}

	if (PIOS_INVENSENSE_SetReg(dev, PIOS_INVENSENSE_GYRO_CFG_REG, (uint8_t)cfg->gyro_range) != 0) {
		{ pios_invensense_dbg_rc = -9; return -9; }
	}
	dev->gyro_range = cfg->gyro_range;

	if (PIOS_INVENSENSE_SetReg(dev, PIOS_INVENSENSE_ACCEL_CFG_REG, (uint8_t)cfg->accel_range) != 0) {
		{ pios_invensense_dbg_rc = -10; return -10; }
	}
	dev->accel_range = cfg->accel_range;

	/*
	 * Accel DLPF.  This register does not exist on the MPU6000, which is
	 * why the older PiOS driver never touched it.  Leaving it at its reset
	 * value gives a 460 Hz bandwidth; match the gyro's bandwidth class
	 * instead so the two are not filtered differently.
	 */
	if (PIOS_INVENSENSE_SetReg(dev, PIOS_INVENSENSE_ACCEL_CFG2_REG, (uint8_t)cfg->filter) != 0) {
		{ pios_invensense_dbg_rc = -11; return -11; }
	}

	if (PIOS_INVENSENSE_SetReg(dev, PIOS_INVENSENSE_INT_CFG_REG, cfg->int_cfg) != 0) {
		{ pios_invensense_dbg_rc = -12; return -12; }
	}
	if (PIOS_INVENSENSE_SetReg(dev, PIOS_INVENSENSE_INT_EN_REG, cfg->int_en) != 0) {
		{ pios_invensense_dbg_rc = -13; return -13; }
	}

	dev->configured = true;
	if (dev->cfg->mag_ak8963) {
		/* Optional: a failure leaves the IMU running without a compass. */
		dev->mag_init_rc = PIOS_INVENSENSE_MagInit(dev);
	}
	return 0;
}

int32_t PIOS_INVENSENSE_Init(pios_invensense_t *handle, uint32_t spi_id,
			     uint32_t slave_num, const struct pios_invensense_cfg *cfg)
{
	struct invensense_dev *dev;

	PIOS_Assert(handle);
	PIOS_Assert(cfg);

	dev = PIOS_INVENSENSE_alloc();
	if (dev == NULL) {
		return -1;
	}

	dev->spi_id = spi_id;
	dev->slave_num = slave_num;
	dev->cfg = cfg;

	if (PIOS_INVENSENSE_Config(dev) != 0) {
		/* Leave the handle invalid so the caller can raise an alarm and
		 * carry on rather than wedging the board. */
		return -2;
	}

	*handle = (pios_invensense_t)dev;

	/* Only hook the data-ready line once the part is known good, so a dead
	 * sensor cannot storm us with interrupts. */
	if (cfg->exti_cfg != NULL) {
		if (PIOS_EXTI_Init(cfg->exti_cfg) != 0) {
			return -3;
		}
	}

	return 0;
}

xQueueHandle PIOS_INVENSENSE_GetQueue(pios_invensense_t handle)
{
	struct invensense_dev *dev = (struct invensense_dev *)handle;

	if (PIOS_INVENSENSE_Validate(dev) != 0) {
		return (xQueueHandle)NULL;
	}
	return dev->queue;
}

int32_t PIOS_INVENSENSE_ReadID(pios_invensense_t handle)
{
	struct invensense_dev *dev = (struct invensense_dev *)handle;

	if (PIOS_INVENSENSE_Validate(dev) != 0) {
		return -1;
	}
	return PIOS_INVENSENSE_GetReg(dev, PIOS_INVENSENSE_WHOAMI);
}

int32_t PIOS_INVENSENSE_Test(pios_invensense_t handle)
{
	struct invensense_dev *dev = (struct invensense_dev *)handle;
	int32_t id;

	if (PIOS_INVENSENSE_Validate(dev) != 0) {
		return -1;
	}

	id = PIOS_INVENSENSE_GetReg(dev, PIOS_INVENSENSE_WHOAMI);
	if (id < 0) {
		return -2;
	}
	/* Must still be the same part we identified at init. */
	if ((uint8_t)id != dev->whoami) {
		return -3;
	}
	return 0;
}

float PIOS_INVENSENSE_GetGyroScale(pios_invensense_t handle)
{
	struct invensense_dev *dev = (struct invensense_dev *)handle;

	if (PIOS_INVENSENSE_Validate(dev) != 0) {
		return 0.0f;
	}

	switch (dev->gyro_range) {
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
	struct invensense_dev *dev = (struct invensense_dev *)handle;

	if (PIOS_INVENSENSE_Validate(dev) != 0) {
		return 0.0f;
	}

	switch (dev->accel_range) {
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

/**
 * @brief Turn a raw temperature reading into degrees C.
 *
 * Deliberately not the MPU6000 formula.  That part is 340 LSB/C referenced to
 * 35 C; the MPU9250 is 333.87 LSB/C referenced to 21 C and the ICM-20608 is
 * 326.8 LSB/C referenced to 25 C.  Using the MPU6000 numbers here would put
 * the reported die temperature out by more than ten degrees, which matters
 * because the attitude code uses it for gyro temperature compensation.
 */
float PIOS_INVENSENSE_GetTemperature(pios_invensense_t handle, int16_t raw)
{
	struct invensense_dev *dev = (struct invensense_dev *)handle;

	if (PIOS_INVENSENSE_Validate(dev) != 0) {
		return 0.0f;
	}

	switch (dev->whoami) {
	case PIOS_INVENSENSE_WHOAMI_ICM20608:
	case PIOS_INVENSENSE_WHOAMI_ICM20602:
		return 25.0f + (float)raw / 326.8f;
	default:
		return 21.0f + (float)raw / 333.87f;
	}
}

/**
 * @brief Rotate a raw chip-frame sample into OpenPilot body axes.
 *
 * The Invensense frame has X to the right and Y forward; OpenPilot has X
 * forward and Y to the right, with Z inverted between the two.  The -1 - v
 * idiom rather than -v keeps the result inside int16_t when v is -32768.
 */
static void PIOS_INVENSENSE_Rotate(const struct invensense_dev *dev, const uint8_t *raw,
				   struct pios_invensense_data *data)
{
	int16_t accel_chip_x = (int16_t)(raw[0] << 8 | raw[1]);
	int16_t accel_chip_y = (int16_t)(raw[2] << 8 | raw[3]);
	int16_t accel_chip_z = (int16_t)(raw[4] << 8 | raw[5]);
	int16_t temperature  = (int16_t)(raw[6] << 8 | raw[7]);
	int16_t gyro_chip_x  = (int16_t)(raw[8] << 8 | raw[9]);
	int16_t gyro_chip_y  = (int16_t)(raw[10] << 8 | raw[11]);
	int16_t gyro_chip_z  = (int16_t)(raw[12] << 8 | raw[13]);

	switch (dev->cfg->orientation) {
	case PIOS_INVENSENSE_TOP_0DEG:
		data->accel_x = accel_chip_y;
		data->accel_y = accel_chip_x;
		data->gyro_x  = gyro_chip_y;
		data->gyro_y  = gyro_chip_x;
		break;
	case PIOS_INVENSENSE_TOP_90DEG:
		data->accel_x = accel_chip_x;
		data->accel_y = -1 - accel_chip_y;
		data->gyro_x  = gyro_chip_x;
		data->gyro_y  = -1 - gyro_chip_y;
		break;
	case PIOS_INVENSENSE_TOP_180DEG:
		data->accel_x = -1 - accel_chip_y;
		data->accel_y = -1 - accel_chip_x;
		data->gyro_x  = -1 - gyro_chip_y;
		data->gyro_y  = -1 - gyro_chip_x;
		break;
	case PIOS_INVENSENSE_TOP_270DEG:
		data->accel_x = -1 - accel_chip_x;
		data->accel_y = accel_chip_y;
		data->gyro_x  = -1 - gyro_chip_x;
		data->gyro_y  = gyro_chip_y;
		break;
	/* Bottom mounts: the TOP mapping with body Y negated (Z is handled
	 * below).  BOTTOM_0DEG is body = (chip_y, -chip_x, chip_z). */
	case PIOS_INVENSENSE_BOTTOM_0DEG:
		data->accel_x = accel_chip_y;
		data->accel_y = -1 - accel_chip_x;
		data->gyro_x  = gyro_chip_y;
		data->gyro_y  = -1 - gyro_chip_x;
		break;
	case PIOS_INVENSENSE_BOTTOM_90DEG:
		data->accel_x = accel_chip_x;
		data->accel_y = accel_chip_y;
		data->gyro_x  = gyro_chip_x;
		data->gyro_y  = gyro_chip_y;
		break;
	case PIOS_INVENSENSE_BOTTOM_180DEG:
		data->accel_x = -1 - accel_chip_y;
		data->accel_y = accel_chip_x;
		data->gyro_x  = -1 - gyro_chip_y;
		data->gyro_y  = gyro_chip_x;
		break;
	case PIOS_INVENSENSE_BOTTOM_270DEG:
		data->accel_x = -1 - accel_chip_x;
		data->accel_y = -1 - accel_chip_y;
		data->gyro_x  = -1 - gyro_chip_x;
		data->gyro_y  = -1 - gyro_chip_y;
		break;
	default:
		data->accel_x = accel_chip_y;
		data->accel_y = accel_chip_x;
		data->gyro_x  = gyro_chip_y;
		data->gyro_y  = gyro_chip_x;
		break;
	}

	if (dev->cfg->orientation >= PIOS_INVENSENSE_BOTTOM_0DEG) {
		/* upside down: chip Z already points along body Z (down) */
		data->accel_z = accel_chip_z;
		data->gyro_z = gyro_chip_z;
	} else {
		data->accel_z = -1 - accel_chip_z;
		data->gyro_z = -1 - gyro_chip_z;
	}
	data->temperature = temperature;
	/*
	 * The AK8963 sits in the same package with its axes at chip
	 * (x, y, z) = mag (y, x, -z) (MPU-9250 datasheet, orientation of axes).
	 * Express the field in the chip frame and push it through the same
	 * mapping as the accelerometer, so it lands in the same body frame.
	 * The part is little-endian, unlike the gyro/accel registers.
	 */
	data->mag_valid = 0;
	data->mag_x = data->mag_y = data->mag_z = 0;
	if (dev->has_mag) {
		const uint8_t *m = &raw[PIOS_INVENSENSE_MAG_OFFSET];
		uint8_t st1 = m[0], st2 = m[7];
		int16_t hx = (int16_t)(m[2] << 8 | m[1]);
		int16_t hy = (int16_t)(m[4] << 8 | m[3]);
		int16_t hz = (int16_t)(m[6] << 8 | m[5]);
		int16_t chip_x = hy, chip_y = hx, chip_z = (int16_t)(-1 - hz);
		uint8_t as_accel[PIOS_INVENSENSE_BURST_LEN] = {
			(uint8_t)(chip_x >> 8), (uint8_t)chip_x,
			(uint8_t)(chip_y >> 8), (uint8_t)chip_y,
			(uint8_t)(chip_z >> 8), (uint8_t)chip_z,
		};
		struct pios_invensense_data tmp;
		struct invensense_dev nomag = *dev;
		nomag.has_mag = false;
		PIOS_INVENSENSE_Rotate(&nomag, as_accel, &tmp);
		data->mag_x = tmp.accel_x;
		data->mag_y = tmp.accel_y;
		data->mag_z = tmp.accel_z;
		if ((st1 & AK8963_ST1_DRDY) && !(st2 & AK8963_ST2_HOFL)) {
			data->mag_valid = 1;
		}
	}
}

/**
 * @brief Blocking read of one sample, for probing and self-test.
 */
/* Diagnostics: interrupt count, samples lost to a busy bus, samples lost to a
 * full queue.  Any argument may be NULL. */
void PIOS_INVENSENSE_GetStats(pios_invensense_t handle, uint32_t *irqs, uint32_t *bus_fails, uint32_t *queue_full)
{
	struct invensense_dev *dev = (struct invensense_dev *)handle;
	if (PIOS_INVENSENSE_Validate(dev) != 0) {
		return;
	}
	if (irqs) *irqs = dev->irqs;
	if (bus_fails) *bus_fails = dev->bus_fails;
	if (queue_full) *queue_full = dev->queue_full;
}

int32_t PIOS_INVENSENSE_GetMagAdjust(pios_invensense_t handle, float asa[3])
{
	struct invensense_dev *dev = (struct invensense_dev *)handle;
	if (PIOS_INVENSENSE_Validate(dev) != 0 || !dev->has_mag) {
		return -1;
	}
	for (int i = 0; i < 3; i++) asa[i] = dev->mag_asa[i];
	return 0;
}

void PIOS_INVENSENSE_GetMagStats(pios_invensense_t handle, uint32_t *samples, uint32_t *overflow, int32_t *init_rc)
{
	struct invensense_dev *dev = (struct invensense_dev *)handle;
	if (PIOS_INVENSENSE_Validate(dev) != 0) {
		return;
	}
	if (samples) *samples = dev->mag_samples;
	if (overflow) *overflow = dev->mag_overflow;
	if (init_rc) *init_rc = dev->mag_init_rc;
}

int32_t PIOS_INVENSENSE_ReadSensors(pios_invensense_t handle, struct pios_invensense_data *data)
{
	struct invensense_dev *dev = (struct invensense_dev *)handle;
	uint8_t tx[1 + PIOS_INVENSENSE_BURST_LEN];
	uint8_t rx[1 + PIOS_INVENSENSE_BURST_LEN];

	if (PIOS_INVENSENSE_Validate(dev) != 0) {
		return -1;
	}

	memset(tx, 0, sizeof(tx));
	tx[0] = PIOS_INVENSENSE_SPI_READ_FLAG | PIOS_INVENSENSE_ACCEL_X_OUT_MSB;

	if (PIOS_INVENSENSE_ClaimBus(dev, true, false, NULL) != 0) {
		return -2;
	}

	if (PIOS_SPI_TransferBlock(dev->spi_id, tx, rx, sizeof(tx), NULL) < 0) {
		PIOS_INVENSENSE_ReleaseBus(dev, false, NULL);
		return -3;
	}

	PIOS_INVENSENSE_ReleaseBus(dev, false, NULL);

	PIOS_INVENSENSE_Rotate(dev, &rx[1], data);
	data->deferred = 0;
	PIOS_INVENSENSE_MagBookkeeping(dev, &rx[1], data);
	return 0;
}

/**
 * @brief Data-ready interrupt: burst-read one sample and queue it.
 *
 * Reads the sensor registers directly rather than going through the FIFO the
 * way the old MPU6000 driver does.  With one interrupt per sample there is
 * nothing for the FIFO to buffer, and skipping it removes both the extra
 * round trip to read the FIFO depth and the overrun handling that goes with
 * it.
 */
bool PIOS_INVENSENSE_IRQHandler(pios_invensense_t handle)
{
	struct invensense_dev *dev = (struct invensense_dev *)handle;
	static uint8_t tx[1 + PIOS_INVENSENSE_BURST_LEN];
	static uint8_t rx[1 + PIOS_INVENSENSE_BURST_LEN];
	struct pios_invensense_data data;
	/* Both the bus semaphore and the sample queue can ready a higher
	 * priority task; collect either into one flag for the ISR epilogue. */
	bool woken = false;

	if (PIOS_INVENSENSE_Validate(dev) != 0 || !dev->configured) {
		return false;
	}

	tx[0] = PIOS_INVENSENSE_SPI_READ_FLAG | PIOS_INVENSENSE_ACCEL_X_OUT_MSB;
	portBASE_TYPE queue_woken = pdFALSE;
	bool bus_ok = (PIOS_INVENSENSE_ClaimBus(dev, true, true, &woken) == 0);
	if (bus_ok) {
		if (PIOS_SPI_TransferBlock(dev->spi_id, tx, rx, sizeof(tx), NULL) < 0) {
			bus_ok = false;
		}
		PIOS_INVENSENSE_ReleaseBus(dev, true, &woken);
	}
	if (!bus_ok) {
		/* The bus is held by a task (the baro shares it).  An ISR cannot
		 * wait for it, and dropping the sample silently starves the
		 * sensors task for its whole timeout.  Hand the read to the task
		 * instead: it blocks on the bus mutex, which lends the holder its
		 * priority, so the sample is only microseconds late. */
		dev->bus_fails++;
		data.deferred = 1;
		if (xQueueSendToBackFromISR(dev->queue, (void *)&data, &queue_woken) != pdTRUE) {
			dev->queue_full++;
		}
		return woken || (queue_woken == pdTRUE);
	}
	PIOS_INVENSENSE_Rotate(dev, &rx[1], &data);
	data.deferred = 0;
	PIOS_INVENSENSE_MagBookkeeping(dev, &rx[1], &data);
	if (xQueueSendToBackFromISR(dev->queue, (void *)&data, &queue_woken) != pdTRUE) {
		dev->queue_full++;
	}
	woken = woken || (queue_woken == pdTRUE);

	dev->irqs++;

	return woken;
}

#endif /* PIOS_INCLUDE_INVENSENSE */

/**
 * @}
 * @}
 */
