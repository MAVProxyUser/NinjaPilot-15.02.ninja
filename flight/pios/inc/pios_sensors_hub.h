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
struct pios_sensors_hub_data {
    float    gyro_dps[3];     /* deg/s, sensor frame          */
    float    accel_mss[3];    /* m/s^2, sensor frame          */
    float    imu_temp_c;
    double   imu_time;        /* CLOCK_MONOTONIC seconds      */
    uint32_t imu_count;
    uint32_t imu_errors;

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

    bool     have_imu;
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

#endif /* PIOS_SENSORS_HUB_H */
