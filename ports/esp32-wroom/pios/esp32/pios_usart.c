/**
 ******************************************************************************
 * @file       pios_usart.c
 * @author     NinjaPilot, 2026
 * @brief      ESP32 UART driver exposed as a PiOS COM device.
 *
 * The STM32 backend does this a byte at a time out of an ISR. IDF gives us a
 * driver with its own ring buffers and event queue, so instead each port gets
 * a small RX task that blocks on the UART and hands whole blocks up to the COM
 * layer. That keeps every byte of UART work in task context.
 *
 * Keeping work out of ISRs is a habit worth having on this part specifically:
 * the Xtensa FPU is not usable from an interrupt handler (IDF does not
 * save/restore FPU context there), so any ISR that drifts into floating point
 * is a latent fault. See the note in the port README about
 * PIOS_MPU6000_HandleData().
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

#if defined(PIOS_INCLUDE_USART) && defined(PIOS_INCLUDE_COM)

#include "driver/uart.h"
#include "freertos/task.h"

#define PIOS_ESP32_USART_MAX_PORTS  3
#define USART_RX_CHUNK              64
#define USART_TX_CHUNK              64
#define USART_RX_TASK_STACK         2048
#define USART_RX_TASK_PRIO          (configMAX_PRIORITIES - 6)

struct pios_esp32_usart_dev {
    const struct pios_esp32_usart_cfg *cfg;
    pios_com_callback rx_in_cb;
    /* RX accounting, for the once-a-second report in usart_rx_task(). */
    uint32_t rx_bytes;
    uint32_t rx_dropped;
    uint32_t rx_reported;
    uint32_t rx_report_ms;
    uint32_t rx_in_context;
    pios_com_callback tx_out_cb;
    uint32_t tx_out_context;
    TaskHandle_t rx_task;
    bool in_use;
};

static struct pios_esp32_usart_dev usart_devs[PIOS_ESP32_USART_MAX_PORTS];

/* ---------------------------------------------------------------------- */

static struct pios_esp32_usart_dev *usart_dev_from_id(uint32_t id)
{
    if (id == 0 || id > PIOS_ESP32_USART_MAX_PORTS) {
        return NULL;
    }
    struct pios_esp32_usart_dev *dev = &usart_devs[id - 1];

    return dev->in_use ? dev : NULL;
}

static void usart_rx_task(void *arg)
{
    struct pios_esp32_usart_dev *dev = (struct pios_esp32_usart_dev *)arg;
    uint8_t buf[USART_RX_CHUNK];

    for (;;) {
        int len = uart_read_bytes(dev->cfg->port, buf, sizeof(buf),
                                  pdMS_TO_TICKS(10));
        if (len <= 0) {
            continue;
        }
        if (!dev->rx_in_cb) {
            continue;
        }

        bool woken = false;
        uint16_t headroom = 0;
        uint16_t consumed = (dev->rx_in_cb)(dev->rx_in_context, buf,
                                            (uint16_t)len, &headroom, &woken);

        dev->rx_bytes += (uint32_t)len;
        dev->rx_dropped += (uint32_t)(len - consumed);

        /* COM layer's receive buffer is full. Dropping is the honest outcome
         * -- there is nowhere to push back to -- but say so, because silent RX
         * loss is miserable to diagnose from the far end.
         *
         * Rate limited to one line a second, and reporting totals plus the
         * COM fifo headroom rather than a bare per-chunk count: an unrated
         * print of every dropped chunk is itself enough console traffic to
         * change the timing of the thing being diagnosed, and the headroom is
         * what distinguishes "nobody is reading this port" (stuck at 0) from
         * "a reader that briefly fell behind" (recovers). */
        if (dev->rx_bytes != dev->rx_reported) {
            uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;
            if (now - dev->rx_report_ms >= 1000) {
                printf("[PIOS] USART%d rx: %lu bytes, %lu dropped, fifo headroom %u\n",
                       (int)dev->cfg->port,
                       (unsigned long)dev->rx_bytes,
                       (unsigned long)dev->rx_dropped,
                       (unsigned)headroom);
#ifdef PIOS_USART_RX_DUMP
                /* Show the chunk itself. Whether the bytes are clean ASCII
                 * sentences or framing hash is the one thing the counters
                 * above cannot tell you, and it is the difference between a
                 * parser problem and a baud problem. */
                printf("[PIOS] USART%d raw: ", (int)dev->cfg->port);
                for (int i = 0; i < len && i < 96; i++) {
                    putchar((buf[i] >= 32 && buf[i] < 127) ? buf[i]
                            : (buf[i] == '\r' || buf[i] == '\n') ? '~' : '.');
                }
                printf("\n");
#endif
                dev->rx_report_ms = now;
                dev->rx_reported = dev->rx_bytes;
            }
        }
    }
}

/* ---------------------------------------------------------------------- */

