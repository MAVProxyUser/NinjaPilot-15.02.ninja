/**
 ******************************************************************************
 *
 * @file       flightbatterystate.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: flightbatterystate.xml.
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

#include "flightbatterystate.h"
#include "uavobjectfield.h"

const QString FlightBatteryState::NAME = QString("FlightBatteryState");
const QString FlightBatteryState::DESCRIPTION = QString("Battery status information.");
const QString FlightBatteryState::CATEGORY = QString("Sensors");

/**
 * Constructor
 */
FlightBatteryState::FlightBatteryState(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList VoltageElemNames;
    VoltageElemNames.append("0");
    fields.append( new UAVObjectField(QString("Voltage"), tr(""), QString("V"), UAVObjectField::FLOAT32, VoltageElemNames, QStringList(), QString("")));
    QStringList CurrentElemNames;
    CurrentElemNames.append("0");
    fields.append( new UAVObjectField(QString("Current"), tr(""), QString("A"), UAVObjectField::FLOAT32, CurrentElemNames, QStringList(), QString("")));
    QStringList BoardSupplyVoltageElemNames;
    BoardSupplyVoltageElemNames.append("0");
    fields.append( new UAVObjectField(QString("BoardSupplyVoltage"), tr(""), QString("V"), UAVObjectField::FLOAT32, BoardSupplyVoltageElemNames, QStringList(), QString("")));
    QStringList PeakCurrentElemNames;
    PeakCurrentElemNames.append("0");
    fields.append( new UAVObjectField(QString("PeakCurrent"), tr(""), QString("A"), UAVObjectField::FLOAT32, PeakCurrentElemNames, QStringList(), QString("")));
    QStringList AvgCurrentElemNames;
    AvgCurrentElemNames.append("0");
    fields.append( new UAVObjectField(QString("AvgCurrent"), tr(""), QString("A"), UAVObjectField::FLOAT32, AvgCurrentElemNames, QStringList(), QString("")));
    QStringList ConsumedEnergyElemNames;
    ConsumedEnergyElemNames.append("0");
    fields.append( new UAVObjectField(QString("ConsumedEnergy"), tr(""), QString("mAh"), UAVObjectField::FLOAT32, ConsumedEnergyElemNames, QStringList(), QString("")));
    QStringList EstimatedFlightTimeElemNames;
    EstimatedFlightTimeElemNames.append("0");
    fields.append( new UAVObjectField(QString("EstimatedFlightTime"), tr(""), QString("sec"), UAVObjectField::FLOAT32, EstimatedFlightTimeElemNames, QStringList(), QString("")));
    QStringList NbCellsElemNames;
    NbCellsElemNames.append("0");
    fields.append( new UAVObjectField(QString("NbCells"), tr(""), QString(""), UAVObjectField::UINT8, NbCellsElemNames, QStringList(), QString("")));
    QStringList NbCellsAutodetectedElemNames;
    NbCellsAutodetectedElemNames.append("0");
    QStringList NbCellsAutodetectedEnumOptions;
    NbCellsAutodetectedEnumOptions.append("False");
    NbCellsAutodetectedEnumOptions.append("True");
    fields.append( new UAVObjectField(QString("NbCellsAutodetected"), tr(""), QString("bool"), UAVObjectField::ENUM, NbCellsAutodetectedElemNames, NbCellsAutodetectedEnumOptions, QString("")));

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
UAVObject::Metadata FlightBatteryState::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READONLY << UAVOBJ_GCS_ACCESS_SHIFT |
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
void FlightBatteryState::setDefaultFieldValues()
{
    data.Voltage = 0;
    data.Current = 0;
    data.BoardSupplyVoltage = 0;
    data.PeakCurrent = 0;
    data.AvgCurrent = 0;
    data.ConsumedEnergy = 0;
    data.EstimatedFlightTime = 0;
    data.NbCells = 3;
    data.NbCellsAutodetected = 0;

}

/**
 * Get the object data fields
 */
FlightBatteryState::DataFields FlightBatteryState::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void FlightBatteryState::setData(const DataFields& data)
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

void FlightBatteryState::emitNotifications()
{
            //if (data.Voltage != oldData.Voltage)
            emit VoltageChanged(data.Voltage);
        //if (data.Current != oldData.Current)
            emit CurrentChanged(data.Current);
        //if (data.BoardSupplyVoltage != oldData.BoardSupplyVoltage)
            emit BoardSupplyVoltageChanged(data.BoardSupplyVoltage);
        //if (data.PeakCurrent != oldData.PeakCurrent)
            emit PeakCurrentChanged(data.PeakCurrent);
        //if (data.AvgCurrent != oldData.AvgCurrent)
            emit AvgCurrentChanged(data.AvgCurrent);
        //if (data.ConsumedEnergy != oldData.ConsumedEnergy)
            emit ConsumedEnergyChanged(data.ConsumedEnergy);
        //if (data.EstimatedFlightTime != oldData.EstimatedFlightTime)
            emit EstimatedFlightTimeChanged(data.EstimatedFlightTime);
        //if (data.NbCells != oldData.NbCells)
            emit NbCellsChanged(data.NbCells);
        //if (data.NbCellsAutodetected != oldData.NbCellsAutodetected)
            emit NbCellsAutodetectedChanged(data.NbCellsAutodetected);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *FlightBatteryState::clone(quint32 instID)
{
    FlightBatteryState *obj = new FlightBatteryState();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *FlightBatteryState::dirtyClone()
{
    FlightBatteryState *obj = new FlightBatteryState();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
FlightBatteryState *FlightBatteryState::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<FlightBatteryState *>(objMngr->getObject(FlightBatteryState::OBJID, instID));
}

float FlightBatteryState::getVoltage() const
{
   QMutexLocker locker(mutex);
   return data.Voltage;
}
void FlightBatteryState::setVoltage(float value)
{
   mutex->lock();
   bool changed = data.Voltage != value;
   data.Voltage = value;
   mutex->unlock();
   if (changed) emit VoltageChanged(value);
}

float FlightBatteryState::getCurrent() const
{
   QMutexLocker locker(mutex);
   return data.Current;
}
void FlightBatteryState::setCurrent(float value)
{
   mutex->lock();
   bool changed = data.Current != value;
   data.Current = value;
   mutex->unlock();
   if (changed) emit CurrentChanged(value);
}

float FlightBatteryState::getBoardSupplyVoltage() const
{
   QMutexLocker locker(mutex);
   return data.BoardSupplyVoltage;
}
void FlightBatteryState::setBoardSupplyVoltage(float value)
{
   mutex->lock();
   bool changed = data.BoardSupplyVoltage != value;
   data.BoardSupplyVoltage = value;
   mutex->unlock();
   if (changed) emit BoardSupplyVoltageChanged(value);
}

float FlightBatteryState::getPeakCurrent() const
{
   QMutexLocker locker(mutex);
   return data.PeakCurrent;
}
void FlightBatteryState::setPeakCurrent(float value)
{
   mutex->lock();
   bool changed = data.PeakCurrent != value;
   data.PeakCurrent = value;
   mutex->unlock();
   if (changed) emit PeakCurrentChanged(value);
}

float FlightBatteryState::getAvgCurrent() const
{
   QMutexLocker locker(mutex);
   return data.AvgCurrent;
}
void FlightBatteryState::setAvgCurrent(float value)
{
   mutex->lock();
   bool changed = data.AvgCurrent != value;
   data.AvgCurrent = value;
   mutex->unlock();
   if (changed) emit AvgCurrentChanged(value);
}

float FlightBatteryState::getConsumedEnergy() const
{
   QMutexLocker locker(mutex);
   return data.ConsumedEnergy;
}
void FlightBatteryState::setConsumedEnergy(float value)
{
   mutex->lock();
   bool changed = data.ConsumedEnergy != value;
   data.ConsumedEnergy = value;
   mutex->unlock();
   if (changed) emit ConsumedEnergyChanged(value);
}

float FlightBatteryState::getEstimatedFlightTime() const
{
   QMutexLocker locker(mutex);
   return data.EstimatedFlightTime;
}
void FlightBatteryState::setEstimatedFlightTime(float value)
{
   mutex->lock();
   bool changed = data.EstimatedFlightTime != value;
   data.EstimatedFlightTime = value;
   mutex->unlock();
   if (changed) emit EstimatedFlightTimeChanged(value);
}

quint8 FlightBatteryState::getNbCells() const
{
   QMutexLocker locker(mutex);
   return data.NbCells;
}
void FlightBatteryState::setNbCells(quint8 value)
{
   mutex->lock();
   bool changed = data.NbCells != value;
   data.NbCells = value;
   mutex->unlock();
   if (changed) emit NbCellsChanged(value);
}

quint8 FlightBatteryState::getNbCellsAutodetected() const
{
   QMutexLocker locker(mutex);
   return data.NbCellsAutodetected;
}
void FlightBatteryState::setNbCellsAutodetected(quint8 value)
{
   mutex->lock();
   bool changed = data.NbCellsAutodetected != value;
   data.NbCellsAutodetected = value;
   mutex->unlock();
   if (changed) emit NbCellsAutodetectedChanged(value);
}


