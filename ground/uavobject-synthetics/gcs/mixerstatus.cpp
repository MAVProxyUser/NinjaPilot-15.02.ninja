/**
 ******************************************************************************
 *
 * @file       mixerstatus.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: mixerstatus.xml.
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

#include "mixerstatus.h"
#include "uavobjectfield.h"

const QString MixerStatus::NAME = QString("MixerStatus");
const QString MixerStatus::DESCRIPTION = QString("Status for the matrix mixer showing the output of each mixer after all scaling");
const QString MixerStatus::CATEGORY = QString("Control");

/**
 * Constructor
 */
MixerStatus::MixerStatus(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList Mixer1ElemNames;
    Mixer1ElemNames.append("0");
    fields.append( new UAVObjectField(QString("Mixer1"), tr(""), QString(""), UAVObjectField::FLOAT32, Mixer1ElemNames, QStringList(), QString("")));
    QStringList Mixer2ElemNames;
    Mixer2ElemNames.append("0");
    fields.append( new UAVObjectField(QString("Mixer2"), tr(""), QString(""), UAVObjectField::FLOAT32, Mixer2ElemNames, QStringList(), QString("")));
    QStringList Mixer3ElemNames;
    Mixer3ElemNames.append("0");
    fields.append( new UAVObjectField(QString("Mixer3"), tr(""), QString(""), UAVObjectField::FLOAT32, Mixer3ElemNames, QStringList(), QString("")));
    QStringList Mixer4ElemNames;
    Mixer4ElemNames.append("0");
    fields.append( new UAVObjectField(QString("Mixer4"), tr(""), QString(""), UAVObjectField::FLOAT32, Mixer4ElemNames, QStringList(), QString("")));
    QStringList Mixer5ElemNames;
    Mixer5ElemNames.append("0");
    fields.append( new UAVObjectField(QString("Mixer5"), tr(""), QString(""), UAVObjectField::FLOAT32, Mixer5ElemNames, QStringList(), QString("")));
    QStringList Mixer6ElemNames;
    Mixer6ElemNames.append("0");
    fields.append( new UAVObjectField(QString("Mixer6"), tr(""), QString(""), UAVObjectField::FLOAT32, Mixer6ElemNames, QStringList(), QString("")));
    QStringList Mixer7ElemNames;
    Mixer7ElemNames.append("0");
    fields.append( new UAVObjectField(QString("Mixer7"), tr(""), QString(""), UAVObjectField::FLOAT32, Mixer7ElemNames, QStringList(), QString("")));
    QStringList Mixer8ElemNames;
    Mixer8ElemNames.append("0");
    fields.append( new UAVObjectField(QString("Mixer8"), tr(""), QString(""), UAVObjectField::FLOAT32, Mixer8ElemNames, QStringList(), QString("")));
    QStringList Mixer9ElemNames;
    Mixer9ElemNames.append("0");
    fields.append( new UAVObjectField(QString("Mixer9"), tr(""), QString(""), UAVObjectField::FLOAT32, Mixer9ElemNames, QStringList(), QString("")));
    QStringList Mixer10ElemNames;
    Mixer10ElemNames.append("0");
    fields.append( new UAVObjectField(QString("Mixer10"), tr(""), QString(""), UAVObjectField::FLOAT32, Mixer10ElemNames, QStringList(), QString("")));
    QStringList Mixer11ElemNames;
    Mixer11ElemNames.append("0");
    fields.append( new UAVObjectField(QString("Mixer11"), tr(""), QString(""), UAVObjectField::FLOAT32, Mixer11ElemNames, QStringList(), QString("")));
    QStringList Mixer12ElemNames;
    Mixer12ElemNames.append("0");
    fields.append( new UAVObjectField(QString("Mixer12"), tr(""), QString(""), UAVObjectField::FLOAT32, Mixer12ElemNames, QStringList(), QString("")));

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
UAVObject::Metadata MixerStatus::getDefaultMetadata()
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
void MixerStatus::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
MixerStatus::DataFields MixerStatus::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void MixerStatus::setData(const DataFields& data)
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

void MixerStatus::emitNotifications()
{
            //if (data.Mixer1 != oldData.Mixer1)
            emit Mixer1Changed(data.Mixer1);
        //if (data.Mixer2 != oldData.Mixer2)
            emit Mixer2Changed(data.Mixer2);
        //if (data.Mixer3 != oldData.Mixer3)
            emit Mixer3Changed(data.Mixer3);
        //if (data.Mixer4 != oldData.Mixer4)
            emit Mixer4Changed(data.Mixer4);
        //if (data.Mixer5 != oldData.Mixer5)
            emit Mixer5Changed(data.Mixer5);
        //if (data.Mixer6 != oldData.Mixer6)
            emit Mixer6Changed(data.Mixer6);
        //if (data.Mixer7 != oldData.Mixer7)
            emit Mixer7Changed(data.Mixer7);
        //if (data.Mixer8 != oldData.Mixer8)
            emit Mixer8Changed(data.Mixer8);
        //if (data.Mixer9 != oldData.Mixer9)
            emit Mixer9Changed(data.Mixer9);
        //if (data.Mixer10 != oldData.Mixer10)
            emit Mixer10Changed(data.Mixer10);
        //if (data.Mixer11 != oldData.Mixer11)
            emit Mixer11Changed(data.Mixer11);
        //if (data.Mixer12 != oldData.Mixer12)
            emit Mixer12Changed(data.Mixer12);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *MixerStatus::clone(quint32 instID)
{
    MixerStatus *obj = new MixerStatus();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *MixerStatus::dirtyClone()
{
    MixerStatus *obj = new MixerStatus();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
MixerStatus *MixerStatus::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<MixerStatus *>(objMngr->getObject(MixerStatus::OBJID, instID));
}

float MixerStatus::getMixer1() const
{
   QMutexLocker locker(mutex);
   return data.Mixer1;
}
void MixerStatus::setMixer1(float value)
{
   mutex->lock();
   bool changed = data.Mixer1 != value;
   data.Mixer1 = value;
   mutex->unlock();
   if (changed) emit Mixer1Changed(value);
}

float MixerStatus::getMixer2() const
{
   QMutexLocker locker(mutex);
   return data.Mixer2;
}
void MixerStatus::setMixer2(float value)
{
   mutex->lock();
   bool changed = data.Mixer2 != value;
   data.Mixer2 = value;
   mutex->unlock();
   if (changed) emit Mixer2Changed(value);
}

float MixerStatus::getMixer3() const
{
   QMutexLocker locker(mutex);
   return data.Mixer3;
}
void MixerStatus::setMixer3(float value)
{
   mutex->lock();
   bool changed = data.Mixer3 != value;
   data.Mixer3 = value;
   mutex->unlock();
   if (changed) emit Mixer3Changed(value);
}

float MixerStatus::getMixer4() const
{
   QMutexLocker locker(mutex);
   return data.Mixer4;
}
void MixerStatus::setMixer4(float value)
{
   mutex->lock();
   bool changed = data.Mixer4 != value;
   data.Mixer4 = value;
   mutex->unlock();
   if (changed) emit Mixer4Changed(value);
}

float MixerStatus::getMixer5() const
{
   QMutexLocker locker(mutex);
   return data.Mixer5;
}
void MixerStatus::setMixer5(float value)
{
   mutex->lock();
   bool changed = data.Mixer5 != value;
   data.Mixer5 = value;
   mutex->unlock();
   if (changed) emit Mixer5Changed(value);
}

float MixerStatus::getMixer6() const
{
   QMutexLocker locker(mutex);
   return data.Mixer6;
}
void MixerStatus::setMixer6(float value)
{
   mutex->lock();
   bool changed = data.Mixer6 != value;
   data.Mixer6 = value;
   mutex->unlock();
   if (changed) emit Mixer6Changed(value);
}

float MixerStatus::getMixer7() const
{
   QMutexLocker locker(mutex);
   return data.Mixer7;
}
void MixerStatus::setMixer7(float value)
{
   mutex->lock();
   bool changed = data.Mixer7 != value;
   data.Mixer7 = value;
   mutex->unlock();
   if (changed) emit Mixer7Changed(value);
}

float MixerStatus::getMixer8() const
{
   QMutexLocker locker(mutex);
   return data.Mixer8;
}
void MixerStatus::setMixer8(float value)
{
   mutex->lock();
   bool changed = data.Mixer8 != value;
   data.Mixer8 = value;
   mutex->unlock();
   if (changed) emit Mixer8Changed(value);
}

float MixerStatus::getMixer9() const
{
   QMutexLocker locker(mutex);
   return data.Mixer9;
}
void MixerStatus::setMixer9(float value)
{
   mutex->lock();
   bool changed = data.Mixer9 != value;
   data.Mixer9 = value;
   mutex->unlock();
   if (changed) emit Mixer9Changed(value);
}

float MixerStatus::getMixer10() const
{
   QMutexLocker locker(mutex);
   return data.Mixer10;
}
void MixerStatus::setMixer10(float value)
{
   mutex->lock();
   bool changed = data.Mixer10 != value;
   data.Mixer10 = value;
   mutex->unlock();
   if (changed) emit Mixer10Changed(value);
}

float MixerStatus::getMixer11() const
{
   QMutexLocker locker(mutex);
   return data.Mixer11;
}
void MixerStatus::setMixer11(float value)
{
   mutex->lock();
   bool changed = data.Mixer11 != value;
   data.Mixer11 = value;
   mutex->unlock();
   if (changed) emit Mixer11Changed(value);
}

float MixerStatus::getMixer12() const
{
   QMutexLocker locker(mutex);
   return data.Mixer12;
}
void MixerStatus::setMixer12(float value)
{
   mutex->lock();
   bool changed = data.Mixer12 != value;
   data.Mixer12 = value;
   mutex->unlock();
   if (changed) emit Mixer12Changed(value);
}


