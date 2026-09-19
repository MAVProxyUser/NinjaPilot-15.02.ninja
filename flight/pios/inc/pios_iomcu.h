/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_IOMCU IO co-processor client (PX4IO register protocol)
 * @brief MAIN OUT 1-8, RC IN and the safety switch on boards whose IO
 *        co-processor runs the ArduPilot IO firmware (Cube, Pixhawk).
 * @{
 *
 * @file       pios_iomcu.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2026.
 * @brief      IO co-processor client header
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

#ifndef PIOS_IOMCU_H
#define PIOS_IOMCU_H

#include <stdint.h>
#include <stdbool.h>
#include "pios_rcvr.h"

#define PIOS_IOMCU_NUM_SERVOS   8	/* MAIN OUT 1-8 */
#define PIOS_IOMCU_NUM_RC       16	/* channels the IO decodes */

enum pios_iomcu_state {
	PIOS_IOMCU_STATE_OFFLINE = 0,	/* never answered */
	PIOS_IOMCU_STATE_INIT,		/* answered, handshake in progress */
	PIOS_IOMCU_STATE_UP,		/* configured and being served */
	PIOS_IOMCU_STATE_LOST,		/* was up, stopped answering */
};

struct pios_iomcu_status {
	enum pios_iomcu_state state;
	uint16_t protocol_version;
	uint16_t protocol_version2;
	uint32_t mcuid;
	uint8_t  safety_off;		/* 1 = outputs enabled by the IO */
	uint16_t status_flags;		/* raw flags word of the older status layout */
	uint16_t vservo_mv;		/* servo rail, millivolts */
	uint16_t vrssi_mv;
	uint32_t io_errors;		/* the IO's own error counter */
	uint32_t rx_bytes;		/* bytes ever received from the IO (diagnostic) */
	uint32_t ok;			/* our transactions that succeeded */
	uint32_t fail;			/* ... and failed (timeout, crc, code) */
	uint32_t fail_timeout;
	uint32_t fail_crc;
	uint32_t fail_code;
	uint32_t fail_short;
	uint8_t  status_regs;		/* registers the IO returned for the status page */
	uint8_t  rcin_regs;		/* ... and for the RC input page */
	uint8_t  last_fail_page;
	uint8_t  rc_count;
	uint8_t  rc_ok;
	uint8_t  rc_failsafe;
	uint8_t  rc_protocol;
	int16_t  rc_rssi;
	uint32_t rc_age_ms;		/* since the last good RC frame */
	uint16_t rc[PIOS_IOMCU_NUM_RC];
	uint16_t servo_readback[PIOS_IOMCU_NUM_SERVOS];	/* what the IO says it outputs */
};

/*
 * Start the client task on a COM port already opened at 1.5 Mbaud.
 * force_safety_off: write the IO's "force safety off" magic once it is
 * up, so the outputs follow this firmware's arming instead of the safety
 * switch (true for the OpenPilot semantics: motors idle when disarmed).
 */
extern int32_t PIOS_IOMCU_Init(uint32_t *iomcu_id, uint32_t com_id, bool force_safety_off);

/* MAIN OUT channel 0..7, microseconds; 0 stops the pulses. */
extern void PIOS_IOMCU_ServoSet(uint32_t iomcu_id, uint8_t channel, uint16_t us);
/* PWM rate for all MAIN OUT channels (50 default). */
extern void PIOS_IOMCU_ServoSetHz(uint32_t iomcu_id, uint16_t hz);
/* PIOS_RCVR semantics: microseconds, or PIOS_RCVR_TIMEOUT / _INVALID. */
extern int32_t PIOS_IOMCU_RcGet(uint32_t iomcu_id, uint8_t channel);
extern void PIOS_IOMCU_GetStatus(uint32_t iomcu_id, struct pios_iomcu_status *status);

extern const struct pios_rcvr_driver pios_iomcu_rcvr_driver;

#endif	/* PIOS_IOMCU_H */

/**
 * @}
 * @}
 */
