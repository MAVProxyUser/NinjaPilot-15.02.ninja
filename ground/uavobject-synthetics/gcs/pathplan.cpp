/**
 ******************************************************************************
 *
 * @file       pathplan.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: pathplan.xml.
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

#include "pathplan.h"
#include "uavobjectfield.h"

const QString PathPlan::NAME = QString("PathPlan");
const QString PathPlan::DESCRIPTION = QString("Flight plan informations");
const QString PathPlan::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
PathPlan::PathPlan(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList WaypointCountElemNames;
    WaypointCountElemNames.append("0");
    fields.append( new UAVObjectField(QString("WaypointCount"), tr(""), QString(""), UAVObjectField::UINT16, WaypointCountElemNames, QStringList(), QString("")));
    QStringList PathActionCountElemNames;
    PathActionCountElemNames.append("0");
    fields.append( new UAVObjectField(QString("PathActionCount"), tr(""), QString(""), UAVObjectField::UINT16, PathActionCountElemNames, QStringList(), QString("")));
    QStringList CrcElemNames;
    CrcElemNames.append("0");
    fields.append( new UAVObjectField(QString("Crc"), tr(""), QString(""), UAVObjectField::UINT8, CrcElemNames, QStringList(), QString("")));

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
UAVObject::Metadata PathPlan::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READONLY << UAVOBJ_ACCESS_SHIFT |
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
void PathPlan::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
PathPlan::DataFields PathPlan::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void PathPlan::setData(const DataFields& data)
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

void PathPlan::emitNotifications()
{
            //if (data.WaypointCount != oldData.WaypointCount)
            emit WaypointCountChanged(data.WaypointCount);
        //if (data.PathActionCount != oldData.PathActionCount)
            emit PathActionCountChanged(data.PathActionCount);
        //if (data.Crc != oldData.Crc)
            emit CrcChanged(data.Crc);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *PathPlan::clone(quint32 instID)
{
    PathPlan *obj = new PathPlan();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *PathPlan::dirtyClone()
{
    PathPlan *obj = new PathPlan();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
PathPlan *PathPlan::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<PathPlan *>(objMngr->getObject(PathPlan::OBJID, instID));
}

quint16 PathPlan::getWaypointCount() const
{
   QMutexLocker locker(mutex);
   return data.WaypointCount;
}
void PathPlan::setWaypointCount(quint16 value)
{
   mutex->lock();
   bool changed = data.WaypointCount != value;
   data.WaypointCount = value;
   mutex->unlock();
   if (changed) emit WaypointCountChanged(value);
}

quint16 PathPlan::getPathActionCount() const
{
   QMutexLocker locker(mutex);
   return data.PathActionCount;
}
void PathPlan::setPathActionCount(quint16 value)
{
   mutex->lock();
   bool changed = data.PathActionCount != value;
   data.PathActionCount = value;
   mutex->unlock();
   if (changed) emit PathActionCountChanged(value);
}

quint8 PathPlan::getCrc() const
{
   QMutexLocker locker(mutex);
   return data.Crc;
}
void PathPlan::setCrc(quint8 value)
{
   mutex->lock();
   bool changed = data.Crc != value;
   data.Crc = value;
   mutex->unlock();
   if (changed) emit CrcChanged(value);
}


