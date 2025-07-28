/**
 ******************************************************************************
 *
 * @file       groundpathfollowersettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: groundpathfollowersettings.xml.
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

#include "groundpathfollowersettings.h"
#include "uavobjectfield.h"

const QString GroundPathFollowerSettings::NAME = QString("GroundPathFollowerSettings");
const QString GroundPathFollowerSettings::DESCRIPTION = QString("Settings for the @ref GroundPathFollowerModule");
const QString GroundPathFollowerSettings::CATEGORY = QString("Control");

/**
 * Constructor
 */
GroundPathFollowerSettings::GroundPathFollowerSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList HorizontalVelMaxElemNames;
    HorizontalVelMaxElemNames.append("0");
    fields.append( new UAVObjectField(QString("HorizontalVelMax"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, HorizontalVelMaxElemNames, QStringList(), QString("")));
    QStringList HorizontalVelMinElemNames;
    HorizontalVelMinElemNames.append("0");
    fields.append( new UAVObjectField(QString("HorizontalVelMin"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, HorizontalVelMinElemNames, QStringList(), QString("")));
    QStringList CourseFeedForwardElemNames;
    CourseFeedForwardElemNames.append("0");
    fields.append( new UAVObjectField(QString("CourseFeedForward"), tr(""), QString("s"), UAVObjectField::FLOAT32, CourseFeedForwardElemNames, QStringList(), QString("")));
    QStringList VelocityFeedForwardElemNames;
    VelocityFeedForwardElemNames.append("0");
    fields.append( new UAVObjectField(QString("VelocityFeedForward"), tr(""), QString("s"), UAVObjectField::FLOAT32, VelocityFeedForwardElemNames, QStringList(), QString("")));
    QStringList HorizontalPosPElemNames;
    HorizontalPosPElemNames.append("0");
    fields.append( new UAVObjectField(QString("HorizontalPosP"), tr(""), QString("(m/s)/m"), UAVObjectField::FLOAT32, HorizontalPosPElemNames, QStringList(), QString("")));
    QStringList SpeedPIElemNames;
    SpeedPIElemNames.append("Kp");
    SpeedPIElemNames.append("Ki");
    SpeedPIElemNames.append("Kd");
    SpeedPIElemNames.append("Beta");
    fields.append( new UAVObjectField(QString("SpeedPI"), tr(""), QString("deg / (m/s)"), UAVObjectField::FLOAT32, SpeedPIElemNames, QStringList(), QString("")));
    QStringList ThrustLimitElemNames;
    ThrustLimitElemNames.append("Min");
    ThrustLimitElemNames.append("SlowForward");
    ThrustLimitElemNames.append("Max");
    fields.append( new UAVObjectField(QString("ThrustLimit"), tr(""), QString(""), UAVObjectField::FLOAT32, ThrustLimitElemNames, QStringList(), QString("")));
    QStringList UpdatePeriodElemNames;
    UpdatePeriodElemNames.append("0");
    fields.append( new UAVObjectField(QString("UpdatePeriod"), tr(""), QString("ms"), UAVObjectField::INT32, UpdatePeriodElemNames, QStringList(), QString("")));

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
UAVObject::Metadata GroundPathFollowerSettings::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        1 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        1 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_ONCHANGE << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_ONCHANGE << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
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
void GroundPathFollowerSettings::setDefaultFieldValues()
{
    data.HorizontalVelMax = 2;
    data.HorizontalVelMin = 0;
    data.CourseFeedForward = 3;
    data.VelocityFeedForward = 0.1;
    data.HorizontalPosP = 0.2;
    data.SpeedPI[0] = 0.1;
    data.SpeedPI[1] = 0.1;
    data.SpeedPI[2] = 0.001;
    data.SpeedPI[3] = 0.8;
    data.ThrustLimit[0] = -0.3;
    data.ThrustLimit[1] = 0.15;
    data.ThrustLimit[2] = 0.3;
    data.UpdatePeriod = 100;

}

/**
 * Get the object data fields
 */
GroundPathFollowerSettings::DataFields GroundPathFollowerSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void GroundPathFollowerSettings::setData(const DataFields& data)
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

void GroundPathFollowerSettings::emitNotifications()
{
            //if (data.HorizontalVelMax != oldData.HorizontalVelMax)
            emit HorizontalVelMaxChanged(data.HorizontalVelMax);
        //if (data.HorizontalVelMin != oldData.HorizontalVelMin)
            emit HorizontalVelMinChanged(data.HorizontalVelMin);
        //if (data.CourseFeedForward != oldData.CourseFeedForward)
            emit CourseFeedForwardChanged(data.CourseFeedForward);
        //if (data.VelocityFeedForward != oldData.VelocityFeedForward)
            emit VelocityFeedForwardChanged(data.VelocityFeedForward);
        //if (data.HorizontalPosP != oldData.HorizontalPosP)
            emit HorizontalPosPChanged(data.HorizontalPosP);
        //if (data.SpeedPI[0] != oldData.SpeedPI[0])
            emit SpeedPI_KpChanged(data.SpeedPI[0]);
        //if (data.SpeedPI[1] != oldData.SpeedPI[1])
            emit SpeedPI_KiChanged(data.SpeedPI[1]);
        //if (data.SpeedPI[2] != oldData.SpeedPI[2])
            emit SpeedPI_KdChanged(data.SpeedPI[2]);
        //if (data.SpeedPI[3] != oldData.SpeedPI[3])
            emit SpeedPI_BetaChanged(data.SpeedPI[3]);
        //if (data.ThrustLimit[0] != oldData.ThrustLimit[0])
            emit ThrustLimit_MinChanged(data.ThrustLimit[0]);
        //if (data.ThrustLimit[1] != oldData.ThrustLimit[1])
            emit ThrustLimit_SlowForwardChanged(data.ThrustLimit[1]);
        //if (data.ThrustLimit[2] != oldData.ThrustLimit[2])
            emit ThrustLimit_MaxChanged(data.ThrustLimit[2]);
        //if (data.UpdatePeriod != oldData.UpdatePeriod)
            emit UpdatePeriodChanged(data.UpdatePeriod);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *GroundPathFollowerSettings::clone(quint32 instID)
{
    GroundPathFollowerSettings *obj = new GroundPathFollowerSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *GroundPathFollowerSettings::dirtyClone()
{
    GroundPathFollowerSettings *obj = new GroundPathFollowerSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
GroundPathFollowerSettings *GroundPathFollowerSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<GroundPathFollowerSettings *>(objMngr->getObject(GroundPathFollowerSettings::OBJID, instID));
}

float GroundPathFollowerSettings::getHorizontalVelMax() const
{
   QMutexLocker locker(mutex);
   return data.HorizontalVelMax;
}
void GroundPathFollowerSettings::setHorizontalVelMax(float value)
{
   mutex->lock();
   bool changed = data.HorizontalVelMax != value;
   data.HorizontalVelMax = value;
   mutex->unlock();
   if (changed) emit HorizontalVelMaxChanged(value);
}

float GroundPathFollowerSettings::getHorizontalVelMin() const
{
   QMutexLocker locker(mutex);
   return data.HorizontalVelMin;
}
void GroundPathFollowerSettings::setHorizontalVelMin(float value)
{
   mutex->lock();
   bool changed = data.HorizontalVelMin != value;
   data.HorizontalVelMin = value;
   mutex->unlock();
   if (changed) emit HorizontalVelMinChanged(value);
}

float GroundPathFollowerSettings::getCourseFeedForward() const
{
   QMutexLocker locker(mutex);
   return data.CourseFeedForward;
}
void GroundPathFollowerSettings::setCourseFeedForward(float value)
{
   mutex->lock();
   bool changed = data.CourseFeedForward != value;
   data.CourseFeedForward = value;
   mutex->unlock();
   if (changed) emit CourseFeedForwardChanged(value);
}

float GroundPathFollowerSettings::getVelocityFeedForward() const
{
   QMutexLocker locker(mutex);
   return data.VelocityFeedForward;
}
void GroundPathFollowerSettings::setVelocityFeedForward(float value)
{
   mutex->lock();
   bool changed = data.VelocityFeedForward != value;
   data.VelocityFeedForward = value;
   mutex->unlock();
   if (changed) emit VelocityFeedForwardChanged(value);
}

float GroundPathFollowerSettings::getHorizontalPosP() const
{
   QMutexLocker locker(mutex);
   return data.HorizontalPosP;
}
void GroundPathFollowerSettings::setHorizontalPosP(float value)
{
   mutex->lock();
   bool changed = data.HorizontalPosP != value;
   data.HorizontalPosP = value;
   mutex->unlock();
   if (changed) emit HorizontalPosPChanged(value);
}

float GroundPathFollowerSettings::getSpeedPI(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.SpeedPI[index];
}
void GroundPathFollowerSettings::setSpeedPI(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.SpeedPI[index] != value;
   data.SpeedPI[index] = value;
   mutex->unlock();
   if (changed) emit SpeedPIChanged(index,value);
}

float GroundPathFollowerSettings::getSpeedPI_Kp() const
{
   QMutexLocker locker(mutex);
   return data.SpeedPI[0];
}
void GroundPathFollowerSettings::setSpeedPI_Kp(float value)
{
   mutex->lock();
   bool changed = data.SpeedPI[0] != value;
   data.SpeedPI[0] = value;
   mutex->unlock();
   if (changed) emit SpeedPI_KpChanged(value);
}

float GroundPathFollowerSettings::getSpeedPI_Ki() const
{
   QMutexLocker locker(mutex);
   return data.SpeedPI[1];
}
void GroundPathFollowerSettings::setSpeedPI_Ki(float value)
{
   mutex->lock();
   bool changed = data.SpeedPI[1] != value;
   data.SpeedPI[1] = value;
   mutex->unlock();
   if (changed) emit SpeedPI_KiChanged(value);
}

float GroundPathFollowerSettings::getSpeedPI_Kd() const
{
   QMutexLocker locker(mutex);
   return data.SpeedPI[2];
}
void GroundPathFollowerSettings::setSpeedPI_Kd(float value)
{
   mutex->lock();
   bool changed = data.SpeedPI[2] != value;
   data.SpeedPI[2] = value;
   mutex->unlock();
   if (changed) emit SpeedPI_KdChanged(value);
}

float GroundPathFollowerSettings::getSpeedPI_Beta() const
{
   QMutexLocker locker(mutex);
   return data.SpeedPI[3];
}
void GroundPathFollowerSettings::setSpeedPI_Beta(float value)
{
   mutex->lock();
   bool changed = data.SpeedPI[3] != value;
   data.SpeedPI[3] = value;
   mutex->unlock();
   if (changed) emit SpeedPI_BetaChanged(value);
}

float GroundPathFollowerSettings::getThrustLimit(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ThrustLimit[index];
}
void GroundPathFollowerSettings::setThrustLimit(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ThrustLimit[index] != value;
   data.ThrustLimit[index] = value;
   mutex->unlock();
   if (changed) emit ThrustLimitChanged(index,value);
}

float GroundPathFollowerSettings::getThrustLimit_Min() const
{
   QMutexLocker locker(mutex);
   return data.ThrustLimit[0];
}
void GroundPathFollowerSettings::setThrustLimit_Min(float value)
{
   mutex->lock();
   bool changed = data.ThrustLimit[0] != value;
   data.ThrustLimit[0] = value;
   mutex->unlock();
   if (changed) emit ThrustLimit_MinChanged(value);
}

float GroundPathFollowerSettings::getThrustLimit_SlowForward() const
{
   QMutexLocker locker(mutex);
   return data.ThrustLimit[1];
}
void GroundPathFollowerSettings::setThrustLimit_SlowForward(float value)
{
   mutex->lock();
   bool changed = data.ThrustLimit[1] != value;
   data.ThrustLimit[1] = value;
   mutex->unlock();
   if (changed) emit ThrustLimit_SlowForwardChanged(value);
}

float GroundPathFollowerSettings::getThrustLimit_Max() const
{
   QMutexLocker locker(mutex);
   return data.ThrustLimit[2];
}
void GroundPathFollowerSettings::setThrustLimit_Max(float value)
{
   mutex->lock();
   bool changed = data.ThrustLimit[2] != value;
   data.ThrustLimit[2] = value;
   mutex->unlock();
   if (changed) emit ThrustLimit_MaxChanged(value);
}

qint32 GroundPathFollowerSettings::getUpdatePeriod() const
{
   QMutexLocker locker(mutex);
   return data.UpdatePeriod;
}
void GroundPathFollowerSettings::setUpdatePeriod(qint32 value)
{
   mutex->lock();
   bool changed = data.UpdatePeriod != value;
   data.UpdatePeriod = value;
   mutex->unlock();
   if (changed) emit UpdatePeriodChanged(value);
}


