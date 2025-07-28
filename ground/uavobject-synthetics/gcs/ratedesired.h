/**
 ******************************************************************************
 *
 * @file       ratedesired.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: ratedesired.xml. 
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
#ifndef RATEDESIRED_H
#define RATEDESIRED_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT RateDesired: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float Roll READ getRoll WRITE setRoll NOTIFY RollChanged);
    Q_PROPERTY(float Pitch READ getPitch WRITE setPitch NOTIFY PitchChanged);
    Q_PROPERTY(float Yaw READ getYaw WRITE setYaw NOTIFY YawChanged);
    Q_PROPERTY(float Thrust READ getThrust WRITE setThrust NOTIFY ThrustChanged);


public:
    // Field structure
    typedef struct {
        float Roll;
        float Pitch;
        float Yaw;
        float Thrust;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Roll information
    // Field Pitch information
    // Field Yaw information
    // Field Thrust information

  
    // Constants
    static const quint32 OBJID = 0x3642723E;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    RateDesired();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static RateDesired* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getRoll() const;
    Q_INVOKABLE float getPitch() const;
    Q_INVOKABLE float getYaw() const;
    Q_INVOKABLE float getThrust() const;


public slots:
    void setRoll(float value);
    void setPitch(float value);
    void setYaw(float value);
    void setThrust(float value);


signals:
    void RollChanged(float value);
    void PitchChanged(float value);
    void YawChanged(float value);
    void ThrustChanged(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // RATEDESIRED_H
