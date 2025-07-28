/**
 ******************************************************************************
 *
 * @file       homelocation.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: homelocation.xml.
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

#include "homelocation.h"
#include "uavobjectfield.h"

const QString HomeLocation::NAME = QString("HomeLocation");
const QString HomeLocation::DESCRIPTION = QString("HomeLocation setting which contains the constants to translate from longitude and latitude to NED reference frame.  Automatically set by @ref GPSModule after acquiring a 3D lock.  Used by @ref AHRSCommsModule.");
const QString HomeLocation::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
HomeLocation::HomeLocation(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList LatitudeElemNames;
    LatitudeElemNames.append("0");
    fields.append( new UAVObjectField(QString("Latitude"), tr(""), QString("deg * 10e6"), UAVObjectField::INT32, LatitudeElemNames, QStringList(), QString("")));
    QStringList LongitudeElemNames;
    LongitudeElemNames.append("0");
    fields.append( new UAVObjectField(QString("Longitude"), tr(""), QString("deg * 10e6"), UAVObjectField::INT32, LongitudeElemNames, QStringList(), QString("")));
    QStringList AltitudeElemNames;
    AltitudeElemNames.append("0");
    fields.append( new UAVObjectField(QString("Altitude"), tr(""), QString("m over geoid"), UAVObjectField::FLOAT32, AltitudeElemNames, QStringList(), QString("")));
    QStringList BeElemNames;
    BeElemNames.append("0");
    BeElemNames.append("1");
    BeElemNames.append("2");
    fields.append( new UAVObjectField(QString("Be"), tr(""), QString(""), UAVObjectField::FLOAT32, BeElemNames, QStringList(), QString("")));
    QStringList g_eElemNames;
    g_eElemNames.append("0");
    fields.append( new UAVObjectField(QString("g_e"), tr(""), QString("m/s^2"), UAVObjectField::FLOAT32, g_eElemNames, QStringList(), QString("")));
    QStringList SetElemNames;
    SetElemNames.append("0");
    QStringList SetEnumOptions;
    SetEnumOptions.append("FALSE");
    SetEnumOptions.append("TRUE");
    fields.append( new UAVObjectField(QString("Set"), tr(""), QString(""), UAVObjectField::ENUM, SetElemNames, SetEnumOptions, QString("")));

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
UAVObject::Metadata HomeLocation::getDefaultMetadata()
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
void HomeLocation::setDefaultFieldValues()
{
    data.Latitude = 0;
    data.Longitude = 0;
    data.Altitude = 0;
    data.Be[0] = 0;
    data.Be[1] = 0;
    data.Be[2] = 0;
    data.g_e = 9.81;
    data.Set = 0;

}

/**
 * Get the object data fields
 */
HomeLocation::DataFields HomeLocation::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void HomeLocation::setData(const DataFields& data)
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

void HomeLocation::emitNotifications()
{
            //if (data.Latitude != oldData.Latitude)
            emit LatitudeChanged(data.Latitude);
        //if (data.Longitude != oldData.Longitude)
            emit LongitudeChanged(data.Longitude);
        //if (data.Altitude != oldData.Altitude)
            emit AltitudeChanged(data.Altitude);
        //if (data.Be[0] != oldData.Be[0])
            emit Be_0Changed(data.Be[0]);
        //if (data.Be[1] != oldData.Be[1])
            emit Be_1Changed(data.Be[1]);
        //if (data.Be[2] != oldData.Be[2])
            emit Be_2Changed(data.Be[2]);
        //if (data.g_e != oldData.g_e)
            emit g_eChanged(data.g_e);
        //if (data.Set != oldData.Set)
            emit SetChanged(data.Set);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *HomeLocation::clone(quint32 instID)
{
    HomeLocation *obj = new HomeLocation();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *HomeLocation::dirtyClone()
{
    HomeLocation *obj = new HomeLocation();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
HomeLocation *HomeLocation::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<HomeLocation *>(objMngr->getObject(HomeLocation::OBJID, instID));
}

qint32 HomeLocation::getLatitude() const
{
   QMutexLocker locker(mutex);
   return data.Latitude;
}
void HomeLocation::setLatitude(qint32 value)
{
   mutex->lock();
   bool changed = data.Latitude != value;
   data.Latitude = value;
   mutex->unlock();
   if (changed) emit LatitudeChanged(value);
}

qint32 HomeLocation::getLongitude() const
{
   QMutexLocker locker(mutex);
   return data.Longitude;
}
void HomeLocation::setLongitude(qint32 value)
{
   mutex->lock();
   bool changed = data.Longitude != value;
   data.Longitude = value;
   mutex->unlock();
   if (changed) emit LongitudeChanged(value);
}

float HomeLocation::getAltitude() const
{
   QMutexLocker locker(mutex);
   return data.Altitude;
}
void HomeLocation::setAltitude(float value)
{
   mutex->lock();
   bool changed = data.Altitude != value;
   data.Altitude = value;
   mutex->unlock();
   if (changed) emit AltitudeChanged(value);
}

float HomeLocation::getBe(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Be[index];
}
void HomeLocation::setBe(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.Be[index] != value;
   data.Be[index] = value;
   mutex->unlock();
   if (changed) emit BeChanged(index,value);
}

float HomeLocation::getBe_0() const
{
   QMutexLocker locker(mutex);
   return data.Be[0];
}
void HomeLocation::setBe_0(float value)
{
   mutex->lock();
   bool changed = data.Be[0] != value;
   data.Be[0] = value;
   mutex->unlock();
   if (changed) emit Be_0Changed(value);
}

float HomeLocation::getBe_1() const
{
   QMutexLocker locker(mutex);
   return data.Be[1];
}
void HomeLocation::setBe_1(float value)
{
   mutex->lock();
   bool changed = data.Be[1] != value;
   data.Be[1] = value;
   mutex->unlock();
   if (changed) emit Be_1Changed(value);
}

float HomeLocation::getBe_2() const
{
   QMutexLocker locker(mutex);
   return data.Be[2];
}
void HomeLocation::setBe_2(float value)
{
   mutex->lock();
   bool changed = data.Be[2] != value;
   data.Be[2] = value;
   mutex->unlock();
   if (changed) emit Be_2Changed(value);
}

float HomeLocation::getg_e() const
{
   QMutexLocker locker(mutex);
   return data.g_e;
}
void HomeLocation::setg_e(float value)
{
   mutex->lock();
   bool changed = data.g_e != value;
   data.g_e = value;
   mutex->unlock();
   if (changed) emit g_eChanged(value);
}

quint8 HomeLocation::getSet() const
{
   QMutexLocker locker(mutex);
   return data.Set;
}
void HomeLocation::setSet(quint8 value)
{
   mutex->lock();
   bool changed = data.Set != value;
   data.Set = value;
   mutex->unlock();
   if (changed) emit SetChanged(value);
}


