/****************************************************************************
** Meta object code from reading C++ file 'stabilizationstatus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/stabilizationstatus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stabilizationstatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StabilizationStatus_t {
    QByteArrayData data[43];
    char stringdata0[737];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StabilizationStatus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StabilizationStatus_t qt_meta_stringdata_StabilizationStatus = {
    {
QT_MOC_LITERAL(0, 0, 19), // "StabilizationStatus"
QT_MOC_LITERAL(1, 20, 16), // "OuterLoopChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 5), // "index"
QT_MOC_LITERAL(4, 44, 5), // "value"
QT_MOC_LITERAL(5, 50, 21), // "OuterLoop_RollChanged"
QT_MOC_LITERAL(6, 72, 22), // "OuterLoop_PitchChanged"
QT_MOC_LITERAL(7, 95, 20), // "OuterLoop_YawChanged"
QT_MOC_LITERAL(8, 116, 23), // "OuterLoop_ThrustChanged"
QT_MOC_LITERAL(9, 140, 16), // "InnerLoopChanged"
QT_MOC_LITERAL(10, 157, 21), // "InnerLoop_RollChanged"
QT_MOC_LITERAL(11, 179, 22), // "InnerLoop_PitchChanged"
QT_MOC_LITERAL(12, 202, 20), // "InnerLoop_YawChanged"
QT_MOC_LITERAL(13, 223, 23), // "InnerLoop_ThrustChanged"
QT_MOC_LITERAL(14, 247, 12), // "setOuterLoop"
QT_MOC_LITERAL(15, 260, 17), // "setOuterLoop_Roll"
QT_MOC_LITERAL(16, 278, 18), // "setOuterLoop_Pitch"
QT_MOC_LITERAL(17, 297, 16), // "setOuterLoop_Yaw"
QT_MOC_LITERAL(18, 314, 19), // "setOuterLoop_Thrust"
QT_MOC_LITERAL(19, 334, 12), // "setInnerLoop"
QT_MOC_LITERAL(20, 347, 17), // "setInnerLoop_Roll"
QT_MOC_LITERAL(21, 365, 18), // "setInnerLoop_Pitch"
QT_MOC_LITERAL(22, 384, 16), // "setInnerLoop_Yaw"
QT_MOC_LITERAL(23, 401, 19), // "setInnerLoop_Thrust"
QT_MOC_LITERAL(24, 421, 17), // "emitNotifications"
QT_MOC_LITERAL(25, 439, 12), // "getOuterLoop"
QT_MOC_LITERAL(26, 452, 17), // "getOuterLoop_Roll"
QT_MOC_LITERAL(27, 470, 18), // "getOuterLoop_Pitch"
QT_MOC_LITERAL(28, 489, 16), // "getOuterLoop_Yaw"
QT_MOC_LITERAL(29, 506, 19), // "getOuterLoop_Thrust"
QT_MOC_LITERAL(30, 526, 12), // "getInnerLoop"
QT_MOC_LITERAL(31, 539, 17), // "getInnerLoop_Roll"
QT_MOC_LITERAL(32, 557, 18), // "getInnerLoop_Pitch"
QT_MOC_LITERAL(33, 576, 16), // "getInnerLoop_Yaw"
QT_MOC_LITERAL(34, 593, 19), // "getInnerLoop_Thrust"
QT_MOC_LITERAL(35, 613, 14), // "OuterLoop_Roll"
QT_MOC_LITERAL(36, 628, 15), // "OuterLoop_Pitch"
QT_MOC_LITERAL(37, 644, 13), // "OuterLoop_Yaw"
QT_MOC_LITERAL(38, 658, 16), // "OuterLoop_Thrust"
QT_MOC_LITERAL(39, 675, 14), // "InnerLoop_Roll"
QT_MOC_LITERAL(40, 690, 15), // "InnerLoop_Pitch"
QT_MOC_LITERAL(41, 706, 13), // "InnerLoop_Yaw"
QT_MOC_LITERAL(42, 720, 16) // "InnerLoop_Thrust"

    },
    "StabilizationStatus\0OuterLoopChanged\0"
    "\0index\0value\0OuterLoop_RollChanged\0"
    "OuterLoop_PitchChanged\0OuterLoop_YawChanged\0"
    "OuterLoop_ThrustChanged\0InnerLoopChanged\0"
    "InnerLoop_RollChanged\0InnerLoop_PitchChanged\0"
    "InnerLoop_YawChanged\0InnerLoop_ThrustChanged\0"
    "setOuterLoop\0setOuterLoop_Roll\0"
    "setOuterLoop_Pitch\0setOuterLoop_Yaw\0"
    "setOuterLoop_Thrust\0setInnerLoop\0"
    "setInnerLoop_Roll\0setInnerLoop_Pitch\0"
    "setInnerLoop_Yaw\0setInnerLoop_Thrust\0"
    "emitNotifications\0getOuterLoop\0"
    "getOuterLoop_Roll\0getOuterLoop_Pitch\0"
    "getOuterLoop_Yaw\0getOuterLoop_Thrust\0"
    "getInnerLoop\0getInnerLoop_Roll\0"
    "getInnerLoop_Pitch\0getInnerLoop_Yaw\0"
    "getInnerLoop_Thrust\0OuterLoop_Roll\0"
    "OuterLoop_Pitch\0OuterLoop_Yaw\0"
    "OuterLoop_Thrust\0InnerLoop_Roll\0"
    "InnerLoop_Pitch\0InnerLoop_Yaw\0"
    "InnerLoop_Thrust"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StabilizationStatus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       8,  252, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  169,    2, 0x06 /* Public */,
       5,    1,  174,    2, 0x06 /* Public */,
       6,    1,  177,    2, 0x06 /* Public */,
       7,    1,  180,    2, 0x06 /* Public */,
       8,    1,  183,    2, 0x06 /* Public */,
       9,    2,  186,    2, 0x06 /* Public */,
      10,    1,  191,    2, 0x06 /* Public */,
      11,    1,  194,    2, 0x06 /* Public */,
      12,    1,  197,    2, 0x06 /* Public */,
      13,    1,  200,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    2,  203,    2, 0x0a /* Public */,
      15,    1,  208,    2, 0x0a /* Public */,
      16,    1,  211,    2, 0x0a /* Public */,
      17,    1,  214,    2, 0x0a /* Public */,
      18,    1,  217,    2, 0x0a /* Public */,
      19,    2,  220,    2, 0x0a /* Public */,
      20,    1,  225,    2, 0x0a /* Public */,
      21,    1,  228,    2, 0x0a /* Public */,
      22,    1,  231,    2, 0x0a /* Public */,
      23,    1,  234,    2, 0x0a /* Public */,
      24,    0,  237,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      25,    1,  238,    2, 0x02 /* Public */,
      26,    0,  241,    2, 0x02 /* Public */,
      27,    0,  242,    2, 0x02 /* Public */,
      28,    0,  243,    2, 0x02 /* Public */,
      29,    0,  244,    2, 0x02 /* Public */,
      30,    1,  245,    2, 0x02 /* Public */,
      31,    0,  248,    2, 0x02 /* Public */,
      32,    0,  249,    2, 0x02 /* Public */,
      33,    0,  250,    2, 0x02 /* Public */,
      34,    0,  251,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::UChar, QMetaType::UInt,    3,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    3,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      35, QMetaType::UChar, 0x00495103,
      36, QMetaType::UChar, 0x00495103,
      37, QMetaType::UChar, 0x00495103,
      38, QMetaType::UChar, 0x00495103,
      39, QMetaType::UChar, 0x00495103,
      40, QMetaType::UChar, 0x00495103,
      41, QMetaType::UChar, 0x00495103,
      42, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       1,
       2,
       3,
       4,
       6,
       7,
       8,
       9,

       0        // eod
};

void StabilizationStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StabilizationStatus *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->OuterLoopChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 1: _t->OuterLoop_RollChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 2: _t->OuterLoop_PitchChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 3: _t->OuterLoop_YawChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 4: _t->OuterLoop_ThrustChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 5: _t->InnerLoopChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 6: _t->InnerLoop_RollChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 7: _t->InnerLoop_PitchChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 8: _t->InnerLoop_YawChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 9: _t->InnerLoop_ThrustChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 10: _t->setOuterLoop((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 11: _t->setOuterLoop_Roll((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->setOuterLoop_Pitch((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 13: _t->setOuterLoop_Yaw((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->setOuterLoop_Thrust((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 15: _t->setInnerLoop((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 16: _t->setInnerLoop_Roll((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->setInnerLoop_Pitch((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 18: _t->setInnerLoop_Yaw((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 19: _t->setInnerLoop_Thrust((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->emitNotifications(); break;
        case 21: { quint8 _r = _t->getOuterLoop((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 22: { quint8 _r = _t->getOuterLoop_Roll();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 23: { quint8 _r = _t->getOuterLoop_Pitch();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 24: { quint8 _r = _t->getOuterLoop_Yaw();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 25: { quint8 _r = _t->getOuterLoop_Thrust();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 26: { quint8 _r = _t->getInnerLoop((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 27: { quint8 _r = _t->getInnerLoop_Roll();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 28: { quint8 _r = _t->getInnerLoop_Pitch();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 29: { quint8 _r = _t->getInnerLoop_Yaw();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 30: { quint8 _r = _t->getInnerLoop_Thrust();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StabilizationStatus::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationStatus::OuterLoopChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StabilizationStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationStatus::OuterLoop_RollChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (StabilizationStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationStatus::OuterLoop_PitchChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (StabilizationStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationStatus::OuterLoop_YawChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (StabilizationStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationStatus::OuterLoop_ThrustChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (StabilizationStatus::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationStatus::InnerLoopChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (StabilizationStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationStatus::InnerLoop_RollChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (StabilizationStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationStatus::InnerLoop_PitchChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (StabilizationStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationStatus::InnerLoop_YawChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (StabilizationStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationStatus::InnerLoop_ThrustChanged)) {
                *result = 9;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<StabilizationStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint8*>(_v) = _t->getOuterLoop_Roll(); break;
        case 1: *reinterpret_cast< quint8*>(_v) = _t->getOuterLoop_Pitch(); break;
        case 2: *reinterpret_cast< quint8*>(_v) = _t->getOuterLoop_Yaw(); break;
        case 3: *reinterpret_cast< quint8*>(_v) = _t->getOuterLoop_Thrust(); break;
        case 4: *reinterpret_cast< quint8*>(_v) = _t->getInnerLoop_Roll(); break;
        case 5: *reinterpret_cast< quint8*>(_v) = _t->getInnerLoop_Pitch(); break;
        case 6: *reinterpret_cast< quint8*>(_v) = _t->getInnerLoop_Yaw(); break;
        case 7: *reinterpret_cast< quint8*>(_v) = _t->getInnerLoop_Thrust(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<StabilizationStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setOuterLoop_Roll(*reinterpret_cast< quint8*>(_v)); break;
        case 1: _t->setOuterLoop_Pitch(*reinterpret_cast< quint8*>(_v)); break;
        case 2: _t->setOuterLoop_Yaw(*reinterpret_cast< quint8*>(_v)); break;
        case 3: _t->setOuterLoop_Thrust(*reinterpret_cast< quint8*>(_v)); break;
        case 4: _t->setInnerLoop_Roll(*reinterpret_cast< quint8*>(_v)); break;
        case 5: _t->setInnerLoop_Pitch(*reinterpret_cast< quint8*>(_v)); break;
        case 6: _t->setInnerLoop_Yaw(*reinterpret_cast< quint8*>(_v)); break;
        case 7: _t->setInnerLoop_Thrust(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject StabilizationStatus::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_StabilizationStatus.data,
    qt_meta_data_StabilizationStatus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StabilizationStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StabilizationStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StabilizationStatus.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int StabilizationStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 31;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void StabilizationStatus::OuterLoopChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StabilizationStatus::OuterLoop_RollChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StabilizationStatus::OuterLoop_PitchChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void StabilizationStatus::OuterLoop_YawChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void StabilizationStatus::OuterLoop_ThrustChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void StabilizationStatus::InnerLoopChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void StabilizationStatus::InnerLoop_RollChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void StabilizationStatus::InnerLoop_PitchChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void StabilizationStatus::InnerLoop_YawChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void StabilizationStatus::InnerLoop_ThrustChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
