# OSD32MP1-RED + NinjaPilot SimPosix

Run the NinjaPilot flight code on the Octavo OSD32MP1-RED (STM32MP157 SiP:
dual Cortex-A7 running Linux, plus a Cortex-M4), using **SimPosix as the
integration base** with real sensors replacing the simulator.

- `CLAUDE.md` — rules and traps. Read before changing anything.
- `SKILLS.md` — the commands.

---

## Status: flight stack running on real sensors (2026-08-16)

| | |
|---|---|
| OS | OpenSTLinux 3.1, kernel 5.10.10, armv7l, 2 cores, ~426 MB RAM |
| Image | `osd32mp1-red-v1_2-NINJAPILOT.img` (edited — see below) |
| Ethernet | **working** — DHCP, mDNS `osd32mp1-red-v12.local` |
| USB console | **working** — `/dev/cu.usbmodem*`, autologin root |
| SSH | **working** — key auth, dropbear |
| Toolchain | gcc/g++ 9.3.0, make 4.3, python3 3.8.2 (**no git, no rsync**) |
| SocketCAN | **DroneCAN bus working** — 2 Matek nodes allocated and publishing; allocator is a systemd service |
| Live sensors | MPU-9150 @ 500 Hz (1440 free-run max), HMC5883L @ 69 Hz max, BMP280 @ 22 Hz (MP1 I2C); MPU-9150 raw proxy 492 Hz (400 kHz bus, clamp-500 guardrail v3), BMP388 @ 50 Hz, RM3100 @ 25 Hz, IST8310 @ 97 Hz max, GNSS @ 10 Hz (20 max) (CAN) |
| **realposix** | **`fw_realposix.elf` reads every sensor natively** (PIOS I2C driver + CAN hub, no Python in the loop) and publishes the full UAVObject set; 360 s soak graded **GO** |
| Node 124 firmware | **custom AP_Periph** (`ap-periph-ninja-debug.patch`, gcc 10.2.1) — adds the declared BMP388 probe + an I2C debug scanner; flashed over CAN |
| SimPosix | still builds and runs (`fwsimposix.service`, bridge-fed) — kept as the sim-parity target; never run both at once (same ports) |

Ethernet was the long pole and the cause was **the wrong device tree**: this is
a **V1.2** board and Octavo's v3.0 image ships only the V1.1 DTB. Details in
`CLAUDE.md`.

## Getting in

Three independent channels, so no single misconfiguration locks you out:

```bash
ssh osd32mp1
```

```bash
./venv/bin/python board_cmd.py "uname -a"
```

```bash
screen /dev/cu.usbmodem* 115200
```

The USB console needs no network at all. Password fallback is `ninjapilot`;
key auth is already installed. Address the board **by mDNS name, never a
remembered IP** — the DHCP lease moves.

## The image, and the three edits it needs

Base: `osd32mp1-red-v1_2-trusted-openstlinux-sdcard-v3_0_1.zip` (the **V1.2**
image — the V1.1 one cannot do Ethernet on this board).

### Provenance — identify by hash, not by filename

- product page: https://octavosystems.com/octavo_products/osd32mp1-red/
- getting started: https://octavosystems.com/app_notes/osd32mp1-red-getting-started/
- Yocto BSP layer: https://github.com/octavosystems/meta-octavo-osd32mp1
  (for **building** images — not a flashable artifact, and not needed to get running)

| | sha256 | size |
|---|---|---|
| **works** `osd32mp1-red-v1_2-trusted-openstlinux-sdcard-v3_0_1.zip` | `4d9546342acf4f5da612a758dc75189d1a64c9e972a42b0b28e46d634f8289c2` | 244,369,137 |
| **wrong for V1.2** `osd32mp1-red-debian-sdcard-v3.0.zip` | `0fc13f0885695766546379c4a4494a36855626460ac37ede603ddb36d05cb404` | 1,127,143,235 |

The second one is listed so it can be told apart, not used: it ships only the
V1.1 device tree, which on this board gives `no phy at addr -1` and no Ethernet
**while the link LEDs keep blinking** — they are driven by the PHY's own link
detection, which works whether or not the SoC can reach it over MDIO. See the
board-revision rule at the top of `CLAUDE.md`; check the silkscreen revision
against the DTB filename before debugging Ethernet at all.

