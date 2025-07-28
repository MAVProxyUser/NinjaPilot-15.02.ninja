/**
 ******************************************************************************
 *
 * @file       firmwareiapobj.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: firmwareiapobj.xml.
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

#include "firmwareiapobj.h"
#include "uavobjectfield.h"

const QString FirmwareIAPObj::NAME = QString("FirmwareIAPObj");
const QString FirmwareIAPObj::DESCRIPTION = QString("Queries board for SN, model, revision, and sends reset command");
const QString FirmwareIAPObj::CATEGORY = QString("System");

/**
 * Constructor
 */
FirmwareIAPObj::FirmwareIAPObj(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList crcElemNames;
    crcElemNames.append("0");
    fields.append( new UAVObjectField(QString("crc"), tr(""), QString(""), UAVObjectField::UINT32, crcElemNames, QStringList(), QString("")));
    QStringList CommandElemNames;
    CommandElemNames.append("0");
    fields.append( new UAVObjectField(QString("Command"), tr(""), QString(""), UAVObjectField::UINT16, CommandElemNames, QStringList(), QString("")));
    QStringList BoardRevisionElemNames;
    BoardRevisionElemNames.append("0");
    fields.append( new UAVObjectField(QString("BoardRevision"), tr(""), QString(""), UAVObjectField::UINT16, BoardRevisionElemNames, QStringList(), QString("")));
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
    DescriptionElemNames.append("40");
    DescriptionElemNames.append("41");
    DescriptionElemNames.append("42");
    DescriptionElemNames.append("43");
    DescriptionElemNames.append("44");
    DescriptionElemNames.append("45");
    DescriptionElemNames.append("46");
    DescriptionElemNames.append("47");
    DescriptionElemNames.append("48");
    DescriptionElemNames.append("49");
    DescriptionElemNames.append("50");
    DescriptionElemNames.append("51");
    DescriptionElemNames.append("52");
    DescriptionElemNames.append("53");
    DescriptionElemNames.append("54");
    DescriptionElemNames.append("55");
    DescriptionElemNames.append("56");
    DescriptionElemNames.append("57");
    DescriptionElemNames.append("58");
    DescriptionElemNames.append("59");
    DescriptionElemNames.append("60");
    DescriptionElemNames.append("61");
    DescriptionElemNames.append("62");
    DescriptionElemNames.append("63");
    DescriptionElemNames.append("64");
    DescriptionElemNames.append("65");
    DescriptionElemNames.append("66");
    DescriptionElemNames.append("67");
    DescriptionElemNames.append("68");
    DescriptionElemNames.append("69");
    DescriptionElemNames.append("70");
    DescriptionElemNames.append("71");
    DescriptionElemNames.append("72");
    DescriptionElemNames.append("73");
    DescriptionElemNames.append("74");
    DescriptionElemNames.append("75");
    DescriptionElemNames.append("76");
    DescriptionElemNames.append("77");
    DescriptionElemNames.append("78");
    DescriptionElemNames.append("79");
    DescriptionElemNames.append("80");
    DescriptionElemNames.append("81");
    DescriptionElemNames.append("82");
    DescriptionElemNames.append("83");
    DescriptionElemNames.append("84");
    DescriptionElemNames.append("85");
    DescriptionElemNames.append("86");
    DescriptionElemNames.append("87");
    DescriptionElemNames.append("88");
    DescriptionElemNames.append("89");
    DescriptionElemNames.append("90");
    DescriptionElemNames.append("91");
    DescriptionElemNames.append("92");
    DescriptionElemNames.append("93");
    DescriptionElemNames.append("94");
    DescriptionElemNames.append("95");
    DescriptionElemNames.append("96");
    DescriptionElemNames.append("97");
    DescriptionElemNames.append("98");
    DescriptionElemNames.append("99");
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
    QStringList BootloaderRevisionElemNames;
    BootloaderRevisionElemNames.append("0");
    fields.append( new UAVObjectField(QString("BootloaderRevision"), tr(""), QString(""), UAVObjectField::UINT8, BootloaderRevisionElemNames, QStringList(), QString("")));
    QStringList ArmResetElemNames;
    ArmResetElemNames.append("0");
    fields.append( new UAVObjectField(QString("ArmReset"), tr(""), QString(""), UAVObjectField::UINT8, ArmResetElemNames, QStringList(), QString("")));

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
UAVObject::Metadata FirmwareIAPObj::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        1 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        1 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_ONCHANGE << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
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
void FirmwareIAPObj::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
FirmwareIAPObj::DataFields FirmwareIAPObj::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void FirmwareIAPObj::setData(const DataFields& data)
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

void FirmwareIAPObj::emitNotifications()
{
            //if (data.crc != oldData.crc)
            emit crcChanged(data.crc);
        //if (data.Command != oldData.Command)
            emit CommandChanged(data.Command);
        //if (data.BoardRevision != oldData.BoardRevision)
            emit BoardRevisionChanged(data.BoardRevision);
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
        //if (data.BootloaderRevision != oldData.BootloaderRevision)
            emit BootloaderRevisionChanged(data.BootloaderRevision);
        //if (data.ArmReset != oldData.ArmReset)
            emit ArmResetChanged(data.ArmReset);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *FirmwareIAPObj::clone(quint32 instID)
{
    FirmwareIAPObj *obj = new FirmwareIAPObj();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *FirmwareIAPObj::dirtyClone()
{
    FirmwareIAPObj *obj = new FirmwareIAPObj();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
FirmwareIAPObj *FirmwareIAPObj::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<FirmwareIAPObj *>(objMngr->getObject(FirmwareIAPObj::OBJID, instID));
}

quint32 FirmwareIAPObj::getcrc() const
{
   QMutexLocker locker(mutex);
   return data.crc;
}
void FirmwareIAPObj::setcrc(quint32 value)
{
   mutex->lock();
   bool changed = data.crc != value;
   data.crc = value;
   mutex->unlock();
   if (changed) emit crcChanged(value);
}

quint16 FirmwareIAPObj::getCommand() const
{
   QMutexLocker locker(mutex);
   return data.Command;
}
void FirmwareIAPObj::setCommand(quint16 value)
{
   mutex->lock();
   bool changed = data.Command != value;
   data.Command = value;
   mutex->unlock();
   if (changed) emit CommandChanged(value);
}

quint16 FirmwareIAPObj::getBoardRevision() const
{
   QMutexLocker locker(mutex);
   return data.BoardRevision;
}
void FirmwareIAPObj::setBoardRevision(quint16 value)
{
   mutex->lock();
   bool changed = data.BoardRevision != value;
   data.BoardRevision = value;
   mutex->unlock();
   if (changed) emit BoardRevisionChanged(value);
}

quint8 FirmwareIAPObj::getCPUSerial(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[index];
}
void FirmwareIAPObj::setCPUSerial(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[index] != value;
   data.CPUSerial[index] = value;
   mutex->unlock();
   if (changed) emit CPUSerialChanged(index,value);
}

quint8 FirmwareIAPObj::getCPUSerial_0() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[0];
}
void FirmwareIAPObj::setCPUSerial_0(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[0] != value;
   data.CPUSerial[0] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_0Changed(value);
}

quint8 FirmwareIAPObj::getCPUSerial_1() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[1];
}
void FirmwareIAPObj::setCPUSerial_1(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[1] != value;
   data.CPUSerial[1] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_1Changed(value);
}

quint8 FirmwareIAPObj::getCPUSerial_2() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[2];
}
void FirmwareIAPObj::setCPUSerial_2(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[2] != value;
   data.CPUSerial[2] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_2Changed(value);
}

