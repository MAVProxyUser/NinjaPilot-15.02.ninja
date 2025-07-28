/**
 ******************************************************************************
 *
 * @file       barosensor.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: barosensor.xml. 
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
#ifndef BAROSENSOR_H
#define BAROSENSOR_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT BaroSensor: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float Altitude READ getAltitude WRITE setAltitude NOTIFY AltitudeChanged);
    Q_PROPERTY(float Temperature READ getTemperature WRITE setTemperature NOTIFY TemperatureChanged);
    Q_PROPERTY(float Pressure READ getPressure WRITE setPressure NOTIFY PressureChanged);


public:
    // Field structure
    typedef struct {
        float Altitude;
        float Temperature;
        float Pressure;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Altitude information
    // Field Temperature information
    // Field Pressure information

  
    // Constants
    static const quint32 OBJID = 0x48120EA6;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    BaroSensor();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static BaroSensor* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getAltitude() const;
    Q_INVOKABLE float getTemperature() const;
    Q_INVOKABLE float getPressure() const;


public slots:
    void setAltitude(float value);
    void setTemperature(float value);
    void setPressure(float value);


signals:
    void AltitudeChanged(float value);
    void TemperatureChanged(float value);
    void PressureChanged(float value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // BAROSENSOR_H
