/****************************************************************************
** Meta object code from reading C++ file 'pluginmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../pluginmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pluginmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExtensionSystem__PluginManager_t {
    QByteArrayData data[11];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExtensionSystem__PluginManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExtensionSystem__PluginManager_t qt_meta_stringdata_ExtensionSystem__PluginManager = {
    {
QT_MOC_LITERAL(0, 0, 30), // "ExtensionSystem::PluginManager"
QT_MOC_LITERAL(1, 31, 11), // "objectAdded"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 3), // "obj"
QT_MOC_LITERAL(4, 48, 19), // "aboutToRemoveObject"
QT_MOC_LITERAL(5, 68, 21), // "pluginAboutToBeLoaded"
QT_MOC_LITERAL(6, 90, 28), // "ExtensionSystem::PluginSpec*"
QT_MOC_LITERAL(7, 119, 10), // "pluginSpec"
QT_MOC_LITERAL(8, 130, 14), // "pluginsChanged"
QT_MOC_LITERAL(9, 145, 16), // "pluginsLoadEnded"
QT_MOC_LITERAL(10, 162, 10) // "startTests"

    },
    "ExtensionSystem::PluginManager\0"
    "objectAdded\0\0obj\0aboutToRemoveObject\0"
    "pluginAboutToBeLoaded\0"
    "ExtensionSystem::PluginSpec*\0pluginSpec\0"
    "pluginsChanged\0pluginsLoadEnded\0"
    "startTests"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExtensionSystem__PluginManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       5,    1,   50,    2, 0x06 /* Public */,
       8,    0,   53,    2, 0x06 /* Public */,
       9,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QObjectStar,    3,
    QMetaType::Void, QMetaType::QObjectStar,    3,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ExtensionSystem::PluginManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PluginManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->objectAdded((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 1: _t->aboutToRemoveObject((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 2: _t->pluginAboutToBeLoaded((*reinterpret_cast< ExtensionSystem::PluginSpec*(*)>(_a[1]))); break;
        case 3: _t->pluginsChanged(); break;
        case 4: _t->pluginsLoadEnded(); break;
        case 5: _t->startTests(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PluginManager::*)(QObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PluginManager::objectAdded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PluginManager::*)(QObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PluginManager::aboutToRemoveObject)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PluginManager::*)(ExtensionSystem::PluginSpec * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PluginManager::pluginAboutToBeLoaded)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PluginManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PluginManager::pluginsChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PluginManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PluginManager::pluginsLoadEnded)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ExtensionSystem::PluginManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ExtensionSystem__PluginManager.data,
    qt_meta_data_ExtensionSystem__PluginManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ExtensionSystem::PluginManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExtensionSystem::PluginManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExtensionSystem__PluginManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ExtensionSystem::PluginManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void ExtensionSystem::PluginManager::objectAdded(QObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExtensionSystem::PluginManager::aboutToRemoveObject(QObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ExtensionSystem::PluginManager::pluginAboutToBeLoaded(ExtensionSystem::PluginSpec * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ExtensionSystem::PluginManager::pluginsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ExtensionSystem::PluginManager::pluginsLoadEnded()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
