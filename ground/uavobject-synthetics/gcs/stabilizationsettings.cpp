/**
 ******************************************************************************
 *
 * @file       stabilizationsettings.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: stabilizationsettings.xml.
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

#include "stabilizationsettings.h"
#include "uavobjectfield.h"

const QString StabilizationSettings::NAME = QString("StabilizationSettings");
const QString StabilizationSettings::DESCRIPTION = QString("PID settings used by the Stabilization module to combine the @ref AttitudeActual and @ref AttitudeDesired to compute @ref ActuatorDesired");
const QString StabilizationSettings::CATEGORY = QString("Control");

/**
 * Constructor
 */
StabilizationSettings::StabilizationSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList VbarSensitivityElemNames;
    VbarSensitivityElemNames.append("Roll");
    VbarSensitivityElemNames.append("Pitch");
    VbarSensitivityElemNames.append("Yaw");
    fields.append( new UAVObjectField(QString("VbarSensitivity"), tr(""), QString("frac"), UAVObjectField::FLOAT32, VbarSensitivityElemNames, QStringList(), QString("")));
    QStringList VbarRollPIElemNames;
    VbarRollPIElemNames.append("Kp");
    VbarRollPIElemNames.append("Ki");
    fields.append( new UAVObjectField(QString("VbarRollPI"), tr(""), QString("1/(deg/s)"), UAVObjectField::FLOAT32, VbarRollPIElemNames, QStringList(), QString("")));
    QStringList VbarPitchPIElemNames;
    VbarPitchPIElemNames.append("Kp");
    VbarPitchPIElemNames.append("Ki");
    fields.append( new UAVObjectField(QString("VbarPitchPI"), tr(""), QString("1/(deg/s)"), UAVObjectField::FLOAT32, VbarPitchPIElemNames, QStringList(), QString("")));
    QStringList VbarYawPIElemNames;
    VbarYawPIElemNames.append("Kp");
    VbarYawPIElemNames.append("Ki");
    fields.append( new UAVObjectField(QString("VbarYawPI"), tr(""), QString("1/(deg/s)"), UAVObjectField::FLOAT32, VbarYawPIElemNames, QStringList(), QString("")));
    QStringList VbarTauElemNames;
    VbarTauElemNames.append("0");
    fields.append( new UAVObjectField(QString("VbarTau"), tr(""), QString("sec"), UAVObjectField::FLOAT32, VbarTauElemNames, QStringList(), QString("")));
    QStringList GyroTauElemNames;
    GyroTauElemNames.append("0");
    fields.append( new UAVObjectField(QString("GyroTau"), tr(""), QString(""), UAVObjectField::FLOAT32, GyroTauElemNames, QStringList(), QString("")));
    QStringList DerivativeGammaElemNames;
    DerivativeGammaElemNames.append("0");
    fields.append( new UAVObjectField(QString("DerivativeGamma"), tr(""), QString(""), UAVObjectField::FLOAT32, DerivativeGammaElemNames, QStringList(), QString("")));
    QStringList AxisLockKpElemNames;
    AxisLockKpElemNames.append("0");
    fields.append( new UAVObjectField(QString("AxisLockKp"), tr(""), QString(""), UAVObjectField::FLOAT32, AxisLockKpElemNames, QStringList(), QString("")));
    QStringList WeakLevelingKpElemNames;
    WeakLevelingKpElemNames.append("0");
    fields.append( new UAVObjectField(QString("WeakLevelingKp"), tr(""), QString("(deg/s)/deg"), UAVObjectField::FLOAT32, WeakLevelingKpElemNames, QStringList(), QString("")));
    QStringList CruiseControlMaxPowerFactorElemNames;
    CruiseControlMaxPowerFactorElemNames.append("0");
    fields.append( new UAVObjectField(QString("CruiseControlMaxPowerFactor"), tr(""), QString("x"), UAVObjectField::FLOAT32, CruiseControlMaxPowerFactorElemNames, QStringList(), QString("")));
    QStringList CruiseControlPowerTrimElemNames;
    CruiseControlPowerTrimElemNames.append("0");
    fields.append( new UAVObjectField(QString("CruiseControlPowerTrim"), tr(""), QString("%"), UAVObjectField::FLOAT32, CruiseControlPowerTrimElemNames, QStringList(), QString("")));
    QStringList CruiseControlPowerDelayCompElemNames;
    CruiseControlPowerDelayCompElemNames.append("0");
    fields.append( new UAVObjectField(QString("CruiseControlPowerDelayComp"), tr(""), QString("sec"), UAVObjectField::FLOAT32, CruiseControlPowerDelayCompElemNames, QStringList(), QString("")));
    QStringList ScaleToAirspeedElemNames;
    ScaleToAirspeedElemNames.append("0");
    fields.append( new UAVObjectField(QString("ScaleToAirspeed"), tr(""), QString("m/s"), UAVObjectField::FLOAT32, ScaleToAirspeedElemNames, QStringList(), QString("")));
    QStringList ScaleToAirspeedLimitsElemNames;
    ScaleToAirspeedLimitsElemNames.append("Min");
    ScaleToAirspeedLimitsElemNames.append("Max");
    fields.append( new UAVObjectField(QString("ScaleToAirspeedLimits"), tr(""), QString(""), UAVObjectField::FLOAT32, ScaleToAirspeedLimitsElemNames, QStringList(), QString("")));
    QStringList FlightModeMapElemNames;
    FlightModeMapElemNames.append("0");
    FlightModeMapElemNames.append("1");
    FlightModeMapElemNames.append("2");
    FlightModeMapElemNames.append("3");
    FlightModeMapElemNames.append("4");
    FlightModeMapElemNames.append("5");
    QStringList FlightModeMapEnumOptions;
    FlightModeMapEnumOptions.append("Bank1");
    FlightModeMapEnumOptions.append("Bank2");
    FlightModeMapEnumOptions.append("Bank3");
    fields.append( new UAVObjectField(QString("FlightModeMap"), tr(""), QString(""), UAVObjectField::ENUM, FlightModeMapElemNames, FlightModeMapEnumOptions, QString("")));
    QStringList VbarGyroSuppressElemNames;
    VbarGyroSuppressElemNames.append("0");
    fields.append( new UAVObjectField(QString("VbarGyroSuppress"), tr(""), QString("%"), UAVObjectField::INT8, VbarGyroSuppressElemNames, QStringList(), QString("")));
    QStringList VbarPiroCompElemNames;
    VbarPiroCompElemNames.append("0");
    QStringList VbarPiroCompEnumOptions;
    VbarPiroCompEnumOptions.append("FALSE");
    VbarPiroCompEnumOptions.append("TRUE");
    fields.append( new UAVObjectField(QString("VbarPiroComp"), tr(""), QString(""), UAVObjectField::ENUM, VbarPiroCompElemNames, VbarPiroCompEnumOptions, QString("")));
    QStringList VbarMaxAngleElemNames;
    VbarMaxAngleElemNames.append("0");
    fields.append( new UAVObjectField(QString("VbarMaxAngle"), tr(""), QString("deg"), UAVObjectField::UINT8, VbarMaxAngleElemNames, QStringList(), QString("")));
    QStringList DerivativeCutoffElemNames;
    DerivativeCutoffElemNames.append("0");
    fields.append( new UAVObjectField(QString("DerivativeCutoff"), tr(""), QString("Hz"), UAVObjectField::UINT8, DerivativeCutoffElemNames, QStringList(), QString("")));
    QStringList MaxAxisLockElemNames;
    MaxAxisLockElemNames.append("0");
    fields.append( new UAVObjectField(QString("MaxAxisLock"), tr(""), QString("deg"), UAVObjectField::UINT8, MaxAxisLockElemNames, QStringList(), QString("")));
    QStringList MaxAxisLockRateElemNames;
    MaxAxisLockRateElemNames.append("0");
    fields.append( new UAVObjectField(QString("MaxAxisLockRate"), tr(""), QString("deg/s"), UAVObjectField::UINT8, MaxAxisLockRateElemNames, QStringList(), QString("")));
    QStringList MaxWeakLevelingRateElemNames;
    MaxWeakLevelingRateElemNames.append("0");
    fields.append( new UAVObjectField(QString("MaxWeakLevelingRate"), tr(""), QString("deg/s"), UAVObjectField::UINT8, MaxWeakLevelingRateElemNames, QStringList(), QString("")));
    QStringList RattitudeModeTransitionElemNames;
    RattitudeModeTransitionElemNames.append("0");
    fields.append( new UAVObjectField(QString("RattitudeModeTransition"), tr(""), QString("%"), UAVObjectField::UINT8, RattitudeModeTransitionElemNames, QStringList(), QString("")));
    QStringList CruiseControlMinThrustElemNames;
    CruiseControlMinThrustElemNames.append("0");
    fields.append( new UAVObjectField(QString("CruiseControlMinThrust"), tr(""), QString("%"), UAVObjectField::INT8, CruiseControlMinThrustElemNames, QStringList(), QString("")));
    QStringList CruiseControlMaxThrustElemNames;
    CruiseControlMaxThrustElemNames.append("0");
    fields.append( new UAVObjectField(QString("CruiseControlMaxThrust"), tr(""), QString("%"), UAVObjectField::UINT8, CruiseControlMaxThrustElemNames, QStringList(), QString("")));
    QStringList CruiseControlMaxAngleElemNames;
    CruiseControlMaxAngleElemNames.append("0");
    fields.append( new UAVObjectField(QString("CruiseControlMaxAngle"), tr(""), QString("deg"), UAVObjectField::UINT8, CruiseControlMaxAngleElemNames, QStringList(), QString("")));
    QStringList CruiseControlFlightModeSwitchPosEnableElemNames;
    CruiseControlFlightModeSwitchPosEnableElemNames.append("0");
    CruiseControlFlightModeSwitchPosEnableElemNames.append("1");
    CruiseControlFlightModeSwitchPosEnableElemNames.append("2");
    CruiseControlFlightModeSwitchPosEnableElemNames.append("3");
    CruiseControlFlightModeSwitchPosEnableElemNames.append("4");
    CruiseControlFlightModeSwitchPosEnableElemNames.append("5");
    QStringList CruiseControlFlightModeSwitchPosEnableEnumOptions;
    CruiseControlFlightModeSwitchPosEnableEnumOptions.append("FALSE");
    CruiseControlFlightModeSwitchPosEnableEnumOptions.append("TRUE");
    fields.append( new UAVObjectField(QString("CruiseControlFlightModeSwitchPosEnable"), tr(""), QString(""), UAVObjectField::ENUM, CruiseControlFlightModeSwitchPosEnableElemNames, CruiseControlFlightModeSwitchPosEnableEnumOptions, QString("")));
    QStringList CruiseControlInvertedThrustReversingElemNames;
    CruiseControlInvertedThrustReversingElemNames.append("0");
    QStringList CruiseControlInvertedThrustReversingEnumOptions;
    CruiseControlInvertedThrustReversingEnumOptions.append("Unreversed");
    CruiseControlInvertedThrustReversingEnumOptions.append("Reversed");
    fields.append( new UAVObjectField(QString("CruiseControlInvertedThrustReversing"), tr(""), QString(""), UAVObjectField::ENUM, CruiseControlInvertedThrustReversingElemNames, CruiseControlInvertedThrustReversingEnumOptions, QString("")));
    QStringList CruiseControlInvertedPowerOutputElemNames;
    CruiseControlInvertedPowerOutputElemNames.append("0");
    QStringList CruiseControlInvertedPowerOutputEnumOptions;
    CruiseControlInvertedPowerOutputEnumOptions.append("Zero");
    CruiseControlInvertedPowerOutputEnumOptions.append("Normal");
    CruiseControlInvertedPowerOutputEnumOptions.append("Boosted");
    fields.append( new UAVObjectField(QString("CruiseControlInvertedPowerOutput"), tr(""), QString(""), UAVObjectField::ENUM, CruiseControlInvertedPowerOutputElemNames, CruiseControlInvertedPowerOutputEnumOptions, QString("")));
    QStringList LowThrottleZeroIntegralElemNames;
    LowThrottleZeroIntegralElemNames.append("0");
    QStringList LowThrottleZeroIntegralEnumOptions;
    LowThrottleZeroIntegralEnumOptions.append("FALSE");
    LowThrottleZeroIntegralEnumOptions.append("TRUE");
    fields.append( new UAVObjectField(QString("LowThrottleZeroIntegral"), tr(""), QString(""), UAVObjectField::ENUM, LowThrottleZeroIntegralElemNames, LowThrottleZeroIntegralEnumOptions, QString("")));
    QStringList FlightModeAssistMapElemNames;
    FlightModeAssistMapElemNames.append("0");
    FlightModeAssistMapElemNames.append("1");
    FlightModeAssistMapElemNames.append("2");
    FlightModeAssistMapElemNames.append("3");
    FlightModeAssistMapElemNames.append("4");
    FlightModeAssistMapElemNames.append("5");
    QStringList FlightModeAssistMapEnumOptions;
    FlightModeAssistMapEnumOptions.append("None");
    FlightModeAssistMapEnumOptions.append("GPSAssist");
    fields.append( new UAVObjectField(QString("FlightModeAssistMap"), tr(""), QString(""), UAVObjectField::ENUM, FlightModeAssistMapElemNames, FlightModeAssistMapEnumOptions, QString("\
                %0401NE:GPSAssist,\
                %0402NE:GPSAssist;\
                \
                %0401NE:GPSAssist,\
                %0402NE:GPSAssist;\
                \
                %0401NE:GPSAssist,\
                %0402NE:GPSAssist;\
                \
                %0401NE:GPSAssist,\
                %0402NE:GPSAssist;\
                \
                %0401NE:GPSAssist,\
                %0402NE:GPSAssist;\
                \
                %0401NE:GPSAssist,\
                %0402NE:GPSAssist;")));

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
UAVObject::Metadata StabilizationSettings::getDefaultMetadata()
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
void StabilizationSettings::setDefaultFieldValues()
{
    data.VbarSensitivity[0] = 0.5;
    data.VbarSensitivity[1] = 0.5;
    data.VbarSensitivity[2] = 0.5;
    data.VbarRollPI[0] = 0.005;
    data.VbarRollPI[1] = 0.002;
    data.VbarPitchPI[0] = 0.005;
    data.VbarPitchPI[1] = 0.002;
    data.VbarYawPI[0] = 0.005;
    data.VbarYawPI[1] = 0.002;
    data.VbarTau = 0.5;
    data.GyroTau = 0.005;
    data.DerivativeGamma = 1;
    data.AxisLockKp = 2.5;
    data.WeakLevelingKp = 0.1;
    data.CruiseControlMaxPowerFactor = 3;
    data.CruiseControlPowerTrim = 100;
    data.CruiseControlPowerDelayComp = 0.25;
    data.ScaleToAirspeed = 0;
    data.ScaleToAirspeedLimits[0] = 0.05;
    data.ScaleToAirspeedLimits[1] = 3;
    data.FlightModeMap[0] = 0;
    data.FlightModeMap[1] = 0;
    data.FlightModeMap[2] = 0;
    data.FlightModeMap[3] = 0;
    data.FlightModeMap[4] = 0;
    data.FlightModeMap[5] = 0;
    data.VbarGyroSuppress = 30;
    data.VbarPiroComp = 0;
    data.VbarMaxAngle = 10;
    data.DerivativeCutoff = 20;
    data.MaxAxisLock = 30;
    data.MaxAxisLockRate = 2;
    data.MaxWeakLevelingRate = 5;
    data.RattitudeModeTransition = 80;
    data.CruiseControlMinThrust = 5;
    data.CruiseControlMaxThrust = 90;
    data.CruiseControlMaxAngle = 105;
    data.CruiseControlFlightModeSwitchPosEnable[0] = 0;
    data.CruiseControlFlightModeSwitchPosEnable[1] = 0;
    data.CruiseControlFlightModeSwitchPosEnable[2] = 0;
    data.CruiseControlFlightModeSwitchPosEnable[3] = 0;
    data.CruiseControlFlightModeSwitchPosEnable[4] = 0;
    data.CruiseControlFlightModeSwitchPosEnable[5] = 0;
    data.CruiseControlInvertedThrustReversing = 0;
    data.CruiseControlInvertedPowerOutput = 0;
    data.LowThrottleZeroIntegral = 1;
    data.FlightModeAssistMap[0] = 0;
    data.FlightModeAssistMap[1] = 0;
    data.FlightModeAssistMap[2] = 0;
    data.FlightModeAssistMap[3] = 0;
    data.FlightModeAssistMap[4] = 0;
    data.FlightModeAssistMap[5] = 0;

}

