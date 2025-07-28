/****************************************************************************
** Meta object code from reading C++ file 'statusvtolland.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/statusvtolland.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'statusvtolland.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StatusVtolLand_t {
    QByteArrayData data[126];
    char stringdata0[2710];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StatusVtolLand_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StatusVtolLand_t qt_meta_stringdata_StatusVtolLand = {
    {
QT_MOC_LITERAL(0, 0, 14), // "StatusVtolLand"
QT_MOC_LITERAL(1, 15, 22), // "AltitudeAtStateChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5), // "index"
QT_MOC_LITERAL(4, 45, 5), // "value"
QT_MOC_LITERAL(5, 51, 24), // "AltitudeAtState_0Changed"
QT_MOC_LITERAL(6, 76, 24), // "AltitudeAtState_1Changed"
QT_MOC_LITERAL(7, 101, 24), // "AltitudeAtState_2Changed"
QT_MOC_LITERAL(8, 126, 24), // "AltitudeAtState_3Changed"
QT_MOC_LITERAL(9, 151, 24), // "AltitudeAtState_4Changed"
QT_MOC_LITERAL(10, 176, 24), // "AltitudeAtState_5Changed"
QT_MOC_LITERAL(11, 201, 24), // "AltitudeAtState_6Changed"
QT_MOC_LITERAL(12, 226, 24), // "AltitudeAtState_7Changed"
QT_MOC_LITERAL(13, 251, 24), // "AltitudeAtState_8Changed"
QT_MOC_LITERAL(14, 276, 24), // "AltitudeAtState_9Changed"
QT_MOC_LITERAL(15, 301, 24), // "targetDescentRateChanged"
QT_MOC_LITERAL(16, 326, 25), // "averageDescentRateChanged"
QT_MOC_LITERAL(17, 352, 27), // "averageDescentThrustChanged"
QT_MOC_LITERAL(18, 380, 30), // "calculatedNeutralThrustChanged"
QT_MOC_LITERAL(19, 411, 25), // "WtgForGroundEffectChanged"
QT_MOC_LITERAL(20, 437, 40), // "WtgForGroundEffect_BounceVelo..."
QT_MOC_LITERAL(21, 478, 37), // "WtgForGroundEffect_BounceAcce..."
QT_MOC_LITERAL(22, 516, 12), // "StateChanged"
QT_MOC_LITERAL(23, 529, 22), // "StateExitReasonChanged"
QT_MOC_LITERAL(24, 552, 24), // "StateExitReason_0Changed"
QT_MOC_LITERAL(25, 577, 24), // "StateExitReason_1Changed"
QT_MOC_LITERAL(26, 602, 24), // "StateExitReason_2Changed"
QT_MOC_LITERAL(27, 627, 24), // "StateExitReason_3Changed"
QT_MOC_LITERAL(28, 652, 24), // "StateExitReason_4Changed"
QT_MOC_LITERAL(29, 677, 24), // "StateExitReason_5Changed"
QT_MOC_LITERAL(30, 702, 24), // "StateExitReason_6Changed"
QT_MOC_LITERAL(31, 727, 24), // "StateExitReason_7Changed"
QT_MOC_LITERAL(32, 752, 24), // "StateExitReason_8Changed"
QT_MOC_LITERAL(33, 777, 24), // "StateExitReason_9Changed"
QT_MOC_LITERAL(34, 802, 20), // "AltitudeStateChanged"
QT_MOC_LITERAL(35, 823, 18), // "setAltitudeAtState"
QT_MOC_LITERAL(36, 842, 20), // "setAltitudeAtState_0"
QT_MOC_LITERAL(37, 863, 20), // "setAltitudeAtState_1"
QT_MOC_LITERAL(38, 884, 20), // "setAltitudeAtState_2"
QT_MOC_LITERAL(39, 905, 20), // "setAltitudeAtState_3"
QT_MOC_LITERAL(40, 926, 20), // "setAltitudeAtState_4"
QT_MOC_LITERAL(41, 947, 20), // "setAltitudeAtState_5"
QT_MOC_LITERAL(42, 968, 20), // "setAltitudeAtState_6"
QT_MOC_LITERAL(43, 989, 20), // "setAltitudeAtState_7"
QT_MOC_LITERAL(44, 1010, 20), // "setAltitudeAtState_8"
QT_MOC_LITERAL(45, 1031, 20), // "setAltitudeAtState_9"
QT_MOC_LITERAL(46, 1052, 20), // "settargetDescentRate"
QT_MOC_LITERAL(47, 1073, 21), // "setaverageDescentRate"
QT_MOC_LITERAL(48, 1095, 23), // "setaverageDescentThrust"
QT_MOC_LITERAL(49, 1119, 26), // "setcalculatedNeutralThrust"
QT_MOC_LITERAL(50, 1146, 21), // "setWtgForGroundEffect"
QT_MOC_LITERAL(51, 1168, 36), // "setWtgForGroundEffect_BounceV..."
QT_MOC_LITERAL(52, 1205, 33), // "setWtgForGroundEffect_BounceA..."
QT_MOC_LITERAL(53, 1239, 8), // "setState"
QT_MOC_LITERAL(54, 1248, 18), // "setStateExitReason"
QT_MOC_LITERAL(55, 1267, 20), // "setStateExitReason_0"
QT_MOC_LITERAL(56, 1288, 20), // "setStateExitReason_1"
QT_MOC_LITERAL(57, 1309, 20), // "setStateExitReason_2"
QT_MOC_LITERAL(58, 1330, 20), // "setStateExitReason_3"
QT_MOC_LITERAL(59, 1351, 20), // "setStateExitReason_4"
QT_MOC_LITERAL(60, 1372, 20), // "setStateExitReason_5"
QT_MOC_LITERAL(61, 1393, 20), // "setStateExitReason_6"
QT_MOC_LITERAL(62, 1414, 20), // "setStateExitReason_7"
QT_MOC_LITERAL(63, 1435, 20), // "setStateExitReason_8"
QT_MOC_LITERAL(64, 1456, 20), // "setStateExitReason_9"
QT_MOC_LITERAL(65, 1477, 16), // "setAltitudeState"
QT_MOC_LITERAL(66, 1494, 17), // "emitNotifications"
QT_MOC_LITERAL(67, 1512, 18), // "getAltitudeAtState"
QT_MOC_LITERAL(68, 1531, 20), // "getAltitudeAtState_0"
QT_MOC_LITERAL(69, 1552, 20), // "getAltitudeAtState_1"
QT_MOC_LITERAL(70, 1573, 20), // "getAltitudeAtState_2"
QT_MOC_LITERAL(71, 1594, 20), // "getAltitudeAtState_3"
QT_MOC_LITERAL(72, 1615, 20), // "getAltitudeAtState_4"
QT_MOC_LITERAL(73, 1636, 20), // "getAltitudeAtState_5"
QT_MOC_LITERAL(74, 1657, 20), // "getAltitudeAtState_6"
QT_MOC_LITERAL(75, 1678, 20), // "getAltitudeAtState_7"
QT_MOC_LITERAL(76, 1699, 20), // "getAltitudeAtState_8"
QT_MOC_LITERAL(77, 1720, 20), // "getAltitudeAtState_9"
QT_MOC_LITERAL(78, 1741, 20), // "gettargetDescentRate"
QT_MOC_LITERAL(79, 1762, 21), // "getaverageDescentRate"
QT_MOC_LITERAL(80, 1784, 23), // "getaverageDescentThrust"
QT_MOC_LITERAL(81, 1808, 26), // "getcalculatedNeutralThrust"
QT_MOC_LITERAL(82, 1835, 21), // "getWtgForGroundEffect"
QT_MOC_LITERAL(83, 1857, 36), // "getWtgForGroundEffect_BounceV..."
QT_MOC_LITERAL(84, 1894, 33), // "getWtgForGroundEffect_BounceA..."
QT_MOC_LITERAL(85, 1928, 8), // "getState"
QT_MOC_LITERAL(86, 1937, 18), // "getStateExitReason"
QT_MOC_LITERAL(87, 1956, 20), // "getStateExitReason_0"
QT_MOC_LITERAL(88, 1977, 20), // "getStateExitReason_1"
QT_MOC_LITERAL(89, 1998, 20), // "getStateExitReason_2"
QT_MOC_LITERAL(90, 2019, 20), // "getStateExitReason_3"
QT_MOC_LITERAL(91, 2040, 20), // "getStateExitReason_4"
QT_MOC_LITERAL(92, 2061, 20), // "getStateExitReason_5"
QT_MOC_LITERAL(93, 2082, 20), // "getStateExitReason_6"
QT_MOC_LITERAL(94, 2103, 20), // "getStateExitReason_7"
QT_MOC_LITERAL(95, 2124, 20), // "getStateExitReason_8"
QT_MOC_LITERAL(96, 2145, 20), // "getStateExitReason_9"
QT_MOC_LITERAL(97, 2166, 16), // "getAltitudeState"
QT_MOC_LITERAL(98, 2183, 17), // "AltitudeAtState_0"
QT_MOC_LITERAL(99, 2201, 17), // "AltitudeAtState_1"
QT_MOC_LITERAL(100, 2219, 17), // "AltitudeAtState_2"
QT_MOC_LITERAL(101, 2237, 17), // "AltitudeAtState_3"
QT_MOC_LITERAL(102, 2255, 17), // "AltitudeAtState_4"
QT_MOC_LITERAL(103, 2273, 17), // "AltitudeAtState_5"
QT_MOC_LITERAL(104, 2291, 17), // "AltitudeAtState_6"
QT_MOC_LITERAL(105, 2309, 17), // "AltitudeAtState_7"
QT_MOC_LITERAL(106, 2327, 17), // "AltitudeAtState_8"
QT_MOC_LITERAL(107, 2345, 17), // "AltitudeAtState_9"
QT_MOC_LITERAL(108, 2363, 17), // "targetDescentRate"
QT_MOC_LITERAL(109, 2381, 18), // "averageDescentRate"
QT_MOC_LITERAL(110, 2400, 20), // "averageDescentThrust"
QT_MOC_LITERAL(111, 2421, 23), // "calculatedNeutralThrust"
QT_MOC_LITERAL(112, 2445, 33), // "WtgForGroundEffect_BounceVelo..."
QT_MOC_LITERAL(113, 2479, 30), // "WtgForGroundEffect_BounceAccel"
QT_MOC_LITERAL(114, 2510, 5), // "State"
QT_MOC_LITERAL(115, 2516, 17), // "StateExitReason_0"
QT_MOC_LITERAL(116, 2534, 17), // "StateExitReason_1"
QT_MOC_LITERAL(117, 2552, 17), // "StateExitReason_2"
QT_MOC_LITERAL(118, 2570, 17), // "StateExitReason_3"
QT_MOC_LITERAL(119, 2588, 17), // "StateExitReason_4"
QT_MOC_LITERAL(120, 2606, 17), // "StateExitReason_5"
QT_MOC_LITERAL(121, 2624, 17), // "StateExitReason_6"
QT_MOC_LITERAL(122, 2642, 17), // "StateExitReason_7"
QT_MOC_LITERAL(123, 2660, 17), // "StateExitReason_8"
QT_MOC_LITERAL(124, 2678, 17), // "StateExitReason_9"
QT_MOC_LITERAL(125, 2696, 13) // "AltitudeState"

    },
    "StatusVtolLand\0AltitudeAtStateChanged\0"
    "\0index\0value\0AltitudeAtState_0Changed\0"
    "AltitudeAtState_1Changed\0"
    "AltitudeAtState_2Changed\0"
    "AltitudeAtState_3Changed\0"
    "AltitudeAtState_4Changed\0"
    "AltitudeAtState_5Changed\0"
    "AltitudeAtState_6Changed\0"
    "AltitudeAtState_7Changed\0"
    "AltitudeAtState_8Changed\0"
    "AltitudeAtState_9Changed\0"
    "targetDescentRateChanged\0"
    "averageDescentRateChanged\0"
    "averageDescentThrustChanged\0"
    "calculatedNeutralThrustChanged\0"
    "WtgForGroundEffectChanged\0"
    "WtgForGroundEffect_BounceVelocityChanged\0"
    "WtgForGroundEffect_BounceAccelChanged\0"
    "StateChanged\0StateExitReasonChanged\0"
    "StateExitReason_0Changed\0"
    "StateExitReason_1Changed\0"
    "StateExitReason_2Changed\0"
    "StateExitReason_3Changed\0"
    "StateExitReason_4Changed\0"
    "StateExitReason_5Changed\0"
    "StateExitReason_6Changed\0"
    "StateExitReason_7Changed\0"
    "StateExitReason_8Changed\0"
    "StateExitReason_9Changed\0AltitudeStateChanged\0"
    "setAltitudeAtState\0setAltitudeAtState_0\0"
    "setAltitudeAtState_1\0setAltitudeAtState_2\0"
    "setAltitudeAtState_3\0setAltitudeAtState_4\0"
    "setAltitudeAtState_5\0setAltitudeAtState_6\0"
    "setAltitudeAtState_7\0setAltitudeAtState_8\0"
    "setAltitudeAtState_9\0settargetDescentRate\0"
    "setaverageDescentRate\0setaverageDescentThrust\0"
    "setcalculatedNeutralThrust\0"
    "setWtgForGroundEffect\0"
    "setWtgForGroundEffect_BounceVelocity\0"
    "setWtgForGroundEffect_BounceAccel\0"
    "setState\0setStateExitReason\0"
    "setStateExitReason_0\0setStateExitReason_1\0"
    "setStateExitReason_2\0setStateExitReason_3\0"
    "setStateExitReason_4\0setStateExitReason_5\0"
    "setStateExitReason_6\0setStateExitReason_7\0"
    "setStateExitReason_8\0setStateExitReason_9\0"
    "setAltitudeState\0emitNotifications\0"
    "getAltitudeAtState\0getAltitudeAtState_0\0"
    "getAltitudeAtState_1\0getAltitudeAtState_2\0"
    "getAltitudeAtState_3\0getAltitudeAtState_4\0"
    "getAltitudeAtState_5\0getAltitudeAtState_6\0"
    "getAltitudeAtState_7\0getAltitudeAtState_8\0"
    "getAltitudeAtState_9\0gettargetDescentRate\0"
    "getaverageDescentRate\0getaverageDescentThrust\0"
    "getcalculatedNeutralThrust\0"
    "getWtgForGroundEffect\0"
    "getWtgForGroundEffect_BounceVelocity\0"
    "getWtgForGroundEffect_BounceAccel\0"
    "getState\0getStateExitReason\0"
    "getStateExitReason_0\0getStateExitReason_1\0"
    "getStateExitReason_2\0getStateExitReason_3\0"
    "getStateExitReason_4\0getStateExitReason_5\0"
    "getStateExitReason_6\0getStateExitReason_7\0"
    "getStateExitReason_8\0getStateExitReason_9\0"
    "getAltitudeState\0AltitudeAtState_0\0"
    "AltitudeAtState_1\0AltitudeAtState_2\0"
    "AltitudeAtState_3\0AltitudeAtState_4\0"
    "AltitudeAtState_5\0AltitudeAtState_6\0"
    "AltitudeAtState_7\0AltitudeAtState_8\0"
    "AltitudeAtState_9\0targetDescentRate\0"
    "averageDescentRate\0averageDescentThrust\0"
    "calculatedNeutralThrust\0"
    "WtgForGroundEffect_BounceVelocity\0"
    "WtgForGroundEffect_BounceAccel\0State\0"
    "StateExitReason_0\0StateExitReason_1\0"
    "StateExitReason_2\0StateExitReason_3\0"
    "StateExitReason_4\0StateExitReason_5\0"
    "StateExitReason_6\0StateExitReason_7\0"
    "StateExitReason_8\0StateExitReason_9\0"
    "AltitudeState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StatusVtolLand[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      94,   14, // methods
      28,  720, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      31,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  484,    2, 0x06 /* Public */,
       5,    1,  489,    2, 0x06 /* Public */,
       6,    1,  492,    2, 0x06 /* Public */,
       7,    1,  495,    2, 0x06 /* Public */,
       8,    1,  498,    2, 0x06 /* Public */,
       9,    1,  501,    2, 0x06 /* Public */,
      10,    1,  504,    2, 0x06 /* Public */,
      11,    1,  507,    2, 0x06 /* Public */,
      12,    1,  510,    2, 0x06 /* Public */,
      13,    1,  513,    2, 0x06 /* Public */,
      14,    1,  516,    2, 0x06 /* Public */,
      15,    1,  519,    2, 0x06 /* Public */,
      16,    1,  522,    2, 0x06 /* Public */,
      17,    1,  525,    2, 0x06 /* Public */,
      18,    1,  528,    2, 0x06 /* Public */,
      19,    2,  531,    2, 0x06 /* Public */,
      20,    1,  536,    2, 0x06 /* Public */,
      21,    1,  539,    2, 0x06 /* Public */,
      22,    1,  542,    2, 0x06 /* Public */,
      23,    2,  545,    2, 0x06 /* Public */,
      24,    1,  550,    2, 0x06 /* Public */,
      25,    1,  553,    2, 0x06 /* Public */,
      26,    1,  556,    2, 0x06 /* Public */,
      27,    1,  559,    2, 0x06 /* Public */,
      28,    1,  562,    2, 0x06 /* Public */,
      29,    1,  565,    2, 0x06 /* Public */,
      30,    1,  568,    2, 0x06 /* Public */,
      31,    1,  571,    2, 0x06 /* Public */,
      32,    1,  574,    2, 0x06 /* Public */,
      33,    1,  577,    2, 0x06 /* Public */,
      34,    1,  580,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      35,    2,  583,    2, 0x0a /* Public */,
      36,    1,  588,    2, 0x0a /* Public */,
      37,    1,  591,    2, 0x0a /* Public */,
      38,    1,  594,    2, 0x0a /* Public */,
      39,    1,  597,    2, 0x0a /* Public */,
      40,    1,  600,    2, 0x0a /* Public */,
      41,    1,  603,    2, 0x0a /* Public */,
      42,    1,  606,    2, 0x0a /* Public */,
      43,    1,  609,    2, 0x0a /* Public */,
      44,    1,  612,    2, 0x0a /* Public */,
      45,    1,  615,    2, 0x0a /* Public */,
      46,    1,  618,    2, 0x0a /* Public */,
      47,    1,  621,    2, 0x0a /* Public */,
      48,    1,  624,    2, 0x0a /* Public */,
      49,    1,  627,    2, 0x0a /* Public */,
      50,    2,  630,    2, 0x0a /* Public */,
      51,    1,  635,    2, 0x0a /* Public */,
      52,    1,  638,    2, 0x0a /* Public */,
      53,    1,  641,    2, 0x0a /* Public */,
      54,    2,  644,    2, 0x0a /* Public */,
      55,    1,  649,    2, 0x0a /* Public */,
      56,    1,  652,    2, 0x0a /* Public */,
      57,    1,  655,    2, 0x0a /* Public */,
      58,    1,  658,    2, 0x0a /* Public */,
      59,    1,  661,    2, 0x0a /* Public */,
      60,    1,  664,    2, 0x0a /* Public */,
      61,    1,  667,    2, 0x0a /* Public */,
      62,    1,  670,    2, 0x0a /* Public */,
      63,    1,  673,    2, 0x0a /* Public */,
      64,    1,  676,    2, 0x0a /* Public */,
      65,    1,  679,    2, 0x0a /* Public */,
      66,    0,  682,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      67,    1,  683,    2, 0x02 /* Public */,
      68,    0,  686,    2, 0x02 /* Public */,
      69,    0,  687,    2, 0x02 /* Public */,
      70,    0,  688,    2, 0x02 /* Public */,
      71,    0,  689,    2, 0x02 /* Public */,
      72,    0,  690,    2, 0x02 /* Public */,
      73,    0,  691,    2, 0x02 /* Public */,
      74,    0,  692,    2, 0x02 /* Public */,
      75,    0,  693,    2, 0x02 /* Public */,
      76,    0,  694,    2, 0x02 /* Public */,
      77,    0,  695,    2, 0x02 /* Public */,
      78,    0,  696,    2, 0x02 /* Public */,
      79,    0,  697,    2, 0x02 /* Public */,
      80,    0,  698,    2, 0x02 /* Public */,
      81,    0,  699,    2, 0x02 /* Public */,
      82,    1,  700,    2, 0x02 /* Public */,
      83,    0,  703,    2, 0x02 /* Public */,
      84,    0,  704,    2, 0x02 /* Public */,
      85,    0,  705,    2, 0x02 /* Public */,
      86,    1,  706,    2, 0x02 /* Public */,
      87,    0,  709,    2, 0x02 /* Public */,
      88,    0,  710,    2, 0x02 /* Public */,
      89,    0,  711,    2, 0x02 /* Public */,
      90,    0,  712,    2, 0x02 /* Public */,
      91,    0,  713,    2, 0x02 /* Public */,
      92,    0,  714,    2, 0x02 /* Public */,
      93,    0,  715,    2, 0x02 /* Public */,
      94,    0,  716,    2, 0x02 /* Public */,
      95,    0,  717,    2, 0x02 /* Public */,
      96,    0,  718,    2, 0x02 /* Public */,
      97,    0,  719,    2, 0x02 /* Public */,

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
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UChar,    4,
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
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UChar,    4,
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
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar,
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

 // properties: name, type, flags
      98, QMetaType::Float, 0x00495103,
      99, QMetaType::Float, 0x00495103,
     100, QMetaType::Float, 0x00495103,
     101, QMetaType::Float, 0x00495103,
     102, QMetaType::Float, 0x00495103,
     103, QMetaType::Float, 0x00495103,
     104, QMetaType::Float, 0x00495103,
     105, QMetaType::Float, 0x00495103,
     106, QMetaType::Float, 0x00495103,
     107, QMetaType::Float, 0x00495103,
     108, QMetaType::Float, 0x00495003,
     109, QMetaType::Float, 0x00495003,
     110, QMetaType::Float, 0x00495003,
     111, QMetaType::Float, 0x00495003,
     112, QMetaType::Float, 0x00495103,
     113, QMetaType::Float, 0x00495103,
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
      16,
      17,
      18,
      20,
      21,
      22,
      23,
      24,
      25,
      26,
      27,
      28,
      29,
      30,

       0        // eod
};

