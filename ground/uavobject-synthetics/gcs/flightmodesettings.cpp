/**
 ******************************************************************************
 *
 * @file       flightmodesettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: flightmodesettings.xml.
 *             This is an automatically generated file.
 *             DO NOT modify manually.
 *
 * @brief      The UAVUObjects GCS plugin
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

#include "flightmodesettings.h"
#include "uavobjectfield.h"

const QString FlightModeSettings::NAME = QString("FlightModeSettings");
const QString FlightModeSettings::DESCRIPTION = QString("Settings to control arming and flight mode");
const QString FlightModeSettings::CATEGORY = QString("Control");

/**
 * Constructor
 */
FlightModeSettings::FlightModeSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList ReturnToBaseAltitudeOffsetElemNames;
    ReturnToBaseAltitudeOffsetElemNames.append("0");
    fields.append( new UAVObjectField(QString("ReturnToBaseAltitudeOffset"), tr(""), QString("m"), UAVObjectField::FLOAT32, ReturnToBaseAltitudeOffsetElemNames, QStringList(), QString("")));
    QStringList LandingVelocityElemNames;
    LandingVelocityElemNames.append("0");
    fields.append( new UAVObjectField(QString("LandingVelocity"), tr(""), QString("m"), UAVObjectField::FLOAT32, LandingVelocityElemNames, QStringList(), QString("")));
    QStringList PositionHoldOffsetElemNames;
    PositionHoldOffsetElemNames.append("Horizontal");
    PositionHoldOffsetElemNames.append("Vertical");
    fields.append( new UAVObjectField(QString("PositionHoldOffset"), tr("stick sensitivity for position roam modes"), QString("m"), UAVObjectField::FLOAT32, PositionHoldOffsetElemNames, QStringList(), QString("")));
    QStringList VarioControlLowPassAlphaElemNames;
    VarioControlLowPassAlphaElemNames.append("0");
    fields.append( new UAVObjectField(QString("VarioControlLowPassAlpha"), tr("stick low pass filter for position roam modes"), QString(""), UAVObjectField::FLOAT32, VarioControlLowPassAlphaElemNames, QStringList(), QString("")));
    QStringList ArmedTimeoutElemNames;
    ArmedTimeoutElemNames.append("0");
    fields.append( new UAVObjectField(QString("ArmedTimeout"), tr(""), QString("ms"), UAVObjectField::UINT16, ArmedTimeoutElemNames, QStringList(), QString("")));
    QStringList ArmingSequenceTimeElemNames;
    ArmingSequenceTimeElemNames.append("0");
    fields.append( new UAVObjectField(QString("ArmingSequenceTime"), tr(""), QString("ms"), UAVObjectField::UINT16, ArmingSequenceTimeElemNames, QStringList(), QString("")));
    QStringList DisarmingSequenceTimeElemNames;
    DisarmingSequenceTimeElemNames.append("0");
    fields.append( new UAVObjectField(QString("DisarmingSequenceTime"), tr(""), QString("ms"), UAVObjectField::UINT16, DisarmingSequenceTimeElemNames, QStringList(), QString("")));
    QStringList ArmingElemNames;
    ArmingElemNames.append("0");
    QStringList ArmingEnumOptions;
    ArmingEnumOptions.append("Always Disarmed");
    ArmingEnumOptions.append("Always Armed");
    ArmingEnumOptions.append("Roll Left");
    ArmingEnumOptions.append("Roll Right");
    ArmingEnumOptions.append("Pitch Forward");
    ArmingEnumOptions.append("Pitch Aft");
    ArmingEnumOptions.append("Yaw Left");
    ArmingEnumOptions.append("Yaw Right");
    ArmingEnumOptions.append("Accessory 0");
    ArmingEnumOptions.append("Accessory 1");
    ArmingEnumOptions.append("Accessory 2");
    fields.append( new UAVObjectField(QString("Arming"), tr(""), QString(""), UAVObjectField::ENUM, ArmingElemNames, ArmingEnumOptions, QString("")));
    QStringList Stabilization1SettingsElemNames;
    Stabilization1SettingsElemNames.append("Roll");
    Stabilization1SettingsElemNames.append("Pitch");
    Stabilization1SettingsElemNames.append("Yaw");
    Stabilization1SettingsElemNames.append("Thrust");
    QStringList Stabilization1SettingsEnumOptions;
    Stabilization1SettingsEnumOptions.append("Manual");
    Stabilization1SettingsEnumOptions.append("Rate");
    Stabilization1SettingsEnumOptions.append("Attitude");
    Stabilization1SettingsEnumOptions.append("AxisLock");
    Stabilization1SettingsEnumOptions.append("WeakLeveling");
    Stabilization1SettingsEnumOptions.append("VirtualBar");
    Stabilization1SettingsEnumOptions.append("Acro+");
    Stabilization1SettingsEnumOptions.append("Rattitude");
    Stabilization1SettingsEnumOptions.append("AltitudeHold");
    Stabilization1SettingsEnumOptions.append("AltitudeVario");
    Stabilization1SettingsEnumOptions.append("CruiseControl");
    fields.append( new UAVObjectField(QString("Stabilization1Settings"), tr(""), QString(""), UAVObjectField::ENUM, Stabilization1SettingsElemNames, Stabilization1SettingsEnumOptions, QString("%NE:AltitudeHold:AltitudeVario:CruiseControl; \
			%NE:AltitudeHold:AltitudeVario:CruiseControl; \
			%NE:AltitudeHold:AltitudeVario:CruiseControl:Attitude:Rattitude:Acro+:WeakLeveling:VirtualBar; \
			%NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude,\
			%0401NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude:AltitudeHold:AltitudeVario,\
			%0402NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude:AltitudeHold:AltitudeVario;")));
    QStringList Stabilization2SettingsElemNames;
    Stabilization2SettingsElemNames.append("Roll");
    Stabilization2SettingsElemNames.append("Pitch");
    Stabilization2SettingsElemNames.append("Yaw");
    Stabilization2SettingsElemNames.append("Thrust");
    QStringList Stabilization2SettingsEnumOptions;
    Stabilization2SettingsEnumOptions.append("Manual");
    Stabilization2SettingsEnumOptions.append("Rate");
    Stabilization2SettingsEnumOptions.append("Attitude");
    Stabilization2SettingsEnumOptions.append("AxisLock");
    Stabilization2SettingsEnumOptions.append("WeakLeveling");
    Stabilization2SettingsEnumOptions.append("VirtualBar");
    Stabilization2SettingsEnumOptions.append("Acro+");
    Stabilization2SettingsEnumOptions.append("Rattitude");
    Stabilization2SettingsEnumOptions.append("AltitudeHold");
    Stabilization2SettingsEnumOptions.append("AltitudeVario");
    Stabilization2SettingsEnumOptions.append("CruiseControl");
    fields.append( new UAVObjectField(QString("Stabilization2Settings"), tr(""), QString(""), UAVObjectField::ENUM, Stabilization2SettingsElemNames, Stabilization2SettingsEnumOptions, QString("%NE:AltitudeHold:AltitudeVario:CruiseControl; \
			%NE:AltitudeHold:AltitudeVario:CruiseControl; \
			%NE:AltitudeHold:AltitudeVario:CruiseControl:Attitude:Rattitude:Acro+:WeakLeveling:VirtualBar; \
			%NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude,\
			%0401NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude:AltitudeHold:AltitudeVario,\
			%0402NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude:AltitudeHold:AltitudeVario;")));
    QStringList Stabilization3SettingsElemNames;
    Stabilization3SettingsElemNames.append("Roll");
    Stabilization3SettingsElemNames.append("Pitch");
    Stabilization3SettingsElemNames.append("Yaw");
    Stabilization3SettingsElemNames.append("Thrust");
    QStringList Stabilization3SettingsEnumOptions;
    Stabilization3SettingsEnumOptions.append("Manual");
    Stabilization3SettingsEnumOptions.append("Rate");
    Stabilization3SettingsEnumOptions.append("Attitude");
    Stabilization3SettingsEnumOptions.append("AxisLock");
    Stabilization3SettingsEnumOptions.append("WeakLeveling");
    Stabilization3SettingsEnumOptions.append("VirtualBar");
    Stabilization3SettingsEnumOptions.append("Acro+");
    Stabilization3SettingsEnumOptions.append("Rattitude");
    Stabilization3SettingsEnumOptions.append("AltitudeHold");
    Stabilization3SettingsEnumOptions.append("AltitudeVario");
    Stabilization3SettingsEnumOptions.append("CruiseControl");
    fields.append( new UAVObjectField(QString("Stabilization3Settings"), tr(""), QString(""), UAVObjectField::ENUM, Stabilization3SettingsElemNames, Stabilization3SettingsEnumOptions, QString("%NE:AltitudeHold:AltitudeVario:CruiseControl; \
			%NE:AltitudeHold:AltitudeVario:CruiseControl; \
			%NE:AltitudeHold:AltitudeVario:CruiseControl:Attitude:Rattitude:Acro+:WeakLeveling:VirtualBar; \
			%NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude,\
			%0401NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude:AltitudeHold:AltitudeVario,\
			%0402NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude:AltitudeHold:AltitudeVario;")));
    QStringList Stabilization4SettingsElemNames;
    Stabilization4SettingsElemNames.append("Roll");
    Stabilization4SettingsElemNames.append("Pitch");
    Stabilization4SettingsElemNames.append("Yaw");
    Stabilization4SettingsElemNames.append("Thrust");
    QStringList Stabilization4SettingsEnumOptions;
    Stabilization4SettingsEnumOptions.append("Manual");
    Stabilization4SettingsEnumOptions.append("Rate");
    Stabilization4SettingsEnumOptions.append("Attitude");
    Stabilization4SettingsEnumOptions.append("AxisLock");
    Stabilization4SettingsEnumOptions.append("WeakLeveling");
    Stabilization4SettingsEnumOptions.append("VirtualBar");
    Stabilization4SettingsEnumOptions.append("Acro+");
    Stabilization4SettingsEnumOptions.append("Rattitude");
    Stabilization4SettingsEnumOptions.append("AltitudeHold");
    Stabilization4SettingsEnumOptions.append("AltitudeVario");
    Stabilization4SettingsEnumOptions.append("CruiseControl");
    fields.append( new UAVObjectField(QString("Stabilization4Settings"), tr(""), QString(""), UAVObjectField::ENUM, Stabilization4SettingsElemNames, Stabilization4SettingsEnumOptions, QString("%NE:AltitudeHold:AltitudeVario:CruiseControl; \
			%NE:AltitudeHold:AltitudeVario:CruiseControl; \
			%NE:AltitudeHold:AltitudeVario:CruiseControl:Attitude:Rattitude:Acro+:WeakLeveling:VirtualBar; \
			%NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude,\
			%0401NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude:AltitudeHold:AltitudeVario,\
			%0402NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude:AltitudeHold:AltitudeVario;")));
    QStringList Stabilization5SettingsElemNames;
    Stabilization5SettingsElemNames.append("Roll");
    Stabilization5SettingsElemNames.append("Pitch");
    Stabilization5SettingsElemNames.append("Yaw");
    Stabilization5SettingsElemNames.append("Thrust");
    QStringList Stabilization5SettingsEnumOptions;
    Stabilization5SettingsEnumOptions.append("Manual");
    Stabilization5SettingsEnumOptions.append("Rate");
    Stabilization5SettingsEnumOptions.append("Attitude");
    Stabilization5SettingsEnumOptions.append("AxisLock");
    Stabilization5SettingsEnumOptions.append("WeakLeveling");
    Stabilization5SettingsEnumOptions.append("VirtualBar");
    Stabilization5SettingsEnumOptions.append("Acro+");
    Stabilization5SettingsEnumOptions.append("Rattitude");
    Stabilization5SettingsEnumOptions.append("AltitudeHold");
    Stabilization5SettingsEnumOptions.append("AltitudeVario");
    Stabilization5SettingsEnumOptions.append("CruiseControl");
    fields.append( new UAVObjectField(QString("Stabilization5Settings"), tr(""), QString(""), UAVObjectField::ENUM, Stabilization5SettingsElemNames, Stabilization5SettingsEnumOptions, QString("%NE:AltitudeHold:AltitudeVario:CruiseControl; \
			%NE:AltitudeHold:AltitudeVario:CruiseControl; \
			%NE:AltitudeHold:AltitudeVario:CruiseControl:Attitude:Rattitude:Acro+:WeakLeveling:VirtualBar; \
			%NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude,\
			%0401NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude:AltitudeHold:AltitudeVario,\
			%0402NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude:AltitudeHold:AltitudeVario;")));
    QStringList Stabilization6SettingsElemNames;
    Stabilization6SettingsElemNames.append("Roll");
    Stabilization6SettingsElemNames.append("Pitch");
    Stabilization6SettingsElemNames.append("Yaw");
    Stabilization6SettingsElemNames.append("Thrust");
    QStringList Stabilization6SettingsEnumOptions;
    Stabilization6SettingsEnumOptions.append("Manual");
    Stabilization6SettingsEnumOptions.append("Rate");
    Stabilization6SettingsEnumOptions.append("Attitude");
    Stabilization6SettingsEnumOptions.append("AxisLock");
    Stabilization6SettingsEnumOptions.append("WeakLeveling");
    Stabilization6SettingsEnumOptions.append("VirtualBar");
    Stabilization6SettingsEnumOptions.append("Acro+");
    Stabilization6SettingsEnumOptions.append("Rattitude");
    Stabilization6SettingsEnumOptions.append("AltitudeHold");
    Stabilization6SettingsEnumOptions.append("AltitudeVario");
    Stabilization6SettingsEnumOptions.append("CruiseControl");
    fields.append( new UAVObjectField(QString("Stabilization6Settings"), tr(""), QString(""), UAVObjectField::ENUM, Stabilization6SettingsElemNames, Stabilization6SettingsEnumOptions, QString("%NE:AltitudeHold:AltitudeVario:CruiseControl; \
			%NE:AltitudeHold:AltitudeVario:CruiseControl; \
			%NE:AltitudeHold:AltitudeVario:CruiseControl:Attitude:Rattitude:Acro+:WeakLeveling:VirtualBar; \
			%NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude,\
			%0401NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude:AltitudeHold:AltitudeVario,\
			%0402NE:Rate:Attitude:AxisLock:WeakLeveling:VirtualBar:Acro+:Rattitude:AltitudeHold:AltitudeVario;")));
    QStringList FlightModePositionElemNames;
    FlightModePositionElemNames.append("0");
    FlightModePositionElemNames.append("1");
    FlightModePositionElemNames.append("2");
    FlightModePositionElemNames.append("3");
    FlightModePositionElemNames.append("4");
    FlightModePositionElemNames.append("5");
    QStringList FlightModePositionEnumOptions;
    FlightModePositionEnumOptions.append("Manual");
    FlightModePositionEnumOptions.append("Stabilized1");
    FlightModePositionEnumOptions.append("Stabilized2");
    FlightModePositionEnumOptions.append("Stabilized3");
    FlightModePositionEnumOptions.append("Stabilized4");
    FlightModePositionEnumOptions.append("Stabilized5");
    FlightModePositionEnumOptions.append("Stabilized6");
    FlightModePositionEnumOptions.append("PositionHold");
    FlightModePositionEnumOptions.append("CourseLock");
    FlightModePositionEnumOptions.append("PositionRoam");
    FlightModePositionEnumOptions.append("HomeLeash");
    FlightModePositionEnumOptions.append("AbsolutePosition");
    FlightModePositionEnumOptions.append("ReturnToBase");
    FlightModePositionEnumOptions.append("Land");
    FlightModePositionEnumOptions.append("PathPlanner");
    FlightModePositionEnumOptions.append("POI");
    FlightModePositionEnumOptions.append("AutoCruise");
    fields.append( new UAVObjectField(QString("FlightModePosition"), tr(""), QString(""), UAVObjectField::ENUM, FlightModePositionElemNames, FlightModePositionEnumOptions, QString("\
                       %0401NE:PositionHold:CourseLock:PositionRoam:HomeLeash:AbsolutePosition:ReturnToBase:Land:PathPlanner:POI:AutoCruise,\
                       %0402NE:PositionHold:CourseLock:PositionRoam:HomeLeash:AbsolutePosition:ReturnToBase:Land:PathPlanner:POI:AutoCruise,\
                       %0903NE:POI:PathPlanner:AutoCruise;\
                       \
                       %0401NE:PositionHold:CourseLock:PositionRoam:HomeLeash:AbsolutePosition:ReturnToBase:Land:PathPlanner:POI:AutoCruise,\
                       %0402NE:PositionHold:CourseLock:PositionRoam:HomeLeash:AbsolutePosition:ReturnToBase:Land:PathPlanner:POI:AutoCruise,\
                       %0903NE:POI:PathPlanner:AutoCruise;\
                       \
                       %0401NE:PositionHold:CourseLock:PositionRoam:HomeLeash:AbsolutePosition:ReturnToBase:Land:PathPlanner:POI:AutoCruise,\
                       %0402NE:PositionHold:CourseLock:PositionRoam:HomeLeash:AbsolutePosition:ReturnToBase:Land:PathPlanner:POI:AutoCruise,\
                       %0903NE:POI:PathPlanner:AutoCruise;\
                       \
                       %0401NE:PositionHold:CourseLock:PositionRoam:HomeLeash:AbsolutePosition:ReturnToBase:Land:PathPlanner:POI:AutoCruise,\
                       %0402NE:PositionHold:CourseLock:PositionRoam:HomeLeash:AbsolutePosition:ReturnToBase:Land:PathPlanner:POI:AutoCruise,\
                       %0903NE:POI:PathPlanner:AutoCruise;\
                       \
                       %0401NE:PositionHold:CourseLock:PositionRoam:HomeLeash:AbsolutePosition:ReturnToBase:Land:PathPlanner:POI:AutoCruise,\
                       %0402NE:PositionHold:CourseLock:PositionRoam:HomeLeash:AbsolutePosition:ReturnToBase:Land:PathPlanner:POI:AutoCruise,\
                       %0903NE:POI:PathPlanner:AutoCruise;\
                       \
                       %0401NE:PositionHold:CourseLock:PositionRoam:HomeLeash:AbsolutePosition:ReturnToBase:Land:PathPlanner:POI:AutoCruise,\
                       %0402NE:PositionHold:CourseLock:PositionRoam:HomeLeash:AbsolutePosition:ReturnToBase:Land:PathPlanner:POI:AutoCruise,\
                       %0903NE:POI:PathPlanner:AutoCruise;")));
    QStringList DisableSanityChecksElemNames;
    DisableSanityChecksElemNames.append("0");
    QStringList DisableSanityChecksEnumOptions;
    DisableSanityChecksEnumOptions.append("FALSE");
    DisableSanityChecksEnumOptions.append("TRUE");
    fields.append( new UAVObjectField(QString("DisableSanityChecks"), tr(""), QString(""), UAVObjectField::ENUM, DisableSanityChecksElemNames, DisableSanityChecksEnumOptions, QString("")));
    QStringList ReturnToBaseNextCommandElemNames;
    ReturnToBaseNextCommandElemNames.append("0");
    QStringList ReturnToBaseNextCommandEnumOptions;
    ReturnToBaseNextCommandEnumOptions.append("Hold");
    ReturnToBaseNextCommandEnumOptions.append("Land");
    fields.append( new UAVObjectField(QString("ReturnToBaseNextCommand"), tr(""), QString(""), UAVObjectField::ENUM, ReturnToBaseNextCommandElemNames, ReturnToBaseNextCommandEnumOptions, QString("")));

    // Initialize object
    initializeFields(fields, (quint8 *)&data, NUMBYTES);
    // Set the default field values
    setDefaultFieldValues();
    // Set the object description
    setDescription(DESCRIPTION);

    // Set the Category of this object type
    setCategory(CATEGORY);

    connect(this, SIGNAL(objectUpdated(UAVObject *)), SLOT(emitNotifications()));
}

