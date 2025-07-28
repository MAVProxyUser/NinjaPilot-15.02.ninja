/**
 ******************************************************************************
 *
 * @file       airspeedsettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: airspeedsettings.xml. 
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
#ifndef AIRSPEEDSETTINGS_H
#define AIRSPEEDSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT AirspeedSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float Scale READ getScale WRITE setScale NOTIFY ScaleChanged);
    Q_PROPERTY(float IMUBasedEstimationLowPassPeriod1 READ getIMUBasedEstimationLowPassPeriod1 WRITE setIMUBasedEstimationLowPassPeriod1 NOTIFY IMUBasedEstimationLowPassPeriod1Changed);
    Q_PROPERTY(float IMUBasedEstimationLowPassPeriod2 READ getIMUBasedEstimationLowPassPeriod2 WRITE setIMUBasedEstimationLowPassPeriod2 NOTIFY IMUBasedEstimationLowPassPeriod2Changed);
    Q_PROPERTY(quint16 ZeroPoint READ getZeroPoint WRITE setZeroPoint NOTIFY ZeroPointChanged);
    Q_PROPERTY(quint8 SamplePeriod READ getSamplePeriod WRITE setSamplePeriod NOTIFY SamplePeriodChanged);
    Q_PROPERTY(quint8 AirspeedSensorType READ getAirspeedSensorType WRITE setAirspeedSensorType NOTIFY AirspeedSensorTypeChanged);


public:
    // Field structure
    typedef struct {
        float Scale;
        float IMUBasedEstimationLowPassPeriod1;
        float IMUBasedEstimationLowPassPeriod2;
        quint16 ZeroPoint;
        quint8 SamplePeriod;
        quint8 AirspeedSensorType;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Scale information
    // Field IMUBasedEstimationLowPassPeriod1 information
    // Field IMUBasedEstimationLowPassPeriod2 information
    // Field ZeroPoint information
    // Field SamplePeriod information
    // Field AirspeedSensorType information
    /* Enumeration options for field AirspeedSensorType */
    typedef enum { AIRSPEEDSENSORTYPE_PIXHAWKAIRSPEEDMS4525DO=0, AIRSPEEDSENSORTYPE_EAGLETREEAIRSPEEDV3=1, AIRSPEEDSENSORTYPE_DIYDRONESMPXV5004=2, AIRSPEEDSENSORTYPE_DIYDRONESMPXV7002=3, AIRSPEEDSENSORTYPE_GROUNDSPEEDBASEDWINDESTIMATION=4, AIRSPEEDSENSORTYPE_NONE=5 } AirspeedSensorTypeOptions;

  
    // Constants
    static const quint32 OBJID = 0x69F4AD7A;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    AirspeedSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static AirspeedSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getScale() const;
    Q_INVOKABLE float getIMUBasedEstimationLowPassPeriod1() const;
    Q_INVOKABLE float getIMUBasedEstimationLowPassPeriod2() const;
    Q_INVOKABLE quint16 getZeroPoint() const;
    Q_INVOKABLE quint8 getSamplePeriod() const;
    Q_INVOKABLE quint8 getAirspeedSensorType() const;


public slots:
    void setScale(float value);
    void setIMUBasedEstimationLowPassPeriod1(float value);
    void setIMUBasedEstimationLowPassPeriod2(float value);
    void setZeroPoint(quint16 value);
    void setSamplePeriod(quint8 value);
    void setAirspeedSensorType(quint8 value);


signals:
    void ScaleChanged(float value);
    void IMUBasedEstimationLowPassPeriod1Changed(float value);
    void IMUBasedEstimationLowPassPeriod2Changed(float value);
    void ZeroPointChanged(quint16 value);
    void SamplePeriodChanged(quint8 value);
    void AirspeedSensorTypeChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // AIRSPEEDSETTINGS_H
