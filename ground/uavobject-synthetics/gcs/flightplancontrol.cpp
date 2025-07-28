/**
 ******************************************************************************
 *
 * @file       flightplancontrol.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: flightplancontrol.xml.
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

#include "flightplancontrol.h"
#include "uavobjectfield.h"

const QString FlightPlanControl::NAME = QString("FlightPlanControl");
const QString FlightPlanControl::DESCRIPTION = QString("Control the flight plan script");
const QString FlightPlanControl::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
FlightPlanControl::FlightPlanControl(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList CommandElemNames;
    CommandElemNames.append("0");
    QStringList CommandEnumOptions;
    CommandEnumOptions.append("Start");
    CommandEnumOptions.append("Stop");
    CommandEnumOptions.append("Kill");
    fields.append( new UAVObjectField(QString("Command"), tr(""), QString(""), UAVObjectField::ENUM, CommandElemNames, CommandEnumOptions, QString("")));

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
UAVObject::Metadata FlightPlanControl::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        1 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        1 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
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
void FlightPlanControl::setDefaultFieldValues()
{
    data.Command = 0;

}

/**
 * Get the object data fields
 */
FlightPlanControl::DataFields FlightPlanControl::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void FlightPlanControl::setData(const DataFields& data)
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

void FlightPlanControl::emitNotifications()
{
            //if (data.Command != oldData.Command)
            emit CommandChanged(data.Command);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *FlightPlanControl::clone(quint32 instID)
{
    FlightPlanControl *obj = new FlightPlanControl();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *FlightPlanControl::dirtyClone()
{
    FlightPlanControl *obj = new FlightPlanControl();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
FlightPlanControl *FlightPlanControl::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<FlightPlanControl *>(objMngr->getObject(FlightPlanControl::OBJID, instID));
}

quint8 FlightPlanControl::getCommand() const
{
   QMutexLocker locker(mutex);
   return data.Command;
}
void FlightPlanControl::setCommand(quint8 value)
{
   mutex->lock();
   bool changed = data.Command != value;
   data.Command = value;
   mutex->unlock();
   if (changed) emit CommandChanged(value);
}


