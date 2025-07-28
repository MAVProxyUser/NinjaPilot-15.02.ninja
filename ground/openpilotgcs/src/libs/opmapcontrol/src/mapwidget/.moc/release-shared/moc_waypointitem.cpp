/****************************************************************************
** Meta object code from reading C++ file 'waypointitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../waypointitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'waypointitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mapcontrol__WayPointItem_t {
    QByteArrayData data[23];
    char stringdata0[312];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mapcontrol__WayPointItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mapcontrol__WayPointItem_t qt_meta_stringdata_mapcontrol__WayPointItem = {
    {
QT_MOC_LITERAL(0, 0, 24), // "mapcontrol::WayPointItem"
QT_MOC_LITERAL(1, 25, 15), // "WPNumberChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 9), // "oldnumber"
QT_MOC_LITERAL(4, 52, 9), // "newnumber"
QT_MOC_LITERAL(5, 62, 13), // "WayPointItem*"
QT_MOC_LITERAL(6, 76, 8), // "waypoint"
QT_MOC_LITERAL(7, 85, 15), // "WPValuesChanged"
QT_MOC_LITERAL(8, 101, 19), // "waypointdoubleclick"
QT_MOC_LITERAL(9, 121, 20), // "localPositionChanged"
QT_MOC_LITERAL(10, 142, 5), // "point"
QT_MOC_LITERAL(11, 148, 17), // "manualCoordChange"
QT_MOC_LITERAL(12, 166, 16), // "aboutToBeDeleted"
QT_MOC_LITERAL(13, 183, 9), // "WPDeleted"
QT_MOC_LITERAL(14, 193, 6), // "number"
QT_MOC_LITERAL(15, 200, 12), // "WPRenumbered"
QT_MOC_LITERAL(16, 213, 10), // "WPInserted"
QT_MOC_LITERAL(17, 224, 21), // "onHomePositionChanged"
QT_MOC_LITERAL(18, 246, 22), // "internals::PointLatLng"
QT_MOC_LITERAL(19, 269, 8), // "altitude"
QT_MOC_LITERAL(20, 278, 10), // "RefreshPos"
QT_MOC_LITERAL(21, 289, 14), // "setOpacitySlot"
QT_MOC_LITERAL(22, 304, 7) // "opacity"

    },
    "mapcontrol::WayPointItem\0WPNumberChanged\0"
    "\0oldnumber\0newnumber\0WayPointItem*\0"
    "waypoint\0WPValuesChanged\0waypointdoubleclick\0"
    "localPositionChanged\0point\0manualCoordChange\0"
    "aboutToBeDeleted\0WPDeleted\0number\0"
    "WPRenumbered\0WPInserted\0onHomePositionChanged\0"
    "internals::PointLatLng\0altitude\0"
    "RefreshPos\0setOpacitySlot\0opacity"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mapcontrol__WayPointItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   74,    2, 0x06 /* Public */,
       7,    1,   81,    2, 0x06 /* Public */,
       8,    1,   84,    2, 0x06 /* Public */,
       9,    2,   87,    2, 0x06 /* Public */,
      11,    1,   92,    2, 0x06 /* Public */,
      12,    1,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    2,   98,    2, 0x0a /* Public */,
      15,    3,  103,    2, 0x0a /* Public */,
      16,    2,  110,    2, 0x0a /* Public */,
      17,    2,  115,    2, 0x0a /* Public */,
      20,    0,  120,    2, 0x0a /* Public */,
      21,    1,  121,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::QPointF, 0x80000000 | 5,   10,    6,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,   14,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,   14,    6,
    QMetaType::Void, 0x80000000 | 18, QMetaType::Float,    2,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,   22,

       0        // eod
};

void mapcontrol::WayPointItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WayPointItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->WPNumberChanged((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< WayPointItem*(*)>(_a[3]))); break;
        case 1: _t->WPValuesChanged((*reinterpret_cast< WayPointItem*(*)>(_a[1]))); break;
        case 2: _t->waypointdoubleclick((*reinterpret_cast< WayPointItem*(*)>(_a[1]))); break;
        case 3: _t->localPositionChanged((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< WayPointItem*(*)>(_a[2]))); break;
        case 4: _t->manualCoordChange((*reinterpret_cast< WayPointItem*(*)>(_a[1]))); break;
        case 5: _t->aboutToBeDeleted((*reinterpret_cast< WayPointItem*(*)>(_a[1]))); break;
        case 6: _t->WPDeleted((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< WayPointItem*(*)>(_a[2]))); break;
        case 7: _t->WPRenumbered((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< WayPointItem*(*)>(_a[3]))); break;
        case 8: _t->WPInserted((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< WayPointItem*(*)>(_a[2]))); break;
        case 9: _t->onHomePositionChanged((*reinterpret_cast< internals::PointLatLng(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 10: _t->RefreshPos(); break;
        case 11: _t->setOpacitySlot((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WayPointItem* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WayPointItem* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WayPointItem* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WayPointItem* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WayPointItem* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WayPointItem* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WayPointItem* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WayPointItem* >(); break;
            }
            break;
        case 8:
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
            using _t = void (WayPointItem::*)(int const & , int const & , WayPointItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WayPointItem::WPNumberChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WayPointItem::*)(WayPointItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WayPointItem::WPValuesChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WayPointItem::*)(WayPointItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WayPointItem::waypointdoubleclick)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WayPointItem::*)(QPointF , WayPointItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WayPointItem::localPositionChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WayPointItem::*)(WayPointItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WayPointItem::manualCoordChange)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WayPointItem::*)(WayPointItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WayPointItem::aboutToBeDeleted)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mapcontrol::WayPointItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_mapcontrol__WayPointItem.data,
    qt_meta_data_mapcontrol__WayPointItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mapcontrol::WayPointItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mapcontrol::WayPointItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mapcontrol__WayPointItem.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(this);
    return QObject::qt_metacast(_clname);
}

int mapcontrol::WayPointItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void mapcontrol::WayPointItem::WPNumberChanged(int const & _t1, int const & _t2, WayPointItem * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mapcontrol::WayPointItem::WPValuesChanged(WayPointItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void mapcontrol::WayPointItem::waypointdoubleclick(WayPointItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void mapcontrol::WayPointItem::localPositionChanged(QPointF _t1, WayPointItem * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void mapcontrol::WayPointItem::manualCoordChange(WayPointItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void mapcontrol::WayPointItem::aboutToBeDeleted(WayPointItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
