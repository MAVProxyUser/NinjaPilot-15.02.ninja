/**
 ******************************************************************************
 *
 * @file       pidstatus.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: pidstatus.xml.
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

#include "pidstatus.h"
#include "uavobjectfield.h"

const QString PIDStatus::NAME = QString("PIDStatus");
const QString PIDStatus::DESCRIPTION = QString("Status of a PID loop for debugging");
const QString PIDStatus::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
PIDStatus::PIDStatus(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList setpointElemNames;
    setpointElemNames.append("0");
    fields.append( new UAVObjectField(QString("setpoint"), tr(""), QString("m"), UAVObjectField::FLOAT32, setpointElemNames, QStringList(), QString("")));
    QStringList actualElemNames;
    actualElemNames.append("0");
    fields.append( new UAVObjectField(QString("actual"), tr(""), QString("m"), UAVObjectField::FLOAT32, actualElemNames, QStringList(), QString("")));
    QStringList errorElemNames;
    errorElemNames.append("0");
    fields.append( new UAVObjectField(QString("error"), tr(""), QString("m"), UAVObjectField::FLOAT32, errorElemNames, QStringList(), QString("")));
    QStringList ulowElemNames;
    ulowElemNames.append("0");
    fields.append( new UAVObjectField(QString("ulow"), tr(""), QString("m"), UAVObjectField::FLOAT32, ulowElemNames, QStringList(), QString("")));
    QStringList uhighElemNames;
    uhighElemNames.append("0");
    fields.append( new UAVObjectField(QString("uhigh"), tr(""), QString("m"), UAVObjectField::FLOAT32, uhighElemNames, QStringList(), QString("")));
    QStringList commandElemNames;
    commandElemNames.append("0");
    fields.append( new UAVObjectField(QString("command"), tr(""), QString("m"), UAVObjectField::FLOAT32, commandElemNames, QStringList(), QString("")));
    QStringList PElemNames;
    PElemNames.append("0");
    fields.append( new UAVObjectField(QString("P"), tr(""), QString("m"), UAVObjectField::FLOAT32, PElemNames, QStringList(), QString("")));
    QStringList IElemNames;
    IElemNames.append("0");
    fields.append( new UAVObjectField(QString("I"), tr(""), QString("m"), UAVObjectField::FLOAT32, IElemNames, QStringList(), QString("")));
    QStringList DElemNames;
    DElemNames.append("0");
    fields.append( new UAVObjectField(QString("D"), tr(""), QString("m"), UAVObjectField::FLOAT32, DElemNames, QStringList(), QString("")));

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
UAVObject::Metadata PIDStatus::getDefaultMetadata()
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
void PIDStatus::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
PIDStatus::DataFields PIDStatus::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void PIDStatus::setData(const DataFields& data)
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

void PIDStatus::emitNotifications()
{
            //if (data.setpoint != oldData.setpoint)
            emit setpointChanged(data.setpoint);
        //if (data.actual != oldData.actual)
            emit actualChanged(data.actual);
        //if (data.error != oldData.error)
            emit errorChanged(data.error);
        //if (data.ulow != oldData.ulow)
            emit ulowChanged(data.ulow);
        //if (data.uhigh != oldData.uhigh)
            emit uhighChanged(data.uhigh);
        //if (data.command != oldData.command)
            emit commandChanged(data.command);
        //if (data.P != oldData.P)
            emit PChanged(data.P);
        //if (data.I != oldData.I)
            emit IChanged(data.I);
        //if (data.D != oldData.D)
            emit DChanged(data.D);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *PIDStatus::clone(quint32 instID)
{
    PIDStatus *obj = new PIDStatus();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *PIDStatus::dirtyClone()
{
    PIDStatus *obj = new PIDStatus();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
PIDStatus *PIDStatus::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<PIDStatus *>(objMngr->getObject(PIDStatus::OBJID, instID));
}

float PIDStatus::getsetpoint() const
{
   QMutexLocker locker(mutex);
   return data.setpoint;
}
void PIDStatus::setsetpoint(float value)
{
   mutex->lock();
   bool changed = data.setpoint != value;
   data.setpoint = value;
   mutex->unlock();
   if (changed) emit setpointChanged(value);
}

float PIDStatus::getactual() const
{
   QMutexLocker locker(mutex);
   return data.actual;
}
void PIDStatus::setactual(float value)
{
   mutex->lock();
   bool changed = data.actual != value;
   data.actual = value;
   mutex->unlock();
   if (changed) emit actualChanged(value);
}

float PIDStatus::geterror() const
{
   QMutexLocker locker(mutex);
   return data.error;
}
void PIDStatus::seterror(float value)
{
   mutex->lock();
   bool changed = data.error != value;
   data.error = value;
   mutex->unlock();
   if (changed) emit errorChanged(value);
}

float PIDStatus::getulow() const
{
   QMutexLocker locker(mutex);
   return data.ulow;
}
void PIDStatus::setulow(float value)
{
   mutex->lock();
   bool changed = data.ulow != value;
   data.ulow = value;
   mutex->unlock();
   if (changed) emit ulowChanged(value);
}

float PIDStatus::getuhigh() const
{
   QMutexLocker locker(mutex);
   return data.uhigh;
}
void PIDStatus::setuhigh(float value)
{
   mutex->lock();
   bool changed = data.uhigh != value;
   data.uhigh = value;
   mutex->unlock();
   if (changed) emit uhighChanged(value);
}

float PIDStatus::getcommand() const
{
   QMutexLocker locker(mutex);
   return data.command;
}
void PIDStatus::setcommand(float value)
{
   mutex->lock();
   bool changed = data.command != value;
   data.command = value;
   mutex->unlock();
   if (changed) emit commandChanged(value);
}

float PIDStatus::getP() const
{
   QMutexLocker locker(mutex);
   return data.P;
}
void PIDStatus::setP(float value)
{
   mutex->lock();
   bool changed = data.P != value;
   data.P = value;
   mutex->unlock();
   if (changed) emit PChanged(value);
}

float PIDStatus::getI() const
{
   QMutexLocker locker(mutex);
   return data.I;
}
void PIDStatus::setI(float value)
{
   mutex->lock();
   bool changed = data.I != value;
   data.I = value;
   mutex->unlock();
   if (changed) emit IChanged(value);
}

float PIDStatus::getD() const
{
   QMutexLocker locker(mutex);
   return data.D;
}
void PIDStatus::setD(float value)
{
   mutex->lock();
   bool changed = data.D != value;
   data.D = value;
   mutex->unlock();
   if (changed) emit DChanged(value);
}


