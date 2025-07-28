/****************************************************************************
** Meta object code from reading C++ file 'connectionmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../connectionmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connectionmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__ConnectionManager_t {
    QByteArrayData data[25];
    char stringdata0[398];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__ConnectionManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__ConnectionManager_t qt_meta_stringdata_Core__ConnectionManager = {
    {
QT_MOC_LITERAL(0, 0, 23), // "Core::ConnectionManager"
QT_MOC_LITERAL(1, 24, 15), // "deviceConnected"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 10), // "QIODevice*"
QT_MOC_LITERAL(4, 52, 6), // "device"
QT_MOC_LITERAL(5, 59, 23), // "deviceAboutToDisconnect"
QT_MOC_LITERAL(6, 83, 18), // "deviceDisconnected"
QT_MOC_LITERAL(7, 102, 23), // "availableDevicesChanged"
QT_MOC_LITERAL(8, 126, 28), // "std::list<Core::DevListItem>"
QT_MOC_LITERAL(9, 155, 7), // "devices"
QT_MOC_LITERAL(10, 163, 18), // "telemetryConnected"
QT_MOC_LITERAL(11, 182, 21), // "telemetryDisconnected"
QT_MOC_LITERAL(12, 204, 11), // "objectAdded"
QT_MOC_LITERAL(13, 216, 3), // "obj"
QT_MOC_LITERAL(14, 220, 19), // "aboutToRemoveObject"
QT_MOC_LITERAL(15, 240, 16), // "onConnectClicked"
QT_MOC_LITERAL(16, 257, 24), // "onDeviceSelectionChanged"
QT_MOC_LITERAL(17, 282, 5), // "index"
QT_MOC_LITERAL(18, 288, 10), // "devChanged"
QT_MOC_LITERAL(19, 299, 12), // "IConnection*"
QT_MOC_LITERAL(20, 312, 10), // "connection"
QT_MOC_LITERAL(21, 323, 21), // "onConnectionDestroyed"
QT_MOC_LITERAL(22, 345, 19), // "connectionsCallBack"
QT_MOC_LITERAL(23, 365, 13), // "reconnectSlot"
QT_MOC_LITERAL(24, 379, 18) // "reconnectCheckSlot"

    },
    "Core::ConnectionManager\0deviceConnected\0"
    "\0QIODevice*\0device\0deviceAboutToDisconnect\0"
    "deviceDisconnected\0availableDevicesChanged\0"
    "std::list<Core::DevListItem>\0devices\0"
    "telemetryConnected\0telemetryDisconnected\0"
    "objectAdded\0obj\0aboutToRemoveObject\0"
    "onConnectClicked\0onDeviceSelectionChanged\0"
    "index\0devChanged\0IConnection*\0connection\0"
    "onConnectionDestroyed\0connectionsCallBack\0"
    "reconnectSlot\0reconnectCheckSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__ConnectionManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       5,    0,   92,    2, 0x06 /* Public */,
       6,    0,   93,    2, 0x06 /* Public */,
       7,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   97,    2, 0x0a /* Public */,
      11,    0,   98,    2, 0x0a /* Public */,
      12,    1,   99,    2, 0x08 /* Private */,
      14,    1,  102,    2, 0x08 /* Private */,
      15,    0,  105,    2, 0x08 /* Private */,
      16,    1,  106,    2, 0x08 /* Private */,
      18,    1,  109,    2, 0x08 /* Private */,
      21,    1,  112,    2, 0x08 /* Private */,
      22,    0,  115,    2, 0x08 /* Private */,
      23,    0,  116,    2, 0x08 /* Private */,
      24,    0,  117,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QObjectStar,   13,
    QMetaType::Void, QMetaType::QObjectStar,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, QMetaType::QObjectStar,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Core::ConnectionManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConnectionManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->deviceConnected((*reinterpret_cast< QIODevice*(*)>(_a[1]))); break;
        case 1: _t->deviceAboutToDisconnect(); break;
        case 2: _t->deviceDisconnected(); break;
        case 3: _t->availableDevicesChanged((*reinterpret_cast< const std::list<Core::DevListItem>(*)>(_a[1]))); break;
        case 4: _t->telemetryConnected(); break;
        case 5: _t->telemetryDisconnected(); break;
        case 6: _t->objectAdded((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 7: _t->aboutToRemoveObject((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 8: _t->onConnectClicked(); break;
        case 9: _t->onDeviceSelectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->devChanged((*reinterpret_cast< IConnection*(*)>(_a[1]))); break;
        case 11: _t->onConnectionDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 12: _t->connectionsCallBack(); break;
        case 13: _t->reconnectSlot(); break;
        case 14: _t->reconnectCheckSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QIODevice* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IConnection* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConnectionManager::*)(QIODevice * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionManager::deviceConnected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConnectionManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionManager::deviceAboutToDisconnect)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ConnectionManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionManager::deviceDisconnected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ConnectionManager::*)(const std::list<Core::DevListItem> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionManager::availableDevicesChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::ConnectionManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Core__ConnectionManager.data,
    qt_meta_data_Core__ConnectionManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::ConnectionManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::ConnectionManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__ConnectionManager.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Core::ConnectionManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Core::ConnectionManager::deviceConnected(QIODevice * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Core::ConnectionManager::deviceAboutToDisconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Core::ConnectionManager::deviceDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Core::ConnectionManager::availableDevicesChanged(const std::list<Core::DevListItem> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
