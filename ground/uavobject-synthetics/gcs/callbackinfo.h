/**
 ******************************************************************************
 *
 * @file       callbackinfo.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: callbackinfo.xml. 
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
#ifndef CALLBACKINFO_H
#define CALLBACKINFO_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT CallbackInfo: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 RunningTime_EventDispatcher READ getRunningTime_EventDispatcher WRITE setRunningTime_EventDispatcher NOTIFY RunningTime_EventDispatcherChanged);
    Q_PROPERTY(quint32 RunningTime_StateEstimation READ getRunningTime_StateEstimation WRITE setRunningTime_StateEstimation NOTIFY RunningTime_StateEstimationChanged);
    Q_PROPERTY(quint32 RunningTime_AltitudeHold READ getRunningTime_AltitudeHold WRITE setRunningTime_AltitudeHold NOTIFY RunningTime_AltitudeHoldChanged);
    Q_PROPERTY(quint32 RunningTime_Stabilization0 READ getRunningTime_Stabilization0 WRITE setRunningTime_Stabilization0 NOTIFY RunningTime_Stabilization0Changed);
    Q_PROPERTY(quint32 RunningTime_Stabilization1 READ getRunningTime_Stabilization1 WRITE setRunningTime_Stabilization1 NOTIFY RunningTime_Stabilization1Changed);
    Q_PROPERTY(quint32 RunningTime_PathFollower READ getRunningTime_PathFollower WRITE setRunningTime_PathFollower NOTIFY RunningTime_PathFollowerChanged);
    Q_PROPERTY(quint32 RunningTime_PathPlanner0 READ getRunningTime_PathPlanner0 WRITE setRunningTime_PathPlanner0 NOTIFY RunningTime_PathPlanner0Changed);
    Q_PROPERTY(quint32 RunningTime_PathPlanner1 READ getRunningTime_PathPlanner1 WRITE setRunningTime_PathPlanner1 NOTIFY RunningTime_PathPlanner1Changed);
    Q_PROPERTY(quint32 RunningTime_ManualControl READ getRunningTime_ManualControl WRITE setRunningTime_ManualControl NOTIFY RunningTime_ManualControlChanged);
    Q_PROPERTY(qint16 StackRemaining_EventDispatcher READ getStackRemaining_EventDispatcher WRITE setStackRemaining_EventDispatcher NOTIFY StackRemaining_EventDispatcherChanged);
    Q_PROPERTY(qint16 StackRemaining_StateEstimation READ getStackRemaining_StateEstimation WRITE setStackRemaining_StateEstimation NOTIFY StackRemaining_StateEstimationChanged);
    Q_PROPERTY(qint16 StackRemaining_AltitudeHold READ getStackRemaining_AltitudeHold WRITE setStackRemaining_AltitudeHold NOTIFY StackRemaining_AltitudeHoldChanged);
    Q_PROPERTY(qint16 StackRemaining_Stabilization0 READ getStackRemaining_Stabilization0 WRITE setStackRemaining_Stabilization0 NOTIFY StackRemaining_Stabilization0Changed);
    Q_PROPERTY(qint16 StackRemaining_Stabilization1 READ getStackRemaining_Stabilization1 WRITE setStackRemaining_Stabilization1 NOTIFY StackRemaining_Stabilization1Changed);
    Q_PROPERTY(qint16 StackRemaining_PathFollower READ getStackRemaining_PathFollower WRITE setStackRemaining_PathFollower NOTIFY StackRemaining_PathFollowerChanged);
    Q_PROPERTY(qint16 StackRemaining_PathPlanner0 READ getStackRemaining_PathPlanner0 WRITE setStackRemaining_PathPlanner0 NOTIFY StackRemaining_PathPlanner0Changed);
    Q_PROPERTY(qint16 StackRemaining_PathPlanner1 READ getStackRemaining_PathPlanner1 WRITE setStackRemaining_PathPlanner1 NOTIFY StackRemaining_PathPlanner1Changed);
    Q_PROPERTY(qint16 StackRemaining_ManualControl READ getStackRemaining_ManualControl WRITE setStackRemaining_ManualControl NOTIFY StackRemaining_ManualControlChanged);
    Q_PROPERTY(quint8 Running_EventDispatcher READ getRunning_EventDispatcher WRITE setRunning_EventDispatcher NOTIFY Running_EventDispatcherChanged);
    Q_PROPERTY(quint8 Running_StateEstimation READ getRunning_StateEstimation WRITE setRunning_StateEstimation NOTIFY Running_StateEstimationChanged);
    Q_PROPERTY(quint8 Running_AltitudeHold READ getRunning_AltitudeHold WRITE setRunning_AltitudeHold NOTIFY Running_AltitudeHoldChanged);
    Q_PROPERTY(quint8 Running_Stabilization0 READ getRunning_Stabilization0 WRITE setRunning_Stabilization0 NOTIFY Running_Stabilization0Changed);
    Q_PROPERTY(quint8 Running_Stabilization1 READ getRunning_Stabilization1 WRITE setRunning_Stabilization1 NOTIFY Running_Stabilization1Changed);
    Q_PROPERTY(quint8 Running_PathFollower READ getRunning_PathFollower WRITE setRunning_PathFollower NOTIFY Running_PathFollowerChanged);
    Q_PROPERTY(quint8 Running_PathPlanner0 READ getRunning_PathPlanner0 WRITE setRunning_PathPlanner0 NOTIFY Running_PathPlanner0Changed);
    Q_PROPERTY(quint8 Running_PathPlanner1 READ getRunning_PathPlanner1 WRITE setRunning_PathPlanner1 NOTIFY Running_PathPlanner1Changed);
    Q_PROPERTY(quint8 Running_ManualControl READ getRunning_ManualControl WRITE setRunning_ManualControl NOTIFY Running_ManualControlChanged);


public:
    // Field structure
    typedef struct {
        quint32 RunningTime[9];
        qint16 StackRemaining[9];
        quint8 Running[9];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field RunningTime information
    /* Array element names for field RunningTime */
    typedef enum { RUNNINGTIME_EVENTDISPATCHER=0, RUNNINGTIME_STATEESTIMATION=1, RUNNINGTIME_ALTITUDEHOLD=2, RUNNINGTIME_STABILIZATION0=3, RUNNINGTIME_STABILIZATION1=4, RUNNINGTIME_PATHFOLLOWER=5, RUNNINGTIME_PATHPLANNER0=6, RUNNINGTIME_PATHPLANNER1=7, RUNNINGTIME_MANUALCONTROL=8 } RunningTimeElem;
    /* Number of elements for field RunningTime */
    static const quint32 RUNNINGTIME_NUMELEM = 9;
    // Field StackRemaining information
    /* Array element names for field StackRemaining */
    typedef enum { STACKREMAINING_EVENTDISPATCHER=0, STACKREMAINING_STATEESTIMATION=1, STACKREMAINING_ALTITUDEHOLD=2, STACKREMAINING_STABILIZATION0=3, STACKREMAINING_STABILIZATION1=4, STACKREMAINING_PATHFOLLOWER=5, STACKREMAINING_PATHPLANNER0=6, STACKREMAINING_PATHPLANNER1=7, STACKREMAINING_MANUALCONTROL=8 } StackRemainingElem;
    /* Number of elements for field StackRemaining */
    static const quint32 STACKREMAINING_NUMELEM = 9;
    // Field Running information
    /* Enumeration options for field Running */
    typedef enum { RUNNING_FALSE=0, RUNNING_TRUE=1 } RunningOptions;
    /* Array element names for field Running */
    typedef enum { RUNNING_EVENTDISPATCHER=0, RUNNING_STATEESTIMATION=1, RUNNING_ALTITUDEHOLD=2, RUNNING_STABILIZATION0=3, RUNNING_STABILIZATION1=4, RUNNING_PATHFOLLOWER=5, RUNNING_PATHPLANNER0=6, RUNNING_PATHPLANNER1=7, RUNNING_MANUALCONTROL=8 } RunningElem;
    /* Number of elements for field Running */
    static const quint32 RUNNING_NUMELEM = 9;

  
    // Constants
    static const quint32 OBJID = 0xB984C78C;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    CallbackInfo();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static CallbackInfo* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint32 getRunningTime(quint32 index) const;
    Q_INVOKABLE quint32 getRunningTime_EventDispatcher() const;
    Q_INVOKABLE quint32 getRunningTime_StateEstimation() const;
    Q_INVOKABLE quint32 getRunningTime_AltitudeHold() const;
    Q_INVOKABLE quint32 getRunningTime_Stabilization0() const;
    Q_INVOKABLE quint32 getRunningTime_Stabilization1() const;
    Q_INVOKABLE quint32 getRunningTime_PathFollower() const;
    Q_INVOKABLE quint32 getRunningTime_PathPlanner0() const;
    Q_INVOKABLE quint32 getRunningTime_PathPlanner1() const;
    Q_INVOKABLE quint32 getRunningTime_ManualControl() const;
    Q_INVOKABLE qint16 getStackRemaining(quint32 index) const;
    Q_INVOKABLE qint16 getStackRemaining_EventDispatcher() const;
    Q_INVOKABLE qint16 getStackRemaining_StateEstimation() const;
    Q_INVOKABLE qint16 getStackRemaining_AltitudeHold() const;
    Q_INVOKABLE qint16 getStackRemaining_Stabilization0() const;
    Q_INVOKABLE qint16 getStackRemaining_Stabilization1() const;
    Q_INVOKABLE qint16 getStackRemaining_PathFollower() const;
    Q_INVOKABLE qint16 getStackRemaining_PathPlanner0() const;
    Q_INVOKABLE qint16 getStackRemaining_PathPlanner1() const;
    Q_INVOKABLE qint16 getStackRemaining_ManualControl() const;
    Q_INVOKABLE quint8 getRunning(quint32 index) const;
    Q_INVOKABLE quint8 getRunning_EventDispatcher() const;
    Q_INVOKABLE quint8 getRunning_StateEstimation() const;
    Q_INVOKABLE quint8 getRunning_AltitudeHold() const;
    Q_INVOKABLE quint8 getRunning_Stabilization0() const;
    Q_INVOKABLE quint8 getRunning_Stabilization1() const;
    Q_INVOKABLE quint8 getRunning_PathFollower() const;
    Q_INVOKABLE quint8 getRunning_PathPlanner0() const;
    Q_INVOKABLE quint8 getRunning_PathPlanner1() const;
    Q_INVOKABLE quint8 getRunning_ManualControl() const;


