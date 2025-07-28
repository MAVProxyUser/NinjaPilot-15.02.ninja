/**
 ******************************************************************************
 *
 * @file       faultsettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: faultsettings.xml.
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

#include "faultsettings.h"
#include "uavobjectfield.h"

const QString FaultSettings::NAME = QString("FaultSettings");
const QString FaultSettings::DESCRIPTION = QString("Allows testers to simulate various fault scenarios.");
const QString FaultSettings::CATEGORY = QString("System");

/**
 * Constructor
 */
FaultSettings::FaultSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList ActivateFaultElemNames;
    ActivateFaultElemNames.append("0");
    QStringList ActivateFaultEnumOptions;
    ActivateFaultEnumOptions.append("NoFault");
    ActivateFaultEnumOptions.append("ModuleInitAssert");
    ActivateFaultEnumOptions.append("InitOutOfMemory");
    ActivateFaultEnumOptions.append("InitBusError");
    ActivateFaultEnumOptions.append("RunawayTask");
    ActivateFaultEnumOptions.append("TaskOutOfMemory");
    fields.append( new UAVObjectField(QString("ActivateFault"), tr(""), QString("fault"), UAVObjectField::ENUM, ActivateFaultElemNames, ActivateFaultEnumOptions, QString("")));

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
UAVObject::Metadata FaultSettings::getDefaultMetadata()
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
void FaultSettings::setDefaultFieldValues()
{
    data.ActivateFault = 0;

}

/**
 * Get the object data fields
 */
FaultSettings::DataFields FaultSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void FaultSettings::setData(const DataFields& data)
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

void FaultSettings::emitNotifications()
{
            //if (data.ActivateFault != oldData.ActivateFault)
            emit ActivateFaultChanged(data.ActivateFault);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *FaultSettings::clone(quint32 instID)
{
    FaultSettings *obj = new FaultSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *FaultSettings::dirtyClone()
{
    FaultSettings *obj = new FaultSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
FaultSettings *FaultSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<FaultSettings *>(objMngr->getObject(FaultSettings::OBJID, instID));
}

quint8 FaultSettings::getActivateFault() const
{
   QMutexLocker locker(mutex);
   return data.ActivateFault;
}
void FaultSettings::setActivateFault(quint8 value)
{
   mutex->lock();
   bool changed = data.ActivateFault != value;
   data.ActivateFault = value;
   mutex->unlock();
   if (changed) emit ActivateFaultChanged(value);
}


