/****************************************************************************
** Meta object code from reading C++ file 'perfcounter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/perfcounter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'perfcounter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PerfCounter_t {
    QByteArrayData data[24];
    char stringdata0[296];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PerfCounter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PerfCounter_t qt_meta_stringdata_PerfCounter = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PerfCounter"
QT_MOC_LITERAL(1, 12, 9), // "IdChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "value"
QT_MOC_LITERAL(4, 29, 14), // "CounterChanged"
QT_MOC_LITERAL(5, 44, 5), // "index"
QT_MOC_LITERAL(6, 50, 20), // "Counter_ValueChanged"
QT_MOC_LITERAL(7, 71, 18), // "Counter_MinChanged"
QT_MOC_LITERAL(8, 90, 18), // "Counter_MaxChanged"
QT_MOC_LITERAL(9, 109, 5), // "setId"
QT_MOC_LITERAL(10, 115, 10), // "setCounter"
QT_MOC_LITERAL(11, 126, 16), // "setCounter_Value"
QT_MOC_LITERAL(12, 143, 14), // "setCounter_Min"
QT_MOC_LITERAL(13, 158, 14), // "setCounter_Max"
QT_MOC_LITERAL(14, 173, 17), // "emitNotifications"
QT_MOC_LITERAL(15, 191, 5), // "getId"
QT_MOC_LITERAL(16, 197, 10), // "getCounter"
QT_MOC_LITERAL(17, 208, 16), // "getCounter_Value"
QT_MOC_LITERAL(18, 225, 14), // "getCounter_Min"
QT_MOC_LITERAL(19, 240, 14), // "getCounter_Max"
QT_MOC_LITERAL(20, 255, 2), // "Id"
QT_MOC_LITERAL(21, 258, 13), // "Counter_Value"
QT_MOC_LITERAL(22, 272, 11), // "Counter_Min"
QT_MOC_LITERAL(23, 284, 11) // "Counter_Max"

    },
    "PerfCounter\0IdChanged\0\0value\0"
    "CounterChanged\0index\0Counter_ValueChanged\0"
    "Counter_MinChanged\0Counter_MaxChanged\0"
    "setId\0setCounter\0setCounter_Value\0"
    "setCounter_Min\0setCounter_Max\0"
    "emitNotifications\0getId\0getCounter\0"
    "getCounter_Value\0getCounter_Min\0"
    "getCounter_Max\0Id\0Counter_Value\0"
    "Counter_Min\0Counter_Max"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PerfCounter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       4,  136, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    2,   97,    2, 0x06 /* Public */,
       6,    1,  102,    2, 0x06 /* Public */,
       7,    1,  105,    2, 0x06 /* Public */,
       8,    1,  108,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,  111,    2, 0x0a /* Public */,
      10,    2,  114,    2, 0x0a /* Public */,
      11,    1,  119,    2, 0x0a /* Public */,
      12,    1,  122,    2, 0x0a /* Public */,
      13,    1,  125,    2, 0x0a /* Public */,
      14,    0,  128,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      15,    0,  129,    2, 0x02 /* Public */,
      16,    1,  130,    2, 0x02 /* Public */,
      17,    0,  133,    2, 0x02 /* Public */,
      18,    0,  134,    2, 0x02 /* Public */,
      19,    0,  135,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Int,    5,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Int,    5,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::UInt,
    QMetaType::Int, QMetaType::UInt,    5,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,

 // properties: name, type, flags
      20, QMetaType::UInt, 0x00495103,
      21, QMetaType::Int, 0x00495103,
      22, QMetaType::Int, 0x00495103,
      23, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       2,
       3,
       4,

       0        // eod
};

void PerfCounter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PerfCounter *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->IdChanged((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 1: _t->CounterChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 2: _t->Counter_ValueChanged((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 3: _t->Counter_MinChanged((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 4: _t->Counter_MaxChanged((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 5: _t->setId((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 6: _t->setCounter((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 7: _t->setCounter_Value((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 8: _t->setCounter_Min((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 9: _t->setCounter_Max((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 10: _t->emitNotifications(); break;
        case 11: { quint32 _r = _t->getId();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 12: { qint32 _r = _t->getCounter((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint32*>(_a[0]) = std::move(_r); }  break;
        case 13: { qint32 _r = _t->getCounter_Value();
            if (_a[0]) *reinterpret_cast< qint32*>(_a[0]) = std::move(_r); }  break;
        case 14: { qint32 _r = _t->getCounter_Min();
            if (_a[0]) *reinterpret_cast< qint32*>(_a[0]) = std::move(_r); }  break;
        case 15: { qint32 _r = _t->getCounter_Max();
            if (_a[0]) *reinterpret_cast< qint32*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PerfCounter::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PerfCounter::IdChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PerfCounter::*)(quint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PerfCounter::CounterChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PerfCounter::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PerfCounter::Counter_ValueChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PerfCounter::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PerfCounter::Counter_MinChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PerfCounter::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PerfCounter::Counter_MaxChanged)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PerfCounter *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint32*>(_v) = _t->getId(); break;
        case 1: *reinterpret_cast< qint32*>(_v) = _t->getCounter_Value(); break;
        case 2: *reinterpret_cast< qint32*>(_v) = _t->getCounter_Min(); break;
        case 3: *reinterpret_cast< qint32*>(_v) = _t->getCounter_Max(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PerfCounter *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setId(*reinterpret_cast< quint32*>(_v)); break;
        case 1: _t->setCounter_Value(*reinterpret_cast< qint32*>(_v)); break;
        case 2: _t->setCounter_Min(*reinterpret_cast< qint32*>(_v)); break;
        case 3: _t->setCounter_Max(*reinterpret_cast< qint32*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject PerfCounter::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_PerfCounter.data,
    qt_meta_data_PerfCounter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PerfCounter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PerfCounter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PerfCounter.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int PerfCounter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
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
void PerfCounter::IdChanged(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PerfCounter::CounterChanged(quint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PerfCounter::Counter_ValueChanged(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PerfCounter::Counter_MinChanged(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PerfCounter::Counter_MaxChanged(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
