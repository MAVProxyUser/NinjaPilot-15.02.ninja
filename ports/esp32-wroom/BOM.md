# Bill of materials -- the airframe that hovered on 2026-09-02

Everything below is what was actually on the quad for the first stable hover,
plus the pin-by-pin wiring the firmware expects. Where a part was a generic
substitute the requirement it has to meet is stated so it can be swapped.
Prices are omitted on purpose (they drift); the links are the ones the parts
were bought from.

## Parts

| # | Item | Part | Qty | Source | Notes |
| --- | --- | --- | --- | --- | --- |
| 1 | Flight controller | **SparkFun Thing Plus - ESP32 WROOM (USB-C)**, SKU **WRL-20168**, module ESP32-WROOM-32E (ESP32-D0WD-V3 rev 3.0) | 1 | https://www.sparkfun.com/products/20168 (also https://www.amazon.com/dp/B0BC29D9QG) | 3.3 V logic, no USB peripheral (the USB-C is a UART bridge). Motor 4 on GPIO12 needs the one-way `XPD_SDIO_FORCE` eFuse burned (see README "Hardware"). |
| 2a | IMU (evaluation board) | **TDK InvenSense EV-ICM-20602** | 1 | https://www.digikey.com/en/products/detail/tdk-invensense/EV-ICM-20602/6140300 | ICM-20602, SPI. Either 2a or 2b. |
| 2b | IMU (breakout) | Generic **ICM-20602** SPI breakout | 1 | https://www.amazon.com/dp/B0FXWL157Q | Any ICM-20602 board with SCLK/MOSI/MISO/CS/INT broken out works. Not an ICM-20948 or BNO08x (different drivers). |
| 3 | Motors | **T-Motor F40 2300KV** FPV series, sold as a set of 2 | 2 sets (4 motors) | https://www.getfpv.com/tiger-motor-f40-2300kv-fpv-series-motor-set-of-2.html | Two CW, two CCW as delivered in a set. |
| 4 | ESC | Generic **4-in-1 ESC** (the tested unit was an unbranded one) | 1 | -- | Must accept standard PWM 1000-2000 us (the firmware has no DShot), rated for 4S and >= 25 A per motor for the F40 on 4x4.5, and provide a 5 V BEC. The BEC feeds the board's VUSB rail -- see "Power". |
| 5 | Props | **HQProp 4x4.5 Bullnose** | 1 set (2 CW + 2 CCW) | https://www.amazon.com/dp/B07FN65Z8L | CW props on M1 (front-left) and M3 (rear-right); CCW props on M2 (front-right) and M4 (rear-left) -- see "Mixer and rotation". Re-check every prop against its motor's rotation after any refit. |
| 6a | Battery | **Tattu 650 mAh 4S1P 75C 14.8 V, XT30** | 1+ | https://www.amazon.com/dp/B07219QLWG | Tested. Mounted aft on this frame -- see "Center of gravity". |
| 6b | Battery | **Tattu 850 mAh 4S 75C 14.8 V, XT30** | 1+ | https://www.amazon.com/dp/B07218QR29 | Also tested. Same electrics, 31 % more capacity and mass; either pack flies. |
| 7 | RC receiver | **Spektrum DSMX satellite, SPM9745** | 1 | Spektrum | 3.3 V device: 3.3 V, GND, signal to GPIO16. Bind it to the transmitter beforehand (firmware auto-bind is off). |
| 8 | Frame | 4-inch-class X frame, ~8 in diagonal motor-to-motor, ~6 in lateral | 1 | -- | Model not recorded. Battery was mounted AFT on the hovering build; see "Center of gravity". |
| 9 | USB-C cable | any data cable | 1 | -- | Flashing only, at 115200 baud (460800 fails on this bridge). **Never with the battery connected.** |
| 10 | (optional) USB-UART adapter, 3.3 V | any | 1 | -- | IDF console on UART1: TX GPIO22, RX GPIO23, 57600. Not needed to fly. |

