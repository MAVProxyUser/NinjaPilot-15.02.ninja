/****************************************************************************
** Meta object code from reading C++ file 'submiteditorwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../submiteditorwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'submiteditorwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Utils__SubmitEditorWidget_t {
    QByteArrayData data[22];
    char stringdata0[381];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Utils__SubmitEditorWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Utils__SubmitEditorWidget_t qt_meta_stringdata_Utils__SubmitEditorWidget = {
    {
QT_MOC_LITERAL(0, 0, 25), // "Utils::SubmitEditorWidget"
QT_MOC_LITERAL(1, 26, 12), // "diffSelected"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 20), // "fileSelectionChanged"
QT_MOC_LITERAL(4, 61, 16), // "someFileSelected"
QT_MOC_LITERAL(5, 78, 21), // "fileCheckStateChanged"
QT_MOC_LITERAL(6, 100, 15), // "someFileChecked"
QT_MOC_LITERAL(7, 116, 19), // "triggerDiffSelected"
QT_MOC_LITERAL(8, 136, 13), // "diffActivated"
QT_MOC_LITERAL(9, 150, 11), // "QModelIndex"
QT_MOC_LITERAL(10, 162, 5), // "index"
QT_MOC_LITERAL(11, 168, 20), // "diffActivatedDelayed"
QT_MOC_LITERAL(12, 189, 13), // "updateActions"
QT_MOC_LITERAL(13, 203, 18), // "updateSubmitAction"
QT_MOC_LITERAL(14, 222, 16), // "updateDiffAction"
QT_MOC_LITERAL(15, 239, 32), // "editorCustomContextMenuRequested"
QT_MOC_LITERAL(16, 272, 15), // "descriptionText"
QT_MOC_LITERAL(17, 288, 14), // "fileNameColumn"
QT_MOC_LITERAL(18, 303, 21), // "fileListSelectionMode"
QT_MOC_LITERAL(19, 325, 32), // "QAbstractItemView::SelectionMode"
QT_MOC_LITERAL(20, 358, 8), // "lineWrap"
QT_MOC_LITERAL(21, 367, 13) // "lineWrapWidth"

    },
    "Utils::SubmitEditorWidget\0diffSelected\0"
    "\0fileSelectionChanged\0someFileSelected\0"
    "fileCheckStateChanged\0someFileChecked\0"
    "triggerDiffSelected\0diffActivated\0"
    "QModelIndex\0index\0diffActivatedDelayed\0"
    "updateActions\0updateSubmitAction\0"
    "updateDiffAction\0editorCustomContextMenuRequested\0"
    "descriptionText\0fileNameColumn\0"
    "fileListSelectionMode\0"
    "QAbstractItemView::SelectionMode\0"
    "lineWrap\0lineWrapWidth"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Utils__SubmitEditorWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       5,   84, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       3,    1,   67,    2, 0x06 /* Public */,
       5,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   73,    2, 0x08 /* Private */,
       8,    1,   74,    2, 0x08 /* Private */,
      11,    0,   77,    2, 0x08 /* Private */,
      12,    0,   78,    2, 0x08 /* Private */,
      13,    0,   79,    2, 0x08 /* Private */,
      14,    0,   80,    2, 0x08 /* Private */,
      15,    1,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,

 // properties: name, type, flags
      16, QMetaType::QString, 0x00095103,
      17, QMetaType::Int, 0x00094103,
      18, 0x80000000 | 19, 0x0009510b,
      20, QMetaType::Bool, 0x00095103,
      21, QMetaType::Int, 0x00095103,

       0        // eod
};

void Utils::SubmitEditorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SubmitEditorWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->diffSelected((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 1: _t->fileSelectionChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->fileCheckStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->triggerDiffSelected(); break;
        case 4: _t->diffActivated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->diffActivatedDelayed(); break;
        case 6: _t->updateActions(); break;
        case 7: _t->updateSubmitAction(); break;
        case 8: _t->updateDiffAction(); break;
        case 9: _t->editorCustomContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SubmitEditorWidget::*)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SubmitEditorWidget::diffSelected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SubmitEditorWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SubmitEditorWidget::fileSelectionChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SubmitEditorWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SubmitEditorWidget::fileCheckStateChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SubmitEditorWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->descriptionText(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->fileNameColumn(); break;
        case 2: *reinterpret_cast< QAbstractItemView::SelectionMode*>(_v) = _t->fileListSelectionMode(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->lineWrap(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->lineWrapWidth(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SubmitEditorWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDescriptionText(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setFileNameColumn(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setFileListSelectionMode(*reinterpret_cast< QAbstractItemView::SelectionMode*>(_v)); break;
        case 3: _t->setLineWrap(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setLineWrapWidth(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

static const QMetaObject::SuperData qt_meta_extradata_Utils__SubmitEditorWidget[] = {
    QMetaObject::SuperData::link<QAbstractItemView::staticMetaObject>(),
    nullptr
};

QT_INIT_METAOBJECT const QMetaObject Utils::SubmitEditorWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Utils__SubmitEditorWidget.data,
    qt_meta_data_Utils__SubmitEditorWidget,
    qt_static_metacall,
    qt_meta_extradata_Utils__SubmitEditorWidget,
    nullptr
} };


const QMetaObject *Utils::SubmitEditorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Utils::SubmitEditorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Utils__SubmitEditorWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Utils::SubmitEditorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
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

// SIGNAL 0
void Utils::SubmitEditorWidget::diffSelected(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Utils::SubmitEditorWidget::fileSelectionChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Utils::SubmitEditorWidget::fileCheckStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
