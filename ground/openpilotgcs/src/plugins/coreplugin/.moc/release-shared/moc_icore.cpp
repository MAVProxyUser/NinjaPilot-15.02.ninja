/****************************************************************************
** Meta object code from reading C++ file 'icore.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../icore.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'icore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__ICore_t {
    QByteArrayData data[11];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__ICore_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__ICore_t qt_meta_stringdata_Core__ICore = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Core::ICore"
QT_MOC_LITERAL(1, 12, 15), // "coreAboutToOpen"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "coreOpened"
QT_MOC_LITERAL(4, 40, 21), // "saveSettingsRequested"
QT_MOC_LITERAL(5, 62, 22), // "optionsDialogRequested"
QT_MOC_LITERAL(6, 85, 16), // "coreAboutToClose"
QT_MOC_LITERAL(7, 102, 20), // "contextAboutToChange"
QT_MOC_LITERAL(8, 123, 15), // "Core::IContext*"
QT_MOC_LITERAL(9, 139, 7), // "context"
QT_MOC_LITERAL(10, 147, 14) // "contextChanged"

    },
    "Core::ICore\0coreAboutToOpen\0\0coreOpened\0"
    "saveSettingsRequested\0optionsDialogRequested\0"
    "coreAboutToClose\0contextAboutToChange\0"
    "Core::IContext*\0context\0contextChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__ICore[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,
       5,    0,   52,    2, 0x06 /* Public */,
       6,    0,   53,    2, 0x06 /* Public */,
       7,    1,   54,    2, 0x06 /* Public */,
      10,    1,   57,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void Core::ICore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ICore *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->coreAboutToOpen(); break;
        case 1: _t->coreOpened(); break;
        case 2: _t->saveSettingsRequested(); break;
        case 3: _t->optionsDialogRequested(); break;
        case 4: _t->coreAboutToClose(); break;
        case 5: _t->contextAboutToChange((*reinterpret_cast< Core::IContext*(*)>(_a[1]))); break;
        case 6: _t->contextChanged((*reinterpret_cast< Core::IContext*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ICore::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ICore::coreAboutToOpen)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ICore::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ICore::coreOpened)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ICore::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ICore::saveSettingsRequested)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ICore::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ICore::optionsDialogRequested)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ICore::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ICore::coreAboutToClose)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ICore::*)(Core::IContext * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ICore::contextAboutToChange)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ICore::*)(Core::IContext * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ICore::contextChanged)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::ICore::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Core__ICore.data,
    qt_meta_data_Core__ICore,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::ICore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::ICore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__ICore.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Core::ICore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void Core::ICore::coreAboutToOpen()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Core::ICore::coreOpened()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Core::ICore::saveSettingsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Core::ICore::optionsDialogRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Core::ICore::coreAboutToClose()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Core::ICore::contextAboutToChange(Core::IContext * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Core::ICore::contextChanged(Core::IContext * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
