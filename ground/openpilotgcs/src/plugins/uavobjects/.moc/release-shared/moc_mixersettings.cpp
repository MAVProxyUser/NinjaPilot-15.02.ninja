/****************************************************************************
** Meta object code from reading C++ file 'mixersettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/mixersettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mixersettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MixerSettings_t {
    QByteArrayData data[407];
    char stringdata0[8960];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MixerSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MixerSettings_t qt_meta_stringdata_MixerSettings = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MixerSettings"
QT_MOC_LITERAL(1, 14, 15), // "MaxAccelChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 5), // "value"
QT_MOC_LITERAL(4, 37, 18), // "FeedForwardChanged"
QT_MOC_LITERAL(5, 56, 16), // "AccelTimeChanged"
QT_MOC_LITERAL(6, 73, 16), // "DecelTimeChanged"
QT_MOC_LITERAL(7, 90, 21), // "ThrottleCurve1Changed"
QT_MOC_LITERAL(8, 112, 5), // "index"
QT_MOC_LITERAL(9, 118, 23), // "ThrottleCurve1_0Changed"
QT_MOC_LITERAL(10, 142, 24), // "ThrottleCurve1_25Changed"
QT_MOC_LITERAL(11, 167, 24), // "ThrottleCurve1_50Changed"
QT_MOC_LITERAL(12, 192, 24), // "ThrottleCurve1_75Changed"
QT_MOC_LITERAL(13, 217, 25), // "ThrottleCurve1_100Changed"
QT_MOC_LITERAL(14, 243, 21), // "ThrottleCurve2Changed"
QT_MOC_LITERAL(15, 265, 23), // "ThrottleCurve2_0Changed"
QT_MOC_LITERAL(16, 289, 24), // "ThrottleCurve2_25Changed"
QT_MOC_LITERAL(17, 314, 24), // "ThrottleCurve2_50Changed"
QT_MOC_LITERAL(18, 339, 24), // "ThrottleCurve2_75Changed"
QT_MOC_LITERAL(19, 364, 25), // "ThrottleCurve2_100Changed"
QT_MOC_LITERAL(20, 390, 21), // "MixerValueRollChanged"
QT_MOC_LITERAL(21, 412, 22), // "MixerValuePitchChanged"
QT_MOC_LITERAL(22, 435, 20), // "MixerValueYawChanged"
QT_MOC_LITERAL(23, 456, 19), // "Curve2SourceChanged"
QT_MOC_LITERAL(24, 476, 17), // "Mixer1TypeChanged"
QT_MOC_LITERAL(25, 494, 19), // "Mixer1VectorChanged"
QT_MOC_LITERAL(26, 514, 34), // "Mixer1Vector_ThrottleCurve1Ch..."
QT_MOC_LITERAL(27, 549, 34), // "Mixer1Vector_ThrottleCurve2Ch..."
QT_MOC_LITERAL(28, 584, 24), // "Mixer1Vector_RollChanged"
QT_MOC_LITERAL(29, 609, 25), // "Mixer1Vector_PitchChanged"
QT_MOC_LITERAL(30, 635, 23), // "Mixer1Vector_YawChanged"
QT_MOC_LITERAL(31, 659, 17), // "Mixer2TypeChanged"
QT_MOC_LITERAL(32, 677, 19), // "Mixer2VectorChanged"
QT_MOC_LITERAL(33, 697, 34), // "Mixer2Vector_ThrottleCurve1Ch..."
QT_MOC_LITERAL(34, 732, 34), // "Mixer2Vector_ThrottleCurve2Ch..."
QT_MOC_LITERAL(35, 767, 24), // "Mixer2Vector_RollChanged"
QT_MOC_LITERAL(36, 792, 25), // "Mixer2Vector_PitchChanged"
QT_MOC_LITERAL(37, 818, 23), // "Mixer2Vector_YawChanged"
QT_MOC_LITERAL(38, 842, 17), // "Mixer3TypeChanged"
QT_MOC_LITERAL(39, 860, 19), // "Mixer3VectorChanged"
QT_MOC_LITERAL(40, 880, 34), // "Mixer3Vector_ThrottleCurve1Ch..."
QT_MOC_LITERAL(41, 915, 34), // "Mixer3Vector_ThrottleCurve2Ch..."
QT_MOC_LITERAL(42, 950, 24), // "Mixer3Vector_RollChanged"
QT_MOC_LITERAL(43, 975, 25), // "Mixer3Vector_PitchChanged"
QT_MOC_LITERAL(44, 1001, 23), // "Mixer3Vector_YawChanged"
QT_MOC_LITERAL(45, 1025, 17), // "Mixer4TypeChanged"
QT_MOC_LITERAL(46, 1043, 19), // "Mixer4VectorChanged"
QT_MOC_LITERAL(47, 1063, 34), // "Mixer4Vector_ThrottleCurve1Ch..."
QT_MOC_LITERAL(48, 1098, 34), // "Mixer4Vector_ThrottleCurve2Ch..."
QT_MOC_LITERAL(49, 1133, 24), // "Mixer4Vector_RollChanged"
QT_MOC_LITERAL(50, 1158, 25), // "Mixer4Vector_PitchChanged"
QT_MOC_LITERAL(51, 1184, 23), // "Mixer4Vector_YawChanged"
QT_MOC_LITERAL(52, 1208, 17), // "Mixer5TypeChanged"
QT_MOC_LITERAL(53, 1226, 19), // "Mixer5VectorChanged"
QT_MOC_LITERAL(54, 1246, 34), // "Mixer5Vector_ThrottleCurve1Ch..."
QT_MOC_LITERAL(55, 1281, 34), // "Mixer5Vector_ThrottleCurve2Ch..."
QT_MOC_LITERAL(56, 1316, 24), // "Mixer5Vector_RollChanged"
QT_MOC_LITERAL(57, 1341, 25), // "Mixer5Vector_PitchChanged"
QT_MOC_LITERAL(58, 1367, 23), // "Mixer5Vector_YawChanged"
QT_MOC_LITERAL(59, 1391, 17), // "Mixer6TypeChanged"
QT_MOC_LITERAL(60, 1409, 19), // "Mixer6VectorChanged"
QT_MOC_LITERAL(61, 1429, 34), // "Mixer6Vector_ThrottleCurve1Ch..."
QT_MOC_LITERAL(62, 1464, 34), // "Mixer6Vector_ThrottleCurve2Ch..."
QT_MOC_LITERAL(63, 1499, 24), // "Mixer6Vector_RollChanged"
QT_MOC_LITERAL(64, 1524, 25), // "Mixer6Vector_PitchChanged"
QT_MOC_LITERAL(65, 1550, 23), // "Mixer6Vector_YawChanged"
QT_MOC_LITERAL(66, 1574, 17), // "Mixer7TypeChanged"
QT_MOC_LITERAL(67, 1592, 19), // "Mixer7VectorChanged"
QT_MOC_LITERAL(68, 1612, 34), // "Mixer7Vector_ThrottleCurve1Ch..."
QT_MOC_LITERAL(69, 1647, 34), // "Mixer7Vector_ThrottleCurve2Ch..."
QT_MOC_LITERAL(70, 1682, 24), // "Mixer7Vector_RollChanged"
QT_MOC_LITERAL(71, 1707, 25), // "Mixer7Vector_PitchChanged"
QT_MOC_LITERAL(72, 1733, 23), // "Mixer7Vector_YawChanged"
QT_MOC_LITERAL(73, 1757, 17), // "Mixer8TypeChanged"
QT_MOC_LITERAL(74, 1775, 19), // "Mixer8VectorChanged"
QT_MOC_LITERAL(75, 1795, 34), // "Mixer8Vector_ThrottleCurve1Ch..."
QT_MOC_LITERAL(76, 1830, 34), // "Mixer8Vector_ThrottleCurve2Ch..."
QT_MOC_LITERAL(77, 1865, 24), // "Mixer8Vector_RollChanged"
QT_MOC_LITERAL(78, 1890, 25), // "Mixer8Vector_PitchChanged"
QT_MOC_LITERAL(79, 1916, 23), // "Mixer8Vector_YawChanged"
QT_MOC_LITERAL(80, 1940, 17), // "Mixer9TypeChanged"
QT_MOC_LITERAL(81, 1958, 19), // "Mixer9VectorChanged"
QT_MOC_LITERAL(82, 1978, 34), // "Mixer9Vector_ThrottleCurve1Ch..."
QT_MOC_LITERAL(83, 2013, 34), // "Mixer9Vector_ThrottleCurve2Ch..."
QT_MOC_LITERAL(84, 2048, 24), // "Mixer9Vector_RollChanged"
QT_MOC_LITERAL(85, 2073, 25), // "Mixer9Vector_PitchChanged"
QT_MOC_LITERAL(86, 2099, 23), // "Mixer9Vector_YawChanged"
QT_MOC_LITERAL(87, 2123, 18), // "Mixer10TypeChanged"
QT_MOC_LITERAL(88, 2142, 20), // "Mixer10VectorChanged"
QT_MOC_LITERAL(89, 2163, 35), // "Mixer10Vector_ThrottleCurve1C..."
QT_MOC_LITERAL(90, 2199, 35), // "Mixer10Vector_ThrottleCurve2C..."
QT_MOC_LITERAL(91, 2235, 25), // "Mixer10Vector_RollChanged"
QT_MOC_LITERAL(92, 2261, 26), // "Mixer10Vector_PitchChanged"
QT_MOC_LITERAL(93, 2288, 24), // "Mixer10Vector_YawChanged"
QT_MOC_LITERAL(94, 2313, 18), // "Mixer11TypeChanged"
QT_MOC_LITERAL(95, 2332, 20), // "Mixer11VectorChanged"
QT_MOC_LITERAL(96, 2353, 35), // "Mixer11Vector_ThrottleCurve1C..."
QT_MOC_LITERAL(97, 2389, 35), // "Mixer11Vector_ThrottleCurve2C..."
QT_MOC_LITERAL(98, 2425, 25), // "Mixer11Vector_RollChanged"
QT_MOC_LITERAL(99, 2451, 26), // "Mixer11Vector_PitchChanged"
QT_MOC_LITERAL(100, 2478, 24), // "Mixer11Vector_YawChanged"
QT_MOC_LITERAL(101, 2503, 18), // "Mixer12TypeChanged"
QT_MOC_LITERAL(102, 2522, 20), // "Mixer12VectorChanged"
QT_MOC_LITERAL(103, 2543, 35), // "Mixer12Vector_ThrottleCurve1C..."
QT_MOC_LITERAL(104, 2579, 35), // "Mixer12Vector_ThrottleCurve2C..."
QT_MOC_LITERAL(105, 2615, 25), // "Mixer12Vector_RollChanged"
QT_MOC_LITERAL(106, 2641, 26), // "Mixer12Vector_PitchChanged"
QT_MOC_LITERAL(107, 2668, 24), // "Mixer12Vector_YawChanged"
QT_MOC_LITERAL(108, 2693, 11), // "setMaxAccel"
QT_MOC_LITERAL(109, 2705, 14), // "setFeedForward"
QT_MOC_LITERAL(110, 2720, 12), // "setAccelTime"
QT_MOC_LITERAL(111, 2733, 12), // "setDecelTime"
QT_MOC_LITERAL(112, 2746, 17), // "setThrottleCurve1"
QT_MOC_LITERAL(113, 2764, 19), // "setThrottleCurve1_0"
QT_MOC_LITERAL(114, 2784, 20), // "setThrottleCurve1_25"
QT_MOC_LITERAL(115, 2805, 20), // "setThrottleCurve1_50"
QT_MOC_LITERAL(116, 2826, 20), // "setThrottleCurve1_75"
QT_MOC_LITERAL(117, 2847, 21), // "setThrottleCurve1_100"
QT_MOC_LITERAL(118, 2869, 17), // "setThrottleCurve2"
QT_MOC_LITERAL(119, 2887, 19), // "setThrottleCurve2_0"
QT_MOC_LITERAL(120, 2907, 20), // "setThrottleCurve2_25"
QT_MOC_LITERAL(121, 2928, 20), // "setThrottleCurve2_50"
QT_MOC_LITERAL(122, 2949, 20), // "setThrottleCurve2_75"
QT_MOC_LITERAL(123, 2970, 21), // "setThrottleCurve2_100"
QT_MOC_LITERAL(124, 2992, 17), // "setMixerValueRoll"
QT_MOC_LITERAL(125, 3010, 18), // "setMixerValuePitch"
QT_MOC_LITERAL(126, 3029, 16), // "setMixerValueYaw"
QT_MOC_LITERAL(127, 3046, 15), // "setCurve2Source"
QT_MOC_LITERAL(128, 3062, 13), // "setMixer1Type"
QT_MOC_LITERAL(129, 3076, 15), // "setMixer1Vector"
QT_MOC_LITERAL(130, 3092, 30), // "setMixer1Vector_ThrottleCurve1"
QT_MOC_LITERAL(131, 3123, 30), // "setMixer1Vector_ThrottleCurve2"
QT_MOC_LITERAL(132, 3154, 20), // "setMixer1Vector_Roll"
QT_MOC_LITERAL(133, 3175, 21), // "setMixer1Vector_Pitch"
QT_MOC_LITERAL(134, 3197, 19), // "setMixer1Vector_Yaw"
QT_MOC_LITERAL(135, 3217, 13), // "setMixer2Type"
QT_MOC_LITERAL(136, 3231, 15), // "setMixer2Vector"
QT_MOC_LITERAL(137, 3247, 30), // "setMixer2Vector_ThrottleCurve1"
QT_MOC_LITERAL(138, 3278, 30), // "setMixer2Vector_ThrottleCurve2"
QT_MOC_LITERAL(139, 3309, 20), // "setMixer2Vector_Roll"
QT_MOC_LITERAL(140, 3330, 21), // "setMixer2Vector_Pitch"
QT_MOC_LITERAL(141, 3352, 19), // "setMixer2Vector_Yaw"
QT_MOC_LITERAL(142, 3372, 13), // "setMixer3Type"
QT_MOC_LITERAL(143, 3386, 15), // "setMixer3Vector"
QT_MOC_LITERAL(144, 3402, 30), // "setMixer3Vector_ThrottleCurve1"
QT_MOC_LITERAL(145, 3433, 30), // "setMixer3Vector_ThrottleCurve2"
QT_MOC_LITERAL(146, 3464, 20), // "setMixer3Vector_Roll"
QT_MOC_LITERAL(147, 3485, 21), // "setMixer3Vector_Pitch"
QT_MOC_LITERAL(148, 3507, 19), // "setMixer3Vector_Yaw"
QT_MOC_LITERAL(149, 3527, 13), // "setMixer4Type"
QT_MOC_LITERAL(150, 3541, 15), // "setMixer4Vector"
QT_MOC_LITERAL(151, 3557, 30), // "setMixer4Vector_ThrottleCurve1"
QT_MOC_LITERAL(152, 3588, 30), // "setMixer4Vector_ThrottleCurve2"
QT_MOC_LITERAL(153, 3619, 20), // "setMixer4Vector_Roll"
QT_MOC_LITERAL(154, 3640, 21), // "setMixer4Vector_Pitch"
QT_MOC_LITERAL(155, 3662, 19), // "setMixer4Vector_Yaw"
QT_MOC_LITERAL(156, 3682, 13), // "setMixer5Type"
QT_MOC_LITERAL(157, 3696, 15), // "setMixer5Vector"
QT_MOC_LITERAL(158, 3712, 30), // "setMixer5Vector_ThrottleCurve1"
QT_MOC_LITERAL(159, 3743, 30), // "setMixer5Vector_ThrottleCurve2"
QT_MOC_LITERAL(160, 3774, 20), // "setMixer5Vector_Roll"
QT_MOC_LITERAL(161, 3795, 21), // "setMixer5Vector_Pitch"
QT_MOC_LITERAL(162, 3817, 19), // "setMixer5Vector_Yaw"
QT_MOC_LITERAL(163, 3837, 13), // "setMixer6Type"
QT_MOC_LITERAL(164, 3851, 15), // "setMixer6Vector"
QT_MOC_LITERAL(165, 3867, 30), // "setMixer6Vector_ThrottleCurve1"
QT_MOC_LITERAL(166, 3898, 30), // "setMixer6Vector_ThrottleCurve2"
QT_MOC_LITERAL(167, 3929, 20), // "setMixer6Vector_Roll"
QT_MOC_LITERAL(168, 3950, 21), // "setMixer6Vector_Pitch"
QT_MOC_LITERAL(169, 3972, 19), // "setMixer6Vector_Yaw"
QT_MOC_LITERAL(170, 3992, 13), // "setMixer7Type"
QT_MOC_LITERAL(171, 4006, 15), // "setMixer7Vector"
QT_MOC_LITERAL(172, 4022, 30), // "setMixer7Vector_ThrottleCurve1"
QT_MOC_LITERAL(173, 4053, 30), // "setMixer7Vector_ThrottleCurve2"
QT_MOC_LITERAL(174, 4084, 20), // "setMixer7Vector_Roll"
QT_MOC_LITERAL(175, 4105, 21), // "setMixer7Vector_Pitch"
QT_MOC_LITERAL(176, 4127, 19), // "setMixer7Vector_Yaw"
QT_MOC_LITERAL(177, 4147, 13), // "setMixer8Type"
QT_MOC_LITERAL(178, 4161, 15), // "setMixer8Vector"
QT_MOC_LITERAL(179, 4177, 30), // "setMixer8Vector_ThrottleCurve1"
QT_MOC_LITERAL(180, 4208, 30), // "setMixer8Vector_ThrottleCurve2"
QT_MOC_LITERAL(181, 4239, 20), // "setMixer8Vector_Roll"
QT_MOC_LITERAL(182, 4260, 21), // "setMixer8Vector_Pitch"
QT_MOC_LITERAL(183, 4282, 19), // "setMixer8Vector_Yaw"
QT_MOC_LITERAL(184, 4302, 13), // "setMixer9Type"
QT_MOC_LITERAL(185, 4316, 15), // "setMixer9Vector"
QT_MOC_LITERAL(186, 4332, 30), // "setMixer9Vector_ThrottleCurve1"
QT_MOC_LITERAL(187, 4363, 30), // "setMixer9Vector_ThrottleCurve2"
QT_MOC_LITERAL(188, 4394, 20), // "setMixer9Vector_Roll"
QT_MOC_LITERAL(189, 4415, 21), // "setMixer9Vector_Pitch"
QT_MOC_LITERAL(190, 4437, 19), // "setMixer9Vector_Yaw"
QT_MOC_LITERAL(191, 4457, 14), // "setMixer10Type"
QT_MOC_LITERAL(192, 4472, 16), // "setMixer10Vector"
QT_MOC_LITERAL(193, 4489, 31), // "setMixer10Vector_ThrottleCurve1"
QT_MOC_LITERAL(194, 4521, 31), // "setMixer10Vector_ThrottleCurve2"
QT_MOC_LITERAL(195, 4553, 21), // "setMixer10Vector_Roll"
QT_MOC_LITERAL(196, 4575, 22), // "setMixer10Vector_Pitch"
QT_MOC_LITERAL(197, 4598, 20), // "setMixer10Vector_Yaw"
QT_MOC_LITERAL(198, 4619, 14), // "setMixer11Type"
QT_MOC_LITERAL(199, 4634, 16), // "setMixer11Vector"
QT_MOC_LITERAL(200, 4651, 31), // "setMixer11Vector_ThrottleCurve1"
QT_MOC_LITERAL(201, 4683, 31), // "setMixer11Vector_ThrottleCurve2"
QT_MOC_LITERAL(202, 4715, 21), // "setMixer11Vector_Roll"
QT_MOC_LITERAL(203, 4737, 22), // "setMixer11Vector_Pitch"
QT_MOC_LITERAL(204, 4760, 20), // "setMixer11Vector_Yaw"
QT_MOC_LITERAL(205, 4781, 14), // "setMixer12Type"
QT_MOC_LITERAL(206, 4796, 16), // "setMixer12Vector"
QT_MOC_LITERAL(207, 4813, 31), // "setMixer12Vector_ThrottleCurve1"
QT_MOC_LITERAL(208, 4845, 31), // "setMixer12Vector_ThrottleCurve2"
QT_MOC_LITERAL(209, 4877, 21), // "setMixer12Vector_Roll"
QT_MOC_LITERAL(210, 4899, 22), // "setMixer12Vector_Pitch"
QT_MOC_LITERAL(211, 4922, 20), // "setMixer12Vector_Yaw"
QT_MOC_LITERAL(212, 4943, 17), // "emitNotifications"
QT_MOC_LITERAL(213, 4961, 11), // "getMaxAccel"
QT_MOC_LITERAL(214, 4973, 14), // "getFeedForward"
QT_MOC_LITERAL(215, 4988, 12), // "getAccelTime"
QT_MOC_LITERAL(216, 5001, 12), // "getDecelTime"
QT_MOC_LITERAL(217, 5014, 17), // "getThrottleCurve1"
QT_MOC_LITERAL(218, 5032, 19), // "getThrottleCurve1_0"
QT_MOC_LITERAL(219, 5052, 20), // "getThrottleCurve1_25"
QT_MOC_LITERAL(220, 5073, 20), // "getThrottleCurve1_50"
QT_MOC_LITERAL(221, 5094, 20), // "getThrottleCurve1_75"
QT_MOC_LITERAL(222, 5115, 21), // "getThrottleCurve1_100"
QT_MOC_LITERAL(223, 5137, 17), // "getThrottleCurve2"
QT_MOC_LITERAL(224, 5155, 19), // "getThrottleCurve2_0"
QT_MOC_LITERAL(225, 5175, 20), // "getThrottleCurve2_25"
QT_MOC_LITERAL(226, 5196, 20), // "getThrottleCurve2_50"
QT_MOC_LITERAL(227, 5217, 20), // "getThrottleCurve2_75"
QT_MOC_LITERAL(228, 5238, 21), // "getThrottleCurve2_100"
QT_MOC_LITERAL(229, 5260, 17), // "getMixerValueRoll"
QT_MOC_LITERAL(230, 5278, 18), // "getMixerValuePitch"
QT_MOC_LITERAL(231, 5297, 16), // "getMixerValueYaw"
QT_MOC_LITERAL(232, 5314, 15), // "getCurve2Source"
QT_MOC_LITERAL(233, 5330, 13), // "getMixer1Type"
QT_MOC_LITERAL(234, 5344, 15), // "getMixer1Vector"
QT_MOC_LITERAL(235, 5360, 30), // "getMixer1Vector_ThrottleCurve1"
QT_MOC_LITERAL(236, 5391, 30), // "getMixer1Vector_ThrottleCurve2"
QT_MOC_LITERAL(237, 5422, 20), // "getMixer1Vector_Roll"
QT_MOC_LITERAL(238, 5443, 21), // "getMixer1Vector_Pitch"
QT_MOC_LITERAL(239, 5465, 19), // "getMixer1Vector_Yaw"
QT_MOC_LITERAL(240, 5485, 13), // "getMixer2Type"
QT_MOC_LITERAL(241, 5499, 15), // "getMixer2Vector"
QT_MOC_LITERAL(242, 5515, 30), // "getMixer2Vector_ThrottleCurve1"
QT_MOC_LITERAL(243, 5546, 30), // "getMixer2Vector_ThrottleCurve2"
QT_MOC_LITERAL(244, 5577, 20), // "getMixer2Vector_Roll"
QT_MOC_LITERAL(245, 5598, 21), // "getMixer2Vector_Pitch"
QT_MOC_LITERAL(246, 5620, 19), // "getMixer2Vector_Yaw"
QT_MOC_LITERAL(247, 5640, 13), // "getMixer3Type"
QT_MOC_LITERAL(248, 5654, 15), // "getMixer3Vector"
QT_MOC_LITERAL(249, 5670, 30), // "getMixer3Vector_ThrottleCurve1"
QT_MOC_LITERAL(250, 5701, 30), // "getMixer3Vector_ThrottleCurve2"
QT_MOC_LITERAL(251, 5732, 20), // "getMixer3Vector_Roll"
QT_MOC_LITERAL(252, 5753, 21), // "getMixer3Vector_Pitch"
QT_MOC_LITERAL(253, 5775, 19), // "getMixer3Vector_Yaw"
QT_MOC_LITERAL(254, 5795, 13), // "getMixer4Type"
QT_MOC_LITERAL(255, 5809, 15), // "getMixer4Vector"
QT_MOC_LITERAL(256, 5825, 30), // "getMixer4Vector_ThrottleCurve1"
QT_MOC_LITERAL(257, 5856, 30), // "getMixer4Vector_ThrottleCurve2"
QT_MOC_LITERAL(258, 5887, 20), // "getMixer4Vector_Roll"
QT_MOC_LITERAL(259, 5908, 21), // "getMixer4Vector_Pitch"
QT_MOC_LITERAL(260, 5930, 19), // "getMixer4Vector_Yaw"
QT_MOC_LITERAL(261, 5950, 13), // "getMixer5Type"
QT_MOC_LITERAL(262, 5964, 15), // "getMixer5Vector"
QT_MOC_LITERAL(263, 5980, 30), // "getMixer5Vector_ThrottleCurve1"
QT_MOC_LITERAL(264, 6011, 30), // "getMixer5Vector_ThrottleCurve2"
QT_MOC_LITERAL(265, 6042, 20), // "getMixer5Vector_Roll"
QT_MOC_LITERAL(266, 6063, 21), // "getMixer5Vector_Pitch"
QT_MOC_LITERAL(267, 6085, 19), // "getMixer5Vector_Yaw"
QT_MOC_LITERAL(268, 6105, 13), // "getMixer6Type"
QT_MOC_LITERAL(269, 6119, 15), // "getMixer6Vector"
QT_MOC_LITERAL(270, 6135, 30), // "getMixer6Vector_ThrottleCurve1"
QT_MOC_LITERAL(271, 6166, 30), // "getMixer6Vector_ThrottleCurve2"
QT_MOC_LITERAL(272, 6197, 20), // "getMixer6Vector_Roll"
QT_MOC_LITERAL(273, 6218, 21), // "getMixer6Vector_Pitch"
QT_MOC_LITERAL(274, 6240, 19), // "getMixer6Vector_Yaw"
QT_MOC_LITERAL(275, 6260, 13), // "getMixer7Type"
QT_MOC_LITERAL(276, 6274, 15), // "getMixer7Vector"
QT_MOC_LITERAL(277, 6290, 30), // "getMixer7Vector_ThrottleCurve1"
QT_MOC_LITERAL(278, 6321, 30), // "getMixer7Vector_ThrottleCurve2"
QT_MOC_LITERAL(279, 6352, 20), // "getMixer7Vector_Roll"
QT_MOC_LITERAL(280, 6373, 21), // "getMixer7Vector_Pitch"
QT_MOC_LITERAL(281, 6395, 19), // "getMixer7Vector_Yaw"
QT_MOC_LITERAL(282, 6415, 13), // "getMixer8Type"
QT_MOC_LITERAL(283, 6429, 15), // "getMixer8Vector"
QT_MOC_LITERAL(284, 6445, 30), // "getMixer8Vector_ThrottleCurve1"
QT_MOC_LITERAL(285, 6476, 30), // "getMixer8Vector_ThrottleCurve2"
QT_MOC_LITERAL(286, 6507, 20), // "getMixer8Vector_Roll"
QT_MOC_LITERAL(287, 6528, 21), // "getMixer8Vector_Pitch"
QT_MOC_LITERAL(288, 6550, 19), // "getMixer8Vector_Yaw"
QT_MOC_LITERAL(289, 6570, 13), // "getMixer9Type"
QT_MOC_LITERAL(290, 6584, 15), // "getMixer9Vector"
QT_MOC_LITERAL(291, 6600, 30), // "getMixer9Vector_ThrottleCurve1"
QT_MOC_LITERAL(292, 6631, 30), // "getMixer9Vector_ThrottleCurve2"
QT_MOC_LITERAL(293, 6662, 20), // "getMixer9Vector_Roll"
QT_MOC_LITERAL(294, 6683, 21), // "getMixer9Vector_Pitch"
QT_MOC_LITERAL(295, 6705, 19), // "getMixer9Vector_Yaw"
QT_MOC_LITERAL(296, 6725, 14), // "getMixer10Type"
QT_MOC_LITERAL(297, 6740, 16), // "getMixer10Vector"
QT_MOC_LITERAL(298, 6757, 31), // "getMixer10Vector_ThrottleCurve1"
QT_MOC_LITERAL(299, 6789, 31), // "getMixer10Vector_ThrottleCurve2"
QT_MOC_LITERAL(300, 6821, 21), // "getMixer10Vector_Roll"
QT_MOC_LITERAL(301, 6843, 22), // "getMixer10Vector_Pitch"
QT_MOC_LITERAL(302, 6866, 20), // "getMixer10Vector_Yaw"
QT_MOC_LITERAL(303, 6887, 14), // "getMixer11Type"
QT_MOC_LITERAL(304, 6902, 16), // "getMixer11Vector"
QT_MOC_LITERAL(305, 6919, 31), // "getMixer11Vector_ThrottleCurve1"
QT_MOC_LITERAL(306, 6951, 31), // "getMixer11Vector_ThrottleCurve2"
QT_MOC_LITERAL(307, 6983, 21), // "getMixer11Vector_Roll"
QT_MOC_LITERAL(308, 7005, 22), // "getMixer11Vector_Pitch"
QT_MOC_LITERAL(309, 7028, 20), // "getMixer11Vector_Yaw"
QT_MOC_LITERAL(310, 7049, 14), // "getMixer12Type"
QT_MOC_LITERAL(311, 7064, 16), // "getMixer12Vector"
QT_MOC_LITERAL(312, 7081, 31), // "getMixer12Vector_ThrottleCurve1"
QT_MOC_LITERAL(313, 7113, 31), // "getMixer12Vector_ThrottleCurve2"
QT_MOC_LITERAL(314, 7145, 21), // "getMixer12Vector_Roll"
QT_MOC_LITERAL(315, 7167, 22), // "getMixer12Vector_Pitch"
QT_MOC_LITERAL(316, 7190, 20), // "getMixer12Vector_Yaw"
QT_MOC_LITERAL(317, 7211, 8), // "MaxAccel"
QT_MOC_LITERAL(318, 7220, 11), // "FeedForward"
QT_MOC_LITERAL(319, 7232, 9), // "AccelTime"
QT_MOC_LITERAL(320, 7242, 9), // "DecelTime"
QT_MOC_LITERAL(321, 7252, 16), // "ThrottleCurve1_0"
QT_MOC_LITERAL(322, 7269, 17), // "ThrottleCurve1_25"
QT_MOC_LITERAL(323, 7287, 17), // "ThrottleCurve1_50"
QT_MOC_LITERAL(324, 7305, 17), // "ThrottleCurve1_75"
QT_MOC_LITERAL(325, 7323, 18), // "ThrottleCurve1_100"
QT_MOC_LITERAL(326, 7342, 16), // "ThrottleCurve2_0"
QT_MOC_LITERAL(327, 7359, 17), // "ThrottleCurve2_25"
QT_MOC_LITERAL(328, 7377, 17), // "ThrottleCurve2_50"
QT_MOC_LITERAL(329, 7395, 17), // "ThrottleCurve2_75"
QT_MOC_LITERAL(330, 7413, 18), // "ThrottleCurve2_100"
QT_MOC_LITERAL(331, 7432, 14), // "MixerValueRoll"
QT_MOC_LITERAL(332, 7447, 15), // "MixerValuePitch"
QT_MOC_LITERAL(333, 7463, 13), // "MixerValueYaw"
QT_MOC_LITERAL(334, 7477, 12), // "Curve2Source"
QT_MOC_LITERAL(335, 7490, 10), // "Mixer1Type"
QT_MOC_LITERAL(336, 7501, 27), // "Mixer1Vector_ThrottleCurve1"
QT_MOC_LITERAL(337, 7529, 27), // "Mixer1Vector_ThrottleCurve2"
QT_MOC_LITERAL(338, 7557, 17), // "Mixer1Vector_Roll"
QT_MOC_LITERAL(339, 7575, 18), // "Mixer1Vector_Pitch"
QT_MOC_LITERAL(340, 7594, 16), // "Mixer1Vector_Yaw"
QT_MOC_LITERAL(341, 7611, 10), // "Mixer2Type"
QT_MOC_LITERAL(342, 7622, 27), // "Mixer2Vector_ThrottleCurve1"
QT_MOC_LITERAL(343, 7650, 27), // "Mixer2Vector_ThrottleCurve2"
QT_MOC_LITERAL(344, 7678, 17), // "Mixer2Vector_Roll"
QT_MOC_LITERAL(345, 7696, 18), // "Mixer2Vector_Pitch"
QT_MOC_LITERAL(346, 7715, 16), // "Mixer2Vector_Yaw"
QT_MOC_LITERAL(347, 7732, 10), // "Mixer3Type"
QT_MOC_LITERAL(348, 7743, 27), // "Mixer3Vector_ThrottleCurve1"
QT_MOC_LITERAL(349, 7771, 27), // "Mixer3Vector_ThrottleCurve2"
QT_MOC_LITERAL(350, 7799, 17), // "Mixer3Vector_Roll"
QT_MOC_LITERAL(351, 7817, 18), // "Mixer3Vector_Pitch"
QT_MOC_LITERAL(352, 7836, 16), // "Mixer3Vector_Yaw"
QT_MOC_LITERAL(353, 7853, 10), // "Mixer4Type"
QT_MOC_LITERAL(354, 7864, 27), // "Mixer4Vector_ThrottleCurve1"
QT_MOC_LITERAL(355, 7892, 27), // "Mixer4Vector_ThrottleCurve2"
QT_MOC_LITERAL(356, 7920, 17), // "Mixer4Vector_Roll"
QT_MOC_LITERAL(357, 7938, 18), // "Mixer4Vector_Pitch"
QT_MOC_LITERAL(358, 7957, 16), // "Mixer4Vector_Yaw"
QT_MOC_LITERAL(359, 7974, 10), // "Mixer5Type"
QT_MOC_LITERAL(360, 7985, 27), // "Mixer5Vector_ThrottleCurve1"
QT_MOC_LITERAL(361, 8013, 27), // "Mixer5Vector_ThrottleCurve2"
QT_MOC_LITERAL(362, 8041, 17), // "Mixer5Vector_Roll"
QT_MOC_LITERAL(363, 8059, 18), // "Mixer5Vector_Pitch"
QT_MOC_LITERAL(364, 8078, 16), // "Mixer5Vector_Yaw"
QT_MOC_LITERAL(365, 8095, 10), // "Mixer6Type"
QT_MOC_LITERAL(366, 8106, 27), // "Mixer6Vector_ThrottleCurve1"
QT_MOC_LITERAL(367, 8134, 27), // "Mixer6Vector_ThrottleCurve2"
QT_MOC_LITERAL(368, 8162, 17), // "Mixer6Vector_Roll"
QT_MOC_LITERAL(369, 8180, 18), // "Mixer6Vector_Pitch"
QT_MOC_LITERAL(370, 8199, 16), // "Mixer6Vector_Yaw"
QT_MOC_LITERAL(371, 8216, 10), // "Mixer7Type"
QT_MOC_LITERAL(372, 8227, 27), // "Mixer7Vector_ThrottleCurve1"
QT_MOC_LITERAL(373, 8255, 27), // "Mixer7Vector_ThrottleCurve2"
QT_MOC_LITERAL(374, 8283, 17), // "Mixer7Vector_Roll"
QT_MOC_LITERAL(375, 8301, 18), // "Mixer7Vector_Pitch"
QT_MOC_LITERAL(376, 8320, 16), // "Mixer7Vector_Yaw"
QT_MOC_LITERAL(377, 8337, 10), // "Mixer8Type"
QT_MOC_LITERAL(378, 8348, 27), // "Mixer8Vector_ThrottleCurve1"
QT_MOC_LITERAL(379, 8376, 27), // "Mixer8Vector_ThrottleCurve2"
QT_MOC_LITERAL(380, 8404, 17), // "Mixer8Vector_Roll"
QT_MOC_LITERAL(381, 8422, 18), // "Mixer8Vector_Pitch"
QT_MOC_LITERAL(382, 8441, 16), // "Mixer8Vector_Yaw"
QT_MOC_LITERAL(383, 8458, 10), // "Mixer9Type"
QT_MOC_LITERAL(384, 8469, 27), // "Mixer9Vector_ThrottleCurve1"
QT_MOC_LITERAL(385, 8497, 27), // "Mixer9Vector_ThrottleCurve2"
QT_MOC_LITERAL(386, 8525, 17), // "Mixer9Vector_Roll"
QT_MOC_LITERAL(387, 8543, 18), // "Mixer9Vector_Pitch"
QT_MOC_LITERAL(388, 8562, 16), // "Mixer9Vector_Yaw"
QT_MOC_LITERAL(389, 8579, 11), // "Mixer10Type"
QT_MOC_LITERAL(390, 8591, 28), // "Mixer10Vector_ThrottleCurve1"
QT_MOC_LITERAL(391, 8620, 28), // "Mixer10Vector_ThrottleCurve2"
QT_MOC_LITERAL(392, 8649, 18), // "Mixer10Vector_Roll"
QT_MOC_LITERAL(393, 8668, 19), // "Mixer10Vector_Pitch"
QT_MOC_LITERAL(394, 8688, 17), // "Mixer10Vector_Yaw"
QT_MOC_LITERAL(395, 8706, 11), // "Mixer11Type"
QT_MOC_LITERAL(396, 8718, 28), // "Mixer11Vector_ThrottleCurve1"
QT_MOC_LITERAL(397, 8747, 28), // "Mixer11Vector_ThrottleCurve2"
QT_MOC_LITERAL(398, 8776, 18), // "Mixer11Vector_Roll"
QT_MOC_LITERAL(399, 8795, 19), // "Mixer11Vector_Pitch"
QT_MOC_LITERAL(400, 8815, 17), // "Mixer11Vector_Yaw"
QT_MOC_LITERAL(401, 8833, 11), // "Mixer12Type"
QT_MOC_LITERAL(402, 8845, 28), // "Mixer12Vector_ThrottleCurve1"
QT_MOC_LITERAL(403, 8874, 28), // "Mixer12Vector_ThrottleCurve2"
QT_MOC_LITERAL(404, 8903, 18), // "Mixer12Vector_Roll"
QT_MOC_LITERAL(405, 8922, 19), // "Mixer12Vector_Pitch"
QT_MOC_LITERAL(406, 8942, 17) // "Mixer12Vector_Yaw"

    },
    "MixerSettings\0MaxAccelChanged\0\0value\0"
    "FeedForwardChanged\0AccelTimeChanged\0"
    "DecelTimeChanged\0ThrottleCurve1Changed\0"
    "index\0ThrottleCurve1_0Changed\0"
    "ThrottleCurve1_25Changed\0"
    "ThrottleCurve1_50Changed\0"
    "ThrottleCurve1_75Changed\0"
    "ThrottleCurve1_100Changed\0"
    "ThrottleCurve2Changed\0ThrottleCurve2_0Changed\0"
    "ThrottleCurve2_25Changed\0"
    "ThrottleCurve2_50Changed\0"
    "ThrottleCurve2_75Changed\0"
    "ThrottleCurve2_100Changed\0"
    "MixerValueRollChanged\0MixerValuePitchChanged\0"
    "MixerValueYawChanged\0Curve2SourceChanged\0"
    "Mixer1TypeChanged\0Mixer1VectorChanged\0"
    "Mixer1Vector_ThrottleCurve1Changed\0"
    "Mixer1Vector_ThrottleCurve2Changed\0"
    "Mixer1Vector_RollChanged\0"
    "Mixer1Vector_PitchChanged\0"
    "Mixer1Vector_YawChanged\0Mixer2TypeChanged\0"
    "Mixer2VectorChanged\0"
    "Mixer2Vector_ThrottleCurve1Changed\0"
    "Mixer2Vector_ThrottleCurve2Changed\0"
    "Mixer2Vector_RollChanged\0"
    "Mixer2Vector_PitchChanged\0"
    "Mixer2Vector_YawChanged\0Mixer3TypeChanged\0"
    "Mixer3VectorChanged\0"
    "Mixer3Vector_ThrottleCurve1Changed\0"
    "Mixer3Vector_ThrottleCurve2Changed\0"
    "Mixer3Vector_RollChanged\0"
    "Mixer3Vector_PitchChanged\0"
    "Mixer3Vector_YawChanged\0Mixer4TypeChanged\0"
    "Mixer4VectorChanged\0"
    "Mixer4Vector_ThrottleCurve1Changed\0"
    "Mixer4Vector_ThrottleCurve2Changed\0"
    "Mixer4Vector_RollChanged\0"
    "Mixer4Vector_PitchChanged\0"
    "Mixer4Vector_YawChanged\0Mixer5TypeChanged\0"
    "Mixer5VectorChanged\0"
    "Mixer5Vector_ThrottleCurve1Changed\0"
    "Mixer5Vector_ThrottleCurve2Changed\0"
    "Mixer5Vector_RollChanged\0"
    "Mixer5Vector_PitchChanged\0"
    "Mixer5Vector_YawChanged\0Mixer6TypeChanged\0"
    "Mixer6VectorChanged\0"
    "Mixer6Vector_ThrottleCurve1Changed\0"
    "Mixer6Vector_ThrottleCurve2Changed\0"
    "Mixer6Vector_RollChanged\0"
    "Mixer6Vector_PitchChanged\0"
    "Mixer6Vector_YawChanged\0Mixer7TypeChanged\0"
    "Mixer7VectorChanged\0"
    "Mixer7Vector_ThrottleCurve1Changed\0"
    "Mixer7Vector_ThrottleCurve2Changed\0"
    "Mixer7Vector_RollChanged\0"
    "Mixer7Vector_PitchChanged\0"
    "Mixer7Vector_YawChanged\0Mixer8TypeChanged\0"
    "Mixer8VectorChanged\0"
    "Mixer8Vector_ThrottleCurve1Changed\0"
    "Mixer8Vector_ThrottleCurve2Changed\0"
    "Mixer8Vector_RollChanged\0"
    "Mixer8Vector_PitchChanged\0"
    "Mixer8Vector_YawChanged\0Mixer9TypeChanged\0"
    "Mixer9VectorChanged\0"
    "Mixer9Vector_ThrottleCurve1Changed\0"
    "Mixer9Vector_ThrottleCurve2Changed\0"
    "Mixer9Vector_RollChanged\0"
    "Mixer9Vector_PitchChanged\0"
    "Mixer9Vector_YawChanged\0Mixer10TypeChanged\0"
    "Mixer10VectorChanged\0"
    "Mixer10Vector_ThrottleCurve1Changed\0"
    "Mixer10Vector_ThrottleCurve2Changed\0"
    "Mixer10Vector_RollChanged\0"
    "Mixer10Vector_PitchChanged\0"
    "Mixer10Vector_YawChanged\0Mixer11TypeChanged\0"
    "Mixer11VectorChanged\0"
    "Mixer11Vector_ThrottleCurve1Changed\0"
    "Mixer11Vector_ThrottleCurve2Changed\0"
    "Mixer11Vector_RollChanged\0"
    "Mixer11Vector_PitchChanged\0"
    "Mixer11Vector_YawChanged\0Mixer12TypeChanged\0"
    "Mixer12VectorChanged\0"
    "Mixer12Vector_ThrottleCurve1Changed\0"
    "Mixer12Vector_ThrottleCurve2Changed\0"
    "Mixer12Vector_RollChanged\0"
    "Mixer12Vector_PitchChanged\0"
    "Mixer12Vector_YawChanged\0setMaxAccel\0"
    "setFeedForward\0setAccelTime\0setDecelTime\0"
    "setThrottleCurve1\0setThrottleCurve1_0\0"
    "setThrottleCurve1_25\0setThrottleCurve1_50\0"
    "setThrottleCurve1_75\0setThrottleCurve1_100\0"
    "setThrottleCurve2\0setThrottleCurve2_0\0"
    "setThrottleCurve2_25\0setThrottleCurve2_50\0"
    "setThrottleCurve2_75\0setThrottleCurve2_100\0"
    "setMixerValueRoll\0setMixerValuePitch\0"
    "setMixerValueYaw\0setCurve2Source\0"
    "setMixer1Type\0setMixer1Vector\0"
    "setMixer1Vector_ThrottleCurve1\0"
    "setMixer1Vector_ThrottleCurve2\0"
    "setMixer1Vector_Roll\0setMixer1Vector_Pitch\0"
    "setMixer1Vector_Yaw\0setMixer2Type\0"
    "setMixer2Vector\0setMixer2Vector_ThrottleCurve1\0"
    "setMixer2Vector_ThrottleCurve2\0"
    "setMixer2Vector_Roll\0setMixer2Vector_Pitch\0"
    "setMixer2Vector_Yaw\0setMixer3Type\0"
    "setMixer3Vector\0setMixer3Vector_ThrottleCurve1\0"
    "setMixer3Vector_ThrottleCurve2\0"
    "setMixer3Vector_Roll\0setMixer3Vector_Pitch\0"
    "setMixer3Vector_Yaw\0setMixer4Type\0"
    "setMixer4Vector\0setMixer4Vector_ThrottleCurve1\0"
    "setMixer4Vector_ThrottleCurve2\0"
    "setMixer4Vector_Roll\0setMixer4Vector_Pitch\0"
    "setMixer4Vector_Yaw\0setMixer5Type\0"
    "setMixer5Vector\0setMixer5Vector_ThrottleCurve1\0"
    "setMixer5Vector_ThrottleCurve2\0"
    "setMixer5Vector_Roll\0setMixer5Vector_Pitch\0"
    "setMixer5Vector_Yaw\0setMixer6Type\0"
    "setMixer6Vector\0setMixer6Vector_ThrottleCurve1\0"
    "setMixer6Vector_ThrottleCurve2\0"
    "setMixer6Vector_Roll\0setMixer6Vector_Pitch\0"
    "setMixer6Vector_Yaw\0setMixer7Type\0"
    "setMixer7Vector\0setMixer7Vector_ThrottleCurve1\0"
    "setMixer7Vector_ThrottleCurve2\0"
    "setMixer7Vector_Roll\0setMixer7Vector_Pitch\0"
    "setMixer7Vector_Yaw\0setMixer8Type\0"
    "setMixer8Vector\0setMixer8Vector_ThrottleCurve1\0"
    "setMixer8Vector_ThrottleCurve2\0"
    "setMixer8Vector_Roll\0setMixer8Vector_Pitch\0"
    "setMixer8Vector_Yaw\0setMixer9Type\0"
    "setMixer9Vector\0setMixer9Vector_ThrottleCurve1\0"
    "setMixer9Vector_ThrottleCurve2\0"
    "setMixer9Vector_Roll\0setMixer9Vector_Pitch\0"
    "setMixer9Vector_Yaw\0setMixer10Type\0"
    "setMixer10Vector\0setMixer10Vector_ThrottleCurve1\0"
    "setMixer10Vector_ThrottleCurve2\0"
    "setMixer10Vector_Roll\0setMixer10Vector_Pitch\0"
    "setMixer10Vector_Yaw\0setMixer11Type\0"
    "setMixer11Vector\0setMixer11Vector_ThrottleCurve1\0"
    "setMixer11Vector_ThrottleCurve2\0"
    "setMixer11Vector_Roll\0setMixer11Vector_Pitch\0"
    "setMixer11Vector_Yaw\0setMixer12Type\0"
    "setMixer12Vector\0setMixer12Vector_ThrottleCurve1\0"
    "setMixer12Vector_ThrottleCurve2\0"
    "setMixer12Vector_Roll\0setMixer12Vector_Pitch\0"
    "setMixer12Vector_Yaw\0emitNotifications\0"
    "getMaxAccel\0getFeedForward\0getAccelTime\0"
    "getDecelTime\0getThrottleCurve1\0"
    "getThrottleCurve1_0\0getThrottleCurve1_25\0"
    "getThrottleCurve1_50\0getThrottleCurve1_75\0"
    "getThrottleCurve1_100\0getThrottleCurve2\0"
    "getThrottleCurve2_0\0getThrottleCurve2_25\0"
    "getThrottleCurve2_50\0getThrottleCurve2_75\0"
    "getThrottleCurve2_100\0getMixerValueRoll\0"
    "getMixerValuePitch\0getMixerValueYaw\0"
    "getCurve2Source\0getMixer1Type\0"
    "getMixer1Vector\0getMixer1Vector_ThrottleCurve1\0"
    "getMixer1Vector_ThrottleCurve2\0"
    "getMixer1Vector_Roll\0getMixer1Vector_Pitch\0"
    "getMixer1Vector_Yaw\0getMixer2Type\0"
    "getMixer2Vector\0getMixer2Vector_ThrottleCurve1\0"
    "getMixer2Vector_ThrottleCurve2\0"
    "getMixer2Vector_Roll\0getMixer2Vector_Pitch\0"
    "getMixer2Vector_Yaw\0getMixer3Type\0"
    "getMixer3Vector\0getMixer3Vector_ThrottleCurve1\0"
    "getMixer3Vector_ThrottleCurve2\0"
    "getMixer3Vector_Roll\0getMixer3Vector_Pitch\0"
    "getMixer3Vector_Yaw\0getMixer4Type\0"
    "getMixer4Vector\0getMixer4Vector_ThrottleCurve1\0"
    "getMixer4Vector_ThrottleCurve2\0"
    "getMixer4Vector_Roll\0getMixer4Vector_Pitch\0"
    "getMixer4Vector_Yaw\0getMixer5Type\0"
    "getMixer5Vector\0getMixer5Vector_ThrottleCurve1\0"
    "getMixer5Vector_ThrottleCurve2\0"
    "getMixer5Vector_Roll\0getMixer5Vector_Pitch\0"
    "getMixer5Vector_Yaw\0getMixer6Type\0"
    "getMixer6Vector\0getMixer6Vector_ThrottleCurve1\0"
    "getMixer6Vector_ThrottleCurve2\0"
    "getMixer6Vector_Roll\0getMixer6Vector_Pitch\0"
    "getMixer6Vector_Yaw\0getMixer7Type\0"
    "getMixer7Vector\0getMixer7Vector_ThrottleCurve1\0"
    "getMixer7Vector_ThrottleCurve2\0"
    "getMixer7Vector_Roll\0getMixer7Vector_Pitch\0"
    "getMixer7Vector_Yaw\0getMixer8Type\0"
    "getMixer8Vector\0getMixer8Vector_ThrottleCurve1\0"
    "getMixer8Vector_ThrottleCurve2\0"
    "getMixer8Vector_Roll\0getMixer8Vector_Pitch\0"
    "getMixer8Vector_Yaw\0getMixer9Type\0"
    "getMixer9Vector\0getMixer9Vector_ThrottleCurve1\0"
    "getMixer9Vector_ThrottleCurve2\0"
    "getMixer9Vector_Roll\0getMixer9Vector_Pitch\0"
    "getMixer9Vector_Yaw\0getMixer10Type\0"
    "getMixer10Vector\0getMixer10Vector_ThrottleCurve1\0"
    "getMixer10Vector_ThrottleCurve2\0"
    "getMixer10Vector_Roll\0getMixer10Vector_Pitch\0"
    "getMixer10Vector_Yaw\0getMixer11Type\0"
    "getMixer11Vector\0getMixer11Vector_ThrottleCurve1\0"
    "getMixer11Vector_ThrottleCurve2\0"
    "getMixer11Vector_Roll\0getMixer11Vector_Pitch\0"
    "getMixer11Vector_Yaw\0getMixer12Type\0"
    "getMixer12Vector\0getMixer12Vector_ThrottleCurve1\0"
    "getMixer12Vector_ThrottleCurve2\0"
    "getMixer12Vector_Roll\0getMixer12Vector_Pitch\0"
    "getMixer12Vector_Yaw\0MaxAccel\0FeedForward\0"
    "AccelTime\0DecelTime\0ThrottleCurve1_0\0"
    "ThrottleCurve1_25\0ThrottleCurve1_50\0"
    "ThrottleCurve1_75\0ThrottleCurve1_100\0"
    "ThrottleCurve2_0\0ThrottleCurve2_25\0"
    "ThrottleCurve2_50\0ThrottleCurve2_75\0"
    "ThrottleCurve2_100\0MixerValueRoll\0"
    "MixerValuePitch\0MixerValueYaw\0"
    "Curve2Source\0Mixer1Type\0"
    "Mixer1Vector_ThrottleCurve1\0"
    "Mixer1Vector_ThrottleCurve2\0"
    "Mixer1Vector_Roll\0Mixer1Vector_Pitch\0"
    "Mixer1Vector_Yaw\0Mixer2Type\0"
    "Mixer2Vector_ThrottleCurve1\0"
    "Mixer2Vector_ThrottleCurve2\0"
    "Mixer2Vector_Roll\0Mixer2Vector_Pitch\0"
    "Mixer2Vector_Yaw\0Mixer3Type\0"
    "Mixer3Vector_ThrottleCurve1\0"
    "Mixer3Vector_ThrottleCurve2\0"
    "Mixer3Vector_Roll\0Mixer3Vector_Pitch\0"
    "Mixer3Vector_Yaw\0Mixer4Type\0"
    "Mixer4Vector_ThrottleCurve1\0"
    "Mixer4Vector_ThrottleCurve2\0"
    "Mixer4Vector_Roll\0Mixer4Vector_Pitch\0"
    "Mixer4Vector_Yaw\0Mixer5Type\0"
    "Mixer5Vector_ThrottleCurve1\0"
    "Mixer5Vector_ThrottleCurve2\0"
    "Mixer5Vector_Roll\0Mixer5Vector_Pitch\0"
    "Mixer5Vector_Yaw\0Mixer6Type\0"
    "Mixer6Vector_ThrottleCurve1\0"
    "Mixer6Vector_ThrottleCurve2\0"
    "Mixer6Vector_Roll\0Mixer6Vector_Pitch\0"
    "Mixer6Vector_Yaw\0Mixer7Type\0"
    "Mixer7Vector_ThrottleCurve1\0"
    "Mixer7Vector_ThrottleCurve2\0"
    "Mixer7Vector_Roll\0Mixer7Vector_Pitch\0"
    "Mixer7Vector_Yaw\0Mixer8Type\0"
    "Mixer8Vector_ThrottleCurve1\0"
    "Mixer8Vector_ThrottleCurve2\0"
    "Mixer8Vector_Roll\0Mixer8Vector_Pitch\0"
    "Mixer8Vector_Yaw\0Mixer9Type\0"
    "Mixer9Vector_ThrottleCurve1\0"
    "Mixer9Vector_ThrottleCurve2\0"
    "Mixer9Vector_Roll\0Mixer9Vector_Pitch\0"
    "Mixer9Vector_Yaw\0Mixer10Type\0"
    "Mixer10Vector_ThrottleCurve1\0"
    "Mixer10Vector_ThrottleCurve2\0"
    "Mixer10Vector_Roll\0Mixer10Vector_Pitch\0"
    "Mixer10Vector_Yaw\0Mixer11Type\0"
    "Mixer11Vector_ThrottleCurve1\0"
    "Mixer11Vector_ThrottleCurve2\0"
    "Mixer11Vector_Roll\0Mixer11Vector_Pitch\0"
    "Mixer11Vector_Yaw\0Mixer12Type\0"
    "Mixer12Vector_ThrottleCurve1\0"
    "Mixer12Vector_ThrottleCurve2\0"
    "Mixer12Vector_Roll\0Mixer12Vector_Pitch\0"
    "Mixer12Vector_Yaw"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MixerSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     313,   14, // methods
      90, 2392, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
     104,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1, 1579,    2, 0x06 /* Public */,
       4,    1, 1582,    2, 0x06 /* Public */,
       5,    1, 1585,    2, 0x06 /* Public */,
       6,    1, 1588,    2, 0x06 /* Public */,
       7,    2, 1591,    2, 0x06 /* Public */,
       9,    1, 1596,    2, 0x06 /* Public */,
      10,    1, 1599,    2, 0x06 /* Public */,
      11,    1, 1602,    2, 0x06 /* Public */,
      12,    1, 1605,    2, 0x06 /* Public */,
      13,    1, 1608,    2, 0x06 /* Public */,
      14,    2, 1611,    2, 0x06 /* Public */,
      15,    1, 1616,    2, 0x06 /* Public */,
      16,    1, 1619,    2, 0x06 /* Public */,
      17,    1, 1622,    2, 0x06 /* Public */,
      18,    1, 1625,    2, 0x06 /* Public */,
      19,    1, 1628,    2, 0x06 /* Public */,
      20,    1, 1631,    2, 0x06 /* Public */,
      21,    1, 1634,    2, 0x06 /* Public */,
      22,    1, 1637,    2, 0x06 /* Public */,
      23,    1, 1640,    2, 0x06 /* Public */,
      24,    1, 1643,    2, 0x06 /* Public */,
      25,    2, 1646,    2, 0x06 /* Public */,
      26,    1, 1651,    2, 0x06 /* Public */,
      27,    1, 1654,    2, 0x06 /* Public */,
      28,    1, 1657,    2, 0x06 /* Public */,
      29,    1, 1660,    2, 0x06 /* Public */,
      30,    1, 1663,    2, 0x06 /* Public */,
      31,    1, 1666,    2, 0x06 /* Public */,
      32,    2, 1669,    2, 0x06 /* Public */,
      33,    1, 1674,    2, 0x06 /* Public */,
      34,    1, 1677,    2, 0x06 /* Public */,
      35,    1, 1680,    2, 0x06 /* Public */,
      36,    1, 1683,    2, 0x06 /* Public */,
      37,    1, 1686,    2, 0x06 /* Public */,
      38,    1, 1689,    2, 0x06 /* Public */,
      39,    2, 1692,    2, 0x06 /* Public */,
      40,    1, 1697,    2, 0x06 /* Public */,
      41,    1, 1700,    2, 0x06 /* Public */,
      42,    1, 1703,    2, 0x06 /* Public */,
      43,    1, 1706,    2, 0x06 /* Public */,
      44,    1, 1709,    2, 0x06 /* Public */,
      45,    1, 1712,    2, 0x06 /* Public */,
      46,    2, 1715,    2, 0x06 /* Public */,
      47,    1, 1720,    2, 0x06 /* Public */,
      48,    1, 1723,    2, 0x06 /* Public */,
      49,    1, 1726,    2, 0x06 /* Public */,
      50,    1, 1729,    2, 0x06 /* Public */,
      51,    1, 1732,    2, 0x06 /* Public */,
      52,    1, 1735,    2, 0x06 /* Public */,
      53,    2, 1738,    2, 0x06 /* Public */,
      54,    1, 1743,    2, 0x06 /* Public */,
      55,    1, 1746,    2, 0x06 /* Public */,
      56,    1, 1749,    2, 0x06 /* Public */,
      57,    1, 1752,    2, 0x06 /* Public */,
      58,    1, 1755,    2, 0x06 /* Public */,
      59,    1, 1758,    2, 0x06 /* Public */,
      60,    2, 1761,    2, 0x06 /* Public */,
      61,    1, 1766,    2, 0x06 /* Public */,
      62,    1, 1769,    2, 0x06 /* Public */,
      63,    1, 1772,    2, 0x06 /* Public */,
      64,    1, 1775,    2, 0x06 /* Public */,
      65,    1, 1778,    2, 0x06 /* Public */,
      66,    1, 1781,    2, 0x06 /* Public */,
      67,    2, 1784,    2, 0x06 /* Public */,
      68,    1, 1789,    2, 0x06 /* Public */,
      69,    1, 1792,    2, 0x06 /* Public */,
      70,    1, 1795,    2, 0x06 /* Public */,
      71,    1, 1798,    2, 0x06 /* Public */,
      72,    1, 1801,    2, 0x06 /* Public */,
      73,    1, 1804,    2, 0x06 /* Public */,
      74,    2, 1807,    2, 0x06 /* Public */,
      75,    1, 1812,    2, 0x06 /* Public */,
      76,    1, 1815,    2, 0x06 /* Public */,
      77,    1, 1818,    2, 0x06 /* Public */,
      78,    1, 1821,    2, 0x06 /* Public */,
      79,    1, 1824,    2, 0x06 /* Public */,
      80,    1, 1827,    2, 0x06 /* Public */,
      81,    2, 1830,    2, 0x06 /* Public */,
      82,    1, 1835,    2, 0x06 /* Public */,
      83,    1, 1838,    2, 0x06 /* Public */,
      84,    1, 1841,    2, 0x06 /* Public */,
      85,    1, 1844,    2, 0x06 /* Public */,
      86,    1, 1847,    2, 0x06 /* Public */,
      87,    1, 1850,    2, 0x06 /* Public */,
      88,    2, 1853,    2, 0x06 /* Public */,
      89,    1, 1858,    2, 0x06 /* Public */,
      90,    1, 1861,    2, 0x06 /* Public */,
      91,    1, 1864,    2, 0x06 /* Public */,
      92,    1, 1867,    2, 0x06 /* Public */,
      93,    1, 1870,    2, 0x06 /* Public */,
      94,    1, 1873,    2, 0x06 /* Public */,
      95,    2, 1876,    2, 0x06 /* Public */,
      96,    1, 1881,    2, 0x06 /* Public */,
      97,    1, 1884,    2, 0x06 /* Public */,
      98,    1, 1887,    2, 0x06 /* Public */,
      99,    1, 1890,    2, 0x06 /* Public */,
     100,    1, 1893,    2, 0x06 /* Public */,
     101,    1, 1896,    2, 0x06 /* Public */,
     102,    2, 1899,    2, 0x06 /* Public */,
     103,    1, 1904,    2, 0x06 /* Public */,
     104,    1, 1907,    2, 0x06 /* Public */,
     105,    1, 1910,    2, 0x06 /* Public */,
     106,    1, 1913,    2, 0x06 /* Public */,
     107,    1, 1916,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
     108,    1, 1919,    2, 0x0a /* Public */,
     109,    1, 1922,    2, 0x0a /* Public */,
     110,    1, 1925,    2, 0x0a /* Public */,
     111,    1, 1928,    2, 0x0a /* Public */,
     112,    2, 1931,    2, 0x0a /* Public */,
     113,    1, 1936,    2, 0x0a /* Public */,
     114,    1, 1939,    2, 0x0a /* Public */,
     115,    1, 1942,    2, 0x0a /* Public */,
     116,    1, 1945,    2, 0x0a /* Public */,
     117,    1, 1948,    2, 0x0a /* Public */,
     118,    2, 1951,    2, 0x0a /* Public */,
     119,    1, 1956,    2, 0x0a /* Public */,
     120,    1, 1959,    2, 0x0a /* Public */,
     121,    1, 1962,    2, 0x0a /* Public */,
     122,    1, 1965,    2, 0x0a /* Public */,
     123,    1, 1968,    2, 0x0a /* Public */,
     124,    1, 1971,    2, 0x0a /* Public */,
     125,    1, 1974,    2, 0x0a /* Public */,
     126,    1, 1977,    2, 0x0a /* Public */,
     127,    1, 1980,    2, 0x0a /* Public */,
     128,    1, 1983,    2, 0x0a /* Public */,
     129,    2, 1986,    2, 0x0a /* Public */,
     130,    1, 1991,    2, 0x0a /* Public */,
     131,    1, 1994,    2, 0x0a /* Public */,
     132,    1, 1997,    2, 0x0a /* Public */,
     133,    1, 2000,    2, 0x0a /* Public */,
     134,    1, 2003,    2, 0x0a /* Public */,
     135,    1, 2006,    2, 0x0a /* Public */,
     136,    2, 2009,    2, 0x0a /* Public */,
     137,    1, 2014,    2, 0x0a /* Public */,
     138,    1, 2017,    2, 0x0a /* Public */,
     139,    1, 2020,    2, 0x0a /* Public */,
     140,    1, 2023,    2, 0x0a /* Public */,
     141,    1, 2026,    2, 0x0a /* Public */,
     142,    1, 2029,    2, 0x0a /* Public */,
     143,    2, 2032,    2, 0x0a /* Public */,
     144,    1, 2037,    2, 0x0a /* Public */,
     145,    1, 2040,    2, 0x0a /* Public */,
     146,    1, 2043,    2, 0x0a /* Public */,
     147,    1, 2046,    2, 0x0a /* Public */,
     148,    1, 2049,    2, 0x0a /* Public */,
     149,    1, 2052,    2, 0x0a /* Public */,
     150,    2, 2055,    2, 0x0a /* Public */,
     151,    1, 2060,    2, 0x0a /* Public */,
     152,    1, 2063,    2, 0x0a /* Public */,
     153,    1, 2066,    2, 0x0a /* Public */,
     154,    1, 2069,    2, 0x0a /* Public */,
     155,    1, 2072,    2, 0x0a /* Public */,
     156,    1, 2075,    2, 0x0a /* Public */,
     157,    2, 2078,    2, 0x0a /* Public */,
     158,    1, 2083,    2, 0x0a /* Public */,
     159,    1, 2086,    2, 0x0a /* Public */,
     160,    1, 2089,    2, 0x0a /* Public */,
     161,    1, 2092,    2, 0x0a /* Public */,
     162,    1, 2095,    2, 0x0a /* Public */,
     163,    1, 2098,    2, 0x0a /* Public */,
     164,    2, 2101,    2, 0x0a /* Public */,
     165,    1, 2106,    2, 0x0a /* Public */,
     166,    1, 2109,    2, 0x0a /* Public */,
     167,    1, 2112,    2, 0x0a /* Public */,
     168,    1, 2115,    2, 0x0a /* Public */,
     169,    1, 2118,    2, 0x0a /* Public */,
     170,    1, 2121,    2, 0x0a /* Public */,
     171,    2, 2124,    2, 0x0a /* Public */,
     172,    1, 2129,    2, 0x0a /* Public */,
     173,    1, 2132,    2, 0x0a /* Public */,
     174,    1, 2135,    2, 0x0a /* Public */,
     175,    1, 2138,    2, 0x0a /* Public */,
     176,    1, 2141,    2, 0x0a /* Public */,
     177,    1, 2144,    2, 0x0a /* Public */,
     178,    2, 2147,    2, 0x0a /* Public */,
     179,    1, 2152,    2, 0x0a /* Public */,
     180,    1, 2155,    2, 0x0a /* Public */,
     181,    1, 2158,    2, 0x0a /* Public */,
     182,    1, 2161,    2, 0x0a /* Public */,
     183,    1, 2164,    2, 0x0a /* Public */,
     184,    1, 2167,    2, 0x0a /* Public */,
     185,    2, 2170,    2, 0x0a /* Public */,
     186,    1, 2175,    2, 0x0a /* Public */,
     187,    1, 2178,    2, 0x0a /* Public */,
     188,    1, 2181,    2, 0x0a /* Public */,
     189,    1, 2184,    2, 0x0a /* Public */,
     190,    1, 2187,    2, 0x0a /* Public */,
     191,    1, 2190,    2, 0x0a /* Public */,
     192,    2, 2193,    2, 0x0a /* Public */,
     193,    1, 2198,    2, 0x0a /* Public */,
     194,    1, 2201,    2, 0x0a /* Public */,
     195,    1, 2204,    2, 0x0a /* Public */,
     196,    1, 2207,    2, 0x0a /* Public */,
     197,    1, 2210,    2, 0x0a /* Public */,
     198,    1, 2213,    2, 0x0a /* Public */,
     199,    2, 2216,    2, 0x0a /* Public */,
     200,    1, 2221,    2, 0x0a /* Public */,
     201,    1, 2224,    2, 0x0a /* Public */,
     202,    1, 2227,    2, 0x0a /* Public */,
     203,    1, 2230,    2, 0x0a /* Public */,
     204,    1, 2233,    2, 0x0a /* Public */,
     205,    1, 2236,    2, 0x0a /* Public */,
     206,    2, 2239,    2, 0x0a /* Public */,
     207,    1, 2244,    2, 0x0a /* Public */,
     208,    1, 2247,    2, 0x0a /* Public */,
     209,    1, 2250,    2, 0x0a /* Public */,
     210,    1, 2253,    2, 0x0a /* Public */,
     211,    1, 2256,    2, 0x0a /* Public */,
     212,    0, 2259,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
     213,    0, 2260,    2, 0x02 /* Public */,
     214,    0, 2261,    2, 0x02 /* Public */,
     215,    0, 2262,    2, 0x02 /* Public */,
     216,    0, 2263,    2, 0x02 /* Public */,
     217,    1, 2264,    2, 0x02 /* Public */,
     218,    0, 2267,    2, 0x02 /* Public */,
     219,    0, 2268,    2, 0x02 /* Public */,
     220,    0, 2269,    2, 0x02 /* Public */,
     221,    0, 2270,    2, 0x02 /* Public */,
     222,    0, 2271,    2, 0x02 /* Public */,
     223,    1, 2272,    2, 0x02 /* Public */,
     224,    0, 2275,    2, 0x02 /* Public */,
     225,    0, 2276,    2, 0x02 /* Public */,
     226,    0, 2277,    2, 0x02 /* Public */,
     227,    0, 2278,    2, 0x02 /* Public */,
     228,    0, 2279,    2, 0x02 /* Public */,
     229,    0, 2280,    2, 0x02 /* Public */,
     230,    0, 2281,    2, 0x02 /* Public */,
     231,    0, 2282,    2, 0x02 /* Public */,
     232,    0, 2283,    2, 0x02 /* Public */,
     233,    0, 2284,    2, 0x02 /* Public */,
     234,    1, 2285,    2, 0x02 /* Public */,
     235,    0, 2288,    2, 0x02 /* Public */,
     236,    0, 2289,    2, 0x02 /* Public */,
     237,    0, 2290,    2, 0x02 /* Public */,
     238,    0, 2291,    2, 0x02 /* Public */,
     239,    0, 2292,    2, 0x02 /* Public */,
     240,    0, 2293,    2, 0x02 /* Public */,
     241,    1, 2294,    2, 0x02 /* Public */,
     242,    0, 2297,    2, 0x02 /* Public */,
     243,    0, 2298,    2, 0x02 /* Public */,
     244,    0, 2299,    2, 0x02 /* Public */,
     245,    0, 2300,    2, 0x02 /* Public */,
     246,    0, 2301,    2, 0x02 /* Public */,
     247,    0, 2302,    2, 0x02 /* Public */,
     248,    1, 2303,    2, 0x02 /* Public */,
     249,    0, 2306,    2, 0x02 /* Public */,
     250,    0, 2307,    2, 0x02 /* Public */,
     251,    0, 2308,    2, 0x02 /* Public */,
     252,    0, 2309,    2, 0x02 /* Public */,
     253,    0, 2310,    2, 0x02 /* Public */,
     254,    0, 2311,    2, 0x02 /* Public */,
     255,    1, 2312,    2, 0x02 /* Public */,
     256,    0, 2315,    2, 0x02 /* Public */,
     257,    0, 2316,    2, 0x02 /* Public */,
     258,    0, 2317,    2, 0x02 /* Public */,
     259,    0, 2318,    2, 0x02 /* Public */,
     260,    0, 2319,    2, 0x02 /* Public */,
     261,    0, 2320,    2, 0x02 /* Public */,
     262,    1, 2321,    2, 0x02 /* Public */,
     263,    0, 2324,    2, 0x02 /* Public */,
     264,    0, 2325,    2, 0x02 /* Public */,
     265,    0, 2326,    2, 0x02 /* Public */,
     266,    0, 2327,    2, 0x02 /* Public */,
     267,    0, 2328,    2, 0x02 /* Public */,
     268,    0, 2329,    2, 0x02 /* Public */,
     269,    1, 2330,    2, 0x02 /* Public */,
     270,    0, 2333,    2, 0x02 /* Public */,
     271,    0, 2334,    2, 0x02 /* Public */,
     272,    0, 2335,    2, 0x02 /* Public */,
     273,    0, 2336,    2, 0x02 /* Public */,
     274,    0, 2337,    2, 0x02 /* Public */,
     275,    0, 2338,    2, 0x02 /* Public */,
     276,    1, 2339,    2, 0x02 /* Public */,
     277,    0, 2342,    2, 0x02 /* Public */,
     278,    0, 2343,    2, 0x02 /* Public */,
     279,    0, 2344,    2, 0x02 /* Public */,
     280,    0, 2345,    2, 0x02 /* Public */,
     281,    0, 2346,    2, 0x02 /* Public */,
     282,    0, 2347,    2, 0x02 /* Public */,
     283,    1, 2348,    2, 0x02 /* Public */,
     284,    0, 2351,    2, 0x02 /* Public */,
     285,    0, 2352,    2, 0x02 /* Public */,
     286,    0, 2353,    2, 0x02 /* Public */,
     287,    0, 2354,    2, 0x02 /* Public */,
     288,    0, 2355,    2, 0x02 /* Public */,
     289,    0, 2356,    2, 0x02 /* Public */,
     290,    1, 2357,    2, 0x02 /* Public */,
     291,    0, 2360,    2, 0x02 /* Public */,
     292,    0, 2361,    2, 0x02 /* Public */,
     293,    0, 2362,    2, 0x02 /* Public */,
     294,    0, 2363,    2, 0x02 /* Public */,
     295,    0, 2364,    2, 0x02 /* Public */,
     296,    0, 2365,    2, 0x02 /* Public */,
     297,    1, 2366,    2, 0x02 /* Public */,
     298,    0, 2369,    2, 0x02 /* Public */,
     299,    0, 2370,    2, 0x02 /* Public */,
     300,    0, 2371,    2, 0x02 /* Public */,
     301,    0, 2372,    2, 0x02 /* Public */,
     302,    0, 2373,    2, 0x02 /* Public */,
     303,    0, 2374,    2, 0x02 /* Public */,
     304,    1, 2375,    2, 0x02 /* Public */,
     305,    0, 2378,    2, 0x02 /* Public */,
     306,    0, 2379,    2, 0x02 /* Public */,
     307,    0, 2380,    2, 0x02 /* Public */,
     308,    0, 2381,    2, 0x02 /* Public */,
     309,    0, 2382,    2, 0x02 /* Public */,
     310,    0, 2383,    2, 0x02 /* Public */,
     311,    1, 2384,    2, 0x02 /* Public */,
     312,    0, 2387,    2, 0x02 /* Public */,
     313,    0, 2388,    2, 0x02 /* Public */,
     314,    0, 2389,    2, 0x02 /* Public */,
     315,    0, 2390,    2, 0x02 /* Public */,
     316,    0, 2391,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    8,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    8,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    8,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    8,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    8,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void, QMetaType::SChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    8,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    8,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    8,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    8,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    8,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    8,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    8,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    8,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    8,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    8,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    8,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    8,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    8,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    8,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,

 // properties: name, type, flags
     317, QMetaType::Float, 0x00495103,
     318, QMetaType::Float, 0x00495103,
     319, QMetaType::Float, 0x00495103,
     320, QMetaType::Float, 0x00495103,
     321, QMetaType::Float, 0x00495103,
     322, QMetaType::Float, 0x00495103,
     323, QMetaType::Float, 0x00495103,
     324, QMetaType::Float, 0x00495103,
     325, QMetaType::Float, 0x00495103,
     326, QMetaType::Float, 0x00495103,
     327, QMetaType::Float, 0x00495103,
     328, QMetaType::Float, 0x00495103,
     329, QMetaType::Float, 0x00495103,
     330, QMetaType::Float, 0x00495103,
     331, QMetaType::SChar, 0x00495103,
     332, QMetaType::SChar, 0x00495103,
     333, QMetaType::SChar, 0x00495103,
     334, QMetaType::UChar, 0x00495103,
     335, QMetaType::UChar, 0x00495103,
     336, QMetaType::SChar, 0x00495103,
     337, QMetaType::SChar, 0x00495103,
     338, QMetaType::SChar, 0x00495103,
     339, QMetaType::SChar, 0x00495103,
     340, QMetaType::SChar, 0x00495103,
     341, QMetaType::UChar, 0x00495103,
     342, QMetaType::SChar, 0x00495103,
     343, QMetaType::SChar, 0x00495103,
     344, QMetaType::SChar, 0x00495103,
     345, QMetaType::SChar, 0x00495103,
     346, QMetaType::SChar, 0x00495103,
     347, QMetaType::UChar, 0x00495103,
     348, QMetaType::SChar, 0x00495103,
     349, QMetaType::SChar, 0x00495103,
     350, QMetaType::SChar, 0x00495103,
     351, QMetaType::SChar, 0x00495103,
     352, QMetaType::SChar, 0x00495103,
     353, QMetaType::UChar, 0x00495103,
     354, QMetaType::SChar, 0x00495103,
     355, QMetaType::SChar, 0x00495103,
     356, QMetaType::SChar, 0x00495103,
     357, QMetaType::SChar, 0x00495103,
     358, QMetaType::SChar, 0x00495103,
     359, QMetaType::UChar, 0x00495103,
     360, QMetaType::SChar, 0x00495103,
     361, QMetaType::SChar, 0x00495103,
     362, QMetaType::SChar, 0x00495103,
     363, QMetaType::SChar, 0x00495103,
     364, QMetaType::SChar, 0x00495103,
     365, QMetaType::UChar, 0x00495103,
     366, QMetaType::SChar, 0x00495103,
     367, QMetaType::SChar, 0x00495103,
     368, QMetaType::SChar, 0x00495103,
     369, QMetaType::SChar, 0x00495103,
     370, QMetaType::SChar, 0x00495103,
     371, QMetaType::UChar, 0x00495103,
     372, QMetaType::SChar, 0x00495103,
     373, QMetaType::SChar, 0x00495103,
     374, QMetaType::SChar, 0x00495103,
     375, QMetaType::SChar, 0x00495103,
     376, QMetaType::SChar, 0x00495103,
     377, QMetaType::UChar, 0x00495103,
     378, QMetaType::SChar, 0x00495103,
     379, QMetaType::SChar, 0x00495103,
     380, QMetaType::SChar, 0x00495103,
     381, QMetaType::SChar, 0x00495103,
     382, QMetaType::SChar, 0x00495103,
     383, QMetaType::UChar, 0x00495103,
     384, QMetaType::SChar, 0x00495103,
     385, QMetaType::SChar, 0x00495103,
     386, QMetaType::SChar, 0x00495103,
     387, QMetaType::SChar, 0x00495103,
     388, QMetaType::SChar, 0x00495103,
     389, QMetaType::UChar, 0x00495103,
     390, QMetaType::SChar, 0x00495103,
     391, QMetaType::SChar, 0x00495103,
     392, QMetaType::SChar, 0x00495103,
     393, QMetaType::SChar, 0x00495103,
     394, QMetaType::SChar, 0x00495103,
     395, QMetaType::UChar, 0x00495103,
     396, QMetaType::SChar, 0x00495103,
     397, QMetaType::SChar, 0x00495103,
     398, QMetaType::SChar, 0x00495103,
     399, QMetaType::SChar, 0x00495103,
     400, QMetaType::SChar, 0x00495103,
     401, QMetaType::UChar, 0x00495103,
     402, QMetaType::SChar, 0x00495103,
     403, QMetaType::SChar, 0x00495103,
     404, QMetaType::SChar, 0x00495103,
     405, QMetaType::SChar, 0x00495103,
     406, QMetaType::SChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       5,
       6,
       7,
       8,
       9,
      11,
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
      29,
      30,
      31,
      32,
      33,
      34,
      36,
      37,
      38,
      39,
      40,
      41,
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
      57,
      58,
      59,
      60,
      61,
      62,
      64,
      65,
      66,
      67,
      68,
      69,
      71,
      72,
      73,
      74,
      75,
      76,
      78,
      79,
      80,
      81,
      82,
      83,
      85,
      86,
      87,
      88,
      89,
      90,
      92,
      93,
      94,
      95,
      96,
      97,
      99,
     100,
     101,
     102,
     103,

       0        // eod
};

void MixerSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MixerSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->MaxAccelChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->FeedForwardChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->AccelTimeChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->DecelTimeChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->ThrottleCurve1Changed((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->ThrottleCurve1_0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->ThrottleCurve1_25Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->ThrottleCurve1_50Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->ThrottleCurve1_75Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->ThrottleCurve1_100Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->ThrottleCurve2Changed((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 11: _t->ThrottleCurve2_0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->ThrottleCurve2_25Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->ThrottleCurve2_50Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->ThrottleCurve2_75Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->ThrottleCurve2_100Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->MixerValueRollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 17: _t->MixerValuePitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 18: _t->MixerValueYawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 19: _t->Curve2SourceChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->Mixer1TypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 21: _t->Mixer1VectorChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 22: _t->Mixer1Vector_ThrottleCurve1Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 23: _t->Mixer1Vector_ThrottleCurve2Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 24: _t->Mixer1Vector_RollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 25: _t->Mixer1Vector_PitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 26: _t->Mixer1Vector_YawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 27: _t->Mixer2TypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 28: _t->Mixer2VectorChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 29: _t->Mixer2Vector_ThrottleCurve1Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 30: _t->Mixer2Vector_ThrottleCurve2Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 31: _t->Mixer2Vector_RollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 32: _t->Mixer2Vector_PitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 33: _t->Mixer2Vector_YawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 34: _t->Mixer3TypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 35: _t->Mixer3VectorChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 36: _t->Mixer3Vector_ThrottleCurve1Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 37: _t->Mixer3Vector_ThrottleCurve2Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 38: _t->Mixer3Vector_RollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 39: _t->Mixer3Vector_PitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 40: _t->Mixer3Vector_YawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 41: _t->Mixer4TypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 42: _t->Mixer4VectorChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 43: _t->Mixer4Vector_ThrottleCurve1Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 44: _t->Mixer4Vector_ThrottleCurve2Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 45: _t->Mixer4Vector_RollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 46: _t->Mixer4Vector_PitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 47: _t->Mixer4Vector_YawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 48: _t->Mixer5TypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 49: _t->Mixer5VectorChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 50: _t->Mixer5Vector_ThrottleCurve1Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 51: _t->Mixer5Vector_ThrottleCurve2Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 52: _t->Mixer5Vector_RollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 53: _t->Mixer5Vector_PitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 54: _t->Mixer5Vector_YawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 55: _t->Mixer6TypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 56: _t->Mixer6VectorChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 57: _t->Mixer6Vector_ThrottleCurve1Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 58: _t->Mixer6Vector_ThrottleCurve2Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 59: _t->Mixer6Vector_RollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 60: _t->Mixer6Vector_PitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 61: _t->Mixer6Vector_YawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 62: _t->Mixer7TypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 63: _t->Mixer7VectorChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 64: _t->Mixer7Vector_ThrottleCurve1Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 65: _t->Mixer7Vector_ThrottleCurve2Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 66: _t->Mixer7Vector_RollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 67: _t->Mixer7Vector_PitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 68: _t->Mixer7Vector_YawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 69: _t->Mixer8TypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 70: _t->Mixer8VectorChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 71: _t->Mixer8Vector_ThrottleCurve1Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 72: _t->Mixer8Vector_ThrottleCurve2Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 73: _t->Mixer8Vector_RollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 74: _t->Mixer8Vector_PitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 75: _t->Mixer8Vector_YawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 76: _t->Mixer9TypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 77: _t->Mixer9VectorChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 78: _t->Mixer9Vector_ThrottleCurve1Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 79: _t->Mixer9Vector_ThrottleCurve2Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 80: _t->Mixer9Vector_RollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 81: _t->Mixer9Vector_PitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 82: _t->Mixer9Vector_YawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 83: _t->Mixer10TypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 84: _t->Mixer10VectorChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 85: _t->Mixer10Vector_ThrottleCurve1Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 86: _t->Mixer10Vector_ThrottleCurve2Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 87: _t->Mixer10Vector_RollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 88: _t->Mixer10Vector_PitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 89: _t->Mixer10Vector_YawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 90: _t->Mixer11TypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 91: _t->Mixer11VectorChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 92: _t->Mixer11Vector_ThrottleCurve1Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 93: _t->Mixer11Vector_ThrottleCurve2Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 94: _t->Mixer11Vector_RollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 95: _t->Mixer11Vector_PitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 96: _t->Mixer11Vector_YawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 97: _t->Mixer12TypeChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 98: _t->Mixer12VectorChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 99: _t->Mixer12Vector_ThrottleCurve1Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 100: _t->Mixer12Vector_ThrottleCurve2Changed((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 101: _t->Mixer12Vector_RollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 102: _t->Mixer12Vector_PitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 103: _t->Mixer12Vector_YawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 104: _t->setMaxAccel((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 105: _t->setFeedForward((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 106: _t->setAccelTime((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 107: _t->setDecelTime((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 108: _t->setThrottleCurve1((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 109: _t->setThrottleCurve1_0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 110: _t->setThrottleCurve1_25((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 111: _t->setThrottleCurve1_50((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 112: _t->setThrottleCurve1_75((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 113: _t->setThrottleCurve1_100((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 114: _t->setThrottleCurve2((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 115: _t->setThrottleCurve2_0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 116: _t->setThrottleCurve2_25((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 117: _t->setThrottleCurve2_50((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 118: _t->setThrottleCurve2_75((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 119: _t->setThrottleCurve2_100((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 120: _t->setMixerValueRoll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 121: _t->setMixerValuePitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 122: _t->setMixerValueYaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 123: _t->setCurve2Source((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 124: _t->setMixer1Type((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 125: _t->setMixer1Vector((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 126: _t->setMixer1Vector_ThrottleCurve1((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 127: _t->setMixer1Vector_ThrottleCurve2((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 128: _t->setMixer1Vector_Roll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 129: _t->setMixer1Vector_Pitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 130: _t->setMixer1Vector_Yaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 131: _t->setMixer2Type((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 132: _t->setMixer2Vector((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 133: _t->setMixer2Vector_ThrottleCurve1((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 134: _t->setMixer2Vector_ThrottleCurve2((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 135: _t->setMixer2Vector_Roll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 136: _t->setMixer2Vector_Pitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 137: _t->setMixer2Vector_Yaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 138: _t->setMixer3Type((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 139: _t->setMixer3Vector((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 140: _t->setMixer3Vector_ThrottleCurve1((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 141: _t->setMixer3Vector_ThrottleCurve2((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 142: _t->setMixer3Vector_Roll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 143: _t->setMixer3Vector_Pitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 144: _t->setMixer3Vector_Yaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 145: _t->setMixer4Type((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 146: _t->setMixer4Vector((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 147: _t->setMixer4Vector_ThrottleCurve1((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 148: _t->setMixer4Vector_ThrottleCurve2((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 149: _t->setMixer4Vector_Roll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 150: _t->setMixer4Vector_Pitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 151: _t->setMixer4Vector_Yaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 152: _t->setMixer5Type((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 153: _t->setMixer5Vector((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 154: _t->setMixer5Vector_ThrottleCurve1((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 155: _t->setMixer5Vector_ThrottleCurve2((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 156: _t->setMixer5Vector_Roll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 157: _t->setMixer5Vector_Pitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 158: _t->setMixer5Vector_Yaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 159: _t->setMixer6Type((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 160: _t->setMixer6Vector((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 161: _t->setMixer6Vector_ThrottleCurve1((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 162: _t->setMixer6Vector_ThrottleCurve2((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 163: _t->setMixer6Vector_Roll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 164: _t->setMixer6Vector_Pitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 165: _t->setMixer6Vector_Yaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 166: _t->setMixer7Type((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 167: _t->setMixer7Vector((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 168: _t->setMixer7Vector_ThrottleCurve1((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 169: _t->setMixer7Vector_ThrottleCurve2((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 170: _t->setMixer7Vector_Roll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 171: _t->setMixer7Vector_Pitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 172: _t->setMixer7Vector_Yaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 173: _t->setMixer8Type((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 174: _t->setMixer8Vector((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 175: _t->setMixer8Vector_ThrottleCurve1((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 176: _t->setMixer8Vector_ThrottleCurve2((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 177: _t->setMixer8Vector_Roll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 178: _t->setMixer8Vector_Pitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 179: _t->setMixer8Vector_Yaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 180: _t->setMixer9Type((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 181: _t->setMixer9Vector((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 182: _t->setMixer9Vector_ThrottleCurve1((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 183: _t->setMixer9Vector_ThrottleCurve2((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 184: _t->setMixer9Vector_Roll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 185: _t->setMixer9Vector_Pitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 186: _t->setMixer9Vector_Yaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 187: _t->setMixer10Type((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 188: _t->setMixer10Vector((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 189: _t->setMixer10Vector_ThrottleCurve1((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 190: _t->setMixer10Vector_ThrottleCurve2((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 191: _t->setMixer10Vector_Roll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 192: _t->setMixer10Vector_Pitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 193: _t->setMixer10Vector_Yaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 194: _t->setMixer11Type((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 195: _t->setMixer11Vector((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 196: _t->setMixer11Vector_ThrottleCurve1((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 197: _t->setMixer11Vector_ThrottleCurve2((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 198: _t->setMixer11Vector_Roll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 199: _t->setMixer11Vector_Pitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 200: _t->setMixer11Vector_Yaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 201: _t->setMixer12Type((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 202: _t->setMixer12Vector((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 203: _t->setMixer12Vector_ThrottleCurve1((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 204: _t->setMixer12Vector_ThrottleCurve2((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 205: _t->setMixer12Vector_Roll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 206: _t->setMixer12Vector_Pitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 207: _t->setMixer12Vector_Yaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 208: _t->emitNotifications(); break;
        case 209: { float _r = _t->getMaxAccel();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 210: { float _r = _t->getFeedForward();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 211: { float _r = _t->getAccelTime();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 212: { float _r = _t->getDecelTime();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 213: { float _r = _t->getThrottleCurve1((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 214: { float _r = _t->getThrottleCurve1_0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 215: { float _r = _t->getThrottleCurve1_25();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 216: { float _r = _t->getThrottleCurve1_50();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 217: { float _r = _t->getThrottleCurve1_75();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 218: { float _r = _t->getThrottleCurve1_100();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 219: { float _r = _t->getThrottleCurve2((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 220: { float _r = _t->getThrottleCurve2_0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 221: { float _r = _t->getThrottleCurve2_25();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 222: { float _r = _t->getThrottleCurve2_50();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 223: { float _r = _t->getThrottleCurve2_75();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 224: { float _r = _t->getThrottleCurve2_100();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 225: { qint8 _r = _t->getMixerValueRoll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 226: { qint8 _r = _t->getMixerValuePitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 227: { qint8 _r = _t->getMixerValueYaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 228: { quint8 _r = _t->getCurve2Source();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 229: { quint8 _r = _t->getMixer1Type();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 230: { qint8 _r = _t->getMixer1Vector((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 231: { qint8 _r = _t->getMixer1Vector_ThrottleCurve1();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 232: { qint8 _r = _t->getMixer1Vector_ThrottleCurve2();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 233: { qint8 _r = _t->getMixer1Vector_Roll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 234: { qint8 _r = _t->getMixer1Vector_Pitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 235: { qint8 _r = _t->getMixer1Vector_Yaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 236: { quint8 _r = _t->getMixer2Type();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 237: { qint8 _r = _t->getMixer2Vector((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 238: { qint8 _r = _t->getMixer2Vector_ThrottleCurve1();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 239: { qint8 _r = _t->getMixer2Vector_ThrottleCurve2();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 240: { qint8 _r = _t->getMixer2Vector_Roll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 241: { qint8 _r = _t->getMixer2Vector_Pitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 242: { qint8 _r = _t->getMixer2Vector_Yaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 243: { quint8 _r = _t->getMixer3Type();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 244: { qint8 _r = _t->getMixer3Vector((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 245: { qint8 _r = _t->getMixer3Vector_ThrottleCurve1();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 246: { qint8 _r = _t->getMixer3Vector_ThrottleCurve2();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 247: { qint8 _r = _t->getMixer3Vector_Roll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 248: { qint8 _r = _t->getMixer3Vector_Pitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 249: { qint8 _r = _t->getMixer3Vector_Yaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 250: { quint8 _r = _t->getMixer4Type();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 251: { qint8 _r = _t->getMixer4Vector((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 252: { qint8 _r = _t->getMixer4Vector_ThrottleCurve1();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 253: { qint8 _r = _t->getMixer4Vector_ThrottleCurve2();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 254: { qint8 _r = _t->getMixer4Vector_Roll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 255: { qint8 _r = _t->getMixer4Vector_Pitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 256: { qint8 _r = _t->getMixer4Vector_Yaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 257: { quint8 _r = _t->getMixer5Type();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 258: { qint8 _r = _t->getMixer5Vector((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 259: { qint8 _r = _t->getMixer5Vector_ThrottleCurve1();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 260: { qint8 _r = _t->getMixer5Vector_ThrottleCurve2();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 261: { qint8 _r = _t->getMixer5Vector_Roll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 262: { qint8 _r = _t->getMixer5Vector_Pitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 263: { qint8 _r = _t->getMixer5Vector_Yaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 264: { quint8 _r = _t->getMixer6Type();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 265: { qint8 _r = _t->getMixer6Vector((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 266: { qint8 _r = _t->getMixer6Vector_ThrottleCurve1();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 267: { qint8 _r = _t->getMixer6Vector_ThrottleCurve2();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 268: { qint8 _r = _t->getMixer6Vector_Roll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 269: { qint8 _r = _t->getMixer6Vector_Pitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 270: { qint8 _r = _t->getMixer6Vector_Yaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 271: { quint8 _r = _t->getMixer7Type();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 272: { qint8 _r = _t->getMixer7Vector((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 273: { qint8 _r = _t->getMixer7Vector_ThrottleCurve1();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 274: { qint8 _r = _t->getMixer7Vector_ThrottleCurve2();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 275: { qint8 _r = _t->getMixer7Vector_Roll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 276: { qint8 _r = _t->getMixer7Vector_Pitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 277: { qint8 _r = _t->getMixer7Vector_Yaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 278: { quint8 _r = _t->getMixer8Type();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 279: { qint8 _r = _t->getMixer8Vector((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 280: { qint8 _r = _t->getMixer8Vector_ThrottleCurve1();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 281: { qint8 _r = _t->getMixer8Vector_ThrottleCurve2();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 282: { qint8 _r = _t->getMixer8Vector_Roll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 283: { qint8 _r = _t->getMixer8Vector_Pitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 284: { qint8 _r = _t->getMixer8Vector_Yaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 285: { quint8 _r = _t->getMixer9Type();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 286: { qint8 _r = _t->getMixer9Vector((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 287: { qint8 _r = _t->getMixer9Vector_ThrottleCurve1();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 288: { qint8 _r = _t->getMixer9Vector_ThrottleCurve2();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 289: { qint8 _r = _t->getMixer9Vector_Roll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 290: { qint8 _r = _t->getMixer9Vector_Pitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 291: { qint8 _r = _t->getMixer9Vector_Yaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 292: { quint8 _r = _t->getMixer10Type();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 293: { qint8 _r = _t->getMixer10Vector((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 294: { qint8 _r = _t->getMixer10Vector_ThrottleCurve1();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 295: { qint8 _r = _t->getMixer10Vector_ThrottleCurve2();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 296: { qint8 _r = _t->getMixer10Vector_Roll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 297: { qint8 _r = _t->getMixer10Vector_Pitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 298: { qint8 _r = _t->getMixer10Vector_Yaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 299: { quint8 _r = _t->getMixer11Type();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 300: { qint8 _r = _t->getMixer11Vector((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 301: { qint8 _r = _t->getMixer11Vector_ThrottleCurve1();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 302: { qint8 _r = _t->getMixer11Vector_ThrottleCurve2();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 303: { qint8 _r = _t->getMixer11Vector_Roll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 304: { qint8 _r = _t->getMixer11Vector_Pitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 305: { qint8 _r = _t->getMixer11Vector_Yaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 306: { quint8 _r = _t->getMixer12Type();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 307: { qint8 _r = _t->getMixer12Vector((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 308: { qint8 _r = _t->getMixer12Vector_ThrottleCurve1();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 309: { qint8 _r = _t->getMixer12Vector_ThrottleCurve2();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 310: { qint8 _r = _t->getMixer12Vector_Roll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 311: { qint8 _r = _t->getMixer12Vector_Pitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 312: { qint8 _r = _t->getMixer12Vector_Yaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::MaxAccelChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::FeedForwardChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::AccelTimeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::DecelTimeChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::ThrottleCurve1Changed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::ThrottleCurve1_0Changed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::ThrottleCurve1_25Changed)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::ThrottleCurve1_50Changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::ThrottleCurve1_75Changed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::ThrottleCurve1_100Changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::ThrottleCurve2Changed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::ThrottleCurve2_0Changed)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::ThrottleCurve2_25Changed)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::ThrottleCurve2_50Changed)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::ThrottleCurve2_75Changed)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::ThrottleCurve2_100Changed)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::MixerValueRollChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::MixerValuePitchChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::MixerValueYawChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Curve2SourceChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer1TypeChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer1VectorChanged)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer1Vector_ThrottleCurve1Changed)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer1Vector_ThrottleCurve2Changed)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer1Vector_RollChanged)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer1Vector_PitchChanged)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer1Vector_YawChanged)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer2TypeChanged)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer2VectorChanged)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer2Vector_ThrottleCurve1Changed)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer2Vector_ThrottleCurve2Changed)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer2Vector_RollChanged)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer2Vector_PitchChanged)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer2Vector_YawChanged)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer3TypeChanged)) {
                *result = 34;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer3VectorChanged)) {
                *result = 35;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer3Vector_ThrottleCurve1Changed)) {
                *result = 36;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer3Vector_ThrottleCurve2Changed)) {
                *result = 37;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer3Vector_RollChanged)) {
                *result = 38;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer3Vector_PitchChanged)) {
                *result = 39;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer3Vector_YawChanged)) {
                *result = 40;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer4TypeChanged)) {
                *result = 41;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer4VectorChanged)) {
                *result = 42;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer4Vector_ThrottleCurve1Changed)) {
                *result = 43;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer4Vector_ThrottleCurve2Changed)) {
                *result = 44;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer4Vector_RollChanged)) {
                *result = 45;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer4Vector_PitchChanged)) {
                *result = 46;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer4Vector_YawChanged)) {
                *result = 47;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer5TypeChanged)) {
                *result = 48;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer5VectorChanged)) {
                *result = 49;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer5Vector_ThrottleCurve1Changed)) {
                *result = 50;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer5Vector_ThrottleCurve2Changed)) {
                *result = 51;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer5Vector_RollChanged)) {
                *result = 52;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer5Vector_PitchChanged)) {
                *result = 53;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer5Vector_YawChanged)) {
                *result = 54;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer6TypeChanged)) {
                *result = 55;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer6VectorChanged)) {
                *result = 56;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer6Vector_ThrottleCurve1Changed)) {
                *result = 57;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer6Vector_ThrottleCurve2Changed)) {
                *result = 58;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer6Vector_RollChanged)) {
                *result = 59;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer6Vector_PitchChanged)) {
                *result = 60;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer6Vector_YawChanged)) {
                *result = 61;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer7TypeChanged)) {
                *result = 62;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer7VectorChanged)) {
                *result = 63;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer7Vector_ThrottleCurve1Changed)) {
                *result = 64;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer7Vector_ThrottleCurve2Changed)) {
                *result = 65;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer7Vector_RollChanged)) {
                *result = 66;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer7Vector_PitchChanged)) {
                *result = 67;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer7Vector_YawChanged)) {
                *result = 68;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer8TypeChanged)) {
                *result = 69;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer8VectorChanged)) {
                *result = 70;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer8Vector_ThrottleCurve1Changed)) {
                *result = 71;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer8Vector_ThrottleCurve2Changed)) {
                *result = 72;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer8Vector_RollChanged)) {
                *result = 73;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer8Vector_PitchChanged)) {
                *result = 74;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer8Vector_YawChanged)) {
                *result = 75;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer9TypeChanged)) {
                *result = 76;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer9VectorChanged)) {
                *result = 77;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer9Vector_ThrottleCurve1Changed)) {
                *result = 78;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer9Vector_ThrottleCurve2Changed)) {
                *result = 79;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer9Vector_RollChanged)) {
                *result = 80;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer9Vector_PitchChanged)) {
                *result = 81;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer9Vector_YawChanged)) {
                *result = 82;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer10TypeChanged)) {
                *result = 83;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer10VectorChanged)) {
                *result = 84;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer10Vector_ThrottleCurve1Changed)) {
                *result = 85;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer10Vector_ThrottleCurve2Changed)) {
                *result = 86;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer10Vector_RollChanged)) {
                *result = 87;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer10Vector_PitchChanged)) {
                *result = 88;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer10Vector_YawChanged)) {
                *result = 89;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer11TypeChanged)) {
                *result = 90;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer11VectorChanged)) {
                *result = 91;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer11Vector_ThrottleCurve1Changed)) {
                *result = 92;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer11Vector_ThrottleCurve2Changed)) {
                *result = 93;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer11Vector_RollChanged)) {
                *result = 94;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer11Vector_PitchChanged)) {
                *result = 95;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer11Vector_YawChanged)) {
                *result = 96;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer12TypeChanged)) {
                *result = 97;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer12VectorChanged)) {
                *result = 98;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer12Vector_ThrottleCurve1Changed)) {
                *result = 99;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer12Vector_ThrottleCurve2Changed)) {
                *result = 100;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer12Vector_RollChanged)) {
                *result = 101;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer12Vector_PitchChanged)) {
                *result = 102;
                return;
            }
        }
        {
            using _t = void (MixerSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerSettings::Mixer12Vector_YawChanged)) {
                *result = 103;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MixerSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getMaxAccel(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getFeedForward(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getAccelTime(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getDecelTime(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getThrottleCurve1_0(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getThrottleCurve1_25(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getThrottleCurve1_50(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getThrottleCurve1_75(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getThrottleCurve1_100(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->getThrottleCurve2_0(); break;
        case 10: *reinterpret_cast< float*>(_v) = _t->getThrottleCurve2_25(); break;
        case 11: *reinterpret_cast< float*>(_v) = _t->getThrottleCurve2_50(); break;
        case 12: *reinterpret_cast< float*>(_v) = _t->getThrottleCurve2_75(); break;
        case 13: *reinterpret_cast< float*>(_v) = _t->getThrottleCurve2_100(); break;
        case 14: *reinterpret_cast< qint8*>(_v) = _t->getMixerValueRoll(); break;
        case 15: *reinterpret_cast< qint8*>(_v) = _t->getMixerValuePitch(); break;
        case 16: *reinterpret_cast< qint8*>(_v) = _t->getMixerValueYaw(); break;
        case 17: *reinterpret_cast< quint8*>(_v) = _t->getCurve2Source(); break;
        case 18: *reinterpret_cast< quint8*>(_v) = _t->getMixer1Type(); break;
        case 19: *reinterpret_cast< qint8*>(_v) = _t->getMixer1Vector_ThrottleCurve1(); break;
        case 20: *reinterpret_cast< qint8*>(_v) = _t->getMixer1Vector_ThrottleCurve2(); break;
        case 21: *reinterpret_cast< qint8*>(_v) = _t->getMixer1Vector_Roll(); break;
        case 22: *reinterpret_cast< qint8*>(_v) = _t->getMixer1Vector_Pitch(); break;
        case 23: *reinterpret_cast< qint8*>(_v) = _t->getMixer1Vector_Yaw(); break;
        case 24: *reinterpret_cast< quint8*>(_v) = _t->getMixer2Type(); break;
        case 25: *reinterpret_cast< qint8*>(_v) = _t->getMixer2Vector_ThrottleCurve1(); break;
        case 26: *reinterpret_cast< qint8*>(_v) = _t->getMixer2Vector_ThrottleCurve2(); break;
        case 27: *reinterpret_cast< qint8*>(_v) = _t->getMixer2Vector_Roll(); break;
        case 28: *reinterpret_cast< qint8*>(_v) = _t->getMixer2Vector_Pitch(); break;
        case 29: *reinterpret_cast< qint8*>(_v) = _t->getMixer2Vector_Yaw(); break;
        case 30: *reinterpret_cast< quint8*>(_v) = _t->getMixer3Type(); break;
        case 31: *reinterpret_cast< qint8*>(_v) = _t->getMixer3Vector_ThrottleCurve1(); break;
        case 32: *reinterpret_cast< qint8*>(_v) = _t->getMixer3Vector_ThrottleCurve2(); break;
        case 33: *reinterpret_cast< qint8*>(_v) = _t->getMixer3Vector_Roll(); break;
        case 34: *reinterpret_cast< qint8*>(_v) = _t->getMixer3Vector_Pitch(); break;
        case 35: *reinterpret_cast< qint8*>(_v) = _t->getMixer3Vector_Yaw(); break;
        case 36: *reinterpret_cast< quint8*>(_v) = _t->getMixer4Type(); break;
        case 37: *reinterpret_cast< qint8*>(_v) = _t->getMixer4Vector_ThrottleCurve1(); break;
        case 38: *reinterpret_cast< qint8*>(_v) = _t->getMixer4Vector_ThrottleCurve2(); break;
        case 39: *reinterpret_cast< qint8*>(_v) = _t->getMixer4Vector_Roll(); break;
        case 40: *reinterpret_cast< qint8*>(_v) = _t->getMixer4Vector_Pitch(); break;
        case 41: *reinterpret_cast< qint8*>(_v) = _t->getMixer4Vector_Yaw(); break;
        case 42: *reinterpret_cast< quint8*>(_v) = _t->getMixer5Type(); break;
        case 43: *reinterpret_cast< qint8*>(_v) = _t->getMixer5Vector_ThrottleCurve1(); break;
        case 44: *reinterpret_cast< qint8*>(_v) = _t->getMixer5Vector_ThrottleCurve2(); break;
        case 45: *reinterpret_cast< qint8*>(_v) = _t->getMixer5Vector_Roll(); break;
        case 46: *reinterpret_cast< qint8*>(_v) = _t->getMixer5Vector_Pitch(); break;
        case 47: *reinterpret_cast< qint8*>(_v) = _t->getMixer5Vector_Yaw(); break;
        case 48: *reinterpret_cast< quint8*>(_v) = _t->getMixer6Type(); break;
        case 49: *reinterpret_cast< qint8*>(_v) = _t->getMixer6Vector_ThrottleCurve1(); break;
        case 50: *reinterpret_cast< qint8*>(_v) = _t->getMixer6Vector_ThrottleCurve2(); break;
        case 51: *reinterpret_cast< qint8*>(_v) = _t->getMixer6Vector_Roll(); break;
        case 52: *reinterpret_cast< qint8*>(_v) = _t->getMixer6Vector_Pitch(); break;
        case 53: *reinterpret_cast< qint8*>(_v) = _t->getMixer6Vector_Yaw(); break;
        case 54: *reinterpret_cast< quint8*>(_v) = _t->getMixer7Type(); break;
        case 55: *reinterpret_cast< qint8*>(_v) = _t->getMixer7Vector_ThrottleCurve1(); break;
        case 56: *reinterpret_cast< qint8*>(_v) = _t->getMixer7Vector_ThrottleCurve2(); break;
        case 57: *reinterpret_cast< qint8*>(_v) = _t->getMixer7Vector_Roll(); break;
        case 58: *reinterpret_cast< qint8*>(_v) = _t->getMixer7Vector_Pitch(); break;
        case 59: *reinterpret_cast< qint8*>(_v) = _t->getMixer7Vector_Yaw(); break;
        case 60: *reinterpret_cast< quint8*>(_v) = _t->getMixer8Type(); break;
        case 61: *reinterpret_cast< qint8*>(_v) = _t->getMixer8Vector_ThrottleCurve1(); break;
        case 62: *reinterpret_cast< qint8*>(_v) = _t->getMixer8Vector_ThrottleCurve2(); break;
        case 63: *reinterpret_cast< qint8*>(_v) = _t->getMixer8Vector_Roll(); break;
        case 64: *reinterpret_cast< qint8*>(_v) = _t->getMixer8Vector_Pitch(); break;
        case 65: *reinterpret_cast< qint8*>(_v) = _t->getMixer8Vector_Yaw(); break;
        case 66: *reinterpret_cast< quint8*>(_v) = _t->getMixer9Type(); break;
        case 67: *reinterpret_cast< qint8*>(_v) = _t->getMixer9Vector_ThrottleCurve1(); break;
        case 68: *reinterpret_cast< qint8*>(_v) = _t->getMixer9Vector_ThrottleCurve2(); break;
        case 69: *reinterpret_cast< qint8*>(_v) = _t->getMixer9Vector_Roll(); break;
        case 70: *reinterpret_cast< qint8*>(_v) = _t->getMixer9Vector_Pitch(); break;
        case 71: *reinterpret_cast< qint8*>(_v) = _t->getMixer9Vector_Yaw(); break;
        case 72: *reinterpret_cast< quint8*>(_v) = _t->getMixer10Type(); break;
        case 73: *reinterpret_cast< qint8*>(_v) = _t->getMixer10Vector_ThrottleCurve1(); break;
        case 74: *reinterpret_cast< qint8*>(_v) = _t->getMixer10Vector_ThrottleCurve2(); break;
        case 75: *reinterpret_cast< qint8*>(_v) = _t->getMixer10Vector_Roll(); break;
        case 76: *reinterpret_cast< qint8*>(_v) = _t->getMixer10Vector_Pitch(); break;
        case 77: *reinterpret_cast< qint8*>(_v) = _t->getMixer10Vector_Yaw(); break;
        case 78: *reinterpret_cast< quint8*>(_v) = _t->getMixer11Type(); break;
        case 79: *reinterpret_cast< qint8*>(_v) = _t->getMixer11Vector_ThrottleCurve1(); break;
        case 80: *reinterpret_cast< qint8*>(_v) = _t->getMixer11Vector_ThrottleCurve2(); break;
        case 81: *reinterpret_cast< qint8*>(_v) = _t->getMixer11Vector_Roll(); break;
        case 82: *reinterpret_cast< qint8*>(_v) = _t->getMixer11Vector_Pitch(); break;
        case 83: *reinterpret_cast< qint8*>(_v) = _t->getMixer11Vector_Yaw(); break;
        case 84: *reinterpret_cast< quint8*>(_v) = _t->getMixer12Type(); break;
        case 85: *reinterpret_cast< qint8*>(_v) = _t->getMixer12Vector_ThrottleCurve1(); break;
        case 86: *reinterpret_cast< qint8*>(_v) = _t->getMixer12Vector_ThrottleCurve2(); break;
        case 87: *reinterpret_cast< qint8*>(_v) = _t->getMixer12Vector_Roll(); break;
        case 88: *reinterpret_cast< qint8*>(_v) = _t->getMixer12Vector_Pitch(); break;
        case 89: *reinterpret_cast< qint8*>(_v) = _t->getMixer12Vector_Yaw(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<MixerSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMaxAccel(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setFeedForward(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setAccelTime(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setDecelTime(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setThrottleCurve1_0(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setThrottleCurve1_25(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setThrottleCurve1_50(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setThrottleCurve1_75(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setThrottleCurve1_100(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setThrottleCurve2_0(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setThrottleCurve2_25(*reinterpret_cast< float*>(_v)); break;
        case 11: _t->setThrottleCurve2_50(*reinterpret_cast< float*>(_v)); break;
        case 12: _t->setThrottleCurve2_75(*reinterpret_cast< float*>(_v)); break;
        case 13: _t->setThrottleCurve2_100(*reinterpret_cast< float*>(_v)); break;
        case 14: _t->setMixerValueRoll(*reinterpret_cast< qint8*>(_v)); break;
        case 15: _t->setMixerValuePitch(*reinterpret_cast< qint8*>(_v)); break;
        case 16: _t->setMixerValueYaw(*reinterpret_cast< qint8*>(_v)); break;
        case 17: _t->setCurve2Source(*reinterpret_cast< quint8*>(_v)); break;
        case 18: _t->setMixer1Type(*reinterpret_cast< quint8*>(_v)); break;
        case 19: _t->setMixer1Vector_ThrottleCurve1(*reinterpret_cast< qint8*>(_v)); break;
        case 20: _t->setMixer1Vector_ThrottleCurve2(*reinterpret_cast< qint8*>(_v)); break;
        case 21: _t->setMixer1Vector_Roll(*reinterpret_cast< qint8*>(_v)); break;
        case 22: _t->setMixer1Vector_Pitch(*reinterpret_cast< qint8*>(_v)); break;
        case 23: _t->setMixer1Vector_Yaw(*reinterpret_cast< qint8*>(_v)); break;
        case 24: _t->setMixer2Type(*reinterpret_cast< quint8*>(_v)); break;
        case 25: _t->setMixer2Vector_ThrottleCurve1(*reinterpret_cast< qint8*>(_v)); break;
        case 26: _t->setMixer2Vector_ThrottleCurve2(*reinterpret_cast< qint8*>(_v)); break;
        case 27: _t->setMixer2Vector_Roll(*reinterpret_cast< qint8*>(_v)); break;
        case 28: _t->setMixer2Vector_Pitch(*reinterpret_cast< qint8*>(_v)); break;
        case 29: _t->setMixer2Vector_Yaw(*reinterpret_cast< qint8*>(_v)); break;
        case 30: _t->setMixer3Type(*reinterpret_cast< quint8*>(_v)); break;
        case 31: _t->setMixer3Vector_ThrottleCurve1(*reinterpret_cast< qint8*>(_v)); break;
        case 32: _t->setMixer3Vector_ThrottleCurve2(*reinterpret_cast< qint8*>(_v)); break;
        case 33: _t->setMixer3Vector_Roll(*reinterpret_cast< qint8*>(_v)); break;
        case 34: _t->setMixer3Vector_Pitch(*reinterpret_cast< qint8*>(_v)); break;
        case 35: _t->setMixer3Vector_Yaw(*reinterpret_cast< qint8*>(_v)); break;
        case 36: _t->setMixer4Type(*reinterpret_cast< quint8*>(_v)); break;
        case 37: _t->setMixer4Vector_ThrottleCurve1(*reinterpret_cast< qint8*>(_v)); break;
        case 38: _t->setMixer4Vector_ThrottleCurve2(*reinterpret_cast< qint8*>(_v)); break;
        case 39: _t->setMixer4Vector_Roll(*reinterpret_cast< qint8*>(_v)); break;
        case 40: _t->setMixer4Vector_Pitch(*reinterpret_cast< qint8*>(_v)); break;
        case 41: _t->setMixer4Vector_Yaw(*reinterpret_cast< qint8*>(_v)); break;
        case 42: _t->setMixer5Type(*reinterpret_cast< quint8*>(_v)); break;
        case 43: _t->setMixer5Vector_ThrottleCurve1(*reinterpret_cast< qint8*>(_v)); break;
        case 44: _t->setMixer5Vector_ThrottleCurve2(*reinterpret_cast< qint8*>(_v)); break;
        case 45: _t->setMixer5Vector_Roll(*reinterpret_cast< qint8*>(_v)); break;
        case 46: _t->setMixer5Vector_Pitch(*reinterpret_cast< qint8*>(_v)); break;
        case 47: _t->setMixer5Vector_Yaw(*reinterpret_cast< qint8*>(_v)); break;
        case 48: _t->setMixer6Type(*reinterpret_cast< quint8*>(_v)); break;
        case 49: _t->setMixer6Vector_ThrottleCurve1(*reinterpret_cast< qint8*>(_v)); break;
        case 50: _t->setMixer6Vector_ThrottleCurve2(*reinterpret_cast< qint8*>(_v)); break;
        case 51: _t->setMixer6Vector_Roll(*reinterpret_cast< qint8*>(_v)); break;
        case 52: _t->setMixer6Vector_Pitch(*reinterpret_cast< qint8*>(_v)); break;
        case 53: _t->setMixer6Vector_Yaw(*reinterpret_cast< qint8*>(_v)); break;
        case 54: _t->setMixer7Type(*reinterpret_cast< quint8*>(_v)); break;
        case 55: _t->setMixer7Vector_ThrottleCurve1(*reinterpret_cast< qint8*>(_v)); break;
        case 56: _t->setMixer7Vector_ThrottleCurve2(*reinterpret_cast< qint8*>(_v)); break;
        case 57: _t->setMixer7Vector_Roll(*reinterpret_cast< qint8*>(_v)); break;
        case 58: _t->setMixer7Vector_Pitch(*reinterpret_cast< qint8*>(_v)); break;
        case 59: _t->setMixer7Vector_Yaw(*reinterpret_cast< qint8*>(_v)); break;
        case 60: _t->setMixer8Type(*reinterpret_cast< quint8*>(_v)); break;
        case 61: _t->setMixer8Vector_ThrottleCurve1(*reinterpret_cast< qint8*>(_v)); break;
        case 62: _t->setMixer8Vector_ThrottleCurve2(*reinterpret_cast< qint8*>(_v)); break;
        case 63: _t->setMixer8Vector_Roll(*reinterpret_cast< qint8*>(_v)); break;
        case 64: _t->setMixer8Vector_Pitch(*reinterpret_cast< qint8*>(_v)); break;
        case 65: _t->setMixer8Vector_Yaw(*reinterpret_cast< qint8*>(_v)); break;
        case 66: _t->setMixer9Type(*reinterpret_cast< quint8*>(_v)); break;
        case 67: _t->setMixer9Vector_ThrottleCurve1(*reinterpret_cast< qint8*>(_v)); break;
        case 68: _t->setMixer9Vector_ThrottleCurve2(*reinterpret_cast< qint8*>(_v)); break;
        case 69: _t->setMixer9Vector_Roll(*reinterpret_cast< qint8*>(_v)); break;
        case 70: _t->setMixer9Vector_Pitch(*reinterpret_cast< qint8*>(_v)); break;
        case 71: _t->setMixer9Vector_Yaw(*reinterpret_cast< qint8*>(_v)); break;
        case 72: _t->setMixer10Type(*reinterpret_cast< quint8*>(_v)); break;
        case 73: _t->setMixer10Vector_ThrottleCurve1(*reinterpret_cast< qint8*>(_v)); break;
        case 74: _t->setMixer10Vector_ThrottleCurve2(*reinterpret_cast< qint8*>(_v)); break;
        case 75: _t->setMixer10Vector_Roll(*reinterpret_cast< qint8*>(_v)); break;
        case 76: _t->setMixer10Vector_Pitch(*reinterpret_cast< qint8*>(_v)); break;
        case 77: _t->setMixer10Vector_Yaw(*reinterpret_cast< qint8*>(_v)); break;
        case 78: _t->setMixer11Type(*reinterpret_cast< quint8*>(_v)); break;
        case 79: _t->setMixer11Vector_ThrottleCurve1(*reinterpret_cast< qint8*>(_v)); break;
        case 80: _t->setMixer11Vector_ThrottleCurve2(*reinterpret_cast< qint8*>(_v)); break;
        case 81: _t->setMixer11Vector_Roll(*reinterpret_cast< qint8*>(_v)); break;
        case 82: _t->setMixer11Vector_Pitch(*reinterpret_cast< qint8*>(_v)); break;
        case 83: _t->setMixer11Vector_Yaw(*reinterpret_cast< qint8*>(_v)); break;
        case 84: _t->setMixer12Type(*reinterpret_cast< quint8*>(_v)); break;
        case 85: _t->setMixer12Vector_ThrottleCurve1(*reinterpret_cast< qint8*>(_v)); break;
        case 86: _t->setMixer12Vector_ThrottleCurve2(*reinterpret_cast< qint8*>(_v)); break;
        case 87: _t->setMixer12Vector_Roll(*reinterpret_cast< qint8*>(_v)); break;
        case 88: _t->setMixer12Vector_Pitch(*reinterpret_cast< qint8*>(_v)); break;
        case 89: _t->setMixer12Vector_Yaw(*reinterpret_cast< qint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject MixerSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_MixerSettings.data,
    qt_meta_data_MixerSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MixerSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MixerSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MixerSettings.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int MixerSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 313)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 313;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 313)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 313;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 90;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 90;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 90;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 90;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 90;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 90;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void MixerSettings::MaxAccelChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MixerSettings::FeedForwardChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MixerSettings::AccelTimeChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MixerSettings::DecelTimeChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MixerSettings::ThrottleCurve1Changed(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MixerSettings::ThrottleCurve1_0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MixerSettings::ThrottleCurve1_25Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MixerSettings::ThrottleCurve1_50Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MixerSettings::ThrottleCurve1_75Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MixerSettings::ThrottleCurve1_100Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MixerSettings::ThrottleCurve2Changed(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MixerSettings::ThrottleCurve2_0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MixerSettings::ThrottleCurve2_25Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MixerSettings::ThrottleCurve2_50Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void MixerSettings::ThrottleCurve2_75Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void MixerSettings::ThrottleCurve2_100Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void MixerSettings::MixerValueRollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void MixerSettings::MixerValuePitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void MixerSettings::MixerValueYawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void MixerSettings::Curve2SourceChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void MixerSettings::Mixer1TypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void MixerSettings::Mixer1VectorChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void MixerSettings::Mixer1Vector_ThrottleCurve1Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void MixerSettings::Mixer1Vector_ThrottleCurve2Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void MixerSettings::Mixer1Vector_RollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void MixerSettings::Mixer1Vector_PitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void MixerSettings::Mixer1Vector_YawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void MixerSettings::Mixer2TypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void MixerSettings::Mixer2VectorChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void MixerSettings::Mixer2Vector_ThrottleCurve1Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void MixerSettings::Mixer2Vector_ThrottleCurve2Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void MixerSettings::Mixer2Vector_RollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void MixerSettings::Mixer2Vector_PitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void MixerSettings::Mixer2Vector_YawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void MixerSettings::Mixer3TypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void MixerSettings::Mixer3VectorChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 35, _a);
}

// SIGNAL 36
void MixerSettings::Mixer3Vector_ThrottleCurve1Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 36, _a);
}

// SIGNAL 37
void MixerSettings::Mixer3Vector_ThrottleCurve2Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 37, _a);
}

// SIGNAL 38
void MixerSettings::Mixer3Vector_RollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 38, _a);
}

// SIGNAL 39
void MixerSettings::Mixer3Vector_PitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 39, _a);
}

// SIGNAL 40
void MixerSettings::Mixer3Vector_YawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 40, _a);
}

// SIGNAL 41
void MixerSettings::Mixer4TypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 41, _a);
}

// SIGNAL 42
void MixerSettings::Mixer4VectorChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 42, _a);
}

// SIGNAL 43
void MixerSettings::Mixer4Vector_ThrottleCurve1Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 43, _a);
}

// SIGNAL 44
void MixerSettings::Mixer4Vector_ThrottleCurve2Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 44, _a);
}

// SIGNAL 45
void MixerSettings::Mixer4Vector_RollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 45, _a);
}

// SIGNAL 46
void MixerSettings::Mixer4Vector_PitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 46, _a);
}

// SIGNAL 47
void MixerSettings::Mixer4Vector_YawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 47, _a);
}

// SIGNAL 48
void MixerSettings::Mixer5TypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 48, _a);
}

// SIGNAL 49
void MixerSettings::Mixer5VectorChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 49, _a);
}

// SIGNAL 50
void MixerSettings::Mixer5Vector_ThrottleCurve1Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 50, _a);
}

// SIGNAL 51
void MixerSettings::Mixer5Vector_ThrottleCurve2Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 51, _a);
}

// SIGNAL 52
void MixerSettings::Mixer5Vector_RollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 52, _a);
}

// SIGNAL 53
void MixerSettings::Mixer5Vector_PitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 53, _a);
}

// SIGNAL 54
void MixerSettings::Mixer5Vector_YawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 54, _a);
}

// SIGNAL 55
void MixerSettings::Mixer6TypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 55, _a);
}

// SIGNAL 56
void MixerSettings::Mixer6VectorChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 56, _a);
}

// SIGNAL 57
void MixerSettings::Mixer6Vector_ThrottleCurve1Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 57, _a);
}

// SIGNAL 58
void MixerSettings::Mixer6Vector_ThrottleCurve2Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 58, _a);
}

// SIGNAL 59
void MixerSettings::Mixer6Vector_RollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 59, _a);
}

// SIGNAL 60
void MixerSettings::Mixer6Vector_PitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 60, _a);
}

// SIGNAL 61
void MixerSettings::Mixer6Vector_YawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 61, _a);
}

// SIGNAL 62
void MixerSettings::Mixer7TypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 62, _a);
}

// SIGNAL 63
void MixerSettings::Mixer7VectorChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 63, _a);
}

// SIGNAL 64
void MixerSettings::Mixer7Vector_ThrottleCurve1Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 64, _a);
}

// SIGNAL 65
void MixerSettings::Mixer7Vector_ThrottleCurve2Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 65, _a);
}

// SIGNAL 66
void MixerSettings::Mixer7Vector_RollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 66, _a);
}

// SIGNAL 67
void MixerSettings::Mixer7Vector_PitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 67, _a);
}

// SIGNAL 68
void MixerSettings::Mixer7Vector_YawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 68, _a);
}

// SIGNAL 69
void MixerSettings::Mixer8TypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 69, _a);
}

// SIGNAL 70
void MixerSettings::Mixer8VectorChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 70, _a);
}

// SIGNAL 71
void MixerSettings::Mixer8Vector_ThrottleCurve1Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 71, _a);
}

// SIGNAL 72
void MixerSettings::Mixer8Vector_ThrottleCurve2Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 72, _a);
}

// SIGNAL 73
void MixerSettings::Mixer8Vector_RollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 73, _a);
}

// SIGNAL 74
void MixerSettings::Mixer8Vector_PitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 74, _a);
}

// SIGNAL 75
void MixerSettings::Mixer8Vector_YawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 75, _a);
}

// SIGNAL 76
void MixerSettings::Mixer9TypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 76, _a);
}

// SIGNAL 77
void MixerSettings::Mixer9VectorChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 77, _a);
}

// SIGNAL 78
void MixerSettings::Mixer9Vector_ThrottleCurve1Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 78, _a);
}

// SIGNAL 79
void MixerSettings::Mixer9Vector_ThrottleCurve2Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 79, _a);
}

// SIGNAL 80
void MixerSettings::Mixer9Vector_RollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 80, _a);
}

// SIGNAL 81
void MixerSettings::Mixer9Vector_PitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 81, _a);
}

// SIGNAL 82
void MixerSettings::Mixer9Vector_YawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 82, _a);
}

// SIGNAL 83
void MixerSettings::Mixer10TypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 83, _a);
}

// SIGNAL 84
void MixerSettings::Mixer10VectorChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 84, _a);
}

// SIGNAL 85
void MixerSettings::Mixer10Vector_ThrottleCurve1Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 85, _a);
}

// SIGNAL 86
void MixerSettings::Mixer10Vector_ThrottleCurve2Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 86, _a);
}

// SIGNAL 87
void MixerSettings::Mixer10Vector_RollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 87, _a);
}

// SIGNAL 88
void MixerSettings::Mixer10Vector_PitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 88, _a);
}

// SIGNAL 89
void MixerSettings::Mixer10Vector_YawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 89, _a);
}

// SIGNAL 90
void MixerSettings::Mixer11TypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 90, _a);
}

// SIGNAL 91
void MixerSettings::Mixer11VectorChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 91, _a);
}

// SIGNAL 92
void MixerSettings::Mixer11Vector_ThrottleCurve1Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 92, _a);
}

// SIGNAL 93
void MixerSettings::Mixer11Vector_ThrottleCurve2Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 93, _a);
}

// SIGNAL 94
void MixerSettings::Mixer11Vector_RollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 94, _a);
}

// SIGNAL 95
void MixerSettings::Mixer11Vector_PitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 95, _a);
}

// SIGNAL 96
void MixerSettings::Mixer11Vector_YawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 96, _a);
}

// SIGNAL 97
void MixerSettings::Mixer12TypeChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 97, _a);
}

// SIGNAL 98
void MixerSettings::Mixer12VectorChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 98, _a);
}

// SIGNAL 99
void MixerSettings::Mixer12Vector_ThrottleCurve1Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 99, _a);
}

// SIGNAL 100
void MixerSettings::Mixer12Vector_ThrottleCurve2Changed(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 100, _a);
}

// SIGNAL 101
void MixerSettings::Mixer12Vector_RollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 101, _a);
}

// SIGNAL 102
void MixerSettings::Mixer12Vector_PitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 102, _a);
}

// SIGNAL 103
void MixerSettings::Mixer12Vector_YawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 103, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
