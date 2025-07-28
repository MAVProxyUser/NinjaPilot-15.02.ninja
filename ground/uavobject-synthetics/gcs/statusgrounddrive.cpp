/**
 ******************************************************************************
 *
 * @file       statusgrounddrive.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: statusgrounddrive.xml.
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

#include "statusgrounddrive.h"
#include "uavobjectfield.h"

const QString StatusGroundDrive::NAME = QString("StatusGroundDrive");
const QString StatusGroundDrive::DESCRIPTION = QString("Status of a Ground drive sequence");
const QString StatusGroundDrive::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
StatusGroundDrive::StatusGroundDrive(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList NECommandElemNames;
    NECommandElemNames.append("North");
    NECommandElemNames.append("East");
    fields.append( new UAVObjectField(QString("NECommand"), tr(""), QString(""), UAVObjectField::FLOAT32, NECommandElemNames, QStringList(), QString("")));
    QStringList StateElemNames;
    StateElemNames.append("Yaw");
    StateElemNames.append("Velocity");
    StateElemNames.append("Thrust");
    fields.append( new UAVObjectField(QString("State"), tr(""), QString(""), UAVObjectField::FLOAT32, StateElemNames, QStringList(), QString("")));
    QStringList BodyCommandElemNames;
    BodyCommandElemNames.append("Forward");
    BodyCommandElemNames.append("Right");
    fields.append( new UAVObjectField(QString("BodyCommand"), tr(""), QString(""), UAVObjectField::FLOAT32, BodyCommandElemNames, QStringList(), QString("")));
    QStringList ControlCommandElemNames;
    ControlCommandElemNames.append("Speed");
    ControlCommandElemNames.append("Course");
    fields.append( new UAVObjectField(QString("ControlCommand"), tr(""), QString(""), UAVObjectField::FLOAT32, ControlCommandElemNames, QStringList(), QString("")));
    QStringList ControlStateElemNames;
    ControlStateElemNames.append("0");
    QStringList ControlStateEnumOptions;
    ControlStateEnumOptions.append("Inactive");
    ControlStateEnumOptions.append("OnTrack");
    ControlStateEnumOptions.append("TurnAroundRight");
    ControlStateEnumOptions.append("TurnAroundLeft");
    ControlStateEnumOptions.append("Brake");
    fields.append( new UAVObjectField(QString("ControlState"), tr(""), QString(""), UAVObjectField::ENUM, ControlStateElemNames, ControlStateEnumOptions, QString("")));

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
UAVObject::Metadata StatusGroundDrive::getDefaultMetadata()
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
    metadata.flightTelemetryUpdatePeriod = 100;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void StatusGroundDrive::setDefaultFieldValues()
{
    data.NECommand[0] = 0;
    data.NECommand[1] = 0;
    data.State[0] = 0;
    data.State[1] = 0;
    data.State[2] = 0;
    data.BodyCommand[0] = 0;
    data.BodyCommand[1] = 0;
    data.ControlCommand[0] = 0;
    data.ControlCommand[1] = 0;

}

/**
 * Get the object data fields
 */
StatusGroundDrive::DataFields StatusGroundDrive::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void StatusGroundDrive::setData(const DataFields& data)
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

