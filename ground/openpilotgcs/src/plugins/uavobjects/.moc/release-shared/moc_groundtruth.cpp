/****************************************************************************
** Meta object code from reading C++ file 'groundtruth.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/groundtruth.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'groundtruth.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GroundTruth_t {
    QByteArrayData data[96];
    char stringdata0[1562];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GroundTruth_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GroundTruth_t qt_meta_stringdata_GroundTruth = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GroundTruth"
QT_MOC_LITERAL(1, 12, 22), // "AccelerationXYZChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "index"
QT_MOC_LITERAL(4, 42, 5), // "value"
QT_MOC_LITERAL(5, 48, 24), // "AccelerationXYZ_0Changed"
QT_MOC_LITERAL(6, 73, 24), // "AccelerationXYZ_1Changed"
QT_MOC_LITERAL(7, 98, 24), // "AccelerationXYZ_2Changed"
QT_MOC_LITERAL(8, 123, 18), // "PositionNEDChanged"
QT_MOC_LITERAL(9, 142, 20), // "PositionNED_0Changed"
QT_MOC_LITERAL(10, 163, 20), // "PositionNED_1Changed"
QT_MOC_LITERAL(11, 184, 20), // "PositionNED_2Changed"
QT_MOC_LITERAL(12, 205, 18), // "VelocityNEDChanged"
QT_MOC_LITERAL(13, 224, 20), // "VelocityNED_0Changed"
QT_MOC_LITERAL(14, 245, 20), // "VelocityNED_1Changed"
QT_MOC_LITERAL(15, 266, 20), // "VelocityNED_2Changed"
QT_MOC_LITERAL(16, 287, 10), // "RPYChanged"
QT_MOC_LITERAL(17, 298, 12), // "RPY_0Changed"
QT_MOC_LITERAL(18, 311, 12), // "RPY_1Changed"
QT_MOC_LITERAL(19, 324, 12), // "RPY_2Changed"
QT_MOC_LITERAL(20, 337, 19), // "AngularRatesChanged"
QT_MOC_LITERAL(21, 357, 21), // "AngularRates_0Changed"
QT_MOC_LITERAL(22, 379, 21), // "AngularRates_1Changed"
QT_MOC_LITERAL(23, 401, 21), // "AngularRates_2Changed"
QT_MOC_LITERAL(24, 423, 19), // "TrueAirspeedChanged"
QT_MOC_LITERAL(25, 443, 25), // "CalibratedAirspeedChanged"
QT_MOC_LITERAL(26, 469, 20), // "AngleOfAttackChanged"
QT_MOC_LITERAL(27, 490, 18), // "AngleOfSlipChanged"
QT_MOC_LITERAL(28, 509, 18), // "setAccelerationXYZ"
QT_MOC_LITERAL(29, 528, 20), // "setAccelerationXYZ_0"
QT_MOC_LITERAL(30, 549, 20), // "setAccelerationXYZ_1"
QT_MOC_LITERAL(31, 570, 20), // "setAccelerationXYZ_2"
QT_MOC_LITERAL(32, 591, 14), // "setPositionNED"
QT_MOC_LITERAL(33, 606, 16), // "setPositionNED_0"
QT_MOC_LITERAL(34, 623, 16), // "setPositionNED_1"
QT_MOC_LITERAL(35, 640, 16), // "setPositionNED_2"
QT_MOC_LITERAL(36, 657, 14), // "setVelocityNED"
QT_MOC_LITERAL(37, 672, 16), // "setVelocityNED_0"
QT_MOC_LITERAL(38, 689, 16), // "setVelocityNED_1"
QT_MOC_LITERAL(39, 706, 16), // "setVelocityNED_2"
QT_MOC_LITERAL(40, 723, 6), // "setRPY"
QT_MOC_LITERAL(41, 730, 8), // "setRPY_0"
QT_MOC_LITERAL(42, 739, 8), // "setRPY_1"
QT_MOC_LITERAL(43, 748, 8), // "setRPY_2"
QT_MOC_LITERAL(44, 757, 15), // "setAngularRates"
QT_MOC_LITERAL(45, 773, 17), // "setAngularRates_0"
QT_MOC_LITERAL(46, 791, 17), // "setAngularRates_1"
QT_MOC_LITERAL(47, 809, 17), // "setAngularRates_2"
QT_MOC_LITERAL(48, 827, 15), // "setTrueAirspeed"
QT_MOC_LITERAL(49, 843, 21), // "setCalibratedAirspeed"
QT_MOC_LITERAL(50, 865, 16), // "setAngleOfAttack"
QT_MOC_LITERAL(51, 882, 14), // "setAngleOfSlip"
QT_MOC_LITERAL(52, 897, 17), // "emitNotifications"
QT_MOC_LITERAL(53, 915, 18), // "getAccelerationXYZ"
QT_MOC_LITERAL(54, 934, 20), // "getAccelerationXYZ_0"
QT_MOC_LITERAL(55, 955, 20), // "getAccelerationXYZ_1"
QT_MOC_LITERAL(56, 976, 20), // "getAccelerationXYZ_2"
QT_MOC_LITERAL(57, 997, 14), // "getPositionNED"
QT_MOC_LITERAL(58, 1012, 16), // "getPositionNED_0"
QT_MOC_LITERAL(59, 1029, 16), // "getPositionNED_1"
QT_MOC_LITERAL(60, 1046, 16), // "getPositionNED_2"
QT_MOC_LITERAL(61, 1063, 14), // "getVelocityNED"
QT_MOC_LITERAL(62, 1078, 16), // "getVelocityNED_0"
QT_MOC_LITERAL(63, 1095, 16), // "getVelocityNED_1"
QT_MOC_LITERAL(64, 1112, 16), // "getVelocityNED_2"
QT_MOC_LITERAL(65, 1129, 6), // "getRPY"
QT_MOC_LITERAL(66, 1136, 8), // "getRPY_0"
QT_MOC_LITERAL(67, 1145, 8), // "getRPY_1"
QT_MOC_LITERAL(68, 1154, 8), // "getRPY_2"
QT_MOC_LITERAL(69, 1163, 15), // "getAngularRates"
QT_MOC_LITERAL(70, 1179, 17), // "getAngularRates_0"
QT_MOC_LITERAL(71, 1197, 17), // "getAngularRates_1"
QT_MOC_LITERAL(72, 1215, 17), // "getAngularRates_2"
QT_MOC_LITERAL(73, 1233, 15), // "getTrueAirspeed"
QT_MOC_LITERAL(74, 1249, 21), // "getCalibratedAirspeed"
QT_MOC_LITERAL(75, 1271, 16), // "getAngleOfAttack"
QT_MOC_LITERAL(76, 1288, 14), // "getAngleOfSlip"
QT_MOC_LITERAL(77, 1303, 17), // "AccelerationXYZ_0"
QT_MOC_LITERAL(78, 1321, 17), // "AccelerationXYZ_1"
QT_MOC_LITERAL(79, 1339, 17), // "AccelerationXYZ_2"
QT_MOC_LITERAL(80, 1357, 13), // "PositionNED_0"
QT_MOC_LITERAL(81, 1371, 13), // "PositionNED_1"
QT_MOC_LITERAL(82, 1385, 13), // "PositionNED_2"
QT_MOC_LITERAL(83, 1399, 13), // "VelocityNED_0"
QT_MOC_LITERAL(84, 1413, 13), // "VelocityNED_1"
QT_MOC_LITERAL(85, 1427, 13), // "VelocityNED_2"
QT_MOC_LITERAL(86, 1441, 5), // "RPY_0"
QT_MOC_LITERAL(87, 1447, 5), // "RPY_1"
QT_MOC_LITERAL(88, 1453, 5), // "RPY_2"
QT_MOC_LITERAL(89, 1459, 14), // "AngularRates_0"
QT_MOC_LITERAL(90, 1474, 14), // "AngularRates_1"
QT_MOC_LITERAL(91, 1489, 14), // "AngularRates_2"
QT_MOC_LITERAL(92, 1504, 12), // "TrueAirspeed"
QT_MOC_LITERAL(93, 1517, 18), // "CalibratedAirspeed"
QT_MOC_LITERAL(94, 1536, 13), // "AngleOfAttack"
QT_MOC_LITERAL(95, 1550, 11) // "AngleOfSlip"

    },
    "GroundTruth\0AccelerationXYZChanged\0\0"
    "index\0value\0AccelerationXYZ_0Changed\0"
    "AccelerationXYZ_1Changed\0"
    "AccelerationXYZ_2Changed\0PositionNEDChanged\0"
    "PositionNED_0Changed\0PositionNED_1Changed\0"
    "PositionNED_2Changed\0VelocityNEDChanged\0"
    "VelocityNED_0Changed\0VelocityNED_1Changed\0"
    "VelocityNED_2Changed\0RPYChanged\0"
    "RPY_0Changed\0RPY_1Changed\0RPY_2Changed\0"
    "AngularRatesChanged\0AngularRates_0Changed\0"
    "AngularRates_1Changed\0AngularRates_2Changed\0"
    "TrueAirspeedChanged\0CalibratedAirspeedChanged\0"
    "AngleOfAttackChanged\0AngleOfSlipChanged\0"
    "setAccelerationXYZ\0setAccelerationXYZ_0\0"
    "setAccelerationXYZ_1\0setAccelerationXYZ_2\0"
    "setPositionNED\0setPositionNED_0\0"
    "setPositionNED_1\0setPositionNED_2\0"
    "setVelocityNED\0setVelocityNED_0\0"
    "setVelocityNED_1\0setVelocityNED_2\0"
    "setRPY\0setRPY_0\0setRPY_1\0setRPY_2\0"
    "setAngularRates\0setAngularRates_0\0"
    "setAngularRates_1\0setAngularRates_2\0"
    "setTrueAirspeed\0setCalibratedAirspeed\0"
    "setAngleOfAttack\0setAngleOfSlip\0"
    "emitNotifications\0getAccelerationXYZ\0"
    "getAccelerationXYZ_0\0getAccelerationXYZ_1\0"
    "getAccelerationXYZ_2\0getPositionNED\0"
    "getPositionNED_0\0getPositionNED_1\0"
    "getPositionNED_2\0getVelocityNED\0"
    "getVelocityNED_0\0getVelocityNED_1\0"
    "getVelocityNED_2\0getRPY\0getRPY_0\0"
    "getRPY_1\0getRPY_2\0getAngularRates\0"
    "getAngularRates_0\0getAngularRates_1\0"
    "getAngularRates_2\0getTrueAirspeed\0"
    "getCalibratedAirspeed\0getAngleOfAttack\0"
    "getAngleOfSlip\0AccelerationXYZ_0\0"
    "AccelerationXYZ_1\0AccelerationXYZ_2\0"
    "PositionNED_0\0PositionNED_1\0PositionNED_2\0"
    "VelocityNED_0\0VelocityNED_1\0VelocityNED_2\0"
    "RPY_0\0RPY_1\0RPY_2\0AngularRates_0\0"
    "AngularRates_1\0AngularRates_2\0"
    "TrueAirspeed\0CalibratedAirspeed\0"
    "AngleOfAttack\0AngleOfSlip"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GroundTruth[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      73,   14, // methods
      19,  578, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      24,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  379,    2, 0x06 /* Public */,
       5,    1,  384,    2, 0x06 /* Public */,
       6,    1,  387,    2, 0x06 /* Public */,
       7,    1,  390,    2, 0x06 /* Public */,
       8,    2,  393,    2, 0x06 /* Public */,
       9,    1,  398,    2, 0x06 /* Public */,
      10,    1,  401,    2, 0x06 /* Public */,
      11,    1,  404,    2, 0x06 /* Public */,
      12,    2,  407,    2, 0x06 /* Public */,
      13,    1,  412,    2, 0x06 /* Public */,
      14,    1,  415,    2, 0x06 /* Public */,
      15,    1,  418,    2, 0x06 /* Public */,
      16,    2,  421,    2, 0x06 /* Public */,
      17,    1,  426,    2, 0x06 /* Public */,
      18,    1,  429,    2, 0x06 /* Public */,
      19,    1,  432,    2, 0x06 /* Public */,
      20,    2,  435,    2, 0x06 /* Public */,
      21,    1,  440,    2, 0x06 /* Public */,
      22,    1,  443,    2, 0x06 /* Public */,
      23,    1,  446,    2, 0x06 /* Public */,
      24,    1,  449,    2, 0x06 /* Public */,
      25,    1,  452,    2, 0x06 /* Public */,
      26,    1,  455,    2, 0x06 /* Public */,
      27,    1,  458,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      28,    2,  461,    2, 0x0a /* Public */,
      29,    1,  466,    2, 0x0a /* Public */,
      30,    1,  469,    2, 0x0a /* Public */,
      31,    1,  472,    2, 0x0a /* Public */,
      32,    2,  475,    2, 0x0a /* Public */,
      33,    1,  480,    2, 0x0a /* Public */,
      34,    1,  483,    2, 0x0a /* Public */,
      35,    1,  486,    2, 0x0a /* Public */,
      36,    2,  489,    2, 0x0a /* Public */,
      37,    1,  494,    2, 0x0a /* Public */,
      38,    1,  497,    2, 0x0a /* Public */,
      39,    1,  500,    2, 0x0a /* Public */,
      40,    2,  503,    2, 0x0a /* Public */,
      41,    1,  508,    2, 0x0a /* Public */,
      42,    1,  511,    2, 0x0a /* Public */,
      43,    1,  514,    2, 0x0a /* Public */,
      44,    2,  517,    2, 0x0a /* Public */,
      45,    1,  522,    2, 0x0a /* Public */,
      46,    1,  525,    2, 0x0a /* Public */,
      47,    1,  528,    2, 0x0a /* Public */,
      48,    1,  531,    2, 0x0a /* Public */,
      49,    1,  534,    2, 0x0a /* Public */,
      50,    1,  537,    2, 0x0a /* Public */,
      51,    1,  540,    2, 0x0a /* Public */,
      52,    0,  543,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      53,    1,  544,    2, 0x02 /* Public */,
      54,    0,  547,    2, 0x02 /* Public */,
      55,    0,  548,    2, 0x02 /* Public */,
      56,    0,  549,    2, 0x02 /* Public */,
      57,    1,  550,    2, 0x02 /* Public */,
      58,    0,  553,    2, 0x02 /* Public */,
      59,    0,  554,    2, 0x02 /* Public */,
      60,    0,  555,    2, 0x02 /* Public */,
      61,    1,  556,    2, 0x02 /* Public */,
      62,    0,  559,    2, 0x02 /* Public */,
      63,    0,  560,    2, 0x02 /* Public */,
      64,    0,  561,    2, 0x02 /* Public */,
      65,    1,  562,    2, 0x02 /* Public */,
      66,    0,  565,    2, 0x02 /* Public */,
      67,    0,  566,    2, 0x02 /* Public */,
      68,    0,  567,    2, 0x02 /* Public */,
      69,    1,  568,    2, 0x02 /* Public */,
      70,    0,  571,    2, 0x02 /* Public */,
      71,    0,  572,    2, 0x02 /* Public */,
      72,    0,  573,    2, 0x02 /* Public */,
      73,    0,  574,    2, 0x02 /* Public */,
      74,    0,  575,    2, 0x02 /* Public */,
      75,    0,  576,    2, 0x02 /* Public */,
      76,    0,  577,    2, 0x02 /* Public */,

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
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
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
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
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
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,

 // properties: name, type, flags
      77, QMetaType::Float, 0x00495103,
      78, QMetaType::Float, 0x00495103,
      79, QMetaType::Float, 0x00495103,
      80, QMetaType::Float, 0x00495103,
      81, QMetaType::Float, 0x00495103,
      82, QMetaType::Float, 0x00495103,
      83, QMetaType::Float, 0x00495103,
      84, QMetaType::Float, 0x00495103,
      85, QMetaType::Float, 0x00495103,
      86, QMetaType::Float, 0x00495103,
      87, QMetaType::Float, 0x00495103,
      88, QMetaType::Float, 0x00495103,
      89, QMetaType::Float, 0x00495103,
      90, QMetaType::Float, 0x00495103,
      91, QMetaType::Float, 0x00495103,
      92, QMetaType::Float, 0x00495103,
      93, QMetaType::Float, 0x00495103,
      94, QMetaType::Float, 0x00495103,
      95, QMetaType::Float, 0x00495103,

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
      20,
      21,
      22,
      23,

       0        // eod
};

