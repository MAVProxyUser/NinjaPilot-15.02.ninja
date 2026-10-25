/**
 ******************************************************************************
 *
 * @file       pios_esp32.h
 * @author     NinjaPilot, 2026
 * @brief      Top-level PiOS header for the ESP32 (Xtensa LX6) architecture.
 *
 * This mirrors the role pios_sim_posix.h plays for the POSIX targets: pios.h
 * keys the whole architecture selection off USE_<BOARD>, and this file is the
 * ESP32 branch. Nothing STM32 is reachable from here.
 *
 * The important structural difference from the STM32 targets is that we run on
 * ESP-IDF's own FreeRTOS build, not the kernel vendored under
 * pios/common/libraries/FreeRTOS. ESP-IDF owns FreeRTOSConfig.h (it is
 * generated from sdkconfig), owns the linker script, and has already started
 * the scheduler by the time our entry point runs. See esp32wroom.c.
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

#ifndef PIOS_ESP32_H
#define PIOS_ESP32_H

/* PIOS board specific feature selection */
#include "pios_config.h"

/* C Lib includes */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/* ESP-IDF's FreeRTOS. Note the path prefix: IDF headers live under
 * freertos/ and pulling them in any other way picks up the vendored
 * V11.3.0 kernel instead, which will not link against IDF's port. */
#ifdef PIOS_INCLUDE_FREERTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

/*
 * Task stacks: WORDS in, BYTES out.
 *
 * ESP-IDF sizes task stacks in BYTES. Vanilla FreeRTOS -- which every shared
 * module in this tree was written against -- counts WORDS, and they all say
 *
 *     xTaskCreate(fooTask, "Foo", STACK_SIZE_BYTES / 4, ...);
 *
 * Left alone on IDF, that asks for a QUARTER of the intended stack. The
 * telemetry RX task ran on 2KB of the 8KB it thought it had; Attitude on 1KB
 * of 4KB; Receiver on 768 bytes of 3KB.
 *
 * The failure mode is not a clean overflow report. The canary is missed and
 * whatever sits below the stack is corrupted instead, surfacing much later and
 * somewhere else entirely -- LoadProhibited inside vTaskSwitchContext, or in
 * PIOS_COM_validate, or in runNextCallback -- with nothing pointing back at
 * the task that actually overran.
 *
 * Rather than edit the xTaskCreate call in every shared module, convert the
 * unit here, once. Every stack size in this port therefore keeps the vanilla
 * FreeRTOS meaning it has on the STM32 targets.
 *
 * This MUST come after freertos/task.h above: it is a function-like macro on
 * the same name, and it would otherwise mangle the prototype in that header.
 */
extern uint32_t pios_esp32_task_create_failures;

static inline BaseType_t pios_esp32_task_create(TaskFunction_t fn, const char *name,
                                                uint32_t stack_words, void *param,
                                                UBaseType_t prio, TaskHandle_t *handle)
{
    /* x4, explicitly. NOT sizeof(StackType_t): the Xtensa port defines
     * portSTACK_TYPE as uint8_t precisely BECAUSE its stacks are counted in
     * bytes, so sizeof(StackType_t) is 1 and multiplying by it does nothing
     * at all. The conversion needed here is words-to-bytes on a 32-bit
     * machine, which is 4. */
    /*
     * Words -> bytes (x4, see above) AND pinned to CORE 1.
     *
     * With SMP enabled, everything created through this shim -- every
     * shared flight module, the callback schedulers, this port's own tasks
     * -- lands on the application core. WiFi, lwIP and IDF housekeeping
     * stay on core 0 (their Kconfig defaults plus explicit affinity in
     * sdkconfig.defaults). The network stack can then never preempt a
     * flight task at all: separation by silicon, not by priority
     * negotiation. Anything that genuinely belongs on core 0 bypasses the
     * shim by parenthesizing the call -- see pios_wifi.c.
     */
    /*
     * Core assignment.
     *
     * The default is core 1 (see above): WiFi, lwIP and IDF housekeeping stay
     * on core 0, so the network stack can never preempt a flight task.
     *
     * But pinning EVERYTHING to core 1 left core 0 measured 98.8% idle while
     * core 1 ran out of headroom. These tasks are not in the control path --
     * they are housekeeping, links and parsers, all tolerant of the few ms of
     * jitter core 0 can add -- so they go there and give core 1 the room back:
     *
     *   System  1Hz housekeeping, and with DIAG_TASKS its task-table walk runs
     *           with the scheduler SUSPENDED; on core 0 that stall stops
     *           landing on the control loop at all.
     *   TelTx/TelRx, PIOS_UART_RX  telemetry and UART plumbing.
     *   GPS     NMEA/UBX parsing on 5Hz data.
     *   RemoteID  beacon housekeeping.
     *
     * Deliberately NOT moved: Sensors, Attitude/StateEstimation, the callback
     * schedulers, Stabilization, Actuator, Receiver and PIOS_DSM (stick input
     * IS control path), and the IMU data-ready task -- anything whose timing
     * the control loop depends on.
     */
    static const char *const core0_tasks[] = {
        "System", "TelTx", "TelRx", "PIOS_UART_RX", "GPS", "RemoteID",
        "StatusLED",
    };
    BaseType_t core = 1;

    for (unsigned i = 0; i < sizeof(core0_tasks) / sizeof(core0_tasks[0]); i++) {
        const char *a = name, *b = core0_tasks[i];
        while (*a && *a == *b) {
            a++;
            b++;
        }
        if (*a == '\0' && *b == '\0') {
            core = 0;
            break;
        }
    }

    BaseType_t rc = (xTaskCreatePinnedToCore)(fn, name, stack_words * 4,
                                              param, prio, handle, core);

    /* PiOS ignores this return value at every call site, so a failed creation
     * is otherwise completely silent and only surfaces much later as a NULL
     * task or queue handle. Count it here instead of printing: most of these
     * calls run on systemTask's stack via MODULE_TASKCREATE_ALL, and a printf
     * there is exactly the kind of stack pressure this shim exists to stop.
     * Read it in a debugger or a core dump. */
    if (rc != pdPASS) {
        pios_esp32_task_create_failures++;
    }
    return rc;
}

