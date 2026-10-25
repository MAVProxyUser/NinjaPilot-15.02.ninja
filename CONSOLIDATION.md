# One repo: what lives where (2026-10-24 consolidation)

This repository was consolidated on 2026-10-24 so there is a single place to
come back to, instead of several branches, forks and renamed folders. The
canonical branch is **`master`**. Everything that was a separate branch or
sibling repo is now either merged into `master`, carried as a subtree under
`ports/`, or preserved as a tag. Nothing was discarded.

## The one branch

`master` holds the whole flight-controller tree: all the firmware targets, the
NinjaPilot GCS, the SimPosix/Gazebo SITL stack and the OSD32MP1 tooling. The
old working branches (`litewing`, `cubepurple`, `brk-i2c-sensors`, `claude`)
were merged into it and then retired; their pre-merge tips are kept as
`archive/*` tags.

## Target boards (`flight/targets/boards/`)

Built from `master` with `make fw_<board>` (needs a space-free path — symlink
the checkout and pass `ROOT_DIR`, see the board READMEs). Verified building
with `arm-none-eabi-gcc` 13.3:

| Board | MCU | Notes |
|-------|-----|-------|
| `coptercontrol` | STM32F1 | CC3D / Atom / OPCC |
| `oplinkmini` | STM32F1 | OPLink Mini radio modem |
| `cubepurple` | STM32F427 | CubePilot Cube Purple (FMUv3), DroneCAN ESCs, flew 2026-10-13 |
| `simposix` | host | primary SITL target (Gazebo bridge) |
| `simwroom` | host | posix twin of the ESP32-WROOM board |
| `simlitewing` | host | posix twin of the LiteWing board |
| `realposix` | Linux (OSD32MP1) | builds on the board's embedded Linux, not on macOS (needs SocketCAN / `sys/prctl.h`) |
| `pixracer` | STM32F427 | FMUv4 port, **staged / not in the default build** — see `flight/targets/boards/pixracer/README.md` |

## Folded-in sibling projects (`ports/`)

| Path | What | Form |
|------|------|------|
| `ports/esp32-wroom/` | ESP32-WROOM-32E firmware (ESP-IDF) | subtree, full history folded in |
| `ports/openpilot-ai/` | OpenPilotAI SITL autonomy distribution | history folded in as tags |

See `ports/README.md`.

## Tags

- `archive/*` — pre-consolidation branch tips (`master-2015`,
  `litewing-pre-unify`, `cubepurple-pre-unify`, `brk-i2c-pre-unify`,
  `claude-2026-09-02`, `recovered-brk-docs-2026-08-20`).
- `experiment/*` — the vertical-estimator experiments (`alt-v1-benedict-bordner`,
  `alt-v2-sagehusa`, `alt-v3-kalman`, `alt-v4-ekf13indoor`) and the 2015
  `cc3d-mem-save-2015` change. Not merged; the flying default is unchanged.
  See `docs/EXPERIMENTS.md`.
- `ports/*` — the ESP32 variant lines (`esp32-wroom-litewing`,
  `esp32-wroom-spektrum-bind`, `esp32-s2`) and the OpenPilotAI lines
  (`openpilot-ai-main`, `openpilot-ai-octavo`).

## Still separate on disk (not git-folded)

`../PixracerOpenPilot` and `../OpenPilot` are a different upstream lineage with
an incompatible tree layout and cannot be git-merged; the PixRacer board is
being brought across by hand (the `pixracer` target above). `../lineage/*`
(ArduPilot, iNav, AM32, …) is third-party reference material, left as is.
