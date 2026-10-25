/**
 ******************************************************************************
 * @file       pios_irq.c
 * @author     NinjaPilot, 2026
 * @brief      ESP32 critical sections (nestable).
 *
 * The STM32 backends implement this as a global CPSID/CPSIE pair with a
 * nesting counter. IDF's equivalent is a per-core spinlock critical section,
 * which already handles nesting itself, so this is a thin wrapper over
 * portENTER_CRITICAL/portEXIT_CRITICAL.
 *
 * With CONFIG_FREERTOS_UNICORE=y (which this target sets) that is exactly the
 * interrupt-disable-plus-nesting-count the STM32 version provides. If unicore
 * is ever turned off, note that this still only excludes the CALLING core --
 * anything genuinely shared across cores needs a real FreeRTOS primitive, not
 * these functions.
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

#ifdef PIOS_INCLUDE_IRQ

#include "freertos/FreeRTOS.h"

static portMUX_TYPE pios_irq_mux = portMUX_INITIALIZER_UNLOCKED;

int32_t PIOS_IRQ_Disable(void)
{
    /* IDF's critical sections nest on the same core, so no counter of our
     * own is needed (and keeping one would only let it drift out of sync
     * with the kernel's). */
    portENTER_CRITICAL(&pios_irq_mux);
    return 0;
}

int32_t PIOS_IRQ_Enable(void)
{
    portEXIT_CRITICAL(&pios_irq_mux);
    return 0;
}

#endif /* PIOS_INCLUDE_IRQ */
