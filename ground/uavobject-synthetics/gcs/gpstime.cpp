/**
 ******************************************************************************
 *
 * @file       gpstime.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: gpstime.xml.
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

#include "gpstime.h"
#include "uavobjectfield.h"

const QString GPSTime::NAME = QString("GPSTime");
const QString GPSTime::DESCRIPTION = QString("Contains the GPS time from @ref GPSModule.  Required to compute the world magnetic model correctly when setting the home location.");
const QString GPSTime::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
GPSTime::GPSTime(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList YearElemNames;
    YearElemNames.append("0");
    fields.append( new UAVObjectField(QString("Year"), tr(""), QString(""), UAVObjectField::INT16, YearElemNames, QStringList(), QString("")));
    QStringList MonthElemNames;
    MonthElemNames.append("0");
    fields.append( new UAVObjectField(QString("Month"), tr(""), QString(""), UAVObjectField::INT8, MonthElemNames, QStringList(), QString("")));
    QStringList DayElemNames;
    DayElemNames.append("0");
    fields.append( new UAVObjectField(QString("Day"), tr(""), QString(""), UAVObjectField::INT8, DayElemNames, QStringList(), QString("")));
    QStringList HourElemNames;
    HourElemNames.append("0");
    fields.append( new UAVObjectField(QString("Hour"), tr(""), QString(""), UAVObjectField::INT8, HourElemNames, QStringList(), QString("")));
    QStringList MinuteElemNames;
    MinuteElemNames.append("0");
    fields.append( new UAVObjectField(QString("Minute"), tr(""), QString(""), UAVObjectField::INT8, MinuteElemNames, QStringList(), QString("")));
    QStringList SecondElemNames;
    SecondElemNames.append("0");
    fields.append( new UAVObjectField(QString("Second"), tr(""), QString(""), UAVObjectField::INT8, SecondElemNames, QStringList(), QString("")));

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
UAVObject::Metadata GPSTime::getDefaultMetadata()
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
void GPSTime::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
GPSTime::DataFields GPSTime::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void GPSTime::setData(const DataFields& data)
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

void GPSTime::emitNotifications()
{
            //if (data.Year != oldData.Year)
            emit YearChanged(data.Year);
        //if (data.Month != oldData.Month)
            emit MonthChanged(data.Month);
        //if (data.Day != oldData.Day)
            emit DayChanged(data.Day);
        //if (data.Hour != oldData.Hour)
            emit HourChanged(data.Hour);
        //if (data.Minute != oldData.Minute)
            emit MinuteChanged(data.Minute);
        //if (data.Second != oldData.Second)
            emit SecondChanged(data.Second);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *GPSTime::clone(quint32 instID)
{
    GPSTime *obj = new GPSTime();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *GPSTime::dirtyClone()
{
    GPSTime *obj = new GPSTime();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
GPSTime *GPSTime::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<GPSTime *>(objMngr->getObject(GPSTime::OBJID, instID));
}

qint16 GPSTime::getYear() const
{
   QMutexLocker locker(mutex);
   return data.Year;
}
void GPSTime::setYear(qint16 value)
{
   mutex->lock();
   bool changed = data.Year != value;
   data.Year = value;
   mutex->unlock();
   if (changed) emit YearChanged(value);
}

qint8 GPSTime::getMonth() const
{
   QMutexLocker locker(mutex);
   return data.Month;
}
void GPSTime::setMonth(qint8 value)
{
   mutex->lock();
   bool changed = data.Month != value;
   data.Month = value;
   mutex->unlock();
   if (changed) emit MonthChanged(value);
}

qint8 GPSTime::getDay() const
{
   QMutexLocker locker(mutex);
   return data.Day;
}
void GPSTime::setDay(qint8 value)
{
   mutex->lock();
   bool changed = data.Day != value;
   data.Day = value;
   mutex->unlock();
   if (changed) emit DayChanged(value);
}

qint8 GPSTime::getHour() const
{
   QMutexLocker locker(mutex);
   return data.Hour;
}
void GPSTime::setHour(qint8 value)
{
   mutex->lock();
   bool changed = data.Hour != value;
   data.Hour = value;
   mutex->unlock();
   if (changed) emit HourChanged(value);
}

qint8 GPSTime::getMinute() const
{
   QMutexLocker locker(mutex);
   return data.Minute;
}
void GPSTime::setMinute(qint8 value)
{
   mutex->lock();
   bool changed = data.Minute != value;
   data.Minute = value;
   mutex->unlock();
   if (changed) emit MinuteChanged(value);
}

qint8 GPSTime::getSecond() const
{
   QMutexLocker locker(mutex);
   return data.Second;
}
void GPSTime::setSecond(qint8 value)
{
   mutex->lock();
   bool changed = data.Second != value;
   data.Second = value;
   mutex->unlock();
   if (changed) emit SecondChanged(value);
}


