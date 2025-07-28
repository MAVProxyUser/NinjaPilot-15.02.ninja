/**
 ******************************************************************************
 *
 * @file       accelgyrosettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: accelgyrosettings.xml.
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

#include "accelgyrosettings.h"
#include "uavobjectfield.h"

const QString AccelGyroSettings::NAME = QString("AccelGyroSettings");
const QString AccelGyroSettings::DESCRIPTION = QString("Settings for Accelerometer and Gyroscope calibration ");
const QString AccelGyroSettings::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
AccelGyroSettings::AccelGyroSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList accel_biasElemNames;
    accel_biasElemNames.append("X");
    accel_biasElemNames.append("Y");
    accel_biasElemNames.append("Z");
    fields.append( new UAVObjectField(QString("accel_bias"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, accel_biasElemNames, QStringList(), QString("")));
    QStringList accel_scaleElemNames;
    accel_scaleElemNames.append("X");
    accel_scaleElemNames.append("Y");
    accel_scaleElemNames.append("Z");
    fields.append( new UAVObjectField(QString("accel_scale"), tr(""), QString("gain"), UAVObjectField::FLOAT32, accel_scaleElemNames, QStringList(), QString("")));
    QStringList accel_temp_coeffElemNames;
    accel_temp_coeffElemNames.append("X");
    accel_temp_coeffElemNames.append("Y");
    accel_temp_coeffElemNames.append("Z");
    fields.append( new UAVObjectField(QString("accel_temp_coeff"), tr(""), QString(""), UAVObjectField::FLOAT32, accel_temp_coeffElemNames, QStringList(), QString("")));
    QStringList gyro_biasElemNames;
    gyro_biasElemNames.append("X");
    gyro_biasElemNames.append("Y");
    gyro_biasElemNames.append("Z");
    fields.append( new UAVObjectField(QString("gyro_bias"), tr(""), QString("deg/s"), UAVObjectField::FLOAT32, gyro_biasElemNames, QStringList(), QString("")));
    QStringList gyro_scaleElemNames;
    gyro_scaleElemNames.append("X");
    gyro_scaleElemNames.append("Y");
    gyro_scaleElemNames.append("Z");
    fields.append( new UAVObjectField(QString("gyro_scale"), tr(""), QString("gain"), UAVObjectField::FLOAT32, gyro_scaleElemNames, QStringList(), QString("")));
    QStringList gyro_temp_coeffElemNames;
    gyro_temp_coeffElemNames.append("X");
    gyro_temp_coeffElemNames.append("X2");
    gyro_temp_coeffElemNames.append("Y");
    gyro_temp_coeffElemNames.append("Y2");
    gyro_temp_coeffElemNames.append("Z");
    gyro_temp_coeffElemNames.append("Z2");
    fields.append( new UAVObjectField(QString("gyro_temp_coeff"), tr(""), QString(""), UAVObjectField::FLOAT32, gyro_temp_coeffElemNames, QStringList(), QString("")));
    QStringList temp_calibrated_extentElemNames;
    temp_calibrated_extentElemNames.append("min");
    temp_calibrated_extentElemNames.append("max");
    fields.append( new UAVObjectField(QString("temp_calibrated_extent"), tr(""), QString("deg C"), UAVObjectField::FLOAT32, temp_calibrated_extentElemNames, QStringList(), QString("")));

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
UAVObject::Metadata AccelGyroSettings::getDefaultMetadata()
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
void AccelGyroSettings::setDefaultFieldValues()
{
    data.accel_bias[0] = 0;
    data.accel_bias[1] = 0;
    data.accel_bias[2] = 0;
    data.accel_scale[0] = 1;
    data.accel_scale[1] = 1;
    data.accel_scale[2] = 1;
    data.accel_temp_coeff[0] = 0;
    data.accel_temp_coeff[1] = 0;
    data.accel_temp_coeff[2] = 0;
    data.gyro_bias[0] = 0;
    data.gyro_bias[1] = 0;
    data.gyro_bias[2] = 0;
    data.gyro_scale[0] = 1;
    data.gyro_scale[1] = 1;
    data.gyro_scale[2] = 1;
    data.gyro_temp_coeff[0] = 0;
    data.gyro_temp_coeff[1] = 0;
    data.gyro_temp_coeff[2] = 0;
    data.gyro_temp_coeff[3] = 0;
    data.gyro_temp_coeff[4] = 0;
    data.gyro_temp_coeff[5] = 0;
    data.temp_calibrated_extent[0] = 0;
    data.temp_calibrated_extent[1] = 0;

}

/**
 * Get the object data fields
 */
