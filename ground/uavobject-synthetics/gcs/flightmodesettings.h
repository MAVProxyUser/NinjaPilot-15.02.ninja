/**
 ******************************************************************************
 *
 * @file       flightmodesettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: flightmodesettings.xml. 
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
#ifndef FLIGHTMODESETTINGS_H
#define FLIGHTMODESETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT FlightModeSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float ReturnToBaseAltitudeOffset READ getReturnToBaseAltitudeOffset WRITE setReturnToBaseAltitudeOffset NOTIFY ReturnToBaseAltitudeOffsetChanged);
    Q_PROPERTY(float LandingVelocity READ getLandingVelocity WRITE setLandingVelocity NOTIFY LandingVelocityChanged);
    Q_PROPERTY(float PositionHoldOffset_Horizontal READ getPositionHoldOffset_Horizontal WRITE setPositionHoldOffset_Horizontal NOTIFY PositionHoldOffset_HorizontalChanged);
    Q_PROPERTY(float PositionHoldOffset_Vertical READ getPositionHoldOffset_Vertical WRITE setPositionHoldOffset_Vertical NOTIFY PositionHoldOffset_VerticalChanged);
    Q_PROPERTY(float VarioControlLowPassAlpha READ getVarioControlLowPassAlpha WRITE setVarioControlLowPassAlpha NOTIFY VarioControlLowPassAlphaChanged);
    Q_PROPERTY(quint16 ArmedTimeout READ getArmedTimeout WRITE setArmedTimeout NOTIFY ArmedTimeoutChanged);
    Q_PROPERTY(quint16 ArmingSequenceTime READ getArmingSequenceTime WRITE setArmingSequenceTime NOTIFY ArmingSequenceTimeChanged);
    Q_PROPERTY(quint16 DisarmingSequenceTime READ getDisarmingSequenceTime WRITE setDisarmingSequenceTime NOTIFY DisarmingSequenceTimeChanged);
    Q_PROPERTY(quint8 Arming READ getArming WRITE setArming NOTIFY ArmingChanged);
    Q_PROPERTY(quint8 Stabilization1Settings_Roll READ getStabilization1Settings_Roll WRITE setStabilization1Settings_Roll NOTIFY Stabilization1Settings_RollChanged);
    Q_PROPERTY(quint8 Stabilization1Settings_Pitch READ getStabilization1Settings_Pitch WRITE setStabilization1Settings_Pitch NOTIFY Stabilization1Settings_PitchChanged);
    Q_PROPERTY(quint8 Stabilization1Settings_Yaw READ getStabilization1Settings_Yaw WRITE setStabilization1Settings_Yaw NOTIFY Stabilization1Settings_YawChanged);
    Q_PROPERTY(quint8 Stabilization1Settings_Thrust READ getStabilization1Settings_Thrust WRITE setStabilization1Settings_Thrust NOTIFY Stabilization1Settings_ThrustChanged);
    Q_PROPERTY(quint8 Stabilization2Settings_Roll READ getStabilization2Settings_Roll WRITE setStabilization2Settings_Roll NOTIFY Stabilization2Settings_RollChanged);
    Q_PROPERTY(quint8 Stabilization2Settings_Pitch READ getStabilization2Settings_Pitch WRITE setStabilization2Settings_Pitch NOTIFY Stabilization2Settings_PitchChanged);
    Q_PROPERTY(quint8 Stabilization2Settings_Yaw READ getStabilization2Settings_Yaw WRITE setStabilization2Settings_Yaw NOTIFY Stabilization2Settings_YawChanged);
    Q_PROPERTY(quint8 Stabilization2Settings_Thrust READ getStabilization2Settings_Thrust WRITE setStabilization2Settings_Thrust NOTIFY Stabilization2Settings_ThrustChanged);
    Q_PROPERTY(quint8 Stabilization3Settings_Roll READ getStabilization3Settings_Roll WRITE setStabilization3Settings_Roll NOTIFY Stabilization3Settings_RollChanged);
    Q_PROPERTY(quint8 Stabilization3Settings_Pitch READ getStabilization3Settings_Pitch WRITE setStabilization3Settings_Pitch NOTIFY Stabilization3Settings_PitchChanged);
    Q_PROPERTY(quint8 Stabilization3Settings_Yaw READ getStabilization3Settings_Yaw WRITE setStabilization3Settings_Yaw NOTIFY Stabilization3Settings_YawChanged);
    Q_PROPERTY(quint8 Stabilization3Settings_Thrust READ getStabilization3Settings_Thrust WRITE setStabilization3Settings_Thrust NOTIFY Stabilization3Settings_ThrustChanged);
    Q_PROPERTY(quint8 Stabilization4Settings_Roll READ getStabilization4Settings_Roll WRITE setStabilization4Settings_Roll NOTIFY Stabilization4Settings_RollChanged);
    Q_PROPERTY(quint8 Stabilization4Settings_Pitch READ getStabilization4Settings_Pitch WRITE setStabilization4Settings_Pitch NOTIFY Stabilization4Settings_PitchChanged);
    Q_PROPERTY(quint8 Stabilization4Settings_Yaw READ getStabilization4Settings_Yaw WRITE setStabilization4Settings_Yaw NOTIFY Stabilization4Settings_YawChanged);
    Q_PROPERTY(quint8 Stabilization4Settings_Thrust READ getStabilization4Settings_Thrust WRITE setStabilization4Settings_Thrust NOTIFY Stabilization4Settings_ThrustChanged);
    Q_PROPERTY(quint8 Stabilization5Settings_Roll READ getStabilization5Settings_Roll WRITE setStabilization5Settings_Roll NOTIFY Stabilization5Settings_RollChanged);
    Q_PROPERTY(quint8 Stabilization5Settings_Pitch READ getStabilization5Settings_Pitch WRITE setStabilization5Settings_Pitch NOTIFY Stabilization5Settings_PitchChanged);
    Q_PROPERTY(quint8 Stabilization5Settings_Yaw READ getStabilization5Settings_Yaw WRITE setStabilization5Settings_Yaw NOTIFY Stabilization5Settings_YawChanged);
    Q_PROPERTY(quint8 Stabilization5Settings_Thrust READ getStabilization5Settings_Thrust WRITE setStabilization5Settings_Thrust NOTIFY Stabilization5Settings_ThrustChanged);
    Q_PROPERTY(quint8 Stabilization6Settings_Roll READ getStabilization6Settings_Roll WRITE setStabilization6Settings_Roll NOTIFY Stabilization6Settings_RollChanged);
    Q_PROPERTY(quint8 Stabilization6Settings_Pitch READ getStabilization6Settings_Pitch WRITE setStabilization6Settings_Pitch NOTIFY Stabilization6Settings_PitchChanged);
    Q_PROPERTY(quint8 Stabilization6Settings_Yaw READ getStabilization6Settings_Yaw WRITE setStabilization6Settings_Yaw NOTIFY Stabilization6Settings_YawChanged);
    Q_PROPERTY(quint8 Stabilization6Settings_Thrust READ getStabilization6Settings_Thrust WRITE setStabilization6Settings_Thrust NOTIFY Stabilization6Settings_ThrustChanged);
    Q_PROPERTY(quint8 FlightModePosition_0 READ getFlightModePosition_0 WRITE setFlightModePosition_0 NOTIFY FlightModePosition_0Changed);
    Q_PROPERTY(quint8 FlightModePosition_1 READ getFlightModePosition_1 WRITE setFlightModePosition_1 NOTIFY FlightModePosition_1Changed);
    Q_PROPERTY(quint8 FlightModePosition_2 READ getFlightModePosition_2 WRITE setFlightModePosition_2 NOTIFY FlightModePosition_2Changed);
    Q_PROPERTY(quint8 FlightModePosition_3 READ getFlightModePosition_3 WRITE setFlightModePosition_3 NOTIFY FlightModePosition_3Changed);
    Q_PROPERTY(quint8 FlightModePosition_4 READ getFlightModePosition_4 WRITE setFlightModePosition_4 NOTIFY FlightModePosition_4Changed);
    Q_PROPERTY(quint8 FlightModePosition_5 READ getFlightModePosition_5 WRITE setFlightModePosition_5 NOTIFY FlightModePosition_5Changed);
    Q_PROPERTY(quint8 DisableSanityChecks READ getDisableSanityChecks WRITE setDisableSanityChecks NOTIFY DisableSanityChecksChanged);
    Q_PROPERTY(quint8 ReturnToBaseNextCommand READ getReturnToBaseNextCommand WRITE setReturnToBaseNextCommand NOTIFY ReturnToBaseNextCommandChanged);


public:
    // Field structure
    typedef struct {
        float ReturnToBaseAltitudeOffset;
        float LandingVelocity;
        float PositionHoldOffset[2];
        float VarioControlLowPassAlpha;
        quint16 ArmedTimeout;
        quint16 ArmingSequenceTime;
        quint16 DisarmingSequenceTime;
        quint8 Arming;
        quint8 Stabilization1Settings[4];
        quint8 Stabilization2Settings[4];
        quint8 Stabilization3Settings[4];
        quint8 Stabilization4Settings[4];
        quint8 Stabilization5Settings[4];
        quint8 Stabilization6Settings[4];
        quint8 FlightModePosition[6];
        quint8 DisableSanityChecks;
        quint8 ReturnToBaseNextCommand;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field ReturnToBaseAltitudeOffset information
    // Field LandingVelocity information
    // Field PositionHoldOffset information
    /* Array element names for field PositionHoldOffset */
    typedef enum { POSITIONHOLDOFFSET_HORIZONTAL=0, POSITIONHOLDOFFSET_VERTICAL=1 } PositionHoldOffsetElem;
    /* Number of elements for field PositionHoldOffset */
    static const quint32 POSITIONHOLDOFFSET_NUMELEM = 2;
    // Field VarioControlLowPassAlpha information
    // Field ArmedTimeout information
    // Field ArmingSequenceTime information
    // Field DisarmingSequenceTime information
    // Field Arming information
    /* Enumeration options for field Arming */
    typedef enum { ARMING_ALWAYSDISARMED=0, ARMING_ALWAYSARMED=1, ARMING_ROLLLEFT=2, ARMING_ROLLRIGHT=3, ARMING_PITCHFORWARD=4, ARMING_PITCHAFT=5, ARMING_YAWLEFT=6, ARMING_YAWRIGHT=7, ARMING_ACCESSORY0=8, ARMING_ACCESSORY1=9, ARMING_ACCESSORY2=10 } ArmingOptions;
    // Field Stabilization1Settings information
    /* Enumeration options for field Stabilization1Settings */
    typedef enum { STABILIZATION1SETTINGS_MANUAL=0, STABILIZATION1SETTINGS_RATE=1, STABILIZATION1SETTINGS_ATTITUDE=2, STABILIZATION1SETTINGS_AXISLOCK=3, STABILIZATION1SETTINGS_WEAKLEVELING=4, STABILIZATION1SETTINGS_VIRTUALBAR=5, STABILIZATION1SETTINGS_ACRO=6, STABILIZATION1SETTINGS_RATTITUDE=7, STABILIZATION1SETTINGS_ALTITUDEHOLD=8, STABILIZATION1SETTINGS_ALTITUDEVARIO=9, STABILIZATION1SETTINGS_CRUISECONTROL=10 } Stabilization1SettingsOptions;
    /* Array element names for field Stabilization1Settings */
    typedef enum { STABILIZATION1SETTINGS_ROLL=0, STABILIZATION1SETTINGS_PITCH=1, STABILIZATION1SETTINGS_YAW=2, STABILIZATION1SETTINGS_THRUST=3 } Stabilization1SettingsElem;
    /* Number of elements for field Stabilization1Settings */
    static const quint32 STABILIZATION1SETTINGS_NUMELEM = 4;
    // Field Stabilization2Settings information
    /* Enumeration options for field Stabilization2Settings */
    typedef enum { STABILIZATION2SETTINGS_MANUAL=0, STABILIZATION2SETTINGS_RATE=1, STABILIZATION2SETTINGS_ATTITUDE=2, STABILIZATION2SETTINGS_AXISLOCK=3, STABILIZATION2SETTINGS_WEAKLEVELING=4, STABILIZATION2SETTINGS_VIRTUALBAR=5, STABILIZATION2SETTINGS_ACRO=6, STABILIZATION2SETTINGS_RATTITUDE=7, STABILIZATION2SETTINGS_ALTITUDEHOLD=8, STABILIZATION2SETTINGS_ALTITUDEVARIO=9, STABILIZATION2SETTINGS_CRUISECONTROL=10 } Stabilization2SettingsOptions;
    /* Array element names for field Stabilization2Settings */
    typedef enum { STABILIZATION2SETTINGS_ROLL=0, STABILIZATION2SETTINGS_PITCH=1, STABILIZATION2SETTINGS_YAW=2, STABILIZATION2SETTINGS_THRUST=3 } Stabilization2SettingsElem;
    /* Number of elements for field Stabilization2Settings */
    static const quint32 STABILIZATION2SETTINGS_NUMELEM = 4;
    // Field Stabilization3Settings information
    /* Enumeration options for field Stabilization3Settings */
    typedef enum { STABILIZATION3SETTINGS_MANUAL=0, STABILIZATION3SETTINGS_RATE=1, STABILIZATION3SETTINGS_ATTITUDE=2, STABILIZATION3SETTINGS_AXISLOCK=3, STABILIZATION3SETTINGS_WEAKLEVELING=4, STABILIZATION3SETTINGS_VIRTUALBAR=5, STABILIZATION3SETTINGS_ACRO=6, STABILIZATION3SETTINGS_RATTITUDE=7, STABILIZATION3SETTINGS_ALTITUDEHOLD=8, STABILIZATION3SETTINGS_ALTITUDEVARIO=9, STABILIZATION3SETTINGS_CRUISECONTROL=10 } Stabilization3SettingsOptions;
    /* Array element names for field Stabilization3Settings */
    typedef enum { STABILIZATION3SETTINGS_ROLL=0, STABILIZATION3SETTINGS_PITCH=1, STABILIZATION3SETTINGS_YAW=2, STABILIZATION3SETTINGS_THRUST=3 } Stabilization3SettingsElem;
    /* Number of elements for field Stabilization3Settings */
    static const quint32 STABILIZATION3SETTINGS_NUMELEM = 4;
    // Field Stabilization4Settings information
    /* Enumeration options for field Stabilization4Settings */
    typedef enum { STABILIZATION4SETTINGS_MANUAL=0, STABILIZATION4SETTINGS_RATE=1, STABILIZATION4SETTINGS_ATTITUDE=2, STABILIZATION4SETTINGS_AXISLOCK=3, STABILIZATION4SETTINGS_WEAKLEVELING=4, STABILIZATION4SETTINGS_VIRTUALBAR=5, STABILIZATION4SETTINGS_ACRO=6, STABILIZATION4SETTINGS_RATTITUDE=7, STABILIZATION4SETTINGS_ALTITUDEHOLD=8, STABILIZATION4SETTINGS_ALTITUDEVARIO=9, STABILIZATION4SETTINGS_CRUISECONTROL=10 } Stabilization4SettingsOptions;
    /* Array element names for field Stabilization4Settings */
    typedef enum { STABILIZATION4SETTINGS_ROLL=0, STABILIZATION4SETTINGS_PITCH=1, STABILIZATION4SETTINGS_YAW=2, STABILIZATION4SETTINGS_THRUST=3 } Stabilization4SettingsElem;
    /* Number of elements for field Stabilization4Settings */
    static const quint32 STABILIZATION4SETTINGS_NUMELEM = 4;
    // Field Stabilization5Settings information
    /* Enumeration options for field Stabilization5Settings */
    typedef enum { STABILIZATION5SETTINGS_MANUAL=0, STABILIZATION5SETTINGS_RATE=1, STABILIZATION5SETTINGS_ATTITUDE=2, STABILIZATION5SETTINGS_AXISLOCK=3, STABILIZATION5SETTINGS_WEAKLEVELING=4, STABILIZATION5SETTINGS_VIRTUALBAR=5, STABILIZATION5SETTINGS_ACRO=6, STABILIZATION5SETTINGS_RATTITUDE=7, STABILIZATION5SETTINGS_ALTITUDEHOLD=8, STABILIZATION5SETTINGS_ALTITUDEVARIO=9, STABILIZATION5SETTINGS_CRUISECONTROL=10 } Stabilization5SettingsOptions;
    /* Array element names for field Stabilization5Settings */
    typedef enum { STABILIZATION5SETTINGS_ROLL=0, STABILIZATION5SETTINGS_PITCH=1, STABILIZATION5SETTINGS_YAW=2, STABILIZATION5SETTINGS_THRUST=3 } Stabilization5SettingsElem;
    /* Number of elements for field Stabilization5Settings */
    static const quint32 STABILIZATION5SETTINGS_NUMELEM = 4;
    // Field Stabilization6Settings information
    /* Enumeration options for field Stabilization6Settings */
    typedef enum { STABILIZATION6SETTINGS_MANUAL=0, STABILIZATION6SETTINGS_RATE=1, STABILIZATION6SETTINGS_ATTITUDE=2, STABILIZATION6SETTINGS_AXISLOCK=3, STABILIZATION6SETTINGS_WEAKLEVELING=4, STABILIZATION6SETTINGS_VIRTUALBAR=5, STABILIZATION6SETTINGS_ACRO=6, STABILIZATION6SETTINGS_RATTITUDE=7, STABILIZATION6SETTINGS_ALTITUDEHOLD=8, STABILIZATION6SETTINGS_ALTITUDEVARIO=9, STABILIZATION6SETTINGS_CRUISECONTROL=10 } Stabilization6SettingsOptions;
    /* Array element names for field Stabilization6Settings */
    typedef enum { STABILIZATION6SETTINGS_ROLL=0, STABILIZATION6SETTINGS_PITCH=1, STABILIZATION6SETTINGS_YAW=2, STABILIZATION6SETTINGS_THRUST=3 } Stabilization6SettingsElem;
    /* Number of elements for field Stabilization6Settings */
    static const quint32 STABILIZATION6SETTINGS_NUMELEM = 4;
    // Field FlightModePosition information
    /* Enumeration options for field FlightModePosition */
    typedef enum { FLIGHTMODEPOSITION_MANUAL=0, FLIGHTMODEPOSITION_STABILIZED1=1, FLIGHTMODEPOSITION_STABILIZED2=2, FLIGHTMODEPOSITION_STABILIZED3=3, FLIGHTMODEPOSITION_STABILIZED4=4, FLIGHTMODEPOSITION_STABILIZED5=5, FLIGHTMODEPOSITION_STABILIZED6=6, FLIGHTMODEPOSITION_POSITIONHOLD=7, FLIGHTMODEPOSITION_COURSELOCK=8, FLIGHTMODEPOSITION_POSITIONROAM=9, FLIGHTMODEPOSITION_HOMELEASH=10, FLIGHTMODEPOSITION_ABSOLUTEPOSITION=11, FLIGHTMODEPOSITION_RETURNTOBASE=12, FLIGHTMODEPOSITION_LAND=13, FLIGHTMODEPOSITION_PATHPLANNER=14, FLIGHTMODEPOSITION_POI=15, FLIGHTMODEPOSITION_AUTOCRUISE=16 } FlightModePositionOptions;
    /* Number of elements for field FlightModePosition */
    static const quint32 FLIGHTMODEPOSITION_NUMELEM = 6;
    // Field DisableSanityChecks information
    /* Enumeration options for field DisableSanityChecks */
    typedef enum { DISABLESANITYCHECKS_FALSE=0, DISABLESANITYCHECKS_TRUE=1 } DisableSanityChecksOptions;
    // Field ReturnToBaseNextCommand information
    /* Enumeration options for field ReturnToBaseNextCommand */
    typedef enum { RETURNTOBASENEXTCOMMAND_HOLD=0, RETURNTOBASENEXTCOMMAND_LAND=1 } ReturnToBaseNextCommandOptions;

  
    // Constants
    static const quint32 OBJID = 0x22D6BC8;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    FlightModeSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static FlightModeSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getReturnToBaseAltitudeOffset() const;
    Q_INVOKABLE float getLandingVelocity() const;
    Q_INVOKABLE float getPositionHoldOffset(quint32 index) const;
    Q_INVOKABLE float getPositionHoldOffset_Horizontal() const;
    Q_INVOKABLE float getPositionHoldOffset_Vertical() const;
    Q_INVOKABLE float getVarioControlLowPassAlpha() const;
    Q_INVOKABLE quint16 getArmedTimeout() const;
    Q_INVOKABLE quint16 getArmingSequenceTime() const;
    Q_INVOKABLE quint16 getDisarmingSequenceTime() const;
    Q_INVOKABLE quint8 getArming() const;
    Q_INVOKABLE quint8 getStabilization1Settings(quint32 index) const;
    Q_INVOKABLE quint8 getStabilization1Settings_Roll() const;
    Q_INVOKABLE quint8 getStabilization1Settings_Pitch() const;
    Q_INVOKABLE quint8 getStabilization1Settings_Yaw() const;
    Q_INVOKABLE quint8 getStabilization1Settings_Thrust() const;
    Q_INVOKABLE quint8 getStabilization2Settings(quint32 index) const;
    Q_INVOKABLE quint8 getStabilization2Settings_Roll() const;
    Q_INVOKABLE quint8 getStabilization2Settings_Pitch() const;
    Q_INVOKABLE quint8 getStabilization2Settings_Yaw() const;
    Q_INVOKABLE quint8 getStabilization2Settings_Thrust() const;
    Q_INVOKABLE quint8 getStabilization3Settings(quint32 index) const;
    Q_INVOKABLE quint8 getStabilization3Settings_Roll() const;
    Q_INVOKABLE quint8 getStabilization3Settings_Pitch() const;
    Q_INVOKABLE quint8 getStabilization3Settings_Yaw() const;
    Q_INVOKABLE quint8 getStabilization3Settings_Thrust() const;
    Q_INVOKABLE quint8 getStabilization4Settings(quint32 index) const;
    Q_INVOKABLE quint8 getStabilization4Settings_Roll() const;
    Q_INVOKABLE quint8 getStabilization4Settings_Pitch() const;
    Q_INVOKABLE quint8 getStabilization4Settings_Yaw() const;
    Q_INVOKABLE quint8 getStabilization4Settings_Thrust() const;
    Q_INVOKABLE quint8 getStabilization5Settings(quint32 index) const;
    Q_INVOKABLE quint8 getStabilization5Settings_Roll() const;
    Q_INVOKABLE quint8 getStabilization5Settings_Pitch() const;
    Q_INVOKABLE quint8 getStabilization5Settings_Yaw() const;
    Q_INVOKABLE quint8 getStabilization5Settings_Thrust() const;
    Q_INVOKABLE quint8 getStabilization6Settings(quint32 index) const;
    Q_INVOKABLE quint8 getStabilization6Settings_Roll() const;
    Q_INVOKABLE quint8 getStabilization6Settings_Pitch() const;
    Q_INVOKABLE quint8 getStabilization6Settings_Yaw() const;
    Q_INVOKABLE quint8 getStabilization6Settings_Thrust() const;
    Q_INVOKABLE quint8 getFlightModePosition(quint32 index) const;
    Q_INVOKABLE quint8 getFlightModePosition_0() const;
    Q_INVOKABLE quint8 getFlightModePosition_1() const;
    Q_INVOKABLE quint8 getFlightModePosition_2() const;
    Q_INVOKABLE quint8 getFlightModePosition_3() const;
    Q_INVOKABLE quint8 getFlightModePosition_4() const;
    Q_INVOKABLE quint8 getFlightModePosition_5() const;
    Q_INVOKABLE quint8 getDisableSanityChecks() const;
    Q_INVOKABLE quint8 getReturnToBaseNextCommand() const;


