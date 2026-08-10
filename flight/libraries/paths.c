/**
 ******************************************************************************
 *
 * @file       paths.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @brief      Library path manipulation
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

#include <pios.h>
#include <pios_math.h>
#include <mathmisc.h>

// Along-leg acceleration used by path_vector()'s trapezoidal speed profile,
// m/s^2.
//
// This constant used to be doing two jobs at once. Besides bounding
// acceleration it set how fast the vehicle was still travelling a given
// distance SHORT of the waypoint (braking follows v=sqrt(v_end^2+2*a*d)), and
// since the plan advanced the moment the vehicle clipped a wide acceptance
// radius, that arrival speed WAS the corner accuracy - hence the earlier note
// here about lowering it to brake sooner and "arrive genuinely slow".
//
// Arrival is no longer its problem. The mission now advances on a confirmed
// stop (a tight sphere plus a speed-and-dwell test, pathplanner.c
// conditionDistanceToTarget) and path_endpoint tapers its feed-forward to
// zero at the point, so the vehicle stops ON the waypoint regardless of this
// value. That frees the constant to do only its real job, and to be sized for
// the leg rather than for the corner: 0.6 -> 0.8.
//
// Bigger is not better here. 1.2 was tried alongside a 1.5 m/s cruise
// (star85) and the pair destabilised the vehicle - braking 1.5->0.5 m/s in
// (1.5^2-0.5^2)/(2*1.2) = 0.83m is a sharp tilt transient right where the
// vehicle is trying to settle on a waypoint, and it showed up as pitch RMS
// 0.9 -> 6.4 deg, altitude peak-to-peak 0.17 -> 1.82m, and a plan that stuck
// at the second waypoint for 43s. At 0.8 the same deceleration is spread over
// 1.25m and the profile is gentle enough for the velocity loop to track.
#define PATH_LEG_ACCEL 0.8f

// Arrival slope, m/s per metre remaining. Caps commanded speed near a
// waypoint so it decays LINEARLY with distance instead of on the braking
// curve's sqrt.
//
// The sqrt curve v=sqrt(2*a*d) is the right shape for the physics and the
// wrong shape for the loop that has to fly it: its slope is infinite at d=0,
// so in the last few centimetres the command collapses far faster than the
// velocity loop can follow, and the vehicle carries its lag straight through
// the point. Measured with a full-stop corner and no cap (star87): every
// waypoint overshot by 0.32-0.82m, then got dragged back by endpoint homing
// while the nose was still turning - which is why the recovery looked like
// the vehicle orbiting the waypoint - and each pass reset the arrival
// confirmation, costing 4-8s per corner.
//
// A linear cap makes the last stretch a first-order settle, which is exactly
// what a P-controlled velocity loop tracks without lag error. It only binds
// inside v/PATH_ARRIVAL_GAIN metres, so it shapes the arrival without
// slowing the leg.
//
// 0.7 -> 0.45 -> 0.85. This slope also sets how long the final approach
// takes, and 0.45 made it far too long: a first-order settle with a 2.2s time
// constant spent 9s creeping the last 0.46m onto the waypoint, which was most
// of a 175s mission (star90 - speed during that crawl was 0.02-0.28 m/s, so
// the hold-up was distance, never the arrival speed gate).
//
// 0.45 was chosen to buy TIME for the corner turn. That is no longer how the
// turn is paced: vtolflycontroller now blends the heading as a function of
// distance remaining, so the nose arrives on the new bearing whatever speed
// the vehicle closes at. With the turn decoupled from the clock, this
// constant is free to be what it should be - fast enough to actually finish
// the arrival, gentle enough that the velocity loop tracks it without
// carrying lag through the point.
//
// 0.85, and 1.15 has now been tried TWICE and rejected twice. The second
// attempt (star120) was made on the reasonable theory that the damped
// velocity loop could finally track a steeper ramp - it recovered 20s of the
// 32s that the tightened acceptance sphere cost, and gave back exactly what
// that sphere was bought for: mean overshoot 0.00 -> 0.13m and cross-track
// 0.08 -> 0.13m. Arriving cleanly on the point is the thing being optimised
// for; buy time on the LEGS instead, where the tracking margin actually is.
#define PATH_ARRIVAL_GAIN 0.85f

// Floor on the arrival SPEED CAP (m/s), not on the speed itself.
//
// path_endpoint caps its feed-forward at EndingVelocity, and a corner meant to
// be a full stop has EndingVelocity = 0 - so the cap is zero and the
// feed-forward is zero for the whole final approach. The last stretch is then
// closed by the follower's position P term alone: 0.35 * 0.14m = 0.05 m/s
// commanded. Measured: the vehicle settled 0.14m from the waypoint and closed
// at ~0.01 m/s over the next four seconds, i.e. it dwelled ALONGSIDE the point
// rather than on it, and the plan confirmed there because 0.14 was inside the
// acceptance radius.
//
// Capping at max(EndingVelocity, this) restores a real closing command while
// keeping the taper: speed is still PATH_ARRIVAL_GAIN * distance, so it goes
// to zero AT the point, but it is no longer clamped to zero on the way in.
// Fly-through waypoints are unaffected - their EndingVelocity is already well
// above this.
#define PATH_ARRIVAL_MIN_CAP 0.30f

#include "uavobjectmanager.h" // <--.
#include "pathdesired.h" // <-- needed only for correct ENUM macro usage with path modes (PATHDESIRED_MODE_xxx,
#include "paths.h"
#include "plans.h" // ModeParameters slot names
// no direct UAVObject usage allowed in this file

// private functions
static void path_endpoint(PathDesiredData *path, float *cur_point, struct path_status *status, bool mode);
static void path_vector(PathDesiredData *path, float *cur_point, struct path_status *status, bool mode);
static void path_circle(PathDesiredData *path, float *cur_point, struct path_status *status, bool clockwise);

/**
 * @brief Compute progress along path and deviation from it
 * @param[in] path  PathDesired structure
 * @param[in] cur_point Current location
 * @param[out] status Structure containing progress along path and deviation
 */
