/****************************************************************************
** Meta object code from reading C++ file 'welcomemode.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../welcomemode.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'welcomemode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Welcome__WelcomeMode_t {
    QByteArrayData data[14];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Welcome__WelcomeMode_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Welcome__WelcomeMode_t qt_meta_stringdata_Welcome__WelcomeMode = {
    {
QT_MOC_LITERAL(0, 0, 20), // "Welcome::WelcomeMode"
QT_MOC_LITERAL(1, 21, 21), // "newVersionTextChanged"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 7), // "openUrl"
QT_MOC_LITERAL(4, 52, 3), // "url"
QT_MOC_LITERAL(5, 56, 8), // "openPage"
QT_MOC_LITERAL(6, 65, 4), // "page"
QT_MOC_LITERAL(7, 70, 13), // "triggerAction"
QT_MOC_LITERAL(8, 84, 8), // "actionId"
QT_MOC_LITERAL(9, 93, 20), // "networkResponseReady"
QT_MOC_LITERAL(10, 114, 14), // "QNetworkReply*"
QT_MOC_LITERAL(11, 129, 5), // "reply"
QT_MOC_LITERAL(12, 135, 13), // "versionString"
QT_MOC_LITERAL(13, 149, 14) // "newVersionText"

    },
    "Welcome::WelcomeMode\0newVersionTextChanged\0"
    "\0openUrl\0url\0openPage\0page\0triggerAction\0"
    "actionId\0networkResponseReady\0"
    "QNetworkReply*\0reply\0versionString\0"
    "newVersionText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Welcome__WelcomeMode[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       2,   52, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   40,    2, 0x0a /* Public */,
       5,    1,   43,    2, 0x0a /* Public */,
       7,    1,   46,    2, 0x0a /* Public */,
       9,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, 0x80000000 | 10,   11,

 // properties: name, type, flags
      12, QMetaType::QString, 0x00095401,
      13, QMetaType::QString, 0x00495001,

 // properties: notify_signal_id
       0,
       0,

       0        // eod
};

void Welcome::WelcomeMode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WelcomeMode *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newVersionTextChanged(); break;
        case 1: _t->openUrl((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->openPage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->triggerAction((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->networkResponseReady((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WelcomeMode::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WelcomeMode::newVersionTextChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<WelcomeMode *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->versionString(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->newVersionText(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Welcome::WelcomeMode::staticMetaObject = { {
    QMetaObject::SuperData::link<Core::IMode::staticMetaObject>(),
    qt_meta_stringdata_Welcome__WelcomeMode.data,
    qt_meta_data_Welcome__WelcomeMode,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Welcome::WelcomeMode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Welcome::WelcomeMode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Welcome__WelcomeMode.stringdata0))
        return static_cast<void*>(this);
    return Core::IMode::qt_metacast(_clname);
}

int Welcome::WelcomeMode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Core::IMode::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Welcome::WelcomeMode::newVersionTextChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
