/**
 ******************************************************************************
 *
 * @file       osdsettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: osdsettings.xml.
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

#include "osdsettings.h"
#include "uavobjectfield.h"

const QString OsdSettings::NAME = QString("OsdSettings");
const QString OsdSettings::DESCRIPTION = QString("OSD settings used by the OSDgen module");
const QString OsdSettings::CATEGORY = QString("System");

/**
 * Constructor
 */
OsdSettings::OsdSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList AttitudeSetupElemNames;
    AttitudeSetupElemNames.append("X");
    AttitudeSetupElemNames.append("Y");
    fields.append( new UAVObjectField(QString("AttitudeSetup"), tr(""), QString(""), UAVObjectField::INT16, AttitudeSetupElemNames, QStringList(), QString("")));
    QStringList TimeSetupElemNames;
    TimeSetupElemNames.append("X");
    TimeSetupElemNames.append("Y");
    fields.append( new UAVObjectField(QString("TimeSetup"), tr(""), QString(""), UAVObjectField::INT16, TimeSetupElemNames, QStringList(), QString("")));
    QStringList BatterySetupElemNames;
    BatterySetupElemNames.append("X");
    BatterySetupElemNames.append("Y");
    fields.append( new UAVObjectField(QString("BatterySetup"), tr(""), QString(""), UAVObjectField::INT16, BatterySetupElemNames, QStringList(), QString("")));
    QStringList SpeedSetupElemNames;
    SpeedSetupElemNames.append("X");
    SpeedSetupElemNames.append("Y");
    fields.append( new UAVObjectField(QString("SpeedSetup"), tr(""), QString(""), UAVObjectField::INT16, SpeedSetupElemNames, QStringList(), QString("")));
    QStringList AltitudeSetupElemNames;
    AltitudeSetupElemNames.append("X");
    AltitudeSetupElemNames.append("Y");
    fields.append( new UAVObjectField(QString("AltitudeSetup"), tr(""), QString(""), UAVObjectField::INT16, AltitudeSetupElemNames, QStringList(), QString("")));
    QStringList HeadingSetupElemNames;
    HeadingSetupElemNames.append("X");
    HeadingSetupElemNames.append("Y");
    fields.append( new UAVObjectField(QString("HeadingSetup"), tr(""), QString(""), UAVObjectField::INT16, HeadingSetupElemNames, QStringList(), QString("")));
    QStringList AttitudeElemNames;
    AttitudeElemNames.append("0");
    QStringList AttitudeEnumOptions;
    AttitudeEnumOptions.append("Disabled");
    AttitudeEnumOptions.append("Enabled");
    fields.append( new UAVObjectField(QString("Attitude"), tr(""), QString(""), UAVObjectField::ENUM, AttitudeElemNames, AttitudeEnumOptions, QString("")));
    QStringList TimeElemNames;
    TimeElemNames.append("0");
    QStringList TimeEnumOptions;
    TimeEnumOptions.append("Disabled");
    TimeEnumOptions.append("Enabled");
    fields.append( new UAVObjectField(QString("Time"), tr(""), QString(""), UAVObjectField::ENUM, TimeElemNames, TimeEnumOptions, QString("")));
    QStringList BatteryElemNames;
    BatteryElemNames.append("0");
    QStringList BatteryEnumOptions;
    BatteryEnumOptions.append("Disabled");
    BatteryEnumOptions.append("Enabled");
    fields.append( new UAVObjectField(QString("Battery"), tr(""), QString(""), UAVObjectField::ENUM, BatteryElemNames, BatteryEnumOptions, QString("")));
    QStringList SpeedElemNames;
    SpeedElemNames.append("0");
    QStringList SpeedEnumOptions;
    SpeedEnumOptions.append("Disabled");
    SpeedEnumOptions.append("Enabled");
    fields.append( new UAVObjectField(QString("Speed"), tr(""), QString(""), UAVObjectField::ENUM, SpeedElemNames, SpeedEnumOptions, QString("")));
    QStringList AltitudeElemNames;
    AltitudeElemNames.append("0");
    QStringList AltitudeEnumOptions;
    AltitudeEnumOptions.append("Disabled");
    AltitudeEnumOptions.append("Enabled");
    fields.append( new UAVObjectField(QString("Altitude"), tr(""), QString(""), UAVObjectField::ENUM, AltitudeElemNames, AltitudeEnumOptions, QString("")));
    QStringList HeadingElemNames;
    HeadingElemNames.append("0");
    QStringList HeadingEnumOptions;
    HeadingEnumOptions.append("Disabled");
    HeadingEnumOptions.append("Enabled");
    fields.append( new UAVObjectField(QString("Heading"), tr(""), QString(""), UAVObjectField::ENUM, HeadingElemNames, HeadingEnumOptions, QString("")));
    QStringList ScreenElemNames;
    ScreenElemNames.append("0");
    fields.append( new UAVObjectField(QString("Screen"), tr(""), QString(""), UAVObjectField::UINT8, ScreenElemNames, QStringList(), QString("")));
    QStringList WhiteElemNames;
    WhiteElemNames.append("0");
    fields.append( new UAVObjectField(QString("White"), tr(""), QString(""), UAVObjectField::UINT8, WhiteElemNames, QStringList(), QString("")));
    QStringList BlackElemNames;
    BlackElemNames.append("0");
    fields.append( new UAVObjectField(QString("Black"), tr(""), QString(""), UAVObjectField::UINT8, BlackElemNames, QStringList(), QString("")));
    QStringList AltitudeSourceElemNames;
    AltitudeSourceElemNames.append("0");
    QStringList AltitudeSourceEnumOptions;
    AltitudeSourceEnumOptions.append("GPS");
    AltitudeSourceEnumOptions.append("Baro");
    fields.append( new UAVObjectField(QString("AltitudeSource"), tr(""), QString(""), UAVObjectField::ENUM, AltitudeSourceElemNames, AltitudeSourceEnumOptions, QString("")));

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
UAVObject::Metadata OsdSettings::getDefaultMetadata()
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
void OsdSettings::setDefaultFieldValues()
{
    data.AttitudeSetup[0] = 168;
    data.AttitudeSetup[1] = 135;
    data.TimeSetup[0] = 10;
    data.TimeSetup[1] = 250;
    data.BatterySetup[0] = 316;
    data.BatterySetup[1] = 210;
    data.SpeedSetup[0] = 2;
    data.SpeedSetup[1] = 145;
    data.AltitudeSetup[0] = 2;
    data.AltitudeSetup[1] = 145;
    data.HeadingSetup[0] = 168;
    data.HeadingSetup[1] = 240;
    data.Attitude = 1;
    data.Time = 1;
    data.Battery = 1;
    data.Speed = 1;
    data.Altitude = 1;
    data.Heading = 1;
    data.Screen = 0;
    data.White = 4;
    data.Black = 1;
    data.AltitudeSource = 0;

}

