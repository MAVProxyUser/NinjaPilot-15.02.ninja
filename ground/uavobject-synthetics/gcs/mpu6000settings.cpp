/**
 ******************************************************************************
 *
 * @file       mpu6000settings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: mpu6000settings.xml.
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

#include "mpu6000settings.h"
#include "uavobjectfield.h"

const QString Mpu6000Settings::NAME = QString("Mpu6000Settings");
const QString Mpu6000Settings::DESCRIPTION = QString("Settings for the @ref MPU6000 sensor used on CC3D and Revolution. Reboot the board for this to takes effect");
const QString Mpu6000Settings::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
Mpu6000Settings::Mpu6000Settings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList GyroScaleElemNames;
    GyroScaleElemNames.append("0");
    QStringList GyroScaleEnumOptions;
    GyroScaleEnumOptions.append("Scale_250");
    GyroScaleEnumOptions.append("Scale_500");
    GyroScaleEnumOptions.append("Scale_1000");
    GyroScaleEnumOptions.append("Scale_2000");
    fields.append( new UAVObjectField(QString("GyroScale"), tr(""), QString("deg/s"), UAVObjectField::ENUM, GyroScaleElemNames, GyroScaleEnumOptions, QString("")));
    QStringList AccelScaleElemNames;
    AccelScaleElemNames.append("0");
    QStringList AccelScaleEnumOptions;
    AccelScaleEnumOptions.append("Scale_2g");
    AccelScaleEnumOptions.append("Scale_4g");
    AccelScaleEnumOptions.append("Scale_8g");
    AccelScaleEnumOptions.append("Scale_16g");
    fields.append( new UAVObjectField(QString("AccelScale"), tr(""), QString("g"), UAVObjectField::ENUM, AccelScaleElemNames, AccelScaleEnumOptions, QString("")));
    QStringList FilterSettingElemNames;
    FilterSettingElemNames.append("0");
    QStringList FilterSettingEnumOptions;
    FilterSettingEnumOptions.append("Lowpass_256_Hz");
    FilterSettingEnumOptions.append("Lowpass_188_Hz");
    FilterSettingEnumOptions.append("Lowpass_98_Hz");
    FilterSettingEnumOptions.append("Lowpass_42_Hz");
    FilterSettingEnumOptions.append("Lowpass_20_Hz");
    FilterSettingEnumOptions.append("Lowpass_10_Hz");
    FilterSettingEnumOptions.append("Lowpass_5_Hz");
    fields.append( new UAVObjectField(QString("FilterSetting"), tr(""), QString("Hz"), UAVObjectField::ENUM, FilterSettingElemNames, FilterSettingEnumOptions, QString("")));

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
UAVObject::Metadata Mpu6000Settings::getDefaultMetadata()
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
void Mpu6000Settings::setDefaultFieldValues()
{
    data.GyroScale = 3;
    data.AccelScale = 2;
    data.FilterSetting = 0;

}

/**
 * Get the object data fields
 */
Mpu6000Settings::DataFields Mpu6000Settings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void Mpu6000Settings::setData(const DataFields& data)
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

void Mpu6000Settings::emitNotifications()
{
            //if (data.GyroScale != oldData.GyroScale)
            emit GyroScaleChanged(data.GyroScale);
        //if (data.AccelScale != oldData.AccelScale)
            emit AccelScaleChanged(data.AccelScale);
        //if (data.FilterSetting != oldData.FilterSetting)
            emit FilterSettingChanged(data.FilterSetting);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *Mpu6000Settings::clone(quint32 instID)
{
    Mpu6000Settings *obj = new Mpu6000Settings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *Mpu6000Settings::dirtyClone()
{
    Mpu6000Settings *obj = new Mpu6000Settings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
Mpu6000Settings *Mpu6000Settings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<Mpu6000Settings *>(objMngr->getObject(Mpu6000Settings::OBJID, instID));
}

quint8 Mpu6000Settings::getGyroScale() const
{
   QMutexLocker locker(mutex);
   return data.GyroScale;
}
void Mpu6000Settings::setGyroScale(quint8 value)
{
   mutex->lock();
   bool changed = data.GyroScale != value;
   data.GyroScale = value;
   mutex->unlock();
   if (changed) emit GyroScaleChanged(value);
}

quint8 Mpu6000Settings::getAccelScale() const
{
   QMutexLocker locker(mutex);
   return data.AccelScale;
}
void Mpu6000Settings::setAccelScale(quint8 value)
{
   mutex->lock();
   bool changed = data.AccelScale != value;
   data.AccelScale = value;
   mutex->unlock();
   if (changed) emit AccelScaleChanged(value);
}

quint8 Mpu6000Settings::getFilterSetting() const
{
   QMutexLocker locker(mutex);
   return data.FilterSetting;
}
void Mpu6000Settings::setFilterSetting(quint8 value)
{
   mutex->lock();
   bool changed = data.FilterSetting != value;
   data.FilterSetting = value;
   mutex->unlock();
   if (changed) emit FilterSettingChanged(value);
}


