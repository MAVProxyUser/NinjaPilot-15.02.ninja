/****************************************************************************
** Meta object code from reading C++ file 'checkablemessagebox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../checkablemessagebox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'checkablemessagebox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Utils__CheckableMessageBox_t {
    QByteArrayData data[13];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Utils__CheckableMessageBox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Utils__CheckableMessageBox_t qt_meta_stringdata_Utils__CheckableMessageBox = {
    {
QT_MOC_LITERAL(0, 0, 26), // "Utils::CheckableMessageBox"
QT_MOC_LITERAL(1, 27, 11), // "slotClicked"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 16), // "QAbstractButton*"
QT_MOC_LITERAL(4, 57, 1), // "b"
QT_MOC_LITERAL(5, 59, 4), // "text"
QT_MOC_LITERAL(6, 64, 10), // "iconPixmap"
QT_MOC_LITERAL(7, 75, 9), // "isChecked"
QT_MOC_LITERAL(8, 85, 12), // "checkBoxText"
QT_MOC_LITERAL(9, 98, 7), // "buttons"
QT_MOC_LITERAL(10, 106, 33), // "QDialogButtonBox::StandardBut..."
QT_MOC_LITERAL(11, 140, 13), // "defaultButton"
QT_MOC_LITERAL(12, 154, 32) // "QDialogButtonBox::StandardButton"

    },
    "Utils::CheckableMessageBox\0slotClicked\0"
    "\0QAbstractButton*\0b\0text\0iconPixmap\0"
    "isChecked\0checkBoxText\0buttons\0"
    "QDialogButtonBox::StandardButtons\0"
    "defaultButton\0QDialogButtonBox::StandardButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Utils__CheckableMessageBox[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       6,   22, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // properties: name, type, flags
       5, QMetaType::QString, 0x00095103,
       6, QMetaType::QPixmap, 0x00095103,
       7, QMetaType::Bool, 0x00095003,
       8, QMetaType::QString, 0x00095103,
       9, 0x80000000 | 10, 0x0009500b,
      11, 0x80000000 | 12, 0x0009510b,

       0        // eod
};

void Utils::CheckableMessageBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CheckableMessageBox *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slotClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CheckableMessageBox *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->text(); break;
        case 1: *reinterpret_cast< QPixmap*>(_v) = _t->iconPixmap(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isChecked(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->checkBoxText(); break;
        case 4: *reinterpret_cast< QDialogButtonBox::StandardButtons*>(_v) = _t->standardButtons(); break;
        case 5: *reinterpret_cast< QDialogButtonBox::StandardButton*>(_v) = _t->defaultButton(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<CheckableMessageBox *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setText(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setIconPixmap(*reinterpret_cast< QPixmap*>(_v)); break;
        case 2: _t->setChecked(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setCheckBoxText(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setStandardButtons(*reinterpret_cast< QDialogButtonBox::StandardButtons*>(_v)); break;
        case 5: _t->setDefaultButton(*reinterpret_cast< QDialogButtonBox::StandardButton*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

static const QMetaObject::SuperData qt_meta_extradata_Utils__CheckableMessageBox[] = {
    QMetaObject::SuperData::link<QDialogButtonBox::staticMetaObject>(),
    nullptr
};

QT_INIT_METAOBJECT const QMetaObject Utils::CheckableMessageBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Utils__CheckableMessageBox.data,
    qt_meta_data_Utils__CheckableMessageBox,
    qt_static_metacall,
    qt_meta_extradata_Utils__CheckableMessageBox,
    nullptr
} };


const QMetaObject *Utils::CheckableMessageBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Utils::CheckableMessageBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Utils__CheckableMessageBox.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Utils::CheckableMessageBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
