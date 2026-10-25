# ESP-IDF project for the NinjaPilot litewing target.
#
# Build:
#   . $IDF_PATH/export.sh
#   cd flight/targets/boards/litewing/esp-idf
#   idf.py set-target esp32
#   idf.py build flash monitor
#
# The UAVObject sources this links against are GENERATED, and the generator is
# Make-driven. Run the normal tree build once first so that
# build/uavobject-synthetics/flight/ is populated:
#
#   make uavobjects_flight
#
cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(ninjapilot_litewing)
