/****************************************************************************
** Meta object code from reading C++ file 'gpspositionsensor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/gpspositionsensor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gpspositionsensor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GPSPositionSensor_t {
    QByteArrayData data[56];
    char stringdata0[712];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GPSPositionSensor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GPSPositionSensor_t qt_meta_stringdata_GPSPositionSensor = {
    {
QT_MOC_LITERAL(0, 0, 17), // "GPSPositionSensor"
QT_MOC_LITERAL(1, 18, 15), // "LatitudeChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "value"
QT_MOC_LITERAL(4, 41, 16), // "LongitudeChanged"
QT_MOC_LITERAL(5, 58, 15), // "AltitudeChanged"
QT_MOC_LITERAL(6, 74, 22), // "GeoidSeparationChanged"
QT_MOC_LITERAL(7, 97, 14), // "HeadingChanged"
QT_MOC_LITERAL(8, 112, 18), // "GroundspeedChanged"
QT_MOC_LITERAL(9, 131, 11), // "PDOPChanged"
QT_MOC_LITERAL(10, 143, 11), // "HDOPChanged"
QT_MOC_LITERAL(11, 155, 11), // "VDOPChanged"
QT_MOC_LITERAL(12, 167, 13), // "StatusChanged"
QT_MOC_LITERAL(13, 181, 17), // "SatellitesChanged"
QT_MOC_LITERAL(14, 199, 17), // "SensorTypeChanged"
QT_MOC_LITERAL(15, 217, 23), // "AutoConfigStatusChanged"
QT_MOC_LITERAL(16, 241, 11), // "setLatitude"
QT_MOC_LITERAL(17, 253, 12), // "setLongitude"
QT_MOC_LITERAL(18, 266, 11), // "setAltitude"
QT_MOC_LITERAL(19, 278, 18), // "setGeoidSeparation"
QT_MOC_LITERAL(20, 297, 10), // "setHeading"
QT_MOC_LITERAL(21, 308, 14), // "setGroundspeed"
QT_MOC_LITERAL(22, 323, 7), // "setPDOP"
QT_MOC_LITERAL(23, 331, 7), // "setHDOP"
QT_MOC_LITERAL(24, 339, 7), // "setVDOP"
QT_MOC_LITERAL(25, 347, 9), // "setStatus"
QT_MOC_LITERAL(26, 357, 13), // "setSatellites"
QT_MOC_LITERAL(27, 371, 13), // "setSensorType"
QT_MOC_LITERAL(28, 385, 19), // "setAutoConfigStatus"
QT_MOC_LITERAL(29, 405, 17), // "emitNotifications"
QT_MOC_LITERAL(30, 423, 11), // "getLatitude"
QT_MOC_LITERAL(31, 435, 12), // "getLongitude"
QT_MOC_LITERAL(32, 448, 11), // "getAltitude"
QT_MOC_LITERAL(33, 460, 18), // "getGeoidSeparation"
QT_MOC_LITERAL(34, 479, 10), // "getHeading"
QT_MOC_LITERAL(35, 490, 14), // "getGroundspeed"
QT_MOC_LITERAL(36, 505, 7), // "getPDOP"
QT_MOC_LITERAL(37, 513, 7), // "getHDOP"
QT_MOC_LITERAL(38, 521, 7), // "getVDOP"
QT_MOC_LITERAL(39, 529, 9), // "getStatus"
QT_MOC_LITERAL(40, 539, 13), // "getSatellites"
QT_MOC_LITERAL(41, 553, 13), // "getSensorType"
QT_MOC_LITERAL(42, 567, 19), // "getAutoConfigStatus"
QT_MOC_LITERAL(43, 587, 8), // "Latitude"
QT_MOC_LITERAL(44, 596, 9), // "Longitude"
QT_MOC_LITERAL(45, 606, 8), // "Altitude"
QT_MOC_LITERAL(46, 615, 15), // "GeoidSeparation"
QT_MOC_LITERAL(47, 631, 7), // "Heading"
QT_MOC_LITERAL(48, 639, 11), // "Groundspeed"
QT_MOC_LITERAL(49, 651, 4), // "PDOP"
QT_MOC_LITERAL(50, 656, 4), // "HDOP"
QT_MOC_LITERAL(51, 661, 4), // "VDOP"
QT_MOC_LITERAL(52, 666, 6), // "Status"
QT_MOC_LITERAL(53, 673, 10), // "Satellites"
QT_MOC_LITERAL(54, 684, 10), // "SensorType"
QT_MOC_LITERAL(55, 695, 16) // "AutoConfigStatus"

    },
    "GPSPositionSensor\0LatitudeChanged\0\0"
    "value\0LongitudeChanged\0AltitudeChanged\0"
    "GeoidSeparationChanged\0HeadingChanged\0"
    "GroundspeedChanged\0PDOPChanged\0"
    "HDOPChanged\0VDOPChanged\0StatusChanged\0"
    "SatellitesChanged\0SensorTypeChanged\0"
    "AutoConfigStatusChanged\0setLatitude\0"
    "setLongitude\0setAltitude\0setGeoidSeparation\0"
    "setHeading\0setGroundspeed\0setPDOP\0"
    "setHDOP\0setVDOP\0setStatus\0setSatellites\0"
    "setSensorType\0setAutoConfigStatus\0"
    "emitNotifications\0getLatitude\0"
    "getLongitude\0getAltitude\0getGeoidSeparation\0"
    "getHeading\0getGroundspeed\0getPDOP\0"
    "getHDOP\0getVDOP\0getStatus\0getSatellites\0"
    "getSensorType\0getAutoConfigStatus\0"
    "Latitude\0Longitude\0Altitude\0GeoidSeparation\0"
    "Heading\0Groundspeed\0PDOP\0HDOP\0VDOP\0"
    "Status\0Satellites\0SensorType\0"
    "AutoConfigStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GPSPositionSensor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
      13,  306, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  214,    2, 0x06 /* Public */,
       4,    1,  217,    2, 0x06 /* Public */,
       5,    1,  220,    2, 0x06 /* Public */,
       6,    1,  223,    2, 0x06 /* Public */,
       7,    1,  226,    2, 0x06 /* Public */,
       8,    1,  229,    2, 0x06 /* Public */,
       9,    1,  232,    2, 0x06 /* Public */,
      10,    1,  235,    2, 0x06 /* Public */,
      11,    1,  238,    2, 0x06 /* Public */,
      12,    1,  241,    2, 0x06 /* Public */,
      13,    1,  244,    2, 0x06 /* Public */,
      14,    1,  247,    2, 0x06 /* Public */,
      15,    1,  250,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,  253,    2, 0x0a /* Public */,
      17,    1,  256,    2, 0x0a /* Public */,
      18,    1,  259,    2, 0x0a /* Public */,
      19,    1,  262,    2, 0x0a /* Public */,
      20,    1,  265,    2, 0x0a /* Public */,
      21,    1,  268,    2, 0x0a /* Public */,
      22,    1,  271,    2, 0x0a /* Public */,
      23,    1,  274,    2, 0x0a /* Public */,
      24,    1,  277,    2, 0x0a /* Public */,
      25,    1,  280,    2, 0x0a /* Public */,
      26,    1,  283,    2, 0x0a /* Public */,
      27,    1,  286,    2, 0x0a /* Public */,
      28,    1,  289,    2, 0x0a /* Public */,
      29,    0,  292,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      30,    0,  293,    2, 0x02 /* Public */,
      31,    0,  294,    2, 0x02 /* Public */,
      32,    0,  295,    2, 0x02 /* Public */,
      33,    0,  296,    2, 0x02 /* Public */,
      34,    0,  297,    2, 0x02 /* Public */,
      35,    0,  298,    2, 0x02 /* Public */,
      36,    0,  299,    2, 0x02 /* Public */,
      37,    0,  300,    2, 0x02 /* Public */,
      38,    0,  301,    2, 0x02 /* Public */,
      39,    0,  302,    2, 0x02 /* Public */,
      40,    0,  303,    2, 0x02 /* Public */,
      41,    0,  304,    2, 0x02 /* Public */,
      42,    0,  305,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      43, QMetaType::Int, 0x00495103,
      44, QMetaType::Int, 0x00495103,
      45, QMetaType::Float, 0x00495103,
      46, QMetaType::Float, 0x00495103,
      47, QMetaType::Float, 0x00495103,
      48, QMetaType::Float, 0x00495103,
      49, QMetaType::Float, 0x00495103,
      50, QMetaType::Float, 0x00495103,
      51, QMetaType::Float, 0x00495103,
      52, QMetaType::UChar, 0x00495103,
      53, QMetaType::SChar, 0x00495103,
      54, QMetaType::UChar, 0x00495103,
      55, QMetaType::UChar, 0x00495103,

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
      10,
      11,
      12,

       0        // eod
};

