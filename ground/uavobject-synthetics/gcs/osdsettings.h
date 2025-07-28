/**
 ******************************************************************************
 *
 * @file       osdsettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: osdsettings.xml. 
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
#ifndef OSDSETTINGS_H
#define OSDSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT OsdSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(qint16 AttitudeSetup_X READ getAttitudeSetup_X WRITE setAttitudeSetup_X NOTIFY AttitudeSetup_XChanged);
    Q_PROPERTY(qint16 AttitudeSetup_Y READ getAttitudeSetup_Y WRITE setAttitudeSetup_Y NOTIFY AttitudeSetup_YChanged);
    Q_PROPERTY(qint16 TimeSetup_X READ getTimeSetup_X WRITE setTimeSetup_X NOTIFY TimeSetup_XChanged);
    Q_PROPERTY(qint16 TimeSetup_Y READ getTimeSetup_Y WRITE setTimeSetup_Y NOTIFY TimeSetup_YChanged);
    Q_PROPERTY(qint16 BatterySetup_X READ getBatterySetup_X WRITE setBatterySetup_X NOTIFY BatterySetup_XChanged);
    Q_PROPERTY(qint16 BatterySetup_Y READ getBatterySetup_Y WRITE setBatterySetup_Y NOTIFY BatterySetup_YChanged);
    Q_PROPERTY(qint16 SpeedSetup_X READ getSpeedSetup_X WRITE setSpeedSetup_X NOTIFY SpeedSetup_XChanged);
    Q_PROPERTY(qint16 SpeedSetup_Y READ getSpeedSetup_Y WRITE setSpeedSetup_Y NOTIFY SpeedSetup_YChanged);
    Q_PROPERTY(qint16 AltitudeSetup_X READ getAltitudeSetup_X WRITE setAltitudeSetup_X NOTIFY AltitudeSetup_XChanged);
    Q_PROPERTY(qint16 AltitudeSetup_Y READ getAltitudeSetup_Y WRITE setAltitudeSetup_Y NOTIFY AltitudeSetup_YChanged);
    Q_PROPERTY(qint16 HeadingSetup_X READ getHeadingSetup_X WRITE setHeadingSetup_X NOTIFY HeadingSetup_XChanged);
    Q_PROPERTY(qint16 HeadingSetup_Y READ getHeadingSetup_Y WRITE setHeadingSetup_Y NOTIFY HeadingSetup_YChanged);
    Q_PROPERTY(quint8 Attitude READ getAttitude WRITE setAttitude NOTIFY AttitudeChanged);
    Q_PROPERTY(quint8 Time READ getTime WRITE setTime NOTIFY TimeChanged);
    Q_PROPERTY(quint8 Battery READ getBattery WRITE setBattery NOTIFY BatteryChanged);
    Q_PROPERTY(quint8 Speed READ getSpeed WRITE setSpeed NOTIFY SpeedChanged);
    Q_PROPERTY(quint8 Altitude READ getAltitude WRITE setAltitude NOTIFY AltitudeChanged);
    Q_PROPERTY(quint8 Heading READ getHeading WRITE setHeading NOTIFY HeadingChanged);
    Q_PROPERTY(quint8 Screen READ getScreen WRITE setScreen NOTIFY ScreenChanged);
    Q_PROPERTY(quint8 White READ getWhite WRITE setWhite NOTIFY WhiteChanged);
    Q_PROPERTY(quint8 Black READ getBlack WRITE setBlack NOTIFY BlackChanged);
    Q_PROPERTY(quint8 AltitudeSource READ getAltitudeSource WRITE setAltitudeSource NOTIFY AltitudeSourceChanged);


public:
    // Field structure
    typedef struct {
        qint16 AttitudeSetup[2];
        qint16 TimeSetup[2];
        qint16 BatterySetup[2];
        qint16 SpeedSetup[2];
        qint16 AltitudeSetup[2];
        qint16 HeadingSetup[2];
        quint8 Attitude;
        quint8 Time;
        quint8 Battery;
        quint8 Speed;
        quint8 Altitude;
        quint8 Heading;
        quint8 Screen;
        quint8 White;
        quint8 Black;
        quint8 AltitudeSource;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field AttitudeSetup information
    /* Array element names for field AttitudeSetup */
    typedef enum { ATTITUDESETUP_X=0, ATTITUDESETUP_Y=1 } AttitudeSetupElem;
    /* Number of elements for field AttitudeSetup */
    static const quint32 ATTITUDESETUP_NUMELEM = 2;
    // Field TimeSetup information
    /* Array element names for field TimeSetup */
    typedef enum { TIMESETUP_X=0, TIMESETUP_Y=1 } TimeSetupElem;
    /* Number of elements for field TimeSetup */
    static const quint32 TIMESETUP_NUMELEM = 2;
    // Field BatterySetup information
    /* Array element names for field BatterySetup */
    typedef enum { BATTERYSETUP_X=0, BATTERYSETUP_Y=1 } BatterySetupElem;
    /* Number of elements for field BatterySetup */
    static const quint32 BATTERYSETUP_NUMELEM = 2;
    // Field SpeedSetup information
    /* Array element names for field SpeedSetup */
    typedef enum { SPEEDSETUP_X=0, SPEEDSETUP_Y=1 } SpeedSetupElem;
    /* Number of elements for field SpeedSetup */
    static const quint32 SPEEDSETUP_NUMELEM = 2;
    // Field AltitudeSetup information
    /* Array element names for field AltitudeSetup */
    typedef enum { ALTITUDESETUP_X=0, ALTITUDESETUP_Y=1 } AltitudeSetupElem;
    /* Number of elements for field AltitudeSetup */
    static const quint32 ALTITUDESETUP_NUMELEM = 2;
    // Field HeadingSetup information
    /* Array element names for field HeadingSetup */
    typedef enum { HEADINGSETUP_X=0, HEADINGSETUP_Y=1 } HeadingSetupElem;
    /* Number of elements for field HeadingSetup */
    static const quint32 HEADINGSETUP_NUMELEM = 2;
    // Field Attitude information
    /* Enumeration options for field Attitude */
    typedef enum { ATTITUDE_DISABLED=0, ATTITUDE_ENABLED=1 } AttitudeOptions;
    // Field Time information
    /* Enumeration options for field Time */
    typedef enum { TIME_DISABLED=0, TIME_ENABLED=1 } TimeOptions;
    // Field Battery information
    /* Enumeration options for field Battery */
    typedef enum { BATTERY_DISABLED=0, BATTERY_ENABLED=1 } BatteryOptions;
    // Field Speed information
    /* Enumeration options for field Speed */
    typedef enum { SPEED_DISABLED=0, SPEED_ENABLED=1 } SpeedOptions;
    // Field Altitude information
    /* Enumeration options for field Altitude */
    typedef enum { ALTITUDE_DISABLED=0, ALTITUDE_ENABLED=1 } AltitudeOptions;
    // Field Heading information
    /* Enumeration options for field Heading */
    typedef enum { HEADING_DISABLED=0, HEADING_ENABLED=1 } HeadingOptions;
    // Field Screen information
    // Field White information
    // Field Black information
    // Field AltitudeSource information
    /* Enumeration options for field AltitudeSource */
    typedef enum { ALTITUDESOURCE_GPS=0, ALTITUDESOURCE_BARO=1 } AltitudeSourceOptions;

  
    // Constants
    static const quint32 OBJID = 0xDCBBA81A;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    OsdSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static OsdSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE qint16 getAttitudeSetup(quint32 index) const;
    Q_INVOKABLE qint16 getAttitudeSetup_X() const;
    Q_INVOKABLE qint16 getAttitudeSetup_Y() const;
    Q_INVOKABLE qint16 getTimeSetup(quint32 index) const;
    Q_INVOKABLE qint16 getTimeSetup_X() const;
    Q_INVOKABLE qint16 getTimeSetup_Y() const;
    Q_INVOKABLE qint16 getBatterySetup(quint32 index) const;
    Q_INVOKABLE qint16 getBatterySetup_X() const;
    Q_INVOKABLE qint16 getBatterySetup_Y() const;
    Q_INVOKABLE qint16 getSpeedSetup(quint32 index) const;
    Q_INVOKABLE qint16 getSpeedSetup_X() const;
    Q_INVOKABLE qint16 getSpeedSetup_Y() const;
    Q_INVOKABLE qint16 getAltitudeSetup(quint32 index) const;
    Q_INVOKABLE qint16 getAltitudeSetup_X() const;
    Q_INVOKABLE qint16 getAltitudeSetup_Y() const;
    Q_INVOKABLE qint16 getHeadingSetup(quint32 index) const;
    Q_INVOKABLE qint16 getHeadingSetup_X() const;
    Q_INVOKABLE qint16 getHeadingSetup_Y() const;
    Q_INVOKABLE quint8 getAttitude() const;
    Q_INVOKABLE quint8 getTime() const;
    Q_INVOKABLE quint8 getBattery() const;
    Q_INVOKABLE quint8 getSpeed() const;
    Q_INVOKABLE quint8 getAltitude() const;
    Q_INVOKABLE quint8 getHeading() const;
    Q_INVOKABLE quint8 getScreen() const;
    Q_INVOKABLE quint8 getWhite() const;
    Q_INVOKABLE quint8 getBlack() const;
    Q_INVOKABLE quint8 getAltitudeSource() const;


