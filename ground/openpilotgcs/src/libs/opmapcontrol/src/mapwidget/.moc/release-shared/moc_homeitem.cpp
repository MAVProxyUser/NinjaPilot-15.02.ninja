/****************************************************************************
** Meta object code from reading C++ file 'homeitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../homeitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'homeitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mapcontrol__HomeItem_t {
    QByteArrayData data[11];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mapcontrol__HomeItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mapcontrol__HomeItem_t qt_meta_stringdata_mapcontrol__HomeItem = {
    {
QT_MOC_LITERAL(0, 0, 20), // "mapcontrol::HomeItem"
QT_MOC_LITERAL(1, 21, 19), // "homePositionChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 22), // "internals::PointLatLng"
QT_MOC_LITERAL(4, 65, 5), // "coord"
QT_MOC_LITERAL(5, 71, 15), // "homedoubleclick"
QT_MOC_LITERAL(6, 87, 9), // "HomeItem*"
QT_MOC_LITERAL(7, 97, 8), // "waypoint"
QT_MOC_LITERAL(8, 106, 10), // "RefreshPos"
QT_MOC_LITERAL(9, 117, 14), // "setOpacitySlot"
QT_MOC_LITERAL(10, 132, 7) // "opacity"

    },
    "mapcontrol::HomeItem\0homePositionChanged\0"
    "\0internals::PointLatLng\0coord\0"
    "homedoubleclick\0HomeItem*\0waypoint\0"
    "RefreshPos\0setOpacitySlot\0opacity"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mapcontrol__HomeItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       5,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   42,    2, 0x0a /* Public */,
       9,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Float,    4,    2,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,   10,

       0        // eod
};

void mapcontrol::HomeItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HomeItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->homePositionChanged((*reinterpret_cast< internals::PointLatLng(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->homedoubleclick((*reinterpret_cast< HomeItem*(*)>(_a[1]))); break;
        case 2: _t->RefreshPos(); break;
        case 3: _t->setOpacitySlot((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< HomeItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HomeItem::*)(internals::PointLatLng , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HomeItem::homePositionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HomeItem::*)(HomeItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HomeItem::homedoubleclick)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mapcontrol::HomeItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_mapcontrol__HomeItem.data,
    qt_meta_data_mapcontrol__HomeItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mapcontrol::HomeItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mapcontrol::HomeItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mapcontrol__HomeItem.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(this);
    return QObject::qt_metacast(_clname);
}

int mapcontrol::HomeItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void mapcontrol::HomeItem::homePositionChanged(internals::PointLatLng _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mapcontrol::HomeItem::homedoubleclick(HomeItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
