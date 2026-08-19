/**
 ******************************************************************************
 * @addtogroup OpenPilotModules OpenPilot Modules
 * @{
 * @addtogroup PathPlanner Path Planner Module
 * @brief Executes a series of waypoints
 * @{
 *
 * @file       pathplanner.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @brief      Executes a series of waypoints
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

#include "openpilot.h"

#include "callbackinfo.h"
#include "pathplan.h"
#include "flightstatus.h"
#include "airspeedstate.h"
#include "pathaction.h"
#include "pathdesired.h"
#include "pathstatus.h"
#include "positionstate.h"
#include "velocitystate.h"
#include "waypoint.h"
#include "waypointactive.h"
#include "flightmodesettings.h"
#include <systemsettings.h>
#include "paths.h"
#include "plans.h"
#include <sanitycheck.h>
#include <vtolpathfollowersettings.h>

// Private constants
#define STACK_SIZE_BYTES            1024
#define TASK_PRIORITY               CALLBACK_TASK_NAVIGATION
#define MAX_QUEUE_SIZE              2
#define PATH_PLANNER_UPDATE_RATE_MS 100 // can be slow, since we listen to status updates as well
// How far off to the side the vehicle may be when it crosses the waypoint
// plane and still be credited with reaching it, as a multiple of the
// acceptance radius. Generous enough that a legitimate swept corner counts,
// tight enough that a flyaway crossing the plane 5m wide does not.
#define CORRIDOR_FACTOR             3.0f

// Private types

// Private functions
static void pathPlannerTask();
static void commandUpdated(UAVObjEvent *ev);
static void statusUpdated(UAVObjEvent *ev);
static void updatePathDesired();
static void setWaypoint(uint16_t num);

static uint8_t checkPathPlan();
static void savePathPlan();
static void savePathProgress();
static void restorePathPlan();
static uint8_t pathConditionCheck();
static uint8_t conditionNone();
static uint8_t conditionTimeOut();
static uint8_t conditionDistanceToTarget();
static uint8_t conditionLegRemaining();
static uint8_t conditionBelowError();
static uint8_t conditionAboveAltitude();
static uint8_t conditionAboveSpeed();
static uint8_t conditionPointingTowardsNext();
static uint8_t conditionPythonScript();
static uint8_t conditionImmediate();
static void SettingsUpdatedCb(__attribute__((unused)) UAVObjEvent *ev);


// Private variables
static DelayedCallbackInfo *pathPlannerHandle;
static DelayedCallbackInfo *pathDesiredUpdaterHandle;
static WaypointActiveData waypointActive;
static WaypointData waypoint;
static PathActionData pathAction;
static bool pathplanner_active = false;
static uint16_t arrivalDwell = 0;   // ticks confirmed at the waypoint
static FrameType_t frameType;
static bool mode3D;

extern FrameType_t GetCurrentFrameType();


/**
 * MISSION PERSISTENCE (NinjaPilot)
 * ---------------------------------------------------------------------
 * Waypoint / PathAction / PathPlan are DATA objects (settings="false"),
 * so nothing ever wrote them to storage: a reboot lost the whole plan
 * and PLAN went back to orange with the aircraft holding no mission.
 * These helpers mirror the RAM plan into the same flashfs the settings
 * use, and restore it at boot.
 *
 * Write policy - deliberately conservative, because this file is shared
 * with the STM32 targets where a flash erase blocks the bus for
 * milliseconds:
 *   - the PLAN is written only when it changes AND the craft is
 *     DISARMED (i.e. at upload time), never in flight;
 *   - PROGRESS (WaypointActive) is written per waypoint transition, and
 *     only where storage is cheap (PIOS_REALPOSIX = files on Linux).
 * Nothing here ever re-engages a mission by itself - see the note on
 * resume in savePathProgress().
 */
static void savePathPlan()
{
    PathPlanData pathPlan;

    PathPlanGet(&pathPlan);

    for (uint16_t i = 0; i < pathPlan.WaypointCount; i++) {
        UAVObjSave(WaypointHandle(), i);
    }
    for (uint16_t i = 0; i < pathPlan.PathActionCount; i++) {
        UAVObjSave(PathActionHandle(), i);
    }
    UAVObjSave(PathPlanHandle(), 0);
}

