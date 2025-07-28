/**
 ******************************************************************************
 *
 * @file       groundpathfollowersettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: groundpathfollowersettings.xml. 
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
#ifndef GROUNDPATHFOLLOWERSETTINGS_H
#define GROUNDPATHFOLLOWERSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT GroundPathFollowerSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float HorizontalVelMax READ getHorizontalVelMax WRITE setHorizontalVelMax NOTIFY HorizontalVelMaxChanged);
    Q_PROPERTY(float HorizontalVelMin READ getHorizontalVelMin WRITE setHorizontalVelMin NOTIFY HorizontalVelMinChanged);
    Q_PROPERTY(float CourseFeedForward READ getCourseFeedForward WRITE setCourseFeedForward NOTIFY CourseFeedForwardChanged);
    Q_PROPERTY(float VelocityFeedForward READ getVelocityFeedForward WRITE setVelocityFeedForward NOTIFY VelocityFeedForwardChanged);
    Q_PROPERTY(float HorizontalPosP READ getHorizontalPosP WRITE setHorizontalPosP NOTIFY HorizontalPosPChanged);
    Q_PROPERTY(float SpeedPI_Kp READ getSpeedPI_Kp WRITE setSpeedPI_Kp NOTIFY SpeedPI_KpChanged);
    Q_PROPERTY(float SpeedPI_Ki READ getSpeedPI_Ki WRITE setSpeedPI_Ki NOTIFY SpeedPI_KiChanged);
    Q_PROPERTY(float SpeedPI_Kd READ getSpeedPI_Kd WRITE setSpeedPI_Kd NOTIFY SpeedPI_KdChanged);
    Q_PROPERTY(float SpeedPI_Beta READ getSpeedPI_Beta WRITE setSpeedPI_Beta NOTIFY SpeedPI_BetaChanged);
    Q_PROPERTY(float ThrustLimit_Min READ getThrustLimit_Min WRITE setThrustLimit_Min NOTIFY ThrustLimit_MinChanged);
    Q_PROPERTY(float ThrustLimit_SlowForward READ getThrustLimit_SlowForward WRITE setThrustLimit_SlowForward NOTIFY ThrustLimit_SlowForwardChanged);
    Q_PROPERTY(float ThrustLimit_Max READ getThrustLimit_Max WRITE setThrustLimit_Max NOTIFY ThrustLimit_MaxChanged);
    Q_PROPERTY(qint32 UpdatePeriod READ getUpdatePeriod WRITE setUpdatePeriod NOTIFY UpdatePeriodChanged);


public:
    // Field structure
    typedef struct {
        float HorizontalVelMax;
        float HorizontalVelMin;
        float CourseFeedForward;
        float VelocityFeedForward;
        float HorizontalPosP;
        float SpeedPI[4];
        float ThrustLimit[3];
        qint32 UpdatePeriod;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field HorizontalVelMax information
    // Field HorizontalVelMin information
    // Field CourseFeedForward information
    // Field VelocityFeedForward information
    // Field HorizontalPosP information
    // Field SpeedPI information
    /* Array element names for field SpeedPI */
    typedef enum { SPEEDPI_KP=0, SPEEDPI_KI=1, SPEEDPI_KD=2, SPEEDPI_BETA=3 } SpeedPIElem;
    /* Number of elements for field SpeedPI */
    static const quint32 SPEEDPI_NUMELEM = 4;
    // Field ThrustLimit information
    /* Array element names for field ThrustLimit */
    typedef enum { THRUSTLIMIT_MIN=0, THRUSTLIMIT_SLOWFORWARD=1, THRUSTLIMIT_MAX=2 } ThrustLimitElem;
    /* Number of elements for field ThrustLimit */
    static const quint32 THRUSTLIMIT_NUMELEM = 3;
    // Field UpdatePeriod information

  
    // Constants
    static const quint32 OBJID = 0xCD54334C;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    GroundPathFollowerSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static GroundPathFollowerSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getHorizontalVelMax() const;
    Q_INVOKABLE float getHorizontalVelMin() const;
    Q_INVOKABLE float getCourseFeedForward() const;
    Q_INVOKABLE float getVelocityFeedForward() const;
    Q_INVOKABLE float getHorizontalPosP() const;
    Q_INVOKABLE float getSpeedPI(quint32 index) const;
    Q_INVOKABLE float getSpeedPI_Kp() const;
    Q_INVOKABLE float getSpeedPI_Ki() const;
    Q_INVOKABLE float getSpeedPI_Kd() const;
    Q_INVOKABLE float getSpeedPI_Beta() const;
    Q_INVOKABLE float getThrustLimit(quint32 index) const;
    Q_INVOKABLE float getThrustLimit_Min() const;
    Q_INVOKABLE float getThrustLimit_SlowForward() const;
    Q_INVOKABLE float getThrustLimit_Max() const;
    Q_INVOKABLE qint32 getUpdatePeriod() const;


public slots:
    void setHorizontalVelMax(float value);
    void setHorizontalVelMin(float value);
    void setCourseFeedForward(float value);
    void setVelocityFeedForward(float value);
    void setHorizontalPosP(float value);
    void setSpeedPI(quint32 index, float value);
    void setSpeedPI_Kp(float value);
    void setSpeedPI_Ki(float value);
    void setSpeedPI_Kd(float value);
    void setSpeedPI_Beta(float value);
    void setThrustLimit(quint32 index, float value);
    void setThrustLimit_Min(float value);
    void setThrustLimit_SlowForward(float value);
    void setThrustLimit_Max(float value);
    void setUpdatePeriod(qint32 value);


signals:
    void HorizontalVelMaxChanged(float value);
    void HorizontalVelMinChanged(float value);
    void CourseFeedForwardChanged(float value);
    void VelocityFeedForwardChanged(float value);
    void HorizontalPosPChanged(float value);
    void SpeedPIChanged(quint32 index, float value);
    void SpeedPI_KpChanged(float value);
    void SpeedPI_KiChanged(float value);
    void SpeedPI_KdChanged(float value);
    void SpeedPI_BetaChanged(float value);
    void ThrustLimitChanged(quint32 index, float value);
    void ThrustLimit_MinChanged(float value);
    void ThrustLimit_SlowForwardChanged(float value);
    void ThrustLimit_MaxChanged(float value);
    void UpdatePeriodChanged(qint32 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // GROUNDPATHFOLLOWERSETTINGS_H
