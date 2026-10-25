/**
 ******************************************************************************
 * @file       pios_led.c
 * @author     NinjaPilot, 2026
 * @brief      ESP32 LED driver.
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

#ifdef PIOS_INCLUDE_LED

#include "driver/gpio.h"

static const struct pios_esp32_led_cfg *led_cfg;
static bool led_state[8];

int32_t PIOS_LED_Init(const struct pios_esp32_led_cfg *cfg)
{
    PIOS_Assert(cfg);
    PIOS_Assert(cfg->num_leds <= NELEMENTS(led_state));

    for (uint8_t i = 0; i < cfg->num_leds; i++) {
        gpio_config_t io = {
            .intr_type    = GPIO_INTR_DISABLE,
            .mode         = GPIO_MODE_OUTPUT,
            .pin_bit_mask = 1ULL << cfg->leds[i].pin,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .pull_up_en   = GPIO_PULLUP_DISABLE,
        };
        if (gpio_config(&io) != ESP_OK) {
            return -1;
        }
        gpio_set_level(cfg->leds[i].pin, cfg->leds[i].active_low ? 1 : 0);
        led_state[i] = false;
    }

    led_cfg = cfg;
    return 0;
}

static void led_apply(uint32_t led_id, bool on)
{
    if (!led_cfg || led_id >= led_cfg->num_leds) {
        return;
    }
    led_state[led_id] = on;
    gpio_set_level(led_cfg->leds[led_id].pin,
                   led_cfg->leds[led_id].active_low ? !on : on);
}

void PIOS_LED_On(uint32_t led_id)
{
    led_apply(led_id, true);
}

void PIOS_LED_Off(uint32_t led_id)
{
    led_apply(led_id, false);
}

void PIOS_LED_Toggle(uint32_t led_id)
{
    if (!led_cfg || led_id >= led_cfg->num_leds) {
        return;
    }
    led_apply(led_id, !led_state[led_id]);
}

#endif /* PIOS_INCLUDE_LED */
