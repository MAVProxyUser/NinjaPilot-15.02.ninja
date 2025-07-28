/****************************************************************************
** Meta object code from reading C++ file 'oplinkstatus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/oplinkstatus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oplinkstatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OPLinkStatus_t {
    QByteArrayData data[178];
    char stringdata0[2614];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OPLinkStatus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OPLinkStatus_t qt_meta_stringdata_OPLinkStatus = {
    {
QT_MOC_LITERAL(0, 0, 12), // "OPLinkStatus"
QT_MOC_LITERAL(1, 13, 15), // "DeviceIDChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "value"
QT_MOC_LITERAL(4, 36, 14), // "PairIDsChanged"
QT_MOC_LITERAL(5, 51, 5), // "index"
QT_MOC_LITERAL(6, 57, 16), // "PairIDs_0Changed"
QT_MOC_LITERAL(7, 74, 16), // "PairIDs_1Changed"
QT_MOC_LITERAL(8, 91, 16), // "PairIDs_2Changed"
QT_MOC_LITERAL(9, 108, 16), // "PairIDs_3Changed"
QT_MOC_LITERAL(10, 125, 20), // "BoardRevisionChanged"
QT_MOC_LITERAL(11, 146, 20), // "HeapRemainingChanged"
QT_MOC_LITERAL(12, 167, 20), // "UAVTalkErrorsChanged"
QT_MOC_LITERAL(13, 188, 13), // "TXRateChanged"
QT_MOC_LITERAL(14, 202, 13), // "RXRateChanged"
QT_MOC_LITERAL(15, 216, 12), // "TXSeqChanged"
QT_MOC_LITERAL(16, 229, 12), // "RXSeqChanged"
QT_MOC_LITERAL(17, 242, 16), // "CPUSerialChanged"
QT_MOC_LITERAL(18, 259, 18), // "CPUSerial_0Changed"
QT_MOC_LITERAL(19, 278, 18), // "CPUSerial_1Changed"
QT_MOC_LITERAL(20, 297, 18), // "CPUSerial_2Changed"
QT_MOC_LITERAL(21, 316, 18), // "CPUSerial_3Changed"
QT_MOC_LITERAL(22, 335, 18), // "CPUSerial_4Changed"
QT_MOC_LITERAL(23, 354, 18), // "CPUSerial_5Changed"
QT_MOC_LITERAL(24, 373, 18), // "CPUSerial_6Changed"
QT_MOC_LITERAL(25, 392, 18), // "CPUSerial_7Changed"
QT_MOC_LITERAL(26, 411, 18), // "CPUSerial_8Changed"
QT_MOC_LITERAL(27, 430, 18), // "CPUSerial_9Changed"
QT_MOC_LITERAL(28, 449, 19), // "CPUSerial_10Changed"
QT_MOC_LITERAL(29, 469, 19), // "CPUSerial_11Changed"
QT_MOC_LITERAL(30, 489, 16), // "BoardTypeChanged"
QT_MOC_LITERAL(31, 506, 13), // "RxGoodChanged"
QT_MOC_LITERAL(32, 520, 18), // "RxCorrectedChanged"
QT_MOC_LITERAL(33, 539, 15), // "RxErrorsChanged"
QT_MOC_LITERAL(34, 555, 15), // "RxMissedChanged"
QT_MOC_LITERAL(35, 571, 16), // "RxFailureChanged"
QT_MOC_LITERAL(36, 588, 16), // "TxDroppedChanged"
QT_MOC_LITERAL(37, 605, 16), // "TxFailureChanged"
QT_MOC_LITERAL(38, 622, 13), // "ResetsChanged"
QT_MOC_LITERAL(39, 636, 15), // "TimeoutsChanged"
QT_MOC_LITERAL(40, 652, 11), // "RSSIChanged"
QT_MOC_LITERAL(41, 664, 18), // "LinkQualityChanged"
QT_MOC_LITERAL(42, 683, 16), // "LinkStateChanged"
QT_MOC_LITERAL(43, 700, 26), // "PairSignalStrengthsChanged"
QT_MOC_LITERAL(44, 727, 28), // "PairSignalStrengths_0Changed"
QT_MOC_LITERAL(45, 756, 28), // "PairSignalStrengths_1Changed"
QT_MOC_LITERAL(46, 785, 28), // "PairSignalStrengths_2Changed"
QT_MOC_LITERAL(47, 814, 28), // "PairSignalStrengths_3Changed"
QT_MOC_LITERAL(48, 843, 11), // "setDeviceID"
QT_MOC_LITERAL(49, 855, 10), // "setPairIDs"
QT_MOC_LITERAL(50, 866, 12), // "setPairIDs_0"
QT_MOC_LITERAL(51, 879, 12), // "setPairIDs_1"
QT_MOC_LITERAL(52, 892, 12), // "setPairIDs_2"
QT_MOC_LITERAL(53, 905, 12), // "setPairIDs_3"
QT_MOC_LITERAL(54, 918, 16), // "setBoardRevision"
QT_MOC_LITERAL(55, 935, 16), // "setHeapRemaining"
QT_MOC_LITERAL(56, 952, 16), // "setUAVTalkErrors"
QT_MOC_LITERAL(57, 969, 9), // "setTXRate"
QT_MOC_LITERAL(58, 979, 9), // "setRXRate"
QT_MOC_LITERAL(59, 989, 8), // "setTXSeq"
QT_MOC_LITERAL(60, 998, 8), // "setRXSeq"
QT_MOC_LITERAL(61, 1007, 12), // "setCPUSerial"
QT_MOC_LITERAL(62, 1020, 14), // "setCPUSerial_0"
QT_MOC_LITERAL(63, 1035, 14), // "setCPUSerial_1"
QT_MOC_LITERAL(64, 1050, 14), // "setCPUSerial_2"
QT_MOC_LITERAL(65, 1065, 14), // "setCPUSerial_3"
QT_MOC_LITERAL(66, 1080, 14), // "setCPUSerial_4"
QT_MOC_LITERAL(67, 1095, 14), // "setCPUSerial_5"
QT_MOC_LITERAL(68, 1110, 14), // "setCPUSerial_6"
QT_MOC_LITERAL(69, 1125, 14), // "setCPUSerial_7"
QT_MOC_LITERAL(70, 1140, 14), // "setCPUSerial_8"
QT_MOC_LITERAL(71, 1155, 14), // "setCPUSerial_9"
QT_MOC_LITERAL(72, 1170, 15), // "setCPUSerial_10"
QT_MOC_LITERAL(73, 1186, 15), // "setCPUSerial_11"
QT_MOC_LITERAL(74, 1202, 12), // "setBoardType"
QT_MOC_LITERAL(75, 1215, 9), // "setRxGood"
QT_MOC_LITERAL(76, 1225, 14), // "setRxCorrected"
QT_MOC_LITERAL(77, 1240, 11), // "setRxErrors"
QT_MOC_LITERAL(78, 1252, 11), // "setRxMissed"
QT_MOC_LITERAL(79, 1264, 12), // "setRxFailure"
QT_MOC_LITERAL(80, 1277, 12), // "setTxDropped"
QT_MOC_LITERAL(81, 1290, 12), // "setTxFailure"
QT_MOC_LITERAL(82, 1303, 9), // "setResets"
QT_MOC_LITERAL(83, 1313, 11), // "setTimeouts"
QT_MOC_LITERAL(84, 1325, 7), // "setRSSI"
QT_MOC_LITERAL(85, 1333, 14), // "setLinkQuality"
QT_MOC_LITERAL(86, 1348, 12), // "setLinkState"
QT_MOC_LITERAL(87, 1361, 22), // "setPairSignalStrengths"
QT_MOC_LITERAL(88, 1384, 24), // "setPairSignalStrengths_0"
QT_MOC_LITERAL(89, 1409, 24), // "setPairSignalStrengths_1"
QT_MOC_LITERAL(90, 1434, 24), // "setPairSignalStrengths_2"
QT_MOC_LITERAL(91, 1459, 24), // "setPairSignalStrengths_3"
QT_MOC_LITERAL(92, 1484, 17), // "emitNotifications"
QT_MOC_LITERAL(93, 1502, 11), // "getDeviceID"
QT_MOC_LITERAL(94, 1514, 10), // "getPairIDs"
QT_MOC_LITERAL(95, 1525, 12), // "getPairIDs_0"
QT_MOC_LITERAL(96, 1538, 12), // "getPairIDs_1"
QT_MOC_LITERAL(97, 1551, 12), // "getPairIDs_2"
QT_MOC_LITERAL(98, 1564, 12), // "getPairIDs_3"
QT_MOC_LITERAL(99, 1577, 16), // "getBoardRevision"
QT_MOC_LITERAL(100, 1594, 16), // "getHeapRemaining"
QT_MOC_LITERAL(101, 1611, 16), // "getUAVTalkErrors"
QT_MOC_LITERAL(102, 1628, 9), // "getTXRate"
QT_MOC_LITERAL(103, 1638, 9), // "getRXRate"
QT_MOC_LITERAL(104, 1648, 8), // "getTXSeq"
QT_MOC_LITERAL(105, 1657, 8), // "getRXSeq"
QT_MOC_LITERAL(106, 1666, 12), // "getCPUSerial"
QT_MOC_LITERAL(107, 1679, 14), // "getCPUSerial_0"
QT_MOC_LITERAL(108, 1694, 14), // "getCPUSerial_1"
QT_MOC_LITERAL(109, 1709, 14), // "getCPUSerial_2"
QT_MOC_LITERAL(110, 1724, 14), // "getCPUSerial_3"
QT_MOC_LITERAL(111, 1739, 14), // "getCPUSerial_4"
QT_MOC_LITERAL(112, 1754, 14), // "getCPUSerial_5"
QT_MOC_LITERAL(113, 1769, 14), // "getCPUSerial_6"
QT_MOC_LITERAL(114, 1784, 14), // "getCPUSerial_7"
QT_MOC_LITERAL(115, 1799, 14), // "getCPUSerial_8"
QT_MOC_LITERAL(116, 1814, 14), // "getCPUSerial_9"
QT_MOC_LITERAL(117, 1829, 15), // "getCPUSerial_10"
QT_MOC_LITERAL(118, 1845, 15), // "getCPUSerial_11"
QT_MOC_LITERAL(119, 1861, 12), // "getBoardType"
QT_MOC_LITERAL(120, 1874, 9), // "getRxGood"
QT_MOC_LITERAL(121, 1884, 14), // "getRxCorrected"
QT_MOC_LITERAL(122, 1899, 11), // "getRxErrors"
QT_MOC_LITERAL(123, 1911, 11), // "getRxMissed"
QT_MOC_LITERAL(124, 1923, 12), // "getRxFailure"
QT_MOC_LITERAL(125, 1936, 12), // "getTxDropped"
QT_MOC_LITERAL(126, 1949, 12), // "getTxFailure"
QT_MOC_LITERAL(127, 1962, 9), // "getResets"
QT_MOC_LITERAL(128, 1972, 11), // "getTimeouts"
QT_MOC_LITERAL(129, 1984, 7), // "getRSSI"
QT_MOC_LITERAL(130, 1992, 14), // "getLinkQuality"
QT_MOC_LITERAL(131, 2007, 12), // "getLinkState"
QT_MOC_LITERAL(132, 2020, 22), // "getPairSignalStrengths"
QT_MOC_LITERAL(133, 2043, 24), // "getPairSignalStrengths_0"
QT_MOC_LITERAL(134, 2068, 24), // "getPairSignalStrengths_1"
QT_MOC_LITERAL(135, 2093, 24), // "getPairSignalStrengths_2"
QT_MOC_LITERAL(136, 2118, 24), // "getPairSignalStrengths_3"
QT_MOC_LITERAL(137, 2143, 8), // "DeviceID"
QT_MOC_LITERAL(138, 2152, 9), // "PairIDs_0"
QT_MOC_LITERAL(139, 2162, 9), // "PairIDs_1"
QT_MOC_LITERAL(140, 2172, 9), // "PairIDs_2"
QT_MOC_LITERAL(141, 2182, 9), // "PairIDs_3"
QT_MOC_LITERAL(142, 2192, 13), // "BoardRevision"
QT_MOC_LITERAL(143, 2206, 13), // "HeapRemaining"
QT_MOC_LITERAL(144, 2220, 13), // "UAVTalkErrors"
QT_MOC_LITERAL(145, 2234, 6), // "TXRate"
QT_MOC_LITERAL(146, 2241, 6), // "RXRate"
QT_MOC_LITERAL(147, 2248, 5), // "TXSeq"
QT_MOC_LITERAL(148, 2254, 5), // "RXSeq"
QT_MOC_LITERAL(149, 2260, 11), // "CPUSerial_0"
QT_MOC_LITERAL(150, 2272, 11), // "CPUSerial_1"
QT_MOC_LITERAL(151, 2284, 11), // "CPUSerial_2"
QT_MOC_LITERAL(152, 2296, 11), // "CPUSerial_3"
QT_MOC_LITERAL(153, 2308, 11), // "CPUSerial_4"
QT_MOC_LITERAL(154, 2320, 11), // "CPUSerial_5"
QT_MOC_LITERAL(155, 2332, 11), // "CPUSerial_6"
QT_MOC_LITERAL(156, 2344, 11), // "CPUSerial_7"
QT_MOC_LITERAL(157, 2356, 11), // "CPUSerial_8"
QT_MOC_LITERAL(158, 2368, 11), // "CPUSerial_9"
QT_MOC_LITERAL(159, 2380, 12), // "CPUSerial_10"
QT_MOC_LITERAL(160, 2393, 12), // "CPUSerial_11"
QT_MOC_LITERAL(161, 2406, 9), // "BoardType"
QT_MOC_LITERAL(162, 2416, 6), // "RxGood"
QT_MOC_LITERAL(163, 2423, 11), // "RxCorrected"
QT_MOC_LITERAL(164, 2435, 8), // "RxErrors"
QT_MOC_LITERAL(165, 2444, 8), // "RxMissed"
QT_MOC_LITERAL(166, 2453, 9), // "RxFailure"
QT_MOC_LITERAL(167, 2463, 9), // "TxDropped"
QT_MOC_LITERAL(168, 2473, 9), // "TxFailure"
QT_MOC_LITERAL(169, 2483, 6), // "Resets"
QT_MOC_LITERAL(170, 2490, 8), // "Timeouts"
QT_MOC_LITERAL(171, 2499, 4), // "RSSI"
QT_MOC_LITERAL(172, 2504, 11), // "LinkQuality"
QT_MOC_LITERAL(173, 2516, 9), // "LinkState"
QT_MOC_LITERAL(174, 2526, 21), // "PairSignalStrengths_0"
QT_MOC_LITERAL(175, 2548, 21), // "PairSignalStrengths_1"
QT_MOC_LITERAL(176, 2570, 21), // "PairSignalStrengths_2"
QT_MOC_LITERAL(177, 2592, 21) // "PairSignalStrengths_3"

    },
    "OPLinkStatus\0DeviceIDChanged\0\0value\0"
    "PairIDsChanged\0index\0PairIDs_0Changed\0"
    "PairIDs_1Changed\0PairIDs_2Changed\0"
    "PairIDs_3Changed\0BoardRevisionChanged\0"
    "HeapRemainingChanged\0UAVTalkErrorsChanged\0"
    "TXRateChanged\0RXRateChanged\0TXSeqChanged\0"
    "RXSeqChanged\0CPUSerialChanged\0"
    "CPUSerial_0Changed\0CPUSerial_1Changed\0"
    "CPUSerial_2Changed\0CPUSerial_3Changed\0"
    "CPUSerial_4Changed\0CPUSerial_5Changed\0"
    "CPUSerial_6Changed\0CPUSerial_7Changed\0"
    "CPUSerial_8Changed\0CPUSerial_9Changed\0"
    "CPUSerial_10Changed\0CPUSerial_11Changed\0"
    "BoardTypeChanged\0RxGoodChanged\0"
    "RxCorrectedChanged\0RxErrorsChanged\0"
    "RxMissedChanged\0RxFailureChanged\0"
    "TxDroppedChanged\0TxFailureChanged\0"
    "ResetsChanged\0TimeoutsChanged\0RSSIChanged\0"
    "LinkQualityChanged\0LinkStateChanged\0"
    "PairSignalStrengthsChanged\0"
    "PairSignalStrengths_0Changed\0"
    "PairSignalStrengths_1Changed\0"
    "PairSignalStrengths_2Changed\0"
    "PairSignalStrengths_3Changed\0setDeviceID\0"
    "setPairIDs\0setPairIDs_0\0setPairIDs_1\0"
    "setPairIDs_2\0setPairIDs_3\0setBoardRevision\0"
    "setHeapRemaining\0setUAVTalkErrors\0"
    "setTXRate\0setRXRate\0setTXSeq\0setRXSeq\0"
    "setCPUSerial\0setCPUSerial_0\0setCPUSerial_1\0"
    "setCPUSerial_2\0setCPUSerial_3\0"
    "setCPUSerial_4\0setCPUSerial_5\0"
    "setCPUSerial_6\0setCPUSerial_7\0"
    "setCPUSerial_8\0setCPUSerial_9\0"
    "setCPUSerial_10\0setCPUSerial_11\0"
    "setBoardType\0setRxGood\0setRxCorrected\0"
    "setRxErrors\0setRxMissed\0setRxFailure\0"
    "setTxDropped\0setTxFailure\0setResets\0"
    "setTimeouts\0setRSSI\0setLinkQuality\0"
    "setLinkState\0setPairSignalStrengths\0"
    "setPairSignalStrengths_0\0"
    "setPairSignalStrengths_1\0"
    "setPairSignalStrengths_2\0"
    "setPairSignalStrengths_3\0emitNotifications\0"
    "getDeviceID\0getPairIDs\0getPairIDs_0\0"
    "getPairIDs_1\0getPairIDs_2\0getPairIDs_3\0"
    "getBoardRevision\0getHeapRemaining\0"
    "getUAVTalkErrors\0getTXRate\0getRXRate\0"
    "getTXSeq\0getRXSeq\0getCPUSerial\0"
    "getCPUSerial_0\0getCPUSerial_1\0"
    "getCPUSerial_2\0getCPUSerial_3\0"
    "getCPUSerial_4\0getCPUSerial_5\0"
    "getCPUSerial_6\0getCPUSerial_7\0"
    "getCPUSerial_8\0getCPUSerial_9\0"
    "getCPUSerial_10\0getCPUSerial_11\0"
    "getBoardType\0getRxGood\0getRxCorrected\0"
    "getRxErrors\0getRxMissed\0getRxFailure\0"
    "getTxDropped\0getTxFailure\0getResets\0"
    "getTimeouts\0getRSSI\0getLinkQuality\0"
    "getLinkState\0getPairSignalStrengths\0"
    "getPairSignalStrengths_0\0"
    "getPairSignalStrengths_1\0"
    "getPairSignalStrengths_2\0"
    "getPairSignalStrengths_3\0DeviceID\0"
    "PairIDs_0\0PairIDs_1\0PairIDs_2\0PairIDs_3\0"
    "BoardRevision\0HeapRemaining\0UAVTalkErrors\0"
    "TXRate\0RXRate\0TXSeq\0RXSeq\0CPUSerial_0\0"
    "CPUSerial_1\0CPUSerial_2\0CPUSerial_3\0"
    "CPUSerial_4\0CPUSerial_5\0CPUSerial_6\0"
    "CPUSerial_7\0CPUSerial_8\0CPUSerial_9\0"
    "CPUSerial_10\0CPUSerial_11\0BoardType\0"
    "RxGood\0RxCorrected\0RxErrors\0RxMissed\0"
    "RxFailure\0TxDropped\0TxFailure\0Resets\0"
    "Timeouts\0RSSI\0LinkQuality\0LinkState\0"
    "PairSignalStrengths_0\0PairSignalStrengths_1\0"
    "PairSignalStrengths_2\0PairSignalStrengths_3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OPLinkStatus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     133,   14, // methods
      41, 1006, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      44,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  679,    2, 0x06 /* Public */,
       4,    2,  682,    2, 0x06 /* Public */,
       6,    1,  687,    2, 0x06 /* Public */,
       7,    1,  690,    2, 0x06 /* Public */,
       8,    1,  693,    2, 0x06 /* Public */,
       9,    1,  696,    2, 0x06 /* Public */,
      10,    1,  699,    2, 0x06 /* Public */,
      11,    1,  702,    2, 0x06 /* Public */,
      12,    1,  705,    2, 0x06 /* Public */,
      13,    1,  708,    2, 0x06 /* Public */,
      14,    1,  711,    2, 0x06 /* Public */,
      15,    1,  714,    2, 0x06 /* Public */,
      16,    1,  717,    2, 0x06 /* Public */,
      17,    2,  720,    2, 0x06 /* Public */,
      18,    1,  725,    2, 0x06 /* Public */,
      19,    1,  728,    2, 0x06 /* Public */,
      20,    1,  731,    2, 0x06 /* Public */,
      21,    1,  734,    2, 0x06 /* Public */,
      22,    1,  737,    2, 0x06 /* Public */,
      23,    1,  740,    2, 0x06 /* Public */,
      24,    1,  743,    2, 0x06 /* Public */,
      25,    1,  746,    2, 0x06 /* Public */,
      26,    1,  749,    2, 0x06 /* Public */,
      27,    1,  752,    2, 0x06 /* Public */,
      28,    1,  755,    2, 0x06 /* Public */,
      29,    1,  758,    2, 0x06 /* Public */,
      30,    1,  761,    2, 0x06 /* Public */,
      31,    1,  764,    2, 0x06 /* Public */,
      32,    1,  767,    2, 0x06 /* Public */,
      33,    1,  770,    2, 0x06 /* Public */,
      34,    1,  773,    2, 0x06 /* Public */,
      35,    1,  776,    2, 0x06 /* Public */,
      36,    1,  779,    2, 0x06 /* Public */,
      37,    1,  782,    2, 0x06 /* Public */,
      38,    1,  785,    2, 0x06 /* Public */,
      39,    1,  788,    2, 0x06 /* Public */,
      40,    1,  791,    2, 0x06 /* Public */,
      41,    1,  794,    2, 0x06 /* Public */,
      42,    1,  797,    2, 0x06 /* Public */,
      43,    2,  800,    2, 0x06 /* Public */,
      44,    1,  805,    2, 0x06 /* Public */,
      45,    1,  808,    2, 0x06 /* Public */,
      46,    1,  811,    2, 0x06 /* Public */,
      47,    1,  814,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      48,    1,  817,    2, 0x0a /* Public */,
      49,    2,  820,    2, 0x0a /* Public */,
      50,    1,  825,    2, 0x0a /* Public */,
      51,    1,  828,    2, 0x0a /* Public */,
      52,    1,  831,    2, 0x0a /* Public */,
      53,    1,  834,    2, 0x0a /* Public */,
      54,    1,  837,    2, 0x0a /* Public */,
      55,    1,  840,    2, 0x0a /* Public */,
      56,    1,  843,    2, 0x0a /* Public */,
      57,    1,  846,    2, 0x0a /* Public */,
      58,    1,  849,    2, 0x0a /* Public */,
      59,    1,  852,    2, 0x0a /* Public */,
      60,    1,  855,    2, 0x0a /* Public */,
      61,    2,  858,    2, 0x0a /* Public */,
      62,    1,  863,    2, 0x0a /* Public */,
      63,    1,  866,    2, 0x0a /* Public */,
      64,    1,  869,    2, 0x0a /* Public */,
      65,    1,  872,    2, 0x0a /* Public */,
      66,    1,  875,    2, 0x0a /* Public */,
      67,    1,  878,    2, 0x0a /* Public */,
      68,    1,  881,    2, 0x0a /* Public */,
      69,    1,  884,    2, 0x0a /* Public */,
      70,    1,  887,    2, 0x0a /* Public */,
      71,    1,  890,    2, 0x0a /* Public */,
      72,    1,  893,    2, 0x0a /* Public */,
      73,    1,  896,    2, 0x0a /* Public */,
      74,    1,  899,    2, 0x0a /* Public */,
      75,    1,  902,    2, 0x0a /* Public */,
      76,    1,  905,    2, 0x0a /* Public */,
      77,    1,  908,    2, 0x0a /* Public */,
      78,    1,  911,    2, 0x0a /* Public */,
      79,    1,  914,    2, 0x0a /* Public */,
      80,    1,  917,    2, 0x0a /* Public */,
      81,    1,  920,    2, 0x0a /* Public */,
      82,    1,  923,    2, 0x0a /* Public */,
      83,    1,  926,    2, 0x0a /* Public */,
      84,    1,  929,    2, 0x0a /* Public */,
      85,    1,  932,    2, 0x0a /* Public */,
      86,    1,  935,    2, 0x0a /* Public */,
      87,    2,  938,    2, 0x0a /* Public */,
      88,    1,  943,    2, 0x0a /* Public */,
      89,    1,  946,    2, 0x0a /* Public */,
      90,    1,  949,    2, 0x0a /* Public */,
      91,    1,  952,    2, 0x0a /* Public */,
      92,    0,  955,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      93,    0,  956,    2, 0x02 /* Public */,
      94,    1,  957,    2, 0x02 /* Public */,
      95,    0,  960,    2, 0x02 /* Public */,
      96,    0,  961,    2, 0x02 /* Public */,
      97,    0,  962,    2, 0x02 /* Public */,
      98,    0,  963,    2, 0x02 /* Public */,
      99,    0,  964,    2, 0x02 /* Public */,
     100,    0,  965,    2, 0x02 /* Public */,
     101,    0,  966,    2, 0x02 /* Public */,
     102,    0,  967,    2, 0x02 /* Public */,
     103,    0,  968,    2, 0x02 /* Public */,
     104,    0,  969,    2, 0x02 /* Public */,
     105,    0,  970,    2, 0x02 /* Public */,
     106,    1,  971,    2, 0x02 /* Public */,
     107,    0,  974,    2, 0x02 /* Public */,
     108,    0,  975,    2, 0x02 /* Public */,
     109,    0,  976,    2, 0x02 /* Public */,
     110,    0,  977,    2, 0x02 /* Public */,
     111,    0,  978,    2, 0x02 /* Public */,
     112,    0,  979,    2, 0x02 /* Public */,
     113,    0,  980,    2, 0x02 /* Public */,
     114,    0,  981,    2, 0x02 /* Public */,
     115,    0,  982,    2, 0x02 /* Public */,
     116,    0,  983,    2, 0x02 /* Public */,
     117,    0,  984,    2, 0x02 /* Public */,
     118,    0,  985,    2, 0x02 /* Public */,
     119,    0,  986,    2, 0x02 /* Public */,
     120,    0,  987,    2, 0x02 /* Public */,
     121,    0,  988,    2, 0x02 /* Public */,
     122,    0,  989,    2, 0x02 /* Public */,
     123,    0,  990,    2, 0x02 /* Public */,
     124,    0,  991,    2, 0x02 /* Public */,
     125,    0,  992,    2, 0x02 /* Public */,
     126,    0,  993,    2, 0x02 /* Public */,
     127,    0,  994,    2, 0x02 /* Public */,
     128,    0,  995,    2, 0x02 /* Public */,
     129,    0,  996,    2, 0x02 /* Public */,
     130,    0,  997,    2, 0x02 /* Public */,
     131,    0,  998,    2, 0x02 /* Public */,
     132,    1,  999,    2, 0x02 /* Public */,
     133,    0, 1002,    2, 0x02 /* Public */,
     134,    0, 1003,    2, 0x02 /* Public */,
     135,    0, 1004,    2, 0x02 /* Public */,
     136,    0, 1005,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,    5,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    5,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    5,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,    5,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    5,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    5,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::UInt,
    QMetaType::UInt, QMetaType::UInt,    5,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UChar, QMetaType::UInt,    5,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    5,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,

 // properties: name, type, flags
     137, QMetaType::UInt, 0x00495103,
     138, QMetaType::UInt, 0x00495103,
     139, QMetaType::UInt, 0x00495103,
     140, QMetaType::UInt, 0x00495103,
     141, QMetaType::UInt, 0x00495103,
     142, QMetaType::UShort, 0x00495103,
     143, QMetaType::UShort, 0x00495103,
     144, QMetaType::UShort, 0x00495103,
     145, QMetaType::UShort, 0x00495103,
     146, QMetaType::UShort, 0x00495103,
     147, QMetaType::UShort, 0x00495103,
     148, QMetaType::UShort, 0x00495103,
     149, QMetaType::UChar, 0x00495103,
     150, QMetaType::UChar, 0x00495103,
     151, QMetaType::UChar, 0x00495103,
     152, QMetaType::UChar, 0x00495103,
     153, QMetaType::UChar, 0x00495103,
     154, QMetaType::UChar, 0x00495103,
     155, QMetaType::UChar, 0x00495103,
     156, QMetaType::UChar, 0x00495103,
     157, QMetaType::UChar, 0x00495103,
     158, QMetaType::UChar, 0x00495103,
     159, QMetaType::UChar, 0x00495103,
     160, QMetaType::UChar, 0x00495103,
     161, QMetaType::UChar, 0x00495103,
     162, QMetaType::UChar, 0x00495103,
     163, QMetaType::UChar, 0x00495103,
     164, QMetaType::UChar, 0x00495103,
     165, QMetaType::UChar, 0x00495103,
     166, QMetaType::UChar, 0x00495103,
     167, QMetaType::UChar, 0x00495103,
     168, QMetaType::UChar, 0x00495103,
     169, QMetaType::UChar, 0x00495103,
     170, QMetaType::UChar, 0x00495103,
     171, QMetaType::SChar, 0x00495103,
     172, QMetaType::UChar, 0x00495103,
     173, QMetaType::UChar, 0x00495103,
     174, QMetaType::SChar, 0x00495103,
     175, QMetaType::SChar, 0x00495103,
     176, QMetaType::SChar, 0x00495103,
     177, QMetaType::SChar, 0x00495103,

 // properties: notify_signal_id
       0,
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
      14,
      15,
      16,
      17,
      18,
      19,
      20,
      21,
      22,
      23,
      24,
      25,
      26,
      27,
      28,
      29,
      30,
      31,
      32,
      33,
      34,
      35,
      36,
      37,
      38,
      40,
      41,
      42,
      43,

       0        // eod
};

void OPLinkStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OPLinkStatus *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->DeviceIDChanged((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 1: _t->PairIDsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        case 2: _t->PairIDs_0Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 3: _t->PairIDs_1Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 4: _t->PairIDs_2Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 5: _t->PairIDs_3Changed((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 6: _t->BoardRevisionChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 7: _t->HeapRemainingChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 8: _t->UAVTalkErrorsChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 9: _t->TXRateChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 10: _t->RXRateChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 11: _t->TXSeqChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 12: _t->RXSeqChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 13: _t->CPUSerialChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 14: _t->CPUSerial_0Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 15: _t->CPUSerial_1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 16: _t->CPUSerial_2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->CPUSerial_3Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 18: _t->CPUSerial_4Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 19: _t->CPUSerial_5Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->CPUSerial_6Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 21: _t->CPUSerial_7Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 22: _t->CPUSerial_8Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 23: _t->CPUSerial_9Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 24: _t->CPUSerial_10Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 25: _t->CPUSerial_11Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 26: _t->BoardTypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 27: _t->RxGoodChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 28: _t->RxCorrectedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 29: _t->RxErrorsChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 30: _t->RxMissedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 31: _t->RxFailureChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 32: _t->TxDroppedChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 33: _t->TxFailureChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 34: _t->ResetsChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 35: _t->TimeoutsChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 36: _t->RSSIChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 37: _t->LinkQualityChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 38: _t->LinkStateChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 39: _t->PairSignalStrengthsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 40: _t->PairSignalStrengths_0Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 41: _t->PairSignalStrengths_1Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 42: _t->PairSignalStrengths_2Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 43: _t->PairSignalStrengths_3Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 44: _t->setDeviceID((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 45: _t->setPairIDs((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        case 46: _t->setPairIDs_0((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 47: _t->setPairIDs_1((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 48: _t->setPairIDs_2((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 49: _t->setPairIDs_3((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 50: _t->setBoardRevision((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 51: _t->setHeapRemaining((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 52: _t->setUAVTalkErrors((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 53: _t->setTXRate((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 54: _t->setRXRate((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 55: _t->setTXSeq((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 56: _t->setRXSeq((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 57: _t->setCPUSerial((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 58: _t->setCPUSerial_0((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 59: _t->setCPUSerial_1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 60: _t->setCPUSerial_2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 61: _t->setCPUSerial_3((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 62: _t->setCPUSerial_4((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 63: _t->setCPUSerial_5((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 64: _t->setCPUSerial_6((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 65: _t->setCPUSerial_7((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 66: _t->setCPUSerial_8((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 67: _t->setCPUSerial_9((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 68: _t->setCPUSerial_10((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 69: _t->setCPUSerial_11((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 70: _t->setBoardType((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 71: _t->setRxGood((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 72: _t->setRxCorrected((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 73: _t->setRxErrors((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 74: _t->setRxMissed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 75: _t->setRxFailure((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 76: _t->setTxDropped((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 77: _t->setTxFailure((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 78: _t->setResets((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 79: _t->setTimeouts((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 80: _t->setRSSI((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 81: _t->setLinkQuality((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 82: _t->setLinkState((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 83: _t->setPairSignalStrengths((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 84: _t->setPairSignalStrengths_0((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 85: _t->setPairSignalStrengths_1((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 86: _t->setPairSignalStrengths_2((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 87: _t->setPairSignalStrengths_3((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 88: _t->emitNotifications(); break;
        case 89: { quint32 _r = _t->getDeviceID();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 90: { quint32 _r = _t->getPairIDs((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 91: { quint32 _r = _t->getPairIDs_0();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 92: { quint32 _r = _t->getPairIDs_1();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 93: { quint32 _r = _t->getPairIDs_2();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 94: { quint32 _r = _t->getPairIDs_3();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        case 95: { quint16 _r = _t->getBoardRevision();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 96: { quint16 _r = _t->getHeapRemaining();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 97: { quint16 _r = _t->getUAVTalkErrors();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 98: { quint16 _r = _t->getTXRate();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 99: { quint16 _r = _t->getRXRate();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 100: { quint16 _r = _t->getTXSeq();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 101: { quint16 _r = _t->getRXSeq();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 102: { quint8 _r = _t->getCPUSerial((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 103: { quint8 _r = _t->getCPUSerial_0();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 104: { quint8 _r = _t->getCPUSerial_1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 105: { quint8 _r = _t->getCPUSerial_2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 106: { quint8 _r = _t->getCPUSerial_3();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 107: { quint8 _r = _t->getCPUSerial_4();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 108: { quint8 _r = _t->getCPUSerial_5();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 109: { quint8 _r = _t->getCPUSerial_6();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 110: { quint8 _r = _t->getCPUSerial_7();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 111: { quint8 _r = _t->getCPUSerial_8();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 112: { quint8 _r = _t->getCPUSerial_9();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 113: { quint8 _r = _t->getCPUSerial_10();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 114: { quint8 _r = _t->getCPUSerial_11();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 115: { quint8 _r = _t->getBoardType();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 116: { quint8 _r = _t->getRxGood();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 117: { quint8 _r = _t->getRxCorrected();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 118: { quint8 _r = _t->getRxErrors();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 119: { quint8 _r = _t->getRxMissed();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 120: { quint8 _r = _t->getRxFailure();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 121: { quint8 _r = _t->getTxDropped();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 122: { quint8 _r = _t->getTxFailure();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 123: { quint8 _r = _t->getResets();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 124: { quint8 _r = _t->getTimeouts();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 125: { qint8 _r = _t->getRSSI();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 126: { quint8 _r = _t->getLinkQuality();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 127: { quint8 _r = _t->getLinkState();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 128: { qint8 _r = _t->getPairSignalStrengths((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 129: { qint8 _r = _t->getPairSignalStrengths_0();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 130: { qint8 _r = _t->getPairSignalStrengths_1();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 131: { qint8 _r = _t->getPairSignalStrengths_2();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 132: { qint8 _r = _t->getPairSignalStrengths_3();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OPLinkStatus::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::DeviceIDChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint32 , quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::PairIDsChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::PairIDs_0Changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::PairIDs_1Changed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::PairIDs_2Changed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::PairIDs_3Changed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::BoardRevisionChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::HeapRemainingChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::UAVTalkErrorsChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::TXRateChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::RXRateChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::TXSeqChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::RXSeqChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::CPUSerialChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::CPUSerial_0Changed)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::CPUSerial_1Changed)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::CPUSerial_2Changed)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::CPUSerial_3Changed)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::CPUSerial_4Changed)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::CPUSerial_5Changed)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::CPUSerial_6Changed)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::CPUSerial_7Changed)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::CPUSerial_8Changed)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::CPUSerial_9Changed)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::CPUSerial_10Changed)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::CPUSerial_11Changed)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::BoardTypeChanged)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::RxGoodChanged)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::RxCorrectedChanged)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::RxErrorsChanged)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::RxMissedChanged)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::RxFailureChanged)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::TxDroppedChanged)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::TxFailureChanged)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::ResetsChanged)) {
                *result = 34;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::TimeoutsChanged)) {
                *result = 35;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::RSSIChanged)) {
                *result = 36;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::LinkQualityChanged)) {
                *result = 37;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::LinkStateChanged)) {
                *result = 38;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::PairSignalStrengthsChanged)) {
                *result = 39;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::PairSignalStrengths_0Changed)) {
                *result = 40;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::PairSignalStrengths_1Changed)) {
                *result = 41;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::PairSignalStrengths_2Changed)) {
                *result = 42;
                return;
            }
        }
        {
            using _t = void (OPLinkStatus::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OPLinkStatus::PairSignalStrengths_3Changed)) {
                *result = 43;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<OPLinkStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint32*>(_v) = _t->getDeviceID(); break;
        case 1: *reinterpret_cast< quint32*>(_v) = _t->getPairIDs_0(); break;
        case 2: *reinterpret_cast< quint32*>(_v) = _t->getPairIDs_1(); break;
        case 3: *reinterpret_cast< quint32*>(_v) = _t->getPairIDs_2(); break;
        case 4: *reinterpret_cast< quint32*>(_v) = _t->getPairIDs_3(); break;
        case 5: *reinterpret_cast< quint16*>(_v) = _t->getBoardRevision(); break;
        case 6: *reinterpret_cast< quint16*>(_v) = _t->getHeapRemaining(); break;
        case 7: *reinterpret_cast< quint16*>(_v) = _t->getUAVTalkErrors(); break;
        case 8: *reinterpret_cast< quint16*>(_v) = _t->getTXRate(); break;
        case 9: *reinterpret_cast< quint16*>(_v) = _t->getRXRate(); break;
        case 10: *reinterpret_cast< quint16*>(_v) = _t->getTXSeq(); break;
        case 11: *reinterpret_cast< quint16*>(_v) = _t->getRXSeq(); break;
        case 12: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_0(); break;
        case 13: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_1(); break;
        case 14: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_2(); break;
        case 15: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_3(); break;
        case 16: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_4(); break;
        case 17: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_5(); break;
        case 18: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_6(); break;
        case 19: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_7(); break;
        case 20: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_8(); break;
        case 21: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_9(); break;
        case 22: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_10(); break;
        case 23: *reinterpret_cast< quint8*>(_v) = _t->getCPUSerial_11(); break;
        case 24: *reinterpret_cast< quint8*>(_v) = _t->getBoardType(); break;
        case 25: *reinterpret_cast< quint8*>(_v) = _t->getRxGood(); break;
        case 26: *reinterpret_cast< quint8*>(_v) = _t->getRxCorrected(); break;
        case 27: *reinterpret_cast< quint8*>(_v) = _t->getRxErrors(); break;
        case 28: *reinterpret_cast< quint8*>(_v) = _t->getRxMissed(); break;
        case 29: *reinterpret_cast< quint8*>(_v) = _t->getRxFailure(); break;
        case 30: *reinterpret_cast< quint8*>(_v) = _t->getTxDropped(); break;
        case 31: *reinterpret_cast< quint8*>(_v) = _t->getTxFailure(); break;
        case 32: *reinterpret_cast< quint8*>(_v) = _t->getResets(); break;
        case 33: *reinterpret_cast< quint8*>(_v) = _t->getTimeouts(); break;
        case 34: *reinterpret_cast< qint8*>(_v) = _t->getRSSI(); break;
        case 35: *reinterpret_cast< quint8*>(_v) = _t->getLinkQuality(); break;
        case 36: *reinterpret_cast< quint8*>(_v) = _t->getLinkState(); break;
        case 37: *reinterpret_cast< qint8*>(_v) = _t->getPairSignalStrengths_0(); break;
        case 38: *reinterpret_cast< qint8*>(_v) = _t->getPairSignalStrengths_1(); break;
        case 39: *reinterpret_cast< qint8*>(_v) = _t->getPairSignalStrengths_2(); break;
        case 40: *reinterpret_cast< qint8*>(_v) = _t->getPairSignalStrengths_3(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<OPLinkStatus *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDeviceID(*reinterpret_cast< quint32*>(_v)); break;
        case 1: _t->setPairIDs_0(*reinterpret_cast< quint32*>(_v)); break;
        case 2: _t->setPairIDs_1(*reinterpret_cast< quint32*>(_v)); break;
        case 3: _t->setPairIDs_2(*reinterpret_cast< quint32*>(_v)); break;
        case 4: _t->setPairIDs_3(*reinterpret_cast< quint32*>(_v)); break;
        case 5: _t->setBoardRevision(*reinterpret_cast< quint16*>(_v)); break;
        case 6: _t->setHeapRemaining(*reinterpret_cast< quint16*>(_v)); break;
        case 7: _t->setUAVTalkErrors(*reinterpret_cast< quint16*>(_v)); break;
        case 8: _t->setTXRate(*reinterpret_cast< quint16*>(_v)); break;
        case 9: _t->setRXRate(*reinterpret_cast< quint16*>(_v)); break;
        case 10: _t->setTXSeq(*reinterpret_cast< quint16*>(_v)); break;
        case 11: _t->setRXSeq(*reinterpret_cast< quint16*>(_v)); break;
        case 12: _t->setCPUSerial_0(*reinterpret_cast< quint8*>(_v)); break;
        case 13: _t->setCPUSerial_1(*reinterpret_cast< quint8*>(_v)); break;
        case 14: _t->setCPUSerial_2(*reinterpret_cast< quint8*>(_v)); break;
        case 15: _t->setCPUSerial_3(*reinterpret_cast< quint8*>(_v)); break;
        case 16: _t->setCPUSerial_4(*reinterpret_cast< quint8*>(_v)); break;
        case 17: _t->setCPUSerial_5(*reinterpret_cast< quint8*>(_v)); break;
        case 18: _t->setCPUSerial_6(*reinterpret_cast< quint8*>(_v)); break;
        case 19: _t->setCPUSerial_7(*reinterpret_cast< quint8*>(_v)); break;
        case 20: _t->setCPUSerial_8(*reinterpret_cast< quint8*>(_v)); break;
        case 21: _t->setCPUSerial_9(*reinterpret_cast< quint8*>(_v)); break;
        case 22: _t->setCPUSerial_10(*reinterpret_cast< quint8*>(_v)); break;
        case 23: _t->setCPUSerial_11(*reinterpret_cast< quint8*>(_v)); break;
        case 24: _t->setBoardType(*reinterpret_cast< quint8*>(_v)); break;
        case 25: _t->setRxGood(*reinterpret_cast< quint8*>(_v)); break;
        case 26: _t->setRxCorrected(*reinterpret_cast< quint8*>(_v)); break;
        case 27: _t->setRxErrors(*reinterpret_cast< quint8*>(_v)); break;
        case 28: _t->setRxMissed(*reinterpret_cast< quint8*>(_v)); break;
        case 29: _t->setRxFailure(*reinterpret_cast< quint8*>(_v)); break;
        case 30: _t->setTxDropped(*reinterpret_cast< quint8*>(_v)); break;
        case 31: _t->setTxFailure(*reinterpret_cast< quint8*>(_v)); break;
        case 32: _t->setResets(*reinterpret_cast< quint8*>(_v)); break;
        case 33: _t->setTimeouts(*reinterpret_cast< quint8*>(_v)); break;
        case 34: _t->setRSSI(*reinterpret_cast< qint8*>(_v)); break;
        case 35: _t->setLinkQuality(*reinterpret_cast< quint8*>(_v)); break;
        case 36: _t->setLinkState(*reinterpret_cast< quint8*>(_v)); break;
        case 37: _t->setPairSignalStrengths_0(*reinterpret_cast< qint8*>(_v)); break;
        case 38: _t->setPairSignalStrengths_1(*reinterpret_cast< qint8*>(_v)); break;
        case 39: _t->setPairSignalStrengths_2(*reinterpret_cast< qint8*>(_v)); break;
        case 40: _t->setPairSignalStrengths_3(*reinterpret_cast< qint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject OPLinkStatus::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_OPLinkStatus.data,
    qt_meta_data_OPLinkStatus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OPLinkStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OPLinkStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OPLinkStatus.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int OPLinkStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 133)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 133;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 133)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 133;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 41;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 41;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 41;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 41;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 41;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void OPLinkStatus::DeviceIDChanged(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OPLinkStatus::PairIDsChanged(quint32 _t1, quint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OPLinkStatus::PairIDs_0Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void OPLinkStatus::PairIDs_1Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void OPLinkStatus::PairIDs_2Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void OPLinkStatus::PairIDs_3Changed(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void OPLinkStatus::BoardRevisionChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void OPLinkStatus::HeapRemainingChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void OPLinkStatus::UAVTalkErrorsChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void OPLinkStatus::TXRateChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void OPLinkStatus::RXRateChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void OPLinkStatus::TXSeqChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void OPLinkStatus::RXSeqChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void OPLinkStatus::CPUSerialChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void OPLinkStatus::CPUSerial_0Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void OPLinkStatus::CPUSerial_1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void OPLinkStatus::CPUSerial_2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void OPLinkStatus::CPUSerial_3Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void OPLinkStatus::CPUSerial_4Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void OPLinkStatus::CPUSerial_5Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void OPLinkStatus::CPUSerial_6Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void OPLinkStatus::CPUSerial_7Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void OPLinkStatus::CPUSerial_8Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void OPLinkStatus::CPUSerial_9Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void OPLinkStatus::CPUSerial_10Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void OPLinkStatus::CPUSerial_11Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void OPLinkStatus::BoardTypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void OPLinkStatus::RxGoodChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void OPLinkStatus::RxCorrectedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void OPLinkStatus::RxErrorsChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void OPLinkStatus::RxMissedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void OPLinkStatus::RxFailureChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void OPLinkStatus::TxDroppedChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void OPLinkStatus::TxFailureChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void OPLinkStatus::ResetsChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void OPLinkStatus::TimeoutsChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 35, _a);
}

// SIGNAL 36
void OPLinkStatus::RSSIChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 36, _a);
}

// SIGNAL 37
void OPLinkStatus::LinkQualityChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 37, _a);
}

// SIGNAL 38
void OPLinkStatus::LinkStateChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 38, _a);
}

// SIGNAL 39
void OPLinkStatus::PairSignalStrengthsChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 39, _a);
}

// SIGNAL 40
void OPLinkStatus::PairSignalStrengths_0Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 40, _a);
}

// SIGNAL 41
void OPLinkStatus::PairSignalStrengths_1Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 41, _a);
}

// SIGNAL 42
void OPLinkStatus::PairSignalStrengths_2Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 42, _a);
}

// SIGNAL 43
void OPLinkStatus::PairSignalStrengths_3Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 43, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
