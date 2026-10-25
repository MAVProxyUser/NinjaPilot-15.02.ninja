# The ESP32 port, built as the IDF 'main' component.
#
# This project lives OUTSIDE the NinjaPilot tree on purpose -- it consumes that
# tree's flight code but does not modify it. Point NINJAPILOT_ROOT at your
# checkout; the default assumes it is a sibling directory:
#
#   cmake -DNINJAPILOT_ROOT=/path/to/NinjaPilot-15.02.ninja ...
#
# The handful of upstream changes this port needs are NOT applied here. They
# are kept as patches/ninjapilot-shared-changes.patch so the flight tree stays
# clean until you choose to apply them. See README.md.
set(ESP32PORT ${CMAKE_CURRENT_LIST_DIR}/../../../..)

if(NOT DEFINED NINJAPILOT_ROOT)
    set(NINJAPILOT_ROOT ${ESP32PORT}/../NinjaPilot-15.02.ninja)
endif()
get_filename_component(NINJAPILOT_ROOT "${NINJAPILOT_ROOT}" ABSOLUTE)

if(NOT EXISTS ${NINJAPILOT_ROOT}/flight/pios/pios.h)
    message(FATAL_ERROR
        "NINJAPILOT_ROOT does not look like a NinjaPilot checkout: ${NINJAPILOT_ROOT}\n"
        "Pass -DNINJAPILOT_ROOT=/path/to/NinjaPilot-15.02.ninja")
endif()

set(FLIGHT ${NINJAPILOT_ROOT}/flight)
set(BOARD  ${ESP32PORT}/targets/esp32wroom)

# Generated UAVObject sources, produced in the NinjaPilot tree by
#   make ROOT_DIR=$PWD uavobjects_flight
# (through a space-free symlink -- see README.md).
set(UAVOSYNTH ${NINJAPILOT_ROOT}/build/uavobject-synthetics/flight)

# --- PiOS: ESP32 backend ----------------------------------------------
set(PIOS_ESP32_SRCS
    ${ESP32PORT}/pios/esp32/pios_sys.c
    ${ESP32PORT}/pios/esp32/pios_delay.c
    ${ESP32PORT}/pios/esp32/pios_irq.c
    ${ESP32PORT}/pios/esp32/pios_led.c
    ${ESP32PORT}/pios/esp32/pios_debug.c
    ${ESP32PORT}/pios/esp32/pios_wdg.c
    ${ESP32PORT}/pios/esp32/pios_usart.c
    ${ESP32PORT}/pios/esp32/pios_spi.c
    ${ESP32PORT}/pios/esp32/pios_servo.c
    ${ESP32PORT}/pios/esp32/pios_exti.c
    ${ESP32PORT}/pios/esp32/pios_ppm.c
    ${ESP32PORT}/pios/esp32/pios_dsm.c
    ${ESP32PORT}/pios/esp32/pios_flashfs_nvs.c
    ${ESP32PORT}/pios/esp32/pios_wifi.c
    ${ESP32PORT}/pios/esp32/pios_rid_wifi.c
    ${ESP32PORT}/pios/esp32/pios_task_runtime.c
)

# --- PiOS: shared ------------------------------------------------------
# NOTE: pios/common/pios_led.c is deliberately EXCLUDED -- it takes a
# struct pios_gpio_cfg (STM32) and pios/esp32/pios_led.c provides the same
# symbols for this target.
set(PIOS_COMMON_SRCS
    ${FLIGHT}/pios/common/pios_com.c
    ${FLIGHT}/pios/common/pios_rcvr.c
    ${FLIGHT}/pios/common/pios_gcsrcvr.c
    ${FLIGHT}/pios/common/pios_mem.c
    ${FLIGHT}/pios/common/pios_crc.c
    ${FLIGHT}/pios/common/pios_deltatime.c
    ${FLIGHT}/pios/common/pios_sensors.c
    ${FLIGHT}/pios/common/pios_task_monitor.c
    ${FLIGHT}/pios/common/pios_callbackscheduler.c
    # ICM-20602, not MPU6000 -- see the header of this file for why it is
    # a separate driver rather than an exception in the shared one.
    ${ESP32PORT}/pios/esp32/pios_icm20602.c
    ${FLIGHT}/pios/common/pios_notify.c
)

