/**
 ******************************************************************************
 *
 * @file       manualcontrolcommand.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: manualcontrolcommand.xml. 
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
#ifndef MANUALCONTROLCOMMAND_H
#define MANUALCONTROLCOMMAND_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT ManualControlCommand: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float Throttle READ getThrottle WRITE setThrottle NOTIFY ThrottleChanged);
    Q_PROPERTY(float Roll READ getRoll WRITE setRoll NOTIFY RollChanged);
    Q_PROPERTY(float Pitch READ getPitch WRITE setPitch NOTIFY PitchChanged);
    Q_PROPERTY(float Yaw READ getYaw WRITE setYaw NOTIFY YawChanged);
    Q_PROPERTY(float Collective READ getCollective WRITE setCollective NOTIFY CollectiveChanged);
    Q_PROPERTY(float Thrust READ getThrust WRITE setThrust NOTIFY ThrustChanged);
    Q_PROPERTY(quint16 Channel_0 READ getChannel_0 WRITE setChannel_0 NOTIFY Channel_0Changed);
    Q_PROPERTY(quint16 Channel_1 READ getChannel_1 WRITE setChannel_1 NOTIFY Channel_1Changed);
    Q_PROPERTY(quint16 Channel_2 READ getChannel_2 WRITE setChannel_2 NOTIFY Channel_2Changed);
    Q_PROPERTY(quint16 Channel_3 READ getChannel_3 WRITE setChannel_3 NOTIFY Channel_3Changed);
    Q_PROPERTY(quint16 Channel_4 READ getChannel_4 WRITE setChannel_4 NOTIFY Channel_4Changed);
    Q_PROPERTY(quint16 Channel_5 READ getChannel_5 WRITE setChannel_5 NOTIFY Channel_5Changed);
    Q_PROPERTY(quint16 Channel_6 READ getChannel_6 WRITE setChannel_6 NOTIFY Channel_6Changed);
    Q_PROPERTY(quint16 Channel_7 READ getChannel_7 WRITE setChannel_7 NOTIFY Channel_7Changed);
    Q_PROPERTY(quint16 Channel_8 READ getChannel_8 WRITE setChannel_8 NOTIFY Channel_8Changed);
    Q_PROPERTY(quint8 Connected READ getConnected WRITE setConnected NOTIFY ConnectedChanged);
    Q_PROPERTY(quint8 FlightModeSwitchPosition READ getFlightModeSwitchPosition WRITE setFlightModeSwitchPosition NOTIFY FlightModeSwitchPositionChanged);


public:
    // Field structure
    typedef struct {
        float Throttle;
        float Roll;
        float Pitch;
        float Yaw;
        float Collective;
        float Thrust;
        quint16 Channel[9];
        quint8 Connected;
        quint8 FlightModeSwitchPosition;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Throttle information
    // Field Roll information
    // Field Pitch information
    // Field Yaw information
    // Field Collective information
    // Field Thrust information
    // Field Channel information
    /* Number of elements for field Channel */
    static const quint32 CHANNEL_NUMELEM = 9;
    // Field Connected information
    /* Enumeration options for field Connected */
    typedef enum { CONNECTED_FALSE=0, CONNECTED_TRUE=1 } ConnectedOptions;
    // Field FlightModeSwitchPosition information

  
    // Constants
    static const quint32 OBJID = 0x161A2C98;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    ManualControlCommand();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static ManualControlCommand* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getThrottle() const;
    Q_INVOKABLE float getRoll() const;
    Q_INVOKABLE float getPitch() const;
    Q_INVOKABLE float getYaw() const;
    Q_INVOKABLE float getCollective() const;
    Q_INVOKABLE float getThrust() const;
    Q_INVOKABLE quint16 getChannel(quint32 index) const;
    Q_INVOKABLE quint16 getChannel_0() const;
    Q_INVOKABLE quint16 getChannel_1() const;
    Q_INVOKABLE quint16 getChannel_2() const;
    Q_INVOKABLE quint16 getChannel_3() const;
    Q_INVOKABLE quint16 getChannel_4() const;
    Q_INVOKABLE quint16 getChannel_5() const;
    Q_INVOKABLE quint16 getChannel_6() const;
    Q_INVOKABLE quint16 getChannel_7() const;
    Q_INVOKABLE quint16 getChannel_8() const;
    Q_INVOKABLE quint8 getConnected() const;
    Q_INVOKABLE quint8 getFlightModeSwitchPosition() const;


public slots:
    void setThrottle(float value);
    void setRoll(float value);
    void setPitch(float value);
    void setYaw(float value);
    void setCollective(float value);
    void setThrust(float value);
    void setChannel(quint32 index, quint16 value);
    void setChannel_0(quint16 value);
    void setChannel_1(quint16 value);
    void setChannel_2(quint16 value);
    void setChannel_3(quint16 value);
    void setChannel_4(quint16 value);
    void setChannel_5(quint16 value);
    void setChannel_6(quint16 value);
    void setChannel_7(quint16 value);
    void setChannel_8(quint16 value);
    void setConnected(quint8 value);
    void setFlightModeSwitchPosition(quint8 value);


signals:
    void ThrottleChanged(float value);
    void RollChanged(float value);
    void PitchChanged(float value);
    void YawChanged(float value);
    void CollectiveChanged(float value);
    void ThrustChanged(float value);
    void ChannelChanged(quint32 index, quint16 value);
    void Channel_0Changed(quint16 value);
    void Channel_1Changed(quint16 value);
    void Channel_2Changed(quint16 value);
    void Channel_3Changed(quint16 value);
    void Channel_4Changed(quint16 value);
    void Channel_5Changed(quint16 value);
    void Channel_6Changed(quint16 value);
    void Channel_7Changed(quint16 value);
    void Channel_8Changed(quint16 value);
    void ConnectedChanged(quint8 value);
    void FlightModeSwitchPositionChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // MANUALCONTROLCOMMAND_H
