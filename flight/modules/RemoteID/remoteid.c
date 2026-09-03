/**
 ******************************************************************************
 * @addtogroup Modules
 * @{
 * @addtogroup RemoteIDModule ASTM F3411 Broadcast Remote ID
 * @brief Encodes the aircraft's identity and state into Remote ID messages
 *        once a second and hands the pack to the board's transmitter.
 *
 * Content:
 *   Basic ID     RemoteIDSettings.IDType / UASID / UAType (skipped when unset)
 *   Location     status from FlightStatus.Armed; position, altitude, speed,
 *                direction and time from GPSPositionSensor/GPSTime when there
 *                is a fix, otherwise the standard's "Unknown" encodings
 *   System       operator location = takeoff position, latched from the GPS
 *                at the moment of arming (F3411 OPERATOR_LOCATION_TYPE_TAKEOFF)
 *   Self-ID      RemoteIDSettings.SelfIDText (skipped when empty)
 *   Operator ID  RemoteIDSettings.OperatorID (skipped when empty)
 *
 * Honesty note: a broadcast without a position is not a compliant Remote ID
 * anywhere. This module is standards-shaped so it becomes complete the moment
 * a GPS is wired (the ESP32's spare UART2) - it never invents a position.
 *
 * Encoding is the reference implementation (flight/libraries/opendroneid,
 * Apache-2.0); the pack assembly below mirrors odid_message_build_pack().
 * @{
 * @see        The GNU Public License (GPL) Version 3
 *****************************************************************************/

#include "openpilot.h"
#include "inc/remoteid.h"
#include <remoteidsettings.h>
#include <remoteidstatus.h>
#include <flightstatus.h>
#include <gpspositionsensor.h>
#include <gpstime.h>
#include <pios_rid.h>
#ifndef ODID_AUTH_MAX_PAGES
#define ODID_AUTH_MAX_PAGES 1   /* must match the library's build definition */
#endif
#include "opendroneid.h"
#include <string.h>
#include <math.h>

#define STACK_SIZE_BYTES 2048
#define TASK_PRIORITY    (tskIDLE_PRIORITY + 1)
#define PERIOD_MS        1000          /* F3411: Location at >= 1 Hz */
#define UNIX_2019        1546300800u   /* System.Timestamp epoch: 2019-01-01T00:00:00Z */

static xTaskHandle taskHandle;
static ODID_UAS_Data uas;                /* static: too large for a small stack */
static uint8_t packBuf[3 + ODID_PACK_MAX_MESSAGES * ODID_MESSAGE_SIZE];
static uint8_t msgCounter;
static bool takeoffValid;
static double takeoffLat, takeoffLon;
static float takeoffAltGeo;
static uint8_t lastArmed = FLIGHTSTATUS_ARMED_DISARMED;

static void RemoteIDTask(void *parameters);

int32_t RemoteIDInitialize(void)
{
    RemoteIDSettingsInitialize();
    RemoteIDStatusInitialize();
    return 0;
}

int32_t RemoteIDStart(void)
{
    xTaskCreate(RemoteIDTask, "RemoteID", STACK_SIZE_BYTES / 4, NULL, TASK_PRIORITY, &taskHandle);
    return 0;
}
MODULE_INITCALL(RemoteIDInitialize, RemoteIDStart);

/* NUL-padded copy of a uint8 UAVO array into an ODID string field */
static void copy_field(char *dst, size_t dstsz, const uint8_t *src, size_t n)
{
    memset(dst, 0, dstsz);
    for (size_t i = 0; i < n && i + 1 < dstsz && src[i]; i++) {
        dst[i] = (char)src[i];
    }
}

/* days since 1970-01-01 for a proleptic Gregorian civil date */
static uint32_t days_from_civil(int y, unsigned m, unsigned d)
{
    y -= m <= 2;
    const int era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = (unsigned)(y - era * 400);
    const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return (uint32_t)(era * 146097 + (int)doe - 719468);
}

