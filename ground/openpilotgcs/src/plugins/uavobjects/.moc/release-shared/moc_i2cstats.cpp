/****************************************************************************
** Meta object code from reading C++ file 'i2cstats.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/i2cstats.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'i2cstats.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_I2CStats_t {
    QByteArrayData data[121];
    char stringdata0[1774];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_I2CStats_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_I2CStats_t qt_meta_stringdata_I2CStats = {
    {
QT_MOC_LITERAL(0, 0, 8), // "I2CStats"
QT_MOC_LITERAL(1, 9, 16), // "evirq_logChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "index"
QT_MOC_LITERAL(4, 33, 5), // "value"
QT_MOC_LITERAL(5, 39, 18), // "evirq_log_0Changed"
QT_MOC_LITERAL(6, 58, 18), // "evirq_log_1Changed"
QT_MOC_LITERAL(7, 77, 18), // "evirq_log_2Changed"
QT_MOC_LITERAL(8, 96, 18), // "evirq_log_3Changed"
QT_MOC_LITERAL(9, 115, 18), // "evirq_log_4Changed"
QT_MOC_LITERAL(10, 134, 16), // "erirq_logChanged"
QT_MOC_LITERAL(11, 151, 18), // "erirq_log_0Changed"
QT_MOC_LITERAL(12, 170, 18), // "erirq_log_1Changed"
QT_MOC_LITERAL(13, 189, 18), // "erirq_log_2Changed"
QT_MOC_LITERAL(14, 208, 18), // "erirq_log_3Changed"
QT_MOC_LITERAL(15, 227, 18), // "erirq_log_4Changed"
QT_MOC_LITERAL(16, 246, 19), // "event_errorsChanged"
QT_MOC_LITERAL(17, 266, 17), // "fsm_errorsChanged"
QT_MOC_LITERAL(18, 284, 17), // "irq_errorsChanged"
QT_MOC_LITERAL(19, 302, 12), // "nacksChanged"
QT_MOC_LITERAL(20, 315, 15), // "timeoutsChanged"
QT_MOC_LITERAL(21, 331, 22), // "last_error_typeChanged"
QT_MOC_LITERAL(22, 354, 16), // "event_logChanged"
QT_MOC_LITERAL(23, 371, 18), // "event_log_0Changed"
QT_MOC_LITERAL(24, 390, 18), // "event_log_1Changed"
QT_MOC_LITERAL(25, 409, 18), // "event_log_2Changed"
QT_MOC_LITERAL(26, 428, 18), // "event_log_3Changed"
QT_MOC_LITERAL(27, 447, 18), // "event_log_4Changed"
QT_MOC_LITERAL(28, 466, 16), // "state_logChanged"
QT_MOC_LITERAL(29, 483, 18), // "state_log_0Changed"
QT_MOC_LITERAL(30, 502, 18), // "state_log_1Changed"
QT_MOC_LITERAL(31, 521, 18), // "state_log_2Changed"
QT_MOC_LITERAL(32, 540, 18), // "state_log_3Changed"
QT_MOC_LITERAL(33, 559, 18), // "state_log_4Changed"
QT_MOC_LITERAL(34, 578, 12), // "setevirq_log"
QT_MOC_LITERAL(35, 591, 14), // "setevirq_log_0"
QT_MOC_LITERAL(36, 606, 14), // "setevirq_log_1"
QT_MOC_LITERAL(37, 621, 14), // "setevirq_log_2"
QT_MOC_LITERAL(38, 636, 14), // "setevirq_log_3"
QT_MOC_LITERAL(39, 651, 14), // "setevirq_log_4"
QT_MOC_LITERAL(40, 666, 12), // "seterirq_log"
QT_MOC_LITERAL(41, 679, 14), // "seterirq_log_0"
QT_MOC_LITERAL(42, 694, 14), // "seterirq_log_1"
QT_MOC_LITERAL(43, 709, 14), // "seterirq_log_2"
QT_MOC_LITERAL(44, 724, 14), // "seterirq_log_3"
QT_MOC_LITERAL(45, 739, 14), // "seterirq_log_4"
QT_MOC_LITERAL(46, 754, 15), // "setevent_errors"
QT_MOC_LITERAL(47, 770, 13), // "setfsm_errors"
QT_MOC_LITERAL(48, 784, 13), // "setirq_errors"
QT_MOC_LITERAL(49, 798, 8), // "setnacks"
QT_MOC_LITERAL(50, 807, 11), // "settimeouts"
QT_MOC_LITERAL(51, 819, 18), // "setlast_error_type"
QT_MOC_LITERAL(52, 838, 12), // "setevent_log"
QT_MOC_LITERAL(53, 851, 14), // "setevent_log_0"
QT_MOC_LITERAL(54, 866, 14), // "setevent_log_1"
QT_MOC_LITERAL(55, 881, 14), // "setevent_log_2"
QT_MOC_LITERAL(56, 896, 14), // "setevent_log_3"
QT_MOC_LITERAL(57, 911, 14), // "setevent_log_4"
QT_MOC_LITERAL(58, 926, 12), // "setstate_log"
QT_MOC_LITERAL(59, 939, 14), // "setstate_log_0"
QT_MOC_LITERAL(60, 954, 14), // "setstate_log_1"
QT_MOC_LITERAL(61, 969, 14), // "setstate_log_2"
QT_MOC_LITERAL(62, 984, 14), // "setstate_log_3"
QT_MOC_LITERAL(63, 999, 14), // "setstate_log_4"
QT_MOC_LITERAL(64, 1014, 17), // "emitNotifications"
QT_MOC_LITERAL(65, 1032, 12), // "getevirq_log"
QT_MOC_LITERAL(66, 1045, 14), // "getevirq_log_0"
QT_MOC_LITERAL(67, 1060, 14), // "getevirq_log_1"
QT_MOC_LITERAL(68, 1075, 14), // "getevirq_log_2"
QT_MOC_LITERAL(69, 1090, 14), // "getevirq_log_3"
QT_MOC_LITERAL(70, 1105, 14), // "getevirq_log_4"
QT_MOC_LITERAL(71, 1120, 12), // "geterirq_log"
QT_MOC_LITERAL(72, 1133, 14), // "geterirq_log_0"
QT_MOC_LITERAL(73, 1148, 14), // "geterirq_log_1"
QT_MOC_LITERAL(74, 1163, 14), // "geterirq_log_2"
QT_MOC_LITERAL(75, 1178, 14), // "geterirq_log_3"
QT_MOC_LITERAL(76, 1193, 14), // "geterirq_log_4"
QT_MOC_LITERAL(77, 1208, 15), // "getevent_errors"
QT_MOC_LITERAL(78, 1224, 13), // "getfsm_errors"
QT_MOC_LITERAL(79, 1238, 13), // "getirq_errors"
QT_MOC_LITERAL(80, 1252, 8), // "getnacks"
QT_MOC_LITERAL(81, 1261, 11), // "gettimeouts"
QT_MOC_LITERAL(82, 1273, 18), // "getlast_error_type"
QT_MOC_LITERAL(83, 1292, 12), // "getevent_log"
QT_MOC_LITERAL(84, 1305, 14), // "getevent_log_0"
QT_MOC_LITERAL(85, 1320, 14), // "getevent_log_1"
QT_MOC_LITERAL(86, 1335, 14), // "getevent_log_2"
QT_MOC_LITERAL(87, 1350, 14), // "getevent_log_3"
QT_MOC_LITERAL(88, 1365, 14), // "getevent_log_4"
QT_MOC_LITERAL(89, 1380, 12), // "getstate_log"
QT_MOC_LITERAL(90, 1393, 14), // "getstate_log_0"
QT_MOC_LITERAL(91, 1408, 14), // "getstate_log_1"
QT_MOC_LITERAL(92, 1423, 14), // "getstate_log_2"
QT_MOC_LITERAL(93, 1438, 14), // "getstate_log_3"
QT_MOC_LITERAL(94, 1453, 14), // "getstate_log_4"
QT_MOC_LITERAL(95, 1468, 11), // "evirq_log_0"
QT_MOC_LITERAL(96, 1480, 11), // "evirq_log_1"
QT_MOC_LITERAL(97, 1492, 11), // "evirq_log_2"
QT_MOC_LITERAL(98, 1504, 11), // "evirq_log_3"
QT_MOC_LITERAL(99, 1516, 11), // "evirq_log_4"
QT_MOC_LITERAL(100, 1528, 11), // "erirq_log_0"
QT_MOC_LITERAL(101, 1540, 11), // "erirq_log_1"
QT_MOC_LITERAL(102, 1552, 11), // "erirq_log_2"
QT_MOC_LITERAL(103, 1564, 11), // "erirq_log_3"
QT_MOC_LITERAL(104, 1576, 11), // "erirq_log_4"
QT_MOC_LITERAL(105, 1588, 12), // "event_errors"
QT_MOC_LITERAL(106, 1601, 10), // "fsm_errors"
QT_MOC_LITERAL(107, 1612, 10), // "irq_errors"
QT_MOC_LITERAL(108, 1623, 5), // "nacks"
QT_MOC_LITERAL(109, 1629, 8), // "timeouts"
QT_MOC_LITERAL(110, 1638, 15), // "last_error_type"
QT_MOC_LITERAL(111, 1654, 11), // "event_log_0"
QT_MOC_LITERAL(112, 1666, 11), // "event_log_1"
QT_MOC_LITERAL(113, 1678, 11), // "event_log_2"
QT_MOC_LITERAL(114, 1690, 11), // "event_log_3"
QT_MOC_LITERAL(115, 1702, 11), // "event_log_4"
QT_MOC_LITERAL(116, 1714, 11), // "state_log_0"
QT_MOC_LITERAL(117, 1726, 11), // "state_log_1"
QT_MOC_LITERAL(118, 1738, 11), // "state_log_2"
QT_MOC_LITERAL(119, 1750, 11), // "state_log_3"
QT_MOC_LITERAL(120, 1762, 11) // "state_log_4"

    },
    "I2CStats\0evirq_logChanged\0\0index\0value\0"
    "evirq_log_0Changed\0evirq_log_1Changed\0"
    "evirq_log_2Changed\0evirq_log_3Changed\0"
    "evirq_log_4Changed\0erirq_logChanged\0"
    "erirq_log_0Changed\0erirq_log_1Changed\0"
    "erirq_log_2Changed\0erirq_log_3Changed\0"
    "erirq_log_4Changed\0event_errorsChanged\0"
    "fsm_errorsChanged\0irq_errorsChanged\0"
    "nacksChanged\0timeoutsChanged\0"
    "last_error_typeChanged\0event_logChanged\0"
    "event_log_0Changed\0event_log_1Changed\0"
    "event_log_2Changed\0event_log_3Changed\0"
    "event_log_4Changed\0state_logChanged\0"
    "state_log_0Changed\0state_log_1Changed\0"
    "state_log_2Changed\0state_log_3Changed\0"
    "state_log_4Changed\0setevirq_log\0"
    "setevirq_log_0\0setevirq_log_1\0"
    "setevirq_log_2\0setevirq_log_3\0"
    "setevirq_log_4\0seterirq_log\0seterirq_log_0\0"
    "seterirq_log_1\0seterirq_log_2\0"
    "seterirq_log_3\0seterirq_log_4\0"
    "setevent_errors\0setfsm_errors\0"
    "setirq_errors\0setnacks\0settimeouts\0"
    "setlast_error_type\0setevent_log\0"
    "setevent_log_0\0setevent_log_1\0"
    "setevent_log_2\0setevent_log_3\0"
    "setevent_log_4\0setstate_log\0setstate_log_0\0"
    "setstate_log_1\0setstate_log_2\0"
    "setstate_log_3\0setstate_log_4\0"
    "emitNotifications\0getevirq_log\0"
    "getevirq_log_0\0getevirq_log_1\0"
    "getevirq_log_2\0getevirq_log_3\0"
    "getevirq_log_4\0geterirq_log\0geterirq_log_0\0"
    "geterirq_log_1\0geterirq_log_2\0"
    "geterirq_log_3\0geterirq_log_4\0"
    "getevent_errors\0getfsm_errors\0"
    "getirq_errors\0getnacks\0gettimeouts\0"
    "getlast_error_type\0getevent_log\0"
    "getevent_log_0\0getevent_log_1\0"
    "getevent_log_2\0getevent_log_3\0"
    "getevent_log_4\0getstate_log\0getstate_log_0\0"
    "getstate_log_1\0getstate_log_2\0"
    "getstate_log_3\0getstate_log_4\0evirq_log_0\0"
    "evirq_log_1\0evirq_log_2\0evirq_log_3\0"
    "evirq_log_4\0erirq_log_0\0erirq_log_1\0"
    "erirq_log_2\0erirq_log_3\0erirq_log_4\0"
    "event_errors\0fsm_errors\0irq_errors\0"
    "nacks\0timeouts\0last_error_type\0"
    "event_log_0\0event_log_1\0event_log_2\0"
    "event_log_3\0event_log_4\0state_log_0\0"
    "state_log_1\0state_log_2\0state_log_3\0"
    "state_log_4"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_I2CStats[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      91,   14, // methods
      26,  704, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      30,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  469,    2, 0x06 /* Public */,
       5,    1,  474,    2, 0x06 /* Public */,
       6,    1,  477,    2, 0x06 /* Public */,
       7,    1,  480,    2, 0x06 /* Public */,
       8,    1,  483,    2, 0x06 /* Public */,
       9,    1,  486,    2, 0x06 /* Public */,
      10,    2,  489,    2, 0x06 /* Public */,
      11,    1,  494,    2, 0x06 /* Public */,
      12,    1,  497,    2, 0x06 /* Public */,
      13,    1,  500,    2, 0x06 /* Public */,
      14,    1,  503,    2, 0x06 /* Public */,
      15,    1,  506,    2, 0x06 /* Public */,
      16,    1,  509,    2, 0x06 /* Public */,
      17,    1,  512,    2, 0x06 /* Public */,
      18,    1,  515,    2, 0x06 /* Public */,
      19,    1,  518,    2, 0x06 /* Public */,
      20,    1,  521,    2, 0x06 /* Public */,
      21,    1,  524,    2, 0x06 /* Public */,
      22,    2,  527,    2, 0x06 /* Public */,
      23,    1,  532,    2, 0x06 /* Public */,
      24,    1,  535,    2, 0x06 /* Public */,
      25,    1,  538,    2, 0x06 /* Public */,
      26,    1,  541,    2, 0x06 /* Public */,
      27,    1,  544,    2, 0x06 /* Public */,
      28,    2,  547,    2, 0x06 /* Public */,
      29,    1,  552,    2, 0x06 /* Public */,
      30,    1,  555,    2, 0x06 /* Public */,
      31,    1,  558,    2, 0x06 /* Public */,
      32,    1,  561,    2, 0x06 /* Public */,
      33,    1,  564,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      34,    2,  567,    2, 0x0a /* Public */,
      35,    1,  572,    2, 0x0a /* Public */,
      36,    1,  575,    2, 0x0a /* Public */,
      37,    1,  578,    2, 0x0a /* Public */,
      38,    1,  581,    2, 0x0a /* Public */,
      39,    1,  584,    2, 0x0a /* Public */,
      40,    2,  587,    2, 0x0a /* Public */,
      41,    1,  592,    2, 0x0a /* Public */,
      42,    1,  595,    2, 0x0a /* Public */,
      43,    1,  598,    2, 0x0a /* Public */,
      44,    1,  601,    2, 0x0a /* Public */,
      45,    1,  604,    2, 0x0a /* Public */,
      46,    1,  607,    2, 0x0a /* Public */,
      47,    1,  610,    2, 0x0a /* Public */,
      48,    1,  613,    2, 0x0a /* Public */,
      49,    1,  616,    2, 0x0a /* Public */,
      50,    1,  619,    2, 0x0a /* Public */,
      51,    1,  622,    2, 0x0a /* Public */,
      52,    2,  625,    2, 0x0a /* Public */,
      53,    1,  630,    2, 0x0a /* Public */,
      54,    1,  633,    2, 0x0a /* Public */,
      55,    1,  636,    2, 0x0a /* Public */,
      56,    1,  639,    2, 0x0a /* Public */,
      57,    1,  642,    2, 0x0a /* Public */,
      58,    2,  645,    2, 0x0a /* Public */,
      59,    1,  650,    2, 0x0a /* Public */,
      60,    1,  653,    2, 0x0a /* Public */,
      61,    1,  656,    2, 0x0a /* Public */,
      62,    1,  659,    2, 0x0a /* Public */,
      63,    1,  662,    2, 0x0a /* Public */,
      64,    0,  665,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      65,    1,  666,    2, 0x02 /* Public */,
      66,    0,  669,    2, 0x02 /* Public */,
      67,    0,  670,    2, 0x02 /* Public */,
      68,    0,  671,    2, 0x02 /* Public */,
      69,    0,  672,    2, 0x02 /* Public */,
      70,    0,  673,    2, 0x02 /* Public */,
      71,    1,  674,    2, 0x02 /* Public */,
      72,    0,  677,    2, 0x02 /* Public */,
      73,    0,  678,    2, 0x02 /* Public */,
      74,    0,  679,    2, 0x02 /* Public */,
      75,    0,  680,    2, 0x02 /* Public */,
      76,    0,  681,    2, 0x02 /* Public */,
      77,    0,  682,    2, 0x02 /* Public */,
      78,    0,  683,    2, 0x02 /* Public */,
      79,    0,  684,    2, 0x02 /* Public */,
      80,    0,  685,    2, 0x02 /* Public */,
      81,    0,  686,    2, 0x02 /* Public */,
      82,    0,  687,    2, 0x02 /* Public */,
      83,    1,  688,    2, 0x02 /* Public */,
      84,    0,  691,    2, 0x02 /* Public */,
      85,    0,  692,    2, 0x02 /* Public */,
      86,    0,  693,    2, 0x02 /* Public */,
      87,    0,  694,    2, 0x02 /* Public */,
      88,    0,  695,    2, 0x02 /* Public */,
      89,    1,  696,    2, 0x02 /* Public */,
      90,    0,  699,    2, 0x02 /* Public */,
      91,    0,  700,    2, 0x02 /* Public */,
      92,    0,  701,    2, 0x02 /* Public */,
      93,    0,  702,    2, 0x02 /* Public */,
      94,    0,  703,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,    3,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,    3,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,    3,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,    3,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::UInt, QMetaType::UInt,    3,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt, QMetaType::UInt,    3,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    3,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    3,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      95, QMetaType::UInt, 0x00495003,
      96, QMetaType::UInt, 0x00495003,
      97, QMetaType::UInt, 0x00495003,
      98, QMetaType::UInt, 0x00495003,
      99, QMetaType::UInt, 0x00495003,
     100, QMetaType::UInt, 0x00495003,
     101, QMetaType::UInt, 0x00495003,
     102, QMetaType::UInt, 0x00495003,
     103, QMetaType::UInt, 0x00495003,
     104, QMetaType::UInt, 0x00495003,
     105, QMetaType::UChar, 0x00495003,
     106, QMetaType::UChar, 0x00495003,
     107, QMetaType::UChar, 0x00495003,
     108, QMetaType::UChar, 0x00495003,
     109, QMetaType::UChar, 0x00495003,
     110, QMetaType::UChar, 0x00495003,
     111, QMetaType::UChar, 0x00495003,
     112, QMetaType::UChar, 0x00495003,
     113, QMetaType::UChar, 0x00495003,
     114, QMetaType::UChar, 0x00495003,
     115, QMetaType::UChar, 0x00495003,
     116, QMetaType::UChar, 0x00495003,
     117, QMetaType::UChar, 0x00495003,
     118, QMetaType::UChar, 0x00495003,
     119, QMetaType::UChar, 0x00495003,
     120, QMetaType::UChar, 0x00495003,

 // properties: notify_signal_id
       1,
       2,
       3,
       4,
       5,
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

       0        // eod
};

