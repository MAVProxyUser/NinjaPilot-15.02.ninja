/**
 ******************************************************************************
 *
 * @file       stabilizationsettingsbank1.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: stabilizationsettingsbank1.xml.
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

#include "stabilizationsettingsbank1.h"
#include "uavobjectfield.h"

const QString StabilizationSettingsBank1::NAME = QString("StabilizationSettingsBank1");
const QString StabilizationSettingsBank1::DESCRIPTION = QString("Currently selected PID bank");
const QString StabilizationSettingsBank1::CATEGORY = QString("Control");

/**
 * Constructor
 */
StabilizationSettingsBank1::StabilizationSettingsBank1(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList ManualRateElemNames;
    ManualRateElemNames.append("Roll");
    ManualRateElemNames.append("Pitch");
    ManualRateElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("ManualRate"), tr(""), QString("degrees/sec"), UAVObjectField::FLOAT32, ManualRateElemNames, QStringList(), QString("%BE:0:500; %BE:0:500; %BE:0:500")));
    QStringList MaximumRateElemNames;
    MaximumRateElemNames.append("Roll");
    MaximumRateElemNames.append("Pitch");
    MaximumRateElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("MaximumRate"), tr(""), QString("degrees/sec"), UAVObjectField::FLOAT32, MaximumRateElemNames, QStringList(), QString("%BE:0:500; %BE:0:500; %BE:0:500")));
    QStringList RollRatePIDElemNames;
    RollRatePIDElemNames.append("Kp");
    RollRatePIDElemNames.append("Ki");
    RollRatePIDElemNames.append("Kd");
    RollRatePIDElemNames.append("ILimit");
    fields.append( new UAVObjectField(QString("RollRatePID"), tr(""), QString(""), UAVObjectField::FLOAT32, RollRatePIDElemNames, QStringList(), QString("%BE:0:0.01; %BE:0:0.015; ; ")));
    QStringList PitchRatePIDElemNames;
    PitchRatePIDElemNames.append("Kp");
    PitchRatePIDElemNames.append("Ki");
    PitchRatePIDElemNames.append("Kd");
    PitchRatePIDElemNames.append("ILimit");
    fields.append( new UAVObjectField(QString("PitchRatePID"), tr(""), QString(""), UAVObjectField::FLOAT32, PitchRatePIDElemNames, QStringList(), QString("%BE:0:0.01; %BE:0:0.015; ; ")));
    QStringList YawRatePIDElemNames;
    YawRatePIDElemNames.append("Kp");
    YawRatePIDElemNames.append("Ki");
    YawRatePIDElemNames.append("Kd");
    YawRatePIDElemNames.append("ILimit");
    fields.append( new UAVObjectField(QString("YawRatePID"), tr(""), QString(""), UAVObjectField::FLOAT32, YawRatePIDElemNames, QStringList(), QString("%BE:0:0.01; %BE:0:0.015 ; ; ")));
    QStringList RollPIElemNames;
    RollPIElemNames.append("Kp");
    RollPIElemNames.append("Ki");
    RollPIElemNames.append("ILimit");
    fields.append( new UAVObjectField(QString("RollPI"), tr(""), QString(""), UAVObjectField::FLOAT32, RollPIElemNames, QStringList(), QString("%BE:0:10; %BE:0:10; ")));
    QStringList PitchPIElemNames;
    PitchPIElemNames.append("Kp");
    PitchPIElemNames.append("Ki");
    PitchPIElemNames.append("ILimit");
    fields.append( new UAVObjectField(QString("PitchPI"), tr(""), QString(""), UAVObjectField::FLOAT32, PitchPIElemNames, QStringList(), QString("%BE:0:10; %BE:0:10; ")));
    QStringList YawPIElemNames;
    YawPIElemNames.append("Kp");
    YawPIElemNames.append("Ki");
    YawPIElemNames.append("ILimit");
    fields.append( new UAVObjectField(QString("YawPI"), tr(""), QString(""), UAVObjectField::FLOAT32, YawPIElemNames, QStringList(), QString("%BE:0:10; %BE:0:10; ")));
    QStringList AcroInsanityFactorElemNames;
    AcroInsanityFactorElemNames.append("0");
    fields.append( new UAVObjectField(QString("AcroInsanityFactor"), tr(""), QString("percent"), UAVObjectField::FLOAT32, AcroInsanityFactorElemNames, QStringList(), QString("%BE:0.0:1.0")));
    QStringList ThrustPIDScaleCurveElemNames;
    ThrustPIDScaleCurveElemNames.append("0");
    ThrustPIDScaleCurveElemNames.append("25");
    ThrustPIDScaleCurveElemNames.append("50");
    ThrustPIDScaleCurveElemNames.append("75");
    ThrustPIDScaleCurveElemNames.append("100");
    fields.append( new UAVObjectField(QString("ThrustPIDScaleCurve"), tr(""), QString("percent"), UAVObjectField::FLOAT32, ThrustPIDScaleCurveElemNames, QStringList(), QString("")));
    QStringList RollMaxElemNames;
    RollMaxElemNames.append("0");
    fields.append( new UAVObjectField(QString("RollMax"), tr(""), QString("degrees"), UAVObjectField::UINT8, RollMaxElemNames, QStringList(), QString("%BE:0:180")));
    QStringList PitchMaxElemNames;
    PitchMaxElemNames.append("0");
    fields.append( new UAVObjectField(QString("PitchMax"), tr(""), QString("degrees"), UAVObjectField::UINT8, PitchMaxElemNames, QStringList(), QString("%BE:0:180")));
    QStringList YawMaxElemNames;
    YawMaxElemNames.append("0");
    fields.append( new UAVObjectField(QString("YawMax"), tr(""), QString("degrees"), UAVObjectField::UINT8, YawMaxElemNames, QStringList(), QString("%BE:0:180")));
    QStringList StickExpoElemNames;
    StickExpoElemNames.append("Roll");
    StickExpoElemNames.append("Pitch");
    StickExpoElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("StickExpo"), tr(""), QString("percent"), UAVObjectField::INT8, StickExpoElemNames, QStringList(), QString("%BE:-100:100; %BE:-100:100; %BE:-100:100")));
    QStringList EnablePiroCompElemNames;
    EnablePiroCompElemNames.append("0");
    QStringList EnablePiroCompEnumOptions;
    EnablePiroCompEnumOptions.append("FALSE");
    EnablePiroCompEnumOptions.append("TRUE");
    fields.append( new UAVObjectField(QString("EnablePiroComp"), tr(""), QString(""), UAVObjectField::ENUM, EnablePiroCompElemNames, EnablePiroCompEnumOptions, QString("")));
    QStringList EnableThrustPIDScalingElemNames;
    EnableThrustPIDScalingElemNames.append("0");
    QStringList EnableThrustPIDScalingEnumOptions;
    EnableThrustPIDScalingEnumOptions.append("FALSE");
    EnableThrustPIDScalingEnumOptions.append("TRUE");
    fields.append( new UAVObjectField(QString("EnableThrustPIDScaling"), tr(""), QString(""), UAVObjectField::ENUM, EnableThrustPIDScalingElemNames, EnableThrustPIDScalingEnumOptions, QString("")));
    QStringList ThrustPIDScaleSourceElemNames;
    ThrustPIDScaleSourceElemNames.append("0");
    QStringList ThrustPIDScaleSourceEnumOptions;
    ThrustPIDScaleSourceEnumOptions.append("ManualControlThrottle");
    ThrustPIDScaleSourceEnumOptions.append("StabilizationDesiredThrust");
    ThrustPIDScaleSourceEnumOptions.append("ActuatorDesiredThrust");
    fields.append( new UAVObjectField(QString("ThrustPIDScaleSource"), tr(""), QString(""), UAVObjectField::ENUM, ThrustPIDScaleSourceElemNames, ThrustPIDScaleSourceEnumOptions, QString("")));
    QStringList ThrustPIDScaleTargetElemNames;
    ThrustPIDScaleTargetElemNames.append("0");
    QStringList ThrustPIDScaleTargetEnumOptions;
    ThrustPIDScaleTargetEnumOptions.append("PID");
    ThrustPIDScaleTargetEnumOptions.append("PI");
    ThrustPIDScaleTargetEnumOptions.append("PD");
    ThrustPIDScaleTargetEnumOptions.append("ID");
    ThrustPIDScaleTargetEnumOptions.append("P");
    ThrustPIDScaleTargetEnumOptions.append("I");
    ThrustPIDScaleTargetEnumOptions.append("D");
    fields.append( new UAVObjectField(QString("ThrustPIDScaleTarget"), tr(""), QString(""), UAVObjectField::ENUM, ThrustPIDScaleTargetElemNames, ThrustPIDScaleTargetEnumOptions, QString("")));
    QStringList ThrustPIDScaleAxesElemNames;
    ThrustPIDScaleAxesElemNames.append("0");
    QStringList ThrustPIDScaleAxesEnumOptions;
    ThrustPIDScaleAxesEnumOptions.append("Roll Pitch Yaw");
    ThrustPIDScaleAxesEnumOptions.append("Roll Pitch");
    ThrustPIDScaleAxesEnumOptions.append("Roll Yaw");
    ThrustPIDScaleAxesEnumOptions.append("Roll");
    ThrustPIDScaleAxesEnumOptions.append("Pitch Yaw");
    ThrustPIDScaleAxesEnumOptions.append("Pitch");
    ThrustPIDScaleAxesEnumOptions.append("Yaw");
    fields.append( new UAVObjectField(QString("ThrustPIDScaleAxes"), tr(""), QString(""), UAVObjectField::ENUM, ThrustPIDScaleAxesElemNames, ThrustPIDScaleAxesEnumOptions, QString("")));

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
UAVObject::Metadata StabilizationSettingsBank1::getDefaultMetadata()
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
void StabilizationSettingsBank1::setDefaultFieldValues()
{
    data.ManualRate[0] = 220;
    data.ManualRate[1] = 220;
    data.ManualRate[2] = 220;
    data.MaximumRate[0] = 300;
    data.MaximumRate[1] = 300;
    data.MaximumRate[2] = 300;
    data.RollRatePID[0] = 0.003;
    data.RollRatePID[1] = 0.0065;
    data.RollRatePID[2] = 3.3e-05;
    data.RollRatePID[3] = 0.3;
    data.PitchRatePID[0] = 0.003;
    data.PitchRatePID[1] = 0.0065;
    data.PitchRatePID[2] = 3.3e-05;
    data.PitchRatePID[3] = 0.3;
    data.YawRatePID[0] = 0.0062;
    data.YawRatePID[1] = 0.01;
    data.YawRatePID[2] = 5e-05;
    data.YawRatePID[3] = 0.3;
    data.RollPI[0] = 2.5;
    data.RollPI[1] = 0;
    data.RollPI[2] = 50;
    data.PitchPI[0] = 2.5;
    data.PitchPI[1] = 0;
    data.PitchPI[2] = 50;
    data.YawPI[0] = 2.5;
    data.YawPI[1] = 0;
    data.YawPI[2] = 50;
    data.AcroInsanityFactor = 0.4;
    data.ThrustPIDScaleCurve[0] = 0.3;
    data.ThrustPIDScaleCurve[1] = 0.15;
    data.ThrustPIDScaleCurve[2] = 0;
    data.ThrustPIDScaleCurve[3] = -0.15;
    data.ThrustPIDScaleCurve[4] = -0.3;
    data.RollMax = 55;
    data.PitchMax = 55;
    data.YawMax = 35;
    data.StickExpo[0] = 0;
    data.StickExpo[1] = 0;
    data.StickExpo[2] = 0;
    data.EnablePiroComp = 1;
    data.EnableThrustPIDScaling = 0;
    data.ThrustPIDScaleSource = 2;
    data.ThrustPIDScaleTarget = 0;
    data.ThrustPIDScaleAxes = 1;

}

