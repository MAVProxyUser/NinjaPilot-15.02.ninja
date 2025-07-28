/****************************************************************************
** Meta object code from reading C++ file 'settingsdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../dialogs/settingsdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__Internal__SettingsDialog_t {
    QByteArrayData data[12];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__Internal__SettingsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__Internal__SettingsDialog_t qt_meta_stringdata_Core__Internal__SettingsDialog = {
    {
QT_MOC_LITERAL(0, 0, 30), // "Core::Internal::SettingsDialog"
QT_MOC_LITERAL(1, 31, 19), // "settingsDialogShown"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 31), // "Core::Internal::SettingsDialog*"
QT_MOC_LITERAL(4, 84, 21), // "settingsDialogRemoved"
QT_MOC_LITERAL(5, 106, 20), // "categoryItemSelected"
QT_MOC_LITERAL(6, 127, 4), // "done"
QT_MOC_LITERAL(7, 132, 14), // "onItemSelected"
QT_MOC_LITERAL(8, 147, 18), // "onCategorySelected"
QT_MOC_LITERAL(9, 166, 6), // "accept"
QT_MOC_LITERAL(10, 173, 6), // "reject"
QT_MOC_LITERAL(11, 180, 5) // "apply"

    },
    "Core::Internal::SettingsDialog\0"
    "settingsDialogShown\0\0"
    "Core::Internal::SettingsDialog*\0"
    "settingsDialogRemoved\0categoryItemSelected\0"
    "done\0onItemSelected\0onCategorySelected\0"
    "accept\0reject\0apply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__Internal__SettingsDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    0,   62,    2, 0x06 /* Public */,
       5,    0,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   64,    2, 0x0a /* Public */,
       7,    0,   67,    2, 0x08 /* Private */,
       8,    0,   68,    2, 0x08 /* Private */,
       9,    0,   69,    2, 0x08 /* Private */,
      10,    0,   70,    2, 0x08 /* Private */,
      11,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Core::Internal::SettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingsDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->settingsDialogShown((*reinterpret_cast< Core::Internal::SettingsDialog*(*)>(_a[1]))); break;
        case 1: _t->settingsDialogRemoved(); break;
        case 2: _t->categoryItemSelected(); break;
        case 3: _t->done((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onItemSelected(); break;
        case 5: _t->onCategorySelected(); break;
        case 6: _t->accept(); break;
        case 7: _t->reject(); break;
        case 8: _t->apply(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Core::Internal::SettingsDialog* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingsDialog::*)(Core::Internal::SettingsDialog * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsDialog::settingsDialogShown)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingsDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsDialog::settingsDialogRemoved)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SettingsDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsDialog::categoryItemSelected)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::Internal::SettingsDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Core__Internal__SettingsDialog.data,
    qt_meta_data_Core__Internal__SettingsDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::Internal::SettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::Internal::SettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__Internal__SettingsDialog.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "::Ui::SettingsDialog"))
        return static_cast< ::Ui::SettingsDialog*>(this);
    return QDialog::qt_metacast(_clname);
}

int Core::Internal::SettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Core::Internal::SettingsDialog::settingsDialogShown(Core::Internal::SettingsDialog * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Core::Internal::SettingsDialog::settingsDialogRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Core::Internal::SettingsDialog::categoryItemSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
