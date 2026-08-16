# OSD32MP1-RED — recipes

Commands that work, with the reasoning kept short. The *why* lives in
`CLAUDE.md`; this file is for getting things done.

All host commands run from `osd32mp1/`. The venv (`./venv/bin/python`) has
`pyusb` for the libusb fallback path.

---

## Reach the board

Three independent channels. If one is broken, the others still work — that is
the whole point of the image edits.

```bash
ssh osd32mp1
```

Ethernet, key auth, fastest. `~/.ssh/config` supplies the mandatory
`+ssh-rsa` options and points at the mDNS name (the DHCP lease moves; the name
does not). Password fallback is `ninjapilot`.

```bash
./venv/bin/python board_cmd.py "uname -a" "ip -brief addr"
```

USB serial console. Needs **no network at all** — use this when Ethernet, DHCP
or sshd are the thing you broke. macOS binds it natively as
`/dev/cu.usbmodem*`; the getty runs `--autologin root`, so there is no login
prompt to script around.

```bash
screen /dev/cu.usbmodem* 115200        # interactive equivalent (ctrl-a k to quit)
```

`usb_console.py` is the libusb fallback for an image whose ACM advertises
protocol `0xff` (the stock build), where macOS binds nothing. **You do not
need it with the edited image.**

### When nothing responds

```bash
./detect.sh
```

Distinguishes ROM-DFU / serial / USB-network / Ethernet and says what to do.
Confirm identity positively rather than by elimination — a "new host" on the
LAN can easily be a printer:

```bash
dscacheutil -q host -a name osd32mp1-red-v12.local
```

## Run a command on the board over the console

```bash
./venv/bin/python board_cmd.py "systemctl is-active dropbear.socket"
./venv/bin/python board_cmd.py "cmd one" "cmd two"      # several in one session
```

Note the board's non-interactive ssh PATH omits `/usr/sbin` and `/sbin`, so
`ip`, `ifconfig` and `reboot` appear "not found" over ssh but work on the
console. Export it when scripting over ssh:

```bash
ssh osd32mp1 'export PATH=/usr/sbin:/sbin:$PATH; ip -brief addr'
```

## Edit an SD image offline, on macOS, without sudo

The reason this works: `/dev/disk*` needs root, but a raw `.img` is a file you
own. Never hardcode offsets — read them from the GPT.

```bash
python3 gpt.py ~/Downloads/osd32mp1-red-v1_2-trusted-openstlinux-sdcard-v3_0_1.img
```

```bash
python3 part.py out image.img rootfs.ext4 88622080 782237696
```

Then edit with `debugfs`, always by `cd`-ing into the target directory and
writing directly (a `write` + `ln` + `rm` sequence corrupts the image):

```bash
debugfs -w -f edits.cmds rootfs.ext4
```

A command file looks like this — `sif` sets mode/uid/gid because `write` does
not preserve them:

```
cd /sbin
rm stm32_usbotg_eth_config.sh
write /host/path/stm32_usbotg_eth_config.sh stm32_usbotg_eth_config.sh
sif stm32_usbotg_eth_config.sh mode 0100755
sif stm32_usbotg_eth_config.sh uid 0
sif stm32_usbotg_eth_config.sh gid 0
quit
```

Verify, inject, verify again. **Both fsck runs must report zero repairs:**

```bash
e2fsck -fy rootfs.ext4 && python3 part.py in image.img rootfs.ext4 88622080 782237696
```

Partition offsets for this image (from `gpt.py`, for reference):

| part | name | offset | size |
|---|---|---|---|
| 4 | boot | 4736000 | 67108864 |
| 6 | rootfs | 88622080 | 782237696 |

`e2fsprogs` is Homebrew's, not on the default PATH:

```bash
export PATH="/opt/homebrew/opt/e2fsprogs/sbin:$PATH"
```

## Flash the card

```bash
diskutil unmountDisk /dev/disk10 && sudo dd if=~/Downloads/osd32mp1-red-v1_2-NINJAPILOT.img of=/dev/rdisk10 bs=4m status=progress
```

Use `/dev/rdisk` (raw) not `/dev/disk` — an order of magnitude faster. Confirm
the disk number with `diskutil list` first; the built-in reader is usually
`disk10` and reports as *internal*, which is normal.

## Generate a password hash

macOS has neither `crypt(3)` `$6$` support nor `openssl passwd -6`:

```bash
python3 sha512crypt.py <password> <salt>
```

