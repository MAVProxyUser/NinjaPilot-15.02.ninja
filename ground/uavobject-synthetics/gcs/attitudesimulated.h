/**
 ******************************************************************************
 *
 * @file       attitudesimulated.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: attitudesimulated.xml. 
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
#ifndef ATTITUDESIMULATED_H
#define ATTITUDESIMULATED_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT AttitudeSimulated: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float q1 READ getq1 WRITE setq1 NOTIFY q1Changed);
    Q_PROPERTY(float q2 READ getq2 WRITE setq2 NOTIFY q2Changed);
    Q_PROPERTY(float q3 READ getq3 WRITE setq3 NOTIFY q3Changed);
    Q_PROPERTY(float q4 READ getq4 WRITE setq4 NOTIFY q4Changed);
    Q_PROPERTY(float Roll READ getRoll WRITE setRoll NOTIFY RollChanged);
    Q_PROPERTY(float Pitch READ getPitch WRITE setPitch NOTIFY PitchChanged);
    Q_PROPERTY(float Yaw READ getYaw WRITE setYaw NOTIFY YawChanged);
    Q_PROPERTY(float Velocity_North READ getVelocity_North WRITE setVelocity_North NOTIFY Velocity_NorthChanged);
    Q_PROPERTY(float Velocity_East READ getVelocity_East WRITE setVelocity_East NOTIFY Velocity_EastChanged);
    Q_PROPERTY(float Velocity_Down READ getVelocity_Down WRITE setVelocity_Down NOTIFY Velocity_DownChanged);
    Q_PROPERTY(float Position_North READ getPosition_North WRITE setPosition_North NOTIFY Position_NorthChanged);
    Q_PROPERTY(float Position_East READ getPosition_East WRITE setPosition_East NOTIFY Position_EastChanged);
    Q_PROPERTY(float Position_Down READ getPosition_Down WRITE setPosition_Down NOTIFY Position_DownChanged);


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
        float Velocity[3];
        float Position[3];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field q1 information
    // Field q2 information
    // Field q3 information
    // Field q4 information
    // Field Roll information
    // Field Pitch information
    // Field Yaw information
    // Field Velocity information
    /* Array element names for field Velocity */
    typedef enum { VELOCITY_NORTH=0, VELOCITY_EAST=1, VELOCITY_DOWN=2 } VelocityElem;
    /* Number of elements for field Velocity */
    static const quint32 VELOCITY_NUMELEM = 3;
    // Field Position information
    /* Array element names for field Position */
    typedef enum { POSITION_NORTH=0, POSITION_EAST=1, POSITION_DOWN=2 } PositionElem;
    /* Number of elements for field Position */
    static const quint32 POSITION_NUMELEM = 3;

  
    // Constants
    static const quint32 OBJID = 0x9266CE74;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    AttitudeSimulated();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static AttitudeSimulated* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getq1() const;
    Q_INVOKABLE float getq2() const;
    Q_INVOKABLE float getq3() const;
    Q_INVOKABLE float getq4() const;
    Q_INVOKABLE float getRoll() const;
    Q_INVOKABLE float getPitch() const;
    Q_INVOKABLE float getYaw() const;
    Q_INVOKABLE float getVelocity(quint32 index) const;
    Q_INVOKABLE float getVelocity_North() const;
    Q_INVOKABLE float getVelocity_East() const;
    Q_INVOKABLE float getVelocity_Down() const;
    Q_INVOKABLE float getPosition(quint32 index) const;
    Q_INVOKABLE float getPosition_North() const;
    Q_INVOKABLE float getPosition_East() const;
    Q_INVOKABLE float getPosition_Down() const;


public slots:
    void setq1(float value);
    void setq2(float value);
    void setq3(float value);
    void setq4(float value);
    void setRoll(float value);
    void setPitch(float value);
    void setYaw(float value);
    void setVelocity(quint32 index, float value);
    void setVelocity_North(float value);
    void setVelocity_East(float value);
    void setVelocity_Down(float value);
    void setPosition(quint32 index, float value);
    void setPosition_North(float value);
    void setPosition_East(float value);
    void setPosition_Down(float value);


signals:
    void q1Changed(float value);
    void q2Changed(float value);
    void q3Changed(float value);
    void q4Changed(float value);
    void RollChanged(float value);
    void PitchChanged(float value);
    void YawChanged(float value);
    void VelocityChanged(quint32 index, float value);
    void Velocity_NorthChanged(float value);
    void Velocity_EastChanged(float value);
    void Velocity_DownChanged(float value);
    void PositionChanged(quint32 index, float value);
    void Position_NorthChanged(float value);
    void Position_EastChanged(float value);
    void Position_DownChanged(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // ATTITUDESIMULATED_H