static void savePathProgress()
{
    /* Records WHERE the mission was, so a reboot can be resumed from the
     * last completed waypoint instead of the start - and so a post-crash
     * teardown can say which leg was flying. It does NOT resume by
     * itself: on a multirotor a reboot stops the motors, so "continue
     * the mission" is a decision for a pilot on the ground (or a
     * fixed-wing with a sub-second MCU reset), never an automatic
     * action by code that just woke up not knowing where it is. */
#if defined(PIOS_REALPOSIX)
    UAVObjSave(WaypointActiveHandle(), 0);
#endif
}

static void restorePathPlan()
{
    PathPlanData pathPlan;

    if (UAVObjLoad(PathPlanHandle(), 0) != 0) {
        return;                       /* nothing stored - normal first boot */
    }
    PathPlanGet(&pathPlan);
    if (pathPlan.WaypointCount == 0
        || pathPlan.WaypointCount > 255 || pathPlan.PathActionCount > 255) {
        return;                       /* implausible - ignore the store */
    }
    for (uint16_t i = 0; i < pathPlan.WaypointCount; i++) {
        if (UAVObjGetNumInstances(WaypointHandle()) <= i) {
            UAVObjCreateInstance(WaypointHandle(), NULL);
        }
        if (UAVObjLoad(WaypointHandle(), i) != 0) {
            return;                   /* partial store - checkPathPlan will reject */
        }
    }
    for (uint16_t i = 0; i < pathPlan.PathActionCount; i++) {
        if (UAVObjGetNumInstances(PathActionHandle()) <= i) {
            UAVObjCreateInstance(PathActionHandle(), NULL);
        }
        if (UAVObjLoad(PathActionHandle(), i) != 0) {
            return;
        }
    }
    /* progress, if it was recorded - published for the GCS/pilot to see;
     * the plan is NOT engaged here */
    UAVObjLoad(WaypointActiveHandle(), 0);

    /* the flight side re-validates the CRC in checkPathPlan() exactly as
     * it does for an uploaded plan, so a corrupted store cannot arm a
     * bogus mission - it just leaves PLAN orange */
}

/**
 * Module initialization
 */
int32_t PathPlannerStart()
{
    plan_initialize();

    /* bring any stored mission back into RAM before the callbacks
     * fire, so a reboot comes up with its plan intact */
    restorePathPlan();

    // when the active waypoint changes, update pathDesired
    WaypointConnectCallback(commandUpdated);
    WaypointActiveConnectCallback(commandUpdated);
    PathActionConnectCallback(commandUpdated);
    PathStatusConnectCallback(statusUpdated);
    SettingsUpdatedCb(NULL);
    SystemSettingsConnectCallback(&SettingsUpdatedCb);
    VtolPathFollowerSettingsConnectCallback(&SettingsUpdatedCb);

    // Start main task callback
    PIOS_CALLBACKSCHEDULER_Dispatch(pathPlannerHandle);

    return 0;
}

/**
 * Module initialization
 */
int32_t PathPlannerInitialize()
{
    PathPlanInitialize();
    PathActionInitialize();
    PathStatusInitialize();
    PathDesiredInitialize();
    PositionStateInitialize();
    AirspeedStateInitialize();
    VelocityStateInitialize();
    WaypointInitialize();
    WaypointActiveInitialize();

    pathPlannerHandle = PIOS_CALLBACKSCHEDULER_Create(&pathPlannerTask, CALLBACK_PRIORITY_REGULAR, TASK_PRIORITY, CALLBACKINFO_RUNNING_PATHPLANNER0, STACK_SIZE_BYTES);
    pathDesiredUpdaterHandle = PIOS_CALLBACKSCHEDULER_Create(&updatePathDesired, CALLBACK_PRIORITY_CRITICAL, TASK_PRIORITY, CALLBACKINFO_RUNNING_PATHPLANNER1, STACK_SIZE_BYTES);

    return 0;
}

MODULE_INITCALL(PathPlannerInitialize, PathPlannerStart);


