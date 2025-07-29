######################################################################
# Qwt Examples - Copyright (C) 2002 Uwe Rathmann
# This file may be used under the terms of the 3-clause BSD License
######################################################################

include( $${PWD}/../examples.pri )

# Suppress warnings for unused private fields in this example
macx: QMAKE_CXXFLAGS += -Wno-unused-private-field

TARGET       = splineeditor

HEADERS = \
    ScalePicker.h \
    CanvasPicker.h \
    Plot.h 

SOURCES = \
    ScalePicker.cpp \
    CanvasPicker.cpp \
    Plot.cpp \
    main.cpp 
