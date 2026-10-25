/**
 ******************************************************************************
 *
 * @file       pios_board.h
 * @author     NinjaPilot, 2026
 * @brief      Board definitions for a bare ESP32-WROOM-32E module.
 *
 * Pin assignments follow the esp32buzz reference wiring (a WROOM-32 devkit
 * with a GY-91-style sensor breakout on VSPI), so an existing rig built to
 * that table works here unchanged. See README.md in this directory for the
 * wiring chart.
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

#ifndef PIOS_BOARD_H
#define PIOS_BOARD_H

// ------------------------
// PIOS_LED
// ------------------------
#define PIOS_LED_HEARTBEAT     0
#define PIOS_LED_ALARM         1
#define PIOS_LED_NUM           1

// ------------------------
// PIOS_WDG
// ------------------------
// Kept deliberately generous for bring-up. The IDF Task WDT timeout in
// sdkconfig.defaults must be LONGER than this or the hardware fires before
// the PiOS flag scheme has had a chance to.
#define PIOS_WATCHDOG_TIMEOUT  250

// One bit per participating flight task. PIOS_WDG_Clear() only pets the
// hardware once every registered bit has been set, so a single stalled task
// takes the board down -- see pios/esp32/pios_wdg.c.
// (No PIOS_WDG_REGISTER equivalent: the STM32 targets stash the outstanding
// flags in a backup register across reset; we read the reset reason instead.)
#define PIOS_WDG_ACTUATOR      0x0001
#define PIOS_WDG_STABILIZATION 0x0002
#define PIOS_WDG_ATTITUDE      0x0004
#define PIOS_WDG_MANUAL        0x0008
#define PIOS_WDG_AUTOTUNE      0x0010

// ------------------------
// Sensor sample rate
// ------------------------
// The gyro data-ready rate, and therefore the stabilization inner loop rate.
// CopterControl runs this on a 72MHz Cortex-M3 with software floating point;
// a 240MHz LX6 with a hardware FPU has considerably more headroom, so 500 is
// a starting point and not a ceiling. Raise it once you have measured the
// real loop margin on hardware.
#define PIOS_SENSOR_RATE       500.0f

// ------------------------
// Receiver
// ------------------------
#define PIOS_PPM_MAX_DEVS      1
#define PIOS_RCVR_MAX_CHANNELS 12
/* PPM and DSM can both be built in; ManualControl picks between them by
 * channel group, so both need a receiver slot. */
#define PIOS_RCVR_MAX_DEVS     2

// -------------------------
// PIOS_DSM  (Spektrum satellite on the aux UART)
// -------------------------
// -------------------------
// Settings storage
// -------------------------
/* PIOS_FLASHFS backed by NVS -- see pios/esp32/pios_flashfs_nvs.c. */
#define PIOS_INCLUDE_FLASH

#define PIOS_INCLUDE_DSM
/* A satellite reports 7 channels per frame; 12 covers the two-frame
 * (11ms) modes that interleave channels 8-11. */
#define PIOS_DSM_NUM_INPUTS    12

// ------------------------
// Servo / actuator outputs
// ------------------------
#define PIOS_SERVO_MAX_BANKS   3
#define PIOS_SERVOS_INITIAL_POSITION 0

// ------------------------
// COM
// ------------------------
#define PIOS_COM_MAX_DEVS      3

/* Must hold a whole GCS burst: on connect it requests every object and
 * its metaobject back to back (~150 requests of ~13 bytes in a few
 * chunks). At 192 the fifo overflowed on that burst and the WiFi RX
 * path's backpressure turned into multi-second stalls the GCS read as a
 * dead link -- connect/disconnect looping forever. */
#define PIOS_COM_TELEM_RF_RX_BUF_LEN 2048
#define PIOS_COM_TELEM_RF_TX_BUF_LEN 192

// Telemetry's view of the COM device, and its task sizing. The handle is
// defined in pios_board.c.
extern uint32_t pios_com_telem_rf_id;
#define PIOS_COM_TELEM_RF      (pios_com_telem_rf_id)

#define TELEM_QUEUE_SIZE       20

// ------------------------
// Task stack sizes (BYTES -- the modules divide by 4 for xTaskCreate)
// ------------------------
// These are all several times the CopterControl values, deliberately.
// Xtensa's windowed ABI spills register windows to the stack, and IDF's
// printf/driver calls are far hungrier than the STM32 equivalents, so the
// stock sizes overflow. The failure mode is nasty: instead of a clean
// "stack overflow in task X" the canary is missed and the scheduler's ready
// list is corrupted, surfacing as a LoadProhibited inside
// vTaskSwitchContext with no hint as to which task did it.
//
// There is ~290KB of heap free on this board, so being generous here costs
// nothing worth counting. Trim later using uxTaskGetStackHighWaterMark,
// not by guessing.
#define PIOS_ATTITUDE_STACK_SIZE       4096
#define PIOS_STABILIZATION_STACK_SIZE  4096
#define PIOS_ACTUATOR_STACK_SIZE       4096
#define PIOS_RECEIVER_STACK_SIZE       3072
#define PIOS_MANUAL_STACK_SIZE         3072
#define PIOS_SYSTEM_STACK_SIZE         4096

// NOTE the unit change: eventdispatcher.c passes this to the callback
// scheduler as (STACK_SIZE * 4), so this one is in WORDS, not bytes.
// 1024 words = 4KB. Its fallback is configMINIMAL_STACK_SIZE, which IDF
// sizes for the idle task -- nowhere near enough to walk the UAVObject
// periodic list, and it fails by corrupting mObjList rather than reporting
// an overflow (LoadProhibited in processPeriodicUpdates).
#define PIOS_EVENTDISPATCHER_STACK_SIZE 4096
// Bytes, not words: PiOS passes this to xTaskCreate via the module's own
// stack macro. 624 is what SimPosix uses; the ESP32 needs more headroom
// because IDF's printf and the UART driver sit on the same stack.
#define PIOS_TELEM_STACK_SIZE  8192

// ------------------------
// Task / callback scheduler
// ------------------------
// ESP-IDF supplies FreeRTOSConfig.h from sdkconfig; configMAX_PRIORITIES is
// 25 there, comfortably above the 8 this tree's other targets need.
#define PIOS_INCLUDE_INITCALL

#endif /* PIOS_BOARD_H */