/**
 * Get the object data fields
 */
StabilizationSettingsBank1::DataFields StabilizationSettingsBank1::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void StabilizationSettingsBank1::setData(const DataFields& data)
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

void StabilizationSettingsBank1::emitNotifications()
{
            //if (data.ManualRate[0] != oldData.ManualRate[0])
            emit ManualRate_RollChanged(data.ManualRate[0]);
        //if (data.ManualRate[1] != oldData.ManualRate[1])
            emit ManualRate_PitchChanged(data.ManualRate[1]);
        //if (data.ManualRate[2] != oldData.ManualRate[2])
            emit ManualRate_YawChanged(data.ManualRate[2]);
        //if (data.MaximumRate[0] != oldData.MaximumRate[0])
            emit MaximumRate_RollChanged(data.MaximumRate[0]);
        //if (data.MaximumRate[1] != oldData.MaximumRate[1])
            emit MaximumRate_PitchChanged(data.MaximumRate[1]);
        //if (data.MaximumRate[2] != oldData.MaximumRate[2])
            emit MaximumRate_YawChanged(data.MaximumRate[2]);
        //if (data.RollRatePID[0] != oldData.RollRatePID[0])
            emit RollRatePID_KpChanged(data.RollRatePID[0]);
        //if (data.RollRatePID[1] != oldData.RollRatePID[1])
            emit RollRatePID_KiChanged(data.RollRatePID[1]);
        //if (data.RollRatePID[2] != oldData.RollRatePID[2])
            emit RollRatePID_KdChanged(data.RollRatePID[2]);
        //if (data.RollRatePID[3] != oldData.RollRatePID[3])
            emit RollRatePID_ILimitChanged(data.RollRatePID[3]);
        //if (data.PitchRatePID[0] != oldData.PitchRatePID[0])
            emit PitchRatePID_KpChanged(data.PitchRatePID[0]);
        //if (data.PitchRatePID[1] != oldData.PitchRatePID[1])
            emit PitchRatePID_KiChanged(data.PitchRatePID[1]);
        //if (data.PitchRatePID[2] != oldData.PitchRatePID[2])
            emit PitchRatePID_KdChanged(data.PitchRatePID[2]);
        //if (data.PitchRatePID[3] != oldData.PitchRatePID[3])
            emit PitchRatePID_ILimitChanged(data.PitchRatePID[3]);
        //if (data.YawRatePID[0] != oldData.YawRatePID[0])
            emit YawRatePID_KpChanged(data.YawRatePID[0]);
        //if (data.YawRatePID[1] != oldData.YawRatePID[1])
            emit YawRatePID_KiChanged(data.YawRatePID[1]);
        //if (data.YawRatePID[2] != oldData.YawRatePID[2])
            emit YawRatePID_KdChanged(data.YawRatePID[2]);
        //if (data.YawRatePID[3] != oldData.YawRatePID[3])
            emit YawRatePID_ILimitChanged(data.YawRatePID[3]);
        //if (data.RollPI[0] != oldData.RollPI[0])
            emit RollPI_KpChanged(data.RollPI[0]);
        //if (data.RollPI[1] != oldData.RollPI[1])
            emit RollPI_KiChanged(data.RollPI[1]);
        //if (data.RollPI[2] != oldData.RollPI[2])
            emit RollPI_ILimitChanged(data.RollPI[2]);
        //if (data.PitchPI[0] != oldData.PitchPI[0])
            emit PitchPI_KpChanged(data.PitchPI[0]);
        //if (data.PitchPI[1] != oldData.PitchPI[1])
            emit PitchPI_KiChanged(data.PitchPI[1]);
        //if (data.PitchPI[2] != oldData.PitchPI[2])
            emit PitchPI_ILimitChanged(data.PitchPI[2]);
        //if (data.YawPI[0] != oldData.YawPI[0])
            emit YawPI_KpChanged(data.YawPI[0]);
        //if (data.YawPI[1] != oldData.YawPI[1])
            emit YawPI_KiChanged(data.YawPI[1]);
        //if (data.YawPI[2] != oldData.YawPI[2])
            emit YawPI_ILimitChanged(data.YawPI[2]);
        //if (data.AcroInsanityFactor != oldData.AcroInsanityFactor)
            emit AcroInsanityFactorChanged(data.AcroInsanityFactor);
        //if (data.ThrustPIDScaleCurve[0] != oldData.ThrustPIDScaleCurve[0])
            emit ThrustPIDScaleCurve_0Changed(data.ThrustPIDScaleCurve[0]);
        //if (data.ThrustPIDScaleCurve[1] != oldData.ThrustPIDScaleCurve[1])
            emit ThrustPIDScaleCurve_25Changed(data.ThrustPIDScaleCurve[1]);
        //if (data.ThrustPIDScaleCurve[2] != oldData.ThrustPIDScaleCurve[2])
            emit ThrustPIDScaleCurve_50Changed(data.ThrustPIDScaleCurve[2]);
        //if (data.ThrustPIDScaleCurve[3] != oldData.ThrustPIDScaleCurve[3])
            emit ThrustPIDScaleCurve_75Changed(data.ThrustPIDScaleCurve[3]);
        //if (data.ThrustPIDScaleCurve[4] != oldData.ThrustPIDScaleCurve[4])
            emit ThrustPIDScaleCurve_100Changed(data.ThrustPIDScaleCurve[4]);
        //if (data.RollMax != oldData.RollMax)
            emit RollMaxChanged(data.RollMax);
        //if (data.PitchMax != oldData.PitchMax)
            emit PitchMaxChanged(data.PitchMax);
        //if (data.YawMax != oldData.YawMax)
            emit YawMaxChanged(data.YawMax);
        //if (data.StickExpo[0] != oldData.StickExpo[0])
            emit StickExpo_RollChanged(data.StickExpo[0]);
        //if (data.StickExpo[1] != oldData.StickExpo[1])
            emit StickExpo_PitchChanged(data.StickExpo[1]);
        //if (data.StickExpo[2] != oldData.StickExpo[2])
            emit StickExpo_YawChanged(data.StickExpo[2]);
        //if (data.EnablePiroComp != oldData.EnablePiroComp)
            emit EnablePiroCompChanged(data.EnablePiroComp);
        //if (data.EnableThrustPIDScaling != oldData.EnableThrustPIDScaling)
            emit EnableThrustPIDScalingChanged(data.EnableThrustPIDScaling);
        //if (data.ThrustPIDScaleSource != oldData.ThrustPIDScaleSource)
            emit ThrustPIDScaleSourceChanged(data.ThrustPIDScaleSource);
        //if (data.ThrustPIDScaleTarget != oldData.ThrustPIDScaleTarget)
            emit ThrustPIDScaleTargetChanged(data.ThrustPIDScaleTarget);
        //if (data.ThrustPIDScaleAxes != oldData.ThrustPIDScaleAxes)
            emit ThrustPIDScaleAxesChanged(data.ThrustPIDScaleAxes);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *StabilizationSettingsBank1::clone(quint32 instID)
{
    StabilizationSettingsBank1 *obj = new StabilizationSettingsBank1();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *StabilizationSettingsBank1::dirtyClone()
{
    StabilizationSettingsBank1 *obj = new StabilizationSettingsBank1();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
StabilizationSettingsBank1 *StabilizationSettingsBank1::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<StabilizationSettingsBank1 *>(objMngr->getObject(StabilizationSettingsBank1::OBJID, instID));
}

float StabilizationSettingsBank1::getManualRate(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ManualRate[index];
}
void StabilizationSettingsBank1::setManualRate(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ManualRate[index] != value;
   data.ManualRate[index] = value;
   mutex->unlock();
   if (changed) emit ManualRateChanged(index,value);
}

float StabilizationSettingsBank1::getManualRate_Roll() const
{
   QMutexLocker locker(mutex);
   return data.ManualRate[0];
}
void StabilizationSettingsBank1::setManualRate_Roll(float value)
{
   mutex->lock();
   bool changed = data.ManualRate[0] != value;
   data.ManualRate[0] = value;
   mutex->unlock();
   if (changed) emit ManualRate_RollChanged(value);
}

float StabilizationSettingsBank1::getManualRate_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.ManualRate[1];
}
void StabilizationSettingsBank1::setManualRate_Pitch(float value)
{
   mutex->lock();
   bool changed = data.ManualRate[1] != value;
   data.ManualRate[1] = value;
   mutex->unlock();
   if (changed) emit ManualRate_PitchChanged(value);
}

float StabilizationSettingsBank1::getManualRate_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.ManualRate[2];
}
void StabilizationSettingsBank1::setManualRate_Yaw(float value)
{
   mutex->lock();
   bool changed = data.ManualRate[2] != value;
   data.ManualRate[2] = value;
   mutex->unlock();
   if (changed) emit ManualRate_YawChanged(value);
}

