/*
 ******************************************************************************
 *
 * @file       vtolflycontroller.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2015.
 * @brief      Class implements the fly controller for vtols
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
#include <openpilot.h>

#include <callbackinfo.h>

#include <math.h>
#ifdef SIMPOSIX
#include <stdio.h>
#endif
#include <pid.h>
#include <CoordinateConversions.h>
#include <sin_lookup.h>
#include <pathdesired.h>
#include <paths.h>
#include "plans.h"
#include <sanitycheck.h>

#include <accelstate.h>
#include <vtolpathfollowersettings.h>
#include <flightstatus.h>
#include <flightmodesettings.h>
#include <pathstatus.h>
#include <positionstate.h>
#include <velocitystate.h>
#include <velocitydesired.h>
#include <stabilizationdesired.h>
#include <attitudestate.h>
#include <gyrostate.h>
#include <takeofflocation.h>
#include <poilocation.h>
#include <manualcontrolcommand.h>
#include <systemsettings.h>
#include <stabilizationbank.h>
#include <stabilizationdesired.h>
#include <vtolselftuningstats.h>
#include <pathsummary.h>
}

// C++ includes
#include "vtolflycontroller.h"
#include "pathfollowerfsm.h"
#include "pidcontroldown.h"
#include "pidcontrolne.h"

// Private constants
#define DEADBAND_HIGH                                        0.10f
#define DEADBAND_LOW                                         -0.10f
#define RTB_LAND_FRACTIONAL_PROGRESS_START_CHECKS            0.95f
#define RTB_LAND_NE_DISTANCE_REQUIRED_TO_START_LAND_SEQUENCE 2.0f

// pointer to a singleton instance
VtolFlyController *VtolFlyController::p_inst = 0;

VtolFlyController::VtolFlyController()
    : vtolPathFollowerSettings(NULL), mActive(false), mManualThrust(false), mMode(0), vtolEmergencyFallback(0.0f), vtolEmergencyFallbackSwitch(false)
{}

// Called when mode first engaged
void VtolFlyController::Activate(void)
{
    if (!mActive) {
        mActive = true;
        mManualThrust = false;
        SettingsUpdated();
        controlDown.Activate();
        controlNE.Activate();
        mMode = pathDesired->Mode;

        vtolEmergencyFallback = 0.0f;
        vtolEmergencyFallbackSwitch = false;
        mYawCommandActive = false;
        mPreTurnActive    = false;
        mPreTurnBearing   = 0.0f;
        // A fresh engagement must not inherit the last one's slew state.
        path_intercept_reset();
    }
}

uint8_t VtolFlyController::IsActive(void)
{
    return mActive;
}

uint8_t VtolFlyController::Mode(void)
{
    return mMode;
}

// Objective updated in pathdesired
void VtolFlyController::ObjectiveUpdated(void)
{}


void VtolFlyController::Deactivate(void)
{
    if (mActive) {
        mActive = false;
        mManualThrust = false;
        controlDown.Deactivate();
        controlNE.Deactivate();
        vtolEmergencyFallback = 0.0f;
        vtolEmergencyFallbackSwitch = false;
    }
}


void VtolFlyController::SettingsUpdated(void)
{
    const float dT = vtolPathFollowerSettings->UpdatePeriod / 1000.0f;

    controlNE.UpdateParameters(vtolPathFollowerSettings->HorizontalVelPID.Kp,
                               vtolPathFollowerSettings->HorizontalVelPID.Ki,
                               vtolPathFollowerSettings->HorizontalVelPID.Kd,
                               vtolPathFollowerSettings->HorizontalVelPID.ILimit,
                               dT,
                               vtolPathFollowerSettings->HorizontalVelMax);
    controlNE.UpdatePositionalParameters(vtolPathFollowerSettings->HorizontalPosP);
    controlNE.UpdateCommandParameters(-vtolPathFollowerSettings->MaxRollPitch, vtolPathFollowerSettings->MaxRollPitch, vtolPathFollowerSettings->VelocityFeedforward);

    controlDown.UpdateParameters(vtolPathFollowerSettings->VerticalVelPID.Kp,
                                 vtolPathFollowerSettings->VerticalVelPID.Ki,
                                 vtolPathFollowerSettings->VerticalVelPID.Kd,
                                 vtolPathFollowerSettings->VerticalVelPID.ILimit, // TODO Change to BETA
                                 dT,
                                 vtolPathFollowerSettings->VerticalVelMax);
    controlDown.UpdatePositionalParameters(vtolPathFollowerSettings->VerticalPosP);

    VtolSelfTuningStatsData vtolSelfTuningStats;
    VtolSelfTuningStatsGet(&vtolSelfTuningStats);
    controlDown.UpdateNeutralThrust(vtolSelfTuningStats.NeutralThrustOffset + vtolPathFollowerSettings->ThrustLimits.Neutral);
    controlDown.SetThrustLimits(vtolPathFollowerSettings->ThrustLimits.Min, vtolPathFollowerSettings->ThrustLimits.Max);
}

/**
 * Initialise the module, called on startup
 * \returns 0 on success or -1 if initialisation failed
 */
