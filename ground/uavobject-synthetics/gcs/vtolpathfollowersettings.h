/**
 ******************************************************************************
 *
 * @file       vtolpathfollowersettings.h
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
#ifndef VTOLPATHFOLLOWERSETTINGS_H
#define VTOLPATHFOLLOWERSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT VtolPathFollowerSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float HorizontalVelMax READ getHorizontalVelMax WRITE setHorizontalVelMax NOTIFY HorizontalVelMaxChanged);
    Q_PROPERTY(float VerticalVelMax READ getVerticalVelMax WRITE setVerticalVelMax NOTIFY VerticalVelMaxChanged);
    Q_PROPERTY(float CourseFeedForward READ getCourseFeedForward WRITE setCourseFeedForward NOTIFY CourseFeedForwardChanged);
    Q_PROPERTY(float HorizontalPosP READ getHorizontalPosP WRITE setHorizontalPosP NOTIFY HorizontalPosPChanged);
    Q_PROPERTY(float VerticalPosP READ getVerticalPosP WRITE setVerticalPosP NOTIFY VerticalPosPChanged);
    Q_PROPERTY(float HorizontalVelPID_Kp READ getHorizontalVelPID_Kp WRITE setHorizontalVelPID_Kp NOTIFY HorizontalVelPID_KpChanged);
    Q_PROPERTY(float HorizontalVelPID_Ki READ getHorizontalVelPID_Ki WRITE setHorizontalVelPID_Ki NOTIFY HorizontalVelPID_KiChanged);
    Q_PROPERTY(float HorizontalVelPID_Kd READ getHorizontalVelPID_Kd WRITE setHorizontalVelPID_Kd NOTIFY HorizontalVelPID_KdChanged);
    Q_PROPERTY(float HorizontalVelPID_ILimit READ getHorizontalVelPID_ILimit WRITE setHorizontalVelPID_ILimit NOTIFY HorizontalVelPID_ILimitChanged);
    Q_PROPERTY(float VerticalVelPID_Kp READ getVerticalVelPID_Kp WRITE setVerticalVelPID_Kp NOTIFY VerticalVelPID_KpChanged);
    Q_PROPERTY(float VerticalVelPID_Ki READ getVerticalVelPID_Ki WRITE setVerticalVelPID_Ki NOTIFY VerticalVelPID_KiChanged);
    Q_PROPERTY(float VerticalVelPID_Kd READ getVerticalVelPID_Kd WRITE setVerticalVelPID_Kd NOTIFY VerticalVelPID_KdChanged);
    Q_PROPERTY(float VerticalVelPID_ILimit READ getVerticalVelPID_ILimit WRITE setVerticalVelPID_ILimit NOTIFY VerticalVelPID_ILimitChanged);
    Q_PROPERTY(float ThrustLimits_Min READ getThrustLimits_Min WRITE setThrustLimits_Min NOTIFY ThrustLimits_MinChanged);
    Q_PROPERTY(float ThrustLimits_Neutral READ getThrustLimits_Neutral WRITE setThrustLimits_Neutral NOTIFY ThrustLimits_NeutralChanged);
    Q_PROPERTY(float ThrustLimits_Max READ getThrustLimits_Max WRITE setThrustLimits_Max NOTIFY ThrustLimits_MaxChanged);
    Q_PROPERTY(float VelocityFeedforward READ getVelocityFeedforward WRITE setVelocityFeedforward NOTIFY VelocityFeedforwardChanged);
    Q_PROPERTY(float FlyawayEmergencyFallbackTriggerTime READ getFlyawayEmergencyFallbackTriggerTime WRITE setFlyawayEmergencyFallbackTriggerTime NOTIFY FlyawayEmergencyFallbackTriggerTimeChanged);
    Q_PROPERTY(float EmergencyFallbackAttitude_Roll READ getEmergencyFallbackAttitude_Roll WRITE setEmergencyFallbackAttitude_Roll NOTIFY EmergencyFallbackAttitude_RollChanged);
    Q_PROPERTY(float EmergencyFallbackAttitude_Pitch READ getEmergencyFallbackAttitude_Pitch WRITE setEmergencyFallbackAttitude_Pitch NOTIFY EmergencyFallbackAttitude_PitchChanged);
    Q_PROPERTY(float EmergencyFallbackYawRate_kP READ getEmergencyFallbackYawRate_kP WRITE setEmergencyFallbackYawRate_kP NOTIFY EmergencyFallbackYawRate_kPChanged);
    Q_PROPERTY(float EmergencyFallbackYawRate_Max READ getEmergencyFallbackYawRate_Max WRITE setEmergencyFallbackYawRate_Max NOTIFY EmergencyFallbackYawRate_MaxChanged);
    Q_PROPERTY(float MaxRollPitch READ getMaxRollPitch WRITE setMaxRollPitch NOTIFY MaxRollPitchChanged);
    Q_PROPERTY(float BrakeRate READ getBrakeRate WRITE setBrakeRate NOTIFY BrakeRateChanged);
    Q_PROPERTY(float BrakeMaxPitch READ getBrakeMaxPitch WRITE setBrakeMaxPitch NOTIFY BrakeMaxPitchChanged);
    Q_PROPERTY(float BrakeHorizontalVelPID_Kp READ getBrakeHorizontalVelPID_Kp WRITE setBrakeHorizontalVelPID_Kp NOTIFY BrakeHorizontalVelPID_KpChanged);
    Q_PROPERTY(float BrakeHorizontalVelPID_Ki READ getBrakeHorizontalVelPID_Ki WRITE setBrakeHorizontalVelPID_Ki NOTIFY BrakeHorizontalVelPID_KiChanged);
    Q_PROPERTY(float BrakeHorizontalVelPID_Kd READ getBrakeHorizontalVelPID_Kd WRITE setBrakeHorizontalVelPID_Kd NOTIFY BrakeHorizontalVelPID_KdChanged);
    Q_PROPERTY(float BrakeHorizontalVelPID_ILimit READ getBrakeHorizontalVelPID_ILimit WRITE setBrakeHorizontalVelPID_ILimit NOTIFY BrakeHorizontalVelPID_ILimitChanged);
    Q_PROPERTY(float BrakeVelocityFeedforward READ getBrakeVelocityFeedforward WRITE setBrakeVelocityFeedforward NOTIFY BrakeVelocityFeedforwardChanged);
    Q_PROPERTY(float LandVerticalVelPID_Kp READ getLandVerticalVelPID_Kp WRITE setLandVerticalVelPID_Kp NOTIFY LandVerticalVelPID_KpChanged);
    Q_PROPERTY(float LandVerticalVelPID_Ki READ getLandVerticalVelPID_Ki WRITE setLandVerticalVelPID_Ki NOTIFY LandVerticalVelPID_KiChanged);
    Q_PROPERTY(float LandVerticalVelPID_Kd READ getLandVerticalVelPID_Kd WRITE setLandVerticalVelPID_Kd NOTIFY LandVerticalVelPID_KdChanged);
    Q_PROPERTY(float LandVerticalVelPID_Beta READ getLandVerticalVelPID_Beta WRITE setLandVerticalVelPID_Beta NOTIFY LandVerticalVelPID_BetaChanged);
    Q_PROPERTY(quint16 UpdatePeriod READ getUpdatePeriod WRITE setUpdatePeriod NOTIFY UpdatePeriodChanged);
    Q_PROPERTY(quint8 TreatCustomCraftAs READ getTreatCustomCraftAs WRITE setTreatCustomCraftAs NOTIFY TreatCustomCraftAsChanged);
    Q_PROPERTY(quint8 ThrustControl READ getThrustControl WRITE setThrustControl NOTIFY ThrustControlChanged);
    Q_PROPERTY(quint8 YawControl READ getYawControl WRITE setYawControl NOTIFY YawControlChanged);
    Q_PROPERTY(quint8 FlyawayEmergencyFallback READ getFlyawayEmergencyFallback WRITE setFlyawayEmergencyFallback NOTIFY FlyawayEmergencyFallbackChanged);


public:
    // Field structure
    typedef struct {
        float HorizontalVelMax;
        float VerticalVelMax;
        float CourseFeedForward;
        float HorizontalPosP;
        float VerticalPosP;
        float HorizontalVelPID[4];
        float VerticalVelPID[4];
        float ThrustLimits[3];
        float VelocityFeedforward;
        float FlyawayEmergencyFallbackTriggerTime;
        float EmergencyFallbackAttitude[2];
        float EmergencyFallbackYawRate[2];
        float MaxRollPitch;
        float BrakeRate;
        float BrakeMaxPitch;
        float BrakeHorizontalVelPID[4];
        float BrakeVelocityFeedforward;
        float LandVerticalVelPID[4];
        quint16 UpdatePeriod;
        quint8 TreatCustomCraftAs;
        quint8 ThrustControl;
        quint8 YawControl;
        quint8 FlyawayEmergencyFallback;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field HorizontalVelMax information
    // Field VerticalVelMax information
    // Field CourseFeedForward information
    // Field HorizontalPosP information
    // Field VerticalPosP information
    // Field HorizontalVelPID information
    /* Array element names for field HorizontalVelPID */
    typedef enum { HORIZONTALVELPID_KP=0, HORIZONTALVELPID_KI=1, HORIZONTALVELPID_KD=2, HORIZONTALVELPID_ILIMIT=3 } HorizontalVelPIDElem;
    /* Number of elements for field HorizontalVelPID */
    static const quint32 HORIZONTALVELPID_NUMELEM = 4;
    // Field VerticalVelPID information
    /* Array element names for field VerticalVelPID */
    typedef enum { VERTICALVELPID_KP=0, VERTICALVELPID_KI=1, VERTICALVELPID_KD=2, VERTICALVELPID_ILIMIT=3 } VerticalVelPIDElem;
    /* Number of elements for field VerticalVelPID */
    static const quint32 VERTICALVELPID_NUMELEM = 4;
    // Field ThrustLimits information
    /* Array element names for field ThrustLimits */
    typedef enum { THRUSTLIMITS_MIN=0, THRUSTLIMITS_NEUTRAL=1, THRUSTLIMITS_MAX=2 } ThrustLimitsElem;
    /* Number of elements for field ThrustLimits */
    static const quint32 THRUSTLIMITS_NUMELEM = 3;
    // Field VelocityFeedforward information
    // Field FlyawayEmergencyFallbackTriggerTime information
    // Field EmergencyFallbackAttitude information
    /* Array element names for field EmergencyFallbackAttitude */
    typedef enum { EMERGENCYFALLBACKATTITUDE_ROLL=0, EMERGENCYFALLBACKATTITUDE_PITCH=1 } EmergencyFallbackAttitudeElem;
    /* Number of elements for field EmergencyFallbackAttitude */
    static const quint32 EMERGENCYFALLBACKATTITUDE_NUMELEM = 2;
    // Field EmergencyFallbackYawRate information
    /* Array element names for field EmergencyFallbackYawRate */
    typedef enum { EMERGENCYFALLBACKYAWRATE_KP=0, EMERGENCYFALLBACKYAWRATE_MAX=1 } EmergencyFallbackYawRateElem;
    /* Number of elements for field EmergencyFallbackYawRate */
    static const quint32 EMERGENCYFALLBACKYAWRATE_NUMELEM = 2;
    // Field MaxRollPitch information
    // Field BrakeRate information
    // Field BrakeMaxPitch information
    // Field BrakeHorizontalVelPID information
    /* Array element names for field BrakeHorizontalVelPID */
    typedef enum { BRAKEHORIZONTALVELPID_KP=0, BRAKEHORIZONTALVELPID_KI=1, BRAKEHORIZONTALVELPID_KD=2, BRAKEHORIZONTALVELPID_ILIMIT=3 } BrakeHorizontalVelPIDElem;
    /* Number of elements for field BrakeHorizontalVelPID */
    static const quint32 BRAKEHORIZONTALVELPID_NUMELEM = 4;
    // Field BrakeVelocityFeedforward information
    // Field LandVerticalVelPID information
    /* Array element names for field LandVerticalVelPID */
    typedef enum { LANDVERTICALVELPID_KP=0, LANDVERTICALVELPID_KI=1, LANDVERTICALVELPID_KD=2, LANDVERTICALVELPID_BETA=3 } LandVerticalVelPIDElem;
    /* Number of elements for field LandVerticalVelPID */
    static const quint32 LANDVERTICALVELPID_NUMELEM = 4;
    // Field UpdatePeriod information
    // Field TreatCustomCraftAs information
    /* Enumeration options for field TreatCustomCraftAs */
    typedef enum { TREATCUSTOMCRAFTAS_FIXEDWING=0, TREATCUSTOMCRAFTAS_VTOL=1, TREATCUSTOMCRAFTAS_GROUND=2 } TreatCustomCraftAsOptions;
    // Field ThrustControl information
    /* Enumeration options for field ThrustControl */
    typedef enum { THRUSTCONTROL_MANUAL=0, THRUSTCONTROL_AUTO=1 } ThrustControlOptions;
    // Field YawControl information
    /* Enumeration options for field YawControl */
    typedef enum { YAWCONTROL_MANUAL=0, YAWCONTROL_TAILIN=1, YAWCONTROL_MOVEMENTDIRECTION=2, YAWCONTROL_PATHDIRECTION=3, YAWCONTROL_POI=4 } YawControlOptions;
    // Field FlyawayEmergencyFallback information
    /* Enumeration options for field FlyawayEmergencyFallback */
    typedef enum { FLYAWAYEMERGENCYFALLBACK_DISABLED=0, FLYAWAYEMERGENCYFALLBACK_ENABLED=1, FLYAWAYEMERGENCYFALLBACK_ALWAYS=2, FLYAWAYEMERGENCYFALLBACK_DEBUGTEST=3 } FlyawayEmergencyFallbackOptions;

  
    // Constants
    static const quint32 OBJID = 0xFB3EAB06;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    VtolPathFollowerSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static VtolPathFollowerSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getHorizontalVelMax() const;
    Q_INVOKABLE float getVerticalVelMax() const;
    Q_INVOKABLE float getCourseFeedForward() const;
    Q_INVOKABLE float getHorizontalPosP() const;
    Q_INVOKABLE float getVerticalPosP() const;
    Q_INVOKABLE float getHorizontalVelPID(quint32 index) const;
    Q_INVOKABLE float getHorizontalVelPID_Kp() const;
    Q_INVOKABLE float getHorizontalVelPID_Ki() const;
    Q_INVOKABLE float getHorizontalVelPID_Kd() const;
    Q_INVOKABLE float getHorizontalVelPID_ILimit() const;
    Q_INVOKABLE float getVerticalVelPID(quint32 index) const;
    Q_INVOKABLE float getVerticalVelPID_Kp() const;
    Q_INVOKABLE float getVerticalVelPID_Ki() const;
    Q_INVOKABLE float getVerticalVelPID_Kd() const;
    Q_INVOKABLE float getVerticalVelPID_ILimit() const;
    Q_INVOKABLE float getThrustLimits(quint32 index) const;
    Q_INVOKABLE float getThrustLimits_Min() const;
    Q_INVOKABLE float getThrustLimits_Neutral() const;
    Q_INVOKABLE float getThrustLimits_Max() const;
    Q_INVOKABLE float getVelocityFeedforward() const;
    Q_INVOKABLE float getFlyawayEmergencyFallbackTriggerTime() const;
    Q_INVOKABLE float getEmergencyFallbackAttitude(quint32 index) const;
    Q_INVOKABLE float getEmergencyFallbackAttitude_Roll() const;
    Q_INVOKABLE float getEmergencyFallbackAttitude_Pitch() const;
    Q_INVOKABLE float getEmergencyFallbackYawRate(quint32 index) const;
    Q_INVOKABLE float getEmergencyFallbackYawRate_kP() const;
    Q_INVOKABLE float getEmergencyFallbackYawRate_Max() const;
    Q_INVOKABLE float getMaxRollPitch() const;
    Q_INVOKABLE float getBrakeRate() const;
    Q_INVOKABLE float getBrakeMaxPitch() const;
    Q_INVOKABLE float getBrakeHorizontalVelPID(quint32 index) const;
    Q_INVOKABLE float getBrakeHorizontalVelPID_Kp() const;
    Q_INVOKABLE float getBrakeHorizontalVelPID_Ki() const;
    Q_INVOKABLE float getBrakeHorizontalVelPID_Kd() const;
    Q_INVOKABLE float getBrakeHorizontalVelPID_ILimit() const;
    Q_INVOKABLE float getBrakeVelocityFeedforward() const;
    Q_INVOKABLE float getLandVerticalVelPID(quint32 index) const;
    Q_INVOKABLE float getLandVerticalVelPID_Kp() const;
    Q_INVOKABLE float getLandVerticalVelPID_Ki() const;
    Q_INVOKABLE float getLandVerticalVelPID_Kd() const;
    Q_INVOKABLE float getLandVerticalVelPID_Beta() const;
    Q_INVOKABLE quint16 getUpdatePeriod() const;
    Q_INVOKABLE quint8 getTreatCustomCraftAs() const;
    Q_INVOKABLE quint8 getThrustControl() const;
    Q_INVOKABLE quint8 getYawControl() const;
    Q_INVOKABLE quint8 getFlyawayEmergencyFallback() const;


