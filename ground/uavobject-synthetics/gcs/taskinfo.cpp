/**
 ******************************************************************************
 *
 * @file       taskinfo.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: taskinfo.xml.
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

#include "taskinfo.h"
#include "uavobjectfield.h"

const QString TaskInfo::NAME = QString("TaskInfo");
const QString TaskInfo::DESCRIPTION = QString("Task information");
const QString TaskInfo::CATEGORY = QString("System");

/**
 * Constructor
 */
TaskInfo::TaskInfo(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList StackRemainingElemNames;
    StackRemainingElemNames.append("System");
    StackRemainingElemNames.append("CallbackScheduler0");
    StackRemainingElemNames.append("CallbackScheduler1");
    StackRemainingElemNames.append("CallbackScheduler2");
    StackRemainingElemNames.append("CallbackScheduler3");
    StackRemainingElemNames.append("Receiver");
    StackRemainingElemNames.append("Stabilization");
    StackRemainingElemNames.append("Actuator");
    StackRemainingElemNames.append("Sensors");
    StackRemainingElemNames.append("Attitude");
    StackRemainingElemNames.append("Altitude");
    StackRemainingElemNames.append("Airspeed");
    StackRemainingElemNames.append("MagBaro");
    StackRemainingElemNames.append("FlightPlan");
    StackRemainingElemNames.append("TelemetryTx");
    StackRemainingElemNames.append("TelemetryRx");
    StackRemainingElemNames.append("RadioRx");
    StackRemainingElemNames.append("Com2UsbBridge");
    StackRemainingElemNames.append("Usb2ComBridge");
    StackRemainingElemNames.append("GPS");
    StackRemainingElemNames.append("OSDGen");
    fields.append( new UAVObjectField(QString("StackRemaining"), tr(""), QString("bytes"), UAVObjectField::UINT16, StackRemainingElemNames, QStringList(), QString("")));
    QStringList RunningElemNames;
    RunningElemNames.append("System");
    RunningElemNames.append("CallbackScheduler0");
    RunningElemNames.append("CallbackScheduler1");
    RunningElemNames.append("CallbackScheduler2");
    RunningElemNames.append("CallbackScheduler3");
    RunningElemNames.append("Receiver");
    RunningElemNames.append("Stabilization");
    RunningElemNames.append("Actuator");
    RunningElemNames.append("Sensors");
    RunningElemNames.append("Attitude");
    RunningElemNames.append("Altitude");
    RunningElemNames.append("Airspeed");
    RunningElemNames.append("MagBaro");
    RunningElemNames.append("FlightPlan");
    RunningElemNames.append("TelemetryTx");
    RunningElemNames.append("TelemetryRx");
    RunningElemNames.append("RadioRx");
    RunningElemNames.append("Com2UsbBridge");
    RunningElemNames.append("Usb2ComBridge");
    RunningElemNames.append("GPS");
    RunningElemNames.append("OSDGen");
    QStringList RunningEnumOptions;
    RunningEnumOptions.append("False");
    RunningEnumOptions.append("True");
    fields.append( new UAVObjectField(QString("Running"), tr(""), QString("bool"), UAVObjectField::ENUM, RunningElemNames, RunningEnumOptions, QString("")));
    QStringList RunningTimeElemNames;
    RunningTimeElemNames.append("System");
    RunningTimeElemNames.append("CallbackScheduler0");
    RunningTimeElemNames.append("CallbackScheduler1");
    RunningTimeElemNames.append("CallbackScheduler2");
    RunningTimeElemNames.append("CallbackScheduler3");
    RunningTimeElemNames.append("Receiver");
    RunningTimeElemNames.append("Stabilization");
    RunningTimeElemNames.append("Actuator");
    RunningTimeElemNames.append("Sensors");
    RunningTimeElemNames.append("Attitude");
    RunningTimeElemNames.append("Altitude");
    RunningTimeElemNames.append("Airspeed");
    RunningTimeElemNames.append("MagBaro");
    RunningTimeElemNames.append("FlightPlan");
    RunningTimeElemNames.append("TelemetryTx");
    RunningTimeElemNames.append("TelemetryRx");
    RunningTimeElemNames.append("RadioRx");
    RunningTimeElemNames.append("Com2UsbBridge");
    RunningTimeElemNames.append("Usb2ComBridge");
    RunningTimeElemNames.append("GPS");
    RunningTimeElemNames.append("OSDGen");
    fields.append( new UAVObjectField(QString("RunningTime"), tr(""), QString("%"), UAVObjectField::UINT8, RunningTimeElemNames, QStringList(), QString("")));

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
UAVObject::Metadata TaskInfo::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READONLY << UAVOBJ_GCS_ACCESS_SHIFT |
        0 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        0 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_PERIODIC << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_ONCHANGE << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_LOGGING_UPDATE_MODE_SHIFT;
    metadata.flightTelemetryUpdatePeriod = 10000;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void TaskInfo::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
TaskInfo::DataFields TaskInfo::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void TaskInfo::setData(const DataFields& data)
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

void TaskInfo::emitNotifications()
{
            //if (data.StackRemaining[0] != oldData.StackRemaining[0])
            emit StackRemaining_SystemChanged(data.StackRemaining[0]);
        //if (data.StackRemaining[1] != oldData.StackRemaining[1])
            emit StackRemaining_CallbackScheduler0Changed(data.StackRemaining[1]);
        //if (data.StackRemaining[2] != oldData.StackRemaining[2])
            emit StackRemaining_CallbackScheduler1Changed(data.StackRemaining[2]);
        //if (data.StackRemaining[3] != oldData.StackRemaining[3])
            emit StackRemaining_CallbackScheduler2Changed(data.StackRemaining[3]);
        //if (data.StackRemaining[4] != oldData.StackRemaining[4])
            emit StackRemaining_CallbackScheduler3Changed(data.StackRemaining[4]);
        //if (data.StackRemaining[5] != oldData.StackRemaining[5])
            emit StackRemaining_ReceiverChanged(data.StackRemaining[5]);
        //if (data.StackRemaining[6] != oldData.StackRemaining[6])
            emit StackRemaining_StabilizationChanged(data.StackRemaining[6]);
        //if (data.StackRemaining[7] != oldData.StackRemaining[7])
            emit StackRemaining_ActuatorChanged(data.StackRemaining[7]);
        //if (data.StackRemaining[8] != oldData.StackRemaining[8])
            emit StackRemaining_SensorsChanged(data.StackRemaining[8]);
        //if (data.StackRemaining[9] != oldData.StackRemaining[9])
            emit StackRemaining_AttitudeChanged(data.StackRemaining[9]);
        //if (data.StackRemaining[10] != oldData.StackRemaining[10])
            emit StackRemaining_AltitudeChanged(data.StackRemaining[10]);
        //if (data.StackRemaining[11] != oldData.StackRemaining[11])
            emit StackRemaining_AirspeedChanged(data.StackRemaining[11]);
        //if (data.StackRemaining[12] != oldData.StackRemaining[12])
            emit StackRemaining_MagBaroChanged(data.StackRemaining[12]);
        //if (data.StackRemaining[13] != oldData.StackRemaining[13])
            emit StackRemaining_FlightPlanChanged(data.StackRemaining[13]);
        //if (data.StackRemaining[14] != oldData.StackRemaining[14])
            emit StackRemaining_TelemetryTxChanged(data.StackRemaining[14]);
        //if (data.StackRemaining[15] != oldData.StackRemaining[15])
            emit StackRemaining_TelemetryRxChanged(data.StackRemaining[15]);
        //if (data.StackRemaining[16] != oldData.StackRemaining[16])
            emit StackRemaining_RadioRxChanged(data.StackRemaining[16]);
        //if (data.StackRemaining[17] != oldData.StackRemaining[17])
            emit StackRemaining_Com2UsbBridgeChanged(data.StackRemaining[17]);
        //if (data.StackRemaining[18] != oldData.StackRemaining[18])
            emit StackRemaining_Usb2ComBridgeChanged(data.StackRemaining[18]);
        //if (data.StackRemaining[19] != oldData.StackRemaining[19])
            emit StackRemaining_GPSChanged(data.StackRemaining[19]);
        //if (data.StackRemaining[20] != oldData.StackRemaining[20])
            emit StackRemaining_OSDGenChanged(data.StackRemaining[20]);
        //if (data.Running[0] != oldData.Running[0])
            emit Running_SystemChanged(data.Running[0]);
        //if (data.Running[1] != oldData.Running[1])
            emit Running_CallbackScheduler0Changed(data.Running[1]);
        //if (data.Running[2] != oldData.Running[2])
            emit Running_CallbackScheduler1Changed(data.Running[2]);
        //if (data.Running[3] != oldData.Running[3])
            emit Running_CallbackScheduler2Changed(data.Running[3]);
        //if (data.Running[4] != oldData.Running[4])
            emit Running_CallbackScheduler3Changed(data.Running[4]);
        //if (data.Running[5] != oldData.Running[5])
            emit Running_ReceiverChanged(data.Running[5]);
        //if (data.Running[6] != oldData.Running[6])
            emit Running_StabilizationChanged(data.Running[6]);
        //if (data.Running[7] != oldData.Running[7])
            emit Running_ActuatorChanged(data.Running[7]);
        //if (data.Running[8] != oldData.Running[8])
            emit Running_SensorsChanged(data.Running[8]);
        //if (data.Running[9] != oldData.Running[9])
            emit Running_AttitudeChanged(data.Running[9]);
        //if (data.Running[10] != oldData.Running[10])
            emit Running_AltitudeChanged(data.Running[10]);
        //if (data.Running[11] != oldData.Running[11])
            emit Running_AirspeedChanged(data.Running[11]);
        //if (data.Running[12] != oldData.Running[12])
            emit Running_MagBaroChanged(data.Running[12]);
        //if (data.Running[13] != oldData.Running[13])
            emit Running_FlightPlanChanged(data.Running[13]);
        //if (data.Running[14] != oldData.Running[14])
            emit Running_TelemetryTxChanged(data.Running[14]);
        //if (data.Running[15] != oldData.Running[15])
            emit Running_TelemetryRxChanged(data.Running[15]);
        //if (data.Running[16] != oldData.Running[16])
            emit Running_RadioRxChanged(data.Running[16]);
        //if (data.Running[17] != oldData.Running[17])
            emit Running_Com2UsbBridgeChanged(data.Running[17]);
        //if (data.Running[18] != oldData.Running[18])
            emit Running_Usb2ComBridgeChanged(data.Running[18]);
        //if (data.Running[19] != oldData.Running[19])
            emit Running_GPSChanged(data.Running[19]);
        //if (data.Running[20] != oldData.Running[20])
            emit Running_OSDGenChanged(data.Running[20]);
        //if (data.RunningTime[0] != oldData.RunningTime[0])
            emit RunningTime_SystemChanged(data.RunningTime[0]);
        //if (data.RunningTime[1] != oldData.RunningTime[1])
            emit RunningTime_CallbackScheduler0Changed(data.RunningTime[1]);
        //if (data.RunningTime[2] != oldData.RunningTime[2])
            emit RunningTime_CallbackScheduler1Changed(data.RunningTime[2]);
        //if (data.RunningTime[3] != oldData.RunningTime[3])
            emit RunningTime_CallbackScheduler2Changed(data.RunningTime[3]);
        //if (data.RunningTime[4] != oldData.RunningTime[4])
            emit RunningTime_CallbackScheduler3Changed(data.RunningTime[4]);
        //if (data.RunningTime[5] != oldData.RunningTime[5])
            emit RunningTime_ReceiverChanged(data.RunningTime[5]);
        //if (data.RunningTime[6] != oldData.RunningTime[6])
            emit RunningTime_StabilizationChanged(data.RunningTime[6]);
        //if (data.RunningTime[7] != oldData.RunningTime[7])
            emit RunningTime_ActuatorChanged(data.RunningTime[7]);
        //if (data.RunningTime[8] != oldData.RunningTime[8])
            emit RunningTime_SensorsChanged(data.RunningTime[8]);
        //if (data.RunningTime[9] != oldData.RunningTime[9])
            emit RunningTime_AttitudeChanged(data.RunningTime[9]);
        //if (data.RunningTime[10] != oldData.RunningTime[10])
            emit RunningTime_AltitudeChanged(data.RunningTime[10]);
        //if (data.RunningTime[11] != oldData.RunningTime[11])
            emit RunningTime_AirspeedChanged(data.RunningTime[11]);
        //if (data.RunningTime[12] != oldData.RunningTime[12])
            emit RunningTime_MagBaroChanged(data.RunningTime[12]);
        //if (data.RunningTime[13] != oldData.RunningTime[13])
            emit RunningTime_FlightPlanChanged(data.RunningTime[13]);
        //if (data.RunningTime[14] != oldData.RunningTime[14])
            emit RunningTime_TelemetryTxChanged(data.RunningTime[14]);
        //if (data.RunningTime[15] != oldData.RunningTime[15])
            emit RunningTime_TelemetryRxChanged(data.RunningTime[15]);
        //if (data.RunningTime[16] != oldData.RunningTime[16])
            emit RunningTime_RadioRxChanged(data.RunningTime[16]);
        //if (data.RunningTime[17] != oldData.RunningTime[17])
            emit RunningTime_Com2UsbBridgeChanged(data.RunningTime[17]);
        //if (data.RunningTime[18] != oldData.RunningTime[18])
            emit RunningTime_Usb2ComBridgeChanged(data.RunningTime[18]);
        //if (data.RunningTime[19] != oldData.RunningTime[19])
            emit RunningTime_GPSChanged(data.RunningTime[19]);
        //if (data.RunningTime[20] != oldData.RunningTime[20])
            emit RunningTime_OSDGenChanged(data.RunningTime[20]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *TaskInfo::clone(quint32 instID)
{
    TaskInfo *obj = new TaskInfo();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *TaskInfo::dirtyClone()
{
    TaskInfo *obj = new TaskInfo();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
TaskInfo *TaskInfo::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<TaskInfo *>(objMngr->getObject(TaskInfo::OBJID, instID));
}

quint16 TaskInfo::getStackRemaining(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[index];
}
void TaskInfo::setStackRemaining(quint32 index, quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[index] != value;
   data.StackRemaining[index] = value;
   mutex->unlock();
   if (changed) emit StackRemainingChanged(index,value);
}

quint16 TaskInfo::getStackRemaining_System() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[0];
}
void TaskInfo::setStackRemaining_System(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[0] != value;
   data.StackRemaining[0] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_SystemChanged(value);
}

quint16 TaskInfo::getStackRemaining_CallbackScheduler0() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[1];
}
void TaskInfo::setStackRemaining_CallbackScheduler0(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[1] != value;
   data.StackRemaining[1] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_CallbackScheduler0Changed(value);
}

quint16 TaskInfo::getStackRemaining_CallbackScheduler1() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[2];
}
void TaskInfo::setStackRemaining_CallbackScheduler1(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[2] != value;
   data.StackRemaining[2] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_CallbackScheduler1Changed(value);
}

quint16 TaskInfo::getStackRemaining_CallbackScheduler2() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[3];
}
void TaskInfo::setStackRemaining_CallbackScheduler2(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[3] != value;
   data.StackRemaining[3] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_CallbackScheduler2Changed(value);
}

