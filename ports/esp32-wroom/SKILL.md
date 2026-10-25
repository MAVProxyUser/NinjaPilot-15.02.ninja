# SKILL.md - operational recipes for the ESP32 port

Paths below assume this repo sits beside the NinjaPilot checkout. Everything
is verified on macOS arm64 with ESP-IDF v5.3.2 at `~/esp/esp-idf`.

## RULE: the flight tree only carries the patch while you are building

```bash
tools/apply-ninjapilot-patch.sh    # before building
tools/revert-ninjapilot-patch.sh   # when you are done
```

The flashed board keeps working either way — reverting only affects the source
tree, not the device.

## Toolchain

```bash
git clone -b v5.3.2 --depth 1 --recursive --shallow-submodules https://github.com/espressif/esp-idf.git ~/esp/esp-idf && ~/esp/esp-idf/install.sh esp32
```

Source it per shell with `. ~/esp/esp-idf/export.sh`. Do **not** pipe that —
`. export.sh | tail` runs it in a subshell and the PATH never lands.

It also **exits non-zero on this machine** -- the same Python dependency check
that breaks `idf.py` (see below) leaves `$?` at 1 even though the toolchain is
on PATH and everything works. So separate it with `;`, never `&&`:

```bash
. ~/esp/esp-idf/export.sh >/dev/null 2>&1; ninja -C build
```

Chained with `&&` the build is silently skipped and you sit there reading stale
output from the previous run wondering why your change did nothing.

## Generate the UAVObjects (once, and after any XML change)

The CMake source list references generated sources that live in the NinjaPilot
tree. Its Makefile cannot handle a space in the path, so go through a symlink:

```bash
ln -sfn "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja" /tmp/njp && cd /tmp/njp && make ROOT_DIR=$PWD uavobjects_flight
```

## Build

`idf.py` runs a Python dependency check that misresolves the dotted
`ruamel.yaml.clib` distribution on this machine, so drive cmake directly and
pass `-DPYTHON_DEPS_CHECKED=1`. It is a false alarm about the checker; nothing
the compiler needs is missing.

```bash
cd targets/esp32wroom/esp-idf && . ~/esp/esp-idf/export.sh && cmake -G Ninja -B build -DIDF_TARGET=esp32 -DSDKCONFIG_DEFAULTS=sdkconfig.defaults -DPYTHON_DEPS_CHECKED=1 . && ninja -C build
```

Point at a checkout elsewhere with `-DNINJAPILOT_ROOT=/path/to/NinjaPilot-15.02.ninja`.

## Flash

```bash
cd targets/esp32wroom/esp-idf/build && . ~/esp/esp-idf/export.sh && python -m esptool --chip esp32 --port /dev/cu.usbserial-210 -b 115200 --before default_reset --after hard_reset write_flash @flash_args
```

460800 is unreliable on this adapter — it fails with "Invalid head of packet".
115200 takes about 16 seconds for the app.

App-only flash of the PREBUILT images in the repo root (bootloader and
partition table already on the board):

```bash
. ~/esp/esp-idf/export.sh
python -m esptool --chip esp32 --port /dev/cu.usbserial-210 -b 115200     --before default_reset --after hard_reset write_flash 0x10000 firmware_normal_41hz.bin
```

`firmware_normal_41hz.bin` is the flight build (41Hz DLPF vibration fix +
all 2026-09-01 defaults); `firmware_esc_cal.bin` is the ESC-calibration
power-up variant — see the ESC calibration section below, and never fly it.

## ESC calibration (USB-free — the only way on this board)

ESCs enter calibration only if they see max throttle at THEIR power-on.
On this airframe ESC power IS board power (BEC 5V feeds VUSB, battery and
USB must never be connected together), and WiFi takes 3-8s to associate —
far longer than the ESC listening window. So no wizard page, no serial
tool, no WiFi-commanded calibration can ever work here; the firmware does
the ritual itself at boot. PROPS OFF THROUGHOUT.