void StatusVtolLand::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StatusVtolLand *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->AltitudeAtStateChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->AltitudeAtState_0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->AltitudeAtState_1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->AltitudeAtState_2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->AltitudeAtState_3Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->AltitudeAtState_4Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->AltitudeAtState_5Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->AltitudeAtState_6Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->AltitudeAtState_7Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->AltitudeAtState_8Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->AltitudeAtState_9Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->targetDescentRateChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->averageDescentRateChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->averageDescentThrustChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->calculatedNeutralThrustChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->WtgForGroundEffectChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 16: _t->WtgForGroundEffect_BounceVelocityChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 17: _t->WtgForGroundEffect_BounceAccelChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->StateChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 19: _t->StateExitReasonChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 20: _t->StateExitReason_0Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 21: _t->StateExitReason_1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 22: _t->StateExitReason_2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 23: _t->StateExitReason_3Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 24: _t->StateExitReason_4Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 25: _t->StateExitReason_5Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 26: _t->StateExitReason_6Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 27: _t->StateExitReason_7Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 28: _t->StateExitReason_8Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 29: _t->StateExitReason_9Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 30: _t->AltitudeStateChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 31: _t->setAltitudeAtState((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 32: _t->setAltitudeAtState_0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 33: _t->setAltitudeAtState_1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 34: _t->setAltitudeAtState_2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 35: _t->setAltitudeAtState_3((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 36: _t->setAltitudeAtState_4((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 37: _t->setAltitudeAtState_5((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 38: _t->setAltitudeAtState_6((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 39: _t->setAltitudeAtState_7((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 40: _t->setAltitudeAtState_8((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 41: _t->setAltitudeAtState_9((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 42: _t->settargetDescentRate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 43: _t->setaverageDescentRate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 44: _t->setaverageDescentThrust((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 45: _t->setcalculatedNeutralThrust((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 46: _t->setWtgForGroundEffect((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 47: _t->setWtgForGroundEffect_BounceVelocity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 48: _t->setWtgForGroundEffect_BounceAccel((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 49: _t->setState((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 50: _t->setStateExitReason((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 51: _t->setStateExitReason_0((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 52: _t->setStateExitReason_1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 53: _t->setStateExitReason_2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 54: _t->setStateExitReason_3((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 55: _t->setStateExitReason_4((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 56: _t->setStateExitReason_5((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 57: _t->setStateExitReason_6((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 58: _t->setStateExitReason_7((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 59: _t->setStateExitReason_8((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 60: _t->setStateExitReason_9((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 61: _t->setAltitudeState((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 62: _t->emitNotifications(); break;
        case 63: { float _r = _t->getAltitudeAtState((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 64: { float _r = _t->getAltitudeAtState_0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 65: { float _r = _t->getAltitudeAtState_1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 66: { float _r = _t->getAltitudeAtState_2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 67: { float _r = _t->getAltitudeAtState_3();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 68: { float _r = _t->getAltitudeAtState_4();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 69: { float _r = _t->getAltitudeAtState_5();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 70: { float _r = _t->getAltitudeAtState_6();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 71: { float _r = _t->getAltitudeAtState_7();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 72: { float _r = _t->getAltitudeAtState_8();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 73: { float _r = _t->getAltitudeAtState_9();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 74: { float _r = _t->gettargetDescentRate();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 75: { float _r = _t->getaverageDescentRate();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 76: { float _r = _t->getaverageDescentThrust();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 77: { float _r = _t->getcalculatedNeutralThrust();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 78: { float _r = _t->getWtgForGroundEffect((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 79: { float _r = _t->getWtgForGroundEffect_BounceVelocity();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 80: { float _r = _t->getWtgForGroundEffect_BounceAccel();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 81: { quint8 _r = _t->getState();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 82: { quint8 _r = _t->getStateExitReason((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 83: { quint8 _r = _t->getStateExitReason_0();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 84: { quint8 _r = _t->getStateExitReason_1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 85: { quint8 _r = _t->getStateExitReason_2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 86: { quint8 _r = _t->getStateExitReason_3();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 87: { quint8 _r = _t->getStateExitReason_4();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 88: { quint8 _r = _t->getStateExitReason_5();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 89: { quint8 _r = _t->getStateExitReason_6();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 90: { quint8 _r = _t->getStateExitReason_7();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 91: { quint8 _r = _t->getStateExitReason_8();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 92: { quint8 _r = _t->getStateExitReason_9();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 93: { quint8 _r = _t->getAltitudeState();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StatusVtolLand::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::AltitudeAtStateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::AltitudeAtState_0Changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::AltitudeAtState_1Changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::AltitudeAtState_2Changed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::AltitudeAtState_3Changed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::AltitudeAtState_4Changed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::AltitudeAtState_5Changed)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::AltitudeAtState_6Changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::AltitudeAtState_7Changed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::AltitudeAtState_8Changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::AltitudeAtState_9Changed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::targetDescentRateChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::averageDescentRateChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::averageDescentThrustChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::calculatedNeutralThrustChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::WtgForGroundEffectChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::WtgForGroundEffect_BounceVelocityChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::WtgForGroundEffect_BounceAccelChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::StateChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::StateExitReasonChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::StateExitReason_0Changed)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::StateExitReason_1Changed)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::StateExitReason_2Changed)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::StateExitReason_3Changed)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::StateExitReason_4Changed)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::StateExitReason_5Changed)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::StateExitReason_6Changed)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::StateExitReason_7Changed)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::StateExitReason_8Changed)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::StateExitReason_9Changed)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (StatusVtolLand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusVtolLand::AltitudeStateChanged)) {
                *result = 30;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<StatusVtolLand *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getAltitudeAtState_0(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getAltitudeAtState_1(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getAltitudeAtState_2(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getAltitudeAtState_3(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getAltitudeAtState_4(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getAltitudeAtState_5(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getAltitudeAtState_6(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getAltitudeAtState_7(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getAltitudeAtState_8(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->getAltitudeAtState_9(); break;
        case 10: *reinterpret_cast< float*>(_v) = _t->gettargetDescentRate(); break;
        case 11: *reinterpret_cast< float*>(_v) = _t->getaverageDescentRate(); break;
        case 12: *reinterpret_cast< float*>(_v) = _t->getaverageDescentThrust(); break;
        case 13: *reinterpret_cast< float*>(_v) = _t->getcalculatedNeutralThrust(); break;
        case 14: *reinterpret_cast< float*>(_v) = _t->getWtgForGroundEffect_BounceVelocity(); break;
        case 15: *reinterpret_cast< float*>(_v) = _t->getWtgForGroundEffect_BounceAccel(); break;
        case 16: *reinterpret_cast< quint8*>(_v) = _t->getState(); break;
        case 17: *reinterpret_cast< quint8*>(_v) = _t->getStateExitReason_0(); break;
        case 18: *reinterpret_cast< quint8*>(_v) = _t->getStateExitReason_1(); break;
        case 19: *reinterpret_cast< quint8*>(_v) = _t->getStateExitReason_2(); break;
        case 20: *reinterpret_cast< quint8*>(_v) = _t->getStateExitReason_3(); break;
        case 21: *reinterpret_cast< quint8*>(_v) = _t->getStateExitReason_4(); break;
        case 22: *reinterpret_cast< quint8*>(_v) = _t->getStateExitReason_5(); break;
        case 23: *reinterpret_cast< quint8*>(_v) = _t->getStateExitReason_6(); break;
        case 24: *reinterpret_cast< quint8*>(_v) = _t->getStateExitReason_7(); break;
        case 25: *reinterpret_cast< quint8*>(_v) = _t->getStateExitReason_8(); break;
        case 26: *reinterpret_cast< quint8*>(_v) = _t->getStateExitReason_9(); break;
        case 27: *reinterpret_cast< quint8*>(_v) = _t->getAltitudeState(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<StatusVtolLand *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAltitudeAtState_0(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setAltitudeAtState_1(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setAltitudeAtState_2(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setAltitudeAtState_3(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setAltitudeAtState_4(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setAltitudeAtState_5(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setAltitudeAtState_6(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setAltitudeAtState_7(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setAltitudeAtState_8(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setAltitudeAtState_9(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->settargetDescentRate(*reinterpret_cast< float*>(_v)); break;
        case 11: _t->setaverageDescentRate(*reinterpret_cast< float*>(_v)); break;
        case 12: _t->setaverageDescentThrust(*reinterpret_cast< float*>(_v)); break;
        case 13: _t->setcalculatedNeutralThrust(*reinterpret_cast< float*>(_v)); break;
        case 14: _t->setWtgForGroundEffect_BounceVelocity(*reinterpret_cast< float*>(_v)); break;
        case 15: _t->setWtgForGroundEffect_BounceAccel(*reinterpret_cast< float*>(_v)); break;
        case 16: _t->setState(*reinterpret_cast< quint8*>(_v)); break;
        case 17: _t->setStateExitReason_0(*reinterpret_cast< quint8*>(_v)); break;
        case 18: _t->setStateExitReason_1(*reinterpret_cast< quint8*>(_v)); break;
        case 19: _t->setStateExitReason_2(*reinterpret_cast< quint8*>(_v)); break;
        case 20: _t->setStateExitReason_3(*reinterpret_cast< quint8*>(_v)); break;
        case 21: _t->setStateExitReason_4(*reinterpret_cast< quint8*>(_v)); break;
        case 22: _t->setStateExitReason_5(*reinterpret_cast< quint8*>(_v)); break;
        case 23: _t->setStateExitReason_6(*reinterpret_cast< quint8*>(_v)); break;
        case 24: _t->setStateExitReason_7(*reinterpret_cast< quint8*>(_v)); break;
        case 25: _t->setStateExitReason_8(*reinterpret_cast< quint8*>(_v)); break;
        case 26: _t->setStateExitReason_9(*reinterpret_cast< quint8*>(_v)); break;
        case 27: _t->setAltitudeState(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject StatusVtolLand::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_StatusVtolLand.data,
    qt_meta_data_StatusVtolLand,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StatusVtolLand::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StatusVtolLand::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StatusVtolLand.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int StatusVtolLand::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 94)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 94;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 94)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 94;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 28;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 28;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 28;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 28;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 28;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void StatusVtolLand::AltitudeAtStateChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StatusVtolLand::AltitudeAtState_0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StatusVtolLand::AltitudeAtState_1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void StatusVtolLand::AltitudeAtState_2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void StatusVtolLand::AltitudeAtState_3Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void StatusVtolLand::AltitudeAtState_4Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void StatusVtolLand::AltitudeAtState_5Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void StatusVtolLand::AltitudeAtState_6Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void StatusVtolLand::AltitudeAtState_7Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void StatusVtolLand::AltitudeAtState_8Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void StatusVtolLand::AltitudeAtState_9Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void StatusVtolLand::targetDescentRateChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void StatusVtolLand::averageDescentRateChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void StatusVtolLand::averageDescentThrustChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void StatusVtolLand::calculatedNeutralThrustChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void StatusVtolLand::WtgForGroundEffectChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void StatusVtolLand::WtgForGroundEffect_BounceVelocityChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void StatusVtolLand::WtgForGroundEffect_BounceAccelChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void StatusVtolLand::StateChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void StatusVtolLand::StateExitReasonChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void StatusVtolLand::StateExitReason_0Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void StatusVtolLand::StateExitReason_1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void StatusVtolLand::StateExitReason_2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void StatusVtolLand::StateExitReason_3Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void StatusVtolLand::StateExitReason_4Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void StatusVtolLand::StateExitReason_5Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void StatusVtolLand::StateExitReason_6Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void StatusVtolLand::StateExitReason_7Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void StatusVtolLand::StateExitReason_8Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void StatusVtolLand::StateExitReason_9Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void StatusVtolLand::AltitudeStateChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
