/**
 ******************************************************************************
 *
 * @file       manualcontrolsettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: manualcontrolsettings.xml.
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

#include "manualcontrolsettings.h"
#include "uavobjectfield.h"

const QString ManualControlSettings::NAME = QString("ManualControlSettings");
const QString ManualControlSettings::DESCRIPTION = QString("Settings to indicate how to decode receiver input by @ref ManualControlModule.");
const QString ManualControlSettings::CATEGORY = QString("Control");

/**
 * Constructor
 */
ManualControlSettings::ManualControlSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList DeadbandElemNames;
    DeadbandElemNames.append("0");
    fields.append( new UAVObjectField(QString("Deadband"), tr(""), QString("%"), UAVObjectField::FLOAT32, DeadbandElemNames, QStringList(), QString("")));
    QStringList DeadbandAssistedControlElemNames;
    DeadbandAssistedControlElemNames.append("0");
    fields.append( new UAVObjectField(QString("DeadbandAssistedControl"), tr("Stick deadband used for AssistedControl"), QString("%"), UAVObjectField::FLOAT32, DeadbandAssistedControlElemNames, QStringList(), QString("")));
    QStringList FailsafeChannelElemNames;
    FailsafeChannelElemNames.append("Throttle");
    FailsafeChannelElemNames.append("Roll");
    FailsafeChannelElemNames.append("Pitch");
    FailsafeChannelElemNames.append("Yaw");
    FailsafeChannelElemNames.append("Collective");
    FailsafeChannelElemNames.append("Accessory0");
    FailsafeChannelElemNames.append("Accessory1");
    FailsafeChannelElemNames.append("Accessory2");
    fields.append( new UAVObjectField(QString("FailsafeChannel"), tr(""), QString("%"), UAVObjectField::FLOAT32, FailsafeChannelElemNames, QStringList(), QString("")));
    QStringList ChannelMinElemNames;
    ChannelMinElemNames.append("Throttle");
    ChannelMinElemNames.append("Roll");
    ChannelMinElemNames.append("Pitch");
    ChannelMinElemNames.append("Yaw");
    ChannelMinElemNames.append("FlightMode");
    ChannelMinElemNames.append("Collective");
    ChannelMinElemNames.append("Accessory0");
    ChannelMinElemNames.append("Accessory1");
    ChannelMinElemNames.append("Accessory2");
    fields.append( new UAVObjectField(QString("ChannelMin"), tr(""), QString("us"), UAVObjectField::INT16, ChannelMinElemNames, QStringList(), QString("")));
    QStringList ChannelNeutralElemNames;
    ChannelNeutralElemNames.append("Throttle");
    ChannelNeutralElemNames.append("Roll");
    ChannelNeutralElemNames.append("Pitch");
    ChannelNeutralElemNames.append("Yaw");
    ChannelNeutralElemNames.append("FlightMode");
    ChannelNeutralElemNames.append("Collective");
    ChannelNeutralElemNames.append("Accessory0");
    ChannelNeutralElemNames.append("Accessory1");
    ChannelNeutralElemNames.append("Accessory2");
    fields.append( new UAVObjectField(QString("ChannelNeutral"), tr(""), QString("us"), UAVObjectField::INT16, ChannelNeutralElemNames, QStringList(), QString("")));
    QStringList ChannelMaxElemNames;
    ChannelMaxElemNames.append("Throttle");
    ChannelMaxElemNames.append("Roll");
    ChannelMaxElemNames.append("Pitch");
    ChannelMaxElemNames.append("Yaw");
    ChannelMaxElemNames.append("FlightMode");
    ChannelMaxElemNames.append("Collective");
    ChannelMaxElemNames.append("Accessory0");
    ChannelMaxElemNames.append("Accessory1");
    ChannelMaxElemNames.append("Accessory2");
    fields.append( new UAVObjectField(QString("ChannelMax"), tr(""), QString("us"), UAVObjectField::INT16, ChannelMaxElemNames, QStringList(), QString("")));
    QStringList ResponseTimeElemNames;
    ResponseTimeElemNames.append("Roll");
    ResponseTimeElemNames.append("Pitch");
    ResponseTimeElemNames.append("Yaw");
    ResponseTimeElemNames.append("Collective");
    ResponseTimeElemNames.append("Accessory0");
    ResponseTimeElemNames.append("Accessory1");
    ResponseTimeElemNames.append("Accessory2");
    fields.append( new UAVObjectField(QString("ResponseTime"), tr(""), QString("ms"), UAVObjectField::UINT16, ResponseTimeElemNames, QStringList(), QString("")));
    QStringList ChannelGroupsElemNames;
    ChannelGroupsElemNames.append("Throttle");
    ChannelGroupsElemNames.append("Roll");
    ChannelGroupsElemNames.append("Pitch");
    ChannelGroupsElemNames.append("Yaw");
    ChannelGroupsElemNames.append("FlightMode");
    ChannelGroupsElemNames.append("Collective");
    ChannelGroupsElemNames.append("Accessory0");
    ChannelGroupsElemNames.append("Accessory1");
    ChannelGroupsElemNames.append("Accessory2");
    QStringList ChannelGroupsEnumOptions;
    ChannelGroupsEnumOptions.append("PWM");
    ChannelGroupsEnumOptions.append("PPM");
    ChannelGroupsEnumOptions.append("DSM (MainPort)");
    ChannelGroupsEnumOptions.append("DSM (FlexiPort)");
    ChannelGroupsEnumOptions.append("S.Bus");
    ChannelGroupsEnumOptions.append("GCS");
    ChannelGroupsEnumOptions.append("OPLink");
    ChannelGroupsEnumOptions.append("None");
    fields.append( new UAVObjectField(QString("ChannelGroups"), tr(""), QString("Channel Group"), UAVObjectField::ENUM, ChannelGroupsElemNames, ChannelGroupsEnumOptions, QString("")));
    QStringList ChannelNumberElemNames;
    ChannelNumberElemNames.append("Throttle");
    ChannelNumberElemNames.append("Roll");
    ChannelNumberElemNames.append("Pitch");
    ChannelNumberElemNames.append("Yaw");
    ChannelNumberElemNames.append("FlightMode");
    ChannelNumberElemNames.append("Collective");
    ChannelNumberElemNames.append("Accessory0");
    ChannelNumberElemNames.append("Accessory1");
    ChannelNumberElemNames.append("Accessory2");
    fields.append( new UAVObjectField(QString("ChannelNumber"), tr(""), QString("channel"), UAVObjectField::UINT8, ChannelNumberElemNames, QStringList(), QString("")));
    QStringList FlightModeNumberElemNames;
    FlightModeNumberElemNames.append("0");
    fields.append( new UAVObjectField(QString("FlightModeNumber"), tr(""), QString(""), UAVObjectField::UINT8, FlightModeNumberElemNames, QStringList(), QString("")));
    QStringList FailsafeFlightModeSwitchPositionElemNames;
    FailsafeFlightModeSwitchPositionElemNames.append("0");
    fields.append( new UAVObjectField(QString("FailsafeFlightModeSwitchPosition"), tr(""), QString(""), UAVObjectField::INT8, FailsafeFlightModeSwitchPositionElemNames, QStringList(), QString("")));

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
UAVObject::Metadata ManualControlSettings::getDefaultMetadata()
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
void ManualControlSettings::setDefaultFieldValues()
{
    data.Deadband = 0.02;
    data.DeadbandAssistedControl = 0.08;
    data.FailsafeChannel[0] = -1;
    data.FailsafeChannel[1] = 0;
    data.FailsafeChannel[2] = 0;
    data.FailsafeChannel[3] = 0;
    data.FailsafeChannel[4] = 0;
    data.FailsafeChannel[5] = 0;
    data.FailsafeChannel[6] = 0;
    data.FailsafeChannel[7] = 0;
    data.ChannelMin[0] = 1000;
    data.ChannelMin[1] = 1000;
    data.ChannelMin[2] = 1000;
    data.ChannelMin[3] = 1000;
    data.ChannelMin[4] = 1000;
    data.ChannelMin[5] = 1000;
    data.ChannelMin[6] = 1000;
    data.ChannelMin[7] = 1000;
    data.ChannelMin[8] = 1000;
    data.ChannelNeutral[0] = 1500;
    data.ChannelNeutral[1] = 1500;
    data.ChannelNeutral[2] = 1500;
    data.ChannelNeutral[3] = 1500;
    data.ChannelNeutral[4] = 1500;
    data.ChannelNeutral[5] = 1500;
    data.ChannelNeutral[6] = 1500;
    data.ChannelNeutral[7] = 1500;
    data.ChannelNeutral[8] = 1500;
    data.ChannelMax[0] = 2000;
    data.ChannelMax[1] = 2000;
    data.ChannelMax[2] = 2000;
    data.ChannelMax[3] = 2000;
    data.ChannelMax[4] = 2000;
    data.ChannelMax[5] = 2000;
    data.ChannelMax[6] = 2000;
    data.ChannelMax[7] = 2000;
    data.ChannelMax[8] = 2000;
    data.ResponseTime[0] = 0;
    data.ResponseTime[1] = 0;
    data.ResponseTime[2] = 0;
    data.ResponseTime[3] = 0;
    data.ResponseTime[4] = 0;
    data.ResponseTime[5] = 0;
    data.ResponseTime[6] = 0;
    data.ChannelGroups[0] = 7;
    data.ChannelGroups[1] = 7;
    data.ChannelGroups[2] = 7;
    data.ChannelGroups[3] = 7;
    data.ChannelGroups[4] = 7;
    data.ChannelGroups[5] = 7;
    data.ChannelGroups[6] = 7;
    data.ChannelGroups[7] = 7;
    data.ChannelGroups[8] = 7;
    data.ChannelNumber[0] = 0;
    data.ChannelNumber[1] = 0;
    data.ChannelNumber[2] = 0;
    data.ChannelNumber[3] = 0;
    data.ChannelNumber[4] = 0;
    data.ChannelNumber[5] = 0;
    data.ChannelNumber[6] = 0;
    data.ChannelNumber[7] = 0;
    data.ChannelNumber[8] = 0;
    data.FlightModeNumber = 3;
    data.FailsafeFlightModeSwitchPosition = -1;

}

