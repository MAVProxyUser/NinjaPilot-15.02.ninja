/**
 ******************************************************************************
 *
 * @file       pathaction.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: pathaction.xml.
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

#include "pathaction.h"
#include "uavobjectfield.h"

const QString PathAction::NAME = QString("PathAction");
const QString PathAction::DESCRIPTION = QString("A waypoint command the pathplanner is to use at a certain waypoint");
const QString PathAction::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
PathAction::PathAction(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList ModeParametersElemNames;
    ModeParametersElemNames.append("0");
    ModeParametersElemNames.append("1");
    ModeParametersElemNames.append("2");
    ModeParametersElemNames.append("3");
    fields.append( new UAVObjectField(QString("ModeParameters"), tr(""), QString(""), UAVObjectField::FLOAT32, ModeParametersElemNames, QStringList(), QString("")));
    QStringList ConditionParametersElemNames;
    ConditionParametersElemNames.append("0");
    ConditionParametersElemNames.append("1");
    ConditionParametersElemNames.append("2");
    ConditionParametersElemNames.append("3");
    fields.append( new UAVObjectField(QString("ConditionParameters"), tr(""), QString(""), UAVObjectField::FLOAT32, ConditionParametersElemNames, QStringList(), QString("")));
    QStringList JumpDestinationElemNames;
    JumpDestinationElemNames.append("0");
    fields.append( new UAVObjectField(QString("JumpDestination"), tr(""), QString("waypoint"), UAVObjectField::INT16, JumpDestinationElemNames, QStringList(), QString("")));
    QStringList ErrorDestinationElemNames;
    ErrorDestinationElemNames.append("0");
    fields.append( new UAVObjectField(QString("ErrorDestination"), tr(""), QString("waypoint"), UAVObjectField::INT16, ErrorDestinationElemNames, QStringList(), QString("")));
    QStringList ModeElemNames;
    ModeElemNames.append("0");
    QStringList ModeEnumOptions;
    ModeEnumOptions.append("GoToEndpoint");
    ModeEnumOptions.append("FollowVector");
    ModeEnumOptions.append("CircleRight");
    ModeEnumOptions.append("CircleLeft");
    ModeEnumOptions.append("FixedAttitude");
    ModeEnumOptions.append("SetAccessory");
    ModeEnumOptions.append("DisarmAlarm");
    ModeEnumOptions.append("Land");
    ModeEnumOptions.append("Brake");
    ModeEnumOptions.append("Velocity");
    fields.append( new UAVObjectField(QString("Mode"), tr(""), QString(""), UAVObjectField::ENUM, ModeElemNames, ModeEnumOptions, QString("")));
    QStringList EndConditionElemNames;
    EndConditionElemNames.append("0");
    QStringList EndConditionEnumOptions;
    EndConditionEnumOptions.append("None");
    EndConditionEnumOptions.append("TimeOut");
    EndConditionEnumOptions.append("DistanceToTarget");
    EndConditionEnumOptions.append("LegRemaining");
    EndConditionEnumOptions.append("BelowError");
    EndConditionEnumOptions.append("AboveAltitude");
    EndConditionEnumOptions.append("AboveSpeed");
    EndConditionEnumOptions.append("PointingTowardsNext");
    EndConditionEnumOptions.append("PythonScript");
    EndConditionEnumOptions.append("Immediate");
    fields.append( new UAVObjectField(QString("EndCondition"), tr(""), QString(""), UAVObjectField::ENUM, EndConditionElemNames, EndConditionEnumOptions, QString("")));
    QStringList CommandElemNames;
    CommandElemNames.append("0");
    QStringList CommandEnumOptions;
    CommandEnumOptions.append("OnConditionNextWaypoint");
    CommandEnumOptions.append("OnNotConditionNextWaypoint");
    CommandEnumOptions.append("OnConditionJumpWaypoint");
    CommandEnumOptions.append("OnNotConditionJumpWaypoint");
    CommandEnumOptions.append("IfConditionJumpWaypointElseNextWaypoint");
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
UAVObject::Metadata PathAction::getDefaultMetadata()
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
void PathAction::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
PathAction::DataFields PathAction::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void PathAction::setData(const DataFields& data)
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

void PathAction::emitNotifications()
{
            //if (data.ModeParameters[0] != oldData.ModeParameters[0])
            emit ModeParameters_0Changed(data.ModeParameters[0]);
        //if (data.ModeParameters[1] != oldData.ModeParameters[1])
            emit ModeParameters_1Changed(data.ModeParameters[1]);
        //if (data.ModeParameters[2] != oldData.ModeParameters[2])
            emit ModeParameters_2Changed(data.ModeParameters[2]);
        //if (data.ModeParameters[3] != oldData.ModeParameters[3])
            emit ModeParameters_3Changed(data.ModeParameters[3]);
        //if (data.ConditionParameters[0] != oldData.ConditionParameters[0])
            emit ConditionParameters_0Changed(data.ConditionParameters[0]);
        //if (data.ConditionParameters[1] != oldData.ConditionParameters[1])
            emit ConditionParameters_1Changed(data.ConditionParameters[1]);
        //if (data.ConditionParameters[2] != oldData.ConditionParameters[2])
            emit ConditionParameters_2Changed(data.ConditionParameters[2]);
        //if (data.ConditionParameters[3] != oldData.ConditionParameters[3])
            emit ConditionParameters_3Changed(data.ConditionParameters[3]);
        //if (data.JumpDestination != oldData.JumpDestination)
            emit JumpDestinationChanged(data.JumpDestination);
        //if (data.ErrorDestination != oldData.ErrorDestination)
            emit ErrorDestinationChanged(data.ErrorDestination);
        //if (data.Mode != oldData.Mode)
            emit ModeChanged(data.Mode);
        //if (data.EndCondition != oldData.EndCondition)
            emit EndConditionChanged(data.EndCondition);
        //if (data.Command != oldData.Command)
            emit CommandChanged(data.Command);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *PathAction::clone(quint32 instID)
{
    PathAction *obj = new PathAction();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *PathAction::dirtyClone()
{
    PathAction *obj = new PathAction();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
PathAction *PathAction::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<PathAction *>(objMngr->getObject(PathAction::OBJID, instID));
}

float PathAction::getModeParameters(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ModeParameters[index];
}
void PathAction::setModeParameters(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ModeParameters[index] != value;
   data.ModeParameters[index] = value;
   mutex->unlock();
   if (changed) emit ModeParametersChanged(index,value);
}

float PathAction::getModeParameters_0() const
{
   QMutexLocker locker(mutex);
   return data.ModeParameters[0];
}
void PathAction::setModeParameters_0(float value)
{
   mutex->lock();
   bool changed = data.ModeParameters[0] != value;
   data.ModeParameters[0] = value;
   mutex->unlock();
   if (changed) emit ModeParameters_0Changed(value);
}

float PathAction::getModeParameters_1() const
{
   QMutexLocker locker(mutex);
   return data.ModeParameters[1];
}
void PathAction::setModeParameters_1(float value)
{
   mutex->lock();
   bool changed = data.ModeParameters[1] != value;
   data.ModeParameters[1] = value;
   mutex->unlock();
   if (changed) emit ModeParameters_1Changed(value);
}

float PathAction::getModeParameters_2() const
{
   QMutexLocker locker(mutex);
   return data.ModeParameters[2];
}
void PathAction::setModeParameters_2(float value)
{
   mutex->lock();
   bool changed = data.ModeParameters[2] != value;
   data.ModeParameters[2] = value;
   mutex->unlock();
   if (changed) emit ModeParameters_2Changed(value);
}

float PathAction::getModeParameters_3() const
{
   QMutexLocker locker(mutex);
   return data.ModeParameters[3];
}
void PathAction::setModeParameters_3(float value)
{
   mutex->lock();
   bool changed = data.ModeParameters[3] != value;
   data.ModeParameters[3] = value;
   mutex->unlock();
   if (changed) emit ModeParameters_3Changed(value);
}

float PathAction::getConditionParameters(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ConditionParameters[index];
}
void PathAction::setConditionParameters(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ConditionParameters[index] != value;
   data.ConditionParameters[index] = value;
   mutex->unlock();
   if (changed) emit ConditionParametersChanged(index,value);
}

float PathAction::getConditionParameters_0() const
{
   QMutexLocker locker(mutex);
   return data.ConditionParameters[0];
}
void PathAction::setConditionParameters_0(float value)
{
   mutex->lock();
   bool changed = data.ConditionParameters[0] != value;
   data.ConditionParameters[0] = value;
   mutex->unlock();
   if (changed) emit ConditionParameters_0Changed(value);
}

float PathAction::getConditionParameters_1() const
{
   QMutexLocker locker(mutex);
   return data.ConditionParameters[1];
}
void PathAction::setConditionParameters_1(float value)
{
   mutex->lock();
   bool changed = data.ConditionParameters[1] != value;
   data.ConditionParameters[1] = value;
   mutex->unlock();
   if (changed) emit ConditionParameters_1Changed(value);
}

float PathAction::getConditionParameters_2() const
{
   QMutexLocker locker(mutex);
   return data.ConditionParameters[2];
}
void PathAction::setConditionParameters_2(float value)
{
   mutex->lock();
   bool changed = data.ConditionParameters[2] != value;
   data.ConditionParameters[2] = value;
   mutex->unlock();
   if (changed) emit ConditionParameters_2Changed(value);
}

float PathAction::getConditionParameters_3() const
{
   QMutexLocker locker(mutex);
   return data.ConditionParameters[3];
}
void PathAction::setConditionParameters_3(float value)
{
   mutex->lock();
   bool changed = data.ConditionParameters[3] != value;
   data.ConditionParameters[3] = value;
   mutex->unlock();
   if (changed) emit ConditionParameters_3Changed(value);
}

qint16 PathAction::getJumpDestination() const
{
   QMutexLocker locker(mutex);
   return data.JumpDestination;
}
void PathAction::setJumpDestination(qint16 value)
{
   mutex->lock();
   bool changed = data.JumpDestination != value;
   data.JumpDestination = value;
   mutex->unlock();
   if (changed) emit JumpDestinationChanged(value);
}

qint16 PathAction::getErrorDestination() const
{
   QMutexLocker locker(mutex);
   return data.ErrorDestination;
}
void PathAction::setErrorDestination(qint16 value)
{
   mutex->lock();
   bool changed = data.ErrorDestination != value;
   data.ErrorDestination = value;
   mutex->unlock();
   if (changed) emit ErrorDestinationChanged(value);
}

quint8 PathAction::getMode() const
{
   QMutexLocker locker(mutex);
   return data.Mode;
}
void PathAction::setMode(quint8 value)
{
   mutex->lock();
   bool changed = data.Mode != value;
   data.Mode = value;
   mutex->unlock();
   if (changed) emit ModeChanged(value);
}

quint8 PathAction::getEndCondition() const
{
   QMutexLocker locker(mutex);
   return data.EndCondition;
}
void PathAction::setEndCondition(quint8 value)
{
   mutex->lock();
   bool changed = data.EndCondition != value;
   data.EndCondition = value;
   mutex->unlock();
   if (changed) emit EndConditionChanged(value);
}

quint8 PathAction::getCommand() const
{
   QMutexLocker locker(mutex);
   return data.Command;
}
void PathAction::setCommand(quint8 value)
{
   mutex->lock();
   bool changed = data.Command != value;
   data.Command = value;
   mutex->unlock();
   if (changed) emit CommandChanged(value);
}