/**
 * Get the object data fields
 */
StabilizationSettings::DataFields StabilizationSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void StabilizationSettings::setData(const DataFields& data)
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

void StabilizationSettings::emitNotifications()
{
            //if (data.VbarSensitivity[0] != oldData.VbarSensitivity[0])
            emit VbarSensitivity_RollChanged(data.VbarSensitivity[0]);
        //if (data.VbarSensitivity[1] != oldData.VbarSensitivity[1])
            emit VbarSensitivity_PitchChanged(data.VbarSensitivity[1]);
        //if (data.VbarSensitivity[2] != oldData.VbarSensitivity[2])
            emit VbarSensitivity_YawChanged(data.VbarSensitivity[2]);
        //if (data.VbarRollPI[0] != oldData.VbarRollPI[0])
            emit VbarRollPI_KpChanged(data.VbarRollPI[0]);
        //if (data.VbarRollPI[1] != oldData.VbarRollPI[1])
            emit VbarRollPI_KiChanged(data.VbarRollPI[1]);
        //if (data.VbarPitchPI[0] != oldData.VbarPitchPI[0])
            emit VbarPitchPI_KpChanged(data.VbarPitchPI[0]);
        //if (data.VbarPitchPI[1] != oldData.VbarPitchPI[1])
            emit VbarPitchPI_KiChanged(data.VbarPitchPI[1]);
        //if (data.VbarYawPI[0] != oldData.VbarYawPI[0])
            emit VbarYawPI_KpChanged(data.VbarYawPI[0]);
        //if (data.VbarYawPI[1] != oldData.VbarYawPI[1])
            emit VbarYawPI_KiChanged(data.VbarYawPI[1]);
        //if (data.VbarTau != oldData.VbarTau)
            emit VbarTauChanged(data.VbarTau);
        //if (data.GyroTau != oldData.GyroTau)
            emit GyroTauChanged(data.GyroTau);
        //if (data.DerivativeGamma != oldData.DerivativeGamma)
            emit DerivativeGammaChanged(data.DerivativeGamma);
        //if (data.AxisLockKp != oldData.AxisLockKp)
            emit AxisLockKpChanged(data.AxisLockKp);
        //if (data.WeakLevelingKp != oldData.WeakLevelingKp)
            emit WeakLevelingKpChanged(data.WeakLevelingKp);
        //if (data.CruiseControlMaxPowerFactor != oldData.CruiseControlMaxPowerFactor)
            emit CruiseControlMaxPowerFactorChanged(data.CruiseControlMaxPowerFactor);
        //if (data.CruiseControlPowerTrim != oldData.CruiseControlPowerTrim)
            emit CruiseControlPowerTrimChanged(data.CruiseControlPowerTrim);
        //if (data.CruiseControlPowerDelayComp != oldData.CruiseControlPowerDelayComp)
            emit CruiseControlPowerDelayCompChanged(data.CruiseControlPowerDelayComp);
        //if (data.ScaleToAirspeed != oldData.ScaleToAirspeed)
            emit ScaleToAirspeedChanged(data.ScaleToAirspeed);
        //if (data.ScaleToAirspeedLimits[0] != oldData.ScaleToAirspeedLimits[0])
            emit ScaleToAirspeedLimits_MinChanged(data.ScaleToAirspeedLimits[0]);
        //if (data.ScaleToAirspeedLimits[1] != oldData.ScaleToAirspeedLimits[1])
            emit ScaleToAirspeedLimits_MaxChanged(data.ScaleToAirspeedLimits[1]);
        //if (data.FlightModeMap[0] != oldData.FlightModeMap[0])
            emit FlightModeMap_0Changed(data.FlightModeMap[0]);
        //if (data.FlightModeMap[1] != oldData.FlightModeMap[1])
            emit FlightModeMap_1Changed(data.FlightModeMap[1]);
        //if (data.FlightModeMap[2] != oldData.FlightModeMap[2])
            emit FlightModeMap_2Changed(data.FlightModeMap[2]);
        //if (data.FlightModeMap[3] != oldData.FlightModeMap[3])
            emit FlightModeMap_3Changed(data.FlightModeMap[3]);
        //if (data.FlightModeMap[4] != oldData.FlightModeMap[4])
            emit FlightModeMap_4Changed(data.FlightModeMap[4]);
        //if (data.FlightModeMap[5] != oldData.FlightModeMap[5])
            emit FlightModeMap_5Changed(data.FlightModeMap[5]);
        //if (data.VbarGyroSuppress != oldData.VbarGyroSuppress)
            emit VbarGyroSuppressChanged(data.VbarGyroSuppress);
        //if (data.VbarPiroComp != oldData.VbarPiroComp)
            emit VbarPiroCompChanged(data.VbarPiroComp);
        //if (data.VbarMaxAngle != oldData.VbarMaxAngle)
            emit VbarMaxAngleChanged(data.VbarMaxAngle);
        //if (data.DerivativeCutoff != oldData.DerivativeCutoff)
            emit DerivativeCutoffChanged(data.DerivativeCutoff);
        //if (data.MaxAxisLock != oldData.MaxAxisLock)
            emit MaxAxisLockChanged(data.MaxAxisLock);
        //if (data.MaxAxisLockRate != oldData.MaxAxisLockRate)
            emit MaxAxisLockRateChanged(data.MaxAxisLockRate);
        //if (data.MaxWeakLevelingRate != oldData.MaxWeakLevelingRate)
            emit MaxWeakLevelingRateChanged(data.MaxWeakLevelingRate);
        //if (data.RattitudeModeTransition != oldData.RattitudeModeTransition)
            emit RattitudeModeTransitionChanged(data.RattitudeModeTransition);
        //if (data.CruiseControlMinThrust != oldData.CruiseControlMinThrust)
            emit CruiseControlMinThrustChanged(data.CruiseControlMinThrust);
        //if (data.CruiseControlMaxThrust != oldData.CruiseControlMaxThrust)
            emit CruiseControlMaxThrustChanged(data.CruiseControlMaxThrust);
        //if (data.CruiseControlMaxAngle != oldData.CruiseControlMaxAngle)
            emit CruiseControlMaxAngleChanged(data.CruiseControlMaxAngle);
        //if (data.CruiseControlFlightModeSwitchPosEnable[0] != oldData.CruiseControlFlightModeSwitchPosEnable[0])
            emit CruiseControlFlightModeSwitchPosEnable_0Changed(data.CruiseControlFlightModeSwitchPosEnable[0]);
        //if (data.CruiseControlFlightModeSwitchPosEnable[1] != oldData.CruiseControlFlightModeSwitchPosEnable[1])
            emit CruiseControlFlightModeSwitchPosEnable_1Changed(data.CruiseControlFlightModeSwitchPosEnable[1]);
        //if (data.CruiseControlFlightModeSwitchPosEnable[2] != oldData.CruiseControlFlightModeSwitchPosEnable[2])
            emit CruiseControlFlightModeSwitchPosEnable_2Changed(data.CruiseControlFlightModeSwitchPosEnable[2]);
        //if (data.CruiseControlFlightModeSwitchPosEnable[3] != oldData.CruiseControlFlightModeSwitchPosEnable[3])
            emit CruiseControlFlightModeSwitchPosEnable_3Changed(data.CruiseControlFlightModeSwitchPosEnable[3]);
        //if (data.CruiseControlFlightModeSwitchPosEnable[4] != oldData.CruiseControlFlightModeSwitchPosEnable[4])
            emit CruiseControlFlightModeSwitchPosEnable_4Changed(data.CruiseControlFlightModeSwitchPosEnable[4]);
        //if (data.CruiseControlFlightModeSwitchPosEnable[5] != oldData.CruiseControlFlightModeSwitchPosEnable[5])
            emit CruiseControlFlightModeSwitchPosEnable_5Changed(data.CruiseControlFlightModeSwitchPosEnable[5]);
        //if (data.CruiseControlInvertedThrustReversing != oldData.CruiseControlInvertedThrustReversing)
            emit CruiseControlInvertedThrustReversingChanged(data.CruiseControlInvertedThrustReversing);
        //if (data.CruiseControlInvertedPowerOutput != oldData.CruiseControlInvertedPowerOutput)
            emit CruiseControlInvertedPowerOutputChanged(data.CruiseControlInvertedPowerOutput);
        //if (data.LowThrottleZeroIntegral != oldData.LowThrottleZeroIntegral)
            emit LowThrottleZeroIntegralChanged(data.LowThrottleZeroIntegral);
        //if (data.FlightModeAssistMap[0] != oldData.FlightModeAssistMap[0])
            emit FlightModeAssistMap_0Changed(data.FlightModeAssistMap[0]);
        //if (data.FlightModeAssistMap[1] != oldData.FlightModeAssistMap[1])
            emit FlightModeAssistMap_1Changed(data.FlightModeAssistMap[1]);
        //if (data.FlightModeAssistMap[2] != oldData.FlightModeAssistMap[2])
            emit FlightModeAssistMap_2Changed(data.FlightModeAssistMap[2]);
        //if (data.FlightModeAssistMap[3] != oldData.FlightModeAssistMap[3])
            emit FlightModeAssistMap_3Changed(data.FlightModeAssistMap[3]);
        //if (data.FlightModeAssistMap[4] != oldData.FlightModeAssistMap[4])
            emit FlightModeAssistMap_4Changed(data.FlightModeAssistMap[4]);
        //if (data.FlightModeAssistMap[5] != oldData.FlightModeAssistMap[5])
            emit FlightModeAssistMap_5Changed(data.FlightModeAssistMap[5]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *StabilizationSettings::clone(quint32 instID)
{
    StabilizationSettings *obj = new StabilizationSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *StabilizationSettings::dirtyClone()
{
    StabilizationSettings *obj = new StabilizationSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
StabilizationSettings *StabilizationSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<StabilizationSettings *>(objMngr->getObject(StabilizationSettings::OBJID, instID));
}

float StabilizationSettings::getVbarSensitivity(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.VbarSensitivity[index];
}
void StabilizationSettings::setVbarSensitivity(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.VbarSensitivity[index] != value;
   data.VbarSensitivity[index] = value;
   mutex->unlock();
   if (changed) emit VbarSensitivityChanged(index,value);
}

float StabilizationSettings::getVbarSensitivity_Roll() const
{
   QMutexLocker locker(mutex);
   return data.VbarSensitivity[0];
}
void StabilizationSettings::setVbarSensitivity_Roll(float value)
{
   mutex->lock();
   bool changed = data.VbarSensitivity[0] != value;
   data.VbarSensitivity[0] = value;
   mutex->unlock();
   if (changed) emit VbarSensitivity_RollChanged(value);
}

float StabilizationSettings::getVbarSensitivity_Pitch() const
{
   QMutexLocker locker(mutex);
   return data.VbarSensitivity[1];
}
void StabilizationSettings::setVbarSensitivity_Pitch(float value)
{
   mutex->lock();
   bool changed = data.VbarSensitivity[1] != value;
   data.VbarSensitivity[1] = value;
   mutex->unlock();
   if (changed) emit VbarSensitivity_PitchChanged(value);
}

float StabilizationSettings::getVbarSensitivity_Yaw() const
{
   QMutexLocker locker(mutex);
   return data.VbarSensitivity[2];
}
void StabilizationSettings::setVbarSensitivity_Yaw(float value)
{
   mutex->lock();
   bool changed = data.VbarSensitivity[2] != value;
   data.VbarSensitivity[2] = value;
   mutex->unlock();
   if (changed) emit VbarSensitivity_YawChanged(value);
}

float StabilizationSettings::getVbarRollPI(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.VbarRollPI[index];
}
void StabilizationSettings::setVbarRollPI(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.VbarRollPI[index] != value;
   data.VbarRollPI[index] = value;
   mutex->unlock();
   if (changed) emit VbarRollPIChanged(index,value);
}

float StabilizationSettings::getVbarRollPI_Kp() const
{
   QMutexLocker locker(mutex);
   return data.VbarRollPI[0];
}
void StabilizationSettings::setVbarRollPI_Kp(float value)
{
   mutex->lock();
   bool changed = data.VbarRollPI[0] != value;
   data.VbarRollPI[0] = value;
   mutex->unlock();
   if (changed) emit VbarRollPI_KpChanged(value);
}

float StabilizationSettings::getVbarRollPI_Ki() const
{
   QMutexLocker locker(mutex);
   return data.VbarRollPI[1];
}
void StabilizationSettings::setVbarRollPI_Ki(float value)
{
   mutex->lock();
   bool changed = data.VbarRollPI[1] != value;
   data.VbarRollPI[1] = value;
   mutex->unlock();
   if (changed) emit VbarRollPI_KiChanged(value);
}

float StabilizationSettings::getVbarPitchPI(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.VbarPitchPI[index];
}
void StabilizationSettings::setVbarPitchPI(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.VbarPitchPI[index] != value;
   data.VbarPitchPI[index] = value;
   mutex->unlock();
   if (changed) emit VbarPitchPIChanged(index,value);
}

float StabilizationSettings::getVbarPitchPI_Kp() const
{
   QMutexLocker locker(mutex);
   return data.VbarPitchPI[0];
}
void StabilizationSettings::setVbarPitchPI_Kp(float value)
{
   mutex->lock();
   bool changed = data.VbarPitchPI[0] != value;
   data.VbarPitchPI[0] = value;
   mutex->unlock();
   if (changed) emit VbarPitchPI_KpChanged(value);
}

float StabilizationSettings::getVbarPitchPI_Ki() const
{
   QMutexLocker locker(mutex);
   return data.VbarPitchPI[1];
}
void StabilizationSettings::setVbarPitchPI_Ki(float value)
{
   mutex->lock();
   bool changed = data.VbarPitchPI[1] != value;
   data.VbarPitchPI[1] = value;
   mutex->unlock();
   if (changed) emit VbarPitchPI_KiChanged(value);
}

float StabilizationSettings::getVbarYawPI(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.VbarYawPI[index];
}
void StabilizationSettings::setVbarYawPI(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.VbarYawPI[index] != value;
   data.VbarYawPI[index] = value;
   mutex->unlock();
   if (changed) emit VbarYawPIChanged(index,value);
}

float StabilizationSettings::getVbarYawPI_Kp() const
{
   QMutexLocker locker(mutex);
   return data.VbarYawPI[0];
}
void StabilizationSettings::setVbarYawPI_Kp(float value)
{
   mutex->lock();
   bool changed = data.VbarYawPI[0] != value;
   data.VbarYawPI[0] = value;
   mutex->unlock();
   if (changed) emit VbarYawPI_KpChanged(value);
}

float StabilizationSettings::getVbarYawPI_Ki() const
{
   QMutexLocker locker(mutex);
   return data.VbarYawPI[1];
}
void StabilizationSettings::setVbarYawPI_Ki(float value)
{
   mutex->lock();
   bool changed = data.VbarYawPI[1] != value;
   data.VbarYawPI[1] = value;
   mutex->unlock();
   if (changed) emit VbarYawPI_KiChanged(value);
}

float StabilizationSettings::getVbarTau() const
{
   QMutexLocker locker(mutex);
   return data.VbarTau;
}
void StabilizationSettings::setVbarTau(float value)
{
   mutex->lock();
   bool changed = data.VbarTau != value;
   data.VbarTau = value;
   mutex->unlock();
   if (changed) emit VbarTauChanged(value);
}

float StabilizationSettings::getGyroTau() const
{
   QMutexLocker locker(mutex);
   return data.GyroTau;
}
void StabilizationSettings::setGyroTau(float value)
{
   mutex->lock();
   bool changed = data.GyroTau != value;
   data.GyroTau = value;
   mutex->unlock();
   if (changed) emit GyroTauChanged(value);
}

float StabilizationSettings::getDerivativeGamma() const
{
   QMutexLocker locker(mutex);
   return data.DerivativeGamma;
}
void StabilizationSettings::setDerivativeGamma(float value)
{
   mutex->lock();
   bool changed = data.DerivativeGamma != value;
   data.DerivativeGamma = value;
   mutex->unlock();
   if (changed) emit DerivativeGammaChanged(value);
}

float StabilizationSettings::getAxisLockKp() const
{
   QMutexLocker locker(mutex);
   return data.AxisLockKp;
}
void StabilizationSettings::setAxisLockKp(float value)
{
   mutex->lock();
   bool changed = data.AxisLockKp != value;
   data.AxisLockKp = value;
   mutex->unlock();
   if (changed) emit AxisLockKpChanged(value);
}

float StabilizationSettings::getWeakLevelingKp() const
{
   QMutexLocker locker(mutex);
   return data.WeakLevelingKp;
}
void StabilizationSettings::setWeakLevelingKp(float value)
{
   mutex->lock();
   bool changed = data.WeakLevelingKp != value;
   data.WeakLevelingKp = value;
   mutex->unlock();
   if (changed) emit WeakLevelingKpChanged(value);
}

float StabilizationSettings::getCruiseControlMaxPowerFactor() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlMaxPowerFactor;
}
void StabilizationSettings::setCruiseControlMaxPowerFactor(float value)
{
   mutex->lock();
   bool changed = data.CruiseControlMaxPowerFactor != value;
   data.CruiseControlMaxPowerFactor = value;
   mutex->unlock();
   if (changed) emit CruiseControlMaxPowerFactorChanged(value);
}

float StabilizationSettings::getCruiseControlPowerTrim() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlPowerTrim;
}
void StabilizationSettings::setCruiseControlPowerTrim(float value)
{
   mutex->lock();
   bool changed = data.CruiseControlPowerTrim != value;
   data.CruiseControlPowerTrim = value;
   mutex->unlock();
   if (changed) emit CruiseControlPowerTrimChanged(value);
}

float StabilizationSettings::getCruiseControlPowerDelayComp() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlPowerDelayComp;
}
void StabilizationSettings::setCruiseControlPowerDelayComp(float value)
{
   mutex->lock();
   bool changed = data.CruiseControlPowerDelayComp != value;
   data.CruiseControlPowerDelayComp = value;
   mutex->unlock();
   if (changed) emit CruiseControlPowerDelayCompChanged(value);
}

