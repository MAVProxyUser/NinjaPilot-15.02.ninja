/**
 ******************************************************************************
 *
 * @file       gpsextendedstatus.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: gpsextendedstatus.xml. 
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
#ifndef GPSEXTENDEDSTATUS_H
#define GPSEXTENDEDSTATUS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT GPSExtendedStatus: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 FlightTime READ getFlightTime WRITE setFlightTime NOTIFY FlightTimeChanged);
    Q_PROPERTY(quint16 Options READ getOptions WRITE setOptions NOTIFY OptionsChanged);
    Q_PROPERTY(quint8 Status READ getStatus WRITE setStatus NOTIFY StatusChanged);
    Q_PROPERTY(quint8 BoardType_0 READ getBoardType_0 WRITE setBoardType_0 NOTIFY BoardType_0Changed);
    Q_PROPERTY(quint8 BoardType_1 READ getBoardType_1 WRITE setBoardType_1 NOTIFY BoardType_1Changed);
    Q_PROPERTY(quint8 FirmwareHash_0 READ getFirmwareHash_0 WRITE setFirmwareHash_0 NOTIFY FirmwareHash_0Changed);
    Q_PROPERTY(quint8 FirmwareHash_1 READ getFirmwareHash_1 WRITE setFirmwareHash_1 NOTIFY FirmwareHash_1Changed);
    Q_PROPERTY(quint8 FirmwareHash_2 READ getFirmwareHash_2 WRITE setFirmwareHash_2 NOTIFY FirmwareHash_2Changed);
    Q_PROPERTY(quint8 FirmwareHash_3 READ getFirmwareHash_3 WRITE setFirmwareHash_3 NOTIFY FirmwareHash_3Changed);
    Q_PROPERTY(quint8 FirmwareHash_4 READ getFirmwareHash_4 WRITE setFirmwareHash_4 NOTIFY FirmwareHash_4Changed);
    Q_PROPERTY(quint8 FirmwareHash_5 READ getFirmwareHash_5 WRITE setFirmwareHash_5 NOTIFY FirmwareHash_5Changed);
    Q_PROPERTY(quint8 FirmwareHash_6 READ getFirmwareHash_6 WRITE setFirmwareHash_6 NOTIFY FirmwareHash_6Changed);
    Q_PROPERTY(quint8 FirmwareHash_7 READ getFirmwareHash_7 WRITE setFirmwareHash_7 NOTIFY FirmwareHash_7Changed);
    Q_PROPERTY(quint8 FirmwareTag_0 READ getFirmwareTag_0 WRITE setFirmwareTag_0 NOTIFY FirmwareTag_0Changed);
    Q_PROPERTY(quint8 FirmwareTag_1 READ getFirmwareTag_1 WRITE setFirmwareTag_1 NOTIFY FirmwareTag_1Changed);
    Q_PROPERTY(quint8 FirmwareTag_2 READ getFirmwareTag_2 WRITE setFirmwareTag_2 NOTIFY FirmwareTag_2Changed);
    Q_PROPERTY(quint8 FirmwareTag_3 READ getFirmwareTag_3 WRITE setFirmwareTag_3 NOTIFY FirmwareTag_3Changed);
    Q_PROPERTY(quint8 FirmwareTag_4 READ getFirmwareTag_4 WRITE setFirmwareTag_4 NOTIFY FirmwareTag_4Changed);
    Q_PROPERTY(quint8 FirmwareTag_5 READ getFirmwareTag_5 WRITE setFirmwareTag_5 NOTIFY FirmwareTag_5Changed);
    Q_PROPERTY(quint8 FirmwareTag_6 READ getFirmwareTag_6 WRITE setFirmwareTag_6 NOTIFY FirmwareTag_6Changed);
    Q_PROPERTY(quint8 FirmwareTag_7 READ getFirmwareTag_7 WRITE setFirmwareTag_7 NOTIFY FirmwareTag_7Changed);
    Q_PROPERTY(quint8 FirmwareTag_8 READ getFirmwareTag_8 WRITE setFirmwareTag_8 NOTIFY FirmwareTag_8Changed);
    Q_PROPERTY(quint8 FirmwareTag_9 READ getFirmwareTag_9 WRITE setFirmwareTag_9 NOTIFY FirmwareTag_9Changed);
    Q_PROPERTY(quint8 FirmwareTag_10 READ getFirmwareTag_10 WRITE setFirmwareTag_10 NOTIFY FirmwareTag_10Changed);
    Q_PROPERTY(quint8 FirmwareTag_11 READ getFirmwareTag_11 WRITE setFirmwareTag_11 NOTIFY FirmwareTag_11Changed);
    Q_PROPERTY(quint8 FirmwareTag_12 READ getFirmwareTag_12 WRITE setFirmwareTag_12 NOTIFY FirmwareTag_12Changed);
    Q_PROPERTY(quint8 FirmwareTag_13 READ getFirmwareTag_13 WRITE setFirmwareTag_13 NOTIFY FirmwareTag_13Changed);
    Q_PROPERTY(quint8 FirmwareTag_14 READ getFirmwareTag_14 WRITE setFirmwareTag_14 NOTIFY FirmwareTag_14Changed);
    Q_PROPERTY(quint8 FirmwareTag_15 READ getFirmwareTag_15 WRITE setFirmwareTag_15 NOTIFY FirmwareTag_15Changed);
    Q_PROPERTY(quint8 FirmwareTag_16 READ getFirmwareTag_16 WRITE setFirmwareTag_16 NOTIFY FirmwareTag_16Changed);
    Q_PROPERTY(quint8 FirmwareTag_17 READ getFirmwareTag_17 WRITE setFirmwareTag_17 NOTIFY FirmwareTag_17Changed);
    Q_PROPERTY(quint8 FirmwareTag_18 READ getFirmwareTag_18 WRITE setFirmwareTag_18 NOTIFY FirmwareTag_18Changed);
    Q_PROPERTY(quint8 FirmwareTag_19 READ getFirmwareTag_19 WRITE setFirmwareTag_19 NOTIFY FirmwareTag_19Changed);
    Q_PROPERTY(quint8 FirmwareTag_20 READ getFirmwareTag_20 WRITE setFirmwareTag_20 NOTIFY FirmwareTag_20Changed);
    Q_PROPERTY(quint8 FirmwareTag_21 READ getFirmwareTag_21 WRITE setFirmwareTag_21 NOTIFY FirmwareTag_21Changed);
    Q_PROPERTY(quint8 FirmwareTag_22 READ getFirmwareTag_22 WRITE setFirmwareTag_22 NOTIFY FirmwareTag_22Changed);
    Q_PROPERTY(quint8 FirmwareTag_23 READ getFirmwareTag_23 WRITE setFirmwareTag_23 NOTIFY FirmwareTag_23Changed);
    Q_PROPERTY(quint8 FirmwareTag_24 READ getFirmwareTag_24 WRITE setFirmwareTag_24 NOTIFY FirmwareTag_24Changed);
    Q_PROPERTY(quint8 FirmwareTag_25 READ getFirmwareTag_25 WRITE setFirmwareTag_25 NOTIFY FirmwareTag_25Changed);


public:
    // Field structure
    typedef struct {
        quint32 FlightTime;
        quint16 Options;
        quint8 Status;
        quint8 BoardType[2];
        quint8 FirmwareHash[8];
        quint8 FirmwareTag[26];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field FlightTime information
    // Field Options information
    // Field Status information
    /* Enumeration options for field Status */
    typedef enum { STATUS_NONE=0, STATUS_GPSV9=1 } StatusOptions;
    // Field BoardType information
    /* Number of elements for field BoardType */
    static const quint32 BOARDTYPE_NUMELEM = 2;
    // Field FirmwareHash information
    /* Number of elements for field FirmwareHash */
    static const quint32 FIRMWAREHASH_NUMELEM = 8;
    // Field FirmwareTag information
    /* Number of elements for field FirmwareTag */
    static const quint32 FIRMWARETAG_NUMELEM = 26;

  
    // Constants
    static const quint32 OBJID = 0xEBB0477C;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    GPSExtendedStatus();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static GPSExtendedStatus* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint32 getFlightTime() const;
    Q_INVOKABLE quint16 getOptions() const;
    Q_INVOKABLE quint8 getStatus() const;
    Q_INVOKABLE quint8 getBoardType(quint32 index) const;
    Q_INVOKABLE quint8 getBoardType_0() const;
    Q_INVOKABLE quint8 getBoardType_1() const;
    Q_INVOKABLE quint8 getFirmwareHash(quint32 index) const;
    Q_INVOKABLE quint8 getFirmwareHash_0() const;
    Q_INVOKABLE quint8 getFirmwareHash_1() const;
    Q_INVOKABLE quint8 getFirmwareHash_2() const;
    Q_INVOKABLE quint8 getFirmwareHash_3() const;
    Q_INVOKABLE quint8 getFirmwareHash_4() const;
    Q_INVOKABLE quint8 getFirmwareHash_5() const;
    Q_INVOKABLE quint8 getFirmwareHash_6() const;
    Q_INVOKABLE quint8 getFirmwareHash_7() const;
    Q_INVOKABLE quint8 getFirmwareTag(quint32 index) const;
    Q_INVOKABLE quint8 getFirmwareTag_0() const;
    Q_INVOKABLE quint8 getFirmwareTag_1() const;
    Q_INVOKABLE quint8 getFirmwareTag_2() const;
    Q_INVOKABLE quint8 getFirmwareTag_3() const;
    Q_INVOKABLE quint8 getFirmwareTag_4() const;
    Q_INVOKABLE quint8 getFirmwareTag_5() const;
    Q_INVOKABLE quint8 getFirmwareTag_6() const;
    Q_INVOKABLE quint8 getFirmwareTag_7() const;
    Q_INVOKABLE quint8 getFirmwareTag_8() const;
    Q_INVOKABLE quint8 getFirmwareTag_9() const;
    Q_INVOKABLE quint8 getFirmwareTag_10() const;
    Q_INVOKABLE quint8 getFirmwareTag_11() const;
    Q_INVOKABLE quint8 getFirmwareTag_12() const;
    Q_INVOKABLE quint8 getFirmwareTag_13() const;
    Q_INVOKABLE quint8 getFirmwareTag_14() const;
    Q_INVOKABLE quint8 getFirmwareTag_15() const;
    Q_INVOKABLE quint8 getFirmwareTag_16() const;
    Q_INVOKABLE quint8 getFirmwareTag_17() const;
    Q_INVOKABLE quint8 getFirmwareTag_18() const;
    Q_INVOKABLE quint8 getFirmwareTag_19() const;
    Q_INVOKABLE quint8 getFirmwareTag_20() const;
    Q_INVOKABLE quint8 getFirmwareTag_21() const;
    Q_INVOKABLE quint8 getFirmwareTag_22() const;
    Q_INVOKABLE quint8 getFirmwareTag_23() const;
    Q_INVOKABLE quint8 getFirmwareTag_24() const;
    Q_INVOKABLE quint8 getFirmwareTag_25() const;


