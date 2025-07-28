/****************************************************************************
** Meta object code from reading C++ file 'auxmagsensor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/auxmagsensor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'auxmagsensor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AuxMagSensor_t {
    QByteArrayData data[20];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AuxMagSensor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AuxMagSensor_t qt_meta_stringdata_AuxMagSensor = {
    {
QT_MOC_LITERAL(0, 0, 12), // "AuxMagSensor"
QT_MOC_LITERAL(1, 13, 8), // "xChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "value"
QT_MOC_LITERAL(4, 29, 8), // "yChanged"
QT_MOC_LITERAL(5, 38, 8), // "zChanged"
QT_MOC_LITERAL(6, 47, 13), // "StatusChanged"
QT_MOC_LITERAL(7, 61, 4), // "setx"
QT_MOC_LITERAL(8, 66, 4), // "sety"
QT_MOC_LITERAL(9, 71, 4), // "setz"
QT_MOC_LITERAL(10, 76, 9), // "setStatus"
QT_MOC_LITERAL(11, 86, 17), // "emitNotifications"
QT_MOC_LITERAL(12, 104, 4), // "getx"
QT_MOC_LITERAL(13, 109, 4), // "gety"
QT_MOC_LITERAL(14, 114, 4), // "getz"
QT_MOC_LITERAL(15, 119, 9), // "getStatus"
QT_MOC_LITERAL(16, 129, 1), // "x"
QT_MOC_LITERAL(17, 131, 1), // "y"
QT_MOC_LITERAL(18, 133, 1), // "z"
QT_MOC_LITERAL(19, 135, 6) // "Status"

    },
    "AuxMagSensor\0xChanged\0\0value\0yChanged\0"
    "zChanged\0StatusChanged\0setx\0sety\0setz\0"
    "setStatus\0emitNotifications\0getx\0gety\0"
    "getz\0getStatus\0x\0y\0z\0Status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuxMagSensor[] = {

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
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar,

 // properties: name, type, flags
      16, QMetaType::Float, 0x00495003,
      17, QMetaType::Float, 0x00495003,
      18, QMetaType::Float, 0x00495003,
      19, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void AuxMagSensor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AuxMagSensor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->xChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->yChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->zChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->StatusChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 4: _t->setx((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->sety((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->setz((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->setStatus((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 8: _t->emitNotifications(); break;
        case 9: { float _r = _t->getx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 10: { float _r = _t->gety();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 11: { float _r = _t->getz();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 12: { quint8 _r = _t->getStatus();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AuxMagSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSensor::xChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AuxMagSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSensor::yChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AuxMagSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSensor::zChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AuxMagSensor::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSensor::StatusChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AuxMagSensor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getx(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->gety(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getz(); break;
        case 3: *reinterpret_cast< quint8*>(_v) = _t->getStatus(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<AuxMagSensor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setx(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->sety(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setz(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setStatus(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject AuxMagSensor::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_AuxMagSensor.data,
    qt_meta_data_AuxMagSensor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AuxMagSensor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuxMagSensor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AuxMagSensor.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int AuxMagSensor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void AuxMagSensor::xChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AuxMagSensor::yChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AuxMagSensor::zChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AuxMagSensor::StatusChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
