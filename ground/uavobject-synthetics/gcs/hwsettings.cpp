/**
 ******************************************************************************
 *
 * @file       hwsettings.cpp
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

#include "hwsettings.h"
#include "uavobjectfield.h"

const QString HwSettings::NAME = QString("HwSettings");
const QString HwSettings::DESCRIPTION = QString("Selection of optional hardware configurations.");
const QString HwSettings::CATEGORY = QString("System");

/**
 * Constructor
 */
HwSettings::HwSettings(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList CC_RcvrPortElemNames;
    CC_RcvrPortElemNames.append("0");
    QStringList CC_RcvrPortEnumOptions;
    CC_RcvrPortEnumOptions.append("Disabled+OneShot");
    CC_RcvrPortEnumOptions.append("PWM+NoOneShot");
    CC_RcvrPortEnumOptions.append("PPM+NoOneShot");
    CC_RcvrPortEnumOptions.append("PPM+PWM+NoOneShot");
    CC_RcvrPortEnumOptions.append("PPM+Outputs+NoOneShot");
    CC_RcvrPortEnumOptions.append("PPM_PIN8+OneShot");
    CC_RcvrPortEnumOptions.append("Outputs+OneShot");
    fields.append( new UAVObjectField(QString("CC_RcvrPort"), tr(""), QString("function"), UAVObjectField::ENUM, CC_RcvrPortElemNames, CC_RcvrPortEnumOptions, QString("")));
    QStringList CC_MainPortElemNames;
    CC_MainPortElemNames.append("0");
    QStringList CC_MainPortEnumOptions;
    CC_MainPortEnumOptions.append("Disabled");
    CC_MainPortEnumOptions.append("Telemetry");
    CC_MainPortEnumOptions.append("GPS");
    CC_MainPortEnumOptions.append("S.Bus");
    CC_MainPortEnumOptions.append("DSM");
    CC_MainPortEnumOptions.append("DebugConsole");
    CC_MainPortEnumOptions.append("ComBridge");
    CC_MainPortEnumOptions.append("OsdHk");
    fields.append( new UAVObjectField(QString("CC_MainPort"), tr(""), QString("function"), UAVObjectField::ENUM, CC_MainPortElemNames, CC_MainPortEnumOptions, QString("")));
    QStringList CC_FlexiPortElemNames;
    CC_FlexiPortElemNames.append("0");
    QStringList CC_FlexiPortEnumOptions;
    CC_FlexiPortEnumOptions.append("Disabled");
    CC_FlexiPortEnumOptions.append("Telemetry");
    CC_FlexiPortEnumOptions.append("GPS");
    CC_FlexiPortEnumOptions.append("I2C");
    CC_FlexiPortEnumOptions.append("PPM");
    CC_FlexiPortEnumOptions.append("DSM");
    CC_FlexiPortEnumOptions.append("DebugConsole");
    CC_FlexiPortEnumOptions.append("ComBridge");
    CC_FlexiPortEnumOptions.append("OsdHk");
    fields.append( new UAVObjectField(QString("CC_FlexiPort"), tr(""), QString("function"), UAVObjectField::ENUM, CC_FlexiPortElemNames, CC_FlexiPortEnumOptions, QString("")));
    QStringList RV_RcvrPortElemNames;
    RV_RcvrPortElemNames.append("0");
    QStringList RV_RcvrPortEnumOptions;
    RV_RcvrPortEnumOptions.append("Disabled");
    RV_RcvrPortEnumOptions.append("PWM");
    RV_RcvrPortEnumOptions.append("PPM");
    RV_RcvrPortEnumOptions.append("PPM+Outputs");
    RV_RcvrPortEnumOptions.append("Outputs");
    fields.append( new UAVObjectField(QString("RV_RcvrPort"), tr(""), QString("function"), UAVObjectField::ENUM, RV_RcvrPortElemNames, RV_RcvrPortEnumOptions, QString("")));
    QStringList RV_AuxPortElemNames;
    RV_AuxPortElemNames.append("0");
    QStringList RV_AuxPortEnumOptions;
    RV_AuxPortEnumOptions.append("Disabled");
    RV_AuxPortEnumOptions.append("Telemetry");
    RV_AuxPortEnumOptions.append("DSM");
    RV_AuxPortEnumOptions.append("ComAux");
    RV_AuxPortEnumOptions.append("ComBridge");
    RV_AuxPortEnumOptions.append("OsdHk");
    fields.append( new UAVObjectField(QString("RV_AuxPort"), tr(""), QString("function"), UAVObjectField::ENUM, RV_AuxPortElemNames, RV_AuxPortEnumOptions, QString("")));
    QStringList RV_AuxSBusPortElemNames;
    RV_AuxSBusPortElemNames.append("0");
    QStringList RV_AuxSBusPortEnumOptions;
    RV_AuxSBusPortEnumOptions.append("Disabled");
    RV_AuxSBusPortEnumOptions.append("S.Bus");
    RV_AuxSBusPortEnumOptions.append("DSM");
    RV_AuxSBusPortEnumOptions.append("ComAux");
    RV_AuxSBusPortEnumOptions.append("ComBridge");
    RV_AuxSBusPortEnumOptions.append("OsdHk");
    fields.append( new UAVObjectField(QString("RV_AuxSBusPort"), tr(""), QString("function"), UAVObjectField::ENUM, RV_AuxSBusPortElemNames, RV_AuxSBusPortEnumOptions, QString("")));
    QStringList RV_FlexiPortElemNames;
    RV_FlexiPortElemNames.append("0");
    QStringList RV_FlexiPortEnumOptions;
    RV_FlexiPortEnumOptions.append("Disabled");
    RV_FlexiPortEnumOptions.append("I2C");
    RV_FlexiPortEnumOptions.append("DSM");
    RV_FlexiPortEnumOptions.append("ComAux");
    RV_FlexiPortEnumOptions.append("ComBridge");
    fields.append( new UAVObjectField(QString("RV_FlexiPort"), tr(""), QString("function"), UAVObjectField::ENUM, RV_FlexiPortElemNames, RV_FlexiPortEnumOptions, QString("")));
    QStringList RV_TelemetryPortElemNames;
    RV_TelemetryPortElemNames.append("0");
    QStringList RV_TelemetryPortEnumOptions;
    RV_TelemetryPortEnumOptions.append("Disabled");
    RV_TelemetryPortEnumOptions.append("Telemetry");
    RV_TelemetryPortEnumOptions.append("ComAux");
    RV_TelemetryPortEnumOptions.append("ComBridge");
    fields.append( new UAVObjectField(QString("RV_TelemetryPort"), tr(""), QString("function"), UAVObjectField::ENUM, RV_TelemetryPortElemNames, RV_TelemetryPortEnumOptions, QString("")));
    QStringList RV_GPSPortElemNames;
    RV_GPSPortElemNames.append("0");
    QStringList RV_GPSPortEnumOptions;
    RV_GPSPortEnumOptions.append("Disabled");
    RV_GPSPortEnumOptions.append("Telemetry");
    RV_GPSPortEnumOptions.append("GPS");
    RV_GPSPortEnumOptions.append("ComAux");
    RV_GPSPortEnumOptions.append("ComBridge");
    fields.append( new UAVObjectField(QString("RV_GPSPort"), tr(""), QString("function"), UAVObjectField::ENUM, RV_GPSPortElemNames, RV_GPSPortEnumOptions, QString("")));
    QStringList RM_RcvrPortElemNames;
    RM_RcvrPortElemNames.append("0");
    QStringList RM_RcvrPortEnumOptions;
    RM_RcvrPortEnumOptions.append("Disabled");
    RM_RcvrPortEnumOptions.append("PWM");
    RM_RcvrPortEnumOptions.append("PPM");
    RM_RcvrPortEnumOptions.append("PPM+PWM");
    RM_RcvrPortEnumOptions.append("PPM+Telemetry");
    RM_RcvrPortEnumOptions.append("PPM+Outputs");
    RM_RcvrPortEnumOptions.append("Outputs");
    RM_RcvrPortEnumOptions.append("Telemetry");
    fields.append( new UAVObjectField(QString("RM_RcvrPort"), tr(""), QString("function"), UAVObjectField::ENUM, RM_RcvrPortElemNames, RM_RcvrPortEnumOptions, QString("")));
    QStringList RM_MainPortElemNames;
    RM_MainPortElemNames.append("0");
    QStringList RM_MainPortEnumOptions;
    RM_MainPortEnumOptions.append("Disabled");
    RM_MainPortEnumOptions.append("Telemetry");
    RM_MainPortEnumOptions.append("GPS");
    RM_MainPortEnumOptions.append("S.Bus");
    RM_MainPortEnumOptions.append("DSM");
    RM_MainPortEnumOptions.append("DebugConsole");
    RM_MainPortEnumOptions.append("ComBridge");
    RM_MainPortEnumOptions.append("OsdHk");
    fields.append( new UAVObjectField(QString("RM_MainPort"), tr(""), QString("function"), UAVObjectField::ENUM, RM_MainPortElemNames, RM_MainPortEnumOptions, QString("")));
    QStringList RM_FlexiPortElemNames;
    RM_FlexiPortElemNames.append("0");
    QStringList RM_FlexiPortEnumOptions;
    RM_FlexiPortEnumOptions.append("Disabled");
    RM_FlexiPortEnumOptions.append("Telemetry");
    RM_FlexiPortEnumOptions.append("GPS");
    RM_FlexiPortEnumOptions.append("I2C");
    RM_FlexiPortEnumOptions.append("DSM");
    RM_FlexiPortEnumOptions.append("DebugConsole");
    RM_FlexiPortEnumOptions.append("ComBridge");
    RM_FlexiPortEnumOptions.append("OsdHk");
    fields.append( new UAVObjectField(QString("RM_FlexiPort"), tr(""), QString("function"), UAVObjectField::ENUM, RM_FlexiPortElemNames, RM_FlexiPortEnumOptions, QString("")));
    QStringList TelemetrySpeedElemNames;
    TelemetrySpeedElemNames.append("0");
    QStringList TelemetrySpeedEnumOptions;
    TelemetrySpeedEnumOptions.append("2400");
    TelemetrySpeedEnumOptions.append("4800");
    TelemetrySpeedEnumOptions.append("9600");
    TelemetrySpeedEnumOptions.append("19200");
    TelemetrySpeedEnumOptions.append("38400");
    TelemetrySpeedEnumOptions.append("57600");
    TelemetrySpeedEnumOptions.append("115200");
    fields.append( new UAVObjectField(QString("TelemetrySpeed"), tr(""), QString("bps"), UAVObjectField::ENUM, TelemetrySpeedElemNames, TelemetrySpeedEnumOptions, QString("")));
    QStringList GPSSpeedElemNames;
    GPSSpeedElemNames.append("0");
    QStringList GPSSpeedEnumOptions;
    GPSSpeedEnumOptions.append("2400");
    GPSSpeedEnumOptions.append("4800");
    GPSSpeedEnumOptions.append("9600");
    GPSSpeedEnumOptions.append("19200");
    GPSSpeedEnumOptions.append("38400");
    GPSSpeedEnumOptions.append("57600");
    GPSSpeedEnumOptions.append("115200");
    GPSSpeedEnumOptions.append("230400");
    fields.append( new UAVObjectField(QString("GPSSpeed"), tr(""), QString("bps"), UAVObjectField::ENUM, GPSSpeedElemNames, GPSSpeedEnumOptions, QString("")));
    QStringList ComUsbBridgeSpeedElemNames;
    ComUsbBridgeSpeedElemNames.append("0");
    QStringList ComUsbBridgeSpeedEnumOptions;
    ComUsbBridgeSpeedEnumOptions.append("2400");
    ComUsbBridgeSpeedEnumOptions.append("4800");
    ComUsbBridgeSpeedEnumOptions.append("9600");
    ComUsbBridgeSpeedEnumOptions.append("19200");
    ComUsbBridgeSpeedEnumOptions.append("38400");
    ComUsbBridgeSpeedEnumOptions.append("57600");
    ComUsbBridgeSpeedEnumOptions.append("115200");
    fields.append( new UAVObjectField(QString("ComUsbBridgeSpeed"), tr(""), QString("bps"), UAVObjectField::ENUM, ComUsbBridgeSpeedElemNames, ComUsbBridgeSpeedEnumOptions, QString("")));
    QStringList USB_HIDPortElemNames;
    USB_HIDPortElemNames.append("0");
    QStringList USB_HIDPortEnumOptions;
    USB_HIDPortEnumOptions.append("USBTelemetry");
    USB_HIDPortEnumOptions.append("RCTransmitter");
    USB_HIDPortEnumOptions.append("Disabled");
    fields.append( new UAVObjectField(QString("USB_HIDPort"), tr(""), QString("function"), UAVObjectField::ENUM, USB_HIDPortElemNames, USB_HIDPortEnumOptions, QString("")));
    QStringList USB_VCPPortElemNames;
    USB_VCPPortElemNames.append("0");
    QStringList USB_VCPPortEnumOptions;
    USB_VCPPortEnumOptions.append("USBTelemetry");
    USB_VCPPortEnumOptions.append("ComBridge");
    USB_VCPPortEnumOptions.append("DebugConsole");
    USB_VCPPortEnumOptions.append("Disabled");
    fields.append( new UAVObjectField(QString("USB_VCPPort"), tr(""), QString("function"), UAVObjectField::ENUM, USB_VCPPortElemNames, USB_VCPPortEnumOptions, QString("")));
    QStringList OptionalModulesElemNames;
    OptionalModulesElemNames.append("CameraStab");
    OptionalModulesElemNames.append("GPS");
    OptionalModulesElemNames.append("Fault");
    OptionalModulesElemNames.append("Altitude");
    OptionalModulesElemNames.append("Airspeed");
    OptionalModulesElemNames.append("TxPID");
    OptionalModulesElemNames.append("Battery");
    OptionalModulesElemNames.append("Overo");
    OptionalModulesElemNames.append("MagBaro");
    OptionalModulesElemNames.append("OsdHk");
    QStringList OptionalModulesEnumOptions;
    OptionalModulesEnumOptions.append("Disabled");
    OptionalModulesEnumOptions.append("Enabled");
    fields.append( new UAVObjectField(QString("OptionalModules"), tr(""), QString(""), UAVObjectField::ENUM, OptionalModulesElemNames, OptionalModulesEnumOptions, QString("")));
    QStringList ADCRoutingElemNames;
    ADCRoutingElemNames.append("adc0");
    ADCRoutingElemNames.append("adc1");
    ADCRoutingElemNames.append("adc2");
    ADCRoutingElemNames.append("adc3");
    QStringList ADCRoutingEnumOptions;
    ADCRoutingEnumOptions.append("Disabled");
    ADCRoutingEnumOptions.append("BatteryVoltage");
    ADCRoutingEnumOptions.append("BatteryCurrent");
    ADCRoutingEnumOptions.append("AnalogAirspeed");
    ADCRoutingEnumOptions.append("Generic");
    fields.append( new UAVObjectField(QString("ADCRouting"), tr(""), QString(""), UAVObjectField::ENUM, ADCRoutingElemNames, ADCRoutingEnumOptions, QString("")));
    QStringList DSMxBindElemNames;
    DSMxBindElemNames.append("0");
    fields.append( new UAVObjectField(QString("DSMxBind"), tr(""), QString(""), UAVObjectField::UINT8, DSMxBindElemNames, QStringList(), QString("")));
    QStringList WS2811LED_OutElemNames;
    WS2811LED_OutElemNames.append("0");
    QStringList WS2811LED_OutEnumOptions;
    WS2811LED_OutEnumOptions.append("ServoOut1");
    WS2811LED_OutEnumOptions.append("ServoOut2");
    WS2811LED_OutEnumOptions.append("ServoOut3");
    WS2811LED_OutEnumOptions.append("ServoOut4");
    WS2811LED_OutEnumOptions.append("ServoOut5");
    WS2811LED_OutEnumOptions.append("ServoOut6");
    WS2811LED_OutEnumOptions.append("FlexiIOPin3");
    WS2811LED_OutEnumOptions.append("FlexiIOPin4");
    WS2811LED_OutEnumOptions.append("Disabled");
    fields.append( new UAVObjectField(QString("WS2811LED_Out"), tr(""), QString(""), UAVObjectField::ENUM, WS2811LED_OutElemNames, WS2811LED_OutEnumOptions, QString("")));

    // Initialize object
    initializeFields(fields, (quint8 *)&data, NUMBYTES);
    // Set the default field values
    setDefaultFieldValues();
    // Set the object description
    setDescription(DESCRIPTION);

    // Set the Category of this object type
    setCategory(CATEGORY);

    connect(this, SIGNAL(objectUpdated(UAVObject *)), SLOT(emitNotifications()));
}

