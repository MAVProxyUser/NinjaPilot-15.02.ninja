/****************************************************************************
** Meta object code from reading C++ file 'ekfconfiguration.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/ekfconfiguration.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ekfconfiguration.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EKFConfiguration_t {
    QByteArrayData data[157];
    char stringdata0[2403];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EKFConfiguration_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EKFConfiguration_t qt_meta_stringdata_EKFConfiguration = {
    {
QT_MOC_LITERAL(0, 0, 16), // "EKFConfiguration"
QT_MOC_LITERAL(1, 17, 8), // "PChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "index"
QT_MOC_LITERAL(4, 33, 5), // "value"
QT_MOC_LITERAL(5, 39, 22), // "P_PositionNorthChanged"
QT_MOC_LITERAL(6, 62, 21), // "P_PositionEastChanged"
QT_MOC_LITERAL(7, 84, 21), // "P_PositionDownChanged"
QT_MOC_LITERAL(8, 106, 22), // "P_VelocityNorthChanged"
QT_MOC_LITERAL(9, 129, 21), // "P_VelocityEastChanged"
QT_MOC_LITERAL(10, 151, 21), // "P_VelocityDownChanged"
QT_MOC_LITERAL(11, 173, 19), // "P_AttitudeQ1Changed"
QT_MOC_LITERAL(12, 193, 19), // "P_AttitudeQ2Changed"
QT_MOC_LITERAL(13, 213, 19), // "P_AttitudeQ3Changed"
QT_MOC_LITERAL(14, 233, 19), // "P_AttitudeQ4Changed"
QT_MOC_LITERAL(15, 253, 19), // "P_GyroDriftXChanged"
QT_MOC_LITERAL(16, 273, 19), // "P_GyroDriftYChanged"
QT_MOC_LITERAL(17, 293, 19), // "P_GyroDriftZChanged"
QT_MOC_LITERAL(18, 313, 8), // "QChanged"
QT_MOC_LITERAL(19, 322, 14), // "Q_GyroXChanged"
QT_MOC_LITERAL(20, 337, 14), // "Q_GyroYChanged"
QT_MOC_LITERAL(21, 352, 14), // "Q_GyroZChanged"
QT_MOC_LITERAL(22, 367, 15), // "Q_AccelXChanged"
QT_MOC_LITERAL(23, 383, 15), // "Q_AccelYChanged"
QT_MOC_LITERAL(24, 399, 15), // "Q_AccelZChanged"
QT_MOC_LITERAL(25, 415, 19), // "Q_GyroDriftXChanged"
QT_MOC_LITERAL(26, 435, 19), // "Q_GyroDriftYChanged"
QT_MOC_LITERAL(27, 455, 19), // "Q_GyroDriftZChanged"
QT_MOC_LITERAL(28, 475, 8), // "RChanged"
QT_MOC_LITERAL(29, 484, 20), // "R_GPSPosNorthChanged"
QT_MOC_LITERAL(30, 505, 19), // "R_GPSPosEastChanged"
QT_MOC_LITERAL(31, 525, 19), // "R_GPSPosDownChanged"
QT_MOC_LITERAL(32, 545, 20), // "R_GPSVelNorthChanged"
QT_MOC_LITERAL(33, 566, 19), // "R_GPSVelEastChanged"
QT_MOC_LITERAL(34, 586, 19), // "R_GPSVelDownChanged"
QT_MOC_LITERAL(35, 606, 13), // "R_MagXChanged"
QT_MOC_LITERAL(36, 620, 13), // "R_MagYChanged"
QT_MOC_LITERAL(37, 634, 13), // "R_MagZChanged"
QT_MOC_LITERAL(38, 648, 14), // "R_BaroZChanged"
QT_MOC_LITERAL(39, 663, 12), // "FakeRChanged"
QT_MOC_LITERAL(40, 676, 29), // "FakeR_FakeGPSPosIndoorChanged"
QT_MOC_LITERAL(41, 706, 29), // "FakeR_FakeGPSVelIndoorChanged"
QT_MOC_LITERAL(42, 736, 31), // "FakeR_FakeGPSVelAirspeedChanged"
QT_MOC_LITERAL(43, 768, 4), // "setP"
QT_MOC_LITERAL(44, 773, 18), // "setP_PositionNorth"
QT_MOC_LITERAL(45, 792, 17), // "setP_PositionEast"
QT_MOC_LITERAL(46, 810, 17), // "setP_PositionDown"
QT_MOC_LITERAL(47, 828, 18), // "setP_VelocityNorth"
QT_MOC_LITERAL(48, 847, 17), // "setP_VelocityEast"
QT_MOC_LITERAL(49, 865, 17), // "setP_VelocityDown"
QT_MOC_LITERAL(50, 883, 15), // "setP_AttitudeQ1"
QT_MOC_LITERAL(51, 899, 15), // "setP_AttitudeQ2"
QT_MOC_LITERAL(52, 915, 15), // "setP_AttitudeQ3"
QT_MOC_LITERAL(53, 931, 15), // "setP_AttitudeQ4"
QT_MOC_LITERAL(54, 947, 15), // "setP_GyroDriftX"
QT_MOC_LITERAL(55, 963, 15), // "setP_GyroDriftY"
QT_MOC_LITERAL(56, 979, 15), // "setP_GyroDriftZ"
QT_MOC_LITERAL(57, 995, 4), // "setQ"
QT_MOC_LITERAL(58, 1000, 10), // "setQ_GyroX"
QT_MOC_LITERAL(59, 1011, 10), // "setQ_GyroY"
QT_MOC_LITERAL(60, 1022, 10), // "setQ_GyroZ"
QT_MOC_LITERAL(61, 1033, 11), // "setQ_AccelX"
QT_MOC_LITERAL(62, 1045, 11), // "setQ_AccelY"
QT_MOC_LITERAL(63, 1057, 11), // "setQ_AccelZ"
QT_MOC_LITERAL(64, 1069, 15), // "setQ_GyroDriftX"
QT_MOC_LITERAL(65, 1085, 15), // "setQ_GyroDriftY"
QT_MOC_LITERAL(66, 1101, 15), // "setQ_GyroDriftZ"
QT_MOC_LITERAL(67, 1117, 4), // "setR"
QT_MOC_LITERAL(68, 1122, 16), // "setR_GPSPosNorth"
QT_MOC_LITERAL(69, 1139, 15), // "setR_GPSPosEast"
QT_MOC_LITERAL(70, 1155, 15), // "setR_GPSPosDown"
QT_MOC_LITERAL(71, 1171, 16), // "setR_GPSVelNorth"
QT_MOC_LITERAL(72, 1188, 15), // "setR_GPSVelEast"
QT_MOC_LITERAL(73, 1204, 15), // "setR_GPSVelDown"
QT_MOC_LITERAL(74, 1220, 9), // "setR_MagX"
QT_MOC_LITERAL(75, 1230, 9), // "setR_MagY"
QT_MOC_LITERAL(76, 1240, 9), // "setR_MagZ"
QT_MOC_LITERAL(77, 1250, 10), // "setR_BaroZ"
QT_MOC_LITERAL(78, 1261, 8), // "setFakeR"
QT_MOC_LITERAL(79, 1270, 25), // "setFakeR_FakeGPSPosIndoor"
QT_MOC_LITERAL(80, 1296, 25), // "setFakeR_FakeGPSVelIndoor"
QT_MOC_LITERAL(81, 1322, 27), // "setFakeR_FakeGPSVelAirspeed"
QT_MOC_LITERAL(82, 1350, 17), // "emitNotifications"
QT_MOC_LITERAL(83, 1368, 4), // "getP"
QT_MOC_LITERAL(84, 1373, 18), // "getP_PositionNorth"
QT_MOC_LITERAL(85, 1392, 17), // "getP_PositionEast"
QT_MOC_LITERAL(86, 1410, 17), // "getP_PositionDown"
QT_MOC_LITERAL(87, 1428, 18), // "getP_VelocityNorth"
QT_MOC_LITERAL(88, 1447, 17), // "getP_VelocityEast"
QT_MOC_LITERAL(89, 1465, 17), // "getP_VelocityDown"
QT_MOC_LITERAL(90, 1483, 15), // "getP_AttitudeQ1"
QT_MOC_LITERAL(91, 1499, 15), // "getP_AttitudeQ2"
QT_MOC_LITERAL(92, 1515, 15), // "getP_AttitudeQ3"
QT_MOC_LITERAL(93, 1531, 15), // "getP_AttitudeQ4"
QT_MOC_LITERAL(94, 1547, 15), // "getP_GyroDriftX"
QT_MOC_LITERAL(95, 1563, 15), // "getP_GyroDriftY"
QT_MOC_LITERAL(96, 1579, 15), // "getP_GyroDriftZ"
QT_MOC_LITERAL(97, 1595, 4), // "getQ"
QT_MOC_LITERAL(98, 1600, 10), // "getQ_GyroX"
QT_MOC_LITERAL(99, 1611, 10), // "getQ_GyroY"
QT_MOC_LITERAL(100, 1622, 10), // "getQ_GyroZ"
QT_MOC_LITERAL(101, 1633, 11), // "getQ_AccelX"
QT_MOC_LITERAL(102, 1645, 11), // "getQ_AccelY"
QT_MOC_LITERAL(103, 1657, 11), // "getQ_AccelZ"
QT_MOC_LITERAL(104, 1669, 15), // "getQ_GyroDriftX"
QT_MOC_LITERAL(105, 1685, 15), // "getQ_GyroDriftY"
QT_MOC_LITERAL(106, 1701, 15), // "getQ_GyroDriftZ"
QT_MOC_LITERAL(107, 1717, 4), // "getR"
QT_MOC_LITERAL(108, 1722, 16), // "getR_GPSPosNorth"
QT_MOC_LITERAL(109, 1739, 15), // "getR_GPSPosEast"
QT_MOC_LITERAL(110, 1755, 15), // "getR_GPSPosDown"
QT_MOC_LITERAL(111, 1771, 16), // "getR_GPSVelNorth"
QT_MOC_LITERAL(112, 1788, 15), // "getR_GPSVelEast"
QT_MOC_LITERAL(113, 1804, 15), // "getR_GPSVelDown"
QT_MOC_LITERAL(114, 1820, 9), // "getR_MagX"
QT_MOC_LITERAL(115, 1830, 9), // "getR_MagY"
QT_MOC_LITERAL(116, 1840, 9), // "getR_MagZ"
QT_MOC_LITERAL(117, 1850, 10), // "getR_BaroZ"
QT_MOC_LITERAL(118, 1861, 8), // "getFakeR"
QT_MOC_LITERAL(119, 1870, 25), // "getFakeR_FakeGPSPosIndoor"
QT_MOC_LITERAL(120, 1896, 25), // "getFakeR_FakeGPSVelIndoor"
QT_MOC_LITERAL(121, 1922, 27), // "getFakeR_FakeGPSVelAirspeed"
QT_MOC_LITERAL(122, 1950, 15), // "P_PositionNorth"
QT_MOC_LITERAL(123, 1966, 14), // "P_PositionEast"
QT_MOC_LITERAL(124, 1981, 14), // "P_PositionDown"
QT_MOC_LITERAL(125, 1996, 15), // "P_VelocityNorth"
QT_MOC_LITERAL(126, 2012, 14), // "P_VelocityEast"
QT_MOC_LITERAL(127, 2027, 14), // "P_VelocityDown"
QT_MOC_LITERAL(128, 2042, 12), // "P_AttitudeQ1"
QT_MOC_LITERAL(129, 2055, 12), // "P_AttitudeQ2"
QT_MOC_LITERAL(130, 2068, 12), // "P_AttitudeQ3"
QT_MOC_LITERAL(131, 2081, 12), // "P_AttitudeQ4"
QT_MOC_LITERAL(132, 2094, 12), // "P_GyroDriftX"
QT_MOC_LITERAL(133, 2107, 12), // "P_GyroDriftY"
QT_MOC_LITERAL(134, 2120, 12), // "P_GyroDriftZ"
QT_MOC_LITERAL(135, 2133, 7), // "Q_GyroX"
QT_MOC_LITERAL(136, 2141, 7), // "Q_GyroY"
QT_MOC_LITERAL(137, 2149, 7), // "Q_GyroZ"
QT_MOC_LITERAL(138, 2157, 8), // "Q_AccelX"
QT_MOC_LITERAL(139, 2166, 8), // "Q_AccelY"
QT_MOC_LITERAL(140, 2175, 8), // "Q_AccelZ"
QT_MOC_LITERAL(141, 2184, 12), // "Q_GyroDriftX"
QT_MOC_LITERAL(142, 2197, 12), // "Q_GyroDriftY"
QT_MOC_LITERAL(143, 2210, 12), // "Q_GyroDriftZ"
QT_MOC_LITERAL(144, 2223, 13), // "R_GPSPosNorth"
QT_MOC_LITERAL(145, 2237, 12), // "R_GPSPosEast"
QT_MOC_LITERAL(146, 2250, 12), // "R_GPSPosDown"
QT_MOC_LITERAL(147, 2263, 13), // "R_GPSVelNorth"
QT_MOC_LITERAL(148, 2277, 12), // "R_GPSVelEast"
QT_MOC_LITERAL(149, 2290, 12), // "R_GPSVelDown"
QT_MOC_LITERAL(150, 2303, 6), // "R_MagX"
QT_MOC_LITERAL(151, 2310, 6), // "R_MagY"
QT_MOC_LITERAL(152, 2317, 6), // "R_MagZ"
QT_MOC_LITERAL(153, 2324, 7), // "R_BaroZ"
QT_MOC_LITERAL(154, 2332, 22), // "FakeR_FakeGPSPosIndoor"
QT_MOC_LITERAL(155, 2355, 22), // "FakeR_FakeGPSVelIndoor"
QT_MOC_LITERAL(156, 2378, 24) // "FakeR_FakeGPSVelAirspeed"

    },
    "EKFConfiguration\0PChanged\0\0index\0value\0"
    "P_PositionNorthChanged\0P_PositionEastChanged\0"
    "P_PositionDownChanged\0P_VelocityNorthChanged\0"
    "P_VelocityEastChanged\0P_VelocityDownChanged\0"
    "P_AttitudeQ1Changed\0P_AttitudeQ2Changed\0"
    "P_AttitudeQ3Changed\0P_AttitudeQ4Changed\0"
    "P_GyroDriftXChanged\0P_GyroDriftYChanged\0"
    "P_GyroDriftZChanged\0QChanged\0"
    "Q_GyroXChanged\0Q_GyroYChanged\0"
    "Q_GyroZChanged\0Q_AccelXChanged\0"
    "Q_AccelYChanged\0Q_AccelZChanged\0"
    "Q_GyroDriftXChanged\0Q_GyroDriftYChanged\0"
    "Q_GyroDriftZChanged\0RChanged\0"
    "R_GPSPosNorthChanged\0R_GPSPosEastChanged\0"
    "R_GPSPosDownChanged\0R_GPSVelNorthChanged\0"
    "R_GPSVelEastChanged\0R_GPSVelDownChanged\0"
    "R_MagXChanged\0R_MagYChanged\0R_MagZChanged\0"
    "R_BaroZChanged\0FakeRChanged\0"
    "FakeR_FakeGPSPosIndoorChanged\0"
    "FakeR_FakeGPSVelIndoorChanged\0"
    "FakeR_FakeGPSVelAirspeedChanged\0setP\0"
    "setP_PositionNorth\0setP_PositionEast\0"
    "setP_PositionDown\0setP_VelocityNorth\0"
    "setP_VelocityEast\0setP_VelocityDown\0"
    "setP_AttitudeQ1\0setP_AttitudeQ2\0"
    "setP_AttitudeQ3\0setP_AttitudeQ4\0"
    "setP_GyroDriftX\0setP_GyroDriftY\0"
    "setP_GyroDriftZ\0setQ\0setQ_GyroX\0"
    "setQ_GyroY\0setQ_GyroZ\0setQ_AccelX\0"
    "setQ_AccelY\0setQ_AccelZ\0setQ_GyroDriftX\0"
    "setQ_GyroDriftY\0setQ_GyroDriftZ\0setR\0"
    "setR_GPSPosNorth\0setR_GPSPosEast\0"
    "setR_GPSPosDown\0setR_GPSVelNorth\0"
    "setR_GPSVelEast\0setR_GPSVelDown\0"
    "setR_MagX\0setR_MagY\0setR_MagZ\0setR_BaroZ\0"
    "setFakeR\0setFakeR_FakeGPSPosIndoor\0"
    "setFakeR_FakeGPSVelIndoor\0"
    "setFakeR_FakeGPSVelAirspeed\0"
    "emitNotifications\0getP\0getP_PositionNorth\0"
    "getP_PositionEast\0getP_PositionDown\0"
    "getP_VelocityNorth\0getP_VelocityEast\0"
    "getP_VelocityDown\0getP_AttitudeQ1\0"
    "getP_AttitudeQ2\0getP_AttitudeQ3\0"
    "getP_AttitudeQ4\0getP_GyroDriftX\0"
    "getP_GyroDriftY\0getP_GyroDriftZ\0getQ\0"
    "getQ_GyroX\0getQ_GyroY\0getQ_GyroZ\0"
    "getQ_AccelX\0getQ_AccelY\0getQ_AccelZ\0"
    "getQ_GyroDriftX\0getQ_GyroDriftY\0"
    "getQ_GyroDriftZ\0getR\0getR_GPSPosNorth\0"
    "getR_GPSPosEast\0getR_GPSPosDown\0"
    "getR_GPSVelNorth\0getR_GPSVelEast\0"
    "getR_GPSVelDown\0getR_MagX\0getR_MagY\0"
    "getR_MagZ\0getR_BaroZ\0getFakeR\0"
    "getFakeR_FakeGPSPosIndoor\0"
    "getFakeR_FakeGPSVelIndoor\0"
    "getFakeR_FakeGPSVelAirspeed\0P_PositionNorth\0"
    "P_PositionEast\0P_PositionDown\0"
    "P_VelocityNorth\0P_VelocityEast\0"
    "P_VelocityDown\0P_AttitudeQ1\0P_AttitudeQ2\0"
    "P_AttitudeQ3\0P_AttitudeQ4\0P_GyroDriftX\0"
    "P_GyroDriftY\0P_GyroDriftZ\0Q_GyroX\0"
    "Q_GyroY\0Q_GyroZ\0Q_AccelX\0Q_AccelY\0"
    "Q_AccelZ\0Q_GyroDriftX\0Q_GyroDriftY\0"
    "Q_GyroDriftZ\0R_GPSPosNorth\0R_GPSPosEast\0"
    "R_GPSPosDown\0R_GPSVelNorth\0R_GPSVelEast\0"
    "R_GPSVelDown\0R_MagX\0R_MagY\0R_MagZ\0"
    "R_BaroZ\0FakeR_FakeGPSPosIndoor\0"
    "FakeR_FakeGPSVelIndoor\0FakeR_FakeGPSVelAirspeed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EKFConfiguration[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     118,   14, // methods
      35,  902, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      39,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  604,    2, 0x06 /* Public */,
       5,    1,  609,    2, 0x06 /* Public */,
       6,    1,  612,    2, 0x06 /* Public */,
       7,    1,  615,    2, 0x06 /* Public */,
       8,    1,  618,    2, 0x06 /* Public */,
       9,    1,  621,    2, 0x06 /* Public */,
      10,    1,  624,    2, 0x06 /* Public */,
      11,    1,  627,    2, 0x06 /* Public */,
      12,    1,  630,    2, 0x06 /* Public */,
      13,    1,  633,    2, 0x06 /* Public */,
      14,    1,  636,    2, 0x06 /* Public */,
      15,    1,  639,    2, 0x06 /* Public */,
      16,    1,  642,    2, 0x06 /* Public */,
      17,    1,  645,    2, 0x06 /* Public */,
      18,    2,  648,    2, 0x06 /* Public */,
      19,    1,  653,    2, 0x06 /* Public */,
      20,    1,  656,    2, 0x06 /* Public */,
      21,    1,  659,    2, 0x06 /* Public */,
      22,    1,  662,    2, 0x06 /* Public */,
      23,    1,  665,    2, 0x06 /* Public */,
      24,    1,  668,    2, 0x06 /* Public */,
      25,    1,  671,    2, 0x06 /* Public */,
      26,    1,  674,    2, 0x06 /* Public */,
      27,    1,  677,    2, 0x06 /* Public */,
      28,    2,  680,    2, 0x06 /* Public */,
      29,    1,  685,    2, 0x06 /* Public */,
      30,    1,  688,    2, 0x06 /* Public */,
      31,    1,  691,    2, 0x06 /* Public */,
      32,    1,  694,    2, 0x06 /* Public */,
      33,    1,  697,    2, 0x06 /* Public */,
      34,    1,  700,    2, 0x06 /* Public */,
      35,    1,  703,    2, 0x06 /* Public */,
      36,    1,  706,    2, 0x06 /* Public */,
      37,    1,  709,    2, 0x06 /* Public */,
      38,    1,  712,    2, 0x06 /* Public */,
      39,    2,  715,    2, 0x06 /* Public */,
      40,    1,  720,    2, 0x06 /* Public */,
      41,    1,  723,    2, 0x06 /* Public */,
      42,    1,  726,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      43,    2,  729,    2, 0x0a /* Public */,
      44,    1,  734,    2, 0x0a /* Public */,
      45,    1,  737,    2, 0x0a /* Public */,
      46,    1,  740,    2, 0x0a /* Public */,
      47,    1,  743,    2, 0x0a /* Public */,
      48,    1,  746,    2, 0x0a /* Public */,
      49,    1,  749,    2, 0x0a /* Public */,
      50,    1,  752,    2, 0x0a /* Public */,
      51,    1,  755,    2, 0x0a /* Public */,
      52,    1,  758,    2, 0x0a /* Public */,
      53,    1,  761,    2, 0x0a /* Public */,
      54,    1,  764,    2, 0x0a /* Public */,
      55,    1,  767,    2, 0x0a /* Public */,
      56,    1,  770,    2, 0x0a /* Public */,
      57,    2,  773,    2, 0x0a /* Public */,
      58,    1,  778,    2, 0x0a /* Public */,
      59,    1,  781,    2, 0x0a /* Public */,
      60,    1,  784,    2, 0x0a /* Public */,
      61,    1,  787,    2, 0x0a /* Public */,
      62,    1,  790,    2, 0x0a /* Public */,
      63,    1,  793,    2, 0x0a /* Public */,
      64,    1,  796,    2, 0x0a /* Public */,
      65,    1,  799,    2, 0x0a /* Public */,
      66,    1,  802,    2, 0x0a /* Public */,
      67,    2,  805,    2, 0x0a /* Public */,
      68,    1,  810,    2, 0x0a /* Public */,
      69,    1,  813,    2, 0x0a /* Public */,
      70,    1,  816,    2, 0x0a /* Public */,
      71,    1,  819,    2, 0x0a /* Public */,
      72,    1,  822,    2, 0x0a /* Public */,
      73,    1,  825,    2, 0x0a /* Public */,
      74,    1,  828,    2, 0x0a /* Public */,
      75,    1,  831,    2, 0x0a /* Public */,
      76,    1,  834,    2, 0x0a /* Public */,
      77,    1,  837,    2, 0x0a /* Public */,
      78,    2,  840,    2, 0x0a /* Public */,
      79,    1,  845,    2, 0x0a /* Public */,
      80,    1,  848,    2, 0x0a /* Public */,
      81,    1,  851,    2, 0x0a /* Public */,
      82,    0,  854,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      83,    1,  855,    2, 0x02 /* Public */,
      84,    0,  858,    2, 0x02 /* Public */,
      85,    0,  859,    2, 0x02 /* Public */,
      86,    0,  860,    2, 0x02 /* Public */,
      87,    0,  861,    2, 0x02 /* Public */,
      88,    0,  862,    2, 0x02 /* Public */,
      89,    0,  863,    2, 0x02 /* Public */,
      90,    0,  864,    2, 0x02 /* Public */,
      91,    0,  865,    2, 0x02 /* Public */,
      92,    0,  866,    2, 0x02 /* Public */,
      93,    0,  867,    2, 0x02 /* Public */,
      94,    0,  868,    2, 0x02 /* Public */,
      95,    0,  869,    2, 0x02 /* Public */,
      96,    0,  870,    2, 0x02 /* Public */,
      97,    1,  871,    2, 0x02 /* Public */,
      98,    0,  874,    2, 0x02 /* Public */,
      99,    0,  875,    2, 0x02 /* Public */,
     100,    0,  876,    2, 0x02 /* Public */,
     101,    0,  877,    2, 0x02 /* Public */,
     102,    0,  878,    2, 0x02 /* Public */,
     103,    0,  879,    2, 0x02 /* Public */,
     104,    0,  880,    2, 0x02 /* Public */,
     105,    0,  881,    2, 0x02 /* Public */,
     106,    0,  882,    2, 0x02 /* Public */,
     107,    1,  883,    2, 0x02 /* Public */,
     108,    0,  886,    2, 0x02 /* Public */,
     109,    0,  887,    2, 0x02 /* Public */,
     110,    0,  888,    2, 0x02 /* Public */,
     111,    0,  889,    2, 0x02 /* Public */,
     112,    0,  890,    2, 0x02 /* Public */,
     113,    0,  891,    2, 0x02 /* Public */,
     114,    0,  892,    2, 0x02 /* Public */,
     115,    0,  893,    2, 0x02 /* Public */,
     116,    0,  894,    2, 0x02 /* Public */,
     117,    0,  895,    2, 0x02 /* Public */,
     118,    1,  896,    2, 0x02 /* Public */,
     119,    0,  899,    2, 0x02 /* Public */,
     120,    0,  900,    2, 0x02 /* Public */,
     121,    0,  901,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
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
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
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
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
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
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,

 // properties: name, type, flags
     122, QMetaType::Float, 0x00495103,
     123, QMetaType::Float, 0x00495103,
     124, QMetaType::Float, 0x00495103,
     125, QMetaType::Float, 0x00495103,
     126, QMetaType::Float, 0x00495103,
     127, QMetaType::Float, 0x00495103,
     128, QMetaType::Float, 0x00495103,
     129, QMetaType::Float, 0x00495103,
     130, QMetaType::Float, 0x00495103,
     131, QMetaType::Float, 0x00495103,
     132, QMetaType::Float, 0x00495103,
     133, QMetaType::Float, 0x00495103,
     134, QMetaType::Float, 0x00495103,
     135, QMetaType::Float, 0x00495103,
     136, QMetaType::Float, 0x00495103,
     137, QMetaType::Float, 0x00495103,
     138, QMetaType::Float, 0x00495103,
     139, QMetaType::Float, 0x00495103,
     140, QMetaType::Float, 0x00495103,
     141, QMetaType::Float, 0x00495103,
     142, QMetaType::Float, 0x00495103,
     143, QMetaType::Float, 0x00495103,
     144, QMetaType::Float, 0x00495103,
     145, QMetaType::Float, 0x00495103,
     146, QMetaType::Float, 0x00495103,
     147, QMetaType::Float, 0x00495103,
     148, QMetaType::Float, 0x00495103,
     149, QMetaType::Float, 0x00495103,
     150, QMetaType::Float, 0x00495103,
     151, QMetaType::Float, 0x00495103,
     152, QMetaType::Float, 0x00495103,
     153, QMetaType::Float, 0x00495103,
     154, QMetaType::Float, 0x00495103,
     155, QMetaType::Float, 0x00495103,
     156, QMetaType::Float, 0x00495103,

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
      15,
      16,
      17,
      18,
      19,
      20,
      21,
      22,
      23,
      25,
      26,
      27,
      28,
      29,
      30,
      31,
      32,
      33,
      34,
      36,
      37,
      38,

       0        // eod
};

