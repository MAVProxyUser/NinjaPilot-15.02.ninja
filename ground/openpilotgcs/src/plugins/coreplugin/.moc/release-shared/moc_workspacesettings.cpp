/****************************************************************************
** Meta object code from reading C++ file 'workspacesettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../workspacesettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'workspacesettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__Internal__WorkspaceSettings_t {
    QByteArrayData data[17];
    char stringdata0[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__Internal__WorkspaceSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__Internal__WorkspaceSettings_t qt_meta_stringdata_Core__Internal__WorkspaceSettings = {
    {
QT_MOC_LITERAL(0, 0, 33), // "Core::Internal::WorkspaceSett..."
QT_MOC_LITERAL(1, 34, 21), // "tabBarSettingsApplied"
QT_MOC_LITERAL(2, 56, 0), // ""
QT_MOC_LITERAL(3, 57, 23), // "QTabWidget::TabPosition"
QT_MOC_LITERAL(4, 81, 3), // "pos"
QT_MOC_LITERAL(5, 85, 7), // "movable"
QT_MOC_LITERAL(6, 93, 15), // "selectWorkspace"
QT_MOC_LITERAL(7, 109, 5), // "index"
QT_MOC_LITERAL(8, 115, 5), // "store"
QT_MOC_LITERAL(9, 121, 25), // "numberOfWorkspacesChanged"
QT_MOC_LITERAL(10, 147, 5), // "value"
QT_MOC_LITERAL(11, 153, 10), // "textEdited"
QT_MOC_LITERAL(12, 164, 6), // "string"
QT_MOC_LITERAL(13, 171, 11), // "iconChanged"
QT_MOC_LITERAL(14, 183, 12), // "newModeOrder"
QT_MOC_LITERAL(15, 196, 15), // "QVector<IMode*>"
QT_MOC_LITERAL(16, 212, 5) // "modes"

    },
    "Core::Internal::WorkspaceSettings\0"
    "tabBarSettingsApplied\0\0QTabWidget::TabPosition\0"
    "pos\0movable\0selectWorkspace\0index\0"
    "store\0numberOfWorkspacesChanged\0value\0"
    "textEdited\0string\0iconChanged\0"
    "newModeOrder\0QVector<IMode*>\0modes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__Internal__WorkspaceSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   54,    2, 0x0a /* Public */,
       6,    1,   59,    2, 0x2a /* Public | MethodCloned */,
       9,    1,   62,    2, 0x0a /* Public */,
      11,    1,   65,    2, 0x0a /* Public */,
      13,    0,   68,    2, 0x0a /* Public */,
      14,    1,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    7,    8,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void Core::Internal::WorkspaceSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WorkspaceSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->tabBarSettingsApplied((*reinterpret_cast< QTabWidget::TabPosition(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->selectWorkspace((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->selectWorkspace((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->numberOfWorkspacesChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->textEdited((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->iconChanged(); break;
        case 6: _t->newModeOrder((*reinterpret_cast< QVector<IMode*>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WorkspaceSettings::*)(QTabWidget::TabPosition , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WorkspaceSettings::tabBarSettingsApplied)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::Internal::WorkspaceSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<IOptionsPage::staticMetaObject>(),
    qt_meta_stringdata_Core__Internal__WorkspaceSettings.data,
    qt_meta_data_Core__Internal__WorkspaceSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::Internal::WorkspaceSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::Internal::WorkspaceSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__Internal__WorkspaceSettings.stringdata0))
        return static_cast<void*>(this);
    return IOptionsPage::qt_metacast(_clname);
}

int Core::Internal::WorkspaceSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IOptionsPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Core::Internal::WorkspaceSettings::tabBarSettingsApplied(QTabWidget::TabPosition _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
