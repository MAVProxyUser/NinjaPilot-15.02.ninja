/**
 ******************************************************************************
 * @addtogroup OpenPilotModules OpenPilot Modules
 * @{
 * @addtogroup FlipModule Flip Module
 * @brief Onboard backflip sequencer, ArduCopter-flip.pde style
 * @{
 *
 * @file       flip.c
 * @author     NinjaPilot, 2026
 *
 * The ground side (GCS, bridge, or later a transmitter switch) writes
 * FlipStatus.Command = Flip; everything after that happens HERE, at task
 * rate against loop-fresh attitude and gyro data. The ground-piloted
 * version of this maneuver (wroom_pilot.py) fought a ~0.25s stick
 * transport lag at every step - at 460 deg/s that is 115 degrees of
 * rotation the endgame had to predict across, and every drift outlier
 * traced to that prediction being wrong. Onboard there is nothing to
 * predict: the taper reads the integrated gyro angle directly and lands
 * the rotation ON level.
 *
 * Ownership: while State is Punch/Rotate/Catch, stabilizedhandler.c
 * defers (it checks FlipStatus), so this module is the sole writer of
 * StabilizationDesired - same single-owner discipline as ArduCopter's
 * mode takeover. Disarming, leaving Stabilized1/2, or the sequence
 * timeout releases ownership immediately.
 *
 * The sequence and its constants are the ones proven in ~60 simulated
 * flips of the piloted version: near-max punch while level (level
 * flight needs no differential headroom), thrust profiled by the tilt
 * through the rotation (torque scales with collective; inverted thrust
 * is wasted), and a fixed-collective dead-stick catch (every clever
 * catch - tilt-gated throttle, brake tilt, level-seek - measured worse).
 *
 * @see        The GNU Public License (GPL) Version 3
 *****************************************************************************/

#include "openpilot.h"
#include "inc/flip.h"

#include <attitudestate.h>
#include <gyrostate.h>
#include <flightstatus.h>
#include <flipstatus.h>
#include <stabilizationdesired.h>

#include <mathmisc.h>
#include <math.h>

// Task
#define STACK_SIZE_BYTES  1024
#define TASK_PRIORITY     (tskIDLE_PRIORITY + 2)
#define LOOP_MS           10     // 100 Hz sequencing against 500 Hz-fresh data

// Maneuver constants (from the piloted tune; see wroom_pilot.py history)
#define FLIP_PUNCH_THRUST 0.95f
#define FLIP_PUNCH_MS     900
#define FLIP_RATE_MAX     460.0f  // deg/s; must be inside the bank's ManualRate/MaximumRate
#define FLIP_TAPER_GAIN   1.9f   // deg/s of commanded rate per deg remaining.
                                  // NOT higher, NOT a trapezoid: gain 3.5 blew
                                  // through level at full rate (braking needs
                                  // ~200 deg of physics), and a 900 deg/s^2
                                  // trapezoid demanded torque the mixer does not
                                  // have at flip collective - the vehicle exited
                                  // with 355 deg/s residual and the catch spent
                                  // 10m of sky arresting it. 1.9 is the gain the
                                  // ground-piloted flips EFFECTIVELY flew (their
                                  // 3.0 through 0.25s of lag) across ~40 clean
                                  // maneuvers: gentle enough for the rate loop to
                                  // actually track, so the residual at level is
                                  // small enough for the spin-kill beat.
#define FLIP_SPINKILL_MS  300     // rate-zero beat after the rotation, before the
                                  // Attitude catch - Attitude cannot out-rate a
                                  // residual spin (proven twice, ground and board)
#define FLIP_THR_UP       0.60f   // collective while thrust points up-ish (cos > 0.35)
#define FLIP_THR_INV      0.10f   // collective while inverted
#define FLIP_ROTATE_MS_MAX 2500
#define FLIP_EXIT_DEG     352.0f  // land just shy of level; the catch closes the rest
#define FLIP_CATCH_THRUST 0.90f   // NOT higher: full collective leaves the mixer no differential
#define FLIP_CATCH_LEAN   0.0f    // MEASURED AND ZEROED: a fixed -8 deg nose-down
                                  // lean (open-loop brake against the deterministic
                                  // southward fling) DOUBLED the drift to 36-47m -
                                  // the fling varies flip to flip and a sensorless
                                  // lean overcorrects into a northward streak. The
                                  // board arrests VERTICALLY only; horizontal
                                  // braking belongs to whoever can see velocity
                                  // (the ground pilot's recovery, or a human).
