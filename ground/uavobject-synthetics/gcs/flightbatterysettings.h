/**
 ******************************************************************************
 *
 * @file       flightbatterysettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: flightbatterysettings.xml. 
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
#ifndef FLIGHTBATTERYSETTINGS_H
#define FLIGHTBATTERYSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT FlightBatterySettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 Capacity READ getCapacity WRITE setCapacity NOTIFY CapacityChanged);
    Q_PROPERTY(float CellVoltageThresholds_Warning READ getCellVoltageThresholds_Warning WRITE setCellVoltageThresholds_Warning NOTIFY CellVoltageThresholds_WarningChanged);
    Q_PROPERTY(float CellVoltageThresholds_Alarm READ getCellVoltageThresholds_Alarm WRITE setCellVoltageThresholds_Alarm NOTIFY CellVoltageThresholds_AlarmChanged);
    Q_PROPERTY(float SensorCalibrations_VoltageFactor READ getSensorCalibrations_VoltageFactor WRITE setSensorCalibrations_VoltageFactor NOTIFY SensorCalibrations_VoltageFactorChanged);
    Q_PROPERTY(float SensorCalibrations_CurrentFactor READ getSensorCalibrations_CurrentFactor WRITE setSensorCalibrations_CurrentFactor NOTIFY SensorCalibrations_CurrentFactorChanged);
    Q_PROPERTY(float SensorCalibrations_VoltageZero READ getSensorCalibrations_VoltageZero WRITE setSensorCalibrations_VoltageZero NOTIFY SensorCalibrations_VoltageZeroChanged);
    Q_PROPERTY(float SensorCalibrations_CurrentZero READ getSensorCalibrations_CurrentZero WRITE setSensorCalibrations_CurrentZero NOTIFY SensorCalibrations_CurrentZeroChanged);
    Q_PROPERTY(quint8 Type READ getType WRITE setType NOTIFY TypeChanged);
    Q_PROPERTY(quint8 NbCells READ getNbCells WRITE setNbCells NOTIFY NbCellsChanged);


public:
    // Field structure
    typedef struct {
        quint32 Capacity;
        float CellVoltageThresholds[2];
        float SensorCalibrations[4];
        quint8 Type;
        quint8 NbCells;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Capacity information
    // Field CellVoltageThresholds information
    /* Array element names for field CellVoltageThresholds */
    typedef enum { CELLVOLTAGETHRESHOLDS_WARNING=0, CELLVOLTAGETHRESHOLDS_ALARM=1 } CellVoltageThresholdsElem;
    /* Number of elements for field CellVoltageThresholds */
    static const quint32 CELLVOLTAGETHRESHOLDS_NUMELEM = 2;
    // Field SensorCalibrations information
    /* Array element names for field SensorCalibrations */
    typedef enum { SENSORCALIBRATIONS_VOLTAGEFACTOR=0, SENSORCALIBRATIONS_CURRENTFACTOR=1, SENSORCALIBRATIONS_VOLTAGEZERO=2, SENSORCALIBRATIONS_CURRENTZERO=3 } SensorCalibrationsElem;
    /* Number of elements for field SensorCalibrations */
    static const quint32 SENSORCALIBRATIONS_NUMELEM = 4;
    // Field Type information
    /* Enumeration options for field Type */
    typedef enum { TYPE_LIPO=0, TYPE_A123=1, TYPE_LICO=2, TYPE_LIFESO4=3, TYPE_NONE=4 } TypeOptions;
    // Field NbCells information

  
    // Constants
    static const quint32 OBJID = 0xC3D9C8AA;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    FlightBatterySettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static FlightBatterySettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint32 getCapacity() const;
    Q_INVOKABLE float getCellVoltageThresholds(quint32 index) const;
    Q_INVOKABLE float getCellVoltageThresholds_Warning() const;
    Q_INVOKABLE float getCellVoltageThresholds_Alarm() const;
    Q_INVOKABLE float getSensorCalibrations(quint32 index) const;
    Q_INVOKABLE float getSensorCalibrations_VoltageFactor() const;
    Q_INVOKABLE float getSensorCalibrations_CurrentFactor() const;
    Q_INVOKABLE float getSensorCalibrations_VoltageZero() const;
    Q_INVOKABLE float getSensorCalibrations_CurrentZero() const;
    Q_INVOKABLE quint8 getType() const;
    Q_INVOKABLE quint8 getNbCells() const;


public slots:
    void setCapacity(quint32 value);
    void setCellVoltageThresholds(quint32 index, float value);
    void setCellVoltageThresholds_Warning(float value);
    void setCellVoltageThresholds_Alarm(float value);
    void setSensorCalibrations(quint32 index, float value);
    void setSensorCalibrations_VoltageFactor(float value);
    void setSensorCalibrations_CurrentFactor(float value);
    void setSensorCalibrations_VoltageZero(float value);
    void setSensorCalibrations_CurrentZero(float value);
    void setType(quint8 value);
    void setNbCells(quint8 value);


signals:
    void CapacityChanged(quint32 value);
    void CellVoltageThresholdsChanged(quint32 index, float value);
    void CellVoltageThresholds_WarningChanged(float value);
    void CellVoltageThresholds_AlarmChanged(float value);
    void SensorCalibrationsChanged(quint32 index, float value);
    void SensorCalibrations_VoltageFactorChanged(float value);
    void SensorCalibrations_CurrentFactorChanged(float value);
    void SensorCalibrations_VoltageZeroChanged(float value);
    void SensorCalibrations_CurrentZeroChanged(float value);
    void TypeChanged(quint8 value);
    void NbCellsChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // FLIGHTBATTERYSETTINGS_H
