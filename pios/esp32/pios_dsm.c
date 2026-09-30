/**
 ******************************************************************************
 * @file       pios_dsm.c
 * @author     NinjaPilot, 2026
 * @brief      Spektrum DSM2/DSMX satellite receiver for the ESP32.
 *
 * A satellite is a three-wire device: 3.3V, ground, and one signal line that
 * carries plain 115200 8N1 serial. Frames are 16 bytes -- two header bytes
 * then seven 16-bit channel words -- and arrive every 11ms or 22ms depending
 * on the mode the receiver was bound in. Frame boundaries are found from the
 * gap between bursts, not from any sync pattern, because there isn't one.
 *
 * The same wire is also how the flight controller puts the satellite INTO
 * bind mode: drive it as an output and emit a train of short low pulses
 * shortly after the satellite powers up. The pulse COUNT selects the
 * protocol, which is why it is a named constant below rather than a
 * magic number.
 *
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

#if defined(PIOS_INCLUDE_DSM) && defined(PIOS_INCLUDE_RCVR)

#include "driver/uart.h"
#include "driver/gpio.h"
#include <pios_rcvr_priv.h>

#define DSM_FRAME_BYTES       16
#define DSM_CHANNELS_IN_FRAME 7
/* Bit 15 set on any word after the first means the frame is not ours. */
#define DSM_2ND_FRAME_MASK    0x8000
/* Two missed 22ms frames is a lost link, not a hiccup. */
#define DSM_STALE_TIMEOUT_MS  200
#define DSM_TASK_STACK_WORDS  768
#define DSM_TASK_PRIORITY     (tskIDLE_PRIORITY + 4)
#define DSM_UART_RX_BUF       256

struct dsm_dev {
    const struct pios_esp32_dsm_cfg *cfg;
    uint16_t channels[PIOS_DSM_NUM_INPUTS];
    uint32_t last_frame_ms;
    uint32_t frames;
    uint32_t bytes;      /* diagnostic: raw bytes seen on the UART */
    /* 10-bit (DSM2 1024) or 11-bit (2048). The receiver does not announce
     * which, so it is inferred from the data -- see dsm_unroll(). */
    uint8_t  resolution;
    bool     bind_attempted;
    bool     in_use;
};

static struct dsm_dev dsm;