# --- UAVObject / UAVTalk machinery -------------------------------------
set(UAVO_SRCS
    ${FLIGHT}/uavobjects/uavobjectmanager.c
    # Real UAVObjSave/UAVObjLoad. Without this they are weak stubs and
    # nothing persists no matter what PIOS_FLASHFS does.
    ${FLIGHT}/uavobjects/uavobjectpersistence.c
    ${FLIGHT}/uavobjects/eventdispatcher.c
    ${FLIGHT}/uavtalk/uavtalk.c
)

# --- Flight libraries --------------------------------------------------
set(LIB_SRCS
    ${FLIGHT}/libraries/alarms.c
    ${FLIGHT}/libraries/CoordinateConversions.c
    ${FLIGHT}/libraries/sanitycheck.c
    ${FLIGHT}/libraries/notification.c
    ${FLIGHT}/libraries/opendroneid/opendroneid.c
    ${FLIGHT}/libraries/optypes.c
    ${FLIGHT}/libraries/fifo_buffer.c
    ${FLIGHT}/libraries/math/pid.c
    ${FLIGHT}/libraries/math/mathmisc.c
    ${FLIGHT}/libraries/math/sin_lookup.c
    ${FLIGHT}/libraries/math/butterworth.c
)


# --- Modules -----------------------------------------------------------
# KEEP IN SYNC with InitMods.c. A module here but not there never starts.
# Rate-mode-only: Attitude is the standalone complementary filter, not the
# StateEstimation chain.
set(NINJA_MODULE_SRCS
    ${FLIGHT}/modules/Attitude/attitude.c
    ${FLIGHT}/modules/Stabilization/stabilization.c
    ${FLIGHT}/modules/Stabilization/innerloop.c
    ${FLIGHT}/modules/Stabilization/outerloop.c
    ${FLIGHT}/modules/Stabilization/cruisecontrol.c
    ${FLIGHT}/modules/Stabilization/virtualflybar.c
    ${FLIGHT}/modules/Stabilization/relay_tuning.c
    ${FLIGHT}/modules/Actuator/actuator.c
    ${FLIGHT}/modules/Receiver/receiver.c
    ${FLIGHT}/modules/ManualControl/manualcontrol.c
    ${FLIGHT}/modules/ManualControl/armhandler.c
    ${FLIGHT}/modules/ManualControl/manualhandler.c
    ${FLIGHT}/modules/ManualControl/stabilizedhandler.c
    ${FLIGHT}/modules/ManualControl/pathfollowerhandler.c
    ${FLIGHT}/modules/ManualControl/pathplannerhandler.c
    ${FLIGHT}/modules/ManualControl/takeofflocationhandler.c
    ${FLIGHT}/modules/Telemetry/telemetry.c
    ${FLIGHT}/modules/RemoteID/remoteid.c
    ${FLIGHT}/modules/System/systemmod.c
)

# --- Board -------------------------------------------------------------
set(BOARD_SRCS
    ${BOARD}/firmware/esp32wroom.c
    ${BOARD}/firmware/pios_board.c
    ${BOARD}/firmware/InitMods.c
)

