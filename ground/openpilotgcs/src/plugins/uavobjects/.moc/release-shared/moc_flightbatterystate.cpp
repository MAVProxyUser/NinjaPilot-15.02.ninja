/****************************************************************************
** Meta object code from reading C++ file 'flightbatterystate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/flightbatterystate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flightbatterystate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FlightBatteryState_t {
    QByteArrayData data[40];
    char stringdata0[645];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlightBatteryState_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlightBatteryState_t qt_meta_stringdata_FlightBatteryState = {
    {
QT_MOC_LITERAL(0, 0, 18), // "FlightBatteryState"
QT_MOC_LITERAL(1, 19, 14), // "VoltageChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "value"
QT_MOC_LITERAL(4, 41, 14), // "CurrentChanged"
QT_MOC_LITERAL(5, 56, 25), // "BoardSupplyVoltageChanged"
QT_MOC_LITERAL(6, 82, 18), // "PeakCurrentChanged"
QT_MOC_LITERAL(7, 101, 17), // "AvgCurrentChanged"
QT_MOC_LITERAL(8, 119, 21), // "ConsumedEnergyChanged"
QT_MOC_LITERAL(9, 141, 26), // "EstimatedFlightTimeChanged"
QT_MOC_LITERAL(10, 168, 14), // "NbCellsChanged"
QT_MOC_LITERAL(11, 183, 26), // "NbCellsAutodetectedChanged"
QT_MOC_LITERAL(12, 210, 10), // "setVoltage"
QT_MOC_LITERAL(13, 221, 10), // "setCurrent"
QT_MOC_LITERAL(14, 232, 21), // "setBoardSupplyVoltage"
QT_MOC_LITERAL(15, 254, 14), // "setPeakCurrent"
QT_MOC_LITERAL(16, 269, 13), // "setAvgCurrent"
QT_MOC_LITERAL(17, 283, 17), // "setConsumedEnergy"
QT_MOC_LITERAL(18, 301, 22), // "setEstimatedFlightTime"
QT_MOC_LITERAL(19, 324, 10), // "setNbCells"
QT_MOC_LITERAL(20, 335, 22), // "setNbCellsAutodetected"
QT_MOC_LITERAL(21, 358, 17), // "emitNotifications"
QT_MOC_LITERAL(22, 376, 10), // "getVoltage"
QT_MOC_LITERAL(23, 387, 10), // "getCurrent"
QT_MOC_LITERAL(24, 398, 21), // "getBoardSupplyVoltage"
QT_MOC_LITERAL(25, 420, 14), // "getPeakCurrent"
QT_MOC_LITERAL(26, 435, 13), // "getAvgCurrent"
QT_MOC_LITERAL(27, 449, 17), // "getConsumedEnergy"
QT_MOC_LITERAL(28, 467, 22), // "getEstimatedFlightTime"
QT_MOC_LITERAL(29, 490, 10), // "getNbCells"
QT_MOC_LITERAL(30, 501, 22), // "getNbCellsAutodetected"
QT_MOC_LITERAL(31, 524, 7), // "Voltage"
QT_MOC_LITERAL(32, 532, 7), // "Current"
QT_MOC_LITERAL(33, 540, 18), // "BoardSupplyVoltage"
QT_MOC_LITERAL(34, 559, 11), // "PeakCurrent"
QT_MOC_LITERAL(35, 571, 10), // "AvgCurrent"
QT_MOC_LITERAL(36, 582, 14), // "ConsumedEnergy"
QT_MOC_LITERAL(37, 597, 19), // "EstimatedFlightTime"
QT_MOC_LITERAL(38, 617, 7), // "NbCells"
QT_MOC_LITERAL(39, 625, 19) // "NbCellsAutodetected"

    },
    "FlightBatteryState\0VoltageChanged\0\0"
    "value\0CurrentChanged\0BoardSupplyVoltageChanged\0"
    "PeakCurrentChanged\0AvgCurrentChanged\0"
    "ConsumedEnergyChanged\0EstimatedFlightTimeChanged\0"
    "NbCellsChanged\0NbCellsAutodetectedChanged\0"
    "setVoltage\0setCurrent\0setBoardSupplyVoltage\0"
    "setPeakCurrent\0setAvgCurrent\0"
    "setConsumedEnergy\0setEstimatedFlightTime\0"
    "setNbCells\0setNbCellsAutodetected\0"
    "emitNotifications\0getVoltage\0getCurrent\0"
    "getBoardSupplyVoltage\0getPeakCurrent\0"
    "getAvgCurrent\0getConsumedEnergy\0"
    "getEstimatedFlightTime\0getNbCells\0"
    "getNbCellsAutodetected\0Voltage\0Current\0"
    "BoardSupplyVoltage\0PeakCurrent\0"
    "AvgCurrent\0ConsumedEnergy\0EstimatedFlightTime\0"
    "NbCells\0NbCellsAutodetected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlightBatteryState[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       9,  218, // properties
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
       8,    1,  169,    2, 0x06 /* Public */,
       9,    1,  172,    2, 0x06 /* Public */,
      10,    1,  175,    2, 0x06 /* Public */,
      11,    1,  178,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,  181,    2, 0x0a /* Public */,
      13,    1,  184,    2, 0x0a /* Public */,
      14,    1,  187,    2, 0x0a /* Public */,
      15,    1,  190,    2, 0x0a /* Public */,
      16,    1,  193,    2, 0x0a /* Public */,
      17,    1,  196,    2, 0x0a /* Public */,
      18,    1,  199,    2, 0x0a /* Public */,
      19,    1,  202,    2, 0x0a /* Public */,
      20,    1,  205,    2, 0x0a /* Public */,
      21,    0,  208,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      22,    0,  209,    2, 0x02 /* Public */,
      23,    0,  210,    2, 0x02 /* Public */,
      24,    0,  211,    2, 0x02 /* Public */,
      25,    0,  212,    2, 0x02 /* Public */,
      26,    0,  213,    2, 0x02 /* Public */,
      27,    0,  214,    2, 0x02 /* Public */,
      28,    0,  215,    2, 0x02 /* Public */,
      29,    0,  216,    2, 0x02 /* Public */,
      30,    0,  217,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
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
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      31, QMetaType::Float, 0x00495103,
      32, QMetaType::Float, 0x00495103,
      33, QMetaType::Float, 0x00495103,
      34, QMetaType::Float, 0x00495103,
      35, QMetaType::Float, 0x00495103,
      36, QMetaType::Float, 0x00495103,
      37, QMetaType::Float, 0x00495103,
      38, QMetaType::UChar, 0x00495103,
      39, QMetaType::UChar, 0x00495103,

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

       0        // eod
};

