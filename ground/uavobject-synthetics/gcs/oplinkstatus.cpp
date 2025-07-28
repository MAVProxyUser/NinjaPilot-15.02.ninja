/**
 ******************************************************************************
 *
 * @file       oplinkstatus.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: oplinkstatus.xml.
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

#include "oplinkstatus.h"
#include "uavobjectfield.h"

const QString OPLinkStatus::NAME = QString("OPLinkStatus");
const QString OPLinkStatus::DESCRIPTION = QString("OPLink device status.");
const QString OPLinkStatus::CATEGORY = QString("System");

/**
 * Constructor
 */
OPLinkStatus::OPLinkStatus(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList DeviceIDElemNames;
    DeviceIDElemNames.append("0");
    fields.append( new UAVObjectField(QString("DeviceID"), tr(""), QString("hex"), UAVObjectField::UINT32, DeviceIDElemNames, QStringList(), QString("")));
    QStringList PairIDsElemNames;
    PairIDsElemNames.append("0");
    PairIDsElemNames.append("1");
    PairIDsElemNames.append("2");
    PairIDsElemNames.append("3");
    fields.append( new UAVObjectField(QString("PairIDs"), tr(""), QString("hex"), UAVObjectField::UINT32, PairIDsElemNames, QStringList(), QString("")));
    QStringList BoardRevisionElemNames;
    BoardRevisionElemNames.append("0");
    fields.append( new UAVObjectField(QString("BoardRevision"), tr(""), QString(""), UAVObjectField::UINT16, BoardRevisionElemNames, QStringList(), QString("")));
    QStringList HeapRemainingElemNames;
    HeapRemainingElemNames.append("0");
    fields.append( new UAVObjectField(QString("HeapRemaining"), tr(""), QString("bytes"), UAVObjectField::UINT16, HeapRemainingElemNames, QStringList(), QString("")));
    QStringList UAVTalkErrorsElemNames;
    UAVTalkErrorsElemNames.append("0");
    fields.append( new UAVObjectField(QString("UAVTalkErrors"), tr(""), QString(""), UAVObjectField::UINT16, UAVTalkErrorsElemNames, QStringList(), QString("")));
    QStringList TXRateElemNames;
    TXRateElemNames.append("0");
    fields.append( new UAVObjectField(QString("TXRate"), tr(""), QString("Bps"), UAVObjectField::UINT16, TXRateElemNames, QStringList(), QString("")));
    QStringList RXRateElemNames;
    RXRateElemNames.append("0");
    fields.append( new UAVObjectField(QString("RXRate"), tr(""), QString("Bps"), UAVObjectField::UINT16, RXRateElemNames, QStringList(), QString("")));
    QStringList TXSeqElemNames;
    TXSeqElemNames.append("0");
    fields.append( new UAVObjectField(QString("TXSeq"), tr(""), QString(""), UAVObjectField::UINT16, TXSeqElemNames, QStringList(), QString("")));
    QStringList RXSeqElemNames;
    RXSeqElemNames.append("0");
    fields.append( new UAVObjectField(QString("RXSeq"), tr(""), QString(""), UAVObjectField::UINT16, RXSeqElemNames, QStringList(), QString("")));
    QStringList DescriptionElemNames;
    DescriptionElemNames.append("0");
    DescriptionElemNames.append("1");
    DescriptionElemNames.append("2");
    DescriptionElemNames.append("3");
    DescriptionElemNames.append("4");
    DescriptionElemNames.append("5");
    DescriptionElemNames.append("6");
    DescriptionElemNames.append("7");
    DescriptionElemNames.append("8");
    DescriptionElemNames.append("9");
    DescriptionElemNames.append("10");
    DescriptionElemNames.append("11");
    DescriptionElemNames.append("12");
    DescriptionElemNames.append("13");
    DescriptionElemNames.append("14");
    DescriptionElemNames.append("15");
    DescriptionElemNames.append("16");
    DescriptionElemNames.append("17");
    DescriptionElemNames.append("18");
    DescriptionElemNames.append("19");
    DescriptionElemNames.append("20");
    DescriptionElemNames.append("21");
    DescriptionElemNames.append("22");
    DescriptionElemNames.append("23");
    DescriptionElemNames.append("24");
    DescriptionElemNames.append("25");
    DescriptionElemNames.append("26");
    DescriptionElemNames.append("27");
    DescriptionElemNames.append("28");
    DescriptionElemNames.append("29");
    DescriptionElemNames.append("30");
    DescriptionElemNames.append("31");
    DescriptionElemNames.append("32");
    DescriptionElemNames.append("33");
    DescriptionElemNames.append("34");
    DescriptionElemNames.append("35");
    DescriptionElemNames.append("36");
    DescriptionElemNames.append("37");
    DescriptionElemNames.append("38");
    DescriptionElemNames.append("39");
    fields.append( new UAVObjectField(QString("Description"), tr(""), QString(""), UAVObjectField::UINT8, DescriptionElemNames, QStringList(), QString("")));
    QStringList CPUSerialElemNames;
    CPUSerialElemNames.append("0");
    CPUSerialElemNames.append("1");
    CPUSerialElemNames.append("2");
    CPUSerialElemNames.append("3");
    CPUSerialElemNames.append("4");
    CPUSerialElemNames.append("5");
    CPUSerialElemNames.append("6");
    CPUSerialElemNames.append("7");
    CPUSerialElemNames.append("8");
    CPUSerialElemNames.append("9");
    CPUSerialElemNames.append("10");
    CPUSerialElemNames.append("11");
    fields.append( new UAVObjectField(QString("CPUSerial"), tr(""), QString("hex"), UAVObjectField::UINT8, CPUSerialElemNames, QStringList(), QString("")));
    QStringList BoardTypeElemNames;
    BoardTypeElemNames.append("0");
    fields.append( new UAVObjectField(QString("BoardType"), tr(""), QString(""), UAVObjectField::UINT8, BoardTypeElemNames, QStringList(), QString("")));
    QStringList RxGoodElemNames;
    RxGoodElemNames.append("0");
    fields.append( new UAVObjectField(QString("RxGood"), tr(""), QString("%"), UAVObjectField::UINT8, RxGoodElemNames, QStringList(), QString("")));
    QStringList RxCorrectedElemNames;
    RxCorrectedElemNames.append("0");
    fields.append( new UAVObjectField(QString("RxCorrected"), tr(""), QString("%"), UAVObjectField::UINT8, RxCorrectedElemNames, QStringList(), QString("")));
    QStringList RxErrorsElemNames;
    RxErrorsElemNames.append("0");
    fields.append( new UAVObjectField(QString("RxErrors"), tr(""), QString("%"), UAVObjectField::UINT8, RxErrorsElemNames, QStringList(), QString("")));
    QStringList RxMissedElemNames;
    RxMissedElemNames.append("0");
    fields.append( new UAVObjectField(QString("RxMissed"), tr(""), QString("%"), UAVObjectField::UINT8, RxMissedElemNames, QStringList(), QString("")));
    QStringList RxFailureElemNames;
    RxFailureElemNames.append("0");
    fields.append( new UAVObjectField(QString("RxFailure"), tr(""), QString("%"), UAVObjectField::UINT8, RxFailureElemNames, QStringList(), QString("")));
    QStringList TxDroppedElemNames;
    TxDroppedElemNames.append("0");
    fields.append( new UAVObjectField(QString("TxDropped"), tr(""), QString("%"), UAVObjectField::UINT8, TxDroppedElemNames, QStringList(), QString("")));
    QStringList TxFailureElemNames;
    TxFailureElemNames.append("0");
    fields.append( new UAVObjectField(QString("TxFailure"), tr(""), QString("%"), UAVObjectField::UINT8, TxFailureElemNames, QStringList(), QString("")));
    QStringList ResetsElemNames;
    ResetsElemNames.append("0");
    fields.append( new UAVObjectField(QString("Resets"), tr(""), QString(""), UAVObjectField::UINT8, ResetsElemNames, QStringList(), QString("")));
    QStringList TimeoutsElemNames;
    TimeoutsElemNames.append("0");
    fields.append( new UAVObjectField(QString("Timeouts"), tr(""), QString(""), UAVObjectField::UINT8, TimeoutsElemNames, QStringList(), QString("")));
    QStringList RSSIElemNames;
    RSSIElemNames.append("0");
    fields.append( new UAVObjectField(QString("RSSI"), tr(""), QString("dBm"), UAVObjectField::INT8, RSSIElemNames, QStringList(), QString("")));
    QStringList LinkQualityElemNames;
    LinkQualityElemNames.append("0");
    fields.append( new UAVObjectField(QString("LinkQuality"), tr(""), QString(""), UAVObjectField::UINT8, LinkQualityElemNames, QStringList(), QString("")));
    QStringList LinkStateElemNames;
    LinkStateElemNames.append("0");
    QStringList LinkStateEnumOptions;
    LinkStateEnumOptions.append("Disabled");
    LinkStateEnumOptions.append("Enabled");
    LinkStateEnumOptions.append("Disconnected");
    LinkStateEnumOptions.append("Connecting");
    LinkStateEnumOptions.append("Connected");
    fields.append( new UAVObjectField(QString("LinkState"), tr(""), QString("function"), UAVObjectField::ENUM, LinkStateElemNames, LinkStateEnumOptions, QString("")));
    QStringList PairSignalStrengthsElemNames;
    PairSignalStrengthsElemNames.append("0");
    PairSignalStrengthsElemNames.append("1");
    PairSignalStrengthsElemNames.append("2");
    PairSignalStrengthsElemNames.append("3");
    fields.append( new UAVObjectField(QString("PairSignalStrengths"), tr(""), QString("dBm"), UAVObjectField::INT8, PairSignalStrengthsElemNames, QStringList(), QString("")));

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
UAVObject::Metadata OPLinkStatus::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READONLY << UAVOBJ_GCS_ACCESS_SHIFT |
        0 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        0 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_THROTTLED << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_LOGGING_UPDATE_MODE_SHIFT;
    metadata.flightTelemetryUpdatePeriod = 500;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void OPLinkStatus::setDefaultFieldValues()
{
    data.DeviceID = 0;
    data.PairIDs[0] = 0;
    data.PairIDs[1] = 0;
    data.PairIDs[2] = 0;
    data.PairIDs[3] = 0;
    data.UAVTalkErrors = 0;
    data.TXRate = 0;
    data.RXRate = 0;
    data.TXSeq = 0;
    data.RXSeq = 0;
    data.RxGood = 0;
    data.RxCorrected = 0;
    data.RxErrors = 0;
    data.RxMissed = 0;
    data.RxFailure = 0;
    data.TxDropped = 0;
    data.TxFailure = 0;
    data.Resets = 0;
    data.Timeouts = 0;
    data.RSSI = 0;
    data.LinkQuality = 0;
    data.LinkState = 0;
    data.PairSignalStrengths[0] = -127;
    data.PairSignalStrengths[1] = -127;
    data.PairSignalStrengths[2] = -127;
    data.PairSignalStrengths[3] = -127;

}

/**
 * Get the object data fields
 */
OPLinkStatus::DataFields OPLinkStatus::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void OPLinkStatus::setData(const DataFields& data)
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

void OPLinkStatus::emitNotifications()
{
            //if (data.DeviceID != oldData.DeviceID)
            emit DeviceIDChanged(data.DeviceID);
        //if (data.PairIDs[0] != oldData.PairIDs[0])
            emit PairIDs_0Changed(data.PairIDs[0]);
        //if (data.PairIDs[1] != oldData.PairIDs[1])
            emit PairIDs_1Changed(data.PairIDs[1]);
        //if (data.PairIDs[2] != oldData.PairIDs[2])
            emit PairIDs_2Changed(data.PairIDs[2]);
        //if (data.PairIDs[3] != oldData.PairIDs[3])
            emit PairIDs_3Changed(data.PairIDs[3]);
        //if (data.BoardRevision != oldData.BoardRevision)
            emit BoardRevisionChanged(data.BoardRevision);
        //if (data.HeapRemaining != oldData.HeapRemaining)
            emit HeapRemainingChanged(data.HeapRemaining);
        //if (data.UAVTalkErrors != oldData.UAVTalkErrors)
            emit UAVTalkErrorsChanged(data.UAVTalkErrors);
        //if (data.TXRate != oldData.TXRate)
            emit TXRateChanged(data.TXRate);
        //if (data.RXRate != oldData.RXRate)
            emit RXRateChanged(data.RXRate);
        //if (data.TXSeq != oldData.TXSeq)
            emit TXSeqChanged(data.TXSeq);
        //if (data.RXSeq != oldData.RXSeq)
            emit RXSeqChanged(data.RXSeq);
        //if (data.CPUSerial[0] != oldData.CPUSerial[0])
            emit CPUSerial_0Changed(data.CPUSerial[0]);
        //if (data.CPUSerial[1] != oldData.CPUSerial[1])
            emit CPUSerial_1Changed(data.CPUSerial[1]);
        //if (data.CPUSerial[2] != oldData.CPUSerial[2])
            emit CPUSerial_2Changed(data.CPUSerial[2]);
        //if (data.CPUSerial[3] != oldData.CPUSerial[3])
            emit CPUSerial_3Changed(data.CPUSerial[3]);
        //if (data.CPUSerial[4] != oldData.CPUSerial[4])
            emit CPUSerial_4Changed(data.CPUSerial[4]);
        //if (data.CPUSerial[5] != oldData.CPUSerial[5])
            emit CPUSerial_5Changed(data.CPUSerial[5]);
        //if (data.CPUSerial[6] != oldData.CPUSerial[6])
            emit CPUSerial_6Changed(data.CPUSerial[6]);
        //if (data.CPUSerial[7] != oldData.CPUSerial[7])
            emit CPUSerial_7Changed(data.CPUSerial[7]);
        //if (data.CPUSerial[8] != oldData.CPUSerial[8])
            emit CPUSerial_8Changed(data.CPUSerial[8]);
        //if (data.CPUSerial[9] != oldData.CPUSerial[9])
            emit CPUSerial_9Changed(data.CPUSerial[9]);
        //if (data.CPUSerial[10] != oldData.CPUSerial[10])
            emit CPUSerial_10Changed(data.CPUSerial[10]);
        //if (data.CPUSerial[11] != oldData.CPUSerial[11])
            emit CPUSerial_11Changed(data.CPUSerial[11]);
        //if (data.BoardType != oldData.BoardType)
            emit BoardTypeChanged(data.BoardType);
        //if (data.RxGood != oldData.RxGood)
            emit RxGoodChanged(data.RxGood);
        //if (data.RxCorrected != oldData.RxCorrected)
            emit RxCorrectedChanged(data.RxCorrected);
        //if (data.RxErrors != oldData.RxErrors)
            emit RxErrorsChanged(data.RxErrors);
        //if (data.RxMissed != oldData.RxMissed)
            emit RxMissedChanged(data.RxMissed);
        //if (data.RxFailure != oldData.RxFailure)
            emit RxFailureChanged(data.RxFailure);
        //if (data.TxDropped != oldData.TxDropped)
            emit TxDroppedChanged(data.TxDropped);
        //if (data.TxFailure != oldData.TxFailure)
            emit TxFailureChanged(data.TxFailure);
        //if (data.Resets != oldData.Resets)
            emit ResetsChanged(data.Resets);
        //if (data.Timeouts != oldData.Timeouts)
            emit TimeoutsChanged(data.Timeouts);
        //if (data.RSSI != oldData.RSSI)
            emit RSSIChanged(data.RSSI);
        //if (data.LinkQuality != oldData.LinkQuality)
            emit LinkQualityChanged(data.LinkQuality);
        //if (data.LinkState != oldData.LinkState)
            emit LinkStateChanged(data.LinkState);
        //if (data.PairSignalStrengths[0] != oldData.PairSignalStrengths[0])
            emit PairSignalStrengths_0Changed(data.PairSignalStrengths[0]);
        //if (data.PairSignalStrengths[1] != oldData.PairSignalStrengths[1])
            emit PairSignalStrengths_1Changed(data.PairSignalStrengths[1]);
        //if (data.PairSignalStrengths[2] != oldData.PairSignalStrengths[2])
            emit PairSignalStrengths_2Changed(data.PairSignalStrengths[2]);
        //if (data.PairSignalStrengths[3] != oldData.PairSignalStrengths[3])
            emit PairSignalStrengths_3Changed(data.PairSignalStrengths[3]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *OPLinkStatus::clone(quint32 instID)
{
    OPLinkStatus *obj = new OPLinkStatus();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *OPLinkStatus::dirtyClone()
{
    OPLinkStatus *obj = new OPLinkStatus();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
OPLinkStatus *OPLinkStatus::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<OPLinkStatus *>(objMngr->getObject(OPLinkStatus::OBJID, instID));
}

quint32 OPLinkStatus::getDeviceID() const
{
   QMutexLocker locker(mutex);
   return data.DeviceID;
}
void OPLinkStatus::setDeviceID(quint32 value)
{
   mutex->lock();
   bool changed = data.DeviceID != value;
   data.DeviceID = value;
   mutex->unlock();
   if (changed) emit DeviceIDChanged(value);
}

quint32 OPLinkStatus::getPairIDs(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.PairIDs[index];
}
void OPLinkStatus::setPairIDs(quint32 index, quint32 value)
{
   mutex->lock();
   bool changed = data.PairIDs[index] != value;
   data.PairIDs[index] = value;
   mutex->unlock();
   if (changed) emit PairIDsChanged(index,value);
}

quint32 OPLinkStatus::getPairIDs_0() const
{
   QMutexLocker locker(mutex);
   return data.PairIDs[0];
}
void OPLinkStatus::setPairIDs_0(quint32 value)
{
   mutex->lock();
   bool changed = data.PairIDs[0] != value;
   data.PairIDs[0] = value;
   mutex->unlock();
   if (changed) emit PairIDs_0Changed(value);
}

quint32 OPLinkStatus::getPairIDs_1() const
{
   QMutexLocker locker(mutex);
   return data.PairIDs[1];
}
void OPLinkStatus::setPairIDs_1(quint32 value)
{
   mutex->lock();
   bool changed = data.PairIDs[1] != value;
   data.PairIDs[1] = value;
   mutex->unlock();
   if (changed) emit PairIDs_1Changed(value);
}

quint32 OPLinkStatus::getPairIDs_2() const
{
   QMutexLocker locker(mutex);
   return data.PairIDs[2];
}
void OPLinkStatus::setPairIDs_2(quint32 value)
{
   mutex->lock();
   bool changed = data.PairIDs[2] != value;
   data.PairIDs[2] = value;
   mutex->unlock();
   if (changed) emit PairIDs_2Changed(value);
}

quint32 OPLinkStatus::getPairIDs_3() const
{
   QMutexLocker locker(mutex);
   return data.PairIDs[3];
}
void OPLinkStatus::setPairIDs_3(quint32 value)
{
   mutex->lock();
   bool changed = data.PairIDs[3] != value;
   data.PairIDs[3] = value;
   mutex->unlock();
   if (changed) emit PairIDs_3Changed(value);
}

quint16 OPLinkStatus::getBoardRevision() const
{
   QMutexLocker locker(mutex);
   return data.BoardRevision;
}
void OPLinkStatus::setBoardRevision(quint16 value)
{
   mutex->lock();
   bool changed = data.BoardRevision != value;
   data.BoardRevision = value;
   mutex->unlock();
   if (changed) emit BoardRevisionChanged(value);
}

quint16 OPLinkStatus::getHeapRemaining() const
{
   QMutexLocker locker(mutex);
   return data.HeapRemaining;
}
void OPLinkStatus::setHeapRemaining(quint16 value)
{
   mutex->lock();
   bool changed = data.HeapRemaining != value;
   data.HeapRemaining = value;
   mutex->unlock();
   if (changed) emit HeapRemainingChanged(value);
}

quint16 OPLinkStatus::getUAVTalkErrors() const
{
   QMutexLocker locker(mutex);
   return data.UAVTalkErrors;
}
void OPLinkStatus::setUAVTalkErrors(quint16 value)
{
   mutex->lock();
   bool changed = data.UAVTalkErrors != value;
   data.UAVTalkErrors = value;
   mutex->unlock();
   if (changed) emit UAVTalkErrorsChanged(value);
}

quint16 OPLinkStatus::getTXRate() const
{
   QMutexLocker locker(mutex);
   return data.TXRate;
}
void OPLinkStatus::setTXRate(quint16 value)
{
   mutex->lock();
   bool changed = data.TXRate != value;
   data.TXRate = value;
   mutex->unlock();
   if (changed) emit TXRateChanged(value);
}

quint16 OPLinkStatus::getRXRate() const
{
   QMutexLocker locker(mutex);
   return data.RXRate;
}
void OPLinkStatus::setRXRate(quint16 value)
{
   mutex->lock();
   bool changed = data.RXRate != value;
   data.RXRate = value;
   mutex->unlock();
   if (changed) emit RXRateChanged(value);
}

quint16 OPLinkStatus::getTXSeq() const
{
   QMutexLocker locker(mutex);
   return data.TXSeq;
}
void OPLinkStatus::setTXSeq(quint16 value)
{
   mutex->lock();
   bool changed = data.TXSeq != value;
   data.TXSeq = value;
   mutex->unlock();
   if (changed) emit TXSeqChanged(value);
}

quint16 OPLinkStatus::getRXSeq() const
{
   QMutexLocker locker(mutex);
   return data.RXSeq;
}
void OPLinkStatus::setRXSeq(quint16 value)
{
   mutex->lock();
   bool changed = data.RXSeq != value;
   data.RXSeq = value;
   mutex->unlock();
   if (changed) emit RXSeqChanged(value);
}

quint8 OPLinkStatus::getCPUSerial(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[index];
}
void OPLinkStatus::setCPUSerial(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[index] != value;
   data.CPUSerial[index] = value;
   mutex->unlock();
   if (changed) emit CPUSerialChanged(index,value);
}

quint8 OPLinkStatus::getCPUSerial_0() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[0];
}
void OPLinkStatus::setCPUSerial_0(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[0] != value;
   data.CPUSerial[0] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_0Changed(value);
}

quint8 OPLinkStatus::getCPUSerial_1() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[1];
}
void OPLinkStatus::setCPUSerial_1(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[1] != value;
   data.CPUSerial[1] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_1Changed(value);
}

quint8 OPLinkStatus::getCPUSerial_2() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[2];
}
void OPLinkStatus::setCPUSerial_2(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[2] != value;
   data.CPUSerial[2] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_2Changed(value);
}

quint8 OPLinkStatus::getCPUSerial_3() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[3];
}
void OPLinkStatus::setCPUSerial_3(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[3] != value;
   data.CPUSerial[3] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_3Changed(value);
}