void path_progress(PathDesiredData *path, float *cur_point, struct path_status *status, bool mode3D)
{
    switch (path->Mode) {
    case PATHDESIRED_MODE_BRAKE:
    case PATHDESIRED_MODE_FOLLOWVECTOR:
        return path_vector(path, cur_point, status, mode3D);

        break;
    case PATHDESIRED_MODE_CIRCLERIGHT:
        return path_circle(path, cur_point, status, true);

        break;
    case PATHDESIRED_MODE_CIRCLELEFT:
        return path_circle(path, cur_point, status, false);

        break;
    case PATHDESIRED_MODE_GOTOENDPOINT:
        return path_endpoint(path, cur_point, status, mode3D);

        break;
    case PATHDESIRED_MODE_LAND:
    default:
        // use the endpoint as default failsafe if called in unknown modes
        return path_endpoint(path, cur_point, status, false);

        break;
    }
}

/**
 * @brief Compute progress towards endpoint. Deviation equals distance
 * @param[in] path PathDesired
 * @param[in] cur_point Current location
 * @param[out] status Structure containing progress along path and deviation
 * @param[in] mode3D set true to include altitude in distance and progress calculation
 */
static void path_endpoint(PathDesiredData *path, float *cur_point, struct path_status *status, bool mode3D)
{
    float diff[3];
    float dist_path, dist_diff;

    // Distance to go
    status->path_vector[0] = path->End.North - path->Start.North;
    status->path_vector[1] = path->End.East - path->Start.East;
    status->path_vector[2] = mode3D ? path->End.Down - path->Start.Down : 0.0f;

    // Current progress location relative to end
    diff[0]   = path->End.North - cur_point[0];
    diff[1]   = path->End.East - cur_point[1];
    diff[2]   = mode3D ? path->End.Down - cur_point[2] : 0.0f;

    dist_diff = vector_lengthf(diff, 3);
    dist_path = vector_lengthf(status->path_vector, 3);

    if (dist_diff < 1e-6f) {
        status->fractional_progress  = 1;
        status->error = 0.0f;
        status->correction_vector[0] = status->correction_vector[1] = status->correction_vector[2] = 0.0f;
        // we have no base movement direction in this mode
        status->path_vector[0] = status->path_vector[1] = status->path_vector[2] = 0.0f;

        return;
    }

    if (fmaxf(dist_path, 1.0f) > dist_diff) {
        status->fractional_progress = 1 - dist_diff / fmaxf(dist_path, 1.0f);
    } else {
        status->fractional_progress = 0; // we don't want fractional_progress to become negative
    }
    status->error = dist_diff;

    // Compute correction vector
    status->correction_vector[0] = diff[0];
    status->correction_vector[1] = diff[1];
    status->correction_vector[2] = diff[2];

    // Base movement direction is a velocity offset toward the endpoint, on
    // top of the correction in the same direction - but TAPERED as the
    // endpoint gets close.
    //
    // The original was a unit vector times EndingVelocity, i.e. a constant
    // full-speed command toward the target no matter how near it was: 0.5 m/s
    // demanded at 0.5m out, and still 0.5 m/s demanded at 0.05m out. With the
    // position correction added on top by the follower, that cannot settle -
    // the vehicle drives through the point, turns around, drives through it
    // again. Measured on star81, at the two waypoints where it caught: the
    // vehicle sat 0.16-0.56m from the point with speed cycling 0.22-0.80 m/s
    // for 11.7s and 8.3s, because the mission's confirm-arrival gate wants
    // speed under 0.4 m/s and the buzzing never held it there. It is also
    // what put a hook in the path just before landing, and it is what the
    // FollowVector past-the-endpoint fallback inherits.
    //
    // Tapering makes the feed-forward vanish as the error vanishes and leaves
    // the fine settling to the follower's position loop, which is what that
    // loop is for. See PATH_ARRIVAL_GAIN for why the slope is linear.
    float speed = path->EndingVelocity;
    if (speed < PATH_ARRIVAL_MIN_CAP) {
        speed = PATH_ARRIVAL_MIN_CAP;
    }
    if (speed > PATH_ARRIVAL_GAIN * dist_diff) {
        speed = PATH_ARRIVAL_GAIN * dist_diff;
    }
    status->path_vector[0] = speed * status->correction_vector[0] / dist_diff;
    status->path_vector[1] = speed * status->correction_vector[1] / dist_diff;
    status->path_vector[2] = speed * status->correction_vector[2] / dist_diff;
}

