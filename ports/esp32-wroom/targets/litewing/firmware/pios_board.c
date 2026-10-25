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
#include <math.h>   /* powf(), for the barometer sanity print at boot */
#include <flightstatus.h>
#include <systemalarms.h>
#include <gpspositionsensor.h>
#include <gpssettings.h>
#include <homelocation.h>
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
#ifdef PIOS_INCLUDE_I2C
static uint32_t pios_i2c_sensors_id;
#ifdef PIOS_INCLUDE_I2C
/* Second bus, expansion header SDA1/SCL1. Kept separate from the IMU bus --
 * see the config in board_hw_defs.c for why. */
static uint32_t pios_i2c_baro_id;
/* Whichever barometer driver the boot probe settled on, NULL if none. */
static const PIOS_SENSORS_Driver *baro_driver;

/* One-byte register read on the barometer bus. The parts disagree about where
 * their chip ID lives, so identification has to happen before any driver is
 * chosen -- which means it cannot use a driver's own read helper. */
static int32_t baro_read_reg(uint8_t addr, uint8_t reg, uint8_t *out)
{
    const struct pios_i2c_txn txn_list[] = {
        { .info = __func__, .addr = addr, .rw = PIOS_I2C_TXN_WRITE, .len = 1, .buf = &reg },
        { .info = __func__, .addr = addr, .rw = PIOS_I2C_TXN_READ,  .len = 1, .buf = out },
    };

    return PIOS_I2C_Transfer(pios_i2c_baro_id, txn_list, NELEMENTS(txn_list));
}
#endif
#endif

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

/*
 * PIOS_DEBUGLOG_Printf: console stand-in.
 *
 * pios/common/pios_debuglog.c stores entries through PIOS_FLASHFS_Obj*() on
 * pios_user_fs_id, and this target has no user flash filesystem yet (same
 * reason as the stubs above), so that implementation cannot be built here.
 * modules/PathPlanner calls this unconditionally -- there is no no-op path in
 * pios_debuglog.h -- so the symbol has to exist for navigation to link.
 *
 * These are low-rate mission events (waypoint reached, mission resumed), so
 * putting them on the console loses persistence but keeps the information.
 * Replace this with the real driver once there is a user FS to log into --
 * pulling logs off the board after a flight is the point of the real one.
 */