float StabilizationSettings::getScaleToAirspeed() const
{
   QMutexLocker locker(mutex);
   return data.ScaleToAirspeed;
}
void StabilizationSettings::setScaleToAirspeed(float value)
{
   mutex->lock();
   bool changed = data.ScaleToAirspeed != value;
   data.ScaleToAirspeed = value;
   mutex->unlock();
   if (changed) emit ScaleToAirspeedChanged(value);
}

float StabilizationSettings::getScaleToAirspeedLimits(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ScaleToAirspeedLimits[index];
}
void StabilizationSettings::setScaleToAirspeedLimits(quint32 index, float value)
{
   mutex->lock();
   bool changed = data.ScaleToAirspeedLimits[index] != value;
   data.ScaleToAirspeedLimits[index] = value;
   mutex->unlock();
   if (changed) emit ScaleToAirspeedLimitsChanged(index,value);
}

float StabilizationSettings::getScaleToAirspeedLimits_Min() const
{
   QMutexLocker locker(mutex);
   return data.ScaleToAirspeedLimits[0];
}
void StabilizationSettings::setScaleToAirspeedLimits_Min(float value)
{
   mutex->lock();
   bool changed = data.ScaleToAirspeedLimits[0] != value;
   data.ScaleToAirspeedLimits[0] = value;
   mutex->unlock();
   if (changed) emit ScaleToAirspeedLimits_MinChanged(value);
}

