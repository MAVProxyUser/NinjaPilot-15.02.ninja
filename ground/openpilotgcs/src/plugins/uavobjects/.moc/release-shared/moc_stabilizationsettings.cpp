/****************************************************************************
** Meta object code from reading C++ file 'stabilizationsettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/stabilizationsettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stabilizationsettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StabilizationSettings_t {
    QByteArrayData data[237];
    char stringdata0[5745];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StabilizationSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StabilizationSettings_t qt_meta_stringdata_StabilizationSettings = {
    {
QT_MOC_LITERAL(0, 0, 21), // "StabilizationSettings"
QT_MOC_LITERAL(1, 22, 22), // "VbarSensitivityChanged"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 5), // "index"
QT_MOC_LITERAL(4, 52, 5), // "value"
QT_MOC_LITERAL(5, 58, 27), // "VbarSensitivity_RollChanged"
QT_MOC_LITERAL(6, 86, 28), // "VbarSensitivity_PitchChanged"
QT_MOC_LITERAL(7, 115, 26), // "VbarSensitivity_YawChanged"
QT_MOC_LITERAL(8, 142, 17), // "VbarRollPIChanged"
QT_MOC_LITERAL(9, 160, 20), // "VbarRollPI_KpChanged"
QT_MOC_LITERAL(10, 181, 20), // "VbarRollPI_KiChanged"
QT_MOC_LITERAL(11, 202, 18), // "VbarPitchPIChanged"
QT_MOC_LITERAL(12, 221, 21), // "VbarPitchPI_KpChanged"
QT_MOC_LITERAL(13, 243, 21), // "VbarPitchPI_KiChanged"
QT_MOC_LITERAL(14, 265, 16), // "VbarYawPIChanged"
QT_MOC_LITERAL(15, 282, 19), // "VbarYawPI_KpChanged"
QT_MOC_LITERAL(16, 302, 19), // "VbarYawPI_KiChanged"
QT_MOC_LITERAL(17, 322, 14), // "VbarTauChanged"
QT_MOC_LITERAL(18, 337, 14), // "GyroTauChanged"
QT_MOC_LITERAL(19, 352, 22), // "DerivativeGammaChanged"
QT_MOC_LITERAL(20, 375, 17), // "AxisLockKpChanged"
QT_MOC_LITERAL(21, 393, 21), // "WeakLevelingKpChanged"
QT_MOC_LITERAL(22, 415, 34), // "CruiseControlMaxPowerFactorCh..."
QT_MOC_LITERAL(23, 450, 29), // "CruiseControlPowerTrimChanged"
QT_MOC_LITERAL(24, 480, 34), // "CruiseControlPowerDelayCompCh..."
QT_MOC_LITERAL(25, 515, 22), // "ScaleToAirspeedChanged"
QT_MOC_LITERAL(26, 538, 28), // "ScaleToAirspeedLimitsChanged"
QT_MOC_LITERAL(27, 567, 32), // "ScaleToAirspeedLimits_MinChanged"
QT_MOC_LITERAL(28, 600, 32), // "ScaleToAirspeedLimits_MaxChanged"
QT_MOC_LITERAL(29, 633, 20), // "FlightModeMapChanged"
QT_MOC_LITERAL(30, 654, 22), // "FlightModeMap_0Changed"
QT_MOC_LITERAL(31, 677, 22), // "FlightModeMap_1Changed"
QT_MOC_LITERAL(32, 700, 22), // "FlightModeMap_2Changed"
QT_MOC_LITERAL(33, 723, 22), // "FlightModeMap_3Changed"
QT_MOC_LITERAL(34, 746, 22), // "FlightModeMap_4Changed"
QT_MOC_LITERAL(35, 769, 22), // "FlightModeMap_5Changed"
QT_MOC_LITERAL(36, 792, 23), // "VbarGyroSuppressChanged"
QT_MOC_LITERAL(37, 816, 19), // "VbarPiroCompChanged"
QT_MOC_LITERAL(38, 836, 19), // "VbarMaxAngleChanged"
QT_MOC_LITERAL(39, 856, 23), // "DerivativeCutoffChanged"
QT_MOC_LITERAL(40, 880, 18), // "MaxAxisLockChanged"
QT_MOC_LITERAL(41, 899, 22), // "MaxAxisLockRateChanged"
QT_MOC_LITERAL(42, 922, 26), // "MaxWeakLevelingRateChanged"
QT_MOC_LITERAL(43, 949, 30), // "RattitudeModeTransitionChanged"
QT_MOC_LITERAL(44, 980, 29), // "CruiseControlMinThrustChanged"
QT_MOC_LITERAL(45, 1010, 29), // "CruiseControlMaxThrustChanged"
QT_MOC_LITERAL(46, 1040, 28), // "CruiseControlMaxAngleChanged"
QT_MOC_LITERAL(47, 1069, 45), // "CruiseControlFlightModeSwitch..."
QT_MOC_LITERAL(48, 1115, 47), // "CruiseControlFlightModeSwitch..."
QT_MOC_LITERAL(49, 1163, 47), // "CruiseControlFlightModeSwitch..."
QT_MOC_LITERAL(50, 1211, 47), // "CruiseControlFlightModeSwitch..."
QT_MOC_LITERAL(51, 1259, 47), // "CruiseControlFlightModeSwitch..."
QT_MOC_LITERAL(52, 1307, 47), // "CruiseControlFlightModeSwitch..."
QT_MOC_LITERAL(53, 1355, 47), // "CruiseControlFlightModeSwitch..."
QT_MOC_LITERAL(54, 1403, 43), // "CruiseControlInvertedThrustRe..."
QT_MOC_LITERAL(55, 1447, 39), // "CruiseControlInvertedPowerOut..."
QT_MOC_LITERAL(56, 1487, 30), // "LowThrottleZeroIntegralChanged"
QT_MOC_LITERAL(57, 1518, 26), // "FlightModeAssistMapChanged"
QT_MOC_LITERAL(58, 1545, 28), // "FlightModeAssistMap_0Changed"
QT_MOC_LITERAL(59, 1574, 28), // "FlightModeAssistMap_1Changed"
QT_MOC_LITERAL(60, 1603, 28), // "FlightModeAssistMap_2Changed"
QT_MOC_LITERAL(61, 1632, 28), // "FlightModeAssistMap_3Changed"
QT_MOC_LITERAL(62, 1661, 28), // "FlightModeAssistMap_4Changed"
QT_MOC_LITERAL(63, 1690, 28), // "FlightModeAssistMap_5Changed"
QT_MOC_LITERAL(64, 1719, 18), // "setVbarSensitivity"
QT_MOC_LITERAL(65, 1738, 23), // "setVbarSensitivity_Roll"
QT_MOC_LITERAL(66, 1762, 24), // "setVbarSensitivity_Pitch"
QT_MOC_LITERAL(67, 1787, 22), // "setVbarSensitivity_Yaw"
QT_MOC_LITERAL(68, 1810, 13), // "setVbarRollPI"
QT_MOC_LITERAL(69, 1824, 16), // "setVbarRollPI_Kp"
QT_MOC_LITERAL(70, 1841, 16), // "setVbarRollPI_Ki"
QT_MOC_LITERAL(71, 1858, 14), // "setVbarPitchPI"
QT_MOC_LITERAL(72, 1873, 17), // "setVbarPitchPI_Kp"
QT_MOC_LITERAL(73, 1891, 17), // "setVbarPitchPI_Ki"
QT_MOC_LITERAL(74, 1909, 12), // "setVbarYawPI"
QT_MOC_LITERAL(75, 1922, 15), // "setVbarYawPI_Kp"
QT_MOC_LITERAL(76, 1938, 15), // "setVbarYawPI_Ki"
QT_MOC_LITERAL(77, 1954, 10), // "setVbarTau"
QT_MOC_LITERAL(78, 1965, 10), // "setGyroTau"
QT_MOC_LITERAL(79, 1976, 18), // "setDerivativeGamma"
QT_MOC_LITERAL(80, 1995, 13), // "setAxisLockKp"
QT_MOC_LITERAL(81, 2009, 17), // "setWeakLevelingKp"
QT_MOC_LITERAL(82, 2027, 30), // "setCruiseControlMaxPowerFactor"
QT_MOC_LITERAL(83, 2058, 25), // "setCruiseControlPowerTrim"
QT_MOC_LITERAL(84, 2084, 30), // "setCruiseControlPowerDelayComp"
QT_MOC_LITERAL(85, 2115, 18), // "setScaleToAirspeed"
QT_MOC_LITERAL(86, 2134, 24), // "setScaleToAirspeedLimits"
QT_MOC_LITERAL(87, 2159, 28), // "setScaleToAirspeedLimits_Min"
QT_MOC_LITERAL(88, 2188, 28), // "setScaleToAirspeedLimits_Max"
QT_MOC_LITERAL(89, 2217, 16), // "setFlightModeMap"
QT_MOC_LITERAL(90, 2234, 18), // "setFlightModeMap_0"
QT_MOC_LITERAL(91, 2253, 18), // "setFlightModeMap_1"
QT_MOC_LITERAL(92, 2272, 18), // "setFlightModeMap_2"
QT_MOC_LITERAL(93, 2291, 18), // "setFlightModeMap_3"
QT_MOC_LITERAL(94, 2310, 18), // "setFlightModeMap_4"
QT_MOC_LITERAL(95, 2329, 18), // "setFlightModeMap_5"
QT_MOC_LITERAL(96, 2348, 19), // "setVbarGyroSuppress"
QT_MOC_LITERAL(97, 2368, 15), // "setVbarPiroComp"
QT_MOC_LITERAL(98, 2384, 15), // "setVbarMaxAngle"
QT_MOC_LITERAL(99, 2400, 19), // "setDerivativeCutoff"
QT_MOC_LITERAL(100, 2420, 14), // "setMaxAxisLock"
QT_MOC_LITERAL(101, 2435, 18), // "setMaxAxisLockRate"
QT_MOC_LITERAL(102, 2454, 22), // "setMaxWeakLevelingRate"
QT_MOC_LITERAL(103, 2477, 26), // "setRattitudeModeTransition"
QT_MOC_LITERAL(104, 2504, 25), // "setCruiseControlMinThrust"
QT_MOC_LITERAL(105, 2530, 25), // "setCruiseControlMaxThrust"
QT_MOC_LITERAL(106, 2556, 24), // "setCruiseControlMaxAngle"
QT_MOC_LITERAL(107, 2581, 41), // "setCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(108, 2623, 43), // "setCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(109, 2667, 43), // "setCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(110, 2711, 43), // "setCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(111, 2755, 43), // "setCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(112, 2799, 43), // "setCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(113, 2843, 43), // "setCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(114, 2887, 39), // "setCruiseControlInvertedThrus..."
QT_MOC_LITERAL(115, 2927, 35), // "setCruiseControlInvertedPower..."
QT_MOC_LITERAL(116, 2963, 26), // "setLowThrottleZeroIntegral"
QT_MOC_LITERAL(117, 2990, 22), // "setFlightModeAssistMap"
QT_MOC_LITERAL(118, 3013, 24), // "setFlightModeAssistMap_0"
QT_MOC_LITERAL(119, 3038, 24), // "setFlightModeAssistMap_1"
QT_MOC_LITERAL(120, 3063, 24), // "setFlightModeAssistMap_2"
QT_MOC_LITERAL(121, 3088, 24), // "setFlightModeAssistMap_3"
QT_MOC_LITERAL(122, 3113, 24), // "setFlightModeAssistMap_4"
QT_MOC_LITERAL(123, 3138, 24), // "setFlightModeAssistMap_5"
QT_MOC_LITERAL(124, 3163, 17), // "emitNotifications"
QT_MOC_LITERAL(125, 3181, 18), // "getVbarSensitivity"
QT_MOC_LITERAL(126, 3200, 23), // "getVbarSensitivity_Roll"
QT_MOC_LITERAL(127, 3224, 24), // "getVbarSensitivity_Pitch"
QT_MOC_LITERAL(128, 3249, 22), // "getVbarSensitivity_Yaw"
QT_MOC_LITERAL(129, 3272, 13), // "getVbarRollPI"
QT_MOC_LITERAL(130, 3286, 16), // "getVbarRollPI_Kp"
QT_MOC_LITERAL(131, 3303, 16), // "getVbarRollPI_Ki"
QT_MOC_LITERAL(132, 3320, 14), // "getVbarPitchPI"
QT_MOC_LITERAL(133, 3335, 17), // "getVbarPitchPI_Kp"
QT_MOC_LITERAL(134, 3353, 17), // "getVbarPitchPI_Ki"
QT_MOC_LITERAL(135, 3371, 12), // "getVbarYawPI"
QT_MOC_LITERAL(136, 3384, 15), // "getVbarYawPI_Kp"
QT_MOC_LITERAL(137, 3400, 15), // "getVbarYawPI_Ki"
QT_MOC_LITERAL(138, 3416, 10), // "getVbarTau"
QT_MOC_LITERAL(139, 3427, 10), // "getGyroTau"
QT_MOC_LITERAL(140, 3438, 18), // "getDerivativeGamma"
QT_MOC_LITERAL(141, 3457, 13), // "getAxisLockKp"
QT_MOC_LITERAL(142, 3471, 17), // "getWeakLevelingKp"
QT_MOC_LITERAL(143, 3489, 30), // "getCruiseControlMaxPowerFactor"
QT_MOC_LITERAL(144, 3520, 25), // "getCruiseControlPowerTrim"
QT_MOC_LITERAL(145, 3546, 30), // "getCruiseControlPowerDelayComp"
QT_MOC_LITERAL(146, 3577, 18), // "getScaleToAirspeed"
QT_MOC_LITERAL(147, 3596, 24), // "getScaleToAirspeedLimits"
QT_MOC_LITERAL(148, 3621, 28), // "getScaleToAirspeedLimits_Min"
QT_MOC_LITERAL(149, 3650, 28), // "getScaleToAirspeedLimits_Max"
QT_MOC_LITERAL(150, 3679, 16), // "getFlightModeMap"
QT_MOC_LITERAL(151, 3696, 18), // "getFlightModeMap_0"
QT_MOC_LITERAL(152, 3715, 18), // "getFlightModeMap_1"
QT_MOC_LITERAL(153, 3734, 18), // "getFlightModeMap_2"
QT_MOC_LITERAL(154, 3753, 18), // "getFlightModeMap_3"
QT_MOC_LITERAL(155, 3772, 18), // "getFlightModeMap_4"
QT_MOC_LITERAL(156, 3791, 18), // "getFlightModeMap_5"
QT_MOC_LITERAL(157, 3810, 19), // "getVbarGyroSuppress"
QT_MOC_LITERAL(158, 3830, 15), // "getVbarPiroComp"
QT_MOC_LITERAL(159, 3846, 15), // "getVbarMaxAngle"
QT_MOC_LITERAL(160, 3862, 19), // "getDerivativeCutoff"
QT_MOC_LITERAL(161, 3882, 14), // "getMaxAxisLock"
QT_MOC_LITERAL(162, 3897, 18), // "getMaxAxisLockRate"
QT_MOC_LITERAL(163, 3916, 22), // "getMaxWeakLevelingRate"
QT_MOC_LITERAL(164, 3939, 26), // "getRattitudeModeTransition"
QT_MOC_LITERAL(165, 3966, 25), // "getCruiseControlMinThrust"
QT_MOC_LITERAL(166, 3992, 25), // "getCruiseControlMaxThrust"
QT_MOC_LITERAL(167, 4018, 24), // "getCruiseControlMaxAngle"
QT_MOC_LITERAL(168, 4043, 41), // "getCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(169, 4085, 43), // "getCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(170, 4129, 43), // "getCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(171, 4173, 43), // "getCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(172, 4217, 43), // "getCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(173, 4261, 43), // "getCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(174, 4305, 43), // "getCruiseControlFlightModeSwi..."
QT_MOC_LITERAL(175, 4349, 39), // "getCruiseControlInvertedThrus..."
QT_MOC_LITERAL(176, 4389, 35), // "getCruiseControlInvertedPower..."
QT_MOC_LITERAL(177, 4425, 26), // "getLowThrottleZeroIntegral"
QT_MOC_LITERAL(178, 4452, 22), // "getFlightModeAssistMap"
QT_MOC_LITERAL(179, 4475, 24), // "getFlightModeAssistMap_0"
QT_MOC_LITERAL(180, 4500, 24), // "getFlightModeAssistMap_1"
QT_MOC_LITERAL(181, 4525, 24), // "getFlightModeAssistMap_2"
QT_MOC_LITERAL(182, 4550, 24), // "getFlightModeAssistMap_3"
QT_MOC_LITERAL(183, 4575, 24), // "getFlightModeAssistMap_4"
QT_MOC_LITERAL(184, 4600, 24), // "getFlightModeAssistMap_5"
QT_MOC_LITERAL(185, 4625, 20), // "VbarSensitivity_Roll"
QT_MOC_LITERAL(186, 4646, 21), // "VbarSensitivity_Pitch"
QT_MOC_LITERAL(187, 4668, 19), // "VbarSensitivity_Yaw"
QT_MOC_LITERAL(188, 4688, 13), // "VbarRollPI_Kp"
QT_MOC_LITERAL(189, 4702, 13), // "VbarRollPI_Ki"
QT_MOC_LITERAL(190, 4716, 14), // "VbarPitchPI_Kp"
QT_MOC_LITERAL(191, 4731, 14), // "VbarPitchPI_Ki"
QT_MOC_LITERAL(192, 4746, 12), // "VbarYawPI_Kp"
QT_MOC_LITERAL(193, 4759, 12), // "VbarYawPI_Ki"
QT_MOC_LITERAL(194, 4772, 7), // "VbarTau"
QT_MOC_LITERAL(195, 4780, 7), // "GyroTau"
QT_MOC_LITERAL(196, 4788, 15), // "DerivativeGamma"
QT_MOC_LITERAL(197, 4804, 10), // "AxisLockKp"
QT_MOC_LITERAL(198, 4815, 14), // "WeakLevelingKp"
QT_MOC_LITERAL(199, 4830, 27), // "CruiseControlMaxPowerFactor"
QT_MOC_LITERAL(200, 4858, 22), // "CruiseControlPowerTrim"
QT_MOC_LITERAL(201, 4881, 27), // "CruiseControlPowerDelayComp"
QT_MOC_LITERAL(202, 4909, 15), // "ScaleToAirspeed"
QT_MOC_LITERAL(203, 4925, 25), // "ScaleToAirspeedLimits_Min"
QT_MOC_LITERAL(204, 4951, 25), // "ScaleToAirspeedLimits_Max"
QT_MOC_LITERAL(205, 4977, 15), // "FlightModeMap_0"
QT_MOC_LITERAL(206, 4993, 15), // "FlightModeMap_1"
QT_MOC_LITERAL(207, 5009, 15), // "FlightModeMap_2"
QT_MOC_LITERAL(208, 5025, 15), // "FlightModeMap_3"
QT_MOC_LITERAL(209, 5041, 15), // "FlightModeMap_4"
QT_MOC_LITERAL(210, 5057, 15), // "FlightModeMap_5"
QT_MOC_LITERAL(211, 5073, 16), // "VbarGyroSuppress"
QT_MOC_LITERAL(212, 5090, 12), // "VbarPiroComp"
QT_MOC_LITERAL(213, 5103, 12), // "VbarMaxAngle"
QT_MOC_LITERAL(214, 5116, 16), // "DerivativeCutoff"
QT_MOC_LITERAL(215, 5133, 11), // "MaxAxisLock"
QT_MOC_LITERAL(216, 5145, 15), // "MaxAxisLockRate"
QT_MOC_LITERAL(217, 5161, 19), // "MaxWeakLevelingRate"
QT_MOC_LITERAL(218, 5181, 23), // "RattitudeModeTransition"
QT_MOC_LITERAL(219, 5205, 22), // "CruiseControlMinThrust"
QT_MOC_LITERAL(220, 5228, 22), // "CruiseControlMaxThrust"
QT_MOC_LITERAL(221, 5251, 21), // "CruiseControlMaxAngle"
QT_MOC_LITERAL(222, 5273, 40), // "CruiseControlFlightModeSwitch..."
QT_MOC_LITERAL(223, 5314, 40), // "CruiseControlFlightModeSwitch..."
QT_MOC_LITERAL(224, 5355, 40), // "CruiseControlFlightModeSwitch..."
QT_MOC_LITERAL(225, 5396, 40), // "CruiseControlFlightModeSwitch..."
QT_MOC_LITERAL(226, 5437, 40), // "CruiseControlFlightModeSwitch..."
QT_MOC_LITERAL(227, 5478, 40), // "CruiseControlFlightModeSwitch..."
QT_MOC_LITERAL(228, 5519, 36), // "CruiseControlInvertedThrustRe..."
QT_MOC_LITERAL(229, 5556, 32), // "CruiseControlInvertedPowerOutput"
QT_MOC_LITERAL(230, 5589, 23), // "LowThrottleZeroIntegral"
QT_MOC_LITERAL(231, 5613, 21), // "FlightModeAssistMap_0"
QT_MOC_LITERAL(232, 5635, 21), // "FlightModeAssistMap_1"
QT_MOC_LITERAL(233, 5657, 21), // "FlightModeAssistMap_2"
QT_MOC_LITERAL(234, 5679, 21), // "FlightModeAssistMap_3"
QT_MOC_LITERAL(235, 5701, 21), // "FlightModeAssistMap_4"
QT_MOC_LITERAL(236, 5723, 21) // "FlightModeAssistMap_5"

    },
    "StabilizationSettings\0VbarSensitivityChanged\0"
    "\0index\0value\0VbarSensitivity_RollChanged\0"
    "VbarSensitivity_PitchChanged\0"
    "VbarSensitivity_YawChanged\0VbarRollPIChanged\0"
    "VbarRollPI_KpChanged\0VbarRollPI_KiChanged\0"
    "VbarPitchPIChanged\0VbarPitchPI_KpChanged\0"
    "VbarPitchPI_KiChanged\0VbarYawPIChanged\0"
    "VbarYawPI_KpChanged\0VbarYawPI_KiChanged\0"
    "VbarTauChanged\0GyroTauChanged\0"
    "DerivativeGammaChanged\0AxisLockKpChanged\0"
    "WeakLevelingKpChanged\0"
    "CruiseControlMaxPowerFactorChanged\0"
    "CruiseControlPowerTrimChanged\0"
    "CruiseControlPowerDelayCompChanged\0"
    "ScaleToAirspeedChanged\0"
    "ScaleToAirspeedLimitsChanged\0"
    "ScaleToAirspeedLimits_MinChanged\0"
    "ScaleToAirspeedLimits_MaxChanged\0"
    "FlightModeMapChanged\0FlightModeMap_0Changed\0"
    "FlightModeMap_1Changed\0FlightModeMap_2Changed\0"
    "FlightModeMap_3Changed\0FlightModeMap_4Changed\0"
    "FlightModeMap_5Changed\0VbarGyroSuppressChanged\0"
    "VbarPiroCompChanged\0VbarMaxAngleChanged\0"
    "DerivativeCutoffChanged\0MaxAxisLockChanged\0"
    "MaxAxisLockRateChanged\0"
    "MaxWeakLevelingRateChanged\0"
    "RattitudeModeTransitionChanged\0"
    "CruiseControlMinThrustChanged\0"
    "CruiseControlMaxThrustChanged\0"
    "CruiseControlMaxAngleChanged\0"
    "CruiseControlFlightModeSwitchPosEnableChanged\0"
    "CruiseControlFlightModeSwitchPosEnable_0Changed\0"
    "CruiseControlFlightModeSwitchPosEnable_1Changed\0"
    "CruiseControlFlightModeSwitchPosEnable_2Changed\0"
    "CruiseControlFlightModeSwitchPosEnable_3Changed\0"
    "CruiseControlFlightModeSwitchPosEnable_4Changed\0"
    "CruiseControlFlightModeSwitchPosEnable_5Changed\0"
    "CruiseControlInvertedThrustReversingChanged\0"
    "CruiseControlInvertedPowerOutputChanged\0"
    "LowThrottleZeroIntegralChanged\0"
    "FlightModeAssistMapChanged\0"
    "FlightModeAssistMap_0Changed\0"
    "FlightModeAssistMap_1Changed\0"
    "FlightModeAssistMap_2Changed\0"
    "FlightModeAssistMap_3Changed\0"
    "FlightModeAssistMap_4Changed\0"
    "FlightModeAssistMap_5Changed\0"
    "setVbarSensitivity\0setVbarSensitivity_Roll\0"
    "setVbarSensitivity_Pitch\0"
    "setVbarSensitivity_Yaw\0setVbarRollPI\0"
    "setVbarRollPI_Kp\0setVbarRollPI_Ki\0"
    "setVbarPitchPI\0setVbarPitchPI_Kp\0"
    "setVbarPitchPI_Ki\0setVbarYawPI\0"
    "setVbarYawPI_Kp\0setVbarYawPI_Ki\0"
    "setVbarTau\0setGyroTau\0setDerivativeGamma\0"
    "setAxisLockKp\0setWeakLevelingKp\0"
    "setCruiseControlMaxPowerFactor\0"
    "setCruiseControlPowerTrim\0"
    "setCruiseControlPowerDelayComp\0"
    "setScaleToAirspeed\0setScaleToAirspeedLimits\0"
    "setScaleToAirspeedLimits_Min\0"
    "setScaleToAirspeedLimits_Max\0"
    "setFlightModeMap\0setFlightModeMap_0\0"
    "setFlightModeMap_1\0setFlightModeMap_2\0"
    "setFlightModeMap_3\0setFlightModeMap_4\0"
    "setFlightModeMap_5\0setVbarGyroSuppress\0"
    "setVbarPiroComp\0setVbarMaxAngle\0"
    "setDerivativeCutoff\0setMaxAxisLock\0"
    "setMaxAxisLockRate\0setMaxWeakLevelingRate\0"
    "setRattitudeModeTransition\0"
    "setCruiseControlMinThrust\0"
    "setCruiseControlMaxThrust\0"
    "setCruiseControlMaxAngle\0"
    "setCruiseControlFlightModeSwitchPosEnable\0"
    "setCruiseControlFlightModeSwitchPosEnable_0\0"
    "setCruiseControlFlightModeSwitchPosEnable_1\0"
    "setCruiseControlFlightModeSwitchPosEnable_2\0"
    "setCruiseControlFlightModeSwitchPosEnable_3\0"
    "setCruiseControlFlightModeSwitchPosEnable_4\0"
    "setCruiseControlFlightModeSwitchPosEnable_5\0"
    "setCruiseControlInvertedThrustReversing\0"
    "setCruiseControlInvertedPowerOutput\0"
    "setLowThrottleZeroIntegral\0"
    "setFlightModeAssistMap\0setFlightModeAssistMap_0\0"
    "setFlightModeAssistMap_1\0"
    "setFlightModeAssistMap_2\0"
    "setFlightModeAssistMap_3\0"
    "setFlightModeAssistMap_4\0"
    "setFlightModeAssistMap_5\0emitNotifications\0"
    "getVbarSensitivity\0getVbarSensitivity_Roll\0"
    "getVbarSensitivity_Pitch\0"
    "getVbarSensitivity_Yaw\0getVbarRollPI\0"
    "getVbarRollPI_Kp\0getVbarRollPI_Ki\0"
    "getVbarPitchPI\0getVbarPitchPI_Kp\0"
    "getVbarPitchPI_Ki\0getVbarYawPI\0"
    "getVbarYawPI_Kp\0getVbarYawPI_Ki\0"
    "getVbarTau\0getGyroTau\0getDerivativeGamma\0"
    "getAxisLockKp\0getWeakLevelingKp\0"
    "getCruiseControlMaxPowerFactor\0"
    "getCruiseControlPowerTrim\0"
    "getCruiseControlPowerDelayComp\0"
    "getScaleToAirspeed\0getScaleToAirspeedLimits\0"
    "getScaleToAirspeedLimits_Min\0"
    "getScaleToAirspeedLimits_Max\0"
    "getFlightModeMap\0getFlightModeMap_0\0"
    "getFlightModeMap_1\0getFlightModeMap_2\0"
    "getFlightModeMap_3\0getFlightModeMap_4\0"
    "getFlightModeMap_5\0getVbarGyroSuppress\0"
    "getVbarPiroComp\0getVbarMaxAngle\0"
    "getDerivativeCutoff\0getMaxAxisLock\0"
    "getMaxAxisLockRate\0getMaxWeakLevelingRate\0"
    "getRattitudeModeTransition\0"
    "getCruiseControlMinThrust\0"
    "getCruiseControlMaxThrust\0"
    "getCruiseControlMaxAngle\0"
    "getCruiseControlFlightModeSwitchPosEnable\0"
    "getCruiseControlFlightModeSwitchPosEnable_0\0"
    "getCruiseControlFlightModeSwitchPosEnable_1\0"
    "getCruiseControlFlightModeSwitchPosEnable_2\0"
    "getCruiseControlFlightModeSwitchPosEnable_3\0"
    "getCruiseControlFlightModeSwitchPosEnable_4\0"
    "getCruiseControlFlightModeSwitchPosEnable_5\0"
    "getCruiseControlInvertedThrustReversing\0"
    "getCruiseControlInvertedPowerOutput\0"
    "getLowThrottleZeroIntegral\0"
    "getFlightModeAssistMap\0getFlightModeAssistMap_0\0"
    "getFlightModeAssistMap_1\0"
    "getFlightModeAssistMap_2\0"
    "getFlightModeAssistMap_3\0"
    "getFlightModeAssistMap_4\0"
    "getFlightModeAssistMap_5\0VbarSensitivity_Roll\0"
    "VbarSensitivity_Pitch\0VbarSensitivity_Yaw\0"
    "VbarRollPI_Kp\0VbarRollPI_Ki\0VbarPitchPI_Kp\0"
    "VbarPitchPI_Ki\0VbarYawPI_Kp\0VbarYawPI_Ki\0"
    "VbarTau\0GyroTau\0DerivativeGamma\0"
    "AxisLockKp\0WeakLevelingKp\0"
    "CruiseControlMaxPowerFactor\0"
    "CruiseControlPowerTrim\0"
    "CruiseControlPowerDelayComp\0ScaleToAirspeed\0"
    "ScaleToAirspeedLimits_Min\0"
    "ScaleToAirspeedLimits_Max\0FlightModeMap_0\0"
    "FlightModeMap_1\0FlightModeMap_2\0"
    "FlightModeMap_3\0FlightModeMap_4\0"
    "FlightModeMap_5\0VbarGyroSuppress\0"
    "VbarPiroComp\0VbarMaxAngle\0DerivativeCutoff\0"
    "MaxAxisLock\0MaxAxisLockRate\0"
    "MaxWeakLevelingRate\0RattitudeModeTransition\0"
    "CruiseControlMinThrust\0CruiseControlMaxThrust\0"
    "CruiseControlMaxAngle\0"
    "CruiseControlFlightModeSwitchPosEnable_0\0"
    "CruiseControlFlightModeSwitchPosEnable_1\0"
    "CruiseControlFlightModeSwitchPosEnable_2\0"
    "CruiseControlFlightModeSwitchPosEnable_3\0"
    "CruiseControlFlightModeSwitchPosEnable_4\0"
    "CruiseControlFlightModeSwitchPosEnable_5\0"
    "CruiseControlInvertedThrustReversing\0"
    "CruiseControlInvertedPowerOutput\0"
    "LowThrottleZeroIntegral\0FlightModeAssistMap_0\0"
    "FlightModeAssistMap_1\0FlightModeAssistMap_2\0"
    "FlightModeAssistMap_3\0FlightModeAssistMap_4\0"
    "FlightModeAssistMap_5"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StabilizationSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     181,   14, // methods
      52, 1388, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      60,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  919,    2, 0x06 /* Public */,
       5,    1,  924,    2, 0x06 /* Public */,
       6,    1,  927,    2, 0x06 /* Public */,
       7,    1,  930,    2, 0x06 /* Public */,
       8,    2,  933,    2, 0x06 /* Public */,
       9,    1,  938,    2, 0x06 /* Public */,
      10,    1,  941,    2, 0x06 /* Public */,
      11,    2,  944,    2, 0x06 /* Public */,
      12,    1,  949,    2, 0x06 /* Public */,
      13,    1,  952,    2, 0x06 /* Public */,
      14,    2,  955,    2, 0x06 /* Public */,
      15,    1,  960,    2, 0x06 /* Public */,
      16,    1,  963,    2, 0x06 /* Public */,
      17,    1,  966,    2, 0x06 /* Public */,
      18,    1,  969,    2, 0x06 /* Public */,
      19,    1,  972,    2, 0x06 /* Public */,
      20,    1,  975,    2, 0x06 /* Public */,
      21,    1,  978,    2, 0x06 /* Public */,
      22,    1,  981,    2, 0x06 /* Public */,
      23,    1,  984,    2, 0x06 /* Public */,
      24,    1,  987,    2, 0x06 /* Public */,
      25,    1,  990,    2, 0x06 /* Public */,
      26,    2,  993,    2, 0x06 /* Public */,
      27,    1,  998,    2, 0x06 /* Public */,
      28,    1, 1001,    2, 0x06 /* Public */,
      29,    2, 1004,    2, 0x06 /* Public */,
      30,    1, 1009,    2, 0x06 /* Public */,
      31,    1, 1012,    2, 0x06 /* Public */,
      32,    1, 1015,    2, 0x06 /* Public */,
      33,    1, 1018,    2, 0x06 /* Public */,
      34,    1, 1021,    2, 0x06 /* Public */,
      35,    1, 1024,    2, 0x06 /* Public */,
      36,    1, 1027,    2, 0x06 /* Public */,
      37,    1, 1030,    2, 0x06 /* Public */,
      38,    1, 1033,    2, 0x06 /* Public */,
      39,    1, 1036,    2, 0x06 /* Public */,
      40,    1, 1039,    2, 0x06 /* Public */,
      41,    1, 1042,    2, 0x06 /* Public */,
      42,    1, 1045,    2, 0x06 /* Public */,
      43,    1, 1048,    2, 0x06 /* Public */,
      44,    1, 1051,    2, 0x06 /* Public */,
      45,    1, 1054,    2, 0x06 /* Public */,
      46,    1, 1057,    2, 0x06 /* Public */,
      47,    2, 1060,    2, 0x06 /* Public */,
      48,    1, 1065,    2, 0x06 /* Public */,
      49,    1, 1068,    2, 0x06 /* Public */,
      50,    1, 1071,    2, 0x06 /* Public */,
      51,    1, 1074,    2, 0x06 /* Public */,
      52,    1, 1077,    2, 0x06 /* Public */,
      53,    1, 1080,    2, 0x06 /* Public */,
      54,    1, 1083,    2, 0x06 /* Public */,
      55,    1, 1086,    2, 0x06 /* Public */,
      56,    1, 1089,    2, 0x06 /* Public */,
      57,    2, 1092,    2, 0x06 /* Public */,
      58,    1, 1097,    2, 0x06 /* Public */,
      59,    1, 1100,    2, 0x06 /* Public */,
      60,    1, 1103,    2, 0x06 /* Public */,
      61,    1, 1106,    2, 0x06 /* Public */,
      62,    1, 1109,    2, 0x06 /* Public */,
      63,    1, 1112,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      64,    2, 1115,    2, 0x0a /* Public */,
      65,    1, 1120,    2, 0x0a /* Public */,
      66,    1, 1123,    2, 0x0a /* Public */,
      67,    1, 1126,    2, 0x0a /* Public */,
      68,    2, 1129,    2, 0x0a /* Public */,
      69,    1, 1134,    2, 0x0a /* Public */,
      70,    1, 1137,    2, 0x0a /* Public */,
      71,    2, 1140,    2, 0x0a /* Public */,
      72,    1, 1145,    2, 0x0a /* Public */,
      73,    1, 1148,    2, 0x0a /* Public */,
      74,    2, 1151,    2, 0x0a /* Public */,
      75,    1, 1156,    2, 0x0a /* Public */,
      76,    1, 1159,    2, 0x0a /* Public */,
      77,    1, 1162,    2, 0x0a /* Public */,
      78,    1, 1165,    2, 0x0a /* Public */,
      79,    1, 1168,    2, 0x0a /* Public */,
      80,    1, 1171,    2, 0x0a /* Public */,
      81,    1, 1174,    2, 0x0a /* Public */,
      82,    1, 1177,    2, 0x0a /* Public */,
      83,    1, 1180,    2, 0x0a /* Public */,
      84,    1, 1183,    2, 0x0a /* Public */,
      85,    1, 1186,    2, 0x0a /* Public */,
      86,    2, 1189,    2, 0x0a /* Public */,
      87,    1, 1194,    2, 0x0a /* Public */,
      88,    1, 1197,    2, 0x0a /* Public */,
      89,    2, 1200,    2, 0x0a /* Public */,
      90,    1, 1205,    2, 0x0a /* Public */,
      91,    1, 1208,    2, 0x0a /* Public */,
      92,    1, 1211,    2, 0x0a /* Public */,
      93,    1, 1214,    2, 0x0a /* Public */,
      94,    1, 1217,    2, 0x0a /* Public */,
      95,    1, 1220,    2, 0x0a /* Public */,
      96,    1, 1223,    2, 0x0a /* Public */,
      97,    1, 1226,    2, 0x0a /* Public */,
      98,    1, 1229,    2, 0x0a /* Public */,
      99,    1, 1232,    2, 0x0a /* Public */,
     100,    1, 1235,    2, 0x0a /* Public */,
     101,    1, 1238,    2, 0x0a /* Public */,
     102,    1, 1241,    2, 0x0a /* Public */,
     103,    1, 1244,    2, 0x0a /* Public */,
     104,    1, 1247,    2, 0x0a /* Public */,
     105,    1, 1250,    2, 0x0a /* Public */,
     106,    1, 1253,    2, 0x0a /* Public */,
     107,    2, 1256,    2, 0x0a /* Public */,
     108,    1, 1261,    2, 0x0a /* Public */,
     109,    1, 1264,    2, 0x0a /* Public */,
     110,    1, 1267,    2, 0x0a /* Public */,
     111,    1, 1270,    2, 0x0a /* Public */,
     112,    1, 1273,    2, 0x0a /* Public */,
     113,    1, 1276,    2, 0x0a /* Public */,
     114,    1, 1279,    2, 0x0a /* Public */,
     115,    1, 1282,    2, 0x0a /* Public */,
     116,    1, 1285,    2, 0x0a /* Public */,
     117,    2, 1288,    2, 0x0a /* Public */,
     118,    1, 1293,    2, 0x0a /* Public */,
     119,    1, 1296,    2, 0x0a /* Public */,
     120,    1, 1299,    2, 0x0a /* Public */,
     121,    1, 1302,    2, 0x0a /* Public */,
     122,    1, 1305,    2, 0x0a /* Public */,
     123,    1, 1308,    2, 0x0a /* Public */,
     124,    0, 1311,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
     125,    1, 1312,    2, 0x02 /* Public */,
     126,    0, 1315,    2, 0x02 /* Public */,
     127,    0, 1316,    2, 0x02 /* Public */,
     128,    0, 1317,    2, 0x02 /* Public */,
     129,    1, 1318,    2, 0x02 /* Public */,
     130,    0, 1321,    2, 0x02 /* Public */,
     131,    0, 1322,    2, 0x02 /* Public */,
     132,    1, 1323,    2, 0x02 /* Public */,
     133,    0, 1326,    2, 0x02 /* Public */,
     134,    0, 1327,    2, 0x02 /* Public */,
     135,    1, 1328,    2, 0x02 /* Public */,
     136,    0, 1331,    2, 0x02 /* Public */,
     137,    0, 1332,    2, 0x02 /* Public */,
     138,    0, 1333,    2, 0x02 /* Public */,
     139,    0, 1334,    2, 0x02 /* Public */,
     140,    0, 1335,    2, 0x02 /* Public */,
     141,    0, 1336,    2, 0x02 /* Public */,
     142,    0, 1337,    2, 0x02 /* Public */,
     143,    0, 1338,    2, 0x02 /* Public */,
     144,    0, 1339,    2, 0x02 /* Public */,
     145,    0, 1340,    2, 0x02 /* Public */,
     146,    0, 1341,    2, 0x02 /* Public */,
     147,    1, 1342,    2, 0x02 /* Public */,
     148,    0, 1345,    2, 0x02 /* Public */,
     149,    0, 1346,    2, 0x02 /* Public */,
     150,    1, 1347,    2, 0x02 /* Public */,
     151,    0, 1350,    2, 0x02 /* Public */,
     152,    0, 1351,    2, 0x02 /* Public */,
     153,    0, 1352,    2, 0x02 /* Public */,
     154,    0, 1353,    2, 0x02 /* Public */,
     155,    0, 1354,    2, 0x02 /* Public */,
     156,    0, 1355,    2, 0x02 /* Public */,
     157,    0, 1356,    2, 0x02 /* Public */,
     158,    0, 1357,    2, 0x02 /* Public */,
     159,    0, 1358,    2, 0x02 /* Public */,
     160,    0, 1359,    2, 0x02 /* Public */,
     161,    0, 1360,    2, 0x02 /* Public */,
     162,    0, 1361,    2, 0x02 /* Public */,
     163,    0, 1362,    2, 0x02 /* Public */,
     164,    0, 1363,    2, 0x02 /* Public */,
     165,    0, 1364,    2, 0x02 /* Public */,
     166,    0, 1365,    2, 0x02 /* Public */,
     167,    0, 1366,    2, 0x02 /* Public */,
     168,    1, 1367,    2, 0x02 /* Public */,
     169,    0, 1370,    2, 0x02 /* Public */,
     170,    0, 1371,    2, 0x02 /* Public */,
     171,    0, 1372,    2, 0x02 /* Public */,
     172,    0, 1373,    2, 0x02 /* Public */,
     173,    0, 1374,    2, 0x02 /* Public */,
     174,    0, 1375,    2, 0x02 /* Public */,
     175,    0, 1376,    2, 0x02 /* Public */,
     176,    0, 1377,    2, 0x02 /* Public */,
     177,    0, 1378,    2, 0x02 /* Public */,
     178,    1, 1379,    2, 0x02 /* Public */,
     179,    0, 1382,    2, 0x02 /* Public */,
     180,    0, 1383,    2, 0x02 /* Public */,
     181,    0, 1384,    2, 0x02 /* Public */,
     182,    0, 1385,    2, 0x02 /* Public */,
     183,    0, 1386,    2, 0x02 /* Public */,
     184,    0, 1387,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
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
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::SChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::SChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
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
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
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
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::SChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::SChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    3,    4,
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
    QMetaType::Float, QMetaType::UInt,    3,
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
    QMetaType::Float, QMetaType::UInt,    3,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UChar, QMetaType::UInt,    3,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::SChar,
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
    QMetaType::UChar, QMetaType::UInt,    3,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    3,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,

 // properties: name, type, flags
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
     200, QMetaType::Float, 0x00495103,
     201, QMetaType::Float, 0x00495103,
     202, QMetaType::Float, 0x00495103,
     203, QMetaType::Float, 0x00495103,
     204, QMetaType::Float, 0x00495103,
     205, QMetaType::UChar, 0x00495103,
     206, QMetaType::UChar, 0x00495103,
     207, QMetaType::UChar, 0x00495103,
     208, QMetaType::UChar, 0x00495103,
     209, QMetaType::UChar, 0x00495103,
     210, QMetaType::UChar, 0x00495103,
     211, QMetaType::SChar, 0x00495103,
     212, QMetaType::UChar, 0x00495103,
     213, QMetaType::UChar, 0x00495103,
     214, QMetaType::UChar, 0x00495103,
     215, QMetaType::UChar, 0x00495103,
     216, QMetaType::UChar, 0x00495103,
     217, QMetaType::UChar, 0x00495103,
     218, QMetaType::UChar, 0x00495103,
     219, QMetaType::SChar, 0x00495103,
     220, QMetaType::UChar, 0x00495103,
     221, QMetaType::UChar, 0x00495103,
     222, QMetaType::UChar, 0x00495103,
     223, QMetaType::UChar, 0x00495103,
     224, QMetaType::UChar, 0x00495103,
     225, QMetaType::UChar, 0x00495103,
     226, QMetaType::UChar, 0x00495103,
     227, QMetaType::UChar, 0x00495103,
     228, QMetaType::UChar, 0x00495103,
     229, QMetaType::UChar, 0x00495103,
     230, QMetaType::UChar, 0x00495103,
     231, QMetaType::UChar, 0x00495103,
     232, QMetaType::UChar, 0x00495103,
     233, QMetaType::UChar, 0x00495103,
     234, QMetaType::UChar, 0x00495103,
     235, QMetaType::UChar, 0x00495103,
     236, QMetaType::UChar, 0x00495103,

 // properties: notify_signal_id
       1,
       2,
       3,
       5,
       6,
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
      21,
      23,
      24,
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
      39,
      40,
      41,
      42,
      44,
      45,
      46,
      47,
      48,
      49,
      50,
      51,
      52,
      54,
      55,
      56,
      57,
      58,
      59,

       0        // eod
};

void StabilizationSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StabilizationSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->VbarSensitivityChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->VbarSensitivity_RollChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->VbarSensitivity_PitchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->VbarSensitivity_YawChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->VbarRollPIChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->VbarRollPI_KpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->VbarRollPI_KiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->VbarPitchPIChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 8: _t->VbarPitchPI_KpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->VbarPitchPI_KiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->VbarYawPIChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 11: _t->VbarYawPI_KpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->VbarYawPI_KiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->VbarTauChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->GyroTauChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->DerivativeGammaChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->AxisLockKpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 17: _t->WeakLevelingKpChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->CruiseControlMaxPowerFactorChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->CruiseControlPowerTrimChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->CruiseControlPowerDelayCompChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->ScaleToAirspeedChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: _t->ScaleToAirspeedLimitsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 23: _t->ScaleToAirspeedLimits_MinChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->ScaleToAirspeedLimits_MaxChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 25: _t->FlightModeMapChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 26: _t->FlightModeMap_0Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 27: _t->FlightModeMap_1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 28: _t->FlightModeMap_2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 29: _t->FlightModeMap_3Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 30: _t->FlightModeMap_4Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 31: _t->FlightModeMap_5Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 32: _t->VbarGyroSuppressChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 33: _t->VbarPiroCompChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 34: _t->VbarMaxAngleChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 35: _t->DerivativeCutoffChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 36: _t->MaxAxisLockChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 37: _t->MaxAxisLockRateChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 38: _t->MaxWeakLevelingRateChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 39: _t->RattitudeModeTransitionChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 40: _t->CruiseControlMinThrustChanged((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 41: _t->CruiseControlMaxThrustChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 42: _t->CruiseControlMaxAngleChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 43: _t->CruiseControlFlightModeSwitchPosEnableChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 44: _t->CruiseControlFlightModeSwitchPosEnable_0Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 45: _t->CruiseControlFlightModeSwitchPosEnable_1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 46: _t->CruiseControlFlightModeSwitchPosEnable_2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 47: _t->CruiseControlFlightModeSwitchPosEnable_3Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 48: _t->CruiseControlFlightModeSwitchPosEnable_4Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 49: _t->CruiseControlFlightModeSwitchPosEnable_5Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 50: _t->CruiseControlInvertedThrustReversingChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 51: _t->CruiseControlInvertedPowerOutputChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 52: _t->LowThrottleZeroIntegralChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 53: _t->FlightModeAssistMapChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 54: _t->FlightModeAssistMap_0Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 55: _t->FlightModeAssistMap_1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 56: _t->FlightModeAssistMap_2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 57: _t->FlightModeAssistMap_3Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 58: _t->FlightModeAssistMap_4Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 59: _t->FlightModeAssistMap_5Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 60: _t->setVbarSensitivity((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 61: _t->setVbarSensitivity_Roll((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 62: _t->setVbarSensitivity_Pitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 63: _t->setVbarSensitivity_Yaw((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 64: _t->setVbarRollPI((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 65: _t->setVbarRollPI_Kp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 66: _t->setVbarRollPI_Ki((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 67: _t->setVbarPitchPI((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 68: _t->setVbarPitchPI_Kp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 69: _t->setVbarPitchPI_Ki((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 70: _t->setVbarYawPI((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 71: _t->setVbarYawPI_Kp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 72: _t->setVbarYawPI_Ki((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 73: _t->setVbarTau((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 74: _t->setGyroTau((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 75: _t->setDerivativeGamma((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 76: _t->setAxisLockKp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 77: _t->setWeakLevelingKp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 78: _t->setCruiseControlMaxPowerFactor((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 79: _t->setCruiseControlPowerTrim((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 80: _t->setCruiseControlPowerDelayComp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 81: _t->setScaleToAirspeed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 82: _t->setScaleToAirspeedLimits((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 83: _t->setScaleToAirspeedLimits_Min((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 84: _t->setScaleToAirspeedLimits_Max((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 85: _t->setFlightModeMap((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 86: _t->setFlightModeMap_0((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 87: _t->setFlightModeMap_1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 88: _t->setFlightModeMap_2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 89: _t->setFlightModeMap_3((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 90: _t->setFlightModeMap_4((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 91: _t->setFlightModeMap_5((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 92: _t->setVbarGyroSuppress((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 93: _t->setVbarPiroComp((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 94: _t->setVbarMaxAngle((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 95: _t->setDerivativeCutoff((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 96: _t->setMaxAxisLock((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 97: _t->setMaxAxisLockRate((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 98: _t->setMaxWeakLevelingRate((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 99: _t->setRattitudeModeTransition((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 100: _t->setCruiseControlMinThrust((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 101: _t->setCruiseControlMaxThrust((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 102: _t->setCruiseControlMaxAngle((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 103: _t->setCruiseControlFlightModeSwitchPosEnable((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 104: _t->setCruiseControlFlightModeSwitchPosEnable_0((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 105: _t->setCruiseControlFlightModeSwitchPosEnable_1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 106: _t->setCruiseControlFlightModeSwitchPosEnable_2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 107: _t->setCruiseControlFlightModeSwitchPosEnable_3((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 108: _t->setCruiseControlFlightModeSwitchPosEnable_4((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 109: _t->setCruiseControlFlightModeSwitchPosEnable_5((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 110: _t->setCruiseControlInvertedThrustReversing((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 111: _t->setCruiseControlInvertedPowerOutput((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 112: _t->setLowThrottleZeroIntegral((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 113: _t->setFlightModeAssistMap((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 114: _t->setFlightModeAssistMap_0((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 115: _t->setFlightModeAssistMap_1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 116: _t->setFlightModeAssistMap_2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 117: _t->setFlightModeAssistMap_3((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 118: _t->setFlightModeAssistMap_4((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 119: _t->setFlightModeAssistMap_5((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 120: _t->emitNotifications(); break;
        case 121: { float _r = _t->getVbarSensitivity((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 122: { float _r = _t->getVbarSensitivity_Roll();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 123: { float _r = _t->getVbarSensitivity_Pitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 124: { float _r = _t->getVbarSensitivity_Yaw();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 125: { float _r = _t->getVbarRollPI((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 126: { float _r = _t->getVbarRollPI_Kp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 127: { float _r = _t->getVbarRollPI_Ki();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 128: { float _r = _t->getVbarPitchPI((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 129: { float _r = _t->getVbarPitchPI_Kp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 130: { float _r = _t->getVbarPitchPI_Ki();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 131: { float _r = _t->getVbarYawPI((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 132: { float _r = _t->getVbarYawPI_Kp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 133: { float _r = _t->getVbarYawPI_Ki();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 134: { float _r = _t->getVbarTau();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 135: { float _r = _t->getGyroTau();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 136: { float _r = _t->getDerivativeGamma();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 137: { float _r = _t->getAxisLockKp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 138: { float _r = _t->getWeakLevelingKp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 139: { float _r = _t->getCruiseControlMaxPowerFactor();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 140: { float _r = _t->getCruiseControlPowerTrim();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 141: { float _r = _t->getCruiseControlPowerDelayComp();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 142: { float _r = _t->getScaleToAirspeed();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 143: { float _r = _t->getScaleToAirspeedLimits((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 144: { float _r = _t->getScaleToAirspeedLimits_Min();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 145: { float _r = _t->getScaleToAirspeedLimits_Max();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 146: { quint8 _r = _t->getFlightModeMap((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 147: { quint8 _r = _t->getFlightModeMap_0();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 148: { quint8 _r = _t->getFlightModeMap_1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 149: { quint8 _r = _t->getFlightModeMap_2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 150: { quint8 _r = _t->getFlightModeMap_3();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 151: { quint8 _r = _t->getFlightModeMap_4();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 152: { quint8 _r = _t->getFlightModeMap_5();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 153: { qint8 _r = _t->getVbarGyroSuppress();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 154: { quint8 _r = _t->getVbarPiroComp();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 155: { quint8 _r = _t->getVbarMaxAngle();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 156: { quint8 _r = _t->getDerivativeCutoff();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 157: { quint8 _r = _t->getMaxAxisLock();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 158: { quint8 _r = _t->getMaxAxisLockRate();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 159: { quint8 _r = _t->getMaxWeakLevelingRate();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 160: { quint8 _r = _t->getRattitudeModeTransition();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 161: { qint8 _r = _t->getCruiseControlMinThrust();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 162: { quint8 _r = _t->getCruiseControlMaxThrust();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 163: { quint8 _r = _t->getCruiseControlMaxAngle();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 164: { quint8 _r = _t->getCruiseControlFlightModeSwitchPosEnable((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 165: { quint8 _r = _t->getCruiseControlFlightModeSwitchPosEnable_0();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 166: { quint8 _r = _t->getCruiseControlFlightModeSwitchPosEnable_1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 167: { quint8 _r = _t->getCruiseControlFlightModeSwitchPosEnable_2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 168: { quint8 _r = _t->getCruiseControlFlightModeSwitchPosEnable_3();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 169: { quint8 _r = _t->getCruiseControlFlightModeSwitchPosEnable_4();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 170: { quint8 _r = _t->getCruiseControlFlightModeSwitchPosEnable_5();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 171: { quint8 _r = _t->getCruiseControlInvertedThrustReversing();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 172: { quint8 _r = _t->getCruiseControlInvertedPowerOutput();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 173: { quint8 _r = _t->getLowThrottleZeroIntegral();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 174: { quint8 _r = _t->getFlightModeAssistMap((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 175: { quint8 _r = _t->getFlightModeAssistMap_0();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 176: { quint8 _r = _t->getFlightModeAssistMap_1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 177: { quint8 _r = _t->getFlightModeAssistMap_2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 178: { quint8 _r = _t->getFlightModeAssistMap_3();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 179: { quint8 _r = _t->getFlightModeAssistMap_4();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 180: { quint8 _r = _t->getFlightModeAssistMap_5();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StabilizationSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarSensitivityChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarSensitivity_RollChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarSensitivity_PitchChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarSensitivity_YawChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarRollPIChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarRollPI_KpChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarRollPI_KiChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarPitchPIChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarPitchPI_KpChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarPitchPI_KiChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarYawPIChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarYawPI_KpChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarYawPI_KiChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarTauChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::GyroTauChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::DerivativeGammaChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::AxisLockKpChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::WeakLevelingKpChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlMaxPowerFactorChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlPowerTrimChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlPowerDelayCompChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::ScaleToAirspeedChanged)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::ScaleToAirspeedLimitsChanged)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::ScaleToAirspeedLimits_MinChanged)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::ScaleToAirspeedLimits_MaxChanged)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeMapChanged)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeMap_0Changed)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeMap_1Changed)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeMap_2Changed)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeMap_3Changed)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeMap_4Changed)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeMap_5Changed)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarGyroSuppressChanged)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarPiroCompChanged)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::VbarMaxAngleChanged)) {
                *result = 34;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::DerivativeCutoffChanged)) {
                *result = 35;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::MaxAxisLockChanged)) {
                *result = 36;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::MaxAxisLockRateChanged)) {
                *result = 37;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::MaxWeakLevelingRateChanged)) {
                *result = 38;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::RattitudeModeTransitionChanged)) {
                *result = 39;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(qint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlMinThrustChanged)) {
                *result = 40;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlMaxThrustChanged)) {
                *result = 41;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlMaxAngleChanged)) {
                *result = 42;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlFlightModeSwitchPosEnableChanged)) {
                *result = 43;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlFlightModeSwitchPosEnable_0Changed)) {
                *result = 44;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlFlightModeSwitchPosEnable_1Changed)) {
                *result = 45;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlFlightModeSwitchPosEnable_2Changed)) {
                *result = 46;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlFlightModeSwitchPosEnable_3Changed)) {
                *result = 47;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlFlightModeSwitchPosEnable_4Changed)) {
                *result = 48;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlFlightModeSwitchPosEnable_5Changed)) {
                *result = 49;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlInvertedThrustReversingChanged)) {
                *result = 50;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::CruiseControlInvertedPowerOutputChanged)) {
                *result = 51;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::LowThrottleZeroIntegralChanged)) {
                *result = 52;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeAssistMapChanged)) {
                *result = 53;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeAssistMap_0Changed)) {
                *result = 54;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeAssistMap_1Changed)) {
                *result = 55;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeAssistMap_2Changed)) {
                *result = 56;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeAssistMap_3Changed)) {
                *result = 57;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeAssistMap_4Changed)) {
                *result = 58;
                return;
            }
        }
        {
            using _t = void (StabilizationSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StabilizationSettings::FlightModeAssistMap_5Changed)) {
                *result = 59;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<StabilizationSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getVbarSensitivity_Roll(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getVbarSensitivity_Pitch(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getVbarSensitivity_Yaw(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getVbarRollPI_Kp(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getVbarRollPI_Ki(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->getVbarPitchPI_Kp(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->getVbarPitchPI_Ki(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->getVbarYawPI_Kp(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->getVbarYawPI_Ki(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->getVbarTau(); break;
        case 10: *reinterpret_cast< float*>(_v) = _t->getGyroTau(); break;
        case 11: *reinterpret_cast< float*>(_v) = _t->getDerivativeGamma(); break;
        case 12: *reinterpret_cast< float*>(_v) = _t->getAxisLockKp(); break;
        case 13: *reinterpret_cast< float*>(_v) = _t->getWeakLevelingKp(); break;
        case 14: *reinterpret_cast< float*>(_v) = _t->getCruiseControlMaxPowerFactor(); break;
        case 15: *reinterpret_cast< float*>(_v) = _t->getCruiseControlPowerTrim(); break;
        case 16: *reinterpret_cast< float*>(_v) = _t->getCruiseControlPowerDelayComp(); break;
        case 17: *reinterpret_cast< float*>(_v) = _t->getScaleToAirspeed(); break;
        case 18: *reinterpret_cast< float*>(_v) = _t->getScaleToAirspeedLimits_Min(); break;
        case 19: *reinterpret_cast< float*>(_v) = _t->getScaleToAirspeedLimits_Max(); break;
        case 20: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeMap_0(); break;
        case 21: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeMap_1(); break;
        case 22: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeMap_2(); break;
        case 23: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeMap_3(); break;
        case 24: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeMap_4(); break;
        case 25: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeMap_5(); break;
        case 26: *reinterpret_cast< qint8*>(_v) = _t->getVbarGyroSuppress(); break;
        case 27: *reinterpret_cast< quint8*>(_v) = _t->getVbarPiroComp(); break;
        case 28: *reinterpret_cast< quint8*>(_v) = _t->getVbarMaxAngle(); break;
        case 29: *reinterpret_cast< quint8*>(_v) = _t->getDerivativeCutoff(); break;
        case 30: *reinterpret_cast< quint8*>(_v) = _t->getMaxAxisLock(); break;
        case 31: *reinterpret_cast< quint8*>(_v) = _t->getMaxAxisLockRate(); break;
        case 32: *reinterpret_cast< quint8*>(_v) = _t->getMaxWeakLevelingRate(); break;
        case 33: *reinterpret_cast< quint8*>(_v) = _t->getRattitudeModeTransition(); break;
        case 34: *reinterpret_cast< qint8*>(_v) = _t->getCruiseControlMinThrust(); break;
        case 35: *reinterpret_cast< quint8*>(_v) = _t->getCruiseControlMaxThrust(); break;
        case 36: *reinterpret_cast< quint8*>(_v) = _t->getCruiseControlMaxAngle(); break;
        case 37: *reinterpret_cast< quint8*>(_v) = _t->getCruiseControlFlightModeSwitchPosEnable_0(); break;
        case 38: *reinterpret_cast< quint8*>(_v) = _t->getCruiseControlFlightModeSwitchPosEnable_1(); break;
        case 39: *reinterpret_cast< quint8*>(_v) = _t->getCruiseControlFlightModeSwitchPosEnable_2(); break;
        case 40: *reinterpret_cast< quint8*>(_v) = _t->getCruiseControlFlightModeSwitchPosEnable_3(); break;
        case 41: *reinterpret_cast< quint8*>(_v) = _t->getCruiseControlFlightModeSwitchPosEnable_4(); break;
        case 42: *reinterpret_cast< quint8*>(_v) = _t->getCruiseControlFlightModeSwitchPosEnable_5(); break;
        case 43: *reinterpret_cast< quint8*>(_v) = _t->getCruiseControlInvertedThrustReversing(); break;
        case 44: *reinterpret_cast< quint8*>(_v) = _t->getCruiseControlInvertedPowerOutput(); break;
        case 45: *reinterpret_cast< quint8*>(_v) = _t->getLowThrottleZeroIntegral(); break;
        case 46: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeAssistMap_0(); break;
        case 47: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeAssistMap_1(); break;
        case 48: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeAssistMap_2(); break;
        case 49: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeAssistMap_3(); break;
        case 50: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeAssistMap_4(); break;
        case 51: *reinterpret_cast< quint8*>(_v) = _t->getFlightModeAssistMap_5(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<StabilizationSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setVbarSensitivity_Roll(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setVbarSensitivity_Pitch(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setVbarSensitivity_Yaw(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setVbarRollPI_Kp(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setVbarRollPI_Ki(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setVbarPitchPI_Kp(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setVbarPitchPI_Ki(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setVbarYawPI_Kp(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setVbarYawPI_Ki(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setVbarTau(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setGyroTau(*reinterpret_cast< float*>(_v)); break;
        case 11: _t->setDerivativeGamma(*reinterpret_cast< float*>(_v)); break;
        case 12: _t->setAxisLockKp(*reinterpret_cast< float*>(_v)); break;
        case 13: _t->setWeakLevelingKp(*reinterpret_cast< float*>(_v)); break;
        case 14: _t->setCruiseControlMaxPowerFactor(*reinterpret_cast< float*>(_v)); break;
        case 15: _t->setCruiseControlPowerTrim(*reinterpret_cast< float*>(_v)); break;
        case 16: _t->setCruiseControlPowerDelayComp(*reinterpret_cast< float*>(_v)); break;
        case 17: _t->setScaleToAirspeed(*reinterpret_cast< float*>(_v)); break;
        case 18: _t->setScaleToAirspeedLimits_Min(*reinterpret_cast< float*>(_v)); break;
        case 19: _t->setScaleToAirspeedLimits_Max(*reinterpret_cast< float*>(_v)); break;
        case 20: _t->setFlightModeMap_0(*reinterpret_cast< quint8*>(_v)); break;
        case 21: _t->setFlightModeMap_1(*reinterpret_cast< quint8*>(_v)); break;
        case 22: _t->setFlightModeMap_2(*reinterpret_cast< quint8*>(_v)); break;
        case 23: _t->setFlightModeMap_3(*reinterpret_cast< quint8*>(_v)); break;
        case 24: _t->setFlightModeMap_4(*reinterpret_cast< quint8*>(_v)); break;
        case 25: _t->setFlightModeMap_5(*reinterpret_cast< quint8*>(_v)); break;
        case 26: _t->setVbarGyroSuppress(*reinterpret_cast< qint8*>(_v)); break;
        case 27: _t->setVbarPiroComp(*reinterpret_cast< quint8*>(_v)); break;
        case 28: _t->setVbarMaxAngle(*reinterpret_cast< quint8*>(_v)); break;
        case 29: _t->setDerivativeCutoff(*reinterpret_cast< quint8*>(_v)); break;
        case 30: _t->setMaxAxisLock(*reinterpret_cast< quint8*>(_v)); break;
        case 31: _t->setMaxAxisLockRate(*reinterpret_cast< quint8*>(_v)); break;
        case 32: _t->setMaxWeakLevelingRate(*reinterpret_cast< quint8*>(_v)); break;
        case 33: _t->setRattitudeModeTransition(*reinterpret_cast< quint8*>(_v)); break;
        case 34: _t->setCruiseControlMinThrust(*reinterpret_cast< qint8*>(_v)); break;
        case 35: _t->setCruiseControlMaxThrust(*reinterpret_cast< quint8*>(_v)); break;
        case 36: _t->setCruiseControlMaxAngle(*reinterpret_cast< quint8*>(_v)); break;
        case 37: _t->setCruiseControlFlightModeSwitchPosEnable_0(*reinterpret_cast< quint8*>(_v)); break;
        case 38: _t->setCruiseControlFlightModeSwitchPosEnable_1(*reinterpret_cast< quint8*>(_v)); break;
        case 39: _t->setCruiseControlFlightModeSwitchPosEnable_2(*reinterpret_cast< quint8*>(_v)); break;
        case 40: _t->setCruiseControlFlightModeSwitchPosEnable_3(*reinterpret_cast< quint8*>(_v)); break;
        case 41: _t->setCruiseControlFlightModeSwitchPosEnable_4(*reinterpret_cast< quint8*>(_v)); break;
        case 42: _t->setCruiseControlFlightModeSwitchPosEnable_5(*reinterpret_cast< quint8*>(_v)); break;
        case 43: _t->setCruiseControlInvertedThrustReversing(*reinterpret_cast< quint8*>(_v)); break;
        case 44: _t->setCruiseControlInvertedPowerOutput(*reinterpret_cast< quint8*>(_v)); break;
        case 45: _t->setLowThrottleZeroIntegral(*reinterpret_cast< quint8*>(_v)); break;
        case 46: _t->setFlightModeAssistMap_0(*reinterpret_cast< quint8*>(_v)); break;
        case 47: _t->setFlightModeAssistMap_1(*reinterpret_cast< quint8*>(_v)); break;
        case 48: _t->setFlightModeAssistMap_2(*reinterpret_cast< quint8*>(_v)); break;
        case 49: _t->setFlightModeAssistMap_3(*reinterpret_cast< quint8*>(_v)); break;
        case 50: _t->setFlightModeAssistMap_4(*reinterpret_cast< quint8*>(_v)); break;
        case 51: _t->setFlightModeAssistMap_5(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject StabilizationSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_StabilizationSettings.data,
    qt_meta_data_StabilizationSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StabilizationSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StabilizationSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StabilizationSettings.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int StabilizationSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 181)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 181;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 181)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 181;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 52;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 52;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 52;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 52;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 52;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 52;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void StabilizationSettings::VbarSensitivityChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StabilizationSettings::VbarSensitivity_RollChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StabilizationSettings::VbarSensitivity_PitchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void StabilizationSettings::VbarSensitivity_YawChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void StabilizationSettings::VbarRollPIChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void StabilizationSettings::VbarRollPI_KpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void StabilizationSettings::VbarRollPI_KiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void StabilizationSettings::VbarPitchPIChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void StabilizationSettings::VbarPitchPI_KpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void StabilizationSettings::VbarPitchPI_KiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void StabilizationSettings::VbarYawPIChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void StabilizationSettings::VbarYawPI_KpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void StabilizationSettings::VbarYawPI_KiChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void StabilizationSettings::VbarTauChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void StabilizationSettings::GyroTauChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void StabilizationSettings::DerivativeGammaChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void StabilizationSettings::AxisLockKpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void StabilizationSettings::WeakLevelingKpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void StabilizationSettings::CruiseControlMaxPowerFactorChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void StabilizationSettings::CruiseControlPowerTrimChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void StabilizationSettings::CruiseControlPowerDelayCompChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void StabilizationSettings::ScaleToAirspeedChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void StabilizationSettings::ScaleToAirspeedLimitsChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void StabilizationSettings::ScaleToAirspeedLimits_MinChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void StabilizationSettings::ScaleToAirspeedLimits_MaxChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void StabilizationSettings::FlightModeMapChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void StabilizationSettings::FlightModeMap_0Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void StabilizationSettings::FlightModeMap_1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void StabilizationSettings::FlightModeMap_2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void StabilizationSettings::FlightModeMap_3Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void StabilizationSettings::FlightModeMap_4Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void StabilizationSettings::FlightModeMap_5Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void StabilizationSettings::VbarGyroSuppressChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void StabilizationSettings::VbarPiroCompChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void StabilizationSettings::VbarMaxAngleChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void StabilizationSettings::DerivativeCutoffChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 35, _a);
}

// SIGNAL 36
void StabilizationSettings::MaxAxisLockChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 36, _a);
}

// SIGNAL 37
void StabilizationSettings::MaxAxisLockRateChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 37, _a);
}

// SIGNAL 38
void StabilizationSettings::MaxWeakLevelingRateChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 38, _a);
}

// SIGNAL 39
void StabilizationSettings::RattitudeModeTransitionChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 39, _a);
}

// SIGNAL 40
void StabilizationSettings::CruiseControlMinThrustChanged(qint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 40, _a);
}

// SIGNAL 41
void StabilizationSettings::CruiseControlMaxThrustChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 41, _a);
}

// SIGNAL 42
void StabilizationSettings::CruiseControlMaxAngleChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 42, _a);
}

// SIGNAL 43
void StabilizationSettings::CruiseControlFlightModeSwitchPosEnableChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 43, _a);
}

// SIGNAL 44
void StabilizationSettings::CruiseControlFlightModeSwitchPosEnable_0Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 44, _a);
}

// SIGNAL 45
void StabilizationSettings::CruiseControlFlightModeSwitchPosEnable_1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 45, _a);
}

// SIGNAL 46
void StabilizationSettings::CruiseControlFlightModeSwitchPosEnable_2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 46, _a);
}

// SIGNAL 47
void StabilizationSettings::CruiseControlFlightModeSwitchPosEnable_3Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 47, _a);
}

// SIGNAL 48
void StabilizationSettings::CruiseControlFlightModeSwitchPosEnable_4Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 48, _a);
}

// SIGNAL 49
void StabilizationSettings::CruiseControlFlightModeSwitchPosEnable_5Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 49, _a);
}

// SIGNAL 50
void StabilizationSettings::CruiseControlInvertedThrustReversingChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 50, _a);
}

// SIGNAL 51
void StabilizationSettings::CruiseControlInvertedPowerOutputChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 51, _a);
}

// SIGNAL 52
void StabilizationSettings::LowThrottleZeroIntegralChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 52, _a);
}

// SIGNAL 53
void StabilizationSettings::FlightModeAssistMapChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 53, _a);
}

// SIGNAL 54
void StabilizationSettings::FlightModeAssistMap_0Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 54, _a);
}

// SIGNAL 55
void StabilizationSettings::FlightModeAssistMap_1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 55, _a);
}

// SIGNAL 56
void StabilizationSettings::FlightModeAssistMap_2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 56, _a);
}

// SIGNAL 57
void StabilizationSettings::FlightModeAssistMap_3Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 57, _a);
}

// SIGNAL 58
void StabilizationSettings::FlightModeAssistMap_4Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 58, _a);
}

// SIGNAL 59
void StabilizationSettings::FlightModeAssistMap_5Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 59, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
