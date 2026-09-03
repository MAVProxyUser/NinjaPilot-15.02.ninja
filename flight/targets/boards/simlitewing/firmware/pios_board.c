/**
 ******************************************************************************
 * @addtogroup Revolution Revolution configuration files
 * @{
 * @brief Configures the revolution board
 * @{
 *
 * @file       pios_board.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2011.
 * @brief      Defines board specific static initializers for hardware for the Revolution board.
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
#include <actuatorsettings.h>
#include <mixersettings.h>
#include <taskinfo.h>
#include <firmwareiapobj.h>
#include <pios_icm20602.h>
#include <pthread.h>
#include <unistd.h>

/* The 100-byte "OpFw" description the make system compiled into this image
 * (make/firmware-defs.mk OPFW_TEMPLATE); its packed layout IS the blob the
 * GCS parses out of FirmwareIAPObj.Description. */
extern const struct fw_version_info fw_version_blob;

/* GCS IAP reset sequence (Command 1122 -> 2233 -> 3344), mirroring the ESP32
 * target's handler in its pios_board.c. On hardware the third command
 * restarts the chip; here it ends the process after a short grace period so
 * the write's ack and any pending telemetry drain first. The harness sees a
 * clean exit, not a crash. */
static void *sim_iap_exit_thread(__attribute__((unused)) void *arg)
{
    usleep(800 * 1000);
    printf("FirmwareIAP: reboot requested by GCS -- exiting\n");
    exit(0);
    return NULL;
}

static void sim_iap_updated_cb(__attribute__((unused)) UAVObjEvent *ev)
{
    static uint8_t iap_step = 0;
    FirmwareIAPObjData iap;

    FirmwareIAPObjGet(&iap);
    switch (iap.Command) {
    case 1122:
        iap_step = 1;
        break;
    case 2233:
        iap_step = (iap_step == 1) ? 2 : 0;
        break;
    case 3344:
        if (iap_step == 2) {
            pthread_t t;
            pthread_create(&t, NULL, sim_iap_exit_thread, NULL);
            pthread_detach(t);
        }
        iap_step = 0;
        break;
    default:
        iap_step = 0;
        break;
    }
}


/*
 * Pull in the board-specific static HW definitions.
 * Including .c files is a bit ugly but this allows all of
 * the HW definitions to be const and static to limit their
 * scope.
 *
 * NOTE: THIS IS THE ONLY PLACE THAT SHOULD EVER INCLUDE THIS FILE
 */
#include "../board_hw_defs.c"

/* Compiled-in Quad X + GCS control, mirroring the real ESP32 board's
 * board_apply_default_airframe (targets/esp32wroom) so the sim twin actually
 * OUTPUTS PWM when armed - the twin has no settings filesystem, so without
 * this its mixer comes up on the all-zero XML default and every motor
 * commands nothing. Receiver is mapped to GCS (this is a UDP-driven sim),
 * MotorsSpinWhileArmed is TRUE, and the neutral sits above the stop so idle
 * spin is visible. This runs every boot (RAM-only target); a UDP client may
 * still override any of it at runtime. */
