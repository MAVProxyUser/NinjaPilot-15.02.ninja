/**
 ******************************************************************************
 *
 * @file       receiveractivity.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: receiveractivity.xml. 
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
#ifndef RECEIVERACTIVITY_H
#define RECEIVERACTIVITY_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT ReceiverActivity: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 ActiveGroup READ getActiveGroup WRITE setActiveGroup NOTIFY ActiveGroupChanged);
    Q_PROPERTY(quint8 ActiveChannel READ getActiveChannel WRITE setActiveChannel NOTIFY ActiveChannelChanged);


public:
    // Field structure
    typedef struct {
        quint8 ActiveGroup;
        quint8 ActiveChannel;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field ActiveGroup information
    /* Enumeration options for field ActiveGroup */
    typedef enum { ACTIVEGROUP_PWM=0, ACTIVEGROUP_PPM=1, ACTIVEGROUP_DSMMAINPORT=2, ACTIVEGROUP_DSMFLEXIPORT=3, ACTIVEGROUP_SBUS=4, ACTIVEGROUP_GCS=5, ACTIVEGROUP_OPLINK=6, ACTIVEGROUP_NONE=7 } ActiveGroupOptions;
    // Field ActiveChannel information

  
    // Constants
    static const quint32 OBJID = 0xFF531024;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    ReceiverActivity();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static ReceiverActivity* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint8 getActiveGroup() const;
    Q_INVOKABLE quint8 getActiveChannel() const;


public slots:
    void setActiveGroup(quint8 value);
    void setActiveChannel(quint8 value);


signals:
    void ActiveGroupChanged(quint8 value);
    void ActiveChannelChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // RECEIVERACTIVITY_H
