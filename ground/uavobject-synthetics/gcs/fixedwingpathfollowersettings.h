/**
 ******************************************************************************
 *
 * @file       fixedwingpathfollowersettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: fixedwingpathfollowersettings.xml. 
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
#ifndef FIXEDWINGPATHFOLLOWERSETTINGS_H
#define FIXEDWINGPATHFOLLOWERSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT FixedWingPathFollowerSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float HorizontalVelMax READ getHorizontalVelMax WRITE setHorizontalVelMax NOTIFY HorizontalVelMaxChanged);
    Q_PROPERTY(float HorizontalVelMin READ getHorizontalVelMin WRITE setHorizontalVelMin NOTIFY HorizontalVelMinChanged);
    Q_PROPERTY(float VerticalVelMax READ getVerticalVelMax WRITE setVerticalVelMax NOTIFY VerticalVelMaxChanged);
    Q_PROPERTY(float CourseFeedForward READ getCourseFeedForward WRITE setCourseFeedForward NOTIFY CourseFeedForwardChanged);
    Q_PROPERTY(float ReverseCourseOverlap READ getReverseCourseOverlap WRITE setReverseCourseOverlap NOTIFY ReverseCourseOverlapChanged);
    Q_PROPERTY(float HorizontalPosP READ getHorizontalPosP WRITE setHorizontalPosP NOTIFY HorizontalPosPChanged);
    Q_PROPERTY(float VerticalPosP READ getVerticalPosP WRITE setVerticalPosP NOTIFY VerticalPosPChanged);
    Q_PROPERTY(float CoursePI_Kp READ getCoursePI_Kp WRITE setCoursePI_Kp NOTIFY CoursePI_KpChanged);
    Q_PROPERTY(float CoursePI_Ki READ getCoursePI_Ki WRITE setCoursePI_Ki NOTIFY CoursePI_KiChanged);
    Q_PROPERTY(float CoursePI_ILimit READ getCoursePI_ILimit WRITE setCoursePI_ILimit NOTIFY CoursePI_ILimitChanged);
    Q_PROPERTY(float SpeedPI_Kp READ getSpeedPI_Kp WRITE setSpeedPI_Kp NOTIFY SpeedPI_KpChanged);
    Q_PROPERTY(float SpeedPI_Ki READ getSpeedPI_Ki WRITE setSpeedPI_Ki NOTIFY SpeedPI_KiChanged);
    Q_PROPERTY(float SpeedPI_ILimit READ getSpeedPI_ILimit WRITE setSpeedPI_ILimit NOTIFY SpeedPI_ILimitChanged);
    Q_PROPERTY(float VerticalToPitchCrossFeed_Kp READ getVerticalToPitchCrossFeed_Kp WRITE setVerticalToPitchCrossFeed_Kp NOTIFY VerticalToPitchCrossFeed_KpChanged);
    Q_PROPERTY(float VerticalToPitchCrossFeed_Max READ getVerticalToPitchCrossFeed_Max WRITE setVerticalToPitchCrossFeed_Max NOTIFY VerticalToPitchCrossFeed_MaxChanged);
    Q_PROPERTY(float AirspeedToPowerCrossFeed_Kp READ getAirspeedToPowerCrossFeed_Kp WRITE setAirspeedToPowerCrossFeed_Kp NOTIFY AirspeedToPowerCrossFeed_KpChanged);
    Q_PROPERTY(float AirspeedToPowerCrossFeed_Max READ getAirspeedToPowerCrossFeed_Max WRITE setAirspeedToPowerCrossFeed_Max NOTIFY AirspeedToPowerCrossFeed_MaxChanged);
    Q_PROPERTY(float PowerPI_Kp READ getPowerPI_Kp WRITE setPowerPI_Kp NOTIFY PowerPI_KpChanged);
    Q_PROPERTY(float PowerPI_Ki READ getPowerPI_Ki WRITE setPowerPI_Ki NOTIFY PowerPI_KiChanged);
    Q_PROPERTY(float PowerPI_ILimit READ getPowerPI_ILimit WRITE setPowerPI_ILimit NOTIFY PowerPI_ILimitChanged);
    Q_PROPERTY(float RollLimit_Min READ getRollLimit_Min WRITE setRollLimit_Min NOTIFY RollLimit_MinChanged);
    Q_PROPERTY(float RollLimit_Neutral READ getRollLimit_Neutral WRITE setRollLimit_Neutral NOTIFY RollLimit_NeutralChanged);
    Q_PROPERTY(float RollLimit_Max READ getRollLimit_Max WRITE setRollLimit_Max NOTIFY RollLimit_MaxChanged);
    Q_PROPERTY(float PitchLimit_Min READ getPitchLimit_Min WRITE setPitchLimit_Min NOTIFY PitchLimit_MinChanged);
    Q_PROPERTY(float PitchLimit_Neutral READ getPitchLimit_Neutral WRITE setPitchLimit_Neutral NOTIFY PitchLimit_NeutralChanged);
    Q_PROPERTY(float PitchLimit_Max READ getPitchLimit_Max WRITE setPitchLimit_Max NOTIFY PitchLimit_MaxChanged);
    Q_PROPERTY(float ThrustLimit_Min READ getThrustLimit_Min WRITE setThrustLimit_Min NOTIFY ThrustLimit_MinChanged);
    Q_PROPERTY(float ThrustLimit_Neutral READ getThrustLimit_Neutral WRITE setThrustLimit_Neutral NOTIFY ThrustLimit_NeutralChanged);
    Q_PROPERTY(float ThrustLimit_Max READ getThrustLimit_Max WRITE setThrustLimit_Max NOTIFY ThrustLimit_MaxChanged);
    Q_PROPERTY(float Safetymargins_Wind READ getSafetymargins_Wind WRITE setSafetymargins_Wind NOTIFY Safetymargins_WindChanged);
    Q_PROPERTY(float Safetymargins_Stallspeed READ getSafetymargins_Stallspeed WRITE setSafetymargins_Stallspeed NOTIFY Safetymargins_StallspeedChanged);
    Q_PROPERTY(float Safetymargins_Lowspeed READ getSafetymargins_Lowspeed WRITE setSafetymargins_Lowspeed NOTIFY Safetymargins_LowspeedChanged);
    Q_PROPERTY(float Safetymargins_Highspeed READ getSafetymargins_Highspeed WRITE setSafetymargins_Highspeed NOTIFY Safetymargins_HighspeedChanged);
    Q_PROPERTY(float Safetymargins_Overspeed READ getSafetymargins_Overspeed WRITE setSafetymargins_Overspeed NOTIFY Safetymargins_OverspeedChanged);
    Q_PROPERTY(float Safetymargins_Lowpower READ getSafetymargins_Lowpower WRITE setSafetymargins_Lowpower NOTIFY Safetymargins_LowpowerChanged);
    Q_PROPERTY(float Safetymargins_Highpower READ getSafetymargins_Highpower WRITE setSafetymargins_Highpower NOTIFY Safetymargins_HighpowerChanged);
    Q_PROPERTY(float Safetymargins_Pitchcontrol READ getSafetymargins_Pitchcontrol WRITE setSafetymargins_Pitchcontrol NOTIFY Safetymargins_PitchcontrolChanged);
    Q_PROPERTY(qint32 UpdatePeriod READ getUpdatePeriod WRITE setUpdatePeriod NOTIFY UpdatePeriodChanged);


public:
    // Field structure
    typedef struct {
        float HorizontalVelMax;
        float HorizontalVelMin;
        float VerticalVelMax;
        float CourseFeedForward;
        float ReverseCourseOverlap;
        float HorizontalPosP;
        float VerticalPosP;
        float CoursePI[3];
        float SpeedPI[3];
        float VerticalToPitchCrossFeed[2];
        float AirspeedToPowerCrossFeed[2];
        float PowerPI[3];
        float RollLimit[3];
        float PitchLimit[3];
        float ThrustLimit[3];
        float Safetymargins[8];
        qint32 UpdatePeriod;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field HorizontalVelMax information
    // Field HorizontalVelMin information
    // Field VerticalVelMax information
    // Field CourseFeedForward information
    // Field ReverseCourseOverlap information
    // Field HorizontalPosP information
    // Field VerticalPosP information
    // Field CoursePI information
    /* Array element names for field CoursePI */
    typedef enum { COURSEPI_KP=0, COURSEPI_KI=1, COURSEPI_ILIMIT=2 } CoursePIElem;
    /* Number of elements for field CoursePI */
    static const quint32 COURSEPI_NUMELEM = 3;
    // Field SpeedPI information
    /* Array element names for field SpeedPI */
    typedef enum { SPEEDPI_KP=0, SPEEDPI_KI=1, SPEEDPI_ILIMIT=2 } SpeedPIElem;
    /* Number of elements for field SpeedPI */
    static const quint32 SPEEDPI_NUMELEM = 3;
    // Field VerticalToPitchCrossFeed information
    /* Array element names for field VerticalToPitchCrossFeed */
    typedef enum { VERTICALTOPITCHCROSSFEED_KP=0, VERTICALTOPITCHCROSSFEED_MAX=1 } VerticalToPitchCrossFeedElem;
    /* Number of elements for field VerticalToPitchCrossFeed */
    static const quint32 VERTICALTOPITCHCROSSFEED_NUMELEM = 2;
    // Field AirspeedToPowerCrossFeed information
    /* Array element names for field AirspeedToPowerCrossFeed */
    typedef enum { AIRSPEEDTOPOWERCROSSFEED_KP=0, AIRSPEEDTOPOWERCROSSFEED_MAX=1 } AirspeedToPowerCrossFeedElem;
    /* Number of elements for field AirspeedToPowerCrossFeed */
    static const quint32 AIRSPEEDTOPOWERCROSSFEED_NUMELEM = 2;
    // Field PowerPI information
    /* Array element names for field PowerPI */
    typedef enum { POWERPI_KP=0, POWERPI_KI=1, POWERPI_ILIMIT=2 } PowerPIElem;
    /* Number of elements for field PowerPI */
    static const quint32 POWERPI_NUMELEM = 3;
    // Field RollLimit information
    /* Array element names for field RollLimit */
    typedef enum { ROLLLIMIT_MIN=0, ROLLLIMIT_NEUTRAL=1, ROLLLIMIT_MAX=2 } RollLimitElem;
    /* Number of elements for field RollLimit */
    static const quint32 ROLLLIMIT_NUMELEM = 3;
    // Field PitchLimit information
    /* Array element names for field PitchLimit */
    typedef enum { PITCHLIMIT_MIN=0, PITCHLIMIT_NEUTRAL=1, PITCHLIMIT_MAX=2 } PitchLimitElem;
    /* Number of elements for field PitchLimit */
    static const quint32 PITCHLIMIT_NUMELEM = 3;
    // Field ThrustLimit information
    /* Array element names for field ThrustLimit */
    typedef enum { THRUSTLIMIT_MIN=0, THRUSTLIMIT_NEUTRAL=1, THRUSTLIMIT_MAX=2 } ThrustLimitElem;
    /* Number of elements for field ThrustLimit */
    static const quint32 THRUSTLIMIT_NUMELEM = 3;
    // Field Safetymargins information
    /* Array element names for field Safetymargins */
    typedef enum { SAFETYMARGINS_WIND=0, SAFETYMARGINS_STALLSPEED=1, SAFETYMARGINS_LOWSPEED=2, SAFETYMARGINS_HIGHSPEED=3, SAFETYMARGINS_OVERSPEED=4, SAFETYMARGINS_LOWPOWER=5, SAFETYMARGINS_HIGHPOWER=6, SAFETYMARGINS_PITCHCONTROL=7 } SafetymarginsElem;
    /* Number of elements for field Safetymargins */
    static const quint32 SAFETYMARGINS_NUMELEM = 8;
    // Field UpdatePeriod information

  
    // Constants
    static const quint32 OBJID = 0x38AD8B0A;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    FixedWingPathFollowerSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static FixedWingPathFollowerSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getHorizontalVelMax() const;
    Q_INVOKABLE float getHorizontalVelMin() const;
    Q_INVOKABLE float getVerticalVelMax() const;
    Q_INVOKABLE float getCourseFeedForward() const;
    Q_INVOKABLE float getReverseCourseOverlap() const;
    Q_INVOKABLE float getHorizontalPosP() const;
    Q_INVOKABLE float getVerticalPosP() const;
    Q_INVOKABLE float getCoursePI(quint32 index) const;
    Q_INVOKABLE float getCoursePI_Kp() const;
    Q_INVOKABLE float getCoursePI_Ki() const;
    Q_INVOKABLE float getCoursePI_ILimit() const;
    Q_INVOKABLE float getSpeedPI(quint32 index) const;
    Q_INVOKABLE float getSpeedPI_Kp() const;
    Q_INVOKABLE float getSpeedPI_Ki() const;
    Q_INVOKABLE float getSpeedPI_ILimit() const;
    Q_INVOKABLE float getVerticalToPitchCrossFeed(quint32 index) const;
    Q_INVOKABLE float getVerticalToPitchCrossFeed_Kp() const;
    Q_INVOKABLE float getVerticalToPitchCrossFeed_Max() const;
    Q_INVOKABLE float getAirspeedToPowerCrossFeed(quint32 index) const;
    Q_INVOKABLE float getAirspeedToPowerCrossFeed_Kp() const;
    Q_INVOKABLE float getAirspeedToPowerCrossFeed_Max() const;
    Q_INVOKABLE float getPowerPI(quint32 index) const;
    Q_INVOKABLE float getPowerPI_Kp() const;
    Q_INVOKABLE float getPowerPI_Ki() const;
    Q_INVOKABLE float getPowerPI_ILimit() const;
    Q_INVOKABLE float getRollLimit(quint32 index) const;
    Q_INVOKABLE float getRollLimit_Min() const;
    Q_INVOKABLE float getRollLimit_Neutral() const;
    Q_INVOKABLE float getRollLimit_Max() const;
    Q_INVOKABLE float getPitchLimit(quint32 index) const;
    Q_INVOKABLE float getPitchLimit_Min() const;
    Q_INVOKABLE float getPitchLimit_Neutral() const;
    Q_INVOKABLE float getPitchLimit_Max() const;
    Q_INVOKABLE float getThrustLimit(quint32 index) const;
    Q_INVOKABLE float getThrustLimit_Min() const;
    Q_INVOKABLE float getThrustLimit_Neutral() const;
    Q_INVOKABLE float getThrustLimit_Max() const;
    Q_INVOKABLE float getSafetymargins(quint32 index) const;
    Q_INVOKABLE float getSafetymargins_Wind() const;
    Q_INVOKABLE float getSafetymargins_Stallspeed() const;
    Q_INVOKABLE float getSafetymargins_Lowspeed() const;
    Q_INVOKABLE float getSafetymargins_Highspeed() const;
    Q_INVOKABLE float getSafetymargins_Overspeed() const;
    Q_INVOKABLE float getSafetymargins_Lowpower() const;
    Q_INVOKABLE float getSafetymargins_Highpower() const;
    Q_INVOKABLE float getSafetymargins_Pitchcontrol() const;
    Q_INVOKABLE qint32 getUpdatePeriod() const;


