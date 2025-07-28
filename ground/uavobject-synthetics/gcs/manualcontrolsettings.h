/**
 ******************************************************************************
 *
 * @file       manualcontrolsettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: manualcontrolsettings.xml. 
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
#ifndef MANUALCONTROLSETTINGS_H
#define MANUALCONTROLSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT ManualControlSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float Deadband READ getDeadband WRITE setDeadband NOTIFY DeadbandChanged);
    Q_PROPERTY(float DeadbandAssistedControl READ getDeadbandAssistedControl WRITE setDeadbandAssistedControl NOTIFY DeadbandAssistedControlChanged);
    Q_PROPERTY(float FailsafeChannel_Throttle READ getFailsafeChannel_Throttle WRITE setFailsafeChannel_Throttle NOTIFY FailsafeChannel_ThrottleChanged);
    Q_PROPERTY(float FailsafeChannel_Roll READ getFailsafeChannel_Roll WRITE setFailsafeChannel_Roll NOTIFY FailsafeChannel_RollChanged);
    Q_PROPERTY(float FailsafeChannel_Pitch READ getFailsafeChannel_Pitch WRITE setFailsafeChannel_Pitch NOTIFY FailsafeChannel_PitchChanged);
    Q_PROPERTY(float FailsafeChannel_Yaw READ getFailsafeChannel_Yaw WRITE setFailsafeChannel_Yaw NOTIFY FailsafeChannel_YawChanged);
    Q_PROPERTY(float FailsafeChannel_Collective READ getFailsafeChannel_Collective WRITE setFailsafeChannel_Collective NOTIFY FailsafeChannel_CollectiveChanged);
    Q_PROPERTY(float FailsafeChannel_Accessory0 READ getFailsafeChannel_Accessory0 WRITE setFailsafeChannel_Accessory0 NOTIFY FailsafeChannel_Accessory0Changed);
    Q_PROPERTY(float FailsafeChannel_Accessory1 READ getFailsafeChannel_Accessory1 WRITE setFailsafeChannel_Accessory1 NOTIFY FailsafeChannel_Accessory1Changed);
    Q_PROPERTY(float FailsafeChannel_Accessory2 READ getFailsafeChannel_Accessory2 WRITE setFailsafeChannel_Accessory2 NOTIFY FailsafeChannel_Accessory2Changed);
    Q_PROPERTY(qint16 ChannelMin_Throttle READ getChannelMin_Throttle WRITE setChannelMin_Throttle NOTIFY ChannelMin_ThrottleChanged);
    Q_PROPERTY(qint16 ChannelMin_Roll READ getChannelMin_Roll WRITE setChannelMin_Roll NOTIFY ChannelMin_RollChanged);
    Q_PROPERTY(qint16 ChannelMin_Pitch READ getChannelMin_Pitch WRITE setChannelMin_Pitch NOTIFY ChannelMin_PitchChanged);
    Q_PROPERTY(qint16 ChannelMin_Yaw READ getChannelMin_Yaw WRITE setChannelMin_Yaw NOTIFY ChannelMin_YawChanged);
    Q_PROPERTY(qint16 ChannelMin_FlightMode READ getChannelMin_FlightMode WRITE setChannelMin_FlightMode NOTIFY ChannelMin_FlightModeChanged);
    Q_PROPERTY(qint16 ChannelMin_Collective READ getChannelMin_Collective WRITE setChannelMin_Collective NOTIFY ChannelMin_CollectiveChanged);
    Q_PROPERTY(qint16 ChannelMin_Accessory0 READ getChannelMin_Accessory0 WRITE setChannelMin_Accessory0 NOTIFY ChannelMin_Accessory0Changed);
    Q_PROPERTY(qint16 ChannelMin_Accessory1 READ getChannelMin_Accessory1 WRITE setChannelMin_Accessory1 NOTIFY ChannelMin_Accessory1Changed);
    Q_PROPERTY(qint16 ChannelMin_Accessory2 READ getChannelMin_Accessory2 WRITE setChannelMin_Accessory2 NOTIFY ChannelMin_Accessory2Changed);
    Q_PROPERTY(qint16 ChannelNeutral_Throttle READ getChannelNeutral_Throttle WRITE setChannelNeutral_Throttle NOTIFY ChannelNeutral_ThrottleChanged);
    Q_PROPERTY(qint16 ChannelNeutral_Roll READ getChannelNeutral_Roll WRITE setChannelNeutral_Roll NOTIFY ChannelNeutral_RollChanged);
    Q_PROPERTY(qint16 ChannelNeutral_Pitch READ getChannelNeutral_Pitch WRITE setChannelNeutral_Pitch NOTIFY ChannelNeutral_PitchChanged);
    Q_PROPERTY(qint16 ChannelNeutral_Yaw READ getChannelNeutral_Yaw WRITE setChannelNeutral_Yaw NOTIFY ChannelNeutral_YawChanged);
    Q_PROPERTY(qint16 ChannelNeutral_FlightMode READ getChannelNeutral_FlightMode WRITE setChannelNeutral_FlightMode NOTIFY ChannelNeutral_FlightModeChanged);
    Q_PROPERTY(qint16 ChannelNeutral_Collective READ getChannelNeutral_Collective WRITE setChannelNeutral_Collective NOTIFY ChannelNeutral_CollectiveChanged);
    Q_PROPERTY(qint16 ChannelNeutral_Accessory0 READ getChannelNeutral_Accessory0 WRITE setChannelNeutral_Accessory0 NOTIFY ChannelNeutral_Accessory0Changed);
    Q_PROPERTY(qint16 ChannelNeutral_Accessory1 READ getChannelNeutral_Accessory1 WRITE setChannelNeutral_Accessory1 NOTIFY ChannelNeutral_Accessory1Changed);
    Q_PROPERTY(qint16 ChannelNeutral_Accessory2 READ getChannelNeutral_Accessory2 WRITE setChannelNeutral_Accessory2 NOTIFY ChannelNeutral_Accessory2Changed);
    Q_PROPERTY(qint16 ChannelMax_Throttle READ getChannelMax_Throttle WRITE setChannelMax_Throttle NOTIFY ChannelMax_ThrottleChanged);
    Q_PROPERTY(qint16 ChannelMax_Roll READ getChannelMax_Roll WRITE setChannelMax_Roll NOTIFY ChannelMax_RollChanged);
    Q_PROPERTY(qint16 ChannelMax_Pitch READ getChannelMax_Pitch WRITE setChannelMax_Pitch NOTIFY ChannelMax_PitchChanged);
    Q_PROPERTY(qint16 ChannelMax_Yaw READ getChannelMax_Yaw WRITE setChannelMax_Yaw NOTIFY ChannelMax_YawChanged);
    Q_PROPERTY(qint16 ChannelMax_FlightMode READ getChannelMax_FlightMode WRITE setChannelMax_FlightMode NOTIFY ChannelMax_FlightModeChanged);
    Q_PROPERTY(qint16 ChannelMax_Collective READ getChannelMax_Collective WRITE setChannelMax_Collective NOTIFY ChannelMax_CollectiveChanged);
    Q_PROPERTY(qint16 ChannelMax_Accessory0 READ getChannelMax_Accessory0 WRITE setChannelMax_Accessory0 NOTIFY ChannelMax_Accessory0Changed);
    Q_PROPERTY(qint16 ChannelMax_Accessory1 READ getChannelMax_Accessory1 WRITE setChannelMax_Accessory1 NOTIFY ChannelMax_Accessory1Changed);
    Q_PROPERTY(qint16 ChannelMax_Accessory2 READ getChannelMax_Accessory2 WRITE setChannelMax_Accessory2 NOTIFY ChannelMax_Accessory2Changed);
    Q_PROPERTY(quint16 ResponseTime_Roll READ getResponseTime_Roll WRITE setResponseTime_Roll NOTIFY ResponseTime_RollChanged);
    Q_PROPERTY(quint16 ResponseTime_Pitch READ getResponseTime_Pitch WRITE setResponseTime_Pitch NOTIFY ResponseTime_PitchChanged);
    Q_PROPERTY(quint16 ResponseTime_Yaw READ getResponseTime_Yaw WRITE setResponseTime_Yaw NOTIFY ResponseTime_YawChanged);
    Q_PROPERTY(quint16 ResponseTime_Collective READ getResponseTime_Collective WRITE setResponseTime_Collective NOTIFY ResponseTime_CollectiveChanged);
    Q_PROPERTY(quint16 ResponseTime_Accessory0 READ getResponseTime_Accessory0 WRITE setResponseTime_Accessory0 NOTIFY ResponseTime_Accessory0Changed);
    Q_PROPERTY(quint16 ResponseTime_Accessory1 READ getResponseTime_Accessory1 WRITE setResponseTime_Accessory1 NOTIFY ResponseTime_Accessory1Changed);
    Q_PROPERTY(quint16 ResponseTime_Accessory2 READ getResponseTime_Accessory2 WRITE setResponseTime_Accessory2 NOTIFY ResponseTime_Accessory2Changed);
    Q_PROPERTY(quint8 ChannelGroups_Throttle READ getChannelGroups_Throttle WRITE setChannelGroups_Throttle NOTIFY ChannelGroups_ThrottleChanged);
    Q_PROPERTY(quint8 ChannelGroups_Roll READ getChannelGroups_Roll WRITE setChannelGroups_Roll NOTIFY ChannelGroups_RollChanged);
    Q_PROPERTY(quint8 ChannelGroups_Pitch READ getChannelGroups_Pitch WRITE setChannelGroups_Pitch NOTIFY ChannelGroups_PitchChanged);
    Q_PROPERTY(quint8 ChannelGroups_Yaw READ getChannelGroups_Yaw WRITE setChannelGroups_Yaw NOTIFY ChannelGroups_YawChanged);
    Q_PROPERTY(quint8 ChannelGroups_FlightMode READ getChannelGroups_FlightMode WRITE setChannelGroups_FlightMode NOTIFY ChannelGroups_FlightModeChanged);
    Q_PROPERTY(quint8 ChannelGroups_Collective READ getChannelGroups_Collective WRITE setChannelGroups_Collective NOTIFY ChannelGroups_CollectiveChanged);
    Q_PROPERTY(quint8 ChannelGroups_Accessory0 READ getChannelGroups_Accessory0 WRITE setChannelGroups_Accessory0 NOTIFY ChannelGroups_Accessory0Changed);
    Q_PROPERTY(quint8 ChannelGroups_Accessory1 READ getChannelGroups_Accessory1 WRITE setChannelGroups_Accessory1 NOTIFY ChannelGroups_Accessory1Changed);
    Q_PROPERTY(quint8 ChannelGroups_Accessory2 READ getChannelGroups_Accessory2 WRITE setChannelGroups_Accessory2 NOTIFY ChannelGroups_Accessory2Changed);
    Q_PROPERTY(quint8 ChannelNumber_Throttle READ getChannelNumber_Throttle WRITE setChannelNumber_Throttle NOTIFY ChannelNumber_ThrottleChanged);
    Q_PROPERTY(quint8 ChannelNumber_Roll READ getChannelNumber_Roll WRITE setChannelNumber_Roll NOTIFY ChannelNumber_RollChanged);
    Q_PROPERTY(quint8 ChannelNumber_Pitch READ getChannelNumber_Pitch WRITE setChannelNumber_Pitch NOTIFY ChannelNumber_PitchChanged);
    Q_PROPERTY(quint8 ChannelNumber_Yaw READ getChannelNumber_Yaw WRITE setChannelNumber_Yaw NOTIFY ChannelNumber_YawChanged);
    Q_PROPERTY(quint8 ChannelNumber_FlightMode READ getChannelNumber_FlightMode WRITE setChannelNumber_FlightMode NOTIFY ChannelNumber_FlightModeChanged);
    Q_PROPERTY(quint8 ChannelNumber_Collective READ getChannelNumber_Collective WRITE setChannelNumber_Collective NOTIFY ChannelNumber_CollectiveChanged);
    Q_PROPERTY(quint8 ChannelNumber_Accessory0 READ getChannelNumber_Accessory0 WRITE setChannelNumber_Accessory0 NOTIFY ChannelNumber_Accessory0Changed);
    Q_PROPERTY(quint8 ChannelNumber_Accessory1 READ getChannelNumber_Accessory1 WRITE setChannelNumber_Accessory1 NOTIFY ChannelNumber_Accessory1Changed);
    Q_PROPERTY(quint8 ChannelNumber_Accessory2 READ getChannelNumber_Accessory2 WRITE setChannelNumber_Accessory2 NOTIFY ChannelNumber_Accessory2Changed);
    Q_PROPERTY(quint8 FlightModeNumber READ getFlightModeNumber WRITE setFlightModeNumber NOTIFY FlightModeNumberChanged);
    Q_PROPERTY(qint8 FailsafeFlightModeSwitchPosition READ getFailsafeFlightModeSwitchPosition WRITE setFailsafeFlightModeSwitchPosition NOTIFY FailsafeFlightModeSwitchPositionChanged);


public:
    // Field structure
    typedef struct {
        float Deadband;
        float DeadbandAssistedControl;
        float FailsafeChannel[8];
        qint16 ChannelMin[9];
        qint16 ChannelNeutral[9];
        qint16 ChannelMax[9];
        quint16 ResponseTime[7];
        quint8 ChannelGroups[9];
        quint8 ChannelNumber[9];
        quint8 FlightModeNumber;
        qint8 FailsafeFlightModeSwitchPosition;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Deadband information
    // Field DeadbandAssistedControl information
    // Field FailsafeChannel information
    /* Array element names for field FailsafeChannel */
    typedef enum { FAILSAFECHANNEL_THROTTLE=0, FAILSAFECHANNEL_ROLL=1, FAILSAFECHANNEL_PITCH=2, FAILSAFECHANNEL_YAW=3, FAILSAFECHANNEL_COLLECTIVE=4, FAILSAFECHANNEL_ACCESSORY0=5, FAILSAFECHANNEL_ACCESSORY1=6, FAILSAFECHANNEL_ACCESSORY2=7 } FailsafeChannelElem;
    /* Number of elements for field FailsafeChannel */
    static const quint32 FAILSAFECHANNEL_NUMELEM = 8;
    // Field ChannelMin information
    /* Array element names for field ChannelMin */
    typedef enum { CHANNELMIN_THROTTLE=0, CHANNELMIN_ROLL=1, CHANNELMIN_PITCH=2, CHANNELMIN_YAW=3, CHANNELMIN_FLIGHTMODE=4, CHANNELMIN_COLLECTIVE=5, CHANNELMIN_ACCESSORY0=6, CHANNELMIN_ACCESSORY1=7, CHANNELMIN_ACCESSORY2=8 } ChannelMinElem;
    /* Number of elements for field ChannelMin */
    static const quint32 CHANNELMIN_NUMELEM = 9;
    // Field ChannelNeutral information
    /* Array element names for field ChannelNeutral */
    typedef enum { CHANNELNEUTRAL_THROTTLE=0, CHANNELNEUTRAL_ROLL=1, CHANNELNEUTRAL_PITCH=2, CHANNELNEUTRAL_YAW=3, CHANNELNEUTRAL_FLIGHTMODE=4, CHANNELNEUTRAL_COLLECTIVE=5, CHANNELNEUTRAL_ACCESSORY0=6, CHANNELNEUTRAL_ACCESSORY1=7, CHANNELNEUTRAL_ACCESSORY2=8 } ChannelNeutralElem;
    /* Number of elements for field ChannelNeutral */
    static const quint32 CHANNELNEUTRAL_NUMELEM = 9;
    // Field ChannelMax information
    /* Array element names for field ChannelMax */
    typedef enum { CHANNELMAX_THROTTLE=0, CHANNELMAX_ROLL=1, CHANNELMAX_PITCH=2, CHANNELMAX_YAW=3, CHANNELMAX_FLIGHTMODE=4, CHANNELMAX_COLLECTIVE=5, CHANNELMAX_ACCESSORY0=6, CHANNELMAX_ACCESSORY1=7, CHANNELMAX_ACCESSORY2=8 } ChannelMaxElem;
    /* Number of elements for field ChannelMax */
    static const quint32 CHANNELMAX_NUMELEM = 9;
    // Field ResponseTime information
    /* Array element names for field ResponseTime */
    typedef enum { RESPONSETIME_ROLL=0, RESPONSETIME_PITCH=1, RESPONSETIME_YAW=2, RESPONSETIME_COLLECTIVE=3, RESPONSETIME_ACCESSORY0=4, RESPONSETIME_ACCESSORY1=5, RESPONSETIME_ACCESSORY2=6 } ResponseTimeElem;
    /* Number of elements for field ResponseTime */
    static const quint32 RESPONSETIME_NUMELEM = 7;
    // Field ChannelGroups information
    /* Enumeration options for field ChannelGroups */
    typedef enum { CHANNELGROUPS_PWM=0, CHANNELGROUPS_PPM=1, CHANNELGROUPS_DSMMAINPORT=2, CHANNELGROUPS_DSMFLEXIPORT=3, CHANNELGROUPS_SBUS=4, CHANNELGROUPS_GCS=5, CHANNELGROUPS_OPLINK=6, CHANNELGROUPS_NONE=7 } ChannelGroupsOptions;
    /* Array element names for field ChannelGroups */
    typedef enum { CHANNELGROUPS_THROTTLE=0, CHANNELGROUPS_ROLL=1, CHANNELGROUPS_PITCH=2, CHANNELGROUPS_YAW=3, CHANNELGROUPS_FLIGHTMODE=4, CHANNELGROUPS_COLLECTIVE=5, CHANNELGROUPS_ACCESSORY0=6, CHANNELGROUPS_ACCESSORY1=7, CHANNELGROUPS_ACCESSORY2=8 } ChannelGroupsElem;
    /* Number of elements for field ChannelGroups */
    static const quint32 CHANNELGROUPS_NUMELEM = 9;
    // Field ChannelNumber information
    /* Array element names for field ChannelNumber */
    typedef enum { CHANNELNUMBER_THROTTLE=0, CHANNELNUMBER_ROLL=1, CHANNELNUMBER_PITCH=2, CHANNELNUMBER_YAW=3, CHANNELNUMBER_FLIGHTMODE=4, CHANNELNUMBER_COLLECTIVE=5, CHANNELNUMBER_ACCESSORY0=6, CHANNELNUMBER_ACCESSORY1=7, CHANNELNUMBER_ACCESSORY2=8 } ChannelNumberElem;
    /* Number of elements for field ChannelNumber */
    static const quint32 CHANNELNUMBER_NUMELEM = 9;
    // Field FlightModeNumber information
    // Field FailsafeFlightModeSwitchPosition information

  
    // Constants
    static const quint32 OBJID = 0x28801F10;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    ManualControlSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static ManualControlSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getDeadband() const;
    Q_INVOKABLE float getDeadbandAssistedControl() const;
    Q_INVOKABLE float getFailsafeChannel(quint32 index) const;
    Q_INVOKABLE float getFailsafeChannel_Throttle() const;
    Q_INVOKABLE float getFailsafeChannel_Roll() const;
    Q_INVOKABLE float getFailsafeChannel_Pitch() const;
    Q_INVOKABLE float getFailsafeChannel_Yaw() const;
    Q_INVOKABLE float getFailsafeChannel_Collective() const;
    Q_INVOKABLE float getFailsafeChannel_Accessory0() const;
    Q_INVOKABLE float getFailsafeChannel_Accessory1() const;
    Q_INVOKABLE float getFailsafeChannel_Accessory2() const;
    Q_INVOKABLE qint16 getChannelMin(quint32 index) const;
    Q_INVOKABLE qint16 getChannelMin_Throttle() const;
    Q_INVOKABLE qint16 getChannelMin_Roll() const;
    Q_INVOKABLE qint16 getChannelMin_Pitch() const;
    Q_INVOKABLE qint16 getChannelMin_Yaw() const;
    Q_INVOKABLE qint16 getChannelMin_FlightMode() const;
    Q_INVOKABLE qint16 getChannelMin_Collective() const;
    Q_INVOKABLE qint16 getChannelMin_Accessory0() const;
    Q_INVOKABLE qint16 getChannelMin_Accessory1() const;
    Q_INVOKABLE qint16 getChannelMin_Accessory2() const;
    Q_INVOKABLE qint16 getChannelNeutral(quint32 index) const;
    Q_INVOKABLE qint16 getChannelNeutral_Throttle() const;
    Q_INVOKABLE qint16 getChannelNeutral_Roll() const;
    Q_INVOKABLE qint16 getChannelNeutral_Pitch() const;
    Q_INVOKABLE qint16 getChannelNeutral_Yaw() const;
    Q_INVOKABLE qint16 getChannelNeutral_FlightMode() const;
    Q_INVOKABLE qint16 getChannelNeutral_Collective() const;
    Q_INVOKABLE qint16 getChannelNeutral_Accessory0() const;
    Q_INVOKABLE qint16 getChannelNeutral_Accessory1() const;
    Q_INVOKABLE qint16 getChannelNeutral_Accessory2() const;
    Q_INVOKABLE qint16 getChannelMax(quint32 index) const;
    Q_INVOKABLE qint16 getChannelMax_Throttle() const;
    Q_INVOKABLE qint16 getChannelMax_Roll() const;
    Q_INVOKABLE qint16 getChannelMax_Pitch() const;
    Q_INVOKABLE qint16 getChannelMax_Yaw() const;
    Q_INVOKABLE qint16 getChannelMax_FlightMode() const;
    Q_INVOKABLE qint16 getChannelMax_Collective() const;
    Q_INVOKABLE qint16 getChannelMax_Accessory0() const;
    Q_INVOKABLE qint16 getChannelMax_Accessory1() const;
    Q_INVOKABLE qint16 getChannelMax_Accessory2() const;
    Q_INVOKABLE quint16 getResponseTime(quint32 index) const;
    Q_INVOKABLE quint16 getResponseTime_Roll() const;
    Q_INVOKABLE quint16 getResponseTime_Pitch() const;
    Q_INVOKABLE quint16 getResponseTime_Yaw() const;
    Q_INVOKABLE quint16 getResponseTime_Collective() const;
    Q_INVOKABLE quint16 getResponseTime_Accessory0() const;
    Q_INVOKABLE quint16 getResponseTime_Accessory1() const;
    Q_INVOKABLE quint16 getResponseTime_Accessory2() const;
    Q_INVOKABLE quint8 getChannelGroups(quint32 index) const;
    Q_INVOKABLE quint8 getChannelGroups_Throttle() const;
    Q_INVOKABLE quint8 getChannelGroups_Roll() const;
    Q_INVOKABLE quint8 getChannelGroups_Pitch() const;
    Q_INVOKABLE quint8 getChannelGroups_Yaw() const;
    Q_INVOKABLE quint8 getChannelGroups_FlightMode() const;
    Q_INVOKABLE quint8 getChannelGroups_Collective() const;
    Q_INVOKABLE quint8 getChannelGroups_Accessory0() const;
    Q_INVOKABLE quint8 getChannelGroups_Accessory1() const;
    Q_INVOKABLE quint8 getChannelGroups_Accessory2() const;
    Q_INVOKABLE quint8 getChannelNumber(quint32 index) const;
    Q_INVOKABLE quint8 getChannelNumber_Throttle() const;
    Q_INVOKABLE quint8 getChannelNumber_Roll() const;
    Q_INVOKABLE quint8 getChannelNumber_Pitch() const;
    Q_INVOKABLE quint8 getChannelNumber_Yaw() const;
    Q_INVOKABLE quint8 getChannelNumber_FlightMode() const;
    Q_INVOKABLE quint8 getChannelNumber_Collective() const;
    Q_INVOKABLE quint8 getChannelNumber_Accessory0() const;
    Q_INVOKABLE quint8 getChannelNumber_Accessory1() const;
    Q_INVOKABLE quint8 getChannelNumber_Accessory2() const;
    Q_INVOKABLE quint8 getFlightModeNumber() const;
    Q_INVOKABLE qint8 getFailsafeFlightModeSwitchPosition() const;