public slots:
    void setFlightTime(quint32 value);
    void setOptions(quint16 value);
    void setStatus(quint8 value);
    void setBoardType(quint32 index, quint8 value);
    void setBoardType_0(quint8 value);
    void setBoardType_1(quint8 value);
    void setFirmwareHash(quint32 index, quint8 value);
    void setFirmwareHash_0(quint8 value);
    void setFirmwareHash_1(quint8 value);
    void setFirmwareHash_2(quint8 value);
    void setFirmwareHash_3(quint8 value);
    void setFirmwareHash_4(quint8 value);
    void setFirmwareHash_5(quint8 value);
    void setFirmwareHash_6(quint8 value);
    void setFirmwareHash_7(quint8 value);
    void setFirmwareTag(quint32 index, quint8 value);
    void setFirmwareTag_0(quint8 value);
    void setFirmwareTag_1(quint8 value);
    void setFirmwareTag_2(quint8 value);
    void setFirmwareTag_3(quint8 value);
    void setFirmwareTag_4(quint8 value);
    void setFirmwareTag_5(quint8 value);
    void setFirmwareTag_6(quint8 value);
    void setFirmwareTag_7(quint8 value);
    void setFirmwareTag_8(quint8 value);
    void setFirmwareTag_9(quint8 value);
    void setFirmwareTag_10(quint8 value);
    void setFirmwareTag_11(quint8 value);
    void setFirmwareTag_12(quint8 value);
    void setFirmwareTag_13(quint8 value);
    void setFirmwareTag_14(quint8 value);
    void setFirmwareTag_15(quint8 value);
    void setFirmwareTag_16(quint8 value);
    void setFirmwareTag_17(quint8 value);
    void setFirmwareTag_18(quint8 value);
    void setFirmwareTag_19(quint8 value);
    void setFirmwareTag_20(quint8 value);
    void setFirmwareTag_21(quint8 value);
    void setFirmwareTag_22(quint8 value);
    void setFirmwareTag_23(quint8 value);
    void setFirmwareTag_24(quint8 value);
    void setFirmwareTag_25(quint8 value);