quint8 OPLinkStatus::getCPUSerial_4() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[4];
}
void OPLinkStatus::setCPUSerial_4(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[4] != value;
   data.CPUSerial[4] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_4Changed(value);
}

quint8 OPLinkStatus::getCPUSerial_5() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[5];
}
void OPLinkStatus::setCPUSerial_5(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[5] != value;
   data.CPUSerial[5] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_5Changed(value);
}

quint8 OPLinkStatus::getCPUSerial_6() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[6];
}
void OPLinkStatus::setCPUSerial_6(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[6] != value;
   data.CPUSerial[6] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_6Changed(value);
}

quint8 OPLinkStatus::getCPUSerial_7() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[7];
}
void OPLinkStatus::setCPUSerial_7(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[7] != value;
   data.CPUSerial[7] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_7Changed(value);
}

quint8 OPLinkStatus::getCPUSerial_8() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[8];
}
void OPLinkStatus::setCPUSerial_8(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[8] != value;
   data.CPUSerial[8] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_8Changed(value);
}

quint8 OPLinkStatus::getCPUSerial_9() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[9];
}
void OPLinkStatus::setCPUSerial_9(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[9] != value;
   data.CPUSerial[9] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_9Changed(value);
}

quint8 OPLinkStatus::getCPUSerial_10() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[10];
}
void OPLinkStatus::setCPUSerial_10(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[10] != value;
   data.CPUSerial[10] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_10Changed(value);
}

