/****************************************************************************
** Meta object code from reading C++ file 'treeitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../treeitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'treeitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HighLightManager_t {
    QByteArrayData data[3];
    char stringdata0[36];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HighLightManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HighLightManager_t qt_meta_stringdata_HighLightManager = {
    {
QT_MOC_LITERAL(0, 0, 16), // "HighLightManager"
QT_MOC_LITERAL(1, 17, 17), // "checkItemsExpired"
QT_MOC_LITERAL(2, 35, 0) // ""

    },
    "HighLightManager\0checkItemsExpired\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HighLightManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void HighLightManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HighLightManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->checkItemsExpired(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject HighLightManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_HighLightManager.data,
    qt_meta_data_HighLightManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HighLightManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HighLightManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HighLightManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HighLightManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
    return _id;
}
struct qt_meta_stringdata_TreeItem_t {
    QByteArrayData data[6];
    char stringdata0[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TreeItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TreeItem_t qt_meta_stringdata_TreeItem = {
    {
QT_MOC_LITERAL(0, 0, 8), // "TreeItem"
QT_MOC_LITERAL(1, 9, 15), // "updateHighlight"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 9), // "TreeItem*"
QT_MOC_LITERAL(4, 36, 4), // "item"
QT_MOC_LITERAL(5, 41, 13) // "updateIsKnown"

    },
    "TreeItem\0updateHighlight\0\0TreeItem*\0"
    "item\0updateIsKnown"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TreeItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       5,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void TreeItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TreeItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateHighlight((*reinterpret_cast< TreeItem*(*)>(_a[1]))); break;
        case 1: _t->updateIsKnown((*reinterpret_cast< TreeItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TreeItem* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TreeItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TreeItem::*)(TreeItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TreeItem::updateHighlight)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TreeItem::*)(TreeItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TreeItem::updateIsKnown)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TreeItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TreeItem.data,
    qt_meta_data_TreeItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TreeItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TreeItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TreeItem.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TreeItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void TreeItem::updateHighlight(TreeItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TreeItem::updateIsKnown(TreeItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_TopTreeItem_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TopTreeItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TopTreeItem_t qt_meta_stringdata_TopTreeItem = {
    {
QT_MOC_LITERAL(0, 0, 11) // "TopTreeItem"

    },
    "TopTreeItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TopTreeItem[] = {

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

void TopTreeItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject TopTreeItem::staticMetaObject = { {
    QMetaObject::SuperData::link<TreeItem::staticMetaObject>(),
    qt_meta_stringdata_TopTreeItem.data,
    qt_meta_data_TopTreeItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TopTreeItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TopTreeItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TopTreeItem.stringdata0))
        return static_cast<void*>(this);
    return TreeItem::qt_metacast(_clname);
}

int TopTreeItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TreeItem::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ObjectTreeItem_t {
    QByteArrayData data[1];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ObjectTreeItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ObjectTreeItem_t qt_meta_stringdata_ObjectTreeItem = {
    {
QT_MOC_LITERAL(0, 0, 14) // "ObjectTreeItem"

    },
    "ObjectTreeItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ObjectTreeItem[] = {

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

void ObjectTreeItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject ObjectTreeItem::staticMetaObject = { {
    QMetaObject::SuperData::link<TreeItem::staticMetaObject>(),
    qt_meta_stringdata_ObjectTreeItem.data,
    qt_meta_data_ObjectTreeItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ObjectTreeItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ObjectTreeItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ObjectTreeItem.stringdata0))
        return static_cast<void*>(this);
    return TreeItem::qt_metacast(_clname);
}

int ObjectTreeItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TreeItem::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_MetaObjectTreeItem_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MetaObjectTreeItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MetaObjectTreeItem_t qt_meta_stringdata_MetaObjectTreeItem = {
    {
QT_MOC_LITERAL(0, 0, 18) // "MetaObjectTreeItem"

    },
    "MetaObjectTreeItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MetaObjectTreeItem[] = {

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

void MetaObjectTreeItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject MetaObjectTreeItem::staticMetaObject = { {
    QMetaObject::SuperData::link<ObjectTreeItem::staticMetaObject>(),
    qt_meta_stringdata_MetaObjectTreeItem.data,
    qt_meta_data_MetaObjectTreeItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MetaObjectTreeItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MetaObjectTreeItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MetaObjectTreeItem.stringdata0))
        return static_cast<void*>(this);
    return ObjectTreeItem::qt_metacast(_clname);
}

int MetaObjectTreeItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ObjectTreeItem::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_DataObjectTreeItem_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataObjectTreeItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataObjectTreeItem_t qt_meta_stringdata_DataObjectTreeItem = {
    {
QT_MOC_LITERAL(0, 0, 18) // "DataObjectTreeItem"

    },
    "DataObjectTreeItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataObjectTreeItem[] = {

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

void DataObjectTreeItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject DataObjectTreeItem::staticMetaObject = { {
    QMetaObject::SuperData::link<ObjectTreeItem::staticMetaObject>(),
    qt_meta_stringdata_DataObjectTreeItem.data,
    qt_meta_data_DataObjectTreeItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataObjectTreeItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataObjectTreeItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataObjectTreeItem.stringdata0))
        return static_cast<void*>(this);
    return ObjectTreeItem::qt_metacast(_clname);
}

int DataObjectTreeItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ObjectTreeItem::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_InstanceTreeItem_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InstanceTreeItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InstanceTreeItem_t qt_meta_stringdata_InstanceTreeItem = {
    {
QT_MOC_LITERAL(0, 0, 16) // "InstanceTreeItem"

    },
    "InstanceTreeItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InstanceTreeItem[] = {

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

void InstanceTreeItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject InstanceTreeItem::staticMetaObject = { {
    QMetaObject::SuperData::link<DataObjectTreeItem::staticMetaObject>(),
    qt_meta_stringdata_InstanceTreeItem.data,
    qt_meta_data_InstanceTreeItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *InstanceTreeItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InstanceTreeItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InstanceTreeItem.stringdata0))
        return static_cast<void*>(this);
    return DataObjectTreeItem::qt_metacast(_clname);
}

int InstanceTreeItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DataObjectTreeItem::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ArrayFieldTreeItem_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ArrayFieldTreeItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ArrayFieldTreeItem_t qt_meta_stringdata_ArrayFieldTreeItem = {
    {
QT_MOC_LITERAL(0, 0, 18) // "ArrayFieldTreeItem"

    },
    "ArrayFieldTreeItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ArrayFieldTreeItem[] = {

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

void ArrayFieldTreeItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject ArrayFieldTreeItem::staticMetaObject = { {
    QMetaObject::SuperData::link<TreeItem::staticMetaObject>(),
    qt_meta_stringdata_ArrayFieldTreeItem.data,
    qt_meta_data_ArrayFieldTreeItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ArrayFieldTreeItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ArrayFieldTreeItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ArrayFieldTreeItem.stringdata0))
        return static_cast<void*>(this);
    return TreeItem::qt_metacast(_clname);
}

int ArrayFieldTreeItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TreeItem::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
