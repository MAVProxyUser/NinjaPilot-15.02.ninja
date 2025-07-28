/****************************************************************************
** Meta object code from reading C++ file 'objectpersistence.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/objectpersistence.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectpersistence.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ObjectPersistence_t {
    QByteArrayData data[20];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ObjectPersistence_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ObjectPersistence_t qt_meta_stringdata_ObjectPersistence = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ObjectPersistence"
QT_MOC_LITERAL(1, 18, 15), // "ObjectIDChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "value"
QT_MOC_LITERAL(4, 41, 17), // "InstanceIDChanged"
QT_MOC_LITERAL(5, 59, 16), // "OperationChanged"
QT_MOC_LITERAL(6, 76, 16), // "SelectionChanged"
QT_MOC_LITERAL(7, 93, 11), // "setObjectID"
QT_MOC_LITERAL(8, 105, 13), // "setInstanceID"
QT_MOC_LITERAL(9, 119, 12), // "setOperation"
QT_MOC_LITERAL(10, 132, 12), // "setSelection"
QT_MOC_LITERAL(11, 145, 17), // "emitNotifications"
QT_MOC_LITERAL(12, 163, 11), // "getObjectID"
QT_MOC_LITERAL(13, 175, 13), // "getInstanceID"
QT_MOC_LITERAL(14, 189, 12), // "getOperation"
QT_MOC_LITERAL(15, 202, 12), // "getSelection"
QT_MOC_LITERAL(16, 215, 8), // "ObjectID"
QT_MOC_LITERAL(17, 224, 10), // "InstanceID"
QT_MOC_LITERAL(18, 235, 9), // "Operation"
QT_MOC_LITERAL(19, 245, 9) // "Selection"

    },
    "ObjectPersistence\0ObjectIDChanged\0\0"
    "value\0InstanceIDChanged\0OperationChanged\0"
    "SelectionChanged\0setObjectID\0setInstanceID\0"
    "setOperation\0setSelection\0emitNotifications\0"
    "getObjectID\0getInstanceID\0getOperation\0"
    "getSelection\0ObjectID\0InstanceID\0"
    "Operation\0Selection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ObjectPersistence[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       4,  108, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       5,    1,   85,    2, 0x06 /* Public */,
       6,    1,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   91,    2, 0x0a /* Public */,
       8,    1,   94,    2, 0x0a /* Public */,
       9,    1,   97,    2, 0x0a /* Public */,
      10,    1,  100,    2, 0x0a /* Public */,
      11,    0,  103,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      12,    0,  104,    2, 0x02 /* Public */,
      13,    0,  105,    2, 0x02 /* Public */,
      14,    0,  106,    2, 0x02 /* Public */,
      15,    0,  107,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      16, QMetaType::UInt, 0x00495103,
      17, QMetaType::UInt, 0x00495103,
      18, QMetaType::UChar, 0x00495103,
      19, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void ObjectPersistence::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ObjectPersistence *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ObjectIDChanged((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 1: _t->InstanceIDChanged((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 2: _t->OperationChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 3: _t->SelectionChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 4: _t->setObjectID((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 5: _t->setInstanceID((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 6: _t->setOperation((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 7: _t->setSelection((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 8: _t->emitNotifications(); break;
        case 9: { quint32 _r = _t->getObjectID();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 10: { quint32 _r = _t->getInstanceID();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 11: { quint8 _r = _t->getOperation();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 12: { quint8 _r = _t->getSelection();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ObjectPersistence::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ObjectPersistence::ObjectIDChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ObjectPersistence::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ObjectPersistence::InstanceIDChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ObjectPersistence::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ObjectPersistence::OperationChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ObjectPersistence::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ObjectPersistence::SelectionChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ObjectPersistence *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint32*>(_v) = _t->getObjectID(); break;
        case 1: *reinterpret_cast< quint32*>(_v) = _t->getInstanceID(); break;
        case 2: *reinterpret_cast< quint8*>(_v) = _t->getOperation(); break;
        case 3: *reinterpret_cast< quint8*>(_v) = _t->getSelection(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ObjectPersistence *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setObjectID(*reinterpret_cast< quint32*>(_v)); break;
        case 1: _t->setInstanceID(*reinterpret_cast< quint32*>(_v)); break;
        case 2: _t->setOperation(*reinterpret_cast< quint8*>(_v)); break;
        case 3: _t->setSelection(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ObjectPersistence::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_ObjectPersistence.data,
    qt_meta_data_ObjectPersistence,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ObjectPersistence::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ObjectPersistence::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ObjectPersistence.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int ObjectPersistence::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ObjectPersistence::ObjectIDChanged(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ObjectPersistence::InstanceIDChanged(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ObjectPersistence::OperationChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ObjectPersistence::SelectionChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
