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
 * @file       innerloop.c
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
#include <pios_shmlog.h>
#include <pid.h>
#include <sin_lookup.h>
#include <callbackinfo.h>
#include <ratedesired.h>
#include <actuatordesired.h>
#include <gyrostate.h>
#include <airspeedstate.h>
#include <stabilizationstatus.h>
#include <flightstatus.h>
#include <manualcontrolcommand.h>
#include <stabilizationbank.h>
#include <stabilizationdesired.h>
#include <actuatordesired.h>

#include <stabilization.h>
#include <relay_tuning.h>
#include <virtualflybar.h>
#include <cruisecontrol.h>

#ifdef SIMPOSIX
#include <stdio.h>
#include <sys/time.h>
#endif

// Private constants

#define CALLBACK_PRIORITY CALLBACK_PRIORITY_CRITICAL

#define UPDATE_EXPECTED   (1.0f / PIOS_SENSOR_RATE)
#define UPDATE_MIN        1.0e-6f
#define UPDATE_MAX        1.0f
#define UPDATE_ALPHA      1.0e-2f

// Private variables
static DelayedCallbackInfo *callbackHandle;
static float gyro_filtered[3] = { 0, 0, 0 };
static float axis_lock_accum[3] = { 0, 0, 0 };
static uint8_t previous_mode[AXES] = { 255, 255, 255, 255 };
static PiOSDeltatimeConfig timeval;
static float speedScaleFactor = 1.0f;

// Private functions
static void stabilizationInnerloopTask();
static void GyroStateUpdatedCb(__attribute__((unused)) UAVObjEvent *ev);
#ifdef REVOLUTION
static void AirSpeedUpdatedCb(__attribute__((unused)) UAVObjEvent *ev);
#endif

void stabilizationInnerloopInit()
{
    RateDesiredInitialize();
    ActuatorDesiredInitialize();
    GyroStateInitialize();
    StabilizationStatusInitialize();
    FlightStatusInitialize();
    ManualControlCommandInitialize();
    StabilizationDesiredInitialize();
    ActuatorDesiredInitialize();
#ifdef REVOLUTION
    AirspeedStateInitialize();
    AirspeedStateConnectCallback(AirSpeedUpdatedCb);
#endif
    PIOS_DELTATIME_Init(&timeval, UPDATE_EXPECTED, UPDATE_MIN, UPDATE_MAX, UPDATE_ALPHA);

    callbackHandle = PIOS_CALLBACKSCHEDULER_Create(&stabilizationInnerloopTask, CALLBACK_PRIORITY, CBTASK_PRIORITY, CALLBACKINFO_RUNNING_STABILIZATION1, STACK_SIZE_BYTES);
    GyroStateConnectCallback(GyroStateUpdatedCb);

    // schedule dead calls every FAILSAFE_TIMEOUT_MS to have the watchdog cleared
    PIOS_CALLBACKSCHEDULER_Schedule(callbackHandle, FAILSAFE_TIMEOUT_MS, CALLBACK_UPDATEMODE_LATER);
}

/**
 * AxisLock's axis_lock_accum[] is a separate accumulator from the PID
 * iAccumulator terms stabilization.c already zeros on arm - it's file-local
 * here, so it needs its own reset entry point. Without this, a heading
 * error that accumulated during an earlier arm session (or from repeated
 * disturbance testing while disarmed) keeps commanding a large corrective
 * yaw rate indefinitely after a fresh arm, even with a level, non-rotating
 * vehicle - AxisLock has no absolute reference to unwind back to on its
 * own, so nothing else ever clears it.
 */
void stabilizationInnerloopResetAxisLock()
{
    axis_lock_accum[0] = 0;
    axis_lock_accum[1] = 0;
    axis_lock_accum[2] = 0;
}