It self-tests against the specification's official vector and **refuses to
emit a hash if that fails**. Do not remove that check — the first
implementation was wrong and the vector is what caught it.

## Switch the USB gadget between console and network

macOS gives you one or the other, never both (see `CLAUDE.md`). Default is the
console. To get USB networking instead, on the board:

```bash
sed -i 's/^func_acm=.*/func_acm=/' /sbin/stm32_usbotg_eth_config.sh
```

...and remove the two `acm.0` lines, or for a quick non-persistent test:

```bash
ssh osd32mp1 'G=/sys/kernel/config/usb_gadget/g1; echo "" > $G/UDC; rm -f $G/configs/c.1/acm.0; rmdir $G/functions/acm.0; ls /sys/class/udc | head -1 > $G/UDC'
```

The host then gets a `192.168.7.x` address from the board's own DHCP server
and the board answers on **192.168.7.1**. Detach the command with `nohup ... &`
if running it over ssh — rebinding the UDC drops the session mid-command.

**This kills the console until reboot** (`BindsTo=dev-ttyGS0.device`, see
`CLAUDE.md`). Reboot rather than fighting it:

```bash
ssh osd32mp1 'nohup sh -c "sleep 1; /sbin/reboot" >/dev/null 2>&1 &'
```

## Inspect gadget state

Board side:

```bash
ssh osd32mp1 'ls /sys/kernel/config/usb_gadget/g1/configs/c.1/; networkctl status usb0'
```

Host side — what macOS actually bound, which is the question that matters:

```bash
ioreg -w0 -l | grep -o '"AppleUSB\(ECM\|ACM\|NCM\)[A-Za-z]*"=[0-9]*' | sort -u
```

`AppleUSBECMControl=1` with `AppleUSBECMData=0` is the signature of the
ECM-blocked-by-ACM case. Full descriptor dump:

```bash
./venv/bin/python usb_descriptors.py
```

## Disk space — build in /usr/local, not /

The rootfs is a **644 MB partition that ships ~93% full**, and installing
`dronecan` + `python3-sqlite3` took it to 97%. It is not a place to build.

Two reclaims, in order of safety:

```bash
ssh osd32mp1 'apt-get clean && rm -f /var/cache/apt/archives/*.deb'
```

```bash
ssh osd32mp1 'resize2fs /dev/mmcblk1p7'
```

The second is free space that was already yours: **p7 is a 705 MB partition
that only contained a 120 MB filesystem** — the image never grew it. Online
resize, no partition-table change, took `/usr/local` to **679 MB with 609 MB
free**. Do this before the SimPosix build and put the tree in `/usr/local`.

If even that runs out, the card has **~30 GB unallocated** past p7 (ends at
sector 3145694 of 61952000), so a new partition is available — but that *does*
mean editing the GPT on the boot medium, so it is a deliberate step, not a
casual one.

## Read the KUSBA accelerometer (Klipper protocol)

No Klipper install needed. Both run **on the board**:

```bash
ssh osd32mp1 'python3 /home/root/klipper_probe.py'
```

Fetches the firmware's data dictionary and reports which sensor commands the
build has. Use `--dump-json` for the full dictionary.

```bash
ssh osd32mp1 'cd /home/root && python3 klipper_accel.py --seconds 5 --rate 800'
```

Configures SPI, verifies `DEVID = 0xE5`, puts the ADXL345 in FIFO stream mode
and decodes samples to m/s^2. `--rate` accepts 25..3200 Hz.

If it reports no response at any sequence, the MCU is wedged mid-config —
unplug/replug the KUSBA. Sequence state persists across connections, which is
why the tools sweep for it rather than assuming 0 (see `CLAUDE.md`).

## Feed real sensors into fw_simposix

```bash
ssh osd32mp1 'cd /usr/local/ninja && python3 sensor_bridge.py --dry-run --seconds 12'
```

Prints the UAVObject values it would send, so the conversions can be checked
against real hardware without the firmware built. Drop `--dry-run` to actually
feed `127.0.0.1:9000`. Measured 190 Hz against a 200 Hz target on this board.

**One-time setup** — OpenSTLinux ships a SPLIT python3, and `multiprocessing`
shared memory needs `mmap`, which is not installed by default (same trap as
`sqlite3`; `import` fails with `No module named 'mmap'`):

```bash
ssh osd32mp1 'apt-get install -y --no-install-recommends python3-mmap python3-multiprocessing python3-ctypes'
```

