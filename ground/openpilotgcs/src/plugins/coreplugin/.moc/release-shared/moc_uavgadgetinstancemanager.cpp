/****************************************************************************
** Meta object code from reading C++ file 'uavgadgetinstancemanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../uavgadgetinstancemanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uavgadgetinstancemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__UAVGadgetInstanceManager_t {
    QByteArrayData data[14];
    char stringdata0[259];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__UAVGadgetInstanceManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__UAVGadgetInstanceManager_t qt_meta_stringdata_Core__UAVGadgetInstanceManager = {
    {
QT_MOC_LITERAL(0, 0, 30), // "Core::UAVGadgetInstanceManager"
QT_MOC_LITERAL(1, 31, 20), // "configurationChanged"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 24), // "IUAVGadgetConfiguration*"
QT_MOC_LITERAL(4, 78, 6), // "config"
QT_MOC_LITERAL(5, 85, 18), // "configurationAdded"
QT_MOC_LITERAL(6, 104, 24), // "configurationToBeDeleted"
QT_MOC_LITERAL(7, 129, 24), // "configurationNameChanged"
QT_MOC_LITERAL(8, 154, 7), // "oldName"
QT_MOC_LITERAL(9, 162, 7), // "newName"
QT_MOC_LITERAL(10, 170, 19), // "settingsDialogShown"
QT_MOC_LITERAL(11, 190, 31), // "Core::Internal::SettingsDialog*"
QT_MOC_LITERAL(12, 222, 14), // "settingsDialog"
QT_MOC_LITERAL(13, 237, 21) // "settingsDialogRemoved"

    },
    "Core::UAVGadgetInstanceManager\0"
    "configurationChanged\0\0IUAVGadgetConfiguration*\0"
    "config\0configurationAdded\0"
    "configurationToBeDeleted\0"
    "configurationNameChanged\0oldName\0"
    "newName\0settingsDialogShown\0"
    "Core::Internal::SettingsDialog*\0"
    "settingsDialog\0settingsDialogRemoved"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__UAVGadgetInstanceManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,
       7,    3,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   60,    2, 0x0a /* Public */,
      13,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString,    4,    8,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,

       0        // eod
};

void Core::UAVGadgetInstanceManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UAVGadgetInstanceManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->configurationChanged((*reinterpret_cast< IUAVGadgetConfiguration*(*)>(_a[1]))); break;
        case 1: _t->configurationAdded((*reinterpret_cast< IUAVGadgetConfiguration*(*)>(_a[1]))); break;
        case 2: _t->configurationToBeDeleted((*reinterpret_cast< IUAVGadgetConfiguration*(*)>(_a[1]))); break;
        case 3: _t->configurationNameChanged((*reinterpret_cast< IUAVGadgetConfiguration*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 4: _t->settingsDialogShown((*reinterpret_cast< Core::Internal::SettingsDialog*(*)>(_a[1]))); break;
        case 5: _t->settingsDialogRemoved(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IUAVGadgetConfiguration* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IUAVGadgetConfiguration* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IUAVGadgetConfiguration* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IUAVGadgetConfiguration* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UAVGadgetInstanceManager::*)(IUAVGadgetConfiguration * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVGadgetInstanceManager::configurationChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UAVGadgetInstanceManager::*)(IUAVGadgetConfiguration * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVGadgetInstanceManager::configurationAdded)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UAVGadgetInstanceManager::*)(IUAVGadgetConfiguration * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVGadgetInstanceManager::configurationToBeDeleted)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UAVGadgetInstanceManager::*)(IUAVGadgetConfiguration * , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVGadgetInstanceManager::configurationNameChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::UAVGadgetInstanceManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Core__UAVGadgetInstanceManager.data,
    qt_meta_data_Core__UAVGadgetInstanceManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::UAVGadgetInstanceManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::UAVGadgetInstanceManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__UAVGadgetInstanceManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Core::UAVGadgetInstanceManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Core::UAVGadgetInstanceManager::configurationChanged(IUAVGadgetConfiguration * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Core::UAVGadgetInstanceManager::configurationAdded(IUAVGadgetConfiguration * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Core::UAVGadgetInstanceManager::configurationToBeDeleted(IUAVGadgetConfiguration * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Core::UAVGadgetInstanceManager::configurationNameChanged(IUAVGadgetConfiguration * _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
