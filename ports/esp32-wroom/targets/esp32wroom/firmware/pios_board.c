/**
 ******************************************************************************
 *
 * @file       pios_board.c
 * @author     NinjaPilot, 2026
 * @brief      Board initialisation for the ESP32-WROOM-32E target.
 *
 * Call order mirrors the CopterControl board file, minus everything that has
 * no ESP32 analogue (IAP, internal-flash settings FS, USB, RTC, timer clock
 * setup -- IDF owns all of those or they are not implemented yet).
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

#include "inc/openpilot.h"
#include <pios_board_info.h>
#include <uavobjectsinit.h>
#include <hwsettings.h>
#include <manualcontrolsettings.h>
#include <mixersettings.h>
#include <actuatorsettings.h>
#include <firmwareiapobj.h>
#include "fw_version_info.h"
#include "esp_timer.h"
#include <flightstatus.h>
#include <systemalarms.h>
#include "driver/gpio.h"
#include "esp_system.h"
#include <taskinfo.h>
#include <pios_com_priv.h>
#include <pios_rcvr_priv.h>
#include <pios_gcsrcvr_priv.h>
#include <gcsreceiver.h>
#include <pios_flashfs.h>
#include <pios_board_info.h>
#include <pios_debuglog.h>

#include "../board_hw_defs.c"

/* Externally visible COM handles, referenced by the Telemetry module.
 * Declared in pios_board.h as PIOS_COM_TELEM_RF. */
uint32_t pios_com_telem_rf_id;
uint32_t pios_com_aux_id;

/* Receiver group map, indexed by MANUALCONTROLSETTINGS_CHANNELGROUPS_*. */
uint32_t pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_NONE];

/* Sensor bus handles. */
static uint32_t pios_spi_sensors_id;

/* ---------------------------------------------------------------------- *
 * Placeholders for the settings filesystem, which this target does not have
 * yet (see pios_config.h).
 *
 * systemmod.c reads both ids and only calls PIOS_FLASHFS_GetStats() when one
 * is non-zero, so leaving them at 0 disables that reporting cleanly. The stub
 * exists purely to satisfy the linker; if it is ever actually reached, that
 * means an id got set without a real backend behind it, so it says so rather
 * than returning plausible zeros.
 * ---------------------------------------------------------------------- */
/* pios/common/pios_board_info.c is not built for this target: it places the
 * blob in a .boardinfo section that only the PiOS bootloader's linker script
 * defines, and it derives fw_base/fw_size from BL_/FW_BANK values that have no
 * meaning here (ESP-IDF's bootloader and partition table own the flash map).
 * Define it directly instead.
 *
 * board_rev MUST stay 0x02 -- see the comment in board-info.mk. */
const struct pios_board_info pios_board_info_blob = {
    .magic      = PIOS_BOARD_INFO_BLOB_MAGIC,
    .board_type = 0x12,
    .board_rev  = 0x02,
    .bl_rev     = 0x00,   /* no PiOS bootloader on this target */
    .hw_type    = 0x00,
    .fw_base    = 0x00010000,  /* factory app partition, see partitions.csv */
    .fw_size    = 1024 * 1024,
    .desc_base  = 0,
    .desc_size  = 0,
    .ee_base    = 0,
    .ee_size    = 0,
};

/* uavobjectmanager.c calls this unconditionally. The real implementation
 * (pios/common/pios_debuglog.c) logs to PIOS_FLASHFS, which this target does
 * not have yet -- so the on-board DebugLog recorder is NOT available here.
 * Worth knowing, because it is the flight recorder the rest of this project
 * leans on. */
void PIOS_DEBUGLOG_UAVObject(__attribute__((unused)) uint32_t objid,
                             __attribute__((unused)) uint16_t instid,
                             __attribute__((unused)) size_t size,
                             __attribute__((unused)) uint8_t *data)
{}

uintptr_t pios_uavo_settings_fs_id;
uintptr_t pios_user_fs_id;

/**
 * Bring up a COM device on one of the ESP32 UARTs.
 *
 * The COM layer owns its own ring buffers; the IDF UART driver has separate
 * ones underneath. That double-buffering is a little wasteful but it keeps
 * pios_usart.c able to hand up whole blocks instead of single bytes.
 */
static void board_com_init(uint32_t *com_id,
                           const struct pios_esp32_usart_cfg *usart_cfg,
                           uint16_t rx_len, uint16_t tx_len)
{
    uint32_t usart_id;

    if (PIOS_ESP32_USART_Init(&usart_id, usart_cfg) != 0) {
        PIOS_Assert(0);
    }

    uint8_t *rx_buffer = (uint8_t *)pios_malloc(rx_len);
    uint8_t *tx_buffer = (uint8_t *)pios_malloc(tx_len);

    PIOS_Assert(rx_buffer);
    PIOS_Assert(tx_buffer);

    if (PIOS_COM_Init(com_id, &pios_esp32_usart_com_driver, usart_id,
                      rx_buffer, rx_len, tx_buffer, tx_len) != 0) {
        PIOS_Assert(0);
    }
}

