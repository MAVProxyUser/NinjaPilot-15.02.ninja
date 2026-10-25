# Working on OpenPilotESP32

Rules and traps for this port. Every entry below cost real bench time to find.

## STATUS 2026-09-02: the quad HOVERED on this firmware

First successful hover of the 4-inch QuadX on the ESP32 Thing Plus. The
settled recipe, in the order the problems were found (each one masked the
next):
1. `AttitudeSettings.BoardRotation = (0,0,180)` - the IMU's +x points at the
   tail. This was the 2026-09-01 flip cause. Verified with
   `tools/orientation_check.py`, enforced by flight_monitor preflight.
2. Power up still for 10 s; arm on the ground, hands off - the CC estimator
   learns gyro bias during the arming second (ZeroDuringArming).
3. Idle low enough that four equal idle thrusts cannot lift the light end
   (battery sits aft: a 1168 us idle pitched it nose-up over its own tail
   at zero throttle, where the FC applies no stabilization).
4. 41 Hz DLPF, Rate yaw, MotorsSpinWhileArmed, 4-inch-class Bank1 defaults.
Preflight GO from `tools/flight_monitor.py` before every flight; it pulls the
objects behind any alarm that goes up. Bench: `tools/bench_test.py --quick`.

## HARD RULE: flight battery and USB are mutually exclusive

On the Thing Plus the ESC/BEC 5 V line feeds VUSB. Never design, suggest or
run a procedure that has both connected. Anything needing powered motors
(RF motor calibration, wizard ESC/output calibration) runs on battery with
the GCS over WiFi; anything on USB runs with motors unpowered. The GCS
wizard enforces this by skipping the battery-powered pages whenever its own
link is USB serial.

## RULE: the serial port belongs to one process, and opening it reboots the board

`/dev/cu.usbserial-210` — one holder at a time; a second opener sees "no
link" and blames the tool. Every classic open toggles DTR/RTS and resets
the chip, and for ~2.5 s after boot CPUOverload/Actuator alarms sit
Critical and block arming. Coordinate before touching the port; values read
in the first seconds after connect are early-boot state, not steady state.

## The xTaskCreate shim: stack words x4, pinned to core 1

`pios/esp32/pios_esp32.h` converts every shared-module `xTaskCreate()` from
FreeRTOS stack WORDS to IDF's bytes with an explicit `* 4` — NOT
`sizeof(StackType_t)`, which is 1 on this Xtensa port and turns the fix
into a silent no-op — and pins the task to core 1, so flight code and the
WiFi/lwIP stack (core 0) are separated by silicon. Code that genuinely
wants core 0, byte-sized stacks, or no pinning calls
`(xTaskCreatePinnedToCore)(...)` with parentheses to bypass the macro.

## RULE: a new board id must tour the GCS's board tables

The GCS gates features on getBoardModel() in about a dozen places, and
every one of them fails SILENTLY for an unknown id: the Attitude config
tab vanished, the Output page showed dead bank dropdowns, the board name
was blank -- each discovered one user complaint at a time until a full
grep of getBoardModel() closed the rest. If a board id ever changes or a
new target appears, audit every call site in one pass instead.

## RULE: on a flip at liftoff, check BOARD ORIENTATION against the airframe FIRST

The 2026-09-01 flips were called wrong FOUR times (flight mode, mixer
geometry, prop strike, then "vibration through the 176 Hz DLPF") before a
five-second physical check settled it: tip the airframe's real nose down
and read what the board says. It said NOSE UP. The IMU's +x points at the
tail (BoardRotation Yaw=180 is the fix, see README). Every board-frame
consistency check - estimate vs gyro, estimate vs accel, mixer vs estimate,
"controller commanded the correct recovery" - PASSES on a backwards board,
because all of them live in the board's own frame; the 9-degree
estimate/accel gap in the crash log was the complementary filter lagging a
fast forced rotation, a symptom. Only a human reference reveals a frame
offset, and it must be an unambiguous one: the first bench run's
voice-lagged labels read the inversion backwards. Use
`tools/orientation_check.py` (five asks, Enter-confirmed) after any
board/IMU rework and before the first hover; `bench_test.py` gates arming
on it. Second: estimate-vs-accel through the event (still a real class of
fault). Corollary: the sim exonerates only the CONTROL code - its sensors
are synthetic and its frame is by construction aligned.