/**
 * Get the object data fields
 */
ManualControlSettings::DataFields ManualControlSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void ManualControlSettings::setData(const DataFields& data)
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

void ManualControlSettings::emitNotifications()
{
            //if (data.Deadband != oldData.Deadband)
            emit DeadbandChanged(data.Deadband);
        //if (data.DeadbandAssistedControl != oldData.DeadbandAssistedControl)
            emit DeadbandAssistedControlChanged(data.DeadbandAssistedControl);
        //if (data.FailsafeChannel[0] != oldData.FailsafeChannel[0])
            emit FailsafeChannel_ThrottleChanged(data.FailsafeChannel[0]);
        //if (data.FailsafeChannel[1] != oldData.FailsafeChannel[1])
            emit FailsafeChannel_RollChanged(data.FailsafeChannel[1]);
        //if (data.FailsafeChannel[2] != oldData.FailsafeChannel[2])
            emit FailsafeChannel_PitchChanged(data.FailsafeChannel[2]);
        //if (data.FailsafeChannel[3] != oldData.FailsafeChannel[3])
            emit FailsafeChannel_YawChanged(data.FailsafeChannel[3]);
        //if (data.FailsafeChannel[4] != oldData.FailsafeChannel[4])
            emit FailsafeChannel_CollectiveChanged(data.FailsafeChannel[4]);
        //if (data.FailsafeChannel[5] != oldData.FailsafeChannel[5])
            emit FailsafeChannel_Accessory0Changed(data.FailsafeChannel[5]);
        //if (data.FailsafeChannel[6] != oldData.FailsafeChannel[6])
            emit FailsafeChannel_Accessory1Changed(data.FailsafeChannel[6]);
        //if (data.FailsafeChannel[7] != oldData.FailsafeChannel[7])
            emit FailsafeChannel_Accessory2Changed(data.FailsafeChannel[7]);
        //if (data.ChannelMin[0] != oldData.ChannelMin[0])
            emit ChannelMin_ThrottleChanged(data.ChannelMin[0]);
        //if (data.ChannelMin[1] != oldData.ChannelMin[1])
            emit ChannelMin_RollChanged(data.ChannelMin[1]);
        //if (data.ChannelMin[2] != oldData.ChannelMin[2])
            emit ChannelMin_PitchChanged(data.ChannelMin[2]);
        //if (data.ChannelMin[3] != oldData.ChannelMin[3])
            emit ChannelMin_YawChanged(data.ChannelMin[3]);
        //if (data.ChannelMin[4] != oldData.ChannelMin[4])
            emit ChannelMin_FlightModeChanged(data.ChannelMin[4]);
        //if (data.ChannelMin[5] != oldData.ChannelMin[5])
            emit ChannelMin_CollectiveChanged(data.ChannelMin[5]);
        //if (data.ChannelMin[6] != oldData.ChannelMin[6])
            emit ChannelMin_Accessory0Changed(data.ChannelMin[6]);
        //if (data.ChannelMin[7] != oldData.ChannelMin[7])
            emit ChannelMin_Accessory1Changed(data.ChannelMin[7]);
        //if (data.ChannelMin[8] != oldData.ChannelMin[8])
            emit ChannelMin_Accessory2Changed(data.ChannelMin[8]);
        //if (data.ChannelNeutral[0] != oldData.ChannelNeutral[0])
            emit ChannelNeutral_ThrottleChanged(data.ChannelNeutral[0]);
        //if (data.ChannelNeutral[1] != oldData.ChannelNeutral[1])
            emit ChannelNeutral_RollChanged(data.ChannelNeutral[1]);
        //if (data.ChannelNeutral[2] != oldData.ChannelNeutral[2])
            emit ChannelNeutral_PitchChanged(data.ChannelNeutral[2]);
        //if (data.ChannelNeutral[3] != oldData.ChannelNeutral[3])
            emit ChannelNeutral_YawChanged(data.ChannelNeutral[3]);
        //if (data.ChannelNeutral[4] != oldData.ChannelNeutral[4])
            emit ChannelNeutral_FlightModeChanged(data.ChannelNeutral[4]);
        //if (data.ChannelNeutral[5] != oldData.ChannelNeutral[5])
            emit ChannelNeutral_CollectiveChanged(data.ChannelNeutral[5]);
        //if (data.ChannelNeutral[6] != oldData.ChannelNeutral[6])
            emit ChannelNeutral_Accessory0Changed(data.ChannelNeutral[6]);
        //if (data.ChannelNeutral[7] != oldData.ChannelNeutral[7])
            emit ChannelNeutral_Accessory1Changed(data.ChannelNeutral[7]);
        //if (data.ChannelNeutral[8] != oldData.ChannelNeutral[8])
            emit ChannelNeutral_Accessory2Changed(data.ChannelNeutral[8]);
        //if (data.ChannelMax[0] != oldData.ChannelMax[0])
            emit ChannelMax_ThrottleChanged(data.ChannelMax[0]);
        //if (data.ChannelMax[1] != oldData.ChannelMax[1])
            emit ChannelMax_RollChanged(data.ChannelMax[1]);
        //if (data.ChannelMax[2] != oldData.ChannelMax[2])
            emit ChannelMax_PitchChanged(data.ChannelMax[2]);
        //if (data.ChannelMax[3] != oldData.ChannelMax[3])
            emit ChannelMax_YawChanged(data.ChannelMax[3]);
        //if (data.ChannelMax[4] != oldData.ChannelMax[4])
            emit ChannelMax_FlightModeChanged(data.ChannelMax[4]);
        //if (data.ChannelMax[5] != oldData.ChannelMax[5])
            emit ChannelMax_CollectiveChanged(data.ChannelMax[5]);
        //if (data.ChannelMax[6] != oldData.ChannelMax[6])
            emit ChannelMax_Accessory0Changed(data.ChannelMax[6]);
        //if (data.ChannelMax[7] != oldData.ChannelMax[7])
            emit ChannelMax_Accessory1Changed(data.ChannelMax[7]);
        //if (data.ChannelMax[8] != oldData.ChannelMax[8])
            emit ChannelMax_Accessory2Changed(data.ChannelMax[8]);
        //if (data.ResponseTime[0] != oldData.ResponseTime[0])
            emit ResponseTime_RollChanged(data.ResponseTime[0]);
        //if (data.ResponseTime[1] != oldData.ResponseTime[1])
            emit ResponseTime_PitchChanged(data.ResponseTime[1]);
        //if (data.ResponseTime[2] != oldData.ResponseTime[2])
            emit ResponseTime_YawChanged(data.ResponseTime[2]);
        //if (data.ResponseTime[3] != oldData.ResponseTime[3])
            emit ResponseTime_CollectiveChanged(data.ResponseTime[3]);
        //if (data.ResponseTime[4] != oldData.ResponseTime[4])
            emit ResponseTime_Accessory0Changed(data.ResponseTime[4]);
        //if (data.ResponseTime[5] != oldData.ResponseTime[5])
            emit ResponseTime_Accessory1Changed(data.ResponseTime[5]);
        //if (data.ResponseTime[6] != oldData.ResponseTime[6])
            emit ResponseTime_Accessory2Changed(data.ResponseTime[6]);
        //if (data.ChannelGroups[0] != oldData.ChannelGroups[0])
            emit ChannelGroups_ThrottleChanged(data.ChannelGroups[0]);
        //if (data.ChannelGroups[1] != oldData.ChannelGroups[1])
            emit ChannelGroups_RollChanged(data.ChannelGroups[1]);
        //if (data.ChannelGroups[2] != oldData.ChannelGroups[2])
            emit ChannelGroups_PitchChanged(data.ChannelGroups[2]);
        //if (data.ChannelGroups[3] != oldData.ChannelGroups[3])
            emit ChannelGroups_YawChanged(data.ChannelGroups[3]);
        //if (data.ChannelGroups[4] != oldData.ChannelGroups[4])
            emit ChannelGroups_FlightModeChanged(data.ChannelGroups[4]);
        //if (data.ChannelGroups[5] != oldData.ChannelGroups[5])
            emit ChannelGroups_CollectiveChanged(data.ChannelGroups[5]);
        //if (data.ChannelGroups[6] != oldData.ChannelGroups[6])
            emit ChannelGroups_Accessory0Changed(data.ChannelGroups[6]);
        //if (data.ChannelGroups[7] != oldData.ChannelGroups[7])
            emit ChannelGroups_Accessory1Changed(data.ChannelGroups[7]);
        //if (data.ChannelGroups[8] != oldData.ChannelGroups[8])
            emit ChannelGroups_Accessory2Changed(data.ChannelGroups[8]);
        //if (data.ChannelNumber[0] != oldData.ChannelNumber[0])
            emit ChannelNumber_ThrottleChanged(data.ChannelNumber[0]);
        //if (data.ChannelNumber[1] != oldData.ChannelNumber[1])
            emit ChannelNumber_RollChanged(data.ChannelNumber[1]);
        //if (data.ChannelNumber[2] != oldData.ChannelNumber[2])
            emit ChannelNumber_PitchChanged(data.ChannelNumber[2]);
        //if (data.ChannelNumber[3] != oldData.ChannelNumber[3])
            emit ChannelNumber_YawChanged(data.ChannelNumber[3]);
        //if (data.ChannelNumber[4] != oldData.ChannelNumber[4])
            emit ChannelNumber_FlightModeChanged(data.ChannelNumber[4]);
        //if (data.ChannelNumber[5] != oldData.ChannelNumber[5])
            emit ChannelNumber_CollectiveChanged(data.ChannelNumber[5]);
        //if (data.ChannelNumber[6] != oldData.ChannelNumber[6])
            emit ChannelNumber_Accessory0Changed(data.ChannelNumber[6]);
        //if (data.ChannelNumber[7] != oldData.ChannelNumber[7])
            emit ChannelNumber_Accessory1Changed(data.ChannelNumber[7]);
        //if (data.ChannelNumber[8] != oldData.ChannelNumber[8])
            emit ChannelNumber_Accessory2Changed(data.ChannelNumber[8]);
        //if (data.FlightModeNumber != oldData.FlightModeNumber)
            emit FlightModeNumberChanged(data.FlightModeNumber);
        //if (data.FailsafeFlightModeSwitchPosition != oldData.FailsafeFlightModeSwitchPosition)
            emit FailsafeFlightModeSwitchPositionChanged(data.FailsafeFlightModeSwitchPosition);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *ManualControlSettings::clone(quint32 instID)
{
    ManualControlSettings *obj = new ManualControlSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *ManualControlSettings::dirtyClone()
{
    ManualControlSettings *obj = new ManualControlSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
ManualControlSettings *ManualControlSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<ManualControlSettings *>(objMngr->getObject(ManualControlSettings::OBJID, instID));
}

float ManualControlSettings::getDeadband() const
{
   QMutexLocker locker(mutex);
   return data.Deadband;
}
void ManualControlSettings::setDeadband(float value)
{
   mutex->lock();
   bool changed = data.Deadband != value;
   data.Deadband = value;
   mutex->unlock();
   if (changed) emit DeadbandChanged(value);
}

float ManualControlSettings::getDeadbandAssistedControl() const
{
   QMutexLocker locker(mutex);
   return data.DeadbandAssistedControl;
}
void ManualControlSettings::setDeadbandAssistedControl(float value)
{
   mutex->lock();
   bool changed = data.DeadbandAssistedControl != value;
   data.DeadbandAssistedControl = value;
   mutex->unlock();
   if (changed) emit DeadbandAssistedControlChanged(value);
}

float ManualControlSettings::getFailsafeChannel(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.FailsafeChannel[index];
}
void ManualControlSettings::setFailsafeChannel(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.FailsafeChannel[index] != value;
   data.FailsafeChannel[index] = value;
   mutex->unlock();
   if (changed) emit FailsafeChannelChanged(index,value);
}

float ManualControlSettings::getFailsafeChannel_Throttle() const
{
   QMutexLocker locker(mutex);
   return data.FailsafeChannel[0];
}
void ManualControlSettings::setFailsafeChannel_Throttle(float value)
{
   mutex->lock();
   bool changed = data.FailsafeChannel[0] != value;
   data.FailsafeChannel[0] = value;
   mutex->unlock();
   if (changed) emit FailsafeChannel_ThrottleChanged(value);
}

float ManualControlSettings::getFailsafeChannel_Roll() const
{
   QMutexLocker locker(mutex);
   return data.FailsafeChannel[1];
}
void ManualControlSettings::setFailsafeChannel_Roll(float value)
{
   mutex->lock();
   bool changed = data.FailsafeChannel[1] != value;
   data.FailsafeChannel[1] = value;
   mutex->unlock();
   if (changed) emit FailsafeChannel_RollChanged(value);
}

float ManualControlSettings::getFailsafeChannel_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.FailsafeChannel[2];
}
void ManualControlSettings::setFailsafeChannel_Pitch(float value)
{
   mutex->lock();
   bool changed = data.FailsafeChannel[2] != value;
   data.FailsafeChannel[2] = value;
   mutex->unlock();
   if (changed) emit FailsafeChannel_PitchChanged(value);
}

float ManualControlSettings::getFailsafeChannel_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.FailsafeChannel[3];
}
void ManualControlSettings::setFailsafeChannel_Yaw(float value)
{
   mutex->lock();
   bool changed = data.FailsafeChannel[3] != value;
   data.FailsafeChannel[3] = value;
   mutex->unlock();
   if (changed) emit FailsafeChannel_YawChanged(value);
}

