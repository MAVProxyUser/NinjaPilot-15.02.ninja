/**
 ******************************************************************************
 *
 * @file       oplinksettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: oplinksettings.xml.
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

#include "oplinksettings.h"
#include "uavobjectfield.h"

const QString OPLinkSettings::NAME = QString("OPLinkSettings");
const QString OPLinkSettings::DESCRIPTION = QString("OPLink configurations options.");
const QString OPLinkSettings::CATEGORY = QString("System");

/**
 * Constructor
 */
OPLinkSettings::OPLinkSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList CoordIDElemNames;
    CoordIDElemNames.append("0");
    fields.append( new UAVObjectField(QString("CoordID"), tr(""), QString("hex"), UAVObjectField::UINT32, CoordIDElemNames, QStringList(), QString("")));
    QStringList CoordinatorElemNames;
    CoordinatorElemNames.append("0");
    QStringList CoordinatorEnumOptions;
    CoordinatorEnumOptions.append("FALSE");
    CoordinatorEnumOptions.append("TRUE");
    fields.append( new UAVObjectField(QString("Coordinator"), tr(""), QString(""), UAVObjectField::ENUM, CoordinatorElemNames, CoordinatorEnumOptions, QString("")));
    QStringList OneWayElemNames;
    OneWayElemNames.append("0");
    QStringList OneWayEnumOptions;
    OneWayEnumOptions.append("FALSE");
    OneWayEnumOptions.append("TRUE");
    fields.append( new UAVObjectField(QString("OneWay"), tr(""), QString(""), UAVObjectField::ENUM, OneWayElemNames, OneWayEnumOptions, QString("")));
    QStringList PPMElemNames;
    PPMElemNames.append("0");
    QStringList PPMEnumOptions;
    PPMEnumOptions.append("FALSE");
    PPMEnumOptions.append("TRUE");
    fields.append( new UAVObjectField(QString("PPM"), tr(""), QString(""), UAVObjectField::ENUM, PPMElemNames, PPMEnumOptions, QString("")));
    QStringList PPMOnlyElemNames;
    PPMOnlyElemNames.append("0");
    QStringList PPMOnlyEnumOptions;
    PPMOnlyEnumOptions.append("FALSE");
    PPMOnlyEnumOptions.append("TRUE");
    fields.append( new UAVObjectField(QString("PPMOnly"), tr(""), QString(""), UAVObjectField::ENUM, PPMOnlyElemNames, PPMOnlyEnumOptions, QString("")));
    QStringList MainPortElemNames;
    MainPortElemNames.append("0");
    QStringList MainPortEnumOptions;
    MainPortEnumOptions.append("Disabled");
    MainPortEnumOptions.append("Telemetry");
    MainPortEnumOptions.append("Serial");
    MainPortEnumOptions.append("PPM");
    MainPortEnumOptions.append("PWM");
    fields.append( new UAVObjectField(QString("MainPort"), tr(""), QString(""), UAVObjectField::ENUM, MainPortElemNames, MainPortEnumOptions, QString("")));
    QStringList FlexiPortElemNames;
    FlexiPortElemNames.append("0");
    QStringList FlexiPortEnumOptions;
    FlexiPortEnumOptions.append("Disabled");
    FlexiPortEnumOptions.append("Telemetry");
    FlexiPortEnumOptions.append("Serial");
    FlexiPortEnumOptions.append("PPM");
    FlexiPortEnumOptions.append("PWM");
    fields.append( new UAVObjectField(QString("FlexiPort"), tr(""), QString(""), UAVObjectField::ENUM, FlexiPortElemNames, FlexiPortEnumOptions, QString("")));
    QStringList VCPPortElemNames;
    VCPPortElemNames.append("0");
    QStringList VCPPortEnumOptions;
    VCPPortEnumOptions.append("Disabled");
    VCPPortEnumOptions.append("Serial");
    fields.append( new UAVObjectField(QString("VCPPort"), tr(""), QString(""), UAVObjectField::ENUM, VCPPortElemNames, VCPPortEnumOptions, QString("")));
    QStringList ComSpeedElemNames;
    ComSpeedElemNames.append("0");
    QStringList ComSpeedEnumOptions;
    ComSpeedEnumOptions.append("4800");
    ComSpeedEnumOptions.append("9600");
    ComSpeedEnumOptions.append("19200");
    ComSpeedEnumOptions.append("38400");
    ComSpeedEnumOptions.append("57600");
    ComSpeedEnumOptions.append("115200");
    fields.append( new UAVObjectField(QString("ComSpeed"), tr(""), QString("bps"), UAVObjectField::ENUM, ComSpeedElemNames, ComSpeedEnumOptions, QString("")));
    QStringList MaxRFPowerElemNames;
    MaxRFPowerElemNames.append("0");
    QStringList MaxRFPowerEnumOptions;
    MaxRFPowerEnumOptions.append("0");
    MaxRFPowerEnumOptions.append("1.25");
    MaxRFPowerEnumOptions.append("1.6");
    MaxRFPowerEnumOptions.append("3.16");
    MaxRFPowerEnumOptions.append("6.3");
    MaxRFPowerEnumOptions.append("12.6");
    MaxRFPowerEnumOptions.append("25");
    MaxRFPowerEnumOptions.append("50");
    MaxRFPowerEnumOptions.append("100");
    fields.append( new UAVObjectField(QString("MaxRFPower"), tr(""), QString("mW"), UAVObjectField::ENUM, MaxRFPowerElemNames, MaxRFPowerEnumOptions, QString("")));
    QStringList MinChannelElemNames;
    MinChannelElemNames.append("0");
    fields.append( new UAVObjectField(QString("MinChannel"), tr(""), QString(""), UAVObjectField::UINT8, MinChannelElemNames, QStringList(), QString("")));
    QStringList MaxChannelElemNames;
    MaxChannelElemNames.append("0");
    fields.append( new UAVObjectField(QString("MaxChannel"), tr(""), QString(""), UAVObjectField::UINT8, MaxChannelElemNames, QStringList(), QString("")));

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
UAVObject::Metadata OPLinkSettings::getDefaultMetadata()
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
void OPLinkSettings::setDefaultFieldValues()
{
    data.CoordID = 0;
    data.Coordinator = 0;
    data.OneWay = 0;
    data.PPM = 0;
    data.PPMOnly = 0;
    data.MainPort = 0;
    data.FlexiPort = 0;
    data.VCPPort = 0;
    data.ComSpeed = 3;
    data.MaxRFPower = 0;
    data.MinChannel = 0;
    data.MaxChannel = 250;

}

