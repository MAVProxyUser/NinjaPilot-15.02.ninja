/**
 ******************************************************************************
 *
 * @file       vtolpathfollowersettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: vtolpathfollowersettings.xml.
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

#include "vtolpathfollowersettings.h"
#include "uavobjectfield.h"

const QString VtolPathFollowerSettings::NAME = QString("VtolPathFollowerSettings");
const QString VtolPathFollowerSettings::DESCRIPTION = QString("Settings for the @ref VtolPathFollowerModule");
const QString VtolPathFollowerSettings::CATEGORY = QString("Control");

/**
 * Constructor
 */
VtolPathFollowerSettings::VtolPathFollowerSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList HorizontalVelMaxElemNames;
    HorizontalVelMaxElemNames.append("0");
    fields.append( new UAVObjectField(QString("HorizontalVelMax"), tr("maximum allowed horizontal movement velocity"), QString("m/s"), UAVObjectField::FLOAT32, HorizontalVelMaxElemNames, QStringList(), QString("")));
    QStringList VerticalVelMaxElemNames;
    VerticalVelMaxElemNames.append("0");
    fields.append( new UAVObjectField(QString("VerticalVelMax"), tr("maximum allowed climb/dive velocity"), QString("m/s"), UAVObjectField::FLOAT32, VerticalVelMaxElemNames, QStringList(), QString("")));
    QStringList CourseFeedForwardElemNames;
    CourseFeedForwardElemNames.append("0");
    fields.append( new UAVObjectField(QString("CourseFeedForward"), tr(""), QString("s"), UAVObjectField::FLOAT32, CourseFeedForwardElemNames, QStringList(), QString("")));
    QStringList HorizontalPosPElemNames;
    HorizontalPosPElemNames.append("0");
    fields.append( new UAVObjectField(QString("HorizontalPosP"), tr(""), QString("(m/s)/m"), UAVObjectField::FLOAT32, HorizontalPosPElemNames, QStringList(), QString("")));
    QStringList VerticalPosPElemNames;
    VerticalPosPElemNames.append("0");
    fields.append( new UAVObjectField(QString("VerticalPosP"), tr(""), QString(""), UAVObjectField::FLOAT32, VerticalPosPElemNames, QStringList(), QString("")));
    QStringList HorizontalVelPIDElemNames;
    HorizontalVelPIDElemNames.append("Kp");
    HorizontalVelPIDElemNames.append("Ki");
    HorizontalVelPIDElemNames.append("Kd");
    HorizontalVelPIDElemNames.append("ILimit");
    fields.append( new UAVObjectField(QString("HorizontalVelPID"), tr(""), QString("deg/(m/s)"), UAVObjectField::FLOAT32, HorizontalVelPIDElemNames, QStringList(), QString("")));
    QStringList VerticalVelPIDElemNames;
    VerticalVelPIDElemNames.append("Kp");
    VerticalVelPIDElemNames.append("Ki");
    VerticalVelPIDElemNames.append("Kd");
    VerticalVelPIDElemNames.append("ILimit");
    fields.append( new UAVObjectField(QString("VerticalVelPID"), tr(""), QString(""), UAVObjectField::FLOAT32, VerticalVelPIDElemNames, QStringList(), QString("")));
    QStringList ThrustLimitsElemNames;
    ThrustLimitsElemNames.append("Min");
    ThrustLimitsElemNames.append("Neutral");
    ThrustLimitsElemNames.append("Max");
    fields.append( new UAVObjectField(QString("ThrustLimits"), tr(""), QString(""), UAVObjectField::FLOAT32, ThrustLimitsElemNames, QStringList(), QString("")));
    QStringList VelocityFeedforwardElemNames;
    VelocityFeedforwardElemNames.append("0");
    fields.append( new UAVObjectField(QString("VelocityFeedforward"), tr(""), QString("deg/(m/s)"), UAVObjectField::FLOAT32, VelocityFeedforwardElemNames, QStringList(), QString("")));
    QStringList FlyawayEmergencyFallbackTriggerTimeElemNames;
    FlyawayEmergencyFallbackTriggerTimeElemNames.append("0");
    fields.append( new UAVObjectField(QString("FlyawayEmergencyFallbackTriggerTime"), tr(""), QString("s"), UAVObjectField::FLOAT32, FlyawayEmergencyFallbackTriggerTimeElemNames, QStringList(), QString("")));
    QStringList EmergencyFallbackAttitudeElemNames;
    EmergencyFallbackAttitudeElemNames.append("Roll");
    EmergencyFallbackAttitudeElemNames.append("Pitch");
    fields.append( new UAVObjectField(QString("EmergencyFallbackAttitude"), tr(""), QString("deg"), UAVObjectField::FLOAT32, EmergencyFallbackAttitudeElemNames, QStringList(), QString("")));
    QStringList EmergencyFallbackYawRateElemNames;
    EmergencyFallbackYawRateElemNames.append("kP");
    EmergencyFallbackYawRateElemNames.append("Max");
    fields.append( new UAVObjectField(QString("EmergencyFallbackYawRate"), tr(""), QString("(deg/s)/deg"), UAVObjectField::FLOAT32, EmergencyFallbackYawRateElemNames, QStringList(), QString("")));
    QStringList MaxRollPitchElemNames;
    MaxRollPitchElemNames.append("0");
    fields.append( new UAVObjectField(QString("MaxRollPitch"), tr(""), QString("deg"), UAVObjectField::FLOAT32, MaxRollPitchElemNames, QStringList(), QString("")));
    QStringList BrakeRateElemNames;
    BrakeRateElemNames.append("0");
    fields.append( new UAVObjectField(QString("BrakeRate"), tr(""), QString("m/s2"), UAVObjectField::FLOAT32, BrakeRateElemNames, QStringList(), QString("")));
    QStringList BrakeMaxPitchElemNames;
    BrakeMaxPitchElemNames.append("0");
    fields.append( new UAVObjectField(QString("BrakeMaxPitch"), tr(""), QString("deg"), UAVObjectField::FLOAT32, BrakeMaxPitchElemNames, QStringList(), QString("")));
    QStringList BrakeHorizontalVelPIDElemNames;
    BrakeHorizontalVelPIDElemNames.append("Kp");
    BrakeHorizontalVelPIDElemNames.append("Ki");
    BrakeHorizontalVelPIDElemNames.append("Kd");
    BrakeHorizontalVelPIDElemNames.append("ILimit");
    fields.append( new UAVObjectField(QString("BrakeHorizontalVelPID"), tr(""), QString("deg/(m/s)"), UAVObjectField::FLOAT32, BrakeHorizontalVelPIDElemNames, QStringList(), QString("")));
    QStringList BrakeVelocityFeedforwardElemNames;
    BrakeVelocityFeedforwardElemNames.append("0");
    fields.append( new UAVObjectField(QString("BrakeVelocityFeedforward"), tr(""), QString("deg/(m/s)"), UAVObjectField::FLOAT32, BrakeVelocityFeedforwardElemNames, QStringList(), QString("")));
    QStringList LandVerticalVelPIDElemNames;
    LandVerticalVelPIDElemNames.append("Kp");
    LandVerticalVelPIDElemNames.append("Ki");
    LandVerticalVelPIDElemNames.append("Kd");
    LandVerticalVelPIDElemNames.append("Beta");
    fields.append( new UAVObjectField(QString("LandVerticalVelPID"), tr(""), QString(""), UAVObjectField::FLOAT32, LandVerticalVelPIDElemNames, QStringList(), QString("")));
    QStringList UpdatePeriodElemNames;
    UpdatePeriodElemNames.append("0");
    fields.append( new UAVObjectField(QString("UpdatePeriod"), tr(""), QString("ms"), UAVObjectField::UINT16, UpdatePeriodElemNames, QStringList(), QString("")));
    QStringList TreatCustomCraftAsElemNames;
    TreatCustomCraftAsElemNames.append("0");
    QStringList TreatCustomCraftAsEnumOptions;
    TreatCustomCraftAsEnumOptions.append("FixedWing");
    TreatCustomCraftAsEnumOptions.append("VTOL");
    TreatCustomCraftAsEnumOptions.append("Ground");
    fields.append( new UAVObjectField(QString("TreatCustomCraftAs"), tr(""), QString("switch"), UAVObjectField::ENUM, TreatCustomCraftAsElemNames, TreatCustomCraftAsEnumOptions, QString("")));
    QStringList ThrustControlElemNames;
    ThrustControlElemNames.append("0");
    QStringList ThrustControlEnumOptions;
    ThrustControlEnumOptions.append("manual");
    ThrustControlEnumOptions.append("auto");
    fields.append( new UAVObjectField(QString("ThrustControl"), tr(""), QString(""), UAVObjectField::ENUM, ThrustControlElemNames, ThrustControlEnumOptions, QString("")));
    QStringList YawControlElemNames;
    YawControlElemNames.append("0");
    QStringList YawControlEnumOptions;
    YawControlEnumOptions.append("manual");
    YawControlEnumOptions.append("tailin");
    YawControlEnumOptions.append("movementdirection");
    YawControlEnumOptions.append("pathdirection");
    YawControlEnumOptions.append("poi");
    fields.append( new UAVObjectField(QString("YawControl"), tr(""), QString(""), UAVObjectField::ENUM, YawControlElemNames, YawControlEnumOptions, QString("")));
    QStringList FlyawayEmergencyFallbackElemNames;
    FlyawayEmergencyFallbackElemNames.append("0");
    QStringList FlyawayEmergencyFallbackEnumOptions;
    FlyawayEmergencyFallbackEnumOptions.append("disabled");
    FlyawayEmergencyFallbackEnumOptions.append("enabled");
    FlyawayEmergencyFallbackEnumOptions.append("always");
    FlyawayEmergencyFallbackEnumOptions.append("debugtest");
    fields.append( new UAVObjectField(QString("FlyawayEmergencyFallback"), tr(""), QString("switch"), UAVObjectField::ENUM, FlyawayEmergencyFallbackElemNames, FlyawayEmergencyFallbackEnumOptions, QString("")));

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
UAVObject::Metadata VtolPathFollowerSettings::getDefaultMetadata()
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
void VtolPathFollowerSettings::setDefaultFieldValues()
{
    data.HorizontalVelMax = 10;
    data.VerticalVelMax = 4;
    data.CourseFeedForward = 1;
    data.HorizontalPosP = 0.25;
    data.VerticalPosP = 0.4;
    data.HorizontalVelPID[0] = 8;
    data.HorizontalVelPID[1] = 0.5;
    data.HorizontalVelPID[2] = 0;
    data.HorizontalVelPID[3] = 15;
    data.VerticalVelPID[0] = 0.3;
    data.VerticalVelPID[1] = 0.3;
    data.VerticalVelPID[2] = 0;
    data.VerticalVelPID[3] = 1;
    data.ThrustLimits[0] = 0.2;
    data.ThrustLimits[1] = 0.5;
    data.ThrustLimits[2] = 0.9;
    data.VelocityFeedforward = 2;
    data.FlyawayEmergencyFallbackTriggerTime = 10;
    data.EmergencyFallbackAttitude[0] = 0;
    data.EmergencyFallbackAttitude[1] = -20;
    data.EmergencyFallbackYawRate[0] = 2;
    data.EmergencyFallbackYawRate[1] = 30;
    data.MaxRollPitch = 25;
    data.BrakeRate = 2.5;
    data.BrakeMaxPitch = 25;
    data.BrakeHorizontalVelPID[0] = 12;
    data.BrakeHorizontalVelPID[1] = 0;
    data.BrakeHorizontalVelPID[2] = 0.03;
    data.BrakeHorizontalVelPID[3] = 15;
    data.BrakeVelocityFeedforward = 0;
    data.LandVerticalVelPID[0] = 0.35;
    data.LandVerticalVelPID[1] = 3;
    data.LandVerticalVelPID[2] = 0.05;
    data.LandVerticalVelPID[3] = 0.9;
    data.UpdatePeriod = 50;
    data.TreatCustomCraftAs = 0;
    data.ThrustControl = 0;
    data.YawControl = 0;
    data.FlyawayEmergencyFallback = 1;

}

