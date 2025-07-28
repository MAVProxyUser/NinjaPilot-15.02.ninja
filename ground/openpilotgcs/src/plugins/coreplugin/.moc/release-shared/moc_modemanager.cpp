/****************************************************************************
** Meta object code from reading C++ file 'modemanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../modemanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__ModeManager_t {
    QByteArrayData data[25];
    char stringdata0[324];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__ModeManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__ModeManager_t qt_meta_stringdata_Core__ModeManager = {
    {
QT_MOC_LITERAL(0, 0, 17), // "Core::ModeManager"
QT_MOC_LITERAL(1, 18, 24), // "currentModeAboutToChange"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 12), // "Core::IMode*"
QT_MOC_LITERAL(4, 57, 4), // "mode"
QT_MOC_LITERAL(5, 62, 18), // "currentModeChanged"
QT_MOC_LITERAL(6, 81, 12), // "newModeOrder"
QT_MOC_LITERAL(7, 94, 15), // "QVector<IMode*>"
QT_MOC_LITERAL(8, 110, 5), // "modes"
QT_MOC_LITERAL(9, 116, 12), // "activateMode"
QT_MOC_LITERAL(10, 129, 2), // "id"
QT_MOC_LITERAL(11, 132, 27), // "activateModeByWorkspaceName"
QT_MOC_LITERAL(12, 160, 21), // "setFocusToCurrentMode"
QT_MOC_LITERAL(13, 182, 13), // "triggerAction"
QT_MOC_LITERAL(14, 196, 8), // "actionId"
QT_MOC_LITERAL(15, 205, 11), // "objectAdded"
QT_MOC_LITERAL(16, 217, 3), // "obj"
QT_MOC_LITERAL(17, 221, 19), // "aboutToRemoveObject"
QT_MOC_LITERAL(18, 241, 23), // "currentTabAboutToChange"
QT_MOC_LITERAL(19, 265, 5), // "index"
QT_MOC_LITERAL(20, 271, 17), // "currentTabChanged"
QT_MOC_LITERAL(21, 289, 17), // "updateModeToolTip"
QT_MOC_LITERAL(22, 307, 8), // "tabMoved"
QT_MOC_LITERAL(23, 316, 4), // "from"
QT_MOC_LITERAL(24, 321, 2) // "to"

    },
    "Core::ModeManager\0currentModeAboutToChange\0"
    "\0Core::IMode*\0mode\0currentModeChanged\0"
    "newModeOrder\0QVector<IMode*>\0modes\0"
    "activateMode\0id\0activateModeByWorkspaceName\0"
    "setFocusToCurrentMode\0triggerAction\0"
    "actionId\0objectAdded\0obj\0aboutToRemoveObject\0"
    "currentTabAboutToChange\0index\0"
    "currentTabChanged\0updateModeToolTip\0"
    "tabMoved\0from\0to"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__ModeManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       5,    1,   82,    2, 0x06 /* Public */,
       6,    1,   85,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   88,    2, 0x0a /* Public */,
      11,    1,   91,    2, 0x0a /* Public */,
      12,    0,   94,    2, 0x0a /* Public */,
      13,    1,   95,    2, 0x0a /* Public */,
      15,    1,   98,    2, 0x08 /* Private */,
      17,    1,  101,    2, 0x08 /* Private */,
      18,    1,  104,    2, 0x08 /* Private */,
      20,    1,  107,    2, 0x08 /* Private */,
      21,    0,  110,    2, 0x08 /* Private */,
      22,    2,  111,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QObjectStar,   16,
    QMetaType::Void, QMetaType::QObjectStar,   16,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   23,   24,

       0        // eod
};

void Core::ModeManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ModeManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->currentModeAboutToChange((*reinterpret_cast< Core::IMode*(*)>(_a[1]))); break;
        case 1: _t->currentModeChanged((*reinterpret_cast< Core::IMode*(*)>(_a[1]))); break;
        case 2: _t->newModeOrder((*reinterpret_cast< QVector<IMode*>(*)>(_a[1]))); break;
        case 3: _t->activateMode((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->activateModeByWorkspaceName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->setFocusToCurrentMode(); break;
        case 6: _t->triggerAction((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->objectAdded((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 8: _t->aboutToRemoveObject((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 9: _t->currentTabAboutToChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->currentTabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->updateModeToolTip(); break;
        case 12: _t->tabMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ModeManager::*)(Core::IMode * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModeManager::currentModeAboutToChange)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ModeManager::*)(Core::IMode * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModeManager::currentModeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ModeManager::*)(QVector<IMode*> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModeManager::newModeOrder)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::ModeManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Core__ModeManager.data,
    qt_meta_data_Core__ModeManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::ModeManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::ModeManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__ModeManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Core::ModeManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Core::ModeManager::currentModeAboutToChange(Core::IMode * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Core::ModeManager::currentModeChanged(Core::IMode * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Core::ModeManager::newModeOrder(QVector<IMode*> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
