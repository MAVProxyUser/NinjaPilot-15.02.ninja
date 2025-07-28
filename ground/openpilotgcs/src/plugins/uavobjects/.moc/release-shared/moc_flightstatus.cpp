/****************************************************************************
** Meta object code from reading C++ file 'flightstatus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/flightstatus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flightstatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FlightStatus_t {
    QByteArrayData data[40];
    char stringdata0[820];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlightStatus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlightStatus_t qt_meta_stringdata_FlightStatus = {
    {
QT_MOC_LITERAL(0, 0, 12), // "FlightStatus"
QT_MOC_LITERAL(1, 13, 12), // "ArmedChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "value"
QT_MOC_LITERAL(4, 33, 17), // "FlightModeChanged"
QT_MOC_LITERAL(5, 51, 23), // "FlightModeAssistChanged"
QT_MOC_LITERAL(6, 75, 27), // "AssistedControlStateChanged"
QT_MOC_LITERAL(7, 103, 28), // "AssistedThrottleStateChanged"
QT_MOC_LITERAL(8, 132, 19), // "ControlChainChanged"
QT_MOC_LITERAL(9, 152, 5), // "index"
QT_MOC_LITERAL(10, 158, 33), // "ControlChain_StabilizationCha..."
QT_MOC_LITERAL(11, 192, 32), // "ControlChain_PathFollowerChanged"
QT_MOC_LITERAL(12, 225, 31), // "ControlChain_PathPlannerChanged"
QT_MOC_LITERAL(13, 257, 8), // "setArmed"
QT_MOC_LITERAL(14, 266, 13), // "setFlightMode"
QT_MOC_LITERAL(15, 280, 19), // "setFlightModeAssist"
QT_MOC_LITERAL(16, 300, 23), // "setAssistedControlState"
QT_MOC_LITERAL(17, 324, 24), // "setAssistedThrottleState"
QT_MOC_LITERAL(18, 349, 15), // "setControlChain"
QT_MOC_LITERAL(19, 365, 29), // "setControlChain_Stabilization"
QT_MOC_LITERAL(20, 395, 28), // "setControlChain_PathFollower"
QT_MOC_LITERAL(21, 424, 27), // "setControlChain_PathPlanner"
QT_MOC_LITERAL(22, 452, 17), // "emitNotifications"
QT_MOC_LITERAL(23, 470, 8), // "getArmed"
QT_MOC_LITERAL(24, 479, 13), // "getFlightMode"
QT_MOC_LITERAL(25, 493, 19), // "getFlightModeAssist"
QT_MOC_LITERAL(26, 513, 23), // "getAssistedControlState"
QT_MOC_LITERAL(27, 537, 24), // "getAssistedThrottleState"
QT_MOC_LITERAL(28, 562, 15), // "getControlChain"
QT_MOC_LITERAL(29, 578, 29), // "getControlChain_Stabilization"
QT_MOC_LITERAL(30, 608, 28), // "getControlChain_PathFollower"
QT_MOC_LITERAL(31, 637, 27), // "getControlChain_PathPlanner"
QT_MOC_LITERAL(32, 665, 5), // "Armed"
QT_MOC_LITERAL(33, 671, 10), // "FlightMode"
QT_MOC_LITERAL(34, 682, 16), // "FlightModeAssist"
QT_MOC_LITERAL(35, 699, 20), // "AssistedControlState"
QT_MOC_LITERAL(36, 720, 21), // "AssistedThrottleState"
QT_MOC_LITERAL(37, 742, 26), // "ControlChain_Stabilization"
QT_MOC_LITERAL(38, 769, 25), // "ControlChain_PathFollower"
QT_MOC_LITERAL(39, 795, 24) // "ControlChain_PathPlanner"

    },
    "FlightStatus\0ArmedChanged\0\0value\0"
    "FlightModeChanged\0FlightModeAssistChanged\0"
    "AssistedControlStateChanged\0"
    "AssistedThrottleStateChanged\0"
    "ControlChainChanged\0index\0"
    "ControlChain_StabilizationChanged\0"
    "ControlChain_PathFollowerChanged\0"
    "ControlChain_PathPlannerChanged\0"
    "setArmed\0setFlightMode\0setFlightModeAssist\0"
    "setAssistedControlState\0"
    "setAssistedThrottleState\0setControlChain\0"
    "setControlChain_Stabilization\0"
    "setControlChain_PathFollower\0"
    "setControlChain_PathPlanner\0"
    "emitNotifications\0getArmed\0getFlightMode\0"
    "getFlightModeAssist\0getAssistedControlState\0"
    "getAssistedThrottleState\0getControlChain\0"
    "getControlChain_Stabilization\0"
    "getControlChain_PathFollower\0"
    "getControlChain_PathPlanner\0Armed\0"
    "FlightMode\0FlightModeAssist\0"
    "AssistedControlState\0AssistedThrottleState\0"
    "ControlChain_Stabilization\0"
    "ControlChain_PathFollower\0"
    "ControlChain_PathPlanner"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlightStatus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       8,  224, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  154,    2, 0x06 /* Public */,
       4,    1,  157,    2, 0x06 /* Public */,
       5,    1,  160,    2, 0x06 /* Public */,
       6,    1,  163,    2, 0x06 /* Public */,
       7,    1,  166,    2, 0x06 /* Public */,
       8,    2,  169,    2, 0x06 /* Public */,
      10,    1,  174,    2, 0x06 /* Public */,
      11,    1,  177,    2, 0x06 /* Public */,
      12,    1,  180,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,  183,    2, 0x0a /* Public */,
      14,    1,  186,    2, 0x0a /* Public */,
      15,    1,  189,    2, 0x0a /* Public */,
      16,    1,  192,    2, 0x0a /* Public */,
      17,    1,  195,    2, 0x0a /* Public */,
      18,    2,  198,    2, 0x0a /* Public */,
      19,    1,  203,    2, 0x0a /* Public */,
      20,    1,  206,    2, 0x0a /* Public */,
      21,    1,  209,    2, 0x0a /* Public */,
      22,    0,  212,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      23,    0,  213,    2, 0x02 /* Public */,
      24,    0,  214,    2, 0x02 /* Public */,
      25,    0,  215,    2, 0x02 /* Public */,
      26,    0,  216,    2, 0x02 /* Public */,
      27,    0,  217,    2, 0x02 /* Public */,
      28,    1,  218,    2, 0x02 /* Public */,
      29,    0,  221,    2, 0x02 /* Public */,
      30,    0,  222,    2, 0x02 /* Public */,
      31,    0,  223,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    9,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    9,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    9,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      32, QMetaType::UChar, 0x00495103,
      33, QMetaType::UChar, 0x00495103,
      34, QMetaType::UChar, 0x00495103,
      35, QMetaType::UChar, 0x00495103,
      36, QMetaType::UChar, 0x00495103,
      37, QMetaType::UChar, 0x00495103,
      38, QMetaType::UChar, 0x00495103,
      39, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       6,
       7,
       8,

       0        // eod
};

void FlightStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FlightStatus *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ArmedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->FlightModeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 2: _t->FlightModeAssistChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 3: _t->AssistedControlStateChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 4: _t->AssistedThrottleStateChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 5: _t->ControlChainChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 6: _t->ControlChain_StabilizationChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 7: _t->ControlChain_PathFollowerChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 8: _t->ControlChain_PathPlannerChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 9: _t->setArmed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 10: _t->setFlightMode((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 11: _t->setFlightModeAssist((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->setAssistedControlState((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 13: _t->setAssistedThrottleState((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->setControlChain((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 15: _t->setControlChain_Stabilization((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 16: _t->setControlChain_PathFollower((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->setControlChain_PathPlanner((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 18: _t->emitNotifications(); break;
        case 19: { quint8 _r = _t->getArmed();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 20: { quint8 _r = _t->getFlightMode();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 21: { quint8 _r = _t->getFlightModeAssist();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 22: { quint8 _r = _t->getAssistedControlState();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 23: { quint8 _r = _t->getAssistedThrottleState();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 24: { quint8 _r = _t->getControlChain((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 25: { quint8 _r = _t->getControlChain_Stabilization();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 26: { quint8 _r = _t->getControlChain_PathFollower();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 27: { quint8 _r = _t->getControlChain_PathPlanner();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FlightStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightStatus::ArmedChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FlightStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightStatus::FlightModeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FlightStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightStatus::FlightModeAssistChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FlightStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightStatus::AssistedControlStateChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FlightStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightStatus::AssistedThrottleStateChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FlightStatus::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightStatus::ControlChainChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (FlightStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightStatus::ControlChain_StabilizationChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (FlightStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightStatus::ControlChain_PathFollowerChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (FlightStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightStatus::ControlChain_PathPlannerChanged)) {
                *result = 8;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FlightStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint8*>(_v) = _t->getArmed(); break;
        case 1: *reinterpret_cast< quint8*>(_v) = _t->getFlightMode(); break;
        case 2: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeAssist(); break;
        case 3: *reinterpret_cast< quint8*>(_v) = _t->getAssistedControlState(); break;
        case 4: *reinterpret_cast< quint8*>(_v) = _t->getAssistedThrottleState(); break;
        case 5: *reinterpret_cast< quint8*>(_v) = _t->getControlChain_Stabilization(); break;
        case 6: *reinterpret_cast< quint8*>(_v) = _t->getControlChain_PathFollower(); break;
        case 7: *reinterpret_cast< quint8*>(_v) = _t->getControlChain_PathPlanner(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<FlightStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setArmed(*reinterpret_cast< quint8*>(_v)); break;
        case 1: _t->setFlightMode(*reinterpret_cast< quint8*>(_v)); break;
        case 2: _t->setFlightModeAssist(*reinterpret_cast< quint8*>(_v)); break;
        case 3: _t->setAssistedControlState(*reinterpret_cast< quint8*>(_v)); break;
        case 4: _t->setAssistedThrottleState(*reinterpret_cast< quint8*>(_v)); break;
        case 5: _t->setControlChain_Stabilization(*reinterpret_cast< quint8*>(_v)); break;
        case 6: _t->setControlChain_PathFollower(*reinterpret_cast< quint8*>(_v)); break;
        case 7: _t->setControlChain_PathPlanner(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject FlightStatus::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_FlightStatus.data,
    qt_meta_data_FlightStatus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FlightStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlightStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlightStatus.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int FlightStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 28;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FlightStatus::ArmedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FlightStatus::FlightModeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FlightStatus::FlightModeAssistChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FlightStatus::AssistedControlStateChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FlightStatus::AssistedThrottleStateChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FlightStatus::ControlChainChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void FlightStatus::ControlChain_StabilizationChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void FlightStatus::ControlChain_PathFollowerChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void FlightStatus::ControlChain_PathPlannerChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
