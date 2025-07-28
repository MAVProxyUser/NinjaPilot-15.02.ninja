/****************************************************************************
** Meta object code from reading C++ file 'sidebar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../sidebar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sidebar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__SideBar_t {
    QByteArrayData data[5];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__SideBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__SideBar_t qt_meta_stringdata_Core__SideBar = {
    {
QT_MOC_LITERAL(0, 0, 13), // "Core::SideBar"
QT_MOC_LITERAL(1, 14, 14), // "splitSubWidget"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 14), // "closeSubWidget"
QT_MOC_LITERAL(4, 45, 13) // "updateWidgets"

    },
    "Core::SideBar\0splitSubWidget\0\0"
    "closeSubWidget\0updateWidgets"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__SideBar[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Core::SideBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SideBar *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->splitSubWidget(); break;
        case 1: _t->closeSubWidget(); break;
        case 2: _t->updateWidgets(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject Core::SideBar::staticMetaObject = { {
    QMetaObject::SuperData::link<MiniSplitter::staticMetaObject>(),
    qt_meta_stringdata_Core__SideBar.data,
    qt_meta_data_Core__SideBar,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::SideBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::SideBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__SideBar.stringdata0))
        return static_cast<void*>(this);
    return MiniSplitter::qt_metacast(_clname);
}

int Core::SideBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MiniSplitter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_Core__Internal__SideBarWidget_t {
    QByteArrayData data[6];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__Internal__SideBarWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__Internal__SideBarWidget_t qt_meta_stringdata_Core__Internal__SideBarWidget = {
    {
QT_MOC_LITERAL(0, 0, 29), // "Core::Internal::SideBarWidget"
QT_MOC_LITERAL(1, 30, 7), // "splitMe"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 7), // "closeMe"
QT_MOC_LITERAL(4, 47, 20), // "currentWidgetChanged"
QT_MOC_LITERAL(5, 68, 15) // "setCurrentIndex"

    },
    "Core::Internal::SideBarWidget\0splitMe\0"
    "\0closeMe\0currentWidgetChanged\0"
    "setCurrentIndex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__Internal__SideBarWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Core::Internal::SideBarWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SideBarWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->splitMe(); break;
        case 1: _t->closeMe(); break;
        case 2: _t->currentWidgetChanged(); break;
        case 3: _t->setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SideBarWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SideBarWidget::splitMe)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SideBarWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SideBarWidget::closeMe)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SideBarWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SideBarWidget::currentWidgetChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::Internal::SideBarWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Core__Internal__SideBarWidget.data,
    qt_meta_data_Core__Internal__SideBarWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::Internal::SideBarWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::Internal::SideBarWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__Internal__SideBarWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Core::Internal::SideBarWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void Core::Internal::SideBarWidget::splitMe()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Core::Internal::SideBarWidget::closeMe()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Core::Internal::SideBarWidget::currentWidgetChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
struct qt_meta_stringdata_Core__Internal__ComboBox_t {
    QByteArrayData data[1];
    char stringdata0[25];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__Internal__ComboBox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__Internal__ComboBox_t qt_meta_stringdata_Core__Internal__ComboBox = {
    {
QT_MOC_LITERAL(0, 0, 24) // "Core::Internal::ComboBox"

    },
    "Core::Internal::ComboBox"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__Internal__ComboBox[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Core::Internal::ComboBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject Core::Internal::ComboBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QComboBox::staticMetaObject>(),
    qt_meta_stringdata_Core__Internal__ComboBox.data,
    qt_meta_data_Core__Internal__ComboBox,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::Internal::ComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::Internal::ComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__Internal__ComboBox.stringdata0))
        return static_cast<void*>(this);
    return QComboBox::qt_metacast(_clname);
}

int Core::Internal::ComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
