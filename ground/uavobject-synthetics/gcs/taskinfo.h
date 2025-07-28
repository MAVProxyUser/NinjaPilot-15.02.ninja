/**
 ******************************************************************************
 *
 * @file       taskinfo.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: taskinfo.xml. 
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
#ifndef TASKINFO_H
#define TASKINFO_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT TaskInfo: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 StackRemaining_System READ getStackRemaining_System WRITE setStackRemaining_System NOTIFY StackRemaining_SystemChanged);
    Q_PROPERTY(quint16 StackRemaining_CallbackScheduler0 READ getStackRemaining_CallbackScheduler0 WRITE setStackRemaining_CallbackScheduler0 NOTIFY StackRemaining_CallbackScheduler0Changed);
    Q_PROPERTY(quint16 StackRemaining_CallbackScheduler1 READ getStackRemaining_CallbackScheduler1 WRITE setStackRemaining_CallbackScheduler1 NOTIFY StackRemaining_CallbackScheduler1Changed);
    Q_PROPERTY(quint16 StackRemaining_CallbackScheduler2 READ getStackRemaining_CallbackScheduler2 WRITE setStackRemaining_CallbackScheduler2 NOTIFY StackRemaining_CallbackScheduler2Changed);
    Q_PROPERTY(quint16 StackRemaining_CallbackScheduler3 READ getStackRemaining_CallbackScheduler3 WRITE setStackRemaining_CallbackScheduler3 NOTIFY StackRemaining_CallbackScheduler3Changed);
    Q_PROPERTY(quint16 StackRemaining_Receiver READ getStackRemaining_Receiver WRITE setStackRemaining_Receiver NOTIFY StackRemaining_ReceiverChanged);
    Q_PROPERTY(quint16 StackRemaining_Stabilization READ getStackRemaining_Stabilization WRITE setStackRemaining_Stabilization NOTIFY StackRemaining_StabilizationChanged);
    Q_PROPERTY(quint16 StackRemaining_Actuator READ getStackRemaining_Actuator WRITE setStackRemaining_Actuator NOTIFY StackRemaining_ActuatorChanged);
    Q_PROPERTY(quint16 StackRemaining_Sensors READ getStackRemaining_Sensors WRITE setStackRemaining_Sensors NOTIFY StackRemaining_SensorsChanged);
    Q_PROPERTY(quint16 StackRemaining_Attitude READ getStackRemaining_Attitude WRITE setStackRemaining_Attitude NOTIFY StackRemaining_AttitudeChanged);
    Q_PROPERTY(quint16 StackRemaining_Altitude READ getStackRemaining_Altitude WRITE setStackRemaining_Altitude NOTIFY StackRemaining_AltitudeChanged);
    Q_PROPERTY(quint16 StackRemaining_Airspeed READ getStackRemaining_Airspeed WRITE setStackRemaining_Airspeed NOTIFY StackRemaining_AirspeedChanged);
    Q_PROPERTY(quint16 StackRemaining_MagBaro READ getStackRemaining_MagBaro WRITE setStackRemaining_MagBaro NOTIFY StackRemaining_MagBaroChanged);
    Q_PROPERTY(quint16 StackRemaining_FlightPlan READ getStackRemaining_FlightPlan WRITE setStackRemaining_FlightPlan NOTIFY StackRemaining_FlightPlanChanged);
    Q_PROPERTY(quint16 StackRemaining_TelemetryTx READ getStackRemaining_TelemetryTx WRITE setStackRemaining_TelemetryTx NOTIFY StackRemaining_TelemetryTxChanged);
    Q_PROPERTY(quint16 StackRemaining_TelemetryRx READ getStackRemaining_TelemetryRx WRITE setStackRemaining_TelemetryRx NOTIFY StackRemaining_TelemetryRxChanged);
    Q_PROPERTY(quint16 StackRemaining_RadioRx READ getStackRemaining_RadioRx WRITE setStackRemaining_RadioRx NOTIFY StackRemaining_RadioRxChanged);
    Q_PROPERTY(quint16 StackRemaining_Com2UsbBridge READ getStackRemaining_Com2UsbBridge WRITE setStackRemaining_Com2UsbBridge NOTIFY StackRemaining_Com2UsbBridgeChanged);
    Q_PROPERTY(quint16 StackRemaining_Usb2ComBridge READ getStackRemaining_Usb2ComBridge WRITE setStackRemaining_Usb2ComBridge NOTIFY StackRemaining_Usb2ComBridgeChanged);
    Q_PROPERTY(quint16 StackRemaining_GPS READ getStackRemaining_GPS WRITE setStackRemaining_GPS NOTIFY StackRemaining_GPSChanged);
    Q_PROPERTY(quint16 StackRemaining_OSDGen READ getStackRemaining_OSDGen WRITE setStackRemaining_OSDGen NOTIFY StackRemaining_OSDGenChanged);
    Q_PROPERTY(quint8 Running_System READ getRunning_System WRITE setRunning_System NOTIFY Running_SystemChanged);
    Q_PROPERTY(quint8 Running_CallbackScheduler0 READ getRunning_CallbackScheduler0 WRITE setRunning_CallbackScheduler0 NOTIFY Running_CallbackScheduler0Changed);
    Q_PROPERTY(quint8 Running_CallbackScheduler1 READ getRunning_CallbackScheduler1 WRITE setRunning_CallbackScheduler1 NOTIFY Running_CallbackScheduler1Changed);
    Q_PROPERTY(quint8 Running_CallbackScheduler2 READ getRunning_CallbackScheduler2 WRITE setRunning_CallbackScheduler2 NOTIFY Running_CallbackScheduler2Changed);
    Q_PROPERTY(quint8 Running_CallbackScheduler3 READ getRunning_CallbackScheduler3 WRITE setRunning_CallbackScheduler3 NOTIFY Running_CallbackScheduler3Changed);
    Q_PROPERTY(quint8 Running_Receiver READ getRunning_Receiver WRITE setRunning_Receiver NOTIFY Running_ReceiverChanged);
    Q_PROPERTY(quint8 Running_Stabilization READ getRunning_Stabilization WRITE setRunning_Stabilization NOTIFY Running_StabilizationChanged);
    Q_PROPERTY(quint8 Running_Actuator READ getRunning_Actuator WRITE setRunning_Actuator NOTIFY Running_ActuatorChanged);
    Q_PROPERTY(quint8 Running_Sensors READ getRunning_Sensors WRITE setRunning_Sensors NOTIFY Running_SensorsChanged);
    Q_PROPERTY(quint8 Running_Attitude READ getRunning_Attitude WRITE setRunning_Attitude NOTIFY Running_AttitudeChanged);
    Q_PROPERTY(quint8 Running_Altitude READ getRunning_Altitude WRITE setRunning_Altitude NOTIFY Running_AltitudeChanged);
    Q_PROPERTY(quint8 Running_Airspeed READ getRunning_Airspeed WRITE setRunning_Airspeed NOTIFY Running_AirspeedChanged);
    Q_PROPERTY(quint8 Running_MagBaro READ getRunning_MagBaro WRITE setRunning_MagBaro NOTIFY Running_MagBaroChanged);
    Q_PROPERTY(quint8 Running_FlightPlan READ getRunning_FlightPlan WRITE setRunning_FlightPlan NOTIFY Running_FlightPlanChanged);
    Q_PROPERTY(quint8 Running_TelemetryTx READ getRunning_TelemetryTx WRITE setRunning_TelemetryTx NOTIFY Running_TelemetryTxChanged);
    Q_PROPERTY(quint8 Running_TelemetryRx READ getRunning_TelemetryRx WRITE setRunning_TelemetryRx NOTIFY Running_TelemetryRxChanged);
    Q_PROPERTY(quint8 Running_RadioRx READ getRunning_RadioRx WRITE setRunning_RadioRx NOTIFY Running_RadioRxChanged);
    Q_PROPERTY(quint8 Running_Com2UsbBridge READ getRunning_Com2UsbBridge WRITE setRunning_Com2UsbBridge NOTIFY Running_Com2UsbBridgeChanged);
    Q_PROPERTY(quint8 Running_Usb2ComBridge READ getRunning_Usb2ComBridge WRITE setRunning_Usb2ComBridge NOTIFY Running_Usb2ComBridgeChanged);
    Q_PROPERTY(quint8 Running_GPS READ getRunning_GPS WRITE setRunning_GPS NOTIFY Running_GPSChanged);
    Q_PROPERTY(quint8 Running_OSDGen READ getRunning_OSDGen WRITE setRunning_OSDGen NOTIFY Running_OSDGenChanged);
    Q_PROPERTY(quint8 RunningTime_System READ getRunningTime_System WRITE setRunningTime_System NOTIFY RunningTime_SystemChanged);
    Q_PROPERTY(quint8 RunningTime_CallbackScheduler0 READ getRunningTime_CallbackScheduler0 WRITE setRunningTime_CallbackScheduler0 NOTIFY RunningTime_CallbackScheduler0Changed);
    Q_PROPERTY(quint8 RunningTime_CallbackScheduler1 READ getRunningTime_CallbackScheduler1 WRITE setRunningTime_CallbackScheduler1 NOTIFY RunningTime_CallbackScheduler1Changed);
    Q_PROPERTY(quint8 RunningTime_CallbackScheduler2 READ getRunningTime_CallbackScheduler2 WRITE setRunningTime_CallbackScheduler2 NOTIFY RunningTime_CallbackScheduler2Changed);
    Q_PROPERTY(quint8 RunningTime_CallbackScheduler3 READ getRunningTime_CallbackScheduler3 WRITE setRunningTime_CallbackScheduler3 NOTIFY RunningTime_CallbackScheduler3Changed);
    Q_PROPERTY(quint8 RunningTime_Receiver READ getRunningTime_Receiver WRITE setRunningTime_Receiver NOTIFY RunningTime_ReceiverChanged);
    Q_PROPERTY(quint8 RunningTime_Stabilization READ getRunningTime_Stabilization WRITE setRunningTime_Stabilization NOTIFY RunningTime_StabilizationChanged);
    Q_PROPERTY(quint8 RunningTime_Actuator READ getRunningTime_Actuator WRITE setRunningTime_Actuator NOTIFY RunningTime_ActuatorChanged);
    Q_PROPERTY(quint8 RunningTime_Sensors READ getRunningTime_Sensors WRITE setRunningTime_Sensors NOTIFY RunningTime_SensorsChanged);
    Q_PROPERTY(quint8 RunningTime_Attitude READ getRunningTime_Attitude WRITE setRunningTime_Attitude NOTIFY RunningTime_AttitudeChanged);
    Q_PROPERTY(quint8 RunningTime_Altitude READ getRunningTime_Altitude WRITE setRunningTime_Altitude NOTIFY RunningTime_AltitudeChanged);
    Q_PROPERTY(quint8 RunningTime_Airspeed READ getRunningTime_Airspeed WRITE setRunningTime_Airspeed NOTIFY RunningTime_AirspeedChanged);
    Q_PROPERTY(quint8 RunningTime_MagBaro READ getRunningTime_MagBaro WRITE setRunningTime_MagBaro NOTIFY RunningTime_MagBaroChanged);
    Q_PROPERTY(quint8 RunningTime_FlightPlan READ getRunningTime_FlightPlan WRITE setRunningTime_FlightPlan NOTIFY RunningTime_FlightPlanChanged);
    Q_PROPERTY(quint8 RunningTime_TelemetryTx READ getRunningTime_TelemetryTx WRITE setRunningTime_TelemetryTx NOTIFY RunningTime_TelemetryTxChanged);
    Q_PROPERTY(quint8 RunningTime_TelemetryRx READ getRunningTime_TelemetryRx WRITE setRunningTime_TelemetryRx NOTIFY RunningTime_TelemetryRxChanged);
    Q_PROPERTY(quint8 RunningTime_RadioRx READ getRunningTime_RadioRx WRITE setRunningTime_RadioRx NOTIFY RunningTime_RadioRxChanged);
    Q_PROPERTY(quint8 RunningTime_Com2UsbBridge READ getRunningTime_Com2UsbBridge WRITE setRunningTime_Com2UsbBridge NOTIFY RunningTime_Com2UsbBridgeChanged);
    Q_PROPERTY(quint8 RunningTime_Usb2ComBridge READ getRunningTime_Usb2ComBridge WRITE setRunningTime_Usb2ComBridge NOTIFY RunningTime_Usb2ComBridgeChanged);
    Q_PROPERTY(quint8 RunningTime_GPS READ getRunningTime_GPS WRITE setRunningTime_GPS NOTIFY RunningTime_GPSChanged);
    Q_PROPERTY(quint8 RunningTime_OSDGen READ getRunningTime_OSDGen WRITE setRunningTime_OSDGen NOTIFY RunningTime_OSDGenChanged);


public:
    // Field structure
    typedef struct {
        quint16 StackRemaining[21];
        quint8 Running[21];
        quint8 RunningTime[21];

    } __attribute__((packed)) DataFields;

    // Field information
    // Field StackRemaining information
    /* Array element names for field StackRemaining */
    typedef enum { STACKREMAINING_SYSTEM=0, STACKREMAINING_CALLBACKSCHEDULER0=1, STACKREMAINING_CALLBACKSCHEDULER1=2, STACKREMAINING_CALLBACKSCHEDULER2=3, STACKREMAINING_CALLBACKSCHEDULER3=4, STACKREMAINING_RECEIVER=5, STACKREMAINING_STABILIZATION=6, STACKREMAINING_ACTUATOR=7, STACKREMAINING_SENSORS=8, STACKREMAINING_ATTITUDE=9, STACKREMAINING_ALTITUDE=10, STACKREMAINING_AIRSPEED=11, STACKREMAINING_MAGBARO=12, STACKREMAINING_FLIGHTPLAN=13, STACKREMAINING_TELEMETRYTX=14, STACKREMAINING_TELEMETRYRX=15, STACKREMAINING_RADIORX=16, STACKREMAINING_COM2USBBRIDGE=17, STACKREMAINING_USB2COMBRIDGE=18, STACKREMAINING_GPS=19, STACKREMAINING_OSDGEN=20 } StackRemainingElem;
    /* Number of elements for field StackRemaining */
    static const quint32 STACKREMAINING_NUMELEM = 21;
    // Field Running information
    /* Enumeration options for field Running */
    typedef enum { RUNNING_FALSE=0, RUNNING_TRUE=1 } RunningOptions;
    /* Array element names for field Running */
    typedef enum { RUNNING_SYSTEM=0, RUNNING_CALLBACKSCHEDULER0=1, RUNNING_CALLBACKSCHEDULER1=2, RUNNING_CALLBACKSCHEDULER2=3, RUNNING_CALLBACKSCHEDULER3=4, RUNNING_RECEIVER=5, RUNNING_STABILIZATION=6, RUNNING_ACTUATOR=7, RUNNING_SENSORS=8, RUNNING_ATTITUDE=9, RUNNING_ALTITUDE=10, RUNNING_AIRSPEED=11, RUNNING_MAGBARO=12, RUNNING_FLIGHTPLAN=13, RUNNING_TELEMETRYTX=14, RUNNING_TELEMETRYRX=15, RUNNING_RADIORX=16, RUNNING_COM2USBBRIDGE=17, RUNNING_USB2COMBRIDGE=18, RUNNING_GPS=19, RUNNING_OSDGEN=20 } RunningElem;
    /* Number of elements for field Running */
    static const quint32 RUNNING_NUMELEM = 21;
    // Field RunningTime information
    /* Array element names for field RunningTime */
    typedef enum { RUNNINGTIME_SYSTEM=0, RUNNINGTIME_CALLBACKSCHEDULER0=1, RUNNINGTIME_CALLBACKSCHEDULER1=2, RUNNINGTIME_CALLBACKSCHEDULER2=3, RUNNINGTIME_CALLBACKSCHEDULER3=4, RUNNINGTIME_RECEIVER=5, RUNNINGTIME_STABILIZATION=6, RUNNINGTIME_ACTUATOR=7, RUNNINGTIME_SENSORS=8, RUNNINGTIME_ATTITUDE=9, RUNNINGTIME_ALTITUDE=10, RUNNINGTIME_AIRSPEED=11, RUNNINGTIME_MAGBARO=12, RUNNINGTIME_FLIGHTPLAN=13, RUNNINGTIME_TELEMETRYTX=14, RUNNINGTIME_TELEMETRYRX=15, RUNNINGTIME_RADIORX=16, RUNNINGTIME_COM2USBBRIDGE=17, RUNNINGTIME_USB2COMBRIDGE=18, RUNNINGTIME_GPS=19, RUNNINGTIME_OSDGEN=20 } RunningTimeElem;
    /* Number of elements for field RunningTime */
    static const quint32 RUNNINGTIME_NUMELEM = 21;

  
    // Constants
    static const quint32 OBJID = 0x7A28AFE8;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    TaskInfo();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static TaskInfo* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint16 getStackRemaining(quint32 index) const;
    Q_INVOKABLE quint16 getStackRemaining_System() const;
    Q_INVOKABLE quint16 getStackRemaining_CallbackScheduler0() const;
    Q_INVOKABLE quint16 getStackRemaining_CallbackScheduler1() const;
    Q_INVOKABLE quint16 getStackRemaining_CallbackScheduler2() const;
    Q_INVOKABLE quint16 getStackRemaining_CallbackScheduler3() const;
    Q_INVOKABLE quint16 getStackRemaining_Receiver() const;
    Q_INVOKABLE quint16 getStackRemaining_Stabilization() const;
    Q_INVOKABLE quint16 getStackRemaining_Actuator() const;
    Q_INVOKABLE quint16 getStackRemaining_Sensors() const;
    Q_INVOKABLE quint16 getStackRemaining_Attitude() const;
    Q_INVOKABLE quint16 getStackRemaining_Altitude() const;
    Q_INVOKABLE quint16 getStackRemaining_Airspeed() const;
    Q_INVOKABLE quint16 getStackRemaining_MagBaro() const;
    Q_INVOKABLE quint16 getStackRemaining_FlightPlan() const;
    Q_INVOKABLE quint16 getStackRemaining_TelemetryTx() const;
    Q_INVOKABLE quint16 getStackRemaining_TelemetryRx() const;
    Q_INVOKABLE quint16 getStackRemaining_RadioRx() const;
    Q_INVOKABLE quint16 getStackRemaining_Com2UsbBridge() const;
    Q_INVOKABLE quint16 getStackRemaining_Usb2ComBridge() const;
    Q_INVOKABLE quint16 getStackRemaining_GPS() const;
    Q_INVOKABLE quint16 getStackRemaining_OSDGen() const;
    Q_INVOKABLE quint8 getRunning(quint32 index) const;
    Q_INVOKABLE quint8 getRunning_System() const;
    Q_INVOKABLE quint8 getRunning_CallbackScheduler0() const;
    Q_INVOKABLE quint8 getRunning_CallbackScheduler1() const;
    Q_INVOKABLE quint8 getRunning_CallbackScheduler2() const;
    Q_INVOKABLE quint8 getRunning_CallbackScheduler3() const;
    Q_INVOKABLE quint8 getRunning_Receiver() const;
    Q_INVOKABLE quint8 getRunning_Stabilization() const;
    Q_INVOKABLE quint8 getRunning_Actuator() const;
    Q_INVOKABLE quint8 getRunning_Sensors() const;
    Q_INVOKABLE quint8 getRunning_Attitude() const;
    Q_INVOKABLE quint8 getRunning_Altitude() const;
    Q_INVOKABLE quint8 getRunning_Airspeed() const;
    Q_INVOKABLE quint8 getRunning_MagBaro() const;
    Q_INVOKABLE quint8 getRunning_FlightPlan() const;
    Q_INVOKABLE quint8 getRunning_TelemetryTx() const;
    Q_INVOKABLE quint8 getRunning_TelemetryRx() const;
    Q_INVOKABLE quint8 getRunning_RadioRx() const;
    Q_INVOKABLE quint8 getRunning_Com2UsbBridge() const;
    Q_INVOKABLE quint8 getRunning_Usb2ComBridge() const;
    Q_INVOKABLE quint8 getRunning_GPS() const;
    Q_INVOKABLE quint8 getRunning_OSDGen() const;
    Q_INVOKABLE quint8 getRunningTime(quint32 index) const;
    Q_INVOKABLE quint8 getRunningTime_System() const;
    Q_INVOKABLE quint8 getRunningTime_CallbackScheduler0() const;
    Q_INVOKABLE quint8 getRunningTime_CallbackScheduler1() const;
    Q_INVOKABLE quint8 getRunningTime_CallbackScheduler2() const;
    Q_INVOKABLE quint8 getRunningTime_CallbackScheduler3() const;
    Q_INVOKABLE quint8 getRunningTime_Receiver() const;
    Q_INVOKABLE quint8 getRunningTime_Stabilization() const;
    Q_INVOKABLE quint8 getRunningTime_Actuator() const;
    Q_INVOKABLE quint8 getRunningTime_Sensors() const;
    Q_INVOKABLE quint8 getRunningTime_Attitude() const;
    Q_INVOKABLE quint8 getRunningTime_Altitude() const;
    Q_INVOKABLE quint8 getRunningTime_Airspeed() const;
    Q_INVOKABLE quint8 getRunningTime_MagBaro() const;
    Q_INVOKABLE quint8 getRunningTime_FlightPlan() const;
    Q_INVOKABLE quint8 getRunningTime_TelemetryTx() const;
    Q_INVOKABLE quint8 getRunningTime_TelemetryRx() const;
    Q_INVOKABLE quint8 getRunningTime_RadioRx() const;
    Q_INVOKABLE quint8 getRunningTime_Com2UsbBridge() const;
    Q_INVOKABLE quint8 getRunningTime_Usb2ComBridge() const;
    Q_INVOKABLE quint8 getRunningTime_GPS() const;
    Q_INVOKABLE quint8 getRunningTime_OSDGen() const;