Third: a constant gyro mean of tens of deg/s with an accelerometer that reads
gravity correctly is LEARNED BIAS, not motion and not vibration. The CC
estimator zeroes gyros with a 0.2 s time constant for ~7 s after power-up and
during the arming second (ZeroDuringArming). Any tool that arms must first
wait for a quiet gyro and re-check the bias after arming (bench_test does).

## Remote ID: a broadcast is not compliance

`flight/modules/RemoteID` broadcasts ASTM F3411 correctly (verified against
the reference encoder on the sim twin). Do not describe it as FAA-compliant:
this airframe has no GPS, so Location is "unknown", and a home-built
transmitter has no Declaration of Compliance. Say "standards-shaped, completes
when a GPS is on UART2". Never invent a position. Traps that already bit:
IDF's early script-mode pass rejects set_source_files_properties at the top
of a component CMakeLists (put it after idf_component_register, guarded by
NOT CMAKE_BUILD_EARLY_EXPANSION); the vendored encoder's debug printf needs
-Wno-format on Xtensa; the library's operator-ID enum is ODID_OPERATOR_ID.
New UAVOs = new UAVO-set hash = GCS resync (recipe in memory).

## ESC range calibration cannot exist on this board -- do not reintroduce it

The procedure requires the controller alive and holding max throttle
BEFORE the ESCs first see power. Stock boards run the FC from USB while
the battery waits -- here that is the forbidden dual-supply state -- and
on battery alone the controller and ESCs power up together, so the ESC
calibration window closes before WiFi telemetry returns. The wizard page
is removed from the ESP32 flow deliberately. BOARD_ESC_CAL (a boot mode
holding max-then-min from power-up) is the supported way; the RF
switch-wiggle calibration was retired in favor of the wizard's output
calibration and lives in git history.

## SMP timing: measured-flat levers — do not re-try without new information

- **QIO flash is ALREADY ACTIVE.** The ROM banner prints "mode:DIO"
  because the image header must be DIO for the ROM; the second-stage
  bootloader upgrades to QIO at runtime (bootloader_enable_qio_mode is in
  the bootloader map). A session was nearly spent "enabling" it.
- **LWIP_IRAM_OPTIMIZATION + SPI_MASTER_IN_IRAM: no measurable effect.**
  3x60s A/B against known-good on the bench-idle stab-warning metric:
  means 9.0 vs 7.0 per minute, spreads 5-14 -- inside run noise.
  Reverted. If IRAM placement is ever revisited, bring a finer metric
  than alarm transitions (the DR-gap counters from the git history).

## SMP timing: ~4 ms whole-scheduler stalls are characterized — and bisects here LIE

lwIP timer work on core 0 meets flight tasks through the SMP global kernel
lock: ~2 stalls/s idle, ~4/s with a TCP telemetry client, each ~3.6 ms.
Tolerated by design (sensor queue + a 5-period attitude timeout), not
eliminated. If you chase timing on this platform: binary layout and AP
radio conditions are hidden variables strong enough to flip a bisect
verdict on EQUIVALENT code — verified-clean and verified-dirty runs of the
same logic both happened in one session. Re-verify any verdict across
reboots AND rebuilds, measure via a UDP side-channel so the flight stack
can be stripped, and remember the GPIO ISR service lands on core 0 no
matter which core installs it (the driver IPCs the install to the core
that first configured a pin).

## RULE: do not modify the NinjaPilot tree in place

This project is deliberately separate. It consumes the NinjaPilot flight code
and must leave that checkout clean. The changes a HAL port cannot avoid live in
`patches/ninjapilot-shared-changes.patch`, applied and reverted with the
scripts in `tools/`.

If you need another upstream change, add it to the patch — do not edit the
flight tree and leave it dirty. The user watches that tree.

## The chip has NO USB peripheral

The original ESP32 (D0WD-V3) has no USB controller — that arrived with the S3.
The USB socket on a WROOM-32 devkit is a CP2102/CH340 **USB-to-UART bridge**.

So there is no USB HID, no USB CDC, and no `PIOS_INCLUDE_USB` on this target.
"UAVTalk over USB" here means UAVTalk over UART0 through that bridge, which is
exactly what the GCS and `ground/pyuavtalk/` talk to. This is silicon, not
configuration — do not go looking for a HID option to enable.

