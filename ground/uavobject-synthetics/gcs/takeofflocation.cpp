/**
 ******************************************************************************
 *
 * @file       takeofflocation.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: takeofflocation.xml.
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

#include "takeofflocation.h"
#include "uavobjectfield.h"

const QString TakeOffLocation::NAME = QString("TakeOffLocation");
const QString TakeOffLocation::DESCRIPTION = QString("TakeOffLocation setting which contains the destination of a ReturnToBase operation");
const QString TakeOffLocation::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
TakeOffLocation::TakeOffLocation(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList NorthElemNames;
    NorthElemNames.append("0");
    fields.append( new UAVObjectField(QString("North"), tr(""), QString("m"), UAVObjectField::FLOAT32, NorthElemNames, QStringList(), QString("")));
    QStringList EastElemNames;
    EastElemNames.append("0");
    fields.append( new UAVObjectField(QString("East"), tr(""), QString("m"), UAVObjectField::FLOAT32, EastElemNames, QStringList(), QString("")));
    QStringList DownElemNames;
    DownElemNames.append("0");
    fields.append( new UAVObjectField(QString("Down"), tr(""), QString("m"), UAVObjectField::FLOAT32, DownElemNames, QStringList(), QString("")));
    QStringList ModeElemNames;
    ModeElemNames.append("0");
    QStringList ModeEnumOptions;
    ModeEnumOptions.append("ArmingLocation");
    ModeEnumOptions.append("FirstArmingLocation");
    ModeEnumOptions.append("Preset");
    fields.append( new UAVObjectField(QString("Mode"), tr(""), QString(""), UAVObjectField::ENUM, ModeElemNames, ModeEnumOptions, QString("")));
    QStringList StatusElemNames;
    StatusElemNames.append("0");
    QStringList StatusEnumOptions;
    StatusEnumOptions.append("Valid");
    StatusEnumOptions.append("Invalid");
    fields.append( new UAVObjectField(QString("Status"), tr(""), QString(""), UAVObjectField::ENUM, StatusElemNames, StatusEnumOptions, QString("")));

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
UAVObject::Metadata TakeOffLocation::getDefaultMetadata()
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
void TakeOffLocation::setDefaultFieldValues()
{
    data.North = 0;
    data.East = 0;
    data.Down = 0;
    data.Mode = 0;
    data.Status = 1;

}

/**
 * Get the object data fields
 */
TakeOffLocation::DataFields TakeOffLocation::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void TakeOffLocation::setData(const DataFields& data)
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

void TakeOffLocation::emitNotifications()
{
            //if (data.North != oldData.North)
            emit NorthChanged(data.North);
        //if (data.East != oldData.East)
            emit EastChanged(data.East);
        //if (data.Down != oldData.Down)
            emit DownChanged(data.Down);
        //if (data.Mode != oldData.Mode)
            emit ModeChanged(data.Mode);
        //if (data.Status != oldData.Status)
            emit StatusChanged(data.Status);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *TakeOffLocation::clone(quint32 instID)
{
    TakeOffLocation *obj = new TakeOffLocation();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *TakeOffLocation::dirtyClone()
{
    TakeOffLocation *obj = new TakeOffLocation();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
TakeOffLocation *TakeOffLocation::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<TakeOffLocation *>(objMngr->getObject(TakeOffLocation::OBJID, instID));
}

float TakeOffLocation::getNorth() const
{
   QMutexLocker locker(mutex);
   return data.North;
}
void TakeOffLocation::setNorth(float value)
{
   mutex->lock();
   bool changed = data.North != value;
   data.North = value;
   mutex->unlock();
   if (changed) emit NorthChanged(value);
}

float TakeOffLocation::getEast() const
{
   QMutexLocker locker(mutex);
   return data.East;
}
void TakeOffLocation::setEast(float value)
{
   mutex->lock();
   bool changed = data.East != value;
   data.East = value;
   mutex->unlock();
   if (changed) emit EastChanged(value);
}

float TakeOffLocation::getDown() const
{
   QMutexLocker locker(mutex);
   return data.Down;
}
void TakeOffLocation::setDown(float value)
{
   mutex->lock();
   bool changed = data.Down != value;
   data.Down = value;
   mutex->unlock();
   if (changed) emit DownChanged(value);
}

quint8 TakeOffLocation::getMode() const
{
   QMutexLocker locker(mutex);
   return data.Mode;
}
void TakeOffLocation::setMode(quint8 value)
{
   mutex->lock();
   bool changed = data.Mode != value;
   data.Mode = value;
   mutex->unlock();
   if (changed) emit ModeChanged(value);
}

quint8 TakeOffLocation::getStatus() const
{
   QMutexLocker locker(mutex);
   return data.Status;
}
void TakeOffLocation::setStatus(quint8 value)
{
   mutex->lock();
   bool changed = data.Status != value;
   data.Status = value;
   mutex->unlock();
   if (changed) emit StatusChanged(value);
}


