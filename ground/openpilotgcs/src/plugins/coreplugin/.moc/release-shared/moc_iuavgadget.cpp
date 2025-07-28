/****************************************************************************
** Meta object code from reading C++ file 'iuavgadget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../iuavgadget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iuavgadget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__IUAVGadget_t {
    QByteArrayData data[7];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__IUAVGadget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__IUAVGadget_t qt_meta_stringdata_Core__IUAVGadget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "Core::IUAVGadget"
QT_MOC_LITERAL(1, 17, 20), // "configurationChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 24), // "IUAVGadgetConfiguration*"
QT_MOC_LITERAL(4, 64, 18), // "configurationAdded"
QT_MOC_LITERAL(5, 83, 24), // "configurationToBeDeleted"
QT_MOC_LITERAL(6, 108, 24) // "configurationNameChanged"

    },
    "Core::IUAVGadget\0configurationChanged\0"
    "\0IUAVGadgetConfiguration*\0configurationAdded\0"
    "configurationToBeDeleted\0"
    "configurationNameChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__IUAVGadget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       5,    1,   40,    2, 0x0a /* Public */,
       6,    3,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString,    2,    2,    2,

       0        // eod
};

void Core::IUAVGadget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IUAVGadget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->configurationChanged((*reinterpret_cast< IUAVGadgetConfiguration*(*)>(_a[1]))); break;
        case 1: _t->configurationAdded((*reinterpret_cast< IUAVGadgetConfiguration*(*)>(_a[1]))); break;
        case 2: _t->configurationToBeDeleted((*reinterpret_cast< IUAVGadgetConfiguration*(*)>(_a[1]))); break;
        case 3: _t->configurationNameChanged((*reinterpret_cast< IUAVGadgetConfiguration*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::IUAVGadget::staticMetaObject = { {
    QMetaObject::SuperData::link<IContext::staticMetaObject>(),
    qt_meta_stringdata_Core__IUAVGadget.data,
    qt_meta_data_Core__IUAVGadget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::IUAVGadget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::IUAVGadget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__IUAVGadget.stringdata0))
        return static_cast<void*>(this);
    return IContext::qt_metacast(_clname);
}

int Core::IUAVGadget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IContext::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
