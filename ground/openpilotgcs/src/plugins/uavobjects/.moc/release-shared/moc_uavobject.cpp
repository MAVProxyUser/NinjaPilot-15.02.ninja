/****************************************************************************
** Meta object code from reading C++ file 'uavobject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../uavobject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uavobject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UAVObject_t {
    QByteArrayData data[24];
    char stringdata0[289];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UAVObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UAVObject_t qt_meta_stringdata_UAVObject = {
    {
QT_MOC_LITERAL(0, 0, 9), // "UAVObject"
QT_MOC_LITERAL(1, 10, 13), // "objectUpdated"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 10), // "UAVObject*"
QT_MOC_LITERAL(4, 36, 3), // "obj"
QT_MOC_LITERAL(5, 40, 17), // "objectUpdatedAuto"
QT_MOC_LITERAL(6, 58, 19), // "objectUpdatedManual"
QT_MOC_LITERAL(7, 78, 3), // "all"
QT_MOC_LITERAL(8, 82, 21), // "objectUpdatedPeriodic"
QT_MOC_LITERAL(9, 104, 14), // "objectUnpacked"
QT_MOC_LITERAL(10, 119, 15), // "updateRequested"
QT_MOC_LITERAL(11, 135, 20), // "transactionCompleted"
QT_MOC_LITERAL(12, 156, 7), // "success"
QT_MOC_LITERAL(13, 164, 11), // "newInstance"
QT_MOC_LITERAL(14, 176, 14), // "isKnownChanged"
QT_MOC_LITERAL(15, 191, 7), // "isKnown"
QT_MOC_LITERAL(16, 199, 13), // "requestUpdate"
QT_MOC_LITERAL(17, 213, 16), // "requestUpdateAll"
QT_MOC_LITERAL(18, 230, 7), // "updated"
QT_MOC_LITERAL(19, 238, 10), // "updatedAll"
QT_MOC_LITERAL(20, 249, 12), // "fieldUpdated"
QT_MOC_LITERAL(21, 262, 15), // "UAVObjectField*"
QT_MOC_LITERAL(22, 278, 5), // "field"
QT_MOC_LITERAL(23, 284, 4) // "Name"

    },
    "UAVObject\0objectUpdated\0\0UAVObject*\0"
    "obj\0objectUpdatedAuto\0objectUpdatedManual\0"
    "all\0objectUpdatedPeriodic\0objectUnpacked\0"
    "updateRequested\0transactionCompleted\0"
    "success\0newInstance\0isKnownChanged\0"
    "isKnown\0requestUpdate\0requestUpdateAll\0"
    "updated\0updatedAll\0fieldUpdated\0"
    "UAVObjectField*\0field\0Name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UAVObject[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       1,  142, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       5,    1,   97,    2, 0x06 /* Public */,
       6,    2,  100,    2, 0x06 /* Public */,
       6,    1,  105,    2, 0x26 /* Public | MethodCloned */,
       8,    1,  108,    2, 0x06 /* Public */,
       9,    1,  111,    2, 0x06 /* Public */,
      10,    2,  114,    2, 0x06 /* Public */,
      10,    1,  119,    2, 0x26 /* Public | MethodCloned */,
      11,    2,  122,    2, 0x06 /* Public */,
      13,    1,  127,    2, 0x06 /* Public */,
      14,    2,  130,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,  135,    2, 0x0a /* Public */,
      17,    0,  136,    2, 0x0a /* Public */,
      18,    0,  137,    2, 0x0a /* Public */,
      19,    0,  138,    2, 0x0a /* Public */,
      20,    1,  139,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    7,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    7,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,   12,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,   15,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   22,

 // properties: name, type, flags
      23, QMetaType::QString, 0x00095001,

       0        // eod
};

void UAVObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UAVObject *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->objectUpdated((*reinterpret_cast< UAVObject*(*)>(_a[1]))); break;
        case 1: _t->objectUpdatedAuto((*reinterpret_cast< UAVObject*(*)>(_a[1]))); break;
        case 2: _t->objectUpdatedManual((*reinterpret_cast< UAVObject*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->objectUpdatedManual((*reinterpret_cast< UAVObject*(*)>(_a[1]))); break;
        case 4: _t->objectUpdatedPeriodic((*reinterpret_cast< UAVObject*(*)>(_a[1]))); break;
        case 5: _t->objectUnpacked((*reinterpret_cast< UAVObject*(*)>(_a[1]))); break;
        case 6: _t->updateRequested((*reinterpret_cast< UAVObject*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->updateRequested((*reinterpret_cast< UAVObject*(*)>(_a[1]))); break;
        case 8: _t->transactionCompleted((*reinterpret_cast< UAVObject*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 9: _t->newInstance((*reinterpret_cast< UAVObject*(*)>(_a[1]))); break;
        case 10: _t->isKnownChanged((*reinterpret_cast< UAVObject*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 11: _t->requestUpdate(); break;
        case 12: _t->requestUpdateAll(); break;
        case 13: _t->updated(); break;
        case 14: _t->updatedAll(); break;
        case 15: _t->fieldUpdated((*reinterpret_cast< UAVObjectField*(*)>(_a[1]))); break;
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
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UAVObject* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UAVObject* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UAVObject* >(); break;
            }
            break;
        case 4:
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
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UAVObject* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UAVObject* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UAVObject* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UAVObject* >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UAVObjectField* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UAVObject::*)(UAVObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVObject::objectUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UAVObject::*)(UAVObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVObject::objectUpdatedAuto)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UAVObject::*)(UAVObject * , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVObject::objectUpdatedManual)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UAVObject::*)(UAVObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVObject::objectUpdatedPeriodic)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (UAVObject::*)(UAVObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVObject::objectUnpacked)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (UAVObject::*)(UAVObject * , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVObject::updateRequested)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (UAVObject::*)(UAVObject * , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVObject::transactionCompleted)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (UAVObject::*)(UAVObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVObject::newInstance)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (UAVObject::*)(UAVObject * , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVObject::isKnownChanged)) {
                *result = 10;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<UAVObject *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getName(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject UAVObject::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_UAVObject.data,
    qt_meta_data_UAVObject,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UAVObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UAVObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UAVObject.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UAVObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void UAVObject::objectUpdated(UAVObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UAVObject::objectUpdatedAuto(UAVObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UAVObject::objectUpdatedManual(UAVObject * _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void UAVObject::objectUpdatedPeriodic(UAVObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void UAVObject::objectUnpacked(UAVObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void UAVObject::updateRequested(UAVObject * _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 8
void UAVObject::transactionCompleted(UAVObject * _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void UAVObject::newInstance(UAVObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void UAVObject::isKnownChanged(UAVObject * _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
