/****************************************************************************
** Meta object code from reading C++ file 'receiveractivity.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/receiveractivity.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'receiveractivity.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ReceiverActivity_t {
    QByteArrayData data[12];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ReceiverActivity_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ReceiverActivity_t qt_meta_stringdata_ReceiverActivity = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ReceiverActivity"
QT_MOC_LITERAL(1, 17, 18), // "ActiveGroupChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 5), // "value"
QT_MOC_LITERAL(4, 43, 20), // "ActiveChannelChanged"
QT_MOC_LITERAL(5, 64, 14), // "setActiveGroup"
QT_MOC_LITERAL(6, 79, 16), // "setActiveChannel"
QT_MOC_LITERAL(7, 96, 17), // "emitNotifications"
QT_MOC_LITERAL(8, 114, 14), // "getActiveGroup"
QT_MOC_LITERAL(9, 129, 16), // "getActiveChannel"
QT_MOC_LITERAL(10, 146, 11), // "ActiveGroup"
QT_MOC_LITERAL(11, 158, 13) // "ActiveChannel"

    },
    "ReceiverActivity\0ActiveGroupChanged\0"
    "\0value\0ActiveChannelChanged\0setActiveGroup\0"
    "setActiveChannel\0emitNotifications\0"
    "getActiveGroup\0getActiveChannel\0"
    "ActiveGroup\0ActiveChannel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReceiverActivity[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       2,   64, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   55,    2, 0x0a /* Public */,
       6,    1,   58,    2, 0x0a /* Public */,
       7,    0,   61,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
       8,    0,   62,    2, 0x02 /* Public */,
       9,    0,   63,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      10, QMetaType::UChar, 0x00495103,
      11, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void ReceiverActivity::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ReceiverActivity *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ActiveGroupChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->ActiveChannelChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 2: _t->setActiveGroup((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 3: _t->setActiveChannel((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 4: _t->emitNotifications(); break;
        case 5: { quint8 _r = _t->getActiveGroup();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 6: { quint8 _r = _t->getActiveChannel();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ReceiverActivity::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ReceiverActivity::ActiveGroupChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ReceiverActivity::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ReceiverActivity::ActiveChannelChanged)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ReceiverActivity *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint8*>(_v) = _t->getActiveGroup(); break;
        case 1: *reinterpret_cast< quint8*>(_v) = _t->getActiveChannel(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ReceiverActivity *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setActiveGroup(*reinterpret_cast< quint8*>(_v)); break;
        case 1: _t->setActiveChannel(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ReceiverActivity::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_ReceiverActivity.data,
    qt_meta_data_ReceiverActivity,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ReceiverActivity::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReceiverActivity::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ReceiverActivity.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int ReceiverActivity::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
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
void ReceiverActivity::ActiveGroupChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ReceiverActivity::ActiveChannelChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
