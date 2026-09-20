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
#include <pios_shmlog.h>
#ifdef SIMPOSIX
#include <stdio.h>
#include <sys/time.h>
#endif
#include <math.h>
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

/* ---- Interceptor mode (Interceptor tail-sitter transition) -------------------------------------------------------------
 * One attitude controller, run in the hover frame, all the time. The mode itself is a setpoint regime:
 *   CLIMB      level attitude, InterceptorClimbThrust, sticks ignored, for InterceptorClimbTime
 *   TRANSITION the pitch offset ramps to InterceptorCruisePitch at InterceptorTransitionRate; thrust ramps to InterceptorCruiseThrust
 *   CRUISE     sticks live: roll/pitch are earth-bound angles about the cruise attitude with the Rattitude blend into
 *              rates at large deflection, yaw stick slews the held heading, throttle takes over after passing through
 *              the auto value (no thrust step at hand-over)
 * The setpoint is built as a quaternion from (roll, pitch_offset + pitch, heading) and the error is the quaternion
 * error that the PIOS_QUATERNION_STABILIZATION path already uses, so nothing here is singular at 90 deg of pitch. */
#ifndef INTERCEPTOR_DEG2RAD
#define INTERCEPTOR_DEG2RAD(x) ((x) * 0.017453292519943295f)
#endif
/* ENTRY_BLEND: whatever roll/pitch the vehicle was actually doing the instant the switch flipped fades to level over this
 * many seconds instead of snapping - flicking the mode mid-stick-input must not command an attitude step.
 * LIVE_BLEND: stick authority (both the attitude offset added on top of theta_off/roll_off and the Rattitude rate blend
 * below) fades IN over this many seconds once CRUISE starts, so the auto-to-manual hand-over has no step either, even
 * if the pilot's stick is not centred the instant the mode finishes its own transition. */
#define INTERCEPTOR_ENTRY_BLEND_TIME 0.6f
#define INTERCEPTOR_LIVE_BLEND_TIME  0.8f
/* Vertical-equilibrium thrust cap: tilting the hover-frame thrust vector theta degrees off vertical costs cos(theta)
 * of vertical lift (TRANSITION_THEORY.md #4's T = weight/sin(pitch-from-horizontal), same statement in this frame's
 * convention: pitch-from-horizontal = 90-|theta_off|, sin(90-x) = cos(x)), so holding altitude at any off-level
 * theta_off needs InterceptorHoverThrust/cos(theta_off) - not a fixed constant good at one angle only, and NOT
 * trimmed/rescaled to force an exact match at any one calibrated angle either (tried, see TRANSITION_THEORY.md #8:
 * forcing the curve through a single (angle, thrust) point distorts every OTHER angle on the curve, which is what
 * made steep targets ground-strike during TRANSITION even though the shallow/validated angle looked fine). This is a
 * FEEDFORWARD ESTIMATE ONLY; ClimbTrim on the Python/guidance side (wroom_pilot.py) closes the real loop once CRUISE
 * starts, exactly where GPS/altitude feedback already lives for this board (no StateEstimation/PathFollower here).
 * Capped so a near-90 deg target cannot divide toward infinity; 6.0 covers up to acos(1/6) = ~80 deg, inside the -60
 * to -85 deg range TRANSITION_THEORY.md #4/#7 flags as this airframe's likely cruise band. */
#define INTERCEPTOR_MAX_TILT_GAIN 6.0f
enum { INTERCEPTOR_CLIMB = 0, INTERCEPTOR_TRANSITION, INTERCEPTOR_CRUISE };
static struct {
    bool    active;
    uint8_t phase;
    float   t_phase;
    float   psi_ref;         /* held heading, deg */
    float   theta_off;       /* current pitch offset, deg (0 = hover) */
    float   roll_off;        /* entry-blend-only roll offset, deg (0 outside the entry blend) */
    float   entry_roll;      /* attitude AT THE INSTANT the mode was engaged, deg - the entry blend fades from here */
    float   entry_pitch;
    float   live_frac;       /* 0..1, stick authority during CRUISE - ramps in, never steps */
    float   thrust_auto;     /* what the mode commands while it owns the throttle */
    bool    thrust_captured;
} interceptor;

