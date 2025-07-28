/**
 ******************************************************************************
 *
 * @file       vtolselftuningstats.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: vtolselftuningstats.xml.
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

#include "vtolselftuningstats.h"
#include "uavobjectfield.h"

const QString VtolSelfTuningStats::NAME = QString("VtolSelfTuningStats");
const QString VtolSelfTuningStats::DESCRIPTION = QString("Automatically calculated adjustments to parameters used into vtol auto flight modes. Can come from @ref PathFollower ");
const QString VtolSelfTuningStats::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
VtolSelfTuningStats::VtolSelfTuningStats(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList NeutralThrustOffsetElemNames;
    NeutralThrustOffsetElemNames.append("0");
    fields.append( new UAVObjectField(QString("NeutralThrustOffset"), tr(""), QString(""), UAVObjectField::FLOAT32, NeutralThrustOffsetElemNames, QStringList(), QString("")));
    QStringList NeutralThrustCorrectionElemNames;
    NeutralThrustCorrectionElemNames.append("0");
    fields.append( new UAVObjectField(QString("NeutralThrustCorrection"), tr(""), QString(""), UAVObjectField::FLOAT32, NeutralThrustCorrectionElemNames, QStringList(), QString("")));
    QStringList NeutralThrustAccumulatorElemNames;
    NeutralThrustAccumulatorElemNames.append("0");
    fields.append( new UAVObjectField(QString("NeutralThrustAccumulator"), tr(""), QString(""), UAVObjectField::FLOAT32, NeutralThrustAccumulatorElemNames, QStringList(), QString("")));
    QStringList NeutralThrustRangeElemNames;
    NeutralThrustRangeElemNames.append("0");
    fields.append( new UAVObjectField(QString("NeutralThrustRange"), tr(""), QString(""), UAVObjectField::FLOAT32, NeutralThrustRangeElemNames, QStringList(), QString("")));

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
UAVObject::Metadata VtolSelfTuningStats::getDefaultMetadata()
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
void VtolSelfTuningStats::setDefaultFieldValues()
{
    data.NeutralThrustOffset = 0;
    data.NeutralThrustCorrection = 0;
    data.NeutralThrustAccumulator = 0;
    data.NeutralThrustRange = 0;

}

/**
 * Get the object data fields
 */
VtolSelfTuningStats::DataFields VtolSelfTuningStats::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void VtolSelfTuningStats::setData(const DataFields& data)
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

void VtolSelfTuningStats::emitNotifications()
{
            //if (data.NeutralThrustOffset != oldData.NeutralThrustOffset)
            emit NeutralThrustOffsetChanged(data.NeutralThrustOffset);
        //if (data.NeutralThrustCorrection != oldData.NeutralThrustCorrection)
            emit NeutralThrustCorrectionChanged(data.NeutralThrustCorrection);
        //if (data.NeutralThrustAccumulator != oldData.NeutralThrustAccumulator)
            emit NeutralThrustAccumulatorChanged(data.NeutralThrustAccumulator);
        //if (data.NeutralThrustRange != oldData.NeutralThrustRange)
            emit NeutralThrustRangeChanged(data.NeutralThrustRange);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *VtolSelfTuningStats::clone(quint32 instID)
{
    VtolSelfTuningStats *obj = new VtolSelfTuningStats();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *VtolSelfTuningStats::dirtyClone()
{
    VtolSelfTuningStats *obj = new VtolSelfTuningStats();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
VtolSelfTuningStats *VtolSelfTuningStats::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<VtolSelfTuningStats *>(objMngr->getObject(VtolSelfTuningStats::OBJID, instID));
}

float VtolSelfTuningStats::getNeutralThrustOffset() const
{
   QMutexLocker locker(mutex);
   return data.NeutralThrustOffset;
}
void VtolSelfTuningStats::setNeutralThrustOffset(float value)
{
   mutex->lock();
   bool changed = data.NeutralThrustOffset != value;
   data.NeutralThrustOffset = value;
   mutex->unlock();
   if (changed) emit NeutralThrustOffsetChanged(value);
}

float VtolSelfTuningStats::getNeutralThrustCorrection() const
{
   QMutexLocker locker(mutex);
   return data.NeutralThrustCorrection;
}
void VtolSelfTuningStats::setNeutralThrustCorrection(float value)
{
   mutex->lock();
   bool changed = data.NeutralThrustCorrection != value;
   data.NeutralThrustCorrection = value;
   mutex->unlock();
   if (changed) emit NeutralThrustCorrectionChanged(value);
}

float VtolSelfTuningStats::getNeutralThrustAccumulator() const
{
   QMutexLocker locker(mutex);
   return data.NeutralThrustAccumulator;
}
void VtolSelfTuningStats::setNeutralThrustAccumulator(float value)
{
   mutex->lock();
   bool changed = data.NeutralThrustAccumulator != value;
   data.NeutralThrustAccumulator = value;
   mutex->unlock();
   if (changed) emit NeutralThrustAccumulatorChanged(value);
}

float VtolSelfTuningStats::getNeutralThrustRange() const
{
   QMutexLocker locker(mutex);
   return data.NeutralThrustRange;
}
void VtolSelfTuningStats::setNeutralThrustRange(float value)
{
   mutex->lock();
   bool changed = data.NeutralThrustRange != value;
   data.NeutralThrustRange = value;
   mutex->unlock();
   if (changed) emit NeutralThrustRangeChanged(value);
}


