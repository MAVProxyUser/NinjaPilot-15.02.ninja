/**
 ******************************************************************************
 *
 * @file       pios_callbackscheduler.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2014.
 * @brief      Include files of the PIOS_CALLBACKSCHEDULER
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

#ifndef PIOS_CALLBACKSCHEDULER_H
#define PIOS_CALLBACKSCHEDULER_H

// Public types
typedef enum {
    CALLBACK_PRIORITY_CRITICAL = 0,
    CALLBACK_PRIORITY_REGULAR  = 1,
    CALLBACK_PRIORITY_LOW = 2
} DelayedCallbackPriority;
// Use the CallbackPriority to define how frequent a callback needs to be
// called in relation to others in the same callback scheduling task.
// The scheduler will call callbacks waiting for execution with the same
// priority in a round robin way. However one slot in this queue is reserved
// for a chosen member of the next lower priority. This member will also be
// chosen in a round robin way.
// Example:
// Assume you have 6 callbacks in the same PriorityTask, all constantly wanting
// to be executed.
// A and B are priority CRITICAL,
// c and d are priority REGULAR,
// x and y are priority LOW.
// Then the execution schedule will look as follows:
// ...ABcABdABxABcABdAByABcABdABxABcABdABy...
// However if only the 3 callbacks, A, c and x want to execute, you will get:
// ...AcAxAcAxAcAxAcAxAcAxAcAxAcAxAcAxAcAx...
// And if only A and y need execution it will be:
// ...AyAyAyAyAyAyAyAyAyAyAyAyAyAyAyAyAyAy...
// despite their different priority they would get treated equally in this case.
//
// WARNING: Callbacks ALWAYS should return as quickly as possible.  Otherwise
// a low priority callback can block a critical one from being executed.
// Callbacks MUST NOT block execution!

// The three-attempt investigation behind CALLBACK_TASK_STATEESTIMATION and
// CALLBACK_TASK_ALTITUDEHOLD's placement here (all confirmed via direct
// instrumentation - a runCount counter in pios_callbackscheduler.c's
// CallbackSchedulerTask/runNextCallback, and a totalCalls/accelBitSetCalls
// counter in stateestimation.c - not just reasoned about):
//
// 1. StateEstimationCb (stateestimation.c) and altitudeHoldTask
//    (altitudeloop.c) both originally shared CALLBACK_TASK_FLIGHTCONTROL
//    with the gyro-driven stabilizationInnerloopTask (CRITICAL priority).
//    Measured running at only ~8 executions/second, vs ~400-500Hz for the
//    gyro loop - the callback scheduler's own round-robin-with-one-
//    reserved-slot fairness mechanism (see the PriorityTask/
//    CallbackPriority comments below) only lets ONE lower-priority
//    callback run per full lap of the CRITICAL queue, and at gyro rate
//    that reserved slot gets consumed by the CRITICAL callback itself
//    almost every time.
// 2. Moving both to a shared CALLBACK_TASK_STATEESTIMATION (its own
//    FreeRTOS task, lower real priority than FLIGHTCONTROL) fixed
//    StateEstimationCb (tens of thousands of executions/test) but not
//    altitudeHoldTask (28 executions in one test) - StateEstimationCb's
//    own dispatch rate (tied to GyroSensor/AccelSensor updates) is high
//    enough to reproduce the exact same starvation pattern one level
//    down, so sharing a task with anything dispatched anywhere near gyro
//    rate doesn't work, no matter the absolute priority level.
// 3. Giving altitudeHoldTask ITS OWN task too, still at a LOWER real
//    priority than FLIGHTCONTROL (reasoning: "it'll get real RTOS
//    scheduling turns whenever FLIGHTCONTROL blocks between gyro
//    samples") - STILL starved (runCount barely moved). Root cause: this
//    is strict-priority preemptive scheduling, not fair-share - a
//    genuinely lower-priority task gets ZERO guaranteed CPU time against
//    a higher-priority one that's continuously ready, and
//    FLIGHTCONTROL's own combined CRITICAL+REGULAR workload (gyro loop +
//    attitude control, both still legitimately needing to run at a high
//    rate) turned out to leave it ready often enough that it essentially
//    never blocks long enough to hand real time to a lower-priority task.
//    This is correct, textbook FreeRTOS behavior, not a bug - the earlier
//    assumption that "FLIGHTCONTROL blocks between gyro samples" just
//    wasn't true in practice.
//
// The actual fix: StateEstimation and AltitudeHold are placed ABOVE
// FlightControl here. Their own callback bodies are brief (a handful of
// float operations - PID applies, sensor fusion math - microseconds, no
// blocking calls), so the added worst-case latency to gyro-loop dispatch
// is negligible; this is standard rate/deadline-monotonic priority
// assignment (a moderate-rate but latency-sensitive task can legitimately
// sit above a task whose own real-time requirement is bounded and whose
// per-cycle cost is small), not a workaround. The real hardware-interrupt-
// level gyro sampling itself is unaffected either way - FreeRTOS task
// priority only governs software task scheduling, not the sensor ISR.
// StateEstimation is placed ABOVE AltitudeHold, not just above
// FlightControl: AltitudeHold is StateEstimation's own CONSUMER
// (altitudeHoldTask is dispatched once per fresh VelocityState, which
// StateEstimation produces). Once the real filterbaro.c/filteraltitude.c
// dead-code bug elsewhere in this investigation was fixed and
// StateEstimationCb actually started running at its real rate (thousands
// of calls/second instead of the ~8Hz it was stuck at for this entire
// investigation), altitudeHoldTask's own dispatch rate rose to match -
// and because it briefly outranked its own producer, it could preempt
// StateEstimationCb often enough, under real flight load, to reproduce
// the exact same starvation pattern one level up (confirmed via a real
// dT spike from ~7ms to ~30ms in filteraltitude.c's integrator during an
// active climb, causing a real, large single-step position error). A
// consumer must never sit above its own producer in a priority-strict
// scheduler for exactly this reason - it can eat the CPU time the
// producer needed to keep up.
//
// CALLBACK_TASK_STABILIZATIONOUTERLOOP: same class of bug, found chasing
// a manual-throttle (no estimator/hold-mode involvement at all) test that
// still got hit with an instant idle-to-near-max thrust snap. outerloop.c
// (produces RateDesired.Thrust from StabilizationDesired.Thrust) and
// innerloop.c (consumes RateDesired.Thrust, CRITICAL priority, gyro-
// triggered at ~500Hz) both used to share CALLBACK_TASK_FLIGHTCONTROL,
// outerloop.c at only REGULAR priority. Confirmed via innerloop.c's own
// rateupdates watchdog counter (already-existing code, see innerloop.c)
// collapsing to its floor within ~3s of boot and staying there - NOT a
// persistent starvation though (confirmed: the instant AttitudeState
// updates resumed flowing after a separate ~12s gap near an arm
// transition, rateupdates recovered from -64 to -6 in a single sample and
// stayed healthy for the rest of the test) - but a real, reproducible
// worst-case risk under sustained CRITICAL load in FLIGHTCONTROL
// regardless. Placed above FlightControl for the same producer-must-
// outrank-consumer reason as StateEstimation above AltitudeHold -
// innerloop.c (the consumer, still correctly CRITICAL-priority inside
// FlightControl - it's a genuinely fast, latency-sensitive loop and
// shouldn't move) must never be able to starve outerloop.c (the
// producer) from getting a chance to run at all.
typedef enum {
    CALLBACK_TASK_AUXILIARY               = (tskIDLE_PRIORITY + 1),
    CALLBACK_TASK_NAVIGATION              = (tskIDLE_PRIORITY + 2),
    CALLBACK_TASK_FLIGHTCONTROL           = (tskIDLE_PRIORITY + 3),
    CALLBACK_TASK_STABILIZATIONOUTERLOOP  = (tskIDLE_PRIORITY + 4),
    CALLBACK_TASK_ALTITUDEHOLD            = (tskIDLE_PRIORITY + 5),
    CALLBACK_TASK_STATEESTIMATION         = (tskIDLE_PRIORITY + 6),
    CALLBACK_TASK_DEVICEDRIVER            = (tskIDLE_PRIORITY + 7),
} DelayedCallbackPriorityTask;
// Use the PriorityTask to define the global importance of callback execution
// compared to other processes in the system.
// Callbacks dispatched in a higher PriorityTasks will halt the execution of
// any lower priority processes, including callbacks and even callback
// scheduling tasks until they are done!
// Assume you have two callbacks:
// A in priorityTask DEVICEDRIVER,
// b and c in priorityTask AUXILIARY,
// Then the execution schedule can look as follows: (| marks a task switch)
// <b ... /b><c ... |<A ... /A>| ... /c><b ...
// be aware that if A gets constantly dispatched this would look like this:
// <b ... |<A><A><A><A><A><A><A><A><A><A><A><A><A><A><A><A><A><A><A>...
//
// WARNING: Any higher priority task can prevent lower priority code from being
// executed! (This does not only apply to callbacks but to all FreeRTOS tasks!)

typedef enum {
    CALLBACK_UPDATEMODE_NONE     = 0,
    CALLBACK_UPDATEMODE_SOONER   = 1,
    CALLBACK_UPDATEMODE_LATER    = 2,
    CALLBACK_UPDATEMODE_OVERRIDE = 3
} DelayedCallbackUpdateMode;
// When scheduling a callback for execution at a time in the future, use the
// update mode to define what should happen if the callback is already
// scheduled.
// With NONE, the schedule will not be updated and the callback will be
// executed at the original time.
// With SOONER, the closer of the two schedules will take precedence
// With LATER, the schedule more distant in the future will be used.
// With OVERRIDE, the original schedule will be discarded.

typedef void (*DelayedCallback)(void);
// Use this type for the callback function.

struct DelayedCallbackInfoStruct;
typedef struct DelayedCallbackInfoStruct DelayedCallbackInfo;
// Use a pointer to DelayedCallbackInfo as a handle to identify registered callbacks.
// be aware that the same callback function can be registered as a callback
// several times, even with different callback priorities and even
// priorityTasks, using different handles and as such different dispatch calls.
// Be aware that using different priorityTasks for the same callback function
// might cause your callback to be executed recursively in different task contexts!

// Public functions
//

/**
 * Initialize the scheduler
 * must be called before any other functions are called
 * \return Success (0), failure (-1)
 */