quint16 TaskInfo::getStackRemaining_CallbackScheduler3() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[4];
}
void TaskInfo::setStackRemaining_CallbackScheduler3(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[4] != value;
   data.StackRemaining[4] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_CallbackScheduler3Changed(value);
}

quint16 TaskInfo::getStackRemaining_Receiver() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[5];
}
void TaskInfo::setStackRemaining_Receiver(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[5] != value;
   data.StackRemaining[5] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_ReceiverChanged(value);
}

quint16 TaskInfo::getStackRemaining_Stabilization() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[6];
}
void TaskInfo::setStackRemaining_Stabilization(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[6] != value;
   data.StackRemaining[6] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_StabilizationChanged(value);
}

quint16 TaskInfo::getStackRemaining_Actuator() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[7];
}
void TaskInfo::setStackRemaining_Actuator(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[7] != value;
   data.StackRemaining[7] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_ActuatorChanged(value);
}

quint16 TaskInfo::getStackRemaining_Sensors() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[8];
}
void TaskInfo::setStackRemaining_Sensors(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[8] != value;
   data.StackRemaining[8] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_SensorsChanged(value);
}

quint16 TaskInfo::getStackRemaining_Attitude() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[9];
}
void TaskInfo::setStackRemaining_Attitude(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[9] != value;
   data.StackRemaining[9] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_AttitudeChanged(value);
}

