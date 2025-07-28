/**
 ******************************************************************************
 *
 * @file       attitudestate.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: attitudestate.xml.
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

#include "attitudestate.h"
#include "uavobjectfield.h"

const QString AttitudeState::NAME = QString("AttitudeState");
const QString AttitudeState::DESCRIPTION = QString("The updated Attitude estimation from @ref StateEstimationModule.");
const QString AttitudeState::CATEGORY = QString("State");

/**
 * Constructor
 */
AttitudeState::AttitudeState(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList q1ElemNames;
    q1ElemNames.append("0");
    fields.append( new UAVObjectField(QString("q1"), tr(""), QString(""), UAVObjectField::FLOAT32, q1ElemNames, QStringList(), QString("")));
    QStringList q2ElemNames;
    q2ElemNames.append("0");
    fields.append( new UAVObjectField(QString("q2"), tr(""), QString(""), UAVObjectField::FLOAT32, q2ElemNames, QStringList(), QString("")));
    QStringList q3ElemNames;
    q3ElemNames.append("0");
    fields.append( new UAVObjectField(QString("q3"), tr(""), QString(""), UAVObjectField::FLOAT32, q3ElemNames, QStringList(), QString("")));
    QStringList q4ElemNames;
    q4ElemNames.append("0");
    fields.append( new UAVObjectField(QString("q4"), tr(""), QString(""), UAVObjectField::FLOAT32, q4ElemNames, QStringList(), QString("")));
    QStringList RollElemNames;
    RollElemNames.append("0");
    fields.append( new UAVObjectField(QString("Roll"), tr(""), QString("degrees"), UAVObjectField::FLOAT32, RollElemNames, QStringList(), QString("")));
    QStringList PitchElemNames;
    PitchElemNames.append("0");
    fields.append( new UAVObjectField(QString("Pitch"), tr(""), QString("degrees"), UAVObjectField::FLOAT32, PitchElemNames, QStringList(), QString("")));
    QStringList YawElemNames;
    YawElemNames.append("0");
    fields.append( new UAVObjectField(QString("Yaw"), tr(""), QString("degrees"), UAVObjectField::FLOAT32, YawElemNames, QStringList(), QString("")));

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
UAVObject::Metadata AttitudeState::getDefaultMetadata()
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
    metadata.flightTelemetryUpdatePeriod = 130;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void AttitudeState::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
AttitudeState::DataFields AttitudeState::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void AttitudeState::setData(const DataFields& data)
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

void AttitudeState::emitNotifications()
{
            //if (data.q1 != oldData.q1)
            emit q1Changed(data.q1);
        //if (data.q2 != oldData.q2)
            emit q2Changed(data.q2);
        //if (data.q3 != oldData.q3)
            emit q3Changed(data.q3);
        //if (data.q4 != oldData.q4)
            emit q4Changed(data.q4);
        //if (data.Roll != oldData.Roll)
            emit RollChanged(data.Roll);
        //if (data.Pitch != oldData.Pitch)
            emit PitchChanged(data.Pitch);
        //if (data.Yaw != oldData.Yaw)
            emit YawChanged(data.Yaw);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *AttitudeState::clone(quint32 instID)
{
    AttitudeState *obj = new AttitudeState();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *AttitudeState::dirtyClone()
{
    AttitudeState *obj = new AttitudeState();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
AttitudeState *AttitudeState::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<AttitudeState *>(objMngr->getObject(AttitudeState::OBJID, instID));
}

float AttitudeState::getq1() const
{
   QMutexLocker locker(mutex);
   return data.q1;
}
void AttitudeState::setq1(float value)
{
   mutex->lock();
   bool changed = data.q1 != value;
   data.q1 = value;
   mutex->unlock();
   if (changed) emit q1Changed(value);
}

float AttitudeState::getq2() const
{
   QMutexLocker locker(mutex);
   return data.q2;
}
void AttitudeState::setq2(float value)
{
   mutex->lock();
   bool changed = data.q2 != value;
   data.q2 = value;
   mutex->unlock();
   if (changed) emit q2Changed(value);
}

float AttitudeState::getq3() const
{
   QMutexLocker locker(mutex);
   return data.q3;
}
void AttitudeState::setq3(float value)
{
   mutex->lock();
   bool changed = data.q3 != value;
   data.q3 = value;
   mutex->unlock();
   if (changed) emit q3Changed(value);
}

float AttitudeState::getq4() const
{
   QMutexLocker locker(mutex);
   return data.q4;
}
void AttitudeState::setq4(float value)
{
   mutex->lock();
   bool changed = data.q4 != value;
   data.q4 = value;
   mutex->unlock();
   if (changed) emit q4Changed(value);
}

float AttitudeState::getRoll() const
{
   QMutexLocker locker(mutex);
   return data.Roll;
}
void AttitudeState::setRoll(float value)
{
   mutex->lock();
   bool changed = data.Roll != value;
   data.Roll = value;
   mutex->unlock();
   if (changed) emit RollChanged(value);
}

float AttitudeState::getPitch() const
{
   QMutexLocker locker(mutex);
   return data.Pitch;
}
void AttitudeState::setPitch(float value)
{
   mutex->lock();
   bool changed = data.Pitch != value;
   data.Pitch = value;
   mutex->unlock();
   if (changed) emit PitchChanged(value);
}

float AttitudeState::getYaw() const
{
   QMutexLocker locker(mutex);
   return data.Yaw;
}
void AttitudeState::setYaw(float value)
{
   mutex->lock();
   bool changed = data.Yaw != value;
   data.Yaw = value;
   mutex->unlock();
   if (changed) emit YawChanged(value);
}


