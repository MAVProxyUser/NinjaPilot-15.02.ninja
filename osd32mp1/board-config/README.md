# Board-side state that is NOT in the source tree

These are changes made to the running board. Without them the firmware still
builds and runs, but misses deadlines badly. Recorded here so the board is
reproducible from the repo instead of from memory.

## 1. `fwsimposix.service` — SCHED_FIFO

Copy to `/etc/systemd/system/`, then `systemctl daemon-reload && systemctl
enable --now fwsimposix`.

At the default SCHED_OTHER the 500 Hz loop runs up to **18 ms late** (9 periods;
0.31 % of periods breach the firmware's own critical threshold when idle, 5.4 %
under load). At SCHED_FIFO 50 the worst case is **0.23 ms** and nothing
breaches. It carries no CPUAffinity on purpose — see the comments in the unit.

## 2. I²C at 400 kHz — a device-tree property

**This is the single highest-impact change on the board and it is one property.**

`/dev/i2c-3` (I2C5, `i2c@40015000`) shipped with **no `clock-frequency`**, so the
stm32f7-i2c driver silently used its **100 kHz** default. A 14-byte MPU-9150
burst read — exactly what a PIOS driver issues once per sensor period — then
costs **1.68 ms, or 84 % of a 500 Hz period**. And because the i2c ioctl is not
a FreeRTOS blocking point, that is 1.68 ms during which the Posix port cannot
schedule *any* task: the whole firmware stalls.

At 400 kHz the same read costs **0.51 ms — 25 %**.

    # dtc is in ST's feed as `dtc dtc-misc`, NOT `device-tree-compiler`,
    # and apt needs a sane PATH or dpkg errors out.
    export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
    apt-get install -y dtc dtc-misc

    DTB=/boot/stm32mp157c-osd32mp1-red-v1_2.dtb
    cp -a $DTB $DTB.orig                      # keep a way back
    fdtput -t i $DTB /soc/i2c@40015000 clock-frequency 400000
    reboot

Verify after reboot — the property must appear in the LIVE tree, not just the
file:

    od -An -tu4 --endian=big /proc/device-tree/soc/i2c@40015000/clock-frequency

Measured before and after with `i2c_rate.c`:

| | 100 kHz | 400 kHz |
|---|---:|---:|
| median read | 1679 µs | **506 µs** |
| worst | 2034 µs | **698 µs** |
| % of a 2 ms period | 84 % | **25 %** |
| read-rate ceiling | 595 Hz | **1975 Hz** |

Do not pin the firmware to one CPU. The Posix port's IDLE task busy-spins, so
the process wants ~105 % of a core; RT bandwidth is aggregated across both
runqueues (~190 %), which is why it does not throttle. Confining it to a single
runqueue caps it at that queue's 95 % budget and causes exactly the throttling
SCHED_FIFO is there to avoid.

## 3. Packages added from ST's OpenSTLinux feed

`dtc`, `dtc-misc` (fdtput/fdtget), plus earlier `mmap`, `sqlite3`, `git`.
