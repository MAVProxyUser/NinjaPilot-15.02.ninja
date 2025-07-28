/****************************************************************************
** Meta object code from reading C++ file 'hwsettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/hwsettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hwsettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HwSettings_t {
    QByteArrayData data[143];
    char stringdata0[2734];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HwSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HwSettings_t qt_meta_stringdata_HwSettings = {
    {
QT_MOC_LITERAL(0, 0, 10), // "HwSettings"
QT_MOC_LITERAL(1, 11, 18), // "CC_RcvrPortChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 5), // "value"
QT_MOC_LITERAL(4, 37, 18), // "CC_MainPortChanged"
QT_MOC_LITERAL(5, 56, 19), // "CC_FlexiPortChanged"
QT_MOC_LITERAL(6, 76, 18), // "RV_RcvrPortChanged"
QT_MOC_LITERAL(7, 95, 17), // "RV_AuxPortChanged"
QT_MOC_LITERAL(8, 113, 21), // "RV_AuxSBusPortChanged"
QT_MOC_LITERAL(9, 135, 19), // "RV_FlexiPortChanged"
QT_MOC_LITERAL(10, 155, 23), // "RV_TelemetryPortChanged"
QT_MOC_LITERAL(11, 179, 17), // "RV_GPSPortChanged"
QT_MOC_LITERAL(12, 197, 18), // "RM_RcvrPortChanged"
QT_MOC_LITERAL(13, 216, 18), // "RM_MainPortChanged"
QT_MOC_LITERAL(14, 235, 19), // "RM_FlexiPortChanged"
QT_MOC_LITERAL(15, 255, 21), // "TelemetrySpeedChanged"
QT_MOC_LITERAL(16, 277, 15), // "GPSSpeedChanged"
QT_MOC_LITERAL(17, 293, 24), // "ComUsbBridgeSpeedChanged"
QT_MOC_LITERAL(18, 318, 18), // "USB_HIDPortChanged"
QT_MOC_LITERAL(19, 337, 18), // "USB_VCPPortChanged"
QT_MOC_LITERAL(20, 356, 22), // "OptionalModulesChanged"
QT_MOC_LITERAL(21, 379, 5), // "index"
QT_MOC_LITERAL(22, 385, 33), // "OptionalModules_CameraStabCha..."
QT_MOC_LITERAL(23, 419, 26), // "OptionalModules_GPSChanged"
QT_MOC_LITERAL(24, 446, 28), // "OptionalModules_FaultChanged"
QT_MOC_LITERAL(25, 475, 31), // "OptionalModules_AltitudeChanged"
QT_MOC_LITERAL(26, 507, 31), // "OptionalModules_AirspeedChanged"
QT_MOC_LITERAL(27, 539, 28), // "OptionalModules_TxPIDChanged"
QT_MOC_LITERAL(28, 568, 30), // "OptionalModules_BatteryChanged"
QT_MOC_LITERAL(29, 599, 28), // "OptionalModules_OveroChanged"
QT_MOC_LITERAL(30, 628, 30), // "OptionalModules_MagBaroChanged"
QT_MOC_LITERAL(31, 659, 28), // "OptionalModules_OsdHkChanged"
QT_MOC_LITERAL(32, 688, 17), // "ADCRoutingChanged"
QT_MOC_LITERAL(33, 706, 22), // "ADCRouting_adc0Changed"
QT_MOC_LITERAL(34, 729, 22), // "ADCRouting_adc1Changed"
QT_MOC_LITERAL(35, 752, 22), // "ADCRouting_adc2Changed"
QT_MOC_LITERAL(36, 775, 22), // "ADCRouting_adc3Changed"
QT_MOC_LITERAL(37, 798, 15), // "DSMxBindChanged"
QT_MOC_LITERAL(38, 814, 20), // "WS2811LED_OutChanged"
QT_MOC_LITERAL(39, 835, 14), // "setCC_RcvrPort"
QT_MOC_LITERAL(40, 850, 14), // "setCC_MainPort"
QT_MOC_LITERAL(41, 865, 15), // "setCC_FlexiPort"
QT_MOC_LITERAL(42, 881, 14), // "setRV_RcvrPort"
QT_MOC_LITERAL(43, 896, 13), // "setRV_AuxPort"
QT_MOC_LITERAL(44, 910, 17), // "setRV_AuxSBusPort"
QT_MOC_LITERAL(45, 928, 15), // "setRV_FlexiPort"
QT_MOC_LITERAL(46, 944, 19), // "setRV_TelemetryPort"
QT_MOC_LITERAL(47, 964, 13), // "setRV_GPSPort"
QT_MOC_LITERAL(48, 978, 14), // "setRM_RcvrPort"
QT_MOC_LITERAL(49, 993, 14), // "setRM_MainPort"
QT_MOC_LITERAL(50, 1008, 15), // "setRM_FlexiPort"
QT_MOC_LITERAL(51, 1024, 17), // "setTelemetrySpeed"
QT_MOC_LITERAL(52, 1042, 11), // "setGPSSpeed"
QT_MOC_LITERAL(53, 1054, 20), // "setComUsbBridgeSpeed"
QT_MOC_LITERAL(54, 1075, 14), // "setUSB_HIDPort"
QT_MOC_LITERAL(55, 1090, 14), // "setUSB_VCPPort"
QT_MOC_LITERAL(56, 1105, 18), // "setOptionalModules"
QT_MOC_LITERAL(57, 1124, 29), // "setOptionalModules_CameraStab"
QT_MOC_LITERAL(58, 1154, 22), // "setOptionalModules_GPS"
QT_MOC_LITERAL(59, 1177, 24), // "setOptionalModules_Fault"
QT_MOC_LITERAL(60, 1202, 27), // "setOptionalModules_Altitude"
QT_MOC_LITERAL(61, 1230, 27), // "setOptionalModules_Airspeed"
QT_MOC_LITERAL(62, 1258, 24), // "setOptionalModules_TxPID"
QT_MOC_LITERAL(63, 1283, 26), // "setOptionalModules_Battery"
QT_MOC_LITERAL(64, 1310, 24), // "setOptionalModules_Overo"
QT_MOC_LITERAL(65, 1335, 26), // "setOptionalModules_MagBaro"
QT_MOC_LITERAL(66, 1362, 24), // "setOptionalModules_OsdHk"
QT_MOC_LITERAL(67, 1387, 13), // "setADCRouting"
QT_MOC_LITERAL(68, 1401, 18), // "setADCRouting_adc0"
QT_MOC_LITERAL(69, 1420, 18), // "setADCRouting_adc1"
QT_MOC_LITERAL(70, 1439, 18), // "setADCRouting_adc2"
QT_MOC_LITERAL(71, 1458, 18), // "setADCRouting_adc3"
QT_MOC_LITERAL(72, 1477, 11), // "setDSMxBind"
QT_MOC_LITERAL(73, 1489, 16), // "setWS2811LED_Out"
QT_MOC_LITERAL(74, 1506, 17), // "emitNotifications"
QT_MOC_LITERAL(75, 1524, 14), // "getCC_RcvrPort"
QT_MOC_LITERAL(76, 1539, 14), // "getCC_MainPort"
QT_MOC_LITERAL(77, 1554, 15), // "getCC_FlexiPort"
QT_MOC_LITERAL(78, 1570, 14), // "getRV_RcvrPort"
QT_MOC_LITERAL(79, 1585, 13), // "getRV_AuxPort"
QT_MOC_LITERAL(80, 1599, 17), // "getRV_AuxSBusPort"
QT_MOC_LITERAL(81, 1617, 15), // "getRV_FlexiPort"
QT_MOC_LITERAL(82, 1633, 19), // "getRV_TelemetryPort"
QT_MOC_LITERAL(83, 1653, 13), // "getRV_GPSPort"
QT_MOC_LITERAL(84, 1667, 14), // "getRM_RcvrPort"
QT_MOC_LITERAL(85, 1682, 14), // "getRM_MainPort"
QT_MOC_LITERAL(86, 1697, 15), // "getRM_FlexiPort"
QT_MOC_LITERAL(87, 1713, 17), // "getTelemetrySpeed"
QT_MOC_LITERAL(88, 1731, 11), // "getGPSSpeed"
QT_MOC_LITERAL(89, 1743, 20), // "getComUsbBridgeSpeed"
QT_MOC_LITERAL(90, 1764, 14), // "getUSB_HIDPort"
QT_MOC_LITERAL(91, 1779, 14), // "getUSB_VCPPort"
QT_MOC_LITERAL(92, 1794, 18), // "getOptionalModules"
QT_MOC_LITERAL(93, 1813, 29), // "getOptionalModules_CameraStab"
QT_MOC_LITERAL(94, 1843, 22), // "getOptionalModules_GPS"
QT_MOC_LITERAL(95, 1866, 24), // "getOptionalModules_Fault"
QT_MOC_LITERAL(96, 1891, 27), // "getOptionalModules_Altitude"
QT_MOC_LITERAL(97, 1919, 27), // "getOptionalModules_Airspeed"
QT_MOC_LITERAL(98, 1947, 24), // "getOptionalModules_TxPID"
QT_MOC_LITERAL(99, 1972, 26), // "getOptionalModules_Battery"
QT_MOC_LITERAL(100, 1999, 24), // "getOptionalModules_Overo"
QT_MOC_LITERAL(101, 2024, 26), // "getOptionalModules_MagBaro"
QT_MOC_LITERAL(102, 2051, 24), // "getOptionalModules_OsdHk"
QT_MOC_LITERAL(103, 2076, 13), // "getADCRouting"
QT_MOC_LITERAL(104, 2090, 18), // "getADCRouting_adc0"
QT_MOC_LITERAL(105, 2109, 18), // "getADCRouting_adc1"
QT_MOC_LITERAL(106, 2128, 18), // "getADCRouting_adc2"
QT_MOC_LITERAL(107, 2147, 18), // "getADCRouting_adc3"
QT_MOC_LITERAL(108, 2166, 11), // "getDSMxBind"
QT_MOC_LITERAL(109, 2178, 16), // "getWS2811LED_Out"
QT_MOC_LITERAL(110, 2195, 11), // "CC_RcvrPort"
QT_MOC_LITERAL(111, 2207, 11), // "CC_MainPort"
QT_MOC_LITERAL(112, 2219, 12), // "CC_FlexiPort"
QT_MOC_LITERAL(113, 2232, 11), // "RV_RcvrPort"
QT_MOC_LITERAL(114, 2244, 10), // "RV_AuxPort"
QT_MOC_LITERAL(115, 2255, 14), // "RV_AuxSBusPort"
QT_MOC_LITERAL(116, 2270, 12), // "RV_FlexiPort"
QT_MOC_LITERAL(117, 2283, 16), // "RV_TelemetryPort"
QT_MOC_LITERAL(118, 2300, 10), // "RV_GPSPort"
QT_MOC_LITERAL(119, 2311, 11), // "RM_RcvrPort"
QT_MOC_LITERAL(120, 2323, 11), // "RM_MainPort"
QT_MOC_LITERAL(121, 2335, 12), // "RM_FlexiPort"
QT_MOC_LITERAL(122, 2348, 14), // "TelemetrySpeed"
QT_MOC_LITERAL(123, 2363, 8), // "GPSSpeed"
QT_MOC_LITERAL(124, 2372, 17), // "ComUsbBridgeSpeed"
QT_MOC_LITERAL(125, 2390, 11), // "USB_HIDPort"
QT_MOC_LITERAL(126, 2402, 11), // "USB_VCPPort"
QT_MOC_LITERAL(127, 2414, 26), // "OptionalModules_CameraStab"
QT_MOC_LITERAL(128, 2441, 19), // "OptionalModules_GPS"
QT_MOC_LITERAL(129, 2461, 21), // "OptionalModules_Fault"
QT_MOC_LITERAL(130, 2483, 24), // "OptionalModules_Altitude"
QT_MOC_LITERAL(131, 2508, 24), // "OptionalModules_Airspeed"
QT_MOC_LITERAL(132, 2533, 21), // "OptionalModules_TxPID"
QT_MOC_LITERAL(133, 2555, 23), // "OptionalModules_Battery"
QT_MOC_LITERAL(134, 2579, 21), // "OptionalModules_Overo"
QT_MOC_LITERAL(135, 2601, 23), // "OptionalModules_MagBaro"
QT_MOC_LITERAL(136, 2625, 21), // "OptionalModules_OsdHk"
QT_MOC_LITERAL(137, 2647, 15), // "ADCRouting_adc0"
QT_MOC_LITERAL(138, 2663, 15), // "ADCRouting_adc1"
QT_MOC_LITERAL(139, 2679, 15), // "ADCRouting_adc2"
QT_MOC_LITERAL(140, 2695, 15), // "ADCRouting_adc3"
QT_MOC_LITERAL(141, 2711, 8), // "DSMxBind"
QT_MOC_LITERAL(142, 2720, 13) // "WS2811LED_Out"

    },
    "HwSettings\0CC_RcvrPortChanged\0\0value\0"
    "CC_MainPortChanged\0CC_FlexiPortChanged\0"
    "RV_RcvrPortChanged\0RV_AuxPortChanged\0"
    "RV_AuxSBusPortChanged\0RV_FlexiPortChanged\0"
    "RV_TelemetryPortChanged\0RV_GPSPortChanged\0"
    "RM_RcvrPortChanged\0RM_MainPortChanged\0"
    "RM_FlexiPortChanged\0TelemetrySpeedChanged\0"
    "GPSSpeedChanged\0ComUsbBridgeSpeedChanged\0"
    "USB_HIDPortChanged\0USB_VCPPortChanged\0"
    "OptionalModulesChanged\0index\0"
    "OptionalModules_CameraStabChanged\0"
    "OptionalModules_GPSChanged\0"
    "OptionalModules_FaultChanged\0"
    "OptionalModules_AltitudeChanged\0"
    "OptionalModules_AirspeedChanged\0"
    "OptionalModules_TxPIDChanged\0"
    "OptionalModules_BatteryChanged\0"
    "OptionalModules_OveroChanged\0"
    "OptionalModules_MagBaroChanged\0"
    "OptionalModules_OsdHkChanged\0"
    "ADCRoutingChanged\0ADCRouting_adc0Changed\0"
    "ADCRouting_adc1Changed\0ADCRouting_adc2Changed\0"
    "ADCRouting_adc3Changed\0DSMxBindChanged\0"
    "WS2811LED_OutChanged\0setCC_RcvrPort\0"
    "setCC_MainPort\0setCC_FlexiPort\0"
    "setRV_RcvrPort\0setRV_AuxPort\0"
    "setRV_AuxSBusPort\0setRV_FlexiPort\0"
    "setRV_TelemetryPort\0setRV_GPSPort\0"
    "setRM_RcvrPort\0setRM_MainPort\0"
    "setRM_FlexiPort\0setTelemetrySpeed\0"
    "setGPSSpeed\0setComUsbBridgeSpeed\0"
    "setUSB_HIDPort\0setUSB_VCPPort\0"
    "setOptionalModules\0setOptionalModules_CameraStab\0"
    "setOptionalModules_GPS\0setOptionalModules_Fault\0"
    "setOptionalModules_Altitude\0"
    "setOptionalModules_Airspeed\0"
    "setOptionalModules_TxPID\0"
    "setOptionalModules_Battery\0"
    "setOptionalModules_Overo\0"
    "setOptionalModules_MagBaro\0"
    "setOptionalModules_OsdHk\0setADCRouting\0"
    "setADCRouting_adc0\0setADCRouting_adc1\0"
    "setADCRouting_adc2\0setADCRouting_adc3\0"
    "setDSMxBind\0setWS2811LED_Out\0"
    "emitNotifications\0getCC_RcvrPort\0"
    "getCC_MainPort\0getCC_FlexiPort\0"
    "getRV_RcvrPort\0getRV_AuxPort\0"
    "getRV_AuxSBusPort\0getRV_FlexiPort\0"
    "getRV_TelemetryPort\0getRV_GPSPort\0"
    "getRM_RcvrPort\0getRM_MainPort\0"
    "getRM_FlexiPort\0getTelemetrySpeed\0"
    "getGPSSpeed\0getComUsbBridgeSpeed\0"
    "getUSB_HIDPort\0getUSB_VCPPort\0"
    "getOptionalModules\0getOptionalModules_CameraStab\0"
    "getOptionalModules_GPS\0getOptionalModules_Fault\0"
    "getOptionalModules_Altitude\0"
    "getOptionalModules_Airspeed\0"
    "getOptionalModules_TxPID\0"
    "getOptionalModules_Battery\0"
    "getOptionalModules_Overo\0"
    "getOptionalModules_MagBaro\0"
    "getOptionalModules_OsdHk\0getADCRouting\0"
    "getADCRouting_adc0\0getADCRouting_adc1\0"
    "getADCRouting_adc2\0getADCRouting_adc3\0"
    "getDSMxBind\0getWS2811LED_Out\0CC_RcvrPort\0"
    "CC_MainPort\0CC_FlexiPort\0RV_RcvrPort\0"
    "RV_AuxPort\0RV_AuxSBusPort\0RV_FlexiPort\0"
    "RV_TelemetryPort\0RV_GPSPort\0RM_RcvrPort\0"
    "RM_MainPort\0RM_FlexiPort\0TelemetrySpeed\0"
    "GPSSpeed\0ComUsbBridgeSpeed\0USB_HIDPort\0"
    "USB_VCPPort\0OptionalModules_CameraStab\0"
    "OptionalModules_GPS\0OptionalModules_Fault\0"
    "OptionalModules_Altitude\0"
    "OptionalModules_Airspeed\0OptionalModules_TxPID\0"
    "OptionalModules_Battery\0OptionalModules_Overo\0"
    "OptionalModules_MagBaro\0OptionalModules_OsdHk\0"
    "ADCRouting_adc0\0ADCRouting_adc1\0"
    "ADCRouting_adc2\0ADCRouting_adc3\0"
    "DSMxBind\0WS2811LED_Out"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HwSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     106,   14, // methods
      33,  802, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      35,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  544,    2, 0x06 /* Public */,
       4,    1,  547,    2, 0x06 /* Public */,
       5,    1,  550,    2, 0x06 /* Public */,
       6,    1,  553,    2, 0x06 /* Public */,
       7,    1,  556,    2, 0x06 /* Public */,
       8,    1,  559,    2, 0x06 /* Public */,
       9,    1,  562,    2, 0x06 /* Public */,
      10,    1,  565,    2, 0x06 /* Public */,
      11,    1,  568,    2, 0x06 /* Public */,
      12,    1,  571,    2, 0x06 /* Public */,
      13,    1,  574,    2, 0x06 /* Public */,
      14,    1,  577,    2, 0x06 /* Public */,
      15,    1,  580,    2, 0x06 /* Public */,
      16,    1,  583,    2, 0x06 /* Public */,
      17,    1,  586,    2, 0x06 /* Public */,
      18,    1,  589,    2, 0x06 /* Public */,
      19,    1,  592,    2, 0x06 /* Public */,
      20,    2,  595,    2, 0x06 /* Public */,
      22,    1,  600,    2, 0x06 /* Public */,
      23,    1,  603,    2, 0x06 /* Public */,
      24,    1,  606,    2, 0x06 /* Public */,
      25,    1,  609,    2, 0x06 /* Public */,
      26,    1,  612,    2, 0x06 /* Public */,
      27,    1,  615,    2, 0x06 /* Public */,
      28,    1,  618,    2, 0x06 /* Public */,
      29,    1,  621,    2, 0x06 /* Public */,
      30,    1,  624,    2, 0x06 /* Public */,
      31,    1,  627,    2, 0x06 /* Public */,
      32,    2,  630,    2, 0x06 /* Public */,
      33,    1,  635,    2, 0x06 /* Public */,
      34,    1,  638,    2, 0x06 /* Public */,
      35,    1,  641,    2, 0x06 /* Public */,
      36,    1,  644,    2, 0x06 /* Public */,
      37,    1,  647,    2, 0x06 /* Public */,
      38,    1,  650,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      39,    1,  653,    2, 0x0a /* Public */,
      40,    1,  656,    2, 0x0a /* Public */,
      41,    1,  659,    2, 0x0a /* Public */,
      42,    1,  662,    2, 0x0a /* Public */,
      43,    1,  665,    2, 0x0a /* Public */,
      44,    1,  668,    2, 0x0a /* Public */,
      45,    1,  671,    2, 0x0a /* Public */,
      46,    1,  674,    2, 0x0a /* Public */,
      47,    1,  677,    2, 0x0a /* Public */,
      48,    1,  680,    2, 0x0a /* Public */,
      49,    1,  683,    2, 0x0a /* Public */,
      50,    1,  686,    2, 0x0a /* Public */,
      51,    1,  689,    2, 0x0a /* Public */,
      52,    1,  692,    2, 0x0a /* Public */,
      53,    1,  695,    2, 0x0a /* Public */,
      54,    1,  698,    2, 0x0a /* Public */,
      55,    1,  701,    2, 0x0a /* Public */,
      56,    2,  704,    2, 0x0a /* Public */,
      57,    1,  709,    2, 0x0a /* Public */,
      58,    1,  712,    2, 0x0a /* Public */,
      59,    1,  715,    2, 0x0a /* Public */,
      60,    1,  718,    2, 0x0a /* Public */,
      61,    1,  721,    2, 0x0a /* Public */,
      62,    1,  724,    2, 0x0a /* Public */,
      63,    1,  727,    2, 0x0a /* Public */,
      64,    1,  730,    2, 0x0a /* Public */,
      65,    1,  733,    2, 0x0a /* Public */,
      66,    1,  736,    2, 0x0a /* Public */,
      67,    2,  739,    2, 0x0a /* Public */,
      68,    1,  744,    2, 0x0a /* Public */,
      69,    1,  747,    2, 0x0a /* Public */,
      70,    1,  750,    2, 0x0a /* Public */,
      71,    1,  753,    2, 0x0a /* Public */,
      72,    1,  756,    2, 0x0a /* Public */,
      73,    1,  759,    2, 0x0a /* Public */,
      74,    0,  762,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      75,    0,  763,    2, 0x02 /* Public */,
      76,    0,  764,    2, 0x02 /* Public */,
      77,    0,  765,    2, 0x02 /* Public */,
      78,    0,  766,    2, 0x02 /* Public */,
      79,    0,  767,    2, 0x02 /* Public */,
      80,    0,  768,    2, 0x02 /* Public */,
      81,    0,  769,    2, 0x02 /* Public */,
      82,    0,  770,    2, 0x02 /* Public */,
      83,    0,  771,    2, 0x02 /* Public */,
      84,    0,  772,    2, 0x02 /* Public */,
      85,    0,  773,    2, 0x02 /* Public */,
      86,    0,  774,    2, 0x02 /* Public */,
      87,    0,  775,    2, 0x02 /* Public */,
      88,    0,  776,    2, 0x02 /* Public */,
      89,    0,  777,    2, 0x02 /* Public */,
      90,    0,  778,    2, 0x02 /* Public */,
      91,    0,  779,    2, 0x02 /* Public */,
      92,    1,  780,    2, 0x02 /* Public */,
      93,    0,  783,    2, 0x02 /* Public */,
      94,    0,  784,    2, 0x02 /* Public */,
      95,    0,  785,    2, 0x02 /* Public */,
      96,    0,  786,    2, 0x02 /* Public */,
      97,    0,  787,    2, 0x02 /* Public */,
      98,    0,  788,    2, 0x02 /* Public */,
      99,    0,  789,    2, 0x02 /* Public */,
     100,    0,  790,    2, 0x02 /* Public */,
     101,    0,  791,    2, 0x02 /* Public */,
     102,    0,  792,    2, 0x02 /* Public */,
     103,    1,  793,    2, 0x02 /* Public */,
     104,    0,  796,    2, 0x02 /* Public */,
     105,    0,  797,    2, 0x02 /* Public */,
     106,    0,  798,    2, 0x02 /* Public */,
     107,    0,  799,    2, 0x02 /* Public */,
     108,    0,  800,    2, 0x02 /* Public */,
     109,    0,  801,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,   21,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,   21,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,   21,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,   21,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,   21,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,   21,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
     110, QMetaType::UChar, 0x00495103,
     111, QMetaType::UChar, 0x00495103,
     112, QMetaType::UChar, 0x00495103,
     113, QMetaType::UChar, 0x00495103,
     114, QMetaType::UChar, 0x00495103,
     115, QMetaType::UChar, 0x00495103,
     116, QMetaType::UChar, 0x00495103,
     117, QMetaType::UChar, 0x00495103,
     118, QMetaType::UChar, 0x00495103,
     119, QMetaType::UChar, 0x00495103,
     120, QMetaType::UChar, 0x00495103,
     121, QMetaType::UChar, 0x00495103,
     122, QMetaType::UChar, 0x00495103,
     123, QMetaType::UChar, 0x00495103,
     124, QMetaType::UChar, 0x00495103,
     125, QMetaType::UChar, 0x00495103,
     126, QMetaType::UChar, 0x00495103,
     127, QMetaType::UChar, 0x00495103,
     128, QMetaType::UChar, 0x00495103,
     129, QMetaType::UChar, 0x00495103,
     130, QMetaType::UChar, 0x00495103,
     131, QMetaType::UChar, 0x00495103,
     132, QMetaType::UChar, 0x00495103,
     133, QMetaType::UChar, 0x00495103,
     134, QMetaType::UChar, 0x00495103,
     135, QMetaType::UChar, 0x00495103,
     136, QMetaType::UChar, 0x00495103,
     137, QMetaType::UChar, 0x00495103,
     138, QMetaType::UChar, 0x00495103,
     139, QMetaType::UChar, 0x00495103,
     140, QMetaType::UChar, 0x00495103,
     141, QMetaType::UChar, 0x00495103,
     142, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,
       9,
      10,
      11,
      12,
      13,
      14,
      15,
      16,
      18,
      19,
      20,
      21,
      22,
      23,
      24,
      25,
      26,
      27,
      29,
      30,
      31,
      32,
      33,
      34,

       0        // eod
};

void HwSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HwSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->CC_RcvrPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->CC_MainPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 2: _t->CC_FlexiPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 3: _t->RV_RcvrPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 4: _t->RV_AuxPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 5: _t->RV_AuxSBusPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 6: _t->RV_FlexiPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 7: _t->RV_TelemetryPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 8: _t->RV_GPSPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 9: _t->RM_RcvrPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 10: _t->RM_MainPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 11: _t->RM_FlexiPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->TelemetrySpeedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 13: _t->GPSSpeedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->ComUsbBridgeSpeedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 15: _t->USB_HIDPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 16: _t->USB_VCPPortChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->OptionalModulesChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 18: _t->OptionalModules_CameraStabChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 19: _t->OptionalModules_GPSChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->OptionalModules_FaultChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 21: _t->OptionalModules_AltitudeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 22: _t->OptionalModules_AirspeedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 23: _t->OptionalModules_TxPIDChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 24: _t->OptionalModules_BatteryChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 25: _t->OptionalModules_OveroChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 26: _t->OptionalModules_MagBaroChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 27: _t->OptionalModules_OsdHkChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 28: _t->ADCRoutingChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 29: _t->ADCRouting_adc0Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 30: _t->ADCRouting_adc1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 31: _t->ADCRouting_adc2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 32: _t->ADCRouting_adc3Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 33: _t->DSMxBindChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 34: _t->WS2811LED_OutChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 35: _t->setCC_RcvrPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 36: _t->setCC_MainPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 37: _t->setCC_FlexiPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 38: _t->setRV_RcvrPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 39: _t->setRV_AuxPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 40: _t->setRV_AuxSBusPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 41: _t->setRV_FlexiPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 42: _t->setRV_TelemetryPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 43: _t->setRV_GPSPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 44: _t->setRM_RcvrPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 45: _t->setRM_MainPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 46: _t->setRM_FlexiPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 47: _t->setTelemetrySpeed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 48: _t->setGPSSpeed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 49: _t->setComUsbBridgeSpeed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 50: _t->setUSB_HIDPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 51: _t->setUSB_VCPPort((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 52: _t->setOptionalModules((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 53: _t->setOptionalModules_CameraStab((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 54: _t->setOptionalModules_GPS((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 55: _t->setOptionalModules_Fault((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 56: _t->setOptionalModules_Altitude((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 57: _t->setOptionalModules_Airspeed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 58: _t->setOptionalModules_TxPID((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 59: _t->setOptionalModules_Battery((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 60: _t->setOptionalModules_Overo((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 61: _t->setOptionalModules_MagBaro((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 62: _t->setOptionalModules_OsdHk((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 63: _t->setADCRouting((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 64: _t->setADCRouting_adc0((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 65: _t->setADCRouting_adc1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 66: _t->setADCRouting_adc2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 67: _t->setADCRouting_adc3((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 68: _t->setDSMxBind((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 69: _t->setWS2811LED_Out((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 70: _t->emitNotifications(); break;
        case 71: { quint8 _r = _t->getCC_RcvrPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 72: { quint8 _r = _t->getCC_MainPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 73: { quint8 _r = _t->getCC_FlexiPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 74: { quint8 _r = _t->getRV_RcvrPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 75: { quint8 _r = _t->getRV_AuxPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 76: { quint8 _r = _t->getRV_AuxSBusPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 77: { quint8 _r = _t->getRV_FlexiPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 78: { quint8 _r = _t->getRV_TelemetryPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 79: { quint8 _r = _t->getRV_GPSPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 80: { quint8 _r = _t->getRM_RcvrPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 81: { quint8 _r = _t->getRM_MainPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 82: { quint8 _r = _t->getRM_FlexiPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 83: { quint8 _r = _t->getTelemetrySpeed();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 84: { quint8 _r = _t->getGPSSpeed();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 85: { quint8 _r = _t->getComUsbBridgeSpeed();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 86: { quint8 _r = _t->getUSB_HIDPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 87: { quint8 _r = _t->getUSB_VCPPort();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 88: { quint8 _r = _t->getOptionalModules((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 89: { quint8 _r = _t->getOptionalModules_CameraStab();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 90: { quint8 _r = _t->getOptionalModules_GPS();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 91: { quint8 _r = _t->getOptionalModules_Fault();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 92: { quint8 _r = _t->getOptionalModules_Altitude();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 93: { quint8 _r = _t->getOptionalModules_Airspeed();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 94: { quint8 _r = _t->getOptionalModules_TxPID();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 95: { quint8 _r = _t->getOptionalModules_Battery();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 96: { quint8 _r = _t->getOptionalModules_Overo();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 97: { quint8 _r = _t->getOptionalModules_MagBaro();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 98: { quint8 _r = _t->getOptionalModules_OsdHk();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 99: { quint8 _r = _t->getADCRouting((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 100: { quint8 _r = _t->getADCRouting_adc0();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 101: { quint8 _r = _t->getADCRouting_adc1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 102: { quint8 _r = _t->getADCRouting_adc2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 103: { quint8 _r = _t->getADCRouting_adc3();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 104: { quint8 _r = _t->getDSMxBind();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 105: { quint8 _r = _t->getWS2811LED_Out();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::CC_RcvrPortChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::CC_MainPortChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::CC_FlexiPortChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::RV_RcvrPortChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::RV_AuxPortChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::RV_AuxSBusPortChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::RV_FlexiPortChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::RV_TelemetryPortChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::RV_GPSPortChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::RM_RcvrPortChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::RM_MainPortChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::RM_FlexiPortChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::TelemetrySpeedChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::GPSSpeedChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::ComUsbBridgeSpeedChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::USB_HIDPortChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::USB_VCPPortChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::OptionalModulesChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::OptionalModules_CameraStabChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::OptionalModules_GPSChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::OptionalModules_FaultChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::OptionalModules_AltitudeChanged)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::OptionalModules_AirspeedChanged)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::OptionalModules_TxPIDChanged)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::OptionalModules_BatteryChanged)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::OptionalModules_OveroChanged)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::OptionalModules_MagBaroChanged)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::OptionalModules_OsdHkChanged)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::ADCRoutingChanged)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::ADCRouting_adc0Changed)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::ADCRouting_adc1Changed)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::ADCRouting_adc2Changed)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::ADCRouting_adc3Changed)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::DSMxBindChanged)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (HwSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HwSettings::WS2811LED_OutChanged)) {
                *result = 34;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<HwSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint8*>(_v) = _t->getCC_RcvrPort(); break;
        case 1: *reinterpret_cast< quint8*>(_v) = _t->getCC_MainPort(); break;
        case 2: *reinterpret_cast< quint8*>(_v) = _t->getCC_FlexiPort(); break;
        case 3: *reinterpret_cast< quint8*>(_v) = _t->getRV_RcvrPort(); break;
        case 4: *reinterpret_cast< quint8*>(_v) = _t->getRV_AuxPort(); break;
        case 5: *reinterpret_cast< quint8*>(_v) = _t->getRV_AuxSBusPort(); break;
        case 6: *reinterpret_cast< quint8*>(_v) = _t->getRV_FlexiPort(); break;
        case 7: *reinterpret_cast< quint8*>(_v) = _t->getRV_TelemetryPort(); break;
        case 8: *reinterpret_cast< quint8*>(_v) = _t->getRV_GPSPort(); break;
        case 9: *reinterpret_cast< quint8*>(_v) = _t->getRM_RcvrPort(); break;
        case 10: *reinterpret_cast< quint8*>(_v) = _t->getRM_MainPort(); break;
        case 11: *reinterpret_cast< quint8*>(_v) = _t->getRM_FlexiPort(); break;
        case 12: *reinterpret_cast< quint8*>(_v) = _t->getTelemetrySpeed(); break;
        case 13: *reinterpret_cast< quint8*>(_v) = _t->getGPSSpeed(); break;
        case 14: *reinterpret_cast< quint8*>(_v) = _t->getComUsbBridgeSpeed(); break;
        case 15: *reinterpret_cast< quint8*>(_v) = _t->getUSB_HIDPort(); break;
        case 16: *reinterpret_cast< quint8*>(_v) = _t->getUSB_VCPPort(); break;
        case 17: *reinterpret_cast< quint8*>(_v) = _t->getOptionalModules_CameraStab(); break;
        case 18: *reinterpret_cast< quint8*>(_v) = _t->getOptionalModules_GPS(); break;
        case 19: *reinterpret_cast< quint8*>(_v) = _t->getOptionalModules_Fault(); break;
        case 20: *reinterpret_cast< quint8*>(_v) = _t->getOptionalModules_Altitude(); break;
        case 21: *reinterpret_cast< quint8*>(_v) = _t->getOptionalModules_Airspeed(); break;
        case 22: *reinterpret_cast< quint8*>(_v) = _t->getOptionalModules_TxPID(); break;
        case 23: *reinterpret_cast< quint8*>(_v) = _t->getOptionalModules_Battery(); break;
        case 24: *reinterpret_cast< quint8*>(_v) = _t->getOptionalModules_Overo(); break;
        case 25: *reinterpret_cast< quint8*>(_v) = _t->getOptionalModules_MagBaro(); break;
        case 26: *reinterpret_cast< quint8*>(_v) = _t->getOptionalModules_OsdHk(); break;
        case 27: *reinterpret_cast< quint8*>(_v) = _t->getADCRouting_adc0(); break;
        case 28: *reinterpret_cast< quint8*>(_v) = _t->getADCRouting_adc1(); break;
        case 29: *reinterpret_cast< quint8*>(_v) = _t->getADCRouting_adc2(); break;
        case 30: *reinterpret_cast< quint8*>(_v) = _t->getADCRouting_adc3(); break;
        case 31: *reinterpret_cast< quint8*>(_v) = _t->getDSMxBind(); break;
        case 32: *reinterpret_cast< quint8*>(_v) = _t->getWS2811LED_Out(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<HwSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCC_RcvrPort(*reinterpret_cast< quint8*>(_v)); break;
        case 1: _t->setCC_MainPort(*reinterpret_cast< quint8*>(_v)); break;
        case 2: _t->setCC_FlexiPort(*reinterpret_cast< quint8*>(_v)); break;
        case 3: _t->setRV_RcvrPort(*reinterpret_cast< quint8*>(_v)); break;
        case 4: _t->setRV_AuxPort(*reinterpret_cast< quint8*>(_v)); break;
        case 5: _t->setRV_AuxSBusPort(*reinterpret_cast< quint8*>(_v)); break;
        case 6: _t->setRV_FlexiPort(*reinterpret_cast< quint8*>(_v)); break;
        case 7: _t->setRV_TelemetryPort(*reinterpret_cast< quint8*>(_v)); break;
        case 8: _t->setRV_GPSPort(*reinterpret_cast< quint8*>(_v)); break;
        case 9: _t->setRM_RcvrPort(*reinterpret_cast< quint8*>(_v)); break;
        case 10: _t->setRM_MainPort(*reinterpret_cast< quint8*>(_v)); break;
        case 11: _t->setRM_FlexiPort(*reinterpret_cast< quint8*>(_v)); break;
        case 12: _t->setTelemetrySpeed(*reinterpret_cast< quint8*>(_v)); break;
        case 13: _t->setGPSSpeed(*reinterpret_cast< quint8*>(_v)); break;
        case 14: _t->setComUsbBridgeSpeed(*reinterpret_cast< quint8*>(_v)); break;
        case 15: _t->setUSB_HIDPort(*reinterpret_cast< quint8*>(_v)); break;
        case 16: _t->setUSB_VCPPort(*reinterpret_cast< quint8*>(_v)); break;
        case 17: _t->setOptionalModules_CameraStab(*reinterpret_cast< quint8*>(_v)); break;
        case 18: _t->setOptionalModules_GPS(*reinterpret_cast< quint8*>(_v)); break;
        case 19: _t->setOptionalModules_Fault(*reinterpret_cast< quint8*>(_v)); break;
        case 20: _t->setOptionalModules_Altitude(*reinterpret_cast< quint8*>(_v)); break;
        case 21: _t->setOptionalModules_Airspeed(*reinterpret_cast< quint8*>(_v)); break;
        case 22: _t->setOptionalModules_TxPID(*reinterpret_cast< quint8*>(_v)); break;
        case 23: _t->setOptionalModules_Battery(*reinterpret_cast< quint8*>(_v)); break;
        case 24: _t->setOptionalModules_Overo(*reinterpret_cast< quint8*>(_v)); break;
        case 25: _t->setOptionalModules_MagBaro(*reinterpret_cast< quint8*>(_v)); break;
        case 26: _t->setOptionalModules_OsdHk(*reinterpret_cast< quint8*>(_v)); break;
        case 27: _t->setADCRouting_adc0(*reinterpret_cast< quint8*>(_v)); break;
        case 28: _t->setADCRouting_adc1(*reinterpret_cast< quint8*>(_v)); break;
        case 29: _t->setADCRouting_adc2(*reinterpret_cast< quint8*>(_v)); break;
        case 30: _t->setADCRouting_adc3(*reinterpret_cast< quint8*>(_v)); break;
        case 31: _t->setDSMxBind(*reinterpret_cast< quint8*>(_v)); break;
        case 32: _t->setWS2811LED_Out(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject HwSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_HwSettings.data,
    qt_meta_data_HwSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HwSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HwSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HwSettings.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int HwSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 106)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 106;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 106)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 106;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 33;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 33;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 33;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 33;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 33;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void HwSettings::CC_RcvrPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HwSettings::CC_MainPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void HwSettings::CC_FlexiPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void HwSettings::RV_RcvrPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void HwSettings::RV_AuxPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void HwSettings::RV_AuxSBusPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void HwSettings::RV_FlexiPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void HwSettings::RV_TelemetryPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void HwSettings::RV_GPSPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void HwSettings::RM_RcvrPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void HwSettings::RM_MainPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void HwSettings::RM_FlexiPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void HwSettings::TelemetrySpeedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void HwSettings::GPSSpeedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void HwSettings::ComUsbBridgeSpeedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void HwSettings::USB_HIDPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void HwSettings::USB_VCPPortChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void HwSettings::OptionalModulesChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void HwSettings::OptionalModules_CameraStabChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void HwSettings::OptionalModules_GPSChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void HwSettings::OptionalModules_FaultChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void HwSettings::OptionalModules_AltitudeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void HwSettings::OptionalModules_AirspeedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void HwSettings::OptionalModules_TxPIDChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void HwSettings::OptionalModules_BatteryChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void HwSettings::OptionalModules_OveroChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void HwSettings::OptionalModules_MagBaroChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void HwSettings::OptionalModules_OsdHkChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void HwSettings::ADCRoutingChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void HwSettings::ADCRouting_adc0Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void HwSettings::ADCRouting_adc1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void HwSettings::ADCRouting_adc2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void HwSettings::ADCRouting_adc3Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void HwSettings::DSMxBindChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void HwSettings::WS2811LED_OutChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
