/**
 ******************************************************************************
 *
 * @file       auxmagsettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: auxmagsettings.xml.
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

#include "auxmagsettings.h"
#include "uavobjectfield.h"

const QString AuxMagSettings::NAME = QString("AuxMagSettings");
const QString AuxMagSettings::DESCRIPTION = QString("Settings for auxiliary magnetometer calibration");
const QString AuxMagSettings::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
AuxMagSettings::AuxMagSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList mag_biasElemNames;
    mag_biasElemNames.append("X");
    mag_biasElemNames.append("Y");
    mag_biasElemNames.append("Z");
    fields.append( new UAVObjectField(QString("mag_bias"), tr(""), QString("mGau"), UAVObjectField::FLOAT32, mag_biasElemNames, QStringList(), QString("")));
    QStringList mag_transformElemNames;
    mag_transformElemNames.append("r0c0");
    mag_transformElemNames.append("r0c1");
    mag_transformElemNames.append("r0c2");
    mag_transformElemNames.append("r1c0");
    mag_transformElemNames.append("r1c1");
    mag_transformElemNames.append("r1c2");
    mag_transformElemNames.append("r2c0");
    mag_transformElemNames.append("r2c1");
    mag_transformElemNames.append("r2c2");
    fields.append( new UAVObjectField(QString("mag_transform"), tr(""), QString("gain"), UAVObjectField::FLOAT32, mag_transformElemNames, QStringList(), QString("")));
    QStringList MagBiasNullingRateElemNames;
    MagBiasNullingRateElemNames.append("0");
    fields.append( new UAVObjectField(QString("MagBiasNullingRate"), tr(""), QString(""), UAVObjectField::FLOAT32, MagBiasNullingRateElemNames, QStringList(), QString("")));
    QStringList OrientationElemNames;
    OrientationElemNames.append("0");
    fields.append( new UAVObjectField(QString("Orientation"), tr(""), QString("degrees"), UAVObjectField::FLOAT32, OrientationElemNames, QStringList(), QString("")));
    QStringList TypeElemNames;
    TypeElemNames.append("0");
    QStringList TypeEnumOptions;
    TypeEnumOptions.append("GPSV9");
    TypeEnumOptions.append("Ext");
    fields.append( new UAVObjectField(QString("Type"), tr(""), QString(""), UAVObjectField::ENUM, TypeElemNames, TypeEnumOptions, QString("")));
    QStringList UsageElemNames;
    UsageElemNames.append("0");
    QStringList UsageEnumOptions;
    UsageEnumOptions.append("Both");
    UsageEnumOptions.append("OnboardOnly");
    UsageEnumOptions.append("AuxOnly");
    fields.append( new UAVObjectField(QString("Usage"), tr(""), QString(""), UAVObjectField::ENUM, UsageElemNames, UsageEnumOptions, QString("")));

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
UAVObject::Metadata AuxMagSettings::getDefaultMetadata()
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
void AuxMagSettings::setDefaultFieldValues()
{
    data.mag_bias[0] = 0;
    data.mag_bias[1] = 0;
    data.mag_bias[2] = 0;
    data.mag_transform[0] = 1;
    data.mag_transform[1] = 0;
    data.mag_transform[2] = 0;
    data.mag_transform[3] = 0;
    data.mag_transform[4] = 1;
    data.mag_transform[5] = 0;
    data.mag_transform[6] = 0;
    data.mag_transform[7] = 0;
    data.mag_transform[8] = 1;
    data.MagBiasNullingRate = 0;
    data.Orientation = 0;
    data.Type = 0;
    data.Usage = 0;

}

/**
 * Get the object data fields
 */
AuxMagSettings::DataFields AuxMagSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void AuxMagSettings::setData(const DataFields& data)
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

