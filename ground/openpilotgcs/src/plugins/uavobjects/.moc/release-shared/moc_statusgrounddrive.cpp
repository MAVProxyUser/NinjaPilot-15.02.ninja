/****************************************************************************
** Meta object code from reading C++ file 'statusgrounddrive.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/statusgrounddrive.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'statusgrounddrive.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StatusGroundDrive_t {
    QByteArrayData data[57];
    char stringdata0[1012];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StatusGroundDrive_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StatusGroundDrive_t qt_meta_stringdata_StatusGroundDrive = {
    {
QT_MOC_LITERAL(0, 0, 17), // "StatusGroundDrive"
QT_MOC_LITERAL(1, 18, 16), // "NECommandChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "index"
QT_MOC_LITERAL(4, 42, 5), // "value"
QT_MOC_LITERAL(5, 48, 22), // "NECommand_NorthChanged"
QT_MOC_LITERAL(6, 71, 21), // "NECommand_EastChanged"
QT_MOC_LITERAL(7, 93, 12), // "StateChanged"
QT_MOC_LITERAL(8, 106, 16), // "State_YawChanged"
QT_MOC_LITERAL(9, 123, 21), // "State_VelocityChanged"
QT_MOC_LITERAL(10, 145, 19), // "State_ThrustChanged"
QT_MOC_LITERAL(11, 165, 18), // "BodyCommandChanged"
QT_MOC_LITERAL(12, 184, 26), // "BodyCommand_ForwardChanged"
QT_MOC_LITERAL(13, 211, 24), // "BodyCommand_RightChanged"
QT_MOC_LITERAL(14, 236, 21), // "ControlCommandChanged"
QT_MOC_LITERAL(15, 258, 27), // "ControlCommand_SpeedChanged"
QT_MOC_LITERAL(16, 286, 28), // "ControlCommand_CourseChanged"
QT_MOC_LITERAL(17, 315, 19), // "ControlStateChanged"
QT_MOC_LITERAL(18, 335, 12), // "setNECommand"
QT_MOC_LITERAL(19, 348, 18), // "setNECommand_North"
QT_MOC_LITERAL(20, 367, 17), // "setNECommand_East"
QT_MOC_LITERAL(21, 385, 8), // "setState"
QT_MOC_LITERAL(22, 394, 12), // "setState_Yaw"
QT_MOC_LITERAL(23, 407, 17), // "setState_Velocity"
QT_MOC_LITERAL(24, 425, 15), // "setState_Thrust"
QT_MOC_LITERAL(25, 441, 14), // "setBodyCommand"
QT_MOC_LITERAL(26, 456, 22), // "setBodyCommand_Forward"
QT_MOC_LITERAL(27, 479, 20), // "setBodyCommand_Right"
QT_MOC_LITERAL(28, 500, 17), // "setControlCommand"
QT_MOC_LITERAL(29, 518, 23), // "setControlCommand_Speed"
QT_MOC_LITERAL(30, 542, 24), // "setControlCommand_Course"
QT_MOC_LITERAL(31, 567, 15), // "setControlState"
QT_MOC_LITERAL(32, 583, 17), // "emitNotifications"
QT_MOC_LITERAL(33, 601, 12), // "getNECommand"
QT_MOC_LITERAL(34, 614, 18), // "getNECommand_North"
QT_MOC_LITERAL(35, 633, 17), // "getNECommand_East"
QT_MOC_LITERAL(36, 651, 8), // "getState"
QT_MOC_LITERAL(37, 660, 12), // "getState_Yaw"
QT_MOC_LITERAL(38, 673, 17), // "getState_Velocity"
QT_MOC_LITERAL(39, 691, 15), // "getState_Thrust"
QT_MOC_LITERAL(40, 707, 14), // "getBodyCommand"
QT_MOC_LITERAL(41, 722, 22), // "getBodyCommand_Forward"
QT_MOC_LITERAL(42, 745, 20), // "getBodyCommand_Right"
QT_MOC_LITERAL(43, 766, 17), // "getControlCommand"
QT_MOC_LITERAL(44, 784, 23), // "getControlCommand_Speed"
QT_MOC_LITERAL(45, 808, 24), // "getControlCommand_Course"
QT_MOC_LITERAL(46, 833, 15), // "getControlState"
QT_MOC_LITERAL(47, 849, 15), // "NECommand_North"
QT_MOC_LITERAL(48, 865, 14), // "NECommand_East"
QT_MOC_LITERAL(49, 880, 9), // "State_Yaw"
QT_MOC_LITERAL(50, 890, 14), // "State_Velocity"
QT_MOC_LITERAL(51, 905, 12), // "State_Thrust"
QT_MOC_LITERAL(52, 918, 19), // "BodyCommand_Forward"
QT_MOC_LITERAL(53, 938, 17), // "BodyCommand_Right"
QT_MOC_LITERAL(54, 956, 20), // "ControlCommand_Speed"
QT_MOC_LITERAL(55, 977, 21), // "ControlCommand_Course"
QT_MOC_LITERAL(56, 999, 12) // "ControlState"

    },
    "StatusGroundDrive\0NECommandChanged\0\0"
    "index\0value\0NECommand_NorthChanged\0"
    "NECommand_EastChanged\0StateChanged\0"
    "State_YawChanged\0State_VelocityChanged\0"
    "State_ThrustChanged\0BodyCommandChanged\0"
    "BodyCommand_ForwardChanged\0"
    "BodyCommand_RightChanged\0ControlCommandChanged\0"
    "ControlCommand_SpeedChanged\0"
    "ControlCommand_CourseChanged\0"
    "ControlStateChanged\0setNECommand\0"
    "setNECommand_North\0setNECommand_East\0"
    "setState\0setState_Yaw\0setState_Velocity\0"
    "setState_Thrust\0setBodyCommand\0"
    "setBodyCommand_Forward\0setBodyCommand_Right\0"
    "setControlCommand\0setControlCommand_Speed\0"
    "setControlCommand_Course\0setControlState\0"
    "emitNotifications\0getNECommand\0"
    "getNECommand_North\0getNECommand_East\0"
    "getState\0getState_Yaw\0getState_Velocity\0"
    "getState_Thrust\0getBodyCommand\0"
    "getBodyCommand_Forward\0getBodyCommand_Right\0"
    "getControlCommand\0getControlCommand_Speed\0"
    "getControlCommand_Course\0getControlState\0"
    "NECommand_North\0NECommand_East\0State_Yaw\0"
    "State_Velocity\0State_Thrust\0"
    "BodyCommand_Forward\0BodyCommand_Right\0"
    "ControlCommand_Speed\0ControlCommand_Course\0"
    "ControlState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StatusGroundDrive[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
      10,  352, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  229,    2, 0x06 /* Public */,
       5,    1,  234,    2, 0x06 /* Public */,
       6,    1,  237,    2, 0x06 /* Public */,
       7,    2,  240,    2, 0x06 /* Public */,
       8,    1,  245,    2, 0x06 /* Public */,
       9,    1,  248,    2, 0x06 /* Public */,
      10,    1,  251,    2, 0x06 /* Public */,
      11,    2,  254,    2, 0x06 /* Public */,
      12,    1,  259,    2, 0x06 /* Public */,
      13,    1,  262,    2, 0x06 /* Public */,
      14,    2,  265,    2, 0x06 /* Public */,
      15,    1,  270,    2, 0x06 /* Public */,
      16,    1,  273,    2, 0x06 /* Public */,
      17,    1,  276,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    2,  279,    2, 0x0a /* Public */,
      19,    1,  284,    2, 0x0a /* Public */,
      20,    1,  287,    2, 0x0a /* Public */,
      21,    2,  290,    2, 0x0a /* Public */,
      22,    1,  295,    2, 0x0a /* Public */,
      23,    1,  298,    2, 0x0a /* Public */,
      24,    1,  301,    2, 0x0a /* Public */,
      25,    2,  304,    2, 0x0a /* Public */,
      26,    1,  309,    2, 0x0a /* Public */,
      27,    1,  312,    2, 0x0a /* Public */,
      28,    2,  315,    2, 0x0a /* Public */,
      29,    1,  320,    2, 0x0a /* Public */,
      30,    1,  323,    2, 0x0a /* Public */,
      31,    1,  326,    2, 0x0a /* Public */,
      32,    0,  329,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      33,    1,  330,    2, 0x02 /* Public */,
      34,    0,  333,    2, 0x02 /* Public */,
      35,    0,  334,    2, 0x02 /* Public */,
      36,    1,  335,    2, 0x02 /* Public */,
      37,    0,  338,    2, 0x02 /* Public */,
      38,    0,  339,    2, 0x02 /* Public */,
      39,    0,  340,    2, 0x02 /* Public */,
      40,    1,  341,    2, 0x02 /* Public */,
      41,    0,  344,    2, 0x02 /* Public */,
      42,    0,  345,    2, 0x02 /* Public */,
      43,    1,  346,    2, 0x02 /* Public */,
      44,    0,  349,    2, 0x02 /* Public */,
      45,    0,  350,    2, 0x02 /* Public */,
      46,    0,  351,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UChar,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar,

 // properties: name, type, flags
      47, QMetaType::Float, 0x00495103,
      48, QMetaType::Float, 0x00495103,
      49, QMetaType::Float, 0x00495103,
      50, QMetaType::Float, 0x00495103,
      51, QMetaType::Float, 0x00495103,
      52, QMetaType::Float, 0x00495103,
      53, QMetaType::Float, 0x00495103,
      54, QMetaType::Float, 0x00495103,
      55, QMetaType::Float, 0x00495103,
      56, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       1,
       2,
       4,
       5,
       6,
       8,
       9,
      11,
      12,
      13,

       0        // eod
};