void PIOS_DEBUGLOG_Printf(char *format, ...)
{
    va_list args;

    va_start(args, format);
    printf("[LOG] ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

/* ---------------------------------------------------------------------- */
/* pios/common/pios_board_info.c is not built for this target: it places the
 * blob in a .boardinfo section that only the PiOS bootloader's linker script
 * defines, and it derives fw_base/fw_size from BL_/FW_BANK values that have no
 * meaning here (ESP-IDF's bootloader and partition table own the flash map).
 * Define it directly instead.
 *
 * board_rev MUST stay 0x02 -- see the comment in board-info.mk.
 *
 * board_type MUST match BOARD_TYPE in board-info.mk. Nothing checks that they
 * agree: board-info.mk feeds the build system, this struct is what the
 * firmware actually PUBLISHES (FirmwareIAPObj.BoardType, and byte 12 of the
 * firmware description). When this was left at the ESP32 quad's 0x12 while
 * board-info.mk said 0x13, the GCS obediently identified a LiteWing as a
 * SparkFun Thing Plus and showed it that board's hardware page and pin map. */
const struct pios_board_info pios_board_info_blob = {
    .magic      = PIOS_BOARD_INFO_BLOB_MAGIC,
    .board_type = 0x13,
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

uint32_t pios_com_gps_id;
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
     * The mixer rows stay the textbook quad X. What changes is which PIN each
     * row drives, via ChannelAddr below -- reordering outputs rather than
     * rewriting the mixer keeps the GCS mixer tab showing the conventional
     * table an operator expects.
     *
     * Corner geometry is read off the PCB (LieWingV2.6.C.kicad_pcb), not
     * guessed. Motor connector placements, KiCad coordinates with Y down:
     *
     *   J7   MOT_1  GPIO5   x 177.7  y  62.3   right, toward the "top" edge
     *   J8   MOT_2  GPIO6   x 179.1  y 124.4   right, toward the "bottom"
     *   J9   MOT_3  GPIO3   x 117.1  y 125.9   left,  toward the "bottom"
     *   J10  MOT_4  GPIO4   x 115.6  y  63.9   left,  toward the "top"
     *
     * Prop rotation comes off the silkscreen, which marks each position A or
     * B and prints the motor wire colours beside it:
     *
     *   J7  = B (black/white)      J8  = A (red/blue)
     *   J9  = B (black/white)      J10 = A (red/blue)
     *
     * A and B fall on opposite diagonals, which is exactly the quad X rule,
     * and it confirms the diagonal PAIRING is J7+J9 against J8+J10. Note it
     * does NOT fix which edge is the nose: the pattern is symmetric under a
     * 180 degree rotation, so both "top is front" and "bottom is front" fit
     * it. Taking the top edge as the nose:
     *
     *   mixer row 1  front-left   -> MOT_4  GPIO4   A  CW
     *   mixer row 2  front-right  -> MOT_1  GPIO5   B  CCW
     *   mixer row 3  rear-right   -> MOT_2  GPIO6   A  CW
     *   mixer row 4  rear-left    -> MOT_3  GPIO3   B  CCW
     *
     * The previous mapping had ChannelAddr 0,1,2,3, i.e. it treated MOT_1 as
     * front-left. The PCB says MOT_1 is on the RIGHT, so that was a quarter
     * turn out -- roll and pitch would both have been wrong while the yaw
     * pairing happened to survive.
     *
     * STILL TO CONFIRM: which edge is the nose, which is the same question as
     * which way the MPU6050's +X points. Settle it before flying, props off:
     * tilt the board nose-down and watch AttitudeState -- pitch should go
     * NEGATIVE. If it goes positive the frame is 180 degrees out, and the fix
     * is to swap the diagonal pairs (ChannelAddr 1,2,3,0 becomes 3,0,1,2).
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
        /* Mixer row -> output pin. See the corner geometry above:
         *   row 1 front-left  -> MOT_2 GPIO6 (index 1)
         *   row 2 front-right -> MOT_3 GPIO3 (index 2)
         *   row 3 rear-right  -> MOT_4 GPIO4 (index 3)
         *   row 4 rear-left   -> MOT_1 GPIO5 (index 0)
         * Bench-confirmed: the PCB fixes the geometry but not which edge is
         * the nose, and top-is-front was 180 degrees out. */
        static const uint8_t motor_addr[4] = { 1, 2, 3, 0 };

        act.ChannelType[i]    = ACTUATORSETTINGS_CHANNELTYPE_PWM;
        act.ChannelAddr[i]    = motor_addr[i];
        /* BRUSHED endpoints -- tenths of a percent duty, NOT microseconds.
         *
         * This is the single most dangerous number on the board. The output
         * backend is LEDC duty (pios_servo.c, cfg->brushed), so a channel
         * value of 1000 is 100% throttle, not "1000us = ESC stop". Carrying
         * the brushless 1000/1000/2000 defaults across from the ESP32 quad
         * would put all four motors at FULL POWER the moment Actuator ran,
         * armed or not, because a disarmed board outputs ChannelMin.
         *
         * There is no ESC to keep alive, so Neutral is 0 and a brushed motor
         * at 0 duty is simply stopped. */
        act.ChannelMin[i]     = 0;      /*   0.0 % duty -- motor stopped */
        act.ChannelNeutral[i] = 0;      /*   no ESC idle to hold         */
        act.ChannelMax[i]     = 1000;   /* 100.0 % duty                  */
    }
    act.MotorsSpinWhileArmed = ACTUATORSETTINGS_MOTORSSPINWHILEARMED_FALSE;
    /*
     * Point the sticks at the GCS receiver -- but only if nothing is mapped
     * yet (Throttle group None = never configured). This used to run
     * unconditionally on every boot, which meant the DSM satellite on IO15
     * was initialised below and then never read: any DSM mapping was
     * overwritten before ManualControl saw it. A stored mapping is the
     * user's and survives the boot.
     */
    {
        ManualControlSettingsData mc;

        ManualControlSettingsGet(&mc);
        if (mc.ChannelGroups.Throttle >= MANUALCONTROLSETTINGS_CHANNELGROUPS_NONE) {
            mc.ChannelGroups.Throttle   = MANUALCONTROLSETTINGS_CHANNELGROUPS_GCS;
            mc.ChannelGroups.Roll       = MANUALCONTROLSETTINGS_CHANNELGROUPS_GCS;
            mc.ChannelGroups.Pitch      = MANUALCONTROLSETTINGS_CHANNELGROUPS_GCS;
            mc.ChannelGroups.Yaw        = MANUALCONTROLSETTINGS_CHANNELGROUPS_GCS;
            mc.ChannelGroups.FlightMode = MANUALCONTROLSETTINGS_CHANNELGROUPS_GCS;
            mc.ChannelNumber.Throttle   = 1;
            mc.ChannelNumber.Roll       = 2;
            mc.ChannelNumber.Pitch      = 3;
            mc.ChannelNumber.Yaw        = 4;
            mc.ChannelNumber.FlightMode = 5;
            mc.ChannelMin.Throttle = 1000; mc.ChannelNeutral.Throttle = 1050; mc.ChannelMax.Throttle = 2000;
            mc.ChannelMin.Roll = 1000; mc.ChannelNeutral.Roll = 1500; mc.ChannelMax.Roll = 2000;
            mc.ChannelMin.Pitch = 1000; mc.ChannelNeutral.Pitch = 1500; mc.ChannelMax.Pitch = 2000;
            mc.ChannelMin.Yaw = 1000; mc.ChannelNeutral.Yaw = 1500; mc.ChannelMax.Yaw = 2000;
            mc.ChannelMin.FlightMode = 1000; mc.ChannelNeutral.FlightMode = 1500; mc.ChannelMax.FlightMode = 2000;
            ManualControlSettingsSet(&mc);
            UAVObjSave(ManualControlSettingsHandle(), 0);
        }
    }

    /* Meaningless on this board and left only so the field is not a stray 0:
     * the outputs are LEDC duty at a fixed 24 kHz carrier, and
     * PIOS_Servo_SetHz() is a no-op in brushed mode. There is no ESC whose
     * frame rate this could describe. */
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


#ifdef BOARD_CPU_REPORT
/*
 * Per-core idle reporting. SystemStats.CPULoad is
 * 100 - PIOS_TASK_MONITOR_GetIdlePercentage(), which samples
 * xTaskGetIdleTaskHandle() -- the idle task of whichever core the caller is
 * on. This port pins every flight task to core 1 and leaves WiFi on core 0,
 * so that number describes core 1 alone and says nothing about the other
 * core. When it reads 100%, this says whether core 1 is genuinely saturated
 * or the measurement is lying.
 */
static void board_cpu_report_task(void *arg)
{
    (void)arg;
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(2000));

        UBaseType_t n = uxTaskGetNumberOfTasks();
        TaskStatus_t *st = pios_malloc(n * sizeof(TaskStatus_t));
        if (!st) {
            continue;
        }
        uint32_t total = 0;
        n = uxTaskGetSystemState(st, n, &total);
        if (!total) {
            vPortFree(st);
            continue;
        }
        uint32_t idle0 = 0, idle1 = 0, busiest = 0;
        const char *busiest_name = "?";
        for (UBaseType_t i = 0; i < n; i++) {
            if (!strcmp(st[i].pcTaskName, "IDLE0")) {
                idle0 = st[i].ulRunTimeCounter;
            } else if (!strcmp(st[i].pcTaskName, "IDLE1")) {
                idle1 = st[i].ulRunTimeCounter;
            } else if (st[i].ulRunTimeCounter > busiest) {
                busiest = st[i].ulRunTimeCounter;
                busiest_name = st[i].pcTaskName;
            }
        }
        /* ulRunTimeCounter is cumulative since boot, so a raw print is a
         * since-boot AVERAGE that keeps converging and understates what the
         * board is doing now. Difference against the previous sample. Per-task
         * deltas need the previous value kept per task; match on the handle,
         * which is stable for the life of the task. */
#define CPUREP_MAX 48
        static TaskHandle_t p_h[CPUREP_MAX];
        static uint32_t p_rt[CPUREP_MAX];
        static uint32_t p_total, p_idle0, p_idle1;
        uint32_t d_total = total - p_total;

        if (d_total) {
            printf("[BOARD] ==== 2s ====  core0 idle %lu%%  core1 idle %lu%%\n",
                   (unsigned long)(100ULL * (idle0 - p_idle0) / d_total),
                   (unsigned long)(100ULL * (idle1 - p_idle1) / d_total));
            for (UBaseType_t i = 0; i < n; i++) {
                uint32_t prev = 0;
                for (int k = 0; k < CPUREP_MAX; k++) {
                    if (p_h[k] == st[i].xHandle) { prev = p_rt[k]; break; }
                }
                uint32_t d = st[i].ulRunTimeCounter - prev;
                unsigned pct = (unsigned)(1000ULL * d / d_total);
                if (pct >= 3) {
                    /* TaskStatus_t carries no core id in this IDF; ask the
                     * kernel for the task's affinity instead. */
                    BaseType_t core = xTaskGetCoreID(st[i].xHandle);
                    printf("[BOARD]   %-16s core%-3s %2u.%u%%\n",
                           st[i].pcTaskName,
                           (core == 0) ? "0" : (core == 1) ? "1" : "any",
                           pct / 10, pct % 10);
                }
            }
        }
        for (UBaseType_t i = 0; i < n && i < CPUREP_MAX; i++) {
            p_h[i] = st[i].xHandle; p_rt[i] = st[i].ulRunTimeCounter;
        }
        p_total = total; p_idle0 = idle0; p_idle1 = idle1;
        vPortFree(st);
    }
}
#endif