float StabilizationSettings::getScaleToAirspeedLimits_Max() const
{
   QMutexLocker locker(mutex);
   return data.ScaleToAirspeedLimits[1];
}
void StabilizationSettings::setScaleToAirspeedLimits_Max(float value)
{
   mutex->lock();
   bool changed = data.ScaleToAirspeedLimits[1] != value;
   data.ScaleToAirspeedLimits[1] = value;
   mutex->unlock();
   if (changed) emit ScaleToAirspeedLimits_MaxChanged(value);
}

quint8 StabilizationSettings::getFlightModeMap(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.FlightModeMap[index];
}
void StabilizationSettings::setFlightModeMap(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeMap[index] != value;
   data.FlightModeMap[index] = value;
   mutex->unlock();
   if (changed) emit FlightModeMapChanged(index,value);
}

quint8 StabilizationSettings::getFlightModeMap_0() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeMap[0];
}
void StabilizationSettings::setFlightModeMap_0(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeMap[0] != value;
   data.FlightModeMap[0] = value;
   mutex->unlock();
   if (changed) emit FlightModeMap_0Changed(value);
}

quint8 StabilizationSettings::getFlightModeMap_1() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeMap[1];
}
void StabilizationSettings::setFlightModeMap_1(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeMap[1] != value;
   data.FlightModeMap[1] = value;
   mutex->unlock();
   if (changed) emit FlightModeMap_1Changed(value);
}

