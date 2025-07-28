/**
 ******************************************************************************
 *
 * @file       systemalarms.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: systemalarms.xml.
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

#include "systemalarms.h"
#include "uavobjectfield.h"

const QString SystemAlarms::NAME = QString("SystemAlarms");
const QString SystemAlarms::DESCRIPTION = QString("Alarms from OpenPilot to indicate failure conditions or warnings.  Set by various modules.  Some modules may have a module defined Status and Substatus fields that details its condition.");
const QString SystemAlarms::CATEGORY = QString("System");

/**
 * Constructor
 */
SystemAlarms::SystemAlarms(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList AlarmElemNames;
    AlarmElemNames.append("SystemConfiguration");
    AlarmElemNames.append("BootFault");
    AlarmElemNames.append("OutOfMemory");
    AlarmElemNames.append("StackOverflow");
    AlarmElemNames.append("CPUOverload");
    AlarmElemNames.append("EventSystem");
    AlarmElemNames.append("Telemetry");
    AlarmElemNames.append("Receiver");
    AlarmElemNames.append("ManualControl");
    AlarmElemNames.append("Actuator");
    AlarmElemNames.append("Attitude");
    AlarmElemNames.append("Sensors");
    AlarmElemNames.append("Magnetometer");
    AlarmElemNames.append("Airspeed");
    AlarmElemNames.append("Stabilization");
    AlarmElemNames.append("Guidance");
    AlarmElemNames.append("PathPlan");
    AlarmElemNames.append("Battery");
    AlarmElemNames.append("FlightTime");
    AlarmElemNames.append("I2C");
    AlarmElemNames.append("GPS");
    QStringList AlarmEnumOptions;
    AlarmEnumOptions.append("Uninitialised");
    AlarmEnumOptions.append("OK");
    AlarmEnumOptions.append("Warning");
    AlarmEnumOptions.append("Critical");
    AlarmEnumOptions.append("Error");
    fields.append( new UAVObjectField(QString("Alarm"), tr(""), QString(""), UAVObjectField::ENUM, AlarmElemNames, AlarmEnumOptions, QString("")));
    QStringList ExtendedAlarmStatusElemNames;
    ExtendedAlarmStatusElemNames.append("SystemConfiguration");
    ExtendedAlarmStatusElemNames.append("BootFault");
    QStringList ExtendedAlarmStatusEnumOptions;
    ExtendedAlarmStatusEnumOptions.append("None");
    ExtendedAlarmStatusEnumOptions.append("RebootRequired");
    ExtendedAlarmStatusEnumOptions.append("FlightMode");
    ExtendedAlarmStatusEnumOptions.append("UnsupportedConfig_OneShot");
    ExtendedAlarmStatusEnumOptions.append("BadThrottleOrCollectiveInputRange");
    fields.append( new UAVObjectField(QString("ExtendedAlarmStatus"), tr(""), QString(""), UAVObjectField::ENUM, ExtendedAlarmStatusElemNames, ExtendedAlarmStatusEnumOptions, QString("")));
    QStringList ExtendedAlarmSubStatusElemNames;
    ExtendedAlarmSubStatusElemNames.append("SystemConfiguration");
    ExtendedAlarmSubStatusElemNames.append("BootFault");
    fields.append( new UAVObjectField(QString("ExtendedAlarmSubStatus"), tr(""), QString(""), UAVObjectField::UINT8, ExtendedAlarmSubStatusElemNames, QStringList(), QString("")));

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
UAVObject::Metadata SystemAlarms::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        0 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        0 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_PERIODIC << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_LOGGING_UPDATE_MODE_SHIFT;
    metadata.flightTelemetryUpdatePeriod = 1000;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void SystemAlarms::setDefaultFieldValues()
{
    data.Alarm[0] = 0;
    data.Alarm[1] = 0;
    data.Alarm[2] = 0;
    data.Alarm[3] = 0;
    data.Alarm[4] = 0;
    data.Alarm[5] = 0;
    data.Alarm[6] = 0;
    data.Alarm[7] = 0;
    data.Alarm[8] = 0;
    data.Alarm[9] = 0;
    data.Alarm[10] = 0;
    data.Alarm[11] = 0;
    data.Alarm[12] = 0;
    data.Alarm[13] = 0;
    data.Alarm[14] = 0;
    data.Alarm[15] = 0;
    data.Alarm[16] = 0;
    data.Alarm[17] = 0;
    data.Alarm[18] = 0;
    data.Alarm[19] = 0;
    data.Alarm[20] = 0;
    data.ExtendedAlarmStatus[0] = 0;
    data.ExtendedAlarmStatus[1] = 0;
    data.ExtendedAlarmSubStatus[0] = 0;
    data.ExtendedAlarmSubStatus[1] = 0;

}

/**
 * Get the object data fields
 */
SystemAlarms::DataFields SystemAlarms::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void SystemAlarms::setData(const DataFields& data)
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

void SystemAlarms::emitNotifications()
{
            //if (data.Alarm[0] != oldData.Alarm[0])
            emit Alarm_SystemConfigurationChanged(data.Alarm[0]);
        //if (data.Alarm[1] != oldData.Alarm[1])
            emit Alarm_BootFaultChanged(data.Alarm[1]);
        //if (data.Alarm[2] != oldData.Alarm[2])
            emit Alarm_OutOfMemoryChanged(data.Alarm[2]);
        //if (data.Alarm[3] != oldData.Alarm[3])
            emit Alarm_StackOverflowChanged(data.Alarm[3]);
        //if (data.Alarm[4] != oldData.Alarm[4])
            emit Alarm_CPUOverloadChanged(data.Alarm[4]);
        //if (data.Alarm[5] != oldData.Alarm[5])
            emit Alarm_EventSystemChanged(data.Alarm[5]);
        //if (data.Alarm[6] != oldData.Alarm[6])
            emit Alarm_TelemetryChanged(data.Alarm[6]);
        //if (data.Alarm[7] != oldData.Alarm[7])
            emit Alarm_ReceiverChanged(data.Alarm[7]);
        //if (data.Alarm[8] != oldData.Alarm[8])
            emit Alarm_ManualControlChanged(data.Alarm[8]);
        //if (data.Alarm[9] != oldData.Alarm[9])
            emit Alarm_ActuatorChanged(data.Alarm[9]);
        //if (data.Alarm[10] != oldData.Alarm[10])
            emit Alarm_AttitudeChanged(data.Alarm[10]);
        //if (data.Alarm[11] != oldData.Alarm[11])
            emit Alarm_SensorsChanged(data.Alarm[11]);
        //if (data.Alarm[12] != oldData.Alarm[12])
            emit Alarm_MagnetometerChanged(data.Alarm[12]);
        //if (data.Alarm[13] != oldData.Alarm[13])
            emit Alarm_AirspeedChanged(data.Alarm[13]);
        //if (data.Alarm[14] != oldData.Alarm[14])
            emit Alarm_StabilizationChanged(data.Alarm[14]);
        //if (data.Alarm[15] != oldData.Alarm[15])
            emit Alarm_GuidanceChanged(data.Alarm[15]);
        //if (data.Alarm[16] != oldData.Alarm[16])
            emit Alarm_PathPlanChanged(data.Alarm[16]);
        //if (data.Alarm[17] != oldData.Alarm[17])
            emit Alarm_BatteryChanged(data.Alarm[17]);
        //if (data.Alarm[18] != oldData.Alarm[18])
            emit Alarm_FlightTimeChanged(data.Alarm[18]);
        //if (data.Alarm[19] != oldData.Alarm[19])
            emit Alarm_I2CChanged(data.Alarm[19]);
        //if (data.Alarm[20] != oldData.Alarm[20])
            emit Alarm_GPSChanged(data.Alarm[20]);
        //if (data.ExtendedAlarmStatus[0] != oldData.ExtendedAlarmStatus[0])
            emit ExtendedAlarmStatus_SystemConfigurationChanged(data.ExtendedAlarmStatus[0]);
        //if (data.ExtendedAlarmStatus[1] != oldData.ExtendedAlarmStatus[1])
            emit ExtendedAlarmStatus_BootFaultChanged(data.ExtendedAlarmStatus[1]);
        //if (data.ExtendedAlarmSubStatus[0] != oldData.ExtendedAlarmSubStatus[0])
            emit ExtendedAlarmSubStatus_SystemConfigurationChanged(data.ExtendedAlarmSubStatus[0]);
        //if (data.ExtendedAlarmSubStatus[1] != oldData.ExtendedAlarmSubStatus[1])
            emit ExtendedAlarmSubStatus_BootFaultChanged(data.ExtendedAlarmSubStatus[1]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *SystemAlarms::clone(quint32 instID)
{
    SystemAlarms *obj = new SystemAlarms();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *SystemAlarms::dirtyClone()
{
    SystemAlarms *obj = new SystemAlarms();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
SystemAlarms *SystemAlarms::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<SystemAlarms *>(objMngr->getObject(SystemAlarms::OBJID, instID));
}

quint8 SystemAlarms::getAlarm(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Alarm[index];
}
void SystemAlarms::setAlarm(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[index] != value;
   data.Alarm[index] = value;
   mutex->unlock();
   if (changed) emit AlarmChanged(index,value);
}

quint8 SystemAlarms::getAlarm_SystemConfiguration() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[0];
}
void SystemAlarms::setAlarm_SystemConfiguration(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[0] != value;
   data.Alarm[0] = value;
   mutex->unlock();
   if (changed) emit Alarm_SystemConfigurationChanged(value);
}

quint8 SystemAlarms::getAlarm_BootFault() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[1];
}
void SystemAlarms::setAlarm_BootFault(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[1] != value;
   data.Alarm[1] = value;
   mutex->unlock();
   if (changed) emit Alarm_BootFaultChanged(value);
}

quint8 SystemAlarms::getAlarm_OutOfMemory() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[2];
}
void SystemAlarms::setAlarm_OutOfMemory(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[2] != value;
   data.Alarm[2] = value;
   mutex->unlock();
   if (changed) emit Alarm_OutOfMemoryChanged(value);
}

quint8 SystemAlarms::getAlarm_StackOverflow() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[3];
}
void SystemAlarms::setAlarm_StackOverflow(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[3] != value;
   data.Alarm[3] = value;
   mutex->unlock();
   if (changed) emit Alarm_StackOverflowChanged(value);
}

