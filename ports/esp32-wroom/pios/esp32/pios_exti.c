/**
 ******************************************************************************
 * @file       pios_exti.c
 * @author     NinjaPilot, 2026
 * @brief      Deferred sensor data-ready dispatch for ESP32.
 *
 * This is the piece of the port that is genuinely different from the STM32
 * backends rather than just differently spelled, so it is worth reading before
 * changing anything on the sensor path.
 *
 * On STM32, PIOS_MPU6000_IRQHandler() runs directly in the EXTI vector: it
 * claims the SPI bus, burst-reads the sensor, scales the temperature, and
 * queues the sample, all in interrupt context. Neither half of that is legal
 * on this part:
 *
 *   - spi_device_polling_transmit() is not ISR-safe.
 *   - The Xtensa FPU is not usable in an ISR. IDF does not save or restore
 *     FPU context for interrupt handlers, and pios_mpu6000.c does float math
 *     on this exact path (the temperature conversion in
 *     PIOS_MPU6000_HandleData()). That would be a silent state corruption,
 *     not a clean fault, which is the worst kind.
 *
 * So the ISR here is one line of real work -- a task notification -- and the
 * registered "vector" runs at high priority in task context immediately
 * afterwards. Latency cost is a context switch, which at 500Hz is noise.
 *
 * The ISR itself is placed in IRAM so it stays serviceable if the flash cache
 * is ever disabled (an SPI-flash write will do that).
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

#include "driver/gpio.h"
#include "esp_attr.h"
#include "freertos/task.h"

#define EXTI_MAX_LINES 2

struct exti_line {
    const struct pios_esp32_exti_cfg *cfg;
    TaskHandle_t task;
    volatile uint32_t missed;   /* notifications lost to a slow handler */
    bool in_use;
};

static struct exti_line exti_lines[EXTI_MAX_LINES];
static bool exti_isr_service_installed;

static void IRAM_ATTR exti_gpio_isr(void *arg)
{
    struct exti_line *line = (struct exti_line *)arg;
    BaseType_t woken = pdFALSE;

    /* vTaskNotifyGiveFromISR is a counting give, so a burst is not lost
     * outright -- but the handler is expected to keep up, and if it does
     * not we want that visible rather than silently smoothed over. */
    vTaskNotifyGiveFromISR(line->task, &woken);

    if (woken == pdTRUE) {
        portYIELD_FROM_ISR();
    }
}


static void exti_task(void *arg)
{
    struct exti_line *line = (struct exti_line *)arg;

    for (;;) {
        /* Clear-on-exit so a backlog collapses to one run: the sensor
         * handler always reads the newest sample, so servicing a stale
         * notification would only cost a wasted SPI transaction. Count
         * what we collapsed so the overrun is measurable. */
        uint32_t pending = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);


        if (pending > 1) {
            line->missed += (pending - 1);
        }

        if (line->cfg->vector) {
            (void)(line->cfg->vector)();
        }
    }
}

int32_t PIOS_ESP32_EXTI_Init(const struct pios_esp32_exti_cfg *cfg)
{
    PIOS_Assert(cfg);
    PIOS_Assert(cfg->vector);

    struct exti_line *line = NULL;

    for (uint8_t i = 0; i < EXTI_MAX_LINES; i++) {
        if (!exti_lines[i].in_use) {
            line = &exti_lines[i];
            break;
        }
    }
    if (!line) {
        return -1;
    }

    line->cfg    = cfg;
    line->missed = 0;

    /* Task first: the ISR notifies it, so it must exist before the
     * interrupt is armed. */
    if (xTaskCreate(exti_task, cfg->task_name ? cfg->task_name : "PIOS_EXTI",
                    cfg->task_stack ? cfg->task_stack : 3072,
                    line,
                    cfg->task_priority ? cfg->task_priority
                                       : (configMAX_PRIORITIES - 1),
                    &line->task) != pdPASS) {
        return -1;
    }

    gpio_config_t io = {
        .intr_type    = GPIO_INTR_POSEDGE,
        .mode         = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ULL << cfg->pin,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
    };
    if (gpio_config(&io) != ESP_OK) {
        goto fail;
    }

    if (!exti_isr_service_installed) {
        if (gpio_install_isr_service(ESP_INTR_FLAG_IRAM) != ESP_OK) {
            goto fail;
        }
        exti_isr_service_installed = true;
    }

    if (gpio_isr_handler_add(cfg->pin, exti_gpio_isr, line) != ESP_OK) {
        goto fail;
    }

    line->in_use = true;
    return 0;

fail:
    vTaskDelete(line->task);
    line->task = NULL;
    return -1;
}

/**
 * Number of data-ready edges that arrived while the handler was still busy.
 * Non-zero means the sensor path is not keeping up -- check before blaming
 * the filter for stale samples.
 */
uint32_t PIOS_ESP32_EXTI_GetMissed(uint8_t line_id)
{
    if (line_id >= EXTI_MAX_LINES || !exti_lines[line_id].in_use) {
        return 0;
    }
    return exti_lines[line_id].missed;
}

/**
 * Shim for the shared sensor drivers.
 *
 * pios/common/pios_mpu6000.c ends PIOS_MPU6000_Init() with an unconditional
 * PIOS_EXTI_Init(cfg->exti_cfg). That call is meaningless here -- struct
 * pios_exti_cfg describes an STM32 EXTI line -- but providing this stub means
 * the shared driver links and runs unmodified, which is worth more than
 * tidiness. Board files set .exti_cfg = NULL and call
 * PIOS_ESP32_EXTI_Init() themselves with the real configuration.
 *
 * If a non-NULL config ever arrives here it means a board file was copied
 * from an STM32 target without being adapted, so say so rather than silently
 * running with no data-ready interrupt at all.
 */
int32_t PIOS_EXTI_Init(const struct pios_exti_cfg *cfg)
{
    if (cfg != NULL) {
        printf("[PIOS] EXTI: ignoring an STM32-style exti_cfg. "
               "Set .exti_cfg = NULL and use PIOS_ESP32_EXTI_Init().\n");
        return -1;
    }
    return 0;
}
