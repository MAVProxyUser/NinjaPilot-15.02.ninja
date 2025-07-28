/****************************************************************************
** Meta object code from reading C++ file 'uavobjectbrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../uavobjectbrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uavobjectbrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UAVObjectBrowser_t {
    QByteArrayData data[9];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UAVObjectBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UAVObjectBrowser_t qt_meta_stringdata_UAVObjectBrowser = {
    {
QT_MOC_LITERAL(0, 0, 16), // "UAVObjectBrowser"
QT_MOC_LITERAL(1, 17, 22), // "viewOptionsChangedSlot"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 11), // "categorized"
QT_MOC_LITERAL(4, 53, 10), // "scientific"
QT_MOC_LITERAL(5, 64, 8), // "metadata"
QT_MOC_LITERAL(6, 73, 11), // "description"
QT_MOC_LITERAL(7, 85, 15), // "splitterChanged"
QT_MOC_LITERAL(8, 101, 5) // "state"

    },
    "UAVObjectBrowser\0viewOptionsChangedSlot\0"
    "\0categorized\0scientific\0metadata\0"
    "description\0splitterChanged\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UAVObjectBrowser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    4,   24,    2, 0x08 /* Private */,
       7,    1,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QByteArray,    8,

       0        // eod
};

void UAVObjectBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UAVObjectBrowser *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->viewOptionsChangedSlot((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 1: _t->splitterChanged((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UAVObjectBrowser::staticMetaObject = { {
    QMetaObject::SuperData::link<Core::IUAVGadget::staticMetaObject>(),
    qt_meta_stringdata_UAVObjectBrowser.data,
    qt_meta_data_UAVObjectBrowser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UAVObjectBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UAVObjectBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UAVObjectBrowser.stringdata0))
        return static_cast<void*>(this);
    return Core::IUAVGadget::qt_metacast(_clname);
}

int UAVObjectBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Core::IUAVGadget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