float StabilizationSettingsBank1::getMaximumRate(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.MaximumRate[index];
}
void StabilizationSettingsBank1::setMaximumRate(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.MaximumRate[index] != value;
   data.MaximumRate[index] = value;
   mutex->unlock();
   if (changed) emit MaximumRateChanged(index,value);
}

float StabilizationSettingsBank1::getMaximumRate_Roll() const
{
   QMutexLocker locker(mutex);
   return data.MaximumRate[0];
}
void StabilizationSettingsBank1::setMaximumRate_Roll(float value)
{
   mutex->lock();
   bool changed = data.MaximumRate[0] != value;
   data.MaximumRate[0] = value;
   mutex->unlock();
   if (changed) emit MaximumRate_RollChanged(value);
}

float StabilizationSettingsBank1::getMaximumRate_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.MaximumRate[1];
}
void StabilizationSettingsBank1::setMaximumRate_Pitch(float value)
{
   mutex->lock();
   bool changed = data.MaximumRate[1] != value;
   data.MaximumRate[1] = value;
   mutex->unlock();
   if (changed) emit MaximumRate_PitchChanged(value);
}

float StabilizationSettingsBank1::getMaximumRate_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.MaximumRate[2];
}
void StabilizationSettingsBank1::setMaximumRate_Yaw(float value)
{
   mutex->lock();
   bool changed = data.MaximumRate[2] != value;
   data.MaximumRate[2] = value;
   mutex->unlock();
   if (changed) emit MaximumRate_YawChanged(value);
}