int32_t VtolFlyController::Initialize(VtolPathFollowerSettingsData *ptr_vtolPathFollowerSettings)
{
    PIOS_Assert(ptr_vtolPathFollowerSettings);

    vtolPathFollowerSettings = ptr_vtolPathFollowerSettings;

    return 0;
}


/**
 * Compute desired velocity from the current position and path
 */
void VtolFlyController::UpdateVelocityDesired()
{
    PositionStateData positionState;

    PositionStateGet(&positionState);

    VelocityStateData velocityState;
    VelocityStateGet(&velocityState);
    controlNE.UpdateVelocityState(velocityState.North, velocityState.East);
    controlDown.UpdateVelocityState(velocityState.Down);

    VelocityDesiredData velocityDesired;

    // Look ahead kFF seconds.
    //
    // The lead term is what lets the follower brake for a waypoint in time,
    // and it earns its keep: cutting it 1.0s -> 0.25s (star96) let the vehicle
    // sail 0.95m past every corner and stretched the mission to 286s.
    // Clamping it to half the remaining distance so the prediction can never
    // cross the target (star97) is the same trade in milder form - 0.69m of
    // overshoot, 198s. Predicting PAST the waypoint is not a bug to be
    // engineered away here; it is the signal that stops the vehicle. Left
    // alone it gives the smallest overshoot measured, 0.21m.
    float kFF = vtolPathFollowerSettings->CourseFeedForward;
    float cur[3] = { positionState.North + (velocityState.North * kFF),
                     positionState.East + (velocityState.East * kFF),
                     positionState.Down + (velocityState.Down * kFF) };
    struct path_status progress;
    path_progress(pathDesired, cur, &progress, true);

    // ================= CORNER LOOKAHEAD (heading only) =================
    // Scope note, learned expensively: this steers YAW and NOTHING ELSE.
    //
    // An earlier version of this block also rewrote translation through the
    // corner (an APPROACH braking profile plus a bounded ARRIVE park). That
    // code could never run - it was gated on pathDesired->ModeParameters[3],
    // which nothing in the firmware ever set - so it sat here for many runs
    // looking like the thing that was flying the corners while paths.c's
    // trapezoidal profile actually was. The first flight in which it did run
    // (star78, once the planner started publishing the bearing) stuck at
    // waypoint 1, drifted 4.1m past the point and swung altitude over a 7.6m
    // range. The reason is structural: `progress` is shared with controlDown,
    // so rewriting path_vector[0]/[1] and correction_vector[0]/[1] here while
    // leaving [2] and fractional_progress as path_progress computed them
    // hands the vertical controller an inconsistent path. It has been removed
    // rather than left disabled.
    //
    // Braking into a corner is already owned by the leg speed profile in
    // paths.c, and stopping ON the point is owned by the mission's
    // confirmed-arrival policy (pathplanner.c conditionDistanceToTarget).
    // Those two produced 0.11m mean arrival accuracy with this block inert.
    // What was genuinely missing was heading: the follower only knew the leg
    // it was on, so it met each corner with no rotation started and left it
    // still turning, which bent the first metres of the next leg.
    mPreTurnActive = false;
    if (vtolPathFollowerSettings->YawControl == VTOLPATHFOLLOWERSETTINGS_YAWCONTROL_PATHDIRECTION
        || vtolPathFollowerSettings->YawControl == VTOLPATHFOLLOWERSETTINGS_YAWCONTROL_MOVEMENTDIRECTION) {
        float legN   = pathDesired->End.North - pathDesired->Start.North;
        float legE   = pathDesired->End.East - pathDesired->Start.East;
        float legLen = sqrtf(legN * legN + legE * legE);

        // Only real corners get a lookahead: a straight-through waypoint, or
        // the last leg (which has no successor and so no valid bearing), is
        // flown with the ordinary leg heading.
        if (pathDesired->ModeParameters[PATHDESIRED_MODEPARAMETER_FOLLOWVECTOR_NEXTBEARINGVALID] > 0.5f && legLen > 1e-3f) {
            float turn = pathDesired->ModeParameters[PATHDESIRED_MODEPARAMETER_FOLLOWVECTOR_NEXTBEARING] - RAD2DEG(atan2f(legE, legN));
            while (turn > 180.0f) {
                turn -= 360.0f;
            }
            while (turn < -180.0f) {
                turn += 360.0f;
            }
            if (fabsf(turn) > 25.0f) {
                float dN = pathDesired->End.North - positionState.North;
                float dE = pathDesired->End.East - positionState.East;
                float distToEnd = sqrtf(dN * dN + dE * dE);

                // Distance over which the nose swings from this leg's bearing
                // to the next one's.
                const float PRETURN_DIST = 7.0f;
                // ...and the distance at which the turn must be FINISHED. The
                // blend used to run all the way to the waypoint, so the nose
                // was still rotating through the final approach - and because
                // yaw rotates the NE->body mapping, that rotation curls the
                // ground track. Measured at wp4: the vehicle arced from 0.57m
                // north of the point out to 0.58m east of it and back before
                // settling, a visible loop at every corner. Finishing the turn
                // a metre out leaves the last stretch a straight, purely
                // translational run-in.
                //
                // But the standoff alone made the curl WORSE (2.04x -> 2.50x
                // path/straight-line over the final 2m), because compressing
                // the same 144deg into 4m->1m instead of 4m->0m RAISES the
                // yaw rate during translation. The curl is driven by rate:
                // the roll/pitch command is computed from the current yaw,
                // and by the time the vehicle achieves that attitude the yaw
                // has moved on, so the achieved acceleration is rotated by
                // roughly (yaw rate x attitude lag). Spreading the turn over
                // MORE distance is what lowers it - 7m to 1m is 144deg over
                // 6m (~29 deg/s at cruise) against 4m over 3m (~47 deg/s).
                const float PRETURN_FINISH = 1.0f;
                if (distToEnd < PRETURN_DIST) {
                    // Blend the heading as a function of DISTANCE REMAINING,
                    // not at a fixed rate.
                    //
                    // Snapping the target to the next leg's bearing and
                    // letting the slew limiter ramp through it at a constant
                    // 35 deg/s produced a visibly jagged S on the way into
                    // every corner: the vehicle starts rotating abruptly,
                    // turns at a rate unrelated to how fast it is closing,
                    // and then stops just as abruptly. Because yaw rotates
                    // the NE->body mapping, each of those rate steps kicks
                    // the translation sideways.
                    //
                    // Keying the blend to distance ties the rotation to the
                    // approach itself: the nose leads the corner in and is
                    // exactly on the new bearing at the point, whatever speed
                    // the vehicle happens to be doing. Smoothstep makes the
                    // rate start and finish at zero, so there is no step at
                    // either end - which is the difference between a car
                    // steering into a corner and one that yanks the wheel.
                    float frac = (PRETURN_DIST - distToEnd)
                                 / (PRETURN_DIST - PRETURN_FINISH);
                    frac = boundf(frac, 0.0f, 1.0f);
                    frac = frac * frac * (3.0f - 2.0f * frac);
                    mPreTurnBearing = RAD2DEG(atan2f(legE, legN)) + frac * turn;
                    mPreTurnActive  = true;

                    // NOTE: rotating the along-track FEED-FORWARD into the
                    // turn by this same fraction was tried and is badly wrong.
                    // Near the vertex the rotation approaches the full 144deg,
                    // so the commanded velocity points down the NEXT leg while
                    // the vehicle is still flying the current one - it stops
                    // tracking the leg it is on. The corner geometry has to
                    // come from the PATH (a real swept/arc corner in the
                    // planner), not from spinning the follower's feed-forward
                    // vector underneath an otherwise straight-line leg.
                }
            }
        }
    }

    controlNE.ControlPositionWithPath(&progress);
    if (!mManualThrust) {
        controlDown.ControlPositionWithPath(&progress);
    }

    float north, east;
    controlNE.GetVelocityDesired(&north, &east);
    velocityDesired.North = north;
    velocityDesired.East  = east;
    if (!mManualThrust) {
        velocityDesired.Down = controlDown.GetVelocityDesired();
    } else { velocityDesired.Down = 0.0f; }

#ifdef SIMPOSIX
    {
        static uint32_t dbgCount = 0;
        if ((dbgCount++ % 100) == 0) {
            printf("[SIMPOSIX-IFDEF-MARKER] vtolfly: posD=%.2f velD_state=%.2f corr=(%.2f,%.2f,%.2f) "
                   "pathv=(%.2f,%.2f,%.2f) velDesired=(%.2f,%.2f,%.2f) manualThrust=%d\n",
                   (double)positionState.Down, (double)velocityState.Down,
                   (double)progress.correction_vector[0], (double)progress.correction_vector[1], (double)progress.correction_vector[2],
                   (double)progress.path_vector[0], (double)progress.path_vector[1], (double)progress.path_vector[2],
                   (double)velocityDesired.North, (double)velocityDesired.East, (double)velocityDesired.Down,
                   (int)mManualThrust);
            fflush(stdout);
        }
    }
#endif

    // update pathstatus
    pathStatus->error = progress.error;
    pathStatus->fractional_progress  = progress.fractional_progress;
    pathStatus->path_direction_north = progress.path_vector[0];
    pathStatus->path_direction_east  = progress.path_vector[1];
    pathStatus->path_direction_down  = progress.path_vector[2];

    pathStatus->correction_direction_north = progress.correction_vector[0];
    pathStatus->correction_direction_east  = progress.correction_vector[1];
    pathStatus->correction_direction_down  = progress.correction_vector[2];

    VelocityDesiredSet(&velocityDesired);
}