quint8 SystemAlarms::getAlarm_CPUOverload() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[4];
}
void SystemAlarms::setAlarm_CPUOverload(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[4] != value;
   data.Alarm[4] = value;
   mutex->unlock();
   if (changed) emit Alarm_CPUOverloadChanged(value);
}

quint8 SystemAlarms::getAlarm_EventSystem() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[5];
}
void SystemAlarms::setAlarm_EventSystem(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[5] != value;
   data.Alarm[5] = value;
   mutex->unlock();
   if (changed) emit Alarm_EventSystemChanged(value);
}

quint8 SystemAlarms::getAlarm_Telemetry() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[6];
}
void SystemAlarms::setAlarm_Telemetry(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[6] != value;
   data.Alarm[6] = value;
   mutex->unlock();
   if (changed) emit Alarm_TelemetryChanged(value);
}

quint8 SystemAlarms::getAlarm_Receiver() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[7];
}
void SystemAlarms::setAlarm_Receiver(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[7] != value;
   data.Alarm[7] = value;
   mutex->unlock();
   if (changed) emit Alarm_ReceiverChanged(value);
}

quint8 SystemAlarms::getAlarm_ManualControl() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[8];
}
void SystemAlarms::setAlarm_ManualControl(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[8] != value;
   data.Alarm[8] = value;
   mutex->unlock();
   if (changed) emit Alarm_ManualControlChanged(value);
}