float StabilizationSettingsBank1::getRollRatePID(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.RollRatePID[index];
}
void StabilizationSettingsBank1::setRollRatePID(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.RollRatePID[index] != value;
   data.RollRatePID[index] = value;
   mutex->unlock();
   if (changed) emit RollRatePIDChanged(index,value);
}

float StabilizationSettingsBank1::getRollRatePID_Kp() const
{
   QMutexLocker locker(mutex);
   return data.RollRatePID[0];
}
void StabilizationSettingsBank1::setRollRatePID_Kp(float value)
{
   mutex->lock();
   bool changed = data.RollRatePID[0] != value;
   data.RollRatePID[0] = value;
   mutex->unlock();
   if (changed) emit RollRatePID_KpChanged(value);
}

float StabilizationSettingsBank1::getRollRatePID_Ki() const
{
   QMutexLocker locker(mutex);
   return data.RollRatePID[1];
}
void StabilizationSettingsBank1::setRollRatePID_Ki(float value)
{
   mutex->lock();
   bool changed = data.RollRatePID[1] != value;
   data.RollRatePID[1] = value;
   mutex->unlock();
   if (changed) emit RollRatePID_KiChanged(value);
}

float StabilizationSettingsBank1::getRollRatePID_Kd() const
{
   QMutexLocker locker(mutex);
   return data.RollRatePID[2];
}
void StabilizationSettingsBank1::setRollRatePID_Kd(float value)
{
   mutex->lock();
   bool changed = data.RollRatePID[2] != value;
   data.RollRatePID[2] = value;
   mutex->unlock();
   if (changed) emit RollRatePID_KdChanged(value);
}

