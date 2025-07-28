/****************************************************************************
** Meta object code from reading C++ file 'pidstatus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/pidstatus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pidstatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PIDStatus_t {
    QByteArrayData data[40];
    char stringdata0[340];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PIDStatus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PIDStatus_t qt_meta_stringdata_PIDStatus = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PIDStatus"
QT_MOC_LITERAL(1, 10, 15), // "setpointChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "value"
QT_MOC_LITERAL(4, 33, 13), // "actualChanged"
QT_MOC_LITERAL(5, 47, 12), // "errorChanged"
QT_MOC_LITERAL(6, 60, 11), // "ulowChanged"
QT_MOC_LITERAL(7, 72, 12), // "uhighChanged"
QT_MOC_LITERAL(8, 85, 14), // "commandChanged"
QT_MOC_LITERAL(9, 100, 8), // "PChanged"
QT_MOC_LITERAL(10, 109, 8), // "IChanged"
QT_MOC_LITERAL(11, 118, 8), // "DChanged"
QT_MOC_LITERAL(12, 127, 11), // "setsetpoint"
QT_MOC_LITERAL(13, 139, 9), // "setactual"
QT_MOC_LITERAL(14, 149, 8), // "seterror"
QT_MOC_LITERAL(15, 158, 7), // "setulow"
QT_MOC_LITERAL(16, 166, 8), // "setuhigh"
QT_MOC_LITERAL(17, 175, 10), // "setcommand"
QT_MOC_LITERAL(18, 186, 4), // "setP"
QT_MOC_LITERAL(19, 191, 4), // "setI"
QT_MOC_LITERAL(20, 196, 4), // "setD"
QT_MOC_LITERAL(21, 201, 17), // "emitNotifications"
QT_MOC_LITERAL(22, 219, 11), // "getsetpoint"
QT_MOC_LITERAL(23, 231, 9), // "getactual"
QT_MOC_LITERAL(24, 241, 8), // "geterror"
QT_MOC_LITERAL(25, 250, 7), // "getulow"
QT_MOC_LITERAL(26, 258, 8), // "getuhigh"
QT_MOC_LITERAL(27, 267, 10), // "getcommand"
QT_MOC_LITERAL(28, 278, 4), // "getP"
QT_MOC_LITERAL(29, 283, 4), // "getI"
QT_MOC_LITERAL(30, 288, 4), // "getD"
QT_MOC_LITERAL(31, 293, 8), // "setpoint"
QT_MOC_LITERAL(32, 302, 6), // "actual"
QT_MOC_LITERAL(33, 309, 5), // "error"
QT_MOC_LITERAL(34, 315, 4), // "ulow"
QT_MOC_LITERAL(35, 320, 5), // "uhigh"
QT_MOC_LITERAL(36, 326, 7), // "command"
QT_MOC_LITERAL(37, 334, 1), // "P"
QT_MOC_LITERAL(38, 336, 1), // "I"
QT_MOC_LITERAL(39, 338, 1) // "D"

    },
    "PIDStatus\0setpointChanged\0\0value\0"
    "actualChanged\0errorChanged\0ulowChanged\0"
    "uhighChanged\0commandChanged\0PChanged\0"
    "IChanged\0DChanged\0setsetpoint\0setactual\0"
    "seterror\0setulow\0setuhigh\0setcommand\0"
    "setP\0setI\0setD\0emitNotifications\0"
    "getsetpoint\0getactual\0geterror\0getulow\0"
    "getuhigh\0getcommand\0getP\0getI\0getD\0"
    "setpoint\0actual\0error\0ulow\0uhigh\0"
    "command\0P\0I\0D"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PIDStatus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       9,  218, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  154,    2, 0x06 /* Public */,
       4,    1,  157,    2, 0x06 /* Public */,
       5,    1,  160,    2, 0x06 /* Public */,
       6,    1,  163,    2, 0x06 /* Public */,
       7,    1,  166,    2, 0x06 /* Public */,
       8,    1,  169,    2, 0x06 /* Public */,
       9,    1,  172,    2, 0x06 /* Public */,
      10,    1,  175,    2, 0x06 /* Public */,
      11,    1,  178,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,  181,    2, 0x0a /* Public */,
      13,    1,  184,    2, 0x0a /* Public */,
      14,    1,  187,    2, 0x0a /* Public */,
      15,    1,  190,    2, 0x0a /* Public */,
      16,    1,  193,    2, 0x0a /* Public */,
      17,    1,  196,    2, 0x0a /* Public */,
      18,    1,  199,    2, 0x0a /* Public */,
      19,    1,  202,    2, 0x0a /* Public */,
      20,    1,  205,    2, 0x0a /* Public */,
      21,    0,  208,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      22,    0,  209,    2, 0x02 /* Public */,
      23,    0,  210,    2, 0x02 /* Public */,
      24,    0,  211,    2, 0x02 /* Public */,
      25,    0,  212,    2, 0x02 /* Public */,
      26,    0,  213,    2, 0x02 /* Public */,
      27,    0,  214,    2, 0x02 /* Public */,
      28,    0,  215,    2, 0x02 /* Public */,
      29,    0,  216,    2, 0x02 /* Public */,
      30,    0,  217,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
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
    QMetaType::Float,
    QMetaType::Float,

 // properties: name, type, flags
      31, QMetaType::Float, 0x00495003,
      32, QMetaType::Float, 0x00495003,
      33, QMetaType::Float, 0x00495003,
      34, QMetaType::Float, 0x00495003,
      35, QMetaType::Float, 0x00495003,
      36, QMetaType::Float, 0x00495003,
      37, QMetaType::Float, 0x00495103,
      38, QMetaType::Float, 0x00495103,
      39, QMetaType::Float, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,

       0        // eod
};

void PIDStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PIDStatus *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setpointChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->actualChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->errorChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->ulowChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->uhighChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->commandChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->PChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->IChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->DChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->setsetpoint((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->setactual((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->seterror((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->setulow((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->setuhigh((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->setcommand((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->setP((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->setI((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 17: _t->setD((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->emitNotifications(); break;
        case 19: { float _r = _t->getsetpoint();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 20: { float _r = _t->getactual();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 21: { float _r = _t->geterror();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 22: { float _r = _t->getulow();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 23: { float _r = _t->getuhigh();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 24: { float _r = _t->getcommand();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 25: { float _r = _t->getP();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 26: { float _r = _t->getI();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 27: { float _r = _t->getD();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PIDStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PIDStatus::setpointChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PIDStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PIDStatus::actualChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PIDStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PIDStatus::errorChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PIDStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PIDStatus::ulowChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PIDStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PIDStatus::uhighChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PIDStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PIDStatus::commandChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PIDStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PIDStatus::PChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PIDStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PIDStatus::IChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PIDStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PIDStatus::DChanged)) {
                *result = 8;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PIDStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getsetpoint(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getactual(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->geterror(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getulow(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getuhigh(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getcommand(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getP(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getI(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getD(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PIDStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setsetpoint(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setactual(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->seterror(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setulow(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setuhigh(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setcommand(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setP(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setI(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setD(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject PIDStatus::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_PIDStatus.data,
    qt_meta_data_PIDStatus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PIDStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PIDStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PIDStatus.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int PIDStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 28;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PIDStatus::setpointChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PIDStatus::actualChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PIDStatus::errorChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PIDStatus::ulowChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PIDStatus::uhighChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PIDStatus::commandChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PIDStatus::PChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PIDStatus::IChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PIDStatus::DChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