/**
 * PIOS_Board_Init()
 *
 * Runs from the init task, with the scheduler already going (ESP-IDF starts
 * it before app_main).
 */

/* ---------------------------------------------------------------------- *
 * Default airframe: Quad X
 *
 * STALE-COMMENT FIX (2026-09-01): this target HAS a settings filesystem
 * now -- pios_flashfs_nvs.c, keyed by object id + instance, size-checked
 * on load, committed on save; UAVObjRegister() loads every settings
 * object from it at boot. These compiled-in Quad X defaults apply ONLY
 * to an unprovisioned board (first boot after flash-erase), so a fresh
 * board is flyable; once anything has been saved, stored settings win
 * (see the IsProvisioned() gate below).
 * ---------------------------------------------------------------------- */
static void board_apply_default_airframe(void)
{
    MixerSettingsData mixer;
    ActuatorSettingsData act;

    /* Stored settings win. These defaults exist so a freshly flashed board is
     * usable, not to overwrite what the operator saved -- without this check
     * every reboot would quietly undo their calibration. */
    if (PIOS_ESP32_FLASHFS_IsProvisioned()) {
        return;
    }

    MixerSettingsGet(&mixer);

    /* The stock ThrottleCurve1 default is all zeros, so even a perfectly
     * correct mixer commands nothing at any stick position. Linear 0..100%. */
    mixer.ThrottleCurve1[0] = 0.0f;
    mixer.ThrottleCurve1[1] = 0.25f;
    mixer.ThrottleCurve1[2] = 0.5f;
    mixer.ThrottleCurve1[3] = 0.75f;
    mixer.ThrottleCurve1[4] = 1.0f;

    /*
     * Quad X, matching the table the GCS itself writes for this airframe
     * (xMixer in configmultirotorwidget.cpp), scaled by 127. Yaw is negative
     * for a CW prop and positive for CCW, so the diagonals pair up:
     *
     *   M1  front-left   GPIO15   pitch +1  roll +1  yaw -1   CW
     *   M2  front-right  GPIO33   pitch +1  roll -1  yaw +1   CCW
     *   M3  rear-right   GPIO27   pitch -1  roll -1  yaw -1   CW
     *   M4  rear-left    GPIO12   pitch -1  roll +1  yaw +1   CCW
     *
     * "Front" is whichever way the IMU's +X points, NOT the ESP32 board --
     * the sensor is on flying leads, so fix its orientation to the frame
     * before trusting any of this.
     */
    mixer.Mixer1Type = MIXERSETTINGS_MIXER1TYPE_MOTOR;
    mixer.Mixer1Vector.ThrottleCurve1 = 127;
    mixer.Mixer1Vector.ThrottleCurve2 = 0;
    mixer.Mixer1Vector.Roll  =  127;
    mixer.Mixer1Vector.Pitch =  127;
    mixer.Mixer1Vector.Yaw   = -127;

    mixer.Mixer2Type = MIXERSETTINGS_MIXER2TYPE_MOTOR;
    mixer.Mixer2Vector.ThrottleCurve1 = 127;
    mixer.Mixer2Vector.ThrottleCurve2 = 0;
    mixer.Mixer2Vector.Roll  = -127;
    mixer.Mixer2Vector.Pitch =  127;
    mixer.Mixer2Vector.Yaw   =  127;

    mixer.Mixer3Type = MIXERSETTINGS_MIXER3TYPE_MOTOR;
    mixer.Mixer3Vector.ThrottleCurve1 = 127;
    mixer.Mixer3Vector.ThrottleCurve2 = 0;
    mixer.Mixer3Vector.Roll  = -127;
    mixer.Mixer3Vector.Pitch = -127;
    mixer.Mixer3Vector.Yaw   = -127;

    mixer.Mixer4Type = MIXERSETTINGS_MIXER4TYPE_MOTOR;
    mixer.Mixer4Vector.ThrottleCurve1 = 127;
    mixer.Mixer4Vector.ThrottleCurve2 = 0;
    mixer.Mixer4Vector.Roll  =  127;
    mixer.Mixer4Vector.Pitch = -127;
    mixer.Mixer4Vector.Yaw   =  127;

    MixerSettingsSet(&mixer);

    ActuatorSettingsGet(&act);
    for (uint8_t i = 0; i < 4; i++) {
        act.ChannelType[i]    = ACTUATORSETTINGS_CHANNELTYPE_PWM;
        act.ChannelAddr[i]    = i;
        /* Min == Neutral means the motors sit at their stop when armed.
         * MotorsSpinWhileArmed stays FALSE. Raise Neutral only after the
         * ESCs have been calibrated against these endpoints. */
        act.ChannelMin[i]     = 1000;
        act.ChannelNeutral[i] = 1000;
        act.ChannelMax[i]     = 2000;
    }
    /*
     * Point the sticks at the DSM satellite. Standard Spektrum channel order:
     * 1 throttle, 2 aileron, 3 elevator, 4 rudder, 5 gear. Endpoints are left
     * at their defaults -- those are per-transmitter and have to be calibrated
     * from the GCS, which will not survive a reboot on this target either.
     *
     * Change these to ..._PPM to fly off the PPM input on GPIO21 instead;
     * both receivers are built and running, and this is the only thing that
     * decides which one ManualControl actually reads.
     */
    {
        ManualControlSettingsData mc;

        ManualControlSettingsGet(&mc);
        mc.ChannelGroups.Throttle   = MANUALCONTROLSETTINGS_CHANNELGROUPS_DSMMAINPORT;
        mc.ChannelGroups.Roll       = MANUALCONTROLSETTINGS_CHANNELGROUPS_DSMMAINPORT;
        mc.ChannelGroups.Pitch      = MANUALCONTROLSETTINGS_CHANNELGROUPS_DSMMAINPORT;
        mc.ChannelGroups.Yaw        = MANUALCONTROLSETTINGS_CHANNELGROUPS_DSMMAINPORT;
        mc.ChannelGroups.FlightMode = MANUALCONTROLSETTINGS_CHANNELGROUPS_DSMMAINPORT;
        mc.ChannelNumber.Throttle   = 1;
        mc.ChannelNumber.Roll       = 2;
        mc.ChannelNumber.Pitch      = 3;
        mc.ChannelNumber.Yaw        = 4;
        mc.ChannelNumber.FlightMode = 5;
        ManualControlSettingsSet(&mc);
        UAVObjSave(ManualControlSettingsHandle(), 0);
    }

    /* 50Hz is the rate every analogue ESC understands. The MCPWM driver
     * applies one rate to all channels (see PIOS_Servo_SetHz), so this is
     * effectively a single global setting -- raise it once you know what the
     * ESCs accept. */
    act.BankUpdateFreq[0] = 50;
    ActuatorSettingsSet(&act);

    UAVObjSave(MixerSettingsHandle(), 0);
    UAVObjSave(ActuatorSettingsHandle(), 0);

    /* Everything above is now on flash; do not do this again. */
    PIOS_ESP32_FLASHFS_MarkProvisioned();
}