1. Battery disconnected, USB in — flash `firmware_esc_cal.bin` (recipe
   above, same command with the other filename).
2. UNPLUG USB. Connect battery. Board and ESCs power up together with all
   four outputs already at MAX — every ESC enters calibration and sings
   the high tone. After 6 seconds the outputs drop to MIN; the ESCs chirp
   the confirm and store the range. LED: solid during MAX, fast blink
   during MIN.
3. Battery off. USB back in — flash `firmware_normal_41hz.bin`.
4. In the GCS: set all four ActuatorSettings.ChannelNeutral values EQUAL
   (one just-above-spool number now fits all four — the by-ear per-channel
   spread this replaces is what left one corner weak at idle), confirm
   MotorsSpinWhileArmed=TRUE and Yaw=Rate on the flight slot, save.

Every power-up of the cal build recalibrates — never leave it flashed.

## Voice-guided bench test (props OFF)

```bash
python3 tools/bench_test.py            # board on battery, GCS closed
python3 tools/orientation_check.py     # read-only: tip the REAL nose down -> must print NOSE DOWN
python3 tools/bench_test.py --paced    # preferred: YOU press Enter to start each phase
python3 tools/bench_test.py --quick    # ~1 min: one cycle at 15%, SAYS which motor pair rose per tilt
python3 tools/bench_report.py ~/NinjaPilot-logs/bench_<stamp>.jsonl   # offline deep pass
```

STILLNESS. The CC estimator learns gyro bias with a 0.2 s time constant during
the first ~7 s after power-up AND during the arming second (ZeroDuringArming is
TRUE here). Whatever rate the quad has then becomes "bias" for the session:
the 01:28 bench armed two seconds after the left-arm dip and learned gyro.x
-54 deg/s; the roll estimate wandered past 90 deg while the accel read the
truth. Power up with the quad sitting still for 10 s; bench_test asks you to place
the quad flat on the bench and press Enter, then arms hands-off. bench_test waits for a quiet gyro, checks
the resting bias before AND after arming (limit 4 deg/s) and disarms if it
learned one; flight_monitor preflight fails on a biased gyro and shouts if a
bias appears after any arming.

ORIENTATION FIRST. The 2026-09-02 00:59 paced run read every commanded tilt
with the opposite sign on both axes while the 23:54 run read them right - the
board did not change, the hands did. `orientation_check.py` prints what the
board believes several times a second: hold the airframe's real nose down and
it must say NOSE DOWN; dip the left arm and it must say LEFT SIDE DOWN. If it
says the opposite the board is mounted 180 deg from the airframe (positive
feedback on both axes on a correct mixer - flips at liftoff): fix the mount or
set AttitudeSettings.BoardRotation Yaw=180 and save. bench_test now runs this
as a gate before arming and refuses if it fails. CONFIRMED 2026-09-02 on this
quad: both axes inverted -> `python3 tools/apply_recommended_settings.py
--board-rotation 0,0,180`, power cycle, re-check. This was the flip cause.

`--paced` steps the throttle 15/35/55/75/max % and, for every phase, speaks
"Next: <move>. Press Enter when you are there." - the window is sampled only
after your Enter, so labels can neither lead nor lag your hands and the
still windows are truly still (clean vibration-per-throttle numbers). The
timed ramp (no flag) remains for hands-off runs.

Radio on or off does not matter: the tool parks every non-GCS channel group
(Collective, Accessory0-2) on None for the run. It used to leave them on DSM,
and receiver.c range-checks any group that is not None, so a transmitter
that was off returned TIMEOUT on an Accessory and invalidated the whole
input (Connected=False, Receiver=Warning) - the 2026-09-01 23:4x abort.
Row labels come from when each prompt was actually spoken plus 1 s, so a
slow `say` queue cannot mislabel your hands (the 23:54 log graded a good
estimator FAIL on two axes purely from label lag; bench_report.py
re-aligns older logs automatically).