float StabilizationSettingsBank1::getRollRatePID_ILimit() const
{
   QMutexLocker locker(mutex);
   return data.RollRatePID[3];
}
void StabilizationSettingsBank1::setRollRatePID_ILimit(float value)
{
   mutex->lock();
   bool changed = data.RollRatePID[3] != value;
   data.RollRatePID[3] = value;
   mutex->unlock();
   if (changed) emit RollRatePID_ILimitChanged(value);
}

float StabilizationSettingsBank1::getPitchRatePID(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.PitchRatePID[index];
}
void StabilizationSettingsBank1::setPitchRatePID(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.PitchRatePID[index] != value;
   data.PitchRatePID[index] = value;
   mutex->unlock();
   if (changed) emit PitchRatePIDChanged(index,value);
}

float StabilizationSettingsBank1::getPitchRatePID_Kp() const
{
   QMutexLocker locker(mutex);
   return data.PitchRatePID[0];
}
void StabilizationSettingsBank1::setPitchRatePID_Kp(float value)
{
   mutex->lock();
   bool changed = data.PitchRatePID[0] != value;
   data.PitchRatePID[0] = value;
   mutex->unlock();
   if (changed) emit PitchRatePID_KpChanged(value);
}

float StabilizationSettingsBank1::getPitchRatePID_Ki() const
{
   QMutexLocker locker(mutex);
   return data.PitchRatePID[1];
}
void StabilizationSettingsBank1::setPitchRatePID_Ki(float value)
{
   mutex->lock();
   bool changed = data.PitchRatePID[1] != value;
   data.PitchRatePID[1] = value;
   mutex->unlock();
   if (changed) emit PitchRatePID_KiChanged(value);
}

float StabilizationSettingsBank1::getPitchRatePID_Kd() const
{
   QMutexLocker locker(mutex);
   return data.PitchRatePID[2];
}
void StabilizationSettingsBank1::setPitchRatePID_Kd(float value)
{
   mutex->lock();
   bool changed = data.PitchRatePID[2] != value;
   data.PitchRatePID[2] = value;
   mutex->unlock();
   if (changed) emit PitchRatePID_KdChanged(value);
}