/* ---------------------------------------------------------------------- *
 * Status LED and the BOOT button
 *
 * The stock Notify module is built for WS2811 RGB strips -- it wants
 * lednotification, flightbatterystate, optypes and HwSettings' WS2811 output
 * config -- which is a lot of machinery for a board whose only indicator is
 * one blue LED on GPIO13. This gives the same information in the form the
 * hardware actually has: blink rate says what the aircraft is doing.
 *
 *     slow heartbeat   disarmed
 *     10Hz strobe      ARMED
 *     flutter          BOOT button held, settings erase pending
 *
 * Deliberately only two flight states. It used to blink alarm severity as
 * well, which made it unreadable -- the alarm state changed faster than a
 * pattern can be recognised and it just looked like random clusters of
 * pulses. Armed vs not armed is the one thing that has to be legible across
 * a field at a glance, so it gets the indicator to itself; alarms belong in
 * the GCS where there is room to name them.
 *
 * The BOOT button lives here too because it is the same kind of thing --
 * board-level UX -- and one task doing both costs less than two.
 * ---------------------------------------------------------------------- */
#define BOARD_BTN_PIN       GPIO_NUM_0
#define BOARD_BTN_HOLD_MS   3000
#define BOARD_UX_TICK_MS    25
#define BOARD_UX_STACK      1024   /* words; see the unit note in pios_esp32.h */
/*
 * BELOW everything that flies the aircraft. Deliberately.
 *
 * This was briefly raised to tskIDLE_PRIORITY + 5 to smooth out a choppy
 * strobe, which was a mistake worth recording: the callback priority map in
 * pios_callbackscheduler.h puts FLIGHTCONTROL at +3 and STABILIZATIONOUTERLOOP
 * at +4, and the Actuator task is +4 as well. A status LED at +5 could
 * therefore preempt the outer loop and the code that drives the motors --
 * trading a flight-control deadline for a prettier blink is not a trade
 * anyone should make.
 *
 * At +1 a busy board can make the blink slightly irregular. That is the
 * correct thing to accept: the LED reports state, it is not state.
 */
