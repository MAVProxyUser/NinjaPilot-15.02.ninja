/**
 ******************************************************************************
 *
 * @file       pathstatus.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: pathstatus.xml.
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

#include "pathstatus.h"
#include "uavobjectfield.h"

const QString PathStatus::NAME = QString("PathStatus");
const QString PathStatus::DESCRIPTION = QString("Status of the current path mode  Can come from any @ref PathFollower module");
const QString PathStatus::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
PathStatus::PathStatus(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList fractional_progressElemNames;
    fractional_progressElemNames.append("0");
    fields.append( new UAVObjectField(QString("fractional_progress"), tr(""), QString(""), UAVObjectField::FLOAT32, fractional_progressElemNames, QStringList(), QString("")));
    QStringList errorElemNames;
    errorElemNames.append("0");
    fields.append( new UAVObjectField(QString("error"), tr(""), QString("m"), UAVObjectField::FLOAT32, errorElemNames, QStringList(), QString("")));
    QStringList path_direction_northElemNames;
    path_direction_northElemNames.append("0");
    fields.append( new UAVObjectField(QString("path_direction_north"), tr(""), QString("m"), UAVObjectField::FLOAT32, path_direction_northElemNames, QStringList(), QString("")));
    QStringList path_direction_eastElemNames;
    path_direction_eastElemNames.append("0");
    fields.append( new UAVObjectField(QString("path_direction_east"), tr(""), QString("m"), UAVObjectField::FLOAT32, path_direction_eastElemNames, QStringList(), QString("")));
    QStringList path_direction_downElemNames;
    path_direction_downElemNames.append("0");
    fields.append( new UAVObjectField(QString("path_direction_down"), tr(""), QString("m"), UAVObjectField::FLOAT32, path_direction_downElemNames, QStringList(), QString("")));
    QStringList correction_direction_northElemNames;
    correction_direction_northElemNames.append("0");
    fields.append( new UAVObjectField(QString("correction_direction_north"), tr(""), QString("m"), UAVObjectField::FLOAT32, correction_direction_northElemNames, QStringList(), QString("")));
    QStringList correction_direction_eastElemNames;
    correction_direction_eastElemNames.append("0");
    fields.append( new UAVObjectField(QString("correction_direction_east"), tr(""), QString("m"), UAVObjectField::FLOAT32, correction_direction_eastElemNames, QStringList(), QString("")));
    QStringList correction_direction_downElemNames;
    correction_direction_downElemNames.append("0");
    fields.append( new UAVObjectField(QString("correction_direction_down"), tr(""), QString("m"), UAVObjectField::FLOAT32, correction_direction_downElemNames, QStringList(), QString("")));
    QStringList path_timeElemNames;
    path_timeElemNames.append("0");
    fields.append( new UAVObjectField(QString("path_time"), tr(""), QString("s"), UAVObjectField::FLOAT32, path_timeElemNames, QStringList(), QString("")));
    QStringList UIDElemNames;
    UIDElemNames.append("0");
    fields.append( new UAVObjectField(QString("UID"), tr(""), QString(""), UAVObjectField::INT16, UIDElemNames, QStringList(), QString("")));
    QStringList StatusElemNames;
    StatusElemNames.append("0");
    QStringList StatusEnumOptions;
    StatusEnumOptions.append("InProgress");
    StatusEnumOptions.append("Completed");
    StatusEnumOptions.append("Warning");
    StatusEnumOptions.append("Critical");
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
UAVObject::Metadata PathStatus::getDefaultMetadata()
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
void PathStatus::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
PathStatus::DataFields PathStatus::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void PathStatus::setData(const DataFields& data)
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

void PathStatus::emitNotifications()
{
            //if (data.fractional_progress != oldData.fractional_progress)
            emit fractional_progressChanged(data.fractional_progress);
        //if (data.error != oldData.error)
            emit errorChanged(data.error);
        //if (data.path_direction_north != oldData.path_direction_north)
            emit path_direction_northChanged(data.path_direction_north);
        //if (data.path_direction_east != oldData.path_direction_east)
            emit path_direction_eastChanged(data.path_direction_east);
        //if (data.path_direction_down != oldData.path_direction_down)
            emit path_direction_downChanged(data.path_direction_down);
        //if (data.correction_direction_north != oldData.correction_direction_north)
            emit correction_direction_northChanged(data.correction_direction_north);
        //if (data.correction_direction_east != oldData.correction_direction_east)
            emit correction_direction_eastChanged(data.correction_direction_east);
        //if (data.correction_direction_down != oldData.correction_direction_down)
            emit correction_direction_downChanged(data.correction_direction_down);
        //if (data.path_time != oldData.path_time)
            emit path_timeChanged(data.path_time);
        //if (data.UID != oldData.UID)
            emit UIDChanged(data.UID);
        //if (data.Status != oldData.Status)
            emit StatusChanged(data.Status);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *PathStatus::clone(quint32 instID)
{
    PathStatus *obj = new PathStatus();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *PathStatus::dirtyClone()
{
    PathStatus *obj = new PathStatus();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
PathStatus *PathStatus::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<PathStatus *>(objMngr->getObject(PathStatus::OBJID, instID));
}

float PathStatus::getfractional_progress() const
{
   QMutexLocker locker(mutex);
   return data.fractional_progress;
}
void PathStatus::setfractional_progress(float value)
{
   mutex->lock();
   bool changed = data.fractional_progress != value;
   data.fractional_progress = value;
   mutex->unlock();
   if (changed) emit fractional_progressChanged(value);
}

float PathStatus::geterror() const
{
   QMutexLocker locker(mutex);
   return data.error;
}
void PathStatus::seterror(float value)
{
   mutex->lock();
   bool changed = data.error != value;
   data.error = value;
   mutex->unlock();
   if (changed) emit errorChanged(value);
}

float PathStatus::getpath_direction_north() const
{
   QMutexLocker locker(mutex);
   return data.path_direction_north;
}
void PathStatus::setpath_direction_north(float value)
{
   mutex->lock();
   bool changed = data.path_direction_north != value;
   data.path_direction_north = value;
   mutex->unlock();
   if (changed) emit path_direction_northChanged(value);
}

float PathStatus::getpath_direction_east() const
{
   QMutexLocker locker(mutex);
   return data.path_direction_east;
}
void PathStatus::setpath_direction_east(float value)
{
   mutex->lock();
   bool changed = data.path_direction_east != value;
   data.path_direction_east = value;
   mutex->unlock();
   if (changed) emit path_direction_eastChanged(value);
}

float PathStatus::getpath_direction_down() const
{
   QMutexLocker locker(mutex);
   return data.path_direction_down;
}
void PathStatus::setpath_direction_down(float value)
{
   mutex->lock();
   bool changed = data.path_direction_down != value;
   data.path_direction_down = value;
   mutex->unlock();
   if (changed) emit path_direction_downChanged(value);
}

float PathStatus::getcorrection_direction_north() const
{
   QMutexLocker locker(mutex);
   return data.correction_direction_north;
}
void PathStatus::setcorrection_direction_north(float value)
{
   mutex->lock();
   bool changed = data.correction_direction_north != value;
   data.correction_direction_north = value;
   mutex->unlock();
   if (changed) emit correction_direction_northChanged(value);
}

float PathStatus::getcorrection_direction_east() const
{
   QMutexLocker locker(mutex);
   return data.correction_direction_east;
}
void PathStatus::setcorrection_direction_east(float value)
{
   mutex->lock();
   bool changed = data.correction_direction_east != value;
   data.correction_direction_east = value;
   mutex->unlock();
   if (changed) emit correction_direction_eastChanged(value);
}

float PathStatus::getcorrection_direction_down() const
{
   QMutexLocker locker(mutex);
   return data.correction_direction_down;
}
void PathStatus::setcorrection_direction_down(float value)
{
   mutex->lock();
   bool changed = data.correction_direction_down != value;
   data.correction_direction_down = value;
   mutex->unlock();
   if (changed) emit correction_direction_downChanged(value);
}

float PathStatus::getpath_time() const
{
   QMutexLocker locker(mutex);
   return data.path_time;
}
void PathStatus::setpath_time(float value)
{
   mutex->lock();
   bool changed = data.path_time != value;
   data.path_time = value;
   mutex->unlock();
   if (changed) emit path_timeChanged(value);
}

qint16 PathStatus::getUID() const
{
   QMutexLocker locker(mutex);
   return data.UID;
}
void PathStatus::setUID(qint16 value)
{
   mutex->lock();
   bool changed = data.UID != value;
   data.UID = value;
   mutex->unlock();
   if (changed) emit UIDChanged(value);
}

quint8 PathStatus::getStatus() const
{
   QMutexLocker locker(mutex);
   return data.Status;
}
void PathStatus::setStatus(quint8 value)
{
   mutex->lock();
   bool changed = data.Status != value;
   data.Status = value;
   mutex->unlock();
   if (changed) emit StatusChanged(value);
}


