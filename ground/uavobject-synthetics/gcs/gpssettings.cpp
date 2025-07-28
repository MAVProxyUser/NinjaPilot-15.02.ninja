/**
 ******************************************************************************
 *
 * @file       gpssettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: gpssettings.xml.
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

#include "gpssettings.h"
#include "uavobjectfield.h"

const QString GPSSettings::NAME = QString("GPSSettings");
const QString GPSSettings::DESCRIPTION = QString("GPS Module specific settings");
const QString GPSSettings::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
GPSSettings::GPSSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList MaxPDOPElemNames;
    MaxPDOPElemNames.append("0");
    fields.append( new UAVObjectField(QString("MaxPDOP"), tr(""), QString(""), UAVObjectField::FLOAT32, MaxPDOPElemNames, QStringList(), QString("")));
    QStringList DataProtocolElemNames;
    DataProtocolElemNames.append("0");
    QStringList DataProtocolEnumOptions;
    DataProtocolEnumOptions.append("NMEA");
    DataProtocolEnumOptions.append("UBX");
    fields.append( new UAVObjectField(QString("DataProtocol"), tr(""), QString(""), UAVObjectField::ENUM, DataProtocolElemNames, DataProtocolEnumOptions, QString("")));
    QStringList MinSatellitesElemNames;
    MinSatellitesElemNames.append("0");
    fields.append( new UAVObjectField(QString("MinSatellites"), tr(""), QString(""), UAVObjectField::UINT8, MinSatellitesElemNames, QStringList(), QString("")));
    QStringList UbxAutoConfigElemNames;
    UbxAutoConfigElemNames.append("0");
    QStringList UbxAutoConfigEnumOptions;
    UbxAutoConfigEnumOptions.append("Disabled");
    UbxAutoConfigEnumOptions.append("Configure");
    UbxAutoConfigEnumOptions.append("ConfigureAndStore");
    fields.append( new UAVObjectField(QString("UbxAutoConfig"), tr(""), QString(""), UAVObjectField::ENUM, UbxAutoConfigElemNames, UbxAutoConfigEnumOptions, QString("")));
    QStringList UbxRateElemNames;
    UbxRateElemNames.append("0");
    fields.append( new UAVObjectField(QString("UbxRate"), tr(""), QString("Hz"), UAVObjectField::INT8, UbxRateElemNames, QStringList(), QString("")));
    QStringList UbxDynamicModelElemNames;
    UbxDynamicModelElemNames.append("0");
    QStringList UbxDynamicModelEnumOptions;
    UbxDynamicModelEnumOptions.append("Portable");
    UbxDynamicModelEnumOptions.append("Stationary");
    UbxDynamicModelEnumOptions.append("Pedestrian");
    UbxDynamicModelEnumOptions.append("Automotive");
    UbxDynamicModelEnumOptions.append("Sea");
    UbxDynamicModelEnumOptions.append("Airborne1G");
    UbxDynamicModelEnumOptions.append("Airborne2G");
    UbxDynamicModelEnumOptions.append("Airborne4G");
    fields.append( new UAVObjectField(QString("UbxDynamicModel"), tr(""), QString(""), UAVObjectField::ENUM, UbxDynamicModelElemNames, UbxDynamicModelEnumOptions, QString("")));
    QStringList UbxSBASModeElemNames;
    UbxSBASModeElemNames.append("0");
    QStringList UbxSBASModeEnumOptions;
    UbxSBASModeEnumOptions.append("Disabled");
    UbxSBASModeEnumOptions.append("Ranging");
    UbxSBASModeEnumOptions.append("Correction");
    UbxSBASModeEnumOptions.append("Integrity");
    UbxSBASModeEnumOptions.append("Ranging+Correction");
    UbxSBASModeEnumOptions.append("Ranging+Integrity");
    UbxSBASModeEnumOptions.append("Ranging+Correction+Integrity");
    UbxSBASModeEnumOptions.append("Correction+Integrity");
    fields.append( new UAVObjectField(QString("UbxSBASMode"), tr(""), QString(""), UAVObjectField::ENUM, UbxSBASModeElemNames, UbxSBASModeEnumOptions, QString("")));
    QStringList UbxSBASChannelsUsedElemNames;
    UbxSBASChannelsUsedElemNames.append("0");
    fields.append( new UAVObjectField(QString("UbxSBASChannelsUsed"), tr(""), QString(""), UAVObjectField::UINT8, UbxSBASChannelsUsedElemNames, QStringList(), QString("")));
    QStringList UbxSBASSatsElemNames;
    UbxSBASSatsElemNames.append("0");
    QStringList UbxSBASSatsEnumOptions;
    UbxSBASSatsEnumOptions.append("AutoScan");
    UbxSBASSatsEnumOptions.append("WAAS");
    UbxSBASSatsEnumOptions.append("EGNOS");
    UbxSBASSatsEnumOptions.append("MSAS");
    UbxSBASSatsEnumOptions.append("GAGAN");
    UbxSBASSatsEnumOptions.append("SDCM");
    fields.append( new UAVObjectField(QString("UbxSBASSats"), tr(""), QString(""), UAVObjectField::ENUM, UbxSBASSatsElemNames, UbxSBASSatsEnumOptions, QString("")));
    QStringList UbxGNSSModeElemNames;
    UbxGNSSModeElemNames.append("0");
    QStringList UbxGNSSModeEnumOptions;
    UbxGNSSModeEnumOptions.append("Default");
    UbxGNSSModeEnumOptions.append("GPS");
    UbxGNSSModeEnumOptions.append("GLONASS");
    UbxGNSSModeEnumOptions.append("GPS+GLONASS");
    UbxGNSSModeEnumOptions.append("GPS+BeiDou");
    UbxGNSSModeEnumOptions.append("GLONASS+BeiDou");
    fields.append( new UAVObjectField(QString("UbxGNSSMode"), tr(""), QString(""), UAVObjectField::ENUM, UbxGNSSModeElemNames, UbxGNSSModeEnumOptions, QString("")));

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
UAVObject::Metadata GPSSettings::getDefaultMetadata()
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
void GPSSettings::setDefaultFieldValues()
{
    data.MaxPDOP = 3.5;
    data.DataProtocol = 1;
    data.MinSatellites = 7;
    data.UbxAutoConfig = 1;
    data.UbxRate = 5;
    data.UbxDynamicModel = 5;
    data.UbxSBASMode = 1;
    data.UbxSBASChannelsUsed = 3;
    data.UbxSBASSats = -1;
    data.UbxGNSSMode = 0;

}

/**
 * Get the object data fields
 */
