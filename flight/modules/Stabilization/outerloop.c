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
#include <pios_math.h>
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
#include <pathdesired.h>
#include <positionstate.h>
#include <velocitystate.h>


#include <stabilization.h>
#include <cruisecontrol.h>
#include <altitudeloop.h>
#include <CoordinateConversions.h>
#include <plans.h>

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
/* 0.8 -> 0.15 (2026-09-24, real reproduced problem): a mid-flight trigger
 * (ground/gazebo_bridge.py's altitude-aligned dive trigger, entering this
 * mode from an already-armed, already-flying PositionHold engagement
 * rather than a ground launch) found this 0.8s dead window ate most of its
 * available reaction time - control.roll's PN steering command was
 * computing real, growing corrections from the moment of entry, but
 * live_frac scaled them toward zero for the first ~0.8s, by which point
 * the target had already drifted off the captured heading with no time
 * left to correct. 0.8s was chosen only to stay "much shorter than a
 * typical few-second ClimbTime" for the ground-launch case this was
 * designed around - it was never load-bearing at that specific value, and
 * a shorter blend is still smooth (no attitude step, same mechanism) while
 * costing that case nothing it was relying on. */
#define INTERCEPTOR_LIVE_BLEND_TIME  0.15f
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
    /* InterceptorThrustIgnoreRoll (2026-09-24): drop the roll term from the
     * feedforward on request. Correct physics for a TRIMMED, steady
     * attitude - wrong for a short, aggressive engagement that ALSO
     * commands a live roll correction on top of an already-ramping pitch:
     * any added roll, correcting the right way or not, pushes MORE thrust
     * into an already-delicate vertical balance. See this field's own
     * comment in stabilizationsettings.xml and TRANSITION_THEORY.md #26.6
     * for the three independent lateral-correction attempts that all
     * failed the same intermittent way before this was added. Default
     * FALSE leaves every existing use (including wroom_pilot.py's own
     * longer-engagement PN steering) bit-for-bit unchanged. */
    if (stabSettings.settings.InterceptorThrustIgnoreRoll == STABILIZATIONSETTINGS_INTERCEPTORTHRUSTIGNOREROLL_TRUE) {
        roll_deg = 0.0f;
    }
    float cos_tilt = cosf(INTERCEPTOR_DEG2RAD(theta_off_deg)) * cosf(INTERCEPTOR_DEG2RAD(roll_deg));
    float gain     = 1.0f / fmaxf(cos_tilt, 1.0f / INTERCEPTOR_MAX_TILT_GAIN);
    return stabSettings.settings.InterceptorHoverThrust * gain;
}

/* ---- ONBOARD FINAL-LEG INTERCEPT GUIDANCE (2026-09-24, extended same day for NOSE-AIM pitch) ---------------------
 * Ports the numerically-robust lead-point design already proven in flight/libraries/paths.c's path_intercept() (the
 * hover-mode PathFollower intercept - this project's own ~0.40-0.60m closest-approach baseline) into THIS state
 * machine's TRANSITION/CRUISE phases, replacing a fragile ground-bridge Python "dive tilt" hack that chased the same
 * problem at 20Hz over a lossy UDP relay and never got clean (TRANSITION_THEORY.md #26.6-26.9: three root causes
 * there, all ultimately from computing heading/lead-time out of noisy INSTANTANEOUS measurements).
 *
 * Two choices make this version safe where the Python one was not:
 *  1. OWN HEADING is attitudeState.Yaw - the INS's own filtered estimate - never re-derived from velocity. The
 *     Python side had no such estimate to read and reconstructed heading via atan2(velocity), which goes to noise
 *     the moment horizontal speed is small relative to vertical - exactly a steep dive (root cause #1 there).
 *  2. t_lead uses path.EndingVelocity - the ground bridge's own already-intentional closing-speed parameter (the
 *     same value it hands path_intercept() for hover-mode intercept), not a live measurement and not a separately
 *     invented constant - range/vmax with vmax fixed for the duration of one lead calculation cannot blow up. A LIVE
 *     speed can and did (root cause #3 there: it passed near-zero during the pitch-over and sent t_lead to 8s,
 *     aiming 70+ degrees off and saturating the bank). Floored at 0.1f, matching path_intercept()'s own defensive
 *     floor exactly rather than picking a fresh number.
 *
 * NOSE-AIM PITCH (direct user requirement, 2026-09-24): "never ever should you NOT have the object in camera view
 * while in pursuit." A fixed InterceptorCruisePitch cannot do this even in principle - it has no relationship to
 * where the target actually is. Tail-sitter frame convention: theta_off=0 is hover, nose straight up (elevation
 * 90deg above the horizon); theta_off=-90 is level cruise, nose horizontal (elevation 0deg) - in general
 * nose_elevation_deg = 90 + theta_off. So aiming the nose at the lead point's true elevation is
 * theta_off = elevation_to_lead_point_deg - 90, computed from the SAME lead point the bank correction already
 * targets, not a second, independent guess. This directly explains a previously-open question from earlier in this
 * project ("why doesn't the camera ever see the ball"): the old fixed -45deg constant points the nose 45deg ABOVE
 * the horizon even against a target the dive trigger has already altitude-aligned (dead level, ~0deg elevation) -
 * the miss was never a tuning problem, pitch and target elevation were simply never connected.
 *
 * Reads PathDesired the same way the ground bridge already feeds path_intercept() for hover-mode intercept (see
 * paths.c) - no new ground-side plumbing required. Both outputs are 0/unset (existing behaviour: static roll_off=0,
 * caller's own InterceptorCruisePitch) whenever PathDesired.Mode isn't PATHDESIRED_MODE_INTERCEPT, so a plain dive
 * with no target in track behaves exactly as before either of these were added. */
