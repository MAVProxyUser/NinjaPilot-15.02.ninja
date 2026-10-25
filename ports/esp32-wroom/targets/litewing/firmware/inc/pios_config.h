/**
 ******************************************************************************
 *
 * @file       pios_config.h
 * @author     NinjaPilot, 2026
 * @brief      PiOS feature selection for the ESP32-WROOM-32E target.
 *
 * This is the "slim" knob the port exists to exercise. It is modelled on the
 * CopterControl config -- the smallest real flight build in this tree -- and
 * trimmed further to rate-mode-only.
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

#ifndef PIOS_CONFIG_H
#define PIOS_CONFIG_H

/* Names this variant, the way PIOS_REALPOSIX does for that target. */
#define PIOS_ESP32_WROOM

/* --- Core ------------------------------------------------------------- */
#define PIOS_INCLUDE_FREERTOS
#define PIOS_INCLUDE_CALLBACKSCHEDULER
#define PIOS_INCLUDE_TASK_MONITOR
#define PIOS_INCLUDE_INITCALL
#define PIOS_INCLUDE_DELAY
#define PIOS_INCLUDE_SYS
#define PIOS_INCLUDE_IRQ
#define PIOS_INCLUDE_LED

/* Enabled, unlike the ArduPilot ESP32 port which turns the watchdogs off.
 * We are not blowing loop deadlines, so there is no reason to fly without
 * it. See pios_wdg.c. */
#define PIOS_INCLUDE_WDG

/* --- Buses and IO ----------------------------------------------------- */
#define PIOS_INCLUDE_SPI
#define PIOS_INCLUDE_COM
#define PIOS_INCLUDE_COM_TELEM
#define PIOS_INCLUDE_USART
#define PIOS_INCLUDE_SERVO
#define PIOS_INCLUDE_RCVR
/* GCS receiver: lets a UDP client drive the control channels over UAVTalk
 * (GCSReceiver object), exactly as the sim twin flies. Harmless for normal
 * flight - it is only an INPUT SOURCE, active only when ManualControlSettings
 * maps a channel group to GCS; the DSM stays the default. Enables tools/
 * bench_test.py to own the throttle for props-off characterization. */
/* Spektrum DSMX satellite (SPM9745) on the expansion header.
 * Signal to IO15, power from 3V3 -- a satellite is a 3.3V device. */
/* Outputs are LEDC duty into MOSFET gates, not ESC pulses. Makes actuator.c
 * refuse any resting endpoint above PIOS_ACTUATOR_BRUSHED_REST_MAX, whatever
 * client wrote it -- see the comment at ActuatorSettingsUpdatedCb(). */
#define PIOS_ACTUATOR_BRUSHED_OUTPUTS
#define PIOS_ACTUATOR_BRUSHED_REST_MAX 100   /* 10% duty; a real rest is 0 */
#define PIOS_ACTUATOR_BRUSHED_CHANNELS 4     /* channels that reach a pin */

#define PIOS_INCLUDE_DSM

/* GPS on UART1: a u-blox M10, driven over UBX.
 *
 * NMEA was tried first and does not work with this module, for a reason worth
 * recording. The M10 leaves the factory emitting UBX binary AND NMEA on the
 * same port, interleaved. parse_nmea_stream() abandons its whole input buffer
 * the moment it meets a byte that is not '$' outside a sentence, so every
 * chunk carrying a UBX frame took the NMEA that followed it down too: clean,
 * checksum-valid $GNRMC/$GNGSA sentences arrived continuously at ~4.7 kB/s and
 * the parser still completed only a couple of sentences a minute, leaving
 * GPSPositionSensor.Status at NoGPS.
 *
 * UBX is also simply the right protocol here: ubx_autoconfig configures the
 * receiver (which turns the NMEA output off, ending the interleaving at the
 * source), and the NAV solution carries velocity and per-axis accuracy
 * estimates that NMEA does not -- both of which position hold and return-to-
 * home consume. NMEA stays compiled in as a fallback for a different module.
 *
 * PIOS_GPS_MINIMAL is deliberately NOT set: it compiles out ubx_autoconfig
 * and the GPSSettings callback, which are the parts doing the work above. */
#define PIOS_INCLUDE_GPS
#define PIOS_INCLUDE_GPS_UBX_PARSER
#define PIOS_INCLUDE_GPS_NMEA_PARSER
/* Let the GPS set HomeLocation once it has a 3D fix. This is not optional
 * here: filtercf.c's mag variant rotates HomeLocation.Be as its heading
 * reference, so with Be = {0,0,0} the correction is degenerate and the
 * attitude estimate collapses toward zero instead of converging. It is also
 * what return-to-home needs a home to BE. Pulls in libraries/WorldMagModel.c,
 * which computes Be from lat/lon/alt, and raises the GPS task stack to 1024
 * (see STACK_SIZE_BYTES in GPS.c) for the WMM arithmetic -- our
 * PIOS_GPS_STACK_SIZE override already sits well above that. */
