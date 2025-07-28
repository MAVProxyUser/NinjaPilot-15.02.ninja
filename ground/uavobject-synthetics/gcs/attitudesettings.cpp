/**
 ******************************************************************************
 *
 * @file       attitudesettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: attitudesettings.xml.
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

#include "attitudesettings.h"
#include "uavobjectfield.h"

const QString AttitudeSettings::NAME = QString("AttitudeSettings");
const QString AttitudeSettings::DESCRIPTION = QString("Settings for the @ref Attitude module used on CopterControl");
const QString AttitudeSettings::CATEGORY = QString("State");

/**
 * Constructor
 */
AttitudeSettings::AttitudeSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList BoardRotationElemNames;
    BoardRotationElemNames.append("Roll");
    BoardRotationElemNames.append("Pitch");
    BoardRotationElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("BoardRotation"), tr(""), QString("deg"), UAVObjectField::FLOAT32, BoardRotationElemNames, QStringList(), QString("")));
    QStringList BoardLevelTrimElemNames;
    BoardLevelTrimElemNames.append("Roll");
    BoardLevelTrimElemNames.append("Pitch");
    fields.append( new UAVObjectField(QString("BoardLevelTrim"), tr(""), QString("deg"), UAVObjectField::FLOAT32, BoardLevelTrimElemNames, QStringList(), QString("")));
    QStringList AccelKpElemNames;
    AccelKpElemNames.append("0");
    fields.append( new UAVObjectField(QString("AccelKp"), tr(""), QString("channel"), UAVObjectField::FLOAT32, AccelKpElemNames, QStringList(), QString("")));
    QStringList AccelKiElemNames;
    AccelKiElemNames.append("0");
    fields.append( new UAVObjectField(QString("AccelKi"), tr(""), QString("channel"), UAVObjectField::FLOAT32, AccelKiElemNames, QStringList(), QString("")));
    QStringList MagKiElemNames;
    MagKiElemNames.append("0");
    fields.append( new UAVObjectField(QString("MagKi"), tr(""), QString(""), UAVObjectField::FLOAT32, MagKiElemNames, QStringList(), QString("")));
    QStringList MagKpElemNames;
    MagKpElemNames.append("0");
    fields.append( new UAVObjectField(QString("MagKp"), tr(""), QString(""), UAVObjectField::FLOAT32, MagKpElemNames, QStringList(), QString("")));
    QStringList AccelTauElemNames;
    AccelTauElemNames.append("0");
    fields.append( new UAVObjectField(QString("AccelTau"), tr(""), QString(""), UAVObjectField::FLOAT32, AccelTauElemNames, QStringList(), QString("")));
    QStringList YawBiasRateElemNames;
    YawBiasRateElemNames.append("0");
    fields.append( new UAVObjectField(QString("YawBiasRate"), tr(""), QString("channel"), UAVObjectField::FLOAT32, YawBiasRateElemNames, QStringList(), QString("")));
    QStringList ZeroDuringArmingElemNames;
    ZeroDuringArmingElemNames.append("0");
    QStringList ZeroDuringArmingEnumOptions;
    ZeroDuringArmingEnumOptions.append("FALSE");
    ZeroDuringArmingEnumOptions.append("TRUE");
    fields.append( new UAVObjectField(QString("ZeroDuringArming"), tr(""), QString("channel"), UAVObjectField::ENUM, ZeroDuringArmingElemNames, ZeroDuringArmingEnumOptions, QString("")));
    QStringList BiasCorrectGyroElemNames;
    BiasCorrectGyroElemNames.append("0");
    QStringList BiasCorrectGyroEnumOptions;
    BiasCorrectGyroEnumOptions.append("FALSE");
    BiasCorrectGyroEnumOptions.append("TRUE");
    fields.append( new UAVObjectField(QString("BiasCorrectGyro"), tr(""), QString("channel"), UAVObjectField::ENUM, BiasCorrectGyroElemNames, BiasCorrectGyroEnumOptions, QString("")));
    QStringList TrimFlightElemNames;
    TrimFlightElemNames.append("0");
    QStringList TrimFlightEnumOptions;
    TrimFlightEnumOptions.append("NORMAL");
    TrimFlightEnumOptions.append("START");
    TrimFlightEnumOptions.append("LOAD");
    fields.append( new UAVObjectField(QString("TrimFlight"), tr(""), QString("channel"), UAVObjectField::ENUM, TrimFlightElemNames, TrimFlightEnumOptions, QString("")));

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
UAVObject::Metadata AttitudeSettings::getDefaultMetadata()
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
void AttitudeSettings::setDefaultFieldValues()
{
    data.BoardRotation[0] = 0;
    data.BoardRotation[1] = 0;
    data.BoardRotation[2] = 0;
    data.BoardLevelTrim[0] = 0;
    data.BoardLevelTrim[1] = 0;
    data.AccelKp = 0.05;
    data.AccelKi = 0.0001;
    data.MagKi = 1e-06;
    data.MagKp = 0.01;
    data.AccelTau = 0;
    data.YawBiasRate = 1e-06;
    data.ZeroDuringArming = 1;
    data.BiasCorrectGyro = 1;
    data.TrimFlight = 0;

}

