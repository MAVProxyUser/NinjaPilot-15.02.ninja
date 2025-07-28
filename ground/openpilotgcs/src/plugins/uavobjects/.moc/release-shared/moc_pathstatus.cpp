/****************************************************************************
** Meta object code from reading C++ file 'pathstatus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/pathstatus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pathstatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PathStatus_t {
    QByteArrayData data[48];
    char stringdata0[927];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PathStatus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PathStatus_t qt_meta_stringdata_PathStatus = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PathStatus"
QT_MOC_LITERAL(1, 11, 26), // "fractional_progressChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5), // "value"
QT_MOC_LITERAL(4, 45, 12), // "errorChanged"
QT_MOC_LITERAL(5, 58, 27), // "path_direction_northChanged"
QT_MOC_LITERAL(6, 86, 26), // "path_direction_eastChanged"
QT_MOC_LITERAL(7, 113, 26), // "path_direction_downChanged"
QT_MOC_LITERAL(8, 140, 33), // "correction_direction_northCha..."
QT_MOC_LITERAL(9, 174, 32), // "correction_direction_eastChanged"
QT_MOC_LITERAL(10, 207, 32), // "correction_direction_downChanged"
QT_MOC_LITERAL(11, 240, 16), // "path_timeChanged"
QT_MOC_LITERAL(12, 257, 10), // "UIDChanged"
QT_MOC_LITERAL(13, 268, 13), // "StatusChanged"
QT_MOC_LITERAL(14, 282, 22), // "setfractional_progress"
QT_MOC_LITERAL(15, 305, 8), // "seterror"
QT_MOC_LITERAL(16, 314, 23), // "setpath_direction_north"
QT_MOC_LITERAL(17, 338, 22), // "setpath_direction_east"
QT_MOC_LITERAL(18, 361, 22), // "setpath_direction_down"
QT_MOC_LITERAL(19, 384, 29), // "setcorrection_direction_north"
QT_MOC_LITERAL(20, 414, 28), // "setcorrection_direction_east"
QT_MOC_LITERAL(21, 443, 28), // "setcorrection_direction_down"
QT_MOC_LITERAL(22, 472, 12), // "setpath_time"
QT_MOC_LITERAL(23, 485, 6), // "setUID"
QT_MOC_LITERAL(24, 492, 9), // "setStatus"
QT_MOC_LITERAL(25, 502, 17), // "emitNotifications"
QT_MOC_LITERAL(26, 520, 22), // "getfractional_progress"
QT_MOC_LITERAL(27, 543, 8), // "geterror"
QT_MOC_LITERAL(28, 552, 23), // "getpath_direction_north"
QT_MOC_LITERAL(29, 576, 22), // "getpath_direction_east"
QT_MOC_LITERAL(30, 599, 22), // "getpath_direction_down"
QT_MOC_LITERAL(31, 622, 29), // "getcorrection_direction_north"
QT_MOC_LITERAL(32, 652, 28), // "getcorrection_direction_east"
QT_MOC_LITERAL(33, 681, 28), // "getcorrection_direction_down"
QT_MOC_LITERAL(34, 710, 12), // "getpath_time"
QT_MOC_LITERAL(35, 723, 6), // "getUID"
QT_MOC_LITERAL(36, 730, 9), // "getStatus"
QT_MOC_LITERAL(37, 740, 19), // "fractional_progress"
QT_MOC_LITERAL(38, 760, 5), // "error"
QT_MOC_LITERAL(39, 766, 20), // "path_direction_north"
QT_MOC_LITERAL(40, 787, 19), // "path_direction_east"
QT_MOC_LITERAL(41, 807, 19), // "path_direction_down"
QT_MOC_LITERAL(42, 827, 26), // "correction_direction_north"
QT_MOC_LITERAL(43, 854, 25), // "correction_direction_east"
QT_MOC_LITERAL(44, 880, 25), // "correction_direction_down"
QT_MOC_LITERAL(45, 906, 9), // "path_time"
QT_MOC_LITERAL(46, 916, 3), // "UID"
QT_MOC_LITERAL(47, 920, 6) // "Status"

    },
    "PathStatus\0fractional_progressChanged\0"
    "\0value\0errorChanged\0path_direction_northChanged\0"
    "path_direction_eastChanged\0"
    "path_direction_downChanged\0"
    "correction_direction_northChanged\0"
    "correction_direction_eastChanged\0"
    "correction_direction_downChanged\0"
    "path_timeChanged\0UIDChanged\0StatusChanged\0"
    "setfractional_progress\0seterror\0"
    "setpath_direction_north\0setpath_direction_east\0"
    "setpath_direction_down\0"
    "setcorrection_direction_north\0"
    "setcorrection_direction_east\0"
    "setcorrection_direction_down\0setpath_time\0"
    "setUID\0setStatus\0emitNotifications\0"
    "getfractional_progress\0geterror\0"
    "getpath_direction_north\0getpath_direction_east\0"
    "getpath_direction_down\0"
    "getcorrection_direction_north\0"
    "getcorrection_direction_east\0"
    "getcorrection_direction_down\0getpath_time\0"
    "getUID\0getStatus\0fractional_progress\0"
    "error\0path_direction_north\0"
    "path_direction_east\0path_direction_down\0"
    "correction_direction_north\0"
    "correction_direction_east\0"
    "correction_direction_down\0path_time\0"
    "UID\0Status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PathStatus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
      11,  262, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  184,    2, 0x06 /* Public */,
       4,    1,  187,    2, 0x06 /* Public */,
       5,    1,  190,    2, 0x06 /* Public */,
       6,    1,  193,    2, 0x06 /* Public */,
       7,    1,  196,    2, 0x06 /* Public */,
       8,    1,  199,    2, 0x06 /* Public */,
       9,    1,  202,    2, 0x06 /* Public */,
      10,    1,  205,    2, 0x06 /* Public */,
      11,    1,  208,    2, 0x06 /* Public */,
      12,    1,  211,    2, 0x06 /* Public */,
      13,    1,  214,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    1,  217,    2, 0x0a /* Public */,
      15,    1,  220,    2, 0x0a /* Public */,
      16,    1,  223,    2, 0x0a /* Public */,
      17,    1,  226,    2, 0x0a /* Public */,
      18,    1,  229,    2, 0x0a /* Public */,
      19,    1,  232,    2, 0x0a /* Public */,
      20,    1,  235,    2, 0x0a /* Public */,
      21,    1,  238,    2, 0x0a /* Public */,
      22,    1,  241,    2, 0x0a /* Public */,
      23,    1,  244,    2, 0x0a /* Public */,
      24,    1,  247,    2, 0x0a /* Public */,
      25,    0,  250,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      26,    0,  251,    2, 0x02 /* Public */,
      27,    0,  252,    2, 0x02 /* Public */,
      28,    0,  253,    2, 0x02 /* Public */,
      29,    0,  254,    2, 0x02 /* Public */,
      30,    0,  255,    2, 0x02 /* Public */,
      31,    0,  256,    2, 0x02 /* Public */,
      32,    0,  257,    2, 0x02 /* Public */,
      33,    0,  258,    2, 0x02 /* Public */,
      34,    0,  259,    2, 0x02 /* Public */,
      35,    0,  260,    2, 0x02 /* Public */,
      36,    0,  261,    2, 0x02 /* Public */,

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
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::UChar,    3,

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
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::UChar,    3,
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
    QMetaType::Short,
    QMetaType::UChar,

 // properties: name, type, flags
      37, QMetaType::Float, 0x00495003,
      38, QMetaType::Float, 0x00495003,
      39, QMetaType::Float, 0x00495003,
      40, QMetaType::Float, 0x00495003,
      41, QMetaType::Float, 0x00495003,
      42, QMetaType::Float, 0x00495003,
      43, QMetaType::Float, 0x00495003,
      44, QMetaType::Float, 0x00495003,
      45, QMetaType::Float, 0x00495003,
      46, QMetaType::Short, 0x00495103,
      47, QMetaType::UChar, 0x00495103,

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
       9,
      10,

       0        // eod
};

void PathStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PathStatus *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fractional_progressChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->errorChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->path_direction_northChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->path_direction_eastChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->path_direction_downChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->correction_direction_northChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->correction_direction_eastChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->correction_direction_downChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->path_timeChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->UIDChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 10: _t->StatusChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 11: _t->setfractional_progress((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->seterror((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->setpath_direction_north((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->setpath_direction_east((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->setpath_direction_down((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->setcorrection_direction_north((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 17: _t->setcorrection_direction_east((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->setcorrection_direction_down((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->setpath_time((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->setUID((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 21: _t->setStatus((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 22: _t->emitNotifications(); break;
        case 23: { float _r = _t->getfractional_progress();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 24: { float _r = _t->geterror();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 25: { float _r = _t->getpath_direction_north();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 26: { float _r = _t->getpath_direction_east();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 27: { float _r = _t->getpath_direction_down();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 28: { float _r = _t->getcorrection_direction_north();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 29: { float _r = _t->getcorrection_direction_east();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 30: { float _r = _t->getcorrection_direction_down();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 31: { float _r = _t->getpath_time();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 32: { qint16 _r = _t->getUID();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 33: { quint8 _r = _t->getStatus();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PathStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathStatus::fractional_progressChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PathStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathStatus::errorChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PathStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathStatus::path_direction_northChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PathStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathStatus::path_direction_eastChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PathStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathStatus::path_direction_downChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PathStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathStatus::correction_direction_northChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PathStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathStatus::correction_direction_eastChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PathStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathStatus::correction_direction_downChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PathStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathStatus::path_timeChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (PathStatus::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathStatus::UIDChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (PathStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathStatus::StatusChanged)) {
                *result = 10;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PathStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getfractional_progress(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->geterror(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getpath_direction_north(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getpath_direction_east(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getpath_direction_down(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getcorrection_direction_north(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getcorrection_direction_east(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getcorrection_direction_down(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getpath_time(); break;
        case 9: *reinterpret_cast< qint16*>(_v) = _t->getUID(); break;
        case 10: *reinterpret_cast< quint8*>(_v) = _t->getStatus(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PathStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setfractional_progress(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->seterror(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setpath_direction_north(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setpath_direction_east(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setpath_direction_down(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setcorrection_direction_north(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setcorrection_direction_east(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setcorrection_direction_down(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setpath_time(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setUID(*reinterpret_cast< qint16*>(_v)); break;
        case 10: _t->setStatus(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject PathStatus::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_PathStatus.data,
    qt_meta_data_PathStatus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PathStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PathStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PathStatus.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int PathStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 34;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 11;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PathStatus::fractional_progressChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PathStatus::errorChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PathStatus::path_direction_northChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PathStatus::path_direction_eastChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PathStatus::path_direction_downChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PathStatus::correction_direction_northChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PathStatus::correction_direction_eastChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PathStatus::correction_direction_downChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PathStatus::path_timeChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void PathStatus::UIDChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void PathStatus::StatusChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
