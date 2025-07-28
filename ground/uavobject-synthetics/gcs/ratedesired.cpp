/**
 ******************************************************************************
 *
 * @file       ratedesired.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: ratedesired.xml.
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

#include "ratedesired.h"
#include "uavobjectfield.h"

const QString RateDesired::NAME = QString("RateDesired");
const QString RateDesired::DESCRIPTION = QString("Status for the matrix mixer showing the output of each mixer after all scaling");
const QString RateDesired::CATEGORY = QString("Control");

/**
 * Constructor
 */
RateDesired::RateDesired(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList RollElemNames;
    RollElemNames.append("0");
    fields.append( new UAVObjectField(QString("Roll"), tr(""), QString("deg/s"), UAVObjectField::FLOAT32, RollElemNames, QStringList(), QString("")));
    QStringList PitchElemNames;
    PitchElemNames.append("0");
    fields.append( new UAVObjectField(QString("Pitch"), tr(""), QString("deg/s"), UAVObjectField::FLOAT32, PitchElemNames, QStringList(), QString("")));
    QStringList YawElemNames;
    YawElemNames.append("0");
    fields.append( new UAVObjectField(QString("Yaw"), tr(""), QString("deg/s"), UAVObjectField::FLOAT32, YawElemNames, QStringList(), QString("")));
    QStringList ThrustElemNames;
    ThrustElemNames.append("0");
    fields.append( new UAVObjectField(QString("Thrust"), tr(""), QString("%"), UAVObjectField::FLOAT32, ThrustElemNames, QStringList(), QString("")));

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
UAVObject::Metadata RateDesired::getDefaultMetadata()
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
void RateDesired::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
RateDesired::DataFields RateDesired::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void RateDesired::setData(const DataFields& data)
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

void RateDesired::emitNotifications()
{
            //if (data.Roll != oldData.Roll)
            emit RollChanged(data.Roll);
        //if (data.Pitch != oldData.Pitch)
            emit PitchChanged(data.Pitch);
        //if (data.Yaw != oldData.Yaw)
            emit YawChanged(data.Yaw);
        //if (data.Thrust != oldData.Thrust)
            emit ThrustChanged(data.Thrust);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *RateDesired::clone(quint32 instID)
{
    RateDesired *obj = new RateDesired();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *RateDesired::dirtyClone()
{
    RateDesired *obj = new RateDesired();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
RateDesired *RateDesired::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<RateDesired *>(objMngr->getObject(RateDesired::OBJID, instID));
}

float RateDesired::getRoll() const
{
   QMutexLocker locker(mutex);
   return data.Roll;
}
void RateDesired::setRoll(float value)
{
   mutex->lock();
   bool changed = data.Roll != value;
   data.Roll = value;
   mutex->unlock();
   if (changed) emit RollChanged(value);
}

float RateDesired::getPitch() const
{
   QMutexLocker locker(mutex);
   return data.Pitch;
}
void RateDesired::setPitch(float value)
{
   mutex->lock();
   bool changed = data.Pitch != value;
   data.Pitch = value;
   mutex->unlock();
   if (changed) emit PitchChanged(value);
}

float RateDesired::getYaw() const
{
   QMutexLocker locker(mutex);
   return data.Yaw;
}
void RateDesired::setYaw(float value)
{
   mutex->lock();
   bool changed = data.Yaw != value;
   data.Yaw = value;
   mutex->unlock();
   if (changed) emit YawChanged(value);
}

float RateDesired::getThrust() const
{
   QMutexLocker locker(mutex);
   return data.Thrust;
}
void RateDesired::setThrust(float value)
{
   mutex->lock();
   bool changed = data.Thrust != value;
   data.Thrust = value;
   mutex->unlock();
   if (changed) emit ThrustChanged(value);
}


