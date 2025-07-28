/**
 ******************************************************************************
 *
 * @file       gpssatellites.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: gpssatellites.xml.
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

#include "gpssatellites.h"
#include "uavobjectfield.h"

const QString GPSSatellites::NAME = QString("GPSSatellites");
const QString GPSSatellites::DESCRIPTION = QString("Contains information about the GPS satellites in view from @ref GPSModule.");
const QString GPSSatellites::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
GPSSatellites::GPSSatellites(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList AzimuthElemNames;
    AzimuthElemNames.append("0");
    AzimuthElemNames.append("1");
    AzimuthElemNames.append("2");
    AzimuthElemNames.append("3");
    AzimuthElemNames.append("4");
    AzimuthElemNames.append("5");
    AzimuthElemNames.append("6");
    AzimuthElemNames.append("7");
    AzimuthElemNames.append("8");
    AzimuthElemNames.append("9");
    AzimuthElemNames.append("10");
    AzimuthElemNames.append("11");
    AzimuthElemNames.append("12");
    AzimuthElemNames.append("13");
    AzimuthElemNames.append("14");
    AzimuthElemNames.append("15");
    fields.append( new UAVObjectField(QString("Azimuth"), tr(""), QString("degrees"), UAVObjectField::INT16, AzimuthElemNames, QStringList(), QString("")));
    QStringList SatsInViewElemNames;
    SatsInViewElemNames.append("0");
    fields.append( new UAVObjectField(QString("SatsInView"), tr(""), QString(""), UAVObjectField::INT8, SatsInViewElemNames, QStringList(), QString("")));
    QStringList PRNElemNames;
    PRNElemNames.append("0");
    PRNElemNames.append("1");
    PRNElemNames.append("2");
    PRNElemNames.append("3");
    PRNElemNames.append("4");
    PRNElemNames.append("5");
    PRNElemNames.append("6");
    PRNElemNames.append("7");
    PRNElemNames.append("8");
    PRNElemNames.append("9");
    PRNElemNames.append("10");
    PRNElemNames.append("11");
    PRNElemNames.append("12");
    PRNElemNames.append("13");
    PRNElemNames.append("14");
    PRNElemNames.append("15");
    fields.append( new UAVObjectField(QString("PRN"), tr(""), QString(""), UAVObjectField::UINT8, PRNElemNames, QStringList(), QString("")));
    QStringList ElevationElemNames;
    ElevationElemNames.append("0");
    ElevationElemNames.append("1");
    ElevationElemNames.append("2");
    ElevationElemNames.append("3");
    ElevationElemNames.append("4");
    ElevationElemNames.append("5");
    ElevationElemNames.append("6");
    ElevationElemNames.append("7");
    ElevationElemNames.append("8");
    ElevationElemNames.append("9");
    ElevationElemNames.append("10");
    ElevationElemNames.append("11");
    ElevationElemNames.append("12");
    ElevationElemNames.append("13");
    ElevationElemNames.append("14");
    ElevationElemNames.append("15");
    fields.append( new UAVObjectField(QString("Elevation"), tr(""), QString("degrees"), UAVObjectField::INT8, ElevationElemNames, QStringList(), QString("")));
    QStringList SNRElemNames;
    SNRElemNames.append("0");
    SNRElemNames.append("1");
    SNRElemNames.append("2");
    SNRElemNames.append("3");
    SNRElemNames.append("4");
    SNRElemNames.append("5");
    SNRElemNames.append("6");
    SNRElemNames.append("7");
    SNRElemNames.append("8");
    SNRElemNames.append("9");
    SNRElemNames.append("10");
    SNRElemNames.append("11");
    SNRElemNames.append("12");
    SNRElemNames.append("13");
    SNRElemNames.append("14");
    SNRElemNames.append("15");
    fields.append( new UAVObjectField(QString("SNR"), tr(""), QString(""), UAVObjectField::INT8, SNRElemNames, QStringList(), QString("")));

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
UAVObject::Metadata GPSSatellites::getDefaultMetadata()
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
    metadata.flightTelemetryUpdatePeriod = 10000;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void GPSSatellites::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
GPSSatellites::DataFields GPSSatellites::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void GPSSatellites::setData(const DataFields& data)
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

void GPSSatellites::emitNotifications()
{
            //if (data.Azimuth[0] != oldData.Azimuth[0])
            emit Azimuth_0Changed(data.Azimuth[0]);
        //if (data.Azimuth[1] != oldData.Azimuth[1])
            emit Azimuth_1Changed(data.Azimuth[1]);
        //if (data.Azimuth[2] != oldData.Azimuth[2])
            emit Azimuth_2Changed(data.Azimuth[2]);
        //if (data.Azimuth[3] != oldData.Azimuth[3])
            emit Azimuth_3Changed(data.Azimuth[3]);
        //if (data.Azimuth[4] != oldData.Azimuth[4])
            emit Azimuth_4Changed(data.Azimuth[4]);
        //if (data.Azimuth[5] != oldData.Azimuth[5])
            emit Azimuth_5Changed(data.Azimuth[5]);
        //if (data.Azimuth[6] != oldData.Azimuth[6])
            emit Azimuth_6Changed(data.Azimuth[6]);
        //if (data.Azimuth[7] != oldData.Azimuth[7])
            emit Azimuth_7Changed(data.Azimuth[7]);
        //if (data.Azimuth[8] != oldData.Azimuth[8])
            emit Azimuth_8Changed(data.Azimuth[8]);
        //if (data.Azimuth[9] != oldData.Azimuth[9])
            emit Azimuth_9Changed(data.Azimuth[9]);
        //if (data.Azimuth[10] != oldData.Azimuth[10])
            emit Azimuth_10Changed(data.Azimuth[10]);
        //if (data.Azimuth[11] != oldData.Azimuth[11])
            emit Azimuth_11Changed(data.Azimuth[11]);
        //if (data.Azimuth[12] != oldData.Azimuth[12])
            emit Azimuth_12Changed(data.Azimuth[12]);
        //if (data.Azimuth[13] != oldData.Azimuth[13])
            emit Azimuth_13Changed(data.Azimuth[13]);
        //if (data.Azimuth[14] != oldData.Azimuth[14])
            emit Azimuth_14Changed(data.Azimuth[14]);
        //if (data.Azimuth[15] != oldData.Azimuth[15])
            emit Azimuth_15Changed(data.Azimuth[15]);
        //if (data.SatsInView != oldData.SatsInView)
            emit SatsInViewChanged(data.SatsInView);
        //if (data.PRN[0] != oldData.PRN[0])
            emit PRN_0Changed(data.PRN[0]);
        //if (data.PRN[1] != oldData.PRN[1])
            emit PRN_1Changed(data.PRN[1]);
        //if (data.PRN[2] != oldData.PRN[2])
            emit PRN_2Changed(data.PRN[2]);
        //if (data.PRN[3] != oldData.PRN[3])
            emit PRN_3Changed(data.PRN[3]);
        //if (data.PRN[4] != oldData.PRN[4])
            emit PRN_4Changed(data.PRN[4]);
        //if (data.PRN[5] != oldData.PRN[5])
            emit PRN_5Changed(data.PRN[5]);
        //if (data.PRN[6] != oldData.PRN[6])
            emit PRN_6Changed(data.PRN[6]);
        //if (data.PRN[7] != oldData.PRN[7])
            emit PRN_7Changed(data.PRN[7]);
        //if (data.PRN[8] != oldData.PRN[8])
            emit PRN_8Changed(data.PRN[8]);
        //if (data.PRN[9] != oldData.PRN[9])
            emit PRN_9Changed(data.PRN[9]);
        //if (data.PRN[10] != oldData.PRN[10])
            emit PRN_10Changed(data.PRN[10]);
        //if (data.PRN[11] != oldData.PRN[11])
            emit PRN_11Changed(data.PRN[11]);
        //if (data.PRN[12] != oldData.PRN[12])
            emit PRN_12Changed(data.PRN[12]);
        //if (data.PRN[13] != oldData.PRN[13])
            emit PRN_13Changed(data.PRN[13]);
        //if (data.PRN[14] != oldData.PRN[14])
            emit PRN_14Changed(data.PRN[14]);
        //if (data.PRN[15] != oldData.PRN[15])
            emit PRN_15Changed(data.PRN[15]);
        //if (data.Elevation[0] != oldData.Elevation[0])
            emit Elevation_0Changed(data.Elevation[0]);
        //if (data.Elevation[1] != oldData.Elevation[1])
            emit Elevation_1Changed(data.Elevation[1]);
        //if (data.Elevation[2] != oldData.Elevation[2])
            emit Elevation_2Changed(data.Elevation[2]);
        //if (data.Elevation[3] != oldData.Elevation[3])
            emit Elevation_3Changed(data.Elevation[3]);
        //if (data.Elevation[4] != oldData.Elevation[4])
            emit Elevation_4Changed(data.Elevation[4]);
        //if (data.Elevation[5] != oldData.Elevation[5])
            emit Elevation_5Changed(data.Elevation[5]);
        //if (data.Elevation[6] != oldData.Elevation[6])
            emit Elevation_6Changed(data.Elevation[6]);
        //if (data.Elevation[7] != oldData.Elevation[7])
            emit Elevation_7Changed(data.Elevation[7]);
        //if (data.Elevation[8] != oldData.Elevation[8])
            emit Elevation_8Changed(data.Elevation[8]);
        //if (data.Elevation[9] != oldData.Elevation[9])
            emit Elevation_9Changed(data.Elevation[9]);
        //if (data.Elevation[10] != oldData.Elevation[10])
            emit Elevation_10Changed(data.Elevation[10]);
        //if (data.Elevation[11] != oldData.Elevation[11])
            emit Elevation_11Changed(data.Elevation[11]);
        //if (data.Elevation[12] != oldData.Elevation[12])
            emit Elevation_12Changed(data.Elevation[12]);
        //if (data.Elevation[13] != oldData.Elevation[13])
            emit Elevation_13Changed(data.Elevation[13]);
        //if (data.Elevation[14] != oldData.Elevation[14])
            emit Elevation_14Changed(data.Elevation[14]);
        //if (data.Elevation[15] != oldData.Elevation[15])
            emit Elevation_15Changed(data.Elevation[15]);
        //if (data.SNR[0] != oldData.SNR[0])
            emit SNR_0Changed(data.SNR[0]);
        //if (data.SNR[1] != oldData.SNR[1])
            emit SNR_1Changed(data.SNR[1]);
        //if (data.SNR[2] != oldData.SNR[2])
            emit SNR_2Changed(data.SNR[2]);
        //if (data.SNR[3] != oldData.SNR[3])
            emit SNR_3Changed(data.SNR[3]);
        //if (data.SNR[4] != oldData.SNR[4])
            emit SNR_4Changed(data.SNR[4]);
        //if (data.SNR[5] != oldData.SNR[5])
            emit SNR_5Changed(data.SNR[5]);
        //if (data.SNR[6] != oldData.SNR[6])
            emit SNR_6Changed(data.SNR[6]);
        //if (data.SNR[7] != oldData.SNR[7])
            emit SNR_7Changed(data.SNR[7]);
        //if (data.SNR[8] != oldData.SNR[8])
            emit SNR_8Changed(data.SNR[8]);
        //if (data.SNR[9] != oldData.SNR[9])
            emit SNR_9Changed(data.SNR[9]);
        //if (data.SNR[10] != oldData.SNR[10])
            emit SNR_10Changed(data.SNR[10]);
        //if (data.SNR[11] != oldData.SNR[11])
            emit SNR_11Changed(data.SNR[11]);
        //if (data.SNR[12] != oldData.SNR[12])
            emit SNR_12Changed(data.SNR[12]);
        //if (data.SNR[13] != oldData.SNR[13])
            emit SNR_13Changed(data.SNR[13]);
        //if (data.SNR[14] != oldData.SNR[14])
            emit SNR_14Changed(data.SNR[14]);
        //if (data.SNR[15] != oldData.SNR[15])
            emit SNR_15Changed(data.SNR[15]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *GPSSatellites::clone(quint32 instID)
{
    GPSSatellites *obj = new GPSSatellites();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *GPSSatellites::dirtyClone()
{
    GPSSatellites *obj = new GPSSatellites();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
GPSSatellites *GPSSatellites::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<GPSSatellites *>(objMngr->getObject(GPSSatellites::OBJID, instID));
}

qint16 GPSSatellites::getAzimuth(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[index];
}
void GPSSatellites::setAzimuth(quint32 index, qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[index] != value;
   data.Azimuth[index] = value;
   mutex->unlock();
   if (changed) emit AzimuthChanged(index,value);
}

qint16 GPSSatellites::getAzimuth_0() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[0];
}
void GPSSatellites::setAzimuth_0(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[0] != value;
   data.Azimuth[0] = value;
   mutex->unlock();
   if (changed) emit Azimuth_0Changed(value);
}

qint16 GPSSatellites::getAzimuth_1() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[1];
}
void GPSSatellites::setAzimuth_1(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[1] != value;
   data.Azimuth[1] = value;
   mutex->unlock();
   if (changed) emit Azimuth_1Changed(value);
}

qint16 GPSSatellites::getAzimuth_2() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[2];
}
void GPSSatellites::setAzimuth_2(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[2] != value;
   data.Azimuth[2] = value;
   mutex->unlock();
   if (changed) emit Azimuth_2Changed(value);
}

qint16 GPSSatellites::getAzimuth_3() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[3];
}
void GPSSatellites::setAzimuth_3(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[3] != value;
   data.Azimuth[3] = value;
   mutex->unlock();
   if (changed) emit Azimuth_3Changed(value);
}

qint16 GPSSatellites::getAzimuth_4() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[4];
}
void GPSSatellites::setAzimuth_4(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[4] != value;
   data.Azimuth[4] = value;
   mutex->unlock();
   if (changed) emit Azimuth_4Changed(value);
}

qint16 GPSSatellites::getAzimuth_5() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[5];
}
void GPSSatellites::setAzimuth_5(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[5] != value;
   data.Azimuth[5] = value;
   mutex->unlock();
   if (changed) emit Azimuth_5Changed(value);
}

qint16 GPSSatellites::getAzimuth_6() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[6];
}
void GPSSatellites::setAzimuth_6(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[6] != value;
   data.Azimuth[6] = value;
   mutex->unlock();
   if (changed) emit Azimuth_6Changed(value);
}

qint16 GPSSatellites::getAzimuth_7() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[7];
}
void GPSSatellites::setAzimuth_7(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[7] != value;
   data.Azimuth[7] = value;
   mutex->unlock();
   if (changed) emit Azimuth_7Changed(value);
}

qint16 GPSSatellites::getAzimuth_8() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[8];
}
void GPSSatellites::setAzimuth_8(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[8] != value;
   data.Azimuth[8] = value;
   mutex->unlock();
   if (changed) emit Azimuth_8Changed(value);
}

qint16 GPSSatellites::getAzimuth_9() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[9];
}
void GPSSatellites::setAzimuth_9(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[9] != value;
   data.Azimuth[9] = value;
   mutex->unlock();
   if (changed) emit Azimuth_9Changed(value);
}

qint16 GPSSatellites::getAzimuth_10() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[10];
}
void GPSSatellites::setAzimuth_10(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[10] != value;
   data.Azimuth[10] = value;
   mutex->unlock();
   if (changed) emit Azimuth_10Changed(value);
}

qint16 GPSSatellites::getAzimuth_11() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[11];
}
void GPSSatellites::setAzimuth_11(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[11] != value;
   data.Azimuth[11] = value;
   mutex->unlock();
   if (changed) emit Azimuth_11Changed(value);
}

qint16 GPSSatellites::getAzimuth_12() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[12];
}
void GPSSatellites::setAzimuth_12(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[12] != value;
   data.Azimuth[12] = value;
   mutex->unlock();
   if (changed) emit Azimuth_12Changed(value);
}

qint16 GPSSatellites::getAzimuth_13() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[13];
}
void GPSSatellites::setAzimuth_13(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[13] != value;
   data.Azimuth[13] = value;
   mutex->unlock();
   if (changed) emit Azimuth_13Changed(value);
}

qint16 GPSSatellites::getAzimuth_14() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[14];
}
void GPSSatellites::setAzimuth_14(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[14] != value;
   data.Azimuth[14] = value;
   mutex->unlock();
   if (changed) emit Azimuth_14Changed(value);
}

qint16 GPSSatellites::getAzimuth_15() const
{
   QMutexLocker locker(mutex);
   return data.Azimuth[15];
}
void GPSSatellites::setAzimuth_15(qint16 value)
{
   mutex->lock();
   bool changed = data.Azimuth[15] != value;
   data.Azimuth[15] = value;
   mutex->unlock();
   if (changed) emit Azimuth_15Changed(value);
}

qint8 GPSSatellites::getSatsInView() const
{
   QMutexLocker locker(mutex);
   return data.SatsInView;
}
void GPSSatellites::setSatsInView(qint8 value)
{
   mutex->lock();
   bool changed = data.SatsInView != value;
   data.SatsInView = value;
   mutex->unlock();
   if (changed) emit SatsInViewChanged(value);
}

quint8 GPSSatellites::getPRN(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.PRN[index];
}
void GPSSatellites::setPRN(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[index] != value;
   data.PRN[index] = value;
   mutex->unlock();
   if (changed) emit PRNChanged(index,value);
}

quint8 GPSSatellites::getPRN_0() const
{
   QMutexLocker locker(mutex);
   return data.PRN[0];
}
void GPSSatellites::setPRN_0(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[0] != value;
   data.PRN[0] = value;
   mutex->unlock();
   if (changed) emit PRN_0Changed(value);
}

quint8 GPSSatellites::getPRN_1() const
{
   QMutexLocker locker(mutex);
   return data.PRN[1];
}
void GPSSatellites::setPRN_1(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[1] != value;
   data.PRN[1] = value;
   mutex->unlock();
   if (changed) emit PRN_1Changed(value);
}

quint8 GPSSatellites::getPRN_2() const
{
   QMutexLocker locker(mutex);
   return data.PRN[2];
}
void GPSSatellites::setPRN_2(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[2] != value;
   data.PRN[2] = value;
   mutex->unlock();
   if (changed) emit PRN_2Changed(value);
}

quint8 GPSSatellites::getPRN_3() const
{
   QMutexLocker locker(mutex);
   return data.PRN[3];
}
void GPSSatellites::setPRN_3(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[3] != value;
   data.PRN[3] = value;
   mutex->unlock();
   if (changed) emit PRN_3Changed(value);
}

quint8 GPSSatellites::getPRN_4() const
{
   QMutexLocker locker(mutex);
   return data.PRN[4];
}
void GPSSatellites::setPRN_4(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[4] != value;
   data.PRN[4] = value;
   mutex->unlock();
   if (changed) emit PRN_4Changed(value);
}

quint8 GPSSatellites::getPRN_5() const
{
   QMutexLocker locker(mutex);
   return data.PRN[5];
}
void GPSSatellites::setPRN_5(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[5] != value;
   data.PRN[5] = value;
   mutex->unlock();
   if (changed) emit PRN_5Changed(value);
}

quint8 GPSSatellites::getPRN_6() const
{
   QMutexLocker locker(mutex);
   return data.PRN[6];
}
void GPSSatellites::setPRN_6(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[6] != value;
   data.PRN[6] = value;
   mutex->unlock();
   if (changed) emit PRN_6Changed(value);
}

quint8 GPSSatellites::getPRN_7() const
{
   QMutexLocker locker(mutex);
   return data.PRN[7];
}
void GPSSatellites::setPRN_7(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[7] != value;
   data.PRN[7] = value;
   mutex->unlock();
   if (changed) emit PRN_7Changed(value);
}

quint8 GPSSatellites::getPRN_8() const
{
   QMutexLocker locker(mutex);
   return data.PRN[8];
}
void GPSSatellites::setPRN_8(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[8] != value;
   data.PRN[8] = value;
   mutex->unlock();
   if (changed) emit PRN_8Changed(value);
}

quint8 GPSSatellites::getPRN_9() const
{
   QMutexLocker locker(mutex);
   return data.PRN[9];
}
void GPSSatellites::setPRN_9(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[9] != value;
   data.PRN[9] = value;
   mutex->unlock();
   if (changed) emit PRN_9Changed(value);
}

quint8 GPSSatellites::getPRN_10() const
{
   QMutexLocker locker(mutex);
   return data.PRN[10];
}
void GPSSatellites::setPRN_10(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[10] != value;
   data.PRN[10] = value;
   mutex->unlock();
   if (changed) emit PRN_10Changed(value);
}

quint8 GPSSatellites::getPRN_11() const
{
   QMutexLocker locker(mutex);
   return data.PRN[11];
}
void GPSSatellites::setPRN_11(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[11] != value;
   data.PRN[11] = value;
   mutex->unlock();
   if (changed) emit PRN_11Changed(value);
}

quint8 GPSSatellites::getPRN_12() const
{
   QMutexLocker locker(mutex);
   return data.PRN[12];
}
void GPSSatellites::setPRN_12(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[12] != value;
   data.PRN[12] = value;
   mutex->unlock();
   if (changed) emit PRN_12Changed(value);
}

quint8 GPSSatellites::getPRN_13() const
{
   QMutexLocker locker(mutex);
   return data.PRN[13];
}
void GPSSatellites::setPRN_13(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[13] != value;
   data.PRN[13] = value;
   mutex->unlock();
   if (changed) emit PRN_13Changed(value);
}

quint8 GPSSatellites::getPRN_14() const
{
   QMutexLocker locker(mutex);
   return data.PRN[14];
}
void GPSSatellites::setPRN_14(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[14] != value;
   data.PRN[14] = value;
   mutex->unlock();
   if (changed) emit PRN_14Changed(value);
}

quint8 GPSSatellites::getPRN_15() const
{
   QMutexLocker locker(mutex);
   return data.PRN[15];
}
void GPSSatellites::setPRN_15(quint8 value)
{
   mutex->lock();
   bool changed = data.PRN[15] != value;
   data.PRN[15] = value;
   mutex->unlock();
   if (changed) emit PRN_15Changed(value);
}

qint8 GPSSatellites::getElevation(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Elevation[index];
}
void GPSSatellites::setElevation(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[index] != value;
   data.Elevation[index] = value;
   mutex->unlock();
   if (changed) emit ElevationChanged(index,value);
}

qint8 GPSSatellites::getElevation_0() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[0];
}
void GPSSatellites::setElevation_0(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[0] != value;
   data.Elevation[0] = value;
   mutex->unlock();
   if (changed) emit Elevation_0Changed(value);
}

qint8 GPSSatellites::getElevation_1() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[1];
}
void GPSSatellites::setElevation_1(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[1] != value;
   data.Elevation[1] = value;
   mutex->unlock();
   if (changed) emit Elevation_1Changed(value);
}

qint8 GPSSatellites::getElevation_2() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[2];
}
void GPSSatellites::setElevation_2(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[2] != value;
   data.Elevation[2] = value;
   mutex->unlock();
   if (changed) emit Elevation_2Changed(value);
}

qint8 GPSSatellites::getElevation_3() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[3];
}
void GPSSatellites::setElevation_3(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[3] != value;
   data.Elevation[3] = value;
   mutex->unlock();
   if (changed) emit Elevation_3Changed(value);
}

qint8 GPSSatellites::getElevation_4() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[4];
}
void GPSSatellites::setElevation_4(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[4] != value;
   data.Elevation[4] = value;
   mutex->unlock();
   if (changed) emit Elevation_4Changed(value);
}

qint8 GPSSatellites::getElevation_5() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[5];
}
void GPSSatellites::setElevation_5(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[5] != value;
   data.Elevation[5] = value;
   mutex->unlock();
   if (changed) emit Elevation_5Changed(value);
}

qint8 GPSSatellites::getElevation_6() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[6];
}
void GPSSatellites::setElevation_6(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[6] != value;
   data.Elevation[6] = value;
   mutex->unlock();
   if (changed) emit Elevation_6Changed(value);
}

qint8 GPSSatellites::getElevation_7() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[7];
}
void GPSSatellites::setElevation_7(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[7] != value;
   data.Elevation[7] = value;
   mutex->unlock();
   if (changed) emit Elevation_7Changed(value);
}

qint8 GPSSatellites::getElevation_8() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[8];
}
void GPSSatellites::setElevation_8(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[8] != value;
   data.Elevation[8] = value;
   mutex->unlock();
   if (changed) emit Elevation_8Changed(value);
}

qint8 GPSSatellites::getElevation_9() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[9];
}
void GPSSatellites::setElevation_9(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[9] != value;
   data.Elevation[9] = value;
   mutex->unlock();
   if (changed) emit Elevation_9Changed(value);
}

qint8 GPSSatellites::getElevation_10() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[10];
}
void GPSSatellites::setElevation_10(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[10] != value;
   data.Elevation[10] = value;
   mutex->unlock();
   if (changed) emit Elevation_10Changed(value);
}

qint8 GPSSatellites::getElevation_11() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[11];
}
void GPSSatellites::setElevation_11(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[11] != value;
   data.Elevation[11] = value;
   mutex->unlock();
   if (changed) emit Elevation_11Changed(value);
}

qint8 GPSSatellites::getElevation_12() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[12];
}
void GPSSatellites::setElevation_12(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[12] != value;
   data.Elevation[12] = value;
   mutex->unlock();
   if (changed) emit Elevation_12Changed(value);
}

qint8 GPSSatellites::getElevation_13() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[13];
}
void GPSSatellites::setElevation_13(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[13] != value;
   data.Elevation[13] = value;
   mutex->unlock();
   if (changed) emit Elevation_13Changed(value);
}

qint8 GPSSatellites::getElevation_14() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[14];
}
void GPSSatellites::setElevation_14(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[14] != value;
   data.Elevation[14] = value;
   mutex->unlock();
   if (changed) emit Elevation_14Changed(value);
}

qint8 GPSSatellites::getElevation_15() const
{
   QMutexLocker locker(mutex);
   return data.Elevation[15];
}
void GPSSatellites::setElevation_15(qint8 value)
{
   mutex->lock();
   bool changed = data.Elevation[15] != value;
   data.Elevation[15] = value;
   mutex->unlock();
   if (changed) emit Elevation_15Changed(value);
}

qint8 GPSSatellites::getSNR(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.SNR[index];
}
void GPSSatellites::setSNR(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[index] != value;
   data.SNR[index] = value;
   mutex->unlock();
   if (changed) emit SNRChanged(index,value);
}

qint8 GPSSatellites::getSNR_0() const
{
   QMutexLocker locker(mutex);
   return data.SNR[0];
}
void GPSSatellites::setSNR_0(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[0] != value;
   data.SNR[0] = value;
   mutex->unlock();
   if (changed) emit SNR_0Changed(value);
}

qint8 GPSSatellites::getSNR_1() const
{
   QMutexLocker locker(mutex);
   return data.SNR[1];
}
void GPSSatellites::setSNR_1(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[1] != value;
   data.SNR[1] = value;
   mutex->unlock();
   if (changed) emit SNR_1Changed(value);
}

qint8 GPSSatellites::getSNR_2() const
{
   QMutexLocker locker(mutex);
   return data.SNR[2];
}
void GPSSatellites::setSNR_2(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[2] != value;
   data.SNR[2] = value;
   mutex->unlock();
   if (changed) emit SNR_2Changed(value);
}

qint8 GPSSatellites::getSNR_3() const
{
   QMutexLocker locker(mutex);
   return data.SNR[3];
}
void GPSSatellites::setSNR_3(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[3] != value;
   data.SNR[3] = value;
   mutex->unlock();
   if (changed) emit SNR_3Changed(value);
}

qint8 GPSSatellites::getSNR_4() const
{
   QMutexLocker locker(mutex);
   return data.SNR[4];
}
void GPSSatellites::setSNR_4(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[4] != value;
   data.SNR[4] = value;
   mutex->unlock();
   if (changed) emit SNR_4Changed(value);
}

qint8 GPSSatellites::getSNR_5() const
{
   QMutexLocker locker(mutex);
   return data.SNR[5];
}
void GPSSatellites::setSNR_5(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[5] != value;
   data.SNR[5] = value;
   mutex->unlock();
   if (changed) emit SNR_5Changed(value);
}

qint8 GPSSatellites::getSNR_6() const
{
   QMutexLocker locker(mutex);
   return data.SNR[6];
}
void GPSSatellites::setSNR_6(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[6] != value;
   data.SNR[6] = value;
   mutex->unlock();
   if (changed) emit SNR_6Changed(value);
}

qint8 GPSSatellites::getSNR_7() const
{
   QMutexLocker locker(mutex);
   return data.SNR[7];
}
void GPSSatellites::setSNR_7(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[7] != value;
   data.SNR[7] = value;
   mutex->unlock();
   if (changed) emit SNR_7Changed(value);
}

qint8 GPSSatellites::getSNR_8() const
{
   QMutexLocker locker(mutex);
   return data.SNR[8];
}
void GPSSatellites::setSNR_8(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[8] != value;
   data.SNR[8] = value;
   mutex->unlock();
   if (changed) emit SNR_8Changed(value);
}

qint8 GPSSatellites::getSNR_9() const
{
   QMutexLocker locker(mutex);
   return data.SNR[9];
}
void GPSSatellites::setSNR_9(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[9] != value;
   data.SNR[9] = value;
   mutex->unlock();
   if (changed) emit SNR_9Changed(value);
}

qint8 GPSSatellites::getSNR_10() const
{
   QMutexLocker locker(mutex);
   return data.SNR[10];
}
void GPSSatellites::setSNR_10(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[10] != value;
   data.SNR[10] = value;
   mutex->unlock();
   if (changed) emit SNR_10Changed(value);
}

qint8 GPSSatellites::getSNR_11() const
{
   QMutexLocker locker(mutex);
   return data.SNR[11];
}
void GPSSatellites::setSNR_11(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[11] != value;
   data.SNR[11] = value;
   mutex->unlock();
   if (changed) emit SNR_11Changed(value);
}

qint8 GPSSatellites::getSNR_12() const
{
   QMutexLocker locker(mutex);
   return data.SNR[12];
}
void GPSSatellites::setSNR_12(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[12] != value;
   data.SNR[12] = value;
   mutex->unlock();
   if (changed) emit SNR_12Changed(value);
}

qint8 GPSSatellites::getSNR_13() const
{
   QMutexLocker locker(mutex);
   return data.SNR[13];
}
void GPSSatellites::setSNR_13(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[13] != value;
   data.SNR[13] = value;
   mutex->unlock();
   if (changed) emit SNR_13Changed(value);
}

qint8 GPSSatellites::getSNR_14() const
{
   QMutexLocker locker(mutex);
   return data.SNR[14];
}
void GPSSatellites::setSNR_14(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[14] != value;
   data.SNR[14] = value;
   mutex->unlock();
   if (changed) emit SNR_14Changed(value);
}

qint8 GPSSatellites::getSNR_15() const
{
   QMutexLocker locker(mutex);
   return data.SNR[15];
}
void GPSSatellites::setSNR_15(qint8 value)
{
   mutex->lock();
   bool changed = data.SNR[15] != value;
   data.SNR[15] = value;
   mutex->unlock();
   if (changed) emit SNR_15Changed(value);
}