void GroundTruth::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GroundTruth *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->AccelerationXYZChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->AccelerationXYZ_0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->AccelerationXYZ_1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->AccelerationXYZ_2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->PositionNEDChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->PositionNED_0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->PositionNED_1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->PositionNED_2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->VelocityNEDChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 9: _t->VelocityNED_0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->VelocityNED_1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->VelocityNED_2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->RPYChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 13: _t->RPY_0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->RPY_1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->RPY_2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->AngularRatesChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 17: _t->AngularRates_0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->AngularRates_1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->AngularRates_2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->TrueAirspeedChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->CalibratedAirspeedChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: _t->AngleOfAttackChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->AngleOfSlipChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->setAccelerationXYZ((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 25: _t->setAccelerationXYZ_0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 26: _t->setAccelerationXYZ_1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->setAccelerationXYZ_2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 28: _t->setPositionNED((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 29: _t->setPositionNED_0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 30: _t->setPositionNED_1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 31: _t->setPositionNED_2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 32: _t->setVelocityNED((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 33: _t->setVelocityNED_0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 34: _t->setVelocityNED_1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 35: _t->setVelocityNED_2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 36: _t->setRPY((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 37: _t->setRPY_0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 38: _t->setRPY_1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 39: _t->setRPY_2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 40: _t->setAngularRates((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 41: _t->setAngularRates_0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 42: _t->setAngularRates_1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 43: _t->setAngularRates_2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 44: _t->setTrueAirspeed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 45: _t->setCalibratedAirspeed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 46: _t->setAngleOfAttack((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 47: _t->setAngleOfSlip((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 48: _t->emitNotifications(); break;
        case 49: { float _r = _t->getAccelerationXYZ((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 50: { float _r = _t->getAccelerationXYZ_0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 51: { float _r = _t->getAccelerationXYZ_1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 52: { float _r = _t->getAccelerationXYZ_2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 53: { float _r = _t->getPositionNED((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 54: { float _r = _t->getPositionNED_0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 55: { float _r = _t->getPositionNED_1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 56: { float _r = _t->getPositionNED_2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 57: { float _r = _t->getVelocityNED((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 58: { float _r = _t->getVelocityNED_0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 59: { float _r = _t->getVelocityNED_1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 60: { float _r = _t->getVelocityNED_2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 61: { float _r = _t->getRPY((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 62: { float _r = _t->getRPY_0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 63: { float _r = _t->getRPY_1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 64: { float _r = _t->getRPY_2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 65: { float _r = _t->getAngularRates((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 66: { float _r = _t->getAngularRates_0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 67: { float _r = _t->getAngularRates_1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 68: { float _r = _t->getAngularRates_2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 69: { float _r = _t->getTrueAirspeed();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 70: { float _r = _t->getCalibratedAirspeed();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 71: { float _r = _t->getAngleOfAttack();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 72: { float _r = _t->getAngleOfSlip();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GroundTruth::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::AccelerationXYZChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::AccelerationXYZ_0Changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::AccelerationXYZ_1Changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::AccelerationXYZ_2Changed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::PositionNEDChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::PositionNED_0Changed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::PositionNED_1Changed)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::PositionNED_2Changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::VelocityNEDChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::VelocityNED_0Changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::VelocityNED_1Changed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::VelocityNED_2Changed)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::RPYChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::RPY_0Changed)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::RPY_1Changed)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::RPY_2Changed)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::AngularRatesChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::AngularRates_0Changed)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::AngularRates_1Changed)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::AngularRates_2Changed)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::TrueAirspeedChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::CalibratedAirspeedChanged)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::AngleOfAttackChanged)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (GroundTruth::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroundTruth::AngleOfSlipChanged)) {
                *result = 23;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<GroundTruth *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getAccelerationXYZ_0(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getAccelerationXYZ_1(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getAccelerationXYZ_2(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getPositionNED_0(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getPositionNED_1(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getPositionNED_2(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getVelocityNED_0(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getVelocityNED_1(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getVelocityNED_2(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->getRPY_0(); break;
        case 10: *reinterpret_cast< float*>(_v) = _t->getRPY_1(); break;
        case 11: *reinterpret_cast< float*>(_v) = _t->getRPY_2(); break;
        case 12: *reinterpret_cast< float*>(_v) = _t->getAngularRates_0(); break;
        case 13: *reinterpret_cast< float*>(_v) = _t->getAngularRates_1(); break;
        case 14: *reinterpret_cast< float*>(_v) = _t->getAngularRates_2(); break;
        case 15: *reinterpret_cast< float*>(_v) = _t->getTrueAirspeed(); break;
        case 16: *reinterpret_cast< float*>(_v) = _t->getCalibratedAirspeed(); break;
        case 17: *reinterpret_cast< float*>(_v) = _t->getAngleOfAttack(); break;
        case 18: *reinterpret_cast< float*>(_v) = _t->getAngleOfSlip(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<GroundTruth *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAccelerationXYZ_0(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setAccelerationXYZ_1(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setAccelerationXYZ_2(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setPositionNED_0(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setPositionNED_1(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setPositionNED_2(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setVelocityNED_0(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setVelocityNED_1(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setVelocityNED_2(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setRPY_0(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setRPY_1(*reinterpret_cast< float*>(_v)); break;
        case 11: _t->setRPY_2(*reinterpret_cast< float*>(_v)); break;
        case 12: _t->setAngularRates_0(*reinterpret_cast< float*>(_v)); break;
        case 13: _t->setAngularRates_1(*reinterpret_cast< float*>(_v)); break;
        case 14: _t->setAngularRates_2(*reinterpret_cast< float*>(_v)); break;
        case 15: _t->setTrueAirspeed(*reinterpret_cast< float*>(_v)); break;
        case 16: _t->setCalibratedAirspeed(*reinterpret_cast< float*>(_v)); break;
        case 17: _t->setAngleOfAttack(*reinterpret_cast< float*>(_v)); break;
        case 18: _t->setAngleOfSlip(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject GroundTruth::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_GroundTruth.data,
    qt_meta_data_GroundTruth,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GroundTruth::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GroundTruth::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GroundTruth.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int GroundTruth::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 73)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 73;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 73)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 73;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 19;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GroundTruth::AccelerationXYZChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GroundTruth::AccelerationXYZ_0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GroundTruth::AccelerationXYZ_1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GroundTruth::AccelerationXYZ_2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GroundTruth::PositionNEDChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GroundTruth::PositionNED_0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GroundTruth::PositionNED_1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void GroundTruth::PositionNED_2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void GroundTruth::VelocityNEDChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void GroundTruth::VelocityNED_0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void GroundTruth::VelocityNED_1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void GroundTruth::VelocityNED_2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void GroundTruth::RPYChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void GroundTruth::RPY_0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void GroundTruth::RPY_1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void GroundTruth::RPY_2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void GroundTruth::AngularRatesChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void GroundTruth::AngularRates_0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void GroundTruth::AngularRates_1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void GroundTruth::AngularRates_2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void GroundTruth::TrueAirspeedChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void GroundTruth::CalibratedAirspeedChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void GroundTruth::AngleOfAttackChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void GroundTruth::AngleOfSlipChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
