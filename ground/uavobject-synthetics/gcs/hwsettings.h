/**
 ******************************************************************************
 *
 * @file       hwsettings.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: hwsettings.xml. 
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
#ifndef HWSETTINGS_H
#define HWSETTINGS_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT HwSettings: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 CC_RcvrPort READ getCC_RcvrPort WRITE setCC_RcvrPort NOTIFY CC_RcvrPortChanged);
    Q_PROPERTY(quint8 CC_MainPort READ getCC_MainPort WRITE setCC_MainPort NOTIFY CC_MainPortChanged);
    Q_PROPERTY(quint8 CC_FlexiPort READ getCC_FlexiPort WRITE setCC_FlexiPort NOTIFY CC_FlexiPortChanged);
    Q_PROPERTY(quint8 RV_RcvrPort READ getRV_RcvrPort WRITE setRV_RcvrPort NOTIFY RV_RcvrPortChanged);
    Q_PROPERTY(quint8 RV_AuxPort READ getRV_AuxPort WRITE setRV_AuxPort NOTIFY RV_AuxPortChanged);
    Q_PROPERTY(quint8 RV_AuxSBusPort READ getRV_AuxSBusPort WRITE setRV_AuxSBusPort NOTIFY RV_AuxSBusPortChanged);
    Q_PROPERTY(quint8 RV_FlexiPort READ getRV_FlexiPort WRITE setRV_FlexiPort NOTIFY RV_FlexiPortChanged);
    Q_PROPERTY(quint8 RV_TelemetryPort READ getRV_TelemetryPort WRITE setRV_TelemetryPort NOTIFY RV_TelemetryPortChanged);
    Q_PROPERTY(quint8 RV_GPSPort READ getRV_GPSPort WRITE setRV_GPSPort NOTIFY RV_GPSPortChanged);
    Q_PROPERTY(quint8 RM_RcvrPort READ getRM_RcvrPort WRITE setRM_RcvrPort NOTIFY RM_RcvrPortChanged);
    Q_PROPERTY(quint8 RM_MainPort READ getRM_MainPort WRITE setRM_MainPort NOTIFY RM_MainPortChanged);
    Q_PROPERTY(quint8 RM_FlexiPort READ getRM_FlexiPort WRITE setRM_FlexiPort NOTIFY RM_FlexiPortChanged);
    Q_PROPERTY(quint8 TelemetrySpeed READ getTelemetrySpeed WRITE setTelemetrySpeed NOTIFY TelemetrySpeedChanged);
    Q_PROPERTY(quint8 GPSSpeed READ getGPSSpeed WRITE setGPSSpeed NOTIFY GPSSpeedChanged);
    Q_PROPERTY(quint8 ComUsbBridgeSpeed READ getComUsbBridgeSpeed WRITE setComUsbBridgeSpeed NOTIFY ComUsbBridgeSpeedChanged);
    Q_PROPERTY(quint8 USB_HIDPort READ getUSB_HIDPort WRITE setUSB_HIDPort NOTIFY USB_HIDPortChanged);
    Q_PROPERTY(quint8 USB_VCPPort READ getUSB_VCPPort WRITE setUSB_VCPPort NOTIFY USB_VCPPortChanged);
    Q_PROPERTY(quint8 OptionalModules_CameraStab READ getOptionalModules_CameraStab WRITE setOptionalModules_CameraStab NOTIFY OptionalModules_CameraStabChanged);
    Q_PROPERTY(quint8 OptionalModules_GPS READ getOptionalModules_GPS WRITE setOptionalModules_GPS NOTIFY OptionalModules_GPSChanged);
    Q_PROPERTY(quint8 OptionalModules_Fault READ getOptionalModules_Fault WRITE setOptionalModules_Fault NOTIFY OptionalModules_FaultChanged);
    Q_PROPERTY(quint8 OptionalModules_Altitude READ getOptionalModules_Altitude WRITE setOptionalModules_Altitude NOTIFY OptionalModules_AltitudeChanged);
    Q_PROPERTY(quint8 OptionalModules_Airspeed READ getOptionalModules_Airspeed WRITE setOptionalModules_Airspeed NOTIFY OptionalModules_AirspeedChanged);
    Q_PROPERTY(quint8 OptionalModules_TxPID READ getOptionalModules_TxPID WRITE setOptionalModules_TxPID NOTIFY OptionalModules_TxPIDChanged);
    Q_PROPERTY(quint8 OptionalModules_Battery READ getOptionalModules_Battery WRITE setOptionalModules_Battery NOTIFY OptionalModules_BatteryChanged);
    Q_PROPERTY(quint8 OptionalModules_Overo READ getOptionalModules_Overo WRITE setOptionalModules_Overo NOTIFY OptionalModules_OveroChanged);
    Q_PROPERTY(quint8 OptionalModules_MagBaro READ getOptionalModules_MagBaro WRITE setOptionalModules_MagBaro NOTIFY OptionalModules_MagBaroChanged);
    Q_PROPERTY(quint8 OptionalModules_OsdHk READ getOptionalModules_OsdHk WRITE setOptionalModules_OsdHk NOTIFY OptionalModules_OsdHkChanged);
    Q_PROPERTY(quint8 ADCRouting_adc0 READ getADCRouting_adc0 WRITE setADCRouting_adc0 NOTIFY ADCRouting_adc0Changed);
    Q_PROPERTY(quint8 ADCRouting_adc1 READ getADCRouting_adc1 WRITE setADCRouting_adc1 NOTIFY ADCRouting_adc1Changed);
    Q_PROPERTY(quint8 ADCRouting_adc2 READ getADCRouting_adc2 WRITE setADCRouting_adc2 NOTIFY ADCRouting_adc2Changed);
    Q_PROPERTY(quint8 ADCRouting_adc3 READ getADCRouting_adc3 WRITE setADCRouting_adc3 NOTIFY ADCRouting_adc3Changed);
    Q_PROPERTY(quint8 DSMxBind READ getDSMxBind WRITE setDSMxBind NOTIFY DSMxBindChanged);
    Q_PROPERTY(quint8 WS2811LED_Out READ getWS2811LED_Out WRITE setWS2811LED_Out NOTIFY WS2811LED_OutChanged);


public:
    // Field structure
    typedef struct {
        quint8 CC_RcvrPort;
        quint8 CC_MainPort;
        quint8 CC_FlexiPort;
        quint8 RV_RcvrPort;
        quint8 RV_AuxPort;
        quint8 RV_AuxSBusPort;
        quint8 RV_FlexiPort;
        quint8 RV_TelemetryPort;
        quint8 RV_GPSPort;
        quint8 RM_RcvrPort;
        quint8 RM_MainPort;
        quint8 RM_FlexiPort;
        quint8 TelemetrySpeed;
        quint8 GPSSpeed;
        quint8 ComUsbBridgeSpeed;
        quint8 USB_HIDPort;
        quint8 USB_VCPPort;
        quint8 OptionalModules[10];
        quint8 ADCRouting[4];
        quint8 DSMxBind;
        quint8 WS2811LED_Out;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field CC_RcvrPort information
    /* Enumeration options for field CC_RcvrPort */
    typedef enum { CC_RCVRPORT_DISABLEDONESHOT=0, CC_RCVRPORT_PWMNOONESHOT=1, CC_RCVRPORT_PPMNOONESHOT=2, CC_RCVRPORT_PPMPWMNOONESHOT=3, CC_RCVRPORT_PPMOUTPUTSNOONESHOT=4, CC_RCVRPORT_PPM_PIN8ONESHOT=5, CC_RCVRPORT_OUTPUTSONESHOT=6 } CC_RcvrPortOptions;
    // Field CC_MainPort information
    /* Enumeration options for field CC_MainPort */
    typedef enum { CC_MAINPORT_DISABLED=0, CC_MAINPORT_TELEMETRY=1, CC_MAINPORT_GPS=2, CC_MAINPORT_SBUS=3, CC_MAINPORT_DSM=4, CC_MAINPORT_DEBUGCONSOLE=5, CC_MAINPORT_COMBRIDGE=6, CC_MAINPORT_OSDHK=7 } CC_MainPortOptions;
    // Field CC_FlexiPort information
    /* Enumeration options for field CC_FlexiPort */
    typedef enum { CC_FLEXIPORT_DISABLED=0, CC_FLEXIPORT_TELEMETRY=1, CC_FLEXIPORT_GPS=2, CC_FLEXIPORT_I2C=3, CC_FLEXIPORT_PPM=4, CC_FLEXIPORT_DSM=5, CC_FLEXIPORT_DEBUGCONSOLE=6, CC_FLEXIPORT_COMBRIDGE=7, CC_FLEXIPORT_OSDHK=8 } CC_FlexiPortOptions;
    // Field RV_RcvrPort information
    /* Enumeration options for field RV_RcvrPort */
    typedef enum { RV_RCVRPORT_DISABLED=0, RV_RCVRPORT_PWM=1, RV_RCVRPORT_PPM=2, RV_RCVRPORT_PPMOUTPUTS=3, RV_RCVRPORT_OUTPUTS=4 } RV_RcvrPortOptions;
    // Field RV_AuxPort information
    /* Enumeration options for field RV_AuxPort */
    typedef enum { RV_AUXPORT_DISABLED=0, RV_AUXPORT_TELEMETRY=1, RV_AUXPORT_DSM=2, RV_AUXPORT_COMAUX=3, RV_AUXPORT_COMBRIDGE=4, RV_AUXPORT_OSDHK=5 } RV_AuxPortOptions;
    // Field RV_AuxSBusPort information
    /* Enumeration options for field RV_AuxSBusPort */
    typedef enum { RV_AUXSBUSPORT_DISABLED=0, RV_AUXSBUSPORT_SBUS=1, RV_AUXSBUSPORT_DSM=2, RV_AUXSBUSPORT_COMAUX=3, RV_AUXSBUSPORT_COMBRIDGE=4, RV_AUXSBUSPORT_OSDHK=5 } RV_AuxSBusPortOptions;
    // Field RV_FlexiPort information
    /* Enumeration options for field RV_FlexiPort */
    typedef enum { RV_FLEXIPORT_DISABLED=0, RV_FLEXIPORT_I2C=1, RV_FLEXIPORT_DSM=2, RV_FLEXIPORT_COMAUX=3, RV_FLEXIPORT_COMBRIDGE=4 } RV_FlexiPortOptions;
    // Field RV_TelemetryPort information
    /* Enumeration options for field RV_TelemetryPort */
    typedef enum { RV_TELEMETRYPORT_DISABLED=0, RV_TELEMETRYPORT_TELEMETRY=1, RV_TELEMETRYPORT_COMAUX=2, RV_TELEMETRYPORT_COMBRIDGE=3 } RV_TelemetryPortOptions;
    // Field RV_GPSPort information
    /* Enumeration options for field RV_GPSPort */
    typedef enum { RV_GPSPORT_DISABLED=0, RV_GPSPORT_TELEMETRY=1, RV_GPSPORT_GPS=2, RV_GPSPORT_COMAUX=3, RV_GPSPORT_COMBRIDGE=4 } RV_GPSPortOptions;
    // Field RM_RcvrPort information
    /* Enumeration options for field RM_RcvrPort */
    typedef enum { RM_RCVRPORT_DISABLED=0, RM_RCVRPORT_PWM=1, RM_RCVRPORT_PPM=2, RM_RCVRPORT_PPMPWM=3, RM_RCVRPORT_PPMTELEMETRY=4, RM_RCVRPORT_PPMOUTPUTS=5, RM_RCVRPORT_OUTPUTS=6, RM_RCVRPORT_TELEMETRY=7 } RM_RcvrPortOptions;
    // Field RM_MainPort information
    /* Enumeration options for field RM_MainPort */
    typedef enum { RM_MAINPORT_DISABLED=0, RM_MAINPORT_TELEMETRY=1, RM_MAINPORT_GPS=2, RM_MAINPORT_SBUS=3, RM_MAINPORT_DSM=4, RM_MAINPORT_DEBUGCONSOLE=5, RM_MAINPORT_COMBRIDGE=6, RM_MAINPORT_OSDHK=7 } RM_MainPortOptions;
    // Field RM_FlexiPort information
    /* Enumeration options for field RM_FlexiPort */
    typedef enum { RM_FLEXIPORT_DISABLED=0, RM_FLEXIPORT_TELEMETRY=1, RM_FLEXIPORT_GPS=2, RM_FLEXIPORT_I2C=3, RM_FLEXIPORT_DSM=4, RM_FLEXIPORT_DEBUGCONSOLE=5, RM_FLEXIPORT_COMBRIDGE=6, RM_FLEXIPORT_OSDHK=7 } RM_FlexiPortOptions;
    // Field TelemetrySpeed information
    /* Enumeration options for field TelemetrySpeed */
    typedef enum { TELEMETRYSPEED_2400=0, TELEMETRYSPEED_4800=1, TELEMETRYSPEED_9600=2, TELEMETRYSPEED_19200=3, TELEMETRYSPEED_38400=4, TELEMETRYSPEED_57600=5, TELEMETRYSPEED_115200=6 } TelemetrySpeedOptions;
    // Field GPSSpeed information
    /* Enumeration options for field GPSSpeed */
    typedef enum { GPSSPEED_2400=0, GPSSPEED_4800=1, GPSSPEED_9600=2, GPSSPEED_19200=3, GPSSPEED_38400=4, GPSSPEED_57600=5, GPSSPEED_115200=6, GPSSPEED_230400=7 } GPSSpeedOptions;
    // Field ComUsbBridgeSpeed information
    /* Enumeration options for field ComUsbBridgeSpeed */
    typedef enum { COMUSBBRIDGESPEED_2400=0, COMUSBBRIDGESPEED_4800=1, COMUSBBRIDGESPEED_9600=2, COMUSBBRIDGESPEED_19200=3, COMUSBBRIDGESPEED_38400=4, COMUSBBRIDGESPEED_57600=5, COMUSBBRIDGESPEED_115200=6 } ComUsbBridgeSpeedOptions;
    // Field USB_HIDPort information
    /* Enumeration options for field USB_HIDPort */
    typedef enum { USB_HIDPORT_USBTELEMETRY=0, USB_HIDPORT_RCTRANSMITTER=1, USB_HIDPORT_DISABLED=2 } USB_HIDPortOptions;
    // Field USB_VCPPort information
    /* Enumeration options for field USB_VCPPort */
    typedef enum { USB_VCPPORT_USBTELEMETRY=0, USB_VCPPORT_COMBRIDGE=1, USB_VCPPORT_DEBUGCONSOLE=2, USB_VCPPORT_DISABLED=3 } USB_VCPPortOptions;
    // Field OptionalModules information
    /* Enumeration options for field OptionalModules */
    typedef enum { OPTIONALMODULES_DISABLED=0, OPTIONALMODULES_ENABLED=1 } OptionalModulesOptions;
    /* Array element names for field OptionalModules */
    typedef enum { OPTIONALMODULES_CAMERASTAB=0, OPTIONALMODULES_GPS=1, OPTIONALMODULES_FAULT=2, OPTIONALMODULES_ALTITUDE=3, OPTIONALMODULES_AIRSPEED=4, OPTIONALMODULES_TXPID=5, OPTIONALMODULES_BATTERY=6, OPTIONALMODULES_OVERO=7, OPTIONALMODULES_MAGBARO=8, OPTIONALMODULES_OSDHK=9 } OptionalModulesElem;
    /* Number of elements for field OptionalModules */
    static const quint32 OPTIONALMODULES_NUMELEM = 10;
    // Field ADCRouting information
    /* Enumeration options for field ADCRouting */
    typedef enum { ADCROUTING_DISABLED=0, ADCROUTING_BATTERYVOLTAGE=1, ADCROUTING_BATTERYCURRENT=2, ADCROUTING_ANALOGAIRSPEED=3, ADCROUTING_GENERIC=4 } ADCRoutingOptions;
    /* Array element names for field ADCRouting */
    typedef enum { ADCROUTING_ADC0=0, ADCROUTING_ADC1=1, ADCROUTING_ADC2=2, ADCROUTING_ADC3=3 } ADCRoutingElem;
    /* Number of elements for field ADCRouting */
    static const quint32 ADCROUTING_NUMELEM = 4;
    // Field DSMxBind information
    // Field WS2811LED_Out information
    /* Enumeration options for field WS2811LED_Out */
    typedef enum { WS2811LED_OUT_SERVOOUT1=0, WS2811LED_OUT_SERVOOUT2=1, WS2811LED_OUT_SERVOOUT3=2, WS2811LED_OUT_SERVOOUT4=3, WS2811LED_OUT_SERVOOUT5=4, WS2811LED_OUT_SERVOOUT6=5, WS2811LED_OUT_FLEXIIOPIN3=6, WS2811LED_OUT_FLEXIIOPIN4=7, WS2811LED_OUT_DISABLED=8 } WS2811LED_OutOptions;

  
    // Constants
    static const quint32 OBJID = 0xA65C5CD0;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 1;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    HwSettings();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static HwSettings* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE quint8 getCC_RcvrPort() const;
    Q_INVOKABLE quint8 getCC_MainPort() const;
    Q_INVOKABLE quint8 getCC_FlexiPort() const;
    Q_INVOKABLE quint8 getRV_RcvrPort() const;
    Q_INVOKABLE quint8 getRV_AuxPort() const;
    Q_INVOKABLE quint8 getRV_AuxSBusPort() const;
    Q_INVOKABLE quint8 getRV_FlexiPort() const;
    Q_INVOKABLE quint8 getRV_TelemetryPort() const;
    Q_INVOKABLE quint8 getRV_GPSPort() const;
    Q_INVOKABLE quint8 getRM_RcvrPort() const;
    Q_INVOKABLE quint8 getRM_MainPort() const;
    Q_INVOKABLE quint8 getRM_FlexiPort() const;
    Q_INVOKABLE quint8 getTelemetrySpeed() const;
    Q_INVOKABLE quint8 getGPSSpeed() const;
    Q_INVOKABLE quint8 getComUsbBridgeSpeed() const;
    Q_INVOKABLE quint8 getUSB_HIDPort() const;
    Q_INVOKABLE quint8 getUSB_VCPPort() const;
    Q_INVOKABLE quint8 getOptionalModules(quint32 index) const;
    Q_INVOKABLE quint8 getOptionalModules_CameraStab() const;
    Q_INVOKABLE quint8 getOptionalModules_GPS() const;
    Q_INVOKABLE quint8 getOptionalModules_Fault() const;
    Q_INVOKABLE quint8 getOptionalModules_Altitude() const;
    Q_INVOKABLE quint8 getOptionalModules_Airspeed() const;
    Q_INVOKABLE quint8 getOptionalModules_TxPID() const;
    Q_INVOKABLE quint8 getOptionalModules_Battery() const;
    Q_INVOKABLE quint8 getOptionalModules_Overo() const;
    Q_INVOKABLE quint8 getOptionalModules_MagBaro() const;
    Q_INVOKABLE quint8 getOptionalModules_OsdHk() const;
    Q_INVOKABLE quint8 getADCRouting(quint32 index) const;
    Q_INVOKABLE quint8 getADCRouting_adc0() const;
    Q_INVOKABLE quint8 getADCRouting_adc1() const;
    Q_INVOKABLE quint8 getADCRouting_adc2() const;
    Q_INVOKABLE quint8 getADCRouting_adc3() const;
    Q_INVOKABLE quint8 getDSMxBind() const;
    Q_INVOKABLE quint8 getWS2811LED_Out() const;


