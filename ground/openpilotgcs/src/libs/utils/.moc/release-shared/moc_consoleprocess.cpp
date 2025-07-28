/****************************************************************************
** Meta object code from reading C++ file 'consoleprocess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../consoleprocess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'consoleprocess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Utils__ConsoleProcess_t {
    QByteArrayData data[11];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Utils__ConsoleProcess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Utils__ConsoleProcess_t qt_meta_stringdata_Utils__ConsoleProcess = {
    {
QT_MOC_LITERAL(0, 0, 21), // "Utils::ConsoleProcess"
QT_MOC_LITERAL(1, 22, 12), // "processError"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "error"
QT_MOC_LITERAL(4, 42, 14), // "processStarted"
QT_MOC_LITERAL(5, 57, 14), // "processStopped"
QT_MOC_LITERAL(6, 72, 14), // "wrapperStarted"
QT_MOC_LITERAL(7, 87, 14), // "wrapperStopped"
QT_MOC_LITERAL(8, 102, 23), // "stubConnectionAvailable"
QT_MOC_LITERAL(9, 126, 14), // "readStubOutput"
QT_MOC_LITERAL(10, 141, 10) // "stubExited"

    },
    "Utils::ConsoleProcess\0processError\0\0"
    "error\0processStarted\0processStopped\0"
    "wrapperStarted\0wrapperStopped\0"
    "stubConnectionAvailable\0readStubOutput\0"
    "stubExited"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Utils__ConsoleProcess[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,
       5,    0,   58,    2, 0x06 /* Public */,
       6,    0,   59,    2, 0x06 /* Public */,
       7,    0,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   61,    2, 0x08 /* Private */,
       9,    0,   62,    2, 0x08 /* Private */,
      10,    0,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Utils::ConsoleProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConsoleProcess *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->processError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->processStarted(); break;
        case 2: _t->processStopped(); break;
        case 3: _t->wrapperStarted(); break;
        case 4: _t->wrapperStopped(); break;
        case 5: _t->stubConnectionAvailable(); break;
        case 6: _t->readStubOutput(); break;
        case 7: _t->stubExited(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConsoleProcess::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConsoleProcess::processError)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConsoleProcess::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConsoleProcess::processStarted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ConsoleProcess::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConsoleProcess::processStopped)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ConsoleProcess::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConsoleProcess::wrapperStarted)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ConsoleProcess::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConsoleProcess::wrapperStopped)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Utils::ConsoleProcess::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Utils__ConsoleProcess.data,
    qt_meta_data_Utils__ConsoleProcess,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Utils::ConsoleProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Utils::ConsoleProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Utils__ConsoleProcess.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "AbstractProcess"))
        return static_cast< AbstractProcess*>(this);
    return QObject::qt_metacast(_clname);
}

int Utils::ConsoleProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Utils::ConsoleProcess::processError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Utils::ConsoleProcess::processStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Utils::ConsoleProcess::processStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Utils::ConsoleProcess::wrapperStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Utils::ConsoleProcess::wrapperStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
