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
static void path_intercept(PathDesiredData *path, float *cur_point, struct path_status *status, bool mode3D);

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
    case PATHDESIRED_MODE_INTERCEPT:
        return path_intercept(path, cur_point, status, mode3D);

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


/**
 * @brief Fly a lead-pursuit intercept on a MOVING target.
 * @param[in] path  PathDesired: End = target position NOW, ModeParameters
 *                  [1..3] = target velocity NED, EndingVelocity = our speed cap
 * @param[in] cur_point Current location
 * @param[out] status Structure containing progress along path and deviation
 *
 * Chasing where a target IS (plain GoToEndpoint homing on a refreshed point)
 * is tail-chase: the command always points behind a crossing target and the
 * miss distance never closes if the target is anywhere near our own speed.
 * This aims where the target WILL BE.
 *
 * Solve for time-to-go from |R + V_t*t| = v_max*t, i.e. the moment our reach
 * equals the target's range. Expanded that is the quadratic
 *
 *     (v_max^2 - |V_t|^2) t^2 - 2(R.V_t) t - |R|^2 = 0
 *
 * with R the relative position (target - us). The positive root is the
 * intercept time; the aim point is R + V_t*t. When the leading coefficient
 * goes non-positive the target is as fast as we are and no intercept exists -
 * fall back to pure pursuit, which at least closes if the target ever turns.
 *
 * AIRFRAME LIMITS ARE THE POINT. A tracker feeding a moving point at 10-20Hz
 * will jitter, and steering straight off it commands acceleration steps the
 * attitude loop cannot follow - the same failure as star126, where rotating
 * the feed-forward mid-leg put the vehicle on the ground. So the commanded
 * velocity is SLEWED, not stepped: the direction may change no faster than
 * INTERCEPT_MAX_TURN_RATE and the magnitude no faster than INTERCEPT_MAX_ACCEL.
 * Both are well inside what this airframe demonstrated during mission flying
 * (0.8 m/s^2 leg acceleration, 35 deg/s yaw slew).
 */
#define INTERCEPT_MAX_ACCEL      1.2f   // m/s^2 on the commanded speed
#define INTERCEPT_MAX_TURN_RATE  60.0f  // deg/s on the commanded direction
// LEAD x1.35 TESTED AND WORSE, on the clean (loop-unblocked) baseline where
// the measurement is trustworthy: mean 0.87m and 1/5 contacts, versus 0.59m
// and 5/5 at x1.0. The endgame lead is already right; do not add more.
#define INTERCEPT_ENDGAME_LEAD_K  1.0f  // multiply the endgame lead horizon.
                                         // Contacts sit at 0.58-0.60m, the
                                         // outer edge of the 0.582m contact
                                         // geometry - grazes, not centre
                                         // hits. Leading slightly longer aims
                                         // into the centre. Measurable now
                                         // that runs repeat to ~2cm.
// LAG COMPENSATION MOVED TO THE ESTIMATOR - do not re-add it here.
//
// The measured miss on the clean baseline was a repeatable 0.57-0.59m
// directly BEHIND the target with near-zero cross-track: a pure ~0.48s time
// lag, not an aiming error. Adding that 0.48s as a CONSTANT to the endgame
// lead was tried and was measurably worse - 1.25m, 1.30m, 1.32m first-pass
// misses over three runs, versus 0.57-0.59m without it.
//
// The reason it backfired: the endgame lead is already range-dependent
// (range/vmax), so a constant on top of it over-leads hardest exactly when
// range is collapsing and the vehicle can least afford a moving aim point.
//
// The compensation now lives where the information is - the bridge's
// TargetEKF propagates the target state forward by the lag through the same
// dynamics it already estimates, and hands the firmware a position that is
// honest about when it will be acted on. That is automatically correct at
// every range. Offline against a synthetic track it predicts 0.48s ahead to
// 0.199m, versus the 0.58m of pure lag it replaces
// (tools/test_target_ekf.py).
#define INTERCEPT_LAG_COMP_S      0.0f   // estimator owns this; see above
#define INTERCEPT_ENDGAME_MAX_LEAD_S 2.5f  // s: cap on the endgame lead
                                           // horizon, so a stalled closure
                                           // cannot aim absurdly far ahead
