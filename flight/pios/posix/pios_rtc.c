/**
 ******************************************************************************
 *
 * @file       pios_rtc.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @brief      RTC functions, posix host has no real RTC peripheral so this
 *             is built on the same wall-clock source as PIOS_DELAY.
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

#include "pios.h"

uint32_t PIOS_RTC_Counter()
{
    return PIOS_DELAY_GetuS();
}

float PIOS_RTC_Rate()
{
    return 1.0e6f; /* PIOS_DELAY_GetuS() ticks once per microsecond */
}

float PIOS_RTC_MsPerTick()
{
    return 1.0e3f / PIOS_RTC_Rate();
}

/**
 * There's no periodic RTC tick to drive registered callbacks from on posix.
 * Nothing currently relies on being ticked (only PIOS_GCSRCVR's channel
 * staleness supervisor registers one, and holding the last commanded value
 * forever is the behavior we want for a SITL virtual receiver anyway), so
 * this just accepts the registration and never fires it.
 */
bool PIOS_RTC_RegisterTickCallback(__attribute__((unused)) void (*fn)(uint32_t id), __attribute__((unused)) uint32_t data)
{
    return true;
}