float ManualControlSettings::getFailsafeChannel_Collective() const
{
   QMutexLocker locker(mutex);
   return data.FailsafeChannel[4];
}
void ManualControlSettings::setFailsafeChannel_Collective(float value)
{
   mutex->lock();
   bool changed = data.FailsafeChannel[4] != value;
   data.FailsafeChannel[4] = value;
   mutex->unlock();
   if (changed) emit FailsafeChannel_CollectiveChanged(value);
}

float ManualControlSettings::getFailsafeChannel_Accessory0() const
{
   QMutexLocker locker(mutex);
   return data.FailsafeChannel[5];
}
void ManualControlSettings::setFailsafeChannel_Accessory0(float value)
{
   mutex->lock();
   bool changed = data.FailsafeChannel[5] != value;
   data.FailsafeChannel[5] = value;
   mutex->unlock();
   if (changed) emit FailsafeChannel_Accessory0Changed(value);
}

float ManualControlSettings::getFailsafeChannel_Accessory1() const
{
   QMutexLocker locker(mutex);
   return data.FailsafeChannel[6];
}
void ManualControlSettings::setFailsafeChannel_Accessory1(float value)
{
   mutex->lock();
   bool changed = data.FailsafeChannel[6] != value;
   data.FailsafeChannel[6] = value;
   mutex->unlock();
   if (changed) emit FailsafeChannel_Accessory1Changed(value);
}