int32_t PIOS_CALLBACKSCHEDULER_Initialize();

/**
 * Start all scheduler tasks
 * Will instantiate all scheduler tasks registered so far.  Although new
 * callbacks CAN be registered beyond that point, any further scheduling tasks
 * will be started the moment of instantiation.  It is not possible to increase
 * the STACK requirements of a scheduler task after this function has been
 * run.  No callbacks will be run before this function is called, although
 * they can be marked for later execution by executing the dispatch function.
 * \return Success (0), failure (-1)
 */
int32_t PIOS_CALLBACKSCHEDULER_Start();

/**
 * Register a new callback to be called by a delayed callback scheduler task.
 * If a scheduler task with the specified task priority does not exist yet, it
 * will be created.
 * \param[in] cb The callback to be invoked
 * \param[in] priority Priority of the callback compared to other callbacks scheduled by the same delayed callback scheduler task.
 * \param[in] priorityTask Task priority of the scheduler task. One scheduler task will be spawned for each distinct value specified, further callbacks created  with the same priorityTask will all be handled by the same delayed callback scheduler task and scheduled according to their individual callback priorities
 * \param[in] stacksize The stack requirements of the callback when called by the scheduler.
 * \param[in] callbackID - CallbackInfoRunningElem from CallbackInfo UAVObject, unique identified to collect stats for the callback, -1 to ignore!
 * \return CallbackInfo Pointer on success, NULL if failed.
 */