public slots:
    void setAttitudeSetup(quint32 index, qint16 value);
    void setAttitudeSetup_X(qint16 value);
    void setAttitudeSetup_Y(qint16 value);
    void setTimeSetup(quint32 index, qint16 value);
    void setTimeSetup_X(qint16 value);
    void setTimeSetup_Y(qint16 value);
    void setBatterySetup(quint32 index, qint16 value);
    void setBatterySetup_X(qint16 value);
    void setBatterySetup_Y(qint16 value);
    void setSpeedSetup(quint32 index, qint16 value);
    void setSpeedSetup_X(qint16 value);
    void setSpeedSetup_Y(qint16 value);
    void setAltitudeSetup(quint32 index, qint16 value);
    void setAltitudeSetup_X(qint16 value);
    void setAltitudeSetup_Y(qint16 value);
    void setHeadingSetup(quint32 index, qint16 value);
    void setHeadingSetup_X(qint16 value);
    void setHeadingSetup_Y(qint16 value);
    void setAttitude(quint8 value);
    void setTime(quint8 value);
    void setBattery(quint8 value);
    void setSpeed(quint8 value);
    void setAltitude(quint8 value);
    void setHeading(quint8 value);
    void setScreen(quint8 value);
    void setWhite(quint8 value);
    void setBlack(quint8 value);
    void setAltitudeSource(quint8 value);


