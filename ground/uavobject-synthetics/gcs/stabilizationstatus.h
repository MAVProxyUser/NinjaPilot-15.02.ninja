/**
 ******************************************************************************
 *
 * @file       stabilizationstatus.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: stabilizationstatus.xml. 
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
#ifndef STABILIZATIONSTATUS_H
#define STABILIZATIONSTATUS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT StabilizationStatus: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 OuterLoop_Roll READ getOuterLoop_Roll WRITE setOuterLoop_Roll NOTIFY OuterLoop_RollChanged);
    Q_PROPERTY(quint8 OuterLoop_Pitch READ getOuterLoop_Pitch WRITE setOuterLoop_Pitch NOTIFY OuterLoop_PitchChanged);
    Q_PROPERTY(quint8 OuterLoop_Yaw READ getOuterLoop_Yaw WRITE setOuterLoop_Yaw NOTIFY OuterLoop_YawChanged);
    Q_PROPERTY(quint8 OuterLoop_Thrust READ getOuterLoop_Thrust WRITE setOuterLoop_Thrust NOTIFY OuterLoop_ThrustChanged);
    Q_PROPERTY(quint8 InnerLoop_Roll READ getInnerLoop_Roll WRITE setInnerLoop_Roll NOTIFY InnerLoop_RollChanged);
    Q_PROPERTY(quint8 InnerLoop_Pitch READ getInnerLoop_Pitch WRITE setInnerLoop_Pitch NOTIFY InnerLoop_PitchChanged);
    Q_PROPERTY(quint8 InnerLoop_Yaw READ getInnerLoop_Yaw WRITE setInnerLoop_Yaw NOTIFY InnerLoop_YawChanged);
    Q_PROPERTY(quint8 InnerLoop_Thrust READ getInnerLoop_Thrust WRITE setInnerLoop_Thrust NOTIFY InnerLoop_ThrustChanged);


public:
    // Field structure
    typedef struct {
        quint8 OuterLoop[4];
        quint8 InnerLoop[4];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field OuterLoop information
    /* Enumeration options for field OuterLoop */
    typedef enum { OUTERLOOP_DIRECT=0, OUTERLOOP_ATTITUDE=1, OUTERLOOP_RATTITUDE=2, OUTERLOOP_WEAKLEVELING=3, OUTERLOOP_ALTITUDE=4, OUTERLOOP_ALTITUDEVARIO=5 } OuterLoopOptions;
    /* Array element names for field OuterLoop */
    typedef enum { OUTERLOOP_ROLL=0, OUTERLOOP_PITCH=1, OUTERLOOP_YAW=2, OUTERLOOP_THRUST=3 } OuterLoopElem;
    /* Number of elements for field OuterLoop */
    static const quint32 OUTERLOOP_NUMELEM = 4;
    // Field InnerLoop information
    /* Enumeration options for field InnerLoop */
    typedef enum { INNERLOOP_DIRECT=0, INNERLOOP_VIRTUALFLYBAR=1, INNERLOOP_ACRO=2, INNERLOOP_AXISLOCK=3, INNERLOOP_RATE=4, INNERLOOP_CRUISECONTROL=5 } InnerLoopOptions;
    /* Array element names for field InnerLoop */
    typedef enum { INNERLOOP_ROLL=0, INNERLOOP_PITCH=1, INNERLOOP_YAW=2, INNERLOOP_THRUST=3 } InnerLoopElem;
    /* Number of elements for field InnerLoop */
    static const quint32 INNERLOOP_NUMELEM = 4;

  
    // Constants
    static const quint32 OBJID = 0x38EAB692;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    StabilizationStatus();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static StabilizationStatus* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint8 getOuterLoop(quint32 index) const;
    Q_INVOKABLE quint8 getOuterLoop_Roll() const;
    Q_INVOKABLE quint8 getOuterLoop_Pitch() const;
    Q_INVOKABLE quint8 getOuterLoop_Yaw() const;
    Q_INVOKABLE quint8 getOuterLoop_Thrust() const;
    Q_INVOKABLE quint8 getInnerLoop(quint32 index) const;
    Q_INVOKABLE quint8 getInnerLoop_Roll() const;
    Q_INVOKABLE quint8 getInnerLoop_Pitch() const;
    Q_INVOKABLE quint8 getInnerLoop_Yaw() const;
    Q_INVOKABLE quint8 getInnerLoop_Thrust() const;


public slots:
    void setOuterLoop(quint32 index, quint8 value);
    void setOuterLoop_Roll(quint8 value);
    void setOuterLoop_Pitch(quint8 value);
    void setOuterLoop_Yaw(quint8 value);
    void setOuterLoop_Thrust(quint8 value);
    void setInnerLoop(quint32 index, quint8 value);
    void setInnerLoop_Roll(quint8 value);
    void setInnerLoop_Pitch(quint8 value);
    void setInnerLoop_Yaw(quint8 value);
    void setInnerLoop_Thrust(quint8 value);


signals:
    void OuterLoopChanged(quint32 index, quint8 value);
    void OuterLoop_RollChanged(quint8 value);
    void OuterLoop_PitchChanged(quint8 value);
    void OuterLoop_YawChanged(quint8 value);
    void OuterLoop_ThrustChanged(quint8 value);
    void InnerLoopChanged(quint32 index, quint8 value);
    void InnerLoop_RollChanged(quint8 value);
    void InnerLoop_PitchChanged(quint8 value);
    void InnerLoop_YawChanged(quint8 value);
    void InnerLoop_ThrustChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // STABILIZATIONSTATUS_H
