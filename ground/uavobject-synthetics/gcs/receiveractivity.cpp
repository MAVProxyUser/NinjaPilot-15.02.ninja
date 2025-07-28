/**
 ******************************************************************************
 *
 * @file       receiveractivity.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: receiveractivity.xml.
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

#include "receiveractivity.h"
#include "uavobjectfield.h"

const QString ReceiverActivity::NAME = QString("ReceiverActivity");
const QString ReceiverActivity::DESCRIPTION = QString("Monitors which receiver channels have been active within the last second.");
const QString ReceiverActivity::CATEGORY = QString("System");

/**
 * Constructor
 */
ReceiverActivity::ReceiverActivity(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList ActiveGroupElemNames;
    ActiveGroupElemNames.append("0");
    QStringList ActiveGroupEnumOptions;
    ActiveGroupEnumOptions.append("PWM");
    ActiveGroupEnumOptions.append("PPM");
    ActiveGroupEnumOptions.append("DSM (MainPort)");
    ActiveGroupEnumOptions.append("DSM (FlexiPort)");
    ActiveGroupEnumOptions.append("S.Bus");
    ActiveGroupEnumOptions.append("GCS");
    ActiveGroupEnumOptions.append("OPLink");
    ActiveGroupEnumOptions.append("None");
    fields.append( new UAVObjectField(QString("ActiveGroup"), tr(""), QString("Channel Group"), UAVObjectField::ENUM, ActiveGroupElemNames, ActiveGroupEnumOptions, QString("")));
    QStringList ActiveChannelElemNames;
    ActiveChannelElemNames.append("0");
    fields.append( new UAVObjectField(QString("ActiveChannel"), tr(""), QString("channel"), UAVObjectField::UINT8, ActiveChannelElemNames, QStringList(), QString("")));

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
UAVObject::Metadata ReceiverActivity::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READONLY << UAVOBJ_GCS_ACCESS_SHIFT |
        0 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        0 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
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
void ReceiverActivity::setDefaultFieldValues()
{
    data.ActiveGroup = 7;
    data.ActiveChannel = 255;

}

/**
 * Get the object data fields
 */
ReceiverActivity::DataFields ReceiverActivity::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void ReceiverActivity::setData(const DataFields& data)
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

void ReceiverActivity::emitNotifications()
{
            //if (data.ActiveGroup != oldData.ActiveGroup)
            emit ActiveGroupChanged(data.ActiveGroup);
        //if (data.ActiveChannel != oldData.ActiveChannel)
            emit ActiveChannelChanged(data.ActiveChannel);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *ReceiverActivity::clone(quint32 instID)
{
    ReceiverActivity *obj = new ReceiverActivity();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *ReceiverActivity::dirtyClone()
{
    ReceiverActivity *obj = new ReceiverActivity();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
ReceiverActivity *ReceiverActivity::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<ReceiverActivity *>(objMngr->getObject(ReceiverActivity::OBJID, instID));
}

quint8 ReceiverActivity::getActiveGroup() const
{
   QMutexLocker locker(mutex);
   return data.ActiveGroup;
}
void ReceiverActivity::setActiveGroup(quint8 value)
{
   mutex->lock();
   bool changed = data.ActiveGroup != value;
   data.ActiveGroup = value;
   mutex->unlock();
   if (changed) emit ActiveGroupChanged(value);
}

quint8 ReceiverActivity::getActiveChannel() const
{
   QMutexLocker locker(mutex);
   return data.ActiveChannel;
}
void ReceiverActivity::setActiveChannel(quint8 value)
{
   mutex->lock();
   bool changed = data.ActiveChannel != value;
   data.ActiveChannel = value;
   mutex->unlock();
   if (changed) emit ActiveChannelChanged(value);
}


