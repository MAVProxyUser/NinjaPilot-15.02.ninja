/****************************************************************************
** Meta object code from reading C++ file 'actuatorcommand.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/actuatorcommand.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'actuatorcommand.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ActuatorCommand_t {
    QByteArrayData data[68];
    char stringdata0[935];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ActuatorCommand_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ActuatorCommand_t qt_meta_stringdata_ActuatorCommand = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ActuatorCommand"
QT_MOC_LITERAL(1, 16, 14), // "ChannelChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "index"
QT_MOC_LITERAL(4, 38, 5), // "value"
QT_MOC_LITERAL(5, 44, 16), // "Channel_0Changed"
QT_MOC_LITERAL(6, 61, 16), // "Channel_1Changed"
QT_MOC_LITERAL(7, 78, 16), // "Channel_2Changed"
QT_MOC_LITERAL(8, 95, 16), // "Channel_3Changed"
QT_MOC_LITERAL(9, 112, 16), // "Channel_4Changed"
QT_MOC_LITERAL(10, 129, 16), // "Channel_5Changed"
QT_MOC_LITERAL(11, 146, 16), // "Channel_6Changed"
QT_MOC_LITERAL(12, 163, 16), // "Channel_7Changed"
QT_MOC_LITERAL(13, 180, 16), // "Channel_8Changed"
QT_MOC_LITERAL(14, 197, 16), // "Channel_9Changed"
QT_MOC_LITERAL(15, 214, 17), // "Channel_10Changed"
QT_MOC_LITERAL(16, 232, 17), // "Channel_11Changed"
QT_MOC_LITERAL(17, 250, 17), // "UpdateTimeChanged"
QT_MOC_LITERAL(18, 268, 20), // "MaxUpdateTimeChanged"
QT_MOC_LITERAL(19, 289, 23), // "NumFailedUpdatesChanged"
QT_MOC_LITERAL(20, 313, 10), // "setChannel"
QT_MOC_LITERAL(21, 324, 12), // "setChannel_0"
QT_MOC_LITERAL(22, 337, 12), // "setChannel_1"
QT_MOC_LITERAL(23, 350, 12), // "setChannel_2"
QT_MOC_LITERAL(24, 363, 12), // "setChannel_3"
QT_MOC_LITERAL(25, 376, 12), // "setChannel_4"
QT_MOC_LITERAL(26, 389, 12), // "setChannel_5"
QT_MOC_LITERAL(27, 402, 12), // "setChannel_6"
QT_MOC_LITERAL(28, 415, 12), // "setChannel_7"
QT_MOC_LITERAL(29, 428, 12), // "setChannel_8"
QT_MOC_LITERAL(30, 441, 12), // "setChannel_9"
QT_MOC_LITERAL(31, 454, 13), // "setChannel_10"
QT_MOC_LITERAL(32, 468, 13), // "setChannel_11"
QT_MOC_LITERAL(33, 482, 13), // "setUpdateTime"
QT_MOC_LITERAL(34, 496, 16), // "setMaxUpdateTime"
QT_MOC_LITERAL(35, 513, 19), // "setNumFailedUpdates"
QT_MOC_LITERAL(36, 533, 17), // "emitNotifications"
QT_MOC_LITERAL(37, 551, 10), // "getChannel"
QT_MOC_LITERAL(38, 562, 12), // "getChannel_0"
QT_MOC_LITERAL(39, 575, 12), // "getChannel_1"
QT_MOC_LITERAL(40, 588, 12), // "getChannel_2"
QT_MOC_LITERAL(41, 601, 12), // "getChannel_3"
QT_MOC_LITERAL(42, 614, 12), // "getChannel_4"
QT_MOC_LITERAL(43, 627, 12), // "getChannel_5"
QT_MOC_LITERAL(44, 640, 12), // "getChannel_6"
QT_MOC_LITERAL(45, 653, 12), // "getChannel_7"
QT_MOC_LITERAL(46, 666, 12), // "getChannel_8"
QT_MOC_LITERAL(47, 679, 12), // "getChannel_9"
QT_MOC_LITERAL(48, 692, 13), // "getChannel_10"
QT_MOC_LITERAL(49, 706, 13), // "getChannel_11"
QT_MOC_LITERAL(50, 720, 13), // "getUpdateTime"
QT_MOC_LITERAL(51, 734, 16), // "getMaxUpdateTime"
QT_MOC_LITERAL(52, 751, 19), // "getNumFailedUpdates"
QT_MOC_LITERAL(53, 771, 9), // "Channel_0"
QT_MOC_LITERAL(54, 781, 9), // "Channel_1"
QT_MOC_LITERAL(55, 791, 9), // "Channel_2"
QT_MOC_LITERAL(56, 801, 9), // "Channel_3"
QT_MOC_LITERAL(57, 811, 9), // "Channel_4"
QT_MOC_LITERAL(58, 821, 9), // "Channel_5"
QT_MOC_LITERAL(59, 831, 9), // "Channel_6"
QT_MOC_LITERAL(60, 841, 9), // "Channel_7"
QT_MOC_LITERAL(61, 851, 9), // "Channel_8"
QT_MOC_LITERAL(62, 861, 9), // "Channel_9"
QT_MOC_LITERAL(63, 871, 10), // "Channel_10"
QT_MOC_LITERAL(64, 882, 10), // "Channel_11"
QT_MOC_LITERAL(65, 893, 10), // "UpdateTime"
QT_MOC_LITERAL(66, 904, 13), // "MaxUpdateTime"
QT_MOC_LITERAL(67, 918, 16) // "NumFailedUpdates"

    },
    "ActuatorCommand\0ChannelChanged\0\0index\0"
    "value\0Channel_0Changed\0Channel_1Changed\0"
    "Channel_2Changed\0Channel_3Changed\0"
    "Channel_4Changed\0Channel_5Changed\0"
    "Channel_6Changed\0Channel_7Changed\0"
    "Channel_8Changed\0Channel_9Changed\0"
    "Channel_10Changed\0Channel_11Changed\0"
    "UpdateTimeChanged\0MaxUpdateTimeChanged\0"
    "NumFailedUpdatesChanged\0setChannel\0"
    "setChannel_0\0setChannel_1\0setChannel_2\0"
    "setChannel_3\0setChannel_4\0setChannel_5\0"
    "setChannel_6\0setChannel_7\0setChannel_8\0"
    "setChannel_9\0setChannel_10\0setChannel_11\0"
    "setUpdateTime\0setMaxUpdateTime\0"
    "setNumFailedUpdates\0emitNotifications\0"
    "getChannel\0getChannel_0\0getChannel_1\0"
    "getChannel_2\0getChannel_3\0getChannel_4\0"
    "getChannel_5\0getChannel_6\0getChannel_7\0"
    "getChannel_8\0getChannel_9\0getChannel_10\0"
    "getChannel_11\0getUpdateTime\0"
    "getMaxUpdateTime\0getNumFailedUpdates\0"
    "Channel_0\0Channel_1\0Channel_2\0Channel_3\0"
    "Channel_4\0Channel_5\0Channel_6\0Channel_7\0"
    "Channel_8\0Channel_9\0Channel_10\0"
    "Channel_11\0UpdateTime\0MaxUpdateTime\0"
    "NumFailedUpdates"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ActuatorCommand[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      49,   14, // methods
      15,  378, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  259,    2, 0x06 /* Public */,
       5,    1,  264,    2, 0x06 /* Public */,
       6,    1,  267,    2, 0x06 /* Public */,
       7,    1,  270,    2, 0x06 /* Public */,
       8,    1,  273,    2, 0x06 /* Public */,
       9,    1,  276,    2, 0x06 /* Public */,
      10,    1,  279,    2, 0x06 /* Public */,
      11,    1,  282,    2, 0x06 /* Public */,
      12,    1,  285,    2, 0x06 /* Public */,
      13,    1,  288,    2, 0x06 /* Public */,
      14,    1,  291,    2, 0x06 /* Public */,
      15,    1,  294,    2, 0x06 /* Public */,
      16,    1,  297,    2, 0x06 /* Public */,
      17,    1,  300,    2, 0x06 /* Public */,
      18,    1,  303,    2, 0x06 /* Public */,
      19,    1,  306,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    2,  309,    2, 0x0a /* Public */,
      21,    1,  314,    2, 0x0a /* Public */,
      22,    1,  317,    2, 0x0a /* Public */,
      23,    1,  320,    2, 0x0a /* Public */,
      24,    1,  323,    2, 0x0a /* Public */,
      25,    1,  326,    2, 0x0a /* Public */,
      26,    1,  329,    2, 0x0a /* Public */,
      27,    1,  332,    2, 0x0a /* Public */,
      28,    1,  335,    2, 0x0a /* Public */,
      29,    1,  338,    2, 0x0a /* Public */,
      30,    1,  341,    2, 0x0a /* Public */,
      31,    1,  344,    2, 0x0a /* Public */,
      32,    1,  347,    2, 0x0a /* Public */,
      33,    1,  350,    2, 0x0a /* Public */,
      34,    1,  353,    2, 0x0a /* Public */,
      35,    1,  356,    2, 0x0a /* Public */,
      36,    0,  359,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      37,    1,  360,    2, 0x02 /* Public */,
      38,    0,  363,    2, 0x02 /* Public */,
      39,    0,  364,    2, 0x02 /* Public */,
      40,    0,  365,    2, 0x02 /* Public */,
      41,    0,  366,    2, 0x02 /* Public */,
      42,    0,  367,    2, 0x02 /* Public */,
      43,    0,  368,    2, 0x02 /* Public */,
      44,    0,  369,    2, 0x02 /* Public */,
      45,    0,  370,    2, 0x02 /* Public */,
      46,    0,  371,    2, 0x02 /* Public */,
      47,    0,  372,    2, 0x02 /* Public */,
      48,    0,  373,    2, 0x02 /* Public */,
      49,    0,  374,    2, 0x02 /* Public */,
      50,    0,  375,    2, 0x02 /* Public */,
      51,    0,  376,    2, 0x02 /* Public */,
      52,    0,  377,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UShort,    4,
    QMetaType::Void, QMetaType::UShort,    4,
    QMetaType::Void, QMetaType::UChar,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    3,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UShort,    4,
    QMetaType::Void, QMetaType::UShort,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Short, QMetaType::UInt,    3,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UChar,

 // properties: name, type, flags
      53, QMetaType::Short, 0x00495103,
      54, QMetaType::Short, 0x00495103,
      55, QMetaType::Short, 0x00495103,
      56, QMetaType::Short, 0x00495103,
      57, QMetaType::Short, 0x00495103,
      58, QMetaType::Short, 0x00495103,
      59, QMetaType::Short, 0x00495103,
      60, QMetaType::Short, 0x00495103,
      61, QMetaType::Short, 0x00495103,
      62, QMetaType::Short, 0x00495103,
      63, QMetaType::Short, 0x00495103,
      64, QMetaType::Short, 0x00495103,
      65, QMetaType::UShort, 0x00495103,
      66, QMetaType::UShort, 0x00495103,
      67, QMetaType::UChar, 0x00495103,

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

       0        // eod
};