float StabilizationSettingsBank1::getPitchRatePID_ILimit() const
{
   QMutexLocker locker(mutex);
   return data.PitchRatePID[3];
}
void StabilizationSettingsBank1::setPitchRatePID_ILimit(float value)
{
   mutex->lock();
   bool changed = data.PitchRatePID[3] != value;
   data.PitchRatePID[3] = value;
   mutex->unlock();
   if (changed) emit PitchRatePID_ILimitChanged(value);
}

float StabilizationSettingsBank1::getYawRatePID(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.YawRatePID[index];
}
void StabilizationSettingsBank1::setYawRatePID(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.YawRatePID[index] != value;
   data.YawRatePID[index] = value;
   mutex->unlock();
   if (changed) emit YawRatePIDChanged(index,value);
}

float StabilizationSettingsBank1::getYawRatePID_Kp() const
{
   QMutexLocker locker(mutex);
   return data.YawRatePID[0];
}
void StabilizationSettingsBank1::setYawRatePID_Kp(float value)
{
   mutex->lock();
   bool changed = data.YawRatePID[0] != value;
   data.YawRatePID[0] = value;
   mutex->unlock();
   if (changed) emit YawRatePID_KpChanged(value);
}

float StabilizationSettingsBank1::getYawRatePID_Ki() const
{
   QMutexLocker locker(mutex);
   return data.YawRatePID[1];
}
void StabilizationSettingsBank1::setYawRatePID_Ki(float value)
{
   mutex->lock();
   bool changed = data.YawRatePID[1] != value;
   data.YawRatePID[1] = value;
   mutex->unlock();
   if (changed) emit YawRatePID_KiChanged(value);
}

float StabilizationSettingsBank1::getYawRatePID_Kd() const
{
   QMutexLocker locker(mutex);
   return data.YawRatePID[2];
}
void StabilizationSettingsBank1::setYawRatePID_Kd(float value)
{
   mutex->lock();
   bool changed = data.YawRatePID[2] != value;
   data.YawRatePID[2] = value;
   mutex->unlock();
   if (changed) emit YawRatePID_KdChanged(value);
}

float StabilizationSettingsBank1::getYawRatePID_ILimit() const
{
   QMutexLocker locker(mutex);
   return data.YawRatePID[3];
}
void StabilizationSettingsBank1::setYawRatePID_ILimit(float value)
{
   mutex->lock();
   bool changed = data.YawRatePID[3] != value;
   data.YawRatePID[3] = value;
   mutex->unlock();
   if (changed) emit YawRatePID_ILimitChanged(value);
}

float StabilizationSettingsBank1::getRollPI(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.RollPI[index];
}
void StabilizationSettingsBank1::setRollPI(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.RollPI[index] != value;
   data.RollPI[index] = value;
   mutex->unlock();
   if (changed) emit RollPIChanged(index,value);
}

float StabilizationSettingsBank1::getRollPI_Kp() const
{
   QMutexLocker locker(mutex);
   return data.RollPI[0];
}
void StabilizationSettingsBank1::setRollPI_Kp(float value)
{
   mutex->lock();
   bool changed = data.RollPI[0] != value;
   data.RollPI[0] = value;
   mutex->unlock();
   if (changed) emit RollPI_KpChanged(value);
}

float StabilizationSettingsBank1::getRollPI_Ki() const
{
   QMutexLocker locker(mutex);
   return data.RollPI[1];
}
void StabilizationSettingsBank1::setRollPI_Ki(float value)
{
   mutex->lock();
   bool changed = data.RollPI[1] != value;
   data.RollPI[1] = value;
   mutex->unlock();
   if (changed) emit RollPI_KiChanged(value);
}

float StabilizationSettingsBank1::getRollPI_ILimit() const
{
   QMutexLocker locker(mutex);
   return data.RollPI[2];
}
void StabilizationSettingsBank1::setRollPI_ILimit(float value)
{
   mutex->lock();
   bool changed = data.RollPI[2] != value;
   data.RollPI[2] = value;
   mutex->unlock();
   if (changed) emit RollPI_ILimitChanged(value);
}

float StabilizationSettingsBank1::getPitchPI(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.PitchPI[index];
}
void StabilizationSettingsBank1::setPitchPI(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.PitchPI[index] != value;
   data.PitchPI[index] = value;
   mutex->unlock();
   if (changed) emit PitchPIChanged(index,value);
}

float StabilizationSettingsBank1::getPitchPI_Kp() const
{
   QMutexLocker locker(mutex);
   return data.PitchPI[0];
}
void StabilizationSettingsBank1::setPitchPI_Kp(float value)
{
   mutex->lock();
   bool changed = data.PitchPI[0] != value;
   data.PitchPI[0] = value;
   mutex->unlock();
   if (changed) emit PitchPI_KpChanged(value);
}

float StabilizationSettingsBank1::getPitchPI_Ki() const
{
   QMutexLocker locker(mutex);
   return data.PitchPI[1];
}
void StabilizationSettingsBank1::setPitchPI_Ki(float value)
{
   mutex->lock();
   bool changed = data.PitchPI[1] != value;
   data.PitchPI[1] = value;
   mutex->unlock();
   if (changed) emit PitchPI_KiChanged(value);
}

