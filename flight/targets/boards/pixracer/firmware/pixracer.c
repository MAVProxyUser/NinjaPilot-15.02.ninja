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


/* OpenPilot Includes */
#include "openpilot.h"
#include "uavobjectsinit.h"
#include "systemmod.h"

/* Task Priorities */
#define PRIORITY_TASK_HOOKS             (tskIDLE_PRIORITY + 3)

/* Global Variables */

/* Local Variables */
#define INCLUDE_TEST_TASKS 0
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

/* Defined further down; used by main() before its definition. */
static void PIOS_Board_capture_reset_cause(void);
extern void Stack_Change(void);
static void Stack_Change_Weak () __attribute__ ((weakref ("Stack_Change")));

/* Local Variables */
#define INIT_TASK_PRIORITY	(tskIDLE_PRIORITY + configMAX_PRIORITIES - 1)	// max priority
#define INIT_TASK_STACK		(1024 / 4)										// XXX this seems excessive
static xTaskHandle initTaskHandle;
#if defined(PIOS_BRINGUP_DIAG)
/* Bring-up: lets the lock probe compare the mutex holder against this task. */
xTaskHandle PIOS_BRINGUP_init_task_handle(void) { return initTaskHandle; }
#endif

/* Function Prototypes */
static void initTask(void *parameters);

/* Prototype of generated InitModules() function */
extern void InitModules(void);

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
	int	result;

	/* Before anything else: latch why we reset, and quiet the watchdog that
	 * the previous firmware may have left running. */
	PIOS_Board_capture_reset_cause();
	PIOS_Board_wdg_kick();
	PIOS_Board_wdg_arm();

	/* Stage 1: reached main().  Nothing but the reset vector and the
	 * startup code has run at this point. */
	PIOS_Board_boot_stage(BRINGUP_LED_GREEN);

	/* NOTE: Do NOT modify the following start-up sequence */
	/* Any new initialization functions should be added in OpenPilotInit() */
	vPortInitialiseBlocks();  

	/* Brings up System using CMSIS functions, enables the LEDs. */
	PIOS_SYS_Init();

	/* Stage 2: clocks are configured.  If the board stops on stage 1 the PLL
	 * never locked, which on this board means the 24 MHz crystal or the
	 * PLL_M/PLL_N values for it. */
	PIOS_Board_boot_stage(BRINGUP_LED_BLUE);
	
	/* For Revolution we use a FreeRTOS task to bring up the system so we can */
	/* always rely on FreeRTOS primitive */
	result = xTaskCreate(initTask, "init",
						 INIT_TASK_STACK, NULL, INIT_TASK_PRIORITY,
						 &initTaskHandle);
	PIOS_Assert(result == pdPASS);
	
	/* Stage 3: heap is up and the init task exists.  Stopping here means the
	 * scheduler never started. */
	PIOS_Board_boot_stage(BRINGUP_LED_RED);

	/* Start the FreeRTOS scheduler */
	vTaskStartScheduler();

	/* If all is well we will never reach here as the scheduler will now be running. */
	/* Do some PIOS_LED_HEARTBEAT to user that something bad just happened */
	PIOS_LED_Off(PIOS_LED_HEARTBEAT); \
	for(;;) { \
		PIOS_LED_Toggle(PIOS_LED_HEARTBEAT); \
		PIOS_DELAY_WaitmS(100); \
	};

	return 0;
}
/*
 * The independent watchdog, and why this board keeps resetting.
 *
 * ArduPilot calls stm32_watchdog_init() as a matter of course, so the
 * ArduCopter that shipped on this board had the IWDG running.  On STM32 the
 * IWDG cannot be turned off once started - only a power-on reset clears it -
 * so it keeps counting into whatever firmware runs next.  A payload that never
 * reloads it gets reset at a fixed interval no matter what it is doing, which
 * is exactly the shape observed here: USB enumerates, the board lives about 24
 * seconds, drops, and repeats.
 *
 * Reloading it is a two-byte write and is harmless when the watchdog was never
 * started, so do it unconditionally and often.
 */
#define PXR_IWDG_BASE		0x40003000UL
#define PXR_IWDG_KR		(*(volatile uint32_t *)(PXR_IWDG_BASE + 0x00))
#define PXR_IWDG_KR_RELOAD	0x0000AAAAUL

void PIOS_Board_wdg_kick(void)
{
	PXR_IWDG_KR = PXR_IWDG_KR_RELOAD;
}

/* Bring-up: the bootloader on this board never arms the IWDG, so a wedged
 * CPU just sits there looking "stuck".  Arm it ourselves: the reporter task
 * feeds it while the scheduler is alive, a wedge reboots into the bootloader
 * (steady green blink) within a few seconds.  LSI is loose, so 4 s nominal
 * is anywhere from ~2.7 s to ~7.5 s. */
void PIOS_Board_wdg_arm(void)
{
	IWDG->KR  = 0x5555;	/* unlock PR/RLR */
	IWDG->PR  = 4;		/* LSI/64 -> ~500 Hz */
	IWDG->RLR = 1999;	/* ~4.0 s */
	IWDG->KR  = 0xCCCC;	/* start (harmless if already running) */
	IWDG->KR  = 0xAAAA;	/* reload with the new period */
}

/* RCC_CSR reset flags, latched before anything clears them. */
uint32_t pios_bringup_reset_cause;

static void PIOS_Board_capture_reset_cause(void)
{
	pios_bringup_reset_cause = RCC->CSR;
	RCC->CSR |= RCC_CSR_RMVF;	/* clear for next time */
}

