cmake_minimum_required(VERSION 3.16)
project(WindControl)

# AUTOMOC did not pick up Q_OBJECT from the .hh header on this toolchain
# (it generated an empty mocs_compilation.cpp and the signals/vtable were
# undefined at link). Invoke moc explicitly instead - deterministic, and
# obvious to anyone reading this later.
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(gz-gui8 REQUIRED)
find_package(gz-msgs10 REQUIRED)
find_package(gz-transport13 REQUIRED)
find_package(gz-plugin2 REQUIRED COMPONENTS register)
find_package(Qt5 REQUIRED COMPONENTS Core Quick QuickControls2)

qt5_wrap_cpp(WIND_MOC WindControl.hh)
qt5_wrap_cpp(GPS_MOC GpsNoise.hh)

# ONE LIBRARY PER PLUGIN. GZ_ADD_PLUGIN emits a per-library registration
# hook, so two registrations linked into the same library collide with a
# "duplicate symbol _GzPluginHook" error.
foreach(plugin WindControl GpsNoise)
  if(plugin STREQUAL "WindControl")
    set(plugin_moc ${WIND_MOC})
  else()
    set(plugin_moc ${GPS_MOC})
  endif()
  add_library(${plugin} SHARED ${plugin}.cc ${plugin_moc} ${plugin}.qrc)
  target_include_directories(${plugin} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(${plugin}
    PRIVATE gz-gui8::gz-gui8
    PRIVATE gz-msgs10::gz-msgs10
    PRIVATE gz-transport13::gz-transport13
    PRIVATE gz-plugin2::register
    PRIVATE Qt5::Core Qt5::Quick Qt5::QuickControls2)
endforeach()
