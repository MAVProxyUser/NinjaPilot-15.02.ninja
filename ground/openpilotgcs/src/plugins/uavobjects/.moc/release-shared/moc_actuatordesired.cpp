/****************************************************************************
** Meta object code from reading C++ file 'actuatordesired.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/actuatordesired.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'actuatordesired.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ActuatorDesired_t {
    QByteArrayData data[28];
    char stringdata0[311];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ActuatorDesired_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ActuatorDesired_t qt_meta_stringdata_ActuatorDesired = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ActuatorDesired"
QT_MOC_LITERAL(1, 16, 11), // "RollChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "value"
QT_MOC_LITERAL(4, 35, 12), // "PitchChanged"
QT_MOC_LITERAL(5, 48, 10), // "YawChanged"
QT_MOC_LITERAL(6, 59, 13), // "ThrustChanged"
QT_MOC_LITERAL(7, 73, 17), // "UpdateTimeChanged"
QT_MOC_LITERAL(8, 91, 21), // "NumLongUpdatesChanged"
QT_MOC_LITERAL(9, 113, 7), // "setRoll"
QT_MOC_LITERAL(10, 121, 8), // "setPitch"
QT_MOC_LITERAL(11, 130, 6), // "setYaw"
QT_MOC_LITERAL(12, 137, 9), // "setThrust"
QT_MOC_LITERAL(13, 147, 13), // "setUpdateTime"
QT_MOC_LITERAL(14, 161, 17), // "setNumLongUpdates"
QT_MOC_LITERAL(15, 179, 17), // "emitNotifications"
QT_MOC_LITERAL(16, 197, 7), // "getRoll"
QT_MOC_LITERAL(17, 205, 8), // "getPitch"
QT_MOC_LITERAL(18, 214, 6), // "getYaw"
QT_MOC_LITERAL(19, 221, 9), // "getThrust"
QT_MOC_LITERAL(20, 231, 13), // "getUpdateTime"
QT_MOC_LITERAL(21, 245, 17), // "getNumLongUpdates"
QT_MOC_LITERAL(22, 263, 4), // "Roll"
QT_MOC_LITERAL(23, 268, 5), // "Pitch"
QT_MOC_LITERAL(24, 274, 3), // "Yaw"
QT_MOC_LITERAL(25, 278, 6), // "Thrust"
QT_MOC_LITERAL(26, 285, 10), // "UpdateTime"
QT_MOC_LITERAL(27, 296, 14) // "NumLongUpdates"

    },
    "ActuatorDesired\0RollChanged\0\0value\0"
    "PitchChanged\0YawChanged\0ThrustChanged\0"
    "UpdateTimeChanged\0NumLongUpdatesChanged\0"
    "setRoll\0setPitch\0setYaw\0setThrust\0"
    "setUpdateTime\0setNumLongUpdates\0"
    "emitNotifications\0getRoll\0getPitch\0"
    "getYaw\0getThrust\0getUpdateTime\0"
    "getNumLongUpdates\0Roll\0Pitch\0Yaw\0"
    "Thrust\0UpdateTime\0NumLongUpdates"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ActuatorDesired[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       6,  152, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x06 /* Public */,
       4,    1,  112,    2, 0x06 /* Public */,
       5,    1,  115,    2, 0x06 /* Public */,
       6,    1,  118,    2, 0x06 /* Public */,
       7,    1,  121,    2, 0x06 /* Public */,
       8,    1,  124,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,  127,    2, 0x0a /* Public */,
      10,    1,  130,    2, 0x0a /* Public */,
      11,    1,  133,    2, 0x0a /* Public */,
      12,    1,  136,    2, 0x0a /* Public */,
      13,    1,  139,    2, 0x0a /* Public */,
      14,    1,  142,    2, 0x0a /* Public */,
      15,    0,  145,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      16,    0,  146,    2, 0x02 /* Public */,
      17,    0,  147,    2, 0x02 /* Public */,
      18,    0,  148,    2, 0x02 /* Public */,
      19,    0,  149,    2, 0x02 /* Public */,
      20,    0,  150,    2, 0x02 /* Public */,
      21,    0,  151,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,

 // properties: name, type, flags
      22, QMetaType::Float, 0x00495103,
      23, QMetaType::Float, 0x00495103,
      24, QMetaType::Float, 0x00495103,
      25, QMetaType::Float, 0x00495103,
      26, QMetaType::Float, 0x00495103,
      27, QMetaType::Float, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,

       0        // eod
};

void ActuatorDesired::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ActuatorDesired *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->RollChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->PitchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->YawChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->ThrustChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->UpdateTimeChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->NumLongUpdatesChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->setRoll((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->setPitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->setYaw((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->setThrust((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->setUpdateTime((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->setNumLongUpdates((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->emitNotifications(); break;
        case 13: { float _r = _t->getRoll();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 14: { float _r = _t->getPitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 15: { float _r = _t->getYaw();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 16: { float _r = _t->getThrust();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 17: { float _r = _t->getUpdateTime();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 18: { float _r = _t->getNumLongUpdates();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ActuatorDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorDesired::RollChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ActuatorDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorDesired::PitchChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ActuatorDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorDesired::YawChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ActuatorDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorDesired::ThrustChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ActuatorDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorDesired::UpdateTimeChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ActuatorDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActuatorDesired::NumLongUpdatesChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ActuatorDesired *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getRoll(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getPitch(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getYaw(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getThrust(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getUpdateTime(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getNumLongUpdates(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ActuatorDesired *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setRoll(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setPitch(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setYaw(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setThrust(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setUpdateTime(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setNumLongUpdates(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ActuatorDesired::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_ActuatorDesired.data,
    qt_meta_data_ActuatorDesired,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ActuatorDesired::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ActuatorDesired::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ActuatorDesired.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int ActuatorDesired::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ActuatorDesired::RollChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ActuatorDesired::PitchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ActuatorDesired::YawChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ActuatorDesired::ThrustChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ActuatorDesired::UpdateTimeChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ActuatorDesired::NumLongUpdatesChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
