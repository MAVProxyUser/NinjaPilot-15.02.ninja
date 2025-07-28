/**
 ******************************************************************************
 *
 * @file       txpidsettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: txpidsettings.xml.
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

#include "txpidsettings.h"
#include "uavobjectfield.h"

const QString TxPIDSettings::NAME = QString("TxPIDSettings");
const QString TxPIDSettings::DESCRIPTION = QString("Settings used by @ref TxPID optional module to tune PID settings using R/C transmitter");
const QString TxPIDSettings::CATEGORY = QString("Control");

/**
 * Constructor
 */
TxPIDSettings::TxPIDSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList ThrottleRangeElemNames;
    ThrottleRangeElemNames.append("Min");
    ThrottleRangeElemNames.append("Max");
    fields.append( new UAVObjectField(QString("ThrottleRange"), tr(""), QString("%"), UAVObjectField::FLOAT32, ThrottleRangeElemNames, QStringList(), QString("")));
    QStringList MinPIDElemNames;
    MinPIDElemNames.append("Instance1");
    MinPIDElemNames.append("Instance2");
    MinPIDElemNames.append("Instance3");
    fields.append( new UAVObjectField(QString("MinPID"), tr(""), QString(""), UAVObjectField::FLOAT32, MinPIDElemNames, QStringList(), QString("")));
    QStringList MaxPIDElemNames;
    MaxPIDElemNames.append("Instance1");
    MaxPIDElemNames.append("Instance2");
    MaxPIDElemNames.append("Instance3");
    fields.append( new UAVObjectField(QString("MaxPID"), tr(""), QString(""), UAVObjectField::FLOAT32, MaxPIDElemNames, QStringList(), QString("")));
    QStringList UpdateModeElemNames;
    UpdateModeElemNames.append("0");
    QStringList UpdateModeEnumOptions;
    UpdateModeEnumOptions.append("Never");
    UpdateModeEnumOptions.append("When Armed");
    UpdateModeEnumOptions.append("Always");
    fields.append( new UAVObjectField(QString("UpdateMode"), tr(""), QString("option"), UAVObjectField::ENUM, UpdateModeElemNames, UpdateModeEnumOptions, QString("")));
    QStringList BankNumberElemNames;
    BankNumberElemNames.append("0");
    QStringList BankNumberEnumOptions;
    BankNumberEnumOptions.append("Bank1");
    BankNumberEnumOptions.append("Bank2");
    BankNumberEnumOptions.append("Bank3");
    fields.append( new UAVObjectField(QString("BankNumber"), tr(""), QString(""), UAVObjectField::ENUM, BankNumberElemNames, BankNumberEnumOptions, QString("")));
    QStringList InputsElemNames;
    InputsElemNames.append("Instance1");
    InputsElemNames.append("Instance2");
    InputsElemNames.append("Instance3");
    QStringList InputsEnumOptions;
    InputsEnumOptions.append("Throttle");
    InputsEnumOptions.append("Accessory0");
    InputsEnumOptions.append("Accessory1");
    InputsEnumOptions.append("Accessory2");
    InputsEnumOptions.append("Accessory3");
    InputsEnumOptions.append("Accessory4");
    InputsEnumOptions.append("Accessory5");
    fields.append( new UAVObjectField(QString("Inputs"), tr(""), QString("channel"), UAVObjectField::ENUM, InputsElemNames, InputsEnumOptions, QString("")));
    QStringList PIDsElemNames;
    PIDsElemNames.append("Instance1");
    PIDsElemNames.append("Instance2");
    PIDsElemNames.append("Instance3");
    QStringList PIDsEnumOptions;
    PIDsEnumOptions.append("Disabled");
    PIDsEnumOptions.append("Roll Rate.Kp");
    PIDsEnumOptions.append("Roll Rate.Ki");
    PIDsEnumOptions.append("Roll Rate.Kd");
    PIDsEnumOptions.append("Roll Rate.ILimit");
    PIDsEnumOptions.append("Roll Rate.Resp");
    PIDsEnumOptions.append("Pitch Rate.Kp");
    PIDsEnumOptions.append("Pitch Rate.Ki");
    PIDsEnumOptions.append("Pitch Rate.Kd");
    PIDsEnumOptions.append("Pitch Rate.ILimit");
    PIDsEnumOptions.append("Pitch Rate.Resp");
    PIDsEnumOptions.append("Roll+Pitch Rate.Kp");
    PIDsEnumOptions.append("Roll+Pitch Rate.Ki");
    PIDsEnumOptions.append("Roll+Pitch Rate.Kd");
    PIDsEnumOptions.append("Roll+Pitch Rate.ILimit");
    PIDsEnumOptions.append("Roll+Pitch Rate.Resp");
    PIDsEnumOptions.append("Yaw Rate.Kp");
    PIDsEnumOptions.append("Yaw Rate.Ki");
    PIDsEnumOptions.append("Yaw Rate.Kd");
    PIDsEnumOptions.append("Yaw Rate.ILimit");
    PIDsEnumOptions.append("Yaw Rate.Resp");
    PIDsEnumOptions.append("Roll Attitude.Kp");
    PIDsEnumOptions.append("Roll Attitude.Ki");
    PIDsEnumOptions.append("Roll Attitude.ILimit");
    PIDsEnumOptions.append("Roll Attitude.Resp");
    PIDsEnumOptions.append("Pitch Attitude.Kp");
    PIDsEnumOptions.append("Pitch Attitude.Ki");
    PIDsEnumOptions.append("Pitch Attitude.ILimit");
    PIDsEnumOptions.append("Pitch Attitude.Resp");
    PIDsEnumOptions.append("Roll+Pitch Attitude.Kp");
    PIDsEnumOptions.append("Roll+Pitch Attitude.Ki");
    PIDsEnumOptions.append("Roll+Pitch Attitude.ILimit");
    PIDsEnumOptions.append("Roll+Pitch Attitude.Resp");
    PIDsEnumOptions.append("Yaw Attitude.Kp");
    PIDsEnumOptions.append("Yaw Attitude.Ki");
    PIDsEnumOptions.append("Yaw Attitude.ILimit");
    PIDsEnumOptions.append("Yaw Attitude.Resp");
    PIDsEnumOptions.append("Roll.Expo");
    PIDsEnumOptions.append("Pitch.Expo");
    PIDsEnumOptions.append("Roll+Pitch.Expo");
    PIDsEnumOptions.append("Yaw.Expo");
    PIDsEnumOptions.append("GyroTau");
    PIDsEnumOptions.append("AcroPlusFactor");
    fields.append( new UAVObjectField(QString("PIDs"), tr(""), QString("option"), UAVObjectField::ENUM, PIDsElemNames, PIDsEnumOptions, QString("")));

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
UAVObject::Metadata TxPIDSettings::getDefaultMetadata()
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
void TxPIDSettings::setDefaultFieldValues()
{
    data.ThrottleRange[0] = 0.2;
    data.ThrottleRange[1] = 0.8;
    data.MinPID[0] = 0;
    data.MinPID[1] = 0;
    data.MinPID[2] = 0;
    data.MaxPID[0] = 0;
    data.MaxPID[1] = 0;
    data.MaxPID[2] = 0;
    data.UpdateMode = 1;
    data.BankNumber = 0;
    data.Inputs[0] = 0;
    data.Inputs[1] = 1;
    data.Inputs[2] = 2;
    data.PIDs[0] = 0;
    data.PIDs[1] = 0;
    data.PIDs[2] = 0;

}