/**
 * Get the object data fields
 */
AttitudeSettings::DataFields AttitudeSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void AttitudeSettings::setData(const DataFields& data)
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

void AttitudeSettings::emitNotifications()
{
            //if (data.BoardRotation[0] != oldData.BoardRotation[0])
            emit BoardRotation_RollChanged(data.BoardRotation[0]);
        //if (data.BoardRotation[1] != oldData.BoardRotation[1])
            emit BoardRotation_PitchChanged(data.BoardRotation[1]);
        //if (data.BoardRotation[2] != oldData.BoardRotation[2])
            emit BoardRotation_YawChanged(data.BoardRotation[2]);
        //if (data.BoardLevelTrim[0] != oldData.BoardLevelTrim[0])
            emit BoardLevelTrim_RollChanged(data.BoardLevelTrim[0]);
        //if (data.BoardLevelTrim[1] != oldData.BoardLevelTrim[1])
            emit BoardLevelTrim_PitchChanged(data.BoardLevelTrim[1]);
        //if (data.AccelKp != oldData.AccelKp)
            emit AccelKpChanged(data.AccelKp);
        //if (data.AccelKi != oldData.AccelKi)
            emit AccelKiChanged(data.AccelKi);
        //if (data.MagKi != oldData.MagKi)
            emit MagKiChanged(data.MagKi);
        //if (data.MagKp != oldData.MagKp)
            emit MagKpChanged(data.MagKp);
        //if (data.AccelTau != oldData.AccelTau)
            emit AccelTauChanged(data.AccelTau);
        //if (data.YawBiasRate != oldData.YawBiasRate)
            emit YawBiasRateChanged(data.YawBiasRate);
        //if (data.ZeroDuringArming != oldData.ZeroDuringArming)
            emit ZeroDuringArmingChanged(data.ZeroDuringArming);
        //if (data.BiasCorrectGyro != oldData.BiasCorrectGyro)
            emit BiasCorrectGyroChanged(data.BiasCorrectGyro);
        //if (data.TrimFlight != oldData.TrimFlight)
            emit TrimFlightChanged(data.TrimFlight);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *AttitudeSettings::clone(quint32 instID)
{
    AttitudeSettings *obj = new AttitudeSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *AttitudeSettings::dirtyClone()
{
    AttitudeSettings *obj = new AttitudeSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
AttitudeSettings *AttitudeSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<AttitudeSettings *>(objMngr->getObject(AttitudeSettings::OBJID, instID));
}

float AttitudeSettings::getBoardRotation(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.BoardRotation[index];
}
void AttitudeSettings::setBoardRotation(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.BoardRotation[index] != value;
   data.BoardRotation[index] = value;
   mutex->unlock();
   if (changed) emit BoardRotationChanged(index,value);
}

float AttitudeSettings::getBoardRotation_Roll() const
{
   QMutexLocker locker(mutex);
   return data.BoardRotation[0];
}
void AttitudeSettings::setBoardRotation_Roll(float value)
{
   mutex->lock();
   bool changed = data.BoardRotation[0] != value;
   data.BoardRotation[0] = value;
   mutex->unlock();
   if (changed) emit BoardRotation_RollChanged(value);
}

float AttitudeSettings::getBoardRotation_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.BoardRotation[1];
}
void AttitudeSettings::setBoardRotation_Pitch(float value)
{
   mutex->lock();
   bool changed = data.BoardRotation[1] != value;
   data.BoardRotation[1] = value;
   mutex->unlock();
   if (changed) emit BoardRotation_PitchChanged(value);
}

float AttitudeSettings::getBoardRotation_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.BoardRotation[2];
}
void AttitudeSettings::setBoardRotation_Yaw(float value)
{
   mutex->lock();
   bool changed = data.BoardRotation[2] != value;
   data.BoardRotation[2] = value;
   mutex->unlock();
   if (changed) emit BoardRotation_YawChanged(value);
}

