/**
 ******************************************************************************
 *
 * @file       flightbatterysettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: flightbatterysettings.xml.
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

#include "flightbatterysettings.h"
#include "uavobjectfield.h"

const QString FlightBatterySettings::NAME = QString("FlightBatterySettings");
const QString FlightBatterySettings::DESCRIPTION = QString("Flight Battery configuration.");
const QString FlightBatterySettings::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
FlightBatterySettings::FlightBatterySettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList CapacityElemNames;
    CapacityElemNames.append("0");
    fields.append( new UAVObjectField(QString("Capacity"), tr(""), QString("mAh"), UAVObjectField::UINT32, CapacityElemNames, QStringList(), QString("")));
    QStringList CellVoltageThresholdsElemNames;
    CellVoltageThresholdsElemNames.append("Warning");
    CellVoltageThresholdsElemNames.append("Alarm");
    fields.append( new UAVObjectField(QString("CellVoltageThresholds"), tr(""), QString("V"), UAVObjectField::FLOAT32, CellVoltageThresholdsElemNames, QStringList(), QString("")));
    QStringList SensorCalibrationsElemNames;
    SensorCalibrationsElemNames.append("VoltageFactor");
    SensorCalibrationsElemNames.append("CurrentFactor");
    SensorCalibrationsElemNames.append("VoltageZero");
    SensorCalibrationsElemNames.append("CurrentZero");
    fields.append( new UAVObjectField(QString("SensorCalibrations"), tr(""), QString(""), UAVObjectField::FLOAT32, SensorCalibrationsElemNames, QStringList(), QString("")));
    QStringList TypeElemNames;
    TypeElemNames.append("0");
    QStringList TypeEnumOptions;
    TypeEnumOptions.append("LiPo");
    TypeEnumOptions.append("A123");
    TypeEnumOptions.append("LiCo");
    TypeEnumOptions.append("LiFeSO4");
    TypeEnumOptions.append("None");
    fields.append( new UAVObjectField(QString("Type"), tr(""), QString(""), UAVObjectField::ENUM, TypeElemNames, TypeEnumOptions, QString("")));
    QStringList NbCellsElemNames;
    NbCellsElemNames.append("0");
    fields.append( new UAVObjectField(QString("NbCells"), tr(""), QString(""), UAVObjectField::UINT8, NbCellsElemNames, QStringList(), QString("")));

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
UAVObject::Metadata FlightBatterySettings::getDefaultMetadata()
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
void FlightBatterySettings::setDefaultFieldValues()
{
    data.Capacity = 2200;
    data.CellVoltageThresholds[0] = 3.4;
    data.CellVoltageThresholds[1] = 3.1;
    data.SensorCalibrations[0] = 1;
    data.SensorCalibrations[1] = 1;
    data.SensorCalibrations[2] = 0;
    data.SensorCalibrations[3] = 0;
    data.Type = 0;
    data.NbCells = 0;

}

/**
 * Get the object data fields
 */
FlightBatterySettings::DataFields FlightBatterySettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void FlightBatterySettings::setData(const DataFields& data)
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