# --- Generated UAVObjects ---------------------------------------------
set(UAVO_SYNTH_SRCS
    ${UAVOSYNTH}/accelgyrosettings.c
    ${UAVOSYNTH}/accelsensor.c
    ${UAVOSYNTH}/accelstate.c
    ${UAVOSYNTH}/accessorydesired.c
    ${UAVOSYNTH}/actuatorcommand.c
    ${UAVOSYNTH}/actuatordesired.c
    ${UAVOSYNTH}/actuatorsettings.c
    ${UAVOSYNTH}/airspeedsensor.c
    ${UAVOSYNTH}/airspeedsettings.c
    ${UAVOSYNTH}/airspeedstate.c
    ${UAVOSYNTH}/ak8975sensor.c
    ${UAVOSYNTH}/altitudefiltersettings.c
    ${UAVOSYNTH}/altitudeholdsettings.c
    ${UAVOSYNTH}/altitudeholdstatus.c
    ${UAVOSYNTH}/attitudesettings.c
    ${UAVOSYNTH}/attitudesimulated.c
    ${UAVOSYNTH}/attitudestate.c
    ${UAVOSYNTH}/auxmagsensor.c
    ${UAVOSYNTH}/auxmagsettings.c
    ${UAVOSYNTH}/barosensor.c
    ${UAVOSYNTH}/callbackinfo.c
    ${UAVOSYNTH}/debuglogcontrol.c
    ${UAVOSYNTH}/debuglogentry.c
    ${UAVOSYNTH}/debuglogsettings.c
    ${UAVOSYNTH}/debuglogstatus.c
    ${UAVOSYNTH}/ekfconfiguration.c
    ${UAVOSYNTH}/ekfstatevariance.c
    ${UAVOSYNTH}/faultsettings.c
    ${UAVOSYNTH}/firmwareiapobj.c
    ${UAVOSYNTH}/settingsgeneration.c
    ${UAVOSYNTH}/flipstatus.c
    ${UAVOSYNTH}/remoteidsettings.c
    ${UAVOSYNTH}/remoteidstatus.c
    ${UAVOSYNTH}/fixedwingpathfollowersettings.c
    ${UAVOSYNTH}/fixedwingpathfollowerstatus.c
    ${UAVOSYNTH}/flightbatterysettings.c
    ${UAVOSYNTH}/flightbatterystate.c
    ${UAVOSYNTH}/flightmodesettings.c
    ${UAVOSYNTH}/flightplancontrol.c
    ${UAVOSYNTH}/flightplansettings.c
    ${UAVOSYNTH}/flightplanstatus.c
    ${UAVOSYNTH}/flightstatus.c
    ${UAVOSYNTH}/flighttelemetrystats.c
    ${UAVOSYNTH}/gcsreceiver.c
    ${UAVOSYNTH}/gcstelemetrystats.c
    ${UAVOSYNTH}/gpsextendedstatus.c
    ${UAVOSYNTH}/gpspositionsensor.c
    ${UAVOSYNTH}/gpssatellites.c
    ${UAVOSYNTH}/gpssettings.c
    ${UAVOSYNTH}/gpstime.c
    ${UAVOSYNTH}/gpsvelocitysensor.c
    ${UAVOSYNTH}/groundpathfollowersettings.c
    ${UAVOSYNTH}/groundtruth.c
    ${UAVOSYNTH}/gyrosensor.c
    ${UAVOSYNTH}/gyrostate.c
    ${UAVOSYNTH}/homelocation.c
    ${UAVOSYNTH}/hwsettings.c
    ${UAVOSYNTH}/i2cbusscan.c
    ${UAVOSYNTH}/i2cstats.c
    ${UAVOSYNTH}/magsensor.c
    ${UAVOSYNTH}/magstate.c
    ${UAVOSYNTH}/manualcontrolcommand.c
    ${UAVOSYNTH}/manualcontrolsettings.c
    ${UAVOSYNTH}/missionprogress.c
    ${UAVOSYNTH}/missionrecoverysettings.c
    ${UAVOSYNTH}/mixersettings.c
    ${UAVOSYNTH}/mixerstatus.c
    ${UAVOSYNTH}/mpu6000settings.c
    ${UAVOSYNTH}/nedaccel.c
    ${UAVOSYNTH}/objectpersistence.c
    ${UAVOSYNTH}/oplinkreceiver.c
    ${UAVOSYNTH}/oplinksettings.c
    ${UAVOSYNTH}/oplinkstatus.c
    ${UAVOSYNTH}/osdsettings.c
    ${UAVOSYNTH}/pathaction.c
    ${UAVOSYNTH}/pathdesired.c
    ${UAVOSYNTH}/pathplan.c
    ${UAVOSYNTH}/pathstatus.c
    ${UAVOSYNTH}/pathsummary.c
    ${UAVOSYNTH}/perfcounter.c
    ${UAVOSYNTH}/pidstatus.c
    ${UAVOSYNTH}/poilearnsettings.c
    ${UAVOSYNTH}/poilocation.c
    ${UAVOSYNTH}/positionstate.c
    ${UAVOSYNTH}/radiocombridgestats.c
    ${UAVOSYNTH}/ratedesired.c
    ${UAVOSYNTH}/receiveractivity.c
    ${UAVOSYNTH}/relaytuning.c
    ${UAVOSYNTH}/relaytuningsettings.c
    ${UAVOSYNTH}/revocalibration.c
    ${UAVOSYNTH}/revosettings.c
    ${UAVOSYNTH}/sensorhubsettings.c
    ${UAVOSYNTH}/sonaraltitude.c
    ${UAVOSYNTH}/stabilizationbank.c
    ${UAVOSYNTH}/stabilizationdesired.c
    ${UAVOSYNTH}/stabilizationsettings.c
    ${UAVOSYNTH}/stabilizationsettingsbank1.c
    ${UAVOSYNTH}/stabilizationsettingsbank2.c
    ${UAVOSYNTH}/stabilizationsettingsbank3.c
    ${UAVOSYNTH}/stabilizationstatus.c
    ${UAVOSYNTH}/statusgrounddrive.c
    ${UAVOSYNTH}/statusvtolland.c
    ${UAVOSYNTH}/systemalarms.c
    ${UAVOSYNTH}/systemsettings.c
    ${UAVOSYNTH}/systemstats.c
    ${UAVOSYNTH}/takeofflocation.c
    ${UAVOSYNTH}/taskinfo.c
    ${UAVOSYNTH}/txpidsettings.c
    ${UAVOSYNTH}/uavobjectsinit.c
    ${UAVOSYNTH}/velocitydesired.c
    ${UAVOSYNTH}/velocitystate.c
    ${UAVOSYNTH}/vtolpathfollowersettings.c
    ${UAVOSYNTH}/vtolselftuningstats.c
    ${UAVOSYNTH}/watchdogstatus.c
    ${UAVOSYNTH}/waypoint.c
    ${UAVOSYNTH}/waypointactive.c
)

