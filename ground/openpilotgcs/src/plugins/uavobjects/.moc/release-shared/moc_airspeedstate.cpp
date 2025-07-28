/****************************************************************************
** Meta object code from reading C++ file 'airspeedstate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/airspeedstate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'airspeedstate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AirspeedState_t {
    QByteArrayData data[12];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AirspeedState_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AirspeedState_t qt_meta_stringdata_AirspeedState = {
    {
QT_MOC_LITERAL(0, 0, 13), // "AirspeedState"
QT_MOC_LITERAL(1, 14, 25), // "CalibratedAirspeedChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 5), // "value"
QT_MOC_LITERAL(4, 47, 19), // "TrueAirspeedChanged"
QT_MOC_LITERAL(5, 67, 21), // "setCalibratedAirspeed"
QT_MOC_LITERAL(6, 89, 15), // "setTrueAirspeed"
QT_MOC_LITERAL(7, 105, 17), // "emitNotifications"
QT_MOC_LITERAL(8, 123, 21), // "getCalibratedAirspeed"
QT_MOC_LITERAL(9, 145, 15), // "getTrueAirspeed"
QT_MOC_LITERAL(10, 161, 18), // "CalibratedAirspeed"
QT_MOC_LITERAL(11, 180, 12) // "TrueAirspeed"

    },
    "AirspeedState\0CalibratedAirspeedChanged\0"
    "\0value\0TrueAirspeedChanged\0"
    "setCalibratedAirspeed\0setTrueAirspeed\0"
    "emitNotifications\0getCalibratedAirspeed\0"
    "getTrueAirspeed\0CalibratedAirspeed\0"
    "TrueAirspeed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AirspeedState[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       2,   64, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   55,    2, 0x0a /* Public */,
       6,    1,   58,    2, 0x0a /* Public */,
       7,    0,   61,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
       8,    0,   62,    2, 0x02 /* Public */,
       9,    0,   63,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float,
    QMetaType::Float,

 // properties: name, type, flags
      10, QMetaType::Float, 0x00495103,
      11, QMetaType::Float, 0x00495103,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void AirspeedState::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AirspeedState *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->CalibratedAirspeedChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->TrueAirspeedChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->setCalibratedAirspeed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->setTrueAirspeed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->emitNotifications(); break;
        case 5: { float _r = _t->getCalibratedAirspeed();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 6: { float _r = _t->getTrueAirspeed();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AirspeedState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AirspeedState::CalibratedAirspeedChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AirspeedState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AirspeedState::TrueAirspeedChanged)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AirspeedState *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getCalibratedAirspeed(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getTrueAirspeed(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<AirspeedState *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCalibratedAirspeed(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setTrueAirspeed(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject AirspeedState::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_AirspeedState.data,
    qt_meta_data_AirspeedState,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AirspeedState::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AirspeedState::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AirspeedState.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int AirspeedState::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AirspeedState::CalibratedAirspeedChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AirspeedState::TrueAirspeedChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
