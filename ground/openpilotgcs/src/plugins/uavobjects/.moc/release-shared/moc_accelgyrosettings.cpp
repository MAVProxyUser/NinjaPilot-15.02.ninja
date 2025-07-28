/****************************************************************************
** Meta object code from reading C++ file 'accelgyrosettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/accelgyrosettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'accelgyrosettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AccelGyroSettings_t {
    QByteArrayData data[118];
    char stringdata0[2251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AccelGyroSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AccelGyroSettings_t qt_meta_stringdata_AccelGyroSettings = {
    {
QT_MOC_LITERAL(0, 0, 17), // "AccelGyroSettings"
QT_MOC_LITERAL(1, 18, 17), // "accel_biasChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 5), // "index"
QT_MOC_LITERAL(4, 43, 5), // "value"
QT_MOC_LITERAL(5, 49, 19), // "accel_bias_XChanged"
QT_MOC_LITERAL(6, 69, 19), // "accel_bias_YChanged"
QT_MOC_LITERAL(7, 89, 19), // "accel_bias_ZChanged"
QT_MOC_LITERAL(8, 109, 18), // "accel_scaleChanged"
QT_MOC_LITERAL(9, 128, 20), // "accel_scale_XChanged"
QT_MOC_LITERAL(10, 149, 20), // "accel_scale_YChanged"
QT_MOC_LITERAL(11, 170, 20), // "accel_scale_ZChanged"
QT_MOC_LITERAL(12, 191, 23), // "accel_temp_coeffChanged"
QT_MOC_LITERAL(13, 215, 25), // "accel_temp_coeff_XChanged"
QT_MOC_LITERAL(14, 241, 25), // "accel_temp_coeff_YChanged"
QT_MOC_LITERAL(15, 267, 25), // "accel_temp_coeff_ZChanged"
QT_MOC_LITERAL(16, 293, 16), // "gyro_biasChanged"
QT_MOC_LITERAL(17, 310, 18), // "gyro_bias_XChanged"
QT_MOC_LITERAL(18, 329, 18), // "gyro_bias_YChanged"
QT_MOC_LITERAL(19, 348, 18), // "gyro_bias_ZChanged"
QT_MOC_LITERAL(20, 367, 17), // "gyro_scaleChanged"
QT_MOC_LITERAL(21, 385, 19), // "gyro_scale_XChanged"
QT_MOC_LITERAL(22, 405, 19), // "gyro_scale_YChanged"
QT_MOC_LITERAL(23, 425, 19), // "gyro_scale_ZChanged"
QT_MOC_LITERAL(24, 445, 22), // "gyro_temp_coeffChanged"
QT_MOC_LITERAL(25, 468, 24), // "gyro_temp_coeff_XChanged"
QT_MOC_LITERAL(26, 493, 25), // "gyro_temp_coeff_X2Changed"
QT_MOC_LITERAL(27, 519, 24), // "gyro_temp_coeff_YChanged"
QT_MOC_LITERAL(28, 544, 25), // "gyro_temp_coeff_Y2Changed"
QT_MOC_LITERAL(29, 570, 24), // "gyro_temp_coeff_ZChanged"
QT_MOC_LITERAL(30, 595, 25), // "gyro_temp_coeff_Z2Changed"
QT_MOC_LITERAL(31, 621, 29), // "temp_calibrated_extentChanged"
QT_MOC_LITERAL(32, 651, 33), // "temp_calibrated_extent_minCha..."
QT_MOC_LITERAL(33, 685, 33), // "temp_calibrated_extent_maxCha..."
QT_MOC_LITERAL(34, 719, 13), // "setaccel_bias"
QT_MOC_LITERAL(35, 733, 15), // "setaccel_bias_X"
QT_MOC_LITERAL(36, 749, 15), // "setaccel_bias_Y"
QT_MOC_LITERAL(37, 765, 15), // "setaccel_bias_Z"
QT_MOC_LITERAL(38, 781, 14), // "setaccel_scale"
QT_MOC_LITERAL(39, 796, 16), // "setaccel_scale_X"
QT_MOC_LITERAL(40, 813, 16), // "setaccel_scale_Y"
QT_MOC_LITERAL(41, 830, 16), // "setaccel_scale_Z"
QT_MOC_LITERAL(42, 847, 19), // "setaccel_temp_coeff"
QT_MOC_LITERAL(43, 867, 21), // "setaccel_temp_coeff_X"
QT_MOC_LITERAL(44, 889, 21), // "setaccel_temp_coeff_Y"
QT_MOC_LITERAL(45, 911, 21), // "setaccel_temp_coeff_Z"
QT_MOC_LITERAL(46, 933, 12), // "setgyro_bias"
QT_MOC_LITERAL(47, 946, 14), // "setgyro_bias_X"
QT_MOC_LITERAL(48, 961, 14), // "setgyro_bias_Y"
QT_MOC_LITERAL(49, 976, 14), // "setgyro_bias_Z"
QT_MOC_LITERAL(50, 991, 13), // "setgyro_scale"
QT_MOC_LITERAL(51, 1005, 15), // "setgyro_scale_X"
QT_MOC_LITERAL(52, 1021, 15), // "setgyro_scale_Y"
QT_MOC_LITERAL(53, 1037, 15), // "setgyro_scale_Z"
QT_MOC_LITERAL(54, 1053, 18), // "setgyro_temp_coeff"
QT_MOC_LITERAL(55, 1072, 20), // "setgyro_temp_coeff_X"
QT_MOC_LITERAL(56, 1093, 21), // "setgyro_temp_coeff_X2"
QT_MOC_LITERAL(57, 1115, 20), // "setgyro_temp_coeff_Y"
QT_MOC_LITERAL(58, 1136, 21), // "setgyro_temp_coeff_Y2"
QT_MOC_LITERAL(59, 1158, 20), // "setgyro_temp_coeff_Z"
QT_MOC_LITERAL(60, 1179, 21), // "setgyro_temp_coeff_Z2"
QT_MOC_LITERAL(61, 1201, 25), // "settemp_calibrated_extent"
QT_MOC_LITERAL(62, 1227, 29), // "settemp_calibrated_extent_min"
QT_MOC_LITERAL(63, 1257, 29), // "settemp_calibrated_extent_max"
QT_MOC_LITERAL(64, 1287, 17), // "emitNotifications"
QT_MOC_LITERAL(65, 1305, 13), // "getaccel_bias"
QT_MOC_LITERAL(66, 1319, 15), // "getaccel_bias_X"
QT_MOC_LITERAL(67, 1335, 15), // "getaccel_bias_Y"
QT_MOC_LITERAL(68, 1351, 15), // "getaccel_bias_Z"
QT_MOC_LITERAL(69, 1367, 14), // "getaccel_scale"
QT_MOC_LITERAL(70, 1382, 16), // "getaccel_scale_X"
QT_MOC_LITERAL(71, 1399, 16), // "getaccel_scale_Y"
QT_MOC_LITERAL(72, 1416, 16), // "getaccel_scale_Z"
QT_MOC_LITERAL(73, 1433, 19), // "getaccel_temp_coeff"
QT_MOC_LITERAL(74, 1453, 21), // "getaccel_temp_coeff_X"
QT_MOC_LITERAL(75, 1475, 21), // "getaccel_temp_coeff_Y"
QT_MOC_LITERAL(76, 1497, 21), // "getaccel_temp_coeff_Z"
QT_MOC_LITERAL(77, 1519, 12), // "getgyro_bias"
QT_MOC_LITERAL(78, 1532, 14), // "getgyro_bias_X"
QT_MOC_LITERAL(79, 1547, 14), // "getgyro_bias_Y"
QT_MOC_LITERAL(80, 1562, 14), // "getgyro_bias_Z"
QT_MOC_LITERAL(81, 1577, 13), // "getgyro_scale"
QT_MOC_LITERAL(82, 1591, 15), // "getgyro_scale_X"
QT_MOC_LITERAL(83, 1607, 15), // "getgyro_scale_Y"
QT_MOC_LITERAL(84, 1623, 15), // "getgyro_scale_Z"
QT_MOC_LITERAL(85, 1639, 18), // "getgyro_temp_coeff"
QT_MOC_LITERAL(86, 1658, 20), // "getgyro_temp_coeff_X"
QT_MOC_LITERAL(87, 1679, 21), // "getgyro_temp_coeff_X2"
QT_MOC_LITERAL(88, 1701, 20), // "getgyro_temp_coeff_Y"
QT_MOC_LITERAL(89, 1722, 21), // "getgyro_temp_coeff_Y2"
QT_MOC_LITERAL(90, 1744, 20), // "getgyro_temp_coeff_Z"
QT_MOC_LITERAL(91, 1765, 21), // "getgyro_temp_coeff_Z2"
QT_MOC_LITERAL(92, 1787, 25), // "gettemp_calibrated_extent"
QT_MOC_LITERAL(93, 1813, 29), // "gettemp_calibrated_extent_min"
QT_MOC_LITERAL(94, 1843, 29), // "gettemp_calibrated_extent_max"
QT_MOC_LITERAL(95, 1873, 12), // "accel_bias_X"
QT_MOC_LITERAL(96, 1886, 12), // "accel_bias_Y"
QT_MOC_LITERAL(97, 1899, 12), // "accel_bias_Z"
QT_MOC_LITERAL(98, 1912, 13), // "accel_scale_X"
QT_MOC_LITERAL(99, 1926, 13), // "accel_scale_Y"
QT_MOC_LITERAL(100, 1940, 13), // "accel_scale_Z"
QT_MOC_LITERAL(101, 1954, 18), // "accel_temp_coeff_X"
QT_MOC_LITERAL(102, 1973, 18), // "accel_temp_coeff_Y"
QT_MOC_LITERAL(103, 1992, 18), // "accel_temp_coeff_Z"
QT_MOC_LITERAL(104, 2011, 11), // "gyro_bias_X"
QT_MOC_LITERAL(105, 2023, 11), // "gyro_bias_Y"
QT_MOC_LITERAL(106, 2035, 11), // "gyro_bias_Z"
QT_MOC_LITERAL(107, 2047, 12), // "gyro_scale_X"
QT_MOC_LITERAL(108, 2060, 12), // "gyro_scale_Y"
QT_MOC_LITERAL(109, 2073, 12), // "gyro_scale_Z"
QT_MOC_LITERAL(110, 2086, 17), // "gyro_temp_coeff_X"
QT_MOC_LITERAL(111, 2104, 18), // "gyro_temp_coeff_X2"
QT_MOC_LITERAL(112, 2123, 17), // "gyro_temp_coeff_Y"
QT_MOC_LITERAL(113, 2141, 18), // "gyro_temp_coeff_Y2"
QT_MOC_LITERAL(114, 2160, 17), // "gyro_temp_coeff_Z"
QT_MOC_LITERAL(115, 2178, 18), // "gyro_temp_coeff_Z2"
QT_MOC_LITERAL(116, 2197, 26), // "temp_calibrated_extent_min"
QT_MOC_LITERAL(117, 2224, 26) // "temp_calibrated_extent_max"

    },
    "AccelGyroSettings\0accel_biasChanged\0"
    "\0index\0value\0accel_bias_XChanged\0"
    "accel_bias_YChanged\0accel_bias_ZChanged\0"
    "accel_scaleChanged\0accel_scale_XChanged\0"
    "accel_scale_YChanged\0accel_scale_ZChanged\0"
    "accel_temp_coeffChanged\0"
    "accel_temp_coeff_XChanged\0"
    "accel_temp_coeff_YChanged\0"
    "accel_temp_coeff_ZChanged\0gyro_biasChanged\0"
    "gyro_bias_XChanged\0gyro_bias_YChanged\0"
    "gyro_bias_ZChanged\0gyro_scaleChanged\0"
    "gyro_scale_XChanged\0gyro_scale_YChanged\0"
    "gyro_scale_ZChanged\0gyro_temp_coeffChanged\0"
    "gyro_temp_coeff_XChanged\0"
    "gyro_temp_coeff_X2Changed\0"
    "gyro_temp_coeff_YChanged\0"
    "gyro_temp_coeff_Y2Changed\0"
    "gyro_temp_coeff_ZChanged\0"
    "gyro_temp_coeff_Z2Changed\0"
    "temp_calibrated_extentChanged\0"
    "temp_calibrated_extent_minChanged\0"
    "temp_calibrated_extent_maxChanged\0"
    "setaccel_bias\0setaccel_bias_X\0"
    "setaccel_bias_Y\0setaccel_bias_Z\0"
    "setaccel_scale\0setaccel_scale_X\0"
    "setaccel_scale_Y\0setaccel_scale_Z\0"
    "setaccel_temp_coeff\0setaccel_temp_coeff_X\0"
    "setaccel_temp_coeff_Y\0setaccel_temp_coeff_Z\0"
    "setgyro_bias\0setgyro_bias_X\0setgyro_bias_Y\0"
    "setgyro_bias_Z\0setgyro_scale\0"
    "setgyro_scale_X\0setgyro_scale_Y\0"
    "setgyro_scale_Z\0setgyro_temp_coeff\0"
    "setgyro_temp_coeff_X\0setgyro_temp_coeff_X2\0"
    "setgyro_temp_coeff_Y\0setgyro_temp_coeff_Y2\0"
    "setgyro_temp_coeff_Z\0setgyro_temp_coeff_Z2\0"
    "settemp_calibrated_extent\0"
    "settemp_calibrated_extent_min\0"
    "settemp_calibrated_extent_max\0"
    "emitNotifications\0getaccel_bias\0"
    "getaccel_bias_X\0getaccel_bias_Y\0"
    "getaccel_bias_Z\0getaccel_scale\0"
    "getaccel_scale_X\0getaccel_scale_Y\0"
    "getaccel_scale_Z\0getaccel_temp_coeff\0"
    "getaccel_temp_coeff_X\0getaccel_temp_coeff_Y\0"
    "getaccel_temp_coeff_Z\0getgyro_bias\0"
    "getgyro_bias_X\0getgyro_bias_Y\0"
    "getgyro_bias_Z\0getgyro_scale\0"
    "getgyro_scale_X\0getgyro_scale_Y\0"
    "getgyro_scale_Z\0getgyro_temp_coeff\0"
    "getgyro_temp_coeff_X\0getgyro_temp_coeff_X2\0"
    "getgyro_temp_coeff_Y\0getgyro_temp_coeff_Y2\0"
    "getgyro_temp_coeff_Z\0getgyro_temp_coeff_Z2\0"
    "gettemp_calibrated_extent\0"
    "gettemp_calibrated_extent_min\0"
    "gettemp_calibrated_extent_max\0"
    "accel_bias_X\0accel_bias_Y\0accel_bias_Z\0"
    "accel_scale_X\0accel_scale_Y\0accel_scale_Z\0"
    "accel_temp_coeff_X\0accel_temp_coeff_Y\0"
    "accel_temp_coeff_Z\0gyro_bias_X\0"
    "gyro_bias_Y\0gyro_bias_Z\0gyro_scale_X\0"
    "gyro_scale_Y\0gyro_scale_Z\0gyro_temp_coeff_X\0"
    "gyro_temp_coeff_X2\0gyro_temp_coeff_Y\0"
    "gyro_temp_coeff_Y2\0gyro_temp_coeff_Z\0"
    "gyro_temp_coeff_Z2\0temp_calibrated_extent_min\0"
    "temp_calibrated_extent_max"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AccelGyroSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      91,   14, // methods
      23,  722, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      30,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  469,    2, 0x06 /* Public */,
       5,    1,  474,    2, 0x06 /* Public */,
       6,    1,  477,    2, 0x06 /* Public */,
       7,    1,  480,    2, 0x06 /* Public */,
       8,    2,  483,    2, 0x06 /* Public */,
       9,    1,  488,    2, 0x06 /* Public */,
      10,    1,  491,    2, 0x06 /* Public */,
      11,    1,  494,    2, 0x06 /* Public */,
      12,    2,  497,    2, 0x06 /* Public */,
      13,    1,  502,    2, 0x06 /* Public */,
      14,    1,  505,    2, 0x06 /* Public */,
      15,    1,  508,    2, 0x06 /* Public */,
      16,    2,  511,    2, 0x06 /* Public */,
      17,    1,  516,    2, 0x06 /* Public */,
      18,    1,  519,    2, 0x06 /* Public */,
      19,    1,  522,    2, 0x06 /* Public */,
      20,    2,  525,    2, 0x06 /* Public */,
      21,    1,  530,    2, 0x06 /* Public */,
      22,    1,  533,    2, 0x06 /* Public */,
      23,    1,  536,    2, 0x06 /* Public */,
      24,    2,  539,    2, 0x06 /* Public */,
      25,    1,  544,    2, 0x06 /* Public */,
      26,    1,  547,    2, 0x06 /* Public */,
      27,    1,  550,    2, 0x06 /* Public */,
      28,    1,  553,    2, 0x06 /* Public */,
      29,    1,  556,    2, 0x06 /* Public */,
      30,    1,  559,    2, 0x06 /* Public */,
      31,    2,  562,    2, 0x06 /* Public */,
      32,    1,  567,    2, 0x06 /* Public */,
      33,    1,  570,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      34,    2,  573,    2, 0x0a /* Public */,
      35,    1,  578,    2, 0x0a /* Public */,
      36,    1,  581,    2, 0x0a /* Public */,
      37,    1,  584,    2, 0x0a /* Public */,
      38,    2,  587,    2, 0x0a /* Public */,
      39,    1,  592,    2, 0x0a /* Public */,
      40,    1,  595,    2, 0x0a /* Public */,
      41,    1,  598,    2, 0x0a /* Public */,
      42,    2,  601,    2, 0x0a /* Public */,
      43,    1,  606,    2, 0x0a /* Public */,
      44,    1,  609,    2, 0x0a /* Public */,
      45,    1,  612,    2, 0x0a /* Public */,
      46,    2,  615,    2, 0x0a /* Public */,
      47,    1,  620,    2, 0x0a /* Public */,
      48,    1,  623,    2, 0x0a /* Public */,
      49,    1,  626,    2, 0x0a /* Public */,
      50,    2,  629,    2, 0x0a /* Public */,
      51,    1,  634,    2, 0x0a /* Public */,
      52,    1,  637,    2, 0x0a /* Public */,
      53,    1,  640,    2, 0x0a /* Public */,
      54,    2,  643,    2, 0x0a /* Public */,
      55,    1,  648,    2, 0x0a /* Public */,
      56,    1,  651,    2, 0x0a /* Public */,
      57,    1,  654,    2, 0x0a /* Public */,
      58,    1,  657,    2, 0x0a /* Public */,
      59,    1,  660,    2, 0x0a /* Public */,
      60,    1,  663,    2, 0x0a /* Public */,
      61,    2,  666,    2, 0x0a /* Public */,
      62,    1,  671,    2, 0x0a /* Public */,
      63,    1,  674,    2, 0x0a /* Public */,
      64,    0,  677,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      65,    1,  678,    2, 0x02 /* Public */,
      66,    0,  681,    2, 0x02 /* Public */,
      67,    0,  682,    2, 0x02 /* Public */,
      68,    0,  683,    2, 0x02 /* Public */,
      69,    1,  684,    2, 0x02 /* Public */,
      70,    0,  687,    2, 0x02 /* Public */,
      71,    0,  688,    2, 0x02 /* Public */,
      72,    0,  689,    2, 0x02 /* Public */,
      73,    1,  690,    2, 0x02 /* Public */,
      74,    0,  693,    2, 0x02 /* Public */,
      75,    0,  694,    2, 0x02 /* Public */,
      76,    0,  695,    2, 0x02 /* Public */,
      77,    1,  696,    2, 0x02 /* Public */,
      78,    0,  699,    2, 0x02 /* Public */,
      79,    0,  700,    2, 0x02 /* Public */,
      80,    0,  701,    2, 0x02 /* Public */,
      81,    1,  702,    2, 0x02 /* Public */,
      82,    0,  705,    2, 0x02 /* Public */,
      83,    0,  706,    2, 0x02 /* Public */,
      84,    0,  707,    2, 0x02 /* Public */,
      85,    1,  708,    2, 0x02 /* Public */,
      86,    0,  711,    2, 0x02 /* Public */,
      87,    0,  712,    2, 0x02 /* Public */,
      88,    0,  713,    2, 0x02 /* Public */,
      89,    0,  714,    2, 0x02 /* Public */,
      90,    0,  715,    2, 0x02 /* Public */,
      91,    0,  716,    2, 0x02 /* Public */,
      92,    1,  717,    2, 0x02 /* Public */,
      93,    0,  720,    2, 0x02 /* Public */,
      94,    0,  721,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,

 // properties: name, type, flags
      95, QMetaType::Float, 0x00495003,
      96, QMetaType::Float, 0x00495003,
      97, QMetaType::Float, 0x00495003,
      98, QMetaType::Float, 0x00495003,
      99, QMetaType::Float, 0x00495003,
     100, QMetaType::Float, 0x00495003,
     101, QMetaType::Float, 0x00495003,
     102, QMetaType::Float, 0x00495003,
     103, QMetaType::Float, 0x00495003,
     104, QMetaType::Float, 0x00495003,
     105, QMetaType::Float, 0x00495003,
     106, QMetaType::Float, 0x00495003,
     107, QMetaType::Float, 0x00495003,
     108, QMetaType::Float, 0x00495003,
     109, QMetaType::Float, 0x00495003,
     110, QMetaType::Float, 0x00495003,
     111, QMetaType::Float, 0x00495003,
     112, QMetaType::Float, 0x00495003,
     113, QMetaType::Float, 0x00495003,
     114, QMetaType::Float, 0x00495003,
     115, QMetaType::Float, 0x00495003,
     116, QMetaType::Float, 0x00495003,
     117, QMetaType::Float, 0x00495003,

 // properties: notify_signal_id
       1,
       2,
       3,
       5,
       6,
       7,
       9,
      10,
      11,
      13,
      14,
      15,
      17,
      18,
      19,
      21,
      22,
      23,
      24,
      25,
      26,
      28,
      29,

       0        // eod
};

void AccelGyroSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AccelGyroSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->accel_biasChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->accel_bias_XChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->accel_bias_YChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->accel_bias_ZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->accel_scaleChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->accel_scale_XChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->accel_scale_YChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->accel_scale_ZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->accel_temp_coeffChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 9: _t->accel_temp_coeff_XChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->accel_temp_coeff_YChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->accel_temp_coeff_ZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->gyro_biasChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 13: _t->gyro_bias_XChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->gyro_bias_YChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->gyro_bias_ZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->gyro_scaleChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 17: _t->gyro_scale_XChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->gyro_scale_YChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->gyro_scale_ZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->gyro_temp_coeffChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 21: _t->gyro_temp_coeff_XChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: _t->gyro_temp_coeff_X2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->gyro_temp_coeff_YChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->gyro_temp_coeff_Y2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 25: _t->gyro_temp_coeff_ZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 26: _t->gyro_temp_coeff_Z2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->temp_calibrated_extentChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 28: _t->temp_calibrated_extent_minChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 29: _t->temp_calibrated_extent_maxChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 30: _t->setaccel_bias((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 31: _t->setaccel_bias_X((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 32: _t->setaccel_bias_Y((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 33: _t->setaccel_bias_Z((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 34: _t->setaccel_scale((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 35: _t->setaccel_scale_X((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 36: _t->setaccel_scale_Y((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 37: _t->setaccel_scale_Z((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 38: _t->setaccel_temp_coeff((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 39: _t->setaccel_temp_coeff_X((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 40: _t->setaccel_temp_coeff_Y((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 41: _t->setaccel_temp_coeff_Z((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 42: _t->setgyro_bias((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 43: _t->setgyro_bias_X((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 44: _t->setgyro_bias_Y((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 45: _t->setgyro_bias_Z((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 46: _t->setgyro_scale((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 47: _t->setgyro_scale_X((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 48: _t->setgyro_scale_Y((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 49: _t->setgyro_scale_Z((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 50: _t->setgyro_temp_coeff((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 51: _t->setgyro_temp_coeff_X((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 52: _t->setgyro_temp_coeff_X2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 53: _t->setgyro_temp_coeff_Y((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 54: _t->setgyro_temp_coeff_Y2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 55: _t->setgyro_temp_coeff_Z((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 56: _t->setgyro_temp_coeff_Z2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 57: _t->settemp_calibrated_extent((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 58: _t->settemp_calibrated_extent_min((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 59: _t->settemp_calibrated_extent_max((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 60: _t->emitNotifications(); break;
        case 61: { float _r = _t->getaccel_bias((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 62: { float _r = _t->getaccel_bias_X();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 63: { float _r = _t->getaccel_bias_Y();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 64: { float _r = _t->getaccel_bias_Z();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 65: { float _r = _t->getaccel_scale((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 66: { float _r = _t->getaccel_scale_X();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 67: { float _r = _t->getaccel_scale_Y();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 68: { float _r = _t->getaccel_scale_Z();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 69: { float _r = _t->getaccel_temp_coeff((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 70: { float _r = _t->getaccel_temp_coeff_X();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 71: { float _r = _t->getaccel_temp_coeff_Y();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 72: { float _r = _t->getaccel_temp_coeff_Z();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 73: { float _r = _t->getgyro_bias((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 74: { float _r = _t->getgyro_bias_X();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 75: { float _r = _t->getgyro_bias_Y();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 76: { float _r = _t->getgyro_bias_Z();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 77: { float _r = _t->getgyro_scale((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 78: { float _r = _t->getgyro_scale_X();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 79: { float _r = _t->getgyro_scale_Y();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 80: { float _r = _t->getgyro_scale_Z();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 81: { float _r = _t->getgyro_temp_coeff((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 82: { float _r = _t->getgyro_temp_coeff_X();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 83: { float _r = _t->getgyro_temp_coeff_X2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 84: { float _r = _t->getgyro_temp_coeff_Y();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 85: { float _r = _t->getgyro_temp_coeff_Y2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 86: { float _r = _t->getgyro_temp_coeff_Z();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 87: { float _r = _t->getgyro_temp_coeff_Z2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 88: { float _r = _t->gettemp_calibrated_extent((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 89: { float _r = _t->gettemp_calibrated_extent_min();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 90: { float _r = _t->gettemp_calibrated_extent_max();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AccelGyroSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::accel_biasChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::accel_bias_XChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::accel_bias_YChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::accel_bias_ZChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::accel_scaleChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::accel_scale_XChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::accel_scale_YChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::accel_scale_ZChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::accel_temp_coeffChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::accel_temp_coeff_XChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::accel_temp_coeff_YChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::accel_temp_coeff_ZChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_biasChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_bias_XChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_bias_YChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_bias_ZChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_scaleChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_scale_XChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_scale_YChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_scale_ZChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_temp_coeffChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_temp_coeff_XChanged)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_temp_coeff_X2Changed)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_temp_coeff_YChanged)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_temp_coeff_Y2Changed)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_temp_coeff_ZChanged)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::gyro_temp_coeff_Z2Changed)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::temp_calibrated_extentChanged)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::temp_calibrated_extent_minChanged)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (AccelGyroSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AccelGyroSettings::temp_calibrated_extent_maxChanged)) {
                *result = 29;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AccelGyroSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getaccel_bias_X(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getaccel_bias_Y(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getaccel_bias_Z(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getaccel_scale_X(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getaccel_scale_Y(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getaccel_scale_Z(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getaccel_temp_coeff_X(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getaccel_temp_coeff_Y(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getaccel_temp_coeff_Z(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->getgyro_bias_X(); break;
        case 10: *reinterpret_cast< float*>(_v) = _t->getgyro_bias_Y(); break;
        case 11: *reinterpret_cast< float*>(_v) = _t->getgyro_bias_Z(); break;
        case 12: *reinterpret_cast< float*>(_v) = _t->getgyro_scale_X(); break;
        case 13: *reinterpret_cast< float*>(_v) = _t->getgyro_scale_Y(); break;
        case 14: *reinterpret_cast< float*>(_v) = _t->getgyro_scale_Z(); break;
        case 15: *reinterpret_cast< float*>(_v) = _t->getgyro_temp_coeff_X(); break;
        case 16: *reinterpret_cast< float*>(_v) = _t->getgyro_temp_coeff_X2(); break;
        case 17: *reinterpret_cast< float*>(_v) = _t->getgyro_temp_coeff_Y(); break;
        case 18: *reinterpret_cast< float*>(_v) = _t->getgyro_temp_coeff_Y2(); break;
        case 19: *reinterpret_cast< float*>(_v) = _t->getgyro_temp_coeff_Z(); break;
        case 20: *reinterpret_cast< float*>(_v) = _t->getgyro_temp_coeff_Z2(); break;
        case 21: *reinterpret_cast< float*>(_v) = _t->gettemp_calibrated_extent_min(); break;
        case 22: *reinterpret_cast< float*>(_v) = _t->gettemp_calibrated_extent_max(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<AccelGyroSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setaccel_bias_X(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setaccel_bias_Y(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setaccel_bias_Z(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setaccel_scale_X(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setaccel_scale_Y(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setaccel_scale_Z(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setaccel_temp_coeff_X(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setaccel_temp_coeff_Y(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setaccel_temp_coeff_Z(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setgyro_bias_X(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setgyro_bias_Y(*reinterpret_cast< float*>(_v)); break;
        case 11: _t->setgyro_bias_Z(*reinterpret_cast< float*>(_v)); break;
        case 12: _t->setgyro_scale_X(*reinterpret_cast< float*>(_v)); break;
        case 13: _t->setgyro_scale_Y(*reinterpret_cast< float*>(_v)); break;
        case 14: _t->setgyro_scale_Z(*reinterpret_cast< float*>(_v)); break;
        case 15: _t->setgyro_temp_coeff_X(*reinterpret_cast< float*>(_v)); break;
        case 16: _t->setgyro_temp_coeff_X2(*reinterpret_cast< float*>(_v)); break;
        case 17: _t->setgyro_temp_coeff_Y(*reinterpret_cast< float*>(_v)); break;
        case 18: _t->setgyro_temp_coeff_Y2(*reinterpret_cast< float*>(_v)); break;
        case 19: _t->setgyro_temp_coeff_Z(*reinterpret_cast< float*>(_v)); break;
        case 20: _t->setgyro_temp_coeff_Z2(*reinterpret_cast< float*>(_v)); break;
        case 21: _t->settemp_calibrated_extent_min(*reinterpret_cast< float*>(_v)); break;
        case 22: _t->settemp_calibrated_extent_max(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject AccelGyroSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_AccelGyroSettings.data,
    qt_meta_data_AccelGyroSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AccelGyroSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AccelGyroSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AccelGyroSettings.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int AccelGyroSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 91)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 91;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 91)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 91;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 23;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 23;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 23;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 23;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 23;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AccelGyroSettings::accel_biasChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AccelGyroSettings::accel_bias_XChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AccelGyroSettings::accel_bias_YChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AccelGyroSettings::accel_bias_ZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AccelGyroSettings::accel_scaleChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AccelGyroSettings::accel_scale_XChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AccelGyroSettings::accel_scale_YChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AccelGyroSettings::accel_scale_ZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AccelGyroSettings::accel_temp_coeffChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void AccelGyroSettings::accel_temp_coeff_XChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void AccelGyroSettings::accel_temp_coeff_YChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void AccelGyroSettings::accel_temp_coeff_ZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void AccelGyroSettings::gyro_biasChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void AccelGyroSettings::gyro_bias_XChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void AccelGyroSettings::gyro_bias_YChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void AccelGyroSettings::gyro_bias_ZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void AccelGyroSettings::gyro_scaleChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void AccelGyroSettings::gyro_scale_XChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void AccelGyroSettings::gyro_scale_YChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void AccelGyroSettings::gyro_scale_ZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void AccelGyroSettings::gyro_temp_coeffChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void AccelGyroSettings::gyro_temp_coeff_XChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void AccelGyroSettings::gyro_temp_coeff_X2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void AccelGyroSettings::gyro_temp_coeff_YChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void AccelGyroSettings::gyro_temp_coeff_Y2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void AccelGyroSettings::gyro_temp_coeff_ZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void AccelGyroSettings::gyro_temp_coeff_Z2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void AccelGyroSettings::temp_calibrated_extentChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void AccelGyroSettings::temp_calibrated_extent_minChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void AccelGyroSettings::temp_calibrated_extent_maxChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
