/****************************************************************************
** Meta object code from reading C++ file 'takeofflocation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/takeofflocation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'takeofflocation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TakeOffLocation_t {
    QByteArrayData data[24];
    char stringdata0[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TakeOffLocation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TakeOffLocation_t qt_meta_stringdata_TakeOffLocation = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TakeOffLocation"
QT_MOC_LITERAL(1, 16, 12), // "NorthChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "value"
QT_MOC_LITERAL(4, 36, 11), // "EastChanged"
QT_MOC_LITERAL(5, 48, 11), // "DownChanged"
QT_MOC_LITERAL(6, 60, 11), // "ModeChanged"
QT_MOC_LITERAL(7, 72, 13), // "StatusChanged"
QT_MOC_LITERAL(8, 86, 8), // "setNorth"
QT_MOC_LITERAL(9, 95, 7), // "setEast"
QT_MOC_LITERAL(10, 103, 7), // "setDown"
QT_MOC_LITERAL(11, 111, 7), // "setMode"
QT_MOC_LITERAL(12, 119, 9), // "setStatus"
QT_MOC_LITERAL(13, 129, 17), // "emitNotifications"
QT_MOC_LITERAL(14, 147, 8), // "getNorth"
QT_MOC_LITERAL(15, 156, 7), // "getEast"
QT_MOC_LITERAL(16, 164, 7), // "getDown"
QT_MOC_LITERAL(17, 172, 7), // "getMode"
QT_MOC_LITERAL(18, 180, 9), // "getStatus"
QT_MOC_LITERAL(19, 190, 5), // "North"
QT_MOC_LITERAL(20, 196, 4), // "East"
QT_MOC_LITERAL(21, 201, 4), // "Down"
QT_MOC_LITERAL(22, 206, 4), // "Mode"
QT_MOC_LITERAL(23, 211, 6) // "Status"

    },
    "TakeOffLocation\0NorthChanged\0\0value\0"
    "EastChanged\0DownChanged\0ModeChanged\0"
    "StatusChanged\0setNorth\0setEast\0setDown\0"
    "setMode\0setStatus\0emitNotifications\0"
    "getNorth\0getEast\0getDown\0getMode\0"
    "getStatus\0North\0East\0Down\0Mode\0Status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TakeOffLocation[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       5,  130, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       5,    1,  100,    2, 0x06 /* Public */,
       6,    1,  103,    2, 0x06 /* Public */,
       7,    1,  106,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,  109,    2, 0x0a /* Public */,
       9,    1,  112,    2, 0x0a /* Public */,
      10,    1,  115,    2, 0x0a /* Public */,
      11,    1,  118,    2, 0x0a /* Public */,
      12,    1,  121,    2, 0x0a /* Public */,
      13,    0,  124,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      14,    0,  125,    2, 0x02 /* Public */,
      15,    0,  126,    2, 0x02 /* Public */,
      16,    0,  127,    2, 0x02 /* Public */,
      17,    0,  128,    2, 0x02 /* Public */,
      18,    0,  129,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      19, QMetaType::Float, 0x00495103,
      20, QMetaType::Float, 0x00495103,
      21, QMetaType::Float, 0x00495103,
      22, QMetaType::UChar, 0x00495103,
      23, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,

       0        // eod
};

void TakeOffLocation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TakeOffLocation *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->NorthChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->EastChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->DownChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->ModeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 4: _t->StatusChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 5: _t->setNorth((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->setEast((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->setDown((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->setMode((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 9: _t->setStatus((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 10: _t->emitNotifications(); break;
        case 11: { float _r = _t->getNorth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 12: { float _r = _t->getEast();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 13: { float _r = _t->getDown();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 14: { quint8 _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 15: { quint8 _r = _t->getStatus();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TakeOffLocation::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TakeOffLocation::NorthChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TakeOffLocation::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TakeOffLocation::EastChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TakeOffLocation::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TakeOffLocation::DownChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TakeOffLocation::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TakeOffLocation::ModeChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TakeOffLocation::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TakeOffLocation::StatusChanged)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<TakeOffLocation *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getNorth(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getEast(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getDown(); break;
        case 3: *reinterpret_cast< quint8*>(_v) = _t->getMode(); break;
        case 4: *reinterpret_cast< quint8*>(_v) = _t->getStatus(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<TakeOffLocation *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setNorth(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setEast(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setDown(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setMode(*reinterpret_cast< quint8*>(_v)); break;
        case 4: _t->setStatus(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject TakeOffLocation::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_TakeOffLocation.data,
    qt_meta_data_TakeOffLocation,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TakeOffLocation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TakeOffLocation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TakeOffLocation.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int TakeOffLocation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void TakeOffLocation::NorthChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TakeOffLocation::EastChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TakeOffLocation::DownChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TakeOffLocation::ModeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TakeOffLocation::StatusChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
