/**
 ******************************************************************************
 *
 * @file       flightstatus.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: flightstatus.xml.
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

#include "flightstatus.h"
#include "uavobjectfield.h"

const QString FlightStatus::NAME = QString("FlightStatus");
const QString FlightStatus::DESCRIPTION = QString("Contains major flight status information for other modules.");
const QString FlightStatus::CATEGORY = QString("Control");

/**
 * Constructor
 */
FlightStatus::FlightStatus(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList ArmedElemNames;
    ArmedElemNames.append("0");
    QStringList ArmedEnumOptions;
    ArmedEnumOptions.append("Disarmed");
    ArmedEnumOptions.append("Arming");
    ArmedEnumOptions.append("Armed");
    fields.append( new UAVObjectField(QString("Armed"), tr(""), QString(""), UAVObjectField::ENUM, ArmedElemNames, ArmedEnumOptions, QString("")));
    QStringList FlightModeElemNames;
    FlightModeElemNames.append("0");
    QStringList FlightModeEnumOptions;
    FlightModeEnumOptions.append("Manual");
    FlightModeEnumOptions.append("Stabilized1");
    FlightModeEnumOptions.append("Stabilized2");
    FlightModeEnumOptions.append("Stabilized3");
    FlightModeEnumOptions.append("Stabilized4");
    FlightModeEnumOptions.append("Stabilized5");
    FlightModeEnumOptions.append("Stabilized6");
    FlightModeEnumOptions.append("PositionHold");
    FlightModeEnumOptions.append("CourseLock");
    FlightModeEnumOptions.append("PositionRoam");
    FlightModeEnumOptions.append("HomeLeash");
    FlightModeEnumOptions.append("AbsolutePosition");
    FlightModeEnumOptions.append("ReturnToBase");
    FlightModeEnumOptions.append("Land");
    FlightModeEnumOptions.append("PathPlanner");
    FlightModeEnumOptions.append("POI");
    FlightModeEnumOptions.append("AutoCruise");
    fields.append( new UAVObjectField(QString("FlightMode"), tr(""), QString(""), UAVObjectField::ENUM, FlightModeElemNames, FlightModeEnumOptions, QString("")));
    QStringList FlightModeAssistElemNames;
    FlightModeAssistElemNames.append("0");
    QStringList FlightModeAssistEnumOptions;
    FlightModeAssistEnumOptions.append("None");
    FlightModeAssistEnumOptions.append("GPSAssist_PrimaryThrust");
    FlightModeAssistEnumOptions.append("GPSAssist");
    fields.append( new UAVObjectField(QString("FlightModeAssist"), tr(""), QString(""), UAVObjectField::ENUM, FlightModeAssistElemNames, FlightModeAssistEnumOptions, QString("")));
    QStringList AssistedControlStateElemNames;
    AssistedControlStateElemNames.append("0");
    QStringList AssistedControlStateEnumOptions;
    AssistedControlStateEnumOptions.append("Primary");
    AssistedControlStateEnumOptions.append("Brake");
    AssistedControlStateEnumOptions.append("Hold");
    fields.append( new UAVObjectField(QString("AssistedControlState"), tr(""), QString(""), UAVObjectField::ENUM, AssistedControlStateElemNames, AssistedControlStateEnumOptions, QString("")));
    QStringList AssistedThrottleStateElemNames;
    AssistedThrottleStateElemNames.append("0");
    QStringList AssistedThrottleStateEnumOptions;
    AssistedThrottleStateEnumOptions.append("Manual");
    AssistedThrottleStateEnumOptions.append("Auto");
    AssistedThrottleStateEnumOptions.append("AutoOverride");
    fields.append( new UAVObjectField(QString("AssistedThrottleState"), tr(""), QString(""), UAVObjectField::ENUM, AssistedThrottleStateElemNames, AssistedThrottleStateEnumOptions, QString("")));
    QStringList ControlChainElemNames;
    ControlChainElemNames.append("Stabilization");
    ControlChainElemNames.append("PathFollower");
    ControlChainElemNames.append("PathPlanner");
    QStringList ControlChainEnumOptions;
    ControlChainEnumOptions.append("false");
    ControlChainEnumOptions.append("true");
    fields.append( new UAVObjectField(QString("ControlChain"), tr(""), QString("bool"), UAVObjectField::ENUM, ControlChainElemNames, ControlChainEnumOptions, QString("")));

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
UAVObject::Metadata FlightStatus::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        0 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        0 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_ONCHANGE << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_LOGGING_UPDATE_MODE_SHIFT;
    metadata.flightTelemetryUpdatePeriod = 5000;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void FlightStatus::setDefaultFieldValues()
{
    data.Armed = 0;
    data.AssistedControlState = 0;
    data.AssistedThrottleState = 0;

}

/**
 * Get the object data fields
 */
FlightStatus::DataFields FlightStatus::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void FlightStatus::setData(const DataFields& data)
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

void FlightStatus::emitNotifications()
{
            //if (data.Armed != oldData.Armed)
            emit ArmedChanged(data.Armed);
        //if (data.FlightMode != oldData.FlightMode)
            emit FlightModeChanged(data.FlightMode);
        //if (data.FlightModeAssist != oldData.FlightModeAssist)
            emit FlightModeAssistChanged(data.FlightModeAssist);
        //if (data.AssistedControlState != oldData.AssistedControlState)
            emit AssistedControlStateChanged(data.AssistedControlState);
        //if (data.AssistedThrottleState != oldData.AssistedThrottleState)
            emit AssistedThrottleStateChanged(data.AssistedThrottleState);
        //if (data.ControlChain[0] != oldData.ControlChain[0])
            emit ControlChain_StabilizationChanged(data.ControlChain[0]);
        //if (data.ControlChain[1] != oldData.ControlChain[1])
            emit ControlChain_PathFollowerChanged(data.ControlChain[1]);
        //if (data.ControlChain[2] != oldData.ControlChain[2])
            emit ControlChain_PathPlannerChanged(data.ControlChain[2]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *FlightStatus::clone(quint32 instID)
{
    FlightStatus *obj = new FlightStatus();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *FlightStatus::dirtyClone()
{
    FlightStatus *obj = new FlightStatus();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
FlightStatus *FlightStatus::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<FlightStatus *>(objMngr->getObject(FlightStatus::OBJID, instID));
}

quint8 FlightStatus::getArmed() const
{
   QMutexLocker locker(mutex);
   return data.Armed;
}
void FlightStatus::setArmed(quint8 value)
{
   mutex->lock();
   bool changed = data.Armed != value;
   data.Armed = value;
   mutex->unlock();
   if (changed) emit ArmedChanged(value);
}

quint8 FlightStatus::getFlightMode() const
{
   QMutexLocker locker(mutex);
   return data.FlightMode;
}
void FlightStatus::setFlightMode(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightMode != value;
   data.FlightMode = value;
   mutex->unlock();
   if (changed) emit FlightModeChanged(value);
}

quint8 FlightStatus::getFlightModeAssist() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeAssist;
}
void FlightStatus::setFlightModeAssist(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeAssist != value;
   data.FlightModeAssist = value;
   mutex->unlock();
   if (changed) emit FlightModeAssistChanged(value);
}

quint8 FlightStatus::getAssistedControlState() const
{
   QMutexLocker locker(mutex);
   return data.AssistedControlState;
}
void FlightStatus::setAssistedControlState(quint8 value)
{
   mutex->lock();
   bool changed = data.AssistedControlState != value;
   data.AssistedControlState = value;
   mutex->unlock();
   if (changed) emit AssistedControlStateChanged(value);
}

quint8 FlightStatus::getAssistedThrottleState() const
{
   QMutexLocker locker(mutex);
   return data.AssistedThrottleState;
}
void FlightStatus::setAssistedThrottleState(quint8 value)
{
   mutex->lock();
   bool changed = data.AssistedThrottleState != value;
   data.AssistedThrottleState = value;
   mutex->unlock();
   if (changed) emit AssistedThrottleStateChanged(value);
}

quint8 FlightStatus::getControlChain(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ControlChain[index];
}
void FlightStatus::setControlChain(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.ControlChain[index] != value;
   data.ControlChain[index] = value;
   mutex->unlock();
   if (changed) emit ControlChainChanged(index,value);
}

quint8 FlightStatus::getControlChain_Stabilization() const
{
   QMutexLocker locker(mutex);
   return data.ControlChain[0];
}
void FlightStatus::setControlChain_Stabilization(quint8 value)
{
   mutex->lock();
   bool changed = data.ControlChain[0] != value;
   data.ControlChain[0] = value;
   mutex->unlock();
   if (changed) emit ControlChain_StabilizationChanged(value);
}

quint8 FlightStatus::getControlChain_PathFollower() const
{
   QMutexLocker locker(mutex);
   return data.ControlChain[1];
}
void FlightStatus::setControlChain_PathFollower(quint8 value)
{
   mutex->lock();
   bool changed = data.ControlChain[1] != value;
   data.ControlChain[1] = value;
   mutex->unlock();
   if (changed) emit ControlChain_PathFollowerChanged(value);
}

quint8 FlightStatus::getControlChain_PathPlanner() const
{
   QMutexLocker locker(mutex);
   return data.ControlChain[2];
}
void FlightStatus::setControlChain_PathPlanner(quint8 value)
{
   mutex->lock();
   bool changed = data.ControlChain[2] != value;
   data.ControlChain[2] = value;
   mutex->unlock();
   if (changed) emit ControlChain_PathPlannerChanged(value);
}


