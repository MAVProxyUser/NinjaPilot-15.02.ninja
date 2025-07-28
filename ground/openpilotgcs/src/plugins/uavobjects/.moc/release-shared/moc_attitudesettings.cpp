/****************************************************************************
** Meta object code from reading C++ file 'attitudesettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/attitudesettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'attitudesettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AttitudeSettings_t {
    QByteArrayData data[67];
    char stringdata0[1107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AttitudeSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AttitudeSettings_t qt_meta_stringdata_AttitudeSettings = {
    {
QT_MOC_LITERAL(0, 0, 16), // "AttitudeSettings"
QT_MOC_LITERAL(1, 17, 20), // "BoardRotationChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5), // "index"
QT_MOC_LITERAL(4, 45, 5), // "value"
QT_MOC_LITERAL(5, 51, 25), // "BoardRotation_RollChanged"
QT_MOC_LITERAL(6, 77, 26), // "BoardRotation_PitchChanged"
QT_MOC_LITERAL(7, 104, 24), // "BoardRotation_YawChanged"
QT_MOC_LITERAL(8, 129, 21), // "BoardLevelTrimChanged"
QT_MOC_LITERAL(9, 151, 26), // "BoardLevelTrim_RollChanged"
QT_MOC_LITERAL(10, 178, 27), // "BoardLevelTrim_PitchChanged"
QT_MOC_LITERAL(11, 206, 14), // "AccelKpChanged"
QT_MOC_LITERAL(12, 221, 14), // "AccelKiChanged"
QT_MOC_LITERAL(13, 236, 12), // "MagKiChanged"
QT_MOC_LITERAL(14, 249, 12), // "MagKpChanged"
QT_MOC_LITERAL(15, 262, 15), // "AccelTauChanged"
QT_MOC_LITERAL(16, 278, 18), // "YawBiasRateChanged"
QT_MOC_LITERAL(17, 297, 23), // "ZeroDuringArmingChanged"
QT_MOC_LITERAL(18, 321, 22), // "BiasCorrectGyroChanged"
QT_MOC_LITERAL(19, 344, 17), // "TrimFlightChanged"
QT_MOC_LITERAL(20, 362, 16), // "setBoardRotation"
QT_MOC_LITERAL(21, 379, 21), // "setBoardRotation_Roll"
QT_MOC_LITERAL(22, 401, 22), // "setBoardRotation_Pitch"
QT_MOC_LITERAL(23, 424, 20), // "setBoardRotation_Yaw"
QT_MOC_LITERAL(24, 445, 17), // "setBoardLevelTrim"
QT_MOC_LITERAL(25, 463, 22), // "setBoardLevelTrim_Roll"
QT_MOC_LITERAL(26, 486, 23), // "setBoardLevelTrim_Pitch"
QT_MOC_LITERAL(27, 510, 10), // "setAccelKp"
QT_MOC_LITERAL(28, 521, 10), // "setAccelKi"
QT_MOC_LITERAL(29, 532, 8), // "setMagKi"
QT_MOC_LITERAL(30, 541, 8), // "setMagKp"
QT_MOC_LITERAL(31, 550, 11), // "setAccelTau"
QT_MOC_LITERAL(32, 562, 14), // "setYawBiasRate"
QT_MOC_LITERAL(33, 577, 19), // "setZeroDuringArming"
QT_MOC_LITERAL(34, 597, 18), // "setBiasCorrectGyro"
QT_MOC_LITERAL(35, 616, 13), // "setTrimFlight"
QT_MOC_LITERAL(36, 630, 17), // "emitNotifications"
QT_MOC_LITERAL(37, 648, 16), // "getBoardRotation"
QT_MOC_LITERAL(38, 665, 21), // "getBoardRotation_Roll"
QT_MOC_LITERAL(39, 687, 22), // "getBoardRotation_Pitch"
QT_MOC_LITERAL(40, 710, 20), // "getBoardRotation_Yaw"
QT_MOC_LITERAL(41, 731, 17), // "getBoardLevelTrim"
QT_MOC_LITERAL(42, 749, 22), // "getBoardLevelTrim_Roll"
QT_MOC_LITERAL(43, 772, 23), // "getBoardLevelTrim_Pitch"
QT_MOC_LITERAL(44, 796, 10), // "getAccelKp"
QT_MOC_LITERAL(45, 807, 10), // "getAccelKi"
QT_MOC_LITERAL(46, 818, 8), // "getMagKi"
QT_MOC_LITERAL(47, 827, 8), // "getMagKp"
QT_MOC_LITERAL(48, 836, 11), // "getAccelTau"
QT_MOC_LITERAL(49, 848, 14), // "getYawBiasRate"
QT_MOC_LITERAL(50, 863, 19), // "getZeroDuringArming"
QT_MOC_LITERAL(51, 883, 18), // "getBiasCorrectGyro"
QT_MOC_LITERAL(52, 902, 13), // "getTrimFlight"
QT_MOC_LITERAL(53, 916, 18), // "BoardRotation_Roll"
QT_MOC_LITERAL(54, 935, 19), // "BoardRotation_Pitch"
QT_MOC_LITERAL(55, 955, 17), // "BoardRotation_Yaw"
QT_MOC_LITERAL(56, 973, 19), // "BoardLevelTrim_Roll"
QT_MOC_LITERAL(57, 993, 20), // "BoardLevelTrim_Pitch"
QT_MOC_LITERAL(58, 1014, 7), // "AccelKp"
QT_MOC_LITERAL(59, 1022, 7), // "AccelKi"
QT_MOC_LITERAL(60, 1030, 5), // "MagKi"
QT_MOC_LITERAL(61, 1036, 5), // "MagKp"
QT_MOC_LITERAL(62, 1042, 8), // "AccelTau"
QT_MOC_LITERAL(63, 1051, 11), // "YawBiasRate"
QT_MOC_LITERAL(64, 1063, 16), // "ZeroDuringArming"
QT_MOC_LITERAL(65, 1080, 15), // "BiasCorrectGyro"
QT_MOC_LITERAL(66, 1096, 10) // "TrimFlight"

    },
    "AttitudeSettings\0BoardRotationChanged\0"
    "\0index\0value\0BoardRotation_RollChanged\0"
    "BoardRotation_PitchChanged\0"
    "BoardRotation_YawChanged\0BoardLevelTrimChanged\0"
    "BoardLevelTrim_RollChanged\0"
    "BoardLevelTrim_PitchChanged\0AccelKpChanged\0"
    "AccelKiChanged\0MagKiChanged\0MagKpChanged\0"
    "AccelTauChanged\0YawBiasRateChanged\0"
    "ZeroDuringArmingChanged\0BiasCorrectGyroChanged\0"
    "TrimFlightChanged\0setBoardRotation\0"
    "setBoardRotation_Roll\0setBoardRotation_Pitch\0"
    "setBoardRotation_Yaw\0setBoardLevelTrim\0"
    "setBoardLevelTrim_Roll\0setBoardLevelTrim_Pitch\0"
    "setAccelKp\0setAccelKi\0setMagKi\0setMagKp\0"
    "setAccelTau\0setYawBiasRate\0"
    "setZeroDuringArming\0setBiasCorrectGyro\0"
    "setTrimFlight\0emitNotifications\0"
    "getBoardRotation\0getBoardRotation_Roll\0"
    "getBoardRotation_Pitch\0getBoardRotation_Yaw\0"
    "getBoardLevelTrim\0getBoardLevelTrim_Roll\0"
    "getBoardLevelTrim_Pitch\0getAccelKp\0"
    "getAccelKi\0getMagKi\0getMagKp\0getAccelTau\0"
    "getYawBiasRate\0getZeroDuringArming\0"
    "getBiasCorrectGyro\0getTrimFlight\0"
    "BoardRotation_Roll\0BoardRotation_Pitch\0"
    "BoardRotation_Yaw\0BoardLevelTrim_Roll\0"
    "BoardLevelTrim_Pitch\0AccelKp\0AccelKi\0"
    "MagKi\0MagKp\0AccelTau\0YawBiasRate\0"
    "ZeroDuringArming\0BiasCorrectGyro\0"
    "TrimFlight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AttitudeSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      49,   14, // methods
      14,  384, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  259,    2, 0x06 /* Public */,
       5,    1,  264,    2, 0x06 /* Public */,
       6,    1,  267,    2, 0x06 /* Public */,
       7,    1,  270,    2, 0x06 /* Public */,
       8,    2,  273,    2, 0x06 /* Public */,
       9,    1,  278,    2, 0x06 /* Public */,
      10,    1,  281,    2, 0x06 /* Public */,
      11,    1,  284,    2, 0x06 /* Public */,
      12,    1,  287,    2, 0x06 /* Public */,
      13,    1,  290,    2, 0x06 /* Public */,
      14,    1,  293,    2, 0x06 /* Public */,
      15,    1,  296,    2, 0x06 /* Public */,
      16,    1,  299,    2, 0x06 /* Public */,
      17,    1,  302,    2, 0x06 /* Public */,
      18,    1,  305,    2, 0x06 /* Public */,
      19,    1,  308,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    2,  311,    2, 0x0a /* Public */,
      21,    1,  316,    2, 0x0a /* Public */,
      22,    1,  319,    2, 0x0a /* Public */,
      23,    1,  322,    2, 0x0a /* Public */,
      24,    2,  325,    2, 0x0a /* Public */,
      25,    1,  330,    2, 0x0a /* Public */,
      26,    1,  333,    2, 0x0a /* Public */,
      27,    1,  336,    2, 0x0a /* Public */,
      28,    1,  339,    2, 0x0a /* Public */,
      29,    1,  342,    2, 0x0a /* Public */,
      30,    1,  345,    2, 0x0a /* Public */,
      31,    1,  348,    2, 0x0a /* Public */,
      32,    1,  351,    2, 0x0a /* Public */,
      33,    1,  354,    2, 0x0a /* Public */,
      34,    1,  357,    2, 0x0a /* Public */,
      35,    1,  360,    2, 0x0a /* Public */,
      36,    0,  363,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      37,    1,  364,    2, 0x02 /* Public */,
      38,    0,  367,    2, 0x02 /* Public */,
      39,    0,  368,    2, 0x02 /* Public */,
      40,    0,  369,    2, 0x02 /* Public */,
      41,    1,  370,    2, 0x02 /* Public */,
      42,    0,  373,    2, 0x02 /* Public */,
      43,    0,  374,    2, 0x02 /* Public */,
      44,    0,  375,    2, 0x02 /* Public */,
      45,    0,  376,    2, 0x02 /* Public */,
      46,    0,  377,    2, 0x02 /* Public */,
      47,    0,  378,    2, 0x02 /* Public */,
      48,    0,  379,    2, 0x02 /* Public */,
      49,    0,  380,    2, 0x02 /* Public */,
      50,    0,  381,    2, 0x02 /* Public */,
      51,    0,  382,    2, 0x02 /* Public */,
      52,    0,  383,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      53, QMetaType::Float, 0x00495103,
      54, QMetaType::Float, 0x00495103,
      55, QMetaType::Float, 0x00495103,
      56, QMetaType::Float, 0x00495103,
      57, QMetaType::Float, 0x00495103,
      58, QMetaType::Float, 0x00495103,
      59, QMetaType::Float, 0x00495103,
      60, QMetaType::Float, 0x00495103,
      61, QMetaType::Float, 0x00495103,
      62, QMetaType::Float, 0x00495103,
      63, QMetaType::Float, 0x00495103,
      64, QMetaType::UChar, 0x00495103,
      65, QMetaType::UChar, 0x00495103,
      66, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       1,
       2,
       3,
       5,
       6,
       7,
       8,
       9,
      10,
      11,
      12,
      13,
      14,
      15,

       0        // eod
};

void AttitudeSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AttitudeSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->BoardRotationChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->BoardRotation_RollChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->BoardRotation_PitchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->BoardRotation_YawChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->BoardLevelTrimChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->BoardLevelTrim_RollChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->BoardLevelTrim_PitchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->AccelKpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->AccelKiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->MagKiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->MagKpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->AccelTauChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->YawBiasRateChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->ZeroDuringArmingChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->BiasCorrectGyroChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 15: _t->TrimFlightChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 16: _t->setBoardRotation((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 17: _t->setBoardRotation_Roll((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->setBoardRotation_Pitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->setBoardRotation_Yaw((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->setBoardLevelTrim((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 21: _t->setBoardLevelTrim_Roll((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: _t->setBoardLevelTrim_Pitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->setAccelKp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->setAccelKi((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 25: _t->setMagKi((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 26: _t->setMagKp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->setAccelTau((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 28: _t->setYawBiasRate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 29: _t->setZeroDuringArming((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 30: _t->setBiasCorrectGyro((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 31: _t->setTrimFlight((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 32: _t->emitNotifications(); break;
        case 33: { float _r = _t->getBoardRotation((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 34: { float _r = _t->getBoardRotation_Roll();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 35: { float _r = _t->getBoardRotation_Pitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 36: { float _r = _t->getBoardRotation_Yaw();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 37: { float _r = _t->getBoardLevelTrim((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 38: { float _r = _t->getBoardLevelTrim_Roll();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 39: { float _r = _t->getBoardLevelTrim_Pitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 40: { float _r = _t->getAccelKp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 41: { float _r = _t->getAccelKi();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 42: { float _r = _t->getMagKi();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 43: { float _r = _t->getMagKp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 44: { float _r = _t->getAccelTau();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 45: { float _r = _t->getYawBiasRate();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 46: { quint8 _r = _t->getZeroDuringArming();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 47: { quint8 _r = _t->getBiasCorrectGyro();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 48: { quint8 _r = _t->getTrimFlight();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AttitudeSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::BoardRotationChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::BoardRotation_RollChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::BoardRotation_PitchChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::BoardRotation_YawChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::BoardLevelTrimChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::BoardLevelTrim_RollChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::BoardLevelTrim_PitchChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::AccelKpChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::AccelKiChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::MagKiChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::MagKpChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::AccelTauChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::YawBiasRateChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::ZeroDuringArmingChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::BiasCorrectGyroChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (AttitudeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AttitudeSettings::TrimFlightChanged)) {
                *result = 15;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AttitudeSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getBoardRotation_Roll(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getBoardRotation_Pitch(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getBoardRotation_Yaw(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getBoardLevelTrim_Roll(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getBoardLevelTrim_Pitch(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getAccelKp(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getAccelKi(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getMagKi(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getMagKp(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->getAccelTau(); break;
        case 10: *reinterpret_cast< float*>(_v) = _t->getYawBiasRate(); break;
        case 11: *reinterpret_cast< quint8*>(_v) = _t->getZeroDuringArming(); break;
        case 12: *reinterpret_cast< quint8*>(_v) = _t->getBiasCorrectGyro(); break;
        case 13: *reinterpret_cast< quint8*>(_v) = _t->getTrimFlight(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<AttitudeSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBoardRotation_Roll(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setBoardRotation_Pitch(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setBoardRotation_Yaw(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setBoardLevelTrim_Roll(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setBoardLevelTrim_Pitch(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setAccelKp(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setAccelKi(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setMagKi(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setMagKp(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setAccelTau(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setYawBiasRate(*reinterpret_cast< float*>(_v)); break;
        case 11: _t->setZeroDuringArming(*reinterpret_cast< quint8*>(_v)); break;
        case 12: _t->setBiasCorrectGyro(*reinterpret_cast< quint8*>(_v)); break;
        case 13: _t->setTrimFlight(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject AttitudeSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_AttitudeSettings.data,
    qt_meta_data_AttitudeSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AttitudeSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AttitudeSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AttitudeSettings.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int AttitudeSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 49)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 49;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 49)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 49;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 14;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AttitudeSettings::BoardRotationChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AttitudeSettings::BoardRotation_RollChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AttitudeSettings::BoardRotation_PitchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AttitudeSettings::BoardRotation_YawChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AttitudeSettings::BoardLevelTrimChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AttitudeSettings::BoardLevelTrim_RollChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AttitudeSettings::BoardLevelTrim_PitchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AttitudeSettings::AccelKpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AttitudeSettings::AccelKiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void AttitudeSettings::MagKiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void AttitudeSettings::MagKpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void AttitudeSettings::AccelTauChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void AttitudeSettings::YawBiasRateChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void AttitudeSettings::ZeroDuringArmingChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void AttitudeSettings::BiasCorrectGyroChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void AttitudeSettings::TrimFlightChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
