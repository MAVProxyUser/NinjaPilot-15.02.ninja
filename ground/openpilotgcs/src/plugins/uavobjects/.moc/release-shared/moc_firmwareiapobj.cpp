/****************************************************************************
** Meta object code from reading C++ file 'firmwareiapobj.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/firmwareiapobj.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'firmwareiapobj.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FirmwareIAPObj_t {
    QByteArrayData data[80];
    char stringdata0[1163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FirmwareIAPObj_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FirmwareIAPObj_t qt_meta_stringdata_FirmwareIAPObj = {
    {
QT_MOC_LITERAL(0, 0, 14), // "FirmwareIAPObj"
QT_MOC_LITERAL(1, 15, 10), // "crcChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "value"
QT_MOC_LITERAL(4, 33, 14), // "CommandChanged"
QT_MOC_LITERAL(5, 48, 20), // "BoardRevisionChanged"
QT_MOC_LITERAL(6, 69, 16), // "CPUSerialChanged"
QT_MOC_LITERAL(7, 86, 5), // "index"
QT_MOC_LITERAL(8, 92, 18), // "CPUSerial_0Changed"
QT_MOC_LITERAL(9, 111, 18), // "CPUSerial_1Changed"
QT_MOC_LITERAL(10, 130, 18), // "CPUSerial_2Changed"
QT_MOC_LITERAL(11, 149, 18), // "CPUSerial_3Changed"
QT_MOC_LITERAL(12, 168, 18), // "CPUSerial_4Changed"
QT_MOC_LITERAL(13, 187, 18), // "CPUSerial_5Changed"
QT_MOC_LITERAL(14, 206, 18), // "CPUSerial_6Changed"
QT_MOC_LITERAL(15, 225, 18), // "CPUSerial_7Changed"
QT_MOC_LITERAL(16, 244, 18), // "CPUSerial_8Changed"
QT_MOC_LITERAL(17, 263, 18), // "CPUSerial_9Changed"
QT_MOC_LITERAL(18, 282, 19), // "CPUSerial_10Changed"
QT_MOC_LITERAL(19, 302, 19), // "CPUSerial_11Changed"
QT_MOC_LITERAL(20, 322, 16), // "BoardTypeChanged"
QT_MOC_LITERAL(21, 339, 25), // "BootloaderRevisionChanged"
QT_MOC_LITERAL(22, 365, 15), // "ArmResetChanged"
QT_MOC_LITERAL(23, 381, 6), // "setcrc"
QT_MOC_LITERAL(24, 388, 10), // "setCommand"
QT_MOC_LITERAL(25, 399, 16), // "setBoardRevision"
QT_MOC_LITERAL(26, 416, 12), // "setCPUSerial"
QT_MOC_LITERAL(27, 429, 14), // "setCPUSerial_0"
QT_MOC_LITERAL(28, 444, 14), // "setCPUSerial_1"
QT_MOC_LITERAL(29, 459, 14), // "setCPUSerial_2"
QT_MOC_LITERAL(30, 474, 14), // "setCPUSerial_3"
QT_MOC_LITERAL(31, 489, 14), // "setCPUSerial_4"
QT_MOC_LITERAL(32, 504, 14), // "setCPUSerial_5"
QT_MOC_LITERAL(33, 519, 14), // "setCPUSerial_6"
QT_MOC_LITERAL(34, 534, 14), // "setCPUSerial_7"
QT_MOC_LITERAL(35, 549, 14), // "setCPUSerial_8"
QT_MOC_LITERAL(36, 564, 14), // "setCPUSerial_9"
QT_MOC_LITERAL(37, 579, 15), // "setCPUSerial_10"
QT_MOC_LITERAL(38, 595, 15), // "setCPUSerial_11"
QT_MOC_LITERAL(39, 611, 12), // "setBoardType"
QT_MOC_LITERAL(40, 624, 21), // "setBootloaderRevision"
QT_MOC_LITERAL(41, 646, 11), // "setArmReset"
QT_MOC_LITERAL(42, 658, 17), // "emitNotifications"
QT_MOC_LITERAL(43, 676, 6), // "getcrc"
QT_MOC_LITERAL(44, 683, 10), // "getCommand"
QT_MOC_LITERAL(45, 694, 16), // "getBoardRevision"
QT_MOC_LITERAL(46, 711, 12), // "getCPUSerial"
QT_MOC_LITERAL(47, 724, 14), // "getCPUSerial_0"
QT_MOC_LITERAL(48, 739, 14), // "getCPUSerial_1"
QT_MOC_LITERAL(49, 754, 14), // "getCPUSerial_2"
QT_MOC_LITERAL(50, 769, 14), // "getCPUSerial_3"
QT_MOC_LITERAL(51, 784, 14), // "getCPUSerial_4"
QT_MOC_LITERAL(52, 799, 14), // "getCPUSerial_5"
QT_MOC_LITERAL(53, 814, 14), // "getCPUSerial_6"
QT_MOC_LITERAL(54, 829, 14), // "getCPUSerial_7"
QT_MOC_LITERAL(55, 844, 14), // "getCPUSerial_8"
QT_MOC_LITERAL(56, 859, 14), // "getCPUSerial_9"
QT_MOC_LITERAL(57, 874, 15), // "getCPUSerial_10"
QT_MOC_LITERAL(58, 890, 15), // "getCPUSerial_11"
QT_MOC_LITERAL(59, 906, 12), // "getBoardType"
QT_MOC_LITERAL(60, 919, 21), // "getBootloaderRevision"
QT_MOC_LITERAL(61, 941, 11), // "getArmReset"
QT_MOC_LITERAL(62, 953, 3), // "crc"
QT_MOC_LITERAL(63, 957, 7), // "Command"
QT_MOC_LITERAL(64, 965, 13), // "BoardRevision"
QT_MOC_LITERAL(65, 979, 11), // "CPUSerial_0"
QT_MOC_LITERAL(66, 991, 11), // "CPUSerial_1"
QT_MOC_LITERAL(67, 1003, 11), // "CPUSerial_2"
QT_MOC_LITERAL(68, 1015, 11), // "CPUSerial_3"
QT_MOC_LITERAL(69, 1027, 11), // "CPUSerial_4"
QT_MOC_LITERAL(70, 1039, 11), // "CPUSerial_5"
QT_MOC_LITERAL(71, 1051, 11), // "CPUSerial_6"
QT_MOC_LITERAL(72, 1063, 11), // "CPUSerial_7"
QT_MOC_LITERAL(73, 1075, 11), // "CPUSerial_8"
QT_MOC_LITERAL(74, 1087, 11), // "CPUSerial_9"
QT_MOC_LITERAL(75, 1099, 12), // "CPUSerial_10"
QT_MOC_LITERAL(76, 1112, 12), // "CPUSerial_11"
QT_MOC_LITERAL(77, 1125, 9), // "BoardType"
QT_MOC_LITERAL(78, 1135, 18), // "BootloaderRevision"
QT_MOC_LITERAL(79, 1154, 8) // "ArmReset"

    },
    "FirmwareIAPObj\0crcChanged\0\0value\0"
    "CommandChanged\0BoardRevisionChanged\0"
    "CPUSerialChanged\0index\0CPUSerial_0Changed\0"
    "CPUSerial_1Changed\0CPUSerial_2Changed\0"
    "CPUSerial_3Changed\0CPUSerial_4Changed\0"
    "CPUSerial_5Changed\0CPUSerial_6Changed\0"
    "CPUSerial_7Changed\0CPUSerial_8Changed\0"
    "CPUSerial_9Changed\0CPUSerial_10Changed\0"
    "CPUSerial_11Changed\0BoardTypeChanged\0"
    "BootloaderRevisionChanged\0ArmResetChanged\0"
    "setcrc\0setCommand\0setBoardRevision\0"
    "setCPUSerial\0setCPUSerial_0\0setCPUSerial_1\0"
    "setCPUSerial_2\0setCPUSerial_3\0"
    "setCPUSerial_4\0setCPUSerial_5\0"
    "setCPUSerial_6\0setCPUSerial_7\0"
    "setCPUSerial_8\0setCPUSerial_9\0"
    "setCPUSerial_10\0setCPUSerial_11\0"
    "setBoardType\0setBootloaderRevision\0"
    "setArmReset\0emitNotifications\0getcrc\0"
    "getCommand\0getBoardRevision\0getCPUSerial\0"
    "getCPUSerial_0\0getCPUSerial_1\0"
    "getCPUSerial_2\0getCPUSerial_3\0"
    "getCPUSerial_4\0getCPUSerial_5\0"
    "getCPUSerial_6\0getCPUSerial_7\0"
    "getCPUSerial_8\0getCPUSerial_9\0"
    "getCPUSerial_10\0getCPUSerial_11\0"
    "getBoardType\0getBootloaderRevision\0"
    "getArmReset\0crc\0Command\0BoardRevision\0"
    "CPUSerial_0\0CPUSerial_1\0CPUSerial_2\0"
    "CPUSerial_3\0CPUSerial_4\0CPUSerial_5\0"
    "CPUSerial_6\0CPUSerial_7\0CPUSerial_8\0"
    "CPUSerial_9\0CPUSerial_10\0CPUSerial_11\0"
    "BoardType\0BootloaderRevision\0ArmReset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FirmwareIAPObj[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      58,   14, // methods
      18,  444, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      19,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  304,    2, 0x06 /* Public */,
       4,    1,  307,    2, 0x06 /* Public */,
       5,    1,  310,    2, 0x06 /* Public */,
       6,    2,  313,    2, 0x06 /* Public */,
       8,    1,  318,    2, 0x06 /* Public */,
       9,    1,  321,    2, 0x06 /* Public */,
      10,    1,  324,    2, 0x06 /* Public */,
      11,    1,  327,    2, 0x06 /* Public */,
      12,    1,  330,    2, 0x06 /* Public */,
      13,    1,  333,    2, 0x06 /* Public */,
      14,    1,  336,    2, 0x06 /* Public */,
      15,    1,  339,    2, 0x06 /* Public */,
      16,    1,  342,    2, 0x06 /* Public */,
      17,    1,  345,    2, 0x06 /* Public */,
      18,    1,  348,    2, 0x06 /* Public */,
      19,    1,  351,    2, 0x06 /* Public */,
      20,    1,  354,    2, 0x06 /* Public */,
      21,    1,  357,    2, 0x06 /* Public */,
      22,    1,  360,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      23,    1,  363,    2, 0x0a /* Public */,
      24,    1,  366,    2, 0x0a /* Public */,
      25,    1,  369,    2, 0x0a /* Public */,
      26,    2,  372,    2, 0x0a /* Public */,
      27,    1,  377,    2, 0x0a /* Public */,
      28,    1,  380,    2, 0x0a /* Public */,
      29,    1,  383,    2, 0x0a /* Public */,
      30,    1,  386,    2, 0x0a /* Public */,
      31,    1,  389,    2, 0x0a /* Public */,
      32,    1,  392,    2, 0x0a /* Public */,
      33,    1,  395,    2, 0x0a /* Public */,
      34,    1,  398,    2, 0x0a /* Public */,
      35,    1,  401,    2, 0x0a /* Public */,
      36,    1,  404,    2, 0x0a /* Public */,
      37,    1,  407,    2, 0x0a /* Public */,
      38,    1,  410,    2, 0x0a /* Public */,
      39,    1,  413,    2, 0x0a /* Public */,
      40,    1,  416,    2, 0x0a /* Public */,
      41,    1,  419,    2, 0x0a /* Public */,
      42,    0,  422,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      43,    0,  423,    2, 0x02 /* Public */,
      44,    0,  424,    2, 0x02 /* Public */,
      45,    0,  425,    2, 0x02 /* Public */,
      46,    1,  426,    2, 0x02 /* Public */,
      47,    0,  429,    2, 0x02 /* Public */,
      48,    0,  430,    2, 0x02 /* Public */,
      49,    0,  431,    2, 0x02 /* Public */,
      50,    0,  432,    2, 0x02 /* Public */,
      51,    0,  433,    2, 0x02 /* Public */,
      52,    0,  434,    2, 0x02 /* Public */,
      53,    0,  435,    2, 0x02 /* Public */,
      54,    0,  436,    2, 0x02 /* Public */,
      55,    0,  437,    2, 0x02 /* Public */,
      56,    0,  438,    2, 0x02 /* Public */,
      57,    0,  439,    2, 0x02 /* Public */,
      58,    0,  440,    2, 0x02 /* Public */,
      59,    0,  441,    2, 0x02 /* Public */,
      60,    0,  442,    2, 0x02 /* Public */,
      61,    0,  443,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    7,    3,
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

 // slots: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    7,    3,
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
    QMetaType::Void,

 // methods: parameters
    QMetaType::UInt,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UChar, QMetaType::UInt,    7,
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

 // properties: name, type, flags
      62, QMetaType::UInt, 0x00495003,
      63, QMetaType::UShort, 0x00495103,
      64, QMetaType::UShort, 0x00495103,
      65, QMetaType::UChar, 0x00495103,
      66, QMetaType::UChar, 0x00495103,
      67, QMetaType::UChar, 0x00495103,
      68, QMetaType::UChar, 0x00495103,
      69, QMetaType::UChar, 0x00495103,
      70, QMetaType::UChar, 0x00495103,
      71, QMetaType::UChar, 0x00495103,
      72, QMetaType::UChar, 0x00495103,
      73, QMetaType::UChar, 0x00495103,
      74, QMetaType::UChar, 0x00495103,
      75, QMetaType::UChar, 0x00495103,
      76, QMetaType::UChar, 0x00495103,
      77, QMetaType::UChar, 0x00495103,
      78, QMetaType::UChar, 0x00495103,
      79, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
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

       0        // eod
};