#define INTERCEPT_LEVEL_BAND     0.10f   // m: within this of the target's
                                        // altitude counts as level - full
                                        // horizontal pursuit
#define INTERCEPT_LEVEL_RAMP     5.0f   // m: ramp horizontal back in over
                                        // this band above LEVEL_BAND.
                                        // 2.5 TRIED AND NEUTRAL (+0.78 ->
                                        // +0.80 at 3.5): the gate releases on
                                        // POSITION gap, so the full sprint
                                        // always starts while still carrying
                                        // ~2 m/s of climb - ramp width never
                                        // touches that. The real entry-rate
                                        // cap is VerticalVelMax (bridge).
#define INTERCEPT_LAUNCH_HORIZ   0.15f  // horizontal fraction on the deck
#define INTERCEPT_FLOOR_M        3.0f   // m: never command descent below this
#define INTERCEPT_ENDGAME_DIST   4.0f   // m: inside this, pure pursuit - the
                                        // cross-range term is ill-conditioned
                                        // at short range and thrashes
#define INTERCEPT_TERMINAL_DIST  3.0f   // m: inside this, aim straight at it
                                        // 1.5 -> 3.0: braking has to START before
                                        // the merge, not at it. At 2 m/s closing,
                                        // 1.5m of runway is 0.75s.
// AMBUSH MARGIN TESTED AND NEUTRAL. Aiming 1.6s past the earliest meeting
// point (arrive first and wait, rather than run a dead heat) gave
// 0.65-1.87m, mean 1.22 - indistinguishable from 1.20 without it. The
// along-track lag is real but is NOT fixed by moving the aim point further
// down the track. Left at 0 rather than carrying an unproven mechanism.
#define INTERCEPT_AMBUSH_MARGIN_S 0.0f
#define INTERCEPT_LOITER_MARGIN  1.5f   // s of slack required to sit and wait
#define INTERCEPT_MAX_CLIMB      3.0f   // m/s: the frame's usable climb rate
#define INTERCEPT_CLIMB_FRAC     0.6f   // of the speed budget, so ~0.8x remains
                                        // horizontal (sqrt(1-0.36)) and the
                                        // vehicle closes WHILE it climbs
// AIM-HIGH BIAS AND GAIN 1.1 WERE TRIED AND FAILED. Aiming 0.9m above the
// object with vertical gain raised 0.7 -> 1.1 made every metric worse:
// closest approach 0.46-0.62m (thru batch) -> 0.94-3.09m, contacts 1/4 -> 0/4,
// and one crash. The sag is real and measured, but over-driving the vertical
// to cancel it destabilises the merge - the vehicle chases altitude instead
// of closing. Do not retry as a pair; if the sag is attacked again it should
// be by removing its CAUSE (lift lost to tilt during horizontal closure),
// not by biasing the aim point on top of an already-marginal loop.
#define INTERCEPT_AIM_HIGH_M     0.0f   // no aim bias - measured worse
#define INTERCEPT_VERT_GAIN      0.7f   // 1/s: vertical speed cap per metre of
                                        // vertical gap, so the climb ends at
                                        // the target's level, not past it
#define INTERCEPT_LOITER_GAIN    0.9f   // 1/s taper settling onto the aim point

// Set by path_intercept_reset(), consumed on the next path_intercept() call.
// A flag rather than direct clearing because the statics it clears are local
// to path_intercept.
static bool interceptResetPending = true;

void path_intercept_reset(void)
{
    interceptResetPending = true;
}