signals:
    void FlightTimeChanged(quint32 value);
    void OptionsChanged(quint16 value);
    void StatusChanged(quint8 value);
    void BoardTypeChanged(quint32 index, quint8 value);
    void BoardType_0Changed(quint8 value);
    void BoardType_1Changed(quint8 value);
    void FirmwareHashChanged(quint32 index, quint8 value);
    void FirmwareHash_0Changed(quint8 value);
    void FirmwareHash_1Changed(quint8 value);
    void FirmwareHash_2Changed(quint8 value);
    void FirmwareHash_3Changed(quint8 value);
    void FirmwareHash_4Changed(quint8 value);
    void FirmwareHash_5Changed(quint8 value);
    void FirmwareHash_6Changed(quint8 value);
    void FirmwareHash_7Changed(quint8 value);
    void FirmwareTagChanged(quint32 index, quint8 value);
    void FirmwareTag_0Changed(quint8 value);
    void FirmwareTag_1Changed(quint8 value);
    void FirmwareTag_2Changed(quint8 value);
    void FirmwareTag_3Changed(quint8 value);
    void FirmwareTag_4Changed(quint8 value);
    void FirmwareTag_5Changed(quint8 value);
    void FirmwareTag_6Changed(quint8 value);
    void FirmwareTag_7Changed(quint8 value);
    void FirmwareTag_8Changed(quint8 value);
    void FirmwareTag_9Changed(quint8 value);
    void FirmwareTag_10Changed(quint8 value);
    void FirmwareTag_11Changed(quint8 value);
    void FirmwareTag_12Changed(quint8 value);
    void FirmwareTag_13Changed(quint8 value);
    void FirmwareTag_14Changed(quint8 value);
    void FirmwareTag_15Changed(quint8 value);
    void FirmwareTag_16Changed(quint8 value);
    void FirmwareTag_17Changed(quint8 value);
    void FirmwareTag_18Changed(quint8 value);
    void FirmwareTag_19Changed(quint8 value);
    void FirmwareTag_20Changed(quint8 value);
    void FirmwareTag_21Changed(quint8 value);
    void FirmwareTag_22Changed(quint8 value);
    void FirmwareTag_23Changed(quint8 value);
    void FirmwareTag_24Changed(quint8 value);
    void FirmwareTag_25Changed(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // GPSEXTENDEDSTATUS_H
