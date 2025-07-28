/**
 ******************************************************************************
 *
 * @file       stabilizationsettings.h
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
#ifndef STABILIZATIONSETTINGS_H
#define STABILIZATIONSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT StabilizationSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float VbarSensitivity_Roll READ getVbarSensitivity_Roll WRITE setVbarSensitivity_Roll NOTIFY VbarSensitivity_RollChanged);
    Q_PROPERTY(float VbarSensitivity_Pitch READ getVbarSensitivity_Pitch WRITE setVbarSensitivity_Pitch NOTIFY VbarSensitivity_PitchChanged);
    Q_PROPERTY(float VbarSensitivity_Yaw READ getVbarSensitivity_Yaw WRITE setVbarSensitivity_Yaw NOTIFY VbarSensitivity_YawChanged);
    Q_PROPERTY(float VbarRollPI_Kp READ getVbarRollPI_Kp WRITE setVbarRollPI_Kp NOTIFY VbarRollPI_KpChanged);
    Q_PROPERTY(float VbarRollPI_Ki READ getVbarRollPI_Ki WRITE setVbarRollPI_Ki NOTIFY VbarRollPI_KiChanged);
    Q_PROPERTY(float VbarPitchPI_Kp READ getVbarPitchPI_Kp WRITE setVbarPitchPI_Kp NOTIFY VbarPitchPI_KpChanged);
    Q_PROPERTY(float VbarPitchPI_Ki READ getVbarPitchPI_Ki WRITE setVbarPitchPI_Ki NOTIFY VbarPitchPI_KiChanged);
    Q_PROPERTY(float VbarYawPI_Kp READ getVbarYawPI_Kp WRITE setVbarYawPI_Kp NOTIFY VbarYawPI_KpChanged);
    Q_PROPERTY(float VbarYawPI_Ki READ getVbarYawPI_Ki WRITE setVbarYawPI_Ki NOTIFY VbarYawPI_KiChanged);
    Q_PROPERTY(float VbarTau READ getVbarTau WRITE setVbarTau NOTIFY VbarTauChanged);
    Q_PROPERTY(float GyroTau READ getGyroTau WRITE setGyroTau NOTIFY GyroTauChanged);
    Q_PROPERTY(float DerivativeGamma READ getDerivativeGamma WRITE setDerivativeGamma NOTIFY DerivativeGammaChanged);
    Q_PROPERTY(float AxisLockKp READ getAxisLockKp WRITE setAxisLockKp NOTIFY AxisLockKpChanged);
    Q_PROPERTY(float WeakLevelingKp READ getWeakLevelingKp WRITE setWeakLevelingKp NOTIFY WeakLevelingKpChanged);
    Q_PROPERTY(float CruiseControlMaxPowerFactor READ getCruiseControlMaxPowerFactor WRITE setCruiseControlMaxPowerFactor NOTIFY CruiseControlMaxPowerFactorChanged);
    Q_PROPERTY(float CruiseControlPowerTrim READ getCruiseControlPowerTrim WRITE setCruiseControlPowerTrim NOTIFY CruiseControlPowerTrimChanged);
    Q_PROPERTY(float CruiseControlPowerDelayComp READ getCruiseControlPowerDelayComp WRITE setCruiseControlPowerDelayComp NOTIFY CruiseControlPowerDelayCompChanged);
    Q_PROPERTY(float ScaleToAirspeed READ getScaleToAirspeed WRITE setScaleToAirspeed NOTIFY ScaleToAirspeedChanged);
    Q_PROPERTY(float ScaleToAirspeedLimits_Min READ getScaleToAirspeedLimits_Min WRITE setScaleToAirspeedLimits_Min NOTIFY ScaleToAirspeedLimits_MinChanged);
    Q_PROPERTY(float ScaleToAirspeedLimits_Max READ getScaleToAirspeedLimits_Max WRITE setScaleToAirspeedLimits_Max NOTIFY ScaleToAirspeedLimits_MaxChanged);
    Q_PROPERTY(quint8 FlightModeMap_0 READ getFlightModeMap_0 WRITE setFlightModeMap_0 NOTIFY FlightModeMap_0Changed);
    Q_PROPERTY(quint8 FlightModeMap_1 READ getFlightModeMap_1 WRITE setFlightModeMap_1 NOTIFY FlightModeMap_1Changed);
    Q_PROPERTY(quint8 FlightModeMap_2 READ getFlightModeMap_2 WRITE setFlightModeMap_2 NOTIFY FlightModeMap_2Changed);
    Q_PROPERTY(quint8 FlightModeMap_3 READ getFlightModeMap_3 WRITE setFlightModeMap_3 NOTIFY FlightModeMap_3Changed);
    Q_PROPERTY(quint8 FlightModeMap_4 READ getFlightModeMap_4 WRITE setFlightModeMap_4 NOTIFY FlightModeMap_4Changed);
    Q_PROPERTY(quint8 FlightModeMap_5 READ getFlightModeMap_5 WRITE setFlightModeMap_5 NOTIFY FlightModeMap_5Changed);
    Q_PROPERTY(qint8 VbarGyroSuppress READ getVbarGyroSuppress WRITE setVbarGyroSuppress NOTIFY VbarGyroSuppressChanged);
    Q_PROPERTY(quint8 VbarPiroComp READ getVbarPiroComp WRITE setVbarPiroComp NOTIFY VbarPiroCompChanged);
    Q_PROPERTY(quint8 VbarMaxAngle READ getVbarMaxAngle WRITE setVbarMaxAngle NOTIFY VbarMaxAngleChanged);
    Q_PROPERTY(quint8 DerivativeCutoff READ getDerivativeCutoff WRITE setDerivativeCutoff NOTIFY DerivativeCutoffChanged);
    Q_PROPERTY(quint8 MaxAxisLock READ getMaxAxisLock WRITE setMaxAxisLock NOTIFY MaxAxisLockChanged);
    Q_PROPERTY(quint8 MaxAxisLockRate READ getMaxAxisLockRate WRITE setMaxAxisLockRate NOTIFY MaxAxisLockRateChanged);
    Q_PROPERTY(quint8 MaxWeakLevelingRate READ getMaxWeakLevelingRate WRITE setMaxWeakLevelingRate NOTIFY MaxWeakLevelingRateChanged);
    Q_PROPERTY(quint8 RattitudeModeTransition READ getRattitudeModeTransition WRITE setRattitudeModeTransition NOTIFY RattitudeModeTransitionChanged);
    Q_PROPERTY(qint8 CruiseControlMinThrust READ getCruiseControlMinThrust WRITE setCruiseControlMinThrust NOTIFY CruiseControlMinThrustChanged);
    Q_PROPERTY(quint8 CruiseControlMaxThrust READ getCruiseControlMaxThrust WRITE setCruiseControlMaxThrust NOTIFY CruiseControlMaxThrustChanged);
    Q_PROPERTY(quint8 CruiseControlMaxAngle READ getCruiseControlMaxAngle WRITE setCruiseControlMaxAngle NOTIFY CruiseControlMaxAngleChanged);
    Q_PROPERTY(quint8 CruiseControlFlightModeSwitchPosEnable_0 READ getCruiseControlFlightModeSwitchPosEnable_0 WRITE setCruiseControlFlightModeSwitchPosEnable_0 NOTIFY CruiseControlFlightModeSwitchPosEnable_0Changed);
    Q_PROPERTY(quint8 CruiseControlFlightModeSwitchPosEnable_1 READ getCruiseControlFlightModeSwitchPosEnable_1 WRITE setCruiseControlFlightModeSwitchPosEnable_1 NOTIFY CruiseControlFlightModeSwitchPosEnable_1Changed);
    Q_PROPERTY(quint8 CruiseControlFlightModeSwitchPosEnable_2 READ getCruiseControlFlightModeSwitchPosEnable_2 WRITE setCruiseControlFlightModeSwitchPosEnable_2 NOTIFY CruiseControlFlightModeSwitchPosEnable_2Changed);
    Q_PROPERTY(quint8 CruiseControlFlightModeSwitchPosEnable_3 READ getCruiseControlFlightModeSwitchPosEnable_3 WRITE setCruiseControlFlightModeSwitchPosEnable_3 NOTIFY CruiseControlFlightModeSwitchPosEnable_3Changed);
    Q_PROPERTY(quint8 CruiseControlFlightModeSwitchPosEnable_4 READ getCruiseControlFlightModeSwitchPosEnable_4 WRITE setCruiseControlFlightModeSwitchPosEnable_4 NOTIFY CruiseControlFlightModeSwitchPosEnable_4Changed);
    Q_PROPERTY(quint8 CruiseControlFlightModeSwitchPosEnable_5 READ getCruiseControlFlightModeSwitchPosEnable_5 WRITE setCruiseControlFlightModeSwitchPosEnable_5 NOTIFY CruiseControlFlightModeSwitchPosEnable_5Changed);
    Q_PROPERTY(quint8 CruiseControlInvertedThrustReversing READ getCruiseControlInvertedThrustReversing WRITE setCruiseControlInvertedThrustReversing NOTIFY CruiseControlInvertedThrustReversingChanged);
    Q_PROPERTY(quint8 CruiseControlInvertedPowerOutput READ getCruiseControlInvertedPowerOutput WRITE setCruiseControlInvertedPowerOutput NOTIFY CruiseControlInvertedPowerOutputChanged);
    Q_PROPERTY(quint8 LowThrottleZeroIntegral READ getLowThrottleZeroIntegral WRITE setLowThrottleZeroIntegral NOTIFY LowThrottleZeroIntegralChanged);
    Q_PROPERTY(quint8 FlightModeAssistMap_0 READ getFlightModeAssistMap_0 WRITE setFlightModeAssistMap_0 NOTIFY FlightModeAssistMap_0Changed);
    Q_PROPERTY(quint8 FlightModeAssistMap_1 READ getFlightModeAssistMap_1 WRITE setFlightModeAssistMap_1 NOTIFY FlightModeAssistMap_1Changed);
    Q_PROPERTY(quint8 FlightModeAssistMap_2 READ getFlightModeAssistMap_2 WRITE setFlightModeAssistMap_2 NOTIFY FlightModeAssistMap_2Changed);
    Q_PROPERTY(quint8 FlightModeAssistMap_3 READ getFlightModeAssistMap_3 WRITE setFlightModeAssistMap_3 NOTIFY FlightModeAssistMap_3Changed);
    Q_PROPERTY(quint8 FlightModeAssistMap_4 READ getFlightModeAssistMap_4 WRITE setFlightModeAssistMap_4 NOTIFY FlightModeAssistMap_4Changed);
    Q_PROPERTY(quint8 FlightModeAssistMap_5 READ getFlightModeAssistMap_5 WRITE setFlightModeAssistMap_5 NOTIFY FlightModeAssistMap_5Changed);


public:
    // Field structure
    typedef struct {
        float VbarSensitivity[3];
        float VbarRollPI[2];
        float VbarPitchPI[2];
        float VbarYawPI[2];
        float VbarTau;
        float GyroTau;
        float DerivativeGamma;
        float AxisLockKp;
        float WeakLevelingKp;
        float CruiseControlMaxPowerFactor;
        float CruiseControlPowerTrim;
        float CruiseControlPowerDelayComp;
        float ScaleToAirspeed;
        float ScaleToAirspeedLimits[2];
        quint8 FlightModeMap[6];
        qint8 VbarGyroSuppress;
        quint8 VbarPiroComp;
        quint8 VbarMaxAngle;
        quint8 DerivativeCutoff;
        quint8 MaxAxisLock;
        quint8 MaxAxisLockRate;
        quint8 MaxWeakLevelingRate;
        quint8 RattitudeModeTransition;
        qint8 CruiseControlMinThrust;
        quint8 CruiseControlMaxThrust;
        quint8 CruiseControlMaxAngle;
        quint8 CruiseControlFlightModeSwitchPosEnable[6];
        quint8 CruiseControlInvertedThrustReversing;
        quint8 CruiseControlInvertedPowerOutput;
        quint8 LowThrottleZeroIntegral;
        quint8 FlightModeAssistMap[6];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field VbarSensitivity information
    /* Array element names for field VbarSensitivity */
    typedef enum { VBARSENSITIVITY_ROLL=0, VBARSENSITIVITY_PITCH=1, VBARSENSITIVITY_YAW=2 } VbarSensitivityElem;
    /* Number of elements for field VbarSensitivity */
    static const quint32 VBARSENSITIVITY_NUMELEM = 3;
    // Field VbarRollPI information
    /* Array element names for field VbarRollPI */
    typedef enum { VBARROLLPI_KP=0, VBARROLLPI_KI=1 } VbarRollPIElem;
    /* Number of elements for field VbarRollPI */
    static const quint32 VBARROLLPI_NUMELEM = 2;
    // Field VbarPitchPI information
    /* Array element names for field VbarPitchPI */
    typedef enum { VBARPITCHPI_KP=0, VBARPITCHPI_KI=1 } VbarPitchPIElem;
    /* Number of elements for field VbarPitchPI */
    static const quint32 VBARPITCHPI_NUMELEM = 2;
    // Field VbarYawPI information
    /* Array element names for field VbarYawPI */
    typedef enum { VBARYAWPI_KP=0, VBARYAWPI_KI=1 } VbarYawPIElem;
    /* Number of elements for field VbarYawPI */
    static const quint32 VBARYAWPI_NUMELEM = 2;
    // Field VbarTau information
    // Field GyroTau information
    // Field DerivativeGamma information
    // Field AxisLockKp information
    // Field WeakLevelingKp information
    // Field CruiseControlMaxPowerFactor information
    // Field CruiseControlPowerTrim information
    // Field CruiseControlPowerDelayComp information
    // Field ScaleToAirspeed information
    // Field ScaleToAirspeedLimits information
    /* Array element names for field ScaleToAirspeedLimits */
    typedef enum { SCALETOAIRSPEEDLIMITS_MIN=0, SCALETOAIRSPEEDLIMITS_MAX=1 } ScaleToAirspeedLimitsElem;
    /* Number of elements for field ScaleToAirspeedLimits */
    static const quint32 SCALETOAIRSPEEDLIMITS_NUMELEM = 2;
    // Field FlightModeMap information
    /* Enumeration options for field FlightModeMap */
    typedef enum { FLIGHTMODEMAP_BANK1=0, FLIGHTMODEMAP_BANK2=1, FLIGHTMODEMAP_BANK3=2 } FlightModeMapOptions;
    /* Number of elements for field FlightModeMap */
    static const quint32 FLIGHTMODEMAP_NUMELEM = 6;
    // Field VbarGyroSuppress information
    // Field VbarPiroComp information
    /* Enumeration options for field VbarPiroComp */
    typedef enum { VBARPIROCOMP_FALSE=0, VBARPIROCOMP_TRUE=1 } VbarPiroCompOptions;
    // Field VbarMaxAngle information
    // Field DerivativeCutoff information
    // Field MaxAxisLock information
    // Field MaxAxisLockRate information
    // Field MaxWeakLevelingRate information
    // Field RattitudeModeTransition information
    // Field CruiseControlMinThrust information
    // Field CruiseControlMaxThrust information
    // Field CruiseControlMaxAngle information
    // Field CruiseControlFlightModeSwitchPosEnable information
    /* Enumeration options for field CruiseControlFlightModeSwitchPosEnable */
    typedef enum { CRUISECONTROLFLIGHTMODESWITCHPOSENABLE_FALSE=0, CRUISECONTROLFLIGHTMODESWITCHPOSENABLE_TRUE=1 } CruiseControlFlightModeSwitchPosEnableOptions;
    /* Number of elements for field CruiseControlFlightModeSwitchPosEnable */
    static const quint32 CRUISECONTROLFLIGHTMODESWITCHPOSENABLE_NUMELEM = 6;
    // Field CruiseControlInvertedThrustReversing information
    /* Enumeration options for field CruiseControlInvertedThrustReversing */
    typedef enum { CRUISECONTROLINVERTEDTHRUSTREVERSING_UNREVERSED=0, CRUISECONTROLINVERTEDTHRUSTREVERSING_REVERSED=1 } CruiseControlInvertedThrustReversingOptions;
    // Field CruiseControlInvertedPowerOutput information
    /* Enumeration options for field CruiseControlInvertedPowerOutput */
    typedef enum { CRUISECONTROLINVERTEDPOWEROUTPUT_ZERO=0, CRUISECONTROLINVERTEDPOWEROUTPUT_NORMAL=1, CRUISECONTROLINVERTEDPOWEROUTPUT_BOOSTED=2 } CruiseControlInvertedPowerOutputOptions;
    // Field LowThrottleZeroIntegral information
    /* Enumeration options for field LowThrottleZeroIntegral */
    typedef enum { LOWTHROTTLEZEROINTEGRAL_FALSE=0, LOWTHROTTLEZEROINTEGRAL_TRUE=1 } LowThrottleZeroIntegralOptions;
    // Field FlightModeAssistMap information
    /* Enumeration options for field FlightModeAssistMap */
    typedef enum { FLIGHTMODEASSISTMAP_NONE=0, FLIGHTMODEASSISTMAP_GPSASSIST=1 } FlightModeAssistMapOptions;
    /* Number of elements for field FlightModeAssistMap */
    static const quint32 FLIGHTMODEASSISTMAP_NUMELEM = 6;

  
    // Constants
    static const quint32 OBJID = 0x73603180;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    StabilizationSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static StabilizationSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getVbarSensitivity(quint32 index) const;
    Q_INVOKABLE float getVbarSensitivity_Roll() const;
    Q_INVOKABLE float getVbarSensitivity_Pitch() const;
    Q_INVOKABLE float getVbarSensitivity_Yaw() const;
    Q_INVOKABLE float getVbarRollPI(quint32 index) const;
    Q_INVOKABLE float getVbarRollPI_Kp() const;
    Q_INVOKABLE float getVbarRollPI_Ki() const;
    Q_INVOKABLE float getVbarPitchPI(quint32 index) const;
    Q_INVOKABLE float getVbarPitchPI_Kp() const;
    Q_INVOKABLE float getVbarPitchPI_Ki() const;
    Q_INVOKABLE float getVbarYawPI(quint32 index) const;
    Q_INVOKABLE float getVbarYawPI_Kp() const;
    Q_INVOKABLE float getVbarYawPI_Ki() const;
    Q_INVOKABLE float getVbarTau() const;
    Q_INVOKABLE float getGyroTau() const;
    Q_INVOKABLE float getDerivativeGamma() const;
    Q_INVOKABLE float getAxisLockKp() const;
    Q_INVOKABLE float getWeakLevelingKp() const;
    Q_INVOKABLE float getCruiseControlMaxPowerFactor() const;
    Q_INVOKABLE float getCruiseControlPowerTrim() const;
    Q_INVOKABLE float getCruiseControlPowerDelayComp() const;
    Q_INVOKABLE float getScaleToAirspeed() const;
    Q_INVOKABLE float getScaleToAirspeedLimits(quint32 index) const;
    Q_INVOKABLE float getScaleToAirspeedLimits_Min() const;
    Q_INVOKABLE float getScaleToAirspeedLimits_Max() const;
    Q_INVOKABLE quint8 getFlightModeMap(quint32 index) const;
    Q_INVOKABLE quint8 getFlightModeMap_0() const;
    Q_INVOKABLE quint8 getFlightModeMap_1() const;
    Q_INVOKABLE quint8 getFlightModeMap_2() const;
    Q_INVOKABLE quint8 getFlightModeMap_3() const;
    Q_INVOKABLE quint8 getFlightModeMap_4() const;
    Q_INVOKABLE quint8 getFlightModeMap_5() const;
    Q_INVOKABLE qint8 getVbarGyroSuppress() const;
    Q_INVOKABLE quint8 getVbarPiroComp() const;
    Q_INVOKABLE quint8 getVbarMaxAngle() const;
    Q_INVOKABLE quint8 getDerivativeCutoff() const;
    Q_INVOKABLE quint8 getMaxAxisLock() const;
    Q_INVOKABLE quint8 getMaxAxisLockRate() const;
    Q_INVOKABLE quint8 getMaxWeakLevelingRate() const;
    Q_INVOKABLE quint8 getRattitudeModeTransition() const;
    Q_INVOKABLE qint8 getCruiseControlMinThrust() const;
    Q_INVOKABLE quint8 getCruiseControlMaxThrust() const;
    Q_INVOKABLE quint8 getCruiseControlMaxAngle() const;
    Q_INVOKABLE quint8 getCruiseControlFlightModeSwitchPosEnable(quint32 index) const;
    Q_INVOKABLE quint8 getCruiseControlFlightModeSwitchPosEnable_0() const;
    Q_INVOKABLE quint8 getCruiseControlFlightModeSwitchPosEnable_1() const;
    Q_INVOKABLE quint8 getCruiseControlFlightModeSwitchPosEnable_2() const;
    Q_INVOKABLE quint8 getCruiseControlFlightModeSwitchPosEnable_3() const;
    Q_INVOKABLE quint8 getCruiseControlFlightModeSwitchPosEnable_4() const;
    Q_INVOKABLE quint8 getCruiseControlFlightModeSwitchPosEnable_5() const;
    Q_INVOKABLE quint8 getCruiseControlInvertedThrustReversing() const;
    Q_INVOKABLE quint8 getCruiseControlInvertedPowerOutput() const;
    Q_INVOKABLE quint8 getLowThrottleZeroIntegral() const;
    Q_INVOKABLE quint8 getFlightModeAssistMap(quint32 index) const;
    Q_INVOKABLE quint8 getFlightModeAssistMap_0() const;
    Q_INVOKABLE quint8 getFlightModeAssistMap_1() const;
    Q_INVOKABLE quint8 getFlightModeAssistMap_2() const;
    Q_INVOKABLE quint8 getFlightModeAssistMap_3() const;
    Q_INVOKABLE quint8 getFlightModeAssistMap_4() const;
    Q_INVOKABLE quint8 getFlightModeAssistMap_5() const;