/**
 * Get the default metadata for this object
 */
UAVObject::Metadata HwSettings::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        1 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        1 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_ONCHANGE << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_ONCHANGE << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_LOGGING_UPDATE_MODE_SHIFT;
    metadata.flightTelemetryUpdatePeriod = 0;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void HwSettings::setDefaultFieldValues()
{
    data.CC_RcvrPort = 1;
    data.CC_MainPort = 1;
    data.CC_FlexiPort = 0;
    data.RV_RcvrPort = 1;
    data.RV_AuxPort = 0;
    data.RV_AuxSBusPort = 0;
    data.RV_FlexiPort = 0;
    data.RV_TelemetryPort = 1;
    data.RV_GPSPort = 2;
    data.RM_RcvrPort = 1;
    data.RM_MainPort = 0;
    data.RM_FlexiPort = 0;
    data.TelemetrySpeed = 5;
    data.GPSSpeed = 5;
    data.ComUsbBridgeSpeed = 5;
    data.USB_HIDPort = 0;
    data.USB_VCPPort = 3;
    data.OptionalModules[0] = 0;
    data.OptionalModules[1] = 0;
    data.OptionalModules[2] = 0;
    data.OptionalModules[3] = 0;
    data.OptionalModules[4] = 0;
    data.OptionalModules[5] = 0;
    data.OptionalModules[6] = 0;
    data.OptionalModules[7] = 0;
    data.OptionalModules[8] = 0;
    data.OptionalModules[9] = 0;
    data.ADCRouting[0] = 0;
    data.ADCRouting[1] = 0;
    data.ADCRouting[2] = 0;
    data.ADCRouting[3] = 0;
    data.DSMxBind = 0;
    data.WS2811LED_Out = 8;

}