#define FLIP_CATCH_MS     1400   // arrest MOST of the fall, then hand off: this
                                 // board has NO vertical-velocity sensor, so it
                                 // cannot exit on "arrested"; 1400ms at 0.90 takes
                                 // a proper flip's -4 m/s down to about -1 and
                                 // costs 1s less horizontal coasting than the
                                 // 2400ms version (whose dead-stick drift ran
                                 // 15-20m). The recovering pilot inherits a small
                                 // residual sink it can see and null.
#define FLIP_LEVEL_DEG    25.0f   // required entry attitude

static xTaskHandle taskHandle;
static bool flipEnabled;

static void FlipTask(void *parameters);

int32_t FlipInitialize(void)
{
    FlipStatusInitialize();
    flipEnabled = true;
    return 0;
}

int32_t FlipStart(void)
{
    if (flipEnabled) {
        xTaskCreate(FlipTask, "Flip", STACK_SIZE_BYTES / 4, NULL, TASK_PRIORITY, &taskHandle);
    }
    return 0;
}
MODULE_INITCALL(FlipInitialize, FlipStart);

static void set_state(FlipStatusData *st, FlipStatusStateOptions state)
{
    st->State = state;
    FlipStatusSet(st);
}

static bool flying_stabilized(void)
{
    FlightStatusData fs;

    FlightStatusGet(&fs);
    return fs.Armed == FLIGHTSTATUS_ARMED_ARMED &&
           (fs.FlightMode == FLIGHTSTATUS_FLIGHTMODE_STABILIZED1 ||
            fs.FlightMode == FLIGHTSTATUS_FLIGHTMODE_STABILIZED2);
}

static void sd_write(FlipStatusStateOptions phase, float pitch_rate_dps, float thrust)
{
    StabilizationDesiredData sd;

    StabilizationDesiredGet(&sd);
    if (phase == FLIPSTATUS_STATE_ROTATE) {
        sd.StabilizationMode.Roll   = STABILIZATIONDESIRED_STABILIZATIONMODE_RATE;
        sd.StabilizationMode.Pitch  = STABILIZATIONDESIRED_STABILIZATIONMODE_RATE;
        sd.StabilizationMode.Yaw    = STABILIZATIONDESIRED_STABILIZATIONMODE_RATE;
        sd.Roll   = 0.0f;
        sd.Pitch  = pitch_rate_dps;
        sd.Yaw    = 0.0f;
    } else {
        sd.StabilizationMode.Roll   = STABILIZATIONDESIRED_STABILIZATIONMODE_ATTITUDE;
        sd.StabilizationMode.Pitch  = STABILIZATIONDESIRED_STABILIZATIONMODE_ATTITUDE;
        sd.StabilizationMode.Yaw    = STABILIZATIONDESIRED_STABILIZATIONMODE_AXISLOCK;
        sd.Roll   = 0.0f;
        sd.Pitch  = (phase == FLIPSTATUS_STATE_CATCH) ? FLIP_CATCH_LEAN : 0.0f;
        sd.Yaw    = 0.0f;
    }
    sd.StabilizationMode.Thrust = STABILIZATIONDESIRED_STABILIZATIONMODE_MANUAL;
    sd.Thrust = thrust;
    StabilizationDesiredSet(&sd);
}

