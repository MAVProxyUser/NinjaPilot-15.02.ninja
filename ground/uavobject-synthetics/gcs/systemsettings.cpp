/**
 ******************************************************************************
 *
 * @file       systemsettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: systemsettings.xml.
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

#include "systemsettings.h"
#include "uavobjectfield.h"

const QString SystemSettings::NAME = QString("SystemSettings");
const QString SystemSettings::DESCRIPTION = QString("Select airframe type.  Currently used by @ref ActuatorModule to choose mixing from @ref ActuatorDesired to @ref ActuatorCommand");
const QString SystemSettings::CATEGORY = QString("System");

/**
 * Constructor
 */
SystemSettings::SystemSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList GUIConfigDataElemNames;
    GUIConfigDataElemNames.append("0");
    GUIConfigDataElemNames.append("1");
    GUIConfigDataElemNames.append("2");
    GUIConfigDataElemNames.append("3");
    fields.append( new UAVObjectField(QString("GUIConfigData"), tr(""), QString("bits"), UAVObjectField::UINT32, GUIConfigDataElemNames, QStringList(), QString("")));
    QStringList AirSpeedMaxElemNames;
    AirSpeedMaxElemNames.append("0");
    fields.append( new UAVObjectField(QString("AirSpeedMax"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, AirSpeedMaxElemNames, QStringList(), QString("")));
    QStringList AirSpeedMinElemNames;
    AirSpeedMinElemNames.append("0");
    fields.append( new UAVObjectField(QString("AirSpeedMin"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, AirSpeedMinElemNames, QStringList(), QString("")));
    QStringList AirframeTypeElemNames;
    AirframeTypeElemNames.append("0");
    QStringList AirframeTypeEnumOptions;
    AirframeTypeEnumOptions.append("FixedWing");
    AirframeTypeEnumOptions.append("FixedWingElevon");
    AirframeTypeEnumOptions.append("FixedWingVtail");
    AirframeTypeEnumOptions.append("VTOL");
    AirframeTypeEnumOptions.append("HeliCP");
    AirframeTypeEnumOptions.append("QuadX");
    AirframeTypeEnumOptions.append("QuadP");
    AirframeTypeEnumOptions.append("Hexa");
    AirframeTypeEnumOptions.append("Octo");
    AirframeTypeEnumOptions.append("Custom");
    AirframeTypeEnumOptions.append("HexaX");
    AirframeTypeEnumOptions.append("HexaH");
    AirframeTypeEnumOptions.append("OctoV");
    AirframeTypeEnumOptions.append("OctoCoaxP");
    AirframeTypeEnumOptions.append("OctoCoaxX");
    AirframeTypeEnumOptions.append("OctoX");
    AirframeTypeEnumOptions.append("HexaCoax");
    AirframeTypeEnumOptions.append("Tri");
    AirframeTypeEnumOptions.append("GroundVehicleCar");
    AirframeTypeEnumOptions.append("GroundVehicleDifferential");
    AirframeTypeEnumOptions.append("GroundVehicleMotorcycle");
    fields.append( new UAVObjectField(QString("AirframeType"), tr(""), QString(""), UAVObjectField::ENUM, AirframeTypeElemNames, AirframeTypeEnumOptions, QString("")));
    QStringList VehicleNameElemNames;
    VehicleNameElemNames.append("0");
    VehicleNameElemNames.append("1");
    VehicleNameElemNames.append("2");
    VehicleNameElemNames.append("3");
    VehicleNameElemNames.append("4");
    VehicleNameElemNames.append("5");
    VehicleNameElemNames.append("6");
    VehicleNameElemNames.append("7");
    VehicleNameElemNames.append("8");
    VehicleNameElemNames.append("9");
    VehicleNameElemNames.append("10");
    VehicleNameElemNames.append("11");
    VehicleNameElemNames.append("12");
    VehicleNameElemNames.append("13");
    VehicleNameElemNames.append("14");
    VehicleNameElemNames.append("15");
    VehicleNameElemNames.append("16");
    VehicleNameElemNames.append("17");
    VehicleNameElemNames.append("18");
    VehicleNameElemNames.append("19");
    fields.append( new UAVObjectField(QString("VehicleName"), tr(""), QString("char"), UAVObjectField::UINT8, VehicleNameElemNames, QStringList(), QString("")));
    QStringList ThrustControlElemNames;
    ThrustControlElemNames.append("0");
    QStringList ThrustControlEnumOptions;
    ThrustControlEnumOptions.append("Throttle");
    ThrustControlEnumOptions.append("Collective");
    ThrustControlEnumOptions.append("None");
    fields.append( new UAVObjectField(QString("ThrustControl"), tr(""), QString(""), UAVObjectField::ENUM, ThrustControlElemNames, ThrustControlEnumOptions, QString("")));

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
UAVObject::Metadata SystemSettings::getDefaultMetadata()
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
void SystemSettings::setDefaultFieldValues()
{
    data.GUIConfigData[0] = 0;
    data.GUIConfigData[1] = 0;
    data.GUIConfigData[2] = 0;
    data.GUIConfigData[3] = 0;
    data.AirSpeedMax = 30;
    data.AirSpeedMin = 10;
    data.AirframeType = 5;
    data.VehicleName[0] = 0;
    data.VehicleName[1] = 0;
    data.VehicleName[2] = 0;
    data.VehicleName[3] = 0;
    data.VehicleName[4] = 0;
    data.VehicleName[5] = 0;
    data.VehicleName[6] = 0;
    data.VehicleName[7] = 0;
    data.VehicleName[8] = 0;
    data.VehicleName[9] = 0;
    data.VehicleName[10] = 0;
    data.VehicleName[11] = 0;
    data.VehicleName[12] = 0;
    data.VehicleName[13] = 0;
    data.VehicleName[14] = 0;
    data.VehicleName[15] = 0;
    data.VehicleName[16] = 0;
    data.VehicleName[17] = 0;
    data.VehicleName[18] = 0;
    data.VehicleName[19] = 0;
    data.ThrustControl = 0;

}

/**
 * Get the object data fields
 */
SystemSettings::DataFields SystemSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void SystemSettings::setData(const DataFields& data)
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

void SystemSettings::emitNotifications()
{
            //if (data.GUIConfigData[0] != oldData.GUIConfigData[0])
            emit GUIConfigData_0Changed(data.GUIConfigData[0]);
        //if (data.GUIConfigData[1] != oldData.GUIConfigData[1])
            emit GUIConfigData_1Changed(data.GUIConfigData[1]);
        //if (data.GUIConfigData[2] != oldData.GUIConfigData[2])
            emit GUIConfigData_2Changed(data.GUIConfigData[2]);
        //if (data.GUIConfigData[3] != oldData.GUIConfigData[3])
            emit GUIConfigData_3Changed(data.GUIConfigData[3]);
        //if (data.AirSpeedMax != oldData.AirSpeedMax)
            emit AirSpeedMaxChanged(data.AirSpeedMax);
        //if (data.AirSpeedMin != oldData.AirSpeedMin)
            emit AirSpeedMinChanged(data.AirSpeedMin);
        //if (data.AirframeType != oldData.AirframeType)
            emit AirframeTypeChanged(data.AirframeType);
        //if (data.VehicleName[0] != oldData.VehicleName[0])
            emit VehicleName_0Changed(data.VehicleName[0]);
        //if (data.VehicleName[1] != oldData.VehicleName[1])
            emit VehicleName_1Changed(data.VehicleName[1]);
        //if (data.VehicleName[2] != oldData.VehicleName[2])
            emit VehicleName_2Changed(data.VehicleName[2]);
        //if (data.VehicleName[3] != oldData.VehicleName[3])
            emit VehicleName_3Changed(data.VehicleName[3]);
        //if (data.VehicleName[4] != oldData.VehicleName[4])
            emit VehicleName_4Changed(data.VehicleName[4]);
        //if (data.VehicleName[5] != oldData.VehicleName[5])
            emit VehicleName_5Changed(data.VehicleName[5]);
        //if (data.VehicleName[6] != oldData.VehicleName[6])
            emit VehicleName_6Changed(data.VehicleName[6]);
        //if (data.VehicleName[7] != oldData.VehicleName[7])
            emit VehicleName_7Changed(data.VehicleName[7]);
        //if (data.VehicleName[8] != oldData.VehicleName[8])
            emit VehicleName_8Changed(data.VehicleName[8]);
        //if (data.VehicleName[9] != oldData.VehicleName[9])
            emit VehicleName_9Changed(data.VehicleName[9]);
        //if (data.VehicleName[10] != oldData.VehicleName[10])
            emit VehicleName_10Changed(data.VehicleName[10]);
        //if (data.VehicleName[11] != oldData.VehicleName[11])
            emit VehicleName_11Changed(data.VehicleName[11]);
        //if (data.VehicleName[12] != oldData.VehicleName[12])
            emit VehicleName_12Changed(data.VehicleName[12]);
        //if (data.VehicleName[13] != oldData.VehicleName[13])
            emit VehicleName_13Changed(data.VehicleName[13]);
        //if (data.VehicleName[14] != oldData.VehicleName[14])
            emit VehicleName_14Changed(data.VehicleName[14]);
        //if (data.VehicleName[15] != oldData.VehicleName[15])
            emit VehicleName_15Changed(data.VehicleName[15]);
        //if (data.VehicleName[16] != oldData.VehicleName[16])
            emit VehicleName_16Changed(data.VehicleName[16]);
        //if (data.VehicleName[17] != oldData.VehicleName[17])
            emit VehicleName_17Changed(data.VehicleName[17]);
        //if (data.VehicleName[18] != oldData.VehicleName[18])
            emit VehicleName_18Changed(data.VehicleName[18]);
        //if (data.VehicleName[19] != oldData.VehicleName[19])
            emit VehicleName_19Changed(data.VehicleName[19]);
        //if (data.ThrustControl != oldData.ThrustControl)
            emit ThrustControlChanged(data.ThrustControl);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *SystemSettings::clone(quint32 instID)
{
    SystemSettings *obj = new SystemSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *SystemSettings::dirtyClone()
{
    SystemSettings *obj = new SystemSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
SystemSettings *SystemSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<SystemSettings *>(objMngr->getObject(SystemSettings::OBJID, instID));
}

quint32 SystemSettings::getGUIConfigData(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.GUIConfigData[index];
}
void SystemSettings::setGUIConfigData(quint32 index, quint32 value)
{
   mutex->lock();
   bool changed = data.GUIConfigData[index] != value;
   data.GUIConfigData[index] = value;
   mutex->unlock();
   if (changed) emit GUIConfigDataChanged(index,value);
}

quint32 SystemSettings::getGUIConfigData_0() const
{
   QMutexLocker locker(mutex);
   return data.GUIConfigData[0];
}
void SystemSettings::setGUIConfigData_0(quint32 value)
{
   mutex->lock();
   bool changed = data.GUIConfigData[0] != value;
   data.GUIConfigData[0] = value;
   mutex->unlock();
   if (changed) emit GUIConfigData_0Changed(value);
}

quint32 SystemSettings::getGUIConfigData_1() const
{
   QMutexLocker locker(mutex);
   return data.GUIConfigData[1];
}
void SystemSettings::setGUIConfigData_1(quint32 value)
{
   mutex->lock();
   bool changed = data.GUIConfigData[1] != value;
   data.GUIConfigData[1] = value;
   mutex->unlock();
   if (changed) emit GUIConfigData_1Changed(value);
}

quint32 SystemSettings::getGUIConfigData_2() const
{
   QMutexLocker locker(mutex);
   return data.GUIConfigData[2];
}
void SystemSettings::setGUIConfigData_2(quint32 value)
{
   mutex->lock();
   bool changed = data.GUIConfigData[2] != value;
   data.GUIConfigData[2] = value;
   mutex->unlock();
   if (changed) emit GUIConfigData_2Changed(value);
}

quint32 SystemSettings::getGUIConfigData_3() const
{
   QMutexLocker locker(mutex);
   return data.GUIConfigData[3];
}
void SystemSettings::setGUIConfigData_3(quint32 value)
{
   mutex->lock();
   bool changed = data.GUIConfigData[3] != value;
   data.GUIConfigData[3] = value;
   mutex->unlock();
   if (changed) emit GUIConfigData_3Changed(value);
}

float SystemSettings::getAirSpeedMax() const
{
   QMutexLocker locker(mutex);
   return data.AirSpeedMax;
}
void SystemSettings::setAirSpeedMax(float value)
{
   mutex->lock();
   bool changed = data.AirSpeedMax != value;
   data.AirSpeedMax = value;
   mutex->unlock();
   if (changed) emit AirSpeedMaxChanged(value);
}

float SystemSettings::getAirSpeedMin() const
{
   QMutexLocker locker(mutex);
   return data.AirSpeedMin;
}
void SystemSettings::setAirSpeedMin(float value)
{
   mutex->lock();
   bool changed = data.AirSpeedMin != value;
   data.AirSpeedMin = value;
   mutex->unlock();
   if (changed) emit AirSpeedMinChanged(value);
}

quint8 SystemSettings::getAirframeType() const
{
   QMutexLocker locker(mutex);
   return data.AirframeType;
}
void SystemSettings::setAirframeType(quint8 value)
{
   mutex->lock();
   bool changed = data.AirframeType != value;
   data.AirframeType = value;
   mutex->unlock();
   if (changed) emit AirframeTypeChanged(value);
}

quint8 SystemSettings::getVehicleName(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[index];
}
void SystemSettings::setVehicleName(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[index] != value;
   data.VehicleName[index] = value;
   mutex->unlock();
   if (changed) emit VehicleNameChanged(index,value);
}

quint8 SystemSettings::getVehicleName_0() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[0];
}
void SystemSettings::setVehicleName_0(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[0] != value;
   data.VehicleName[0] = value;
   mutex->unlock();
   if (changed) emit VehicleName_0Changed(value);
}

quint8 SystemSettings::getVehicleName_1() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[1];
}
void SystemSettings::setVehicleName_1(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[1] != value;
   data.VehicleName[1] = value;
   mutex->unlock();
   if (changed) emit VehicleName_1Changed(value);
}

quint8 SystemSettings::getVehicleName_2() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[2];
}
void SystemSettings::setVehicleName_2(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[2] != value;
   data.VehicleName[2] = value;
   mutex->unlock();
   if (changed) emit VehicleName_2Changed(value);
}

quint8 SystemSettings::getVehicleName_3() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[3];
}
void SystemSettings::setVehicleName_3(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[3] != value;
   data.VehicleName[3] = value;
   mutex->unlock();
   if (changed) emit VehicleName_3Changed(value);
}