/**
 * @brief Compute progress along path and deviation from it
 * @param[in] path PathDesired
 * @param[in] cur_point Current location
 * @param[out] status Structure containing progress along path and deviation
 * @param[in] mode3D set true to include altitude in distance and progress calculation
 */
static void path_vector(PathDesiredData *path, float *cur_point, struct path_status *status, bool mode3D)
{
    float diff[3];
    float dist_path;
    float dot;
    float velocity;
    float track_point[3];

    // Distance to go
    status->path_vector[0] = path->End.North - path->Start.North;
    status->path_vector[1] = path->End.East - path->Start.East;
    status->path_vector[2] = mode3D ? path->End.Down - path->Start.Down : 0.0f;

    // Current progress location relative to start
    diff[0]   = cur_point[0] - path->Start.North;
    diff[1]   = cur_point[1] - path->Start.East;
    diff[2]   = mode3D ? cur_point[2] - path->Start.Down : 0.0f;

    dot       = status->path_vector[0] * diff[0] + status->path_vector[1] * diff[1] + status->path_vector[2] * diff[2];
    dist_path = vector_lengthf(status->path_vector, 3);

    if (dist_path > 1e-6f) {
        // Compute direction to travel & progress
        status->fractional_progress = dot / (dist_path * dist_path);
    } else {
        // Fly towards the endpoint to prevent flying away,
        // but assume progress=1 either way.
        path_endpoint(path, cur_point, status, mode3D);
        status->fractional_progress = 1;
        return;
    }
    // Past the endpoint the infinite-line projection is a trap: track_point
    // extends BEYOND End and path_vector keeps pushing along the leg's
    // extension forever, so a vehicle that crosses the waypoint outside its
    // acceptance radius just sails away at EndingVelocity (missions 12 and
    // 18 did exactly this - 30m and 12m respectively - until a ground-side
    // guard intervened). Fall back to endpoint behaviour instead: home in
    // on End at EndingVelocity, which brings the vehicle back through the
    // acceptance radius and lets the plan advance.
    if (status->fractional_progress >= 1.0f) {
        path_endpoint(path, cur_point, status, mode3D);
        status->fractional_progress = 1.0f;
        return;
    }

    // Compute point on track that is closest to our current position.
    track_point[0] = status->fractional_progress * status->path_vector[0] + path->Start.North;
    track_point[1] = status->fractional_progress * status->path_vector[1] + path->Start.East;
    track_point[2] = status->fractional_progress * status->path_vector[2] + path->Start.Down;

    status->correction_vector[0] = track_point[0] - cur_point[0];
    status->correction_vector[1] = track_point[1] - cur_point[1];
    status->correction_vector[2] = track_point[2] - cur_point[2];

    status->error = vector_lengthf(status->correction_vector, 3);

    // Trapezoidal speed profile instead of the original linear
    // StartingVelocity -> EndingVelocity interpolation. The linear ramp
    // starts slowing toward the corner speed from the moment the leg
    // begins, so a 12m leg into a 0.45 m/s hairpin crawled its whole
    // length. Here the leg accelerates away from the previous corner at
    // PATH_LEG_ACCEL, cruises at the faster of the two endpoint speeds,
    // and only brakes inside the distance actually needed to reach
    // EndingVelocity - the standard v^2 = v0^2 + 2*a*d braking curve.
    // Legs with equal endpoint speeds (fixed-wing cruise, slow letter
    // strokes) behave exactly as before: all three limits equal the
    // endpoint speed. Past the endpoint (fractional_progress > 1) the
    // profile holds EndingVelocity, same as the old code.
    {
        float progress = boundf(status->fractional_progress, 0.0f, 1.0f);
        float d_gone   = progress * dist_path;
        float d_left   = dist_path - d_gone;
        float cruise   = fmaxf(path->StartingVelocity, path->EndingVelocity);
        // Optional LEG CRUISE SPEED, independent of the endpoint speeds.
        //
        // Without it a leg can never travel faster than its own endpoints,
        // because both limits above are endpoint velocities. That is fine for
        // a fly-through waypoint but wrong for a corner-to-corner leg: in the
        // star EVERY vertex is a 144deg hairpin, so both endpoints carry the
        // slow corner speed and the whole 11.4m leg crawled at it - measured
        // 0.53 m/s median while MISSION_SPEED was 1.5. The mission was asking
        // for a fast leg between slow corners and had no way to say so.
        // ModeParameters[0] says it. Zero (or anything below the endpoint
        // speeds) keeps the historic behaviour exactly.
        // Slot 1, not slot 0: slot 0 aliases GOTOENDPOINT_NEXTCOMMAND and a
        // speed parked there triggers the RTB landing sequence (see plans.h).
        if (path->Mode == PATHDESIRED_MODE_FOLLOWVECTOR
            && path->ModeParameters[PATHDESIRED_MODEPARAMETER_FOLLOWVECTOR_CRUISESPEED] > cruise) {
            cruise = path->ModeParameters[PATHDESIRED_MODEPARAMETER_FOLLOWVECTOR_CRUISESPEED];
        }
        // The acceleration limit needs a floor, or a leg that begins stopped
        // AT its own start point can never begin: accel_lim = sqrt(v0^2 +
        // 2*a*d_gone) is exactly zero when v0 and d_gone are both zero, the
        // profile commands no speed, the vehicle does not move, d_gone stays
        // zero. Deadlock. It went unnoticed while every waypoint carried a
        // nonzero arrival velocity, and appeared the moment corners became
        // true stops AND a leg started from a standstill exactly on its Start
        // - a vertical climb waypoint directly over the pad, which hung for
        // 93s without ever leaving the ground (star91). Treating the vehicle
        // as already a few centimetres along is enough to break the tie.
        float accel_lim = sqrtf(squaref(path->StartingVelocity)
                                + 2.0f * PATH_LEG_ACCEL * fmaxf(d_gone, 0.05f));
        float brake_lim = sqrtf(squaref(path->EndingVelocity) + 2.0f * PATH_LEG_ACCEL * d_left);
        velocity = fminf(cruise, fminf(accel_lim, brake_lim));
        // Linear arrival cap, so the vehicle settles ON the endpoint instead
        // of carrying its loop lag through it. Only meaningful for a leg that
        // ends stopped or nearly so - with a fly-through EndingVelocity the
        // brake limit never drops that low anyway.
        if (velocity > path->EndingVelocity + PATH_ARRIVAL_GAIN * d_left) {
            velocity = path->EndingVelocity + PATH_ARRIVAL_GAIN * d_left;
        }
    }
    status->path_vector[0] = velocity * status->path_vector[0] / dist_path;
    status->path_vector[1] = velocity * status->path_vector[1] / dist_path;
    status->path_vector[2] = velocity * status->path_vector[2] / dist_path;
}

