/**
 ******************************************************************************
 *
 * @file       ekfconfiguration.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: ekfconfiguration.xml.
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

#include "ekfconfiguration.h"
#include "uavobjectfield.h"

const QString EKFConfiguration::NAME = QString("EKFConfiguration");
const QString EKFConfiguration::DESCRIPTION = QString("Extended Kalman Filter initialisation");
const QString EKFConfiguration::CATEGORY = QString("State");

/**
 * Constructor
 */
EKFConfiguration::EKFConfiguration(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
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
    QStringList QElemNames;
    QElemNames.append("GyroX");
    QElemNames.append("GyroY");
    QElemNames.append("GyroZ");
    QElemNames.append("AccelX");
    QElemNames.append("AccelY");
    QElemNames.append("AccelZ");
    QElemNames.append("GyroDriftX");
    QElemNames.append("GyroDriftY");
    QElemNames.append("GyroDriftZ");
    fields.append( new UAVObjectField(QString("Q"), tr(""), QString("1^2"), UAVObjectField::FLOAT32, QElemNames, QStringList(), QString("")));
    QStringList RElemNames;
    RElemNames.append("GPSPosNorth");
    RElemNames.append("GPSPosEast");
    RElemNames.append("GPSPosDown");
    RElemNames.append("GPSVelNorth");
    RElemNames.append("GPSVelEast");
    RElemNames.append("GPSVelDown");
    RElemNames.append("MagX");
    RElemNames.append("MagY");
    RElemNames.append("MagZ");
    RElemNames.append("BaroZ");
    fields.append( new UAVObjectField(QString("R"), tr(""), QString("1^2"), UAVObjectField::FLOAT32, RElemNames, QStringList(), QString("")));
    QStringList FakeRElemNames;
    FakeRElemNames.append("FakeGPSPosIndoor");
    FakeRElemNames.append("FakeGPSVelIndoor");
    FakeRElemNames.append("FakeGPSVelAirspeed");
    fields.append( new UAVObjectField(QString("FakeR"), tr(""), QString("1^2"), UAVObjectField::FLOAT32, FakeRElemNames, QStringList(), QString("")));

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
UAVObject::Metadata EKFConfiguration::getDefaultMetadata()
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
void EKFConfiguration::setDefaultFieldValues()
{
    data.P[0] = 10;
    data.P[1] = 10;
    data.P[2] = 10;
    data.P[3] = 1;
    data.P[4] = 1;
    data.P[5] = 1;
    data.P[6] = 0.007;
    data.P[7] = 0.007;
    data.P[8] = 0.007;
    data.P[9] = 0.007;
    data.P[10] = 1e-06;
    data.P[11] = 1e-06;
    data.P[12] = 1e-06;
    data.Q[0] = 0.01;
    data.Q[1] = 0.01;
    data.Q[2] = 0.01;
    data.Q[3] = 0.01;
    data.Q[4] = 0.01;
    data.Q[5] = 0.01;
    data.Q[6] = 1e-06;
    data.Q[7] = 1e-06;
    data.Q[8] = 1e-06;
    data.R[0] = 1;
    data.R[1] = 1;
    data.R[2] = 1e+06;
    data.R[3] = 0.001;
    data.R[4] = 0.001;
    data.R[5] = 0.001;
    data.R[6] = 10;
    data.R[7] = 10;
    data.R[8] = 10;
    data.R[9] = 0.01;
    data.FakeR[0] = 10;
    data.FakeR[1] = 1;
    data.FakeR[2] = 1000;

}

/**
 * Get the object data fields
 */
EKFConfiguration::DataFields EKFConfiguration::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void EKFConfiguration::setData(const DataFields& data)
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

void EKFConfiguration::emitNotifications()
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
        //if (data.Q[0] != oldData.Q[0])
            emit Q_GyroXChanged(data.Q[0]);
        //if (data.Q[1] != oldData.Q[1])
            emit Q_GyroYChanged(data.Q[1]);
        //if (data.Q[2] != oldData.Q[2])
            emit Q_GyroZChanged(data.Q[2]);
        //if (data.Q[3] != oldData.Q[3])
            emit Q_AccelXChanged(data.Q[3]);
        //if (data.Q[4] != oldData.Q[4])
            emit Q_AccelYChanged(data.Q[4]);
        //if (data.Q[5] != oldData.Q[5])
            emit Q_AccelZChanged(data.Q[5]);
        //if (data.Q[6] != oldData.Q[6])
            emit Q_GyroDriftXChanged(data.Q[6]);
        //if (data.Q[7] != oldData.Q[7])
            emit Q_GyroDriftYChanged(data.Q[7]);
        //if (data.Q[8] != oldData.Q[8])
            emit Q_GyroDriftZChanged(data.Q[8]);
        //if (data.R[0] != oldData.R[0])
            emit R_GPSPosNorthChanged(data.R[0]);
        //if (data.R[1] != oldData.R[1])
            emit R_GPSPosEastChanged(data.R[1]);
        //if (data.R[2] != oldData.R[2])
            emit R_GPSPosDownChanged(data.R[2]);
        //if (data.R[3] != oldData.R[3])
            emit R_GPSVelNorthChanged(data.R[3]);
        //if (data.R[4] != oldData.R[4])
            emit R_GPSVelEastChanged(data.R[4]);
        //if (data.R[5] != oldData.R[5])
            emit R_GPSVelDownChanged(data.R[5]);
        //if (data.R[6] != oldData.R[6])
            emit R_MagXChanged(data.R[6]);
        //if (data.R[7] != oldData.R[7])
            emit R_MagYChanged(data.R[7]);
        //if (data.R[8] != oldData.R[8])
            emit R_MagZChanged(data.R[8]);
        //if (data.R[9] != oldData.R[9])
            emit R_BaroZChanged(data.R[9]);
        //if (data.FakeR[0] != oldData.FakeR[0])
            emit FakeR_FakeGPSPosIndoorChanged(data.FakeR[0]);
        //if (data.FakeR[1] != oldData.FakeR[1])
            emit FakeR_FakeGPSVelIndoorChanged(data.FakeR[1]);
        //if (data.FakeR[2] != oldData.FakeR[2])
            emit FakeR_FakeGPSVelAirspeedChanged(data.FakeR[2]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *EKFConfiguration::clone(quint32 instID)
{
    EKFConfiguration *obj = new EKFConfiguration();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *EKFConfiguration::dirtyClone()
{
    EKFConfiguration *obj = new EKFConfiguration();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
EKFConfiguration *EKFConfiguration::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<EKFConfiguration *>(objMngr->getObject(EKFConfiguration::OBJID, instID));
}

float EKFConfiguration::getP(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.P[index];
}
void EKFConfiguration::setP(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.P[index] != value;
   data.P[index] = value;
   mutex->unlock();
   if (changed) emit PChanged(index,value);
}

float EKFConfiguration::getP_PositionNorth() const
{
   QMutexLocker locker(mutex);
   return data.P[0];
}
void EKFConfiguration::setP_PositionNorth(float value)
{
   mutex->lock();
   bool changed = data.P[0] != value;
   data.P[0] = value;
   mutex->unlock();
   if (changed) emit P_PositionNorthChanged(value);
}

float EKFConfiguration::getP_PositionEast() const
{
   QMutexLocker locker(mutex);
   return data.P[1];
}
void EKFConfiguration::setP_PositionEast(float value)
{
   mutex->lock();
   bool changed = data.P[1] != value;
   data.P[1] = value;
   mutex->unlock();
   if (changed) emit P_PositionEastChanged(value);
}

float EKFConfiguration::getP_PositionDown() const
{
   QMutexLocker locker(mutex);
   return data.P[2];
}
void EKFConfiguration::setP_PositionDown(float value)
{
   mutex->lock();
   bool changed = data.P[2] != value;
   data.P[2] = value;
   mutex->unlock();
   if (changed) emit P_PositionDownChanged(value);
}

float EKFConfiguration::getP_VelocityNorth() const
{
   QMutexLocker locker(mutex);
   return data.P[3];
}
void EKFConfiguration::setP_VelocityNorth(float value)
{
   mutex->lock();
   bool changed = data.P[3] != value;
   data.P[3] = value;
   mutex->unlock();
   if (changed) emit P_VelocityNorthChanged(value);
}

float EKFConfiguration::getP_VelocityEast() const
{
   QMutexLocker locker(mutex);
   return data.P[4];
}
void EKFConfiguration::setP_VelocityEast(float value)
{
   mutex->lock();
   bool changed = data.P[4] != value;
   data.P[4] = value;
   mutex->unlock();
   if (changed) emit P_VelocityEastChanged(value);
}

float EKFConfiguration::getP_VelocityDown() const
{
   QMutexLocker locker(mutex);
   return data.P[5];
}
void EKFConfiguration::setP_VelocityDown(float value)
{
   mutex->lock();
   bool changed = data.P[5] != value;
   data.P[5] = value;
   mutex->unlock();
   if (changed) emit P_VelocityDownChanged(value);
}

float EKFConfiguration::getP_AttitudeQ1() const
{
   QMutexLocker locker(mutex);
   return data.P[6];
}
void EKFConfiguration::setP_AttitudeQ1(float value)
{
   mutex->lock();
   bool changed = data.P[6] != value;
   data.P[6] = value;
   mutex->unlock();
   if (changed) emit P_AttitudeQ1Changed(value);
}

float EKFConfiguration::getP_AttitudeQ2() const
{
   QMutexLocker locker(mutex);
   return data.P[7];
}
void EKFConfiguration::setP_AttitudeQ2(float value)
{
   mutex->lock();
   bool changed = data.P[7] != value;
   data.P[7] = value;
   mutex->unlock();
   if (changed) emit P_AttitudeQ2Changed(value);
}

float EKFConfiguration::getP_AttitudeQ3() const
{
   QMutexLocker locker(mutex);
   return data.P[8];
}
void EKFConfiguration::setP_AttitudeQ3(float value)
{
   mutex->lock();
   bool changed = data.P[8] != value;
   data.P[8] = value;
   mutex->unlock();
   if (changed) emit P_AttitudeQ3Changed(value);
}

float EKFConfiguration::getP_AttitudeQ4() const
{
   QMutexLocker locker(mutex);
   return data.P[9];
}
void EKFConfiguration::setP_AttitudeQ4(float value)
{
   mutex->lock();
   bool changed = data.P[9] != value;
   data.P[9] = value;
   mutex->unlock();
   if (changed) emit P_AttitudeQ4Changed(value);
}

float EKFConfiguration::getP_GyroDriftX() const
{
   QMutexLocker locker(mutex);
   return data.P[10];
}
void EKFConfiguration::setP_GyroDriftX(float value)
{
   mutex->lock();
   bool changed = data.P[10] != value;
   data.P[10] = value;
   mutex->unlock();
   if (changed) emit P_GyroDriftXChanged(value);
}

float EKFConfiguration::getP_GyroDriftY() const
{
   QMutexLocker locker(mutex);
   return data.P[11];
}
void EKFConfiguration::setP_GyroDriftY(float value)
{
   mutex->lock();
   bool changed = data.P[11] != value;
   data.P[11] = value;
   mutex->unlock();
   if (changed) emit P_GyroDriftYChanged(value);
}

float EKFConfiguration::getP_GyroDriftZ() const
{
   QMutexLocker locker(mutex);
   return data.P[12];
}
void EKFConfiguration::setP_GyroDriftZ(float value)
{
   mutex->lock();
   bool changed = data.P[12] != value;
   data.P[12] = value;
   mutex->unlock();
   if (changed) emit P_GyroDriftZChanged(value);
}

float EKFConfiguration::getQ(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Q[index];
}
void EKFConfiguration::setQ(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.Q[index] != value;
   data.Q[index] = value;
   mutex->unlock();
   if (changed) emit QChanged(index,value);
}

float EKFConfiguration::getQ_GyroX() const
{
   QMutexLocker locker(mutex);
   return data.Q[0];
}
void EKFConfiguration::setQ_GyroX(float value)
{
   mutex->lock();
   bool changed = data.Q[0] != value;
   data.Q[0] = value;
   mutex->unlock();
   if (changed) emit Q_GyroXChanged(value);
}

float EKFConfiguration::getQ_GyroY() const
{
   QMutexLocker locker(mutex);
   return data.Q[1];
}
void EKFConfiguration::setQ_GyroY(float value)
{
   mutex->lock();
   bool changed = data.Q[1] != value;
   data.Q[1] = value;
   mutex->unlock();
   if (changed) emit Q_GyroYChanged(value);
}

float EKFConfiguration::getQ_GyroZ() const
{
   QMutexLocker locker(mutex);
   return data.Q[2];
}
void EKFConfiguration::setQ_GyroZ(float value)
{
   mutex->lock();
   bool changed = data.Q[2] != value;
   data.Q[2] = value;
   mutex->unlock();
   if (changed) emit Q_GyroZChanged(value);
}

float EKFConfiguration::getQ_AccelX() const
{
   QMutexLocker locker(mutex);
   return data.Q[3];
}
void EKFConfiguration::setQ_AccelX(float value)
{
   mutex->lock();
   bool changed = data.Q[3] != value;
   data.Q[3] = value;
   mutex->unlock();
   if (changed) emit Q_AccelXChanged(value);
}

float EKFConfiguration::getQ_AccelY() const
{
   QMutexLocker locker(mutex);
   return data.Q[4];
}
void EKFConfiguration::setQ_AccelY(float value)
{
   mutex->lock();
   bool changed = data.Q[4] != value;
   data.Q[4] = value;
   mutex->unlock();
   if (changed) emit Q_AccelYChanged(value);
}

float EKFConfiguration::getQ_AccelZ() const
{
   QMutexLocker locker(mutex);
   return data.Q[5];
}
void EKFConfiguration::setQ_AccelZ(float value)
{
   mutex->lock();
   bool changed = data.Q[5] != value;
   data.Q[5] = value;
   mutex->unlock();
   if (changed) emit Q_AccelZChanged(value);
}

float EKFConfiguration::getQ_GyroDriftX() const
{
   QMutexLocker locker(mutex);
   return data.Q[6];
}
void EKFConfiguration::setQ_GyroDriftX(float value)
{
   mutex->lock();
   bool changed = data.Q[6] != value;
   data.Q[6] = value;
   mutex->unlock();
   if (changed) emit Q_GyroDriftXChanged(value);
}

float EKFConfiguration::getQ_GyroDriftY() const
{
   QMutexLocker locker(mutex);
   return data.Q[7];
}
void EKFConfiguration::setQ_GyroDriftY(float value)
{
   mutex->lock();
   bool changed = data.Q[7] != value;
   data.Q[7] = value;
   mutex->unlock();
   if (changed) emit Q_GyroDriftYChanged(value);
}

float EKFConfiguration::getQ_GyroDriftZ() const
{
   QMutexLocker locker(mutex);
   return data.Q[8];
}
void EKFConfiguration::setQ_GyroDriftZ(float value)
{
   mutex->lock();
   bool changed = data.Q[8] != value;
   data.Q[8] = value;
   mutex->unlock();
   if (changed) emit Q_GyroDriftZChanged(value);
}

float EKFConfiguration::getR(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.R[index];
}
void EKFConfiguration::setR(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.R[index] != value;
   data.R[index] = value;
   mutex->unlock();
   if (changed) emit RChanged(index,value);
}

float EKFConfiguration::getR_GPSPosNorth() const
{
   QMutexLocker locker(mutex);
   return data.R[0];
}
void EKFConfiguration::setR_GPSPosNorth(float value)
{
   mutex->lock();
   bool changed = data.R[0] != value;
   data.R[0] = value;
   mutex->unlock();
   if (changed) emit R_GPSPosNorthChanged(value);
}

float EKFConfiguration::getR_GPSPosEast() const
{
   QMutexLocker locker(mutex);
   return data.R[1];
}
void EKFConfiguration::setR_GPSPosEast(float value)
{
   mutex->lock();
   bool changed = data.R[1] != value;
   data.R[1] = value;
   mutex->unlock();
   if (changed) emit R_GPSPosEastChanged(value);
}

float EKFConfiguration::getR_GPSPosDown() const
{
   QMutexLocker locker(mutex);
   return data.R[2];
}
void EKFConfiguration::setR_GPSPosDown(float value)
{
   mutex->lock();
   bool changed = data.R[2] != value;
   data.R[2] = value;
   mutex->unlock();
   if (changed) emit R_GPSPosDownChanged(value);
}

float EKFConfiguration::getR_GPSVelNorth() const
{
   QMutexLocker locker(mutex);
   return data.R[3];
}
void EKFConfiguration::setR_GPSVelNorth(float value)
{
   mutex->lock();
   bool changed = data.R[3] != value;
   data.R[3] = value;
   mutex->unlock();
   if (changed) emit R_GPSVelNorthChanged(value);
}

float EKFConfiguration::getR_GPSVelEast() const
{
   QMutexLocker locker(mutex);
   return data.R[4];
}
void EKFConfiguration::setR_GPSVelEast(float value)
{
   mutex->lock();
   bool changed = data.R[4] != value;
   data.R[4] = value;
   mutex->unlock();
   if (changed) emit R_GPSVelEastChanged(value);
}

float EKFConfiguration::getR_GPSVelDown() const
{
   QMutexLocker locker(mutex);
   return data.R[5];
}
void EKFConfiguration::setR_GPSVelDown(float value)
{
   mutex->lock();
   bool changed = data.R[5] != value;
   data.R[5] = value;
   mutex->unlock();
   if (changed) emit R_GPSVelDownChanged(value);
}

float EKFConfiguration::getR_MagX() const
{
   QMutexLocker locker(mutex);
   return data.R[6];
}
void EKFConfiguration::setR_MagX(float value)
{
   mutex->lock();
   bool changed = data.R[6] != value;
   data.R[6] = value;
   mutex->unlock();
   if (changed) emit R_MagXChanged(value);
}

float EKFConfiguration::getR_MagY() const
{
   QMutexLocker locker(mutex);
   return data.R[7];
}
void EKFConfiguration::setR_MagY(float value)
{
   mutex->lock();
   bool changed = data.R[7] != value;
   data.R[7] = value;
   mutex->unlock();
   if (changed) emit R_MagYChanged(value);
}

float EKFConfiguration::getR_MagZ() const
{
   QMutexLocker locker(mutex);
   return data.R[8];
}
void EKFConfiguration::setR_MagZ(float value)
{
   mutex->lock();
   bool changed = data.R[8] != value;
   data.R[8] = value;
   mutex->unlock();
   if (changed) emit R_MagZChanged(value);
}

float EKFConfiguration::getR_BaroZ() const
{
   QMutexLocker locker(mutex);
   return data.R[9];
}
void EKFConfiguration::setR_BaroZ(float value)
{
   mutex->lock();
   bool changed = data.R[9] != value;
   data.R[9] = value;
   mutex->unlock();
   if (changed) emit R_BaroZChanged(value);
}

float EKFConfiguration::getFakeR(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.FakeR[index];
}
void EKFConfiguration::setFakeR(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.FakeR[index] != value;
   data.FakeR[index] = value;
   mutex->unlock();
   if (changed) emit FakeRChanged(index,value);
}

float EKFConfiguration::getFakeR_FakeGPSPosIndoor() const
{
   QMutexLocker locker(mutex);
   return data.FakeR[0];
}
void EKFConfiguration::setFakeR_FakeGPSPosIndoor(float value)
{
   mutex->lock();
   bool changed = data.FakeR[0] != value;
   data.FakeR[0] = value;
   mutex->unlock();
   if (changed) emit FakeR_FakeGPSPosIndoorChanged(value);
}

float EKFConfiguration::getFakeR_FakeGPSVelIndoor() const
{
   QMutexLocker locker(mutex);
   return data.FakeR[1];
}
void EKFConfiguration::setFakeR_FakeGPSVelIndoor(float value)
{
   mutex->lock();
   bool changed = data.FakeR[1] != value;
   data.FakeR[1] = value;
   mutex->unlock();
   if (changed) emit FakeR_FakeGPSVelIndoorChanged(value);
}

float EKFConfiguration::getFakeR_FakeGPSVelAirspeed() const
{
   QMutexLocker locker(mutex);
   return data.FakeR[2];
}
void EKFConfiguration::setFakeR_FakeGPSVelAirspeed(float value)
{
   mutex->lock();
   bool changed = data.FakeR[2] != value;
   data.FakeR[2] = value;
   mutex->unlock();
   if (changed) emit FakeR_FakeGPSVelAirspeedChanged(value);
}


