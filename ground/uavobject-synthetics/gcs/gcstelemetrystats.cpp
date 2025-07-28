/**
 ******************************************************************************
 *
 * @file       gcstelemetrystats.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: gcstelemetrystats.xml.
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

#include "gcstelemetrystats.h"
#include "uavobjectfield.h"

const QString GCSTelemetryStats::NAME = QString("GCSTelemetryStats");
const QString GCSTelemetryStats::DESCRIPTION = QString("The telemetry statistics from the ground computer");
const QString GCSTelemetryStats::CATEGORY = QString("System");

/**
 * Constructor
 */
GCSTelemetryStats::GCSTelemetryStats(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList TxDataRateElemNames;
    TxDataRateElemNames.append("0");
    fields.append( new UAVObjectField(QString("TxDataRate"), tr(""), QString("bytes/sec"), UAVObjectField::FLOAT32, TxDataRateElemNames, QStringList(), QString("")));
    QStringList TxBytesElemNames;
    TxBytesElemNames.append("0");
    fields.append( new UAVObjectField(QString("TxBytes"), tr(""), QString("bytes"), UAVObjectField::UINT32, TxBytesElemNames, QStringList(), QString("")));
    QStringList TxFailuresElemNames;
    TxFailuresElemNames.append("0");
    fields.append( new UAVObjectField(QString("TxFailures"), tr(""), QString("count"), UAVObjectField::UINT32, TxFailuresElemNames, QStringList(), QString("")));
    QStringList TxRetriesElemNames;
    TxRetriesElemNames.append("0");
    fields.append( new UAVObjectField(QString("TxRetries"), tr(""), QString("count"), UAVObjectField::UINT32, TxRetriesElemNames, QStringList(), QString("")));
    QStringList RxDataRateElemNames;
    RxDataRateElemNames.append("0");
    fields.append( new UAVObjectField(QString("RxDataRate"), tr(""), QString("bytes/sec"), UAVObjectField::FLOAT32, RxDataRateElemNames, QStringList(), QString("")));
    QStringList RxBytesElemNames;
    RxBytesElemNames.append("0");
    fields.append( new UAVObjectField(QString("RxBytes"), tr(""), QString("bytes"), UAVObjectField::UINT32, RxBytesElemNames, QStringList(), QString("")));
    QStringList RxFailuresElemNames;
    RxFailuresElemNames.append("0");
    fields.append( new UAVObjectField(QString("RxFailures"), tr(""), QString("count"), UAVObjectField::UINT32, RxFailuresElemNames, QStringList(), QString("")));
    QStringList RxSyncErrorsElemNames;
    RxSyncErrorsElemNames.append("0");
    fields.append( new UAVObjectField(QString("RxSyncErrors"), tr(""), QString("count"), UAVObjectField::UINT32, RxSyncErrorsElemNames, QStringList(), QString("")));
    QStringList RxCrcErrorsElemNames;
    RxCrcErrorsElemNames.append("0");
    fields.append( new UAVObjectField(QString("RxCrcErrors"), tr(""), QString("count"), UAVObjectField::UINT32, RxCrcErrorsElemNames, QStringList(), QString("")));
    QStringList StatusElemNames;
    StatusElemNames.append("0");
    QStringList StatusEnumOptions;
    StatusEnumOptions.append("Disconnected");
    StatusEnumOptions.append("HandshakeReq");
    StatusEnumOptions.append("HandshakeAck");
    StatusEnumOptions.append("Connected");
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
UAVObject::Metadata GCSTelemetryStats::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        0 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        0 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_PERIODIC << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_LOGGING_UPDATE_MODE_SHIFT;
    metadata.flightTelemetryUpdatePeriod = 0;
    metadata.gcsTelemetryUpdatePeriod = 5000;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void GCSTelemetryStats::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
GCSTelemetryStats::DataFields GCSTelemetryStats::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void GCSTelemetryStats::setData(const DataFields& data)
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

void GCSTelemetryStats::emitNotifications()
{
            //if (data.TxDataRate != oldData.TxDataRate)
            emit TxDataRateChanged(data.TxDataRate);
        //if (data.TxBytes != oldData.TxBytes)
            emit TxBytesChanged(data.TxBytes);
        //if (data.TxFailures != oldData.TxFailures)
            emit TxFailuresChanged(data.TxFailures);
        //if (data.TxRetries != oldData.TxRetries)
            emit TxRetriesChanged(data.TxRetries);
        //if (data.RxDataRate != oldData.RxDataRate)
            emit RxDataRateChanged(data.RxDataRate);
        //if (data.RxBytes != oldData.RxBytes)
            emit RxBytesChanged(data.RxBytes);
        //if (data.RxFailures != oldData.RxFailures)
            emit RxFailuresChanged(data.RxFailures);
        //if (data.RxSyncErrors != oldData.RxSyncErrors)
            emit RxSyncErrorsChanged(data.RxSyncErrors);
        //if (data.RxCrcErrors != oldData.RxCrcErrors)
            emit RxCrcErrorsChanged(data.RxCrcErrors);
        //if (data.Status != oldData.Status)
            emit StatusChanged(data.Status);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *GCSTelemetryStats::clone(quint32 instID)
{
    GCSTelemetryStats *obj = new GCSTelemetryStats();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *GCSTelemetryStats::dirtyClone()
{
    GCSTelemetryStats *obj = new GCSTelemetryStats();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
GCSTelemetryStats *GCSTelemetryStats::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<GCSTelemetryStats *>(objMngr->getObject(GCSTelemetryStats::OBJID, instID));
}

float GCSTelemetryStats::getTxDataRate() const
{
   QMutexLocker locker(mutex);
   return data.TxDataRate;
}
void GCSTelemetryStats::setTxDataRate(float value)
{
   mutex->lock();
   bool changed = data.TxDataRate != value;
   data.TxDataRate = value;
   mutex->unlock();
   if (changed) emit TxDataRateChanged(value);
}

quint32 GCSTelemetryStats::getTxBytes() const
{
   QMutexLocker locker(mutex);
   return data.TxBytes;
}
void GCSTelemetryStats::setTxBytes(quint32 value)
{
   mutex->lock();
   bool changed = data.TxBytes != value;
   data.TxBytes = value;
   mutex->unlock();
   if (changed) emit TxBytesChanged(value);
}

quint32 GCSTelemetryStats::getTxFailures() const
{
   QMutexLocker locker(mutex);
   return data.TxFailures;
}
void GCSTelemetryStats::setTxFailures(quint32 value)
{
   mutex->lock();
   bool changed = data.TxFailures != value;
   data.TxFailures = value;
   mutex->unlock();
   if (changed) emit TxFailuresChanged(value);
}

quint32 GCSTelemetryStats::getTxRetries() const
{
   QMutexLocker locker(mutex);
   return data.TxRetries;
}
void GCSTelemetryStats::setTxRetries(quint32 value)
{
   mutex->lock();
   bool changed = data.TxRetries != value;
   data.TxRetries = value;
   mutex->unlock();
   if (changed) emit TxRetriesChanged(value);
}

float GCSTelemetryStats::getRxDataRate() const
{
   QMutexLocker locker(mutex);
   return data.RxDataRate;
}
void GCSTelemetryStats::setRxDataRate(float value)
{
   mutex->lock();
   bool changed = data.RxDataRate != value;
   data.RxDataRate = value;
   mutex->unlock();
   if (changed) emit RxDataRateChanged(value);
}

quint32 GCSTelemetryStats::getRxBytes() const
{
   QMutexLocker locker(mutex);
   return data.RxBytes;
}
void GCSTelemetryStats::setRxBytes(quint32 value)
{
   mutex->lock();
   bool changed = data.RxBytes != value;
   data.RxBytes = value;
   mutex->unlock();
   if (changed) emit RxBytesChanged(value);
}

quint32 GCSTelemetryStats::getRxFailures() const
{
   QMutexLocker locker(mutex);
   return data.RxFailures;
}
void GCSTelemetryStats::setRxFailures(quint32 value)
{
   mutex->lock();
   bool changed = data.RxFailures != value;
   data.RxFailures = value;
   mutex->unlock();
   if (changed) emit RxFailuresChanged(value);
}

quint32 GCSTelemetryStats::getRxSyncErrors() const
{
   QMutexLocker locker(mutex);
   return data.RxSyncErrors;
}
void GCSTelemetryStats::setRxSyncErrors(quint32 value)
{
   mutex->lock();
   bool changed = data.RxSyncErrors != value;
   data.RxSyncErrors = value;
   mutex->unlock();
   if (changed) emit RxSyncErrorsChanged(value);
}

quint32 GCSTelemetryStats::getRxCrcErrors() const
{
   QMutexLocker locker(mutex);
   return data.RxCrcErrors;
}
void GCSTelemetryStats::setRxCrcErrors(quint32 value)
{
   mutex->lock();
   bool changed = data.RxCrcErrors != value;
   data.RxCrcErrors = value;
   mutex->unlock();
   if (changed) emit RxCrcErrorsChanged(value);
}

quint8 GCSTelemetryStats::getStatus() const
{
   QMutexLocker locker(mutex);
   return data.Status;
}
void GCSTelemetryStats::setStatus(quint8 value)
{
   mutex->lock();
   bool changed = data.Status != value;
   data.Status = value;
   mutex->unlock();
   if (changed) emit StatusChanged(value);
}