/**
 * @brief Compute progress along circular path and deviation from it
 * @param[in] path PathDesired
 * @param[in] cur_point Current location
 * @param[out] status Structure containing progress along path and deviation
 */
static void path_circle(PathDesiredData *path, float *cur_point, struct path_status *status, bool clockwise)
{
    float radius_north, radius_east, diff_north, diff_east, diff_down;
    float radius, cradius;
    float normal[2];
    float progress;
    float a_diff, a_radius;

    // Radius
    radius_north = path->End.North - path->Start.North;
    radius_east  = path->End.East - path->Start.East;

    // Current location relative to center
    diff_north   = cur_point[0] - path->End.North;
    diff_east    = cur_point[1] - path->End.East;
    diff_down    = cur_point[2] - path->End.Down;

    radius  = sqrtf(squaref(radius_north) + squaref(radius_east));
    cradius = sqrtf(squaref(diff_north) + squaref(diff_east));

    // circles are always horizontal (for now - TODO: allow 3d circles - problem: clockwise/counterclockwise does no longer apply)
    status->path_vector[2] = 0.0f;

    // error is current radius minus wanted radius - positive if too close
    status->error = radius - cradius;

    if (cradius < 1e-6f) {
        // cradius is zero, just fly somewhere
        status->fractional_progress  = 1;
        status->correction_vector[0] = 0;
        status->correction_vector[1] = 0;
        status->path_vector[0] = path->EndingVelocity;
        status->path_vector[1] = 0;
    } else {
        if (clockwise) {
            // Compute the normal to the radius clockwise
            normal[0] = -diff_east / cradius;
            normal[1] = diff_north / cradius;
        } else {
            // Compute the normal to the radius counter clockwise
            normal[0] = diff_east / cradius;
            normal[1] = -diff_north / cradius;
        }

        // normalize progress to 0..1
        a_diff   = atan2f(diff_north, diff_east);
        a_radius = atan2f(radius_north, radius_east);

        if (a_diff < 0) {
            a_diff += 2.0f * M_PI_F;
        }
        if (a_radius < 0) {
            a_radius += 2.0f * M_PI_F;
        }

        progress = (a_diff - a_radius + M_PI_F) / (2.0f * M_PI_F);

        if (progress < 0.0f) {
            progress += 1.0f;
        } else if (progress >= 1.0f) {
            progress -= 1.0f;
        }

        if (clockwise) {
            progress = 1.0f - progress;
        }

        status->fractional_progress = progress;

        // Compute direction to travel
        status->path_vector[0] = normal[0] * path->EndingVelocity;
        status->path_vector[1] = normal[1] * path->EndingVelocity;

        // Compute direction to correct error
        status->correction_vector[0] = status->error * diff_north / cradius;
        status->correction_vector[1] = status->error * diff_east / cradius;
    }

    status->correction_vector[2] = -diff_down;

    status->error = fabs(status->error);
}
