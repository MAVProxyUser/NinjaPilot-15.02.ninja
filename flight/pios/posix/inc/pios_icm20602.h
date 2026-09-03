/**
 ******************************************************************************
 * @file       pios_icm20602.h
 * @author     NinjaPilot, 2026
 * @brief      Posix twin of the ESP32 target's ICM-20602 driver interface.
 *
 * The SIM_WROOM target compiles the Attitude module down the exact same
 * PIOS_INCLUDE_ICM20602 branch the ESP32 Thing Plus hardware build takes;
 * this header stands in for the hardware repo's pios/esp32/inc/pios_icm20602.h
 * and exposes only what attitude.c consumes -- the driver struct -- plus the
 * simulation feeder's init hook.
 * @see        The GNU Public License (GPL) Version 3
 *****************************************************************************/
#ifndef PIOS_ICM20602_H
#define PIOS_ICM20602_H

#include <pios_sensors.h>

extern const PIOS_SENSORS_Driver PIOS_ICM20602_Driver;

/* Simulation only: create the sample queue, subscribe to the bridge's
 * GyroSensor/AccelSensor UAVObjects, register with the sensor subsystem. */
extern int32_t PIOS_ICM20602_SIM_Init(void);

#endif /* PIOS_ICM20602_H */