Deployed layout is `/usr/local/ninja/{sensor_bridge.py,pyuavtalk/,shared/uavobjectdefinition/}`.
Pass `--xml-dir` if you move it — `default_xml_dir()` resolves a repo-relative
path that does not hold once deployed.

## Get source onto the board

`git` and `rsync` are **absent**, so tar over ssh:

```bash
tar czf - -C ../NinjaPilot-15.02.ninja . | ssh osd32mp1 'mkdir -p /home/root/ninjapilot && tar xzf - -C /home/root/ninjapilot'
```

Include `.git` if the build needs it — `version-info.py` reads the worktree and
produces `0xNone commit_hash_prefix` without it. Space is not a concern
mid-development.

## Build SimPosix on the board

```bash
ssh osd32mp1 'cd /home/root/ninjapilot && make -j2 simposix'
```

Two cores and ~426 MB RAM, so `-j2`. Expect the same workarounds the Debian
build needed: pre-generated UAVObjects, a stub generator, and `QMAKE=true` when
`qmake` is missing.

## Probe sensors (runs on the board)

> **`probe_sensors.py` IS NOT WRITTEN YET.** It is the next tool to build, and
> is specified here so the spec does not drift. Until it exists, use
> `i2cdetect -y <bus>` and `i2cget` directly on the board.

Intended interface:

```bash
./probe_sensors.py --i2c      # bus scan + WHO_AM_I identity checks
./probe_sensors.py --can      # SocketCAN presence, bitrate, live frame count
```

A bus scan only proves *something* acked an address; the identity register is
the real test:

| part | register | expected |
|---|---|---|
| MPU9150 | `0x75` WHO_AM_I | `0x68` |
| AK8975 (inside MPU9150) | `0x00` WIA | `0x48` |
| HMC5883L | `0x0A,0x0B,0x0C` | `0x48,0x34,0x33` = `"H43"` |

Bring `can0` up before probing CAN:

```bash
ssh osd32mp1 'ip link set can0 up type can bitrate 1000000; ip -details link show can0'
```

## DroneCAN: see who is on the bus

```bash
./can_poll.py
```

Host-side. Brings `can0` up, dumps, decodes the 29-bit IDs into source node +
message type. `--seconds`, `--bitrate`, `--raw`. Handles the anonymous-frame ID
layout correctly (see `CLAUDE.md` — the normal layout gives garbage there).

Healthy output is `ERROR-ACTIVE` with `berr-counter tx 0 rx 0`. If you get zero
frames with the counter pinned at **127 at every bitrate**, that is
termination, not bitrate.

Prove the controller independently of the wiring:

```bash
ssh osd32mp1 'ip link set can0 down; ip link set can0 up type can bitrate 1000000 loopback on; (candump -T 2000 can0 &); cansend can0 123#DEADBEEF; sleep 2'
```

## Measure CAN bus load and timing

```bash
ssh osd32mp1 'cd /usr/local/ninja && python3 can_bandwidth.py --seconds 300'
```

Reports bus utilisation (nominal and worst-case bit stuffing) and, per message
type, the **transfer** rate/jitter/max-gap plus frames-per-message. Uses kernel
`SO_TIMESTAMP`, and counts a transfer only on the tail byte's start-of-transfer
bit - timing raw frames reports ~300 % jitter that is entirely artifact.

## DroneCAN: grant node IDs and watch live sensor data

Nodes stay silent until something allocates them an ID:

```bash
ssh osd32mp1 'python3 /home/root/dronecan_allocator.py --seconds 60'
```

Runs the allocation server (node 127) plus a monitor, and prints each node's
name, message mix and any GNSS fix. Grants persist in
`/home/root/dronecan_alloc.db`, so IDs are stable across reboots.

**One-time setup on the board:**

```bash
ssh osd32mp1 'python3 -m pip install --no-cache-dir dronecan && apt-get update && apt-get install -y --no-install-recommends python3-sqlite3'
```

`python3-sqlite3` is genuinely required and genuinely missing from the stock
image — `dronecan.app.dynamic_node_id` imports `sqlite3` at module scope, so
**`import dronecan` itself fails** without it, not just the allocator. The
library `libsqlite3.so.0` is already present; only Python's `_sqlite3`
extension is absent, and ST's OpenSTLinux apt feed has it.


## Bring up CAN after a reboot (do this BEFORE believing any sensor is missing)

`can0` comes up DOWN, and `ip` is not on root's default PATH — so the obvious
command fails with a bare `sh: ip: not found`.

