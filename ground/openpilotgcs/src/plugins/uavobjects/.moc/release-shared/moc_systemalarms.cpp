/****************************************************************************
** Meta object code from reading C++ file 'systemalarms.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/systemalarms.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'systemalarms.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SystemAlarms_t {
    QByteArrayData data[114];
    char stringdata0[2523];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SystemAlarms_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SystemAlarms_t qt_meta_stringdata_SystemAlarms = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SystemAlarms"
QT_MOC_LITERAL(1, 13, 12), // "AlarmChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "index"
QT_MOC_LITERAL(4, 33, 5), // "value"
QT_MOC_LITERAL(5, 39, 32), // "Alarm_SystemConfigurationChanged"
QT_MOC_LITERAL(6, 72, 22), // "Alarm_BootFaultChanged"
QT_MOC_LITERAL(7, 95, 24), // "Alarm_OutOfMemoryChanged"
QT_MOC_LITERAL(8, 120, 26), // "Alarm_StackOverflowChanged"
QT_MOC_LITERAL(9, 147, 24), // "Alarm_CPUOverloadChanged"
QT_MOC_LITERAL(10, 172, 24), // "Alarm_EventSystemChanged"
QT_MOC_LITERAL(11, 197, 22), // "Alarm_TelemetryChanged"
QT_MOC_LITERAL(12, 220, 21), // "Alarm_ReceiverChanged"
QT_MOC_LITERAL(13, 242, 26), // "Alarm_ManualControlChanged"
QT_MOC_LITERAL(14, 269, 21), // "Alarm_ActuatorChanged"
QT_MOC_LITERAL(15, 291, 21), // "Alarm_AttitudeChanged"
QT_MOC_LITERAL(16, 313, 20), // "Alarm_SensorsChanged"
QT_MOC_LITERAL(17, 334, 25), // "Alarm_MagnetometerChanged"
QT_MOC_LITERAL(18, 360, 21), // "Alarm_AirspeedChanged"
QT_MOC_LITERAL(19, 382, 26), // "Alarm_StabilizationChanged"
QT_MOC_LITERAL(20, 409, 21), // "Alarm_GuidanceChanged"
QT_MOC_LITERAL(21, 431, 21), // "Alarm_PathPlanChanged"
QT_MOC_LITERAL(22, 453, 20), // "Alarm_BatteryChanged"
QT_MOC_LITERAL(23, 474, 23), // "Alarm_FlightTimeChanged"
QT_MOC_LITERAL(24, 498, 16), // "Alarm_I2CChanged"
QT_MOC_LITERAL(25, 515, 16), // "Alarm_GPSChanged"
QT_MOC_LITERAL(26, 532, 26), // "ExtendedAlarmStatusChanged"
QT_MOC_LITERAL(27, 559, 46), // "ExtendedAlarmStatus_SystemCon..."
QT_MOC_LITERAL(28, 606, 36), // "ExtendedAlarmStatus_BootFault..."
QT_MOC_LITERAL(29, 643, 29), // "ExtendedAlarmSubStatusChanged"
QT_MOC_LITERAL(30, 673, 49), // "ExtendedAlarmSubStatus_System..."
QT_MOC_LITERAL(31, 723, 39), // "ExtendedAlarmSubStatus_BootFa..."
QT_MOC_LITERAL(32, 763, 8), // "setAlarm"
QT_MOC_LITERAL(33, 772, 28), // "setAlarm_SystemConfiguration"
QT_MOC_LITERAL(34, 801, 18), // "setAlarm_BootFault"
QT_MOC_LITERAL(35, 820, 20), // "setAlarm_OutOfMemory"
QT_MOC_LITERAL(36, 841, 22), // "setAlarm_StackOverflow"
QT_MOC_LITERAL(37, 864, 20), // "setAlarm_CPUOverload"
QT_MOC_LITERAL(38, 885, 20), // "setAlarm_EventSystem"
QT_MOC_LITERAL(39, 906, 18), // "setAlarm_Telemetry"
QT_MOC_LITERAL(40, 925, 17), // "setAlarm_Receiver"
QT_MOC_LITERAL(41, 943, 22), // "setAlarm_ManualControl"
QT_MOC_LITERAL(42, 966, 17), // "setAlarm_Actuator"
QT_MOC_LITERAL(43, 984, 17), // "setAlarm_Attitude"
QT_MOC_LITERAL(44, 1002, 16), // "setAlarm_Sensors"
QT_MOC_LITERAL(45, 1019, 21), // "setAlarm_Magnetometer"
QT_MOC_LITERAL(46, 1041, 17), // "setAlarm_Airspeed"
QT_MOC_LITERAL(47, 1059, 22), // "setAlarm_Stabilization"
QT_MOC_LITERAL(48, 1082, 17), // "setAlarm_Guidance"
QT_MOC_LITERAL(49, 1100, 17), // "setAlarm_PathPlan"
QT_MOC_LITERAL(50, 1118, 16), // "setAlarm_Battery"
QT_MOC_LITERAL(51, 1135, 19), // "setAlarm_FlightTime"
QT_MOC_LITERAL(52, 1155, 12), // "setAlarm_I2C"
QT_MOC_LITERAL(53, 1168, 12), // "setAlarm_GPS"
QT_MOC_LITERAL(54, 1181, 22), // "setExtendedAlarmStatus"
QT_MOC_LITERAL(55, 1204, 42), // "setExtendedAlarmStatus_System..."
QT_MOC_LITERAL(56, 1247, 32), // "setExtendedAlarmStatus_BootFault"
QT_MOC_LITERAL(57, 1280, 25), // "setExtendedAlarmSubStatus"
QT_MOC_LITERAL(58, 1306, 45), // "setExtendedAlarmSubStatus_Sys..."
QT_MOC_LITERAL(59, 1352, 35), // "setExtendedAlarmSubStatus_Boo..."
QT_MOC_LITERAL(60, 1388, 17), // "emitNotifications"
QT_MOC_LITERAL(61, 1406, 8), // "getAlarm"
QT_MOC_LITERAL(62, 1415, 28), // "getAlarm_SystemConfiguration"
QT_MOC_LITERAL(63, 1444, 18), // "getAlarm_BootFault"
QT_MOC_LITERAL(64, 1463, 20), // "getAlarm_OutOfMemory"
QT_MOC_LITERAL(65, 1484, 22), // "getAlarm_StackOverflow"
QT_MOC_LITERAL(66, 1507, 20), // "getAlarm_CPUOverload"
QT_MOC_LITERAL(67, 1528, 20), // "getAlarm_EventSystem"
QT_MOC_LITERAL(68, 1549, 18), // "getAlarm_Telemetry"
QT_MOC_LITERAL(69, 1568, 17), // "getAlarm_Receiver"
QT_MOC_LITERAL(70, 1586, 22), // "getAlarm_ManualControl"
QT_MOC_LITERAL(71, 1609, 17), // "getAlarm_Actuator"
QT_MOC_LITERAL(72, 1627, 17), // "getAlarm_Attitude"
QT_MOC_LITERAL(73, 1645, 16), // "getAlarm_Sensors"
QT_MOC_LITERAL(74, 1662, 21), // "getAlarm_Magnetometer"
QT_MOC_LITERAL(75, 1684, 17), // "getAlarm_Airspeed"
QT_MOC_LITERAL(76, 1702, 22), // "getAlarm_Stabilization"
QT_MOC_LITERAL(77, 1725, 17), // "getAlarm_Guidance"
QT_MOC_LITERAL(78, 1743, 17), // "getAlarm_PathPlan"
QT_MOC_LITERAL(79, 1761, 16), // "getAlarm_Battery"
QT_MOC_LITERAL(80, 1778, 19), // "getAlarm_FlightTime"
QT_MOC_LITERAL(81, 1798, 12), // "getAlarm_I2C"
QT_MOC_LITERAL(82, 1811, 12), // "getAlarm_GPS"
QT_MOC_LITERAL(83, 1824, 22), // "getExtendedAlarmStatus"
QT_MOC_LITERAL(84, 1847, 42), // "getExtendedAlarmStatus_System..."
QT_MOC_LITERAL(85, 1890, 32), // "getExtendedAlarmStatus_BootFault"
QT_MOC_LITERAL(86, 1923, 25), // "getExtendedAlarmSubStatus"
QT_MOC_LITERAL(87, 1949, 45), // "getExtendedAlarmSubStatus_Sys..."
QT_MOC_LITERAL(88, 1995, 35), // "getExtendedAlarmSubStatus_Boo..."
QT_MOC_LITERAL(89, 2031, 25), // "Alarm_SystemConfiguration"
QT_MOC_LITERAL(90, 2057, 15), // "Alarm_BootFault"
QT_MOC_LITERAL(91, 2073, 17), // "Alarm_OutOfMemory"
QT_MOC_LITERAL(92, 2091, 19), // "Alarm_StackOverflow"
QT_MOC_LITERAL(93, 2111, 17), // "Alarm_CPUOverload"
QT_MOC_LITERAL(94, 2129, 17), // "Alarm_EventSystem"
QT_MOC_LITERAL(95, 2147, 15), // "Alarm_Telemetry"
QT_MOC_LITERAL(96, 2163, 14), // "Alarm_Receiver"
QT_MOC_LITERAL(97, 2178, 19), // "Alarm_ManualControl"
QT_MOC_LITERAL(98, 2198, 14), // "Alarm_Actuator"
QT_MOC_LITERAL(99, 2213, 14), // "Alarm_Attitude"
QT_MOC_LITERAL(100, 2228, 13), // "Alarm_Sensors"
QT_MOC_LITERAL(101, 2242, 18), // "Alarm_Magnetometer"
QT_MOC_LITERAL(102, 2261, 14), // "Alarm_Airspeed"
QT_MOC_LITERAL(103, 2276, 19), // "Alarm_Stabilization"
QT_MOC_LITERAL(104, 2296, 14), // "Alarm_Guidance"
QT_MOC_LITERAL(105, 2311, 14), // "Alarm_PathPlan"
QT_MOC_LITERAL(106, 2326, 13), // "Alarm_Battery"
QT_MOC_LITERAL(107, 2340, 16), // "Alarm_FlightTime"
QT_MOC_LITERAL(108, 2357, 9), // "Alarm_I2C"
QT_MOC_LITERAL(109, 2367, 9), // "Alarm_GPS"
QT_MOC_LITERAL(110, 2377, 39), // "ExtendedAlarmStatus_SystemCon..."
QT_MOC_LITERAL(111, 2417, 29), // "ExtendedAlarmStatus_BootFault"
QT_MOC_LITERAL(112, 2447, 42), // "ExtendedAlarmSubStatus_System..."
QT_MOC_LITERAL(113, 2490, 32) // "ExtendedAlarmSubStatus_BootFault"

    },
    "SystemAlarms\0AlarmChanged\0\0index\0value\0"
    "Alarm_SystemConfigurationChanged\0"
    "Alarm_BootFaultChanged\0Alarm_OutOfMemoryChanged\0"
    "Alarm_StackOverflowChanged\0"
    "Alarm_CPUOverloadChanged\0"
    "Alarm_EventSystemChanged\0"
    "Alarm_TelemetryChanged\0Alarm_ReceiverChanged\0"
    "Alarm_ManualControlChanged\0"
    "Alarm_ActuatorChanged\0Alarm_AttitudeChanged\0"
    "Alarm_SensorsChanged\0Alarm_MagnetometerChanged\0"
    "Alarm_AirspeedChanged\0Alarm_StabilizationChanged\0"
    "Alarm_GuidanceChanged\0Alarm_PathPlanChanged\0"
    "Alarm_BatteryChanged\0Alarm_FlightTimeChanged\0"
    "Alarm_I2CChanged\0Alarm_GPSChanged\0"
    "ExtendedAlarmStatusChanged\0"
    "ExtendedAlarmStatus_SystemConfigurationChanged\0"
    "ExtendedAlarmStatus_BootFaultChanged\0"
    "ExtendedAlarmSubStatusChanged\0"
    "ExtendedAlarmSubStatus_SystemConfigurationChanged\0"
    "ExtendedAlarmSubStatus_BootFaultChanged\0"
    "setAlarm\0setAlarm_SystemConfiguration\0"
    "setAlarm_BootFault\0setAlarm_OutOfMemory\0"
    "setAlarm_StackOverflow\0setAlarm_CPUOverload\0"
    "setAlarm_EventSystem\0setAlarm_Telemetry\0"
    "setAlarm_Receiver\0setAlarm_ManualControl\0"
    "setAlarm_Actuator\0setAlarm_Attitude\0"
    "setAlarm_Sensors\0setAlarm_Magnetometer\0"
    "setAlarm_Airspeed\0setAlarm_Stabilization\0"
    "setAlarm_Guidance\0setAlarm_PathPlan\0"
    "setAlarm_Battery\0setAlarm_FlightTime\0"
    "setAlarm_I2C\0setAlarm_GPS\0"
    "setExtendedAlarmStatus\0"
    "setExtendedAlarmStatus_SystemConfiguration\0"
    "setExtendedAlarmStatus_BootFault\0"
    "setExtendedAlarmSubStatus\0"
    "setExtendedAlarmSubStatus_SystemConfiguration\0"
    "setExtendedAlarmSubStatus_BootFault\0"
    "emitNotifications\0getAlarm\0"
    "getAlarm_SystemConfiguration\0"
    "getAlarm_BootFault\0getAlarm_OutOfMemory\0"
    "getAlarm_StackOverflow\0getAlarm_CPUOverload\0"
    "getAlarm_EventSystem\0getAlarm_Telemetry\0"
    "getAlarm_Receiver\0getAlarm_ManualControl\0"
    "getAlarm_Actuator\0getAlarm_Attitude\0"
    "getAlarm_Sensors\0getAlarm_Magnetometer\0"
    "getAlarm_Airspeed\0getAlarm_Stabilization\0"
    "getAlarm_Guidance\0getAlarm_PathPlan\0"
    "getAlarm_Battery\0getAlarm_FlightTime\0"
    "getAlarm_I2C\0getAlarm_GPS\0"
    "getExtendedAlarmStatus\0"
    "getExtendedAlarmStatus_SystemConfiguration\0"
    "getExtendedAlarmStatus_BootFault\0"
    "getExtendedAlarmSubStatus\0"
    "getExtendedAlarmSubStatus_SystemConfiguration\0"
    "getExtendedAlarmSubStatus_BootFault\0"
    "Alarm_SystemConfiguration\0Alarm_BootFault\0"
    "Alarm_OutOfMemory\0Alarm_StackOverflow\0"
    "Alarm_CPUOverload\0Alarm_EventSystem\0"
    "Alarm_Telemetry\0Alarm_Receiver\0"
    "Alarm_ManualControl\0Alarm_Actuator\0"
    "Alarm_Attitude\0Alarm_Sensors\0"
    "Alarm_Magnetometer\0Alarm_Airspeed\0"
    "Alarm_Stabilization\0Alarm_Guidance\0"
    "Alarm_PathPlan\0Alarm_Battery\0"
    "Alarm_FlightTime\0Alarm_I2C\0Alarm_GPS\0"
    "ExtendedAlarmStatus_SystemConfiguration\0"
    "ExtendedAlarmStatus_BootFault\0"
    "ExtendedAlarmSubStatus_SystemConfiguration\0"
    "ExtendedAlarmSubStatus_BootFault"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SystemAlarms[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      85,   14, // methods
      25,  654, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      28,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  439,    2, 0x06 /* Public */,
       5,    1,  444,    2, 0x06 /* Public */,
       6,    1,  447,    2, 0x06 /* Public */,
       7,    1,  450,    2, 0x06 /* Public */,
       8,    1,  453,    2, 0x06 /* Public */,
       9,    1,  456,    2, 0x06 /* Public */,
      10,    1,  459,    2, 0x06 /* Public */,
      11,    1,  462,    2, 0x06 /* Public */,
      12,    1,  465,    2, 0x06 /* Public */,
      13,    1,  468,    2, 0x06 /* Public */,
      14,    1,  471,    2, 0x06 /* Public */,
      15,    1,  474,    2, 0x06 /* Public */,
      16,    1,  477,    2, 0x06 /* Public */,
      17,    1,  480,    2, 0x06 /* Public */,
      18,    1,  483,    2, 0x06 /* Public */,
      19,    1,  486,    2, 0x06 /* Public */,
      20,    1,  489,    2, 0x06 /* Public */,
      21,    1,  492,    2, 0x06 /* Public */,
      22,    1,  495,    2, 0x06 /* Public */,
      23,    1,  498,    2, 0x06 /* Public */,
      24,    1,  501,    2, 0x06 /* Public */,
      25,    1,  504,    2, 0x06 /* Public */,
      26,    2,  507,    2, 0x06 /* Public */,
      27,    1,  512,    2, 0x06 /* Public */,
      28,    1,  515,    2, 0x06 /* Public */,
      29,    2,  518,    2, 0x06 /* Public */,
      30,    1,  523,    2, 0x06 /* Public */,
      31,    1,  526,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      32,    2,  529,    2, 0x0a /* Public */,
      33,    1,  534,    2, 0x0a /* Public */,
      34,    1,  537,    2, 0x0a /* Public */,
      35,    1,  540,    2, 0x0a /* Public */,
      36,    1,  543,    2, 0x0a /* Public */,
      37,    1,  546,    2, 0x0a /* Public */,
      38,    1,  549,    2, 0x0a /* Public */,
      39,    1,  552,    2, 0x0a /* Public */,
      40,    1,  555,    2, 0x0a /* Public */,
      41,    1,  558,    2, 0x0a /* Public */,
      42,    1,  561,    2, 0x0a /* Public */,
      43,    1,  564,    2, 0x0a /* Public */,
      44,    1,  567,    2, 0x0a /* Public */,
      45,    1,  570,    2, 0x0a /* Public */,
      46,    1,  573,    2, 0x0a /* Public */,
      47,    1,  576,    2, 0x0a /* Public */,
      48,    1,  579,    2, 0x0a /* Public */,
      49,    1,  582,    2, 0x0a /* Public */,
      50,    1,  585,    2, 0x0a /* Public */,
      51,    1,  588,    2, 0x0a /* Public */,
      52,    1,  591,    2, 0x0a /* Public */,
      53,    1,  594,    2, 0x0a /* Public */,
      54,    2,  597,    2, 0x0a /* Public */,
      55,    1,  602,    2, 0x0a /* Public */,
      56,    1,  605,    2, 0x0a /* Public */,
      57,    2,  608,    2, 0x0a /* Public */,
      58,    1,  613,    2, 0x0a /* Public */,
      59,    1,  616,    2, 0x0a /* Public */,
      60,    0,  619,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      61,    1,  620,    2, 0x02 /* Public */,
      62,    0,  623,    2, 0x02 /* Public */,
      63,    0,  624,    2, 0x02 /* Public */,
      64,    0,  625,    2, 0x02 /* Public */,
      65,    0,  626,    2, 0x02 /* Public */,
      66,    0,  627,    2, 0x02 /* Public */,
      67,    0,  628,    2, 0x02 /* Public */,
      68,    0,  629,    2, 0x02 /* Public */,
      69,    0,  630,    2, 0x02 /* Public */,
      70,    0,  631,    2, 0x02 /* Public */,
      71,    0,  632,    2, 0x02 /* Public */,
      72,    0,  633,    2, 0x02 /* Public */,
      73,    0,  634,    2, 0x02 /* Public */,
      74,    0,  635,    2, 0x02 /* Public */,
      75,    0,  636,    2, 0x02 /* Public */,
      76,    0,  637,    2, 0x02 /* Public */,
      77,    0,  638,    2, 0x02 /* Public */,
      78,    0,  639,    2, 0x02 /* Public */,
      79,    0,  640,    2, 0x02 /* Public */,
      80,    0,  641,    2, 0x02 /* Public */,
      81,    0,  642,    2, 0x02 /* Public */,
      82,    0,  643,    2, 0x02 /* Public */,
      83,    1,  644,    2, 0x02 /* Public */,
      84,    0,  647,    2, 0x02 /* Public */,
      85,    0,  648,    2, 0x02 /* Public */,
      86,    1,  649,    2, 0x02 /* Public */,
      87,    0,  652,    2, 0x02 /* Public */,
      88,    0,  653,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::UChar, QMetaType::UInt,    3,
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
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    3,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    3,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      89, QMetaType::UChar, 0x00495103,
      90, QMetaType::UChar, 0x00495103,
      91, QMetaType::UChar, 0x00495103,
      92, QMetaType::UChar, 0x00495103,
      93, QMetaType::UChar, 0x00495103,
      94, QMetaType::UChar, 0x00495103,
      95, QMetaType::UChar, 0x00495103,
      96, QMetaType::UChar, 0x00495103,
      97, QMetaType::UChar, 0x00495103,
      98, QMetaType::UChar, 0x00495103,
      99, QMetaType::UChar, 0x00495103,
     100, QMetaType::UChar, 0x00495103,
     101, QMetaType::UChar, 0x00495103,
     102, QMetaType::UChar, 0x00495103,
     103, QMetaType::UChar, 0x00495103,
     104, QMetaType::UChar, 0x00495103,
     105, QMetaType::UChar, 0x00495103,
     106, QMetaType::UChar, 0x00495103,
     107, QMetaType::UChar, 0x00495103,
     108, QMetaType::UChar, 0x00495103,
     109, QMetaType::UChar, 0x00495103,
     110, QMetaType::UChar, 0x00495103,
     111, QMetaType::UChar, 0x00495103,
     112, QMetaType::UChar, 0x00495103,
     113, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
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
      17,
      18,
      19,
      20,
      21,
      23,
      24,
      26,
      27,

       0        // eod
};

