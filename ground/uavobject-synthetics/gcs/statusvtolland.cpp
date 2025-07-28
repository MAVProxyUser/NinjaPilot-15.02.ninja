/**
 ******************************************************************************
 *
 * @file       statusvtolland.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: statusvtolland.xml.
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

#include "statusvtolland.h"
#include "uavobjectfield.h"

const QString StatusVtolLand::NAME = QString("StatusVtolLand");
const QString StatusVtolLand::DESCRIPTION = QString("Status of a Vtol landing sequence");
const QString StatusVtolLand::CATEGORY = QString("Navigation");

/**
 * Constructor
 */
StatusVtolLand::StatusVtolLand(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList AltitudeAtStateElemNames;
    AltitudeAtStateElemNames.append("0");
    AltitudeAtStateElemNames.append("1");
    AltitudeAtStateElemNames.append("2");
    AltitudeAtStateElemNames.append("3");
    AltitudeAtStateElemNames.append("4");
    AltitudeAtStateElemNames.append("5");
    AltitudeAtStateElemNames.append("6");
    AltitudeAtStateElemNames.append("7");
    AltitudeAtStateElemNames.append("8");
    AltitudeAtStateElemNames.append("9");
    fields.append( new UAVObjectField(QString("AltitudeAtState"), tr(""), QString("m"), UAVObjectField::FLOAT32, AltitudeAtStateElemNames, QStringList(), QString("")));
    QStringList targetDescentRateElemNames;
    targetDescentRateElemNames.append("0");
    fields.append( new UAVObjectField(QString("targetDescentRate"), tr(""), QString("m"), UAVObjectField::FLOAT32, targetDescentRateElemNames, QStringList(), QString("")));
    QStringList averageDescentRateElemNames;
    averageDescentRateElemNames.append("0");
    fields.append( new UAVObjectField(QString("averageDescentRate"), tr(""), QString("m"), UAVObjectField::FLOAT32, averageDescentRateElemNames, QStringList(), QString("")));
    QStringList averageDescentThrustElemNames;
    averageDescentThrustElemNames.append("0");
    fields.append( new UAVObjectField(QString("averageDescentThrust"), tr(""), QString("m"), UAVObjectField::FLOAT32, averageDescentThrustElemNames, QStringList(), QString("")));
    QStringList calculatedNeutralThrustElemNames;
    calculatedNeutralThrustElemNames.append("0");
    fields.append( new UAVObjectField(QString("calculatedNeutralThrust"), tr(""), QString("m"), UAVObjectField::FLOAT32, calculatedNeutralThrustElemNames, QStringList(), QString("")));
    QStringList WtgForGroundEffectElemNames;
    WtgForGroundEffectElemNames.append("BounceVelocity");
    WtgForGroundEffectElemNames.append("BounceAccel");
    fields.append( new UAVObjectField(QString("WtgForGroundEffect"), tr(""), QString(""), UAVObjectField::FLOAT32, WtgForGroundEffectElemNames, QStringList(), QString("")));
    QStringList StateElemNames;
    StateElemNames.append("0");
    QStringList StateEnumOptions;
    StateEnumOptions.append("Inactive");
    StateEnumOptions.append("InitAltHold");
    StateEnumOptions.append("WtgForDescentRate");
    StateEnumOptions.append("AtDescentRate");
    StateEnumOptions.append("WtgForGroundEffect");
    StateEnumOptions.append("GroundEffect");
    StateEnumOptions.append("ThrustDown");
    StateEnumOptions.append("ThrustOff");
    StateEnumOptions.append("Disarmed");
    StateEnumOptions.append("Abort");
    fields.append( new UAVObjectField(QString("State"), tr(""), QString(""), UAVObjectField::ENUM, StateElemNames, StateEnumOptions, QString("")));
    QStringList StateExitReasonElemNames;
    StateExitReasonElemNames.append("0");
    StateExitReasonElemNames.append("1");
    StateExitReasonElemNames.append("2");
    StateExitReasonElemNames.append("3");
    StateExitReasonElemNames.append("4");
    StateExitReasonElemNames.append("5");
    StateExitReasonElemNames.append("6");
    StateExitReasonElemNames.append("7");
    StateExitReasonElemNames.append("8");
    StateExitReasonElemNames.append("9");
    QStringList StateExitReasonEnumOptions;
    StateExitReasonEnumOptions.append("None");
    StateExitReasonEnumOptions.append("DescentRateOk");
    StateExitReasonEnumOptions.append("OnGround");
    StateExitReasonEnumOptions.append("BounceVelocity");
    StateExitReasonEnumOptions.append("BounceAccel");
    StateExitReasonEnumOptions.append("LowDescentRate");
    StateExitReasonEnumOptions.append("ZeroThrust");
    StateExitReasonEnumOptions.append("PositionError");
    StateExitReasonEnumOptions.append("Timeout");
    fields.append( new UAVObjectField(QString("StateExitReason"), tr(""), QString(""), UAVObjectField::ENUM, StateExitReasonElemNames, StateExitReasonEnumOptions, QString("")));
    QStringList AltitudeStateElemNames;
    AltitudeStateElemNames.append("0");
    QStringList AltitudeStateEnumOptions;
    AltitudeStateEnumOptions.append("High");
    AltitudeStateEnumOptions.append("Low");
    fields.append( new UAVObjectField(QString("AltitudeState"), tr(""), QString(""), UAVObjectField::ENUM, AltitudeStateElemNames, AltitudeStateEnumOptions, QString("")));

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
UAVObject::Metadata StatusVtolLand::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        0 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        0 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_ONCHANGE << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_LOGGING_UPDATE_MODE_SHIFT;
    metadata.flightTelemetryUpdatePeriod = 100;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void StatusVtolLand::setDefaultFieldValues()
{
    data.WtgForGroundEffect[0] = 0;
    data.WtgForGroundEffect[1] = 0;

}

/**
 * Get the object data fields
 */
StatusVtolLand::DataFields StatusVtolLand::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void StatusVtolLand::setData(const DataFields& data)
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

void StatusVtolLand::emitNotifications()
{
            //if (data.AltitudeAtState[0] != oldData.AltitudeAtState[0])
            emit AltitudeAtState_0Changed(data.AltitudeAtState[0]);
        //if (data.AltitudeAtState[1] != oldData.AltitudeAtState[1])
            emit AltitudeAtState_1Changed(data.AltitudeAtState[1]);
        //if (data.AltitudeAtState[2] != oldData.AltitudeAtState[2])
            emit AltitudeAtState_2Changed(data.AltitudeAtState[2]);
        //if (data.AltitudeAtState[3] != oldData.AltitudeAtState[3])
            emit AltitudeAtState_3Changed(data.AltitudeAtState[3]);
        //if (data.AltitudeAtState[4] != oldData.AltitudeAtState[4])
            emit AltitudeAtState_4Changed(data.AltitudeAtState[4]);
        //if (data.AltitudeAtState[5] != oldData.AltitudeAtState[5])
            emit AltitudeAtState_5Changed(data.AltitudeAtState[5]);
        //if (data.AltitudeAtState[6] != oldData.AltitudeAtState[6])
            emit AltitudeAtState_6Changed(data.AltitudeAtState[6]);
        //if (data.AltitudeAtState[7] != oldData.AltitudeAtState[7])
            emit AltitudeAtState_7Changed(data.AltitudeAtState[7]);
        //if (data.AltitudeAtState[8] != oldData.AltitudeAtState[8])
            emit AltitudeAtState_8Changed(data.AltitudeAtState[8]);
        //if (data.AltitudeAtState[9] != oldData.AltitudeAtState[9])
            emit AltitudeAtState_9Changed(data.AltitudeAtState[9]);
        //if (data.targetDescentRate != oldData.targetDescentRate)
            emit targetDescentRateChanged(data.targetDescentRate);
        //if (data.averageDescentRate != oldData.averageDescentRate)
            emit averageDescentRateChanged(data.averageDescentRate);
        //if (data.averageDescentThrust != oldData.averageDescentThrust)
            emit averageDescentThrustChanged(data.averageDescentThrust);
        //if (data.calculatedNeutralThrust != oldData.calculatedNeutralThrust)
            emit calculatedNeutralThrustChanged(data.calculatedNeutralThrust);
        //if (data.WtgForGroundEffect[0] != oldData.WtgForGroundEffect[0])
            emit WtgForGroundEffect_BounceVelocityChanged(data.WtgForGroundEffect[0]);
        //if (data.WtgForGroundEffect[1] != oldData.WtgForGroundEffect[1])
            emit WtgForGroundEffect_BounceAccelChanged(data.WtgForGroundEffect[1]);
        //if (data.State != oldData.State)
            emit StateChanged(data.State);
        //if (data.StateExitReason[0] != oldData.StateExitReason[0])
            emit StateExitReason_0Changed(data.StateExitReason[0]);
        //if (data.StateExitReason[1] != oldData.StateExitReason[1])
            emit StateExitReason_1Changed(data.StateExitReason[1]);
        //if (data.StateExitReason[2] != oldData.StateExitReason[2])
            emit StateExitReason_2Changed(data.StateExitReason[2]);
        //if (data.StateExitReason[3] != oldData.StateExitReason[3])
            emit StateExitReason_3Changed(data.StateExitReason[3]);
        //if (data.StateExitReason[4] != oldData.StateExitReason[4])
            emit StateExitReason_4Changed(data.StateExitReason[4]);
        //if (data.StateExitReason[5] != oldData.StateExitReason[5])
            emit StateExitReason_5Changed(data.StateExitReason[5]);
        //if (data.StateExitReason[6] != oldData.StateExitReason[6])
            emit StateExitReason_6Changed(data.StateExitReason[6]);
        //if (data.StateExitReason[7] != oldData.StateExitReason[7])
            emit StateExitReason_7Changed(data.StateExitReason[7]);
        //if (data.StateExitReason[8] != oldData.StateExitReason[8])
            emit StateExitReason_8Changed(data.StateExitReason[8]);
        //if (data.StateExitReason[9] != oldData.StateExitReason[9])
            emit StateExitReason_9Changed(data.StateExitReason[9]);
        //if (data.AltitudeState != oldData.AltitudeState)
            emit AltitudeStateChanged(data.AltitudeState);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *StatusVtolLand::clone(quint32 instID)
{
    StatusVtolLand *obj = new StatusVtolLand();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *StatusVtolLand::dirtyClone()
{
    StatusVtolLand *obj = new StatusVtolLand();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
StatusVtolLand *StatusVtolLand::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<StatusVtolLand *>(objMngr->getObject(StatusVtolLand::OBJID, instID));
}

float StatusVtolLand::getAltitudeAtState(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.AltitudeAtState[index];
}
void StatusVtolLand::setAltitudeAtState(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.AltitudeAtState[index] != value;
   data.AltitudeAtState[index] = value;
   mutex->unlock();
   if (changed) emit AltitudeAtStateChanged(index,value);
}

float StatusVtolLand::getAltitudeAtState_0() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeAtState[0];
}
void StatusVtolLand::setAltitudeAtState_0(float value)
{
   mutex->lock();
   bool changed = data.AltitudeAtState[0] != value;
   data.AltitudeAtState[0] = value;
   mutex->unlock();
   if (changed) emit AltitudeAtState_0Changed(value);
}

float StatusVtolLand::getAltitudeAtState_1() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeAtState[1];
}
void StatusVtolLand::setAltitudeAtState_1(float value)
{
   mutex->lock();
   bool changed = data.AltitudeAtState[1] != value;
   data.AltitudeAtState[1] = value;
   mutex->unlock();
   if (changed) emit AltitudeAtState_1Changed(value);
}

float StatusVtolLand::getAltitudeAtState_2() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeAtState[2];
}
void StatusVtolLand::setAltitudeAtState_2(float value)
{
   mutex->lock();
   bool changed = data.AltitudeAtState[2] != value;
   data.AltitudeAtState[2] = value;
   mutex->unlock();
   if (changed) emit AltitudeAtState_2Changed(value);
}

