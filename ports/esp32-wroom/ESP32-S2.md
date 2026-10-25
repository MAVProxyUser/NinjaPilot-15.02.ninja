# The ESP32-S2 port (branch `esp32s2`, experimental)

> **The code described here is NOT on `main`.** It lives on the
> [`esp32s2`](https://github.com/MAVProxyUser/OpenPilotESP32-WROOM-32E/tree/esp32s2)
> branch. This file is carried on `main` as a pointer and a record, so the
> findings are not buried on a side branch. Files it refers to
> (`sdkconfig.defaults.s2`, the LEDC backend in `pios_servo.c`, the
> `BOARD_PIN_*` map) exist only on that branch. `main` is the ESP32 build that
> flew.

Status 2026-09-02: **builds, flashes, and boots on real S2 hardware.** Nothing
on the sensor, attitude or control path has been exercised, because no IMU was
wired. Read "What is NOT validated" before trusting any of this.

Verified on an ESP32-S2 rev v0.0, MAC `7c:df:a1:55:b6:24`, on
`/dev/cu.usbserial-110`.

The short version: the S2 is a **downgrade** for this workload. If you want to
move off the original ESP32, the target you want is the **S3** — see
"Why the S3 is the better target" at the bottom.

---

## Contents

1. [Silicon differences that actually matter](#1-silicon-differences-that-actually-matter)
2. [Build and flash](#2-build-and-flash)
3. [What changed in the code, and why](#3-what-changed-in-the-code-and-why)
4. [The S2 pin map](#4-the-s2-pin-map)
5. [UART allocation: a bring-up compromise](#5-uart-allocation-a-bring-up-compromise)
6. [Traps](#6-traps)
7. [What boot looks like when it works](#7-what-boot-looks-like-when-it-works)
8. [What is NOT validated](#8-what-is-not-validated)
9. [Open questions and next steps](#9-open-questions-and-next-steps)
10. [Why the S3 is the better target](#10-why-the-s3-is-the-better-target)

---

## 1. Silicon differences that actually matter

Every row below is from the IDF's own `components/soc/<chip>/include/soc/soc_caps.h`,
not from a datasheet summary or guesswork.

| | ESP32 (D0WD, shipping target) | ESP32-S2 | ESP32-S3 |
| --- | --- | --- | --- |
| CPU cores | 2 | **1** | 2 |
| MCPWM | yes | **absent** | yes |
| Native USB OTG | no | **yes** | yes |
| Hardware UARTs | 3 | **2** | 3 |
| LEDC timer width | 20 bit | **14 bit** | 14 bit |
| LEDC high-speed mode | yes | **no** | no |
| Bluetooth | yes | no | yes |
| WiFi | yes | yes | yes |
| SRAM | 520 KB | **320 KB** | 512 KB |

Plus the GPIO facts, from `SOC_GPIO_VALID_GPIO_MASK`:

- **GPIO 22, 23, 24, 25 DO NOT EXIST on the S2.** Not "reserved" — absent.
  The ESP32 build's console pins are 22 and 23, so that config is not merely
  suboptimal on an S2, it is nonsense.
- **GPIO 26-32 are the WROOM module's SPI flash.** Using one bricks the boot.
  The ESP32 build has the IMU data-ready on 32 and a motor on 27.
- **GPIO 46 is input-only** (excluded from `SOC_GPIO_VALID_OUTPUT_GPIO_MASK`).
- GPIO 43/44 are UART0's default pins, which is where a devkit's USB-serial
  bridge lands.

### The single core is the architectural one

This port's whole timing strategy on the ESP32 is **separation by silicon**:
every flight task pinned to core 1, WiFi and lwIP left on core 0, so the
network stack can never preempt the control loop. The S2 has one core. That
separation does not exist and cannot be recreated.

This is less alarming than it sounds *for this codebase specifically*, because
the port ran single-threaded before SMP was introduced — reverting to one core
is going back to a known-good shape, not inventing one. But the measured cost
that motivated SMP in the first place (WiFi + lwIP preempting the flight stack
produced a 5x jump in stabilization deadline warnings) applies again in full.
See [Open questions](#9-open-questions-and-next-steps).

---

## 2. Build and flash

```bash
cd targets/esp32wroom/esp-idf && . ~/esp/esp-idf/export.sh
cmake -G Ninja -B build-s2 -DIDF_TARGET=esp32s2 -DSDKCONFIG=sdkconfig.s2 \
      -DSDKCONFIG_DEFAULTS=sdkconfig.defaults.s2 -DPYTHON_DEPS_CHECKED=1 .
ninja -C build-s2
```

```bash
python -m esptool --chip esp32s2 --port /dev/cu.usbserial-110 -b 115200 \
    --before default_reset --after hard_reset write_flash @build-s2/flash_args
```

Read the console (UART0, 115200, over the same bridge):

```bash
python3 -c "import serial,time; s=serial.Serial('/dev/cu.usbserial-110',115200,timeout=0.3); s.dtr=False; s.rts=True; time.sleep(0.15); s.rts=False; t=time.time(); b=b''
while time.time()-t<20: b+=s.read(4096)
print(b.decode('utf-8','replace'))"
```

Both `-DSDKCONFIG=` and a separate defaults file are **required**, not tidiness:

- `-DSDKCONFIG=sdkconfig.s2` — the ESP32 build's generated `sdkconfig` pins
  `CONFIG_IDF_TARGET="esp32"`, and cmake hard-refuses to retarget over it
  ("Target 'esp32' in sdkconfig does not match currently selected IDF_TARGET").
- `sdkconfig.defaults.s2` is **standalone, not a layer** on
  `sdkconfig.defaults`. The base file pins the target and carries dual-core
  options (`CONFIG_LWIP_TCPIP_TASK_AFFINITY_CPU0`,
  `CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1`) that the S2 has no CPU for.

`-DPYTHON_DEPS_CHECKED=1` is the same `ruamel.yaml.clib` false alarm as the
ESP32 build. Separate `build-s2/` directory; the ESP32 `build/` is untouched
and was rebuilt to confirm no regression.

Sizes, for reference:

| | image | app partition free | heap free at boot |
| --- | --- | --- | --- |
| ESP32 | 888,896 B | 15% | ~280 KB |
| ESP32-S2 | 851,920 B | 19% | **100,492 B** |

The heap number is the one to watch. 100 KB against the ESP32's 280 KB, from
320 KB of SRAM against 520 KB, with stacks that are *already* inflated for
Xtensa's windowed ABI (see CLAUDE.md, "Every stack size in this tree is sized
for a Cortex-M3"). It fits today with no IMU and no WiFi running. It has not
been measured with either.

---

## 3. What changed in the code, and why

Four files. Every switch is on a **capability**, not a chip name, so a future
target selects the right path by itself.

### `pios/esp32/pios_servo.c` — LEDC backend

Gated on `SOC_MCPWM_SUPPORTED`. The MCPWM path is untouched for ESP32/S3.

The LEDC backend puts every channel on **one** shared low-speed timer, which is
what PiOS wants here anyway — `PIOS_Servo_SetHz()` on this port already applies
bank 0's rate globally, so separate timers would buy nothing.

LEDC duty is a **fraction of the period**, not a microsecond count, so `Set()`
stages microseconds and `Update()` converts:

```
duty = us * 2^bits * rate / 1e6        (64-bit; it overflows 32 inside the servo range)
```

Resolution is fine: 14 bits at 400 Hz is 2500 µs / 16384 = **0.15 µs per step**,
far finer than any ESC resolves, so nothing is lost against MCPWM's 1 µs tick.
The duty-resolution bits are computed from the rate at init and recomputed on
`SetHz`, backing off until the APB clock can actually divide to that rate.

**Honest difference from MCPWM.** MCPWM's `update_cmp_on_tez` makes every
channel adopt its new comparator value at the *same* period boundary. LEDC
latches per channel at that channel's next period. Because all channels sit on
one timer their periods are aligned, so worst-case skew is the few microseconds
`Update()` takes to walk four channels — not a period. Fine for PWM ESCs. If
DShot or tight sync ever matters on an S2, RMT is the peripheral to reach for.

A rate change invalidates every channel's duty even though its pulse width in
microseconds is unchanged, because duty is a fraction of the period. `SetHz`
recomputes them all.

### `pios/esp32/pios_esp32.h` — flight core

`PIOS_ESP32_FLIGHT_CORE` now derives from `portNUM_PROCESSORS` (which already
reflects `CONFIG_FREERTOS_UNICORE`): core 1 on dual-core parts, core 0 on the
S2. See [Traps](#6-traps) for why the old hardcoded 1 was worse than useless.

### `targets/esp32wroom/board_hw_defs.c` — pin map

Both maps now live side by side as `BOARD_PIN_*` / `BOARD_UART_*` macros under
`#if CONFIG_IDF_TARGET_ESP32S2`, instead of literals scattered through the file.

### `targets/esp32wroom/pios_board.h` — DSM guard

`PIOS_INCLUDE_DSM` is compiled out on the S2 for want of a third UART.

---

## 4. The S2 pin map

**NOT verified against a physical S2 Thing Plus silkscreen.** These are valid,
conflict-free GPIOs chosen so every driver initialises. Treat this as a
starting point for wiring, not as a wiring diagram — check the silkscreen
before you solder anything.

| Function | ESP32 | ESP32-S2 | why it moved |
| --- | --- | --- | --- |
| Status LED | 13 | 13 | — |
| IMU chip select | 14 | 14 | — |
| SPI SCLK | 5 | 5 | — |
| SPI MOSI | 18 | 18 | — |
| SPI MISO | 19 | 19 | — |
| IMU data ready | 32 | **33** | 32 is module flash on the S2 |
| Motor 1 (front-left) | 15 | **1** | regrouped clear of flash/strapping |
| Motor 2 (front-right) | 33 | **2** | 33 taken by data-ready |
| Motor 3 (rear-right) | 27 | **3** | 27 is module flash on the S2 |
| Motor 4 (rear-left) | 12 | **4** | 12's eFuse trick is ESP32-only |
| PIOS telemetry UART | UART0, 3/1 | **UART1, 16/17** | see below |
| Aux UART | UART2, 16/17 | defined, never initialised | only two UARTs |
| IDF console | UART1, 22/23 | **UART0, 43/44** | 22/23 do not exist on S2 |
| BOOT button | 0 | 0 | — |

Note the ESP32's GPIO12 motor-4 story — the `XPD_SDIO_FORCE` eFuse burn
described in README.md — is **ESP32-specific and does not carry over**. The S2
motor pins need no eFuse.

---

## 5. UART allocation: a bring-up compromise

The S2 has two UARTs. The ESP32 build wants three (telemetry, aux/DSM, console).

Current arrangement, chosen so the **boot log is readable** during bring-up:

- **UART0** (43/44, the devkit bridge) → IDF console.
- **UART1** (16/17) → PIOS telemetry / UAVTalk. Physically unconnected.
- **DSM** → compiled out.

This is deliberately backwards from what you want in flight. The ESP32 build's
hard rule — *the console stays OFF UART0 because log text interleaves into
UAVTalk frames and the GCS never links* (CLAUDE.md) — still applies. **Before
connecting a GCS, swap them**: telemetry to UART0, console to UART1, and read
the console with a second USB-serial adapter.

The real fix is the S2's **native USB**: run UAVTalk over USB CDC and both
hardware UARTs come free, which solves the DSM problem outright. That is the
single most valuable thing the S2 offers this port, and it is not done yet.

---

## 6. Traps

**Pinning to a core that does not exist fails SILENTLY.**
`xTaskCreatePinnedToCore(..., 1)` on a unicore build does not warn, it returns
a failure — and PiOS ignores the return value at every call site, so the task
simply never exists. It surfaces much later as a NULL task or queue handle, or
as a subsystem that quietly never runs. The shim in `pios_esp32.h` counts these
in `pios_esp32_task_create_failures`; read it in a debugger or core dump. This
is the one change that would have been most painful to debug and least visible
in a log.

**The generated `sdkconfig` pins the target.** cmake refuses to retarget over
it. Use a separate `-DSDKCONFIG=`, or you will be told the target does not
match and be tempted to delete the working ESP32 config.

**`sdkconfig.defaults` cannot be layered here.** It sets `CONFIG_IDF_TARGET`
and dual-core-only options. The S2 needs a standalone defaults file.

**Do not assume a GPIO exists.** 22-25 are absent on the S2 and 26-32 are
flash. Check `SOC_GPIO_VALID_GPIO_MASK` in the IDF for the part before
assigning a pin, rather than porting a number across from the ESP32.

**`PIOS_Assert()` is still a silent infinite spin** on this target (CLAUDE.md).
A failed `PIOS_ESP32_Servo_Init` would look exactly like a dead board with no
message. That the S2 reaches "init complete" is therefore real evidence the
LEDC backend initialised.

---

## 7. What boot looks like when it works

```
ESP-ROM:esp32s2-rc4-20191025
I (208) cpu_start: Unicore app
I (215) cpu_start: cpu freq: 240000000 Hz
I (270) heap_init: At 3FFD6880 len 00025780 (149 KiB): RAM
I (293) spi_flash: flash io: qio
I (318) main_task: Started on CPU0

[PIOS] NinjaPilot on ESP32: 1 core(s), silicon rev 0, 4096KB flash
[NinjaPilot] esp32wroom target starting
I (335) gpio: GPIO[13]| InputEn: 0| OutputEn: 1| ...
[BOARD] MISO(GPIO19) pulldown=0 pullup=1 : FLOATING -- nothing connected or the sensor has no power
[BOARD] no usable IMU on SPI3 (SCLK=5 MOSI=18 MISO=19 CS=14): WHO_AM_I=0xFF
I (2677) gpio: GPIO[33]| InputEn: 1| OutputEn: 0| ... Intr:1
[NinjaPilot] init complete, 100492 bytes heap free
I (2701) main_task: Returned from app_main()
```

Things worth reading in that: `Unicore app`; the port's own banner correctly
reporting `1 core(s)`; GPIO33 coming up as an interrupt input (the relocated
data-ready); reaching `init complete`; and `Returned from app_main()`, which is
normal — the module threads carry on.

The missing-IMU report is the **documented graceful path**, not a failure of
the port: `PIOS_ICM20602_Register()` is called unconditionally so module init
cannot hang, the fault is raised where UAVTalk can see it, and the board
refuses to arm. See CLAUDE.md.

**60-second soak:** one boot banner, zero panic/abort markers, zero
task-watchdog lines. That is meaningful because the task watchdog is armed at
2 s with `CONFIG_ESP_TASK_WDT_PANIC=y` — any registered flight task that
stopped checking in would have reset the board. None did.

---

## 8. What is NOT validated

Be blunt about this before anyone flies it.

- **No IMU was wired.** Nothing on the sensor, attitude, estimator or control
  path has executed. The 500 Hz data-ready path, the SPI burst read, the
  complementary filter — all unexercised on this silicon.
- **LEDC output was never scoped.** It initialises; no one has confirmed a
  1000-2000 µs pulse actually appears on GPIO 1-4, nor measured the real
  channel-to-channel skew against the analysis above.
- **The pin map is unverified against hardware.** Conflict-free by
  construction, not checked against a silkscreen.
- **WiFi has never been brought up on the S2.** This is the big one — see
  below.
- **No motors, no ESCs, no airframe.** Obviously.
- **RAM headroom is untested under load**: 100 KB free with no IMU and no WiFi.

---

## 9. Open questions and next steps

In the order I would do them.

1. **Wire an ICM-20602** to SCLK 5 / MOSI 18 / MISO 19 / CS 14 / DRDY 33 and
   confirm `WHO_AM_I=0x12`, then that the 500 Hz data-ready task and attitude
   filter run. This is the step that decides whether the S2 is flyable at all.
2. **Scope the LEDC output** on GPIO 1-4: pulse width, rate, and the real
   inter-channel skew.
3. **Bring up WiFi and measure contention.** The open question of the whole
   port. On one core, WiFi and lwIP contend directly with the control loop,
   with none of the isolation the ESP32 build relies on. The ESP32 measurement
   that justified going dual-core was a **5x jump in stabilization deadline
   warnings** when the network stack shared a core. Expect that back. Use the
   same bench-idle stab-warning metric so the numbers are comparable, and note
   CLAUDE.md's warning that timing bisects on this platform lie.
4. **Move UAVTalk to native USB CDC.** The S2's real advantage. It frees both
   UARTs (restoring DSM), removes the console-versus-telemetry conflict
   entirely, and sidesteps the CP2102 bridge. Probably also the cleanest answer
   to (3), since a board that does not need WiFi in flight does not care that
   it has one core.
5. **Verify the pin map** against a physical S2 Thing Plus silkscreen and
   redo the map for real wiring.
6. **Re-check stack sizes** against the smaller SRAM once the IMU and WiFi are
   in, using the failure mode described in CLAUDE.md (they do not report as
   stack overflows; they corrupt the heap or the ready-list).

---

## 10. Why the S3 is the better target

If the goal is moving off the original ESP32 rather than the S2 specifically,
the **ESP32-S3** is the right chip and this branch makes that easy:

- **Dual-core**, so the flight/network separation-by-silicon survives intact
  and the WiFi contention question in (3) never arises.
- **Has MCPWM**, so the motor driver needs no change at all — the existing
  MCPWM path is selected automatically by `SOC_MCPWM_SUPPORTED`.
- **Native USB** as a bonus, the same win as the S2.
- **3 UARTs** and 512 KB SRAM, so no DSM sacrifice and no heap squeeze.

The S2 is the only one of the three that is a downgrade for this workload. It
was worth doing because it forced the port's ESP32 assumptions out into the
open — capability-gated servo backend, core-count-aware task creation, a
parameterised pin map — and every one of those makes the S3 nearly a retarget
plus a pin map.