quint8 OPLinkStatus::getCPUSerial_11() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[11];
}
void OPLinkStatus::setCPUSerial_11(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[11] != value;
   data.CPUSerial[11] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_11Changed(value);
}

quint8 OPLinkStatus::getBoardType() const
{
   QMutexLocker locker(mutex);
   return data.BoardType;
}
void OPLinkStatus::setBoardType(quint8 value)
{
   mutex->lock();
   bool changed = data.BoardType != value;
   data.BoardType = value;
   mutex->unlock();
   if (changed) emit BoardTypeChanged(value);
}

quint8 OPLinkStatus::getRxGood() const
{
   QMutexLocker locker(mutex);
   return data.RxGood;
}
void OPLinkStatus::setRxGood(quint8 value)
{
   mutex->lock();
   bool changed = data.RxGood != value;
   data.RxGood = value;
   mutex->unlock();
   if (changed) emit RxGoodChanged(value);
}

quint8 OPLinkStatus::getRxCorrected() const
{
   QMutexLocker locker(mutex);
   return data.RxCorrected;
}
void OPLinkStatus::setRxCorrected(quint8 value)
{
   mutex->lock();
   bool changed = data.RxCorrected != value;
   data.RxCorrected = value;
   mutex->unlock();
   if (changed) emit RxCorrectedChanged(value);
}

