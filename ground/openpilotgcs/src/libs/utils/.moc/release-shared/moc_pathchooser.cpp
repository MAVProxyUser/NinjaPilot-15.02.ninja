/****************************************************************************
** Meta object code from reading C++ file 'pathchooser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../pathchooser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pathchooser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Utils__PathChooser_t {
    QByteArrayData data[19];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Utils__PathChooser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Utils__PathChooser_t qt_meta_stringdata_Utils__PathChooser = {
    {
QT_MOC_LITERAL(0, 0, 18), // "Utils::PathChooser"
QT_MOC_LITERAL(1, 19, 12), // "validChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 10), // "validState"
QT_MOC_LITERAL(4, 44, 7), // "changed"
QT_MOC_LITERAL(5, 52, 4), // "text"
QT_MOC_LITERAL(6, 57, 15), // "editingFinished"
QT_MOC_LITERAL(7, 73, 14), // "beforeBrowsing"
QT_MOC_LITERAL(8, 88, 16), // "browsingFinished"
QT_MOC_LITERAL(9, 105, 13), // "returnPressed"
QT_MOC_LITERAL(10, 119, 7), // "setPath"
QT_MOC_LITERAL(11, 127, 10), // "slotBrowse"
QT_MOC_LITERAL(12, 138, 4), // "path"
QT_MOC_LITERAL(13, 143, 17), // "promptDialogTitle"
QT_MOC_LITERAL(14, 161, 12), // "expectedKind"
QT_MOC_LITERAL(15, 174, 4), // "Kind"
QT_MOC_LITERAL(16, 179, 9), // "Directory"
QT_MOC_LITERAL(17, 189, 4), // "File"
QT_MOC_LITERAL(18, 194, 7) // "Command"

    },
    "Utils::PathChooser\0validChanged\0\0"
    "validState\0changed\0text\0editingFinished\0"
    "beforeBrowsing\0browsingFinished\0"
    "returnPressed\0setPath\0slotBrowse\0path\0"
    "promptDialogTitle\0expectedKind\0Kind\0"
    "Directory\0File\0Command"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Utils__PathChooser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       3,   74, // properties
       1,   83, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       1,    1,   60,    2, 0x06 /* Public */,
       4,    1,   63,    2, 0x06 /* Public */,
       6,    0,   66,    2, 0x06 /* Public */,
       7,    0,   67,    2, 0x06 /* Public */,
       8,    0,   68,    2, 0x06 /* Public */,
       9,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   70,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // properties: name, type, flags
      12, QMetaType::QString, 0x00095103,
      13, QMetaType::QString, 0x00095103,
      14, 0x80000000 | 15, 0x0009510b,

 // enums: name, alias, flags, count, data
      15,   15, 0x0,    3,   88,

 // enum data: key, value
      16, uint(Utils::PathChooser::Directory),
      17, uint(Utils::PathChooser::File),
      18, uint(Utils::PathChooser::Command),

       0        // eod
};

void Utils::PathChooser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PathChooser *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->validChanged(); break;
        case 1: _t->validChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->editingFinished(); break;
        case 4: _t->beforeBrowsing(); break;
        case 5: _t->browsingFinished(); break;
        case 6: _t->returnPressed(); break;
        case 7: _t->setPath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->slotBrowse(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PathChooser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathChooser::validChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PathChooser::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathChooser::validChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PathChooser::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathChooser::changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PathChooser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathChooser::editingFinished)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PathChooser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathChooser::beforeBrowsing)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PathChooser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathChooser::browsingFinished)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PathChooser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathChooser::returnPressed)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PathChooser *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->path(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->promptDialogTitle(); break;
        case 2: *reinterpret_cast< Kind*>(_v) = _t->expectedKind(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PathChooser *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPath(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setPromptDialogTitle(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setExpectedKind(*reinterpret_cast< Kind*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Utils::PathChooser::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Utils__PathChooser.data,
    qt_meta_data_Utils__PathChooser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Utils::PathChooser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Utils::PathChooser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Utils__PathChooser.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Utils::PathChooser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Utils::PathChooser::validChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Utils::PathChooser::validChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Utils::PathChooser::changed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Utils::PathChooser::editingFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Utils::PathChooser::beforeBrowsing()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Utils::PathChooser::browsingFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Utils::PathChooser::returnPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