void GPSPositionSensor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GPSPositionSensor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->LatitudeChanged((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 1: _t->LongitudeChanged((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 2: _t->AltitudeChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->GeoidSeparationChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->HeadingChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->GroundspeedChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->PDOPChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->HDOPChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->VDOPChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->StatusChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 10: _t->SatellitesChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 11: _t->SensorTypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->AutoConfigStatusChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 13: _t->setLatitude((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 14: _t->setLongitude((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 15: _t->setAltitude((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->setGeoidSeparation((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 17: _t->setHeading((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->setGroundspeed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->setPDOP((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->setHDOP((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->setVDOP((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: _t->setStatus((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 23: _t->setSatellites((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 24: _t->setSensorType((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 25: _t->setAutoConfigStatus((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 26: _t->emitNotifications(); break;
        case 27: { qint32 _r = _t->getLatitude();
            if (_a[0]) *reinterpret_cast< qint32*>(_a[0]) = std::move(_r); }  break;
        case 28: { qint32 _r = _t->getLongitude();
            if (_a[0]) *reinterpret_cast< qint32*>(_a[0]) = std::move(_r); }  break;
        case 29: { float _r = _t->getAltitude();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 30: { float _r = _t->getGeoidSeparation();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 31: { float _r = _t->getHeading();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 32: { float _r = _t->getGroundspeed();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 33: { float _r = _t->getPDOP();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 34: { float _r = _t->getHDOP();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 35: { float _r = _t->getVDOP();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 36: { quint8 _r = _t->getStatus();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 37: { qint8 _r = _t->getSatellites();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 38: { quint8 _r = _t->getSensorType();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 39: { quint8 _r = _t->getAutoConfigStatus();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GPSPositionSensor::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSPositionSensor::LatitudeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GPSPositionSensor::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSPositionSensor::LongitudeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GPSPositionSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSPositionSensor::AltitudeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GPSPositionSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSPositionSensor::GeoidSeparationChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GPSPositionSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSPositionSensor::HeadingChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GPSPositionSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSPositionSensor::GroundspeedChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GPSPositionSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSPositionSensor::PDOPChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GPSPositionSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSPositionSensor::HDOPChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GPSPositionSensor::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSPositionSensor::VDOPChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (GPSPositionSensor::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSPositionSensor::StatusChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (GPSPositionSensor::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSPositionSensor::SatellitesChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (GPSPositionSensor::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSPositionSensor::SensorTypeChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (GPSPositionSensor::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPSPositionSensor::AutoConfigStatusChanged)) {
                *result = 12;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<GPSPositionSensor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qint32*>(_v) = _t->getLatitude(); break;
        case 1: *reinterpret_cast< qint32*>(_v) = _t->getLongitude(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getAltitude(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getGeoidSeparation(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getHeading(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getGroundspeed(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getPDOP(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getHDOP(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getVDOP(); break;
        case 9: *reinterpret_cast< quint8*>(_v) = _t->getStatus(); break;
        case 10: *reinterpret_cast< qint8*>(_v) = _t->getSatellites(); break;
        case 11: *reinterpret_cast< quint8*>(_v) = _t->getSensorType(); break;
        case 12: *reinterpret_cast< quint8*>(_v) = _t->getAutoConfigStatus(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<GPSPositionSensor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLatitude(*reinterpret_cast< qint32*>(_v)); break;
        case 1: _t->setLongitude(*reinterpret_cast< qint32*>(_v)); break;
        case 2: _t->setAltitude(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setGeoidSeparation(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setHeading(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setGroundspeed(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setPDOP(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setHDOP(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setVDOP(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setStatus(*reinterpret_cast< quint8*>(_v)); break;
        case 10: _t->setSatellites(*reinterpret_cast< qint8*>(_v)); break;
        case 11: _t->setSensorType(*reinterpret_cast< quint8*>(_v)); break;
        case 12: _t->setAutoConfigStatus(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject GPSPositionSensor::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_GPSPositionSensor.data,
    qt_meta_data_GPSPositionSensor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GPSPositionSensor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GPSPositionSensor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GPSPositionSensor.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int GPSPositionSensor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 40;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 13;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GPSPositionSensor::LatitudeChanged(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GPSPositionSensor::LongitudeChanged(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GPSPositionSensor::AltitudeChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GPSPositionSensor::GeoidSeparationChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GPSPositionSensor::HeadingChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GPSPositionSensor::GroundspeedChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GPSPositionSensor::PDOPChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void GPSPositionSensor::HDOPChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void GPSPositionSensor::VDOPChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void GPSPositionSensor::StatusChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void GPSPositionSensor::SatellitesChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void GPSPositionSensor::SensorTypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void GPSPositionSensor::AutoConfigStatusChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
