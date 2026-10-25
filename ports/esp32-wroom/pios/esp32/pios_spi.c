/**
 ******************************************************************************
 * @file       pios_spi.c
 * @author     NinjaPilot, 2026
 * @brief      ESP32 SPI master, presented through the PiOS SPI interface.
 *
 * Two things about this mapping are worth knowing before you touch it.
 *
 * 1. CS IS DRIVEN AS A PLAIN GPIO, not by the SPI peripheral. PiOS asserts and
 *    releases chip select itself via PIOS_SPI_RC_PinSet() and holds it across
 *    multiple transfers (see PIOS_MPU6000_ReadSensor), which the IDF's
 *    automatic CS cannot express. So every device is registered with
 *    .spics_io_num = -1 and we toggle the pin ourselves.
 *
 * 2. THE "ISR" VARIANTS ARE NOT ISR-SAFE HERE, and cannot be. IDF's
 *    spi_device_polling_transmit() must not be called from an interrupt
 *    handler. The STM32 backend gets away with PIOS_SPI_ClaimBusISR() because
 *    the MPU6000 data-ready path runs in EXTI context there; on this target
 *    that path is deferred to a task instead (see pios_exti.c), so by the time
 *    anything calls these we are in task context and the plain implementation
 *    is correct. The *ISR entry points are kept only so the shared MPU6000
 *    driver compiles unmodified.
 *
 *    If you ever wire a genuine ISR to these, it will fail -- deliberately
 *    loudly, not subtly.
 *
 * Bus clock is per-device on the ESP32, not a prescaler on a shared bus, so
 * each slave is registered twice (a "low" handle used during device probe and
 * a "fast" handle for streaming) and PIOS_SPI_SetClockSpeed() picks between
 * them. Re-adding devices at runtime would be the alternative and is worse.
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

#ifdef PIOS_INCLUDE_SPI

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "freertos/semphr.h"

#define PIOS_ESP32_SPI_MAX_BUSES 2
#define SPI_MAX_XFER             64   /* matches the largest MPU6000 burst */

struct pios_esp32_spi_dev {
    const struct pios_esp32_spi_cfg *cfg;
    spi_device_handle_t slow[PIOS_ESP32_SPI_MAX_SLAVES];
    spi_device_handle_t fast[PIOS_ESP32_SPI_MAX_SLAVES];
    /* Which handle each slave is currently using. */
    bool use_fast[PIOS_ESP32_SPI_MAX_SLAVES];
    /* PiOS's bus lock. Recursive claim is not permitted by the interface,
     * so a binary semaphore is the right primitive. */
    SemaphoreHandle_t lock;
    /* DMA-capable bounce buffers. Per-bus, not shared: PiOS hands us stack
     * memory and IDF needs word-aligned DMA-safe buffers, but two buses can
     * be mid-transfer at once so a single global pair would race. */
    WORD_ALIGNED_ATTR uint8_t txbuf[SPI_MAX_XFER];
    WORD_ALIGNED_ATTR uint8_t rxbuf[SPI_MAX_XFER];
    int8_t  active_slave;   /* -1 when CS is not asserted anywhere */
    bool    in_use;
};

static struct pios_esp32_spi_dev spi_devs[PIOS_ESP32_SPI_MAX_BUSES];

static struct pios_esp32_spi_dev *spi_dev_from_id(uint32_t id)
{
    if (id == 0 || id > PIOS_ESP32_SPI_MAX_BUSES) {
        return NULL;
    }
    struct pios_esp32_spi_dev *dev = &spi_devs[id - 1];

    return dev->in_use ? dev : NULL;
}

/* The handle a transfer should go out on: the active slave's, at whichever
 * speed was last selected. */
static spi_device_handle_t spi_active_handle(struct pios_esp32_spi_dev *dev)
{
    if (dev->active_slave < 0) {
        return NULL;
    }
    uint8_t s = (uint8_t)dev->active_slave;

    return dev->use_fast[s] ? dev->fast[s] : dev->slow[s];
}

/* ---------------------------------------------------------------------- */

