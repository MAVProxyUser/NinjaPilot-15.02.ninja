/**
 ******************************************************************************
 * @file       pios_sensors_hub.h
 * @author     NinjaPilot, 2026
 * @brief      Realposix sensor hub - all sensors, one dedicated reader thread
 * @see        The GNU Public License (GPL) Version 3
 *****************************************************************************/
#ifndef PIOS_SENSORS_HUB_H
#define PIOS_SENSORS_HUB_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Snapshot of every sensor. Copied out under a seqlock, so a reader either
 * gets a wholly consistent set or retries - never a torn mix of two updates.
 * Units are the ones the flight code wants, converted at the source.
 */
#define PIOS_HUB_MAX_NODES 8

/** uavcan.protocol.NodeStatus - per-node health, the bus's own liveness signal */
struct pios_hub_node {
    uint8_t  node_id;
    uint8_t  health;        /* 0 OK, 1 WARNING, 2 ERROR, 3 CRITICAL   */
    uint8_t  mode;          /* 0 OPERATIONAL, 1 INIT, 2 MAINT, 7 OFFLINE */
    uint8_t  sub_mode;
    uint32_t uptime_sec;
    uint16_t vendor_code;
    double   last_seen;     /* CLOCK_MONOTONIC; stale => node gone      */
    uint32_t count;
};

struct pios_sensors_hub_data {
    float    gyro_dps[3];     /* deg/s, sensor frame          */
    float    accel_mss[3];    /* m/s^2, sensor frame          */
    float    imu_temp_c;
    double   imu_time;        /* CLOCK_MONOTONIC seconds      */
    uint32_t imu_count;
    uint32_t imu_errors;

    /* Second barometer: BMP280 on the MP1's own I2C (0x76/0x77, chip 0x58).
     * The CAN baro's local twin - BaroSensor failover source. */
    float    baro2_press_pa;
    float    baro2_temp_c;
    double   baro2_time;
    uint32_t baro2_count;
    bool     have_baro2;

    /* Third magnetometer: the QMC5883P on the M9N-5883, via node 124's
     * MagneticFieldStrength. UNCALIBRATED (bench |B| reads ~76 uT vs the
     * RM3100's 51) - ingested for visibility, not yet published. */
    float    qmc_ga[3];
    uint8_t  qmc_node;
    double   qmc_time;
    uint32_t qmc_count;

    /* Second IMU: the MPU-9150 on the L431 CAN node, via the compact
     * single-frame stream (msgs 20500/20501). Failover source only. */
    float    imu2_gyro_dps[3];
    float    imu2_accel_mss[3];
    double   imu2_time;
    uint32_t imu2_count;

    float    press_pa;        /* Pascals                      */
    float    baro_temp_c;
    double   baro_time;
    uint32_t baro_count;
    uint32_t baro_errors;

    float    mag_ga[3];       /* Gauss, RM3100 via DroneCAN   */
    uint8_t  mag_node;
    double   mag_time;
    uint32_t mag_count;

    float    mag2_ga[3];      /* Gauss, HMC5883L on local I2C */
    double   mag2_time;
    uint32_t mag2_count;
    uint32_t mag2_errors;

    struct pios_hub_node nodes[PIOS_HUB_MAX_NODES];
    uint8_t  node_count;

    /* ardupilot.gnss.Status (msg 20003) - confirmed against the DSDL */
    uint32_t gnss_error_codes;
    bool     gnss_healthy;
    bool     gnss_armable;      /* STATUS_ARMABLE - "safe to arm"      */
    bool     gnss_logging;      /* STATUS_LOGGING                      */
    uint32_t gnss_status_raw;   /* full 23-bit field, undocumented bits */
    uint8_t  gnss_node;
    double   gnss_time;
    uint32_t gnss_count;