quint8 OPLinkStatus::getRxErrors() const
{
   QMutexLocker locker(mutex);
   return data.RxErrors;
}
void OPLinkStatus::setRxErrors(quint8 value)
{
   mutex->lock();
   bool changed = data.RxErrors != value;
   data.RxErrors = value;
   mutex->unlock();
   if (changed) emit RxErrorsChanged(value);
}

quint8 OPLinkStatus::getRxMissed() const
{
   QMutexLocker locker(mutex);
   return data.RxMissed;
}
void OPLinkStatus::setRxMissed(quint8 value)
{
   mutex->lock();
   bool changed = data.RxMissed != value;
   data.RxMissed = value;
   mutex->unlock();
   if (changed) emit RxMissedChanged(value);
}

quint8 OPLinkStatus::getRxFailure() const
{
   QMutexLocker locker(mutex);
   return data.RxFailure;
}
void OPLinkStatus::setRxFailure(quint8 value)
{
   mutex->lock();
   bool changed = data.RxFailure != value;
   data.RxFailure = value;
   mutex->unlock();
   if (changed) emit RxFailureChanged(value);
}

quint8 OPLinkStatus::getTxDropped() const
{
   QMutexLocker locker(mutex);
   return data.TxDropped;
}
void OPLinkStatus::setTxDropped(quint8 value)
{
   mutex->lock();
   bool changed = data.TxDropped != value;
   data.TxDropped = value;
   mutex->unlock();
   if (changed) emit TxDroppedChanged(value);
}

