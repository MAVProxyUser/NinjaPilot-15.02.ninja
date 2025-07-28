/**
 ******************************************************************************
 *
 * @file       waypoint.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: waypoint.xml. 
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
#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT Waypoint: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float Position_North READ getPosition_North WRITE setPosition_North NOTIFY Position_NorthChanged);
    Q_PROPERTY(float Position_East READ getPosition_East WRITE setPosition_East NOTIFY Position_EastChanged);
    Q_PROPERTY(float Position_Down READ getPosition_Down WRITE setPosition_Down NOTIFY Position_DownChanged);
    Q_PROPERTY(float Velocity READ getVelocity WRITE setVelocity NOTIFY VelocityChanged);
    Q_PROPERTY(quint8 Action READ getAction WRITE setAction NOTIFY ActionChanged);


public:
    // Field structure
    typedef struct {
        float Position[3];
        float Velocity;
        quint8 Action;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Position information
    /* Array element names for field Position */
    typedef enum { POSITION_NORTH=0, POSITION_EAST=1, POSITION_DOWN=2 } PositionElem;
    /* Number of elements for field Position */
    static const quint32 POSITION_NUMELEM = 3;
    // Field Velocity information
    // Field Action information

  
    // Constants
    static const quint32 OBJID = 0xD23852DC;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 0;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    Waypoint();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static Waypoint* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getPosition(quint32 index) const;
    Q_INVOKABLE float getPosition_North() const;
    Q_INVOKABLE float getPosition_East() const;
    Q_INVOKABLE float getPosition_Down() const;
    Q_INVOKABLE float getVelocity() const;
    Q_INVOKABLE quint8 getAction() const;


public slots:
    void setPosition(quint32 index, float value);
    void setPosition_North(float value);
    void setPosition_East(float value);
    void setPosition_Down(float value);
    void setVelocity(float value);
    void setAction(quint8 value);


signals:
    void PositionChanged(quint32 index, float value);
    void Position_NorthChanged(float value);
    void Position_EastChanged(float value);
    void Position_DownChanged(float value);
    void VelocityChanged(float value);
    void ActionChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // WAYPOINT_H
