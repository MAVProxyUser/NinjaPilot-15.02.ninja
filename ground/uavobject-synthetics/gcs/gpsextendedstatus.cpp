/**
 ******************************************************************************
 *
 * @file       gpsextendedstatus.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: gpsextendedstatus.xml.
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

#include "gpsextendedstatus.h"
#include "uavobjectfield.h"

const QString GPSExtendedStatus::NAME = QString("GPSExtendedStatus");
const QString GPSExtendedStatus::DESCRIPTION = QString("Extended GPS status.");
const QString GPSExtendedStatus::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
GPSExtendedStatus::GPSExtendedStatus(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList FlightTimeElemNames;
    FlightTimeElemNames.append("0");
    fields.append( new UAVObjectField(QString("FlightTime"), tr(""), QString(""), UAVObjectField::UINT32, FlightTimeElemNames, QStringList(), QString("")));
    QStringList OptionsElemNames;
    OptionsElemNames.append("0");
    fields.append( new UAVObjectField(QString("Options"), tr(""), QString(""), UAVObjectField::UINT16, OptionsElemNames, QStringList(), QString("")));
    QStringList StatusElemNames;
    StatusElemNames.append("0");
    QStringList StatusEnumOptions;
    StatusEnumOptions.append("NONE");
    StatusEnumOptions.append("GPSV9");
    fields.append( new UAVObjectField(QString("Status"), tr(""), QString(""), UAVObjectField::ENUM, StatusElemNames, StatusEnumOptions, QString("")));
    QStringList BoardTypeElemNames;
    BoardTypeElemNames.append("0");
    BoardTypeElemNames.append("1");
    fields.append( new UAVObjectField(QString("BoardType"), tr(""), QString("hex"), UAVObjectField::UINT8, BoardTypeElemNames, QStringList(), QString("")));
    QStringList FirmwareHashElemNames;
    FirmwareHashElemNames.append("0");
    FirmwareHashElemNames.append("1");
    FirmwareHashElemNames.append("2");
    FirmwareHashElemNames.append("3");
    FirmwareHashElemNames.append("4");
    FirmwareHashElemNames.append("5");
    FirmwareHashElemNames.append("6");
    FirmwareHashElemNames.append("7");
    fields.append( new UAVObjectField(QString("FirmwareHash"), tr(""), QString("hex"), UAVObjectField::UINT8, FirmwareHashElemNames, QStringList(), QString("")));
    QStringList FirmwareTagElemNames;
    FirmwareTagElemNames.append("0");
    FirmwareTagElemNames.append("1");
    FirmwareTagElemNames.append("2");
    FirmwareTagElemNames.append("3");
    FirmwareTagElemNames.append("4");
    FirmwareTagElemNames.append("5");
    FirmwareTagElemNames.append("6");
    FirmwareTagElemNames.append("7");
    FirmwareTagElemNames.append("8");
    FirmwareTagElemNames.append("9");
    FirmwareTagElemNames.append("10");
    FirmwareTagElemNames.append("11");
    FirmwareTagElemNames.append("12");
    FirmwareTagElemNames.append("13");
    FirmwareTagElemNames.append("14");
    FirmwareTagElemNames.append("15");
    FirmwareTagElemNames.append("16");
    FirmwareTagElemNames.append("17");
    FirmwareTagElemNames.append("18");
    FirmwareTagElemNames.append("19");
    FirmwareTagElemNames.append("20");
    FirmwareTagElemNames.append("21");
    FirmwareTagElemNames.append("22");
    FirmwareTagElemNames.append("23");
    FirmwareTagElemNames.append("24");
    FirmwareTagElemNames.append("25");
    fields.append( new UAVObjectField(QString("FirmwareTag"), tr(""), QString("char"), UAVObjectField::UINT8, FirmwareTagElemNames, QStringList(), QString("")));

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
UAVObject::Metadata GPSExtendedStatus::getDefaultMetadata()
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
void GPSExtendedStatus::setDefaultFieldValues()
{
    data.Status = 0;

}

/**
 * Get the object data fields
 */