quint8 StabilizationSettings::getFlightModeMap_2() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeMap[2];
}
void StabilizationSettings::setFlightModeMap_2(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeMap[2] != value;
   data.FlightModeMap[2] = value;
   mutex->unlock();
   if (changed) emit FlightModeMap_2Changed(value);
}

quint8 StabilizationSettings::getFlightModeMap_3() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeMap[3];
}
void StabilizationSettings::setFlightModeMap_3(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeMap[3] != value;
   data.FlightModeMap[3] = value;
   mutex->unlock();
   if (changed) emit FlightModeMap_3Changed(value);
}

quint8 StabilizationSettings::getFlightModeMap_4() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeMap[4];
}
void StabilizationSettings::setFlightModeMap_4(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeMap[4] != value;
   data.FlightModeMap[4] = value;
   mutex->unlock();
   if (changed) emit FlightModeMap_4Changed(value);
}

quint8 StabilizationSettings::getFlightModeMap_5() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeMap[5];
}
void StabilizationSettings::setFlightModeMap_5(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeMap[5] != value;
   data.FlightModeMap[5] = value;
   mutex->unlock();
   if (changed) emit FlightModeMap_5Changed(value);
}

qint8 StabilizationSettings::getVbarGyroSuppress() const
{
   QMutexLocker locker(mutex);
   return data.VbarGyroSuppress;
}
void StabilizationSettings::setVbarGyroSuppress(qint8 value)
{
   mutex->lock();
   bool changed = data.VbarGyroSuppress != value;
   data.VbarGyroSuppress = value;
   mutex->unlock();
   if (changed) emit VbarGyroSuppressChanged(value);
}