void I2CStats::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<I2CStats *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->evirq_logChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        case 1: _t->evirq_log_0Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 2: _t->evirq_log_1Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 3: _t->evirq_log_2Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 4: _t->evirq_log_3Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 5: _t->evirq_log_4Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 6: _t->erirq_logChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        case 7: _t->erirq_log_0Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 8: _t->erirq_log_1Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 9: _t->erirq_log_2Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 10: _t->erirq_log_3Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 11: _t->erirq_log_4Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 12: _t->event_errorsChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 13: _t->fsm_errorsChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->irq_errorsChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 15: _t->nacksChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 16: _t->timeoutsChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->last_error_typeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 18: _t->event_logChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 19: _t->event_log_0Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->event_log_1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 21: _t->event_log_2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 22: _t->event_log_3Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 23: _t->event_log_4Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 24: _t->state_logChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 25: _t->state_log_0Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 26: _t->state_log_1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 27: _t->state_log_2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 28: _t->state_log_3Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 29: _t->state_log_4Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 30: _t->setevirq_log((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        case 31: _t->setevirq_log_0((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 32: _t->setevirq_log_1((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 33: _t->setevirq_log_2((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 34: _t->setevirq_log_3((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 35: _t->setevirq_log_4((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 36: _t->seterirq_log((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        case 37: _t->seterirq_log_0((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 38: _t->seterirq_log_1((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 39: _t->seterirq_log_2((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 40: _t->seterirq_log_3((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 41: _t->seterirq_log_4((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 42: _t->setevent_errors((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 43: _t->setfsm_errors((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 44: _t->setirq_errors((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 45: _t->setnacks((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 46: _t->settimeouts((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 47: _t->setlast_error_type((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 48: _t->setevent_log((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 49: _t->setevent_log_0((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 50: _t->setevent_log_1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 51: _t->setevent_log_2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 52: _t->setevent_log_3((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 53: _t->setevent_log_4((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 54: _t->setstate_log((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 55: _t->setstate_log_0((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 56: _t->setstate_log_1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 57: _t->setstate_log_2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 58: _t->setstate_log_3((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 59: _t->setstate_log_4((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 60: _t->emitNotifications(); break;
        case 61: { quint32 _r = _t->getevirq_log((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 62: { quint32 _r = _t->getevirq_log_0();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 63: { quint32 _r = _t->getevirq_log_1();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 64: { quint32 _r = _t->getevirq_log_2();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 65: { quint32 _r = _t->getevirq_log_3();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 66: { quint32 _r = _t->getevirq_log_4();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 67: { quint32 _r = _t->geterirq_log((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 68: { quint32 _r = _t->geterirq_log_0();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 69: { quint32 _r = _t->geterirq_log_1();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 70: { quint32 _r = _t->geterirq_log_2();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 71: { quint32 _r = _t->geterirq_log_3();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 72: { quint32 _r = _t->geterirq_log_4();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 73: { quint8 _r = _t->getevent_errors();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 74: { quint8 _r = _t->getfsm_errors();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 75: { quint8 _r = _t->getirq_errors();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 76: { quint8 _r = _t->getnacks();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 77: { quint8 _r = _t->gettimeouts();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 78: { quint8 _r = _t->getlast_error_type();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 79: { quint8 _r = _t->getevent_log((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 80: { quint8 _r = _t->getevent_log_0();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 81: { quint8 _r = _t->getevent_log_1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 82: { quint8 _r = _t->getevent_log_2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 83: { quint8 _r = _t->getevent_log_3();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 84: { quint8 _r = _t->getevent_log_4();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 85: { quint8 _r = _t->getstate_log((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 86: { quint8 _r = _t->getstate_log_0();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 87: { quint8 _r = _t->getstate_log_1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 88: { quint8 _r = _t->getstate_log_2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 89: { quint8 _r = _t->getstate_log_3();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 90: { quint8 _r = _t->getstate_log_4();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (I2CStats::*)(quint32 , quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::evirq_logChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::evirq_log_0Changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::evirq_log_1Changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::evirq_log_2Changed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::evirq_log_3Changed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::evirq_log_4Changed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint32 , quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::erirq_logChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::erirq_log_0Changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::erirq_log_1Changed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::erirq_log_2Changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::erirq_log_3Changed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::erirq_log_4Changed)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::event_errorsChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::fsm_errorsChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::irq_errorsChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::nacksChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::timeoutsChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::last_error_typeChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::event_logChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::event_log_0Changed)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::event_log_1Changed)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::event_log_2Changed)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::event_log_3Changed)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::event_log_4Changed)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::state_logChanged)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::state_log_0Changed)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::state_log_1Changed)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::state_log_2Changed)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::state_log_3Changed)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (I2CStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I2CStats::state_log_4Changed)) {
                *result = 29;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<I2CStats *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint32*>(_v) = _t->getevirq_log_0(); break;
        case 1: *reinterpret_cast< quint32*>(_v) = _t->getevirq_log_1(); break;
        case 2: *reinterpret_cast< quint32*>(_v) = _t->getevirq_log_2(); break;
        case 3: *reinterpret_cast< quint32*>(_v) = _t->getevirq_log_3(); break;
        case 4: *reinterpret_cast< quint32*>(_v) = _t->getevirq_log_4(); break;
        case 5: *reinterpret_cast< quint32*>(_v) = _t->geterirq_log_0(); break;
        case 6: *reinterpret_cast< quint32*>(_v) = _t->geterirq_log_1(); break;
        case 7: *reinterpret_cast< quint32*>(_v) = _t->geterirq_log_2(); break;
        case 8: *reinterpret_cast< quint32*>(_v) = _t->geterirq_log_3(); break;
        case 9: *reinterpret_cast< quint32*>(_v) = _t->geterirq_log_4(); break;
        case 10: *reinterpret_cast< quint8*>(_v) = _t->getevent_errors(); break;
        case 11: *reinterpret_cast< quint8*>(_v) = _t->getfsm_errors(); break;
        case 12: *reinterpret_cast< quint8*>(_v) = _t->getirq_errors(); break;
        case 13: *reinterpret_cast< quint8*>(_v) = _t->getnacks(); break;
        case 14: *reinterpret_cast< quint8*>(_v) = _t->gettimeouts(); break;
        case 15: *reinterpret_cast< quint8*>(_v) = _t->getlast_error_type(); break;
        case 16: *reinterpret_cast< quint8*>(_v) = _t->getevent_log_0(); break;
        case 17: *reinterpret_cast< quint8*>(_v) = _t->getevent_log_1(); break;
        case 18: *reinterpret_cast< quint8*>(_v) = _t->getevent_log_2(); break;
        case 19: *reinterpret_cast< quint8*>(_v) = _t->getevent_log_3(); break;
        case 20: *reinterpret_cast< quint8*>(_v) = _t->getevent_log_4(); break;
        case 21: *reinterpret_cast< quint8*>(_v) = _t->getstate_log_0(); break;
        case 22: *reinterpret_cast< quint8*>(_v) = _t->getstate_log_1(); break;
        case 23: *reinterpret_cast< quint8*>(_v) = _t->getstate_log_2(); break;
        case 24: *reinterpret_cast< quint8*>(_v) = _t->getstate_log_3(); break;
        case 25: *reinterpret_cast< quint8*>(_v) = _t->getstate_log_4(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<I2CStats *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setevirq_log_0(*reinterpret_cast< quint32*>(_v)); break;
        case 1: _t->setevirq_log_1(*reinterpret_cast< quint32*>(_v)); break;
        case 2: _t->setevirq_log_2(*reinterpret_cast< quint32*>(_v)); break;
        case 3: _t->setevirq_log_3(*reinterpret_cast< quint32*>(_v)); break;
        case 4: _t->setevirq_log_4(*reinterpret_cast< quint32*>(_v)); break;
        case 5: _t->seterirq_log_0(*reinterpret_cast< quint32*>(_v)); break;
        case 6: _t->seterirq_log_1(*reinterpret_cast< quint32*>(_v)); break;
        case 7: _t->seterirq_log_2(*reinterpret_cast< quint32*>(_v)); break;
        case 8: _t->seterirq_log_3(*reinterpret_cast< quint32*>(_v)); break;
        case 9: _t->seterirq_log_4(*reinterpret_cast< quint32*>(_v)); break;
        case 10: _t->setevent_errors(*reinterpret_cast< quint8*>(_v)); break;
        case 11: _t->setfsm_errors(*reinterpret_cast< quint8*>(_v)); break;
        case 12: _t->setirq_errors(*reinterpret_cast< quint8*>(_v)); break;
        case 13: _t->setnacks(*reinterpret_cast< quint8*>(_v)); break;
        case 14: _t->settimeouts(*reinterpret_cast< quint8*>(_v)); break;
        case 15: _t->setlast_error_type(*reinterpret_cast< quint8*>(_v)); break;
        case 16: _t->setevent_log_0(*reinterpret_cast< quint8*>(_v)); break;
        case 17: _t->setevent_log_1(*reinterpret_cast< quint8*>(_v)); break;
        case 18: _t->setevent_log_2(*reinterpret_cast< quint8*>(_v)); break;
        case 19: _t->setevent_log_3(*reinterpret_cast< quint8*>(_v)); break;
        case 20: _t->setevent_log_4(*reinterpret_cast< quint8*>(_v)); break;
        case 21: _t->setstate_log_0(*reinterpret_cast< quint8*>(_v)); break;
        case 22: _t->setstate_log_1(*reinterpret_cast< quint8*>(_v)); break;
        case 23: _t->setstate_log_2(*reinterpret_cast< quint8*>(_v)); break;
        case 24: _t->setstate_log_3(*reinterpret_cast< quint8*>(_v)); break;
        case 25: _t->setstate_log_4(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject I2CStats::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_I2CStats.data,
    qt_meta_data_I2CStats,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *I2CStats::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *I2CStats::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_I2CStats.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int I2CStats::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 26;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 26;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 26;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 26;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 26;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 26;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void I2CStats::evirq_logChanged(quint32 _t1, quint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void I2CStats::evirq_log_0Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void I2CStats::evirq_log_1Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void I2CStats::evirq_log_2Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void I2CStats::evirq_log_3Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void I2CStats::evirq_log_4Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void I2CStats::erirq_logChanged(quint32 _t1, quint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void I2CStats::erirq_log_0Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void I2CStats::erirq_log_1Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void I2CStats::erirq_log_2Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void I2CStats::erirq_log_3Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void I2CStats::erirq_log_4Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void I2CStats::event_errorsChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void I2CStats::fsm_errorsChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void I2CStats::irq_errorsChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void I2CStats::nacksChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void I2CStats::timeoutsChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void I2CStats::last_error_typeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void I2CStats::event_logChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void I2CStats::event_log_0Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void I2CStats::event_log_1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void I2CStats::event_log_2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void I2CStats::event_log_3Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void I2CStats::event_log_4Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void I2CStats::state_logChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void I2CStats::state_log_0Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void I2CStats::state_log_1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void I2CStats::state_log_2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void I2CStats::state_log_3Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void I2CStats::state_log_4Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