static void path_intercept(PathDesiredData *path, float *cur_point, struct path_status *status, bool mode3D)
{
    // Relative position: target minus us.
    float R[3] = { path->End.North - cur_point[0],
                   path->End.East - cur_point[1],
                   path->End.Down - cur_point[2] };
    if (!mode3D) {
        R[2] = 0.0f;
    }
    float Vt[3] = { path->ModeParameters[PATHDESIRED_MODEPARAMETER_INTERCEPT_TARGETVELN],
                    path->ModeParameters[PATHDESIRED_MODEPARAMETER_INTERCEPT_TARGETVELE],
                    mode3D ? path->ModeParameters[PATHDESIRED_MODEPARAMETER_INTERCEPT_TARGETVELD] : 0.0f };

    float range = vector_lengthf(R, 3);
    float vmax  = path->EndingVelocity;
    if (vmax < 0.1f) {
        vmax = 0.1f;
    }

    // EARLIEST REACHABLE POINT, steered on a CONSTANT BEARING.
    //
    // Two ideas, and both matter:
    //
    // 1. AIM AT THE EARLIEST POINT ON THE TRACK WE CAN REACH - not the far
    //    meeting point. Solving (vmax^2-|Vt|^2)t^2 - 2(R.Vt)t - |R|^2 = 0
    //    gives the soonest time we can be where the object will be. When our
    //    speed margin over the object is small that time is long and the
    //    point sits far downrange; committing to it makes the two look like
    //    they are racing to a finish line, and every metre of that run is
    //    wasted the moment the object turns. Recomputing it every tick keeps
    //    it the EARLIEST point, which walks backwards toward us as we close.
    //
    // 2. STEER A CONSTANT BEARING, not a heading to a waypoint. Decompose
    //    the object's velocity about the line of sight: matching its
    //    cross-LOS component holds the bearing constant, which is the
    //    collision condition, and the remaining speed closes the range.
    //    Constant bearing + decreasing range - what a mariner or a CIWS
    //    director uses. It needs only what is observable right now; nothing
    //    about where the object is going, which we could never know.
    float u[3] = { R[0], R[1], R[2] };
    if (range > 1e-3f) {
        u[0] /= range; u[1] /= range; u[2] /= range;
    }

    // --- (1) earliest reachable point on the track
    float vt2 = Vt[0] * Vt[0] + Vt[1] * Vt[1] + Vt[2] * Vt[2];
    float qa = vmax * vmax - vt2;
    float qb = 2.0f * (R[0] * Vt[0] + R[1] * Vt[1] + R[2] * Vt[2]);
    float t_int = 0.0f;
    if (qa > 1e-3f) {
        float disc = qb * qb + 4.0f * qa * range * range;
        if (disc > 0.0f) {
            t_int = (qb + sqrtf(disc)) / (2.0f * qa);
        }
    }
    if (!(t_int > 0.0f) || t_int > 60.0f) {
        t_int = 0.0f;               // no solution: object is as fast as us
    }
    // AMBUSH MARGIN: aim at where it will be a little AFTER the earliest
    // possible meeting, so we arrive with time in hand and it flies into us.
    //
    // The earliest reachable point is the mathematically soonest meeting, but
    // reaching it requires arriving at exactly the right moment - a dead heat
    // with no margin. At 2.2 m/s against a 1.2 m/s crosser the net closure is
    // ~1 m/s, and the measured failure is an ALONG-TRACK LAG: the vehicle
    // matches one axis and trails the other as the object pulls ahead
    // (cf3: dN 0.28 matched, dE 0.67 trailing at closest approach). A dead
    // heat that loses by half a metre is still a miss.
    //
    // Aiming further down the track converts the problem from "win a race"
    // to "be there first and wait", which a slower interceptor CAN do because
    // it cuts the corner while the object flies the hypotenuse. This is the
    // ambush the operator described - arrive at a point on the trajectory,
    // let the object come to it - now with explicit margin instead of hoping
    // the dead heat lands.
    float t_aim = t_int + INTERCEPT_AMBUSH_MARGIN_S;
    float toP[3] = { R[0] + Vt[0] * t_aim,
                     R[1] + Vt[1] * t_aim,
                     R[2] + Vt[2] * t_aim };
    float distP = vector_lengthf(toP, 3);

    // --- (2) constant-bearing direction
    float vt_along = Vt[0] * u[0] + Vt[1] * u[1] + Vt[2] * u[2];
    float vperp[3] = { Vt[0] - vt_along * u[0],
                       Vt[1] - vt_along * u[1],
                       Vt[2] - vt_along * u[2] };
    float vperp_mag = vector_lengthf(vperp, 3);
    float bear[3];
    if (range < INTERCEPT_ENDGAME_DIST) {
        // ENDGAME: SHORT-HORIZON LEAD, not pure pursuit.
        //
        // Pure pursuit was tried here and it is wrong: aiming where the
        // object IS guarantees trailing it, and every run grazed at
        // 0.53-0.60m - the outer edge of the contact geometry - instead of
        // hitting centre. Missing the first pass is expensive: it costs the
        // whole engagement, because a stern chase afterwards has almost no
        // closing speed and degenerates into flailing alongside.
        //
        // But the full cross-range solution is ill-conditioned at short
        // range (line-of-sight rate diverges as range -> 0, which is what
        // made the command thrash). The stable middle is to lead over the
        // time WE need to cover the remaining range: t = range / vmax. That
        // horizon shrinks smoothly to zero as we arrive, so it cannot blow
        // up, and at 4m out with a 1.2 m/s object it is still a 2.2m lead -
        // the difference between a centre hit and the corner graze.
        // ADD the measured loop lag, do not scale by it.
        //
        // On the clean baseline the miss is astonishingly repeatable: the
        // vehicle sits 0.57-0.59m BEHIND the ball along its own direction of
        // travel, with cross-track essentially zero (-0.18..0.00m). That is
        // not an aiming error, it is LATENCY - 0.58m at 1.2 m/s is 0.48s of
        // lag through bridge sampling, transport, and the ~130ms attitude
        // response. It is a constant offset in TIME, so it needs a constant
        // correction in time.
        //
        // Scaling the geometric lead was tried (x1.35) and was worse - mean
        // 0.87m, 1/5 contacts vs 0.59m, 5/5 - because the geometric term
        // grows with range: it overshoots badly at 4m while barely moving the
        // aim at 0.6m, which is where the miss actually is.
        float t_lead = (range / vmax) * INTERCEPT_ENDGAME_LEAD_K
                       + INTERCEPT_LAG_COMP_S;
        if (t_lead > INTERCEPT_ENDGAME_MAX_LEAD_S) {
            t_lead = INTERCEPT_ENDGAME_MAX_LEAD_S;
        }
        float lead[3] = { R[0] + Vt[0] * t_lead,
                          R[1] + Vt[1] * t_lead,
                          R[2] + Vt[2] * t_lead };
        float ll = vector_lengthf(lead, 3);
        if (ll > 1e-3f) {
            bear[0] = lead[0] / ll * vmax;
            bear[1] = lead[1] / ll * vmax;
            bear[2] = lead[2] / ll * vmax;
        } else {
            bear[0] = u[0] * vmax; bear[1] = u[1] * vmax; bear[2] = u[2] * vmax;
        }
    } else if (vperp_mag >= vmax) {
        // Cannot match the cross-range motion: unwinnable geometry, put
        // everything into cross-range rather than pretending otherwise.
        bear[0] = vperp[0]; bear[1] = vperp[1]; bear[2] = vperp[2];
    } else {
        float closing = sqrtf(vmax * vmax - vperp_mag * vperp_mag);
        bear[0] = vperp[0] + closing * u[0];
        bear[1] = vperp[1] + closing * u[1];
        bear[2] = vperp[2] + closing * u[2];
    }
    float bl = vector_lengthf(bear, 3);
    float dir[3];
    if (bl > 1e-3f) {
        dir[0] = bear[0] / bl; dir[1] = bear[1] / bl; dir[2] = bear[2] / bl;
    } else {
        dir[0] = u[0]; dir[1] = u[1]; dir[2] = u[2];
    }

    // --- speed: full effort, easing only when there is genuinely time in
    // hand to sit on the earliest point and let the object come to us, or
    // when close enough that contact should be an arrival, not a ram.
    // Is the range opening? Then we have missed and are trailing it, and the
    // only correct response is maximum effort - re-attack at the earliest
    // point we can still reach. Measured on the scramble runs: after a miss
    // the vehicle sat at ~4.6m closing at 0.1 m/s with a 2.2 m/s cap against
    // a 1.2 m/s object, because the loiter branch believed it had time in
    // hand. It does not: "wait for it to come to you" is only valid while
    // the object is still INBOUND.
    static float lastRange = 0.0f;
    static bool haveRange = false;
    bool opening = haveRange && (range > lastRange + 0.02f);
    lastRange = range;
    haveRange = true;
    if (interceptResetPending) {
        haveRange = false;
    }

    float speed = vmax;
    float t_us = distP / vmax;
    if (!opening && range > INTERCEPT_ENDGAME_DIST
        && t_int > 0.0f && t_us + INTERCEPT_LOITER_MARGIN < t_int) {
        // Loiter is for holding station on the earliest point while the
        // object is still FAR. Inside the endgame it would crawl into the
        // merge, which is the same mistake as the terminal taper.
        speed = boundf(INTERCEPT_LOITER_GAIN * distP, 0.0f, vmax);
    }
    // NO TERMINAL DECELERATION - deliberately removed.
    //
    // This used to taper to 0.35-1.0x vmax inside 3m, which at the 0.58m
    // contact distance is UNDER HALF SPEED. The vehicle crawled into the
    // merge, stopped short of the object, and grazed. That taper came from
    // waypoint arrival logic, where stopping ON the point is the entire
    // objective - here it is exactly backwards. An intercept path must be
    // flown THROUGH the target at full speed.
    //
    // It also destroyed the thing that makes a strike register: closing
    // speed. The runs that produced 63g, 23g and 16g were fast merges; every
    // 1.3g brush was the vehicle arriving slowly. Slowing down near a moving
    // object is the one thing guaranteed to turn a hit into a graze.

    // ---- rate limiting, so a jittery tracker cannot overload the airframe ----
    // NOTE these persist across calls BY DESIGN (the rate limiter needs the
    // previous command) - and therefore also across engagements, which is a
    // trap. Re-entering intercept after a break would resume slewing from a
    // command aimed wherever the last engagement ended. path_intercept_reset()
    // is called from VtolFlyController::Activate() to clear it.
    static float lastCmd[3] = { 0.0f, 0.0f, 0.0f };
    static bool  haveLast   = false;

    if (interceptResetPending) {
        interceptResetPending = false;
        haveLast = false;
        lastCmd[0] = lastCmd[1] = lastCmd[2] = 0.0f;
    }
    float cmd[3] = { dir[0] * speed, dir[1] * speed, dir[2] * speed };

    if (haveLast) {
        const float dT = 0.02f; // follower update period; conservative if faster
        float lastLen = vector_lengthf(lastCmd, 3);
        if (lastLen > 1e-3f) {
            // limit direction change
            float lu[3] = { lastCmd[0] / lastLen, lastCmd[1] / lastLen, lastCmd[2] / lastLen };
            float dot = boundf(lu[0] * dir[0] + lu[1] * dir[1] + lu[2] * dir[2], -1.0f, 1.0f);
            float ang = RAD2DEG(acosf(dot));
            float maxAng = INTERCEPT_MAX_TURN_RATE * dT;
            if (ang > maxAng && ang > 1e-3f) {
                float f = maxAng / ang;
                dir[0] = lu[0] + (dir[0] - lu[0]) * f;
                dir[1] = lu[1] + (dir[1] - lu[1]) * f;
                dir[2] = lu[2] + (dir[2] - lu[2]) * f;
                float dl = vector_lengthf(dir, 3);
                if (dl > 1e-3f) { dir[0] /= dl; dir[1] /= dl; dir[2] /= dl; }
            }
        }
        // Symmetric, as originally. Unclamping deceleration was TRIED on the
        // theory that the merge overshoot was the limiter refusing to brake:
        // it made the overshoot WORSE (3.38m -> 6.52m above the target), so
        // the limiter was never what held the climb on. Do not retry without
        // new evidence.
        float maxDv = INTERCEPT_MAX_ACCEL * dT;
        float dv = speed - lastLen;
        if (dv > maxDv) { speed = lastLen + maxDv; }
        else if (dv < -maxDv) { speed = lastLen - maxDv; }
        cmd[0] = dir[0] * speed; cmd[1] = dir[1] * speed; cmd[2] = dir[2] * speed;
    }
    lastCmd[0] = cmd[0]; lastCmd[1] = cmd[1]; lastCmd[2] = cmd[2];
    haveLast = true;

    // TIME-MATCHED VERTICAL ALLOCATION.
    //
    // A constant-bearing direction to a distant, higher target is almost
    // entirely HORIZONTAL - the altitude gap is a small part of a long
    // vector. Spending the whole speed budget along it demands a big tilt,
    // and tilt costs lift by cos(theta), so the vehicle pins itself to the
    // ground accelerating sideways and never climbs. Measured exactly that:
    // liftoff reached 0.88m climbing at 1.35 m/s, then the intercept engaged
    // and it sat at 0.52m for the whole run while the object flew over.
    // Raising the tilt limit makes this WORSE, not better.
    //
    // So the vertical channel gets what it needs FIRST: the rate that closes
    // the altitude gap over the time we have (t_int), clamped to what the
    // airframe can climb. Whatever speed is left goes horizontal. That
    // guarantees arriving at the object's ALTITUDE at the moment we arrive
    // at its position, instead of arriving level with the ground.
    if (mode3D) {
        // AIM BIAS: aim ABOVE the object, because the vehicle chronically
        // arrives BELOW it.
        //
        // Measured across six runs: the vertical error at closest approach
        // is below the target in five of them, and median altitude through
        // the engagement is 9.1-10.5m against an object at 11.0m. The cause
        // is structural, not noise - the vertical command is proportional to
        // the remaining gap, so the correction shrinks exactly as the gap
        // does, while tilting for horizontal closure keeps costing lift by
        // cos(theta). It asymptotes low instead of arriving level.
        //
        // This is the gun-laying answer from the Phalanx work: a systematic
        // miss is not noise to average away, it is a BIAS to correct. Aim
        // high by the observed sag so the sag lands the strike on centre.
        float vgap = R[2] - INTERCEPT_AIM_HIGH_M; // +ve = target is BELOW us
        float t_use = (t_int > 0.5f) ? t_int : 0.5f;
        // Time-matching ALONE dawdles: with a 10m gap and ~26s to intercept it
        // asks for 0.4 m/s and the vehicle is still low when the object
        // arrives - measured, the intercept landed 83% along the object's
        // track. Altitude is not just another axis to schedule, it is the
        // ENABLER: nothing can be intercepted from the ground, and every
        // second spent low is a second the horizontal closure cannot be used.
        // So climb at the gap-proportional rate (fast, early) or the
        // time-matched rate, whichever is GREATER, and let the clamps below
        // keep it inside what the frame and the controller can do.
        float v_time = vgap / t_use;
        float v_gapr = INTERCEPT_VERT_GAIN * vgap;
        float v_need = (fabsf(v_gapr) > fabsf(v_time)) ? v_gapr : v_time;
        // Never demand more climb than the frame can give, and taper near the
        // gap so the merge is level rather than still climbing.
        // The climb may never consume the WHOLE speed budget, or the
        // horizontal term below gets sqrt of a negative and is zeroed - the
        // vehicle then rises straight up with no closure at all and has to
        // stern-chase afterwards. That is precisely what happened:
        // INTERCEPT_MAX_CLIMB 3.0 against a 2.2 m/s budget zeroed horizontal
        // motion for the entire climb, and the intercepts landed 79-95% along
        // the object's track, soft, because a stern chase has almost no
        // closing speed left. Cap the climb at a FRACTION of the budget so
        // both axes make progress at once.
        float vcap = INTERCEPT_VERT_GAIN * fabsf(vgap);
        // THE CAP MUST NOT DEFEAT THE TIME MATCH. This was the whole vertical
        // miss (2026-08-10). v_need above already takes the GREATER of the
        // gap-proportional and time-matched rates - and then this cap, being
        // itself INTERCEPT_VERT_GAIN * vgap, clamped it straight back down to
        // the gap-proportional value. The time-matched term could never
        // survive, so the vertical channel was a pure proportional approach
        // with a 1/0.7 = 1.43s time constant while the endgame lasts ~0.7s:
        // structurally incapable of arriving level.
        //
        // Measured signature, two runs, confirmed by the FC's OWN log: the
        // vehicle tracked its vertical command to within 0.10 m/s all the way
        // through the merge, while that command decayed to 0.41-0.45 m/s with
        // 1.16-1.28m still to close. Guidance under-asked; the airframe was
        // never the limit. Horizontal at the same moment was 0.08-0.10m.
        //
        // RAISING THE CAP TO THE TIME-MATCHED RATE WAS TRIED AND IS WORSE.
        // Setting vcap = max(gap-proportional, |vgap|/t_go) with t_go the
        // sooner of t_int and range/vmax:
        //
        //   before (ekfA1/A2)  horiz 0.10 / 0.08   vert -1.16 / -1.28
        //   after  (vt2/vt3)   horiz 0.23 / 0.30   vert -1.41 / -1.51
        //
        // Worse on BOTH axes, which is the tell. vmax is a SHARED BUDGET -
        // the horizontal term is sqrt(vmax^2 - v_climb^2) - so buying climb
        // spends closure. At 2.2 m/s, demanding 1.32 m/s of climb instead of
        // 0.98 drops horizontal from 1.97 to 1.76 m/s, the merge happens
        // sooner (t+5.6-5.7s vs t+6.2s) and the vehicle is therefore LOWER
        // when it gets there. Under-asking was never the real constraint.
        //
        // The diagnosis that produced this attempt still stands and is worth
        // keeping: the FC's own log shows the vehicle tracking its vertical
        // command to 0.10 m/s while that command decayed to 0.41 m/s with
        // 1.16m to close. Guidance does under-ask. But the fix is not to ask
        // harder out of the same budget - it is to remove the competition,
        // either by reaching the target's altitude before committing
        // horizontally (the INTERCEPT_LEVEL_BAND gate, which currently
        // releases at 1.5m) or by giving the vertical channel authority that
        // does not come out of vmax at all.
        float budget_cap = INTERCEPT_CLIMB_FRAC * vmax;
        if (vcap > budget_cap) { vcap = budget_cap; }
        if (vcap > INTERCEPT_MAX_CLIMB) { vcap = INTERCEPT_MAX_CLIMB; }
        if (v_need > vcap) { v_need = vcap; }
        else if (v_need < -vcap) { v_need = -vcap; }

        cmd[2] = v_need;

        // CLIMB TO THE TARGET'S ALTITUDE BEFORE PURSUING HORIZONTALLY.
        //
        // Gated on the VERTICAL GAP TO THE TARGET, not absolute altitude. The
        // earlier version throttled horizontal only below a fixed 6m - but
        // the object is at 11m, so above 6m the vehicle committed horizontally
        // while still 5m low, arrived at horizontal alignment ~1m under the
        // target every run, and missed. The object is at a fixed height the
        // airframe can reach (peak altitude 11.4m measured), and getting to
        // that level FIRST removes the coupled vertical miss entirely: arrive
        // already level and let horizontal closure bring them together. The
        // geometry costs nothing - climbing straight to 11m (~4s) then
        // pursuing takes the same ~12s as chasing out low, because the object
        // passes overhead either way. It also stops tilting on the deck: at
        // launch the gap is ~11m so horizontal is throttled to near zero and
        // the airframe climbs out clean instead of grinding sideways.
        float vgap_abs = fabsf(R[2]);
        float launch_scale = 1.0f;
        if (vgap_abs > INTERCEPT_LEVEL_BAND) {
            float over = (vgap_abs - INTERCEPT_LEVEL_BAND) / INTERCEPT_LEVEL_RAMP;
            if (over > 1.0f) { over = 1.0f; }
            launch_scale = INTERCEPT_LAUNCH_HORIZ
                + (1.0f - INTERCEPT_LAUNCH_HORIZ) * (1.0f - over);
            // Full climb effort while closing the altitude gap.
            float climb_max = INTERCEPT_MAX_CLIMB;
            if (climb_max > vmax) { climb_max = vmax; }
            if (vgap < 0.0f && cmd[2] > -climb_max) {
                cmd[2] = -climb_max;          // object above: climb hard
            } else if (vgap > 0.0f && cmd[2] < climb_max) {
                cmd[2] = climb_max;           // object below: descend to it
            }
        }

        // Horizontal keeps the remainder of the speed budget...
        float horiz_budget = vmax * vmax - v_need * v_need;
        horiz_budget = (horiz_budget > 0.0f) ? sqrtf(horiz_budget) : 0.0f;

        // ...but is also PACED BY THE CLIMB. Arriving over the object's
        // position while still below its altitude is a guaranteed miss, and
        // it is what was happening: the climb is budget-limited to ~1.3 m/s
        // so 10m of altitude takes ~7.6s, while horizontal closure gets
        // there sooner. The vehicle showed up underneath, missed, and every
        // pass after that was a stern chase with no closing speed left.
        //
        // So if the vertical needs longer than the horizontal, slow the
        // horizontal to match. Better to arrive together than to arrive
        // early and low. Deliberately NOT applied in the endgame - inside
        // the merge the lead is doing the work and throttling it there would
        // just stall the strike.
        if (range > INTERCEPT_ENDGAME_DIST) {
            float hdist = sqrtf(R[0] * R[0] + R[1] * R[1]);
            float vdist = fabsf(R[2]);
            float vrate = fabsf(v_need);
            if (vrate > 0.05f && horiz_budget > 0.05f) {
                float t_vert = vdist / vrate;
                float t_horiz = hdist / horiz_budget;
                if (t_vert > t_horiz && t_vert > 0.1f) {
                    float paced = hdist / t_vert;
                    if (paced < horiz_budget) {
                        horiz_budget = paced;
                    }
                }
            }
        }

        horiz_budget *= launch_scale;

        float hmag = sqrtf(cmd[0] * cmd[0] + cmd[1] * cmd[1]);
        if (hmag > 1e-3f) {
            cmd[0] = cmd[0] / hmag * horiz_budget;
            cmd[1] = cmd[1] / hmag * horiz_budget;
        }
    }

    // HARD FLOOR. The guidance will chase whatever the tracker reports, and
    // after a strike the object is a FALLING BODY - so it chases it into the
    // ground. Two of five runs ended that way, descending steadily from
    // ~12m to the deck while still dutifully closing on a target that was
    // itself on its way down. Never accept a descent command below the
    // floor; if the object goes below it, the object is no longer a threat
    // and no longer worth following.
    if (mode3D) {
        float altitude = -cur_point[2];
        if (altitude < INTERCEPT_FLOOR_M && cmd[2] > 0.0f) {
            cmd[2] = 0.0f;                    // +Down = descending
        }
    }

    status->path_vector[0] = cmd[0];
    status->path_vector[1] = cmd[1];
    status->path_vector[2] = mode3D ? cmd[2] : 0.0f;

    // Position error toward the aim point, exactly as path_endpoint does with
    // its `diff`. This drives the follower's POSITION loop.
    //
    // Zeroing this was a real bug and it cost the first intercept a solid
    // hit. The reasoning was "an intercept has no line to hold, so there is
    // no cross-track correction" - true for the horizontal LINE sense, but
    // correction_vector[2] is also the only vertical position feedback the
    // controller gets. Without it the vertical channel ran on feed-forward
    // alone and sagged: at closest approach the vehicle was 28cm BELOW the
    // target and still descending, turning what should have been a centre
    // hit into a ~25mm graze that the IMU barely registered (icpt03: contact
    // confirmed by Gazebo at 0.31m, peak 1.40g).
    status->correction_vector[0] = toP[0];
    status->correction_vector[1] = toP[1];
    status->correction_vector[2] = mode3D ? toP[2] : 0.0f;

    // Progress reads as closure: 0 at handover range, 1 on contact. Anything
    // watching fractional_progress (PathStatus consumers, the RTB-land check)
    // sees a sane monotonic number as the range shrinks.
    status->fractional_progress = 1.0f - boundf(range / 30.0f, 0.0f, 1.0f);
    status->error = range;
}