quint8 SystemSettings::getVehicleName_4() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[4];
}
void SystemSettings::setVehicleName_4(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[4] != value;
   data.VehicleName[4] = value;
   mutex->unlock();
   if (changed) emit VehicleName_4Changed(value);
}

quint8 SystemSettings::getVehicleName_5() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[5];
}
void SystemSettings::setVehicleName_5(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[5] != value;
   data.VehicleName[5] = value;
   mutex->unlock();
   if (changed) emit VehicleName_5Changed(value);
}

quint8 SystemSettings::getVehicleName_6() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[6];
}
void SystemSettings::setVehicleName_6(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[6] != value;
   data.VehicleName[6] = value;
   mutex->unlock();
   if (changed) emit VehicleName_6Changed(value);
}

quint8 SystemSettings::getVehicleName_7() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[7];
}
void SystemSettings::setVehicleName_7(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[7] != value;
   data.VehicleName[7] = value;
   mutex->unlock();
   if (changed) emit VehicleName_7Changed(value);
}

quint8 SystemSettings::getVehicleName_8() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[8];
}
void SystemSettings::setVehicleName_8(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[8] != value;
   data.VehicleName[8] = value;
   mutex->unlock();
   if (changed) emit VehicleName_8Changed(value);
}

quint8 SystemSettings::getVehicleName_9() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[9];
}
void SystemSettings::setVehicleName_9(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[9] != value;
   data.VehicleName[9] = value;
   mutex->unlock();
   if (changed) emit VehicleName_9Changed(value);
}

