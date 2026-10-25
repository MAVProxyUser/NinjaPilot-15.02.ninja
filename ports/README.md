# ports/ — folded-in sibling projects

Projects that used to live in their own repos next to this one, folded into
this tree during the 2026-10-24 consolidation so there is one place to come
back to. Each keeps its own build; none is part of the STM32/posix `make`
tree at the top level.

| Path | What | Form |
|------|------|------|
| `esp32-wroom/` | ESP32-WROOM-32E flight firmware (ESP-IDF, builds with `idf.py`). The litewing line. | checked-out subtree, full history folded in |
| `openpilot-ai/` | The OpenPilotAI SITL autonomy distribution (SimPosix + Gazebo) + intercept barn-trials. | history folded in as tags (see its README) |

Other preserved lines of these projects are reachable as tags:
`ports/esp32-wroom-spektrum-bind`, `ports/esp32-s2`, `ports/openpilot-ai-main`,
`ports/openpilot-ai-octavo`.