int32_t PIOS_ESP32_SPI_Init(uint32_t *spi_id, const struct pios_esp32_spi_cfg *cfg)
{
    PIOS_Assert(spi_id);
    PIOS_Assert(cfg);
    PIOS_Assert(cfg->num_slaves <= PIOS_ESP32_SPI_MAX_SLAVES);

    struct pios_esp32_spi_dev *dev = NULL;
    uint32_t slot = 0;

    for (uint32_t i = 0; i < PIOS_ESP32_SPI_MAX_BUSES; i++) {
        if (!spi_devs[i].in_use) {
            dev  = &spi_devs[i];
            slot = i + 1;
            break;
        }
    }
    if (!dev) {
        return -1;
    }

    const spi_bus_config_t bus = {
        .mosi_io_num     = cfg->mosi_pin,
        .miso_io_num     = cfg->miso_pin,
        .sclk_io_num     = cfg->sclk_pin,
        .quadwp_io_num   = -1,
        .quadhd_io_num   = -1,
        .max_transfer_sz = SPI_MAX_XFER,
    };

    if (spi_bus_initialize(cfg->host, &bus, cfg->dma_channel) != ESP_OK) {
        return -1;
    }

    for (uint8_t s = 0; s < cfg->num_slaves; s++) {
        const struct pios_esp32_spi_slave *sl = &cfg->slaves[s];

        /* CS as a normal output, deasserted (high). */
        gpio_config_t io = {
            .intr_type    = GPIO_INTR_DISABLE,
            .mode         = GPIO_MODE_OUTPUT,
            .pin_bit_mask = 1ULL << sl->cs_pin,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .pull_up_en   = GPIO_PULLUP_DISABLE,
        };
        if (gpio_config(&io) != ESP_OK) {
            return -1;
        }
        gpio_set_level(sl->cs_pin, 1);

        spi_device_interface_config_t devcfg = {
            .command_bits   = 0,
            .address_bits   = 0,
            .dummy_bits     = 0,
            .mode           = sl->mode,
            .spics_io_num   = -1,       /* see file header: PiOS owns CS */
            .queue_size     = 1,
            .flags          = SPI_DEVICE_NO_DUMMY,
        };

        devcfg.clock_speed_hz = sl->clock_speed_hz;
        if (spi_bus_add_device(cfg->host, &devcfg, &dev->slow[s]) != ESP_OK) {
            printf("[SPI] slow add_device FAILED\n");
            return -1;
        }
        devcfg.clock_speed_hz = sl->fast_speed_hz;
        if (spi_bus_add_device(cfg->host, &devcfg, &dev->fast[s]) != ESP_OK) {
            printf("[SPI] fast add_device FAILED\n");
            return -1;
        }
        dev->use_fast[s] = false;
    }

    dev->lock = xSemaphoreCreateBinary();
    if (!dev->lock) {
        return -1;
    }
    xSemaphoreGive(dev->lock);

    dev->cfg          = cfg;
    dev->active_slave = -1;
    dev->in_use       = true;

    *spi_id = slot;
    return 0;
}

/* ---------------------------------------------------------------------- */

int32_t PIOS_SPI_ClaimBus(uint32_t spi_id)
{
    struct pios_esp32_spi_dev *dev = spi_dev_from_id(spi_id);

    if (!dev) {
        return -1;
    }
    if (xSemaphoreTake(dev->lock, portMAX_DELAY) != pdTRUE) {
        return -1;
    }
    return 0;
}

int32_t PIOS_SPI_ClaimBusISR(uint32_t spi_id, __attribute__((unused)) bool *woken)
{
    /* See the file header. This is reached from a task, never a real ISR. */
    return PIOS_SPI_ClaimBus(spi_id);
}

int32_t PIOS_SPI_ReleaseBus(uint32_t spi_id)
{
    struct pios_esp32_spi_dev *dev = spi_dev_from_id(spi_id);

    if (!dev) {
        return -1;
    }
    xSemaphoreGive(dev->lock);
    return 0;
}

