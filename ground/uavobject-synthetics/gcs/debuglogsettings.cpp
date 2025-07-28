/**
 ******************************************************************************
 *
 * @file       debuglogsettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: debuglogsettings.xml.
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

#include "debuglogsettings.h"
#include "uavobjectfield.h"

const QString DebugLogSettings::NAME = QString("DebugLogSettings");
const QString DebugLogSettings::DESCRIPTION = QString("Configure On Board Logging Facilities");
const QString DebugLogSettings::CATEGORY = QString("System");

/**
 * Constructor
 */
DebugLogSettings::DebugLogSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList LoggingEnabledElemNames;
    LoggingEnabledElemNames.append("0");
    QStringList LoggingEnabledEnumOptions;
    LoggingEnabledEnumOptions.append("Disabled");
    LoggingEnabledEnumOptions.append("OnlyWhenArmed");
    LoggingEnabledEnumOptions.append("Always");
    fields.append( new UAVObjectField(QString("LoggingEnabled"), tr("If set to OnlyWhenArmed logs will only be saved when craft is armed. Disabled turns logging off, and Always will always log."), QString(""), UAVObjectField::ENUM, LoggingEnabledElemNames, LoggingEnabledEnumOptions, QString("")));

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
UAVObject::Metadata DebugLogSettings::getDefaultMetadata()
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
void DebugLogSettings::setDefaultFieldValues()
{
    data.LoggingEnabled = 0;

}

/**
 * Get the object data fields
 */
DebugLogSettings::DataFields DebugLogSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void DebugLogSettings::setData(const DataFields& data)
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

void DebugLogSettings::emitNotifications()
{
            //if (data.LoggingEnabled != oldData.LoggingEnabled)
            emit LoggingEnabledChanged(data.LoggingEnabled);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *DebugLogSettings::clone(quint32 instID)
{
    DebugLogSettings *obj = new DebugLogSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *DebugLogSettings::dirtyClone()
{
    DebugLogSettings *obj = new DebugLogSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
DebugLogSettings *DebugLogSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<DebugLogSettings *>(objMngr->getObject(DebugLogSettings::OBJID, instID));
}

quint8 DebugLogSettings::getLoggingEnabled() const
{
   QMutexLocker locker(mutex);
   return data.LoggingEnabled;
}
void DebugLogSettings::setLoggingEnabled(quint8 value)
{
   mutex->lock();
   bool changed = data.LoggingEnabled != value;
   data.LoggingEnabled = value;
   mutex->unlock();
   if (changed) emit LoggingEnabledChanged(value);
}


