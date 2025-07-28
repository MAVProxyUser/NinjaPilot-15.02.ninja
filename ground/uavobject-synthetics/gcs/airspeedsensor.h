/**
 ******************************************************************************
 *
 * @file       airspeedsensor.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: airspeedsensor.xml. 
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
#ifndef AIRSPEEDSENSOR_H
#define AIRSPEEDSENSOR_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT AirspeedSensor: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float DifferentialPressure READ getDifferentialPressure WRITE setDifferentialPressure NOTIFY DifferentialPressureChanged);
    Q_PROPERTY(float Temperature READ getTemperature WRITE setTemperature NOTIFY TemperatureChanged);
    Q_PROPERTY(float CalibratedAirspeed READ getCalibratedAirspeed WRITE setCalibratedAirspeed NOTIFY CalibratedAirspeedChanged);
    Q_PROPERTY(float TrueAirspeed READ getTrueAirspeed WRITE setTrueAirspeed NOTIFY TrueAirspeedChanged);
    Q_PROPERTY(quint16 SensorValue READ getSensorValue WRITE setSensorValue NOTIFY SensorValueChanged);
    Q_PROPERTY(quint16 SensorValueTemperature READ getSensorValueTemperature WRITE setSensorValueTemperature NOTIFY SensorValueTemperatureChanged);
    Q_PROPERTY(quint8 SensorConnected READ getSensorConnected WRITE setSensorConnected NOTIFY SensorConnectedChanged);


public:
    // Field structure
    typedef struct {
        float DifferentialPressure;
        float Temperature;
        float CalibratedAirspeed;
        float TrueAirspeed;
        quint16 SensorValue;
        quint16 SensorValueTemperature;
        quint8 SensorConnected;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field DifferentialPressure information
    // Field Temperature information
    // Field CalibratedAirspeed information
    // Field TrueAirspeed information
    // Field SensorValue information
    // Field SensorValueTemperature information
    // Field SensorConnected information
    /* Enumeration options for field SensorConnected */
    typedef enum { SENSORCONNECTED_FALSE=0, SENSORCONNECTED_TRUE=1 } SensorConnectedOptions;

  
    // Constants
    static const quint32 OBJID = 0x438D5F9A;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    AirspeedSensor();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static AirspeedSensor* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getDifferentialPressure() const;
    Q_INVOKABLE float getTemperature() const;
    Q_INVOKABLE float getCalibratedAirspeed() const;
    Q_INVOKABLE float getTrueAirspeed() const;
    Q_INVOKABLE quint16 getSensorValue() const;
    Q_INVOKABLE quint16 getSensorValueTemperature() const;
    Q_INVOKABLE quint8 getSensorConnected() const;


public slots:
    void setDifferentialPressure(float value);
    void setTemperature(float value);
    void setCalibratedAirspeed(float value);
    void setTrueAirspeed(float value);
    void setSensorValue(quint16 value);
    void setSensorValueTemperature(quint16 value);
    void setSensorConnected(quint8 value);


signals:
    void DifferentialPressureChanged(float value);
    void TemperatureChanged(float value);
    void CalibratedAirspeedChanged(float value);
    void TrueAirspeedChanged(float value);
    void SensorValueChanged(quint16 value);
    void SensorValueTemperatureChanged(quint16 value);
    void SensorConnectedChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // AIRSPEEDSENSOR_H
