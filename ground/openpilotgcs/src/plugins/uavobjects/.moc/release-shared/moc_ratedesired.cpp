/****************************************************************************
** Meta object code from reading C++ file 'ratedesired.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/ratedesired.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ratedesired.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RateDesired_t {
    QByteArrayData data[20];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RateDesired_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RateDesired_t qt_meta_stringdata_RateDesired = {
    {
QT_MOC_LITERAL(0, 0, 11), // "RateDesired"
QT_MOC_LITERAL(1, 12, 11), // "RollChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "value"
QT_MOC_LITERAL(4, 31, 12), // "PitchChanged"
QT_MOC_LITERAL(5, 44, 10), // "YawChanged"
QT_MOC_LITERAL(6, 55, 13), // "ThrustChanged"
QT_MOC_LITERAL(7, 69, 7), // "setRoll"
QT_MOC_LITERAL(8, 77, 8), // "setPitch"
QT_MOC_LITERAL(9, 86, 6), // "setYaw"
QT_MOC_LITERAL(10, 93, 9), // "setThrust"
QT_MOC_LITERAL(11, 103, 17), // "emitNotifications"
QT_MOC_LITERAL(12, 121, 7), // "getRoll"
QT_MOC_LITERAL(13, 129, 8), // "getPitch"
QT_MOC_LITERAL(14, 138, 6), // "getYaw"
QT_MOC_LITERAL(15, 145, 9), // "getThrust"
QT_MOC_LITERAL(16, 155, 4), // "Roll"
QT_MOC_LITERAL(17, 160, 5), // "Pitch"
QT_MOC_LITERAL(18, 166, 3), // "Yaw"
QT_MOC_LITERAL(19, 170, 6) // "Thrust"

    },
    "RateDesired\0RollChanged\0\0value\0"
    "PitchChanged\0YawChanged\0ThrustChanged\0"
    "setRoll\0setPitch\0setYaw\0setThrust\0"
    "emitNotifications\0getRoll\0getPitch\0"
    "getYaw\0getThrust\0Roll\0Pitch\0Yaw\0Thrust"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RateDesired[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       4,  108, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       5,    1,   85,    2, 0x06 /* Public */,
       6,    1,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   91,    2, 0x0a /* Public */,
       8,    1,   94,    2, 0x0a /* Public */,
       9,    1,   97,    2, 0x0a /* Public */,
      10,    1,  100,    2, 0x0a /* Public */,
      11,    0,  103,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      12,    0,  104,    2, 0x02 /* Public */,
      13,    0,  105,    2, 0x02 /* Public */,
      14,    0,  106,    2, 0x02 /* Public */,
      15,    0,  107,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,

 // slots: parameters
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

 // properties: name, type, flags
      16, QMetaType::Float, 0x00495103,
      17, QMetaType::Float, 0x00495103,
      18, QMetaType::Float, 0x00495103,
      19, QMetaType::Float, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void RateDesired::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RateDesired *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->RollChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->PitchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->YawChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->ThrustChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->setRoll((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->setPitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->setYaw((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->setThrust((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->emitNotifications(); break;
        case 9: { float _r = _t->getRoll();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 10: { float _r = _t->getPitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 11: { float _r = _t->getYaw();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 12: { float _r = _t->getThrust();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RateDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RateDesired::RollChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RateDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RateDesired::PitchChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RateDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RateDesired::YawChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (RateDesired::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RateDesired::ThrustChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<RateDesired *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getRoll(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getPitch(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getYaw(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getThrust(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<RateDesired *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setRoll(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setPitch(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setYaw(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setThrust(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject RateDesired::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_RateDesired.data,
    qt_meta_data_RateDesired,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RateDesired::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RateDesired::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RateDesired.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int RateDesired::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void RateDesired::RollChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RateDesired::PitchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RateDesired::YawChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RateDesired::ThrustChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
