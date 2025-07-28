/****************************************************************************
** Meta object code from reading C++ file 'debuglogstatus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/debuglogstatus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'debuglogstatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DebugLogStatus_t {
    QByteArrayData data[20];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DebugLogStatus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DebugLogStatus_t qt_meta_stringdata_DebugLogStatus = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DebugLogStatus"
QT_MOC_LITERAL(1, 15, 13), // "FlightChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "value"
QT_MOC_LITERAL(4, 36, 12), // "EntryChanged"
QT_MOC_LITERAL(5, 49, 16), // "UsedSlotsChanged"
QT_MOC_LITERAL(6, 66, 16), // "FreeSlotsChanged"
QT_MOC_LITERAL(7, 83, 9), // "setFlight"
QT_MOC_LITERAL(8, 93, 8), // "setEntry"
QT_MOC_LITERAL(9, 102, 12), // "setUsedSlots"
QT_MOC_LITERAL(10, 115, 12), // "setFreeSlots"
QT_MOC_LITERAL(11, 128, 17), // "emitNotifications"
QT_MOC_LITERAL(12, 146, 9), // "getFlight"
QT_MOC_LITERAL(13, 156, 8), // "getEntry"
QT_MOC_LITERAL(14, 165, 12), // "getUsedSlots"
QT_MOC_LITERAL(15, 178, 12), // "getFreeSlots"
QT_MOC_LITERAL(16, 191, 6), // "Flight"
QT_MOC_LITERAL(17, 198, 5), // "Entry"
QT_MOC_LITERAL(18, 204, 9), // "UsedSlots"
QT_MOC_LITERAL(19, 214, 9) // "FreeSlots"

    },
    "DebugLogStatus\0FlightChanged\0\0value\0"
    "EntryChanged\0UsedSlotsChanged\0"
    "FreeSlotsChanged\0setFlight\0setEntry\0"
    "setUsedSlots\0setFreeSlots\0emitNotifications\0"
    "getFlight\0getEntry\0getUsedSlots\0"
    "getFreeSlots\0Flight\0Entry\0UsedSlots\0"
    "FreeSlots"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DebugLogStatus[] = {

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
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,

 // properties: name, type, flags
      16, QMetaType::UShort, 0x00495103,
      17, QMetaType::UShort, 0x00495103,
      18, QMetaType::UShort, 0x00495103,
      19, QMetaType::UShort, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void DebugLogStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DebugLogStatus *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->FlightChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 1: _t->EntryChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 2: _t->UsedSlotsChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 3: _t->FreeSlotsChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 4: _t->setFlight((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 5: _t->setEntry((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 6: _t->setUsedSlots((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 7: _t->setFreeSlots((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 8: _t->emitNotifications(); break;
        case 9: { quint16 _r = _t->getFlight();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 10: { quint16 _r = _t->getEntry();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 11: { quint16 _r = _t->getUsedSlots();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 12: { quint16 _r = _t->getFreeSlots();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DebugLogStatus::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DebugLogStatus::FlightChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DebugLogStatus::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DebugLogStatus::EntryChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DebugLogStatus::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DebugLogStatus::UsedSlotsChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DebugLogStatus::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DebugLogStatus::FreeSlotsChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<DebugLogStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint16*>(_v) = _t->getFlight(); break;
        case 1: *reinterpret_cast< quint16*>(_v) = _t->getEntry(); break;
        case 2: *reinterpret_cast< quint16*>(_v) = _t->getUsedSlots(); break;
        case 3: *reinterpret_cast< quint16*>(_v) = _t->getFreeSlots(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<DebugLogStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setFlight(*reinterpret_cast< quint16*>(_v)); break;
        case 1: _t->setEntry(*reinterpret_cast< quint16*>(_v)); break;
        case 2: _t->setUsedSlots(*reinterpret_cast< quint16*>(_v)); break;
        case 3: _t->setFreeSlots(*reinterpret_cast< quint16*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject DebugLogStatus::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_DebugLogStatus.data,
    qt_meta_data_DebugLogStatus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DebugLogStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DebugLogStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DebugLogStatus.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int DebugLogStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void DebugLogStatus::FlightChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DebugLogStatus::EntryChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DebugLogStatus::UsedSlotsChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DebugLogStatus::FreeSlotsChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