```bash
export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
ip link set can0 up type can bitrate 1000000
ip -br link show can0
```

Then start the dynamic node-ID allocator. Until it runs, **every node sits
broadcasting anonymous allocation requests and publishes no sensor data**, so
the bus looks dead and a bridge run reports `mag: 0` and `gps: 0`:

```bash
setsid nohup python3 /home/root/dronecan_allocator.py > /tmp/alloc.log 2>&1 &
```

`setsid` matters: a plain `&` job is killed by SIGHUP when the ssh session ends.

Healthy bus, ~15 s after the allocator starts:

    msg 1001  25.1 Hz  node 125   magnetometer
    msg 1061   5.0 Hz  node 124   gnss.Auxiliary
    msg 1063   5.0 Hz  node 124   gnss.Heading
    msg  341   3.0 Hz  nodes 124/125/127  NodeStatus

## Read the magnetometer off CAN

Payload is three `float16` Gauss values at **offset 0** — there is no
`sensor_id` byte. Count transfers, not frames: only frames whose tail byte has
bit 0x80 set start a transfer. Skip `node == 0`, whose ID layout differs.

```python
cid, dlc = struct.unpack("<IB", frame[:5]); cid &= 0x1FFFFFFF
node = cid & 0x7F
if node and (cid >> 8) & 0xFFFF == 1001:
    b = frame[8:8+dlc]
    if b[dlc-1] & 0x80:                        # start of transfer
        x, y, z = struct.unpack("<eee", b[:6]) # Gauss
```

Sanity check the magnitude before trusting any of it: Earth's field is
0.25-0.65 Ga (25-65 uT). A reading of thousands of Gauss means the offset is
wrong, not that the sensor is broken.

## Read firmware diagnostics (the ring, not stdout)

Flight-loop diagnostics go to a lock-free ring in `/dev/shm/ninjapilot-log`
(printf in a flight loop caused priority-inversion deadlock - see CLAUDE.md).

```bash
shmlogd            # follow live, like tail -f
shmlogd --dump     # replay backlog and exit - WORKS AFTER A CRASH
```

The ring survives firmware death, so `--dump` after a wedge shows the final
seconds. Build if missing: `cc -O2 -o /usr/bin/shmlogd osd32mp1/shmlogd.c`.
Only one firmware instance can run: the flock pidfile at
`/var/run/ninjapilot-fw.pid` names the pid of whoever holds it.

## Build the custom AP_Periph for the L431 (gcc 10.2.1 ONLY)

The patch (`ap-periph-ninja-debug.patch`) adds the declared BMP388 probe that
the stock hwdef structurally cannot do (`HAL_I2C_INTERNAL_MASK 1` hides the
bus from every `BARO_PROBE_EXT` bit), plus a bench I2C scanner with SDA/SCL
swap detection reported over `debug.LogMessage`.

```bash
# toolchain: gcc 13.3 produces images that HOLD THE NODE IN ITS BOOTLOADER.
# 10.2.1 (arm-gnu 10-2020-q4-major) is ArduPilot's blessed compiler and works.
export PATH=~/gcc-arm-none-eabi-10-2020-q4-major/bin:$PATH

# the tree must live at a path with NO SPACES (ChibiOS scripts break)
cd ~/ardupilot
git apply "<repo>/osd32mp1/ap-periph-ninja-debug.patch"

./waf configure --board MatekL431-Periph   # RERUN after ANY hwdef edit -
./waf AP_Periph                            # else you get a byte-identical
                                           # binary and a 2-second "success"
```

Output: `build/MatekL431-Periph/bin/AP_Periph.bin`. The exact flashed binary
is committed as `fw/AP_Periph-ninja-gcc10.bin` (md5-verify against it after a
rebuild if you expect no change). Parameters survive app updates.

## Flash an L431 node over CAN, and recover a failed flash

```bash
scp fw/AP_Periph-ninja-gcc10.bin root@<board>:/home/root/fw/AP_Periph.bin
ssh root@<board> 'python3 can_flash.py'    # flashes node 124, ~2 min at 1.7 KB/s
```

`can_flash.py` sends `BeginFirmwareUpdate` and serves the file itself. It
embeds the three dronecan-python traps: every `node.spin()` wrapped (raises
`TransferError` on wire noise), request callbacks guarded against None (the
timeout value), flasher node id 126 (127 is the resident allocator).

