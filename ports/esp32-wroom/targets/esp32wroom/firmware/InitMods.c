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
 * CC-class build: Attitude is the standalone complementary filter
 * (modules/Attitude/attitude.c), not the StateEstimation chain. Every
 * Stabilization mode (Rate, Attitude, AxisLock, Rattitude, ...) is available;
 * what is absent is navigation (no baro/mag/GPS modules).
 * @see        The GNU Public License (GPL) Version 3
 *****************************************************************************/

extern unsigned int AttitudeInitialize(void);
extern unsigned int StabilizationInitialize(void);
extern unsigned int ActuatorInitialize(void);
extern unsigned int ReceiverInitialize(void);
extern unsigned int ManualControlInitialize(void);
extern unsigned int TelemetryInitialize(void);
extern unsigned int RemoteIDInitialize(void);

extern unsigned int AttitudeStart(void);
extern unsigned int StabilizationStart(void);
extern unsigned int ActuatorStart(void);
extern unsigned int ReceiverStart(void);
extern unsigned int ManualControlStart(void);
extern unsigned int TelemetryStart(void);
extern unsigned int RemoteIDStart(void);

void InitModules(void)
{
    AttitudeInitialize();
    StabilizationInitialize();
    ActuatorInitialize();
    ReceiverInitialize();
    ManualControlInitialize();
    TelemetryInitialize();
    RemoteIDInitialize();
}

void StartModules(void)
{
    AttitudeStart();
    StabilizationStart();
    ActuatorStart();
    ReceiverStart();
    ManualControlStart();
    TelemetryStart();
    RemoteIDStart();
}
