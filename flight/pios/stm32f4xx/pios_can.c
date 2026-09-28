/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_CAN CAN bus (bxCAN) driver
 * @brief STM32F4 bxCAN: accept-everything filter, RX0 interrupt into a
 *        FreeRTOS queue, TX straight into the three hardware mailboxes.
 * @{
 *
 * @file       pios_can.c
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

#include "pios.h"

#ifdef PIOS_INCLUDE_CAN

#include "pios_can_priv.h"

#define PIOS_CAN_RX_QUEUE_LEN 32

enum pios_can_dev_magic {
    PIOS_CAN_DEV_MAGIC = 0xCA4BC0DE,
};

struct pios_can_dev {
    enum pios_can_dev_magic magic;
    const struct pios_can_cfg *cfg;
    QueueHandle_t rx_queue;
    struct pios_can_stats stats;
};

static struct pios_can_dev *pios_can_dev_1;
static struct pios_can_dev *pios_can_dev_2;

static bool PIOS_CAN_validate(struct pios_can_dev *dev)
{
    return dev && dev->magic == PIOS_CAN_DEV_MAGIC;
}

static void PIOS_CAN_gpio_init(const struct stm32_gpio *pin, uint8_t af)
{
    GPIO_PinAFConfig(pin->gpio, __builtin_ctz(pin->init.GPIO_Pin), af);
    GPIO_Init(pin->gpio, (GPIO_InitTypeDef *)&pin->init);
}

int32_t PIOS_CAN_Init(uint32_t *can_id, const struct pios_can_cfg *cfg)
{
    PIOS_Assert(can_id);
    PIOS_Assert(cfg);

    struct pios_can_dev *dev = (struct pios_can_dev *)pios_malloc(sizeof(*dev));
    if (!dev) {
        return -1;
    }
    memset(dev, 0, sizeof(*dev));
    dev->magic    = PIOS_CAN_DEV_MAGIC;
    dev->cfg      = cfg;
    dev->rx_queue = xQueueCreate(PIOS_CAN_RX_QUEUE_LEN, sizeof(struct pios_can_frame));
    if (!dev->rx_queue) {
        return -2;
    }

    /* CAN2 is a slave of CAN1 (shared filter banks): both clocks on. */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1 | cfg->rcc_periph, ENABLE);

    PIOS_CAN_gpio_init(&cfg->rx, cfg->remap);
    PIOS_CAN_gpio_init(&cfg->tx, cfg->remap);

    CAN_DeInit(cfg->regs);
    if (CAN_Init(cfg->regs, (CAN_InitTypeDef *)&cfg->init) != CAN_InitStatus_Success) {
        return -3; /* no acknowledge of INRQ: peripheral not clocked or wired */
    }

    /* One accept-everything mask filter into FIFO 0. */
    CAN_SlaveStartBank(14);
    CAN_FilterInitTypeDef filter = {
        .CAN_FilterNumber         = cfg->filter_bank,
        .CAN_FilterMode           = CAN_FilterMode_IdMask,
        .CAN_FilterScale          = CAN_FilterScale_32bit,
        .CAN_FilterIdHigh         = 0,
        .CAN_FilterIdLow          = 0,
        .CAN_FilterMaskIdHigh     = 0,
        .CAN_FilterMaskIdLow      = 0,
        .CAN_FilterFIFOAssignment = CAN_Filter_FIFO0,
        .CAN_FilterActivation     = ENABLE,
    };
    CAN_FilterInit(&filter);

    if (cfg->regs == CAN1) {
        pios_can_dev_1 = dev;
    } else {
        pios_can_dev_2 = dev;
    }

    NVIC_Init((NVIC_InitTypeDef *)&cfg->rx_irq.init);
    CAN_ITConfig(cfg->regs, CAN_IT_FMP0, ENABLE);

    *can_id = (uint32_t)dev;
    return 0;
}

int32_t PIOS_CAN_Send(uint32_t can_id, const struct pios_can_frame *frame)
{
    struct pios_can_dev *dev = (struct pios_can_dev *)can_id;

    if (!PIOS_CAN_validate(dev) || !frame || frame->dlc > 8) {
        return -1;
    }
    CanTxMsg msg;
    msg.StdId = frame->ext ? 0 : (frame->id & 0x7FF);
    msg.ExtId = frame->ext ? (frame->id & 0x1FFFFFFF) : 0;
    msg.IDE   = frame->ext ? CAN_Id_Extended : CAN_Id_Standard;
    msg.RTR   = CAN_RTR_Data;
    msg.DLC   = frame->dlc;
    memcpy(msg.Data, frame->data, 8);
    if (CAN_Transmit(dev->cfg->regs, &msg) == CAN_TxStatus_NoMailBox) {
        dev->stats.tx_dropped++;
        return -1;
    }
    dev->stats.tx_frames++;
    return 0;
}

bool PIOS_CAN_Receive(uint32_t can_id, struct pios_can_frame *frame, uint32_t timeout_ms)
{
    struct pios_can_dev *dev = (struct pios_can_dev *)can_id;

    if (!PIOS_CAN_validate(dev) || !frame) {
        return false;
    }
    return xQueueReceive(dev->rx_queue, frame, timeout_ms / portTICK_RATE_MS) == pdTRUE;
}

void PIOS_CAN_GetStats(uint32_t can_id, struct pios_can_stats *stats)
{
    struct pios_can_dev *dev = (struct pios_can_dev *)can_id;

    if (!PIOS_CAN_validate(dev) || !stats) {
        return;
    }
    dev->stats.tx_errors = CAN_GetLSBTransmitErrorCounter(dev->cfg->regs);
    dev->stats.rx_errors = CAN_GetReceiveErrorCounter(dev->cfg->regs);
    dev->stats.bus_off   = CAN_GetFlagStatus(dev->cfg->regs, CAN_FLAG_BOF) == SET;
    *stats = dev->stats;
}

static void PIOS_CAN_rx_irq_handler(struct pios_can_dev *dev)
{
    if (!PIOS_CAN_validate(dev)) {
        return;
    }
    BaseType_t woken = pdFALSE;
    while (CAN_MessagePending(dev->cfg->regs, CAN_FIFO0) > 0) {
        CanRxMsg msg;
        CAN_Receive(dev->cfg->regs, CAN_FIFO0, &msg);
        struct pios_can_frame frame;
        frame.ext = (msg.IDE == CAN_Id_Extended);
        frame.id  = frame.ext ? msg.ExtId : msg.StdId;
        frame.dlc = msg.DLC > 8 ? 8 : msg.DLC;
        memcpy(frame.data, msg.Data, 8);
        dev->stats.rx_frames++;
        if (xQueueSendToBackFromISR(dev->rx_queue, &frame, &woken) != pdTRUE) {
            dev->stats.rx_dropped++;
        }
    }
    portYIELD_FROM_ISR(woken);
}

void CAN1_RX0_IRQHandler(void)
{
    PIOS_CAN_rx_irq_handler(pios_can_dev_1);
}

void CAN2_RX0_IRQHandler(void)
{
    PIOS_CAN_rx_irq_handler(pios_can_dev_2);
}

#endif /* PIOS_INCLUDE_CAN */

/**
 * @}
 * @}
 */
