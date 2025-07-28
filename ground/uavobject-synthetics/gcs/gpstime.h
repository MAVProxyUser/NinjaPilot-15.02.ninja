/**
 ******************************************************************************
 *
 * @file       gpstime.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: gpstime.xml. 
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
#ifndef GPSTIME_H
#define GPSTIME_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT GPSTime: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(qint16 Year READ getYear WRITE setYear NOTIFY YearChanged);
    Q_PROPERTY(qint8 Month READ getMonth WRITE setMonth NOTIFY MonthChanged);
    Q_PROPERTY(qint8 Day READ getDay WRITE setDay NOTIFY DayChanged);
    Q_PROPERTY(qint8 Hour READ getHour WRITE setHour NOTIFY HourChanged);
    Q_PROPERTY(qint8 Minute READ getMinute WRITE setMinute NOTIFY MinuteChanged);
    Q_PROPERTY(qint8 Second READ getSecond WRITE setSecond NOTIFY SecondChanged);


public:
    // Field structure
    typedef struct {
        qint16 Year;
        qint8 Month;
        qint8 Day;
        qint8 Hour;
        qint8 Minute;
        qint8 Second;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Year information
    // Field Month information
    // Field Day information
    // Field Hour information
    // Field Minute information
    // Field Second information

  
    // Constants
    static const quint32 OBJID = 0xD4478084;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    GPSTime();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static GPSTime* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE qint16 getYear() const;
    Q_INVOKABLE qint8 getMonth() const;
    Q_INVOKABLE qint8 getDay() const;
    Q_INVOKABLE qint8 getHour() const;
    Q_INVOKABLE qint8 getMinute() const;
    Q_INVOKABLE qint8 getSecond() const;


public slots:
    void setYear(qint16 value);
    void setMonth(qint8 value);
    void setDay(qint8 value);
    void setHour(qint8 value);
    void setMinute(qint8 value);
    void setSecond(qint8 value);


signals:
    void YearChanged(qint16 value);
    void MonthChanged(qint8 value);
    void DayChanged(qint8 value);
    void HourChanged(qint8 value);
    void MinuteChanged(qint8 value);
    void SecondChanged(qint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // GPSTIME_H