/**
 * Get the object data fields
 */
OsdSettings::DataFields OsdSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void OsdSettings::setData(const DataFields& data)
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

void OsdSettings::emitNotifications()
{
            //if (data.AttitudeSetup[0] != oldData.AttitudeSetup[0])
            emit AttitudeSetup_XChanged(data.AttitudeSetup[0]);
        //if (data.AttitudeSetup[1] != oldData.AttitudeSetup[1])
            emit AttitudeSetup_YChanged(data.AttitudeSetup[1]);
        //if (data.TimeSetup[0] != oldData.TimeSetup[0])
            emit TimeSetup_XChanged(data.TimeSetup[0]);
        //if (data.TimeSetup[1] != oldData.TimeSetup[1])
            emit TimeSetup_YChanged(data.TimeSetup[1]);
        //if (data.BatterySetup[0] != oldData.BatterySetup[0])
            emit BatterySetup_XChanged(data.BatterySetup[0]);
        //if (data.BatterySetup[1] != oldData.BatterySetup[1])
            emit BatterySetup_YChanged(data.BatterySetup[1]);
        //if (data.SpeedSetup[0] != oldData.SpeedSetup[0])
            emit SpeedSetup_XChanged(data.SpeedSetup[0]);
        //if (data.SpeedSetup[1] != oldData.SpeedSetup[1])
            emit SpeedSetup_YChanged(data.SpeedSetup[1]);
        //if (data.AltitudeSetup[0] != oldData.AltitudeSetup[0])
            emit AltitudeSetup_XChanged(data.AltitudeSetup[0]);
        //if (data.AltitudeSetup[1] != oldData.AltitudeSetup[1])
            emit AltitudeSetup_YChanged(data.AltitudeSetup[1]);
        //if (data.HeadingSetup[0] != oldData.HeadingSetup[0])
            emit HeadingSetup_XChanged(data.HeadingSetup[0]);
        //if (data.HeadingSetup[1] != oldData.HeadingSetup[1])
            emit HeadingSetup_YChanged(data.HeadingSetup[1]);
        //if (data.Attitude != oldData.Attitude)
            emit AttitudeChanged(data.Attitude);
        //if (data.Time != oldData.Time)
            emit TimeChanged(data.Time);
        //if (data.Battery != oldData.Battery)
            emit BatteryChanged(data.Battery);
        //if (data.Speed != oldData.Speed)
            emit SpeedChanged(data.Speed);
        //if (data.Altitude != oldData.Altitude)
            emit AltitudeChanged(data.Altitude);
        //if (data.Heading != oldData.Heading)
            emit HeadingChanged(data.Heading);
        //if (data.Screen != oldData.Screen)
            emit ScreenChanged(data.Screen);
        //if (data.White != oldData.White)
            emit WhiteChanged(data.White);
        //if (data.Black != oldData.Black)
            emit BlackChanged(data.Black);
        //if (data.AltitudeSource != oldData.AltitudeSource)
            emit AltitudeSourceChanged(data.AltitudeSource);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *OsdSettings::clone(quint32 instID)
{
    OsdSettings *obj = new OsdSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *OsdSettings::dirtyClone()
{
    OsdSettings *obj = new OsdSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
OsdSettings *OsdSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<OsdSettings *>(objMngr->getObject(OsdSettings::OBJID, instID));
}

qint16 OsdSettings::getAttitudeSetup(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.AttitudeSetup[index];
}
void OsdSettings::setAttitudeSetup(quint32 index, qint16 value)
{
   mutex->lock();
   bool changed = data.AttitudeSetup[index] != value;
   data.AttitudeSetup[index] = value;
   mutex->unlock();
   if (changed) emit AttitudeSetupChanged(index,value);
}

qint16 OsdSettings::getAttitudeSetup_X() const
{
   QMutexLocker locker(mutex);
   return data.AttitudeSetup[0];
}
void OsdSettings::setAttitudeSetup_X(qint16 value)
{
   mutex->lock();
   bool changed = data.AttitudeSetup[0] != value;
   data.AttitudeSetup[0] = value;
   mutex->unlock();
   if (changed) emit AttitudeSetup_XChanged(value);
}

qint16 OsdSettings::getAttitudeSetup_Y() const
{
   QMutexLocker locker(mutex);
   return data.AttitudeSetup[1];
}
void OsdSettings::setAttitudeSetup_Y(qint16 value)
{
   mutex->lock();
   bool changed = data.AttitudeSetup[1] != value;
   data.AttitudeSetup[1] = value;
   mutex->unlock();
   if (changed) emit AttitudeSetup_YChanged(value);
}

qint16 OsdSettings::getTimeSetup(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.TimeSetup[index];
}
void OsdSettings::setTimeSetup(quint32 index, qint16 value)
{
   mutex->lock();
   bool changed = data.TimeSetup[index] != value;
   data.TimeSetup[index] = value;
   mutex->unlock();
   if (changed) emit TimeSetupChanged(index,value);
}

qint16 OsdSettings::getTimeSetup_X() const
{
   QMutexLocker locker(mutex);
   return data.TimeSetup[0];
}
void OsdSettings::setTimeSetup_X(qint16 value)
{
   mutex->lock();
   bool changed = data.TimeSetup[0] != value;
   data.TimeSetup[0] = value;
   mutex->unlock();
   if (changed) emit TimeSetup_XChanged(value);
}

qint16 OsdSettings::getTimeSetup_Y() const
{
   QMutexLocker locker(mutex);
   return data.TimeSetup[1];
}
void OsdSettings::setTimeSetup_Y(qint16 value)
{
   mutex->lock();
   bool changed = data.TimeSetup[1] != value;
   data.TimeSetup[1] = value;
   mutex->unlock();
   if (changed) emit TimeSetup_YChanged(value);
}

qint16 OsdSettings::getBatterySetup(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.BatterySetup[index];
}
void OsdSettings::setBatterySetup(quint32 index, qint16 value)
{
   mutex->lock();
   bool changed = data.BatterySetup[index] != value;
   data.BatterySetup[index] = value;
   mutex->unlock();
   if (changed) emit BatterySetupChanged(index,value);
}

qint16 OsdSettings::getBatterySetup_X() const
{
   QMutexLocker locker(mutex);
   return data.BatterySetup[0];
}
void OsdSettings::setBatterySetup_X(qint16 value)
{
   mutex->lock();
   bool changed = data.BatterySetup[0] != value;
   data.BatterySetup[0] = value;
   mutex->unlock();
   if (changed) emit BatterySetup_XChanged(value);
}

qint16 OsdSettings::getBatterySetup_Y() const
{
   QMutexLocker locker(mutex);
   return data.BatterySetup[1];
}
void OsdSettings::setBatterySetup_Y(qint16 value)
{
   mutex->lock();
   bool changed = data.BatterySetup[1] != value;
   data.BatterySetup[1] = value;
   mutex->unlock();
   if (changed) emit BatterySetup_YChanged(value);
}

qint16 OsdSettings::getSpeedSetup(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.SpeedSetup[index];
}
void OsdSettings::setSpeedSetup(quint32 index, qint16 value)
{
   mutex->lock();
   bool changed = data.SpeedSetup[index] != value;
   data.SpeedSetup[index] = value;
   mutex->unlock();
   if (changed) emit SpeedSetupChanged(index,value);
}

qint16 OsdSettings::getSpeedSetup_X() const
{
   QMutexLocker locker(mutex);
   return data.SpeedSetup[0];
}
void OsdSettings::setSpeedSetup_X(qint16 value)
{
   mutex->lock();
   bool changed = data.SpeedSetup[0] != value;
   data.SpeedSetup[0] = value;
   mutex->unlock();
   if (changed) emit SpeedSetup_XChanged(value);
}

qint16 OsdSettings::getSpeedSetup_Y() const
{
   QMutexLocker locker(mutex);
   return data.SpeedSetup[1];
}
void OsdSettings::setSpeedSetup_Y(qint16 value)
{
   mutex->lock();
   bool changed = data.SpeedSetup[1] != value;
   data.SpeedSetup[1] = value;
   mutex->unlock();
   if (changed) emit SpeedSetup_YChanged(value);
}

qint16 OsdSettings::getAltitudeSetup(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.AltitudeSetup[index];
}
void OsdSettings::setAltitudeSetup(quint32 index, qint16 value)
{
   mutex->lock();
   bool changed = data.AltitudeSetup[index] != value;
   data.AltitudeSetup[index] = value;
   mutex->unlock();
   if (changed) emit AltitudeSetupChanged(index,value);
}

qint16 OsdSettings::getAltitudeSetup_X() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeSetup[0];
}
void OsdSettings::setAltitudeSetup_X(qint16 value)
{
   mutex->lock();
   bool changed = data.AltitudeSetup[0] != value;
   data.AltitudeSetup[0] = value;
   mutex->unlock();
   if (changed) emit AltitudeSetup_XChanged(value);
}

qint16 OsdSettings::getAltitudeSetup_Y() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeSetup[1];
}
void OsdSettings::setAltitudeSetup_Y(qint16 value)
{
   mutex->lock();
   bool changed = data.AltitudeSetup[1] != value;
   data.AltitudeSetup[1] = value;
   mutex->unlock();
   if (changed) emit AltitudeSetup_YChanged(value);
}