public slots:
    void setHorizontalVelMax(float value);
    void setVerticalVelMax(float value);
    void setCourseFeedForward(float value);
    void setHorizontalPosP(float value);
    void setVerticalPosP(float value);
    void setHorizontalVelPID(quint32 index, float value);
    void setHorizontalVelPID_Kp(float value);
    void setHorizontalVelPID_Ki(float value);
    void setHorizontalVelPID_Kd(float value);
    void setHorizontalVelPID_ILimit(float value);
    void setVerticalVelPID(quint32 index, float value);
    void setVerticalVelPID_Kp(float value);
    void setVerticalVelPID_Ki(float value);
    void setVerticalVelPID_Kd(float value);
    void setVerticalVelPID_ILimit(float value);
    void setThrustLimits(quint32 index, float value);
    void setThrustLimits_Min(float value);
    void setThrustLimits_Neutral(float value);
    void setThrustLimits_Max(float value);
    void setVelocityFeedforward(float value);
    void setFlyawayEmergencyFallbackTriggerTime(float value);
    void setEmergencyFallbackAttitude(quint32 index, float value);
    void setEmergencyFallbackAttitude_Roll(float value);
    void setEmergencyFallbackAttitude_Pitch(float value);
    void setEmergencyFallbackYawRate(quint32 index, float value);
    void setEmergencyFallbackYawRate_kP(float value);
    void setEmergencyFallbackYawRate_Max(float value);
    void setMaxRollPitch(float value);
    void setBrakeRate(float value);
    void setBrakeMaxPitch(float value);
    void setBrakeHorizontalVelPID(quint32 index, float value);
    void setBrakeHorizontalVelPID_Kp(float value);
    void setBrakeHorizontalVelPID_Ki(float value);
    void setBrakeHorizontalVelPID_Kd(float value);
    void setBrakeHorizontalVelPID_ILimit(float value);
    void setBrakeVelocityFeedforward(float value);
    void setLandVerticalVelPID(quint32 index, float value);
    void setLandVerticalVelPID_Kp(float value);
    void setLandVerticalVelPID_Ki(float value);
    void setLandVerticalVelPID_Kd(float value);
    void setLandVerticalVelPID_Beta(float value);
    void setUpdatePeriod(quint16 value);
    void setTreatCustomCraftAs(quint8 value);
    void setThrustControl(quint8 value);
    void setYawControl(quint8 value);
    void setFlyawayEmergencyFallback(quint8 value);


