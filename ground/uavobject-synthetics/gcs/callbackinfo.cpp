/**
 ******************************************************************************
 *
 * @file       callbackinfo.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: callbackinfo.xml.
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

#include "callbackinfo.h"
#include "uavobjectfield.h"

const QString CallbackInfo::NAME = QString("CallbackInfo");
const QString CallbackInfo::DESCRIPTION = QString("Task information");
const QString CallbackInfo::CATEGORY = QString("System");

/**
 * Constructor
 */
CallbackInfo::CallbackInfo(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList RunningTimeElemNames;
    RunningTimeElemNames.append("EventDispatcher");
    RunningTimeElemNames.append("StateEstimation");
    RunningTimeElemNames.append("AltitudeHold");
    RunningTimeElemNames.append("Stabilization0");
    RunningTimeElemNames.append("Stabilization1");
    RunningTimeElemNames.append("PathFollower");
    RunningTimeElemNames.append("PathPlanner0");
    RunningTimeElemNames.append("PathPlanner1");
    RunningTimeElemNames.append("ManualControl");
    fields.append( new UAVObjectField(QString("RunningTime"), tr(""), QString("#"), UAVObjectField::UINT32, RunningTimeElemNames, QStringList(), QString("")));
    QStringList StackRemainingElemNames;
    StackRemainingElemNames.append("EventDispatcher");
    StackRemainingElemNames.append("StateEstimation");
    StackRemainingElemNames.append("AltitudeHold");
    StackRemainingElemNames.append("Stabilization0");
    StackRemainingElemNames.append("Stabilization1");
    StackRemainingElemNames.append("PathFollower");
    StackRemainingElemNames.append("PathPlanner0");
    StackRemainingElemNames.append("PathPlanner1");
    StackRemainingElemNames.append("ManualControl");
    fields.append( new UAVObjectField(QString("StackRemaining"), tr(""), QString("bytes"), UAVObjectField::INT16, StackRemainingElemNames, QStringList(), QString("")));
    QStringList RunningElemNames;
    RunningElemNames.append("EventDispatcher");
    RunningElemNames.append("StateEstimation");
    RunningElemNames.append("AltitudeHold");
    RunningElemNames.append("Stabilization0");
    RunningElemNames.append("Stabilization1");
    RunningElemNames.append("PathFollower");
    RunningElemNames.append("PathPlanner0");
    RunningElemNames.append("PathPlanner1");
    RunningElemNames.append("ManualControl");
    QStringList RunningEnumOptions;
    RunningEnumOptions.append("False");
    RunningEnumOptions.append("True");
    fields.append( new UAVObjectField(QString("Running"), tr(""), QString("bool"), UAVObjectField::ENUM, RunningElemNames, RunningEnumOptions, QString("")));

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
UAVObject::Metadata CallbackInfo::getDefaultMetadata()
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
void CallbackInfo::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
CallbackInfo::DataFields CallbackInfo::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void CallbackInfo::setData(const DataFields& data)
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

void CallbackInfo::emitNotifications()
{
            //if (data.RunningTime[0] != oldData.RunningTime[0])
            emit RunningTime_EventDispatcherChanged(data.RunningTime[0]);
        //if (data.RunningTime[1] != oldData.RunningTime[1])
            emit RunningTime_StateEstimationChanged(data.RunningTime[1]);
        //if (data.RunningTime[2] != oldData.RunningTime[2])
            emit RunningTime_AltitudeHoldChanged(data.RunningTime[2]);
        //if (data.RunningTime[3] != oldData.RunningTime[3])
            emit RunningTime_Stabilization0Changed(data.RunningTime[3]);
        //if (data.RunningTime[4] != oldData.RunningTime[4])
            emit RunningTime_Stabilization1Changed(data.RunningTime[4]);
        //if (data.RunningTime[5] != oldData.RunningTime[5])
            emit RunningTime_PathFollowerChanged(data.RunningTime[5]);
        //if (data.RunningTime[6] != oldData.RunningTime[6])
            emit RunningTime_PathPlanner0Changed(data.RunningTime[6]);
        //if (data.RunningTime[7] != oldData.RunningTime[7])
            emit RunningTime_PathPlanner1Changed(data.RunningTime[7]);
        //if (data.RunningTime[8] != oldData.RunningTime[8])
            emit RunningTime_ManualControlChanged(data.RunningTime[8]);
        //if (data.StackRemaining[0] != oldData.StackRemaining[0])
            emit StackRemaining_EventDispatcherChanged(data.StackRemaining[0]);
        //if (data.StackRemaining[1] != oldData.StackRemaining[1])
            emit StackRemaining_StateEstimationChanged(data.StackRemaining[1]);
        //if (data.StackRemaining[2] != oldData.StackRemaining[2])
            emit StackRemaining_AltitudeHoldChanged(data.StackRemaining[2]);
        //if (data.StackRemaining[3] != oldData.StackRemaining[3])
            emit StackRemaining_Stabilization0Changed(data.StackRemaining[3]);
        //if (data.StackRemaining[4] != oldData.StackRemaining[4])
            emit StackRemaining_Stabilization1Changed(data.StackRemaining[4]);
        //if (data.StackRemaining[5] != oldData.StackRemaining[5])
            emit StackRemaining_PathFollowerChanged(data.StackRemaining[5]);
        //if (data.StackRemaining[6] != oldData.StackRemaining[6])
            emit StackRemaining_PathPlanner0Changed(data.StackRemaining[6]);
        //if (data.StackRemaining[7] != oldData.StackRemaining[7])
            emit StackRemaining_PathPlanner1Changed(data.StackRemaining[7]);
        //if (data.StackRemaining[8] != oldData.StackRemaining[8])
            emit StackRemaining_ManualControlChanged(data.StackRemaining[8]);
        //if (data.Running[0] != oldData.Running[0])
            emit Running_EventDispatcherChanged(data.Running[0]);
        //if (data.Running[1] != oldData.Running[1])
            emit Running_StateEstimationChanged(data.Running[1]);
        //if (data.Running[2] != oldData.Running[2])
            emit Running_AltitudeHoldChanged(data.Running[2]);
        //if (data.Running[3] != oldData.Running[3])
            emit Running_Stabilization0Changed(data.Running[3]);
        //if (data.Running[4] != oldData.Running[4])
            emit Running_Stabilization1Changed(data.Running[4]);
        //if (data.Running[5] != oldData.Running[5])
            emit Running_PathFollowerChanged(data.Running[5]);
        //if (data.Running[6] != oldData.Running[6])
            emit Running_PathPlanner0Changed(data.Running[6]);
        //if (data.Running[7] != oldData.Running[7])
            emit Running_PathPlanner1Changed(data.Running[7]);
        //if (data.Running[8] != oldData.Running[8])
            emit Running_ManualControlChanged(data.Running[8]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *CallbackInfo::clone(quint32 instID)
{
    CallbackInfo *obj = new CallbackInfo();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *CallbackInfo::dirtyClone()
{
    CallbackInfo *obj = new CallbackInfo();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
CallbackInfo *CallbackInfo::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<CallbackInfo *>(objMngr->getObject(CallbackInfo::OBJID, instID));
}

quint32 CallbackInfo::getRunningTime(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[index];
}
void CallbackInfo::setRunningTime(quint32 index, quint32 value)
{
   mutex->lock();
   bool changed = data.RunningTime[index] != value;
   data.RunningTime[index] = value;
   mutex->unlock();
   if (changed) emit RunningTimeChanged(index,value);
}

quint32 CallbackInfo::getRunningTime_EventDispatcher() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[0];
}
void CallbackInfo::setRunningTime_EventDispatcher(quint32 value)
{
   mutex->lock();
   bool changed = data.RunningTime[0] != value;
   data.RunningTime[0] = value;
   mutex->unlock();
   if (changed) emit RunningTime_EventDispatcherChanged(value);
}

quint32 CallbackInfo::getRunningTime_StateEstimation() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[1];
}
void CallbackInfo::setRunningTime_StateEstimation(quint32 value)
{
   mutex->lock();
   bool changed = data.RunningTime[1] != value;
   data.RunningTime[1] = value;
   mutex->unlock();
   if (changed) emit RunningTime_StateEstimationChanged(value);
}

quint32 CallbackInfo::getRunningTime_AltitudeHold() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[2];
}
void CallbackInfo::setRunningTime_AltitudeHold(quint32 value)
{
   mutex->lock();
   bool changed = data.RunningTime[2] != value;
   data.RunningTime[2] = value;
   mutex->unlock();
   if (changed) emit RunningTime_AltitudeHoldChanged(value);
}

quint32 CallbackInfo::getRunningTime_Stabilization0() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[3];
}
void CallbackInfo::setRunningTime_Stabilization0(quint32 value)
{
   mutex->lock();
   bool changed = data.RunningTime[3] != value;
   data.RunningTime[3] = value;
   mutex->unlock();
   if (changed) emit RunningTime_Stabilization0Changed(value);
}