public slots:
    void setRunningTime(quint32 index, quint32 value);
    void setRunningTime_EventDispatcher(quint32 value);
    void setRunningTime_StateEstimation(quint32 value);
    void setRunningTime_AltitudeHold(quint32 value);
    void setRunningTime_Stabilization0(quint32 value);
    void setRunningTime_Stabilization1(quint32 value);
    void setRunningTime_PathFollower(quint32 value);
    void setRunningTime_PathPlanner0(quint32 value);
    void setRunningTime_PathPlanner1(quint32 value);
    void setRunningTime_ManualControl(quint32 value);
    void setStackRemaining(quint32 index, qint16 value);
    void setStackRemaining_EventDispatcher(qint16 value);
    void setStackRemaining_StateEstimation(qint16 value);
    void setStackRemaining_AltitudeHold(qint16 value);
    void setStackRemaining_Stabilization0(qint16 value);
    void setStackRemaining_Stabilization1(qint16 value);
    void setStackRemaining_PathFollower(qint16 value);
    void setStackRemaining_PathPlanner0(qint16 value);
    void setStackRemaining_PathPlanner1(qint16 value);
    void setStackRemaining_ManualControl(qint16 value);
    void setRunning(quint32 index, quint8 value);
    void setRunning_EventDispatcher(quint8 value);
    void setRunning_StateEstimation(quint8 value);
    void setRunning_AltitudeHold(quint8 value);
    void setRunning_Stabilization0(quint8 value);
    void setRunning_Stabilization1(quint8 value);
    void setRunning_PathFollower(quint8 value);
    void setRunning_PathPlanner0(quint8 value);
    void setRunning_PathPlanner1(quint8 value);
    void setRunning_ManualControl(quint8 value);


