/**
 ******************************************************************************
 *
 * @file       flightbatterystate.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: flightbatterystate.xml. 
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
#ifndef FLIGHTBATTERYSTATE_H
#define FLIGHTBATTERYSTATE_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT FlightBatteryState: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float Voltage READ getVoltage WRITE setVoltage NOTIFY VoltageChanged);
    Q_PROPERTY(float Current READ getCurrent WRITE setCurrent NOTIFY CurrentChanged);
    Q_PROPERTY(float BoardSupplyVoltage READ getBoardSupplyVoltage WRITE setBoardSupplyVoltage NOTIFY BoardSupplyVoltageChanged);
    Q_PROPERTY(float PeakCurrent READ getPeakCurrent WRITE setPeakCurrent NOTIFY PeakCurrentChanged);
    Q_PROPERTY(float AvgCurrent READ getAvgCurrent WRITE setAvgCurrent NOTIFY AvgCurrentChanged);
    Q_PROPERTY(float ConsumedEnergy READ getConsumedEnergy WRITE setConsumedEnergy NOTIFY ConsumedEnergyChanged);
    Q_PROPERTY(float EstimatedFlightTime READ getEstimatedFlightTime WRITE setEstimatedFlightTime NOTIFY EstimatedFlightTimeChanged);
    Q_PROPERTY(quint8 NbCells READ getNbCells WRITE setNbCells NOTIFY NbCellsChanged);
    Q_PROPERTY(quint8 NbCellsAutodetected READ getNbCellsAutodetected WRITE setNbCellsAutodetected NOTIFY NbCellsAutodetectedChanged);


public:
    // Field structure
    typedef struct {
        float Voltage;
        float Current;
        float BoardSupplyVoltage;
        float PeakCurrent;
        float AvgCurrent;
        float ConsumedEnergy;
        float EstimatedFlightTime;
        quint8 NbCells;
        quint8 NbCellsAutodetected;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Voltage information
    // Field Current information
    // Field BoardSupplyVoltage information
    // Field PeakCurrent information
    // Field AvgCurrent information
    // Field ConsumedEnergy information
    // Field EstimatedFlightTime information
    // Field NbCells information
    // Field NbCellsAutodetected information
    /* Enumeration options for field NbCellsAutodetected */
    typedef enum { NBCELLSAUTODETECTED_FALSE=0, NBCELLSAUTODETECTED_TRUE=1 } NbCellsAutodetectedOptions;

  
    // Constants
    static const quint32 OBJID = 0x26962352;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    FlightBatteryState();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static FlightBatteryState* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getVoltage() const;
    Q_INVOKABLE float getCurrent() const;
    Q_INVOKABLE float getBoardSupplyVoltage() const;
    Q_INVOKABLE float getPeakCurrent() const;
    Q_INVOKABLE float getAvgCurrent() const;
    Q_INVOKABLE float getConsumedEnergy() const;
    Q_INVOKABLE float getEstimatedFlightTime() const;
    Q_INVOKABLE quint8 getNbCells() const;
    Q_INVOKABLE quint8 getNbCellsAutodetected() const;


public slots:
    void setVoltage(float value);
    void setCurrent(float value);
    void setBoardSupplyVoltage(float value);
    void setPeakCurrent(float value);
    void setAvgCurrent(float value);
    void setConsumedEnergy(float value);
    void setEstimatedFlightTime(float value);
    void setNbCells(quint8 value);
    void setNbCellsAutodetected(quint8 value);


signals:
    void VoltageChanged(float value);
    void CurrentChanged(float value);
    void BoardSupplyVoltageChanged(float value);
    void PeakCurrentChanged(float value);
    void AvgCurrentChanged(float value);
    void ConsumedEnergyChanged(float value);
    void EstimatedFlightTimeChanged(float value);
    void NbCellsChanged(quint8 value);
    void NbCellsAutodetectedChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // FLIGHTBATTERYSTATE_H
