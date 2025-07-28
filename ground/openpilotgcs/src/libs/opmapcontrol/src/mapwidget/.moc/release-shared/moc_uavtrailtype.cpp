/****************************************************************************
** Meta object code from reading C++ file 'uavtrailtype.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../uavtrailtype.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uavtrailtype.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mapcontrol__UAVTrailType_t {
    QByteArrayData data[5];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mapcontrol__UAVTrailType_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mapcontrol__UAVTrailType_t qt_meta_stringdata_mapcontrol__UAVTrailType = {
    {
QT_MOC_LITERAL(0, 0, 24), // "mapcontrol::UAVTrailType"
QT_MOC_LITERAL(1, 25, 5), // "Types"
QT_MOC_LITERAL(2, 31, 7), // "NoTrail"
QT_MOC_LITERAL(3, 39, 13), // "ByTimeElapsed"
QT_MOC_LITERAL(4, 53, 10) // "ByDistance"

    },
    "mapcontrol::UAVTrailType\0Types\0NoTrail\0"
    "ByTimeElapsed\0ByDistance"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mapcontrol__UAVTrailType[] = {

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
       2, uint(mapcontrol::UAVTrailType::NoTrail),
       3, uint(mapcontrol::UAVTrailType::ByTimeElapsed),
       4, uint(mapcontrol::UAVTrailType::ByDistance),

       0        // eod
};

void mapcontrol::UAVTrailType::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject mapcontrol::UAVTrailType::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_mapcontrol__UAVTrailType.data,
    qt_meta_data_mapcontrol__UAVTrailType,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mapcontrol::UAVTrailType::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mapcontrol::UAVTrailType::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mapcontrol__UAVTrailType.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int mapcontrol::UAVTrailType::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
