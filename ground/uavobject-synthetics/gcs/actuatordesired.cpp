/**
 ******************************************************************************
 *
 * @file       actuatordesired.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: actuatordesired.xml.
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

#include "actuatordesired.h"
#include "uavobjectfield.h"

const QString ActuatorDesired::NAME = QString("ActuatorDesired");
const QString ActuatorDesired::DESCRIPTION = QString("Desired raw, pitch and yaw actuator settings.  Comes from either @ref StabilizationModule or @ref ManualControlModule depending on FlightMode.");
const QString ActuatorDesired::CATEGORY = QString("Control");

/**
 * Constructor
 */
ActuatorDesired::ActuatorDesired(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList RollElemNames;
    RollElemNames.append("0");
    fields.append( new UAVObjectField(QString("Roll"), tr(""), QString("%"), UAVObjectField::FLOAT32, RollElemNames, QStringList(), QString("")));
    QStringList PitchElemNames;
    PitchElemNames.append("0");
    fields.append( new UAVObjectField(QString("Pitch"), tr(""), QString("%"), UAVObjectField::FLOAT32, PitchElemNames, QStringList(), QString("")));
    QStringList YawElemNames;
    YawElemNames.append("0");
    fields.append( new UAVObjectField(QString("Yaw"), tr(""), QString("%"), UAVObjectField::FLOAT32, YawElemNames, QStringList(), QString("")));
    QStringList ThrustElemNames;
    ThrustElemNames.append("0");
    fields.append( new UAVObjectField(QString("Thrust"), tr(""), QString("%"), UAVObjectField::FLOAT32, ThrustElemNames, QStringList(), QString("")));
    QStringList UpdateTimeElemNames;
    UpdateTimeElemNames.append("0");
    fields.append( new UAVObjectField(QString("UpdateTime"), tr(""), QString("ms"), UAVObjectField::FLOAT32, UpdateTimeElemNames, QStringList(), QString("")));
    QStringList NumLongUpdatesElemNames;
    NumLongUpdatesElemNames.append("0");
    fields.append( new UAVObjectField(QString("NumLongUpdates"), tr(""), QString("ms"), UAVObjectField::FLOAT32, NumLongUpdatesElemNames, QStringList(), QString("")));

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
UAVObject::Metadata ActuatorDesired::getDefaultMetadata()
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
void ActuatorDesired::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
ActuatorDesired::DataFields ActuatorDesired::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void ActuatorDesired::setData(const DataFields& data)
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

void ActuatorDesired::emitNotifications()
{
            //if (data.Roll != oldData.Roll)
            emit RollChanged(data.Roll);
        //if (data.Pitch != oldData.Pitch)
            emit PitchChanged(data.Pitch);
        //if (data.Yaw != oldData.Yaw)
            emit YawChanged(data.Yaw);
        //if (data.Thrust != oldData.Thrust)
            emit ThrustChanged(data.Thrust);
        //if (data.UpdateTime != oldData.UpdateTime)
            emit UpdateTimeChanged(data.UpdateTime);
        //if (data.NumLongUpdates != oldData.NumLongUpdates)
            emit NumLongUpdatesChanged(data.NumLongUpdates);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *ActuatorDesired::clone(quint32 instID)
{
    ActuatorDesired *obj = new ActuatorDesired();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *ActuatorDesired::dirtyClone()
{
    ActuatorDesired *obj = new ActuatorDesired();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
ActuatorDesired *ActuatorDesired::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<ActuatorDesired *>(objMngr->getObject(ActuatorDesired::OBJID, instID));
}

float ActuatorDesired::getRoll() const
{
   QMutexLocker locker(mutex);
   return data.Roll;
}
void ActuatorDesired::setRoll(float value)
{
   mutex->lock();
   bool changed = data.Roll != value;
   data.Roll = value;
   mutex->unlock();
   if (changed) emit RollChanged(value);
}

float ActuatorDesired::getPitch() const
{
   QMutexLocker locker(mutex);
   return data.Pitch;
}
void ActuatorDesired::setPitch(float value)
{
   mutex->lock();
   bool changed = data.Pitch != value;
   data.Pitch = value;
   mutex->unlock();
   if (changed) emit PitchChanged(value);
}

float ActuatorDesired::getYaw() const
{
   QMutexLocker locker(mutex);
   return data.Yaw;
}
void ActuatorDesired::setYaw(float value)
{
   mutex->lock();
   bool changed = data.Yaw != value;
   data.Yaw = value;
   mutex->unlock();
   if (changed) emit YawChanged(value);
}

float ActuatorDesired::getThrust() const
{
   QMutexLocker locker(mutex);
   return data.Thrust;
}
void ActuatorDesired::setThrust(float value)
{
   mutex->lock();
   bool changed = data.Thrust != value;
   data.Thrust = value;
   mutex->unlock();
   if (changed) emit ThrustChanged(value);
}

float ActuatorDesired::getUpdateTime() const
{
   QMutexLocker locker(mutex);
   return data.UpdateTime;
}
void ActuatorDesired::setUpdateTime(float value)
{
   mutex->lock();
   bool changed = data.UpdateTime != value;
   data.UpdateTime = value;
   mutex->unlock();
   if (changed) emit UpdateTimeChanged(value);
}

float ActuatorDesired::getNumLongUpdates() const
{
   QMutexLocker locker(mutex);
   return data.NumLongUpdates;
}
void ActuatorDesired::setNumLongUpdates(float value)
{
   mutex->lock();
   bool changed = data.NumLongUpdates != value;
   data.NumLongUpdates = value;
   mutex->unlock();
   if (changed) emit NumLongUpdatesChanged(value);
}