/* Quadshot-style heading: continuous through 90 deg of pitch as long as roll stays under 90 deg */
static float interceptor_heading(const AttitudeStateData *a)
{
    if (fabsf(a->Roll) < 90.0f) {
        return a->Yaw - sinf(INTERCEPTOR_DEG2RAD(a->Pitch)) * a->Roll;
    }
    return (a->Pitch > 0.0f) ? a->Yaw - a->Roll : a->Yaw + a->Roll;
}

/* thrust that holds LEVEL altitude at a thrust vector tilted theta_off_deg (pitch) AND roll_deg (roll) off vertical,
 * given InterceptorHoverThrust holds it at zero tilt. Anchored on the HOVER reference, not InterceptorClimbThrust
 * (deliberately above hover, to make CLIMB climb) - using the climb value here was tried first and made every
 * intermediate angle of the ramp wrong by whatever the sign of (ClimbThrust - true hover) was, badly enough to
 * ground-strike DURING transition at steep targets even though the curve was still exactly right at the one
 * calibrated cruise angle by construction. See TRANSITION_THEORY.md #8.
 *
 * cos(roll)*cos(pitch) is the standard small-angle-exact tilt-compensation term (same one PX4/Betaflight-style
 * altitude hold uses for a banked turn): it is the vertical component of the body +z axis after independent
 * roll-then-pitch rotation, ignoring yaw (yaw does not tilt +z relative to vertical). Pitch-only was tried first and
 * plainly missing this: a star mission leg 2026-09-19 needed a sustained ~20 deg bank to correct a large heading
 * error, and ClimbTrim cut throttle hard chasing a climb-rate error the geometric term was blind to the cause of
 * (the bank, not the ClimbTrim itself, was reading real - the bank was ALSO stealing vertical lift the pitch-only
 * formula never accounted for, so the closed loop was fighting two effects with only one visible). See
 * INTERCEPTOR_FLIGHT_LOG.md section 5. */
static inline float interceptor_level_thrust(float theta_off_deg, float roll_deg)
{
    float cos_tilt = cosf(INTERCEPTOR_DEG2RAD(theta_off_deg)) * cosf(INTERCEPTOR_DEG2RAD(roll_deg));
    float gain     = 1.0f / fmaxf(cos_tilt, 1.0f / INTERCEPTOR_MAX_TILT_GAIN);
    return stabSettings.settings.InterceptorHoverThrust * gain;
}

static void interceptor_enter(const AttitudeStateData *a)
{
    interceptor.active      = true;
    interceptor.phase       = INTERCEPTOR_CLIMB;
    interceptor.t_phase     = 0.0f;
    interceptor.psi_ref     = interceptor_heading(a);
    interceptor.entry_roll  = a->Roll;   /* the real attitude at hand-over, not an assumed level - the blend fades from here */
    interceptor.entry_pitch = a->Pitch;
    interceptor.theta_off   = interceptor.entry_pitch;
    interceptor.roll_off    = interceptor.entry_roll;
    interceptor.live_frac   = 0.0f;
    interceptor.thrust_auto = stabSettings.settings.InterceptorClimbThrust;
    interceptor.thrust_captured = false;
}

/* advance the state machine by dT; yaw_stick_rate in deg/s (magnitude already fades in via live_frac at the call
 * site); actual_roll_deg is the vehicle's REAL measured roll (not roll_off, which is a SETPOINT and is zero outside
 * the entry blend) - it is what the thrust curve needs to know about during CRUISE, when a steering bank the pilot
 * or the autopilot commanded is real lift loss the pitch-only formula was blind to (see interceptor_level_thrust()'s
 * comment and INTERCEPTOR_FLIGHT_LOG.md section 5's leg-4 finding). */
