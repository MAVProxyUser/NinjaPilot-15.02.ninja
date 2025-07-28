/****************************************************************************
** Meta object code from reading C++ file 'osdsettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/osdsettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'osdsettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OsdSettings_t {
    QByteArrayData data[111];
    char stringdata0[1644];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OsdSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OsdSettings_t qt_meta_stringdata_OsdSettings = {
    {
QT_MOC_LITERAL(0, 0, 11), // "OsdSettings"
QT_MOC_LITERAL(1, 12, 20), // "AttitudeSetupChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "index"
QT_MOC_LITERAL(4, 40, 5), // "value"
QT_MOC_LITERAL(5, 46, 22), // "AttitudeSetup_XChanged"
QT_MOC_LITERAL(6, 69, 22), // "AttitudeSetup_YChanged"
QT_MOC_LITERAL(7, 92, 16), // "TimeSetupChanged"
QT_MOC_LITERAL(8, 109, 18), // "TimeSetup_XChanged"
QT_MOC_LITERAL(9, 128, 18), // "TimeSetup_YChanged"
QT_MOC_LITERAL(10, 147, 19), // "BatterySetupChanged"
QT_MOC_LITERAL(11, 167, 21), // "BatterySetup_XChanged"
QT_MOC_LITERAL(12, 189, 21), // "BatterySetup_YChanged"
QT_MOC_LITERAL(13, 211, 17), // "SpeedSetupChanged"
QT_MOC_LITERAL(14, 229, 19), // "SpeedSetup_XChanged"
QT_MOC_LITERAL(15, 249, 19), // "SpeedSetup_YChanged"
QT_MOC_LITERAL(16, 269, 20), // "AltitudeSetupChanged"
QT_MOC_LITERAL(17, 290, 22), // "AltitudeSetup_XChanged"
QT_MOC_LITERAL(18, 313, 22), // "AltitudeSetup_YChanged"
QT_MOC_LITERAL(19, 336, 19), // "HeadingSetupChanged"
QT_MOC_LITERAL(20, 356, 21), // "HeadingSetup_XChanged"
QT_MOC_LITERAL(21, 378, 21), // "HeadingSetup_YChanged"
QT_MOC_LITERAL(22, 400, 15), // "AttitudeChanged"
QT_MOC_LITERAL(23, 416, 11), // "TimeChanged"
QT_MOC_LITERAL(24, 428, 14), // "BatteryChanged"
QT_MOC_LITERAL(25, 443, 12), // "SpeedChanged"
QT_MOC_LITERAL(26, 456, 15), // "AltitudeChanged"
QT_MOC_LITERAL(27, 472, 14), // "HeadingChanged"
QT_MOC_LITERAL(28, 487, 13), // "ScreenChanged"
QT_MOC_LITERAL(29, 501, 12), // "WhiteChanged"
QT_MOC_LITERAL(30, 514, 12), // "BlackChanged"
QT_MOC_LITERAL(31, 527, 21), // "AltitudeSourceChanged"
QT_MOC_LITERAL(32, 549, 16), // "setAttitudeSetup"
QT_MOC_LITERAL(33, 566, 18), // "setAttitudeSetup_X"
QT_MOC_LITERAL(34, 585, 18), // "setAttitudeSetup_Y"
QT_MOC_LITERAL(35, 604, 12), // "setTimeSetup"
QT_MOC_LITERAL(36, 617, 14), // "setTimeSetup_X"
QT_MOC_LITERAL(37, 632, 14), // "setTimeSetup_Y"
QT_MOC_LITERAL(38, 647, 15), // "setBatterySetup"
QT_MOC_LITERAL(39, 663, 17), // "setBatterySetup_X"
QT_MOC_LITERAL(40, 681, 17), // "setBatterySetup_Y"
QT_MOC_LITERAL(41, 699, 13), // "setSpeedSetup"
QT_MOC_LITERAL(42, 713, 15), // "setSpeedSetup_X"
QT_MOC_LITERAL(43, 729, 15), // "setSpeedSetup_Y"
QT_MOC_LITERAL(44, 745, 16), // "setAltitudeSetup"
QT_MOC_LITERAL(45, 762, 18), // "setAltitudeSetup_X"
QT_MOC_LITERAL(46, 781, 18), // "setAltitudeSetup_Y"
QT_MOC_LITERAL(47, 800, 15), // "setHeadingSetup"
QT_MOC_LITERAL(48, 816, 17), // "setHeadingSetup_X"
QT_MOC_LITERAL(49, 834, 17), // "setHeadingSetup_Y"
QT_MOC_LITERAL(50, 852, 11), // "setAttitude"
QT_MOC_LITERAL(51, 864, 7), // "setTime"
QT_MOC_LITERAL(52, 872, 10), // "setBattery"
QT_MOC_LITERAL(53, 883, 8), // "setSpeed"
QT_MOC_LITERAL(54, 892, 11), // "setAltitude"
QT_MOC_LITERAL(55, 904, 10), // "setHeading"
QT_MOC_LITERAL(56, 915, 9), // "setScreen"
QT_MOC_LITERAL(57, 925, 8), // "setWhite"
QT_MOC_LITERAL(58, 934, 8), // "setBlack"
QT_MOC_LITERAL(59, 943, 17), // "setAltitudeSource"
QT_MOC_LITERAL(60, 961, 17), // "emitNotifications"
QT_MOC_LITERAL(61, 979, 16), // "getAttitudeSetup"
QT_MOC_LITERAL(62, 996, 18), // "getAttitudeSetup_X"
QT_MOC_LITERAL(63, 1015, 18), // "getAttitudeSetup_Y"
QT_MOC_LITERAL(64, 1034, 12), // "getTimeSetup"
QT_MOC_LITERAL(65, 1047, 14), // "getTimeSetup_X"
QT_MOC_LITERAL(66, 1062, 14), // "getTimeSetup_Y"
QT_MOC_LITERAL(67, 1077, 15), // "getBatterySetup"
QT_MOC_LITERAL(68, 1093, 17), // "getBatterySetup_X"
QT_MOC_LITERAL(69, 1111, 17), // "getBatterySetup_Y"
QT_MOC_LITERAL(70, 1129, 13), // "getSpeedSetup"
QT_MOC_LITERAL(71, 1143, 15), // "getSpeedSetup_X"
QT_MOC_LITERAL(72, 1159, 15), // "getSpeedSetup_Y"
QT_MOC_LITERAL(73, 1175, 16), // "getAltitudeSetup"
QT_MOC_LITERAL(74, 1192, 18), // "getAltitudeSetup_X"
QT_MOC_LITERAL(75, 1211, 18), // "getAltitudeSetup_Y"
QT_MOC_LITERAL(76, 1230, 15), // "getHeadingSetup"
QT_MOC_LITERAL(77, 1246, 17), // "getHeadingSetup_X"
QT_MOC_LITERAL(78, 1264, 17), // "getHeadingSetup_Y"
QT_MOC_LITERAL(79, 1282, 11), // "getAttitude"
QT_MOC_LITERAL(80, 1294, 7), // "getTime"
QT_MOC_LITERAL(81, 1302, 10), // "getBattery"
QT_MOC_LITERAL(82, 1313, 8), // "getSpeed"
QT_MOC_LITERAL(83, 1322, 11), // "getAltitude"
QT_MOC_LITERAL(84, 1334, 10), // "getHeading"
QT_MOC_LITERAL(85, 1345, 9), // "getScreen"
QT_MOC_LITERAL(86, 1355, 8), // "getWhite"
QT_MOC_LITERAL(87, 1364, 8), // "getBlack"
QT_MOC_LITERAL(88, 1373, 17), // "getAltitudeSource"
QT_MOC_LITERAL(89, 1391, 15), // "AttitudeSetup_X"
QT_MOC_LITERAL(90, 1407, 15), // "AttitudeSetup_Y"
QT_MOC_LITERAL(91, 1423, 11), // "TimeSetup_X"
QT_MOC_LITERAL(92, 1435, 11), // "TimeSetup_Y"
QT_MOC_LITERAL(93, 1447, 14), // "BatterySetup_X"
QT_MOC_LITERAL(94, 1462, 14), // "BatterySetup_Y"
QT_MOC_LITERAL(95, 1477, 12), // "SpeedSetup_X"
QT_MOC_LITERAL(96, 1490, 12), // "SpeedSetup_Y"
QT_MOC_LITERAL(97, 1503, 15), // "AltitudeSetup_X"
QT_MOC_LITERAL(98, 1519, 15), // "AltitudeSetup_Y"
QT_MOC_LITERAL(99, 1535, 14), // "HeadingSetup_X"
QT_MOC_LITERAL(100, 1550, 14), // "HeadingSetup_Y"
QT_MOC_LITERAL(101, 1565, 8), // "Attitude"
QT_MOC_LITERAL(102, 1574, 4), // "Time"
QT_MOC_LITERAL(103, 1579, 7), // "Battery"
QT_MOC_LITERAL(104, 1587, 5), // "Speed"
QT_MOC_LITERAL(105, 1593, 8), // "Altitude"
QT_MOC_LITERAL(106, 1602, 7), // "Heading"
QT_MOC_LITERAL(107, 1610, 6), // "Screen"
QT_MOC_LITERAL(108, 1617, 5), // "White"
QT_MOC_LITERAL(109, 1623, 5), // "Black"
QT_MOC_LITERAL(110, 1629, 14) // "AltitudeSource"

    },
    "OsdSettings\0AttitudeSetupChanged\0\0"
    "index\0value\0AttitudeSetup_XChanged\0"
    "AttitudeSetup_YChanged\0TimeSetupChanged\0"
    "TimeSetup_XChanged\0TimeSetup_YChanged\0"
    "BatterySetupChanged\0BatterySetup_XChanged\0"
    "BatterySetup_YChanged\0SpeedSetupChanged\0"
    "SpeedSetup_XChanged\0SpeedSetup_YChanged\0"
    "AltitudeSetupChanged\0AltitudeSetup_XChanged\0"
    "AltitudeSetup_YChanged\0HeadingSetupChanged\0"
    "HeadingSetup_XChanged\0HeadingSetup_YChanged\0"
    "AttitudeChanged\0TimeChanged\0BatteryChanged\0"
    "SpeedChanged\0AltitudeChanged\0"
    "HeadingChanged\0ScreenChanged\0WhiteChanged\0"
    "BlackChanged\0AltitudeSourceChanged\0"
    "setAttitudeSetup\0setAttitudeSetup_X\0"
    "setAttitudeSetup_Y\0setTimeSetup\0"
    "setTimeSetup_X\0setTimeSetup_Y\0"
    "setBatterySetup\0setBatterySetup_X\0"
    "setBatterySetup_Y\0setSpeedSetup\0"
    "setSpeedSetup_X\0setSpeedSetup_Y\0"
    "setAltitudeSetup\0setAltitudeSetup_X\0"
    "setAltitudeSetup_Y\0setHeadingSetup\0"
    "setHeadingSetup_X\0setHeadingSetup_Y\0"
    "setAttitude\0setTime\0setBattery\0setSpeed\0"
    "setAltitude\0setHeading\0setScreen\0"
    "setWhite\0setBlack\0setAltitudeSource\0"
    "emitNotifications\0getAttitudeSetup\0"
    "getAttitudeSetup_X\0getAttitudeSetup_Y\0"
    "getTimeSetup\0getTimeSetup_X\0getTimeSetup_Y\0"
    "getBatterySetup\0getBatterySetup_X\0"
    "getBatterySetup_Y\0getSpeedSetup\0"
    "getSpeedSetup_X\0getSpeedSetup_Y\0"
    "getAltitudeSetup\0getAltitudeSetup_X\0"
    "getAltitudeSetup_Y\0getHeadingSetup\0"
    "getHeadingSetup_X\0getHeadingSetup_Y\0"
    "getAttitude\0getTime\0getBattery\0getSpeed\0"
    "getAltitude\0getHeading\0getScreen\0"
    "getWhite\0getBlack\0getAltitudeSource\0"
    "AttitudeSetup_X\0AttitudeSetup_Y\0"
    "TimeSetup_X\0TimeSetup_Y\0BatterySetup_X\0"
    "BatterySetup_Y\0SpeedSetup_X\0SpeedSetup_Y\0"
    "AltitudeSetup_X\0AltitudeSetup_Y\0"
    "HeadingSetup_X\0HeadingSetup_Y\0Attitude\0"
    "Time\0Battery\0Speed\0Altitude\0Heading\0"
    "Screen\0White\0Black\0AltitudeSource"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OsdSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      85,   14, // methods
      22,  672, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      28,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  439,    2, 0x06 /* Public */,
       5,    1,  444,    2, 0x06 /* Public */,
       6,    1,  447,    2, 0x06 /* Public */,
       7,    2,  450,    2, 0x06 /* Public */,
       8,    1,  455,    2, 0x06 /* Public */,
       9,    1,  458,    2, 0x06 /* Public */,
      10,    2,  461,    2, 0x06 /* Public */,
      11,    1,  466,    2, 0x06 /* Public */,
      12,    1,  469,    2, 0x06 /* Public */,
      13,    2,  472,    2, 0x06 /* Public */,
      14,    1,  477,    2, 0x06 /* Public */,
      15,    1,  480,    2, 0x06 /* Public */,
      16,    2,  483,    2, 0x06 /* Public */,
      17,    1,  488,    2, 0x06 /* Public */,
      18,    1,  491,    2, 0x06 /* Public */,
      19,    2,  494,    2, 0x06 /* Public */,
      20,    1,  499,    2, 0x06 /* Public */,
      21,    1,  502,    2, 0x06 /* Public */,
      22,    1,  505,    2, 0x06 /* Public */,
      23,    1,  508,    2, 0x06 /* Public */,
      24,    1,  511,    2, 0x06 /* Public */,
      25,    1,  514,    2, 0x06 /* Public */,
      26,    1,  517,    2, 0x06 /* Public */,
      27,    1,  520,    2, 0x06 /* Public */,
      28,    1,  523,    2, 0x06 /* Public */,
      29,    1,  526,    2, 0x06 /* Public */,
      30,    1,  529,    2, 0x06 /* Public */,
      31,    1,  532,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      32,    2,  535,    2, 0x0a /* Public */,
      33,    1,  540,    2, 0x0a /* Public */,
      34,    1,  543,    2, 0x0a /* Public */,
      35,    2,  546,    2, 0x0a /* Public */,
      36,    1,  551,    2, 0x0a /* Public */,
      37,    1,  554,    2, 0x0a /* Public */,
      38,    2,  557,    2, 0x0a /* Public */,
      39,    1,  562,    2, 0x0a /* Public */,
      40,    1,  565,    2, 0x0a /* Public */,
      41,    2,  568,    2, 0x0a /* Public */,
      42,    1,  573,    2, 0x0a /* Public */,
      43,    1,  576,    2, 0x0a /* Public */,
      44,    2,  579,    2, 0x0a /* Public */,
      45,    1,  584,    2, 0x0a /* Public */,
      46,    1,  587,    2, 0x0a /* Public */,
      47,    2,  590,    2, 0x0a /* Public */,
      48,    1,  595,    2, 0x0a /* Public */,
      49,    1,  598,    2, 0x0a /* Public */,
      50,    1,  601,    2, 0x0a /* Public */,
      51,    1,  604,    2, 0x0a /* Public */,
      52,    1,  607,    2, 0x0a /* Public */,
      53,    1,  610,    2, 0x0a /* Public */,
      54,    1,  613,    2, 0x0a /* Public */,
      55,    1,  616,    2, 0x0a /* Public */,
      56,    1,  619,    2, 0x0a /* Public */,
      57,    1,  622,    2, 0x0a /* Public */,
      58,    1,  625,    2, 0x0a /* Public */,
      59,    1,  628,    2, 0x0a /* Public */,
      60,    0,  631,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      61,    1,  632,    2, 0x02 /* Public */,
      62,    0,  635,    2, 0x02 /* Public */,
      63,    0,  636,    2, 0x02 /* Public */,
      64,    1,  637,    2, 0x02 /* Public */,
      65,    0,  640,    2, 0x02 /* Public */,
      66,    0,  641,    2, 0x02 /* Public */,
      67,    1,  642,    2, 0x02 /* Public */,
      68,    0,  645,    2, 0x02 /* Public */,
      69,    0,  646,    2, 0x02 /* Public */,
      70,    1,  647,    2, 0x02 /* Public */,
      71,    0,  650,    2, 0x02 /* Public */,
      72,    0,  651,    2, 0x02 /* Public */,
      73,    1,  652,    2, 0x02 /* Public */,
      74,    0,  655,    2, 0x02 /* Public */,
      75,    0,  656,    2, 0x02 /* Public */,
      76,    1,  657,    2, 0x02 /* Public */,
      77,    0,  660,    2, 0x02 /* Public */,
      78,    0,  661,    2, 0x02 /* Public */,
      79,    0,  662,    2, 0x02 /* Public */,
      80,    0,  663,    2, 0x02 /* Public */,
      81,    0,  664,    2, 0x02 /* Public */,
      82,    0,  665,    2, 0x02 /* Public */,
      83,    0,  666,    2, 0x02 /* Public */,
      84,    0,  667,    2, 0x02 /* Public */,
      85,    0,  668,    2, 0x02 /* Public */,
      86,    0,  669,    2, 0x02 /* Public */,
      87,    0,  670,    2, 0x02 /* Public */,
      88,    0,  671,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
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

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
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
    QMetaType::Void,

 // methods: parameters
    QMetaType::Short, QMetaType::UInt,    3,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short, QMetaType::UInt,    3,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short, QMetaType::UInt,    3,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short, QMetaType::UInt,    3,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short, QMetaType::UInt,    3,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short, QMetaType::UInt,    3,
    QMetaType::Short,
    QMetaType::Short,
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

 // properties: name, type, flags
      89, QMetaType::Short, 0x00495103,
      90, QMetaType::Short, 0x00495103,
      91, QMetaType::Short, 0x00495103,
      92, QMetaType::Short, 0x00495103,
      93, QMetaType::Short, 0x00495103,
      94, QMetaType::Short, 0x00495103,
      95, QMetaType::Short, 0x00495103,
      96, QMetaType::Short, 0x00495103,
      97, QMetaType::Short, 0x00495103,
      98, QMetaType::Short, 0x00495103,
      99, QMetaType::Short, 0x00495103,
     100, QMetaType::Short, 0x00495103,
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

 // properties: notify_signal_id
       1,
       2,
       4,
       5,
       7,
       8,
      10,
      11,
      13,
      14,
      16,
      17,
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

       0        // eod
};

void OsdSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OsdSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->AttitudeSetupChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 1: _t->AttitudeSetup_XChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 2: _t->AttitudeSetup_YChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 3: _t->TimeSetupChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 4: _t->TimeSetup_XChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 5: _t->TimeSetup_YChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 6: _t->BatterySetupChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 7: _t->BatterySetup_XChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 8: _t->BatterySetup_YChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 9: _t->SpeedSetupChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 10: _t->SpeedSetup_XChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 11: _t->SpeedSetup_YChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 12: _t->AltitudeSetupChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 13: _t->AltitudeSetup_XChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 14: _t->AltitudeSetup_YChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 15: _t->HeadingSetupChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 16: _t->HeadingSetup_XChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 17: _t->HeadingSetup_YChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 18: _t->AttitudeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 19: _t->TimeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->BatteryChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 21: _t->SpeedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 22: _t->AltitudeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 23: _t->HeadingChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 24: _t->ScreenChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 25: _t->WhiteChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 26: _t->BlackChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 27: _t->AltitudeSourceChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 28: _t->setAttitudeSetup((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 29: _t->setAttitudeSetup_X((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 30: _t->setAttitudeSetup_Y((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 31: _t->setTimeSetup((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 32: _t->setTimeSetup_X((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 33: _t->setTimeSetup_Y((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 34: _t->setBatterySetup((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 35: _t->setBatterySetup_X((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 36: _t->setBatterySetup_Y((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 37: _t->setSpeedSetup((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 38: _t->setSpeedSetup_X((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 39: _t->setSpeedSetup_Y((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 40: _t->setAltitudeSetup((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 41: _t->setAltitudeSetup_X((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 42: _t->setAltitudeSetup_Y((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 43: _t->setHeadingSetup((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 44: _t->setHeadingSetup_X((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 45: _t->setHeadingSetup_Y((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 46: _t->setAttitude((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 47: _t->setTime((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 48: _t->setBattery((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 49: _t->setSpeed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 50: _t->setAltitude((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 51: _t->setHeading((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 52: _t->setScreen((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 53: _t->setWhite((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 54: _t->setBlack((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 55: _t->setAltitudeSource((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 56: _t->emitNotifications(); break;
        case 57: { qint16 _r = _t->getAttitudeSetup((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 58: { qint16 _r = _t->getAttitudeSetup_X();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 59: { qint16 _r = _t->getAttitudeSetup_Y();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 60: { qint16 _r = _t->getTimeSetup((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 61: { qint16 _r = _t->getTimeSetup_X();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 62: { qint16 _r = _t->getTimeSetup_Y();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 63: { qint16 _r = _t->getBatterySetup((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 64: { qint16 _r = _t->getBatterySetup_X();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 65: { qint16 _r = _t->getBatterySetup_Y();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 66: { qint16 _r = _t->getSpeedSetup((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 67: { qint16 _r = _t->getSpeedSetup_X();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 68: { qint16 _r = _t->getSpeedSetup_Y();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 69: { qint16 _r = _t->getAltitudeSetup((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 70: { qint16 _r = _t->getAltitudeSetup_X();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 71: { qint16 _r = _t->getAltitudeSetup_Y();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 72: { qint16 _r = _t->getHeadingSetup((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 73: { qint16 _r = _t->getHeadingSetup_X();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 74: { qint16 _r = _t->getHeadingSetup_Y();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 75: { quint8 _r = _t->getAttitude();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 76: { quint8 _r = _t->getTime();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 77: { quint8 _r = _t->getBattery();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 78: { quint8 _r = _t->getSpeed();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 79: { quint8 _r = _t->getAltitude();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 80: { quint8 _r = _t->getHeading();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 81: { quint8 _r = _t->getScreen();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 82: { quint8 _r = _t->getWhite();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 83: { quint8 _r = _t->getBlack();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 84: { quint8 _r = _t->getAltitudeSource();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OsdSettings::*)(quint32 , qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::AttitudeSetupChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::AttitudeSetup_XChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::AttitudeSetup_YChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint32 , qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::TimeSetupChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::TimeSetup_XChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::TimeSetup_YChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint32 , qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::BatterySetupChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::BatterySetup_XChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::BatterySetup_YChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint32 , qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::SpeedSetupChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::SpeedSetup_XChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::SpeedSetup_YChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint32 , qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::AltitudeSetupChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::AltitudeSetup_XChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::AltitudeSetup_YChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint32 , qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::HeadingSetupChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::HeadingSetup_XChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::HeadingSetup_YChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::AttitudeChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::TimeChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::BatteryChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::SpeedChanged)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::AltitudeChanged)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::HeadingChanged)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::ScreenChanged)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::WhiteChanged)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::BlackChanged)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (OsdSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OsdSettings::AltitudeSourceChanged)) {
                *result = 27;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<OsdSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qint16*>(_v) = _t->getAttitudeSetup_X(); break;
        case 1: *reinterpret_cast< qint16*>(_v) = _t->getAttitudeSetup_Y(); break;
        case 2: *reinterpret_cast< qint16*>(_v) = _t->getTimeSetup_X(); break;
        case 3: *reinterpret_cast< qint16*>(_v) = _t->getTimeSetup_Y(); break;
        case 4: *reinterpret_cast< qint16*>(_v) = _t->getBatterySetup_X(); break;
        case 5: *reinterpret_cast< qint16*>(_v) = _t->getBatterySetup_Y(); break;
        case 6: *reinterpret_cast< qint16*>(_v) = _t->getSpeedSetup_X(); break;
        case 7: *reinterpret_cast< qint16*>(_v) = _t->getSpeedSetup_Y(); break;
        case 8: *reinterpret_cast< qint16*>(_v) = _t->getAltitudeSetup_X(); break;
        case 9: *reinterpret_cast< qint16*>(_v) = _t->getAltitudeSetup_Y(); break;
        case 10: *reinterpret_cast< qint16*>(_v) = _t->getHeadingSetup_X(); break;
        case 11: *reinterpret_cast< qint16*>(_v) = _t->getHeadingSetup_Y(); break;
        case 12: *reinterpret_cast< quint8*>(_v) = _t->getAttitude(); break;
        case 13: *reinterpret_cast< quint8*>(_v) = _t->getTime(); break;
        case 14: *reinterpret_cast< quint8*>(_v) = _t->getBattery(); break;
        case 15: *reinterpret_cast< quint8*>(_v) = _t->getSpeed(); break;
        case 16: *reinterpret_cast< quint8*>(_v) = _t->getAltitude(); break;
        case 17: *reinterpret_cast< quint8*>(_v) = _t->getHeading(); break;
        case 18: *reinterpret_cast< quint8*>(_v) = _t->getScreen(); break;
        case 19: *reinterpret_cast< quint8*>(_v) = _t->getWhite(); break;
        case 20: *reinterpret_cast< quint8*>(_v) = _t->getBlack(); break;
        case 21: *reinterpret_cast< quint8*>(_v) = _t->getAltitudeSource(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<OsdSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAttitudeSetup_X(*reinterpret_cast< qint16*>(_v)); break;
        case 1: _t->setAttitudeSetup_Y(*reinterpret_cast< qint16*>(_v)); break;
        case 2: _t->setTimeSetup_X(*reinterpret_cast< qint16*>(_v)); break;
        case 3: _t->setTimeSetup_Y(*reinterpret_cast< qint16*>(_v)); break;
        case 4: _t->setBatterySetup_X(*reinterpret_cast< qint16*>(_v)); break;
        case 5: _t->setBatterySetup_Y(*reinterpret_cast< qint16*>(_v)); break;
        case 6: _t->setSpeedSetup_X(*reinterpret_cast< qint16*>(_v)); break;
        case 7: _t->setSpeedSetup_Y(*reinterpret_cast< qint16*>(_v)); break;
        case 8: _t->setAltitudeSetup_X(*reinterpret_cast< qint16*>(_v)); break;
        case 9: _t->setAltitudeSetup_Y(*reinterpret_cast< qint16*>(_v)); break;
        case 10: _t->setHeadingSetup_X(*reinterpret_cast< qint16*>(_v)); break;
        case 11: _t->setHeadingSetup_Y(*reinterpret_cast< qint16*>(_v)); break;
        case 12: _t->setAttitude(*reinterpret_cast< quint8*>(_v)); break;
        case 13: _t->setTime(*reinterpret_cast< quint8*>(_v)); break;
        case 14: _t->setBattery(*reinterpret_cast< quint8*>(_v)); break;
        case 15: _t->setSpeed(*reinterpret_cast< quint8*>(_v)); break;
        case 16: _t->setAltitude(*reinterpret_cast< quint8*>(_v)); break;
        case 17: _t->setHeading(*reinterpret_cast< quint8*>(_v)); break;
        case 18: _t->setScreen(*reinterpret_cast< quint8*>(_v)); break;
        case 19: _t->setWhite(*reinterpret_cast< quint8*>(_v)); break;
        case 20: _t->setBlack(*reinterpret_cast< quint8*>(_v)); break;
        case 21: _t->setAltitudeSource(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject OsdSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_OsdSettings.data,
    qt_meta_data_OsdSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OsdSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OsdSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OsdSettings.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int OsdSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 22;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void OsdSettings::AttitudeSetupChanged(quint32 _t1, qint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OsdSettings::AttitudeSetup_XChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OsdSettings::AttitudeSetup_YChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void OsdSettings::TimeSetupChanged(quint32 _t1, qint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void OsdSettings::TimeSetup_XChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void OsdSettings::TimeSetup_YChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void OsdSettings::BatterySetupChanged(quint32 _t1, qint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void OsdSettings::BatterySetup_XChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void OsdSettings::BatterySetup_YChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void OsdSettings::SpeedSetupChanged(quint32 _t1, qint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void OsdSettings::SpeedSetup_XChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void OsdSettings::SpeedSetup_YChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void OsdSettings::AltitudeSetupChanged(quint32 _t1, qint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void OsdSettings::AltitudeSetup_XChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void OsdSettings::AltitudeSetup_YChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void OsdSettings::HeadingSetupChanged(quint32 _t1, qint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void OsdSettings::HeadingSetup_XChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void OsdSettings::HeadingSetup_YChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void OsdSettings::AttitudeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void OsdSettings::TimeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void OsdSettings::BatteryChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void OsdSettings::SpeedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void OsdSettings::AltitudeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void OsdSettings::HeadingChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void OsdSettings::ScreenChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void OsdSettings::WhiteChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void OsdSettings::BlackChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void OsdSettings::AltitudeSourceChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