/**
 * Get the object data fields
 */
OPLinkSettings::DataFields OPLinkSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void OPLinkSettings::setData(const DataFields& data)
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

void OPLinkSettings::emitNotifications()
{
            //if (data.CoordID != oldData.CoordID)
            emit CoordIDChanged(data.CoordID);
        //if (data.Coordinator != oldData.Coordinator)
            emit CoordinatorChanged(data.Coordinator);
        //if (data.OneWay != oldData.OneWay)
            emit OneWayChanged(data.OneWay);
        //if (data.PPM != oldData.PPM)
            emit PPMChanged(data.PPM);
        //if (data.PPMOnly != oldData.PPMOnly)
            emit PPMOnlyChanged(data.PPMOnly);
        //if (data.MainPort != oldData.MainPort)
            emit MainPortChanged(data.MainPort);
        //if (data.FlexiPort != oldData.FlexiPort)
            emit FlexiPortChanged(data.FlexiPort);
        //if (data.VCPPort != oldData.VCPPort)
            emit VCPPortChanged(data.VCPPort);
        //if (data.ComSpeed != oldData.ComSpeed)
            emit ComSpeedChanged(data.ComSpeed);
        //if (data.MaxRFPower != oldData.MaxRFPower)
            emit MaxRFPowerChanged(data.MaxRFPower);
        //if (data.MinChannel != oldData.MinChannel)
            emit MinChannelChanged(data.MinChannel);
        //if (data.MaxChannel != oldData.MaxChannel)
            emit MaxChannelChanged(data.MaxChannel);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *OPLinkSettings::clone(quint32 instID)
{
    OPLinkSettings *obj = new OPLinkSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *OPLinkSettings::dirtyClone()
{
    OPLinkSettings *obj = new OPLinkSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
OPLinkSettings *OPLinkSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<OPLinkSettings *>(objMngr->getObject(OPLinkSettings::OBJID, instID));
}

quint32 OPLinkSettings::getCoordID() const
{
   QMutexLocker locker(mutex);
   return data.CoordID;
}
void OPLinkSettings::setCoordID(quint32 value)
{
   mutex->lock();
   bool changed = data.CoordID != value;
   data.CoordID = value;
   mutex->unlock();
   if (changed) emit CoordIDChanged(value);
}

quint8 OPLinkSettings::getCoordinator() const
{
   QMutexLocker locker(mutex);
   return data.Coordinator;
}
void OPLinkSettings::setCoordinator(quint8 value)
{
   mutex->lock();
   bool changed = data.Coordinator != value;
   data.Coordinator = value;
   mutex->unlock();
   if (changed) emit CoordinatorChanged(value);
}

quint8 OPLinkSettings::getOneWay() const
{
   QMutexLocker locker(mutex);
   return data.OneWay;
}
void OPLinkSettings::setOneWay(quint8 value)
{
   mutex->lock();
   bool changed = data.OneWay != value;
   data.OneWay = value;
   mutex->unlock();
   if (changed) emit OneWayChanged(value);
}

quint8 OPLinkSettings::getPPM() const
{
   QMutexLocker locker(mutex);
   return data.PPM;
}
void OPLinkSettings::setPPM(quint8 value)
{
   mutex->lock();
   bool changed = data.PPM != value;
   data.PPM = value;
   mutex->unlock();
   if (changed) emit PPMChanged(value);
}

quint8 OPLinkSettings::getPPMOnly() const
{
   QMutexLocker locker(mutex);
   return data.PPMOnly;
}
void OPLinkSettings::setPPMOnly(quint8 value)
{
   mutex->lock();
   bool changed = data.PPMOnly != value;
   data.PPMOnly = value;
   mutex->unlock();
   if (changed) emit PPMOnlyChanged(value);
}

quint8 OPLinkSettings::getMainPort() const
{
   QMutexLocker locker(mutex);
   return data.MainPort;
}
void OPLinkSettings::setMainPort(quint8 value)
{
   mutex->lock();
   bool changed = data.MainPort != value;
   data.MainPort = value;
   mutex->unlock();
   if (changed) emit MainPortChanged(value);
}

quint8 OPLinkSettings::getFlexiPort() const
{
   QMutexLocker locker(mutex);
   return data.FlexiPort;
}
void OPLinkSettings::setFlexiPort(quint8 value)
{
   mutex->lock();
   bool changed = data.FlexiPort != value;
   data.FlexiPort = value;
   mutex->unlock();
   if (changed) emit FlexiPortChanged(value);
}

quint8 OPLinkSettings::getVCPPort() const
{
   QMutexLocker locker(mutex);
   return data.VCPPort;
}
void OPLinkSettings::setVCPPort(quint8 value)
{
   mutex->lock();
   bool changed = data.VCPPort != value;
   data.VCPPort = value;
   mutex->unlock();
   if (changed) emit VCPPortChanged(value);
}

quint8 OPLinkSettings::getComSpeed() const
{
   QMutexLocker locker(mutex);
   return data.ComSpeed;
}
void OPLinkSettings::setComSpeed(quint8 value)
{
   mutex->lock();
   bool changed = data.ComSpeed != value;
   data.ComSpeed = value;
   mutex->unlock();
   if (changed) emit ComSpeedChanged(value);
}

quint8 OPLinkSettings::getMaxRFPower() const
{
   QMutexLocker locker(mutex);
   return data.MaxRFPower;
}
void OPLinkSettings::setMaxRFPower(quint8 value)
{
   mutex->lock();
   bool changed = data.MaxRFPower != value;
   data.MaxRFPower = value;
   mutex->unlock();
   if (changed) emit MaxRFPowerChanged(value);
}

quint8 OPLinkSettings::getMinChannel() const
{
   QMutexLocker locker(mutex);
   return data.MinChannel;
}
void OPLinkSettings::setMinChannel(quint8 value)
{
   mutex->lock();
   bool changed = data.MinChannel != value;
   data.MinChannel = value;
   mutex->unlock();
   if (changed) emit MinChannelChanged(value);
}

quint8 OPLinkSettings::getMaxChannel() const
{
   QMutexLocker locker(mutex);
   return data.MaxChannel;
}
void OPLinkSettings::setMaxChannel(quint8 value)
{
   mutex->lock();
   bool changed = data.MaxChannel != value;
   data.MaxChannel = value;
   mutex->unlock();
   if (changed) emit MaxChannelChanged(value);
}