void SystemAlarms::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SystemAlarms *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->AlarmChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 1: _t->Alarm_SystemConfigurationChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 2: _t->Alarm_BootFaultChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 3: _t->Alarm_OutOfMemoryChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 4: _t->Alarm_StackOverflowChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 5: _t->Alarm_CPUOverloadChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 6: _t->Alarm_EventSystemChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 7: _t->Alarm_TelemetryChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 8: _t->Alarm_ReceiverChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 9: _t->Alarm_ManualControlChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 10: _t->Alarm_ActuatorChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 11: _t->Alarm_AttitudeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->Alarm_SensorsChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 13: _t->Alarm_MagnetometerChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->Alarm_AirspeedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 15: _t->Alarm_StabilizationChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 16: _t->Alarm_GuidanceChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->Alarm_PathPlanChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 18: _t->Alarm_BatteryChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 19: _t->Alarm_FlightTimeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->Alarm_I2CChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 21: _t->Alarm_GPSChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 22: _t->ExtendedAlarmStatusChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 23: _t->ExtendedAlarmStatus_SystemConfigurationChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 24: _t->ExtendedAlarmStatus_BootFaultChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 25: _t->ExtendedAlarmSubStatusChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 26: _t->ExtendedAlarmSubStatus_SystemConfigurationChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 27: _t->ExtendedAlarmSubStatus_BootFaultChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 28: _t->setAlarm((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 29: _t->setAlarm_SystemConfiguration((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 30: _t->setAlarm_BootFault((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 31: _t->setAlarm_OutOfMemory((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 32: _t->setAlarm_StackOverflow((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 33: _t->setAlarm_CPUOverload((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 34: _t->setAlarm_EventSystem((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 35: _t->setAlarm_Telemetry((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 36: _t->setAlarm_Receiver((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 37: _t->setAlarm_ManualControl((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 38: _t->setAlarm_Actuator((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 39: _t->setAlarm_Attitude((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 40: _t->setAlarm_Sensors((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 41: _t->setAlarm_Magnetometer((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 42: _t->setAlarm_Airspeed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 43: _t->setAlarm_Stabilization((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 44: _t->setAlarm_Guidance((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 45: _t->setAlarm_PathPlan((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 46: _t->setAlarm_Battery((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 47: _t->setAlarm_FlightTime((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 48: _t->setAlarm_I2C((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 49: _t->setAlarm_GPS((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 50: _t->setExtendedAlarmStatus((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 51: _t->setExtendedAlarmStatus_SystemConfiguration((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 52: _t->setExtendedAlarmStatus_BootFault((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 53: _t->setExtendedAlarmSubStatus((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 54: _t->setExtendedAlarmSubStatus_SystemConfiguration((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 55: _t->setExtendedAlarmSubStatus_BootFault((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 56: _t->emitNotifications(); break;
        case 57: { quint8 _r = _t->getAlarm((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 58: { quint8 _r = _t->getAlarm_SystemConfiguration();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 59: { quint8 _r = _t->getAlarm_BootFault();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 60: { quint8 _r = _t->getAlarm_OutOfMemory();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 61: { quint8 _r = _t->getAlarm_StackOverflow();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 62: { quint8 _r = _t->getAlarm_CPUOverload();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 63: { quint8 _r = _t->getAlarm_EventSystem();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 64: { quint8 _r = _t->getAlarm_Telemetry();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 65: { quint8 _r = _t->getAlarm_Receiver();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 66: { quint8 _r = _t->getAlarm_ManualControl();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 67: { quint8 _r = _t->getAlarm_Actuator();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 68: { quint8 _r = _t->getAlarm_Attitude();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 69: { quint8 _r = _t->getAlarm_Sensors();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 70: { quint8 _r = _t->getAlarm_Magnetometer();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 71: { quint8 _r = _t->getAlarm_Airspeed();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 72: { quint8 _r = _t->getAlarm_Stabilization();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 73: { quint8 _r = _t->getAlarm_Guidance();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 74: { quint8 _r = _t->getAlarm_PathPlan();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 75: { quint8 _r = _t->getAlarm_Battery();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 76: { quint8 _r = _t->getAlarm_FlightTime();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 77: { quint8 _r = _t->getAlarm_I2C();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 78: { quint8 _r = _t->getAlarm_GPS();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 79: { quint8 _r = _t->getExtendedAlarmStatus((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 80: { quint8 _r = _t->getExtendedAlarmStatus_SystemConfiguration();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 81: { quint8 _r = _t->getExtendedAlarmStatus_BootFault();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 82: { quint8 _r = _t->getExtendedAlarmSubStatus((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 83: { quint8 _r = _t->getExtendedAlarmSubStatus_SystemConfiguration();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 84: { quint8 _r = _t->getExtendedAlarmSubStatus_BootFault();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SystemAlarms::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::AlarmChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_SystemConfigurationChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_BootFaultChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_OutOfMemoryChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_StackOverflowChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_CPUOverloadChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_EventSystemChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_TelemetryChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_ReceiverChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_ManualControlChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_ActuatorChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_AttitudeChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_SensorsChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_MagnetometerChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_AirspeedChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_StabilizationChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_GuidanceChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_PathPlanChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_BatteryChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_FlightTimeChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_I2CChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::Alarm_GPSChanged)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::ExtendedAlarmStatusChanged)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::ExtendedAlarmStatus_SystemConfigurationChanged)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::ExtendedAlarmStatus_BootFaultChanged)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::ExtendedAlarmSubStatusChanged)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::ExtendedAlarmSubStatus_SystemConfigurationChanged)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (SystemAlarms::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemAlarms::ExtendedAlarmSubStatus_BootFaultChanged)) {
                *result = 27;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SystemAlarms *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_SystemConfiguration(); break;
        case 1: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_BootFault(); break;
        case 2: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_OutOfMemory(); break;
        case 3: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_StackOverflow(); break;
        case 4: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_CPUOverload(); break;
        case 5: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_EventSystem(); break;
        case 6: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_Telemetry(); break;
        case 7: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_Receiver(); break;
        case 8: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_ManualControl(); break;
        case 9: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_Actuator(); break;
        case 10: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_Attitude(); break;
        case 11: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_Sensors(); break;
        case 12: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_Magnetometer(); break;
        case 13: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_Airspeed(); break;
        case 14: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_Stabilization(); break;
        case 15: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_Guidance(); break;
        case 16: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_PathPlan(); break;
        case 17: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_Battery(); break;
        case 18: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_FlightTime(); break;
        case 19: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_I2C(); break;
        case 20: *reinterpret_cast< quint8*>(_v) = _t->getAlarm_GPS(); break;
        case 21: *reinterpret_cast< quint8*>(_v) = _t->getExtendedAlarmStatus_SystemConfiguration(); break;
        case 22: *reinterpret_cast< quint8*>(_v) = _t->getExtendedAlarmStatus_BootFault(); break;
        case 23: *reinterpret_cast< quint8*>(_v) = _t->getExtendedAlarmSubStatus_SystemConfiguration(); break;
        case 24: *reinterpret_cast< quint8*>(_v) = _t->getExtendedAlarmSubStatus_BootFault(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SystemAlarms *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAlarm_SystemConfiguration(*reinterpret_cast< quint8*>(_v)); break;
        case 1: _t->setAlarm_BootFault(*reinterpret_cast< quint8*>(_v)); break;
        case 2: _t->setAlarm_OutOfMemory(*reinterpret_cast< quint8*>(_v)); break;
        case 3: _t->setAlarm_StackOverflow(*reinterpret_cast< quint8*>(_v)); break;
        case 4: _t->setAlarm_CPUOverload(*reinterpret_cast< quint8*>(_v)); break;
        case 5: _t->setAlarm_EventSystem(*reinterpret_cast< quint8*>(_v)); break;
        case 6: _t->setAlarm_Telemetry(*reinterpret_cast< quint8*>(_v)); break;
        case 7: _t->setAlarm_Receiver(*reinterpret_cast< quint8*>(_v)); break;
        case 8: _t->setAlarm_ManualControl(*reinterpret_cast< quint8*>(_v)); break;
        case 9: _t->setAlarm_Actuator(*reinterpret_cast< quint8*>(_v)); break;
        case 10: _t->setAlarm_Attitude(*reinterpret_cast< quint8*>(_v)); break;
        case 11: _t->setAlarm_Sensors(*reinterpret_cast< quint8*>(_v)); break;
        case 12: _t->setAlarm_Magnetometer(*reinterpret_cast< quint8*>(_v)); break;
        case 13: _t->setAlarm_Airspeed(*reinterpret_cast< quint8*>(_v)); break;
        case 14: _t->setAlarm_Stabilization(*reinterpret_cast< quint8*>(_v)); break;
        case 15: _t->setAlarm_Guidance(*reinterpret_cast< quint8*>(_v)); break;
        case 16: _t->setAlarm_PathPlan(*reinterpret_cast< quint8*>(_v)); break;
        case 17: _t->setAlarm_Battery(*reinterpret_cast< quint8*>(_v)); break;
        case 18: _t->setAlarm_FlightTime(*reinterpret_cast< quint8*>(_v)); break;
        case 19: _t->setAlarm_I2C(*reinterpret_cast< quint8*>(_v)); break;
        case 20: _t->setAlarm_GPS(*reinterpret_cast< quint8*>(_v)); break;
        case 21: _t->setExtendedAlarmStatus_SystemConfiguration(*reinterpret_cast< quint8*>(_v)); break;
        case 22: _t->setExtendedAlarmStatus_BootFault(*reinterpret_cast< quint8*>(_v)); break;
        case 23: _t->setExtendedAlarmSubStatus_SystemConfiguration(*reinterpret_cast< quint8*>(_v)); break;
        case 24: _t->setExtendedAlarmSubStatus_BootFault(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject SystemAlarms::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_SystemAlarms.data,
    qt_meta_data_SystemAlarms,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SystemAlarms::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SystemAlarms::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SystemAlarms.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int SystemAlarms::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 85)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 85;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 85)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 85;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 25;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 25;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 25;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 25;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 25;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void SystemAlarms::AlarmChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SystemAlarms::Alarm_SystemConfigurationChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SystemAlarms::Alarm_BootFaultChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SystemAlarms::Alarm_OutOfMemoryChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SystemAlarms::Alarm_StackOverflowChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SystemAlarms::Alarm_CPUOverloadChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SystemAlarms::Alarm_EventSystemChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SystemAlarms::Alarm_TelemetryChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SystemAlarms::Alarm_ReceiverChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void SystemAlarms::Alarm_ManualControlChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void SystemAlarms::Alarm_ActuatorChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void SystemAlarms::Alarm_AttitudeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void SystemAlarms::Alarm_SensorsChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void SystemAlarms::Alarm_MagnetometerChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void SystemAlarms::Alarm_AirspeedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void SystemAlarms::Alarm_StabilizationChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void SystemAlarms::Alarm_GuidanceChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void SystemAlarms::Alarm_PathPlanChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void SystemAlarms::Alarm_BatteryChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void SystemAlarms::Alarm_FlightTimeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void SystemAlarms::Alarm_I2CChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void SystemAlarms::Alarm_GPSChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void SystemAlarms::ExtendedAlarmStatusChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void SystemAlarms::ExtendedAlarmStatus_SystemConfigurationChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void SystemAlarms::ExtendedAlarmStatus_BootFaultChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void SystemAlarms::ExtendedAlarmSubStatusChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void SystemAlarms::ExtendedAlarmSubStatus_SystemConfigurationChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void SystemAlarms::ExtendedAlarmSubStatus_BootFaultChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