int8_t VtolFlyController::UpdateStabilizationDesired(bool yaw_attitude, float yaw_direction)
{
    uint8_t result = 1;
    StabilizationDesiredData stabDesired;
    AttitudeStateData attitudeState;
    StabilizationBankData stabSettings;
    float northCommand;
    float eastCommand;

    StabilizationDesiredGet(&stabDesired);
    AttitudeStateGet(&attitudeState);
    StabilizationBankGet(&stabSettings);

    controlNE.GetNECommand(&northCommand, &eastCommand);

    // Convert the NED command to body frame using PREDICTED yaw, not
    // current yaw.
    //
    // The attitude loop takes ~130ms to achieve a commanded tilt (relay
    // autotune: roll 113ms, pitch 155ms). If the body is yawing, the tilt is
    // achieved in a frame that has rotated ~ yawRate*lag past the one it was
    // computed in, so the applied acceleration lands rotated IN the yaw
    // direction. While BRAKING (command anti-parallel to travel) a
    // clockwise-rotated brake vector has an error component pointing LEFT of
    // travel - integrate that over a 5s braking approach with the corner
    // pre-turn sweeping yaw right at 35 deg/s and you get ~0.5m of leftward
    // drift arriving at every corner. That drift seeded the left-handed
    // "cursive-l" loop observed at star vertices across dozens of runs, and
    // its isolation was empirical: identical stop-corner missions flew +570
    // deg LEFT curls with yaw-following on (star132) and near-clean corners
    // with it off (star133 control). Compensating with predicted yaw aims
    // the thrust vector where it will be needed when it is actually achieved.
    GyroStateData gyroState;
    GyroStateGet(&gyroState);
    const float YAW_LAG_COMP_S = 0.26f; // PROBE: 2x - if this flips the residual drift RIGHT, bracket and interpolate
    float angle_radians = DEG2RAD(attitudeState.Yaw + gyroState.z * YAW_LAG_COMP_S);
    float cos_angle     = cosf(angle_radians);
    float sine_angle    = sinf(angle_radians);
    float maxPitch = vtolPathFollowerSettings->MaxRollPitch;
    stabDesired.StabilizationMode.Pitch = STABILIZATIONDESIRED_STABILIZATIONMODE_ATTITUDE;
    stabDesired.Pitch = boundf(-northCommand * cos_angle - eastCommand * sine_angle, -maxPitch, maxPitch); // this should be in the controller
    stabDesired.StabilizationMode.Roll  = STABILIZATIONDESIRED_STABILIZATIONMODE_ATTITUDE;
    stabDesired.Roll = boundf(-northCommand * sine_angle + eastCommand * cos_angle, -maxPitch, maxPitch);

    ManualControlCommandData manualControl;
    ManualControlCommandGet(&manualControl);

    // TODO The below need to be rewritten because the PID implementation has changed.
#if 0
    // DEBUG HACK: allow user to skew compass on purpose to see if emergency failsafe kicks in
    if (vtolPathFollowerSettings->FlyawayEmergencyFallback == VTOLPATHFOLLOWERSETTINGS_FLYAWAYEMERGENCYFALLBACK_DEBUGTEST) {
        attitudeState.Yaw += 120.0f;
        if (attitudeState.Yaw > 180.0f) {
            attitudeState.Yaw -= 360.0f;
        }
    }


    if ( // emergency flyaway detection
        ( // integral already at its limit
            vtolPathFollowerSettings.HorizontalVelPID.ILimit - fabsf(global.PIDvel[0].iAccumulator) < 1e-6f ||
            vtolPathFollowerSettings.HorizontalVelPID.ILimit - fabsf(global.PIDvel[1].iAccumulator) < 1e-6f
        ) &&
        // angle between desired and actual velocity >90 degrees (by dot product)
        (velocityDesired.North * velocityState.North + velocityDesired.East * velocityState.East < 0.0f) &&
        // quad is moving at significant speed (during flyaway it would keep speeding up)
        squaref(velocityState.North) + squaref(velocityState.East) > 1.0f
        ) {
        vtolEmergencyFallback += dT;
        if (vtolEmergencyFallback >= vtolPathFollowerSettings->FlyawayEmergencyFallbackTriggerTime) {
            // after emergency timeout, trigger alarm - everything else is handled by callers
            // (switch to emergency algorithm, switch to emergency waypoint in pathplanner, alarms, ...)
            result = 0;
        }
    } else {
        vtolEmergencyFallback = 0.0f;
    }
#endif // if 0

    if (yaw_attitude) {
        stabDesired.StabilizationMode.Yaw = STABILIZATIONDESIRED_STABILIZATIONMODE_ATTITUDE;
        stabDesired.Yaw = yaw_direction;
    } else {
        stabDesired.StabilizationMode.Yaw = STABILIZATIONDESIRED_STABILIZATIONMODE_AXISLOCK;
        stabDesired.Yaw = stabSettings.MaximumRate.Yaw * manualControl.Yaw;
    }

    // default thrust mode to cruise control
    stabDesired.StabilizationMode.Thrust = STABILIZATIONDESIRED_STABILIZATIONMODE_CRUISECONTROL;

    if (mManualThrust) {
        stabDesired.Thrust = manualControl.Thrust;
    } else {
        stabDesired.Thrust = controlDown.GetDownCommand();
    }

    StabilizationDesiredSet(&stabDesired);

    return result;
}