/**
 * Get the default metadata for this object
 */
UAVObject::Metadata FlightModeSettings::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        1 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        1 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_ONCHANGE << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_ONCHANGE << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_LOGGING_UPDATE_MODE_SHIFT;
    metadata.flightTelemetryUpdatePeriod = 0;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void FlightModeSettings::setDefaultFieldValues()
{
    data.ReturnToBaseAltitudeOffset = 10;
    data.LandingVelocity = 0.6;
    data.PositionHoldOffset[0] = 30;
    data.PositionHoldOffset[1] = 15;
    data.VarioControlLowPassAlpha = 0.98;
    data.ArmedTimeout = 30000;
    data.ArmingSequenceTime = 1000;
    data.DisarmingSequenceTime = 1000;
    data.Arming = 0;
    data.Stabilization1Settings[0] = 2;
    data.Stabilization1Settings[1] = 2;
    data.Stabilization1Settings[2] = 3;
    data.Stabilization1Settings[3] = 0;
    data.Stabilization2Settings[0] = 2;
    data.Stabilization2Settings[1] = 2;
    data.Stabilization2Settings[2] = 1;
    data.Stabilization2Settings[3] = 0;
    data.Stabilization3Settings[0] = 1;
    data.Stabilization3Settings[1] = 1;
    data.Stabilization3Settings[2] = 1;
    data.Stabilization3Settings[3] = 0;
    data.Stabilization4Settings[0] = 2;
    data.Stabilization4Settings[1] = 2;
    data.Stabilization4Settings[2] = 3;
    data.Stabilization4Settings[3] = 10;
    data.Stabilization5Settings[0] = 2;
    data.Stabilization5Settings[1] = 2;
    data.Stabilization5Settings[2] = 1;
    data.Stabilization5Settings[3] = 10;
    data.Stabilization6Settings[0] = 1;
    data.Stabilization6Settings[1] = 1;
    data.Stabilization6Settings[2] = 1;
    data.Stabilization6Settings[3] = 0;
    data.FlightModePosition[0] = 1;
    data.FlightModePosition[1] = 2;
    data.FlightModePosition[2] = 3;
    data.FlightModePosition[3] = 4;
    data.FlightModePosition[4] = 5;
    data.FlightModePosition[5] = 6;
    data.DisableSanityChecks = 0;
    data.ReturnToBaseNextCommand = 0;

}

