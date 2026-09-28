/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_CAN CAN bus (bxCAN) driver
 * @{
 *
 * @file       pios_can_priv.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2026.
 * @brief      Board configuration of a bxCAN peripheral
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

#ifndef PIOS_CAN_PRIV_H
#define PIOS_CAN_PRIV_H

#include <pios.h>
#include <pios_stm32.h>
#include "pios_can.h"

struct pios_can_cfg {
    CAN_TypeDef     *regs;
    uint32_t        rcc_periph;  /* RCC_APB1Periph_CANx; CAN2 also needs CAN1's clock, handled by the driver */
    CAN_InitTypeDef init;        /* bit timing and mode */
    uint8_t         filter_bank; /* first filter bank owned by this peripheral (0 for CAN1, 14 for CAN2) */
    uint8_t         remap;       /* GPIO_AF_CANx */
    struct stm32_gpio rx;
    struct stm32_gpio tx;
    struct stm32_irq  rx_irq;    /* CANx_RX0_IRQn */
};

#endif /* PIOS_CAN_PRIV_H */

/**
 * @}
 * @}
 */
