/**
 ******************************************************************************
 * @file       pios_ppm.c
 * @author     NinjaPilot, 2026
 * @brief      PPM-sum RC input on ESP32, decoded with the RMT peripheral.
 *
 * RMT is the right tool here: it timestamps edges in hardware into a symbol
 * buffer, so a whole PPM frame arrives as one callback with exact pulse widths
 * and we never sample a GPIO in software. That is strictly better than the
 * timer-capture approach the STM32 backend uses.
 *
 * The RMT done-callback runs in ISR context, so it does nothing but copy
 * already-decoded integer widths into the channel array -- no floats, no bus
 * access. (See pios_exti.c for why that rule matters on this part.)
 *
 * Frame detection is the usual one: a gap longer than PPM_SYNC_MIN_US ends the
 * frame and the next pulse starts channel 0.
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

#if defined(PIOS_INCLUDE_PPM) && defined(PIOS_INCLUDE_RCVR)

#include "driver/rmt_rx.h"
#include "esp_attr.h"

#define PPM_IN_MAX_NUM_CHANNELS   12
#define PPM_SYNC_MIN_US           3000    /* gap that delimits a frame     */
#define PPM_PULSE_MIN_US          800     /* reject noise / glitches       */
#define PPM_PULSE_MAX_US          2200
#define PPM_STALE_TIMEOUT_MS      100     /* no frame for this long = fail */
#define PPM_RMT_RESOLUTION_HZ     1000000 /* 1 tick == 1us                 */
#define PPM_RMT_MEM_BLOCK_SYMBOLS 64

struct pios_ppm_dev {
    rmt_channel_handle_t channel;
    rmt_symbol_word_t    raw[PPM_RMT_MEM_BLOCK_SYMBOLS];
    rmt_receive_config_t rx_cfg;

    volatile uint16_t channels[PPM_IN_MAX_NUM_CHANNELS];
    volatile uint8_t  num_channels;
    volatile uint32_t last_frame_ms;
    bool in_use;
};

static struct pios_ppm_dev ppm_dev;

/* ---------------------------------------------------------------------- */

static bool IRAM_ATTR ppm_rx_done(rmt_channel_handle_t chan,
                                  const rmt_rx_done_event_data_t *edata,
                                  void *user_ctx)
{
    struct pios_ppm_dev *dev = (struct pios_ppm_dev *)user_ctx;
    uint8_t ch = 0;

    for (size_t i = 0; i < edata->num_symbols && ch < PPM_IN_MAX_NUM_CHANNELS; i++) {
        /* An RMT symbol is a level/duration pair twice over. For PPM the
         * channel value is the full period from one rising edge to the
         * next, which is duration0 + duration1. */
        uint32_t width = edata->received_symbols[i].duration0 +
                         edata->received_symbols[i].duration1;

        if (width >= PPM_SYNC_MIN_US) {
            /* A sync gap. The receive window opens at an arbitrary point in
             * the stream, so the FIRST gap we see is usually the leading one
             * with no channels before it -- skipping it is what lets the
             * frame start. Only a gap that follows real channel data marks
             * the end of a frame. */
            if (ch == 0) {
                continue;
            }
            break;
        }
        if (width >= PPM_PULSE_MIN_US && width <= PPM_PULSE_MAX_US) {
            dev->channels[ch++] = (uint16_t)width;
        }
    }

    if (ch > 0) {
        dev->num_channels  = ch;
        /* xTaskGetTickCountFromISR is the ISR-safe form; the plain one
         * asserts in an interrupt context on IDF. */
        dev->last_frame_ms = (uint32_t)(xTaskGetTickCountFromISR() * portTICK_PERIOD_MS);
    }

    /* Re-arm. Returning false means "no higher-priority task was woken". */
    rmt_receive(chan, dev->raw, sizeof(dev->raw), &dev->rx_cfg);
    return false;
}

/* ---------------------------------------------------------------------- */

int32_t PIOS_ESP32_PPM_Init(uint32_t *ppm_id, const struct pios_esp32_ppm_cfg *cfg)
{
    PIOS_Assert(ppm_id);
    PIOS_Assert(cfg);

    if (ppm_dev.in_use) {
        return -1;
    }

    rmt_rx_channel_config_t rxcfg = {
        .gpio_num          = cfg->pin,
        .clk_src           = RMT_CLK_SRC_DEFAULT,
        .resolution_hz     = PPM_RMT_RESOLUTION_HZ,
        .mem_block_symbols = PPM_RMT_MEM_BLOCK_SYMBOLS,
        .flags.with_dma    = false,
    };

    if (rmt_new_rx_channel(&rxcfg, &ppm_dev.channel) != ESP_OK) {
        return -1;
    }

    rmt_rx_event_callbacks_t cbs = { .on_recv_done = ppm_rx_done };

    if (rmt_rx_register_event_callbacks(ppm_dev.channel, &cbs, &ppm_dev) != ESP_OK) {
        return -1;
    }

    ppm_dev.rx_cfg.signal_range_min_ns = 1000;              /* 1us glitch filter */
    ppm_dev.rx_cfg.signal_range_max_ns = 12 * 1000 * 1000;  /* 12ms idle = done  */

    if (rmt_enable(ppm_dev.channel) != ESP_OK) {
        return -1;
    }
    if (rmt_receive(ppm_dev.channel, ppm_dev.raw, sizeof(ppm_dev.raw),
                    &ppm_dev.rx_cfg) != ESP_OK) {
        return -1;
    }

    ppm_dev.in_use = true;
    *ppm_id = 1;
    return 0;
}

/* ---------------------------------------------------------------------- *
 * pios_rcvr_driver implementation
 * ---------------------------------------------------------------------- */

static void PIOS_ESP32_PPM_RcvrInit(__attribute__((unused)) uint32_t id)
{}

static int32_t PIOS_ESP32_PPM_RcvrRead(__attribute__((unused)) uint32_t id,
                                       uint8_t channel)
{
    if (!ppm_dev.in_use) {
        return PIOS_RCVR_INVALID;
    }
    if (channel >= ppm_dev.num_channels) {
        return PIOS_RCVR_INVALID;
    }

    uint32_t now = (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);

    if ((now - ppm_dev.last_frame_ms) > PPM_STALE_TIMEOUT_MS) {
        /* Transmitter is gone. Report failsafe rather than the last good
         * value -- ManualControl must be able to tell the difference. */
        return PIOS_RCVR_TIMEOUT;
    }

    return (int32_t)ppm_dev.channels[channel];
}

static xSemaphoreHandle PIOS_ESP32_PPM_RcvrGetSemaphore(__attribute__((unused)) uint32_t id,
                                                        __attribute__((unused)) uint8_t channel)
{
    return NULL;
}

const struct pios_rcvr_driver pios_esp32_ppm_rcvr_driver = {
    .init          = PIOS_ESP32_PPM_RcvrInit,
    .read          = PIOS_ESP32_PPM_RcvrRead,
    .get_semaphore = PIOS_ESP32_PPM_RcvrGetSemaphore,
};

#endif /* PIOS_INCLUDE_PPM && PIOS_INCLUDE_RCVR */