/**
 * Get the object data fields
 */
FlightModeSettings::DataFields FlightModeSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void FlightModeSettings::setData(const DataFields& data)
{
    QMutexLocker locker(mutex);
    // Get metadata
    Metadata mdata = getMetadata();
    // Update object if the access mode permits
    if (UAVObject::GetGcsAccess(mdata) == ACCESS_READWRITE) {
        this->data = data;
        emit objectUpdatedAuto(this); // trigger object updated event
        emit objectUpdated(this);
    }
}

void FlightModeSettings::emitNotifications()
{
            //if (data.ReturnToBaseAltitudeOffset != oldData.ReturnToBaseAltitudeOffset)
            emit ReturnToBaseAltitudeOffsetChanged(data.ReturnToBaseAltitudeOffset);
        //if (data.LandingVelocity != oldData.LandingVelocity)
            emit LandingVelocityChanged(data.LandingVelocity);
        //if (data.PositionHoldOffset[0] != oldData.PositionHoldOffset[0])
            emit PositionHoldOffset_HorizontalChanged(data.PositionHoldOffset[0]);
        //if (data.PositionHoldOffset[1] != oldData.PositionHoldOffset[1])
            emit PositionHoldOffset_VerticalChanged(data.PositionHoldOffset[1]);
        //if (data.VarioControlLowPassAlpha != oldData.VarioControlLowPassAlpha)
            emit VarioControlLowPassAlphaChanged(data.VarioControlLowPassAlpha);
        //if (data.ArmedTimeout != oldData.ArmedTimeout)
            emit ArmedTimeoutChanged(data.ArmedTimeout);
        //if (data.ArmingSequenceTime != oldData.ArmingSequenceTime)
            emit ArmingSequenceTimeChanged(data.ArmingSequenceTime);
        //if (data.DisarmingSequenceTime != oldData.DisarmingSequenceTime)
            emit DisarmingSequenceTimeChanged(data.DisarmingSequenceTime);
        //if (data.Arming != oldData.Arming)
            emit ArmingChanged(data.Arming);
        //if (data.Stabilization1Settings[0] != oldData.Stabilization1Settings[0])
            emit Stabilization1Settings_RollChanged(data.Stabilization1Settings[0]);
        //if (data.Stabilization1Settings[1] != oldData.Stabilization1Settings[1])
            emit Stabilization1Settings_PitchChanged(data.Stabilization1Settings[1]);
        //if (data.Stabilization1Settings[2] != oldData.Stabilization1Settings[2])
            emit Stabilization1Settings_YawChanged(data.Stabilization1Settings[2]);
        //if (data.Stabilization1Settings[3] != oldData.Stabilization1Settings[3])
            emit Stabilization1Settings_ThrustChanged(data.Stabilization1Settings[3]);
        //if (data.Stabilization2Settings[0] != oldData.Stabilization2Settings[0])
            emit Stabilization2Settings_RollChanged(data.Stabilization2Settings[0]);
        //if (data.Stabilization2Settings[1] != oldData.Stabilization2Settings[1])
            emit Stabilization2Settings_PitchChanged(data.Stabilization2Settings[1]);
        //if (data.Stabilization2Settings[2] != oldData.Stabilization2Settings[2])
            emit Stabilization2Settings_YawChanged(data.Stabilization2Settings[2]);
        //if (data.Stabilization2Settings[3] != oldData.Stabilization2Settings[3])
            emit Stabilization2Settings_ThrustChanged(data.Stabilization2Settings[3]);
        //if (data.Stabilization3Settings[0] != oldData.Stabilization3Settings[0])
            emit Stabilization3Settings_RollChanged(data.Stabilization3Settings[0]);
        //if (data.Stabilization3Settings[1] != oldData.Stabilization3Settings[1])
            emit Stabilization3Settings_PitchChanged(data.Stabilization3Settings[1]);
        //if (data.Stabilization3Settings[2] != oldData.Stabilization3Settings[2])
            emit Stabilization3Settings_YawChanged(data.Stabilization3Settings[2]);
        //if (data.Stabilization3Settings[3] != oldData.Stabilization3Settings[3])
            emit Stabilization3Settings_ThrustChanged(data.Stabilization3Settings[3]);
        //if (data.Stabilization4Settings[0] != oldData.Stabilization4Settings[0])
            emit Stabilization4Settings_RollChanged(data.Stabilization4Settings[0]);
        //if (data.Stabilization4Settings[1] != oldData.Stabilization4Settings[1])
            emit Stabilization4Settings_PitchChanged(data.Stabilization4Settings[1]);
        //if (data.Stabilization4Settings[2] != oldData.Stabilization4Settings[2])
            emit Stabilization4Settings_YawChanged(data.Stabilization4Settings[2]);
        //if (data.Stabilization4Settings[3] != oldData.Stabilization4Settings[3])
            emit Stabilization4Settings_ThrustChanged(data.Stabilization4Settings[3]);
        //if (data.Stabilization5Settings[0] != oldData.Stabilization5Settings[0])
            emit Stabilization5Settings_RollChanged(data.Stabilization5Settings[0]);
        //if (data.Stabilization5Settings[1] != oldData.Stabilization5Settings[1])
            emit Stabilization5Settings_PitchChanged(data.Stabilization5Settings[1]);
        //if (data.Stabilization5Settings[2] != oldData.Stabilization5Settings[2])
            emit Stabilization5Settings_YawChanged(data.Stabilization5Settings[2]);
        //if (data.Stabilization5Settings[3] != oldData.Stabilization5Settings[3])
            emit Stabilization5Settings_ThrustChanged(data.Stabilization5Settings[3]);
        //if (data.Stabilization6Settings[0] != oldData.Stabilization6Settings[0])
            emit Stabilization6Settings_RollChanged(data.Stabilization6Settings[0]);
        //if (data.Stabilization6Settings[1] != oldData.Stabilization6Settings[1])
            emit Stabilization6Settings_PitchChanged(data.Stabilization6Settings[1]);
        //if (data.Stabilization6Settings[2] != oldData.Stabilization6Settings[2])
            emit Stabilization6Settings_YawChanged(data.Stabilization6Settings[2]);
        //if (data.Stabilization6Settings[3] != oldData.Stabilization6Settings[3])
            emit Stabilization6Settings_ThrustChanged(data.Stabilization6Settings[3]);
        //if (data.FlightModePosition[0] != oldData.FlightModePosition[0])
            emit FlightModePosition_0Changed(data.FlightModePosition[0]);
        //if (data.FlightModePosition[1] != oldData.FlightModePosition[1])
            emit FlightModePosition_1Changed(data.FlightModePosition[1]);
        //if (data.FlightModePosition[2] != oldData.FlightModePosition[2])
            emit FlightModePosition_2Changed(data.FlightModePosition[2]);
        //if (data.FlightModePosition[3] != oldData.FlightModePosition[3])
            emit FlightModePosition_3Changed(data.FlightModePosition[3]);
        //if (data.FlightModePosition[4] != oldData.FlightModePosition[4])
            emit FlightModePosition_4Changed(data.FlightModePosition[4]);
        //if (data.FlightModePosition[5] != oldData.FlightModePosition[5])
            emit FlightModePosition_5Changed(data.FlightModePosition[5]);
        //if (data.DisableSanityChecks != oldData.DisableSanityChecks)
            emit DisableSanityChecksChanged(data.DisableSanityChecks);
        //if (data.ReturnToBaseNextCommand != oldData.ReturnToBaseNextCommand)
            emit ReturnToBaseNextCommandChanged(data.ReturnToBaseNextCommand);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *FlightModeSettings::clone(quint32 instID)
{
    FlightModeSettings *obj = new FlightModeSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *FlightModeSettings::dirtyClone()
{
    FlightModeSettings *obj = new FlightModeSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
FlightModeSettings *FlightModeSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<FlightModeSettings *>(objMngr->getObject(FlightModeSettings::OBJID, instID));
}

float FlightModeSettings::getReturnToBaseAltitudeOffset() const
{
   QMutexLocker locker(mutex);
   return data.ReturnToBaseAltitudeOffset;
}
void FlightModeSettings::setReturnToBaseAltitudeOffset(float value)
{
   mutex->lock();
   bool changed = data.ReturnToBaseAltitudeOffset != value;
   data.ReturnToBaseAltitudeOffset = value;
   mutex->unlock();
   if (changed) emit ReturnToBaseAltitudeOffsetChanged(value);
}

float FlightModeSettings::getLandingVelocity() const
{
   QMutexLocker locker(mutex);
   return data.LandingVelocity;
}
void FlightModeSettings::setLandingVelocity(float value)
{
   mutex->lock();
   bool changed = data.LandingVelocity != value;
   data.LandingVelocity = value;
   mutex->unlock();
   if (changed) emit LandingVelocityChanged(value);
}

float FlightModeSettings::getPositionHoldOffset(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.PositionHoldOffset[index];
}
void FlightModeSettings::setPositionHoldOffset(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.PositionHoldOffset[index] != value;
   data.PositionHoldOffset[index] = value;
   mutex->unlock();
   if (changed) emit PositionHoldOffsetChanged(index,value);
}

float FlightModeSettings::getPositionHoldOffset_Horizontal() const
{
   QMutexLocker locker(mutex);
   return data.PositionHoldOffset[0];
}
void FlightModeSettings::setPositionHoldOffset_Horizontal(float value)
{
   mutex->lock();
   bool changed = data.PositionHoldOffset[0] != value;
   data.PositionHoldOffset[0] = value;
   mutex->unlock();
   if (changed) emit PositionHoldOffset_HorizontalChanged(value);
}

float FlightModeSettings::getPositionHoldOffset_Vertical() const
{
   QMutexLocker locker(mutex);
   return data.PositionHoldOffset[1];
}
void FlightModeSettings::setPositionHoldOffset_Vertical(float value)
{
   mutex->lock();
   bool changed = data.PositionHoldOffset[1] != value;
   data.PositionHoldOffset[1] = value;
   mutex->unlock();
   if (changed) emit PositionHoldOffset_VerticalChanged(value);
}

float FlightModeSettings::getVarioControlLowPassAlpha() const
{
   QMutexLocker locker(mutex);
   return data.VarioControlLowPassAlpha;
}
void FlightModeSettings::setVarioControlLowPassAlpha(float value)
{
   mutex->lock();
   bool changed = data.VarioControlLowPassAlpha != value;
   data.VarioControlLowPassAlpha = value;
   mutex->unlock();
   if (changed) emit VarioControlLowPassAlphaChanged(value);
}

quint16 FlightModeSettings::getArmedTimeout() const
{
   QMutexLocker locker(mutex);
   return data.ArmedTimeout;
}
void FlightModeSettings::setArmedTimeout(quint16 value)
{
   mutex->lock();
   bool changed = data.ArmedTimeout != value;
   data.ArmedTimeout = value;
   mutex->unlock();
   if (changed) emit ArmedTimeoutChanged(value);
}

quint16 FlightModeSettings::getArmingSequenceTime() const
{
   QMutexLocker locker(mutex);
   return data.ArmingSequenceTime;
}
void FlightModeSettings::setArmingSequenceTime(quint16 value)
{
   mutex->lock();
   bool changed = data.ArmingSequenceTime != value;
   data.ArmingSequenceTime = value;
   mutex->unlock();
   if (changed) emit ArmingSequenceTimeChanged(value);
}

quint16 FlightModeSettings::getDisarmingSequenceTime() const
{
   QMutexLocker locker(mutex);
   return data.DisarmingSequenceTime;
}
void FlightModeSettings::setDisarmingSequenceTime(quint16 value)
{
   mutex->lock();
   bool changed = data.DisarmingSequenceTime != value;
   data.DisarmingSequenceTime = value;
   mutex->unlock();
   if (changed) emit DisarmingSequenceTimeChanged(value);
}

quint8 FlightModeSettings::getArming() const
{
   QMutexLocker locker(mutex);
   return data.Arming;
}
void FlightModeSettings::setArming(quint8 value)
{
   mutex->lock();
   bool changed = data.Arming != value;
   data.Arming = value;
   mutex->unlock();
   if (changed) emit ArmingChanged(value);
}

quint8 FlightModeSettings::getStabilization1Settings(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Stabilization1Settings[index];
}
void FlightModeSettings::setStabilization1Settings(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization1Settings[index] != value;
   data.Stabilization1Settings[index] = value;
   mutex->unlock();
   if (changed) emit Stabilization1SettingsChanged(index,value);
}

quint8 FlightModeSettings::getStabilization1Settings_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization1Settings[0];
}
void FlightModeSettings::setStabilization1Settings_Roll(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization1Settings[0] != value;
   data.Stabilization1Settings[0] = value;
   mutex->unlock();
   if (changed) emit Stabilization1Settings_RollChanged(value);
}

quint8 FlightModeSettings::getStabilization1Settings_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization1Settings[1];
}
void FlightModeSettings::setStabilization1Settings_Pitch(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization1Settings[1] != value;
   data.Stabilization1Settings[1] = value;
   mutex->unlock();
   if (changed) emit Stabilization1Settings_PitchChanged(value);
}