/* KP is a first-cut tuning value with no equivalent to borrow - path_intercept() commands a velocity VECTOR
 * directly rather than closing a bearing-error loop with a gain, so there is nothing analogous in this codebase to
 * reuse the way the three constants below are reused. Flagged here so it reads as "picked, needs validation", not
 * "derived". */
#define INTERCEPTOR_INTERCEPT_KP           1.2f    /* deg commanded bank per deg bearing error */
/* The remaining three all borrow an already-validated constant from paths.c's path_intercept() (this project's own
 * ~0.40-0.60m baseline) instead of inventing separate numbers for the identical purpose - the earlier version of
 * this function used its own 35deg/90deg-per-s/6s and got caught for it: none had any relationship to a value this
 * exact codebase already tunes for the same job. */
#define INTERCEPTOR_INTERCEPT_MAX_BANK_DEG stabSettings.stabBank.RollMax   /* the airframe's own configured roll limit, not a second one */
#define INTERCEPTOR_INTERCEPT_MAX_SLEW_DPS 60.0f   /* = paths.c INTERCEPT_MAX_TURN_RATE */
#define INTERCEPTOR_INTERCEPT_MAX_LEAD_S   2.5f    /* = paths.c INTERCEPT_ENDGAME_MAX_LEAD_S */
/* TWO FIXES TRIED AND REVERTED (2026-09-25) for the residual "closes to ~3m then re-opens" pattern:
 * 1. Dropping the bank/pitch slew limit inside path_intercept()'s own INTERCEPT_ENDGAME_DIST (4m), on the theory
 *    the pattern was a reaction-lag problem a faster response would fix. A matched 3-seed check showed it uniformly
 *    WORSE (5.50/5.49/5.66m vs. 5.51/3.30/3.72m) - proof this is a KINEMATIC pure-pursuit overshoot, not a lag one:
 *    this vehicle commits to real forward airspeed and a real turn radius once in CRUISE, and reacting faster to
 *    the instantaneous bearing does not fix a flight path that geometrically cannot curve tightly enough on top of
 *    an already-poor approach angle - it just overcorrects harder.
 * 2. path_intercept()'s own GENERAL-case steering (constant-bearing via cross-LOS decomposition, matching the
 *    target's cross-range velocity to hold bearing fixed while closing range) ported from its velocity-vector
 *    output to a heading. The vector math is an exact match to paths.c and is not itself wrong - but it is the
 *    WRONG TOOL for this vehicle: PN deliberately steers OFF the direct target bearing to null cross-track motion,
 *    which is fine for a hover-capable vehicle whose camera can point independently of its flight direction, and
 *    is exactly what the user watched happen live ("hooked away... sign flip in the spline curve" - it was not a
 *    sign error, it was PN doing its job). For THIS tail-sitter, heading IS flight direction once in CRUISE, so
 *    steering off the direct bearing at all means the nose - and the camera - comes off the target, directly
 *    violating "never ever should you NOT have the object in camera view while in pursuit." PN and permanent
 *    nose-lock are incompatible for an airframe with no independent camera gimbal; do not retry PN/cross-LOS here
 *    without one. */