quint16 TaskInfo::getStackRemaining_Altitude() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[10];
}
void TaskInfo::setStackRemaining_Altitude(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[10] != value;
   data.StackRemaining[10] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_AltitudeChanged(value);
}

quint16 TaskInfo::getStackRemaining_Airspeed() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[11];
}
void TaskInfo::setStackRemaining_Airspeed(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[11] != value;
   data.StackRemaining[11] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_AirspeedChanged(value);
}

quint16 TaskInfo::getStackRemaining_MagBaro() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[12];
}
void TaskInfo::setStackRemaining_MagBaro(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[12] != value;
   data.StackRemaining[12] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_MagBaroChanged(value);
}

quint16 TaskInfo::getStackRemaining_FlightPlan() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[13];
}
void TaskInfo::setStackRemaining_FlightPlan(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[13] != value;
   data.StackRemaining[13] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_FlightPlanChanged(value);
}

quint16 TaskInfo::getStackRemaining_TelemetryTx() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[14];
}
void TaskInfo::setStackRemaining_TelemetryTx(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[14] != value;
   data.StackRemaining[14] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_TelemetryTxChanged(value);
}

quint16 TaskInfo::getStackRemaining_TelemetryRx() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[15];
}
void TaskInfo::setStackRemaining_TelemetryRx(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[15] != value;
   data.StackRemaining[15] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_TelemetryRxChanged(value);
}

