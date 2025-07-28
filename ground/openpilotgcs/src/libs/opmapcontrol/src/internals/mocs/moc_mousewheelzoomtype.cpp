/****************************************************************************
** Meta object code from reading C++ file 'mousewheelzoomtype.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mousewheelzoomtype.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mousewheelzoomtype.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_internals__MouseWheelZoomType_t {
    QByteArrayData data[5];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_internals__MouseWheelZoomType_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_internals__MouseWheelZoomType_t qt_meta_stringdata_internals__MouseWheelZoomType = {
    {
QT_MOC_LITERAL(0, 0, 29), // "internals::MouseWheelZoomType"
QT_MOC_LITERAL(1, 30, 5), // "Types"
QT_MOC_LITERAL(2, 36, 22), // "MousePositionAndCenter"
QT_MOC_LITERAL(3, 59, 26), // "MousePositionWithoutCenter"
QT_MOC_LITERAL(4, 86, 10) // "ViewCenter"

    },
    "internals::MouseWheelZoomType\0Types\0"
    "MousePositionAndCenter\0"
    "MousePositionWithoutCenter\0ViewCenter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_internals__MouseWheelZoomType[] = {

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
       2, uint(internals::MouseWheelZoomType::MousePositionAndCenter),
       3, uint(internals::MouseWheelZoomType::MousePositionWithoutCenter),
       4, uint(internals::MouseWheelZoomType::ViewCenter),

       0        // eod
};

void internals::MouseWheelZoomType::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject internals::MouseWheelZoomType::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_internals__MouseWheelZoomType.data,
    qt_meta_data_internals__MouseWheelZoomType,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *internals::MouseWheelZoomType::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *internals::MouseWheelZoomType::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_internals__MouseWheelZoomType.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int internals::MouseWheelZoomType::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