public slots:
    void setHorizontalVelMax(float value);
    void setHorizontalVelMin(float value);
    void setVerticalVelMax(float value);
    void setCourseFeedForward(float value);
    void setReverseCourseOverlap(float value);
    void setHorizontalPosP(float value);
    void setVerticalPosP(float value);
    void setCoursePI(quint32 index, float value);
    void setCoursePI_Kp(float value);
    void setCoursePI_Ki(float value);
    void setCoursePI_ILimit(float value);
    void setSpeedPI(quint32 index, float value);
    void setSpeedPI_Kp(float value);
    void setSpeedPI_Ki(float value);
    void setSpeedPI_ILimit(float value);
    void setVerticalToPitchCrossFeed(quint32 index, float value);
    void setVerticalToPitchCrossFeed_Kp(float value);
    void setVerticalToPitchCrossFeed_Max(float value);
    void setAirspeedToPowerCrossFeed(quint32 index, float value);
    void setAirspeedToPowerCrossFeed_Kp(float value);
    void setAirspeedToPowerCrossFeed_Max(float value);
    void setPowerPI(quint32 index, float value);
    void setPowerPI_Kp(float value);
    void setPowerPI_Ki(float value);
    void setPowerPI_ILimit(float value);
    void setRollLimit(quint32 index, float value);
    void setRollLimit_Min(float value);
    void setRollLimit_Neutral(float value);
    void setRollLimit_Max(float value);
    void setPitchLimit(quint32 index, float value);
    void setPitchLimit_Min(float value);
    void setPitchLimit_Neutral(float value);
    void setPitchLimit_Max(float value);
    void setThrustLimit(quint32 index, float value);
    void setThrustLimit_Min(float value);
    void setThrustLimit_Neutral(float value);
    void setThrustLimit_Max(float value);
    void setSafetymargins(quint32 index, float value);
    void setSafetymargins_Wind(float value);
    void setSafetymargins_Stallspeed(float value);
    void setSafetymargins_Lowspeed(float value);
    void setSafetymargins_Highspeed(float value);
    void setSafetymargins_Overspeed(float value);
    void setSafetymargins_Lowpower(float value);
    void setSafetymargins_Highpower(float value);
    void setSafetymargins_Pitchcontrol(float value);
    void setUpdatePeriod(qint32 value);


