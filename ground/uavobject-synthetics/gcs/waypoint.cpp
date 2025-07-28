/**
 ******************************************************************************
 *
 * @file       waypoint.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: waypoint.xml.
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

#include "waypoint.h"
#include "uavobjectfield.h"

const QString Waypoint::NAME = QString("Waypoint");
const QString Waypoint::DESCRIPTION = QString("A waypoint the aircraft can try and hit.  Used by the @ref PathPlanner module");
const QString Waypoint::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
Waypoint::Waypoint(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList PositionElemNames;
    PositionElemNames.append("North");
    PositionElemNames.append("East");
    PositionElemNames.append("Down");
    fields.append( new UAVObjectField(QString("Position"), tr(""), QString("m"), UAVObjectField::FLOAT32, PositionElemNames, QStringList(), QString("")));
    QStringList VelocityElemNames;
    VelocityElemNames.append("0");
    fields.append( new UAVObjectField(QString("Velocity"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, VelocityElemNames, QStringList(), QString("")));
    QStringList ActionElemNames;
    ActionElemNames.append("0");
    fields.append( new UAVObjectField(QString("Action"), tr(""), QString(""), UAVObjectField::UINT8, ActionElemNames, QStringList(), QString("")));

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
UAVObject::Metadata Waypoint::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        1 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        1 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
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
void Waypoint::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
Waypoint::DataFields Waypoint::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void Waypoint::setData(const DataFields& data)
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

void Waypoint::emitNotifications()
{
            //if (data.Position[0] != oldData.Position[0])
            emit Position_NorthChanged(data.Position[0]);
        //if (data.Position[1] != oldData.Position[1])
            emit Position_EastChanged(data.Position[1]);
        //if (data.Position[2] != oldData.Position[2])
            emit Position_DownChanged(data.Position[2]);
        //if (data.Velocity != oldData.Velocity)
            emit VelocityChanged(data.Velocity);
        //if (data.Action != oldData.Action)
            emit ActionChanged(data.Action);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *Waypoint::clone(quint32 instID)
{
    Waypoint *obj = new Waypoint();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *Waypoint::dirtyClone()
{
    Waypoint *obj = new Waypoint();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
Waypoint *Waypoint::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<Waypoint *>(objMngr->getObject(Waypoint::OBJID, instID));
}

float Waypoint::getPosition(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Position[index];
}
void Waypoint::setPosition(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.Position[index] != value;
   data.Position[index] = value;
   mutex->unlock();
   if (changed) emit PositionChanged(index,value);
}

float Waypoint::getPosition_North() const
{
   QMutexLocker locker(mutex);
   return data.Position[0];
}
void Waypoint::setPosition_North(float value)
{
   mutex->lock();
   bool changed = data.Position[0] != value;
   data.Position[0] = value;
   mutex->unlock();
   if (changed) emit Position_NorthChanged(value);
}

float Waypoint::getPosition_East() const
{
   QMutexLocker locker(mutex);
   return data.Position[1];
}
void Waypoint::setPosition_East(float value)
{
   mutex->lock();
   bool changed = data.Position[1] != value;
   data.Position[1] = value;
   mutex->unlock();
   if (changed) emit Position_EastChanged(value);
}

float Waypoint::getPosition_Down() const
{
   QMutexLocker locker(mutex);
   return data.Position[2];
}
void Waypoint::setPosition_Down(float value)
{
   mutex->lock();
   bool changed = data.Position[2] != value;
   data.Position[2] = value;
   mutex->unlock();
   if (changed) emit Position_DownChanged(value);
}

float Waypoint::getVelocity() const
{
   QMutexLocker locker(mutex);
   return data.Velocity;
}
void Waypoint::setVelocity(float value)
{
   mutex->lock();
   bool changed = data.Velocity != value;
   data.Velocity = value;
   mutex->unlock();
   if (changed) emit VelocityChanged(value);
}

quint8 Waypoint::getAction() const
{
   QMutexLocker locker(mutex);
   return data.Action;
}
void Waypoint::setAction(quint8 value)
{
   mutex->lock();
   bool changed = data.Action != value;
   data.Action = value;
   mutex->unlock();
   if (changed) emit ActionChanged(value);
}