/**
 * Compute desired attitude for vtols - emergency fallback
 */
void VtolFlyController::UpdateDesiredAttitudeEmergencyFallback()
{
    VelocityDesiredData velocityDesired;
    VelocityStateData velocityState;
    StabilizationDesiredData stabDesired;

    float courseError;
    float courseCommand;

    VelocityStateGet(&velocityState);
    VelocityDesiredGet(&velocityDesired);

    ManualControlCommandData manualControlData;
    ManualControlCommandGet(&manualControlData);

    courseError = RAD2DEG(atan2f(velocityDesired.East, velocityDesired.North) - atan2f(velocityState.East, velocityState.North));

    if (courseError < -180.0f) {
        courseError += 360.0f;
    }
    if (courseError > 180.0f) {
        courseError -= 360.0f;
    }


    courseCommand   = (courseError * vtolPathFollowerSettings->EmergencyFallbackYawRate.kP);
    stabDesired.Yaw = boundf(courseCommand, -vtolPathFollowerSettings->EmergencyFallbackYawRate.Max, vtolPathFollowerSettings->EmergencyFallbackYawRate.Max);

    controlDown.UpdateVelocitySetpoint(velocityDesired.Down);
    controlDown.UpdateVelocityState(velocityState.Down);
    stabDesired.Thrust = controlDown.GetDownCommand();


    stabDesired.Roll   = vtolPathFollowerSettings->EmergencyFallbackAttitude.Roll;
    stabDesired.Pitch  = vtolPathFollowerSettings->EmergencyFallbackAttitude.Pitch;

    if (vtolPathFollowerSettings->ThrustControl == VTOLPATHFOLLOWERSETTINGS_THRUSTCONTROL_MANUAL) {
        stabDesired.Thrust = manualControlData.Thrust;
    }

    stabDesired.StabilizationMode.Roll   = STABILIZATIONDESIRED_STABILIZATIONMODE_ATTITUDE;
    stabDesired.StabilizationMode.Pitch  = STABILIZATIONDESIRED_STABILIZATIONMODE_ATTITUDE;
    stabDesired.StabilizationMode.Yaw    = STABILIZATIONDESIRED_STABILIZATIONMODE_RATE;
    stabDesired.StabilizationMode.Thrust = STABILIZATIONDESIRED_STABILIZATIONMODE_CRUISECONTROL;
    StabilizationDesiredSet(&stabDesired);
}


