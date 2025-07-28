/**
 ******************************************************************************
 *
 * @file       altitudefiltersettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: altitudefiltersettings.xml.
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

#include "altitudefiltersettings.h"
#include "uavobjectfield.h"

const QString AltitudeFilterSettings::NAME = QString("AltitudeFilterSettings");
const QString AltitudeFilterSettings::DESCRIPTION = QString("Settings for the @ref State Estimator module plugin altitudeFilter");
const QString AltitudeFilterSettings::CATEGORY = QString("State");

/**
 * Constructor
 */
AltitudeFilterSettings::AltitudeFilterSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList AccelLowPassKpElemNames;
    AccelLowPassKpElemNames.append("0");
    fields.append( new UAVObjectField(QString("AccelLowPassKp"), tr(""), QString("m/s^2"), UAVObjectField::FLOAT32, AccelLowPassKpElemNames, QStringList(), QString("")));
    QStringList AccelDriftKiElemNames;
    AccelDriftKiElemNames.append("0");
    fields.append( new UAVObjectField(QString("AccelDriftKi"), tr(""), QString("m/s^2"), UAVObjectField::FLOAT32, AccelDriftKiElemNames, QStringList(), QString("")));
    QStringList InitializationAccelDriftKiElemNames;
    InitializationAccelDriftKiElemNames.append("0");
    fields.append( new UAVObjectField(QString("InitializationAccelDriftKi"), tr(""), QString("m/s^2"), UAVObjectField::FLOAT32, InitializationAccelDriftKiElemNames, QStringList(), QString("")));
    QStringList BaroKpElemNames;
    BaroKpElemNames.append("0");
    fields.append( new UAVObjectField(QString("BaroKp"), tr(""), QString("m"), UAVObjectField::FLOAT32, BaroKpElemNames, QStringList(), QString("")));

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
UAVObject::Metadata AltitudeFilterSettings::getDefaultMetadata()
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
void AltitudeFilterSettings::setDefaultFieldValues()
{
    data.AccelLowPassKp = 0.04;
    data.AccelDriftKi = 0.0005;
    data.InitializationAccelDriftKi = 0.2;
    data.BaroKp = 0.04;

}

/**
 * Get the object data fields
 */
AltitudeFilterSettings::DataFields AltitudeFilterSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void AltitudeFilterSettings::setData(const DataFields& data)
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

void AltitudeFilterSettings::emitNotifications()
{
            //if (data.AccelLowPassKp != oldData.AccelLowPassKp)
            emit AccelLowPassKpChanged(data.AccelLowPassKp);
        //if (data.AccelDriftKi != oldData.AccelDriftKi)
            emit AccelDriftKiChanged(data.AccelDriftKi);
        //if (data.InitializationAccelDriftKi != oldData.InitializationAccelDriftKi)
            emit InitializationAccelDriftKiChanged(data.InitializationAccelDriftKi);
        //if (data.BaroKp != oldData.BaroKp)
            emit BaroKpChanged(data.BaroKp);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *AltitudeFilterSettings::clone(quint32 instID)
{
    AltitudeFilterSettings *obj = new AltitudeFilterSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *AltitudeFilterSettings::dirtyClone()
{
    AltitudeFilterSettings *obj = new AltitudeFilterSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
AltitudeFilterSettings *AltitudeFilterSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<AltitudeFilterSettings *>(objMngr->getObject(AltitudeFilterSettings::OBJID, instID));
}

float AltitudeFilterSettings::getAccelLowPassKp() const
{
   QMutexLocker locker(mutex);
   return data.AccelLowPassKp;
}
void AltitudeFilterSettings::setAccelLowPassKp(float value)
{
   mutex->lock();
   bool changed = data.AccelLowPassKp != value;
   data.AccelLowPassKp = value;
   mutex->unlock();
   if (changed) emit AccelLowPassKpChanged(value);
}

float AltitudeFilterSettings::getAccelDriftKi() const
{
   QMutexLocker locker(mutex);
   return data.AccelDriftKi;
}
void AltitudeFilterSettings::setAccelDriftKi(float value)
{
   mutex->lock();
   bool changed = data.AccelDriftKi != value;
   data.AccelDriftKi = value;
   mutex->unlock();
   if (changed) emit AccelDriftKiChanged(value);
}

float AltitudeFilterSettings::getInitializationAccelDriftKi() const
{
   QMutexLocker locker(mutex);
   return data.InitializationAccelDriftKi;
}
void AltitudeFilterSettings::setInitializationAccelDriftKi(float value)
{
   mutex->lock();
   bool changed = data.InitializationAccelDriftKi != value;
   data.InitializationAccelDriftKi = value;
   mutex->unlock();
   if (changed) emit InitializationAccelDriftKiChanged(value);
}

float AltitudeFilterSettings::getBaroKp() const
{
   QMutexLocker locker(mutex);
   return data.BaroKp;
}
void AltitudeFilterSettings::setBaroKp(float value)
{
   mutex->lock();
   bool changed = data.BaroKp != value;
   data.BaroKp = value;
   mutex->unlock();
   if (changed) emit BaroKpChanged(value);
}