void StatusGroundDrive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StatusGroundDrive *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->NECommandChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->NECommand_NorthChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->NECommand_EastChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->StateChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 4: _t->State_YawChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->State_VelocityChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->State_ThrustChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->BodyCommandChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 8: _t->BodyCommand_ForwardChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->BodyCommand_RightChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->ControlCommandChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 11: _t->ControlCommand_SpeedChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->ControlCommand_CourseChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->ControlStateChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->setNECommand((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 15: _t->setNECommand_North((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->setNECommand_East((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 17: _t->setState((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 18: _t->setState_Yaw((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->setState_Velocity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->setState_Thrust((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->setBodyCommand((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 22: _t->setBodyCommand_Forward((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->setBodyCommand_Right((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->setControlCommand((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 25: _t->setControlCommand_Speed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 26: _t->setControlCommand_Course((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->setControlState((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 28: _t->emitNotifications(); break;
        case 29: { float _r = _t->getNECommand((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 30: { float _r = _t->getNECommand_North();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 31: { float _r = _t->getNECommand_East();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 32: { float _r = _t->getState((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 33: { float _r = _t->getState_Yaw();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 34: { float _r = _t->getState_Velocity();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 35: { float _r = _t->getState_Thrust();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 36: { float _r = _t->getBodyCommand((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 37: { float _r = _t->getBodyCommand_Forward();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 38: { float _r = _t->getBodyCommand_Right();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 39: { float _r = _t->getControlCommand((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 40: { float _r = _t->getControlCommand_Speed();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 41: { float _r = _t->getControlCommand_Course();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 42: { quint8 _r = _t->getControlState();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StatusGroundDrive::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::NECommandChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StatusGroundDrive::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::NECommand_NorthChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (StatusGroundDrive::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::NECommand_EastChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (StatusGroundDrive::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::StateChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (StatusGroundDrive::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::State_YawChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (StatusGroundDrive::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::State_VelocityChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (StatusGroundDrive::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::State_ThrustChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (StatusGroundDrive::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::BodyCommandChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (StatusGroundDrive::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::BodyCommand_ForwardChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (StatusGroundDrive::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::BodyCommand_RightChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (StatusGroundDrive::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::ControlCommandChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (StatusGroundDrive::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::ControlCommand_SpeedChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (StatusGroundDrive::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::ControlCommand_CourseChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (StatusGroundDrive::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusGroundDrive::ControlStateChanged)) {
                *result = 13;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<StatusGroundDrive *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getNECommand_North(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getNECommand_East(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getState_Yaw(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getState_Velocity(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getState_Thrust(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getBodyCommand_Forward(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getBodyCommand_Right(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getControlCommand_Speed(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getControlCommand_Course(); break;
        case 9: *reinterpret_cast< quint8*>(_v) = _t->getControlState(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<StatusGroundDrive *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setNECommand_North(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setNECommand_East(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setState_Yaw(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setState_Velocity(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setState_Thrust(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setBodyCommand_Forward(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setBodyCommand_Right(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setControlCommand_Speed(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setControlCommand_Course(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setControlState(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject StatusGroundDrive::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_StatusGroundDrive.data,
    qt_meta_data_StatusGroundDrive,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StatusGroundDrive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StatusGroundDrive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StatusGroundDrive.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int StatusGroundDrive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 43)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 43)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 43;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void StatusGroundDrive::NECommandChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StatusGroundDrive::NECommand_NorthChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StatusGroundDrive::NECommand_EastChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void StatusGroundDrive::StateChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void StatusGroundDrive::State_YawChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void StatusGroundDrive::State_VelocityChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void StatusGroundDrive::State_ThrustChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void StatusGroundDrive::BodyCommandChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void StatusGroundDrive::BodyCommand_ForwardChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void StatusGroundDrive::BodyCommand_RightChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void StatusGroundDrive::ControlCommandChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void StatusGroundDrive::ControlCommand_SpeedChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void StatusGroundDrive::ControlCommand_CourseChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void StatusGroundDrive::ControlStateChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
