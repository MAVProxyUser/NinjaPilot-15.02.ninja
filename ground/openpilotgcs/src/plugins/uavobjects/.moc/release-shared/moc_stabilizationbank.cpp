/****************************************************************************
** Meta object code from reading C++ file 'stabilizationbank.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/stabilizationbank.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stabilizationbank.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StabilizationBank_t {
    QByteArrayData data[211];
    char stringdata0[3861];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StabilizationBank_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StabilizationBank_t qt_meta_stringdata_StabilizationBank = {
    {
QT_MOC_LITERAL(0, 0, 17), // "StabilizationBank"
QT_MOC_LITERAL(1, 18, 17), // "ManualRateChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 5), // "index"
QT_MOC_LITERAL(4, 43, 5), // "value"
QT_MOC_LITERAL(5, 49, 22), // "ManualRate_RollChanged"
QT_MOC_LITERAL(6, 72, 23), // "ManualRate_PitchChanged"
QT_MOC_LITERAL(7, 96, 21), // "ManualRate_YawChanged"
QT_MOC_LITERAL(8, 118, 18), // "MaximumRateChanged"
QT_MOC_LITERAL(9, 137, 23), // "MaximumRate_RollChanged"
QT_MOC_LITERAL(10, 161, 24), // "MaximumRate_PitchChanged"
QT_MOC_LITERAL(11, 186, 22), // "MaximumRate_YawChanged"
QT_MOC_LITERAL(12, 209, 18), // "RollRatePIDChanged"
QT_MOC_LITERAL(13, 228, 21), // "RollRatePID_KpChanged"
QT_MOC_LITERAL(14, 250, 21), // "RollRatePID_KiChanged"
QT_MOC_LITERAL(15, 272, 21), // "RollRatePID_KdChanged"
QT_MOC_LITERAL(16, 294, 25), // "RollRatePID_ILimitChanged"
QT_MOC_LITERAL(17, 320, 19), // "PitchRatePIDChanged"
QT_MOC_LITERAL(18, 340, 22), // "PitchRatePID_KpChanged"
QT_MOC_LITERAL(19, 363, 22), // "PitchRatePID_KiChanged"
QT_MOC_LITERAL(20, 386, 22), // "PitchRatePID_KdChanged"
QT_MOC_LITERAL(21, 409, 26), // "PitchRatePID_ILimitChanged"
QT_MOC_LITERAL(22, 436, 17), // "YawRatePIDChanged"
QT_MOC_LITERAL(23, 454, 20), // "YawRatePID_KpChanged"
QT_MOC_LITERAL(24, 475, 20), // "YawRatePID_KiChanged"
QT_MOC_LITERAL(25, 496, 20), // "YawRatePID_KdChanged"
QT_MOC_LITERAL(26, 517, 24), // "YawRatePID_ILimitChanged"
QT_MOC_LITERAL(27, 542, 13), // "RollPIChanged"
QT_MOC_LITERAL(28, 556, 16), // "RollPI_KpChanged"
QT_MOC_LITERAL(29, 573, 16), // "RollPI_KiChanged"
QT_MOC_LITERAL(30, 590, 20), // "RollPI_ILimitChanged"
QT_MOC_LITERAL(31, 611, 14), // "PitchPIChanged"
QT_MOC_LITERAL(32, 626, 17), // "PitchPI_KpChanged"
QT_MOC_LITERAL(33, 644, 17), // "PitchPI_KiChanged"
QT_MOC_LITERAL(34, 662, 21), // "PitchPI_ILimitChanged"
QT_MOC_LITERAL(35, 684, 12), // "YawPIChanged"
QT_MOC_LITERAL(36, 697, 15), // "YawPI_KpChanged"
QT_MOC_LITERAL(37, 713, 15), // "YawPI_KiChanged"
QT_MOC_LITERAL(38, 729, 19), // "YawPI_ILimitChanged"
QT_MOC_LITERAL(39, 749, 25), // "AcroInsanityFactorChanged"
QT_MOC_LITERAL(40, 775, 26), // "ThrustPIDScaleCurveChanged"
QT_MOC_LITERAL(41, 802, 28), // "ThrustPIDScaleCurve_0Changed"
QT_MOC_LITERAL(42, 831, 29), // "ThrustPIDScaleCurve_25Changed"
QT_MOC_LITERAL(43, 861, 29), // "ThrustPIDScaleCurve_50Changed"
QT_MOC_LITERAL(44, 891, 29), // "ThrustPIDScaleCurve_75Changed"
QT_MOC_LITERAL(45, 921, 30), // "ThrustPIDScaleCurve_100Changed"
QT_MOC_LITERAL(46, 952, 14), // "RollMaxChanged"
QT_MOC_LITERAL(47, 967, 15), // "PitchMaxChanged"
QT_MOC_LITERAL(48, 983, 13), // "YawMaxChanged"
QT_MOC_LITERAL(49, 997, 16), // "StickExpoChanged"
QT_MOC_LITERAL(50, 1014, 21), // "StickExpo_RollChanged"
QT_MOC_LITERAL(51, 1036, 22), // "StickExpo_PitchChanged"
QT_MOC_LITERAL(52, 1059, 20), // "StickExpo_YawChanged"
QT_MOC_LITERAL(53, 1080, 21), // "EnablePiroCompChanged"
QT_MOC_LITERAL(54, 1102, 29), // "EnableThrustPIDScalingChanged"
QT_MOC_LITERAL(55, 1132, 27), // "ThrustPIDScaleSourceChanged"
QT_MOC_LITERAL(56, 1160, 27), // "ThrustPIDScaleTargetChanged"
QT_MOC_LITERAL(57, 1188, 25), // "ThrustPIDScaleAxesChanged"
QT_MOC_LITERAL(58, 1214, 13), // "setManualRate"
QT_MOC_LITERAL(59, 1228, 18), // "setManualRate_Roll"
QT_MOC_LITERAL(60, 1247, 19), // "setManualRate_Pitch"
QT_MOC_LITERAL(61, 1267, 17), // "setManualRate_Yaw"
QT_MOC_LITERAL(62, 1285, 14), // "setMaximumRate"
QT_MOC_LITERAL(63, 1300, 19), // "setMaximumRate_Roll"
QT_MOC_LITERAL(64, 1320, 20), // "setMaximumRate_Pitch"
QT_MOC_LITERAL(65, 1341, 18), // "setMaximumRate_Yaw"
QT_MOC_LITERAL(66, 1360, 14), // "setRollRatePID"
QT_MOC_LITERAL(67, 1375, 17), // "setRollRatePID_Kp"
QT_MOC_LITERAL(68, 1393, 17), // "setRollRatePID_Ki"
QT_MOC_LITERAL(69, 1411, 17), // "setRollRatePID_Kd"
QT_MOC_LITERAL(70, 1429, 21), // "setRollRatePID_ILimit"
QT_MOC_LITERAL(71, 1451, 15), // "setPitchRatePID"
QT_MOC_LITERAL(72, 1467, 18), // "setPitchRatePID_Kp"
QT_MOC_LITERAL(73, 1486, 18), // "setPitchRatePID_Ki"
QT_MOC_LITERAL(74, 1505, 18), // "setPitchRatePID_Kd"
QT_MOC_LITERAL(75, 1524, 22), // "setPitchRatePID_ILimit"
QT_MOC_LITERAL(76, 1547, 13), // "setYawRatePID"
QT_MOC_LITERAL(77, 1561, 16), // "setYawRatePID_Kp"
QT_MOC_LITERAL(78, 1578, 16), // "setYawRatePID_Ki"
QT_MOC_LITERAL(79, 1595, 16), // "setYawRatePID_Kd"
QT_MOC_LITERAL(80, 1612, 20), // "setYawRatePID_ILimit"
QT_MOC_LITERAL(81, 1633, 9), // "setRollPI"
QT_MOC_LITERAL(82, 1643, 12), // "setRollPI_Kp"
QT_MOC_LITERAL(83, 1656, 12), // "setRollPI_Ki"
QT_MOC_LITERAL(84, 1669, 16), // "setRollPI_ILimit"
QT_MOC_LITERAL(85, 1686, 10), // "setPitchPI"
QT_MOC_LITERAL(86, 1697, 13), // "setPitchPI_Kp"
QT_MOC_LITERAL(87, 1711, 13), // "setPitchPI_Ki"
QT_MOC_LITERAL(88, 1725, 17), // "setPitchPI_ILimit"
QT_MOC_LITERAL(89, 1743, 8), // "setYawPI"
QT_MOC_LITERAL(90, 1752, 11), // "setYawPI_Kp"
QT_MOC_LITERAL(91, 1764, 11), // "setYawPI_Ki"
QT_MOC_LITERAL(92, 1776, 15), // "setYawPI_ILimit"
QT_MOC_LITERAL(93, 1792, 21), // "setAcroInsanityFactor"
QT_MOC_LITERAL(94, 1814, 22), // "setThrustPIDScaleCurve"
QT_MOC_LITERAL(95, 1837, 24), // "setThrustPIDScaleCurve_0"
QT_MOC_LITERAL(96, 1862, 25), // "setThrustPIDScaleCurve_25"
QT_MOC_LITERAL(97, 1888, 25), // "setThrustPIDScaleCurve_50"
QT_MOC_LITERAL(98, 1914, 25), // "setThrustPIDScaleCurve_75"
QT_MOC_LITERAL(99, 1940, 26), // "setThrustPIDScaleCurve_100"
QT_MOC_LITERAL(100, 1967, 10), // "setRollMax"
QT_MOC_LITERAL(101, 1978, 11), // "setPitchMax"
QT_MOC_LITERAL(102, 1990, 9), // "setYawMax"
QT_MOC_LITERAL(103, 2000, 12), // "setStickExpo"
QT_MOC_LITERAL(104, 2013, 17), // "setStickExpo_Roll"
QT_MOC_LITERAL(105, 2031, 18), // "setStickExpo_Pitch"
QT_MOC_LITERAL(106, 2050, 16), // "setStickExpo_Yaw"
QT_MOC_LITERAL(107, 2067, 17), // "setEnablePiroComp"
QT_MOC_LITERAL(108, 2085, 25), // "setEnableThrustPIDScaling"
QT_MOC_LITERAL(109, 2111, 23), // "setThrustPIDScaleSource"
QT_MOC_LITERAL(110, 2135, 23), // "setThrustPIDScaleTarget"
QT_MOC_LITERAL(111, 2159, 21), // "setThrustPIDScaleAxes"
QT_MOC_LITERAL(112, 2181, 17), // "emitNotifications"
QT_MOC_LITERAL(113, 2199, 13), // "getManualRate"
QT_MOC_LITERAL(114, 2213, 18), // "getManualRate_Roll"
QT_MOC_LITERAL(115, 2232, 19), // "getManualRate_Pitch"
QT_MOC_LITERAL(116, 2252, 17), // "getManualRate_Yaw"
QT_MOC_LITERAL(117, 2270, 14), // "getMaximumRate"
QT_MOC_LITERAL(118, 2285, 19), // "getMaximumRate_Roll"
QT_MOC_LITERAL(119, 2305, 20), // "getMaximumRate_Pitch"
QT_MOC_LITERAL(120, 2326, 18), // "getMaximumRate_Yaw"
QT_MOC_LITERAL(121, 2345, 14), // "getRollRatePID"
QT_MOC_LITERAL(122, 2360, 17), // "getRollRatePID_Kp"
QT_MOC_LITERAL(123, 2378, 17), // "getRollRatePID_Ki"
QT_MOC_LITERAL(124, 2396, 17), // "getRollRatePID_Kd"
QT_MOC_LITERAL(125, 2414, 21), // "getRollRatePID_ILimit"
QT_MOC_LITERAL(126, 2436, 15), // "getPitchRatePID"
QT_MOC_LITERAL(127, 2452, 18), // "getPitchRatePID_Kp"
QT_MOC_LITERAL(128, 2471, 18), // "getPitchRatePID_Ki"
QT_MOC_LITERAL(129, 2490, 18), // "getPitchRatePID_Kd"
QT_MOC_LITERAL(130, 2509, 22), // "getPitchRatePID_ILimit"
QT_MOC_LITERAL(131, 2532, 13), // "getYawRatePID"
QT_MOC_LITERAL(132, 2546, 16), // "getYawRatePID_Kp"
QT_MOC_LITERAL(133, 2563, 16), // "getYawRatePID_Ki"
QT_MOC_LITERAL(134, 2580, 16), // "getYawRatePID_Kd"
QT_MOC_LITERAL(135, 2597, 20), // "getYawRatePID_ILimit"
QT_MOC_LITERAL(136, 2618, 9), // "getRollPI"
QT_MOC_LITERAL(137, 2628, 12), // "getRollPI_Kp"
QT_MOC_LITERAL(138, 2641, 12), // "getRollPI_Ki"
QT_MOC_LITERAL(139, 2654, 16), // "getRollPI_ILimit"
QT_MOC_LITERAL(140, 2671, 10), // "getPitchPI"
QT_MOC_LITERAL(141, 2682, 13), // "getPitchPI_Kp"
QT_MOC_LITERAL(142, 2696, 13), // "getPitchPI_Ki"
QT_MOC_LITERAL(143, 2710, 17), // "getPitchPI_ILimit"
QT_MOC_LITERAL(144, 2728, 8), // "getYawPI"
QT_MOC_LITERAL(145, 2737, 11), // "getYawPI_Kp"
QT_MOC_LITERAL(146, 2749, 11), // "getYawPI_Ki"
QT_MOC_LITERAL(147, 2761, 15), // "getYawPI_ILimit"
QT_MOC_LITERAL(148, 2777, 21), // "getAcroInsanityFactor"
QT_MOC_LITERAL(149, 2799, 22), // "getThrustPIDScaleCurve"
QT_MOC_LITERAL(150, 2822, 24), // "getThrustPIDScaleCurve_0"
QT_MOC_LITERAL(151, 2847, 25), // "getThrustPIDScaleCurve_25"
QT_MOC_LITERAL(152, 2873, 25), // "getThrustPIDScaleCurve_50"
QT_MOC_LITERAL(153, 2899, 25), // "getThrustPIDScaleCurve_75"
QT_MOC_LITERAL(154, 2925, 26), // "getThrustPIDScaleCurve_100"
QT_MOC_LITERAL(155, 2952, 10), // "getRollMax"
QT_MOC_LITERAL(156, 2963, 11), // "getPitchMax"
QT_MOC_LITERAL(157, 2975, 9), // "getYawMax"
QT_MOC_LITERAL(158, 2985, 12), // "getStickExpo"
QT_MOC_LITERAL(159, 2998, 17), // "getStickExpo_Roll"
QT_MOC_LITERAL(160, 3016, 18), // "getStickExpo_Pitch"
QT_MOC_LITERAL(161, 3035, 16), // "getStickExpo_Yaw"
QT_MOC_LITERAL(162, 3052, 17), // "getEnablePiroComp"
QT_MOC_LITERAL(163, 3070, 25), // "getEnableThrustPIDScaling"
QT_MOC_LITERAL(164, 3096, 23), // "getThrustPIDScaleSource"
QT_MOC_LITERAL(165, 3120, 23), // "getThrustPIDScaleTarget"
QT_MOC_LITERAL(166, 3144, 21), // "getThrustPIDScaleAxes"
QT_MOC_LITERAL(167, 3166, 15), // "ManualRate_Roll"
QT_MOC_LITERAL(168, 3182, 16), // "ManualRate_Pitch"
QT_MOC_LITERAL(169, 3199, 14), // "ManualRate_Yaw"
QT_MOC_LITERAL(170, 3214, 16), // "MaximumRate_Roll"
QT_MOC_LITERAL(171, 3231, 17), // "MaximumRate_Pitch"
QT_MOC_LITERAL(172, 3249, 15), // "MaximumRate_Yaw"
QT_MOC_LITERAL(173, 3265, 14), // "RollRatePID_Kp"
QT_MOC_LITERAL(174, 3280, 14), // "RollRatePID_Ki"
QT_MOC_LITERAL(175, 3295, 14), // "RollRatePID_Kd"
QT_MOC_LITERAL(176, 3310, 18), // "RollRatePID_ILimit"
QT_MOC_LITERAL(177, 3329, 15), // "PitchRatePID_Kp"
QT_MOC_LITERAL(178, 3345, 15), // "PitchRatePID_Ki"
QT_MOC_LITERAL(179, 3361, 15), // "PitchRatePID_Kd"
QT_MOC_LITERAL(180, 3377, 19), // "PitchRatePID_ILimit"
QT_MOC_LITERAL(181, 3397, 13), // "YawRatePID_Kp"
QT_MOC_LITERAL(182, 3411, 13), // "YawRatePID_Ki"
QT_MOC_LITERAL(183, 3425, 13), // "YawRatePID_Kd"
QT_MOC_LITERAL(184, 3439, 17), // "YawRatePID_ILimit"
QT_MOC_LITERAL(185, 3457, 9), // "RollPI_Kp"
QT_MOC_LITERAL(186, 3467, 9), // "RollPI_Ki"
QT_MOC_LITERAL(187, 3477, 13), // "RollPI_ILimit"
QT_MOC_LITERAL(188, 3491, 10), // "PitchPI_Kp"
QT_MOC_LITERAL(189, 3502, 10), // "PitchPI_Ki"
QT_MOC_LITERAL(190, 3513, 14), // "PitchPI_ILimit"
QT_MOC_LITERAL(191, 3528, 8), // "YawPI_Kp"
QT_MOC_LITERAL(192, 3537, 8), // "YawPI_Ki"
QT_MOC_LITERAL(193, 3546, 12), // "YawPI_ILimit"
QT_MOC_LITERAL(194, 3559, 18), // "AcroInsanityFactor"
QT_MOC_LITERAL(195, 3578, 21), // "ThrustPIDScaleCurve_0"
QT_MOC_LITERAL(196, 3600, 22), // "ThrustPIDScaleCurve_25"
QT_MOC_LITERAL(197, 3623, 22), // "ThrustPIDScaleCurve_50"
QT_MOC_LITERAL(198, 3646, 22), // "ThrustPIDScaleCurve_75"
QT_MOC_LITERAL(199, 3669, 23), // "ThrustPIDScaleCurve_100"
QT_MOC_LITERAL(200, 3693, 7), // "RollMax"
QT_MOC_LITERAL(201, 3701, 8), // "PitchMax"
QT_MOC_LITERAL(202, 3710, 6), // "YawMax"
QT_MOC_LITERAL(203, 3717, 14), // "StickExpo_Roll"
QT_MOC_LITERAL(204, 3732, 15), // "StickExpo_Pitch"
QT_MOC_LITERAL(205, 3748, 13), // "StickExpo_Yaw"
QT_MOC_LITERAL(206, 3762, 14), // "EnablePiroComp"
QT_MOC_LITERAL(207, 3777, 22), // "EnableThrustPIDScaling"
QT_MOC_LITERAL(208, 3800, 20), // "ThrustPIDScaleSource"
QT_MOC_LITERAL(209, 3821, 20), // "ThrustPIDScaleTarget"
QT_MOC_LITERAL(210, 3842, 18) // "ThrustPIDScaleAxes"

    },
    "StabilizationBank\0ManualRateChanged\0"
    "\0index\0value\0ManualRate_RollChanged\0"
    "ManualRate_PitchChanged\0ManualRate_YawChanged\0"
    "MaximumRateChanged\0MaximumRate_RollChanged\0"
    "MaximumRate_PitchChanged\0"
    "MaximumRate_YawChanged\0RollRatePIDChanged\0"
    "RollRatePID_KpChanged\0RollRatePID_KiChanged\0"
    "RollRatePID_KdChanged\0RollRatePID_ILimitChanged\0"
    "PitchRatePIDChanged\0PitchRatePID_KpChanged\0"
    "PitchRatePID_KiChanged\0PitchRatePID_KdChanged\0"
    "PitchRatePID_ILimitChanged\0YawRatePIDChanged\0"
    "YawRatePID_KpChanged\0YawRatePID_KiChanged\0"
    "YawRatePID_KdChanged\0YawRatePID_ILimitChanged\0"
    "RollPIChanged\0RollPI_KpChanged\0"
    "RollPI_KiChanged\0RollPI_ILimitChanged\0"
    "PitchPIChanged\0PitchPI_KpChanged\0"
    "PitchPI_KiChanged\0PitchPI_ILimitChanged\0"
    "YawPIChanged\0YawPI_KpChanged\0"
    "YawPI_KiChanged\0YawPI_ILimitChanged\0"
    "AcroInsanityFactorChanged\0"
    "ThrustPIDScaleCurveChanged\0"
    "ThrustPIDScaleCurve_0Changed\0"
    "ThrustPIDScaleCurve_25Changed\0"
    "ThrustPIDScaleCurve_50Changed\0"
    "ThrustPIDScaleCurve_75Changed\0"
    "ThrustPIDScaleCurve_100Changed\0"
    "RollMaxChanged\0PitchMaxChanged\0"
    "YawMaxChanged\0StickExpoChanged\0"
    "StickExpo_RollChanged\0StickExpo_PitchChanged\0"
    "StickExpo_YawChanged\0EnablePiroCompChanged\0"
    "EnableThrustPIDScalingChanged\0"
    "ThrustPIDScaleSourceChanged\0"
    "ThrustPIDScaleTargetChanged\0"
    "ThrustPIDScaleAxesChanged\0setManualRate\0"
    "setManualRate_Roll\0setManualRate_Pitch\0"
    "setManualRate_Yaw\0setMaximumRate\0"
    "setMaximumRate_Roll\0setMaximumRate_Pitch\0"
    "setMaximumRate_Yaw\0setRollRatePID\0"
    "setRollRatePID_Kp\0setRollRatePID_Ki\0"
    "setRollRatePID_Kd\0setRollRatePID_ILimit\0"
    "setPitchRatePID\0setPitchRatePID_Kp\0"
    "setPitchRatePID_Ki\0setPitchRatePID_Kd\0"
    "setPitchRatePID_ILimit\0setYawRatePID\0"
    "setYawRatePID_Kp\0setYawRatePID_Ki\0"
    "setYawRatePID_Kd\0setYawRatePID_ILimit\0"
    "setRollPI\0setRollPI_Kp\0setRollPI_Ki\0"
    "setRollPI_ILimit\0setPitchPI\0setPitchPI_Kp\0"
    "setPitchPI_Ki\0setPitchPI_ILimit\0"
    "setYawPI\0setYawPI_Kp\0setYawPI_Ki\0"
    "setYawPI_ILimit\0setAcroInsanityFactor\0"
    "setThrustPIDScaleCurve\0setThrustPIDScaleCurve_0\0"
    "setThrustPIDScaleCurve_25\0"
    "setThrustPIDScaleCurve_50\0"
    "setThrustPIDScaleCurve_75\0"
    "setThrustPIDScaleCurve_100\0setRollMax\0"
    "setPitchMax\0setYawMax\0setStickExpo\0"
    "setStickExpo_Roll\0setStickExpo_Pitch\0"
    "setStickExpo_Yaw\0setEnablePiroComp\0"
    "setEnableThrustPIDScaling\0"
    "setThrustPIDScaleSource\0setThrustPIDScaleTarget\0"
    "setThrustPIDScaleAxes\0emitNotifications\0"
    "getManualRate\0getManualRate_Roll\0"
    "getManualRate_Pitch\0getManualRate_Yaw\0"
    "getMaximumRate\0getMaximumRate_Roll\0"
    "getMaximumRate_Pitch\0getMaximumRate_Yaw\0"
    "getRollRatePID\0getRollRatePID_Kp\0"
    "getRollRatePID_Ki\0getRollRatePID_Kd\0"
    "getRollRatePID_ILimit\0getPitchRatePID\0"
    "getPitchRatePID_Kp\0getPitchRatePID_Ki\0"
    "getPitchRatePID_Kd\0getPitchRatePID_ILimit\0"
    "getYawRatePID\0getYawRatePID_Kp\0"
    "getYawRatePID_Ki\0getYawRatePID_Kd\0"
    "getYawRatePID_ILimit\0getRollPI\0"
    "getRollPI_Kp\0getRollPI_Ki\0getRollPI_ILimit\0"
    "getPitchPI\0getPitchPI_Kp\0getPitchPI_Ki\0"
    "getPitchPI_ILimit\0getYawPI\0getYawPI_Kp\0"
    "getYawPI_Ki\0getYawPI_ILimit\0"
    "getAcroInsanityFactor\0getThrustPIDScaleCurve\0"
    "getThrustPIDScaleCurve_0\0"
    "getThrustPIDScaleCurve_25\0"
    "getThrustPIDScaleCurve_50\0"
    "getThrustPIDScaleCurve_75\0"
    "getThrustPIDScaleCurve_100\0getRollMax\0"
    "getPitchMax\0getYawMax\0getStickExpo\0"
    "getStickExpo_Roll\0getStickExpo_Pitch\0"
    "getStickExpo_Yaw\0getEnablePiroComp\0"
    "getEnableThrustPIDScaling\0"
    "getThrustPIDScaleSource\0getThrustPIDScaleTarget\0"
    "getThrustPIDScaleAxes\0ManualRate_Roll\0"
    "ManualRate_Pitch\0ManualRate_Yaw\0"
    "MaximumRate_Roll\0MaximumRate_Pitch\0"
    "MaximumRate_Yaw\0RollRatePID_Kp\0"
    "RollRatePID_Ki\0RollRatePID_Kd\0"
    "RollRatePID_ILimit\0PitchRatePID_Kp\0"
    "PitchRatePID_Ki\0PitchRatePID_Kd\0"
    "PitchRatePID_ILimit\0YawRatePID_Kp\0"
    "YawRatePID_Ki\0YawRatePID_Kd\0"
    "YawRatePID_ILimit\0RollPI_Kp\0RollPI_Ki\0"
    "RollPI_ILimit\0PitchPI_Kp\0PitchPI_Ki\0"
    "PitchPI_ILimit\0YawPI_Kp\0YawPI_Ki\0"
    "YawPI_ILimit\0AcroInsanityFactor\0"
    "ThrustPIDScaleCurve_0\0ThrustPIDScaleCurve_25\0"
    "ThrustPIDScaleCurve_50\0ThrustPIDScaleCurve_75\0"
    "ThrustPIDScaleCurve_100\0RollMax\0"
    "PitchMax\0YawMax\0StickExpo_Roll\0"
    "StickExpo_Pitch\0StickExpo_Yaw\0"
    "EnablePiroComp\0EnableThrustPIDScaling\0"
    "ThrustPIDScaleSource\0ThrustPIDScaleTarget\0"
    "ThrustPIDScaleAxes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StabilizationBank[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     163,   14, // methods
      44, 1268, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      54,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  829,    2, 0x06 /* Public */,
       5,    1,  834,    2, 0x06 /* Public */,
       6,    1,  837,    2, 0x06 /* Public */,
       7,    1,  840,    2, 0x06 /* Public */,
       8,    2,  843,    2, 0x06 /* Public */,
       9,    1,  848,    2, 0x06 /* Public */,
      10,    1,  851,    2, 0x06 /* Public */,
      11,    1,  854,    2, 0x06 /* Public */,
      12,    2,  857,    2, 0x06 /* Public */,
      13,    1,  862,    2, 0x06 /* Public */,
      14,    1,  865,    2, 0x06 /* Public */,
      15,    1,  868,    2, 0x06 /* Public */,
      16,    1,  871,    2, 0x06 /* Public */,
      17,    2,  874,    2, 0x06 /* Public */,
      18,    1,  879,    2, 0x06 /* Public */,
      19,    1,  882,    2, 0x06 /* Public */,
      20,    1,  885,    2, 0x06 /* Public */,
      21,    1,  888,    2, 0x06 /* Public */,
      22,    2,  891,    2, 0x06 /* Public */,
      23,    1,  896,    2, 0x06 /* Public */,
      24,    1,  899,    2, 0x06 /* Public */,
      25,    1,  902,    2, 0x06 /* Public */,
      26,    1,  905,    2, 0x06 /* Public */,
      27,    2,  908,    2, 0x06 /* Public */,
      28,    1,  913,    2, 0x06 /* Public */,
      29,    1,  916,    2, 0x06 /* Public */,
      30,    1,  919,    2, 0x06 /* Public */,
      31,    2,  922,    2, 0x06 /* Public */,
      32,    1,  927,    2, 0x06 /* Public */,
      33,    1,  930,    2, 0x06 /* Public */,
      34,    1,  933,    2, 0x06 /* Public */,
      35,    2,  936,    2, 0x06 /* Public */,
      36,    1,  941,    2, 0x06 /* Public */,
      37,    1,  944,    2, 0x06 /* Public */,
      38,    1,  947,    2, 0x06 /* Public */,
      39,    1,  950,    2, 0x06 /* Public */,
      40,    2,  953,    2, 0x06 /* Public */,
      41,    1,  958,    2, 0x06 /* Public */,
      42,    1,  961,    2, 0x06 /* Public */,
      43,    1,  964,    2, 0x06 /* Public */,
      44,    1,  967,    2, 0x06 /* Public */,
      45,    1,  970,    2, 0x06 /* Public */,
      46,    1,  973,    2, 0x06 /* Public */,
      47,    1,  976,    2, 0x06 /* Public */,
      48,    1,  979,    2, 0x06 /* Public */,
      49,    2,  982,    2, 0x06 /* Public */,
      50,    1,  987,    2, 0x06 /* Public */,
      51,    1,  990,    2, 0x06 /* Public */,
      52,    1,  993,    2, 0x06 /* Public */,
      53,    1,  996,    2, 0x06 /* Public */,
      54,    1,  999,    2, 0x06 /* Public */,
      55,    1, 1002,    2, 0x06 /* Public */,
      56,    1, 1005,    2, 0x06 /* Public */,
      57,    1, 1008,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      58,    2, 1011,    2, 0x0a /* Public */,
      59,    1, 1016,    2, 0x0a /* Public */,
      60,    1, 1019,    2, 0x0a /* Public */,
      61,    1, 1022,    2, 0x0a /* Public */,
      62,    2, 1025,    2, 0x0a /* Public */,
      63,    1, 1030,    2, 0x0a /* Public */,
      64,    1, 1033,    2, 0x0a /* Public */,
      65,    1, 1036,    2, 0x0a /* Public */,
      66,    2, 1039,    2, 0x0a /* Public */,
      67,    1, 1044,    2, 0x0a /* Public */,
      68,    1, 1047,    2, 0x0a /* Public */,
      69,    1, 1050,    2, 0x0a /* Public */,
      70,    1, 1053,    2, 0x0a /* Public */,
      71,    2, 1056,    2, 0x0a /* Public */,
      72,    1, 1061,    2, 0x0a /* Public */,
      73,    1, 1064,    2, 0x0a /* Public */,
      74,    1, 1067,    2, 0x0a /* Public */,
      75,    1, 1070,    2, 0x0a /* Public */,
      76,    2, 1073,    2, 0x0a /* Public */,
      77,    1, 1078,    2, 0x0a /* Public */,
      78,    1, 1081,    2, 0x0a /* Public */,
      79,    1, 1084,    2, 0x0a /* Public */,
      80,    1, 1087,    2, 0x0a /* Public */,
      81,    2, 1090,    2, 0x0a /* Public */,
      82,    1, 1095,    2, 0x0a /* Public */,
      83,    1, 1098,    2, 0x0a /* Public */,
      84,    1, 1101,    2, 0x0a /* Public */,
      85,    2, 1104,    2, 0x0a /* Public */,
      86,    1, 1109,    2, 0x0a /* Public */,
      87,    1, 1112,    2, 0x0a /* Public */,
      88,    1, 1115,    2, 0x0a /* Public */,
      89,    2, 1118,    2, 0x0a /* Public */,
      90,    1, 1123,    2, 0x0a /* Public */,
      91,    1, 1126,    2, 0x0a /* Public */,
      92,    1, 1129,    2, 0x0a /* Public */,
      93,    1, 1132,    2, 0x0a /* Public */,
      94,    2, 1135,    2, 0x0a /* Public */,
      95,    1, 1140,    2, 0x0a /* Public */,
      96,    1, 1143,    2, 0x0a /* Public */,
      97,    1, 1146,    2, 0x0a /* Public */,
      98,    1, 1149,    2, 0x0a /* Public */,
      99,    1, 1152,    2, 0x0a /* Public */,
     100,    1, 1155,    2, 0x0a /* Public */,
     101,    1, 1158,    2, 0x0a /* Public */,
     102,    1, 1161,    2, 0x0a /* Public */,
     103,    2, 1164,    2, 0x0a /* Public */,
     104,    1, 1169,    2, 0x0a /* Public */,
     105,    1, 1172,    2, 0x0a /* Public */,
     106,    1, 1175,    2, 0x0a /* Public */,
     107,    1, 1178,    2, 0x0a /* Public */,
     108,    1, 1181,    2, 0x0a /* Public */,
     109,    1, 1184,    2, 0x0a /* Public */,
     110,    1, 1187,    2, 0x0a /* Public */,
     111,    1, 1190,    2, 0x0a /* Public */,
     112,    0, 1193,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
     113,    1, 1194,    2, 0x02 /* Public */,
     114,    0, 1197,    2, 0x02 /* Public */,
     115,    0, 1198,    2, 0x02 /* Public */,
     116,    0, 1199,    2, 0x02 /* Public */,
     117,    1, 1200,    2, 0x02 /* Public */,
     118,    0, 1203,    2, 0x02 /* Public */,
     119,    0, 1204,    2, 0x02 /* Public */,
     120,    0, 1205,    2, 0x02 /* Public */,
     121,    1, 1206,    2, 0x02 /* Public */,
     122,    0, 1209,    2, 0x02 /* Public */,
     123,    0, 1210,    2, 0x02 /* Public */,
     124,    0, 1211,    2, 0x02 /* Public */,
     125,    0, 1212,    2, 0x02 /* Public */,
     126,    1, 1213,    2, 0x02 /* Public */,
     127,    0, 1216,    2, 0x02 /* Public */,
     128,    0, 1217,    2, 0x02 /* Public */,
     129,    0, 1218,    2, 0x02 /* Public */,
     130,    0, 1219,    2, 0x02 /* Public */,
     131,    1, 1220,    2, 0x02 /* Public */,
     132,    0, 1223,    2, 0x02 /* Public */,
     133,    0, 1224,    2, 0x02 /* Public */,
     134,    0, 1225,    2, 0x02 /* Public */,
     135,    0, 1226,    2, 0x02 /* Public */,
     136,    1, 1227,    2, 0x02 /* Public */,
     137,    0, 1230,    2, 0x02 /* Public */,
     138,    0, 1231,    2, 0x02 /* Public */,
     139,    0, 1232,    2, 0x02 /* Public */,
     140,    1, 1233,    2, 0x02 /* Public */,
     141,    0, 1236,    2, 0x02 /* Public */,
     142,    0, 1237,    2, 0x02 /* Public */,
     143,    0, 1238,    2, 0x02 /* Public */,
     144,    1, 1239,    2, 0x02 /* Public */,
     145,    0, 1242,    2, 0x02 /* Public */,
     146,    0, 1243,    2, 0x02 /* Public */,
     147,    0, 1244,    2, 0x02 /* Public */,
     148,    0, 1245,    2, 0x02 /* Public */,
     149,    1, 1246,    2, 0x02 /* Public */,
     150,    0, 1249,    2, 0x02 /* Public */,
     151,    0, 1250,    2, 0x02 /* Public */,
     152,    0, 1251,    2, 0x02 /* Public */,
     153,    0, 1252,    2, 0x02 /* Public */,
     154,    0, 1253,    2, 0x02 /* Public */,
     155,    0, 1254,    2, 0x02 /* Public */,
     156,    0, 1255,    2, 0x02 /* Public */,
     157,    0, 1256,    2, 0x02 /* Public */,
     158,    1, 1257,    2, 0x02 /* Public */,
     159,    0, 1260,    2, 0x02 /* Public */,
     160,    0, 1261,    2, 0x02 /* Public */,
     161,    0, 1262,    2, 0x02 /* Public */,
     162,    0, 1263,    2, 0x02 /* Public */,
     163,    0, 1264,    2, 0x02 /* Public */,
     164,    0, 1265,    2, 0x02 /* Public */,
     165,    0, 1266,    2, 0x02 /* Public */,
     166,    0, 1267,    2, 0x02 /* Public */,

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
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
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
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    3,    4,
    QMetaType::Void, QMetaType::SChar,    4,
    QMetaType::Void, QMetaType::SChar,    4,
    QMetaType::Void, QMetaType::SChar,    4,
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
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
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
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::SChar,    3,    4,
    QMetaType::Void, QMetaType::SChar,    4,
    QMetaType::Void, QMetaType::SChar,    4,
    QMetaType::Void, QMetaType::SChar,    4,
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
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
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
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::SChar, QMetaType::UInt,    3,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::SChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
     167, QMetaType::Float, 0x00495103,
     168, QMetaType::Float, 0x00495103,
     169, QMetaType::Float, 0x00495103,
     170, QMetaType::Float, 0x00495103,
     171, QMetaType::Float, 0x00495103,
     172, QMetaType::Float, 0x00495103,
     173, QMetaType::Float, 0x00495103,
     174, QMetaType::Float, 0x00495103,
     175, QMetaType::Float, 0x00495103,
     176, QMetaType::Float, 0x00495103,
     177, QMetaType::Float, 0x00495103,
     178, QMetaType::Float, 0x00495103,
     179, QMetaType::Float, 0x00495103,
     180, QMetaType::Float, 0x00495103,
     181, QMetaType::Float, 0x00495103,
     182, QMetaType::Float, 0x00495103,
     183, QMetaType::Float, 0x00495103,
     184, QMetaType::Float, 0x00495103,
     185, QMetaType::Float, 0x00495103,
     186, QMetaType::Float, 0x00495103,
     187, QMetaType::Float, 0x00495103,
     188, QMetaType::Float, 0x00495103,
     189, QMetaType::Float, 0x00495103,
     190, QMetaType::Float, 0x00495103,
     191, QMetaType::Float, 0x00495103,
     192, QMetaType::Float, 0x00495103,
     193, QMetaType::Float, 0x00495103,
     194, QMetaType::Float, 0x00495103,
     195, QMetaType::Float, 0x00495103,
     196, QMetaType::Float, 0x00495103,
     197, QMetaType::Float, 0x00495103,
     198, QMetaType::Float, 0x00495103,
     199, QMetaType::Float, 0x00495103,
     200, QMetaType::UChar, 0x00495103,
     201, QMetaType::UChar, 0x00495103,
     202, QMetaType::UChar, 0x00495103,
     203, QMetaType::SChar, 0x00495103,
     204, QMetaType::SChar, 0x00495103,
     205, QMetaType::SChar, 0x00495103,
     206, QMetaType::UChar, 0x00495103,
     207, QMetaType::UChar, 0x00495103,
     208, QMetaType::UChar, 0x00495103,
     209, QMetaType::UChar, 0x00495103,
     210, QMetaType::UChar, 0x00495103,

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
      12,
      14,
      15,
      16,
      17,
      19,
      20,
      21,
      22,
      24,
      25,
      26,
      28,
      29,
      30,
      32,
      33,
      34,
      35,
      37,
      38,
      39,
      40,
      41,
      42,
      43,
      44,
      46,
      47,
      48,
      49,
      50,
      51,
      52,
      53,

       0        // eod
};