quint8 SystemSettings::getVehicleName_10() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[10];
}
void SystemSettings::setVehicleName_10(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[10] != value;
   data.VehicleName[10] = value;
   mutex->unlock();
   if (changed) emit VehicleName_10Changed(value);
}

quint8 SystemSettings::getVehicleName_11() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[11];
}
void SystemSettings::setVehicleName_11(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[11] != value;
   data.VehicleName[11] = value;
   mutex->unlock();
   if (changed) emit VehicleName_11Changed(value);
}

quint8 SystemSettings::getVehicleName_12() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[12];
}
void SystemSettings::setVehicleName_12(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[12] != value;
   data.VehicleName[12] = value;
   mutex->unlock();
   if (changed) emit VehicleName_12Changed(value);
}

quint8 SystemSettings::getVehicleName_13() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[13];
}
void SystemSettings::setVehicleName_13(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[13] != value;
   data.VehicleName[13] = value;
   mutex->unlock();
   if (changed) emit VehicleName_13Changed(value);
}

quint8 SystemSettings::getVehicleName_14() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[14];
}
void SystemSettings::setVehicleName_14(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[14] != value;
   data.VehicleName[14] = value;
   mutex->unlock();
   if (changed) emit VehicleName_14Changed(value);
}

quint8 SystemSettings::getVehicleName_15() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[15];
}
void SystemSettings::setVehicleName_15(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[15] != value;
   data.VehicleName[15] = value;
   mutex->unlock();
   if (changed) emit VehicleName_15Changed(value);
}

