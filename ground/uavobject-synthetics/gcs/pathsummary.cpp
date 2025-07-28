/**
 ******************************************************************************
 *
 * @file       pathsummary.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: pathsummary.xml.
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

#include "pathsummary.h"
#include "uavobjectfield.h"

const QString PathSummary::NAME = QString("PathSummary");
const QString PathSummary::DESCRIPTION = QString("Summary of a completed path segment  Can come from any @ref PathFollower module");
const QString PathSummary::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
PathSummary::PathSummary(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList brake_distance_offsetElemNames;
    brake_distance_offsetElemNames.append("0");
    fields.append( new UAVObjectField(QString("brake_distance_offset"), tr(""), QString("m"), UAVObjectField::FLOAT32, brake_distance_offsetElemNames, QStringList(), QString("")));
    QStringList time_remainingElemNames;
    time_remainingElemNames.append("0");
    fields.append( new UAVObjectField(QString("time_remaining"), tr(""), QString("s"), UAVObjectField::FLOAT32, time_remainingElemNames, QStringList(), QString("")));
    QStringList fractional_progressElemNames;
    fractional_progressElemNames.append("0");
    fields.append( new UAVObjectField(QString("fractional_progress"), tr(""), QString(""), UAVObjectField::FLOAT32, fractional_progressElemNames, QStringList(), QString("")));
    QStringList decelrateElemNames;
    decelrateElemNames.append("0");
    fields.append( new UAVObjectField(QString("decelrate"), tr(""), QString("m/s2"), UAVObjectField::FLOAT32, decelrateElemNames, QStringList(), QString("")));
    QStringList brakeRateActualDesiredRatioElemNames;
    brakeRateActualDesiredRatioElemNames.append("0");
    fields.append( new UAVObjectField(QString("brakeRateActualDesiredRatio"), tr(""), QString(""), UAVObjectField::FLOAT32, brakeRateActualDesiredRatioElemNames, QStringList(), QString("")));
    QStringList velocityIntoHoldElemNames;
    velocityIntoHoldElemNames.append("0");
    fields.append( new UAVObjectField(QString("velocityIntoHold"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, velocityIntoHoldElemNames, QStringList(), QString("")));
    QStringList UIDElemNames;
    UIDElemNames.append("0");
    fields.append( new UAVObjectField(QString("UID"), tr(""), QString(""), UAVObjectField::INT16, UIDElemNames, QStringList(), QString("")));
    QStringList brake_exit_reasonElemNames;
    brake_exit_reasonElemNames.append("0");
    QStringList brake_exit_reasonEnumOptions;
    brake_exit_reasonEnumOptions.append("Timeout");
    brake_exit_reasonEnumOptions.append("PathCompleted");
    brake_exit_reasonEnumOptions.append("PathError");
    fields.append( new UAVObjectField(QString("brake_exit_reason"), tr(""), QString(""), UAVObjectField::ENUM, brake_exit_reasonElemNames, brake_exit_reasonEnumOptions, QString("")));
    QStringList ModeElemNames;
    ModeElemNames.append("0");
    QStringList ModeEnumOptions;
    ModeEnumOptions.append("GoToEndpoint");
    ModeEnumOptions.append("FollowVector");
    ModeEnumOptions.append("CircleRight");
    ModeEnumOptions.append("CircleLeft");
    ModeEnumOptions.append("FixedAttitude");
    ModeEnumOptions.append("SetAccessory");
    ModeEnumOptions.append("DisarmAlarm");
    ModeEnumOptions.append("Land");
    ModeEnumOptions.append("Brake");
    ModeEnumOptions.append("Velocity");
    fields.append( new UAVObjectField(QString("Mode"), tr(""), QString(""), UAVObjectField::ENUM, ModeElemNames, ModeEnumOptions, QString("")));

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
UAVObject::Metadata PathSummary::getDefaultMetadata()
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
void PathSummary::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
PathSummary::DataFields PathSummary::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void PathSummary::setData(const DataFields& data)
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

void PathSummary::emitNotifications()
{
            //if (data.brake_distance_offset != oldData.brake_distance_offset)
            emit brake_distance_offsetChanged(data.brake_distance_offset);
        //if (data.time_remaining != oldData.time_remaining)
            emit time_remainingChanged(data.time_remaining);
        //if (data.fractional_progress != oldData.fractional_progress)
            emit fractional_progressChanged(data.fractional_progress);
        //if (data.decelrate != oldData.decelrate)
            emit decelrateChanged(data.decelrate);
        //if (data.brakeRateActualDesiredRatio != oldData.brakeRateActualDesiredRatio)
            emit brakeRateActualDesiredRatioChanged(data.brakeRateActualDesiredRatio);
        //if (data.velocityIntoHold != oldData.velocityIntoHold)
            emit velocityIntoHoldChanged(data.velocityIntoHold);
        //if (data.UID != oldData.UID)
            emit UIDChanged(data.UID);
        //if (data.brake_exit_reason != oldData.brake_exit_reason)
            emit brake_exit_reasonChanged(data.brake_exit_reason);
        //if (data.Mode != oldData.Mode)
            emit ModeChanged(data.Mode);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *PathSummary::clone(quint32 instID)
{
    PathSummary *obj = new PathSummary();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *PathSummary::dirtyClone()
{
    PathSummary *obj = new PathSummary();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
PathSummary *PathSummary::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<PathSummary *>(objMngr->getObject(PathSummary::OBJID, instID));
}

float PathSummary::getbrake_distance_offset() const
{
   QMutexLocker locker(mutex);
   return data.brake_distance_offset;
}
void PathSummary::setbrake_distance_offset(float value)
{
   mutex->lock();
   bool changed = data.brake_distance_offset != value;
   data.brake_distance_offset = value;
   mutex->unlock();
   if (changed) emit brake_distance_offsetChanged(value);
}

float PathSummary::gettime_remaining() const
{
   QMutexLocker locker(mutex);
   return data.time_remaining;
}
void PathSummary::settime_remaining(float value)
{
   mutex->lock();
   bool changed = data.time_remaining != value;
   data.time_remaining = value;
   mutex->unlock();
   if (changed) emit time_remainingChanged(value);
}

float PathSummary::getfractional_progress() const
{
   QMutexLocker locker(mutex);
   return data.fractional_progress;
}
void PathSummary::setfractional_progress(float value)
{
   mutex->lock();
   bool changed = data.fractional_progress != value;
   data.fractional_progress = value;
   mutex->unlock();
   if (changed) emit fractional_progressChanged(value);
}

float PathSummary::getdecelrate() const
{
   QMutexLocker locker(mutex);
   return data.decelrate;
}
void PathSummary::setdecelrate(float value)
{
   mutex->lock();
   bool changed = data.decelrate != value;
   data.decelrate = value;
   mutex->unlock();
   if (changed) emit decelrateChanged(value);
}

float PathSummary::getbrakeRateActualDesiredRatio() const
{
   QMutexLocker locker(mutex);
   return data.brakeRateActualDesiredRatio;
}
void PathSummary::setbrakeRateActualDesiredRatio(float value)
{
   mutex->lock();
   bool changed = data.brakeRateActualDesiredRatio != value;
   data.brakeRateActualDesiredRatio = value;
   mutex->unlock();
   if (changed) emit brakeRateActualDesiredRatioChanged(value);
}

float PathSummary::getvelocityIntoHold() const
{
   QMutexLocker locker(mutex);
   return data.velocityIntoHold;
}
void PathSummary::setvelocityIntoHold(float value)
{
   mutex->lock();
   bool changed = data.velocityIntoHold != value;
   data.velocityIntoHold = value;
   mutex->unlock();
   if (changed) emit velocityIntoHoldChanged(value);
}

qint16 PathSummary::getUID() const
{
   QMutexLocker locker(mutex);
   return data.UID;
}
void PathSummary::setUID(qint16 value)
{
   mutex->lock();
   bool changed = data.UID != value;
   data.UID = value;
   mutex->unlock();
   if (changed) emit UIDChanged(value);
}

quint8 PathSummary::getbrake_exit_reason() const
{
   QMutexLocker locker(mutex);
   return data.brake_exit_reason;
}
void PathSummary::setbrake_exit_reason(quint8 value)
{
   mutex->lock();
   bool changed = data.brake_exit_reason != value;
   data.brake_exit_reason = value;
   mutex->unlock();
   if (changed) emit brake_exit_reasonChanged(value);
}

quint8 PathSummary::getMode() const
{
   QMutexLocker locker(mutex);
   return data.Mode;
}
void PathSummary::setMode(quint8 value)
{
   mutex->lock();
   bool changed = data.Mode != value;
   data.Mode = value;
   mutex->unlock();
   if (changed) emit ModeChanged(value);
}


