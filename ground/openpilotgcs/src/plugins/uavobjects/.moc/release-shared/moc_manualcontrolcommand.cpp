/****************************************************************************
** Meta object code from reading C++ file 'manualcontrolcommand.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/manualcontrolcommand.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'manualcontrolcommand.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ManualControlCommand_t {
    QByteArrayData data[76];
    char stringdata0[978];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ManualControlCommand_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ManualControlCommand_t qt_meta_stringdata_ManualControlCommand = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ManualControlCommand"
QT_MOC_LITERAL(1, 21, 15), // "ThrottleChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 5), // "value"
QT_MOC_LITERAL(4, 44, 11), // "RollChanged"
QT_MOC_LITERAL(5, 56, 12), // "PitchChanged"
QT_MOC_LITERAL(6, 69, 10), // "YawChanged"
QT_MOC_LITERAL(7, 80, 17), // "CollectiveChanged"
QT_MOC_LITERAL(8, 98, 13), // "ThrustChanged"
QT_MOC_LITERAL(9, 112, 14), // "ChannelChanged"
QT_MOC_LITERAL(10, 127, 5), // "index"
QT_MOC_LITERAL(11, 133, 16), // "Channel_0Changed"
QT_MOC_LITERAL(12, 150, 16), // "Channel_1Changed"
QT_MOC_LITERAL(13, 167, 16), // "Channel_2Changed"
QT_MOC_LITERAL(14, 184, 16), // "Channel_3Changed"
QT_MOC_LITERAL(15, 201, 16), // "Channel_4Changed"
QT_MOC_LITERAL(16, 218, 16), // "Channel_5Changed"
QT_MOC_LITERAL(17, 235, 16), // "Channel_6Changed"
QT_MOC_LITERAL(18, 252, 16), // "Channel_7Changed"
QT_MOC_LITERAL(19, 269, 16), // "Channel_8Changed"
QT_MOC_LITERAL(20, 286, 16), // "ConnectedChanged"
QT_MOC_LITERAL(21, 303, 31), // "FlightModeSwitchPositionChanged"
QT_MOC_LITERAL(22, 335, 11), // "setThrottle"
QT_MOC_LITERAL(23, 347, 7), // "setRoll"
QT_MOC_LITERAL(24, 355, 8), // "setPitch"
QT_MOC_LITERAL(25, 364, 6), // "setYaw"
QT_MOC_LITERAL(26, 371, 13), // "setCollective"
QT_MOC_LITERAL(27, 385, 9), // "setThrust"
QT_MOC_LITERAL(28, 395, 10), // "setChannel"
QT_MOC_LITERAL(29, 406, 12), // "setChannel_0"
QT_MOC_LITERAL(30, 419, 12), // "setChannel_1"
QT_MOC_LITERAL(31, 432, 12), // "setChannel_2"
QT_MOC_LITERAL(32, 445, 12), // "setChannel_3"
QT_MOC_LITERAL(33, 458, 12), // "setChannel_4"
QT_MOC_LITERAL(34, 471, 12), // "setChannel_5"
QT_MOC_LITERAL(35, 484, 12), // "setChannel_6"
QT_MOC_LITERAL(36, 497, 12), // "setChannel_7"
QT_MOC_LITERAL(37, 510, 12), // "setChannel_8"
QT_MOC_LITERAL(38, 523, 12), // "setConnected"
QT_MOC_LITERAL(39, 536, 27), // "setFlightModeSwitchPosition"
QT_MOC_LITERAL(40, 564, 17), // "emitNotifications"
QT_MOC_LITERAL(41, 582, 11), // "getThrottle"
QT_MOC_LITERAL(42, 594, 7), // "getRoll"
QT_MOC_LITERAL(43, 602, 8), // "getPitch"
QT_MOC_LITERAL(44, 611, 6), // "getYaw"
QT_MOC_LITERAL(45, 618, 13), // "getCollective"
QT_MOC_LITERAL(46, 632, 9), // "getThrust"
QT_MOC_LITERAL(47, 642, 10), // "getChannel"
QT_MOC_LITERAL(48, 653, 12), // "getChannel_0"
QT_MOC_LITERAL(49, 666, 12), // "getChannel_1"
QT_MOC_LITERAL(50, 679, 12), // "getChannel_2"
QT_MOC_LITERAL(51, 692, 12), // "getChannel_3"
QT_MOC_LITERAL(52, 705, 12), // "getChannel_4"
QT_MOC_LITERAL(53, 718, 12), // "getChannel_5"
QT_MOC_LITERAL(54, 731, 12), // "getChannel_6"
QT_MOC_LITERAL(55, 744, 12), // "getChannel_7"
QT_MOC_LITERAL(56, 757, 12), // "getChannel_8"
QT_MOC_LITERAL(57, 770, 12), // "getConnected"
QT_MOC_LITERAL(58, 783, 27), // "getFlightModeSwitchPosition"
QT_MOC_LITERAL(59, 811, 8), // "Throttle"
QT_MOC_LITERAL(60, 820, 4), // "Roll"
QT_MOC_LITERAL(61, 825, 5), // "Pitch"
QT_MOC_LITERAL(62, 831, 3), // "Yaw"
QT_MOC_LITERAL(63, 835, 10), // "Collective"
QT_MOC_LITERAL(64, 846, 6), // "Thrust"
QT_MOC_LITERAL(65, 853, 9), // "Channel_0"
QT_MOC_LITERAL(66, 863, 9), // "Channel_1"
QT_MOC_LITERAL(67, 873, 9), // "Channel_2"
QT_MOC_LITERAL(68, 883, 9), // "Channel_3"
QT_MOC_LITERAL(69, 893, 9), // "Channel_4"
QT_MOC_LITERAL(70, 903, 9), // "Channel_5"
QT_MOC_LITERAL(71, 913, 9), // "Channel_6"
QT_MOC_LITERAL(72, 923, 9), // "Channel_7"
QT_MOC_LITERAL(73, 933, 9), // "Channel_8"
QT_MOC_LITERAL(74, 943, 9), // "Connected"
QT_MOC_LITERAL(75, 953, 24) // "FlightModeSwitchPosition"

    },
    "ManualControlCommand\0ThrottleChanged\0"
    "\0value\0RollChanged\0PitchChanged\0"
    "YawChanged\0CollectiveChanged\0ThrustChanged\0"
    "ChannelChanged\0index\0Channel_0Changed\0"
    "Channel_1Changed\0Channel_2Changed\0"
    "Channel_3Changed\0Channel_4Changed\0"
    "Channel_5Changed\0Channel_6Changed\0"
    "Channel_7Changed\0Channel_8Changed\0"
    "ConnectedChanged\0FlightModeSwitchPositionChanged\0"
    "setThrottle\0setRoll\0setPitch\0setYaw\0"
    "setCollective\0setThrust\0setChannel\0"
    "setChannel_0\0setChannel_1\0setChannel_2\0"
    "setChannel_3\0setChannel_4\0setChannel_5\0"
    "setChannel_6\0setChannel_7\0setChannel_8\0"
    "setConnected\0setFlightModeSwitchPosition\0"
    "emitNotifications\0getThrottle\0getRoll\0"
    "getPitch\0getYaw\0getCollective\0getThrust\0"
    "getChannel\0getChannel_0\0getChannel_1\0"
    "getChannel_2\0getChannel_3\0getChannel_4\0"
    "getChannel_5\0getChannel_6\0getChannel_7\0"
    "getChannel_8\0getConnected\0"
    "getFlightModeSwitchPosition\0Throttle\0"
    "Roll\0Pitch\0Yaw\0Collective\0Thrust\0"
    "Channel_0\0Channel_1\0Channel_2\0Channel_3\0"
    "Channel_4\0Channel_5\0Channel_6\0Channel_7\0"
    "Channel_8\0Connected\0FlightModeSwitchPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ManualControlCommand[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      55,   14, // methods
      17,  422, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  289,    2, 0x06 /* Public */,
       4,    1,  292,    2, 0x06 /* Public */,
       5,    1,  295,    2, 0x06 /* Public */,
       6,    1,  298,    2, 0x06 /* Public */,
       7,    1,  301,    2, 0x06 /* Public */,
       8,    1,  304,    2, 0x06 /* Public */,
       9,    2,  307,    2, 0x06 /* Public */,
      11,    1,  312,    2, 0x06 /* Public */,
      12,    1,  315,    2, 0x06 /* Public */,
      13,    1,  318,    2, 0x06 /* Public */,
      14,    1,  321,    2, 0x06 /* Public */,
      15,    1,  324,    2, 0x06 /* Public */,
      16,    1,  327,    2, 0x06 /* Public */,
      17,    1,  330,    2, 0x06 /* Public */,
      18,    1,  333,    2, 0x06 /* Public */,
      19,    1,  336,    2, 0x06 /* Public */,
      20,    1,  339,    2, 0x06 /* Public */,
      21,    1,  342,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      22,    1,  345,    2, 0x0a /* Public */,
      23,    1,  348,    2, 0x0a /* Public */,
      24,    1,  351,    2, 0x0a /* Public */,
      25,    1,  354,    2, 0x0a /* Public */,
      26,    1,  357,    2, 0x0a /* Public */,
      27,    1,  360,    2, 0x0a /* Public */,
      28,    2,  363,    2, 0x0a /* Public */,
      29,    1,  368,    2, 0x0a /* Public */,
      30,    1,  371,    2, 0x0a /* Public */,
      31,    1,  374,    2, 0x0a /* Public */,
      32,    1,  377,    2, 0x0a /* Public */,
      33,    1,  380,    2, 0x0a /* Public */,
      34,    1,  383,    2, 0x0a /* Public */,
      35,    1,  386,    2, 0x0a /* Public */,
      36,    1,  389,    2, 0x0a /* Public */,
      37,    1,  392,    2, 0x0a /* Public */,
      38,    1,  395,    2, 0x0a /* Public */,
      39,    1,  398,    2, 0x0a /* Public */,
      40,    0,  401,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      41,    0,  402,    2, 0x02 /* Public */,
      42,    0,  403,    2, 0x02 /* Public */,
      43,    0,  404,    2, 0x02 /* Public */,
      44,    0,  405,    2, 0x02 /* Public */,
      45,    0,  406,    2, 0x02 /* Public */,
      46,    0,  407,    2, 0x02 /* Public */,
      47,    1,  408,    2, 0x02 /* Public */,
      48,    0,  411,    2, 0x02 /* Public */,
      49,    0,  412,    2, 0x02 /* Public */,
      50,    0,  413,    2, 0x02 /* Public */,
      51,    0,  414,    2, 0x02 /* Public */,
      52,    0,  415,    2, 0x02 /* Public */,
      53,    0,  416,    2, 0x02 /* Public */,
      54,    0,  417,    2, 0x02 /* Public */,
      55,    0,  418,    2, 0x02 /* Public */,
      56,    0,  419,    2, 0x02 /* Public */,
      57,    0,  420,    2, 0x02 /* Public */,
      58,    0,  421,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UShort,   10,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UShort,   10,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UShort, QMetaType::UInt,   10,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      59, QMetaType::Float, 0x00495103,
      60, QMetaType::Float, 0x00495103,
      61, QMetaType::Float, 0x00495103,
      62, QMetaType::Float, 0x00495103,
      63, QMetaType::Float, 0x00495103,
      64, QMetaType::Float, 0x00495103,
      65, QMetaType::UShort, 0x00495103,
      66, QMetaType::UShort, 0x00495103,
      67, QMetaType::UShort, 0x00495103,
      68, QMetaType::UShort, 0x00495103,
      69, QMetaType::UShort, 0x00495103,
      70, QMetaType::UShort, 0x00495103,
      71, QMetaType::UShort, 0x00495103,
      72, QMetaType::UShort, 0x00495103,
      73, QMetaType::UShort, 0x00495103,
      74, QMetaType::UChar, 0x00495103,
      75, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       0,
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

       0        // eod
};

