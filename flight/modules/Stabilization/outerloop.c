/**
 ******************************************************************************
 * @addtogroup OpenPilotModules OpenPilot Modules
 * @{
 * @addtogroup StabilizationModule Stabilization Module
 * @brief Stabilization PID loops in an airframe type independent manner
 * @note This object updates the @ref ActuatorDesired "Actuator Desired" based on the
 * PID loops on the @ref AttitudeDesired "Attitude Desired" and @ref AttitudeState "Attitude State"
 * @{
 *
 * @file       outerloop.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2014.
 * @brief      Attitude stabilization module.
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

#include <openpilot.h>
#ifdef SIMPOSIX
#include <stdio.h>
#include <sys/time.h>
#endif
#include <pid.h>
#include <callbackinfo.h>
#include <ratedesired.h>
#include <stabilizationdesired.h>
#include <attitudestate.h>
#include <stabilizationstatus.h>
#include <flightstatus.h>
#include <manualcontrolcommand.h>
#include <stabilizationbank.h>


#include <stabilization.h>
#include <cruisecontrol.h>
#include <altitudeloop.h>
#include <CoordinateConversions.h>

// Private constants

#define CALLBACK_PRIORITY CALLBACK_PRIORITY_REGULAR

#define UPDATE_EXPECTED   (1.0f / PIOS_SENSOR_RATE)
#define UPDATE_MIN        1.0e-6f
#define UPDATE_MAX        1.0f
#define UPDATE_ALPHA      1.0e-2f

// Private variables
static DelayedCallbackInfo *callbackHandle;
static AttitudeStateData attitude;

static uint8_t previous_mode[AXES] = { 255, 255, 255, 255 };
static PiOSDeltatimeConfig timeval;

// Private functions
static void stabilizationOuterloopTask();
static void AttitudeStateUpdatedCb(__attribute__((unused)) UAVObjEvent *ev);

void stabilizationOuterloopInit()
{
    RateDesiredInitialize();
    StabilizationDesiredInitialize();
    AttitudeStateInitialize();
    StabilizationStatusInitialize();
    FlightStatusInitialize();
    ManualControlCommandInitialize();

    PIOS_DELTATIME_Init(&timeval, UPDATE_EXPECTED, UPDATE_MIN, UPDATE_MAX, UPDATE_ALPHA);

    // Its own dedicated task, NOT the shared CBTASK_PRIORITY (CALLBACK_TASK_FLIGHTCONTROL)
    // that innerloop.c still correctly uses - see pios_callbackscheduler.h's
    // CALLBACK_TASK_STABILIZATIONOUTERLOOP comment for why: this task
    // (outerloop.c) is RateDesired.Thrust's producer, innerloop.c (still
    // CRITICAL priority inside FlightControl, correctly so - it's a fast,
    // gyro-triggered loop) is its consumer, and a consumer must never be
    // able to starve its own producer of scheduler time.
    callbackHandle = PIOS_CALLBACKSCHEDULER_Create(&stabilizationOuterloopTask, CALLBACK_PRIORITY, CALLBACK_TASK_STABILIZATIONOUTERLOOP, CALLBACKINFO_RUNNING_STABILIZATION0, STACK_SIZE_BYTES);
    AttitudeStateConnectCallback(AttitudeStateUpdatedCb);
}


/**
 * WARNING! This callback executes with critical flight control priority every
 * time a gyroscope update happens do NOT put any time consuming calculations
 * in this loop unless they really have to execute with every gyro update
 */
