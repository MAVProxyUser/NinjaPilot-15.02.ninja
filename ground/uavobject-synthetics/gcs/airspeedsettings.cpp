/**
 ******************************************************************************
 *
 * @file       airspeedsettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: airspeedsettings.xml.
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

#include "airspeedsettings.h"
#include "uavobjectfield.h"

const QString AirspeedSettings::NAME = QString("AirspeedSettings");
const QString AirspeedSettings::DESCRIPTION = QString("Settings for the @ref BaroAirspeed module used on CopterControl or Revolution");
const QString AirspeedSettings::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
AirspeedSettings::AirspeedSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList ScaleElemNames;
    ScaleElemNames.append("0");
    fields.append( new UAVObjectField(QString("Scale"), tr(""), QString("raw"), UAVObjectField::FLOAT32, ScaleElemNames, QStringList(), QString("")));
    QStringList IMUBasedEstimationLowPassPeriod1ElemNames;
    IMUBasedEstimationLowPassPeriod1ElemNames.append("0");
    fields.append( new UAVObjectField(QString("IMUBasedEstimationLowPassPeriod1"), tr(""), QString("s"), UAVObjectField::FLOAT32, IMUBasedEstimationLowPassPeriod1ElemNames, QStringList(), QString("")));
    QStringList IMUBasedEstimationLowPassPeriod2ElemNames;
    IMUBasedEstimationLowPassPeriod2ElemNames.append("0");
    fields.append( new UAVObjectField(QString("IMUBasedEstimationLowPassPeriod2"), tr(""), QString("s"), UAVObjectField::FLOAT32, IMUBasedEstimationLowPassPeriod2ElemNames, QStringList(), QString("")));
    QStringList ZeroPointElemNames;
    ZeroPointElemNames.append("0");
    fields.append( new UAVObjectField(QString("ZeroPoint"), tr(""), QString("raw"), UAVObjectField::UINT16, ZeroPointElemNames, QStringList(), QString("")));
    QStringList SamplePeriodElemNames;
    SamplePeriodElemNames.append("0");
    fields.append( new UAVObjectField(QString("SamplePeriod"), tr(""), QString("ms"), UAVObjectField::UINT8, SamplePeriodElemNames, QStringList(), QString("")));
    QStringList AirspeedSensorTypeElemNames;
    AirspeedSensorTypeElemNames.append("0");
    QStringList AirspeedSensorTypeEnumOptions;
    AirspeedSensorTypeEnumOptions.append("PixHawkAirspeedMS4525DO");
    AirspeedSensorTypeEnumOptions.append("EagleTreeAirspeedV3");
    AirspeedSensorTypeEnumOptions.append("DIYDronesMPXV5004");
    AirspeedSensorTypeEnumOptions.append("DIYDronesMPXV7002");
    AirspeedSensorTypeEnumOptions.append("GroundSpeedBasedWindEstimation");
    AirspeedSensorTypeEnumOptions.append("None");
    fields.append( new UAVObjectField(QString("AirspeedSensorType"), tr(""), QString(""), UAVObjectField::ENUM, AirspeedSensorTypeElemNames, AirspeedSensorTypeEnumOptions, QString("")));

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
UAVObject::Metadata AirspeedSettings::getDefaultMetadata()
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
void AirspeedSettings::setDefaultFieldValues()
{
    data.Scale = 1;
    data.IMUBasedEstimationLowPassPeriod1 = 0.5;
    data.IMUBasedEstimationLowPassPeriod2 = 10;
    data.ZeroPoint = 0;
    data.SamplePeriod = 100;
    data.AirspeedSensorType = 5;

}

/**
 * Get the object data fields
 */
AirspeedSettings::DataFields AirspeedSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void AirspeedSettings::setData(const DataFields& data)
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

