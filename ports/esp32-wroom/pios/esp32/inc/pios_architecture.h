/**
 ******************************************************************************
 *
 * @file       pios_architecture.h
 * @author     NinjaPilot, 2026
 * @brief      Architecture specific macros and definitions for ESP32.
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

#ifndef PIOS_ARCHITECTURE_H
#define PIOS_ARCHITECTURE_H

/* ESP32 SAR ADC is 12-bit. With 11dB attenuation the usable full-scale is
 * nominally ~3.1V (not 3.3V), and the transfer function is noticeably
 * non-linear -- IDF's esp_adc_cal/adc_cali eFuse calibration exists for
 * exactly this reason. Treat this scale as a placeholder: anything doing
 * real battery telemetry should go through adc_cali_raw_to_voltage()
 * rather than multiplying by a constant.
 *
 * NOTE (WROOM-32): ADC2 is unusable while WiFi is active. Keep every
 * analog input on ADC1 (GPIO32-39). */
#define PIOS_ADC_VOLTAGE_SCALE           (3.10f / 4096.0f)

/* The ESP32 has an internal temperature sensor but it is not exposed the
 * way the STM32's is (and on the original ESP32 it is famously unusable
 * once WiFi is running). No CPU-temp conversion is offered. */
#define PIOS_CONVERT_VOLT_TO_CPU_TEMP(x) (0.0f)

#endif /* PIOS_ARCHITECTURE_H */
