/**
 ******************************************************************************
 *
 * @file       systemalarms.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: systemalarms.xml. 
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
#ifndef SYSTEMALARMS_H
#define SYSTEMALARMS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT SystemAlarms: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 Alarm_SystemConfiguration READ getAlarm_SystemConfiguration WRITE setAlarm_SystemConfiguration NOTIFY Alarm_SystemConfigurationChanged);
    Q_PROPERTY(quint8 Alarm_BootFault READ getAlarm_BootFault WRITE setAlarm_BootFault NOTIFY Alarm_BootFaultChanged);
    Q_PROPERTY(quint8 Alarm_OutOfMemory READ getAlarm_OutOfMemory WRITE setAlarm_OutOfMemory NOTIFY Alarm_OutOfMemoryChanged);
    Q_PROPERTY(quint8 Alarm_StackOverflow READ getAlarm_StackOverflow WRITE setAlarm_StackOverflow NOTIFY Alarm_StackOverflowChanged);
    Q_PROPERTY(quint8 Alarm_CPUOverload READ getAlarm_CPUOverload WRITE setAlarm_CPUOverload NOTIFY Alarm_CPUOverloadChanged);
    Q_PROPERTY(quint8 Alarm_EventSystem READ getAlarm_EventSystem WRITE setAlarm_EventSystem NOTIFY Alarm_EventSystemChanged);
    Q_PROPERTY(quint8 Alarm_Telemetry READ getAlarm_Telemetry WRITE setAlarm_Telemetry NOTIFY Alarm_TelemetryChanged);
    Q_PROPERTY(quint8 Alarm_Receiver READ getAlarm_Receiver WRITE setAlarm_Receiver NOTIFY Alarm_ReceiverChanged);
    Q_PROPERTY(quint8 Alarm_ManualControl READ getAlarm_ManualControl WRITE setAlarm_ManualControl NOTIFY Alarm_ManualControlChanged);
    Q_PROPERTY(quint8 Alarm_Actuator READ getAlarm_Actuator WRITE setAlarm_Actuator NOTIFY Alarm_ActuatorChanged);
    Q_PROPERTY(quint8 Alarm_Attitude READ getAlarm_Attitude WRITE setAlarm_Attitude NOTIFY Alarm_AttitudeChanged);
    Q_PROPERTY(quint8 Alarm_Sensors READ getAlarm_Sensors WRITE setAlarm_Sensors NOTIFY Alarm_SensorsChanged);
    Q_PROPERTY(quint8 Alarm_Magnetometer READ getAlarm_Magnetometer WRITE setAlarm_Magnetometer NOTIFY Alarm_MagnetometerChanged);
    Q_PROPERTY(quint8 Alarm_Airspeed READ getAlarm_Airspeed WRITE setAlarm_Airspeed NOTIFY Alarm_AirspeedChanged);
    Q_PROPERTY(quint8 Alarm_Stabilization READ getAlarm_Stabilization WRITE setAlarm_Stabilization NOTIFY Alarm_StabilizationChanged);
    Q_PROPERTY(quint8 Alarm_Guidance READ getAlarm_Guidance WRITE setAlarm_Guidance NOTIFY Alarm_GuidanceChanged);
    Q_PROPERTY(quint8 Alarm_PathPlan READ getAlarm_PathPlan WRITE setAlarm_PathPlan NOTIFY Alarm_PathPlanChanged);
    Q_PROPERTY(quint8 Alarm_Battery READ getAlarm_Battery WRITE setAlarm_Battery NOTIFY Alarm_BatteryChanged);
    Q_PROPERTY(quint8 Alarm_FlightTime READ getAlarm_FlightTime WRITE setAlarm_FlightTime NOTIFY Alarm_FlightTimeChanged);
    Q_PROPERTY(quint8 Alarm_I2C READ getAlarm_I2C WRITE setAlarm_I2C NOTIFY Alarm_I2CChanged);
    Q_PROPERTY(quint8 Alarm_GPS READ getAlarm_GPS WRITE setAlarm_GPS NOTIFY Alarm_GPSChanged);
    Q_PROPERTY(quint8 ExtendedAlarmStatus_SystemConfiguration READ getExtendedAlarmStatus_SystemConfiguration WRITE setExtendedAlarmStatus_SystemConfiguration NOTIFY ExtendedAlarmStatus_SystemConfigurationChanged);
    Q_PROPERTY(quint8 ExtendedAlarmStatus_BootFault READ getExtendedAlarmStatus_BootFault WRITE setExtendedAlarmStatus_BootFault NOTIFY ExtendedAlarmStatus_BootFaultChanged);
    Q_PROPERTY(quint8 ExtendedAlarmSubStatus_SystemConfiguration READ getExtendedAlarmSubStatus_SystemConfiguration WRITE setExtendedAlarmSubStatus_SystemConfiguration NOTIFY ExtendedAlarmSubStatus_SystemConfigurationChanged);
    Q_PROPERTY(quint8 ExtendedAlarmSubStatus_BootFault READ getExtendedAlarmSubStatus_BootFault WRITE setExtendedAlarmSubStatus_BootFault NOTIFY ExtendedAlarmSubStatus_BootFaultChanged);


public:
    // Field structure
    typedef struct {
        quint8 Alarm[21];
        quint8 ExtendedAlarmStatus[2];
        quint8 ExtendedAlarmSubStatus[2];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field Alarm information
    /* Enumeration options for field Alarm */
    typedef enum { ALARM_UNINITIALISED=0, ALARM_OK=1, ALARM_WARNING=2, ALARM_CRITICAL=3, ALARM_ERROR=4 } AlarmOptions;
    /* Array element names for field Alarm */
    typedef enum { ALARM_SYSTEMCONFIGURATION=0, ALARM_BOOTFAULT=1, ALARM_OUTOFMEMORY=2, ALARM_STACKOVERFLOW=3, ALARM_CPUOVERLOAD=4, ALARM_EVENTSYSTEM=5, ALARM_TELEMETRY=6, ALARM_RECEIVER=7, ALARM_MANUALCONTROL=8, ALARM_ACTUATOR=9, ALARM_ATTITUDE=10, ALARM_SENSORS=11, ALARM_MAGNETOMETER=12, ALARM_AIRSPEED=13, ALARM_STABILIZATION=14, ALARM_GUIDANCE=15, ALARM_PATHPLAN=16, ALARM_BATTERY=17, ALARM_FLIGHTTIME=18, ALARM_I2C=19, ALARM_GPS=20 } AlarmElem;
    /* Number of elements for field Alarm */
    static const quint32 ALARM_NUMELEM = 21;
    // Field ExtendedAlarmStatus information
    /* Enumeration options for field ExtendedAlarmStatus */
    typedef enum { EXTENDEDALARMSTATUS_NONE=0, EXTENDEDALARMSTATUS_REBOOTREQUIRED=1, EXTENDEDALARMSTATUS_FLIGHTMODE=2, EXTENDEDALARMSTATUS_UNSUPPORTEDCONFIG_ONESHOT=3, EXTENDEDALARMSTATUS_BADTHROTTLEORCOLLECTIVEINPUTRANGE=4 } ExtendedAlarmStatusOptions;
    /* Array element names for field ExtendedAlarmStatus */
    typedef enum { EXTENDEDALARMSTATUS_SYSTEMCONFIGURATION=0, EXTENDEDALARMSTATUS_BOOTFAULT=1 } ExtendedAlarmStatusElem;
    /* Number of elements for field ExtendedAlarmStatus */
    static const quint32 EXTENDEDALARMSTATUS_NUMELEM = 2;
    // Field ExtendedAlarmSubStatus information
    /* Array element names for field ExtendedAlarmSubStatus */
    typedef enum { EXTENDEDALARMSUBSTATUS_SYSTEMCONFIGURATION=0, EXTENDEDALARMSUBSTATUS_BOOTFAULT=1 } ExtendedAlarmSubStatusElem;
    /* Number of elements for field ExtendedAlarmSubStatus */
    static const quint32 EXTENDEDALARMSUBSTATUS_NUMELEM = 2;

  
    // Constants
    static const quint32 OBJID = 0x6B7639EC;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    SystemAlarms();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static SystemAlarms* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint8 getAlarm(quint32 index) const;
    Q_INVOKABLE quint8 getAlarm_SystemConfiguration() const;
    Q_INVOKABLE quint8 getAlarm_BootFault() const;
    Q_INVOKABLE quint8 getAlarm_OutOfMemory() const;
    Q_INVOKABLE quint8 getAlarm_StackOverflow() const;
    Q_INVOKABLE quint8 getAlarm_CPUOverload() const;
    Q_INVOKABLE quint8 getAlarm_EventSystem() const;
    Q_INVOKABLE quint8 getAlarm_Telemetry() const;
    Q_INVOKABLE quint8 getAlarm_Receiver() const;
    Q_INVOKABLE quint8 getAlarm_ManualControl() const;
    Q_INVOKABLE quint8 getAlarm_Actuator() const;
    Q_INVOKABLE quint8 getAlarm_Attitude() const;
    Q_INVOKABLE quint8 getAlarm_Sensors() const;
    Q_INVOKABLE quint8 getAlarm_Magnetometer() const;
    Q_INVOKABLE quint8 getAlarm_Airspeed() const;
    Q_INVOKABLE quint8 getAlarm_Stabilization() const;
    Q_INVOKABLE quint8 getAlarm_Guidance() const;
    Q_INVOKABLE quint8 getAlarm_PathPlan() const;
    Q_INVOKABLE quint8 getAlarm_Battery() const;
    Q_INVOKABLE quint8 getAlarm_FlightTime() const;
    Q_INVOKABLE quint8 getAlarm_I2C() const;
    Q_INVOKABLE quint8 getAlarm_GPS() const;
    Q_INVOKABLE quint8 getExtendedAlarmStatus(quint32 index) const;
    Q_INVOKABLE quint8 getExtendedAlarmStatus_SystemConfiguration() const;
    Q_INVOKABLE quint8 getExtendedAlarmStatus_BootFault() const;
    Q_INVOKABLE quint8 getExtendedAlarmSubStatus(quint32 index) const;
    Q_INVOKABLE quint8 getExtendedAlarmSubStatus_SystemConfiguration() const;
    Q_INVOKABLE quint8 getExtendedAlarmSubStatus_BootFault() const;