qint16 OsdSettings::getHeadingSetup(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.HeadingSetup[index];
}
void OsdSettings::setHeadingSetup(quint32 index, qint16 value)
{
   mutex->lock();
   bool changed = data.HeadingSetup[index] != value;
   data.HeadingSetup[index] = value;
   mutex->unlock();
   if (changed) emit HeadingSetupChanged(index,value);
}

qint16 OsdSettings::getHeadingSetup_X() const
{
   QMutexLocker locker(mutex);
   return data.HeadingSetup[0];
}
void OsdSettings::setHeadingSetup_X(qint16 value)
{
   mutex->lock();
   bool changed = data.HeadingSetup[0] != value;
   data.HeadingSetup[0] = value;
   mutex->unlock();
   if (changed) emit HeadingSetup_XChanged(value);
}

qint16 OsdSettings::getHeadingSetup_Y() const
{
   QMutexLocker locker(mutex);
   return data.HeadingSetup[1];
}
void OsdSettings::setHeadingSetup_Y(qint16 value)
{
   mutex->lock();
   bool changed = data.HeadingSetup[1] != value;
   data.HeadingSetup[1] = value;
   mutex->unlock();
   if (changed) emit HeadingSetup_YChanged(value);
}

quint8 OsdSettings::getAttitude() const
{
   QMutexLocker locker(mutex);
   return data.Attitude;
}
void OsdSettings::setAttitude(quint8 value)
{
   mutex->lock();
   bool changed = data.Attitude != value;
   data.Attitude = value;
   mutex->unlock();
   if (changed) emit AttitudeChanged(value);
}

