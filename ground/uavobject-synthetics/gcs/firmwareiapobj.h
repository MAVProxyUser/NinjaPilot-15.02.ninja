/**
 ******************************************************************************
 *
 * @file       firmwareiapobj.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: firmwareiapobj.xml. 
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
#ifndef FIRMWAREIAPOBJ_H
#define FIRMWAREIAPOBJ_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT FirmwareIAPObj: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 crc READ getcrc WRITE setcrc NOTIFY crcChanged);
    Q_PROPERTY(quint16 Command READ getCommand WRITE setCommand NOTIFY CommandChanged);
    Q_PROPERTY(quint16 BoardRevision READ getBoardRevision WRITE setBoardRevision NOTIFY BoardRevisionChanged);
    Q_PROPERTY(quint8 CPUSerial_0 READ getCPUSerial_0 WRITE setCPUSerial_0 NOTIFY CPUSerial_0Changed);
    Q_PROPERTY(quint8 CPUSerial_1 READ getCPUSerial_1 WRITE setCPUSerial_1 NOTIFY CPUSerial_1Changed);
    Q_PROPERTY(quint8 CPUSerial_2 READ getCPUSerial_2 WRITE setCPUSerial_2 NOTIFY CPUSerial_2Changed);
    Q_PROPERTY(quint8 CPUSerial_3 READ getCPUSerial_3 WRITE setCPUSerial_3 NOTIFY CPUSerial_3Changed);
    Q_PROPERTY(quint8 CPUSerial_4 READ getCPUSerial_4 WRITE setCPUSerial_4 NOTIFY CPUSerial_4Changed);
    Q_PROPERTY(quint8 CPUSerial_5 READ getCPUSerial_5 WRITE setCPUSerial_5 NOTIFY CPUSerial_5Changed);
    Q_PROPERTY(quint8 CPUSerial_6 READ getCPUSerial_6 WRITE setCPUSerial_6 NOTIFY CPUSerial_6Changed);
    Q_PROPERTY(quint8 CPUSerial_7 READ getCPUSerial_7 WRITE setCPUSerial_7 NOTIFY CPUSerial_7Changed);
    Q_PROPERTY(quint8 CPUSerial_8 READ getCPUSerial_8 WRITE setCPUSerial_8 NOTIFY CPUSerial_8Changed);
    Q_PROPERTY(quint8 CPUSerial_9 READ getCPUSerial_9 WRITE setCPUSerial_9 NOTIFY CPUSerial_9Changed);
    Q_PROPERTY(quint8 CPUSerial_10 READ getCPUSerial_10 WRITE setCPUSerial_10 NOTIFY CPUSerial_10Changed);
    Q_PROPERTY(quint8 CPUSerial_11 READ getCPUSerial_11 WRITE setCPUSerial_11 NOTIFY CPUSerial_11Changed);
    Q_PROPERTY(quint8 BoardType READ getBoardType WRITE setBoardType NOTIFY BoardTypeChanged);
    Q_PROPERTY(quint8 BootloaderRevision READ getBootloaderRevision WRITE setBootloaderRevision NOTIFY BootloaderRevisionChanged);
    Q_PROPERTY(quint8 ArmReset READ getArmReset WRITE setArmReset NOTIFY ArmResetChanged);


public:
    // Field structure
    typedef struct {
        quint32 crc;
        quint16 Command;
        quint16 BoardRevision;
        quint8 Description[100];
        quint8 CPUSerial[12];
        quint8 BoardType;
        quint8 BootloaderRevision;
        quint8 ArmReset;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field crc information
    // Field Command information
    // Field BoardRevision information
    // Field Description information
    /* Number of elements for field Description */
    static const quint32 DESCRIPTION_NUMELEM = 100;
    // Field CPUSerial information
    /* Number of elements for field CPUSerial */
    static const quint32 CPUSERIAL_NUMELEM = 12;
    // Field BoardType information
    // Field BootloaderRevision information
    // Field ArmReset information

  
    // Constants
    static const quint32 OBJID = 0x8328F252;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    FirmwareIAPObj();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static FirmwareIAPObj* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint32 getcrc() const;
    Q_INVOKABLE quint16 getCommand() const;
    Q_INVOKABLE quint16 getBoardRevision() const;
    Q_INVOKABLE quint8 getCPUSerial(quint32 index) const;
    Q_INVOKABLE quint8 getCPUSerial_0() const;
    Q_INVOKABLE quint8 getCPUSerial_1() const;
    Q_INVOKABLE quint8 getCPUSerial_2() const;
    Q_INVOKABLE quint8 getCPUSerial_3() const;
    Q_INVOKABLE quint8 getCPUSerial_4() const;
    Q_INVOKABLE quint8 getCPUSerial_5() const;
    Q_INVOKABLE quint8 getCPUSerial_6() const;
    Q_INVOKABLE quint8 getCPUSerial_7() const;
    Q_INVOKABLE quint8 getCPUSerial_8() const;
    Q_INVOKABLE quint8 getCPUSerial_9() const;
    Q_INVOKABLE quint8 getCPUSerial_10() const;
    Q_INVOKABLE quint8 getCPUSerial_11() const;
    Q_INVOKABLE quint8 getBoardType() const;
    Q_INVOKABLE quint8 getBootloaderRevision() const;
    Q_INVOKABLE quint8 getArmReset() const;


public slots:
    void setcrc(quint32 value);
    void setCommand(quint16 value);
    void setBoardRevision(quint16 value);
    void setCPUSerial(quint32 index, quint8 value);
    void setCPUSerial_0(quint8 value);
    void setCPUSerial_1(quint8 value);
    void setCPUSerial_2(quint8 value);
    void setCPUSerial_3(quint8 value);
    void setCPUSerial_4(quint8 value);
    void setCPUSerial_5(quint8 value);
    void setCPUSerial_6(quint8 value);
    void setCPUSerial_7(quint8 value);
    void setCPUSerial_8(quint8 value);
    void setCPUSerial_9(quint8 value);
    void setCPUSerial_10(quint8 value);
    void setCPUSerial_11(quint8 value);
    void setBoardType(quint8 value);
    void setBootloaderRevision(quint8 value);
    void setArmReset(quint8 value);


signals:
    void crcChanged(quint32 value);
    void CommandChanged(quint16 value);
    void BoardRevisionChanged(quint16 value);
    void CPUSerialChanged(quint32 index, quint8 value);
    void CPUSerial_0Changed(quint8 value);
    void CPUSerial_1Changed(quint8 value);
    void CPUSerial_2Changed(quint8 value);
    void CPUSerial_3Changed(quint8 value);
    void CPUSerial_4Changed(quint8 value);
    void CPUSerial_5Changed(quint8 value);
    void CPUSerial_6Changed(quint8 value);
    void CPUSerial_7Changed(quint8 value);
    void CPUSerial_8Changed(quint8 value);
    void CPUSerial_9Changed(quint8 value);
    void CPUSerial_10Changed(quint8 value);
    void CPUSerial_11Changed(quint8 value);
    void BoardTypeChanged(quint8 value);
    void BootloaderRevisionChanged(quint8 value);
    void ArmResetChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // FIRMWAREIAPOBJ_H