**Judging the result — the bootloader identity trap:** anything answering
GetNodeInfo with `sw 2.0 vcs=00000000 mode=MAINTENANCE vendor≈13` is the
BOOTLOADER, not an app. A flash is done ONLY when mode reads OPERATIONAL (0)
and the sensor suite publishes. The healthy boot trace is mode 3 → 1 → 0.

**Recovery floor (tested live):** a failed or interrupted flash leaves the
node's bootloader waiting on the bus in mode 3 — reachable and reflashable
forever. The CAN update path never writes the bootloader region, so the worst
case is a waiting bootloader, never a brick. Re-run the flasher with a good
image (the stock one from
https://firmware.ardupilot.org/AP_Periph/latest/MatekL431-Periph/ always
works). SWD pads are the absolute fallback; they have never been needed.

## Recover a CAN node that has gone deaf (TX storm / pool starvation)

Symptom: the node heartbeats but answers NOTHING (params, restart, Begin all
time out), sensor rates collapsed, multi-frame transfers never complete.
Software cannot break in — the shared canard pool is exhausted.

Arm the ambush on the board, then power-cycle the node:

```python
# spam BeginFirmwareUpdate ~5/s; the app's ~1s init calm after power-on
# hears it before the storm starts and parks in the bootloader (mode 3)
node = dronecan.make_node("can0", node_id=126, bitrate=1000000)
fs = dronecan.app.file_server.FileServer(node, lookup_paths=["/home/root/fw"])
begin = dronecan.uavcan.protocol.file.BeginFirmwareUpdate.Request(
    source_node_id=126,
    image_file_remote_path=dronecan.uavcan.protocol.file.Path(path="AP_Periph.bin"))
while True:
    node.request(begin, 124, lambda e: None, timeout=0.2)
    node.spin(0.1)   # watch NodeStatus for mode 3, then keep serving
```

Once parked, run `flash124b.py` (a fresh Begin re-attaches cleanly even if
the ambush server died mid-feed). Judge success ONLY by mode==0 AND the
sensor suite publishing — `mode = (b[4]>>3)&7`, and health `(b[4]>>6)` is
NOT mode.


## Identify anything on the L431's I2C bus (one command, no rebuild)

The custom AP_Periph carries a param-triggered scanner: set `I2C_SCAN=1`
over DroneCAN and the node sweeps its bus, reports every ACK with common ID
registers over `debug.LogMessage` (msg 16383), then bit-bangs the same probe
with SDA/SCL swapped to catch crossed pairs. Self-clears; reboot the node
afterwards (the pin-stealing leaves a cosmetic IERR chatter until restart).

Known IDs seen on this bench: `0x68 id[75]=68` MPU-9150, `0x77 id[00]=50`
BMP388, `0x2C id[00]=80` QMC5883P, `0x0E id[00]=10` IST8310.

This settled two "missing compass" mysteries in ninety seconds each. Scan
and read IDs before trusting any module's part label or pin silk.

## Tune the CAN sensor stream live (no reflash)

All set over DroneCAN param GetSet on node 124, effective immediately:

| param | range | what |
|---|---|---|
| `INS_SAMPLE_RATE` | 1-400 | compact gyro/accel pair rate; delivered = ~316/N (divider of the real 316 Hz loop base; max ~305-317) |
| `IMU_RAW_RATE` | 0-200 | standard RawIMU; **0 disables** (halves the bus); >=100 storms the wire - deliberately allowed to exercise DEGRADEDHZ |
| `BARO_MAX_RATE` | 0-100 | 0 = native 50 Hz, else cap |
| `GPS1_RATE_MS` | 100-200 | 100 = 10 Hz on the M9N |

DEGRADEDHZ (NodeStatus vendor bit 15) latches if TX fails sustained; the
throttle releases the moment a NEW rate is requested - only the flag stays
until reboot.

## Push to BOTH remotes

Day-to-day history goes to origin; OpenPilotAI gets tree snapshots (its
Octavo branch has no shared ancestry - never push the full history there):

```bash
git push git@github.com:MAVProxyUser/NinjaPilot-15.02.ninja.git claude:claude
git fetch git@github.com:MAVProxyUser/OpenPilotAI.git Octavo:refs/remotes/opai/Octavo
NEW=$(git commit-tree 'HEAD^{tree}' -p refs/remotes/opai/Octavo -m "snapshot: <summary>")
git push git@github.com:MAVProxyUser/OpenPilotAI.git $NEW:refs/heads/Octavo
```