float StatusVtolLand::getAltitudeAtState_3() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeAtState[3];
}
void StatusVtolLand::setAltitudeAtState_3(float value)
{
   mutex->lock();
   bool changed = data.AltitudeAtState[3] != value;
   data.AltitudeAtState[3] = value;
   mutex->unlock();
   if (changed) emit AltitudeAtState_3Changed(value);
}

float StatusVtolLand::getAltitudeAtState_4() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeAtState[4];
}
void StatusVtolLand::setAltitudeAtState_4(float value)
{
   mutex->lock();
   bool changed = data.AltitudeAtState[4] != value;
   data.AltitudeAtState[4] = value;
   mutex->unlock();
   if (changed) emit AltitudeAtState_4Changed(value);
}

float StatusVtolLand::getAltitudeAtState_5() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeAtState[5];
}
void StatusVtolLand::setAltitudeAtState_5(float value)
{
   mutex->lock();
   bool changed = data.AltitudeAtState[5] != value;
   data.AltitudeAtState[5] = value;
   mutex->unlock();
   if (changed) emit AltitudeAtState_5Changed(value);
}

float StatusVtolLand::getAltitudeAtState_6() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeAtState[6];
}
void StatusVtolLand::setAltitudeAtState_6(float value)
{
   mutex->lock();
   bool changed = data.AltitudeAtState[6] != value;
   data.AltitudeAtState[6] = value;
   mutex->unlock();
   if (changed) emit AltitudeAtState_6Changed(value);
}

