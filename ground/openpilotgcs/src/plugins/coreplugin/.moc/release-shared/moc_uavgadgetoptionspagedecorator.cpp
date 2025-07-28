/****************************************************************************
** Meta object code from reading C++ file 'uavgadgetoptionspagedecorator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../uavgadgetoptionspagedecorator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uavgadgetoptionspagedecorator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__UAVGadgetOptionsPageDecorator_t {
    QByteArrayData data[6];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__UAVGadgetOptionsPageDecorator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__UAVGadgetOptionsPageDecorator_t qt_meta_stringdata_Core__UAVGadgetOptionsPageDecorator = {
    {
QT_MOC_LITERAL(0, 0, 35), // "Core::UAVGadgetOptionsPageDec..."
QT_MOC_LITERAL(1, 36, 11), // "updateState"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 18), // "cloneConfiguration"
QT_MOC_LITERAL(4, 68, 19), // "deleteConfiguration"
QT_MOC_LITERAL(5, 88, 10) // "textEdited"

    },
    "Core::UAVGadgetOptionsPageDecorator\0"
    "updateState\0\0cloneConfiguration\0"
    "deleteConfiguration\0textEdited"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__UAVGadgetOptionsPageDecorator[] = {

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
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    1,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void Core::UAVGadgetOptionsPageDecorator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UAVGadgetOptionsPageDecorator *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateState(); break;
        case 1: _t->cloneConfiguration(); break;
        case 2: _t->deleteConfiguration(); break;
        case 3: _t->textEdited((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::UAVGadgetOptionsPageDecorator::staticMetaObject = { {
    QMetaObject::SuperData::link<Core::IOptionsPage::staticMetaObject>(),
    qt_meta_stringdata_Core__UAVGadgetOptionsPageDecorator.data,
    qt_meta_data_Core__UAVGadgetOptionsPageDecorator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::UAVGadgetOptionsPageDecorator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::UAVGadgetOptionsPageDecorator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__UAVGadgetOptionsPageDecorator.stringdata0))
        return static_cast<void*>(this);
    return Core::IOptionsPage::qt_metacast(_clname);
}

int Core::UAVGadgetOptionsPageDecorator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Core::IOptionsPage::qt_metacall(_c, _id, _a);
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