static void simlitewing_apply_default_airframe(void)
{
    MixerSettingsData mixer;

    MixerSettingsGet(&mixer);
    mixer.ThrottleCurve1[0] = 0.0f;
    mixer.ThrottleCurve1[1] = 0.25f;
    mixer.ThrottleCurve1[2] = 0.5f;
    mixer.ThrottleCurve1[3] = 0.75f;
    mixer.ThrottleCurve1[4] = 1.0f;
    mixer.Mixer1Type = MIXERSETTINGS_MIXER1TYPE_MOTOR;
    mixer.Mixer1Vector.ThrottleCurve1 = 127;
    mixer.Mixer1Vector.Roll = 127; mixer.Mixer1Vector.Pitch = 127; mixer.Mixer1Vector.Yaw = -127;
    mixer.Mixer2Type = MIXERSETTINGS_MIXER2TYPE_MOTOR;
    mixer.Mixer2Vector.ThrottleCurve1 = 127;
    mixer.Mixer2Vector.Roll = -127; mixer.Mixer2Vector.Pitch = 127; mixer.Mixer2Vector.Yaw = 127;
    mixer.Mixer3Type = MIXERSETTINGS_MIXER3TYPE_MOTOR;
    mixer.Mixer3Vector.ThrottleCurve1 = 127;
    mixer.Mixer3Vector.Roll = -127; mixer.Mixer3Vector.Pitch = -127; mixer.Mixer3Vector.Yaw = -127;
    mixer.Mixer4Type = MIXERSETTINGS_MIXER4TYPE_MOTOR;
    mixer.Mixer4Vector.ThrottleCurve1 = 127;
    mixer.Mixer4Vector.Roll = 127; mixer.Mixer4Vector.Pitch = -127; mixer.Mixer4Vector.Yaw = 127;
    MixerSettingsSet(&mixer);

    /* ---------------------------------------------------------------------
     * BRUSHED output, not servo PWM. This is the whole point of the target.
     *
     * The ESP32 Thing Plus quad drives brushless ESCs, which want a 1000-2000
     * us pulse and need an idle above their stop or they never spin up. The
     * LiteWing drives four 720-size coreless motors straight through
     * IRLML6344 low-side N-channel MOSFETs (schematic V2.6.C, "Motor
     * Drivers"): the gate takes a DUTY CYCLE, 0 to 100%, at a carrier of
     * roughly 20 kHz. There is no pulse width, no arming ritual, no ESC
     * calibration, and nothing to protect against a stop that is below the
     * ESC's minimum.
     *
     * So the range is reinterpreted rather than reused: ChannelMin/Max are
     * 0..1000 = 0.0..100.0 % duty, tenths of a percent. The actuator pipeline
     * is untouched; only the meaning of the endpoints changes, and the
     * hardware backend turns the number into an LEDC duty instead of a pulse.
     *
     * MotorsSpinWhileArmed is FALSE and ChannelNeutral is 0 on purpose. A
     * brushed motor at zero duty simply stops, so the armed idle that exists
     * to keep ESCs alive is not needed here -- and that removes, by
     * construction, the failure that tipped the ESP32 quad over on its tail
     * on 2026-09-02: four equal idle thrusts lifting the light end while the
     * FC applied no stabilisation because throttle was below zero. On this
     * airframe an armed, throttle-down quad sits still.
     * ------------------------------------------------------------------- */
    ActuatorSettingsData act;
    ActuatorSettingsGet(&act);
    for (uint8_t i = 0; i < 4; i++) {
        act.ChannelType[i]    = ACTUATORSETTINGS_CHANNELTYPE_PWM;
        act.ChannelAddr[i]    = i;
        act.ChannelMin[i]     = 0;      /* 0.0 % duty -- motor stopped   */
        act.ChannelNeutral[i] = 0;      /* no ESC idle to hold           */
        act.ChannelMax[i]     = 1000;   /* 100.0 % duty                  */
    }
    act.MotorsSpinWhileArmed = ACTUATORSETTINGS_MOTORSSPINWHILEARMED_FALSE;
    ActuatorSettingsSet(&act);

    ManualControlSettingsData mc;
    ManualControlSettingsGet(&mc);
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
}

/**
 * Sensor configurations
 */

/* One slot per selectable receiver group.
 *  eg. PWM, PPM, GCS, SPEKTRUM1, SPEKTRUM2, SBUS
 * NOTE: No slot in this map for NONE.
 */
uint32_t pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_NONE];

// Was 512/512 - sized for a 57600-baud radio link on real hardware. On
// SimPosix with external physics this port carries the ENTIRE simulated
// sensor bus (500Hz gyro + accel + baro/mag/GPS + GCS control, tens of
// KB/s in per-tick bursts from pios_udp.c's drain loop), and at 512B the
// com fifo's whole-packet-discard-on-full behavior systematically
// destroyed the TAIL of each burst - measured live: gyroMatches=28464 vs
// accelMatches=195 (99.7% of AccelSensor lost, because accel is sent
// last in each tick's burst), which starved the altitude estimator's
// accel-integration branch down to ~4Hz. 8KB absorbs many full ticks of
// burst while the (SimPosix-elevated, see telemetry.c) parser drains.
#define PIOS_COM_TELEM_RF_RX_BUF_LEN  8192
#define PIOS_COM_TELEM_RF_TX_BUF_LEN  4096

