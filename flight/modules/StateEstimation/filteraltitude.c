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
 * V3 EXPERIMENT: this file's original body was a fixed-gain complementary
 * filter (predict via accel double-integration, correct via a constant
 * BaroKp/BaroKp^2 low-pass toward baro). That filter has no way to
 * distinguish "accelerometer bias has drifted" from "the vehicle is
 * undergoing a real, sustained acceleration" - both look identical to its
 * slow bias tracker - and its fixed, small baro-correction gain can't
 * out-pull a large sustained integration error once one occurs. This
 * replaces it with a real 3-state (altitude, velocity, accel-bias) Kalman
 * filter: same physical model, but the correction gain is derived each
 * step from propagated covariance instead of hand-picked, so a period of
 * high uncertainty (from a sustained real acceleration the process-noise
 * model didn't expect) automatically produces a stronger baro correction
 * gain, not a weaker one.
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
#include <pios_shmlog.h>
#include <attitudestate.h>
#include <altitudefiltersettings.h>
#include <homelocation.h>

#include <CoordinateConversions.h>

#ifdef SIMPOSIX
#include <stdio.h>
#include <sys/time.h>
#endif

// Private constants

#define STACK_REQUIRED 128

#define DT_ALPHA       1e-2f
#define DT_MIN         1e-6f
#define DT_MAX         1.0f
#define DT_AVERAGE     1e-3f

// Process/measurement noise. Unlike the old BaroKp/AccelDriftKi gains,
// these describe *uncertainty*, not a fixed blend rate - the Kalman gain
// each step is derived from these plus the propagated covariance, not
// picked directly.
// Process noise for the velocity/altitude states. This is NOT just
// accelerometer sensor noise: the predict step frequently runs with a stale
// accel sample (see accelBitOnEntry diagnostics), so during maneuvers the
// model error is on the order of the vehicle's actual acceleration. The
// original 1e-2 (0.1 m/s^2 sigma) let the covariance collapse after ~20s of
// quiet, consistent measurements - P[1][1] << R meant K ~ 0 and the filter
// went deaf: mission 14's onboard log shows GPS reporting a real 1 m/s
// descent at the first corner while the over-confident velocity state read
// "climbing 0.3" and ignored every innovation, trimming thrust into the
// floor. 1.0 (1 m/s^2 sigma) keeps the gains alive through maneuvers.
#define ACCEL_NOISE_VAR_MPS2SQ 1.0f   // unmodeled-acceleration process noise variance, (m/s^2)^2
#define BIAS_NOISE_VAR_MPS2SQ  1e-7f  // accel-bias random-walk variance per second, (m/s^2)^2/s - deliberately small, bias drifts slowly
#define BARO_NOISE_VAR_M2      0.25f  // barometer measurement noise variance, m^2 (~0.5m std dev)
#define GPSVEL_NOISE_VAR_M2S2  0.04f  // GPS vertical-velocity measurement noise variance, (m/s)^2 (~0.2 m/s std dev - u-blox VELNED grade)
#define INITIAL_P_ALT          1.0f
#define INITIAL_P_VEL          1.0f
#define INITIAL_P_BIAS         1.0f

static volatile bool reloadSettings;

// Private types
struct data {
    // state vector: [0]=altitude (m, up positive), [1]=velocity (m/s, up
    // positive), [2]=accelBias (m/s^2)
    float x[3];
    // covariance matrix, symmetric - stored in full for clarity, not just
    // the upper triangle.
    float P[3][3];

    float pos[3]; // position updates from other filters
    float vel[3]; // position updates from other filters

    PiOSDeltatimeConfig dt1config;
    PiOSDeltatimeConfig dt2config;
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
static void kfPredict(struct data *this, float accelMeas, float dT);
static void kfCorrectBaro(struct data *this, float baroMeas);


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

    this->x[0] = 0.0f;
    this->x[1] = 0.0f;
    this->x[2] = 0.0f;

    this->P[0][0] = INITIAL_P_ALT;
    this->P[0][1] = 0.0f;
    this->P[0][2] = 0.0f;
    this->P[1][0] = 0.0f;
    this->P[1][1] = INITIAL_P_VEL;
    this->P[1][2] = 0.0f;
    this->P[2][0] = 0.0f;
    this->P[2][1] = 0.0f;
    this->P[2][2] = INITIAL_P_BIAS;

    this->pos[0] = 0.0f;
    this->pos[1] = 0.0f;
    this->pos[2] = 0.0f;
    this->vel[0] = 0.0f;
    this->vel[1] = 0.0f;
    this->vel[2] = 0.0f;
    PIOS_DELTATIME_Init(&this->dt1config, DT_AVERAGE, DT_MIN, DT_MAX, DT_ALPHA);
    PIOS_DELTATIME_Init(&this->dt2config, DT_AVERAGE, DT_MIN, DT_MAX, DT_ALPHA);
    this->baroLast  = 0.0f;
    this->first_run = 1;
    HomeLocationg_eGet(&this->gravity);
    return 0;
}

/**
 * Predict step: propagate [altitude, velocity, accelBias] through the
 * strapdown model x_k = F*x_{k-1} + B*u_k, P_k = F*P_{k-1}*F^T + Q, where
 * u = accelMeas (control input, not a state) and the bias state is
 * subtracted from the accel input inside F/B's coupling (bias enters
 * with a negative sign, matching "measured = true + bias").
 */
static void kfPredict(struct data *this, float accelMeas, float dT)
{
    // F = [[1, dT, -0.5*dT^2], [0, 1, -dT], [0, 0, 1]]
    // B = [0.5*dT^2, dT, 0]^T applied to accelMeas
    float alt  = this->x[0] + this->x[1] * dT + 0.5f * (accelMeas - this->x[2]) * dT * dT;
    float vel  = this->x[1] + (accelMeas - this->x[2]) * dT;
    float bias = this->x[2];

    this->x[0] = alt;
    this->x[1] = vel;
    this->x[2] = bias;

    float F[3][3] = {
        { 1.0f, dT, -0.5f * dT * dT },
        { 0.0f, 1.0f, -dT           },
        { 0.0f, 0.0f, 1.0f          }
    };

    // Pp = F*P*F^T
    float FP[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            FP[i][j] = F[i][0] * this->P[0][j] + F[i][1] * this->P[1][j] + F[i][2] * this->P[2][j];
        }
    }
    float Pp[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Pp[i][j] = FP[i][0] * F[j][0] + FP[i][1] * F[j][1] + FP[i][2] * F[j][2];
        }
    }

    // Q = B * accelVar * B^T (accel measurement noise coupling into
    // altitude/velocity) plus a separate small random-walk term on bias.
    float B[3] = { 0.5f * dT * dT, dT, 0.0f };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Pp[i][j] += B[i] * ACCEL_NOISE_VAR_MPS2SQ * B[j];
        }
    }
    Pp[2][2] += BIAS_NOISE_VAR_MPS2SQ * dT;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->P[i][j] = Pp[i][j];
        }
    }
}

