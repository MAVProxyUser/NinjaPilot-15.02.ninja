/**
 ******************************************************************************
 *
 * @file       stabilizationstatus.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: stabilizationstatus.xml.
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

#include "stabilizationstatus.h"
#include "uavobjectfield.h"

const QString StabilizationStatus::NAME = QString("StabilizationStatus");
const QString StabilizationStatus::DESCRIPTION = QString("Contains status information to control submodules for stabilization.");
const QString StabilizationStatus::CATEGORY = QString("Control");

/**
 * Constructor
 */
StabilizationStatus::StabilizationStatus(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList OuterLoopElemNames;
    OuterLoopElemNames.append("Roll");
    OuterLoopElemNames.append("Pitch");
    OuterLoopElemNames.append("Yaw");
    OuterLoopElemNames.append("Thrust");
    QStringList OuterLoopEnumOptions;
    OuterLoopEnumOptions.append("Direct");
    OuterLoopEnumOptions.append("Attitude");
    OuterLoopEnumOptions.append("Rattitude");
    OuterLoopEnumOptions.append("Weakleveling");
    OuterLoopEnumOptions.append("Altitude");
    OuterLoopEnumOptions.append("AltitudeVario");
    fields.append( new UAVObjectField(QString("OuterLoop"), tr(""), QString(""), UAVObjectField::ENUM, OuterLoopElemNames, OuterLoopEnumOptions, QString("")));
    QStringList InnerLoopElemNames;
    InnerLoopElemNames.append("Roll");
    InnerLoopElemNames.append("Pitch");
    InnerLoopElemNames.append("Yaw");
    InnerLoopElemNames.append("Thrust");
    QStringList InnerLoopEnumOptions;
    InnerLoopEnumOptions.append("Direct");
    InnerLoopEnumOptions.append("VirtualFlyBar");
    InnerLoopEnumOptions.append("Acro+");
    InnerLoopEnumOptions.append("AxisLock");
    InnerLoopEnumOptions.append("Rate");
    InnerLoopEnumOptions.append("CruiseControl");
    fields.append( new UAVObjectField(QString("InnerLoop"), tr(""), QString(""), UAVObjectField::ENUM, InnerLoopElemNames, InnerLoopEnumOptions, QString("")));

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
UAVObject::Metadata StabilizationStatus::getDefaultMetadata()
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
    metadata.flightTelemetryUpdatePeriod = 5000;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void StabilizationStatus::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
StabilizationStatus::DataFields StabilizationStatus::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void StabilizationStatus::setData(const DataFields& data)
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

void StabilizationStatus::emitNotifications()
{
            //if (data.OuterLoop[0] != oldData.OuterLoop[0])
            emit OuterLoop_RollChanged(data.OuterLoop[0]);
        //if (data.OuterLoop[1] != oldData.OuterLoop[1])
            emit OuterLoop_PitchChanged(data.OuterLoop[1]);
        //if (data.OuterLoop[2] != oldData.OuterLoop[2])
            emit OuterLoop_YawChanged(data.OuterLoop[2]);
        //if (data.OuterLoop[3] != oldData.OuterLoop[3])
            emit OuterLoop_ThrustChanged(data.OuterLoop[3]);
        //if (data.InnerLoop[0] != oldData.InnerLoop[0])
            emit InnerLoop_RollChanged(data.InnerLoop[0]);
        //if (data.InnerLoop[1] != oldData.InnerLoop[1])
            emit InnerLoop_PitchChanged(data.InnerLoop[1]);
        //if (data.InnerLoop[2] != oldData.InnerLoop[2])
            emit InnerLoop_YawChanged(data.InnerLoop[2]);
        //if (data.InnerLoop[3] != oldData.InnerLoop[3])
            emit InnerLoop_ThrustChanged(data.InnerLoop[3]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *StabilizationStatus::clone(quint32 instID)
{
    StabilizationStatus *obj = new StabilizationStatus();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *StabilizationStatus::dirtyClone()
{
    StabilizationStatus *obj = new StabilizationStatus();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
StabilizationStatus *StabilizationStatus::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<StabilizationStatus *>(objMngr->getObject(StabilizationStatus::OBJID, instID));
}

quint8 StabilizationStatus::getOuterLoop(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.OuterLoop[index];
}
void StabilizationStatus::setOuterLoop(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.OuterLoop[index] != value;
   data.OuterLoop[index] = value;
   mutex->unlock();
   if (changed) emit OuterLoopChanged(index,value);
}

quint8 StabilizationStatus::getOuterLoop_Roll() const
{
   QMutexLocker locker(mutex);
   return data.OuterLoop[0];
}
void StabilizationStatus::setOuterLoop_Roll(quint8 value)
{
   mutex->lock();
   bool changed = data.OuterLoop[0] != value;
   data.OuterLoop[0] = value;
   mutex->unlock();
   if (changed) emit OuterLoop_RollChanged(value);
}

quint8 StabilizationStatus::getOuterLoop_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.OuterLoop[1];
}
void StabilizationStatus::setOuterLoop_Pitch(quint8 value)
{
   mutex->lock();
   bool changed = data.OuterLoop[1] != value;
   data.OuterLoop[1] = value;
   mutex->unlock();
   if (changed) emit OuterLoop_PitchChanged(value);
}

quint8 StabilizationStatus::getOuterLoop_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.OuterLoop[2];
}
void StabilizationStatus::setOuterLoop_Yaw(quint8 value)
{
   mutex->lock();
   bool changed = data.OuterLoop[2] != value;
   data.OuterLoop[2] = value;
   mutex->unlock();
   if (changed) emit OuterLoop_YawChanged(value);
}

quint8 StabilizationStatus::getOuterLoop_Thrust() const
{
   QMutexLocker locker(mutex);
   return data.OuterLoop[3];
}
void StabilizationStatus::setOuterLoop_Thrust(quint8 value)
{
   mutex->lock();
   bool changed = data.OuterLoop[3] != value;
   data.OuterLoop[3] = value;
   mutex->unlock();
   if (changed) emit OuterLoop_ThrustChanged(value);
}

quint8 StabilizationStatus::getInnerLoop(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.InnerLoop[index];
}
void StabilizationStatus::setInnerLoop(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.InnerLoop[index] != value;
   data.InnerLoop[index] = value;
   mutex->unlock();
   if (changed) emit InnerLoopChanged(index,value);
}

quint8 StabilizationStatus::getInnerLoop_Roll() const
{
   QMutexLocker locker(mutex);
   return data.InnerLoop[0];
}
void StabilizationStatus::setInnerLoop_Roll(quint8 value)
{
   mutex->lock();
   bool changed = data.InnerLoop[0] != value;
   data.InnerLoop[0] = value;
   mutex->unlock();
   if (changed) emit InnerLoop_RollChanged(value);
}

quint8 StabilizationStatus::getInnerLoop_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.InnerLoop[1];
}
void StabilizationStatus::setInnerLoop_Pitch(quint8 value)
{
   mutex->lock();
   bool changed = data.InnerLoop[1] != value;
   data.InnerLoop[1] = value;
   mutex->unlock();
   if (changed) emit InnerLoop_PitchChanged(value);
}

quint8 StabilizationStatus::getInnerLoop_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.InnerLoop[2];
}
void StabilizationStatus::setInnerLoop_Yaw(quint8 value)
{
   mutex->lock();
   bool changed = data.InnerLoop[2] != value;
   data.InnerLoop[2] = value;
   mutex->unlock();
   if (changed) emit InnerLoop_YawChanged(value);
}

quint8 StabilizationStatus::getInnerLoop_Thrust() const
{
   QMutexLocker locker(mutex);
   return data.InnerLoop[3];
}
void StabilizationStatus::setInnerLoop_Thrust(quint8 value)
{
   mutex->lock();
   bool changed = data.InnerLoop[3] != value;
   data.InnerLoop[3] = value;
   mutex->unlock();
   if (changed) emit InnerLoop_ThrustChanged(value);
}


