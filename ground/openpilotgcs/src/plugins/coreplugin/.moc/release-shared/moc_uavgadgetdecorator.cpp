/****************************************************************************
** Meta object code from reading C++ file 'uavgadgetdecorator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../uavgadgetdecorator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uavgadgetdecorator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__UAVGadgetDecorator_t {
    QByteArrayData data[12];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__UAVGadgetDecorator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__UAVGadgetDecorator_t qt_meta_stringdata_Core__UAVGadgetDecorator = {
    {
QT_MOC_LITERAL(0, 0, 24), // "Core::UAVGadgetDecorator"
QT_MOC_LITERAL(1, 25, 20), // "configurationChanged"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 24), // "IUAVGadgetConfiguration*"
QT_MOC_LITERAL(4, 72, 6), // "config"
QT_MOC_LITERAL(5, 79, 18), // "configurationAdded"
QT_MOC_LITERAL(6, 98, 24), // "configurationToBeDeleted"
QT_MOC_LITERAL(7, 123, 24), // "configurationNameChanged"
QT_MOC_LITERAL(8, 148, 7), // "oldName"
QT_MOC_LITERAL(9, 156, 7), // "newName"
QT_MOC_LITERAL(10, 164, 17), // "loadConfiguration"
QT_MOC_LITERAL(11, 182, 5) // "index"

    },
    "Core::UAVGadgetDecorator\0configurationChanged\0"
    "\0IUAVGadgetConfiguration*\0config\0"
    "configurationAdded\0configurationToBeDeleted\0"
    "configurationNameChanged\0oldName\0"
    "newName\0loadConfiguration\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__UAVGadgetDecorator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x0a /* Public */,
       6,    1,   45,    2, 0x0a /* Public */,
       7,    3,   48,    2, 0x0a /* Public */,
      10,    1,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString,    4,    8,    9,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void Core::UAVGadgetDecorator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UAVGadgetDecorator *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->configurationChanged((*reinterpret_cast< IUAVGadgetConfiguration*(*)>(_a[1]))); break;
        case 1: _t->configurationAdded((*reinterpret_cast< IUAVGadgetConfiguration*(*)>(_a[1]))); break;
        case 2: _t->configurationToBeDeleted((*reinterpret_cast< IUAVGadgetConfiguration*(*)>(_a[1]))); break;
        case 3: _t->configurationNameChanged((*reinterpret_cast< IUAVGadgetConfiguration*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 4: _t->loadConfiguration((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::UAVGadgetDecorator::staticMetaObject = { {
    QMetaObject::SuperData::link<IUAVGadget::staticMetaObject>(),
    qt_meta_stringdata_Core__UAVGadgetDecorator.data,
    qt_meta_data_Core__UAVGadgetDecorator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::UAVGadgetDecorator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::UAVGadgetDecorator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__UAVGadgetDecorator.stringdata0))
        return static_cast<void*>(this);
    return IUAVGadget::qt_metacast(_clname);
}

int Core::UAVGadgetDecorator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IUAVGadget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