quint16 TaskInfo::getStackRemaining_RadioRx() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[16];
}
void TaskInfo::setStackRemaining_RadioRx(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[16] != value;
   data.StackRemaining[16] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_RadioRxChanged(value);
}

quint16 TaskInfo::getStackRemaining_Com2UsbBridge() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[17];
}
void TaskInfo::setStackRemaining_Com2UsbBridge(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[17] != value;
   data.StackRemaining[17] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_Com2UsbBridgeChanged(value);
}

quint16 TaskInfo::getStackRemaining_Usb2ComBridge() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[18];
}
void TaskInfo::setStackRemaining_Usb2ComBridge(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[18] != value;
   data.StackRemaining[18] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_Usb2ComBridgeChanged(value);
}

quint16 TaskInfo::getStackRemaining_GPS() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[19];
}
void TaskInfo::setStackRemaining_GPS(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[19] != value;
   data.StackRemaining[19] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_GPSChanged(value);
}

quint16 TaskInfo::getStackRemaining_OSDGen() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[20];
}
void TaskInfo::setStackRemaining_OSDGen(quint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[20] != value;
   data.StackRemaining[20] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_OSDGenChanged(value);
}

quint8 TaskInfo::getRunning(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Running[index];
}
void TaskInfo::setRunning(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.Running[index] != value;
   data.Running[index] = value;
   mutex->unlock();
   if (changed) emit RunningChanged(index,value);
}

