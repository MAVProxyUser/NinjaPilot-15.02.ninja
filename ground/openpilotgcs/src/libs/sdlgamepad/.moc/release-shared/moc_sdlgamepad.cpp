/****************************************************************************
** Meta object code from reading C++ file 'sdlgamepad.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../sdlgamepad.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sdlgamepad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SDLGamepad_t {
    QByteArrayData data[17];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SDLGamepad_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SDLGamepad_t qt_meta_stringdata_SDLGamepad = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SDLGamepad"
QT_MOC_LITERAL(1, 11, 8), // "gamepads"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 5), // "count"
QT_MOC_LITERAL(4, 27, 11), // "buttonState"
QT_MOC_LITERAL(5, 39, 12), // "ButtonNumber"
QT_MOC_LITERAL(6, 52, 6), // "number"
QT_MOC_LITERAL(7, 59, 7), // "pressed"
QT_MOC_LITERAL(8, 67, 10), // "axesValues"
QT_MOC_LITERAL(9, 78, 10), // "QListInt16"
QT_MOC_LITERAL(10, 89, 6), // "values"
QT_MOC_LITERAL(11, 96, 4), // "init"
QT_MOC_LITERAL(12, 101, 4), // "quit"
QT_MOC_LITERAL(13, 106, 11), // "setTickRate"
QT_MOC_LITERAL(14, 118, 2), // "ms"
QT_MOC_LITERAL(15, 121, 10), // "setGamepad"
QT_MOC_LITERAL(16, 132, 5) // "index"

    },
    "SDLGamepad\0gamepads\0\0count\0buttonState\0"
    "ButtonNumber\0number\0pressed\0axesValues\0"
    "QListInt16\0values\0init\0quit\0setTickRate\0"
    "ms\0setGamepad\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SDLGamepad[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    2,   52,    2, 0x06 /* Public */,
       8,    1,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   60,    2, 0x0a /* Public */,
      12,    0,   61,    2, 0x0a /* Public */,
      13,    1,   62,    2, 0x0a /* Public */,
      15,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Bool,    6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Short,   14,
    QMetaType::Bool, QMetaType::Short,   16,

       0        // eod
};

void SDLGamepad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SDLGamepad *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->gamepads((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->buttonState((*reinterpret_cast< ButtonNumber(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->axesValues((*reinterpret_cast< QListInt16(*)>(_a[1]))); break;
        case 3: { bool _r = _t->init();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->quit(); break;
        case 5: _t->setTickRate((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 6: { bool _r = _t->setGamepad((*reinterpret_cast< qint16(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SDLGamepad::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SDLGamepad::gamepads)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SDLGamepad::*)(ButtonNumber , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SDLGamepad::buttonState)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SDLGamepad::*)(QListInt16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SDLGamepad::axesValues)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SDLGamepad::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_SDLGamepad.data,
    qt_meta_data_SDLGamepad,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SDLGamepad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SDLGamepad::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SDLGamepad.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int SDLGamepad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void SDLGamepad::gamepads(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SDLGamepad::buttonState(ButtonNumber _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SDLGamepad::axesValues(QListInt16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