REQUIRES firmware built 2026-09-01 20:18 or later (firmware_normal_41hz.bin):
earlier builds never bound the GCS receiver as an input source, so a UDP
client could not drive the throttle - the board simply would not arm or
output PWM. The tool now VERIFIES arming from FlightStatus and aborts with
the blocking reason (throttle not reaching the flight side, an alarm, or an
unconfigured mixer) rather than assuming it worked.

The tool drives, you hold the quad and follow the spoken prompts (macOS
`say`): it applies the recommended settings (persisted), temporarily
takes control (GCS receiver mapping + Always Armed, RAM ONLY - a power
cycle restores DSM unconditionally), announces arming, ramps throttle
0->90% over ~100s while directing labeled motions (nose down / nose up /
roll left / roll right / hold still with a countdown), then announces
disarm and restores the radio. Grades printed at the end: per-stimulus
estimate signs, mixer response direction (does the dropped side's motor
pair rise), gyro-vs-estimate and accel-vs-estimate correlations (the
flip signature, live), and vibration per throttle band from the
hold-still windows. Motors spin from the moment of arming - PROPS OFF,
and expect them to scream at the high end of the ramp. Ctrl+C at any
time = safe shutdown + restore. Full record lands in
~/NinjaPilot-logs/bench_*.jsonl.

## Parts and wiring

See `BOM.md`: every part on the airframe that hovered, pin-by-pin wiring,
the power rule, IMU orientation, and the settings table.

## Remote ID (ASTM F3411 over WiFi beacon)

```bash
python3 tools/remoteid_setup.py --id-type CAARegistrationID --uas-id FA3xxx --operator-id FA3xxx --self-id "text" --enable
python3 tools/remoteid_setup.py --status
python3 tools/remoteid_listen.py           # sim twin: decode UDP :9020 packs
python3 tools/remoteid_listen.py --hex DD..  # decode a captured element
```

Module `flight/modules/RemoteID`, encoder `flight/libraries/opendroneid`
(vendored, Apache-2.0; the ESP32 build exempts it from -Werror=format after
`idf_component_register` - IDF's early script pass rejects
set_source_files_properties). Transmitter `pios/esp32/pios_rid_wifi.c`
(APSTA soft-AP `RID-xxxxxx`, vendor element via esp_wifi_set_vendor_ie);
sim `flight/pios/posix/pios_rid_sim.c` (UDP :9020, `PIOS_INCLUDE_RID_SIM`).
Objects RemoteIDSettings / RemoteIDStatus (GCS resynced, hash e60dc1f0).
Sim self-test: fresh dir, start fw_simwroom, `remoteid_listen.py --count 3 &`,
`remoteid_setup.py --host 127.0.0.1 ... --enable` -> 5-message v2 pack decodes.
Not compliant Remote ID without a GPS (Location = unknown) - see README.

## Monitor a real flight

```bash
python3 tools/flight_monitor.py            # board at 192.168.0.45:9000
# any alarm that goes up pulls its context objects (Attitude -> AttitudeState/GyroState/AccelState/
# AttitudeSettings, Receiver -> ManualControlCommand/..., see ALARM_CONTEXT) at once and every 5 s: CTX lines + jsonl
```

Close/disconnect the GCS first (one UAVTalk client at a time). On connect
it runs a PREFLIGHT: reads the board's actual configuration over UAVTalk
and prints a GO/NO-GO checklist - firmware currency (build stamp or UAVO-set
hash), board identity, QuadX mixer table, throttle curve, neutral symmetry,
spin-while-armed, Stabilized1-3 mode arrays, Bank1 gain sanity, receiver
mapping, board rotation (Yaw MUST be 180 on this frame), Error/Critical
alarms (BootFault here = IMU gave no WHO_AM_I at boot), resting gyro bias
and a live gyro stream, airframe type. A FAIL means do not fly. After any
arming it averages the resting gyro for 2 s and shouts GYRO BIAS if the quad
moved during the arming second.

