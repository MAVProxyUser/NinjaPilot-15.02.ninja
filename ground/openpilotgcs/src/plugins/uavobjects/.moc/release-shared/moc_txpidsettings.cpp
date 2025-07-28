/****************************************************************************
** Meta object code from reading C++ file 'txpidsettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/txpidsettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'txpidsettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TxPIDSettings_t {
    QByteArrayData data[84];
    char stringdata0[1462];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TxPIDSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TxPIDSettings_t qt_meta_stringdata_TxPIDSettings = {
    {
QT_MOC_LITERAL(0, 0, 13), // "TxPIDSettings"
QT_MOC_LITERAL(1, 14, 20), // "ThrottleRangeChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "index"
QT_MOC_LITERAL(4, 42, 5), // "value"
QT_MOC_LITERAL(5, 48, 24), // "ThrottleRange_MinChanged"
QT_MOC_LITERAL(6, 73, 24), // "ThrottleRange_MaxChanged"
QT_MOC_LITERAL(7, 98, 13), // "MinPIDChanged"
QT_MOC_LITERAL(8, 112, 23), // "MinPID_Instance1Changed"
QT_MOC_LITERAL(9, 136, 23), // "MinPID_Instance2Changed"
QT_MOC_LITERAL(10, 160, 23), // "MinPID_Instance3Changed"
QT_MOC_LITERAL(11, 184, 13), // "MaxPIDChanged"
QT_MOC_LITERAL(12, 198, 23), // "MaxPID_Instance1Changed"
QT_MOC_LITERAL(13, 222, 23), // "MaxPID_Instance2Changed"
QT_MOC_LITERAL(14, 246, 23), // "MaxPID_Instance3Changed"
QT_MOC_LITERAL(15, 270, 17), // "UpdateModeChanged"
QT_MOC_LITERAL(16, 288, 17), // "BankNumberChanged"
QT_MOC_LITERAL(17, 306, 13), // "InputsChanged"
QT_MOC_LITERAL(18, 320, 23), // "Inputs_Instance1Changed"
QT_MOC_LITERAL(19, 344, 23), // "Inputs_Instance2Changed"
QT_MOC_LITERAL(20, 368, 23), // "Inputs_Instance3Changed"
QT_MOC_LITERAL(21, 392, 11), // "PIDsChanged"
QT_MOC_LITERAL(22, 404, 21), // "PIDs_Instance1Changed"
QT_MOC_LITERAL(23, 426, 21), // "PIDs_Instance2Changed"
QT_MOC_LITERAL(24, 448, 21), // "PIDs_Instance3Changed"
QT_MOC_LITERAL(25, 470, 16), // "setThrottleRange"
QT_MOC_LITERAL(26, 487, 20), // "setThrottleRange_Min"
QT_MOC_LITERAL(27, 508, 20), // "setThrottleRange_Max"
QT_MOC_LITERAL(28, 529, 9), // "setMinPID"
QT_MOC_LITERAL(29, 539, 19), // "setMinPID_Instance1"
QT_MOC_LITERAL(30, 559, 19), // "setMinPID_Instance2"
QT_MOC_LITERAL(31, 579, 19), // "setMinPID_Instance3"
QT_MOC_LITERAL(32, 599, 9), // "setMaxPID"
QT_MOC_LITERAL(33, 609, 19), // "setMaxPID_Instance1"
QT_MOC_LITERAL(34, 629, 19), // "setMaxPID_Instance2"
QT_MOC_LITERAL(35, 649, 19), // "setMaxPID_Instance3"
QT_MOC_LITERAL(36, 669, 13), // "setUpdateMode"
QT_MOC_LITERAL(37, 683, 13), // "setBankNumber"
QT_MOC_LITERAL(38, 697, 9), // "setInputs"
QT_MOC_LITERAL(39, 707, 19), // "setInputs_Instance1"
QT_MOC_LITERAL(40, 727, 19), // "setInputs_Instance2"
QT_MOC_LITERAL(41, 747, 19), // "setInputs_Instance3"
QT_MOC_LITERAL(42, 767, 7), // "setPIDs"
QT_MOC_LITERAL(43, 775, 17), // "setPIDs_Instance1"
QT_MOC_LITERAL(44, 793, 17), // "setPIDs_Instance2"
QT_MOC_LITERAL(45, 811, 17), // "setPIDs_Instance3"
QT_MOC_LITERAL(46, 829, 17), // "emitNotifications"
QT_MOC_LITERAL(47, 847, 16), // "getThrottleRange"
QT_MOC_LITERAL(48, 864, 20), // "getThrottleRange_Min"
QT_MOC_LITERAL(49, 885, 20), // "getThrottleRange_Max"
QT_MOC_LITERAL(50, 906, 9), // "getMinPID"
QT_MOC_LITERAL(51, 916, 19), // "getMinPID_Instance1"
QT_MOC_LITERAL(52, 936, 19), // "getMinPID_Instance2"
QT_MOC_LITERAL(53, 956, 19), // "getMinPID_Instance3"
QT_MOC_LITERAL(54, 976, 9), // "getMaxPID"
QT_MOC_LITERAL(55, 986, 19), // "getMaxPID_Instance1"
QT_MOC_LITERAL(56, 1006, 19), // "getMaxPID_Instance2"
QT_MOC_LITERAL(57, 1026, 19), // "getMaxPID_Instance3"
QT_MOC_LITERAL(58, 1046, 13), // "getUpdateMode"
QT_MOC_LITERAL(59, 1060, 13), // "getBankNumber"
QT_MOC_LITERAL(60, 1074, 9), // "getInputs"
QT_MOC_LITERAL(61, 1084, 19), // "getInputs_Instance1"
QT_MOC_LITERAL(62, 1104, 19), // "getInputs_Instance2"
QT_MOC_LITERAL(63, 1124, 19), // "getInputs_Instance3"
QT_MOC_LITERAL(64, 1144, 7), // "getPIDs"
QT_MOC_LITERAL(65, 1152, 17), // "getPIDs_Instance1"
QT_MOC_LITERAL(66, 1170, 17), // "getPIDs_Instance2"
QT_MOC_LITERAL(67, 1188, 17), // "getPIDs_Instance3"
QT_MOC_LITERAL(68, 1206, 17), // "ThrottleRange_Min"
QT_MOC_LITERAL(69, 1224, 17), // "ThrottleRange_Max"
QT_MOC_LITERAL(70, 1242, 16), // "MinPID_Instance1"
QT_MOC_LITERAL(71, 1259, 16), // "MinPID_Instance2"
QT_MOC_LITERAL(72, 1276, 16), // "MinPID_Instance3"
QT_MOC_LITERAL(73, 1293, 16), // "MaxPID_Instance1"
QT_MOC_LITERAL(74, 1310, 16), // "MaxPID_Instance2"
QT_MOC_LITERAL(75, 1327, 16), // "MaxPID_Instance3"
QT_MOC_LITERAL(76, 1344, 10), // "UpdateMode"
QT_MOC_LITERAL(77, 1355, 10), // "BankNumber"
QT_MOC_LITERAL(78, 1366, 16), // "Inputs_Instance1"
QT_MOC_LITERAL(79, 1383, 16), // "Inputs_Instance2"
QT_MOC_LITERAL(80, 1400, 16), // "Inputs_Instance3"
QT_MOC_LITERAL(81, 1417, 14), // "PIDs_Instance1"
QT_MOC_LITERAL(82, 1432, 14), // "PIDs_Instance2"
QT_MOC_LITERAL(83, 1447, 14) // "PIDs_Instance3"

    },
    "TxPIDSettings\0ThrottleRangeChanged\0\0"
    "index\0value\0ThrottleRange_MinChanged\0"
    "ThrottleRange_MaxChanged\0MinPIDChanged\0"
    "MinPID_Instance1Changed\0MinPID_Instance2Changed\0"
    "MinPID_Instance3Changed\0MaxPIDChanged\0"
    "MaxPID_Instance1Changed\0MaxPID_Instance2Changed\0"
    "MaxPID_Instance3Changed\0UpdateModeChanged\0"
    "BankNumberChanged\0InputsChanged\0"
    "Inputs_Instance1Changed\0Inputs_Instance2Changed\0"
    "Inputs_Instance3Changed\0PIDsChanged\0"
    "PIDs_Instance1Changed\0PIDs_Instance2Changed\0"
    "PIDs_Instance3Changed\0setThrottleRange\0"
    "setThrottleRange_Min\0setThrottleRange_Max\0"
    "setMinPID\0setMinPID_Instance1\0"
    "setMinPID_Instance2\0setMinPID_Instance3\0"
    "setMaxPID\0setMaxPID_Instance1\0"
    "setMaxPID_Instance2\0setMaxPID_Instance3\0"
    "setUpdateMode\0setBankNumber\0setInputs\0"
    "setInputs_Instance1\0setInputs_Instance2\0"
    "setInputs_Instance3\0setPIDs\0"
    "setPIDs_Instance1\0setPIDs_Instance2\0"
    "setPIDs_Instance3\0emitNotifications\0"
    "getThrottleRange\0getThrottleRange_Min\0"
    "getThrottleRange_Max\0getMinPID\0"
    "getMinPID_Instance1\0getMinPID_Instance2\0"
    "getMinPID_Instance3\0getMaxPID\0"
    "getMaxPID_Instance1\0getMaxPID_Instance2\0"
    "getMaxPID_Instance3\0getUpdateMode\0"
    "getBankNumber\0getInputs\0getInputs_Instance1\0"
    "getInputs_Instance2\0getInputs_Instance3\0"
    "getPIDs\0getPIDs_Instance1\0getPIDs_Instance2\0"
    "getPIDs_Instance3\0ThrottleRange_Min\0"
    "ThrottleRange_Max\0MinPID_Instance1\0"
    "MinPID_Instance2\0MinPID_Instance3\0"
    "MaxPID_Instance1\0MaxPID_Instance2\0"
    "MaxPID_Instance3\0UpdateMode\0BankNumber\0"
    "Inputs_Instance1\0Inputs_Instance2\0"
    "Inputs_Instance3\0PIDs_Instance1\0"
    "PIDs_Instance2\0PIDs_Instance3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TxPIDSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      64,   14, // methods
      16,  512, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      21,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  334,    2, 0x06 /* Public */,
       5,    1,  339,    2, 0x06 /* Public */,
       6,    1,  342,    2, 0x06 /* Public */,
       7,    2,  345,    2, 0x06 /* Public */,
       8,    1,  350,    2, 0x06 /* Public */,
       9,    1,  353,    2, 0x06 /* Public */,
      10,    1,  356,    2, 0x06 /* Public */,
      11,    2,  359,    2, 0x06 /* Public */,
      12,    1,  364,    2, 0x06 /* Public */,
      13,    1,  367,    2, 0x06 /* Public */,
      14,    1,  370,    2, 0x06 /* Public */,
      15,    1,  373,    2, 0x06 /* Public */,
      16,    1,  376,    2, 0x06 /* Public */,
      17,    2,  379,    2, 0x06 /* Public */,
      18,    1,  384,    2, 0x06 /* Public */,
      19,    1,  387,    2, 0x06 /* Public */,
      20,    1,  390,    2, 0x06 /* Public */,
      21,    2,  393,    2, 0x06 /* Public */,
      22,    1,  398,    2, 0x06 /* Public */,
      23,    1,  401,    2, 0x06 /* Public */,
      24,    1,  404,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      25,    2,  407,    2, 0x0a /* Public */,
      26,    1,  412,    2, 0x0a /* Public */,
      27,    1,  415,    2, 0x0a /* Public */,
      28,    2,  418,    2, 0x0a /* Public */,
      29,    1,  423,    2, 0x0a /* Public */,
      30,    1,  426,    2, 0x0a /* Public */,
      31,    1,  429,    2, 0x0a /* Public */,
      32,    2,  432,    2, 0x0a /* Public */,
      33,    1,  437,    2, 0x0a /* Public */,
      34,    1,  440,    2, 0x0a /* Public */,
      35,    1,  443,    2, 0x0a /* Public */,
      36,    1,  446,    2, 0x0a /* Public */,
      37,    1,  449,    2, 0x0a /* Public */,
      38,    2,  452,    2, 0x0a /* Public */,
      39,    1,  457,    2, 0x0a /* Public */,
      40,    1,  460,    2, 0x0a /* Public */,
      41,    1,  463,    2, 0x0a /* Public */,
      42,    2,  466,    2, 0x0a /* Public */,
      43,    1,  471,    2, 0x0a /* Public */,
      44,    1,  474,    2, 0x0a /* Public */,
      45,    1,  477,    2, 0x0a /* Public */,
      46,    0,  480,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      47,    1,  481,    2, 0x02 /* Public */,
      48,    0,  484,    2, 0x02 /* Public */,
      49,    0,  485,    2, 0x02 /* Public */,
      50,    1,  486,    2, 0x02 /* Public */,
      51,    0,  489,    2, 0x02 /* Public */,
      52,    0,  490,    2, 0x02 /* Public */,
      53,    0,  491,    2, 0x02 /* Public */,
      54,    1,  492,    2, 0x02 /* Public */,
      55,    0,  495,    2, 0x02 /* Public */,
      56,    0,  496,    2, 0x02 /* Public */,
      57,    0,  497,    2, 0x02 /* Public */,
      58,    0,  498,    2, 0x02 /* Public */,
      59,    0,  499,    2, 0x02 /* Public */,
      60,    1,  500,    2, 0x02 /* Public */,
      61,    0,  503,    2, 0x02 /* Public */,
      62,    0,  504,    2, 0x02 /* Public */,
      63,    0,  505,    2, 0x02 /* Public */,
      64,    1,  506,    2, 0x02 /* Public */,
      65,    0,  509,    2, 0x02 /* Public */,
      66,    0,  510,    2, 0x02 /* Public */,
      67,    0,  511,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    3,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    3,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
      68, QMetaType::Float, 0x00495103,
      69, QMetaType::Float, 0x00495103,
      70, QMetaType::Float, 0x00495103,
      71, QMetaType::Float, 0x00495103,
      72, QMetaType::Float, 0x00495103,
      73, QMetaType::Float, 0x00495103,
      74, QMetaType::Float, 0x00495103,
      75, QMetaType::Float, 0x00495103,
      76, QMetaType::UChar, 0x00495103,
      77, QMetaType::UChar, 0x00495103,
      78, QMetaType::UChar, 0x00495103,
      79, QMetaType::UChar, 0x00495103,
      80, QMetaType::UChar, 0x00495103,
      81, QMetaType::UChar, 0x00495103,
      82, QMetaType::UChar, 0x00495103,
      83, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       1,
       2,
       4,
       5,
       6,
       8,
       9,
      10,
      11,
      12,
      14,
      15,
      16,
      18,
      19,
      20,

       0        // eod
};

void TxPIDSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TxPIDSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ThrottleRangeChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->ThrottleRange_MinChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->ThrottleRange_MaxChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->MinPIDChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 4: _t->MinPID_Instance1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->MinPID_Instance2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->MinPID_Instance3Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->MaxPIDChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 8: _t->MaxPID_Instance1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->MaxPID_Instance2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->MaxPID_Instance3Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->UpdateModeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->BankNumberChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 13: _t->InputsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 14: _t->Inputs_Instance1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 15: _t->Inputs_Instance2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 16: _t->Inputs_Instance3Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->PIDsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 18: _t->PIDs_Instance1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 19: _t->PIDs_Instance2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->PIDs_Instance3Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 21: _t->setThrottleRange((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 22: _t->setThrottleRange_Min((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->setThrottleRange_Max((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->setMinPID((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 25: _t->setMinPID_Instance1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 26: _t->setMinPID_Instance2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->setMinPID_Instance3((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 28: _t->setMaxPID((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 29: _t->setMaxPID_Instance1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 30: _t->setMaxPID_Instance2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 31: _t->setMaxPID_Instance3((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 32: _t->setUpdateMode((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 33: _t->setBankNumber((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 34: _t->setInputs((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 35: _t->setInputs_Instance1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 36: _t->setInputs_Instance2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 37: _t->setInputs_Instance3((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 38: _t->setPIDs((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 39: _t->setPIDs_Instance1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 40: _t->setPIDs_Instance2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 41: _t->setPIDs_Instance3((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 42: _t->emitNotifications(); break;
        case 43: { float _r = _t->getThrottleRange((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 44: { float _r = _t->getThrottleRange_Min();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 45: { float _r = _t->getThrottleRange_Max();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 46: { float _r = _t->getMinPID((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 47: { float _r = _t->getMinPID_Instance1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 48: { float _r = _t->getMinPID_Instance2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 49: { float _r = _t->getMinPID_Instance3();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 50: { float _r = _t->getMaxPID((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 51: { float _r = _t->getMaxPID_Instance1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 52: { float _r = _t->getMaxPID_Instance2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 53: { float _r = _t->getMaxPID_Instance3();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 54: { quint8 _r = _t->getUpdateMode();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 55: { quint8 _r = _t->getBankNumber();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 56: { quint8 _r = _t->getInputs((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 57: { quint8 _r = _t->getInputs_Instance1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 58: { quint8 _r = _t->getInputs_Instance2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 59: { quint8 _r = _t->getInputs_Instance3();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 60: { quint8 _r = _t->getPIDs((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 61: { quint8 _r = _t->getPIDs_Instance1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 62: { quint8 _r = _t->getPIDs_Instance2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 63: { quint8 _r = _t->getPIDs_Instance3();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TxPIDSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::ThrottleRangeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::ThrottleRange_MinChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::ThrottleRange_MaxChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::MinPIDChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::MinPID_Instance1Changed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::MinPID_Instance2Changed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::MinPID_Instance3Changed)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::MaxPIDChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::MaxPID_Instance1Changed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::MaxPID_Instance2Changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::MaxPID_Instance3Changed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::UpdateModeChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::BankNumberChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::InputsChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::Inputs_Instance1Changed)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::Inputs_Instance2Changed)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::Inputs_Instance3Changed)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::PIDsChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::PIDs_Instance1Changed)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::PIDs_Instance2Changed)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (TxPIDSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TxPIDSettings::PIDs_Instance3Changed)) {
                *result = 20;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<TxPIDSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getThrottleRange_Min(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getThrottleRange_Max(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getMinPID_Instance1(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getMinPID_Instance2(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getMinPID_Instance3(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getMaxPID_Instance1(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getMaxPID_Instance2(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getMaxPID_Instance3(); break;
        case 8: *reinterpret_cast< quint8*>(_v) = _t->getUpdateMode(); break;
        case 9: *reinterpret_cast< quint8*>(_v) = _t->getBankNumber(); break;
        case 10: *reinterpret_cast< quint8*>(_v) = _t->getInputs_Instance1(); break;
        case 11: *reinterpret_cast< quint8*>(_v) = _t->getInputs_Instance2(); break;
        case 12: *reinterpret_cast< quint8*>(_v) = _t->getInputs_Instance3(); break;
        case 13: *reinterpret_cast< quint8*>(_v) = _t->getPIDs_Instance1(); break;
        case 14: *reinterpret_cast< quint8*>(_v) = _t->getPIDs_Instance2(); break;
        case 15: *reinterpret_cast< quint8*>(_v) = _t->getPIDs_Instance3(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<TxPIDSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setThrottleRange_Min(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setThrottleRange_Max(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setMinPID_Instance1(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setMinPID_Instance2(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setMinPID_Instance3(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setMaxPID_Instance1(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setMaxPID_Instance2(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setMaxPID_Instance3(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setUpdateMode(*reinterpret_cast< quint8*>(_v)); break;
        case 9: _t->setBankNumber(*reinterpret_cast< quint8*>(_v)); break;
        case 10: _t->setInputs_Instance1(*reinterpret_cast< quint8*>(_v)); break;
        case 11: _t->setInputs_Instance2(*reinterpret_cast< quint8*>(_v)); break;
        case 12: _t->setInputs_Instance3(*reinterpret_cast< quint8*>(_v)); break;
        case 13: _t->setPIDs_Instance1(*reinterpret_cast< quint8*>(_v)); break;
        case 14: _t->setPIDs_Instance2(*reinterpret_cast< quint8*>(_v)); break;
        case 15: _t->setPIDs_Instance3(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject TxPIDSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_TxPIDSettings.data,
    qt_meta_data_TxPIDSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TxPIDSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TxPIDSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TxPIDSettings.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int TxPIDSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 64)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 64;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 64)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 64;
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
void TxPIDSettings::ThrottleRangeChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TxPIDSettings::ThrottleRange_MinChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TxPIDSettings::ThrottleRange_MaxChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TxPIDSettings::MinPIDChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TxPIDSettings::MinPID_Instance1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TxPIDSettings::MinPID_Instance2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TxPIDSettings::MinPID_Instance3Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void TxPIDSettings::MaxPIDChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void TxPIDSettings::MaxPID_Instance1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void TxPIDSettings::MaxPID_Instance2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void TxPIDSettings::MaxPID_Instance3Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void TxPIDSettings::UpdateModeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void TxPIDSettings::BankNumberChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void TxPIDSettings::InputsChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void TxPIDSettings::Inputs_Instance1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void TxPIDSettings::Inputs_Instance2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void TxPIDSettings::Inputs_Instance3Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void TxPIDSettings::PIDsChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void TxPIDSettings::PIDs_Instance1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void TxPIDSettings::PIDs_Instance2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void TxPIDSettings::PIDs_Instance3Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
