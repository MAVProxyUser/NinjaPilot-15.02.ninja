/****************************************************************************
** Meta object code from reading C++ file 'pathaction.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/pathaction.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pathaction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PathAction_t {
    QByteArrayData data[63];
    char stringdata0[1202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PathAction_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PathAction_t qt_meta_stringdata_PathAction = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PathAction"
QT_MOC_LITERAL(1, 11, 21), // "ModeParametersChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "index"
QT_MOC_LITERAL(4, 40, 5), // "value"
QT_MOC_LITERAL(5, 46, 23), // "ModeParameters_0Changed"
QT_MOC_LITERAL(6, 70, 23), // "ModeParameters_1Changed"
QT_MOC_LITERAL(7, 94, 23), // "ModeParameters_2Changed"
QT_MOC_LITERAL(8, 118, 23), // "ModeParameters_3Changed"
QT_MOC_LITERAL(9, 142, 26), // "ConditionParametersChanged"
QT_MOC_LITERAL(10, 169, 28), // "ConditionParameters_0Changed"
QT_MOC_LITERAL(11, 198, 28), // "ConditionParameters_1Changed"
QT_MOC_LITERAL(12, 227, 28), // "ConditionParameters_2Changed"
QT_MOC_LITERAL(13, 256, 28), // "ConditionParameters_3Changed"
QT_MOC_LITERAL(14, 285, 22), // "JumpDestinationChanged"
QT_MOC_LITERAL(15, 308, 23), // "ErrorDestinationChanged"
QT_MOC_LITERAL(16, 332, 11), // "ModeChanged"
QT_MOC_LITERAL(17, 344, 19), // "EndConditionChanged"
QT_MOC_LITERAL(18, 364, 14), // "CommandChanged"
QT_MOC_LITERAL(19, 379, 17), // "setModeParameters"
QT_MOC_LITERAL(20, 397, 19), // "setModeParameters_0"
QT_MOC_LITERAL(21, 417, 19), // "setModeParameters_1"
QT_MOC_LITERAL(22, 437, 19), // "setModeParameters_2"
QT_MOC_LITERAL(23, 457, 19), // "setModeParameters_3"
QT_MOC_LITERAL(24, 477, 22), // "setConditionParameters"
QT_MOC_LITERAL(25, 500, 24), // "setConditionParameters_0"
QT_MOC_LITERAL(26, 525, 24), // "setConditionParameters_1"
QT_MOC_LITERAL(27, 550, 24), // "setConditionParameters_2"
QT_MOC_LITERAL(28, 575, 24), // "setConditionParameters_3"
QT_MOC_LITERAL(29, 600, 18), // "setJumpDestination"
QT_MOC_LITERAL(30, 619, 19), // "setErrorDestination"
QT_MOC_LITERAL(31, 639, 7), // "setMode"
QT_MOC_LITERAL(32, 647, 15), // "setEndCondition"
QT_MOC_LITERAL(33, 663, 10), // "setCommand"
QT_MOC_LITERAL(34, 674, 17), // "emitNotifications"
QT_MOC_LITERAL(35, 692, 17), // "getModeParameters"
QT_MOC_LITERAL(36, 710, 19), // "getModeParameters_0"
QT_MOC_LITERAL(37, 730, 19), // "getModeParameters_1"
QT_MOC_LITERAL(38, 750, 19), // "getModeParameters_2"
QT_MOC_LITERAL(39, 770, 19), // "getModeParameters_3"
QT_MOC_LITERAL(40, 790, 22), // "getConditionParameters"
QT_MOC_LITERAL(41, 813, 24), // "getConditionParameters_0"
QT_MOC_LITERAL(42, 838, 24), // "getConditionParameters_1"
QT_MOC_LITERAL(43, 863, 24), // "getConditionParameters_2"
QT_MOC_LITERAL(44, 888, 24), // "getConditionParameters_3"
QT_MOC_LITERAL(45, 913, 18), // "getJumpDestination"
QT_MOC_LITERAL(46, 932, 19), // "getErrorDestination"
QT_MOC_LITERAL(47, 952, 7), // "getMode"
QT_MOC_LITERAL(48, 960, 15), // "getEndCondition"
QT_MOC_LITERAL(49, 976, 10), // "getCommand"
QT_MOC_LITERAL(50, 987, 16), // "ModeParameters_0"
QT_MOC_LITERAL(51, 1004, 16), // "ModeParameters_1"
QT_MOC_LITERAL(52, 1021, 16), // "ModeParameters_2"
QT_MOC_LITERAL(53, 1038, 16), // "ModeParameters_3"
QT_MOC_LITERAL(54, 1055, 21), // "ConditionParameters_0"
QT_MOC_LITERAL(55, 1077, 21), // "ConditionParameters_1"
QT_MOC_LITERAL(56, 1099, 21), // "ConditionParameters_2"
QT_MOC_LITERAL(57, 1121, 21), // "ConditionParameters_3"
QT_MOC_LITERAL(58, 1143, 15), // "JumpDestination"
QT_MOC_LITERAL(59, 1159, 16), // "ErrorDestination"
QT_MOC_LITERAL(60, 1176, 4), // "Mode"
QT_MOC_LITERAL(61, 1181, 12), // "EndCondition"
QT_MOC_LITERAL(62, 1194, 7) // "Command"

    },
    "PathAction\0ModeParametersChanged\0\0"
    "index\0value\0ModeParameters_0Changed\0"
    "ModeParameters_1Changed\0ModeParameters_2Changed\0"
    "ModeParameters_3Changed\0"
    "ConditionParametersChanged\0"
    "ConditionParameters_0Changed\0"
    "ConditionParameters_1Changed\0"
    "ConditionParameters_2Changed\0"
    "ConditionParameters_3Changed\0"
    "JumpDestinationChanged\0ErrorDestinationChanged\0"
    "ModeChanged\0EndConditionChanged\0"
    "CommandChanged\0setModeParameters\0"
    "setModeParameters_0\0setModeParameters_1\0"
    "setModeParameters_2\0setModeParameters_3\0"
    "setConditionParameters\0setConditionParameters_0\0"
    "setConditionParameters_1\0"
    "setConditionParameters_2\0"
    "setConditionParameters_3\0setJumpDestination\0"
    "setErrorDestination\0setMode\0setEndCondition\0"
    "setCommand\0emitNotifications\0"
    "getModeParameters\0getModeParameters_0\0"
    "getModeParameters_1\0getModeParameters_2\0"
    "getModeParameters_3\0getConditionParameters\0"
    "getConditionParameters_0\0"
    "getConditionParameters_1\0"
    "getConditionParameters_2\0"
    "getConditionParameters_3\0getJumpDestination\0"
    "getErrorDestination\0getMode\0getEndCondition\0"
    "getCommand\0ModeParameters_0\0"
    "ModeParameters_1\0ModeParameters_2\0"
    "ModeParameters_3\0ConditionParameters_0\0"
    "ConditionParameters_1\0ConditionParameters_2\0"
    "ConditionParameters_3\0JumpDestination\0"
    "ErrorDestination\0Mode\0EndCondition\0"
    "Command"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PathAction[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      46,   14, // methods
      13,  362, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  244,    2, 0x06 /* Public */,
       5,    1,  249,    2, 0x06 /* Public */,
       6,    1,  252,    2, 0x06 /* Public */,
       7,    1,  255,    2, 0x06 /* Public */,
       8,    1,  258,    2, 0x06 /* Public */,
       9,    2,  261,    2, 0x06 /* Public */,
      10,    1,  266,    2, 0x06 /* Public */,
      11,    1,  269,    2, 0x06 /* Public */,
      12,    1,  272,    2, 0x06 /* Public */,
      13,    1,  275,    2, 0x06 /* Public */,
      14,    1,  278,    2, 0x06 /* Public */,
      15,    1,  281,    2, 0x06 /* Public */,
      16,    1,  284,    2, 0x06 /* Public */,
      17,    1,  287,    2, 0x06 /* Public */,
      18,    1,  290,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    2,  293,    2, 0x0a /* Public */,
      20,    1,  298,    2, 0x0a /* Public */,
      21,    1,  301,    2, 0x0a /* Public */,
      22,    1,  304,    2, 0x0a /* Public */,
      23,    1,  307,    2, 0x0a /* Public */,
      24,    2,  310,    2, 0x0a /* Public */,
      25,    1,  315,    2, 0x0a /* Public */,
      26,    1,  318,    2, 0x0a /* Public */,
      27,    1,  321,    2, 0x0a /* Public */,
      28,    1,  324,    2, 0x0a /* Public */,
      29,    1,  327,    2, 0x0a /* Public */,
      30,    1,  330,    2, 0x0a /* Public */,
      31,    1,  333,    2, 0x0a /* Public */,
      32,    1,  336,    2, 0x0a /* Public */,
      33,    1,  339,    2, 0x0a /* Public */,
      34,    0,  342,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      35,    1,  343,    2, 0x02 /* Public */,
      36,    0,  346,    2, 0x02 /* Public */,
      37,    0,  347,    2, 0x02 /* Public */,
      38,    0,  348,    2, 0x02 /* Public */,
      39,    0,  349,    2, 0x02 /* Public */,
      40,    1,  350,    2, 0x02 /* Public */,
      41,    0,  353,    2, 0x02 /* Public */,
      42,    0,  354,    2, 0x02 /* Public */,
      43,    0,  355,    2, 0x02 /* Public */,
      44,    0,  356,    2, 0x02 /* Public */,
      45,    0,  357,    2, 0x02 /* Public */,
      46,    0,  358,    2, 0x02 /* Public */,
      47,    0,  359,    2, 0x02 /* Public */,
      48,    0,  360,    2, 0x02 /* Public */,
      49,    0,  361,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::Short,    4,
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
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      50, QMetaType::Float, 0x00495103,
      51, QMetaType::Float, 0x00495103,
      52, QMetaType::Float, 0x00495103,
      53, QMetaType::Float, 0x00495103,
      54, QMetaType::Float, 0x00495103,
      55, QMetaType::Float, 0x00495103,
      56, QMetaType::Float, 0x00495103,
      57, QMetaType::Float, 0x00495103,
      58, QMetaType::Short, 0x00495103,
      59, QMetaType::Short, 0x00495103,
      60, QMetaType::UChar, 0x00495103,
      61, QMetaType::UChar, 0x00495103,
      62, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       1,
       2,
       3,
       4,
       6,
       7,
       8,
       9,
      10,
      11,
      12,
      13,
      14,

       0        // eod
};

void PathAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PathAction *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ModeParametersChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->ModeParameters_0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->ModeParameters_1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->ModeParameters_2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->ModeParameters_3Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->ConditionParametersChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 6: _t->ConditionParameters_0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->ConditionParameters_1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->ConditionParameters_2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->ConditionParameters_3Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->JumpDestinationChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 11: _t->ErrorDestinationChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 12: _t->ModeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 13: _t->EndConditionChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->CommandChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 15: _t->setModeParameters((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 16: _t->setModeParameters_0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 17: _t->setModeParameters_1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->setModeParameters_2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->setModeParameters_3((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->setConditionParameters((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 21: _t->setConditionParameters_0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: _t->setConditionParameters_1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->setConditionParameters_2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->setConditionParameters_3((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 25: _t->setJumpDestination((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 26: _t->setErrorDestination((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 27: _t->setMode((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 28: _t->setEndCondition((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 29: _t->setCommand((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 30: _t->emitNotifications(); break;
        case 31: { float _r = _t->getModeParameters((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 32: { float _r = _t->getModeParameters_0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 33: { float _r = _t->getModeParameters_1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 34: { float _r = _t->getModeParameters_2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 35: { float _r = _t->getModeParameters_3();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 36: { float _r = _t->getConditionParameters((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 37: { float _r = _t->getConditionParameters_0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 38: { float _r = _t->getConditionParameters_1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 39: { float _r = _t->getConditionParameters_2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 40: { float _r = _t->getConditionParameters_3();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 41: { qint16 _r = _t->getJumpDestination();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 42: { qint16 _r = _t->getErrorDestination();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 43: { quint8 _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 44: { quint8 _r = _t->getEndCondition();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 45: { quint8 _r = _t->getCommand();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PathAction::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::ModeParametersChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::ModeParameters_0Changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::ModeParameters_1Changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::ModeParameters_2Changed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::ModeParameters_3Changed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::ConditionParametersChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::ConditionParameters_0Changed)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::ConditionParameters_1Changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::ConditionParameters_2Changed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::ConditionParameters_3Changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::JumpDestinationChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::ErrorDestinationChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::ModeChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::EndConditionChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (PathAction::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathAction::CommandChanged)) {
                *result = 14;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PathAction *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getModeParameters_0(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getModeParameters_1(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getModeParameters_2(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getModeParameters_3(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getConditionParameters_0(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getConditionParameters_1(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getConditionParameters_2(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getConditionParameters_3(); break;
        case 8: *reinterpret_cast< qint16*>(_v) = _t->getJumpDestination(); break;
        case 9: *reinterpret_cast< qint16*>(_v) = _t->getErrorDestination(); break;
        case 10: *reinterpret_cast< quint8*>(_v) = _t->getMode(); break;
        case 11: *reinterpret_cast< quint8*>(_v) = _t->getEndCondition(); break;
        case 12: *reinterpret_cast< quint8*>(_v) = _t->getCommand(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PathAction *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setModeParameters_0(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setModeParameters_1(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setModeParameters_2(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setModeParameters_3(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setConditionParameters_0(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setConditionParameters_1(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setConditionParameters_2(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setConditionParameters_3(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setJumpDestination(*reinterpret_cast< qint16*>(_v)); break;
        case 9: _t->setErrorDestination(*reinterpret_cast< qint16*>(_v)); break;
        case 10: _t->setMode(*reinterpret_cast< quint8*>(_v)); break;
        case 11: _t->setEndCondition(*reinterpret_cast< quint8*>(_v)); break;
        case 12: _t->setCommand(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject PathAction::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_PathAction.data,
    qt_meta_data_PathAction,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PathAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PathAction::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PathAction.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int PathAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 46)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 46;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 46)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 46;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 13;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PathAction::ModeParametersChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PathAction::ModeParameters_0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PathAction::ModeParameters_1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PathAction::ModeParameters_2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PathAction::ModeParameters_3Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PathAction::ConditionParametersChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PathAction::ConditionParameters_0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PathAction::ConditionParameters_1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PathAction::ConditionParameters_2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void PathAction::ConditionParameters_3Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void PathAction::JumpDestinationChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void PathAction::ErrorDestinationChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void PathAction::ModeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void PathAction::EndConditionChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void PathAction::CommandChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
