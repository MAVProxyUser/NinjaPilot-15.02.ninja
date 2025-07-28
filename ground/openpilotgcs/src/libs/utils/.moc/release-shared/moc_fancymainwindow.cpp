/****************************************************************************
** Meta object code from reading C++ file 'fancymainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../fancymainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fancymainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Utils__FancyMainWindow_t {
    QByteArrayData data[10];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Utils__FancyMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Utils__FancyMainWindow_t qt_meta_stringdata_Utils__FancyMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 22), // "Utils::FancyMainWindow"
QT_MOC_LITERAL(1, 23, 11), // "resetLayout"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 9), // "setLocked"
QT_MOC_LITERAL(4, 46, 6), // "locked"
QT_MOC_LITERAL(5, 53, 21), // "setDockActionsVisible"
QT_MOC_LITERAL(6, 75, 1), // "v"
QT_MOC_LITERAL(7, 77, 21), // "onDockActionTriggered"
QT_MOC_LITERAL(8, 99, 22), // "onDockVisibilityChange"
QT_MOC_LITERAL(9, 122, 17) // "onTopLevelChanged"

    },
    "Utils::FancyMainWindow\0resetLayout\0\0"
    "setLocked\0locked\0setDockActionsVisible\0"
    "v\0onDockActionTriggered\0onDockVisibilityChange\0"
    "onTopLevelChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Utils__FancyMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   45,    2, 0x0a /* Public */,
       5,    1,   48,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x08 /* Private */,
       8,    1,   52,    2, 0x08 /* Private */,
       9,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

       0        // eod
};

void Utils::FancyMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FancyMainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->resetLayout(); break;
        case 1: _t->setLocked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setDockActionsVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->onDockActionTriggered(); break;
        case 4: _t->onDockVisibilityChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->onTopLevelChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FancyMainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FancyMainWindow::resetLayout)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Utils::FancyMainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Utils__FancyMainWindow.data,
    qt_meta_data_Utils__FancyMainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Utils::FancyMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Utils::FancyMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Utils__FancyMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Utils::FancyMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Utils::FancyMainWindow::resetLayout()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
