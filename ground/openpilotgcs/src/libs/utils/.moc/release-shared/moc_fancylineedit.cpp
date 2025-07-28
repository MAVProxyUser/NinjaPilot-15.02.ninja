/****************************************************************************
** Meta object code from reading C++ file 'fancylineedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../fancylineedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fancylineedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Utils__FancyLineEdit_t {
    QByteArrayData data[15];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Utils__FancyLineEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Utils__FancyLineEdit_t qt_meta_stringdata_Utils__FancyLineEdit = {
    {
QT_MOC_LITERAL(0, 0, 20), // "Utils::FancyLineEdit"
QT_MOC_LITERAL(1, 21, 9), // "setPixmap"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "pixmap"
QT_MOC_LITERAL(4, 39, 11), // "setHintText"
QT_MOC_LITERAL(5, 51, 2), // "ht"
QT_MOC_LITERAL(6, 54, 12), // "showHintText"
QT_MOC_LITERAL(7, 67, 12), // "hideHintText"
QT_MOC_LITERAL(8, 80, 4), // "side"
QT_MOC_LITERAL(9, 85, 4), // "Side"
QT_MOC_LITERAL(10, 90, 18), // "useLayoutDirection"
QT_MOC_LITERAL(11, 109, 19), // "menuTabFocusTrigger"
QT_MOC_LITERAL(12, 129, 8), // "hintText"
QT_MOC_LITERAL(13, 138, 4), // "Left"
QT_MOC_LITERAL(14, 143, 5) // "Right"

    },
    "Utils::FancyLineEdit\0setPixmap\0\0pixmap\0"
    "setHintText\0ht\0showHintText\0hideHintText\0"
    "side\0Side\0useLayoutDirection\0"
    "menuTabFocusTrigger\0hintText\0Left\0"
    "Right"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Utils__FancyLineEdit[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       5,   42, // properties
       1,   57, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       6,    0,   40,    2, 0x0a /* Public */,
       7,    0,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPixmap,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       3, QMetaType::QPixmap, 0x00095103,
       8, 0x80000000 | 9, 0x0009510b,
      10, QMetaType::Bool, 0x00095103,
      11, QMetaType::Bool, 0x00095103,
      12, QMetaType::QString, 0x00095103,

 // enums: name, alias, flags, count, data
       9,    9, 0x0,    2,   62,

 // enum data: key, value
      13, uint(Utils::FancyLineEdit::Left),
      14, uint(Utils::FancyLineEdit::Right),

       0        // eod
};

void Utils::FancyLineEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FancyLineEdit *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setPixmap((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 1: _t->setHintText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->showHintText(); break;
        case 3: _t->hideHintText(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FancyLineEdit *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPixmap*>(_v) = _t->pixmap(); break;
        case 1: *reinterpret_cast< Side*>(_v) = _t->side(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->useLayoutDirection(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->hasMenuTabFocusTrigger(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->hintText(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<FancyLineEdit *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPixmap(*reinterpret_cast< QPixmap*>(_v)); break;
        case 1: _t->setSide(*reinterpret_cast< Side*>(_v)); break;
        case 2: _t->setUseLayoutDirection(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setMenuTabFocusTrigger(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setHintText(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Utils::FancyLineEdit::staticMetaObject = { {
    QMetaObject::SuperData::link<QLineEdit::staticMetaObject>(),
    qt_meta_stringdata_Utils__FancyLineEdit.data,
    qt_meta_data_Utils__FancyLineEdit,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Utils::FancyLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Utils::FancyLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Utils__FancyLineEdit.stringdata0))
        return static_cast<void*>(this);
    return QLineEdit::qt_metacast(_clname);
}

int Utils::FancyLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