void ManualControlCommand::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ManualControlCommand *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ThrottleChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->RollChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->PitchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->YawChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->CollectiveChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->ThrustChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->ChannelChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 7: _t->Channel_0Changed((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 8: _t->Channel_1Changed((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 9: _t->Channel_2Changed((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 10: _t->Channel_3Changed((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 11: _t->Channel_4Changed((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 12: _t->Channel_5Changed((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 13: _t->Channel_6Changed((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 14: _t->Channel_7Changed((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 15: _t->Channel_8Changed((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 16: _t->ConnectedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->FlightModeSwitchPositionChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 18: _t->setThrottle((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->setRoll((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->setPitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->setYaw((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: _t->setCollective((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->setThrust((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->setChannel((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 25: _t->setChannel_0((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 26: _t->setChannel_1((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 27: _t->setChannel_2((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 28: _t->setChannel_3((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 29: _t->setChannel_4((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 30: _t->setChannel_5((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 31: _t->setChannel_6((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 32: _t->setChannel_7((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 33: _t->setChannel_8((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 34: _t->setConnected((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 35: _t->setFlightModeSwitchPosition((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 36: _t->emitNotifications(); break;
        case 37: { float _r = _t->getThrottle();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 38: { float _r = _t->getRoll();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 39: { float _r = _t->getPitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 40: { float _r = _t->getYaw();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 41: { float _r = _t->getCollective();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 42: { float _r = _t->getThrust();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 43: { quint16 _r = _t->getChannel((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 44: { quint16 _r = _t->getChannel_0();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 45: { quint16 _r = _t->getChannel_1();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 46: { quint16 _r = _t->getChannel_2();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 47: { quint16 _r = _t->getChannel_3();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 48: { quint16 _r = _t->getChannel_4();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 49: { quint16 _r = _t->getChannel_5();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 50: { quint16 _r = _t->getChannel_6();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 51: { quint16 _r = _t->getChannel_7();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 52: { quint16 _r = _t->getChannel_8();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 53: { quint8 _r = _t->getConnected();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 54: { quint8 _r = _t->getFlightModeSwitchPosition();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ManualControlCommand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::ThrottleChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::RollChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::PitchChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::YawChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::CollectiveChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::ThrustChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(quint32 , quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::ChannelChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::Channel_0Changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::Channel_1Changed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::Channel_2Changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::Channel_3Changed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::Channel_4Changed)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::Channel_5Changed)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::Channel_6Changed)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::Channel_7Changed)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::Channel_8Changed)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::ConnectedChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (ManualControlCommand::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlCommand::FlightModeSwitchPositionChanged)) {
                *result = 17;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ManualControlCommand *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getThrottle(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getRoll(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getPitch(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getYaw(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getCollective(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getThrust(); break;
        case 6: *reinterpret_cast< quint16*>(_v) = _t->getChannel_0(); break;
        case 7: *reinterpret_cast< quint16*>(_v) = _t->getChannel_1(); break;
        case 8: *reinterpret_cast< quint16*>(_v) = _t->getChannel_2(); break;
        case 9: *reinterpret_cast< quint16*>(_v) = _t->getChannel_3(); break;
        case 10: *reinterpret_cast< quint16*>(_v) = _t->getChannel_4(); break;
        case 11: *reinterpret_cast< quint16*>(_v) = _t->getChannel_5(); break;
        case 12: *reinterpret_cast< quint16*>(_v) = _t->getChannel_6(); break;
        case 13: *reinterpret_cast< quint16*>(_v) = _t->getChannel_7(); break;
        case 14: *reinterpret_cast< quint16*>(_v) = _t->getChannel_8(); break;
        case 15: *reinterpret_cast< quint8*>(_v) = _t->getConnected(); break;
        case 16: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeSwitchPosition(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ManualControlCommand *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setThrottle(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setRoll(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setPitch(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setYaw(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setCollective(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setThrust(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setChannel_0(*reinterpret_cast< quint16*>(_v)); break;
        case 7: _t->setChannel_1(*reinterpret_cast< quint16*>(_v)); break;
        case 8: _t->setChannel_2(*reinterpret_cast< quint16*>(_v)); break;
        case 9: _t->setChannel_3(*reinterpret_cast< quint16*>(_v)); break;
        case 10: _t->setChannel_4(*reinterpret_cast< quint16*>(_v)); break;
        case 11: _t->setChannel_5(*reinterpret_cast< quint16*>(_v)); break;
        case 12: _t->setChannel_6(*reinterpret_cast< quint16*>(_v)); break;
        case 13: _t->setChannel_7(*reinterpret_cast< quint16*>(_v)); break;
        case 14: _t->setChannel_8(*reinterpret_cast< quint16*>(_v)); break;
        case 15: _t->setConnected(*reinterpret_cast< quint8*>(_v)); break;
        case 16: _t->setFlightModeSwitchPosition(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ManualControlCommand::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_ManualControlCommand.data,
    qt_meta_data_ManualControlCommand,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ManualControlCommand::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ManualControlCommand::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ManualControlCommand.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int ManualControlCommand::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 55)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 55;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 55)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 55;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 17;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ManualControlCommand::ThrottleChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ManualControlCommand::RollChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ManualControlCommand::PitchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ManualControlCommand::YawChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ManualControlCommand::CollectiveChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ManualControlCommand::ThrustChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ManualControlCommand::ChannelChanged(quint32 _t1, quint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ManualControlCommand::Channel_0Changed(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ManualControlCommand::Channel_1Changed(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ManualControlCommand::Channel_2Changed(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ManualControlCommand::Channel_3Changed(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ManualControlCommand::Channel_4Changed(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ManualControlCommand::Channel_5Changed(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ManualControlCommand::Channel_6Changed(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ManualControlCommand::Channel_7Changed(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void ManualControlCommand::Channel_8Changed(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void ManualControlCommand::ConnectedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void ManualControlCommand::FlightModeSwitchPositionChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
