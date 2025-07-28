/**
 ******************************************************************************
 *
 * @file       flightplanstatus.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: flightplanstatus.xml.
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

#include "flightplanstatus.h"
#include "uavobjectfield.h"

const QString FlightPlanStatus::NAME = QString("FlightPlanStatus");
const QString FlightPlanStatus::DESCRIPTION = QString("Status of the flight plan script");
const QString FlightPlanStatus::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
FlightPlanStatus::FlightPlanStatus(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList ErrorFileIDElemNames;
    ErrorFileIDElemNames.append("0");
    fields.append( new UAVObjectField(QString("ErrorFileID"), tr(""), QString(""), UAVObjectField::UINT32, ErrorFileIDElemNames, QStringList(), QString("")));
    QStringList ErrorLineNumElemNames;
    ErrorLineNumElemNames.append("0");
    fields.append( new UAVObjectField(QString("ErrorLineNum"), tr(""), QString(""), UAVObjectField::UINT32, ErrorLineNumElemNames, QStringList(), QString("")));
    QStringList DebugElemNames;
    DebugElemNames.append("0");
    DebugElemNames.append("1");
    fields.append( new UAVObjectField(QString("Debug"), tr(""), QString(""), UAVObjectField::FLOAT32, DebugElemNames, QStringList(), QString("")));
    QStringList StatusElemNames;
    StatusElemNames.append("0");
    QStringList StatusEnumOptions;
    StatusEnumOptions.append("Stopped");
    StatusEnumOptions.append("Running");
    StatusEnumOptions.append("Error");
    fields.append( new UAVObjectField(QString("Status"), tr(""), QString(""), UAVObjectField::ENUM, StatusElemNames, StatusEnumOptions, QString("")));
    QStringList ErrorTypeElemNames;
    ErrorTypeElemNames.append("0");
    QStringList ErrorTypeEnumOptions;
    ErrorTypeEnumOptions.append("None");
    ErrorTypeEnumOptions.append("VMInitError");
    ErrorTypeEnumOptions.append("Exception");
    ErrorTypeEnumOptions.append("IOError");
    ErrorTypeEnumOptions.append("DivByZero");
    ErrorTypeEnumOptions.append("AssertError");
    ErrorTypeEnumOptions.append("AttributeError");
    ErrorTypeEnumOptions.append("ImportError");
    ErrorTypeEnumOptions.append("IndexError");
    ErrorTypeEnumOptions.append("KeyError");
    ErrorTypeEnumOptions.append("MemoryError");
    ErrorTypeEnumOptions.append("NameError");
    ErrorTypeEnumOptions.append("SyntaxError");
    ErrorTypeEnumOptions.append("SystemError");
    ErrorTypeEnumOptions.append("TypeError");
    ErrorTypeEnumOptions.append("ValueError");
    ErrorTypeEnumOptions.append("StopIteration");
    ErrorTypeEnumOptions.append("Warning");
    ErrorTypeEnumOptions.append("UnknownError");
    fields.append( new UAVObjectField(QString("ErrorType"), tr(""), QString(""), UAVObjectField::ENUM, ErrorTypeElemNames, ErrorTypeEnumOptions, QString("")));

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
UAVObject::Metadata FlightPlanStatus::getDefaultMetadata()
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
    metadata.flightTelemetryUpdatePeriod = 2000;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void FlightPlanStatus::setDefaultFieldValues()
{
    data.Debug[0] = 0;
    data.Debug[1] = 0;
    data.Status = 0;
    data.ErrorType = 0;

}

/**
 * Get the object data fields
 */
FlightPlanStatus::DataFields FlightPlanStatus::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void FlightPlanStatus::setData(const DataFields& data)
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

void FlightPlanStatus::emitNotifications()
{
            //if (data.ErrorFileID != oldData.ErrorFileID)
            emit ErrorFileIDChanged(data.ErrorFileID);
        //if (data.ErrorLineNum != oldData.ErrorLineNum)
            emit ErrorLineNumChanged(data.ErrorLineNum);
        //if (data.Debug[0] != oldData.Debug[0])
            emit Debug_0Changed(data.Debug[0]);
        //if (data.Debug[1] != oldData.Debug[1])
            emit Debug_1Changed(data.Debug[1]);
        //if (data.Status != oldData.Status)
            emit StatusChanged(data.Status);
        //if (data.ErrorType != oldData.ErrorType)
            emit ErrorTypeChanged(data.ErrorType);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *FlightPlanStatus::clone(quint32 instID)
{
    FlightPlanStatus *obj = new FlightPlanStatus();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *FlightPlanStatus::dirtyClone()
{
    FlightPlanStatus *obj = new FlightPlanStatus();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
FlightPlanStatus *FlightPlanStatus::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<FlightPlanStatus *>(objMngr->getObject(FlightPlanStatus::OBJID, instID));
}

quint32 FlightPlanStatus::getErrorFileID() const
{
   QMutexLocker locker(mutex);
   return data.ErrorFileID;
}
void FlightPlanStatus::setErrorFileID(quint32 value)
{
   mutex->lock();
   bool changed = data.ErrorFileID != value;
   data.ErrorFileID = value;
   mutex->unlock();
   if (changed) emit ErrorFileIDChanged(value);
}

quint32 FlightPlanStatus::getErrorLineNum() const
{
   QMutexLocker locker(mutex);
   return data.ErrorLineNum;
}
void FlightPlanStatus::setErrorLineNum(quint32 value)
{
   mutex->lock();
   bool changed = data.ErrorLineNum != value;
   data.ErrorLineNum = value;
   mutex->unlock();
   if (changed) emit ErrorLineNumChanged(value);
}

float FlightPlanStatus::getDebug(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Debug[index];
}
void FlightPlanStatus::setDebug(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.Debug[index] != value;
   data.Debug[index] = value;
   mutex->unlock();
   if (changed) emit DebugChanged(index,value);
}

float FlightPlanStatus::getDebug_0() const
{
   QMutexLocker locker(mutex);
   return data.Debug[0];
}
void FlightPlanStatus::setDebug_0(float value)
{
   mutex->lock();
   bool changed = data.Debug[0] != value;
   data.Debug[0] = value;
   mutex->unlock();
   if (changed) emit Debug_0Changed(value);
}

float FlightPlanStatus::getDebug_1() const
{
   QMutexLocker locker(mutex);
   return data.Debug[1];
}
void FlightPlanStatus::setDebug_1(float value)
{
   mutex->lock();
   bool changed = data.Debug[1] != value;
   data.Debug[1] = value;
   mutex->unlock();
   if (changed) emit Debug_1Changed(value);
}

quint8 FlightPlanStatus::getStatus() const
{
   QMutexLocker locker(mutex);
   return data.Status;
}
void FlightPlanStatus::setStatus(quint8 value)
{
   mutex->lock();
   bool changed = data.Status != value;
   data.Status = value;
   mutex->unlock();
   if (changed) emit StatusChanged(value);
}

quint8 FlightPlanStatus::getErrorType() const
{
   QMutexLocker locker(mutex);
   return data.ErrorType;
}
void FlightPlanStatus::setErrorType(quint8 value)
{
   mutex->lock();
   bool changed = data.ErrorType != value;
   data.ErrorType = value;
   mutex->unlock();
   if (changed) emit ErrorTypeChanged(value);
}