quint8 SystemSettings::getVehicleName_16() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[16];
}
void SystemSettings::setVehicleName_16(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[16] != value;
   data.VehicleName[16] = value;
   mutex->unlock();
   if (changed) emit VehicleName_16Changed(value);
}

quint8 SystemSettings::getVehicleName_17() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[17];
}
void SystemSettings::setVehicleName_17(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[17] != value;
   data.VehicleName[17] = value;
   mutex->unlock();
   if (changed) emit VehicleName_17Changed(value);
}

quint8 SystemSettings::getVehicleName_18() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[18];
}
void SystemSettings::setVehicleName_18(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[18] != value;
   data.VehicleName[18] = value;
   mutex->unlock();
   if (changed) emit VehicleName_18Changed(value);
}

quint8 SystemSettings::getVehicleName_19() const
{
   QMutexLocker locker(mutex);
   return data.VehicleName[19];
}
void SystemSettings::setVehicleName_19(quint8 value)
{
   mutex->lock();
   bool changed = data.VehicleName[19] != value;
   data.VehicleName[19] = value;
   mutex->unlock();
   if (changed) emit VehicleName_19Changed(value);
}

quint8 SystemSettings::getThrustControl() const
{
   QMutexLocker locker(mutex);
   return data.ThrustControl;
}
void SystemSettings::setThrustControl(quint8 value)
{
   mutex->lock();
   bool changed = data.ThrustControl != value;
   data.ThrustControl = value;
   mutex->unlock();
   if (changed) emit ThrustControlChanged(value);
}


