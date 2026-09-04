/**
 ******************************************************************************
 * @addtogroup Modules
 * @{
 * @addtogroup AltFilterModule Barometric altitude filter
 * @brief Turns a barometer into PositionState.Down and VelocityState.Down,
 *        which is the one thing standing between this firmware and a working
 *        AltitudeHold thrust mode.
 *
 * Everything else was already here and it took reading the tree to notice:
 *   - Stabilization/altitudeloop.c IS the altitude-hold controller, and it is
 *     already compiled in (the Stabilization Makefile wildcards every .c).
 *   - outerloop.c already calls stabilizationAltitudeHold() whenever the
 *     thrust mode is ALTITUDEHOLD or ALTITUDEVARIO.
 *   - altitudeloop reads PositionState.Down and VelocityState.Down.
 * Nothing compiled into this target published those two. That is the entire
 * gap, and this module fills it.
 *
 * Why not StateEstimation, which has a perfectly good filteraltitude.c: that
 * module also writes AttitudeState, so running it alongside the CC
 * complementary filter in modules/Attitude means two writers fighting over
 * the vehicle's attitude. This target deliberately runs the CC filter (it is
 * the twin of an ESP32 board that does), so the altitude estimate is split
 * out instead. The Kalman below is the same 3-state design as
 * filteraltitude.c, with its noise constants, for the same reasons its header
 * gives: a fixed-gain complementary filter cannot tell "accel bias drifted"
 * from "the vehicle is really accelerating".
 *
 * Two sources of BaroSensor are supported, because the same module has to
 * serve both the posix twin and real hardware:
 *   - if a PIOS_SENSORS_TYPE_1AXIS_BARO is registered (e.g. the BMP280 on
 *     LiteWing's I2C0), poll it and publish BaroSensor ourselves;
 *   - otherwise consume whatever BaroSensor arrives over UAVTalk, which is
 *     how the Gazebo bridge feeds simulated pressure to the twin.
 *
 * @see        The GNU Public License (GPL) Version 3
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
#include "inc/altfilter.h"

#include <barosensor.h>
#include <accelstate.h>
#include <attitudestate.h>
#include <positionstate.h>
#include <velocitystate.h>
#include <flightstatus.h>
#include <CoordinateConversions.h>
#include <pios_sensors.h>
#include <pios_constants.h>
#include <math.h>
#include <string.h>

#define STACK_SIZE_BYTES 1536
#define TASK_PRIORITY    (tskIDLE_PRIORITY + 1)
#define LOOP_MS          20                  /* 50 Hz: a baro is not fast    */
#define DT               (LOOP_MS / 1000.0f)

/* Same constants filteraltitude.c uses, and for the reasons documented there. */
#define BARO_NOISE_VAR_M2      0.25f   /* ~0.5 m std dev                      */
#define ACCEL_NOISE_VAR_MPS2SQ 1.0f    /* unmodelled acceleration             */
#define BIAS_NOISE_VAR_MPS2SQ  1e-7f   /* accel bias random walk, per second  */

static xTaskHandle taskHandle;
static bool altFilterEnabled;

/* x = [down (m, +down), downVelocity (m/s), accelBias (m/s^2)] */
static float x[3];
static float P[3][3];
static bool  primed;
static float baroRef;                  /* baro altitude at first fix, so Down
                                        * starts at 0 rather than at whatever
                                        * height the launch site happens to be */
static const PIOS_SENSORS_Instance *baroInstance;

static void AltFilterTask(void *parameters);

int32_t AltFilterInitialize(void)
{
    BaroSensorInitialize();
    AccelStateInitialize();
    AttitudeStateInitialize();
    PositionStateInitialize();
    VelocityStateInitialize();
    FlightStatusInitialize();
    altFilterEnabled = true;
    return 0;
}

int32_t AltFilterStart(void)
{
    if (altFilterEnabled) {
        xTaskCreate(AltFilterTask, "AltFilter", STACK_SIZE_BYTES / 4, NULL,
                    TASK_PRIORITY, &taskHandle);
    }
    return 0;
}
MODULE_INITCALL(AltFilterInitialize, AltFilterStart);