quint8 OPLinkStatus::getTxFailure() const
{
   QMutexLocker locker(mutex);
   return data.TxFailure;
}
void OPLinkStatus::setTxFailure(quint8 value)
{
   mutex->lock();
   bool changed = data.TxFailure != value;
   data.TxFailure = value;
   mutex->unlock();
   if (changed) emit TxFailureChanged(value);
}

quint8 OPLinkStatus::getResets() const
{
   QMutexLocker locker(mutex);
   return data.Resets;
}
void OPLinkStatus::setResets(quint8 value)
{
   mutex->lock();
   bool changed = data.Resets != value;
   data.Resets = value;
   mutex->unlock();
   if (changed) emit ResetsChanged(value);
}

quint8 OPLinkStatus::getTimeouts() const
{
   QMutexLocker locker(mutex);
   return data.Timeouts;
}
void OPLinkStatus::setTimeouts(quint8 value)
{
   mutex->lock();
   bool changed = data.Timeouts != value;
   data.Timeouts = value;
   mutex->unlock();
   if (changed) emit TimeoutsChanged(value);
}

qint8 OPLinkStatus::getRSSI() const
{
   QMutexLocker locker(mutex);
   return data.RSSI;
}
void OPLinkStatus::setRSSI(qint8 value)
{
   mutex->lock();
   bool changed = data.RSSI != value;
   data.RSSI = value;
   mutex->unlock();
   if (changed) emit RSSIChanged(value);
}