/**
 * Get the object data fields
 */
HwSettings::DataFields HwSettings::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void HwSettings::setData(const DataFields& data)
{
    QMutexLocker locker(mutex);
    // Get metadata
    Metadata mdata = getMetadata();
    // Update object if the access mode permits
    if (UAVObject::GetGcsAccess(mdata) == ACCESS_READWRITE) {
        this->data = data;
        emit objectUpdatedAuto(this); // trigger object updated event
        emit objectUpdated(this);
    }
}

void HwSettings::emitNotifications()
{
            //if (data.CC_RcvrPort != oldData.CC_RcvrPort)
            emit CC_RcvrPortChanged(data.CC_RcvrPort);
        //if (data.CC_MainPort != oldData.CC_MainPort)
            emit CC_MainPortChanged(data.CC_MainPort);
        //if (data.CC_FlexiPort != oldData.CC_FlexiPort)
            emit CC_FlexiPortChanged(data.CC_FlexiPort);
        //if (data.RV_RcvrPort != oldData.RV_RcvrPort)
            emit RV_RcvrPortChanged(data.RV_RcvrPort);
        //if (data.RV_AuxPort != oldData.RV_AuxPort)
            emit RV_AuxPortChanged(data.RV_AuxPort);
        //if (data.RV_AuxSBusPort != oldData.RV_AuxSBusPort)
            emit RV_AuxSBusPortChanged(data.RV_AuxSBusPort);
        //if (data.RV_FlexiPort != oldData.RV_FlexiPort)
            emit RV_FlexiPortChanged(data.RV_FlexiPort);
        //if (data.RV_TelemetryPort != oldData.RV_TelemetryPort)
            emit RV_TelemetryPortChanged(data.RV_TelemetryPort);
        //if (data.RV_GPSPort != oldData.RV_GPSPort)
            emit RV_GPSPortChanged(data.RV_GPSPort);
        //if (data.RM_RcvrPort != oldData.RM_RcvrPort)
            emit RM_RcvrPortChanged(data.RM_RcvrPort);
        //if (data.RM_MainPort != oldData.RM_MainPort)
            emit RM_MainPortChanged(data.RM_MainPort);
        //if (data.RM_FlexiPort != oldData.RM_FlexiPort)
            emit RM_FlexiPortChanged(data.RM_FlexiPort);
        //if (data.TelemetrySpeed != oldData.TelemetrySpeed)
            emit TelemetrySpeedChanged(data.TelemetrySpeed);
        //if (data.GPSSpeed != oldData.GPSSpeed)
            emit GPSSpeedChanged(data.GPSSpeed);
        //if (data.ComUsbBridgeSpeed != oldData.ComUsbBridgeSpeed)
            emit ComUsbBridgeSpeedChanged(data.ComUsbBridgeSpeed);
        //if (data.USB_HIDPort != oldData.USB_HIDPort)
            emit USB_HIDPortChanged(data.USB_HIDPort);
        //if (data.USB_VCPPort != oldData.USB_VCPPort)
            emit USB_VCPPortChanged(data.USB_VCPPort);
        //if (data.OptionalModules[0] != oldData.OptionalModules[0])
            emit OptionalModules_CameraStabChanged(data.OptionalModules[0]);
        //if (data.OptionalModules[1] != oldData.OptionalModules[1])
            emit OptionalModules_GPSChanged(data.OptionalModules[1]);
        //if (data.OptionalModules[2] != oldData.OptionalModules[2])
            emit OptionalModules_FaultChanged(data.OptionalModules[2]);
        //if (data.OptionalModules[3] != oldData.OptionalModules[3])
            emit OptionalModules_AltitudeChanged(data.OptionalModules[3]);
        //if (data.OptionalModules[4] != oldData.OptionalModules[4])
            emit OptionalModules_AirspeedChanged(data.OptionalModules[4]);
        //if (data.OptionalModules[5] != oldData.OptionalModules[5])
            emit OptionalModules_TxPIDChanged(data.OptionalModules[5]);
        //if (data.OptionalModules[6] != oldData.OptionalModules[6])
            emit OptionalModules_BatteryChanged(data.OptionalModules[6]);
        //if (data.OptionalModules[7] != oldData.OptionalModules[7])
            emit OptionalModules_OveroChanged(data.OptionalModules[7]);
        //if (data.OptionalModules[8] != oldData.OptionalModules[8])
            emit OptionalModules_MagBaroChanged(data.OptionalModules[8]);
        //if (data.OptionalModules[9] != oldData.OptionalModules[9])
            emit OptionalModules_OsdHkChanged(data.OptionalModules[9]);
        //if (data.ADCRouting[0] != oldData.ADCRouting[0])
            emit ADCRouting_adc0Changed(data.ADCRouting[0]);
        //if (data.ADCRouting[1] != oldData.ADCRouting[1])
            emit ADCRouting_adc1Changed(data.ADCRouting[1]);
        //if (data.ADCRouting[2] != oldData.ADCRouting[2])
            emit ADCRouting_adc2Changed(data.ADCRouting[2]);
        //if (data.ADCRouting[3] != oldData.ADCRouting[3])
            emit ADCRouting_adc3Changed(data.ADCRouting[3]);
        //if (data.DSMxBind != oldData.DSMxBind)
            emit DSMxBindChanged(data.DSMxBind);
        //if (data.WS2811LED_Out != oldData.WS2811LED_Out)
            emit WS2811LED_OutChanged(data.WS2811LED_Out);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *HwSettings::clone(quint32 instID)
{
    HwSettings *obj = new HwSettings();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *HwSettings::dirtyClone()
{
    HwSettings *obj = new HwSettings();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
HwSettings *HwSettings::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<HwSettings *>(objMngr->getObject(HwSettings::OBJID, instID));
}

quint8 HwSettings::getCC_RcvrPort() const
{
   QMutexLocker locker(mutex);
   return data.CC_RcvrPort;
}
void HwSettings::setCC_RcvrPort(quint8 value)
{
   mutex->lock();
   bool changed = data.CC_RcvrPort != value;
   data.CC_RcvrPort = value;
   mutex->unlock();
   if (changed) emit CC_RcvrPortChanged(value);
}

quint8 HwSettings::getCC_MainPort() const
{
   QMutexLocker locker(mutex);
   return data.CC_MainPort;
}
void HwSettings::setCC_MainPort(quint8 value)
{
   mutex->lock();
   bool changed = data.CC_MainPort != value;
   data.CC_MainPort = value;
   mutex->unlock();
   if (changed) emit CC_MainPortChanged(value);
}

quint8 HwSettings::getCC_FlexiPort() const
{
   QMutexLocker locker(mutex);
   return data.CC_FlexiPort;
}
void HwSettings::setCC_FlexiPort(quint8 value)
{
   mutex->lock();
   bool changed = data.CC_FlexiPort != value;
   data.CC_FlexiPort = value;
   mutex->unlock();
   if (changed) emit CC_FlexiPortChanged(value);
}

quint8 HwSettings::getRV_RcvrPort() const
{
   QMutexLocker locker(mutex);
   return data.RV_RcvrPort;
}
void HwSettings::setRV_RcvrPort(quint8 value)
{
   mutex->lock();
   bool changed = data.RV_RcvrPort != value;
   data.RV_RcvrPort = value;
   mutex->unlock();
   if (changed) emit RV_RcvrPortChanged(value);
}

quint8 HwSettings::getRV_AuxPort() const
{
   QMutexLocker locker(mutex);
   return data.RV_AuxPort;
}
void HwSettings::setRV_AuxPort(quint8 value)
{
   mutex->lock();
   bool changed = data.RV_AuxPort != value;
   data.RV_AuxPort = value;
   mutex->unlock();
   if (changed) emit RV_AuxPortChanged(value);
}

quint8 HwSettings::getRV_AuxSBusPort() const
{
   QMutexLocker locker(mutex);
   return data.RV_AuxSBusPort;
}
void HwSettings::setRV_AuxSBusPort(quint8 value)
{
   mutex->lock();
   bool changed = data.RV_AuxSBusPort != value;
   data.RV_AuxSBusPort = value;
   mutex->unlock();
   if (changed) emit RV_AuxSBusPortChanged(value);
}

quint8 HwSettings::getRV_FlexiPort() const
{
   QMutexLocker locker(mutex);
   return data.RV_FlexiPort;
}
void HwSettings::setRV_FlexiPort(quint8 value)
{
   mutex->lock();
   bool changed = data.RV_FlexiPort != value;
   data.RV_FlexiPort = value;
   mutex->unlock();
   if (changed) emit RV_FlexiPortChanged(value);
}

quint8 HwSettings::getRV_TelemetryPort() const
{
   QMutexLocker locker(mutex);
   return data.RV_TelemetryPort;
}
void HwSettings::setRV_TelemetryPort(quint8 value)
{
   mutex->lock();
   bool changed = data.RV_TelemetryPort != value;
   data.RV_TelemetryPort = value;
   mutex->unlock();
   if (changed) emit RV_TelemetryPortChanged(value);
}

quint8 HwSettings::getRV_GPSPort() const
{
   QMutexLocker locker(mutex);
   return data.RV_GPSPort;
}
void HwSettings::setRV_GPSPort(quint8 value)
{
   mutex->lock();
   bool changed = data.RV_GPSPort != value;
   data.RV_GPSPort = value;
   mutex->unlock();
   if (changed) emit RV_GPSPortChanged(value);
}

quint8 HwSettings::getRM_RcvrPort() const
{
   QMutexLocker locker(mutex);
   return data.RM_RcvrPort;
}
void HwSettings::setRM_RcvrPort(quint8 value)
{
   mutex->lock();
   bool changed = data.RM_RcvrPort != value;
   data.RM_RcvrPort = value;
   mutex->unlock();
   if (changed) emit RM_RcvrPortChanged(value);
}

quint8 HwSettings::getRM_MainPort() const
{
   QMutexLocker locker(mutex);
   return data.RM_MainPort;
}
void HwSettings::setRM_MainPort(quint8 value)
{
   mutex->lock();
   bool changed = data.RM_MainPort != value;
   data.RM_MainPort = value;
   mutex->unlock();
   if (changed) emit RM_MainPortChanged(value);
}

quint8 HwSettings::getRM_FlexiPort() const
{
   QMutexLocker locker(mutex);
   return data.RM_FlexiPort;
}
void HwSettings::setRM_FlexiPort(quint8 value)
{
   mutex->lock();
   bool changed = data.RM_FlexiPort != value;
   data.RM_FlexiPort = value;
   mutex->unlock();
   if (changed) emit RM_FlexiPortChanged(value);
}

quint8 HwSettings::getTelemetrySpeed() const
{
   QMutexLocker locker(mutex);
   return data.TelemetrySpeed;
}
void HwSettings::setTelemetrySpeed(quint8 value)
{
   mutex->lock();
   bool changed = data.TelemetrySpeed != value;
   data.TelemetrySpeed = value;
   mutex->unlock();
   if (changed) emit TelemetrySpeedChanged(value);
}

quint8 HwSettings::getGPSSpeed() const
{
   QMutexLocker locker(mutex);
   return data.GPSSpeed;
}
void HwSettings::setGPSSpeed(quint8 value)
{
   mutex->lock();
   bool changed = data.GPSSpeed != value;
   data.GPSSpeed = value;
   mutex->unlock();
   if (changed) emit GPSSpeedChanged(value);
}

quint8 HwSettings::getComUsbBridgeSpeed() const
{
   QMutexLocker locker(mutex);
   return data.ComUsbBridgeSpeed;
}
void HwSettings::setComUsbBridgeSpeed(quint8 value)
{
   mutex->lock();
   bool changed = data.ComUsbBridgeSpeed != value;
   data.ComUsbBridgeSpeed = value;
   mutex->unlock();
   if (changed) emit ComUsbBridgeSpeedChanged(value);
}

quint8 HwSettings::getUSB_HIDPort() const
{
   QMutexLocker locker(mutex);
   return data.USB_HIDPort;
}
void HwSettings::setUSB_HIDPort(quint8 value)
{
   mutex->lock();
   bool changed = data.USB_HIDPort != value;
   data.USB_HIDPort = value;
   mutex->unlock();
   if (changed) emit USB_HIDPortChanged(value);
}

quint8 HwSettings::getUSB_VCPPort() const
{
   QMutexLocker locker(mutex);
   return data.USB_VCPPort;
}
void HwSettings::setUSB_VCPPort(quint8 value)
{
   mutex->lock();
   bool changed = data.USB_VCPPort != value;
   data.USB_VCPPort = value;
   mutex->unlock();
   if (changed) emit USB_VCPPortChanged(value);
}

quint8 HwSettings::getOptionalModules(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.OptionalModules[index];
}
void HwSettings::setOptionalModules(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.OptionalModules[index] != value;
   data.OptionalModules[index] = value;
   mutex->unlock();
   if (changed) emit OptionalModulesChanged(index,value);
}

quint8 HwSettings::getOptionalModules_CameraStab() const
{
   QMutexLocker locker(mutex);
   return data.OptionalModules[0];
}
void HwSettings::setOptionalModules_CameraStab(quint8 value)
{
   mutex->lock();
   bool changed = data.OptionalModules[0] != value;
   data.OptionalModules[0] = value;
   mutex->unlock();
   if (changed) emit OptionalModules_CameraStabChanged(value);
}

quint8 HwSettings::getOptionalModules_GPS() const
{
   QMutexLocker locker(mutex);
   return data.OptionalModules[1];
}
void HwSettings::setOptionalModules_GPS(quint8 value)
{
   mutex->lock();
   bool changed = data.OptionalModules[1] != value;
   data.OptionalModules[1] = value;
   mutex->unlock();
   if (changed) emit OptionalModules_GPSChanged(value);
}

quint8 HwSettings::getOptionalModules_Fault() const
{
   QMutexLocker locker(mutex);
   return data.OptionalModules[2];
}
void HwSettings::setOptionalModules_Fault(quint8 value)
{
   mutex->lock();
   bool changed = data.OptionalModules[2] != value;
   data.OptionalModules[2] = value;
   mutex->unlock();
   if (changed) emit OptionalModules_FaultChanged(value);
}

quint8 HwSettings::getOptionalModules_Altitude() const
{
   QMutexLocker locker(mutex);
   return data.OptionalModules[3];
}
void HwSettings::setOptionalModules_Altitude(quint8 value)
{
   mutex->lock();
   bool changed = data.OptionalModules[3] != value;
   data.OptionalModules[3] = value;
   mutex->unlock();
   if (changed) emit OptionalModules_AltitudeChanged(value);
}

quint8 HwSettings::getOptionalModules_Airspeed() const
{
   QMutexLocker locker(mutex);
   return data.OptionalModules[4];
}
void HwSettings::setOptionalModules_Airspeed(quint8 value)
{
   mutex->lock();
   bool changed = data.OptionalModules[4] != value;
   data.OptionalModules[4] = value;
   mutex->unlock();
   if (changed) emit OptionalModules_AirspeedChanged(value);
}

quint8 HwSettings::getOptionalModules_TxPID() const
{
   QMutexLocker locker(mutex);
   return data.OptionalModules[5];
}
void HwSettings::setOptionalModules_TxPID(quint8 value)
{
   mutex->lock();
   bool changed = data.OptionalModules[5] != value;
   data.OptionalModules[5] = value;
   mutex->unlock();
   if (changed) emit OptionalModules_TxPIDChanged(value);
}

quint8 HwSettings::getOptionalModules_Battery() const
{
   QMutexLocker locker(mutex);
   return data.OptionalModules[6];
}
void HwSettings::setOptionalModules_Battery(quint8 value)
{
   mutex->lock();
   bool changed = data.OptionalModules[6] != value;
   data.OptionalModules[6] = value;
   mutex->unlock();
   if (changed) emit OptionalModules_BatteryChanged(value);
}

quint8 HwSettings::getOptionalModules_Overo() const
{
   QMutexLocker locker(mutex);
   return data.OptionalModules[7];
}
void HwSettings::setOptionalModules_Overo(quint8 value)
{
   mutex->lock();
   bool changed = data.OptionalModules[7] != value;
   data.OptionalModules[7] = value;
   mutex->unlock();
   if (changed) emit OptionalModules_OveroChanged(value);
}

quint8 HwSettings::getOptionalModules_MagBaro() const
{
   QMutexLocker locker(mutex);
   return data.OptionalModules[8];
}
void HwSettings::setOptionalModules_MagBaro(quint8 value)
{
   mutex->lock();
   bool changed = data.OptionalModules[8] != value;
   data.OptionalModules[8] = value;
   mutex->unlock();
   if (changed) emit OptionalModules_MagBaroChanged(value);
}

quint8 HwSettings::getOptionalModules_OsdHk() const
{
   QMutexLocker locker(mutex);
   return data.OptionalModules[9];
}
void HwSettings::setOptionalModules_OsdHk(quint8 value)
{
   mutex->lock();
   bool changed = data.OptionalModules[9] != value;
   data.OptionalModules[9] = value;
   mutex->unlock();
   if (changed) emit OptionalModules_OsdHkChanged(value);
}

quint8 HwSettings::getADCRouting(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.ADCRouting[index];
}
void HwSettings::setADCRouting(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.ADCRouting[index] != value;
   data.ADCRouting[index] = value;
   mutex->unlock();
   if (changed) emit ADCRoutingChanged(index,value);
}

quint8 HwSettings::getADCRouting_adc0() const
{
   QMutexLocker locker(mutex);
   return data.ADCRouting[0];
}
void HwSettings::setADCRouting_adc0(quint8 value)
{
   mutex->lock();
   bool changed = data.ADCRouting[0] != value;
   data.ADCRouting[0] = value;
   mutex->unlock();
   if (changed) emit ADCRouting_adc0Changed(value);
}

quint8 HwSettings::getADCRouting_adc1() const
{
   QMutexLocker locker(mutex);
   return data.ADCRouting[1];
}
void HwSettings::setADCRouting_adc1(quint8 value)
{
   mutex->lock();
   bool changed = data.ADCRouting[1] != value;
   data.ADCRouting[1] = value;
   mutex->unlock();
   if (changed) emit ADCRouting_adc1Changed(value);
}

quint8 HwSettings::getADCRouting_adc2() const
{
   QMutexLocker locker(mutex);
   return data.ADCRouting[2];
}
void HwSettings::setADCRouting_adc2(quint8 value)
{
   mutex->lock();
   bool changed = data.ADCRouting[2] != value;
   data.ADCRouting[2] = value;
   mutex->unlock();
   if (changed) emit ADCRouting_adc2Changed(value);
}

quint8 HwSettings::getADCRouting_adc3() const
{
   QMutexLocker locker(mutex);
   return data.ADCRouting[3];
}
void HwSettings::setADCRouting_adc3(quint8 value)
{
   mutex->lock();
   bool changed = data.ADCRouting[3] != value;
   data.ADCRouting[3] = value;
   mutex->unlock();
   if (changed) emit ADCRouting_adc3Changed(value);
}

quint8 HwSettings::getDSMxBind() const
{
   QMutexLocker locker(mutex);
   return data.DSMxBind;
}
void HwSettings::setDSMxBind(quint8 value)
{
   mutex->lock();
   bool changed = data.DSMxBind != value;
   data.DSMxBind = value;
   mutex->unlock();
   if (changed) emit DSMxBindChanged(value);
}

quint8 HwSettings::getWS2811LED_Out() const
{
   QMutexLocker locker(mutex);
   return data.WS2811LED_Out;
}
void HwSettings::setWS2811LED_Out(quint8 value)
{
   mutex->lock();
   bool changed = data.WS2811LED_Out != value;
   data.WS2811LED_Out = value;
   mutex->unlock();
   if (changed) emit WS2811LED_OutChanged(value);
}


