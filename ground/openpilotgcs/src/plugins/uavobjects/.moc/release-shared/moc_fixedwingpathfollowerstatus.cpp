/****************************************************************************
** Meta object code from reading C++ file 'fixedwingpathfollowerstatus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/fixedwingpathfollowerstatus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fixedwingpathfollowerstatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FixedWingPathFollowerStatus_t {
    QByteArrayData data[85];
    char stringdata0[1458];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FixedWingPathFollowerStatus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FixedWingPathFollowerStatus_t qt_meta_stringdata_FixedWingPathFollowerStatus = {
    {
QT_MOC_LITERAL(0, 0, 27), // "FixedWingPathFollowerStatus"
QT_MOC_LITERAL(1, 28, 12), // "ErrorChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 5), // "index"
QT_MOC_LITERAL(4, 48, 5), // "value"
QT_MOC_LITERAL(5, 54, 19), // "Error_CourseChanged"
QT_MOC_LITERAL(6, 74, 18), // "Error_SpeedChanged"
QT_MOC_LITERAL(7, 93, 18), // "Error_PowerChanged"
QT_MOC_LITERAL(8, 112, 15), // "ErrorIntChanged"
QT_MOC_LITERAL(9, 128, 22), // "ErrorInt_CourseChanged"
QT_MOC_LITERAL(10, 151, 21), // "ErrorInt_SpeedChanged"
QT_MOC_LITERAL(11, 173, 21), // "ErrorInt_PowerChanged"
QT_MOC_LITERAL(12, 195, 14), // "CommandChanged"
QT_MOC_LITERAL(13, 210, 21), // "Command_CourseChanged"
QT_MOC_LITERAL(14, 232, 20), // "Command_SpeedChanged"
QT_MOC_LITERAL(15, 253, 20), // "Command_PowerChanged"
QT_MOC_LITERAL(16, 274, 13), // "ErrorsChanged"
QT_MOC_LITERAL(17, 288, 18), // "Errors_WindChanged"
QT_MOC_LITERAL(18, 307, 24), // "Errors_StallspeedChanged"
QT_MOC_LITERAL(19, 332, 22), // "Errors_LowspeedChanged"
QT_MOC_LITERAL(20, 355, 23), // "Errors_HighspeedChanged"
QT_MOC_LITERAL(21, 379, 23), // "Errors_OverspeedChanged"
QT_MOC_LITERAL(22, 403, 22), // "Errors_LowpowerChanged"
QT_MOC_LITERAL(23, 426, 23), // "Errors_HighpowerChanged"
QT_MOC_LITERAL(24, 450, 26), // "Errors_PitchcontrolChanged"
QT_MOC_LITERAL(25, 477, 8), // "setError"
QT_MOC_LITERAL(26, 486, 15), // "setError_Course"
QT_MOC_LITERAL(27, 502, 14), // "setError_Speed"
QT_MOC_LITERAL(28, 517, 14), // "setError_Power"
QT_MOC_LITERAL(29, 532, 11), // "setErrorInt"
QT_MOC_LITERAL(30, 544, 18), // "setErrorInt_Course"
QT_MOC_LITERAL(31, 563, 17), // "setErrorInt_Speed"
QT_MOC_LITERAL(32, 581, 17), // "setErrorInt_Power"
QT_MOC_LITERAL(33, 599, 10), // "setCommand"
QT_MOC_LITERAL(34, 610, 17), // "setCommand_Course"
QT_MOC_LITERAL(35, 628, 16), // "setCommand_Speed"
QT_MOC_LITERAL(36, 645, 16), // "setCommand_Power"
QT_MOC_LITERAL(37, 662, 9), // "setErrors"
QT_MOC_LITERAL(38, 672, 14), // "setErrors_Wind"
QT_MOC_LITERAL(39, 687, 20), // "setErrors_Stallspeed"
QT_MOC_LITERAL(40, 708, 18), // "setErrors_Lowspeed"
QT_MOC_LITERAL(41, 727, 19), // "setErrors_Highspeed"
QT_MOC_LITERAL(42, 747, 19), // "setErrors_Overspeed"
QT_MOC_LITERAL(43, 767, 18), // "setErrors_Lowpower"
QT_MOC_LITERAL(44, 786, 19), // "setErrors_Highpower"
QT_MOC_LITERAL(45, 806, 22), // "setErrors_Pitchcontrol"
QT_MOC_LITERAL(46, 829, 17), // "emitNotifications"
QT_MOC_LITERAL(47, 847, 8), // "getError"
QT_MOC_LITERAL(48, 856, 15), // "getError_Course"
QT_MOC_LITERAL(49, 872, 14), // "getError_Speed"
QT_MOC_LITERAL(50, 887, 14), // "getError_Power"
QT_MOC_LITERAL(51, 902, 11), // "getErrorInt"
QT_MOC_LITERAL(52, 914, 18), // "getErrorInt_Course"
QT_MOC_LITERAL(53, 933, 17), // "getErrorInt_Speed"
QT_MOC_LITERAL(54, 951, 17), // "getErrorInt_Power"
QT_MOC_LITERAL(55, 969, 10), // "getCommand"
QT_MOC_LITERAL(56, 980, 17), // "getCommand_Course"
QT_MOC_LITERAL(57, 998, 16), // "getCommand_Speed"
QT_MOC_LITERAL(58, 1015, 16), // "getCommand_Power"
QT_MOC_LITERAL(59, 1032, 9), // "getErrors"
QT_MOC_LITERAL(60, 1042, 14), // "getErrors_Wind"
QT_MOC_LITERAL(61, 1057, 20), // "getErrors_Stallspeed"
QT_MOC_LITERAL(62, 1078, 18), // "getErrors_Lowspeed"
QT_MOC_LITERAL(63, 1097, 19), // "getErrors_Highspeed"
QT_MOC_LITERAL(64, 1117, 19), // "getErrors_Overspeed"
QT_MOC_LITERAL(65, 1137, 18), // "getErrors_Lowpower"
QT_MOC_LITERAL(66, 1156, 19), // "getErrors_Highpower"
QT_MOC_LITERAL(67, 1176, 22), // "getErrors_Pitchcontrol"
QT_MOC_LITERAL(68, 1199, 12), // "Error_Course"
QT_MOC_LITERAL(69, 1212, 11), // "Error_Speed"
QT_MOC_LITERAL(70, 1224, 11), // "Error_Power"
QT_MOC_LITERAL(71, 1236, 15), // "ErrorInt_Course"
QT_MOC_LITERAL(72, 1252, 14), // "ErrorInt_Speed"
QT_MOC_LITERAL(73, 1267, 14), // "ErrorInt_Power"
QT_MOC_LITERAL(74, 1282, 14), // "Command_Course"
QT_MOC_LITERAL(75, 1297, 13), // "Command_Speed"
QT_MOC_LITERAL(76, 1311, 13), // "Command_Power"
QT_MOC_LITERAL(77, 1325, 11), // "Errors_Wind"
QT_MOC_LITERAL(78, 1337, 17), // "Errors_Stallspeed"
QT_MOC_LITERAL(79, 1355, 15), // "Errors_Lowspeed"
QT_MOC_LITERAL(80, 1371, 16), // "Errors_Highspeed"
QT_MOC_LITERAL(81, 1388, 16), // "Errors_Overspeed"
QT_MOC_LITERAL(82, 1405, 15), // "Errors_Lowpower"
QT_MOC_LITERAL(83, 1421, 16), // "Errors_Highpower"
QT_MOC_LITERAL(84, 1438, 19) // "Errors_Pitchcontrol"

    },
    "FixedWingPathFollowerStatus\0ErrorChanged\0"
    "\0index\0value\0Error_CourseChanged\0"
    "Error_SpeedChanged\0Error_PowerChanged\0"
    "ErrorIntChanged\0ErrorInt_CourseChanged\0"
    "ErrorInt_SpeedChanged\0ErrorInt_PowerChanged\0"
    "CommandChanged\0Command_CourseChanged\0"
    "Command_SpeedChanged\0Command_PowerChanged\0"
    "ErrorsChanged\0Errors_WindChanged\0"
    "Errors_StallspeedChanged\0"
    "Errors_LowspeedChanged\0Errors_HighspeedChanged\0"
    "Errors_OverspeedChanged\0Errors_LowpowerChanged\0"
    "Errors_HighpowerChanged\0"
    "Errors_PitchcontrolChanged\0setError\0"
    "setError_Course\0setError_Speed\0"
    "setError_Power\0setErrorInt\0"
    "setErrorInt_Course\0setErrorInt_Speed\0"
    "setErrorInt_Power\0setCommand\0"
    "setCommand_Course\0setCommand_Speed\0"
    "setCommand_Power\0setErrors\0setErrors_Wind\0"
    "setErrors_Stallspeed\0setErrors_Lowspeed\0"
    "setErrors_Highspeed\0setErrors_Overspeed\0"
    "setErrors_Lowpower\0setErrors_Highpower\0"
    "setErrors_Pitchcontrol\0emitNotifications\0"
    "getError\0getError_Course\0getError_Speed\0"
    "getError_Power\0getErrorInt\0"
    "getErrorInt_Course\0getErrorInt_Speed\0"
    "getErrorInt_Power\0getCommand\0"
    "getCommand_Course\0getCommand_Speed\0"
    "getCommand_Power\0getErrors\0getErrors_Wind\0"
    "getErrors_Stallspeed\0getErrors_Lowspeed\0"
    "getErrors_Highspeed\0getErrors_Overspeed\0"
    "getErrors_Lowpower\0getErrors_Highpower\0"
    "getErrors_Pitchcontrol\0Error_Course\0"
    "Error_Speed\0Error_Power\0ErrorInt_Course\0"
    "ErrorInt_Speed\0ErrorInt_Power\0"
    "Command_Course\0Command_Speed\0Command_Power\0"
    "Errors_Wind\0Errors_Stallspeed\0"
    "Errors_Lowspeed\0Errors_Highspeed\0"
    "Errors_Overspeed\0Errors_Lowpower\0"
    "Errors_Highpower\0Errors_Pitchcontrol"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FixedWingPathFollowerStatus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      64,   14, // methods
      17,  506, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      21,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  334,    2, 0x06 /* Public */,
       5,    1,  339,    2, 0x06 /* Public */,
       6,    1,  342,    2, 0x06 /* Public */,
       7,    1,  345,    2, 0x06 /* Public */,
       8,    2,  348,    2, 0x06 /* Public */,
       9,    1,  353,    2, 0x06 /* Public */,
      10,    1,  356,    2, 0x06 /* Public */,
      11,    1,  359,    2, 0x06 /* Public */,
      12,    2,  362,    2, 0x06 /* Public */,
      13,    1,  367,    2, 0x06 /* Public */,
      14,    1,  370,    2, 0x06 /* Public */,
      15,    1,  373,    2, 0x06 /* Public */,
      16,    2,  376,    2, 0x06 /* Public */,
      17,    1,  381,    2, 0x06 /* Public */,
      18,    1,  384,    2, 0x06 /* Public */,
      19,    1,  387,    2, 0x06 /* Public */,
      20,    1,  390,    2, 0x06 /* Public */,
      21,    1,  393,    2, 0x06 /* Public */,
      22,    1,  396,    2, 0x06 /* Public */,
      23,    1,  399,    2, 0x06 /* Public */,
      24,    1,  402,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      25,    2,  405,    2, 0x0a /* Public */,
      26,    1,  410,    2, 0x0a /* Public */,
      27,    1,  413,    2, 0x0a /* Public */,
      28,    1,  416,    2, 0x0a /* Public */,
      29,    2,  419,    2, 0x0a /* Public */,
      30,    1,  424,    2, 0x0a /* Public */,
      31,    1,  427,    2, 0x0a /* Public */,
      32,    1,  430,    2, 0x0a /* Public */,
      33,    2,  433,    2, 0x0a /* Public */,
      34,    1,  438,    2, 0x0a /* Public */,
      35,    1,  441,    2, 0x0a /* Public */,
      36,    1,  444,    2, 0x0a /* Public */,
      37,    2,  447,    2, 0x0a /* Public */,
      38,    1,  452,    2, 0x0a /* Public */,
      39,    1,  455,    2, 0x0a /* Public */,
      40,    1,  458,    2, 0x0a /* Public */,
      41,    1,  461,    2, 0x0a /* Public */,
      42,    1,  464,    2, 0x0a /* Public */,
      43,    1,  467,    2, 0x0a /* Public */,
      44,    1,  470,    2, 0x0a /* Public */,
      45,    1,  473,    2, 0x0a /* Public */,
      46,    0,  476,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      47,    1,  477,    2, 0x02 /* Public */,
      48,    0,  480,    2, 0x02 /* Public */,
      49,    0,  481,    2, 0x02 /* Public */,
      50,    0,  482,    2, 0x02 /* Public */,
      51,    1,  483,    2, 0x02 /* Public */,
      52,    0,  486,    2, 0x02 /* Public */,
      53,    0,  487,    2, 0x02 /* Public */,
      54,    0,  488,    2, 0x02 /* Public */,
      55,    1,  489,    2, 0x02 /* Public */,
      56,    0,  492,    2, 0x02 /* Public */,
      57,    0,  493,    2, 0x02 /* Public */,
      58,    0,  494,    2, 0x02 /* Public */,
      59,    1,  495,    2, 0x02 /* Public */,
      60,    0,  498,    2, 0x02 /* Public */,
      61,    0,  499,    2, 0x02 /* Public */,
      62,    0,  500,    2, 0x02 /* Public */,
      63,    0,  501,    2, 0x02 /* Public */,
      64,    0,  502,    2, 0x02 /* Public */,
      65,    0,  503,    2, 0x02 /* Public */,
      66,    0,  504,    2, 0x02 /* Public */,
      67,    0,  505,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
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
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
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
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
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
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar, QMetaType::UInt,    3,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
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
      76, QMetaType::Float, 0x00495103,
      77, QMetaType::UChar, 0x00495103,
      78, QMetaType::UChar, 0x00495103,
      79, QMetaType::UChar, 0x00495103,
      80, QMetaType::UChar, 0x00495103,
      81, QMetaType::UChar, 0x00495103,
      82, QMetaType::UChar, 0x00495103,
      83, QMetaType::UChar, 0x00495103,
      84, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       1,
       2,
       3,
       5,
       6,
       7,
       9,
      10,
      11,
      13,
      14,
      15,
      16,
      17,
      18,
      19,
      20,

       0        // eod
};

void FixedWingPathFollowerStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FixedWingPathFollowerStatus *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ErrorChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->Error_CourseChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->Error_SpeedChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->Error_PowerChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->ErrorIntChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->ErrorInt_CourseChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->ErrorInt_SpeedChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->ErrorInt_PowerChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->CommandChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 9: _t->Command_CourseChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->Command_SpeedChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->Command_PowerChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->ErrorsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 13: _t->Errors_WindChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->Errors_StallspeedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 15: _t->Errors_LowspeedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 16: _t->Errors_HighspeedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->Errors_OverspeedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 18: _t->Errors_LowpowerChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 19: _t->Errors_HighpowerChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->Errors_PitchcontrolChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 21: _t->setError((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 22: _t->setError_Course((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->setError_Speed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->setError_Power((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 25: _t->setErrorInt((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 26: _t->setErrorInt_Course((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->setErrorInt_Speed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 28: _t->setErrorInt_Power((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 29: _t->setCommand((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 30: _t->setCommand_Course((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 31: _t->setCommand_Speed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 32: _t->setCommand_Power((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 33: _t->setErrors((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 34: _t->setErrors_Wind((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 35: _t->setErrors_Stallspeed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 36: _t->setErrors_Lowspeed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 37: _t->setErrors_Highspeed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 38: _t->setErrors_Overspeed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 39: _t->setErrors_Lowpower((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 40: _t->setErrors_Highpower((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 41: _t->setErrors_Pitchcontrol((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 42: _t->emitNotifications(); break;
        case 43: { float _r = _t->getError((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 44: { float _r = _t->getError_Course();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 45: { float _r = _t->getError_Speed();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 46: { float _r = _t->getError_Power();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 47: { float _r = _t->getErrorInt((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 48: { float _r = _t->getErrorInt_Course();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 49: { float _r = _t->getErrorInt_Speed();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 50: { float _r = _t->getErrorInt_Power();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 51: { float _r = _t->getCommand((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 52: { float _r = _t->getCommand_Course();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 53: { float _r = _t->getCommand_Speed();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 54: { float _r = _t->getCommand_Power();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 55: { quint8 _r = _t->getErrors((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 56: { quint8 _r = _t->getErrors_Wind();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 57: { quint8 _r = _t->getErrors_Stallspeed();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 58: { quint8 _r = _t->getErrors_Lowspeed();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 59: { quint8 _r = _t->getErrors_Highspeed();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 60: { quint8 _r = _t->getErrors_Overspeed();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 61: { quint8 _r = _t->getErrors_Lowpower();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 62: { quint8 _r = _t->getErrors_Highpower();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 63: { quint8 _r = _t->getErrors_Pitchcontrol();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FixedWingPathFollowerStatus::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::ErrorChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Error_CourseChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Error_SpeedChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Error_PowerChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::ErrorIntChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::ErrorInt_CourseChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::ErrorInt_SpeedChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::ErrorInt_PowerChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::CommandChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Command_CourseChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Command_SpeedChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Command_PowerChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::ErrorsChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Errors_WindChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Errors_StallspeedChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Errors_LowspeedChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Errors_HighspeedChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Errors_OverspeedChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Errors_LowpowerChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Errors_HighpowerChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (FixedWingPathFollowerStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FixedWingPathFollowerStatus::Errors_PitchcontrolChanged)) {
                *result = 20;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FixedWingPathFollowerStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getError_Course(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getError_Speed(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getError_Power(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getErrorInt_Course(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getErrorInt_Speed(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getErrorInt_Power(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getCommand_Course(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getCommand_Speed(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getCommand_Power(); break;
        case 9: *reinterpret_cast< quint8*>(_v) = _t->getErrors_Wind(); break;
        case 10: *reinterpret_cast< quint8*>(_v) = _t->getErrors_Stallspeed(); break;
        case 11: *reinterpret_cast< quint8*>(_v) = _t->getErrors_Lowspeed(); break;
        case 12: *reinterpret_cast< quint8*>(_v) = _t->getErrors_Highspeed(); break;
        case 13: *reinterpret_cast< quint8*>(_v) = _t->getErrors_Overspeed(); break;
        case 14: *reinterpret_cast< quint8*>(_v) = _t->getErrors_Lowpower(); break;
        case 15: *reinterpret_cast< quint8*>(_v) = _t->getErrors_Highpower(); break;
        case 16: *reinterpret_cast< quint8*>(_v) = _t->getErrors_Pitchcontrol(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<FixedWingPathFollowerStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setError_Course(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setError_Speed(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setError_Power(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setErrorInt_Course(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setErrorInt_Speed(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setErrorInt_Power(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setCommand_Course(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setCommand_Speed(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setCommand_Power(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setErrors_Wind(*reinterpret_cast< quint8*>(_v)); break;
        case 10: _t->setErrors_Stallspeed(*reinterpret_cast< quint8*>(_v)); break;
        case 11: _t->setErrors_Lowspeed(*reinterpret_cast< quint8*>(_v)); break;
        case 12: _t->setErrors_Highspeed(*reinterpret_cast< quint8*>(_v)); break;
        case 13: _t->setErrors_Overspeed(*reinterpret_cast< quint8*>(_v)); break;
        case 14: _t->setErrors_Lowpower(*reinterpret_cast< quint8*>(_v)); break;
        case 15: _t->setErrors_Highpower(*reinterpret_cast< quint8*>(_v)); break;
        case 16: _t->setErrors_Pitchcontrol(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject FixedWingPathFollowerStatus::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_FixedWingPathFollowerStatus.data,
    qt_meta_data_FixedWingPathFollowerStatus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FixedWingPathFollowerStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FixedWingPathFollowerStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FixedWingPathFollowerStatus.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int FixedWingPathFollowerStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 17;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FixedWingPathFollowerStatus::ErrorChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FixedWingPathFollowerStatus::Error_CourseChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FixedWingPathFollowerStatus::Error_SpeedChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FixedWingPathFollowerStatus::Error_PowerChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FixedWingPathFollowerStatus::ErrorIntChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FixedWingPathFollowerStatus::ErrorInt_CourseChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void FixedWingPathFollowerStatus::ErrorInt_SpeedChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void FixedWingPathFollowerStatus::ErrorInt_PowerChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void FixedWingPathFollowerStatus::CommandChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void FixedWingPathFollowerStatus::Command_CourseChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void FixedWingPathFollowerStatus::Command_SpeedChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void FixedWingPathFollowerStatus::Command_PowerChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void FixedWingPathFollowerStatus::ErrorsChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void FixedWingPathFollowerStatus::Errors_WindChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void FixedWingPathFollowerStatus::Errors_StallspeedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void FixedWingPathFollowerStatus::Errors_LowspeedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void FixedWingPathFollowerStatus::Errors_HighspeedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void FixedWingPathFollowerStatus::Errors_OverspeedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void FixedWingPathFollowerStatus::Errors_LowpowerChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void FixedWingPathFollowerStatus::Errors_HighpowerChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void FixedWingPathFollowerStatus::Errors_PitchcontrolChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