quint32 CallbackInfo::getRunningTime_Stabilization1() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[4];
}
void CallbackInfo::setRunningTime_Stabilization1(quint32 value)
{
   mutex->lock();
   bool changed = data.RunningTime[4] != value;
   data.RunningTime[4] = value;
   mutex->unlock();
   if (changed) emit RunningTime_Stabilization1Changed(value);
}

quint32 CallbackInfo::getRunningTime_PathFollower() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[5];
}
void CallbackInfo::setRunningTime_PathFollower(quint32 value)
{
   mutex->lock();
   bool changed = data.RunningTime[5] != value;
   data.RunningTime[5] = value;
   mutex->unlock();
   if (changed) emit RunningTime_PathFollowerChanged(value);
}

quint32 CallbackInfo::getRunningTime_PathPlanner0() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[6];
}
void CallbackInfo::setRunningTime_PathPlanner0(quint32 value)
{
   mutex->lock();
   bool changed = data.RunningTime[6] != value;
   data.RunningTime[6] = value;
   mutex->unlock();
   if (changed) emit RunningTime_PathPlanner0Changed(value);
}

quint32 CallbackInfo::getRunningTime_PathPlanner1() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[7];
}
void CallbackInfo::setRunningTime_PathPlanner1(quint32 value)
{
   mutex->lock();
   bool changed = data.RunningTime[7] != value;
   data.RunningTime[7] = value;
   mutex->unlock();
   if (changed) emit RunningTime_PathPlanner1Changed(value);
}

