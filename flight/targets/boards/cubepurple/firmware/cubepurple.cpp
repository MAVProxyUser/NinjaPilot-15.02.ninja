/**
 ******************************************************************************
 * @addtogroup OpenPilotSystem OpenPilot System
 * @brief These files are the core system files of OpenPilot.
 * They are the ground layer just above PiOS. In practice, OpenPilot actually starts
 * in the main() function of openpilot.c
 * @{
 * @addtogroup OpenPilotCore OpenPilot Core
 * @brief This is where the OP firmware starts. Those files also define the compile-time
 * options of the firmware.
 * @{
 * @file       openpilot.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @brief      Sets up and runs main OpenPilot tasks.
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

extern "C" {
#include "inc/openpilot.h"
#include <uavobjectsinit.h>

/* Task Priorities */
#define PRIORITY_TASK_HOOKS (tskIDLE_PRIORITY + 3)

/* Global Variables */

/* Local Variables */
#define INCLUDE_TEST_TASKS  0
#if INCLUDE_TEST_TASKS
static uint8_t sdcard_available;
#endif
char Buffer[1024];
uint32_t Cache;

/* Function Prototypes */
#if INCLUDE_TEST_TASKS
static void TaskTick(void *pvParameters);
static void TaskTesting(void *pvParameters);
static void TaskHIDTest(void *pvParameters);
static void TaskServos(void *pvParameters);
static void TaskSDCard(void *pvParameters);
#endif
int32_t CONSOLE_Parse(uint8_t port, char c);
void OP_ADC_NotifyChange(uint32_t pin, uint32_t pin_value);

/* Prototype of PIOS_Board_Init() function */
extern void PIOS_Board_Init(void);
/* Bring-up aid, see pios_board.c (CUBE_BOOT_STOP) */
extern void CUBE_BootStage(uint32_t n);
extern void CUBE_Mark(uint32_t slot);
extern void Stack_Change(void);
static void Stack_Change_Weak() __attribute__((weakref("Stack_Change")));

/* Local Variables */
#define INIT_TASK_PRIORITY (tskIDLE_PRIORITY + configMAX_PRIORITIES - 1) // max priority
#define INIT_TASK_STACK    (1024 / 4)                                                                              // XXX this seems excessive
static xTaskHandle initTaskHandle;

/* Function Prototypes */
static void initTask(void *parameters);

/* Prototype of generated InitModules() function */
extern void InitModules(void);
}

/**
 * OpenPilot Main function:
 *
 * Initialize PiOS<BR>
 * Create the "System" task (SystemModInitializein Modules/System/systemmod.c) <BR>
 * Start FreeRTOS Scheduler (vTaskStartScheduler)<BR>
 * If something goes wrong, blink LED1 and LED2 every 100ms
 *
 */
int main()
{
    int result;

    CUBE_BootStage(100);
    CUBE_Mark(22);
    /*
     * This board arrives here from the ArduPilot bootloader, not an OpenPilot
     * one: its USB, UART and timer interrupts can still be enabled and pending
     * in the NVIC.  They would fire into drivers that are not set up yet the
     * moment the scheduler enables interrupts, so quiesce everything first.
     */
    SysTick->CTRL = 0;
    for (unsigned i = 0; i < sizeof(NVIC->ICER) / sizeof(NVIC->ICER[0]); i++) {
        NVIC->ICER[i] = 0xFFFFFFFF;
        NVIC->ICPR[i] = 0xFFFFFFFF;
    }
    SCB->ICSR = SCB_ICSR_PENDSVCLR_Msk | SCB_ICSR_PENDSTCLR_Msk;
    __DSB();
    __ISB();
    /* NOTE: Do NOT modify the following start-up sequence */
    /* Any new initialization functions should be added in OpenPilotInit() */
    vPortInitialiseBlocks();
    CUBE_Mark(23);

    /* Brings up System using CMSIS functions, enables the LEDs. */
    PIOS_SYS_Init();
    CUBE_BootStage(101);
    CUBE_Mark(24);

    /* For Revolution we use a FreeRTOS task to bring up the system so we can */
    /* always rely on FreeRTOS primitive */
    result = xTaskCreate(initTask, "init",
                         INIT_TASK_STACK, NULL, INIT_TASK_PRIORITY,
                         &initTaskHandle);
    PIOS_Assert(result == pdPASS);
    CUBE_Mark(25);

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    /* If all is well we will never reach here as the scheduler will now be running. */
    /* Do some PIOS_LED_HEARTBEAT to user that something bad just happened */
    PIOS_LED_Off(PIOS_LED_HEARTBEAT); \
    for (;;) { \
        PIOS_LED_Toggle(PIOS_LED_HEARTBEAT); \
        PIOS_DELAY_WaitmS(100); \
    }
    ;

    return 0;
}
/**
 * Initialisation task.
 *
 * Runs board and module initialisation, then terminates.
 */
void initTask(__attribute__((unused)) void *parameters)
{
    CUBE_BootStage(102);
    CUBE_Mark(0);
    /* board driver init */
    PIOS_Board_Init();

    CUBE_Mark(20);
    /* Initialize modules */
    MODULE_INITIALISE_ALL;
    CUBE_Mark(21);

    /* terminate this task */
    vTaskDelete(NULL);
}

/**
 * @}
 * @}
 */