public slots:
    void setVbarSensitivity(quint32 index, float value);
    void setVbarSensitivity_Roll(float value);
    void setVbarSensitivity_Pitch(float value);
    void setVbarSensitivity_Yaw(float value);
    void setVbarRollPI(quint32 index, float value);
    void setVbarRollPI_Kp(float value);
    void setVbarRollPI_Ki(float value);
    void setVbarPitchPI(quint32 index, float value);
    void setVbarPitchPI_Kp(float value);
    void setVbarPitchPI_Ki(float value);
    void setVbarYawPI(quint32 index, float value);
    void setVbarYawPI_Kp(float value);
    void setVbarYawPI_Ki(float value);
    void setVbarTau(float value);
    void setGyroTau(float value);
    void setDerivativeGamma(float value);
    void setAxisLockKp(float value);
    void setWeakLevelingKp(float value);
    void setCruiseControlMaxPowerFactor(float value);
    void setCruiseControlPowerTrim(float value);
    void setCruiseControlPowerDelayComp(float value);
    void setScaleToAirspeed(float value);
    void setScaleToAirspeedLimits(quint32 index, float value);
    void setScaleToAirspeedLimits_Min(float value);
    void setScaleToAirspeedLimits_Max(float value);
    void setFlightModeMap(quint32 index, quint8 value);
    void setFlightModeMap_0(quint8 value);
    void setFlightModeMap_1(quint8 value);
    void setFlightModeMap_2(quint8 value);
    void setFlightModeMap_3(quint8 value);
    void setFlightModeMap_4(quint8 value);
    void setFlightModeMap_5(quint8 value);
    void setVbarGyroSuppress(qint8 value);
    void setVbarPiroComp(quint8 value);
    void setVbarMaxAngle(quint8 value);
    void setDerivativeCutoff(quint8 value);
    void setMaxAxisLock(quint8 value);
    void setMaxAxisLockRate(quint8 value);
    void setMaxWeakLevelingRate(quint8 value);
    void setRattitudeModeTransition(quint8 value);
    void setCruiseControlMinThrust(qint8 value);
    void setCruiseControlMaxThrust(quint8 value);
    void setCruiseControlMaxAngle(quint8 value);
    void setCruiseControlFlightModeSwitchPosEnable(quint32 index, quint8 value);
    void setCruiseControlFlightModeSwitchPosEnable_0(quint8 value);
    void setCruiseControlFlightModeSwitchPosEnable_1(quint8 value);
    void setCruiseControlFlightModeSwitchPosEnable_2(quint8 value);
    void setCruiseControlFlightModeSwitchPosEnable_3(quint8 value);
    void setCruiseControlFlightModeSwitchPosEnable_4(quint8 value);
    void setCruiseControlFlightModeSwitchPosEnable_5(quint8 value);
    void setCruiseControlInvertedThrustReversing(quint8 value);
    void setCruiseControlInvertedPowerOutput(quint8 value);
    void setLowThrottleZeroIntegral(quint8 value);
    void setFlightModeAssistMap(quint32 index, quint8 value);
    void setFlightModeAssistMap_0(quint8 value);
    void setFlightModeAssistMap_1(quint8 value);
    void setFlightModeAssistMap_2(quint8 value);
    void setFlightModeAssistMap_3(quint8 value);
    void setFlightModeAssistMap_4(quint8 value);
    void setFlightModeAssistMap_5(quint8 value);