DelayedCallbackInfo *PIOS_CALLBACKSCHEDULER_Create(
    DelayedCallback cb,
    DelayedCallbackPriority priority,
    DelayedCallbackPriorityTask priorityTask,
    int16_t callbackID,
    uint32_t stacksize);

/**
 * Schedule dispatching a callback at some point in the future. The function returns immediately.
 * \param[in] *cbinfo the callback handle
 * \param[in] milliseconds How far in the future to dispatch the callback
 * \param[in] updatemode What to do if the callback is already scheduled but not dispatched yet.
 * The options are:
 * UPDATEMODE_NONE: An existing schedule will not be touched, the call will have no effect at all if there's an existing schedule.
 * UPDATEMODE_SOONER: The callback will be rescheduled only if the new schedule triggers before the original one would have triggered.
 * UPDATEMODE_LATER: The callback will be rescheduled only if the new schedule triggers after the original one would have triggered.
 * UPDATEMODE_OVERRIDE: The callback will be rescheduled in any case, effectively overriding any previous schedule. (sooner+later=override)
 * \return 0: not scheduled, previous schedule takes precedence, 1: new schedule, 2: previous schedule overridden
 */
int32_t PIOS_CALLBACKSCHEDULER_Schedule(
    DelayedCallbackInfo *cbinfo,
    int32_t milliseconds,
    DelayedCallbackUpdateMode updatemode);

