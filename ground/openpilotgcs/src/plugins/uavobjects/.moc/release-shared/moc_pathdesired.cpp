/****************************************************************************
** Meta object code from reading C++ file 'pathdesired.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/pathdesired.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pathdesired.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PathDesired_t {
    QByteArrayData data[70];
    char stringdata0[1023];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PathDesired_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PathDesired_t qt_meta_stringdata_PathDesired = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PathDesired"
QT_MOC_LITERAL(1, 12, 12), // "StartChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "index"
QT_MOC_LITERAL(4, 32, 5), // "value"
QT_MOC_LITERAL(5, 38, 18), // "Start_NorthChanged"
QT_MOC_LITERAL(6, 57, 17), // "Start_EastChanged"
QT_MOC_LITERAL(7, 75, 17), // "Start_DownChanged"
QT_MOC_LITERAL(8, 93, 10), // "EndChanged"
QT_MOC_LITERAL(9, 104, 16), // "End_NorthChanged"
QT_MOC_LITERAL(10, 121, 15), // "End_EastChanged"
QT_MOC_LITERAL(11, 137, 15), // "End_DownChanged"
QT_MOC_LITERAL(12, 153, 23), // "StartingVelocityChanged"
QT_MOC_LITERAL(13, 177, 21), // "EndingVelocityChanged"
QT_MOC_LITERAL(14, 199, 21), // "ModeParametersChanged"
QT_MOC_LITERAL(15, 221, 23), // "ModeParameters_0Changed"
QT_MOC_LITERAL(16, 245, 23), // "ModeParameters_1Changed"
QT_MOC_LITERAL(17, 269, 23), // "ModeParameters_2Changed"
QT_MOC_LITERAL(18, 293, 23), // "ModeParameters_3Changed"
QT_MOC_LITERAL(19, 317, 10), // "UIDChanged"
QT_MOC_LITERAL(20, 328, 11), // "ModeChanged"
QT_MOC_LITERAL(21, 340, 8), // "setStart"
QT_MOC_LITERAL(22, 349, 14), // "setStart_North"
QT_MOC_LITERAL(23, 364, 13), // "setStart_East"
QT_MOC_LITERAL(24, 378, 13), // "setStart_Down"
QT_MOC_LITERAL(25, 392, 6), // "setEnd"
QT_MOC_LITERAL(26, 399, 12), // "setEnd_North"
QT_MOC_LITERAL(27, 412, 11), // "setEnd_East"
QT_MOC_LITERAL(28, 424, 11), // "setEnd_Down"
QT_MOC_LITERAL(29, 436, 19), // "setStartingVelocity"
QT_MOC_LITERAL(30, 456, 17), // "setEndingVelocity"
QT_MOC_LITERAL(31, 474, 17), // "setModeParameters"
QT_MOC_LITERAL(32, 492, 19), // "setModeParameters_0"
QT_MOC_LITERAL(33, 512, 19), // "setModeParameters_1"
QT_MOC_LITERAL(34, 532, 19), // "setModeParameters_2"
QT_MOC_LITERAL(35, 552, 19), // "setModeParameters_3"
QT_MOC_LITERAL(36, 572, 6), // "setUID"
QT_MOC_LITERAL(37, 579, 7), // "setMode"
QT_MOC_LITERAL(38, 587, 17), // "emitNotifications"
QT_MOC_LITERAL(39, 605, 8), // "getStart"
QT_MOC_LITERAL(40, 614, 14), // "getStart_North"
QT_MOC_LITERAL(41, 629, 13), // "getStart_East"
QT_MOC_LITERAL(42, 643, 13), // "getStart_Down"
QT_MOC_LITERAL(43, 657, 6), // "getEnd"
QT_MOC_LITERAL(44, 664, 12), // "getEnd_North"
QT_MOC_LITERAL(45, 677, 11), // "getEnd_East"
QT_MOC_LITERAL(46, 689, 11), // "getEnd_Down"
QT_MOC_LITERAL(47, 701, 19), // "getStartingVelocity"
QT_MOC_LITERAL(48, 721, 17), // "getEndingVelocity"
QT_MOC_LITERAL(49, 739, 17), // "getModeParameters"
QT_MOC_LITERAL(50, 757, 19), // "getModeParameters_0"
QT_MOC_LITERAL(51, 777, 19), // "getModeParameters_1"
QT_MOC_LITERAL(52, 797, 19), // "getModeParameters_2"
QT_MOC_LITERAL(53, 817, 19), // "getModeParameters_3"
QT_MOC_LITERAL(54, 837, 6), // "getUID"
QT_MOC_LITERAL(55, 844, 7), // "getMode"
QT_MOC_LITERAL(56, 852, 11), // "Start_North"
QT_MOC_LITERAL(57, 864, 10), // "Start_East"
QT_MOC_LITERAL(58, 875, 10), // "Start_Down"
QT_MOC_LITERAL(59, 886, 9), // "End_North"
QT_MOC_LITERAL(60, 896, 8), // "End_East"
QT_MOC_LITERAL(61, 905, 8), // "End_Down"
QT_MOC_LITERAL(62, 914, 16), // "StartingVelocity"
QT_MOC_LITERAL(63, 931, 14), // "EndingVelocity"
QT_MOC_LITERAL(64, 946, 16), // "ModeParameters_0"
QT_MOC_LITERAL(65, 963, 16), // "ModeParameters_1"
QT_MOC_LITERAL(66, 980, 16), // "ModeParameters_2"
QT_MOC_LITERAL(67, 997, 16), // "ModeParameters_3"
QT_MOC_LITERAL(68, 1014, 3), // "UID"
QT_MOC_LITERAL(69, 1018, 4) // "Mode"

    },
    "PathDesired\0StartChanged\0\0index\0value\0"
    "Start_NorthChanged\0Start_EastChanged\0"
    "Start_DownChanged\0EndChanged\0"
    "End_NorthChanged\0End_EastChanged\0"
    "End_DownChanged\0StartingVelocityChanged\0"
    "EndingVelocityChanged\0ModeParametersChanged\0"
    "ModeParameters_0Changed\0ModeParameters_1Changed\0"
    "ModeParameters_2Changed\0ModeParameters_3Changed\0"
    "UIDChanged\0ModeChanged\0setStart\0"
    "setStart_North\0setStart_East\0setStart_Down\0"
    "setEnd\0setEnd_North\0setEnd_East\0"
    "setEnd_Down\0setStartingVelocity\0"
    "setEndingVelocity\0setModeParameters\0"
    "setModeParameters_0\0setModeParameters_1\0"
    "setModeParameters_2\0setModeParameters_3\0"
    "setUID\0setMode\0emitNotifications\0"
    "getStart\0getStart_North\0getStart_East\0"
    "getStart_Down\0getEnd\0getEnd_North\0"
    "getEnd_East\0getEnd_Down\0getStartingVelocity\0"
    "getEndingVelocity\0getModeParameters\0"
    "getModeParameters_0\0getModeParameters_1\0"
    "getModeParameters_2\0getModeParameters_3\0"
    "getUID\0getMode\0Start_North\0Start_East\0"
    "Start_Down\0End_North\0End_East\0End_Down\0"
    "StartingVelocity\0EndingVelocity\0"
    "ModeParameters_0\0ModeParameters_1\0"
    "ModeParameters_2\0ModeParameters_3\0UID\0"
    "Mode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PathDesired[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      52,   14, // methods
      14,  412, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  274,    2, 0x06 /* Public */,
       5,    1,  279,    2, 0x06 /* Public */,
       6,    1,  282,    2, 0x06 /* Public */,
       7,    1,  285,    2, 0x06 /* Public */,
       8,    2,  288,    2, 0x06 /* Public */,
       9,    1,  293,    2, 0x06 /* Public */,
      10,    1,  296,    2, 0x06 /* Public */,
      11,    1,  299,    2, 0x06 /* Public */,
      12,    1,  302,    2, 0x06 /* Public */,
      13,    1,  305,    2, 0x06 /* Public */,
      14,    2,  308,    2, 0x06 /* Public */,
      15,    1,  313,    2, 0x06 /* Public */,
      16,    1,  316,    2, 0x06 /* Public */,
      17,    1,  319,    2, 0x06 /* Public */,
      18,    1,  322,    2, 0x06 /* Public */,
      19,    1,  325,    2, 0x06 /* Public */,
      20,    1,  328,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    2,  331,    2, 0x0a /* Public */,
      22,    1,  336,    2, 0x0a /* Public */,
      23,    1,  339,    2, 0x0a /* Public */,
      24,    1,  342,    2, 0x0a /* Public */,
      25,    2,  345,    2, 0x0a /* Public */,
      26,    1,  350,    2, 0x0a /* Public */,
      27,    1,  353,    2, 0x0a /* Public */,
      28,    1,  356,    2, 0x0a /* Public */,
      29,    1,  359,    2, 0x0a /* Public */,
      30,    1,  362,    2, 0x0a /* Public */,
      31,    2,  365,    2, 0x0a /* Public */,
      32,    1,  370,    2, 0x0a /* Public */,
      33,    1,  373,    2, 0x0a /* Public */,
      34,    1,  376,    2, 0x0a /* Public */,
      35,    1,  379,    2, 0x0a /* Public */,
      36,    1,  382,    2, 0x0a /* Public */,
      37,    1,  385,    2, 0x0a /* Public */,
      38,    0,  388,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      39,    1,  389,    2, 0x02 /* Public */,
      40,    0,  392,    2, 0x02 /* Public */,
      41,    0,  393,    2, 0x02 /* Public */,
      42,    0,  394,    2, 0x02 /* Public */,
      43,    1,  395,    2, 0x02 /* Public */,
      44,    0,  398,    2, 0x02 /* Public */,
      45,    0,  399,    2, 0x02 /* Public */,
      46,    0,  400,    2, 0x02 /* Public */,
      47,    0,  401,    2, 0x02 /* Public */,
      48,    0,  402,    2, 0x02 /* Public */,
      49,    1,  403,    2, 0x02 /* Public */,
      50,    0,  406,    2, 0x02 /* Public */,
      51,    0,  407,    2, 0x02 /* Public */,
      52,    0,  408,    2, 0x02 /* Public */,
      53,    0,  409,    2, 0x02 /* Public */,
      54,    0,  410,    2, 0x02 /* Public */,
      55,    0,  411,    2, 0x02 /* Public */,

 // signals: parameters
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
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UChar,    4,

 // slots: parameters
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
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, QMetaType::UChar,    4,
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
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Short,
    QMetaType::UChar,

 // properties: name, type, flags
      56, QMetaType::Float, 0x00495103,
      57, QMetaType::Float, 0x00495103,
      58, QMetaType::Float, 0x00495103,
      59, QMetaType::Float, 0x00495103,
      60, QMetaType::Float, 0x00495103,
      61, QMetaType::Float, 0x00495103,
      62, QMetaType::Float, 0x00495103,
      63, QMetaType::Float, 0x00495103,
      64, QMetaType::Float, 0x00495103,
      65, QMetaType::Float, 0x00495103,
      66, QMetaType::Float, 0x00495103,
      67, QMetaType::Float, 0x00495103,
      68, QMetaType::Short, 0x00495103,
      69, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       1,
       2,
       3,
       5,
       6,
       7,
       8,
       9,
      11,
      12,
      13,
      14,
      15,
      16,

       0        // eod
};