static void kfReset(float down0)
{
    x[0] = down0;
    x[1] = 0.0f;
    x[2] = 0.0f;
    memset(P, 0, sizeof(P));
    P[0][0] = 1.0f;
    P[1][1] = 1.0f;
    P[2][2] = 0.1f;
}

/* Propagate [down, downVel, accelBias] with the measured down-acceleration.
 * u is TRUE acceleration (specific force plus gravity), bias-corrected. */
static void kfPredict(float accelDown, float dT)
{
    float u = accelDown - x[2];

    x[0] += x[1] * dT + 0.5f * u * dT * dT;
    x[1] += u * dT;

    /* P = F P F' + Q, done as an explicit matrix product.
     *
     * This was originally hand-expanded into scalar terms and the expansion
     * was WRONG: the position/velocity cross-covariance never grew, so the
     * baro correction gain K[1] stayed near zero and a velocity error took
     * tens of seconds to bleed off. Measured against Gazebo truth the filter
     * claimed +3.16 m/s while the vehicle hovered at +0.02. Three states is
     * small enough that the loop costs nothing and cannot be mis-expanded.
     *
     * F = [[1, dT, -dT^2/2],
     *      [0,  1,     -dT],
     *      [0,  0,       1]]
     * (the accel-bias column is negative because u = accelDown - bias) */
    const float h = 0.5f * dT * dT;
    const float F[3][3] = {
        { 1.0f, dT,   -h   },
        { 0.0f, 1.0f, -dT  },
        { 0.0f, 0.0f, 1.0f },
    };
    float FP[3][3], Pn[3][3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float acc = 0.0f;
            for (int k = 0; k < 3; k++) {
                acc += F[i][k] * P[k][j];
            }
            FP[i][j] = acc;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float acc = 0.0f;
            for (int k = 0; k < 3; k++) {
                acc += FP[i][k] * F[j][k];   /* * F' */
            }
            Pn[i][j] = acc;
        }
    }

    /* Q: unmodelled acceleration enters through position and velocity as
     * [dT^2/2, dT]', the bias random-walks slowly. */
    Pn[0][0] += ACCEL_NOISE_VAR_MPS2SQ * h * h;
    Pn[0][1] += ACCEL_NOISE_VAR_MPS2SQ * h * dT;
    Pn[1][0] += ACCEL_NOISE_VAR_MPS2SQ * h * dT;
    Pn[1][1] += ACCEL_NOISE_VAR_MPS2SQ * dT * dT;
    Pn[2][2] += BIAS_NOISE_VAR_MPS2SQ * dT;

    memcpy(P, Pn, sizeof(P));
}

/* Scalar measurement update from the barometer, H = [1, 0, 0]. */
static void kfCorrectBaro(float downMeas)
{
    float S = P[0][0] + BARO_NOISE_VAR_M2;

    if (S < 1e-6f) {
        return;
    }
    float K0 = P[0][0] / S;
    float K1 = P[1][0] / S;
    float K2 = P[2][0] / S;
    float y  = downMeas - x[0];

    x[0] += K0 * y;
    x[1] += K1 * y;
    x[2] += K2 * y;

    float p00 = P[0][0], p01 = P[0][1], p02 = P[0][2];

    P[0][0] -= K0 * p00; P[0][1] -= K0 * p01; P[0][2] -= K0 * p02;
    P[1][0] -= K1 * p00; P[1][1] -= K1 * p01; P[1][2] -= K1 * p02;
    P[2][0] -= K2 * p00; P[2][1] -= K2 * p01; P[2][2] -= K2 * p02;
}

/* If a barometer is registered with PIOS_SENSORS, poll it and publish
 * BaroSensor. Returns true if we produced a sample this pass. */