# Generate the firmware version blob header (git + UAVO-set hash) so the
# GCS's version-mismatch check has something truthful to compare against.
execute_process(
    COMMAND python3 "${NINJAPILOT_ROOT}/make/scripts/version-info.py"
            --path=${CMAKE_CURRENT_LIST_DIR}/../../../..
            --uavodir=${NINJAPILOT_ROOT}/shared/uavobjectdefinition
            --template=${CMAKE_CURRENT_LIST_DIR}/fw_version_info.tpl
            --outfile=${CMAKE_BINARY_DIR}/fw_version_info.h
    RESULT_VARIABLE FW_VERSION_RC)
if(NOT FW_VERSION_RC EQUAL 0)
    message(FATAL_ERROR "fw_version_info.h generation failed")
endif()

idf_component_register(
    SRCS
        ${BOARD_SRCS}
        ${PIOS_ESP32_SRCS}
        ${PIOS_COMMON_SRCS}
        ${UAVO_SRCS}
        ${UAVO_SYNTH_SRCS}
        ${LIB_SRCS}
        ${NINJA_MODULE_SRCS}
    INCLUDE_DIRS
        ${CMAKE_BINARY_DIR}
        ${BOARD}
        ${BOARD}/firmware
        ${BOARD}/firmware/inc
        ${FLIGHT}/pios
        ${FLIGHT}/pios/inc
        ${ESP32PORT}/pios/esp32
        ${ESP32PORT}/pios/esp32/inc
        ${FLIGHT}/uavobjects/inc
        ${FLIGHT}/uavtalk/inc
        ${FLIGHT}/libraries/inc
        ${FLIGHT}/libraries/math
        ${FLIGHT}/modules/Attitude/inc
        ${FLIGHT}/modules/Stabilization/inc
        ${FLIGHT}/modules/Actuator/inc
        ${FLIGHT}/modules/ManualControl/inc
        ${FLIGHT}/modules/Telemetry/inc
        ${FLIGHT}/modules/RemoteID/inc
        ${FLIGHT}/libraries/opendroneid
        ${FLIGHT}/modules/System/inc
        ${UAVOSYNTH}
        # pios_instrumentation.h and friends include "FreeRTOS.h" without
        # the freertos/ prefix IDF normally requires.
        $ENV{IDF_PATH}/components/freertos/FreeRTOS-Kernel/include/freertos
    REQUIRES
        esp_wifi
        esp_netif
        esp_event
        lwip
        driver
        esp_timer
        esp_adc
        nvs_flash
        esp_system
        esp_hw_support
)