float ManualControlSettings::getFailsafeChannel_Accessory2() const
{
   QMutexLocker locker(mutex);
   return data.FailsafeChannel[7];
}
void ManualControlSettings::setFailsafeChannel_Accessory2(float value)
{
   mutex->lock();
   bool changed = data.FailsafeChannel[7] != value;
   data.FailsafeChannel[7] = value;
   mutex->unlock();
   if (changed) emit FailsafeChannel_Accessory2Changed(value);
}

qint16 ManualControlSettings::getChannelMin(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ChannelMin[index];
}
void ManualControlSettings::setChannelMin(quint32 index, qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMin[index] != value;
   data.ChannelMin[index] = value;
   mutex->unlock();
   if (changed) emit ChannelMinChanged(index,value);
}

qint16 ManualControlSettings::getChannelMin_Throttle() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMin[0];
}
void ManualControlSettings::setChannelMin_Throttle(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMin[0] != value;
   data.ChannelMin[0] = value;
   mutex->unlock();
   if (changed) emit ChannelMin_ThrottleChanged(value);
}

qint16 ManualControlSettings::getChannelMin_Roll() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMin[1];
}
void ManualControlSettings::setChannelMin_Roll(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMin[1] != value;
   data.ChannelMin[1] = value;
   mutex->unlock();
   if (changed) emit ChannelMin_RollChanged(value);
}

