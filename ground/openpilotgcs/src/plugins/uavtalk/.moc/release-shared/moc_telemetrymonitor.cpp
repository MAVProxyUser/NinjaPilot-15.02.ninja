/****************************************************************************
** Meta object code from reading C++ file 'telemetrymonitor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../telemetrymonitor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'telemetrymonitor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TelemetryMonitor_t {
    QByteArrayData data[14];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TelemetryMonitor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TelemetryMonitor_t qt_meta_stringdata_TelemetryMonitor = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TelemetryMonitor"
QT_MOC_LITERAL(1, 17, 9), // "connected"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "disconnected"
QT_MOC_LITERAL(4, 41, 16), // "telemetryUpdated"
QT_MOC_LITERAL(5, 58, 6), // "txRate"
QT_MOC_LITERAL(6, 65, 6), // "rxRate"
QT_MOC_LITERAL(7, 72, 20), // "transactionCompleted"
QT_MOC_LITERAL(8, 93, 10), // "UAVObject*"
QT_MOC_LITERAL(9, 104, 3), // "obj"
QT_MOC_LITERAL(10, 108, 7), // "success"
QT_MOC_LITERAL(11, 116, 19), // "processStatsUpdates"
QT_MOC_LITERAL(12, 136, 18), // "flightStatsUpdated"
QT_MOC_LITERAL(13, 155, 18) // "firmwareIAPUpdated"

    },
    "TelemetryMonitor\0connected\0\0disconnected\0"
    "telemetryUpdated\0txRate\0rxRate\0"
    "transactionCompleted\0UAVObject*\0obj\0"
    "success\0processStatsUpdates\0"
    "flightStatsUpdated\0firmwareIAPUpdated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TelemetryMonitor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    2,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   56,    2, 0x0a /* Public */,
      11,    0,   61,    2, 0x0a /* Public */,
      12,    1,   62,    2, 0x0a /* Public */,
      13,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    5,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8, QMetaType::Bool,    9,   10,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void TelemetryMonitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TelemetryMonitor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->telemetryUpdated((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->transactionCompleted((*reinterpret_cast< UAVObject*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->processStatsUpdates(); break;
        case 5: _t->flightStatsUpdated((*reinterpret_cast< UAVObject*(*)>(_a[1]))); break;
        case 6: _t->firmwareIAPUpdated((*reinterpret_cast< UAVObject*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UAVObject* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UAVObject* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UAVObject* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TelemetryMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelemetryMonitor::connected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TelemetryMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelemetryMonitor::disconnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TelemetryMonitor::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelemetryMonitor::telemetryUpdated)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TelemetryMonitor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TelemetryMonitor.data,
    qt_meta_data_TelemetryMonitor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TelemetryMonitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TelemetryMonitor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TelemetryMonitor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TelemetryMonitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TelemetryMonitor::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TelemetryMonitor::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TelemetryMonitor::telemetryUpdated(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
