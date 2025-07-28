/**
 ******************************************************************************
 *
 * @file       manualcontrolcommand.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: manualcontrolcommand.xml.
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

#include "manualcontrolcommand.h"
#include "uavobjectfield.h"

const QString ManualControlCommand::NAME = QString("ManualControlCommand");
const QString ManualControlCommand::DESCRIPTION = QString("The output from the @ref ManualControlModule which decodes the receiver inputs. Overriden by GCS for fly-by-wire control.");
const QString ManualControlCommand::CATEGORY = QString("Control");

/**
 * Constructor
 */
ManualControlCommand::ManualControlCommand(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList ThrottleElemNames;
    ThrottleElemNames.append("0");
    fields.append( new UAVObjectField(QString("Throttle"), tr(""), QString("%"), UAVObjectField::FLOAT32, ThrottleElemNames, QStringList(), QString("")));
    QStringList RollElemNames;
    RollElemNames.append("0");
    fields.append( new UAVObjectField(QString("Roll"), tr(""), QString("%"), UAVObjectField::FLOAT32, RollElemNames, QStringList(), QString("")));
    QStringList PitchElemNames;
    PitchElemNames.append("0");
    fields.append( new UAVObjectField(QString("Pitch"), tr(""), QString("%"), UAVObjectField::FLOAT32, PitchElemNames, QStringList(), QString("")));
    QStringList YawElemNames;
    YawElemNames.append("0");
    fields.append( new UAVObjectField(QString("Yaw"), tr(""), QString("%"), UAVObjectField::FLOAT32, YawElemNames, QStringList(), QString("")));
    QStringList CollectiveElemNames;
    CollectiveElemNames.append("0");
    fields.append( new UAVObjectField(QString("Collective"), tr(""), QString("%"), UAVObjectField::FLOAT32, CollectiveElemNames, QStringList(), QString("")));
    QStringList ThrustElemNames;
    ThrustElemNames.append("0");
    fields.append( new UAVObjectField(QString("Thrust"), tr(""), QString("%"), UAVObjectField::FLOAT32, ThrustElemNames, QStringList(), QString("")));
    QStringList ChannelElemNames;
    ChannelElemNames.append("0");
    ChannelElemNames.append("1");
    ChannelElemNames.append("2");
    ChannelElemNames.append("3");
    ChannelElemNames.append("4");
    ChannelElemNames.append("5");
    ChannelElemNames.append("6");
    ChannelElemNames.append("7");
    ChannelElemNames.append("8");
    fields.append( new UAVObjectField(QString("Channel"), tr(""), QString("us"), UAVObjectField::UINT16, ChannelElemNames, QStringList(), QString("")));
    QStringList ConnectedElemNames;
    ConnectedElemNames.append("0");
    QStringList ConnectedEnumOptions;
    ConnectedEnumOptions.append("False");
    ConnectedEnumOptions.append("True");
    fields.append( new UAVObjectField(QString("Connected"), tr(""), QString(""), UAVObjectField::ENUM, ConnectedElemNames, ConnectedEnumOptions, QString("")));
    QStringList FlightModeSwitchPositionElemNames;
    FlightModeSwitchPositionElemNames.append("0");
    fields.append( new UAVObjectField(QString("FlightModeSwitchPosition"), tr(""), QString(""), UAVObjectField::UINT8, FlightModeSwitchPositionElemNames, QStringList(), QString("")));

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
UAVObject::Metadata ManualControlCommand::getDefaultMetadata()
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
    metadata.flightTelemetryUpdatePeriod = 2000;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void ManualControlCommand::setDefaultFieldValues()
{
    data.FlightModeSwitchPosition = 0;

}

/**
 * Get the object data fields
 */
ManualControlCommand::DataFields ManualControlCommand::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void ManualControlCommand::setData(const DataFields& data)
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

void ManualControlCommand::emitNotifications()
{
            //if (data.Throttle != oldData.Throttle)
            emit ThrottleChanged(data.Throttle);
        //if (data.Roll != oldData.Roll)
            emit RollChanged(data.Roll);
        //if (data.Pitch != oldData.Pitch)
            emit PitchChanged(data.Pitch);
        //if (data.Yaw != oldData.Yaw)
            emit YawChanged(data.Yaw);
        //if (data.Collective != oldData.Collective)
            emit CollectiveChanged(data.Collective);
        //if (data.Thrust != oldData.Thrust)
            emit ThrustChanged(data.Thrust);
        //if (data.Channel[0] != oldData.Channel[0])
            emit Channel_0Changed(data.Channel[0]);
        //if (data.Channel[1] != oldData.Channel[1])
            emit Channel_1Changed(data.Channel[1]);
        //if (data.Channel[2] != oldData.Channel[2])
            emit Channel_2Changed(data.Channel[2]);
        //if (data.Channel[3] != oldData.Channel[3])
            emit Channel_3Changed(data.Channel[3]);
        //if (data.Channel[4] != oldData.Channel[4])
            emit Channel_4Changed(data.Channel[4]);
        //if (data.Channel[5] != oldData.Channel[5])
            emit Channel_5Changed(data.Channel[5]);
        //if (data.Channel[6] != oldData.Channel[6])
            emit Channel_6Changed(data.Channel[6]);
        //if (data.Channel[7] != oldData.Channel[7])
            emit Channel_7Changed(data.Channel[7]);
        //if (data.Channel[8] != oldData.Channel[8])
            emit Channel_8Changed(data.Channel[8]);
        //if (data.Connected != oldData.Connected)
            emit ConnectedChanged(data.Connected);
        //if (data.FlightModeSwitchPosition != oldData.FlightModeSwitchPosition)
            emit FlightModeSwitchPositionChanged(data.FlightModeSwitchPosition);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *ManualControlCommand::clone(quint32 instID)
{
    ManualControlCommand *obj = new ManualControlCommand();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *ManualControlCommand::dirtyClone()
{
    ManualControlCommand *obj = new ManualControlCommand();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
ManualControlCommand *ManualControlCommand::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<ManualControlCommand *>(objMngr->getObject(ManualControlCommand::OBJID, instID));
}

float ManualControlCommand::getThrottle() const
{
   QMutexLocker locker(mutex);
   return data.Throttle;
}
void ManualControlCommand::setThrottle(float value)
{
   mutex->lock();
   bool changed = data.Throttle != value;
   data.Throttle = value;
   mutex->unlock();
   if (changed) emit ThrottleChanged(value);
}

float ManualControlCommand::getRoll() const
{
   QMutexLocker locker(mutex);
   return data.Roll;
}
void ManualControlCommand::setRoll(float value)
{
   mutex->lock();
   bool changed = data.Roll != value;
   data.Roll = value;
   mutex->unlock();
   if (changed) emit RollChanged(value);
}

float ManualControlCommand::getPitch() const
{
   QMutexLocker locker(mutex);
   return data.Pitch;
}
void ManualControlCommand::setPitch(float value)
{
   mutex->lock();
   bool changed = data.Pitch != value;
   data.Pitch = value;
   mutex->unlock();
   if (changed) emit PitchChanged(value);
}

float ManualControlCommand::getYaw() const
{
   QMutexLocker locker(mutex);
   return data.Yaw;
}
void ManualControlCommand::setYaw(float value)
{
   mutex->lock();
   bool changed = data.Yaw != value;
   data.Yaw = value;
   mutex->unlock();
   if (changed) emit YawChanged(value);
}

float ManualControlCommand::getCollective() const
{
   QMutexLocker locker(mutex);
   return data.Collective;
}
void ManualControlCommand::setCollective(float value)
{
   mutex->lock();
   bool changed = data.Collective != value;
   data.Collective = value;
   mutex->unlock();
   if (changed) emit CollectiveChanged(value);
}

float ManualControlCommand::getThrust() const
{
   QMutexLocker locker(mutex);
   return data.Thrust;
}
void ManualControlCommand::setThrust(float value)
{
   mutex->lock();
   bool changed = data.Thrust != value;
   data.Thrust = value;
   mutex->unlock();
   if (changed) emit ThrustChanged(value);
}

quint16 ManualControlCommand::getChannel(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Channel[index];
}
void ManualControlCommand::setChannel(quint32 index, quint16 value)
{
   mutex->lock();
   bool changed = data.Channel[index] != value;
   data.Channel[index] = value;
   mutex->unlock();
   if (changed) emit ChannelChanged(index,value);
}

quint16 ManualControlCommand::getChannel_0() const
{
   QMutexLocker locker(mutex);
   return data.Channel[0];
}
void ManualControlCommand::setChannel_0(quint16 value)
{
   mutex->lock();
   bool changed = data.Channel[0] != value;
   data.Channel[0] = value;
   mutex->unlock();
   if (changed) emit Channel_0Changed(value);
}

quint16 ManualControlCommand::getChannel_1() const
{
   QMutexLocker locker(mutex);
   return data.Channel[1];
}
void ManualControlCommand::setChannel_1(quint16 value)
{
   mutex->lock();
   bool changed = data.Channel[1] != value;
   data.Channel[1] = value;
   mutex->unlock();
   if (changed) emit Channel_1Changed(value);
}

quint16 ManualControlCommand::getChannel_2() const
{
   QMutexLocker locker(mutex);
   return data.Channel[2];
}
void ManualControlCommand::setChannel_2(quint16 value)
{
   mutex->lock();
   bool changed = data.Channel[2] != value;
   data.Channel[2] = value;
   mutex->unlock();
   if (changed) emit Channel_2Changed(value);
}

quint16 ManualControlCommand::getChannel_3() const
{
   QMutexLocker locker(mutex);
   return data.Channel[3];
}
void ManualControlCommand::setChannel_3(quint16 value)
{
   mutex->lock();
   bool changed = data.Channel[3] != value;
   data.Channel[3] = value;
   mutex->unlock();
   if (changed) emit Channel_3Changed(value);
}

quint16 ManualControlCommand::getChannel_4() const
{
   QMutexLocker locker(mutex);
   return data.Channel[4];
}
void ManualControlCommand::setChannel_4(quint16 value)
{
   mutex->lock();
   bool changed = data.Channel[4] != value;
   data.Channel[4] = value;
   mutex->unlock();
   if (changed) emit Channel_4Changed(value);
}

quint16 ManualControlCommand::getChannel_5() const
{
   QMutexLocker locker(mutex);
   return data.Channel[5];
}
void ManualControlCommand::setChannel_5(quint16 value)
{
   mutex->lock();
   bool changed = data.Channel[5] != value;
   data.Channel[5] = value;
   mutex->unlock();
   if (changed) emit Channel_5Changed(value);
}

quint16 ManualControlCommand::getChannel_6() const
{
   QMutexLocker locker(mutex);
   return data.Channel[6];
}
void ManualControlCommand::setChannel_6(quint16 value)
{
   mutex->lock();
   bool changed = data.Channel[6] != value;
   data.Channel[6] = value;
   mutex->unlock();
   if (changed) emit Channel_6Changed(value);
}

quint16 ManualControlCommand::getChannel_7() const
{
   QMutexLocker locker(mutex);
   return data.Channel[7];
}
void ManualControlCommand::setChannel_7(quint16 value)
{
   mutex->lock();
   bool changed = data.Channel[7] != value;
   data.Channel[7] = value;
   mutex->unlock();
   if (changed) emit Channel_7Changed(value);
}

quint16 ManualControlCommand::getChannel_8() const
{
   QMutexLocker locker(mutex);
   return data.Channel[8];
}
void ManualControlCommand::setChannel_8(quint16 value)
{
   mutex->lock();
   bool changed = data.Channel[8] != value;
   data.Channel[8] = value;
   mutex->unlock();
   if (changed) emit Channel_8Changed(value);
}

quint8 ManualControlCommand::getConnected() const
{
   QMutexLocker locker(mutex);
   return data.Connected;
}
void ManualControlCommand::setConnected(quint8 value)
{
   mutex->lock();
   bool changed = data.Connected != value;
   data.Connected = value;
   mutex->unlock();
   if (changed) emit ConnectedChanged(value);
}

quint8 ManualControlCommand::getFlightModeSwitchPosition() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeSwitchPosition;
}
void ManualControlCommand::setFlightModeSwitchPosition(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeSwitchPosition != value;
   data.FlightModeSwitchPosition = value;
   mutex->unlock();
   if (changed) emit FlightModeSwitchPositionChanged(value);
}


