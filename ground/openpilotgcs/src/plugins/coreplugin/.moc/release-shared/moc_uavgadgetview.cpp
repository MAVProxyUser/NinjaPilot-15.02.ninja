/****************************************************************************
** Meta object code from reading C++ file 'uavgadgetview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../uavgadgetmanager/uavgadgetview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uavgadgetview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__Internal__UAVGadgetView_t {
    QByteArrayData data[8];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__Internal__UAVGadgetView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__Internal__UAVGadgetView_t qt_meta_stringdata_Core__Internal__UAVGadgetView = {
    {
QT_MOC_LITERAL(0, 0, 29), // "Core::Internal::UAVGadgetView"
QT_MOC_LITERAL(1, 30, 9), // "closeView"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 22), // "listSelectionActivated"
QT_MOC_LITERAL(4, 64, 5), // "index"
QT_MOC_LITERAL(5, 70, 20), // "currentGadgetChanged"
QT_MOC_LITERAL(6, 91, 11), // "IUAVGadget*"
QT_MOC_LITERAL(7, 103, 6) // "gadget"

    },
    "Core::Internal::UAVGadgetView\0closeView\0"
    "\0listSelectionActivated\0index\0"
    "currentGadgetChanged\0IUAVGadget*\0"
    "gadget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__Internal__UAVGadgetView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    1,   30,    2, 0x08 /* Private */,
       5,    1,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void Core::Internal::UAVGadgetView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UAVGadgetView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->closeView(); break;
        case 1: _t->listSelectionActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->currentGadgetChanged((*reinterpret_cast< IUAVGadget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::Internal::UAVGadgetView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Core__Internal__UAVGadgetView.data,
    qt_meta_data_Core__Internal__UAVGadgetView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::Internal::UAVGadgetView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::Internal::UAVGadgetView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__Internal__UAVGadgetView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Core::Internal::UAVGadgetView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
