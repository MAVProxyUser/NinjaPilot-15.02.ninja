/****************************************************************************
** Meta object code from reading C++ file 'airspeedsensor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/airspeedsensor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'airspeedsensor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AirspeedSensor_t {
    QByteArrayData data[32];
    char stringdata0[595];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AirspeedSensor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AirspeedSensor_t qt_meta_stringdata_AirspeedSensor = {
    {
QT_MOC_LITERAL(0, 0, 14), // "AirspeedSensor"
QT_MOC_LITERAL(1, 15, 27), // "DifferentialPressureChanged"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 5), // "value"
QT_MOC_LITERAL(4, 50, 18), // "TemperatureChanged"
QT_MOC_LITERAL(5, 69, 25), // "CalibratedAirspeedChanged"
QT_MOC_LITERAL(6, 95, 19), // "TrueAirspeedChanged"
QT_MOC_LITERAL(7, 115, 18), // "SensorValueChanged"
QT_MOC_LITERAL(8, 134, 29), // "SensorValueTemperatureChanged"
QT_MOC_LITERAL(9, 164, 22), // "SensorConnectedChanged"
QT_MOC_LITERAL(10, 187, 23), // "setDifferentialPressure"
QT_MOC_LITERAL(11, 211, 14), // "setTemperature"
QT_MOC_LITERAL(12, 226, 21), // "setCalibratedAirspeed"
QT_MOC_LITERAL(13, 248, 15), // "setTrueAirspeed"
QT_MOC_LITERAL(14, 264, 14), // "setSensorValue"
QT_MOC_LITERAL(15, 279, 25), // "setSensorValueTemperature"
QT_MOC_LITERAL(16, 305, 18), // "setSensorConnected"
QT_MOC_LITERAL(17, 324, 17), // "emitNotifications"
QT_MOC_LITERAL(18, 342, 23), // "getDifferentialPressure"
QT_MOC_LITERAL(19, 366, 14), // "getTemperature"
QT_MOC_LITERAL(20, 381, 21), // "getCalibratedAirspeed"
QT_MOC_LITERAL(21, 403, 15), // "getTrueAirspeed"
QT_MOC_LITERAL(22, 419, 14), // "getSensorValue"
QT_MOC_LITERAL(23, 434, 25), // "getSensorValueTemperature"
QT_MOC_LITERAL(24, 460, 18), // "getSensorConnected"
QT_MOC_LITERAL(25, 479, 20), // "DifferentialPressure"
QT_MOC_LITERAL(26, 500, 11), // "Temperature"
QT_MOC_LITERAL(27, 512, 18), // "CalibratedAirspeed"
QT_MOC_LITERAL(28, 531, 12), // "TrueAirspeed"
QT_MOC_LITERAL(29, 544, 11), // "SensorValue"
QT_MOC_LITERAL(30, 556, 22), // "SensorValueTemperature"
QT_MOC_LITERAL(31, 579, 15) // "SensorConnected"

    },
    "AirspeedSensor\0DifferentialPressureChanged\0"
    "\0value\0TemperatureChanged\0"
    "CalibratedAirspeedChanged\0TrueAirspeedChanged\0"
    "SensorValueChanged\0SensorValueTemperatureChanged\0"
    "SensorConnectedChanged\0setDifferentialPressure\0"
    "setTemperature\0setCalibratedAirspeed\0"
    "setTrueAirspeed\0setSensorValue\0"
    "setSensorValueTemperature\0setSensorConnected\0"
    "emitNotifications\0getDifferentialPressure\0"
    "getTemperature\0getCalibratedAirspeed\0"
    "getTrueAirspeed\0getSensorValue\0"
    "getSensorValueTemperature\0getSensorConnected\0"
    "DifferentialPressure\0Temperature\0"
    "CalibratedAirspeed\0TrueAirspeed\0"
    "SensorValue\0SensorValueTemperature\0"
    "SensorConnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AirspeedSensor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       7,  174, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  124,    2, 0x06 /* Public */,
       4,    1,  127,    2, 0x06 /* Public */,
       5,    1,  130,    2, 0x06 /* Public */,
       6,    1,  133,    2, 0x06 /* Public */,
       7,    1,  136,    2, 0x06 /* Public */,
       8,    1,  139,    2, 0x06 /* Public */,
       9,    1,  142,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,  145,    2, 0x0a /* Public */,
      11,    1,  148,    2, 0x0a /* Public */,
      12,    1,  151,    2, 0x0a /* Public */,
      13,    1,  154,    2, 0x0a /* Public */,
      14,    1,  157,    2, 0x0a /* Public */,
      15,    1,  160,    2, 0x0a /* Public */,
      16,    1,  163,    2, 0x0a /* Public */,
      17,    0,  166,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      18,    0,  167,    2, 0x02 /* Public */,
      19,    0,  168,    2, 0x02 /* Public */,
      20,    0,  169,    2, 0x02 /* Public */,
      21,    0,  170,    2, 0x02 /* Public */,
      22,    0,  171,    2, 0x02 /* Public */,
      23,    0,  172,    2, 0x02 /* Public */,
      24,    0,  173,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UChar,

 // properties: name, type, flags
      25, QMetaType::Float, 0x00495103,
      26, QMetaType::Float, 0x00495103,
      27, QMetaType::Float, 0x00495103,
      28, QMetaType::Float, 0x00495103,
      29, QMetaType::UShort, 0x00495103,
      30, QMetaType::UShort, 0x00495103,
      31, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,

       0        // eod
};

