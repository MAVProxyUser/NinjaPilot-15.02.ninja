/****************************************************************************
** Meta object code from reading C++ file 'synchronousprocess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../synchronousprocess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'synchronousprocess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Utils__SynchronousProcess_t {
    QByteArrayData data[17];
    char stringdata0[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Utils__SynchronousProcess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Utils__SynchronousProcess_t qt_meta_stringdata_Utils__SynchronousProcess = {
    {
QT_MOC_LITERAL(0, 0, 25), // "Utils::SynchronousProcess"
QT_MOC_LITERAL(1, 26, 6), // "stdOut"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 4), // "data"
QT_MOC_LITERAL(4, 39, 9), // "firstTime"
QT_MOC_LITERAL(5, 49, 6), // "stdErr"
QT_MOC_LITERAL(6, 56, 14), // "stdOutBuffered"
QT_MOC_LITERAL(7, 71, 14), // "stdErrBuffered"
QT_MOC_LITERAL(8, 86, 11), // "slotTimeout"
QT_MOC_LITERAL(9, 98, 8), // "finished"
QT_MOC_LITERAL(10, 107, 8), // "exitCode"
QT_MOC_LITERAL(11, 116, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(12, 137, 1), // "e"
QT_MOC_LITERAL(13, 139, 5), // "error"
QT_MOC_LITERAL(14, 145, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(15, 168, 11), // "stdOutReady"
QT_MOC_LITERAL(16, 180, 11) // "stdErrReady"

    },
    "Utils::SynchronousProcess\0stdOut\0\0"
    "data\0firstTime\0stdErr\0stdOutBuffered\0"
    "stdErrBuffered\0slotTimeout\0finished\0"
    "exitCode\0QProcess::ExitStatus\0e\0error\0"
    "QProcess::ProcessError\0stdOutReady\0"
    "stdErrReady"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Utils__SynchronousProcess[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       5,    2,   64,    2, 0x06 /* Public */,
       6,    2,   69,    2, 0x06 /* Public */,
       7,    2,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   79,    2, 0x08 /* Private */,
       9,    2,   80,    2, 0x08 /* Private */,
      13,    1,   85,    2, 0x08 /* Private */,
      15,    0,   88,    2, 0x08 /* Private */,
      16,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,   10,   12,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Utils::SynchronousProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SynchronousProcess *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->stdOut((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->stdErr((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->stdOutBuffered((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->stdErrBuffered((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->slotTimeout(); break;
        case 5: _t->finished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 6: _t->error((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 7: _t->stdOutReady(); break;
        case 8: _t->stdErrReady(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SynchronousProcess::*)(const QByteArray & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SynchronousProcess::stdOut)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SynchronousProcess::*)(const QByteArray & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SynchronousProcess::stdErr)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SynchronousProcess::*)(const QString & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SynchronousProcess::stdOutBuffered)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SynchronousProcess::*)(const QString & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SynchronousProcess::stdErrBuffered)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Utils::SynchronousProcess::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Utils__SynchronousProcess.data,
    qt_meta_data_Utils__SynchronousProcess,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Utils::SynchronousProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Utils::SynchronousProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Utils__SynchronousProcess.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Utils::SynchronousProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Utils::SynchronousProcess::stdOut(const QByteArray & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Utils::SynchronousProcess::stdErr(const QByteArray & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Utils::SynchronousProcess::stdOutBuffered(const QString & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Utils::SynchronousProcess::stdErrBuffered(const QString & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