quint8 TaskInfo::getRunning_System() const
{
   QMutexLocker locker(mutex);
   return data.Running[0];
}
void TaskInfo::setRunning_System(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[0] != value;
   data.Running[0] = value;
   mutex->unlock();
   if (changed) emit Running_SystemChanged(value);
}

quint8 TaskInfo::getRunning_CallbackScheduler0() const
{
   QMutexLocker locker(mutex);
   return data.Running[1];
}
void TaskInfo::setRunning_CallbackScheduler0(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[1] != value;
   data.Running[1] = value;
   mutex->unlock();
   if (changed) emit Running_CallbackScheduler0Changed(value);
}

quint8 TaskInfo::getRunning_CallbackScheduler1() const
{
   QMutexLocker locker(mutex);
   return data.Running[2];
}
void TaskInfo::setRunning_CallbackScheduler1(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[2] != value;
   data.Running[2] = value;
   mutex->unlock();
   if (changed) emit Running_CallbackScheduler1Changed(value);
}

quint8 TaskInfo::getRunning_CallbackScheduler2() const
{
   QMutexLocker locker(mutex);
   return data.Running[3];
}
void TaskInfo::setRunning_CallbackScheduler2(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[3] != value;
   data.Running[3] = value;
   mutex->unlock();
   if (changed) emit Running_CallbackScheduler2Changed(value);
}