public slots:
    void setAlarm(quint32 index, quint8 value);
    void setAlarm_SystemConfiguration(quint8 value);
    void setAlarm_BootFault(quint8 value);
    void setAlarm_OutOfMemory(quint8 value);
    void setAlarm_StackOverflow(quint8 value);
    void setAlarm_CPUOverload(quint8 value);
    void setAlarm_EventSystem(quint8 value);
    void setAlarm_Telemetry(quint8 value);
    void setAlarm_Receiver(quint8 value);
    void setAlarm_ManualControl(quint8 value);
    void setAlarm_Actuator(quint8 value);
    void setAlarm_Attitude(quint8 value);
    void setAlarm_Sensors(quint8 value);
    void setAlarm_Magnetometer(quint8 value);
    void setAlarm_Airspeed(quint8 value);
    void setAlarm_Stabilization(quint8 value);
    void setAlarm_Guidance(quint8 value);
    void setAlarm_PathPlan(quint8 value);
    void setAlarm_Battery(quint8 value);
    void setAlarm_FlightTime(quint8 value);
    void setAlarm_I2C(quint8 value);
    void setAlarm_GPS(quint8 value);
    void setExtendedAlarmStatus(quint32 index, quint8 value);
    void setExtendedAlarmStatus_SystemConfiguration(quint8 value);
    void setExtendedAlarmStatus_BootFault(quint8 value);
    void setExtendedAlarmSubStatus(quint32 index, quint8 value);
    void setExtendedAlarmSubStatus_SystemConfiguration(quint8 value);
    void setExtendedAlarmSubStatus_BootFault(quint8 value);


