/**
 ******************************************************************************
 *
 * @file       objectpersistence.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: objectpersistence.xml.
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

#include "objectpersistence.h"
#include "uavobjectfield.h"

const QString ObjectPersistence::NAME = QString("ObjectPersistence");
const QString ObjectPersistence::DESCRIPTION = QString("Used by gcs to handle object persistence to flash memory");
const QString ObjectPersistence::CATEGORY = QString("System");

/**
 * Constructor
 */
ObjectPersistence::ObjectPersistence(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList ObjectIDElemNames;
    ObjectIDElemNames.append("0");
    fields.append( new UAVObjectField(QString("ObjectID"), tr(""), QString(""), UAVObjectField::UINT32, ObjectIDElemNames, QStringList(), QString("")));
    QStringList InstanceIDElemNames;
    InstanceIDElemNames.append("0");
    fields.append( new UAVObjectField(QString("InstanceID"), tr(""), QString(""), UAVObjectField::UINT32, InstanceIDElemNames, QStringList(), QString("")));
    QStringList OperationElemNames;
    OperationElemNames.append("0");
    QStringList OperationEnumOptions;
    OperationEnumOptions.append("NOP");
    OperationEnumOptions.append("Load");
    OperationEnumOptions.append("Save");
    OperationEnumOptions.append("Delete");
    OperationEnumOptions.append("FullErase");
    OperationEnumOptions.append("Completed");
    OperationEnumOptions.append("Error");
    fields.append( new UAVObjectField(QString("Operation"), tr(""), QString(""), UAVObjectField::ENUM, OperationElemNames, OperationEnumOptions, QString("")));
    QStringList SelectionElemNames;
    SelectionElemNames.append("0");
    QStringList SelectionEnumOptions;
    SelectionEnumOptions.append("SingleObject");
    SelectionEnumOptions.append("AllSettings");
    SelectionEnumOptions.append("AllMetaObjects");
    SelectionEnumOptions.append("AllObjects");
    fields.append( new UAVObjectField(QString("Selection"), tr(""), QString(""), UAVObjectField::ENUM, SelectionElemNames, SelectionEnumOptions, QString("")));

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
UAVObject::Metadata ObjectPersistence::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        1 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        1 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
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
void ObjectPersistence::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
ObjectPersistence::DataFields ObjectPersistence::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void ObjectPersistence::setData(const DataFields& data)
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

void ObjectPersistence::emitNotifications()
{
            //if (data.ObjectID != oldData.ObjectID)
            emit ObjectIDChanged(data.ObjectID);
        //if (data.InstanceID != oldData.InstanceID)
            emit InstanceIDChanged(data.InstanceID);
        //if (data.Operation != oldData.Operation)
            emit OperationChanged(data.Operation);
        //if (data.Selection != oldData.Selection)
            emit SelectionChanged(data.Selection);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *ObjectPersistence::clone(quint32 instID)
{
    ObjectPersistence *obj = new ObjectPersistence();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *ObjectPersistence::dirtyClone()
{
    ObjectPersistence *obj = new ObjectPersistence();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
ObjectPersistence *ObjectPersistence::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<ObjectPersistence *>(objMngr->getObject(ObjectPersistence::OBJID, instID));
}

quint32 ObjectPersistence::getObjectID() const
{
   QMutexLocker locker(mutex);
   return data.ObjectID;
}
void ObjectPersistence::setObjectID(quint32 value)
{
   mutex->lock();
   bool changed = data.ObjectID != value;
   data.ObjectID = value;
   mutex->unlock();
   if (changed) emit ObjectIDChanged(value);
}

quint32 ObjectPersistence::getInstanceID() const
{
   QMutexLocker locker(mutex);
   return data.InstanceID;
}
void ObjectPersistence::setInstanceID(quint32 value)
{
   mutex->lock();
   bool changed = data.InstanceID != value;
   data.InstanceID = value;
   mutex->unlock();
   if (changed) emit InstanceIDChanged(value);
}

quint8 ObjectPersistence::getOperation() const
{
   QMutexLocker locker(mutex);
   return data.Operation;
}
void ObjectPersistence::setOperation(quint8 value)
{
   mutex->lock();
   bool changed = data.Operation != value;
   data.Operation = value;
   mutex->unlock();
   if (changed) emit OperationChanged(value);
}

quint8 ObjectPersistence::getSelection() const
{
   QMutexLocker locker(mutex);
   return data.Selection;
}
void ObjectPersistence::setSelection(quint8 value)
{
   mutex->lock();
   bool changed = data.Selection != value;
   data.Selection = value;
   mutex->unlock();
   if (changed) emit SelectionChanged(value);
}