GPSSettings::DataFields GPSSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void GPSSettings::setData(const DataFields& data)
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

void GPSSettings::emitNotifications()
{
            //if (data.MaxPDOP != oldData.MaxPDOP)
            emit MaxPDOPChanged(data.MaxPDOP);
        //if (data.DataProtocol != oldData.DataProtocol)
            emit DataProtocolChanged(data.DataProtocol);
        //if (data.MinSatellites != oldData.MinSatellites)
            emit MinSatellitesChanged(data.MinSatellites);
        //if (data.UbxAutoConfig != oldData.UbxAutoConfig)
            emit UbxAutoConfigChanged(data.UbxAutoConfig);
        //if (data.UbxRate != oldData.UbxRate)
            emit UbxRateChanged(data.UbxRate);
        //if (data.UbxDynamicModel != oldData.UbxDynamicModel)
            emit UbxDynamicModelChanged(data.UbxDynamicModel);
        //if (data.UbxSBASMode != oldData.UbxSBASMode)
            emit UbxSBASModeChanged(data.UbxSBASMode);
        //if (data.UbxSBASChannelsUsed != oldData.UbxSBASChannelsUsed)
            emit UbxSBASChannelsUsedChanged(data.UbxSBASChannelsUsed);
        //if (data.UbxSBASSats != oldData.UbxSBASSats)
            emit UbxSBASSatsChanged(data.UbxSBASSats);
        //if (data.UbxGNSSMode != oldData.UbxGNSSMode)
            emit UbxGNSSModeChanged(data.UbxGNSSMode);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *GPSSettings::clone(quint32 instID)
{
    GPSSettings *obj = new GPSSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *GPSSettings::dirtyClone()
{
    GPSSettings *obj = new GPSSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
GPSSettings *GPSSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<GPSSettings *>(objMngr->getObject(GPSSettings::OBJID, instID));
}

float GPSSettings::getMaxPDOP() const
{
   QMutexLocker locker(mutex);
   return data.MaxPDOP;
}
void GPSSettings::setMaxPDOP(float value)
{
   mutex->lock();
   bool changed = data.MaxPDOP != value;
   data.MaxPDOP = value;
   mutex->unlock();
   if (changed) emit MaxPDOPChanged(value);
}

quint8 GPSSettings::getDataProtocol() const
{
   QMutexLocker locker(mutex);
   return data.DataProtocol;
}
void GPSSettings::setDataProtocol(quint8 value)
{
   mutex->lock();
   bool changed = data.DataProtocol != value;
   data.DataProtocol = value;
   mutex->unlock();
   if (changed) emit DataProtocolChanged(value);
}

quint8 GPSSettings::getMinSatellites() const
{
   QMutexLocker locker(mutex);
   return data.MinSatellites;
}
void GPSSettings::setMinSatellites(quint8 value)
{
   mutex->lock();
   bool changed = data.MinSatellites != value;
   data.MinSatellites = value;
   mutex->unlock();
   if (changed) emit MinSatellitesChanged(value);
}

quint8 GPSSettings::getUbxAutoConfig() const
{
   QMutexLocker locker(mutex);
   return data.UbxAutoConfig;
}
void GPSSettings::setUbxAutoConfig(quint8 value)
{
   mutex->lock();
   bool changed = data.UbxAutoConfig != value;
   data.UbxAutoConfig = value;
   mutex->unlock();
   if (changed) emit UbxAutoConfigChanged(value);
}

qint8 GPSSettings::getUbxRate() const
{
   QMutexLocker locker(mutex);
   return data.UbxRate;
}
void GPSSettings::setUbxRate(qint8 value)
{
   mutex->lock();
   bool changed = data.UbxRate != value;
   data.UbxRate = value;
   mutex->unlock();
   if (changed) emit UbxRateChanged(value);
}

quint8 GPSSettings::getUbxDynamicModel() const
{
   QMutexLocker locker(mutex);
   return data.UbxDynamicModel;
}
void GPSSettings::setUbxDynamicModel(quint8 value)
{
   mutex->lock();
   bool changed = data.UbxDynamicModel != value;
   data.UbxDynamicModel = value;
   mutex->unlock();
   if (changed) emit UbxDynamicModelChanged(value);
}

quint8 GPSSettings::getUbxSBASMode() const
{
   QMutexLocker locker(mutex);
   return data.UbxSBASMode;
}
void GPSSettings::setUbxSBASMode(quint8 value)
{
   mutex->lock();
   bool changed = data.UbxSBASMode != value;
   data.UbxSBASMode = value;
   mutex->unlock();
   if (changed) emit UbxSBASModeChanged(value);
}

quint8 GPSSettings::getUbxSBASChannelsUsed() const
{
   QMutexLocker locker(mutex);
   return data.UbxSBASChannelsUsed;
}
void GPSSettings::setUbxSBASChannelsUsed(quint8 value)
{
   mutex->lock();
   bool changed = data.UbxSBASChannelsUsed != value;
   data.UbxSBASChannelsUsed = value;
   mutex->unlock();
   if (changed) emit UbxSBASChannelsUsedChanged(value);
}

quint8 GPSSettings::getUbxSBASSats() const
{
   QMutexLocker locker(mutex);
   return data.UbxSBASSats;
}
void GPSSettings::setUbxSBASSats(quint8 value)
{
   mutex->lock();
   bool changed = data.UbxSBASSats != value;
   data.UbxSBASSats = value;
   mutex->unlock();
   if (changed) emit UbxSBASSatsChanged(value);
}

quint8 GPSSettings::getUbxGNSSMode() const
{
   QMutexLocker locker(mutex);
   return data.UbxGNSSMode;
}
void GPSSettings::setUbxGNSSMode(quint8 value)
{
   mutex->lock();
   bool changed = data.UbxGNSSMode != value;
   data.UbxGNSSMode = value;
   mutex->unlock();
   if (changed) emit UbxGNSSModeChanged(value);
}


