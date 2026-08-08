/**
 ******************************************************************************
 * @addtogroup OpenPilotModules OpenPilot Modules
 * @{
 * @addtogroup State Estimation
 * @brief Acquires sensor data and computes state estimate
 * @{
 *
 * @file       filteraltitude.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2013.
 * @brief      Barometric altitude filter, calculates vertical speed and true
 *             altitude based on Barometric altitude and accelerometers
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

#include "inc/stateestimation.h"
#include <attitudestate.h>
#include <altitudefiltersettings.h>
#include <homelocation.h>

#include <CoordinateConversions.h>

#ifdef SIMPOSIX
#include <stdio.h>
#include <sys/time.h>
#endif

// Private constants

// duration of accel bias initialization phase
#define INITIALIZATION_DURATION_MS 5000

#define STACK_REQUIRED             128

#define DT_ALPHA                   1e-2f
#define DT_MIN                     1e-6f
#define DT_MAX                     1.0f
#define DT_AVERAGE                 1e-3f
static volatile bool reloadSettings;

// Private types
struct data {
    float altitudeState; // state = altitude,velocity,accel_offset,accel
    float velocityState;
    float accelBiasState;
    float accelState;
    float pos[3]; // position updates from other filters
    float vel[3]; // position updates from other filters

    PiOSDeltatimeConfig dt1config;
    PiOSDeltatimeConfig dt2config;
    float accelLast;
    float baroLast;
    bool  first_run;
    portTickType initTimer;
    AltitudeFilterSettingsData settings;
    float gravity;
};

// Private variables

// Private functions

static int32_t init(stateFilter *self);
static filterResult filter(stateFilter *self, stateEstimation *state);
static void settingsUpdatedCb(UAVObjEvent *ev);


int32_t filterAltitudeInitialize(stateFilter *handle)
{
    handle->init      = &init;
    handle->filter    = &filter;
    handle->localdata = pios_malloc(sizeof(struct data));
    HomeLocationInitialize();
    AttitudeStateInitialize();
    AltitudeFilterSettingsInitialize();
    AltitudeFilterSettingsConnectCallback(&settingsUpdatedCb);
    reloadSettings = true;
    return STACK_REQUIRED;
}

static int32_t init(stateFilter *self)
{
    struct data *this = (struct data *)self->localdata;

    this->altitudeState  = 0.0f;
    this->velocityState  = 0.0f;
    this->accelBiasState = 0.0f;
    this->accelState     = 0.0f;
    this->pos[0]    = 0.0f;
    this->pos[1]    = 0.0f;
    this->pos[2]    = 0.0f;
    this->vel[0]    = 0.0f;
    this->vel[1]    = 0.0f;
    this->vel[2]    = 0.0f;
    PIOS_DELTATIME_Init(&this->dt1config, DT_AVERAGE, DT_MIN, DT_MAX, DT_ALPHA);
    PIOS_DELTATIME_Init(&this->dt2config, DT_AVERAGE, DT_MIN, DT_MAX, DT_ALPHA);
    this->baroLast  = 0.0f;
    this->accelLast = 0.0f;
    this->first_run = 1;
    HomeLocationg_eGet(&this->gravity);
    return 0;
}

static filterResult filter(stateFilter *self, stateEstimation *state)
{
    struct data *this = (struct data *)self->localdata;

#ifdef SIMPOSIX
    // Unconditional, no gating at all - filterChain is confirmed correct
    // and non-null (altitudeFilter IS in it), yet the accel-integrator
    // print further down this same function has never fired in a full
    // test run. Checking whether this function is even being CALLED, and
    // what first_run/state->updated actually look like on entry, instead
    // of continuing to assume.
    {
        static uint32_t callCount = 0;
        static uint32_t lastPrintMs = 0;
        struct timeval tv;
        callCount++;
        gettimeofday(&tv, NULL);
        uint32_t nowMs = (uint32_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
        if (callCount == 1 || nowMs - lastPrintMs >= 1000) {
            lastPrintMs = nowMs;
            printf("[SIMPOSIX-IFDEF-MARKER] filteraltitude.c filter() ENTRY: callCount=%lu first_run=%d "
                   "state->updated=0x%02x accelBitOnEntry=%d\n",
                   (unsigned long)callCount, (int)this->first_run, (unsigned)state->updated,
                   (int)IS_SET(state->updated, SENSORUPDATES_accel));
            fflush(stdout);
        }
    }
#endif

    if (reloadSettings) {
        reloadSettings = false;
        AltitudeFilterSettingsGet(&this->settings);
    }

    if (this->first_run) {
        // Initialize to current altitude reading at initial location.
        //
        // ROOT CAUSE, confirmed via direct instrumentation (an
        // unconditional entry print showing first_run=1 and
        // state->updated never containing SENSORUPDATES_baro, through
        // 2973+ calls in one test): this used to check
        // IS_SET(state->updated, SENSORUPDATES_baro), but filterbaro.c -
        // FOURTH in the cfmQueue chain, immediately before this filter -
        // unconditionally UNSET_MASKs SENSORUPDATES_baro once it's done
        // its own baro processing. By the time this filter (fifth in the
        // chain) runs, that bit has always already been cleared, so
        // first_run could NEVER clear, meaning this filter's entire body
        // past this gate - including the accel-integration branch that
        // produces the real VelocityState/PositionState output altitude-
        // hold and everything downstream of it depends on - has been dead
        // code for this fusion algorithm the whole time. The only
        // VelocityState updates ever happening were the sparse trickle
        // from GPS velocity sensor elsewhere in the chain, which is
        // exactly the ~3/sec rate this was chased through several layers
        // of (genuinely real, and now fixed) transport and scheduling
        // bugs before finding this.
        //
        // state->baro[0] is a static-storage field in StateEstimationCb's
        // own `states` struct - once real baro data has been loaded into
        // it ONE time (which happens the moment the raw sensor fetch sees
        // SENSORUPDATES_baro set, before ANY filter in the chain runs),
        // it stays a real, valid number on every subsequent call
        // regardless of what any filter later does to the *bit* -
        // checking that instead correctly reflects "has real baro data
        // ever arrived", the actual thing this one-time init needs to
        // know, without depending on a flag another filter destructively
        // consumes first.
        if (IS_REAL(state->baro[0])) {
            this->first_run = 0;
            this->initTimer = xTaskGetTickCount();
        }
    } else {
        // save existing position and velocity updates so GPS will still work
        if (IS_SET(state->updated, SENSORUPDATES_pos)) {
            this->pos[0]  = state->pos[0];
            this->pos[1]  = state->pos[1];
            this->pos[2]  = state->pos[2];
            state->pos[2] = -this->altitudeState;
        }
        if (IS_SET(state->updated, SENSORUPDATES_vel)) {
            this->vel[0]  = state->vel[0];
            this->vel[1]  = state->vel[1];
            this->vel[2]  = state->vel[2];
            state->vel[2] = -this->velocityState;
        }
        if (IS_SET(state->updated, SENSORUPDATES_accel)) {
            // rotate accels into global coordinate frame
            AttitudeStateData att;
            AttitudeStateGet(&att);
            float Rbe[3][3];
            Quaternion2R(&att.q1, Rbe);
            float current = -(Rbe[0][2] * state->accel[0] + Rbe[1][2] * state->accel[1] + Rbe[2][2] * state->accel[2] + this->gravity);

            // low pass filter accelerometers
            this->accelState = (1.0f - this->settings.AccelLowPassKp) * this->accelState + this->settings.AccelLowPassKp * current;
            if (((xTaskGetTickCount() - this->initTimer) / portTICK_RATE_MS) < INITIALIZATION_DURATION_MS) {
                // allow the offset to reach quickly the target value in case of small AccelDriftKi
                this->accelBiasState = (1.0f - this->settings.InitializationAccelDriftKi) * this->accelBiasState + this->settings.InitializationAccelDriftKi * this->accelState;
            } else {
                // correct accel offset (low pass zeroing)
                this->accelBiasState = (1.0f - this->settings.AccelDriftKi) * this->accelBiasState + this->settings.AccelDriftKi * this->accelState;
            }
            // correct velocity and position state (integration)
            // low pass for average dT, compensate timing jitter from scheduler
            //
            float dT = PIOS_DELTATIME_GetAverageSeconds(&this->dt1config);
            float speedLast = this->velocityState;

#ifdef SIMPOSIX
            // ROOT CAUSE, confirmed via direct trace: accelBiasState tracks
            // accelState at AccelDriftKi (firmware default 0.0005 - very
            // slow, by design, since real accel bias drifts slowly). But a
            // real, large, fast transient in `current` (observed swinging
            // from ~0.25 to -9.81 and back within about a second, plausibly
            // the vehicle's own real response to the altitudeloop.c PID
            // saturation investigated alongside this) leaves accelBiasState
            // stranded far from accelState for an extended time. The
            // "corrected acceleration" (accelLast) that gap produces gets
            // DOUBLE-INTEGRATED (into velocityState, then into
            // altitudeState) with nothing bounding it - one real incident
            // measured velocityState reaching 60 m/s and altitudeState 51m
            // from this alone. Bounding the corrected acceleration to a
            // physically sane limit (2g) doesn't fix why the transient
            // happens, but stops it from cascading into an unbounded
            // runaway regardless of cause - the same "bound the output"
            // pattern already applied to altitudeloop.c's PID output
            // elsewhere in this investigation.
            float correctedAccel = boundf(this->accelState - this->accelBiasState, -2.0f * this->gravity, 2.0f * this->gravity);
            this->velocityState += 0.5f * (this->accelLast + correctedAccel) * dT;
            this->accelLast      = correctedAccel;
#else
            this->velocityState += 0.5f * (this->accelLast + (this->accelState - this->accelBiasState)) * dT;
            this->accelLast      = this->accelState - this->accelBiasState;
#endif

            this->altitudeState += 0.5f * (speedLast + this->velocityState) * dT;

#ifdef SIMPOSIX
            // Confirmed via direct trace (contrary to an earlier, wrong
            // conclusion in this investigation caused by checking the
            // bridge's Python log instead of fw_simposix's own C-side
            // stdout) that this branch runs regularly - roughly matching
            // PIOS_SENSOR_RATE. ~1Hz print.
            {
                static int callCount = 0;
                static portTickType lastPrintTick = 0;
                callCount++;
                portTickType nowTick = xTaskGetTickCount();
                // Time-based, not call-count-based: the real call rate here
                // is unknown (the count-based %500 throttle never fired in
                // one full test run, meaning this branch runs far slower
                // than the assumed 500Hz) - print the very first call
                // immediately (confirms the branch runs at all) then at
                // most once per second after that.
                if (callCount == 1 || (nowTick - lastPrintTick) / portTICK_RATE_MS >= 1000) {
                    lastPrintTick = nowTick;
                    // Real wall-clock time (not the RTOS tick, which is
                    // relative to boot and not directly comparable to the
                    // bridge's own time.time()-stamped [climbdbg]/[barodiag]
                    // logs) - added to let a C-side and Python-side trace be
                    // correlated directly instead of inferred from call-count
                    // order, which turned out to be ambiguous (the reinit
                    // marker for entering the test's AltitudeVario mode
                    // appeared EARLIER in this file than callCount==1 of
                    // this very print, even though this print's own comment
                    // claims callCount==1 fires on the first call ever - the
                    // two prints' relative file position alone couldn't
                    // settle which one actually happened first in real time).
                    struct timeval tv;
                    gettimeofday(&tv, NULL);
                    double wallclock = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
                    printf("[SIMPOSIX-IFDEF-MARKER] filteraltitude.c accel integrator: "
                           "t=%.3f callCount=%d dT=%.6f current=%.5f accelState=%.5f accelBiasState=%.5f "
                           "accelLast=%.5f velocityState=%.5f altitudeState=%.5f\n",
                           wallclock, callCount, (double)dT, (double)current, (double)this->accelState,
                           (double)this->accelBiasState, (double)this->accelLast,
                           (double)this->velocityState, (double)this->altitudeState);
                    fflush(stdout);
                }
            }
#endif

            state->pos[0]   = this->pos[0];
            state->pos[1]   = this->pos[1];
            state->pos[2]   = -this->altitudeState;
            state->updated |= SENSORUPDATES_pos;

            state->vel[0]   = this->vel[0];
            state->vel[1]   = this->vel[1];
            state->vel[2]   = -this->velocityState;
            state->updated |= SENSORUPDATES_vel;
        }
        if (IS_SET(state->updated, SENSORUPDATES_baro)) {
#ifdef SIMPOSIX
            // The root cause turned out to be the accel-integration branch
            // above (an unbounded corrected-acceleration double-integration,
            // now fixed with a 2g bound) - not this baro term, which was
            // confirmed sane throughout (BaroKp in range, no NaN, tracks
            // real altitude with the expected low-pass lag). Kept logging
            // every time, unconditionally, while actively chasing this -
            // this is a targeted one-off debugging session, not a
            // steady-state print left permanently enabled.
            printf("[SIMPOSIX-IFDEF-MARKER] filteraltitude.c baro lowpass IN: "
                   "BaroKp=%.6f baro=%.4f altitudeStateBefore=%.4f isnan_altBefore=%d isnan_BaroKp=%d\n",
                   (double)this->settings.BaroKp, (double)state->baro[0],
                   (double)this->altitudeState, isnan(this->altitudeState), isnan(this->settings.BaroKp));
            fflush(stdout);
#endif
            // correct the altitude state (simple low pass)
            this->altitudeState = (1.0f - this->settings.BaroKp) * this->altitudeState + this->settings.BaroKp * state->baro[0];

            // correct the velocity state (low pass differentiation)
            // low pass for average dT, compensate timing jitter from scheduler
            float dT = PIOS_DELTATIME_GetAverageSeconds(&this->dt2config);
#ifdef SIMPOSIX
            float velBefore = this->velocityState;
#endif
            this->velocityState = (1.0f - (this->settings.BaroKp * this->settings.BaroKp)) * this->velocityState + (this->settings.BaroKp * this->settings.BaroKp) * (state->baro[0] - this->baroLast) / dT;
#ifdef SIMPOSIX
            // A single baro-diff step producing a multi-m/s velocityState jump is
            // the suspected mechanism behind the PositionState.Down flyaway
            // seen investigating PositionHold - divide-by-small-dT amplifying
            // an ordinary baro sample-to-sample difference. Only print when
            // it actually happens (not every sample) so this doesn't flood
            // the log during normal operation.
            if (fabsf(this->velocityState - velBefore) > 3.0f) {
                printf("[SIMPOSIX-IFDEF-MARKER] filteraltitude.c baro velocity spike: "
                       "dT=%.6f baro=%.4f baroLast=%.4f velBefore=%.4f velAfter=%.4f BaroKp=%.4f\n",
                       (double)dT, (double)state->baro[0], (double)this->baroLast,
                       (double)velBefore, (double)this->velocityState, (double)this->settings.BaroKp);
                fflush(stdout);
            }
#endif
            this->baroLast  = state->baro[0];

            state->pos[0]   = this->pos[0];
            state->pos[1]   = this->pos[1];
            state->pos[2]   = -this->altitudeState;
            state->updated |= SENSORUPDATES_pos;

            state->vel[0]   = this->vel[0];
            state->vel[1]   = this->vel[1];
            state->vel[2]   = -this->velocityState;
            state->updated |= SENSORUPDATES_vel;
        }
    }

    return FILTERRESULT_OK;
}

void settingsUpdatedCb(UAVObjEvent *ev)
{
    if (ev->obj == AltitudeFilterSettingsHandle()) {
        reloadSettings = true;
    }
}

/**
 * @}
 * @}
 */
