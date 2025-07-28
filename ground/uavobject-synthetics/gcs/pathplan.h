/**
 ******************************************************************************
 *
 * @file       pathplan.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: pathplan.xml. 
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
#ifndef PATHPLAN_H
#define PATHPLAN_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT PathPlan: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 WaypointCount READ getWaypointCount WRITE setWaypointCount NOTIFY WaypointCountChanged);
    Q_PROPERTY(quint16 PathActionCount READ getPathActionCount WRITE setPathActionCount NOTIFY PathActionCountChanged);
    Q_PROPERTY(quint8 Crc READ getCrc WRITE setCrc NOTIFY CrcChanged);


public:
    // Field structure
    typedef struct {
        quint16 WaypointCount;
        quint16 PathActionCount;
        quint8 Crc;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field WaypointCount information
    // Field PathActionCount information
    // Field Crc information

  
    // Constants
    static const quint32 OBJID = 0x82F5D500;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    PathPlan();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static PathPlan* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint16 getWaypointCount() const;
    Q_INVOKABLE quint16 getPathActionCount() const;
    Q_INVOKABLE quint8 getCrc() const;


public slots:
    void setWaypointCount(quint16 value);
    void setPathActionCount(quint16 value);
    void setCrc(quint8 value);


signals:
    void WaypointCountChanged(quint16 value);
    void PathActionCountChanged(quint16 value);
    void CrcChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // PATHPLAN_H
