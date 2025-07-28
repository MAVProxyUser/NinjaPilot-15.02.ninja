/****************************************************************************
** Meta object code from reading C++ file 'multitask.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../multitask.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'multitask.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtConcurrent__MultiTaskBase_t {
    QByteArrayData data[10];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtConcurrent__MultiTaskBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtConcurrent__MultiTaskBase_t qt_meta_stringdata_QtConcurrent__MultiTaskBase = {
    {
QT_MOC_LITERAL(0, 0, 27), // "QtConcurrent::MultiTaskBase"
QT_MOC_LITERAL(1, 28, 10), // "cancelSelf"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 11), // "setFinished"
QT_MOC_LITERAL(4, 52, 16), // "setProgressRange"
QT_MOC_LITERAL(5, 69, 3), // "min"
QT_MOC_LITERAL(6, 73, 3), // "max"
QT_MOC_LITERAL(7, 77, 16), // "setProgressValue"
QT_MOC_LITERAL(8, 94, 5), // "value"
QT_MOC_LITERAL(9, 100, 15) // "setProgressText"

    },
    "QtConcurrent::MultiTaskBase\0cancelSelf\0"
    "\0setFinished\0setProgressRange\0min\0max\0"
    "setProgressValue\0value\0setProgressText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtConcurrent__MultiTaskBase[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x09 /* Protected */,
       3,    0,   40,    2, 0x09 /* Protected */,
       4,    2,   41,    2, 0x09 /* Protected */,
       7,    1,   46,    2, 0x09 /* Protected */,
       9,    1,   49,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void QtConcurrent::MultiTaskBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MultiTaskBase *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->cancelSelf(); break;
        case 1: _t->setFinished(); break;
        case 2: _t->setProgressRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setProgressValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setProgressText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtConcurrent::MultiTaskBase::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QtConcurrent__MultiTaskBase.data,
    qt_meta_data_QtConcurrent__MultiTaskBase,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtConcurrent::MultiTaskBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtConcurrent::MultiTaskBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtConcurrent__MultiTaskBase.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(this);
    return QObject::qt_metacast(_clname);
}

int QtConcurrent::MultiTaskBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
