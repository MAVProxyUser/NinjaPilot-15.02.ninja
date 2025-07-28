/****************************************************************************
** Meta object code from reading C++ file 'uavgadgetmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../uavgadgetmanager/uavgadgetmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uavgadgetmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__UAVGadgetManager_t {
    QByteArrayData data[24];
    char stringdata0[325];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__UAVGadgetManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__UAVGadgetManager_t qt_meta_stringdata_Core__UAVGadgetManager = {
    {
QT_MOC_LITERAL(0, 0, 22), // "Core::UAVGadgetManager"
QT_MOC_LITERAL(1, 23, 20), // "currentGadgetChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 11), // "IUAVGadget*"
QT_MOC_LITERAL(4, 57, 6), // "gadget"
QT_MOC_LITERAL(5, 64, 18), // "showUavGadgetMenus"
QT_MOC_LITERAL(6, 83, 4), // "show"
QT_MOC_LITERAL(7, 88, 11), // "hasSplitter"
QT_MOC_LITERAL(8, 100, 16), // "updateSplitMenus"
QT_MOC_LITERAL(9, 117, 19), // "handleContextChange"
QT_MOC_LITERAL(10, 137, 15), // "Core::IContext*"
QT_MOC_LITERAL(11, 153, 7), // "context"
QT_MOC_LITERAL(12, 161, 20), // "updateUavGadgetMenus"
QT_MOC_LITERAL(13, 182, 11), // "modeChanged"
QT_MOC_LITERAL(14, 194, 12), // "Core::IMode*"
QT_MOC_LITERAL(15, 207, 4), // "mode"
QT_MOC_LITERAL(16, 212, 5), // "split"
QT_MOC_LITERAL(17, 218, 15), // "Qt::Orientation"
QT_MOC_LITERAL(18, 234, 11), // "orientation"
QT_MOC_LITERAL(19, 246, 15), // "splitSideBySide"
QT_MOC_LITERAL(20, 262, 18), // "removeCurrentSplit"
QT_MOC_LITERAL(21, 281, 15), // "removeAllSplits"
QT_MOC_LITERAL(22, 297, 14), // "gotoOtherSplit"
QT_MOC_LITERAL(23, 312, 12) // "showToolbars"

    },
    "Core::UAVGadgetManager\0currentGadgetChanged\0"
    "\0IUAVGadget*\0gadget\0showUavGadgetMenus\0"
    "show\0hasSplitter\0updateSplitMenus\0"
    "handleContextChange\0Core::IContext*\0"
    "context\0updateUavGadgetMenus\0modeChanged\0"
    "Core::IMode*\0mode\0split\0Qt::Orientation\0"
    "orientation\0splitSideBySide\0"
    "removeCurrentSplit\0removeAllSplits\0"
    "gotoOtherSplit\0showToolbars"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__UAVGadgetManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       5,    2,   82,    2, 0x06 /* Public */,
       8,    1,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   90,    2, 0x08 /* Private */,
      12,    0,   93,    2, 0x08 /* Private */,
      13,    1,   94,    2, 0x08 /* Private */,
      16,    1,   97,    2, 0x0a /* Public */,
      16,    0,  100,    2, 0x0a /* Public */,
      19,    0,  101,    2, 0x0a /* Public */,
      20,    0,  102,    2, 0x0a /* Public */,
      21,    0,  103,    2, 0x0a /* Public */,
      22,    0,  104,    2, 0x0a /* Public */,
      23,    1,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,    6,    7,
    QMetaType::Void, QMetaType::Bool,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,

       0        // eod
};

void Core::UAVGadgetManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UAVGadgetManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->currentGadgetChanged((*reinterpret_cast< IUAVGadget*(*)>(_a[1]))); break;
        case 1: _t->showUavGadgetMenus((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->updateSplitMenus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->handleContextChange((*reinterpret_cast< Core::IContext*(*)>(_a[1]))); break;
        case 4: _t->updateUavGadgetMenus(); break;
        case 5: _t->modeChanged((*reinterpret_cast< Core::IMode*(*)>(_a[1]))); break;
        case 6: _t->split((*reinterpret_cast< Qt::Orientation(*)>(_a[1]))); break;
        case 7: _t->split(); break;
        case 8: _t->splitSideBySide(); break;
        case 9: _t->removeCurrentSplit(); break;
        case 10: _t->removeAllSplits(); break;
        case 11: _t->gotoOtherSplit(); break;
        case 12: _t->showToolbars((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Core::IContext* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Core::IMode* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UAVGadgetManager::*)(IUAVGadget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVGadgetManager::currentGadgetChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UAVGadgetManager::*)(bool , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVGadgetManager::showUavGadgetMenus)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UAVGadgetManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UAVGadgetManager::updateSplitMenus)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::UAVGadgetManager::staticMetaObject = { {
    QMetaObject::SuperData::link<IMode::staticMetaObject>(),
    qt_meta_stringdata_Core__UAVGadgetManager.data,
    qt_meta_data_Core__UAVGadgetManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::UAVGadgetManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::UAVGadgetManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__UAVGadgetManager.stringdata0))
        return static_cast<void*>(this);
    return IMode::qt_metacast(_clname);
}

int Core::UAVGadgetManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IMode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Core::UAVGadgetManager::currentGadgetChanged(IUAVGadget * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Core::UAVGadgetManager::showUavGadgetMenus(bool _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Core::UAVGadgetManager::updateSplitMenus(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
