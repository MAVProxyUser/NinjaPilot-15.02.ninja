/****************************************************************************
** Meta object code from reading C++ file 'waypoint.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/waypoint.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'waypoint.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Waypoint_t {
    QByteArrayData data[28];
    char stringdata0[381];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Waypoint_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Waypoint_t qt_meta_stringdata_Waypoint = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Waypoint"
QT_MOC_LITERAL(1, 9, 15), // "PositionChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "index"
QT_MOC_LITERAL(4, 32, 5), // "value"
QT_MOC_LITERAL(5, 38, 21), // "Position_NorthChanged"
QT_MOC_LITERAL(6, 60, 20), // "Position_EastChanged"
QT_MOC_LITERAL(7, 81, 20), // "Position_DownChanged"
QT_MOC_LITERAL(8, 102, 15), // "VelocityChanged"
QT_MOC_LITERAL(9, 118, 13), // "ActionChanged"
QT_MOC_LITERAL(10, 132, 11), // "setPosition"
QT_MOC_LITERAL(11, 144, 17), // "setPosition_North"
QT_MOC_LITERAL(12, 162, 16), // "setPosition_East"
QT_MOC_LITERAL(13, 179, 16), // "setPosition_Down"
QT_MOC_LITERAL(14, 196, 11), // "setVelocity"
QT_MOC_LITERAL(15, 208, 9), // "setAction"
QT_MOC_LITERAL(16, 218, 17), // "emitNotifications"
QT_MOC_LITERAL(17, 236, 11), // "getPosition"
QT_MOC_LITERAL(18, 248, 17), // "getPosition_North"
QT_MOC_LITERAL(19, 266, 16), // "getPosition_East"
QT_MOC_LITERAL(20, 283, 16), // "getPosition_Down"
QT_MOC_LITERAL(21, 300, 11), // "getVelocity"
QT_MOC_LITERAL(22, 312, 9), // "getAction"
QT_MOC_LITERAL(23, 322, 14), // "Position_North"
QT_MOC_LITERAL(24, 337, 13), // "Position_East"
QT_MOC_LITERAL(25, 351, 13), // "Position_Down"
QT_MOC_LITERAL(26, 365, 8), // "Velocity"
QT_MOC_LITERAL(27, 374, 6) // "Action"

    },
    "Waypoint\0PositionChanged\0\0index\0value\0"
    "Position_NorthChanged\0Position_EastChanged\0"
    "Position_DownChanged\0VelocityChanged\0"
    "ActionChanged\0setPosition\0setPosition_North\0"
    "setPosition_East\0setPosition_Down\0"
    "setVelocity\0setAction\0emitNotifications\0"
    "getPosition\0getPosition_North\0"
    "getPosition_East\0getPosition_Down\0"
    "getVelocity\0getAction\0Position_North\0"
    "Position_East\0Position_Down\0Velocity\0"
    "Action"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Waypoint[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       5,  158, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  109,    2, 0x06 /* Public */,
       5,    1,  114,    2, 0x06 /* Public */,
       6,    1,  117,    2, 0x06 /* Public */,
       7,    1,  120,    2, 0x06 /* Public */,
       8,    1,  123,    2, 0x06 /* Public */,
       9,    1,  126,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    2,  129,    2, 0x0a /* Public */,
      11,    1,  134,    2, 0x0a /* Public */,
      12,    1,  137,    2, 0x0a /* Public */,
      13,    1,  140,    2, 0x0a /* Public */,
      14,    1,  143,    2, 0x0a /* Public */,
      15,    1,  146,    2, 0x0a /* Public */,
      16,    0,  149,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      17,    1,  150,    2, 0x02 /* Public */,
      18,    0,  153,    2, 0x02 /* Public */,
      19,    0,  154,    2, 0x02 /* Public */,
      20,    0,  155,    2, 0x02 /* Public */,
      21,    0,  156,    2, 0x02 /* Public */,
      22,    0,  157,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UChar,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar,

 // properties: name, type, flags
      23, QMetaType::Float, 0x00495103,
      24, QMetaType::Float, 0x00495103,
      25, QMetaType::Float, 0x00495103,
      26, QMetaType::Float, 0x00495103,
      27, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       1,
       2,
       3,
       4,
       5,

       0        // eod
};

void Waypoint::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Waypoint *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->PositionChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->Position_NorthChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->Position_EastChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->Position_DownChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->VelocityChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->ActionChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 6: _t->setPosition((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 7: _t->setPosition_North((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->setPosition_East((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->setPosition_Down((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->setVelocity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->setAction((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->emitNotifications(); break;
        case 13: { float _r = _t->getPosition((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 14: { float _r = _t->getPosition_North();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 15: { float _r = _t->getPosition_East();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 16: { float _r = _t->getPosition_Down();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 17: { float _r = _t->getVelocity();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 18: { quint8 _r = _t->getAction();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Waypoint::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Waypoint::PositionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Waypoint::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Waypoint::Position_NorthChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Waypoint::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Waypoint::Position_EastChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Waypoint::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Waypoint::Position_DownChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Waypoint::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Waypoint::VelocityChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Waypoint::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Waypoint::ActionChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Waypoint *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getPosition_North(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getPosition_East(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getPosition_Down(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getVelocity(); break;
        case 4: *reinterpret_cast< quint8*>(_v) = _t->getAction(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Waypoint *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPosition_North(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setPosition_East(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setPosition_Down(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setVelocity(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setAction(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Waypoint::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_Waypoint.data,
    qt_meta_data_Waypoint,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Waypoint::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Waypoint::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Waypoint.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int Waypoint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Waypoint::PositionChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Waypoint::Position_NorthChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Waypoint::Position_EastChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Waypoint::Position_DownChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Waypoint::VelocityChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Waypoint::ActionChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