signals:
    void HorizontalVelMaxChanged(float value);
    void HorizontalVelMinChanged(float value);
    void VerticalVelMaxChanged(float value);
    void CourseFeedForwardChanged(float value);
    void ReverseCourseOverlapChanged(float value);
    void HorizontalPosPChanged(float value);
    void VerticalPosPChanged(float value);
    void CoursePIChanged(quint32 index, float value);
    void CoursePI_KpChanged(float value);
    void CoursePI_KiChanged(float value);
    void CoursePI_ILimitChanged(float value);
    void SpeedPIChanged(quint32 index, float value);
    void SpeedPI_KpChanged(float value);
    void SpeedPI_KiChanged(float value);
    void SpeedPI_ILimitChanged(float value);
    void VerticalToPitchCrossFeedChanged(quint32 index, float value);
    void VerticalToPitchCrossFeed_KpChanged(float value);
    void VerticalToPitchCrossFeed_MaxChanged(float value);
    void AirspeedToPowerCrossFeedChanged(quint32 index, float value);
    void AirspeedToPowerCrossFeed_KpChanged(float value);
    void AirspeedToPowerCrossFeed_MaxChanged(float value);
    void PowerPIChanged(quint32 index, float value);
    void PowerPI_KpChanged(float value);
    void PowerPI_KiChanged(float value);
    void PowerPI_ILimitChanged(float value);
    void RollLimitChanged(quint32 index, float value);
    void RollLimit_MinChanged(float value);
    void RollLimit_NeutralChanged(float value);
    void RollLimit_MaxChanged(float value);
    void PitchLimitChanged(quint32 index, float value);
    void PitchLimit_MinChanged(float value);
    void PitchLimit_NeutralChanged(float value);
    void PitchLimit_MaxChanged(float value);
    void ThrustLimitChanged(quint32 index, float value);
    void ThrustLimit_MinChanged(float value);
    void ThrustLimit_NeutralChanged(float value);
    void ThrustLimit_MaxChanged(float value);
    void SafetymarginsChanged(quint32 index, float value);
    void Safetymargins_WindChanged(float value);
    void Safetymargins_StallspeedChanged(float value);
    void Safetymargins_LowspeedChanged(float value);
    void Safetymargins_HighspeedChanged(float value);
    void Safetymargins_OverspeedChanged(float value);
    void Safetymargins_LowpowerChanged(float value);
    void Safetymargins_HighpowerChanged(float value);
    void Safetymargins_PitchcontrolChanged(float value);
    void UpdatePeriodChanged(qint32 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // FIXEDWINGPATHFOLLOWERSETTINGS_H