signals:
    void RunningTimeChanged(quint32 index, quint32 value);
    void RunningTime_EventDispatcherChanged(quint32 value);
    void RunningTime_StateEstimationChanged(quint32 value);
    void RunningTime_AltitudeHoldChanged(quint32 value);
    void RunningTime_Stabilization0Changed(quint32 value);
    void RunningTime_Stabilization1Changed(quint32 value);
    void RunningTime_PathFollowerChanged(quint32 value);
    void RunningTime_PathPlanner0Changed(quint32 value);
    void RunningTime_PathPlanner1Changed(quint32 value);
    void RunningTime_ManualControlChanged(quint32 value);
    void StackRemainingChanged(quint32 index, qint16 value);
    void StackRemaining_EventDispatcherChanged(qint16 value);
    void StackRemaining_StateEstimationChanged(qint16 value);
    void StackRemaining_AltitudeHoldChanged(qint16 value);
    void StackRemaining_Stabilization0Changed(qint16 value);
    void StackRemaining_Stabilization1Changed(qint16 value);
    void StackRemaining_PathFollowerChanged(qint16 value);
    void StackRemaining_PathPlanner0Changed(qint16 value);
    void StackRemaining_PathPlanner1Changed(qint16 value);
    void StackRemaining_ManualControlChanged(qint16 value);
    void RunningChanged(quint32 index, quint8 value);
    void Running_EventDispatcherChanged(quint8 value);
    void Running_StateEstimationChanged(quint8 value);
    void Running_AltitudeHoldChanged(quint8 value);
    void Running_Stabilization0Changed(quint8 value);
    void Running_Stabilization1Changed(quint8 value);
    void Running_PathFollowerChanged(quint8 value);
    void Running_PathPlanner0Changed(quint8 value);
    void Running_PathPlanner1Changed(quint8 value);
    void Running_ManualControlChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // CALLBACKINFO_H
