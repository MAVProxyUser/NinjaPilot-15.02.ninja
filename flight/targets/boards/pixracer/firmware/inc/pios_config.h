/**
 ******************************************************************************
 * @addtogroup OpenPilotSystem OpenPilot System
 * @{
 * @addtogroup OpenPilotCore OpenPilot Core
 * @{
 * @file       pios_config.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010-2013.
 * @brief      PiOS configuration header, the compile time config file for the PIOS.
 *             Defines which PiOS libraries and features are included in the firmware.
 * @see        The GNU Public License (GPL) Version 3
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

/*
 * Below is a complete list of PIOS configurable options.
 * Please do not remove or rearrange them. Only comment out
 * unused options in the list. See main pios.h header for more
 * details.
 */

#define PIOS_INCLUDE_DEBUG_CONSOLE	/* UART7, the debug pads - needs the F427 ST library */
/* #define DEBUG_LEVEL 0 */

/* PIOS FreeRTOS support */
#define PIOS_INCLUDE_FREERTOS

/* Shared System module (systemmod.c) needs these in this tree */
#define PIOS_INCLUDE_CALLBACKSCHEDULER
#define PIOS_INCLUDE_TASK_MONITOR

/* PIOS bootloader helper */
#define PIOS_INCLUDE_BL_HELPER
/* #define PIOS_INCLUDE_BL_HELPER_WRITE_SUPPORT */

/* PIOS system functions */
#define PIOS_INCLUDE_DELAY
#define PIOS_INCLUDE_INITCALL
#define PIOS_INCLUDE_SYS

/* PIOS hardware peripherals */
#define PIOS_INCLUDE_IRQ
#define PIOS_INCLUDE_RTC
#define PIOS_INCLUDE_TIM
#define PIOS_INCLUDE_USART
#define PIOS_INCLUDE_ADC
#define PIOS_INCLUDE_I2C
#define PIOS_INCLUDE_SPI
#define PIOS_INCLUDE_GPIO
#define PIOS_INCLUDE_EXTI
#define PIOS_INCLUDE_WDG

/* PIOS USB functions */
#define PIOS_INCLUDE_USB
#define PIOS_INCLUDE_USB_HID
/*
 * HID only, no CDC.
 *
 * With the composite HID+CDC descriptor macOS matched the two CDC interfaces
 * and never exposed the HID one at all - so the GCS, which talks HID, had
 * nothing to attach to.  Revo ships HID only and that is the configuration the
 * GCS expects.  The debug console moves back to UART7.
 */
/* #define PIOS_INCLUDE_USB_CDC */
/* #define PIOS_INCLUDE_USB_RCTX */

/* PIOS sensor interfaces */
/* #define PIOS_INCLUDE_ADXL345 */
/* #define PIOS_INCLUDE_BMA180 */
/* #define PIOS_INCLUDE_L3GD20 */
/* #define PIOS_INCLUDE_MPU6000 */		/* PixRacer has MPU9250 + ICM-20608-G */
/* MPU9250 and ICM-20608-G, both handled by the shared Invensense driver */
#define PIOS_INCLUDE_INVENSENSE
#define PIOS_MPU6000_ACCEL
/* #define PIOS_INCLUDE_HMC5843 */
/* #define PIOS_INCLUDE_HMC5883 */		/* HMC5983 on SPI1, via the hmc5x83 driver */
#define PIOS_INCLUDE_HMC5X83		/* HMC5983 on SPI1 */
#define PIOS_HMC5883_HAS_GPIOS
/* #define PIOS_INCLUDE_BMP085 */
#define PIOS_INCLUDE_MS5611		/* on SPI2, not I2C - see PIOS_MS5611_SPI_Init */
#define PIOS_INCLUDE_MPXV
#define PIOS_INCLUDE_ETASV3
/* #define PIOS_INCLUDE_HCSR04 */

