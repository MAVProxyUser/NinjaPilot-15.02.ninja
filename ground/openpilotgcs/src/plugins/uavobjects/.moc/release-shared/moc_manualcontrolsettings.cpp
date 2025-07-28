/****************************************************************************
** Meta object code from reading C++ file 'manualcontrolsettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/manualcontrolsettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'manualcontrolsettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ManualControlSettings_t {
    QByteArrayData data[282];
    char stringdata0[6894];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ManualControlSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ManualControlSettings_t qt_meta_stringdata_ManualControlSettings = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ManualControlSettings"
QT_MOC_LITERAL(1, 22, 15), // "DeadbandChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5), // "value"
QT_MOC_LITERAL(4, 45, 30), // "DeadbandAssistedControlChanged"
QT_MOC_LITERAL(5, 76, 22), // "FailsafeChannelChanged"
QT_MOC_LITERAL(6, 99, 5), // "index"
QT_MOC_LITERAL(7, 105, 31), // "FailsafeChannel_ThrottleChanged"
QT_MOC_LITERAL(8, 137, 27), // "FailsafeChannel_RollChanged"
QT_MOC_LITERAL(9, 165, 28), // "FailsafeChannel_PitchChanged"
QT_MOC_LITERAL(10, 194, 26), // "FailsafeChannel_YawChanged"
QT_MOC_LITERAL(11, 221, 33), // "FailsafeChannel_CollectiveCha..."
QT_MOC_LITERAL(12, 255, 33), // "FailsafeChannel_Accessory0Cha..."
QT_MOC_LITERAL(13, 289, 33), // "FailsafeChannel_Accessory1Cha..."
QT_MOC_LITERAL(14, 323, 33), // "FailsafeChannel_Accessory2Cha..."
QT_MOC_LITERAL(15, 357, 17), // "ChannelMinChanged"
QT_MOC_LITERAL(16, 375, 26), // "ChannelMin_ThrottleChanged"
QT_MOC_LITERAL(17, 402, 22), // "ChannelMin_RollChanged"
QT_MOC_LITERAL(18, 425, 23), // "ChannelMin_PitchChanged"
QT_MOC_LITERAL(19, 449, 21), // "ChannelMin_YawChanged"
QT_MOC_LITERAL(20, 471, 28), // "ChannelMin_FlightModeChanged"
QT_MOC_LITERAL(21, 500, 28), // "ChannelMin_CollectiveChanged"
QT_MOC_LITERAL(22, 529, 28), // "ChannelMin_Accessory0Changed"
QT_MOC_LITERAL(23, 558, 28), // "ChannelMin_Accessory1Changed"
QT_MOC_LITERAL(24, 587, 28), // "ChannelMin_Accessory2Changed"
QT_MOC_LITERAL(25, 616, 21), // "ChannelNeutralChanged"
QT_MOC_LITERAL(26, 638, 30), // "ChannelNeutral_ThrottleChanged"
QT_MOC_LITERAL(27, 669, 26), // "ChannelNeutral_RollChanged"
QT_MOC_LITERAL(28, 696, 27), // "ChannelNeutral_PitchChanged"
QT_MOC_LITERAL(29, 724, 25), // "ChannelNeutral_YawChanged"
QT_MOC_LITERAL(30, 750, 32), // "ChannelNeutral_FlightModeChanged"
QT_MOC_LITERAL(31, 783, 32), // "ChannelNeutral_CollectiveChanged"
QT_MOC_LITERAL(32, 816, 32), // "ChannelNeutral_Accessory0Changed"
QT_MOC_LITERAL(33, 849, 32), // "ChannelNeutral_Accessory1Changed"
QT_MOC_LITERAL(34, 882, 32), // "ChannelNeutral_Accessory2Changed"
QT_MOC_LITERAL(35, 915, 17), // "ChannelMaxChanged"
QT_MOC_LITERAL(36, 933, 26), // "ChannelMax_ThrottleChanged"
QT_MOC_LITERAL(37, 960, 22), // "ChannelMax_RollChanged"
QT_MOC_LITERAL(38, 983, 23), // "ChannelMax_PitchChanged"
QT_MOC_LITERAL(39, 1007, 21), // "ChannelMax_YawChanged"
QT_MOC_LITERAL(40, 1029, 28), // "ChannelMax_FlightModeChanged"
QT_MOC_LITERAL(41, 1058, 28), // "ChannelMax_CollectiveChanged"
QT_MOC_LITERAL(42, 1087, 28), // "ChannelMax_Accessory0Changed"
QT_MOC_LITERAL(43, 1116, 28), // "ChannelMax_Accessory1Changed"
QT_MOC_LITERAL(44, 1145, 28), // "ChannelMax_Accessory2Changed"
QT_MOC_LITERAL(45, 1174, 19), // "ResponseTimeChanged"
QT_MOC_LITERAL(46, 1194, 24), // "ResponseTime_RollChanged"
QT_MOC_LITERAL(47, 1219, 25), // "ResponseTime_PitchChanged"
QT_MOC_LITERAL(48, 1245, 23), // "ResponseTime_YawChanged"
QT_MOC_LITERAL(49, 1269, 30), // "ResponseTime_CollectiveChanged"
QT_MOC_LITERAL(50, 1300, 30), // "ResponseTime_Accessory0Changed"
QT_MOC_LITERAL(51, 1331, 30), // "ResponseTime_Accessory1Changed"
QT_MOC_LITERAL(52, 1362, 30), // "ResponseTime_Accessory2Changed"
QT_MOC_LITERAL(53, 1393, 20), // "ChannelGroupsChanged"
QT_MOC_LITERAL(54, 1414, 29), // "ChannelGroups_ThrottleChanged"
QT_MOC_LITERAL(55, 1444, 25), // "ChannelGroups_RollChanged"
QT_MOC_LITERAL(56, 1470, 26), // "ChannelGroups_PitchChanged"
QT_MOC_LITERAL(57, 1497, 24), // "ChannelGroups_YawChanged"
QT_MOC_LITERAL(58, 1522, 31), // "ChannelGroups_FlightModeChanged"
QT_MOC_LITERAL(59, 1554, 31), // "ChannelGroups_CollectiveChanged"
QT_MOC_LITERAL(60, 1586, 31), // "ChannelGroups_Accessory0Changed"
QT_MOC_LITERAL(61, 1618, 31), // "ChannelGroups_Accessory1Changed"
QT_MOC_LITERAL(62, 1650, 31), // "ChannelGroups_Accessory2Changed"
QT_MOC_LITERAL(63, 1682, 20), // "ChannelNumberChanged"
QT_MOC_LITERAL(64, 1703, 29), // "ChannelNumber_ThrottleChanged"
QT_MOC_LITERAL(65, 1733, 25), // "ChannelNumber_RollChanged"
QT_MOC_LITERAL(66, 1759, 26), // "ChannelNumber_PitchChanged"
QT_MOC_LITERAL(67, 1786, 24), // "ChannelNumber_YawChanged"
QT_MOC_LITERAL(68, 1811, 31), // "ChannelNumber_FlightModeChanged"
QT_MOC_LITERAL(69, 1843, 31), // "ChannelNumber_CollectiveChanged"
QT_MOC_LITERAL(70, 1875, 31), // "ChannelNumber_Accessory0Changed"
QT_MOC_LITERAL(71, 1907, 31), // "ChannelNumber_Accessory1Changed"
QT_MOC_LITERAL(72, 1939, 31), // "ChannelNumber_Accessory2Changed"
QT_MOC_LITERAL(73, 1971, 23), // "FlightModeNumberChanged"
QT_MOC_LITERAL(74, 1995, 39), // "FailsafeFlightModeSwitchPosit..."
QT_MOC_LITERAL(75, 2035, 11), // "setDeadband"
QT_MOC_LITERAL(76, 2047, 26), // "setDeadbandAssistedControl"
QT_MOC_LITERAL(77, 2074, 18), // "setFailsafeChannel"
QT_MOC_LITERAL(78, 2093, 27), // "setFailsafeChannel_Throttle"
QT_MOC_LITERAL(79, 2121, 23), // "setFailsafeChannel_Roll"
QT_MOC_LITERAL(80, 2145, 24), // "setFailsafeChannel_Pitch"
QT_MOC_LITERAL(81, 2170, 22), // "setFailsafeChannel_Yaw"
QT_MOC_LITERAL(82, 2193, 29), // "setFailsafeChannel_Collective"
QT_MOC_LITERAL(83, 2223, 29), // "setFailsafeChannel_Accessory0"
QT_MOC_LITERAL(84, 2253, 29), // "setFailsafeChannel_Accessory1"
QT_MOC_LITERAL(85, 2283, 29), // "setFailsafeChannel_Accessory2"
QT_MOC_LITERAL(86, 2313, 13), // "setChannelMin"
QT_MOC_LITERAL(87, 2327, 22), // "setChannelMin_Throttle"
QT_MOC_LITERAL(88, 2350, 18), // "setChannelMin_Roll"
QT_MOC_LITERAL(89, 2369, 19), // "setChannelMin_Pitch"
QT_MOC_LITERAL(90, 2389, 17), // "setChannelMin_Yaw"
QT_MOC_LITERAL(91, 2407, 24), // "setChannelMin_FlightMode"
QT_MOC_LITERAL(92, 2432, 24), // "setChannelMin_Collective"
QT_MOC_LITERAL(93, 2457, 24), // "setChannelMin_Accessory0"
QT_MOC_LITERAL(94, 2482, 24), // "setChannelMin_Accessory1"
QT_MOC_LITERAL(95, 2507, 24), // "setChannelMin_Accessory2"
QT_MOC_LITERAL(96, 2532, 17), // "setChannelNeutral"
QT_MOC_LITERAL(97, 2550, 26), // "setChannelNeutral_Throttle"
QT_MOC_LITERAL(98, 2577, 22), // "setChannelNeutral_Roll"
QT_MOC_LITERAL(99, 2600, 23), // "setChannelNeutral_Pitch"
QT_MOC_LITERAL(100, 2624, 21), // "setChannelNeutral_Yaw"
QT_MOC_LITERAL(101, 2646, 28), // "setChannelNeutral_FlightMode"
QT_MOC_LITERAL(102, 2675, 28), // "setChannelNeutral_Collective"
QT_MOC_LITERAL(103, 2704, 28), // "setChannelNeutral_Accessory0"
QT_MOC_LITERAL(104, 2733, 28), // "setChannelNeutral_Accessory1"
QT_MOC_LITERAL(105, 2762, 28), // "setChannelNeutral_Accessory2"
QT_MOC_LITERAL(106, 2791, 13), // "setChannelMax"
QT_MOC_LITERAL(107, 2805, 22), // "setChannelMax_Throttle"
QT_MOC_LITERAL(108, 2828, 18), // "setChannelMax_Roll"
QT_MOC_LITERAL(109, 2847, 19), // "setChannelMax_Pitch"
QT_MOC_LITERAL(110, 2867, 17), // "setChannelMax_Yaw"
QT_MOC_LITERAL(111, 2885, 24), // "setChannelMax_FlightMode"
QT_MOC_LITERAL(112, 2910, 24), // "setChannelMax_Collective"
QT_MOC_LITERAL(113, 2935, 24), // "setChannelMax_Accessory0"
QT_MOC_LITERAL(114, 2960, 24), // "setChannelMax_Accessory1"
QT_MOC_LITERAL(115, 2985, 24), // "setChannelMax_Accessory2"
QT_MOC_LITERAL(116, 3010, 15), // "setResponseTime"
QT_MOC_LITERAL(117, 3026, 20), // "setResponseTime_Roll"
QT_MOC_LITERAL(118, 3047, 21), // "setResponseTime_Pitch"
QT_MOC_LITERAL(119, 3069, 19), // "setResponseTime_Yaw"
QT_MOC_LITERAL(120, 3089, 26), // "setResponseTime_Collective"
QT_MOC_LITERAL(121, 3116, 26), // "setResponseTime_Accessory0"
QT_MOC_LITERAL(122, 3143, 26), // "setResponseTime_Accessory1"
QT_MOC_LITERAL(123, 3170, 26), // "setResponseTime_Accessory2"
QT_MOC_LITERAL(124, 3197, 16), // "setChannelGroups"
QT_MOC_LITERAL(125, 3214, 25), // "setChannelGroups_Throttle"
QT_MOC_LITERAL(126, 3240, 21), // "setChannelGroups_Roll"
QT_MOC_LITERAL(127, 3262, 22), // "setChannelGroups_Pitch"
QT_MOC_LITERAL(128, 3285, 20), // "setChannelGroups_Yaw"
QT_MOC_LITERAL(129, 3306, 27), // "setChannelGroups_FlightMode"
QT_MOC_LITERAL(130, 3334, 27), // "setChannelGroups_Collective"
QT_MOC_LITERAL(131, 3362, 27), // "setChannelGroups_Accessory0"
QT_MOC_LITERAL(132, 3390, 27), // "setChannelGroups_Accessory1"
QT_MOC_LITERAL(133, 3418, 27), // "setChannelGroups_Accessory2"
QT_MOC_LITERAL(134, 3446, 16), // "setChannelNumber"
QT_MOC_LITERAL(135, 3463, 25), // "setChannelNumber_Throttle"
QT_MOC_LITERAL(136, 3489, 21), // "setChannelNumber_Roll"
QT_MOC_LITERAL(137, 3511, 22), // "setChannelNumber_Pitch"
QT_MOC_LITERAL(138, 3534, 20), // "setChannelNumber_Yaw"
QT_MOC_LITERAL(139, 3555, 27), // "setChannelNumber_FlightMode"
QT_MOC_LITERAL(140, 3583, 27), // "setChannelNumber_Collective"
QT_MOC_LITERAL(141, 3611, 27), // "setChannelNumber_Accessory0"
QT_MOC_LITERAL(142, 3639, 27), // "setChannelNumber_Accessory1"
QT_MOC_LITERAL(143, 3667, 27), // "setChannelNumber_Accessory2"
QT_MOC_LITERAL(144, 3695, 19), // "setFlightModeNumber"
QT_MOC_LITERAL(145, 3715, 35), // "setFailsafeFlightModeSwitchPo..."
QT_MOC_LITERAL(146, 3751, 17), // "emitNotifications"
QT_MOC_LITERAL(147, 3769, 11), // "getDeadband"
QT_MOC_LITERAL(148, 3781, 26), // "getDeadbandAssistedControl"
QT_MOC_LITERAL(149, 3808, 18), // "getFailsafeChannel"
QT_MOC_LITERAL(150, 3827, 27), // "getFailsafeChannel_Throttle"
QT_MOC_LITERAL(151, 3855, 23), // "getFailsafeChannel_Roll"
QT_MOC_LITERAL(152, 3879, 24), // "getFailsafeChannel_Pitch"
QT_MOC_LITERAL(153, 3904, 22), // "getFailsafeChannel_Yaw"
QT_MOC_LITERAL(154, 3927, 29), // "getFailsafeChannel_Collective"
QT_MOC_LITERAL(155, 3957, 29), // "getFailsafeChannel_Accessory0"
QT_MOC_LITERAL(156, 3987, 29), // "getFailsafeChannel_Accessory1"
QT_MOC_LITERAL(157, 4017, 29), // "getFailsafeChannel_Accessory2"
QT_MOC_LITERAL(158, 4047, 13), // "getChannelMin"
QT_MOC_LITERAL(159, 4061, 22), // "getChannelMin_Throttle"
QT_MOC_LITERAL(160, 4084, 18), // "getChannelMin_Roll"
QT_MOC_LITERAL(161, 4103, 19), // "getChannelMin_Pitch"
QT_MOC_LITERAL(162, 4123, 17), // "getChannelMin_Yaw"
QT_MOC_LITERAL(163, 4141, 24), // "getChannelMin_FlightMode"
QT_MOC_LITERAL(164, 4166, 24), // "getChannelMin_Collective"
QT_MOC_LITERAL(165, 4191, 24), // "getChannelMin_Accessory0"
QT_MOC_LITERAL(166, 4216, 24), // "getChannelMin_Accessory1"
QT_MOC_LITERAL(167, 4241, 24), // "getChannelMin_Accessory2"
QT_MOC_LITERAL(168, 4266, 17), // "getChannelNeutral"
QT_MOC_LITERAL(169, 4284, 26), // "getChannelNeutral_Throttle"
QT_MOC_LITERAL(170, 4311, 22), // "getChannelNeutral_Roll"
QT_MOC_LITERAL(171, 4334, 23), // "getChannelNeutral_Pitch"
QT_MOC_LITERAL(172, 4358, 21), // "getChannelNeutral_Yaw"
QT_MOC_LITERAL(173, 4380, 28), // "getChannelNeutral_FlightMode"
QT_MOC_LITERAL(174, 4409, 28), // "getChannelNeutral_Collective"
QT_MOC_LITERAL(175, 4438, 28), // "getChannelNeutral_Accessory0"
QT_MOC_LITERAL(176, 4467, 28), // "getChannelNeutral_Accessory1"
QT_MOC_LITERAL(177, 4496, 28), // "getChannelNeutral_Accessory2"
QT_MOC_LITERAL(178, 4525, 13), // "getChannelMax"
QT_MOC_LITERAL(179, 4539, 22), // "getChannelMax_Throttle"
QT_MOC_LITERAL(180, 4562, 18), // "getChannelMax_Roll"
QT_MOC_LITERAL(181, 4581, 19), // "getChannelMax_Pitch"
QT_MOC_LITERAL(182, 4601, 17), // "getChannelMax_Yaw"
QT_MOC_LITERAL(183, 4619, 24), // "getChannelMax_FlightMode"
QT_MOC_LITERAL(184, 4644, 24), // "getChannelMax_Collective"
QT_MOC_LITERAL(185, 4669, 24), // "getChannelMax_Accessory0"
QT_MOC_LITERAL(186, 4694, 24), // "getChannelMax_Accessory1"
QT_MOC_LITERAL(187, 4719, 24), // "getChannelMax_Accessory2"
QT_MOC_LITERAL(188, 4744, 15), // "getResponseTime"
QT_MOC_LITERAL(189, 4760, 20), // "getResponseTime_Roll"
QT_MOC_LITERAL(190, 4781, 21), // "getResponseTime_Pitch"
QT_MOC_LITERAL(191, 4803, 19), // "getResponseTime_Yaw"
QT_MOC_LITERAL(192, 4823, 26), // "getResponseTime_Collective"
QT_MOC_LITERAL(193, 4850, 26), // "getResponseTime_Accessory0"
QT_MOC_LITERAL(194, 4877, 26), // "getResponseTime_Accessory1"
QT_MOC_LITERAL(195, 4904, 26), // "getResponseTime_Accessory2"
QT_MOC_LITERAL(196, 4931, 16), // "getChannelGroups"
QT_MOC_LITERAL(197, 4948, 25), // "getChannelGroups_Throttle"
QT_MOC_LITERAL(198, 4974, 21), // "getChannelGroups_Roll"
QT_MOC_LITERAL(199, 4996, 22), // "getChannelGroups_Pitch"
QT_MOC_LITERAL(200, 5019, 20), // "getChannelGroups_Yaw"
QT_MOC_LITERAL(201, 5040, 27), // "getChannelGroups_FlightMode"
QT_MOC_LITERAL(202, 5068, 27), // "getChannelGroups_Collective"
QT_MOC_LITERAL(203, 5096, 27), // "getChannelGroups_Accessory0"
QT_MOC_LITERAL(204, 5124, 27), // "getChannelGroups_Accessory1"
QT_MOC_LITERAL(205, 5152, 27), // "getChannelGroups_Accessory2"
QT_MOC_LITERAL(206, 5180, 16), // "getChannelNumber"
QT_MOC_LITERAL(207, 5197, 25), // "getChannelNumber_Throttle"
QT_MOC_LITERAL(208, 5223, 21), // "getChannelNumber_Roll"
QT_MOC_LITERAL(209, 5245, 22), // "getChannelNumber_Pitch"
QT_MOC_LITERAL(210, 5268, 20), // "getChannelNumber_Yaw"
QT_MOC_LITERAL(211, 5289, 27), // "getChannelNumber_FlightMode"
QT_MOC_LITERAL(212, 5317, 27), // "getChannelNumber_Collective"
QT_MOC_LITERAL(213, 5345, 27), // "getChannelNumber_Accessory0"
QT_MOC_LITERAL(214, 5373, 27), // "getChannelNumber_Accessory1"
QT_MOC_LITERAL(215, 5401, 27), // "getChannelNumber_Accessory2"
QT_MOC_LITERAL(216, 5429, 19), // "getFlightModeNumber"
QT_MOC_LITERAL(217, 5449, 35), // "getFailsafeFlightModeSwitchPo..."
QT_MOC_LITERAL(218, 5485, 8), // "Deadband"
QT_MOC_LITERAL(219, 5494, 23), // "DeadbandAssistedControl"
QT_MOC_LITERAL(220, 5518, 24), // "FailsafeChannel_Throttle"
QT_MOC_LITERAL(221, 5543, 20), // "FailsafeChannel_Roll"
QT_MOC_LITERAL(222, 5564, 21), // "FailsafeChannel_Pitch"
QT_MOC_LITERAL(223, 5586, 19), // "FailsafeChannel_Yaw"
QT_MOC_LITERAL(224, 5606, 26), // "FailsafeChannel_Collective"
QT_MOC_LITERAL(225, 5633, 26), // "FailsafeChannel_Accessory0"
QT_MOC_LITERAL(226, 5660, 26), // "FailsafeChannel_Accessory1"
QT_MOC_LITERAL(227, 5687, 26), // "FailsafeChannel_Accessory2"
QT_MOC_LITERAL(228, 5714, 19), // "ChannelMin_Throttle"
QT_MOC_LITERAL(229, 5734, 15), // "ChannelMin_Roll"
QT_MOC_LITERAL(230, 5750, 16), // "ChannelMin_Pitch"
QT_MOC_LITERAL(231, 5767, 14), // "ChannelMin_Yaw"
QT_MOC_LITERAL(232, 5782, 21), // "ChannelMin_FlightMode"
QT_MOC_LITERAL(233, 5804, 21), // "ChannelMin_Collective"
QT_MOC_LITERAL(234, 5826, 21), // "ChannelMin_Accessory0"
QT_MOC_LITERAL(235, 5848, 21), // "ChannelMin_Accessory1"
QT_MOC_LITERAL(236, 5870, 21), // "ChannelMin_Accessory2"
QT_MOC_LITERAL(237, 5892, 23), // "ChannelNeutral_Throttle"
QT_MOC_LITERAL(238, 5916, 19), // "ChannelNeutral_Roll"
QT_MOC_LITERAL(239, 5936, 20), // "ChannelNeutral_Pitch"
QT_MOC_LITERAL(240, 5957, 18), // "ChannelNeutral_Yaw"
QT_MOC_LITERAL(241, 5976, 25), // "ChannelNeutral_FlightMode"
QT_MOC_LITERAL(242, 6002, 25), // "ChannelNeutral_Collective"
QT_MOC_LITERAL(243, 6028, 25), // "ChannelNeutral_Accessory0"
QT_MOC_LITERAL(244, 6054, 25), // "ChannelNeutral_Accessory1"
QT_MOC_LITERAL(245, 6080, 25), // "ChannelNeutral_Accessory2"
QT_MOC_LITERAL(246, 6106, 19), // "ChannelMax_Throttle"
QT_MOC_LITERAL(247, 6126, 15), // "ChannelMax_Roll"
QT_MOC_LITERAL(248, 6142, 16), // "ChannelMax_Pitch"
QT_MOC_LITERAL(249, 6159, 14), // "ChannelMax_Yaw"
QT_MOC_LITERAL(250, 6174, 21), // "ChannelMax_FlightMode"
QT_MOC_LITERAL(251, 6196, 21), // "ChannelMax_Collective"
QT_MOC_LITERAL(252, 6218, 21), // "ChannelMax_Accessory0"
QT_MOC_LITERAL(253, 6240, 21), // "ChannelMax_Accessory1"
QT_MOC_LITERAL(254, 6262, 21), // "ChannelMax_Accessory2"
QT_MOC_LITERAL(255, 6284, 17), // "ResponseTime_Roll"
QT_MOC_LITERAL(256, 6302, 18), // "ResponseTime_Pitch"
QT_MOC_LITERAL(257, 6321, 16), // "ResponseTime_Yaw"
QT_MOC_LITERAL(258, 6338, 23), // "ResponseTime_Collective"
QT_MOC_LITERAL(259, 6362, 23), // "ResponseTime_Accessory0"
QT_MOC_LITERAL(260, 6386, 23), // "ResponseTime_Accessory1"
QT_MOC_LITERAL(261, 6410, 23), // "ResponseTime_Accessory2"
QT_MOC_LITERAL(262, 6434, 22), // "ChannelGroups_Throttle"
QT_MOC_LITERAL(263, 6457, 18), // "ChannelGroups_Roll"
QT_MOC_LITERAL(264, 6476, 19), // "ChannelGroups_Pitch"
QT_MOC_LITERAL(265, 6496, 17), // "ChannelGroups_Yaw"
QT_MOC_LITERAL(266, 6514, 24), // "ChannelGroups_FlightMode"
QT_MOC_LITERAL(267, 6539, 24), // "ChannelGroups_Collective"
QT_MOC_LITERAL(268, 6564, 24), // "ChannelGroups_Accessory0"
QT_MOC_LITERAL(269, 6589, 24), // "ChannelGroups_Accessory1"
QT_MOC_LITERAL(270, 6614, 24), // "ChannelGroups_Accessory2"
QT_MOC_LITERAL(271, 6639, 22), // "ChannelNumber_Throttle"
QT_MOC_LITERAL(272, 6662, 18), // "ChannelNumber_Roll"
QT_MOC_LITERAL(273, 6681, 19), // "ChannelNumber_Pitch"
QT_MOC_LITERAL(274, 6701, 17), // "ChannelNumber_Yaw"
QT_MOC_LITERAL(275, 6719, 24), // "ChannelNumber_FlightMode"
QT_MOC_LITERAL(276, 6744, 24), // "ChannelNumber_Collective"
QT_MOC_LITERAL(277, 6769, 24), // "ChannelNumber_Accessory0"
QT_MOC_LITERAL(278, 6794, 24), // "ChannelNumber_Accessory1"
QT_MOC_LITERAL(279, 6819, 24), // "ChannelNumber_Accessory2"
QT_MOC_LITERAL(280, 6844, 16), // "FlightModeNumber"
QT_MOC_LITERAL(281, 6861, 32) // "FailsafeFlightModeSwitchPosition"

    },
    "ManualControlSettings\0DeadbandChanged\0"
    "\0value\0DeadbandAssistedControlChanged\0"
    "FailsafeChannelChanged\0index\0"
    "FailsafeChannel_ThrottleChanged\0"
    "FailsafeChannel_RollChanged\0"
    "FailsafeChannel_PitchChanged\0"
    "FailsafeChannel_YawChanged\0"
    "FailsafeChannel_CollectiveChanged\0"
    "FailsafeChannel_Accessory0Changed\0"
    "FailsafeChannel_Accessory1Changed\0"
    "FailsafeChannel_Accessory2Changed\0"
    "ChannelMinChanged\0ChannelMin_ThrottleChanged\0"
    "ChannelMin_RollChanged\0ChannelMin_PitchChanged\0"
    "ChannelMin_YawChanged\0"
    "ChannelMin_FlightModeChanged\0"
    "ChannelMin_CollectiveChanged\0"
    "ChannelMin_Accessory0Changed\0"
    "ChannelMin_Accessory1Changed\0"
    "ChannelMin_Accessory2Changed\0"
    "ChannelNeutralChanged\0"
    "ChannelNeutral_ThrottleChanged\0"
    "ChannelNeutral_RollChanged\0"
    "ChannelNeutral_PitchChanged\0"
    "ChannelNeutral_YawChanged\0"
    "ChannelNeutral_FlightModeChanged\0"
    "ChannelNeutral_CollectiveChanged\0"
    "ChannelNeutral_Accessory0Changed\0"
    "ChannelNeutral_Accessory1Changed\0"
    "ChannelNeutral_Accessory2Changed\0"
    "ChannelMaxChanged\0ChannelMax_ThrottleChanged\0"
    "ChannelMax_RollChanged\0ChannelMax_PitchChanged\0"
    "ChannelMax_YawChanged\0"
    "ChannelMax_FlightModeChanged\0"
    "ChannelMax_CollectiveChanged\0"
    "ChannelMax_Accessory0Changed\0"
    "ChannelMax_Accessory1Changed\0"
    "ChannelMax_Accessory2Changed\0"
    "ResponseTimeChanged\0ResponseTime_RollChanged\0"
    "ResponseTime_PitchChanged\0"
    "ResponseTime_YawChanged\0"
    "ResponseTime_CollectiveChanged\0"
    "ResponseTime_Accessory0Changed\0"
    "ResponseTime_Accessory1Changed\0"
    "ResponseTime_Accessory2Changed\0"
    "ChannelGroupsChanged\0ChannelGroups_ThrottleChanged\0"
    "ChannelGroups_RollChanged\0"
    "ChannelGroups_PitchChanged\0"
    "ChannelGroups_YawChanged\0"
    "ChannelGroups_FlightModeChanged\0"
    "ChannelGroups_CollectiveChanged\0"
    "ChannelGroups_Accessory0Changed\0"
    "ChannelGroups_Accessory1Changed\0"
    "ChannelGroups_Accessory2Changed\0"
    "ChannelNumberChanged\0ChannelNumber_ThrottleChanged\0"
    "ChannelNumber_RollChanged\0"
    "ChannelNumber_PitchChanged\0"
    "ChannelNumber_YawChanged\0"
    "ChannelNumber_FlightModeChanged\0"
    "ChannelNumber_CollectiveChanged\0"
    "ChannelNumber_Accessory0Changed\0"
    "ChannelNumber_Accessory1Changed\0"
    "ChannelNumber_Accessory2Changed\0"
    "FlightModeNumberChanged\0"
    "FailsafeFlightModeSwitchPositionChanged\0"
    "setDeadband\0setDeadbandAssistedControl\0"
    "setFailsafeChannel\0setFailsafeChannel_Throttle\0"
    "setFailsafeChannel_Roll\0"
    "setFailsafeChannel_Pitch\0"
    "setFailsafeChannel_Yaw\0"
    "setFailsafeChannel_Collective\0"
    "setFailsafeChannel_Accessory0\0"
    "setFailsafeChannel_Accessory1\0"
    "setFailsafeChannel_Accessory2\0"
    "setChannelMin\0setChannelMin_Throttle\0"
    "setChannelMin_Roll\0setChannelMin_Pitch\0"
    "setChannelMin_Yaw\0setChannelMin_FlightMode\0"
    "setChannelMin_Collective\0"
    "setChannelMin_Accessory0\0"
    "setChannelMin_Accessory1\0"
    "setChannelMin_Accessory2\0setChannelNeutral\0"
    "setChannelNeutral_Throttle\0"
    "setChannelNeutral_Roll\0setChannelNeutral_Pitch\0"
    "setChannelNeutral_Yaw\0"
    "setChannelNeutral_FlightMode\0"
    "setChannelNeutral_Collective\0"
    "setChannelNeutral_Accessory0\0"
    "setChannelNeutral_Accessory1\0"
    "setChannelNeutral_Accessory2\0setChannelMax\0"
    "setChannelMax_Throttle\0setChannelMax_Roll\0"
    "setChannelMax_Pitch\0setChannelMax_Yaw\0"
    "setChannelMax_FlightMode\0"
    "setChannelMax_Collective\0"
    "setChannelMax_Accessory0\0"
    "setChannelMax_Accessory1\0"
    "setChannelMax_Accessory2\0setResponseTime\0"
    "setResponseTime_Roll\0setResponseTime_Pitch\0"
    "setResponseTime_Yaw\0setResponseTime_Collective\0"
    "setResponseTime_Accessory0\0"
    "setResponseTime_Accessory1\0"
    "setResponseTime_Accessory2\0setChannelGroups\0"
    "setChannelGroups_Throttle\0"
    "setChannelGroups_Roll\0setChannelGroups_Pitch\0"
    "setChannelGroups_Yaw\0setChannelGroups_FlightMode\0"
    "setChannelGroups_Collective\0"
    "setChannelGroups_Accessory0\0"
    "setChannelGroups_Accessory1\0"
    "setChannelGroups_Accessory2\0"
    "setChannelNumber\0setChannelNumber_Throttle\0"
    "setChannelNumber_Roll\0setChannelNumber_Pitch\0"
    "setChannelNumber_Yaw\0setChannelNumber_FlightMode\0"
    "setChannelNumber_Collective\0"
    "setChannelNumber_Accessory0\0"
    "setChannelNumber_Accessory1\0"
    "setChannelNumber_Accessory2\0"
    "setFlightModeNumber\0"
    "setFailsafeFlightModeSwitchPosition\0"
    "emitNotifications\0getDeadband\0"
    "getDeadbandAssistedControl\0"
    "getFailsafeChannel\0getFailsafeChannel_Throttle\0"
    "getFailsafeChannel_Roll\0"
    "getFailsafeChannel_Pitch\0"
    "getFailsafeChannel_Yaw\0"
    "getFailsafeChannel_Collective\0"
    "getFailsafeChannel_Accessory0\0"
    "getFailsafeChannel_Accessory1\0"
    "getFailsafeChannel_Accessory2\0"
    "getChannelMin\0getChannelMin_Throttle\0"
    "getChannelMin_Roll\0getChannelMin_Pitch\0"
    "getChannelMin_Yaw\0getChannelMin_FlightMode\0"
    "getChannelMin_Collective\0"
    "getChannelMin_Accessory0\0"
    "getChannelMin_Accessory1\0"
    "getChannelMin_Accessory2\0getChannelNeutral\0"
    "getChannelNeutral_Throttle\0"
    "getChannelNeutral_Roll\0getChannelNeutral_Pitch\0"
    "getChannelNeutral_Yaw\0"
    "getChannelNeutral_FlightMode\0"
    "getChannelNeutral_Collective\0"
    "getChannelNeutral_Accessory0\0"
    "getChannelNeutral_Accessory1\0"
    "getChannelNeutral_Accessory2\0getChannelMax\0"
    "getChannelMax_Throttle\0getChannelMax_Roll\0"
    "getChannelMax_Pitch\0getChannelMax_Yaw\0"
    "getChannelMax_FlightMode\0"
    "getChannelMax_Collective\0"
    "getChannelMax_Accessory0\0"
    "getChannelMax_Accessory1\0"
    "getChannelMax_Accessory2\0getResponseTime\0"
    "getResponseTime_Roll\0getResponseTime_Pitch\0"
    "getResponseTime_Yaw\0getResponseTime_Collective\0"
    "getResponseTime_Accessory0\0"
    "getResponseTime_Accessory1\0"
    "getResponseTime_Accessory2\0getChannelGroups\0"
    "getChannelGroups_Throttle\0"
    "getChannelGroups_Roll\0getChannelGroups_Pitch\0"
    "getChannelGroups_Yaw\0getChannelGroups_FlightMode\0"
    "getChannelGroups_Collective\0"
    "getChannelGroups_Accessory0\0"
    "getChannelGroups_Accessory1\0"
    "getChannelGroups_Accessory2\0"
    "getChannelNumber\0getChannelNumber_Throttle\0"
    "getChannelNumber_Roll\0getChannelNumber_Pitch\0"
    "getChannelNumber_Yaw\0getChannelNumber_FlightMode\0"
    "getChannelNumber_Collective\0"
    "getChannelNumber_Accessory0\0"
    "getChannelNumber_Accessory1\0"
    "getChannelNumber_Accessory2\0"
    "getFlightModeNumber\0"
    "getFailsafeFlightModeSwitchPosition\0"
    "Deadband\0DeadbandAssistedControl\0"
    "FailsafeChannel_Throttle\0FailsafeChannel_Roll\0"
    "FailsafeChannel_Pitch\0FailsafeChannel_Yaw\0"
    "FailsafeChannel_Collective\0"
    "FailsafeChannel_Accessory0\0"
    "FailsafeChannel_Accessory1\0"
    "FailsafeChannel_Accessory2\0"
    "ChannelMin_Throttle\0ChannelMin_Roll\0"
    "ChannelMin_Pitch\0ChannelMin_Yaw\0"
    "ChannelMin_FlightMode\0ChannelMin_Collective\0"
    "ChannelMin_Accessory0\0ChannelMin_Accessory1\0"
    "ChannelMin_Accessory2\0ChannelNeutral_Throttle\0"
    "ChannelNeutral_Roll\0ChannelNeutral_Pitch\0"
    "ChannelNeutral_Yaw\0ChannelNeutral_FlightMode\0"
    "ChannelNeutral_Collective\0"
    "ChannelNeutral_Accessory0\0"
    "ChannelNeutral_Accessory1\0"
    "ChannelNeutral_Accessory2\0ChannelMax_Throttle\0"
    "ChannelMax_Roll\0ChannelMax_Pitch\0"
    "ChannelMax_Yaw\0ChannelMax_FlightMode\0"
    "ChannelMax_Collective\0ChannelMax_Accessory0\0"
    "ChannelMax_Accessory1\0ChannelMax_Accessory2\0"
    "ResponseTime_Roll\0ResponseTime_Pitch\0"
    "ResponseTime_Yaw\0ResponseTime_Collective\0"
    "ResponseTime_Accessory0\0ResponseTime_Accessory1\0"
    "ResponseTime_Accessory2\0ChannelGroups_Throttle\0"
    "ChannelGroups_Roll\0ChannelGroups_Pitch\0"
    "ChannelGroups_Yaw\0ChannelGroups_FlightMode\0"
    "ChannelGroups_Collective\0"
    "ChannelGroups_Accessory0\0"
    "ChannelGroups_Accessory1\0"
    "ChannelGroups_Accessory2\0"
    "ChannelNumber_Throttle\0ChannelNumber_Roll\0"
    "ChannelNumber_Pitch\0ChannelNumber_Yaw\0"
    "ChannelNumber_FlightMode\0"
    "ChannelNumber_Collective\0"
    "ChannelNumber_Accessory0\0"
    "ChannelNumber_Accessory1\0"
    "ChannelNumber_Accessory2\0FlightModeNumber\0"
    "FailsafeFlightModeSwitchPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ManualControlSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     214,   14, // methods
      64, 1624, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      71,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1, 1084,    2, 0x06 /* Public */,
       4,    1, 1087,    2, 0x06 /* Public */,
       5,    2, 1090,    2, 0x06 /* Public */,
       7,    1, 1095,    2, 0x06 /* Public */,
       8,    1, 1098,    2, 0x06 /* Public */,
       9,    1, 1101,    2, 0x06 /* Public */,
      10,    1, 1104,    2, 0x06 /* Public */,
      11,    1, 1107,    2, 0x06 /* Public */,
      12,    1, 1110,    2, 0x06 /* Public */,
      13,    1, 1113,    2, 0x06 /* Public */,
      14,    1, 1116,    2, 0x06 /* Public */,
      15,    2, 1119,    2, 0x06 /* Public */,
      16,    1, 1124,    2, 0x06 /* Public */,
      17,    1, 1127,    2, 0x06 /* Public */,
      18,    1, 1130,    2, 0x06 /* Public */,
      19,    1, 1133,    2, 0x06 /* Public */,
      20,    1, 1136,    2, 0x06 /* Public */,
      21,    1, 1139,    2, 0x06 /* Public */,
      22,    1, 1142,    2, 0x06 /* Public */,
      23,    1, 1145,    2, 0x06 /* Public */,
      24,    1, 1148,    2, 0x06 /* Public */,
      25,    2, 1151,    2, 0x06 /* Public */,
      26,    1, 1156,    2, 0x06 /* Public */,
      27,    1, 1159,    2, 0x06 /* Public */,
      28,    1, 1162,    2, 0x06 /* Public */,
      29,    1, 1165,    2, 0x06 /* Public */,
      30,    1, 1168,    2, 0x06 /* Public */,
      31,    1, 1171,    2, 0x06 /* Public */,
      32,    1, 1174,    2, 0x06 /* Public */,
      33,    1, 1177,    2, 0x06 /* Public */,
      34,    1, 1180,    2, 0x06 /* Public */,
      35,    2, 1183,    2, 0x06 /* Public */,
      36,    1, 1188,    2, 0x06 /* Public */,
      37,    1, 1191,    2, 0x06 /* Public */,
      38,    1, 1194,    2, 0x06 /* Public */,
      39,    1, 1197,    2, 0x06 /* Public */,
      40,    1, 1200,    2, 0x06 /* Public */,
      41,    1, 1203,    2, 0x06 /* Public */,
      42,    1, 1206,    2, 0x06 /* Public */,
      43,    1, 1209,    2, 0x06 /* Public */,
      44,    1, 1212,    2, 0x06 /* Public */,
      45,    2, 1215,    2, 0x06 /* Public */,
      46,    1, 1220,    2, 0x06 /* Public */,
      47,    1, 1223,    2, 0x06 /* Public */,
      48,    1, 1226,    2, 0x06 /* Public */,
      49,    1, 1229,    2, 0x06 /* Public */,
      50,    1, 1232,    2, 0x06 /* Public */,
      51,    1, 1235,    2, 0x06 /* Public */,
      52,    1, 1238,    2, 0x06 /* Public */,
      53,    2, 1241,    2, 0x06 /* Public */,
      54,    1, 1246,    2, 0x06 /* Public */,
      55,    1, 1249,    2, 0x06 /* Public */,
      56,    1, 1252,    2, 0x06 /* Public */,
      57,    1, 1255,    2, 0x06 /* Public */,
      58,    1, 1258,    2, 0x06 /* Public */,
      59,    1, 1261,    2, 0x06 /* Public */,
      60,    1, 1264,    2, 0x06 /* Public */,
      61,    1, 1267,    2, 0x06 /* Public */,
      62,    1, 1270,    2, 0x06 /* Public */,
      63,    2, 1273,    2, 0x06 /* Public */,
      64,    1, 1278,    2, 0x06 /* Public */,
      65,    1, 1281,    2, 0x06 /* Public */,
      66,    1, 1284,    2, 0x06 /* Public */,
      67,    1, 1287,    2, 0x06 /* Public */,
      68,    1, 1290,    2, 0x06 /* Public */,
      69,    1, 1293,    2, 0x06 /* Public */,
      70,    1, 1296,    2, 0x06 /* Public */,
      71,    1, 1299,    2, 0x06 /* Public */,
      72,    1, 1302,    2, 0x06 /* Public */,
      73,    1, 1305,    2, 0x06 /* Public */,
      74,    1, 1308,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      75,    1, 1311,    2, 0x0a /* Public */,
      76,    1, 1314,    2, 0x0a /* Public */,
      77,    2, 1317,    2, 0x0a /* Public */,
      78,    1, 1322,    2, 0x0a /* Public */,
      79,    1, 1325,    2, 0x0a /* Public */,
      80,    1, 1328,    2, 0x0a /* Public */,
      81,    1, 1331,    2, 0x0a /* Public */,
      82,    1, 1334,    2, 0x0a /* Public */,
      83,    1, 1337,    2, 0x0a /* Public */,
      84,    1, 1340,    2, 0x0a /* Public */,
      85,    1, 1343,    2, 0x0a /* Public */,
      86,    2, 1346,    2, 0x0a /* Public */,
      87,    1, 1351,    2, 0x0a /* Public */,
      88,    1, 1354,    2, 0x0a /* Public */,
      89,    1, 1357,    2, 0x0a /* Public */,
      90,    1, 1360,    2, 0x0a /* Public */,
      91,    1, 1363,    2, 0x0a /* Public */,
      92,    1, 1366,    2, 0x0a /* Public */,
      93,    1, 1369,    2, 0x0a /* Public */,
      94,    1, 1372,    2, 0x0a /* Public */,
      95,    1, 1375,    2, 0x0a /* Public */,
      96,    2, 1378,    2, 0x0a /* Public */,
      97,    1, 1383,    2, 0x0a /* Public */,
      98,    1, 1386,    2, 0x0a /* Public */,
      99,    1, 1389,    2, 0x0a /* Public */,
     100,    1, 1392,    2, 0x0a /* Public */,
     101,    1, 1395,    2, 0x0a /* Public */,
     102,    1, 1398,    2, 0x0a /* Public */,
     103,    1, 1401,    2, 0x0a /* Public */,
     104,    1, 1404,    2, 0x0a /* Public */,
     105,    1, 1407,    2, 0x0a /* Public */,
     106,    2, 1410,    2, 0x0a /* Public */,
     107,    1, 1415,    2, 0x0a /* Public */,
     108,    1, 1418,    2, 0x0a /* Public */,
     109,    1, 1421,    2, 0x0a /* Public */,
     110,    1, 1424,    2, 0x0a /* Public */,
     111,    1, 1427,    2, 0x0a /* Public */,
     112,    1, 1430,    2, 0x0a /* Public */,
     113,    1, 1433,    2, 0x0a /* Public */,
     114,    1, 1436,    2, 0x0a /* Public */,
     115,    1, 1439,    2, 0x0a /* Public */,
     116,    2, 1442,    2, 0x0a /* Public */,
     117,    1, 1447,    2, 0x0a /* Public */,
     118,    1, 1450,    2, 0x0a /* Public */,
     119,    1, 1453,    2, 0x0a /* Public */,
     120,    1, 1456,    2, 0x0a /* Public */,
     121,    1, 1459,    2, 0x0a /* Public */,
     122,    1, 1462,    2, 0x0a /* Public */,
     123,    1, 1465,    2, 0x0a /* Public */,
     124,    2, 1468,    2, 0x0a /* Public */,
     125,    1, 1473,    2, 0x0a /* Public */,
     126,    1, 1476,    2, 0x0a /* Public */,
     127,    1, 1479,    2, 0x0a /* Public */,
     128,    1, 1482,    2, 0x0a /* Public */,
     129,    1, 1485,    2, 0x0a /* Public */,
     130,    1, 1488,    2, 0x0a /* Public */,
     131,    1, 1491,    2, 0x0a /* Public */,
     132,    1, 1494,    2, 0x0a /* Public */,
     133,    1, 1497,    2, 0x0a /* Public */,
     134,    2, 1500,    2, 0x0a /* Public */,
     135,    1, 1505,    2, 0x0a /* Public */,
     136,    1, 1508,    2, 0x0a /* Public */,
     137,    1, 1511,    2, 0x0a /* Public */,
     138,    1, 1514,    2, 0x0a /* Public */,
     139,    1, 1517,    2, 0x0a /* Public */,
     140,    1, 1520,    2, 0x0a /* Public */,
     141,    1, 1523,    2, 0x0a /* Public */,
     142,    1, 1526,    2, 0x0a /* Public */,
     143,    1, 1529,    2, 0x0a /* Public */,
     144,    1, 1532,    2, 0x0a /* Public */,
     145,    1, 1535,    2, 0x0a /* Public */,
     146,    0, 1538,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
     147,    0, 1539,    2, 0x02 /* Public */,
     148,    0, 1540,    2, 0x02 /* Public */,
     149,    1, 1541,    2, 0x02 /* Public */,
     150,    0, 1544,    2, 0x02 /* Public */,
     151,    0, 1545,    2, 0x02 /* Public */,
     152,    0, 1546,    2, 0x02 /* Public */,
     153,    0, 1547,    2, 0x02 /* Public */,
     154,    0, 1548,    2, 0x02 /* Public */,
     155,    0, 1549,    2, 0x02 /* Public */,
     156,    0, 1550,    2, 0x02 /* Public */,
     157,    0, 1551,    2, 0x02 /* Public */,
     158,    1, 1552,    2, 0x02 /* Public */,
     159,    0, 1555,    2, 0x02 /* Public */,
     160,    0, 1556,    2, 0x02 /* Public */,
     161,    0, 1557,    2, 0x02 /* Public */,
     162,    0, 1558,    2, 0x02 /* Public */,
     163,    0, 1559,    2, 0x02 /* Public */,
     164,    0, 1560,    2, 0x02 /* Public */,
     165,    0, 1561,    2, 0x02 /* Public */,
     166,    0, 1562,    2, 0x02 /* Public */,
     167,    0, 1563,    2, 0x02 /* Public */,
     168,    1, 1564,    2, 0x02 /* Public */,
     169,    0, 1567,    2, 0x02 /* Public */,
     170,    0, 1568,    2, 0x02 /* Public */,
     171,    0, 1569,    2, 0x02 /* Public */,
     172,    0, 1570,    2, 0x02 /* Public */,
     173,    0, 1571,    2, 0x02 /* Public */,
     174,    0, 1572,    2, 0x02 /* Public */,
     175,    0, 1573,    2, 0x02 /* Public */,
     176,    0, 1574,    2, 0x02 /* Public */,
     177,    0, 1575,    2, 0x02 /* Public */,
     178,    1, 1576,    2, 0x02 /* Public */,
     179,    0, 1579,    2, 0x02 /* Public */,
     180,    0, 1580,    2, 0x02 /* Public */,
     181,    0, 1581,    2, 0x02 /* Public */,
     182,    0, 1582,    2, 0x02 /* Public */,
     183,    0, 1583,    2, 0x02 /* Public */,
     184,    0, 1584,    2, 0x02 /* Public */,
     185,    0, 1585,    2, 0x02 /* Public */,
     186,    0, 1586,    2, 0x02 /* Public */,
     187,    0, 1587,    2, 0x02 /* Public */,
     188,    1, 1588,    2, 0x02 /* Public */,
     189,    0, 1591,    2, 0x02 /* Public */,
     190,    0, 1592,    2, 0x02 /* Public */,
     191,    0, 1593,    2, 0x02 /* Public */,
     192,    0, 1594,    2, 0x02 /* Public */,
     193,    0, 1595,    2, 0x02 /* Public */,
     194,    0, 1596,    2, 0x02 /* Public */,
     195,    0, 1597,    2, 0x02 /* Public */,
     196,    1, 1598,    2, 0x02 /* Public */,
     197,    0, 1601,    2, 0x02 /* Public */,
     198,    0, 1602,    2, 0x02 /* Public */,
     199,    0, 1603,    2, 0x02 /* Public */,
     200,    0, 1604,    2, 0x02 /* Public */,
     201,    0, 1605,    2, 0x02 /* Public */,
     202,    0, 1606,    2, 0x02 /* Public */,
     203,    0, 1607,    2, 0x02 /* Public */,
     204,    0, 1608,    2, 0x02 /* Public */,
     205,    0, 1609,    2, 0x02 /* Public */,
     206,    1, 1610,    2, 0x02 /* Public */,
     207,    0, 1613,    2, 0x02 /* Public */,
     208,    0, 1614,    2, 0x02 /* Public */,
     209,    0, 1615,    2, 0x02 /* Public */,
     210,    0, 1616,    2, 0x02 /* Public */,
     211,    0, 1617,    2, 0x02 /* Public */,
     212,    0, 1618,    2, 0x02 /* Public */,
     213,    0, 1619,    2, 0x02 /* Public */,
     214,    0, 1620,    2, 0x02 /* Public */,
     215,    0, 1621,    2, 0x02 /* Public */,
     216,    0, 1622,    2, 0x02 /* Public */,
     217,    0, 1623,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    6,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    6,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    6,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    6,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UShort,    6,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
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

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    6,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    6,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    6,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Short,    6,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UShort,    6,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
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
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    6,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Short, QMetaType::UInt,    6,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short, QMetaType::UInt,    6,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short, QMetaType::UInt,    6,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::Short,
    QMetaType::UShort, QMetaType::UInt,    6,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UChar, QMetaType::UInt,    6,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    6,
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

 // properties: name, type, flags
     218, QMetaType::Float, 0x00495103,
     219, QMetaType::Float, 0x00495103,
     220, QMetaType::Float, 0x00495103,
     221, QMetaType::Float, 0x00495103,
     222, QMetaType::Float, 0x00495103,
     223, QMetaType::Float, 0x00495103,
     224, QMetaType::Float, 0x00495103,
     225, QMetaType::Float, 0x00495103,
     226, QMetaType::Float, 0x00495103,
     227, QMetaType::Float, 0x00495103,
     228, QMetaType::Short, 0x00495103,
     229, QMetaType::Short, 0x00495103,
     230, QMetaType::Short, 0x00495103,
     231, QMetaType::Short, 0x00495103,
     232, QMetaType::Short, 0x00495103,
     233, QMetaType::Short, 0x00495103,
     234, QMetaType::Short, 0x00495103,
     235, QMetaType::Short, 0x00495103,
     236, QMetaType::Short, 0x00495103,
     237, QMetaType::Short, 0x00495103,
     238, QMetaType::Short, 0x00495103,
     239, QMetaType::Short, 0x00495103,
     240, QMetaType::Short, 0x00495103,
     241, QMetaType::Short, 0x00495103,
     242, QMetaType::Short, 0x00495103,
     243, QMetaType::Short, 0x00495103,
     244, QMetaType::Short, 0x00495103,
     245, QMetaType::Short, 0x00495103,
     246, QMetaType::Short, 0x00495103,
     247, QMetaType::Short, 0x00495103,
     248, QMetaType::Short, 0x00495103,
     249, QMetaType::Short, 0x00495103,
     250, QMetaType::Short, 0x00495103,
     251, QMetaType::Short, 0x00495103,
     252, QMetaType::Short, 0x00495103,
     253, QMetaType::Short, 0x00495103,
     254, QMetaType::Short, 0x00495103,
     255, QMetaType::UShort, 0x00495103,
     256, QMetaType::UShort, 0x00495103,
     257, QMetaType::UShort, 0x00495103,
     258, QMetaType::UShort, 0x00495103,
     259, QMetaType::UShort, 0x00495103,
     260, QMetaType::UShort, 0x00495103,
     261, QMetaType::UShort, 0x00495103,
     262, QMetaType::UChar, 0x00495103,
     263, QMetaType::UChar, 0x00495103,
     264, QMetaType::UChar, 0x00495103,
     265, QMetaType::UChar, 0x00495103,
     266, QMetaType::UChar, 0x00495103,
     267, QMetaType::UChar, 0x00495103,
     268, QMetaType::UChar, 0x00495103,
     269, QMetaType::UChar, 0x00495103,
     270, QMetaType::UChar, 0x00495103,
     271, QMetaType::UChar, 0x00495103,
     272, QMetaType::UChar, 0x00495103,
     273, QMetaType::UChar, 0x00495103,
     274, QMetaType::UChar, 0x00495103,
     275, QMetaType::UChar, 0x00495103,
     276, QMetaType::UChar, 0x00495103,
     277, QMetaType::UChar, 0x00495103,
     278, QMetaType::UChar, 0x00495103,
     279, QMetaType::UChar, 0x00495103,
     280, QMetaType::UChar, 0x00495103,
     281, QMetaType::SChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       3,
       4,
       5,
       6,
       7,
       8,
       9,
      10,
      12,
      13,
      14,
      15,
      16,
      17,
      18,
      19,
      20,
      22,
      23,
      24,
      25,
      26,
      27,
      28,
      29,
      30,
      32,
      33,
      34,
      35,
      36,
      37,
      38,
      39,
      40,
      42,
      43,
      44,
      45,
      46,
      47,
      48,
      50,
      51,
      52,
      53,
      54,
      55,
      56,
      57,
      58,
      60,
      61,
      62,
      63,
      64,
      65,
      66,
      67,
      68,
      69,
      70,

       0        // eod
};

void ManualControlSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ManualControlSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->DeadbandChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->DeadbandAssistedControlChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->FailsafeChannelChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->FailsafeChannel_ThrottleChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->FailsafeChannel_RollChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->FailsafeChannel_PitchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->FailsafeChannel_YawChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->FailsafeChannel_CollectiveChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->FailsafeChannel_Accessory0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->FailsafeChannel_Accessory1Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->FailsafeChannel_Accessory2Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->ChannelMinChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 12: _t->ChannelMin_ThrottleChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 13: _t->ChannelMin_RollChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 14: _t->ChannelMin_PitchChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 15: _t->ChannelMin_YawChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 16: _t->ChannelMin_FlightModeChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 17: _t->ChannelMin_CollectiveChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 18: _t->ChannelMin_Accessory0Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 19: _t->ChannelMin_Accessory1Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 20: _t->ChannelMin_Accessory2Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 21: _t->ChannelNeutralChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 22: _t->ChannelNeutral_ThrottleChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 23: _t->ChannelNeutral_RollChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 24: _t->ChannelNeutral_PitchChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 25: _t->ChannelNeutral_YawChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 26: _t->ChannelNeutral_FlightModeChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 27: _t->ChannelNeutral_CollectiveChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 28: _t->ChannelNeutral_Accessory0Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 29: _t->ChannelNeutral_Accessory1Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 30: _t->ChannelNeutral_Accessory2Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 31: _t->ChannelMaxChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 32: _t->ChannelMax_ThrottleChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 33: _t->ChannelMax_RollChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 34: _t->ChannelMax_PitchChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 35: _t->ChannelMax_YawChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 36: _t->ChannelMax_FlightModeChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 37: _t->ChannelMax_CollectiveChanged((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 38: _t->ChannelMax_Accessory0Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 39: _t->ChannelMax_Accessory1Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 40: _t->ChannelMax_Accessory2Changed((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 41: _t->ResponseTimeChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 42: _t->ResponseTime_RollChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 43: _t->ResponseTime_PitchChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 44: _t->ResponseTime_YawChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 45: _t->ResponseTime_CollectiveChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 46: _t->ResponseTime_Accessory0Changed((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 47: _t->ResponseTime_Accessory1Changed((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 48: _t->ResponseTime_Accessory2Changed((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 49: _t->ChannelGroupsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 50: _t->ChannelGroups_ThrottleChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 51: _t->ChannelGroups_RollChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 52: _t->ChannelGroups_PitchChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 53: _t->ChannelGroups_YawChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 54: _t->ChannelGroups_FlightModeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 55: _t->ChannelGroups_CollectiveChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 56: _t->ChannelGroups_Accessory0Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 57: _t->ChannelGroups_Accessory1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 58: _t->ChannelGroups_Accessory2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 59: _t->ChannelNumberChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 60: _t->ChannelNumber_ThrottleChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 61: _t->ChannelNumber_RollChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 62: _t->ChannelNumber_PitchChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 63: _t->ChannelNumber_YawChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 64: _t->ChannelNumber_FlightModeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 65: _t->ChannelNumber_CollectiveChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 66: _t->ChannelNumber_Accessory0Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 67: _t->ChannelNumber_Accessory1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 68: _t->ChannelNumber_Accessory2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 69: _t->FlightModeNumberChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 70: _t->FailsafeFlightModeSwitchPositionChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 71: _t->setDeadband((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 72: _t->setDeadbandAssistedControl((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 73: _t->setFailsafeChannel((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 74: _t->setFailsafeChannel_Throttle((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 75: _t->setFailsafeChannel_Roll((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 76: _t->setFailsafeChannel_Pitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 77: _t->setFailsafeChannel_Yaw((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 78: _t->setFailsafeChannel_Collective((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 79: _t->setFailsafeChannel_Accessory0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 80: _t->setFailsafeChannel_Accessory1((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 81: _t->setFailsafeChannel_Accessory2((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 82: _t->setChannelMin((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 83: _t->setChannelMin_Throttle((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 84: _t->setChannelMin_Roll((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 85: _t->setChannelMin_Pitch((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 86: _t->setChannelMin_Yaw((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 87: _t->setChannelMin_FlightMode((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 88: _t->setChannelMin_Collective((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 89: _t->setChannelMin_Accessory0((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 90: _t->setChannelMin_Accessory1((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 91: _t->setChannelMin_Accessory2((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 92: _t->setChannelNeutral((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 93: _t->setChannelNeutral_Throttle((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 94: _t->setChannelNeutral_Roll((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 95: _t->setChannelNeutral_Pitch((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 96: _t->setChannelNeutral_Yaw((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 97: _t->setChannelNeutral_FlightMode((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 98: _t->setChannelNeutral_Collective((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 99: _t->setChannelNeutral_Accessory0((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 100: _t->setChannelNeutral_Accessory1((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 101: _t->setChannelNeutral_Accessory2((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 102: _t->setChannelMax((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 103: _t->setChannelMax_Throttle((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 104: _t->setChannelMax_Roll((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 105: _t->setChannelMax_Pitch((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 106: _t->setChannelMax_Yaw((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 107: _t->setChannelMax_FlightMode((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 108: _t->setChannelMax_Collective((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 109: _t->setChannelMax_Accessory0((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 110: _t->setChannelMax_Accessory1((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 111: _t->setChannelMax_Accessory2((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 112: _t->setResponseTime((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 113: _t->setResponseTime_Roll((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 114: _t->setResponseTime_Pitch((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 115: _t->setResponseTime_Yaw((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 116: _t->setResponseTime_Collective((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 117: _t->setResponseTime_Accessory0((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 118: _t->setResponseTime_Accessory1((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 119: _t->setResponseTime_Accessory2((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 120: _t->setChannelGroups((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 121: _t->setChannelGroups_Throttle((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 122: _t->setChannelGroups_Roll((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 123: _t->setChannelGroups_Pitch((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 124: _t->setChannelGroups_Yaw((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 125: _t->setChannelGroups_FlightMode((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 126: _t->setChannelGroups_Collective((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 127: _t->setChannelGroups_Accessory0((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 128: _t->setChannelGroups_Accessory1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 129: _t->setChannelGroups_Accessory2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 130: _t->setChannelNumber((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 131: _t->setChannelNumber_Throttle((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 132: _t->setChannelNumber_Roll((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 133: _t->setChannelNumber_Pitch((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 134: _t->setChannelNumber_Yaw((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 135: _t->setChannelNumber_FlightMode((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 136: _t->setChannelNumber_Collective((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 137: _t->setChannelNumber_Accessory0((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 138: _t->setChannelNumber_Accessory1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 139: _t->setChannelNumber_Accessory2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 140: _t->setFlightModeNumber((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 141: _t->setFailsafeFlightModeSwitchPosition((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 142: _t->emitNotifications(); break;
        case 143: { float _r = _t->getDeadband();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 144: { float _r = _t->getDeadbandAssistedControl();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 145: { float _r = _t->getFailsafeChannel((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 146: { float _r = _t->getFailsafeChannel_Throttle();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 147: { float _r = _t->getFailsafeChannel_Roll();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 148: { float _r = _t->getFailsafeChannel_Pitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 149: { float _r = _t->getFailsafeChannel_Yaw();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 150: { float _r = _t->getFailsafeChannel_Collective();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 151: { float _r = _t->getFailsafeChannel_Accessory0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 152: { float _r = _t->getFailsafeChannel_Accessory1();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 153: { float _r = _t->getFailsafeChannel_Accessory2();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 154: { qint16 _r = _t->getChannelMin((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 155: { qint16 _r = _t->getChannelMin_Throttle();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 156: { qint16 _r = _t->getChannelMin_Roll();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 157: { qint16 _r = _t->getChannelMin_Pitch();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 158: { qint16 _r = _t->getChannelMin_Yaw();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 159: { qint16 _r = _t->getChannelMin_FlightMode();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 160: { qint16 _r = _t->getChannelMin_Collective();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 161: { qint16 _r = _t->getChannelMin_Accessory0();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 162: { qint16 _r = _t->getChannelMin_Accessory1();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 163: { qint16 _r = _t->getChannelMin_Accessory2();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 164: { qint16 _r = _t->getChannelNeutral((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 165: { qint16 _r = _t->getChannelNeutral_Throttle();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 166: { qint16 _r = _t->getChannelNeutral_Roll();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 167: { qint16 _r = _t->getChannelNeutral_Pitch();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 168: { qint16 _r = _t->getChannelNeutral_Yaw();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 169: { qint16 _r = _t->getChannelNeutral_FlightMode();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 170: { qint16 _r = _t->getChannelNeutral_Collective();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 171: { qint16 _r = _t->getChannelNeutral_Accessory0();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 172: { qint16 _r = _t->getChannelNeutral_Accessory1();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 173: { qint16 _r = _t->getChannelNeutral_Accessory2();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 174: { qint16 _r = _t->getChannelMax((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 175: { qint16 _r = _t->getChannelMax_Throttle();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 176: { qint16 _r = _t->getChannelMax_Roll();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 177: { qint16 _r = _t->getChannelMax_Pitch();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 178: { qint16 _r = _t->getChannelMax_Yaw();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 179: { qint16 _r = _t->getChannelMax_FlightMode();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 180: { qint16 _r = _t->getChannelMax_Collective();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 181: { qint16 _r = _t->getChannelMax_Accessory0();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 182: { qint16 _r = _t->getChannelMax_Accessory1();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 183: { qint16 _r = _t->getChannelMax_Accessory2();
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = std::move(_r); }  break;
        case 184: { quint16 _r = _t->getResponseTime((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 185: { quint16 _r = _t->getResponseTime_Roll();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 186: { quint16 _r = _t->getResponseTime_Pitch();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 187: { quint16 _r = _t->getResponseTime_Yaw();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 188: { quint16 _r = _t->getResponseTime_Collective();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 189: { quint16 _r = _t->getResponseTime_Accessory0();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 190: { quint16 _r = _t->getResponseTime_Accessory1();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 191: { quint16 _r = _t->getResponseTime_Accessory2();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 192: { quint8 _r = _t->getChannelGroups((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 193: { quint8 _r = _t->getChannelGroups_Throttle();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 194: { quint8 _r = _t->getChannelGroups_Roll();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 195: { quint8 _r = _t->getChannelGroups_Pitch();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 196: { quint8 _r = _t->getChannelGroups_Yaw();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 197: { quint8 _r = _t->getChannelGroups_FlightMode();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 198: { quint8 _r = _t->getChannelGroups_Collective();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 199: { quint8 _r = _t->getChannelGroups_Accessory0();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 200: { quint8 _r = _t->getChannelGroups_Accessory1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 201: { quint8 _r = _t->getChannelGroups_Accessory2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 202: { quint8 _r = _t->getChannelNumber((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 203: { quint8 _r = _t->getChannelNumber_Throttle();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 204: { quint8 _r = _t->getChannelNumber_Roll();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 205: { quint8 _r = _t->getChannelNumber_Pitch();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 206: { quint8 _r = _t->getChannelNumber_Yaw();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 207: { quint8 _r = _t->getChannelNumber_FlightMode();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 208: { quint8 _r = _t->getChannelNumber_Collective();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 209: { quint8 _r = _t->getChannelNumber_Accessory0();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 210: { quint8 _r = _t->getChannelNumber_Accessory1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 211: { quint8 _r = _t->getChannelNumber_Accessory2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 212: { quint8 _r = _t->getFlightModeNumber();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 213: { qint8 _r = _t->getFailsafeFlightModeSwitchPosition();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ManualControlSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::DeadbandChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::DeadbandAssistedControlChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::FailsafeChannelChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::FailsafeChannel_ThrottleChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::FailsafeChannel_RollChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::FailsafeChannel_PitchChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::FailsafeChannel_YawChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::FailsafeChannel_CollectiveChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::FailsafeChannel_Accessory0Changed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::FailsafeChannel_Accessory1Changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::FailsafeChannel_Accessory2Changed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint32 , qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMinChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMin_ThrottleChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMin_RollChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMin_PitchChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMin_YawChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMin_FlightModeChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMin_CollectiveChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMin_Accessory0Changed)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMin_Accessory1Changed)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMin_Accessory2Changed)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint32 , qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNeutralChanged)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNeutral_ThrottleChanged)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNeutral_RollChanged)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNeutral_PitchChanged)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNeutral_YawChanged)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNeutral_FlightModeChanged)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNeutral_CollectiveChanged)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNeutral_Accessory0Changed)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNeutral_Accessory1Changed)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNeutral_Accessory2Changed)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint32 , qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMaxChanged)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMax_ThrottleChanged)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMax_RollChanged)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMax_PitchChanged)) {
                *result = 34;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMax_YawChanged)) {
                *result = 35;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMax_FlightModeChanged)) {
                *result = 36;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMax_CollectiveChanged)) {
                *result = 37;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMax_Accessory0Changed)) {
                *result = 38;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMax_Accessory1Changed)) {
                *result = 39;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelMax_Accessory2Changed)) {
                *result = 40;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint32 , quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ResponseTimeChanged)) {
                *result = 41;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ResponseTime_RollChanged)) {
                *result = 42;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ResponseTime_PitchChanged)) {
                *result = 43;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ResponseTime_YawChanged)) {
                *result = 44;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ResponseTime_CollectiveChanged)) {
                *result = 45;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ResponseTime_Accessory0Changed)) {
                *result = 46;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ResponseTime_Accessory1Changed)) {
                *result = 47;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ResponseTime_Accessory2Changed)) {
                *result = 48;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelGroupsChanged)) {
                *result = 49;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelGroups_ThrottleChanged)) {
                *result = 50;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelGroups_RollChanged)) {
                *result = 51;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelGroups_PitchChanged)) {
                *result = 52;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelGroups_YawChanged)) {
                *result = 53;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelGroups_FlightModeChanged)) {
                *result = 54;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelGroups_CollectiveChanged)) {
                *result = 55;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelGroups_Accessory0Changed)) {
                *result = 56;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelGroups_Accessory1Changed)) {
                *result = 57;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelGroups_Accessory2Changed)) {
                *result = 58;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNumberChanged)) {
                *result = 59;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNumber_ThrottleChanged)) {
                *result = 60;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNumber_RollChanged)) {
                *result = 61;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNumber_PitchChanged)) {
                *result = 62;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNumber_YawChanged)) {
                *result = 63;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNumber_FlightModeChanged)) {
                *result = 64;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNumber_CollectiveChanged)) {
                *result = 65;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNumber_Accessory0Changed)) {
                *result = 66;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNumber_Accessory1Changed)) {
                *result = 67;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::ChannelNumber_Accessory2Changed)) {
                *result = 68;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::FlightModeNumberChanged)) {
                *result = 69;
                return;
            }
        }
        {
            using _t = void (ManualControlSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ManualControlSettings::FailsafeFlightModeSwitchPositionChanged)) {
                *result = 70;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ManualControlSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getDeadband(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getDeadbandAssistedControl(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getFailsafeChannel_Throttle(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getFailsafeChannel_Roll(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getFailsafeChannel_Pitch(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getFailsafeChannel_Yaw(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getFailsafeChannel_Collective(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getFailsafeChannel_Accessory0(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getFailsafeChannel_Accessory1(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->getFailsafeChannel_Accessory2(); break;
        case 10: *reinterpret_cast< qint16*>(_v) = _t->getChannelMin_Throttle(); break;
        case 11: *reinterpret_cast< qint16*>(_v) = _t->getChannelMin_Roll(); break;
        case 12: *reinterpret_cast< qint16*>(_v) = _t->getChannelMin_Pitch(); break;
        case 13: *reinterpret_cast< qint16*>(_v) = _t->getChannelMin_Yaw(); break;
        case 14: *reinterpret_cast< qint16*>(_v) = _t->getChannelMin_FlightMode(); break;
        case 15: *reinterpret_cast< qint16*>(_v) = _t->getChannelMin_Collective(); break;
        case 16: *reinterpret_cast< qint16*>(_v) = _t->getChannelMin_Accessory0(); break;
        case 17: *reinterpret_cast< qint16*>(_v) = _t->getChannelMin_Accessory1(); break;
        case 18: *reinterpret_cast< qint16*>(_v) = _t->getChannelMin_Accessory2(); break;
        case 19: *reinterpret_cast< qint16*>(_v) = _t->getChannelNeutral_Throttle(); break;
        case 20: *reinterpret_cast< qint16*>(_v) = _t->getChannelNeutral_Roll(); break;
        case 21: *reinterpret_cast< qint16*>(_v) = _t->getChannelNeutral_Pitch(); break;
        case 22: *reinterpret_cast< qint16*>(_v) = _t->getChannelNeutral_Yaw(); break;
        case 23: *reinterpret_cast< qint16*>(_v) = _t->getChannelNeutral_FlightMode(); break;
        case 24: *reinterpret_cast< qint16*>(_v) = _t->getChannelNeutral_Collective(); break;
        case 25: *reinterpret_cast< qint16*>(_v) = _t->getChannelNeutral_Accessory0(); break;
        case 26: *reinterpret_cast< qint16*>(_v) = _t->getChannelNeutral_Accessory1(); break;
        case 27: *reinterpret_cast< qint16*>(_v) = _t->getChannelNeutral_Accessory2(); break;
        case 28: *reinterpret_cast< qint16*>(_v) = _t->getChannelMax_Throttle(); break;
        case 29: *reinterpret_cast< qint16*>(_v) = _t->getChannelMax_Roll(); break;
        case 30: *reinterpret_cast< qint16*>(_v) = _t->getChannelMax_Pitch(); break;
        case 31: *reinterpret_cast< qint16*>(_v) = _t->getChannelMax_Yaw(); break;
        case 32: *reinterpret_cast< qint16*>(_v) = _t->getChannelMax_FlightMode(); break;
        case 33: *reinterpret_cast< qint16*>(_v) = _t->getChannelMax_Collective(); break;
        case 34: *reinterpret_cast< qint16*>(_v) = _t->getChannelMax_Accessory0(); break;
        case 35: *reinterpret_cast< qint16*>(_v) = _t->getChannelMax_Accessory1(); break;
        case 36: *reinterpret_cast< qint16*>(_v) = _t->getChannelMax_Accessory2(); break;
        case 37: *reinterpret_cast< quint16*>(_v) = _t->getResponseTime_Roll(); break;
        case 38: *reinterpret_cast< quint16*>(_v) = _t->getResponseTime_Pitch(); break;
        case 39: *reinterpret_cast< quint16*>(_v) = _t->getResponseTime_Yaw(); break;
        case 40: *reinterpret_cast< quint16*>(_v) = _t->getResponseTime_Collective(); break;
        case 41: *reinterpret_cast< quint16*>(_v) = _t->getResponseTime_Accessory0(); break;
        case 42: *reinterpret_cast< quint16*>(_v) = _t->getResponseTime_Accessory1(); break;
        case 43: *reinterpret_cast< quint16*>(_v) = _t->getResponseTime_Accessory2(); break;
        case 44: *reinterpret_cast< quint8*>(_v) = _t->getChannelGroups_Throttle(); break;
        case 45: *reinterpret_cast< quint8*>(_v) = _t->getChannelGroups_Roll(); break;
        case 46: *reinterpret_cast< quint8*>(_v) = _t->getChannelGroups_Pitch(); break;
        case 47: *reinterpret_cast< quint8*>(_v) = _t->getChannelGroups_Yaw(); break;
        case 48: *reinterpret_cast< quint8*>(_v) = _t->getChannelGroups_FlightMode(); break;
        case 49: *reinterpret_cast< quint8*>(_v) = _t->getChannelGroups_Collective(); break;
        case 50: *reinterpret_cast< quint8*>(_v) = _t->getChannelGroups_Accessory0(); break;
        case 51: *reinterpret_cast< quint8*>(_v) = _t->getChannelGroups_Accessory1(); break;
        case 52: *reinterpret_cast< quint8*>(_v) = _t->getChannelGroups_Accessory2(); break;
        case 53: *reinterpret_cast< quint8*>(_v) = _t->getChannelNumber_Throttle(); break;
        case 54: *reinterpret_cast< quint8*>(_v) = _t->getChannelNumber_Roll(); break;
        case 55: *reinterpret_cast< quint8*>(_v) = _t->getChannelNumber_Pitch(); break;
        case 56: *reinterpret_cast< quint8*>(_v) = _t->getChannelNumber_Yaw(); break;
        case 57: *reinterpret_cast< quint8*>(_v) = _t->getChannelNumber_FlightMode(); break;
        case 58: *reinterpret_cast< quint8*>(_v) = _t->getChannelNumber_Collective(); break;
        case 59: *reinterpret_cast< quint8*>(_v) = _t->getChannelNumber_Accessory0(); break;
        case 60: *reinterpret_cast< quint8*>(_v) = _t->getChannelNumber_Accessory1(); break;
        case 61: *reinterpret_cast< quint8*>(_v) = _t->getChannelNumber_Accessory2(); break;
        case 62: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeNumber(); break;
        case 63: *reinterpret_cast< qint8*>(_v) = _t->getFailsafeFlightModeSwitchPosition(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ManualControlSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDeadband(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setDeadbandAssistedControl(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setFailsafeChannel_Throttle(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setFailsafeChannel_Roll(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setFailsafeChannel_Pitch(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setFailsafeChannel_Yaw(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setFailsafeChannel_Collective(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setFailsafeChannel_Accessory0(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setFailsafeChannel_Accessory1(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setFailsafeChannel_Accessory2(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setChannelMin_Throttle(*reinterpret_cast< qint16*>(_v)); break;
        case 11: _t->setChannelMin_Roll(*reinterpret_cast< qint16*>(_v)); break;
        case 12: _t->setChannelMin_Pitch(*reinterpret_cast< qint16*>(_v)); break;
        case 13: _t->setChannelMin_Yaw(*reinterpret_cast< qint16*>(_v)); break;
        case 14: _t->setChannelMin_FlightMode(*reinterpret_cast< qint16*>(_v)); break;
        case 15: _t->setChannelMin_Collective(*reinterpret_cast< qint16*>(_v)); break;
        case 16: _t->setChannelMin_Accessory0(*reinterpret_cast< qint16*>(_v)); break;
        case 17: _t->setChannelMin_Accessory1(*reinterpret_cast< qint16*>(_v)); break;
        case 18: _t->setChannelMin_Accessory2(*reinterpret_cast< qint16*>(_v)); break;
        case 19: _t->setChannelNeutral_Throttle(*reinterpret_cast< qint16*>(_v)); break;
        case 20: _t->setChannelNeutral_Roll(*reinterpret_cast< qint16*>(_v)); break;
        case 21: _t->setChannelNeutral_Pitch(*reinterpret_cast< qint16*>(_v)); break;
        case 22: _t->setChannelNeutral_Yaw(*reinterpret_cast< qint16*>(_v)); break;
        case 23: _t->setChannelNeutral_FlightMode(*reinterpret_cast< qint16*>(_v)); break;
        case 24: _t->setChannelNeutral_Collective(*reinterpret_cast< qint16*>(_v)); break;
        case 25: _t->setChannelNeutral_Accessory0(*reinterpret_cast< qint16*>(_v)); break;
        case 26: _t->setChannelNeutral_Accessory1(*reinterpret_cast< qint16*>(_v)); break;
        case 27: _t->setChannelNeutral_Accessory2(*reinterpret_cast< qint16*>(_v)); break;
        case 28: _t->setChannelMax_Throttle(*reinterpret_cast< qint16*>(_v)); break;
        case 29: _t->setChannelMax_Roll(*reinterpret_cast< qint16*>(_v)); break;
        case 30: _t->setChannelMax_Pitch(*reinterpret_cast< qint16*>(_v)); break;
        case 31: _t->setChannelMax_Yaw(*reinterpret_cast< qint16*>(_v)); break;
        case 32: _t->setChannelMax_FlightMode(*reinterpret_cast< qint16*>(_v)); break;
        case 33: _t->setChannelMax_Collective(*reinterpret_cast< qint16*>(_v)); break;
        case 34: _t->setChannelMax_Accessory0(*reinterpret_cast< qint16*>(_v)); break;
        case 35: _t->setChannelMax_Accessory1(*reinterpret_cast< qint16*>(_v)); break;
        case 36: _t->setChannelMax_Accessory2(*reinterpret_cast< qint16*>(_v)); break;
        case 37: _t->setResponseTime_Roll(*reinterpret_cast< quint16*>(_v)); break;
        case 38: _t->setResponseTime_Pitch(*reinterpret_cast< quint16*>(_v)); break;
        case 39: _t->setResponseTime_Yaw(*reinterpret_cast< quint16*>(_v)); break;
        case 40: _t->setResponseTime_Collective(*reinterpret_cast< quint16*>(_v)); break;
        case 41: _t->setResponseTime_Accessory0(*reinterpret_cast< quint16*>(_v)); break;
        case 42: _t->setResponseTime_Accessory1(*reinterpret_cast< quint16*>(_v)); break;
        case 43: _t->setResponseTime_Accessory2(*reinterpret_cast< quint16*>(_v)); break;
        case 44: _t->setChannelGroups_Throttle(*reinterpret_cast< quint8*>(_v)); break;
        case 45: _t->setChannelGroups_Roll(*reinterpret_cast< quint8*>(_v)); break;
        case 46: _t->setChannelGroups_Pitch(*reinterpret_cast< quint8*>(_v)); break;
        case 47: _t->setChannelGroups_Yaw(*reinterpret_cast< quint8*>(_v)); break;
        case 48: _t->setChannelGroups_FlightMode(*reinterpret_cast< quint8*>(_v)); break;
        case 49: _t->setChannelGroups_Collective(*reinterpret_cast< quint8*>(_v)); break;
        case 50: _t->setChannelGroups_Accessory0(*reinterpret_cast< quint8*>(_v)); break;
        case 51: _t->setChannelGroups_Accessory1(*reinterpret_cast< quint8*>(_v)); break;
        case 52: _t->setChannelGroups_Accessory2(*reinterpret_cast< quint8*>(_v)); break;
        case 53: _t->setChannelNumber_Throttle(*reinterpret_cast< quint8*>(_v)); break;
        case 54: _t->setChannelNumber_Roll(*reinterpret_cast< quint8*>(_v)); break;
        case 55: _t->setChannelNumber_Pitch(*reinterpret_cast< quint8*>(_v)); break;
        case 56: _t->setChannelNumber_Yaw(*reinterpret_cast< quint8*>(_v)); break;
        case 57: _t->setChannelNumber_FlightMode(*reinterpret_cast< quint8*>(_v)); break;
        case 58: _t->setChannelNumber_Collective(*reinterpret_cast< quint8*>(_v)); break;
        case 59: _t->setChannelNumber_Accessory0(*reinterpret_cast< quint8*>(_v)); break;
        case 60: _t->setChannelNumber_Accessory1(*reinterpret_cast< quint8*>(_v)); break;
        case 61: _t->setChannelNumber_Accessory2(*reinterpret_cast< quint8*>(_v)); break;
        case 62: _t->setFlightModeNumber(*reinterpret_cast< quint8*>(_v)); break;
        case 63: _t->setFailsafeFlightModeSwitchPosition(*reinterpret_cast< qint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ManualControlSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_ManualControlSettings.data,
    qt_meta_data_ManualControlSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ManualControlSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ManualControlSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ManualControlSettings.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int ManualControlSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 214)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 214;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 214)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 214;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 64;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 64;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 64;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 64;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 64;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 64;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ManualControlSettings::DeadbandChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ManualControlSettings::DeadbandAssistedControlChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ManualControlSettings::FailsafeChannelChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ManualControlSettings::FailsafeChannel_ThrottleChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ManualControlSettings::FailsafeChannel_RollChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ManualControlSettings::FailsafeChannel_PitchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ManualControlSettings::FailsafeChannel_YawChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ManualControlSettings::FailsafeChannel_CollectiveChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ManualControlSettings::FailsafeChannel_Accessory0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ManualControlSettings::FailsafeChannel_Accessory1Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ManualControlSettings::FailsafeChannel_Accessory2Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ManualControlSettings::ChannelMinChanged(quint32 _t1, qint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ManualControlSettings::ChannelMin_ThrottleChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ManualControlSettings::ChannelMin_RollChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ManualControlSettings::ChannelMin_PitchChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void ManualControlSettings::ChannelMin_YawChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void ManualControlSettings::ChannelMin_FlightModeChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void ManualControlSettings::ChannelMin_CollectiveChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void ManualControlSettings::ChannelMin_Accessory0Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void ManualControlSettings::ChannelMin_Accessory1Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void ManualControlSettings::ChannelMin_Accessory2Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void ManualControlSettings::ChannelNeutralChanged(quint32 _t1, qint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void ManualControlSettings::ChannelNeutral_ThrottleChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void ManualControlSettings::ChannelNeutral_RollChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void ManualControlSettings::ChannelNeutral_PitchChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void ManualControlSettings::ChannelNeutral_YawChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void ManualControlSettings::ChannelNeutral_FlightModeChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void ManualControlSettings::ChannelNeutral_CollectiveChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void ManualControlSettings::ChannelNeutral_Accessory0Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void ManualControlSettings::ChannelNeutral_Accessory1Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void ManualControlSettings::ChannelNeutral_Accessory2Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void ManualControlSettings::ChannelMaxChanged(quint32 _t1, qint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void ManualControlSettings::ChannelMax_ThrottleChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void ManualControlSettings::ChannelMax_RollChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void ManualControlSettings::ChannelMax_PitchChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void ManualControlSettings::ChannelMax_YawChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 35, _a);
}

// SIGNAL 36
void ManualControlSettings::ChannelMax_FlightModeChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 36, _a);
}

// SIGNAL 37
void ManualControlSettings::ChannelMax_CollectiveChanged(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 37, _a);
}

// SIGNAL 38
void ManualControlSettings::ChannelMax_Accessory0Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 38, _a);
}

// SIGNAL 39
void ManualControlSettings::ChannelMax_Accessory1Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 39, _a);
}

// SIGNAL 40
void ManualControlSettings::ChannelMax_Accessory2Changed(qint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 40, _a);
}

// SIGNAL 41
void ManualControlSettings::ResponseTimeChanged(quint32 _t1, quint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 41, _a);
}

// SIGNAL 42
void ManualControlSettings::ResponseTime_RollChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 42, _a);
}

// SIGNAL 43
void ManualControlSettings::ResponseTime_PitchChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 43, _a);
}

// SIGNAL 44
void ManualControlSettings::ResponseTime_YawChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 44, _a);
}

// SIGNAL 45
void ManualControlSettings::ResponseTime_CollectiveChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 45, _a);
}

// SIGNAL 46
void ManualControlSettings::ResponseTime_Accessory0Changed(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 46, _a);
}

// SIGNAL 47
void ManualControlSettings::ResponseTime_Accessory1Changed(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 47, _a);
}

// SIGNAL 48
void ManualControlSettings::ResponseTime_Accessory2Changed(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 48, _a);
}

// SIGNAL 49
void ManualControlSettings::ChannelGroupsChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 49, _a);
}

// SIGNAL 50
void ManualControlSettings::ChannelGroups_ThrottleChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 50, _a);
}

// SIGNAL 51
void ManualControlSettings::ChannelGroups_RollChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 51, _a);
}

// SIGNAL 52
void ManualControlSettings::ChannelGroups_PitchChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 52, _a);
}

// SIGNAL 53
void ManualControlSettings::ChannelGroups_YawChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 53, _a);
}

// SIGNAL 54
void ManualControlSettings::ChannelGroups_FlightModeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 54, _a);
}

// SIGNAL 55
void ManualControlSettings::ChannelGroups_CollectiveChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 55, _a);
}

// SIGNAL 56
void ManualControlSettings::ChannelGroups_Accessory0Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 56, _a);
}

// SIGNAL 57
void ManualControlSettings::ChannelGroups_Accessory1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 57, _a);
}

// SIGNAL 58
void ManualControlSettings::ChannelGroups_Accessory2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 58, _a);
}

// SIGNAL 59
void ManualControlSettings::ChannelNumberChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 59, _a);
}

// SIGNAL 60
void ManualControlSettings::ChannelNumber_ThrottleChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 60, _a);
}

// SIGNAL 61
void ManualControlSettings::ChannelNumber_RollChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 61, _a);
}

// SIGNAL 62
void ManualControlSettings::ChannelNumber_PitchChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 62, _a);
}

// SIGNAL 63
void ManualControlSettings::ChannelNumber_YawChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 63, _a);
}

// SIGNAL 64
void ManualControlSettings::ChannelNumber_FlightModeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 64, _a);
}

// SIGNAL 65
void ManualControlSettings::ChannelNumber_CollectiveChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 65, _a);
}

// SIGNAL 66
void ManualControlSettings::ChannelNumber_Accessory0Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 66, _a);
}

// SIGNAL 67
void ManualControlSettings::ChannelNumber_Accessory1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 67, _a);
}

// SIGNAL 68
void ManualControlSettings::ChannelNumber_Accessory2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 68, _a);
}

// SIGNAL 69
void ManualControlSettings::FlightModeNumberChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 69, _a);
}

// SIGNAL 70
void ManualControlSettings::FailsafeFlightModeSwitchPositionChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 70, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