// Every remaining com buffer bumped to desktop-appropriate sizes for the
// same reason as TELEM_RF above - and one of these tiny values was the
// PROVEN mechanism behind the deterministic last-packet-in-burst CRC
// kill: the per-tick sensor burst is 65 bytes (Accel 27 + ObjReq 11 +
// Gyro 27) and a 65-byte fifo with the classic one-reserved-byte
// circular design holds exactly 64 - the final byte (always the last
// packet's CRC) fell off EVERY tick, confirmed by the parser reporting
// perfectly-framed packets whose received "CRC" byte was a constant
// stale value while computed checksums varied normally. On real
// hardware these sizes are fine (real links pace bytes; SimPosix
// delivers whole bursts instantaneously).
#define PIOS_COM_GPS_RX_BUF_LEN       1024

#define PIOS_COM_TELEM_USB_RX_BUF_LEN 8192
#define PIOS_COM_TELEM_USB_TX_BUF_LEN 4096

#define PIOS_COM_BRIDGE_RX_BUF_LEN    1024
#define PIOS_COM_BRIDGE_TX_BUF_LEN    1024

#define PIOS_COM_AUX_RX_BUF_LEN       8192
#define PIOS_COM_AUX_TX_BUF_LEN       4096

uint32_t pios_com_aux_id       = 0;
uint32_t pios_com_gps_id       = 0;
uint32_t pios_com_telem_usb_id = 0;
uint32_t pios_com_telem_rf_id  = 0;
uint32_t pios_com_bridge_id    = 0;

uintptr_t pios_uavo_settings_fs_id;
uintptr_t pios_user_fs_id;

/*
 * Setup a com port based on the passed cfg, driver and buffer sizes. tx size of -1 make the port rx only
 */
static void PIOS_Board_configure_com(const struct pios_udp_cfg *usart_port_cfg, size_t rx_buf_len, size_t tx_buf_len,
                                     const struct pios_com_driver *com_driver, uint32_t *pios_com_id)
{
    uint32_t pios_usart_id;

    if (PIOS_UDP_Init(&pios_usart_id, usart_port_cfg)) {
        PIOS_Assert(0);
    }

    uint8_t *rx_buffer = (uint8_t *)pvPortMalloc(rx_buf_len);
    PIOS_Assert(rx_buffer);
    if (tx_buf_len != -1) { // this is the case for rx/tx ports
        uint8_t *tx_buffer = (uint8_t *)pvPortMalloc(tx_buf_len);
        PIOS_Assert(tx_buffer);

        if (PIOS_COM_Init(pios_com_id, com_driver, pios_usart_id,
                          rx_buffer, rx_buf_len,
                          tx_buffer, tx_buf_len)) {
            PIOS_Assert(0);
        }
    } else { // rx only port
        if (PIOS_COM_Init(pios_com_id, com_driver, pios_usart_id,
                          rx_buffer, rx_buf_len,
                          NULL, 0)) {
            PIOS_Assert(0);
        }
    }
}

/**
 * PIOS_Board_Init()
 * initializes all the core subsystems on this specific hardware
 * called from System/openpilot.c
 */