void VtolFlyController::UpdateAutoPilot()
{
    if (vtolPathFollowerSettings->ThrustControl == VTOLPATHFOLLOWERSETTINGS_THRUSTCONTROL_MANUAL) {
        mManualThrust = true;
    }

    uint8_t result = RunAutoPilot();

    if (result) {
        AlarmsSet(SYSTEMALARMS_ALARM_GUIDANCE, SYSTEMALARMS_ALARM_OK);
    } else {
        pathStatus->Status = PATHSTATUS_STATUS_CRITICAL;
        AlarmsSet(SYSTEMALARMS_ALARM_GUIDANCE, SYSTEMALARMS_ALARM_WARNING);
    }

    PathStatusSet(pathStatus);

    // If rtbl, detect arrival at the endpoint and then triggers a change
    // to the pathDesired to initiate a Landing sequence. This is the simpliest approach. plans.c
    // can't manage this.  And pathplanner whilst similar does not manage this as it is not a
    // waypoint traversal and is not aware of flight modes other than path plan.
    // The mode check is NOT redundant. ModeParameters is a union of per-mode
    // payloads, so slot 0 only means "next command" when the mode is
    // GoToEndpoint; in other modes it holds something else entirely (a
    // FollowVector leg cruise speed of 1.5 m/s casts to (uint8_t)1, which is
    // exactly RETURNTOBASENEXTCOMMAND_LAND). Without this guard the vehicle
    // flew its first waypoint and then landed itself in mid-mission.
    if (pathDesired->Mode == PATHDESIRED_MODE_GOTOENDPOINT
        && (uint8_t)pathDesired->ModeParameters[PATHDESIRED_MODEPARAMETER_GOTOENDPOINT_NEXTCOMMAND] == FLIGHTMODESETTINGS_RETURNTOBASENEXTCOMMAND_LAND) {
        if (pathStatus->fractional_progress > RTB_LAND_FRACTIONAL_PROGRESS_START_CHECKS) {
            if (fabsf(pathStatus->correction_direction_north) < RTB_LAND_NE_DISTANCE_REQUIRED_TO_START_LAND_SEQUENCE && fabsf(pathStatus->correction_direction_east) < RTB_LAND_NE_DISTANCE_REQUIRED_TO_START_LAND_SEQUENCE) {
                plan_setup_land();
            }
        }
    }
}
/**
 * vtol autopilot
 * use hover capable algorithm with unlimeted movement calculation. if that fails (flyaway situation due to compass failure)
 * fall back to emergency fallback autopilot to keep minimum amount of flight control
 */