static void SettingsUpdatedCb(__attribute__((unused)) UAVObjEvent *ev)
{
    uint8_t TreatCustomCraftAs;

    VtolPathFollowerSettingsTreatCustomCraftAsGet(&TreatCustomCraftAs);

    frameType = GetCurrentFrameType();

    if (frameType == FRAME_TYPE_CUSTOM) {
        switch (TreatCustomCraftAs) {
        case VTOLPATHFOLLOWERSETTINGS_TREATCUSTOMCRAFTAS_FIXEDWING:
            frameType = FRAME_TYPE_FIXED_WING;
            break;
        case VTOLPATHFOLLOWERSETTINGS_TREATCUSTOMCRAFTAS_VTOL:
            frameType = FRAME_TYPE_MULTIROTOR;
            break;
        case VTOLPATHFOLLOWERSETTINGS_TREATCUSTOMCRAFTAS_GROUND:
            frameType = FRAME_TYPE_GROUND;
            break;
        }
    }

    switch (frameType) {
    case FRAME_TYPE_GROUND:
        mode3D = false;
        break;
    default:
        mode3D = true;
    }
}


/**
 * Module task
 */
static void pathPlannerTask()
{
    PIOS_CALLBACKSCHEDULER_Schedule(pathPlannerHandle, PATH_PLANNER_UPDATE_RATE_MS, CALLBACK_UPDATEMODE_SOONER);

    bool endCondition = false;

    // check path plan validity early to raise alarm
    // even if not in guided mode
    uint8_t validPathPlan = checkPathPlan();

    FlightStatusData flightStatus;
    FlightStatusGet(&flightStatus);

    /* mirror a freshly validated plan to storage - disarmed only, so the
     * write never lands in flight */
    static uint8_t lastSavedCrc;
    static bool    haveSavedCrc;
    if (validPathPlan && flightStatus.Armed == FLIGHTSTATUS_ARMED_DISARMED) {
        PathPlanData pp;
        PathPlanGet(&pp);
        if (!haveSavedCrc || pp.Crc != lastSavedCrc) {
            savePathPlan();
            lastSavedCrc = pp.Crc;
            haveSavedCrc = true;
        }
    }

    if (flightStatus.ControlChain.PathPlanner != FLIGHTSTATUS_CONTROLCHAIN_TRUE) {
        pathplanner_active = false;
        if (!validPathPlan) {
            // unverified path plans are only a warning while we are not in pathplanner mode
            // so it does not prevent arming. However manualcontrols safety check
            // shall test for this warning when pathplan is on the flight mode selector
            // thus a valid flight plan is a prerequirement for arming
            AlarmsSet(SYSTEMALARMS_ALARM_PATHPLAN, SYSTEMALARMS_ALARM_WARNING);
        } else {
            AlarmsClear(SYSTEMALARMS_ALARM_PATHPLAN);
        }

        return;
    }

    PathDesiredData pathDesired;
    PathDesiredGet(&pathDesired);

    static uint8_t failsafeRTHset = 0;
    if (!validPathPlan) {
        pathplanner_active = false;

        if (!failsafeRTHset) {
            failsafeRTHset = 1;
            plan_setup_positionHold();
        }
        AlarmsSet(SYSTEMALARMS_ALARM_PATHPLAN, SYSTEMALARMS_ALARM_CRITICAL);

        return;
    }

    failsafeRTHset = 0;
    AlarmsClear(SYSTEMALARMS_ALARM_PATHPLAN);

    WaypointActiveGet(&waypointActive);

    if (pathplanner_active == false) {
        pathplanner_active   = true;

        // This triggers callback to update variable
        waypointActive.Index = 0;
        WaypointActiveSet(&waypointActive);

        return;
    }

    WaypointInstGet(waypointActive.Index, &waypoint);
    PathActionInstGet(waypoint.Action, &pathAction);
    PathStatusData pathStatus;
    PathStatusGet(&pathStatus);

    // delay next step until path follower has acknowledged the path mode
    if (pathStatus.UID != pathDesired.UID) {
        return;
    }

    // negative destinations DISABLE this feature
    if (pathStatus.Status == PATHSTATUS_STATUS_CRITICAL && waypointActive.Index != pathAction.ErrorDestination && pathAction.ErrorDestination >= 0) {
        setWaypoint(pathAction.ErrorDestination);
        return;
    }

    // check if condition has been met
    endCondition = pathConditionCheck();
    // decide what to do
    switch (pathAction.Command) {
    case PATHACTION_COMMAND_ONNOTCONDITIONNEXTWAYPOINT:
        endCondition = !endCondition;
    case PATHACTION_COMMAND_ONCONDITIONNEXTWAYPOINT:
        if (endCondition) {
            setWaypoint(waypointActive.Index + 1);
        }
        break;
    case PATHACTION_COMMAND_ONNOTCONDITIONJUMPWAYPOINT:
        endCondition = !endCondition;
    case PATHACTION_COMMAND_ONCONDITIONJUMPWAYPOINT:
        if (endCondition) {
            if (pathAction.JumpDestination < 0) {
                // waypoint ids <0 code relative jumps
                setWaypoint(waypointActive.Index - pathAction.JumpDestination);
            } else {
                setWaypoint(pathAction.JumpDestination);
            }
        }
        break;
    case PATHACTION_COMMAND_IFCONDITIONJUMPWAYPOINTELSENEXTWAYPOINT:
        if (endCondition) {
            if (pathAction.JumpDestination < 0) {
                // waypoint ids <0 code relative jumps
                setWaypoint(waypointActive.Index - pathAction.JumpDestination);
            } else {
                setWaypoint(pathAction.JumpDestination);
            }
        } else {
            setWaypoint(waypointActive.Index + 1);
        }
        break;
    }
}