void PIOS_Board_Init(void)
{
    /* Delay system */
    PIOS_DELAY_Init();

    // Initialize logfs for settings.
    // If linking in yaffs for testing, this will be /dev0 with settings stored
    // via the logfs object api in /dev0/logfs/
    if (PIOS_FLASHFS_Logfs_Init(&pios_uavo_settings_fs_id, NULL, NULL, 0)) {
        PIOS_DEBUG_Assert(0);
    }
    // If linking in yaffs for testing, this will re-use the simposix yaffs /dev0 nor
    // simulation, which does not support being instanced twice.
    pios_user_fs_id = pios_uavo_settings_fs_id;

    /* Initialize the task monitor */
    if (PIOS_TASK_MONITOR_Initialize(TASKINFO_RUNNING_NUMELEM)) {
        PIOS_Assert(0);
    }

    /* Initialize the delayed callback library */
    PIOS_CALLBACKSCHEDULER_Initialize();

    /* Initialize UAVObject libraries */
    EventDispatcherInitialize();
    UAVObjInitialize();

    HwSettingsInitialize();

    UAVObjectsInitializeAll();

    /* Give the twin a real QuadX airframe + GCS control so it outputs PWM
     * when armed (see the function comment). */
    simlitewing_apply_default_airframe();

    /* The GCS identifies the board through FirmwareIAPObj -- populate the
     * same identity the real ESP32 Thing Plus reports (board model 0x1202)
     * plus this build's version description, so the GCS treats the
     * simulation exactly like the hardware: same config screens, same
     * silkscreen pin labels, same UAVO-set version check. */
    {
        FirmwareIAPObjInitialize();
        FirmwareIAPObjData iap;
        FirmwareIAPObjGet(&iap);
        iap.BoardType     = pios_board_info_blob.board_type;
        iap.BoardRevision = pios_board_info_blob.board_rev;
        memset(iap.Description, 0, sizeof(iap.Description));
        memcpy(iap.Description, &fw_version_blob,
               sizeof(iap.Description) < sizeof(fw_version_blob) ?
               sizeof(iap.Description) : sizeof(fw_version_blob));
        FirmwareIAPObjSet(&iap);
        UAVObjConnectCallback(FirmwareIAPObjHandle(), sim_iap_updated_cb,
                              EV_UNPACKED);
    }

    /* Register the simulated ICM-20602 before the Attitude module starts
     * looking for its queue -- same ordering as the hardware board init. */
    if (PIOS_ICM20602_SIM_Init() != 0) {
        PIOS_Assert(0);
    }

    /* Initialize the alarms library */
    AlarmsInitialize();

    /* Configure IO ports */

    /* Configure Telemetry port */
    uint8_t hwsettings_rv_telemetryport;
    HwSettingsRV_TelemetryPortGet(&hwsettings_rv_telemetryport);

    switch (hwsettings_rv_telemetryport) {
    case HWSETTINGS_RV_TELEMETRYPORT_DISABLED:
        break;
    case HWSETTINGS_RV_TELEMETRYPORT_TELEMETRY:
        PIOS_Board_configure_com(&pios_udp_telem_cfg, PIOS_COM_TELEM_RF_RX_BUF_LEN, PIOS_COM_TELEM_RF_TX_BUF_LEN, &pios_udp_com_driver, &pios_com_telem_rf_id);
        break;
    case HWSETTINGS_RV_TELEMETRYPORT_COMAUX:
        PIOS_Board_configure_com(&pios_udp_telem_cfg, PIOS_COM_AUX_RX_BUF_LEN, PIOS_COM_AUX_TX_BUF_LEN, &pios_udp_com_driver, &pios_com_aux_id);
        break;
    } /*        hwsettings_rv_telemetryport */

    /* Configure GPS port */
    uint8_t hwsettings_rv_gpsport;
    HwSettingsRV_GPSPortGet(&hwsettings_rv_gpsport);
    switch (hwsettings_rv_gpsport) {
    case HWSETTINGS_RV_GPSPORT_DISABLED:
        break;

    case HWSETTINGS_RV_GPSPORT_TELEMETRY:
        PIOS_Board_configure_com(&pios_udp_gps_cfg, PIOS_COM_TELEM_RF_RX_BUF_LEN, PIOS_COM_TELEM_RF_TX_BUF_LEN, &pios_udp_com_driver, &pios_com_telem_rf_id);
        break;

    case HWSETTINGS_RV_GPSPORT_GPS:
        PIOS_Board_configure_com(&pios_udp_gps_cfg, PIOS_COM_GPS_RX_BUF_LEN, -1, &pios_udp_com_driver, &pios_com_gps_id);
        break;

    case HWSETTINGS_RV_GPSPORT_COMAUX:
        PIOS_Board_configure_com(&pios_udp_gps_cfg, PIOS_COM_AUX_RX_BUF_LEN, PIOS_COM_AUX_TX_BUF_LEN, &pios_udp_com_driver, &pios_com_aux_id);
        break;
    } /* hwsettings_rv_gpsport */

    /* Configure AUXPort */
    uint8_t hwsettings_rv_auxport;
    HwSettingsRV_AuxPortGet(&hwsettings_rv_auxport);

    switch (hwsettings_rv_auxport) {
    case HWSETTINGS_RV_AUXPORT_DISABLED:
        break;

    case HWSETTINGS_RV_AUXPORT_TELEMETRY:
        PIOS_Board_configure_com(&pios_udp_aux_cfg, PIOS_COM_TELEM_RF_RX_BUF_LEN, PIOS_COM_TELEM_RF_TX_BUF_LEN, &pios_udp_com_driver, &pios_com_telem_rf_id);
        break;

    case HWSETTINGS_RV_AUXPORT_COMAUX:
        PIOS_Board_configure_com(&pios_udp_aux_cfg, PIOS_COM_AUX_RX_BUF_LEN, PIOS_COM_AUX_TX_BUF_LEN, &pios_udp_com_driver, &pios_com_aux_id);
        break;
        break;
    } /* hwsettings_rv_auxport */

#if defined(PIOS_INCLUDE_GCSRCVR)
    GCSReceiverInitialize();
    uint32_t pios_gcsrcvr_id;
    PIOS_GCSRCVR_Init(&pios_gcsrcvr_id);
    uint32_t pios_gcsrcvr_rcvr_id;
    if (PIOS_RCVR_Init(&pios_gcsrcvr_rcvr_id, &pios_gcsrcvr_rcvr_driver, pios_gcsrcvr_id)) {
        PIOS_Assert(0);
    }
    pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_GCS] = pios_gcsrcvr_rcvr_id;