float AttitudeSettings::getBoardLevelTrim(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.BoardLevelTrim[index];
}
void AttitudeSettings::setBoardLevelTrim(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.BoardLevelTrim[index] != value;
   data.BoardLevelTrim[index] = value;
   mutex->unlock();
   if (changed) emit BoardLevelTrimChanged(index,value);
}

float AttitudeSettings::getBoardLevelTrim_Roll() const
{
   QMutexLocker locker(mutex);
   return data.BoardLevelTrim[0];
}
void AttitudeSettings::setBoardLevelTrim_Roll(float value)
{
   mutex->lock();
   bool changed = data.BoardLevelTrim[0] != value;
   data.BoardLevelTrim[0] = value;
   mutex->unlock();
   if (changed) emit BoardLevelTrim_RollChanged(value);
}

float AttitudeSettings::getBoardLevelTrim_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.BoardLevelTrim[1];
}
void AttitudeSettings::setBoardLevelTrim_Pitch(float value)
{
   mutex->lock();
   bool changed = data.BoardLevelTrim[1] != value;
   data.BoardLevelTrim[1] = value;
   mutex->unlock();
   if (changed) emit BoardLevelTrim_PitchChanged(value);
}

float AttitudeSettings::getAccelKp() const
{
   QMutexLocker locker(mutex);
   return data.AccelKp;
}
void AttitudeSettings::setAccelKp(float value)
{
   mutex->lock();
   bool changed = data.AccelKp != value;
   data.AccelKp = value;
   mutex->unlock();
   if (changed) emit AccelKpChanged(value);
}

float AttitudeSettings::getAccelKi() const
{
   QMutexLocker locker(mutex);
   return data.AccelKi;
}
void AttitudeSettings::setAccelKi(float value)
{
   mutex->lock();
   bool changed = data.AccelKi != value;
   data.AccelKi = value;
   mutex->unlock();
   if (changed) emit AccelKiChanged(value);
}

float AttitudeSettings::getMagKi() const
{
   QMutexLocker locker(mutex);
   return data.MagKi;
}
void AttitudeSettings::setMagKi(float value)
{
   mutex->lock();
   bool changed = data.MagKi != value;
   data.MagKi = value;
   mutex->unlock();
   if (changed) emit MagKiChanged(value);
}

float AttitudeSettings::getMagKp() const
{
   QMutexLocker locker(mutex);
   return data.MagKp;
}
void AttitudeSettings::setMagKp(float value)
{
   mutex->lock();
   bool changed = data.MagKp != value;
   data.MagKp = value;
   mutex->unlock();
   if (changed) emit MagKpChanged(value);
}

float AttitudeSettings::getAccelTau() const
{
   QMutexLocker locker(mutex);
   return data.AccelTau;
}
void AttitudeSettings::setAccelTau(float value)
{
   mutex->lock();
   bool changed = data.AccelTau != value;
   data.AccelTau = value;
   mutex->unlock();
   if (changed) emit AccelTauChanged(value);
}

float AttitudeSettings::getYawBiasRate() const
{
   QMutexLocker locker(mutex);
   return data.YawBiasRate;
}
void AttitudeSettings::setYawBiasRate(float value)
{
   mutex->lock();
   bool changed = data.YawBiasRate != value;
   data.YawBiasRate = value;
   mutex->unlock();
   if (changed) emit YawBiasRateChanged(value);
}

quint8 AttitudeSettings::getZeroDuringArming() const
{
   QMutexLocker locker(mutex);
   return data.ZeroDuringArming;
}
void AttitudeSettings::setZeroDuringArming(quint8 value)
{
   mutex->lock();
   bool changed = data.ZeroDuringArming != value;
   data.ZeroDuringArming = value;
   mutex->unlock();
   if (changed) emit ZeroDuringArmingChanged(value);
}

quint8 AttitudeSettings::getBiasCorrectGyro() const
{
   QMutexLocker locker(mutex);
   return data.BiasCorrectGyro;
}
void AttitudeSettings::setBiasCorrectGyro(quint8 value)
{
   mutex->lock();
   bool changed = data.BiasCorrectGyro != value;
   data.BiasCorrectGyro = value;
   mutex->unlock();
   if (changed) emit BiasCorrectGyroChanged(value);
}

quint8 AttitudeSettings::getTrimFlight() const
{
   QMutexLocker locker(mutex);
   return data.TrimFlight;
}
void AttitudeSettings::setTrimFlight(quint8 value)
{
   mutex->lock();
   bool changed = data.TrimFlight != value;
   data.TrimFlight = value;
   mutex->unlock();
   if (changed) emit TrimFlightChanged(value);
}