# The vendored reference encoder prints uint32_t with %u in its debug helpers;
# Xtensa newlib makes that a -Werror=format. Unmodified upstream file, so exempt
# it. Must come after idf_component_register and not during IDF's early
# script-mode pass (set_source_files_properties is "not scriptable" there).
if(NOT CMAKE_BUILD_EARLY_EXPANSION)
    set_source_files_properties(${FLIGHT}/libraries/opendroneid/opendroneid.c
        PROPERTIES COMPILE_OPTIONS "-Wno-format")
endif()


# Keeps the UAVObject handle table in writable RAM *and* preserves the
# __start__/__stop__ boundary symbols. See the header of uavo_handles.ld --
# both properties are required and the obvious fixes each lose one of them.
target_linker_script(${COMPONENT_LIB} INTERFACE "uavo_handles.ld")

# USE_ESP32 is what pios.h keys the architecture selection off. Without it the
# build silently falls into the STM32 include path and fails confusingly.
target_compile_definitions(${COMPONENT_LIB} PRIVATE
    USE_ESP32=1
    # Onboard Flip module deliberately NOT built for the real board (user
    # call, 2026-09-01): sim-twin only until it has earned trust there. The
    # FlipStatus UAVO stays compiled so the object set matches the sim (no
    # GCS version mismatch) - it simply sits at Idle with nothing driving it,
    # and the stabilizedhandler ownership guard compiles out without
    # MODULE_FLIP_BUILTIN.
    # Autotune module likewise NOT built for the real board: tuning happens
    # through bank DEFAULTS and the GCS only. Both remain available to the
    # sim targets.
    # Per-task diagnostics (TaskInfo/CallbackInfo: stack remaining, running
    # flag, runtime percent). Without this the objects exist but stay
    # all-zero -- which cost a full wedge-reproduction run whose TaskInfo
    # dumps came back empty. The cost is a 1Hz walk of the task list from
    # systemmod; keep it on, this board is still being brought up.
    # DIAG_TASKS: per-task stack/runtime in TaskInfo. OFF for normal builds:
    # its 1Hz task-table walk runs with the scheduler SUSPENDED, and the walk
    # got longer when WiFi added five tasks -- a periodic global stall. Turn
    # it back on when hunting a task-level problem.
    # DIAG_TASKS=1
    # BOARD_ESC_CAL: USB-free ESC endpoint calibration at power-up (max 6s,
    # then min). Flash it, UNPLUG USB, connect battery, listen for the tones,
    # reflash normal firmware. PROPS OFF. Never ship enabled. This exists
    # because battery and USB must NEVER be connected together on this
    # airframe (BEC 5V feeds VUSB) -- so no serial tool may ever drive ESC
    # calibration.
    # BOARD_PWM_SELFTEST sweeps every motor output during board init. Verified
    # working on hardware and then deliberately turned back OFF -- a flight
    # controller that spins its motors on every power-up is not something to
    # leave enabled. Add BOARD_PWM_SELFTEST=1 here to run it again, PROPS OFF,
    # and take it back out afterwards.
    ESP_PLATFORM=1
)