uint8_t VtolFlyController::RunAutoPilot()
{
    enum { RETURN_0 = 0, RETURN_1 = 1, RETURN_RESULT } returnmode;
    enum { FOLLOWER_REGULAR, FOLLOWER_FALLBACK } followermode;
    uint8_t result = 0;

    // decide on behaviour based on settings and system state
    if (vtolEmergencyFallbackSwitch) {
        returnmode   = RETURN_0;
        followermode = FOLLOWER_FALLBACK;
    } else {
        if (vtolPathFollowerSettings->FlyawayEmergencyFallback == VTOLPATHFOLLOWERSETTINGS_FLYAWAYEMERGENCYFALLBACK_ALWAYS) {
            returnmode   = RETURN_1;
            followermode = FOLLOWER_FALLBACK;
        } else {
            returnmode   = RETURN_RESULT;
            followermode = FOLLOWER_REGULAR;
        }
    }

    switch (followermode) {
    case FOLLOWER_REGULAR:
    {
        // horizontal position control PID loop works according to settings in regular mode, allowing integral terms
        UpdateVelocityDesired();

        // yaw behaviour is configurable in vtolpathfollower, select yaw control algorithm
        bool yaw_attitude = true;
        float yaw = 0.0f;

        switch (vtolPathFollowerSettings->YawControl) {
        case VTOLPATHFOLLOWERSETTINGS_YAWCONTROL_MANUAL:
            yaw_attitude = false;
            break;
        case VTOLPATHFOLLOWERSETTINGS_YAWCONTROL_TAILIN:
            yaw = updateTailInBearing();
            break;
        case VTOLPATHFOLLOWERSETTINGS_YAWCONTROL_MOVEMENTDIRECTION:
            yaw = updateCourseBearing();
            break;
        case VTOLPATHFOLLOWERSETTINGS_YAWCONTROL_PATHDIRECTION:
            yaw = updatePathBearing();
            break;
        case VTOLPATHFOLLOWERSETTINGS_YAWCONTROL_POI:
            yaw = updatePOIBearing();
            break;
        }

        if (yaw_attitude) {
            // Slew the yaw COMMAND toward the selected bearing instead of
            // feeding the attitude loop a step. A waypoint switch flips the
            // path bearing instantly (a hairpin by ~144 degrees); presented
            // as a step, the yaw loop saturates its rate demand for seconds
            // and the fight for mixer authority on weak-yaw-torque
            // airframes costs roll/pitch control - three consecutive
            // tip-overs at the same star hairpin (roll/pitch reaching
            // 65-81 degrees) traced to exactly this, at several different
            // MaximumRate.Yaw caps. With the command slewed the loop error
            // stays small at all times and yaw authority is never
            // saturated. 30 deg/s crosses a hairpin in ~5s, matching the
            // corner-deceleration speeds the missions fly.
            // 60 deg/s under a MaximumRate.Yaw of 90, so the loop keeps
            // tracking headroom above the command. This is aggressive for
            // an airframe whose yaw is 8x weaker than roll, and it is only
            // safe BECAUSE of the point-turn gate below: turns now happen
            // while the vehicle is stationary, where roll/pitch need almost
            // no mixer authority, so yaw may consume it. Before the gate,
            // yaw and translation overlapped and this much yaw demand tipped
            // the vehicle over. Relay autotune measured this airframe's
            // yaw ultimate period at 560ms vs 114ms for roll - yaw is ~5x
            // slower to respond, so the command must be correspondingly
            // gentler or the loop is forever chasing a target it cannot reach.
            // 35 deg/s, and this is a CEILING set by the airframe, not a
            // preference. Relay autotune measured this vehicle's yaw ultimate
            // period at 560ms vs 114ms for roll - yaw responds ~5x slower, so
            // a command slewed faster than the loop can track is just an error
            // signal the loop chases and overshoots.
            //
            // 35 -> 50, but its ROLE changed. It used to be the thing that
            // shaped the corner turn, ramping a stepped target at a constant
            // rate; now the corner blend above shapes the turn as a smooth
            // function of distance and this is only a safety cap for the rest
            // of the time. A pure rate limit set too high is dangerous: 60
            // deg/s driving a stepped target (star80) took yaw RMS from 8.4
            // to 15.3 deg and stretched the mission to 169s. Driving a
            // smoothly blended target it should rarely bind at all.
            const float yawSlewDps = 50.0f;
            float dT = vtolPathFollowerSettings->UpdatePeriod * 0.001f;
            if (!mYawCommandActive) {
                AttitudeStateData attitude;
                AttitudeStateGet(&attitude);
                mYawCommand = attitude.Yaw;
                mYawCommandActive = true;
            }
            float step = yaw - mYawCommand;
            while (step > 180.0f) {
                step -= 360.0f;
            }
            while (step < -180.0f) {
                step += 360.0f;
            }
            step = boundf(step, -yawSlewDps * dT, yawSlewDps * dT);
            mYawCommand += step;
            while (mYawCommand > 180.0f) {
                mYawCommand -= 360.0f;
            }
            while (mYawCommand < -180.0f) {
                mYawCommand += 360.0f;
            }
            yaw = mYawCommand;
        } else {
            mYawCommandActive = false;
        }

        result = UpdateStabilizationDesired(yaw_attitude, yaw);

        if (!result) {
            if (vtolPathFollowerSettings->FlyawayEmergencyFallback != VTOLPATHFOLLOWERSETTINGS_FLYAWAYEMERGENCYFALLBACK_DISABLED) {
                // switch to emergency follower if follower indicates problems
                vtolEmergencyFallbackSwitch = true;
            }
        }
    }
    break;
    case FOLLOWER_FALLBACK:
    {
        // fallback loop only cares about intended horizontal flight direction, simplify control behaviour accordingly
        controlNE.UpdatePositionalParameters(1.0f);
        UpdateVelocityDesired();

        // emergency follower has no return value
        UpdateDesiredAttitudeEmergencyFallback();
    }
    break;
    }

    switch (returnmode) {
    case RETURN_RESULT:
        return result;

    default:
        // returns either 0 or 1 according to enum definition above
        return returnmode;
    }
}