/**
 * Correct step: scalar measurement update from the barometer (H = [1,0,0]).
 * Kalman gain K = P*H^T / (H*P*H^T + R) is derived from the *current*
 * covariance, not a fixed constant - if the predict step above has been
 * running with a real, sustained accel-vs-bias mismatch (covariance
 * growing faster than the process-noise model assumed), this gain rises
 * automatically instead of staying pinned at a value tuned for quiet
 * hover noise.
 */
static void kfCorrectBaro(struct data *this, float baroMeas)
{
    float S = this->P[0][0] + BARO_NOISE_VAR_M2;
    float K[3] = { this->P[0][0] / S, this->P[1][0] / S, this->P[2][0] / S };

    float y = baroMeas - this->x[0];
    this->x[0] += K[0] * y;
    this->x[1] += K[1] * y;
    this->x[2] += K[2] * y;

    // P = (I - K*H) * P, H picks row 0
    float P0[3] = { this->P[0][0], this->P[0][1], this->P[0][2] };
    for (int i = 0; i < 3; i++) {
        this->P[i][0] -= K[i] * P0[0];
        this->P[i][1] -= K[i] * P0[1];
        this->P[i][2] -= K[i] * P0[2];
    }
}

/**
 * Correct step: scalar measurement update from GPS vertical velocity
 * (H = [0,1,0]). Without this, the velocity state is nearly inert: the
 * predict step frequently runs with stale accel (see the accelBitOnEntry
 * diagnostics) and baro's velocity-correction gain K[1] is small, so under
 * a REAL sustained climb the velocity state lagged reality by many seconds
 * - mission 12/13 onboard logs showed baro at 10m climbing 3 m/s while
 * x[1] read "descending 2 m/s", and the vertical loop closed a slow
 * porpoise/runaway through that wrong-sign damping. GPS Down velocity is
 * exactly the measurement the state needs (on real hardware this is u-blox
 * VELNED - the same source the UBX parser feeds GPSVelocitySensor from).
 * Also makes the accel-bias state observable from two independent
 * measurements instead of baro alone.
 */