# UAVObjectsInitializeAll() wraps EVERY call in #ifdef UAVOBJ_INIT_<name>.
# The Make-based targets get these from their UAVObjects.inc; without them the
# function compiles to an EMPTY BODY. That links and runs perfectly quietly
# while leaving the object system half-built -- only the objects some module
# happens to reference directly ever get initialised (36 of 111 here). Not a
# subtle degradation either: the event dispatcher then walks a periodic list
# referring to uninitialised objects and dies on a null pointer.
#
# The list is deliberately the CopterControl set, NOT all 111. Initialising
# everything makes telemetry stream every object at its default period,
# which saturates a 57600 link -- object REQUESTS then queue behind seconds
# of backlog and never appear to be answered. Keep this slim.
#
# Keep this list in step with UAVO_SYNTH_SRCS above.
target_compile_definitions(${COMPONENT_LIB} PRIVATE
    UAVOBJ_INIT_accelgyrosettings=1
    UAVOBJ_INIT_flipstatus=1
    UAVOBJ_INIT_remoteidsettings=1
    UAVOBJ_INIT_remoteidstatus=1
    ODID_AUTH_MAX_PAGES=1
    UAVOBJ_INIT_accelstate=1
    UAVOBJ_INIT_accessorydesired=1
    UAVOBJ_INIT_actuatorcommand=1
    UAVOBJ_INIT_actuatordesired=1
    UAVOBJ_INIT_actuatorsettings=1
    UAVOBJ_INIT_attitudesettings=1
    UAVOBJ_INIT_attitudestate=1
    UAVOBJ_INIT_callbackinfo=1
    UAVOBJ_INIT_faultsettings=1
    UAVOBJ_INIT_firmwareiapobj=1
    UAVOBJ_INIT_settingsgeneration=1
    UAVOBJ_INIT_flightmodesettings=1
    UAVOBJ_INIT_flightstatus=1
    UAVOBJ_INIT_flighttelemetrystats=1
    UAVOBJ_INIT_gcsreceiver=1
    UAVOBJ_INIT_gcstelemetrystats=1
    UAVOBJ_INIT_gpspositionsensor=1
    UAVOBJ_INIT_gpssettings=1
    UAVOBJ_INIT_gpsvelocitysensor=1
    UAVOBJ_INIT_gyrostate=1
    UAVOBJ_INIT_hwsettings=1
    UAVOBJ_INIT_i2cstats=1
    UAVOBJ_INIT_manualcontrolcommand=1
    UAVOBJ_INIT_manualcontrolsettings=1
    UAVOBJ_INIT_mixersettings=1
    UAVOBJ_INIT_mixerstatus=1
    UAVOBJ_INIT_mpu6000settings=1
    UAVOBJ_INIT_objectpersistence=1
    UAVOBJ_INIT_perfcounter=1
    UAVOBJ_INIT_ratedesired=1
    UAVOBJ_INIT_receiveractivity=1
    UAVOBJ_INIT_relaytuning=1
    UAVOBJ_INIT_relaytuningsettings=1
    UAVOBJ_INIT_stabilizationbank=1
    UAVOBJ_INIT_stabilizationdesired=1
    UAVOBJ_INIT_stabilizationsettings=1
    UAVOBJ_INIT_stabilizationsettingsbank1=1
    UAVOBJ_INIT_stabilizationsettingsbank2=1
    UAVOBJ_INIT_stabilizationsettingsbank3=1
    UAVOBJ_INIT_stabilizationstatus=1
    UAVOBJ_INIT_systemalarms=1
    UAVOBJ_INIT_systemsettings=1
    UAVOBJ_INIT_systemstats=1
    UAVOBJ_INIT_takeofflocation=1
    UAVOBJ_INIT_positionstate=1
    UAVOBJ_INIT_vtolpathfollowersettings=1
    UAVOBJ_INIT_vtolselftuningstats=1
    # ^ compiled all along but never initialized, so PositionStateHandle()
    # returned NULL -- and takeOffLocationHandler dereferenced it at the
    # moment of arming, taking down the whole object system. An object that
    # is in the build MUST be in this list.
    UAVOBJ_INIT_taskinfo=1
    UAVOBJ_INIT_txpidsettings=1
    UAVOBJ_INIT_watchdogstatus=1
)