quint8 FlightModeSettings::getStabilization1Settings_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization1Settings[2];
}
void FlightModeSettings::setStabilization1Settings_Yaw(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization1Settings[2] != value;
   data.Stabilization1Settings[2] = value;
   mutex->unlock();
   if (changed) emit Stabilization1Settings_YawChanged(value);
}

quint8 FlightModeSettings::getStabilization1Settings_Thrust() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization1Settings[3];
}
void FlightModeSettings::setStabilization1Settings_Thrust(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization1Settings[3] != value;
   data.Stabilization1Settings[3] = value;
   mutex->unlock();
   if (changed) emit Stabilization1Settings_ThrustChanged(value);
}

quint8 FlightModeSettings::getStabilization2Settings(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Stabilization2Settings[index];
}
void FlightModeSettings::setStabilization2Settings(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization2Settings[index] != value;
   data.Stabilization2Settings[index] = value;
   mutex->unlock();
   if (changed) emit Stabilization2SettingsChanged(index,value);
}

quint8 FlightModeSettings::getStabilization2Settings_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization2Settings[0];
}
void FlightModeSettings::setStabilization2Settings_Roll(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization2Settings[0] != value;
   data.Stabilization2Settings[0] = value;
   mutex->unlock();
   if (changed) emit Stabilization2Settings_RollChanged(value);
}