#define PIOS_GPS_SETS_HOMELOCATION
#define PIOS_INCLUDE_GCSRCVR
#define PIOS_INCLUDE_RID_WIFI   /* Remote ID as a beacon vendor element (pios_rid_wifi.c) */
/* PPM disabled: the RMT receiver on an unconnected pin collects coupled
 * noise edges (one per 500Hz SPI burst), fills its 64-item RX memory every
 * ~254ms, and its ISR then blocks level-1 interrupts on core 0 for ~3.6ms
 * -- starving the gyro DR interrupt. Re-enable only with a real PPM source
 * wired. DSM is this board's receiver. */
// #define PIOS_INCLUDE_PPM

/* No native USB on the WROOM-32 -- the console is UART0 through the devkit's
 * USB-serial bridge. (The S3 would allow PIOS_INCLUDE_USB_CDC here.) */
/* #define PIOS_INCLUDE_USB */

/* --- Sensors ---------------------------------------------------------- */
/* ICM-20602, which is NOT an MPU6000 -- see pios/esp32/pios_icm20602.c */
/* Publish the RAW AccelSensor/GyroSensor objects (with die temperature) from
 * attitude.c, which the Revo path gets from sensors.c and this one otherwise
 * never produces. The GCS thermal calibration fits drift against those, so
 * without them the wizard samples nothing. */
#define PIOS_INCLUDE_RAW_SENSORS
#define PIOS_INCLUDE_ICM20602
/* WiFi telemetry: active only when credentials exist in NVS (see
 * tools/wifi_setup.py). Bench feature; erase credentials before flight. */
#define PIOS_INCLUDE_WIFI
#define PIOS_MPU6000_ACCEL

/* Deliberately off for a first bring-up: rate mode needs a gyro and nothing
 * else. Turn these on one at a time, with the wiring to match.
 *
 * NOTE on the MPU9250 / GY-91 breakouts: pios_mpu6000.c gates on
 * WHO_AM_I == 0x68 and an MPU9250 answers 0x71, so it will be rejected.
 * That gate is in shared flight code, so widening it is a decision for you,
 * not something this port should do behind your back. A genuine MPU6000 or
 * MPU6050 (0x68) works as-is. */
/* HMC5883L magnetometer on I2C1 (0x1E), next to the baro. Heading is what
 * rotates a NED position error into roll/pitch, so GPS position hold and RTH
 * need this: without it heading is unobservable at a hover and the vehicle
 * drifts or circles. */
#define PIOS_INCLUDE_HMC5X83
/* #define PIOS_INCLUDE_MS5611 */
#define PIOS_INCLUDE_I2C

/* BMP388 barometer on I2C1 (expansion header SDA1/SCL1 = GPIO40/41).
 * Feeds modules/AltFilter, which publishes BaroSensor and runs the altitude
 * Kalman. Without AltFilter compiled in, the driver would register with
 * PIOS_SENSORS and nothing would ever poll it. */
#define PIOS_INCLUDE_BMP388
/* ...and the BMP280, because the two are indistinguishable by I2C address.
 * Which one is fitted is decided at boot from the chip ID, not from a build
 * flag -- see the probe in pios_board.c. */
#define PIOS_INCLUDE_BMP280
/* #define PIOS_INCLUDE_ADC */
/* #define PIOS_INCLUDE_GPS */

/* --- Not available on this target ------------------------------------- */
/* Settings persistence is not wired up yet. On STM32 this is PIOS_FLASHFS
 * over internal flash; the ESP32 equivalent is an NVS namespace and it is
 * the next thing worth building. Until then the board boots to defaults
 * every time and you configure over the GCS link. */
/* #define PIOS_INCLUDE_FLASH */
/* #define PIOS_INCLUDE_FLASH_LOGFS_SETTINGS */
/* #define PIOS_INCLUDE_IAP */
/* #define PIOS_INCLUDE_BL_HELPER */
/* #define PIOS_INCLUDE_SDCARD */
/* #define PIOS_INCLUDE_RTC */

#define PIOS_SENSOR_RATE               250.0f

/* --- Stabilization ---------------------------------------------------- */
#define PIOS_QUATERNION_STABILIZATION

/* --- Alarm thresholds ------------------------------------------------- */
/* Raised well above the STM32 targets': FreeRTOS on IDF reports free heap
 * across a much larger pool, so the 4000/1000 byte thresholds the other
 * boards use would never trip and would tell you nothing. */
#define HEAP_LIMIT_WARNING             16000
#define HEAP_LIMIT_CRITICAL            8000
#define IRQSTACK_LIMIT_WARNING         150
#define IRQSTACK_LIMIT_CRITICAL        80
#define CPULOAD_LIMIT_WARNING          80
#define CPULOAD_LIMIT_CRITICAL         95

#endif /* PIOS_CONFIG_H */
