/****************************************************************************
** Meta object code from reading C++ file 'ophid_usbmon.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../inc/ophid_usbmon.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ophid_usbmon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_USBMonitor_t {
    QByteArrayData data[7];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_USBMonitor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_USBMonitor_t qt_meta_stringdata_USBMonitor = {
    {
QT_MOC_LITERAL(0, 0, 10), // "USBMonitor"
QT_MOC_LITERAL(1, 11, 16), // "deviceDiscovered"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "USBPortInfo"
QT_MOC_LITERAL(4, 41, 4), // "info"
QT_MOC_LITERAL(5, 46, 13), // "deviceRemoved"
QT_MOC_LITERAL(6, 60, 19) // "deviceEventReceived"

    },
    "USBMonitor\0deviceDiscovered\0\0USBPortInfo\0"
    "info\0deviceRemoved\0deviceEventReceived"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_USBMonitor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       1,    0,   42,    2, 0x06 /* Public */,
       5,    1,   43,    2, 0x06 /* Public */,
       5,    0,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void USBMonitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<USBMonitor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->deviceDiscovered((*reinterpret_cast< const USBPortInfo(*)>(_a[1]))); break;
        case 1: _t->deviceDiscovered(); break;
        case 2: _t->deviceRemoved((*reinterpret_cast< const USBPortInfo(*)>(_a[1]))); break;
        case 3: _t->deviceRemoved(); break;
        case 4: _t->deviceEventReceived(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (USBMonitor::*)(const USBPortInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&USBMonitor::deviceDiscovered)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (USBMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&USBMonitor::deviceDiscovered)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (USBMonitor::*)(const USBPortInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&USBMonitor::deviceRemoved)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (USBMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&USBMonitor::deviceRemoved)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject USBMonitor::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_USBMonitor.data,
    qt_meta_data_USBMonitor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *USBMonitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *USBMonitor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_USBMonitor.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int USBMonitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void USBMonitor::deviceDiscovered(const USBPortInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void USBMonitor::deviceDiscovered()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void USBMonitor::deviceRemoved(const USBPortInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void USBMonitor::deviceRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
