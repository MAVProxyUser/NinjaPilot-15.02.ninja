/**
 ******************************************************************************
 *
 * @file       airspeedstate.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: airspeedstate.xml.
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

#include "airspeedstate.h"
#include "uavobjectfield.h"

const QString AirspeedState::NAME = QString("AirspeedState");
const QString AirspeedState::DESCRIPTION = QString("UAVO for true airspeed and calibrated airspeed state estimation.");
const QString AirspeedState::CATEGORY = QString("State");

/**
 * Constructor
 */
AirspeedState::AirspeedState(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList CalibratedAirspeedElemNames;
    CalibratedAirspeedElemNames.append("0");
    fields.append( new UAVObjectField(QString("CalibratedAirspeed"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, CalibratedAirspeedElemNames, QStringList(), QString("")));
    QStringList TrueAirspeedElemNames;
    TrueAirspeedElemNames.append("0");
    fields.append( new UAVObjectField(QString("TrueAirspeed"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, TrueAirspeedElemNames, QStringList(), QString("")));

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
UAVObject::Metadata AirspeedState::getDefaultMetadata()
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
void AirspeedState::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
AirspeedState::DataFields AirspeedState::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void AirspeedState::setData(const DataFields& data)
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

void AirspeedState::emitNotifications()
{
            //if (data.CalibratedAirspeed != oldData.CalibratedAirspeed)
            emit CalibratedAirspeedChanged(data.CalibratedAirspeed);
        //if (data.TrueAirspeed != oldData.TrueAirspeed)
            emit TrueAirspeedChanged(data.TrueAirspeed);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *AirspeedState::clone(quint32 instID)
{
    AirspeedState *obj = new AirspeedState();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *AirspeedState::dirtyClone()
{
    AirspeedState *obj = new AirspeedState();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
AirspeedState *AirspeedState::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<AirspeedState *>(objMngr->getObject(AirspeedState::OBJID, instID));
}

float AirspeedState::getCalibratedAirspeed() const
{
   QMutexLocker locker(mutex);
   return data.CalibratedAirspeed;
}
void AirspeedState::setCalibratedAirspeed(float value)
{
   mutex->lock();
   bool changed = data.CalibratedAirspeed != value;
   data.CalibratedAirspeed = value;
   mutex->unlock();
   if (changed) emit CalibratedAirspeedChanged(value);
}

float AirspeedState::getTrueAirspeed() const
{
   QMutexLocker locker(mutex);
   return data.TrueAirspeed;
}
void AirspeedState::setTrueAirspeed(float value)
{
   mutex->lock();
   bool changed = data.TrueAirspeed != value;
   data.TrueAirspeed = value;
   mutex->unlock();
   if (changed) emit TrueAirspeedChanged(value);
}


