#
# This file is part of SDLGamepad.
#
# SDLGamepad is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# SDLGamepad is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
#
# Manuel Blanquett
# mail.nalla@gmail.com
#

TEMPLATE = lib
TARGET = sdlgamepad
DEFINES += SDLGAMEPAD_LIBRARY

include(../../openpilotgcslibrary.pri)

macx {
    # Use pkg-config to find SDL2
    CONFIG += link_pkgconfig
    PKGCONFIG += sdl2
    
    # Fallback for systems without pkg-config
    isEmpty(PKGCONFIG) {
        INCLUDEPATH += /opt/homebrew/include/SDL2 /usr/local/include/SDL2
        LIBS += -L/opt/homebrew/lib -L/usr/local/lib -lSDL2
    }
    
    LIBS += -framework OpenGL -framework Cocoa
}

win32 {
    INCLUDEPATH += $${SDL2_DIR}/include
    LIBS += -L$${SDL2_DIR}/lib -lSDL2 -lSDL2main
}

unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG += sdl2
    
    # Fallback for systems without pkg-config
    isEmpty(PKGCONFIG) {
        LIBS += -lSDL2
    }
}

SOURCES += \
    sdlgamepad.cpp

HEADERS += \
    sdlgamepad.h \
    sdlgamepad_global.h

OTHER_FILES += \
	COPYING \
    README \
    sdlgamepad.dox \
    sdlgamepad.doc

include(copydata.pro)