static float get_pid_scale_source_value()
{
    float value;

    switch (stabSettings.stabBank.ThrustPIDScaleSource) {
    case STABILIZATIONBANK_THRUSTPIDSCALESOURCE_MANUALCONTROLTHROTTLE:
        ManualControlCommandThrottleGet(&value);
        break;
    case STABILIZATIONBANK_THRUSTPIDSCALESOURCE_STABILIZATIONDESIREDTHRUST:
        StabilizationDesiredThrustGet(&value);
        break;
    case STABILIZATIONBANK_THRUSTPIDSCALESOURCE_ACTUATORDESIREDTHRUST:
        ActuatorDesiredThrustGet(&value);
        break;
    default:
        ActuatorDesiredThrustGet(&value);
        break;
    }

    if (value < 0) {
        value = 0.0f;
    }

    return value;
}

typedef struct pid_curve_scaler {
    float  x;
    pointf points[5];
} pid_curve_scaler;

static float pid_curve_value(const pid_curve_scaler *scaler)
{
    float y = y_on_curve(scaler->x, scaler->points, sizeof(scaler->points) / sizeof(scaler->points[0]));

    return 1.0f + (IS_REAL(y) ? y : 0.0f);
}

static pid_scaler create_pid_scaler(int axis)
{
    pid_scaler scaler;

    // Always scaled with the this.
    scaler.p = scaler.i = scaler.d = speedScaleFactor;

    if (stabSettings.thrust_pid_scaling_enabled[axis][0]
        || stabSettings.thrust_pid_scaling_enabled[axis][1]
        || stabSettings.thrust_pid_scaling_enabled[axis][2]) {
        const pid_curve_scaler curve_scaler = {
            .x      = get_pid_scale_source_value(),
            .points = {
                { 0.00f, stabSettings.stabBank.ThrustPIDScaleCurve[0] },
                { 0.25f, stabSettings.stabBank.ThrustPIDScaleCurve[1] },
                { 0.50f, stabSettings.stabBank.ThrustPIDScaleCurve[2] },
                { 0.75f, stabSettings.stabBank.ThrustPIDScaleCurve[3] },
                { 1.00f, stabSettings.stabBank.ThrustPIDScaleCurve[4] }
            }
        };

        float curve_value = pid_curve_value(&curve_scaler);

        if (stabSettings.thrust_pid_scaling_enabled[axis][0]) {
            scaler.p *= curve_value;
        }
        if (stabSettings.thrust_pid_scaling_enabled[axis][1]) {
            scaler.i *= curve_value;
        }
        if (stabSettings.thrust_pid_scaling_enabled[axis][2]) {
            scaler.d *= curve_value;
        }
    }

    return scaler;
}

/**
 * WARNING! This callback executes with critical flight control priority every
 * time a gyroscope update happens do NOT put any time consuming calculations
 * in this loop unless they really have to execute with every gyro update
 */