/*
 * Status LEDs.
 *
 * The board carries three LEDs (BLUE GPIO7, RED GPIO8, GREEN GPIO9) and the
 * firmware only ever used the blue one. Before a GPS-assisted flight you need
 * to know two things from across the field, without a laptop: may it arm, and
 * will position hold actually hold. So:
 *
 *   RED    off          disarmed, nothing blocking
 *          fast blink   CANNOT ARM - an arm-blocking alarm is set
 *          solid        ARMED
 *
 *   GREEN  off          no 3D fix
 *          slow blink   3D fix, but NOT good enough for position hold
 *          solid        position hold is ready
 *
 * Green deliberately mirrors filterlla.c's own admission test (Fix3D, plus
 * Satellites and PDOP against GPSSettings) and adds HomeLocation.Set. That is
 * the exact condition under which PositionState North/East stop being zero, so
 * a solid green means the brake-and-hold has real position to work with --
 * rather than merely meaning "a GPS is plugged in", which is the thing that
 * would get a quad flown into a fence.
 *
 * Runs on core 0 with the rest of the housekeeping; see the affinity table in
 * pios_esp32.h.
 */
static void board_status_led_task(__attribute__((unused)) void *arg)
{
    /* UAVObjects are registered by the module init that runs after this task
     * is created, so wait for the ones we read rather than racing them. */
    while (!GPSPositionSensorHandle() || !FlightStatusHandle()
           || !SystemAlarmsHandle() || !HomeLocationHandle()
           || !GPSSettingsHandle()) {
        vTaskDelay(pdMS_TO_TICKS(250));
    }

    uint32_t tick = 0;

    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(100));
        tick++;

        /* ---- RED: arming ---- */
        uint8_t armed = FLIGHTSTATUS_ARMED_DISARMED;
        FlightStatusArmedGet(&armed);

        if (armed == FLIGHTSTATUS_ARMED_ARMED) {
            PIOS_LED_On(PIOS_LED_ARMED);
        } else {
            /* Same rule armhandler.c:okToArm() applies: any Critical alarm
             * blocks, except GPS and Telemetry. */
            SystemAlarmsData alarms;
            SystemAlarmsGet(&alarms);
            bool blocked = false;
            for (uint8_t i = 0; i < SYSTEMALARMS_ALARM_NUMELEM; i++) {
                if (i == SYSTEMALARMS_ALARM_GPS || i == SYSTEMALARMS_ALARM_TELEMETRY) {
                    continue;
                }
                if (SystemAlarmsAlarmToArray(alarms.Alarm)[i] >= SYSTEMALARMS_ALARM_CRITICAL) {
                    blocked = true;
                    break;
                }
            }
            if (blocked) {
                if (tick & 1) {         /* ~5Hz */
                    PIOS_LED_On(PIOS_LED_ARMED);
                } else {
                    PIOS_LED_Off(PIOS_LED_ARMED);
                }
            } else {
                PIOS_LED_Off(PIOS_LED_ARMED);
            }
        }

        /* ---- GREEN: navigation readiness ---- */
        GPSPositionSensorData gps;
        GPSSettingsData gpsSettings;
        HomeLocationData home;

        GPSPositionSensorGet(&gps);
        GPSSettingsGet(&gpsSettings);
        HomeLocationGet(&home);

        bool fix3d = (gps.Status == GPSPOSITIONSENSOR_STATUS_FIX3D);
        bool navReady = fix3d
                        && (gps.Satellites >= gpsSettings.MinSatellites)
                        && (gps.PDOP < gpsSettings.MaxPDOP)
                        && (home.Set == HOMELOCATION_SET_TRUE);

        if (navReady) {
            PIOS_LED_On(PIOS_LED_NAVREADY);
        } else if (fix3d) {
            if ((tick % 10) < 5) {      /* ~1Hz */
                PIOS_LED_On(PIOS_LED_NAVREADY);
            } else {
                PIOS_LED_Off(PIOS_LED_NAVREADY);
            }
        } else {
            PIOS_LED_Off(PIOS_LED_NAVREADY);
        }
    }
}

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

    /* ------------------------------------------------------------------
     * Brushed-endpoint sanity gate.
     *
     * board_apply_default_airframe() bails out early on a provisioned board,
     * so STORED settings reach the outputs untouched -- and a board that was
     * ever provisioned against a brushless target carries ChannelMin = 1000.
     * On this target that is not "ESC stop", it is 100% duty on a coreless
     * motor with no ESC in the way: four motors at full power on a disarmed
     * board. The stored value is not silently rewritten (that is the
     * operator's data), but it is refused: BootFault blocks arming and the
     * reason goes out over telemetry.
     * ------------------------------------------------------------------ */
    {
        ActuatorSettingsData chk;
        ActuatorSettingsGet(&chk);
        for (uint8_t i = 0; i < 4; i++) {
            if (chk.ChannelMin[i] > 100 || chk.ChannelNeutral[i] > 100) {
                printf("[BOARD] REFUSING OUTPUTS: channel %u has Min=%d Neutral=%d. "
                       "These are BRUSHED duty units (0..1000 = 0..100%%), so that is "
                       "%d%% throttle at rest -- almost certainly brushless settings "
                       "(1000/1000/2000) left over from another target. Set Min and "
                       "Neutral to 0 and Max to 1000.\n",
                       (unsigned)i, (int)chk.ChannelMin[i], (int)chk.ChannelNeutral[i],
                       (int)(chk.ChannelMin[i] / 10));
                AlarmsSet(SYSTEMALARMS_ALARM_BOOTFAULT, SYSTEMALARMS_ALARM_CRITICAL);
                break;
            }
        }
    }

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
#ifdef PIOS_INCLUDE_GPS
    /* UART1 on the expansion header. Brought up unconditionally: a module that
     * is not plugged in simply never sends anything, and modules/GPS raises its
     * own alarm for that, which is more useful than a silent absence. */
    board_com_init(&pios_com_gps_id, &pios_usart_gps_cfg,
                   PIOS_COM_GPS_RX_BUF_LEN, PIOS_COM_GPS_TX_BUF_LEN);
    printf("[BOARD] GPS UART1 up on RX=GPIO18 TX=GPIO17 @115200\n");
