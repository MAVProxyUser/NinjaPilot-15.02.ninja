/**
 ******************************************************************************
 * @addtogroup OpenPilotSystem OpenPilot System
 * @{
 * @addtogroup OpenPilotCore OpenPilot Core
 * @{
 *
 * @file       board_hw_defs.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @brief      Defines board specific static initializers for hardware for the OpenPilot board.
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

#ifdef PIOS_INCLUDE_UDP

#include <pios_udp_priv.h>

#ifdef PIOS_INCLUDE_COM_TELEM
/*
 * Telemetry on main USART
 */
const struct pios_udp_cfg pios_udp_telem_cfg = {
    .ip   = "0.0.0.0",
    .port = 9000,
};
#endif /* PIOS_COM_TELEM */

#ifdef PIOS_INCLUDE_GPS
/*
 * GPS USART
 */
const struct pios_udp_cfg pios_udp_gps_cfg = {
    .ip   = "0.0.0.0",
    .port = 9001,
};

#endif /* PIOS_INCLUDE_GPS */

#ifdef PIOS_INCLUDE_COM_AUX
/*
 * AUX USART (UART label on rev2)
 */
const struct pios_udp_cfg pios_udp_aux_cfg = {
    .ip   = "0.0.0.0",
    .port = 9002,
};
#endif /* PIOS_COM_AUX */

#endif /* PIOS_UDP */

#if defined(PIOS_INCLUDE_COM)

#include <pios_com_priv.h>

#endif /* PIOS_INCLUDE_COM */

#if defined(PIOS_INCLUDE_FLASH)
#include "pios_flashfs_logfs_priv.h"
#endif

#if defined(PIOS_INCLUDE_GCSRCVR)
#include "pios_gcsrcvr_priv.h"
#endif /* PIOS_INCLUDE_GCSRCVR */

#if defined(PIOS_INCLUDE_RCVR)
#include "pios_rcvr_priv.h"
#endif /* PIOS_INCLUDE_RCVR */

/* ---------------------------------------------------------------------------
 * LiteWing V2.6.C pin map -- transcribed from the KiCad schematic
 * (jobitjoseph/LiteWing, hardware/LieWingV2.6.C). Nothing on this posix twin
 * reads these: they are here so the hardware port inherits a map that came
 * from the schematic rather than from guesswork.
 *
 * SoC: ESP32-S3-WROOM-1 (U8). Dual-core LX7, so the core-isolation split this
 * codebase depends on -- flight tasks on core 1, WiFi/lwIP on core 0 --
 * survives. That is the reason an S3 is portable and an S2 is not.
 *
 *   Motors (low-side IRLML6344 N-FET gates, PWM duty NOT servo pulses)
 *     MOT_1  GPIO5      MOT_2  GPIO6      MOT_3  GPIO3      MOT_4  GPIO4
 *
 *   IMU: MPU6050 on I2C0        SCL GPIO10   SDA GPIO11   INT GPIO12
 *   Battery sense               ADC_BAT GPIO2
 *   LEDs                        BLUE GPIO7   RED GPIO8    GREEN GPIO9
 *   Buzzer                      BUZ1 GPIO38  BUZ2 GPIO39
 *   Aux I2C1 (VL53L1X ToF)      SDA1 GPIO40  SCL1 GPIO41
 *   Optical flow (PMW3901, SPI) MOSI GPIO35  CLK GPIO36  MISO GPIO37  CS GPIO42
 *   UART0 (CH340K bridge)       TXD0 / RXD0
 *   Boot / enable               GPIO0, EN
 *
 * TRAPS, both load-bearing:
 *
 * 1. GPIO35/36/37 are the octal-PSRAM pins on ESP32-S3-WROOM-1 variants that
 *    carry PSRAM (the schematic brackets them "PSRAM" for exactly this
 *    reason) and this board uses them for the optical-flow SPI. A module with
 *    octal PSRAM therefore CANNOT drive that sensor. Confirm the module
 *    suffix before wiring flow, and do not enable PSRAM in sdkconfig.
 *
 * 2. WHICH PHYSICAL CORNER IS MOT_1 IS NOT KNOWN FROM THE SCHEMATIC. The
 *    netlist gives gate-to-GPIO only; the corner assignment lives on the PCB
 *    silkscreen. The mixer below therefore uses the stock OpenPilot QuadX
 *    convention (1 NW, 2 NE, 3 SE, 4 SW) as a PLACEHOLDER. Verify it against
 *    the board before anything spins: an IMU or motor-order frame that
 *    disagrees with the mixer is positive feedback on both axes, and it is
 *    what flipped the ESP32 quad twice on 2026-09-01.
 * ------------------------------------------------------------------------- */