float StabilizationSettingsBank1::getPitchPI_ILimit() const
{
   QMutexLocker locker(mutex);
   return data.PitchPI[2];
}
void StabilizationSettingsBank1::setPitchPI_ILimit(float value)
{
   mutex->lock();
   bool changed = data.PitchPI[2] != value;
   data.PitchPI[2] = value;
   mutex->unlock();
   if (changed) emit PitchPI_ILimitChanged(value);
}

float StabilizationSettingsBank1::getYawPI(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.YawPI[index];
}
void StabilizationSettingsBank1::setYawPI(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.YawPI[index] != value;
   data.YawPI[index] = value;
   mutex->unlock();
   if (changed) emit YawPIChanged(index,value);
}

float StabilizationSettingsBank1::getYawPI_Kp() const
{
   QMutexLocker locker(mutex);
   return data.YawPI[0];
}
void StabilizationSettingsBank1::setYawPI_Kp(float value)
{
   mutex->lock();
   bool changed = data.YawPI[0] != value;
   data.YawPI[0] = value;
   mutex->unlock();
   if (changed) emit YawPI_KpChanged(value);
}

float StabilizationSettingsBank1::getYawPI_Ki() const
{
   QMutexLocker locker(mutex);
   return data.YawPI[1];
}
void StabilizationSettingsBank1::setYawPI_Ki(float value)
{
   mutex->lock();
   bool changed = data.YawPI[1] != value;
   data.YawPI[1] = value;
   mutex->unlock();
   if (changed) emit YawPI_KiChanged(value);
}

float StabilizationSettingsBank1::getYawPI_ILimit() const
{
   QMutexLocker locker(mutex);
   return data.YawPI[2];
}
void StabilizationSettingsBank1::setYawPI_ILimit(float value)
{
   mutex->lock();
   bool changed = data.YawPI[2] != value;
   data.YawPI[2] = value;
   mutex->unlock();
   if (changed) emit YawPI_ILimitChanged(value);
}

float StabilizationSettingsBank1::getAcroInsanityFactor() const
{
   QMutexLocker locker(mutex);
   return data.AcroInsanityFactor;
}
void StabilizationSettingsBank1::setAcroInsanityFactor(float value)
{
   mutex->lock();
   bool changed = data.AcroInsanityFactor != value;
   data.AcroInsanityFactor = value;
   mutex->unlock();
   if (changed) emit AcroInsanityFactorChanged(value);
}

float StabilizationSettingsBank1::getThrustPIDScaleCurve(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ThrustPIDScaleCurve[index];
}
void StabilizationSettingsBank1::setThrustPIDScaleCurve(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ThrustPIDScaleCurve[index] != value;
   data.ThrustPIDScaleCurve[index] = value;
   mutex->unlock();
   if (changed) emit ThrustPIDScaleCurveChanged(index,value);
}

float StabilizationSettingsBank1::getThrustPIDScaleCurve_0() const
{
   QMutexLocker locker(mutex);
   return data.ThrustPIDScaleCurve[0];
}
void StabilizationSettingsBank1::setThrustPIDScaleCurve_0(float value)
{
   mutex->lock();
   bool changed = data.ThrustPIDScaleCurve[0] != value;
   data.ThrustPIDScaleCurve[0] = value;
   mutex->unlock();
   if (changed) emit ThrustPIDScaleCurve_0Changed(value);
}

float StabilizationSettingsBank1::getThrustPIDScaleCurve_25() const
{
   QMutexLocker locker(mutex);
   return data.ThrustPIDScaleCurve[1];
}
void StabilizationSettingsBank1::setThrustPIDScaleCurve_25(float value)
{
   mutex->lock();
   bool changed = data.ThrustPIDScaleCurve[1] != value;
   data.ThrustPIDScaleCurve[1] = value;
   mutex->unlock();
   if (changed) emit ThrustPIDScaleCurve_25Changed(value);
}

float StabilizationSettingsBank1::getThrustPIDScaleCurve_50() const
{
   QMutexLocker locker(mutex);
   return data.ThrustPIDScaleCurve[2];
}
void StabilizationSettingsBank1::setThrustPIDScaleCurve_50(float value)
{
   mutex->lock();
   bool changed = data.ThrustPIDScaleCurve[2] != value;
   data.ThrustPIDScaleCurve[2] = value;
   mutex->unlock();
   if (changed) emit ThrustPIDScaleCurve_50Changed(value);
}

float StabilizationSettingsBank1::getThrustPIDScaleCurve_75() const
{
   QMutexLocker locker(mutex);
   return data.ThrustPIDScaleCurve[3];
}
void StabilizationSettingsBank1::setThrustPIDScaleCurve_75(float value)
{
   mutex->lock();
   bool changed = data.ThrustPIDScaleCurve[3] != value;
   data.ThrustPIDScaleCurve[3] = value;
   mutex->unlock();
   if (changed) emit ThrustPIDScaleCurve_75Changed(value);
}

float StabilizationSettingsBank1::getThrustPIDScaleCurve_100() const
{
   QMutexLocker locker(mutex);
   return data.ThrustPIDScaleCurve[4];
}
void StabilizationSettingsBank1::setThrustPIDScaleCurve_100(float value)
{
   mutex->lock();
   bool changed = data.ThrustPIDScaleCurve[4] != value;
   data.ThrustPIDScaleCurve[4] = value;
   mutex->unlock();
   if (changed) emit ThrustPIDScaleCurve_100Changed(value);
}