/**
 * Compute bearing of current takeoff location
 */
float VtolFlyController::updateTailInBearing()
{
    PositionStateData p;

    PositionStateGet(&p);
    TakeOffLocationData t;
    TakeOffLocationGet(&t);
    // atan2f always returns in between + and - 180 degrees
    return RAD2DEG(atan2f(p.East - t.East, p.North - t.North));
}


/**
 * Compute bearing of current movement direction
 */
float VtolFlyController::updateCourseBearing()
{
    VelocityStateData v;

    VelocityStateGet(&v);
    // atan2f always returns in between + and - 180 degrees
    return RAD2DEG(atan2f(v.East, v.North));
}


/**
 * Compute bearing of current path direction
 */
float VtolFlyController::updatePathBearing()
{
    // Bearing of the LEG ITSELF (Start -> End), not of progress.path_vector.
    // path_vector is a *velocity* vector: for GoToEndpoint (and for
    // FollowVector once past the endpoint, where path_progress falls back to
    // endpoint homing) it points from the vehicle AT the endpoint, so it
    // swings through large angles - and spins outright - as the vehicle
    // passes close to the waypoint. Feeding that to the yaw attitude loop
    // made the nose whip around at every waypoint. The leg direction is
    // constant for the whole leg and only steps at waypoint transitions,
    // where the yaw command slew smooths it.
    // Inside the corner, aim at the leg we are about to fly, not the one we
    // are finishing. See PRETURN_DIST in UpdateVelocityDesired.
    if (mPreTurnActive) {
        return mPreTurnBearing;
    }

    float dn = pathDesired->End.North - pathDesired->Start.North;
    float de = pathDesired->End.East - pathDesired->Start.East;

    if ((dn * dn + de * de) < 1e-6f) {
        // Degenerate leg (e.g. a pure climb, or a hold): keep current heading
        // rather than yawing to a meaningless bearing.
        AttitudeStateData attitude;
        AttitudeStateGet(&attitude);
        return attitude.Yaw;
    }

    // atan2f always returns in between + and - 180 degrees
    return RAD2DEG(atan2f(de, dn));
}