## RULE: the IDF console stays OFF UART0

`sdkconfig.defaults` moves it to UART1 on GPIO22 (TX) / GPIO23 (RX), 57600. Do not move it back except as a
deliberate, temporary debugging step (see SKILL.md).

**Why:** UART0 carries UAVTalk. With the console sharing it, log text
interleaves into the middle of UAVTalk frames. The receiver reports
`failed CRC check` in a loop and the GCS never links. `pyuavtalk` hides this —
it silently drops bad frames and limps along — so the symptom presents as
*flaky request/reply* rather than corruption. The GCS is stricter and simply
shows NO LINK.

## RULE: PIOS_MPU6000_Register() is called UNCONDITIONALLY

Even when no IMU answered. This looks wrong and has already been "fixed" once,
which broke the board.

**Why:** `Register()` publishes the PIOS_SENSORS instance the sensor consumers
wait on. Skip it and module init hangs before telemetry ever starts — the board
looks completely dead, with no console output and no core dump. Report the
missing IMU with `SYSTEMALARMS_ALARM_BOOTFAULT` (visible over UAVTalk) and let
the board boot. A board that comes up, says what is wrong and refuses to arm is
far more useful than one that silently wedges.

## Every stack size in this tree is sized for a Cortex-M3

They are too small on Xtensa — the windowed ABI spills register windows to the
stack and IDF's printf/driver layers are far hungrier than the STM32
equivalents. See the `PIOS_*_STACK_SIZE` block in `pios_board.h`.

**The failure mode is the problem:** these do NOT report as stack overflows.
They corrupt the heap or the scheduler ready-list and crash somewhere
unrelated. Telemetry at 3072 bytes corrupted the *event dispatcher's* periodic
object list; Attitude's hardcoded 540 crashed inside `vTaskSwitchContext`.

**How to find one:** comment modules out of `firmware/InitMods.c` down to none,
confirm the board is stable, then add them back one at a time. Do not guess.

## Two DTR/RTS traps

On these adapters DTR and RTS are wired to EN/RESET and GPIO0 — that is how
esptool reboots the chip. Both pyserial and Qt's QSerialPort **assert them when
they open a port**, which holds the ESP32 in reset.

Symptom: zero bytes at every baud while esptool still talks to the chip
perfectly. Already fixed in `ground/pyuavtalk/uavtalk_client.py`
(`SerialTransport`) and in the GCS `serialconnection` plugin. If you write new
tooling, deassert both after opening.

## PIOS_Assert() is a SILENT infinite spin

`DEBUG` is not defined for this target, so `PIOS_Assert(x)` expands to
`if (!(x)) { while (1) {;} }` — no message, no core dump, no reset. It is
indistinguishable from a dead board.

When bisecting a hang, remember an assert is a candidate even though nothing
was printed. `PIOS_DEBUG_Panic()` is the loud alternative, but note it aborts
and reboots, which turns a wedge into a boot loop — pick deliberately.

## Things that must not drift

- **`BOARD_REVISION` must stay `0x02`.** `modules/Attitude/attitude.c` derives
  its sensor path from `BOARDISCC3D (bdinfo->board_rev == 0x02)`. Anything else
  selects the CopterControl analog-gyro + ADXL345 path, which this board does
  not have. It compiles fine and then never produces a sample.
- **`UAVOBJ_INIT_*` must be defined** for every object you want initialised
  (see `esp-idf/main/CMakeLists.txt`). `UAVObjectsInitializeAll()` wraps every
  call in `#ifdef UAVOBJ_INIT_<name>`; with none defined it is an EMPTY
  FUNCTION that links and runs silently. Keep the list slim — initialising all
  111 objects makes telemetry stream everything and saturates a 57600 link.
- **`esp-idf/main/uavo_handles.ld` is load-bearing.** Read its header before
  touching it: the section must be writable *and* keep its name, and the two
  obvious fixes each break one of those.

## Sensor data-ready runs in a TASK, not an ISR

`pios/esp32/pios_exti.c`. Two independent reasons, both hard:

- IDF's `spi_device_polling_transmit()` is not ISR-safe, and the MPU6000
  data-ready handler reads the sensor over SPI.
- The Xtensa FPU is unusable in an ISR — IDF does not save/restore FPU context
  there — and `PIOS_MPU6000_HandleData()` does float math on that exact path.