qint16 ManualControlSettings::getChannelMin_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMin[2];
}
void ManualControlSettings::setChannelMin_Pitch(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMin[2] != value;
   data.ChannelMin[2] = value;
   mutex->unlock();
   if (changed) emit ChannelMin_PitchChanged(value);
}

qint16 ManualControlSettings::getChannelMin_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMin[3];
}
void ManualControlSettings::setChannelMin_Yaw(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMin[3] != value;
   data.ChannelMin[3] = value;
   mutex->unlock();
   if (changed) emit ChannelMin_YawChanged(value);
}

qint16 ManualControlSettings::getChannelMin_FlightMode() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMin[4];
}
void ManualControlSettings::setChannelMin_FlightMode(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMin[4] != value;
   data.ChannelMin[4] = value;
   mutex->unlock();
   if (changed) emit ChannelMin_FlightModeChanged(value);
}

qint16 ManualControlSettings::getChannelMin_Collective() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMin[5];
}
void ManualControlSettings::setChannelMin_Collective(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMin[5] != value;
   data.ChannelMin[5] = value;
   mutex->unlock();
   if (changed) emit ChannelMin_CollectiveChanged(value);
}

qint16 ManualControlSettings::getChannelMin_Accessory0() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMin[6];
}
void ManualControlSettings::setChannelMin_Accessory0(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMin[6] != value;
   data.ChannelMin[6] = value;
   mutex->unlock();
   if (changed) emit ChannelMin_Accessory0Changed(value);
}

qint16 ManualControlSettings::getChannelMin_Accessory1() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMin[7];
}
void ManualControlSettings::setChannelMin_Accessory1(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMin[7] != value;
   data.ChannelMin[7] = value;
   mutex->unlock();
   if (changed) emit ChannelMin_Accessory1Changed(value);
}

qint16 ManualControlSettings::getChannelMin_Accessory2() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMin[8];
}
void ManualControlSettings::setChannelMin_Accessory2(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMin[8] != value;
   data.ChannelMin[8] = value;
   mutex->unlock();
   if (changed) emit ChannelMin_Accessory2Changed(value);
}

