/**
 ******************************************************************************
 *
 * @file       stabilizationdesired.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: stabilizationdesired.xml.
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

#include "stabilizationdesired.h"
#include "uavobjectfield.h"

const QString StabilizationDesired::NAME = QString("StabilizationDesired");
const QString StabilizationDesired::DESCRIPTION = QString("The desired attitude that @ref StabilizationModule will try and achieve if FlightMode is Stabilized.  Comes from @ref ManaulControlModule.");
const QString StabilizationDesired::CATEGORY = QString("Control");

/**
 * Constructor
 */
StabilizationDesired::StabilizationDesired(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList RollElemNames;
    RollElemNames.append("0");
    fields.append( new UAVObjectField(QString("Roll"), tr(""), QString("degrees"), UAVObjectField::FLOAT32, RollElemNames, QStringList(), QString("")));
    QStringList PitchElemNames;
    PitchElemNames.append("0");
    fields.append( new UAVObjectField(QString("Pitch"), tr(""), QString("degrees"), UAVObjectField::FLOAT32, PitchElemNames, QStringList(), QString("")));
    QStringList YawElemNames;
    YawElemNames.append("0");
    fields.append( new UAVObjectField(QString("Yaw"), tr(""), QString("degrees"), UAVObjectField::FLOAT32, YawElemNames, QStringList(), QString("")));
    QStringList ThrustElemNames;
    ThrustElemNames.append("0");
    fields.append( new UAVObjectField(QString("Thrust"), tr(""), QString("%"), UAVObjectField::FLOAT32, ThrustElemNames, QStringList(), QString("")));
    QStringList StabilizationModeElemNames;
    StabilizationModeElemNames.append("Roll");
    StabilizationModeElemNames.append("Pitch");
    StabilizationModeElemNames.append("Yaw");
    StabilizationModeElemNames.append("Thrust");
    QStringList StabilizationModeEnumOptions;
    StabilizationModeEnumOptions.append("Manual");
    StabilizationModeEnumOptions.append("Rate");
    StabilizationModeEnumOptions.append("Attitude");
    StabilizationModeEnumOptions.append("AxisLock");
    StabilizationModeEnumOptions.append("WeakLeveling");
    StabilizationModeEnumOptions.append("VirtualBar");
    StabilizationModeEnumOptions.append("Acro+");
    StabilizationModeEnumOptions.append("Rattitude");
    StabilizationModeEnumOptions.append("AltitudeHold");
    StabilizationModeEnumOptions.append("AltitudeVario");
    StabilizationModeEnumOptions.append("CruiseControl");
    fields.append( new UAVObjectField(QString("StabilizationMode"), tr(""), QString(""), UAVObjectField::ENUM, StabilizationModeElemNames, StabilizationModeEnumOptions, QString("")));

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
UAVObject::Metadata StabilizationDesired::getDefaultMetadata()
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
void StabilizationDesired::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
StabilizationDesired::DataFields StabilizationDesired::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void StabilizationDesired::setData(const DataFields& data)
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

void StabilizationDesired::emitNotifications()
{
            //if (data.Roll != oldData.Roll)
            emit RollChanged(data.Roll);
        //if (data.Pitch != oldData.Pitch)
            emit PitchChanged(data.Pitch);
        //if (data.Yaw != oldData.Yaw)
            emit YawChanged(data.Yaw);
        //if (data.Thrust != oldData.Thrust)
            emit ThrustChanged(data.Thrust);
        //if (data.StabilizationMode[0] != oldData.StabilizationMode[0])
            emit StabilizationMode_RollChanged(data.StabilizationMode[0]);
        //if (data.StabilizationMode[1] != oldData.StabilizationMode[1])
            emit StabilizationMode_PitchChanged(data.StabilizationMode[1]);
        //if (data.StabilizationMode[2] != oldData.StabilizationMode[2])
            emit StabilizationMode_YawChanged(data.StabilizationMode[2]);
        //if (data.StabilizationMode[3] != oldData.StabilizationMode[3])
            emit StabilizationMode_ThrustChanged(data.StabilizationMode[3]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *StabilizationDesired::clone(quint32 instID)
{
    StabilizationDesired *obj = new StabilizationDesired();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *StabilizationDesired::dirtyClone()
{
    StabilizationDesired *obj = new StabilizationDesired();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
StabilizationDesired *StabilizationDesired::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<StabilizationDesired *>(objMngr->getObject(StabilizationDesired::OBJID, instID));
}

float StabilizationDesired::getRoll() const
{
   QMutexLocker locker(mutex);
   return data.Roll;
}
void StabilizationDesired::setRoll(float value)
{
   mutex->lock();
   bool changed = data.Roll != value;
   data.Roll = value;
   mutex->unlock();
   if (changed) emit RollChanged(value);
}

float StabilizationDesired::getPitch() const
{
   QMutexLocker locker(mutex);
   return data.Pitch;
}
void StabilizationDesired::setPitch(float value)
{
   mutex->lock();
   bool changed = data.Pitch != value;
   data.Pitch = value;
   mutex->unlock();
   if (changed) emit PitchChanged(value);
}

float StabilizationDesired::getYaw() const
{
   QMutexLocker locker(mutex);
   return data.Yaw;
}
void StabilizationDesired::setYaw(float value)
{
   mutex->lock();
   bool changed = data.Yaw != value;
   data.Yaw = value;
   mutex->unlock();
   if (changed) emit YawChanged(value);
}

float StabilizationDesired::getThrust() const
{
   QMutexLocker locker(mutex);
   return data.Thrust;
}
void StabilizationDesired::setThrust(float value)
{
   mutex->lock();
   bool changed = data.Thrust != value;
   data.Thrust = value;
   mutex->unlock();
   if (changed) emit ThrustChanged(value);
}

quint8 StabilizationDesired::getStabilizationMode(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.StabilizationMode[index];
}
void StabilizationDesired::setStabilizationMode(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.StabilizationMode[index] != value;
   data.StabilizationMode[index] = value;
   mutex->unlock();
   if (changed) emit StabilizationModeChanged(index,value);
}

quint8 StabilizationDesired::getStabilizationMode_Roll() const
{
   QMutexLocker locker(mutex);
   return data.StabilizationMode[0];
}
void StabilizationDesired::setStabilizationMode_Roll(quint8 value)
{
   mutex->lock();
   bool changed = data.StabilizationMode[0] != value;
   data.StabilizationMode[0] = value;
   mutex->unlock();
   if (changed) emit StabilizationMode_RollChanged(value);
}

quint8 StabilizationDesired::getStabilizationMode_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.StabilizationMode[1];
}
void StabilizationDesired::setStabilizationMode_Pitch(quint8 value)
{
   mutex->lock();
   bool changed = data.StabilizationMode[1] != value;
   data.StabilizationMode[1] = value;
   mutex->unlock();
   if (changed) emit StabilizationMode_PitchChanged(value);
}

quint8 StabilizationDesired::getStabilizationMode_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.StabilizationMode[2];
}
void StabilizationDesired::setStabilizationMode_Yaw(quint8 value)
{
   mutex->lock();
   bool changed = data.StabilizationMode[2] != value;
   data.StabilizationMode[2] = value;
   mutex->unlock();
   if (changed) emit StabilizationMode_YawChanged(value);
}

quint8 StabilizationDesired::getStabilizationMode_Thrust() const
{
   QMutexLocker locker(mutex);
   return data.StabilizationMode[3];
}
void StabilizationDesired::setStabilizationMode_Thrust(quint8 value)
{
   mutex->lock();
   bool changed = data.StabilizationMode[3] != value;
   data.StabilizationMode[3] = value;
   mutex->unlock();
   if (changed) emit StabilizationMode_ThrustChanged(value);
}