void PathDesired::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PathDesired *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->StartChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->Start_NorthChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->Start_EastChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->Start_DownChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->EndChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->End_NorthChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->End_EastChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->End_DownChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->StartingVelocityChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->EndingVelocityChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->ModeParametersChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 11: _t->ModeParameters_0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->ModeParameters_1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->ModeParameters_2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->ModeParameters_3Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->UIDChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 16: _t->ModeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->setStart((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 18: _t->setStart_North((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->setStart_East((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->setStart_Down((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->setEnd((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 22: _t->setEnd_North((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->setEnd_East((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->setEnd_Down((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 25: _t->setStartingVelocity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 26: _t->setEndingVelocity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->setModeParameters((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 28: _t->setModeParameters_0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 29: _t->setModeParameters_1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 30: _t->setModeParameters_2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 31: _t->setModeParameters_3((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 32: _t->setUID((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 33: _t->setMode((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 34: _t->emitNotifications(); break;
        case 35: { float _r = _t->getStart((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 36: { float _r = _t->getStart_North();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 37: { float _r = _t->getStart_East();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 38: { float _r = _t->getStart_Down();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 39: { float _r = _t->getEnd((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 40: { float _r = _t->getEnd_North();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 41: { float _r = _t->getEnd_East();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 42: { float _r = _t->getEnd_Down();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 43: { float _r = _t->getStartingVelocity();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 44: { float _r = _t->getEndingVelocity();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 45: { float _r = _t->getModeParameters((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 46: { float _r = _t->getModeParameters_0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 47: { float _r = _t->getModeParameters_1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 48: { float _r = _t->getModeParameters_2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 49: { float _r = _t->getModeParameters_3();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 50: { qint16 _r = _t->getUID();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 51: { quint8 _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PathDesired::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::StartChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::Start_NorthChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::Start_EastChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::Start_DownChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::EndChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::End_NorthChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::End_EastChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::End_DownChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::StartingVelocityChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::EndingVelocityChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::ModeParametersChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::ModeParameters_0Changed)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::ModeParameters_1Changed)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::ModeParameters_2Changed)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::ModeParameters_3Changed)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::UIDChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (PathDesired::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDesired::ModeChanged)) {
                *result = 16;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PathDesired *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getStart_North(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getStart_East(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getStart_Down(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getEnd_North(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getEnd_East(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getEnd_Down(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getStartingVelocity(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getEndingVelocity(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getModeParameters_0(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->getModeParameters_1(); break;
        case 10: *reinterpret_cast< float*>(_v) = _t->getModeParameters_2(); break;
        case 11: *reinterpret_cast< float*>(_v) = _t->getModeParameters_3(); break;
        case 12: *reinterpret_cast< qint16*>(_v) = _t->getUID(); break;
        case 13: *reinterpret_cast< quint8*>(_v) = _t->getMode(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PathDesired *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setStart_North(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setStart_East(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setStart_Down(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setEnd_North(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setEnd_East(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setEnd_Down(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setStartingVelocity(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setEndingVelocity(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setModeParameters_0(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setModeParameters_1(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setModeParameters_2(*reinterpret_cast< float*>(_v)); break;
        case 11: _t->setModeParameters_3(*reinterpret_cast< float*>(_v)); break;
        case 12: _t->setUID(*reinterpret_cast< qint16*>(_v)); break;
        case 13: _t->setMode(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject PathDesired::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_PathDesired.data,
    qt_meta_data_PathDesired,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PathDesired::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PathDesired::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PathDesired.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int PathDesired::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 52)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 52;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 52)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 52;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 14;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PathDesired::StartChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PathDesired::Start_NorthChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PathDesired::Start_EastChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PathDesired::Start_DownChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PathDesired::EndChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PathDesired::End_NorthChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PathDesired::End_EastChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PathDesired::End_DownChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PathDesired::StartingVelocityChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void PathDesired::EndingVelocityChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void PathDesired::ModeParametersChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void PathDesired::ModeParameters_0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void PathDesired::ModeParameters_1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void PathDesired::ModeParameters_2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void PathDesired::ModeParameters_3Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void PathDesired::UIDChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void PathDesired::ModeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