quint8 StabilizationSettings::getVbarPiroComp() const
{
   QMutexLocker locker(mutex);
   return data.VbarPiroComp;
}
void StabilizationSettings::setVbarPiroComp(quint8 value)
{
   mutex->lock();
   bool changed = data.VbarPiroComp != value;
   data.VbarPiroComp = value;
   mutex->unlock();
   if (changed) emit VbarPiroCompChanged(value);
}

quint8 StabilizationSettings::getVbarMaxAngle() const
{
   QMutexLocker locker(mutex);
   return data.VbarMaxAngle;
}
void StabilizationSettings::setVbarMaxAngle(quint8 value)
{
   mutex->lock();
   bool changed = data.VbarMaxAngle != value;
   data.VbarMaxAngle = value;
   mutex->unlock();
   if (changed) emit VbarMaxAngleChanged(value);
}

quint8 StabilizationSettings::getDerivativeCutoff() const
{
   QMutexLocker locker(mutex);
   return data.DerivativeCutoff;
}
void StabilizationSettings::setDerivativeCutoff(quint8 value)
{
   mutex->lock();
   bool changed = data.DerivativeCutoff != value;
   data.DerivativeCutoff = value;
   mutex->unlock();
   if (changed) emit DerivativeCutoffChanged(value);
}