#endif

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

    /* --- Sensor bus ---------------------------------------------------
     * LiteWing's IMU is an MPU6050 on I2C0 (SCL 10 / SDA 11), not an
     * ICM-20602 on SPI. The SPI bus is still brought up because the
     * expansion header carries it for an optional PMW3901 flow module. */
#ifdef PIOS_INCLUDE_I2C
    if (PIOS_ESP32_I2C_Init(&pios_i2c_sensors_id, &pios_i2c_sensors_cfg) != 0) {
        PIOS_Assert(0);
    }
#endif
    if (PIOS_ESP32_SPI_Init(&pios_spi_sensors_id, &pios_spi_sensors_cfg) != 0) {
        PIOS_Assert(0);
    }

#ifdef PIOS_INCLUDE_I2C
    /* Cheap and worth its bytes: a bus scan turns "the IMU is dead" into
     * "nothing answers at all" vs "the IMU answers but WHO_AM_I is wrong",
     * and it also finds a baro/mag added to the expansion header. */
    {
        static const uint8_t scan[] = { 0x68, 0x69, 0x76, 0x77, 0x1E, 0x0D };
        printf("[BOARD] I2C0 scan (SCL=10 SDA=11):");
        for (unsigned i = 0; i < NELEMENTS(scan); i++) {
            if (PIOS_ESP32_I2C_Probe(pios_i2c_sensors_id, scan[i])) {
                printf(" 0x%02X", scan[i]);
            }
        }
        printf("\n");
    }

    /* --- Barometer bus (I2C1, expansion header) ------------------------
     * Brought up unconditionally so the scan below reports an empty header
     * as "nothing answered" rather than not running at all. A failure here
     * is not fatal: the aircraft flies in rate mode without a barometer,
     * and refusing to boot over a missing add-on sensor would be worse than
     * losing altitude hold. */
    if (PIOS_ESP32_I2C_Init(&pios_i2c_baro_id, &pios_i2c_baro_cfg) != 0) {
        printf("[BOARD] I2C1 init FAILED -- no barometer this boot\n");
        pios_i2c_baro_id = 0;
    } else {
        static const uint8_t bscan[] = { 0x76, 0x77, 0x29, 0x1E, 0x0D };
        printf("[BOARD] I2C1 scan (SCL=41 SDA=40):");
        for (unsigned i = 0; i < NELEMENTS(bscan); i++) {
            if (PIOS_ESP32_I2C_Probe(pios_i2c_baro_id, bscan[i])) {
                printf(" 0x%02X", bscan[i]);
            }
        }
        printf("\n");
    }
