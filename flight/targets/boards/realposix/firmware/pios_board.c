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
#include <taskinfo.h>


/*
 * Pull in the board-specific static HW definitions.
 * Including .c files is a bit ugly but this allows all of
 * the HW definitions to be const and static to limit their
 * scope.
 *
 * NOTE: THIS IS THE ONLY PLACE THAT SHOULD EVER INCLUDE THIS FILE
 */
#include "../board_hw_defs.c"

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

    /* Initialize the alarms library */
    AlarmsInitialize();

#ifdef PIOS_INCLUDE_SENSORS_HUB
    /*
     * REALPOSIX: real sensors, read on a DEDICATED pthread rather than from a
     * FreeRTOS task. The Posix port runs one task at a time and a blocking
     * ioctl is not a FreeRTOS blocking point, so reading I2C from a task would
     * freeze the WHOLE firmware for ~506 us per sample - 25 % of a 500 Hz
     * period, scaling linearly with sensor count. Off the scheduler it is
     * free: measured, a 500 Hz RT loop sees 0.200 -> 0.270 ms worst-case
     * latency with the bus hammered continuously.
     *
     * Init failures are NOT fatal. A missing baro or a down CAN bus should
     * still leave a debuggable firmware, and the hub reports which sensors
     * came up. It only fails hard when NOTHING initialised.
     */
    if (PIOS_SENSORS_HUB_Init(PIOS_REALPOSIX_I2C_DEV, PIOS_REALPOSIX_CAN_IF) != 0) {
        PIOS_DEBUG_Assert(0);
    }
#endif

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
    ActuatorSettingsInitialize();
    ActuatorSettingsData actuatorSettings;
    ActuatorSettingsGet(&actuatorSettings);
    for (int i = 0; i < ACTUATORSETTINGS_CHANNELMIN_NUMELEM; i++) {
        actuatorSettings.ChannelMin[i]  = 1000;
        actuatorSettings.ChannelMax[i]  = 2000;
        // Motor channels (the first 4, matching board_orientation_viz.py's
        // QuadX mixer) use Neutral==Min for a clean 0-100% linear ESC
        // calibration; the rest default to a servo-style centered 1500.
        actuatorSettings.ChannelNeutral[i] = (i < 4) ? 1000 : 1500;
    }
    ActuatorSettingsSet(&actuatorSettings);
}

/**
 * @}
 * @}
 */