public slots:
    void setDeadband(float value);
    void setDeadbandAssistedControl(float value);
    void setFailsafeChannel(quint32 index, float value);
    void setFailsafeChannel_Throttle(float value);
    void setFailsafeChannel_Roll(float value);
    void setFailsafeChannel_Pitch(float value);
    void setFailsafeChannel_Yaw(float value);
    void setFailsafeChannel_Collective(float value);
    void setFailsafeChannel_Accessory0(float value);
    void setFailsafeChannel_Accessory1(float value);
    void setFailsafeChannel_Accessory2(float value);
    void setChannelMin(quint32 index, qint16 value);
    void setChannelMin_Throttle(qint16 value);
    void setChannelMin_Roll(qint16 value);
    void setChannelMin_Pitch(qint16 value);
    void setChannelMin_Yaw(qint16 value);
    void setChannelMin_FlightMode(qint16 value);
    void setChannelMin_Collective(qint16 value);
    void setChannelMin_Accessory0(qint16 value);
    void setChannelMin_Accessory1(qint16 value);
    void setChannelMin_Accessory2(qint16 value);
    void setChannelNeutral(quint32 index, qint16 value);
    void setChannelNeutral_Throttle(qint16 value);
    void setChannelNeutral_Roll(qint16 value);
    void setChannelNeutral_Pitch(qint16 value);
    void setChannelNeutral_Yaw(qint16 value);
    void setChannelNeutral_FlightMode(qint16 value);
    void setChannelNeutral_Collective(qint16 value);
    void setChannelNeutral_Accessory0(qint16 value);
    void setChannelNeutral_Accessory1(qint16 value);
    void setChannelNeutral_Accessory2(qint16 value);
    void setChannelMax(quint32 index, qint16 value);
    void setChannelMax_Throttle(qint16 value);
    void setChannelMax_Roll(qint16 value);
    void setChannelMax_Pitch(qint16 value);
    void setChannelMax_Yaw(qint16 value);
    void setChannelMax_FlightMode(qint16 value);
    void setChannelMax_Collective(qint16 value);
    void setChannelMax_Accessory0(qint16 value);
    void setChannelMax_Accessory1(qint16 value);
    void setChannelMax_Accessory2(qint16 value);
    void setResponseTime(quint32 index, quint16 value);
    void setResponseTime_Roll(quint16 value);
    void setResponseTime_Pitch(quint16 value);
    void setResponseTime_Yaw(quint16 value);
    void setResponseTime_Collective(quint16 value);
    void setResponseTime_Accessory0(quint16 value);
    void setResponseTime_Accessory1(quint16 value);
    void setResponseTime_Accessory2(quint16 value);
    void setChannelGroups(quint32 index, quint8 value);
    void setChannelGroups_Throttle(quint8 value);
    void setChannelGroups_Roll(quint8 value);
    void setChannelGroups_Pitch(quint8 value);
    void setChannelGroups_Yaw(quint8 value);
    void setChannelGroups_FlightMode(quint8 value);
    void setChannelGroups_Collective(quint8 value);
    void setChannelGroups_Accessory0(quint8 value);
    void setChannelGroups_Accessory1(quint8 value);
    void setChannelGroups_Accessory2(quint8 value);
    void setChannelNumber(quint32 index, quint8 value);
    void setChannelNumber_Throttle(quint8 value);
    void setChannelNumber_Roll(quint8 value);
    void setChannelNumber_Pitch(quint8 value);
    void setChannelNumber_Yaw(quint8 value);
    void setChannelNumber_FlightMode(quint8 value);
    void setChannelNumber_Collective(quint8 value);
    void setChannelNumber_Accessory0(quint8 value);
    void setChannelNumber_Accessory1(quint8 value);
    void setChannelNumber_Accessory2(quint8 value);
    void setFlightModeNumber(quint8 value);
    void setFailsafeFlightModeSwitchPosition(qint8 value);