/**
 * Compute bearing between current position and POI
 */
float VtolFlyController::updatePOIBearing()
{
    PoiLocationData poi;

    PoiLocationGet(&poi);
    PositionStateData positionState;
    PositionStateGet(&positionState);

    const float dT = vtolPathFollowerSettings->UpdatePeriod / 1000.0f;
    float dLoc[3];
    float yaw = 0;
    /*float elevation = 0;*/

    dLoc[0] = positionState.North - poi.North;
    dLoc[1] = positionState.East - poi.East;
    dLoc[2] = positionState.Down - poi.Down;

    if (dLoc[1] < 0) {
        yaw = RAD2DEG(atan2f(dLoc[1], dLoc[0])) + 180.0f;
    } else {
        yaw = RAD2DEG(atan2f(dLoc[1], dLoc[0])) - 180.0f;
    }
    ManualControlCommandData manualControlData;
    ManualControlCommandGet(&manualControlData);

    float pathAngle = 0;
    if (manualControlData.Roll > DEADBAND_HIGH) {
        pathAngle = -(manualControlData.Roll - DEADBAND_HIGH) * dT * 300.0f;
    } else if (manualControlData.Roll < DEADBAND_LOW) {
        pathAngle = -(manualControlData.Roll - DEADBAND_LOW) * dT * 300.0f;
    }

    return yaw + (pathAngle / 2.0f);
}