What actually runs, once flashed:

    ST OpenSTLinux - Weston (Yocto/dunfell) 3.1-snapshot-20230124
    kernel 5.10.10   (SMP PREEMPT — note: NOT PREEMPT_RT)
    /boot/stm32mp157c-osd32mp1-red-v1_2.dtb

The version strings do not match the zip's name: Octavo's "v3.0.1" packaging
contains an ST 3.1-snapshot distro. That is expected, not a mixed-up download.

Two further changes are made **after** flashing and are not part of the image —
SCHED_FIFO for the firmware, and I²C at 400 kHz. Both are in `board-config/`
with the measurements that justify them; the I²C one is the single
highest-impact change on the board.

| # | stock behaviour | edit |
|---|---|---|
| 1 | gadget is `rndis.0`; macOS has no RNDIS driver at all | → `ecm.0` |
| 2 | no console over USB | add `acm.0` → `/dev/ttyGS0` + getty |
| 3 | root password is EMPTY; dropbear refuses blank auth | `authorized_keys` + real hash |

Already correct in the stock image, and left alone: `dropbear.socket` is
enabled, `/lib/systemd/network/53-usb-otg.network` already gives `usb0`
192.168.7.1/24 with `DHCPServer=yes`, and `iptables.rules` is empty.

**The gadget is currently either a network device or a console, not both.** The
cause is **dwc2 TX-FIFO exhaustion on the board** (`No suitable fifo found` out
of `ecm_set_alt`), not a macOS limitation as first written — see `CLAUDE.md`.
Extending `g-tx-fifo-size` in the DTB is the untried fix. The shipped config
picks the console. Flash with:

```bash
diskutil unmountDisk /dev/disk10 && sudo dd if=~/Downloads/osd32mp1-red-v1_2-NINJAPILOT.img of=/dev/rdisk10 bs=4m status=progress
```

The edits are reproducible offline on macOS without sudo — `gpt.py` + `part.py`
+ `debugfs`, recipe in `SKILLS.md`.

## Sensor inventory — what is actually connected and live

| sensor | where | address / node | rate | state |
|---|---|---|---|---|
| MPU-9150 #1 gyro+accel | MP1 I2C `/dev/i2c-3` | 0x68 | **500 Hz** | live — the PRIMARY IMU |
| MPU-9150 #2 gyro+accel | DroneCAN, L431 I2C | node 124, msg 20500/20501 | **491.8 Hz** | live — RAW-count proxy (no cal/filter on the node), 400 kHz bus, hard-clamped 500 with guardrail v3 (pool-occupancy wire-health, tiered backoff to a 100 Hz floor, 10 s boot soft-start); realposix failover IMU |
| BMP388 barometer | DroneCAN, L431 I2C | node 124, msg 1028/1029 | **50 Hz** | live, 98.1 kPa |
| BMP280 barometer | MP1 I2C `/dev/i2c-3` | 0x76 (CHIP_ID 0x58) | **25 Hz** | live in the hub (baro2_*) — BaroSensor failover if the CAN baro dies; latent CAN probe also declared on the L431 |
| HMC5883L mag | MP1 I2C `/dev/i2c-3` | 0x1E (ID 'H43') | **50 Hz** | live → AuxMagSensor |
| RM3100 mag | DroneCAN | node 125, msg 1001 | **25 Hz** | live, 51 uT — the FLIGHT mag (hub keys 1001 to node 125) |
| IST8310 mag | DroneCAN, L431 I2C | node 124, msg 1001 | **25 Hz (97 max)** | live, 46.9 uT — Holybro Micro M9N; `MAG_MAX_RATE=100` unlocks ~97 Hz; hub ingests as qmc_* (aux) |
| GPS (Holybro Micro M9N) | DroneCAN, L431 UART | node 124, msg 1063/1061/20003 | **10 Hz (20 max)** | decoded — Fix2 + Auxiliary + Status; `GPS1_RATE_MS` 100→10 Hz, 50→true 20 Hz; indoors no-fix (two receivers showed 0 sats at this bench — window test decides) |