void FlightBatterySettings::emitNotifications()
{
            //if (data.Capacity != oldData.Capacity)
            emit CapacityChanged(data.Capacity);
        //if (data.CellVoltageThresholds[0] != oldData.CellVoltageThresholds[0])
            emit CellVoltageThresholds_WarningChanged(data.CellVoltageThresholds[0]);
        //if (data.CellVoltageThresholds[1] != oldData.CellVoltageThresholds[1])
            emit CellVoltageThresholds_AlarmChanged(data.CellVoltageThresholds[1]);
        //if (data.SensorCalibrations[0] != oldData.SensorCalibrations[0])
            emit SensorCalibrations_VoltageFactorChanged(data.SensorCalibrations[0]);
        //if (data.SensorCalibrations[1] != oldData.SensorCalibrations[1])
            emit SensorCalibrations_CurrentFactorChanged(data.SensorCalibrations[1]);
        //if (data.SensorCalibrations[2] != oldData.SensorCalibrations[2])
            emit SensorCalibrations_VoltageZeroChanged(data.SensorCalibrations[2]);
        //if (data.SensorCalibrations[3] != oldData.SensorCalibrations[3])
            emit SensorCalibrations_CurrentZeroChanged(data.SensorCalibrations[3]);
        //if (data.Type != oldData.Type)
            emit TypeChanged(data.Type);
        //if (data.NbCells != oldData.NbCells)
            emit NbCellsChanged(data.NbCells);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *FlightBatterySettings::clone(quint32 instID)
{
    FlightBatterySettings *obj = new FlightBatterySettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *FlightBatterySettings::dirtyClone()
{
    FlightBatterySettings *obj = new FlightBatterySettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
FlightBatterySettings *FlightBatterySettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<FlightBatterySettings *>(objMngr->getObject(FlightBatterySettings::OBJID, instID));
}

quint32 FlightBatterySettings::getCapacity() const
{
   QMutexLocker locker(mutex);
   return data.Capacity;
}
void FlightBatterySettings::setCapacity(quint32 value)
{
   mutex->lock();
   bool changed = data.Capacity != value;
   data.Capacity = value;
   mutex->unlock();
   if (changed) emit CapacityChanged(value);
}

float FlightBatterySettings::getCellVoltageThresholds(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.CellVoltageThresholds[index];
}
void FlightBatterySettings::setCellVoltageThresholds(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.CellVoltageThresholds[index] != value;
   data.CellVoltageThresholds[index] = value;
   mutex->unlock();
   if (changed) emit CellVoltageThresholdsChanged(index,value);
}

float FlightBatterySettings::getCellVoltageThresholds_Warning() const
{
   QMutexLocker locker(mutex);
   return data.CellVoltageThresholds[0];
}
void FlightBatterySettings::setCellVoltageThresholds_Warning(float value)
{
   mutex->lock();
   bool changed = data.CellVoltageThresholds[0] != value;
   data.CellVoltageThresholds[0] = value;
   mutex->unlock();
   if (changed) emit CellVoltageThresholds_WarningChanged(value);
}

float FlightBatterySettings::getCellVoltageThresholds_Alarm() const
{
   QMutexLocker locker(mutex);
   return data.CellVoltageThresholds[1];
}
void FlightBatterySettings::setCellVoltageThresholds_Alarm(float value)
{
   mutex->lock();
   bool changed = data.CellVoltageThresholds[1] != value;
   data.CellVoltageThresholds[1] = value;
   mutex->unlock();
   if (changed) emit CellVoltageThresholds_AlarmChanged(value);
}

float FlightBatterySettings::getSensorCalibrations(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.SensorCalibrations[index];
}
void FlightBatterySettings::setSensorCalibrations(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.SensorCalibrations[index] != value;
   data.SensorCalibrations[index] = value;
   mutex->unlock();
   if (changed) emit SensorCalibrationsChanged(index,value);
}

float FlightBatterySettings::getSensorCalibrations_VoltageFactor() const
{
   QMutexLocker locker(mutex);
   return data.SensorCalibrations[0];
}
void FlightBatterySettings::setSensorCalibrations_VoltageFactor(float value)
{
   mutex->lock();
   bool changed = data.SensorCalibrations[0] != value;
   data.SensorCalibrations[0] = value;
   mutex->unlock();
   if (changed) emit SensorCalibrations_VoltageFactorChanged(value);
}

float FlightBatterySettings::getSensorCalibrations_CurrentFactor() const
{
   QMutexLocker locker(mutex);
   return data.SensorCalibrations[1];
}
void FlightBatterySettings::setSensorCalibrations_CurrentFactor(float value)
{
   mutex->lock();
   bool changed = data.SensorCalibrations[1] != value;
   data.SensorCalibrations[1] = value;
   mutex->unlock();
   if (changed) emit SensorCalibrations_CurrentFactorChanged(value);
}

float FlightBatterySettings::getSensorCalibrations_VoltageZero() const
{
   QMutexLocker locker(mutex);
   return data.SensorCalibrations[2];
}
void FlightBatterySettings::setSensorCalibrations_VoltageZero(float value)
{
   mutex->lock();
   bool changed = data.SensorCalibrations[2] != value;
   data.SensorCalibrations[2] = value;
   mutex->unlock();
   if (changed) emit SensorCalibrations_VoltageZeroChanged(value);
}

float FlightBatterySettings::getSensorCalibrations_CurrentZero() const
{
   QMutexLocker locker(mutex);
   return data.SensorCalibrations[3];
}
void FlightBatterySettings::setSensorCalibrations_CurrentZero(float value)
{
   mutex->lock();
   bool changed = data.SensorCalibrations[3] != value;
   data.SensorCalibrations[3] = value;
   mutex->unlock();
   if (changed) emit SensorCalibrations_CurrentZeroChanged(value);
}

quint8 FlightBatterySettings::getType() const
{
   QMutexLocker locker(mutex);
   return data.Type;
}
void FlightBatterySettings::setType(quint8 value)
{
   mutex->lock();
   bool changed = data.Type != value;
   data.Type = value;
   mutex->unlock();
   if (changed) emit TypeChanged(value);
}

quint8 FlightBatterySettings::getNbCells() const
{
   QMutexLocker locker(mutex);
   return data.NbCells;
}
void FlightBatterySettings::setNbCells(quint8 value)
{
   mutex->lock();
   bool changed = data.NbCells != value;
   data.NbCells = value;
   mutex->unlock();
   if (changed) emit NbCellsChanged(value);
}