public slots:
    void setStackRemaining(quint32 index, quint16 value);
    void setStackRemaining_System(quint16 value);
    void setStackRemaining_CallbackScheduler0(quint16 value);
    void setStackRemaining_CallbackScheduler1(quint16 value);
    void setStackRemaining_CallbackScheduler2(quint16 value);
    void setStackRemaining_CallbackScheduler3(quint16 value);
    void setStackRemaining_Receiver(quint16 value);
    void setStackRemaining_Stabilization(quint16 value);
    void setStackRemaining_Actuator(quint16 value);
    void setStackRemaining_Sensors(quint16 value);
    void setStackRemaining_Attitude(quint16 value);
    void setStackRemaining_Altitude(quint16 value);
    void setStackRemaining_Airspeed(quint16 value);
    void setStackRemaining_MagBaro(quint16 value);
    void setStackRemaining_FlightPlan(quint16 value);
    void setStackRemaining_TelemetryTx(quint16 value);
    void setStackRemaining_TelemetryRx(quint16 value);
    void setStackRemaining_RadioRx(quint16 value);
    void setStackRemaining_Com2UsbBridge(quint16 value);
    void setStackRemaining_Usb2ComBridge(quint16 value);
    void setStackRemaining_GPS(quint16 value);
    void setStackRemaining_OSDGen(quint16 value);
    void setRunning(quint32 index, quint8 value);
    void setRunning_System(quint8 value);
    void setRunning_CallbackScheduler0(quint8 value);
    void setRunning_CallbackScheduler1(quint8 value);
    void setRunning_CallbackScheduler2(quint8 value);
    void setRunning_CallbackScheduler3(quint8 value);
    void setRunning_Receiver(quint8 value);
    void setRunning_Stabilization(quint8 value);
    void setRunning_Actuator(quint8 value);
    void setRunning_Sensors(quint8 value);
    void setRunning_Attitude(quint8 value);
    void setRunning_Altitude(quint8 value);
    void setRunning_Airspeed(quint8 value);
    void setRunning_MagBaro(quint8 value);
    void setRunning_FlightPlan(quint8 value);
    void setRunning_TelemetryTx(quint8 value);
    void setRunning_TelemetryRx(quint8 value);
    void setRunning_RadioRx(quint8 value);
    void setRunning_Com2UsbBridge(quint8 value);
    void setRunning_Usb2ComBridge(quint8 value);
    void setRunning_GPS(quint8 value);
    void setRunning_OSDGen(quint8 value);
    void setRunningTime(quint32 index, quint8 value);
    void setRunningTime_System(quint8 value);
    void setRunningTime_CallbackScheduler0(quint8 value);
    void setRunningTime_CallbackScheduler1(quint8 value);
    void setRunningTime_CallbackScheduler2(quint8 value);
    void setRunningTime_CallbackScheduler3(quint8 value);
    void setRunningTime_Receiver(quint8 value);
    void setRunningTime_Stabilization(quint8 value);
    void setRunningTime_Actuator(quint8 value);
    void setRunningTime_Sensors(quint8 value);
    void setRunningTime_Attitude(quint8 value);
    void setRunningTime_Altitude(quint8 value);
    void setRunningTime_Airspeed(quint8 value);
    void setRunningTime_MagBaro(quint8 value);
    void setRunningTime_FlightPlan(quint8 value);
    void setRunningTime_TelemetryTx(quint8 value);
    void setRunningTime_TelemetryRx(quint8 value);
    void setRunningTime_RadioRx(quint8 value);
    void setRunningTime_Com2UsbBridge(quint8 value);
    void setRunningTime_Usb2ComBridge(quint8 value);
    void setRunningTime_GPS(quint8 value);
    void setRunningTime_OSDGen(quint8 value);