public slots:
    void setReturnToBaseAltitudeOffset(float value);
    void setLandingVelocity(float value);
    void setPositionHoldOffset(quint32 index, float value);
    void setPositionHoldOffset_Horizontal(float value);
    void setPositionHoldOffset_Vertical(float value);
    void setVarioControlLowPassAlpha(float value);
    void setArmedTimeout(quint16 value);
    void setArmingSequenceTime(quint16 value);
    void setDisarmingSequenceTime(quint16 value);
    void setArming(quint8 value);
    void setStabilization1Settings(quint32 index, quint8 value);
    void setStabilization1Settings_Roll(quint8 value);
    void setStabilization1Settings_Pitch(quint8 value);
    void setStabilization1Settings_Yaw(quint8 value);
    void setStabilization1Settings_Thrust(quint8 value);
    void setStabilization2Settings(quint32 index, quint8 value);
    void setStabilization2Settings_Roll(quint8 value);
    void setStabilization2Settings_Pitch(quint8 value);
    void setStabilization2Settings_Yaw(quint8 value);
    void setStabilization2Settings_Thrust(quint8 value);
    void setStabilization3Settings(quint32 index, quint8 value);
    void setStabilization3Settings_Roll(quint8 value);
    void setStabilization3Settings_Pitch(quint8 value);
    void setStabilization3Settings_Yaw(quint8 value);
    void setStabilization3Settings_Thrust(quint8 value);
    void setStabilization4Settings(quint32 index, quint8 value);
    void setStabilization4Settings_Roll(quint8 value);
    void setStabilization4Settings_Pitch(quint8 value);
    void setStabilization4Settings_Yaw(quint8 value);
    void setStabilization4Settings_Thrust(quint8 value);
    void setStabilization5Settings(quint32 index, quint8 value);
    void setStabilization5Settings_Roll(quint8 value);
    void setStabilization5Settings_Pitch(quint8 value);
    void setStabilization5Settings_Yaw(quint8 value);
    void setStabilization5Settings_Thrust(quint8 value);
    void setStabilization6Settings(quint32 index, quint8 value);
    void setStabilization6Settings_Roll(quint8 value);
    void setStabilization6Settings_Pitch(quint8 value);
    void setStabilization6Settings_Yaw(quint8 value);
    void setStabilization6Settings_Thrust(quint8 value);
    void setFlightModePosition(quint32 index, quint8 value);
    void setFlightModePosition_0(quint8 value);
    void setFlightModePosition_1(quint8 value);
    void setFlightModePosition_2(quint8 value);
    void setFlightModePosition_3(quint8 value);
    void setFlightModePosition_4(quint8 value);
    void setFlightModePosition_5(quint8 value);
    void setDisableSanityChecks(quint8 value);
    void setReturnToBaseNextCommand(quint8 value);