quint8 OPLinkStatus::getLinkQuality() const
{
   QMutexLocker locker(mutex);
   return data.LinkQuality;
}
void OPLinkStatus::setLinkQuality(quint8 value)
{
   mutex->lock();
   bool changed = data.LinkQuality != value;
   data.LinkQuality = value;
   mutex->unlock();
   if (changed) emit LinkQualityChanged(value);
}

quint8 OPLinkStatus::getLinkState() const
{
   QMutexLocker locker(mutex);
   return data.LinkState;
}
void OPLinkStatus::setLinkState(quint8 value)
{
   mutex->lock();
   bool changed = data.LinkState != value;
   data.LinkState = value;
   mutex->unlock();
   if (changed) emit LinkStateChanged(value);
}

qint8 OPLinkStatus::getPairSignalStrengths(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.PairSignalStrengths[index];
}
void OPLinkStatus::setPairSignalStrengths(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.PairSignalStrengths[index] != value;
   data.PairSignalStrengths[index] = value;
   mutex->unlock();
   if (changed) emit PairSignalStrengthsChanged(index,value);
}

qint8 OPLinkStatus::getPairSignalStrengths_0() const
{
   QMutexLocker locker(mutex);
   return data.PairSignalStrengths[0];
}
void OPLinkStatus::setPairSignalStrengths_0(qint8 value)
{
   mutex->lock();
   bool changed = data.PairSignalStrengths[0] != value;
   data.PairSignalStrengths[0] = value;
   mutex->unlock();
   if (changed) emit PairSignalStrengths_0Changed(value);
}