quint8 OsdSettings::getTime() const
{
   QMutexLocker locker(mutex);
   return data.Time;
}
void OsdSettings::setTime(quint8 value)
{
   mutex->lock();
   bool changed = data.Time != value;
   data.Time = value;
   mutex->unlock();
   if (changed) emit TimeChanged(value);
}

quint8 OsdSettings::getBattery() const
{
   QMutexLocker locker(mutex);
   return data.Battery;
}
void OsdSettings::setBattery(quint8 value)
{
   mutex->lock();
   bool changed = data.Battery != value;
   data.Battery = value;
   mutex->unlock();
   if (changed) emit BatteryChanged(value);
}

quint8 OsdSettings::getSpeed() const
{
   QMutexLocker locker(mutex);
   return data.Speed;
}
void OsdSettings::setSpeed(quint8 value)
{
   mutex->lock();
   bool changed = data.Speed != value;
   data.Speed = value;
   mutex->unlock();
   if (changed) emit SpeedChanged(value);
}

quint8 OsdSettings::getAltitude() const
{
   QMutexLocker locker(mutex);
   return data.Altitude;
}
void OsdSettings::setAltitude(quint8 value)
{
   mutex->lock();
   bool changed = data.Altitude != value;
   data.Altitude = value;
   mutex->unlock();
   if (changed) emit AltitudeChanged(value);
}

