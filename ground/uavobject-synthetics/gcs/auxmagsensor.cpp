/**
 ******************************************************************************
 *
 * @file       auxmagsensor.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: auxmagsensor.xml.
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

#include "auxmagsensor.h"
#include "uavobjectfield.h"

const QString AuxMagSensor::NAME = QString("AuxMagSensor");
const QString AuxMagSensor::DESCRIPTION = QString("Calibrated sensor data from aux 3 axis magnetometer in MilliGauss.");
const QString AuxMagSensor::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
AuxMagSensor::AuxMagSensor(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList xElemNames;
    xElemNames.append("0");
    fields.append( new UAVObjectField(QString("x"), tr(""), QString("mGa"), UAVObjectField::FLOAT32, xElemNames, QStringList(), QString("")));
    QStringList yElemNames;
    yElemNames.append("0");
    fields.append( new UAVObjectField(QString("y"), tr(""), QString("mGa"), UAVObjectField::FLOAT32, yElemNames, QStringList(), QString("")));
    QStringList zElemNames;
    zElemNames.append("0");
    fields.append( new UAVObjectField(QString("z"), tr(""), QString("mGa"), UAVObjectField::FLOAT32, zElemNames, QStringList(), QString("")));
    QStringList StatusElemNames;
    StatusElemNames.append("0");
    QStringList StatusEnumOptions;
    StatusEnumOptions.append("None");
    StatusEnumOptions.append("Ok");
    fields.append( new UAVObjectField(QString("Status"), tr(""), QString(""), UAVObjectField::ENUM, StatusElemNames, StatusEnumOptions, QString("")));

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
UAVObject::Metadata AuxMagSensor::getDefaultMetadata()
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
void AuxMagSensor::setDefaultFieldValues()
{
    data.Status = 0;

}

/**
 * Get the object data fields
 */
AuxMagSensor::DataFields AuxMagSensor::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void AuxMagSensor::setData(const DataFields& data)
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

void AuxMagSensor::emitNotifications()
{
            //if (data.x != oldData.x)
            emit xChanged(data.x);
        //if (data.y != oldData.y)
            emit yChanged(data.y);
        //if (data.z != oldData.z)
            emit zChanged(data.z);
        //if (data.Status != oldData.Status)
            emit StatusChanged(data.Status);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *AuxMagSensor::clone(quint32 instID)
{
    AuxMagSensor *obj = new AuxMagSensor();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *AuxMagSensor::dirtyClone()
{
    AuxMagSensor *obj = new AuxMagSensor();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
AuxMagSensor *AuxMagSensor::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<AuxMagSensor *>(objMngr->getObject(AuxMagSensor::OBJID, instID));
}

float AuxMagSensor::getx() const
{
   QMutexLocker locker(mutex);
   return data.x;
}
void AuxMagSensor::setx(float value)
{
   mutex->lock();
   bool changed = data.x != value;
   data.x = value;
   mutex->unlock();
   if (changed) emit xChanged(value);
}

float AuxMagSensor::gety() const
{
   QMutexLocker locker(mutex);
   return data.y;
}
void AuxMagSensor::sety(float value)
{
   mutex->lock();
   bool changed = data.y != value;
   data.y = value;
   mutex->unlock();
   if (changed) emit yChanged(value);
}

float AuxMagSensor::getz() const
{
   QMutexLocker locker(mutex);
   return data.z;
}
void AuxMagSensor::setz(float value)
{
   mutex->lock();
   bool changed = data.z != value;
   data.z = value;
   mutex->unlock();
   if (changed) emit zChanged(value);
}

quint8 AuxMagSensor::getStatus() const
{
   QMutexLocker locker(mutex);
   return data.Status;
}
void AuxMagSensor::setStatus(quint8 value)
{
   mutex->lock();
   bool changed = data.Status != value;
   data.Status = value;
   mutex->unlock();
   if (changed) emit StatusChanged(value);
}