static bool pollRegisteredBaro(void)
{
    /* Defensive even with the registry fixed: .poll and .fetch are OPTIONAL
     * in PIOS_SENSORS_Driver -- queue-based drivers leave them NULL and set
     * is_polled = false. Calling them unchecked is how this module first
     * segfaulted the firmware. */
    if (!baroInstance || !baroInstance->driver
        || !baroInstance->driver->is_polled
        || !baroInstance->driver->poll || !baroInstance->driver->fetch) {
        return false;
    }
    if (!baroInstance->driver->poll(baroInstance->context)) {
        return false;
    }

    PIOS_SENSORS_1Axis_SensorsWithTemp s;
    baroInstance->driver->fetch(&s, sizeof(s), baroInstance->context);

    /* s.sample is PASCALS -- see the units note in pios_bmp280.c. */
    float altitude = 44330.0f
                     * (1.0f - powf(s.sample / PIOS_CONST_MKS_STD_ATMOSPHERE_F, (1.0f / 5.255f)));

    if (isnan(altitude)) {
        return false;
    }

    BaroSensorData baro;
    baro.Pressure    = s.sample;
    baro.Temperature = s.temperature;
    baro.Altitude    = altitude;
    BaroSensorSet(&baro);
    return true;
}

static void AltFilterTask(__attribute__((unused)) void *parameters)
{
    portTickType lastSysTime = xTaskGetTickCount();

    baroInstance = PIOS_SENSORS_GetInstanceByType(NULL, PIOS_SENSORS_TYPE_1AXIS_BARO);
    primed = false;

    while (1) {
        vTaskDelayUntil(&lastSysTime, LOOP_MS / portTICK_RATE_MS);

        /* On real hardware we own the baro; on the twin someone else feeds
         * BaroSensor over UAVTalk and this is a no-op. */
        pollRegisteredBaro();

        BaroSensorData baro;
        BaroSensorGet(&baro);
        if (isnan(baro.Altitude)) {
            continue;
        }

        /* Hold the filter in reset while DISARMED, re-zeroing the reference
         * every pass.
         *
         * Two reasons, one of which cost an afternoon:
         *  - the CC complementary filter spends its first several seconds
         *    converging, so AttitudeState is garbage and the rotation below
         *    turns a perfectly good accelerometer into a garbage vertical
         *    acceleration. Integrating that put the estimate 2.6 m up and
         *    5.1 m/s climbing while the airframe sat on the ground, and
         *    because P had collapsed by then it could only crawl back --
         *    which reads as a badly tuned filter and is not one.
         *  - altitude hold should reference the point you armed at anyway.
         * So the estimate only starts integrating once the vehicle is armed,
         * by which time attitude is settled. */
        FlightStatusData fs;
        FlightStatusGet(&fs);
        if (fs.Armed != FLIGHTSTATUS_ARMED_ARMED) {
            baroRef = baro.Altitude;
            kfReset(0.0f);
            primed = true;
            continue;
        }
        if (!primed) {
            baroRef = baro.Altitude;
            kfReset(0.0f);
            primed = true;
            continue;
        }

        /* Down-axis acceleration in the earth frame. Quaternion2R gives Rbe,
         * which rotates EARTH -> BODY, so body -> earth is its transpose and
         * the down component is column 2. Specific force at rest reads
         * (0,0,-g) in this convention, so adding gravity yields zero true
         * acceleration when stationary. */
        AttitudeStateData att;
        AccelStateData acc;
        AttitudeStateGet(&att);
        AccelStateGet(&acc);

        float q[4] = { att.q1, att.q2, att.q3, att.q4 };
        float Rbe[3][3];
        Quaternion2R(q, Rbe);

        float accelDown = Rbe[0][2] * acc.x + Rbe[1][2] * acc.y + Rbe[2][2] * acc.z
                          + PIOS_CONST_MKS_GRAV_ACCEL_F;

        kfPredict(accelDown, DT);

        /* If the estimate has run away from the barometer by more than any
         * real excursion could explain, the covariance has collapsed around a
         * wrong state and no amount of correction will pull it back quickly.
         * Re-inflate rather than crawl. */
        float meas = -(baro.Altitude - baroRef);   /* baro is UP, state is DOWN */
        if (fabsf(meas - x[0]) > 10.0f) {
            P[0][0] += 25.0f;
            P[1][1] += 25.0f;
            P[2][2] += 1.0f;
        }
        kfCorrectBaro(meas);

        PositionStateData pos;
        VelocityStateData vel;
        PositionStateGet(&pos);
        VelocityStateGet(&vel);
        pos.Down = x[0];
        vel.Down = x[1];
        PositionStateSet(&pos);
        VelocityStateSet(&vel);
    }
}

/**
 * @}
 * @}
 */