**GPS module history**: Holybro M8N → Matek M9N-5883 (its "QMC5883L" is
really a **QMC5883P at 0x2C** — scan before trusting a 5883 label; the module
has TWO mirrored JST-GH-6P connectors wired in parallel for pass-through) →
Holybro Micro M9N (IST8310 at 0x0E). Whichever module is plugged in, its
compass is found at boot: the custom firmware declares both QMC5883P and
IST8310 probes, and `I2C_SCAN=1` identifies anything new in one sweep.

**CAN vs I2C, sensor class by sensor class — all measured, same bench:**

| class | MP1 I2C (local) | DroneCAN (L431 node 124/125) | verdict |
|---|---|---|---|
| IMU rate | MPU-9150 #1: **493 Hz** paced (1440 free-run) | MPU-9150 #2: **491.8 Hz** sustained | TRANSPORT PARITY — the wire costs ~1 Hz |
| gyro bias | 1.184 dps (DLPF 44) | 0.640 dps TRUE (raw, DLPF off) | both raw die properties; PIOS calibrates |
| gyro noise sd | 0.041–0.047 dps | 0.085–0.094 dps | 2x = bandwidth physics (42 vs 256 Hz BW), not transport |
| gyro quantization | 0.0610 dps | **0.0610 dps IDENTICAL** | the proxy is bit-transparent |
| accel scale | −1.5 % (0.9846 g) | +4.3 % (1.0430 g) | stable per-die, repeatable to 0.001 g; one-time cal holds |
| accel noise | 0.014–0.022 m/s² | 0.030–0.046 m/s² | same bandwidth story |
| baro | BMP280: **25 Hz**, sd 1.5 Pa (~12 cm) | BMP388: **50 Hz** | CAN wins; ~131 Pa absolute offset between units (~11 m) — failover only, never blend |
| mag | HMC5883L: **69 Hz** true ODR | RM3100: **25 Hz**, 12.2 nT / IST8310: **25 Hz (97 max)** | RM3100 is the flight mag by quality (~25x finer than HMC) |
| GPS | — (no local GNSS) | M9N: **10 Hz sustained, 20 Hz true max** | CAN only |
| IMU latency | in-process read | 2 single frames, ~0.3 ms wire | both inside a 2 ms loop budget |

Bus load with everything at max: ~1215 fr/s ≈ 18 % of 1 Mbit, zero RX
overruns across full loaded windows. The wire is a bystander; the L431's
I2C+CPU is the ceiling on every stream.

**Which bus feeds which UAVObject (realposix source map):**

| UAVObject | source | fallback |
|---|---|---|
| GyroSensor / AccelSensor | MPU-9150 #1 (MP1 I2C, 500 Hz) | MPU-9150 #2 over CAN if local silent >200 ms |
| BaroSensor | BMP388 over CAN | local BMP280 if CAN baro silent >1 s |
| MagSensor | RM3100 over CAN | — |
| AuxMagSensor | HMC5883L (MP1 I2C) | — |
| GPSPosition/VelocitySensor | M9N over CAN | — |

Every sensor on either bus lands in the same hub snapshot with one
timestamp domain, so CAN-vs-I2C comparisons run **simultaneously under
identical motion** — the two IMU streams are the same sensor model on the
two transports, recorded side by side. Measured head-to-head (120 s,
stationary): 493 Hz local vs 399 Hz paired over CAN, **identical 0.0610
dps quantization on both** (the raw-count contract makes the wire
bit-faithful), true uncalibrated biases on both, noise differing only by
DLPF bandwidth choice. Full table in `CLAUDE.md`.

The BMP388 **moved** from the board's own I2C bus to the L431 CAN node
(2026-08-16). That took a custom AP_Periph build — the stock hwdef marks the
L431's only I2C bus INTERNAL, so no `BARO_PROBE_EXT` bit can ever reach it;
the fix is a *declared* probe (`BARO BMP388 I2C:0:0x77`). The full diff is
`ap-periph-ninja-debug.patch` (also: an I2C bench scanner with SDA/SCL-swap
detection over `debug.LogMessage`, airspeed+battery trimmed for flash), the
known-good binary is `fw/AP_Periph-ninja-gcc10.bin`, and the build **must use
gcc 10.2.1** — a gcc 13.3 image holds the node in its bootloader. Recipe in
`SKILLS.md`, saga in `CLAUDE.md`. The move freed ~10 % of the MP1's I2C budget
(bus busy 30 % → ~20 %) and costs ~1 % of CAN.

