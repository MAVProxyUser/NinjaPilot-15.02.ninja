/**
 ******************************************************************************
 *
 * @file       pathdesired.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: pathdesired.xml.
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

#include "pathdesired.h"
#include "uavobjectfield.h"

const QString PathDesired::NAME = QString("PathDesired");
const QString PathDesired::DESCRIPTION = QString("The endpoint or path the craft is trying to achieve.  Can come from @ref ManualControl or @ref PathPlanner ");
const QString PathDesired::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
PathDesired::PathDesired(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList StartElemNames;
    StartElemNames.append("North");
    StartElemNames.append("East");
    StartElemNames.append("Down");
    fields.append( new UAVObjectField(QString("Start"), tr(""), QString("m"), UAVObjectField::FLOAT32, StartElemNames, QStringList(), QString("")));
    QStringList EndElemNames;
    EndElemNames.append("North");
    EndElemNames.append("East");
    EndElemNames.append("Down");
    fields.append( new UAVObjectField(QString("End"), tr(""), QString("m"), UAVObjectField::FLOAT32, EndElemNames, QStringList(), QString("")));
    QStringList StartingVelocityElemNames;
    StartingVelocityElemNames.append("0");
    fields.append( new UAVObjectField(QString("StartingVelocity"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, StartingVelocityElemNames, QStringList(), QString("")));
    QStringList EndingVelocityElemNames;
    EndingVelocityElemNames.append("0");
    fields.append( new UAVObjectField(QString("EndingVelocity"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, EndingVelocityElemNames, QStringList(), QString("")));
    QStringList ModeParametersElemNames;
    ModeParametersElemNames.append("0");
    ModeParametersElemNames.append("1");
    ModeParametersElemNames.append("2");
    ModeParametersElemNames.append("3");
    fields.append( new UAVObjectField(QString("ModeParameters"), tr(""), QString(""), UAVObjectField::FLOAT32, ModeParametersElemNames, QStringList(), QString("")));
    QStringList UIDElemNames;
    UIDElemNames.append("0");
    fields.append( new UAVObjectField(QString("UID"), tr(""), QString(""), UAVObjectField::INT16, UIDElemNames, QStringList(), QString("")));
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
UAVObject::Metadata PathDesired::getDefaultMetadata()
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
void PathDesired::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
PathDesired::DataFields PathDesired::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void PathDesired::setData(const DataFields& data)
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

void PathDesired::emitNotifications()
{
            //if (data.Start[0] != oldData.Start[0])
            emit Start_NorthChanged(data.Start[0]);
        //if (data.Start[1] != oldData.Start[1])
            emit Start_EastChanged(data.Start[1]);
        //if (data.Start[2] != oldData.Start[2])
            emit Start_DownChanged(data.Start[2]);
        //if (data.End[0] != oldData.End[0])
            emit End_NorthChanged(data.End[0]);
        //if (data.End[1] != oldData.End[1])
            emit End_EastChanged(data.End[1]);
        //if (data.End[2] != oldData.End[2])
            emit End_DownChanged(data.End[2]);
        //if (data.StartingVelocity != oldData.StartingVelocity)
            emit StartingVelocityChanged(data.StartingVelocity);
        //if (data.EndingVelocity != oldData.EndingVelocity)
            emit EndingVelocityChanged(data.EndingVelocity);
        //if (data.ModeParameters[0] != oldData.ModeParameters[0])
            emit ModeParameters_0Changed(data.ModeParameters[0]);
        //if (data.ModeParameters[1] != oldData.ModeParameters[1])
            emit ModeParameters_1Changed(data.ModeParameters[1]);
        //if (data.ModeParameters[2] != oldData.ModeParameters[2])
            emit ModeParameters_2Changed(data.ModeParameters[2]);
        //if (data.ModeParameters[3] != oldData.ModeParameters[3])
            emit ModeParameters_3Changed(data.ModeParameters[3]);
        //if (data.UID != oldData.UID)
            emit UIDChanged(data.UID);
        //if (data.Mode != oldData.Mode)
            emit ModeChanged(data.Mode);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *PathDesired::clone(quint32 instID)
{
    PathDesired *obj = new PathDesired();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *PathDesired::dirtyClone()
{
    PathDesired *obj = new PathDesired();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
PathDesired *PathDesired::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<PathDesired *>(objMngr->getObject(PathDesired::OBJID, instID));
}

float PathDesired::getStart(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Start[index];
}
void PathDesired::setStart(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.Start[index] != value;
   data.Start[index] = value;
   mutex->unlock();
   if (changed) emit StartChanged(index,value);
}

float PathDesired::getStart_North() const
{
   QMutexLocker locker(mutex);
   return data.Start[0];
}
void PathDesired::setStart_North(float value)
{
   mutex->lock();
   bool changed = data.Start[0] != value;
   data.Start[0] = value;
   mutex->unlock();
   if (changed) emit Start_NorthChanged(value);
}

float PathDesired::getStart_East() const
{
   QMutexLocker locker(mutex);
   return data.Start[1];
}
void PathDesired::setStart_East(float value)
{
   mutex->lock();
   bool changed = data.Start[1] != value;
   data.Start[1] = value;
   mutex->unlock();
   if (changed) emit Start_EastChanged(value);
}

float PathDesired::getStart_Down() const
{
   QMutexLocker locker(mutex);
   return data.Start[2];
}
void PathDesired::setStart_Down(float value)
{
   mutex->lock();
   bool changed = data.Start[2] != value;
   data.Start[2] = value;
   mutex->unlock();
   if (changed) emit Start_DownChanged(value);
}

float PathDesired::getEnd(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.End[index];
}
void PathDesired::setEnd(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.End[index] != value;
   data.End[index] = value;
   mutex->unlock();
   if (changed) emit EndChanged(index,value);
}

float PathDesired::getEnd_North() const
{
   QMutexLocker locker(mutex);
   return data.End[0];
}
void PathDesired::setEnd_North(float value)
{
   mutex->lock();
   bool changed = data.End[0] != value;
   data.End[0] = value;
   mutex->unlock();
   if (changed) emit End_NorthChanged(value);
}

float PathDesired::getEnd_East() const
{
   QMutexLocker locker(mutex);
   return data.End[1];
}
void PathDesired::setEnd_East(float value)
{
   mutex->lock();
   bool changed = data.End[1] != value;
   data.End[1] = value;
   mutex->unlock();
   if (changed) emit End_EastChanged(value);
}

float PathDesired::getEnd_Down() const
{
   QMutexLocker locker(mutex);
   return data.End[2];
}
void PathDesired::setEnd_Down(float value)
{
   mutex->lock();
   bool changed = data.End[2] != value;
   data.End[2] = value;
   mutex->unlock();
   if (changed) emit End_DownChanged(value);
}

float PathDesired::getStartingVelocity() const
{
   QMutexLocker locker(mutex);
   return data.StartingVelocity;
}
void PathDesired::setStartingVelocity(float value)
{
   mutex->lock();
   bool changed = data.StartingVelocity != value;
   data.StartingVelocity = value;
   mutex->unlock();
   if (changed) emit StartingVelocityChanged(value);
}

float PathDesired::getEndingVelocity() const
{
   QMutexLocker locker(mutex);
   return data.EndingVelocity;
}
void PathDesired::setEndingVelocity(float value)
{
   mutex->lock();
   bool changed = data.EndingVelocity != value;
   data.EndingVelocity = value;
   mutex->unlock();
   if (changed) emit EndingVelocityChanged(value);
}

float PathDesired::getModeParameters(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ModeParameters[index];
}
void PathDesired::setModeParameters(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ModeParameters[index] != value;
   data.ModeParameters[index] = value;
   mutex->unlock();
   if (changed) emit ModeParametersChanged(index,value);
}

float PathDesired::getModeParameters_0() const
{
   QMutexLocker locker(mutex);
   return data.ModeParameters[0];
}
void PathDesired::setModeParameters_0(float value)
{
   mutex->lock();
   bool changed = data.ModeParameters[0] != value;
   data.ModeParameters[0] = value;
   mutex->unlock();
   if (changed) emit ModeParameters_0Changed(value);
}

float PathDesired::getModeParameters_1() const
{
   QMutexLocker locker(mutex);
   return data.ModeParameters[1];
}
void PathDesired::setModeParameters_1(float value)
{
   mutex->lock();
   bool changed = data.ModeParameters[1] != value;
   data.ModeParameters[1] = value;
   mutex->unlock();
   if (changed) emit ModeParameters_1Changed(value);
}

float PathDesired::getModeParameters_2() const
{
   QMutexLocker locker(mutex);
   return data.ModeParameters[2];
}
void PathDesired::setModeParameters_2(float value)
{
   mutex->lock();
   bool changed = data.ModeParameters[2] != value;
   data.ModeParameters[2] = value;
   mutex->unlock();
   if (changed) emit ModeParameters_2Changed(value);
}

float PathDesired::getModeParameters_3() const
{
   QMutexLocker locker(mutex);
   return data.ModeParameters[3];
}
void PathDesired::setModeParameters_3(float value)
{
   mutex->lock();
   bool changed = data.ModeParameters[3] != value;
   data.ModeParameters[3] = value;
   mutex->unlock();
   if (changed) emit ModeParameters_3Changed(value);
}

qint16 PathDesired::getUID() const
{
   QMutexLocker locker(mutex);
   return data.UID;
}
void PathDesired::setUID(qint16 value)
{
   mutex->lock();
   bool changed = data.UID != value;
   data.UID = value;
   mutex->unlock();
   if (changed) emit UIDChanged(value);
}

quint8 PathDesired::getMode() const
{
   QMutexLocker locker(mutex);
   return data.Mode;
}
void PathDesired::setMode(quint8 value)
{
   mutex->lock();
   bool changed = data.Mode != value;
   data.Mode = value;
   mutex->unlock();
   if (changed) emit ModeChanged(value);
}


