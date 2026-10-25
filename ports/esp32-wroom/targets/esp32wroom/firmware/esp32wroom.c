/**
 ******************************************************************************
 *
 * @file       esp32wroom.c
 * @author     NinjaPilot, 2026
 * @brief      Entry point for the ESP32-WROOM-32E target.
 *
 * The STM32 and POSIX targets own main(): they call PIOS_SYS_Init(), create an
 * init task, then vTaskStartScheduler(). None of that applies here. ESP-IDF's
 * startup code has already brought up the clocks, the heap and FreeRTOS, and
 * calls app_main() as an ordinary task. Starting the scheduler a second time
 * would fault.
 *
 * So app_main() IS the init task: it does the board bring-up inline and then
 * returns, which deletes the task and leaves the module threads running. That
 * is the documented IDF idiom, not a shortcut.
 *
 * @see        The GNU Public License (GPL) Version 3
 *
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

#include "inc/openpilot.h"
#include <systemmod.h>
#include <uavobjectsinit.h>

/* Provided by InitMods.c (kept in sync with the module list by hand on this
 * target -- the Make-driven codegen the other boards use is not in play). */
extern void InitModules(void);
extern void StartModules(void);

extern void PIOS_Board_Init(void);

void app_main(void)
{
    /* Console banner and chip identification. */
    PIOS_SYS_Init();

    printf("[NinjaPilot] esp32wroom target starting\n");

    /* Board drivers. */
    PIOS_Board_Init();

    /* MODULE_INITIALISE_ALL expands, on this target, to InitModules()
     * followed by SystemModInitialize() -- see the USE_ESP32 branch in
     * pios_initcall.h. SystemModInitialize() is what eventually reaches
     * MODULE_TASKCREATE_ALL and starts every module thread. */
    MODULE_INITIALISE_ALL;

    printf("[NinjaPilot] init complete, %u bytes heap free\n",
           (unsigned)xPortGetFreeHeapSize());

    /* Returning from app_main() deletes this task; the module threads carry
     * on. The IDF explicitly supports this.
     *
     * (Tested: parking here instead of returning does NOT change the
     * callback-scheduler corruption seen during bring-up, so the dangling
     * reference is not into this task's stack.) */
}