void AirspeedSensor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AirspeedSensor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->DifferentialPressureChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->TemperatureChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->CalibratedAirspeedChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->TrueAirspeedChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->SensorValueChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 5: _t->SensorValueTemperatureChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 6: _t->SensorConnectedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 7: _t->setDifferentialPressure((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->setTemperature((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->setCalibratedAirspeed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->setTrueAirspeed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->setSensorValue((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 12: _t->setSensorValueTemperature((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 13: _t->setSensorConnected((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->emitNotifications(); break;
        case 15: { float _r = _t->getDifferentialPressure();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 16: { float _r = _t->getTemperature();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 17: { float _r = _t->getCalibratedAirspeed();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 18: { float _r = _t->getTrueAirspeed();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 19: { quint16 _r = _t->getSensorValue();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 20: { quint16 _r = _t->getSensorValueTemperature();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 21: { quint8 _r = _t->getSensorConnected();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AirspeedSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AirspeedSensor::DifferentialPressureChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AirspeedSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AirspeedSensor::TemperatureChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AirspeedSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AirspeedSensor::CalibratedAirspeedChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AirspeedSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AirspeedSensor::TrueAirspeedChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AirspeedSensor::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AirspeedSensor::SensorValueChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AirspeedSensor::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AirspeedSensor::SensorValueTemperatureChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (AirspeedSensor::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AirspeedSensor::SensorConnectedChanged)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AirspeedSensor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getDifferentialPressure(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getTemperature(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getCalibratedAirspeed(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getTrueAirspeed(); break;
        case 4: *reinterpret_cast< quint16*>(_v) = _t->getSensorValue(); break;
        case 5: *reinterpret_cast< quint16*>(_v) = _t->getSensorValueTemperature(); break;
        case 6: *reinterpret_cast< quint8*>(_v) = _t->getSensorConnected(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<AirspeedSensor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDifferentialPressure(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setTemperature(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setCalibratedAirspeed(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setTrueAirspeed(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setSensorValue(*reinterpret_cast< quint16*>(_v)); break;
        case 5: _t->setSensorValueTemperature(*reinterpret_cast< quint16*>(_v)); break;
        case 6: _t->setSensorConnected(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject AirspeedSensor::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_AirspeedSensor.data,
    qt_meta_data_AirspeedSensor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AirspeedSensor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AirspeedSensor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AirspeedSensor.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int AirspeedSensor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AirspeedSensor::DifferentialPressureChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AirspeedSensor::TemperatureChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AirspeedSensor::CalibratedAirspeedChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AirspeedSensor::TrueAirspeedChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AirspeedSensor::SensorValueChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AirspeedSensor::SensorValueTemperatureChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AirspeedSensor::SensorConnectedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