static void interceptor_run(float dT, float yaw_stick_rate, float actual_roll_deg)
{
    interceptor.t_phase += dT;
    switch (interceptor.phase) {
    case INTERCEPTOR_CLIMB:
    {
        /* fade whatever attitude the vehicle actually had at engagement down to level - not a step to zero - so
         * flicking the switch mid-stick-input is not itself a disturbance the rate loop has to fight */
        float blend = boundf(interceptor.t_phase / INTERCEPTOR_ENTRY_BLEND_TIME, 0.0f, 1.0f);
        interceptor.theta_off   = interceptor.entry_pitch * (1.0f - blend);
        interceptor.roll_off    = interceptor.entry_roll  * (1.0f - blend);
        interceptor.thrust_auto = stabSettings.settings.InterceptorClimbThrust;
        if (interceptor.t_phase >= stabSettings.settings.InterceptorClimbTime) {
            interceptor.phase   = INTERCEPTOR_TRANSITION;
            interceptor.t_phase = 0.0f;
        }
    }
    break;
    case INTERCEPTOR_TRANSITION:
    {
        interceptor.roll_off = 0.0f;   /* entry blend is long done by the time transition starts (ClimbTime > ENTRY_BLEND_TIME) */
        float target = stabSettings.settings.InterceptorCruisePitch;
        float step   = fabsf(stabSettings.settings.InterceptorTransitionRate) * dT;
        if (fabsf(target - interceptor.theta_off) <= step) {
            interceptor.theta_off = target;
            interceptor.phase     = INTERCEPTOR_CRUISE;
            interceptor.t_phase   = 0.0f;
        } else {
            interceptor.theta_off += (target > interceptor.theta_off) ? step : -step;
        }
        interceptor.thrust_auto = interceptor_level_thrust(interceptor.theta_off, actual_roll_deg);
    }
    break;
    case INTERCEPTOR_CRUISE:
    default:
        interceptor.roll_off    = 0.0f;
        interceptor.theta_off   = stabSettings.settings.InterceptorCruisePitch;
        interceptor.thrust_auto = interceptor_level_thrust(interceptor.theta_off, actual_roll_deg);
        interceptor.live_frac   = boundf(interceptor.live_frac + dT / INTERCEPTOR_LIVE_BLEND_TIME, 0.0f, 1.0f);
        interceptor.psi_ref    += yaw_stick_rate * dT;
        while (interceptor.psi_ref > 180.0f) { interceptor.psi_ref -= 360.0f; }
        while (interceptor.psi_ref < -180.0f) { interceptor.psi_ref += 360.0f; }
        break;
    }
}

