#####
# Project: OpenPilot
#
# Makefile for OpenPilot UAVObject code
#
# The OpenPilot Team, http://www.openpilot.org, Copyright (C) 2011.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#####

# These are the UAVObjects supposed to be build as part of the OpenPilot target
# (all architectures)

UAVOBJSRCFILENAMES =
UAVOBJSRCFILENAMES += statusgrounddrive
UAVOBJSRCFILENAMES += pidstatus
UAVOBJSRCFILENAMES += statusvtolland
UAVOBJSRCFILENAMES += vtolselftuningstats
UAVOBJSRCFILENAMES += accessorydesired
UAVOBJSRCFILENAMES += actuatorcommand
UAVOBJSRCFILENAMES += actuatordesired
UAVOBJSRCFILENAMES += actuatorsettings
UAVOBJSRCFILENAMES += attitudesettings
UAVOBJSRCFILENAMES += attitudestate
UAVOBJSRCFILENAMES += attitudesimulated
UAVOBJSRCFILENAMES += gyrostate
UAVOBJSRCFILENAMES += gyrosensor
UAVOBJSRCFILENAMES += accelstate
UAVOBJSRCFILENAMES += accelsensor
UAVOBJSRCFILENAMES += accelgyrosettings
UAVOBJSRCFILENAMES += magsensor
UAVOBJSRCFILENAMES += auxmagsensor
UAVOBJSRCFILENAMES += auxmagsettings
UAVOBJSRCFILENAMES += magstate
UAVOBJSRCFILENAMES += barosensor
UAVOBJSRCFILENAMES += airspeedsensor
UAVOBJSRCFILENAMES += airspeedsettings
UAVOBJSRCFILENAMES += airspeedstate
UAVOBJSRCFILENAMES += debuglogsettings
UAVOBJSRCFILENAMES += debuglogcontrol
UAVOBJSRCFILENAMES += debuglogstatus
UAVOBJSRCFILENAMES += debuglogentry
UAVOBJSRCFILENAMES += firmwareiapobj
UAVOBJSRCFILENAMES += flightbatterystate
UAVOBJSRCFILENAMES += flighttelemetrystats
UAVOBJSRCFILENAMES += gcstelemetrystats
UAVOBJSRCFILENAMES += gcsreceiver
UAVOBJSRCFILENAMES += gpspositionsensor
UAVOBJSRCFILENAMES += gpssatellites
UAVOBJSRCFILENAMES += gpstime
UAVOBJSRCFILENAMES += gpsvelocitysensor
UAVOBJSRCFILENAMES += gpsextendedstatus
UAVOBJSRCFILENAMES += gpssettings
UAVOBJSRCFILENAMES += vtolpathfollowersettings
UAVOBJSRCFILENAMES += groundpathfollowersettings
UAVOBJSRCFILENAMES += fixedwingpathfollowersettings
UAVOBJSRCFILENAMES += fixedwingpathfollowerstatus
UAVOBJSRCFILENAMES += homelocation
UAVOBJSRCFILENAMES += i2cstats
UAVOBJSRCFILENAMES += manualcontrolcommand
UAVOBJSRCFILENAMES += manualcontrolsettings
UAVOBJSRCFILENAMES += flightmodesettings
UAVOBJSRCFILENAMES += mixersettings
UAVOBJSRCFILENAMES += mixerstatus
UAVOBJSRCFILENAMES += objectpersistence
UAVOBJSRCFILENAMES += oplinkstatus
UAVOBJSRCFILENAMES += pathaction
UAVOBJSRCFILENAMES += pathdesired
UAVOBJSRCFILENAMES += pathplan
UAVOBJSRCFILENAMES += missionprogress
UAVOBJSRCFILENAMES += missionrecoverysettings
UAVOBJSRCFILENAMES += pathstatus
UAVOBJSRCFILENAMES += pathsummary
UAVOBJSRCFILENAMES += positionstate
UAVOBJSRCFILENAMES += ratedesired
UAVOBJSRCFILENAMES += relaytuning
UAVOBJSRCFILENAMES += relaytuningsettings
UAVOBJSRCFILENAMES += revocalibration
UAVOBJSRCFILENAMES += revosettings
UAVOBJSRCFILENAMES += stabilizationdesired
UAVOBJSRCFILENAMES += stabilizationsettings
UAVOBJSRCFILENAMES += stabilizationsettingsbank1
UAVOBJSRCFILENAMES += stabilizationsettingsbank2
UAVOBJSRCFILENAMES += stabilizationsettingsbank3
UAVOBJSRCFILENAMES += stabilizationstatus
UAVOBJSRCFILENAMES += stabilizationbank
UAVOBJSRCFILENAMES += systemalarms
UAVOBJSRCFILENAMES += systemsettings
UAVOBJSRCFILENAMES += systemstats
UAVOBJSRCFILENAMES += taskinfo
UAVOBJSRCFILENAMES += callbackinfo
UAVOBJSRCFILENAMES += velocitystate
UAVOBJSRCFILENAMES += velocitydesired
UAVOBJSRCFILENAMES += watchdogstatus
UAVOBJSRCFILENAMES += waypoint
UAVOBJSRCFILENAMES += waypointactive
UAVOBJSRCFILENAMES += poilocation
UAVOBJSRCFILENAMES += flightstatus
UAVOBJSRCFILENAMES += hwsettings
UAVOBJSRCFILENAMES += receiveractivity
UAVOBJSRCFILENAMES += altitudeholdsettings
UAVOBJSRCFILENAMES += altitudefiltersettings
UAVOBJSRCFILENAMES += altitudeholdstatus
UAVOBJSRCFILENAMES += ekfconfiguration
UAVOBJSRCFILENAMES += ekfstatevariance
UAVOBJSRCFILENAMES += takeofflocation

UAVOBJSRC = $(foreach UAVOBJSRCFILE,$(UAVOBJSRCFILENAMES),$(UAVOBJSYNTHDIR)/$(UAVOBJSRCFILE).c )
UAVOBJDEFINE = $(foreach UAVOBJSRCFILE,$(UAVOBJSRCFILENAMES),-DUAVOBJ_INIT_$(UAVOBJSRCFILE) )