signals:
    void StackRemainingChanged(quint32 index, quint16 value);
    void StackRemaining_SystemChanged(quint16 value);
    void StackRemaining_CallbackScheduler0Changed(quint16 value);
    void StackRemaining_CallbackScheduler1Changed(quint16 value);
    void StackRemaining_CallbackScheduler2Changed(quint16 value);
    void StackRemaining_CallbackScheduler3Changed(quint16 value);
    void StackRemaining_ReceiverChanged(quint16 value);
    void StackRemaining_StabilizationChanged(quint16 value);
    void StackRemaining_ActuatorChanged(quint16 value);
    void StackRemaining_SensorsChanged(quint16 value);
    void StackRemaining_AttitudeChanged(quint16 value);
    void StackRemaining_AltitudeChanged(quint16 value);
    void StackRemaining_AirspeedChanged(quint16 value);
    void StackRemaining_MagBaroChanged(quint16 value);
    void StackRemaining_FlightPlanChanged(quint16 value);
    void StackRemaining_TelemetryTxChanged(quint16 value);
    void StackRemaining_TelemetryRxChanged(quint16 value);
    void StackRemaining_RadioRxChanged(quint16 value);
    void StackRemaining_Com2UsbBridgeChanged(quint16 value);
    void StackRemaining_Usb2ComBridgeChanged(quint16 value);
    void StackRemaining_GPSChanged(quint16 value);
    void StackRemaining_OSDGenChanged(quint16 value);
    void RunningChanged(quint32 index, quint8 value);
    void Running_SystemChanged(quint8 value);
    void Running_CallbackScheduler0Changed(quint8 value);
    void Running_CallbackScheduler1Changed(quint8 value);
    void Running_CallbackScheduler2Changed(quint8 value);
    void Running_CallbackScheduler3Changed(quint8 value);
    void Running_ReceiverChanged(quint8 value);
    void Running_StabilizationChanged(quint8 value);
    void Running_ActuatorChanged(quint8 value);
    void Running_SensorsChanged(quint8 value);
    void Running_AttitudeChanged(quint8 value);
    void Running_AltitudeChanged(quint8 value);
    void Running_AirspeedChanged(quint8 value);
    void Running_MagBaroChanged(quint8 value);
    void Running_FlightPlanChanged(quint8 value);
    void Running_TelemetryTxChanged(quint8 value);
    void Running_TelemetryRxChanged(quint8 value);
    void Running_RadioRxChanged(quint8 value);
    void Running_Com2UsbBridgeChanged(quint8 value);
    void Running_Usb2ComBridgeChanged(quint8 value);
    void Running_GPSChanged(quint8 value);
    void Running_OSDGenChanged(quint8 value);
    void RunningTimeChanged(quint32 index, quint8 value);
    void RunningTime_SystemChanged(quint8 value);
    void RunningTime_CallbackScheduler0Changed(quint8 value);
    void RunningTime_CallbackScheduler1Changed(quint8 value);
    void RunningTime_CallbackScheduler2Changed(quint8 value);
    void RunningTime_CallbackScheduler3Changed(quint8 value);
    void RunningTime_ReceiverChanged(quint8 value);
    void RunningTime_StabilizationChanged(quint8 value);
    void RunningTime_ActuatorChanged(quint8 value);
    void RunningTime_SensorsChanged(quint8 value);
    void RunningTime_AttitudeChanged(quint8 value);
    void RunningTime_AltitudeChanged(quint8 value);
    void RunningTime_AirspeedChanged(quint8 value);
    void RunningTime_MagBaroChanged(quint8 value);
    void RunningTime_FlightPlanChanged(quint8 value);
    void RunningTime_TelemetryTxChanged(quint8 value);
    void RunningTime_TelemetryRxChanged(quint8 value);
    void RunningTime_RadioRxChanged(quint8 value);
    void RunningTime_Com2UsbBridgeChanged(quint8 value);
    void RunningTime_Usb2ComBridgeChanged(quint8 value);
    void RunningTime_GPSChanged(quint8 value);
    void RunningTime_OSDGenChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // TASKINFO_H