int32_t PIOS_SPI_ReleaseBusISR(uint32_t spi_id, __attribute__((unused)) bool *woken)
{
    return PIOS_SPI_ReleaseBus(spi_id);
}

int32_t PIOS_SPI_RC_PinSet(uint32_t spi_id, uint32_t slave_id, uint8_t pin_value)
{
    struct pios_esp32_spi_dev *dev = spi_dev_from_id(spi_id);

    if (!dev || slave_id >= dev->cfg->num_slaves) {
        return -1;
    }

    gpio_set_level(dev->cfg->slaves[slave_id].cs_pin, pin_value ? 1 : 0);

    /* pin_value == 0 means "assert" (CS is active low). Track which slave
     * owns the bus so transfers pick the right device handle. */
    dev->active_slave = pin_value ? -1 : (int8_t)slave_id;
    return 0;
}

int32_t PIOS_SPI_SetClockSpeed(uint32_t spi_id, SPIPrescalerTypeDef spi_prescaler)
{
    struct pios_esp32_spi_dev *dev = spi_dev_from_id(spi_id);

    if (!dev || dev->active_slave < 0) {
        return -1;
    }

    /* PiOS talks in STM32 APB prescalers. All the callers actually want is
     * "slow for configuration, fast for streaming", so collapse it to that:
     * anything divided by 16 or more is the slow handle. */
    dev->use_fast[dev->active_slave] = (spi_prescaler < PIOS_SPI_PRESCALER_16);
    return 0;
}

void PIOS_SPI_SetPrescalar(uint32_t spi_id, uint32_t prescalar)
{
    (void)PIOS_SPI_SetClockSpeed(spi_id, (SPIPrescalerTypeDef)prescalar);
}

int32_t PIOS_SPI_TransferBlock(uint32_t spi_id, const uint8_t *send_buffer,
                               uint8_t *receive_buffer, uint16_t len,
                               void *callback)
{
    struct pios_esp32_spi_dev *dev = spi_dev_from_id(spi_id);

    if (!dev || len == 0 || len > SPI_MAX_XFER) {
        return -1;
    }
    /* PiOS's async/DMA-completion callback form is not implemented; every
     * caller in this tree passes NULL. Refuse rather than silently running
     * the transfer synchronously and never calling back. */
    if (callback != NULL) {
        return -1;
    }

    spi_device_handle_t handle = spi_active_handle(dev);

    if (!handle) {
        return -1;
    }

    /* Bounce through this bus's own DMA-safe buffers (see struct). The
     * caller holds the bus claim, so no further locking is needed. */
    if (send_buffer) {
        memcpy(dev->txbuf, send_buffer, len);
    } else {
        memset(dev->txbuf, 0, len);
    }

    spi_transaction_t t = {
        .length    = (size_t)len * 8,
        .tx_buffer = dev->txbuf,
        .rx_buffer = receive_buffer ? dev->rxbuf : NULL,
    };

    if (spi_device_polling_transmit(handle, &t) != ESP_OK) {
        return -1;
    }

    if (receive_buffer) {
        memcpy(receive_buffer, dev->rxbuf, len);
    }
    return 0;
}

int32_t PIOS_SPI_TransferByte(uint32_t spi_id, uint8_t b)
{
    uint8_t rx = 0;

    if (PIOS_SPI_TransferBlock(spi_id, &b, &rx, 1, NULL) != 0) {
        return -1;
    }
    return (int32_t)rx;
}

int32_t PIOS_SPI_Busy(uint32_t spi_id)
{
    struct pios_esp32_spi_dev *dev = spi_dev_from_id(spi_id);

    if (!dev) {
        return -1;
    }
    /* Transfers are synchronous, so the bus is busy exactly when someone
     * holds the claim. */
    return uxSemaphoreGetCount(dev->lock) == 0 ? 1 : 0;
}

void PIOS_SPI_IRQ_Handler(__attribute__((unused)) uint32_t spi_id)
{
    /* No interrupt-driven transfer path on this backend. */
}

#endif /* PIOS_INCLUDE_SPI */
