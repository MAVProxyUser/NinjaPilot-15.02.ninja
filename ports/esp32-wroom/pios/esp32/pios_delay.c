/**
 ******************************************************************************
 * @file       pios_delay.c
 * @author     NinjaPilot, 2026
 * @brief      ESP32 delay/timebase functions.
 *
 * esp_timer_get_time() is a free-running 64-bit microsecond counter that the
 * IDF keeps coherent across sleep and across both cores, so it is a much
 * better timebase than anything we would build out of a hardware timer. PiOS
 * only wants 32 bits; the truncation wraps every ~71.6 minutes, which is
 * exactly what the STM32 backends do and what PIOS_DELAY_DiffuS() is written
 * to tolerate.
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

#ifdef PIOS_INCLUDE_DELAY

#include "esp_timer.h"
#include "rom/ets_sys.h"

int32_t PIOS_DELAY_Init(void)
{
    /* esp_timer is brought up by the IDF before app_main() runs. Nothing
     * to do, but keep the entry point so board init reads the same as the
     * other backends. */
    return 0;
}

int32_t PIOS_DELAY_WaituS(uint32_t uS)
{
    /* Busy-wait. Deliberately not vTaskDelay(): callers use this for
     * sub-tick sensor timing where yielding would be wrong. Keep the
     * argument small. */
    ets_delay_us(uS);
    return 0;
}

int32_t PIOS_DELAY_WaitmS(uint32_t mS)
{
    /* Milliseconds are long enough to be worth yielding for, and every
     * caller of this is in init or an error path. Round up so we never
     * return early. */
    vTaskDelay((mS + portTICK_PERIOD_MS - 1) / portTICK_PERIOD_MS);
    return 0;
}

uint32_t PIOS_DELAY_GetuS(void)
{
    return (uint32_t)esp_timer_get_time();
}

uint32_t PIOS_DELAY_GetuSSince(uint32_t t)
{
    return PIOS_DELAY_GetuS() - t;
}

uint32_t PIOS_DELAY_GetRaw(void)
{
    return PIOS_DELAY_GetuS();
}

uint32_t PIOS_DELAY_DiffuS(uint32_t raw)
{
    /* Unsigned arithmetic makes the 32-bit wrap self-correcting for any
     * interval shorter than the wrap period. */
    return PIOS_DELAY_GetuS() - raw;
}

#endif /* PIOS_INCLUDE_DELAY */