AccelGyroSettings::DataFields AccelGyroSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void AccelGyroSettings::setData(const DataFields& data)
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

void AccelGyroSettings::emitNotifications()
{
            //if (data.accel_bias[0] != oldData.accel_bias[0])
            emit accel_bias_XChanged(data.accel_bias[0]);
        //if (data.accel_bias[1] != oldData.accel_bias[1])
            emit accel_bias_YChanged(data.accel_bias[1]);
        //if (data.accel_bias[2] != oldData.accel_bias[2])
            emit accel_bias_ZChanged(data.accel_bias[2]);
        //if (data.accel_scale[0] != oldData.accel_scale[0])
            emit accel_scale_XChanged(data.accel_scale[0]);
        //if (data.accel_scale[1] != oldData.accel_scale[1])
            emit accel_scale_YChanged(data.accel_scale[1]);
        //if (data.accel_scale[2] != oldData.accel_scale[2])
            emit accel_scale_ZChanged(data.accel_scale[2]);
        //if (data.accel_temp_coeff[0] != oldData.accel_temp_coeff[0])
            emit accel_temp_coeff_XChanged(data.accel_temp_coeff[0]);
        //if (data.accel_temp_coeff[1] != oldData.accel_temp_coeff[1])
            emit accel_temp_coeff_YChanged(data.accel_temp_coeff[1]);
        //if (data.accel_temp_coeff[2] != oldData.accel_temp_coeff[2])
            emit accel_temp_coeff_ZChanged(data.accel_temp_coeff[2]);
        //if (data.gyro_bias[0] != oldData.gyro_bias[0])
            emit gyro_bias_XChanged(data.gyro_bias[0]);
        //if (data.gyro_bias[1] != oldData.gyro_bias[1])
            emit gyro_bias_YChanged(data.gyro_bias[1]);
        //if (data.gyro_bias[2] != oldData.gyro_bias[2])
            emit gyro_bias_ZChanged(data.gyro_bias[2]);
        //if (data.gyro_scale[0] != oldData.gyro_scale[0])
            emit gyro_scale_XChanged(data.gyro_scale[0]);
        //if (data.gyro_scale[1] != oldData.gyro_scale[1])
            emit gyro_scale_YChanged(data.gyro_scale[1]);
        //if (data.gyro_scale[2] != oldData.gyro_scale[2])
            emit gyro_scale_ZChanged(data.gyro_scale[2]);
        //if (data.gyro_temp_coeff[0] != oldData.gyro_temp_coeff[0])
            emit gyro_temp_coeff_XChanged(data.gyro_temp_coeff[0]);
        //if (data.gyro_temp_coeff[1] != oldData.gyro_temp_coeff[1])
            emit gyro_temp_coeff_X2Changed(data.gyro_temp_coeff[1]);
        //if (data.gyro_temp_coeff[2] != oldData.gyro_temp_coeff[2])
            emit gyro_temp_coeff_YChanged(data.gyro_temp_coeff[2]);
        //if (data.gyro_temp_coeff[3] != oldData.gyro_temp_coeff[3])
            emit gyro_temp_coeff_Y2Changed(data.gyro_temp_coeff[3]);
        //if (data.gyro_temp_coeff[4] != oldData.gyro_temp_coeff[4])
            emit gyro_temp_coeff_ZChanged(data.gyro_temp_coeff[4]);
        //if (data.gyro_temp_coeff[5] != oldData.gyro_temp_coeff[5])
            emit gyro_temp_coeff_Z2Changed(data.gyro_temp_coeff[5]);
        //if (data.temp_calibrated_extent[0] != oldData.temp_calibrated_extent[0])
            emit temp_calibrated_extent_minChanged(data.temp_calibrated_extent[0]);
        //if (data.temp_calibrated_extent[1] != oldData.temp_calibrated_extent[1])
            emit temp_calibrated_extent_maxChanged(data.temp_calibrated_extent[1]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *AccelGyroSettings::clone(quint32 instID)
{
    AccelGyroSettings *obj = new AccelGyroSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *AccelGyroSettings::dirtyClone()
{
    AccelGyroSettings *obj = new AccelGyroSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
AccelGyroSettings *AccelGyroSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<AccelGyroSettings *>(objMngr->getObject(AccelGyroSettings::OBJID, instID));
}

float AccelGyroSettings::getaccel_bias(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.accel_bias[index];
}
void AccelGyroSettings::setaccel_bias(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.accel_bias[index] != value;
   data.accel_bias[index] = value;
   mutex->unlock();
   if (changed) emit accel_biasChanged(index,value);
}

float AccelGyroSettings::getaccel_bias_X() const
{
   QMutexLocker locker(mutex);
   return data.accel_bias[0];
}
void AccelGyroSettings::setaccel_bias_X(float value)
{
   mutex->lock();
   bool changed = data.accel_bias[0] != value;
   data.accel_bias[0] = value;
   mutex->unlock();
   if (changed) emit accel_bias_XChanged(value);
}

float AccelGyroSettings::getaccel_bias_Y() const
{
   QMutexLocker locker(mutex);
   return data.accel_bias[1];
}
void AccelGyroSettings::setaccel_bias_Y(float value)
{
   mutex->lock();
   bool changed = data.accel_bias[1] != value;
   data.accel_bias[1] = value;
   mutex->unlock();
   if (changed) emit accel_bias_YChanged(value);
}

float AccelGyroSettings::getaccel_bias_Z() const
{
   QMutexLocker locker(mutex);
   return data.accel_bias[2];
}
void AccelGyroSettings::setaccel_bias_Z(float value)
{
   mutex->lock();
   bool changed = data.accel_bias[2] != value;
   data.accel_bias[2] = value;
   mutex->unlock();
   if (changed) emit accel_bias_ZChanged(value);
}

float AccelGyroSettings::getaccel_scale(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.accel_scale[index];
}
void AccelGyroSettings::setaccel_scale(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.accel_scale[index] != value;
   data.accel_scale[index] = value;
   mutex->unlock();
   if (changed) emit accel_scaleChanged(index,value);
}

float AccelGyroSettings::getaccel_scale_X() const
{
   QMutexLocker locker(mutex);
   return data.accel_scale[0];
}
void AccelGyroSettings::setaccel_scale_X(float value)
{
   mutex->lock();
   bool changed = data.accel_scale[0] != value;
   data.accel_scale[0] = value;
   mutex->unlock();
   if (changed) emit accel_scale_XChanged(value);
}

float AccelGyroSettings::getaccel_scale_Y() const
{
   QMutexLocker locker(mutex);
   return data.accel_scale[1];
}
void AccelGyroSettings::setaccel_scale_Y(float value)
{
   mutex->lock();
   bool changed = data.accel_scale[1] != value;
   data.accel_scale[1] = value;
   mutex->unlock();
   if (changed) emit accel_scale_YChanged(value);
}

float AccelGyroSettings::getaccel_scale_Z() const
{
   QMutexLocker locker(mutex);
   return data.accel_scale[2];
}
void AccelGyroSettings::setaccel_scale_Z(float value)
{
   mutex->lock();
   bool changed = data.accel_scale[2] != value;
   data.accel_scale[2] = value;
   mutex->unlock();
   if (changed) emit accel_scale_ZChanged(value);
}

float AccelGyroSettings::getaccel_temp_coeff(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.accel_temp_coeff[index];
}
void AccelGyroSettings::setaccel_temp_coeff(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.accel_temp_coeff[index] != value;
   data.accel_temp_coeff[index] = value;
   mutex->unlock();
   if (changed) emit accel_temp_coeffChanged(index,value);
}

float AccelGyroSettings::getaccel_temp_coeff_X() const
{
   QMutexLocker locker(mutex);
   return data.accel_temp_coeff[0];
}
void AccelGyroSettings::setaccel_temp_coeff_X(float value)
{
   mutex->lock();
   bool changed = data.accel_temp_coeff[0] != value;
   data.accel_temp_coeff[0] = value;
   mutex->unlock();
   if (changed) emit accel_temp_coeff_XChanged(value);
}

float AccelGyroSettings::getaccel_temp_coeff_Y() const
{
   QMutexLocker locker(mutex);
   return data.accel_temp_coeff[1];
}
void AccelGyroSettings::setaccel_temp_coeff_Y(float value)
{
   mutex->lock();
   bool changed = data.accel_temp_coeff[1] != value;
   data.accel_temp_coeff[1] = value;
   mutex->unlock();
   if (changed) emit accel_temp_coeff_YChanged(value);
}

float AccelGyroSettings::getaccel_temp_coeff_Z() const
{
   QMutexLocker locker(mutex);
   return data.accel_temp_coeff[2];
}
void AccelGyroSettings::setaccel_temp_coeff_Z(float value)
{
   mutex->lock();
   bool changed = data.accel_temp_coeff[2] != value;
   data.accel_temp_coeff[2] = value;
   mutex->unlock();
   if (changed) emit accel_temp_coeff_ZChanged(value);
}

float AccelGyroSettings::getgyro_bias(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.gyro_bias[index];
}
void AccelGyroSettings::setgyro_bias(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.gyro_bias[index] != value;
   data.gyro_bias[index] = value;
   mutex->unlock();
   if (changed) emit gyro_biasChanged(index,value);
}

float AccelGyroSettings::getgyro_bias_X() const
{
   QMutexLocker locker(mutex);
   return data.gyro_bias[0];
}
void AccelGyroSettings::setgyro_bias_X(float value)
{
   mutex->lock();
   bool changed = data.gyro_bias[0] != value;
   data.gyro_bias[0] = value;
   mutex->unlock();
   if (changed) emit gyro_bias_XChanged(value);
}

float AccelGyroSettings::getgyro_bias_Y() const
{
   QMutexLocker locker(mutex);
   return data.gyro_bias[1];
}
void AccelGyroSettings::setgyro_bias_Y(float value)
{
   mutex->lock();
   bool changed = data.gyro_bias[1] != value;
   data.gyro_bias[1] = value;
   mutex->unlock();
   if (changed) emit gyro_bias_YChanged(value);
}

float AccelGyroSettings::getgyro_bias_Z() const
{
   QMutexLocker locker(mutex);
   return data.gyro_bias[2];
}
void AccelGyroSettings::setgyro_bias_Z(float value)
{
   mutex->lock();
   bool changed = data.gyro_bias[2] != value;
   data.gyro_bias[2] = value;
   mutex->unlock();
   if (changed) emit gyro_bias_ZChanged(value);
}

float AccelGyroSettings::getgyro_scale(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.gyro_scale[index];
}
void AccelGyroSettings::setgyro_scale(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.gyro_scale[index] != value;
   data.gyro_scale[index] = value;
   mutex->unlock();
   if (changed) emit gyro_scaleChanged(index,value);
}

float AccelGyroSettings::getgyro_scale_X() const
{
   QMutexLocker locker(mutex);
   return data.gyro_scale[0];
}
void AccelGyroSettings::setgyro_scale_X(float value)
{
   mutex->lock();
   bool changed = data.gyro_scale[0] != value;
   data.gyro_scale[0] = value;
   mutex->unlock();
   if (changed) emit gyro_scale_XChanged(value);
}

float AccelGyroSettings::getgyro_scale_Y() const
{
   QMutexLocker locker(mutex);
   return data.gyro_scale[1];
}
void AccelGyroSettings::setgyro_scale_Y(float value)
{
   mutex->lock();
   bool changed = data.gyro_scale[1] != value;
   data.gyro_scale[1] = value;
   mutex->unlock();
   if (changed) emit gyro_scale_YChanged(value);
}

float AccelGyroSettings::getgyro_scale_Z() const
{
   QMutexLocker locker(mutex);
   return data.gyro_scale[2];
}
void AccelGyroSettings::setgyro_scale_Z(float value)
{
   mutex->lock();
   bool changed = data.gyro_scale[2] != value;
   data.gyro_scale[2] = value;
   mutex->unlock();
   if (changed) emit gyro_scale_ZChanged(value);
}

float AccelGyroSettings::getgyro_temp_coeff(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.gyro_temp_coeff[index];
}
void AccelGyroSettings::setgyro_temp_coeff(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.gyro_temp_coeff[index] != value;
   data.gyro_temp_coeff[index] = value;
   mutex->unlock();
   if (changed) emit gyro_temp_coeffChanged(index,value);
}

float AccelGyroSettings::getgyro_temp_coeff_X() const
{
   QMutexLocker locker(mutex);
   return data.gyro_temp_coeff[0];
}
void AccelGyroSettings::setgyro_temp_coeff_X(float value)
{
   mutex->lock();
   bool changed = data.gyro_temp_coeff[0] != value;
   data.gyro_temp_coeff[0] = value;
   mutex->unlock();
   if (changed) emit gyro_temp_coeff_XChanged(value);
}

float AccelGyroSettings::getgyro_temp_coeff_X2() const
{
   QMutexLocker locker(mutex);
   return data.gyro_temp_coeff[1];
}
void AccelGyroSettings::setgyro_temp_coeff_X2(float value)
{
   mutex->lock();
   bool changed = data.gyro_temp_coeff[1] != value;
   data.gyro_temp_coeff[1] = value;
   mutex->unlock();
   if (changed) emit gyro_temp_coeff_X2Changed(value);
}

float AccelGyroSettings::getgyro_temp_coeff_Y() const
{
   QMutexLocker locker(mutex);
   return data.gyro_temp_coeff[2];
}
void AccelGyroSettings::setgyro_temp_coeff_Y(float value)
{
   mutex->lock();
   bool changed = data.gyro_temp_coeff[2] != value;
   data.gyro_temp_coeff[2] = value;
   mutex->unlock();
   if (changed) emit gyro_temp_coeff_YChanged(value);
}

float AccelGyroSettings::getgyro_temp_coeff_Y2() const
{
   QMutexLocker locker(mutex);
   return data.gyro_temp_coeff[3];
}
void AccelGyroSettings::setgyro_temp_coeff_Y2(float value)
{
   mutex->lock();
   bool changed = data.gyro_temp_coeff[3] != value;
   data.gyro_temp_coeff[3] = value;
   mutex->unlock();
   if (changed) emit gyro_temp_coeff_Y2Changed(value);
}

float AccelGyroSettings::getgyro_temp_coeff_Z() const
{
   QMutexLocker locker(mutex);
   return data.gyro_temp_coeff[4];
}
void AccelGyroSettings::setgyro_temp_coeff_Z(float value)
{
   mutex->lock();
   bool changed = data.gyro_temp_coeff[4] != value;
   data.gyro_temp_coeff[4] = value;
   mutex->unlock();
   if (changed) emit gyro_temp_coeff_ZChanged(value);
}

float AccelGyroSettings::getgyro_temp_coeff_Z2() const
{
   QMutexLocker locker(mutex);
   return data.gyro_temp_coeff[5];
}
void AccelGyroSettings::setgyro_temp_coeff_Z2(float value)
{
   mutex->lock();
   bool changed = data.gyro_temp_coeff[5] != value;
   data.gyro_temp_coeff[5] = value;
   mutex->unlock();
   if (changed) emit gyro_temp_coeff_Z2Changed(value);
}

float AccelGyroSettings::gettemp_calibrated_extent(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.temp_calibrated_extent[index];
}
void AccelGyroSettings::settemp_calibrated_extent(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.temp_calibrated_extent[index] != value;
   data.temp_calibrated_extent[index] = value;
   mutex->unlock();
   if (changed) emit temp_calibrated_extentChanged(index,value);
}

float AccelGyroSettings::gettemp_calibrated_extent_min() const
{
   QMutexLocker locker(mutex);
   return data.temp_calibrated_extent[0];
}
void AccelGyroSettings::settemp_calibrated_extent_min(float value)
{
   mutex->lock();
   bool changed = data.temp_calibrated_extent[0] != value;
   data.temp_calibrated_extent[0] = value;
   mutex->unlock();
   if (changed) emit temp_calibrated_extent_minChanged(value);
}

float AccelGyroSettings::gettemp_calibrated_extent_max() const
{
   QMutexLocker locker(mutex);
   return data.temp_calibrated_extent[1];
}
void AccelGyroSettings::settemp_calibrated_extent_max(float value)
{
   mutex->lock();
   bool changed = data.temp_calibrated_extent[1] != value;
   data.temp_calibrated_extent[1] = value;
   mutex->unlock();
   if (changed) emit temp_calibrated_extent_maxChanged(value);
}


