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

add_library(WindControl SHARED WindControl.cc ${WIND_MOC} WindControl.qrc)
target_include_directories(WindControl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(WindControl
  PRIVATE gz-gui8::gz-gui8
  PRIVATE gz-msgs10::gz-msgs10
  PRIVATE gz-transport13::gz-transport13
  PRIVATE gz-plugin2::register
  PRIVATE Qt5::Core Qt5::Quick Qt5::QuickControls2)