#endif /* PIOS_INCLUDE_GCSRCVR */

    // BootFault ties to IAP backup-register boot-count tracking on real
    // hardware (coptercontrol/pios_board.c) - there's no bootloader/IAP
    // hardware to check here, and no code path anywhere sets this alarm
    // for simposix, so it just sits at its Uninitialised default forever.
    // A cold SITL process trivially never had a boot fault.
    AlarmsClear(SYSTEMALARMS_ALARM_BOOTFAULT);

    // GPS/Airspeed modules read HwSettings.OptionalModules exactly once,
    // via MODULE_INITCALL in initTask() right after this function returns
    // - a UAVTalk write from the ground tool after boot is far too late,
    // GPSStart()/AirspeedStart() will have already decided not to create
    // their tasks. Enable both here instead, before MODULE_INITIALISE_ALL
    // runs. The simulated sensors (sensors.c) already publish plausible
    // GPS/attitude/velocity data either way.
    HwSettingsInitialize();
    HwSettingsOptionalModulesData optionalModules;
    HwSettingsOptionalModulesGet(&optionalModules);
    optionalModules.GPS      = HWSETTINGS_OPTIONALMODULES_ENABLED;
    optionalModules.Airspeed = HWSETTINGS_OPTIONALMODULES_ENABLED;
    HwSettingsOptionalModulesSet(&optionalModules);

    // ActuatorSettings.ChannelMin/Neutral/Max stock-default to a degenerate
    // Min=Max=Neutral=1000 (the real "won't move until you run the Output
    // wizard" safety default) - the Actuator module scales its internal
    // mixer output into real PWM using these per-channel values, so a
    // zero-span range pins every output at 1000us regardless of what the
    // mixer computes. A runtime UAVTalk write for this object turned out to
    // be unreliable over this SITL link for reasons not fully root-caused
    // (isolated single-object writes for this specific object never landed,
    // even though byte-identical writes to other settings objects worked
    // fine) - setting it directly here at boot sidesteps that entirely,
    // same rationale as the HwSettings.OptionalModules block above.
    //
    // BRUSHED endpoints, and this block runs AFTER
    // simlitewing_apply_default_airframe() -- so it, not the airframe
    // function, is what the board actually ends up with. Measured the hard
    // way: the airframe function's 0/0/1000 was silently overwritten back to
    // 1000/1000/2000 here, and the probe read servo values on a brushed
    // board. Both places have to agree.
    //
    // The first four channels are coreless-motor gates: 0..1000 is 0.0..100.0
    // % duty, with no idle to hold (see the airframe function). The remaining
    // channels keep servo-style values because nothing on this airframe uses
    // them and a centred 1500 is the harmless default.
    ActuatorSettingsInitialize();
    ActuatorSettingsData actuatorSettings;
    ActuatorSettingsGet(&actuatorSettings);
    for (int i = 0; i < ACTUATORSETTINGS_CHANNELMIN_NUMELEM; i++) {
        actuatorSettings.ChannelMin[i]     = (i < 4) ? 0    : 1000;
        actuatorSettings.ChannelMax[i]     = (i < 4) ? 1000 : 2000;
        actuatorSettings.ChannelNeutral[i] = (i < 4) ? 0    : 1500;
    }
    actuatorSettings.MotorsSpinWhileArmed = ACTUATORSETTINGS_MOTORSSPINWHILEARMED_FALSE;
    ActuatorSettingsSet(&actuatorSettings);
}

/**
 * @}
 * @}
 */