quint8 FlightModeSettings::getStabilization2Settings_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization2Settings[1];
}
void FlightModeSettings::setStabilization2Settings_Pitch(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization2Settings[1] != value;
   data.Stabilization2Settings[1] = value;
   mutex->unlock();
   if (changed) emit Stabilization2Settings_PitchChanged(value);
}

quint8 FlightModeSettings::getStabilization2Settings_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization2Settings[2];
}
void FlightModeSettings::setStabilization2Settings_Yaw(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization2Settings[2] != value;
   data.Stabilization2Settings[2] = value;
   mutex->unlock();
   if (changed) emit Stabilization2Settings_YawChanged(value);
}

quint8 FlightModeSettings::getStabilization2Settings_Thrust() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization2Settings[3];
}
void FlightModeSettings::setStabilization2Settings_Thrust(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization2Settings[3] != value;
   data.Stabilization2Settings[3] = value;
   mutex->unlock();
   if (changed) emit Stabilization2Settings_ThrustChanged(value);
}

quint8 FlightModeSettings::getStabilization3Settings(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Stabilization3Settings[index];
}
void FlightModeSettings::setStabilization3Settings(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization3Settings[index] != value;
   data.Stabilization3Settings[index] = value;
   mutex->unlock();
   if (changed) emit Stabilization3SettingsChanged(index,value);
}

