# LiteWing (ESP32-S3) — brushed nano quad port

> Two repositories are involved. The **ESP-IDF board target** and its tools are
> here on the [`litewing`](https://github.com/MAVProxyUser/OpenPilotESP32-WROOM-32E/tree/litewing)
> branch (`targets/litewing/`). The **posix twin** and the ground-side tooling
> are on the [`litewing`](https://github.com/MAVProxyUser/NinjaPilot-15.02.ninja/tree/litewing)
> branch of **NinjaPilot** (`flight/targets/boards/simlitewing/`,
> `ground/pyuavtalk/`, and the GCS config plugin).

Status 2026-09-04: **the firmware runs on real LiteWing hardware.** It boots,
the MPU6050 streams, all four motors drive, the GCS knows the board, and the
control path is closed — `ManualControlCommand.Connected = True` with sticks
arriving over the link. The twin also still hovers in Gazebo.

Not yet done, and honest about it: **no barometer is fitted and no altitude
hold is compiled in**; the accel wants its six-point calibration; the Bank1 PID
gains are still 4-inch-class and meaningless at 45 g; and it has not flown.

### Verified on hardware

| | |
| --- | --- |
| Boot + telemetry | 25 objects streaming, UAVTalk 57600 on UART0 |
| Alarms | Sensors, Attitude, Actuator, Telemetry, ManualControl all **OK** |
| Gyro at rest | x +0.028  y −0.010  z −0.025 °/s, σ 0.05 — quiet |
| Accel | −101 mg Z offset, gain +1.7 % (inside ±3 % spec; needs calibration) |
| Motors | M1–M4 individually **and all four together** at 12.5 % and 25 % duty |
| Control | `Connected = True`, channels echo 1000/1500/1500/1500/1500 |
| Disarmed output | `ActuatorCommand = [0, 0, 0, 0]` |
| RC receiver | SPM9745 DSMX satellite on IO15, sticks reaching ManualControl |
| IMU orientation | HUD tracks the airframe in roll and pitch, so `BoardRotation` 0/0/0 |
| Motor corners | all four walked on the bench and matched after correction |

### Flashing

```bash
cd targets/litewing/esp-idf
idf.py -p /dev/cu.wchusbserial8320 -b 115200 flash
```

460800 fails on the CH340K; use 115200.

**A reflash does not fix stored settings.** `board_apply_default_airframe()`
returns early on a provisioned board, deliberately, so it never overwrites what
you saved. A board first flashed before the GCS-receiver change keeps the old
DSM mapping and will not arm. Push the fix over the link instead of erasing
everything:

```bash
python3 ../../../NinjaPilot-15.02.ninja/ground/pyuavtalk/persist_gcs_receiver.py \
        --serial /dev/cu.wchusbserial8320
```

### There is no receiver on this board

The V2.6.C schematic has no satellite connector and no PPM input — LiteWing is
flown over WiFi, which is the point of the airframe. All five channels come
from the **GCS receiver** (`GCSReceiver` UAVObject) and ride the telemetry
link, so the same mapping works over WiFi UDP in flight and USB serial on the
bench.

This was the one thing standing between the firmware and a hover. The mapping
inherited from the ESP32 quad pointed at `DSMMAINPORT`, so
`ManualControlCommand` sat at `Connected=FALSE` with every channel at 65535 and
the board could not arm no matter what else was right.

### Power, read off the schematic

```
USB-C VBUS ─> +5V ─┬─ D1 SS34 ─> VBUS ─> U2 SPX3819 ─> +3V3 ─> ESP32
                   ├─ U1 AO3401A gate   (P-channel power path)
                   └─ IC1 TP4056 VCC ─> BAT ─> +BATT ─┬─> J2 battery
                                                      └─> motors J7–J10
```

**USB and the battery may be connected at the same time — that is how it
charges.** U1 isolates the battery from VBUS whenever USB is present, and its
body diode blocks VBUS→+BATT. This is the *opposite* of the ESP32 quad's rule,
where an ESC BEC and USB meet on one VUSB rail; do not carry that rule over.

On USB alone the motor rail is still live, fed by the TP4056's BAT pin and
capped by Rprog = R5 = 1.2 kΩ at `1100/1.2 ≈ 917 mA` for all four motors. Four
720-size coreless motors want 0.8–1.0 A *each*, so the props spin but cannot
lift. With no battery the TP4056 also cycles, so that rail is not a clean
supply. R22–R25 are 10 k gate pulldowns, so the motors are held off by hardware
before the ESP32 drives a pin.

### Bench tools

```bash
# one motor, or all four in turn then together. Nothing is armed. PROPS OFF.
python3 tools/litewing_motor_test.py --all --duty 250 --seconds 2

# accel: turn the board over in your hands, it stops on its own
python3 ../../NinjaPilot-15.02.ninja/ground/pyuavtalk/accel_calibrate.py \
        --serial /dev/cu.wchusbserial8320 --apply --save
```

The motor test switches `ActuatorCommand` to flight-read-only, which is the
mechanism the GCS Output tab uses: `actuator.c` computes its mixer output, has
`ActuatorCommandSet()` refused, re-reads the object and pushes *our* value to
the pins. No mixer, no stabilization, no arming anywhere in the path. It reads
the channel back off the board to prove the override took, and counts link
drops so a brownout is reported rather than inferred.

### The GCS knows this board

Board id **0x1302**. `devicedescriptorstruct.h` names it, and
`configgadgetwidget.cpp` has a `0x1300` branch giving it the CC-style attitude
widget (where the six-point accel calibration lands) plus a fixed-function
hardware card.

**The board must actually SAY it is a LiteWing, and the GCS must have its own
entry for it.** Board-specific handling now lives in five places on the ground
side plus the setup wizard's controller type, and LiteWing has its own
`CONTROLLER_LITEWING` rather than borrowing the Thing Plus's. Sharing a type
works right up until the two boards need different behaviour, and then applies
one board's assumptions to the other silently -- which is exactly what would
have happened with `ChannelAddr`: the wizard resets it to identity, correct
wherever a mis-ordered motor is fixed by moving an ESC lead, and wrong here
where the motors are soldered and `ChannelAddr` IS the corner mapping.

**The corner mapping is `1,2,3,0`**, derived from the PCB and then confirmed by
driving each mixer row on the bench:

| Net | Pin | PCB position | Physical |
| --- | --- | --- | --- |
| MOT_1 | GPIO5 | right, top | rear-left |
| MOT_2 | GPIO6 | right, bottom | front-left |
| MOT_3 | GPIO3 | left, bottom | front-right |
| MOT_4 | GPIO4 | left, top | rear-right |

The PCB gives relative geometry but does not by itself say which EDGE is the
nose -- except that it does, and it was missed: `U7` (the MPU6050), `U8` (the
ESP32) and `J1` (USB-C) are **all placed at rot=180**, four parts agreeing that
the board's logical orientation is a half turn from the KiCad canvas. Guessing
top-is-front instead of reading that field produced a mapping 180 degrees out,
caught only when driving mixer row 1 spun the back-right motor. The IMU itself
was never wrong: the HUD tracks the airframe in roll and pitch, so
`BoardRotation` stays 0/0/0.

**The board must actually SAY it is a LiteWing.** `board-info.mk` feeds the
build system, but `pios_board_info_blob` in `pios_board.c` is what the firmware
*publishes* — through `FirmwareIAPObj.BoardType` and byte 12 of the firmware
description — and nothing checks that the two agree. Left at the ESP32 quad's
`0x12` while `board-info.mk` said `0x13`, the GCS obediently identified this
board as a Thing Plus and showed that board's hardware page, pin map and motor
badges. Every LiteWing branch in the GCS was correct and simply never ran.
Confirm with `FirmwareIAPObj`: BoardType `0x13`, BoardRevision `0x02`.

Board-specific pin names live in three separate places in the GCS, and all
three needed teaching: the hardware card (`configgadgetwidget.cpp`), the Output
tab labels (`outputchannelform.cpp`) and the mixer channel dropdown
(`cfg_vehicletypes/vehicleconfig.cpp`). The motor badges painted on the airframe
picture were a fourth, and worse — they were baked *inside* the `quad-x` group
in `multirotor-shapes.svg`, so a static asset was asserting one board's pin
numbers for every board. They are now separate groups selected at runtime.

One trap worth knowing, because it is armed and waiting on any brushed board:
`outputchannelform.cpp` had `MINOUTPUT_VALUE = 500`, a sane floor in
*microseconds*. Here a channel value is tenths of a percent *duty*, so a 500
floor cannot represent 0 — opening the Output tab would have silently clamped
`ChannelMin` from 0 up to 500, which is **50 % throttle on all four motors at
rest**. The bounds now follow the board.

### The S3 compiles as-is

```bash
cd targets/esp32wroom/esp-idf
cmake -G Ninja -B build-s3 -DIDF_TARGET=esp32s3 \
      -DSDKCONFIG_DEFAULTS=sdkconfig.defaults -DSDKCONFIG=sdkconfig.s3 \
      -DPYTHON_DEPS_CHECKED=1 . && ninja -C build-s3
```

Configures and builds with **no errors and no source edits**: an 879,696-byte
image. That is the concrete version of the claim above — the S2 needed an LEDC
servo backend, core-count-aware task creation and a relocated pin map before it
would even build, and the S3 needed nothing.

It is emphatically **not** a flashable LiteWing firmware. It compiles; it has
never run. What it still carries:

- the **Thing Plus pin map**, so motors are on GPIO 15/33/27/12 instead of
  LiteWing's 5/6/3/4, and GPIO 26–32 are flash/PSRAM territory on S3 modules;
- the **console on GPIO 22/23, which do not exist on the S3 at all** —
  `SOC_GPIO_VALID_GPIO_MASK` in the IDF masks out bits 22–25;
- **brushless servo-pulse output**, not the brushed duty model below;
- the **ICM-20602 SPI** sensor path, not MPU6050 over I2C.

So the remaining work to a real LiteWing image is the pin map, the brushed LEDC
backend, an MPU6050 I2C transport and the console pins — not an architecture
fight.

## Why the S3 is portable when the S2 is not

From the IDF's own `soc_caps.h`, not from marketing:

| | ESP32 (flew) | ESP32-S2 | **ESP32-S3 (LiteWing)** |
| --- | --- | --- | --- |
| CPU cores | 2 | 1 | **2** |
| MCPWM | yes | **none** | **yes** |
| Native USB | no | yes | yes |
| Hardware UARTs | 3 | 2 | 3 |
| SRAM | 520 KB | 320 KB | 512 KB |

The dual core is the whole argument. This codebase pins every flight task to
core 1 and leaves WiFi and lwIP on core 0, and the characterised ~4 ms
scheduler stalls are tolerable only because of that split. The S2 has one core
and destroys it. The S3 keeps it, and keeps MCPWM as well, so the S3 is close
to a retarget-plus-pinmap where the S2 was a rewrite. See [ESP32-S2.md](ESP32-S2.md).

## The hardware

LiteWing V2.6.C, from CircuitDigest / Semicon Media. ESP32-S3-WROOM-1, ~45 g,
100 × 100 mm, 1S LiPo, four 720-size **coreless brushed** motors on 55/65 mm
props. Schematic: `jobitjoseph/LiteWing`, `hardware/LieWingV2.6.C`.

Pin map transcribed from the KiCad schematic, not the wiki (which does not
publish the motor pins):

| Function | GPIO |
| --- | --- |
| Motors MOT_1 / MOT_2 / MOT_3 / MOT_4 | 5 / 6 / 3 / 4 |
| MPU6050 (I2C0) SCL / SDA / INT | 10 / 11 / 12 |
| Battery sense ADC_BAT | 2 |
| LEDs blue / red / green | 7 / 8 / 9 |
| Buzzer BUZ1 / BUZ2 | 38 / 39 |
| I2C1 header (for a ToF module) SDA1 / SCL1 | 40 / 41 |
| SPI header (for a flow module) MOSI / CLK / MISO / CS | 35 / 36 / 37 / 42 |
| UART0 (CH340K bridge) | TXD0 / RXD0 |

Expansion header also brings out nine free GPIOs (1, 13, 15–20, 48), UART0,
both I2C buses, the flow SPI, 3V3 and VBUS.

**The base board carries exactly one sensor: the MPU6050.** The V2.6.C
schematic contains no PMW3901, VL53L1X, MS5611 or HMC5883 symbol — only bare
connectors (`Conn_01x06`, `Conn_01x09`) where such parts would attach. The
last two rows of that table are *header pinouts*, not fitted devices. The ToF
and optical flow live on a separate **LiteWing Drone Positioning Module**
(its own board and schematic in the same hardware repo); baro and mag would go
on I2C0 via the expansion header. Plan for a bare IMU and add from there.

## The real work: a brushed output model

Every other target here drives brushless ESCs, which want a 1000–2000 µs pulse
and an idle above their stop or they never spin. LiteWing drives coreless
motors through low-side **IRLML6344** N-channel MOSFETs. The gate takes a
**duty cycle**, 0–100 %, at roughly a 20 kHz carrier. There is no pulse width,
no arming ritual, no ESC range calibration.

So the range is reinterpreted rather than reused. `ChannelMin`/`Max` become
`0..1000` = 0.0–100.0 % duty; `ChannelNeutral` is 0 and
`MotorsSpinWhileArmed` is FALSE, because a brushed motor at zero duty simply
stops. On hardware the backend turns that number into an LEDC duty instead of
a pulse; the actuator pipeline above it is untouched.

That last part is worth more than convenience. It removes **by construction**
the failure that tipped the ESP32 quad onto its tail on 2026-09-02, where four
equal idle thrusts lifted the light (nose) end while the FC applied no
stabilisation at all because throttle was below zero. Here an armed,
throttle-down quad sits still.

Measured on the twin:

| stick | ActuatorCommand |
| --- | --- |
| armed, throttle down | `[0, 0, 0, 0]` |
| 50 % | `[469, 469, 469, 469]` — 46.9 % duty |
| 100 % | `[992, 992, 992, 992]` — 99.2 % duty |

The control loop drives that model in the right direction on both axes too —
tilt injected via the sensor stream at 50 % throttle, reading
`ActuatorCommand` (M1 NW, M2 NE, M3 SE, M4 SW):

| stimulus | ActuatorCommand | result |
| --- | --- | --- |
| level | `[456, 483, 456, 483]` | balanced |
| nose down | `[956, 983, 0, 0]` | front pair up |
| nose up | `[0, 0, 956, 983]` | rear pair up |
| roll left | `[708, 0, 204, 1000]` | left pair (M1/M4) up |
| roll right | `[0, 729, 1000, 236]` | right pair (M2/M3) up |

Each correction raises the dropped side, which is the whole game. The rail-to-
rail saturation is expected: nothing feeds vehicle dynamics back, so a sustained
20° error winds the integrator exactly as it does props-off on real hardware.

## It flies in Gazebo

`ground/gazebo_bridge/worlds/litewing.sdf` on the branch is generated from the
airframe's real numbers, not copied from the X3: 55 g, motors at ±35 mm for a
99 mm diagonal, `motorConstant` 2.4e-08 so a 720 coreless on a 55 mm prop makes
~22 g at 3000 rad/s — **thrust-to-weight 1.60**. `tools/litewing_bridge.py`
closes the loop: Gazebo's IMU becomes GyroSensor/AccelSensor, the firmware's
brushed `ActuatorCommand` drives the rotors, and only the collective is the
bridge's — every attitude correction comes from the firmware.

macOS needs the server and GUI as separate processes (gz-sim#44); run both
under `GZ_PARTITION` so another Gazebo on the machine is undisturbed.

```
  t     alt      vz     roll   pitch   ActuatorCommand
  1.0   0.015   +0.09    +0.0    +0.0   [692, 694, 692, 694]
  5.1   0.966   +0.06    +0.0    -0.0   [644, 644, 644, 644]
 11.2   1.038   +0.00    -0.0    -0.0   [647, 647, 647, 647]
 25.4   1.039   +0.00    +0.0    +0.0   [647, 647, 647, 647]
 39.5   1.039   +0.00    +0.0    +0.0   [646, 647, 648, 647]
```

Thirty-plus seconds at 1.039 m, `vz` 0.00, roll and pitch pinned at ±0.0°, all
four motors within ±1. The model predicts hover at **624** duty from first
principles; the aircraft hovers at **647** — agreement to 4 %, so the brushed
0..1000 duty model and the physics are consistent.

### The retune, measured rather than asserted

Bank1's stock 4-inch-class gains **do** diverge on a 55 g airframe: a
rock-steady ten-second hover, then the rails, reproducibly at t≈17 s. A nano
has a fraction of the inertia for comparable authority.

| | stock (4-inch) | LiteWing |
| --- | --- | --- |
| Roll/Pitch rate Kp | 0.0032 | **0.0012** |
| rate Ki | 0.0075 | **0.0022** |
| rate Kd | 0.00005 | **0.00002** |
| attitude Kp | 3.2 | **2.5** |

`LITEWING_STOCK_GAINS=1` reproduces the divergence.

### Landing: command a descent, never cut throttle

The first version dropped throttle to zero when the flight timer expired. From
1.5 m that is a free fall — about 0.55 s, arriving near **5.4 m/s** — and it
put the airframe on its back, where it then sat unable to take off (roll
−180°, motors pushing it into the ground) until the pose was reset. On real
hardware that is how arms break.

The bridge now walks the altitude setpoint down at 0.35 m/s, lets the same PD
fly it, and only cuts power once the airframe is resting and still, then
disarms:

```
  land  0.5  alt  1.483  vz -0.04   land  4.6  alt  0.735  vz -0.27
  land  2.0  alt  1.264  vz -0.20   land  6.7  alt  0.113  vz -0.20
  land  3.6  alt  0.944  vz -0.32   land  7.7  alt  0.006  vz -0.00
  touchdown at 0.006 m, vz +0.00 m/s   disarmed: Disarmed
```

### Flight trail

Translucent cyan **CYLINDER** segments via the `/marker` service, so the flown
path persists in the scene and take-off is visible after the fact. Cylinders,
not `LINE_STRIP`: gz renders LINE_STRIP at 1 px regardless of scale and it is
invisible at scene distance — the same lesson `gazebo_bridge.py` already
records. 40 mm tubes suit a 100 mm airframe, and the `/marker` service replies
with `Empty`, not `Boolean`.

### Three traps that each cost an afternoon

**1. `ActuatorCommand` telemetry is periodic at 1000 ms.** Publishing the
cached value drove Gazebo's rotors at 1 Hz against 1 kHz physics: the airframe
pogoed floor-to-6 m and flipped. It reads exactly like a tuning problem and is
not one. Poll the object explicitly at loop rate.

**2. A paused world looks exactly like a firmware failure.** A GUI connecting
to a running server can leave the world paused, and a paused world steps no
physics and publishes no IMU — so the aircraft sits motionless at its spawn
pose while a naive bridge happily prints an altitude column. The tell is the
number: a paused model sits at its **spawn** z (0.03 here), whereas a landed
one rests at half its body thickness (**0.006**). Those differ, and that
difference is the whole diagnosis. The bridge now forces `pause:false` via
`/world/<w>/control` before anything else, and **exits** if zero IMU frames
arrive rather than printing numbers that would not be a real flight. Verify
independently of your own bridge with
`gz topic -e -t /world/litewing/dynamic_pose/info`.

**3. macOS cannot run `gz sim` server and GUI in one process** (gz-sim#44), and
the Ruby `gz` wrapper **exits on stdin EOF** — so a detached server dies the
moment whatever held its stdin goes away. Spawn it with a pipe held open, and
run everything under `GZ_PARTITION` so a second Gazebo on the machine is
undisturbed.

## Traps

- **`board_rev` must stay `0x02`.** `attitude.c` has
  `#define BOARDISCC3D (bdinfo->board_rev == 0x02)` and keys the MPU6000-family
  sensor path off it. Any other revision silently routes to the ADXL345 path,
  `updateSensors()` returns −1 forever and Attitude sits at Error with no
  sample ever reaching the filter. The board id is `0x1302`: `0x13` is
  LiteWing, `0x02` is a sensor-path selector, not a revision number.
- **The airframe defaults are written in two places.** A second block later in
  `PIOS_Board_Init` re-writes `ChannelMin/Neutral/Max` after
  `simlitewing_apply_default_airframe()` runs. It silently overwrote the
  brushed 0/0/1000 back to servo 1000/1000/2000, and the first probe duly
  reported servo values on a brushed board. Both sites must agree.
- **GPIO 35/36/37 are the octal-PSRAM pins** on ESP32-S3-WROOM-1 variants that
  carry PSRAM — the schematic brackets them "PSRAM" for exactly this reason —
  and this board routes them to the SPI header the flow module plugs into. A
  part with octal PSRAM cannot drive that header at all. Check the module
  suffix; do not enable PSRAM.
- **Which physical corner is MOT_1 is NOT in the schematic.** The netlist gives
  gate-to-GPIO only; the corner assignment is on the PCB silkscreen. The mixer
  in the twin is the stock OpenPilot QuadX convention as an explicit
  **placeholder**. Verify it against the board before anything spins — a motor
  order or IMU frame that disagrees with the mixer is positive feedback on both
  axes, and it is what flipped the ESP32 quad twice on 2026-09-01.

## What already exists, and what does not

Already in the flight tree, so these are *enable-and-wire*, not *write*:

- `flight/pios/common/pios_ms5611.c` — MS5611 barometer, and its init is
  `PIOS_MS5611_Init(cfg, int32_t i2c_device)`, which takes an I2C handle
  directly.
- `flight/pios/common/pios_hmc5x83.c` — HMC5883/5983 magnetometer family.
- `pios_i2c.c` already exists in the ESP32 port.

The LiteWing expansion header lists MS5611 and HMC5883 as intended I2C0
devices. So altitude hold and magnetic heading are reachable on this airframe
in a way they are not on the Thing Plus build, which is rate-and-attitude
only — provided you fit the parts, because nothing but the MPU6050 is on the
base board.

Written for this board: **BMP388** (`flight/pios/common/pios_bmp388.c`), which
also drives a BMP390. Not in the tree, and would need writing: **VL53L1X**
(ToF) and **PMW3901**
(optical flow) — both of which are on the separate Positioning Module anyway,
so they are two purchases and two drivers away, not one `#define`.

**Done:** the MPU6050-over-I2C transport. Rather than fork 770 lines,
`pios_icm20602.c` gained an I2C branch in the three functions that actually
touch the bus — the family is register-compatible for everything the driver
uses, so only the transport differs. Blocking I2C is safe there because the
data-ready path runs in a task, not an ISR, and the I2C burst lands at
`buffer[1]` so sample offsets match the SPI layout (byte 0 there is the
address-echo dummy). SPI-only targets get constant-false stubs and are
unchanged.

One trap that came with it: `board_hw_defs.c` had inherited
`.User_ctl = USERCTL_DIS_I2C`. That is bit 4, `I2C_IF_DIS` — it would have hung
up the bus mid-configuration on a part we talk to *over* I2C, and the MPU6050
datasheet marks it "always write 0" regardless.

**I2C budget caution.** Baro and mag would share I2C0 with the IMU. A 15-byte
read at 400 kHz costs ~390 µs, about 19 % of a 500 Hz period, and MS5611
conversions run ~10 ms. Budget the rates (baro 20–50 Hz, mag 50–100 Hz, both
normal) — and note this is precisely why Revo and CC3D put their IMU on SPI.

## Sensors on the expansion header

Nothing but the MPU6050 is fitted, so every capability below is a part you add.

### Barometer — the cheap win, and a driver now exists

`flight/pios/common/pios_bmp280.c` + `pios_bmp280.h` were written for this
airframe (on the `litewing` branch). There was no Bosch driver in the tree at
all before — only `pios_bmp085.c` and `pios_ms5611.c` — which is why altitude
hold kept being described as needing GPS.

Mass is the whole argument: a **BMP280 is ~1 g**; a Matek M9N-5883 is
**14.5 g**, which on a 55 g airframe takes AUW to ~70 g and thrust-to-weight
from **1.60 to 1.24**.

It is simpler than the MS5611 on purpose. The MS5611 needs a state machine
because temperature and pressure are separately commanded conversions; the
BMP280 in NORMAL mode converts both continuously, so `poll()` is "read six
bytes and compensate" with no FSM to get wrong.

**The units trap.** `handleBaro()` in `modules/Sensors/sensors.c` compares
against `PIOS_CONST_MKS_STD_ATMOSPHERE_F` = 1.01325e5, so the sample must be
**Pascals** — even though `barosensor.xml` labels the field "kPa". Bosch's
compensation returns Q24.8, hence the `/256`. Emitting kPa as the label
suggests would report a 1.5 m hover as **32,423 m**.

What is verified, and what is not:

| | status |
| --- | --- |
| Bosch compensation maths | **verified** against the datasheet's worked example: 25.08 °C, 100653.3 Pa |
| Units contract, driver → `handleBaro` | **verified**, round-trips 0–1000 m to under 0.2 mm |
| Compiles into the target | **yes**, twin still boots 0x1302 with brushed endpoints intact |
| I2C transactions, real silicon | **untested** — no BMP280 on a posix twin's nonexistent bus |

### GPS + compass — fitted and working

Not the Matek M9N-5883 this section used to plan for. What is on the board:

| part | bus | address / pins | state |
| --- | --- | --- | --- |
| **Sequre M10-12** (u-blox M10) | UART1 | RX **GPIO18**, TX **GPIO17**, 115200 | Fix3D, UBX |
| **HMC5883L** | I2C1 | **0x1E** (SCL 41 / SDA 40) | reading, uncalibrated |
| BMP388 | I2C1 | 0x77 | working |

Both sensors share I2C1 with the barometer — the VL53L1X pads
(`VIN / GND / SCL1 / SDA1`). The GPS runs on **3.3 V**, not the 5 V its manual
asks for; no boost converter was needed.

**The M10 must run UBX, not NMEA.** It leaves the factory emitting UBX binary
*and* NMEA interleaved on the same port, and `parse_nmea_stream()` abandons its
whole input buffer on any non-`$` byte outside a sentence — so every UBX frame
took the NMEA following it down too. Checksum-valid `$GNRMC`/`$GNGSA` arrived
continuously at ~4.7 kB/s and the parser still completed about one sentence a
minute, leaving `GPSPositionSensor.Status` at `NoGPS`. UBX is the right answer
anyway: `ubx_autoconfig` silences the NMEA at source, and the NAV solution
carries velocity and accuracy estimates NMEA does not.

**Verify the compass part before wiring.** Most modules sold as "HMC5883L" —
the blue GY-271 especially — are actually **QMC5883L**: address 0x0D, different
register map, no in-tree driver. A genuine HMC answers at **0x1E** and its ID
registers (0x0A-0x0C) read `H`, `4`, `3`. The board prints this at boot:

    [BOARD] I2C1 scan (SCL=41 SDA=40): 0x77 0x1E
    [BOARD] mag at 0x1E: id='H43' (0x48 0x34 0x33) -> HMC5883L/5983
    [BOARD] HMC5883L at 0x1E registered

A genuine HMC needs **no new driver** — `pios/common/pios_hmc5x83.c` is in-tree
and `PIOS_I2C_Transfer` already exists in this port. Two fixes were needed to
use it here, both upstream-safe:

- The driver sets `data_ready` **only** in its DRDY interrupt handler, yet
  declares `is_polled = true`. With no DRDY wire it registered, passed
  `PIOS_SENSORS_Test()`, and then silently never produced a sample. It now
  reads the part's own status register (0x09 bit 0) when
  `PIOS_HMC5X83_HAS_GPIOS` is undefined. STM32 targets are untouched.
- Its SPI half uses the STM32 StdPeriph name `SPI_BaudRatePrescaler_16`;
  aliased to `PIOS_SPI_PRESCALER_16` in `pios/esp32/pios_esp32.h`. Dead code
  here, but it still has to compile.

#### HomeLocation, and a WMM bug worth knowing about

`HomeLocation.Be` — the earth's field vector at home — is what `filtermag.c`
scores every magnetometer sample against. Without a valid one the Magnetometer
alarm sits at Critical and `armhandler.c` refuses to arm, in **every** fusion
mode.

`libraries/WorldMagModel.c` had a **use-after-free** that made this impossible
to satisfy: `WMM_GetMagVector()` assigned `B[]` in nT, FREE()d
`GeoMagneticElements`, and then read back through the dangling pointer to
rescale to milligauss. Zeros on a host build, about -1.7e36 on the ESP32 —
while returning success. A perfectly good GPS fix still produced an unarmable
board. Fixed by scaling inside the success branch.

(Separately, `WMM_DateToYear()` validates month and day but never the year, and
the coefficients are WMM-2010. The date is now clamped to their 2015 validity;
that is an accuracy fix, worth a degree or two of declination, and was *not*
the cause of the garbage.)

Home is now set two ways: the GPS sets and **persists** it on the first
qualifying fix, and a hand-entered lat/lon gets its `Be` computed by the
board's own WMM. That second path exists because the GCS carries no magnetic
model at all — nothing outside the firmware can produce `Be`.

#### The thresholds that gate everything

`GPSSettings.MaxPDOP` (3.5) and `MinSatellites` (7) gate **three** things at
once: auto-home, `filterlla.c` converting GPS lat/lon into NED, and therefore
`PositionState` North/East, `TakeOffLocation` and return-to-home. Below them
PositionState horizontal stays exactly 0.00 and position hold has nothing to
hold. Indoors at a window this board reaches 5-6 sats / PDOP 4-8, so none of it
engages; open sky is not optional.

### Altitude hold -- fitted and working

> **Superseded.** This section describes the `modules/AltFilter` era. That
> module has been removed — the vertical channel now comes from stock
> StateEstimation (`filteraltitude.c` + `filterbaro.c`). The barometer
> measurements and the sensor-rate reasoning below still hold; the references
> to AltFilter's own constants do not. See **The navigation stack**.


A barometer is on the expansion header and the chain behind it is compiled in.
Wiring, on the pads next to the VL53L1X footprint:

| Baro | LiteWing |
| --- | --- |
| SDA | **GPIO40** (SDA1) |
| SCL | **GPIO41** (SCL1) |
| VCC | 3V3 (the pad is silkscreened VIN -- meter it before trusting it) |
| GND | GND |

I2C1, deliberately *not* I2C0: that bus carries the MPU6050 at 500 Hz, where a
15-byte burst already costs ~19% of a period, and a barometer has no business
taking time from the only sensor the aircraft cannot fly without. The ToF's
`IO1` pad is an interrupt line and stays unconnected.

**The part is identified at boot, not chosen at build time.** This matters more
than it sounds. The I2C address does not identify a barometer -- 0x76 and 0x77
are shared by the BMP280, BME280, BMP388 and BMP390, and every breakout brings
out an ADDR/SDO pad that moves its part between them, so a board silkscreened
"default 0x77" can perfectly well answer at 0x76. The chip ID does identify it,
but it lives at a *different register per family*: 0x00 on a BMP388/BMP390,
0xD0 on a BMP280/BME280. A BMP280 cannot answer a BMP388 probe, and the result
looks exactly like a dead sensor.

So `PIOS_Board_Init` probes both addresses, reads both ID registers, prints the
raw bytes, and starts whichever driver matches:

```
[BOARD] I2C1 scan (SCL=41 SDA=40): 0x76
[BOARD] baro at 0x76: reg0x00=0x00 reg0xD0=0x58
[BOARD] BMP280 at 0x76 initialised
[BOARD] BMP280 sample 0: 98614.52 Pa  22.28 C  (~228.1 m)
```

Measured spread across consecutive samples is ~0.2 Pa, about 1.5 cm of
altitude. `pios_bmp388.c` was written for this board (the BMP280 driver already
existed); both are compiled, and either part works in the socket.

**Reading the outcome without a console.** The IDF console is on UART1
(GPIO17/18) because UART0 carries UAVTalk, so those prints need an adapter
clipped to the expansion header. The same news arrives over telemetry as the
`I2C` system alarm, and the severity says which failure it is:

| Alarm | Meaning |
| --- | --- |
| OK | barometer found and initialised |
| Warning | bus is up, nothing answered -- wiring, power, or an address that is neither 0x76 nor 0x77 |
| Critical | something answered but is not a part we can drive -- read the printed chip IDs |
| Error | right part, rejected the configuration |

`modules/AltFilter` consumes whatever registers as a
`PIOS_SENSORS_TYPE_1AXIS_BARO`, publishes `BaroSensor`, and runs the 3-state
altitude Kalman that fills `PositionState.Down` / `VelocityState.Down`. It is
in both the module list and `InitMods.c` -- a module in one and not the other
never starts, silently.

The filter is **held in reset while disarmed**, re-zeroing its reference every
pass, so `PositionState.Down` reading exactly 0.0 on the bench is correct
rather than a fault: altitude hold references the point you armed at. The CC
complementary filter also needs several seconds to converge, and integrating
its output before then puts the estimate metres from the truth while the
airframe sits still.

### The altitude hold thrust mode

OpenPilot already has the controller -- `modules/Stabilization/altitudeloop.c`
and the `ALTITUDEHOLD` / `ALTITUDEVARIO` thrust modes. None of it is new here;
it was simply behind `#ifdef REVOLUTION`, along with its two call sites in
`stabilization.c` and `outerloop.c`. Those three guards are now
`#if defined(REVOLUTION) || defined(LITEWING)`, and this target defines
`LITEWING=1`. Defining `REVOLUTION` instead would pull in the whole navigation
chain to win three `#ifdef`s.

The loop also needs `AltitudeHoldSettings` and `AltitudeHoldStatus`
initialised. Both were already in `UAVO_SYNTH_SRCS` but had no
`UAVOBJ_INIT_*` flag, which compiles and links silently while leaving the
objects half-built.

Confirmed on hardware with a BMP388 fitted: `BaroSensor` streaming pressure
and temperature, every system alarm OK, and both altitude-hold objects
readable over telemetry.

**Not yet flown.** The loop commands thrust, so `AltitudeHoldSettings` wants
tuning for a 45 g airframe before anyone trusts it in the air. Barometer noise
measured over the same telemetry window, which sets the floor for how tight
the hold can be:

| Part | Config | Spread | ~altitude |
| --- | --- | --- | --- |
| BMP280 | osr x16, IIR 16 | 1.6 Pa | ~13 cm |
| BMP388 | osr x8, IIR 3 | 6.6 Pa | ~55 cm |

Both parts were then swept properly rather than left on a datasheet
recommendation. `firmware/baro_sweep.c`, built with `BOARD_BARO_SWEEP=1` and
the console temporarily on UART0, walks the fitted part through a table of
oversampling/IIR/ODR settings, takes 48 samples of each and scores them on the
**RMS of successive differences**. That metric is the point: a plain standard
deviation over a ~5 s window is dominated by real room-pressure drift, which
penalises the slower configs purely for taking longer to collect, while a
first difference cancels any linear drift and leaves sample-to-sample noise --
which is what the estimator actually has to reject.

BMP388 @ 0x77, and BMP280 @ 0x76, noise in cm of altitude:

| BMP388 | noise | | BMP280 | noise |
| --- | --- | --- | --- | --- |
| x1 IIR off 50Hz | 47.0 | | x1 IIR off | 27.9 |
| x2 IIR 1 50Hz | 17.2 | | x2 IIR 2 | 12.6 |
| x4 IIR 3 50Hz | 8.6 | | x4 IIR 4 | 4.9 |
| x8 IIR 3 50Hz | 4.6 | | x8 IIR 4 | 5.8 |
| x8 IIR 7 50Hz | 2.3 | | x8 IIR 8 | 3.1 |
| **x8 IIR 15 50Hz** | **1.3** | | **x8 IIR 16** | **2.3** |
| x16 IIR 7 25Hz | 2.0 | | x16 IIR 4 | 4.0 |
| x16 IIR 15 25Hz | 0.8 | | x16 IIR 8 | 1.9 |
| x16 IIR 31 25Hz | 0.4 | | x16 IIR 16 | 1.7 |
| x32 IIR 15 12.5Hz | 0.6 | | | |
| x32 IIR 31 12.5Hz | 0.6 | | | |

**The quietest row is not the chosen one in either column**, for two reasons
that only show up downstream:

*AltFilter polls at exactly 50 Hz.* An ODR below that hands it the same
conversion twice, and the Kalman treats a repeat as independent evidence,
shrinking its covariance on information it never received. Every sub-50 Hz row
pays that today. It is why the BMP280 runs x8 (~40 Hz) rather than its
quietest x16 (~26 Hz) for 0.6 cm more noise. Gating the drivers on data-ready,
so a stale read returns false and AltFilter skips the correction, would make
the quiet rows safe -- that work is not done.

*The IIR coefficient is group delay.* The time constant is roughly
coefficient x ODR period, so the 0.4 cm row (IIR 31 at 25 Hz) is ~1.2 s of lag
handed to a thrust loop on a 45 g airframe.

Chosen: BMP388 **x8 IIR 15 at 50 Hz** (1.3 cm, ~300 ms time constant, 3.5x
better than the drone recommendation it replaced) and BMP280 **x8 IIR 16**
(2.3 cm, ~40 Hz). Whichever part is fitted gets its own config, so swapping
between them needs no reflash.

For scale: `AltFilter` assumes `BARO_NOISE_VAR_M2 = 0.25`, i.e. **50 cm** of
barometer noise -- 20-40x worse than either part measures here, so the filter
is discounting the barometer heavily. Resist lowering it on bench numbers
alone: a board on a desk cannot reproduce prop wash over an open port, which
is the disturbance that assumption is really carrying.

## The navigation stack

`modules/Attitude` (the standalone complementary filter) and the hand-written
`modules/AltFilter` are **out**. The board now runs stock `modules/Sensors` +
`modules/StateEstimation`, the same chain Revolution uses, plus
`modules/PathFollower`. Validated against the old filter at the same physical
pose: roll 2.7137 -> 2.7043, pitch 1.4918 -> 1.5198, identical 0.0008 deg noise.

Port traps this uncovered, all of the same shape — shared code carrying
CopterControl assumptions:

- `PIOS_ICM20602_Test()` accepted only WHO_AM_I 0x12 while this board's part
  answers 0x68. Nothing called it until Sensors did, and the symptom was **not**
  "IMU failed": a failing sensor makes SensorsTask park in a
  `while (1) vTaskDelay(10)` that never reloads its watchdog flag, so the board
  became a silent watchdog reboot loop with both cores idle and no mention of
  the IMU.
- Stack sizes again (`PIOS_SENSORS_STACK_SIZE`, `PIOS_STATEESTIMATION_STACK_SIZE`,
  `PIOS_PATHFOLLOWER_STACK_SIZE`). The StateEstimation one is a FLOOR —
  stateestimation.c maxes it against each filter's own request.
- `PIOS_WDG_SENSORS` did not exist in the board header.

**PathPlanner is deliberately NOT built.** It alone panics this board:
StoreProhibited at address 8 inside `PIOS_CALLBACKSCHEDULER_Dispatch`, reached
from altitudeloop.c, i.e. an unrelated callback's scheduler-task pointer is
corrupt. Ruled out by measurement: callback stack size (1K/3K/8K/16K, each
verified in effect), heap (~159 KB free), the priority-array bounds. It appears
only when PathPlanner creates a fifth callback scheduler task
(`CALLBACK_TASK_NAVIGATION`); moving it onto an existing task makes the symptom
vanish, which looks like heap layout masking the corruption rather than fixing
it, so that workaround was not taken. Prime suspect is `restorePathPlan()`,
which restores a stored mission through a flashfs this target does not have.

Position hold and return-to-home do **not** need it:
`ManualControl/pathfollowerhandler.c` calls `plan_setup_positionHold()` and
`plan_setup_returnToBase()` directly and PathFollower executes the resulting
PathDesired. PathPlanner only sequences multi-waypoint missions.

### Flight mode 2: Rattitude + GPS Assist

Acro at the stick edges, self-levelling in the middle, and let go to brake and
park in 3D:

    FlightModeSettings.Stabilization2Settings = Rattitude, Rattitude, AxisLock, CruiseControl
    StabilizationSettings.FlightModeAssistMap = None, GPSAssist, None, None, None, None

`isAssistedFlightMode()` keys only on `FlightModeAssistMap[position]` and the
bank's **thrust** mode — never on the roll/pitch/yaw modes — so Rattitude is
orthogonal to the assist. CruiseControl thrust gives full `GPSASSIST` (auto
thrust, true 3D hold); AltitudeHold/Vario would give
`GPSASSIST_PRIMARYTHRUST`, leaving you the throttle.

**You cannot arm in this position.** `armhandler.c:296-308` refuses both ways:
AltitudeHold/Vario thrust returns false, and `GPSASSIST` returns false ("as it
sits waiting to launch, it will move to hold, and auto thrust will auto launch
otherwise"). Arm in position 1, take off, then switch.

"Let go" is `flagRollPitchHasInput = |Roll| > 0 || |Pitch| > 0` — an EXACT
zero. That only works because `receiver.c` forces `DeadbandAssistedControl`
(0.08 here) whenever assist is active; with no deadband, stick noise would
never let it enter BRAKE.

### Status LEDs

The board has **three** LEDs and the firmware drove one. BLUE GPIO7 (heartbeat,
unchanged), RED GPIO8, GREEN GPIO9, driven by `board_status_led_task` on core 0:

| LED | state | meaning |
| --- | --- | --- |
| RED | off | disarmed, nothing blocking |
| RED | fast blink | **cannot arm** — an arm-blocking alarm is set |
| RED | solid | armed |
| GREEN | off | no 3D fix |
| GREEN | slow blink | 3D fix, but not good enough to hold position |
| GREEN | solid | position hold is ready |

Green mirrors `filterlla.c`'s own admission test plus `HomeLocation.Set`, so
solid green means PositionState North/East are genuinely non-zero — not merely
that a GPS is attached.

## CPU budget

Measured per-task, not guessed (`BOARD_CPU_REPORT` prints per-interval
percentages from `uxTaskGetSystemState` deltas; cumulative counters understate
badly).

The `xTaskCreate` shim used to pin **everything** to core 1 while core 0 sat
98.8% idle. It now has a name-based affinity table in `pios/esp32/pios_esp32.h`:
System, TelTx/TelRx, PIOS_UART_RX, GPS, RemoteID and StatusLED go to core 0.
Sensors, StateEstimation, the callback schedulers, Stabilization, Actuator,
Receiver, PIOS_DSM (stick input is control path) and the IMU data-ready task
stay on core 1. Result: **core-1 load 100% -> ~74%**.

That exposed a trap worth remembering: `PIOS_TASK_MONITOR_GetIdlePercentage()`
calls `xTaskGetIdleTaskHandle()`, which returns the idle task of the **calling**
core — so the moment systemmod moved to core 0, `SystemStats.CPULoad` silently
started reporting core 0 (29%!) and the CPUOverload alarm stopped watching the
control core. It now asks for core 1 explicitly. `CPULOAD_LIMIT_CRITICAL` is
95, and armhandler blocks on any Critical alarm, so that number is an arming
gate, not a curiosity.

Per-callback share of callback-task time: EventDispatcher 35.8, StateEstimation
35.2, AltitudeHold 13.3, Stabilization1 10.8, Stabilization0 2.3,
ManualControl 2.2, **PathFollower 0.4**. The remaining levers, largest first,
are EventDispatcher and AltitudeHold — both driven by PositionState/VelocityState
publishing at the full sensor rate from `filteraltitude.c`'s predict step.

`PIOS_SENSOR_RATE` is **250 Hz** with the IMU divider at 333 Hz, deliberately
running the producer ahead of the consumer: matching them exactly makes every
poll marginal, because SensorsTask waits exactly one sensor period for the
primary sample and counts a timeout as a sensor failure.

## Next steps

Before the next flight:

1. **Six-point magnetometer calibration.** The Magnetometer alarm is the only
   remaining arm-blocker: measured field is ~986 mGa against a correct 529 mGa
   reference, i.e. uncalibrated hard iron. Configuration -> Attitude.
2. **Fly it outdoors.** 7 satellites / PDOP < 3.5 is what turns PositionState
   North/East from zero into real numbers; a window will not do it.
3. **Verify the red/green LED polarity.** Assumed `active_low = false` to match
   blue. If they read inverted, flip the field in `board_hw_defs.c`.

Then:

4. Position hold and RTH on `Complementary+Mag+GPSOutdoor` (measured 76%, so it
   fits). INS13 is the heavier EKF and would need the CPU conversation above.
5. Find the PathPlanner fault if multi-waypoint missions are wanted.