// safety checks for path plan integrity
static uint8_t checkPathPlan()
{
    uint16_t i;
    uint16_t waypointCount;
    uint16_t actionCount;
    uint8_t pathCrc;
    PathPlanData pathPlan;

    // WaypointData waypoint; // using global instead (?)
    // PathActionData action; // using global instead (?)

    PathPlanGet(&pathPlan);

    waypointCount = pathPlan.WaypointCount;
    if (waypointCount == 0) {
        // an empty path plan is invalid
        return false;
    }
    actionCount = pathPlan.PathActionCount;

    // check count consistency
    if (waypointCount > UAVObjGetNumInstances(WaypointHandle())) {
        // PIOS_DEBUGLOG_Printf("PathPlan : waypoint count error!");
        return false;
    }
    if (actionCount > UAVObjGetNumInstances(PathActionHandle())) {
        // PIOS_DEBUGLOG_Printf("PathPlan : path action count error!");
        return false;
    }

    // check CRC
    pathCrc = 0;
    for (i = 0; i < waypointCount; i++) {
        pathCrc = UAVObjUpdateCRC(WaypointHandle(), i, pathCrc);
    }
    for (i = 0; i < actionCount; i++) {
        pathCrc = UAVObjUpdateCRC(PathActionHandle(), i, pathCrc);
    }
    if (pathCrc != pathPlan.Crc) {
        // failed crc check
        // PIOS_DEBUGLOG_Printf("PathPlan : bad CRC (%d / %d)!", pathCrc, pathPlan.Crc);
        return false;
    }

    // waypoint consistency
    for (i = 0; i < waypointCount; i++) {
        WaypointInstGet(i, &waypoint);
        if (waypoint.Action >= actionCount) {
            // path action id is out of range
            return false;
        }
    }

    // path action consistency
    for (i = 0; i < actionCount; i++) {
        PathActionInstGet(i, &pathAction);
        if (pathAction.ErrorDestination >= waypointCount) {
            // waypoint id is out of range
            return false;
        }
        if (pathAction.JumpDestination >= waypointCount) {
            // waypoint id is out of range
            return false;
        }
    }

    // path plan passed checks

    return true;
}

// callback function when status changed, issue execution of state machine
void commandUpdated(__attribute__((unused)) UAVObjEvent *ev)
{
    PIOS_CALLBACKSCHEDULER_Dispatch(pathDesiredUpdaterHandle);
}

