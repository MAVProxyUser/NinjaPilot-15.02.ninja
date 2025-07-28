/**
 ******************************************************************************
 *
 * @file       watchdogstatus.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: watchdogstatus.xml. 
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
#ifndef WATCHDOGSTATUS_H
#define WATCHDOGSTATUS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT WatchdogStatus: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 BootupFlags READ getBootupFlags WRITE setBootupFlags NOTIFY BootupFlagsChanged);
    Q_PROPERTY(quint16 ActiveFlags READ getActiveFlags WRITE setActiveFlags NOTIFY ActiveFlagsChanged);


public:
    // Field structure
    typedef struct {
        quint16 BootupFlags;
        quint16 ActiveFlags;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field BootupFlags information
    // Field ActiveFlags information

  
    // Constants
    static const quint32 OBJID = 0xA207FA7C;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    WatchdogStatus();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static WatchdogStatus* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint16 getBootupFlags() const;
    Q_INVOKABLE quint16 getActiveFlags() const;


public slots:
    void setBootupFlags(quint16 value);
    void setActiveFlags(quint16 value);


signals:
    void BootupFlagsChanged(quint16 value);
    void ActiveFlagsChanged(quint16 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // WATCHDOGSTATUS_H
