/**
 ******************************************************************************
 * @file       pios_wdg.c
 * @author     NinjaPilot, 2026
 * @brief      ESP32 watchdog, backed by the IDF Task WDT.
 *
 * PiOS's watchdog is a flag scheme, not a plain kick: each participating task
 * registers a bit, sets it once per pass, and only when EVERY registered bit
 * has been seen does PIOS_WDG_Clear() actually pet the hardware. That means a
 * single stalled task takes the board down even while the others keep running,
 * which is the behaviour you want from a flight controller.
 *
 * This is deliberately ENABLED on this target. (The ArduPilot ESP32 port
 * disables both the interrupt and task watchdogs in sdkconfig because its loop
 * overruns kept tripping them; we are not carrying that problem, so there is
 * no reason to fly without the protection.)
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

#ifdef PIOS_INCLUDE_WDG

#include "esp_task_wdt.h"
#include "esp_system.h"

static struct wdg_state {
    uint16_t used_flags;            /* bits handed out by RegisterFlag   */
    uint16_t bootup_flags;          /* flags outstanding at last reset   */
    volatile uint16_t active_flags; /* bits set since the last full set  */
    bool     armed;                 /* a full set has been seen at least once */
    /* Set if the watchdog task could not start or could not subscribe. Never
     * printed -- printf on this target is a genuine hazard (see wdg_task) --
     * but it is the first thing to look at in a debugger or core dump when
     * the watchdog appears to be doing nothing. */
    bool     subscribe_failed;
} wdg;

/* active_flags is written by every participating task, so the read-modify-write
 * needs protecting even on a unicore build -- a preemption between the load and
 * the store would silently drop another task's bit. */
static portMUX_TYPE wdg_lock = portMUX_INITIALIZER_UNLOCKED;

/*
 * ONE task owns the IDF watchdog.
 *
 * The IDF watchdog is per-task: esp_task_wdt_add() subscribes whichever task
 * calls it and esp_task_wdt_reset() only ever resets the caller's own entry,
 * with no way to reset on another task's behalf. PiOS is the other shape
 * entirely -- participants set a flag bit and whichever one completes the set
 * does the petting, so the task that reaches the watchdog changes pass to pass.
 *
 * Two earlier attempts to bridge that gap are worth recording, because both
 * failed on hardware:
 *
 *   1. A single global "already subscribed" bool. The first task to arrive
 *      subscribed itself and set the flag; every other task then read the flag
 *      as proof it was subscribed too and called esp_task_wdt_reset() having
 *      never been added. That fails with ESP_ERR_NOT_FOUND and logged an error
 *      at roughly 50 lines a second -- and meant only one of the four
 *      participating tasks was ever really being watched.
 *
 *   2. Subscribing each task lazily on its first check-in. Correct in
 *      principle, fatal in practice: it puts esp_task_wdt_status() and
 *      esp_task_wdt_add() on the hot path of flight tasks whose stacks are
 *      sized to the byte, and the board panicked inside the IDF watchdog on
 *      the very first check-in with a corrupted list. (See the note on
 *      xTaskCreate stack units in PIOS_WDG_Init.)
 *
 * So: the flight tasks only ever set a bit, which costs a spinlock and no
 * calls. This task -- with a stack of its own, sized for the job -- is the
 * only thing that ever touches the IDF watchdog.
 */
#define PIOS_WDG_TASK_STACK_WORDS 768   /* 3KB -- see the unit note in pios_esp32.h */
#define PIOS_WDG_TASK_PRIORITY    (tskIDLE_PRIORITY + 3)
#define PIOS_WDG_POLL_MS          100

static void wdg_task(__attribute__((unused)) void *arg)
{
    if (esp_task_wdt_add(NULL) != ESP_OK) {
        wdg.subscribe_failed = true;
    }

    for (;;) {
        bool complete;

        vTaskDelay(pdMS_TO_TICKS(PIOS_WDG_POLL_MS));

        portENTER_CRITICAL(&wdg_lock);
        complete = (wdg.active_flags & wdg.used_flags) == wdg.used_flags;
        if (complete) {
            wdg.active_flags = 0;
            wdg.armed = true;
        }
        portEXIT_CRITICAL(&wdg_lock);

        if (complete || !wdg.armed) {
            /* Keep petting until the first full set arrives, so the gap
             * between a module registering its flag in Start() and its task
             * reaching its first check-in cannot trip the watchdog. */
            esp_task_wdt_reset();
        }
        /* Otherwise deliberately do NOT reset: some registered task has
         * stopped checking in, and letting the IDF watchdog time out and
         * reset the board is exactly the point of the flag scheme. */
    }
}

uint16_t PIOS_WDG_Init(void)
{
    /* A reset cause of TASK_WDT/INT_WDT means the previous boot died with
     * flags outstanding. We cannot recover which ones (that would need RTC
     * memory), so report all-registered and let the System module raise the
     * alarm on a non-zero bootup word. */
    esp_reset_reason_t reason = esp_reset_reason();

    if (reason == ESP_RST_TASK_WDT || reason == ESP_RST_INT_WDT || reason == ESP_RST_WDT) {
        wdg.bootup_flags = 0xFFFF;
        printf("[PIOS] WDG: previous boot ended in a watchdog reset (reason %d)\n",
               (int)reason);
    } else {
        wdg.bootup_flags = 0;
    }

    wdg.used_flags   = 0;
    wdg.active_flags = 0;
    wdg.armed        = false;

    /* Stack in WORDS, like every other task in the tree -- pios_esp32.h
     * converts to the bytes ESP-IDF actually wants. */
    if (xTaskCreate(wdg_task, "PIOS_WDG", PIOS_WDG_TASK_STACK_WORDS, NULL,
                    PIOS_WDG_TASK_PRIORITY, NULL) != pdPASS) {
        wdg.subscribe_failed = true;
    }

    return wdg.bootup_flags;
}

bool PIOS_WDG_RegisterFlag(uint16_t flag_requested)
{
    /* Registration must finish before the scheduler has anything to guard,
     * and PiOS only ever calls this from module init, so no locking. */
    if (wdg.used_flags & flag_requested) {
        return false;
    }
    wdg.used_flags |= flag_requested;
    return true;
}

bool PIOS_WDG_UpdateFlag(uint16_t flag)
{
    bool complete;

    /* Hot path, called from flight tasks on very tight stacks: set a bit and
     * get out. No IDF calls, no printf, no allocation -- see wdg_task(). */
    portENTER_CRITICAL(&wdg_lock);
    wdg.active_flags |= flag;
    complete = (wdg.active_flags & wdg.used_flags) == wdg.used_flags;
    portEXIT_CRITICAL(&wdg_lock);

    return complete;
}

uint16_t PIOS_WDG_GetBootupFlags(void)
{
    return wdg.bootup_flags;
}

uint16_t PIOS_WDG_GetActiveFlags(void)
{
    return wdg.active_flags;
}

void PIOS_WDG_Clear(void)
{
    portENTER_CRITICAL(&wdg_lock);
    wdg.active_flags = 0;
    portEXIT_CRITICAL(&wdg_lock);
}

#endif /* PIOS_INCLUDE_WDG */
