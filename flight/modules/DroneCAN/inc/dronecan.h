/**
 ******************************************************************************
 * @addtogroup OpenPilotModules OpenPilot Modules
 * @{
 * @addtogroup DroneCANModule DroneCAN Module
 * @brief Listens on the CAN bus, serves dynamic node-id allocation, announces
 *        the flight controller as a node and publishes what it hears.
 * @{
 *
 * @file       dronecan.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2026.
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

#ifndef DRONECAN_H
#define DRONECAN_H

int32_t DroneCANInitialize(void);
int32_t DroneCANStart(void);

/* Actuator output: the actuator module hands over every channel whose
 * ActuatorSettings ChannelType is DroneCAN (index = ChannelAddr, raw
 * 0..8191) and flushes once per update; one esc.RawCommand goes out. */
void DroneCANESCSet(uint8_t index, int16_t raw);
void DroneCANESCFlush(void);

#endif /* DRONECAN_H */