void StabilizationBank::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StabilizationBank *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ManualRateChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->ManualRate_RollChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->ManualRate_PitchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->ManualRate_YawChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->MaximumRateChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->MaximumRate_RollChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->MaximumRate_PitchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->MaximumRate_YawChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->RollRatePIDChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 9: _t->RollRatePID_KpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->RollRatePID_KiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->RollRatePID_KdChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->RollRatePID_ILimitChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->PitchRatePIDChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 14: _t->PitchRatePID_KpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->PitchRatePID_KiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->PitchRatePID_KdChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 17: _t->PitchRatePID_ILimitChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->YawRatePIDChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 19: _t->YawRatePID_KpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->YawRatePID_KiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->YawRatePID_KdChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: _t->YawRatePID_ILimitChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->RollPIChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 24: _t->RollPI_KpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 25: _t->RollPI_KiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 26: _t->RollPI_ILimitChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->PitchPIChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 28: _t->PitchPI_KpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 29: _t->PitchPI_KiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 30: _t->PitchPI_ILimitChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 31: _t->YawPIChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 32: _t->YawPI_KpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 33: _t->YawPI_KiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 34: _t->YawPI_ILimitChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 35: _t->AcroInsanityFactorChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 36: _t->ThrustPIDScaleCurveChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 37: _t->ThrustPIDScaleCurve_0Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 38: _t->ThrustPIDScaleCurve_25Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 39: _t->ThrustPIDScaleCurve_50Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 40: _t->ThrustPIDScaleCurve_75Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 41: _t->ThrustPIDScaleCurve_100Changed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 42: _t->RollMaxChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 43: _t->PitchMaxChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 44: _t->YawMaxChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 45: _t->StickExpoChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 46: _t->StickExpo_RollChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 47: _t->StickExpo_PitchChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 48: _t->StickExpo_YawChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 49: _t->EnablePiroCompChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 50: _t->EnableThrustPIDScalingChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 51: _t->ThrustPIDScaleSourceChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 52: _t->ThrustPIDScaleTargetChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 53: _t->ThrustPIDScaleAxesChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 54: _t->setManualRate((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 55: _t->setManualRate_Roll((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 56: _t->setManualRate_Pitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 57: _t->setManualRate_Yaw((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 58: _t->setMaximumRate((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 59: _t->setMaximumRate_Roll((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 60: _t->setMaximumRate_Pitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 61: _t->setMaximumRate_Yaw((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 62: _t->setRollRatePID((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 63: _t->setRollRatePID_Kp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 64: _t->setRollRatePID_Ki((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 65: _t->setRollRatePID_Kd((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 66: _t->setRollRatePID_ILimit((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 67: _t->setPitchRatePID((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 68: _t->setPitchRatePID_Kp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 69: _t->setPitchRatePID_Ki((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 70: _t->setPitchRatePID_Kd((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 71: _t->setPitchRatePID_ILimit((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 72: _t->setYawRatePID((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 73: _t->setYawRatePID_Kp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 74: _t->setYawRatePID_Ki((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 75: _t->setYawRatePID_Kd((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 76: _t->setYawRatePID_ILimit((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 77: _t->setRollPI((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 78: _t->setRollPI_Kp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 79: _t->setRollPI_Ki((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 80: _t->setRollPI_ILimit((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 81: _t->setPitchPI((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 82: _t->setPitchPI_Kp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 83: _t->setPitchPI_Ki((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 84: _t->setPitchPI_ILimit((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 85: _t->setYawPI((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 86: _t->setYawPI_Kp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 87: _t->setYawPI_Ki((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 88: _t->setYawPI_ILimit((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 89: _t->setAcroInsanityFactor((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 90: _t->setThrustPIDScaleCurve((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 91: _t->setThrustPIDScaleCurve_0((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 92: _t->setThrustPIDScaleCurve_25((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 93: _t->setThrustPIDScaleCurve_50((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 94: _t->setThrustPIDScaleCurve_75((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 95: _t->setThrustPIDScaleCurve_100((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 96: _t->setRollMax((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 97: _t->setPitchMax((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 98: _t->setYawMax((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 99: _t->setStickExpo((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2]))); break;
        case 100: _t->setStickExpo_Roll((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 101: _t->setStickExpo_Pitch((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 102: _t->setStickExpo_Yaw((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 103: _t->setEnablePiroComp((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 104: _t->setEnableThrustPIDScaling((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 105: _t->setThrustPIDScaleSource((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 106: _t->setThrustPIDScaleTarget((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 107: _t->setThrustPIDScaleAxes((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 108: _t->emitNotifications(); break;
        case 109: { float _r = _t->getManualRate((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 110: { float _r = _t->getManualRate_Roll();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 111: { float _r = _t->getManualRate_Pitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 112: { float _r = _t->getManualRate_Yaw();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 113: { float _r = _t->getMaximumRate((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 114: { float _r = _t->getMaximumRate_Roll();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 115: { float _r = _t->getMaximumRate_Pitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 116: { float _r = _t->getMaximumRate_Yaw();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 117: { float _r = _t->getRollRatePID((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 118: { float _r = _t->getRollRatePID_Kp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 119: { float _r = _t->getRollRatePID_Ki();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 120: { float _r = _t->getRollRatePID_Kd();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 121: { float _r = _t->getRollRatePID_ILimit();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 122: { float _r = _t->getPitchRatePID((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 123: { float _r = _t->getPitchRatePID_Kp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 124: { float _r = _t->getPitchRatePID_Ki();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 125: { float _r = _t->getPitchRatePID_Kd();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 126: { float _r = _t->getPitchRatePID_ILimit();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 127: { float _r = _t->getYawRatePID((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 128: { float _r = _t->getYawRatePID_Kp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 129: { float _r = _t->getYawRatePID_Ki();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 130: { float _r = _t->getYawRatePID_Kd();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 131: { float _r = _t->getYawRatePID_ILimit();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 132: { float _r = _t->getRollPI((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 133: { float _r = _t->getRollPI_Kp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 134: { float _r = _t->getRollPI_Ki();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 135: { float _r = _t->getRollPI_ILimit();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 136: { float _r = _t->getPitchPI((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 137: { float _r = _t->getPitchPI_Kp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 138: { float _r = _t->getPitchPI_Ki();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 139: { float _r = _t->getPitchPI_ILimit();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 140: { float _r = _t->getYawPI((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 141: { float _r = _t->getYawPI_Kp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 142: { float _r = _t->getYawPI_Ki();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 143: { float _r = _t->getYawPI_ILimit();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 144: { float _r = _t->getAcroInsanityFactor();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 145: { float _r = _t->getThrustPIDScaleCurve((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 146: { float _r = _t->getThrustPIDScaleCurve_0();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 147: { float _r = _t->getThrustPIDScaleCurve_25();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 148: { float _r = _t->getThrustPIDScaleCurve_50();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 149: { float _r = _t->getThrustPIDScaleCurve_75();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 150: { float _r = _t->getThrustPIDScaleCurve_100();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 151: { quint8 _r = _t->getRollMax();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 152: { quint8 _r = _t->getPitchMax();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 153: { quint8 _r = _t->getYawMax();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 154: { qint8 _r = _t->getStickExpo((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 155: { qint8 _r = _t->getStickExpo_Roll();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 156: { qint8 _r = _t->getStickExpo_Pitch();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 157: { qint8 _r = _t->getStickExpo_Yaw();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 158: { quint8 _r = _t->getEnablePiroComp();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 159: { quint8 _r = _t->getEnableThrustPIDScaling();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 160: { quint8 _r = _t->getThrustPIDScaleSource();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 161: { quint8 _r = _t->getThrustPIDScaleTarget();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 162: { quint8 _r = _t->getThrustPIDScaleAxes();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StabilizationBank::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::ManualRateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::ManualRate_RollChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::ManualRate_PitchChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::ManualRate_YawChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::MaximumRateChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::MaximumRate_RollChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::MaximumRate_PitchChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::MaximumRate_YawChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::RollRatePIDChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::RollRatePID_KpChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::RollRatePID_KiChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::RollRatePID_KdChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::RollRatePID_ILimitChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::PitchRatePIDChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::PitchRatePID_KpChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::PitchRatePID_KiChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::PitchRatePID_KdChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::PitchRatePID_ILimitChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::YawRatePIDChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::YawRatePID_KpChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::YawRatePID_KiChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::YawRatePID_KdChanged)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::YawRatePID_ILimitChanged)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::RollPIChanged)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::RollPI_KpChanged)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::RollPI_KiChanged)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::RollPI_ILimitChanged)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::PitchPIChanged)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::PitchPI_KpChanged)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::PitchPI_KiChanged)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::PitchPI_ILimitChanged)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::YawPIChanged)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::YawPI_KpChanged)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::YawPI_KiChanged)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::YawPI_ILimitChanged)) {
                *result = 34;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::AcroInsanityFactorChanged)) {
                *result = 35;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::ThrustPIDScaleCurveChanged)) {
                *result = 36;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::ThrustPIDScaleCurve_0Changed)) {
                *result = 37;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::ThrustPIDScaleCurve_25Changed)) {
                *result = 38;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::ThrustPIDScaleCurve_50Changed)) {
                *result = 39;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::ThrustPIDScaleCurve_75Changed)) {
                *result = 40;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::ThrustPIDScaleCurve_100Changed)) {
                *result = 41;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::RollMaxChanged)) {
                *result = 42;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::PitchMaxChanged)) {
                *result = 43;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::YawMaxChanged)) {
                *result = 44;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint32 , qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::StickExpoChanged)) {
                *result = 45;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::StickExpo_RollChanged)) {
                *result = 46;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::StickExpo_PitchChanged)) {
                *result = 47;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::StickExpo_YawChanged)) {
                *result = 48;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::EnablePiroCompChanged)) {
                *result = 49;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::EnableThrustPIDScalingChanged)) {
                *result = 50;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::ThrustPIDScaleSourceChanged)) {
                *result = 51;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::ThrustPIDScaleTargetChanged)) {
                *result = 52;
                return;
            }
        }
        {
            using _t = void (StabilizationBank::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationBank::ThrustPIDScaleAxesChanged)) {
                *result = 53;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<StabilizationBank *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getManualRate_Roll(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getManualRate_Pitch(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getManualRate_Yaw(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getMaximumRate_Roll(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getMaximumRate_Pitch(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getMaximumRate_Yaw(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getRollRatePID_Kp(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getRollRatePID_Ki(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getRollRatePID_Kd(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->getRollRatePID_ILimit(); break;
        case 10: *reinterpret_cast< float*>(_v) = _t->getPitchRatePID_Kp(); break;
        case 11: *reinterpret_cast< float*>(_v) = _t->getPitchRatePID_Ki(); break;
        case 12: *reinterpret_cast< float*>(_v) = _t->getPitchRatePID_Kd(); break;
        case 13: *reinterpret_cast< float*>(_v) = _t->getPitchRatePID_ILimit(); break;
        case 14: *reinterpret_cast< float*>(_v) = _t->getYawRatePID_Kp(); break;
        case 15: *reinterpret_cast< float*>(_v) = _t->getYawRatePID_Ki(); break;
        case 16: *reinterpret_cast< float*>(_v) = _t->getYawRatePID_Kd(); break;
        case 17: *reinterpret_cast< float*>(_v) = _t->getYawRatePID_ILimit(); break;
        case 18: *reinterpret_cast< float*>(_v) = _t->getRollPI_Kp(); break;
        case 19: *reinterpret_cast< float*>(_v) = _t->getRollPI_Ki(); break;
        case 20: *reinterpret_cast< float*>(_v) = _t->getRollPI_ILimit(); break;
        case 21: *reinterpret_cast< float*>(_v) = _t->getPitchPI_Kp(); break;
        case 22: *reinterpret_cast< float*>(_v) = _t->getPitchPI_Ki(); break;
        case 23: *reinterpret_cast< float*>(_v) = _t->getPitchPI_ILimit(); break;
        case 24: *reinterpret_cast< float*>(_v) = _t->getYawPI_Kp(); break;
        case 25: *reinterpret_cast< float*>(_v) = _t->getYawPI_Ki(); break;
        case 26: *reinterpret_cast< float*>(_v) = _t->getYawPI_ILimit(); break;
        case 27: *reinterpret_cast< float*>(_v) = _t->getAcroInsanityFactor(); break;
        case 28: *reinterpret_cast< float*>(_v) = _t->getThrustPIDScaleCurve_0(); break;
        case 29: *reinterpret_cast< float*>(_v) = _t->getThrustPIDScaleCurve_25(); break;
        case 30: *reinterpret_cast< float*>(_v) = _t->getThrustPIDScaleCurve_50(); break;
        case 31: *reinterpret_cast< float*>(_v) = _t->getThrustPIDScaleCurve_75(); break;
        case 32: *reinterpret_cast< float*>(_v) = _t->getThrustPIDScaleCurve_100(); break;
        case 33: *reinterpret_cast< quint8*>(_v) = _t->getRollMax(); break;
        case 34: *reinterpret_cast< quint8*>(_v) = _t->getPitchMax(); break;
        case 35: *reinterpret_cast< quint8*>(_v) = _t->getYawMax(); break;
        case 36: *reinterpret_cast< qint8*>(_v) = _t->getStickExpo_Roll(); break;
        case 37: *reinterpret_cast< qint8*>(_v) = _t->getStickExpo_Pitch(); break;
        case 38: *reinterpret_cast< qint8*>(_v) = _t->getStickExpo_Yaw(); break;
        case 39: *reinterpret_cast< quint8*>(_v) = _t->getEnablePiroComp(); break;
        case 40: *reinterpret_cast< quint8*>(_v) = _t->getEnableThrustPIDScaling(); break;
        case 41: *reinterpret_cast< quint8*>(_v) = _t->getThrustPIDScaleSource(); break;
        case 42: *reinterpret_cast< quint8*>(_v) = _t->getThrustPIDScaleTarget(); break;
        case 43: *reinterpret_cast< quint8*>(_v) = _t->getThrustPIDScaleAxes(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<StabilizationBank *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setManualRate_Roll(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setManualRate_Pitch(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setManualRate_Yaw(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setMaximumRate_Roll(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setMaximumRate_Pitch(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setMaximumRate_Yaw(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setRollRatePID_Kp(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setRollRatePID_Ki(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setRollRatePID_Kd(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setRollRatePID_ILimit(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setPitchRatePID_Kp(*reinterpret_cast< float*>(_v)); break;
        case 11: _t->setPitchRatePID_Ki(*reinterpret_cast< float*>(_v)); break;
        case 12: _t->setPitchRatePID_Kd(*reinterpret_cast< float*>(_v)); break;
        case 13: _t->setPitchRatePID_ILimit(*reinterpret_cast< float*>(_v)); break;
        case 14: _t->setYawRatePID_Kp(*reinterpret_cast< float*>(_v)); break;
        case 15: _t->setYawRatePID_Ki(*reinterpret_cast< float*>(_v)); break;
        case 16: _t->setYawRatePID_Kd(*reinterpret_cast< float*>(_v)); break;
        case 17: _t->setYawRatePID_ILimit(*reinterpret_cast< float*>(_v)); break;
        case 18: _t->setRollPI_Kp(*reinterpret_cast< float*>(_v)); break;
        case 19: _t->setRollPI_Ki(*reinterpret_cast< float*>(_v)); break;
        case 20: _t->setRollPI_ILimit(*reinterpret_cast< float*>(_v)); break;
        case 21: _t->setPitchPI_Kp(*reinterpret_cast< float*>(_v)); break;
        case 22: _t->setPitchPI_Ki(*reinterpret_cast< float*>(_v)); break;
        case 23: _t->setPitchPI_ILimit(*reinterpret_cast< float*>(_v)); break;
        case 24: _t->setYawPI_Kp(*reinterpret_cast< float*>(_v)); break;
        case 25: _t->setYawPI_Ki(*reinterpret_cast< float*>(_v)); break;
        case 26: _t->setYawPI_ILimit(*reinterpret_cast< float*>(_v)); break;
        case 27: _t->setAcroInsanityFactor(*reinterpret_cast< float*>(_v)); break;
        case 28: _t->setThrustPIDScaleCurve_0(*reinterpret_cast< float*>(_v)); break;
        case 29: _t->setThrustPIDScaleCurve_25(*reinterpret_cast< float*>(_v)); break;
        case 30: _t->setThrustPIDScaleCurve_50(*reinterpret_cast< float*>(_v)); break;
        case 31: _t->setThrustPIDScaleCurve_75(*reinterpret_cast< float*>(_v)); break;
        case 32: _t->setThrustPIDScaleCurve_100(*reinterpret_cast< float*>(_v)); break;
        case 33: _t->setRollMax(*reinterpret_cast< quint8*>(_v)); break;
        case 34: _t->setPitchMax(*reinterpret_cast< quint8*>(_v)); break;
        case 35: _t->setYawMax(*reinterpret_cast< quint8*>(_v)); break;
        case 36: _t->setStickExpo_Roll(*reinterpret_cast< qint8*>(_v)); break;
        case 37: _t->setStickExpo_Pitch(*reinterpret_cast< qint8*>(_v)); break;
        case 38: _t->setStickExpo_Yaw(*reinterpret_cast< qint8*>(_v)); break;
        case 39: _t->setEnablePiroComp(*reinterpret_cast< quint8*>(_v)); break;
        case 40: _t->setEnableThrustPIDScaling(*reinterpret_cast< quint8*>(_v)); break;
        case 41: _t->setThrustPIDScaleSource(*reinterpret_cast< quint8*>(_v)); break;
        case 42: _t->setThrustPIDScaleTarget(*reinterpret_cast< quint8*>(_v)); break;
        case 43: _t->setThrustPIDScaleAxes(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject StabilizationBank::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_StabilizationBank.data,
    qt_meta_data_StabilizationBank,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StabilizationBank::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StabilizationBank::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StabilizationBank.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int StabilizationBank::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 163)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 163;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 163)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 163;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 44;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 44;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 44;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 44;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 44;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 44;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void StabilizationBank::ManualRateChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StabilizationBank::ManualRate_RollChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StabilizationBank::ManualRate_PitchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void StabilizationBank::ManualRate_YawChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void StabilizationBank::MaximumRateChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void StabilizationBank::MaximumRate_RollChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void StabilizationBank::MaximumRate_PitchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void StabilizationBank::MaximumRate_YawChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void StabilizationBank::RollRatePIDChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void StabilizationBank::RollRatePID_KpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void StabilizationBank::RollRatePID_KiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void StabilizationBank::RollRatePID_KdChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void StabilizationBank::RollRatePID_ILimitChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void StabilizationBank::PitchRatePIDChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void StabilizationBank::PitchRatePID_KpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void StabilizationBank::PitchRatePID_KiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void StabilizationBank::PitchRatePID_KdChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void StabilizationBank::PitchRatePID_ILimitChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void StabilizationBank::YawRatePIDChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void StabilizationBank::YawRatePID_KpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void StabilizationBank::YawRatePID_KiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void StabilizationBank::YawRatePID_KdChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void StabilizationBank::YawRatePID_ILimitChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void StabilizationBank::RollPIChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void StabilizationBank::RollPI_KpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void StabilizationBank::RollPI_KiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void StabilizationBank::RollPI_ILimitChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void StabilizationBank::PitchPIChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void StabilizationBank::PitchPI_KpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void StabilizationBank::PitchPI_KiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void StabilizationBank::PitchPI_ILimitChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void StabilizationBank::YawPIChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void StabilizationBank::YawPI_KpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void StabilizationBank::YawPI_KiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void StabilizationBank::YawPI_ILimitChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void StabilizationBank::AcroInsanityFactorChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 35, _a);
}

// SIGNAL 36
void StabilizationBank::ThrustPIDScaleCurveChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 36, _a);
}

// SIGNAL 37
void StabilizationBank::ThrustPIDScaleCurve_0Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 37, _a);
}

// SIGNAL 38
void StabilizationBank::ThrustPIDScaleCurve_25Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 38, _a);
}

// SIGNAL 39
void StabilizationBank::ThrustPIDScaleCurve_50Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 39, _a);
}

// SIGNAL 40
void StabilizationBank::ThrustPIDScaleCurve_75Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 40, _a);
}

// SIGNAL 41
void StabilizationBank::ThrustPIDScaleCurve_100Changed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 41, _a);
}

// SIGNAL 42
void StabilizationBank::RollMaxChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 42, _a);
}

// SIGNAL 43
void StabilizationBank::PitchMaxChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 43, _a);
}

// SIGNAL 44
void StabilizationBank::YawMaxChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 44, _a);
}

// SIGNAL 45
void StabilizationBank::StickExpoChanged(quint32 _t1, qint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 45, _a);
}

// SIGNAL 46
void StabilizationBank::StickExpo_RollChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 46, _a);
}

// SIGNAL 47
void StabilizationBank::StickExpo_PitchChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 47, _a);
}

// SIGNAL 48
void StabilizationBank::StickExpo_YawChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 48, _a);
}

// SIGNAL 49
void StabilizationBank::EnablePiroCompChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 49, _a);
}

// SIGNAL 50
void StabilizationBank::EnableThrustPIDScalingChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 50, _a);
}

// SIGNAL 51
void StabilizationBank::ThrustPIDScaleSourceChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 51, _a);
}

// SIGNAL 52
void StabilizationBank::ThrustPIDScaleTargetChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 52, _a);
}

// SIGNAL 53
void StabilizationBank::ThrustPIDScaleAxesChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 53, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
