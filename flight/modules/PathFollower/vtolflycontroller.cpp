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

    // look ahead kFF seconds
    float cur[3] = { positionState.North + (velocityState.North * vtolPathFollowerSettings->CourseFeedForward),
                     positionState.East + (velocityState.East * vtolPathFollowerSettings->CourseFeedForward),
                     positionState.Down + (velocityState.Down * vtolPathFollowerSettings->CourseFeedForward) };
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

                // Distance at which the nose starts swinging to the NEXT leg.
                // The turn has to be FINISHED on arrival, so the vehicle lands
                // on the point already pointing down the next leg and can
                // accelerate straight out of it. A 144deg hairpin takes 4.1s at
                // the 35deg/s slew, so the lookahead has to cover at least that
                // much flying time.
                //
                // What makes 3.5m safe now is that it is no longer 3.5m of
                // CRUISING. An early attempt at 4.0m (star79) rotated the
                // vehicle while it was still at full leg speed and cost the
                // vertical channel badly (altitude peak-to-peak 0.08 -> 0.65m).
                // With PATH_ARRIVAL_GAIN lowered to 0.45 the vehicle is already
                // decelerating from ~2.2m out, so most of the rotation now
                // happens while it is slowing onto the point rather than while
                // it is crossing the leg.
                // The yaw command slews at yawSlewDps (35 deg/s) and a star
                // hairpin is ~144 deg = ~4.1s; the last few metres of a
                // decelerating approach take about that long. Measured on
                // star77, before this existed: the vehicle was still rotating
                // 106->180 deg as it reached the final waypoint and settled
                // only at the instant the waypoint switched - a hook in the
                // landing, and a bend at the start of every leg.
                const float PRETURN_DIST = 3.5f;
                if (distToEnd < PRETURN_DIST) {
                    mPreTurnBearing = pathDesired->ModeParameters[PATHDESIRED_MODEPARAMETER_FOLLOWVECTOR_NEXTBEARING];
                    mPreTurnActive  = true;
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

    float angle_radians = DEG2RAD(attitudeState.Yaw);
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
            // Tried 60 deg/s (star80) to make a 144deg hairpin take 2.4s
            // instead of 4.1s, so the turn could finish while parked on the
            // waypoint. It bought the best cross-track and arrival numbers of
            // the session (0.17m / 0.09m) and paid for them in exactly the
            // place the ultimate period predicted: yaw RMS 8.4 -> 15.3 deg,
            // peak-to-peak 48 -> 90 deg, and the mission stretched 118s ->
            // 169s as waypoints waited out the hunting. Reverted.
            const float yawSlewDps = 35.0f;
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