void FirmwareIAPObj::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FirmwareIAPObj *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->crcChanged((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 1: _t->CommandChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 2: _t->BoardRevisionChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 3: _t->CPUSerialChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 4: _t->CPUSerial_0Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 5: _t->CPUSerial_1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 6: _t->CPUSerial_2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 7: _t->CPUSerial_3Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 8: _t->CPUSerial_4Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 9: _t->CPUSerial_5Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 10: _t->CPUSerial_6Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 11: _t->CPUSerial_7Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->CPUSerial_8Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 13: _t->CPUSerial_9Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->CPUSerial_10Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 15: _t->CPUSerial_11Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 16: _t->BoardTypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->BootloaderRevisionChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 18: _t->ArmResetChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 19: _t->setcrc((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 20: _t->setCommand((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 21: _t->setBoardRevision((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 22: _t->setCPUSerial((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 23: _t->setCPUSerial_0((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 24: _t->setCPUSerial_1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 25: _t->setCPUSerial_2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 26: _t->setCPUSerial_3((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 27: _t->setCPUSerial_4((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 28: _t->setCPUSerial_5((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 29: _t->setCPUSerial_6((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 30: _t->setCPUSerial_7((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 31: _t->setCPUSerial_8((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 32: _t->setCPUSerial_9((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 33: _t->setCPUSerial_10((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 34: _t->setCPUSerial_11((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 35: _t->setBoardType((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 36: _t->setBootloaderRevision((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 37: _t->setArmReset((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 38: _t->emitNotifications(); break;
        case 39: { quint32 _r = _t->getcrc();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 40: { quint16 _r = _t->getCommand();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 41: { quint16 _r = _t->getBoardRevision();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 42: { quint8 _r = _t->getCPUSerial((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 43: { quint8 _r = _t->getCPUSerial_0();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 44: { quint8 _r = _t->getCPUSerial_1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 45: { quint8 _r = _t->getCPUSerial_2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 46: { quint8 _r = _t->getCPUSerial_3();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 47: { quint8 _r = _t->getCPUSerial_4();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 48: { quint8 _r = _t->getCPUSerial_5();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 49: { quint8 _r = _t->getCPUSerial_6();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 50: { quint8 _r = _t->getCPUSerial_7();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 51: { quint8 _r = _t->getCPUSerial_8();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 52: { quint8 _r = _t->getCPUSerial_9();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 53: { quint8 _r = _t->getCPUSerial_10();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 54: { quint8 _r = _t->getCPUSerial_11();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 55: { quint8 _r = _t->getBoardType();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 56: { quint8 _r = _t->getBootloaderRevision();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 57: { quint8 _r = _t->getArmReset();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FirmwareIAPObj::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::crcChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CommandChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::BoardRevisionChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CPUSerialChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CPUSerial_0Changed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CPUSerial_1Changed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CPUSerial_2Changed)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CPUSerial_3Changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CPUSerial_4Changed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CPUSerial_5Changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CPUSerial_6Changed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CPUSerial_7Changed)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CPUSerial_8Changed)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CPUSerial_9Changed)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CPUSerial_10Changed)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::CPUSerial_11Changed)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::BoardTypeChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::BootloaderRevisionChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (FirmwareIAPObj::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirmwareIAPObj::ArmResetChanged)) {
                *result = 18;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FirmwareIAPObj *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint32*>(_v) = _t->getcrc(); break;
        case 1: *reinterpret_cast< quint16*>(_v) = _t->getCommand(); break;
        case 2: *reinterpret_cast< quint16*>(_v) = _t->getBoardRevision(); break;
        case 3: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_0(); break;
        case 4: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_1(); break;
        case 5: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_2(); break;
        case 6: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_3(); break;
        case 7: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_4(); break;
        case 8: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_5(); break;
        case 9: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_6(); break;
        case 10: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_7(); break;
        case 11: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_8(); break;
        case 12: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_9(); break;
        case 13: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_10(); break;
        case 14: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_11(); break;
        case 15: *reinterpret_cast< quint8*>(_v) = _t->getBoardType(); break;
        case 16: *reinterpret_cast< quint8*>(_v) = _t->getBootloaderRevision(); break;
        case 17: *reinterpret_cast< quint8*>(_v) = _t->getArmReset(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<FirmwareIAPObj *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setcrc(*reinterpret_cast< quint32*>(_v)); break;
        case 1: _t->setCommand(*reinterpret_cast< quint16*>(_v)); break;
        case 2: _t->setBoardRevision(*reinterpret_cast< quint16*>(_v)); break;
        case 3: _t->setCPUSerial_0(*reinterpret_cast< quint8*>(_v)); break;
        case 4: _t->setCPUSerial_1(*reinterpret_cast< quint8*>(_v)); break;
        case 5: _t->setCPUSerial_2(*reinterpret_cast< quint8*>(_v)); break;
        case 6: _t->setCPUSerial_3(*reinterpret_cast< quint8*>(_v)); break;
        case 7: _t->setCPUSerial_4(*reinterpret_cast< quint8*>(_v)); break;
        case 8: _t->setCPUSerial_5(*reinterpret_cast< quint8*>(_v)); break;
        case 9: _t->setCPUSerial_6(*reinterpret_cast< quint8*>(_v)); break;
        case 10: _t->setCPUSerial_7(*reinterpret_cast< quint8*>(_v)); break;
        case 11: _t->setCPUSerial_8(*reinterpret_cast< quint8*>(_v)); break;
        case 12: _t->setCPUSerial_9(*reinterpret_cast< quint8*>(_v)); break;
        case 13: _t->setCPUSerial_10(*reinterpret_cast< quint8*>(_v)); break;
        case 14: _t->setCPUSerial_11(*reinterpret_cast< quint8*>(_v)); break;
        case 15: _t->setBoardType(*reinterpret_cast< quint8*>(_v)); break;
        case 16: _t->setBootloaderRevision(*reinterpret_cast< quint8*>(_v)); break;
        case 17: _t->setArmReset(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject FirmwareIAPObj::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_FirmwareIAPObj.data,
    qt_meta_data_FirmwareIAPObj,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FirmwareIAPObj::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FirmwareIAPObj::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FirmwareIAPObj.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int FirmwareIAPObj::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 58)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 58;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 58)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 58;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 18;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 18;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 18;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 18;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 18;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FirmwareIAPObj::crcChanged(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FirmwareIAPObj::CommandChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FirmwareIAPObj::BoardRevisionChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FirmwareIAPObj::CPUSerialChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FirmwareIAPObj::CPUSerial_0Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FirmwareIAPObj::CPUSerial_1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void FirmwareIAPObj::CPUSerial_2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void FirmwareIAPObj::CPUSerial_3Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void FirmwareIAPObj::CPUSerial_4Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void FirmwareIAPObj::CPUSerial_5Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void FirmwareIAPObj::CPUSerial_6Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void FirmwareIAPObj::CPUSerial_7Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void FirmwareIAPObj::CPUSerial_8Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void FirmwareIAPObj::CPUSerial_9Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void FirmwareIAPObj::CPUSerial_10Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void FirmwareIAPObj::CPUSerial_11Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void FirmwareIAPObj::BoardTypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void FirmwareIAPObj::BootloaderRevisionChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void FirmwareIAPObj::ArmResetChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