// callback function when waypoints changed in any way, update pathDesired
void statusUpdated(__attribute__((unused)) UAVObjEvent *ev)
{
    PIOS_CALLBACKSCHEDULER_Dispatch(pathPlannerHandle);
}


// callback function when waypoints changed in any way, update pathDesired
void updatePathDesired()
{
    // only ever touch pathDesired if pathplanner is enabled
    if (!pathplanner_active) {
        return;
    }

    PathDesiredData pathDesired;

    // find out current waypoint
    WaypointActiveGet(&waypointActive);

    WaypointInstGet(waypointActive.Index, &waypoint);
    PathActionInstGet(waypoint.Action, &pathAction);

    pathDesired.End.North = waypoint.Position.North;
    pathDesired.End.East  = waypoint.Position.East;
    pathDesired.End.Down  = waypoint.Position.Down;
    pathDesired.EndingVelocity    = waypoint.Velocity;
    pathDesired.Mode = pathAction.Mode;
    pathDesired.ModeParameters[0] = pathAction.ModeParameters[0];
    pathDesired.ModeParameters[1] = pathAction.ModeParameters[1];
    pathDesired.ModeParameters[2] = pathAction.ModeParameters[2];
    pathDesired.ModeParameters[3] = pathAction.ModeParameters[3];
    pathDesired.UID = waypointActive.Index;

    // Publish the bearing of the NEXT leg, so the path follower can see the
    // corner BEFORE it arrives:
    //     ModeParameters[2] = bearing of leg (this wp -> next wp), degrees
    //     ModeParameters[3] = 1 when that bearing is meaningful
    // Without this the follower only ever knows the leg it is currently on,
    // so it learns about a corner at the instant the waypoint switches -
    // which is precisely too late to have turned for it, and the vehicle
    // leaves the corner still rotating. That residual rotation is what bends
    // the start of the next leg.
    //
    // Only for the line-following modes: Land and the Circle modes carry
    // real payload in ModeParameters (Land's are velN/velE/velDown/options),
    // and clobbering those would break the landing.
    if (pathDesired.Mode == PATHDESIRED_MODE_FOLLOWVECTOR
        || pathDesired.Mode == PATHDESIRED_MODE_GOTOENDPOINT) {
        pathDesired.ModeParameters[PATHDESIRED_MODEPARAMETER_FOLLOWVECTOR_NEXTBEARING] = 0.0f;
        pathDesired.ModeParameters[PATHDESIRED_MODEPARAMETER_FOLLOWVECTOR_NEXTBEARINGVALID] = 0.0f;

        PathPlanData pathPlan;
        PathPlanGet(&pathPlan);
        uint16_t nextIdx = waypointActive.Index + 1;
        if (nextIdx < pathPlan.WaypointCount) {
            WaypointData nextWaypoint;
            WaypointInstGet(nextIdx, &nextWaypoint);
            float nN = nextWaypoint.Position.North - waypoint.Position.North;
            float nE = nextWaypoint.Position.East - waypoint.Position.East;
            // A zero-length next leg (a duplicated waypoint - missions end in
            // one so they can terminate in a Land action) has no bearing at
            // all. Reporting atan2f(0,0)=0 would claim "next leg heads due
            // North" and make the follower turn for a corner that does not
            // exist.
            if ((nN * nN + nE * nE) > 1e-4f) {
                pathDesired.ModeParameters[PATHDESIRED_MODEPARAMETER_FOLLOWVECTOR_NEXTBEARING] = RAD2DEG(atan2f(nE, nN));
                pathDesired.ModeParameters[PATHDESIRED_MODEPARAMETER_FOLLOWVECTOR_NEXTBEARINGVALID] = 1.0f;
            }
        }
    }

    if (waypointActive.Index == 0) {
        PositionStateData positionState;
        PositionStateGet(&positionState);
        // First waypoint has itself as start point (used to be home position but that proved dangerous when looping)

        /*pathDesired.Start[PATHDESIRED_START_NORTH] =  waypoint.Position[WAYPOINT_POSITION_NORTH];
           pathDesired.Start[PATHDESIRED_START_EAST] =  waypoint.Position[WAYPOINT_POSITION_EAST];
           pathDesired.Start[PATHDESIRED_START_DOWN] =  waypoint.Position[WAYPOINT_POSITION_DOWN];*/
        pathDesired.Start.North = positionState.North;
        pathDesired.Start.East  = positionState.East;
        pathDesired.Start.Down  = positionState.Down;
        pathDesired.StartingVelocity = pathDesired.EndingVelocity;
    } else {
        // Get previous waypoint as start point
        WaypointData waypointPrev;
        WaypointInstGet(waypointActive.Index - 1, &waypointPrev);

        pathDesired.Start.North = waypointPrev.Position.North;
        pathDesired.Start.East  = waypointPrev.Position.East;
        pathDesired.Start.Down  = waypointPrev.Position.Down;
        pathDesired.StartingVelocity = waypointPrev.Velocity;
    }
    PathDesiredSet(&pathDesired);
}