signals:
    void DeadbandChanged(float value);
    void DeadbandAssistedControlChanged(float value);
    void FailsafeChannelChanged(quint32 index, float value);
    void FailsafeChannel_ThrottleChanged(float value);
    void FailsafeChannel_RollChanged(float value);
    void FailsafeChannel_PitchChanged(float value);
    void FailsafeChannel_YawChanged(float value);
    void FailsafeChannel_CollectiveChanged(float value);
    void FailsafeChannel_Accessory0Changed(float value);
    void FailsafeChannel_Accessory1Changed(float value);
    void FailsafeChannel_Accessory2Changed(float value);
    void ChannelMinChanged(quint32 index, qint16 value);
    void ChannelMin_ThrottleChanged(qint16 value);
    void ChannelMin_RollChanged(qint16 value);
    void ChannelMin_PitchChanged(qint16 value);
    void ChannelMin_YawChanged(qint16 value);
    void ChannelMin_FlightModeChanged(qint16 value);
    void ChannelMin_CollectiveChanged(qint16 value);
    void ChannelMin_Accessory0Changed(qint16 value);
    void ChannelMin_Accessory1Changed(qint16 value);
    void ChannelMin_Accessory2Changed(qint16 value);
    void ChannelNeutralChanged(quint32 index, qint16 value);
    void ChannelNeutral_ThrottleChanged(qint16 value);
    void ChannelNeutral_RollChanged(qint16 value);
    void ChannelNeutral_PitchChanged(qint16 value);
    void ChannelNeutral_YawChanged(qint16 value);
    void ChannelNeutral_FlightModeChanged(qint16 value);
    void ChannelNeutral_CollectiveChanged(qint16 value);
    void ChannelNeutral_Accessory0Changed(qint16 value);
    void ChannelNeutral_Accessory1Changed(qint16 value);
    void ChannelNeutral_Accessory2Changed(qint16 value);
    void ChannelMaxChanged(quint32 index, qint16 value);
    void ChannelMax_ThrottleChanged(qint16 value);
    void ChannelMax_RollChanged(qint16 value);
    void ChannelMax_PitchChanged(qint16 value);
    void ChannelMax_YawChanged(qint16 value);
    void ChannelMax_FlightModeChanged(qint16 value);
    void ChannelMax_CollectiveChanged(qint16 value);
    void ChannelMax_Accessory0Changed(qint16 value);
    void ChannelMax_Accessory1Changed(qint16 value);
    void ChannelMax_Accessory2Changed(qint16 value);
    void ResponseTimeChanged(quint32 index, quint16 value);
    void ResponseTime_RollChanged(quint16 value);
    void ResponseTime_PitchChanged(quint16 value);
    void ResponseTime_YawChanged(quint16 value);
    void ResponseTime_CollectiveChanged(quint16 value);
    void ResponseTime_Accessory0Changed(quint16 value);
    void ResponseTime_Accessory1Changed(quint16 value);
    void ResponseTime_Accessory2Changed(quint16 value);
    void ChannelGroupsChanged(quint32 index, quint8 value);
    void ChannelGroups_ThrottleChanged(quint8 value);
    void ChannelGroups_RollChanged(quint8 value);
    void ChannelGroups_PitchChanged(quint8 value);
    void ChannelGroups_YawChanged(quint8 value);
    void ChannelGroups_FlightModeChanged(quint8 value);
    void ChannelGroups_CollectiveChanged(quint8 value);
    void ChannelGroups_Accessory0Changed(quint8 value);
    void ChannelGroups_Accessory1Changed(quint8 value);
    void ChannelGroups_Accessory2Changed(quint8 value);
    void ChannelNumberChanged(quint32 index, quint8 value);
    void ChannelNumber_ThrottleChanged(quint8 value);
    void ChannelNumber_RollChanged(quint8 value);
    void ChannelNumber_PitchChanged(quint8 value);
    void ChannelNumber_YawChanged(quint8 value);
    void ChannelNumber_FlightModeChanged(quint8 value);
    void ChannelNumber_CollectiveChanged(quint8 value);
    void ChannelNumber_Accessory0Changed(quint8 value);
    void ChannelNumber_Accessory1Changed(quint8 value);
    void ChannelNumber_Accessory2Changed(quint8 value);
    void FlightModeNumberChanged(quint8 value);
    void FailsafeFlightModeSwitchPositionChanged(qint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // MANUALCONTROLSETTINGS_H