signals:
    void VbarSensitivityChanged(quint32 index, float value);
    void VbarSensitivity_RollChanged(float value);
    void VbarSensitivity_PitchChanged(float value);
    void VbarSensitivity_YawChanged(float value);
    void VbarRollPIChanged(quint32 index, float value);
    void VbarRollPI_KpChanged(float value);
    void VbarRollPI_KiChanged(float value);
    void VbarPitchPIChanged(quint32 index, float value);
    void VbarPitchPI_KpChanged(float value);
    void VbarPitchPI_KiChanged(float value);
    void VbarYawPIChanged(quint32 index, float value);
    void VbarYawPI_KpChanged(float value);
    void VbarYawPI_KiChanged(float value);
    void VbarTauChanged(float value);
    void GyroTauChanged(float value);
    void DerivativeGammaChanged(float value);
    void AxisLockKpChanged(float value);
    void WeakLevelingKpChanged(float value);
    void CruiseControlMaxPowerFactorChanged(float value);
    void CruiseControlPowerTrimChanged(float value);
    void CruiseControlPowerDelayCompChanged(float value);
    void ScaleToAirspeedChanged(float value);
    void ScaleToAirspeedLimitsChanged(quint32 index, float value);
    void ScaleToAirspeedLimits_MinChanged(float value);
    void ScaleToAirspeedLimits_MaxChanged(float value);
    void FlightModeMapChanged(quint32 index, quint8 value);
    void FlightModeMap_0Changed(quint8 value);
    void FlightModeMap_1Changed(quint8 value);
    void FlightModeMap_2Changed(quint8 value);
    void FlightModeMap_3Changed(quint8 value);
    void FlightModeMap_4Changed(quint8 value);
    void FlightModeMap_5Changed(quint8 value);
    void VbarGyroSuppressChanged(qint8 value);
    void VbarPiroCompChanged(quint8 value);
    void VbarMaxAngleChanged(quint8 value);
    void DerivativeCutoffChanged(quint8 value);
    void MaxAxisLockChanged(quint8 value);
    void MaxAxisLockRateChanged(quint8 value);
    void MaxWeakLevelingRateChanged(quint8 value);
    void RattitudeModeTransitionChanged(quint8 value);
    void CruiseControlMinThrustChanged(qint8 value);
    void CruiseControlMaxThrustChanged(quint8 value);
    void CruiseControlMaxAngleChanged(quint8 value);
    void CruiseControlFlightModeSwitchPosEnableChanged(quint32 index, quint8 value);
    void CruiseControlFlightModeSwitchPosEnable_0Changed(quint8 value);
    void CruiseControlFlightModeSwitchPosEnable_1Changed(quint8 value);
    void CruiseControlFlightModeSwitchPosEnable_2Changed(quint8 value);
    void CruiseControlFlightModeSwitchPosEnable_3Changed(quint8 value);
    void CruiseControlFlightModeSwitchPosEnable_4Changed(quint8 value);
    void CruiseControlFlightModeSwitchPosEnable_5Changed(quint8 value);
    void CruiseControlInvertedThrustReversingChanged(quint8 value);
    void CruiseControlInvertedPowerOutputChanged(quint8 value);
    void LowThrottleZeroIntegralChanged(quint8 value);
    void FlightModeAssistMapChanged(quint32 index, quint8 value);
    void FlightModeAssistMap_0Changed(quint8 value);
    void FlightModeAssistMap_1Changed(quint8 value);
    void FlightModeAssistMap_2Changed(quint8 value);
    void FlightModeAssistMap_3Changed(quint8 value);
    void FlightModeAssistMap_4Changed(quint8 value);
    void FlightModeAssistMap_5Changed(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // STABILIZATIONSETTINGS_H