float StatusVtolLand::getAltitudeAtState_7() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeAtState[7];
}
void StatusVtolLand::setAltitudeAtState_7(float value)
{
   mutex->lock();
   bool changed = data.AltitudeAtState[7] != value;
   data.AltitudeAtState[7] = value;
   mutex->unlock();
   if (changed) emit AltitudeAtState_7Changed(value);
}

float StatusVtolLand::getAltitudeAtState_8() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeAtState[8];
}
void StatusVtolLand::setAltitudeAtState_8(float value)
{
   mutex->lock();
   bool changed = data.AltitudeAtState[8] != value;
   data.AltitudeAtState[8] = value;
   mutex->unlock();
   if (changed) emit AltitudeAtState_8Changed(value);
}

float StatusVtolLand::getAltitudeAtState_9() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeAtState[9];
}
void StatusVtolLand::setAltitudeAtState_9(float value)
{
   mutex->lock();
   bool changed = data.AltitudeAtState[9] != value;
   data.AltitudeAtState[9] = value;
   mutex->unlock();
   if (changed) emit AltitudeAtState_9Changed(value);
}

float StatusVtolLand::gettargetDescentRate() const
{
   QMutexLocker locker(mutex);
   return data.targetDescentRate;
}
void StatusVtolLand::settargetDescentRate(float value)
{
   mutex->lock();
   bool changed = data.targetDescentRate != value;
   data.targetDescentRate = value;
   mutex->unlock();
   if (changed) emit targetDescentRateChanged(value);
}

