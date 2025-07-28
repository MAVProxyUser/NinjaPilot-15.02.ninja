/**
 ******************************************************************************
 *
 * @file       stabilizationdesired.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: stabilizationdesired.xml. 
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
#ifndef STABILIZATIONDESIRED_H
#define STABILIZATIONDESIRED_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT StabilizationDesired: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float Roll READ getRoll WRITE setRoll NOTIFY RollChanged);
    Q_PROPERTY(float Pitch READ getPitch WRITE setPitch NOTIFY PitchChanged);
    Q_PROPERTY(float Yaw READ getYaw WRITE setYaw NOTIFY YawChanged);
    Q_PROPERTY(float Thrust READ getThrust WRITE setThrust NOTIFY ThrustChanged);
    Q_PROPERTY(quint8 StabilizationMode_Roll READ getStabilizationMode_Roll WRITE setStabilizationMode_Roll NOTIFY StabilizationMode_RollChanged);
    Q_PROPERTY(quint8 StabilizationMode_Pitch READ getStabilizationMode_Pitch WRITE setStabilizationMode_Pitch NOTIFY StabilizationMode_PitchChanged);
    Q_PROPERTY(quint8 StabilizationMode_Yaw READ getStabilizationMode_Yaw WRITE setStabilizationMode_Yaw NOTIFY StabilizationMode_YawChanged);
    Q_PROPERTY(quint8 StabilizationMode_Thrust READ getStabilizationMode_Thrust WRITE setStabilizationMode_Thrust NOTIFY StabilizationMode_ThrustChanged);


public:
    // Field structure
    typedef struct {
        float Roll;
        float Pitch;
        float Yaw;
        float Thrust;
        quint8 StabilizationMode[4];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Roll information
    // Field Pitch information
    // Field Yaw information
    // Field Thrust information
    // Field StabilizationMode information
    /* Enumeration options for field StabilizationMode */
    typedef enum { STABILIZATIONMODE_MANUAL=0, STABILIZATIONMODE_RATE=1, STABILIZATIONMODE_ATTITUDE=2, STABILIZATIONMODE_AXISLOCK=3, STABILIZATIONMODE_WEAKLEVELING=4, STABILIZATIONMODE_VIRTUALBAR=5, STABILIZATIONMODE_ACRO=6, STABILIZATIONMODE_RATTITUDE=7, STABILIZATIONMODE_ALTITUDEHOLD=8, STABILIZATIONMODE_ALTITUDEVARIO=9, STABILIZATIONMODE_CRUISECONTROL=10 } StabilizationModeOptions;
    /* Array element names for field StabilizationMode */
    typedef enum { STABILIZATIONMODE_ROLL=0, STABILIZATIONMODE_PITCH=1, STABILIZATIONMODE_YAW=2, STABILIZATIONMODE_THRUST=3 } StabilizationModeElem;
    /* Number of elements for field StabilizationMode */
    static const quint32 STABILIZATIONMODE_NUMELEM = 4;

  
    // Constants
    static const quint32 OBJID = 0x8A2A042C;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    StabilizationDesired();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static StabilizationDesired* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getRoll() const;
    Q_INVOKABLE float getPitch() const;
    Q_INVOKABLE float getYaw() const;
    Q_INVOKABLE float getThrust() const;
    Q_INVOKABLE quint8 getStabilizationMode(quint32 index) const;
    Q_INVOKABLE quint8 getStabilizationMode_Roll() const;
    Q_INVOKABLE quint8 getStabilizationMode_Pitch() const;
    Q_INVOKABLE quint8 getStabilizationMode_Yaw() const;
    Q_INVOKABLE quint8 getStabilizationMode_Thrust() const;


public slots:
    void setRoll(float value);
    void setPitch(float value);
    void setYaw(float value);
    void setThrust(float value);
    void setStabilizationMode(quint32 index, quint8 value);
    void setStabilizationMode_Roll(quint8 value);
    void setStabilizationMode_Pitch(quint8 value);
    void setStabilizationMode_Yaw(quint8 value);
    void setStabilizationMode_Thrust(quint8 value);


signals:
    void RollChanged(float value);
    void PitchChanged(float value);
    void YawChanged(float value);
    void ThrustChanged(float value);
    void StabilizationModeChanged(quint32 index, quint8 value);
    void StabilizationMode_RollChanged(quint8 value);
    void StabilizationMode_PitchChanged(quint8 value);
    void StabilizationMode_YawChanged(quint8 value);
    void StabilizationMode_ThrustChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // STABILIZATIONDESIRED_H
