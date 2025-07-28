/**
 ******************************************************************************
 *
 * @file       perfcounter.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: perfcounter.xml.
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

#include "perfcounter.h"
#include "uavobjectfield.h"

const QString PerfCounter::NAME = QString("PerfCounter");
const QString PerfCounter::DESCRIPTION = QString("A single performance counter, used to instrument flight code");
const QString PerfCounter::CATEGORY = QString("System");

/**
 * Constructor
 */
PerfCounter::PerfCounter(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList IdElemNames;
    IdElemNames.append("0");
    fields.append( new UAVObjectField(QString("Id"), tr(""), QString("hex"), UAVObjectField::UINT32, IdElemNames, QStringList(), QString("")));
    QStringList CounterElemNames;
    CounterElemNames.append("Value");
    CounterElemNames.append("Min");
    CounterElemNames.append("Max");
    fields.append( new UAVObjectField(QString("Counter"), tr(""), QString(""), UAVObjectField::INT32, CounterElemNames, QStringList(), QString("")));

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
UAVObject::Metadata PerfCounter::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        0 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        0 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
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
void PerfCounter::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
PerfCounter::DataFields PerfCounter::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void PerfCounter::setData(const DataFields& data)
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

void PerfCounter::emitNotifications()
{
            //if (data.Id != oldData.Id)
            emit IdChanged(data.Id);
        //if (data.Counter[0] != oldData.Counter[0])
            emit Counter_ValueChanged(data.Counter[0]);
        //if (data.Counter[1] != oldData.Counter[1])
            emit Counter_MinChanged(data.Counter[1]);
        //if (data.Counter[2] != oldData.Counter[2])
            emit Counter_MaxChanged(data.Counter[2]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *PerfCounter::clone(quint32 instID)
{
    PerfCounter *obj = new PerfCounter();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *PerfCounter::dirtyClone()
{
    PerfCounter *obj = new PerfCounter();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
PerfCounter *PerfCounter::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<PerfCounter *>(objMngr->getObject(PerfCounter::OBJID, instID));
}

quint32 PerfCounter::getId() const
{
   QMutexLocker locker(mutex);
   return data.Id;
}
void PerfCounter::setId(quint32 value)
{
   mutex->lock();
   bool changed = data.Id != value;
   data.Id = value;
   mutex->unlock();
   if (changed) emit IdChanged(value);
}

qint32 PerfCounter::getCounter(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Counter[index];
}
void PerfCounter::setCounter(quint32 index, qint32 value)
{
   mutex->lock();
   bool changed = data.Counter[index] != value;
   data.Counter[index] = value;
   mutex->unlock();
   if (changed) emit CounterChanged(index,value);
}

qint32 PerfCounter::getCounter_Value() const
{
   QMutexLocker locker(mutex);
   return data.Counter[0];
}
void PerfCounter::setCounter_Value(qint32 value)
{
   mutex->lock();
   bool changed = data.Counter[0] != value;
   data.Counter[0] = value;
   mutex->unlock();
   if (changed) emit Counter_ValueChanged(value);
}

qint32 PerfCounter::getCounter_Min() const
{
   QMutexLocker locker(mutex);
   return data.Counter[1];
}
void PerfCounter::setCounter_Min(qint32 value)
{
   mutex->lock();
   bool changed = data.Counter[1] != value;
   data.Counter[1] = value;
   mutex->unlock();
   if (changed) emit Counter_MinChanged(value);
}

qint32 PerfCounter::getCounter_Max() const
{
   QMutexLocker locker(mutex);
   return data.Counter[2];
}
void PerfCounter::setCounter_Max(qint32 value)
{
   mutex->lock();
   bool changed = data.Counter[2] != value;
   data.Counter[2] = value;
   mutex->unlock();
   if (changed) emit Counter_MaxChanged(value);
}