signals:
    void AttitudeSetupChanged(quint32 index, qint16 value);
    void AttitudeSetup_XChanged(qint16 value);
    void AttitudeSetup_YChanged(qint16 value);
    void TimeSetupChanged(quint32 index, qint16 value);
    void TimeSetup_XChanged(qint16 value);
    void TimeSetup_YChanged(qint16 value);
    void BatterySetupChanged(quint32 index, qint16 value);
    void BatterySetup_XChanged(qint16 value);
    void BatterySetup_YChanged(qint16 value);
    void SpeedSetupChanged(quint32 index, qint16 value);
    void SpeedSetup_XChanged(qint16 value);
    void SpeedSetup_YChanged(qint16 value);
    void AltitudeSetupChanged(quint32 index, qint16 value);
    void AltitudeSetup_XChanged(qint16 value);
    void AltitudeSetup_YChanged(qint16 value);
    void HeadingSetupChanged(quint32 index, qint16 value);
    void HeadingSetup_XChanged(qint16 value);
    void HeadingSetup_YChanged(qint16 value);
    void AttitudeChanged(quint8 value);
    void TimeChanged(quint8 value);
    void BatteryChanged(quint8 value);
    void SpeedChanged(quint8 value);
    void AltitudeChanged(quint8 value);
    void HeadingChanged(quint8 value);
    void ScreenChanged(quint8 value);
    void WhiteChanged(quint8 value);
    void BlackChanged(quint8 value);
    void AltitudeSourceChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // OSDSETTINGS_H
