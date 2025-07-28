/**
 ******************************************************************************
 *
 * @file       altitudeholdstatus.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: altitudeholdstatus.xml.
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

#include "altitudeholdstatus.h"
#include "uavobjectfield.h"

const QString AltitudeHoldStatus::NAME = QString("AltitudeHoldStatus");
const QString AltitudeHoldStatus::DESCRIPTION = QString("Status Data from Altitude Hold Control Loops");
const QString AltitudeHoldStatus::CATEGORY = QString("Control");

/**
 * Constructor
 */
AltitudeHoldStatus::AltitudeHoldStatus(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList VelocityDesiredElemNames;
    VelocityDesiredElemNames.append("0");
    fields.append( new UAVObjectField(QString("VelocityDesired"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, VelocityDesiredElemNames, QStringList(), QString("")));

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
UAVObject::Metadata AltitudeHoldStatus::getDefaultMetadata()
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
void AltitudeHoldStatus::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
AltitudeHoldStatus::DataFields AltitudeHoldStatus::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void AltitudeHoldStatus::setData(const DataFields& data)
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

void AltitudeHoldStatus::emitNotifications()
{
            //if (data.VelocityDesired != oldData.VelocityDesired)
            emit VelocityDesiredChanged(data.VelocityDesired);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *AltitudeHoldStatus::clone(quint32 instID)
{
    AltitudeHoldStatus *obj = new AltitudeHoldStatus();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *AltitudeHoldStatus::dirtyClone()
{
    AltitudeHoldStatus *obj = new AltitudeHoldStatus();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
AltitudeHoldStatus *AltitudeHoldStatus::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<AltitudeHoldStatus *>(objMngr->getObject(AltitudeHoldStatus::OBJID, instID));
}

float AltitudeHoldStatus::getVelocityDesired() const
{
   QMutexLocker locker(mutex);
   return data.VelocityDesired;
}
void AltitudeHoldStatus::setVelocityDesired(float value)
{
   mutex->lock();
   bool changed = data.VelocityDesired != value;
   data.VelocityDesired = value;
   mutex->unlock();
   if (changed) emit VelocityDesiredChanged(value);
}


