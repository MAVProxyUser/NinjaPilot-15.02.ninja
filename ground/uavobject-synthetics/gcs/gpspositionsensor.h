/**
 ******************************************************************************
 *
 * @file       gpspositionsensor.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: gpspositionsensor.xml. 
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
#ifndef GPSPOSITIONSENSOR_H
#define GPSPOSITIONSENSOR_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT GPSPositionSensor: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 Latitude READ getLatitude WRITE setLatitude NOTIFY LatitudeChanged);
    Q_PROPERTY(qint32 Longitude READ getLongitude WRITE setLongitude NOTIFY LongitudeChanged);
    Q_PROPERTY(float Altitude READ getAltitude WRITE setAltitude NOTIFY AltitudeChanged);
    Q_PROPERTY(float GeoidSeparation READ getGeoidSeparation WRITE setGeoidSeparation NOTIFY GeoidSeparationChanged);
    Q_PROPERTY(float Heading READ getHeading WRITE setHeading NOTIFY HeadingChanged);
    Q_PROPERTY(float Groundspeed READ getGroundspeed WRITE setGroundspeed NOTIFY GroundspeedChanged);
    Q_PROPERTY(float PDOP READ getPDOP WRITE setPDOP NOTIFY PDOPChanged);
    Q_PROPERTY(float HDOP READ getHDOP WRITE setHDOP NOTIFY HDOPChanged);
    Q_PROPERTY(float VDOP READ getVDOP WRITE setVDOP NOTIFY VDOPChanged);
    Q_PROPERTY(quint8 Status READ getStatus WRITE setStatus NOTIFY StatusChanged);
    Q_PROPERTY(qint8 Satellites READ getSatellites WRITE setSatellites NOTIFY SatellitesChanged);
    Q_PROPERTY(quint8 SensorType READ getSensorType WRITE setSensorType NOTIFY SensorTypeChanged);
    Q_PROPERTY(quint8 AutoConfigStatus READ getAutoConfigStatus WRITE setAutoConfigStatus NOTIFY AutoConfigStatusChanged);


public:
    // Field structure
    typedef struct {
        qint32 Latitude;
        qint32 Longitude;
        float Altitude;
        float GeoidSeparation;
        float Heading;
        float Groundspeed;
        float PDOP;
        float HDOP;
        float VDOP;
        quint8 Status;
        qint8 Satellites;
        quint8 SensorType;
        quint8 AutoConfigStatus;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Latitude information
    // Field Longitude information
    // Field Altitude information
    // Field GeoidSeparation information
    // Field Heading information
    // Field Groundspeed information
    // Field PDOP information
    // Field HDOP information
    // Field VDOP information
    // Field Status information
    /* Enumeration options for field Status */
    typedef enum { STATUS_NOGPS=0, STATUS_NOFIX=1, STATUS_FIX2D=2, STATUS_FIX3D=3 } StatusOptions;
    // Field Satellites information
    // Field SensorType information
    /* Enumeration options for field SensorType */
    typedef enum { SENSORTYPE_UNKNOWN=0, SENSORTYPE_NMEA=1, SENSORTYPE_UBX=2, SENSORTYPE_UBX7=3, SENSORTYPE_UBX8=4 } SensorTypeOptions;
    // Field AutoConfigStatus information
    /* Enumeration options for field AutoConfigStatus */
    typedef enum { AUTOCONFIGSTATUS_DISABLED=0, AUTOCONFIGSTATUS_RUNNING=1, AUTOCONFIGSTATUS_DONE=2, AUTOCONFIGSTATUS_ERROR=3 } AutoConfigStatusOptions;

  
    // Constants
    static const quint32 OBJID = 0x7D26A6E6;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    GPSPositionSensor();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static GPSPositionSensor* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE qint32 getLatitude() const;
    Q_INVOKABLE qint32 getLongitude() const;
    Q_INVOKABLE float getAltitude() const;
    Q_INVOKABLE float getGeoidSeparation() const;
    Q_INVOKABLE float getHeading() const;
    Q_INVOKABLE float getGroundspeed() const;
    Q_INVOKABLE float getPDOP() const;
    Q_INVOKABLE float getHDOP() const;
    Q_INVOKABLE float getVDOP() const;
    Q_INVOKABLE quint8 getStatus() const;
    Q_INVOKABLE qint8 getSatellites() const;
    Q_INVOKABLE quint8 getSensorType() const;
    Q_INVOKABLE quint8 getAutoConfigStatus() const;


public slots:
    void setLatitude(qint32 value);
    void setLongitude(qint32 value);
    void setAltitude(float value);
    void setGeoidSeparation(float value);
    void setHeading(float value);
    void setGroundspeed(float value);
    void setPDOP(float value);
    void setHDOP(float value);
    void setVDOP(float value);
    void setStatus(quint8 value);
    void setSatellites(qint8 value);
    void setSensorType(quint8 value);
    void setAutoConfigStatus(quint8 value);


signals:
    void LatitudeChanged(qint32 value);
    void LongitudeChanged(qint32 value);
    void AltitudeChanged(float value);
    void GeoidSeparationChanged(float value);
    void HeadingChanged(float value);
    void GroundspeedChanged(float value);
    void PDOPChanged(float value);
    void HDOPChanged(float value);
    void VDOPChanged(float value);
    void StatusChanged(quint8 value);
    void SatellitesChanged(qint8 value);
    void SensorTypeChanged(quint8 value);
    void AutoConfigStatusChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // GPSPOSITIONSENSOR_H
