/****************************************************************************
** Meta object code from reading C++ file 'vtolpathfollowersettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/vtolpathfollowersettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vtolpathfollowersettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VtolPathFollowerSettings_t {
    QByteArrayData data[182];
    char stringdata0[4293];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VtolPathFollowerSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VtolPathFollowerSettings_t qt_meta_stringdata_VtolPathFollowerSettings = {
    {
QT_MOC_LITERAL(0, 0, 24), // "VtolPathFollowerSettings"
QT_MOC_LITERAL(1, 25, 23), // "HorizontalVelMaxChanged"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 5), // "value"
QT_MOC_LITERAL(4, 56, 21), // "VerticalVelMaxChanged"
QT_MOC_LITERAL(5, 78, 24), // "CourseFeedForwardChanged"
QT_MOC_LITERAL(6, 103, 21), // "HorizontalPosPChanged"
QT_MOC_LITERAL(7, 125, 19), // "VerticalPosPChanged"
QT_MOC_LITERAL(8, 145, 23), // "HorizontalVelPIDChanged"
QT_MOC_LITERAL(9, 169, 5), // "index"
QT_MOC_LITERAL(10, 175, 26), // "HorizontalVelPID_KpChanged"
QT_MOC_LITERAL(11, 202, 26), // "HorizontalVelPID_KiChanged"
QT_MOC_LITERAL(12, 229, 26), // "HorizontalVelPID_KdChanged"
QT_MOC_LITERAL(13, 256, 30), // "HorizontalVelPID_ILimitChanged"
QT_MOC_LITERAL(14, 287, 21), // "VerticalVelPIDChanged"
QT_MOC_LITERAL(15, 309, 24), // "VerticalVelPID_KpChanged"
QT_MOC_LITERAL(16, 334, 24), // "VerticalVelPID_KiChanged"
QT_MOC_LITERAL(17, 359, 24), // "VerticalVelPID_KdChanged"
QT_MOC_LITERAL(18, 384, 28), // "VerticalVelPID_ILimitChanged"
QT_MOC_LITERAL(19, 413, 19), // "ThrustLimitsChanged"
QT_MOC_LITERAL(20, 433, 23), // "ThrustLimits_MinChanged"
QT_MOC_LITERAL(21, 457, 27), // "ThrustLimits_NeutralChanged"
QT_MOC_LITERAL(22, 485, 23), // "ThrustLimits_MaxChanged"
QT_MOC_LITERAL(23, 509, 26), // "VelocityFeedforwardChanged"
QT_MOC_LITERAL(24, 536, 42), // "FlyawayEmergencyFallbackTrigg..."
QT_MOC_LITERAL(25, 579, 32), // "EmergencyFallbackAttitudeChanged"
QT_MOC_LITERAL(26, 612, 37), // "EmergencyFallbackAttitude_Rol..."
QT_MOC_LITERAL(27, 650, 38), // "EmergencyFallbackAttitude_Pit..."
QT_MOC_LITERAL(28, 689, 31), // "EmergencyFallbackYawRateChanged"
QT_MOC_LITERAL(29, 721, 34), // "EmergencyFallbackYawRate_kPCh..."
QT_MOC_LITERAL(30, 756, 35), // "EmergencyFallbackYawRate_MaxC..."
QT_MOC_LITERAL(31, 792, 19), // "MaxRollPitchChanged"
QT_MOC_LITERAL(32, 812, 16), // "BrakeRateChanged"
QT_MOC_LITERAL(33, 829, 20), // "BrakeMaxPitchChanged"
QT_MOC_LITERAL(34, 850, 28), // "BrakeHorizontalVelPIDChanged"
QT_MOC_LITERAL(35, 879, 31), // "BrakeHorizontalVelPID_KpChanged"
QT_MOC_LITERAL(36, 911, 31), // "BrakeHorizontalVelPID_KiChanged"
QT_MOC_LITERAL(37, 943, 31), // "BrakeHorizontalVelPID_KdChanged"
QT_MOC_LITERAL(38, 975, 35), // "BrakeHorizontalVelPID_ILimitC..."
QT_MOC_LITERAL(39, 1011, 31), // "BrakeVelocityFeedforwardChanged"
QT_MOC_LITERAL(40, 1043, 25), // "LandVerticalVelPIDChanged"
QT_MOC_LITERAL(41, 1069, 28), // "LandVerticalVelPID_KpChanged"
QT_MOC_LITERAL(42, 1098, 28), // "LandVerticalVelPID_KiChanged"
QT_MOC_LITERAL(43, 1127, 28), // "LandVerticalVelPID_KdChanged"
QT_MOC_LITERAL(44, 1156, 30), // "LandVerticalVelPID_BetaChanged"
QT_MOC_LITERAL(45, 1187, 19), // "UpdatePeriodChanged"
QT_MOC_LITERAL(46, 1207, 25), // "TreatCustomCraftAsChanged"
QT_MOC_LITERAL(47, 1233, 20), // "ThrustControlChanged"
QT_MOC_LITERAL(48, 1254, 17), // "YawControlChanged"
QT_MOC_LITERAL(49, 1272, 31), // "FlyawayEmergencyFallbackChanged"
QT_MOC_LITERAL(50, 1304, 19), // "setHorizontalVelMax"
QT_MOC_LITERAL(51, 1324, 17), // "setVerticalVelMax"
QT_MOC_LITERAL(52, 1342, 20), // "setCourseFeedForward"
QT_MOC_LITERAL(53, 1363, 17), // "setHorizontalPosP"
QT_MOC_LITERAL(54, 1381, 15), // "setVerticalPosP"
QT_MOC_LITERAL(55, 1397, 19), // "setHorizontalVelPID"
QT_MOC_LITERAL(56, 1417, 22), // "setHorizontalVelPID_Kp"
QT_MOC_LITERAL(57, 1440, 22), // "setHorizontalVelPID_Ki"
QT_MOC_LITERAL(58, 1463, 22), // "setHorizontalVelPID_Kd"
QT_MOC_LITERAL(59, 1486, 26), // "setHorizontalVelPID_ILimit"
QT_MOC_LITERAL(60, 1513, 17), // "setVerticalVelPID"
QT_MOC_LITERAL(61, 1531, 20), // "setVerticalVelPID_Kp"
QT_MOC_LITERAL(62, 1552, 20), // "setVerticalVelPID_Ki"
QT_MOC_LITERAL(63, 1573, 20), // "setVerticalVelPID_Kd"
QT_MOC_LITERAL(64, 1594, 24), // "setVerticalVelPID_ILimit"
QT_MOC_LITERAL(65, 1619, 15), // "setThrustLimits"
QT_MOC_LITERAL(66, 1635, 19), // "setThrustLimits_Min"
QT_MOC_LITERAL(67, 1655, 23), // "setThrustLimits_Neutral"
QT_MOC_LITERAL(68, 1679, 19), // "setThrustLimits_Max"
QT_MOC_LITERAL(69, 1699, 22), // "setVelocityFeedforward"
QT_MOC_LITERAL(70, 1722, 38), // "setFlyawayEmergencyFallbackTr..."
QT_MOC_LITERAL(71, 1761, 28), // "setEmergencyFallbackAttitude"
QT_MOC_LITERAL(72, 1790, 33), // "setEmergencyFallbackAttitude_..."
QT_MOC_LITERAL(73, 1824, 34), // "setEmergencyFallbackAttitude_..."
QT_MOC_LITERAL(74, 1859, 27), // "setEmergencyFallbackYawRate"
QT_MOC_LITERAL(75, 1887, 30), // "setEmergencyFallbackYawRate_kP"
QT_MOC_LITERAL(76, 1918, 31), // "setEmergencyFallbackYawRate_Max"
QT_MOC_LITERAL(77, 1950, 15), // "setMaxRollPitch"
QT_MOC_LITERAL(78, 1966, 12), // "setBrakeRate"
QT_MOC_LITERAL(79, 1979, 16), // "setBrakeMaxPitch"
QT_MOC_LITERAL(80, 1996, 24), // "setBrakeHorizontalVelPID"
QT_MOC_LITERAL(81, 2021, 27), // "setBrakeHorizontalVelPID_Kp"
QT_MOC_LITERAL(82, 2049, 27), // "setBrakeHorizontalVelPID_Ki"
QT_MOC_LITERAL(83, 2077, 27), // "setBrakeHorizontalVelPID_Kd"
QT_MOC_LITERAL(84, 2105, 31), // "setBrakeHorizontalVelPID_ILimit"
QT_MOC_LITERAL(85, 2137, 27), // "setBrakeVelocityFeedforward"
QT_MOC_LITERAL(86, 2165, 21), // "setLandVerticalVelPID"
QT_MOC_LITERAL(87, 2187, 24), // "setLandVerticalVelPID_Kp"
QT_MOC_LITERAL(88, 2212, 24), // "setLandVerticalVelPID_Ki"
QT_MOC_LITERAL(89, 2237, 24), // "setLandVerticalVelPID_Kd"
QT_MOC_LITERAL(90, 2262, 26), // "setLandVerticalVelPID_Beta"
QT_MOC_LITERAL(91, 2289, 15), // "setUpdatePeriod"
QT_MOC_LITERAL(92, 2305, 21), // "setTreatCustomCraftAs"
QT_MOC_LITERAL(93, 2327, 16), // "setThrustControl"
QT_MOC_LITERAL(94, 2344, 13), // "setYawControl"
QT_MOC_LITERAL(95, 2358, 27), // "setFlyawayEmergencyFallback"
QT_MOC_LITERAL(96, 2386, 17), // "emitNotifications"
QT_MOC_LITERAL(97, 2404, 19), // "getHorizontalVelMax"
QT_MOC_LITERAL(98, 2424, 17), // "getVerticalVelMax"
QT_MOC_LITERAL(99, 2442, 20), // "getCourseFeedForward"
QT_MOC_LITERAL(100, 2463, 17), // "getHorizontalPosP"
QT_MOC_LITERAL(101, 2481, 15), // "getVerticalPosP"
QT_MOC_LITERAL(102, 2497, 19), // "getHorizontalVelPID"
QT_MOC_LITERAL(103, 2517, 22), // "getHorizontalVelPID_Kp"
QT_MOC_LITERAL(104, 2540, 22), // "getHorizontalVelPID_Ki"
QT_MOC_LITERAL(105, 2563, 22), // "getHorizontalVelPID_Kd"
QT_MOC_LITERAL(106, 2586, 26), // "getHorizontalVelPID_ILimit"
QT_MOC_LITERAL(107, 2613, 17), // "getVerticalVelPID"
QT_MOC_LITERAL(108, 2631, 20), // "getVerticalVelPID_Kp"
QT_MOC_LITERAL(109, 2652, 20), // "getVerticalVelPID_Ki"
QT_MOC_LITERAL(110, 2673, 20), // "getVerticalVelPID_Kd"
QT_MOC_LITERAL(111, 2694, 24), // "getVerticalVelPID_ILimit"
QT_MOC_LITERAL(112, 2719, 15), // "getThrustLimits"
QT_MOC_LITERAL(113, 2735, 19), // "getThrustLimits_Min"
QT_MOC_LITERAL(114, 2755, 23), // "getThrustLimits_Neutral"
QT_MOC_LITERAL(115, 2779, 19), // "getThrustLimits_Max"
QT_MOC_LITERAL(116, 2799, 22), // "getVelocityFeedforward"
QT_MOC_LITERAL(117, 2822, 38), // "getFlyawayEmergencyFallbackTr..."
QT_MOC_LITERAL(118, 2861, 28), // "getEmergencyFallbackAttitude"
QT_MOC_LITERAL(119, 2890, 33), // "getEmergencyFallbackAttitude_..."
QT_MOC_LITERAL(120, 2924, 34), // "getEmergencyFallbackAttitude_..."
QT_MOC_LITERAL(121, 2959, 27), // "getEmergencyFallbackYawRate"
QT_MOC_LITERAL(122, 2987, 30), // "getEmergencyFallbackYawRate_kP"
QT_MOC_LITERAL(123, 3018, 31), // "getEmergencyFallbackYawRate_Max"
QT_MOC_LITERAL(124, 3050, 15), // "getMaxRollPitch"
QT_MOC_LITERAL(125, 3066, 12), // "getBrakeRate"
QT_MOC_LITERAL(126, 3079, 16), // "getBrakeMaxPitch"
QT_MOC_LITERAL(127, 3096, 24), // "getBrakeHorizontalVelPID"
QT_MOC_LITERAL(128, 3121, 27), // "getBrakeHorizontalVelPID_Kp"
QT_MOC_LITERAL(129, 3149, 27), // "getBrakeHorizontalVelPID_Ki"
QT_MOC_LITERAL(130, 3177, 27), // "getBrakeHorizontalVelPID_Kd"
QT_MOC_LITERAL(131, 3205, 31), // "getBrakeHorizontalVelPID_ILimit"
QT_MOC_LITERAL(132, 3237, 27), // "getBrakeVelocityFeedforward"
QT_MOC_LITERAL(133, 3265, 21), // "getLandVerticalVelPID"
QT_MOC_LITERAL(134, 3287, 24), // "getLandVerticalVelPID_Kp"
QT_MOC_LITERAL(135, 3312, 24), // "getLandVerticalVelPID_Ki"
QT_MOC_LITERAL(136, 3337, 24), // "getLandVerticalVelPID_Kd"
QT_MOC_LITERAL(137, 3362, 26), // "getLandVerticalVelPID_Beta"
QT_MOC_LITERAL(138, 3389, 15), // "getUpdatePeriod"
QT_MOC_LITERAL(139, 3405, 21), // "getTreatCustomCraftAs"
QT_MOC_LITERAL(140, 3427, 16), // "getThrustControl"
QT_MOC_LITERAL(141, 3444, 13), // "getYawControl"
QT_MOC_LITERAL(142, 3458, 27), // "getFlyawayEmergencyFallback"
QT_MOC_LITERAL(143, 3486, 16), // "HorizontalVelMax"
QT_MOC_LITERAL(144, 3503, 14), // "VerticalVelMax"
QT_MOC_LITERAL(145, 3518, 17), // "CourseFeedForward"
QT_MOC_LITERAL(146, 3536, 14), // "HorizontalPosP"
QT_MOC_LITERAL(147, 3551, 12), // "VerticalPosP"
QT_MOC_LITERAL(148, 3564, 19), // "HorizontalVelPID_Kp"
QT_MOC_LITERAL(149, 3584, 19), // "HorizontalVelPID_Ki"
QT_MOC_LITERAL(150, 3604, 19), // "HorizontalVelPID_Kd"
QT_MOC_LITERAL(151, 3624, 23), // "HorizontalVelPID_ILimit"
QT_MOC_LITERAL(152, 3648, 17), // "VerticalVelPID_Kp"
QT_MOC_LITERAL(153, 3666, 17), // "VerticalVelPID_Ki"
QT_MOC_LITERAL(154, 3684, 17), // "VerticalVelPID_Kd"
QT_MOC_LITERAL(155, 3702, 21), // "VerticalVelPID_ILimit"
QT_MOC_LITERAL(156, 3724, 16), // "ThrustLimits_Min"
QT_MOC_LITERAL(157, 3741, 20), // "ThrustLimits_Neutral"
QT_MOC_LITERAL(158, 3762, 16), // "ThrustLimits_Max"
QT_MOC_LITERAL(159, 3779, 19), // "VelocityFeedforward"
QT_MOC_LITERAL(160, 3799, 35), // "FlyawayEmergencyFallbackTrigg..."
QT_MOC_LITERAL(161, 3835, 30), // "EmergencyFallbackAttitude_Roll"
QT_MOC_LITERAL(162, 3866, 31), // "EmergencyFallbackAttitude_Pitch"
QT_MOC_LITERAL(163, 3898, 27), // "EmergencyFallbackYawRate_kP"
QT_MOC_LITERAL(164, 3926, 28), // "EmergencyFallbackYawRate_Max"
QT_MOC_LITERAL(165, 3955, 12), // "MaxRollPitch"
QT_MOC_LITERAL(166, 3968, 9), // "BrakeRate"
QT_MOC_LITERAL(167, 3978, 13), // "BrakeMaxPitch"
QT_MOC_LITERAL(168, 3992, 24), // "BrakeHorizontalVelPID_Kp"
QT_MOC_LITERAL(169, 4017, 24), // "BrakeHorizontalVelPID_Ki"
QT_MOC_LITERAL(170, 4042, 24), // "BrakeHorizontalVelPID_Kd"
QT_MOC_LITERAL(171, 4067, 28), // "BrakeHorizontalVelPID_ILimit"
QT_MOC_LITERAL(172, 4096, 24), // "BrakeVelocityFeedforward"
QT_MOC_LITERAL(173, 4121, 21), // "LandVerticalVelPID_Kp"
QT_MOC_LITERAL(174, 4143, 21), // "LandVerticalVelPID_Ki"
QT_MOC_LITERAL(175, 4165, 21), // "LandVerticalVelPID_Kd"
QT_MOC_LITERAL(176, 4187, 23), // "LandVerticalVelPID_Beta"
QT_MOC_LITERAL(177, 4211, 12), // "UpdatePeriod"
QT_MOC_LITERAL(178, 4224, 18), // "TreatCustomCraftAs"
QT_MOC_LITERAL(179, 4243, 13), // "ThrustControl"
QT_MOC_LITERAL(180, 4257, 10), // "YawControl"
QT_MOC_LITERAL(181, 4268, 24) // "FlyawayEmergencyFallback"

    },
    "VtolPathFollowerSettings\0"
    "HorizontalVelMaxChanged\0\0value\0"
    "VerticalVelMaxChanged\0CourseFeedForwardChanged\0"
    "HorizontalPosPChanged\0VerticalPosPChanged\0"
    "HorizontalVelPIDChanged\0index\0"
    "HorizontalVelPID_KpChanged\0"
    "HorizontalVelPID_KiChanged\0"
    "HorizontalVelPID_KdChanged\0"
    "HorizontalVelPID_ILimitChanged\0"
    "VerticalVelPIDChanged\0VerticalVelPID_KpChanged\0"
    "VerticalVelPID_KiChanged\0"
    "VerticalVelPID_KdChanged\0"
    "VerticalVelPID_ILimitChanged\0"
    "ThrustLimitsChanged\0ThrustLimits_MinChanged\0"
    "ThrustLimits_NeutralChanged\0"
    "ThrustLimits_MaxChanged\0"
    "VelocityFeedforwardChanged\0"
    "FlyawayEmergencyFallbackTriggerTimeChanged\0"
    "EmergencyFallbackAttitudeChanged\0"
    "EmergencyFallbackAttitude_RollChanged\0"
    "EmergencyFallbackAttitude_PitchChanged\0"
    "EmergencyFallbackYawRateChanged\0"
    "EmergencyFallbackYawRate_kPChanged\0"
    "EmergencyFallbackYawRate_MaxChanged\0"
    "MaxRollPitchChanged\0BrakeRateChanged\0"
    "BrakeMaxPitchChanged\0BrakeHorizontalVelPIDChanged\0"
    "BrakeHorizontalVelPID_KpChanged\0"
    "BrakeHorizontalVelPID_KiChanged\0"
    "BrakeHorizontalVelPID_KdChanged\0"
    "BrakeHorizontalVelPID_ILimitChanged\0"
    "BrakeVelocityFeedforwardChanged\0"
    "LandVerticalVelPIDChanged\0"
    "LandVerticalVelPID_KpChanged\0"
    "LandVerticalVelPID_KiChanged\0"
    "LandVerticalVelPID_KdChanged\0"
    "LandVerticalVelPID_BetaChanged\0"
    "UpdatePeriodChanged\0TreatCustomCraftAsChanged\0"
    "ThrustControlChanged\0YawControlChanged\0"
    "FlyawayEmergencyFallbackChanged\0"
    "setHorizontalVelMax\0setVerticalVelMax\0"
    "setCourseFeedForward\0setHorizontalPosP\0"
    "setVerticalPosP\0setHorizontalVelPID\0"
    "setHorizontalVelPID_Kp\0setHorizontalVelPID_Ki\0"
    "setHorizontalVelPID_Kd\0"
    "setHorizontalVelPID_ILimit\0setVerticalVelPID\0"
    "setVerticalVelPID_Kp\0setVerticalVelPID_Ki\0"
    "setVerticalVelPID_Kd\0setVerticalVelPID_ILimit\0"
    "setThrustLimits\0setThrustLimits_Min\0"
    "setThrustLimits_Neutral\0setThrustLimits_Max\0"
    "setVelocityFeedforward\0"
    "setFlyawayEmergencyFallbackTriggerTime\0"
    "setEmergencyFallbackAttitude\0"
    "setEmergencyFallbackAttitude_Roll\0"
    "setEmergencyFallbackAttitude_Pitch\0"
    "setEmergencyFallbackYawRate\0"
    "setEmergencyFallbackYawRate_kP\0"
    "setEmergencyFallbackYawRate_Max\0"
    "setMaxRollPitch\0setBrakeRate\0"
    "setBrakeMaxPitch\0setBrakeHorizontalVelPID\0"
    "setBrakeHorizontalVelPID_Kp\0"
    "setBrakeHorizontalVelPID_Ki\0"
    "setBrakeHorizontalVelPID_Kd\0"
    "setBrakeHorizontalVelPID_ILimit\0"
    "setBrakeVelocityFeedforward\0"
    "setLandVerticalVelPID\0setLandVerticalVelPID_Kp\0"
    "setLandVerticalVelPID_Ki\0"
    "setLandVerticalVelPID_Kd\0"
    "setLandVerticalVelPID_Beta\0setUpdatePeriod\0"
    "setTreatCustomCraftAs\0setThrustControl\0"
    "setYawControl\0setFlyawayEmergencyFallback\0"
    "emitNotifications\0getHorizontalVelMax\0"
    "getVerticalVelMax\0getCourseFeedForward\0"
    "getHorizontalPosP\0getVerticalPosP\0"
    "getHorizontalVelPID\0getHorizontalVelPID_Kp\0"
    "getHorizontalVelPID_Ki\0getHorizontalVelPID_Kd\0"
    "getHorizontalVelPID_ILimit\0getVerticalVelPID\0"
    "getVerticalVelPID_Kp\0getVerticalVelPID_Ki\0"
    "getVerticalVelPID_Kd\0getVerticalVelPID_ILimit\0"
    "getThrustLimits\0getThrustLimits_Min\0"
    "getThrustLimits_Neutral\0getThrustLimits_Max\0"
    "getVelocityFeedforward\0"
    "getFlyawayEmergencyFallbackTriggerTime\0"
    "getEmergencyFallbackAttitude\0"
    "getEmergencyFallbackAttitude_Roll\0"
    "getEmergencyFallbackAttitude_Pitch\0"
    "getEmergencyFallbackYawRate\0"
    "getEmergencyFallbackYawRate_kP\0"
    "getEmergencyFallbackYawRate_Max\0"
    "getMaxRollPitch\0getBrakeRate\0"
    "getBrakeMaxPitch\0getBrakeHorizontalVelPID\0"
    "getBrakeHorizontalVelPID_Kp\0"
    "getBrakeHorizontalVelPID_Ki\0"
    "getBrakeHorizontalVelPID_Kd\0"
    "getBrakeHorizontalVelPID_ILimit\0"
    "getBrakeVelocityFeedforward\0"
    "getLandVerticalVelPID\0getLandVerticalVelPID_Kp\0"
    "getLandVerticalVelPID_Ki\0"
    "getLandVerticalVelPID_Kd\0"
    "getLandVerticalVelPID_Beta\0getUpdatePeriod\0"
    "getTreatCustomCraftAs\0getThrustControl\0"
    "getYawControl\0getFlyawayEmergencyFallback\0"
    "HorizontalVelMax\0VerticalVelMax\0"
    "CourseFeedForward\0HorizontalPosP\0"
    "VerticalPosP\0HorizontalVelPID_Kp\0"
    "HorizontalVelPID_Ki\0HorizontalVelPID_Kd\0"
    "HorizontalVelPID_ILimit\0VerticalVelPID_Kp\0"
    "VerticalVelPID_Ki\0VerticalVelPID_Kd\0"
    "VerticalVelPID_ILimit\0ThrustLimits_Min\0"
    "ThrustLimits_Neutral\0ThrustLimits_Max\0"
    "VelocityFeedforward\0"
    "FlyawayEmergencyFallbackTriggerTime\0"
    "EmergencyFallbackAttitude_Roll\0"
    "EmergencyFallbackAttitude_Pitch\0"
    "EmergencyFallbackYawRate_kP\0"
    "EmergencyFallbackYawRate_Max\0MaxRollPitch\0"
    "BrakeRate\0BrakeMaxPitch\0"
    "BrakeHorizontalVelPID_Kp\0"
    "BrakeHorizontalVelPID_Ki\0"
    "BrakeHorizontalVelPID_Kd\0"
    "BrakeHorizontalVelPID_ILimit\0"
    "BrakeVelocityFeedforward\0LandVerticalVelPID_Kp\0"
    "LandVerticalVelPID_Ki\0LandVerticalVelPID_Kd\0"
    "LandVerticalVelPID_Beta\0UpdatePeriod\0"
    "TreatCustomCraftAs\0ThrustControl\0"
    "YawControl\0FlyawayEmergencyFallback"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VtolPathFollowerSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     139,   14, // methods
      39, 1074, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      46,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  709,    2, 0x06 /* Public */,
       4,    1,  712,    2, 0x06 /* Public */,
       5,    1,  715,    2, 0x06 /* Public */,
       6,    1,  718,    2, 0x06 /* Public */,
       7,    1,  721,    2, 0x06 /* Public */,
       8,    2,  724,    2, 0x06 /* Public */,
      10,    1,  729,    2, 0x06 /* Public */,
      11,    1,  732,    2, 0x06 /* Public */,
      12,    1,  735,    2, 0x06 /* Public */,
      13,    1,  738,    2, 0x06 /* Public */,
      14,    2,  741,    2, 0x06 /* Public */,
      15,    1,  746,    2, 0x06 /* Public */,
      16,    1,  749,    2, 0x06 /* Public */,
      17,    1,  752,    2, 0x06 /* Public */,
      18,    1,  755,    2, 0x06 /* Public */,
      19,    2,  758,    2, 0x06 /* Public */,
      20,    1,  763,    2, 0x06 /* Public */,
      21,    1,  766,    2, 0x06 /* Public */,
      22,    1,  769,    2, 0x06 /* Public */,
      23,    1,  772,    2, 0x06 /* Public */,
      24,    1,  775,    2, 0x06 /* Public */,
      25,    2,  778,    2, 0x06 /* Public */,
      26,    1,  783,    2, 0x06 /* Public */,
      27,    1,  786,    2, 0x06 /* Public */,
      28,    2,  789,    2, 0x06 /* Public */,
      29,    1,  794,    2, 0x06 /* Public */,
      30,    1,  797,    2, 0x06 /* Public */,
      31,    1,  800,    2, 0x06 /* Public */,
      32,    1,  803,    2, 0x06 /* Public */,
      33,    1,  806,    2, 0x06 /* Public */,
      34,    2,  809,    2, 0x06 /* Public */,
      35,    1,  814,    2, 0x06 /* Public */,
      36,    1,  817,    2, 0x06 /* Public */,
      37,    1,  820,    2, 0x06 /* Public */,
      38,    1,  823,    2, 0x06 /* Public */,
      39,    1,  826,    2, 0x06 /* Public */,
      40,    2,  829,    2, 0x06 /* Public */,
      41,    1,  834,    2, 0x06 /* Public */,
      42,    1,  837,    2, 0x06 /* Public */,
      43,    1,  840,    2, 0x06 /* Public */,
      44,    1,  843,    2, 0x06 /* Public */,
      45,    1,  846,    2, 0x06 /* Public */,
      46,    1,  849,    2, 0x06 /* Public */,
      47,    1,  852,    2, 0x06 /* Public */,
      48,    1,  855,    2, 0x06 /* Public */,
      49,    1,  858,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      50,    1,  861,    2, 0x0a /* Public */,
      51,    1,  864,    2, 0x0a /* Public */,
      52,    1,  867,    2, 0x0a /* Public */,
      53,    1,  870,    2, 0x0a /* Public */,
      54,    1,  873,    2, 0x0a /* Public */,
      55,    2,  876,    2, 0x0a /* Public */,
      56,    1,  881,    2, 0x0a /* Public */,
      57,    1,  884,    2, 0x0a /* Public */,
      58,    1,  887,    2, 0x0a /* Public */,
      59,    1,  890,    2, 0x0a /* Public */,
      60,    2,  893,    2, 0x0a /* Public */,
      61,    1,  898,    2, 0x0a /* Public */,
      62,    1,  901,    2, 0x0a /* Public */,
      63,    1,  904,    2, 0x0a /* Public */,
      64,    1,  907,    2, 0x0a /* Public */,
      65,    2,  910,    2, 0x0a /* Public */,
      66,    1,  915,    2, 0x0a /* Public */,
      67,    1,  918,    2, 0x0a /* Public */,
      68,    1,  921,    2, 0x0a /* Public */,
      69,    1,  924,    2, 0x0a /* Public */,
      70,    1,  927,    2, 0x0a /* Public */,
      71,    2,  930,    2, 0x0a /* Public */,
      72,    1,  935,    2, 0x0a /* Public */,
      73,    1,  938,    2, 0x0a /* Public */,
      74,    2,  941,    2, 0x0a /* Public */,
      75,    1,  946,    2, 0x0a /* Public */,
      76,    1,  949,    2, 0x0a /* Public */,
      77,    1,  952,    2, 0x0a /* Public */,
      78,    1,  955,    2, 0x0a /* Public */,
      79,    1,  958,    2, 0x0a /* Public */,
      80,    2,  961,    2, 0x0a /* Public */,
      81,    1,  966,    2, 0x0a /* Public */,
      82,    1,  969,    2, 0x0a /* Public */,
      83,    1,  972,    2, 0x0a /* Public */,
      84,    1,  975,    2, 0x0a /* Public */,
      85,    1,  978,    2, 0x0a /* Public */,
      86,    2,  981,    2, 0x0a /* Public */,
      87,    1,  986,    2, 0x0a /* Public */,
      88,    1,  989,    2, 0x0a /* Public */,
      89,    1,  992,    2, 0x0a /* Public */,
      90,    1,  995,    2, 0x0a /* Public */,
      91,    1,  998,    2, 0x0a /* Public */,
      92,    1, 1001,    2, 0x0a /* Public */,
      93,    1, 1004,    2, 0x0a /* Public */,
      94,    1, 1007,    2, 0x0a /* Public */,
      95,    1, 1010,    2, 0x0a /* Public */,
      96,    0, 1013,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      97,    0, 1014,    2, 0x02 /* Public */,
      98,    0, 1015,    2, 0x02 /* Public */,
      99,    0, 1016,    2, 0x02 /* Public */,
     100,    0, 1017,    2, 0x02 /* Public */,
     101,    0, 1018,    2, 0x02 /* Public */,
     102,    1, 1019,    2, 0x02 /* Public */,
     103,    0, 1022,    2, 0x02 /* Public */,
     104,    0, 1023,    2, 0x02 /* Public */,
     105,    0, 1024,    2, 0x02 /* Public */,
     106,    0, 1025,    2, 0x02 /* Public */,
     107,    1, 1026,    2, 0x02 /* Public */,
     108,    0, 1029,    2, 0x02 /* Public */,
     109,    0, 1030,    2, 0x02 /* Public */,
     110,    0, 1031,    2, 0x02 /* Public */,
     111,    0, 1032,    2, 0x02 /* Public */,
     112,    1, 1033,    2, 0x02 /* Public */,
     113,    0, 1036,    2, 0x02 /* Public */,
     114,    0, 1037,    2, 0x02 /* Public */,
     115,    0, 1038,    2, 0x02 /* Public */,
     116,    0, 1039,    2, 0x02 /* Public */,
     117,    0, 1040,    2, 0x02 /* Public */,
     118,    1, 1041,    2, 0x02 /* Public */,
     119,    0, 1044,    2, 0x02 /* Public */,
     120,    0, 1045,    2, 0x02 /* Public */,
     121,    1, 1046,    2, 0x02 /* Public */,
     122,    0, 1049,    2, 0x02 /* Public */,
     123,    0, 1050,    2, 0x02 /* Public */,
     124,    0, 1051,    2, 0x02 /* Public */,
     125,    0, 1052,    2, 0x02 /* Public */,
     126,    0, 1053,    2, 0x02 /* Public */,
     127,    1, 1054,    2, 0x02 /* Public */,
     128,    0, 1057,    2, 0x02 /* Public */,
     129,    0, 1058,    2, 0x02 /* Public */,
     130,    0, 1059,    2, 0x02 /* Public */,
     131,    0, 1060,    2, 0x02 /* Public */,
     132,    0, 1061,    2, 0x02 /* Public */,
     133,    1, 1062,    2, 0x02 /* Public */,
     134,    0, 1065,    2, 0x02 /* Public */,
     135,    0, 1066,    2, 0x02 /* Public */,
     136,    0, 1067,    2, 0x02 /* Public */,
     137,    0, 1068,    2, 0x02 /* Public */,
     138,    0, 1069,    2, 0x02 /* Public */,
     139,    0, 1070,    2, 0x02 /* Public */,
     140,    0, 1071,    2, 0x02 /* Public */,
     141,    0, 1072,    2, 0x02 /* Public */,
     142,    0, 1073,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    9,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    9,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    9,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    9,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    9,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    9,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    9,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    9,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UShort,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
     143, QMetaType::Float, 0x00495103,
     144, QMetaType::Float, 0x00495103,
     145, QMetaType::Float, 0x00495103,
     146, QMetaType::Float, 0x00495103,
     147, QMetaType::Float, 0x00495103,
     148, QMetaType::Float, 0x00495103,
     149, QMetaType::Float, 0x00495103,
     150, QMetaType::Float, 0x00495103,
     151, QMetaType::Float, 0x00495103,
     152, QMetaType::Float, 0x00495103,
     153, QMetaType::Float, 0x00495103,
     154, QMetaType::Float, 0x00495103,
     155, QMetaType::Float, 0x00495103,
     156, QMetaType::Float, 0x00495103,
     157, QMetaType::Float, 0x00495103,
     158, QMetaType::Float, 0x00495103,
     159, QMetaType::Float, 0x00495103,
     160, QMetaType::Float, 0x00495103,
     161, QMetaType::Float, 0x00495103,
     162, QMetaType::Float, 0x00495103,
     163, QMetaType::Float, 0x00495103,
     164, QMetaType::Float, 0x00495103,
     165, QMetaType::Float, 0x00495103,
     166, QMetaType::Float, 0x00495103,
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
     177, QMetaType::UShort, 0x00495103,
     178, QMetaType::UChar, 0x00495103,
     179, QMetaType::UChar, 0x00495103,
     180, QMetaType::UChar, 0x00495103,
     181, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       6,
       7,
       8,
       9,
      11,
      12,
      13,
      14,
      16,
      17,
      18,
      19,
      20,
      22,
      23,
      25,
      26,
      27,
      28,
      29,
      31,
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
      45,

       0        // eod
};

void VtolPathFollowerSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VtolPathFollowerSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->HorizontalVelMaxChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->VerticalVelMaxChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->CourseFeedForwardChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->HorizontalPosPChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->VerticalPosPChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->HorizontalVelPIDChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 6: _t->HorizontalVelPID_KpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->HorizontalVelPID_KiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->HorizontalVelPID_KdChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->HorizontalVelPID_ILimitChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->VerticalVelPIDChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 11: _t->VerticalVelPID_KpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->VerticalVelPID_KiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->VerticalVelPID_KdChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->VerticalVelPID_ILimitChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->ThrustLimitsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 16: _t->ThrustLimits_MinChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 17: _t->ThrustLimits_NeutralChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->ThrustLimits_MaxChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->VelocityFeedforwardChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->FlyawayEmergencyFallbackTriggerTimeChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->EmergencyFallbackAttitudeChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 22: _t->EmergencyFallbackAttitude_RollChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->EmergencyFallbackAttitude_PitchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->EmergencyFallbackYawRateChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 25: _t->EmergencyFallbackYawRate_kPChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 26: _t->EmergencyFallbackYawRate_MaxChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->MaxRollPitchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 28: _t->BrakeRateChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 29: _t->BrakeMaxPitchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 30: _t->BrakeHorizontalVelPIDChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 31: _t->BrakeHorizontalVelPID_KpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 32: _t->BrakeHorizontalVelPID_KiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 33: _t->BrakeHorizontalVelPID_KdChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 34: _t->BrakeHorizontalVelPID_ILimitChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 35: _t->BrakeVelocityFeedforwardChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 36: _t->LandVerticalVelPIDChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 37: _t->LandVerticalVelPID_KpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 38: _t->LandVerticalVelPID_KiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 39: _t->LandVerticalVelPID_KdChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 40: _t->LandVerticalVelPID_BetaChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 41: _t->UpdatePeriodChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 42: _t->TreatCustomCraftAsChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 43: _t->ThrustControlChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 44: _t->YawControlChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 45: _t->FlyawayEmergencyFallbackChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 46: _t->setHorizontalVelMax((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 47: _t->setVerticalVelMax((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 48: _t->setCourseFeedForward((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 49: _t->setHorizontalPosP((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 50: _t->setVerticalPosP((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 51: _t->setHorizontalVelPID((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 52: _t->setHorizontalVelPID_Kp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 53: _t->setHorizontalVelPID_Ki((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 54: _t->setHorizontalVelPID_Kd((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 55: _t->setHorizontalVelPID_ILimit((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 56: _t->setVerticalVelPID((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 57: _t->setVerticalVelPID_Kp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 58: _t->setVerticalVelPID_Ki((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 59: _t->setVerticalVelPID_Kd((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 60: _t->setVerticalVelPID_ILimit((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 61: _t->setThrustLimits((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 62: _t->setThrustLimits_Min((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 63: _t->setThrustLimits_Neutral((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 64: _t->setThrustLimits_Max((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 65: _t->setVelocityFeedforward((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 66: _t->setFlyawayEmergencyFallbackTriggerTime((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 67: _t->setEmergencyFallbackAttitude((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 68: _t->setEmergencyFallbackAttitude_Roll((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 69: _t->setEmergencyFallbackAttitude_Pitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 70: _t->setEmergencyFallbackYawRate((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 71: _t->setEmergencyFallbackYawRate_kP((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 72: _t->setEmergencyFallbackYawRate_Max((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 73: _t->setMaxRollPitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 74: _t->setBrakeRate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 75: _t->setBrakeMaxPitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 76: _t->setBrakeHorizontalVelPID((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 77: _t->setBrakeHorizontalVelPID_Kp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 78: _t->setBrakeHorizontalVelPID_Ki((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 79: _t->setBrakeHorizontalVelPID_Kd((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 80: _t->setBrakeHorizontalVelPID_ILimit((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 81: _t->setBrakeVelocityFeedforward((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 82: _t->setLandVerticalVelPID((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 83: _t->setLandVerticalVelPID_Kp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 84: _t->setLandVerticalVelPID_Ki((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 85: _t->setLandVerticalVelPID_Kd((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 86: _t->setLandVerticalVelPID_Beta((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 87: _t->setUpdatePeriod((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 88: _t->setTreatCustomCraftAs((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 89: _t->setThrustControl((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 90: _t->setYawControl((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 91: _t->setFlyawayEmergencyFallback((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 92: _t->emitNotifications(); break;
        case 93: { float _r = _t->getHorizontalVelMax();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 94: { float _r = _t->getVerticalVelMax();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 95: { float _r = _t->getCourseFeedForward();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 96: { float _r = _t->getHorizontalPosP();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 97: { float _r = _t->getVerticalPosP();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 98: { float _r = _t->getHorizontalVelPID((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 99: { float _r = _t->getHorizontalVelPID_Kp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 100: { float _r = _t->getHorizontalVelPID_Ki();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 101: { float _r = _t->getHorizontalVelPID_Kd();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 102: { float _r = _t->getHorizontalVelPID_ILimit();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 103: { float _r = _t->getVerticalVelPID((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 104: { float _r = _t->getVerticalVelPID_Kp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 105: { float _r = _t->getVerticalVelPID_Ki();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 106: { float _r = _t->getVerticalVelPID_Kd();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 107: { float _r = _t->getVerticalVelPID_ILimit();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 108: { float _r = _t->getThrustLimits((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 109: { float _r = _t->getThrustLimits_Min();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 110: { float _r = _t->getThrustLimits_Neutral();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 111: { float _r = _t->getThrustLimits_Max();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 112: { float _r = _t->getVelocityFeedforward();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 113: { float _r = _t->getFlyawayEmergencyFallbackTriggerTime();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 114: { float _r = _t->getEmergencyFallbackAttitude((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 115: { float _r = _t->getEmergencyFallbackAttitude_Roll();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 116: { float _r = _t->getEmergencyFallbackAttitude_Pitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 117: { float _r = _t->getEmergencyFallbackYawRate((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 118: { float _r = _t->getEmergencyFallbackYawRate_kP();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 119: { float _r = _t->getEmergencyFallbackYawRate_Max();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 120: { float _r = _t->getMaxRollPitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 121: { float _r = _t->getBrakeRate();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 122: { float _r = _t->getBrakeMaxPitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 123: { float _r = _t->getBrakeHorizontalVelPID((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 124: { float _r = _t->getBrakeHorizontalVelPID_Kp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 125: { float _r = _t->getBrakeHorizontalVelPID_Ki();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 126: { float _r = _t->getBrakeHorizontalVelPID_Kd();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 127: { float _r = _t->getBrakeHorizontalVelPID_ILimit();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 128: { float _r = _t->getBrakeVelocityFeedforward();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 129: { float _r = _t->getLandVerticalVelPID((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 130: { float _r = _t->getLandVerticalVelPID_Kp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 131: { float _r = _t->getLandVerticalVelPID_Ki();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 132: { float _r = _t->getLandVerticalVelPID_Kd();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 133: { float _r = _t->getLandVerticalVelPID_Beta();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 134: { quint16 _r = _t->getUpdatePeriod();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 135: { quint8 _r = _t->getTreatCustomCraftAs();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 136: { quint8 _r = _t->getThrustControl();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 137: { quint8 _r = _t->getYawControl();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 138: { quint8 _r = _t->getFlyawayEmergencyFallback();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::HorizontalVelMaxChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::VerticalVelMaxChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::CourseFeedForwardChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::HorizontalPosPChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::VerticalPosPChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::HorizontalVelPIDChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::HorizontalVelPID_KpChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::HorizontalVelPID_KiChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::HorizontalVelPID_KdChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::HorizontalVelPID_ILimitChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::VerticalVelPIDChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::VerticalVelPID_KpChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::VerticalVelPID_KiChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::VerticalVelPID_KdChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::VerticalVelPID_ILimitChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::ThrustLimitsChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::ThrustLimits_MinChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::ThrustLimits_NeutralChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::ThrustLimits_MaxChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::VelocityFeedforwardChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::FlyawayEmergencyFallbackTriggerTimeChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::EmergencyFallbackAttitudeChanged)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::EmergencyFallbackAttitude_RollChanged)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::EmergencyFallbackAttitude_PitchChanged)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::EmergencyFallbackYawRateChanged)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::EmergencyFallbackYawRate_kPChanged)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::EmergencyFallbackYawRate_MaxChanged)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::MaxRollPitchChanged)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::BrakeRateChanged)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::BrakeMaxPitchChanged)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::BrakeHorizontalVelPIDChanged)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::BrakeHorizontalVelPID_KpChanged)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::BrakeHorizontalVelPID_KiChanged)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::BrakeHorizontalVelPID_KdChanged)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::BrakeHorizontalVelPID_ILimitChanged)) {
                *result = 34;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::BrakeVelocityFeedforwardChanged)) {
                *result = 35;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::LandVerticalVelPIDChanged)) {
                *result = 36;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::LandVerticalVelPID_KpChanged)) {
                *result = 37;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::LandVerticalVelPID_KiChanged)) {
                *result = 38;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::LandVerticalVelPID_KdChanged)) {
                *result = 39;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::LandVerticalVelPID_BetaChanged)) {
                *result = 40;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::UpdatePeriodChanged)) {
                *result = 41;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::TreatCustomCraftAsChanged)) {
                *result = 42;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::ThrustControlChanged)) {
                *result = 43;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::YawControlChanged)) {
                *result = 44;
                return;
            }
        }
        {
            using _t = void (VtolPathFollowerSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VtolPathFollowerSettings::FlyawayEmergencyFallbackChanged)) {
                *result = 45;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<VtolPathFollowerSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getHorizontalVelMax(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getVerticalVelMax(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getCourseFeedForward(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getHorizontalPosP(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getVerticalPosP(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getHorizontalVelPID_Kp(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getHorizontalVelPID_Ki(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getHorizontalVelPID_Kd(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getHorizontalVelPID_ILimit(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->getVerticalVelPID_Kp(); break;
        case 10: *reinterpret_cast< float*>(_v) = _t->getVerticalVelPID_Ki(); break;
        case 11: *reinterpret_cast< float*>(_v) = _t->getVerticalVelPID_Kd(); break;
        case 12: *reinterpret_cast< float*>(_v) = _t->getVerticalVelPID_ILimit(); break;
        case 13: *reinterpret_cast< float*>(_v) = _t->getThrustLimits_Min(); break;
        case 14: *reinterpret_cast< float*>(_v) = _t->getThrustLimits_Neutral(); break;
        case 15: *reinterpret_cast< float*>(_v) = _t->getThrustLimits_Max(); break;
        case 16: *reinterpret_cast< float*>(_v) = _t->getVelocityFeedforward(); break;
        case 17: *reinterpret_cast< float*>(_v) = _t->getFlyawayEmergencyFallbackTriggerTime(); break;
        case 18: *reinterpret_cast< float*>(_v) = _t->getEmergencyFallbackAttitude_Roll(); break;
        case 19: *reinterpret_cast< float*>(_v) = _t->getEmergencyFallbackAttitude_Pitch(); break;
        case 20: *reinterpret_cast< float*>(_v) = _t->getEmergencyFallbackYawRate_kP(); break;
        case 21: *reinterpret_cast< float*>(_v) = _t->getEmergencyFallbackYawRate_Max(); break;
        case 22: *reinterpret_cast< float*>(_v) = _t->getMaxRollPitch(); break;
        case 23: *reinterpret_cast< float*>(_v) = _t->getBrakeRate(); break;
        case 24: *reinterpret_cast< float*>(_v) = _t->getBrakeMaxPitch(); break;
        case 25: *reinterpret_cast< float*>(_v) = _t->getBrakeHorizontalVelPID_Kp(); break;
        case 26: *reinterpret_cast< float*>(_v) = _t->getBrakeHorizontalVelPID_Ki(); break;
        case 27: *reinterpret_cast< float*>(_v) = _t->getBrakeHorizontalVelPID_Kd(); break;
        case 28: *reinterpret_cast< float*>(_v) = _t->getBrakeHorizontalVelPID_ILimit(); break;
        case 29: *reinterpret_cast< float*>(_v) = _t->getBrakeVelocityFeedforward(); break;
        case 30: *reinterpret_cast< float*>(_v) = _t->getLandVerticalVelPID_Kp(); break;
        case 31: *reinterpret_cast< float*>(_v) = _t->getLandVerticalVelPID_Ki(); break;
        case 32: *reinterpret_cast< float*>(_v) = _t->getLandVerticalVelPID_Kd(); break;
        case 33: *reinterpret_cast< float*>(_v) = _t->getLandVerticalVelPID_Beta(); break;
        case 34: *reinterpret_cast< quint16*>(_v) = _t->getUpdatePeriod(); break;
        case 35: *reinterpret_cast< quint8*>(_v) = _t->getTreatCustomCraftAs(); break;
        case 36: *reinterpret_cast< quint8*>(_v) = _t->getThrustControl(); break;
        case 37: *reinterpret_cast< quint8*>(_v) = _t->getYawControl(); break;
        case 38: *reinterpret_cast< quint8*>(_v) = _t->getFlyawayEmergencyFallback(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<VtolPathFollowerSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setHorizontalVelMax(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setVerticalVelMax(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setCourseFeedForward(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setHorizontalPosP(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setVerticalPosP(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setHorizontalVelPID_Kp(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setHorizontalVelPID_Ki(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setHorizontalVelPID_Kd(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setHorizontalVelPID_ILimit(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setVerticalVelPID_Kp(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setVerticalVelPID_Ki(*reinterpret_cast< float*>(_v)); break;
        case 11: _t->setVerticalVelPID_Kd(*reinterpret_cast< float*>(_v)); break;
        case 12: _t->setVerticalVelPID_ILimit(*reinterpret_cast< float*>(_v)); break;
        case 13: _t->setThrustLimits_Min(*reinterpret_cast< float*>(_v)); break;
        case 14: _t->setThrustLimits_Neutral(*reinterpret_cast< float*>(_v)); break;
        case 15: _t->setThrustLimits_Max(*reinterpret_cast< float*>(_v)); break;
        case 16: _t->setVelocityFeedforward(*reinterpret_cast< float*>(_v)); break;
        case 17: _t->setFlyawayEmergencyFallbackTriggerTime(*reinterpret_cast< float*>(_v)); break;
        case 18: _t->setEmergencyFallbackAttitude_Roll(*reinterpret_cast< float*>(_v)); break;
        case 19: _t->setEmergencyFallbackAttitude_Pitch(*reinterpret_cast< float*>(_v)); break;
        case 20: _t->setEmergencyFallbackYawRate_kP(*reinterpret_cast< float*>(_v)); break;
        case 21: _t->setEmergencyFallbackYawRate_Max(*reinterpret_cast< float*>(_v)); break;
        case 22: _t->setMaxRollPitch(*reinterpret_cast< float*>(_v)); break;
        case 23: _t->setBrakeRate(*reinterpret_cast< float*>(_v)); break;
        case 24: _t->setBrakeMaxPitch(*reinterpret_cast< float*>(_v)); break;
        case 25: _t->setBrakeHorizontalVelPID_Kp(*reinterpret_cast< float*>(_v)); break;
        case 26: _t->setBrakeHorizontalVelPID_Ki(*reinterpret_cast< float*>(_v)); break;
        case 27: _t->setBrakeHorizontalVelPID_Kd(*reinterpret_cast< float*>(_v)); break;
        case 28: _t->setBrakeHorizontalVelPID_ILimit(*reinterpret_cast< float*>(_v)); break;
        case 29: _t->setBrakeVelocityFeedforward(*reinterpret_cast< float*>(_v)); break;
        case 30: _t->setLandVerticalVelPID_Kp(*reinterpret_cast< float*>(_v)); break;
        case 31: _t->setLandVerticalVelPID_Ki(*reinterpret_cast< float*>(_v)); break;
        case 32: _t->setLandVerticalVelPID_Kd(*reinterpret_cast< float*>(_v)); break;
        case 33: _t->setLandVerticalVelPID_Beta(*reinterpret_cast< float*>(_v)); break;
        case 34: _t->setUpdatePeriod(*reinterpret_cast< quint16*>(_v)); break;
        case 35: _t->setTreatCustomCraftAs(*reinterpret_cast< quint8*>(_v)); break;
        case 36: _t->setThrustControl(*reinterpret_cast< quint8*>(_v)); break;
        case 37: _t->setYawControl(*reinterpret_cast< quint8*>(_v)); break;
        case 38: _t->setFlyawayEmergencyFallback(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject VtolPathFollowerSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_VtolPathFollowerSettings.data,
    qt_meta_data_VtolPathFollowerSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VtolPathFollowerSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VtolPathFollowerSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VtolPathFollowerSettings.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int VtolPathFollowerSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 139)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 139;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 139)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 139;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 39;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 39;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 39;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 39;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 39;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void VtolPathFollowerSettings::HorizontalVelMaxChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VtolPathFollowerSettings::VerticalVelMaxChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VtolPathFollowerSettings::CourseFeedForwardChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VtolPathFollowerSettings::HorizontalPosPChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VtolPathFollowerSettings::VerticalPosPChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VtolPathFollowerSettings::HorizontalVelPIDChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void VtolPathFollowerSettings::HorizontalVelPID_KpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void VtolPathFollowerSettings::HorizontalVelPID_KiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void VtolPathFollowerSettings::HorizontalVelPID_KdChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void VtolPathFollowerSettings::HorizontalVelPID_ILimitChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void VtolPathFollowerSettings::VerticalVelPIDChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void VtolPathFollowerSettings::VerticalVelPID_KpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void VtolPathFollowerSettings::VerticalVelPID_KiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void VtolPathFollowerSettings::VerticalVelPID_KdChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void VtolPathFollowerSettings::VerticalVelPID_ILimitChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void VtolPathFollowerSettings::ThrustLimitsChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void VtolPathFollowerSettings::ThrustLimits_MinChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void VtolPathFollowerSettings::ThrustLimits_NeutralChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void VtolPathFollowerSettings::ThrustLimits_MaxChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void VtolPathFollowerSettings::VelocityFeedforwardChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void VtolPathFollowerSettings::FlyawayEmergencyFallbackTriggerTimeChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void VtolPathFollowerSettings::EmergencyFallbackAttitudeChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void VtolPathFollowerSettings::EmergencyFallbackAttitude_RollChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void VtolPathFollowerSettings::EmergencyFallbackAttitude_PitchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void VtolPathFollowerSettings::EmergencyFallbackYawRateChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void VtolPathFollowerSettings::EmergencyFallbackYawRate_kPChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void VtolPathFollowerSettings::EmergencyFallbackYawRate_MaxChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void VtolPathFollowerSettings::MaxRollPitchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void VtolPathFollowerSettings::BrakeRateChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void VtolPathFollowerSettings::BrakeMaxPitchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void VtolPathFollowerSettings::BrakeHorizontalVelPIDChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void VtolPathFollowerSettings::BrakeHorizontalVelPID_KpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void VtolPathFollowerSettings::BrakeHorizontalVelPID_KiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void VtolPathFollowerSettings::BrakeHorizontalVelPID_KdChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void VtolPathFollowerSettings::BrakeHorizontalVelPID_ILimitChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void VtolPathFollowerSettings::BrakeVelocityFeedforwardChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 35, _a);
}

// SIGNAL 36
void VtolPathFollowerSettings::LandVerticalVelPIDChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 36, _a);
}

// SIGNAL 37
void VtolPathFollowerSettings::LandVerticalVelPID_KpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 37, _a);
}

// SIGNAL 38
void VtolPathFollowerSettings::LandVerticalVelPID_KiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 38, _a);
}

// SIGNAL 39
void VtolPathFollowerSettings::LandVerticalVelPID_KdChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 39, _a);
}

// SIGNAL 40
void VtolPathFollowerSettings::LandVerticalVelPID_BetaChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 40, _a);
}

// SIGNAL 41
void VtolPathFollowerSettings::UpdatePeriodChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 41, _a);
}

// SIGNAL 42
void VtolPathFollowerSettings::TreatCustomCraftAsChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 42, _a);
}

// SIGNAL 43
void VtolPathFollowerSettings::ThrustControlChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 43, _a);
}

// SIGNAL 44
void VtolPathFollowerSettings::YawControlChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 44, _a);
}

// SIGNAL 45
void VtolPathFollowerSettings::FlyawayEmergencyFallbackChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 45, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
