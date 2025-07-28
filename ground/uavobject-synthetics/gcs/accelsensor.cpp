/**
 ******************************************************************************
 *
 * @file       accelsensor.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: accelsensor.xml.
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

#include "accelsensor.h"
#include "uavobjectfield.h"

const QString AccelSensor::NAME = QString("AccelSensor");
const QString AccelSensor::DESCRIPTION = QString("Calibrated sensor data from 3 axis accelerometer in m/s².");
const QString AccelSensor::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
AccelSensor::AccelSensor(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList xElemNames;
    xElemNames.append("0");
    fields.append( new UAVObjectField(QString("x"), tr(""), QString("m/s^2"), UAVObjectField::FLOAT32, xElemNames, QStringList(), QString("")));
    QStringList yElemNames;
    yElemNames.append("0");
    fields.append( new UAVObjectField(QString("y"), tr(""), QString("m/s^2"), UAVObjectField::FLOAT32, yElemNames, QStringList(), QString("")));
    QStringList zElemNames;
    zElemNames.append("0");
    fields.append( new UAVObjectField(QString("z"), tr(""), QString("m/s^2"), UAVObjectField::FLOAT32, zElemNames, QStringList(), QString("")));
    QStringList temperatureElemNames;
    temperatureElemNames.append("0");
    fields.append( new UAVObjectField(QString("temperature"), tr(""), QString("deg C"), UAVObjectField::FLOAT32, temperatureElemNames, QStringList(), QString("")));

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
UAVObject::Metadata AccelSensor::getDefaultMetadata()
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
void AccelSensor::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
AccelSensor::DataFields AccelSensor::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void AccelSensor::setData(const DataFields& data)
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

void AccelSensor::emitNotifications()
{
            //if (data.x != oldData.x)
            emit xChanged(data.x);
        //if (data.y != oldData.y)
            emit yChanged(data.y);
        //if (data.z != oldData.z)
            emit zChanged(data.z);
        //if (data.temperature != oldData.temperature)
            emit temperatureChanged(data.temperature);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *AccelSensor::clone(quint32 instID)
{
    AccelSensor *obj = new AccelSensor();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *AccelSensor::dirtyClone()
{
    AccelSensor *obj = new AccelSensor();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
AccelSensor *AccelSensor::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<AccelSensor *>(objMngr->getObject(AccelSensor::OBJID, instID));
}

float AccelSensor::getx() const
{
   QMutexLocker locker(mutex);
   return data.x;
}
void AccelSensor::setx(float value)
{
   mutex->lock();
   bool changed = data.x != value;
   data.x = value;
   mutex->unlock();
   if (changed) emit xChanged(value);
}

float AccelSensor::gety() const
{
   QMutexLocker locker(mutex);
   return data.y;
}
void AccelSensor::sety(float value)
{
   mutex->lock();
   bool changed = data.y != value;
   data.y = value;
   mutex->unlock();
   if (changed) emit yChanged(value);
}

float AccelSensor::getz() const
{
   QMutexLocker locker(mutex);
   return data.z;
}
void AccelSensor::setz(float value)
{
   mutex->lock();
   bool changed = data.z != value;
   data.z = value;
   mutex->unlock();
   if (changed) emit zChanged(value);
}

float AccelSensor::gettemperature() const
{
   QMutexLocker locker(mutex);
   return data.temperature;
}
void AccelSensor::settemperature(float value)
{
   mutex->lock();
   bool changed = data.temperature != value;
   data.temperature = value;
   mutex->unlock();
   if (changed) emit temperatureChanged(value);
}