quint32 CallbackInfo::getRunningTime_ManualControl() const
{
   QMutexLocker locker(mutex);
   return data.RunningTime[8];
}
void CallbackInfo::setRunningTime_ManualControl(quint32 value)
{
   mutex->lock();
   bool changed = data.RunningTime[8] != value;
   data.RunningTime[8] = value;
   mutex->unlock();
   if (changed) emit RunningTime_ManualControlChanged(value);
}

qint16 CallbackInfo::getStackRemaining(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[index];
}
void CallbackInfo::setStackRemaining(quint32 index, qint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[index] != value;
   data.StackRemaining[index] = value;
   mutex->unlock();
   if (changed) emit StackRemainingChanged(index,value);
}

qint16 CallbackInfo::getStackRemaining_EventDispatcher() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[0];
}
void CallbackInfo::setStackRemaining_EventDispatcher(qint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[0] != value;
   data.StackRemaining[0] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_EventDispatcherChanged(value);
}

qint16 CallbackInfo::getStackRemaining_StateEstimation() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[1];
}
void CallbackInfo::setStackRemaining_StateEstimation(qint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[1] != value;
   data.StackRemaining[1] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_StateEstimationChanged(value);
}

qint16 CallbackInfo::getStackRemaining_AltitudeHold() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[2];
}
void CallbackInfo::setStackRemaining_AltitudeHold(qint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[2] != value;
   data.StackRemaining[2] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_AltitudeHoldChanged(value);
}

qint16 CallbackInfo::getStackRemaining_Stabilization0() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[3];
}
void CallbackInfo::setStackRemaining_Stabilization0(qint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[3] != value;
   data.StackRemaining[3] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_Stabilization0Changed(value);
}

qint16 CallbackInfo::getStackRemaining_Stabilization1() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[4];
}
void CallbackInfo::setStackRemaining_Stabilization1(qint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[4] != value;
   data.StackRemaining[4] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_Stabilization1Changed(value);
}

qint16 CallbackInfo::getStackRemaining_PathFollower() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[5];
}
void CallbackInfo::setStackRemaining_PathFollower(qint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[5] != value;
   data.StackRemaining[5] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_PathFollowerChanged(value);
}

