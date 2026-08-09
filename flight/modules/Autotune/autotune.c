/**
 ******************************************************************************
 * @addtogroup OpenPilotModules OpenPilot Modules
 * @{
 * @addtogroup AutotuneModule Autotune Module
 * @brief Relay-feedback autotuner: measures each axis' ultimate gain and
 * period by replacing the rate PID with a relay (bang-bang) controller,
 * then derives rate and attitude PI(D) gains Ziegler-Nichols style.
 * @{
 *
 * @file       autotune.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @brief      Autotuning module
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

/*
 * Resurrected 2026-08 from pre-OP-1588 history (the relay flight modes were
 * removed upstream in Nov 2014) and modernized for the 15.02 codebase:
 * - StabilizationDesired.StabilizationMode is a named-field struct now.
 * - Rate/attitude PIDs live in the settings BANKS: results are written to
 *   StabilizationSettingsBank1 (the persistent object - the volatile
 *   StabilizationBank mirror gets stomped on every flight-mode change).
 * - A yaw relay state was added: the original tuned roll/pitch only, and
 *   yaw is precisely the axis the simulated X3 airframe misbehaves on.
 *
 * Operating protocol (the order matters):
 * 1. Configure RelayTuningSettings (Mode=Rate, Behavior=Compute|Save).
 * 2. Arm, take off, and hover ON MANUAL THROTTLE - thrust passes straight
 *    through from ManualControlCommand for the entire tune.
 * 3. Switch the flight mode to Autotune WHILE AIRBORNE with thrust > 0
 *    (AT_INIT refuses to advance on the ground).
 * 4. The module runs relay on roll, then pitch, then yaw (MEASURE_TIME
 *    each) while RelayTuning streams the measured Period/Gain.
 * 5. Land and DISARM while still in Autotune mode - the gains are only
 *    computed and written on the armed->disarmed transition (AT_SET).
 *    Leaving Autotune mode before disarming discards everything.
 */

#include <openpilot.h>

#include "flightstatus.h"
#include "hwsettings.h"
#include "manualcontrolcommand.h"
#include "relaytuning.h"
#include "relaytuningsettings.h"
#include "stabilizationdesired.h"
#include "stabilizationbank.h"
#include "stabilizationsettingsbank1.h"
#include "taskinfo.h"

// Private constants
#define STACK_SIZE_BYTES 1024
#define TASK_PRIORITY    (tskIDLE_PRIORITY + 2)

// Private types
enum AUTOTUNE_STATE { AT_INIT, AT_START, AT_ROLL, AT_PITCH, AT_YAW, AT_FINISHED, AT_SET };

// Private variables
static xTaskHandle taskHandle;
static bool autotuneEnabled;

// Private functions
static void AutotuneTask(void *parameters);
static void update_stabilization_settings();

/**
 * Initialise the module, called on startup
 * \returns 0 on success or -1 if initialisation failed
 */
int32_t AutotuneInitialize(void)
{
    // Create a queue, connect to manual control command and flightstatus
#ifdef MODULE_AUTOTUNE_BUILTIN
    autotuneEnabled = true;
#else
    HwSettingsInitialize();
    uint8_t optionalModules[HWSETTINGS_OPTIONALMODULES_NUMELEM];

    HwSettingsOptionalModulesGet(optionalModules);

    if (optionalModules[HWSETTINGS_OPTIONALMODULES_AUTOTUNE] == HWSETTINGS_OPTIONALMODULES_ENABLED) {
        autotuneEnabled = true;
    } else {
        autotuneEnabled = false;
    }
#endif

    return 0;
}

/**
 * Initialise the module, called on startup
 * \returns 0 on success or -1 if initialisation failed
 */
int32_t AutotuneStart(void)
{
    // Start main task if it is enabled
    if (autotuneEnabled) {
        xTaskCreate(AutotuneTask, "Autotune", STACK_SIZE_BYTES / 4, NULL, TASK_PRIORITY, &taskHandle);

        PIOS_TASK_MONITOR_RegisterTask(TASKINFO_RUNNING_AUTOTUNE, taskHandle);
#ifdef PIOS_WDG_AUTOTUNE
        PIOS_WDG_RegisterFlag(PIOS_WDG_AUTOTUNE);
#endif
    }
    return 0;
}

MODULE_INITCALL(AutotuneInitialize, AutotuneStart);

/**
 * Module thread, should not return.
 */