// helper function to go to a specific waypoint
static void setWaypoint(uint16_t num)
{
    PathPlanData pathPlan;

    PathPlanGet(&pathPlan);

    // here it is assumed that the path plan has been validated (waypoint count is consistent)
    if (num >= pathPlan.WaypointCount) {
        // path plans wrap around
        num = 0;
    }

    waypointActive.Index = num;
    WaypointActiveSet(&waypointActive);
    savePathProgress();
}

// execute the appropriate condition and report result
static uint8_t pathConditionCheck()
{
    // i thought about a lookup table, but a switch is safer considering there could be invalid EndCondition ID's
    switch (pathAction.EndCondition) {
    case PATHACTION_ENDCONDITION_NONE:
        return conditionNone();

        break;
    case PATHACTION_ENDCONDITION_TIMEOUT:
        return conditionTimeOut();

        break;
    case PATHACTION_ENDCONDITION_DISTANCETOTARGET:
        return conditionDistanceToTarget();

        break;
    case PATHACTION_ENDCONDITION_LEGREMAINING:
        return conditionLegRemaining();

        break;
    case PATHACTION_ENDCONDITION_BELOWERROR:
        return conditionBelowError();

        break;
    case PATHACTION_ENDCONDITION_ABOVEALTITUDE:
        return conditionAboveAltitude();

        break;
    case PATHACTION_ENDCONDITION_ABOVESPEED:
        return conditionAboveSpeed();

        break;
    case PATHACTION_ENDCONDITION_POINTINGTOWARDSNEXT:
        return conditionPointingTowardsNext();

        break;
    case PATHACTION_ENDCONDITION_PYTHONSCRIPT:
        return conditionPythonScript();

        break;
    case PATHACTION_ENDCONDITION_IMMEDIATE:
        return conditionImmediate();

        break;
    default:
        // invalid endconditions are always true to prevent freezes
        return true;

        break;
    }
}

/* the None condition is always false */
static uint8_t conditionNone()
{
    return false;
}

/**
 * the Timeout condition measures time this waypoint is active
 * Parameter 0:  timeout in seconds
 */
static uint8_t conditionTimeOut()
{
    static uint16_t toWaypoint;
    static uint32_t toStarttime;

    // reset timer if waypoint changed
    if (waypointActive.Index != toWaypoint) {
        toWaypoint  = waypointActive.Index;
        toStarttime = PIOS_DELAY_GetRaw();
    }
    if (PIOS_DELAY_DiffuS(toStarttime) >= 1e6f * pathAction.ConditionParameters[0]) {
        // make sure we reinitialize even if the same waypoint comes twice
        toWaypoint = 0xFFFF;
        return true;
    }
    return false;
}

/**
 * the DistanceToTarget measures distance to a waypoint
 * returns true if closer
 * Parameter 0:  distance in meters
 * Parameter 1:  flag: 0=2d 1=3d
 */