quint8 TaskInfo::getRunning_CallbackScheduler3() const
{
   QMutexLocker locker(mutex);
   return data.Running[4];
}
void TaskInfo::setRunning_CallbackScheduler3(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[4] != value;
   data.Running[4] = value;
   mutex->unlock();
   if (changed) emit Running_CallbackScheduler3Changed(value);
}

quint8 TaskInfo::getRunning_Receiver() const
{
   QMutexLocker locker(mutex);
   return data.Running[5];
}
void TaskInfo::setRunning_Receiver(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[5] != value;
   data.Running[5] = value;
   mutex->unlock();
   if (changed) emit Running_ReceiverChanged(value);
}

quint8 TaskInfo::getRunning_Stabilization() const
{
   QMutexLocker locker(mutex);
   return data.Running[6];
}
void TaskInfo::setRunning_Stabilization(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[6] != value;
   data.Running[6] = value;
   mutex->unlock();
   if (changed) emit Running_StabilizationChanged(value);
}

quint8 TaskInfo::getRunning_Actuator() const
{
   QMutexLocker locker(mutex);
   return data.Running[7];
}
void TaskInfo::setRunning_Actuator(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[7] != value;
   data.Running[7] = value;
   mutex->unlock();
   if (changed) emit Running_ActuatorChanged(value);
}

quint8 TaskInfo::getRunning_Sensors() const
{
   QMutexLocker locker(mutex);
   return data.Running[8];
}
void TaskInfo::setRunning_Sensors(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[8] != value;
   data.Running[8] = value;
   mutex->unlock();
   if (changed) emit Running_SensorsChanged(value);
}

quint8 TaskInfo::getRunning_Attitude() const
{
   QMutexLocker locker(mutex);
   return data.Running[9];
}
void TaskInfo::setRunning_Attitude(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[9] != value;
   data.Running[9] = value;
   mutex->unlock();
   if (changed) emit Running_AttitudeChanged(value);
}

quint8 TaskInfo::getRunning_Altitude() const
{
   QMutexLocker locker(mutex);
   return data.Running[10];
}
void TaskInfo::setRunning_Altitude(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[10] != value;
   data.Running[10] = value;
   mutex->unlock();
   if (changed) emit Running_AltitudeChanged(value);
}

quint8 TaskInfo::getRunning_Airspeed() const
{
   QMutexLocker locker(mutex);
   return data.Running[11];
}
void TaskInfo::setRunning_Airspeed(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[11] != value;
   data.Running[11] = value;
   mutex->unlock();
   if (changed) emit Running_AirspeedChanged(value);
}

quint8 TaskInfo::getRunning_MagBaro() const
{
   QMutexLocker locker(mutex);
   return data.Running[12];
}
void TaskInfo::setRunning_MagBaro(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[12] != value;
   data.Running[12] = value;
   mutex->unlock();
   if (changed) emit Running_MagBaroChanged(value);
}

quint8 TaskInfo::getRunning_FlightPlan() const
{
   QMutexLocker locker(mutex);
   return data.Running[13];
}
void TaskInfo::setRunning_FlightPlan(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[13] != value;
   data.Running[13] = value;
   mutex->unlock();
   if (changed) emit Running_FlightPlanChanged(value);
}

quint8 TaskInfo::getRunning_TelemetryTx() const
{
   QMutexLocker locker(mutex);
   return data.Running[14];
}
void TaskInfo::setRunning_TelemetryTx(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[14] != value;
   data.Running[14] = value;
   mutex->unlock();
   if (changed) emit Running_TelemetryTxChanged(value);
}