public slots:
    void setCC_RcvrPort(quint8 value);
    void setCC_MainPort(quint8 value);
    void setCC_FlexiPort(quint8 value);
    void setRV_RcvrPort(quint8 value);
    void setRV_AuxPort(quint8 value);
    void setRV_AuxSBusPort(quint8 value);
    void setRV_FlexiPort(quint8 value);
    void setRV_TelemetryPort(quint8 value);
    void setRV_GPSPort(quint8 value);
    void setRM_RcvrPort(quint8 value);
    void setRM_MainPort(quint8 value);
    void setRM_FlexiPort(quint8 value);
    void setTelemetrySpeed(quint8 value);
    void setGPSSpeed(quint8 value);
    void setComUsbBridgeSpeed(quint8 value);
    void setUSB_HIDPort(quint8 value);
    void setUSB_VCPPort(quint8 value);
    void setOptionalModules(quint32 index, quint8 value);
    void setOptionalModules_CameraStab(quint8 value);
    void setOptionalModules_GPS(quint8 value);
    void setOptionalModules_Fault(quint8 value);
    void setOptionalModules_Altitude(quint8 value);
    void setOptionalModules_Airspeed(quint8 value);
    void setOptionalModules_TxPID(quint8 value);
    void setOptionalModules_Battery(quint8 value);
    void setOptionalModules_Overo(quint8 value);
    void setOptionalModules_MagBaro(quint8 value);
    void setOptionalModules_OsdHk(quint8 value);
    void setADCRouting(quint32 index, quint8 value);
    void setADCRouting_adc0(quint8 value);
    void setADCRouting_adc1(quint8 value);
    void setADCRouting_adc2(quint8 value);
    void setADCRouting_adc3(quint8 value);
    void setDSMxBind(quint8 value);
    void setWS2811LED_Out(quint8 value);


