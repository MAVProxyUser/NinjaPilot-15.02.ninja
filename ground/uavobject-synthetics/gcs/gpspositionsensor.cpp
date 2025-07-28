/**
 ******************************************************************************
 *
 * @file       gpspositionsensor.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: gpspositionsensor.xml.
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

#include "gpspositionsensor.h"
#include "uavobjectfield.h"

const QString GPSPositionSensor::NAME = QString("GPSPositionSensor");
const QString GPSPositionSensor::DESCRIPTION = QString("Raw GPS data from @ref GPSModule.");
const QString GPSPositionSensor::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
GPSPositionSensor::GPSPositionSensor(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList LatitudeElemNames;
    LatitudeElemNames.append("0");
    fields.append( new UAVObjectField(QString("Latitude"), tr(""), QString("degrees x 10^-7"), UAVObjectField::INT32, LatitudeElemNames, QStringList(), QString("")));
    QStringList LongitudeElemNames;
    LongitudeElemNames.append("0");
    fields.append( new UAVObjectField(QString("Longitude"), tr(""), QString("degrees x 10^-7"), UAVObjectField::INT32, LongitudeElemNames, QStringList(), QString("")));
    QStringList AltitudeElemNames;
    AltitudeElemNames.append("0");
    fields.append( new UAVObjectField(QString("Altitude"), tr(""), QString("meters"), UAVObjectField::FLOAT32, AltitudeElemNames, QStringList(), QString("")));
    QStringList GeoidSeparationElemNames;
    GeoidSeparationElemNames.append("0");
    fields.append( new UAVObjectField(QString("GeoidSeparation"), tr(""), QString("meters"), UAVObjectField::FLOAT32, GeoidSeparationElemNames, QStringList(), QString("")));
    QStringList HeadingElemNames;
    HeadingElemNames.append("0");
    fields.append( new UAVObjectField(QString("Heading"), tr(""), QString("degrees"), UAVObjectField::FLOAT32, HeadingElemNames, QStringList(), QString("")));
    QStringList GroundspeedElemNames;
    GroundspeedElemNames.append("0");
    fields.append( new UAVObjectField(QString("Groundspeed"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, GroundspeedElemNames, QStringList(), QString("")));
    QStringList PDOPElemNames;
    PDOPElemNames.append("0");
    fields.append( new UAVObjectField(QString("PDOP"), tr(""), QString(""), UAVObjectField::FLOAT32, PDOPElemNames, QStringList(), QString("")));
    QStringList HDOPElemNames;
    HDOPElemNames.append("0");
    fields.append( new UAVObjectField(QString("HDOP"), tr(""), QString(""), UAVObjectField::FLOAT32, HDOPElemNames, QStringList(), QString("")));
    QStringList VDOPElemNames;
    VDOPElemNames.append("0");
    fields.append( new UAVObjectField(QString("VDOP"), tr(""), QString(""), UAVObjectField::FLOAT32, VDOPElemNames, QStringList(), QString("")));
    QStringList StatusElemNames;
    StatusElemNames.append("0");
    QStringList StatusEnumOptions;
    StatusEnumOptions.append("NoGPS");
    StatusEnumOptions.append("NoFix");
    StatusEnumOptions.append("Fix2D");
    StatusEnumOptions.append("Fix3D");
    fields.append( new UAVObjectField(QString("Status"), tr(""), QString(""), UAVObjectField::ENUM, StatusElemNames, StatusEnumOptions, QString("")));
    QStringList SatellitesElemNames;
    SatellitesElemNames.append("0");
    fields.append( new UAVObjectField(QString("Satellites"), tr(""), QString(""), UAVObjectField::INT8, SatellitesElemNames, QStringList(), QString("")));
    QStringList SensorTypeElemNames;
    SensorTypeElemNames.append("0");
    QStringList SensorTypeEnumOptions;
    SensorTypeEnumOptions.append("Unknown");
    SensorTypeEnumOptions.append("NMEA");
    SensorTypeEnumOptions.append("UBX");
    SensorTypeEnumOptions.append("UBX7");
    SensorTypeEnumOptions.append("UBX8");
    fields.append( new UAVObjectField(QString("SensorType"), tr(""), QString(""), UAVObjectField::ENUM, SensorTypeElemNames, SensorTypeEnumOptions, QString("")));
    QStringList AutoConfigStatusElemNames;
    AutoConfigStatusElemNames.append("0");
    QStringList AutoConfigStatusEnumOptions;
    AutoConfigStatusEnumOptions.append("DISABLED");
    AutoConfigStatusEnumOptions.append("RUNNING");
    AutoConfigStatusEnumOptions.append("DONE");
    AutoConfigStatusEnumOptions.append("ERROR");
    fields.append( new UAVObjectField(QString("AutoConfigStatus"), tr(""), QString(""), UAVObjectField::ENUM, AutoConfigStatusElemNames, AutoConfigStatusEnumOptions, QString("")));

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
UAVObject::Metadata GPSPositionSensor::getDefaultMetadata()
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
void GPSPositionSensor::setDefaultFieldValues()
{
    data.SensorType = 0;
    data.AutoConfigStatus = 0;

}

/**
 * Get the object data fields
 */