quint8 StabilizationSettings::getMaxAxisLock() const
{
   QMutexLocker locker(mutex);
   return data.MaxAxisLock;
}
void StabilizationSettings::setMaxAxisLock(quint8 value)
{
   mutex->lock();
   bool changed = data.MaxAxisLock != value;
   data.MaxAxisLock = value;
   mutex->unlock();
   if (changed) emit MaxAxisLockChanged(value);
}

quint8 StabilizationSettings::getMaxAxisLockRate() const
{
   QMutexLocker locker(mutex);
   return data.MaxAxisLockRate;
}
void StabilizationSettings::setMaxAxisLockRate(quint8 value)
{
   mutex->lock();
   bool changed = data.MaxAxisLockRate != value;
   data.MaxAxisLockRate = value;
   mutex->unlock();
   if (changed) emit MaxAxisLockRateChanged(value);
}

quint8 StabilizationSettings::getMaxWeakLevelingRate() const
{
   QMutexLocker locker(mutex);
   return data.MaxWeakLevelingRate;
}
void StabilizationSettings::setMaxWeakLevelingRate(quint8 value)
{
   mutex->lock();
   bool changed = data.MaxWeakLevelingRate != value;
   data.MaxWeakLevelingRate = value;
   mutex->unlock();
   if (changed) emit MaxWeakLevelingRateChanged(value);
}

quint8 StabilizationSettings::getRattitudeModeTransition() const
{
   QMutexLocker locker(mutex);
   return data.RattitudeModeTransition;
}
void StabilizationSettings::setRattitudeModeTransition(quint8 value)
{
   mutex->lock();
   bool changed = data.RattitudeModeTransition != value;
   data.RattitudeModeTransition = value;
   mutex->unlock();
   if (changed) emit RattitudeModeTransitionChanged(value);
}

qint8 StabilizationSettings::getCruiseControlMinThrust() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlMinThrust;
}
void StabilizationSettings::setCruiseControlMinThrust(qint8 value)
{
   mutex->lock();
   bool changed = data.CruiseControlMinThrust != value;
   data.CruiseControlMinThrust = value;
   mutex->unlock();
   if (changed) emit CruiseControlMinThrustChanged(value);
}

quint8 StabilizationSettings::getCruiseControlMaxThrust() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlMaxThrust;
}
void StabilizationSettings::setCruiseControlMaxThrust(quint8 value)
{
   mutex->lock();
   bool changed = data.CruiseControlMaxThrust != value;
   data.CruiseControlMaxThrust = value;
   mutex->unlock();
   if (changed) emit CruiseControlMaxThrustChanged(value);
}

quint8 StabilizationSettings::getCruiseControlMaxAngle() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlMaxAngle;
}
void StabilizationSettings::setCruiseControlMaxAngle(quint8 value)
{
   mutex->lock();
   bool changed = data.CruiseControlMaxAngle != value;
   data.CruiseControlMaxAngle = value;
   mutex->unlock();
   if (changed) emit CruiseControlMaxAngleChanged(value);
}

quint8 StabilizationSettings::getCruiseControlFlightModeSwitchPosEnable(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlFlightModeSwitchPosEnable[index];
}
void StabilizationSettings::setCruiseControlFlightModeSwitchPosEnable(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.CruiseControlFlightModeSwitchPosEnable[index] != value;
   data.CruiseControlFlightModeSwitchPosEnable[index] = value;
   mutex->unlock();
   if (changed) emit CruiseControlFlightModeSwitchPosEnableChanged(index,value);
}

quint8 StabilizationSettings::getCruiseControlFlightModeSwitchPosEnable_0() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlFlightModeSwitchPosEnable[0];
}
void StabilizationSettings::setCruiseControlFlightModeSwitchPosEnable_0(quint8 value)
{
   mutex->lock();
   bool changed = data.CruiseControlFlightModeSwitchPosEnable[0] != value;
   data.CruiseControlFlightModeSwitchPosEnable[0] = value;
   mutex->unlock();
   if (changed) emit CruiseControlFlightModeSwitchPosEnable_0Changed(value);
}

quint8 StabilizationSettings::getCruiseControlFlightModeSwitchPosEnable_1() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlFlightModeSwitchPosEnable[1];
}
void StabilizationSettings::setCruiseControlFlightModeSwitchPosEnable_1(quint8 value)
{
   mutex->lock();
   bool changed = data.CruiseControlFlightModeSwitchPosEnable[1] != value;
   data.CruiseControlFlightModeSwitchPosEnable[1] = value;
   mutex->unlock();
   if (changed) emit CruiseControlFlightModeSwitchPosEnable_1Changed(value);
}

