/**
 ******************************************************************************
 *
 * @file       systemstats.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: systemstats.xml. 
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
#ifndef SYSTEMSTATS_H
#define SYSTEMSTATS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT SystemStats: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 FlightTime READ getFlightTime WRITE setFlightTime NOTIFY FlightTimeChanged);
    Q_PROPERTY(quint32 HeapRemaining READ getHeapRemaining WRITE setHeapRemaining NOTIFY HeapRemainingChanged);
    Q_PROPERTY(quint32 EventSystemWarningID READ getEventSystemWarningID WRITE setEventSystemWarningID NOTIFY EventSystemWarningIDChanged);
    Q_PROPERTY(quint32 ObjectManagerCallbackID READ getObjectManagerCallbackID WRITE setObjectManagerCallbackID NOTIFY ObjectManagerCallbackIDChanged);
    Q_PROPERTY(quint32 ObjectManagerQueueID READ getObjectManagerQueueID WRITE setObjectManagerQueueID NOTIFY ObjectManagerQueueIDChanged);
    Q_PROPERTY(quint16 IRQStackRemaining READ getIRQStackRemaining WRITE setIRQStackRemaining NOTIFY IRQStackRemainingChanged);
    Q_PROPERTY(quint16 SystemModStackRemaining READ getSystemModStackRemaining WRITE setSystemModStackRemaining NOTIFY SystemModStackRemainingChanged);
    Q_PROPERTY(quint16 SysSlotsFree READ getSysSlotsFree WRITE setSysSlotsFree NOTIFY SysSlotsFreeChanged);
    Q_PROPERTY(quint16 SysSlotsActive READ getSysSlotsActive WRITE setSysSlotsActive NOTIFY SysSlotsActiveChanged);
    Q_PROPERTY(quint16 UsrSlotsFree READ getUsrSlotsFree WRITE setUsrSlotsFree NOTIFY UsrSlotsFreeChanged);
    Q_PROPERTY(quint16 UsrSlotsActive READ getUsrSlotsActive WRITE setUsrSlotsActive NOTIFY UsrSlotsActiveChanged);
    Q_PROPERTY(quint8 CPULoad READ getCPULoad WRITE setCPULoad NOTIFY CPULoadChanged);
    Q_PROPERTY(qint8 CPUTemp READ getCPUTemp WRITE setCPUTemp NOTIFY CPUTempChanged);


public:
    // Field structure
    typedef struct {
        quint32 FlightTime;
        quint32 HeapRemaining;
        quint32 EventSystemWarningID;
        quint32 ObjectManagerCallbackID;
        quint32 ObjectManagerQueueID;
        quint16 IRQStackRemaining;
        quint16 SystemModStackRemaining;
        quint16 SysSlotsFree;
        quint16 SysSlotsActive;
        quint16 UsrSlotsFree;
        quint16 UsrSlotsActive;
        quint8 CPULoad;
        qint8 CPUTemp;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field FlightTime information
    // Field HeapRemaining information
    // Field EventSystemWarningID information
    // Field ObjectManagerCallbackID information
    // Field ObjectManagerQueueID information
    // Field IRQStackRemaining information
    // Field SystemModStackRemaining information
    // Field SysSlotsFree information
    // Field SysSlotsActive information
    // Field UsrSlotsFree information
    // Field UsrSlotsActive information
    // Field CPULoad information
    // Field CPUTemp information

  
    // Constants
    static const quint32 OBJID = 0x40BFFEFC;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    SystemStats();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static SystemStats* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint32 getFlightTime() const;
    Q_INVOKABLE quint32 getHeapRemaining() const;
    Q_INVOKABLE quint32 getEventSystemWarningID() const;
    Q_INVOKABLE quint32 getObjectManagerCallbackID() const;
    Q_INVOKABLE quint32 getObjectManagerQueueID() const;
    Q_INVOKABLE quint16 getIRQStackRemaining() const;
    Q_INVOKABLE quint16 getSystemModStackRemaining() const;
    Q_INVOKABLE quint16 getSysSlotsFree() const;
    Q_INVOKABLE quint16 getSysSlotsActive() const;
    Q_INVOKABLE quint16 getUsrSlotsFree() const;
    Q_INVOKABLE quint16 getUsrSlotsActive() const;
    Q_INVOKABLE quint8 getCPULoad() const;
    Q_INVOKABLE qint8 getCPUTemp() const;


public slots:
    void setFlightTime(quint32 value);
    void setHeapRemaining(quint32 value);
    void setEventSystemWarningID(quint32 value);
    void setObjectManagerCallbackID(quint32 value);
    void setObjectManagerQueueID(quint32 value);
    void setIRQStackRemaining(quint16 value);
    void setSystemModStackRemaining(quint16 value);
    void setSysSlotsFree(quint16 value);
    void setSysSlotsActive(quint16 value);
    void setUsrSlotsFree(quint16 value);
    void setUsrSlotsActive(quint16 value);
    void setCPULoad(quint8 value);
    void setCPUTemp(qint8 value);


signals:
    void FlightTimeChanged(quint32 value);
    void HeapRemainingChanged(quint32 value);
    void EventSystemWarningIDChanged(quint32 value);
    void ObjectManagerCallbackIDChanged(quint32 value);
    void ObjectManagerQueueIDChanged(quint32 value);
    void IRQStackRemainingChanged(quint16 value);
    void SystemModStackRemainingChanged(quint16 value);
    void SysSlotsFreeChanged(quint16 value);
    void SysSlotsActiveChanged(quint16 value);
    void UsrSlotsFreeChanged(quint16 value);
    void UsrSlotsActiveChanged(quint16 value);
    void CPULoadChanged(quint8 value);
    void CPUTempChanged(qint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // SYSTEMSTATS_H
