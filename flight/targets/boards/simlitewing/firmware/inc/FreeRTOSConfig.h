#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
* Application specific definitions.
*
* These definitions should be adjusted for your particular hardware and
* application requirements.
*
* THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
* FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
*
* See http://www.freertos.org/a00110.html.
*----------------------------------------------------------*/

/* Notes: We use 5 task priorities */


/* The old FreeRTOS V8.0.1 Posix port (Source/portable/GCC/Posix, superseded
 * by the FreeRTOS-Kernel V11.3.0 upgrade) used a bespoke set of per-platform
 * macros here (COND_SIGNALING/CHECK_TASK_RESUMES/RUNNING_THREAD_MUTEX/
 * TICK_SIGNAL/TICK_SIGWAIT/IDLE_SLEEPS) to select between several alternate
 * signal+condvar suspend/resume implementations, one of which (the __APPLE__
 * branch, i.e. this exact host) had a real missed-wakeup race between a
 * thread marking itself about to sleep and actually calling
 * pthread_cond_wait - confirmed via live process sampling (fw_simposix's
 * flight-control callback thread sat blocked, not busy, for ~90 real
 * seconds spanning an AltitudeVario runaway-climb test, while the resumer
 * side of that race checks/signals threadStatus without holding the
 * sleeper's own mutex). The new port (portable/ThirdParty/GCC/Posix)
 * doesn't use any of these macros - it replaced the whole mechanism with a
 * purpose-built event primitive (utils/wait_for_event.c) designed to avoid
 * exactly that race, so there is nothing left to select per-platform here. */
#ifdef __APPLE__
        #define configUSE_PREEMPTION    1
        #define configIDLE_SHOULD_YIELD 0
#endif
#ifdef __CYGWIN__
        #define configUSE_PREEMPTION    0
        #define configIDLE_SHOULD_YIELD 1
#endif
#ifdef __linux__
        #define configUSE_PREEMPTION                 1
        #define configIDLE_SHOULD_YIELD              0
#endif


#define configUSE_IDLE_HOOK                          1
#define configUSE_TICK_HOOK                          0
#define configCPU_CLOCK_HZ                           72000000
#define configTICK_RATE_HZ                           1000
#define configMAX_PRIORITIES                         8  /* was 7 - bumped again for CALLBACK_TASK_STABILIZATIONOUTERLOOP, see pios_callbackscheduler.h */
#define configMINIMAL_STACK_SIZE                     256
#define configTOTAL_HEAP_SIZE                        (45 * 1024)
#define configMAX_TASK_NAME_LEN                      (16)
#define configUSE_TRACE_FACILITY                     0
#define configUSE_16_BIT_TICKS                       0
#define configUSE_MUTEXES                            1
#define configUSE_RECURSIVE_MUTEXES                  1
#define configUSE_COUNTING_SEMAPHORES                0
#define configUSE_ALTERNATIVE_API                    0
/* The Posix port runs each task on a real pthread-managed OS stack, not a
 * FreeRTOS-owned buffer (pxPortInitialiseStack() just returns pxTopOfStack
 * unchanged) - so the generic pattern-based overflow check below is
 * comparing against memory that was never actually used as the task's
 * stack, and fires on effectively every task regardless of real usage.
 * Meaningless here; the OS's own stack guard pages are what actually
 * protect these threads. */
#define configCHECK_FOR_STACK_OVERFLOW               0
#define configQUEUE_REGISTRY_SIZE                    10


/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                        0
#define configMAX_CO_ROUTINE_PRIORITIES              (2)

/* Set the following definitions to 1 to include the API function, or zero
   to exclude the API function. */

#define INCLUDE_vTaskPrioritySet                     1
#define INCLUDE_uxTaskPriorityGet                    1
#define INCLUDE_vTaskDelete                          1
#define INCLUDE_vTaskCleanUpResources                0
#define INCLUDE_vTaskSuspend                         1
#define INCLUDE_vTaskDelayUntil                      1
#define INCLUDE_vTaskDelay                           1
#define INCLUDE_xTaskGetSchedulerState               1
#define INCLUDE_xTaskGetCurrentTaskHandle            1
#define INCLUDE_uxTaskGetStackHighWaterMark          0


/* This is the raw value as per the Cortex-M3 NVIC.  Values can be 255
   (lowest) to 1 (highest maskable) to 0 (highest non-maskable). */
#define configKERNEL_INTERRUPT_PRIORITY              15 << 4 /* equivalent to NVIC priority 15 */
        #define configMAX_SYSCALL_INTERRUPT_PRIORITY 3 << 4 /* equivalent to NVIC priority  3 */


/* This is the value being used as per the ST library which permits 16
   priority values, 0 to 15.  This must correspond to the
   configKERNEL_INTERRUPT_PRIORITY setting.  Here 15 corresponds to the lowest
   NVIC value of 255. */
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY      15

#endif /* FREERTOS_CONFIG_H */
