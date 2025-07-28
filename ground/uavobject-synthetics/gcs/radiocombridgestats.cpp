/**
 ******************************************************************************
 *
 * @file       radiocombridgestats.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: radiocombridgestats.xml.
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

#include "radiocombridgestats.h"
#include "uavobjectfield.h"

const QString RadioComBridgeStats::NAME = QString("RadioComBridgeStats");
const QString RadioComBridgeStats::DESCRIPTION = QString("Maintains the telemetry statistics from the OPLM RadioComBridge.");
const QString RadioComBridgeStats::CATEGORY = QString("System");

/**
 * Constructor
 */
RadioComBridgeStats::RadioComBridgeStats(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList TelemetryTxBytesElemNames;
    TelemetryTxBytesElemNames.append("0");
    fields.append( new UAVObjectField(QString("TelemetryTxBytes"), tr(""), QString("bytes"), UAVObjectField::UINT32, TelemetryTxBytesElemNames, QStringList(), QString("")));
    QStringList TelemetryTxFailuresElemNames;
    TelemetryTxFailuresElemNames.append("0");
    fields.append( new UAVObjectField(QString("TelemetryTxFailures"), tr(""), QString("count"), UAVObjectField::UINT32, TelemetryTxFailuresElemNames, QStringList(), QString("")));
    QStringList TelemetryTxRetriesElemNames;
    TelemetryTxRetriesElemNames.append("0");
    fields.append( new UAVObjectField(QString("TelemetryTxRetries"), tr(""), QString("count"), UAVObjectField::UINT32, TelemetryTxRetriesElemNames, QStringList(), QString("")));
    QStringList TelemetryRxBytesElemNames;
    TelemetryRxBytesElemNames.append("0");
    fields.append( new UAVObjectField(QString("TelemetryRxBytes"), tr(""), QString("bytes"), UAVObjectField::UINT32, TelemetryRxBytesElemNames, QStringList(), QString("")));
    QStringList TelemetryRxFailuresElemNames;
    TelemetryRxFailuresElemNames.append("0");
    fields.append( new UAVObjectField(QString("TelemetryRxFailures"), tr(""), QString("count"), UAVObjectField::UINT32, TelemetryRxFailuresElemNames, QStringList(), QString("")));
    QStringList TelemetryRxSyncErrorsElemNames;
    TelemetryRxSyncErrorsElemNames.append("0");
    fields.append( new UAVObjectField(QString("TelemetryRxSyncErrors"), tr(""), QString("count"), UAVObjectField::UINT32, TelemetryRxSyncErrorsElemNames, QStringList(), QString("")));
    QStringList TelemetryRxCrcErrorsElemNames;
    TelemetryRxCrcErrorsElemNames.append("0");
    fields.append( new UAVObjectField(QString("TelemetryRxCrcErrors"), tr(""), QString("count"), UAVObjectField::UINT32, TelemetryRxCrcErrorsElemNames, QStringList(), QString("")));
    QStringList RadioTxBytesElemNames;
    RadioTxBytesElemNames.append("0");
    fields.append( new UAVObjectField(QString("RadioTxBytes"), tr(""), QString("bytes"), UAVObjectField::UINT32, RadioTxBytesElemNames, QStringList(), QString("")));
    QStringList RadioTxFailuresElemNames;
    RadioTxFailuresElemNames.append("0");
    fields.append( new UAVObjectField(QString("RadioTxFailures"), tr(""), QString("count"), UAVObjectField::UINT32, RadioTxFailuresElemNames, QStringList(), QString("")));
    QStringList RadioTxRetriesElemNames;
    RadioTxRetriesElemNames.append("0");
    fields.append( new UAVObjectField(QString("RadioTxRetries"), tr(""), QString("count"), UAVObjectField::UINT32, RadioTxRetriesElemNames, QStringList(), QString("")));
    QStringList RadioRxBytesElemNames;
    RadioRxBytesElemNames.append("0");
    fields.append( new UAVObjectField(QString("RadioRxBytes"), tr(""), QString("bytes"), UAVObjectField::UINT32, RadioRxBytesElemNames, QStringList(), QString("")));
    QStringList RadioRxFailuresElemNames;
    RadioRxFailuresElemNames.append("0");
    fields.append( new UAVObjectField(QString("RadioRxFailures"), tr(""), QString("count"), UAVObjectField::UINT32, RadioRxFailuresElemNames, QStringList(), QString("")));
    QStringList RadioRxSyncErrorsElemNames;
    RadioRxSyncErrorsElemNames.append("0");
    fields.append( new UAVObjectField(QString("RadioRxSyncErrors"), tr(""), QString("count"), UAVObjectField::UINT32, RadioRxSyncErrorsElemNames, QStringList(), QString("")));
    QStringList RadioRxCrcErrorsElemNames;
    RadioRxCrcErrorsElemNames.append("0");
    fields.append( new UAVObjectField(QString("RadioRxCrcErrors"), tr(""), QString("count"), UAVObjectField::UINT32, RadioRxCrcErrorsElemNames, QStringList(), QString("")));

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
UAVObject::Metadata RadioComBridgeStats::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READONLY << UAVOBJ_GCS_ACCESS_SHIFT |
        0 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        0 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_PERIODIC << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
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
void RadioComBridgeStats::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
RadioComBridgeStats::DataFields RadioComBridgeStats::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void RadioComBridgeStats::setData(const DataFields& data)
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

void RadioComBridgeStats::emitNotifications()
{
            //if (data.TelemetryTxBytes != oldData.TelemetryTxBytes)
            emit TelemetryTxBytesChanged(data.TelemetryTxBytes);
        //if (data.TelemetryTxFailures != oldData.TelemetryTxFailures)
            emit TelemetryTxFailuresChanged(data.TelemetryTxFailures);
        //if (data.TelemetryTxRetries != oldData.TelemetryTxRetries)
            emit TelemetryTxRetriesChanged(data.TelemetryTxRetries);
        //if (data.TelemetryRxBytes != oldData.TelemetryRxBytes)
            emit TelemetryRxBytesChanged(data.TelemetryRxBytes);
        //if (data.TelemetryRxFailures != oldData.TelemetryRxFailures)
            emit TelemetryRxFailuresChanged(data.TelemetryRxFailures);
        //if (data.TelemetryRxSyncErrors != oldData.TelemetryRxSyncErrors)
            emit TelemetryRxSyncErrorsChanged(data.TelemetryRxSyncErrors);
        //if (data.TelemetryRxCrcErrors != oldData.TelemetryRxCrcErrors)
            emit TelemetryRxCrcErrorsChanged(data.TelemetryRxCrcErrors);
        //if (data.RadioTxBytes != oldData.RadioTxBytes)
            emit RadioTxBytesChanged(data.RadioTxBytes);
        //if (data.RadioTxFailures != oldData.RadioTxFailures)
            emit RadioTxFailuresChanged(data.RadioTxFailures);
        //if (data.RadioTxRetries != oldData.RadioTxRetries)
            emit RadioTxRetriesChanged(data.RadioTxRetries);
        //if (data.RadioRxBytes != oldData.RadioRxBytes)
            emit RadioRxBytesChanged(data.RadioRxBytes);
        //if (data.RadioRxFailures != oldData.RadioRxFailures)
            emit RadioRxFailuresChanged(data.RadioRxFailures);
        //if (data.RadioRxSyncErrors != oldData.RadioRxSyncErrors)
            emit RadioRxSyncErrorsChanged(data.RadioRxSyncErrors);
        //if (data.RadioRxCrcErrors != oldData.RadioRxCrcErrors)
            emit RadioRxCrcErrorsChanged(data.RadioRxCrcErrors);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *RadioComBridgeStats::clone(quint32 instID)
{
    RadioComBridgeStats *obj = new RadioComBridgeStats();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *RadioComBridgeStats::dirtyClone()
{
    RadioComBridgeStats *obj = new RadioComBridgeStats();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
RadioComBridgeStats *RadioComBridgeStats::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<RadioComBridgeStats *>(objMngr->getObject(RadioComBridgeStats::OBJID, instID));
}

quint32 RadioComBridgeStats::getTelemetryTxBytes() const
{
   QMutexLocker locker(mutex);
   return data.TelemetryTxBytes;
}
void RadioComBridgeStats::setTelemetryTxBytes(quint32 value)
{
   mutex->lock();
   bool changed = data.TelemetryTxBytes != value;
   data.TelemetryTxBytes = value;
   mutex->unlock();
   if (changed) emit TelemetryTxBytesChanged(value);
}

quint32 RadioComBridgeStats::getTelemetryTxFailures() const
{
   QMutexLocker locker(mutex);
   return data.TelemetryTxFailures;
}
void RadioComBridgeStats::setTelemetryTxFailures(quint32 value)
{
   mutex->lock();
   bool changed = data.TelemetryTxFailures != value;
   data.TelemetryTxFailures = value;
   mutex->unlock();
   if (changed) emit TelemetryTxFailuresChanged(value);
}

quint32 RadioComBridgeStats::getTelemetryTxRetries() const
{
   QMutexLocker locker(mutex);
   return data.TelemetryTxRetries;
}
void RadioComBridgeStats::setTelemetryTxRetries(quint32 value)
{
   mutex->lock();
   bool changed = data.TelemetryTxRetries != value;
   data.TelemetryTxRetries = value;
   mutex->unlock();
   if (changed) emit TelemetryTxRetriesChanged(value);
}

quint32 RadioComBridgeStats::getTelemetryRxBytes() const
{
   QMutexLocker locker(mutex);
   return data.TelemetryRxBytes;
}
void RadioComBridgeStats::setTelemetryRxBytes(quint32 value)
{
   mutex->lock();
   bool changed = data.TelemetryRxBytes != value;
   data.TelemetryRxBytes = value;
   mutex->unlock();
   if (changed) emit TelemetryRxBytesChanged(value);
}

quint32 RadioComBridgeStats::getTelemetryRxFailures() const
{
   QMutexLocker locker(mutex);
   return data.TelemetryRxFailures;
}
void RadioComBridgeStats::setTelemetryRxFailures(quint32 value)
{
   mutex->lock();
   bool changed = data.TelemetryRxFailures != value;
   data.TelemetryRxFailures = value;
   mutex->unlock();
   if (changed) emit TelemetryRxFailuresChanged(value);
}

quint32 RadioComBridgeStats::getTelemetryRxSyncErrors() const
{
   QMutexLocker locker(mutex);
   return data.TelemetryRxSyncErrors;
}
void RadioComBridgeStats::setTelemetryRxSyncErrors(quint32 value)
{
   mutex->lock();
   bool changed = data.TelemetryRxSyncErrors != value;
   data.TelemetryRxSyncErrors = value;
   mutex->unlock();
   if (changed) emit TelemetryRxSyncErrorsChanged(value);
}

quint32 RadioComBridgeStats::getTelemetryRxCrcErrors() const
{
   QMutexLocker locker(mutex);
   return data.TelemetryRxCrcErrors;
}
void RadioComBridgeStats::setTelemetryRxCrcErrors(quint32 value)
{
   mutex->lock();
   bool changed = data.TelemetryRxCrcErrors != value;
   data.TelemetryRxCrcErrors = value;
   mutex->unlock();
   if (changed) emit TelemetryRxCrcErrorsChanged(value);
}

quint32 RadioComBridgeStats::getRadioTxBytes() const
{
   QMutexLocker locker(mutex);
   return data.RadioTxBytes;
}
void RadioComBridgeStats::setRadioTxBytes(quint32 value)
{
   mutex->lock();
   bool changed = data.RadioTxBytes != value;
   data.RadioTxBytes = value;
   mutex->unlock();
   if (changed) emit RadioTxBytesChanged(value);
}

quint32 RadioComBridgeStats::getRadioTxFailures() const
{
   QMutexLocker locker(mutex);
   return data.RadioTxFailures;
}
void RadioComBridgeStats::setRadioTxFailures(quint32 value)
{
   mutex->lock();
   bool changed = data.RadioTxFailures != value;
   data.RadioTxFailures = value;
   mutex->unlock();
   if (changed) emit RadioTxFailuresChanged(value);
}

quint32 RadioComBridgeStats::getRadioTxRetries() const
{
   QMutexLocker locker(mutex);
   return data.RadioTxRetries;
}
void RadioComBridgeStats::setRadioTxRetries(quint32 value)
{
   mutex->lock();
   bool changed = data.RadioTxRetries != value;
   data.RadioTxRetries = value;
   mutex->unlock();
   if (changed) emit RadioTxRetriesChanged(value);
}

quint32 RadioComBridgeStats::getRadioRxBytes() const
{
   QMutexLocker locker(mutex);
   return data.RadioRxBytes;
}
void RadioComBridgeStats::setRadioRxBytes(quint32 value)
{
   mutex->lock();
   bool changed = data.RadioRxBytes != value;
   data.RadioRxBytes = value;
   mutex->unlock();
   if (changed) emit RadioRxBytesChanged(value);
}

quint32 RadioComBridgeStats::getRadioRxFailures() const
{
   QMutexLocker locker(mutex);
   return data.RadioRxFailures;
}
void RadioComBridgeStats::setRadioRxFailures(quint32 value)
{
   mutex->lock();
   bool changed = data.RadioRxFailures != value;
   data.RadioRxFailures = value;
   mutex->unlock();
   if (changed) emit RadioRxFailuresChanged(value);
}

quint32 RadioComBridgeStats::getRadioRxSyncErrors() const
{
   QMutexLocker locker(mutex);
   return data.RadioRxSyncErrors;
}
void RadioComBridgeStats::setRadioRxSyncErrors(quint32 value)
{
   mutex->lock();
   bool changed = data.RadioRxSyncErrors != value;
   data.RadioRxSyncErrors = value;
   mutex->unlock();
   if (changed) emit RadioRxSyncErrorsChanged(value);
}

quint32 RadioComBridgeStats::getRadioRxCrcErrors() const
{
   QMutexLocker locker(mutex);
   return data.RadioRxCrcErrors;
}
void RadioComBridgeStats::setRadioRxCrcErrors(quint32 value)
{
   mutex->lock();
   bool changed = data.RadioRxCrcErrors != value;
   data.RadioRxCrcErrors = value;
   mutex->unlock();
   if (changed) emit RadioRxCrcErrorsChanged(value);
}