#define BOARD_UX_PRIORITY   (tskIDLE_PRIORITY + 1)

static void board_iap_restart(__attribute__((unused)) void *arg)
{
    esp_restart();
}

static void board_iap_updated_cb(UAVObjEvent *ev)
{
    static uint16_t iap_last;

    if (!ev || ev->event != EV_UNPACKED) {
        return;
    }
    FirmwareIAPObjData iap;
    FirmwareIAPObjGet(&iap);
    if (iap.Command == 1122) {
        iap_last = 1122;
    } else if (iap.Command == 2233 && iap_last == 1122) {
        iap_last = 2233;
    } else if (iap.Command == 3344 && iap_last == 2233) {
        iap_last = 0;
        const esp_timer_create_args_t targs = {
            .callback = board_iap_restart,
            .name     = "iap_restart",
        };
        esp_timer_handle_t t;
        if (esp_timer_create(&targs, &t) == ESP_OK) {
            esp_timer_start_once(t, 800 * 1000);
        }
    } else {
        iap_last = 0;
    }
}

static void board_ux_task(__attribute__((unused)) void *arg)
{
    uint32_t held_ms = 0;
    uint32_t phase   = 0;
    TickType_t wake = xTaskGetTickCount();

    for (;;) {
        /* delayUntil, not delay: plain vTaskDelay waits AT LEAST the period,
         * so every preemption permanently shifted the blink and the strobe
         * wandered. This keeps a fixed cadence. */
        vTaskDelayUntil(&wake, pdMS_TO_TICKS(BOARD_UX_TICK_MS));
        phase += BOARD_UX_TICK_MS;

        /*
         * BOOT is GPIO0, active low. Note this deliberately does NOT try to
         * detect the button being held at power-up: GPIO0 low at the reset
         * instant IS the serial-download strap, so a board held that way
         * never reaches this code at all. Holding it after boot is the only
         * thing firmware can see.
         */
        if (gpio_get_level(BOARD_BTN_PIN) == 0) {
            held_ms += BOARD_UX_TICK_MS;
            if (held_ms >= BOARD_BTN_HOLD_MS) {
                /* Wipe settings and come back on compiled-in defaults. The
                 * marker lives in the same namespace, so Format() clears it
                 * too and the next boot re-provisions. */
                PIOS_LED_On(PIOS_LED_HEARTBEAT);
                (void)PIOS_FLASHFS_Format(pios_uavo_settings_fs_id);
                vTaskDelay(pdMS_TO_TICKS(300));
                esp_restart();
            }
            /* Flutter while held, so it is obvious something is happening
             * before it happens. */
            PIOS_LED_Toggle(PIOS_LED_HEARTBEAT);
            continue;
        }
        held_ms = 0;

        uint16_t on_ms, off_ms;
        FlightStatusArmedOptions armed = FLIGHTSTATUS_ARMED_DISARMED;

        FlightStatusArmedGet(&armed);

        /*
         * Two states, and only two.
         *
         * This used to also blink alarm severity, which made it useless: the
         * alarm state changed faster than a pattern could be recognised and
         * the LED just looked like random clusters of pulses. Armed vs not
         * armed is the one thing that must be readable across a field at a
         * glance, so it gets the indicator to itself. Alarms are visible in
         * the GCS, where there is room to say which one.
         */
        if (armed == FLIGHTSTATUS_ARMED_ARMED) {
            on_ms = 50;  off_ms = 50;    /* 10Hz strobe -- ARMED */
        } else {
            on_ms = 100; off_ms = 900;   /* slow heartbeat -- disarmed */
        }

        if (phase >= (uint32_t)(on_ms + off_ms)) {
            phase = 0;
        }
        if (phase < on_ms) {
            PIOS_LED_On(PIOS_LED_HEARTBEAT);
        } else {
            PIOS_LED_Off(PIOS_LED_HEARTBEAT);
        }
    }
}

static void board_ux_start(void)
{
    gpio_config_t io = {
        .intr_type    = GPIO_INTR_DISABLE,
        .mode         = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ULL << BOARD_BTN_PIN,
        .pull_up_en   = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
    };

    gpio_config(&io);
    xTaskCreate(board_ux_task, "BoardUX", BOARD_UX_STACK, NULL,
                BOARD_UX_PRIORITY, NULL);
}


