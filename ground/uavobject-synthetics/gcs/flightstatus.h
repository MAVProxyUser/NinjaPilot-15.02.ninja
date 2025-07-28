/**
 ******************************************************************************
 *
 * @file       flightstatus.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: flightstatus.xml. 
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
#ifndef FLIGHTSTATUS_H
#define FLIGHTSTATUS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT FlightStatus: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 Armed READ getArmed WRITE setArmed NOTIFY ArmedChanged);
    Q_PROPERTY(quint8 FlightMode READ getFlightMode WRITE setFlightMode NOTIFY FlightModeChanged);
    Q_PROPERTY(quint8 FlightModeAssist READ getFlightModeAssist WRITE setFlightModeAssist NOTIFY FlightModeAssistChanged);
    Q_PROPERTY(quint8 AssistedControlState READ getAssistedControlState WRITE setAssistedControlState NOTIFY AssistedControlStateChanged);
    Q_PROPERTY(quint8 AssistedThrottleState READ getAssistedThrottleState WRITE setAssistedThrottleState NOTIFY AssistedThrottleStateChanged);
    Q_PROPERTY(quint8 ControlChain_Stabilization READ getControlChain_Stabilization WRITE setControlChain_Stabilization NOTIFY ControlChain_StabilizationChanged);
    Q_PROPERTY(quint8 ControlChain_PathFollower READ getControlChain_PathFollower WRITE setControlChain_PathFollower NOTIFY ControlChain_PathFollowerChanged);
    Q_PROPERTY(quint8 ControlChain_PathPlanner READ getControlChain_PathPlanner WRITE setControlChain_PathPlanner NOTIFY ControlChain_PathPlannerChanged);


public:
    // Field structure
    typedef struct {
        quint8 Armed;
        quint8 FlightMode;
        quint8 FlightModeAssist;
        quint8 AssistedControlState;
        quint8 AssistedThrottleState;
        quint8 ControlChain[3];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Armed information
    /* Enumeration options for field Armed */
    typedef enum { ARMED_DISARMED=0, ARMED_ARMING=1, ARMED_ARMED=2 } ArmedOptions;
    // Field FlightMode information
    /* Enumeration options for field FlightMode */
    typedef enum { FLIGHTMODE_MANUAL=0, FLIGHTMODE_STABILIZED1=1, FLIGHTMODE_STABILIZED2=2, FLIGHTMODE_STABILIZED3=3, FLIGHTMODE_STABILIZED4=4, FLIGHTMODE_STABILIZED5=5, FLIGHTMODE_STABILIZED6=6, FLIGHTMODE_POSITIONHOLD=7, FLIGHTMODE_COURSELOCK=8, FLIGHTMODE_POSITIONROAM=9, FLIGHTMODE_HOMELEASH=10, FLIGHTMODE_ABSOLUTEPOSITION=11, FLIGHTMODE_RETURNTOBASE=12, FLIGHTMODE_LAND=13, FLIGHTMODE_PATHPLANNER=14, FLIGHTMODE_POI=15, FLIGHTMODE_AUTOCRUISE=16 } FlightModeOptions;
    // Field FlightModeAssist information
    /* Enumeration options for field FlightModeAssist */
    typedef enum { FLIGHTMODEASSIST_NONE=0, FLIGHTMODEASSIST_GPSASSIST_PRIMARYTHRUST=1, FLIGHTMODEASSIST_GPSASSIST=2 } FlightModeAssistOptions;
    // Field AssistedControlState information
    /* Enumeration options for field AssistedControlState */
    typedef enum { ASSISTEDCONTROLSTATE_PRIMARY=0, ASSISTEDCONTROLSTATE_BRAKE=1, ASSISTEDCONTROLSTATE_HOLD=2 } AssistedControlStateOptions;
    // Field AssistedThrottleState information
    /* Enumeration options for field AssistedThrottleState */
    typedef enum { ASSISTEDTHROTTLESTATE_MANUAL=0, ASSISTEDTHROTTLESTATE_AUTO=1, ASSISTEDTHROTTLESTATE_AUTOOVERRIDE=2 } AssistedThrottleStateOptions;
    // Field ControlChain information
    /* Enumeration options for field ControlChain */
    typedef enum { CONTROLCHAIN_FALSE=0, CONTROLCHAIN_TRUE=1 } ControlChainOptions;
    /* Array element names for field ControlChain */
    typedef enum { CONTROLCHAIN_STABILIZATION=0, CONTROLCHAIN_PATHFOLLOWER=1, CONTROLCHAIN_PATHPLANNER=2 } ControlChainElem;
    /* Number of elements for field ControlChain */
    static const quint32 CONTROLCHAIN_NUMELEM = 3;

  
    // Constants
    static const quint32 OBJID = 0x8A80EA52;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    FlightStatus();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static FlightStatus* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint8 getArmed() const;
    Q_INVOKABLE quint8 getFlightMode() const;
    Q_INVOKABLE quint8 getFlightModeAssist() const;
    Q_INVOKABLE quint8 getAssistedControlState() const;
    Q_INVOKABLE quint8 getAssistedThrottleState() const;
    Q_INVOKABLE quint8 getControlChain(quint32 index) const;
    Q_INVOKABLE quint8 getControlChain_Stabilization() const;
    Q_INVOKABLE quint8 getControlChain_PathFollower() const;
    Q_INVOKABLE quint8 getControlChain_PathPlanner() const;


public slots:
    void setArmed(quint8 value);
    void setFlightMode(quint8 value);
    void setFlightModeAssist(quint8 value);
    void setAssistedControlState(quint8 value);
    void setAssistedThrottleState(quint8 value);
    void setControlChain(quint32 index, quint8 value);
    void setControlChain_Stabilization(quint8 value);
    void setControlChain_PathFollower(quint8 value);
    void setControlChain_PathPlanner(quint8 value);


signals:
    void ArmedChanged(quint8 value);
    void FlightModeChanged(quint8 value);
    void FlightModeAssistChanged(quint8 value);
    void AssistedControlStateChanged(quint8 value);
    void AssistedThrottleStateChanged(quint8 value);
    void ControlChainChanged(quint32 index, quint8 value);
    void ControlChain_StabilizationChanged(quint8 value);
    void ControlChain_PathFollowerChanged(quint8 value);
    void ControlChain_PathPlannerChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // FLIGHTSTATUS_H
