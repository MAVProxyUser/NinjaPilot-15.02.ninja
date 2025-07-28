/**
 ******************************************************************************
 *
 * @file       debuglogstatus.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: debuglogstatus.xml.
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

#include "debuglogstatus.h"
#include "uavobjectfield.h"

const QString DebugLogStatus::NAME = QString("DebugLogStatus");
const QString DebugLogStatus::DESCRIPTION = QString("Log Status Object, contains log partition status information");
const QString DebugLogStatus::CATEGORY = QString("System");

/**
 * Constructor
 */
DebugLogStatus::DebugLogStatus(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList FlightElemNames;
    FlightElemNames.append("0");
    fields.append( new UAVObjectField(QString("Flight"), tr("The current flight number (logging session)"), QString(""), UAVObjectField::UINT16, FlightElemNames, QStringList(), QString("")));
    QStringList EntryElemNames;
    EntryElemNames.append("0");
    fields.append( new UAVObjectField(QString("Entry"), tr("The current log entry id"), QString(""), UAVObjectField::UINT16, EntryElemNames, QStringList(), QString("")));
    QStringList UsedSlotsElemNames;
    UsedSlotsElemNames.append("0");
    fields.append( new UAVObjectField(QString("UsedSlots"), tr("Holds the total log entries saved"), QString(""), UAVObjectField::UINT16, UsedSlotsElemNames, QStringList(), QString("")));
    QStringList FreeSlotsElemNames;
    FreeSlotsElemNames.append("0");
    fields.append( new UAVObjectField(QString("FreeSlots"), tr("The number of free log slots available"), QString(""), UAVObjectField::UINT16, FreeSlotsElemNames, QStringList(), QString("")));

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
UAVObject::Metadata DebugLogStatus::getDefaultMetadata()
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
void DebugLogStatus::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
DebugLogStatus::DataFields DebugLogStatus::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void DebugLogStatus::setData(const DataFields& data)
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

void DebugLogStatus::emitNotifications()
{
            //if (data.Flight != oldData.Flight)
            emit FlightChanged(data.Flight);
        //if (data.Entry != oldData.Entry)
            emit EntryChanged(data.Entry);
        //if (data.UsedSlots != oldData.UsedSlots)
            emit UsedSlotsChanged(data.UsedSlots);
        //if (data.FreeSlots != oldData.FreeSlots)
            emit FreeSlotsChanged(data.FreeSlots);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *DebugLogStatus::clone(quint32 instID)
{
    DebugLogStatus *obj = new DebugLogStatus();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *DebugLogStatus::dirtyClone()
{
    DebugLogStatus *obj = new DebugLogStatus();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
DebugLogStatus *DebugLogStatus::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<DebugLogStatus *>(objMngr->getObject(DebugLogStatus::OBJID, instID));
}

quint16 DebugLogStatus::getFlight() const
{
   QMutexLocker locker(mutex);
   return data.Flight;
}
void DebugLogStatus::setFlight(quint16 value)
{
   mutex->lock();
   bool changed = data.Flight != value;
   data.Flight = value;
   mutex->unlock();
   if (changed) emit FlightChanged(value);
}

quint16 DebugLogStatus::getEntry() const
{
   QMutexLocker locker(mutex);
   return data.Entry;
}
void DebugLogStatus::setEntry(quint16 value)
{
   mutex->lock();
   bool changed = data.Entry != value;
   data.Entry = value;
   mutex->unlock();
   if (changed) emit EntryChanged(value);
}

quint16 DebugLogStatus::getUsedSlots() const
{
   QMutexLocker locker(mutex);
   return data.UsedSlots;
}
void DebugLogStatus::setUsedSlots(quint16 value)
{
   mutex->lock();
   bool changed = data.UsedSlots != value;
   data.UsedSlots = value;
   mutex->unlock();
   if (changed) emit UsedSlotsChanged(value);
}

quint16 DebugLogStatus::getFreeSlots() const
{
   QMutexLocker locker(mutex);
   return data.FreeSlots;
}
void DebugLogStatus::setFreeSlots(quint16 value)
{
   mutex->lock();
   bool changed = data.FreeSlots != value;
   data.FreeSlots = value;
   mutex->unlock();
   if (changed) emit FreeSlotsChanged(value);
}