static inline bool interceptor_sticks_live(void)
{
    return interceptor.active && interceptor.phase == INTERCEPTOR_CRUISE;
}


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
    /* AXES is 4 (stabilization.h) and the per-axis loop below iterates
     * t=0..AXES-1, so it reaches t=3 (Thrust). These arrays were declared
     * with only three elements on every target except the simulator, which
     * made each t=3 access -- stabilizationAltitudeHold()'s input AND
     * rateDesiredAxis[3]'s output -- read and write one float past the end of
     * a stack array, on the flight controller, every control cycle. That is
     * undefined behaviour, not a style question, and the compiler flags it
     * (-Warray-bounds). Sized to AXES with Thrust included on all targets.
     */
    float stabilizationDesiredAxis[AXES] = {stabilizationDesired.Roll, stabilizationDesired.Pitch, stabilizationDesired.Yaw, stabilizationDesired.Thrust};
    float rateDesiredAxis[AXES] = {rateDesired.Roll, rateDesired.Pitch, rateDesired.Yaw, rateDesired.Thrust};
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
            case STABILIZATIONSTATUS_OUTERLOOP_INTERCEPTOR:
            case STABILIZATIONSTATUS_OUTERLOOP_WEAKLEVELING:
                rpy_desired[t] = stabilizationDesiredAxis[t];
                break;
            case STABILIZATIONSTATUS_OUTERLOOP_DIRECT:
            default:
                rpy_desired[t] = ((float *)&attitudeState.Roll)[t];
                break;
            }
        }

        /* Interceptor mode owns the whole attitude setpoint: enter on the first cycle the roll axis shows the mode, leave when it stops */
        if (StabilizationStatusOuterLoopToArray(enabled)[0] == STABILIZATIONSTATUS_OUTERLOOP_INTERCEPTOR) {
            uint8_t armed_now;
            FlightStatusArmedGet(&armed_now);
            if (!interceptor.active || armed_now != FLIGHTSTATUS_ARMED_ARMED) {
                interceptor_enter(&attitudeState);
            }
            interceptor_run(dT, interceptor.live_frac * stabilizationDesiredAxis[2], attitudeState.Roll);
            rpy_desired[0] = interceptor.roll_off  + interceptor.live_frac * stabilizationDesiredAxis[0];
            rpy_desired[1] = interceptor.theta_off + interceptor.live_frac * stabilizationDesiredAxis[1];
            rpy_desired[2] = interceptor.psi_ref;
        } else {
            interceptor.active = false;
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
            case STABILIZATIONSTATUS_OUTERLOOP_INTERCEPTOR:
            {
                /* attitude error (quaternion path) -> rate, as Attitude mode; then the Rattitude blend toward a pure stick
                 * rate at large deflection, only once the sticks are live. Yaw: the heading is held by psi_ref, which the
                 * yaw stick slews inside interceptor_run(), so the error term alone is right here. */
                float att_rate = pid_apply(&stabSettings.outerPids[t], local_error[t], dT);
                if (t < 2 && interceptor_sticks_live()) {
                    float stickinput[2];
                    stickinput[0] = boundf(stabilizationDesiredAxis[0] / stabSettings.stabBank.RollMax, -1.0f, 1.0f);
                    stickinput[1] = boundf(stabilizationDesiredAxis[1] / stabSettings.stabBank.PitchMax, -1.0f, 1.0f);
                    float manual_rate = StabilizationBankManualRateToArray(stabSettings.stabBank.ManualRate)[t];
                    float stick_rate  = stickinput[t] * manual_rate;
                    att_rate = boundf(att_rate, -manual_rate, manual_rate);
                    float magnitude = fmaxf(fabsf(stickinput[0]), fabsf(stickinput[1]));
                    if (magnitude <= stabSettings.rattitude_mode_transition_stick_position) {
                        magnitude *= 0.618033989f / stabSettings.rattitude_mode_transition_stick_position;
                    } else {
                        magnitude = (magnitude - stabSettings.rattitude_mode_transition_stick_position)
                                    * (1.0f - 0.618033989f) / (1.0f - stabSettings.rattitude_mode_transition_stick_position) + 0.618033989f;
                    }
                    /* live_frac fades this blend IN over INTERCEPTOR_LIVE_BLEND_TIME - at the instant CRUISE starts a
                     * held-over stick deflection contributes nothing yet, so hand-over is never a rate step */
                    magnitude *= interceptor.live_frac;
                    att_rate = (1.0f - magnitude) * att_rate + magnitude * stick_rate;
                }
                rateDesiredAxis[t] = att_rate;
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
#if defined(REVOLUTION) || defined(LITEWING)
            case STABILIZATIONSTATUS_OUTERLOOP_ALTITUDE:
                rateDesiredAxis[t] = stabilizationAltitudeHold(stabilizationDesiredAxis[t], ALTITUDEHOLD, reinit);
                break;
            case STABILIZATIONSTATUS_OUTERLOOP_ALTITUDEVARIO:
                rateDesiredAxis[t] = stabilizationAltitudeHold(stabilizationDesiredAxis[t], ALTITUDEVARIO, reinit);
                break;
#endif /* REVOLUTION || LITEWING */
            case STABILIZATIONSTATUS_OUTERLOOP_INTERCEPTOR:
                /* the mode owns the throttle until the pilot's stick passes through the auto value (within 5%), then the
                 * stick has it - so the hand-over never steps the thrust */
                if (interceptor_sticks_live() && !interceptor.thrust_captured &&
                    fabsf(stabilizationDesiredAxis[t] - interceptor.thrust_auto) < 0.05f) {
                    interceptor.thrust_captured = true;
                }
                rateDesiredAxis[t] = interceptor.thrust_captured ? stabilizationDesiredAxis[t] : interceptor.thrust_auto;
                break;
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

    /* Trust the loop's per-mode switch rather than bypassing it.
     *
     * This used to copy stabilizationDesired.Thrust -- the RAW, pre-outer-loop
     * stick input -- over whatever the switch above had just computed for
     * t=3, which discarded stabilizationAltitudeHold()'s PID output on every
     * cycle. Altitude hold therefore could not move the throttle at all on
     * real hardware: confirmed in the air, the pilot flying the whole time on
     * manual thrust with the mode selected.
     *
     * For every other thrust mode this changes nothing. DIRECT and
     * CruiseControl fall to the switch's default case, which assigns
     * rateDesiredAxis[3] = stabilizationDesiredAxis[3], i.e. exactly
     * stabilizationDesired.Thrust. Only ALTITUDEHOLD/ALTITUDEVARIO differ,
     * and only because they previously did nothing.
     */
    rateDesired.Thrust = rateDesiredAxis[3];

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
            PIOS_SHMLOG_Printf("[SIMPOSIX-IFDEF-MARKER] outerloop.c AttitudeStateUpdatedCb: t=%.3f callCount=%u\n",
                   wallclock, (unsigned)callCount);
            /* shmlog: no flush */
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
