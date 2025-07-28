/****************************************************************************
** Meta object code from reading C++ file 'ipconnectionconfiguration.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ipconnectionconfiguration.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ipconnectionconfiguration.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IPconnectionConfiguration_t {
    QByteArrayData data[8];
    char stringdata0[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IPconnectionConfiguration_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IPconnectionConfiguration_t qt_meta_stringdata_IPconnectionConfiguration = {
    {
QT_MOC_LITERAL(0, 0, 25), // "IPconnectionConfiguration"
QT_MOC_LITERAL(1, 26, 11), // "setHostName"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 8), // "HostName"
QT_MOC_LITERAL(4, 48, 7), // "setPort"
QT_MOC_LITERAL(5, 56, 4), // "Port"
QT_MOC_LITERAL(6, 61, 9), // "setUseTCP"
QT_MOC_LITERAL(7, 71, 6) // "UseTCP"

    },
    "IPconnectionConfiguration\0setHostName\0"
    "\0HostName\0setPort\0Port\0setUseTCP\0"
    "UseTCP"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IPconnectionConfiguration[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       3,   38, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       6,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,

 // properties: name, type, flags
       3, QMetaType::QString, 0x00095103,
       5, QMetaType::Int, 0x00095103,
       7, QMetaType::Int, 0x00095103,

       0        // eod
};

void IPconnectionConfiguration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IPconnectionConfiguration *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setHostName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->setPort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setUseTCP((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<IPconnectionConfiguration *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->HostName(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->Port(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->UseTCP(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<IPconnectionConfiguration *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setHostName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setPort(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setUseTCP(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject IPconnectionConfiguration::staticMetaObject = { {
    QMetaObject::SuperData::link<IUAVGadgetConfiguration::staticMetaObject>(),
    qt_meta_stringdata_IPconnectionConfiguration.data,
    qt_meta_data_IPconnectionConfiguration,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IPconnectionConfiguration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IPconnectionConfiguration::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IPconnectionConfiguration.stringdata0))
        return static_cast<void*>(this);
    return IUAVGadgetConfiguration::qt_metacast(_clname);
}

int IPconnectionConfiguration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IUAVGadgetConfiguration::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