The sequence that hovered (2026-09-02): battery in with the quad sitting
still, hands off 10 s -> start the monitor, wait for GO -> arm on the
ground, do not touch it until the motors idle -> throttle up gently. Idle
must not lift the light end (rear battery): at 1168 us it tipped nose-up
over its own tail at zero throttle, where the FC applies no stabilization. Then the 1Hz status
line: arm state, mode, attitude, throttle, all four motor PWMs, alarms,
packet rate; instant events for arming, mode and alarm transitions, and
STALL warnings on >1s telemetry gaps. Everything received is recorded to
`~/NinjaPilot-logs/flightmon_*.jsonl` (wall-stamped) for post-flight
forensics. Fly, land, Ctrl+C for the summary. It listens far more than it
sends (~7 single-frame polls/s, never back-to-back).

## Talk to the board

```bash
python3 tools/esp32_link_check.py --serial /dev/cu.usbserial-210 --baud 57600
```

Checks framing, handshake, an object read and an object write (restoring the
original value). For a live object dump instead:

```bash
python3 /tmp/njp/ground/pyuavtalk/uavtalk_client.py --serial /dev/cu.usbserial-210 --baud 57600 --duration 20
```

## RULE: deassert DTR/RTS before reading the port

They are wired to EN/RESET and GPIO0. pyserial asserts both on open, which
holds the ESP32 in reset — you get **zero bytes at every baud** while esptool
still talks to the chip fine. Any new tool needs:

```python
ser.dtr = False
ser.rts = False
```

`uavtalk_client.py`'s `SerialTransport` already does this.

## WiFi telemetry

Provision credentials offline (board unplugged from everything else; this
uses esptool through the serial port and reboots the chip):

```bash
python3 tools/wifi_setup.py set --ssid YourNetwork        # prompts for the password
python3 tools/wifi_setup.py check                          # waits for the discovery beacon
python3 tools/wifi_setup.py erase                          # before flying
```

On boot with stored credentials the board joins the network, serves UAVTalk
on port 9000 over BOTH TCP and UDP, and broadcasts `NINJAPILOT <ip> 9000`
on UDP :9999 every 2 s until a client connects. UART0 goes quiet — one
telemetry port at a time. Prefer UDP (GCS: Options -> IP connections,
uncheck "Use TCP"): a connected TCP client arms lwIP's 250 ms tcp fast
timer, which is this platform's residual scheduler-stall source. A UDP
peer claims the stream with its first datagram, KEEPS it until 3 s of
silence (later senders cannot steal an active stream — their requests
are processed but replies go to the holder), and releases fully after
10 s. Diagnostic scripts that need their own stream while a GCS is
connected should use TCP — knowing a TCP session preempts the UDP
telemetry for its duration and knocks the GCS into a brief reconnect.
The GCS Firmware-tab reboot and the wizard's post-save reboot work: the
firmware honors the IAP command sequence with a clean restart. Passwords with shell-special characters: let the getpass
prompt take them; quoting on the command line has already stored a literal
backslash once.

## RC and motor bring-up tools

All of these speak UAVTalk over serial or TCP and hold the port while
running (see the port rule in CLAUDE.md):

```bash
python3 tools/rc_monitor.py        # live channels, arming verdicts, alarm edges
python3 tools/rc_check.py --apply  # per-axis direction check, writes reversals
python3 tools/rc_calibrate.py      # endpoints + throttle neutral (min + 5%)
python3 tools/motor_watch.py       # commanded vs actual PWM while you arm and stick
python3 tools/setup_wizard.py      # orientation / level / USB-free config steps
```