float StatusVtolLand::getaverageDescentRate() const
{
   QMutexLocker locker(mutex);
   return data.averageDescentRate;
}
void StatusVtolLand::setaverageDescentRate(float value)
{
   mutex->lock();
   bool changed = data.averageDescentRate != value;
   data.averageDescentRate = value;
   mutex->unlock();
   if (changed) emit averageDescentRateChanged(value);
}

float StatusVtolLand::getaverageDescentThrust() const
{
   QMutexLocker locker(mutex);
   return data.averageDescentThrust;
}
void StatusVtolLand::setaverageDescentThrust(float value)
{
   mutex->lock();
   bool changed = data.averageDescentThrust != value;
   data.averageDescentThrust = value;
   mutex->unlock();
   if (changed) emit averageDescentThrustChanged(value);
}

float StatusVtolLand::getcalculatedNeutralThrust() const
{
   QMutexLocker locker(mutex);
   return data.calculatedNeutralThrust;
}
void StatusVtolLand::setcalculatedNeutralThrust(float value)
{
   mutex->lock();
   bool changed = data.calculatedNeutralThrust != value;
   data.calculatedNeutralThrust = value;
   mutex->unlock();
   if (changed) emit calculatedNeutralThrustChanged(value);
}

float StatusVtolLand::getWtgForGroundEffect(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.WtgForGroundEffect[index];
}
void StatusVtolLand::setWtgForGroundEffect(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.WtgForGroundEffect[index] != value;
   data.WtgForGroundEffect[index] = value;
   mutex->unlock();
   if (changed) emit WtgForGroundEffectChanged(index,value);
}

float StatusVtolLand::getWtgForGroundEffect_BounceVelocity() const
{
   QMutexLocker locker(mutex);
   return data.WtgForGroundEffect[0];
}
void StatusVtolLand::setWtgForGroundEffect_BounceVelocity(float value)
{
   mutex->lock();
   bool changed = data.WtgForGroundEffect[0] != value;
   data.WtgForGroundEffect[0] = value;
   mutex->unlock();
   if (changed) emit WtgForGroundEffect_BounceVelocityChanged(value);
}

float StatusVtolLand::getWtgForGroundEffect_BounceAccel() const
{
   QMutexLocker locker(mutex);
   return data.WtgForGroundEffect[1];
}
void StatusVtolLand::setWtgForGroundEffect_BounceAccel(float value)
{
   mutex->lock();
   bool changed = data.WtgForGroundEffect[1] != value;
   data.WtgForGroundEffect[1] = value;
   mutex->unlock();
   if (changed) emit WtgForGroundEffect_BounceAccelChanged(value);
}

quint8 StatusVtolLand::getState() const
{
   QMutexLocker locker(mutex);
   return data.State;
}
void StatusVtolLand::setState(quint8 value)
{
   mutex->lock();
   bool changed = data.State != value;
   data.State = value;
   mutex->unlock();
   if (changed) emit StateChanged(value);
}

quint8 StatusVtolLand::getStateExitReason(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.StateExitReason[index];
}
void StatusVtolLand::setStateExitReason(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.StateExitReason[index] != value;
   data.StateExitReason[index] = value;
   mutex->unlock();
   if (changed) emit StateExitReasonChanged(index,value);
}

