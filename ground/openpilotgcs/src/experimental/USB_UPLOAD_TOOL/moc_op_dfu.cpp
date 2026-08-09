/****************************************************************************
** Meta object code from reading C++ file 'op_dfu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "op_dfu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'op_dfu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OP_DFU__DFUObject_t {
    QByteArrayData data[8];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OP_DFU__DFUObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OP_DFU__DFUObject_t qt_meta_stringdata_OP_DFU__DFUObject = {
    {
QT_MOC_LITERAL(0, 0, 17), // "OP_DFU::DFUObject"
QT_MOC_LITERAL(1, 18, 15), // "progressUpdated"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 16), // "downloadFinished"
QT_MOC_LITERAL(4, 52, 14), // "uploadFinished"
QT_MOC_LITERAL(5, 67, 14), // "OP_DFU::Status"
QT_MOC_LITERAL(6, 82, 17), // "operationProgress"
QT_MOC_LITERAL(7, 100, 6) // "status"

    },
    "OP_DFU::DFUObject\0progressUpdated\0\0"
    "downloadFinished\0uploadFinished\0"
    "OP_DFU::Status\0operationProgress\0"
    "status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OP_DFU__DFUObject[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       3,    0,   37,    2, 0x06 /* Public */,
       4,    1,   38,    2, 0x06 /* Public */,
       6,    1,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void OP_DFU::DFUObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DFUObject *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->progressUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->downloadFinished(); break;
        case 2: _t->uploadFinished((*reinterpret_cast< OP_DFU::Status(*)>(_a[1]))); break;
        case 3: _t->operationProgress((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< OP_DFU::Status >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DFUObject::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DFUObject::progressUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DFUObject::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DFUObject::downloadFinished)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DFUObject::*)(OP_DFU::Status );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DFUObject::uploadFinished)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DFUObject::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DFUObject::operationProgress)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OP_DFU::DFUObject::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_OP_DFU__DFUObject.data,
    qt_meta_data_OP_DFU__DFUObject,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OP_DFU::DFUObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OP_DFU::DFUObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OP_DFU__DFUObject.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int OP_DFU::DFUObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void OP_DFU::DFUObject::progressUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OP_DFU::DFUObject::downloadFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void OP_DFU::DFUObject::uploadFinished(OP_DFU::Status _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void OP_DFU::DFUObject::operationProgress(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_OP_DFU_t {
    QByteArrayData data[16];
    char stringdata0[217];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OP_DFU_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OP_DFU_t qt_meta_stringdata_OP_DFU = {
    {
QT_MOC_LITERAL(0, 0, 6), // "OP_DFU"
QT_MOC_LITERAL(1, 7, 6), // "Status"
QT_MOC_LITERAL(2, 14, 7), // "DFUidle"
QT_MOC_LITERAL(3, 22, 9), // "uploading"
QT_MOC_LITERAL(4, 32, 21), // "wrong_packet_received"
QT_MOC_LITERAL(5, 54, 16), // "too_many_packets"
QT_MOC_LITERAL(6, 71, 15), // "too_few_packets"
QT_MOC_LITERAL(7, 87, 22), // "Last_operation_Success"
QT_MOC_LITERAL(8, 110, 11), // "downloading"
QT_MOC_LITERAL(9, 122, 4), // "idle"
QT_MOC_LITERAL(10, 127, 21), // "Last_operation_failed"
QT_MOC_LITERAL(11, 149, 17), // "uploadingStarting"
QT_MOC_LITERAL(12, 167, 22), // "outsideDevCapabilities"
QT_MOC_LITERAL(13, 190, 8), // "CRC_Fail"
QT_MOC_LITERAL(14, 199, 11), // "failed_jump"
QT_MOC_LITERAL(15, 211, 5) // "abort"

    },
    "OP_DFU\0Status\0DFUidle\0uploading\0"
    "wrong_packet_received\0too_many_packets\0"
    "too_few_packets\0Last_operation_Success\0"
    "downloading\0idle\0Last_operation_failed\0"
    "uploadingStarting\0outsideDevCapabilities\0"
    "CRC_Fail\0failed_jump\0abort"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OP_DFU[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,   14,   19,

 // enum data: key, value
       2, uint(OP_DFU::DFUidle),
       3, uint(OP_DFU::uploading),
       4, uint(OP_DFU::wrong_packet_received),
       5, uint(OP_DFU::too_many_packets),
       6, uint(OP_DFU::too_few_packets),
       7, uint(OP_DFU::Last_operation_Success),
       8, uint(OP_DFU::downloading),
       9, uint(OP_DFU::idle),
      10, uint(OP_DFU::Last_operation_failed),
      11, uint(OP_DFU::uploadingStarting),
      12, uint(OP_DFU::outsideDevCapabilities),
      13, uint(OP_DFU::CRC_Fail),
      14, uint(OP_DFU::failed_jump),
      15, uint(OP_DFU::abort),

       0        // eod
};

QT_INIT_METAOBJECT const QMetaObject OP_DFU::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_OP_DFU.data,
    qt_meta_data_OP_DFU,
    nullptr,
    nullptr,
    nullptr
} };

QT_WARNING_POP
QT_END_MOC_NAMESPACE
