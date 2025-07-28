/****************************************************************************
** Meta object code from reading C++ file 'systemstats.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/systemstats.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'systemstats.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SystemStats_t {
    QByteArrayData data[56];
    char stringdata0[1026];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SystemStats_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SystemStats_t qt_meta_stringdata_SystemStats = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SystemStats"
QT_MOC_LITERAL(1, 12, 17), // "FlightTimeChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 5), // "value"
QT_MOC_LITERAL(4, 37, 20), // "HeapRemainingChanged"
QT_MOC_LITERAL(5, 58, 27), // "EventSystemWarningIDChanged"
QT_MOC_LITERAL(6, 86, 30), // "ObjectManagerCallbackIDChanged"
QT_MOC_LITERAL(7, 117, 27), // "ObjectManagerQueueIDChanged"
QT_MOC_LITERAL(8, 145, 24), // "IRQStackRemainingChanged"
QT_MOC_LITERAL(9, 170, 30), // "SystemModStackRemainingChanged"
QT_MOC_LITERAL(10, 201, 19), // "SysSlotsFreeChanged"
QT_MOC_LITERAL(11, 221, 21), // "SysSlotsActiveChanged"
QT_MOC_LITERAL(12, 243, 19), // "UsrSlotsFreeChanged"
QT_MOC_LITERAL(13, 263, 21), // "UsrSlotsActiveChanged"
QT_MOC_LITERAL(14, 285, 14), // "CPULoadChanged"
QT_MOC_LITERAL(15, 300, 14), // "CPUTempChanged"
QT_MOC_LITERAL(16, 315, 13), // "setFlightTime"
QT_MOC_LITERAL(17, 329, 16), // "setHeapRemaining"
QT_MOC_LITERAL(18, 346, 23), // "setEventSystemWarningID"
QT_MOC_LITERAL(19, 370, 26), // "setObjectManagerCallbackID"
QT_MOC_LITERAL(20, 397, 23), // "setObjectManagerQueueID"
QT_MOC_LITERAL(21, 421, 20), // "setIRQStackRemaining"
QT_MOC_LITERAL(22, 442, 26), // "setSystemModStackRemaining"
QT_MOC_LITERAL(23, 469, 15), // "setSysSlotsFree"
QT_MOC_LITERAL(24, 485, 17), // "setSysSlotsActive"
QT_MOC_LITERAL(25, 503, 15), // "setUsrSlotsFree"
QT_MOC_LITERAL(26, 519, 17), // "setUsrSlotsActive"
QT_MOC_LITERAL(27, 537, 10), // "setCPULoad"
QT_MOC_LITERAL(28, 548, 10), // "setCPUTemp"
QT_MOC_LITERAL(29, 559, 17), // "emitNotifications"
QT_MOC_LITERAL(30, 577, 13), // "getFlightTime"
QT_MOC_LITERAL(31, 591, 16), // "getHeapRemaining"
QT_MOC_LITERAL(32, 608, 23), // "getEventSystemWarningID"
QT_MOC_LITERAL(33, 632, 26), // "getObjectManagerCallbackID"
QT_MOC_LITERAL(34, 659, 23), // "getObjectManagerQueueID"
QT_MOC_LITERAL(35, 683, 20), // "getIRQStackRemaining"
QT_MOC_LITERAL(36, 704, 26), // "getSystemModStackRemaining"
QT_MOC_LITERAL(37, 731, 15), // "getSysSlotsFree"
QT_MOC_LITERAL(38, 747, 17), // "getSysSlotsActive"
QT_MOC_LITERAL(39, 765, 15), // "getUsrSlotsFree"
QT_MOC_LITERAL(40, 781, 17), // "getUsrSlotsActive"
QT_MOC_LITERAL(41, 799, 10), // "getCPULoad"
QT_MOC_LITERAL(42, 810, 10), // "getCPUTemp"
QT_MOC_LITERAL(43, 821, 10), // "FlightTime"
QT_MOC_LITERAL(44, 832, 13), // "HeapRemaining"
QT_MOC_LITERAL(45, 846, 20), // "EventSystemWarningID"
QT_MOC_LITERAL(46, 867, 23), // "ObjectManagerCallbackID"
QT_MOC_LITERAL(47, 891, 20), // "ObjectManagerQueueID"
QT_MOC_LITERAL(48, 912, 17), // "IRQStackRemaining"
QT_MOC_LITERAL(49, 930, 23), // "SystemModStackRemaining"
QT_MOC_LITERAL(50, 954, 12), // "SysSlotsFree"
QT_MOC_LITERAL(51, 967, 14), // "SysSlotsActive"
QT_MOC_LITERAL(52, 982, 12), // "UsrSlotsFree"
QT_MOC_LITERAL(53, 995, 14), // "UsrSlotsActive"
QT_MOC_LITERAL(54, 1010, 7), // "CPULoad"
QT_MOC_LITERAL(55, 1018, 7) // "CPUTemp"

    },
    "SystemStats\0FlightTimeChanged\0\0value\0"
    "HeapRemainingChanged\0EventSystemWarningIDChanged\0"
    "ObjectManagerCallbackIDChanged\0"
    "ObjectManagerQueueIDChanged\0"
    "IRQStackRemainingChanged\0"
    "SystemModStackRemainingChanged\0"
    "SysSlotsFreeChanged\0SysSlotsActiveChanged\0"
    "UsrSlotsFreeChanged\0UsrSlotsActiveChanged\0"
    "CPULoadChanged\0CPUTempChanged\0"
    "setFlightTime\0setHeapRemaining\0"
    "setEventSystemWarningID\0"
    "setObjectManagerCallbackID\0"
    "setObjectManagerQueueID\0setIRQStackRemaining\0"
    "setSystemModStackRemaining\0setSysSlotsFree\0"
    "setSysSlotsActive\0setUsrSlotsFree\0"
    "setUsrSlotsActive\0setCPULoad\0setCPUTemp\0"
    "emitNotifications\0getFlightTime\0"
    "getHeapRemaining\0getEventSystemWarningID\0"
    "getObjectManagerCallbackID\0"
    "getObjectManagerQueueID\0getIRQStackRemaining\0"
    "getSystemModStackRemaining\0getSysSlotsFree\0"
    "getSysSlotsActive\0getUsrSlotsFree\0"
    "getUsrSlotsActive\0getCPULoad\0getCPUTemp\0"
    "FlightTime\0HeapRemaining\0EventSystemWarningID\0"
    "ObjectManagerCallbackID\0ObjectManagerQueueID\0"
    "IRQStackRemaining\0SystemModStackRemaining\0"
    "SysSlotsFree\0SysSlotsActive\0UsrSlotsFree\0"
    "UsrSlotsActive\0CPULoad\0CPUTemp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SystemStats[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
      13,  306, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  214,    2, 0x06 /* Public */,
       4,    1,  217,    2, 0x06 /* Public */,
       5,    1,  220,    2, 0x06 /* Public */,
       6,    1,  223,    2, 0x06 /* Public */,
       7,    1,  226,    2, 0x06 /* Public */,
       8,    1,  229,    2, 0x06 /* Public */,
       9,    1,  232,    2, 0x06 /* Public */,
      10,    1,  235,    2, 0x06 /* Public */,
      11,    1,  238,    2, 0x06 /* Public */,
      12,    1,  241,    2, 0x06 /* Public */,
      13,    1,  244,    2, 0x06 /* Public */,
      14,    1,  247,    2, 0x06 /* Public */,
      15,    1,  250,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,  253,    2, 0x0a /* Public */,
      17,    1,  256,    2, 0x0a /* Public */,
      18,    1,  259,    2, 0x0a /* Public */,
      19,    1,  262,    2, 0x0a /* Public */,
      20,    1,  265,    2, 0x0a /* Public */,
      21,    1,  268,    2, 0x0a /* Public */,
      22,    1,  271,    2, 0x0a /* Public */,
      23,    1,  274,    2, 0x0a /* Public */,
      24,    1,  277,    2, 0x0a /* Public */,
      25,    1,  280,    2, 0x0a /* Public */,
      26,    1,  283,    2, 0x0a /* Public */,
      27,    1,  286,    2, 0x0a /* Public */,
      28,    1,  289,    2, 0x0a /* Public */,
      29,    0,  292,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      30,    0,  293,    2, 0x02 /* Public */,
      31,    0,  294,    2, 0x02 /* Public */,
      32,    0,  295,    2, 0x02 /* Public */,
      33,    0,  296,    2, 0x02 /* Public */,
      34,    0,  297,    2, 0x02 /* Public */,
      35,    0,  298,    2, 0x02 /* Public */,
      36,    0,  299,    2, 0x02 /* Public */,
      37,    0,  300,    2, 0x02 /* Public */,
      38,    0,  301,    2, 0x02 /* Public */,
      39,    0,  302,    2, 0x02 /* Public */,
      40,    0,  303,    2, 0x02 /* Public */,
      41,    0,  304,    2, 0x02 /* Public */,
      42,    0,  305,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UChar,
    QMetaType::SChar,

 // properties: name, type, flags
      43, QMetaType::UInt, 0x00495103,
      44, QMetaType::UInt, 0x00495103,
      45, QMetaType::UInt, 0x00495103,
      46, QMetaType::UInt, 0x00495103,
      47, QMetaType::UInt, 0x00495103,
      48, QMetaType::UShort, 0x00495103,
      49, QMetaType::UShort, 0x00495103,
      50, QMetaType::UShort, 0x00495103,
      51, QMetaType::UShort, 0x00495103,
      52, QMetaType::UShort, 0x00495103,
      53, QMetaType::UShort, 0x00495103,
      54, QMetaType::UChar, 0x00495103,
      55, QMetaType::SChar, 0x00495103,

 // properties: notify_signal_id
       0,
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

       0        // eod
};