quint8 StabilizationSettings::getCruiseControlFlightModeSwitchPosEnable_2() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlFlightModeSwitchPosEnable[2];
}
void StabilizationSettings::setCruiseControlFlightModeSwitchPosEnable_2(quint8 value)
{
   mutex->lock();
   bool changed = data.CruiseControlFlightModeSwitchPosEnable[2] != value;
   data.CruiseControlFlightModeSwitchPosEnable[2] = value;
   mutex->unlock();
   if (changed) emit CruiseControlFlightModeSwitchPosEnable_2Changed(value);
}

quint8 StabilizationSettings::getCruiseControlFlightModeSwitchPosEnable_3() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlFlightModeSwitchPosEnable[3];
}
void StabilizationSettings::setCruiseControlFlightModeSwitchPosEnable_3(quint8 value)
{
   mutex->lock();
   bool changed = data.CruiseControlFlightModeSwitchPosEnable[3] != value;
   data.CruiseControlFlightModeSwitchPosEnable[3] = value;
   mutex->unlock();
   if (changed) emit CruiseControlFlightModeSwitchPosEnable_3Changed(value);
}

quint8 StabilizationSettings::getCruiseControlFlightModeSwitchPosEnable_4() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlFlightModeSwitchPosEnable[4];
}
void StabilizationSettings::setCruiseControlFlightModeSwitchPosEnable_4(quint8 value)
{
   mutex->lock();
   bool changed = data.CruiseControlFlightModeSwitchPosEnable[4] != value;
   data.CruiseControlFlightModeSwitchPosEnable[4] = value;
   mutex->unlock();
   if (changed) emit CruiseControlFlightModeSwitchPosEnable_4Changed(value);
}

quint8 StabilizationSettings::getCruiseControlFlightModeSwitchPosEnable_5() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlFlightModeSwitchPosEnable[5];
}
void StabilizationSettings::setCruiseControlFlightModeSwitchPosEnable_5(quint8 value)
{
   mutex->lock();
   bool changed = data.CruiseControlFlightModeSwitchPosEnable[5] != value;
   data.CruiseControlFlightModeSwitchPosEnable[5] = value;
   mutex->unlock();
   if (changed) emit CruiseControlFlightModeSwitchPosEnable_5Changed(value);
}

quint8 StabilizationSettings::getCruiseControlInvertedThrustReversing() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlInvertedThrustReversing;
}
void StabilizationSettings::setCruiseControlInvertedThrustReversing(quint8 value)
{
   mutex->lock();
   bool changed = data.CruiseControlInvertedThrustReversing != value;
   data.CruiseControlInvertedThrustReversing = value;
   mutex->unlock();
   if (changed) emit CruiseControlInvertedThrustReversingChanged(value);
}

quint8 StabilizationSettings::getCruiseControlInvertedPowerOutput() const
{
   QMutexLocker locker(mutex);
   return data.CruiseControlInvertedPowerOutput;
}
void StabilizationSettings::setCruiseControlInvertedPowerOutput(quint8 value)
{
   mutex->lock();
   bool changed = data.CruiseControlInvertedPowerOutput != value;
   data.CruiseControlInvertedPowerOutput = value;
   mutex->unlock();
   if (changed) emit CruiseControlInvertedPowerOutputChanged(value);
}

quint8 StabilizationSettings::getLowThrottleZeroIntegral() const
{
   QMutexLocker locker(mutex);
   return data.LowThrottleZeroIntegral;
}
void StabilizationSettings::setLowThrottleZeroIntegral(quint8 value)
{
   mutex->lock();
   bool changed = data.LowThrottleZeroIntegral != value;
   data.LowThrottleZeroIntegral = value;
   mutex->unlock();
   if (changed) emit LowThrottleZeroIntegralChanged(value);
}

quint8 StabilizationSettings::getFlightModeAssistMap(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.FlightModeAssistMap[index];
}
void StabilizationSettings::setFlightModeAssistMap(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeAssistMap[index] != value;
   data.FlightModeAssistMap[index] = value;
   mutex->unlock();
   if (changed) emit FlightModeAssistMapChanged(index,value);
}

quint8 StabilizationSettings::getFlightModeAssistMap_0() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeAssistMap[0];
}
void StabilizationSettings::setFlightModeAssistMap_0(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeAssistMap[0] != value;
   data.FlightModeAssistMap[0] = value;
   mutex->unlock();
   if (changed) emit FlightModeAssistMap_0Changed(value);
}

quint8 StabilizationSettings::getFlightModeAssistMap_1() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeAssistMap[1];
}
void StabilizationSettings::setFlightModeAssistMap_1(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeAssistMap[1] != value;
   data.FlightModeAssistMap[1] = value;
   mutex->unlock();
   if (changed) emit FlightModeAssistMap_1Changed(value);
}

quint8 StabilizationSettings::getFlightModeAssistMap_2() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeAssistMap[2];
}
void StabilizationSettings::setFlightModeAssistMap_2(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeAssistMap[2] != value;
   data.FlightModeAssistMap[2] = value;
   mutex->unlock();
   if (changed) emit FlightModeAssistMap_2Changed(value);
}

quint8 StabilizationSettings::getFlightModeAssistMap_3() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeAssistMap[3];
}
void StabilizationSettings::setFlightModeAssistMap_3(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeAssistMap[3] != value;
   data.FlightModeAssistMap[3] = value;
   mutex->unlock();
   if (changed) emit FlightModeAssistMap_3Changed(value);
}

quint8 StabilizationSettings::getFlightModeAssistMap_4() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeAssistMap[4];
}
void StabilizationSettings::setFlightModeAssistMap_4(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeAssistMap[4] != value;
   data.FlightModeAssistMap[4] = value;
   mutex->unlock();
   if (changed) emit FlightModeAssistMap_4Changed(value);
}

quint8 StabilizationSettings::getFlightModeAssistMap_5() const
{
   QMutexLocker locker(mutex);
   return data.FlightModeAssistMap[5];
}
void StabilizationSettings::setFlightModeAssistMap_5(quint8 value)
{
   mutex->lock();
   bool changed = data.FlightModeAssistMap[5] != value;
   data.FlightModeAssistMap[5] = value;
   mutex->unlock();
   if (changed) emit FlightModeAssistMap_5Changed(value);
}


