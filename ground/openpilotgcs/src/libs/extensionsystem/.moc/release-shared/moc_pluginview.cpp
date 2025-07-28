/****************************************************************************
** Meta object code from reading C++ file 'pluginview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../pluginview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pluginview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExtensionSystem__PluginView_t {
    QByteArrayData data[12];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExtensionSystem__PluginView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExtensionSystem__PluginView_t qt_meta_stringdata_ExtensionSystem__PluginView = {
    {
QT_MOC_LITERAL(0, 0, 27), // "ExtensionSystem::PluginView"
QT_MOC_LITERAL(1, 28, 20), // "currentPluginChanged"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 28), // "ExtensionSystem::PluginSpec*"
QT_MOC_LITERAL(4, 79, 4), // "spec"
QT_MOC_LITERAL(5, 84, 15), // "pluginActivated"
QT_MOC_LITERAL(6, 100, 10), // "updateList"
QT_MOC_LITERAL(7, 111, 12), // "selectPlugin"
QT_MOC_LITERAL(8, 124, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(9, 141, 7), // "current"
QT_MOC_LITERAL(10, 149, 14), // "activatePlugin"
QT_MOC_LITERAL(11, 164, 4) // "item"

    },
    "ExtensionSystem::PluginView\0"
    "currentPluginChanged\0\0"
    "ExtensionSystem::PluginSpec*\0spec\0"
    "pluginActivated\0updateList\0selectPlugin\0"
    "QTreeWidgetItem*\0current\0activatePlugin\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExtensionSystem__PluginView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   45,    2, 0x08 /* Private */,
       7,    1,   46,    2, 0x08 /* Private */,
      10,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,   11,

       0        // eod
};

void ExtensionSystem::PluginView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PluginView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->currentPluginChanged((*reinterpret_cast< ExtensionSystem::PluginSpec*(*)>(_a[1]))); break;
        case 1: _t->pluginActivated((*reinterpret_cast< ExtensionSystem::PluginSpec*(*)>(_a[1]))); break;
        case 2: _t->updateList(); break;
        case 3: _t->selectPlugin((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->activatePlugin((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PluginView::*)(ExtensionSystem::PluginSpec * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PluginView::currentPluginChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PluginView::*)(ExtensionSystem::PluginSpec * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PluginView::pluginActivated)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ExtensionSystem::PluginView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ExtensionSystem__PluginView.data,
    qt_meta_data_ExtensionSystem__PluginView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ExtensionSystem::PluginView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExtensionSystem::PluginView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExtensionSystem__PluginView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ExtensionSystem::PluginView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void ExtensionSystem::PluginView::currentPluginChanged(ExtensionSystem::PluginSpec * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExtensionSystem::PluginView::pluginActivated(ExtensionSystem::PluginSpec * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