void StatusGroundDrive::emitNotifications()
{
            //if (data.NECommand[0] != oldData.NECommand[0])
            emit NECommand_NorthChanged(data.NECommand[0]);
        //if (data.NECommand[1] != oldData.NECommand[1])
            emit NECommand_EastChanged(data.NECommand[1]);
        //if (data.State[0] != oldData.State[0])
            emit State_YawChanged(data.State[0]);
        //if (data.State[1] != oldData.State[1])
            emit State_VelocityChanged(data.State[1]);
        //if (data.State[2] != oldData.State[2])
            emit State_ThrustChanged(data.State[2]);
        //if (data.BodyCommand[0] != oldData.BodyCommand[0])
            emit BodyCommand_ForwardChanged(data.BodyCommand[0]);
        //if (data.BodyCommand[1] != oldData.BodyCommand[1])
            emit BodyCommand_RightChanged(data.BodyCommand[1]);
        //if (data.ControlCommand[0] != oldData.ControlCommand[0])
            emit ControlCommand_SpeedChanged(data.ControlCommand[0]);
        //if (data.ControlCommand[1] != oldData.ControlCommand[1])
            emit ControlCommand_CourseChanged(data.ControlCommand[1]);
        //if (data.ControlState != oldData.ControlState)
            emit ControlStateChanged(data.ControlState);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *StatusGroundDrive::clone(quint32 instID)
{
    StatusGroundDrive *obj = new StatusGroundDrive();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *StatusGroundDrive::dirtyClone()
{
    StatusGroundDrive *obj = new StatusGroundDrive();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
StatusGroundDrive *StatusGroundDrive::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<StatusGroundDrive *>(objMngr->getObject(StatusGroundDrive::OBJID, instID));
}

float StatusGroundDrive::getNECommand(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.NECommand[index];
}
void StatusGroundDrive::setNECommand(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.NECommand[index] != value;
   data.NECommand[index] = value;
   mutex->unlock();
   if (changed) emit NECommandChanged(index,value);
}

float StatusGroundDrive::getNECommand_North() const
{
   QMutexLocker locker(mutex);
   return data.NECommand[0];
}
void StatusGroundDrive::setNECommand_North(float value)
{
   mutex->lock();
   bool changed = data.NECommand[0] != value;
   data.NECommand[0] = value;
   mutex->unlock();
   if (changed) emit NECommand_NorthChanged(value);
}

float StatusGroundDrive::getNECommand_East() const
{
   QMutexLocker locker(mutex);
   return data.NECommand[1];
}
void StatusGroundDrive::setNECommand_East(float value)
{
   mutex->lock();
   bool changed = data.NECommand[1] != value;
   data.NECommand[1] = value;
   mutex->unlock();
   if (changed) emit NECommand_EastChanged(value);
}

float StatusGroundDrive::getState(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.State[index];
}
void StatusGroundDrive::setState(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.State[index] != value;
   data.State[index] = value;
   mutex->unlock();
   if (changed) emit StateChanged(index,value);
}

float StatusGroundDrive::getState_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.State[0];
}
void StatusGroundDrive::setState_Yaw(float value)
{
   mutex->lock();
   bool changed = data.State[0] != value;
   data.State[0] = value;
   mutex->unlock();
   if (changed) emit State_YawChanged(value);
}

float StatusGroundDrive::getState_Velocity() const
{
   QMutexLocker locker(mutex);
   return data.State[1];
}
void StatusGroundDrive::setState_Velocity(float value)
{
   mutex->lock();
   bool changed = data.State[1] != value;
   data.State[1] = value;
   mutex->unlock();
   if (changed) emit State_VelocityChanged(value);
}

float StatusGroundDrive::getState_Thrust() const
{
   QMutexLocker locker(mutex);
   return data.State[2];
}
void StatusGroundDrive::setState_Thrust(float value)
{
   mutex->lock();
   bool changed = data.State[2] != value;
   data.State[2] = value;
   mutex->unlock();
   if (changed) emit State_ThrustChanged(value);
}

float StatusGroundDrive::getBodyCommand(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.BodyCommand[index];
}
void StatusGroundDrive::setBodyCommand(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.BodyCommand[index] != value;
   data.BodyCommand[index] = value;
   mutex->unlock();
   if (changed) emit BodyCommandChanged(index,value);
}

float StatusGroundDrive::getBodyCommand_Forward() const
{
   QMutexLocker locker(mutex);
   return data.BodyCommand[0];
}
void StatusGroundDrive::setBodyCommand_Forward(float value)
{
   mutex->lock();
   bool changed = data.BodyCommand[0] != value;
   data.BodyCommand[0] = value;
   mutex->unlock();
   if (changed) emit BodyCommand_ForwardChanged(value);
}

float StatusGroundDrive::getBodyCommand_Right() const
{
   QMutexLocker locker(mutex);
   return data.BodyCommand[1];
}
void StatusGroundDrive::setBodyCommand_Right(float value)
{
   mutex->lock();
   bool changed = data.BodyCommand[1] != value;
   data.BodyCommand[1] = value;
   mutex->unlock();
   if (changed) emit BodyCommand_RightChanged(value);
}

float StatusGroundDrive::getControlCommand(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ControlCommand[index];
}
void StatusGroundDrive::setControlCommand(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ControlCommand[index] != value;
   data.ControlCommand[index] = value;
   mutex->unlock();
   if (changed) emit ControlCommandChanged(index,value);
}

float StatusGroundDrive::getControlCommand_Speed() const
{
   QMutexLocker locker(mutex);
   return data.ControlCommand[0];
}
void StatusGroundDrive::setControlCommand_Speed(float value)
{
   mutex->lock();
   bool changed = data.ControlCommand[0] != value;
   data.ControlCommand[0] = value;
   mutex->unlock();
   if (changed) emit ControlCommand_SpeedChanged(value);
}

float StatusGroundDrive::getControlCommand_Course() const
{
   QMutexLocker locker(mutex);
   return data.ControlCommand[1];
}
void StatusGroundDrive::setControlCommand_Course(float value)
{
   mutex->lock();
   bool changed = data.ControlCommand[1] != value;
   data.ControlCommand[1] = value;
   mutex->unlock();
   if (changed) emit ControlCommand_CourseChanged(value);
}

quint8 StatusGroundDrive::getControlState() const
{
   QMutexLocker locker(mutex);
   return data.ControlState;
}
void StatusGroundDrive::setControlState(quint8 value)
{
   mutex->lock();
   bool changed = data.ControlState != value;
   data.ControlState = value;
   mutex->unlock();
   if (changed) emit ControlStateChanged(value);
}


