/**
 ******************************************************************************
 * @file       pios_task_runtime.c
 * @author     NinjaPilot, 2026
 * @brief      uxTaskGetRunTime() for ESP-IDF's FreeRTOS build.
 *
 * pios/common/pios_task_monitor.c calls uxTaskGetRunTime(), which is NOT stock
 * FreeRTOS -- it is this tree's one deliberate local patch on top of V11.3.0
 * (see the FreeRTOS section of CLAUDE.md): a read-and-clear per-task run-time
 * counter.
 *
 * We cannot carry that patch here, because this target links against ESP-IDF's
 * own FreeRTOS build rather than the vendored kernel, and the standing rule in
 * this repo is not to patch kernel internals anyway. So the same semantics are
 * reconstructed at the PiOS layer out of stock API: uxTaskGetSystemState()
 * reports each task's cumulative ulRunTimeCounter, and this file keeps the
 * previous reading per task and returns the delta.
 *
 * Requires CONFIG_FREERTOS_GENERATE_RUN_TIME_STATS=y and
 * CONFIG_FREERTOS_USE_TRACE_FACILITY=y (both set in sdkconfig.defaults).
 * Without them the counters read zero and the task monitor simply reports 0%
 * rather than misbehaving.
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

#ifdef PIOS_INCLUDE_TASK_MONITOR

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Enough for the module tasks plus IDF's own. Overflow just means the
 * least-recently-seen task loses its baseline and reports one short
 * interval; it does not break anything. */
#define RUNTIME_MAX_TRACKED 24
/* uxTaskGetSystemState() returns 0 -- not a partial list -- when this array is
 * too small for the number of tasks that exist. The shim then finds nothing,
 * reports zero runtime for the idle task, and the task monitor concludes 0%
 * idle, i.e. 100% CPU and a Critical CPUOverload alarm on a board that is
 * barely working. Adding two tasks (AltFilter and the altitude-hold callback)
 * to a system already carrying WiFi crossed the old limit of 32 and did
 * exactly that. Sized well clear of the real count, which is around 30. */
#define RUNTIME_MAX_TASKS   48

struct runtime_entry {
    TaskHandle_t handle;
    uint32_t     last;
};

static struct runtime_entry runtime_table[RUNTIME_MAX_TRACKED];
static uint8_t runtime_next_slot;

/**
 * Run time consumed by one task since the previous call for that task.
 *
 * Matches the read-and-clear behaviour pios_task_monitor.c expects from the
 * patched kernel: the first call for a given task establishes a baseline and
 * returns 0, and each later call returns the delta.
 */
UBaseType_t uxTaskGetRunTime(TaskHandle_t xTask)
{
    if (xTask == NULL) {
        return 0;
    }

    /* uxTaskGetSystemState() is the only stock way to reach a specific
     * task's cumulative counter. It walks every task list under a critical
     * section, so this is not something to call at loop rate -- the task
     * monitor runs it once a second, which is fine. */
    static TaskStatus_t status[RUNTIME_MAX_TASKS];

    UBaseType_t count = uxTaskGetSystemState(status, RUNTIME_MAX_TASKS, NULL);
    uint32_t    total = 0;
    bool        found = false;

    if (count == 0) {
        /* Buffer too small for the live task count. Say so once: the symptom
         * downstream is a permanent 100% CPU reading and a Critical alarm that
         * blocks arming, which looks nothing like "raise a compile-time
         * constant". */
        static bool warned;
        if (!warned) {
            warned = true;
            printf("[TASKRT] uxTaskGetSystemState returned 0 -- more than %d tasks; "
                   "CPU load will read 100%%\n", RUNTIME_MAX_TASKS);
        }
        return 0;
    }

    for (UBaseType_t i = 0; i < count; i++) {
        if (status[i].xHandle == xTask) {
            total = (uint32_t)status[i].ulRunTimeCounter;
            found = true;
            break;
        }
    }
    if (!found) {
        return 0;
    }

    struct runtime_entry *entry = NULL;

    for (uint8_t i = 0; i < RUNTIME_MAX_TRACKED; i++) {
        if (runtime_table[i].handle == xTask) {
            entry = &runtime_table[i];
            break;
        }
    }

    if (entry == NULL) {
        entry = &runtime_table[runtime_next_slot];
        runtime_next_slot = (runtime_next_slot + 1) % RUNTIME_MAX_TRACKED;
        entry->handle = xTask;
        entry->last   = total;
        return 0;   /* first sight of this task: establish a baseline */
    }

    /* Unsigned subtraction, so a counter wrap self-corrects. */
    uint32_t delta = total - entry->last;

    entry->last = total;
    return (UBaseType_t)delta;
}

#endif /* PIOS_INCLUDE_TASK_MONITOR */