/* ---------------------------------------------------------------------- *
 * PWM output self-test
 *
 * The servo driver had never emitted a pulse on hardware -- everything up to
 * here proved the flight code decides the right numbers, and nothing proved
 * those numbers reach the pins. This drives the outputs directly so that gap
 * is closed on a bench rather than on a first hover.
 *
 * It runs inside PIOS_Board_Init, BEFORE any module starts. That matters: the
 * Actuator module writes the servos every cycle once it is running, so a test
 * scheduled after startup would simply be overwritten.
 *
 * Each motor is swept ALONE first, in order, then all four together. The solo
 * sweeps are the useful part -- they tell you which physical motor each pin
 * actually drives, which is the mistake that flips an airframe on takeoff and
 * is invisible from the bench any other way.
 *
 * !! PROPS OFF !!  With a battery connected this spins motors.
 * Compile-time gated and OFF by default, so it cannot ship enabled.
 * ---------------------------------------------------------------------- */
#ifdef BOARD_PWM_SELFTEST

#ifndef BOARD_PWM_SELFTEST_PEAK_US
#define BOARD_PWM_SELFTEST_PEAK_US 1500   /* mid stick */
#endif
#define BOARD_PWM_IDLE_US          1000
#define BOARD_PWM_STEP_US          10
#define BOARD_PWM_STEP_MS          8

static void board_pwm_write_all(uint16_t us)
{
    for (uint8_t ch = 0; ch < 4; ch++) {
        PIOS_Servo_Set(ch, us);
    }
    PIOS_Servo_Update();
}

/* Sweep one channel idle -> peak -> idle, holding the rest at idle.
 * Pass 0xFF to sweep all four together. */
static void board_pwm_sweep(uint8_t only_ch)
{
    for (int dir = 0; dir < 2; dir++) {
        for (uint16_t us = BOARD_PWM_IDLE_US; us <= BOARD_PWM_SELFTEST_PEAK_US;
             us += BOARD_PWM_STEP_US) {
            uint16_t v = (dir == 0) ? us
                         : (BOARD_PWM_SELFTEST_PEAK_US -
                            (us - BOARD_PWM_IDLE_US) + BOARD_PWM_IDLE_US);

            for (uint8_t ch = 0; ch < 4; ch++) {
                PIOS_Servo_Set(ch, (only_ch == 0xFF || ch == only_ch)
                                   ? v : BOARD_PWM_IDLE_US);
            }
            PIOS_Servo_Update();
            PIOS_DELAY_WaitmS(BOARD_PWM_STEP_MS);
        }
    }
    board_pwm_write_all(BOARD_PWM_IDLE_US);
}

static void board_pwm_selftest(void)
{
    /* Hold idle first. An ESC wants to see a valid minimum for a moment
     * before anything else, and this is also the arming tone if one is
     * powered. */
    board_pwm_write_all(BOARD_PWM_IDLE_US);
    PIOS_DELAY_WaitmS(3000);

    for (uint8_t ch = 0; ch < 4; ch++) {
        PIOS_LED_Toggle(PIOS_LED_HEARTBEAT);
        board_pwm_sweep(ch);
        PIOS_DELAY_WaitmS(700);      /* gap so the solos are countable */
    }

    PIOS_LED_On(PIOS_LED_HEARTBEAT);
    board_pwm_sweep(0xFF);           /* all four together */
    board_pwm_write_all(BOARD_PWM_IDLE_US);
}
#endif /* BOARD_PWM_SELFTEST */


