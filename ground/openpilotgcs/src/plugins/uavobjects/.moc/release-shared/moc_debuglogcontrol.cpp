/****************************************************************************
** Meta object code from reading C++ file 'debuglogcontrol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/debuglogcontrol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'debuglogcontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DebugLogControl_t {
    QByteArrayData data[16];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DebugLogControl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DebugLogControl_t qt_meta_stringdata_DebugLogControl = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DebugLogControl"
QT_MOC_LITERAL(1, 16, 13), // "FlightChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 5), // "value"
QT_MOC_LITERAL(4, 37, 12), // "EntryChanged"
QT_MOC_LITERAL(5, 50, 16), // "OperationChanged"
QT_MOC_LITERAL(6, 67, 9), // "setFlight"
QT_MOC_LITERAL(7, 77, 8), // "setEntry"
QT_MOC_LITERAL(8, 86, 12), // "setOperation"
QT_MOC_LITERAL(9, 99, 17), // "emitNotifications"
QT_MOC_LITERAL(10, 117, 9), // "getFlight"
QT_MOC_LITERAL(11, 127, 8), // "getEntry"
QT_MOC_LITERAL(12, 136, 12), // "getOperation"
QT_MOC_LITERAL(13, 149, 6), // "Flight"
QT_MOC_LITERAL(14, 156, 5), // "Entry"
QT_MOC_LITERAL(15, 162, 9) // "Operation"

    },
    "DebugLogControl\0FlightChanged\0\0value\0"
    "EntryChanged\0OperationChanged\0setFlight\0"
    "setEntry\0setOperation\0emitNotifications\0"
    "getFlight\0getEntry\0getOperation\0Flight\0"
    "Entry\0Operation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DebugLogControl[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       3,   86, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       5,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   73,    2, 0x0a /* Public */,
       7,    1,   76,    2, 0x0a /* Public */,
       8,    1,   79,    2, 0x0a /* Public */,
       9,    0,   82,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      10,    0,   83,    2, 0x02 /* Public */,
      11,    0,   84,    2, 0x02 /* Public */,
      12,    0,   85,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UChar,

 // properties: name, type, flags
      13, QMetaType::UShort, 0x00495103,
      14, QMetaType::UShort, 0x00495103,
      15, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void DebugLogControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DebugLogControl *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->FlightChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 1: _t->EntryChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 2: _t->OperationChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 3: _t->setFlight((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 4: _t->setEntry((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 5: _t->setOperation((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 6: _t->emitNotifications(); break;
        case 7: { quint16 _r = _t->getFlight();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 8: { quint16 _r = _t->getEntry();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 9: { quint8 _r = _t->getOperation();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DebugLogControl::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DebugLogControl::FlightChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DebugLogControl::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DebugLogControl::EntryChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DebugLogControl::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DebugLogControl::OperationChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<DebugLogControl *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint16*>(_v) = _t->getFlight(); break;
        case 1: *reinterpret_cast< quint16*>(_v) = _t->getEntry(); break;
        case 2: *reinterpret_cast< quint8*>(_v) = _t->getOperation(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<DebugLogControl *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setFlight(*reinterpret_cast< quint16*>(_v)); break;
        case 1: _t->setEntry(*reinterpret_cast< quint16*>(_v)); break;
        case 2: _t->setOperation(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject DebugLogControl::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_DebugLogControl.data,
    qt_meta_data_DebugLogControl,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DebugLogControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DebugLogControl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DebugLogControl.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int DebugLogControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DebugLogControl::FlightChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DebugLogControl::EntryChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DebugLogControl::OperationChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