void AuxMagSettings::emitNotifications()
{
            //if (data.mag_bias[0] != oldData.mag_bias[0])
            emit mag_bias_XChanged(data.mag_bias[0]);
        //if (data.mag_bias[1] != oldData.mag_bias[1])
            emit mag_bias_YChanged(data.mag_bias[1]);
        //if (data.mag_bias[2] != oldData.mag_bias[2])
            emit mag_bias_ZChanged(data.mag_bias[2]);
        //if (data.mag_transform[0] != oldData.mag_transform[0])
            emit mag_transform_r0c0Changed(data.mag_transform[0]);
        //if (data.mag_transform[1] != oldData.mag_transform[1])
            emit mag_transform_r0c1Changed(data.mag_transform[1]);
        //if (data.mag_transform[2] != oldData.mag_transform[2])
            emit mag_transform_r0c2Changed(data.mag_transform[2]);
        //if (data.mag_transform[3] != oldData.mag_transform[3])
            emit mag_transform_r1c0Changed(data.mag_transform[3]);
        //if (data.mag_transform[4] != oldData.mag_transform[4])
            emit mag_transform_r1c1Changed(data.mag_transform[4]);
        //if (data.mag_transform[5] != oldData.mag_transform[5])
            emit mag_transform_r1c2Changed(data.mag_transform[5]);
        //if (data.mag_transform[6] != oldData.mag_transform[6])
            emit mag_transform_r2c0Changed(data.mag_transform[6]);
        //if (data.mag_transform[7] != oldData.mag_transform[7])
            emit mag_transform_r2c1Changed(data.mag_transform[7]);
        //if (data.mag_transform[8] != oldData.mag_transform[8])
            emit mag_transform_r2c2Changed(data.mag_transform[8]);
        //if (data.MagBiasNullingRate != oldData.MagBiasNullingRate)
            emit MagBiasNullingRateChanged(data.MagBiasNullingRate);
        //if (data.Orientation != oldData.Orientation)
            emit OrientationChanged(data.Orientation);
        //if (data.Type != oldData.Type)
            emit TypeChanged(data.Type);
        //if (data.Usage != oldData.Usage)
            emit UsageChanged(data.Usage);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *AuxMagSettings::clone(quint32 instID)
{
    AuxMagSettings *obj = new AuxMagSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *AuxMagSettings::dirtyClone()
{
    AuxMagSettings *obj = new AuxMagSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
AuxMagSettings *AuxMagSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<AuxMagSettings *>(objMngr->getObject(AuxMagSettings::OBJID, instID));
}

float AuxMagSettings::getmag_bias(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.mag_bias[index];
}
void AuxMagSettings::setmag_bias(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.mag_bias[index] != value;
   data.mag_bias[index] = value;
   mutex->unlock();
   if (changed) emit mag_biasChanged(index,value);
}

float AuxMagSettings::getmag_bias_X() const
{
   QMutexLocker locker(mutex);
   return data.mag_bias[0];
}
void AuxMagSettings::setmag_bias_X(float value)
{
   mutex->lock();
   bool changed = data.mag_bias[0] != value;
   data.mag_bias[0] = value;
   mutex->unlock();
   if (changed) emit mag_bias_XChanged(value);
}

float AuxMagSettings::getmag_bias_Y() const
{
   QMutexLocker locker(mutex);
   return data.mag_bias[1];
}
void AuxMagSettings::setmag_bias_Y(float value)
{
   mutex->lock();
   bool changed = data.mag_bias[1] != value;
   data.mag_bias[1] = value;
   mutex->unlock();
   if (changed) emit mag_bias_YChanged(value);
}

float AuxMagSettings::getmag_bias_Z() const
{
   QMutexLocker locker(mutex);
   return data.mag_bias[2];
}
void AuxMagSettings::setmag_bias_Z(float value)
{
   mutex->lock();
   bool changed = data.mag_bias[2] != value;
   data.mag_bias[2] = value;
   mutex->unlock();
   if (changed) emit mag_bias_ZChanged(value);
}

float AuxMagSettings::getmag_transform(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.mag_transform[index];
}
void AuxMagSettings::setmag_transform(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.mag_transform[index] != value;
   data.mag_transform[index] = value;
   mutex->unlock();
   if (changed) emit mag_transformChanged(index,value);
}

float AuxMagSettings::getmag_transform_r0c0() const
{
   QMutexLocker locker(mutex);
   return data.mag_transform[0];
}
void AuxMagSettings::setmag_transform_r0c0(float value)
{
   mutex->lock();
   bool changed = data.mag_transform[0] != value;
   data.mag_transform[0] = value;
   mutex->unlock();
   if (changed) emit mag_transform_r0c0Changed(value);
}

float AuxMagSettings::getmag_transform_r0c1() const
{
   QMutexLocker locker(mutex);
   return data.mag_transform[1];
}
void AuxMagSettings::setmag_transform_r0c1(float value)
{
   mutex->lock();
   bool changed = data.mag_transform[1] != value;
   data.mag_transform[1] = value;
   mutex->unlock();
   if (changed) emit mag_transform_r0c1Changed(value);
}

float AuxMagSettings::getmag_transform_r0c2() const
{
   QMutexLocker locker(mutex);
   return data.mag_transform[2];
}
void AuxMagSettings::setmag_transform_r0c2(float value)
{
   mutex->lock();
   bool changed = data.mag_transform[2] != value;
   data.mag_transform[2] = value;
   mutex->unlock();
   if (changed) emit mag_transform_r0c2Changed(value);
}

float AuxMagSettings::getmag_transform_r1c0() const
{
   QMutexLocker locker(mutex);
   return data.mag_transform[3];
}
void AuxMagSettings::setmag_transform_r1c0(float value)
{
   mutex->lock();
   bool changed = data.mag_transform[3] != value;
   data.mag_transform[3] = value;
   mutex->unlock();
   if (changed) emit mag_transform_r1c0Changed(value);
}

float AuxMagSettings::getmag_transform_r1c1() const
{
   QMutexLocker locker(mutex);
   return data.mag_transform[4];
}
void AuxMagSettings::setmag_transform_r1c1(float value)
{
   mutex->lock();
   bool changed = data.mag_transform[4] != value;
   data.mag_transform[4] = value;
   mutex->unlock();
   if (changed) emit mag_transform_r1c1Changed(value);
}

float AuxMagSettings::getmag_transform_r1c2() const
{
   QMutexLocker locker(mutex);
   return data.mag_transform[5];
}
void AuxMagSettings::setmag_transform_r1c2(float value)
{
   mutex->lock();
   bool changed = data.mag_transform[5] != value;
   data.mag_transform[5] = value;
   mutex->unlock();
   if (changed) emit mag_transform_r1c2Changed(value);
}

float AuxMagSettings::getmag_transform_r2c0() const
{
   QMutexLocker locker(mutex);
   return data.mag_transform[6];
}
void AuxMagSettings::setmag_transform_r2c0(float value)
{
   mutex->lock();
   bool changed = data.mag_transform[6] != value;
   data.mag_transform[6] = value;
   mutex->unlock();
   if (changed) emit mag_transform_r2c0Changed(value);
}

float AuxMagSettings::getmag_transform_r2c1() const
{
   QMutexLocker locker(mutex);
   return data.mag_transform[7];
}
void AuxMagSettings::setmag_transform_r2c1(float value)
{
   mutex->lock();
   bool changed = data.mag_transform[7] != value;
   data.mag_transform[7] = value;
   mutex->unlock();
   if (changed) emit mag_transform_r2c1Changed(value);
}

float AuxMagSettings::getmag_transform_r2c2() const
{
   QMutexLocker locker(mutex);
   return data.mag_transform[8];
}
void AuxMagSettings::setmag_transform_r2c2(float value)
{
   mutex->lock();
   bool changed = data.mag_transform[8] != value;
   data.mag_transform[8] = value;
   mutex->unlock();
   if (changed) emit mag_transform_r2c2Changed(value);
}

float AuxMagSettings::getMagBiasNullingRate() const
{
   QMutexLocker locker(mutex);
   return data.MagBiasNullingRate;
}
void AuxMagSettings::setMagBiasNullingRate(float value)
{
   mutex->lock();
   bool changed = data.MagBiasNullingRate != value;
   data.MagBiasNullingRate = value;
   mutex->unlock();
   if (changed) emit MagBiasNullingRateChanged(value);
}

float AuxMagSettings::getOrientation() const
{
   QMutexLocker locker(mutex);
   return data.Orientation;
}
void AuxMagSettings::setOrientation(float value)
{
   mutex->lock();
   bool changed = data.Orientation != value;
   data.Orientation = value;
   mutex->unlock();
   if (changed) emit OrientationChanged(value);
}

quint8 AuxMagSettings::getType() const
{
   QMutexLocker locker(mutex);
   return data.Type;
}
void AuxMagSettings::setType(quint8 value)
{
   mutex->lock();
   bool changed = data.Type != value;
   data.Type = value;
   mutex->unlock();
   if (changed) emit TypeChanged(value);
}

quint8 AuxMagSettings::getUsage() const
{
   QMutexLocker locker(mutex);
   return data.Usage;
}
void AuxMagSettings::setUsage(quint8 value)
{
   mutex->lock();
   bool changed = data.Usage != value;
   data.Usage = value;
   mutex->unlock();
   if (changed) emit UsageChanged(value);
}