qint16 ManualControlSettings::getChannelNeutral(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ChannelNeutral[index];
}
void ManualControlSettings::setChannelNeutral(quint32 index, qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelNeutral[index] != value;
   data.ChannelNeutral[index] = value;
   mutex->unlock();
   if (changed) emit ChannelNeutralChanged(index,value);
}

qint16 ManualControlSettings::getChannelNeutral_Throttle() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNeutral[0];
}
void ManualControlSettings::setChannelNeutral_Throttle(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelNeutral[0] != value;
   data.ChannelNeutral[0] = value;
   mutex->unlock();
   if (changed) emit ChannelNeutral_ThrottleChanged(value);
}

qint16 ManualControlSettings::getChannelNeutral_Roll() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNeutral[1];
}
void ManualControlSettings::setChannelNeutral_Roll(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelNeutral[1] != value;
   data.ChannelNeutral[1] = value;
   mutex->unlock();
   if (changed) emit ChannelNeutral_RollChanged(value);
}

qint16 ManualControlSettings::getChannelNeutral_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNeutral[2];
}
void ManualControlSettings::setChannelNeutral_Pitch(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelNeutral[2] != value;
   data.ChannelNeutral[2] = value;
   mutex->unlock();
   if (changed) emit ChannelNeutral_PitchChanged(value);
}

qint16 ManualControlSettings::getChannelNeutral_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNeutral[3];
}
void ManualControlSettings::setChannelNeutral_Yaw(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelNeutral[3] != value;
   data.ChannelNeutral[3] = value;
   mutex->unlock();
   if (changed) emit ChannelNeutral_YawChanged(value);
}

qint16 ManualControlSettings::getChannelNeutral_FlightMode() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNeutral[4];
}
void ManualControlSettings::setChannelNeutral_FlightMode(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelNeutral[4] != value;
   data.ChannelNeutral[4] = value;
   mutex->unlock();
   if (changed) emit ChannelNeutral_FlightModeChanged(value);
}

qint16 ManualControlSettings::getChannelNeutral_Collective() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNeutral[5];
}
void ManualControlSettings::setChannelNeutral_Collective(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelNeutral[5] != value;
   data.ChannelNeutral[5] = value;
   mutex->unlock();
   if (changed) emit ChannelNeutral_CollectiveChanged(value);
}

qint16 ManualControlSettings::getChannelNeutral_Accessory0() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNeutral[6];
}
void ManualControlSettings::setChannelNeutral_Accessory0(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelNeutral[6] != value;
   data.ChannelNeutral[6] = value;
   mutex->unlock();
   if (changed) emit ChannelNeutral_Accessory0Changed(value);
}

qint16 ManualControlSettings::getChannelNeutral_Accessory1() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNeutral[7];
}
void ManualControlSettings::setChannelNeutral_Accessory1(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelNeutral[7] != value;
   data.ChannelNeutral[7] = value;
   mutex->unlock();
   if (changed) emit ChannelNeutral_Accessory1Changed(value);
}

qint16 ManualControlSettings::getChannelNeutral_Accessory2() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNeutral[8];
}
void ManualControlSettings::setChannelNeutral_Accessory2(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelNeutral[8] != value;
   data.ChannelNeutral[8] = value;
   mutex->unlock();
   if (changed) emit ChannelNeutral_Accessory2Changed(value);
}

qint16 ManualControlSettings::getChannelMax(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ChannelMax[index];
}
void ManualControlSettings::setChannelMax(quint32 index, qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMax[index] != value;
   data.ChannelMax[index] = value;
   mutex->unlock();
   if (changed) emit ChannelMaxChanged(index,value);
}

qint16 ManualControlSettings::getChannelMax_Throttle() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMax[0];
}
void ManualControlSettings::setChannelMax_Throttle(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMax[0] != value;
   data.ChannelMax[0] = value;
   mutex->unlock();
   if (changed) emit ChannelMax_ThrottleChanged(value);
}

qint16 ManualControlSettings::getChannelMax_Roll() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMax[1];
}
void ManualControlSettings::setChannelMax_Roll(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMax[1] != value;
   data.ChannelMax[1] = value;
   mutex->unlock();
   if (changed) emit ChannelMax_RollChanged(value);
}

qint16 ManualControlSettings::getChannelMax_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMax[2];
}
void ManualControlSettings::setChannelMax_Pitch(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMax[2] != value;
   data.ChannelMax[2] = value;
   mutex->unlock();
   if (changed) emit ChannelMax_PitchChanged(value);
}

qint16 ManualControlSettings::getChannelMax_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMax[3];
}
void ManualControlSettings::setChannelMax_Yaw(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMax[3] != value;
   data.ChannelMax[3] = value;
   mutex->unlock();
   if (changed) emit ChannelMax_YawChanged(value);
}

qint16 ManualControlSettings::getChannelMax_FlightMode() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMax[4];
}
void ManualControlSettings::setChannelMax_FlightMode(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMax[4] != value;
   data.ChannelMax[4] = value;
   mutex->unlock();
   if (changed) emit ChannelMax_FlightModeChanged(value);
}

qint16 ManualControlSettings::getChannelMax_Collective() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMax[5];
}
void ManualControlSettings::setChannelMax_Collective(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMax[5] != value;
   data.ChannelMax[5] = value;
   mutex->unlock();
   if (changed) emit ChannelMax_CollectiveChanged(value);
}

qint16 ManualControlSettings::getChannelMax_Accessory0() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMax[6];
}
void ManualControlSettings::setChannelMax_Accessory0(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMax[6] != value;
   data.ChannelMax[6] = value;
   mutex->unlock();
   if (changed) emit ChannelMax_Accessory0Changed(value);
}

qint16 ManualControlSettings::getChannelMax_Accessory1() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMax[7];
}
void ManualControlSettings::setChannelMax_Accessory1(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMax[7] != value;
   data.ChannelMax[7] = value;
   mutex->unlock();
   if (changed) emit ChannelMax_Accessory1Changed(value);
}

