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
/* #define PIOS_INCLUDE_HMC5X83 */
/* #define PIOS_INCLUDE_MS5611 */
/* #define PIOS_INCLUDE_I2C */
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

#define PIOS_SENSOR_RATE               500.0f

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