Motor idle points are set from the GCS wizard's output-calibration page
over WiFi, on battery power with USB out. For true ESC range calibration
use the BOARD_ESC_CAL boot mode: flash it over USB with no battery,
unplug USB, connect the battery — the board boots straight into
max-for-6s-then-min inside the ESCs' calibration window. (The old RF
switch-wiggle calibration was retired once the wizard path existed; it
lives in git history if ever needed.)

## Run the simulation twin (fw_simwroom)

The posix twin of this board (same control stack, board id 0x1202 — see
README "Simulation twin"). Build in the NinjaPilot tree through the
space-free symlink, run from a scratch directory (the settings filesystem
writes slot files into the CWD):

```bash
ln -sfn "/path/to/NinjaPilot-15.02.ninja" /tmp/njp
cd /tmp/njp && make ROOT_DIR=$PWD fw_simwroom
mkdir -p /tmp/simwroom_cwd && cd /tmp/simwroom_cwd
/tmp/njp/build/fw_simwroom/fw_simwroom.elf     # UAVTalk on UDP :9000
```

The GCS connects to it over UDP 127.0.0.1:9000 exactly like the hardware
over WiFi — same screens, same pin labels, same version check. Sensor
input is GyroSensor/AccelSensor UAVObjects (what gazebo_bridge publishes);
without a feeder the attitude sits level and the Attitude alarm complains,
which is correct. Stdout is block-buffered when redirected — an empty log
from a killed process is buffering, not silence.

To FLY it in Gazebo (server must already be running; start it with the
`gz sim -s -r --headless-rendering worlds/quadcopter_ninjapilot.sdf` line
from run_gazebo_bridge.sh plus `gz sim -g` for the window):

```bash
cd /path/to/NinjaPilot-15.02.ninja/ground/gazebo_bridge
./run_wroom.sh <label> hover     # GPS-only hover, 4m / 30s
./run_wroom.sh <label> sticks    # scripted stick pokes, attitude tracking
./run_wroom.sh <label> rth       # 15m flyout, GPS-only return-to-home
./run_wroom.sh <label> flip      # backflip(s) from a 13m perch
```

`NINJAPILOT_WROOM_FLIPS=5` chains flips in one flight (recovery re-climbs
to the perch between them). `NINJAPILOT_FLIP_LAG` (default 0.25s) is the
stick-command latency the flip endgame predicts across - retune it if the
telemetry path's timing ever changes.

