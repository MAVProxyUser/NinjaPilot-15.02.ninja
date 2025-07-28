/****************************************************************************
** Meta object code from reading C++ file 'uavitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../uavitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uavitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mapcontrol__UAVItem_t {
    QByteArrayData data[15];
    char stringdata0[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mapcontrol__UAVItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mapcontrol__UAVItem_t qt_meta_stringdata_mapcontrol__UAVItem = {
    {
QT_MOC_LITERAL(0, 0, 19), // "mapcontrol::UAVItem"
QT_MOC_LITERAL(1, 20, 18), // "UAVReachedWayPoint"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 14), // "waypointnumber"
QT_MOC_LITERAL(4, 55, 13), // "WayPointItem*"
QT_MOC_LITERAL(5, 69, 8), // "waypoint"
QT_MOC_LITERAL(6, 78, 19), // "UAVLeftSafetyBouble"
QT_MOC_LITERAL(7, 98, 22), // "internals::PointLatLng"
QT_MOC_LITERAL(8, 121, 8), // "position"
QT_MOC_LITERAL(9, 130, 16), // "setChildPosition"
QT_MOC_LITERAL(10, 147, 12), // "setChildLine"
QT_MOC_LITERAL(11, 160, 10), // "RefreshPos"
QT_MOC_LITERAL(12, 171, 14), // "setOpacitySlot"
QT_MOC_LITERAL(13, 186, 7), // "opacity"
QT_MOC_LITERAL(14, 194, 15) // "zoomChangedSlot"

    },
    "mapcontrol::UAVItem\0UAVReachedWayPoint\0"
    "\0waypointnumber\0WayPointItem*\0waypoint\0"
    "UAVLeftSafetyBouble\0internals::PointLatLng\0"
    "position\0setChildPosition\0setChildLine\0"
    "RefreshPos\0setOpacitySlot\0opacity\0"
    "zoomChangedSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mapcontrol__UAVItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       6,    1,   54,    2, 0x06 /* Public */,
       9,    0,   57,    2, 0x06 /* Public */,
      10,    0,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   59,    2, 0x0a /* Public */,
      12,    1,   60,    2, 0x0a /* Public */,
      14,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,   13,
    QMetaType::Void,

       0        // eod
};

void mapcontrol::UAVItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UAVItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->UAVReachedWayPoint((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< WayPointItem*(*)>(_a[2]))); break;
        case 1: _t->UAVLeftSafetyBouble((*reinterpret_cast< const internals::PointLatLng(*)>(_a[1]))); break;
        case 2: _t->setChildPosition(); break;
        case 3: _t->setChildLine(); break;
        case 4: _t->RefreshPos(); break;
        case 5: _t->setOpacitySlot((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 6: _t->zoomChangedSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WayPointItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UAVItem::*)(int const & , WayPointItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVItem::UAVReachedWayPoint)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UAVItem::*)(internals::PointLatLng const & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVItem::UAVLeftSafetyBouble)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UAVItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVItem::setChildPosition)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UAVItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVItem::setChildLine)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mapcontrol::UAVItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_mapcontrol__UAVItem.data,
    qt_meta_data_mapcontrol__UAVItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mapcontrol::UAVItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mapcontrol::UAVItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mapcontrol__UAVItem.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(this);
    return QObject::qt_metacast(_clname);
}

int mapcontrol::UAVItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void mapcontrol::UAVItem::UAVReachedWayPoint(int const & _t1, WayPointItem * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mapcontrol::UAVItem::UAVLeftSafetyBouble(internals::PointLatLng const & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void mapcontrol::UAVItem::setChildPosition()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void mapcontrol::UAVItem::setChildLine()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