qint16 CallbackInfo::getStackRemaining_PathPlanner0() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[6];
}
void CallbackInfo::setStackRemaining_PathPlanner0(qint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[6] != value;
   data.StackRemaining[6] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_PathPlanner0Changed(value);
}

qint16 CallbackInfo::getStackRemaining_PathPlanner1() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[7];
}
void CallbackInfo::setStackRemaining_PathPlanner1(qint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[7] != value;
   data.StackRemaining[7] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_PathPlanner1Changed(value);
}

qint16 CallbackInfo::getStackRemaining_ManualControl() const
{
   QMutexLocker locker(mutex);
   return data.StackRemaining[8];
}
void CallbackInfo::setStackRemaining_ManualControl(qint16 value)
{
   mutex->lock();
   bool changed = data.StackRemaining[8] != value;
   data.StackRemaining[8] = value;
   mutex->unlock();
   if (changed) emit StackRemaining_ManualControlChanged(value);
}

quint8 CallbackInfo::getRunning(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Running[index];
}
void CallbackInfo::setRunning(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.Running[index] != value;
   data.Running[index] = value;
   mutex->unlock();
   if (changed) emit RunningChanged(index,value);
}

quint8 CallbackInfo::getRunning_EventDispatcher() const
{
   QMutexLocker locker(mutex);
   return data.Running[0];
}
void CallbackInfo::setRunning_EventDispatcher(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[0] != value;
   data.Running[0] = value;
   mutex->unlock();
   if (changed) emit Running_EventDispatcherChanged(value);
}

quint8 CallbackInfo::getRunning_StateEstimation() const
{
   QMutexLocker locker(mutex);
   return data.Running[1];
}
void CallbackInfo::setRunning_StateEstimation(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[1] != value;
   data.Running[1] = value;
   mutex->unlock();
   if (changed) emit Running_StateEstimationChanged(value);
}

quint8 CallbackInfo::getRunning_AltitudeHold() const
{
   QMutexLocker locker(mutex);
   return data.Running[2];
}
void CallbackInfo::setRunning_AltitudeHold(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[2] != value;
   data.Running[2] = value;
   mutex->unlock();
   if (changed) emit Running_AltitudeHoldChanged(value);
}

quint8 CallbackInfo::getRunning_Stabilization0() const
{
   QMutexLocker locker(mutex);
   return data.Running[3];
}
void CallbackInfo::setRunning_Stabilization0(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[3] != value;
   data.Running[3] = value;
   mutex->unlock();
   if (changed) emit Running_Stabilization0Changed(value);
}

quint8 CallbackInfo::getRunning_Stabilization1() const
{
   QMutexLocker locker(mutex);
   return data.Running[4];
}
void CallbackInfo::setRunning_Stabilization1(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[4] != value;
   data.Running[4] = value;
   mutex->unlock();
   if (changed) emit Running_Stabilization1Changed(value);
}

quint8 CallbackInfo::getRunning_PathFollower() const
{
   QMutexLocker locker(mutex);
   return data.Running[5];
}
void CallbackInfo::setRunning_PathFollower(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[5] != value;
   data.Running[5] = value;
   mutex->unlock();
   if (changed) emit Running_PathFollowerChanged(value);
}

quint8 CallbackInfo::getRunning_PathPlanner0() const
{
   QMutexLocker locker(mutex);
   return data.Running[6];
}
void CallbackInfo::setRunning_PathPlanner0(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[6] != value;
   data.Running[6] = value;
   mutex->unlock();
   if (changed) emit Running_PathPlanner0Changed(value);
}

quint8 CallbackInfo::getRunning_PathPlanner1() const
{
   QMutexLocker locker(mutex);
   return data.Running[7];
}
void CallbackInfo::setRunning_PathPlanner1(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[7] != value;
   data.Running[7] = value;
   mutex->unlock();
   if (changed) emit Running_PathPlanner1Changed(value);
}

quint8 CallbackInfo::getRunning_ManualControl() const
{
   QMutexLocker locker(mutex);
   return data.Running[8];
}
void CallbackInfo::setRunning_ManualControl(quint8 value)
{
   mutex->lock();
   bool changed = data.Running[8] != value;
   data.Running[8] = value;
   mutex->unlock();
   if (changed) emit Running_ManualControlChanged(value);
}