qint8 OPLinkStatus::getPairSignalStrengths_1() const
{
   QMutexLocker locker(mutex);
   return data.PairSignalStrengths[1];
}
void OPLinkStatus::setPairSignalStrengths_1(qint8 value)
{
   mutex->lock();
   bool changed = data.PairSignalStrengths[1] != value;
   data.PairSignalStrengths[1] = value;
   mutex->unlock();
   if (changed) emit PairSignalStrengths_1Changed(value);
}

qint8 OPLinkStatus::getPairSignalStrengths_2() const
{
   QMutexLocker locker(mutex);
   return data.PairSignalStrengths[2];
}
void OPLinkStatus::setPairSignalStrengths_2(qint8 value)
{
   mutex->lock();
   bool changed = data.PairSignalStrengths[2] != value;
   data.PairSignalStrengths[2] = value;
   mutex->unlock();
   if (changed) emit PairSignalStrengths_2Changed(value);
}

qint8 OPLinkStatus::getPairSignalStrengths_3() const
{
   QMutexLocker locker(mutex);
   return data.PairSignalStrengths[3];
}
void OPLinkStatus::setPairSignalStrengths_3(qint8 value)
{
   mutex->lock();
   bool changed = data.PairSignalStrengths[3] != value;
   data.PairSignalStrengths[3] = value;
   mutex->unlock();
   if (changed) emit PairSignalStrengths_3Changed(value);
}


