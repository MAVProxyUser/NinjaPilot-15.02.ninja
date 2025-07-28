/**
 ******************************************************************************
 *
 * @file       airspeedsensor.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: airspeedsensor.xml.
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

#include "airspeedsensor.h"
#include "uavobjectfield.h"

const QString AirspeedSensor::NAME = QString("AirspeedSensor");
const QString AirspeedSensor::DESCRIPTION = QString("The raw data from the dynamic pressure sensor with pressure, temperature and airspeed.");
const QString AirspeedSensor::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
AirspeedSensor::AirspeedSensor(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList DifferentialPressureElemNames;
    DifferentialPressureElemNames.append("0");
    fields.append( new UAVObjectField(QString("DifferentialPressure"), tr(""), QString("Pa"), UAVObjectField::FLOAT32, DifferentialPressureElemNames, QStringList(), QString("")));
    QStringList TemperatureElemNames;
    TemperatureElemNames.append("0");
    fields.append( new UAVObjectField(QString("Temperature"), tr(""), QString("K"), UAVObjectField::FLOAT32, TemperatureElemNames, QStringList(), QString("")));
    QStringList CalibratedAirspeedElemNames;
    CalibratedAirspeedElemNames.append("0");
    fields.append( new UAVObjectField(QString("CalibratedAirspeed"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, CalibratedAirspeedElemNames, QStringList(), QString("")));
    QStringList TrueAirspeedElemNames;
    TrueAirspeedElemNames.append("0");
    fields.append( new UAVObjectField(QString("TrueAirspeed"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, TrueAirspeedElemNames, QStringList(), QString("")));
    QStringList SensorValueElemNames;
    SensorValueElemNames.append("0");
    fields.append( new UAVObjectField(QString("SensorValue"), tr(""), QString("raw"), UAVObjectField::UINT16, SensorValueElemNames, QStringList(), QString("")));
    QStringList SensorValueTemperatureElemNames;
    SensorValueTemperatureElemNames.append("0");
    fields.append( new UAVObjectField(QString("SensorValueTemperature"), tr(""), QString("raw"), UAVObjectField::UINT16, SensorValueTemperatureElemNames, QStringList(), QString("")));
    QStringList SensorConnectedElemNames;
    SensorConnectedElemNames.append("0");
    QStringList SensorConnectedEnumOptions;
    SensorConnectedEnumOptions.append("False");
    SensorConnectedEnumOptions.append("True");
    fields.append( new UAVObjectField(QString("SensorConnected"), tr(""), QString(""), UAVObjectField::ENUM, SensorConnectedElemNames, SensorConnectedEnumOptions, QString("")));

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
UAVObject::Metadata AirspeedSensor::getDefaultMetadata()
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
void AirspeedSensor::setDefaultFieldValues()
{
    data.TrueAirspeed = -1;

}

/**
 * Get the object data fields
 */
AirspeedSensor::DataFields AirspeedSensor::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void AirspeedSensor::setData(const DataFields& data)
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

void AirspeedSensor::emitNotifications()
{
            //if (data.DifferentialPressure != oldData.DifferentialPressure)
            emit DifferentialPressureChanged(data.DifferentialPressure);
        //if (data.Temperature != oldData.Temperature)
            emit TemperatureChanged(data.Temperature);
        //if (data.CalibratedAirspeed != oldData.CalibratedAirspeed)
            emit CalibratedAirspeedChanged(data.CalibratedAirspeed);
        //if (data.TrueAirspeed != oldData.TrueAirspeed)
            emit TrueAirspeedChanged(data.TrueAirspeed);
        //if (data.SensorValue != oldData.SensorValue)
            emit SensorValueChanged(data.SensorValue);
        //if (data.SensorValueTemperature != oldData.SensorValueTemperature)
            emit SensorValueTemperatureChanged(data.SensorValueTemperature);
        //if (data.SensorConnected != oldData.SensorConnected)
            emit SensorConnectedChanged(data.SensorConnected);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *AirspeedSensor::clone(quint32 instID)
{
    AirspeedSensor *obj = new AirspeedSensor();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *AirspeedSensor::dirtyClone()
{
    AirspeedSensor *obj = new AirspeedSensor();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
AirspeedSensor *AirspeedSensor::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<AirspeedSensor *>(objMngr->getObject(AirspeedSensor::OBJID, instID));
}

float AirspeedSensor::getDifferentialPressure() const
{
   QMutexLocker locker(mutex);
   return data.DifferentialPressure;
}
void AirspeedSensor::setDifferentialPressure(float value)
{
   mutex->lock();
   bool changed = data.DifferentialPressure != value;
   data.DifferentialPressure = value;
   mutex->unlock();
   if (changed) emit DifferentialPressureChanged(value);
}

float AirspeedSensor::getTemperature() const
{
   QMutexLocker locker(mutex);
   return data.Temperature;
}
void AirspeedSensor::setTemperature(float value)
{
   mutex->lock();
   bool changed = data.Temperature != value;
   data.Temperature = value;
   mutex->unlock();
   if (changed) emit TemperatureChanged(value);
}

float AirspeedSensor::getCalibratedAirspeed() const
{
   QMutexLocker locker(mutex);
   return data.CalibratedAirspeed;
}
void AirspeedSensor::setCalibratedAirspeed(float value)
{
   mutex->lock();
   bool changed = data.CalibratedAirspeed != value;
   data.CalibratedAirspeed = value;
   mutex->unlock();
   if (changed) emit CalibratedAirspeedChanged(value);
}

float AirspeedSensor::getTrueAirspeed() const
{
   QMutexLocker locker(mutex);
   return data.TrueAirspeed;
}
void AirspeedSensor::setTrueAirspeed(float value)
{
   mutex->lock();
   bool changed = data.TrueAirspeed != value;
   data.TrueAirspeed = value;
   mutex->unlock();
   if (changed) emit TrueAirspeedChanged(value);
}

quint16 AirspeedSensor::getSensorValue() const
{
   QMutexLocker locker(mutex);
   return data.SensorValue;
}
void AirspeedSensor::setSensorValue(quint16 value)
{
   mutex->lock();
   bool changed = data.SensorValue != value;
   data.SensorValue = value;
   mutex->unlock();
   if (changed) emit SensorValueChanged(value);
}

quint16 AirspeedSensor::getSensorValueTemperature() const
{
   QMutexLocker locker(mutex);
   return data.SensorValueTemperature;
}
void AirspeedSensor::setSensorValueTemperature(quint16 value)
{
   mutex->lock();
   bool changed = data.SensorValueTemperature != value;
   data.SensorValueTemperature = value;
   mutex->unlock();
   if (changed) emit SensorValueTemperatureChanged(value);
}

quint8 AirspeedSensor::getSensorConnected() const
{
   QMutexLocker locker(mutex);
   return data.SensorConnected;
}
void AirspeedSensor::setSensorConnected(quint8 value)
{
   mutex->lock();
   bool changed = data.SensorConnected != value;
   data.SensorConnected = value;
   mutex->unlock();
   if (changed) emit SensorConnectedChanged(value);
}