void ActuatorCommand::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ActuatorCommand *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ChannelChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 1: _t->Channel_0Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 2: _t->Channel_1Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 3: _t->Channel_2Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 4: _t->Channel_3Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 5: _t->Channel_4Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 6: _t->Channel_5Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 7: _t->Channel_6Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 8: _t->Channel_7Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 9: _t->Channel_8Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 10: _t->Channel_9Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 11: _t->Channel_10Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 12: _t->Channel_11Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 13: _t->UpdateTimeChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 14: _t->MaxUpdateTimeChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 15: _t->NumFailedUpdatesChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 16: _t->setChannel((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 17: _t->setChannel_0((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 18: _t->setChannel_1((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 19: _t->setChannel_2((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 20: _t->setChannel_3((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 21: _t->setChannel_4((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 22: _t->setChannel_5((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 23: _t->setChannel_6((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 24: _t->setChannel_7((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 25: _t->setChannel_8((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 26: _t->setChannel_9((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 27: _t->setChannel_10((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 28: _t->setChannel_11((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 29: _t->setUpdateTime((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 30: _t->setMaxUpdateTime((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 31: _t->setNumFailedUpdates((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 32: _t->emitNotifications(); break;
        case 33: { qint16 _r = _t->getChannel((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 34: { qint16 _r = _t->getChannel_0();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 35: { qint16 _r = _t->getChannel_1();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 36: { qint16 _r = _t->getChannel_2();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 37: { qint16 _r = _t->getChannel_3();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 38: { qint16 _r = _t->getChannel_4();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 39: { qint16 _r = _t->getChannel_5();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 40: { qint16 _r = _t->getChannel_6();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 41: { qint16 _r = _t->getChannel_7();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 42: { qint16 _r = _t->getChannel_8();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 43: { qint16 _r = _t->getChannel_9();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 44: { qint16 _r = _t->getChannel_10();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 45: { qint16 _r = _t->getChannel_11();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 46: { quint16 _r = _t->getUpdateTime();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 47: { quint16 _r = _t->getMaxUpdateTime();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 48: { quint8 _r = _t->getNumFailedUpdates();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ActuatorCommand::*)(quint32 , qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::ChannelChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::Channel_0Changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::Channel_1Changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::Channel_2Changed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::Channel_3Changed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::Channel_4Changed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::Channel_5Changed)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::Channel_6Changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::Channel_7Changed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::Channel_8Changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::Channel_9Changed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::Channel_10Changed)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::Channel_11Changed)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::UpdateTimeChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::MaxUpdateTimeChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (ActuatorCommand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorCommand::NumFailedUpdatesChanged)) {
                *result = 15;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ActuatorCommand *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qint16*>(_v) = _t->getChannel_0(); break;
        case 1: *reinterpret_cast< qint16*>(_v) = _t->getChannel_1(); break;
        case 2: *reinterpret_cast< qint16*>(_v) = _t->getChannel_2(); break;
        case 3: *reinterpret_cast< qint16*>(_v) = _t->getChannel_3(); break;
        case 4: *reinterpret_cast< qint16*>(_v) = _t->getChannel_4(); break;
        case 5: *reinterpret_cast< qint16*>(_v) = _t->getChannel_5(); break;
        case 6: *reinterpret_cast< qint16*>(_v) = _t->getChannel_6(); break;
        case 7: *reinterpret_cast< qint16*>(_v) = _t->getChannel_7(); break;
        case 8: *reinterpret_cast< qint16*>(_v) = _t->getChannel_8(); break;
        case 9: *reinterpret_cast< qint16*>(_v) = _t->getChannel_9(); break;
        case 10: *reinterpret_cast< qint16*>(_v) = _t->getChannel_10(); break;
        case 11: *reinterpret_cast< qint16*>(_v) = _t->getChannel_11(); break;
        case 12: *reinterpret_cast< quint16*>(_v) = _t->getUpdateTime(); break;
        case 13: *reinterpret_cast< quint16*>(_v) = _t->getMaxUpdateTime(); break;
        case 14: *reinterpret_cast< quint8*>(_v) = _t->getNumFailedUpdates(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ActuatorCommand *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setChannel_0(*reinterpret_cast< qint16*>(_v)); break;
        case 1: _t->setChannel_1(*reinterpret_cast< qint16*>(_v)); break;
        case 2: _t->setChannel_2(*reinterpret_cast< qint16*>(_v)); break;
        case 3: _t->setChannel_3(*reinterpret_cast< qint16*>(_v)); break;
        case 4: _t->setChannel_4(*reinterpret_cast< qint16*>(_v)); break;
        case 5: _t->setChannel_5(*reinterpret_cast< qint16*>(_v)); break;
        case 6: _t->setChannel_6(*reinterpret_cast< qint16*>(_v)); break;
        case 7: _t->setChannel_7(*reinterpret_cast< qint16*>(_v)); break;
        case 8: _t->setChannel_8(*reinterpret_cast< qint16*>(_v)); break;
        case 9: _t->setChannel_9(*reinterpret_cast< qint16*>(_v)); break;
        case 10: _t->setChannel_10(*reinterpret_cast< qint16*>(_v)); break;
        case 11: _t->setChannel_11(*reinterpret_cast< qint16*>(_v)); break;
        case 12: _t->setUpdateTime(*reinterpret_cast< quint16*>(_v)); break;
        case 13: _t->setMaxUpdateTime(*reinterpret_cast< quint16*>(_v)); break;
        case 14: _t->setNumFailedUpdates(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ActuatorCommand::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_ActuatorCommand.data,
    qt_meta_data_ActuatorCommand,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ActuatorCommand::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ActuatorCommand::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ActuatorCommand.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int ActuatorCommand::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 49)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 49;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 49)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 49;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 15;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 15;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 15;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 15;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 15;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ActuatorCommand::ChannelChanged(quint32 _t1, qint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ActuatorCommand::Channel_0Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ActuatorCommand::Channel_1Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ActuatorCommand::Channel_2Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ActuatorCommand::Channel_3Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ActuatorCommand::Channel_4Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ActuatorCommand::Channel_5Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ActuatorCommand::Channel_6Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ActuatorCommand::Channel_7Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ActuatorCommand::Channel_8Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ActuatorCommand::Channel_9Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ActuatorCommand::Channel_10Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ActuatorCommand::Channel_11Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ActuatorCommand::UpdateTimeChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ActuatorCommand::MaxUpdateTimeChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void ActuatorCommand::NumFailedUpdatesChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