/* Pitch has NO proportional gain, unlike bank: theta_off = elevation_deg - 90 is an exact geometric identity (the
 * nose-aim requirement), not a control law being tuned toward a setpoint - see block comment. */

struct interceptor_aim {
    float bank_deg;   /* interceptor.roll_off setpoint */
    float pitch_deg;  /* interceptor.theta_off setpoint */
    bool  tracking;   /* false: PathDesired isn't in INTERCEPT mode - caller should use its own fallback pitch */
};

static struct interceptor_aim interceptor_intercept_aim(float dT, float actual_yaw_deg)
{
    static float lastBank  = 0.0f;
    static float lastPitch = 0.0f;
    struct interceptor_aim aim = { 0.0f, 0.0f, false };

    PathDesiredData path;
    PathDesiredGet(&path);
    if (path.Mode != PATHDESIRED_MODE_INTERCEPT) {
        lastBank  = 0.0f;
        lastPitch = 0.0f;
        return aim;
    }
    aim.tracking = true;

    PositionStateData pos;
    PositionStateGet(&pos);

    float Rn    = path.End.North - pos.North;
    float Re    = path.End.East  - pos.East;
    float range = sqrtf(Rn * Rn + Re * Re);
    if (range < 1e-3f) {
        aim.bank_deg  = lastBank;
        aim.pitch_deg = lastPitch;
        return aim;
    }

    float Vtn = path.ModeParameters[PATHDESIRED_MODEPARAMETER_INTERCEPT_TARGETVELN];
    float Vte = path.ModeParameters[PATHDESIRED_MODEPARAMETER_INTERCEPT_TARGETVELE];
    float vmax = path.EndingVelocity;
    if (vmax < 0.1f) {
        vmax = 0.1f;
    }
    float t_lead = range / vmax;
    if (t_lead > INTERCEPTOR_INTERCEPT_MAX_LEAD_S) {
        t_lead = INTERCEPTOR_INTERCEPT_MAX_LEAD_S;
    }
    /* Short-horizon lead point, used for BOTH bank/bearing and pitch/elevation, at every range - see this
     * function's own block comment for the two range-dependent alternatives tried and reverted. Always aiming
     * directly at this point (never a PN-style off-bearing correction) is what keeps the nose - and the camera -
     * on the target throughout pursuit, which is the harder, non-negotiable requirement here. */
    float lead_n = path.End.North + Vtn * t_lead;
    float lead_e = path.End.East  + Vte * t_lead;
    float lead_d = path.End.Down  + path.ModeParameters[PATHDESIRED_MODEPARAMETER_INTERCEPT_TARGETVELD] * t_lead;
    float dn = lead_n - pos.North;
    float de = lead_e - pos.East;
    if (dn * dn + de * de < 1e-6f) {
        aim.bank_deg  = lastBank;
        aim.pitch_deg = lastPitch;
        return aim;
    }

    /* ---- azimuth (bank/heading) ---- */
    float desired_bearing_deg = RAD2DEG(atan2f(de, dn));
    float bear_err = desired_bearing_deg - actual_yaw_deg;
    while (bear_err > 180.0f) { bear_err -= 360.0f; }
    while (bear_err < -180.0f) { bear_err += 360.0f; }

    float bank = boundf(INTERCEPTOR_INTERCEPT_KP * bear_err,
                         -INTERCEPTOR_INTERCEPT_MAX_BANK_DEG, INTERCEPTOR_INTERCEPT_MAX_BANK_DEG);
    float maxBankStep = INTERCEPTOR_INTERCEPT_MAX_SLEW_DPS * dT;
    float dBank = bank - lastBank;
    if (dBank > maxBankStep) { bank = lastBank + maxBankStep; } else if (dBank < -maxBankStep) { bank = lastBank - maxBankStep; }
    lastBank = bank;

    /* ---- elevation (pitch/nose-aim) - see block comment for the frame-convention derivation ---- */
    float horiz_range   = sqrtf(dn * dn + de * de);
    float vertical_gap  = pos.Down - lead_d;   /* +ve: lead point is ABOVE us */
    float elevation_deg = RAD2DEG(atan2f(vertical_gap, horiz_range));
    float pitch_desired = elevation_deg - 90.0f;
    float maxPitchStep   = INTERCEPTOR_INTERCEPT_MAX_SLEW_DPS * dT;
    float dPitch = pitch_desired - lastPitch;
    if (dPitch > maxPitchStep) { pitch_desired = lastPitch + maxPitchStep; } else if (dPitch < -maxPitchStep) { pitch_desired = lastPitch - maxPitchStep; }
    lastPitch = pitch_desired;