quint8 StatusVtolLand::getStateExitReason_0() const
{
   QMutexLocker locker(mutex);
   return data.StateExitReason[0];
}
void StatusVtolLand::setStateExitReason_0(quint8 value)
{
   mutex->lock();
   bool changed = data.StateExitReason[0] != value;
   data.StateExitReason[0] = value;
   mutex->unlock();
   if (changed) emit StateExitReason_0Changed(value);
}

quint8 StatusVtolLand::getStateExitReason_1() const
{
   QMutexLocker locker(mutex);
   return data.StateExitReason[1];
}
void StatusVtolLand::setStateExitReason_1(quint8 value)
{
   mutex->lock();
   bool changed = data.StateExitReason[1] != value;
   data.StateExitReason[1] = value;
   mutex->unlock();
   if (changed) emit StateExitReason_1Changed(value);
}

quint8 StatusVtolLand::getStateExitReason_2() const
{
   QMutexLocker locker(mutex);
   return data.StateExitReason[2];
}
void StatusVtolLand::setStateExitReason_2(quint8 value)
{
   mutex->lock();
   bool changed = data.StateExitReason[2] != value;
   data.StateExitReason[2] = value;
   mutex->unlock();
   if (changed) emit StateExitReason_2Changed(value);
}

quint8 StatusVtolLand::getStateExitReason_3() const
{
   QMutexLocker locker(mutex);
   return data.StateExitReason[3];
}
void StatusVtolLand::setStateExitReason_3(quint8 value)
{
   mutex->lock();
   bool changed = data.StateExitReason[3] != value;
   data.StateExitReason[3] = value;
   mutex->unlock();
   if (changed) emit StateExitReason_3Changed(value);
}

quint8 StatusVtolLand::getStateExitReason_4() const
{
   QMutexLocker locker(mutex);
   return data.StateExitReason[4];
}
void StatusVtolLand::setStateExitReason_4(quint8 value)
{
   mutex->lock();
   bool changed = data.StateExitReason[4] != value;
   data.StateExitReason[4] = value;
   mutex->unlock();
   if (changed) emit StateExitReason_4Changed(value);
}

quint8 StatusVtolLand::getStateExitReason_5() const
{
   QMutexLocker locker(mutex);
   return data.StateExitReason[5];
}
void StatusVtolLand::setStateExitReason_5(quint8 value)
{
   mutex->lock();
   bool changed = data.StateExitReason[5] != value;
   data.StateExitReason[5] = value;
   mutex->unlock();
   if (changed) emit StateExitReason_5Changed(value);
}

quint8 StatusVtolLand::getStateExitReason_6() const
{
   QMutexLocker locker(mutex);
   return data.StateExitReason[6];
}
void StatusVtolLand::setStateExitReason_6(quint8 value)
{
   mutex->lock();
   bool changed = data.StateExitReason[6] != value;
   data.StateExitReason[6] = value;
   mutex->unlock();
   if (changed) emit StateExitReason_6Changed(value);
}

quint8 StatusVtolLand::getStateExitReason_7() const
{
   QMutexLocker locker(mutex);
   return data.StateExitReason[7];
}
void StatusVtolLand::setStateExitReason_7(quint8 value)
{
   mutex->lock();
   bool changed = data.StateExitReason[7] != value;
   data.StateExitReason[7] = value;
   mutex->unlock();
   if (changed) emit StateExitReason_7Changed(value);
}

quint8 StatusVtolLand::getStateExitReason_8() const
{
   QMutexLocker locker(mutex);
   return data.StateExitReason[8];
}
void StatusVtolLand::setStateExitReason_8(quint8 value)
{
   mutex->lock();
   bool changed = data.StateExitReason[8] != value;
   data.StateExitReason[8] = value;
   mutex->unlock();
   if (changed) emit StateExitReason_8Changed(value);
}

quint8 StatusVtolLand::getStateExitReason_9() const
{
   QMutexLocker locker(mutex);
   return data.StateExitReason[9];
}
void StatusVtolLand::setStateExitReason_9(quint8 value)
{
   mutex->lock();
   bool changed = data.StateExitReason[9] != value;
   data.StateExitReason[9] = value;
   mutex->unlock();
   if (changed) emit StateExitReason_9Changed(value);
}

quint8 StatusVtolLand::getAltitudeState() const
{
   QMutexLocker locker(mutex);
   return data.AltitudeState;
}
void StatusVtolLand::setAltitudeState(quint8 value)
{
   mutex->lock();
   bool changed = data.AltitudeState != value;
   data.AltitudeState = value;
   mutex->unlock();
   if (changed) emit AltitudeStateChanged(value);
}


