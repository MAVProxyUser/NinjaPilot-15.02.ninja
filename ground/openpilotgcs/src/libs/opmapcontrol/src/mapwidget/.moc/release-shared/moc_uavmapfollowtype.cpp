/****************************************************************************
** Meta object code from reading C++ file 'uavmapfollowtype.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../uavmapfollowtype.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uavmapfollowtype.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mapcontrol__UAVMapFollowType_t {
    QByteArrayData data[5];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mapcontrol__UAVMapFollowType_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mapcontrol__UAVMapFollowType_t qt_meta_stringdata_mapcontrol__UAVMapFollowType = {
    {
QT_MOC_LITERAL(0, 0, 28), // "mapcontrol::UAVMapFollowType"
QT_MOC_LITERAL(1, 29, 5), // "Types"
QT_MOC_LITERAL(2, 35, 9), // "CenterMap"
QT_MOC_LITERAL(3, 45, 18), // "CenterAndRotateMap"
QT_MOC_LITERAL(4, 64, 4) // "None"

    },
    "mapcontrol::UAVMapFollowType\0Types\0"
    "CenterMap\0CenterAndRotateMap\0None"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mapcontrol__UAVMapFollowType[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    3,   19,

 // enum data: key, value
       2, uint(mapcontrol::UAVMapFollowType::CenterMap),
       3, uint(mapcontrol::UAVMapFollowType::CenterAndRotateMap),
       4, uint(mapcontrol::UAVMapFollowType::None),

       0        // eod
};

void mapcontrol::UAVMapFollowType::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject mapcontrol::UAVMapFollowType::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_mapcontrol__UAVMapFollowType.data,
    qt_meta_data_mapcontrol__UAVMapFollowType,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mapcontrol::UAVMapFollowType::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mapcontrol::UAVMapFollowType::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mapcontrol__UAVMapFollowType.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int mapcontrol::UAVMapFollowType::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
