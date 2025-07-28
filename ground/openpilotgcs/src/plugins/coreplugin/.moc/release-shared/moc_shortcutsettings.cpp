/****************************************************************************
** Meta object code from reading C++ file 'shortcutsettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../dialogs/shortcutsettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shortcutsettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__Internal__ShortcutSettings_t {
    QByteArrayData data[13];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__Internal__ShortcutSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__Internal__ShortcutSettings_t qt_meta_stringdata_Core__Internal__ShortcutSettings = {
    {
QT_MOC_LITERAL(0, 0, 32), // "Core::Internal::ShortcutSettings"
QT_MOC_LITERAL(1, 33, 14), // "commandChanged"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 66, 7), // "current"
QT_MOC_LITERAL(5, 74, 13), // "filterChanged"
QT_MOC_LITERAL(6, 88, 1), // "f"
QT_MOC_LITERAL(7, 90, 10), // "keyChanged"
QT_MOC_LITERAL(8, 101, 16), // "resetKeySequence"
QT_MOC_LITERAL(9, 118, 17), // "removeKeySequence"
QT_MOC_LITERAL(10, 136, 12), // "importAction"
QT_MOC_LITERAL(11, 149, 12), // "exportAction"
QT_MOC_LITERAL(12, 162, 13) // "defaultAction"

    },
    "Core::Internal::ShortcutSettings\0"
    "commandChanged\0\0QTreeWidgetItem*\0"
    "current\0filterChanged\0f\0keyChanged\0"
    "resetKeySequence\0removeKeySequence\0"
    "importAction\0exportAction\0defaultAction"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__Internal__ShortcutSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       5,    1,   57,    2, 0x08 /* Private */,
       7,    0,   60,    2, 0x08 /* Private */,
       8,    0,   61,    2, 0x08 /* Private */,
       9,    0,   62,    2, 0x08 /* Private */,
      10,    0,   63,    2, 0x08 /* Private */,
      11,    0,   64,    2, 0x08 /* Private */,
      12,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Core::Internal::ShortcutSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ShortcutSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->commandChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->filterChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->keyChanged(); break;
        case 3: _t->resetKeySequence(); break;
        case 4: _t->removeKeySequence(); break;
        case 5: _t->importAction(); break;
        case 6: _t->exportAction(); break;
        case 7: _t->defaultAction(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::Internal::ShortcutSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<Core::IOptionsPage::staticMetaObject>(),
    qt_meta_stringdata_Core__Internal__ShortcutSettings.data,
    qt_meta_data_Core__Internal__ShortcutSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::Internal::ShortcutSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::Internal::ShortcutSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__Internal__ShortcutSettings.stringdata0))
        return static_cast<void*>(this);
    return Core::IOptionsPage::qt_metacast(_clname);
}

int Core::Internal::ShortcutSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Core::IOptionsPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