quint8 OsdSettings::getHeading() const
{
   QMutexLocker locker(mutex);
   return data.Heading;
}
void OsdSettings::setHeading(quint8 value)
{
   mutex->lock();
   bool changed = data.Heading != value;
   data.Heading = value;
   mutex->unlock();
   if (changed) emit HeadingChanged(value);
}

quint8 OsdSettings::getScreen() const
{
   QMutexLocker locker(mutex);
   return data.Screen;
}
void OsdSettings::setScreen(quint8 value)
{
   mutex->lock();
   bool changed = data.Screen != value;
   data.Screen = value;
   mutex->unlock();
   if (changed) emit ScreenChanged(value);
}

quint8 OsdSettings::getWhite() const
{
   QMutexLocker locker(mutex);
   return data.White;
}
void OsdSettings::setWhite(quint8 value)
{
   mutex->lock();
   bool changed = data.White != value;
   data.White = value;
   mutex->unlock();
   if (changed) emit WhiteChanged(value);
}

quint8 OsdSettings::getBlack() const
{
   QMutexLocker locker(mutex);
   return data.Black;
}
void OsdSettings::setBlack(quint8 value)
{
   mutex->lock();
   bool changed = data.Black != value;
   data.Black = value;
   mutex->unlock();
   if (changed) emit BlackChanged(value);
}

quint8 OsdSettings::getAltitudeSource() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeSource;
}
void OsdSettings::setAltitudeSource(quint8 value)
{
   mutex->lock();
   bool changed = data.AltitudeSource != value;
   data.AltitudeSource = value;
   mutex->unlock();
   if (changed) emit AltitudeSourceChanged(value);
}