#define xTaskCreate(fn, name, depth, param, prio, handle) \
    pios_esp32_task_create((fn), (name), (uint32_t)(depth), (param), (prio), (handle))
#endif

/*
 * STM32 StdPeriph spelling used by shared drivers.
 *
 * pios_hmc5x83.c's SPI path calls PIOS_SPI_SetClockSpeed() with
 * SPI_BaudRatePrescaler_16 -- a name that only exists on STM32 targets, where
 * stm32fxxx_spi.h is in scope. PiOS's own portable enum for the same thing is
 * PIOS_SPI_PRESCALER_16 in pios_spi.h. Alias it rather than editing the shared
 * driver: we drive that part over I2C here, so the SPI half is dead code that
 * still has to compile (it is gated on PIOS_INCLUDE_SPI, which this board
 * needs for the IMU).
 */
#ifndef SPI_BaudRatePrescaler_16
#define SPI_BaudRatePrescaler_16 PIOS_SPI_PRESCALER_16
#endif

#include <pios_mem.h>
#include <pios_architecture.h>

/* PIOS board specific device configuration */
#include "pios_board.h"

/* PIOS debug interface */
#include <pios_debug.h>
#include <pios_debuglog.h>

#ifdef PIOS_INCLUDE_FLASH
/* Settings storage. The STM32 branch of pios.h pulls this in the same way;
 * uavobjectpersistence.c expects it to arrive via pios.h. */
#include <pios_flashfs.h>
#endif

/* PIOS common functions */
#include <pios_crc.h>

#ifdef PIOS_INCLUDE_TASK_MONITOR
#ifndef PIOS_INCLUDE_FREERTOS
#error PiOS Task Monitor requires PIOS_INCLUDE_FREERTOS to be defined
#endif
#include <pios_task_monitor.h>
/* Not stock FreeRTOS -- see pios/esp32/pios_task_runtime.c. */
UBaseType_t uxTaskGetRunTime(TaskHandle_t xTask);
#endif

#ifdef PIOS_INCLUDE_CALLBACKSCHEDULER
#ifndef PIOS_INCLUDE_FREERTOS
#error PiOS CallbackScheduler requires PIOS_INCLUDE_FREERTOS to be defined
#endif
#include <pios_callbackscheduler.h>
#endif

/* PIOS system functions */
#ifdef PIOS_INCLUDE_DELAY
#include <pios_delay.h>
#include <pios_deltatime.h>
#endif

#include "pios_initcall.h"

#ifdef PIOS_INCLUDE_SYS
#include <pios_sys.h>
#endif

#ifdef PIOS_INCLUDE_IRQ
#include <pios_irq.h>
#endif

#ifdef PIOS_INCLUDE_WDG
#include <pios_wdg.h>
#endif

#ifdef PIOS_INCLUDE_LED
#include <pios_led.h>
#endif

#ifdef PIOS_INCLUDE_SPI
#include <pios_spi.h>
#endif

#ifdef PIOS_INCLUDE_I2C
/* Safe to include here -- unlike pios_sensors.h this pulls in nothing but
 * stdbool, so there is no cycle back through pios.h. */
#include <pios_i2c.h>
#endif

#ifdef PIOS_INCLUDE_SERVO
#include <pios_servo.h>
#endif

#ifdef PIOS_INCLUDE_RCVR
#include <pios_rcvr.h>
#endif

#ifdef PIOS_INCLUDE_PPM
#include <pios_ppm.h>
#endif

#ifdef PIOS_INCLUDE_COM
#include <pios_com.h>
#endif

/* Sensor headers are deliberately NOT included here. pios_sensors.h opens
 * with #include <pios.h>, so pulling it (or pios_mpu6000.h, which needs its
 * typedefs) in from this file creates a cycle: pios_sensors.c -> pios_sensors.h
 * -> pios.h -> here -> pios_mpu6000.h, at which point pios_sensors.h's guard
 * is set but PIOS_SENSORS_Driver is not yet defined.
 *
 * The STM32 branch of pios.h does not include them either -- board files pull
 * in the sensor drivers they actually use. board_hw_defs.c does the same. */

/* The shared sensor drivers carry a `const struct pios_exti_cfg *` field
 * describing an STM32 EXTI line. We never populate it (see pios_exti.c), but
 * it has to be a known -- if incomplete -- type for the headers to compile. */
struct pios_exti_cfg;
extern int32_t PIOS_EXTI_Init(const struct pios_exti_cfg *cfg);

/* ESP32-specific driver private interfaces (config structs + Init
 * prototypes). These deliberately do NOT reuse pios/inc/pios_*_priv.h --
 * those carry STM32 peripheral-library types (TIM_TimeBaseInitTypeDef,
 * GPIO_InitTypeDef) and are unusable here. The POSIX backend takes the
 * same approach. */
#include <pios_esp32_priv.h>

#endif /* PIOS_ESP32_H */