void PIOS_Board_Init(void)
{
    PIOS_DELAY_Init();

    PIOS_LED_Init(&pios_led_cfg);
    PIOS_LED_On(PIOS_LED_HEARTBEAT);

    /* The task monitor owns a recursive mutex that the System module's
     * updateStats() takes once a second via
     * PIOS_TASK_MONITOR_GetIdlePercentage(). Skipping this init does not
     * fail loudly at startup -- it asserts inside FreeRTOS a second later,
     * once the System task first runs. */
    if (PIOS_TASK_MONITOR_Initialize(TASKINFO_RUNNING_NUMELEM)) {
        PIOS_Assert(0);
    }

    /* Object plumbing has to exist before anything tries to publish. */
    PIOS_CALLBACKSCHEDULER_Initialize();
    EventDispatcherInitialize();
    /* Drag the real UAVObjSave/UAVObjLoad into the link -- see the comment on
     * this symbol in uavobjectpersistence.c. Without it the weak stubs win,
     * every save returns success, and nothing is ever stored. */
    {
        extern const int uavobject_persistence_linked;
        static const int *const keep_persistence __attribute__((used)) =
            &uavobject_persistence_linked;
        (void)keep_persistence;
    }

    /* Settings storage first: UAVObjRegister() calls UAVObjLoad() for every
     * object as it registers, so the filesystem has to be open by then or
     * every setting silently comes up on its compiled-in default. */
    if (PIOS_ESP32_FLASHFS_Init(&pios_uavo_settings_fs_id) != 0) {
        /* Not fatal -- the board still flies, it just forgets. Say so once,
         * because "my tuning keeps reverting" is otherwise a long afternoon. */
        printf("[BOARD] settings storage unavailable, settings will not persist\n");
        pios_uavo_settings_fs_id = 0;
    }

    UAVObjInitialize();
    UAVObjectsInitializeAll();

    /* Compiled-in Quad X mixer and output endpoints -- see the comment on the
     * function for why this is not left to the GCS. */
    board_apply_default_airframe();

    /* The GCS identifies the board through FirmwareIAPObj (board model =
     * type<<8 | revision -- the Setup Wizard switches on it). The stock
     * FirmwareIAP module is bootloader plumbing this target has no use
     * for, so populate the identity fields directly and leave the module
     * out. */
    {
        FirmwareIAPObjInitialize();
        FirmwareIAPObjData iap;
        FirmwareIAPObjGet(&iap);
        iap.BoardType     = pios_board_info_blob.board_type;
        iap.BoardRevision = pios_board_info_blob.board_rev;

        /* The 100-byte "OpFw" description blob the GCS parses
         * (devicedescriptorstruct.h). The uavo-set sha1 at offset 60 is
         * what the GCS's version-mismatch warning compares; the rest
         * feeds its version display. Generated into fw_version_info.h at
         * configure time from the same script and XML tree the GCS
         * builds its own hash from. */
        memset(iap.Description, 0, sizeof(iap.Description));
        memcpy(&iap.Description[0], "OpFw", 4);
        uint32_t v = FW_VERSION_HASH32;
        memcpy(&iap.Description[4], &v, 4);
        v = FW_VERSION_UNIXTIME;
        memcpy(&iap.Description[8], &v, 4);
        iap.Description[12] = pios_board_info_blob.board_type;
        iap.Description[13] = pios_board_info_blob.board_rev;
        strncpy((char *)&iap.Description[14], FW_VERSION_FWTAG, 25);
        memcpy(&iap.Description[60], fw_version_uavo_sha1, 20);
        FirmwareIAPObjSet(&iap);

        /* Honor the GCS's IAP reset sequence (Command 1122 -> 2233 ->
         * 3344). On STM32 that jumps to the serial bootloader; here it
         * is a plain restart -- which is all the GCS's reboot flow needs
         * once its ESP32 branch stops expecting a DFU device. The
         * restart is deferred through a one-shot timer so the write's
         * ACK and the telemetry buffers get out first. */
        UAVObjConnectCallback(FirmwareIAPObjHandle(), board_iap_updated_cb,
                              EV_UNPACKED);
    }

    /* No settings filesystem on this target yet (see pios_config.h), so
     * HwSettings comes up on defaults every boot. Say so once, plainly --
     * a board that silently forgets its configuration on every power cycle
     * is a bad surprise to discover mid-tuning. */
    HwSettingsInitialize();

    PIOS_WDG_Init();

    AlarmsInitialize();

    /* --- Telemetry / console ------------------------------------------ */
    board_com_init(&pios_com_telem_rf_id, &pios_usart_telem_cfg,
                   PIOS_COM_TELEM_RF_RX_BUF_LEN, PIOS_COM_TELEM_RF_TX_BUF_LEN);

#ifdef PIOS_INCLUDE_WIFI
    /* WiFi telemetry, bench feature: only runs when credentials are stored
     * (tools/wifi_setup.py). On a successful join, telemetry moves to the
     * TCP socket and UART0 goes quiet -- one telemetry port at a time. No
     * credentials costs one NVS lookup and nothing else. Erase credentials
     * before flying; the WiFi stack's own tasks have not been characterized
     * against the control loop. */
    if (PIOS_ESP32_WIFI_Init() == 0) {
        static uint8_t wifi_rx_buf[PIOS_COM_TELEM_RF_RX_BUF_LEN];
        static uint8_t wifi_tx_buf[PIOS_COM_TELEM_RF_TX_BUF_LEN];
        uint32_t wifi_com_id;

        if (PIOS_COM_Init(&wifi_com_id, &pios_esp32_wifi_com_driver, 1,
                          wifi_rx_buf, sizeof(wifi_rx_buf),
                          wifi_tx_buf, sizeof(wifi_tx_buf)) == 0) {
            pios_com_telem_rf_id = wifi_com_id;
            printf("[BOARD] telemetry on WiFi TCP\n");
        }
    }
#endif

    /* --- Is anything actually on the sensor bus? -----------------------
     *
     * Before SPI claims MISO, drive the pin's internal pull-down and then its
     * pull-up and read it back. A connected, powered device holds the line;
     * an unconnected one follows whichever pull is enabled. This separates
     * "wired wrong" from "not powered" without a meter, and a WHO_AM_I of
     * 0xFF alone cannot tell those apart. */
    {
        gpio_config_t io = {
            .intr_type    = GPIO_INTR_DISABLE,
            .mode         = GPIO_MODE_INPUT,
            .pin_bit_mask = 1ULL << GPIO_NUM_19,
            .pull_down_en = GPIO_PULLDOWN_ENABLE,
            .pull_up_en   = GPIO_PULLUP_DISABLE,
        };
        gpio_config(&io);
        vTaskDelay(pdMS_TO_TICKS(5));
        int with_pd = gpio_get_level(GPIO_NUM_19);

        io.pull_down_en = GPIO_PULLDOWN_DISABLE;
        io.pull_up_en   = GPIO_PULLUP_ENABLE;
        gpio_config(&io);
        vTaskDelay(pdMS_TO_TICKS(5));
        int with_pu = gpio_get_level(GPIO_NUM_19);

        const char *verdict =
            (with_pd == 1) ? "held HIGH by something -- device present and powered" :
            (with_pu == 0) ? "held LOW by something -- device present, but check CS" :
                             "FLOATING -- nothing connected or the sensor has no power";
        printf("[BOARD] MISO(GPIO19) pulldown=%d pullup=%d : %s\n",
               with_pd, with_pu, verdict);
    }

    /* --- Sensor bus --------------------------------------------------- */
    if (PIOS_ESP32_SPI_Init(&pios_spi_sensors_id, &pios_spi_sensors_cfg) != 0) {
        PIOS_Assert(0);
    }


#ifdef PIOS_INCLUDE_ICM20602
    /* Slave 0 on the sensor bus.
     *
     * Two things worth knowing here:
     *
     * 1. PIOS_ICM20602_Init() returns 0 as long as its allocation succeeds.
     *    PIOS_ICM20602_Config() calls PIOS_ICM20602_Test() but ignores the
     *    result, so a missing or unrecognised part does NOT show up in the
     *    return value. WHO_AM_I is read separately below to report it.
     *
     * 2. PIOS_ICM20602_Register() and the data-ready task are started
     *    REGARDLESS of whether a sensor answered. That looks wrong, and it
     *    is what an earlier revision "fixed" -- but skipping the registration
     *    hangs module init: the sensor consumers wait on a PIOS_SENSORS
     *    instance that never appears, and the board never reaches telemetry.
     *    A board that boots, reports the fault over UAVTalk and refuses to
     *    arm is far more useful than one that silently wedges, so register
     *    unconditionally and let the alarm carry the bad news.
     */
    PIOS_ICM20602_Init(pios_spi_sensors_id, 0, &pios_icm20602_cfg);

    /* The first SPI read after a soft restart can return garbage while
     * the sensor is perfectly healthy -- a single misread here latched a
     * BootFault Critical (arming blocked) on a board whose gyro then
     * streamed flawlessly. Ask a few times before believing a bad answer. */
    int32_t imu_id = PIOS_ICM20602_ReadID();
    for (int tries = 0; tries < 4 && imu_id != 0x68 && imu_id != 0x70 && imu_id != 0x12; tries++) {
        PIOS_DELAY_WaitmS(10);
        imu_id = PIOS_ICM20602_ReadID();
    }

    if (imu_id != 0x68 && imu_id != 0x70 && imu_id != 0x12) {
        printf("[BOARD] no usable IMU on SPI3 (SCLK=5 MOSI=18 MISO=19 CS=14): WHO_AM_I=0x%02X "
               "(expect 0x68 MPU6000/6050, 0x70 MPU6500, 0x12 ICM-20602; "
               "0x00/0xFF means nothing is answering)\n", (unsigned)imu_id);
        AlarmsSet(SYSTEMALARMS_ALARM_BOOTFAULT, SYSTEMALARMS_ALARM_CRITICAL);
    } else {
        printf("[BOARD] IMU found, WHO_AM_I=0x%02X\n", (unsigned)imu_id);
    }

    PIOS_ICM20602_Register();

    /* The data-ready path runs in a task, not an ISR -- see
     * pios/esp32/pios_exti.c for the two reasons why. */
    if (PIOS_ESP32_EXTI_Init(&pios_exti_icm20602_cfg) != 0) {
        printf("[BOARD] failed to start the ICM-20602 data-ready task\n");
        AlarmsSet(SYSTEMALARMS_ALARM_BOOTFAULT, SYSTEMALARMS_ALARM_CRITICAL);
    }
#endif /* PIOS_INCLUDE_ICM20602 */

    /* --- Actuator outputs --------------------------------------------- */
#ifdef PIOS_INCLUDE_SERVO
    if (PIOS_ESP32_Servo_Init(&pios_servo_cfg) != 0) {
        PIOS_Assert(0);
    }
#ifdef BOARD_PWM_SELFTEST
    board_pwm_selftest();
#endif
#ifdef BOARD_ESC_CAL
    /*
     * ESC endpoint calibration -- the USB-FREE way, and the only way on
     * this airframe. The BEC's 5V feeds VUSB, so battery and USB must
     * never be connected together (hard rule). Serial-driven calibration
     * tools are therefore impossible; instead the board does the classic
     * ritual itself at power-up, on battery power alone:
     *
     *   flash this build over USB -> UNPLUG USB -> connect battery.
     *   Board and ESCs power up together; all four outputs are already at
     *   MAX, so every ESC enters calibration and sings its max tone.
     *   6 seconds later the outputs drop to MIN; ESCs store the range and
     *   arm. LED: solid during MAX, fast blink during MIN, then normal.
     *
     *   Then reflash the normal build. PROPS OFF THROUGHOUT.
     *
     * Every power-up of THIS build recalibrates, which is why it must
     * never ship enabled -- same rule as BOARD_PWM_SELFTEST.
     */
    {
        PIOS_LED_On(PIOS_LED_HEARTBEAT);
        for (uint8_t ch = 0; ch < 4; ch++) {
            PIOS_Servo_Set(ch, 2000);
        }
        PIOS_Servo_Update();
        PIOS_DELAY_WaitmS(6000);

        for (uint8_t ch = 0; ch < 4; ch++) {
            PIOS_Servo_Set(ch, 1000);
        }
        PIOS_Servo_Update();
        for (uint8_t i = 0; i < 12; i++) {   /* 3s fast blink = MIN phase */
            PIOS_LED_Toggle(PIOS_LED_HEARTBEAT);
            PIOS_DELAY_WaitmS(250);
        }
        PIOS_LED_Off(PIOS_LED_HEARTBEAT);
    }
#endif
#endif

    /* --- RC input ------------------------------------------------------ */
#ifdef PIOS_INCLUDE_PPM
    {
        uint32_t pios_ppm_id;

        if (PIOS_ESP32_PPM_Init(&pios_ppm_id, &pios_ppm_cfg) != 0) {
            PIOS_Assert(0);
        }

        uint32_t pios_ppm_rcvr_id;

        if (PIOS_RCVR_Init(&pios_ppm_rcvr_id, &pios_esp32_ppm_rcvr_driver,
                           pios_ppm_id) != 0) {
            PIOS_Assert(0);
        }
        pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_PPM] = pios_ppm_rcvr_id;
    }