void SystemStats::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SystemStats *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->FlightTimeChanged((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 1: _t->HeapRemainingChanged((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 2: _t->EventSystemWarningIDChanged((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 3: _t->ObjectManagerCallbackIDChanged((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 4: _t->ObjectManagerQueueIDChanged((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 5: _t->IRQStackRemainingChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 6: _t->SystemModStackRemainingChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 7: _t->SysSlotsFreeChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 8: _t->SysSlotsActiveChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 9: _t->UsrSlotsFreeChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 10: _t->UsrSlotsActiveChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 11: _t->CPULoadChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->CPUTempChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 13: _t->setFlightTime((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 14: _t->setHeapRemaining((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 15: _t->setEventSystemWarningID((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 16: _t->setObjectManagerCallbackID((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 17: _t->setObjectManagerQueueID((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 18: _t->setIRQStackRemaining((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 19: _t->setSystemModStackRemaining((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 20: _t->setSysSlotsFree((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 21: _t->setSysSlotsActive((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 22: _t->setUsrSlotsFree((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 23: _t->setUsrSlotsActive((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 24: _t->setCPULoad((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 25: _t->setCPUTemp((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 26: _t->emitNotifications(); break;
        case 27: { quint32 _r = _t->getFlightTime();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 28: { quint32 _r = _t->getHeapRemaining();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 29: { quint32 _r = _t->getEventSystemWarningID();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 30: { quint32 _r = _t->getObjectManagerCallbackID();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 31: { quint32 _r = _t->getObjectManagerQueueID();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 32: { quint16 _r = _t->getIRQStackRemaining();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 33: { quint16 _r = _t->getSystemModStackRemaining();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 34: { quint16 _r = _t->getSysSlotsFree();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 35: { quint16 _r = _t->getSysSlotsActive();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 36: { quint16 _r = _t->getUsrSlotsFree();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 37: { quint16 _r = _t->getUsrSlotsActive();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 38: { quint8 _r = _t->getCPULoad();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 39: { qint8 _r = _t->getCPUTemp();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SystemStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemStats::FlightTimeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SystemStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemStats::HeapRemainingChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SystemStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemStats::EventSystemWarningIDChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SystemStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemStats::ObjectManagerCallbackIDChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SystemStats::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemStats::ObjectManagerQueueIDChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SystemStats::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemStats::IRQStackRemainingChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SystemStats::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemStats::SystemModStackRemainingChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SystemStats::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemStats::SysSlotsFreeChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SystemStats::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemStats::SysSlotsActiveChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SystemStats::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemStats::UsrSlotsFreeChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SystemStats::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemStats::UsrSlotsActiveChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (SystemStats::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemStats::CPULoadChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (SystemStats::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemStats::CPUTempChanged)) {
                *result = 12;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SystemStats *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint32*>(_v) = _t->getFlightTime(); break;
        case 1: *reinterpret_cast< quint32*>(_v) = _t->getHeapRemaining(); break;
        case 2: *reinterpret_cast< quint32*>(_v) = _t->getEventSystemWarningID(); break;
        case 3: *reinterpret_cast< quint32*>(_v) = _t->getObjectManagerCallbackID(); break;
        case 4: *reinterpret_cast< quint32*>(_v) = _t->getObjectManagerQueueID(); break;
        case 5: *reinterpret_cast< quint16*>(_v) = _t->getIRQStackRemaining(); break;
        case 6: *reinterpret_cast< quint16*>(_v) = _t->getSystemModStackRemaining(); break;
        case 7: *reinterpret_cast< quint16*>(_v) = _t->getSysSlotsFree(); break;
        case 8: *reinterpret_cast< quint16*>(_v) = _t->getSysSlotsActive(); break;
        case 9: *reinterpret_cast< quint16*>(_v) = _t->getUsrSlotsFree(); break;
        case 10: *reinterpret_cast< quint16*>(_v) = _t->getUsrSlotsActive(); break;
        case 11: *reinterpret_cast< quint8*>(_v) = _t->getCPULoad(); break;
        case 12: *reinterpret_cast< qint8*>(_v) = _t->getCPUTemp(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SystemStats *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setFlightTime(*reinterpret_cast< quint32*>(_v)); break;
        case 1: _t->setHeapRemaining(*reinterpret_cast< quint32*>(_v)); break;
        case 2: _t->setEventSystemWarningID(*reinterpret_cast< quint32*>(_v)); break;
        case 3: _t->setObjectManagerCallbackID(*reinterpret_cast< quint32*>(_v)); break;
        case 4: _t->setObjectManagerQueueID(*reinterpret_cast< quint32*>(_v)); break;
        case 5: _t->setIRQStackRemaining(*reinterpret_cast< quint16*>(_v)); break;
        case 6: _t->setSystemModStackRemaining(*reinterpret_cast< quint16*>(_v)); break;
        case 7: _t->setSysSlotsFree(*reinterpret_cast< quint16*>(_v)); break;
        case 8: _t->setSysSlotsActive(*reinterpret_cast< quint16*>(_v)); break;
        case 9: _t->setUsrSlotsFree(*reinterpret_cast< quint16*>(_v)); break;
        case 10: _t->setUsrSlotsActive(*reinterpret_cast< quint16*>(_v)); break;
        case 11: _t->setCPULoad(*reinterpret_cast< quint8*>(_v)); break;
        case 12: _t->setCPUTemp(*reinterpret_cast< qint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject SystemStats::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_SystemStats.data,
    qt_meta_data_SystemStats,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SystemStats::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SystemStats::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SystemStats.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int SystemStats::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 40;
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
void SystemStats::FlightTimeChanged(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SystemStats::HeapRemainingChanged(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SystemStats::EventSystemWarningIDChanged(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SystemStats::ObjectManagerCallbackIDChanged(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SystemStats::ObjectManagerQueueIDChanged(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SystemStats::IRQStackRemainingChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SystemStats::SystemModStackRemainingChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SystemStats::SysSlotsFreeChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SystemStats::SysSlotsActiveChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void SystemStats::UsrSlotsFreeChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void SystemStats::UsrSlotsActiveChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void SystemStats::CPULoadChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void SystemStats::CPUTempChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