To FILM a flight (chase-cam mp4, GPU-rendered, no GUI needed - adapted
from the Cheetah port's record_video.py): start the run, then

```bash
./venv/bin/python3 tools/chase_cam.py /tmp/flight.mp4 95 5 0 0.8
```

(args: out, seconds, then camera offset east/north/up - due east sees a
backflip in full profile). It spawns a camera rig teleported along a
smoothed follow path via /world/.../set_pose, pipes frames to ffmpeg, and
refuses to record until vehicle poses are actually arriving - gz's
multicast discovery occasionally leaves a subscription silently unmatched,
and the symptom is 95 seconds of scenery. Rig names/topics are unique per
run because the create service AUTO-RENAMES duplicates instead of failing:
stale rigs otherwise pile up publishing onto a shared topic, and the
recorder pulls frames from a camera parked inside the barn.

Each run purges slots, resets the scene, flies, pulls the FC's own
DebugLog (the twin compiles the Logging module as a documented sim-only
deviation), writes a pilot track CSV to logs/, and renders the
planned-vs-flown picture. NINJAPILOT_WROOM_FEEDBACK=truth switches the
pilot loops to ground-truth feedback; the default is gps because that is
the question being asked. One UAVTalk client at a time, as always — no
GCS attached during a bridge flight.

## Run the GCS against the board

The GCS prefers UDP by default (that is the OSD32MP1 workflow). Override it:

```bash
NINJAPILOT_GCS_AUTOMATION=1 NINJAPILOT_GCS_PREFER="Serial: cu.usbserial-210" DYLD_FRAMEWORK_PATH=/opt/homebrew/opt/qt@5/lib /tmp/njp/build/openpilotgcs_release/bin/NinjaPilotGCS.app/Contents/MacOS/NinjaPilotGCS
```

Success looks like `Serial telemetry running at "57600"`, no `failed CRC check`
lines, and NO LINK clearing in the System Health panel.

Over WiFi instead: configure the IP connection (TCP, the board's IP, port
9000) in Options -> IP connections, pick `TCP: <ip>` in the Connections
dropdown, Connect. The Setup Wizard (Tools -> Vehicle Setup Wizard) detects
the board and adapts: input locked to the Spektrum satellite, Thing Plus
artwork in the connection diagram, and the battery-powered ESC/output
calibration pages offered only on a network link (with an unplug-USB
checkpoint), never over USB serial.

Drive it headlessly with `ground/pyuavtalk/gcs_client.py` (JSON on port 17654):
`ping`, `workspaces`, `find`, `get`, `do`, `menu`.

## Build the GCS on macOS

`make gcs` **cannot** work: it depends on `OPFW_RESOURCE`, which builds all
firmware, and `fw_realposix` needs `linux/can.h` (SocketCAN, Linux-only).

```bash
printf '<!DOCTYPE RCC><RCC version="1.0">\n    <qresource prefix="/firmware">\n    </qresource>\n</RCC>\n' > /tmp/njp/build/openpilotgcs-synthetics/opfw_resource.qrc
```

Then qmake the project directly:

```bash
cd /tmp/njp/build/openpilotgcs_release && /opt/homebrew/opt/qt@5/bin/qmake /tmp/njp/ground/openpilotgcs/openpilotgcs.pro -spec macx-clang -r CONFIG+=release && make -j8
```

`src/libs/utils/submiteditorwidget.moc` must exist in the source tree — GNU
make cannot express a target path containing a space, so the rule never fires
from "OP Revo Redux". Regenerate it by hand if it goes missing:
`moc submiteditorwidget.cpp -o submiteditorwidget.moc`.

## Debugging a board that says nothing

1. **Is it alive?** `python -m esptool --port /dev/cu.usbserial-210 chip_id`.
   If esptool syncs, the chip is fine and the problem is in the firmware.
2. **Temporarily put the console back on UART0** to see boot output. Delete the
   four `CONFIG_ESP_CONSOLE_UART_*` lines from `sdkconfig.defaults`, rebuild,
   flash. Remember UAVTalk is corrupted in that configuration — it is a
   diagnostic build, not a working one. Put them back afterwards.
3. **Read the core dump**, which survives a reset:
   `python -m esp_coredump --chip esp32 --port /dev/cu.usbserial-210 --baud 115200 info_corefile build/ninjapilot_esp32wroom.elf`
   A CRC error usually means the board is rebooting and rewriting it while you
   read; `should be ffffffff` means the partition is simply empty.
4. **Decode a backtrace** printed on the console:
   `xtensa-esp32-elf-addr2line -pfiaC -e build/ninjapilot_esp32wroom.elf 0x400... 0x400...`
5. **Bisect the modules.** Comment entries out of
   `targets/esp32wroom/firmware/InitMods.c` down to none, confirm stability,
   then add back one at a time. This is how the telemetry stack-overflow was
   found; guessing did not work.

Remember `PIOS_Assert()` is a silent infinite spin on this target (no `DEBUG`
define) — no message, no core dump, no reset. A hang with no output is still
consistent with a failed assert.

## Check the linker did the right thing

```bash
xtensa-esp32-elf-nm build/ninjapilot_esp32wroom.elf | grep -E "uavo_handles|_heap_start" | sort
```

`__start__uavo_handles` and `__stop__uavo_handles` must both exist and be in
DRAM (`0x3ffb....`), and `_heap_start` must be **at or above**
`__stop__uavo_handles`. If the handles land at `0x3f40....` they are in
read-only flash and `UAVObjInitialize()`'s memset will fault on boot.
