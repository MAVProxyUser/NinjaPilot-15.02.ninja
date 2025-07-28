/****************************************************************************
** Meta object code from reading C++ file 'gpstime.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/gpstime.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gpstime.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GPSTime_t {
    QByteArrayData data[28];
    char stringdata0[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GPSTime_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GPSTime_t qt_meta_stringdata_GPSTime = {
    {
QT_MOC_LITERAL(0, 0, 7), // "GPSTime"
QT_MOC_LITERAL(1, 8, 11), // "YearChanged"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 5), // "value"
QT_MOC_LITERAL(4, 27, 12), // "MonthChanged"
QT_MOC_LITERAL(5, 40, 10), // "DayChanged"
QT_MOC_LITERAL(6, 51, 11), // "HourChanged"
QT_MOC_LITERAL(7, 63, 13), // "MinuteChanged"
QT_MOC_LITERAL(8, 77, 13), // "SecondChanged"
QT_MOC_LITERAL(9, 91, 7), // "setYear"
QT_MOC_LITERAL(10, 99, 8), // "setMonth"
QT_MOC_LITERAL(11, 108, 6), // "setDay"
QT_MOC_LITERAL(12, 115, 7), // "setHour"
QT_MOC_LITERAL(13, 123, 9), // "setMinute"
QT_MOC_LITERAL(14, 133, 9), // "setSecond"
QT_MOC_LITERAL(15, 143, 17), // "emitNotifications"
QT_MOC_LITERAL(16, 161, 7), // "getYear"
QT_MOC_LITERAL(17, 169, 8), // "getMonth"
QT_MOC_LITERAL(18, 178, 6), // "getDay"
QT_MOC_LITERAL(19, 185, 7), // "getHour"
QT_MOC_LITERAL(20, 193, 9), // "getMinute"
QT_MOC_LITERAL(21, 203, 9), // "getSecond"
QT_MOC_LITERAL(22, 213, 4), // "Year"
QT_MOC_LITERAL(23, 218, 5), // "Month"
QT_MOC_LITERAL(24, 224, 3), // "Day"
QT_MOC_LITERAL(25, 228, 4), // "Hour"
QT_MOC_LITERAL(26, 233, 6), // "Minute"
QT_MOC_LITERAL(27, 240, 6) // "Second"

    },
    "GPSTime\0YearChanged\0\0value\0MonthChanged\0"
    "DayChanged\0HourChanged\0MinuteChanged\0"
    "SecondChanged\0setYear\0setMonth\0setDay\0"
    "setHour\0setMinute\0setSecond\0"
    "emitNotifications\0getYear\0getMonth\0"
    "getDay\0getHour\0getMinute\0getSecond\0"
    "Year\0Month\0Day\0Hour\0Minute\0Second"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GPSTime[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       6,  152, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x06 /* Public */,
       4,    1,  112,    2, 0x06 /* Public */,
       5,    1,  115,    2, 0x06 /* Public */,
       6,    1,  118,    2, 0x06 /* Public */,
       7,    1,  121,    2, 0x06 /* Public */,
       8,    1,  124,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,  127,    2, 0x0a /* Public */,
      10,    1,  130,    2, 0x0a /* Public */,
      11,    1,  133,    2, 0x0a /* Public */,
      12,    1,  136,    2, 0x0a /* Public */,
      13,    1,  139,    2, 0x0a /* Public */,
      14,    1,  142,    2, 0x0a /* Public */,
      15,    0,  145,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      16,    0,  146,    2, 0x02 /* Public */,
      17,    0,  147,    2, 0x02 /* Public */,
      18,    0,  148,    2, 0x02 /* Public */,
      19,    0,  149,    2, 0x02 /* Public */,
      20,    0,  150,    2, 0x02 /* Public */,
      21,    0,  151,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Short,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,

 // properties: name, type, flags
      22, QMetaType::Short, 0x00495103,
      23, QMetaType::SChar, 0x00495103,
      24, QMetaType::SChar, 0x00495103,
      25, QMetaType::SChar, 0x00495103,
      26, QMetaType::SChar, 0x00495103,
      27, QMetaType::SChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,

       0        // eod
};

void GPSTime::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GPSTime *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->YearChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 1: _t->MonthChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 2: _t->DayChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 3: _t->HourChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 4: _t->MinuteChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 5: _t->SecondChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 6: _t->setYear((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 7: _t->setMonth((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 8: _t->setDay((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 9: _t->setHour((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 10: _t->setMinute((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 11: _t->setSecond((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 12: _t->emitNotifications(); break;
        case 13: { qint16 _r = _t->getYear();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 14: { qint8 _r = _t->getMonth();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 15: { qint8 _r = _t->getDay();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 16: { qint8 _r = _t->getHour();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 17: { qint8 _r = _t->getMinute();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 18: { qint8 _r = _t->getSecond();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GPSTime::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSTime::YearChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GPSTime::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSTime::MonthChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GPSTime::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSTime::DayChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GPSTime::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSTime::HourChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GPSTime::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSTime::MinuteChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GPSTime::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSTime::SecondChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<GPSTime *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qint16*>(_v) = _t->getYear(); break;
        case 1: *reinterpret_cast< qint8*>(_v) = _t->getMonth(); break;
        case 2: *reinterpret_cast< qint8*>(_v) = _t->getDay(); break;
        case 3: *reinterpret_cast< qint8*>(_v) = _t->getHour(); break;
        case 4: *reinterpret_cast< qint8*>(_v) = _t->getMinute(); break;
        case 5: *reinterpret_cast< qint8*>(_v) = _t->getSecond(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<GPSTime *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setYear(*reinterpret_cast< qint16*>(_v)); break;
        case 1: _t->setMonth(*reinterpret_cast< qint8*>(_v)); break;
        case 2: _t->setDay(*reinterpret_cast< qint8*>(_v)); break;
        case 3: _t->setHour(*reinterpret_cast< qint8*>(_v)); break;
        case 4: _t->setMinute(*reinterpret_cast< qint8*>(_v)); break;
        case 5: _t->setSecond(*reinterpret_cast< qint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject GPSTime::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_GPSTime.data,
    qt_meta_data_GPSTime,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GPSTime::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GPSTime::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GPSTime.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int GPSTime::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void GPSTime::YearChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GPSTime::MonthChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GPSTime::DayChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GPSTime::HourChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GPSTime::MinuteChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GPSTime::SecondChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