/* Assemble the pack exactly like the reference odid_message_build_pack() */
static int build_pack(uint8_t *out, size_t outsz)
{
    ODID_MessagePack_data mp;
    memset(&mp, 0, sizeof(mp));
    mp.SingleMessageSize = ODID_MESSAGE_SIZE;
    mp.MsgPackSize = 0;
    for (int i = 0; i < ODID_BASIC_ID_MAX_MESSAGES; i++) {
        if (uas.BasicIDValid[i] && mp.MsgPackSize < ODID_PACK_MAX_MESSAGES
            && encodeBasicIDMessage((void *)&mp.Messages[mp.MsgPackSize], &uas.BasicID[i]) == ODID_SUCCESS) {
            mp.MsgPackSize++;
        }
    }
    if (uas.LocationValid && mp.MsgPackSize < ODID_PACK_MAX_MESSAGES
        && encodeLocationMessage((void *)&mp.Messages[mp.MsgPackSize], &uas.Location) == ODID_SUCCESS) {
        mp.MsgPackSize++;
    }
    if (uas.SelfIDValid && mp.MsgPackSize < ODID_PACK_MAX_MESSAGES
        && encodeSelfIDMessage((void *)&mp.Messages[mp.MsgPackSize], &uas.SelfID) == ODID_SUCCESS) {
        mp.MsgPackSize++;
    }
    if (uas.SystemValid && mp.MsgPackSize < ODID_PACK_MAX_MESSAGES
        && encodeSystemMessage((void *)&mp.Messages[mp.MsgPackSize], &uas.System) == ODID_SUCCESS) {
        mp.MsgPackSize++;
    }
    if (uas.OperatorIDValid && mp.MsgPackSize < ODID_PACK_MAX_MESSAGES
        && encodeOperatorIDMessage((void *)&mp.Messages[mp.MsgPackSize], &uas.OperatorID) == ODID_SUCCESS) {
        mp.MsgPackSize++;
    }
    if (mp.MsgPackSize == 0) {
        return -1;
    }
    size_t len = sizeof(ODID_MessagePack_encoded) - (ODID_PACK_MAX_MESSAGES - mp.MsgPackSize) * ODID_MESSAGE_SIZE;
    if (len > outsz) {
        return -1;
    }
    if (encodeMessagePack((ODID_MessagePack_encoded *)out, &mp) != ODID_SUCCESS) {
        return -1;
    }
    return (int)len;
}

static void fill(const RemoteIDSettingsData *s, RemoteIDStatusData *st)
{
    odid_initUasData(&uas);

    /* --- Basic ID ------------------------------------------------------ */
    if (s->IDType != REMOTEIDSETTINGS_IDTYPE_NONE && s->UASID[0]) {
        uas.BasicID[0].UAType = (ODID_uatype_t)s->UAType;   /* same enumeration order as F3411 */
        uas.BasicID[0].IDType = (ODID_idtype_t)s->IDType;
        copy_field(uas.BasicID[0].UASID, sizeof(uas.BasicID[0].UASID), s->UASID, REMOTEIDSETTINGS_UASID_NUMELEM);
        uas.BasicIDValid[0] = 1;
    }

    /* --- Location / Vector --------------------------------------------- */
    FlightStatusData fs;
    FlightStatusGet(&fs);
    bool armed = fs.Armed == FLIGHTSTATUS_ARMED_ARMED;

    GPSPositionSensorData gps;
    bool fix = false, fix3d = false;
    if (GPSPositionSensorHandle()) {
        GPSPositionSensorGet(&gps);
        fix   = gps.Status == GPSPOSITIONSENSOR_STATUS_FIX2D || gps.Status == GPSPOSITIONSENSOR_STATUS_FIX3D;
        fix3d = gps.Status == GPSPOSITIONSENSOR_STATUS_FIX3D;
    }
    GPSTimeData gt;
    bool haveTime = false;
    if (GPSTimeHandle()) {
        GPSTimeGet(&gt);
        haveTime = gt.Year >= 2019;
    }

    ODID_Location_data *L = &uas.Location;
    L->Status          = armed ? ODID_STATUS_AIRBORNE : ODID_STATUS_GROUND;
    L->Direction       = INV_DIR;
    L->SpeedHorizontal = INV_SPEED_H;
    L->SpeedVertical   = INV_SPEED_V;
    L->Latitude        = 0;
    L->Longitude       = 0;
    L->AltitudeBaro    = INV_ALT;
    L->AltitudeGeo     = INV_ALT;
    L->HeightType      = ODID_HEIGHT_REF_OVER_TAKEOFF;
    L->Height          = INV_ALT;
    L->HorizAccuracy   = ODID_HOR_ACC_UNKNOWN;
    L->VertAccuracy    = ODID_VER_ACC_UNKNOWN;
    L->BaroAccuracy    = ODID_VER_ACC_UNKNOWN;
    L->SpeedAccuracy   = ODID_SPEED_ACC_UNKNOWN;
    L->TSAccuracy      = ODID_TIME_ACC_UNKNOWN;
    L->TimeStamp       = INV_TIMESTAMP;
    if (fix) {
        L->Latitude        = gps.Latitude * 1e-7;
        L->Longitude       = gps.Longitude * 1e-7;
        L->SpeedHorizontal = gps.Groundspeed;
        L->SpeedAccuracy   = ODID_SPEED_ACC_1_METERS_PER_SECOND;
        if (gps.Groundspeed > 0.5f) {
            float h = gps.Heading;
            while (h < 0) { h += 360.0f; }
            while (h >= 360.0f) { h -= 360.0f; }
            L->Direction = h;
        }
        L->HorizAccuracy = gps.HDOP < 2.0f ? ODID_HOR_ACC_10_METER : gps.HDOP < 6.0f ? ODID_HOR_ACC_30_METER : ODID_HOR_ACC_UNKNOWN;
        if (fix3d) {
            float hae = gps.Altitude + gps.GeoidSeparation;   /* MSL + separation = WGS84 HAE */
            L->AltitudeGeo  = hae;
            L->VertAccuracy = ODID_VER_ACC_10_METER;
            if (takeoffValid) {
                L->Height = hae - takeoffAltGeo;
            }
        }
        if (haveTime) {
            L->TimeStamp  = (float)(gt.Minute * 60 + gt.Second);   /* seconds after the hour */
            L->TSAccuracy = ODID_TIME_ACC_1_0_SECOND;
        }
    }
    uas.LocationValid = 1;

    /* takeoff latch: first arming with a fix defines the operator/takeoff point */
    if (armed && lastArmed != FLIGHTSTATUS_ARMED_ARMED && fix) {
        takeoffValid  = true;
        takeoffLat    = L->Latitude;
        takeoffLon    = L->Longitude;
        takeoffAltGeo = fix3d ? gps.Altitude + gps.GeoidSeparation : INV_ALT;
    }
    lastArmed = fs.Armed;

    /* --- System --------------------------------------------------------- */
    ODID_System_data *S = &uas.System;
    S->OperatorLocationType = ODID_OPERATOR_LOCATION_TYPE_TAKEOFF;
    S->ClassificationType   = ODID_CLASSIFICATION_TYPE_UNDECLARED;
    S->OperatorLatitude     = takeoffValid ? takeoffLat : 0;
    S->OperatorLongitude    = takeoffValid ? takeoffLon : 0;
    S->AreaCount   = 1;
    S->AreaRadius  = 0;
    S->AreaCeiling = INV_ALT;
    S->AreaFloor   = INV_ALT;
    S->CategoryEU  = ODID_CATEGORY_EU_UNDECLARED;
    S->ClassEU     = ODID_CLASS_EU_UNDECLARED;
    S->OperatorAltitudeGeo = takeoffValid ? takeoffAltGeo : INV_ALT;
    S->Timestamp = 0;
    if (haveTime) {
        uint32_t unix = days_from_civil(gt.Year, gt.Month, gt.Day) * 86400u + gt.Hour * 3600u + gt.Minute * 60u + gt.Second;
        S->Timestamp = unix > UNIX_2019 ? unix - UNIX_2019 : 0;
    }
    uas.SystemValid = 1;

    /* --- Self-ID / Operator ID ----------------------------------------- */
    if (s->SelfIDText[0]) {
        uas.SelfID.DescType = ODID_DESC_TYPE_TEXT;
        copy_field(uas.SelfID.Desc, sizeof(uas.SelfID.Desc), s->SelfIDText, REMOTEIDSETTINGS_SELFIDTEXT_NUMELEM);
        uas.SelfIDValid = 1;
    }
    if (s->OperatorID[0]) {
        uas.OperatorID.OperatorIdType = ODID_OPERATOR_ID;
        copy_field(uas.OperatorID.OperatorId, sizeof(uas.OperatorID.OperatorId), s->OperatorID, REMOTEIDSETTINGS_OPERATORID_NUMELEM);
        uas.OperatorIDValid = 1;
    }

    st->PositionSource = fix ? REMOTEIDSTATUS_POSITIONSOURCE_GPS : REMOTEIDSTATUS_POSITIONSOURCE_NONE;
}