Firmware: `firmware_normal_41hz.bin` from this repo (41 Hz DLPF, Rate yaw,
MotorsSpinWhileArmed, GCS receiver bound, no Flip, no Autotune). Toolchain
that built it: ESP-IDF v5.3.2, GCC 13.2, macOS arm64. Ground: the NinjaPilot
GCS (Qt 5.15) and the Python tools in `tools/` (Python 3, no extra packages).

## Wiring (SparkFun Thing Plus silkscreen names, from `board_hw_defs.c`)

| Signal | Board GPIO | Goes to |
| --- | --- | --- |
| SPI SCLK | 5 (SCK) | IMU SCLK |
| SPI MOSI | 18 (MOSI) | IMU SDI / MOSI |
| SPI MISO | 19 (MISO) | IMU SDO / MISO -- leave the IMU's SA0/AD0 pin **unconnected** (it is often the same net as SDO; grounding it shorts MISO) |
| IMU chip select | 14 | IMU nCS |
| IMU data ready | 32 | IMU INT1 |
| 3.3 V, GND | 3V3, GND | IMU VDD/VDDIO, GND (3.3 V only) |
| DSM satellite | 16 (RX1) | satellite signal on UART2 RX; satellite power from 3V3, not 5 V |
| UART2 TX (spare) | 17 (TX1) | unused. The same UART2 (16/17, 57600) is the `pios_usart_aux_cfg` spare port for GPS / second telemetry / serial RC; SBUS would use `invert_rx` (ESP32 inverts in hardware) -- but it is DSM's port on this build |
| PPM sum in | 21 | **compiled out** (RMT noise on an open pin starved the gyro task); wire a real PPM source before enabling |
| IDF console (optional) | 22 TX / 23 RX | UART1, 57600, boot log and panics; not needed to fly |
| Motor 1 | 15 | ESC channel for the **front-left** motor (NW) |
| Motor 2 | 33 | ESC channel for the **front-right** motor (NE) |
| Motor 3 | 27 | ESC channel for the **rear-right** motor (SE) |
| Motor 4 | 12 | ESC channel for the **rear-left** motor (SW) -- eFuse note above |
| ESC 5 V BEC | VUSB | powers the board in flight |
| ESC GND | GND | |
| Status LED | 13 | on-board (slow blink disarmed, strobe armed) |
| BOOT button | 0 | `BOARD_BTN_PIN`: hold ~3 s at power-up to erase stored settings (LED flutters while pending) |
| UART0 | 1 TX / 3 RX | the USB-C bridge (`pios_usart_telem_cfg`, 115200 at boot); serial UAVTalk if WiFi is not used |

Motor numbering is the OpenPilot QuadX convention: 1 NW, 2 NE, 3 SE, 4 SW,
looking down with the nose up the page. "Nose" is the airframe's, not the
IMU's -- see below.

## Mixer and rotation

`MixerSettings.Mixer{1..4}Vector` is `[ThrottleCurve1, ThrottleCurve2, Roll,
Pitch, Yaw]`; the preflight in `tools/flight_monitor.py` insists on this
table (its `QUADX_MIXER`, the last three columns):

| Output | GPIO | Position | Roll | Pitch | Yaw | Motor spin (from above) | Prop |
| --- | --- | --- | --- | --- | --- | --- | --- |
| M1 | 15 | front-left (NW) | +64 | +64 | -64 | **CW** | CW |
| M2 | 33 | front-right (NE) | -64 | +64 | +64 | **CCW** | CCW |
| M3 | 27 | rear-right (SE) | -64 | -64 | -64 | **CW** | CW |
| M4 | 12 | rear-left (SW) | +64 | -64 | +64 | **CCW** | CCW |

How to read it, and why the physical layout must match it exactly:

- **Roll +**: a positive roll command (the controller wants the right side
  down / is fixing a left-side-low tilt) speeds up the motors with +Roll,
  so those must be the LEFT motors: M1 and M4.
- **Pitch +**: a positive pitch command (nose up / fixing a nose-low tilt)
  speeds up the +Pitch motors, so those must be the FRONT motors: M1 and M2.
