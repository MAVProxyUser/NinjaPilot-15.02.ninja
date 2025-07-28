/**
 ******************************************************************************
 *
 * @file       ekfstatevariance.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: ekfstatevariance.xml.
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

#include "ekfstatevariance.h"
#include "uavobjectfield.h"

const QString EKFStateVariance::NAME = QString("EKFStateVariance");
const QString EKFStateVariance::DESCRIPTION = QString("Extended Kalman Filter state covariance");
const QString EKFStateVariance::CATEGORY = QString("State");

/**
 * Constructor
 */
EKFStateVariance::EKFStateVariance(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList PElemNames;
    PElemNames.append("PositionNorth");
    PElemNames.append("PositionEast");
    PElemNames.append("PositionDown");
    PElemNames.append("VelocityNorth");
    PElemNames.append("VelocityEast");
    PElemNames.append("VelocityDown");
    PElemNames.append("AttitudeQ1");
    PElemNames.append("AttitudeQ2");
    PElemNames.append("AttitudeQ3");
    PElemNames.append("AttitudeQ4");
    PElemNames.append("GyroDriftX");
    PElemNames.append("GyroDriftY");
    PElemNames.append("GyroDriftZ");
    fields.append( new UAVObjectField(QString("P"), tr(""), QString("1^2"), UAVObjectField::FLOAT32, PElemNames, QStringList(), QString("")));

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
UAVObject::Metadata EKFStateVariance::getDefaultMetadata()
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
    metadata.flightTelemetryUpdatePeriod = 10000;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void EKFStateVariance::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
EKFStateVariance::DataFields EKFStateVariance::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void EKFStateVariance::setData(const DataFields& data)
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

void EKFStateVariance::emitNotifications()
{
            //if (data.P[0] != oldData.P[0])
            emit P_PositionNorthChanged(data.P[0]);
        //if (data.P[1] != oldData.P[1])
            emit P_PositionEastChanged(data.P[1]);
        //if (data.P[2] != oldData.P[2])
            emit P_PositionDownChanged(data.P[2]);
        //if (data.P[3] != oldData.P[3])
            emit P_VelocityNorthChanged(data.P[3]);
        //if (data.P[4] != oldData.P[4])
            emit P_VelocityEastChanged(data.P[4]);
        //if (data.P[5] != oldData.P[5])
            emit P_VelocityDownChanged(data.P[5]);
        //if (data.P[6] != oldData.P[6])
            emit P_AttitudeQ1Changed(data.P[6]);
        //if (data.P[7] != oldData.P[7])
            emit P_AttitudeQ2Changed(data.P[7]);
        //if (data.P[8] != oldData.P[8])
            emit P_AttitudeQ3Changed(data.P[8]);
        //if (data.P[9] != oldData.P[9])
            emit P_AttitudeQ4Changed(data.P[9]);
        //if (data.P[10] != oldData.P[10])
            emit P_GyroDriftXChanged(data.P[10]);
        //if (data.P[11] != oldData.P[11])
            emit P_GyroDriftYChanged(data.P[11]);
        //if (data.P[12] != oldData.P[12])
            emit P_GyroDriftZChanged(data.P[12]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *EKFStateVariance::clone(quint32 instID)
{
    EKFStateVariance *obj = new EKFStateVariance();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *EKFStateVariance::dirtyClone()
{
    EKFStateVariance *obj = new EKFStateVariance();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
EKFStateVariance *EKFStateVariance::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<EKFStateVariance *>(objMngr->getObject(EKFStateVariance::OBJID, instID));
}

float EKFStateVariance::getP(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.P[index];
}
void EKFStateVariance::setP(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.P[index] != value;
   data.P[index] = value;
   mutex->unlock();
   if (changed) emit PChanged(index,value);
}

float EKFStateVariance::getP_PositionNorth() const
{
   QMutexLocker locker(mutex);
   return data.P[0];
}
void EKFStateVariance::setP_PositionNorth(float value)
{
   mutex->lock();
   bool changed = data.P[0] != value;
   data.P[0] = value;
   mutex->unlock();
   if (changed) emit P_PositionNorthChanged(value);
}

float EKFStateVariance::getP_PositionEast() const
{
   QMutexLocker locker(mutex);
   return data.P[1];
}
void EKFStateVariance::setP_PositionEast(float value)
{
   mutex->lock();
   bool changed = data.P[1] != value;
   data.P[1] = value;
   mutex->unlock();
   if (changed) emit P_PositionEastChanged(value);
}

float EKFStateVariance::getP_PositionDown() const
{
   QMutexLocker locker(mutex);
   return data.P[2];
}
void EKFStateVariance::setP_PositionDown(float value)
{
   mutex->lock();
   bool changed = data.P[2] != value;
   data.P[2] = value;
   mutex->unlock();
   if (changed) emit P_PositionDownChanged(value);
}

float EKFStateVariance::getP_VelocityNorth() const
{
   QMutexLocker locker(mutex);
   return data.P[3];
}
void EKFStateVariance::setP_VelocityNorth(float value)
{
   mutex->lock();
   bool changed = data.P[3] != value;
   data.P[3] = value;
   mutex->unlock();
   if (changed) emit P_VelocityNorthChanged(value);
}

float EKFStateVariance::getP_VelocityEast() const
{
   QMutexLocker locker(mutex);
   return data.P[4];
}
void EKFStateVariance::setP_VelocityEast(float value)
{
   mutex->lock();
   bool changed = data.P[4] != value;
   data.P[4] = value;
   mutex->unlock();
   if (changed) emit P_VelocityEastChanged(value);
}

float EKFStateVariance::getP_VelocityDown() const
{
   QMutexLocker locker(mutex);
   return data.P[5];
}
void EKFStateVariance::setP_VelocityDown(float value)
{
   mutex->lock();
   bool changed = data.P[5] != value;
   data.P[5] = value;
   mutex->unlock();
   if (changed) emit P_VelocityDownChanged(value);
}

float EKFStateVariance::getP_AttitudeQ1() const
{
   QMutexLocker locker(mutex);
   return data.P[6];
}
void EKFStateVariance::setP_AttitudeQ1(float value)
{
   mutex->lock();
   bool changed = data.P[6] != value;
   data.P[6] = value;
   mutex->unlock();
   if (changed) emit P_AttitudeQ1Changed(value);
}

float EKFStateVariance::getP_AttitudeQ2() const
{
   QMutexLocker locker(mutex);
   return data.P[7];
}
void EKFStateVariance::setP_AttitudeQ2(float value)
{
   mutex->lock();
   bool changed = data.P[7] != value;
   data.P[7] = value;
   mutex->unlock();
   if (changed) emit P_AttitudeQ2Changed(value);
}

float EKFStateVariance::getP_AttitudeQ3() const
{
   QMutexLocker locker(mutex);
   return data.P[8];
}
void EKFStateVariance::setP_AttitudeQ3(float value)
{
   mutex->lock();
   bool changed = data.P[8] != value;
   data.P[8] = value;
   mutex->unlock();
   if (changed) emit P_AttitudeQ3Changed(value);
}

float EKFStateVariance::getP_AttitudeQ4() const
{
   QMutexLocker locker(mutex);
   return data.P[9];
}
void EKFStateVariance::setP_AttitudeQ4(float value)
{
   mutex->lock();
   bool changed = data.P[9] != value;
   data.P[9] = value;
   mutex->unlock();
   if (changed) emit P_AttitudeQ4Changed(value);
}

float EKFStateVariance::getP_GyroDriftX() const
{
   QMutexLocker locker(mutex);
   return data.P[10];
}
void EKFStateVariance::setP_GyroDriftX(float value)
{
   mutex->lock();
   bool changed = data.P[10] != value;
   data.P[10] = value;
   mutex->unlock();
   if (changed) emit P_GyroDriftXChanged(value);
}

float EKFStateVariance::getP_GyroDriftY() const
{
   QMutexLocker locker(mutex);
   return data.P[11];
}
void EKFStateVariance::setP_GyroDriftY(float value)
{
   mutex->lock();
   bool changed = data.P[11] != value;
   data.P[11] = value;
   mutex->unlock();
   if (changed) emit P_GyroDriftYChanged(value);
}

float EKFStateVariance::getP_GyroDriftZ() const
{
   QMutexLocker locker(mutex);
   return data.P[12];
}
void EKFStateVariance::setP_GyroDriftZ(float value)
{
   mutex->lock();
   bool changed = data.P[12] != value;
   data.P[12] = value;
   mutex->unlock();
   if (changed) emit P_GyroDriftZChanged(value);
}