static void stabilizationInnerloopTask()
{
    // watchdog and error handling
    {
#ifdef PIOS_INCLUDE_WDG
        PIOS_WDG_UpdateFlag(PIOS_WDG_STABILIZATION);
#endif
        bool warn  = false;
        bool error = false;
        bool crit  = false;
        // check if outer loop keeps executing
        if (stabSettings.monitor.rateupdates > -64) {
            stabSettings.monitor.rateupdates--;
        }
#if defined(PIOS_REALPOSIX)
        /* This counter decrements PER INNER-LOOP PASS, so the tolerance it
         * grants the outer loop is measured in passes, not time - raising
         * the sensor rate mechanically shrinks it (at ~300 passes/s the
         * stock -8 is ~25 ms, inside ordinary Linux scheduling hiccups
         * that self-heal; measured: 40 one-shot trips in 180 s at 500 Hz
         * IMU, zero at 250 Hz, control output healthy throughout). Same
         * adaptation as the gyroupdates thresholds above: alarm when the
         * outer loop is genuinely slow, not when the yardstick shrank.
         * -24 ~= 80 ms stall, -48 ~= 160 ms at the 500 Hz operating
         * point. -64 stays the never-ran floor. */
        if (stabSettings.monitor.rateupdates < -24) {
            warn = true;
        }
        if (stabSettings.monitor.rateupdates < -48) {
            crit = true;
        }
#else
        if (stabSettings.monitor.rateupdates < -(2 * OUTERLOOP_SKIPCOUNT)) {
            // warning if rate loop skipped more than 2 execution
            warn = true;
        }
        if (stabSettings.monitor.rateupdates < -(4 * OUTERLOOP_SKIPCOUNT)) {
            // critical if rate loop skipped more than 4 executions
            crit = true;
        }
#endif
        // check if gyro keeps updating
        if (stabSettings.monitor.gyroupdates < 1) {
            // error if gyro didn't update at all!
            error = true;
        }
#if defined(PIOS_REALPOSIX)
        /* TIME-based latency watchdog. Counting SAMPLES per pass makes the
         * tolerance a function of the sensor rate (8 samples = 8 ms at the
         * 959 Hz era it was calibrated in, but 16 ms at 490 Hz and 32 ms
         * at 250) - so raising or lowering the IMU rate silently
         * re-tightens or re-loosens the alarm. Measured: the identical
         * bench tripped 0 times at 250 Hz and ~20/min at 490 Hz on
         * ordinary 16-32 ms Linux scheduler hiccups that self-heal and
         * that the latest-sample-consuming loop rides through. Judge the
         * loop by WALL-CLOCK pass gap instead: warn past 48 ms, critical
         * past 96 ms (the estimator's own staleness watchdog sits at
         * 50 ms for the same reason). */
        {
            static uint32_t lastPassMs = 0;
            static bool     wdArmed    = false;
            uint32_t nowMs = xTaskGetTickCount() * portTICK_RATE_MS;
            if (!wdArmed) {
                wdArmed = true;
                PIOS_SHMLOG_Printf("[innerloop] time-based latency watchdog v2 armed");
            } else {
                uint32_t gapMs = nowMs - lastPassMs;
                if (gapMs > 48) {
                    warn = true;
                }
                if (gapMs > 96) {
                    crit = true;
                }
            }
            lastPassMs = nowMs;
        }
#else
        if (stabSettings.monitor.gyroupdates > 1) {
            // warning if we missed a gyro update
            warn = true;
        }
        if (stabSettings.monitor.gyroupdates > 3) {
            // critical if we missed 3 gyro updates
            crit = true;
        }
#endif
#ifdef SIMPOSIX
        {
            static double lastMonPrint = 0.0;
            struct timeval tvm;
            gettimeofday(&tvm, NULL);
            double wcm = (double)tvm.tv_sec + (double)tvm.tv_usec / 1e6;
            if (wcm - lastMonPrint > 0.5) {
                lastMonPrint = wcm;
                PIOS_SHMLOG_Printf("[SIMPOSIX-IFDEF-MARKER] innerloop.c watchdog: t=%.3f gyroupdates=%d rateupdates=%d "
                       "warn=%d error=%d crit=%d\n", wcm, (int)stabSettings.monitor.gyroupdates,
                       (int)stabSettings.monitor.rateupdates, (int)warn, (int)error, (int)crit);
                /* shmlog: no flush */
            }
        }
#endif
        stabSettings.monitor.gyroupdates = 0;

        if (crit) {
            AlarmsSet(SYSTEMALARMS_ALARM_STABILIZATION, SYSTEMALARMS_ALARM_CRITICAL);
        } else if (error) {
            AlarmsSet(SYSTEMALARMS_ALARM_STABILIZATION, SYSTEMALARMS_ALARM_ERROR);
        } else if (warn) {
            AlarmsSet(SYSTEMALARMS_ALARM_STABILIZATION, SYSTEMALARMS_ALARM_WARNING);
        } else {
            AlarmsClear(SYSTEMALARMS_ALARM_STABILIZATION);
        }
    }


    RateDesiredData rateDesired;
    ActuatorDesiredData actuator;
    StabilizationStatusInnerLoopData enabled;
    FlightStatusControlChainData cchain;

    RateDesiredGet(&rateDesired);
    ActuatorDesiredGet(&actuator);
    StabilizationStatusInnerLoopGet(&enabled);
    FlightStatusControlChainGet(&cchain);
    float rate[4] = {rateDesired.Roll, rateDesired.Pitch, rateDesired.Yaw, rateDesired.Thrust};
    float actuatorDesiredAxis[4] = {actuator.Roll, actuator.Pitch, actuator.Yaw, actuator.Thrust};
    int t;
    float dT;
    dT = PIOS_DELTATIME_GetAverageSeconds(&timeval);

    for (t = 0; t < AXES; t++) {
        bool reinit = (StabilizationStatusInnerLoopToArray(enabled)[t] != previous_mode[t]);
        previous_mode[t] = StabilizationStatusInnerLoopToArray(enabled)[t];

        if (t < STABILIZATIONSTATUS_INNERLOOP_THRUST) {
            if (reinit) {
                stabSettings.innerPids[t].iAccumulator = 0;
            }
            switch (StabilizationStatusInnerLoopToArray(enabled)[t]) {
            case STABILIZATIONSTATUS_INNERLOOP_VIRTUALFLYBAR:
                stabilization_virtual_flybar(gyro_filtered[t], rate[t], &actuatorDesiredAxis[t], dT, reinit, t, &stabSettings.settings);
                break;
            case STABILIZATIONSTATUS_INNERLOOP_RELAYTUNING:
                rate[t] = boundf(rate[t],
                                 -StabilizationBankMaximumRateToArray(stabSettings.stabBank.MaximumRate)[t],
                                 StabilizationBankMaximumRateToArray(stabSettings.stabBank.MaximumRate)[t]
                                 );
                stabilization_relay_rate(rate[t] - gyro_filtered[t], &actuatorDesiredAxis[t], t, reinit);
                break;
            case STABILIZATIONSTATUS_INNERLOOP_AXISLOCK:
                if (fabsf(rate[t]) > stabSettings.settings.MaxAxisLockRate) {
                    // While getting strong commands act like rate mode
                    axis_lock_accum[t] = 0;
                } else {
                    // For weaker commands or no command simply attitude lock (almost) on no gyro change
                    axis_lock_accum[t] += (rate[t] - gyro_filtered[t]) * dT;
                    axis_lock_accum[t]  = boundf(axis_lock_accum[t], -stabSettings.settings.MaxAxisLock, stabSettings.settings.MaxAxisLock);
                    rate[t] = axis_lock_accum[t] * stabSettings.settings.AxisLockKp;
                }
            // IMPORTANT: deliberately no "break;" here, execution continues with regular RATE control loop to avoid code duplication!
            // keep order as it is, RATE must follow!
            __attribute__((fallthrough));
            case STABILIZATIONSTATUS_INNERLOOP_RATE:
                // limit rate to maximum configured limits (once here instead of 5 times in outer loop)
                rate[t] = boundf(rate[t],
                                 -StabilizationBankMaximumRateToArray(stabSettings.stabBank.MaximumRate)[t],
                                 StabilizationBankMaximumRateToArray(stabSettings.stabBank.MaximumRate)[t]
                                 );
                pid_scaler scaler = create_pid_scaler(t);
                actuatorDesiredAxis[t] = pid_apply_setpoint(&stabSettings.innerPids[t], &scaler, rate[t], gyro_filtered[t], dT);
                break;
            case STABILIZATIONSTATUS_INNERLOOP_ACRO:
            {
                float stickinput[3];
                stickinput[0] = boundf(rate[0] / stabSettings.stabBank.ManualRate.Roll, -1.0f, 1.0f);
                stickinput[1] = boundf(rate[1] / stabSettings.stabBank.ManualRate.Pitch, -1.0f, 1.0f);
                stickinput[2] = boundf(rate[2] / stabSettings.stabBank.ManualRate.Yaw, -1.0f, 1.0f);
                rate[t] = boundf(rate[t],
                                 -StabilizationBankMaximumRateToArray(stabSettings.stabBank.MaximumRate)[t],
                                 StabilizationBankMaximumRateToArray(stabSettings.stabBank.MaximumRate)[t]
                                 );
                pid_scaler ascaler = create_pid_scaler(t);
                ascaler.i *= boundf(1.0f - (1.5f * fabsf(stickinput[t])), 0.0f, 1.0f); // this prevents Integral from getting too high while controlled manually
                float arate  = pid_apply_setpoint(&stabSettings.innerPids[t], &ascaler, rate[t], gyro_filtered[t], dT);
                float factor = fabsf(stickinput[t]) * stabSettings.stabBank.AcroInsanityFactor;
                actuatorDesiredAxis[t] = factor * stickinput[t] + (1.0f - factor) * arate;
            }
            break;
            case STABILIZATIONSTATUS_INNERLOOP_DIRECT:
            default:
                actuatorDesiredAxis[t] = rate[t];
                break;
            }
        } else {
            switch (StabilizationStatusInnerLoopToArray(enabled)[t]) {
            case STABILIZATIONSTATUS_INNERLOOP_CRUISECONTROL:
                actuatorDesiredAxis[t] = cruisecontrol_apply_factor(rate[t]);
                break;
            case STABILIZATIONSTATUS_INNERLOOP_DIRECT:
            default:
                actuatorDesiredAxis[t] = rate[t];
                break;
            }
        }

        actuatorDesiredAxis[t] = boundf(actuatorDesiredAxis[t], -1.0f, 1.0f);
    }

    // Copy arrays back to structs
    actuator.Roll = actuatorDesiredAxis[0];
    actuator.Pitch = actuatorDesiredAxis[1];
    actuator.Yaw = actuatorDesiredAxis[2];
    actuator.Thrust = actuatorDesiredAxis[3];
    
    actuator.UpdateTime = dT * 1000;

#ifdef SIMPOSIX
    {
        static bool lastGateOpen = false;
        bool gateOpen = (cchain.Stabilization == FLIGHTSTATUS_CONTROLCHAIN_TRUE);
        if (gateOpen != lastGateOpen) {
            lastGateOpen = gateOpen;
            struct timeval tv;
            gettimeofday(&tv, NULL);
            double wallclock = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
            PIOS_SHMLOG_Printf("[SIMPOSIX-IFDEF-MARKER] innerloop.c cchain.Stabilization gate CHANGED: t=%.3f gateOpen=%d "
                   "actuator.Thrust=%.4f\n", wallclock, (int)gateOpen, (double)actuator.Thrust);
            /* shmlog: no flush */
        }
        static double lastPeriodicPrint = 0.0;
        struct timeval tv2;
        gettimeofday(&tv2, NULL);
        double wallclock2 = (double)tv2.tv_sec + (double)tv2.tv_usec / 1e6;
        if (wallclock2 - lastPeriodicPrint > 0.5) {
            lastPeriodicPrint = wallclock2;
            PIOS_SHMLOG_Printf("[SIMPOSIX-IFDEF-MARKER] innerloop.c PERIODIC: t=%.3f gateOpen=%d "
                   "rateDesired.Thrust=%.4f actuatorDesiredAxis3_BEFORE_LOOP=%.4f actuator.Thrust_BEFORE_LOOP=%.4f "
                   "InnerLoop[3]=%d OuterLoop_n/a StabMode3=%d\n",
                   wallclock2, (int)gateOpen, (double)rateDesired.Thrust, (double)actuatorDesiredAxis[3],
                   (double)actuator.Thrust, (int)StabilizationStatusInnerLoopToArray(enabled)[3],
                   (int)previous_mode[3]);
            /* shmlog: no flush */
        }
    }
#endif
    if (cchain.Stabilization == FLIGHTSTATUS_CONTROLCHAIN_TRUE) {
        ActuatorDesiredSet(&actuator);
#ifdef SIMPOSIX
        {
            static uint32_t setCount = 0;
            static double lastSetPrint = 0.0;
            struct timeval tvs;
            setCount++;
            gettimeofday(&tvs, NULL);
            double now = (double)tvs.tv_sec + (double)tvs.tv_usec / 1e6;
            if (now - lastSetPrint > 1.0) {
                lastSetPrint = now;
                PIOS_SHMLOG_Printf("[inner] ActuatorDesiredSet calls=%u handle=%p",
                                   (unsigned)setCount, (void *)ActuatorDesiredHandle());
            }
        }
#endif
    } else {
        // Force all axes to reinitialize when engaged
        for (t = 0; t < AXES; t++) {
            previous_mode[t] = 255;
        }
    }

    if (stabSettings.stabBank.EnablePiroComp == STABILIZATIONBANK_ENABLEPIROCOMP_TRUE && stabSettings.innerPids[0].iLim > 1e-3f && stabSettings.innerPids[1].iLim > 1e-3f) {
        // attempted piro compensation - rotate pitch and yaw integrals (experimental)
        float angleYaw = DEG2RAD(gyro_filtered[2] * dT);
        float sinYaw   = sinf(angleYaw);
        float cosYaw   = cosf(angleYaw);
        float rollAcc  = stabSettings.innerPids[0].iAccumulator / stabSettings.innerPids[0].iLim;
        float pitchAcc = stabSettings.innerPids[1].iAccumulator / stabSettings.innerPids[1].iLim;
        stabSettings.innerPids[0].iAccumulator = stabSettings.innerPids[0].iLim * (cosYaw * rollAcc + sinYaw * pitchAcc);
        stabSettings.innerPids[1].iAccumulator = stabSettings.innerPids[1].iLim * (cosYaw * pitchAcc - sinYaw * rollAcc);
    }

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
    PIOS_CALLBACKSCHEDULER_Schedule(callbackHandle, FAILSAFE_TIMEOUT_MS, CALLBACK_UPDATEMODE_LATER);
}


