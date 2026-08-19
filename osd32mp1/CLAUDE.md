# Working on the OSD32MP1-RED

Rules and traps for the Octavo OSD32MP1-RED bring-up. Each one cost real time
to learn — read before changing something, not after it breaks.

Companion docs: `README.md` (what this is, current state), `SKILLS.md` (the
commands). The flight-code rules live in
`../NinjaPilot-15.02.ninja/CLAUDE.md` and still apply once firmware is running
here.

---

## RULE: the BOARD REVISION picks the DTB, and getting it wrong looks like dead hardware

This board is **hardware revision V1.2**. Octavo's v3.0 image ships only the
**V1.1** device tree. They are not interchangeable — the Ethernet PHY changed:

| rev | PHY | interface | MDIO addr |
|---|---|---|---|
| V1.1 | (RGMII part) | RGMII | 3 |
| **V1.2** | **KSZ8051RNLU** | **RMII** | **7** |

Booting the V1.1 DTB on a V1.2 board gives `no phy at addr -1` and no
Ethernet, while the link LEDs still blink — because the LEDs are driven by the
PHY's own link detection, which works regardless of whether the SoC can talk
to it over MDIO. **Blinking link lights are not evidence the MAC is working.**

The fix was not a cable, a jumper, or a config: it was
`osd32mp1-red-v1_2-trusted-openstlinux-sdcard-v3_0_1.zip`, whose boot
partition carries `stm32mp157c-osd32mp1-red-v1_2.dtb`. Ethernet came up on the
first boot with it.

**The schematic says so outright** — `OSD32MP15x_RED_7x_sch-V1_2`, Rev 1.2
change list, item 6: *"Updated U10 (Ethernet PHY) to KSZ8051RNL."* The part
changed with the board revision, so the device tree had to as well. Item 4 of
the same list (*"Updated U20 (CAN IC) to TJA1441BTK"*) is the CAN transceiver,
for the same reason.

Two wrong theories were held along the way, both worth not repeating:
- "the PHY needs 50 MHz REF_CLK and isn't getting it" — plausible, and wrong;
  the user had physically disconnected the PHY during that test, so the
  evidence never supported it
- "a rescan needs a reboot" — disproved by `no phy at addr -1` appearing at
  ifup time

**Check the silkscreen revision against the DTB filename before debugging
Ethernet at all.**

## The gadget is currently EITHER a network device OR a console — and the cause is dwc2 FIFOs, NOT macOS

Measured 2026-08-15 against the running board:

| gadget functions | `/dev/cu.usbmodem*` | USB network |
|---|---|---|
| `ecm.0` + `acm.0` (either order) | yes | **no** — `AppleUSBECMData=0` |
| `ecm.0` alone | no | yes — host gets 192.168.7.x, board answers on .1 |
| `ncm.0` + `acm.0` | yes | no — both drivers attach, carrier never negotiates |

**CORRECTION.** This was first written up as "macOS will not bind both", which
is WRONG and was believed for several hours because the host-side evidence
(`AppleUSBECMControl=1`, `AppleUSBECMData=0`) is genuinely consistent with it.
The board's own kernel log gives the real answer:

    dwc2 49000000.usb-otg: dwc2_hsotg_ep_enable: No suitable fifo found
      dwc2_hsotg_ep_enable <- usb_ep_enable <- gether_connect [u_ether]
        <- ecm_set_alt [usb_f_ecm] <- composite_setup [libcomposite]

macOS did exactly the right thing — it selected ECM's data alt-setting — and
**the BOARD failed to enable the endpoint**, so no carrier ever came up and
`usb0` stayed at `no-carrier (configuring)`. The host was never the problem.

The mechanism is TX FIFO exhaustion in the dwc2 gadget controller. The device
tree pins the partitioning:

    g-rx-fifo-size     0x200
    g-np-tx-fifo-size  0x20
    g-tx-fifo-size     <0x100 0x10 ...>   one entry per IN endpoint

ECM (bulk IN + interrupt IN) plus ACM (bulk IN + interrupt IN) needs **four**
IN endpoints, and the available FIFO RAM / entry list does not stretch that
far. Adding functions is not free on this controller.

So "either/or" is a **current limitation, not a law** — extending
`g-tx-fifo-size` in the DTB is the fix worth trying if both are ever wanted at
once. Until then the shipped config chooses the console (`acm.0` + `ecm.0`),
because Ethernet already covers networking and the console survives any
network misconfiguration. Switching is one word — see `SKILLS.md`.

**Method lesson:** host-side symptoms told a coherent, wrong story. The board's
`dmesg` had the answer the whole time and was not read until much later. When
two devices disagree, read BOTH logs before concluding which one is at fault.

### Corollary: do NOT read USB descriptors before the image is actually running

Descriptors were dumped after flashing but before the new image had booted,
which produced the confident and wrong claim *"this gadget was never RNDIS."*
The V1.2 OpenSTLinux rootfs ships `func_eth=rndis.0`, and RNDIS is a Microsoft
protocol macOS cannot use at all. A descriptor dump only describes whatever
gadget is bound **right now**.

Related: this image's ACM advertises `bInterfaceProtocol 0x01`, so macOS binds
it natively and creates `/dev/cu.usbmodem*`. The older Debian image advertised
`0xff` and macOS refused it, which is why `usb_console.py` (libusb) exists.
**These two images behave oppositely — do not carry conclusions between them.**

## RULE: edit disk images offline as FILES, and fsck every time

macOS cannot mount ext4 and `/dev/disk*` needs root, but a raw image is just a
file you own, so the whole edit runs unprivileged: parse the GPT for byte
offsets, `dd` the partition out, `debugfs` it, `e2fsck`, inject it back.
`gpt.py` and `part.py` do this; never hardcode offsets.

Two failure modes, both hit for real:

- **`write` + `ln` + `rm` in one debugfs session corrupted the image** — the
  operations collided on one inode (26349). **`cd` into the target directory
  and `write` directly.** No hard-link/remove dance.
- A structural error introduced here does not announce itself; it shows up
  much later as a card that will not boot. **`e2fsck -fy` after editing, and
  again after injecting.** Both must come back with zero repairs.

## dropbear on this image: two gotchas that both read as "SSH is broken"

- **It offers only the SHA-1 `ssh-rsa` host key and pubkey algorithm.**
  OpenSSH 8.8+ disables those by default, so a correct setup still dies with
  `no matching host key type found. Their offer: ssh-rsa`. Both
  `HostKeyAlgorithms=+ssh-rsa` and `PubkeyAcceptedAlgorithms=+ssh-rsa` are
  required, and are in `~/.ssh/config` under `Host osd32mp1`.
- **root ships with an EMPTY password**, and dropbear refuses blank-password
  authentication. `dropbear.socket` being enabled is therefore not sufficient
  to log in. The edited image installs an `authorized_keys` and sets a real
  hash.

Note `iptables.service` and `ip6tables.service` are enabled but
`/etc/iptables/iptables.rules` is **empty** — the firewall was suspected and
is not a factor.

## TRAP: tearing down the gadget at runtime kills the console permanently

`serial-getty@.service` carries `BindsTo=dev-%i.device`. When the USB gadget is
unbound, `/dev/ttyGS0` disappears, systemd treats that as a *clean stop*, and
`Restart=always` therefore never fires. The getty stays dead even after the
device returns.

This only bites when rebuilding the gadget live (as the ECM/ACM experiments
did). A normal boot is fine. Recovery is `systemctl restart
serial-getty@ttyGS0`, or a reboot — and a reboot is usually better, because
repeated live teardowns also wedge the ACM endpoint itself, at which point
even opening `/dev/cu.usbmodem*` hangs with nothing holding the port.

The image also ships a drop-in with `StartLimitIntervalSec=0` and
`RestartSec=2`, because `ttyGS0` does not exist until `usbotg-config.service`
binds at `multi-user.target` — without it systemd burns its default
5-starts-in-10s budget and gives up before the node ever appears.

## RULE: `console=` ORDER on the kernel cmdline is load-bearing

`extlinux.conf` reads:

    console=ttyGS0,115200 console=ttySTM0,115200

ttyGS0 goes **first on purpose**. The *last* `console=` becomes `/dev/console`,
and ttyGS0 only exists while USB is plugged in and the gadget is bound. Making
a disappears-when-unplugged device primary would throw systemd's output away
and cost the UART console too.

## Octavo's eMMC deploy tarball is genuinely truncated (this was challenged, so: proof)

Two independent downloads of `osd32mp1-red-emmc-deploy.tar.xz`:

    size   83886080 bytes  (both)  = exactly 80 MiB
    md5    ae6fbd99fc1bf313836775df042b0dd6  (both, IDENTICAL)
    xz -t  "Unexpected end of input", exit 1

Byte-identical output from two separate transfers rules out a network fault —
network corruption does not reproduce bit-for-bit. xz verifies a CRC64 per
block plus a stream footer, so it is detecting a genuinely absent end of
stream. The bootloaders inside survive because they sit at the front of the
tar; only the rootfs was cut off. This is why the forum recovery procedure
fails for people who follow it.

**The scepticism was still right in principle** — "the vendor's file is
broken" is a claim that should be proven, not asserted, and the proof above is
what a challenge is for.

## The board cannot be bricked

The STM32MP1 ROM bootloader is in silicon. It always offers USB-DFU
(`0483:df11`) when it cannot boot the selected medium, and the ROM has **no
eMMC write path** — DFU phase `0x01 fsbl1-boot` loads TF-A into SYSRAM only. A
power cycle always returns a clean recovery state. Experiment freely.

## Verify claims; a self-test caught a real bug here

The `$6$` password hash was generated by a hand-written SHA-512 crypt
(`sha512crypt.py`) because macOS has neither `crypt(3)` `$6$` support nor
`openssl passwd -6`. The implementation was **wrong on the first attempt** —
Drepper's custom base64 packs the first index as the *most* significant byte,
and encoding it little-endian produces a plausible-looking but invalid hash.
The official spec test vector caught it immediately. `sha512crypt.py` refuses
to emit a hash unless that vector passes; keep it that way.

