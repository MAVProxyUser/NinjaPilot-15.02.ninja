/****************************************************************************
** Meta object code from reading C++ file 'gpssettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/gpssettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gpssettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GPSSettings_t {
    QByteArrayData data[44];
    char stringdata0[683];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GPSSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GPSSettings_t qt_meta_stringdata_GPSSettings = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GPSSettings"
QT_MOC_LITERAL(1, 12, 14), // "MaxPDOPChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 5), // "value"
QT_MOC_LITERAL(4, 34, 19), // "DataProtocolChanged"
QT_MOC_LITERAL(5, 54, 20), // "MinSatellitesChanged"
QT_MOC_LITERAL(6, 75, 20), // "UbxAutoConfigChanged"
QT_MOC_LITERAL(7, 96, 14), // "UbxRateChanged"
QT_MOC_LITERAL(8, 111, 22), // "UbxDynamicModelChanged"
QT_MOC_LITERAL(9, 134, 18), // "UbxSBASModeChanged"
QT_MOC_LITERAL(10, 153, 26), // "UbxSBASChannelsUsedChanged"
QT_MOC_LITERAL(11, 180, 18), // "UbxSBASSatsChanged"
QT_MOC_LITERAL(12, 199, 18), // "UbxGNSSModeChanged"
QT_MOC_LITERAL(13, 218, 10), // "setMaxPDOP"
QT_MOC_LITERAL(14, 229, 15), // "setDataProtocol"
QT_MOC_LITERAL(15, 245, 16), // "setMinSatellites"
QT_MOC_LITERAL(16, 262, 16), // "setUbxAutoConfig"
QT_MOC_LITERAL(17, 279, 10), // "setUbxRate"
QT_MOC_LITERAL(18, 290, 18), // "setUbxDynamicModel"
QT_MOC_LITERAL(19, 309, 14), // "setUbxSBASMode"
QT_MOC_LITERAL(20, 324, 22), // "setUbxSBASChannelsUsed"
QT_MOC_LITERAL(21, 347, 14), // "setUbxSBASSats"
QT_MOC_LITERAL(22, 362, 14), // "setUbxGNSSMode"
QT_MOC_LITERAL(23, 377, 17), // "emitNotifications"
QT_MOC_LITERAL(24, 395, 10), // "getMaxPDOP"
QT_MOC_LITERAL(25, 406, 15), // "getDataProtocol"
QT_MOC_LITERAL(26, 422, 16), // "getMinSatellites"
QT_MOC_LITERAL(27, 439, 16), // "getUbxAutoConfig"
QT_MOC_LITERAL(28, 456, 10), // "getUbxRate"
QT_MOC_LITERAL(29, 467, 18), // "getUbxDynamicModel"
QT_MOC_LITERAL(30, 486, 14), // "getUbxSBASMode"
QT_MOC_LITERAL(31, 501, 22), // "getUbxSBASChannelsUsed"
QT_MOC_LITERAL(32, 524, 14), // "getUbxSBASSats"
QT_MOC_LITERAL(33, 539, 14), // "getUbxGNSSMode"
QT_MOC_LITERAL(34, 554, 7), // "MaxPDOP"
QT_MOC_LITERAL(35, 562, 12), // "DataProtocol"
QT_MOC_LITERAL(36, 575, 13), // "MinSatellites"
QT_MOC_LITERAL(37, 589, 13), // "UbxAutoConfig"
QT_MOC_LITERAL(38, 603, 7), // "UbxRate"
QT_MOC_LITERAL(39, 611, 15), // "UbxDynamicModel"
QT_MOC_LITERAL(40, 627, 11), // "UbxSBASMode"
QT_MOC_LITERAL(41, 639, 19), // "UbxSBASChannelsUsed"
QT_MOC_LITERAL(42, 659, 11), // "UbxSBASSats"
QT_MOC_LITERAL(43, 671, 11) // "UbxGNSSMode"

    },
    "GPSSettings\0MaxPDOPChanged\0\0value\0"
    "DataProtocolChanged\0MinSatellitesChanged\0"
    "UbxAutoConfigChanged\0UbxRateChanged\0"
    "UbxDynamicModelChanged\0UbxSBASModeChanged\0"
    "UbxSBASChannelsUsedChanged\0"
    "UbxSBASSatsChanged\0UbxGNSSModeChanged\0"
    "setMaxPDOP\0setDataProtocol\0setMinSatellites\0"
    "setUbxAutoConfig\0setUbxRate\0"
    "setUbxDynamicModel\0setUbxSBASMode\0"
    "setUbxSBASChannelsUsed\0setUbxSBASSats\0"
    "setUbxGNSSMode\0emitNotifications\0"
    "getMaxPDOP\0getDataProtocol\0getMinSatellites\0"
    "getUbxAutoConfig\0getUbxRate\0"
    "getUbxDynamicModel\0getUbxSBASMode\0"
    "getUbxSBASChannelsUsed\0getUbxSBASSats\0"
    "getUbxGNSSMode\0MaxPDOP\0DataProtocol\0"
    "MinSatellites\0UbxAutoConfig\0UbxRate\0"
    "UbxDynamicModel\0UbxSBASMode\0"
    "UbxSBASChannelsUsed\0UbxSBASSats\0"
    "UbxGNSSMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GPSSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
      10,  240, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  169,    2, 0x06 /* Public */,
       4,    1,  172,    2, 0x06 /* Public */,
       5,    1,  175,    2, 0x06 /* Public */,
       6,    1,  178,    2, 0x06 /* Public */,
       7,    1,  181,    2, 0x06 /* Public */,
       8,    1,  184,    2, 0x06 /* Public */,
       9,    1,  187,    2, 0x06 /* Public */,
      10,    1,  190,    2, 0x06 /* Public */,
      11,    1,  193,    2, 0x06 /* Public */,
      12,    1,  196,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,  199,    2, 0x0a /* Public */,
      14,    1,  202,    2, 0x0a /* Public */,
      15,    1,  205,    2, 0x0a /* Public */,
      16,    1,  208,    2, 0x0a /* Public */,
      17,    1,  211,    2, 0x0a /* Public */,
      18,    1,  214,    2, 0x0a /* Public */,
      19,    1,  217,    2, 0x0a /* Public */,
      20,    1,  220,    2, 0x0a /* Public */,
      21,    1,  223,    2, 0x0a /* Public */,
      22,    1,  226,    2, 0x0a /* Public */,
      23,    0,  229,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      24,    0,  230,    2, 0x02 /* Public */,
      25,    0,  231,    2, 0x02 /* Public */,
      26,    0,  232,    2, 0x02 /* Public */,
      27,    0,  233,    2, 0x02 /* Public */,
      28,    0,  234,    2, 0x02 /* Public */,
      29,    0,  235,    2, 0x02 /* Public */,
      30,    0,  236,    2, 0x02 /* Public */,
      31,    0,  237,    2, 0x02 /* Public */,
      32,    0,  238,    2, 0x02 /* Public */,
      33,    0,  239,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      34, QMetaType::Float, 0x00495103,
      35, QMetaType::UChar, 0x00495103,
      36, QMetaType::UChar, 0x00495103,
      37, QMetaType::UChar, 0x00495103,
      38, QMetaType::SChar, 0x00495103,
      39, QMetaType::UChar, 0x00495103,
      40, QMetaType::UChar, 0x00495103,
      41, QMetaType::UChar, 0x00495103,
      42, QMetaType::UChar, 0x00495103,
      43, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,
       9,

       0        // eod
};

void GPSSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GPSSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->MaxPDOPChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->DataProtocolChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 2: _t->MinSatellitesChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 3: _t->UbxAutoConfigChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 4: _t->UbxRateChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 5: _t->UbxDynamicModelChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 6: _t->UbxSBASModeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 7: _t->UbxSBASChannelsUsedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 8: _t->UbxSBASSatsChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 9: _t->UbxGNSSModeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 10: _t->setMaxPDOP((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->setDataProtocol((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->setMinSatellites((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 13: _t->setUbxAutoConfig((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->setUbxRate((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 15: _t->setUbxDynamicModel((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 16: _t->setUbxSBASMode((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->setUbxSBASChannelsUsed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 18: _t->setUbxSBASSats((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 19: _t->setUbxGNSSMode((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->emitNotifications(); break;
        case 21: { float _r = _t->getMaxPDOP();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 22: { quint8 _r = _t->getDataProtocol();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 23: { quint8 _r = _t->getMinSatellites();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 24: { quint8 _r = _t->getUbxAutoConfig();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 25: { qint8 _r = _t->getUbxRate();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 26: { quint8 _r = _t->getUbxDynamicModel();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 27: { quint8 _r = _t->getUbxSBASMode();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 28: { quint8 _r = _t->getUbxSBASChannelsUsed();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 29: { quint8 _r = _t->getUbxSBASSats();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 30: { quint8 _r = _t->getUbxGNSSMode();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GPSSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSSettings::MaxPDOPChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GPSSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSSettings::DataProtocolChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GPSSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSSettings::MinSatellitesChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GPSSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSSettings::UbxAutoConfigChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GPSSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSSettings::UbxRateChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GPSSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSSettings::UbxDynamicModelChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GPSSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSSettings::UbxSBASModeChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GPSSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSSettings::UbxSBASChannelsUsedChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GPSSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSSettings::UbxSBASSatsChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (GPSSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSSettings::UbxGNSSModeChanged)) {
                *result = 9;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<GPSSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getMaxPDOP(); break;
        case 1: *reinterpret_cast< quint8*>(_v) = _t->getDataProtocol(); break;
        case 2: *reinterpret_cast< quint8*>(_v) = _t->getMinSatellites(); break;
        case 3: *reinterpret_cast< quint8*>(_v) = _t->getUbxAutoConfig(); break;
        case 4: *reinterpret_cast< qint8*>(_v) = _t->getUbxRate(); break;
        case 5: *reinterpret_cast< quint8*>(_v) = _t->getUbxDynamicModel(); break;
        case 6: *reinterpret_cast< quint8*>(_v) = _t->getUbxSBASMode(); break;
        case 7: *reinterpret_cast< quint8*>(_v) = _t->getUbxSBASChannelsUsed(); break;
        case 8: *reinterpret_cast< quint8*>(_v) = _t->getUbxSBASSats(); break;
        case 9: *reinterpret_cast< quint8*>(_v) = _t->getUbxGNSSMode(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<GPSSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMaxPDOP(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setDataProtocol(*reinterpret_cast< quint8*>(_v)); break;
        case 2: _t->setMinSatellites(*reinterpret_cast< quint8*>(_v)); break;
        case 3: _t->setUbxAutoConfig(*reinterpret_cast< quint8*>(_v)); break;
        case 4: _t->setUbxRate(*reinterpret_cast< qint8*>(_v)); break;
        case 5: _t->setUbxDynamicModel(*reinterpret_cast< quint8*>(_v)); break;
        case 6: _t->setUbxSBASMode(*reinterpret_cast< quint8*>(_v)); break;
        case 7: _t->setUbxSBASChannelsUsed(*reinterpret_cast< quint8*>(_v)); break;
        case 8: _t->setUbxSBASSats(*reinterpret_cast< quint8*>(_v)); break;
        case 9: _t->setUbxGNSSMode(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject GPSSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_GPSSettings.data,
    qt_meta_data_GPSSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GPSSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GPSSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GPSSettings.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int GPSSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 31;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GPSSettings::MaxPDOPChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GPSSettings::DataProtocolChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GPSSettings::MinSatellitesChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GPSSettings::UbxAutoConfigChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GPSSettings::UbxRateChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GPSSettings::UbxDynamicModelChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GPSSettings::UbxSBASModeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void GPSSettings::UbxSBASChannelsUsedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void GPSSettings::UbxSBASSatsChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void GPSSettings::UbxGNSSModeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