quint8 FlightModeSettings::getStabilization3Settings_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization3Settings[0];
}
void FlightModeSettings::setStabilization3Settings_Roll(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization3Settings[0] != value;
   data.Stabilization3Settings[0] = value;
   mutex->unlock();
   if (changed) emit Stabilization3Settings_RollChanged(value);
}

quint8 FlightModeSettings::getStabilization3Settings_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization3Settings[1];
}
void FlightModeSettings::setStabilization3Settings_Pitch(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization3Settings[1] != value;
   data.Stabilization3Settings[1] = value;
   mutex->unlock();
   if (changed) emit Stabilization3Settings_PitchChanged(value);
}

quint8 FlightModeSettings::getStabilization3Settings_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization3Settings[2];
}
void FlightModeSettings::setStabilization3Settings_Yaw(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization3Settings[2] != value;
   data.Stabilization3Settings[2] = value;
   mutex->unlock();
   if (changed) emit Stabilization3Settings_YawChanged(value);
}

quint8 FlightModeSettings::getStabilization3Settings_Thrust() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization3Settings[3];
}
void FlightModeSettings::setStabilization3Settings_Thrust(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization3Settings[3] != value;
   data.Stabilization3Settings[3] = value;
   mutex->unlock();
   if (changed) emit Stabilization3Settings_ThrustChanged(value);
}

