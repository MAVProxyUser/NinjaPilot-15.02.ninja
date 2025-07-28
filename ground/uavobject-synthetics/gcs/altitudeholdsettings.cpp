/**
 ******************************************************************************
 *
 * @file       altitudeholdsettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: altitudeholdsettings.xml.
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

#include "altitudeholdsettings.h"
#include "uavobjectfield.h"

const QString AltitudeHoldSettings::NAME = QString("AltitudeHoldSettings");
const QString AltitudeHoldSettings::DESCRIPTION = QString("Settings for the @ref AltitudeHold module");
const QString AltitudeHoldSettings::CATEGORY = QString("Control");

/**
 * Constructor
 */
AltitudeHoldSettings::AltitudeHoldSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList AltitudePIElemNames;
    AltitudePIElemNames.append("Kp");
    AltitudePIElemNames.append("Ki");
    AltitudePIElemNames.append("Ilimit");
    fields.append( new UAVObjectField(QString("AltitudePI"), tr(""), QString("(m/s)/m"), UAVObjectField::FLOAT32, AltitudePIElemNames, QStringList(), QString("")));
    QStringList VelocityPIElemNames;
    VelocityPIElemNames.append("Kp");
    VelocityPIElemNames.append("Ki");
    VelocityPIElemNames.append("Ilimit");
    fields.append( new UAVObjectField(QString("VelocityPI"), tr(""), QString("(m/s^2)/(m/s)"), UAVObjectField::FLOAT32, VelocityPIElemNames, QStringList(), QString("")));
    QStringList ThrustRateElemNames;
    ThrustRateElemNames.append("0");
    fields.append( new UAVObjectField(QString("ThrustRate"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, ThrustRateElemNames, QStringList(), QString("")));
    QStringList CutThrustWhenZeroElemNames;
    CutThrustWhenZeroElemNames.append("0");
    QStringList CutThrustWhenZeroEnumOptions;
    CutThrustWhenZeroEnumOptions.append("False");
    CutThrustWhenZeroEnumOptions.append("True");
    fields.append( new UAVObjectField(QString("CutThrustWhenZero"), tr(""), QString("bool"), UAVObjectField::ENUM, CutThrustWhenZeroElemNames, CutThrustWhenZeroEnumOptions, QString("")));
    QStringList ThrustExpElemNames;
    ThrustExpElemNames.append("0");
    fields.append( new UAVObjectField(QString("ThrustExp"), tr(""), QString(""), UAVObjectField::UINT8, ThrustExpElemNames, QStringList(), QString("")));

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
UAVObject::Metadata AltitudeHoldSettings::getDefaultMetadata()
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
void AltitudeHoldSettings::setDefaultFieldValues()
{
    data.AltitudePI[0] = 0.8;
    data.AltitudePI[1] = 0;
    data.AltitudePI[2] = 0;
    data.VelocityPI[0] = 0.3;
    data.VelocityPI[1] = 0.3;
    data.VelocityPI[2] = 2;
    data.ThrustRate = 5;
    data.CutThrustWhenZero = 1;
    data.ThrustExp = 128;

}

/**
 * Get the object data fields
 */
AltitudeHoldSettings::DataFields AltitudeHoldSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void AltitudeHoldSettings::setData(const DataFields& data)
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

void AltitudeHoldSettings::emitNotifications()
{
            //if (data.AltitudePI[0] != oldData.AltitudePI[0])
            emit AltitudePI_KpChanged(data.AltitudePI[0]);
        //if (data.AltitudePI[1] != oldData.AltitudePI[1])
            emit AltitudePI_KiChanged(data.AltitudePI[1]);
        //if (data.AltitudePI[2] != oldData.AltitudePI[2])
            emit AltitudePI_IlimitChanged(data.AltitudePI[2]);
        //if (data.VelocityPI[0] != oldData.VelocityPI[0])
            emit VelocityPI_KpChanged(data.VelocityPI[0]);
        //if (data.VelocityPI[1] != oldData.VelocityPI[1])
            emit VelocityPI_KiChanged(data.VelocityPI[1]);
        //if (data.VelocityPI[2] != oldData.VelocityPI[2])
            emit VelocityPI_IlimitChanged(data.VelocityPI[2]);
        //if (data.ThrustRate != oldData.ThrustRate)
            emit ThrustRateChanged(data.ThrustRate);
        //if (data.CutThrustWhenZero != oldData.CutThrustWhenZero)
            emit CutThrustWhenZeroChanged(data.CutThrustWhenZero);
        //if (data.ThrustExp != oldData.ThrustExp)
            emit ThrustExpChanged(data.ThrustExp);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *AltitudeHoldSettings::clone(quint32 instID)
{
    AltitudeHoldSettings *obj = new AltitudeHoldSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *AltitudeHoldSettings::dirtyClone()
{
    AltitudeHoldSettings *obj = new AltitudeHoldSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
AltitudeHoldSettings *AltitudeHoldSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<AltitudeHoldSettings *>(objMngr->getObject(AltitudeHoldSettings::OBJID, instID));
}

float AltitudeHoldSettings::getAltitudePI(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.AltitudePI[index];
}
void AltitudeHoldSettings::setAltitudePI(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.AltitudePI[index] != value;
   data.AltitudePI[index] = value;
   mutex->unlock();
   if (changed) emit AltitudePIChanged(index,value);
}

float AltitudeHoldSettings::getAltitudePI_Kp() const
{
   QMutexLocker locker(mutex);
   return data.AltitudePI[0];
}
void AltitudeHoldSettings::setAltitudePI_Kp(float value)
{
   mutex->lock();
   bool changed = data.AltitudePI[0] != value;
   data.AltitudePI[0] = value;
   mutex->unlock();
   if (changed) emit AltitudePI_KpChanged(value);
}

float AltitudeHoldSettings::getAltitudePI_Ki() const
{
   QMutexLocker locker(mutex);
   return data.AltitudePI[1];
}
void AltitudeHoldSettings::setAltitudePI_Ki(float value)
{
   mutex->lock();
   bool changed = data.AltitudePI[1] != value;
   data.AltitudePI[1] = value;
   mutex->unlock();
   if (changed) emit AltitudePI_KiChanged(value);
}

float AltitudeHoldSettings::getAltitudePI_Ilimit() const
{
   QMutexLocker locker(mutex);
   return data.AltitudePI[2];
}
void AltitudeHoldSettings::setAltitudePI_Ilimit(float value)
{
   mutex->lock();
   bool changed = data.AltitudePI[2] != value;
   data.AltitudePI[2] = value;
   mutex->unlock();
   if (changed) emit AltitudePI_IlimitChanged(value);
}

float AltitudeHoldSettings::getVelocityPI(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.VelocityPI[index];
}
void AltitudeHoldSettings::setVelocityPI(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.VelocityPI[index] != value;
   data.VelocityPI[index] = value;
   mutex->unlock();
   if (changed) emit VelocityPIChanged(index,value);
}

float AltitudeHoldSettings::getVelocityPI_Kp() const
{
   QMutexLocker locker(mutex);
   return data.VelocityPI[0];
}
void AltitudeHoldSettings::setVelocityPI_Kp(float value)
{
   mutex->lock();
   bool changed = data.VelocityPI[0] != value;
   data.VelocityPI[0] = value;
   mutex->unlock();
   if (changed) emit VelocityPI_KpChanged(value);
}

float AltitudeHoldSettings::getVelocityPI_Ki() const
{
   QMutexLocker locker(mutex);
   return data.VelocityPI[1];
}
void AltitudeHoldSettings::setVelocityPI_Ki(float value)
{
   mutex->lock();
   bool changed = data.VelocityPI[1] != value;
   data.VelocityPI[1] = value;
   mutex->unlock();
   if (changed) emit VelocityPI_KiChanged(value);
}

float AltitudeHoldSettings::getVelocityPI_Ilimit() const
{
   QMutexLocker locker(mutex);
   return data.VelocityPI[2];
}
void AltitudeHoldSettings::setVelocityPI_Ilimit(float value)
{
   mutex->lock();
   bool changed = data.VelocityPI[2] != value;
   data.VelocityPI[2] = value;
   mutex->unlock();
   if (changed) emit VelocityPI_IlimitChanged(value);
}

float AltitudeHoldSettings::getThrustRate() const
{
   QMutexLocker locker(mutex);
   return data.ThrustRate;
}
void AltitudeHoldSettings::setThrustRate(float value)
{
   mutex->lock();
   bool changed = data.ThrustRate != value;
   data.ThrustRate = value;
   mutex->unlock();
   if (changed) emit ThrustRateChanged(value);
}

quint8 AltitudeHoldSettings::getCutThrustWhenZero() const
{
   QMutexLocker locker(mutex);
   return data.CutThrustWhenZero;
}
void AltitudeHoldSettings::setCutThrustWhenZero(quint8 value)
{
   mutex->lock();
   bool changed = data.CutThrustWhenZero != value;
   data.CutThrustWhenZero = value;
   mutex->unlock();
   if (changed) emit CutThrustWhenZeroChanged(value);
}

quint8 AltitudeHoldSettings::getThrustExp() const
{
   QMutexLocker locker(mutex);
   return data.ThrustExp;
}
void AltitudeHoldSettings::setThrustExp(quint8 value)
{
   mutex->lock();
   bool changed = data.ThrustExp != value;
   data.ThrustExp = value;
   mutex->unlock();
   if (changed) emit ThrustExpChanged(value);
}