static uint8_t conditionDistanceToTarget()
{
    float distance;
    PositionStateData positionState;

    PositionStateGet(&positionState);
    if (pathAction.ConditionParameters[1] > 0.5f) {
        distance = sqrtf(powf(waypoint.Position.North - positionState.North, 2)
                         + powf(waypoint.Position.East - positionState.East, 2)
                         + powf(waypoint.Position.Down - positionState.Down, 2));
    } else {
        distance = sqrtf(powf(waypoint.Position.North - positionState.North, 2)
                         + powf(waypoint.Position.East - positionState.East, 2));
    }

    // HALF-PLANE ARRIVAL. A waypoint is also reached the moment the vehicle
    // CROSSES it - the plane through the waypoint perpendicular to the
    // inbound leg - regardless of how close it got.
    //
    // Without this, a vehicle that passes the point by even a few centimetres
    // is commanded straight back to it, because endpoint homing points at the
    // waypoint from wherever you are. Coming back from beyond the vertex is a
    // rotation the OPPOSITE way round from the corner itself, so the ground
    // track hooks left into a right-hand turn, loops back, and only then
    // departs. Measured: the commanded heading swings -25 deg (outbound) ->
    // +146 deg (back up the inbound leg) as the vehicle crosses, and the
    // actual track follows it round; five of six star corners hooked the
    // wrong way. It is also most of the time spent at each waypoint.
    //
    // Crossing the plane means the waypoint is behind you and the mission's
    // business there is finished. Bounded by the same acceptance radius as a
    // corridor so a vehicle that sails past far off to one side is not
    // credited with arriving.
    if (waypointActive.Index > 0) {
        WaypointData wpPrev;
        WaypointInstGet(waypointActive.Index - 1, &wpPrev);
        float legN = waypoint.Position.North - wpPrev.Position.North;
        float legE = waypoint.Position.East - wpPrev.Position.East;
        float legLen = sqrtf(legN * legN + legE * legE);
        if (legLen > 0.5f) {
            float un = legN / legLen, ue = legE / legLen;
            float relN = positionState.North - waypoint.Position.North;
            float relE = positionState.East - waypoint.Position.East;
            float along = relN * un + relE * ue;            // >0 = past it
            float cross = fabsf(-relN * ue + relE * un);    // lateral miss
            if (along > 0.0f && cross < CORRIDOR_FACTOR * pathAction.ConditionParameters[0]) {
                arrivalDwell = 0;
                return true;
            }
        }
    }

    if (distance > pathAction.ConditionParameters[0]) {
        arrivalDwell = 0;
        return false;
    }

    // CONFIRM ARRIVAL. Distance alone is not arrival: a vehicle crossing
    // the acceptance sphere at speed satisfies it while still travelling,
    // so the plan advances early and the next leg begins from the wrong
    // place. How a corner should be taken is a property of the MISSION,
    // not of the airframe or the controller, so it is expressed per
    // waypoint:
    //     ConditionParameters[2] = speed at/below which arrival counts (m/s)
    //     ConditionParameters[3] = how long it must hold that (seconds)
    // Both 0 keeps the historic distance-only behaviour, which is what a
    // fly-through waypoint (or a fixed-wing spline/loiter turn) wants. A
    // multirotor hairpin asks for a low speed and a short dwell and gets a
    // precise, confirmed stop on the point. Same firmware, same plan
    // format, different vehicles - the plan decides.
    //
    // NOTE the waypoint's own Velocity must be <= ConditionParameters[2],
    // or the leg's speed profile never lets the vehicle satisfy this and
    // the plan stalls at that waypoint (learned the hard way).
    float confirmSpeed = pathAction.ConditionParameters[2];
    if (confirmSpeed > 0.0f) {
        VelocityStateData velocityState;
        VelocityStateGet(&velocityState);
        float speed = sqrtf(velocityState.North * velocityState.North
                            + velocityState.East * velocityState.East);
        if (speed > confirmSpeed) {
            arrivalDwell = 0;
            return false;
        }
        uint16_t needed = (uint16_t)(pathAction.ConditionParameters[3] * 1000.0f
                                     / PATH_PLANNER_UPDATE_RATE_MS);
        if (arrivalDwell < needed) {
            arrivalDwell++;
            return false;
        }
    }
    arrivalDwell = 0;
    return true;
}


/**
 * the LegRemaining measures how far the pathfollower got on a linear path segment
 * returns true if closer to destination (path more complete)
 * Parameter 0:  relative distance (0= complete, 1= just starting)
 */
