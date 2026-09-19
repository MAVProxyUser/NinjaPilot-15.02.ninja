/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_IOMCU IO co-processor client (PX4IO register protocol)
 * @{
 *
 * @file       pios_iomcu.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2026.
 * @brief      Talks the ArduPilot IO firmware's register protocol over a UART
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

/*
 * The IO co-processor on a Cube or Pixhawk is a second MCU that owns the
 * MAIN OUT header, the RC IN connector and the safety switch.  It runs
 * ArduPilot's IO firmware, which is never written here: this is only a
 * client of its register protocol.
 *
 * Wire format (both directions, little-endian):
 *   byte 0   count (bits 0-5, number of 16-bit registers) | code (bits 6-7)
 *   byte 1   crc-8, polynomial 0x07, over the packet with this byte zeroed
 *   byte 2   page
 *   byte 3   offset (first register)
 *   then     count * 2 bytes of registers
 * Codes sent: 0 read, 1 write.  Codes received: 0 success, 1 corrupt,
 * 2 error.  A read request is the 4-byte header; the reply carries the
 * registers.  A write carries the registers; the reply is the 4-byte
 * header.  Pages and registers as in ioprotocol.h of the IO firmware.
 */

#include "pios.h"

#if defined(PIOS_INCLUDE_IOMCU)

#include "pios_iomcu.h"
#include <string.h>

#define PKT_MAX_REGS		22
#define PKT_HEADER		4
#define CODE_READ		0
#define CODE_WRITE		1
#define CODE_SUCCESS		0

#define PAGE_CONFIG		0
#define PAGE_STATUS		1
#define PAGE_SERVOS		3
#define PAGE_RAW_RCIN		4
#define PAGE_SETUP		50
#define PAGE_DIRECT_PWM		54

#define REG_SETUP_ARMING	1
#define REG_SETUP_PWM_RATE_MASK	2
#define REG_SETUP_DEFAULTRATE	3
#define REG_SETUP_ALTRATE	4
#define REG_SETUP_FORCE_SAFETY_OFF 12
#define FORCE_SAFETY_MAGIC	22027

#define ARMING_IO_ARM_OK	(1 << 0)
#define ARMING_FMU_ARMED	(1 << 1)
#define ARMING_RC_HANDLING_DISABLED (1 << 6)

/* Register counts of the pages as the IO firmware lays them out
 * (natural alignment, no packing): config 12 bytes, status 44, rc input 38. */
#define CONFIG_REGS		6
#define STATUS_REGS		22
#define RCIN_REGS		19

#define IOMCU_PERIOD_MS		10	/* servo output rate 100 Hz */
#define IOMCU_REPLY_TIMEOUT_MS	10
#define IOMCU_RC_STALE_MS	100
#define IOMCU_FAILS_TO_LOST	20

enum pios_iomcu_dev_magic {
	PIOS_IOMCU_DEV_MAGIC = 0x10AC0D01,
};

struct pios_iomcu_dev {
	enum pios_iomcu_dev_magic magic;
	uint32_t com_id;
	bool force_safety_off;
	TaskHandle_t task;

	struct pios_iomcu_status st;
	uint32_t rc_last_ok_ms;
	uint32_t consecutive_fails;

	uint16_t servo[PIOS_IOMCU_NUM_SERVOS];
	uint16_t rate_hz;
	bool rate_dirty;
	bool safety_forced;
	uint8_t tx[PKT_HEADER + 2 * PKT_MAX_REGS];
	uint8_t rx[PKT_HEADER + 2 * PKT_MAX_REGS];
	uint16_t rx_fill;
};

static uint8_t crc8(const uint8_t *p, uint8_t len)
{
	uint8_t crc = 0;
	while (len--) {
		crc ^= *p++;
		for (int i = 0; i < 8; i++) {
			crc = (crc & 0x80) ? (uint8_t)((crc << 1) ^ 0x07) : (uint8_t)(crc << 1);
		}
	}
	return crc;
}

static int32_t PIOS_IOMCU_Validate(struct pios_iomcu_dev *dev)
{
	return (dev && dev->magic == PIOS_IOMCU_DEV_MAGIC) ? 0 : -1;
}

static void PIOS_IOMCU_Flush(struct pios_iomcu_dev *dev)
{
	uint8_t junk[32];
	uint16_t n;
	while ((n = PIOS_COM_ReceiveBuffer(dev->com_id, junk, sizeof(junk), 0)) > 0) {
		dev->st.rx_bytes += n;
	}
}

/* Read exactly want bytes into dev->rx, or give up after the timeout. */
static bool PIOS_IOMCU_Receive(struct pios_iomcu_dev *dev, uint16_t want, uint32_t timeout_ms)
{
	uint16_t got = dev->rx_fill;
	uint32_t t0 = xTaskGetTickCount();
	while (got < want) {
		uint16_t n = PIOS_COM_ReceiveBuffer(dev->com_id, &dev->rx[got], want - got, 1);
		got += n;
		dev->rx_fill = got;
		dev->st.rx_bytes += n;
		if (n == 0 && (xTaskGetTickCount() - t0) > timeout_ms) {
			return false;
		}
	}
	return true;
}

static bool PIOS_IOMCU_Transact(struct pios_iomcu_dev *dev, uint8_t code, uint8_t page, uint8_t offset,
				uint8_t count, const uint16_t *wr, uint16_t *rd)
{
	if (count > PKT_MAX_REGS) {
		return false;
	}
	/* A read request carries (zeroed) registers too: the older protocol
	 * expects the request to be as long as the reply it asks for. */
	uint8_t txlen = PKT_HEADER + 2 * count;

	dev->tx[0] = (uint8_t)((count & 0x3F) | (code << 6));
	dev->tx[1] = 0;
	dev->tx[2] = page;
	dev->tx[3] = offset;
	if (code == CODE_WRITE) {
		memcpy(&dev->tx[PKT_HEADER], wr, 2 * count);
	} else {
		memset(&dev->tx[PKT_HEADER], 0, 2 * count);
	}
	dev->tx[1] = crc8(dev->tx, txlen);

	PIOS_IOMCU_Flush(dev);
	dev->rx_fill = 0;
	if (PIOS_COM_SendBuffer(dev->com_id, dev->tx, txlen) != txlen) {
		dev->st.fail_timeout++;
		goto fail;
	}
	/* Header first; the IO says how many registers follow.  An older IO
	 * firmware has shorter pages than the one we read from, so take what it
	 * sends rather than waiting for bytes that never come. */
	if (!PIOS_IOMCU_Receive(dev, PKT_HEADER, IOMCU_REPLY_TIMEOUT_MS)) {
		dev->st.fail_timeout++;
		goto fail;
	}
	uint8_t rx_count = dev->rx[0] & 0x3F;
	if (rx_count > PKT_MAX_REGS) {
		dev->st.fail_short++;
		goto fail;
	}
	uint16_t rxlen = PKT_HEADER + ((code == CODE_READ) ? 2 * rx_count : 0);
	if (rxlen > PKT_HEADER && !PIOS_IOMCU_Receive(dev, rxlen, IOMCU_REPLY_TIMEOUT_MS)) {
		dev->st.fail_timeout++;
		goto fail;
	}
	{
		uint8_t got_crc = dev->rx[1];
		dev->rx[1] = 0;
		if (crc8(dev->rx, (uint8_t)rxlen) != got_crc) {
			dev->st.fail_crc++;
			goto fail;
		}
	}
	if ((dev->rx[0] >> 6) != CODE_SUCCESS) {
		dev->st.fail_code++;
		goto fail;
	}
	if (code == CODE_READ) {
		if (rx_count == 0) {
			dev->st.fail_short++;
			goto fail;
		}
		memset(rd, 0, 2 * count);
		memcpy(rd, &dev->rx[PKT_HEADER], 2 * (rx_count < count ? rx_count : count));
		if (page == PAGE_STATUS) dev->st.status_regs = rx_count;
		if (page == PAGE_RAW_RCIN) dev->st.rcin_regs = rx_count;
	}
	dev->st.ok++;
	dev->consecutive_fails = 0;
	return true;

fail:
	dev->st.fail++;
	dev->st.last_fail_page = page;
	dev->consecutive_fails++;
	return false;
}

static bool PIOS_IOMCU_ReadRegs(struct pios_iomcu_dev *dev, uint8_t page, uint8_t offset, uint8_t count, uint16_t *regs)
{
	return PIOS_IOMCU_Transact(dev, CODE_READ, page, offset, count, NULL, regs);
}

static bool PIOS_IOMCU_WriteRegs(struct pios_iomcu_dev *dev, uint8_t page, uint8_t offset, uint8_t count, const uint16_t *regs)
{
	return PIOS_IOMCU_Transact(dev, CODE_WRITE, page, offset, count, regs, NULL);
}

static bool PIOS_IOMCU_ModifyReg(struct pios_iomcu_dev *dev, uint8_t page, uint8_t offset, uint16_t clear, uint16_t set)
{
	uint16_t v;
	if (!PIOS_IOMCU_ReadRegs(dev, page, offset, 1, &v)) {
		return false;
	}
	v = (v & ~clear) | set;
	return PIOS_IOMCU_WriteRegs(dev, page, offset, 1, &v);
}

static bool PIOS_IOMCU_Handshake(struct pios_iomcu_dev *dev)
{
	uint16_t cfg[CONFIG_REGS];

	if (!PIOS_IOMCU_ReadRegs(dev, PAGE_CONFIG, 0, CONFIG_REGS, cfg)) {
		return false;
	}
	dev->st.protocol_version = cfg[0];
	dev->st.protocol_version2 = cfg[1];
	dev->st.mcuid = (uint32_t)cfg[2] | ((uint32_t)cfg[3] << 16);
	dev->st.state = PIOS_IOMCU_STATE_INIT;

	/* The IO may arm its outputs, this firmware does the mixing (no IO-side
	 * failsafe mixing), and the outputs follow our values at once: this
	 * firmware's own arming decides what those values are. */
	if (!PIOS_IOMCU_ModifyReg(dev, PAGE_SETUP, REG_SETUP_ARMING, 0,
				  ARMING_IO_ARM_OK | ARMING_RC_HANDLING_DISABLED | ARMING_FMU_ARMED)) {
		return false;
	}
	if (dev->force_safety_off && !dev->safety_forced) {
		uint16_t magic = FORCE_SAFETY_MAGIC;
		if (!PIOS_IOMCU_WriteRegs(dev, PAGE_SETUP, REG_SETUP_FORCE_SAFETY_OFF, 1, &magic)) {
			return false;
		}
		dev->safety_forced = true;
	}
	dev->rate_dirty = true;
	dev->st.state = PIOS_IOMCU_STATE_UP;
	return true;
}

static void PIOS_IOMCU_ApplyRate(struct pios_iomcu_dev *dev)
{
	uint16_t regs[3];
	/* PWM_RATE_MASK selects the channels on ALTRATE; the rest run DEFAULTRATE. */
	regs[0] = (dev->rate_hz == 50 || dev->rate_hz == 0) ? 0 : 0xFF;
	regs[1] = 50;
	regs[2] = (dev->rate_hz == 0) ? 50 : dev->rate_hz;
	if (PIOS_IOMCU_WriteRegs(dev, PAGE_SETUP, REG_SETUP_PWM_RATE_MASK, 3, regs)) {
		dev->rate_dirty = false;
	}
}

static void PIOS_IOMCU_Task(void *parameters)
{
	struct pios_iomcu_dev *dev = (struct pios_iomcu_dev *)parameters;
	TickType_t last = xTaskGetTickCount();
	uint32_t tick = 0;
	uint16_t regs[PKT_MAX_REGS];

	/* The IO's bootloader listens briefly after power-up before it starts
	 * the application; nothing answers until then. */
	vTaskDelay(500 / portTICK_PERIOD_MS);

	while (1) {
		vTaskDelayUntil(&last, IOMCU_PERIOD_MS / portTICK_PERIOD_MS);
		tick++;

		if (dev->st.state != PIOS_IOMCU_STATE_UP) {
			if ((tick % 50) == 0) {	/* every 500 ms */
				PIOS_IOMCU_Handshake(dev);
			}
			continue;
		}

		/* outputs, every period */
		memcpy(regs, dev->servo, sizeof(dev->servo));
		PIOS_IOMCU_WriteRegs(dev, PAGE_DIRECT_PWM, 0, PIOS_IOMCU_NUM_SERVOS, regs);

		if (dev->rate_dirty) {
			PIOS_IOMCU_ApplyRate(dev);
		}

		/* RC input, every other period (50 Hz is plenty for any RC link) */
		if ((tick % 2) == 0 && PIOS_IOMCU_ReadRegs(dev, PAGE_RAW_RCIN, 0, RCIN_REGS, regs)) {
			const uint8_t *b = (const uint8_t *)regs;
			dev->st.rc_count = b[0];
			dev->st.rc_failsafe = b[1] & 0x01;
			dev->st.rc_ok = (b[1] >> 1) & 0x01;
			dev->st.rc_protocol = b[2];
			memcpy(dev->st.rc, &regs[2], sizeof(dev->st.rc));
			dev->st.rc_rssi = (int16_t)regs[18];
			if (dev->st.rc_ok && !dev->st.rc_failsafe) {
				dev->rc_last_ok_ms = xTaskGetTickCount() * portTICK_PERIOD_MS;
			}
		}

		/* status and servo readback, 10 Hz */
		if ((tick % 10) == 5 && PIOS_IOMCU_ReadRegs(dev, PAGE_STATUS, 0, STATUS_REGS, regs)) {
			const uint8_t *b = (const uint8_t *)regs;
			if (dev->st.status_regs >= STATUS_REGS) {
				/* current IO firmware: page_reg_status */
				dev->st.vservo_mv = regs[6];
				dev->st.vrssi_mv = regs[7];
				memcpy(&dev->st.io_errors, &b[16], 4);
				dev->st.safety_off = b[32];
			} else {
				/* older IO firmware, the PX4IO layout: freemem, cpuload,
				 * flags, alarms, vbatt, ibatt, vservo, vrssi, prssi, ...
				 * with SAFETY_OFF as flags bit 4. */
				dev->st.vservo_mv = regs[6];
				dev->st.vrssi_mv = regs[7];
				dev->st.io_errors = regs[3];
				dev->st.status_flags = regs[2];
				dev->st.safety_off = ((regs[2] >> 4) & 1) | ((regs[2] >> 12) & 1);
			}
		}
		if ((tick % 10) == 8 && PIOS_IOMCU_ReadRegs(dev, PAGE_SERVOS, 0, PIOS_IOMCU_NUM_SERVOS, regs)) {
			memcpy(dev->st.servo_readback, regs, sizeof(dev->st.servo_readback));
		}

		if (dev->consecutive_fails > IOMCU_FAILS_TO_LOST) {
			dev->st.state = PIOS_IOMCU_STATE_LOST;
			dev->st.rc_ok = 0;
		}
	}
}

int32_t PIOS_IOMCU_Init(uint32_t *iomcu_id, uint32_t com_id, bool force_safety_off)
{
	struct pios_iomcu_dev *dev = (struct pios_iomcu_dev *)pios_malloc(sizeof(*dev));

	if (!dev) {
		return -1;
	}
	memset(dev, 0, sizeof(*dev));
	dev->magic = PIOS_IOMCU_DEV_MAGIC;
	dev->com_id = com_id;
	dev->force_safety_off = force_safety_off;
	dev->rate_hz = 50;
	*iomcu_id = (uint32_t)dev;

	if (xTaskCreate(PIOS_IOMCU_Task, "IOMCU", 512, dev,
			tskIDLE_PRIORITY + 2, &dev->task) != pdPASS) {
		return -2;
	}
	return 0;
}

void PIOS_IOMCU_ServoSet(uint32_t iomcu_id, uint8_t channel, uint16_t us)
{
	struct pios_iomcu_dev *dev = (struct pios_iomcu_dev *)iomcu_id;

	if (PIOS_IOMCU_Validate(dev) != 0 || channel >= PIOS_IOMCU_NUM_SERVOS) {
		return;
	}
	dev->servo[channel] = us;
}

void PIOS_IOMCU_ServoSetHz(uint32_t iomcu_id, uint16_t hz)
{
	struct pios_iomcu_dev *dev = (struct pios_iomcu_dev *)iomcu_id;

	if (PIOS_IOMCU_Validate(dev) != 0) {
		return;
	}
	if (hz != dev->rate_hz) {
		dev->rate_hz = hz;
		dev->rate_dirty = true;
	}
}

int32_t PIOS_IOMCU_RcGet(uint32_t iomcu_id, uint8_t channel)
{
	struct pios_iomcu_dev *dev = (struct pios_iomcu_dev *)iomcu_id;

	if (PIOS_IOMCU_Validate(dev) != 0) {
		return PIOS_RCVR_NODRIVER;
	}
	if (channel >= PIOS_IOMCU_NUM_RC || channel >= dev->st.rc_count) {
		return PIOS_RCVR_INVALID;
	}
	uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;
	if (dev->st.state != PIOS_IOMCU_STATE_UP || !dev->st.rc_ok || dev->st.rc_failsafe ||
	    (now - dev->rc_last_ok_ms) > IOMCU_RC_STALE_MS) {
		return PIOS_RCVR_TIMEOUT;
	}
	return dev->st.rc[channel];
}

void PIOS_IOMCU_GetStatus(uint32_t iomcu_id, struct pios_iomcu_status *status)
{
	struct pios_iomcu_dev *dev = (struct pios_iomcu_dev *)iomcu_id;

	if (PIOS_IOMCU_Validate(dev) != 0 || !status) {
		return;
	}
	*status = dev->st;
	status->rc_age_ms = xTaskGetTickCount() * portTICK_PERIOD_MS - dev->rc_last_ok_ms;
}

static int32_t PIOS_IOMCU_RcvrRead(uint32_t rcvr_id, uint8_t channel)
{
	return PIOS_IOMCU_RcGet(rcvr_id, channel);
}

const struct pios_rcvr_driver pios_iomcu_rcvr_driver = {
	.read = PIOS_IOMCU_RcvrRead,
};

#endif /* PIOS_INCLUDE_IOMCU */

/**
 * @}
 * @}
 */
