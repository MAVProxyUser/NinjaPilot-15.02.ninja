/**
 ******************************************************************************
 *
 * @file       systemsettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: systemsettings.xml. 
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
#ifndef SYSTEMSETTINGS_H
#define SYSTEMSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT SystemSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 GUIConfigData_0 READ getGUIConfigData_0 WRITE setGUIConfigData_0 NOTIFY GUIConfigData_0Changed);
    Q_PROPERTY(quint32 GUIConfigData_1 READ getGUIConfigData_1 WRITE setGUIConfigData_1 NOTIFY GUIConfigData_1Changed);
    Q_PROPERTY(quint32 GUIConfigData_2 READ getGUIConfigData_2 WRITE setGUIConfigData_2 NOTIFY GUIConfigData_2Changed);
    Q_PROPERTY(quint32 GUIConfigData_3 READ getGUIConfigData_3 WRITE setGUIConfigData_3 NOTIFY GUIConfigData_3Changed);
    Q_PROPERTY(float AirSpeedMax READ getAirSpeedMax WRITE setAirSpeedMax NOTIFY AirSpeedMaxChanged);
    Q_PROPERTY(float AirSpeedMin READ getAirSpeedMin WRITE setAirSpeedMin NOTIFY AirSpeedMinChanged);
    Q_PROPERTY(quint8 AirframeType READ getAirframeType WRITE setAirframeType NOTIFY AirframeTypeChanged);
    Q_PROPERTY(quint8 VehicleName_0 READ getVehicleName_0 WRITE setVehicleName_0 NOTIFY VehicleName_0Changed);
    Q_PROPERTY(quint8 VehicleName_1 READ getVehicleName_1 WRITE setVehicleName_1 NOTIFY VehicleName_1Changed);
    Q_PROPERTY(quint8 VehicleName_2 READ getVehicleName_2 WRITE setVehicleName_2 NOTIFY VehicleName_2Changed);
    Q_PROPERTY(quint8 VehicleName_3 READ getVehicleName_3 WRITE setVehicleName_3 NOTIFY VehicleName_3Changed);
    Q_PROPERTY(quint8 VehicleName_4 READ getVehicleName_4 WRITE setVehicleName_4 NOTIFY VehicleName_4Changed);
    Q_PROPERTY(quint8 VehicleName_5 READ getVehicleName_5 WRITE setVehicleName_5 NOTIFY VehicleName_5Changed);
    Q_PROPERTY(quint8 VehicleName_6 READ getVehicleName_6 WRITE setVehicleName_6 NOTIFY VehicleName_6Changed);
    Q_PROPERTY(quint8 VehicleName_7 READ getVehicleName_7 WRITE setVehicleName_7 NOTIFY VehicleName_7Changed);
    Q_PROPERTY(quint8 VehicleName_8 READ getVehicleName_8 WRITE setVehicleName_8 NOTIFY VehicleName_8Changed);
    Q_PROPERTY(quint8 VehicleName_9 READ getVehicleName_9 WRITE setVehicleName_9 NOTIFY VehicleName_9Changed);
    Q_PROPERTY(quint8 VehicleName_10 READ getVehicleName_10 WRITE setVehicleName_10 NOTIFY VehicleName_10Changed);
    Q_PROPERTY(quint8 VehicleName_11 READ getVehicleName_11 WRITE setVehicleName_11 NOTIFY VehicleName_11Changed);
    Q_PROPERTY(quint8 VehicleName_12 READ getVehicleName_12 WRITE setVehicleName_12 NOTIFY VehicleName_12Changed);
    Q_PROPERTY(quint8 VehicleName_13 READ getVehicleName_13 WRITE setVehicleName_13 NOTIFY VehicleName_13Changed);
    Q_PROPERTY(quint8 VehicleName_14 READ getVehicleName_14 WRITE setVehicleName_14 NOTIFY VehicleName_14Changed);
    Q_PROPERTY(quint8 VehicleName_15 READ getVehicleName_15 WRITE setVehicleName_15 NOTIFY VehicleName_15Changed);
    Q_PROPERTY(quint8 VehicleName_16 READ getVehicleName_16 WRITE setVehicleName_16 NOTIFY VehicleName_16Changed);
    Q_PROPERTY(quint8 VehicleName_17 READ getVehicleName_17 WRITE setVehicleName_17 NOTIFY VehicleName_17Changed);
    Q_PROPERTY(quint8 VehicleName_18 READ getVehicleName_18 WRITE setVehicleName_18 NOTIFY VehicleName_18Changed);
    Q_PROPERTY(quint8 VehicleName_19 READ getVehicleName_19 WRITE setVehicleName_19 NOTIFY VehicleName_19Changed);
    Q_PROPERTY(quint8 ThrustControl READ getThrustControl WRITE setThrustControl NOTIFY ThrustControlChanged);


public:
    // Field structure
    typedef struct {
        quint32 GUIConfigData[4];
        float AirSpeedMax;
        float AirSpeedMin;
        quint8 AirframeType;
        quint8 VehicleName[20];
        quint8 ThrustControl;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field GUIConfigData information
    /* Number of elements for field GUIConfigData */
    static const quint32 GUICONFIGDATA_NUMELEM = 4;
    // Field AirSpeedMax information
    // Field AirSpeedMin information
    // Field AirframeType information
    /* Enumeration options for field AirframeType */
    typedef enum { AIRFRAMETYPE_FIXEDWING=0, AIRFRAMETYPE_FIXEDWINGELEVON=1, AIRFRAMETYPE_FIXEDWINGVTAIL=2, AIRFRAMETYPE_VTOL=3, AIRFRAMETYPE_HELICP=4, AIRFRAMETYPE_QUADX=5, AIRFRAMETYPE_QUADP=6, AIRFRAMETYPE_HEXA=7, AIRFRAMETYPE_OCTO=8, AIRFRAMETYPE_CUSTOM=9, AIRFRAMETYPE_HEXAX=10, AIRFRAMETYPE_HEXAH=11, AIRFRAMETYPE_OCTOV=12, AIRFRAMETYPE_OCTOCOAXP=13, AIRFRAMETYPE_OCTOCOAXX=14, AIRFRAMETYPE_OCTOX=15, AIRFRAMETYPE_HEXACOAX=16, AIRFRAMETYPE_TRI=17, AIRFRAMETYPE_GROUNDVEHICLECAR=18, AIRFRAMETYPE_GROUNDVEHICLEDIFFERENTIAL=19, AIRFRAMETYPE_GROUNDVEHICLEMOTORCYCLE=20 } AirframeTypeOptions;
    // Field VehicleName information
    /* Number of elements for field VehicleName */
    static const quint32 VEHICLENAME_NUMELEM = 20;
    // Field ThrustControl information
    /* Enumeration options for field ThrustControl */
    typedef enum { THRUSTCONTROL_THROTTLE=0, THRUSTCONTROL_COLLECTIVE=1, THRUSTCONTROL_NONE=2 } ThrustControlOptions;

  
    // Constants
    static const quint32 OBJID = 0xD9D093B8;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    SystemSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static SystemSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint32 getGUIConfigData(quint32 index) const;
    Q_INVOKABLE quint32 getGUIConfigData_0() const;
    Q_INVOKABLE quint32 getGUIConfigData_1() const;
    Q_INVOKABLE quint32 getGUIConfigData_2() const;
    Q_INVOKABLE quint32 getGUIConfigData_3() const;
    Q_INVOKABLE float getAirSpeedMax() const;
    Q_INVOKABLE float getAirSpeedMin() const;
    Q_INVOKABLE quint8 getAirframeType() const;
    Q_INVOKABLE quint8 getVehicleName(quint32 index) const;
    Q_INVOKABLE quint8 getVehicleName_0() const;
    Q_INVOKABLE quint8 getVehicleName_1() const;
    Q_INVOKABLE quint8 getVehicleName_2() const;
    Q_INVOKABLE quint8 getVehicleName_3() const;
    Q_INVOKABLE quint8 getVehicleName_4() const;
    Q_INVOKABLE quint8 getVehicleName_5() const;
    Q_INVOKABLE quint8 getVehicleName_6() const;
    Q_INVOKABLE quint8 getVehicleName_7() const;
    Q_INVOKABLE quint8 getVehicleName_8() const;
    Q_INVOKABLE quint8 getVehicleName_9() const;
    Q_INVOKABLE quint8 getVehicleName_10() const;
    Q_INVOKABLE quint8 getVehicleName_11() const;
    Q_INVOKABLE quint8 getVehicleName_12() const;
    Q_INVOKABLE quint8 getVehicleName_13() const;
    Q_INVOKABLE quint8 getVehicleName_14() const;
    Q_INVOKABLE quint8 getVehicleName_15() const;
    Q_INVOKABLE quint8 getVehicleName_16() const;
    Q_INVOKABLE quint8 getVehicleName_17() const;
    Q_INVOKABLE quint8 getVehicleName_18() const;
    Q_INVOKABLE quint8 getVehicleName_19() const;
    Q_INVOKABLE quint8 getThrustControl() const;