/**
 * Get the object data fields
 */
TxPIDSettings::DataFields TxPIDSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void TxPIDSettings::setData(const DataFields& data)
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

void TxPIDSettings::emitNotifications()
{
            //if (data.ThrottleRange[0] != oldData.ThrottleRange[0])
            emit ThrottleRange_MinChanged(data.ThrottleRange[0]);
        //if (data.ThrottleRange[1] != oldData.ThrottleRange[1])
            emit ThrottleRange_MaxChanged(data.ThrottleRange[1]);
        //if (data.MinPID[0] != oldData.MinPID[0])
            emit MinPID_Instance1Changed(data.MinPID[0]);
        //if (data.MinPID[1] != oldData.MinPID[1])
            emit MinPID_Instance2Changed(data.MinPID[1]);
        //if (data.MinPID[2] != oldData.MinPID[2])
            emit MinPID_Instance3Changed(data.MinPID[2]);
        //if (data.MaxPID[0] != oldData.MaxPID[0])
            emit MaxPID_Instance1Changed(data.MaxPID[0]);
        //if (data.MaxPID[1] != oldData.MaxPID[1])
            emit MaxPID_Instance2Changed(data.MaxPID[1]);
        //if (data.MaxPID[2] != oldData.MaxPID[2])
            emit MaxPID_Instance3Changed(data.MaxPID[2]);
        //if (data.UpdateMode != oldData.UpdateMode)
            emit UpdateModeChanged(data.UpdateMode);
        //if (data.BankNumber != oldData.BankNumber)
            emit BankNumberChanged(data.BankNumber);
        //if (data.Inputs[0] != oldData.Inputs[0])
            emit Inputs_Instance1Changed(data.Inputs[0]);
        //if (data.Inputs[1] != oldData.Inputs[1])
            emit Inputs_Instance2Changed(data.Inputs[1]);
        //if (data.Inputs[2] != oldData.Inputs[2])
            emit Inputs_Instance3Changed(data.Inputs[2]);
        //if (data.PIDs[0] != oldData.PIDs[0])
            emit PIDs_Instance1Changed(data.PIDs[0]);
        //if (data.PIDs[1] != oldData.PIDs[1])
            emit PIDs_Instance2Changed(data.PIDs[1]);
        //if (data.PIDs[2] != oldData.PIDs[2])
            emit PIDs_Instance3Changed(data.PIDs[2]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *TxPIDSettings::clone(quint32 instID)
{
    TxPIDSettings *obj = new TxPIDSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *TxPIDSettings::dirtyClone()
{
    TxPIDSettings *obj = new TxPIDSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
TxPIDSettings *TxPIDSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<TxPIDSettings *>(objMngr->getObject(TxPIDSettings::OBJID, instID));
}

float TxPIDSettings::getThrottleRange(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ThrottleRange[index];
}
void TxPIDSettings::setThrottleRange(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ThrottleRange[index] != value;
   data.ThrottleRange[index] = value;
   mutex->unlock();
   if (changed) emit ThrottleRangeChanged(index,value);
}

float TxPIDSettings::getThrottleRange_Min() const
{
   QMutexLocker locker(mutex);
   return data.ThrottleRange[0];
}
void TxPIDSettings::setThrottleRange_Min(float value)
{
   mutex->lock();
   bool changed = data.ThrottleRange[0] != value;
   data.ThrottleRange[0] = value;
   mutex->unlock();
   if (changed) emit ThrottleRange_MinChanged(value);
}

float TxPIDSettings::getThrottleRange_Max() const
{
   QMutexLocker locker(mutex);
   return data.ThrottleRange[1];
}
void TxPIDSettings::setThrottleRange_Max(float value)
{
   mutex->lock();
   bool changed = data.ThrottleRange[1] != value;
   data.ThrottleRange[1] = value;
   mutex->unlock();
   if (changed) emit ThrottleRange_MaxChanged(value);
}

float TxPIDSettings::getMinPID(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.MinPID[index];
}
void TxPIDSettings::setMinPID(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.MinPID[index] != value;
   data.MinPID[index] = value;
   mutex->unlock();
   if (changed) emit MinPIDChanged(index,value);
}

float TxPIDSettings::getMinPID_Instance1() const
{
   QMutexLocker locker(mutex);
   return data.MinPID[0];
}
void TxPIDSettings::setMinPID_Instance1(float value)
{
   mutex->lock();
   bool changed = data.MinPID[0] != value;
   data.MinPID[0] = value;
   mutex->unlock();
   if (changed) emit MinPID_Instance1Changed(value);
}

float TxPIDSettings::getMinPID_Instance2() const
{
   QMutexLocker locker(mutex);
   return data.MinPID[1];
}
void TxPIDSettings::setMinPID_Instance2(float value)
{
   mutex->lock();
   bool changed = data.MinPID[1] != value;
   data.MinPID[1] = value;
   mutex->unlock();
   if (changed) emit MinPID_Instance2Changed(value);
}

float TxPIDSettings::getMinPID_Instance3() const
{
   QMutexLocker locker(mutex);
   return data.MinPID[2];
}
void TxPIDSettings::setMinPID_Instance3(float value)
{
   mutex->lock();
   bool changed = data.MinPID[2] != value;
   data.MinPID[2] = value;
   mutex->unlock();
   if (changed) emit MinPID_Instance3Changed(value);
}

float TxPIDSettings::getMaxPID(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.MaxPID[index];
}
void TxPIDSettings::setMaxPID(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.MaxPID[index] != value;
   data.MaxPID[index] = value;
   mutex->unlock();
   if (changed) emit MaxPIDChanged(index,value);
}

float TxPIDSettings::getMaxPID_Instance1() const
{
   QMutexLocker locker(mutex);
   return data.MaxPID[0];
}
void TxPIDSettings::setMaxPID_Instance1(float value)
{
   mutex->lock();
   bool changed = data.MaxPID[0] != value;
   data.MaxPID[0] = value;
   mutex->unlock();
   if (changed) emit MaxPID_Instance1Changed(value);
}

float TxPIDSettings::getMaxPID_Instance2() const
{
   QMutexLocker locker(mutex);
   return data.MaxPID[1];
}
void TxPIDSettings::setMaxPID_Instance2(float value)
{
   mutex->lock();
   bool changed = data.MaxPID[1] != value;
   data.MaxPID[1] = value;
   mutex->unlock();
   if (changed) emit MaxPID_Instance2Changed(value);
}

float TxPIDSettings::getMaxPID_Instance3() const
{
   QMutexLocker locker(mutex);
   return data.MaxPID[2];
}
void TxPIDSettings::setMaxPID_Instance3(float value)
{
   mutex->lock();
   bool changed = data.MaxPID[2] != value;
   data.MaxPID[2] = value;
   mutex->unlock();
   if (changed) emit MaxPID_Instance3Changed(value);
}

quint8 TxPIDSettings::getUpdateMode() const
{
   QMutexLocker locker(mutex);
   return data.UpdateMode;
}
void TxPIDSettings::setUpdateMode(quint8 value)
{
   mutex->lock();
   bool changed = data.UpdateMode != value;
   data.UpdateMode = value;
   mutex->unlock();
   if (changed) emit UpdateModeChanged(value);
}

quint8 TxPIDSettings::getBankNumber() const
{
   QMutexLocker locker(mutex);
   return data.BankNumber;
}
void TxPIDSettings::setBankNumber(quint8 value)
{
   mutex->lock();
   bool changed = data.BankNumber != value;
   data.BankNumber = value;
   mutex->unlock();
   if (changed) emit BankNumberChanged(value);
}

quint8 TxPIDSettings::getInputs(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Inputs[index];
}
void TxPIDSettings::setInputs(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.Inputs[index] != value;
   data.Inputs[index] = value;
   mutex->unlock();
   if (changed) emit InputsChanged(index,value);
}

quint8 TxPIDSettings::getInputs_Instance1() const
{
   QMutexLocker locker(mutex);
   return data.Inputs[0];
}
void TxPIDSettings::setInputs_Instance1(quint8 value)
{
   mutex->lock();
   bool changed = data.Inputs[0] != value;
   data.Inputs[0] = value;
   mutex->unlock();
   if (changed) emit Inputs_Instance1Changed(value);
}

quint8 TxPIDSettings::getInputs_Instance2() const
{
   QMutexLocker locker(mutex);
   return data.Inputs[1];
}
void TxPIDSettings::setInputs_Instance2(quint8 value)
{
   mutex->lock();
   bool changed = data.Inputs[1] != value;
   data.Inputs[1] = value;
   mutex->unlock();
   if (changed) emit Inputs_Instance2Changed(value);
}

quint8 TxPIDSettings::getInputs_Instance3() const
{
   QMutexLocker locker(mutex);
   return data.Inputs[2];
}
void TxPIDSettings::setInputs_Instance3(quint8 value)
{
   mutex->lock();
   bool changed = data.Inputs[2] != value;
   data.Inputs[2] = value;
   mutex->unlock();
   if (changed) emit Inputs_Instance3Changed(value);
}

quint8 TxPIDSettings::getPIDs(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.PIDs[index];
}
void TxPIDSettings::setPIDs(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.PIDs[index] != value;
   data.PIDs[index] = value;
   mutex->unlock();
   if (changed) emit PIDsChanged(index,value);
}

quint8 TxPIDSettings::getPIDs_Instance1() const
{
   QMutexLocker locker(mutex);
   return data.PIDs[0];
}
void TxPIDSettings::setPIDs_Instance1(quint8 value)
{
   mutex->lock();
   bool changed = data.PIDs[0] != value;
   data.PIDs[0] = value;
   mutex->unlock();
   if (changed) emit PIDs_Instance1Changed(value);
}

quint8 TxPIDSettings::getPIDs_Instance2() const
{
   QMutexLocker locker(mutex);
   return data.PIDs[1];
}
void TxPIDSettings::setPIDs_Instance2(quint8 value)
{
   mutex->lock();
   bool changed = data.PIDs[1] != value;
   data.PIDs[1] = value;
   mutex->unlock();
   if (changed) emit PIDs_Instance2Changed(value);
}

quint8 TxPIDSettings::getPIDs_Instance3() const
{
   QMutexLocker locker(mutex);
   return data.PIDs[2];
}
void TxPIDSettings::setPIDs_Instance3(quint8 value)
{
   mutex->lock();
   bool changed = data.PIDs[2] != value;
   data.PIDs[2] = value;
   mutex->unlock();
   if (changed) emit PIDs_Instance3Changed(value);
}