void AirspeedSettings::emitNotifications()
{
            //if (data.Scale != oldData.Scale)
            emit ScaleChanged(data.Scale);
        //if (data.IMUBasedEstimationLowPassPeriod1 != oldData.IMUBasedEstimationLowPassPeriod1)
            emit IMUBasedEstimationLowPassPeriod1Changed(data.IMUBasedEstimationLowPassPeriod1);
        //if (data.IMUBasedEstimationLowPassPeriod2 != oldData.IMUBasedEstimationLowPassPeriod2)
            emit IMUBasedEstimationLowPassPeriod2Changed(data.IMUBasedEstimationLowPassPeriod2);
        //if (data.ZeroPoint != oldData.ZeroPoint)
            emit ZeroPointChanged(data.ZeroPoint);
        //if (data.SamplePeriod != oldData.SamplePeriod)
            emit SamplePeriodChanged(data.SamplePeriod);
        //if (data.AirspeedSensorType != oldData.AirspeedSensorType)
            emit AirspeedSensorTypeChanged(data.AirspeedSensorType);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *AirspeedSettings::clone(quint32 instID)
{
    AirspeedSettings *obj = new AirspeedSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *AirspeedSettings::dirtyClone()
{
    AirspeedSettings *obj = new AirspeedSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
AirspeedSettings *AirspeedSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<AirspeedSettings *>(objMngr->getObject(AirspeedSettings::OBJID, instID));
}

float AirspeedSettings::getScale() const
{
   QMutexLocker locker(mutex);
   return data.Scale;
}
void AirspeedSettings::setScale(float value)
{
   mutex->lock();
   bool changed = data.Scale != value;
   data.Scale = value;
   mutex->unlock();
   if (changed) emit ScaleChanged(value);
}

float AirspeedSettings::getIMUBasedEstimationLowPassPeriod1() const
{
   QMutexLocker locker(mutex);
   return data.IMUBasedEstimationLowPassPeriod1;
}
void AirspeedSettings::setIMUBasedEstimationLowPassPeriod1(float value)
{
   mutex->lock();
   bool changed = data.IMUBasedEstimationLowPassPeriod1 != value;
   data.IMUBasedEstimationLowPassPeriod1 = value;
   mutex->unlock();
   if (changed) emit IMUBasedEstimationLowPassPeriod1Changed(value);
}

float AirspeedSettings::getIMUBasedEstimationLowPassPeriod2() const
{
   QMutexLocker locker(mutex);
   return data.IMUBasedEstimationLowPassPeriod2;
}
void AirspeedSettings::setIMUBasedEstimationLowPassPeriod2(float value)
{
   mutex->lock();
   bool changed = data.IMUBasedEstimationLowPassPeriod2 != value;
   data.IMUBasedEstimationLowPassPeriod2 = value;
   mutex->unlock();
   if (changed) emit IMUBasedEstimationLowPassPeriod2Changed(value);
}

quint16 AirspeedSettings::getZeroPoint() const
{
   QMutexLocker locker(mutex);
   return data.ZeroPoint;
}
void AirspeedSettings::setZeroPoint(quint16 value)
{
   mutex->lock();
   bool changed = data.ZeroPoint != value;
   data.ZeroPoint = value;
   mutex->unlock();
   if (changed) emit ZeroPointChanged(value);
}

quint8 AirspeedSettings::getSamplePeriod() const
{
   QMutexLocker locker(mutex);
   return data.SamplePeriod;
}
void AirspeedSettings::setSamplePeriod(quint8 value)
{
   mutex->lock();
   bool changed = data.SamplePeriod != value;
   data.SamplePeriod = value;
   mutex->unlock();
   if (changed) emit SamplePeriodChanged(value);
}

quint8 AirspeedSettings::getAirspeedSensorType() const
{
   QMutexLocker locker(mutex);
   return data.AirspeedSensorType;
}
void AirspeedSettings::setAirspeedSensorType(quint8 value)
{
   mutex->lock();
   bool changed = data.AirspeedSensorType != value;
   data.AirspeedSensorType = value;
   mutex->unlock();
   if (changed) emit AirspeedSensorTypeChanged(value);
}