#endif

#ifdef BOARD_GPS_SNIFF
    {
        extern void PIOS_GPS_Sniff(void);
        PIOS_GPS_Sniff();
    }
#endif

#if defined(PIOS_INCLUDE_I2C) && (defined(PIOS_INCLUDE_BMP388) || defined(PIOS_INCLUDE_BMP280))
    if (pios_i2c_baro_id) {
        /* One barometer socket, several parts that might be in it.
         *
         * The I2C address does NOT identify the part: 0x76 and 0x77 are shared
         * by the BMP280, BME280, BMP388 and BMP390, and every breakout brings
         * out an ADDR/SDO pad that moves its part between the two -- so a
         * board silkscreened "default 0x77" can perfectly well answer at 0x76.
         *
         * The chip ID does identify it, but it lives at a different register
         * per family: 0x00 on a BMP388/BMP390, 0xD0 on a BMP280/BME280. A
         * BMP280 therefore cannot answer a BMP388 probe and vice versa, which
         * looks exactly like a dead sensor.
         *
         * So: try both addresses, read both ID registers, and print the raw
         * bytes whatever the outcome. Guessing which part is fitted from a
         * build flag is how this wasted a bench session.
         */
        static const uint8_t addrs[] = { 0x76, 0x77 };
        uint8_t baro_addr = 0;
        uint8_t id_bmp3 = 0;   /* register 0x00 -- BMP388 / BMP390 */
        uint8_t id_bmp2 = 0;   /* register 0xD0 -- BMP280 / BME280 */

        for (unsigned i = 0; i < NELEMENTS(addrs) && !baro_addr; i++) {
            uint8_t v;

            if (!PIOS_ESP32_I2C_Probe(pios_i2c_baro_id, addrs[i])) {
                continue;
            }
            baro_addr = addrs[i];
            if (baro_read_reg(baro_addr, 0x00, &v) == 0) {
                id_bmp3 = v;
            }
            if (baro_read_reg(baro_addr, 0xD0, &v) == 0) {
                id_bmp2 = v;
            }
            printf("[BOARD] baro at 0x%02X: reg0x00=0x%02X reg0xD0=0x%02X\n",
                   baro_addr, id_bmp3, id_bmp2);
        }

        if (!baro_addr) {
            printf("[BOARD] no barometer on I2C1 -- no altitude hold\n");
            AlarmsSet(SYSTEMALARMS_ALARM_I2C, SYSTEMALARMS_ALARM_WARNING);
        } else {
            int32_t brc = -100;
            const char *part = NULL;

#ifdef PIOS_INCLUDE_BMP388
            if (id_bmp3 == 0x50 || id_bmp3 == 0x60) {
                struct pios_bmp388_cfg c = pios_bmp388_cfg;
                c.i2c_addr = baro_addr;
                part = (id_bmp3 == 0x60) ? "BMP390" : "BMP388";
                brc  = PIOS_BMP388_Init(&c, pios_i2c_baro_id);
                if (brc == 0) {
                    PIOS_BMP388_Register();
                    baro_driver = &PIOS_BMP388_Driver;
                }
            }
#endif
#ifdef PIOS_INCLUDE_BMP280
            if (!part && id_bmp2 == 0x58) {
                struct pios_bmp280_cfg c = pios_bmp280_cfg;
                c.i2c_addr = baro_addr;
                part = "BMP280";
                brc  = PIOS_BMP280_Init(&c, pios_i2c_baro_id);
                if (brc == 0) {
                    PIOS_BMP280_Register();
                    baro_driver = &PIOS_BMP280_Driver;
                }
            }
#endif
            if (!part) {
                /* Answered, but is not a part we can drive. 0xD0 reading 0x60
                 * is a BME280 -- same pressure block plus humidity, but a
                 * different calibration layout, so the BMP280 driver would
                 * compensate it wrongly rather than fail. */
                printf("[BOARD] baro at 0x%02X is not a supported part "
                       "(reg0x00=0x%02X reg0xD0=0x%02X)%s\n",
                       baro_addr, id_bmp3, id_bmp2,
                       id_bmp2 == 0x60 ? " -- looks like a BME280" : "");
                AlarmsSet(SYSTEMALARMS_ALARM_I2C, SYSTEMALARMS_ALARM_CRITICAL);
            } else if (brc != 0) {
                /* Right part, rejected the configuration. */
                printf("[BOARD] %s init failed (%d) -- no altitude hold\n",
                       part, (int)brc);
                AlarmsSet(SYSTEMALARMS_ALARM_I2C, SYSTEMALARMS_ALARM_ERROR);
            } else {
                printf("[BOARD] %s at 0x%02X initialised\n", part, baro_addr);

                /* Print real readings at boot. A barometer that answers its
                 * chip ID but returns nonsense is a normal failure (trim
                 * parsed wrong, half-soldered SDA) and is invisible until
                 * something tries to hold altitude. Pressure near 1e5 Pa with
                 * a plausible room temperature is the cheap proof that the
                 * compensation maths suits THIS part's calibration. */
                for (int i = 0; i < 4; i++) {
                    PIOS_DELAY_WaitmS(40);
                    if (baro_driver->poll(0)) {
                        PIOS_SENSORS_1Axis_SensorsWithTemp s;
                        baro_driver->fetch(&s, sizeof(s), 0);
                        printf("[BOARD] %s sample %d: %.2f Pa  %.2f C  (~%.1f m)\n",
                               part, i, s.sample, s.temperature,
                               44330.0f * (1.0f - powf(s.sample / 101325.0f, 1.0f / 5.255f)));
                    } else {
                        printf("[BOARD] %s sample %d: not ready\n", part, i);
                    }
                }
#ifdef BOARD_BARO_SWEEP
                {
                    extern void PIOS_BaroSweep(uint32_t i2c_id, uint8_t addr, bool is_bmp388);
                    PIOS_BaroSweep(pios_i2c_baro_id, baro_addr,
                                   baro_driver == &PIOS_BMP388_Driver);
                }
#endif
            }
        }
    }