- **Yaw +**: a positive yaw command (nose right, clockwise from above) speeds
  up the +Yaw motors. A motor's reaction torque turns the frame the opposite
  way to its own spin, so the +Yaw motors (M2, M4) must spin **CCW** and the
  -Yaw motors (M1, M3) **CW**. Props are matched to that: CW props on M1/M3,
  CCW props on M2/M4.

Every one of those statements is relative to the IMU's idea of "front", so
the IMU orientation (next section) has to be right first. The bench tool
(`tools/bench_test.py --quick`) confirms the roll and pitch columns against
the airframe (tip the nose down: M1 and M2 must speed up), and the 2026-09-01
crashes are what it looks like when the IMU's front is the airframe's tail on
this exact table.

## Power -- the one hard rule

**Never connect the flight battery and USB at the same time.** The ESC's 5 V
BEC and the USB-C bridge land on the same VUSB rail; two supplies on one rail
has destroyed boards. Flash on USB with no battery; run motors on battery
with no USB. There is deliberately no firmware interlock (the only detectable
signal is also energized by the BEC in flight).

## IMU orientation

The firmware mounts the ICM-20602 as `TOP_0DEG`: the chip's +x is the nose.
On the hovering build the breakout ended up with +x pointing at the TAIL, and
that -- not tuning, not vibration -- flipped the quad twice on 2026-09-01: on
a correct mixer a backwards board is positive feedback on both axes. Either
mount the IMU with +x forward, or set `AttitudeSettings.BoardRotation =
(0, 0, 180)` and save (`tools/apply_recommended_settings.py --board-rotation
0,0,180`). **Verify before the first arm**: `tools/orientation_check.py`, tip
the airframe's real nose down, it must say NOSE DOWN. The preflight in
`tools/flight_monitor.py` fails unless Yaw is 180 on this frame; edit that
expectation if you mount the IMU straight.

## Center of gravity and idle

The 650 mAh pack sits aft on this frame. Four equal idle thrusts lift the
light end first: at a 1168 us idle the armed quad pitched nose-up over its own
tail at zero throttle, where the FC applies no stabilization at all. Set the
idle (`ActuatorSettings.ChannelNeutral`, `--neutral` in the apply tool) low
enough that the motors barely turn, and/or move the battery forward over the
motor centroid. Arm with the quad on the ground and untouched: the estimator
learns gyro bias during the arming second.

## Settings that made it fly

| Object.Field | Value | Why |
| --- | --- | --- |
| AttitudeSettings.BoardRotation | 0, 0, 180 | IMU +x at the tail on this build |
| ManualControlSettings.ChannelGroups | DSM (MainPort) x5 | SPM9745 on GPIO16 |
| ActuatorSettings.MotorsSpinWhileArmed | TRUE | idle spin when armed |
| ActuatorSettings.ChannelNeutral | low enough not to lift the nose | see above |
| FlightModeSettings.Arming | Yaw Right | gesture arming, on the ground |
| FlightModeSettings.Stabilization1-3 | Attitude, Attitude, Rate, Manual | self-leveling, rate yaw |
| StabilizationSettingsBank1 | rate 0.0032 / 0.0075 / 0.00005, attitude Kp 3.2 | 4-inch-class defaults; "hovers", not yet tuned |
| MixerSettings | stock QuadX table, linear curve | preflight checks it |
| board_hw_defs.c DLPF | 41 Hz | good practice on a 4-inch frame |

`tools/flight_monitor.py` checks all of these and prints GO/NO-GO before you
arm.

## Remote ID

Broadcast Remote ID rides on the ESP32's own WiFi: a soft-AP `RID-xxxxxx`
carries the ASTM F3411 Message Pack in its beacons (`firmware_remoteid.bin`,
configure with `tools/remoteid_setup.py`). To make it a complete broadcast
add a GPS on the spare UART2 (GPIO16 RX / GPIO17 TX, 57600 default) - the
Location and System messages fill in from `GPSPositionSensor` automatically.