quint8 SystemAlarms::getAlarm_Actuator() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[9];
}
void SystemAlarms::setAlarm_Actuator(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[9] != value;
   data.Alarm[9] = value;
   mutex->unlock();
   if (changed) emit Alarm_ActuatorChanged(value);
}

quint8 SystemAlarms::getAlarm_Attitude() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[10];
}
void SystemAlarms::setAlarm_Attitude(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[10] != value;
   data.Alarm[10] = value;
   mutex->unlock();
   if (changed) emit Alarm_AttitudeChanged(value);
}

quint8 SystemAlarms::getAlarm_Sensors() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[11];
}
void SystemAlarms::setAlarm_Sensors(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[11] != value;
   data.Alarm[11] = value;
   mutex->unlock();
   if (changed) emit Alarm_SensorsChanged(value);
}

quint8 SystemAlarms::getAlarm_Magnetometer() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[12];
}
void SystemAlarms::setAlarm_Magnetometer(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[12] != value;
   data.Alarm[12] = value;
   mutex->unlock();
   if (changed) emit Alarm_MagnetometerChanged(value);
}

quint8 SystemAlarms::getAlarm_Airspeed() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[13];
}
void SystemAlarms::setAlarm_Airspeed(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[13] != value;
   data.Alarm[13] = value;
   mutex->unlock();
   if (changed) emit Alarm_AirspeedChanged(value);
}

quint8 SystemAlarms::getAlarm_Stabilization() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[14];
}
void SystemAlarms::setAlarm_Stabilization(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[14] != value;
   data.Alarm[14] = value;
   mutex->unlock();
   if (changed) emit Alarm_StabilizationChanged(value);
}

quint8 SystemAlarms::getAlarm_Guidance() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[15];
}
void SystemAlarms::setAlarm_Guidance(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[15] != value;
   data.Alarm[15] = value;
   mutex->unlock();
   if (changed) emit Alarm_GuidanceChanged(value);
}

