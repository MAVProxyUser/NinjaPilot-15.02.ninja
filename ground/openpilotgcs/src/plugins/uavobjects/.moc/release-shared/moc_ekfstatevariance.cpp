/****************************************************************************
** Meta object code from reading C++ file 'ekfstatevariance.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/ekfstatevariance.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ekfstatevariance.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EKFStateVariance_t {
    QByteArrayData data[60];
    char stringdata0[968];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EKFStateVariance_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EKFStateVariance_t qt_meta_stringdata_EKFStateVariance = {
    {
QT_MOC_LITERAL(0, 0, 16), // "EKFStateVariance"
QT_MOC_LITERAL(1, 17, 8), // "PChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "index"
QT_MOC_LITERAL(4, 33, 5), // "value"
QT_MOC_LITERAL(5, 39, 22), // "P_PositionNorthChanged"
QT_MOC_LITERAL(6, 62, 21), // "P_PositionEastChanged"
QT_MOC_LITERAL(7, 84, 21), // "P_PositionDownChanged"
QT_MOC_LITERAL(8, 106, 22), // "P_VelocityNorthChanged"
QT_MOC_LITERAL(9, 129, 21), // "P_VelocityEastChanged"
QT_MOC_LITERAL(10, 151, 21), // "P_VelocityDownChanged"
QT_MOC_LITERAL(11, 173, 19), // "P_AttitudeQ1Changed"
QT_MOC_LITERAL(12, 193, 19), // "P_AttitudeQ2Changed"
QT_MOC_LITERAL(13, 213, 19), // "P_AttitudeQ3Changed"
QT_MOC_LITERAL(14, 233, 19), // "P_AttitudeQ4Changed"
QT_MOC_LITERAL(15, 253, 19), // "P_GyroDriftXChanged"
QT_MOC_LITERAL(16, 273, 19), // "P_GyroDriftYChanged"
QT_MOC_LITERAL(17, 293, 19), // "P_GyroDriftZChanged"
QT_MOC_LITERAL(18, 313, 4), // "setP"
QT_MOC_LITERAL(19, 318, 18), // "setP_PositionNorth"
QT_MOC_LITERAL(20, 337, 17), // "setP_PositionEast"
QT_MOC_LITERAL(21, 355, 17), // "setP_PositionDown"
QT_MOC_LITERAL(22, 373, 18), // "setP_VelocityNorth"
QT_MOC_LITERAL(23, 392, 17), // "setP_VelocityEast"
QT_MOC_LITERAL(24, 410, 17), // "setP_VelocityDown"
QT_MOC_LITERAL(25, 428, 15), // "setP_AttitudeQ1"
QT_MOC_LITERAL(26, 444, 15), // "setP_AttitudeQ2"
QT_MOC_LITERAL(27, 460, 15), // "setP_AttitudeQ3"
QT_MOC_LITERAL(28, 476, 15), // "setP_AttitudeQ4"
QT_MOC_LITERAL(29, 492, 15), // "setP_GyroDriftX"
QT_MOC_LITERAL(30, 508, 15), // "setP_GyroDriftY"
QT_MOC_LITERAL(31, 524, 15), // "setP_GyroDriftZ"
QT_MOC_LITERAL(32, 540, 17), // "emitNotifications"
QT_MOC_LITERAL(33, 558, 4), // "getP"
QT_MOC_LITERAL(34, 563, 18), // "getP_PositionNorth"
QT_MOC_LITERAL(35, 582, 17), // "getP_PositionEast"
QT_MOC_LITERAL(36, 600, 17), // "getP_PositionDown"
QT_MOC_LITERAL(37, 618, 18), // "getP_VelocityNorth"
QT_MOC_LITERAL(38, 637, 17), // "getP_VelocityEast"
QT_MOC_LITERAL(39, 655, 17), // "getP_VelocityDown"
QT_MOC_LITERAL(40, 673, 15), // "getP_AttitudeQ1"
QT_MOC_LITERAL(41, 689, 15), // "getP_AttitudeQ2"
QT_MOC_LITERAL(42, 705, 15), // "getP_AttitudeQ3"
QT_MOC_LITERAL(43, 721, 15), // "getP_AttitudeQ4"
QT_MOC_LITERAL(44, 737, 15), // "getP_GyroDriftX"
QT_MOC_LITERAL(45, 753, 15), // "getP_GyroDriftY"
QT_MOC_LITERAL(46, 769, 15), // "getP_GyroDriftZ"
QT_MOC_LITERAL(47, 785, 15), // "P_PositionNorth"
QT_MOC_LITERAL(48, 801, 14), // "P_PositionEast"
QT_MOC_LITERAL(49, 816, 14), // "P_PositionDown"
QT_MOC_LITERAL(50, 831, 15), // "P_VelocityNorth"
QT_MOC_LITERAL(51, 847, 14), // "P_VelocityEast"
QT_MOC_LITERAL(52, 862, 14), // "P_VelocityDown"
QT_MOC_LITERAL(53, 877, 12), // "P_AttitudeQ1"
QT_MOC_LITERAL(54, 890, 12), // "P_AttitudeQ2"
QT_MOC_LITERAL(55, 903, 12), // "P_AttitudeQ3"
QT_MOC_LITERAL(56, 916, 12), // "P_AttitudeQ4"
QT_MOC_LITERAL(57, 929, 12), // "P_GyroDriftX"
QT_MOC_LITERAL(58, 942, 12), // "P_GyroDriftY"
QT_MOC_LITERAL(59, 955, 12) // "P_GyroDriftZ"

    },
    "EKFStateVariance\0PChanged\0\0index\0value\0"
    "P_PositionNorthChanged\0P_PositionEastChanged\0"
    "P_PositionDownChanged\0P_VelocityNorthChanged\0"
    "P_VelocityEastChanged\0P_VelocityDownChanged\0"
    "P_AttitudeQ1Changed\0P_AttitudeQ2Changed\0"
    "P_AttitudeQ3Changed\0P_AttitudeQ4Changed\0"
    "P_GyroDriftXChanged\0P_GyroDriftYChanged\0"
    "P_GyroDriftZChanged\0setP\0setP_PositionNorth\0"
    "setP_PositionEast\0setP_PositionDown\0"
    "setP_VelocityNorth\0setP_VelocityEast\0"
    "setP_VelocityDown\0setP_AttitudeQ1\0"
    "setP_AttitudeQ2\0setP_AttitudeQ3\0"
    "setP_AttitudeQ4\0setP_GyroDriftX\0"
    "setP_GyroDriftY\0setP_GyroDriftZ\0"
    "emitNotifications\0getP\0getP_PositionNorth\0"
    "getP_PositionEast\0getP_PositionDown\0"
    "getP_VelocityNorth\0getP_VelocityEast\0"
    "getP_VelocityDown\0getP_AttitudeQ1\0"
    "getP_AttitudeQ2\0getP_AttitudeQ3\0"
    "getP_AttitudeQ4\0getP_GyroDriftX\0"
    "getP_GyroDriftY\0getP_GyroDriftZ\0"
    "P_PositionNorth\0P_PositionEast\0"
    "P_PositionDown\0P_VelocityNorth\0"
    "P_VelocityEast\0P_VelocityDown\0"
    "P_AttitudeQ1\0P_AttitudeQ2\0P_AttitudeQ3\0"
    "P_AttitudeQ4\0P_GyroDriftX\0P_GyroDriftY\0"
    "P_GyroDriftZ"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EKFStateVariance[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
      13,  334, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  229,    2, 0x06 /* Public */,
       5,    1,  234,    2, 0x06 /* Public */,
       6,    1,  237,    2, 0x06 /* Public */,
       7,    1,  240,    2, 0x06 /* Public */,
       8,    1,  243,    2, 0x06 /* Public */,
       9,    1,  246,    2, 0x06 /* Public */,
      10,    1,  249,    2, 0x06 /* Public */,
      11,    1,  252,    2, 0x06 /* Public */,
      12,    1,  255,    2, 0x06 /* Public */,
      13,    1,  258,    2, 0x06 /* Public */,
      14,    1,  261,    2, 0x06 /* Public */,
      15,    1,  264,    2, 0x06 /* Public */,
      16,    1,  267,    2, 0x06 /* Public */,
      17,    1,  270,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    2,  273,    2, 0x0a /* Public */,
      19,    1,  278,    2, 0x0a /* Public */,
      20,    1,  281,    2, 0x0a /* Public */,
      21,    1,  284,    2, 0x0a /* Public */,
      22,    1,  287,    2, 0x0a /* Public */,
      23,    1,  290,    2, 0x0a /* Public */,
      24,    1,  293,    2, 0x0a /* Public */,
      25,    1,  296,    2, 0x0a /* Public */,
      26,    1,  299,    2, 0x0a /* Public */,
      27,    1,  302,    2, 0x0a /* Public */,
      28,    1,  305,    2, 0x0a /* Public */,
      29,    1,  308,    2, 0x0a /* Public */,
      30,    1,  311,    2, 0x0a /* Public */,
      31,    1,  314,    2, 0x0a /* Public */,
      32,    0,  317,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      33,    1,  318,    2, 0x02 /* Public */,
      34,    0,  321,    2, 0x02 /* Public */,
      35,    0,  322,    2, 0x02 /* Public */,
      36,    0,  323,    2, 0x02 /* Public */,
      37,    0,  324,    2, 0x02 /* Public */,
      38,    0,  325,    2, 0x02 /* Public */,
      39,    0,  326,    2, 0x02 /* Public */,
      40,    0,  327,    2, 0x02 /* Public */,
      41,    0,  328,    2, 0x02 /* Public */,
      42,    0,  329,    2, 0x02 /* Public */,
      43,    0,  330,    2, 0x02 /* Public */,
      44,    0,  331,    2, 0x02 /* Public */,
      45,    0,  332,    2, 0x02 /* Public */,
      46,    0,  333,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,

 // properties: name, type, flags
      47, QMetaType::Float, 0x00495103,
      48, QMetaType::Float, 0x00495103,
      49, QMetaType::Float, 0x00495103,
      50, QMetaType::Float, 0x00495103,
      51, QMetaType::Float, 0x00495103,
      52, QMetaType::Float, 0x00495103,
      53, QMetaType::Float, 0x00495103,
      54, QMetaType::Float, 0x00495103,
      55, QMetaType::Float, 0x00495103,
      56, QMetaType::Float, 0x00495103,
      57, QMetaType::Float, 0x00495103,
      58, QMetaType::Float, 0x00495103,
      59, QMetaType::Float, 0x00495103,

 // properties: notify_signal_id
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
      13,

       0        // eod
};