signals:
    void CC_RcvrPortChanged(quint8 value);
    void CC_MainPortChanged(quint8 value);
    void CC_FlexiPortChanged(quint8 value);
    void RV_RcvrPortChanged(quint8 value);
    void RV_AuxPortChanged(quint8 value);
    void RV_AuxSBusPortChanged(quint8 value);
    void RV_FlexiPortChanged(quint8 value);
    void RV_TelemetryPortChanged(quint8 value);
    void RV_GPSPortChanged(quint8 value);
    void RM_RcvrPortChanged(quint8 value);
    void RM_MainPortChanged(quint8 value);
    void RM_FlexiPortChanged(quint8 value);
    void TelemetrySpeedChanged(quint8 value);
    void GPSSpeedChanged(quint8 value);
    void ComUsbBridgeSpeedChanged(quint8 value);
    void USB_HIDPortChanged(quint8 value);
    void USB_VCPPortChanged(quint8 value);
    void OptionalModulesChanged(quint32 index, quint8 value);
    void OptionalModules_CameraStabChanged(quint8 value);
    void OptionalModules_GPSChanged(quint8 value);
    void OptionalModules_FaultChanged(quint8 value);
    void OptionalModules_AltitudeChanged(quint8 value);
    void OptionalModules_AirspeedChanged(quint8 value);
    void OptionalModules_TxPIDChanged(quint8 value);
    void OptionalModules_BatteryChanged(quint8 value);
    void OptionalModules_OveroChanged(quint8 value);
    void OptionalModules_MagBaroChanged(quint8 value);
    void OptionalModules_OsdHkChanged(quint8 value);
    void ADCRoutingChanged(quint32 index, quint8 value);
    void ADCRouting_adc0Changed(quint8 value);
    void ADCRouting_adc1Changed(quint8 value);
    void ADCRouting_adc2Changed(quint8 value);
    void ADCRouting_adc3Changed(quint8 value);
    void DSMxBindChanged(quint8 value);
    void WS2811LED_OutChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // HWSETTINGS_H
