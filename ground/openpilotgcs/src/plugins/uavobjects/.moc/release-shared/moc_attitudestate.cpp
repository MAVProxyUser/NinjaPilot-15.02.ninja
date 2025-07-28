/****************************************************************************
** Meta object code from reading C++ file 'attitudestate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/attitudestate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'attitudestate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AttitudeState_t {
    QByteArrayData data[32];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AttitudeState_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AttitudeState_t qt_meta_stringdata_AttitudeState = {
    {
QT_MOC_LITERAL(0, 0, 13), // "AttitudeState"
QT_MOC_LITERAL(1, 14, 9), // "q1Changed"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "value"
QT_MOC_LITERAL(4, 31, 9), // "q2Changed"
QT_MOC_LITERAL(5, 41, 9), // "q3Changed"
QT_MOC_LITERAL(6, 51, 9), // "q4Changed"
QT_MOC_LITERAL(7, 61, 11), // "RollChanged"
QT_MOC_LITERAL(8, 73, 12), // "PitchChanged"
QT_MOC_LITERAL(9, 86, 10), // "YawChanged"
QT_MOC_LITERAL(10, 97, 5), // "setq1"
QT_MOC_LITERAL(11, 103, 5), // "setq2"
QT_MOC_LITERAL(12, 109, 5), // "setq3"
QT_MOC_LITERAL(13, 115, 5), // "setq4"
QT_MOC_LITERAL(14, 121, 7), // "setRoll"
QT_MOC_LITERAL(15, 129, 8), // "setPitch"
QT_MOC_LITERAL(16, 138, 6), // "setYaw"
QT_MOC_LITERAL(17, 145, 17), // "emitNotifications"
QT_MOC_LITERAL(18, 163, 5), // "getq1"
QT_MOC_LITERAL(19, 169, 5), // "getq2"
QT_MOC_LITERAL(20, 175, 5), // "getq3"
QT_MOC_LITERAL(21, 181, 5), // "getq4"
QT_MOC_LITERAL(22, 187, 7), // "getRoll"
QT_MOC_LITERAL(23, 195, 8), // "getPitch"
QT_MOC_LITERAL(24, 204, 6), // "getYaw"
QT_MOC_LITERAL(25, 211, 2), // "q1"
QT_MOC_LITERAL(26, 214, 2), // "q2"
QT_MOC_LITERAL(27, 217, 2), // "q3"
QT_MOC_LITERAL(28, 220, 2), // "q4"
QT_MOC_LITERAL(29, 223, 4), // "Roll"
QT_MOC_LITERAL(30, 228, 5), // "Pitch"
QT_MOC_LITERAL(31, 234, 3) // "Yaw"

    },
    "AttitudeState\0q1Changed\0\0value\0q2Changed\0"
    "q3Changed\0q4Changed\0RollChanged\0"
    "PitchChanged\0YawChanged\0setq1\0setq2\0"
    "setq3\0setq4\0setRoll\0setPitch\0setYaw\0"
    "emitNotifications\0getq1\0getq2\0getq3\0"
    "getq4\0getRoll\0getPitch\0getYaw\0q1\0q2\0"
    "q3\0q4\0Roll\0Pitch\0Yaw"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AttitudeState[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       7,  174, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  124,    2, 0x06 /* Public */,
       4,    1,  127,    2, 0x06 /* Public */,
       5,    1,  130,    2, 0x06 /* Public */,
       6,    1,  133,    2, 0x06 /* Public */,
       7,    1,  136,    2, 0x06 /* Public */,
       8,    1,  139,    2, 0x06 /* Public */,
       9,    1,  142,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,  145,    2, 0x0a /* Public */,
      11,    1,  148,    2, 0x0a /* Public */,
      12,    1,  151,    2, 0x0a /* Public */,
      13,    1,  154,    2, 0x0a /* Public */,
      14,    1,  157,    2, 0x0a /* Public */,
      15,    1,  160,    2, 0x0a /* Public */,
      16,    1,  163,    2, 0x0a /* Public */,
      17,    0,  166,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      18,    0,  167,    2, 0x02 /* Public */,
      19,    0,  168,    2, 0x02 /* Public */,
      20,    0,  169,    2, 0x02 /* Public */,
      21,    0,  170,    2, 0x02 /* Public */,
      22,    0,  171,    2, 0x02 /* Public */,
      23,    0,  172,    2, 0x02 /* Public */,
      24,    0,  173,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,

 // properties: name, type, flags
      25, QMetaType::Float, 0x00495003,
      26, QMetaType::Float, 0x00495003,
      27, QMetaType::Float, 0x00495003,
      28, QMetaType::Float, 0x00495003,
      29, QMetaType::Float, 0x00495103,
      30, QMetaType::Float, 0x00495103,
      31, QMetaType::Float, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,

       0        // eod
};

void AttitudeState::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AttitudeState *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->q1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->q2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->q3Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->q4Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->RollChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->PitchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->YawChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->setq1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->setq2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->setq3((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->setq4((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->setRoll((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->setPitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->setYaw((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->emitNotifications(); break;
        case 15: { float _r = _t->getq1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 16: { float _r = _t->getq2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 17: { float _r = _t->getq3();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 18: { float _r = _t->getq4();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 19: { float _r = _t->getRoll();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 20: { float _r = _t->getPitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 21: { float _r = _t->getYaw();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AttitudeState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeState::q1Changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AttitudeState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeState::q2Changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AttitudeState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeState::q3Changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AttitudeState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeState::q4Changed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AttitudeState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeState::RollChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AttitudeState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeState::PitchChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (AttitudeState::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeState::YawChanged)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AttitudeState *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getq1(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getq2(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getq3(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getq4(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getRoll(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getPitch(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getYaw(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<AttitudeState *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setq1(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setq2(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setq3(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setq4(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setRoll(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setPitch(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setYaw(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject AttitudeState::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_AttitudeState.data,
    qt_meta_data_AttitudeState,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AttitudeState::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AttitudeState::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AttitudeState.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int AttitudeState::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AttitudeState::q1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AttitudeState::q2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AttitudeState::q3Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AttitudeState::q4Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AttitudeState::RollChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AttitudeState::PitchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AttitudeState::YawChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
