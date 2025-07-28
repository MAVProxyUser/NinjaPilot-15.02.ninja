/**
 ******************************************************************************
 *
 *
 * @file       UAVObjectsInitialize.java
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @brief      the template for the uavobjects init part
 *             $(GENERATEDWARNING)
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

package org.openpilot.uavtalk.uavobjects;

import org.openpilot.uavtalk.UAVObjectManager;

public class UAVObjectsInitialize {
	
	public static void register(UAVObjectManager objMngr) {
		try {
			objMngr.registerObject( new AccelGyroSettings() );
			objMngr.registerObject( new AccelSensor() );
			objMngr.registerObject( new AccelState() );
			objMngr.registerObject( new AccessoryDesired() );
			objMngr.registerObject( new ActuatorCommand() );
			objMngr.registerObject( new ActuatorDesired() );
			objMngr.registerObject( new ActuatorSettings() );
			objMngr.registerObject( new AirspeedSensor() );
			objMngr.registerObject( new AirspeedSettings() );
			objMngr.registerObject( new AirspeedState() );
			objMngr.registerObject( new AltitudeFilterSettings() );
			objMngr.registerObject( new AltitudeHoldSettings() );
			objMngr.registerObject( new AltitudeHoldStatus() );
			objMngr.registerObject( new AttitudeSettings() );
			objMngr.registerObject( new AttitudeSimulated() );
			objMngr.registerObject( new AttitudeState() );
			objMngr.registerObject( new AuxMagSensor() );
			objMngr.registerObject( new AuxMagSettings() );
			objMngr.registerObject( new BaroSensor() );
			objMngr.registerObject( new CallbackInfo() );
			objMngr.registerObject( new DebugLogControl() );
			objMngr.registerObject( new DebugLogEntry() );
			objMngr.registerObject( new DebugLogSettings() );
			objMngr.registerObject( new DebugLogStatus() );
			objMngr.registerObject( new EKFConfiguration() );
			objMngr.registerObject( new EKFStateVariance() );
			objMngr.registerObject( new FaultSettings() );
			objMngr.registerObject( new FirmwareIAPObj() );
			objMngr.registerObject( new FixedWingPathFollowerSettings() );
			objMngr.registerObject( new FixedWingPathFollowerStatus() );
			objMngr.registerObject( new FlightBatterySettings() );
			objMngr.registerObject( new FlightBatteryState() );
			objMngr.registerObject( new FlightModeSettings() );
			objMngr.registerObject( new FlightPlanControl() );
			objMngr.registerObject( new FlightPlanSettings() );
			objMngr.registerObject( new FlightPlanStatus() );
			objMngr.registerObject( new FlightStatus() );
			objMngr.registerObject( new FlightTelemetryStats() );
			objMngr.registerObject( new GCSReceiver() );
			objMngr.registerObject( new GCSTelemetryStats() );
			objMngr.registerObject( new GPSExtendedStatus() );
			objMngr.registerObject( new GPSPositionSensor() );
			objMngr.registerObject( new GPSSatellites() );
			objMngr.registerObject( new GPSSettings() );
			objMngr.registerObject( new GPSTime() );
			objMngr.registerObject( new GPSVelocitySensor() );
			objMngr.registerObject( new GroundPathFollowerSettings() );
			objMngr.registerObject( new GroundTruth() );
			objMngr.registerObject( new GyroSensor() );
			objMngr.registerObject( new GyroState() );
			objMngr.registerObject( new HomeLocation() );
			objMngr.registerObject( new HwSettings() );
			objMngr.registerObject( new I2CStats() );
			objMngr.registerObject( new MagSensor() );
			objMngr.registerObject( new MagState() );
			objMngr.registerObject( new ManualControlCommand() );
			objMngr.registerObject( new ManualControlSettings() );
			objMngr.registerObject( new MixerSettings() );
			objMngr.registerObject( new MixerStatus() );
			objMngr.registerObject( new Mpu6000Settings() );
			objMngr.registerObject( new NedAccel() );
			objMngr.registerObject( new ObjectPersistence() );
			objMngr.registerObject( new OPLinkReceiver() );
			objMngr.registerObject( new OPLinkSettings() );
			objMngr.registerObject( new OPLinkStatus() );
			objMngr.registerObject( new OsdSettings() );
			objMngr.registerObject( new PathAction() );
			objMngr.registerObject( new PathDesired() );
			objMngr.registerObject( new PathPlan() );
			objMngr.registerObject( new PathStatus() );
			objMngr.registerObject( new PathSummary() );
			objMngr.registerObject( new PerfCounter() );
			objMngr.registerObject( new PIDStatus() );
			objMngr.registerObject( new PoiLearnSettings() );
			objMngr.registerObject( new PoiLocation() );
			objMngr.registerObject( new PositionState() );
			objMngr.registerObject( new RadioComBridgeStats() );
			objMngr.registerObject( new RateDesired() );
			objMngr.registerObject( new ReceiverActivity() );
			objMngr.registerObject( new SonarAltitude() );
			objMngr.registerObject( new StabilizationBank() );
			objMngr.registerObject( new StabilizationDesired() );
			objMngr.registerObject( new StabilizationSettings() );
			objMngr.registerObject( new StabilizationSettingsBank1() );
			objMngr.registerObject( new StabilizationSettingsBank2() );
			objMngr.registerObject( new StabilizationSettingsBank3() );
			objMngr.registerObject( new StabilizationStatus() );
			objMngr.registerObject( new StatusGroundDrive() );
			objMngr.registerObject( new StatusVtolLand() );
			objMngr.registerObject( new SystemAlarms() );
			objMngr.registerObject( new SystemSettings() );
			objMngr.registerObject( new SystemStats() );
			objMngr.registerObject( new TakeOffLocation() );
			objMngr.registerObject( new TaskInfo() );
			objMngr.registerObject( new TxPIDSettings() );
			objMngr.registerObject( new VelocityDesired() );
			objMngr.registerObject( new VelocityState() );
			objMngr.registerObject( new VtolPathFollowerSettings() );
			objMngr.registerObject( new VtolSelfTuningStats() );
			objMngr.registerObject( new WatchdogStatus() );
			objMngr.registerObject( new Waypoint() );
			objMngr.registerObject( new WaypointActive() );
	
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
