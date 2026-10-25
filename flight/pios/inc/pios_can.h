/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_CAN CAN bus (bxCAN) driver
 * @brief Classic CAN frames in and out of an STM32 bxCAN peripheral: RX by
 *        interrupt into a queue, TX through the hardware mailboxes.
 * @{
 *
 * @file       pios_can.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2026.
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

#ifndef PIOS_CAN_H
#define PIOS_CAN_H

#include <stdint.h>
#include <stdbool.h>

struct pios_can_frame {
    uint32_t id;      /* 11-bit or 29-bit identifier */
    bool     ext;     /* extended (29-bit) identifier */
    uint8_t  dlc;     /* 0..8 */
    uint8_t  data[8];
};

struct pios_can_stats {
    uint32_t rx_frames;
    uint32_t tx_frames;
    uint32_t rx_dropped;   /* queue full */
    uint32_t tx_dropped;   /* no free mailbox */
    uint8_t  tx_errors;    /* TEC */
    uint8_t  rx_errors;    /* REC */
    bool     bus_off;
};

struct pios_can_cfg;

extern int32_t PIOS_CAN_Init(uint32_t *can_id, const struct pios_can_cfg *cfg);
/* 0 = queued in a mailbox, -1 = no free mailbox right now */
extern int32_t PIOS_CAN_Send(uint32_t can_id, const struct pios_can_frame *frame);
extern bool PIOS_CAN_Receive(uint32_t can_id, struct pios_can_frame *frame, uint32_t timeout_ms);
extern void PIOS_CAN_GetStats(uint32_t can_id, struct pios_can_stats *stats);

#endif /* PIOS_CAN_H */

/**
 * @}
 * @}
 */