The KUSBA/ADXL345 was **removed from the bench permanently** (2026-08-15). It
was only ever a vibration reference - it read 0.912 g at rest, ~9 % low and
uncalibrated - and reading it needed the whole Klipper protocol (CRC16 framing,
a sequence number that persists across host connections, and a
zlib-compressed per-build JSON command dictionary). `klipper_probe.py` and
`klipper_accel.py` are kept because the protocol work is reusable, but nothing
in the flight path depends on it.

The magnetometer **works** — `|B| = 0.5113 Ga = 51.1 uT` against an Earth field
of 0.25-0.65 Ga. An earlier note in this repo claimed there was no working
magnetometer; that was wrong — the bus was silent because the DroneCAN
allocator was not running. `CLAUDE.md` records the trap.

The IST8310 on the GPS board is a **closed, irrelevant** question: it has no
driver in the AP_Periph image and is not the mag we use. Ignore it.

**Nothing on CAN publishes until the DroneCAN allocator has handed out node
IDs**, and `can0` comes up DOWN after every reboot. See `SKILLS.md`.

## Hardware reference

### Power

5V, at least 2A: barrel jack (5.5 mm outer / 2.5 mm inner) or USB-C. Prefer the
barrel jack once peripherals are attached.

**Octavo's getting-started page is stale here.** It calls the USB-C power
select **JP3** — but **there is no JP3 anywhere in the V1.2 schematic**. The
V1.2 equivalent is **JP21** (sheet 10, "Source power path", 3-pin, *default
1-2*). Trust the schematic over the web docs on jumper designators.

Headers and jumpers, verified page-by-page against
`OSD32MP15x_RED_7x_sch-V1_2`:

| ref | sheet | what |
|---|---|---|
| **JP4** | 7 | **UART4 header, 6-pin 2.54 mm** — buffered through U6 (SN74LVC2G241). This is the **serial-console header** (`console=ttySTM0`), i.e. a fourth way in that needs no USB and no network |
| **JP7** | 12 | mikroBUS / Click header — **pin 10 = 5 V, pin 9 = GND** |
| **JP8** | 7 | CAN FD — `4=NC, 3=CANH, 2=CANL, 1=GND`; `R48` 120 Ω **DNP** |
| **JP19** | 11 | Motor Control header — 3.3 V, motor current sense (`MC_CRNT_A/B/C`, `ANA0`). **Not a power tap** |
| **JP20** | 12 | the 40-pin RPi header |
| **JP21** | 10 | USB-C source power path, default **1-2** |
| **JP23** | 8 | camera `DCMI_HSYNC`, DNP |
| **JP24** | 2 | VBAT header — backup-domain **input**, not a supply |
| JP1 / JP2 | — | must be 1-2 for HDMI |

### The board has TWO 5.2 V rails, and the headers are on the riskier one

| rail | sheets | feeds |
|---|---|---|
| `PMIC_BSTOUT_5P2V` | 2, 7, 8, 10 | **CAN transceiver** (U20), HDMI, USB-C |
| `PMIC_VBUSOTG_5P2V/DET` | 2, 4, 11, 12 | **RPi header (JP20), mikroBUS (JP7)**, motor control |

The header 5 V is the **USB-OTG VBUS** rail. On the STPMIC1 that output is
normally enabled to *source* VBUS when the port acts as a USB **host** — and
we deliberately run the USB-C port in **device/gadget mode** (that is where
ECM/ACM come from). **So JP7 pin 10 may be dead in our configuration.**

**Measure JP7 pin 10 to GND, with the board booted the way we actually run it,
before wiring anything to it.** If it is dead, the clean answer for bench work
is to power the Matek nodes from a separate 5 V supply and simply tie the
grounds together — the CAN bus only needs a common reference, not a shared
rail.

Do not use an unidentified jumper as a power tap without measuring it.

### Where to take 5V for the CAN nodes

All confirmed against **schematic `OSD32MP15x_RED_7x_sch-V1_2`** (sheets 11–12),
not inferred from the standard pinouts.

The board's CAN connector **JP8** is `4=NC, 3=CANH, 2=CANL, 1=GND` — matching
the `NC / H / L / G` silkscreen — and **carries no power**, so the node's
supply comes from elsewhere:

| source | verdict |
|---|---|
| **mikroBUS `JP7` pin 10 (`5V`), GND on pin 9** | **best** — schematic-confirmed |
| **RPi header `JP20`** 5 V pins (2/4), GND 6 | fine — same `PMIC_VBUSOTG_5P2V` rail |
| **`JP4`** | **no** — sits on the 3.3 V domain (`PMIC_VOUT4_3P3V`), and is DNP |
| **VBAT header `JP24`** | **NO** — VBAT is the RTC/backup-SRAM domain **input** for a battery or supercap. It is not a rail, and cannot source 40 mA |

Both headers take 5 V from **`PMIC_VBUSOTG_5P2V/DET`** — nominally **5.2 V**,
which is inside the Matek CAN-L431's **4.5–5.5 V** input range (~40 mA), so
current is a non-issue and the voltage is fine.

Transceiver is a **TJA1441BTK**.

### Termination

**Exactly two 120 Ω terminators, one at each physical END of the bus** — not
one per node. Middle nodes stay open. The Matek nodes have a `120R` solder
jumper, **open from the factory** ("bridge it if the CAN wires are too long" —
Matek); the board's `R48` is 120 Ω but **DNP**, so the OSD32MP1 can never
terminate itself as shipped.

| bus | close `120R` on |
|---|---|
| L431 ↔ L4-3100 only | both — each is an end |
| board → L431 → L4-3100 | L4-3100 only; L431 is the middle |
| **L431 → board → L4-3100** | **both Matek nodes** — board is the middle, so DNP is exactly right |

The third row is the tidy one: it needs no soldering and turns the DNP into a
feature. Keep the splice stubs at JP8 short.

**Verify by measurement, powered off, across CANH–CANL:**

| reading | meaning |
|---|---|
| **~60 Ω** | correct — two terminators |
| ~120 Ω | only one — under-terminated |
| ~40 Ω | three — over-terminated (a real fault: overloads the drivers) |
| open | none fitted |

An under-terminated bus often works fine on a short bench harness and then
fails intermittently at airframe cable lengths — so terminate properly *before*
trusting any bench result.

### The actual bench chain

```
OSD32MP1 (JP8) ──── CAN-L431 ──── CAN-L4-3100
    END              MIDDLE           END
                  (serial GPS on
                   its UART - not
                   on the CAN bus)
```

Close `120R` on the **L4-3100** only; the **L431 stays open** because it is the
middle node. The board end needs a 120 Ω added — simplest is a resistor across
the **H and L wires inside the JP8 connector shell**, which needs no board
soldering and sits exactly at the bus end.

**Power trap:** the Matek JST-GH-4P carries `5V, CANH, CANL, GND`, but **JP8
pin 4 is `NC`** — the board supplies no 5 V on the CAN connector. So the
board→L431 cable runs H/L/G only (its 5 V wire lands on `NC` and powers
nothing), and **the L431 must be powered from somewhere else**. The
L431→L4-3100 cable is the full 4 wires, so the L4-3100 takes 5 V daisy-chained
through the L431.

For that "somewhere else", mikroBUS **JP7 pin 10** is the obvious candidate —
**but check it first**: it sits on `PMIC_VBUSOTG_5P2V`, the OTG VBUS rail,
which may be disabled while the USB-C port runs in gadget mode (see above).
A separate 5 V bench supply with grounds tied is the no-surprises option.

Load is ~40 mA per node plus ~30–50 mA of GPS. Run the board off the barrel
jack rather than bus USB.

**Measure before connecting.** On the Matek JST-GH-4P a **5V/GND swap is
destructive**, while a **CANH/CANL swap is harmless** (it simply will not
communicate) — verify the power pair with a multimeter and treat the signal
pair as recoverable. Grounds must be common.

## Why SimPosix is the right base

The Gazebo work already built the seam this needs. SimPosix supports:

    NINJAPILOT_EXTERNAL_PHYSICS=1

which disables the simulator's internal fake sensors and makes the firmware
consume sensor UAVObjects **injected over UAVTalk/UDP**. `gazebo_bridge.py` is
one producer of those objects — **real hardware is just a different producer of
the same objects**, so going from simulated to real sensors needs no firmware
change:

```
   Gazebo  ──┐
             ├──► GyroSensor / AccelSensor / MagSensor / BaroSensor /
   REAL   ───┘    GPSPositionSensor / GPSVelocitySensor   (UAVTalk, UDP :9000)
   SENSORS                          │
                                    ▼
                          fw_simposix.elf  (NINJAPILOT_EXTERNAL_PHYSICS=1)
```

The contract, as emitted by the existing bridge:

| object | fields | units |
|---|---|---|
| `GyroSensor` | x, y, z, temperature | **deg/s**, body frame |
| `AccelSensor` | x, y, z, temperature | **m/s²**, body frame (FRD) |
| `MagSensor` | x, y, z, temperature | milligauss, body frame |
| `BaroSensor` | Altitude, Temperature, Pressure | m, °C, kPa |
| `GPSPositionSensor` | Lat/Lon (1e7), Altitude, Status, Satellites, PDOP | — |
| `GPSVelocitySensor` | North, East, Down | m/s |

Frame convention is **FRD body → NED world** (`gazebo_bridge.py`'s `Q_FLU2FRD`
/ `Q_ENU2NED`). Any real sensor must be rotated into FRD before injection —
**the single most likely source of sign bugs in this whole effort.**

### Will it build here? — audited, yes

| concern | finding |
|---|---|
| ARM? | already builds arm64 on Apple Silicon; no `-march`/`-mcpu`, no inline asm in `flight/pios/posix/` |
| Linux? | `#ifdef __linux__` is a first-class branch in `FreeRTOSConfig.h` |
| 32-bit armhf? | no pointer-size or endianness assumptions in the posix layer |
| RAM? | `configTOTAL_HEAP_SIZE` is 45 KB (`MEM_SIZE` is defined and never referenced — dead) |
| link | Linux branch complete: `-lc -lgcc -lpthread -lrt` |

Build **natively on the board**. Cross-compiling from macOS is pointless here,
and this Mac volume is case-insensitive so Yocto/OpenSTLinux builds cannot run
on it at all.

## THE GYRO ANSWER: a mikroBUS Click, already software-enabled

The one missing sensor is a gyro, and the cheapest correct answer is a Click
board in the socket the board already has:

| Click | sensor | note |
|---|---|---|
| **6DOF IMU 14** (MIKROE-4237) | **ICM-42688-P** | I2C 1 MHz **or SPI 25 MHz** (COMM SEL jumpers), 2 kB FIFO |
| 6DOF IMU 27 (MIKROE-6514) | ICM-45686 | newer premium part |
| 6DOF IMU 22 | ICM-42670-P | |
| 9DOF 2 | ICM-20948 | |

**Verified ready on this board, no work needed:**

    spi@44009000  status=okay   = SPI5, the mikroBUS socket
    spi0       -> 44009000.spi
    /dev/spidev0.0 exists, child spidev@0, cs-gpios set, opens cleanly

JP7 carries `SPI5_NSS/SCLK/MISO/MOSI` (PF6/PF7/PF8/PF9) **and `MCLICK_INT` on
PD15** — so the ICM's data-ready interrupt lands on a GPIO, which is exactly
what a gyro-triggered `stabilizationInnerloopTask` wants. Click logic is 3.3 V
and JP7's 3V3 is `PMIC_VOUT4_3P3V` (the solid rail, not the questionable
VBUSOTG one). ICM-42688-P `WHO_AM_I` = **0x47**.

**Why not USB or CAN for the gyro** — all three routes were evaluated and each
fails on rate or latency, while SPI costs ~5 us:

| route | ceiling | why rejected |
|---|---|---|
| Klipper USB (KUSBA) | accel only | Klipper never streams gyro; full-speed USB = 1-2 ms jitter |
| DroneCAN RawIMU | ~200-400 Hz | ~59 B = 9 frames = 1.35 ms/sample at 1 Mbit |
| JuxiTech AHRS USB/UART | **100 Hz** | hard cap; UART 115200, I2C 100 kHz; does its own fusion |
| **mikroBUS SPI** | **8 kHz+** | — |

`PIOS_SENSOR_RATE` is 500 Hz and the inner loop is gyro-triggered, so anything
under ~500 Hz means lowering the control rate to suit the transport.