# UAVObjectsInitializeAll() wraps EVERY call in #ifdef UAVOBJ_INIT_<name>.
# The Make-based targets get these from their UAVObjects.inc; without them
# the function compiles to an EMPTY BODY, which links and runs perfectly
# quietly while leaving the object system half-built -- only the objects some
# module happened to reference directly ever get initialised (36 of 0 here).
# That is not a subtle degradation: the event dispatcher then walks a periodic
# list referring to uninitialised objects and dies on a null pointer.
#
# Keep this list in step with UAVO_SYNTH_SRCS above.
target_compile_definitions(${COMPONENT_LIB} PRIVATE
    UAVOBJ_INIT_accelgyrosettings=1
    UAVOBJ_INIT_flipstatus=1
    UAVOBJ_INIT_remoteidsettings=1
    UAVOBJ_INIT_remoteidstatus=1
    ODID_AUTH_MAX_PAGES=1
    UAVOBJ_INIT_accelstate=1
    UAVOBJ_INIT_accessorydesired=1
    UAVOBJ_INIT_actuatorcommand=1
    UAVOBJ_INIT_actuatordesired=1
    UAVOBJ_INIT_actuatorsettings=1
    UAVOBJ_INIT_attitudesettings=1
    UAVOBJ_INIT_attitudestate=1
    UAVOBJ_INIT_callbackinfo=1
    UAVOBJ_INIT_faultsettings=1
    UAVOBJ_INIT_firmwareiapobj=1
    UAVOBJ_INIT_settingsgeneration=1
    UAVOBJ_INIT_flightmodesettings=1
    UAVOBJ_INIT_flightstatus=1
    UAVOBJ_INIT_flighttelemetrystats=1
    UAVOBJ_INIT_gcsreceiver=1
    UAVOBJ_INIT_gcstelemetrystats=1
    UAVOBJ_INIT_gpspositionsensor=1
    UAVOBJ_INIT_gpssettings=1
    UAVOBJ_INIT_gpsvelocitysensor=1
    UAVOBJ_INIT_gyrostate=1
    UAVOBJ_INIT_hwsettings=1
    UAVOBJ_INIT_i2cstats=1
    UAVOBJ_INIT_manualcontrolcommand=1
    UAVOBJ_INIT_manualcontrolsettings=1
    UAVOBJ_INIT_mixersettings=1
    UAVOBJ_INIT_mixerstatus=1
    UAVOBJ_INIT_mpu6000settings=1
    UAVOBJ_INIT_objectpersistence=1
    UAVOBJ_INIT_perfcounter=1
    UAVOBJ_INIT_ratedesired=1
    UAVOBJ_INIT_receiveractivity=1
    UAVOBJ_INIT_relaytuning=1
    UAVOBJ_INIT_relaytuningsettings=1
    UAVOBJ_INIT_stabilizationbank=1
    UAVOBJ_INIT_stabilizationdesired=1
    UAVOBJ_INIT_stabilizationsettings=1
    UAVOBJ_INIT_stabilizationsettingsbank1=1
    UAVOBJ_INIT_stabilizationsettingsbank2=1
    UAVOBJ_INIT_stabilizationsettingsbank3=1
    UAVOBJ_INIT_stabilizationstatus=1
    UAVOBJ_INIT_systemalarms=1
    UAVOBJ_INIT_systemsettings=1
    UAVOBJ_INIT_systemstats=1
    UAVOBJ_INIT_takeofflocation=1
    UAVOBJ_INIT_positionstate=1
    UAVOBJ_INIT_vtolpathfollowersettings=1
    UAVOBJ_INIT_vtolselftuningstats=1
    # ^ compiled all along but never initialized, so PositionStateHandle()
    # returned NULL -- and takeOffLocationHandler dereferenced it at the
    # moment of arming, taking down the whole object system. An object that
    # is in the build MUST be in this list.
    UAVOBJ_INIT_taskinfo=1
    UAVOBJ_INIT_txpidsettings=1
    UAVOBJ_INIT_watchdogstatus=1
)

# -fsingle-precision-constant matters here: the complementary filter and the
# rate PIDs are all float32, and without this every literal promotes to double
# and lands in software emulation on a part whose FPU is single-precision only.
target_compile_options(${COMPONENT_LIB} PRIVATE
    -fsingle-precision-constant
    -Wno-unused-parameter
    # GCC 13 false positive on the float[4] quaternion helpers
    # (quat_mult in outerloop.c). Keep the warning, drop the -Werror.
    -Wno-error=stringop-overread
    -Wno-error=stringop-overflow
    -Wno-error=array-bounds
)