quint8 StabilizationSettingsBank1::getRollMax() const
{
   QMutexLocker locker(mutex);
   return data.RollMax;
}
void StabilizationSettingsBank1::setRollMax(quint8 value)
{
   mutex->lock();
   bool changed = data.RollMax != value;
   data.RollMax = value;
   mutex->unlock();
   if (changed) emit RollMaxChanged(value);
}

quint8 StabilizationSettingsBank1::getPitchMax() const
{
   QMutexLocker locker(mutex);
   return data.PitchMax;
}
void StabilizationSettingsBank1::setPitchMax(quint8 value)
{
   mutex->lock();
   bool changed = data.PitchMax != value;
   data.PitchMax = value;
   mutex->unlock();
   if (changed) emit PitchMaxChanged(value);
}

quint8 StabilizationSettingsBank1::getYawMax() const
{
   QMutexLocker locker(mutex);
   return data.YawMax;
}
void StabilizationSettingsBank1::setYawMax(quint8 value)
{
   mutex->lock();
   bool changed = data.YawMax != value;
   data.YawMax = value;
   mutex->unlock();
   if (changed) emit YawMaxChanged(value);
}

qint8 StabilizationSettingsBank1::getStickExpo(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.StickExpo[index];
}
void StabilizationSettingsBank1::setStickExpo(quint32 index, qint8 value)
{
   mutex->lock();
   bool changed = data.StickExpo[index] != value;
   data.StickExpo[index] = value;
   mutex->unlock();
   if (changed) emit StickExpoChanged(index,value);
}

qint8 StabilizationSettingsBank1::getStickExpo_Roll() const
{
   QMutexLocker locker(mutex);
   return data.StickExpo[0];
}
void StabilizationSettingsBank1::setStickExpo_Roll(qint8 value)
{
   mutex->lock();
   bool changed = data.StickExpo[0] != value;
   data.StickExpo[0] = value;
   mutex->unlock();
   if (changed) emit StickExpo_RollChanged(value);
}

qint8 StabilizationSettingsBank1::getStickExpo_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.StickExpo[1];
}
void StabilizationSettingsBank1::setStickExpo_Pitch(qint8 value)
{
   mutex->lock();
   bool changed = data.StickExpo[1] != value;
   data.StickExpo[1] = value;
   mutex->unlock();
   if (changed) emit StickExpo_PitchChanged(value);
}

qint8 StabilizationSettingsBank1::getStickExpo_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.StickExpo[2];
}
void StabilizationSettingsBank1::setStickExpo_Yaw(qint8 value)
{
   mutex->lock();
   bool changed = data.StickExpo[2] != value;
   data.StickExpo[2] = value;
   mutex->unlock();
   if (changed) emit StickExpo_YawChanged(value);
}

quint8 StabilizationSettingsBank1::getEnablePiroComp() const
{
   QMutexLocker locker(mutex);
   return data.EnablePiroComp;
}
void StabilizationSettingsBank1::setEnablePiroComp(quint8 value)
{
   mutex->lock();
   bool changed = data.EnablePiroComp != value;
   data.EnablePiroComp = value;
   mutex->unlock();
   if (changed) emit EnablePiroCompChanged(value);
}

quint8 StabilizationSettingsBank1::getEnableThrustPIDScaling() const
{
   QMutexLocker locker(mutex);
   return data.EnableThrustPIDScaling;
}
void StabilizationSettingsBank1::setEnableThrustPIDScaling(quint8 value)
{
   mutex->lock();
   bool changed = data.EnableThrustPIDScaling != value;
   data.EnableThrustPIDScaling = value;
   mutex->unlock();
   if (changed) emit EnableThrustPIDScalingChanged(value);
}

quint8 StabilizationSettingsBank1::getThrustPIDScaleSource() const
{
   QMutexLocker locker(mutex);
   return data.ThrustPIDScaleSource;
}
void StabilizationSettingsBank1::setThrustPIDScaleSource(quint8 value)
{
   mutex->lock();
   bool changed = data.ThrustPIDScaleSource != value;
   data.ThrustPIDScaleSource = value;
   mutex->unlock();
   if (changed) emit ThrustPIDScaleSourceChanged(value);
}

quint8 StabilizationSettingsBank1::getThrustPIDScaleTarget() const
{
   QMutexLocker locker(mutex);
   return data.ThrustPIDScaleTarget;
}
void StabilizationSettingsBank1::setThrustPIDScaleTarget(quint8 value)
{
   mutex->lock();
   bool changed = data.ThrustPIDScaleTarget != value;
   data.ThrustPIDScaleTarget = value;
   mutex->unlock();
   if (changed) emit ThrustPIDScaleTargetChanged(value);
}

quint8 StabilizationSettingsBank1::getThrustPIDScaleAxes() const
{
   QMutexLocker locker(mutex);
   return data.ThrustPIDScaleAxes;
}
void StabilizationSettingsBank1::setThrustPIDScaleAxes(quint8 value)
{
   mutex->lock();
   bool changed = data.ThrustPIDScaleAxes != value;
   data.ThrustPIDScaleAxes = value;
   mutex->unlock();
   if (changed) emit ThrustPIDScaleAxesChanged(value);
}