## Sensor integration plan

| device | bus | role |
|---|---|---|
| Matek CAN Node L431 | DroneCAN node 124 | GPS concentrator (serial GPS on its UART) — publishes `gnss.Fix2` @ 5 Hz |
| Matek CAN-L4-3100 | DroneCAN node 125 | **RM3100 magnetometer** (the "3100" in the name) — `MagneticFieldStrength` @ 25 Hz |
| SparkFun MPU9150 | **board I2C5 -> `/dev/i2c-3`** (RPi header JP20), addr `0x68` | **the only gyro source we have.** NOT on the Matek node - that build has no IMU driver at all |

**I2C bus map — the mikroBUS one is a trap:**

| header | bus | `/dev/` | occupants |
|---|---|---|---|
| **RPi JP20** | **I2C5** | **`i2c-3`** | **free — use this** |
| RPi JP20 | I2C1 | `i2c-0` | HDMI transmitter, touchscreens |
| **mikroBUS JP7** | I2C4 | `i2c-4` | **STPMIC1 + EEPROM + STUSB1600 — the power bus, do not use** |

MPU9150 is **3.3 V and NOT 5 V tolerant** — JP20 pin 1, never pins 2/4.

**Driver reality check:** this tree has `pios_mpu6000.c` (SPI), `pios_l3gd20.c`
and `pios_adxl345.c` — and **no MPU9150 driver at all**. So MPU9150 has no
incumbent advantage: any IMU here needs a new PiOS driver either way, and
`pios_mpu6000.c` is the SPI/FIFO template to copy. That argues for choosing on
merit (ICM-42688-P / SCH16T over SPI) rather than for the part already owned.
MPU9150 is also I2C-only: a 14-byte sample at 400 kHz costs ~340 us of blocking
bus time (~17 % at 500 Hz), versus ~5 us over 24 MHz SPI.
| SparkFun HMC5883L | I2C `0x1E` | magnetometer |
| Klipper accelerometer (KUSBA v2) | USB CDC → `/dev/ttyACM0` | ADXL345 @ up to 3200 Hz — **working**, see `klipper_accel.py` |

Two topologies, both worth having:

**A. Via CAN (flight-realistic).** Sensors hang off the Matek node's I2C, the
node publishes DroneCAN, the OSD32MP1 reads it through SocketCAN (`can0`) and
the bridge translates DroneCAN → UAVObjects. This is how a real airframe is
wired and keeps sensor timing off the application CPU.

**B. Direct I2C on the board (bring-up).** MPU9150/HMC5883L straight onto an
OSD32MP1 I2C bus via `/dev/i2c-*`. Fewer moving parts, so it is the right way
to *first* prove the sensor→UAVObject→firmware path. **Do B first, then A.**

The Klipper accelerometer is a USB-serial ADXL345 — useful as an independent
vibration reference to sanity-check the flight IMU, not as a flight sensor.

**RESOLVED: AP_Periph DOES support IMU over DroneCAN.** `Tools/AP_Periph/AP_Periph.h`
carries `AP_PERIPH_IMU_ENABLED`, an `AP_InertialSensor imu;` member and
`can_imu_update()`. Both AP_Periph's own README and dronecan.github.io omit IMU
from their supported-sensor lists — **the docs are stale, the source is not**.

But bandwidth makes it unsuitable for the RATE LOOP on classic CAN.
`uavcan.equipment.ahrs.RawIMU` is ~59 bytes without covariance, which is 9
frames of a multi-frame DroneCAN transfer, ~1.35 ms at 1 Mbit:

| RawIMU rate | bus utilisation |
|---|---|
| 100 Hz | ~14 % |
| 200 Hz | ~27 % |
| 500 Hz | ~68 % |
| 1000 Hz | **>100 % — impossible** |

`PIOS_SENSOR_RATE` is 500 Hz and `stabilizationInnerloopTask` is
**gyro-triggered**, so a classic-CAN gyro would both saturate the bus and add
arbitration jitter to the one loop that least tolerates it. **Keep the gyro
local (SPI); keep DroneCAN for GPS/mag/baro, which are slow.** The escape hatch
is CAN FD — the board's `m_can` controller is FD-capable (the DT exposes
`dtseg1/dtseg2/dbrp`), which would cut a RawIMU transfer to 1–2 frames.