int32_t PIOS_ESP32_USART_Init(uint32_t *usart_id,
                              const struct pios_esp32_usart_cfg *cfg)
{
    PIOS_Assert(usart_id);
    PIOS_Assert(cfg);

    struct pios_esp32_usart_dev *dev = NULL;
    uint32_t slot = 0;

    for (uint32_t i = 0; i < PIOS_ESP32_USART_MAX_PORTS; i++) {
        if (!usart_devs[i].in_use) {
            dev  = &usart_devs[i];
            slot = i + 1;
            break;
        }
    }
    if (!dev) {
        return -1;
    }

    const uart_config_t uart_cfg = {
        .baud_rate  = (int)cfg->init_baud,
        .data_bits  = UART_DATA_8_BITS,
        .parity     = UART_PARITY_DISABLE,
        .stop_bits  = UART_STOP_BITS_1,
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
        /* Pin the source clock explicitly rather than taking
         * UART_SCLK_DEFAULT. UART0 has already been brought up by IDF's
         * console before we get here, and inheriting whatever clock it left
         * selected made a requested 57600 come out as 38400 on the wire --
         * exactly the 1.5x you get from computing a divisor against the
         * wrong reference. APB is 80MHz and is what the console uses. */
        .source_clk = UART_SCLK_APB,
    };

    if (uart_driver_install(cfg->port, cfg->rx_buffer_size,
                            cfg->tx_buffer_size, 0, NULL, 0) != ESP_OK) {
        return -1;
    }
    if (uart_param_config(cfg->port, &uart_cfg) != ESP_OK) {
        goto fail;
    }
    if (uart_set_pin(cfg->port, cfg->tx_pin, cfg->rx_pin,
                     UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) != ESP_OK) {
        goto fail;
    }
    /* Hardware RX inversion -- this is what lets SBUS work without an
     * external inverter. */
    if (cfg->invert_rx) {
        if (uart_set_line_inverse(cfg->port, UART_SIGNAL_RXD_INV) != ESP_OK) {
            goto fail;
        }
    }

    dev->cfg    = cfg;
    dev->in_use = true;

    if (xTaskCreate(usart_rx_task, "PIOS_UART_RX", USART_RX_TASK_STACK, dev,
                    USART_RX_TASK_PRIO, &dev->rx_task) != pdPASS) {
        dev->in_use = false;
        goto fail;
    }

    *usart_id = slot;
    return 0;

fail:
    uart_driver_delete(cfg->port);
    return -1;
}

/* ---------------------------------------------------------------------- *
 * pios_com_driver implementation
 * ---------------------------------------------------------------------- */

static void PIOS_ESP32_USART_ComInit(__attribute__((unused)) uint32_t id)
{
    /* Everything happens in PIOS_ESP32_USART_Init(). */
}

static void PIOS_ESP32_USART_SetBaud(uint32_t id, uint32_t baud)
{
    struct pios_esp32_usart_dev *dev = usart_dev_from_id(id);

    if (!dev) {
        return;
    }
    uart_set_baudrate(dev->cfg->port, (int)baud);

    uint32_t actual = 0;
    if (uart_get_baudrate(dev->cfg->port, &actual) == ESP_OK && actual != baud) {
        printf("[PIOS] USART%d: asked for %lu baud, got %lu\n",
               (int)dev->cfg->port, (unsigned long)baud, (unsigned long)actual);
    }
}

static void PIOS_ESP32_USART_TxStart(uint32_t id,
                                     __attribute__((unused)) uint16_t tx_bytes_avail)
{
    struct pios_esp32_usart_dev *dev = usart_dev_from_id(id);

    if (!dev || !dev->tx_out_cb) {
        return;
    }

    uint8_t buf[USART_TX_CHUNK];

    for (;;) {
        bool woken = false;
        uint16_t len = (dev->tx_out_cb)(dev->tx_out_context, buf,
                                        sizeof(buf), NULL, &woken);
        if (len == 0) {
            break;
        }
        /* uart_write_bytes copies into the IDF TX ring buffer and returns
         * once it has taken everything, so this does not block on the wire
         * unless the ring is full. */
        uart_write_bytes(dev->cfg->port, buf, len);

        if (len < sizeof(buf)) {
            break;
        }
    }
}

static void PIOS_ESP32_USART_RxStart(__attribute__((unused)) uint32_t id,
                                     __attribute__((unused)) uint16_t rx_bytes_avail)
{
    /* The RX task is always running; there is no interrupt to unmask. */
}

static void PIOS_ESP32_USART_BindRxCb(uint32_t id, pios_com_callback rx_in_cb,
                                      uint32_t context)
{
    struct pios_esp32_usart_dev *dev = usart_dev_from_id(id);

    if (!dev) {
        return;
    }
    dev->rx_in_context = context;
    dev->rx_in_cb = rx_in_cb;
}

static void PIOS_ESP32_USART_BindTxCb(uint32_t id, pios_com_callback tx_out_cb,
                                      uint32_t context)
{
    struct pios_esp32_usart_dev *dev = usart_dev_from_id(id);

    if (!dev) {
        return;
    }
    dev->tx_out_context = context;
    dev->tx_out_cb = tx_out_cb;
}

static bool PIOS_ESP32_USART_Available(uint32_t id)
{
    return usart_dev_from_id(id) != NULL;
}

const struct pios_com_driver pios_esp32_usart_com_driver = {
    .init        = PIOS_ESP32_USART_ComInit,
    .set_baud    = PIOS_ESP32_USART_SetBaud,
    .tx_start    = PIOS_ESP32_USART_TxStart,
    .rx_start    = PIOS_ESP32_USART_RxStart,
    .bind_rx_cb  = PIOS_ESP32_USART_BindRxCb,
    .bind_tx_cb  = PIOS_ESP32_USART_BindTxCb,
    .available   = PIOS_ESP32_USART_Available,
};

#endif /* PIOS_INCLUDE_USART && PIOS_INCLUDE_COM */