static uint32_t dsm_now_ms(void)
{
    return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

static int32_t dsm_uart_start(const struct pios_esp32_dsm_cfg *cfg)
{
    const uart_config_t uc = {
        .baud_rate  = 115200,
        .data_bits  = UART_DATA_8_BITS,
        .parity     = UART_PARITY_DISABLE,
        .stop_bits  = UART_STOP_BITS_1,
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    if (uart_driver_install(cfg->port, DSM_UART_RX_BUF, 0, 0, NULL, 0) != ESP_OK) {
        return -1;
    }
    if (uart_param_config(cfg->port, &uc) != ESP_OK) {
        return -1;
    }
    /* Receive only. The satellite never listens to us over the UART -- the
     * only thing we ever transmit on this wire is the bind pulse train, and
     * that is done with the UART detached. */
    if (uart_set_pin(cfg->port, UART_PIN_NO_CHANGE, cfg->rx_pin,
                     UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) != ESP_OK) {
        return -1;
    }
    return 0;
}

/*
 * Put the satellite into bind mode.
 *
 * The satellite only listens for this shortly after IT powers up, which on
 * this board is the same moment the flight controller does -- so this has to
 * happen early, and it is why the listen window before it is short.
 *
 * The pulse count selects the protocol the satellite will ask the transmitter
 * for. Getting it wrong binds at the wrong frame rate or not at all, so the
 * choice lives in pios_esp32_dsm_cfg with the reasoning next to it.
 */
static void dsm_send_bind_pulses(const struct pios_esp32_dsm_cfg *cfg)
{
    /* The UART owns this pin through the GPIO matrix; take it back before
     * driving it by hand, and give it back afterwards. */
    uart_driver_delete(cfg->port);

    gpio_config_t io = {
        .intr_type    = GPIO_INTR_DISABLE,
        .mode         = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << cfg->rx_pin,
        .pull_up_en   = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
    };
    gpio_config(&io);

    /* Idle high, then the pulse train: 120us low, 120us high, N times. */
    gpio_set_level(cfg->rx_pin, 1);
    PIOS_DELAY_WaitmS(2);

    for (uint8_t i = 0; i < cfg->bind_pulses; i++) {
        gpio_set_level(cfg->rx_pin, 0);
        PIOS_DELAY_WaituS(120);
        gpio_set_level(cfg->rx_pin, 1);
        PIOS_DELAY_WaituS(120);
    }

    /* Release the pin and go back to listening. */
    gpio_reset_pin(cfg->rx_pin);
    (void)dsm_uart_start(cfg);
}

/*
 * Decode one 16-byte frame into channel values.
 *
 * Channel words are {channel number, value} packed together, with the split
 * depending on whether the link is 10- or 11-bit. Nothing in the frame says
 * which, so it is detected from the data: a repeated channel number means we
 * are reading one bit too far left, and the 0x55 pattern means the opposite.
 * Same approach as the STM32 driver, so both behave identically on the wire.
 *
 * \return 0 on success, -1 if the frame did not decode
 */
static int dsm_unroll(const uint8_t *frame, uint8_t depth)
{
    uint32_t seen = 0;
    uint16_t mask = (dsm.resolution == 10) ? 0x03ff : 0x07ff;
    const uint8_t *s = &frame[2];

    /* The retry below flips resolution and re-runs; one flip is legitimate,
     * a second means the frame is simply bad. */
    if (depth > 1) {
        return -1;
    }

    for (int i = 0; i < DSM_CHANNELS_IN_FRAME; i++) {
        uint16_t word = ((uint16_t)s[0] << 8) | s[1];
        uint8_t  ch;

        s += 2;

        if (word == 0xffff) {
            continue;   /* empty slot */
        }
        if ((i > 0) && (word & DSM_2ND_FRAME_MASK)) {
            return -1;  /* not our frame */
        }

        ch = (word >> dsm.resolution) & 0x0f;
        if (ch >= PIOS_DSM_NUM_INPUTS) {
            continue;
        }
        if (seen & (1u << ch)) {
            /* Duplicate channel: we are decoding 10-bit data as 11-bit. */
            if (dsm.cfg->resolution) {
                return -1;      /* forced: drop the bad frame, keep the setting */
            }
            dsm.resolution = 10;
            return dsm_unroll(frame, depth + 1);
        }
        if ((seen & 0xff) == 0x55) {
            /* This pattern only appears when 11-bit data is read as 10. */
            if (dsm.cfg->resolution) {
                return -1;
            }
            dsm.resolution = 11;
            return dsm_unroll(frame, depth + 1);
        }

        dsm.channels[ch] = word & mask;
        seen |= (1u << ch);
    }
    return 0;
}

static void dsm_task(__attribute__((unused)) void *arg)
{
    const struct pios_esp32_dsm_cfg *cfg = dsm.cfg;
    uint8_t frame[DSM_FRAME_BYTES];
    uint8_t have = 0;
    uint32_t started = dsm_now_ms();

    /* BIND FIRMWARE (bind_pulses != 0).
     *
     * Spektrum's Remote Receiver Interfacing spec: the bind pulses must
     * arrive within 200 ms of the SATELLITE's power-up. This task starts
     * seconds after the board's power-up -- bootloader, WiFi, sensors and
     * the rest of PIOS_Board_Init() all come first -- so the one-shot
     * attempt below, 250 ms after the task starts, never once made the
     * window. It cannot, from application code.
     *
     * The window is relative to the satellite's own power, so turn the
     * problem round: for the first 30 s after this task starts, send the
     * pulse train every 80 ms (two full trains inside any 200 ms window),
     * and the operator plugs the satellite in -- or applies its 3.3 V --
     * AFTER the board is up. The red LED blinks while trains are going
     * out. The pin is open-drain between pulses so it never fights the
     * satellite's own data line. UART comes up afterwards as normal. */
    if (cfg->bind_pulses) {
        printf("[DSM] BIND FIRMWARE: pulsing IO%d every 80 ms for 30 s -- "
               "connect the satellite's power NOW (red LED blinks meanwhile)\n",
               (int)cfg->rx_pin);
        uart_driver_delete(cfg->port);
        gpio_config_t io = {
            .intr_type    = GPIO_INTR_DISABLE,
            .mode         = GPIO_MODE_OUTPUT_OD,
            .pin_bit_mask = 1ULL << cfg->rx_pin,
            .pull_up_en   = GPIO_PULLUP_ENABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
        };
        gpio_config(&io);
        gpio_set_level(cfg->rx_pin, 1);
        uint32_t t0 = dsm_now_ms();
        uint32_t trains = 0;
        while ((dsm_now_ms() - t0) < 30000) {
            for (uint8_t i = 0; i < cfg->bind_pulses; i++) {
                gpio_set_level(cfg->rx_pin, 0);
                PIOS_DELAY_WaituS(120);
                gpio_set_level(cfg->rx_pin, 1);
                PIOS_DELAY_WaituS(120);
            }
            trains++;
#if defined(PIOS_INCLUDE_LED) && defined(PIOS_LED_ARMED)
            if ((trains & 1) == 0) {
                PIOS_LED_Toggle(PIOS_LED_ARMED);
            }
#endif
            vTaskDelay(pdMS_TO_TICKS(80));
        }
#if defined(PIOS_INCLUDE_LED) && defined(PIOS_LED_ARMED)
        PIOS_LED_Off(PIOS_LED_ARMED);
#endif
        gpio_reset_pin(cfg->rx_pin);
        (void)dsm_uart_start(cfg);
        dsm.bind_attempted = true;   /* the one-shot below stays off */
        started = dsm_now_ms();
        printf("[DSM] bind window over (%lu trains sent); listening for frames\n",
               (unsigned long)trains);
    }

    for (;;) {
        int got = uart_read_bytes(cfg->port, &frame[have],
                                  DSM_FRAME_BYTES - have, pdMS_TO_TICKS(4));

        if (got > 0) {
            dsm.bytes += (uint32_t)got;
            have += (uint8_t)got;
            if (have == DSM_FRAME_BYTES) {
                if (dsm_unroll(frame, 0) == 0) {
                    dsm.last_frame_ms = dsm_now_ms();
                    dsm.frames++;
                }
                have = 0;
            }
            continue;
        }

        /* Nothing for 4ms: that is the gap between frames, so whatever we
         * were holding was a fragment. Drop it and resync. */
        have = 0;

        /* Auto-bind. A satellite that is already bound starts talking within
         * a few frame times of power-up, so silence for the whole listen
         * window means it is not bound to anything -- with one important
         * exception: a bound satellite is equally silent if the transmitter
         * is simply switched off. Powering the board up with the TX off will
         * therefore drop it into bind mode. Set bind_pulses to 0 to disable. */
        if (!dsm.bind_attempted && cfg->bind_pulses && dsm.frames == 0 &&
            (dsm_now_ms() - started) > cfg->listen_ms) {
            dsm.bind_attempted = true;
            dsm_send_bind_pulses(cfg);
        }
    }
}

int32_t PIOS_ESP32_DSM_Init(uint32_t *dsm_id, const struct pios_esp32_dsm_cfg *cfg)
{
    PIOS_Assert(dsm_id);
    PIOS_Assert(cfg);

    if (dsm.in_use) {
        return -1;
    }

    dsm.cfg        = cfg;
    dsm.resolution = cfg->resolution ? cfg->resolution : 11;

    for (uint8_t i = 0; i < PIOS_DSM_NUM_INPUTS; i++) {
        dsm.channels[i] = PIOS_RCVR_TIMEOUT;
    }

    if (dsm_uart_start(cfg) != 0) {
        return -1;
    }

    if (xTaskCreate(dsm_task, "PIOS_DSM", DSM_TASK_STACK_WORDS, NULL,
                    DSM_TASK_PRIORITY, NULL) != pdPASS) {
        uart_driver_delete(cfg->port);
        return -1;
    }

    dsm.in_use = true;
    *dsm_id    = 1;
    return 0;
}

/* Frames decoded so far, and whether a bind was attempted this boot. Read
 * from the init task -- this path deliberately does no printing itself. */
void PIOS_ESP32_DSM_GetState(uint32_t *frames, bool *bind_attempted)
{
    /* dsm.bytes counts raw UART bytes and dsm.frames counts frames that
     * decoded. The pair separates the three failure modes that otherwise look
     * identical from outside: no bytes at all is wiring, power or pin; bytes
     * without frames is baud, framing or resync; both climbing means the
     * transport is fine and the problem is downstream. Worth having on a board
     * whose console is not reachable over its USB connector. */
    if (frames) {
        *frames = dsm.frames;
    }
    if (bind_attempted) {
        *bind_attempted = dsm.bind_attempted;
    }
}

/* ---------------------------------------------------------------------- *
 * pios_rcvr_driver implementation
 * ---------------------------------------------------------------------- */

static void PIOS_ESP32_DSM_RcvrInit(__attribute__((unused)) uint32_t id)
{}

static int32_t PIOS_ESP32_DSM_RcvrRead(__attribute__((unused)) uint32_t id,
                                       uint8_t channel)
{
    if (!dsm.in_use) {
        return PIOS_RCVR_INVALID;
    }
    if (channel >= PIOS_DSM_NUM_INPUTS) {
        return PIOS_RCVR_INVALID;
    }
    if (dsm.frames == 0) {
        return PIOS_RCVR_TIMEOUT;
    }
    if ((dsm_now_ms() - dsm.last_frame_ms) > DSM_STALE_TIMEOUT_MS) {
        /* Report the failure rather than the last good value --
         * ManualControl has to be able to tell the difference. */
        return PIOS_RCVR_TIMEOUT;
    }

    return (int32_t)dsm.channels[channel];
}

static xSemaphoreHandle PIOS_ESP32_DSM_RcvrGetSemaphore(__attribute__((unused)) uint32_t id,
                                                        __attribute__((unused)) uint8_t channel)
{
    return NULL;
}

const struct pios_rcvr_driver pios_esp32_dsm_rcvr_driver = {
    .init          = PIOS_ESP32_DSM_RcvrInit,
    .read          = PIOS_ESP32_DSM_RcvrRead,
    .get_semaphore = PIOS_ESP32_DSM_RcvrGetSemaphore,
};

#endif /* PIOS_INCLUDE_DSM && PIOS_INCLUDE_RCVR */
