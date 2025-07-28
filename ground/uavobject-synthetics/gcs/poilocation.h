/**
 ******************************************************************************
 *
 * @file       poilocation.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: poilocation.xml. 
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
#ifndef POILOCATION_H
#define POILOCATION_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT PoiLocation: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float North READ getNorth WRITE setNorth NOTIFY NorthChanged);
    Q_PROPERTY(float East READ getEast WRITE setEast NOTIFY EastChanged);
    Q_PROPERTY(float Down READ getDown WRITE setDown NOTIFY DownChanged);


public:
    // Field structure
    typedef struct {
        float North;
        float East;
        float Down;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field North information
    // Field East information
    // Field Down information

  
    // Constants
    static const quint32 OBJID = 0x17E829B8;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    PoiLocation();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static PoiLocation* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getNorth() const;
    Q_INVOKABLE float getEast() const;
    Q_INVOKABLE float getDown() const;


public slots:
    void setNorth(float value);
    void setEast(float value);
    void setDown(float value);


signals:
    void NorthChanged(float value);
    void EastChanged(float value);
    void DownChanged(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // POILOCATION_H