/**
 * Dispatch an event by invoking the supplied callback. The function
 * returns immediately, the callback is invoked from the event task.
 * \param[in] *cbinfo the callback handle
 * \return Success (-1), failure (0)
 */
int32_t PIOS_CALLBACKSCHEDULER_Dispatch(DelayedCallbackInfo *cbinfo);

/**
 * Dispatch an event by invoking the supplied callback. The function
 * returns immediately, the callback is invoked from the event task.
 * \param[in] *cbinfo the callback handle
 * \param[in] pxHigherPriorityTaskWoken
 * xSemaphoreGiveFromISR() will set *pxHigherPriorityTaskWoken to pdTRUE if
 * giving the semaphore caused a task to unblock, and the unblocked task has a
 * priority higher than the currently running task.  If xSemaphoreGiveFromISR()
 * sets this value to pdTRUE then a context switch should be requested before
 * the interrupt is exited.
 * From FreeRTOS Docu: Context switching from an ISR uses port specific syntax.
 * Check the demo task for your port to find the syntax required.
 * \return Success (-1), failure (0)
 */
int32_t PIOS_CALLBACKSCHEDULER_DispatchFromISR(DelayedCallbackInfo *cbinfo, long *pxHigherPriorityTaskWoken);

/**
 * Information about a running callback that has been registered
 * via a call to PIOS_CALLBACKSCHEDULER_Create().
 */
struct pios_callback_info {
    /** Remaining task stack in bytes -1 for detected stack overflow. */
    int32_t  stack_remaining;
    /** Flag indicating whether or not the task is running. */
    bool     is_running;
    /** Count of executions of the callback since system start */
    uint32_t running_time_count;
};

/**
 * Iterator callback, called for each monitored callback by PIOS_CALLBACKSCHEDULER_ForEachCallback().
 *
 * @param task_id   The id of the task the task_info refers to.
 * @param task_info Information about the task identified by task_id.
 * @param context   Context information optionally provided by the caller to PIOS_TASK_MONITOR_TasksIterate()
 */
typedef void (*CallbackSchedulerCallbackInfoCallback)(int16_t task_id, const struct pios_callback_info *callback_info, void *context);

/**
 * Iterator. Iterates over all callbacks and all scheduler tasks and retrieves information
 *
 * @param[in] callback  Callback function to receive the data - will be called in same task context as the callerThe id of the task the task_info refers to.
 * @param     context   Context information optionally provided to the callback.
 */
void PIOS_CALLBACKSCHEDULER_ForEachCallback(CallbackSchedulerCallbackInfoCallback callback, void *context);

#endif // PIOS_CALLBACKSCHEDULER_H
