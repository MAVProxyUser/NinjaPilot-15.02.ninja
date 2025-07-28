/**
 ******************************************************************************
 *
 * @file       fixedwingpathfollowerstatus.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: fixedwingpathfollowerstatus.xml.
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

#include "fixedwingpathfollowerstatus.h"
#include "uavobjectfield.h"

const QString FixedWingPathFollowerStatus::NAME = QString("FixedWingPathFollowerStatus");
const QString FixedWingPathFollowerStatus::DESCRIPTION = QString("Object Storing Debugging Information on PID internals");
const QString FixedWingPathFollowerStatus::CATEGORY = QString("Control");

/**
 * Constructor
 */
FixedWingPathFollowerStatus::FixedWingPathFollowerStatus(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList ErrorElemNames;
    ErrorElemNames.append("Course");
    ErrorElemNames.append("Speed");
    ErrorElemNames.append("Power");
    fields.append( new UAVObjectField(QString("Error"), tr(""), QString(""), UAVObjectField::FLOAT32, ErrorElemNames, QStringList(), QString("")));
    QStringList ErrorIntElemNames;
    ErrorIntElemNames.append("Course");
    ErrorIntElemNames.append("Speed");
    ErrorIntElemNames.append("Power");
    fields.append( new UAVObjectField(QString("ErrorInt"), tr(""), QString(""), UAVObjectField::FLOAT32, ErrorIntElemNames, QStringList(), QString("")));
    QStringList CommandElemNames;
    CommandElemNames.append("Course");
    CommandElemNames.append("Speed");
    CommandElemNames.append("Power");
    fields.append( new UAVObjectField(QString("Command"), tr(""), QString(""), UAVObjectField::FLOAT32, CommandElemNames, QStringList(), QString("")));
    QStringList ErrorsElemNames;
    ErrorsElemNames.append("Wind");
    ErrorsElemNames.append("Stallspeed");
    ErrorsElemNames.append("Lowspeed");
    ErrorsElemNames.append("Highspeed");
    ErrorsElemNames.append("Overspeed");
    ErrorsElemNames.append("Lowpower");
    ErrorsElemNames.append("Highpower");
    ErrorsElemNames.append("Pitchcontrol");
    fields.append( new UAVObjectField(QString("Errors"), tr(""), QString(""), UAVObjectField::UINT8, ErrorsElemNames, QStringList(), QString("")));

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
UAVObject::Metadata FixedWingPathFollowerStatus::getDefaultMetadata()
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
    metadata.flightTelemetryUpdatePeriod = 500;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void FixedWingPathFollowerStatus::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
FixedWingPathFollowerStatus::DataFields FixedWingPathFollowerStatus::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void FixedWingPathFollowerStatus::setData(const DataFields& data)
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

void FixedWingPathFollowerStatus::emitNotifications()
{
            //if (data.Error[0] != oldData.Error[0])
            emit Error_CourseChanged(data.Error[0]);
        //if (data.Error[1] != oldData.Error[1])
            emit Error_SpeedChanged(data.Error[1]);
        //if (data.Error[2] != oldData.Error[2])
            emit Error_PowerChanged(data.Error[2]);
        //if (data.ErrorInt[0] != oldData.ErrorInt[0])
            emit ErrorInt_CourseChanged(data.ErrorInt[0]);
        //if (data.ErrorInt[1] != oldData.ErrorInt[1])
            emit ErrorInt_SpeedChanged(data.ErrorInt[1]);
        //if (data.ErrorInt[2] != oldData.ErrorInt[2])
            emit ErrorInt_PowerChanged(data.ErrorInt[2]);
        //if (data.Command[0] != oldData.Command[0])
            emit Command_CourseChanged(data.Command[0]);
        //if (data.Command[1] != oldData.Command[1])
            emit Command_SpeedChanged(data.Command[1]);
        //if (data.Command[2] != oldData.Command[2])
            emit Command_PowerChanged(data.Command[2]);
        //if (data.Errors[0] != oldData.Errors[0])
            emit Errors_WindChanged(data.Errors[0]);
        //if (data.Errors[1] != oldData.Errors[1])
            emit Errors_StallspeedChanged(data.Errors[1]);
        //if (data.Errors[2] != oldData.Errors[2])
            emit Errors_LowspeedChanged(data.Errors[2]);
        //if (data.Errors[3] != oldData.Errors[3])
            emit Errors_HighspeedChanged(data.Errors[3]);
        //if (data.Errors[4] != oldData.Errors[4])
            emit Errors_OverspeedChanged(data.Errors[4]);
        //if (data.Errors[5] != oldData.Errors[5])
            emit Errors_LowpowerChanged(data.Errors[5]);
        //if (data.Errors[6] != oldData.Errors[6])
            emit Errors_HighpowerChanged(data.Errors[6]);
        //if (data.Errors[7] != oldData.Errors[7])
            emit Errors_PitchcontrolChanged(data.Errors[7]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *FixedWingPathFollowerStatus::clone(quint32 instID)
{
    FixedWingPathFollowerStatus *obj = new FixedWingPathFollowerStatus();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *FixedWingPathFollowerStatus::dirtyClone()
{
    FixedWingPathFollowerStatus *obj = new FixedWingPathFollowerStatus();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
FixedWingPathFollowerStatus *FixedWingPathFollowerStatus::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<FixedWingPathFollowerStatus *>(objMngr->getObject(FixedWingPathFollowerStatus::OBJID, instID));
}

float FixedWingPathFollowerStatus::getError(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Error[index];
}
void FixedWingPathFollowerStatus::setError(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.Error[index] != value;
   data.Error[index] = value;
   mutex->unlock();
   if (changed) emit ErrorChanged(index,value);
}

float FixedWingPathFollowerStatus::getError_Course() const
{
   QMutexLocker locker(mutex);
   return data.Error[0];
}
void FixedWingPathFollowerStatus::setError_Course(float value)
{
   mutex->lock();
   bool changed = data.Error[0] != value;
   data.Error[0] = value;
   mutex->unlock();
   if (changed) emit Error_CourseChanged(value);
}

float FixedWingPathFollowerStatus::getError_Speed() const
{
   QMutexLocker locker(mutex);
   return data.Error[1];
}
void FixedWingPathFollowerStatus::setError_Speed(float value)
{
   mutex->lock();
   bool changed = data.Error[1] != value;
   data.Error[1] = value;
   mutex->unlock();
   if (changed) emit Error_SpeedChanged(value);
}

float FixedWingPathFollowerStatus::getError_Power() const
{
   QMutexLocker locker(mutex);
   return data.Error[2];
}
void FixedWingPathFollowerStatus::setError_Power(float value)
{
   mutex->lock();
   bool changed = data.Error[2] != value;
   data.Error[2] = value;
   mutex->unlock();
   if (changed) emit Error_PowerChanged(value);
}

float FixedWingPathFollowerStatus::getErrorInt(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ErrorInt[index];
}
void FixedWingPathFollowerStatus::setErrorInt(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ErrorInt[index] != value;
   data.ErrorInt[index] = value;
   mutex->unlock();
   if (changed) emit ErrorIntChanged(index,value);
}

float FixedWingPathFollowerStatus::getErrorInt_Course() const
{
   QMutexLocker locker(mutex);
   return data.ErrorInt[0];
}
void FixedWingPathFollowerStatus::setErrorInt_Course(float value)
{
   mutex->lock();
   bool changed = data.ErrorInt[0] != value;
   data.ErrorInt[0] = value;
   mutex->unlock();
   if (changed) emit ErrorInt_CourseChanged(value);
}

float FixedWingPathFollowerStatus::getErrorInt_Speed() const
{
   QMutexLocker locker(mutex);
   return data.ErrorInt[1];
}
void FixedWingPathFollowerStatus::setErrorInt_Speed(float value)
{
   mutex->lock();
   bool changed = data.ErrorInt[1] != value;
   data.ErrorInt[1] = value;
   mutex->unlock();
   if (changed) emit ErrorInt_SpeedChanged(value);
}

float FixedWingPathFollowerStatus::getErrorInt_Power() const
{
   QMutexLocker locker(mutex);
   return data.ErrorInt[2];
}
void FixedWingPathFollowerStatus::setErrorInt_Power(float value)
{
   mutex->lock();
   bool changed = data.ErrorInt[2] != value;
   data.ErrorInt[2] = value;
   mutex->unlock();
   if (changed) emit ErrorInt_PowerChanged(value);
}

float FixedWingPathFollowerStatus::getCommand(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Command[index];
}
void FixedWingPathFollowerStatus::setCommand(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.Command[index] != value;
   data.Command[index] = value;
   mutex->unlock();
   if (changed) emit CommandChanged(index,value);
}

float FixedWingPathFollowerStatus::getCommand_Course() const
{
   QMutexLocker locker(mutex);
   return data.Command[0];
}
void FixedWingPathFollowerStatus::setCommand_Course(float value)
{
   mutex->lock();
   bool changed = data.Command[0] != value;
   data.Command[0] = value;
   mutex->unlock();
   if (changed) emit Command_CourseChanged(value);
}

float FixedWingPathFollowerStatus::getCommand_Speed() const
{
   QMutexLocker locker(mutex);
   return data.Command[1];
}
void FixedWingPathFollowerStatus::setCommand_Speed(float value)
{
   mutex->lock();
   bool changed = data.Command[1] != value;
   data.Command[1] = value;
   mutex->unlock();
   if (changed) emit Command_SpeedChanged(value);
}

float FixedWingPathFollowerStatus::getCommand_Power() const
{
   QMutexLocker locker(mutex);
   return data.Command[2];
}
void FixedWingPathFollowerStatus::setCommand_Power(float value)
{
   mutex->lock();
   bool changed = data.Command[2] != value;
   data.Command[2] = value;
   mutex->unlock();
   if (changed) emit Command_PowerChanged(value);
}

quint8 FixedWingPathFollowerStatus::getErrors(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Errors[index];
}
void FixedWingPathFollowerStatus::setErrors(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.Errors[index] != value;
   data.Errors[index] = value;
   mutex->unlock();
   if (changed) emit ErrorsChanged(index,value);
}

quint8 FixedWingPathFollowerStatus::getErrors_Wind() const
{
   QMutexLocker locker(mutex);
   return data.Errors[0];
}
void FixedWingPathFollowerStatus::setErrors_Wind(quint8 value)
{
   mutex->lock();
   bool changed = data.Errors[0] != value;
   data.Errors[0] = value;
   mutex->unlock();
   if (changed) emit Errors_WindChanged(value);
}

quint8 FixedWingPathFollowerStatus::getErrors_Stallspeed() const
{
   QMutexLocker locker(mutex);
   return data.Errors[1];
}
void FixedWingPathFollowerStatus::setErrors_Stallspeed(quint8 value)
{
   mutex->lock();
   bool changed = data.Errors[1] != value;
   data.Errors[1] = value;
   mutex->unlock();
   if (changed) emit Errors_StallspeedChanged(value);
}

quint8 FixedWingPathFollowerStatus::getErrors_Lowspeed() const
{
   QMutexLocker locker(mutex);
   return data.Errors[2];
}
void FixedWingPathFollowerStatus::setErrors_Lowspeed(quint8 value)
{
   mutex->lock();
   bool changed = data.Errors[2] != value;
   data.Errors[2] = value;
   mutex->unlock();
   if (changed) emit Errors_LowspeedChanged(value);
}

quint8 FixedWingPathFollowerStatus::getErrors_Highspeed() const
{
   QMutexLocker locker(mutex);
   return data.Errors[3];
}
void FixedWingPathFollowerStatus::setErrors_Highspeed(quint8 value)
{
   mutex->lock();
   bool changed = data.Errors[3] != value;
   data.Errors[3] = value;
   mutex->unlock();
   if (changed) emit Errors_HighspeedChanged(value);
}

quint8 FixedWingPathFollowerStatus::getErrors_Overspeed() const
{
   QMutexLocker locker(mutex);
   return data.Errors[4];
}
void FixedWingPathFollowerStatus::setErrors_Overspeed(quint8 value)
{
   mutex->lock();
   bool changed = data.Errors[4] != value;
   data.Errors[4] = value;
   mutex->unlock();
   if (changed) emit Errors_OverspeedChanged(value);
}

quint8 FixedWingPathFollowerStatus::getErrors_Lowpower() const
{
   QMutexLocker locker(mutex);
   return data.Errors[5];
}
void FixedWingPathFollowerStatus::setErrors_Lowpower(quint8 value)
{
   mutex->lock();
   bool changed = data.Errors[5] != value;
   data.Errors[5] = value;
   mutex->unlock();
   if (changed) emit Errors_LowpowerChanged(value);
}

quint8 FixedWingPathFollowerStatus::getErrors_Highpower() const
{
   QMutexLocker locker(mutex);
   return data.Errors[6];
}
void FixedWingPathFollowerStatus::setErrors_Highpower(quint8 value)
{
   mutex->lock();
   bool changed = data.Errors[6] != value;
   data.Errors[6] = value;
   mutex->unlock();
   if (changed) emit Errors_HighpowerChanged(value);
}

quint8 FixedWingPathFollowerStatus::getErrors_Pitchcontrol() const
{
   QMutexLocker locker(mutex);
   return data.Errors[7];
}
void FixedWingPathFollowerStatus::setErrors_Pitchcontrol(quint8 value)
{
   mutex->lock();
   bool changed = data.Errors[7] != value;
   data.Errors[7] = value;
   mutex->unlock();
   if (changed) emit Errors_PitchcontrolChanged(value);
}