static uint8_t conditionLegRemaining()
{
    PathDesiredData pathDesired;
    PositionStateData positionState;

    PathDesiredGet(&pathDesired);
    PositionStateGet(&positionState);

    float cur[3] = { positionState.North, positionState.East, positionState.Down };
    struct path_status progress;

    path_progress(&pathDesired,
                  cur, &progress, mode3D);
    if (progress.fractional_progress >= 1.0f - pathAction.ConditionParameters[0]) {
        return true;
    }
    return false;
}

/**
 * the BelowError measures the error on a path segment
 * returns true if error is below margin
 * Parameter 0: error margin (in m)
 */
static uint8_t conditionBelowError()
{
    PathDesiredData pathDesired;
    PositionStateData positionState;

    PathDesiredGet(&pathDesired);
    PositionStateGet(&positionState);

    float cur[3] = { positionState.North, positionState.East, positionState.Down };
    struct path_status progress;

    path_progress(&pathDesired,
                  cur, &progress, mode3D);
    if (progress.error <= pathAction.ConditionParameters[0]) {
        return true;
    }
    return false;
}

/**
 * the AboveAltitude measures the flight altitude relative to home position
 * returns true if above critical altitude
 * WARNING! Altitudes are always negative (down coordinate)
 * Parameter 0:  altitude in meters (negative!)
 */
static uint8_t conditionAboveAltitude()
{
    PositionStateData positionState;

    PositionStateGet(&positionState);

    if (positionState.Down <= pathAction.ConditionParameters[0]) {
        return true;
    }
    return false;
}

/**
 * the AboveSpeed measures the movement speed (3d)
 * returns true if above critical speed
 * Parameter 0:  speed in m/s
 * Parameter 1:  flag: 0=groundspeed 1=airspeed
 */
static uint8_t conditionAboveSpeed()
{
    VelocityStateData velocityState;

    VelocityStateGet(&velocityState);
    float velocity = sqrtf(velocityState.North * velocityState.North + velocityState.East * velocityState.East + velocityState.Down * velocityState.Down);

    // use airspeed if requested and available
    if (pathAction.ConditionParameters[1] > 0.5f) {
        AirspeedStateData airspeed;
        AirspeedStateGet(&airspeed);
        velocity = airspeed.CalibratedAirspeed;
    }

    if (velocity >= pathAction.ConditionParameters[0]) {
        return true;
    }
    return false;
}


/**
 * the PointingTowardsNext measures the horizontal movement vector direction relative to the next waypoint
 * regardless whether this waypoint will ever be active (Command could jump to another one on true)
 * This is useful for curve segments where the craft should stop circling when facing a certain way (usually the next waypoint)
 * returns true if within a certain angular margin
 * Parameter 0:  degrees variation allowed
 */
static uint8_t conditionPointingTowardsNext()
{
    uint16_t nextWaypointId = waypointActive.Index + 1;

    if (nextWaypointId >= UAVObjGetNumInstances(WaypointHandle())) {
        nextWaypointId = 0;
    }
    WaypointData nextWaypoint;
    WaypointInstGet(nextWaypointId, &nextWaypoint);

    float angle1 = atan2f((nextWaypoint.Position.North - waypoint.Position.North), (nextWaypoint.Position.East - waypoint.Position.East));

    VelocityStateData velocity;
    VelocityStateGet(&velocity);
    float angle2 = atan2f(velocity.North, velocity.East);

    // calculate the absolute angular difference
    angle1 = fabsf(RAD2DEG(angle1 - angle2));
    while (angle1 > 360) {
        angle1 -= 360;
    }

    if (angle1 <= pathAction.ConditionParameters[0]) {
        return true;
    }
    return false;
}

/**
 * the PythonScript is supposed to read the output of a PyMite program running at the same time
 * and return based on its output, likely read out through some to be defined UAVObject
 * TODO XXX NOT YET IMPLEMENTED
 * returns always true until implemented
 * Parameter 0-3: defined by user script
 */
static uint8_t conditionPythonScript()
{
    return true;
}

/* the immediate condition is always true */
static uint8_t conditionImmediate()
{
    return true;
}

/**
 * @}
 * @}
 */