void FlightBatteryState::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FlightBatteryState *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->VoltageChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->CurrentChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->BoardSupplyVoltageChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->PeakCurrentChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->AvgCurrentChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->ConsumedEnergyChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->EstimatedFlightTimeChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->NbCellsChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 8: _t->NbCellsAutodetectedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 9: _t->setVoltage((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->setCurrent((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->setBoardSupplyVoltage((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->setPeakCurrent((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->setAvgCurrent((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->setConsumedEnergy((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->setEstimatedFlightTime((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->setNbCells((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->setNbCellsAutodetected((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 18: _t->emitNotifications(); break;
        case 19: { float _r = _t->getVoltage();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 20: { float _r = _t->getCurrent();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 21: { float _r = _t->getBoardSupplyVoltage();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 22: { float _r = _t->getPeakCurrent();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 23: { float _r = _t->getAvgCurrent();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 24: { float _r = _t->getConsumedEnergy();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 25: { float _r = _t->getEstimatedFlightTime();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 26: { quint8 _r = _t->getNbCells();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 27: { quint8 _r = _t->getNbCellsAutodetected();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FlightBatteryState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightBatteryState::VoltageChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FlightBatteryState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightBatteryState::CurrentChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FlightBatteryState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightBatteryState::BoardSupplyVoltageChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FlightBatteryState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightBatteryState::PeakCurrentChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FlightBatteryState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightBatteryState::AvgCurrentChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FlightBatteryState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightBatteryState::ConsumedEnergyChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (FlightBatteryState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightBatteryState::EstimatedFlightTimeChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (FlightBatteryState::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightBatteryState::NbCellsChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (FlightBatteryState::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightBatteryState::NbCellsAutodetectedChanged)) {
                *result = 8;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FlightBatteryState *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getVoltage(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getCurrent(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getBoardSupplyVoltage(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getPeakCurrent(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getAvgCurrent(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getConsumedEnergy(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getEstimatedFlightTime(); break;
        case 7: *reinterpret_cast< quint8*>(_v) = _t->getNbCells(); break;
        case 8: *reinterpret_cast< quint8*>(_v) = _t->getNbCellsAutodetected(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<FlightBatteryState *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setVoltage(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setCurrent(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setBoardSupplyVoltage(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setPeakCurrent(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setAvgCurrent(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setConsumedEnergy(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setEstimatedFlightTime(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setNbCells(*reinterpret_cast< quint8*>(_v)); break;
        case 8: _t->setNbCellsAutodetected(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject FlightBatteryState::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_FlightBatteryState.data,
    qt_meta_data_FlightBatteryState,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FlightBatteryState::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlightBatteryState::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlightBatteryState.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int FlightBatteryState::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FlightBatteryState::VoltageChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FlightBatteryState::CurrentChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FlightBatteryState::BoardSupplyVoltageChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FlightBatteryState::PeakCurrentChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FlightBatteryState::AvgCurrentChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FlightBatteryState::ConsumedEnergyChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void FlightBatteryState::EstimatedFlightTimeChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void FlightBatteryState::NbCellsChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void FlightBatteryState::NbCellsAutodetectedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