static void GyroStateUpdatedCb(__attribute__((unused)) UAVObjEvent *ev)
{
    GyroStateData gyroState;

    GyroStateGet(&gyroState);

    gyro_filtered[0] = gyro_filtered[0] * stabSettings.gyro_alpha + gyroState.x * (1 - stabSettings.gyro_alpha);
    gyro_filtered[1] = gyro_filtered[1] * stabSettings.gyro_alpha + gyroState.y * (1 - stabSettings.gyro_alpha);
    gyro_filtered[2] = gyro_filtered[2] * stabSettings.gyro_alpha + gyroState.z * (1 - stabSettings.gyro_alpha);

    PIOS_CALLBACKSCHEDULER_Dispatch(callbackHandle);
    stabSettings.monitor.gyroupdates++;
}

#ifdef REVOLUTION
static void AirSpeedUpdatedCb(__attribute__((unused)) UAVObjEvent *ev)
{
    // Scale PID coefficients based on current airspeed estimation - needed for fixed wing planes
    AirspeedStateData airspeedState;

    AirspeedStateGet(&airspeedState);
    if (stabSettings.settings.ScaleToAirspeed < 0.1f || airspeedState.CalibratedAirspeed < 0.1f) {
        // feature has been turned off
        speedScaleFactor = 1.0f;
    } else {
        // scale the factor to be 1.0 at the specified airspeed (for example 10m/s) but scaled by 1/speed^2
        speedScaleFactor = boundf((stabSettings.settings.ScaleToAirspeed * stabSettings.settings.ScaleToAirspeed) / (airspeedState.CalibratedAirspeed * airspeedState.CalibratedAirspeed),
                                  stabSettings.settings.ScaleToAirspeedLimits.Min,
                                  stabSettings.settings.ScaleToAirspeedLimits.Max);
    }
}
#endif

/**
 * @}
 * @}
 */