public slots:
    void setGUIConfigData(quint32 index, quint32 value);
    void setGUIConfigData_0(quint32 value);
    void setGUIConfigData_1(quint32 value);
    void setGUIConfigData_2(quint32 value);
    void setGUIConfigData_3(quint32 value);
    void setAirSpeedMax(float value);
    void setAirSpeedMin(float value);
    void setAirframeType(quint8 value);
    void setVehicleName(quint32 index, quint8 value);
    void setVehicleName_0(quint8 value);
    void setVehicleName_1(quint8 value);
    void setVehicleName_2(quint8 value);
    void setVehicleName_3(quint8 value);
    void setVehicleName_4(quint8 value);
    void setVehicleName_5(quint8 value);
    void setVehicleName_6(quint8 value);
    void setVehicleName_7(quint8 value);
    void setVehicleName_8(quint8 value);
    void setVehicleName_9(quint8 value);
    void setVehicleName_10(quint8 value);
    void setVehicleName_11(quint8 value);
    void setVehicleName_12(quint8 value);
    void setVehicleName_13(quint8 value);
    void setVehicleName_14(quint8 value);
    void setVehicleName_15(quint8 value);
    void setVehicleName_16(quint8 value);
    void setVehicleName_17(quint8 value);
    void setVehicleName_18(quint8 value);
    void setVehicleName_19(quint8 value);
    void setThrustControl(quint8 value);