void EKFStateVariance::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EKFStateVariance *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->PChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->P_PositionNorthChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->P_PositionEastChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->P_PositionDownChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->P_VelocityNorthChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->P_VelocityEastChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->P_VelocityDownChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->P_AttitudeQ1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->P_AttitudeQ2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->P_AttitudeQ3Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->P_AttitudeQ4Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->P_GyroDriftXChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->P_GyroDriftYChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->P_GyroDriftZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->setP((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 15: _t->setP_PositionNorth((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->setP_PositionEast((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 17: _t->setP_PositionDown((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->setP_VelocityNorth((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->setP_VelocityEast((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->setP_VelocityDown((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->setP_AttitudeQ1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: _t->setP_AttitudeQ2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->setP_AttitudeQ3((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->setP_AttitudeQ4((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 25: _t->setP_GyroDriftX((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 26: _t->setP_GyroDriftY((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->setP_GyroDriftZ((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 28: _t->emitNotifications(); break;
        case 29: { float _r = _t->getP((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 30: { float _r = _t->getP_PositionNorth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 31: { float _r = _t->getP_PositionEast();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 32: { float _r = _t->getP_PositionDown();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 33: { float _r = _t->getP_VelocityNorth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 34: { float _r = _t->getP_VelocityEast();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 35: { float _r = _t->getP_VelocityDown();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 36: { float _r = _t->getP_AttitudeQ1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 37: { float _r = _t->getP_AttitudeQ2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 38: { float _r = _t->getP_AttitudeQ3();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 39: { float _r = _t->getP_AttitudeQ4();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 40: { float _r = _t->getP_GyroDriftX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 41: { float _r = _t->getP_GyroDriftY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 42: { float _r = _t->getP_GyroDriftZ();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EKFStateVariance::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::PChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EKFStateVariance::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::P_PositionNorthChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (EKFStateVariance::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::P_PositionEastChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (EKFStateVariance::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::P_PositionDownChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (EKFStateVariance::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::P_VelocityNorthChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (EKFStateVariance::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::P_VelocityEastChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (EKFStateVariance::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::P_VelocityDownChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (EKFStateVariance::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::P_AttitudeQ1Changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (EKFStateVariance::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::P_AttitudeQ2Changed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (EKFStateVariance::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::P_AttitudeQ3Changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (EKFStateVariance::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::P_AttitudeQ4Changed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (EKFStateVariance::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::P_GyroDriftXChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (EKFStateVariance::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::P_GyroDriftYChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (EKFStateVariance::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EKFStateVariance::P_GyroDriftZChanged)) {
                *result = 13;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<EKFStateVariance *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getP_PositionNorth(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getP_PositionEast(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getP_PositionDown(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getP_VelocityNorth(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getP_VelocityEast(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getP_VelocityDown(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getP_AttitudeQ1(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getP_AttitudeQ2(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getP_AttitudeQ3(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->getP_AttitudeQ4(); break;
        case 10: *reinterpret_cast< float*>(_v) = _t->getP_GyroDriftX(); break;
        case 11: *reinterpret_cast< float*>(_v) = _t->getP_GyroDriftY(); break;
        case 12: *reinterpret_cast< float*>(_v) = _t->getP_GyroDriftZ(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<EKFStateVariance *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setP_PositionNorth(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setP_PositionEast(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setP_PositionDown(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setP_VelocityNorth(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setP_VelocityEast(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setP_VelocityDown(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setP_AttitudeQ1(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setP_AttitudeQ2(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setP_AttitudeQ3(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setP_AttitudeQ4(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setP_GyroDriftX(*reinterpret_cast< float*>(_v)); break;
        case 11: _t->setP_GyroDriftY(*reinterpret_cast< float*>(_v)); break;
        case 12: _t->setP_GyroDriftZ(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject EKFStateVariance::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_EKFStateVariance.data,
    qt_meta_data_EKFStateVariance,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EKFStateVariance::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EKFStateVariance::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EKFStateVariance.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int EKFStateVariance::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 43)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 43)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 43;
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
void EKFStateVariance::PChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EKFStateVariance::P_PositionNorthChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void EKFStateVariance::P_PositionEastChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void EKFStateVariance::P_PositionDownChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void EKFStateVariance::P_VelocityNorthChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void EKFStateVariance::P_VelocityEastChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void EKFStateVariance::P_VelocityDownChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void EKFStateVariance::P_AttitudeQ1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void EKFStateVariance::P_AttitudeQ2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void EKFStateVariance::P_AttitudeQ3Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void EKFStateVariance::P_AttitudeQ4Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void EKFStateVariance::P_GyroDriftXChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void EKFStateVariance::P_GyroDriftYChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void EKFStateVariance::P_GyroDriftZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