quint8 SystemAlarms::getAlarm_PathPlan() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[16];
}
void SystemAlarms::setAlarm_PathPlan(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[16] != value;
   data.Alarm[16] = value;
   mutex->unlock();
   if (changed) emit Alarm_PathPlanChanged(value);
}

quint8 SystemAlarms::getAlarm_Battery() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[17];
}
void SystemAlarms::setAlarm_Battery(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[17] != value;
   data.Alarm[17] = value;
   mutex->unlock();
   if (changed) emit Alarm_BatteryChanged(value);
}

quint8 SystemAlarms::getAlarm_FlightTime() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[18];
}
void SystemAlarms::setAlarm_FlightTime(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[18] != value;
   data.Alarm[18] = value;
   mutex->unlock();
   if (changed) emit Alarm_FlightTimeChanged(value);
}

quint8 SystemAlarms::getAlarm_I2C() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[19];
}
void SystemAlarms::setAlarm_I2C(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[19] != value;
   data.Alarm[19] = value;
   mutex->unlock();
   if (changed) emit Alarm_I2CChanged(value);
}

quint8 SystemAlarms::getAlarm_GPS() const
{
   QMutexLocker locker(mutex);
   return data.Alarm[20];
}
void SystemAlarms::setAlarm_GPS(quint8 value)
{
   mutex->lock();
   bool changed = data.Alarm[20] != value;
   data.Alarm[20] = value;
   mutex->unlock();
   if (changed) emit Alarm_GPSChanged(value);
}

quint8 SystemAlarms::getExtendedAlarmStatus(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ExtendedAlarmStatus[index];
}
void SystemAlarms::setExtendedAlarmStatus(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.ExtendedAlarmStatus[index] != value;
   data.ExtendedAlarmStatus[index] = value;
   mutex->unlock();
   if (changed) emit ExtendedAlarmStatusChanged(index,value);
}

quint8 SystemAlarms::getExtendedAlarmStatus_SystemConfiguration() const
{
   QMutexLocker locker(mutex);
   return data.ExtendedAlarmStatus[0];
}
void SystemAlarms::setExtendedAlarmStatus_SystemConfiguration(quint8 value)
{
   mutex->lock();
   bool changed = data.ExtendedAlarmStatus[0] != value;
   data.ExtendedAlarmStatus[0] = value;
   mutex->unlock();
   if (changed) emit ExtendedAlarmStatus_SystemConfigurationChanged(value);
}

quint8 SystemAlarms::getExtendedAlarmStatus_BootFault() const
{
   QMutexLocker locker(mutex);
   return data.ExtendedAlarmStatus[1];
}
void SystemAlarms::setExtendedAlarmStatus_BootFault(quint8 value)
{
   mutex->lock();
   bool changed = data.ExtendedAlarmStatus[1] != value;
   data.ExtendedAlarmStatus[1] = value;
   mutex->unlock();
   if (changed) emit ExtendedAlarmStatus_BootFaultChanged(value);
}

quint8 SystemAlarms::getExtendedAlarmSubStatus(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ExtendedAlarmSubStatus[index];
}
void SystemAlarms::setExtendedAlarmSubStatus(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.ExtendedAlarmSubStatus[index] != value;
   data.ExtendedAlarmSubStatus[index] = value;
   mutex->unlock();
   if (changed) emit ExtendedAlarmSubStatusChanged(index,value);
}

quint8 SystemAlarms::getExtendedAlarmSubStatus_SystemConfiguration() const
{
   QMutexLocker locker(mutex);
   return data.ExtendedAlarmSubStatus[0];
}
void SystemAlarms::setExtendedAlarmSubStatus_SystemConfiguration(quint8 value)
{
   mutex->lock();
   bool changed = data.ExtendedAlarmSubStatus[0] != value;
   data.ExtendedAlarmSubStatus[0] = value;
   mutex->unlock();
   if (changed) emit ExtendedAlarmSubStatus_SystemConfigurationChanged(value);
}

quint8 SystemAlarms::getExtendedAlarmSubStatus_BootFault() const
{
   QMutexLocker locker(mutex);
   return data.ExtendedAlarmSubStatus[1];
}
void SystemAlarms::setExtendedAlarmSubStatus_BootFault(quint8 value)
{
   mutex->lock();
   bool changed = data.ExtendedAlarmSubStatus[1] != value;
   data.ExtendedAlarmSubStatus[1] = value;
   mutex->unlock();
   if (changed) emit ExtendedAlarmSubStatus_BootFaultChanged(value);
}


