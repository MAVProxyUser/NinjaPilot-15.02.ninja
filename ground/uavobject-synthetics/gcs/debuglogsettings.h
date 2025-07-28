/**
 ******************************************************************************
 *
 * @file       debuglogsettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: debuglogsettings.xml. 
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
#ifndef DEBUGLOGSETTINGS_H
#define DEBUGLOGSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT DebugLogSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 LoggingEnabled READ getLoggingEnabled WRITE setLoggingEnabled NOTIFY LoggingEnabledChanged);


public:
    // Field structure
    typedef struct {
        quint8 LoggingEnabled;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field LoggingEnabled information
    /* Enumeration options for field LoggingEnabled */
    typedef enum { LOGGINGENABLED_DISABLED=0, LOGGINGENABLED_ONLYWHENARMED=1, LOGGINGENABLED_ALWAYS=2 } LoggingEnabledOptions;

  
    // Constants
    static const quint32 OBJID = 0x5E5903CC;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    DebugLogSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static DebugLogSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint8 getLoggingEnabled() const;


public slots:
    void setLoggingEnabled(quint8 value);


signals:
    void LoggingEnabledChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // DEBUGLOGSETTINGS_H
