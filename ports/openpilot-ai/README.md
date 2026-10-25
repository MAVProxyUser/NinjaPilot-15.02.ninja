# OpenPilotAI — folded in as tags

OpenPilotAI is the SITL autonomy distribution built on this tree: SimPosix +
Gazebo Harmonic, the intercept flight mode, the target EKF, the barn-trial
results, and example flights with their three matching logs. It lived in the
separate `OpenPilotAI` repo (which the project also uses as a publish mirror).

## Why this is a tag, not a checked-out subtree

Its `main` line is a **125 MB distribution** whose bulk is a *snapshot of this
very tree's* `flight/` and `ground/` code plus large binary assets (Gazebo
world meshes, CMSIS `.a` libraries, a packaged `OpenPilot.dmg`). Checking that
into the working tree would duplicate NinjaPilot's own firmware and re-bloat
the repo that was just cleaned up. Instead its **full history is folded into
this repository** and reachable from these tags:

- `ports/openpilot-ai-main` — the autonomy distribution + intercept work +
  example flights (own root; 18 commits).
- `ports/openpilot-ai-octavo` — the OSD32MP1 snapshot line + the DroneCAN DNA
  firmware node + the BRK board bring-up docs (138 commits).

The objects live in this repo's store and push to its origin, so everything is
in one place. Nothing from OpenPilotAI is lost.

## Getting the distribution out

```bash
# browse it
git show ports/openpilot-ai-main:README.md
# extract the whole distribution into a scratch dir
git archive ports/openpilot-ai-main | tar -x -C /tmp/openpilot-ai
# or check out just the unique parts (intercept docs, example flights)
git checkout ports/openpilot-ai-main -- examples docs
```

The live intercept / SITL source is maintained in this tree directly
(`flight/`, `ground/gazebo_bridge/`, `CLAUDE.md`); the OpenPilotAI tags are the
packaged, distributable form of it.

If you want the full distribution checked out here as a working subtree instead
of a tag, it can be subtree-merged under this directory on request.
