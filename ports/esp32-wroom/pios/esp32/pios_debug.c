/**
 ******************************************************************************
 * @file       pios_debug.c
 * @author     NinjaPilot, 2026
 * @brief      ESP32 debug/panic support.
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

#include "pios.h"

const char *PIOS_DEBUG_AssertMsg = "ASSERT FAILED";

void PIOS_DEBUG_Init(void)
{
    /* Debug pins are not wired on this target. */
}

void PIOS_DEBUG_PinHigh(__attribute__((unused)) uint8_t pin)
{}

void PIOS_DEBUG_PinLow(__attribute__((unused)) uint8_t pin)
{}

void PIOS_DEBUG_PinValue8Bit(__attribute__((unused)) uint8_t value)
{}

void PIOS_DEBUG_PinValue4BitL(__attribute__((unused)) uint8_t value)
{}

/**
 * Halt on an unrecoverable error.
 *
 * Deliberately NOT an infinite loop the way the STM32 backends do it. On
 * ESP32 we want the panic to reach the console and then let the watchdog
 * reset the part -- a silently wedged flight controller is worse than one
 * that reboots and says why. abort() gives us the IDF panic handler, which
 * prints a backtrace and (if enabled in sdkconfig) writes a core dump to
 * the coredump partition.
 */
void PIOS_DEBUG_Panic(const char *msg)
{
    printf("\n[PIOS] PANIC: %s\n", msg ? msg : "(no message)");
    fflush(stdout);

    abort();
}