GPSPositionSensor::DataFields GPSPositionSensor::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void GPSPositionSensor::setData(const DataFields& data)
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

void GPSPositionSensor::emitNotifications()
{
            //if (data.Latitude != oldData.Latitude)
            emit LatitudeChanged(data.Latitude);
        //if (data.Longitude != oldData.Longitude)
            emit LongitudeChanged(data.Longitude);
        //if (data.Altitude != oldData.Altitude)
            emit AltitudeChanged(data.Altitude);
        //if (data.GeoidSeparation != oldData.GeoidSeparation)
            emit GeoidSeparationChanged(data.GeoidSeparation);
        //if (data.Heading != oldData.Heading)
            emit HeadingChanged(data.Heading);
        //if (data.Groundspeed != oldData.Groundspeed)
            emit GroundspeedChanged(data.Groundspeed);
        //if (data.PDOP != oldData.PDOP)
            emit PDOPChanged(data.PDOP);
        //if (data.HDOP != oldData.HDOP)
            emit HDOPChanged(data.HDOP);
        //if (data.VDOP != oldData.VDOP)
            emit VDOPChanged(data.VDOP);
        //if (data.Status != oldData.Status)
            emit StatusChanged(data.Status);
        //if (data.Satellites != oldData.Satellites)
            emit SatellitesChanged(data.Satellites);
        //if (data.SensorType != oldData.SensorType)
            emit SensorTypeChanged(data.SensorType);
        //if (data.AutoConfigStatus != oldData.AutoConfigStatus)
            emit AutoConfigStatusChanged(data.AutoConfigStatus);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *GPSPositionSensor::clone(quint32 instID)
{
    GPSPositionSensor *obj = new GPSPositionSensor();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *GPSPositionSensor::dirtyClone()
{
    GPSPositionSensor *obj = new GPSPositionSensor();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
GPSPositionSensor *GPSPositionSensor::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<GPSPositionSensor *>(objMngr->getObject(GPSPositionSensor::OBJID, instID));
}

qint32 GPSPositionSensor::getLatitude() const
{
   QMutexLocker locker(mutex);
   return data.Latitude;
}
void GPSPositionSensor::setLatitude(qint32 value)
{
   mutex->lock();
   bool changed = data.Latitude != value;
   data.Latitude = value;
   mutex->unlock();
   if (changed) emit LatitudeChanged(value);
}

qint32 GPSPositionSensor::getLongitude() const
{
   QMutexLocker locker(mutex);
   return data.Longitude;
}
void GPSPositionSensor::setLongitude(qint32 value)
{
   mutex->lock();
   bool changed = data.Longitude != value;
   data.Longitude = value;
   mutex->unlock();
   if (changed) emit LongitudeChanged(value);
}

float GPSPositionSensor::getAltitude() const
{
   QMutexLocker locker(mutex);
   return data.Altitude;
}
void GPSPositionSensor::setAltitude(float value)
{
   mutex->lock();
   bool changed = data.Altitude != value;
   data.Altitude = value;
   mutex->unlock();
   if (changed) emit AltitudeChanged(value);
}

float GPSPositionSensor::getGeoidSeparation() const
{
   QMutexLocker locker(mutex);
   return data.GeoidSeparation;
}
void GPSPositionSensor::setGeoidSeparation(float value)
{
   mutex->lock();
   bool changed = data.GeoidSeparation != value;
   data.GeoidSeparation = value;
   mutex->unlock();
   if (changed) emit GeoidSeparationChanged(value);
}

float GPSPositionSensor::getHeading() const
{
   QMutexLocker locker(mutex);
   return data.Heading;
}
void GPSPositionSensor::setHeading(float value)
{
   mutex->lock();
   bool changed = data.Heading != value;
   data.Heading = value;
   mutex->unlock();
   if (changed) emit HeadingChanged(value);
}

float GPSPositionSensor::getGroundspeed() const
{
   QMutexLocker locker(mutex);
   return data.Groundspeed;
}
void GPSPositionSensor::setGroundspeed(float value)
{
   mutex->lock();
   bool changed = data.Groundspeed != value;
   data.Groundspeed = value;
   mutex->unlock();
   if (changed) emit GroundspeedChanged(value);
}

float GPSPositionSensor::getPDOP() const
{
   QMutexLocker locker(mutex);
   return data.PDOP;
}
void GPSPositionSensor::setPDOP(float value)
{
   mutex->lock();
   bool changed = data.PDOP != value;
   data.PDOP = value;
   mutex->unlock();
   if (changed) emit PDOPChanged(value);
}

float GPSPositionSensor::getHDOP() const
{
   QMutexLocker locker(mutex);
   return data.HDOP;
}
void GPSPositionSensor::setHDOP(float value)
{
   mutex->lock();
   bool changed = data.HDOP != value;
   data.HDOP = value;
   mutex->unlock();
   if (changed) emit HDOPChanged(value);
}

float GPSPositionSensor::getVDOP() const
{
   QMutexLocker locker(mutex);
   return data.VDOP;
}
void GPSPositionSensor::setVDOP(float value)
{
   mutex->lock();
   bool changed = data.VDOP != value;
   data.VDOP = value;
   mutex->unlock();
   if (changed) emit VDOPChanged(value);
}

quint8 GPSPositionSensor::getStatus() const
{
   QMutexLocker locker(mutex);
   return data.Status;
}
void GPSPositionSensor::setStatus(quint8 value)
{
   mutex->lock();
   bool changed = data.Status != value;
   data.Status = value;
   mutex->unlock();
   if (changed) emit StatusChanged(value);
}

qint8 GPSPositionSensor::getSatellites() const
{
   QMutexLocker locker(mutex);
   return data.Satellites;
}
void GPSPositionSensor::setSatellites(qint8 value)
{
   mutex->lock();
   bool changed = data.Satellites != value;
   data.Satellites = value;
   mutex->unlock();
   if (changed) emit SatellitesChanged(value);
}

quint8 GPSPositionSensor::getSensorType() const
{
   QMutexLocker locker(mutex);
   return data.SensorType;
}
void GPSPositionSensor::setSensorType(quint8 value)
{
   mutex->lock();
   bool changed = data.SensorType != value;
   data.SensorType = value;
   mutex->unlock();
   if (changed) emit SensorTypeChanged(value);
}

quint8 GPSPositionSensor::getAutoConfigStatus() const
{
   QMutexLocker locker(mutex);
   return data.AutoConfigStatus;
}
void GPSPositionSensor::setAutoConfigStatus(quint8 value)
{
   mutex->lock();
   bool changed = data.AutoConfigStatus != value;
   data.AutoConfigStatus = value;
   mutex->unlock();
   if (changed) emit AutoConfigStatusChanged(value);
}