#endif


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
    /* 0x68: MPU6050 with AD0 low, which is how LiteWing wires it. */
    PIOS_ICM20602_InitI2C(pios_i2c_sensors_id, 0x68, &pios_icm20602_cfg);

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
        printf("[BOARD] no usable IMU on I2C0 (SCL=10 SDA=11 addr 0x68): WHO_AM_I=0x%02X "
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


#ifdef BOARD_CPU_REPORT
    xTaskCreate(board_cpu_report_task, "CPUReport", 3072 / 4, NULL,
                tskIDLE_PRIORITY + 1, NULL);
#endif

    /* Identify whatever is sitting at 0x1E on I2C1. A genuine HMC5883L/HMC5983
     * returns 'H','4','3' from its three ID registers (0x0A-0x0C); the QMC5883L
     * that is commonly sold under the same name lives at 0x0D instead and has a
     * different register map entirely. Check before registering: a magnetometer
     * that answers but misidentifies would fail PIOS_SENSORS_Test(), and
     * SensorsTask responds to that by parking without reloading its watchdog
     * flag -- i.e. a silent board-wide reboot loop. */
    {
        uint8_t ida = 0, idb = 0, idc = 0;
        if (PIOS_ESP32_I2C_Probe(pios_i2c_baro_id, 0x1E)) {
            baro_read_reg(0x1E, 0x0A, &ida);
            baro_read_reg(0x1E, 0x0B, &idb);
            baro_read_reg(0x1E, 0x0C, &idc);
            printf("[BOARD] mag at 0x1E: id='%c%c%c' (0x%02X 0x%02X 0x%02X) -> %s\n",
                   (ida >= 32 && ida < 127) ? ida : '.',
                   (idb >= 32 && idb < 127) ? idb : '.',
                   (idc >= 32 && idc < 127) ? idc : '.',
                   ida, idb, idc,
                   (ida == 'H' && idb == '4' && idc == '3') ? "HMC5883L/5983"
                                                            : "UNKNOWN part");
        }
    }

#ifdef PIOS_INCLUDE_HMC5X83
    /* Bring the mag up only if it actually answered and identified above.
     * PIOS_SENSORS_Register()ing a part that then fails PIOS_SENSORS_Test()
     * makes SensorsTask park without reloading its watchdog flag, which the
     * board experiences as a silent reboot loop with no mention of the mag. */
    {
        uint8_t ida = 0, idb = 0, idc = 0;
        if (PIOS_ESP32_I2C_Probe(pios_i2c_baro_id, 0x1E)
            && baro_read_reg(0x1E, 0x0A, &ida) == 0
            && baro_read_reg(0x1E, 0x0B, &idb) == 0
            && baro_read_reg(0x1E, 0x0C, &idc) == 0
            && ida == 'H' && idb == '4' && idc == '3') {
            pios_hmc5x83_dev_t mag = PIOS_HMC5x83_Init(&pios_hmc5x83_cfg,
                                                       pios_i2c_baro_id, 0);
            if (mag) {
                PIOS_HMC5x83_Register(mag);
                printf("[BOARD] HMC5883L at 0x1E registered\n");
            } else {
                printf("[BOARD] HMC5883L at 0x1E failed to initialise\n");
            }
        }
    }
#endif /* PIOS_INCLUDE_HMC5X83 */

    xTaskCreate(board_status_led_task, "StatusLED", 3072 / 4, NULL,
                tskIDLE_PRIORITY + 1, NULL);

    /* Report what modules/Sensors will find. Its SensorsTask runs the same
     * PIOS_SENSORS_Test() over this list and, if ANY of them fails, parks in a
     * `while (1) vTaskDelay(10)` that never reloads its watchdog flag -- so a
     * single failing sensor shows up as a board-wide watchdog reboot loop with
     * both cores idle and nothing naming the sensor. Say which one here. */
    {
        const PIOS_SENSORS_Instance *list = PIOS_SENSORS_GetList();
        PIOS_SENSORS_Instance *si;
        LL_FOREACH((PIOS_SENSORS_Instance *)list, si) {
            printf("[BOARD] sensor type=0x%02X polled=%d test=%s\n",
                   (unsigned)si->type, (int)si->driver->is_polled,
                   PIOS_SENSORS_Test(si) ? "PASS" : "FAIL");
        }
    }

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