signals:
    void ReturnToBaseAltitudeOffsetChanged(float value);
    void LandingVelocityChanged(float value);
    void PositionHoldOffsetChanged(quint32 index, float value);
    void PositionHoldOffset_HorizontalChanged(float value);
    void PositionHoldOffset_VerticalChanged(float value);
    void VarioControlLowPassAlphaChanged(float value);
    void ArmedTimeoutChanged(quint16 value);
    void ArmingSequenceTimeChanged(quint16 value);
    void DisarmingSequenceTimeChanged(quint16 value);
    void ArmingChanged(quint8 value);
    void Stabilization1SettingsChanged(quint32 index, quint8 value);
    void Stabilization1Settings_RollChanged(quint8 value);
    void Stabilization1Settings_PitchChanged(quint8 value);
    void Stabilization1Settings_YawChanged(quint8 value);
    void Stabilization1Settings_ThrustChanged(quint8 value);
    void Stabilization2SettingsChanged(quint32 index, quint8 value);
    void Stabilization2Settings_RollChanged(quint8 value);
    void Stabilization2Settings_PitchChanged(quint8 value);
    void Stabilization2Settings_YawChanged(quint8 value);
    void Stabilization2Settings_ThrustChanged(quint8 value);
    void Stabilization3SettingsChanged(quint32 index, quint8 value);
    void Stabilization3Settings_RollChanged(quint8 value);
    void Stabilization3Settings_PitchChanged(quint8 value);
    void Stabilization3Settings_YawChanged(quint8 value);
    void Stabilization3Settings_ThrustChanged(quint8 value);
    void Stabilization4SettingsChanged(quint32 index, quint8 value);
    void Stabilization4Settings_RollChanged(quint8 value);
    void Stabilization4Settings_PitchChanged(quint8 value);
    void Stabilization4Settings_YawChanged(quint8 value);
    void Stabilization4Settings_ThrustChanged(quint8 value);
    void Stabilization5SettingsChanged(quint32 index, quint8 value);
    void Stabilization5Settings_RollChanged(quint8 value);
    void Stabilization5Settings_PitchChanged(quint8 value);
    void Stabilization5Settings_YawChanged(quint8 value);
    void Stabilization5Settings_ThrustChanged(quint8 value);
    void Stabilization6SettingsChanged(quint32 index, quint8 value);
    void Stabilization6Settings_RollChanged(quint8 value);
    void Stabilization6Settings_PitchChanged(quint8 value);
    void Stabilization6Settings_YawChanged(quint8 value);
    void Stabilization6Settings_ThrustChanged(quint8 value);
    void FlightModePositionChanged(quint32 index, quint8 value);
    void FlightModePosition_0Changed(quint8 value);
    void FlightModePosition_1Changed(quint8 value);
    void FlightModePosition_2Changed(quint8 value);
    void FlightModePosition_3Changed(quint8 value);
    void FlightModePosition_4Changed(quint8 value);
    void FlightModePosition_5Changed(quint8 value);
    void DisableSanityChecksChanged(quint8 value);
    void ReturnToBaseNextCommandChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // FLIGHTMODESETTINGS_H