const char *PIOS_Board_reset_cause_str(void)
{
	uint32_t c = pios_bringup_reset_cause;

	if (c & (1u << 29)) return "INDEPENDENT WATCHDOG";
	if (c & (1u << 30)) return "window watchdog";
	if (c & (1u << 28)) return "software";
	if (c & (1u << 27)) return "power-on";
	if (c & (1u << 26)) return "NRST pin";
	if (c & (1u << 25)) return "brown-out";
	if (c & (1u << 31)) return "low-power";
	return "unknown";
}

/**
 * Drive the three LEDs directly, without PiOS.
 *
 * Usable from the first instruction of main(): it enables the GPIOB clock
 * itself and does not depend on the clock tree being configured, so it works
 * whether the CPU is on HSI or the PLL.
 */
void PIOS_Board_boot_stage(uint32_t leds)
{
	PIOS_Board_wdg_kick();

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	/* PB1, PB3 and PB11 to push-pull output */
	GPIOB->MODER = (GPIOB->MODER & ~((3u << (1 * 2)) | (3u << (3 * 2)) | (3u << (11 * 2))))
		     | ((1u << (1 * 2)) | (1u << (3 * 2)) | (1u << (11 * 2)));
	GPIOB->OTYPER &= ~(uint16_t)BRINGUP_LED_ALL;

	/* Active low, so clearing a bit lights the LED. */
	GPIOB->BSRRH = (uint16_t)(leds & BRINGUP_LED_ALL);
	GPIOB->BSRRL = (uint16_t)(BRINGUP_LED_ALL & ~leds);
}

/**
 * Blink the given LED n times, leaving all LEDs off afterwards.
 *
 * Busy-waits, which is fine: the only caller runs before the system is doing
 * anything else, and the point is to be visible.
 */
void PIOS_Board_boot_blink(uint32_t led, unsigned n)
{
	PIOS_Board_boot_stage(0);
	PIOS_DELAY_WaitmS(450);

	while (n--) {
		PIOS_Board_boot_stage(led);
		PIOS_DELAY_WaitmS(90);
		PIOS_Board_boot_stage(0);
		PIOS_DELAY_WaitmS(110);
		PIOS_Board_wdg_kick();
	}

	PIOS_DELAY_WaitmS(350);
}

/* Plain-string console output; the formatted PIOS_COM helpers pull in stdio. */
void PIOS_Board_debug_puts(const char *str)
{
	PIOS_Board_wdg_kick();	/* every boot step feeds the dog */
#if defined(PIOS_INCLUDE_DEBUG_CONSOLE)
	if (PIOS_COM_DEBUG > 0) {
		PIOS_COM_SendStringNonBlocking(PIOS_COM_DEBUG, str);
	}
#else
	(void)str;
#endif
}

void PIOS_Board_debug_putu(unsigned v)
{
	char buf[12];
	int i = sizeof(buf) - 1;

	buf[i] = '\0';
	do {
		buf[--i] = '0' + (v % 10);
		v /= 10;
	} while (v && i > 0);

	PIOS_Board_debug_puts(&buf[i]);
}

void PIOS_Board_debug_puthex(unsigned v)
{
	static const char digits[] = "0123456789ABCDEF";
	char buf[11];
	int i = sizeof(buf) - 1;

	buf[i] = '\0';
	do {
		buf[--i] = digits[v & 0xF];
		v >>= 4;
	} while (v && i > 2);
	buf[--i] = 'x';
	buf[--i] = '0';
	PIOS_Board_debug_puts(&buf[i]);
}

/**
 * Initialisation task.
 *
 * Runs board and module initialisation, then terminates.
 */
void
initTask(void *parameters)
{
    (void)parameters;
	/* board driver init */
	PIOS_Board_Init();

	/*
	 * BRING-UP DIAGNOSTIC, in place of a plain MODULE_INITIALISE_ALL.
	 *
	 * This task runs at the maximum priority and does not block, so a module
	 * whose init function never returns - a failed PIOS_Assert is an
	 * unconditional while(1) - freezes the entire system.  No other task ever
	 * runs, the System module never gets to blink the heartbeat, and the board
	 * simply sits there.  That is indistinguishable from a dozen other
	 * failures unless the module is identified.
	 *
	 * Before running module N the green LED blinks N+1 times, then red is left
	 * on for the duration of the call.  A board frozen on solid red therefore
	 * says "the module after the last blink group is the one that hung", with
	 * no console needed.  The same index goes to the UART7 console for anyone
	 * who has a serial adapter on the debug pads.
	 */
	{
		unsigned idx = 0;

		for (initmodule_t *fn = __module_initcall_start; fn < __module_initcall_end; fn++) {
			if (!fn->fn_minit) {
				idx++;
				continue;
			}

			/* The per-module green blink identified module 15
			 * (TelemetryInitialize) as the one that hangs, so it is off
			 * now - it cost 25 s of boot and the sub-step trace inside
			 * that module is what matters.  Restore it by uncommenting
			 * if a different module ever needs finding.
			 *
			 * PIOS_Board_boot_blink(BRINGUP_LED_GREEN, idx + 1);
			 */
			PIOS_Board_debug_puts("module init ");
			PIOS_Board_debug_putu(idx);
			PIOS_Board_debug_puts(", free heap ");
			PIOS_Board_debug_putu(xPortGetFreeHeapSize());
			PIOS_Board_debug_puts("\r\n");

			/* red stays on while the module initialises */
			PIOS_Board_boot_stage(BRINGUP_LED_RED);
			(fn->fn_minit)();

			idx++;
		}

		PIOS_Board_debug_puts("all modules initialised\r\n");
	}

	/* terminate this task */
	vTaskDelete(NULL);
}

/**
 * @}
 * @}
 */

