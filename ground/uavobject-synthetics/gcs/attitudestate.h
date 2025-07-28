/**
 ******************************************************************************
 *
 * @file       attitudestate.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: attitudestate.xml. 
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
#ifndef ATTITUDESTATE_H
#define ATTITUDESTATE_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT AttitudeState: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float q1 READ getq1 WRITE setq1 NOTIFY q1Changed);
    Q_PROPERTY(float q2 READ getq2 WRITE setq2 NOTIFY q2Changed);
    Q_PROPERTY(float q3 READ getq3 WRITE setq3 NOTIFY q3Changed);
    Q_PROPERTY(float q4 READ getq4 WRITE setq4 NOTIFY q4Changed);
    Q_PROPERTY(float Roll READ getRoll WRITE setRoll NOTIFY RollChanged);
    Q_PROPERTY(float Pitch READ getPitch WRITE setPitch NOTIFY PitchChanged);
    Q_PROPERTY(float Yaw READ getYaw WRITE setYaw NOTIFY YawChanged);


public:
    // Field structure
    typedef struct {
        float q1;
        float q2;
        float q3;
        float q4;
        float Roll;
        float Pitch;
        float Yaw;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field q1 information
    // Field q2 information
    // Field q3 information
    // Field q4 information
    // Field Roll information
    // Field Pitch information
    // Field Yaw information

  
    // Constants
    static const quint32 OBJID = 0xD7E0D964;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    AttitudeState();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static AttitudeState* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getq1() const;
    Q_INVOKABLE float getq2() const;
    Q_INVOKABLE float getq3() const;
    Q_INVOKABLE float getq4() const;
    Q_INVOKABLE float getRoll() const;
    Q_INVOKABLE float getPitch() const;
    Q_INVOKABLE float getYaw() const;


public slots:
    void setq1(float value);
    void setq2(float value);
    void setq3(float value);
    void setq4(float value);
    void setRoll(float value);
    void setPitch(float value);
    void setYaw(float value);


signals:
    void q1Changed(float value);
    void q2Changed(float value);
    void q3Changed(float value);
    void q4Changed(float value);
    void RollChanged(float value);
    void PitchChanged(float value);
    void YawChanged(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // ATTITUDESTATE_H
