/**
 ******************************************************************************
 *
 * @file       waypointactive.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: waypointactive.xml.
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

#include "waypointactive.h"
#include "uavobjectfield.h"

const QString WaypointActive::NAME = QString("WaypointActive");
const QString WaypointActive::DESCRIPTION = QString("Indicates the currently active waypoint");
const QString WaypointActive::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
WaypointActive::WaypointActive(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList IndexElemNames;
    IndexElemNames.append("0");
    fields.append( new UAVObjectField(QString("Index"), tr(""), QString(""), UAVObjectField::INT16, IndexElemNames, QStringList(), QString("")));

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
UAVObject::Metadata WaypointActive::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        0 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        0 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_ONCHANGE << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
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
void WaypointActive::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
WaypointActive::DataFields WaypointActive::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void WaypointActive::setData(const DataFields& data)
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

void WaypointActive::emitNotifications()
{
            //if (data.Index != oldData.Index)
            emit IndexChanged(data.Index);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *WaypointActive::clone(quint32 instID)
{
    WaypointActive *obj = new WaypointActive();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *WaypointActive::dirtyClone()
{
    WaypointActive *obj = new WaypointActive();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
WaypointActive *WaypointActive::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<WaypointActive *>(objMngr->getObject(WaypointActive::OBJID, instID));
}

qint16 WaypointActive::getIndex() const
{
   QMutexLocker locker(mutex);
   return data.Index;
}
void WaypointActive::setIndex(qint16 value)
{
   mutex->lock();
   bool changed = data.Index != value;
   data.Index = value;
   mutex->unlock();
   if (changed) emit IndexChanged(value);
}