#endif /* PIOS_INCLUDE_PPM */

#ifdef PIOS_INCLUDE_DSM
    {
        uint32_t pios_dsm_id;

        /* Starts a task that listens for frames and, if the satellite turns
         * out not to be bound to anything, puts it into bind mode. That has
         * to happen close to power-up, which is why this is here rather than
         * behind a GCS command. */
        if (PIOS_ESP32_DSM_Init(&pios_dsm_id, &pios_dsm_cfg) != 0) {
            printf("[BOARD] DSM receiver failed to start\n");
            AlarmsSet(SYSTEMALARMS_ALARM_BOOTFAULT, SYSTEMALARMS_ALARM_CRITICAL);
        } else {
            uint32_t pios_dsm_rcvr_id;

            if (PIOS_RCVR_Init(&pios_dsm_rcvr_id, &pios_esp32_dsm_rcvr_driver,
                               pios_dsm_id) != 0) {
                PIOS_Assert(0);
            }
            pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_DSMMAINPORT] =
                pios_dsm_rcvr_id;

        }
    }
#endif /* PIOS_INCLUDE_DSM */

#ifdef PIOS_INCLUDE_GCSRCVR
    /* Bind the GCS receiver as an input source (same pattern the sim twin
     * uses). It sources nothing until ManualControlSettings maps a channel
     * group to GCS -- so it costs a real flight nothing, and it lets a UDP
     * client (tools/bench_test.py, or a GCS) drive the control channels for
     * ground testing without a transmitter. */
    {
        GCSReceiverInitialize();
        uint32_t pios_gcsrcvr_id;
        PIOS_GCSRCVR_Init(&pios_gcsrcvr_id);
        uint32_t pios_gcsrcvr_rcvr_id;
        if (PIOS_RCVR_Init(&pios_gcsrcvr_rcvr_id, &pios_gcsrcvr_rcvr_driver, pios_gcsrcvr_id)) {
            PIOS_Assert(0);
        }
        pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_GCS] = pios_gcsrcvr_rcvr_id;
    }
#endif /* PIOS_INCLUDE_GCSRCVR */

    /* From here the LED belongs to the status task, not to init. */
    board_ux_start();
}