signals:
    void GUIConfigDataChanged(quint32 index, quint32 value);
    void GUIConfigData_0Changed(quint32 value);
    void GUIConfigData_1Changed(quint32 value);
    void GUIConfigData_2Changed(quint32 value);
    void GUIConfigData_3Changed(quint32 value);
    void AirSpeedMaxChanged(float value);
    void AirSpeedMinChanged(float value);
    void AirframeTypeChanged(quint8 value);
    void VehicleNameChanged(quint32 index, quint8 value);
    void VehicleName_0Changed(quint8 value);
    void VehicleName_1Changed(quint8 value);
    void VehicleName_2Changed(quint8 value);
    void VehicleName_3Changed(quint8 value);
    void VehicleName_4Changed(quint8 value);
    void VehicleName_5Changed(quint8 value);
    void VehicleName_6Changed(quint8 value);
    void VehicleName_7Changed(quint8 value);
    void VehicleName_8Changed(quint8 value);
    void VehicleName_9Changed(quint8 value);
    void VehicleName_10Changed(quint8 value);
    void VehicleName_11Changed(quint8 value);
    void VehicleName_12Changed(quint8 value);
    void VehicleName_13Changed(quint8 value);
    void VehicleName_14Changed(quint8 value);
    void VehicleName_15Changed(quint8 value);
    void VehicleName_16Changed(quint8 value);
    void VehicleName_17Changed(quint8 value);
    void VehicleName_18Changed(quint8 value);
    void VehicleName_19Changed(quint8 value);
    void ThrustControlChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // SYSTEMSETTINGS_H
