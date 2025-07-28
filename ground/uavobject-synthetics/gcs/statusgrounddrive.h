/**
 ******************************************************************************
 *
 * @file       statusgrounddrive.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: statusgrounddrive.xml. 
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
#ifndef STATUSGROUNDDRIVE_H
#define STATUSGROUNDDRIVE_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT StatusGroundDrive: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float NECommand_North READ getNECommand_North WRITE setNECommand_North NOTIFY NECommand_NorthChanged);
    Q_PROPERTY(float NECommand_East READ getNECommand_East WRITE setNECommand_East NOTIFY NECommand_EastChanged);
    Q_PROPERTY(float State_Yaw READ getState_Yaw WRITE setState_Yaw NOTIFY State_YawChanged);
    Q_PROPERTY(float State_Velocity READ getState_Velocity WRITE setState_Velocity NOTIFY State_VelocityChanged);
    Q_PROPERTY(float State_Thrust READ getState_Thrust WRITE setState_Thrust NOTIFY State_ThrustChanged);
    Q_PROPERTY(float BodyCommand_Forward READ getBodyCommand_Forward WRITE setBodyCommand_Forward NOTIFY BodyCommand_ForwardChanged);
    Q_PROPERTY(float BodyCommand_Right READ getBodyCommand_Right WRITE setBodyCommand_Right NOTIFY BodyCommand_RightChanged);
    Q_PROPERTY(float ControlCommand_Speed READ getControlCommand_Speed WRITE setControlCommand_Speed NOTIFY ControlCommand_SpeedChanged);
    Q_PROPERTY(float ControlCommand_Course READ getControlCommand_Course WRITE setControlCommand_Course NOTIFY ControlCommand_CourseChanged);
    Q_PROPERTY(quint8 ControlState READ getControlState WRITE setControlState NOTIFY ControlStateChanged);


public:
    // Field structure
    typedef struct {
        float NECommand[2];
        float State[3];
        float BodyCommand[2];
        float ControlCommand[2];
        quint8 ControlState;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field NECommand information
    /* Array element names for field NECommand */
    typedef enum { NECOMMAND_NORTH=0, NECOMMAND_EAST=1 } NECommandElem;
    /* Number of elements for field NECommand */
    static const quint32 NECOMMAND_NUMELEM = 2;
    // Field State information
    /* Array element names for field State */
    typedef enum { STATE_YAW=0, STATE_VELOCITY=1, STATE_THRUST=2 } StateElem;
    /* Number of elements for field State */
    static const quint32 STATE_NUMELEM = 3;
    // Field BodyCommand information
    /* Array element names for field BodyCommand */
    typedef enum { BODYCOMMAND_FORWARD=0, BODYCOMMAND_RIGHT=1 } BodyCommandElem;
    /* Number of elements for field BodyCommand */
    static const quint32 BODYCOMMAND_NUMELEM = 2;
    // Field ControlCommand information
    /* Array element names for field ControlCommand */
    typedef enum { CONTROLCOMMAND_SPEED=0, CONTROLCOMMAND_COURSE=1 } ControlCommandElem;
    /* Number of elements for field ControlCommand */
    static const quint32 CONTROLCOMMAND_NUMELEM = 2;
    // Field ControlState information
    /* Enumeration options for field ControlState */
    typedef enum { CONTROLSTATE_INACTIVE=0, CONTROLSTATE_ONTRACK=1, CONTROLSTATE_TURNAROUNDRIGHT=2, CONTROLSTATE_TURNAROUNDLEFT=3, CONTROLSTATE_BRAKE=4 } ControlStateOptions;

  
    // Constants
    static const quint32 OBJID = 0xC8A92AA8;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    StatusGroundDrive();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static StatusGroundDrive* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getNECommand(quint32 index) const;
    Q_INVOKABLE float getNECommand_North() const;
    Q_INVOKABLE float getNECommand_East() const;
    Q_INVOKABLE float getState(quint32 index) const;
    Q_INVOKABLE float getState_Yaw() const;
    Q_INVOKABLE float getState_Velocity() const;
    Q_INVOKABLE float getState_Thrust() const;
    Q_INVOKABLE float getBodyCommand(quint32 index) const;
    Q_INVOKABLE float getBodyCommand_Forward() const;
    Q_INVOKABLE float getBodyCommand_Right() const;
    Q_INVOKABLE float getControlCommand(quint32 index) const;
    Q_INVOKABLE float getControlCommand_Speed() const;
    Q_INVOKABLE float getControlCommand_Course() const;
    Q_INVOKABLE quint8 getControlState() const;


public slots:
    void setNECommand(quint32 index, float value);
    void setNECommand_North(float value);
    void setNECommand_East(float value);
    void setState(quint32 index, float value);
    void setState_Yaw(float value);
    void setState_Velocity(float value);
    void setState_Thrust(float value);
    void setBodyCommand(quint32 index, float value);
    void setBodyCommand_Forward(float value);
    void setBodyCommand_Right(float value);
    void setControlCommand(quint32 index, float value);
    void setControlCommand_Speed(float value);
    void setControlCommand_Course(float value);
    void setControlState(quint8 value);


signals:
    void NECommandChanged(quint32 index, float value);
    void NECommand_NorthChanged(float value);
    void NECommand_EastChanged(float value);
    void StateChanged(quint32 index, float value);
    void State_YawChanged(float value);
    void State_VelocityChanged(float value);
    void State_ThrustChanged(float value);
    void BodyCommandChanged(quint32 index, float value);
    void BodyCommand_ForwardChanged(float value);
    void BodyCommand_RightChanged(float value);
    void ControlCommandChanged(quint32 index, float value);
    void ControlCommand_SpeedChanged(float value);
    void ControlCommand_CourseChanged(float value);
    void ControlStateChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // STATUSGROUNDDRIVE_H
