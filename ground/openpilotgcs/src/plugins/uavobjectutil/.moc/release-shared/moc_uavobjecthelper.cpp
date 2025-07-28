/****************************************************************************
** Meta object code from reading C++ file 'uavobjecthelper.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../uavobjecthelper.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uavobjecthelper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AbstractUAVObjectHelper_t {
    QByteArrayData data[6];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AbstractUAVObjectHelper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AbstractUAVObjectHelper_t qt_meta_stringdata_AbstractUAVObjectHelper = {
    {
QT_MOC_LITERAL(0, 0, 23), // "AbstractUAVObjectHelper"
QT_MOC_LITERAL(1, 24, 20), // "transactionCompleted"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 10), // "UAVObject*"
QT_MOC_LITERAL(4, 57, 6), // "object"
QT_MOC_LITERAL(5, 64, 7) // "success"

    },
    "AbstractUAVObjectHelper\0transactionCompleted\0"
    "\0UAVObject*\0object\0success"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AbstractUAVObjectHelper[] = {

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
       1,    2,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    5,

       0        // eod
};

void AbstractUAVObjectHelper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AbstractUAVObjectHelper *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->transactionCompleted((*reinterpret_cast< UAVObject*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UAVObject* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AbstractUAVObjectHelper::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AbstractUAVObjectHelper.data,
    qt_meta_data_AbstractUAVObjectHelper,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AbstractUAVObjectHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbstractUAVObjectHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractUAVObjectHelper.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AbstractUAVObjectHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_UAVObjectUpdaterHelper_t {
    QByteArrayData data[1];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UAVObjectUpdaterHelper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UAVObjectUpdaterHelper_t qt_meta_stringdata_UAVObjectUpdaterHelper = {
    {
QT_MOC_LITERAL(0, 0, 22) // "UAVObjectUpdaterHelper"

    },
    "UAVObjectUpdaterHelper"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UAVObjectUpdaterHelper[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void UAVObjectUpdaterHelper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject UAVObjectUpdaterHelper::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractUAVObjectHelper::staticMetaObject>(),
    qt_meta_stringdata_UAVObjectUpdaterHelper.data,
    qt_meta_data_UAVObjectUpdaterHelper,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UAVObjectUpdaterHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UAVObjectUpdaterHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UAVObjectUpdaterHelper.stringdata0))
        return static_cast<void*>(this);
    return AbstractUAVObjectHelper::qt_metacast(_clname);
}

int UAVObjectUpdaterHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractUAVObjectHelper::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_UAVObjectRequestHelper_t {
    QByteArrayData data[1];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UAVObjectRequestHelper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UAVObjectRequestHelper_t qt_meta_stringdata_UAVObjectRequestHelper = {
    {
QT_MOC_LITERAL(0, 0, 22) // "UAVObjectRequestHelper"

    },
    "UAVObjectRequestHelper"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UAVObjectRequestHelper[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void UAVObjectRequestHelper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject UAVObjectRequestHelper::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractUAVObjectHelper::staticMetaObject>(),
    qt_meta_stringdata_UAVObjectRequestHelper.data,
    qt_meta_data_UAVObjectRequestHelper,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UAVObjectRequestHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UAVObjectRequestHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UAVObjectRequestHelper.stringdata0))
        return static_cast<void*>(this);
    return AbstractUAVObjectHelper::qt_metacast(_clname);
}

int UAVObjectRequestHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractUAVObjectHelper::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