static void RemoteIDTask(__attribute__((unused)) void *parameters)
{
    portTickType lastSysTime = xTaskGetTickCount();
    RemoteIDStatusData st;
    RemoteIDStatusGet(&st);
    bool wasOn = false;

    while (1) {
        vTaskDelayUntil(&lastSysTime, PERIOD_MS / portTICK_RATE_MS);

        RemoteIDSettingsData s;
        RemoteIDSettingsGet(&s);

        if (s.Enabled != REMOTEIDSETTINGS_ENABLED_TRUE) {
            if (wasOn) {
                PIOS_RID_Broadcast(NULL, 0, 0);   /* stop */
                wasOn = false;
            }
            st.State    = REMOTEIDSTATUS_STATE_DISABLED;
            st.Messages = 0;
            st.PositionSource = REMOTEIDSTATUS_POSITIONSOURCE_NONE;
            RemoteIDStatusSet(&st);
            continue;
        }

        fill(&s, &st);
        int len = build_pack(packBuf, sizeof(packBuf));
        if (len < 0) {
            st.State = REMOTEIDSTATUS_STATE_NOTRANSMITTER;
            RemoteIDStatusSet(&st);
            continue;
        }
        st.Messages = ((ODID_MessagePack_encoded *)packBuf)->MsgPackSize;
        if (PIOS_RID_Broadcast(packBuf, (uint16_t)len, msgCounter++) == 0) {
            wasOn = true;
            st.TxCount++;
            st.State = uas.BasicIDValid[0] ? REMOTEIDSTATUS_STATE_BROADCASTING : REMOTEIDSTATUS_STATE_NOID;
        } else {
            st.State = REMOTEIDSTATUS_STATE_NOTRANSMITTER;
        }
        RemoteIDStatusSet(&st);
    }
}

/**
 * @}
 * @}
 */
