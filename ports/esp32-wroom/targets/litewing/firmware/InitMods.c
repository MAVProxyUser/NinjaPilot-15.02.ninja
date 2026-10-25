/**
 ******************************************************************************
 * @file       InitMods.c
 * @author     NinjaPilot, 2026
 * @brief      Module init/start table for the ESP32-WROOM-32E target.
 *
 * The Make-based targets generate this from their MODULES list (see the
 * ${OUTDIR}/InitMods.c rule in simposix/firmware/Makefile). This target
 * builds under ESP-IDF's CMake instead, so the file is checked in.
 *
 * KEEP IN SYNC with the NINJA_MODULE_SRCS list in esp-idf/main/CMakeLists.txt.
 * A module compiled in but missing here simply never starts, silently.
 *
 * Navigation build: Sensors publishes the *Sensor objects and StateEstimation
 * runs the stock filter chain selected by RevoSettings.FusionAlgorithm,
 * producing AttitudeState/PositionState/VelocityState. This replaced the
 * standalone complementary filter (modules/Attitude) and modules/AltFilter.
 *
 * ORDER MATTERS: Sensors must initialize before StateEstimation, which
 * connects callbacks to the *Sensor objects StateEstimation consumes.
 * @see        The GNU Public License (GPL) Version 3
 *****************************************************************************/

extern unsigned int SensorsInitialize(void);
extern unsigned int StateEstimationInitialize(void);
extern unsigned int StabilizationInitialize(void);
extern unsigned int ActuatorInitialize(void);
extern unsigned int ReceiverInitialize(void);
extern unsigned int ManualControlInitialize(void);
extern unsigned int TelemetryInitialize(void);
extern unsigned int RemoteIDInitialize(void);
extern unsigned int GPSInitialize(void);
extern unsigned int PathFollowerInitialize(void);

extern unsigned int SensorsStart(void);
extern unsigned int StateEstimationStart(void);
extern unsigned int StabilizationStart(void);
extern unsigned int ActuatorStart(void);
extern unsigned int ReceiverStart(void);
extern unsigned int ManualControlStart(void);
extern unsigned int TelemetryStart(void);
extern unsigned int RemoteIDStart(void);
extern unsigned int GPSStart(void);
extern unsigned int PathFollowerStart(void);

void InitModules(void)
{
    SensorsInitialize();
    StateEstimationInitialize();
    StabilizationInitialize();
    ActuatorInitialize();
    ReceiverInitialize();
    ManualControlInitialize();
    TelemetryInitialize();
    RemoteIDInitialize();
    GPSInitialize();
    PathFollowerInitialize();
}

void StartModules(void)
{
    SensorsStart();
    StateEstimationStart();
    StabilizationStart();
    ActuatorStart();
    ReceiverStart();
    ManualControlStart();
    TelemetryStart();
    RemoteIDStart();
    GPSStart();
    PathFollowerStart();
}