signals:
    void HorizontalVelMaxChanged(float value);
    void VerticalVelMaxChanged(float value);
    void CourseFeedForwardChanged(float value);
    void HorizontalPosPChanged(float value);
    void VerticalPosPChanged(float value);
    void HorizontalVelPIDChanged(quint32 index, float value);
    void HorizontalVelPID_KpChanged(float value);
    void HorizontalVelPID_KiChanged(float value);
    void HorizontalVelPID_KdChanged(float value);
    void HorizontalVelPID_ILimitChanged(float value);
    void VerticalVelPIDChanged(quint32 index, float value);
    void VerticalVelPID_KpChanged(float value);
    void VerticalVelPID_KiChanged(float value);
    void VerticalVelPID_KdChanged(float value);
    void VerticalVelPID_ILimitChanged(float value);
    void ThrustLimitsChanged(quint32 index, float value);
    void ThrustLimits_MinChanged(float value);
    void ThrustLimits_NeutralChanged(float value);
    void ThrustLimits_MaxChanged(float value);
    void VelocityFeedforwardChanged(float value);
    void FlyawayEmergencyFallbackTriggerTimeChanged(float value);
    void EmergencyFallbackAttitudeChanged(quint32 index, float value);
    void EmergencyFallbackAttitude_RollChanged(float value);
    void EmergencyFallbackAttitude_PitchChanged(float value);
    void EmergencyFallbackYawRateChanged(quint32 index, float value);
    void EmergencyFallbackYawRate_kPChanged(float value);
    void EmergencyFallbackYawRate_MaxChanged(float value);
    void MaxRollPitchChanged(float value);
    void BrakeRateChanged(float value);
    void BrakeMaxPitchChanged(float value);
    void BrakeHorizontalVelPIDChanged(quint32 index, float value);
    void BrakeHorizontalVelPID_KpChanged(float value);
    void BrakeHorizontalVelPID_KiChanged(float value);
    void BrakeHorizontalVelPID_KdChanged(float value);
    void BrakeHorizontalVelPID_ILimitChanged(float value);
    void BrakeVelocityFeedforwardChanged(float value);
    void LandVerticalVelPIDChanged(quint32 index, float value);
    void LandVerticalVelPID_KpChanged(float value);
    void LandVerticalVelPID_KiChanged(float value);
    void LandVerticalVelPID_KdChanged(float value);
    void LandVerticalVelPID_BetaChanged(float value);
    void UpdatePeriodChanged(quint16 value);
    void TreatCustomCraftAsChanged(quint8 value);
    void ThrustControlChanged(quint8 value);
    void YawControlChanged(quint8 value);
    void FlyawayEmergencyFallbackChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // VTOLPATHFOLLOWERSETTINGS_H