quint8 FlightModeSettings::getStabilization4Settings(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Stabilization4Settings[index];
}
void FlightModeSettings::setStabilization4Settings(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization4Settings[index] != value;
   data.Stabilization4Settings[index] = value;
   mutex->unlock();
   if (changed) emit Stabilization4SettingsChanged(index,value);
}

quint8 FlightModeSettings::getStabilization4Settings_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization4Settings[0];
}
void FlightModeSettings::setStabilization4Settings_Roll(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization4Settings[0] != value;
   data.Stabilization4Settings[0] = value;
   mutex->unlock();
   if (changed) emit Stabilization4Settings_RollChanged(value);
}

quint8 FlightModeSettings::getStabilization4Settings_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization4Settings[1];
}
void FlightModeSettings::setStabilization4Settings_Pitch(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization4Settings[1] != value;
   data.Stabilization4Settings[1] = value;
   mutex->unlock();
   if (changed) emit Stabilization4Settings_PitchChanged(value);
}

quint8 FlightModeSettings::getStabilization4Settings_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization4Settings[2];
}
void FlightModeSettings::setStabilization4Settings_Yaw(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization4Settings[2] != value;
   data.Stabilization4Settings[2] = value;
   mutex->unlock();
   if (changed) emit Stabilization4Settings_YawChanged(value);
}

quint8 FlightModeSettings::getStabilization4Settings_Thrust() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization4Settings[3];
}
void FlightModeSettings::setStabilization4Settings_Thrust(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization4Settings[3] != value;
   data.Stabilization4Settings[3] = value;
   mutex->unlock();
   if (changed) emit Stabilization4Settings_ThrustChanged(value);
}

quint8 FlightModeSettings::getStabilization5Settings(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Stabilization5Settings[index];
}
void FlightModeSettings::setStabilization5Settings(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization5Settings[index] != value;
   data.Stabilization5Settings[index] = value;
   mutex->unlock();
   if (changed) emit Stabilization5SettingsChanged(index,value);
}

quint8 FlightModeSettings::getStabilization5Settings_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization5Settings[0];
}
void FlightModeSettings::setStabilization5Settings_Roll(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization5Settings[0] != value;
   data.Stabilization5Settings[0] = value;
   mutex->unlock();
   if (changed) emit Stabilization5Settings_RollChanged(value);
}

quint8 FlightModeSettings::getStabilization5Settings_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization5Settings[1];
}
void FlightModeSettings::setStabilization5Settings_Pitch(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization5Settings[1] != value;
   data.Stabilization5Settings[1] = value;
   mutex->unlock();
   if (changed) emit Stabilization5Settings_PitchChanged(value);
}

