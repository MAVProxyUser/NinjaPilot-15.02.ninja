/****************************************************************************
** Meta object code from reading C++ file 'flightplanstatus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/flightplanstatus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flightplanstatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FlightPlanStatus_t {
    QByteArrayData data[32];
    char stringdata0[389];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlightPlanStatus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlightPlanStatus_t qt_meta_stringdata_FlightPlanStatus = {
    {
QT_MOC_LITERAL(0, 0, 16), // "FlightPlanStatus"
QT_MOC_LITERAL(1, 17, 18), // "ErrorFileIDChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 5), // "value"
QT_MOC_LITERAL(4, 43, 19), // "ErrorLineNumChanged"
QT_MOC_LITERAL(5, 63, 12), // "DebugChanged"
QT_MOC_LITERAL(6, 76, 5), // "index"
QT_MOC_LITERAL(7, 82, 14), // "Debug_0Changed"
QT_MOC_LITERAL(8, 97, 14), // "Debug_1Changed"
QT_MOC_LITERAL(9, 112, 13), // "StatusChanged"
QT_MOC_LITERAL(10, 126, 16), // "ErrorTypeChanged"
QT_MOC_LITERAL(11, 143, 14), // "setErrorFileID"
QT_MOC_LITERAL(12, 158, 15), // "setErrorLineNum"
QT_MOC_LITERAL(13, 174, 8), // "setDebug"
QT_MOC_LITERAL(14, 183, 10), // "setDebug_0"
QT_MOC_LITERAL(15, 194, 10), // "setDebug_1"
QT_MOC_LITERAL(16, 205, 9), // "setStatus"
QT_MOC_LITERAL(17, 215, 12), // "setErrorType"
QT_MOC_LITERAL(18, 228, 17), // "emitNotifications"
QT_MOC_LITERAL(19, 246, 14), // "getErrorFileID"
QT_MOC_LITERAL(20, 261, 15), // "getErrorLineNum"
QT_MOC_LITERAL(21, 277, 8), // "getDebug"
QT_MOC_LITERAL(22, 286, 10), // "getDebug_0"
QT_MOC_LITERAL(23, 297, 10), // "getDebug_1"
QT_MOC_LITERAL(24, 308, 9), // "getStatus"
QT_MOC_LITERAL(25, 318, 12), // "getErrorType"
QT_MOC_LITERAL(26, 331, 11), // "ErrorFileID"
QT_MOC_LITERAL(27, 343, 12), // "ErrorLineNum"
QT_MOC_LITERAL(28, 356, 7), // "Debug_0"
QT_MOC_LITERAL(29, 364, 7), // "Debug_1"
QT_MOC_LITERAL(30, 372, 6), // "Status"
QT_MOC_LITERAL(31, 379, 9) // "ErrorType"

    },
    "FlightPlanStatus\0ErrorFileIDChanged\0"
    "\0value\0ErrorLineNumChanged\0DebugChanged\0"
    "index\0Debug_0Changed\0Debug_1Changed\0"
    "StatusChanged\0ErrorTypeChanged\0"
    "setErrorFileID\0setErrorLineNum\0setDebug\0"
    "setDebug_0\0setDebug_1\0setStatus\0"
    "setErrorType\0emitNotifications\0"
    "getErrorFileID\0getErrorLineNum\0getDebug\0"
    "getDebug_0\0getDebug_1\0getStatus\0"
    "getErrorType\0ErrorFileID\0ErrorLineNum\0"
    "Debug_0\0Debug_1\0Status\0ErrorType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlightPlanStatus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       6,  180, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  124,    2, 0x06 /* Public */,
       4,    1,  127,    2, 0x06 /* Public */,
       5,    2,  130,    2, 0x06 /* Public */,
       7,    1,  135,    2, 0x06 /* Public */,
       8,    1,  138,    2, 0x06 /* Public */,
       9,    1,  141,    2, 0x06 /* Public */,
      10,    1,  144,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,  147,    2, 0x0a /* Public */,
      12,    1,  150,    2, 0x0a /* Public */,
      13,    2,  153,    2, 0x0a /* Public */,
      14,    1,  158,    2, 0x0a /* Public */,
      15,    1,  161,    2, 0x0a /* Public */,
      16,    1,  164,    2, 0x0a /* Public */,
      17,    1,  167,    2, 0x0a /* Public */,
      18,    0,  170,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      19,    0,  171,    2, 0x02 /* Public */,
      20,    0,  172,    2, 0x02 /* Public */,
      21,    1,  173,    2, 0x02 /* Public */,
      22,    0,  176,    2, 0x02 /* Public */,
      23,    0,  177,    2, 0x02 /* Public */,
      24,    0,  178,    2, 0x02 /* Public */,
      25,    0,  179,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    6,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    6,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::Float, QMetaType::UInt,    6,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      26, QMetaType::UInt, 0x00495103,
      27, QMetaType::UInt, 0x00495103,
      28, QMetaType::Float, 0x00495103,
      29, QMetaType::Float, 0x00495103,
      30, QMetaType::UChar, 0x00495103,
      31, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       3,
       4,
       5,
       6,

       0        // eod
};

void FlightPlanStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FlightPlanStatus *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ErrorFileIDChanged((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 1: _t->ErrorLineNumChanged((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 2: _t->DebugChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->Debug_0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->Debug_1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->StatusChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 6: _t->ErrorTypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 7: _t->setErrorFileID((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 8: _t->setErrorLineNum((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 9: _t->setDebug((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 10: _t->setDebug_0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->setDebug_1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->setStatus((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 13: _t->setErrorType((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->emitNotifications(); break;
        case 15: { quint32 _r = _t->getErrorFileID();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 16: { quint32 _r = _t->getErrorLineNum();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 17: { float _r = _t->getDebug((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 18: { float _r = _t->getDebug_0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 19: { float _r = _t->getDebug_1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 20: { quint8 _r = _t->getStatus();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 21: { quint8 _r = _t->getErrorType();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FlightPlanStatus::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightPlanStatus::ErrorFileIDChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FlightPlanStatus::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightPlanStatus::ErrorLineNumChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FlightPlanStatus::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightPlanStatus::DebugChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FlightPlanStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightPlanStatus::Debug_0Changed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FlightPlanStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightPlanStatus::Debug_1Changed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FlightPlanStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightPlanStatus::StatusChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (FlightPlanStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightPlanStatus::ErrorTypeChanged)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FlightPlanStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint32*>(_v) = _t->getErrorFileID(); break;
        case 1: *reinterpret_cast< quint32*>(_v) = _t->getErrorLineNum(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getDebug_0(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getDebug_1(); break;
        case 4: *reinterpret_cast< quint8*>(_v) = _t->getStatus(); break;
        case 5: *reinterpret_cast< quint8*>(_v) = _t->getErrorType(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<FlightPlanStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setErrorFileID(*reinterpret_cast< quint32*>(_v)); break;
        case 1: _t->setErrorLineNum(*reinterpret_cast< quint32*>(_v)); break;
        case 2: _t->setDebug_0(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setDebug_1(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setStatus(*reinterpret_cast< quint8*>(_v)); break;
        case 5: _t->setErrorType(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject FlightPlanStatus::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_FlightPlanStatus.data,
    qt_meta_data_FlightPlanStatus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FlightPlanStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlightPlanStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlightPlanStatus.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int FlightPlanStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FlightPlanStatus::ErrorFileIDChanged(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FlightPlanStatus::ErrorLineNumChanged(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FlightPlanStatus::DebugChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FlightPlanStatus::Debug_0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FlightPlanStatus::Debug_1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FlightPlanStatus::StatusChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void FlightPlanStatus::ErrorTypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
