/****************************************************************************
** Meta object code from reading C++ file 'core.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../core.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'core.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_internals__Core_t {
    QByteArrayData data[19];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_internals__Core_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_internals__Core_t qt_meta_stringdata_internals__Core = {
    {
QT_MOC_LITERAL(0, 0, 15), // "internals::Core"
QT_MOC_LITERAL(1, 16, 24), // "OnCurrentPositionChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 22), // "internals::PointLatLng"
QT_MOC_LITERAL(4, 65, 5), // "point"
QT_MOC_LITERAL(5, 71, 18), // "OnTileLoadComplete"
QT_MOC_LITERAL(6, 90, 18), // "OnTilesStillToLoad"
QT_MOC_LITERAL(7, 109, 6), // "number"
QT_MOC_LITERAL(8, 116, 15), // "OnTileLoadStart"
QT_MOC_LITERAL(9, 132, 9), // "OnMapDrag"
QT_MOC_LITERAL(10, 142, 16), // "OnMapZoomChanged"
QT_MOC_LITERAL(11, 159, 16), // "OnMapTypeChanged"
QT_MOC_LITERAL(12, 176, 14), // "MapType::Types"
QT_MOC_LITERAL(13, 191, 4), // "type"
QT_MOC_LITERAL(14, 196, 16), // "OnEmptyTileError"
QT_MOC_LITERAL(15, 213, 4), // "zoom"
QT_MOC_LITERAL(16, 218, 11), // "core::Point"
QT_MOC_LITERAL(17, 230, 3), // "pos"
QT_MOC_LITERAL(18, 234, 18) // "OnNeedInvalidation"

    },
    "internals::Core\0OnCurrentPositionChanged\0"
    "\0internals::PointLatLng\0point\0"
    "OnTileLoadComplete\0OnTilesStillToLoad\0"
    "number\0OnTileLoadStart\0OnMapDrag\0"
    "OnMapZoomChanged\0OnMapTypeChanged\0"
    "MapType::Types\0type\0OnEmptyTileError\0"
    "zoom\0core::Point\0pos\0OnNeedInvalidation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_internals__Core[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    0,   62,    2, 0x06 /* Public */,
       6,    1,   63,    2, 0x06 /* Public */,
       8,    0,   66,    2, 0x06 /* Public */,
       9,    0,   67,    2, 0x06 /* Public */,
      10,    0,   68,    2, 0x06 /* Public */,
      11,    1,   69,    2, 0x06 /* Public */,
      14,    2,   72,    2, 0x06 /* Public */,
      18,    0,   77,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16,   15,   17,
    QMetaType::Void,

       0        // eod
};

void internals::Core::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Core *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->OnCurrentPositionChanged((*reinterpret_cast< internals::PointLatLng(*)>(_a[1]))); break;
        case 1: _t->OnTileLoadComplete(); break;
        case 2: _t->OnTilesStillToLoad((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnTileLoadStart(); break;
        case 4: _t->OnMapDrag(); break;
        case 5: _t->OnMapZoomChanged(); break;
        case 6: _t->OnMapTypeChanged((*reinterpret_cast< MapType::Types(*)>(_a[1]))); break;
        case 7: _t->OnEmptyTileError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< core::Point(*)>(_a[2]))); break;
        case 8: _t->OnNeedInvalidation(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Core::*)(internals::PointLatLng );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::OnCurrentPositionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Core::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::OnTileLoadComplete)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Core::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::OnTilesStillToLoad)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Core::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::OnTileLoadStart)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Core::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::OnMapDrag)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Core::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::OnMapZoomChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Core::*)(MapType::Types );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::OnMapTypeChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Core::*)(int , core::Point );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::OnEmptyTileError)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Core::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::OnNeedInvalidation)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject internals::Core::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_internals__Core.data,
    qt_meta_data_internals__Core,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *internals::Core::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *internals::Core::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_internals__Core.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(this);
    return QObject::qt_metacast(_clname);
}

int internals::Core::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void internals::Core::OnCurrentPositionChanged(internals::PointLatLng _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void internals::Core::OnTileLoadComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void internals::Core::OnTilesStillToLoad(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void internals::Core::OnTileLoadStart()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void internals::Core::OnMapDrag()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void internals::Core::OnMapZoomChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void internals::Core::OnMapTypeChanged(MapType::Types _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void internals::Core::OnEmptyTileError(int _t1, core::Point _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void internals::Core::OnNeedInvalidation()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