static void kfCorrectVel(struct data *this, float velMeas)
{
    float S = this->P[1][1] + GPSVEL_NOISE_VAR_M2S2;
    float K[3] = { this->P[0][1] / S, this->P[1][1] / S, this->P[2][1] / S };

    float y = velMeas - this->x[1];

    this->x[0] += K[0] * y;
    this->x[1] += K[1] * y;
    this->x[2] += K[2] * y;

    // P = (I - K*H) * P, H picks row 1
    float P1[3] = { this->P[1][0], this->P[1][1], this->P[1][2] };
    for (int i = 0; i < 3; i++) {
        this->P[i][0] -= K[i] * P1[0];
        this->P[i][1] -= K[i] * P1[1];
        this->P[i][2] -= K[i] * P1[2];
    }
}

static filterResult filter(stateFilter *self, stateEstimation *state)
{
    struct data *this = (struct data *)self->localdata;

#ifdef SIMPOSIX
    {
        static uint32_t callCount = 0;
        static uint32_t lastPrintMs = 0;
        struct timeval tv;
        callCount++;
        gettimeofday(&tv, NULL);
        uint32_t nowMs = (uint32_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
        if (callCount == 1 || nowMs - lastPrintMs >= 1000) {
            lastPrintMs = nowMs;
            PIOS_SHMLOG_Printf("[SIMPOSIX-IFDEF-MARKER] filteraltitude.c(V3-KF) filter() ENTRY: callCount=%lu first_run=%d "
                   "state->updated=0x%02x accelBitOnEntry=%d\n",
                   (unsigned long)callCount, (int)this->first_run, (unsigned)state->updated,
                   (int)IS_SET(state->updated, SENSORUPDATES_accel));
            /* shmlog: no flush */
        }
    }
#endif

    if (reloadSettings) {
        reloadSettings = false;
        AltitudeFilterSettingsGet(&this->settings);
    }

    if (this->first_run) {
        // Same first_run gate fix as the original filter - see git history
        // for the filterbaro.c bit-clearing root cause this works around.
        if (IS_REAL(state->baro[0])) {
            this->first_run = 0;
            this->initTimer = xTaskGetTickCount();
        }
    } else {
        if (IS_SET(state->updated, SENSORUPDATES_pos)) {
            this->pos[0]  = state->pos[0];
            this->pos[1]  = state->pos[1];
            this->pos[2]  = state->pos[2];
            state->pos[2] = -this->x[0];
        }
        if (IS_SET(state->updated, SENSORUPDATES_vel)) {
            this->vel[0]  = state->vel[0];
            this->vel[1]  = state->vel[1];
            this->vel[2]  = state->vel[2];
            // Use the incoming GPS vertical velocity as a measurement
            // before publishing the filtered state (NED down -> filter's
            // altitude-up frame). The improved x[0] rides out through the
            // frequent accel/baro branches; deliberately NOT marking pos
            // updated here so downstream chain filters keep their cadence.
            kfCorrectVel(this, -this->vel[2]);
            state->vel[2] = -this->x[1];
        }
        if (IS_SET(state->updated, SENSORUPDATES_accel)) {
            // rotate accels into global coordinate frame
            AttitudeStateData att;
            AttitudeStateGet(&att);
            float Rbe[3][3];
            Quaternion2R(&att.q1, Rbe);
            float current = -(Rbe[0][2] * state->accel[0] + Rbe[1][2] * state->accel[1] + Rbe[2][2] * state->accel[2] + this->gravity);

            float dT = PIOS_DELTATIME_GetAverageSeconds(&this->dt1config);
            kfPredict(this, current, dT);

#ifdef SIMPOSIX
            {
                static int callCount = 0;
                static portTickType lastPrintTick = 0;
                callCount++;
                portTickType nowTick = xTaskGetTickCount();
                if (callCount == 1 || (nowTick - lastPrintTick) / portTICK_RATE_MS >= 1000) {
                    lastPrintTick = nowTick;
                    struct timeval tv;
                    gettimeofday(&tv, NULL);
                    double wallclock = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
                    PIOS_SHMLOG_Printf("[SIMPOSIX-IFDEF-MARKER] filteraltitude.c(V3-KF) predict: "
                           "t=%.3f callCount=%d dT=%.6f current=%.5f alt=%.5f vel=%.5f bias=%.5f "
                           "Palt=%.5f Pvel=%.5f Pbias=%.5f\n",
                           wallclock, callCount, (double)dT, (double)current,
                           (double)this->x[0], (double)this->x[1], (double)this->x[2],
                           (double)this->P[0][0], (double)this->P[1][1], (double)this->P[2][2]);
                    /* shmlog: no flush */
                }
            }
#endif

            state->pos[0]   = this->pos[0];
            state->pos[1]   = this->pos[1];
            state->pos[2]   = -this->x[0];
            state->updated |= SENSORUPDATES_pos;

            state->vel[0]   = this->vel[0];
            state->vel[1]   = this->vel[1];
            state->vel[2]   = -this->x[1];
            state->updated |= SENSORUPDATES_vel;
        }
        if (IS_SET(state->updated, SENSORUPDATES_baro)) {
#ifdef SIMPOSIX
            float altBefore = this->x[0];
            float velBefore = this->x[1];
#endif
            kfCorrectBaro(this, state->baro[0]);
            this->baroLast = state->baro[0];

#ifdef SIMPOSIX
            if (fabsf(this->x[1] - velBefore) > 3.0f || fabsf(this->x[0] - altBefore) > 3.0f) {
                PIOS_SHMLOG_Printf("[SIMPOSIX-IFDEF-MARKER] filteraltitude.c(V3-KF) correct spike: "
                       "baro=%.4f altBefore=%.4f altAfter=%.4f velBefore=%.4f velAfter=%.4f Palt=%.5f\n",
                       (double)state->baro[0], (double)altBefore, (double)this->x[0],
                       (double)velBefore, (double)this->x[1], (double)this->P[0][0]);
                /* shmlog: no flush */
            }
#endif

            state->pos[0]   = this->pos[0];
            state->pos[1]   = this->pos[1];
            state->pos[2]   = -this->x[0];
            state->updated |= SENSORUPDATES_pos;

            state->vel[0]   = this->vel[0];
            state->vel[1]   = this->vel[1];
            state->vel[2]   = -this->x[1];
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