quint8 TaskInfo::getRunning_TelemetryRx() const
{
   QMutexLocker locker(mutex);
   return data.Running[15];
}
void TaskInfo::setRunning_TelemetryRx(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[15] != value;
   data.Running[15] = value;
   mutex->unlock();
   if (changed) emit Running_TelemetryRxChanged(value);
}

quint8 TaskInfo::getRunning_RadioRx() const
{
   QMutexLocker locker(mutex);
   return data.Running[16];
}
void TaskInfo::setRunning_RadioRx(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[16] != value;
   data.Running[16] = value;
   mutex->unlock();
   if (changed) emit Running_RadioRxChanged(value);
}

quint8 TaskInfo::getRunning_Com2UsbBridge() const
{
   QMutexLocker locker(mutex);
   return data.Running[17];
}
void TaskInfo::setRunning_Com2UsbBridge(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[17] != value;
   data.Running[17] = value;
   mutex->unlock();
   if (changed) emit Running_Com2UsbBridgeChanged(value);
}

quint8 TaskInfo::getRunning_Usb2ComBridge() const
{
   QMutexLocker locker(mutex);
   return data.Running[18];
}
void TaskInfo::setRunning_Usb2ComBridge(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[18] != value;
   data.Running[18] = value;
   mutex->unlock();
   if (changed) emit Running_Usb2ComBridgeChanged(value);
}

quint8 TaskInfo::getRunning_GPS() const
{
   QMutexLocker locker(mutex);
   return data.Running[19];
}
void TaskInfo::setRunning_GPS(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[19] != value;
   data.Running[19] = value;
   mutex->unlock();
   if (changed) emit Running_GPSChanged(value);
}

quint8 TaskInfo::getRunning_OSDGen() const
{
   QMutexLocker locker(mutex);
   return data.Running[20];
}
void TaskInfo::setRunning_OSDGen(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[20] != value;
   data.Running[20] = value;
   mutex->unlock();
   if (changed) emit Running_OSDGenChanged(value);
}

quint8 TaskInfo::getRunningTime(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[index];
}
void TaskInfo::setRunningTime(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[index] != value;
   data.RunningTime[index] = value;
   mutex->unlock();
   if (changed) emit RunningTimeChanged(index,value);
}

quint8 TaskInfo::getRunningTime_System() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[0];
}
void TaskInfo::setRunningTime_System(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[0] != value;
   data.RunningTime[0] = value;
   mutex->unlock();
   if (changed) emit RunningTime_SystemChanged(value);
}

quint8 TaskInfo::getRunningTime_CallbackScheduler0() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[1];
}
void TaskInfo::setRunningTime_CallbackScheduler0(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[1] != value;
   data.RunningTime[1] = value;
   mutex->unlock();
   if (changed) emit RunningTime_CallbackScheduler0Changed(value);
}

quint8 TaskInfo::getRunningTime_CallbackScheduler1() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[2];
}
void TaskInfo::setRunningTime_CallbackScheduler1(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[2] != value;
   data.RunningTime[2] = value;
   mutex->unlock();
   if (changed) emit RunningTime_CallbackScheduler1Changed(value);
}

quint8 TaskInfo::getRunningTime_CallbackScheduler2() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[3];
}
void TaskInfo::setRunningTime_CallbackScheduler2(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[3] != value;
   data.RunningTime[3] = value;
   mutex->unlock();
   if (changed) emit RunningTime_CallbackScheduler2Changed(value);
}

quint8 TaskInfo::getRunningTime_CallbackScheduler3() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[4];
}
void TaskInfo::setRunningTime_CallbackScheduler3(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[4] != value;
   data.RunningTime[4] = value;
   mutex->unlock();
   if (changed) emit RunningTime_CallbackScheduler3Changed(value);
}

quint8 TaskInfo::getRunningTime_Receiver() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[5];
}
void TaskInfo::setRunningTime_Receiver(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[5] != value;
   data.RunningTime[5] = value;
   mutex->unlock();
   if (changed) emit RunningTime_ReceiverChanged(value);
}

quint8 TaskInfo::getRunningTime_Stabilization() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[6];
}
void TaskInfo::setRunningTime_Stabilization(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[6] != value;
   data.RunningTime[6] = value;
   mutex->unlock();
   if (changed) emit RunningTime_StabilizationChanged(value);
}