**Start with GPS, not the IMU.** A serial GPS on the L431's UART sidesteps that
open question entirely: publishing GNSS is AP_Periph's primary job, so it emits
`uavcan.equipment.gnss.Fix2`, which maps straight onto the
`GPSPositionSensor` / `GPSVelocitySensor` objects the firmware already consumes.
It is also the one sensor with **no body-frame rotation to get wrong**, so it
exercises the whole DroneCAN → SocketCAN → UAVObject path without exposing the
FRD/NED sign trap at the same time. Prove the transport first, then add the
axes that can be inverted.

## Order of work

1. ~~Get Linux booting~~ **done** — V1.2 OpenSTLinux on SD.
2. ~~Build the firmware on the A7~~ **done** — both `fw_simposix.elf` and
   `fw_realposix.elf` build natively (see `SKILLS.md` for the Qt stub dance).
3. ~~Prove the stack with simulated sensors~~ **done** — bridge-fed simposix.
4. ~~Prove each sensor's identity~~ **done** — `probe_sensors.py` reads
   identity registers, not just ACKs.
5. ~~Real sensors natively in the firmware~~ **done** — the `realposix`
   target reads I2C through the PIOS Posix driver and CAN through the sensor
   hub, publishes the full UAVObject set, and passed a 360 s readiness soak.
6. ~~Move slow sensors behind the CAN node~~ **done for the baro** — BMP388
   on the L431 via the custom AP_Periph, decoded back into `BaroSensor`.

**Remaining before flight:** actuator output (PWM/DroneCAN ESC path), RC
input, failsafe wiring, an outdoor GPS fix to validate the lat/lon decode
(and settle the antenna question), then HITL against Gazebo.

## Files

| file | what |
|---|---|
| `ap-periph-ninja-debug.patch` | **the custom AP_Periph diff** for node 124: declared BMP388 probe, I2C debug scanner (SDA/SCL-swap detection over `debug.LogMessage`), airspeed+battery trimmed. Apply to ArduPilot master, build with **gcc 10.2.1 only** |
| `fw/AP_Periph-ninja-gcc10.bin` | the known-good binary built from that patch (195,244 B) — exactly what is flashed on node 124 |
| `can_flash.py` | **flash an L431 node over CAN** (BeginFirmwareUpdate + FileServer); embeds the three dronecan-python traps |
| `allocatord.py` | DroneCAN node-ID allocator **daemon** (runs on the board under `dronecan-allocator.service`; brings can0 up itself) |
| `dronecan_allocator.py` | the older session tool — allocates, prints a report, then **exits by design**; useful for its report only |
| `shmlogd.c` | consumer daemon for the firmware's `/dev/shm` log ring (`--dump` replays post-mortem, and **consumes** the ring) |
| `flight_readiness.py` | grades a soak from the ring: per-sensor Hz, bus saturation, GO/NO-GO per window |
| `probe_sensors.py` | sensor identity checks on an I2C bus — reads identity registers, not just ACKs (**on the board**) |
| `board_cmd.py` | run commands over the USB console (no network needed) |
| `can_poll.py` | who is on the DroneCAN bus; decodes node ids + message types |
| `can_bandwidth.py` | CAN load + per-transfer timing (counts transfers, not frames) |
| `klipper_probe.py` | Klipper wire protocol + data-dictionary fetch (**on the board**) |
| `klipper_accel.py` | ADXL345 streaming from the KUSBA (**on the board**) |
| `sensor_bridge.py` | **real sensors -> UAVTalk UAVObjects** for fw_simposix (**on the board**) |
| `detect.sh` | classify how/whether the board is attached |
| `gpt.py`, `part.py` | parse GPT / extract+inject partitions, unprivileged |
| `sha512crypt.py` | `$6$` hashes on macOS; self-tests against the spec vector |
| `usb_console.py` | libusb console fallback for stock images (ACM proto `0xff`) |
| `usb_descriptors.py` | dump what the gadget actually offers |
| `write_sdcard.sh` | guarded SD writer |
| `image-edits/` | the exact files written into the image |
| `board-config/` | SCHED_FIFO + 400 kHz I2C deployment, with the measurements |