quint8 FlightModeSettings::getStabilization5Settings_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization5Settings[2];
}
void FlightModeSettings::setStabilization5Settings_Yaw(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization5Settings[2] != value;
   data.Stabilization5Settings[2] = value;
   mutex->unlock();
   if (changed) emit Stabilization5Settings_YawChanged(value);
}

quint8 FlightModeSettings::getStabilization5Settings_Thrust() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization5Settings[3];
}
void FlightModeSettings::setStabilization5Settings_Thrust(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization5Settings[3] != value;
   data.Stabilization5Settings[3] = value;
   mutex->unlock();
   if (changed) emit Stabilization5Settings_ThrustChanged(value);
}

quint8 FlightModeSettings::getStabilization6Settings(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Stabilization6Settings[index];
}
void FlightModeSettings::setStabilization6Settings(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization6Settings[index] != value;
   data.Stabilization6Settings[index] = value;
   mutex->unlock();
   if (changed) emit Stabilization6SettingsChanged(index,value);
}

quint8 FlightModeSettings::getStabilization6Settings_Roll() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization6Settings[0];
}
void FlightModeSettings::setStabilization6Settings_Roll(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization6Settings[0] != value;
   data.Stabilization6Settings[0] = value;
   mutex->unlock();
   if (changed) emit Stabilization6Settings_RollChanged(value);
}

quint8 FlightModeSettings::getStabilization6Settings_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization6Settings[1];
}
void FlightModeSettings::setStabilization6Settings_Pitch(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization6Settings[1] != value;
   data.Stabilization6Settings[1] = value;
   mutex->unlock();
   if (changed) emit Stabilization6Settings_PitchChanged(value);
}

quint8 FlightModeSettings::getStabilization6Settings_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization6Settings[2];
}
void FlightModeSettings::setStabilization6Settings_Yaw(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization6Settings[2] != value;
   data.Stabilization6Settings[2] = value;
   mutex->unlock();
   if (changed) emit Stabilization6Settings_YawChanged(value);
}

quint8 FlightModeSettings::getStabilization6Settings_Thrust() const
{
   QMutexLocker locker(mutex);
   return data.Stabilization6Settings[3];
}
void FlightModeSettings::setStabilization6Settings_Thrust(quint8 value)
{
   mutex->lock();
   bool changed = data.Stabilization6Settings[3] != value;
   data.Stabilization6Settings[3] = value;
   mutex->unlock();
   if (changed) emit Stabilization6Settings_ThrustChanged(value);
}

quint8 FlightModeSettings::getFlightModePosition(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.FlightModePosition[index];
}
void FlightModeSettings::setFlightModePosition(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModePosition[index] != value;
   data.FlightModePosition[index] = value;
   mutex->unlock();
   if (changed) emit FlightModePositionChanged(index,value);
}

quint8 FlightModeSettings::getFlightModePosition_0() const
{
   QMutexLocker locker(mutex);
   return data.FlightModePosition[0];
}
void FlightModeSettings::setFlightModePosition_0(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModePosition[0] != value;
   data.FlightModePosition[0] = value;
   mutex->unlock();
   if (changed) emit FlightModePosition_0Changed(value);
}

quint8 FlightModeSettings::getFlightModePosition_1() const
{
   QMutexLocker locker(mutex);
   return data.FlightModePosition[1];
}
void FlightModeSettings::setFlightModePosition_1(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModePosition[1] != value;
   data.FlightModePosition[1] = value;
   mutex->unlock();
   if (changed) emit FlightModePosition_1Changed(value);
}

quint8 FlightModeSettings::getFlightModePosition_2() const
{
   QMutexLocker locker(mutex);
   return data.FlightModePosition[2];
}
void FlightModeSettings::setFlightModePosition_2(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModePosition[2] != value;
   data.FlightModePosition[2] = value;
   mutex->unlock();
   if (changed) emit FlightModePosition_2Changed(value);
}

quint8 FlightModeSettings::getFlightModePosition_3() const
{
   QMutexLocker locker(mutex);
   return data.FlightModePosition[3];
}
void FlightModeSettings::setFlightModePosition_3(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModePosition[3] != value;
   data.FlightModePosition[3] = value;
   mutex->unlock();
   if (changed) emit FlightModePosition_3Changed(value);
}

quint8 FlightModeSettings::getFlightModePosition_4() const
{
   QMutexLocker locker(mutex);
   return data.FlightModePosition[4];
}
void FlightModeSettings::setFlightModePosition_4(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModePosition[4] != value;
   data.FlightModePosition[4] = value;
   mutex->unlock();
   if (changed) emit FlightModePosition_4Changed(value);
}

quint8 FlightModeSettings::getFlightModePosition_5() const
{
   QMutexLocker locker(mutex);
   return data.FlightModePosition[5];
}
void FlightModeSettings::setFlightModePosition_5(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModePosition[5] != value;
   data.FlightModePosition[5] = value;
   mutex->unlock();
   if (changed) emit FlightModePosition_5Changed(value);
}

quint8 FlightModeSettings::getDisableSanityChecks() const
{
   QMutexLocker locker(mutex);
   return data.DisableSanityChecks;
}
void FlightModeSettings::setDisableSanityChecks(quint8 value)
{
   mutex->lock();
   bool changed = data.DisableSanityChecks != value;
   data.DisableSanityChecks = value;
   mutex->unlock();
   if (changed) emit DisableSanityChecksChanged(value);
}

quint8 FlightModeSettings::getReturnToBaseNextCommand() const
{
   QMutexLocker locker(mutex);
   return data.ReturnToBaseNextCommand;
}
void FlightModeSettings::setReturnToBaseNextCommand(quint8 value)
{
   mutex->lock();
   bool changed = data.ReturnToBaseNextCommand != value;
   data.ReturnToBaseNextCommand = value;
   mutex->unlock();
   if (changed) emit ReturnToBaseNextCommandChanged(value);
}