GPSExtendedStatus::DataFields GPSExtendedStatus::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void GPSExtendedStatus::setData(const DataFields& data)
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

void GPSExtendedStatus::emitNotifications()
{
            //if (data.FlightTime != oldData.FlightTime)
            emit FlightTimeChanged(data.FlightTime);
        //if (data.Options != oldData.Options)
            emit OptionsChanged(data.Options);
        //if (data.Status != oldData.Status)
            emit StatusChanged(data.Status);
        //if (data.BoardType[0] != oldData.BoardType[0])
            emit BoardType_0Changed(data.BoardType[0]);
        //if (data.BoardType[1] != oldData.BoardType[1])
            emit BoardType_1Changed(data.BoardType[1]);
        //if (data.FirmwareHash[0] != oldData.FirmwareHash[0])
            emit FirmwareHash_0Changed(data.FirmwareHash[0]);
        //if (data.FirmwareHash[1] != oldData.FirmwareHash[1])
            emit FirmwareHash_1Changed(data.FirmwareHash[1]);
        //if (data.FirmwareHash[2] != oldData.FirmwareHash[2])
            emit FirmwareHash_2Changed(data.FirmwareHash[2]);
        //if (data.FirmwareHash[3] != oldData.FirmwareHash[3])
            emit FirmwareHash_3Changed(data.FirmwareHash[3]);
        //if (data.FirmwareHash[4] != oldData.FirmwareHash[4])
            emit FirmwareHash_4Changed(data.FirmwareHash[4]);
        //if (data.FirmwareHash[5] != oldData.FirmwareHash[5])
            emit FirmwareHash_5Changed(data.FirmwareHash[5]);
        //if (data.FirmwareHash[6] != oldData.FirmwareHash[6])
            emit FirmwareHash_6Changed(data.FirmwareHash[6]);
        //if (data.FirmwareHash[7] != oldData.FirmwareHash[7])
            emit FirmwareHash_7Changed(data.FirmwareHash[7]);
        //if (data.FirmwareTag[0] != oldData.FirmwareTag[0])
            emit FirmwareTag_0Changed(data.FirmwareTag[0]);
        //if (data.FirmwareTag[1] != oldData.FirmwareTag[1])
            emit FirmwareTag_1Changed(data.FirmwareTag[1]);
        //if (data.FirmwareTag[2] != oldData.FirmwareTag[2])
            emit FirmwareTag_2Changed(data.FirmwareTag[2]);
        //if (data.FirmwareTag[3] != oldData.FirmwareTag[3])
            emit FirmwareTag_3Changed(data.FirmwareTag[3]);
        //if (data.FirmwareTag[4] != oldData.FirmwareTag[4])
            emit FirmwareTag_4Changed(data.FirmwareTag[4]);
        //if (data.FirmwareTag[5] != oldData.FirmwareTag[5])
            emit FirmwareTag_5Changed(data.FirmwareTag[5]);
        //if (data.FirmwareTag[6] != oldData.FirmwareTag[6])
            emit FirmwareTag_6Changed(data.FirmwareTag[6]);
        //if (data.FirmwareTag[7] != oldData.FirmwareTag[7])
            emit FirmwareTag_7Changed(data.FirmwareTag[7]);
        //if (data.FirmwareTag[8] != oldData.FirmwareTag[8])
            emit FirmwareTag_8Changed(data.FirmwareTag[8]);
        //if (data.FirmwareTag[9] != oldData.FirmwareTag[9])
            emit FirmwareTag_9Changed(data.FirmwareTag[9]);
        //if (data.FirmwareTag[10] != oldData.FirmwareTag[10])
            emit FirmwareTag_10Changed(data.FirmwareTag[10]);
        //if (data.FirmwareTag[11] != oldData.FirmwareTag[11])
            emit FirmwareTag_11Changed(data.FirmwareTag[11]);
        //if (data.FirmwareTag[12] != oldData.FirmwareTag[12])
            emit FirmwareTag_12Changed(data.FirmwareTag[12]);
        //if (data.FirmwareTag[13] != oldData.FirmwareTag[13])
            emit FirmwareTag_13Changed(data.FirmwareTag[13]);
        //if (data.FirmwareTag[14] != oldData.FirmwareTag[14])
            emit FirmwareTag_14Changed(data.FirmwareTag[14]);
        //if (data.FirmwareTag[15] != oldData.FirmwareTag[15])
            emit FirmwareTag_15Changed(data.FirmwareTag[15]);
        //if (data.FirmwareTag[16] != oldData.FirmwareTag[16])
            emit FirmwareTag_16Changed(data.FirmwareTag[16]);
        //if (data.FirmwareTag[17] != oldData.FirmwareTag[17])
            emit FirmwareTag_17Changed(data.FirmwareTag[17]);
        //if (data.FirmwareTag[18] != oldData.FirmwareTag[18])
            emit FirmwareTag_18Changed(data.FirmwareTag[18]);
        //if (data.FirmwareTag[19] != oldData.FirmwareTag[19])
            emit FirmwareTag_19Changed(data.FirmwareTag[19]);
        //if (data.FirmwareTag[20] != oldData.FirmwareTag[20])
            emit FirmwareTag_20Changed(data.FirmwareTag[20]);
        //if (data.FirmwareTag[21] != oldData.FirmwareTag[21])
            emit FirmwareTag_21Changed(data.FirmwareTag[21]);
        //if (data.FirmwareTag[22] != oldData.FirmwareTag[22])
            emit FirmwareTag_22Changed(data.FirmwareTag[22]);
        //if (data.FirmwareTag[23] != oldData.FirmwareTag[23])
            emit FirmwareTag_23Changed(data.FirmwareTag[23]);
        //if (data.FirmwareTag[24] != oldData.FirmwareTag[24])
            emit FirmwareTag_24Changed(data.FirmwareTag[24]);
        //if (data.FirmwareTag[25] != oldData.FirmwareTag[25])
            emit FirmwareTag_25Changed(data.FirmwareTag[25]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *GPSExtendedStatus::clone(quint32 instID)
{
    GPSExtendedStatus *obj = new GPSExtendedStatus();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *GPSExtendedStatus::dirtyClone()
{
    GPSExtendedStatus *obj = new GPSExtendedStatus();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
GPSExtendedStatus *GPSExtendedStatus::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<GPSExtendedStatus *>(objMngr->getObject(GPSExtendedStatus::OBJID, instID));
}

quint32 GPSExtendedStatus::getFlightTime() const
{
   QMutexLocker locker(mutex);
   return data.FlightTime;
}
void GPSExtendedStatus::setFlightTime(quint32 value)
{
   mutex->lock();
   bool changed = data.FlightTime != value;
   data.FlightTime = value;
   mutex->unlock();
   if (changed) emit FlightTimeChanged(value);
}

quint16 GPSExtendedStatus::getOptions() const
{
   QMutexLocker locker(mutex);
   return data.Options;
}
void GPSExtendedStatus::setOptions(quint16 value)
{
   mutex->lock();
   bool changed = data.Options != value;
   data.Options = value;
   mutex->unlock();
   if (changed) emit OptionsChanged(value);
}

quint8 GPSExtendedStatus::getStatus() const
{
   QMutexLocker locker(mutex);
   return data.Status;
}
void GPSExtendedStatus::setStatus(quint8 value)
{
   mutex->lock();
   bool changed = data.Status != value;
   data.Status = value;
   mutex->unlock();
   if (changed) emit StatusChanged(value);
}

quint8 GPSExtendedStatus::getBoardType(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.BoardType[index];
}
void GPSExtendedStatus::setBoardType(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.BoardType[index] != value;
   data.BoardType[index] = value;
   mutex->unlock();
   if (changed) emit BoardTypeChanged(index,value);
}

quint8 GPSExtendedStatus::getBoardType_0() const
{
   QMutexLocker locker(mutex);
   return data.BoardType[0];
}
void GPSExtendedStatus::setBoardType_0(quint8 value)
{
   mutex->lock();
   bool changed = data.BoardType[0] != value;
   data.BoardType[0] = value;
   mutex->unlock();
   if (changed) emit BoardType_0Changed(value);
}

quint8 GPSExtendedStatus::getBoardType_1() const
{
   QMutexLocker locker(mutex);
   return data.BoardType[1];
}
void GPSExtendedStatus::setBoardType_1(quint8 value)
{
   mutex->lock();
   bool changed = data.BoardType[1] != value;
   data.BoardType[1] = value;
   mutex->unlock();
   if (changed) emit BoardType_1Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareHash(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.FirmwareHash[index];
}
void GPSExtendedStatus::setFirmwareHash(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareHash[index] != value;
   data.FirmwareHash[index] = value;
   mutex->unlock();
   if (changed) emit FirmwareHashChanged(index,value);
}

quint8 GPSExtendedStatus::getFirmwareHash_0() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareHash[0];
}
void GPSExtendedStatus::setFirmwareHash_0(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareHash[0] != value;
   data.FirmwareHash[0] = value;
   mutex->unlock();
   if (changed) emit FirmwareHash_0Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareHash_1() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareHash[1];
}
void GPSExtendedStatus::setFirmwareHash_1(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareHash[1] != value;
   data.FirmwareHash[1] = value;
   mutex->unlock();
   if (changed) emit FirmwareHash_1Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareHash_2() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareHash[2];
}
void GPSExtendedStatus::setFirmwareHash_2(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareHash[2] != value;
   data.FirmwareHash[2] = value;
   mutex->unlock();
   if (changed) emit FirmwareHash_2Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareHash_3() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareHash[3];
}
void GPSExtendedStatus::setFirmwareHash_3(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareHash[3] != value;
   data.FirmwareHash[3] = value;
   mutex->unlock();
   if (changed) emit FirmwareHash_3Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareHash_4() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareHash[4];
}
void GPSExtendedStatus::setFirmwareHash_4(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareHash[4] != value;
   data.FirmwareHash[4] = value;
   mutex->unlock();
   if (changed) emit FirmwareHash_4Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareHash_5() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareHash[5];
}
void GPSExtendedStatus::setFirmwareHash_5(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareHash[5] != value;
   data.FirmwareHash[5] = value;
   mutex->unlock();
   if (changed) emit FirmwareHash_5Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareHash_6() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareHash[6];
}
void GPSExtendedStatus::setFirmwareHash_6(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareHash[6] != value;
   data.FirmwareHash[6] = value;
   mutex->unlock();
   if (changed) emit FirmwareHash_6Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareHash_7() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareHash[7];
}
void GPSExtendedStatus::setFirmwareHash_7(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareHash[7] != value;
   data.FirmwareHash[7] = value;
   mutex->unlock();
   if (changed) emit FirmwareHash_7Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[index];
}
void GPSExtendedStatus::setFirmwareTag(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[index] != value;
   data.FirmwareTag[index] = value;
   mutex->unlock();
   if (changed) emit FirmwareTagChanged(index,value);
}

quint8 GPSExtendedStatus::getFirmwareTag_0() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[0];
}
void GPSExtendedStatus::setFirmwareTag_0(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[0] != value;
   data.FirmwareTag[0] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_0Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_1() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[1];
}
void GPSExtendedStatus::setFirmwareTag_1(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[1] != value;
   data.FirmwareTag[1] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_1Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_2() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[2];
}
void GPSExtendedStatus::setFirmwareTag_2(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[2] != value;
   data.FirmwareTag[2] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_2Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_3() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[3];
}
void GPSExtendedStatus::setFirmwareTag_3(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[3] != value;
   data.FirmwareTag[3] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_3Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_4() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[4];
}
void GPSExtendedStatus::setFirmwareTag_4(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[4] != value;
   data.FirmwareTag[4] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_4Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_5() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[5];
}
void GPSExtendedStatus::setFirmwareTag_5(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[5] != value;
   data.FirmwareTag[5] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_5Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_6() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[6];
}
void GPSExtendedStatus::setFirmwareTag_6(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[6] != value;
   data.FirmwareTag[6] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_6Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_7() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[7];
}
void GPSExtendedStatus::setFirmwareTag_7(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[7] != value;
   data.FirmwareTag[7] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_7Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_8() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[8];
}
void GPSExtendedStatus::setFirmwareTag_8(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[8] != value;
   data.FirmwareTag[8] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_8Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_9() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[9];
}
void GPSExtendedStatus::setFirmwareTag_9(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[9] != value;
   data.FirmwareTag[9] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_9Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_10() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[10];
}
void GPSExtendedStatus::setFirmwareTag_10(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[10] != value;
   data.FirmwareTag[10] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_10Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_11() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[11];
}
void GPSExtendedStatus::setFirmwareTag_11(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[11] != value;
   data.FirmwareTag[11] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_11Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_12() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[12];
}
void GPSExtendedStatus::setFirmwareTag_12(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[12] != value;
   data.FirmwareTag[12] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_12Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_13() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[13];
}
void GPSExtendedStatus::setFirmwareTag_13(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[13] != value;
   data.FirmwareTag[13] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_13Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_14() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[14];
}
void GPSExtendedStatus::setFirmwareTag_14(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[14] != value;
   data.FirmwareTag[14] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_14Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_15() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[15];
}
void GPSExtendedStatus::setFirmwareTag_15(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[15] != value;
   data.FirmwareTag[15] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_15Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_16() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[16];
}
void GPSExtendedStatus::setFirmwareTag_16(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[16] != value;
   data.FirmwareTag[16] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_16Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_17() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[17];
}
void GPSExtendedStatus::setFirmwareTag_17(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[17] != value;
   data.FirmwareTag[17] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_17Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_18() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[18];
}
void GPSExtendedStatus::setFirmwareTag_18(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[18] != value;
   data.FirmwareTag[18] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_18Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_19() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[19];
}
void GPSExtendedStatus::setFirmwareTag_19(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[19] != value;
   data.FirmwareTag[19] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_19Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_20() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[20];
}
void GPSExtendedStatus::setFirmwareTag_20(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[20] != value;
   data.FirmwareTag[20] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_20Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_21() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[21];
}
void GPSExtendedStatus::setFirmwareTag_21(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[21] != value;
   data.FirmwareTag[21] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_21Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_22() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[22];
}
void GPSExtendedStatus::setFirmwareTag_22(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[22] != value;
   data.FirmwareTag[22] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_22Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_23() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[23];
}
void GPSExtendedStatus::setFirmwareTag_23(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[23] != value;
   data.FirmwareTag[23] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_23Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_24() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[24];
}
void GPSExtendedStatus::setFirmwareTag_24(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[24] != value;
   data.FirmwareTag[24] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_24Changed(value);
}

quint8 GPSExtendedStatus::getFirmwareTag_25() const
{
   QMutexLocker locker(mutex);
   return data.FirmwareTag[25];
}
void GPSExtendedStatus::setFirmwareTag_25(quint8 value)
{
   mutex->lock();
   bool changed = data.FirmwareTag[25] != value;
   data.FirmwareTag[25] = value;
   mutex->unlock();
   if (changed) emit FirmwareTag_25Changed(value);
}