Same lesson, cheaper: a LAN scan turned up a "new" host at `192.168.0.40` that
looked like the board and was a **printer** (ports 80/443/**631 IPP**). One
port scan separated a plausible story from the truth. The board was
identifiable positively — avahi publishes hostname `osd32mp1-red-v1_2` as
`osd32mp1-red-v12` (mDNS drops the underscore).

## Hardware facts worth not re-deriving

- **armv7l, 2 cores, ~426 MB usable RAM**, kernel 5.10.10, OpenSTLinux 3.1
- **`gcc`/`g++` 9.3.0, `make` 4.3, `python3` 3.8.2 are present**
- **`git` and `rsync` are ABSENT** — ship source as a tar over ssh, and expect
  `version-info.py` to need the stub treatment (`0xNone commit_hash_prefix` is
  the symptom of a missing git worktree)
- `can0` already exists as a SocketCAN interface
- DHCP lease moves (`.167` → `.90` across one reboot) — **always address the
  board by its mDNS name**, never a remembered IP
- power: 5V ≥2A, barrel jack 5.5mm/2.5mm, or USB-C with jumper JP3 at 1-2

## Sensor wiring: the two mistakes that cost hardware, and the one that costs a day

- **5V/GND swapped on the Matek JST-GH-4P is destructive.** CANH/CANL swapped
  is harmless — it simply will not communicate. So verify the power pair with
  a multimeter and treat the signal pair as recoverable.
- The board's CAN connector **JP8** (sheet 7) is `4=NC, 3=CANH, 2=CANL, 1=GND`
  and carries **no power**.
- **There are TWO 5.2 V rails and they are not interchangeable.** The CAN
  transceiver runs on `PMIC_BSTOUT_5P2V`; the RPi and mikroBUS headers run on
  `PMIC_VBUSOTG_5P2V/DET`. The header rail is the **USB-OTG VBUS** output,
  which the PMIC normally enables to *source* VBUS in host mode — and we run
  the port in **device/gadget mode**. So `JP7` pin 10 may simply be dead in our
  configuration. **Measure it, booted as we actually run it, before wiring
  anything to it.** A separate bench 5 V with grounds tied avoids the question
  entirely; CAN needs a common reference, not a shared rail.
- **`R48` (120 Ω CAN termination) is DNP — the board can never terminate
  itself.** A CAN bus needs **exactly two** terminators, one at each physical
  END; middle nodes stay open. The Matek `120R` jumpers are open from the
  factory. Wiring the board as the MIDDLE node (`L431 → board → L4-3100`) makes
  the DNP correct by construction and needs no soldering.
  **Check by measuring CANH–CANL with power off: ~60 Ω is right**, 120 Ω means
  one terminator, 40 Ω means three (a real fault — it overloads the drivers).
  Under-termination is the dangerous case because a short bench harness works
  anyway and only fails at airframe cable lengths.
- **VBAT (header `JP24`) is NOT a supply.** It is the RTC / backup-SRAM domain
  *input*, for a battery or supercap. `JP4` is not a 5 V tap either — it sits
  on `PMIC_VOUT4_3P3V` and is DNP.
- Source of truth for all of the above is the schematic
  `OSD32MP15x_RED_7x_sch-V1_2` (sheets 11–12), not the standard RPi/mikroBUS
  pinouts — Octavo's public web docs do not give pin numbers at all.
- **The frame convention is FRD body → NED world**, per `gazebo_bridge.py`'s
  `Q_FLU2FRD` / `Q_ENU2NED`. Every real sensor must be rotated into FRD before
  injection. This is the single most likely source of sign bugs in the whole
  sensor effort, and a sign error reads as a control bug, not a wiring bug.

## SETTLED: DroneCAN bring-up, and the two things that make a healthy bus look dead

Both Matek nodes are up and publishing (2026-08-15):

    node 124  org.ardupilot.MatekL431-Periph   gnss.Fix2 @ 5 Hz
    node 125  org.ardupilot.MatekL431-GPS      ahrs.MagneticFieldStrength @ 25 Hz

Mag reads `[0.2617, -0.0750, 0.3547]` gauss = **0.447 G / 44.7 µT**, inside
Earth's 25–65 µT range and stable to ±0.03 µT — a real sensor, sanity-checked
by magnitude rather than by "numbers appeared".

Getting there hit two failures that both present as "the bus is dead":

**1. No termination anywhere.** `R48` is DNP on the board and the Matek `120R`
jumpers ship open, so the bus had ZERO terminators. Signature, and it is
distinctive: line activity present, **zero decodable frames at EVERY bitrate**
(1M/500k/250k/125k tried), rx error counter pinned at **127**. A bitrate
mismatch does not look like this — one rate would usually work. After
soldering one terminator: `ERROR-ACTIVE`, `berr-counter tx 0 rx 0`, frames
immediately.

Before blaming the bus, prove the controller with a loopback — it takes
seconds and cleanly separates SoC-side from wire-side:

    ip link set can0 up type can bitrate 1000000 loopback on
    cansend can0 123#DEADBEEF        # candump should echo it back

Also worth knowing: `can0` is `4400e000.can` (FDCAN1); its DT node has only
pinctrl and **no standby GPIO**. The transceiver's `S` pin is on **PG3**
(gpiochip6 line 3), which sits unused as an input reading **0** — i.e. the
TJA1441 is already in normal mode. Standby is NOT a candidate cause here; that
was checked and ruled out.

**2. No dynamic node-ID allocator.** AP_Periph nodes boot anonymous and
broadcast `dynamic_node_id.Allocation` until something grants them an ID —
publishing **nothing else** in the meantime. On an aircraft the flight
controller is the allocator; on this bench nothing was, so the nodes retried
forever and the bus looked alive-but-useless. `dronecan_allocator.py` fills the
role and persists grants in a small DB so IDs survive reboots.

### Anonymous frames use a DIFFERENT CAN-ID layout

This produced a confident wrong answer before it was caught. A normal message
puts a 16-bit type in bits 8–23, but an anonymous frame has no source node ID
to identify the sender, so:

    normal     bits 8-23  = message type id (16 bits)
    anonymous  bits 8-9   = message type id (2 bits - only ids 0..3 exist)
               bits 10-23 = discriminator derived from the unique id

Decoding an anonymous frame with the normal layout yields plausible-looking
garbage — it reported "msg 12537" and "msg 39521" for what were really type 1
(Allocation) from two different senders. **Those two bogus numbers were the
only evidence that a second node existed**, so the misdecode was concealing the
device count as well as the message type. Group anonymous senders by
discriminator, never by node id (they are all 0).

## TRAP: read the MODULE's design, not just the chip's datasheet

The GY-63 refused to answer on I2C while the MPU9150 on the SAME bus worked
perfectly - proving bus, pull-ups, 3.3 V and SDA/SCL orientation were all fine.
Two wrong theories were chased before the real one:

1. "PS is floating so it is in SPI mode" - plausible (see below, it IS a real
   trap) but jumpering PS and CSB changed nothing.
2. "SDA/SCL are swapped" - **wrong by construction**: another device on the same
   bus still answered, which proves the orientation. Swapping would only have
   broken what worked. Do not reach for this when a second device is happy.

**The actual cause is the module, not the chip.** A GY-63 carries a
**MIC5205 3.3 V regulator plus level-shifting MOSFETs** and is designed to be
fed **5 V**. A MIC5205-3.3 needs ~3.47 V in to regulate, so at 3.3 V it sits in
dropout: the internal rail sags, the level shifters (gate-referenced to that
sagged rail) never switch, and the part is electrically absent from the bus
while its power LED - wired across the INPUT - still cheerfully lights.

"MS5611 is not 5 V tolerant" is true of the die and **actively misleading about
the board**. Always check whether a breakout has its own regulator and
shifters before choosing a supply voltage.

Beware the obvious fix: powering a GY-63 from 5 V puts 5 V-referenced pull-ups
on the bus, which would endanger the 3.3 V-only MPU9150 sharing it. Test such a
module ALONE, and measure SDA idle voltage before letting them coexist.

**Preferred replacement: Adafruit BMP388.** Its breakout has a 3.3 V regulator
*and* level shifting explicitly rated for 3 V or 5 V logic, so it works on this
bus as-is; 0.1 m altitude noise, addr 0x77 (0x76 with SDO low). Note this tree
has `pios_ms5611.c` but NO BMP388 driver, so the native-firmware path would
need writing later - irrelevant to the Python bridge.

### The PS/CSB trap is still real, just not what bit us here

Symptom: power LED on, `i2cdetect` finds nothing at 0x76 or 0x77, wiring looks
perfect, and another device on the SAME bus (the MPU9150 at 0x68) works fine -
which proves the bus, pull-ups, 3.3 V and SDA/SCL orientation are all correct.

The MS5611 has a hard **protocol-select input**:

    PS  HIGH            -> I2C
    PS  LOW or FLOATING -> SPI   <-- ignores I2C entirely, never ACKs

Many GY-63 boards break `PS` out without pulling it anywhere, so it floats and
the part sits in SPI mode. No amount of correct SDA/SCL wiring helps.

    PS  -> 3.3 V     required for I2C
    CSB -> GND       address 0x77   (3.3 V -> 0x76)   must NOT float
    SDO -> unconnected              (SPI MISO, unused in I2C mode)

`CSB` polarity feels inverted because the datasheet address is `111011C` where
**C is the COMPLEMENT of CSB** - pulling CSB low yields 0x77.

Do not chase this by swapping SDA/SCL: if another device on the same bus still
answers, the bus orientation is proven correct and swapping only breaks what
works. A power LED proves nothing - it sits across the supply rail and lights
whenever VCC is present, regardless of protocol mode or whether the sensor is
soldered to the bus at all.

## MEASURED: the CAN bus is 1.4% loaded and its timing is navigation-grade

300 s sample, 29,401 frames, kernel `SO_TIMESTAMP` (not `time.time()` in the
read loop - Python's own scheduling jitter on this 2-core armv7 is the same
order as the jitter being measured):

    frames            98.0 /s
    on-wire           12.3 kbit/s nominal, 14.5 kbit/s worst-case stuffing
                      = 1.23 - 1.45 % of 1 Mbit
    headroom          ~98.6 % free

| transfer | Hz | period | sd | max gap | frames/msg |
|---|---|---|---|---|---|
| `ahrs.MagneticFieldStrength` (n125) | 25.00 | 40.0 ms | **0.5 ms** | 53.7 ms | 1 |
| `gnss.Fix2` (n124) | 5.00 | 200.0 ms | **2.8 ms** | 216.3 ms | 10 |
| `gnss.Auxiliary` (n124) | 5.00 | 200.0 ms | 0.7 ms | 201.8 ms | 3 |
| vendor 20003 (n124) | 5.00 | 200.0 ms | 1.9 ms | 212.8 ms | 1 |
| `NodeStatus` x3 | 1.00 | 1000 ms | ~1 ms | ~1002 ms | 1 |

Jitter is **1.25 % of period for the mag and 1.4 % for GPS**, and across ~12,900
transfers the worst gap was 1.34x nominal - i.e. **no dropouts at all**. Both
are comfortably usable for navigation; 5 Hz GPS is what ArduPilot/PX4 use
anyway.

### MEASURE TRANSFERS, NOT FRAMES

The first run of this reported "gnss.Fix2 50 Hz, sd 58.9 ms, jitter 295 %" and
that was **pure artifact**. A multi-frame DroneCAN transfer emits its frames
back to back (~0.1 ms apart) then nothing until the next message, so timing raw
frames averages two completely different populations. Count a transfer only
when the tail byte's **start-of-transfer bit (0x80)** is set. Same data, same
run: 5.00 Hz, sd 2.8 ms, verdict OK.

### Frame economics, now empirical rather than estimated

Measured **147.9 bits/frame** worst case = **148 us at 1 Mbit**, and Fix2 is
**10 frames/transfer** = 1.48 ms per message. So a `RawIMU` on this bus:

| rate | bus |
|---|---|
| 100 Hz | 14.8 % |
| 200 Hz | 29.6 % |
| 500 Hz | **73.9 %** - FITS, but see below |
| 1000 Hz | **147.9 %** - exceeds the bus |

**CORRECTION (user called it): "no headroom left" overstated the capacity
argument.** 73.9 % + today's 1.2 % fits on the wire. The real arguments
against gyro-over-CAN are latency and budget, not capacity:
- a 10-frame transfer is **1.48 ms of serialization** - the sample cannot be
  consumed until its last frame lands, so the gyro-triggered inner loop eats
  ~75 % of its 2 ms period as pure transport delay, before queueing. At 74 %
  utilisation, queueing multiplies waits ~4x on top.
- the plan puts MOTOR COMMANDS on this same bus. ESC/actuator streams at
  200-400 Hz cost 6-12 %+; the gyro stream would spend the margin the
  control OUTPUT path needs - and the output path cannot tolerate jitter.
- two IMUs at 500 Hz (MPU-9150 + ICM-20602) genuinely do not fit: 148 %.
A REDUNDANT gyro stream at 100-250 Hz over CAN (15-37 %) is perfectly
reasonable; the PRIMARY 500 Hz gyro belongs on SPI/local for latency, not
for bandwidth.

This confirms the earlier back-of-envelope estimate (~1.35 ms/sample) with real
numbers, and settles it: `PIOS_SENSOR_RATE` is 500 Hz, so a DroneCAN gyro would
consume three quarters of the bus and still fight the existing traffic for
arbitration. The gyro belongs on local SPI. Slow sensors are free - a 20 Hz
baro would cost ~0.3 %.

## USB host port works — and `usb33` is a RED HERRING

The USB-A host port enumerates normally:

    usb 3-1: new full-speed USB device number 2 using ohci-platform
    cdc_acm 3-1:1.0: ttyACM0: USB ACM device

**Do not diagnose port power from the `usb33` regulator.** It reads
`state=disabled users=0` even while a device is happily enumerated and
streaming — it is not a usable signal for "is the port powered". Time was
spent suspecting it before a device was simply plugged in. The honest test is
`dmesg`: a connect event appears, or it does not. If it does not, measure VBUS
on the port with a meter rather than reading regulator sysfs.

The Klipper accelerometer identifies as **`1d50:614e`**, manufacturer `Anchor`,
product `Rampon` → `/dev/ttyACM0`. It is **silent until spoken to**, which is
correct: Klipper firmware speaks a custom binary protocol (sync-framed, CRC16),
and the host must first fetch the MCU's compressed *data dictionary* before it
can issue any command. So "no output on open" is health, not a fault — but it
also means reading it needs a real protocol implementation, not a serial read.
That keeps it in its documented role: an independent vibration reference, not
a flight sensor.

## SOLVED: reading the KUSBA (Klipper protocol) — four traps, all silent

`klipper_probe.py` (transport + dictionary) and `klipper_accel.py` (ADXL345
streaming) talk to the KUSBA with no Klipper install. Measured 2026-08-15:
**3190 samples in 4 s at 798 Hz**, `DEVID = 0xE5` on `spi0`.

The device is a **KUSBA v2**: ADXL345 on an RP2040, stock Klipper firmware,
`1d50:614e` / `Anchor` / `Rampon`, dictionary reports `MCU rampon_anchor`,
`CLOCK_FREQ 1000000`, 17 commands.

Every failure mode here looks like "dead device", so they are worth knowing:

- **The MCU's expected sequence number PERSISTS across host connections.** It
  is whatever the previous client left it at, NOT 0. Guess wrong and every
  block is silently ignored with no error — indistinguishable from unplugged.
  **Sweep 0..15 to discover it**, then track the value the MCU echoes in each
  reply. This cost a full debugging round: seq 0 worked, then the next run
  failed because the first run had advanced it to 1.
- **Send a run of sync bytes (0x7E) before the first command.** The MCU
  discards input until a sync boundary, so if its parser is mid-garbage-block
  your first well-formed block is eaten as that block's tail.
- **A zero-length payload is a bare ACK block, not an error.** Assuming at
  least one message raises IndexError on every ack.
- **One block can carry SEVERAL messages back to back.** Decoding only the
  first silently drops data — including sensor samples.

Command IDs are **not fixed**; they are assigned per firmware build and
published in the zlib-compressed JSON dictionary fetched via `identify`
(command id 1, the only guaranteed-constant one). Drive everything from the
dictionary — `klipper_accel.py` builds its codec from it at connect time.

**Accuracy caveat:** magnitude at rest reads **0.912 g**, ~9% low. That is
uncalibrated ADXL345 zero-g offset (spec is ±150 mg/axis typical) plus
sensitivity tolerance, not a decode bug — the axes are stable to ~0.05 m/s²
and the vector direction is consistent. Fine for **relative** vibration work,
which is this device's documented role; it would need calibration before any
absolute use.

## What the Matek L431's I2C port CAN and CANNOT drive

From `MatekL431-Periph/hwdef.dat` - the same authority that settled the
IST8310 question:

    define AP_PERIPH_GPS_ENABLED 1      define AP_PERIPH_MAG_ENABLED 1
    define AP_PERIPH_BARO_ENABLED 1     define AP_PERIPH_AIRSPEED_ENABLED 1
    define AP_PERIPH_BATTERY_ENABLED 1
    BARO    SPL06     I2C:0:0x76
    COMPASS QMC5883L  I2C:0:0xd

**There is NO `AP_PERIPH_IMU_ENABLED` and no IMU driver of any kind** - no
AP_InertialSensor, no MPU/ICM/Invensense. So an **MPU9150 on that JST port is
invisible**, exactly like the IST8310, and for the same reason: no code to
talk to it. Rebuilding AP_Periph with IMU support would still be the wrong
transport - measured on this bus, RawIMU at 500 Hz costs 74 %.

**CORRECTED 2026-08-15 against the shipped build's own `features.txt`** (from
https://firmware.ardupilot.org/AP_Periph/latest/MatekL431-Periph/, commit
a824813): the earlier claim here that "the driver list is exact: SPL06, not
MS5611, BMP280 or anything else" was WRONG. It was inferred from the hwdef's
`BARO SPL06 I2C:0:0x76` line, which declares the ONBOARD baro - not the set of
drivers compiled in. The real list is broad:

    AP_BARO_BMP280_ENABLED   AP_BARO_BMP388_ENABLED   AP_BARO_BMP581_ENABLED
    AP_BARO_MS5611_ENABLED   AP_BARO_MS5607_ENABLED   AP_BARO_MS5637_ENABLED
    AP_BARO_SPL06_ENABLED    AP_BARO_DPS280_ENABLED   AP_BARO_FBM320_ENABLED
    AP_BARO_BMP085_ENABLED   AP_BARO_LPS2XH_ENABLED
    AP_BARO_PROBE_EXTERNAL_I2C_BUSES   <- probes external buses too

So the L431 CAN drive an MS5611, a BMP280 or a BMP388 on its I2C port. The
GY-63 would have worked there. Read `features.txt` from the firmware server
before claiming what a build supports - the hwdef alone does not say.

**SUPERSEDED - put the baro on the board's own I2C instead.** There is no such
thing as a standalone DroneCAN barometer to buy (baro is always bundled into a
combo node - mRobotics KitCAN, Beyond Robotix AUAV, CubePilot Here 2), the
L431 route would need an SPL06 specifically, and the MS5611 already on the
bench needs no purchase at all. It also has a driver in this very tree:
`flight/pios/common/pios_ms5611.c`, 486 lines, I2C addr 0x77, already used by
the coptercontrol/oplinkmini targets. Wire it to `/dev/i2c-3` alongside the
MPU9150.

So: **gyro goes on the board's own I2C/SPI, baro goes on the CAN node.** Fast
and latency-critical local; slow and latency-tolerant over CAN.

## CLOSED — ignore the IST8310 entirely

The GPS board carries an IST8310 that this setup will never use, and it is
**not a problem to solve**. The AP_Periph image compiles only RM3100 and
QMC5883L backends with `HAL_COMPASS_MAX_SENSORS 1`, so a correctly wired
IST8310 still never replies. That is settled; do not re-diagnose it, do not
rebuild AP_Periph for it.

**The mag we actually use is the RM3100 on node 125** — better by an order of
magnitude (12.2 nT quantisation vs ~300 nT) and already publishing at 25 Hz.
If a magnetometer question comes up, it is about node 125, not the IST8310.

## DONE: fw_simposix builds and runs on OpenSTLinux, fed by REAL sensors

2026-08-15. `fw_simposix.elf` (ARM EABI5, 2.2 MB) built natively on the board
and running under systemd as `fwsimposix.service`, taking sensors ONLY from
`sensor_bridge.py` over UAVTalk/UDP:9000:

    bridge sent  mag +14.7,-19.1,+35.9 uT  -> FW MagSensor  +146.5,-191.2,+359.1 mG
    bridge sent  accel +1.95,+1.07,+8.49   -> FW AccelSensor  +1.99,+0.99,+8.64
                                            -> FW AttitudeState Roll -172.5 Pitch +11.9

The gauss->milligauss conversion checks exactly (14.7 uT = 0.147 G = 147 mG),
and `gyroupdates` was a flat **0** before the bridge started - with
`NINJAPILOT_EXTERNAL_PHYSICS=1` there is no other sensor source, so those
numbers can only have come from the RM3100 on CAN and the ADXL345 on USB.

### The four things the build needed on this image

1. **`package/`** is a separate top-level dir - `Makefile:727` includes
   `package/$(UNAME).mk` and the build dies without it.
2. **`QMAKE=true` PLUS a no-op `build/uavobjgenerator/Makefile`.** There is no
   Qt here. The `uavobjgenerator` target runs qmake *and then* `$(MAKE)` in
   that directory, so stubbing only qmake still fails. UAVObject sources are
   pre-generated elsewhere into `build/uavobject-synthetics` (215 files).
3. **`git`** from the ST feed - `version-info.py` shells out to it, and
   without it you get the `0xNone commit_hash_prefix` failure. A local
   `git init` + one commit is enough.
4. **A non-root build user.** `Makefile:85` refuses to run as root unless
   `FAKEROOTKEY` is set. Creating a `build` user is the honest fix; the check
   exists to stop root-owned artifacts.

### TRAP: `pkill -f fw_simposix` kills your own SSH session

Three launches "silently failed" before this was spotted. `pkill -f` matches
the FULL command line, and an ssh command that launches
`.../fw_simposix.elf` contains that string - so pkill killed the shell that
was about to start the firmware. The `[f]w_simposix` bracket trick does NOT
help, because the binary path in the same command line still matches. Use
`pkill -x fw_simposix.elf` (exact process NAME), or just `systemctl stop`.

Run it under systemd, not `nohup`/`setsid` over ssh - backgrounded processes
did not survive the session:

    systemd-run --unit=fwsimposix --working-directory=/usr/local/ninja/fcwd \
      -E NINJAPILOT_EXTERNAL_PHYSICS=1 \
      /usr/local/ninja/src/build/fw_simposix/fw_simposix.elf

### What this does NOT yet do

`AttitudeState` Roll reads **-172 deg** because the KUSBA is loose on the
bench in an arbitrary orientation - that is the mounting rotation caveat, not
a bug. Yaw barely moves because **GyroSensor is zeros**, and `rateupdates`
stays negative because the inner loop cannot close without a real gyro. Fix
is the ICM-42688-P Click on mikroBUS SPI.

## Do NOT re-litigate: SimPosix already builds and runs here

The port was proven on the earlier Debian image — `fw_simposix.elf` built
natively on armv7l and ran with full PiOS/FreeRTOS init and an LED heartbeat,
EXIT=0. The one genuine portability bug found was in
`flight/pios/inc/pios_posix.h`: `#define false FALSE` sat *outside* the
`#ifndef __cplusplus` guard. macOS hides this because its system headers define
TRUE/FALSE; glibc does not, so it only appears when building for Linux. Nothing
architecture-specific about it.

## MEASURED: SCHED_FIFO is the difference between flyable and not

The FreeRTOS Posix port makes every task a pthread, so each task wake-up
inherits the host scheduler's latency. Measured with `rt_jitter.c` (C, not
Python — an interpreter's overhead would be indistinguishable from scheduler
latency), `clock_nanosleep(TIMER_ABSTIME)` on `CLOCK_MONOTONIC`, `mlockall`
held, 10 000 wake-ups at 500 Hz = `PIOS_SENSOR_RATE`. "Critical" is the
firmware's OWN threshold: `innerloop.c` calls 3 missed gyro updates critical.

| configuration                     | worst late | vs period | >3 periods |
|-----------------------------------|-----------:|----------:|-----------:|
| SCHED_OTHER, idle                 |  18.254 ms | 9.1x      | 0.310 %    |
| SCHED_OTHER, 2 busy cores         |  18.625 ms | 9.3x      | 5.400 %    |
| **SCHED_FIFO 50, idle**           | **0.212 ms** | 0.1x    | **0 %**    |
| **SCHED_FIFO 50, 2 busy cores**   | **0.233 ms** | 0.1x    | **0 %**    |
| SCHED_FIFO 50 + performance gov   |   0.244 ms | 0.1x      | 0 %        |

Two things follow, and only two:

1. **At default priority this cannot fly.** An 18 ms stall is 9 missed gyro
   samples; 0.31 % of periods breach the firmware's own critical threshold
   even with the machine IDLE. Under load it is 5.4 %.
2. **`chrt -f 50` fixes it completely** — 78x better tail, zero breaches, and
   it does NOT degrade under a fully loaded machine. This is the single
   highest-value change on the board and it is one word on a command line.

The `ondemand` -> `performance` governor made no measurable difference: the
A7s were already pinned at 650 MHz (`scaling_cur_freq` reads 650000 either
way). Do not bother; it is not the lever.

### TRAP: do not fork() load children from a SCHED_FIFO parent
First run showed 12 SECONDS of lateness under FIFO+load, which is nonsense.
Cause: `fork()` inherits the scheduling policy, so the busy children were also
FIFO 50, and FIFO is run-to-completion — they never yielded, and the measured
loop only ran when the kernel's RT throttle (`sched_rt_runtime_us` 950000 of
1000000) forced a break. 12 s of starvation per 20 s run is exactly that 95 %
duty. `rt_jitter.c` now drops children to SCHED_OTHER explicitly.

The artifact carries a REAL warning: once the flight code runs at RT priority,
any FreeRTOS task that busy-loops or blocks starves every other task, because
the Posix port already serialises tasks. RT throttling is then the only thing
between you and a dead scheduler.

## The FreeRTOS scheduler thread burns a whole core, always

`ps` shows `Scheduler` at 98.5–104 % CPU permanently — that is the Posix port
spinning, not the flight code working. On a 2-core board HALF the machine is
gone the moment fw_simposix starts, before any sensor arrives. Budget for one
core, not two, and keep the bridge on the other.

## The real limit is the SENSOR PATH, not the scheduler

With FIFO the scheduler contributes 0.2 ms of jitter. The transport
contributes far more, and that is where a real-world flight argument has to be
made:

- firmware WANTS `PIOS_SENSOR_RATE` = 500 Hz gyro
- MPU-9150 over I2C in the bridge is configured 200 Hz, and DELIVERED
  4276 objects in 30 s = **142.5 Hz** — a 3.5x shortfall against what the
  inner loop expects
- every sample crosses: I2C read -> Python process -> UDP loopback -> UAVTalk
  parse. Each hop adds jitter that `rt_jitter` does NOT capture.

So: scheduling is a SOLVED problem here (one `chrt`). Sensor delivery rate and
jitter are NOT, and no amount of RT priority fixes them.

## CORRECTION: the UDP bridge is a Gazebo artifact, not the sensor path

Do not measure "sensor latency" through `sensor_bridge.py`. That path
(I2C -> Python -> UDP loopback -> UAVTalk) exists because Gazebo SITL needed an
external physics producer. On real hardware the correct pipeline is:

    I2C  -> PIOS driver -> UAVTalk        (gyro/accel, /dev/i2c-3)
    CAN  -> PIOS driver -> UAVTalk        (GPS, mag, baro, and PWM OUT to motors)

UAVTalk over UDP is one *consumer* of the output, and on Linux it does not even
have to be UDP - a unix socket or shm IPC is available now. Any figure quoted
from the bridge (e.g. the old "142.5 Hz gyro") measures the SITL scaffolding,
NOT the board.

## MEASURED: the gyro bottleneck is the I2C CLOCK, not FreeRTOS

14-byte burst read of MPU-9150 `ACCEL_XOUT_H..GYRO_ZOUT_L` - the exact
transaction a PIOS driver issues once per sensor period - from C on the board
(`i2c_rate.c`), 5000 reads:

| priority     | median | p99 | worst | blew the 2 ms budget |
|--------------|-------:|----:|------:|---------------------:|
| SCHED_OTHER  | 1740.7 us | 3184.8 us | 14755.6 us | 927 (18.54 %) |
| SCHED_FIFO 50| 1679.3 us | 1802.5 us |  2034.2 us |   1 (0.02 %)  |

**1.68 ms for one gyro read = 84 % of a 500 Hz period.** Cause: `/dev/i2c-3`
(I2C5, `i2c@40015000`) has NO `clock-frequency` in the DTB, so the stm32f7-i2c
driver falls back to the **100 kHz** default. Only i2c-4 (`5c002000`, the PMIC
bus - unusable for sensors) was given 400000.

The arithmetic confirms it exactly, so this is not a guess:
- reg-write txn: START + addr(9b) + reg(9b) + STOP ~ 20 bits ~ 200 us
- read txn: START + addr(9b) + 14x9b + STOP ~ 137 bits ~ 1370 us
- + inter-transaction gap = **~1.68 ms measured**. At 400 kHz: **~420 us**.

### The fix (staged, needs a reboot to take effect)
`fdtput` adds the one missing property; `dtc` is in ST's feed as `dtc dtc-misc`
(NOT `device-tree-compiler`, and `apt` needs a sane PATH or dpkg errors):

    fdtput -t i <dtb> /soc/i2c@40015000 clock-frequency 400000

Verified minimal: 449 nodes before and after, identical dtc warning set (8),
and the ONLY dts diff is the added line. On the board:
- `/boot/stm32mp157c-osd32mp1-red-v1_2.dtb.orig` - untouched backup
- `/boot/stm32mp157c-osd32mp1-red-v1_2.dtb.400k` - patched, NOT yet installed

Expected after: ~420 us/read = 21 % of a 2 ms period, i.e. transport stops
being the constraint.

## Reference point: STM32F4 uses SPI, and that is the real gap

OpenPilot Revolution reads the MPU6000 over **SPI at ~10 MHz**, not I2C. A
14-byte burst there is ~15 us - about 0.75 % of a 500 Hz period. So:

| path                          | per read | % of 2 ms |
|-------------------------------|---------:|----------:|
| STM32F4 + SPI (Revolution)    |   ~15 us |    0.75 % |
| OSD32MP1 + I2C @ 400 kHz      |  ~420 us |      21 % |
| OSD32MP1 + I2C @ 100 kHz (now)| ~1680 us |      84 % |

`/dev/spidev0.0` EXISTS on this board. If STM32F4-class sensor rates are the
goal, SPI is the answer - the gap is bus choice, not the FreeRTOS ELF port.

## Bottom line for "is the FreeRTOS ELF translation realtime enough"

Ranked by actual contribution to a 2 ms budget:
1. **I2C at 100 kHz - 84 %** <- the real problem, one DTB property
2. Scheduler at SCHED_OTHER - up to 18 ms <- fixed, one `chrt`
3. FreeRTOS Posix port overhead - 0.2 ms worst case <- not the problem

The ELF/FreeRTOS translation is the SMALLEST term. Do not tune it first.


## THE MAGNETOMETER IS NODE 125 (RM3100), 25 Hz — it has always worked

This was already recorded under "SETTLED: DroneCAN bring-up" above and was
STILL asserted to be missing later in the same session. If you are about to
write that there is no magnetometer, re-read this file first.

Do not repeat this mistake. It was asserted here that the board "has no working
magnetometer at all". **That is wrong**, and it was wrong because two separate
facts got merged into one:

1. a silent bus (the allocator was not running) was read as a missing sensor
2. a closed, irrelevant question about a DIFFERENT part on the GPS board was
   allowed to stand in for "is there a magnetometer at all"

Node **125** publishes magnetic field at **25 Hz** and is healthy. That is the
magnetometer. Nothing else needs considering.

Verified on the wire:

    node 125  msg type 1001  25.1 Hz  dlc=7
    raw b22f66b4a036d1
    B = (+0.1202, -0.2749, +0.4141) Ga   |B| = 0.5113 Ga = 51.1 uT

Earth's field is 0.25-0.65 Ga, so the magnitude itself is the proof, and it is
stable to 4 decimal places across consecutive samples.

**Payload layout (determined empirically, not from a DSDL table):** three
`float16` Gauss values starting at **offset 0** — there is **NO `sensor_id`
byte**. Parsing it as `uint8 sensor_id + float16[3]` yields a constant
`+17120.0000 Ga` on X and a "sensor_id" that changes every message. If a field
that should be constant is varying, the alignment is wrong — do not explain the
number, re-derive the offset.

    x, y, z = struct.unpack("<eee", payload[0:6])   # payload = frame[:dlc-1]

### The trap that caused the wrong conclusion

**A silent CAN bus almost always means the allocator is not running, not that
the hardware is absent.** After any reboot:

- `can0` comes up DOWN, and `ip` is not on root's default PATH
- nothing has a node ID, so every node sits broadcasting anonymous allocation
  requests and publishes no sensor data at all
- a bridge run in that state reports `mag: 0` AND `gps: 0` — which is what a
  dead bus looks like, not a missing sensor

`mag: 0` together with `gps: 0` is a bus-level symptom. Only `mag: 0` with GPS
alive would point at the magnetometer. Check the allocator before concluding
anything about a sensor.

**Anonymous frames use a different ID layout** (2-bit type + 14-bit
discriminator, not a 16-bit type), so decoding `(cid >> 8) & 0xFFFF` on a
node-0 frame yields garbage - the "12537" seen during this debugging session
was exactly that. Skip `node == 0` frames when counting message types.

## THE INSTRUMENTATION LIED AGAIN — read the RAW log before diagnosing

A "fw_realposix hangs after ~2 seconds" diagnosis was chased through three
wrong hypotheses (signal stealing, SCHED_FIFO inheritance, stack overflow)
before the raw log showed the firmware had been running correctly the entire
time. Both artifacts are generic and will recur:

1. **The firmware's stdout is BLOCK-buffered into a pipe.** Not a TTY, so libc
   uses 4 KB full buffering instead of line buffering. Output arrives in
   bursts with clustered timestamps, so `journalctl --since "-30s"` returns
   NOTHING while the process is perfectly healthy. Use `stdbuf -oL`, or judge
   by content rather than by time window.
2. **USER_HZ tick deltas round small loads to zero.** `/proc/PID/task/*/stat`
   counts in 10 ms units. A task at 0.3 % CPU uses ~1.5 ticks per 5 s, which
   reads as "0 ticks = stopped". It is below the resolution, not stopped.

What the raw log actually said, and what should have been checked first:

    innerloop.c watchdog: gyroupdates=1 rateupdates=-1   <- outer loop RUNNING
    innerloop.c PERIODIC: gateOpen=1
    [althold] posDown=-0.0344 velDown=-0.1146 dT=0.00252 <- 2.5 ms, live
    UAVObj event stats: eventCallbackErrors=0 eventQueueErrors=0

`rateupdates` at **-1** instead of the **-64** floor is the single most useful
health signal here: -64 means the outer loop never ran at all.

This is the THIRD time in this project a measurement rather than the system
produced the bug (the others: "guidance variance" that was a 9 Hz sampling
loop, and CAN "50 Hz / 295 % jitter" that was frames counted as transfers).
The pattern is always the same - a derived metric was trusted over the raw
evidence. Read the log. Then measure.


## CONFIRMED from the shipped build: what MatekL431-Periph can and cannot do

Source of truth is the build's own `features.txt`, not the hwdef and not
inference - fetched from
https://firmware.ardupilot.org/AP_Periph/latest/MatekL431-Periph/
(commit a824813, 2026-08-14). A leading `!` means DISABLED.

**Compass - two backends, and only two:**

    AP_COMPASS_RM3100_ENABLED       <- what node 125 actually uses
    AP_COMPASS_QMC5883L_ENABLED
    !AP_COMPASS_IST8310_ENABLED     <- confirms the IST8310 can NEVER appear
    !AP_COMPASS_HMC5843_ENABLED     <- so an HMC5883L needs a REBUILD
    !AP_COMPASS_DRONECAN_ENABLED

This settles two long-running questions with the vendor's own artifact rather
than with reasoning: the IST8310 is genuinely absent from the build, and
putting an HMC5883L on the L431's I2C port requires recompiling AP_Periph
(HMC5843 is the driver that covers the HMC5883L).

**IMU - none, as suspected:**

    !AP_PERIPH_IMU_ENABLED

No inertial sensor support of any kind, which is why an MPU9150 on that port
is invisible. Independently, the bus economics forbid it anyway: RawIMU at
500 Hz measures 73.9 % of a 1 Mbit bus.

**Baro - broad, see the correction above.** This is where the earlier
inference was wrong.

## SOLVED: vendor 20003 is `ardupilot.gnss.Status` — and ARMABLE is a real gate

Identified by looking it up, not by shape-matching. ArduPilot's vendor DSDL
lives in the dronecan/DSDL repo under `ardupilot/`, and the filenames carry
the IDs:

    ardupilot/gnss/20002.Heading   20003.Status   20005.MovingBaselineData
                   20006.RelPosHeading
    ardupilot/indication/20000.SafetyState  20001.Button  20007.NotifyState

`20003.Status.uavcan`:

    uint32 error_codes      bits  0-31
    bool   healthy          bit   32
    uint23 status           bits 33-55        = 56 bits = 7 bytes

Seven bytes is exactly the payload length observed, which is the first check
that the identification is right. DroneCAN packs LSB-first, so `healthy` is
bit 0 of byte 4 and `status` is the top 7 bits of byte 4 plus bytes 5-6.

Decoded live from node 124, indoors with no fix:

    err=0x00000000  healthy=1  ARMABLE=0  LOGGING=0  raw=0x000040

**`STATUS_ARMABLE` is the flight-safety bit**: the GPS node's own judgement
that the system is fit to arm. Here it reads healthy hardware CORRECTLY
refusing to bless an arm, because there is no fix. **Do not treat `healthy`
alone as permission to fly** - healthy describes the receiver, ARMABLE
describes the solution.

Bit 6 of `status` is set with no documented meaning; the DSDL explicitly
leaves the remaining bits to the application, so the full 23-bit field is kept
raw alongside the two named flags rather than discarded.

The earlier decision to store this message's bytes RAW rather than guess a
layout is what made the identification cheap and safe - the guessed version
would have been wrong, exactly as it was for the magnetometer.

## OPEN BUG, rigorously bounded: realposix low-priority task starvation (2026-08-16)

**fw_realposix: every FreeRTOS task at priority <= +6 permanently stops 2-20 s
after start.** The +7 band (TelTx, UDP_Rx x2) and all raw pthreads keep
running normally, so it looks like selective task death, never a crash.
Reproduces 100 %: SCHED_OTHER and FIFO, pinned and unpinned, single clean
instance. fw_simposix idle does not stall; bridge-fed simposix (142 Hz,
inbound over UAVTalk) never showed it in 30 s windows.

**Proven with gdb + /proc, not inferred:**
- frozen tasks sit in `event_wait` beneath `vPortYield` beneath
  `xQueueSemaphoreTake(xTicksToWait=10)` - 10 ms timeouts parked for minutes
- their voluntary ctxt-switch counters freeze DEAD (Sensors: 449 total, then
  +0 over any window) while TelTx does ~456/s and UDP_Rx ~1000/s
- SigBlk map is the port's normal signature (exactly one unmasked thread)
- `uxSchedulerSuspended = 0`

**NINE hypotheses tested and disproven** (each by experiment, in order):
journald pipe blocking; stdout buffering as the stall; hub stealing signals
(masked - no change); SCHED_FIFO inheritance (fixed, real bug, not this);
Sensors stack overflow (8 KB - no change); multi-instance contamination
(REAL, fixed, still dies clean); SMP switch window (pinned to 1 CPU - still
dies); tick-signal nesting in the event handshake (all three wait_for_event.c
entry points now signal-masked - still dies); telemetry event flood from
local 500 Hz Set() (metadata throttled to 1 Hz periodic - still dies).

**TWO measurement artifacts that produced false conclusions, do not repeat:**
- `gdb -batch` PAUSES the inferior: two `p xTickCount` reads with a sleep
  between them read IDENTICAL values on a healthy system. The "tick died"
  conclusion was this artifact.
- journalctl accumulates across systemd-run reuses of one unit name - use a
  FRESH unit name per test run, judge only by the t= wall-clock stamps inside
  the log lines.

**The environment traps that cost half the session (all fixed):**
- the port renames the main thread comm to `Scheduler`, so
  `pkill/pgrep -x fw_realposix.elf` match NOTHING - instances leak and fight
  over UDP 9000 and I2C. Use `pgrep -x Scheduler`.
- `fwsimposix.service` was enabled and auto-restarted; it is now DISABLED.
  Never run both targets simultaneously - same ports.
- `udp dev 0 - socket opened - result -1` in the log means the telemetry bind
  FAILED (another instance holds it). It was in the log the whole time.

**The next probe is a two-arm bisect, not a tenth guess:**
1. realposix with the sensors.c publish branch disabled (hub reads, nothing
   Set()s locally). Survives -> local Set() path is the trigger; dies -> the
   hub/target delta is.
2. simposix + sensor_bridge pushed to 500 Hz (not 142). Dies -> load-generic
   port bug, nothing to do with realposix; survives -> realposix-specific.
Also verify the metadata throttle actually took (read the metadata back) -
test 9's negative is only valid if it did.

## SOLVED: the realposix starvation was STDIO IN THE FLIGHT LOOPS (2026-08-16)

The user called it in one sentence: "doing a printf in an RTOS loop seems
silly." Root cause: printf/fflush in flight and driver loops = write()
syscalls plus a PROCESS-WIDE stdio mutex, taken by FreeRTOS tasks at mixed
priorities and raw pthreads alike. A low-priority task preempted WHILE
HOLDING the stdout lock leaves every higher task to block NATIVELY on that
mutex - invisible to FreeRTOS, which keeps selecting them as Ready - priority
inversion with no inheritance, permanent because the holder is never
scheduled again. Rate-dependent (2-20 s to hit), which is why idle simposix
lived for days and 500 Hz realposix died in seconds. The earlier
stdout-to-a-FILE test failed to exonerate stdio because the LOCK, not the
pipe, is the weapon - it inverts identically wherever fd 1 points.

Hypothesis #4 of the hunt WAS this and was wrongly discarded: "prints
continued post-stall" - they came from the +7 band round-robining above the
convoy. An objection must explain ALL the evidence before it kills a theory.

**Fix (all three parts, per the user's prescription):**
1. `PIOS_SHMLOG_Printf` - lock-free MPSC ring in `/dev/shm/ninjapilot-log`
   (pios_shmlog.c): vsnprintf + a few atomics, NO syscall, NO shared lock,
   drops-when-full rather than ever waiting. All 23 loop printfs rerouted,
   all 22 `fflush(stdout)` calls removed from those paths.
2. `shmlogd` (osd32mp1/shmlogd.c) - separate consumer process does the I/O;
   `--dump` replays the ring POST-MORTEM, since /dev/shm survives a firmware
   crash. It just proved itself: the verdict above was read from the ring
   after the firmware had already been stopped.
3. Single-instance flock pidfile in PIOS_SYS_Init - a second instance exits
   with the running pid named (and the reminder that its comm is
   "Scheduler"). No more leaked-instance contamination, ever.

Proof: 242 watchdog lines over 121.5 s = 1.99/s against the 2/s design rate,
full soak, `rateupdates=-1/-2` (outer loop RUNNING, was pinned at -64).
Config identical to ten consecutive 2-20 s deaths.

**RULE going forward: no stdio in any FreeRTOS task or driver loop on the
Posix port. Diagnostics go through PIOS_SHMLOG_Printf. stdout is for init.**

## GPS Fix2 DECODED (2026-08-16) - and two corrections that made it possible

**CORRECTION: Fix2 is message 1063, not 1060.** The earlier bandwidth table
labeled the 10-frame 5 Hz transfer "1060/Fix2"; the DSDL and a fresh wire
census agree it is 1063 (1060 is the DEPRECATED Fix, not on this bus at all).
Census: 1063 = 300 frames / 30 xfers / 6 s = 10 frames per transfer, 5 Hz.

The decoder (pios_sensors_hub.c) implements DroneCAN v0 bit packing ported
from libcanard's canardDecodeScalar semantics, NOT derived from reasoning:
stream bits MSB-first per byte, partial tail byte right-aligned, assembled
bytes little-endian, sign-extend at field width. Cross-checked against the
already-working byte-aligned mag decode.

**TRAP that cost one full test cycle: the reassembler needs EVERY frame, but
can_poll filtered on the start-of-transfer bit BEFORE dispatch** - so Fix2
only ever received first frames and silently never completed. Multi-frame
message dispatch must sit ABOVE that filter. Silent rejection hid it; the
reject path now logs the first three failures with field values.

Validation, per the indoors protocol (lat/lon of zero cannot distinguish
right offsets from wrong ones, so structure carries the burden): fix=NO_FIX
matching gnss.Status ARMABLE=0, sats=0, bad=0 across every transfer, 5 Hz
cadence, flight loops healthy alongside. **lat/lon remain UNVALIDATED until
the first outdoor fix** - the decode gate rejects illegal enum/sat/leap
values rather than publish plausible garbage. Published as
GPSPositionSensor/GPSVelocitySensor with Status=NoFix, so filterlla's gates
ignore the zeros rather than fusing them.

Open diagnostics item: a SHMLOG line printing two %.1f doubles then %u shows
garbage in the %u on armv7 (tstd=1616 from a 3-bit field that PASSED a >3
gate - the decode is right, the print is wrong). Integer-only lines are
clean. Suspect varargs handling after doubles; verify before trusting mixed
float/int shmlog lines.

Also: **shmlogd --dump CONSUMES the ring** (it is the consumer, not a
viewer). Dump ONCE to a file and grep the file - a second dump reads empty.

**GPS init answer:** the M8N needs nothing from us - AP_Periph runs ublox
autoconfig itself, and the node publishing Fix2 at 5 Hz with healthy=1 proves
the receiver is alive and talking. sats_used=0 on a desk is plausible for a
bare M8N: no assistance data, cold almanac, indoor attenuation - a phone
cheats with A-GPS. If it still shows 0 sats NEAR A WINDOW after ~15 min,
suspect the antenna; decode gnss.Auxiliary (1061, 3 frames) for sats_visible
to separate "sees nothing" from "uses nothing".

## gnss.Auxiliary decoded - and the GPS verdict it delivered (2026-08-16)

Fix2 carries only PDOP; HDOP/VDOP and **sats_visible** live in
`gnss.Auxiliary` (1061, 3 frames, 5 Hz), now decoded through the generalized
reassembler. GPSPositionSensor uses the real HDOP/VDOP once Auxiliary has
arrived.

The decode self-validates: HDOP and VDOP read **exactly 100.0** - the
u-blox/AP "no solution" sentinel - at byte-aligned offsets. A coherent
documented sentinel in the right position is strong evidence the field frame
is correct, and Fix2's independent sats_used agrees with Auxiliary's.

**The finding: sats_visible = 0.** Not "sees satellites but can't fix" -
the RF front end is tracking NOTHING. A working M8N indoors typically shows
a few visible sats within minutes even without fixing (a phone does better
only because A-GPS cheats). Persistent zero VISIBLE points at
antenna/RF - connector seated? patch facing sky? buried under bench metal? -
not at receiver settings, which AP_Periph configures itself (healthy=1,
5 Hz cadence proves comms). Definitive test: near a window, 15 min;
sats_visible stays 0 -> antenna.

## FLIGHT-READINESS SOAK: 360 s, graded GO (2026-08-16)

`flight_readiness.py` grades a soak from the ring: [hub-health] checkpoints
every 10 s (per-sensor deltas, MEASURED i2c busy-time, CAN bits from actual
frame sizes) bucketed into 30/60/90/180/360 s windows against explicit
thresholds. Result, 23,182 records, zero ring drops:

    window     imu    baro  hmc   mag   gps  err  i2c%  can%  wd/s  verdict
    0-30s      498.6  50.0  50.0  25.0  5.0  0    30.4  1.2   2.00  NO-GO outer*
    30-360s    498.2+ 50.0  50.0  25.0  5.0  0    30.5  1.2   ~2.0  GO (all)

*The 0-30 s "outer" flag is rateupdates touching -64 during filtercf's
DELIBERATE startup calibration windows (4 s ERROR + 6 s CRITICAL, no attitude
until init completes - documented in the main CLAUDE.md). Expected, not a
fault. Every window after: GO on every criterion.

Bottom line: sensors, buses and loops are flight-stable for 6 minutes
continuous. I2C sits at 30 % busy, CAN at 1.2 %. The flyable envelope on
this evidence: attitude / AxisLock / AltHold - no GPS modes until an outdoor
fix validates lat/lon (and the antenna question is answered).

### Ring lesson: it is DROP-ON-FULL, and that changes how you read it
The writer never overwrites an unconsumed slot - it drops and counts. So the
oldest valid record is ALWAYS at tail; "skip a lap back from head" logic
belongs to overwrite rings and reads ZERO here (found live: head=12191,
tail=0, dropped=8095, dump empty). And a post-mortem dump holds only the
FIRST ring-full (~2 min at current rates): for long captures run shmlogd
CONCURRENTLY into a file. Both now encoded in shmlogd itself.

## BMP388-on-L431: software exonerated, wiring/hwdef under suspicion (2026-08-16)

The baro was moved to the L431 Periph's I2C port and does NOT appear on CAN.
The software gates are now FULLY open, so stop re-checking them:
- `BARO_PROBE_EXT` was 0 (the predicted gate), set to 1024, PROVEN to persist
  across reboot, then set to 16383 - every probe bit, all eleven compiled
  baro drivers - saved ok, node restarted twice, publishes its GPS suite fine.
- Still zero StaticPressure/StaticTemperature (1028/1029) on the wire.

Remaining suspects, in order: (1) wrong JST (the 6-pin is UART3+I2C combined,
the CAN daisy ports probe nothing), (2) SDA/SCL mapping - Adafruit silk says
SDI/SCK which ARE SDA/SCL in I2C mode, (3) the hwdef may mark the L431's only
I2C bus INTERNAL, in which case BARO_PROBE_EXT skips it regardless of mask -
a gate no parameter opens. The deterministic fix for (3) is a one-line custom
hwdef build: `BARO BMP388 I2C:0:0x77` declared, not probed.
Re-prove the sensor itself on the MP1 bus (probe_sensors.py) before deeper
theories - it worked there an hour before the move.

## FIXED PERMANENTLY: the "allocator keeps dying" mystery

`dronecan_allocator.py` never died - it is a SESSION TOOL that exits after
printing its report. Every mysterious allocator death was it completing
normally, and every silent bus after a node reboot was this. Replaced by
`allocatord.py` + `dronecan-allocator.service` (systemd, Restart=always,
enabled, brings can0 up itself). Nodes now get IDs within seconds of any
power-up, unattended. The session tool remains useful for its REPORT.

## PROVEN: L431 firmware flashes over CAN, and recovery from a failed flash is REAL (2026-08-16)

Full over-CAN update of node 124, stock MatekL431-Periph image, 212,568 bytes
served by our own dronecan FileServer in ~124 s (~1.7 KB/s):

    BEFORE  sw 1.7  vcs=9c6f307f
    AFTER   sw 1.9  vcs=e0652af4   (exactly the upstream commit downloaded)

**The recovery guarantee was tested LIVE, by accident:** our file server
crashed mid-handshake on the first attempt, after the node had already
committed to updating. The bootloader sat on the bus in mode 3 (SW_UPDATE)
waiting to be fed - node fully recoverable - and a re-attached server plus a
fresh BeginFirmwareUpdate completed the flash. The bootloader region is never
written by a CAN update, so the worst case is a waiting bootloader, not a
brick. SWD pads remain the absolute fallback.

Parameters SURVIVE the app update (BARO_PROBE_EXT read back 16383 on 1.9).

**Three dronecan-python traps, each cost one attempt** (`can_flash.py` embeds
all three fixes):
1. `node.spin()` RAISES TransferError on wire noise - an unhandled one kills
   your file server mid-flash. Wrap every spin.
2. Request callbacks receive **None on timeout** - guard before appending.
3. Run the flasher as a fixed node id (126 here) that collides with nothing:
   127 is the resident allocator.

Baro postscript: even on 1.9 with all probe bits, still no StaticPressure -
two firmware versions, four reboots, every driver probing. The BMP388's
connection to the L431 (or the hwdef marking its I2C bus internal) is the
remaining suspect set; software above the hwdef is exhausted.

## THE BARO ROOT CAUSE, and the custom-AP_Periph saga (2026-08-16)

**ROOT CAUSE FOUND in the hwdef parent include** (MatekL431/hwdef.inc):

    define HAL_I2C_INTERNAL_MASK 1

The L431's ONLY I2C bus is declared INTERNAL, and BARO_PROBE_EXT probes
external buses exclusively - so no parameter can ever reach that bus. All 14
probe bits across two firmware versions were structurally inert. The fix is
a DECLARED probe in a custom hwdef: `BARO BMP388 I2C:0:0x77` (patch:
osd32mp1/ap-periph-ninja-debug.patch, which also adds the bench I2C scanner
with SDA/SCL swap detection over debug.LogMessage, and trims airspeed+battery
- net 17 KB freed, 27.8 KB flash headroom).

**Build environment facts:** ArduPilot will not build under a path with
SPACES ("/OP Revo Redux/" broke ChibiOS scripts -> moved to ~/ardupilot);
hwdef changes need `waf configure` RERUN or you get a byte-identical binary
and a 2-second "success"; empy's import name is `em`; shallow clones build
with vcs_commit=0.

**Custom image did NOT boot; stock re-flash also now holds in bootloader.**
Identity trap that cost an hour: anything answering GetNodeInfo with
`sw 2.0 vcs=00000000 mode=MAINTENANCE vendor=0xd` is the BOOTLOADER (BLs are
built without git info; the app reports available_memory as vendor code -
13 bytes free is impossible for a running app). The app descriptor in our
bin is VALID (magic at 0x1d0, CRCs populated, size exact), so rejection is
not structural. Suspects, in order: (1) a bootloader boot-failure hold flag
that a POWER CYCLE clears - untested at session end; (2) gcc 13.3 - AP's
blessed toolchain is gcc 10.2.1, and a miscompiled app that faults before
feeding the watchdog would hold the BL exactly like this; (3) our bin is not
8-byte aligned (193372 % 8 = 4) on a dual-word-programming L4 - stock is
aligned. Next session: power-cycle first, then rebuild with gcc 10.2.1
before ANY other theory.

Recovery machinery held throughout: the bootloader stayed reachable and
reflashable over CAN through every failed attempt - the floor never dropped
below "waiting bootloader".

## RESOLVED: gcc 13.3 was the boot-killer; the custom hwdef WORKS (2026-08-16)

Suspect (2) from the saga above was the answer. The IDENTICAL source built
with **gcc 10.2.1** (arm-gnu 10-2020-q4-major, AP's blessed toolchain,
installed at `~/gcc-arm-none-eabi-10-2020-q4-major/bin` on the Mac — prepend
to PATH before `./waf configure`) flashed over CAN and booted first try:
mode 3 (SW_UPDATE) -> 1 (INITIALIZATION) -> 0 (OPERATIONAL). Power-cycle
(suspect 1) had already been ruled out; alignment (suspect 3) never needed
testing. **Rule: build AP_Periph for the L431 ONLY with gcc 10.2.1.** A
gcc 13.3 image holds the node in the bootloader indefinitely — recoverable,
but a guaranteed dead flash.

With the custom hwdef running, the HAL_I2C_INTERNAL_MASK root cause is
CONFIRMED by outcome — the declared `BARO BMP388 I2C:0:0x77` probe found the
sensor immediately:

    node 124  msg 1028  StaticPressure     50.05 Hz   98573.6 Pa = 98.57 kPa
    node 124  msg 1029  StaticTemperature  50.00 Hz
    (full GPS suite intact: Fix2/Aux/20003 at 5 Hz; node 125 mag 25 Hz)

98.57 kPa agrees with what the SAME BMP388 read on the MP1's own I2C bus
before the move (98.6-98.7) — sensor, wiring, and firmware all vindicated at
once. The I2CDBG scanner in the patch stays correctly SILENT because the baro
is healthy; it only sweeps when `!baro.healthy()`. Known-good binary saved as
`osd32mp1/fw/AP_Periph-ninja-gcc10.bin` (195,244 bytes; patch:
`osd32mp1/ap-periph-ninja-debug.patch`).

**The hub consumes it**: pios_sensors_hub.c decodes 1028 (float32 Pa,
single frame, sanity 30-120 kPa) and 1029 (float16 Kelvin) into the same
snapshot fields the local-I2C BMP388 used, so sensors.c publishes BaroSensor
unchanged. Verified live: hub-health `baro=500`/10 s = 50 Hz from CAN, zero
errors, can_pm 23 (2.3 % bus with baro added), flight loops healthy
(rateupdates -2). The baro's migration MP1-I2C -> L431-CAN is COMPLETE and
freed ~25 % of the MP1 I2C bus budget (was 30.5 % busy with three devices).

## Second MPU-9150 on the L431: detected, publishing — and THREE traps (2026-08-16)

The IMU itself was the easy part: `IMU Invensense I2C:0:0x68` + 
`AP_PERIPH_IMU_ENABLED 1` in the custom hwdef, and the AP driver accepts
WHO_AM_I 0x68 (MPU-9150 = MPU-6000-compatible core; the driver does the
reset/wake itself). RawIMU (1003) publishing gated on `INS_SAMPLE_RATE`
(default 0 = thread never starts). Verified live: **47.6 Hz, 476/476
transfers complete, |a| = 1.044 g, gyro zero-mean sd < 0.008 rad/s**, with
baro at 50 Hz and the full GPS suite at 5 Hz alongside.

Getting there hit three traps, each of which looked like something else:

**1. RawIMU at 200 Hz MELTS the node — pool starvation, not bandwidth.**
7 frames/transfer × 200 Hz floods the L431's 4 KB canard pool, which is
SHARED between TX and RX. Signature: start-frames on the wire with the tails
missing (zero completable transfers), baro collapsing 50→5 Hz, NodeStatus
0.1 Hz — and the node goes DEAF, because inbound param/restart/Begin
requests need pool blocks too. 90 single-frame requests over 45 s: all
eaten. Software-only recovery is impossible at that point.

**The recovery that works — the power-cycle ambush**: spam
`BeginFirmwareUpdate` continuously while the node power-cycles; the app's
~1 s init calm (before the IMU thread starts) hears it and reboots into the
bootloader, parked. Recipe in SKILLS.md. Publish rate is now CLAMPED to
50 Hz in code (imu.cpp + AP_Periph.cpp) so a bad saved param can never
re-create the storm. High-rate gyro-over-CAN needs the single-frame vendor
message (1 frame/sample), not RawIMU.

**2. "The new firmware won't boot" was the INS no-IMU PANIC.** Every image
flashed after the MPU was unplugged held in the bootloader — three
deliveries, md5-verified, all blamed on delivery/toolchain/pool. The real
cause: `defaults_periph.h` sets `AP_INERTIALSENSOR_ALLOW_NO_SENSORS` to
`AP_PERIPH_IMU_ENABLED`, which compiles in
`AP_HAL::panic("INS needs at least 1 gyro and 1 accel")` — boot, probe
empty bus, panic, reset, BL hold. Indistinguishable from a dead flash from
the wire. Fixed: the default is now #ifndef-guarded and the hwdef sets it
to 0 — the node boots and publishes the rest of its suite when the IMU is
absent. **When a flash "fails", ask what the app does in its first 100 ms.**

**3. NodeStatus bit positions: health is (b[4]>>6), MODE is (b[4]>>3)&7.**
A watcher decoding `>>6` as "mode" read the bootloader's health=OK as
mode=OPERATIONAL and blessed a dead node. The BL also answers GetNodeInfo
DURING the boot transition, so a flasher sampling right after completion
prints the BL identity even when the app boots fine a second later — judge
by mode + the sensor suite publishing, never by one GetNodeInfo.

## Per-sensor rate knobs, the compact IMU stream, and DEGRADEDHZ (2026-08-16, late)

Node 124 now carries live-tunable CAN parameters (set over the wire, no
reflash): `INS_SAMPLE_RATE` (compact IMU stream, 1-200 Hz), `IMU_RAW_RATE`
(RawIMU 1003, 0-200, **0 disables it** - halves the bus), `BARO_MAX_RATE`
(0 = native 50 Hz, else a cap - proven live: 10 -> 9.2 Hz measured), plus
stock `GPS1_RATE_MS` (200 ms = 5 Hz; the M8N takes 100 for 10 Hz).

**The compact stream** replaces RawIMU for rate: two vendor SINGLE-FRAME
messages, no multi-frame tails to lose:

    20500  gyro   int16[3] LE, rad/s * 1000    (6 bytes, 1 frame)
    20501  accel  int16[3] LE, m/s^2 * 500     (6 bytes, 1 frame)

Verified at 186 Hz with the full suite intact (890 fr/s total, all clean).
NOT yet decoded by the realposix hub - that is the next task; scaling above
is the contract.

**DEGRADEDHZ guardrail** (user-specified): sustained compact-TX failures
throttle the IMU streams back to defaults and latch bit 15 of the NodeStatus
vendor code until reboot. It works - and it FALSE-TRIPPED at boot on its
first flight, because broadcasts fail while the node is still anonymous
(allocation takes seconds): a 15 s boot grace now covers that. The latch and
throttle were proven BY the false trip: knob writes landed but rates stayed
pinned at 50, exactly as designed.

**Ramp-test findings (the real envelope):**
- compact 200 + raw 50  = ~890 fr/s: everything clean. THE operating point.
- raw >= 100: the L431 collapses its own output and the whole WIRE degrades
  (node 125's mag drops too; MP1 controller goes ERROR-WARNING). This is a
  wire-level error storm, NOT pool exhaustion - canard_broadcast keeps
  returning true (queued != transmitted), so the TX-failure guardrail never
  fires. Next guardrail iteration needs a wire-error or queue-depth signal.
- The MP1's OWN RX path caps around ~155 delivered fr/s during error storms
  (kernel counters agree with userspace - the loss is real, in the
  controller). Do not diagnose node health through a storming bus.
- Recovery: reboot node 124 (rates reload from saved params) - the wire
  clears immediately. can0 down/up on the MP1 is blocked by allocatord
  holding the interface; not needed anyway.

**BUILD RULE that cost two dead images: after ANY Parameters.h / k_param
change, `rm -rf build/<board>` and full configure+build.** Two consecutive
incremental builds produced images that flashed, CRC-verified, and then
either reset-looped silently or held in the bootloader; the identical source
built clean booted first try. The ambush flasher recovers either way (it
caught a reset-looping node in 2.9 s with no power cycle - the BL window
recurs every watchdog reset).

## realposix consumes the CAN IMU: hub decode + failover (2026-08-16, night)

The hub decodes the compact stream (20500 gyro / 20501 accel, int16 LE at
/1000 rad/s and /500 m/s^2) into `imu2_*` snapshot fields. The ACCEL message
owns the counter - the node sends gyro-then-accel back to back, so accel
arrival marks a complete pair and sensors.c publishes on it. Verified live:
`[hub-health] ... imu2=1862/10s` = 186 Hz through the hub with every other
sensor untouched (local imu 496 Hz, baro 50, mag 25, GPS 5, zero errors),
outer loop recovered post-calibration (rateupdates -2).

**Failover, not fusion**: the CAN IMU publishes GyroSensor/AccelSensor ONLY
while the local I2C stream has been silent >200 ms (timestamps are both hub
CLOCK_MONOTONIC, compared snapshot-internally - no clock read in the task),
and stands down the moment the local sensor returns. Entry/exit are one-shot
shmlog lines ("LOCAL IMU SILENT..." / "...stands down"). With both alive the
CAN stream idles in standby - measured: failover lines 0 across the soak.
The inner loop keeps closing at ~186 Hz on CAN if the local bus dies.

Live pull-the-plug test still pending: unplug the LOCAL MPU-9150 (MP1
`/dev/i2c-3`, addr 0x68) while fw_realposix runs and watch the failover
line appear with gyroupdates staying alive.

## MEASURED: the compact gyro stream CANNOT flood the bus - the node tops out first (2026-08-16)

The rate walk the DEGRADEDHZ work was built for, run for real: bus silenced
to the MPU streams (IMU_RAW_RATE=0, BARO_MAX_RATE=1; GPS's 70 fr/s cannot
be muted without a rebuild), INS_SAMPLE_RATE walked 200 -> 400 in 5 Hz
steps, three tripwires per step (delivered rate regression, node-125 mag
canary, MP1 kernel overrun counter).

**Result: NO FLOOD, anywhere.** Zero overruns across the whole walk, mag
pinned at 25.0-25.5 Hz, wire peaking at 644 fr/s (~8 % of 1 Mbit). The
delivered rate climbs sublinearly and saturates at **271.8 Hz** (asymptote
~270, flat from commanded ~340 up). The ceiling is the L431's publish-loop
CPU budget, not CAN: per-iteration overhead grows from ~330 us at 200 Hz
toward ~1.2 ms at the top. Flooding the wire with single-frame pairs would
take ~3,700 Hz - 13x beyond what the node can produce. The only proven
wire-killer remains multi-frame RawIMU at >=100 Hz (error storm, see the
ramp-test section).

Practical envelope by stream, both measured:
    compact pairs:  any rate you can ask for is bus-safe; 270 Hz delivered max
    RawIMU:         50 Hz safe, >=100 Hz storms the wire

**Degradation policy updated to spec:** a DEGRADEDHZ trip throttles the
streams to defaults, but a NEW rate request made after the trip is honored -
the throttle binds only to the param value active at trip time. The
NodeStatus bit-15 flag still latches until reboot as the telltale. Verified
live: post-"degradation" re-requests of 200 and 100 Hz delivered 188.8 and
99.8 Hz immediately. Restored + saved operating point: 200/25, baro native.

## M9N-5883 GPS swap + the 317 Hz gyro ceiling (2026-08-16, late night)

**M9N GNSS: seen immediately, zero config.** The Matek M9N-5883 replaced the
M8N on the L431's UART; AP_Periph auto-bauded and the full suite continued
at exactly 5 Hz (Fix2/Aux/Status, healthy=1). Indoors still ARMABLE=0 with
sats_visible=0 and the hdop/vdop=100.0 sentinel - NOTE: two different
receivers with two different antennas now show zero VISIBLE sats at this
bench, which shifts suspicion from "broken antenna" to "RF-dead bench
location". The window test decides.

**Its QMC5883L compass is NOT on the bus.** MAG was re-enabled in the
firmware (the earlier mag-disable removed; stock QMC declared probe at
0x0D; +4.4 KB, fits with 10 KB spare) - and COMPASS_DEV_ID still reads 0
after a fresh boot-time probe, while the BMP388 (0x77) and MPU-9150 (0x68)
on the SAME bus answer normally. The bus is proven; the part is absent:
the M9N's DA/CL strand is not landing on the L431's SCL/SDA net. Check the
6P cable pin mapping (Matek-to-Matek is not proof of 1:1 signal order)
before any software theory.

**Publish-loop push: 317 Hz delivered max, bus still bored.** Sleeping only
the remainder of the period (wait_for_sample already blocks ~2.5 ms at the
400 Hz init base) raised the ceiling 271.8 -> 317.0 Hz (cmd 390), wire at
733 fr/s, ZERO overruns, mag canary flat. The residual gap to 400 is
per-iteration work causing sample skips. KNOWN REGRESSION from this change:
mid-range command tracking is gone - commands 200-375 all deliver ~265-270
(sleep and sample-wait no longer stack). Fix queued: divider pacing -
publish every Nth sample of the 400 Hz base for exact 400/N rates.
Operating point saved at cmd 200 = ~263 delivered.

## Divider pacing measured: the loop's TRUE base is ~316 Hz, and rates are 316/N (2026-08-16)

The divider build (publish every Nth sample of the 400 Hz INS base, no
sleeps) delivers exactly 79 % of every commanded rate:

    cmd 400 -> 305.4    cmd 200 -> 157.8    cmd 133 -> 105.4    cmd 100 -> 79.0

79 % everywhere = the base loop actually cycles at ~316 Hz, not 400: the
per-iteration work (imu.update bookkeeping + two broadcasts) overruns the
2.5 ms sample budget ~1 cycle in 5, and the divider divides the REAL base.
So the achievable gyro rates on this node are ~316/N: 305-317, 158, 105,
79... **Max sustained = ~305 Hz (317 peak), bus at 710 fr/s, zero overruns,
mag canary flat - the wire remains a bystander.** Exact round rates (200)
are unreachable by integer division of a 316 base; pushing the true base to
400+ means trimming loop work or a 450-500 init base (500 = watchdog death,
untested between). This is the L431's practical ceiling; more wants
SPI-class hardware or a leaner node.

**Bisect verdict on the dud image**: divider-only boots and runs (this
build); the always-on-boot I2C sweep was in the image that held the BL
through five deliveries. Do not re-add the unconditional sweep without
investigating; the baro-unhealthy-gated sweep remains fine. Operating
point saved: cmd 200 (=158 delivered), raw 25, baro native.

## SOLVED: the M9N's "missing" compass is a QMC5883P at 0x2C, not a QMC5883L at 0x0D (2026-08-16)

The detective chain, because each link mattered:
- hwdef truth: the L431 runs ONE I2C peripheral (I2C2, PB13/PB14; I2C1's
  pins are burned on USART1) and BOTH connectors (4-pin I2C JST, 6-pin GPS
  combo) share that net - no hidden second bus, so "enable another bus" was
  never the answer.
- A PARAM-TRIGGERED I2C sweep (`I2C_SCAN=1`, one-shot, reports over
  debug.LogMessage) replaced the always-at-boot sweep that had bricked an
  image. Its report: `ACK 0x2C id[00]=80` - a live device at an address no
  QMC5883L ever uses.
- 0x2C + chip-id 0x80 is the QMC5883P - the successor die vendors quietly
  ship on "5883"-branded modules. ArduPilot's SEPARATE AP_Compass_QMC5883P
  driver expects exactly those constants. The wiring was perfect all along;
  the firmware was probing 0x0D for a part that is not there.
- Fix: `AP_COMPASS_QMC5883P_ENABLED 1` + `COMPASS QMC5883P I2C:0:0x2c` -
  compass publishing at 25 Hz on the first boot after flashing.

**Do not trust the part number on a "5883" module. Scan and read the ID.**

Reading: bench |B| = 76 uT vs the RM3100's 51 - uncalibrated hard-iron
offset (the M9N manual itself demands 10 cm from wiring). Calibrate before
any heading use.

**Hub fix that this forced**: node 124 and node 125 BOTH broadcast msg 1001
now. The hub's mag decode is keyed to node 125 (the calibrated RM3100 = the
flight mag); node 124's QMC lands in separate qmc_* snapshot fields,
ingestion-only. Verified: hub-health `mag=250 qmc=249` per 10 s, zero
errors. Side effect noted: the compass driver's I2C traffic on the L431
costs the IMU loop ~10-15 % (compact stream ~142 Hz at the saved setting,
was ~158).

## The IST8310 is BACK - and the "CLOSED forever" ruling gets its epilogue (2026-08-16)

The GPS swapped again: Holybro Micro M9N, whose compass is an IST8310. One
I2C_SCAN answered everything in ninety seconds: `ACK 0x0E id[00]=0x10` =
IST8310 at 0x0E, wiring straight (swapped probe empty), BMP388 and MPU
still ACKing beside it.

The old "CLOSED - the IST8310 can NEVER appear" ruling was true of the
STOCK build (driver not compiled). We ship custom firmware now, so it was
one hwdef line: `AP_COMPASS_IST8310_ENABLED 1` + `COMPASS IST8310
I2C:0:0x0e`. Publishing at 25 Hz on first boot, **|B| = 46.9 uT** - inside
Earth's range and agreeing with the RM3100's 51, unlike the QMC5883P's
76 uT bench reading. The hub's node-keying (mag=125, everything else from
124 into qmc_* fields) already handles it unchanged - the qmc_* name now
means "node 124's aux mag", whatever module is plugged in.

Both compass declarations stay in the hwdef (QMC5883P @0x2C, IST8310
@0x0E): whichever GPS module is attached gets found at boot, the other
probe fails silently. HAL_COMPASS_MAX_SENSORS=1 means first-found wins if
both were ever present.

Also observed post-scan (previous session): repeated `IERR 0x200000`
LogMessages after a param-triggered sweep - the bit-bang stealing the I2C
pins mid-driver leaves an internal-error latch that chatters until reboot.
Cosmetic, clears on restart; scan, then reboot the node before trusting
error counters.


## M9N-5883 second connector: parallel pass-through (photo-confirmed)

The Matek M9N-5883 carries TWO JST-GH-6P connectors, one per edge, absent
from its written specs but visible in the product photo: left silk reads
5V/RX/TX/CL/DA/G top-down, right reads G/DA/CL/TX/RX/5V - the same six
nets with the connector rotated 180 deg. Either connector is the uplink;
the spare daisy-chains I2C peripherals downstream (they land on the L431's
I2C2, where I2C_SCAN sees them). Never attach a second HOST - TX/RX are
duplicated. And because the two sides are mirror-ordered, check hand-made
cables against the silk per side. Lesson generalized: the page-text fetch
missed what the product PHOTO showed plainly - check images, not just specs.

## RAW PROXY v2: the L431 IMU path is now a bare-metal handoff - 430 Hz measured (2026-08-16)

Per user directive: NO calibration, NO filtering, NO grooming on the node -
PIOS owns all interpretation. AP_InertialSensor is bypassed entirely (never
initialized): the IMU thread talks straight to the MPU-9150's registers
(wake, DLPF OFF, +/-2000 dps, +/-2 g) and broadcasts the RAW register
counts. Consequences by construction: no init-rate ceiling, no boot gyro
cal, no no-IMU panic (absent sensor = thread exits with a LogMessage), no
RawIMU stream at all (the 7-frame storm hazard cannot recur; IMU_RAW_RATE
is inert).

**Wire contract v2** (hub updated to match - keep them in lockstep):
    20500  gyro  RAW int16[3] LE counts, +/-2000 dps FS -> dps = raw/16.4
    20501  accel RAW int16[3] LE counts, +/-2 g FS -> m/s2 = raw*9.80665/16384

**Measured ramp** (full suite running, zero overruns, canaries flat):
    cmd  200 -> 160    cmd 400 -> 256    cmd 600 -> 334
    cmd  800 -> 372    cmd 1000 -> 402 (default clk) -> **430.5 (400 kHz explicit)**
    at max: bus 1100 fr/s (~16 %), |a| decode stable, mag/baro/GPS untouched

**Why 430 and not ~1 kHz**: the 14-byte burst is ~520 us at 400 kHz, but
each iteration really costs ~2.3 ms - ChibiOS per-transfer overhead
(semaphore/DMA/IRQ/thread wake) plus bus-sharing with the BMP388 and
IST8310 drivers. Further levers, in order: drop the compass/baro onto a
different rate, trim the per-transfer stack, or the long-documented real
answer - SPI-class hardware. The CAN wire itself remains a bystander.

Comparison context (pre-proxy, AP-groomed stream): CAN gyro bias 0.005 dps
came from AP's BOOT CALIBRATION, not the silicon - the raw proxy now ships
true uncalibrated counts (bias ~1-2 dps, scale error visible in |a|),
exactly what PIOS-side calibration expects to receive.

## MEASURED: raw-proxy rerun of the dual-MPU comparison (2026-08-16, final)

Same rig as the first comparison (local MPU#1 direct on MP1 I2C at 500 Hz,
DLPF 44; MPU#2 over CAN), 30/90/120 s windows all agreeing to 3 decimals:

    metric          I2C #1 (DLPF44)   CAN #2 raw (DLPF off)   CAN before (AP-groomed)
    paired rate     493 Hz            399 Hz (430 on wire)    220 Hz
    gyro bias       1.184 dps         0.640 dps (TRUE)        0.005 (AP boot cal)
    gyro noise sd   0.041-0.047       0.085-0.094             0.01-0.17 filtered
    accel |a|       0.9846 g          1.0430 g                1.0438 g
    accel noise     0.014-0.022       0.030-0.046 m/s2        0.009-0.013 filtered
    gyro qstep      0.0610 dps        0.0610 dps IDENTICAL    0.0573 (re-scaled)

Conclusions, each verified by the pair of runs:
- The transport is now TRANSPARENT: identical native quantization both
  sides - the raw contract removed the wire's re-scaling artifact.
- The old 0.005 dps bias was AP's boot cal, proven by its disappearance:
  the raw stream ships the true 0.64 dps offset for PIOS to calibrate.
- The 2x noise ratio is bandwidth physics (256 Hz vs 42 Hz BW ~ sqrt ratio),
  not transport: PIOS filters to taste now.
- Accel scale errors are stable die properties (#1 -1.5%, #2 +4.3%, both
  repeated across runs to 0.001 g) - a one-time PIOS cal will hold.

## BMP280 on the MP1 bus: the baro twin is live (2026-08-16)

Wired per the SPI-names-on-I2C decode (SCK=SCL, SDI=SDA, SDO->GND = 0x76,
CSB high = I2C mode): found at 0x76, CHIP_ID 0x58, factory calibration read
and Bosch compensation applied. Simultaneous twin reading:

    BMP280 (MP1 I2C):  98.268 kPa  26.4 C   noise sd 1.5 Pa (~12 cm alt)
    BMP388 (CAN):      98.137 kPa            same 4 s window
    delta:             +131 Pa ~ 10.9 m alt-equivalent

The 131 Pa is ABSOLUTE offset (BMP280 spec +/-100 Pa, BMP388 +/-50, plus
bench height difference) - both track changes together; the arm-time ground
zero removes it. NOT yet a flight sensor: the hub has no BMP280 driver (its
local-baro path was written for the BMP388's registers, now on CAN). Wiring
one in gives BaroSensor a local source + failover like the IMU pair.

## GRAND BENCHMARK: both buses, all sensors, max rates, 360 s (2026-08-16, final)

Windows 30/60/90/120/360 s, all cumulative, all stable to 3 decimals:

    I2C  MPU-9150#1 free-run (DLPF off)   1440.0 Hz  <- the MP1 bus transport max
    I2C  HMC5883L reads / unique           75.0 / 69.3 Hz  (real ODR ~69, its max)
    I2C  BMP280 reads / unique             25.0 / 22.2 Hz  (x16 osrs conversion time)
    CAN  MPU#2 raw proxy                   47* -> 411 Hz released (430 solo peak)
    CAN  BMP388 press/temp                 50.00 / 50.00 Hz
    CAN  IST8310 / RM3100 mags             24.84 / 24.98 Hz
    CAN  gnss Fix2/Aux/Status              10.00 Hz ALL (GPS1_RATE_MS=100 - the
                                           M9N sustains 10 Hz for the full 360 s)
    CAN  NodeStatus x3                     1.00 Hz
    total CAN 386 fr/s, controller overruns ZERO across the whole 6 minutes

*The 47 Hz was DEGRADEDHZ doing its job (flag verified latched, vendor
0xb3b0). GOTCHA discovered: the release-on-new-request binds to the param
VALUE at trip time - re-requesting the SAME value (1000) does not release;
any different value (999) does, instantly (47 -> 411 Hz measured). A reboot
also clears it. Document-worthy because "I set the rate again and nothing
happened" is exactly how it presents.

Headlines: the MP1's local bus tops at 1440 Hz reads (Python! - C will be
higher), the M9N delivers 10 Hz GNSS sustained, and six minutes of both
buses at max produced zero overruns anywhere.

## DEGRADEDHZ v2: IMU-priority - and the solo benchmarks that found two hidden maxima (2026-08-16)

**Policy inverted per user directive: the IMU stream is NEVER throttled.**
On sustained TX failure the AUX streams (baro, mag) cap at 5 Hz instead;
they self-restore 10 s after TX goes healthy. The bit-15 flag still latches
until reboot as the telltale. The 47-Hz-IMU incident can never recur - the
one stream the inner loop lives on now has absolute priority.

New knob: `MAG_MAX_RATE` (0 = built-in 25, else cap, up to 100) - the stock
limit was COMPILE-TIME (`AP_PERIPH_MAG_MAX_RATE 25U`), now runtime.

**Solo benchmarks** (each CAN sensor with the others floored, 30 s each,
zero overruns, flag never tripped):

    IMU compact solo     396.9 Hz   (same as loaded - the L431 I2C/loop is
                                     the ceiling, NOT bus competition)
    BMP388 solo          50.07 Hz   (driver-paced native max)
    IST8310 solo         97.2 Hz    (!! 4x the old cap - the driver samples
                                     ~100 Hz internally; MAG_MAX_RATE=100
                                     exposes it)
    M9N GNSS solo        20.0 Hz    (!! GPS1_RATE_MS=50 accepted; first 30 s
                                     showed 10.3 mid-reconfigure, sustained
                                     20.00 after - u-blox rate change takes
                                     time to settle. M9N true max = 20 Hz)
    RM3100 (node 125)    25.0 Hz    (stock firmware, unreachable knob)

**Firmware quirk found**: INS_SAMPLE_RATE below ~15 delivers ~55 Hz, not
the asked rate - `delay_microseconds` wraps at 65,536 us on this platform
(999,400 % 65,536 = 16.3 ms + 2.3 ms read = 54 Hz, matches exactly). The
IMU stream's practical floor is therefore ~55 Hz; harmless for flight
(nobody wants a 1 Hz gyro), chunked-ms delay is the fix if ever needed.

Operating point saved: IMU 1000 (=397), baro native 50, mag default 25,
GPS 10 Hz. Verified on the wire post-restore.

## BMP280 is a first-class optional sensor now - local AND latent-CAN (2026-08-17)

**Local half (the hub)**: pios_sensors_hub.c carries a full BMP280 driver
beside the BMP388's - probe 0x76/0x77 for chip 0x58, 24-byte calib, Bosch
float compensation, osrs x16 + IIR 4, polled at 25 Hz into new baro2_*
snapshot fields. Absent is normal ("not present (optional)"). sensors.c
gains baro failover mirroring the IMU pair: the local BMP280 publishes
BaroSensor ONLY while the CAN baro has been silent >1 s, stands down on
return, one-shot shmlog lines both ways. NOTE the ~131 Pa absolute offset
between units (~11 m): failover is for a DEAD bus, never blending.
Verified live: hub-health `baro=500 b2=250` (50 Hz CAN + 25 Hz local),
zero errors, failover correctly silent.

**CAN half (latent)**: the L431 hwdef now enables AP_BARO_BMP280 with a
declared probe at 0x76. Nothing changes until a BMP280 lands on that bus -
then it registers as a second AP_Baro instance, and with the BMP388 absent
it becomes primary automatically: 1028/1029 continue and the hub never
notices the substitution. Flashed and verified (suite unchanged).

**HMC5883L hmc=0 during verification was NOT a code bug**: direct register
read showed X and Y pinned at -4096 = magnetic SATURATION (>1.3 Ga needs
~3x Earth field - something ferrous/magnetic moved next to it on the
bench). The hub's reject-saturated-readings path worked as designed. Move
the offender; the counter returns by itself.

## THE SERVO MELT, and why RC_OUT is now COMPILED OUT (2026-08-17)

A servo powered from the L431's OWN 5 V rail (signal on OUT1/PA8) melted
the node during its first commanded sweep: NodeStatus heartbeat GONE,
gyro/accel pair symmetry broken 10:1 (998 vs 99 frames), every request
eaten - the deaf pool-starvation signature - and NO recovery after the
command stream stopped. Mechanism (electrical, not software): the sweep's
current transients sagged the node's regulator, which also feeds the CAN
TRANSCEIVER - TX errors back the queue into the shared canard pool and
the node starves. The user's "feels like it needs distribution" instinct
was exactly right, in advance.

Two software facts learned on the way:
- `rcout_init()` defaults every output to k_rcin1+i, so actuator_id N
  drives OUTn with NO param changes - `SERVO1_FUNCTION=51` was already
  the default. actuator.ArrayCommand (UNITLESS, -1..1) at >=20 Hz is the
  drive recipe (a servo timeout releases outputs when the stream stops).
- The sim actuator-status sender is AP_SIM_ENABLED-only; the hardware
  command path is thin. The melt was the rail, not a message flood.

**RC_OUT is now REMOVED per user directive** ("a single message can never
tear down the CAN bus again"): hwdef drops the five PWM pin lines
(PA8-PA11, PA15) and sets AP_PERIPH_RC_OUT_ENABLED 0 (plus
HAL_SERIAL_ESC_COMM_ENABLED 0), compiling out rc_out.cpp and the
esc.RawCommand / actuator.ArrayCommand handlers entirely. Regression
PROVEN on the flashed build: 20 s of actuator+esc commands at 20 Hz each
(the exact melt reproducer) - heartbeat 20/20 beats, uptime monotonic,
GetNodeInfo answers instantly after. Re-enabling someday = restore the
pin lines + the define, and power actuators from their OWN rail.

NOTE the flasher's vcs verdict reads "unchanged" for our builds - both
sides are the same uncommitted tree. Verify custom-build deliveries BY
EFFECT (here: the node ignoring actuator commands proved the new image).

## VERIFIED: realposix flies on CAN sensors ALONE (2026-08-17)

All local I2C sensors physically removed (MPU-9150 #1, BMP280, HMC5883L
all no-ack); 90 s realposix soak on the CAN suite only, ring post-mortem:

    [hub-health] imu=0 imu2=4915-4933 baro=500 b2=0 hmc=0 mag=250 qmc=248
                 fix2=50 aux=50 ierr=0 berr=0 gbad=0 i2c_pm=0 can_pm=147

- CAN IMU ~492 Hz feeding GyroSensor/AccelSensor via the failover path,
  which announced once at boot ("LOCAL IMU SILENT - failing over") and
  is effectively primary while the local bus is empty - no code change
  needed for CAN-only operation.
- filtercf completed its calibration ON CAN SENSORS and the outer loop
  recovered (rateupdates -64 during the documented startup window, then
  -1/-3 crit=0 steady) - the full attitude chain closes on CAN data.
- Zero hub errors, i2c_pm=0 (local bus idle), can_pm ~14.7 %.
- Flight envelope on this sensing: attitude / AxisLock / AltHold. GPS
  publishes 5 Hz but indoors no-fix - GPS modes still gated on the first
  outdoor fix. Actuation (PWM out) remains the open half of "flyable".

Fallback inventory in this state: every fallback is inert by absence
(b2=0, no local IMU to stand down for). NOTE if the local MPU is ever
replugged mid-run the failover WILL stand down and hand back to local -
by design; unplugged, CAN is the sole and steady source.

**EPILOGUE (2026-08-17): the module was wired to 5 V the whole time.** The
user found and fixed it (moved to 3.3 V); re-probed immediately after: ID
'H43' correct, |B| = 49.5-49.7 uT stable across samples - agreeing with
the RM3100 (51.1) and IST8310 (46.9), and the -4096 pinning is GONE with
no bench cleanup. So the "saturation" may have been electrical (overdriven
input levels reading as overflow), not magnetic - the ferrous-offender
theory was never confirmed and should not be re-cited as settled. Both
3.3 V busmates verified undamaged by the 5 V period: MPU-9150 WHO_AM_I
0x68, BMP280 id 0x58, both ACKing normally.

## The missing ~100 Hz on the CAN IMU: found, mostly reclaimed - 457.7 Hz (2026-08-17)

User called it ("feels like the bridge code is lacking just a hair"): at
cmd 1000 the proxy loop still slept a fixed 400 us every iteration - the
static 600 us work reserve under-estimated the true per-iteration cost
(ChibiOS transfer stack + broadcasts), so the leftover sleep fired even
with no time to spare. Fix: measured-remainder pacing - timestamp each
iteration, sleep only period-minus-actual-work, chunked at 50 ms (which
also fixes the delay_microseconds 65 ms wrap floor for low rates).

    397.9 Hz -> 457.7 Hz, suite untouched.

Remaining gap to the MP1's paced 493: ~2.18 ms of true per-iteration work
(wire 520 us + ChibiOS per-transfer overhead + bus sharing with the
IST8310/BMP388 drivers + two broadcasts). That is the platform floor for
I2C-attached parts on this node; parity beyond ~93 % wants SPI or a leaner
I2C stack, not pacing tricks.

## IMUSTAT: the proxy's floor decomposed - it is the I2C STACK, not sharing (2026-08-17)

Live instrumentation (IMUSTAT over LogMessage every 5 s, still in the
flashed build) on the 458 Hz proxy:

    rd_avg=2117 us   rd_max=4588 us   bc_avg=78 us

The broadcasts are nearly FREE. The whole iteration lives in the read leg,
and its average is 4x the 520 us wire time - a UNIFORM ~1.6 ms of ChibiOS
per-transfer overhead (cross-thread semaphore handoff to the bus thread,
per call). Contention with the IST/BMP388 drivers only explains the 4.5 ms
TAIL, so quieting the aux sensors would trim spikes, not the average.

**The real 2x**: AP drivers reach 1 kHz on I2C by registering a periodic
callback that runs INSIDE the bus thread - no per-read handoff. Restructure
the proxy the same way (callback samples into a buffer, the CAN thread
consumes) and the read cost collapses toward wire time -> ~900+ Hz
potential. Queued as the next proxy iteration.

## PWM discovery: the MP1 has 4 hardware PWM channels live TODAY

    /sys/class/pwm/pwmchip0  npwm=4  device=40003000.timer (TIM4)

A quadcopter's worth of hardware PWM already exposed by the stock DT.
Local actuator detection = enumerate /sys/class/pwm (trivial, runtime).
Which pads/header TIM4 CH1-4 route to needs the schematic (sheet 11/12) -
candidate: the motor-control header JP19. CAN ESC detection: passive =
esc.Status (1034) from live ESCs; active = GetNodeInfo names on allocated
nodes (the hub already tracks per-node NodeStatus - flagging ESC nodes is
a small extension). And the L431 can BECOME a 5-channel CAN PWM node
(PA8-PA11, PA15) via HAL_PERIPH_ENABLE_RC_OUT + esc.RawCommand - a CAN
"ESC node" on this bench with zero new hardware.

### CORRECTED against the DTB + schematic (2026-08-17): it is TIM5, and ONE pad

Two errors above, both fixed by reading the actual sources:
- **0x40003000 is TIM5, not TIM4** (MP1 APB1 map: TIM2=40000000,
  TIM3=40001000, TIM4=40002000, TIM5=40003000). The DTB's own pinctrl
  node is named `tim5_pwm_mx`.
- npwm=4 but **only ONE channel reaches a pad**: pinmux 0x7b03 =
  **PH11 AF2 = TIM5_CH2**, routed to the RPi header (sheet 12). That is
  pwmchip0 **pwm1** (0-indexed CH2) - exporting pwm0/2/3 toggles nothing
  external. Verified live: pwm1 exports, runs 50 Hz / 1.5 ms, clean.
- JP19 "Motor Control" (sheet 11) is NOT hobby-PWM: it is TIM8's
  three-phase complementary pairs (MC_UH/UL/VH/VL/WH/WL on
  PI5/PH13/PI6/PH14/PI7/PH15) plus current-sense/encoder/brake lines -
  a gate-driver bridge header for FOC, wrong shape for a servo lead.
- More pads need one DT edit each (same fdtput pattern as the I2C clock):
  mikroBUS PWM pin = **PD14 = TIM4_CH3** (sheet 12, MCLICK_PWM), RPi
  header also carries **PD13 = TIM4_CH2**; TIM4's pwm node is disabled
  in the stock DT.

### PWM UNLOCK (2026-08-17): SIX hardware channels via one DT edit

TIM4 + TIM8 pwm nodes enabled with fdtput on the live DTB (backup
.pre-pwm; new pinctrl groups tim4-pwm-ninja-0 / tim8-pwm-ninja-0,
phandles 0x75/0x76; +4 nodes, dtc warnings unchanged from stock):

    pinmux 0x3d03 0x3e03           PD13/PD14 AF2 = TIM4_CH2/CH3
    pinmux 0x8504 0x8604 0x8704    PI5/PI6/PI7 AF3 = TIM8_CH1/2/3

**TIM3 added the same day** (pin 33 = PB5 = TIM3_CH2, pinmux 0x1503,
phandle 0x77, backup .pre-tim3) - a FOURTH independent timer, swept
immediately after reboot. Full recipe now lives in `dt-pwm-unlock.sh`
(reproducible on a fresh image). SEVEN channels total.

Post-second-reboot map - chip numbers SHIFT whenever a lower-address
timer is enabled; NEVER hardcode pwmchipN, find by address via
`readlink -f /sys/class/pwm/pwmchip*/device`:

    pwmchip0  = TIM3 (40001000)  pwm1=PB5  (RPi hdr pin 33)
    pwmchip4  = TIM4 (40002000)  pwm1=PD13 (pin 32)  pwm2=PD14 (mikroBUS)
    pwmchip8  = TIM5 (40003000)  pwm1=PH11 (pin 31)
    pwmchip12 = TIM8 (44001000)  pwm0/1/2=PI5/PI6/PI7 (pins 12/38/35 + JP19)

Total 6 channels; 5 verified enabled at 50 Hz immediately, and FOUR
channels across all three timers verified moving a real servo -
pin 31 (PH11/TIM5_CH2), pin 32 (PD13/TIM4_CH2), pin 38 (PI6/TIM8_CH2),
pin 35 (PI7/TIM8_CH3), pin 12 (PI5/TIM8_CH1), PD14 (TIM4_CH3,
mikroBUS PWM pin), pin 33 (PB5/TIM3_CH2) - user-confirmed motion on
EVERY ONE: **7/7 channels servo-verified across four independent
timers.** Remaining unlockable-if-ever-needed: TIM5_CH1 (PH10, on JP19
as MC_EN_A) for an 8th; TIM4_CH1 (PD12) only by sacrificing I2C1_SCL
on pin 28; TIM8's PH13/14/15 are complementary twins of existing
channels, not independent outputs. JP20 pin map now read
from the schematic crop: PWM on pins 31 (PH11/TIM5_CH2), 32
(PD13/TIM4_CH2), 12/35/38 (PI5/PI7/PI6 = TIM8 CH1/CH3/CH2 - the JP19
nets alias onto the RPi header), and pin 33 = PB5 TIM3_CH2, a seventh
channel behind one more DT enable. Grounds 6/9/14/20/25/30/34/39;
3.3 V pins 1/17; 5 V pins 2/4 = the dead-ish VBUSOTG rail. The 6th
(PD14) exposed the constraint worth knowing: **channels of one timer
share a single period register** - "Device or resource busy" when
setting a different period while a sibling channel runs. Per-channel
duty, per-TIMER frame rate: group same-rate actuators on one timer
(e.g. 4 motors at 400 Hz on one timer, servos at 50 Hz on another).

TWO traps from the same hour:
- **`ssh root@board reboot` silently did nothing once** - board pinged
  on, uptime kept climbing, and a later "verification" was tautological.
  ALWAYS verify a reboot by watching ping actually drop, then check
  `uptime` after. `systemctl reboot` went down in ~20 s.
- A wedged partial shutdown also made intermediate ssh commands return
  EMPTY output with exit 0 - if ssh output goes silent, check uptime
  before believing anything else.

## REALPOSIX DRIVES THE PWM: the actuator chain is closed (2026-08-17)

The missing output half of "realposix can fly" is in:

- **pios_servo.c grew a real Linux-pwm backend** (PIOS_REALPOSIX-gated;
  simposix keeps the stub): 7 outputs mapped motors-first (out0-2 =
  TIM8 pins 12/38/35, out3-4 = TIM4 pin 32 + mikroBUS, out5 = TIM5
  pin 31, out6 = TIM3 pin 33). Chips found BY ADDRESS at lazy init
  (numbering shifts - TIM8 probed as pwmchip12 this boot). A bank IS a
  timer, matching the shared-period hardware rule 1:1. Hot path is
  snprintf+pwrite only - no stdio (shmlog lesson). Init logs each
  mapping to the ring: "[servo] out6 -> TIM3_CH2/PB5/pin33 (...)".
- **THE GATE THAT HID EVERYTHING: actuator.c's set_channel was stubbed
  `#if defined(ARCH_POSIX)`** - every posix build silently discarded
  channel writes (simulation-era leftover). Symptom worth remembering:
  ActuatorCommand.Channel showed the right values over telemetry while
  the pads stayed at zero - the UAVObject side is NOT proof the
  hardware was touched. Now `&& !defined(PIOS_REALPOSIX)`.
- **Mixer-driven motion PROVEN over UAVTalk from the Mac** (pyuavtalk
  straight at 192.168.0.90:9000): set Mixer7Type=Servo +
  ActuatorSettings ChannelNeutral[6] swept 1100/1900/1500 - the
  disarmed failsafe path (setFailsafe writes ChannelNeutral to
  Servo-type channels every ActuatorDesired timeout) drove pin 33,
  sysfs duty tracked to 1500000, servo moved. ChannelAddr defaults are
  the identity map 0..11, so flight channel N = driver out N.
- Settings written live are NOT persisted - a firmware restart reverts
  to defaults (the "servo moved" heard during a restart was a
  transient, disproven by duty=0; re-config after every restart or
  save via ObjectPersistence).

## THE STABILIZE-DEMO HUNT: four gates found, one still closed (2026-08-17)

Goal: armed Attitude-mode stabilization driving the pin-33 servo from the
CAN IMU. Four sequential gates were found; three are OPEN, documented
with their recipes, and the chain is proven up to the LAST hop:

1. **Arming needs a valid RECEIVER, not just Always Armed.** The
   Always-Armed branch of armhandler.c only runs in the throttle-low
   path; with no RC, ManualControlCommand reads Connected=False,
   Throttle=0.00 (not low) and arming never fires. Recipe (the bridge's,
   replayed over UAVTalk from the Mac): ManualControlSettings
   ChannelGroups=[5,5,5,5,5,7,7,7,7] / ChannelNumber=[1..5] (GCS group),
   then STREAM GCSReceiver at >=20 Hz (it goes stale in 100 ms) with
   throttle 1000. Verified: FlightStatus -> Armed.
2. **Stabilized-bank settings only latch on a flight-mode TRANSITION**
   (the StabilizationBank-mirror family): writing
   Stabilization1Settings=Attitude changed nothing until the GCS mode
   channel toggled 2000->1000, forcing a mode change. Verified:
   StabilizationDesired modes Rate,Rate -> Attitude,Attitude.
3. **Rate mode is why a tilted-but-still board commands nothing** - the
   default Stabilized1 banks are Rate; a stabilize DEMO wants Attitude.
   With Attitude latched and the bench IMU at +117 deg roll,
   ActuatorDesired.Roll saturated to -0.878. THE WHOLE CHAIN LIVES:
   CAN IMU -> hub -> failover -> filtercf -> outer/inner loops ->
   ActuatorDesired.
4. **SOLVED - and it was never the queue.** Ring instrumentation showed
   the queue PERFECT (recv_ok 1:1 with innerloop Sets, zero timeouts,
   connect_rc=0) while UpdateTime stayed 0. The real gate:
   **actuator.c refuses to mix with fewer than TWO active mixers**
   ("Nothing can fly with less than two mixers" -
   `if (mixer_settings_count < 2) ... continue;`) - the single-servo
   bench config (only Mixer7) tripped it silently on every event, every
   boot. Fix is pure config: declare a second mixer (Mixer8=Servo on
   the inert 8th channel). RESULT: **ch6 jumped 1500 -> 1062 us, the
   saturated roll correction from the +118 deg tilt - the FULL chain
   CAN IMU -> attitude -> stabilization -> mixer -> PWM -> servo is
   CLOSED and moving metal in Attitude mode.** The queue-starvation
   readings that started this hunt were all taken on WEDGED firmware
   instances (see below) - UpdateTime==0 on a healthy boot was the
   two-mixer guard, not events.

The two instabilities, BOTH root-caused the same day:
- **The ring dump-empty state = a STALE CORRUPT RING FILE.** The writer
  attaches to an existing /dev/shm/ninjapilot-log; one left with insane
  head/tail (from a shmlogd killed mid-read) reads as forever-full and
  every write drops. Fix: `rm /dev/shm/ninjapilot-log` while the
  firmware is stopped - it creates a fresh ring at boot. Rule: delete
  the ring file on every firmware restart.
- **The AttitudeState freeze = the stdio convoy RETURNED through the
  systemd pipe.** pios_led.c still had a RUNTIME printf ("PIOS: LED...")
  per heartbeat toggle; block-buffered stdout fills 4 KB over minutes,
  then flushes in ONE blocking write into the journald pipe - a stall
  there blocks the task WHILE HOLDING the process-wide stdio lock, and
  the event-driven chain (Sensors -> StateEstimation -> inner/outer
  loops) convoys to death while the hub pthread, telemetry and actuator
  task live on. Ring forensics: [inner] Set counter and innerloop
  watchdog died at the same second while [actu] timeouts started
  climbing and hub-health continued. Fixes: the printf is compiled out
  for realposix, AND the firmware now launches with
  `-p StandardOutput=null -p StandardError=null`. No wedge since.
  RULE (now twice-learned): NO stdio ANYWHERE in realposix runtime -
  init prints go to a pipe that can block too.

## 958 Hz: THE LADDER - the user demanded empiricism and the theory died rung by rung (2026-08-17)

"prove your theory... 50hz bumps until it falls over. find the real max,
not theoretical." It NEVER fell over. Every claimed ceiling died:

    clamp   delivered   symmetry   overruns   aux suite
    500     491.8       exact      0          full     (the old "max")
    600     ~590        exact      0          full     ("node ceiling" - wrong)
    650     637.0       99.99%     0          full
    700     683.1       99.99%     0          full     (1589 fr/s - past the old "death zone")
    750     730.5       100.00%    2fr/27s    full
    800     783.3       100.00%    0          full     (sampling-limited, 1250us callback)
    1000*   958.6 wire  100.00%    0          FULL - baro 50, mag 25, GPS 5
            959.7 hub   (*callback 1250 -> 1000 us + clamp 1000)

THE REAL MAX = ~960 Hz, limited by the MPU-9150's OWN 1 kHz accel output
rate - the silicon, not the node, not the wire, not the receiver. Wire at
2141 fr/s (~32 %), MP1 ingesting everything with zero overruns and
healthy loops (imu2=9597/10 s). Three dead theories, each disproven by a
rung: "wire destabilizes >1200 fr/s" (the receiver's log cascade),
"~590 is the node I2C/loop ceiling" (pacing overhead, scales with clamp),
"1 kHz callback starves aux to 14/7 Hz" (measured in the 100 kHz-clamp
era when reads took 2.1 ms; at true 400 kHz reads are ~520 us and
EVERYTHING fits). Ladder ops note: CAN flash delivery got flakier during
the ladder (several mode-2 holds; one run took 4 attempts) - flash with
fw_realposix STOPPED and just retry with patience; allocatord was seen
at ~23 % CPU and is worth an eye.

## 589 Hz: the clamp raised to 600 once the log-loop myth died (2026-08-17)

The user asked the right question ("can we pull faster now?"): with the
MP1 log-amplification loop dead, the old "wire destabilizes >1200 fr/s"
conclusion was re-tested and DISPROVEN - it was the receiver's own
logging cascade all along. Node clamp raised 500 -> 600 (imu.cpp),
flashed (flash retries needed - flash with fw_realposix STOPPED, the
running firmware's CPU+bus load starves the file server):

    delivered   ~590 Hz wire (18837/18837 EXACTLY symmetric)
                589.1 Hz through the hub (imu2=5891/10 s)
    bus         ~1400 fr/s total, overrun delta ZERO (firmware running too)
    suite       baro 50 / mags 25+25 / GPS 5 - untouched
    loops       watchdog rateupdates -1..-4, no crit

590 is the NODE's own physics ceiling (I2C read + loop overhead), the
same number the pre-storm unclamped observations hit - the clamp at 600
leaves it the binding constraint. Beyond ~600 wants SPI-class hardware
or a leaner node loop, not a bigger clamp. Guardrail v3 + soft-start
remain armed underneath.

## FLIGHT CONFIG ERA: QuadX saved onboard, Revolution masquerade, event queue widened (2026-08-17, night)

- **realposix now reports BOARD_TYPE 0x09 (Revolution)** instead of the
  unknown 0x11, so the GCS wizard/uploader recognize it. Revo is the
  closest real board (6 outputs, full sensor suite). Revo-specific wizard
  pages (SPI cal, radio) may look odd - vehicle/output config works.
- **Event dispatcher queue 20 -> 64** via PIOS_EVENTDISAPTCHER_QUEUE
  (typo is upstream's) in realposix pios_config.h - the shared
  ConnectCallback queue overflowed on config bursts and dropped
  notifications silently (the EVENT tile's orange flashes).
- **QuadX config written AND PERSISTED via ObjectPersistence** (survives
  firmware restarts, greets the wizard): AirframeType=QuadX, Mixer1-4 =
  Motor with the standard X matrix (NW 64/64/-64, NE -64/64/64,
  SE -64/-64/-64, SW 64/-64/64, throttle 127), motors on out0-3 =
  TIM8 pins 12/38/35 + TIM4 pin 32, ChannelMin/Neutral/Max
  1000/1100/2000, banks 400/400/50/50 Hz, MotorsSpinWhileArmed FALSE.
- **RATE A/B MEASURED - the 958 Hz stream is FREE**: innerloop watchdog
  warn incidence 39/60 at 492 Hz vs 41/60 at 959 Hz (identical). The
  STAB flicker is NOT sensor-rate CPU load; it is the outer-loop
  callback cadence running marginally behind its 4-update window at ANY
  rate - structural scheduling granularity, the same -1..-3 rateupdates
  every healthy soak has shown. Keep max rate: lower latency, no cost.
  (My CPU-load hypothesis: disproven out loud, per the repo rule.)
- str.replace on '#define PIOS_REALPOSIX' hit the _I2C_DEV/_CAN_IF
  prefixed defines too and mangled the header - anchor unique strings
  (newline-terminated) when patching defines programmatically.
- pios_config.h touches = FULL rebuild on the board (~12 min on 2 cores);
  run it as a detached systemd unit, never inside an ssh timeout.

## THE MP1 LOG-STORM FEEDBACK LOOP: how a healthy bus looks broken (2026-08-17)

After the IMU cord replug, every census showed "storm signatures"
(pair asymmetry 10:1, NodeStatus missing, node-125 mag at 3 Hz, ~10 %
delivery) while node 124's own telltales read HEALTHY (mode 0, guardrail
clear, clean IMUSTAT) and the MP1 transceiver saw a clean wire
(ERROR-ACTIVE, berr 0/0). Cause: **MP1-side CPU starvation feedback** -
RX FIFO loss -> m_can logs EVERY lost frame -> journald churns (41 %
CPU, loadavg 10 on 2 cores) -> CAN IRQ starved -> more loss. The frames
never made it off the controller; every "wire" symptom was RX-side.
Break the loop: `systemctl stop systemd-journald.service
systemd-journald.socket systemd-journald-dev-log.socket` + `dmesg -n 1`;
the bus healed INSTANTLY (5896/5896 symmetric, zero overrun delta).
Rules: (1) loadavg is part of every bus diagnosis on this board;
(2) node self-telltales (mode, vendor bit 15, IMUSTAT) outrank MP1-side
censuses; (3) the m_can per-frame error logging is an amplifier -
consider rate-limiting it permanently.

### FIRST ACTUATOR MOTION (2026-08-17): a real servo swept from PH11

Signal on PH11 (RPi header), ground on pin 34, servo powered from its
OWN external 5 V (the servo-melt lesson applied) - full sweep
1.5/1.0/2.0 ms x2 via sysfs, user-confirmed motion ("that absolutely
moved it"). The working recipe, including the sysfs constraint that
bites (duty must be lowered BEFORE the period can shrink below it):

    cd /sys/class/pwm/pwmchip0; echo 1 > export; cd pwm1
    echo 0 > enable; echo 1000000 > duty_cycle   # duty first!
    echo 20000000 > period                       # 50 Hz
    echo 1500000 > duty_cycle; echo 1 > enable   # 1.5 ms center
    # 1000000..2000000 ns sweeps the range

With CAN-only sensing verified the same day, the MP1 now has BOTH
halves in primitive form: flight-rate sensors in, and one hardware PWM
out. Next rungs: PIOS actuator driver on this pwmchip, DT-enable TIM4
for PD13/PD14 (two more channels), then an ESC on external power.

## THE 100 kHz CLAMP, proxy v3, and the storm that killed journald (2026-08-17)

**Root cause of the 458 Hz ceiling, three layers deep, each disproven
honestly:**
1. v2 theory "cross-thread handoff costs 1.6 ms" - DISPROVEN by v3: moving
   the read into the bus thread via register_periodic_callback measured the
   IDENTICAL 2.1 ms cadence. The transfer itself was slow.
2. 2.1 ms for a 14-byte burst = the 100 kHz signature. Culprit found in
   AP_HAL_ChibiOS/I2CDevice.cpp line 54: **`#define HAL_I2C_MAX_CLOCK
   100000`** - the HAL silently clamps EVERY bus to 100 kHz regardless of
   the bus_clock a device requests. Every "400 kHz" request all session was
   theater. Fix: `define HAL_I2C_MAX_CLOCK 400000` in the hwdef (all parts
   on this bus are 400k-capable).
3. Unclamped, the proxy immediately produced ~600 Hz observed - and THE
   PRODUCER OUT-RAN THE ECOSYSTEM.

**Proxy v3 architecture** (imu.cpp): sampling runs inside the I2C bus
thread via register_periodic_callback (1250 us - 1 kHz oversubscribed the
bus thread and starved the baro/mag drivers to 14/7 Hz, measured); a
seqlock hands samples to the publish loop, which only broadcasts.
IMUSTAT telemetry stays in the build.

**THE STORM CASCADE (the user's dmesg):** at saved INS_SAMPLE_RATE=1000
the unclamped node emits ~1600+ fr/s -> wire/receiver destabilizes
(>~1200 fr/s) -> MP1 m_can RX FIFO overruns at full rate -> the driver
logs EVERY lost frame -> /dev/kmsg overruns -> systemd-journald CORE
DUMPS. Three-stage cascade whose root cause is "the sender got faster".

**THE BOOT-STORM TRAP (the durable lesson): saved params are calibrated to
the OLD physics.** After the bus-clock change, the saved 1000 re-created
the storm on EVERY boot before any command could land - RestartNode,
param blasts, boot-window barrages all failed; the node was deaf within
seconds of every reboot. Software recovery IMPOSSIBLE. Fix: the rate
ceiling is now HARD-CLAMPED at 500 in code, so no saved value can poison
a boot. Rule: when changing transport physics, re-derive every saved
rate's safety FIRST, or clamp in code.

Recovery: emergency 500-ceiling build + power-cycle ambush (re-Begins
automatically if a transfer aborts). Storm-state wire also broke pair
symmetry (accel << gyro) - partial-pair loss is a storm signature.

## WHY DEGRADEDHZ NEVER FIRED IN THE STORM - and guardrail v3 (2026-08-17)

The user called it: "the degradation checker didn't meet conditions to
degrade itself." Correct, and it is TWO gaps compounding:

1. **The detector was blind to this failure class.** Its trip condition
   was canard_broadcast returning false - pool exhaustion at ENQUEUE. In
   a wire-error storm the enqueue keeps succeeding and the frames die on
   the wire: queued != transmitted (documented at the first ramp test,
   walked straight through here). The 15 s boot grace also delayed arming
   past the moment the boot-storm latched.
2. **Even a firing detector would have spared the arsonist.** The
   IMU-priority policy ("never throttle the IMU") taken literally exempts
   the exact stream causing the storm. An IMU stream on a dead bus is
   0 Hz - so "IMU priority" must mean LAST to degrade, never EXEMPT.

**Guardrail v3** (in the flashed safe build, imu.cpp publish loop):
- **Wire-health signal**: canard pool occupancy
  (canardGetPoolAllocatorStatistics, current_usage_blocks), checked every
  500 ms. Frames queued but not draining pile up in the pool - this sees
  wire-level distress that enqueue-failure counting cannot.
- **Tiered backoff**: >60 % occupancy -> aux streams cap at 5 Hz first
  (unchanged policy), AND the IMU divides its rate 1/2 -> 1/4 -> 1/8 with
  a hard floor of 100 Hz. Recovery is stepwise (halving the divider) only
  after 5 s of <25 % occupancy. bit-15 telltale still latches.
- **Soft-start**: effective rate ramps 100 -> 500 Hz over the first 10 s
  of every boot regardless of the saved param - so no saved value can
  ever storm a boot again, independent of the hard 500 ceiling.

**Recovery + verification (same day):** with the MPU unplugged the node
boots quiet even on the poisoned saved param (proxy exits at probe), so
the flash landed normally - remember this: PULLING THE IMU IS THE
UNIVERSAL DE-STORM. Flash #1 delivered but parked in mode 2 (the ~50 %
delivery lottery); the retry booted 3 -> 1 -> 0. Post-flash identity
reads sw 1.9 vcs=381357f8 - that vcs is ~/ardupilot's HEAD (all work is
uncommitted patch-on-top), so it is OUR build's identity, not the old
firmware's.

**MEASURED, the v3 steady state (saved INS_SAMPLE_RATE still 1000):**

    CAN MPU-9150 proxy   491.8 Hz sustained  (clamp 500 binding; pair
                         symmetry EXACT, gyro==accel frame counts)
    baro 50.0 / mag 25.0 / node-125 mag 25.0 / GPS suite 5.0 - all nominal
    total bus ~1215 fr/s, RX overrun delta ZERO across loaded windows
    IMUSTAT: n=2466/5s (493 Hz), bc_avg~58 us

The boot-with-poison test passed by construction and by observation:
multiple boots at saved 1000, zero storms. 492 Hz over CAN vs 493 Hz
local paced = TRANSPORT PARITY with the MP1's own bus. The clamp, not
physics, is the current ceiling (unclamped pre-storm observations hit
~590-600); raising it is gated on proving the pool-occupancy guardrail
under real induced distress first. The old m_can loss at uptime 18511 s
and abs overrun 6400 are storm-era residue - always judge by DELTA.

## Native board identity + honest health tiles (2026-08-17, evening)

- **realposix is its own GCS-recognized board now: BOARD_TYPE 0x11 restored**
  (board model 0x1101). The Revolution masquerade (0x09) is gone. GCS side:
  `CONTROLLER_REALPOSIX` in vehicleconfigurationsource.h; 0x1101 detection +
  "NinjaPilot RealPosix (OSD32MP1)" combo entry in controllerpage.cpp; case
  fallthroughs beside every CONTROLLER_REVO gate (setupwizard.cpp,
  connectiondiagram.cpp, vehicleconfigurationhelper.cpp, inputpage.cpp);
  "RealPosix" in devicedescriptorstruct.h (matches the fw_realposix filename
  convention); Revolution artwork reused in uploader device widgets.
- **TRAP: BOARD_TYPE lives in pios_board_info.c's objects, and make does not
  track board-info.mk.** After changing BOARD_TYPE the incremental build only
  regenerates firmware_info.c and the board still reports the OLD type over
  UAVTalk. `touch flight/pios/posix/pios_board_info.c` and rebuild.
- **STAB tile red was the gyro-coalescing watchdog, not a control failure.**
  innerloop's `gyroupdates > 1 warn / > 3 crit` assumes the STM32 design
  where the inner loop turns around once per gyro sample. On realposix the
  transport (959 Hz) deliberately outruns the loop (~200-400 Hz, always
  consuming the LATEST sample), so 2-6 samples/pass is steady state.
  Diagnosed from shmlog: rateupdates -1/-2 (outer loop healthy) while
  gyroupdates 2-6 tripped crit. Fixed under PIOS_REALPOSIX: warn > 8
  (~<120 Hz), crit > 16 (~<60 Hz). STAB now reads OK.
- **INPUT responds now: ManualControlSettings persisted onboard** with
  ChannelGroups GCS on Thr/Roll/Pitch/Yaw/Mode (ground/pyuavtalk/
  persist_gcs_receiver.py, saved via ObjectPersistence, verified across
  restart). Receiver alarm sits at Warning until something streams
  GCSReceiver - the GCS Control gadget (with joystick support) or a script.
- **GCS defaults to the board**: default_configurations seeds IPconnection
  UDP 192.168.0.90:9000, and connectionmanager.cpp now auto-selects the
  first "UDP:" entry in the connection dropdown when the GCS is idle
  (serial ports used to win by list order).
- **OPEN: ATTI Warning = the estimator's 10ms staleness watchdog**
  (stateestimation.c: callback woken by timeout with updatedSensors==0 and
  >TIMEOUT_MS since the last real sample -> FILTERRESULT_WARNING). It
  re-fires at least every ~100ms on the bench even though StateEstimationCb
  totals ~1000 calls/s, so either the 959 Hz feed really has frequent >10ms
  delivery gaps (hub aux work? Linux scheduling?) or PIOS_DELAY_DiffuS
  misreports on this platform. Instrument the actual gap distribution
  before touching TIMEOUT_MS - do not blind-relax the threshold.
- **Wizard "Next" gate**: controllerpage.cpp isComplete() only accepted
  connections named "USB:"/"Serial:" - a detected board on "UDP:" could
  never proceed. UDP/TCP now accepted.
- **ground/pyuavtalk/health_monitor.py**: the System Health tiles without
  the GCS. One-shot table (tile, alarm, status, GCS color, why), --watch N
  transition timeline with JSONL log + incidence summary, --enable-fclogs
  (DebugLogSettings Always + SystemAlarms/FlightStatus onchange +
  SystemStats 1s periodic logging metadata, persisted). Slots are host
  files /usr/local/ninja/fcwd/233CDC*.o* - scp + decode_fcwd.py. NOTE:
  one UDP client at a time - running it steals a live GCS link.
- **The ATTI/STAB/EVENT flicker is ONE phenomenon** (measured, host
  monitor + onboard log agree): ~1.2s degraded windows recurring every
  ~1.8s median. In a window: estimator 10ms staleness timeouts (ATTI),
  gyro coalescing >8/pass (STAB), AttitudeState callback queue overflow
  (EVENT orange; SystemStats.ObjectManagerCallbackID latches AttitudeState).
  Onset phase is UNIFORM within the second - NOT aligned to the 1 Hz
  telemetry/SystemStats cadence (hypothesis tested and dead). The ~1.8s
  rhythm with uniform phase suggests a BEAT between two near-equal rates
  (wire 958.6 Hz vs hub 959.7 Hz gives ~0.9s; 2x = 1.8s). Confirm with
  shmlog gyroupdates series once the ring is healthy again - the ring is
  currently in the corrupt/dump-empty state (rm + firmware restart ritual).
- **Onboard DebugLog is now Always + persisted** on the bench board:
  233CDC slots accumulate in fcwd between sessions - purge before timed
  comparisons, and expect ~1 slot per few seconds from SystemStats 1s.

## The health-tile flapping ROOT CAUSE + fixes (2026-08-17, night)

The ATTI/STAB/EVENT oscillation was NOT the sensor rate (wire was already
~490 Hz - the 958 Hz state died with the boot-storm reflash; INS_SAMPLE_RATE
saved=500, delivered 490.8 Hz; nothing consumes more, ~1 kHz buys nothing).
Three stacked causes, isolated by A/B (ring-only vs client-attached):

1. **Telemetry at +7 preempted the estimator band whenever a GCS was
   connected.** telemetry.c's SIMPOSIX elevation (telemetry IS the sensor
   bus under external physics) leaked into realposix, where telemetry is
   ordinary GCS chatter. Now +2 under PIOS_REALPOSIX. Flapping was
   client-correlated: ring-only watch clean, client watch ATTI 54%/STAB 31%
   warn -> after fix 95%/89% OK.
2. **DebugLog "Always" self-excited**: alarm transition -> onchange log
   write -> stall -> new transition; EVENT cb-error latched GyroSensor
   (= innerloop dispatch drops). Keep OnlyWhenArmed for flights.
3. **The IMU node itself was service-deaf** (canard pool starved) during
   the original measurements - its clumped TX was the "1.2s windows every
   1.8s" signature. A node power-cycle cleared it. dronecan-python on this
   bus needs the PER-FRAME exception wrap (node._recv_frame monkeypatch,
   see /home/root/set_ins_rate.py) - wrapping spin() drops whole batches
   including service responses ("NO RESPONSE" while streaming).
- **stateestimation TIMEOUT_MS 10 -> 50 under PIOS_REALPOSIX**: 10-20ms CAN
  delivery jitter is endemic/harmless here; 10ms assumed DMA-local sensors.
- **shmlog ring can no longer wedge**: the writer advanced head on DROPPED
  writes, so any consumer-less period pushed head unrecoverably far past
  tail (writers drop forever, readers see empty - "dump-empty corrupt ring").
  Now a Vyukov CAS claim (head only advances into writable slots), init
  self-heals insane rings (no more rm ritual), generation counter lets
  shmlogd resync across firmware restarts. Also: two concurrent shmlogd
  readers still corrupt each other - one reader at a time.
- **New tiles** (all verified live): MAG = RM3100 delivery (sensors.c owns
  it only under Basic fusion; filtermag owns it in mag chains); CAN tile
  (SystemAlarms I2C slot; SVG tile added at the MAG column, CONFIG row):
  greyed=never seen, green<50%, orange>50%, red>80% or bus-death; BATT =
  power source via DWC2 GOTGCTL bit19 VBUS: green=jack/AC, orange=USB
  (VBUS raised by any powered cable - caveat in pios_sensors_hub.h).
- **TIME tile** = FlightTime alarm = the Battery module's estimated
  remaining flight time from consumed mAh - NOT GPS time. Uninitialised
  here because no battery module/sensor runs.
- **Uploader board art**: this fork's qrc dropped gcs-board-revo.png with
  the Revo purge, so any case pointing at it rendered BLANK silently.
  realposix now ships its own drawn gcs-board-osd32mp1.png.

## RT scheduling, the real CPU picture, and the wizard-save wipe (2026-08-18)

- **The remaining tile flicker was scheduling, and RT recovers most of it.**
  With chrt -f -a -p 30 on the firmware: EVENT 100% / ATTI 98.2% / STAB
  94.2% OK over 90s with a client attached (from 50/50 flapping at the
  day's start). chrt does NOT survive a firmware restart - prior sessions'
  RT state silently vanished on every systemd-run restart. This image's
  systemd (v244) REJECTS CPUSchedulingPriority on transient units, so the
  launch ritual is now: start fwrp unit, then
  `chrt -f -a -p 30 $(pgrep -f fw_realposix.elf | head -1)`.
  Proper fix queued: a real .service file.
- **The box is NOT idle: the firmware itself burns ~118% of the 2 cores**
  (54 us / 43 sy, 0 idle; loadavg ~6) while its own CPULoad UAVO says 50%.
  The sy share points at the posix port's 1 kHz tick + context-switch
  futex/signal traffic. This self-contention is the rest of the flicker -
  profiling it is the path to 100% green (task #75).
- **A momentary grey+X tile = telemetry link blip**, not firmware state:
  on disconnect the GCS's object copies revert to defaults (Uninitialised)
  until re-received. Two UAVTalk clients on port 9000 (GCS + health
  monitor) steal each other's packets and cause exactly this - one client
  at a time, always.
- **TRAP: a firmware restart under an active wizard save wipes settings.**
  The wizard hung at "Preparing mixer settings" when fwrp restarted
  mid-save, the GCS crashed on reconnect churn, and MixerSettings was left
  ALL-Disabled (OUTPUT Critical) - the QuadX motor mixers gone. Restored
  from the documented baseline + persisted (verify: ObjectPersistence
  Operation=Completed). GCS hardening queued (task #74). Never restart the
  firmware while a GCS save/wizard is in flight.
- **CPUSerial is real now**: pios_sys.c (posix) reads the STM32MP1 96-bit
  UID from /sys/firmware/devicetree/base/serial-number (fallback
  /proc/cpuinfo Serial); simposix hosts without either keep the FF..FF
  placeholder. Verified over UAVTalk: 002e00463231510531333437.

## ZERO-transition health, the hub spin trap, and the bench mag setup (2026-08-18)

- **FLICKER FULLY DEAD: 0 transitions in 121s** (ATTI/STAB/EVENT 100% OK,
  client attached) with the full stack: telemetry at +2, RT via chrt,
  hub poll() fix below, INS_SAMPLE_RATE=250 (bench value, saved on the
  node; 500 restorable via /home/root/set_ins_rate.py - the node answers
  services only in its fresh-boot window, so expect NO RESPONSE prints
  while streaming; VERIFY BY MEASURING candump, the set usually landed).
- **The 50%-CPU "init" thread was the sensor hub busy-spinning.** The
  hub thread inherits its spawner's name (now prctl's "sensorhub"), and
  its sleep was computed from next_imu, which only advances when the
  LOCAL IMU is present - with the MPU unplugged it froze in the past and
  the loop polled CAN at ~3200 read()/s. Now: due considers enabled
  sources only, and the wait blocks in poll() on the CAN socket (woken
  per frame - same latency, ~5% CPU). Firmware total 118% -> ~75-90%;
  the freed core un-starved the estimator band (that was the residual
  ATTI/STAB flicker).
- **TRAP: pgrep -f 'fw_realposix.elf' can match a stray sh** - chrt'd
  the wrong process once. Use `systemctl show fwrp-native -p MainPID
  --value`.
- **Whole-object-write trap RE-CONFIRMED, self-inflicted**: sending
  RevoSettings with only FusionAlgorithm zeroed every other field
  (MagnetometerMaxDeviation [0,0] -> filtermag rejected everything,
  MAG Critical). ALWAYS read-modify-write settings objects. AND:
  filtermag caches revoSettings AT CHAIN INIT - new thresholds need a
  FusionAlgorithm flip (Basic and back) or reboot to load.
- **Bench mag state (persisted)**: Complementary+Mag, HomeLocation.Be =
  measured bench field [-171.9, 115.2, 385.9] mGauss (current orientation
  == yaw 0 by construction), MagnetometerMaxDeviation [1.5, 2.5] to
  accept the indoor field on the tilted board. Yaw now follows the
  RM3100; MAG tile = filtermag's judgment, green. This is a BENCH
  calibration - proper mag cal is the ConfigRevoWidget resurrection.
- **The stock health SVG had a fully wired I2C tile all along** (I/O row,
  x=57.9 - state rects order their attributes differently than the grid
  scan expected). It is now labeled CAN and lights from our bus-health
  alarm; the duplicate spare-box tile and both "?" placeholder boxes are
  removed.
- **BATT/voltage on this platform**: VBUS presence (USB vs jack) is the
  only power signal identified; the two enabled ADC channels
  (in_voltage0/1 on adc@48003000, raw 2311/432) have UNKNOWN nets without
  the RED schematic - identify empirically by switching supplies while
  watching raw values. STPMIC1 has no input-voltage telemetry.
  health_monitor prints POWER SOURCE: USB/AC from the Battery alarm.

## The frozen compass: node 125 wedged, not the plumbing (2026-08-18, late)

- User rotated the RM3100 and NOTHING moved. Verified the entire GCS
  plumbing chain live (node 125 frames -> hub.mag_ga -> MagSensor ->
  filtermag -> MagState -> yaw): values present at every stage - but
  CONSTANT. Raw candump: node 125's MagneticFieldStrength spread over
  40s of physical rotation = 1-2 mGauss (noise floor). The node is
  HALF-WEDGED: broadcasts NodeStatus + its last mag reading at 25 Hz,
  answers NO services (GetNodeInfo times out), uptime 8000s+ - it did
  NOT share node 124's power cycle (separate supply). Remedy: power
  cycle the RM3100 node itself. Verify revival: candump spread moves
  when rotated, GetNodeInfo answers.
- **Mag topology now as intended**: RM3100 (node 125) -> MagSensor =
  PRIMARY fusion mag; QMC5883P on the M9N GPS module (node 124) ->
  AuxMagSensor (sensors.c publishes from hub.qmc) = aux/display.
  AuxMagSettings.Usage=OnboardOnly persisted so the uncalibrated QMC
  (bench |B| ~76 uT vs RM3100 ~51) never fuses. Set Usage=Both/AuxOnly
  to let filtermag use it.
- Node identity crib: 124 = org.ardupilot.MatekL431-Periph (IMU, baro,
  GPS, QMC, IST8310); 125 = the RM3100 DroneCAN mag unit.

## Boot chain + the compass identity mystery (2026-08-18, late)

- **Full unattended boot recovery is in place** (user requirement: a
  reboot mid-anything must come back flying-ready). /etc/systemd/system/
  ninjapilot.service (reference copies in osd32mp1/systemd/): firmware
  enabled at boot, CPUSchedulingPolicy=fifo prio 30 IN THE UNIT (works in
  real unit files; only systemd-run transient units reject it),
  StandardOutput=null, Restart=on-failure, ordered After=Wants=
  dronecan-allocator.service (which was already enabled and brings can0
  up itself in ExecStartPre). Verified: fresh boot -> allocator + firmware
  up unaided, threads FF/RT, no chrt ritual needed anymore.
- **DebugLogSettings persisted as OnlyWhenArmed** (was persisted Always -
  would have resurrected the self-exciting log loop on every boot).
- **GCS auto-connects the configured UDP device at launch** (one-shot in
  connectionmanager.cpp updateConnectionDropdown; manual disconnects stay
  disconnected).
- **OPEN - the RM3100 mystery is now PHYSICAL-IDENTITY, not software.**
  Node 125's stream: bit-level LSB noise flows (5 unique payloads/20s -
  live sensor sampling), values changed across the bench power cycle
  (fresh read), every software stage verified live... yet the user
  rotating "the RM3100" produces ZERO swing in node 125's raw CAN frames
  (three separate 40-45s captures). GetNodeInfo NO RESPONSE even fresh -
  possibly this node's normal (minimal firmware), not a wedge.
  ground/pyuavtalk/mag_live.py = self-serve dual-compass viewer (1 Hz,
  flags >20 mGa movement with *); the MAGNET TEST is the decisive
  discriminator: a magnet/steel tool held to the true node-125 sensor
  swings hundreds of mGa regardless of orientation. Candidates: whatever
  the RM3100 breakout actually wires to vs the unit in hand.
- **Compass semantics + bench MagKp**: the heading gauge is fused yaw -
  gyro moves it INSTANTLY, the mag only steers it back at MagKp. Stock
  0.01 = tens-of-seconds correction (invisible on the rose); bench value
  now 0.2 (persisted) so mag steering shows in seconds - which makes the
  GCS compass itself the magnet-test instrument: board still + magnet on
  the true node-125 sensor -> visible swing. "Compass follows the IMU"
  reports are this, not a display wiring fault. Flight tune should
  revisit 0.2 (high gain couples mag noise into yaw).
- **REVERSAL: node 125 was NEVER wedged - the magnet test proved both
  mags live** (RM3100 4899 mGa / QMC 10994 mGa with a magnet against
  them vs ~440/~647 baselines). The "frozen during rotation" captures
  were TIMING artifacts (rotations outside the capture windows). The
  services-dead behavior is the node's normal minimal firmware. AND the
  reason a magnet never moves the HUD: filtermag's magnetic-anomaly
  validation rejects any sample whose field deviates hugely from Be -
  BY DESIGN (power lines/steel must not steer heading). Valid HUD demo:
  magnet away, board still, rotate the mag <=90 deg - direction changes,
  magnitude stays earthlike, sample accepted, MagKp 0.2 steers visibly.
  RM3100 startup sequence (CMM init): node 125's firmware does it -
  confirmed by the magnet response.
- **CLOSED: mag -> heading VERIFIED live** (75s adjudication trace):
  magnet near = anomaly-rejected, yaw parked; magnet away = accepted
  values track raw exactly; mag ROTATED (z-axis sign flip) = yaw
  48.9 -> 74.25 deg within seconds, board untouched. 40.6 deg of yaw
  moved purely by mag rotation. The three things that had to align:
  a mag-consuming fusion mode, sane MagnetometerMaxDeviation, and
  MagKp fast enough to see (0.2 bench vs 0.01 stock). Primary mag only
  on the HUD; QMC = AuxMagSensor numbers.
- **PFD dual raw-mag needles** (user-requested bench instrumentation):
  Compass.qml now draws two mini N-up needles flanking the fused rose -
  green "main" = raw RM3100 heading, blue "aux" = raw QMC heading, both
  atan2(-my, mx) tilt-ignored (bench-flat convention). The center rose
  stays the fused estimate; rotate IMU+mag together and all three agree.
  MagSensor/AuxMagSensor added to pfdqml's QML export whitelist. NOTE
  the needles read MAGNETIC heading of each sensor's own mount - they
  will disagree with each other by their relative mounting yaw.
- **PWR group redesigned in system-health.svg** (user spec): TIME
  (FlightTime tile) moved into the MISC zone; its old slot now holds AC
  and USB source boxes. One alarm drives all three via SVG GROUP ids:
  Battery-OK = <g> lighting BATT green + AC green; Battery-Warning =
  <g> lighting BATT green + USB green (severity Warning still means
  "USB source" on the wire - the GCS just paints it as green source
  selection now); Battery-Critical stays red on BATT alone. The
  systemhealth gadget renders whatever element carries the id, group or
  rect. TIME remains "estimated flight time REMAINING from battery
  consumption" - not a clock - and stays greyed without a battery
  sensor; the board's wall/GPS time is a different display entirely.

## Map tiles revived, PWR row respaced, PATH/PLAN demo (2026-08-18)

- **Map tiles pull again** (opmapcontrol): three stacked kills fixed -
  http-> https 301s that the code never followed (redirect-follow
  attribute now set on tile requests), deprecated subdomain OSM URL
  (now https://tile.openstreetmap.org/z/x/y.png), and the fake 2009
  Firefox User-Agent that OSM policy blocks (now an honest
  "NinjaPilotGCS/1.0" UA). The dead GoogleMap provider is ALIASED to
  OSM so every existing config's default selection shows real tiles.
  Verified: curl with the new UA returns a real 256x256 PNG.
- **The "?" box was the extended-status slot**: SystemConfiguration-
  FlightMode/BadThrottle/UnsupportedConfig + BootFault-RebootRequired
  red overlays rendered there. They now overlay the CONFIG tile itself.
- **PWR/MISC row final layout**: BATT | AC | USB (14 wide, standard
  2.3 gaps) | divider | CONFIG | TIME, panels + rotated MISC header
  shifted right to match. Battery alarm drives BATT+source boxes via
  group ids. TIME reads green whenever USB VBUS power is present
  (sensors.c clears FLIGHTTIME - tethered = unlimited runtime).
- **PLAN vs PATH, demonstrated live**: PLAN (PathPlan alarm) orange =
  no valid plan; uploading a 5-waypoint square (bridge upload recipe:
  multi-instance Waypoint/PathAction + PathPlan CRC-8 poly 0x07) took
  it to GREEN in seconds - the flight side recomputed the CRC and
  accepted. PATH (Guidance alarm) stays GREYED until a PathFollower
  mode actually engages (PositionHold/PathPlanner while armed); green
  = following fine, orange/red = following badly. Plans are RAM-only:
  firmware restart wipes them, PLAN returns to orange.
- **GCS opens on the Flight data workspace** (mainwindow
  extensionsInitialized deferred activateModeByWorkspaceName).
- **Map fix round 2 - why the fantasy map survived round 1**: the factory
  config itself ships one opmap gadget at mapProvider=GoogleSatellite
  (was NOT aliased) and one at accessMode=CacheOnly (NEVER downloads).
  Now: GoogleSatellite/-Labels/-Terrain aliased too (satellite -> Esri
  World_Imagery XYZ, labels/terrain -> OSM; GoogleHybrid has no case of
  its own), factory CacheOnly -> ServerAndCache. TRAP: .gitignore line
  13 'core' (core-dump rule) silently swallows opmapcontrol/src/core/ -
  git add -f required. TRAP: 'make in the plugin dir succeeded' proves
  nothing - VERIFY with strings on the bundle dylib (a false positive
  also lurks: other providers already reference arcgisonline). A user
  config saved before this fix may retain CacheOnly - flip Access Mode
  in the OP Map gadget options or reset the config.
- **Map polish final**: the antique "here be dragons" chart (dragons1.jpg,
  painted as the WHOLE map-item backdrop in mapgraphicitem.cpp before
  tiles draw) is replaced by a flat dark fill - it only ever showed
  through where tiles were missing, and at min zoom around the world's
  edges. opmapgadgetconfiguration.cpp now COERCES a loaded
  accessMode=CacheOnly to ServerAndCache, so no saved config can
  silently disable tile downloads again - downloads work with zero user
  setup. Verified live by the user: Esri World Imagery rendering,
  centered on the board's GPS coordinates.
- **"Center over UAV" was a static-bench bug**: uavitem.cpp only
  recentered inside the position-CHANGED guard, so a parked UAV could
  never be followed (works fine airborne - that's why upstream never
  saw it). Follow now also recenters when the position is static, and
  the GCS toggle snaps to the UAV immediately on engage instead of
  waiting for the next position change.
- **Power tile popups rewritten** (systemhealth plugin html resources):
  Battery-Warning now reads "Power: OK - USB connected" (VBUS, bench
  power, cannot drive motors) and a new Battery-OK popup reads "Power:
  OK - AC/jack supply" - the stock "voltage has fallen below threshold"
  text was wrong for the power-source semantics. Popups are compiled
  qrc resources: edit html/ + systemhealth.qrc + rebuild the plugin.
- **Group separator anatomy** (learned by breaking it): each group's
  dark panel carries its rotated label ~3.84 units inside its LEFT edge,
  and the first tile starts ~5.25 units in (the label strip). Moving a
  divider means moving panel edge + label + first-tile x TOGETHER with
  those offsets, or the label lands in the inter-panel junction and
  disappears under the dark panels.

## ConfigRevoWidget RESURRECTED + map extent clamp (2026-08-18)

- **The Configuration workspace placeholders are gone**: configrevowidget
  (attitude/mag calibration) and configrevohwwidget (hardware ports) +
  revosensors.ui + revolution_top.png restored from pre-7f571cf87
  history and wired for board families 0x09 AND 0x11 in
  configgadgetwidget.cpp. Restoration fallout fixed: the calibration
  model sources (sixpoint + thermal/*) existed on disk but were UNLISTED
  from config.pro (nothing referenced them since the purge), and
  static const float/double in-class initializers needed constexpr
  under current clang. The wizard is NOT required for these panels -
  they are board-family UI, unrelated to the (persisted) QuadX config.
- **Map min-zoom is now dynamic** (mapgraphicitem resize): never allows
  zooming out past "world fills the window" (256*2^z >= widget side), so
  no dead margins - which previously showed the dragons chart, then
  black.
- **SVG debugging workflow that finally worked**: render locally
  (qlmanage -t -s 1200 -o /tmp file.svg), CROP with PIL and LOOK, fix,
  re-render, verify BEFORE bundling - ends the screenshot ping-pong.
  Z-ORDER TRAP: elements late in the document (state rects, the
  full-canvas "opacity" tint) paint OVER the base-layer labels; the MISC
  divider label was valid and correctly positioned through two fix
  attempts but painted-over - relocated to document end (top of stack).
  CAN label resized to fit its 11.3-wide tile.
- **Welcome tab blank after the Flight-data jump**: WelcomeMode renders
  via QQuickView in createWindowContainer; switching modes MID-show
  (the deferred singleShot jump) left the container half-mapped and
  permanently blank. The jump now happens BEFORE show() so Welcome is
  simply never the startup tab and initializes on first click.
- **THE systemhealth SVG RULE (two failures before it was learned): the
  gadget renders ONLY the element with id="background"** (plus per-state
  QGraphicsSvgItems it manages; systemhealthgadgetwidget.cpp line ~157
  setElementId("background")). ANYTHING outside that group - appended at
  document root or in its own top-level group - renders in
  qlmanage/browsers but NEVER in the GCS. This ate the first AC/USB
  base boxes AND two rounds of MISC-label fixes. All base art
  (backdrops, outlines, labels) goes INSIDE the background group; end
  of the group = top of the background z-order. State overlays are
  separate hidden layers the gadget composites itself. When verifying,
  simulate the app: whole-doc renders lie.
- **PWR/MISC divider drawn as an EXPLICIT khaki rect** inside the
  background group (the panel-gap showthrough that draws the other row
  separators rendered in WebKit but not in the app's QtSvg for this
  gap; an explicit rect is renderer-proof).
- **Welcome tab rewired to living endpoints** (user spec): Home/Wiki/
  Code Reviews/Progress Tracker -> the NinjaPilot GitHub repo (root,
  wiki, pulls, master...claude compare), Store -> Octavo OSD32MP15x
  product page, Forums -> x.com/d0tslash. ActivityPanel rewritten as an
  "Issue Tracker" portal (GitHub serves no Atom feed for issues);
  NewsPanel now feeds from the repo's commits/claude.atom - project
  news IS the commit history. Welcome QML is compiled qrc: edit
  src/plugins/welcome/qml + rebuild the plugin.
- **ActivityPanel lists live issues** via the GitHub JSON API
  (api.github.com /issues?state=all + XMLHttpRequest in QML; the
  /issues endpoint also returns PRs - filtered on the pull_request
  key). NewsPanel gotchas: GitHub Atom <title> is wrapped in
  newline+indent (must .trim() or every entry renders with blank
  lines) and <author><name> is EMPTY for unlinked committer emails -
  show the <updated> date instead.
- **Map heading-follow implies position-follow**: setMapFollowingMode
  maps heading-without-position to None, so the heading toolbutton
  silently did nothing unless position-follow was already on. The
  toggles are now paired both ways and rotation snaps immediately.
## Demo-image daemons: the kill list is applied and documented (2026-08-18)

- The OpenSTLinux demo payload (netdata + its two collector plugins,
  avahi, bluetoothd, pulseaudio, tcf-agent, iiod, ninfod, rdisc,
  rpcbind) is DISABLED on the bench board - full table, rationale and
  the one-shot disable loop live in README.md "Slimming the demo
  image". netdata was the top CPU consumer after the firmware;
  tcf-agent is an unauthenticated remote-debug listener (a genuine
  backdoor on a dev image). Verified 2026-08-18: seven of nine down;
  rdisc and rpcbind survived the first pass and need one more
  `systemctl disable --now`.
- **NEVER disable**: dropbear (the only SSH), systemd-networkd/
  resolved (the link), journald/udevd/logind/dbus (systemd plumbing),
  timesyncd, rngd. galcore threads are the GPU kernel driver, not a
  service; the per-login `dbus-daemon --session` swarm dies with its
  sessions.
- **The board HAS WiFi**: Murata 1DX module (BCM43430/1 die) on SDIO
  mmc0 - brcmfmac driver + firmware load cleanly at boot, `wlan0` and
  `phy0` exist (verified 2026-08-18), unconfigured. The Bluetooth half
  of the same module is what bluetoothd was for. A flight link or AP
  mode over wlan0 is available hardware, zero new parts.
## allocatord: kernel CAN filters cut 30-40% CPU to ~2.5% (2026-08-18)

- dronecan-python hands EVERY frame to the interpreter; at the sensor
  firehose's ~1200 fr/s the eleven-line allocator burned 30-40% of a
  core parsing traffic it discards. Fix is three SocketCAN
  CAN_RAW_FILTERs (anonymous source-0 frames, NodeStatus 341, service
  frames to node 127) so the kernel drops the rest: MEASURED 2.5%
  steady state, 5 wakeups/s, ~1.5 fr/s reaching userspace
  (/proc/net/can/rcvlist_fil match counters), GetNodeInfo still
  answered through the filter. Porting to C was considered and is not
  worth it - the CPU was frame volume, not Python.
- **FOUND EN ROUTE: the allocator has been on a crash diet forever.**
  dronecan-python has a DSDL type registered at 20500 and RAISES
  decoding our vendor compact-gyro payload against it ("Not enough
  bits") - and an exception out of an unwrapped node.spin() KILLS the
  process. Restart=always was silently absorbing the deaths. allocatord
  now carries the per-frame _recv_frame monkeypatch (the can_flash.py
  trap, same fix) + a rate-limited log of undecodable CAN ids, plus a
  guarded spin. If a vendor message ever needs a new type id, avoid
  ids dronecan-python already knows.
- Traps for anyone touching this: the socket buffers a PRE-FILTER
  backlog between make_node's bind and the setsockopt (the guard eats
  it, expect one "dropped undecodable" at startup); ps %cpu right
  after restart is startup-polluted (DSDL compile burst) - measure a
  utime+stime jiffies DELTA at steady state, and mind HZ=100 math;
  /proc/net/can/rcvlist_all's match-everything entry belongs to the
  firmware's sensor hub, not a bug.
## DT peripheral trim + the SPI DMA finding (2026-08-18)

- **Camera and audio are OUT of the device tree** (user directive):
  dcmi@4c006000, the ov5640 node on i2c@40013000, audio-controller@
  4000b000 (I2S2) and the root /sound card - all status=disabled via
  fdtput on the live DTB (backup: .pre-trim; the pwm-unlock edits are
  preserved - always edit the CURRENT dtb). Fresh boot verified: zero
  ov5640/dcmi/audio probes, flight stack auto-recovered, suite
  publishing.
- **The dmamux "Run out of free DMA requests" exhaustion is NOT
  camera/audio**: even with both trimmed, spi_stm32 44009000 still
  fails to get its TX DMA channel and falls back to PIO. Harmless
  today (spidev unused) but it matters the day the SPI IMU lands -
  the next trim candidates are cryp/hash/spare UARTs.
- **TRAP: a board reboot makes the CAN bus look dead for a while.**
  Right after reboot a 5 s candump caught 6 frames (heartbeat-ish);
  minutes later the full firehose was back. Two compounding causes:
  nodes ride through the board's can0 outage in bus-off/recovery +
  DEGRADEDHZ soft-start, and `timeout N candump | wc -l` LOSES
  buffered lines when timeout kills candump (block-buffered pipe).
  Judge the bus a minute after boot, from raw candump lines.
- **WiFi bring-up is vendor-documented on the image itself**:
  /lib/systemd/network/51-wireless.network.sample contains the whole
  recipe, and wpa_supplicant@.service expects
  /etc/wpa_supplicant/wpa_supplicant-wlan0.conf. Strip the #psk=
  plaintext comment wpa_passphrase emits. Copy the .network sample to
  /etc/systemd/network/ rather than renaming in /lib.
- **CORRECTION to the kill list: avahi-daemon is REQUIRED, re-enabled**
  (2026-08-18, same evening). Disabling it silently broke every NEW ssh
  connection - the ~/.ssh/config alias resolves the board via its mDNS
  name, and the top-of-file rule "address by mDNS name, never a
  remembered IP" exists because the DHCP lease moves. Existing sessions
  survive (already connected), so the lockout appears only on the next
  fresh connection - long after the disable. If avahi must ever go,
  put a DHCP reservation in the router and key the ssh config to the
  fixed IP FIRST. Note: bare `ping osd32mp1` never resolves regardless
  - that name is an ssh-config alias; mDNS publishes
  `osd32mp1-red-v12.local`.
- **TRAP: /etc/wpa_supplicant.conf is a decoy - and the proof needed
  TWO passes** (the user's grep caught the first pass incomplete).
  Candidate consumers, each verified dead: (1) plain
  wpa_supplicant.service runs `-u` - D-Bus mode, no config, no
  interface, waits for connman/NM which aren't installed; (2) the
  ifupdown hook /etc/network/if-pre-up.d/wpa-supplicant DOES pass
  `-c $IF_WPA_CONF` - but that variable comes from a `wpa-conf` line
  in /etc/network/interfaces, which DOES NOT EXIST on this image, and
  no networking/ifupdown service is present either. Reviving that
  path would put ifupdown and systemd-networkd on one interface - the
  two-owners trap again. Also the file's default network block is
  `key_mgmt=NONE` (join any OPEN network). WiFi config goes ONLY in
  /etc/wpa_supplicant/wpa_supplicant-wlan0.conf consumed by
  wpa_supplicant@wlan0.service.
- **WiFi is LIVE (2026-08-18)**: wlan0 (Murata 1DX, brcmfmac) joined
  the bench 2.4 GHz AP via wpa_supplicant@wlan0 + the copied
  51-wireless.network - DHCP 192.168.0.14 beside eth0's .90, both
  permanent across reboots. Route metrics landed right by default:
  eth0 metric 10, wlan0 1024 - wired preferred, WiFi automatic
  fallback when the cable goes. Measured WiFi RTT 9-26 ms (vs sub-ms
  wired): fine for ssh/telemetry, but keep timing-sensitive bench
  measurements and the GCS link on Ethernet when both exist. mDNS
  (avahi) announces on both links. First ssh to a NEW address needs
  the usual ssh-rsa options plus the fresh known_hosts entry.
- **TRAP: UDP telemetry answers .14 requests FROM .90 (dual-homed
  reply asymmetry).** pios_udp binds 0.0.0.0:9000 so it receives on
  both addresses, but replies route via the preferred link (eth0,
  metric 10) and carry eth0's source address. Proven with an
  unconnected probe: sent to .14 -> reply from .90. A GCS connected
  to .14 discards those replies = "service dead on WiFi" while the
  cable is in. Unplug Ethernet and .14 works (only route). Real fix
  if ever wanted: IP_PKTINFO recvmsg/sendmsg in pios_udp (reply from
  the arrival address). ALSO: never configure two UDP devices in the
  GCS (one for each address) - two sockets speaking to the
  last-speaker firmware steal each other and NEITHER connects.
## FIXED: dual-homed UDP asymmetry (IP_PKTINFO) + the ECM WARN (2026-08-18)

- **pios_udp now replies from the address the client addressed.** Linux
  path (__linux__-guarded; macOS sim builds untouched): IP_PKTINFO on
  the socket, recvmsg records each request's destination address +
  arrival ifindex into the udp dev, sendmsg replies with a pktinfo
  cmsg (ipi_spec_dst = that address, ipi_ifindex = that interface).
  Broadcast/multicast destinations fall back to the kernel's spec_dst
  (the receiving interface's own unicast). Verified live post-reboot:
  probe to .90 answered FROM .90, probe to .14 answered FROM .14 -
  both bench addresses now work simultaneously; the GCS can target
  either. The trap entry above ("answers .14 requests FROM .90")
  describes the PRE-fix behavior.
- **The boot-time dwc2 WARN is gone: ECM is unlinked from the USB
  gadget** (stm32_usbotg_eth_config.sh, both the board and the
  image-edits reference copy). ECM's data endpoint could never enable
  (FIFO exhaustion with ACM+ECM bound) so every host attempt fired the
  dma_free_attrs WARN from the error path; the gadget is now
  console-only (acm.0), which is its actual job - Ethernet and WiFi
  carry the networking. Verified: 0 warnings on a fresh boot, ttyGS0
  getty alive. To revive ECM: g-tx-fifo-size in the DTB first, then
  restore the ln -s.
## WiFi hardened: the post-reboot no-address mystery, solved in three layers (2026-08-18)

The supplicant was NEVER the problem - it associated 12 s into every
boot and re-associated after every drop. The chain that actually lost
the address:
1. **brcmfmac power save** let the AP deauth the dozing radio (~3 min
   after boot, -78 dBm bench signal). Fixed persistently:
   wifi-powersave-off.service (reference copy in osd32mp1/systemd/).
2. **networkd v244 drops the lease on carrier loss and then wedges** -
   after re-association it sat "degraded (configuring)" indefinitely,
   never completing a fresh DHCP. Fixed: IgnoreCarrierLoss=yes in
   51-wireless.network (reference copy alongside) - the address+lease
   now survive blips outright, which also sidesteps the wedge path.
3. Verified live: a later 2 s carrier blip kept the address (no "lease
   lost" logged), and with the Ethernet cable pulled the board ran
   entirely on wlan0 - ssh AND UAVTalk telemetry (which, per the
   IP_PKTINFO fix, answers .14 from .14). Replugging eth0 restores
   wired preference by route metric automatically.
Diagnosis crib for "wlan0 has no IPv4": iw dev wlan0 link (association
+ moving counters), arping -I wlan0 <router> (L2 proof), then blame
DHCP/networkd - in that order. Signal here is -78 dBm: functional but
marginal; a better antenna position would calm the blips at the root.
- **GPS UAVObject semantics on realposix - which fields are REAL:**
  GPSPositionSensor is the truth (hub-fed from DroneCAN: Satellites =
  Fix2 sats_used; HDOP/VDOP real once gnss.Auxiliary arrives).
  GPSSatellites and GPSExtendedStatus are NEVER WRITTEN on this target
  - their only writers are the serial protocol parsers (NMEA.c/UBX.c)
  in the GPS module, which does not run here; whatever they display is
  compile-time default filler, and a "conflict" with GPSPositionSensor
  is expected. The honest sats-in-view count DOES exist unpublished:
  hub.gps_sats_visible (gnss.Auxiliary decode, pios_sensors_hub.c) -
  publishing it into GPSSatellites.SatsInView (arrays zeroed; DroneCAN
  carries no per-satellite data) is a small sensors.c addition if ever
  wanted.
## FLY-OVER-UDP: PPM-format sticks on port 9003 + graded INPUT health (2026-08-18, overnight)

- **New receiver: pios_udp_rcvr.c** (posix, PIOS_INCLUDE_UDPRCVR,
  realposix only). Wire format "PPM1" + seq + count + uint16le
  microseconds per channel, one frame per datagram, udp/9003 (9000
  telem / 9001 gps / 9002 aux were taken). Registered as the **PPM
  channel group** - the board has no hardware PPM and a literal new
  "UDP" enum option would change ManualControlSettings' object id,
  orphaning every persisted setting and forcing a GCS rebuild. So:
  ChannelGroups=PPM means network sticks on this board.
- **INPUT tile grading per spec** (receiver.c, UDPRCVR-gated): clean
  stream -> OK/green; quality < 70% (seq-gap loss accounting over 1 s
  windows) -> Warning/orange while still flying; >1 s silence on a
  link that WAS alive -> Error/red (never-configured stays orange).
  Channel reads fail safe at 500 ms staleness.
- **Senders**: ground/pyuavtalk/udp_sticks.py (--center/--pattern/
  --arm/--joystick via pygame for Xbox-class pads/--lossy N/--stop-
  after S); ground/pyuavtalk/setup_udp_sticks.py configures (PPM
  groups + Arming="Yaw Right", both persisted) and walks the whole
  matrix. VERIFIED 8/8 live: baseline orange, green, orange at 60%
  loss, red on dead stream, green restored, ARMED via UDP yaw-right,
  DISARMED via yaw-left.
- **GPS UAVObjects now truthfully populated** (sensors.c 1 Hz):
  GPSSatellites.SatsInView from gnss.Auxiliary sats_visible
  (per-satellite arrays zeroed - the DroneCAN suite carries no per-sat
  data, and AP_GPS does not retain it either, so enriching the CAN
  messages could not add it); GPSTime from Fix2's UTC gnss_timestamp
  (hub now captures the previously skipped 56-bit field; sanity-gated
  2020..2100) - PROVEN LIVE indoors: 2026-08-18 08:13:30 UTC with zero
  sats visible, the receiver has TIME before it has position;
  GPSExtendedStatus is semantically the GPSV9 self-description, so
  Status stays NONE with FirmwareTag="DroneCAN AP_Periph M9N" and
  BoardType[0]=124 as the honest identity.
- Traps hit: eth0 was still unplugged (ship over .14); pios_config.h
  touch = full ~13 min rebuild, as documented.
## GCS truth pass: slideouts, mixer pins, banks, HITL (2026-08-18, day)

- **AttEstAlgo blank = STOCK UPSTREAM BUG**: Panels.qml assigned the
  label ARRAY to Text.text without indexing it. Fixed with the full
  six-option RevoSettings.FusionAlgorithm map.
- **GPS type reads "CAN"**: SensorType gained a DroneCAN enum option
  (gpspositionsensor.xml - a DATA object, objid change orphans nothing,
  but GCS + firmware + synthetics MUST regenerate together; verified by
  decoding the new objid over the wire). Regenerate with
  `cd ground/uavobject-synthetics && ../uavobjgenerator/uavobjgenerator
  ../../shared/uavobjectdefinition ../..` - the top Makefile chokes on
  the SPACE in this repo's real path, and the synthetics Makefile
  hardcodes a stale qmake; run the generator directly.
- **Battery slideout on USB**: sensors.c publishes the TETHERED
  SENTINEL (V=5.00 nominal - the OTG block has presence only, no VBUS
  ADC; A=0.00 - no current-sense hardware exists;
  EstimatedFlightTime=999999). Panels.qml keys `usb_powered` on the
  sentinel: green boxes, infinity for time-left and mAh. On jack power
  everything reverts to stock alarm-keyed behavior.
- **Mixer dropdowns + Output tab name REAL pins** on board 0x11xx:
  canonical map in vehicleconfig.cpp (1:PI5/RPi-12/TIM8_CH1,
  2:PI6/RPi-38, 3:PI7/RPi-35, 4:PD13/RPi-32, 5:PD14/mikroBUS-16,
  6:PH11/RPi-31, 7:PB5/RPi-33, 8:PH10/JP19 DT-off); Output tab banks =
  timers (1 TIM8 1-3, 2 TIM4 4-5, 3 TIM5 6+8, 4 TIM3 7) - a bank's
  rate IS that timer's shared PWM frame rate.
- HITL's white void = the sim log console; placeholderText added.
- Welcome header now "NinjaPilot Websites".
- Octavo/OSD32MP1_RED_Rev1.2/ holds EAGLE CAD (.brd/.sch/.lbr) + the
  schematic PDF - NO photo/render imagery. A board view could be made
  by importing the .brd into KiCad (manual); the attitude-tab board art
  swap is deferred until real art exists.
- **Map "boxy wrong-scale patches" = the stale-zoom tile race, FIXED**:
  a loader thread stamps each tile with the zoom captured at enqueue,
  downloads for seconds, then inserted into the drawing matrix without
  checking the zoom was still current - and SetZoom's Matrix.Clear()
  cannot evict a tile that lands AFTER it. Tile positions overlap
  between zoom levels, so the stale tile painted the wrong scale into
  the current grid. Two guards (opmapcontrol): insertion refuses tiles
  whose zoom != current (bytes stay in the disk cache), and paint
  skips any mismatched tile that slips through. git add -f for
  opmapcontrol/src/core files (the .gitignore 'core' trap).
- **The mixer/output pin labels needed a SECOND pass - two traps:**
  (1) Config widgets are constructed (and the vehicle widget CACHED) at
  GCS STARTUP, before any board connects - a constructor-time
  getBoardModel() check reads 0 and generic labels stick forever. Pin
  names now apply at CONNECT: VehicleConfig::updateChannelNames()
  (rebuilds channelNames + repopulates ChannelBo* combos preserving
  selection, called from getVehicleConfigWidget) and
  OutputChannelForm::updateChannelLabel() (called from
  ConfigOutputWidget::refreshWidgetsValues).
  (2) The vehicle tab's motor dropdowns read "None" because the GUI's
  source of truth is SystemSettings.GUIConfigData (packed bitfields
  only the GUI normally writes), NOT MixerSettings - script-written
  configs leave it zeroed. QuadX ch1-4 = 0x34210000 in word 0
  (bitfields pack first-declared lowest: N,S,E,W,NW,NE,SW,SE x 4 bit;
  NW=1 NE=2 SW=4 SE=3). Written + persisted on the bench board.
## FIRST OUTDOOR GPS FIX + BRK migration facts (2026-08-18)

- **The M9N delivered its first real fix: 16 sats, 3D, HDOP 0.91** -
  lat/lon decode validated at last (40.1N -83.1W, sane altitude), GPS
  UAVObjects live end to end. The bench was RF-dead, not the antennas.
  GPS flight modes are no longer gated on decode validation.
- **GPS Display gadget "pulsing" fixed**: value QLabels resized with
  every numeric update and reflowed the layout. All value labels now
  pinned at worst-case fontMetrics width + left-aligned; heading
  zero-padded, speed space-padded (gpsdisplaywidget.cpp).
- **BRK CAN verification, from the schematics themselves**: the RED
  wires the TJA1441 to SiP pins PD0/PD1 (FDCAN1 RX/TX, the CAN1_RX/
  CAN1_TX nets) with STBY on PG3 - and the BRK's BREAKOUTS.SchDoc
  exposes PD0 (ball V11), PG3 (ball C9) and the PD bank on its
  headers. So the RED's exact CAN topology reproduces on the BRK: one
  3.3V-logic transceiver (TJA1441 needs its 5V rail like the RED's
  BSTOUT; an SN65HVD230-class part runs on 3.3V alone - simpler) plus
  CANH/CANL/GND to the bus. The RED DTB's m_can + pinmux block ports
  near-verbatim.
- **All 8 PWM pins are on the BRK headers** (PI5/PI6/PI7, PD13/PD14,
  PH11/PH10, PB5 all present in BREAKOUTS.SchDoc): PWM needs NO added
  hardware - 3.3V push-pull drives ESC/servo signal pins directly;
  actuator POWER stays on its own rail (the servo-melt rule). The DT
  timer unlocks must be re-applied to the BRK's own DTB.
- **BRK bring-up facts** (Octavo getting-started): boots OpenSTLinux
  v3.0 from SD, boot switches 101, power+data on ONE micro-USB, and
  the stock gadget is RNDIS - useless to macOS, so the first BRK act
  is the same ecm+acm gadget surgery as the RED. No Ethernet/WiFi at
  all: gadget networking or a USB WiFi dongle are the only links.
- The Octavo STP library models the SiP PACKAGE only (all five Octavo
  parts) - no board-level models anywhere in it.
## The PFD slide-out saga, solved structurally + map over-zoom (2026-08-18)

- **PFD cards now select by VISIBILITY, not z-juggling** (Panels.qml
  property active_card, set by the four hide_display_* functions). The
  stock design stacked four different-SIZED cards in one slot and
  juggled z - the taller RC dial poked out from behind the shorter
  LINK METER, which is what "the OPLink slideout shows a roll/pitch/
  throttle thing" was. TRAP found on the way: the icon TABS are baked
  into each card's bg SVG group, so hiding a card hid its icon -
  standalone icon elements exist in pfd.svg (rc-input-icon,
  battery-icon, oplm-icon, system-logo) and now render as an
  always-visible z:100 icon strip.
- **Map: Esri serves a CONSTANT "Map data not yet available" JPEG**
  (2521 bytes, md5 f27d9de7f80c13501f470595e327aa6d at EVERY position/
  zoom - verified) where deep imagery does not exist. opmaps.cpp now
  rejects it at download as a missing tile, and mapgraphicitem.cpp
  paints an OVER-ZOOM FALLBACK for any missing tile: the nearest
  cached ancestor tile's quadrant scaled up (up to 4 levels) - "the
  previous tile extent" instead of gray apologies. Note the GCS's own
  empty-tile message branch is if(false) dead code - the text the user
  saw was Esri's, not ours.
- **RULE: diagnostic GCS launches MUST use an isolated settings dir**
  (or not exit via pkill): a `-noload IPconnection` instance rewrote
  ~/.config/NinjaPilot/NinjaPilotGCS_config.xml on exit. This time the
  IPconnection section SURVIVED (verified .14:9000 intact) - the
  observed "lost UDP config" was transient two-instance interference -
  but the hazard class is real.
- **The occasional shutdown SEGV is Qt 5.15's QWindowContainer
  recursion**: crash trace = QWindowContainer::parentWasRaised infinite
  recursion during MainWindow teardown, triggered by ModeManager
  removing modes while the Welcome tab's QQuickView-in-
  createWindowContainer still lives; QStackedLayout::takeAt raises a
  sibling, the container re-enters parentWasRaised, stack dies. Exit-
  time only - no data loss. Mitigation if it annoys: destroy/reparent
  the Welcome container BEFORE plugin shutdown (WelcomeMode dtor).
## Session epilogue: the radio icon, the exit crash answered, real USB amps (2026-08-18)

- **EPILOGUE to the slide-out saga: the user had been clicking the
  BOTTOM icon** - it depicts an RC transmitter, and its card is the
  stock RC INPUT MONITOR (throttle bar = ManualControlCommand.Throttle,
  red dot = Roll/Pitch, crosshair twists with Yaw). The antenna card
  was correct all along. The visibility rewrite STAYS: it makes card
  selection deterministic and cures the real different-sized-cards
  poke-through hazard.
- **The occasional exit SEGV is FIXED at its root**: upstream's
  WelcomePlugin destructor cleanup was commented out with "TODO: Fix a
  real solution" (removing the mode during MainWindow teardown crashed
  one way; leaving it leaked the QQuickView window container into the
  teardown where QWindowContainer::parentWasRaised recurses to death -
  the crash the user reported). The real solution: IPlugin::shutdown()
  runs on every plugin BEFORE any destructor, with MainWindow fully
  alive - the mode is removed + deleted there. Also: the container
  OWNS the QQuickView (createWindowContainer semantics) - delete the
  container, never both. The dead openpilot.org version phone-home
  went too.
- **Battery slideout Amps = the real USB-C budget**: the hub reads
  /sys/class/typec/port0/power_operation_mode (STUSB1600) - "default"
  0.5 / "1.5A" / "3.0A" - the SOURCE'S ADVERTISED limit, live per
  charger. On the bench it reads 1.5A. BRK note: plain micro-USB has
  no typec controller -> field stays 0.
- **BUILD TRAP (cost one cycle): an scp'd source can land while make
  resolves stale** - the usbamps build reported success with the new
  hub code absent from the ELF (strings | grep typec = 0). VERIFY
  EFFECT: `strings` the ELF for a string your change introduces;
  remedy is touch + rebuild. Same lesson as the GCS bundle-dylib rule.
## GPS wire census with a real fix + the sats_visible verdict (2026-08-18, evening)

- **30 s transfer-level census (SO_TIMESTAMP), full suite live**: IMU
  pair 247.6 Hz (sd 0.6 ms), baro 50 Hz x2, mag 49.9 Hz, GPS trio
  (Fix2/Aux/Status) at 5.00 Hz sd 5.4-6.3 ms max-gap 1.06x nominal -
  zero dropouts, 719 fr/s total. **The GPS was at 5 Hz - the saved
  10 Hz operating point did NOT survive some node reflash** (params
  usually survive; this one didn't). Restored: GPS1_RATE_MS=100 set +
  save opcode sent (both NO RESPONSE while streaming, as always) and
  VERIFIED BY WIRE: 10.00/10.00/10.00 Hz. Check it again after the
  next node power cycle - the save ack was never seen.
- **20 Hz not recommended for flights**: measured sustainable solo,
  but the estimator gains little past 10 (AP/PX4 fly 5-10), and it
  spends bus + L431 loop budget that competes with the 247 Hz IMU
  stream. 10 Hz is the operating point.
- **GPSSatellites SatsInView=0 was a FAITHFUL decode**: DSDL confirms
  the hub's Auxiliary offsets (sats_visible u7 @112, sats_used u6
  @119), and AP_Periph gps.cpp fills ONLY pkt.sats_used - AP_GPS holds
  no visible count at all (would need NAV-SAT parsing). sensors.c now
  publishes SatsInView = max(visible, used) - live: 17. Per-satellite
  arrays stay zeroed forever on this bus.
- **ground/pyuavtalk/upload_demo_plan.py**: standalone PLAN demo -
  5-wp square @30 m, PLAN alarm verified GREEN (flight side recomputed
  crc=128). Plans are RAM-ONLY: nothing on the filesystem, firmware
  restart wipes them.
- **The .elf's Linux footprint** (from /proc/PID/fd + fs): flashfs =
  the CWD /usr/local/ninja/fcwd as plain files - 233CDC00.oNN are
  DebugLog slots (1855 accumulated from the Always era - purge
  233CDC* before timed log work, NEVER the objid-named files like
  042F462A.o00: those are the PERSISTED SETTINGS), /dev/shm/
  ninjapilot-log (shmlog ring), /run/ninjapilot-fw.pid (single-
  instance flock), open fds to /dev/i2c-3 + six PWM duty_cycle sysfs
  nodes + the UDP sockets, stdio on /dev/null.
## THE FLASH PATH WAS BROKEN THREE WAYS (2026-08-18, night) - and the node is now in a BL hold

Chasing the NAV-SAT flash exposed why over-CAN flashing has ALWAYS been
flaky in this project ("several mode-2 holds; one run took 4 attempts").
Three independent bugs, all fixed:

1. **Staging path**: can_flash.py's FileServer serves ONLY from
   /home/root/fw. An image staged in /home/root (one level up) means the
   node re-flashes whatever STALE file is in fw/ - and the flasher still
   prints its verdict as if it worked. Verified: three "flashes" all
   re-wrote an Aug-17 image.
2. **python-dronecan treats a full TX queue as FATAL**: SocketCAN
   send_frame() raises TxQueueFullError instead of applying backpressure,
   killing the file server mid-transfer. NOT the wire (berr-counter tx 0
   rx 0, zero TX errors/drops) and NOT txqueuelen (10 -> 1000 changed
   nothing). Fixed by monkeypatching send_frame to BLOCK on a full queue
   (the writer thread already retries ENOBUFS itself).
3. **The 240 s deadline was too short**: an instrumented run
   (can_flash_verbose.py, counts Read requests + max offset) measures a
   COMPLETE transfer at ~222 s / 800 reads / 178 KB / zero errors. The
   old deadline killed the server just before the end. Now 420 s.
   RULE: judge a flash by MAX OFFSET REACHED, never by the vcs verdict -
   "sw 2.0 vcs=00000000 mode=2" is the BOOTLOADER answering, and
   can_flash's own "FLASH SUCCEEDED" line printed that as success.

**REMAINING, and it needs hardware: node 124 is in a BOOTLOADER HOLD.**
With all three bugs fixed, TWO complete zero-error transfers (our new
NAV-SAT image AND a previously-good image) both leave the node in mode 2
with uptime climbing and NO reset loop - the BL takes the image and
never launches an app. That exonerates the firmware image (the
known-good behaves identically) and matches the long-standing
"bootloader boot-failure hold flag that a POWER CYCLE clears" suspect,
which has never been tested. Next step: power-cycle node 124; the
NAV-SAT image is already staged and fully written.
## RESOLVED: per-satellite GPS data is live, and the flash lesson (2026-08-18, late night)

**It works**: node 124 runs the NAV-SAT firmware, msg 20502 broadcasts at
0.94 Hz, and GPSSatellites carries a real sky: PRN 16 at 80 deg
elevation, PRN 31 SNR 30, WAAS birds 131/133/138 tracked at SNR 0,
GLONASS alongside GPS, 16 in view against a 0.87 HDOP fix. The GCS's
sky dome + SNR bars (telemetryparser.cpp) consume it with no GCS
change.

**THE REAL LESSON, and it cost two hours: the over-CAN flash is
INTERMITTENTLY flaky, and I mis-diagnosed that as an image defect.**
Same file, same procedure: 843 reads -> boots; 1700-2400 reads -> the
bootloader rejects it. The KNOWN-GOOD image failed a run too, which is
what finally disproved "the image is bad". Read count is the health
signal (~840 reads for a 178 KB image = clean; 2x that = the BL
re-requesting blocks). RULE: **retry the flash until the node reports
mode 0** - osd32mp1/flash_until_boot.sh does exactly that (it booted on
attempt 2). Do NOT theorise about the image until several attempts have
failed.

Dead ends burned along the way, all measured, none of them the cause:
image size (42,948 B free; explicitly compiling out nine baro backends
+ RM3100 produced a BYTE-IDENTICAL binary - AP_Periph's feature gates
had already excluded them), the app descriptor (signature at 0x1d0,
board_id 1062, image_size exact - identical structure to the
known-good), incremental vs clean builds (byte-identical), staged-file
integrity, and txqueuelen.

**Also mine, and worth remembering:** my first instrumented flasher
registered a SECOND uavcan.protocol.file.Read handler alongside the
FileServer's own, so every request drew two responses and corrupted the
transfers I then reported as "complete, zero-error". Patch the
FileServer._read CLASS method before instantiating (osd32mp1/
can_flash_verbose.py) - never node.add_handler for a service the
FileServer already owns.
- **THE EXIT SIGSEGV, actually root-caused (my earlier Welcome fix was
  the WRONG container)**: PfdQmlGadget and QmlViewGadget destructors did
  `delete m_widget` on the QQuick view they had handed to
  QWidget::createWindowContainer - which OWNS that QWindow. The freed
  view left the container (still parented into the mode's
  QStackedLayout) holding a dangling window, so shutdown's
  QLayout::removeWidget -> QStackedLayout::takeAt -> setCurrentIndex ->
  QWidget::raise() -> QWindowContainer::parentWasRaised recursed onto a
  dead QWindow and null-dereferenced in QWindow::parent() (crash trace
  x0=0). Both destructors now delete the CONTAINER (which takes the view
  with it). RULE: anything handed to createWindowContainer belongs to
  the container - never delete it directly. The PFD gadget is the one
  users hit because Flight Data is the default workspace.
## Missions now survive a reboot (2026-08-19)

Waypoint/PathAction/PathPlan are DATA objects (settings="false"), so a
reboot silently lost the whole mission - the aircraft came back holding
no plan with PLAN orange. pathplanner.c now mirrors a VALIDATED plan
into the same flashfs the settings use, restores it in
PathPlannerStart() before the callbacks hook up, and lets the existing
checkPathPlan() CRC re-validate it (a corrupt store cannot arm a bogus
mission - it just leaves PLAN orange). VERIFIED: upload -> restart
firmware -> PLAN green with 5 wp / 1 action / crc 128 intact, no
re-upload. Waypoint instances land as D23852DC.oNN in fcwd.

Write policy is deliberately conservative because this file is shared
with the STM32 targets, where a flash erase blocks for milliseconds:
the plan is written ONLY when its CRC changes AND the craft is
DISARMED (i.e. at upload), and progress (WaypointActive) is written per
waypoint transition and only under PIOS_REALPOSIX where storage is
files.

**Resume is deliberately NOT automatic, and the reason is physics:** on
a multirotor a reboot stops the motors, so the aircraft is falling long
before any resume logic could run (a fw_realposix restart is ~10 s).
Persisted progress therefore buys (a) no re-upload after any reboot,
(b) resume-from-waypoint-N after a GROUND reboot mid-mission, and (c)
forensics - which leg was active when it died. True in-air resume is
only meaningful for a fixed-wing with a sub-second MCU reset, and would
need gates: valid 3D fix, position within a sane radius of the recorded
leg, and an explicit pilot/settings opt-in.
## Mission recovery: progress record + opt-in resume flag (2026-08-19)

- **MissionRecoverySettings** (settings, persists): AutoResume
  Disabled|ResumeAtWaypoint, MaxDistance 50 m, MaxAge 300 s. VERIFIED
  live: readback, set to ResumeAtWaypoint, ObjectPersistence-saved.
- **MissionProgress** (data, persisted by the planner): WaypointIndex,
  PlanCrc, Position NED, Lat/Lon, Timestamp, WasArmed, Valid. Written
  by savePathProgress() at every PLANNER-DRIVEN waypoint transition,
  alongside a DebugLog line ("MISSION wp=.. crc=.. N/E/D.. armed=..")
  as the forensic trail the user asked for.
- **Resume semantics**: on boot the planner restores the plan, loads the
  record, and accepts it only if Valid AND PlanCrc matches the restored
  plan AND the index is in range - a record from a DIFFERENT mission is
  marked invalid rather than resumed. With AutoResume enabled it sets
  WaypointActive to that index, so engaging PathPlanner continues from
  that leg instead of waypoint 0. It NEVER arms, engages a mode or moves
  the aircraft.
- **Corrupt plan is now RED**: checkPathPlan returns PLAN_EMPTY /
  PLAN_VALID / PLAN_CORRUPT. Empty (nothing uploaded) stays Warning;
  counts or CRC failing = Error, because that means the aircraft is
  holding a DAMAGED mission, not merely no mission.
- **BUILD NOTE**: the board's build/uavobjgenerator is a 75-byte STUB
  (the no-Qt dance) - new UAVObjects must be generated on the Mac
  (ground/uavobject-synthetics && ../uavobjgenerator/uavobjgenerator
  ../../shared/uavobjectdefinition ../..) and the .c/.h copied to the
  board's build/uavobject-synthetics/flight/.
- **NOT yet verified end to end**: the record only fills during a real
  planner-driven mission (poking WaypointActive over telemetry does not
  call setWaypoint), so resume-after-reboot wants a flown or simulated
  mission to confirm.
- **Adding a UAVObject: the two traps.** (1) uavobjgenerator emits the
  XML <description> VERBATIM into a C++ string literal, so a multi-line
  description produces "error: expected expression" in the GCS build -
  keep descriptions on ONE line. (2) The GCS's
  plugins/uavobjects/uavobjects.pro carries a STATIC synthetics
  inventory (HEADERS and SOURCES lists); a regenerated object is not
  compiled until it is added to BOTH lists, and the symptom is a link
  error naming the new class's constructor. Object IDs hash name+fields
  only, so editing a description does not change the id and does not
  require a firmware rebuild.
## The STAB flicker returned WITH the 500 Hz restore - and both watchdogs were rate-relative (2026-08-19)

Restoring INS_SAMPLE_RATE 250 -> 500 brought the STAB orange flashes
back (the zero-transition state had been measured AT 250). Root cause,
proven with the new alarm-transition logger: BOTH innerloop watchdog
dimensions measure in COUNTS, so their wall-clock tolerance is a
function of the sensor rate - raising the rate silently re-tightens
the alarm:
- gyroupdates > 8 was ~8 ms of pass latency in the 959 Hz era it was
  calibrated in, but 16 ms at 490 Hz - inside ordinary self-healing
  Linux scheduler hiccups. 40-57 one-shot trips per 3 min, each held
  ~1.07 s by the alarm GRACETIME = the visible flashing.
- rateupdates < -8 shrank identically (~20 ms at 490 Hz).
Fix: the realposix innerloop watchdog is now TIME-based - wall-clock
pass gap, warn > 48 ms / crit > 96 ms (the estimator's own staleness
watchdog sits at 50 ms for the same reason). Sample-count thresholds
remain for the STM32 targets, where samples ARE time.

**Instrumentation that settled it, both durable:**
- alarms.c logs EVERY alarm transition to the ring: "[alarm] idx=N -> S"
  (transitions only; self-stubbed on hard targets). Tiles flash faster
  than any poller can sample, and polling SystemAlarms over UDP steals
  the GCS link - read the ring instead. Alarm index crib: 5=EVENT,
  10=ATTI, 14=STAB (SystemAlarms element order).
- The 0.5 s-throttled watchdog PRINT lines hide sub-window spikes: the
  printed max was 8/-4 while the alarm tripped on unprinted 9-16/-9+
  excursions between prints. Judge alarms by the transition log, never
  by the throttled telemetry prints.
- shmlogd had vanished from the board (rebuilt from osd32mp1/shmlogd.c:
  gcc -O2 -o /home/root/shmlogd shmlogd.c).

**The AppleDouble tar trap struck a SECOND time** - the documented
COPYFILE_DISABLE=1 rule existed and was violated by a plain `tar czf`
in this very session, planting 13 `._*` files that broke the UAVO hash
AGAIN. The complete both-sides UAVObject recipe (with junk-free
shipping, the version_info hash-library step, and the tree-hash
pre-check) now lives in SKILLS.md "Change or add a UAVObject".
- **VERDICT (clean live window, backlog drained): STAB = 0 transitions
  in 180 s at 500 Hz** with the time-based watchdog (was 40-57 per
  window). Residual: EVENT ~2/min one-shot blips (AttitudeState
  callback queue under the doubled rate - task #75 territory) and one
  Receiver blip. TRAP that voided one whole verification round:
  shmlogd drains the RING BACKLOG first, so a capture started after a
  restart replays the PREVIOUS firmware's lines with old timestamps -
  drain with --dump before any live measurement, and check the
  process start time against the capture window. Also: a board build
  can take past the moment you think it finished - the ELF mtime and
  the service start time tell the real story.
- **EVENT blips killed the same night - STM32-era queue depths were the
  contention**: the dispatcher's eventErrors (the ONE term of systemmod's
  EVENT check not shown in the printed stats line) counts drops at two
  queues still sized for a microcontroller: TELEM_QUEUE_SIZE 20 (40 ms
  of buffering at the 490 Hz event rate, behind a telemetry task that
  deliberately runs at the BOTTOM of the RT band) and
  PIOS_EVENTDISAPTCHER_QUEUE 64 (~130 ms). MP1 sizing: 512 (~1 s) and
  1024 (~2 s) for ~32 KB total of the 426 MB. VERDICT: **ZERO alarm
  transitions of ANY kind in a clean 180 s window** - STAB 0, EVENT 0,
  Receiver 0 - GCS attached, IMU at 500 Hz. Both defines live in
  realposix pios_board.h / pios_config.h = full ~13 min board rebuild.
## Attitude truth-pass + the wizard blockers, root-located (2026-08-19)

- **"Yaw spin / accel drift" forensics**: the MPU startup sequence is
  CORRECT on the node (PWR_MGMT_1=0x01 = wake + PLL-on-X-gyro - the
  clock whose omission causes classic drift; verified in imu.cpp).
  Wire bias measured healthy (X+0.03 Y-0.59 Z-0.11 dps raw). The spin
  was FUSION: HomeLocation.Be was captured for an earlier bench
  geometry, the reattached hardware changed it (deviation 740 mGa vs a
  372 mGa field - Y and Z sign-flipped), filtermag rejected every
  sample, and yaw free-integrated. A clean-restart calibration fixed
  roll/pitch (stable to 0.01 deg); Be re-captured+persisted for the
  current pose. CAVEAT: the "Be := measured field = yaw 0" bench
  recipe assumes a LEVEL board - at roll -77 deg it redefines the
  reference crookedly and yaw slews to converge. The DURABLE fix is a
  real calibration pass (wizard/ConfigRevoWidget), not another Be
  splice.
- **Wizard blockers for realposix, root-located**: (1) the summary
  page's Next runs SummaryPage::validatePage ->
  VehicleConfigurationHelper::setupVehicle(false) - acked-write wait
  loops tuned for Revo hardware stall or fail on this board = "can't
  click Next" (same class as task #74). (2) PAGE_INPUT rebooted the
  board on input change - needed on STM32 to re-init receiver ports,
  pointless on realposix (receiver set is compile-time) and it has
  wedged saves; now SKIPPED for CONTROLLER_REALPOSIX. (3) the GPS page
  offers no "u-blox on CAN/DroneCAN" option - wants a new enum +
  helper case that writes nothing (the CAN GPS is always-on). (2) is
  FIXED; (1) and (3) are the next wizard session, and (1) is the
  gate: instrument setupVehicle's apply loop to log which object write
  fails to ack on realposix, then fix or skip those writes.
- **Wizard follow-through (2026-08-19, late)**: GPS page now offers
  "U-Blox on CAN bus (DroneCAN)" (GPS_DRONECAN enum appended LAST so
  saved configs keep their meaning); the helper deliberately writes
  NOTHING for it, and applyHardwareConfiguration is a complete NO-OP
  for CONTROLLER_REALPOSIX - no serial ports/speeds exist here, and
  every skipped write is one fewer acked transaction for the summary
  page's blocking apply loop to stall on. If the summary Next still
  stalls, the GCS console names the culprit: "Transaction timed out
  when trying to save: <object>" - fix or skip THAT write, do not
  raise the timeouts.
- **CORRECTION (user called it, same night): the wizard hardware no-op
  was an over-reach and is REVERTED.** "Every HwSettings/GPSSettings
  write is meaningless on realposix" was false on two counts: the GPS
  module is REAL here (UDP port 9001, UBX/NMEA parsers - the GPS
  thread in the RT listing), so OptionalModules[GPS] and
  GPSSettings.DataProtocol are live config; and the port fields RECORD
  the user's input choice, which a future hardware receiver driver on
  the MP1 timer pins will read. The wizard must retain the power to
  override every default (QuadX today, plane tomorrow; UDP sticks
  today, hardware PPM tomorrow). realposix now takes the standard
  Revo-family apply path; the ONLY skip is GPS_DRONECAN's serial
  protocol config. If the summary-page Next still stalls, get the
  culprit from the GCS console ("Transaction timed out when trying to
  save: <object>") and fix THAT write - do not amputate the wizard.
- **The wizard SEVERED the UDP receiver on its first real run**: its
  input page maps the selection into ManualControlSettings.ChannelGroups
  (applyManualControlDefaults), and PWM/SBUS/DSM groups have no driver
  on this board - the UDP receiver lives in the PPM group BY DESIGN.
  Result: working sticks -> dead INPUT tile, no error anywhere. Fixed:
  on CONTROLLER_REALPOSIX the wizard binds ChannelGroups to PPM for
  EVERY input choice (the choice itself is still recorded in HwSettings
  for future hardware). Restore ritual if it ever recurs:
  ground/pyuavtalk/setup_udp_sticks.py - and run its verification with
  the GCS CLOSED (two UDP clients steal each other's packets and fake
  FAILs; a 3/8 with config-readback PASSing is the stolen-packet
  signature, not a broken receiver).
- **Zero-rate gyro trim (disarmed only) + the two-gyro observability
  answer (2026-08-19)**: no number of gyros can distinguish "still" from
  "slowly rotating" - every gyro reports rate+bias, so redundancy
  averages noise and catches faults but cannot observe the common bias
  mode; absolute yaw needs mag/GPS/vision. STILLNESS is observable from
  variance though: sensors.c now measures 512-sample windows while
  DISARMED and trims the published gyro by the window mean when sd <
  0.35 dps (freezes on arm/motion; low-passed engagement; one-shot ring
  line). Verified: published gyro z -0.005 dps against -0.11 raw.
  Bench yaw walk history: +0.33 (mag rejected, stale Be) -> -0.49 (Be
  spliced BODY-frame on a 77-deg-rolled board = permanent mag residual,
  constant MagKp*error rotation) -> -0.22 dps after writing Be
  ATTITUDE-CONSISTENTLY (rotate measured body field into NED through
  current attitude). RULE: never write Be as the raw body vector unless
  the board is LEVEL; rotate through attitude, or capture level. The
  remaining -0.22 is uncalibrated bench geometry (accel scale +4.3%,
  loose modules, no six-point cal) - the durable fix is a real
  calibration session with the board level, not more Be splices.