    /* uavcan.equipment.gnss.Fix2 (msg 1063) - decoded per the DSDL.
     * lat/lon VALIDATED only for the no-fix case until flown outdoors:
     * indoors, zero reads identically whether the bit offsets are right or
     * wrong, so the structural fields (status/sats/time standard) carry the
     * validation burden. See the decode comment in the .c. */
    int32_t  gps_lat_1e7;      /* degrees x 1e7, OpenPilot convention */
    int32_t  gps_lon_1e7;
    float    gps_alt_msl_m;
    float    gps_ned_vel[3];   /* m/s */
    float    gps_pdop;
    uint8_t  gps_sats;
    uint8_t  gps_fix;          /* 0 NO_FIX, 1 TIME_ONLY, 2 2D, 3 3D */
    double   gps_time;
    uint64_t gps_utc_usec;
    float    usb_amps;         /* USB-C negotiated current budget from the
                                  STUSB1600 (typec sysfs power_operation_mode):
                                  0.5 default / 1.5 / 3.0; 0 = not readable */     /* Fix2 gnss_timestamp: UTC usec since epoch,
                                  0 until the receiver has time (needs sats,
                                  not necessarily a position fix) */
    uint32_t gps_count;
    uint32_t gps_bad;          /* reassembly/decode rejects */

    /* gnss.Auxiliary (msg 1061): the DOPs Fix2 lacks, and the field that
     * separates "antenna sees nothing" from "solution uses nothing" */
    float    gps_hdop;
    float    gps_vdop;
    uint8_t  gps_sats_visible;
    /* per-satellite table (vendor msg 20502: NAV-SAT captured on the
     * node; az2 = azimuth/2 degrees) */
    uint8_t  gps_sat_count;
    uint8_t  gps_sat_svid[16];
    int8_t   gps_sat_elev[16];
    uint8_t  gps_sat_az2[16];
    uint8_t  gps_sat_cno[16];
    uint32_t gps_sat_seq;
    /* CAN IMU die temperature (vendor 20503, 1 Hz): degC = raw/340 + 35 */
    float    imu2_temp_c;
    bool     have_imu2_temp;
    /* IST8310 die temp, RAW counts (iSentek publishes no conversion) */
    int16_t  auxmag_temp_raw;
    bool     have_auxmag_temp;
    /* AK8975 (the 9150's own compass) via vendor 20504: mGa, device frame */
    float    ak_mga[3];
    bool     ak_overflow;
    uint32_t ak_count;
    uint32_t gps_aux_count;

    /* CAN bus health, rolling 1 s window: utilisation in permille of the
     * 1 Mbit wire (from measured frame sizes, same accounting as the 10 s
     * hub-health print) and total frames ever seen. Drives the CAN tile. */
    uint32_t can_load_pm;
    uint32_t can_frames;
    bool     can_seen;

    /* Power source, from the DWC2 OTG controller's B-session-valid bit
     * (VBUS present = USB power attached). CAVEAT: a data cable from a
     * host also raises VBUS, so this reads "USB" whenever any powered
     * cable is on the USB-C port, even if the jack is supplying too. */
    bool     vbus_present;
    bool     have_pwr;

    bool     have_imu;
    bool     have_imu2;
    bool     have_baro;
    bool     have_mag;        /* RM3100 over CAN   */
    bool     have_mag2;       /* HMC5883L on I2C   */
};

/**
 * Open the sensors and start the reader thread.
 * @param i2c_dev e.g. "/dev/i2c-3"   @param can_if e.g. "can0"
 * @return 0 if at least one sensor came up, -1 if none did
 */
extern int32_t PIOS_SENSORS_HUB_Init(const char *i2c_dev, const char *can_if);

/** Wait-free consistent snapshot. False only if a writer kept winning. */
extern bool PIOS_SENSORS_HUB_Get(struct pios_sensors_hub_data *out);

extern void PIOS_SENSORS_HUB_Stop(void);
/* Commanded rates for the node's deadman-gated streams; broadcast at 1 Hz
 * as vendor msg 20510. Until this is called the hub sends nothing and the
 * node stays silent - a freshly booted bus is always flash-quiet. */
extern void PIOS_SENSORS_HUB_SetCanStreamRates(uint16_t imu_hz, uint8_t ak_hz);

#endif /* PIOS_SENSORS_HUB_H */
