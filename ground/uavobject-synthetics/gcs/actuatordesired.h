/**
 ******************************************************************************
 *
 * @file       actuatordesired.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: actuatordesired.xml. 
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
#ifndef ACTUATORDESIRED_H
#define ACTUATORDESIRED_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT ActuatorDesired: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float Roll READ getRoll WRITE setRoll NOTIFY RollChanged);
    Q_PROPERTY(float Pitch READ getPitch WRITE setPitch NOTIFY PitchChanged);
    Q_PROPERTY(float Yaw READ getYaw WRITE setYaw NOTIFY YawChanged);
    Q_PROPERTY(float Thrust READ getThrust WRITE setThrust NOTIFY ThrustChanged);
    Q_PROPERTY(float UpdateTime READ getUpdateTime WRITE setUpdateTime NOTIFY UpdateTimeChanged);
    Q_PROPERTY(float NumLongUpdates READ getNumLongUpdates WRITE setNumLongUpdates NOTIFY NumLongUpdatesChanged);


public:
    // Field structure
    typedef struct {
        float Roll;
        float Pitch;
        float Yaw;
        float Thrust;
        float UpdateTime;
        float NumLongUpdates;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Roll information
    // Field Pitch information
    // Field Yaw information
    // Field Thrust information
    // Field UpdateTime information
    // Field NumLongUpdates information

  
    // Constants
    static const quint32 OBJID = 0xEAE65C28;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    ActuatorDesired();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static ActuatorDesired* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getRoll() const;
    Q_INVOKABLE float getPitch() const;
    Q_INVOKABLE float getYaw() const;
    Q_INVOKABLE float getThrust() const;
    Q_INVOKABLE float getUpdateTime() const;
    Q_INVOKABLE float getNumLongUpdates() const;


public slots:
    void setRoll(float value);
    void setPitch(float value);
    void setYaw(float value);
    void setThrust(float value);
    void setUpdateTime(float value);
    void setNumLongUpdates(float value);


signals:
    void RollChanged(float value);
    void PitchChanged(float value);
    void YawChanged(float value);
    void ThrustChanged(float value);
    void UpdateTimeChanged(float value);
    void NumLongUpdatesChanged(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // ACTUATORDESIRED_H