static void stabilizationOuterloopTask()
{
    AttitudeStateData attitudeState;
    RateDesiredData rateDesired;
    StabilizationDesiredData stabilizationDesired;
    StabilizationStatusOuterLoopData enabled;

    AttitudeStateGet(&attitudeState);
    StabilizationDesiredGet(&stabilizationDesired);
    RateDesiredGet(&rateDesired);
    StabilizationStatusOuterLoopGet(&enabled);
#ifdef SIMPOSIX
    // AXES is 4 (stabilization.h) and the per-axis loop below iterates
    // t=0..AXES-1, reaching t=3 (Thrust) for both arrays - but they were
    // declared with only 3 elements (Roll/Pitch/Yaw), so every t=3 access
    // (stabilizationAltitudeHold()'s input AND rateDesiredAxis[3]'s
    // output) was out-of-bounds/undefined behavior, compiler-flagged
    // (-Warray-bounds). Sized to AXES with Thrust included so the
    // existing loop logic below works correctly within bounds, no other
    // changes needed. Gated to SIMPOSIX pending independent verification
    // against real hardware (see the rateDesired.Thrust assignment below,
    // which depends on this being properly sized).
    float stabilizationDesiredAxis[AXES] = {stabilizationDesired.Roll, stabilizationDesired.Pitch, stabilizationDesired.Yaw, stabilizationDesired.Thrust};
    float rateDesiredAxis[AXES] = {rateDesired.Roll, rateDesired.Pitch, rateDesired.Yaw, rateDesired.Thrust};
#else
    float stabilizationDesiredAxis[3] = {stabilizationDesired.Roll, stabilizationDesired.Pitch, stabilizationDesired.Yaw};
    float rateDesiredAxis[3] = {rateDesired.Roll, rateDesired.Pitch, rateDesired.Yaw};
#endif
    int t;
    float dT = PIOS_DELTATIME_GetAverageSeconds(&timeval);

    float local_error[3];
    {
#if defined(PIOS_QUATERNION_STABILIZATION)
        // Quaternion calculation of error in each axis.  Uses more memory.
        float rpy_desired[3];
        float q_desired[4];
        float q_error[4];

        for (t = 0; t < 3; t++) {
            switch (StabilizationStatusOuterLoopToArray(enabled)[t]) {
            case STABILIZATIONSTATUS_OUTERLOOP_ATTITUDE:
            case STABILIZATIONSTATUS_OUTERLOOP_RATTITUDE:
            case STABILIZATIONSTATUS_OUTERLOOP_WEAKLEVELING:
                rpy_desired[t] = stabilizationDesiredAxis[t];
                break;
            case STABILIZATIONSTATUS_OUTERLOOP_DIRECT:
            default:
                rpy_desired[t] = ((float *)&attitudeState.Roll)[t];
                break;
            }
        }

        RPY2Quaternion(rpy_desired, q_desired);
        quat_inverse(q_desired);
        quat_mult(q_desired, &attitudeState.q1, q_error);
        quat_inverse(q_error);
        Quaternion2RPY(q_error, local_error);

#else /* if defined(PIOS_QUATERNION_STABILIZATION) */
        // Simpler algorithm for CC, less memory
        local_error[0] = stabilizationDesiredAxis[0] - attitudeState.Roll;
        local_error[1] = stabilizationDesiredAxis[1] - attitudeState.Pitch;
        local_error[2] = stabilizationDesiredAxis[2] - attitudeState.Yaw;

        // find shortest way
        float modulo = fmodf(local_error[2] + 180.0f, 360.0f);
        if (modulo < 0) {
            local_error[2] = modulo + 180.0f;
        } else {
            local_error[2] = modulo - 180.0f;
        }
#endif /* if defined(PIOS_QUATERNION_STABILIZATION) */
    }
    for (t = 0; t < AXES; t++) {
        bool reinit = (StabilizationStatusOuterLoopToArray(enabled)[t] != previous_mode[t]);
        previous_mode[t] = StabilizationStatusOuterLoopToArray(enabled)[t];

        if (t < STABILIZATIONSTATUS_OUTERLOOP_THRUST) {
            if (reinit) {
                stabSettings.outerPids[t].iAccumulator = 0;
            }
            switch (StabilizationStatusOuterLoopToArray(enabled)[t]) {
            case STABILIZATIONSTATUS_OUTERLOOP_ATTITUDE:
                rateDesiredAxis[t] = pid_apply(&stabSettings.outerPids[t], local_error[t], dT);
                break;
            case STABILIZATIONSTATUS_OUTERLOOP_RATTITUDE:
            {
                float stickinput[3];
                stickinput[0] = boundf(stabilizationDesiredAxis[0] / stabSettings.stabBank.RollMax, -1.0f, 1.0f);
                stickinput[1] = boundf(stabilizationDesiredAxis[1] / stabSettings.stabBank.PitchMax, -1.0f, 1.0f);
                stickinput[2] = boundf(stabilizationDesiredAxis[2] / stabSettings.stabBank.YawMax, -1.0f, 1.0f);
                float rateDesiredAxisRate = stickinput[t] * StabilizationBankManualRateToArray(stabSettings.stabBank.ManualRate)[t];
                // limit corrective rate to maximum rates to not give it overly large impact over manual rate when joined together
                rateDesiredAxis[t] = boundf(pid_apply(&stabSettings.outerPids[t], local_error[t], dT),
                                            -StabilizationBankManualRateToArray(stabSettings.stabBank.ManualRate)[t],
                                            StabilizationBankManualRateToArray(stabSettings.stabBank.ManualRate)[t]
                                            );
                // Compute the weighted average rate desired
                // Using max() rather than sqrt() for cpu speed;
                // - this makes the stick region into a square;
                // - this is a feature!
                // - hold a roll angle and add just pitch without the stick sensitivity changing
                float magnitude = fabsf(stickinput[t]);
                if (t < 2) {
                    magnitude = fmaxf(fabsf(stickinput[0]), fabsf(stickinput[1]));
                }

                // modify magnitude to move the Att to Rate transition to the place
                // specified by the user
                // we are looking for where the stick angle == transition angle
                // and the Att rate equals the Rate rate
                // that's where Rate x (1-StickAngle) [Attitude pulling down max X Ratt proportion]
                // == Rate x StickAngle [Rate pulling up according to stick angle]
                // * StickAngle [X Ratt proportion]
                // so 1-x == x*x or x*x+x-1=0 where xE(0,1)
                // (-1+-sqrt(1+4))/2 = (-1+sqrt(5))/2
                // and quadratic formula says that is 0.618033989f
                // I tested 14.01 and came up with .61 without even remembering this number
                // I thought that moving the P,I, and maxangle terms around would change this value
                // and that I would have to take these into account, but varying
                // all P's and I's by factors of 1/2 to 2 didn't change it noticeably
                // and varying maxangle from 4 to 120 didn't either.
                // so for now I'm not taking these into account
                // while working with this, it occurred to me that Attitude mode,
                // set up with maxangle=190 would be similar to Ratt, and it is.
                #define STICK_VALUE_AT_MODE_TRANSITION 0.618033989f

                // the following assumes the transition would otherwise be at 0.618033989f
                // and THAT assumes that Att ramps up to max roll rate
                // when a small number of degrees off of where it should be

                // if below the transition angle (still in attitude mode)
                // '<=' instead of '<' keeps rattitude_mode_transition_stick_position==1.0 from causing DZ
                if (magnitude <= stabSettings.rattitude_mode_transition_stick_position) {
                    magnitude *= STICK_VALUE_AT_MODE_TRANSITION / stabSettings.rattitude_mode_transition_stick_position;
                } else {
                    magnitude = (magnitude - stabSettings.rattitude_mode_transition_stick_position)
                                * (1.0f - STICK_VALUE_AT_MODE_TRANSITION)
                                / (1.0f - stabSettings.rattitude_mode_transition_stick_position)
                                + STICK_VALUE_AT_MODE_TRANSITION;
                }
                rateDesiredAxis[t] = (1.0f - magnitude) * rateDesiredAxis[t] + magnitude * rateDesiredAxisRate;
            }
            break;
            case STABILIZATIONSTATUS_OUTERLOOP_WEAKLEVELING:
                // FIXME: local_error[] is rate - attitude for Weak Leveling
                // The only ramifications are:
                // Weak Leveling Kp is off by a factor of 3 to 12 and may need a different default in GCS
                // Changing Rate mode max rate currently requires a change to Kp
                // That would be changed to Attitude mode max angle affecting Kp
                // Also does not take dT into account
            {
                float stickinput[3];
                stickinput[0] = boundf(stabilizationDesiredAxis[0] / stabSettings.stabBank.RollMax, -1.0f, 1.0f);
                stickinput[1] = boundf(stabilizationDesiredAxis[1] / stabSettings.stabBank.PitchMax, -1.0f, 1.0f);
                stickinput[2] = boundf(stabilizationDesiredAxis[2] / stabSettings.stabBank.YawMax, -1.0f, 1.0f);
                float rate_input    = stickinput[t] * StabilizationBankManualRateToArray(stabSettings.stabBank.ManualRate)[t];
                float weak_leveling = local_error[t] * stabSettings.settings.WeakLevelingKp;
                weak_leveling = boundf(weak_leveling, -stabSettings.settings.MaxWeakLevelingRate, stabSettings.settings.MaxWeakLevelingRate);

                // Compute desired rate as input biased towards leveling
                rateDesiredAxis[t] = rate_input + weak_leveling;
            }
            break;
            case STABILIZATIONSTATUS_OUTERLOOP_DIRECT:
            default:
                rateDesiredAxis[t] = stabilizationDesiredAxis[t];
                break;
            }
        } else {
            switch (StabilizationStatusOuterLoopToArray(enabled)[t]) {
#ifdef REVOLUTION
            case STABILIZATIONSTATUS_OUTERLOOP_ALTITUDE:
                rateDesiredAxis[t] = stabilizationAltitudeHold(stabilizationDesiredAxis[t], ALTITUDEHOLD, reinit);
                break;
            case STABILIZATIONSTATUS_OUTERLOOP_ALTITUDEVARIO:
                rateDesiredAxis[t] = stabilizationAltitudeHold(stabilizationDesiredAxis[t], ALTITUDEVARIO, reinit);
                break;
#endif /* REVOLUTION */
            case STABILIZATIONSTATUS_OUTERLOOP_DIRECT:
            default:
                rateDesiredAxis[t] = stabilizationDesiredAxis[t];
                break;
            }
        }
    }

    // Copy arrays back to structs
    rateDesired.Roll = rateDesiredAxis[0];
    rateDesired.Pitch = rateDesiredAxis[1];
    rateDesired.Yaw = rateDesiredAxis[2];

#ifdef SIMPOSIX
    // The comment this replaces claimed "this per-axis loop only ever runs
    // over t=0..2 (Roll/Pitch/Yaw)" - but AXES is 4 (stabilization.h), so
    // the loop above DOES reach t=3 (Thrust), and its switch (line ~247)
    // already computes rateDesiredAxis[3] correctly for every mode:
    // stabilizationAltitudeHold()'s real PID output for
    // ALTITUDEHOLD/ALTITUDEVARIO, or a raw passthrough for DIRECT/other
    // modes (including CruiseControl, which isn't listed here and falls to
    // default). Unconditionally copying stabilizationDesired.Thrust (the
    // RAW, pre-outer-loop input) instead of rateDesiredAxis[3] discards
    // whatever stabilizationAltitudeHold() just computed every single
    // cycle - confirmed empirically: ActuatorDesired.Thrust stayed frozen
    // bit-for-bit for the entire duration of an AltitudeHold-mode test,
    // never once reflecting the PID's output. This was very likely an
    // earlier fix (see git history / CLAUDE.md session notes) for Thrust
    // being stuck at 0.0 during early Manual-mode-only testing - that
    // symptom is real and this line does fix it for DIRECT/CruiseControl
    // (where rateDesiredAxis[3] equals stabilizationDesired.Thrust anyway,
    // so no behavior change there), but it silently broke
    // ALTITUDEHOLD/ALTITUDEVARIO, which weren't exercised yet at the time.
    // Matches the Roll/Pitch/Yaw pattern two lines above - trust the
    // loop's per-mode switch instead of bypassing it. Gated to SIMPOSIX
    // pending independent verification against real hardware.
    {
        static bool marker_printed = false;
        if (!marker_printed) {
            marker_printed = true;
            printf("[SIMPOSIX-IFDEF-MARKER] outerloop.c using rateDesired.Thrust=rateDesiredAxis[3] (%.4f), not stabilizationDesired.Thrust (%.4f)\n",
                   (double)rateDesiredAxis[3], (double)stabilizationDesired.Thrust);
            fflush(stdout);
        }
    }
    rateDesired.Thrust = rateDesiredAxis[3];
#else
    // Thrust has no outer-loop PID of its own - every other axis falls
    // through to a direct stabilizationDesired->rateDesired copy in
    // OUTERLOOP_DIRECT above, but this per-axis loop only ever runs over
    // t=0..2 (Roll/Pitch/Yaw), so that copy never happened for Thrust.
    // Nothing else in the codebase writes RateDesired.Thrust, so it sat at
    // its 0.0 default forever - Actuator's mixer reads ActuatorDesired.Thrust
    // (which chains back to this), so no motor could ever respond to
    // throttle. This is the same passthrough OUTERLOOP_DIRECT does, applied
    // unconditionally since Thrust doesn't have Attitude/RattitudeWeakLeveling/etc
    // outer-loop modes to begin with.
    rateDesired.Thrust = stabilizationDesired.Thrust;
#endif

    RateDesiredSet(&rateDesired);
    {
        uint8_t armed;
        FlightStatusArmedGet(&armed);
        float throttleDesired;
        ManualControlCommandThrottleGet(&throttleDesired);
        if (armed != FLIGHTSTATUS_ARMED_ARMED ||
            ((stabSettings.settings.LowThrottleZeroIntegral == STABILIZATIONSETTINGS_LOWTHROTTLEZEROINTEGRAL_TRUE) && throttleDesired < 0)) {
            // Force all axes to reinitialize when engaged
            for (t = 0; t < AXES; t++) {
                previous_mode[t] = 255;
            }
        }
    }

    // update cruisecontrol based on attitude
    cruisecontrol_compute_factor(&attitudeState, rateDesired.Thrust);
    stabSettings.monitor.rateupdates = 0;
}


static void AttitudeStateUpdatedCb(__attribute__((unused)) UAVObjEvent *ev)
{
    // to reduce CPU utilization, outer loop is not executed on every state update
    static uint8_t cpusaver = 0;

#ifdef SIMPOSIX
    {
        static uint32_t callCount = 0;
        static double lastPrint = 0.0;
        struct timeval tv;
        callCount++;
        gettimeofday(&tv, NULL);
        double wallclock = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
        if (callCount == 1 || wallclock - lastPrint > 0.5) {
            lastPrint = wallclock;
            printf("[SIMPOSIX-IFDEF-MARKER] outerloop.c AttitudeStateUpdatedCb: t=%.3f callCount=%u\n",
                   wallclock, (unsigned)callCount);
            fflush(stdout);
        }
    }
#endif

    if ((cpusaver++ % OUTERLOOP_SKIPCOUNT) == 0) {
        // this does not need mutex protection as both eventdispatcher and stabi run in same callback task!
        AttitudeStateGet(&attitude);
        PIOS_CALLBACKSCHEDULER_Dispatch(callbackHandle);
    }
}

/**
 * @}
 * @}
 */