static void AutotuneTask(__attribute__((unused)) void *parameters)
{
    enum AUTOTUNE_STATE state = AT_INIT;

    portTickType lastUpdateTime = xTaskGetTickCount();

    while (1) {
#ifdef PIOS_WDG_AUTOTUNE
        PIOS_WDG_UpdateFlag(PIOS_WDG_AUTOTUNE);
#endif

        portTickType diffTime;

        const uint32_t PREPARE_TIME = 2000;
        const uint32_t MEAURE_TIME  = 20000;

        FlightStatusData flightStatus;
        FlightStatusGet(&flightStatus);

        // Only allow this module to run when autotuning
        if (flightStatus.FlightMode != FLIGHTSTATUS_FLIGHTMODE_AUTOTUNE) {
            state = AT_INIT;
            vTaskDelay(50);
            continue;
        }

        StabilizationDesiredData stabDesired;
        StabilizationDesiredGet(&stabDesired);

        StabilizationBankData stabBank;
        StabilizationBankGet(&stabBank);

        ManualControlCommandData manualControl;
        ManualControlCommandGet(&manualControl);

        RelayTuningSettingsData relaySettings;
        RelayTuningSettingsGet(&relaySettings);

        bool rate = relaySettings.Mode == RELAYTUNINGSETTINGS_MODE_RATE;

        if (rate) { // rate mode
            stabDesired.StabilizationMode.Roll  = STABILIZATIONDESIRED_STABILIZATIONMODE_RATE;
            stabDesired.StabilizationMode.Pitch = STABILIZATIONDESIRED_STABILIZATIONMODE_RATE;

            stabDesired.Roll  = manualControl.Roll * stabBank.ManualRate.Roll;
            stabDesired.Pitch = manualControl.Pitch * stabBank.ManualRate.Pitch;
        } else {
            stabDesired.StabilizationMode.Roll  = STABILIZATIONDESIRED_STABILIZATIONMODE_ATTITUDE;
            stabDesired.StabilizationMode.Pitch = STABILIZATIONDESIRED_STABILIZATIONMODE_ATTITUDE;

            stabDesired.Roll  = manualControl.Roll * stabBank.RollMax;
            stabDesired.Pitch = manualControl.Pitch * stabBank.PitchMax;
        }

        stabDesired.StabilizationMode.Yaw    = STABILIZATIONDESIRED_STABILIZATIONMODE_RATE;
        stabDesired.Yaw = manualControl.Yaw * stabBank.ManualRate.Yaw;
        stabDesired.StabilizationMode.Thrust = STABILIZATIONDESIRED_STABILIZATIONMODE_MANUAL;
        stabDesired.Thrust = manualControl.Thrust;

        switch (state) {
        case AT_INIT:

            lastUpdateTime = xTaskGetTickCount();

            // Only start when armed and flying
            if (flightStatus.Armed == FLIGHTSTATUS_ARMED_ARMED && stabDesired.Thrust > 0) {
                state = AT_START;
            }
            break;

        case AT_START:

            diffTime = xTaskGetTickCount() - lastUpdateTime;

            // Spend the first block of time in normal rate mode to get airborne
            if (diffTime > PREPARE_TIME) {
                state = AT_ROLL;
                lastUpdateTime = xTaskGetTickCount();
            }
            break;

        case AT_ROLL:

            diffTime = xTaskGetTickCount() - lastUpdateTime;

            // Run relay mode on the roll axis for the measurement time
            stabDesired.StabilizationMode.Roll = rate ? STABILIZATIONDESIRED_STABILIZATIONMODE_RELAYRATE :
                                                 STABILIZATIONDESIRED_STABILIZATIONMODE_RELAYATTITUDE;
            if (diffTime > MEAURE_TIME) { // Move on to next state
                state = AT_PITCH;
                lastUpdateTime = xTaskGetTickCount();
            }
            break;

        case AT_PITCH:

            diffTime = xTaskGetTickCount() - lastUpdateTime;

            // Run relay mode on the pitch axis for the measurement time
            stabDesired.StabilizationMode.Pitch = rate ? STABILIZATIONDESIRED_STABILIZATIONMODE_RELAYRATE :
                                                  STABILIZATIONDESIRED_STABILIZATIONMODE_RELAYATTITUDE;
            if (diffTime > MEAURE_TIME) { // Move on to next state
                state = AT_YAW;
                lastUpdateTime = xTaskGetTickCount();
            }
            break;

        case AT_YAW:

            diffTime = xTaskGetTickCount() - lastUpdateTime;

            // Yaw relay always runs in RATE (relay toggles the yaw rate
            // setpoint around zero while hovering, sticks centered). The
            // original module never tuned yaw at all - and yaw is the axis
            // the simulated X3 actually oscillates on.
            stabDesired.StabilizationMode.Yaw = STABILIZATIONDESIRED_STABILIZATIONMODE_RELAYRATE;
            if (diffTime > MEAURE_TIME) { // Move on to next state
                state = AT_FINISHED;
                lastUpdateTime = xTaskGetTickCount();
            }
            break;

        case AT_FINISHED:

            // Wait until disarmed and landed before updating the settings
            if (flightStatus.Armed == FLIGHTSTATUS_ARMED_DISARMED && stabDesired.Thrust <= 0) {
                state = AT_SET;
            }

            break;

        case AT_SET:
            update_stabilization_settings();
            state = AT_INIT;
            break;

        default:
            break;
        }

        StabilizationDesiredSet(&stabDesired);

        vTaskDelay(10);
    }
}