This is why `pios/common/pios_mpu6000.c` is used unmodified.

## The simwroom simulation twin: traps that already bit once

`flight/targets/boards/simwroom/` (carried in the shared patch) is the posix
twin of this board. Rules learned building it:

- **`BOARD := SIM_POSIX`, never SIM_WROOM.** The build defines
  `USE_$(BOARD)` and pios.h keys the whole POSIX-vs-STM32 architecture
  selection off `USE_SIM_POSIX`; renaming BOARD silently drops the target
  into the STM32 include path (realposix's board-info.mk documents the same
  trap). BOARD names the ARCHITECTURE; `PIOS_SIMWROOM` in pios_config.h
  names the variant. Board identity (0x1202) comes from
  BOARD_TYPE/BOARD_REVISION, which are independent of BOARD.
- **Every `.c` in flight/pios/posix/ compiles into EVERY posix target** —
  library.mk does `SRC += $(wildcard $(PIOS_DEVLIB)*.c)`. A new posix driver
  must guard its whole body (`#ifdef PIOS_INCLUDE_ICM20602`) or it breaks
  simposix/realposix.
- **The sensor registry is not in the posix wildcard.** `PIOS_SENSORS_Register`
  lives in `flight/pios/common/pios_sensors.c`; the simwroom Makefile adds it
  explicitly, same as the ESP32 CMake build does.
- **The patch is regenerated against a BASE COMMIT, not the index** (changed
  2026-09-02):

  ```bash
  cd /path/to/NinjaPilot-15.02.ninja
  git diff ed51f146d2cfff2622c6c24567ed0b02d52e595d -- . ':(exclude)**/__pycache__/**' \
      > /path/to/OpenPilotESP32/patches/ninjapilot-shared-changes.patch
  ```

  It used to be `git diff > patch; git diff --cached >> patch`, which read
  only UNCOMMITTED state. That worked while every shared change sat staged or
  modified, and it is why new files had to be `git add`ed but never committed.
  The moment any of that work was committed on the `claude` branch the two
  diffs went empty for those files and the patch silently SHED them -- measured:
  83 files before the commit, 48 after, with simwroom, Flip and Remote ID
  simply gone. A patch that quietly loses a board target is worse than one
  that fails loudly.

  `ed51f14` is the anchor: NinjaPilot as it stood before that work was
  committed. It does not move. Anything committed after it is still captured,
  so work may now be committed on `claude` freely.

  Exclude `__pycache__`: a tracked `.pyc` in that tree lands in the patch as a
  binary hunk and makes `git apply` fail with "cannot apply binary patch
  without full index line".

  Verify a regenerated patch before trusting it:
  `git apply --check -R patches/ninjapilot-shared-changes.patch` from the
  NinjaPilot checkout. Clean reverse-apply means the patch matches the tree.
- The twin advertises the REAL scale factors (±2000 dps → 1/16.4, ±8 g →
  g/4096). If board_hw_defs.c ever changes the configured ranges, change
  `pios_icm20602_sim.c` to match — the pair drifting apart silently skews
  every sim-vs-hardware comparison.

## Do not try to build realposix here

It needs `linux/can.h` and `sys/prctl.h` — SocketCAN, Linux-only by design.
That is why `make gcs` cannot work on macOS (it depends on OPFW_RESOURCE, which
builds all firmware). See SKILL.md for the way around it.

## SETTLED: the HwSettings NACK was the linker-section object registry

`UAVObjGetByID()` returned NULL for a compiled, linked, correctly-initialised
object because the linker-section iteration the object manager relies on is
not dependable under this toolchain. The flight patch gives the object
manager an explicit `USE_ESP32` registration array instead, plus NULL guards
in the Get/Set entry points. If an object ever NACKs again, suspect a
missing `UAVOBJ_INIT_<name>` define first (see the list in
`esp-idf/main/CMakeLists.txt`) — an uninitialised object produces exactly
the same symptom.

## Board identity for the GCS is set in pios_board.c, not a module

The Setup Wizard identifies the board through `FirmwareIAPObj`
(type 0x12 << 8 | rev 0x02 = model 0x1202). The stock FirmwareIAP module is
bootloader plumbing this target has no use for, so `pios_board.c` populates
the identity fields directly after object init. Remove that and the wizard
shows "<Unknown>" and refuses to advance on every transport.