qint16 ManualControlSettings::getChannelMax_Accessory2() const
{
   QMutexLocker locker(mutex);
   return data.ChannelMax[8];
}
void ManualControlSettings::setChannelMax_Accessory2(qint16 value)
{
   mutex->lock();
   bool changed = data.ChannelMax[8] != value;
   data.ChannelMax[8] = value;
   mutex->unlock();
   if (changed) emit ChannelMax_Accessory2Changed(value);
}

quint16 ManualControlSettings::getResponseTime(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ResponseTime[index];
}
void ManualControlSettings::setResponseTime(quint32 index, quint16 value)
{
   mutex->lock();
   bool changed = data.ResponseTime[index] != value;
   data.ResponseTime[index] = value;
   mutex->unlock();
   if (changed) emit ResponseTimeChanged(index,value);
}

quint16 ManualControlSettings::getResponseTime_Roll() const
{
   QMutexLocker locker(mutex);
   return data.ResponseTime[0];
}
void ManualControlSettings::setResponseTime_Roll(quint16 value)
{
   mutex->lock();
   bool changed = data.ResponseTime[0] != value;
   data.ResponseTime[0] = value;
   mutex->unlock();
   if (changed) emit ResponseTime_RollChanged(value);
}

quint16 ManualControlSettings::getResponseTime_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.ResponseTime[1];
}
void ManualControlSettings::setResponseTime_Pitch(quint16 value)
{
   mutex->lock();
   bool changed = data.ResponseTime[1] != value;
   data.ResponseTime[1] = value;
   mutex->unlock();
   if (changed) emit ResponseTime_PitchChanged(value);
}

quint16 ManualControlSettings::getResponseTime_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.ResponseTime[2];
}
void ManualControlSettings::setResponseTime_Yaw(quint16 value)
{
   mutex->lock();
   bool changed = data.ResponseTime[2] != value;
   data.ResponseTime[2] = value;
   mutex->unlock();
   if (changed) emit ResponseTime_YawChanged(value);
}

quint16 ManualControlSettings::getResponseTime_Collective() const
{
   QMutexLocker locker(mutex);
   return data.ResponseTime[3];
}
void ManualControlSettings::setResponseTime_Collective(quint16 value)
{
   mutex->lock();
   bool changed = data.ResponseTime[3] != value;
   data.ResponseTime[3] = value;
   mutex->unlock();
   if (changed) emit ResponseTime_CollectiveChanged(value);
}

quint16 ManualControlSettings::getResponseTime_Accessory0() const
{
   QMutexLocker locker(mutex);
   return data.ResponseTime[4];
}
void ManualControlSettings::setResponseTime_Accessory0(quint16 value)
{
   mutex->lock();
   bool changed = data.ResponseTime[4] != value;
   data.ResponseTime[4] = value;
   mutex->unlock();
   if (changed) emit ResponseTime_Accessory0Changed(value);
}

quint16 ManualControlSettings::getResponseTime_Accessory1() const
{
   QMutexLocker locker(mutex);
   return data.ResponseTime[5];
}
void ManualControlSettings::setResponseTime_Accessory1(quint16 value)
{
   mutex->lock();
   bool changed = data.ResponseTime[5] != value;
   data.ResponseTime[5] = value;
   mutex->unlock();
   if (changed) emit ResponseTime_Accessory1Changed(value);
}

quint16 ManualControlSettings::getResponseTime_Accessory2() const
{
   QMutexLocker locker(mutex);
   return data.ResponseTime[6];
}
void ManualControlSettings::setResponseTime_Accessory2(quint16 value)
{
   mutex->lock();
   bool changed = data.ResponseTime[6] != value;
   data.ResponseTime[6] = value;
   mutex->unlock();
   if (changed) emit ResponseTime_Accessory2Changed(value);
}

quint8 ManualControlSettings::getChannelGroups(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ChannelGroups[index];
}
void ManualControlSettings::setChannelGroups(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelGroups[index] != value;
   data.ChannelGroups[index] = value;
   mutex->unlock();
   if (changed) emit ChannelGroupsChanged(index,value);
}

quint8 ManualControlSettings::getChannelGroups_Throttle() const
{
   QMutexLocker locker(mutex);
   return data.ChannelGroups[0];
}
void ManualControlSettings::setChannelGroups_Throttle(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelGroups[0] != value;
   data.ChannelGroups[0] = value;
   mutex->unlock();
   if (changed) emit ChannelGroups_ThrottleChanged(value);
}

quint8 ManualControlSettings::getChannelGroups_Roll() const
{
   QMutexLocker locker(mutex);
   return data.ChannelGroups[1];
}
void ManualControlSettings::setChannelGroups_Roll(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelGroups[1] != value;
   data.ChannelGroups[1] = value;
   mutex->unlock();
   if (changed) emit ChannelGroups_RollChanged(value);
}

quint8 ManualControlSettings::getChannelGroups_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.ChannelGroups[2];
}
void ManualControlSettings::setChannelGroups_Pitch(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelGroups[2] != value;
   data.ChannelGroups[2] = value;
   mutex->unlock();
   if (changed) emit ChannelGroups_PitchChanged(value);
}

quint8 ManualControlSettings::getChannelGroups_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.ChannelGroups[3];
}
void ManualControlSettings::setChannelGroups_Yaw(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelGroups[3] != value;
   data.ChannelGroups[3] = value;
   mutex->unlock();
   if (changed) emit ChannelGroups_YawChanged(value);
}

quint8 ManualControlSettings::getChannelGroups_FlightMode() const
{
   QMutexLocker locker(mutex);
   return data.ChannelGroups[4];
}
void ManualControlSettings::setChannelGroups_FlightMode(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelGroups[4] != value;
   data.ChannelGroups[4] = value;
   mutex->unlock();
   if (changed) emit ChannelGroups_FlightModeChanged(value);
}