/**
 * Called after measuring roll, pitch and yaw to update the
 * stabilization settings
 *
 * takes in @ref RelayTuning and outputs @ref StabilizationSettingsBank1
 */
static void update_stabilization_settings()
{
    RelayTuningData relayTuning;

    RelayTuningGet(&relayTuning);

    RelayTuningSettingsData relaySettings;
    RelayTuningSettingsGet(&relaySettings);

    // 15.02 moved the rate/attitude PIDs into the settings BANKS; write the
    // persistent Bank1 (the volatile StabilizationBank mirror gets stomped
    // by SettingsBankUpdatedCb on every mode change).
    StabilizationSettingsBank1Data bank;
    StabilizationSettingsBank1Get(&bank);

    // Eventually get these settings from RelayTuningSettings
    const float gain_ratio_r = 1.0f / 3.0f;
    const float zero_ratio_r = 1.0f / 3.0f;
    const float gain_ratio_p = 1.0f / 5.0f;
    const float zero_ratio_p = 1.0f / 5.0f;

    // Roll, pitch AND yaw (the original module stopped at pitch)
    for (unsigned int i = 0; i < 3; i++) {
        float period = RelayTuningPeriodToArray(relayTuning.Period)[i];
        float gain   = RelayTuningGainToArray(relayTuning.Gain)[i];
        if (period < 1.0f || gain < 1e-6f) {
            continue; // axis was never measured - leave its gains alone
        }
        float wu  = 1000.0f * 2 * M_PI / period; // ultimate freq = output osc freq (rad/s)

        float wc  = wu * gain_ratio_r;  // target openloop crossover frequency (rad/s)
        float zc  = wc * zero_ratio_r;  // controller zero location (rad/s)
        float kpu = 4.0f / M_PI / gain; // ultimate gain, i.e. the proportional gain for instablity
        float kp  = kpu * gain_ratio_r; // proportional gain
        float ki  = zc * kp;            // integral gain

        // Now calculate gains for the next loop out knowing it is the integral of
        // the inner loop -- the plant is position/velocity = scale*1/s
        float wc2 = wc * gain_ratio_p;        // crossover of the attitude loop
        float kp2 = wc2;                      // kp of attitude
        float ki2 = wc2 * zero_ratio_p * kp2; // ki of attitude

        switch (i) {
        case 0: // Roll
            bank.RollRatePID.Kp = kp;
            bank.RollRatePID.Ki = ki;
            bank.RollPI.Kp = kp2;
            bank.RollPI.Ki = ki2;
            break;
        case 1: // Pitch
            bank.PitchRatePID.Kp = kp;
            bank.PitchRatePID.Ki = ki;
            bank.PitchPI.Kp = kp2;
            bank.PitchPI.Ki = ki2;
            break;
        case 2: // Yaw
            bank.YawRatePID.Kp = kp;
            bank.YawRatePID.Ki = ki;
            bank.YawPI.Kp = kp2;
            bank.YawPI.Ki = ki2;
            break;
        default:
            break;
        }
    }
    switch (relaySettings.Behavior) {
    case RELAYTUNINGSETTINGS_BEHAVIOR_MEASURE:
        // Just measure, don't update the stab settings
        break;
    case RELAYTUNINGSETTINGS_BEHAVIOR_COMPUTE:
        StabilizationSettingsBank1Set(&bank);
        break;
    case RELAYTUNINGSETTINGS_BEHAVIOR_SAVE:
        StabilizationSettingsBank1Set(&bank);
        UAVObjSave(StabilizationSettingsBank1Handle(), 0);
        break;
    }
}

/**
 * @}
 * @}
 */