/**
 * Get the object data fields
 */
VtolPathFollowerSettings::DataFields VtolPathFollowerSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void VtolPathFollowerSettings::setData(const DataFields& data)
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

void VtolPathFollowerSettings::emitNotifications()
{
            //if (data.HorizontalVelMax != oldData.HorizontalVelMax)
            emit HorizontalVelMaxChanged(data.HorizontalVelMax);
        //if (data.VerticalVelMax != oldData.VerticalVelMax)
            emit VerticalVelMaxChanged(data.VerticalVelMax);
        //if (data.CourseFeedForward != oldData.CourseFeedForward)
            emit CourseFeedForwardChanged(data.CourseFeedForward);
        //if (data.HorizontalPosP != oldData.HorizontalPosP)
            emit HorizontalPosPChanged(data.HorizontalPosP);
        //if (data.VerticalPosP != oldData.VerticalPosP)
            emit VerticalPosPChanged(data.VerticalPosP);
        //if (data.HorizontalVelPID[0] != oldData.HorizontalVelPID[0])
            emit HorizontalVelPID_KpChanged(data.HorizontalVelPID[0]);
        //if (data.HorizontalVelPID[1] != oldData.HorizontalVelPID[1])
            emit HorizontalVelPID_KiChanged(data.HorizontalVelPID[1]);
        //if (data.HorizontalVelPID[2] != oldData.HorizontalVelPID[2])
            emit HorizontalVelPID_KdChanged(data.HorizontalVelPID[2]);
        //if (data.HorizontalVelPID[3] != oldData.HorizontalVelPID[3])
            emit HorizontalVelPID_ILimitChanged(data.HorizontalVelPID[3]);
        //if (data.VerticalVelPID[0] != oldData.VerticalVelPID[0])
            emit VerticalVelPID_KpChanged(data.VerticalVelPID[0]);
        //if (data.VerticalVelPID[1] != oldData.VerticalVelPID[1])
            emit VerticalVelPID_KiChanged(data.VerticalVelPID[1]);
        //if (data.VerticalVelPID[2] != oldData.VerticalVelPID[2])
            emit VerticalVelPID_KdChanged(data.VerticalVelPID[2]);
        //if (data.VerticalVelPID[3] != oldData.VerticalVelPID[3])
            emit VerticalVelPID_ILimitChanged(data.VerticalVelPID[3]);
        //if (data.ThrustLimits[0] != oldData.ThrustLimits[0])
            emit ThrustLimits_MinChanged(data.ThrustLimits[0]);
        //if (data.ThrustLimits[1] != oldData.ThrustLimits[1])
            emit ThrustLimits_NeutralChanged(data.ThrustLimits[1]);
        //if (data.ThrustLimits[2] != oldData.ThrustLimits[2])
            emit ThrustLimits_MaxChanged(data.ThrustLimits[2]);
        //if (data.VelocityFeedforward != oldData.VelocityFeedforward)
            emit VelocityFeedforwardChanged(data.VelocityFeedforward);
        //if (data.FlyawayEmergencyFallbackTriggerTime != oldData.FlyawayEmergencyFallbackTriggerTime)
            emit FlyawayEmergencyFallbackTriggerTimeChanged(data.FlyawayEmergencyFallbackTriggerTime);
        //if (data.EmergencyFallbackAttitude[0] != oldData.EmergencyFallbackAttitude[0])
            emit EmergencyFallbackAttitude_RollChanged(data.EmergencyFallbackAttitude[0]);
        //if (data.EmergencyFallbackAttitude[1] != oldData.EmergencyFallbackAttitude[1])
            emit EmergencyFallbackAttitude_PitchChanged(data.EmergencyFallbackAttitude[1]);
        //if (data.EmergencyFallbackYawRate[0] != oldData.EmergencyFallbackYawRate[0])
            emit EmergencyFallbackYawRate_kPChanged(data.EmergencyFallbackYawRate[0]);
        //if (data.EmergencyFallbackYawRate[1] != oldData.EmergencyFallbackYawRate[1])
            emit EmergencyFallbackYawRate_MaxChanged(data.EmergencyFallbackYawRate[1]);
        //if (data.MaxRollPitch != oldData.MaxRollPitch)
            emit MaxRollPitchChanged(data.MaxRollPitch);
        //if (data.BrakeRate != oldData.BrakeRate)
            emit BrakeRateChanged(data.BrakeRate);
        //if (data.BrakeMaxPitch != oldData.BrakeMaxPitch)
            emit BrakeMaxPitchChanged(data.BrakeMaxPitch);
        //if (data.BrakeHorizontalVelPID[0] != oldData.BrakeHorizontalVelPID[0])
            emit BrakeHorizontalVelPID_KpChanged(data.BrakeHorizontalVelPID[0]);
        //if (data.BrakeHorizontalVelPID[1] != oldData.BrakeHorizontalVelPID[1])
            emit BrakeHorizontalVelPID_KiChanged(data.BrakeHorizontalVelPID[1]);
        //if (data.BrakeHorizontalVelPID[2] != oldData.BrakeHorizontalVelPID[2])
            emit BrakeHorizontalVelPID_KdChanged(data.BrakeHorizontalVelPID[2]);
        //if (data.BrakeHorizontalVelPID[3] != oldData.BrakeHorizontalVelPID[3])
            emit BrakeHorizontalVelPID_ILimitChanged(data.BrakeHorizontalVelPID[3]);
        //if (data.BrakeVelocityFeedforward != oldData.BrakeVelocityFeedforward)
            emit BrakeVelocityFeedforwardChanged(data.BrakeVelocityFeedforward);
        //if (data.LandVerticalVelPID[0] != oldData.LandVerticalVelPID[0])
            emit LandVerticalVelPID_KpChanged(data.LandVerticalVelPID[0]);
        //if (data.LandVerticalVelPID[1] != oldData.LandVerticalVelPID[1])
            emit LandVerticalVelPID_KiChanged(data.LandVerticalVelPID[1]);
        //if (data.LandVerticalVelPID[2] != oldData.LandVerticalVelPID[2])
            emit LandVerticalVelPID_KdChanged(data.LandVerticalVelPID[2]);
        //if (data.LandVerticalVelPID[3] != oldData.LandVerticalVelPID[3])
            emit LandVerticalVelPID_BetaChanged(data.LandVerticalVelPID[3]);
        //if (data.UpdatePeriod != oldData.UpdatePeriod)
            emit UpdatePeriodChanged(data.UpdatePeriod);
        //if (data.TreatCustomCraftAs != oldData.TreatCustomCraftAs)
            emit TreatCustomCraftAsChanged(data.TreatCustomCraftAs);
        //if (data.ThrustControl != oldData.ThrustControl)
            emit ThrustControlChanged(data.ThrustControl);
        //if (data.YawControl != oldData.YawControl)
            emit YawControlChanged(data.YawControl);
        //if (data.FlyawayEmergencyFallback != oldData.FlyawayEmergencyFallback)
            emit FlyawayEmergencyFallbackChanged(data.FlyawayEmergencyFallback);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *VtolPathFollowerSettings::clone(quint32 instID)
{
    VtolPathFollowerSettings *obj = new VtolPathFollowerSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *VtolPathFollowerSettings::dirtyClone()
{
    VtolPathFollowerSettings *obj = new VtolPathFollowerSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
VtolPathFollowerSettings *VtolPathFollowerSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<VtolPathFollowerSettings *>(objMngr->getObject(VtolPathFollowerSettings::OBJID, instID));
}

float VtolPathFollowerSettings::getHorizontalVelMax() const
{
   QMutexLocker locker(mutex);
   return data.HorizontalVelMax;
}
void VtolPathFollowerSettings::setHorizontalVelMax(float value)
{
   mutex->lock();
   bool changed = data.HorizontalVelMax != value;
   data.HorizontalVelMax = value;
   mutex->unlock();
   if (changed) emit HorizontalVelMaxChanged(value);
}

float VtolPathFollowerSettings::getVerticalVelMax() const
{
   QMutexLocker locker(mutex);
   return data.VerticalVelMax;
}
void VtolPathFollowerSettings::setVerticalVelMax(float value)
{
   mutex->lock();
   bool changed = data.VerticalVelMax != value;
   data.VerticalVelMax = value;
   mutex->unlock();
   if (changed) emit VerticalVelMaxChanged(value);
}

float VtolPathFollowerSettings::getCourseFeedForward() const
{
   QMutexLocker locker(mutex);
   return data.CourseFeedForward;
}
void VtolPathFollowerSettings::setCourseFeedForward(float value)
{
   mutex->lock();
   bool changed = data.CourseFeedForward != value;
   data.CourseFeedForward = value;
   mutex->unlock();
   if (changed) emit CourseFeedForwardChanged(value);
}

float VtolPathFollowerSettings::getHorizontalPosP() const
{
   QMutexLocker locker(mutex);
   return data.HorizontalPosP;
}
void VtolPathFollowerSettings::setHorizontalPosP(float value)
{
   mutex->lock();
   bool changed = data.HorizontalPosP != value;
   data.HorizontalPosP = value;
   mutex->unlock();
   if (changed) emit HorizontalPosPChanged(value);
}

float VtolPathFollowerSettings::getVerticalPosP() const
{
   QMutexLocker locker(mutex);
   return data.VerticalPosP;
}
void VtolPathFollowerSettings::setVerticalPosP(float value)
{
   mutex->lock();
   bool changed = data.VerticalPosP != value;
   data.VerticalPosP = value;
   mutex->unlock();
   if (changed) emit VerticalPosPChanged(value);
}

float VtolPathFollowerSettings::getHorizontalVelPID(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.HorizontalVelPID[index];
}
void VtolPathFollowerSettings::setHorizontalVelPID(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.HorizontalVelPID[index] != value;
   data.HorizontalVelPID[index] = value;
   mutex->unlock();
   if (changed) emit HorizontalVelPIDChanged(index,value);
}

float VtolPathFollowerSettings::getHorizontalVelPID_Kp() const
{
   QMutexLocker locker(mutex);
   return data.HorizontalVelPID[0];
}
void VtolPathFollowerSettings::setHorizontalVelPID_Kp(float value)
{
   mutex->lock();
   bool changed = data.HorizontalVelPID[0] != value;
   data.HorizontalVelPID[0] = value;
   mutex->unlock();
   if (changed) emit HorizontalVelPID_KpChanged(value);
}

float VtolPathFollowerSettings::getHorizontalVelPID_Ki() const
{
   QMutexLocker locker(mutex);
   return data.HorizontalVelPID[1];
}
void VtolPathFollowerSettings::setHorizontalVelPID_Ki(float value)
{
   mutex->lock();
   bool changed = data.HorizontalVelPID[1] != value;
   data.HorizontalVelPID[1] = value;
   mutex->unlock();
   if (changed) emit HorizontalVelPID_KiChanged(value);
}

float VtolPathFollowerSettings::getHorizontalVelPID_Kd() const
{
   QMutexLocker locker(mutex);
   return data.HorizontalVelPID[2];
}
void VtolPathFollowerSettings::setHorizontalVelPID_Kd(float value)
{
   mutex->lock();
   bool changed = data.HorizontalVelPID[2] != value;
   data.HorizontalVelPID[2] = value;
   mutex->unlock();
   if (changed) emit HorizontalVelPID_KdChanged(value);
}

float VtolPathFollowerSettings::getHorizontalVelPID_ILimit() const
{
   QMutexLocker locker(mutex);
   return data.HorizontalVelPID[3];
}
void VtolPathFollowerSettings::setHorizontalVelPID_ILimit(float value)
{
   mutex->lock();
   bool changed = data.HorizontalVelPID[3] != value;
   data.HorizontalVelPID[3] = value;
   mutex->unlock();
   if (changed) emit HorizontalVelPID_ILimitChanged(value);
}

float VtolPathFollowerSettings::getVerticalVelPID(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.VerticalVelPID[index];
}
void VtolPathFollowerSettings::setVerticalVelPID(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.VerticalVelPID[index] != value;
   data.VerticalVelPID[index] = value;
   mutex->unlock();
   if (changed) emit VerticalVelPIDChanged(index,value);
}

float VtolPathFollowerSettings::getVerticalVelPID_Kp() const
{
   QMutexLocker locker(mutex);
   return data.VerticalVelPID[0];
}
void VtolPathFollowerSettings::setVerticalVelPID_Kp(float value)
{
   mutex->lock();
   bool changed = data.VerticalVelPID[0] != value;
   data.VerticalVelPID[0] = value;
   mutex->unlock();
   if (changed) emit VerticalVelPID_KpChanged(value);
}

float VtolPathFollowerSettings::getVerticalVelPID_Ki() const
{
   QMutexLocker locker(mutex);
   return data.VerticalVelPID[1];
}
void VtolPathFollowerSettings::setVerticalVelPID_Ki(float value)
{
   mutex->lock();
   bool changed = data.VerticalVelPID[1] != value;
   data.VerticalVelPID[1] = value;
   mutex->unlock();
   if (changed) emit VerticalVelPID_KiChanged(value);
}

float VtolPathFollowerSettings::getVerticalVelPID_Kd() const
{
   QMutexLocker locker(mutex);
   return data.VerticalVelPID[2];
}
void VtolPathFollowerSettings::setVerticalVelPID_Kd(float value)
{
   mutex->lock();
   bool changed = data.VerticalVelPID[2] != value;
   data.VerticalVelPID[2] = value;
   mutex->unlock();
   if (changed) emit VerticalVelPID_KdChanged(value);
}

float VtolPathFollowerSettings::getVerticalVelPID_ILimit() const
{
   QMutexLocker locker(mutex);
   return data.VerticalVelPID[3];
}
void VtolPathFollowerSettings::setVerticalVelPID_ILimit(float value)
{
   mutex->lock();
   bool changed = data.VerticalVelPID[3] != value;
   data.VerticalVelPID[3] = value;
   mutex->unlock();
   if (changed) emit VerticalVelPID_ILimitChanged(value);
}

float VtolPathFollowerSettings::getThrustLimits(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ThrustLimits[index];
}
void VtolPathFollowerSettings::setThrustLimits(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ThrustLimits[index] != value;
   data.ThrustLimits[index] = value;
   mutex->unlock();
   if (changed) emit ThrustLimitsChanged(index,value);
}

float VtolPathFollowerSettings::getThrustLimits_Min() const
{
   QMutexLocker locker(mutex);
   return data.ThrustLimits[0];
}
void VtolPathFollowerSettings::setThrustLimits_Min(float value)
{
   mutex->lock();
   bool changed = data.ThrustLimits[0] != value;
   data.ThrustLimits[0] = value;
   mutex->unlock();
   if (changed) emit ThrustLimits_MinChanged(value);
}

float VtolPathFollowerSettings::getThrustLimits_Neutral() const
{
   QMutexLocker locker(mutex);
   return data.ThrustLimits[1];
}
void VtolPathFollowerSettings::setThrustLimits_Neutral(float value)
{
   mutex->lock();
   bool changed = data.ThrustLimits[1] != value;
   data.ThrustLimits[1] = value;
   mutex->unlock();
   if (changed) emit ThrustLimits_NeutralChanged(value);
}

float VtolPathFollowerSettings::getThrustLimits_Max() const
{
   QMutexLocker locker(mutex);
   return data.ThrustLimits[2];
}
void VtolPathFollowerSettings::setThrustLimits_Max(float value)
{
   mutex->lock();
   bool changed = data.ThrustLimits[2] != value;
   data.ThrustLimits[2] = value;
   mutex->unlock();
   if (changed) emit ThrustLimits_MaxChanged(value);
}

float VtolPathFollowerSettings::getVelocityFeedforward() const
{
   QMutexLocker locker(mutex);
   return data.VelocityFeedforward;
}
void VtolPathFollowerSettings::setVelocityFeedforward(float value)
{
   mutex->lock();
   bool changed = data.VelocityFeedforward != value;
   data.VelocityFeedforward = value;
   mutex->unlock();
   if (changed) emit VelocityFeedforwardChanged(value);
}

float VtolPathFollowerSettings::getFlyawayEmergencyFallbackTriggerTime() const
{
   QMutexLocker locker(mutex);
   return data.FlyawayEmergencyFallbackTriggerTime;
}
void VtolPathFollowerSettings::setFlyawayEmergencyFallbackTriggerTime(float value)
{
   mutex->lock();
   bool changed = data.FlyawayEmergencyFallbackTriggerTime != value;
   data.FlyawayEmergencyFallbackTriggerTime = value;
   mutex->unlock();
   if (changed) emit FlyawayEmergencyFallbackTriggerTimeChanged(value);
}

float VtolPathFollowerSettings::getEmergencyFallbackAttitude(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.EmergencyFallbackAttitude[index];
}
void VtolPathFollowerSettings::setEmergencyFallbackAttitude(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.EmergencyFallbackAttitude[index] != value;
   data.EmergencyFallbackAttitude[index] = value;
   mutex->unlock();
   if (changed) emit EmergencyFallbackAttitudeChanged(index,value);
}

float VtolPathFollowerSettings::getEmergencyFallbackAttitude_Roll() const
{
   QMutexLocker locker(mutex);
   return data.EmergencyFallbackAttitude[0];
}
void VtolPathFollowerSettings::setEmergencyFallbackAttitude_Roll(float value)
{
   mutex->lock();
   bool changed = data.EmergencyFallbackAttitude[0] != value;
   data.EmergencyFallbackAttitude[0] = value;
   mutex->unlock();
   if (changed) emit EmergencyFallbackAttitude_RollChanged(value);
}

float VtolPathFollowerSettings::getEmergencyFallbackAttitude_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.EmergencyFallbackAttitude[1];
}
void VtolPathFollowerSettings::setEmergencyFallbackAttitude_Pitch(float value)
{
   mutex->lock();
   bool changed = data.EmergencyFallbackAttitude[1] != value;
   data.EmergencyFallbackAttitude[1] = value;
   mutex->unlock();
   if (changed) emit EmergencyFallbackAttitude_PitchChanged(value);
}

float VtolPathFollowerSettings::getEmergencyFallbackYawRate(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.EmergencyFallbackYawRate[index];
}
void VtolPathFollowerSettings::setEmergencyFallbackYawRate(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.EmergencyFallbackYawRate[index] != value;
   data.EmergencyFallbackYawRate[index] = value;
   mutex->unlock();
   if (changed) emit EmergencyFallbackYawRateChanged(index,value);
}

float VtolPathFollowerSettings::getEmergencyFallbackYawRate_kP() const
{
   QMutexLocker locker(mutex);
   return data.EmergencyFallbackYawRate[0];
}
void VtolPathFollowerSettings::setEmergencyFallbackYawRate_kP(float value)
{
   mutex->lock();
   bool changed = data.EmergencyFallbackYawRate[0] != value;
   data.EmergencyFallbackYawRate[0] = value;
   mutex->unlock();
   if (changed) emit EmergencyFallbackYawRate_kPChanged(value);
}

float VtolPathFollowerSettings::getEmergencyFallbackYawRate_Max() const
{
   QMutexLocker locker(mutex);
   return data.EmergencyFallbackYawRate[1];
}
void VtolPathFollowerSettings::setEmergencyFallbackYawRate_Max(float value)
{
   mutex->lock();
   bool changed = data.EmergencyFallbackYawRate[1] != value;
   data.EmergencyFallbackYawRate[1] = value;
   mutex->unlock();
   if (changed) emit EmergencyFallbackYawRate_MaxChanged(value);
}

float VtolPathFollowerSettings::getMaxRollPitch() const
{
   QMutexLocker locker(mutex);
   return data.MaxRollPitch;
}
void VtolPathFollowerSettings::setMaxRollPitch(float value)
{
   mutex->lock();
   bool changed = data.MaxRollPitch != value;
   data.MaxRollPitch = value;
   mutex->unlock();
   if (changed) emit MaxRollPitchChanged(value);
}

float VtolPathFollowerSettings::getBrakeRate() const
{
   QMutexLocker locker(mutex);
   return data.BrakeRate;
}
void VtolPathFollowerSettings::setBrakeRate(float value)
{
   mutex->lock();
   bool changed = data.BrakeRate != value;
   data.BrakeRate = value;
   mutex->unlock();
   if (changed) emit BrakeRateChanged(value);
}

float VtolPathFollowerSettings::getBrakeMaxPitch() const
{
   QMutexLocker locker(mutex);
   return data.BrakeMaxPitch;
}
void VtolPathFollowerSettings::setBrakeMaxPitch(float value)
{
   mutex->lock();
   bool changed = data.BrakeMaxPitch != value;
   data.BrakeMaxPitch = value;
   mutex->unlock();
   if (changed) emit BrakeMaxPitchChanged(value);
}

float VtolPathFollowerSettings::getBrakeHorizontalVelPID(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.BrakeHorizontalVelPID[index];
}
void VtolPathFollowerSettings::setBrakeHorizontalVelPID(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.BrakeHorizontalVelPID[index] != value;
   data.BrakeHorizontalVelPID[index] = value;
   mutex->unlock();
   if (changed) emit BrakeHorizontalVelPIDChanged(index,value);
}

float VtolPathFollowerSettings::getBrakeHorizontalVelPID_Kp() const
{
   QMutexLocker locker(mutex);
   return data.BrakeHorizontalVelPID[0];
}
void VtolPathFollowerSettings::setBrakeHorizontalVelPID_Kp(float value)
{
   mutex->lock();
   bool changed = data.BrakeHorizontalVelPID[0] != value;
   data.BrakeHorizontalVelPID[0] = value;
   mutex->unlock();
   if (changed) emit BrakeHorizontalVelPID_KpChanged(value);
}

float VtolPathFollowerSettings::getBrakeHorizontalVelPID_Ki() const
{
   QMutexLocker locker(mutex);
   return data.BrakeHorizontalVelPID[1];
}
void VtolPathFollowerSettings::setBrakeHorizontalVelPID_Ki(float value)
{
   mutex->lock();
   bool changed = data.BrakeHorizontalVelPID[1] != value;
   data.BrakeHorizontalVelPID[1] = value;
   mutex->unlock();
   if (changed) emit BrakeHorizontalVelPID_KiChanged(value);
}

float VtolPathFollowerSettings::getBrakeHorizontalVelPID_Kd() const
{
   QMutexLocker locker(mutex);
   return data.BrakeHorizontalVelPID[2];
}
void VtolPathFollowerSettings::setBrakeHorizontalVelPID_Kd(float value)
{
   mutex->lock();
   bool changed = data.BrakeHorizontalVelPID[2] != value;
   data.BrakeHorizontalVelPID[2] = value;
   mutex->unlock();
   if (changed) emit BrakeHorizontalVelPID_KdChanged(value);
}

float VtolPathFollowerSettings::getBrakeHorizontalVelPID_ILimit() const
{
   QMutexLocker locker(mutex);
   return data.BrakeHorizontalVelPID[3];
}
void VtolPathFollowerSettings::setBrakeHorizontalVelPID_ILimit(float value)
{
   mutex->lock();
   bool changed = data.BrakeHorizontalVelPID[3] != value;
   data.BrakeHorizontalVelPID[3] = value;
   mutex->unlock();
   if (changed) emit BrakeHorizontalVelPID_ILimitChanged(value);
}

float VtolPathFollowerSettings::getBrakeVelocityFeedforward() const
{
   QMutexLocker locker(mutex);
   return data.BrakeVelocityFeedforward;
}
void VtolPathFollowerSettings::setBrakeVelocityFeedforward(float value)
{
   mutex->lock();
   bool changed = data.BrakeVelocityFeedforward != value;
   data.BrakeVelocityFeedforward = value;
   mutex->unlock();
   if (changed) emit BrakeVelocityFeedforwardChanged(value);
}

float VtolPathFollowerSettings::getLandVerticalVelPID(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.LandVerticalVelPID[index];
}
void VtolPathFollowerSettings::setLandVerticalVelPID(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.LandVerticalVelPID[index] != value;
   data.LandVerticalVelPID[index] = value;
   mutex->unlock();
   if (changed) emit LandVerticalVelPIDChanged(index,value);
}

float VtolPathFollowerSettings::getLandVerticalVelPID_Kp() const
{
   QMutexLocker locker(mutex);
   return data.LandVerticalVelPID[0];
}
void VtolPathFollowerSettings::setLandVerticalVelPID_Kp(float value)
{
   mutex->lock();
   bool changed = data.LandVerticalVelPID[0] != value;
   data.LandVerticalVelPID[0] = value;
   mutex->unlock();
   if (changed) emit LandVerticalVelPID_KpChanged(value);
}

float VtolPathFollowerSettings::getLandVerticalVelPID_Ki() const
{
   QMutexLocker locker(mutex);
   return data.LandVerticalVelPID[1];
}
void VtolPathFollowerSettings::setLandVerticalVelPID_Ki(float value)
{
   mutex->lock();
   bool changed = data.LandVerticalVelPID[1] != value;
   data.LandVerticalVelPID[1] = value;
   mutex->unlock();
   if (changed) emit LandVerticalVelPID_KiChanged(value);
}

float VtolPathFollowerSettings::getLandVerticalVelPID_Kd() const
{
   QMutexLocker locker(mutex);
   return data.LandVerticalVelPID[2];
}
void VtolPathFollowerSettings::setLandVerticalVelPID_Kd(float value)
{
   mutex->lock();
   bool changed = data.LandVerticalVelPID[2] != value;
   data.LandVerticalVelPID[2] = value;
   mutex->unlock();
   if (changed) emit LandVerticalVelPID_KdChanged(value);
}

float VtolPathFollowerSettings::getLandVerticalVelPID_Beta() const
{
   QMutexLocker locker(mutex);
   return data.LandVerticalVelPID[3];
}
void VtolPathFollowerSettings::setLandVerticalVelPID_Beta(float value)
{
   mutex->lock();
   bool changed = data.LandVerticalVelPID[3] != value;
   data.LandVerticalVelPID[3] = value;
   mutex->unlock();
   if (changed) emit LandVerticalVelPID_BetaChanged(value);
}

quint16 VtolPathFollowerSettings::getUpdatePeriod() const
{
   QMutexLocker locker(mutex);
   return data.UpdatePeriod;
}
void VtolPathFollowerSettings::setUpdatePeriod(quint16 value)
{
   mutex->lock();
   bool changed = data.UpdatePeriod != value;
   data.UpdatePeriod = value;
   mutex->unlock();
   if (changed) emit UpdatePeriodChanged(value);
}

quint8 VtolPathFollowerSettings::getTreatCustomCraftAs() const
{
   QMutexLocker locker(mutex);
   return data.TreatCustomCraftAs;
}
void VtolPathFollowerSettings::setTreatCustomCraftAs(quint8 value)
{
   mutex->lock();
   bool changed = data.TreatCustomCraftAs != value;
   data.TreatCustomCraftAs = value;
   mutex->unlock();
   if (changed) emit TreatCustomCraftAsChanged(value);
}

quint8 VtolPathFollowerSettings::getThrustControl() const
{
   QMutexLocker locker(mutex);
   return data.ThrustControl;
}
void VtolPathFollowerSettings::setThrustControl(quint8 value)
{
   mutex->lock();
   bool changed = data.ThrustControl != value;
   data.ThrustControl = value;
   mutex->unlock();
   if (changed) emit ThrustControlChanged(value);
}

quint8 VtolPathFollowerSettings::getYawControl() const
{
   QMutexLocker locker(mutex);
   return data.YawControl;
}
void VtolPathFollowerSettings::setYawControl(quint8 value)
{
   mutex->lock();
   bool changed = data.YawControl != value;
   data.YawControl = value;
   mutex->unlock();
   if (changed) emit YawControlChanged(value);
}

quint8 VtolPathFollowerSettings::getFlyawayEmergencyFallback() const
{
   QMutexLocker locker(mutex);
   return data.FlyawayEmergencyFallback;
}
void VtolPathFollowerSettings::setFlyawayEmergencyFallback(quint8 value)
{
   mutex->lock();
   bool changed = data.FlyawayEmergencyFallback != value;
   data.FlyawayEmergencyFallback = value;
   mutex->unlock();
   if (changed) emit FlyawayEmergencyFallbackChanged(value);
}