void EKFConfiguration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EKFConfiguration *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->PChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->P_PositionNorthChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->P_PositionEastChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->P_PositionDownChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->P_VelocityNorthChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->P_VelocityEastChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->P_VelocityDownChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->P_AttitudeQ1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->P_AttitudeQ2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->P_AttitudeQ3Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->P_AttitudeQ4Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->P_GyroDriftXChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->P_GyroDriftYChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->P_GyroDriftZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->QChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 15: _t->Q_GyroXChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->Q_GyroYChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 17: _t->Q_GyroZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->Q_AccelXChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->Q_AccelYChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->Q_AccelZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->Q_GyroDriftXChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: _t->Q_GyroDriftYChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->Q_GyroDriftZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->RChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 25: _t->R_GPSPosNorthChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 26: _t->R_GPSPosEastChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->R_GPSPosDownChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 28: _t->R_GPSVelNorthChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 29: _t->R_GPSVelEastChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 30: _t->R_GPSVelDownChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 31: _t->R_MagXChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 32: _t->R_MagYChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 33: _t->R_MagZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 34: _t->R_BaroZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 35: _t->FakeRChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 36: _t->FakeR_FakeGPSPosIndoorChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 37: _t->FakeR_FakeGPSVelIndoorChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 38: _t->FakeR_FakeGPSVelAirspeedChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 39: _t->setP((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 40: _t->setP_PositionNorth((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 41: _t->setP_PositionEast((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 42: _t->setP_PositionDown((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 43: _t->setP_VelocityNorth((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 44: _t->setP_VelocityEast((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 45: _t->setP_VelocityDown((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 46: _t->setP_AttitudeQ1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 47: _t->setP_AttitudeQ2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 48: _t->setP_AttitudeQ3((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 49: _t->setP_AttitudeQ4((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 50: _t->setP_GyroDriftX((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 51: _t->setP_GyroDriftY((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 52: _t->setP_GyroDriftZ((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 53: _t->setQ((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 54: _t->setQ_GyroX((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 55: _t->setQ_GyroY((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 56: _t->setQ_GyroZ((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 57: _t->setQ_AccelX((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 58: _t->setQ_AccelY((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 59: _t->setQ_AccelZ((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 60: _t->setQ_GyroDriftX((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 61: _t->setQ_GyroDriftY((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 62: _t->setQ_GyroDriftZ((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 63: _t->setR((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 64: _t->setR_GPSPosNorth((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 65: _t->setR_GPSPosEast((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 66: _t->setR_GPSPosDown((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 67: _t->setR_GPSVelNorth((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 68: _t->setR_GPSVelEast((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 69: _t->setR_GPSVelDown((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 70: _t->setR_MagX((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 71: _t->setR_MagY((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 72: _t->setR_MagZ((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 73: _t->setR_BaroZ((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 74: _t->setFakeR((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 75: _t->setFakeR_FakeGPSPosIndoor((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 76: _t->setFakeR_FakeGPSVelIndoor((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 77: _t->setFakeR_FakeGPSVelAirspeed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 78: _t->emitNotifications(); break;
        case 79: { float _r = _t->getP((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 80: { float _r = _t->getP_PositionNorth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 81: { float _r = _t->getP_PositionEast();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 82: { float _r = _t->getP_PositionDown();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 83: { float _r = _t->getP_VelocityNorth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 84: { float _r = _t->getP_VelocityEast();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 85: { float _r = _t->getP_VelocityDown();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 86: { float _r = _t->getP_AttitudeQ1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 87: { float _r = _t->getP_AttitudeQ2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 88: { float _r = _t->getP_AttitudeQ3();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 89: { float _r = _t->getP_AttitudeQ4();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 90: { float _r = _t->getP_GyroDriftX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 91: { float _r = _t->getP_GyroDriftY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 92: { float _r = _t->getP_GyroDriftZ();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 93: { float _r = _t->getQ((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 94: { float _r = _t->getQ_GyroX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 95: { float _r = _t->getQ_GyroY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 96: { float _r = _t->getQ_GyroZ();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 97: { float _r = _t->getQ_AccelX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 98: { float _r = _t->getQ_AccelY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 99: { float _r = _t->getQ_AccelZ();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 100: { float _r = _t->getQ_GyroDriftX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 101: { float _r = _t->getQ_GyroDriftY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 102: { float _r = _t->getQ_GyroDriftZ();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 103: { float _r = _t->getR((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 104: { float _r = _t->getR_GPSPosNorth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 105: { float _r = _t->getR_GPSPosEast();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 106: { float _r = _t->getR_GPSPosDown();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 107: { float _r = _t->getR_GPSVelNorth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 108: { float _r = _t->getR_GPSVelEast();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 109: { float _r = _t->getR_GPSVelDown();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 110: { float _r = _t->getR_MagX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 111: { float _r = _t->getR_MagY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 112: { float _r = _t->getR_MagZ();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 113: { float _r = _t->getR_BaroZ();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 114: { float _r = _t->getFakeR((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 115: { float _r = _t->getFakeR_FakeGPSPosIndoor();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 116: { float _r = _t->getFakeR_FakeGPSVelIndoor();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 117: { float _r = _t->getFakeR_FakeGPSVelAirspeed();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EKFConfiguration::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::PChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::P_PositionNorthChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::P_PositionEastChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::P_PositionDownChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::P_VelocityNorthChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::P_VelocityEastChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::P_VelocityDownChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::P_AttitudeQ1Changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::P_AttitudeQ2Changed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::P_AttitudeQ3Changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::P_AttitudeQ4Changed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::P_GyroDriftXChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::P_GyroDriftYChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::P_GyroDriftZChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::QChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::Q_GyroXChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::Q_GyroYChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::Q_GyroZChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::Q_AccelXChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::Q_AccelYChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::Q_AccelZChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::Q_GyroDriftXChanged)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::Q_GyroDriftYChanged)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::Q_GyroDriftZChanged)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::RChanged)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::R_GPSPosNorthChanged)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::R_GPSPosEastChanged)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::R_GPSPosDownChanged)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::R_GPSVelNorthChanged)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::R_GPSVelEastChanged)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::R_GPSVelDownChanged)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::R_MagXChanged)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::R_MagYChanged)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::R_MagZChanged)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::R_BaroZChanged)) {
                *result = 34;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::FakeRChanged)) {
                *result = 35;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::FakeR_FakeGPSPosIndoorChanged)) {
                *result = 36;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::FakeR_FakeGPSVelIndoorChanged)) {
                *result = 37;
                return;
            }
        }
        {
            using _t = void (EKFConfiguration::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFConfiguration::FakeR_FakeGPSVelAirspeedChanged)) {
                *result = 38;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<EKFConfiguration *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getP_PositionNorth(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getP_PositionEast(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getP_PositionDown(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getP_VelocityNorth(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getP_VelocityEast(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getP_VelocityDown(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getP_AttitudeQ1(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getP_AttitudeQ2(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getP_AttitudeQ3(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->getP_AttitudeQ4(); break;
        case 10: *reinterpret_cast< float*>(_v) = _t->getP_GyroDriftX(); break;
        case 11: *reinterpret_cast< float*>(_v) = _t->getP_GyroDriftY(); break;
        case 12: *reinterpret_cast< float*>(_v) = _t->getP_GyroDriftZ(); break;
        case 13: *reinterpret_cast< float*>(_v) = _t->getQ_GyroX(); break;
        case 14: *reinterpret_cast< float*>(_v) = _t->getQ_GyroY(); break;
        case 15: *reinterpret_cast< float*>(_v) = _t->getQ_GyroZ(); break;
        case 16: *reinterpret_cast< float*>(_v) = _t->getQ_AccelX(); break;
        case 17: *reinterpret_cast< float*>(_v) = _t->getQ_AccelY(); break;
        case 18: *reinterpret_cast< float*>(_v) = _t->getQ_AccelZ(); break;
        case 19: *reinterpret_cast< float*>(_v) = _t->getQ_GyroDriftX(); break;
        case 20: *reinterpret_cast< float*>(_v) = _t->getQ_GyroDriftY(); break;
        case 21: *reinterpret_cast< float*>(_v) = _t->getQ_GyroDriftZ(); break;
        case 22: *reinterpret_cast< float*>(_v) = _t->getR_GPSPosNorth(); break;
        case 23: *reinterpret_cast< float*>(_v) = _t->getR_GPSPosEast(); break;
        case 24: *reinterpret_cast< float*>(_v) = _t->getR_GPSPosDown(); break;
        case 25: *reinterpret_cast< float*>(_v) = _t->getR_GPSVelNorth(); break;
        case 26: *reinterpret_cast< float*>(_v) = _t->getR_GPSVelEast(); break;
        case 27: *reinterpret_cast< float*>(_v) = _t->getR_GPSVelDown(); break;
        case 28: *reinterpret_cast< float*>(_v) = _t->getR_MagX(); break;
        case 29: *reinterpret_cast< float*>(_v) = _t->getR_MagY(); break;
        case 30: *reinterpret_cast< float*>(_v) = _t->getR_MagZ(); break;
        case 31: *reinterpret_cast< float*>(_v) = _t->getR_BaroZ(); break;
        case 32: *reinterpret_cast< float*>(_v) = _t->getFakeR_FakeGPSPosIndoor(); break;
        case 33: *reinterpret_cast< float*>(_v) = _t->getFakeR_FakeGPSVelIndoor(); break;
        case 34: *reinterpret_cast< float*>(_v) = _t->getFakeR_FakeGPSVelAirspeed(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<EKFConfiguration *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setP_PositionNorth(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setP_PositionEast(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setP_PositionDown(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setP_VelocityNorth(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setP_VelocityEast(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setP_VelocityDown(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setP_AttitudeQ1(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setP_AttitudeQ2(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setP_AttitudeQ3(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setP_AttitudeQ4(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setP_GyroDriftX(*reinterpret_cast< float*>(_v)); break;
        case 11: _t->setP_GyroDriftY(*reinterpret_cast< float*>(_v)); break;
        case 12: _t->setP_GyroDriftZ(*reinterpret_cast< float*>(_v)); break;
        case 13: _t->setQ_GyroX(*reinterpret_cast< float*>(_v)); break;
        case 14: _t->setQ_GyroY(*reinterpret_cast< float*>(_v)); break;
        case 15: _t->setQ_GyroZ(*reinterpret_cast< float*>(_v)); break;
        case 16: _t->setQ_AccelX(*reinterpret_cast< float*>(_v)); break;
        case 17: _t->setQ_AccelY(*reinterpret_cast< float*>(_v)); break;
        case 18: _t->setQ_AccelZ(*reinterpret_cast< float*>(_v)); break;
        case 19: _t->setQ_GyroDriftX(*reinterpret_cast< float*>(_v)); break;
        case 20: _t->setQ_GyroDriftY(*reinterpret_cast< float*>(_v)); break;
        case 21: _t->setQ_GyroDriftZ(*reinterpret_cast< float*>(_v)); break;
        case 22: _t->setR_GPSPosNorth(*reinterpret_cast< float*>(_v)); break;
        case 23: _t->setR_GPSPosEast(*reinterpret_cast< float*>(_v)); break;
        case 24: _t->setR_GPSPosDown(*reinterpret_cast< float*>(_v)); break;
        case 25: _t->setR_GPSVelNorth(*reinterpret_cast< float*>(_v)); break;
        case 26: _t->setR_GPSVelEast(*reinterpret_cast< float*>(_v)); break;
        case 27: _t->setR_GPSVelDown(*reinterpret_cast< float*>(_v)); break;
        case 28: _t->setR_MagX(*reinterpret_cast< float*>(_v)); break;
        case 29: _t->setR_MagY(*reinterpret_cast< float*>(_v)); break;
        case 30: _t->setR_MagZ(*reinterpret_cast< float*>(_v)); break;
        case 31: _t->setR_BaroZ(*reinterpret_cast< float*>(_v)); break;
        case 32: _t->setFakeR_FakeGPSPosIndoor(*reinterpret_cast< float*>(_v)); break;
        case 33: _t->setFakeR_FakeGPSVelIndoor(*reinterpret_cast< float*>(_v)); break;
        case 34: _t->setFakeR_FakeGPSVelAirspeed(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject EKFConfiguration::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_EKFConfiguration.data,
    qt_meta_data_EKFConfiguration,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EKFConfiguration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EKFConfiguration::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EKFConfiguration.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int EKFConfiguration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 118)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 118;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 118)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 118;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 35;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 35;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 35;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 35;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 35;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void EKFConfiguration::PChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EKFConfiguration::P_PositionNorthChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void EKFConfiguration::P_PositionEastChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void EKFConfiguration::P_PositionDownChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void EKFConfiguration::P_VelocityNorthChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void EKFConfiguration::P_VelocityEastChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void EKFConfiguration::P_VelocityDownChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void EKFConfiguration::P_AttitudeQ1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void EKFConfiguration::P_AttitudeQ2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void EKFConfiguration::P_AttitudeQ3Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void EKFConfiguration::P_AttitudeQ4Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void EKFConfiguration::P_GyroDriftXChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void EKFConfiguration::P_GyroDriftYChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void EKFConfiguration::P_GyroDriftZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void EKFConfiguration::QChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void EKFConfiguration::Q_GyroXChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void EKFConfiguration::Q_GyroYChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void EKFConfiguration::Q_GyroZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void EKFConfiguration::Q_AccelXChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void EKFConfiguration::Q_AccelYChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void EKFConfiguration::Q_AccelZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void EKFConfiguration::Q_GyroDriftXChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void EKFConfiguration::Q_GyroDriftYChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void EKFConfiguration::Q_GyroDriftZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void EKFConfiguration::RChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void EKFConfiguration::R_GPSPosNorthChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void EKFConfiguration::R_GPSPosEastChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void EKFConfiguration::R_GPSPosDownChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void EKFConfiguration::R_GPSVelNorthChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void EKFConfiguration::R_GPSVelEastChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void EKFConfiguration::R_GPSVelDownChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void EKFConfiguration::R_MagXChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void EKFConfiguration::R_MagYChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void EKFConfiguration::R_MagZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void EKFConfiguration::R_BaroZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void EKFConfiguration::FakeRChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 35, _a);
}

// SIGNAL 36
void EKFConfiguration::FakeR_FakeGPSPosIndoorChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 36, _a);
}

// SIGNAL 37
void EKFConfiguration::FakeR_FakeGPSVelIndoorChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 37, _a);
}

// SIGNAL 38
void EKFConfiguration::FakeR_FakeGPSVelAirspeedChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 38, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
