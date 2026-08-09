# WindControl - Gazebo GUI wind panel

Two sliders inside the Gazebo window: **wind speed** (mph) and the direction
the wind blows **FROM** (compass degrees, with an N/NNE/... label).

The stock `Publisher` panel can publish wind too, but only by hand-writing a
protobuf message - which means doing this conversion in your head every time:

    linear_velocity is the ENU vector the wind blows TOWARD, so for a wind
    FROM bearing B at speed v:   x(east) = -v*sin(B),  y(north) = -v*cos(B)
    and enable_wind must be true or WindEffects applies nothing.

## Build

Qt5 is keg-only under Homebrew, so CMake has to be pointed at it:

```bash
cd gui_plugins/WindControl && mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qt@5
make
```

## Run

```bash
export GZ_GUI_PLUGIN_PATH="$PWD/gui_plugins/WindControl/build:$GZ_GUI_PLUGIN_PATH"
gz sim -g
```

The world declares the panel in its `<gui>` block. Note that block contains
ONLY this plugin: listing the full default panel set there instead replaces
Gazebo's defaults, which silently drops the MarkerManager and takes the
flight trails with it.

## Gotcha, for whoever builds the next panel

AUTOMOC did not detect `Q_OBJECT` in the `.hh` header on this toolchain - it
produced an empty `mocs_compilation.cpp` and the signals and vtable were
undefined at link time. `qt5_wrap_cpp` is called explicitly instead.