quint8 TaskInfo::getRunningTime_Actuator() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[7];
}
void TaskInfo::setRunningTime_Actuator(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[7] != value;
   data.RunningTime[7] = value;
   mutex->unlock();
   if (changed) emit RunningTime_ActuatorChanged(value);
}

quint8 TaskInfo::getRunningTime_Sensors() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[8];
}
void TaskInfo::setRunningTime_Sensors(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[8] != value;
   data.RunningTime[8] = value;
   mutex->unlock();
   if (changed) emit RunningTime_SensorsChanged(value);
}

quint8 TaskInfo::getRunningTime_Attitude() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[9];
}
void TaskInfo::setRunningTime_Attitude(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[9] != value;
   data.RunningTime[9] = value;
   mutex->unlock();
   if (changed) emit RunningTime_AttitudeChanged(value);
}

quint8 TaskInfo::getRunningTime_Altitude() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[10];
}
void TaskInfo::setRunningTime_Altitude(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[10] != value;
   data.RunningTime[10] = value;
   mutex->unlock();
   if (changed) emit RunningTime_AltitudeChanged(value);
}

quint8 TaskInfo::getRunningTime_Airspeed() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[11];
}
void TaskInfo::setRunningTime_Airspeed(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[11] != value;
   data.RunningTime[11] = value;
   mutex->unlock();
   if (changed) emit RunningTime_AirspeedChanged(value);
}

quint8 TaskInfo::getRunningTime_MagBaro() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[12];
}
void TaskInfo::setRunningTime_MagBaro(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[12] != value;
   data.RunningTime[12] = value;
   mutex->unlock();
   if (changed) emit RunningTime_MagBaroChanged(value);
}

quint8 TaskInfo::getRunningTime_FlightPlan() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[13];
}
void TaskInfo::setRunningTime_FlightPlan(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[13] != value;
   data.RunningTime[13] = value;
   mutex->unlock();
   if (changed) emit RunningTime_FlightPlanChanged(value);
}

quint8 TaskInfo::getRunningTime_TelemetryTx() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[14];
}
void TaskInfo::setRunningTime_TelemetryTx(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[14] != value;
   data.RunningTime[14] = value;
   mutex->unlock();
   if (changed) emit RunningTime_TelemetryTxChanged(value);
}

quint8 TaskInfo::getRunningTime_TelemetryRx() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[15];
}
void TaskInfo::setRunningTime_TelemetryRx(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[15] != value;
   data.RunningTime[15] = value;
   mutex->unlock();
   if (changed) emit RunningTime_TelemetryRxChanged(value);
}

quint8 TaskInfo::getRunningTime_RadioRx() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[16];
}
void TaskInfo::setRunningTime_RadioRx(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[16] != value;
   data.RunningTime[16] = value;
   mutex->unlock();
   if (changed) emit RunningTime_RadioRxChanged(value);
}

quint8 TaskInfo::getRunningTime_Com2UsbBridge() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[17];
}
void TaskInfo::setRunningTime_Com2UsbBridge(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[17] != value;
   data.RunningTime[17] = value;
   mutex->unlock();
   if (changed) emit RunningTime_Com2UsbBridgeChanged(value);
}

quint8 TaskInfo::getRunningTime_Usb2ComBridge() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[18];
}
void TaskInfo::setRunningTime_Usb2ComBridge(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[18] != value;
   data.RunningTime[18] = value;
   mutex->unlock();
   if (changed) emit RunningTime_Usb2ComBridgeChanged(value);
}

quint8 TaskInfo::getRunningTime_GPS() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[19];
}
void TaskInfo::setRunningTime_GPS(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[19] != value;
   data.RunningTime[19] = value;
   mutex->unlock();
   if (changed) emit RunningTime_GPSChanged(value);
}

quint8 TaskInfo::getRunningTime_OSDGen() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[20];
}
void TaskInfo::setRunningTime_OSDGen(quint8 value)
{
   mutex->lock();
   bool changed = data.RunningTime[20] != value;
   data.RunningTime[20] = value;
   mutex->unlock();
   if (changed) emit RunningTime_OSDGenChanged(value);
}


