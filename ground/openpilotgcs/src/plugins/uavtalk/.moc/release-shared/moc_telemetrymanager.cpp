/****************************************************************************
** Meta object code from reading C++ file 'telemetrymanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../telemetrymanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'telemetrymanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TelemetryManager_t {
    QByteArrayData data[16];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TelemetryManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TelemetryManager_t qt_meta_stringdata_TelemetryManager = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TelemetryManager"
QT_MOC_LITERAL(1, 17, 10), // "connecting"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 9), // "connected"
QT_MOC_LITERAL(4, 39, 13), // "disconnecting"
QT_MOC_LITERAL(5, 53, 12), // "disconnected"
QT_MOC_LITERAL(6, 66, 16), // "telemetryUpdated"
QT_MOC_LITERAL(7, 83, 6), // "txRate"
QT_MOC_LITERAL(8, 90, 6), // "rxRate"
QT_MOC_LITERAL(9, 97, 7), // "myStart"
QT_MOC_LITERAL(10, 105, 6), // "myStop"
QT_MOC_LITERAL(11, 112, 9), // "onConnect"
QT_MOC_LITERAL(12, 122, 12), // "onDisconnect"
QT_MOC_LITERAL(13, 135, 17), // "onTelemetryUpdate"
QT_MOC_LITERAL(14, 153, 7), // "onStart"
QT_MOC_LITERAL(15, 161, 6) // "onStop"

    },
    "TelemetryManager\0connecting\0\0connected\0"
    "disconnecting\0disconnected\0telemetryUpdated\0"
    "txRate\0rxRate\0myStart\0myStop\0onConnect\0"
    "onDisconnect\0onTelemetryUpdate\0onStart\0"
    "onStop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TelemetryManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,
       5,    0,   77,    2, 0x06 /* Public */,
       6,    2,   78,    2, 0x06 /* Public */,
       9,    0,   83,    2, 0x06 /* Public */,
      10,    0,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   85,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    2,   87,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    7,    8,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    7,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TelemetryManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TelemetryManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connecting(); break;
        case 1: _t->connected(); break;
        case 2: _t->disconnecting(); break;
        case 3: _t->disconnected(); break;
        case 4: _t->telemetryUpdated((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 5: _t->myStart(); break;
        case 6: _t->myStop(); break;
        case 7: _t->onConnect(); break;
        case 8: _t->onDisconnect(); break;
        case 9: _t->onTelemetryUpdate((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 10: _t->onStart(); break;
        case 11: _t->onStop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TelemetryManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelemetryManager::connecting)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TelemetryManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelemetryManager::connected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TelemetryManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelemetryManager::disconnecting)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TelemetryManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelemetryManager::disconnected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TelemetryManager::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelemetryManager::telemetryUpdated)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TelemetryManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelemetryManager::myStart)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TelemetryManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TelemetryManager::myStop)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TelemetryManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TelemetryManager.data,
    qt_meta_data_TelemetryManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TelemetryManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TelemetryManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TelemetryManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TelemetryManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void TelemetryManager::connecting()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TelemetryManager::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TelemetryManager::disconnecting()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TelemetryManager::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void TelemetryManager::telemetryUpdated(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TelemetryManager::myStart()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void TelemetryManager::myStop()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
struct qt_meta_stringdata_IODeviceReader_t {
    QByteArrayData data[3];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IODeviceReader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IODeviceReader_t qt_meta_stringdata_IODeviceReader = {
    {
QT_MOC_LITERAL(0, 0, 14), // "IODeviceReader"
QT_MOC_LITERAL(1, 15, 4), // "read"
QT_MOC_LITERAL(2, 20, 0) // ""

    },
    "IODeviceReader\0read\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IODeviceReader[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void IODeviceReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IODeviceReader *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->read(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject IODeviceReader::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_IODeviceReader.data,
    qt_meta_data_IODeviceReader,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IODeviceReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IODeviceReader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IODeviceReader.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IODeviceReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
