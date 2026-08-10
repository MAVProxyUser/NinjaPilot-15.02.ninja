/**
 ******************************************************************************
 * @addtogroup OpenPilotLibraries OpenPilot Libraries
 * @{
 * @addtogroup Navigation
 * @brief setups RTH/PH and other pathfollower/pathplanner status
 * @{
 *
 * @file       plan.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2014.
 *
 * @see        The GNU Public License (GPL) Version 3
 *
 ******************************************************************************/
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

#ifndef PLANS_H_
#define PLANS_H_
#include <stdint.h>
#include <pios_math.h>

/** \page standard Plans
   How to use this library
   \li Call plan_initialize() to init all needed struct and uavos at startup.<br>
   It may be safely called more than once.<br>

   \li Functions called plan_setup_* needs to be called once, every time the requested function is engaged.<br>

   \li Functions called plan_run_* are to be periodically called while the requested mode is engaged.<br>
 */

/**
 * @brief initialize UAVOs and structs used by this library
 */
void plan_initialize();

/**
 * @brief setup pathplanner/pathfollower for positionhold
 */
void plan_setup_positionHold();

/**
 * @brief setup pathplanner/pathfollower for return to base
 */
void plan_setup_returnToBase();

/**
 * @brief setup pathplanner/pathfollower for land
 */
void plan_setup_land();

/**
 * @brief setup pathplanner/pathfollower for braking
 */
void plan_setup_assistedcontrol(uint8_t timeout_occurred);

#define PATHDESIRED_MODEPARAMETER_BRAKE_STARTVELOCITYVECTOR_NORTH 0
#define PATHDESIRED_MODEPARAMETER_BRAKE_STARTVELOCITYVECTOR_EAST  1
#define PATHDESIRED_MODEPARAMETER_BRAKE_STARTVELOCITYVECTOR_DOWN  2
#define PATHDESIRED_MODEPARAMETER_BRAKE_TIMEOUT                   3

#define PATHDESIRED_MODEPARAMETER_VELOCITY_VELOCITYVECTOR_NORTH   0
#define PATHDESIRED_MODEPARAMETER_VELOCITY_VELOCITYVECTOR_EAST    1
#define PATHDESIRED_MODEPARAMETER_VELOCITY_VELOCITYVECTOR_DOWN    2
#define PATHDESIRED_MODEPARAMETER_VELOCITY_UNUSED                 3

#define PATHDESIRED_MODEPARAMETER_LAND_VELOCITYVECTOR_NORTH       0
#define PATHDESIRED_MODEPARAMETER_LAND_VELOCITYVECTOR_EAST        1
#define PATHDESIRED_MODEPARAMETER_LAND_VELOCITYVECTOR_DOWN        2
#define PATHDESIRED_MODEPARAMETER_LAND_OPTIONS                    3

#define PATHDESIRED_MODEPARAMETER_LAND_OPTION_NONE                0
#define PATHDESIRED_MODEPARAMETER_LAND_OPTION_HORIZONTAL_PH       1

#define PATHDESIRED_MODEPARAMETER_GOTOENDPOINT_NEXTCOMMAND        0
#define PATHDESIRED_MODEPARAMETER_GOTOENDPOINT_UNUSED1            1
#define PATHDESIRED_MODEPARAMETER_GOTOENDPOINT_UNUSED2            2
#define PATHDESIRED_MODEPARAMETER_GOTOENDPOINT_UNUSED3            3

// FollowVector. Note slot 0 is deliberately left alone: it aliases
// GOTOENDPOINT_NEXTCOMMAND, and vtolflycontroller compares that slot against
// FLIGHTMODESETTINGS_RETURNTOBASENEXTCOMMAND_LAND (== 1). A leg cruise speed
// of 1.5 m/s parked in slot 0 casts to (uint8_t)1 and triggered a real
// landing sequence in mid-mission - the vehicle flew to its first waypoint
// and then descended to the ground under control, which reads as a crash but
// is the RTB-land path firing on a number that was never a command.
// Intercept mode: the target's CURRENT velocity in NED. Its position rides in
// PathDesired.End and is refreshed by whatever is tracking it. Slot 0 is left
// unused for the same reason as FollowVector - it aliases
// PATHDESIRED_MODEPARAMETER_GOTOENDPOINT_NEXTCOMMAND, and a non-zero value
// there once cast to the RTB-LAND enum and landed the aircraft mid-mission.
#define PATHDESIRED_MODEPARAMETER_INTERCEPT_UNUSED0     0
#define PATHDESIRED_MODEPARAMETER_INTERCEPT_TARGETVELN  1
#define PATHDESIRED_MODEPARAMETER_INTERCEPT_TARGETVELE  2
#define PATHDESIRED_MODEPARAMETER_INTERCEPT_TARGETVELD  3

#define PATHDESIRED_MODEPARAMETER_FOLLOWVECTOR_UNUSED0            0
// Leg cruise speed (m/s). 0 = no opinion, leg is capped by its endpoint
// velocities as it always was.
#define PATHDESIRED_MODEPARAMETER_FOLLOWVECTOR_CRUISESPEED        1
// Bearing of the NEXT leg (degrees) and whether it is meaningful. Published
// by the path planner so the follower can turn for a corner before reaching
// it instead of discovering it at the waypoint switch.
#define PATHDESIRED_MODEPARAMETER_FOLLOWVECTOR_NEXTBEARING        2
#define PATHDESIRED_MODEPARAMETER_FOLLOWVECTOR_NEXTBEARINGVALID   3
/**
 * @brief setup pathfollower for positionvario
 */
void plan_setup_CourseLock();
void plan_setup_PositionRoam();
void plan_setup_VelocityRoam();
void plan_setup_HomeLeash();
void plan_setup_AbsolutePosition();

/**
 * @brief run for positionvario
 */
void plan_run_CourseLock();
void plan_run_PositionRoam();
void plan_run_VelocityRoam();
void plan_run_HomeLeash();
void plan_run_AbsolutePosition();

/**
 * @brief setup pathplanner/pathfollower for AutoCruise
 */
void plan_setup_AutoCruise();

/**
 * @brief execute AutoCruise
 */
void plan_run_AutoCruise();

#endif /* PLANS_H_ */
