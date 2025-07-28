/****************************************************************************
** Meta object code from reading C++ file 'auxmagsettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/auxmagsettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'auxmagsettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AuxMagSettings_t {
    QByteArrayData data[75];
    char stringdata0[1333];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AuxMagSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AuxMagSettings_t qt_meta_stringdata_AuxMagSettings = {
    {
QT_MOC_LITERAL(0, 0, 14), // "AuxMagSettings"
QT_MOC_LITERAL(1, 15, 15), // "mag_biasChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "index"
QT_MOC_LITERAL(4, 38, 5), // "value"
QT_MOC_LITERAL(5, 44, 17), // "mag_bias_XChanged"
QT_MOC_LITERAL(6, 62, 17), // "mag_bias_YChanged"
QT_MOC_LITERAL(7, 80, 17), // "mag_bias_ZChanged"
QT_MOC_LITERAL(8, 98, 20), // "mag_transformChanged"
QT_MOC_LITERAL(9, 119, 25), // "mag_transform_r0c0Changed"
QT_MOC_LITERAL(10, 145, 25), // "mag_transform_r0c1Changed"
QT_MOC_LITERAL(11, 171, 25), // "mag_transform_r0c2Changed"
QT_MOC_LITERAL(12, 197, 25), // "mag_transform_r1c0Changed"
QT_MOC_LITERAL(13, 223, 25), // "mag_transform_r1c1Changed"
QT_MOC_LITERAL(14, 249, 25), // "mag_transform_r1c2Changed"
QT_MOC_LITERAL(15, 275, 25), // "mag_transform_r2c0Changed"
QT_MOC_LITERAL(16, 301, 25), // "mag_transform_r2c1Changed"
QT_MOC_LITERAL(17, 327, 25), // "mag_transform_r2c2Changed"
QT_MOC_LITERAL(18, 353, 25), // "MagBiasNullingRateChanged"
QT_MOC_LITERAL(19, 379, 18), // "OrientationChanged"
QT_MOC_LITERAL(20, 398, 11), // "TypeChanged"
QT_MOC_LITERAL(21, 410, 12), // "UsageChanged"
QT_MOC_LITERAL(22, 423, 11), // "setmag_bias"
QT_MOC_LITERAL(23, 435, 13), // "setmag_bias_X"
QT_MOC_LITERAL(24, 449, 13), // "setmag_bias_Y"
QT_MOC_LITERAL(25, 463, 13), // "setmag_bias_Z"
QT_MOC_LITERAL(26, 477, 16), // "setmag_transform"
QT_MOC_LITERAL(27, 494, 21), // "setmag_transform_r0c0"
QT_MOC_LITERAL(28, 516, 21), // "setmag_transform_r0c1"
QT_MOC_LITERAL(29, 538, 21), // "setmag_transform_r0c2"
QT_MOC_LITERAL(30, 560, 21), // "setmag_transform_r1c0"
QT_MOC_LITERAL(31, 582, 21), // "setmag_transform_r1c1"
QT_MOC_LITERAL(32, 604, 21), // "setmag_transform_r1c2"
QT_MOC_LITERAL(33, 626, 21), // "setmag_transform_r2c0"
QT_MOC_LITERAL(34, 648, 21), // "setmag_transform_r2c1"
QT_MOC_LITERAL(35, 670, 21), // "setmag_transform_r2c2"
QT_MOC_LITERAL(36, 692, 21), // "setMagBiasNullingRate"
QT_MOC_LITERAL(37, 714, 14), // "setOrientation"
QT_MOC_LITERAL(38, 729, 7), // "setType"
QT_MOC_LITERAL(39, 737, 8), // "setUsage"
QT_MOC_LITERAL(40, 746, 17), // "emitNotifications"
QT_MOC_LITERAL(41, 764, 11), // "getmag_bias"
QT_MOC_LITERAL(42, 776, 13), // "getmag_bias_X"
QT_MOC_LITERAL(43, 790, 13), // "getmag_bias_Y"
QT_MOC_LITERAL(44, 804, 13), // "getmag_bias_Z"
QT_MOC_LITERAL(45, 818, 16), // "getmag_transform"
QT_MOC_LITERAL(46, 835, 21), // "getmag_transform_r0c0"
QT_MOC_LITERAL(47, 857, 21), // "getmag_transform_r0c1"
QT_MOC_LITERAL(48, 879, 21), // "getmag_transform_r0c2"
QT_MOC_LITERAL(49, 901, 21), // "getmag_transform_r1c0"
QT_MOC_LITERAL(50, 923, 21), // "getmag_transform_r1c1"
QT_MOC_LITERAL(51, 945, 21), // "getmag_transform_r1c2"
QT_MOC_LITERAL(52, 967, 21), // "getmag_transform_r2c0"
QT_MOC_LITERAL(53, 989, 21), // "getmag_transform_r2c1"
QT_MOC_LITERAL(54, 1011, 21), // "getmag_transform_r2c2"
QT_MOC_LITERAL(55, 1033, 21), // "getMagBiasNullingRate"
QT_MOC_LITERAL(56, 1055, 14), // "getOrientation"
QT_MOC_LITERAL(57, 1070, 7), // "getType"
QT_MOC_LITERAL(58, 1078, 8), // "getUsage"
QT_MOC_LITERAL(59, 1087, 10), // "mag_bias_X"
QT_MOC_LITERAL(60, 1098, 10), // "mag_bias_Y"
QT_MOC_LITERAL(61, 1109, 10), // "mag_bias_Z"
QT_MOC_LITERAL(62, 1120, 18), // "mag_transform_r0c0"
QT_MOC_LITERAL(63, 1139, 18), // "mag_transform_r0c1"
QT_MOC_LITERAL(64, 1158, 18), // "mag_transform_r0c2"
QT_MOC_LITERAL(65, 1177, 18), // "mag_transform_r1c0"
QT_MOC_LITERAL(66, 1196, 18), // "mag_transform_r1c1"
QT_MOC_LITERAL(67, 1215, 18), // "mag_transform_r1c2"
QT_MOC_LITERAL(68, 1234, 18), // "mag_transform_r2c0"
QT_MOC_LITERAL(69, 1253, 18), // "mag_transform_r2c1"
QT_MOC_LITERAL(70, 1272, 18), // "mag_transform_r2c2"
QT_MOC_LITERAL(71, 1291, 18), // "MagBiasNullingRate"
QT_MOC_LITERAL(72, 1310, 11), // "Orientation"
QT_MOC_LITERAL(73, 1322, 4), // "Type"
QT_MOC_LITERAL(74, 1327, 5) // "Usage"

    },
    "AuxMagSettings\0mag_biasChanged\0\0index\0"
    "value\0mag_bias_XChanged\0mag_bias_YChanged\0"
    "mag_bias_ZChanged\0mag_transformChanged\0"
    "mag_transform_r0c0Changed\0"
    "mag_transform_r0c1Changed\0"
    "mag_transform_r0c2Changed\0"
    "mag_transform_r1c0Changed\0"
    "mag_transform_r1c1Changed\0"
    "mag_transform_r1c2Changed\0"
    "mag_transform_r2c0Changed\0"
    "mag_transform_r2c1Changed\0"
    "mag_transform_r2c2Changed\0"
    "MagBiasNullingRateChanged\0OrientationChanged\0"
    "TypeChanged\0UsageChanged\0setmag_bias\0"
    "setmag_bias_X\0setmag_bias_Y\0setmag_bias_Z\0"
    "setmag_transform\0setmag_transform_r0c0\0"
    "setmag_transform_r0c1\0setmag_transform_r0c2\0"
    "setmag_transform_r1c0\0setmag_transform_r1c1\0"
    "setmag_transform_r1c2\0setmag_transform_r2c0\0"
    "setmag_transform_r2c1\0setmag_transform_r2c2\0"
    "setMagBiasNullingRate\0setOrientation\0"
    "setType\0setUsage\0emitNotifications\0"
    "getmag_bias\0getmag_bias_X\0getmag_bias_Y\0"
    "getmag_bias_Z\0getmag_transform\0"
    "getmag_transform_r0c0\0getmag_transform_r0c1\0"
    "getmag_transform_r0c2\0getmag_transform_r1c0\0"
    "getmag_transform_r1c1\0getmag_transform_r1c2\0"
    "getmag_transform_r2c0\0getmag_transform_r2c1\0"
    "getmag_transform_r2c2\0getMagBiasNullingRate\0"
    "getOrientation\0getType\0getUsage\0"
    "mag_bias_X\0mag_bias_Y\0mag_bias_Z\0"
    "mag_transform_r0c0\0mag_transform_r0c1\0"
    "mag_transform_r0c2\0mag_transform_r1c0\0"
    "mag_transform_r1c1\0mag_transform_r1c2\0"
    "mag_transform_r2c0\0mag_transform_r2c1\0"
    "mag_transform_r2c2\0MagBiasNullingRate\0"
    "Orientation\0Type\0Usage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuxMagSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      55,   14, // methods
      16,  428, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  289,    2, 0x06 /* Public */,
       5,    1,  294,    2, 0x06 /* Public */,
       6,    1,  297,    2, 0x06 /* Public */,
       7,    1,  300,    2, 0x06 /* Public */,
       8,    2,  303,    2, 0x06 /* Public */,
       9,    1,  308,    2, 0x06 /* Public */,
      10,    1,  311,    2, 0x06 /* Public */,
      11,    1,  314,    2, 0x06 /* Public */,
      12,    1,  317,    2, 0x06 /* Public */,
      13,    1,  320,    2, 0x06 /* Public */,
      14,    1,  323,    2, 0x06 /* Public */,
      15,    1,  326,    2, 0x06 /* Public */,
      16,    1,  329,    2, 0x06 /* Public */,
      17,    1,  332,    2, 0x06 /* Public */,
      18,    1,  335,    2, 0x06 /* Public */,
      19,    1,  338,    2, 0x06 /* Public */,
      20,    1,  341,    2, 0x06 /* Public */,
      21,    1,  344,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      22,    2,  347,    2, 0x0a /* Public */,
      23,    1,  352,    2, 0x0a /* Public */,
      24,    1,  355,    2, 0x0a /* Public */,
      25,    1,  358,    2, 0x0a /* Public */,
      26,    2,  361,    2, 0x0a /* Public */,
      27,    1,  366,    2, 0x0a /* Public */,
      28,    1,  369,    2, 0x0a /* Public */,
      29,    1,  372,    2, 0x0a /* Public */,
      30,    1,  375,    2, 0x0a /* Public */,
      31,    1,  378,    2, 0x0a /* Public */,
      32,    1,  381,    2, 0x0a /* Public */,
      33,    1,  384,    2, 0x0a /* Public */,
      34,    1,  387,    2, 0x0a /* Public */,
      35,    1,  390,    2, 0x0a /* Public */,
      36,    1,  393,    2, 0x0a /* Public */,
      37,    1,  396,    2, 0x0a /* Public */,
      38,    1,  399,    2, 0x0a /* Public */,
      39,    1,  402,    2, 0x0a /* Public */,
      40,    0,  405,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      41,    1,  406,    2, 0x02 /* Public */,
      42,    0,  409,    2, 0x02 /* Public */,
      43,    0,  410,    2, 0x02 /* Public */,
      44,    0,  411,    2, 0x02 /* Public */,
      45,    1,  412,    2, 0x02 /* Public */,
      46,    0,  415,    2, 0x02 /* Public */,
      47,    0,  416,    2, 0x02 /* Public */,
      48,    0,  417,    2, 0x02 /* Public */,
      49,    0,  418,    2, 0x02 /* Public */,
      50,    0,  419,    2, 0x02 /* Public */,
      51,    0,  420,    2, 0x02 /* Public */,
      52,    0,  421,    2, 0x02 /* Public */,
      53,    0,  422,    2, 0x02 /* Public */,
      54,    0,  423,    2, 0x02 /* Public */,
      55,    0,  424,    2, 0x02 /* Public */,
      56,    0,  425,    2, 0x02 /* Public */,
      57,    0,  426,    2, 0x02 /* Public */,
      58,    0,  427,    2, 0x02 /* Public */,

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
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
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
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
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
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      59, QMetaType::Float, 0x00495003,
      60, QMetaType::Float, 0x00495003,
      61, QMetaType::Float, 0x00495003,
      62, QMetaType::Float, 0x00495003,
      63, QMetaType::Float, 0x00495003,
      64, QMetaType::Float, 0x00495003,
      65, QMetaType::Float, 0x00495003,
      66, QMetaType::Float, 0x00495003,
      67, QMetaType::Float, 0x00495003,
      68, QMetaType::Float, 0x00495003,
      69, QMetaType::Float, 0x00495003,
      70, QMetaType::Float, 0x00495003,
      71, QMetaType::Float, 0x00495103,
      72, QMetaType::Float, 0x00495103,
      73, QMetaType::UChar, 0x00495103,
      74, QMetaType::UChar, 0x00495103,

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
      16,
      17,

       0        // eod
};

void AuxMagSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AuxMagSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->mag_biasChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->mag_bias_XChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->mag_bias_YChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->mag_bias_ZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->mag_transformChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->mag_transform_r0c0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->mag_transform_r0c1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->mag_transform_r0c2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->mag_transform_r1c0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->mag_transform_r1c1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->mag_transform_r1c2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->mag_transform_r2c0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->mag_transform_r2c1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->mag_transform_r2c2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->MagBiasNullingRateChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->OrientationChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->TypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->UsageChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 18: _t->setmag_bias((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 19: _t->setmag_bias_X((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->setmag_bias_Y((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->setmag_bias_Z((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: _t->setmag_transform((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 23: _t->setmag_transform_r0c0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->setmag_transform_r0c1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 25: _t->setmag_transform_r0c2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 26: _t->setmag_transform_r1c0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->setmag_transform_r1c1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 28: _t->setmag_transform_r1c2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 29: _t->setmag_transform_r2c0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 30: _t->setmag_transform_r2c1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 31: _t->setmag_transform_r2c2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 32: _t->setMagBiasNullingRate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 33: _t->setOrientation((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 34: _t->setType((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 35: _t->setUsage((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 36: _t->emitNotifications(); break;
        case 37: { float _r = _t->getmag_bias((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 38: { float _r = _t->getmag_bias_X();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 39: { float _r = _t->getmag_bias_Y();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 40: { float _r = _t->getmag_bias_Z();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 41: { float _r = _t->getmag_transform((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 42: { float _r = _t->getmag_transform_r0c0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 43: { float _r = _t->getmag_transform_r0c1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 44: { float _r = _t->getmag_transform_r0c2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 45: { float _r = _t->getmag_transform_r1c0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 46: { float _r = _t->getmag_transform_r1c1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 47: { float _r = _t->getmag_transform_r1c2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 48: { float _r = _t->getmag_transform_r2c0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 49: { float _r = _t->getmag_transform_r2c1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 50: { float _r = _t->getmag_transform_r2c2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 51: { float _r = _t->getMagBiasNullingRate();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 52: { float _r = _t->getOrientation();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 53: { quint8 _r = _t->getType();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 54: { quint8 _r = _t->getUsage();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AuxMagSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_biasChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_bias_XChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_bias_YChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_bias_ZChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_transformChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_transform_r0c0Changed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_transform_r0c1Changed)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_transform_r0c2Changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_transform_r1c0Changed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_transform_r1c1Changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_transform_r1c2Changed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_transform_r2c0Changed)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_transform_r2c1Changed)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::mag_transform_r2c2Changed)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::MagBiasNullingRateChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::OrientationChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::TypeChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (AuxMagSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuxMagSettings::UsageChanged)) {
                *result = 17;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AuxMagSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getmag_bias_X(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getmag_bias_Y(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getmag_bias_Z(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getmag_transform_r0c0(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getmag_transform_r0c1(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getmag_transform_r0c2(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getmag_transform_r1c0(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getmag_transform_r1c1(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getmag_transform_r1c2(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->getmag_transform_r2c0(); break;
        case 10: *reinterpret_cast< float*>(_v) = _t->getmag_transform_r2c1(); break;
        case 11: *reinterpret_cast< float*>(_v) = _t->getmag_transform_r2c2(); break;
        case 12: *reinterpret_cast< float*>(_v) = _t->getMagBiasNullingRate(); break;
        case 13: *reinterpret_cast< float*>(_v) = _t->getOrientation(); break;
        case 14: *reinterpret_cast< quint8*>(_v) = _t->getType(); break;
        case 15: *reinterpret_cast< quint8*>(_v) = _t->getUsage(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<AuxMagSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setmag_bias_X(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setmag_bias_Y(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setmag_bias_Z(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setmag_transform_r0c0(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setmag_transform_r0c1(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setmag_transform_r0c2(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setmag_transform_r1c0(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setmag_transform_r1c1(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setmag_transform_r1c2(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setmag_transform_r2c0(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setmag_transform_r2c1(*reinterpret_cast< float*>(_v)); break;
        case 11: _t->setmag_transform_r2c2(*reinterpret_cast< float*>(_v)); break;
        case 12: _t->setMagBiasNullingRate(*reinterpret_cast< float*>(_v)); break;
        case 13: _t->setOrientation(*reinterpret_cast< float*>(_v)); break;
        case 14: _t->setType(*reinterpret_cast< quint8*>(_v)); break;
        case 15: _t->setUsage(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject AuxMagSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_AuxMagSettings.data,
    qt_meta_data_AuxMagSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AuxMagSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuxMagSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AuxMagSettings.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int AuxMagSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 55)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 55;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 55)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 55;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 16;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AuxMagSettings::mag_biasChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AuxMagSettings::mag_bias_XChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AuxMagSettings::mag_bias_YChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AuxMagSettings::mag_bias_ZChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AuxMagSettings::mag_transformChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AuxMagSettings::mag_transform_r0c0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AuxMagSettings::mag_transform_r0c1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AuxMagSettings::mag_transform_r0c2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AuxMagSettings::mag_transform_r1c0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void AuxMagSettings::mag_transform_r1c1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void AuxMagSettings::mag_transform_r1c2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void AuxMagSettings::mag_transform_r2c0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void AuxMagSettings::mag_transform_r2c1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void AuxMagSettings::mag_transform_r2c2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void AuxMagSettings::MagBiasNullingRateChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void AuxMagSettings::OrientationChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void AuxMagSettings::TypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void AuxMagSettings::UsageChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
