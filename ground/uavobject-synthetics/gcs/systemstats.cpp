/**
 ******************************************************************************
 *
 * @file       systemstats.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: systemstats.xml.
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

#include "systemstats.h"
#include "uavobjectfield.h"

const QString SystemStats::NAME = QString("SystemStats");
const QString SystemStats::DESCRIPTION = QString("CPU and memory usage from OpenPilot computer. ");
const QString SystemStats::CATEGORY = QString("System");

/**
 * Constructor
 */
SystemStats::SystemStats(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList FlightTimeElemNames;
    FlightTimeElemNames.append("0");
    fields.append( new UAVObjectField(QString("FlightTime"), tr(""), QString("ms"), UAVObjectField::UINT32, FlightTimeElemNames, QStringList(), QString("")));
    QStringList HeapRemainingElemNames;
    HeapRemainingElemNames.append("0");
    fields.append( new UAVObjectField(QString("HeapRemaining"), tr(""), QString("bytes"), UAVObjectField::UINT32, HeapRemainingElemNames, QStringList(), QString("")));
    QStringList EventSystemWarningIDElemNames;
    EventSystemWarningIDElemNames.append("0");
    fields.append( new UAVObjectField(QString("EventSystemWarningID"), tr(""), QString("uavoid"), UAVObjectField::UINT32, EventSystemWarningIDElemNames, QStringList(), QString("")));
    QStringList ObjectManagerCallbackIDElemNames;
    ObjectManagerCallbackIDElemNames.append("0");
    fields.append( new UAVObjectField(QString("ObjectManagerCallbackID"), tr(""), QString("uavoid"), UAVObjectField::UINT32, ObjectManagerCallbackIDElemNames, QStringList(), QString("")));
    QStringList ObjectManagerQueueIDElemNames;
    ObjectManagerQueueIDElemNames.append("0");
    fields.append( new UAVObjectField(QString("ObjectManagerQueueID"), tr(""), QString("uavoid"), UAVObjectField::UINT32, ObjectManagerQueueIDElemNames, QStringList(), QString("")));
    QStringList IRQStackRemainingElemNames;
    IRQStackRemainingElemNames.append("0");
    fields.append( new UAVObjectField(QString("IRQStackRemaining"), tr(""), QString("bytes"), UAVObjectField::UINT16, IRQStackRemainingElemNames, QStringList(), QString("")));
    QStringList SystemModStackRemainingElemNames;
    SystemModStackRemainingElemNames.append("0");
    fields.append( new UAVObjectField(QString("SystemModStackRemaining"), tr(""), QString("bytes"), UAVObjectField::UINT16, SystemModStackRemainingElemNames, QStringList(), QString("")));
    QStringList SysSlotsFreeElemNames;
    SysSlotsFreeElemNames.append("0");
    fields.append( new UAVObjectField(QString("SysSlotsFree"), tr(""), QString("slots"), UAVObjectField::UINT16, SysSlotsFreeElemNames, QStringList(), QString("")));
    QStringList SysSlotsActiveElemNames;
    SysSlotsActiveElemNames.append("0");
    fields.append( new UAVObjectField(QString("SysSlotsActive"), tr(""), QString("slots"), UAVObjectField::UINT16, SysSlotsActiveElemNames, QStringList(), QString("")));
    QStringList UsrSlotsFreeElemNames;
    UsrSlotsFreeElemNames.append("0");
    fields.append( new UAVObjectField(QString("UsrSlotsFree"), tr(""), QString("slots"), UAVObjectField::UINT16, UsrSlotsFreeElemNames, QStringList(), QString("")));
    QStringList UsrSlotsActiveElemNames;
    UsrSlotsActiveElemNames.append("0");
    fields.append( new UAVObjectField(QString("UsrSlotsActive"), tr(""), QString("slots"), UAVObjectField::UINT16, UsrSlotsActiveElemNames, QStringList(), QString("")));
    QStringList CPULoadElemNames;
    CPULoadElemNames.append("0");
    fields.append( new UAVObjectField(QString("CPULoad"), tr(""), QString("%"), UAVObjectField::UINT8, CPULoadElemNames, QStringList(), QString("")));
    QStringList CPUTempElemNames;
    CPUTempElemNames.append("0");
    fields.append( new UAVObjectField(QString("CPUTemp"), tr(""), QString("C"), UAVObjectField::INT8, CPUTempElemNames, QStringList(), QString("")));

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
UAVObject::Metadata SystemStats::getDefaultMetadata()
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
void SystemStats::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
SystemStats::DataFields SystemStats::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void SystemStats::setData(const DataFields& data)
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

void SystemStats::emitNotifications()
{
            //if (data.FlightTime != oldData.FlightTime)
            emit FlightTimeChanged(data.FlightTime);
        //if (data.HeapRemaining != oldData.HeapRemaining)
            emit HeapRemainingChanged(data.HeapRemaining);
        //if (data.EventSystemWarningID != oldData.EventSystemWarningID)
            emit EventSystemWarningIDChanged(data.EventSystemWarningID);
        //if (data.ObjectManagerCallbackID != oldData.ObjectManagerCallbackID)
            emit ObjectManagerCallbackIDChanged(data.ObjectManagerCallbackID);
        //if (data.ObjectManagerQueueID != oldData.ObjectManagerQueueID)
            emit ObjectManagerQueueIDChanged(data.ObjectManagerQueueID);
        //if (data.IRQStackRemaining != oldData.IRQStackRemaining)
            emit IRQStackRemainingChanged(data.IRQStackRemaining);
        //if (data.SystemModStackRemaining != oldData.SystemModStackRemaining)
            emit SystemModStackRemainingChanged(data.SystemModStackRemaining);
        //if (data.SysSlotsFree != oldData.SysSlotsFree)
            emit SysSlotsFreeChanged(data.SysSlotsFree);
        //if (data.SysSlotsActive != oldData.SysSlotsActive)
            emit SysSlotsActiveChanged(data.SysSlotsActive);
        //if (data.UsrSlotsFree != oldData.UsrSlotsFree)
            emit UsrSlotsFreeChanged(data.UsrSlotsFree);
        //if (data.UsrSlotsActive != oldData.UsrSlotsActive)
            emit UsrSlotsActiveChanged(data.UsrSlotsActive);
        //if (data.CPULoad != oldData.CPULoad)
            emit CPULoadChanged(data.CPULoad);
        //if (data.CPUTemp != oldData.CPUTemp)
            emit CPUTempChanged(data.CPUTemp);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *SystemStats::clone(quint32 instID)
{
    SystemStats *obj = new SystemStats();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *SystemStats::dirtyClone()
{
    SystemStats *obj = new SystemStats();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
SystemStats *SystemStats::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<SystemStats *>(objMngr->getObject(SystemStats::OBJID, instID));
}

quint32 SystemStats::getFlightTime() const
{
   QMutexLocker locker(mutex);
   return data.FlightTime;
}
void SystemStats::setFlightTime(quint32 value)
{
   mutex->lock();
   bool changed = data.FlightTime != value;
   data.FlightTime = value;
   mutex->unlock();
   if (changed) emit FlightTimeChanged(value);
}

quint32 SystemStats::getHeapRemaining() const
{
   QMutexLocker locker(mutex);
   return data.HeapRemaining;
}
void SystemStats::setHeapRemaining(quint32 value)
{
   mutex->lock();
   bool changed = data.HeapRemaining != value;
   data.HeapRemaining = value;
   mutex->unlock();
   if (changed) emit HeapRemainingChanged(value);
}

quint32 SystemStats::getEventSystemWarningID() const
{
   QMutexLocker locker(mutex);
   return data.EventSystemWarningID;
}
void SystemStats::setEventSystemWarningID(quint32 value)
{
   mutex->lock();
   bool changed = data.EventSystemWarningID != value;
   data.EventSystemWarningID = value;
   mutex->unlock();
   if (changed) emit EventSystemWarningIDChanged(value);
}

quint32 SystemStats::getObjectManagerCallbackID() const
{
   QMutexLocker locker(mutex);
   return data.ObjectManagerCallbackID;
}
void SystemStats::setObjectManagerCallbackID(quint32 value)
{
   mutex->lock();
   bool changed = data.ObjectManagerCallbackID != value;
   data.ObjectManagerCallbackID = value;
   mutex->unlock();
   if (changed) emit ObjectManagerCallbackIDChanged(value);
}

quint32 SystemStats::getObjectManagerQueueID() const
{
   QMutexLocker locker(mutex);
   return data.ObjectManagerQueueID;
}
void SystemStats::setObjectManagerQueueID(quint32 value)
{
   mutex->lock();
   bool changed = data.ObjectManagerQueueID != value;
   data.ObjectManagerQueueID = value;
   mutex->unlock();
   if (changed) emit ObjectManagerQueueIDChanged(value);
}

quint16 SystemStats::getIRQStackRemaining() const
{
   QMutexLocker locker(mutex);
   return data.IRQStackRemaining;
}
void SystemStats::setIRQStackRemaining(quint16 value)
{
   mutex->lock();
   bool changed = data.IRQStackRemaining != value;
   data.IRQStackRemaining = value;
   mutex->unlock();
   if (changed) emit IRQStackRemainingChanged(value);
}

quint16 SystemStats::getSystemModStackRemaining() const
{
   QMutexLocker locker(mutex);
   return data.SystemModStackRemaining;
}
void SystemStats::setSystemModStackRemaining(quint16 value)
{
   mutex->lock();
   bool changed = data.SystemModStackRemaining != value;
   data.SystemModStackRemaining = value;
   mutex->unlock();
   if (changed) emit SystemModStackRemainingChanged(value);
}

quint16 SystemStats::getSysSlotsFree() const
{
   QMutexLocker locker(mutex);
   return data.SysSlotsFree;
}
void SystemStats::setSysSlotsFree(quint16 value)
{
   mutex->lock();
   bool changed = data.SysSlotsFree != value;
   data.SysSlotsFree = value;
   mutex->unlock();
   if (changed) emit SysSlotsFreeChanged(value);
}

quint16 SystemStats::getSysSlotsActive() const
{
   QMutexLocker locker(mutex);
   return data.SysSlotsActive;
}
void SystemStats::setSysSlotsActive(quint16 value)
{
   mutex->lock();
   bool changed = data.SysSlotsActive != value;
   data.SysSlotsActive = value;
   mutex->unlock();
   if (changed) emit SysSlotsActiveChanged(value);
}

quint16 SystemStats::getUsrSlotsFree() const
{
   QMutexLocker locker(mutex);
   return data.UsrSlotsFree;
}
void SystemStats::setUsrSlotsFree(quint16 value)
{
   mutex->lock();
   bool changed = data.UsrSlotsFree != value;
   data.UsrSlotsFree = value;
   mutex->unlock();
   if (changed) emit UsrSlotsFreeChanged(value);
}

quint16 SystemStats::getUsrSlotsActive() const
{
   QMutexLocker locker(mutex);
   return data.UsrSlotsActive;
}
void SystemStats::setUsrSlotsActive(quint16 value)
{
   mutex->lock();
   bool changed = data.UsrSlotsActive != value;
   data.UsrSlotsActive = value;
   mutex->unlock();
   if (changed) emit UsrSlotsActiveChanged(value);
}

quint8 SystemStats::getCPULoad() const
{
   QMutexLocker locker(mutex);
   return data.CPULoad;
}
void SystemStats::setCPULoad(quint8 value)
{
   mutex->lock();
   bool changed = data.CPULoad != value;
   data.CPULoad = value;
   mutex->unlock();
   if (changed) emit CPULoadChanged(value);
}

qint8 SystemStats::getCPUTemp() const
{
   QMutexLocker locker(mutex);
   return data.CPUTemp;
}
void SystemStats::setCPUTemp(qint8 value)
{
   mutex->lock();
   bool changed = data.CPUTemp != value;
   data.CPUTemp = value;
   mutex->unlock();
   if (changed) emit CPUTempChanged(value);
}