quint8 FirmwareIAPObj::getCPUSerial_3() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[3];
}
void FirmwareIAPObj::setCPUSerial_3(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[3] != value;
   data.CPUSerial[3] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_3Changed(value);
}

quint8 FirmwareIAPObj::getCPUSerial_4() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[4];
}
void FirmwareIAPObj::setCPUSerial_4(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[4] != value;
   data.CPUSerial[4] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_4Changed(value);
}

quint8 FirmwareIAPObj::getCPUSerial_5() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[5];
}
void FirmwareIAPObj::setCPUSerial_5(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[5] != value;
   data.CPUSerial[5] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_5Changed(value);
}

quint8 FirmwareIAPObj::getCPUSerial_6() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[6];
}
void FirmwareIAPObj::setCPUSerial_6(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[6] != value;
   data.CPUSerial[6] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_6Changed(value);
}

quint8 FirmwareIAPObj::getCPUSerial_7() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[7];
}
void FirmwareIAPObj::setCPUSerial_7(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[7] != value;
   data.CPUSerial[7] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_7Changed(value);
}

quint8 FirmwareIAPObj::getCPUSerial_8() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[8];
}
void FirmwareIAPObj::setCPUSerial_8(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[8] != value;
   data.CPUSerial[8] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_8Changed(value);
}

quint8 FirmwareIAPObj::getCPUSerial_9() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[9];
}
void FirmwareIAPObj::setCPUSerial_9(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[9] != value;
   data.CPUSerial[9] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_9Changed(value);
}

quint8 FirmwareIAPObj::getCPUSerial_10() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[10];
}
void FirmwareIAPObj::setCPUSerial_10(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[10] != value;
   data.CPUSerial[10] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_10Changed(value);
}

quint8 FirmwareIAPObj::getCPUSerial_11() const
{
   QMutexLocker locker(mutex);
   return data.CPUSerial[11];
}
void FirmwareIAPObj::setCPUSerial_11(quint8 value)
{
   mutex->lock();
   bool changed = data.CPUSerial[11] != value;
   data.CPUSerial[11] = value;
   mutex->unlock();
   if (changed) emit CPUSerial_11Changed(value);
}

quint8 FirmwareIAPObj::getBoardType() const
{
   QMutexLocker locker(mutex);
   return data.BoardType;
}
void FirmwareIAPObj::setBoardType(quint8 value)
{
   mutex->lock();
   bool changed = data.BoardType != value;
   data.BoardType = value;
   mutex->unlock();
   if (changed) emit BoardTypeChanged(value);
}

quint8 FirmwareIAPObj::getBootloaderRevision() const
{
   QMutexLocker locker(mutex);
   return data.BootloaderRevision;
}
void FirmwareIAPObj::setBootloaderRevision(quint8 value)
{
   mutex->lock();
   bool changed = data.BootloaderRevision != value;
   data.BootloaderRevision = value;
   mutex->unlock();
   if (changed) emit BootloaderRevisionChanged(value);
}

quint8 FirmwareIAPObj::getArmReset() const
{
   QMutexLocker locker(mutex);
   return data.ArmReset;
}
void FirmwareIAPObj::setArmReset(quint8 value)
{
   mutex->lock();
   bool changed = data.ArmReset != value;
   data.ArmReset = value;
   mutex->unlock();
   if (changed) emit ArmResetChanged(value);
}