/* PIOS receiver drivers */
#define PIOS_INCLUDE_PWM
#define PIOS_INCLUDE_PPM
/* #define PIOS_INCLUDE_PPM_FLEXI */
#define PIOS_INCLUDE_DSM
#define PIOS_INCLUDE_SBUS
#define PIOS_INCLUDE_GCSRCVR

/* PIOS abstract receiver interface */
#define PIOS_INCLUDE_RCVR

/* PIOS common peripherals */
#define PIOS_INCLUDE_LED
#define PIOS_INCLUDE_IAP
#define PIOS_INCLUDE_SERVO
/* #define PIOS_INCLUDE_I2C_ESC */
/* #define PIOS_INCLUDE_OVERO */
/* #define PIOS_OVERO_SPI */
/* #define PIOS_INCLUDE_SDCARD */
/* #define LOG_FILENAME "startup.log" */
#define PIOS_INCLUDE_FLASH
/* PixRacer has no SPI NOR part - settings live in internal flash.
 * The FM25V02 FRAM on SPI2 is a future home for them. */
#define PIOS_INCLUDE_FLASH_INTERNAL
#define PIOS_INCLUDE_FLASH_SECTOR_SETTINGS
#define FLASH_FREERTOS
/* #define PIOS_INCLUDE_FLASH_EEPROM */

/* PIOS radio modules */
/* No RFM22B radio on PixRacer */
/* #define PIOS_INCLUDE_RFM22B */
/* #define PIOS_INCLUDE_RFM22B_COM */
/* #define PIOS_INCLUDE_RFM22B_RCVR */
/* #define PIOS_INCLUDE_PPM_OUT */
/* #define PIOS_RFM22B_DEBUG_ON_TELEM */

/* PIOS misc peripherals */
/* #define PIOS_INCLUDE_VIDEO */
/* #define PIOS_INCLUDE_WAVE */
/* #define PIOS_INCLUDE_UDP */

/* PIOS abstract comms interface with options */
#define PIOS_INCLUDE_COM
/* #define PIOS_INCLUDE_COM_MSG */
/* #define PIOS_INCLUDE_TELEMETRY_RF */
#define PIOS_INCLUDE_COM_TELEM
/* #define PIOS_INCLUDE_COM_FLEXI */	/* no flexi port on PixRacer */
#define PIOS_INCLUDE_COM_AUX		/* USART1, the ESP8266 header */
#define PIOS_TELEM_PRIORITY_QUEUE
#define PIOS_INCLUDE_GPS
/* #define PIOS_GPS_MINIMAL */
#define PIOS_INCLUDE_GPS_NMEA_PARSER
#define PIOS_INCLUDE_GPS_UBX_PARSER
#define PIOS_GPS_SETS_HOMELOCATION

/* Stabilization options */
/* #define PIOS_QUATERNION_STABILIZATION */

/* Performance counters */
#define IDLE_COUNTS_PER_SEC_AT_NO_LOAD	8379692

/* Alarm Thresholds */
#define HEAP_LIMIT_WARNING		1000
#define HEAP_LIMIT_CRITICAL		500
#define IRQSTACK_LIMIT_WARNING		150
#define IRQSTACK_LIMIT_CRITICAL		80
#define CPULOAD_LIMIT_WARNING		80
#define CPULOAD_LIMIT_CRITICAL		95

/* Task stack sizes */
/* #define PIOS_ACTUATOR_STACK_SIZE	1020 */
/* #define PIOS_MANUAL_STACK_SIZE		800 */
/* #define PIOS_SYSTEM_STACK_SIZE		660 */
/* #define PIOS_STABILIZATION_STACK_SIZE	524 */
/* #define PIOS_TELEM_STACK_SIZE		500 */
/* #define PIOS_EVENTDISPATCHER_STACK_SIZE	130 */

/* This can't be too high to stop eventdispatcher thread overflowing */
#define PIOS_EVENTDISAPTCHER_QUEUE	10

/* Revolution series */
#define REVOLUTION

#endif /* PIOS_CONFIG_H */

/**
 * @}
 * @}
 */