signals:
    void AlarmChanged(quint32 index, quint8 value);
    void Alarm_SystemConfigurationChanged(quint8 value);
    void Alarm_BootFaultChanged(quint8 value);
    void Alarm_OutOfMemoryChanged(quint8 value);
    void Alarm_StackOverflowChanged(quint8 value);
    void Alarm_CPUOverloadChanged(quint8 value);
    void Alarm_EventSystemChanged(quint8 value);
    void Alarm_TelemetryChanged(quint8 value);
    void Alarm_ReceiverChanged(quint8 value);
    void Alarm_ManualControlChanged(quint8 value);
    void Alarm_ActuatorChanged(quint8 value);
    void Alarm_AttitudeChanged(quint8 value);
    void Alarm_SensorsChanged(quint8 value);
    void Alarm_MagnetometerChanged(quint8 value);
    void Alarm_AirspeedChanged(quint8 value);
    void Alarm_StabilizationChanged(quint8 value);
    void Alarm_GuidanceChanged(quint8 value);
    void Alarm_PathPlanChanged(quint8 value);
    void Alarm_BatteryChanged(quint8 value);
    void Alarm_FlightTimeChanged(quint8 value);
    void Alarm_I2CChanged(quint8 value);
    void Alarm_GPSChanged(quint8 value);
    void ExtendedAlarmStatusChanged(quint32 index, quint8 value);
    void ExtendedAlarmStatus_SystemConfigurationChanged(quint8 value);
    void ExtendedAlarmStatus_BootFaultChanged(quint8 value);
    void ExtendedAlarmSubStatusChanged(quint32 index, quint8 value);
    void ExtendedAlarmSubStatus_SystemConfigurationChanged(quint8 value);
    void ExtendedAlarmSubStatus_BootFaultChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // SYSTEMALARMS_H