static void FlipTask(__attribute__((unused)) void *parameters)
{
    portTickType lastSysTime = xTaskGetTickCount();
    FlipStatusData st;
    uint32_t phase_ms = 0;
    float angle_deg   = 0.0f;
    uint16_t done_ms  = 0;
    uint32_t last_us  = PIOS_DELAY_GetuS();
    float dt_s        = (float)LOOP_MS / 1000.0f;

    while (1) {
        vTaskDelayUntil(&lastSysTime, LOOP_MS / portTICK_RATE_MS);
        // MEASURED dt, never the nominal loop period: under load the posix
        // scheduler delivers fewer iterations than 100Hz, and an integral
        // that adds gyro*10ms per ITERATION loses exactly the missing
        // fraction - the first flights read 352 deg while the vehicle had
        // done ~500, and every catch inherited a full-speed spin.
        {
            uint32_t now_us = PIOS_DELAY_GetuS();
            dt_s = (float)(now_us - last_us) * 1e-6f;
            last_us = now_us;
            if (dt_s < 0.0f || dt_s > 0.05f) {
                dt_s = (float)LOOP_MS / 1000.0f;
            }
        }
        FlipStatusGet(&st);

        // Loss of the right flight state releases ownership instantly,
        // from any phase.
        bool active = (st.State == FLIPSTATUS_STATE_PUNCH ||
                       st.State == FLIPSTATUS_STATE_ROTATE ||
                       st.State == FLIPSTATUS_STATE_CATCH);
        if (active && !flying_stabilized()) {
            st.Command = FLIPSTATUS_COMMAND_NONE;
            set_state(&st, FLIPSTATUS_STATE_ABORT);
            continue;
        }

        switch (st.State) {
        case FLIPSTATUS_STATE_IDLE:
            if (st.Command == FLIPSTATUS_COMMAND_FLIP) {
                st.Command = FLIPSTATUS_COMMAND_NONE;
                AttitudeStateData att0;
                AttitudeStateGet(&att0);
                if (flying_stabilized() &&
                    fabsf(att0.Roll) < FLIP_LEVEL_DEG && fabsf(att0.Pitch) < FLIP_LEVEL_DEG) {
                    phase_ms     = 0;
                    angle_deg    = 0.0f;
                    st.LastAngle = 0.0f;   // doubles as the beat-entry marker below
                    set_state(&st, FLIPSTATUS_STATE_PUNCH);
                } else {
                    set_state(&st, FLIPSTATUS_STATE_ABORT);
                }
            }
            break;

        case FLIPSTATUS_STATE_PUNCH:
            sd_write(FLIPSTATUS_STATE_PUNCH, 0.0f, FLIP_PUNCH_THRUST);
            phase_ms += (uint32_t)(dt_s * 1000.0f);
            if (phase_ms >= FLIP_PUNCH_MS) {
                phase_ms = 0;
                set_state(&st, FLIPSTATUS_STATE_ROTATE);
            }
            break;

        case FLIPSTATUS_STATE_ROTATE:
        {
            // Rotation angle straight from the gyro integral: no euler
            // wrap gymnastics, no telemetry lag, exact by construction.
            GyroStateData gyro;
            GyroStateGet(&gyro);
            angle_deg += gyro.y * dt_s;

            if (angle_deg < FLIP_EXIT_DEG && phase_ms < FLIP_ROTATE_MS_MAX) {
                float remaining = FLIP_EXIT_DEG - angle_deg;
                float rate = boundf(FLIP_TAPER_GAIN * remaining, 0.0f, FLIP_RATE_MAX);
                float z    = cosf(DEG2RAD(angle_deg));
                // brake segment gets FLIP_THR_UP regardless of tilt:
                // differential torque scales with collective, and the
                // braking needs the torque more than the energy budget
                // needs the thrust discipline
                bool braking = remaining < 130.0f;
                sd_write(FLIPSTATUS_STATE_ROTATE, rate,
                         (z > 0.35f || braking) ? FLIP_THR_UP : FLIP_THR_INV);
                phase_ms += (uint32_t)(dt_s * 1000.0f);
            } else {
                // spin-kill beat: rate zero, still in Rate mode, so the
                // gyro loop scrubs whatever residual the profile left
                // before Attitude is asked to hold anything
                if (st.LastAngle == 0.0f) {
                    st.LastAngle = angle_deg;   // record where the profile ended
                    phase_ms     = 0;           // and start the beat timer
                    FlipStatusSet(&st);
                }
                sd_write(FLIPSTATUS_STATE_ROTATE, 0.0f, 0.70f);
                phase_ms += (uint32_t)(dt_s * 1000.0f);
                if (phase_ms >= FLIP_SPINKILL_MS) {
                    phase_ms = 0;
                    set_state(&st, FLIPSTATUS_STATE_CATCH);
                }
            }
            break;
        }

        case FLIPSTATUS_STATE_CATCH:
            sd_write(FLIPSTATUS_STATE_CATCH, 0.0f, FLIP_CATCH_THRUST);
            phase_ms += (uint32_t)(dt_s * 1000.0f);
            if (phase_ms >= FLIP_CATCH_MS) {
                st.Flips++;
                phase_ms = 0;
                done_ms  = 0;
                set_state(&st, FLIPSTATUS_STATE_DONE);
            }
            break;

        case FLIPSTATUS_STATE_DONE:
        case FLIPSTATUS_STATE_ABORT:
            // ownership already released (handler resumes on these states);
            // linger briefly so the ground side can see the terminal state
            done_ms += (uint16_t)(dt_s * 1000.0f);
            if (done_ms >= 500) {
                done_ms = 0;
                set_state(&st, FLIPSTATUS_STATE_IDLE);
            }
            break;
        }
    }
}

/**
 * @}
 * @}
 */
