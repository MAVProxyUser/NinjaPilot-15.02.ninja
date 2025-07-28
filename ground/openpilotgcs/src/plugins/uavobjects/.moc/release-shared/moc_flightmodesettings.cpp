/****************************************************************************
** Meta object code from reading C++ file 'flightmodesettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../uavobject-synthetics/gcs/flightmodesettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flightmodesettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FlightModeSettings_t {
    QByteArrayData data[193];
    char stringdata0[5379];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlightModeSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlightModeSettings_t qt_meta_stringdata_FlightModeSettings = {
    {
QT_MOC_LITERAL(0, 0, 18), // "FlightModeSettings"
QT_MOC_LITERAL(1, 19, 33), // "ReturnToBaseAltitudeOffsetCha..."
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 5), // "value"
QT_MOC_LITERAL(4, 60, 22), // "LandingVelocityChanged"
QT_MOC_LITERAL(5, 83, 25), // "PositionHoldOffsetChanged"
QT_MOC_LITERAL(6, 109, 5), // "index"
QT_MOC_LITERAL(7, 115, 36), // "PositionHoldOffset_Horizontal..."
QT_MOC_LITERAL(8, 152, 34), // "PositionHoldOffset_VerticalCh..."
QT_MOC_LITERAL(9, 187, 31), // "VarioControlLowPassAlphaChanged"
QT_MOC_LITERAL(10, 219, 19), // "ArmedTimeoutChanged"
QT_MOC_LITERAL(11, 239, 25), // "ArmingSequenceTimeChanged"
QT_MOC_LITERAL(12, 265, 28), // "DisarmingSequenceTimeChanged"
QT_MOC_LITERAL(13, 294, 13), // "ArmingChanged"
QT_MOC_LITERAL(14, 308, 29), // "Stabilization1SettingsChanged"
QT_MOC_LITERAL(15, 338, 34), // "Stabilization1Settings_RollCh..."
QT_MOC_LITERAL(16, 373, 35), // "Stabilization1Settings_PitchC..."
QT_MOC_LITERAL(17, 409, 33), // "Stabilization1Settings_YawCha..."
QT_MOC_LITERAL(18, 443, 36), // "Stabilization1Settings_Thrust..."
QT_MOC_LITERAL(19, 480, 29), // "Stabilization2SettingsChanged"
QT_MOC_LITERAL(20, 510, 34), // "Stabilization2Settings_RollCh..."
QT_MOC_LITERAL(21, 545, 35), // "Stabilization2Settings_PitchC..."
QT_MOC_LITERAL(22, 581, 33), // "Stabilization2Settings_YawCha..."
QT_MOC_LITERAL(23, 615, 36), // "Stabilization2Settings_Thrust..."
QT_MOC_LITERAL(24, 652, 29), // "Stabilization3SettingsChanged"
QT_MOC_LITERAL(25, 682, 34), // "Stabilization3Settings_RollCh..."
QT_MOC_LITERAL(26, 717, 35), // "Stabilization3Settings_PitchC..."
QT_MOC_LITERAL(27, 753, 33), // "Stabilization3Settings_YawCha..."
QT_MOC_LITERAL(28, 787, 36), // "Stabilization3Settings_Thrust..."
QT_MOC_LITERAL(29, 824, 29), // "Stabilization4SettingsChanged"
QT_MOC_LITERAL(30, 854, 34), // "Stabilization4Settings_RollCh..."
QT_MOC_LITERAL(31, 889, 35), // "Stabilization4Settings_PitchC..."
QT_MOC_LITERAL(32, 925, 33), // "Stabilization4Settings_YawCha..."
QT_MOC_LITERAL(33, 959, 36), // "Stabilization4Settings_Thrust..."
QT_MOC_LITERAL(34, 996, 29), // "Stabilization5SettingsChanged"
QT_MOC_LITERAL(35, 1026, 34), // "Stabilization5Settings_RollCh..."
QT_MOC_LITERAL(36, 1061, 35), // "Stabilization5Settings_PitchC..."
QT_MOC_LITERAL(37, 1097, 33), // "Stabilization5Settings_YawCha..."
QT_MOC_LITERAL(38, 1131, 36), // "Stabilization5Settings_Thrust..."
QT_MOC_LITERAL(39, 1168, 29), // "Stabilization6SettingsChanged"
QT_MOC_LITERAL(40, 1198, 34), // "Stabilization6Settings_RollCh..."
QT_MOC_LITERAL(41, 1233, 35), // "Stabilization6Settings_PitchC..."
QT_MOC_LITERAL(42, 1269, 33), // "Stabilization6Settings_YawCha..."
QT_MOC_LITERAL(43, 1303, 36), // "Stabilization6Settings_Thrust..."
QT_MOC_LITERAL(44, 1340, 25), // "FlightModePositionChanged"
QT_MOC_LITERAL(45, 1366, 27), // "FlightModePosition_0Changed"
QT_MOC_LITERAL(46, 1394, 27), // "FlightModePosition_1Changed"
QT_MOC_LITERAL(47, 1422, 27), // "FlightModePosition_2Changed"
QT_MOC_LITERAL(48, 1450, 27), // "FlightModePosition_3Changed"
QT_MOC_LITERAL(49, 1478, 27), // "FlightModePosition_4Changed"
QT_MOC_LITERAL(50, 1506, 27), // "FlightModePosition_5Changed"
QT_MOC_LITERAL(51, 1534, 26), // "DisableSanityChecksChanged"
QT_MOC_LITERAL(52, 1561, 30), // "ReturnToBaseNextCommandChanged"
QT_MOC_LITERAL(53, 1592, 29), // "setReturnToBaseAltitudeOffset"
QT_MOC_LITERAL(54, 1622, 18), // "setLandingVelocity"
QT_MOC_LITERAL(55, 1641, 21), // "setPositionHoldOffset"
QT_MOC_LITERAL(56, 1663, 32), // "setPositionHoldOffset_Horizontal"
QT_MOC_LITERAL(57, 1696, 30), // "setPositionHoldOffset_Vertical"
QT_MOC_LITERAL(58, 1727, 27), // "setVarioControlLowPassAlpha"
QT_MOC_LITERAL(59, 1755, 15), // "setArmedTimeout"
QT_MOC_LITERAL(60, 1771, 21), // "setArmingSequenceTime"
QT_MOC_LITERAL(61, 1793, 24), // "setDisarmingSequenceTime"
QT_MOC_LITERAL(62, 1818, 9), // "setArming"
QT_MOC_LITERAL(63, 1828, 25), // "setStabilization1Settings"
QT_MOC_LITERAL(64, 1854, 30), // "setStabilization1Settings_Roll"
QT_MOC_LITERAL(65, 1885, 31), // "setStabilization1Settings_Pitch"
QT_MOC_LITERAL(66, 1917, 29), // "setStabilization1Settings_Yaw"
QT_MOC_LITERAL(67, 1947, 32), // "setStabilization1Settings_Thrust"
QT_MOC_LITERAL(68, 1980, 25), // "setStabilization2Settings"
QT_MOC_LITERAL(69, 2006, 30), // "setStabilization2Settings_Roll"
QT_MOC_LITERAL(70, 2037, 31), // "setStabilization2Settings_Pitch"
QT_MOC_LITERAL(71, 2069, 29), // "setStabilization2Settings_Yaw"
QT_MOC_LITERAL(72, 2099, 32), // "setStabilization2Settings_Thrust"
QT_MOC_LITERAL(73, 2132, 25), // "setStabilization3Settings"
QT_MOC_LITERAL(74, 2158, 30), // "setStabilization3Settings_Roll"
QT_MOC_LITERAL(75, 2189, 31), // "setStabilization3Settings_Pitch"
QT_MOC_LITERAL(76, 2221, 29), // "setStabilization3Settings_Yaw"
QT_MOC_LITERAL(77, 2251, 32), // "setStabilization3Settings_Thrust"
QT_MOC_LITERAL(78, 2284, 25), // "setStabilization4Settings"
QT_MOC_LITERAL(79, 2310, 30), // "setStabilization4Settings_Roll"
QT_MOC_LITERAL(80, 2341, 31), // "setStabilization4Settings_Pitch"
QT_MOC_LITERAL(81, 2373, 29), // "setStabilization4Settings_Yaw"
QT_MOC_LITERAL(82, 2403, 32), // "setStabilization4Settings_Thrust"
QT_MOC_LITERAL(83, 2436, 25), // "setStabilization5Settings"
QT_MOC_LITERAL(84, 2462, 30), // "setStabilization5Settings_Roll"
QT_MOC_LITERAL(85, 2493, 31), // "setStabilization5Settings_Pitch"
QT_MOC_LITERAL(86, 2525, 29), // "setStabilization5Settings_Yaw"
QT_MOC_LITERAL(87, 2555, 32), // "setStabilization5Settings_Thrust"
QT_MOC_LITERAL(88, 2588, 25), // "setStabilization6Settings"
QT_MOC_LITERAL(89, 2614, 30), // "setStabilization6Settings_Roll"
QT_MOC_LITERAL(90, 2645, 31), // "setStabilization6Settings_Pitch"
QT_MOC_LITERAL(91, 2677, 29), // "setStabilization6Settings_Yaw"
QT_MOC_LITERAL(92, 2707, 32), // "setStabilization6Settings_Thrust"
QT_MOC_LITERAL(93, 2740, 21), // "setFlightModePosition"
QT_MOC_LITERAL(94, 2762, 23), // "setFlightModePosition_0"
QT_MOC_LITERAL(95, 2786, 23), // "setFlightModePosition_1"
QT_MOC_LITERAL(96, 2810, 23), // "setFlightModePosition_2"
QT_MOC_LITERAL(97, 2834, 23), // "setFlightModePosition_3"
QT_MOC_LITERAL(98, 2858, 23), // "setFlightModePosition_4"
QT_MOC_LITERAL(99, 2882, 23), // "setFlightModePosition_5"
QT_MOC_LITERAL(100, 2906, 22), // "setDisableSanityChecks"
QT_MOC_LITERAL(101, 2929, 26), // "setReturnToBaseNextCommand"
QT_MOC_LITERAL(102, 2956, 17), // "emitNotifications"
QT_MOC_LITERAL(103, 2974, 29), // "getReturnToBaseAltitudeOffset"
QT_MOC_LITERAL(104, 3004, 18), // "getLandingVelocity"
QT_MOC_LITERAL(105, 3023, 21), // "getPositionHoldOffset"
QT_MOC_LITERAL(106, 3045, 32), // "getPositionHoldOffset_Horizontal"
QT_MOC_LITERAL(107, 3078, 30), // "getPositionHoldOffset_Vertical"
QT_MOC_LITERAL(108, 3109, 27), // "getVarioControlLowPassAlpha"
QT_MOC_LITERAL(109, 3137, 15), // "getArmedTimeout"
QT_MOC_LITERAL(110, 3153, 21), // "getArmingSequenceTime"
QT_MOC_LITERAL(111, 3175, 24), // "getDisarmingSequenceTime"
QT_MOC_LITERAL(112, 3200, 9), // "getArming"
QT_MOC_LITERAL(113, 3210, 25), // "getStabilization1Settings"
QT_MOC_LITERAL(114, 3236, 30), // "getStabilization1Settings_Roll"
QT_MOC_LITERAL(115, 3267, 31), // "getStabilization1Settings_Pitch"
QT_MOC_LITERAL(116, 3299, 29), // "getStabilization1Settings_Yaw"
QT_MOC_LITERAL(117, 3329, 32), // "getStabilization1Settings_Thrust"
QT_MOC_LITERAL(118, 3362, 25), // "getStabilization2Settings"
QT_MOC_LITERAL(119, 3388, 30), // "getStabilization2Settings_Roll"
QT_MOC_LITERAL(120, 3419, 31), // "getStabilization2Settings_Pitch"
QT_MOC_LITERAL(121, 3451, 29), // "getStabilization2Settings_Yaw"
QT_MOC_LITERAL(122, 3481, 32), // "getStabilization2Settings_Thrust"
QT_MOC_LITERAL(123, 3514, 25), // "getStabilization3Settings"
QT_MOC_LITERAL(124, 3540, 30), // "getStabilization3Settings_Roll"
QT_MOC_LITERAL(125, 3571, 31), // "getStabilization3Settings_Pitch"
QT_MOC_LITERAL(126, 3603, 29), // "getStabilization3Settings_Yaw"
QT_MOC_LITERAL(127, 3633, 32), // "getStabilization3Settings_Thrust"
QT_MOC_LITERAL(128, 3666, 25), // "getStabilization4Settings"
QT_MOC_LITERAL(129, 3692, 30), // "getStabilization4Settings_Roll"
QT_MOC_LITERAL(130, 3723, 31), // "getStabilization4Settings_Pitch"
QT_MOC_LITERAL(131, 3755, 29), // "getStabilization4Settings_Yaw"
QT_MOC_LITERAL(132, 3785, 32), // "getStabilization4Settings_Thrust"
QT_MOC_LITERAL(133, 3818, 25), // "getStabilization5Settings"
QT_MOC_LITERAL(134, 3844, 30), // "getStabilization5Settings_Roll"
QT_MOC_LITERAL(135, 3875, 31), // "getStabilization5Settings_Pitch"
QT_MOC_LITERAL(136, 3907, 29), // "getStabilization5Settings_Yaw"
QT_MOC_LITERAL(137, 3937, 32), // "getStabilization5Settings_Thrust"
QT_MOC_LITERAL(138, 3970, 25), // "getStabilization6Settings"
QT_MOC_LITERAL(139, 3996, 30), // "getStabilization6Settings_Roll"
QT_MOC_LITERAL(140, 4027, 31), // "getStabilization6Settings_Pitch"
QT_MOC_LITERAL(141, 4059, 29), // "getStabilization6Settings_Yaw"
QT_MOC_LITERAL(142, 4089, 32), // "getStabilization6Settings_Thrust"
QT_MOC_LITERAL(143, 4122, 21), // "getFlightModePosition"
QT_MOC_LITERAL(144, 4144, 23), // "getFlightModePosition_0"
QT_MOC_LITERAL(145, 4168, 23), // "getFlightModePosition_1"
QT_MOC_LITERAL(146, 4192, 23), // "getFlightModePosition_2"
QT_MOC_LITERAL(147, 4216, 23), // "getFlightModePosition_3"
QT_MOC_LITERAL(148, 4240, 23), // "getFlightModePosition_4"
QT_MOC_LITERAL(149, 4264, 23), // "getFlightModePosition_5"
QT_MOC_LITERAL(150, 4288, 22), // "getDisableSanityChecks"
QT_MOC_LITERAL(151, 4311, 26), // "getReturnToBaseNextCommand"
QT_MOC_LITERAL(152, 4338, 26), // "ReturnToBaseAltitudeOffset"
QT_MOC_LITERAL(153, 4365, 15), // "LandingVelocity"
QT_MOC_LITERAL(154, 4381, 29), // "PositionHoldOffset_Horizontal"
QT_MOC_LITERAL(155, 4411, 27), // "PositionHoldOffset_Vertical"
QT_MOC_LITERAL(156, 4439, 24), // "VarioControlLowPassAlpha"
QT_MOC_LITERAL(157, 4464, 12), // "ArmedTimeout"
QT_MOC_LITERAL(158, 4477, 18), // "ArmingSequenceTime"
QT_MOC_LITERAL(159, 4496, 21), // "DisarmingSequenceTime"
QT_MOC_LITERAL(160, 4518, 6), // "Arming"
QT_MOC_LITERAL(161, 4525, 27), // "Stabilization1Settings_Roll"
QT_MOC_LITERAL(162, 4553, 28), // "Stabilization1Settings_Pitch"
QT_MOC_LITERAL(163, 4582, 26), // "Stabilization1Settings_Yaw"
QT_MOC_LITERAL(164, 4609, 29), // "Stabilization1Settings_Thrust"
QT_MOC_LITERAL(165, 4639, 27), // "Stabilization2Settings_Roll"
QT_MOC_LITERAL(166, 4667, 28), // "Stabilization2Settings_Pitch"
QT_MOC_LITERAL(167, 4696, 26), // "Stabilization2Settings_Yaw"
QT_MOC_LITERAL(168, 4723, 29), // "Stabilization2Settings_Thrust"
QT_MOC_LITERAL(169, 4753, 27), // "Stabilization3Settings_Roll"
QT_MOC_LITERAL(170, 4781, 28), // "Stabilization3Settings_Pitch"
QT_MOC_LITERAL(171, 4810, 26), // "Stabilization3Settings_Yaw"
QT_MOC_LITERAL(172, 4837, 29), // "Stabilization3Settings_Thrust"
QT_MOC_LITERAL(173, 4867, 27), // "Stabilization4Settings_Roll"
QT_MOC_LITERAL(174, 4895, 28), // "Stabilization4Settings_Pitch"
QT_MOC_LITERAL(175, 4924, 26), // "Stabilization4Settings_Yaw"
QT_MOC_LITERAL(176, 4951, 29), // "Stabilization4Settings_Thrust"
QT_MOC_LITERAL(177, 4981, 27), // "Stabilization5Settings_Roll"
QT_MOC_LITERAL(178, 5009, 28), // "Stabilization5Settings_Pitch"
QT_MOC_LITERAL(179, 5038, 26), // "Stabilization5Settings_Yaw"
QT_MOC_LITERAL(180, 5065, 29), // "Stabilization5Settings_Thrust"
QT_MOC_LITERAL(181, 5095, 27), // "Stabilization6Settings_Roll"
QT_MOC_LITERAL(182, 5123, 28), // "Stabilization6Settings_Pitch"
QT_MOC_LITERAL(183, 5152, 26), // "Stabilization6Settings_Yaw"
QT_MOC_LITERAL(184, 5179, 29), // "Stabilization6Settings_Thrust"
QT_MOC_LITERAL(185, 5209, 20), // "FlightModePosition_0"
QT_MOC_LITERAL(186, 5230, 20), // "FlightModePosition_1"
QT_MOC_LITERAL(187, 5251, 20), // "FlightModePosition_2"
QT_MOC_LITERAL(188, 5272, 20), // "FlightModePosition_3"
QT_MOC_LITERAL(189, 5293, 20), // "FlightModePosition_4"
QT_MOC_LITERAL(190, 5314, 20), // "FlightModePosition_5"
QT_MOC_LITERAL(191, 5335, 19), // "DisableSanityChecks"
QT_MOC_LITERAL(192, 5355, 23) // "ReturnToBaseNextCommand"

    },
    "FlightModeSettings\0ReturnToBaseAltitudeOffsetChanged\0"
    "\0value\0LandingVelocityChanged\0"
    "PositionHoldOffsetChanged\0index\0"
    "PositionHoldOffset_HorizontalChanged\0"
    "PositionHoldOffset_VerticalChanged\0"
    "VarioControlLowPassAlphaChanged\0"
    "ArmedTimeoutChanged\0ArmingSequenceTimeChanged\0"
    "DisarmingSequenceTimeChanged\0ArmingChanged\0"
    "Stabilization1SettingsChanged\0"
    "Stabilization1Settings_RollChanged\0"
    "Stabilization1Settings_PitchChanged\0"
    "Stabilization1Settings_YawChanged\0"
    "Stabilization1Settings_ThrustChanged\0"
    "Stabilization2SettingsChanged\0"
    "Stabilization2Settings_RollChanged\0"
    "Stabilization2Settings_PitchChanged\0"
    "Stabilization2Settings_YawChanged\0"
    "Stabilization2Settings_ThrustChanged\0"
    "Stabilization3SettingsChanged\0"
    "Stabilization3Settings_RollChanged\0"
    "Stabilization3Settings_PitchChanged\0"
    "Stabilization3Settings_YawChanged\0"
    "Stabilization3Settings_ThrustChanged\0"
    "Stabilization4SettingsChanged\0"
    "Stabilization4Settings_RollChanged\0"
    "Stabilization4Settings_PitchChanged\0"
    "Stabilization4Settings_YawChanged\0"
    "Stabilization4Settings_ThrustChanged\0"
    "Stabilization5SettingsChanged\0"
    "Stabilization5Settings_RollChanged\0"
    "Stabilization5Settings_PitchChanged\0"
    "Stabilization5Settings_YawChanged\0"
    "Stabilization5Settings_ThrustChanged\0"
    "Stabilization6SettingsChanged\0"
    "Stabilization6Settings_RollChanged\0"
    "Stabilization6Settings_PitchChanged\0"
    "Stabilization6Settings_YawChanged\0"
    "Stabilization6Settings_ThrustChanged\0"
    "FlightModePositionChanged\0"
    "FlightModePosition_0Changed\0"
    "FlightModePosition_1Changed\0"
    "FlightModePosition_2Changed\0"
    "FlightModePosition_3Changed\0"
    "FlightModePosition_4Changed\0"
    "FlightModePosition_5Changed\0"
    "DisableSanityChecksChanged\0"
    "ReturnToBaseNextCommandChanged\0"
    "setReturnToBaseAltitudeOffset\0"
    "setLandingVelocity\0setPositionHoldOffset\0"
    "setPositionHoldOffset_Horizontal\0"
    "setPositionHoldOffset_Vertical\0"
    "setVarioControlLowPassAlpha\0setArmedTimeout\0"
    "setArmingSequenceTime\0setDisarmingSequenceTime\0"
    "setArming\0setStabilization1Settings\0"
    "setStabilization1Settings_Roll\0"
    "setStabilization1Settings_Pitch\0"
    "setStabilization1Settings_Yaw\0"
    "setStabilization1Settings_Thrust\0"
    "setStabilization2Settings\0"
    "setStabilization2Settings_Roll\0"
    "setStabilization2Settings_Pitch\0"
    "setStabilization2Settings_Yaw\0"
    "setStabilization2Settings_Thrust\0"
    "setStabilization3Settings\0"
    "setStabilization3Settings_Roll\0"
    "setStabilization3Settings_Pitch\0"
    "setStabilization3Settings_Yaw\0"
    "setStabilization3Settings_Thrust\0"
    "setStabilization4Settings\0"
    "setStabilization4Settings_Roll\0"
    "setStabilization4Settings_Pitch\0"
    "setStabilization4Settings_Yaw\0"
    "setStabilization4Settings_Thrust\0"
    "setStabilization5Settings\0"
    "setStabilization5Settings_Roll\0"
    "setStabilization5Settings_Pitch\0"
    "setStabilization5Settings_Yaw\0"
    "setStabilization5Settings_Thrust\0"
    "setStabilization6Settings\0"
    "setStabilization6Settings_Roll\0"
    "setStabilization6Settings_Pitch\0"
    "setStabilization6Settings_Yaw\0"
    "setStabilization6Settings_Thrust\0"
    "setFlightModePosition\0setFlightModePosition_0\0"
    "setFlightModePosition_1\0setFlightModePosition_2\0"
    "setFlightModePosition_3\0setFlightModePosition_4\0"
    "setFlightModePosition_5\0setDisableSanityChecks\0"
    "setReturnToBaseNextCommand\0emitNotifications\0"
    "getReturnToBaseAltitudeOffset\0"
    "getLandingVelocity\0getPositionHoldOffset\0"
    "getPositionHoldOffset_Horizontal\0"
    "getPositionHoldOffset_Vertical\0"
    "getVarioControlLowPassAlpha\0getArmedTimeout\0"
    "getArmingSequenceTime\0getDisarmingSequenceTime\0"
    "getArming\0getStabilization1Settings\0"
    "getStabilization1Settings_Roll\0"
    "getStabilization1Settings_Pitch\0"
    "getStabilization1Settings_Yaw\0"
    "getStabilization1Settings_Thrust\0"
    "getStabilization2Settings\0"
    "getStabilization2Settings_Roll\0"
    "getStabilization2Settings_Pitch\0"
    "getStabilization2Settings_Yaw\0"
    "getStabilization2Settings_Thrust\0"
    "getStabilization3Settings\0"
    "getStabilization3Settings_Roll\0"
    "getStabilization3Settings_Pitch\0"
    "getStabilization3Settings_Yaw\0"
    "getStabilization3Settings_Thrust\0"
    "getStabilization4Settings\0"
    "getStabilization4Settings_Roll\0"
    "getStabilization4Settings_Pitch\0"
    "getStabilization4Settings_Yaw\0"
    "getStabilization4Settings_Thrust\0"
    "getStabilization5Settings\0"
    "getStabilization5Settings_Roll\0"
    "getStabilization5Settings_Pitch\0"
    "getStabilization5Settings_Yaw\0"
    "getStabilization5Settings_Thrust\0"
    "getStabilization6Settings\0"
    "getStabilization6Settings_Roll\0"
    "getStabilization6Settings_Pitch\0"
    "getStabilization6Settings_Yaw\0"
    "getStabilization6Settings_Thrust\0"
    "getFlightModePosition\0getFlightModePosition_0\0"
    "getFlightModePosition_1\0getFlightModePosition_2\0"
    "getFlightModePosition_3\0getFlightModePosition_4\0"
    "getFlightModePosition_5\0getDisableSanityChecks\0"
    "getReturnToBaseNextCommand\0"
    "ReturnToBaseAltitudeOffset\0LandingVelocity\0"
    "PositionHoldOffset_Horizontal\0"
    "PositionHoldOffset_Vertical\0"
    "VarioControlLowPassAlpha\0ArmedTimeout\0"
    "ArmingSequenceTime\0DisarmingSequenceTime\0"
    "Arming\0Stabilization1Settings_Roll\0"
    "Stabilization1Settings_Pitch\0"
    "Stabilization1Settings_Yaw\0"
    "Stabilization1Settings_Thrust\0"
    "Stabilization2Settings_Roll\0"
    "Stabilization2Settings_Pitch\0"
    "Stabilization2Settings_Yaw\0"
    "Stabilization2Settings_Thrust\0"
    "Stabilization3Settings_Roll\0"
    "Stabilization3Settings_Pitch\0"
    "Stabilization3Settings_Yaw\0"
    "Stabilization3Settings_Thrust\0"
    "Stabilization4Settings_Roll\0"
    "Stabilization4Settings_Pitch\0"
    "Stabilization4Settings_Yaw\0"
    "Stabilization4Settings_Thrust\0"
    "Stabilization5Settings_Roll\0"
    "Stabilization5Settings_Pitch\0"
    "Stabilization5Settings_Yaw\0"
    "Stabilization5Settings_Thrust\0"
    "Stabilization6Settings_Roll\0"
    "Stabilization6Settings_Pitch\0"
    "Stabilization6Settings_Yaw\0"
    "Stabilization6Settings_Thrust\0"
    "FlightModePosition_0\0FlightModePosition_1\0"
    "FlightModePosition_2\0FlightModePosition_3\0"
    "FlightModePosition_4\0FlightModePosition_5\0"
    "DisableSanityChecks\0ReturnToBaseNextCommand"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlightModeSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     148,   14, // methods
      41, 1146, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      49,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  754,    2, 0x06 /* Public */,
       4,    1,  757,    2, 0x06 /* Public */,
       5,    2,  760,    2, 0x06 /* Public */,
       7,    1,  765,    2, 0x06 /* Public */,
       8,    1,  768,    2, 0x06 /* Public */,
       9,    1,  771,    2, 0x06 /* Public */,
      10,    1,  774,    2, 0x06 /* Public */,
      11,    1,  777,    2, 0x06 /* Public */,
      12,    1,  780,    2, 0x06 /* Public */,
      13,    1,  783,    2, 0x06 /* Public */,
      14,    2,  786,    2, 0x06 /* Public */,
      15,    1,  791,    2, 0x06 /* Public */,
      16,    1,  794,    2, 0x06 /* Public */,
      17,    1,  797,    2, 0x06 /* Public */,
      18,    1,  800,    2, 0x06 /* Public */,
      19,    2,  803,    2, 0x06 /* Public */,
      20,    1,  808,    2, 0x06 /* Public */,
      21,    1,  811,    2, 0x06 /* Public */,
      22,    1,  814,    2, 0x06 /* Public */,
      23,    1,  817,    2, 0x06 /* Public */,
      24,    2,  820,    2, 0x06 /* Public */,
      25,    1,  825,    2, 0x06 /* Public */,
      26,    1,  828,    2, 0x06 /* Public */,
      27,    1,  831,    2, 0x06 /* Public */,
      28,    1,  834,    2, 0x06 /* Public */,
      29,    2,  837,    2, 0x06 /* Public */,
      30,    1,  842,    2, 0x06 /* Public */,
      31,    1,  845,    2, 0x06 /* Public */,
      32,    1,  848,    2, 0x06 /* Public */,
      33,    1,  851,    2, 0x06 /* Public */,
      34,    2,  854,    2, 0x06 /* Public */,
      35,    1,  859,    2, 0x06 /* Public */,
      36,    1,  862,    2, 0x06 /* Public */,
      37,    1,  865,    2, 0x06 /* Public */,
      38,    1,  868,    2, 0x06 /* Public */,
      39,    2,  871,    2, 0x06 /* Public */,
      40,    1,  876,    2, 0x06 /* Public */,
      41,    1,  879,    2, 0x06 /* Public */,
      42,    1,  882,    2, 0x06 /* Public */,
      43,    1,  885,    2, 0x06 /* Public */,
      44,    2,  888,    2, 0x06 /* Public */,
      45,    1,  893,    2, 0x06 /* Public */,
      46,    1,  896,    2, 0x06 /* Public */,
      47,    1,  899,    2, 0x06 /* Public */,
      48,    1,  902,    2, 0x06 /* Public */,
      49,    1,  905,    2, 0x06 /* Public */,
      50,    1,  908,    2, 0x06 /* Public */,
      51,    1,  911,    2, 0x06 /* Public */,
      52,    1,  914,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      53,    1,  917,    2, 0x0a /* Public */,
      54,    1,  920,    2, 0x0a /* Public */,
      55,    2,  923,    2, 0x0a /* Public */,
      56,    1,  928,    2, 0x0a /* Public */,
      57,    1,  931,    2, 0x0a /* Public */,
      58,    1,  934,    2, 0x0a /* Public */,
      59,    1,  937,    2, 0x0a /* Public */,
      60,    1,  940,    2, 0x0a /* Public */,
      61,    1,  943,    2, 0x0a /* Public */,
      62,    1,  946,    2, 0x0a /* Public */,
      63,    2,  949,    2, 0x0a /* Public */,
      64,    1,  954,    2, 0x0a /* Public */,
      65,    1,  957,    2, 0x0a /* Public */,
      66,    1,  960,    2, 0x0a /* Public */,
      67,    1,  963,    2, 0x0a /* Public */,
      68,    2,  966,    2, 0x0a /* Public */,
      69,    1,  971,    2, 0x0a /* Public */,
      70,    1,  974,    2, 0x0a /* Public */,
      71,    1,  977,    2, 0x0a /* Public */,
      72,    1,  980,    2, 0x0a /* Public */,
      73,    2,  983,    2, 0x0a /* Public */,
      74,    1,  988,    2, 0x0a /* Public */,
      75,    1,  991,    2, 0x0a /* Public */,
      76,    1,  994,    2, 0x0a /* Public */,
      77,    1,  997,    2, 0x0a /* Public */,
      78,    2, 1000,    2, 0x0a /* Public */,
      79,    1, 1005,    2, 0x0a /* Public */,
      80,    1, 1008,    2, 0x0a /* Public */,
      81,    1, 1011,    2, 0x0a /* Public */,
      82,    1, 1014,    2, 0x0a /* Public */,
      83,    2, 1017,    2, 0x0a /* Public */,
      84,    1, 1022,    2, 0x0a /* Public */,
      85,    1, 1025,    2, 0x0a /* Public */,
      86,    1, 1028,    2, 0x0a /* Public */,
      87,    1, 1031,    2, 0x0a /* Public */,
      88,    2, 1034,    2, 0x0a /* Public */,
      89,    1, 1039,    2, 0x0a /* Public */,
      90,    1, 1042,    2, 0x0a /* Public */,
      91,    1, 1045,    2, 0x0a /* Public */,
      92,    1, 1048,    2, 0x0a /* Public */,
      93,    2, 1051,    2, 0x0a /* Public */,
      94,    1, 1056,    2, 0x0a /* Public */,
      95,    1, 1059,    2, 0x0a /* Public */,
      96,    1, 1062,    2, 0x0a /* Public */,
      97,    1, 1065,    2, 0x0a /* Public */,
      98,    1, 1068,    2, 0x0a /* Public */,
      99,    1, 1071,    2, 0x0a /* Public */,
     100,    1, 1074,    2, 0x0a /* Public */,
     101,    1, 1077,    2, 0x0a /* Public */,
     102,    0, 1080,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
     103,    0, 1081,    2, 0x02 /* Public */,
     104,    0, 1082,    2, 0x02 /* Public */,
     105,    1, 1083,    2, 0x02 /* Public */,
     106,    0, 1086,    2, 0x02 /* Public */,
     107,    0, 1087,    2, 0x02 /* Public */,
     108,    0, 1088,    2, 0x02 /* Public */,
     109,    0, 1089,    2, 0x02 /* Public */,
     110,    0, 1090,    2, 0x02 /* Public */,
     111,    0, 1091,    2, 0x02 /* Public */,
     112,    0, 1092,    2, 0x02 /* Public */,
     113,    1, 1093,    2, 0x02 /* Public */,
     114,    0, 1096,    2, 0x02 /* Public */,
     115,    0, 1097,    2, 0x02 /* Public */,
     116,    0, 1098,    2, 0x02 /* Public */,
     117,    0, 1099,    2, 0x02 /* Public */,
     118,    1, 1100,    2, 0x02 /* Public */,
     119,    0, 1103,    2, 0x02 /* Public */,
     120,    0, 1104,    2, 0x02 /* Public */,
     121,    0, 1105,    2, 0x02 /* Public */,
     122,    0, 1106,    2, 0x02 /* Public */,
     123,    1, 1107,    2, 0x02 /* Public */,
     124,    0, 1110,    2, 0x02 /* Public */,
     125,    0, 1111,    2, 0x02 /* Public */,
     126,    0, 1112,    2, 0x02 /* Public */,
     127,    0, 1113,    2, 0x02 /* Public */,
     128,    1, 1114,    2, 0x02 /* Public */,
     129,    0, 1117,    2, 0x02 /* Public */,
     130,    0, 1118,    2, 0x02 /* Public */,
     131,    0, 1119,    2, 0x02 /* Public */,
     132,    0, 1120,    2, 0x02 /* Public */,
     133,    1, 1121,    2, 0x02 /* Public */,
     134,    0, 1124,    2, 0x02 /* Public */,
     135,    0, 1125,    2, 0x02 /* Public */,
     136,    0, 1126,    2, 0x02 /* Public */,
     137,    0, 1127,    2, 0x02 /* Public */,
     138,    1, 1128,    2, 0x02 /* Public */,
     139,    0, 1131,    2, 0x02 /* Public */,
     140,    0, 1132,    2, 0x02 /* Public */,
     141,    0, 1133,    2, 0x02 /* Public */,
     142,    0, 1134,    2, 0x02 /* Public */,
     143,    1, 1135,    2, 0x02 /* Public */,
     144,    0, 1138,    2, 0x02 /* Public */,
     145,    0, 1139,    2, 0x02 /* Public */,
     146,    0, 1140,    2, 0x02 /* Public */,
     147,    0, 1141,    2, 0x02 /* Public */,
     148,    0, 1142,    2, 0x02 /* Public */,
     149,    0, 1143,    2, 0x02 /* Public */,
     150,    0, 1144,    2, 0x02 /* Public */,
     151,    0, 1145,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    6,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
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

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    6,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,    6,    3,
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
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float, QMetaType::UInt,    6,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UShort,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    6,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    6,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    6,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    6,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    6,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar,
    QMetaType::UChar, QMetaType::UInt,    6,
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

 // properties: name, type, flags
     152, QMetaType::Float, 0x00495103,
     153, QMetaType::Float, 0x00495103,
     154, QMetaType::Float, 0x00495103,
     155, QMetaType::Float, 0x00495103,
     156, QMetaType::Float, 0x00495103,
     157, QMetaType::UShort, 0x00495103,
     158, QMetaType::UShort, 0x00495103,
     159, QMetaType::UShort, 0x00495103,
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
     171, QMetaType::UChar, 0x00495103,
     172, QMetaType::UChar, 0x00495103,
     173, QMetaType::UChar, 0x00495103,
     174, QMetaType::UChar, 0x00495103,
     175, QMetaType::UChar, 0x00495103,
     176, QMetaType::UChar, 0x00495103,
     177, QMetaType::UChar, 0x00495103,
     178, QMetaType::UChar, 0x00495103,
     179, QMetaType::UChar, 0x00495103,
     180, QMetaType::UChar, 0x00495103,
     181, QMetaType::UChar, 0x00495103,
     182, QMetaType::UChar, 0x00495103,
     183, QMetaType::UChar, 0x00495103,
     184, QMetaType::UChar, 0x00495103,
     185, QMetaType::UChar, 0x00495103,
     186, QMetaType::UChar, 0x00495103,
     187, QMetaType::UChar, 0x00495103,
     188, QMetaType::UChar, 0x00495103,
     189, QMetaType::UChar, 0x00495103,
     190, QMetaType::UChar, 0x00495103,
     191, QMetaType::UChar, 0x00495103,
     192, QMetaType::UChar, 0x00495103,

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
      11,
      12,
      13,
      14,
      16,
      17,
      18,
      19,
      21,
      22,
      23,
      24,
      26,
      27,
      28,
      29,
      31,
      32,
      33,
      34,
      36,
      37,
      38,
      39,
      41,
      42,
      43,
      44,
      45,
      46,
      47,
      48,

       0        // eod
};

void FlightModeSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FlightModeSettings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ReturnToBaseAltitudeOffsetChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->LandingVelocityChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->PositionHoldOffsetChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->PositionHoldOffset_HorizontalChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->PositionHoldOffset_VerticalChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->VarioControlLowPassAlphaChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->ArmedTimeoutChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 7: _t->ArmingSequenceTimeChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 8: _t->DisarmingSequenceTimeChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 9: _t->ArmingChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 10: _t->Stabilization1SettingsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 11: _t->Stabilization1Settings_RollChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->Stabilization1Settings_PitchChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 13: _t->Stabilization1Settings_YawChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->Stabilization1Settings_ThrustChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 15: _t->Stabilization2SettingsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 16: _t->Stabilization2Settings_RollChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 17: _t->Stabilization2Settings_PitchChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 18: _t->Stabilization2Settings_YawChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 19: _t->Stabilization2Settings_ThrustChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->Stabilization3SettingsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 21: _t->Stabilization3Settings_RollChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 22: _t->Stabilization3Settings_PitchChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 23: _t->Stabilization3Settings_YawChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 24: _t->Stabilization3Settings_ThrustChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 25: _t->Stabilization4SettingsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 26: _t->Stabilization4Settings_RollChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 27: _t->Stabilization4Settings_PitchChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 28: _t->Stabilization4Settings_YawChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 29: _t->Stabilization4Settings_ThrustChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 30: _t->Stabilization5SettingsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 31: _t->Stabilization5Settings_RollChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 32: _t->Stabilization5Settings_PitchChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 33: _t->Stabilization5Settings_YawChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 34: _t->Stabilization5Settings_ThrustChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 35: _t->Stabilization6SettingsChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 36: _t->Stabilization6Settings_RollChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 37: _t->Stabilization6Settings_PitchChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 38: _t->Stabilization6Settings_YawChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 39: _t->Stabilization6Settings_ThrustChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 40: _t->FlightModePositionChanged((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 41: _t->FlightModePosition_0Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 42: _t->FlightModePosition_1Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 43: _t->FlightModePosition_2Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 44: _t->FlightModePosition_3Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 45: _t->FlightModePosition_4Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 46: _t->FlightModePosition_5Changed((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 47: _t->DisableSanityChecksChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 48: _t->ReturnToBaseNextCommandChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 49: _t->setReturnToBaseAltitudeOffset((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 50: _t->setLandingVelocity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 51: _t->setPositionHoldOffset((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 52: _t->setPositionHoldOffset_Horizontal((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 53: _t->setPositionHoldOffset_Vertical((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 54: _t->setVarioControlLowPassAlpha((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 55: _t->setArmedTimeout((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 56: _t->setArmingSequenceTime((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 57: _t->setDisarmingSequenceTime((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 58: _t->setArming((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 59: _t->setStabilization1Settings((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 60: _t->setStabilization1Settings_Roll((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 61: _t->setStabilization1Settings_Pitch((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 62: _t->setStabilization1Settings_Yaw((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 63: _t->setStabilization1Settings_Thrust((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 64: _t->setStabilization2Settings((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 65: _t->setStabilization2Settings_Roll((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 66: _t->setStabilization2Settings_Pitch((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 67: _t->setStabilization2Settings_Yaw((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 68: _t->setStabilization2Settings_Thrust((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 69: _t->setStabilization3Settings((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 70: _t->setStabilization3Settings_Roll((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 71: _t->setStabilization3Settings_Pitch((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 72: _t->setStabilization3Settings_Yaw((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 73: _t->setStabilization3Settings_Thrust((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 74: _t->setStabilization4Settings((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 75: _t->setStabilization4Settings_Roll((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 76: _t->setStabilization4Settings_Pitch((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 77: _t->setStabilization4Settings_Yaw((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 78: _t->setStabilization4Settings_Thrust((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 79: _t->setStabilization5Settings((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 80: _t->setStabilization5Settings_Roll((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 81: _t->setStabilization5Settings_Pitch((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 82: _t->setStabilization5Settings_Yaw((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 83: _t->setStabilization5Settings_Thrust((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 84: _t->setStabilization6Settings((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 85: _t->setStabilization6Settings_Roll((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 86: _t->setStabilization6Settings_Pitch((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 87: _t->setStabilization6Settings_Yaw((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 88: _t->setStabilization6Settings_Thrust((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 89: _t->setFlightModePosition((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 90: _t->setFlightModePosition_0((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 91: _t->setFlightModePosition_1((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 92: _t->setFlightModePosition_2((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 93: _t->setFlightModePosition_3((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 94: _t->setFlightModePosition_4((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 95: _t->setFlightModePosition_5((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 96: _t->setDisableSanityChecks((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 97: _t->setReturnToBaseNextCommand((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 98: _t->emitNotifications(); break;
        case 99: { float _r = _t->getReturnToBaseAltitudeOffset();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 100: { float _r = _t->getLandingVelocity();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 101: { float _r = _t->getPositionHoldOffset((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 102: { float _r = _t->getPositionHoldOffset_Horizontal();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 103: { float _r = _t->getPositionHoldOffset_Vertical();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 104: { float _r = _t->getVarioControlLowPassAlpha();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 105: { quint16 _r = _t->getArmedTimeout();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 106: { quint16 _r = _t->getArmingSequenceTime();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 107: { quint16 _r = _t->getDisarmingSequenceTime();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 108: { quint8 _r = _t->getArming();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 109: { quint8 _r = _t->getStabilization1Settings((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 110: { quint8 _r = _t->getStabilization1Settings_Roll();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 111: { quint8 _r = _t->getStabilization1Settings_Pitch();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 112: { quint8 _r = _t->getStabilization1Settings_Yaw();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 113: { quint8 _r = _t->getStabilization1Settings_Thrust();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 114: { quint8 _r = _t->getStabilization2Settings((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 115: { quint8 _r = _t->getStabilization2Settings_Roll();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 116: { quint8 _r = _t->getStabilization2Settings_Pitch();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 117: { quint8 _r = _t->getStabilization2Settings_Yaw();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 118: { quint8 _r = _t->getStabilization2Settings_Thrust();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 119: { quint8 _r = _t->getStabilization3Settings((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 120: { quint8 _r = _t->getStabilization3Settings_Roll();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 121: { quint8 _r = _t->getStabilization3Settings_Pitch();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 122: { quint8 _r = _t->getStabilization3Settings_Yaw();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 123: { quint8 _r = _t->getStabilization3Settings_Thrust();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 124: { quint8 _r = _t->getStabilization4Settings((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 125: { quint8 _r = _t->getStabilization4Settings_Roll();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 126: { quint8 _r = _t->getStabilization4Settings_Pitch();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 127: { quint8 _r = _t->getStabilization4Settings_Yaw();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 128: { quint8 _r = _t->getStabilization4Settings_Thrust();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 129: { quint8 _r = _t->getStabilization5Settings((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 130: { quint8 _r = _t->getStabilization5Settings_Roll();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 131: { quint8 _r = _t->getStabilization5Settings_Pitch();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 132: { quint8 _r = _t->getStabilization5Settings_Yaw();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 133: { quint8 _r = _t->getStabilization5Settings_Thrust();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 134: { quint8 _r = _t->getStabilization6Settings((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 135: { quint8 _r = _t->getStabilization6Settings_Roll();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 136: { quint8 _r = _t->getStabilization6Settings_Pitch();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 137: { quint8 _r = _t->getStabilization6Settings_Yaw();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 138: { quint8 _r = _t->getStabilization6Settings_Thrust();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 139: { quint8 _r = _t->getFlightModePosition((*reinterpret_cast< quint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 140: { quint8 _r = _t->getFlightModePosition_0();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 141: { quint8 _r = _t->getFlightModePosition_1();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 142: { quint8 _r = _t->getFlightModePosition_2();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 143: { quint8 _r = _t->getFlightModePosition_3();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 144: { quint8 _r = _t->getFlightModePosition_4();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 145: { quint8 _r = _t->getFlightModePosition_5();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 146: { quint8 _r = _t->getDisableSanityChecks();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 147: { quint8 _r = _t->getReturnToBaseNextCommand();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FlightModeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::ReturnToBaseAltitudeOffsetChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::LandingVelocityChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::PositionHoldOffsetChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::PositionHoldOffset_HorizontalChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::PositionHoldOffset_VerticalChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::VarioControlLowPassAlphaChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::ArmedTimeoutChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::ArmingSequenceTimeChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::DisarmingSequenceTimeChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::ArmingChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization1SettingsChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization1Settings_RollChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization1Settings_PitchChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization1Settings_YawChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization1Settings_ThrustChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization2SettingsChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization2Settings_RollChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization2Settings_PitchChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization2Settings_YawChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization2Settings_ThrustChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization3SettingsChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization3Settings_RollChanged)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization3Settings_PitchChanged)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization3Settings_YawChanged)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization3Settings_ThrustChanged)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization4SettingsChanged)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization4Settings_RollChanged)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization4Settings_PitchChanged)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization4Settings_YawChanged)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization4Settings_ThrustChanged)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization5SettingsChanged)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization5Settings_RollChanged)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization5Settings_PitchChanged)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization5Settings_YawChanged)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization5Settings_ThrustChanged)) {
                *result = 34;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization6SettingsChanged)) {
                *result = 35;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization6Settings_RollChanged)) {
                *result = 36;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization6Settings_PitchChanged)) {
                *result = 37;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization6Settings_YawChanged)) {
                *result = 38;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::Stabilization6Settings_ThrustChanged)) {
                *result = 39;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint32 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::FlightModePositionChanged)) {
                *result = 40;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::FlightModePosition_0Changed)) {
                *result = 41;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::FlightModePosition_1Changed)) {
                *result = 42;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::FlightModePosition_2Changed)) {
                *result = 43;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::FlightModePosition_3Changed)) {
                *result = 44;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::FlightModePosition_4Changed)) {
                *result = 45;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::FlightModePosition_5Changed)) {
                *result = 46;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::DisableSanityChecksChanged)) {
                *result = 47;
                return;
            }
        }
        {
            using _t = void (FlightModeSettings::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlightModeSettings::ReturnToBaseNextCommandChanged)) {
                *result = 48;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FlightModeSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->getReturnToBaseAltitudeOffset(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->getLandingVelocity(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->getPositionHoldOffset_Horizontal(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->getPositionHoldOffset_Vertical(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->getVarioControlLowPassAlpha(); break;
        case 5: *reinterpret_cast< quint16*>(_v) = _t->getArmedTimeout(); break;
        case 6: *reinterpret_cast< quint16*>(_v) = _t->getArmingSequenceTime(); break;
        case 7: *reinterpret_cast< quint16*>(_v) = _t->getDisarmingSequenceTime(); break;
        case 8: *reinterpret_cast< quint8*>(_v) = _t->getArming(); break;
        case 9: *reinterpret_cast< quint8*>(_v) = _t->getStabilization1Settings_Roll(); break;
        case 10: *reinterpret_cast< quint8*>(_v) = _t->getStabilization1Settings_Pitch(); break;
        case 11: *reinterpret_cast< quint8*>(_v) = _t->getStabilization1Settings_Yaw(); break;
        case 12: *reinterpret_cast< quint8*>(_v) = _t->getStabilization1Settings_Thrust(); break;
        case 13: *reinterpret_cast< quint8*>(_v) = _t->getStabilization2Settings_Roll(); break;
        case 14: *reinterpret_cast< quint8*>(_v) = _t->getStabilization2Settings_Pitch(); break;
        case 15: *reinterpret_cast< quint8*>(_v) = _t->getStabilization2Settings_Yaw(); break;
        case 16: *reinterpret_cast< quint8*>(_v) = _t->getStabilization2Settings_Thrust(); break;
        case 17: *reinterpret_cast< quint8*>(_v) = _t->getStabilization3Settings_Roll(); break;
        case 18: *reinterpret_cast< quint8*>(_v) = _t->getStabilization3Settings_Pitch(); break;
        case 19: *reinterpret_cast< quint8*>(_v) = _t->getStabilization3Settings_Yaw(); break;
        case 20: *reinterpret_cast< quint8*>(_v) = _t->getStabilization3Settings_Thrust(); break;
        case 21: *reinterpret_cast< quint8*>(_v) = _t->getStabilization4Settings_Roll(); break;
        case 22: *reinterpret_cast< quint8*>(_v) = _t->getStabilization4Settings_Pitch(); break;
        case 23: *reinterpret_cast< quint8*>(_v) = _t->getStabilization4Settings_Yaw(); break;
        case 24: *reinterpret_cast< quint8*>(_v) = _t->getStabilization4Settings_Thrust(); break;
        case 25: *reinterpret_cast< quint8*>(_v) = _t->getStabilization5Settings_Roll(); break;
        case 26: *reinterpret_cast< quint8*>(_v) = _t->getStabilization5Settings_Pitch(); break;
        case 27: *reinterpret_cast< quint8*>(_v) = _t->getStabilization5Settings_Yaw(); break;
        case 28: *reinterpret_cast< quint8*>(_v) = _t->getStabilization5Settings_Thrust(); break;
        case 29: *reinterpret_cast< quint8*>(_v) = _t->getStabilization6Settings_Roll(); break;
        case 30: *reinterpret_cast< quint8*>(_v) = _t->getStabilization6Settings_Pitch(); break;
        case 31: *reinterpret_cast< quint8*>(_v) = _t->getStabilization6Settings_Yaw(); break;
        case 32: *reinterpret_cast< quint8*>(_v) = _t->getStabilization6Settings_Thrust(); break;
        case 33: *reinterpret_cast< quint8*>(_v) = _t->getFlightModePosition_0(); break;
        case 34: *reinterpret_cast< quint8*>(_v) = _t->getFlightModePosition_1(); break;
        case 35: *reinterpret_cast< quint8*>(_v) = _t->getFlightModePosition_2(); break;
        case 36: *reinterpret_cast< quint8*>(_v) = _t->getFlightModePosition_3(); break;
        case 37: *reinterpret_cast< quint8*>(_v) = _t->getFlightModePosition_4(); break;
        case 38: *reinterpret_cast< quint8*>(_v) = _t->getFlightModePosition_5(); break;
        case 39: *reinterpret_cast< quint8*>(_v) = _t->getDisableSanityChecks(); break;
        case 40: *reinterpret_cast< quint8*>(_v) = _t->getReturnToBaseNextCommand(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<FlightModeSettings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setReturnToBaseAltitudeOffset(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setLandingVelocity(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setPositionHoldOffset_Horizontal(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setPositionHoldOffset_Vertical(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setVarioControlLowPassAlpha(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setArmedTimeout(*reinterpret_cast< quint16*>(_v)); break;
        case 6: _t->setArmingSequenceTime(*reinterpret_cast< quint16*>(_v)); break;
        case 7: _t->setDisarmingSequenceTime(*reinterpret_cast< quint16*>(_v)); break;
        case 8: _t->setArming(*reinterpret_cast< quint8*>(_v)); break;
        case 9: _t->setStabilization1Settings_Roll(*reinterpret_cast< quint8*>(_v)); break;
        case 10: _t->setStabilization1Settings_Pitch(*reinterpret_cast< quint8*>(_v)); break;
        case 11: _t->setStabilization1Settings_Yaw(*reinterpret_cast< quint8*>(_v)); break;
        case 12: _t->setStabilization1Settings_Thrust(*reinterpret_cast< quint8*>(_v)); break;
        case 13: _t->setStabilization2Settings_Roll(*reinterpret_cast< quint8*>(_v)); break;
        case 14: _t->setStabilization2Settings_Pitch(*reinterpret_cast< quint8*>(_v)); break;
        case 15: _t->setStabilization2Settings_Yaw(*reinterpret_cast< quint8*>(_v)); break;
        case 16: _t->setStabilization2Settings_Thrust(*reinterpret_cast< quint8*>(_v)); break;
        case 17: _t->setStabilization3Settings_Roll(*reinterpret_cast< quint8*>(_v)); break;
        case 18: _t->setStabilization3Settings_Pitch(*reinterpret_cast< quint8*>(_v)); break;
        case 19: _t->setStabilization3Settings_Yaw(*reinterpret_cast< quint8*>(_v)); break;
        case 20: _t->setStabilization3Settings_Thrust(*reinterpret_cast< quint8*>(_v)); break;
        case 21: _t->setStabilization4Settings_Roll(*reinterpret_cast< quint8*>(_v)); break;
        case 22: _t->setStabilization4Settings_Pitch(*reinterpret_cast< quint8*>(_v)); break;
        case 23: _t->setStabilization4Settings_Yaw(*reinterpret_cast< quint8*>(_v)); break;
        case 24: _t->setStabilization4Settings_Thrust(*reinterpret_cast< quint8*>(_v)); break;
        case 25: _t->setStabilization5Settings_Roll(*reinterpret_cast< quint8*>(_v)); break;
        case 26: _t->setStabilization5Settings_Pitch(*reinterpret_cast< quint8*>(_v)); break;
        case 27: _t->setStabilization5Settings_Yaw(*reinterpret_cast< quint8*>(_v)); break;
        case 28: _t->setStabilization5Settings_Thrust(*reinterpret_cast< quint8*>(_v)); break;
        case 29: _t->setStabilization6Settings_Roll(*reinterpret_cast< quint8*>(_v)); break;
        case 30: _t->setStabilization6Settings_Pitch(*reinterpret_cast< quint8*>(_v)); break;
        case 31: _t->setStabilization6Settings_Yaw(*reinterpret_cast< quint8*>(_v)); break;
        case 32: _t->setStabilization6Settings_Thrust(*reinterpret_cast< quint8*>(_v)); break;
        case 33: _t->setFlightModePosition_0(*reinterpret_cast< quint8*>(_v)); break;
        case 34: _t->setFlightModePosition_1(*reinterpret_cast< quint8*>(_v)); break;
        case 35: _t->setFlightModePosition_2(*reinterpret_cast< quint8*>(_v)); break;
        case 36: _t->setFlightModePosition_3(*reinterpret_cast< quint8*>(_v)); break;
        case 37: _t->setFlightModePosition_4(*reinterpret_cast< quint8*>(_v)); break;
        case 38: _t->setFlightModePosition_5(*reinterpret_cast< quint8*>(_v)); break;
        case 39: _t->setDisableSanityChecks(*reinterpret_cast< quint8*>(_v)); break;
        case 40: _t->setReturnToBaseNextCommand(*reinterpret_cast< quint8*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject FlightModeSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<UAVDataObject::staticMetaObject>(),
    qt_meta_stringdata_FlightModeSettings.data,
    qt_meta_data_FlightModeSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FlightModeSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlightModeSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlightModeSettings.stringdata0))
        return static_cast<void*>(this);
    return UAVDataObject::qt_metacast(_clname);
}

int FlightModeSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UAVDataObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 148)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 148;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 148)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 148;
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
void FlightModeSettings::ReturnToBaseAltitudeOffsetChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FlightModeSettings::LandingVelocityChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FlightModeSettings::PositionHoldOffsetChanged(quint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FlightModeSettings::PositionHoldOffset_HorizontalChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FlightModeSettings::PositionHoldOffset_VerticalChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FlightModeSettings::VarioControlLowPassAlphaChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void FlightModeSettings::ArmedTimeoutChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void FlightModeSettings::ArmingSequenceTimeChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void FlightModeSettings::DisarmingSequenceTimeChanged(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void FlightModeSettings::ArmingChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void FlightModeSettings::Stabilization1SettingsChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void FlightModeSettings::Stabilization1Settings_RollChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void FlightModeSettings::Stabilization1Settings_PitchChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void FlightModeSettings::Stabilization1Settings_YawChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void FlightModeSettings::Stabilization1Settings_ThrustChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void FlightModeSettings::Stabilization2SettingsChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void FlightModeSettings::Stabilization2Settings_RollChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void FlightModeSettings::Stabilization2Settings_PitchChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void FlightModeSettings::Stabilization2Settings_YawChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void FlightModeSettings::Stabilization2Settings_ThrustChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void FlightModeSettings::Stabilization3SettingsChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void FlightModeSettings::Stabilization3Settings_RollChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void FlightModeSettings::Stabilization3Settings_PitchChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void FlightModeSettings::Stabilization3Settings_YawChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void FlightModeSettings::Stabilization3Settings_ThrustChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void FlightModeSettings::Stabilization4SettingsChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void FlightModeSettings::Stabilization4Settings_RollChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void FlightModeSettings::Stabilization4Settings_PitchChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void FlightModeSettings::Stabilization4Settings_YawChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void FlightModeSettings::Stabilization4Settings_ThrustChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void FlightModeSettings::Stabilization5SettingsChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void FlightModeSettings::Stabilization5Settings_RollChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void FlightModeSettings::Stabilization5Settings_PitchChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void FlightModeSettings::Stabilization5Settings_YawChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void FlightModeSettings::Stabilization5Settings_ThrustChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void FlightModeSettings::Stabilization6SettingsChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 35, _a);
}

// SIGNAL 36
void FlightModeSettings::Stabilization6Settings_RollChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 36, _a);
}

// SIGNAL 37
void FlightModeSettings::Stabilization6Settings_PitchChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 37, _a);
}

// SIGNAL 38
void FlightModeSettings::Stabilization6Settings_YawChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 38, _a);
}

// SIGNAL 39
void FlightModeSettings::Stabilization6Settings_ThrustChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 39, _a);
}

// SIGNAL 40
void FlightModeSettings::FlightModePositionChanged(quint32 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 40, _a);
}

// SIGNAL 41
void FlightModeSettings::FlightModePosition_0Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 41, _a);
}

// SIGNAL 42
void FlightModeSettings::FlightModePosition_1Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 42, _a);
}

// SIGNAL 43
void FlightModeSettings::FlightModePosition_2Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 43, _a);
}

// SIGNAL 44
void FlightModeSettings::FlightModePosition_3Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 44, _a);
}

// SIGNAL 45
void FlightModeSettings::FlightModePosition_4Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 45, _a);
}

// SIGNAL 46
void FlightModeSettings::FlightModePosition_5Changed(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 46, _a);
}

// SIGNAL 47
void FlightModeSettings::DisableSanityChecksChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 47, _a);
}

// SIGNAL 48
void FlightModeSettings::ReturnToBaseNextCommandChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 48, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