quint8 ManualControlSettings::getChannelGroups_Collective() const
{
   QMutexLocker locker(mutex);
   return data.ChannelGroups[5];
}
void ManualControlSettings::setChannelGroups_Collective(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelGroups[5] != value;
   data.ChannelGroups[5] = value;
   mutex->unlock();
   if (changed) emit ChannelGroups_CollectiveChanged(value);
}

quint8 ManualControlSettings::getChannelGroups_Accessory0() const
{
   QMutexLocker locker(mutex);
   return data.ChannelGroups[6];
}
void ManualControlSettings::setChannelGroups_Accessory0(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelGroups[6] != value;
   data.ChannelGroups[6] = value;
   mutex->unlock();
   if (changed) emit ChannelGroups_Accessory0Changed(value);
}

quint8 ManualControlSettings::getChannelGroups_Accessory1() const
{
   QMutexLocker locker(mutex);
   return data.ChannelGroups[7];
}
void ManualControlSettings::setChannelGroups_Accessory1(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelGroups[7] != value;
   data.ChannelGroups[7] = value;
   mutex->unlock();
   if (changed) emit ChannelGroups_Accessory1Changed(value);
}

quint8 ManualControlSettings::getChannelGroups_Accessory2() const
{
   QMutexLocker locker(mutex);
   return data.ChannelGroups[8];
}
void ManualControlSettings::setChannelGroups_Accessory2(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelGroups[8] != value;
   data.ChannelGroups[8] = value;
   mutex->unlock();
   if (changed) emit ChannelGroups_Accessory2Changed(value);
}

quint8 ManualControlSettings::getChannelNumber(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ChannelNumber[index];
}
void ManualControlSettings::setChannelNumber(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelNumber[index] != value;
   data.ChannelNumber[index] = value;
   mutex->unlock();
   if (changed) emit ChannelNumberChanged(index,value);
}

quint8 ManualControlSettings::getChannelNumber_Throttle() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNumber[0];
}
void ManualControlSettings::setChannelNumber_Throttle(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelNumber[0] != value;
   data.ChannelNumber[0] = value;
   mutex->unlock();
   if (changed) emit ChannelNumber_ThrottleChanged(value);
}

quint8 ManualControlSettings::getChannelNumber_Roll() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNumber[1];
}
void ManualControlSettings::setChannelNumber_Roll(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelNumber[1] != value;
   data.ChannelNumber[1] = value;
   mutex->unlock();
   if (changed) emit ChannelNumber_RollChanged(value);
}

quint8 ManualControlSettings::getChannelNumber_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNumber[2];
}
void ManualControlSettings::setChannelNumber_Pitch(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelNumber[2] != value;
   data.ChannelNumber[2] = value;
   mutex->unlock();
   if (changed) emit ChannelNumber_PitchChanged(value);
}

quint8 ManualControlSettings::getChannelNumber_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNumber[3];
}
void ManualControlSettings::setChannelNumber_Yaw(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelNumber[3] != value;
   data.ChannelNumber[3] = value;
   mutex->unlock();
   if (changed) emit ChannelNumber_YawChanged(value);
}

quint8 ManualControlSettings::getChannelNumber_FlightMode() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNumber[4];
}
void ManualControlSettings::setChannelNumber_FlightMode(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelNumber[4] != value;
   data.ChannelNumber[4] = value;
   mutex->unlock();
   if (changed) emit ChannelNumber_FlightModeChanged(value);
}

quint8 ManualControlSettings::getChannelNumber_Collective() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNumber[5];
}
void ManualControlSettings::setChannelNumber_Collective(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelNumber[5] != value;
   data.ChannelNumber[5] = value;
   mutex->unlock();
   if (changed) emit ChannelNumber_CollectiveChanged(value);
}

quint8 ManualControlSettings::getChannelNumber_Accessory0() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNumber[6];
}
void ManualControlSettings::setChannelNumber_Accessory0(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelNumber[6] != value;
   data.ChannelNumber[6] = value;
   mutex->unlock();
   if (changed) emit ChannelNumber_Accessory0Changed(value);
}

quint8 ManualControlSettings::getChannelNumber_Accessory1() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNumber[7];
}
void ManualControlSettings::setChannelNumber_Accessory1(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelNumber[7] != value;
   data.ChannelNumber[7] = value;
   mutex->unlock();
   if (changed) emit ChannelNumber_Accessory1Changed(value);
}

quint8 ManualControlSettings::getChannelNumber_Accessory2() const
{
   QMutexLocker locker(mutex);
   return data.ChannelNumber[8];
}
void ManualControlSettings::setChannelNumber_Accessory2(quint8 value)
{
   mutex->lock();
   bool changed = data.ChannelNumber[8] != value;
   data.ChannelNumber[8] = value;
   mutex->unlock();
   if (changed) emit ChannelNumber_Accessory2Changed(value);
}

quint8 ManualControlSettings::getFlightModeNumber() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeNumber;
}
void ManualControlSettings::setFlightModeNumber(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeNumber != value;
   data.FlightModeNumber = value;
   mutex->unlock();
   if (changed) emit FlightModeNumberChanged(value);
}

qint8 ManualControlSettings::getFailsafeFlightModeSwitchPosition() const
{
   QMutexLocker locker(mutex);
   return data.FailsafeFlightModeSwitchPosition;
}
void ManualControlSettings::setFailsafeFlightModeSwitchPosition(qint8 value)
{
   mutex->lock();
   bool changed = data.FailsafeFlightModeSwitchPosition != value;
   data.FailsafeFlightModeSwitchPosition = value;
   mutex->unlock();
   if (changed) emit FailsafeFlightModeSwitchPositionChanged(value);
}


