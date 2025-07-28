/****************************************************************************
** Meta object code from reading C++ file 'logfile.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../logfile.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logfile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LogFile_t {
    QByteArrayData data[10];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LogFile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LogFile_t qt_meta_stringdata_LogFile = {
    {
QT_MOC_LITERAL(0, 0, 7), // "LogFile"
QT_MOC_LITERAL(1, 8, 9), // "readReady"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 13), // "replayStarted"
QT_MOC_LITERAL(4, 33, 14), // "replayFinished"
QT_MOC_LITERAL(5, 48, 14), // "setReplaySpeed"
QT_MOC_LITERAL(6, 63, 3), // "val"
QT_MOC_LITERAL(7, 67, 11), // "pauseReplay"
QT_MOC_LITERAL(8, 79, 12), // "resumeReplay"
QT_MOC_LITERAL(9, 92, 10) // "timerFired"

    },
    "LogFile\0readReady\0\0replayStarted\0"
    "replayFinished\0setReplaySpeed\0val\0"
    "pauseReplay\0resumeReplay\0timerFired"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LogFile[] = {

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
       4,    0,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   52,    2, 0x0a /* Public */,
       7,    0,   55,    2, 0x0a /* Public */,
       8,    0,   56,    2, 0x0a /* Public */,
       9,    0,   57,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LogFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LogFile *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->readReady(); break;
        case 1: _t->replayStarted(); break;
        case 2: _t->replayFinished(); break;
        case 3: _t->setReplaySpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->pauseReplay(); break;
        case 5: _t->resumeReplay(); break;
        case 6: _t->timerFired(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LogFile::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LogFile::readReady)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LogFile::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LogFile::replayStarted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LogFile::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LogFile::replayFinished)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LogFile::staticMetaObject = { {
    QMetaObject::SuperData::link<QIODevice::staticMetaObject>(),
    qt_meta_stringdata_LogFile.data,
    qt_meta_data_LogFile,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LogFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LogFile::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LogFile.stringdata0))
        return static_cast<void*>(this);
    return QIODevice::qt_metacast(_clname);
}

int LogFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QIODevice::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void LogFile::readReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LogFile::replayStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LogFile::replayFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