    aim.bank_deg  = bank;
    aim.pitch_deg = pitch_desired;
    return aim;
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
static void interceptor_run(float dT, float yaw_stick_rate, float actual_roll_deg, float actual_yaw_deg)
{
    interceptor.t_phase += dT;

    /* GROUND-COMMANDED STEERING NOW RAMPS IN FROM ENGAGEMENT, NOT FROM CRUISE (2026-09-20, real
     * user-caught design flaw, not a physical constraint): this used to live inside the CRUISE
     * case only, meaning live_frac - and therefore ALL ground-commanded roll/pitch/yaw correction,
     * since the blend at the call site (rpy_desired[t] = .._off + live_frac*stabilizationDesiredAxis[t])
     * already runs every phase unconditionally - stayed pinned at exactly 0.0 for the entire CLIMB
     * and TRANSITION duration (climb_s+transition_s, ~6-7s at typical settings). During CLIMB the
     * vehicle is near-hover under mostly-vertical thrust - exactly the regime where banking/yawing
     * costs the least - so there was never a physical reason to withhold steering there; it was an
     * accident of where this one increment happened to be written, not a deliberate design choice.
     * The real-world cost was severe: any ground-side guidance had to pre-compute a single aim
     * point BEFORE engaging and then fly blind on it for the whole climb+transition, with no way to
     * correct for an inbound target's own motion or any error in predicting how long that blind
     * window would actually last. Ramping live_frac from t=0 (bounded to 1.0 well before CRUISE
     * even starts, given INTERCEPTOR_LIVE_BLEND_TIME=0.8s << a typical few-second ClimbTime) means
     * the ground side can track a moving target continuously from the moment interceptor mode
     * engages, the same way any other guided phase of flight does - closing the actual gap this
     * bug caused, not working around it with more precomputation. Still fades in over
     * INTERCEPTOR_LIVE_BLEND_TIME rather than snapping to 1.0, for the same reason it always did:
     * flicking the switch mid-stick-input should not itself be a disturbance the rate loop has to
     * fight. Yaw's own psi_ref integration moves out of the CRUISE-only case for the identical
     * reason - it was the other half of "sticks are live," gated by the same accident. */
    interceptor.live_frac = boundf(interceptor.live_frac + dT / INTERCEPTOR_LIVE_BLEND_TIME, 0.0f, 1.0f);
    interceptor.psi_ref  += yaw_stick_rate * dT;
    while (interceptor.psi_ref > 180.0f) { interceptor.psi_ref -= 360.0f; }
    while (interceptor.psi_ref < -180.0f) { interceptor.psi_ref += 360.0f; }

    /* Called once per tick regardless of phase (not just from CRUISE) so its internal slew-rate state stays warm
     * across the TRANSITION->CRUISE handoff (no step), and so aiming starts the moment a target is in track rather
     * than waiting for CRUISE to begin - see this function's own block comment for why "aim throughout pursuit,
     * not just at the end" is a hard requirement here, not a nicety. */
    struct interceptor_aim aim = interceptor_intercept_aim(dT, actual_yaw_deg);

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
        /* entry blend is long done by the time transition starts (ClimbTime > ENTRY_BLEND_TIME); once a target is
         * in track, aim at it from here rather than waiting for CRUISE - see interceptor_intercept_aim()'s comment */
        interceptor.roll_off = aim.tracking ? aim.bank_deg : 0.0f;
        float target = aim.tracking ? aim.pitch_deg : stabSettings.settings.InterceptorCruisePitch;
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
        /* onboard final-leg intercept guidance, both axes - see interceptor_intercept_aim()'s own block comment.
         * Falls back to the old fixed roll_off=0/InterceptorCruisePitch behaviour whenever PathDesired isn't in
         * INTERCEPT mode, so a plain dive with no target in track is unchanged from before this was added. */
        interceptor.roll_off    = aim.tracking ? aim.bank_deg  : 0.0f;
        interceptor.theta_off   = aim.tracking ? aim.pitch_deg : stabSettings.settings.InterceptorCruisePitch;
        interceptor.thrust_auto = interceptor_level_thrust(interceptor.theta_off, actual_roll_deg);
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
            interceptor_run(dT, interceptor.live_frac * stabilizationDesiredAxis[2], attitudeState.Roll, attitudeState.Yaw);
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
