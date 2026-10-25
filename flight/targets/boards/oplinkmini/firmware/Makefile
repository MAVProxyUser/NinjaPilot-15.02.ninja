#
# Copyright (c) 2009-2013, The OpenPilot Team, http://www.openpilot.org
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

ifndef OPENPILOT_IS_COOL
    $(error Top level Makefile must be used to build this target)
endif

include ../board-info.mk
include $(ROOT_DIR)/make/firmware-defs.mk

# ARM DSP library
override USE_DSP_LIB := NO

# List of mandatory modules to include
MODULES += RadioComBridge
# Firmware update / reboot over UAVTalk (GCS 'Halt', opdfu.py halt): the modem
# answers the 1122/2233/3344 sequence only when BoardType names its own board.
MODULES += FirmwareIAP

# List of optional modules to include
OPTMODULES =

# List C source files here (C dependencies are automatically generated).
# Use file-extension c for "c-only"-files
ifndef TESTAPP
    ## The standard CMSIS startup
    SRC += $(CMSIS_DEVICEDIR)/system_stm32f10x.c

    ## Application Core
    SRC += ../pios_usb_board_data.c
    SRC += $(OPMODULEDIR)/OPLink/oplinkmod.c
    SRC += $(OPSYSTEM)/oplink.c
    SRC += $(OPSYSTEM)/pios_board.c
    SRC += $(OPUAVTALK)/uavtalk.c
    SRC += $(OPUAVOBJ)/uavobjectmanager.c
    SRC += $(OPUAVOBJ)/uavobjectpersistence.c
    SRC += $(OPUAVOBJ)/eventdispatcher.c

    ## Misc library functions
    SRC += $(FLIGHTLIB)/sha1.c

    ## UAVObjects
    SRC += $(OPUAVSYNTHDIR)/oplinkstatus.c
    SRC += $(OPUAVSYNTHDIR)/oplinksettings.c
    SRC += $(OPUAVSYNTHDIR)/objectpersistence.c
    SRC += $(OPUAVSYNTHDIR)/oplinkreceiver.c
    SRC += $(OPUAVSYNTHDIR)/radiocombridgestats.c
    SRC += $(OPUAVSYNTHDIR)/firmwareiapobj.c
else
    ## Test Code
    SRC += $(OPTESTS)/test_common.c
    SRC += $(OPTESTS)/$(TESTAPP).c
endif

# Optional component libraries
include $(FLIGHTLIB)/rscode/library.mk

# GCC 13 vs this F1 tree (same block as the Cube Purple target):
# strict-aliasing miscompiled the kernel's list handling, and the packed
# UAVObject structs trip -Werror=address-of-packed-member.
CFLAGS += -fno-strict-aliasing
CPPFLAGS += -fno-strict-aliasing
CFLAGS += -Wno-address-of-packed-member
CPPFLAGS += -Wno-address-of-packed-member
CFLAGS += -Wno-missing-attributes -Wno-misleading-indentation -Wno-attributes
CFLAGS += -Wno-stringop-overflow -Wno-stringop-overread
CPPFLAGS += -Wno-stringop-overflow -Wno-stringop-overread
CFLAGS += -Wno-implicit-fallthrough -Wno-unused-function -Wno-unused-but-set-variable -Wno-array-bounds -Wno-maybe-uninitialized
CPPFLAGS += -Wno-implicit-fallthrough -Wno-unused-function -Wno-unused-but-set-variable -Wno-array-bounds -Wno-maybe-uninitialized

# A modem has no FlightStatus: FirmwareIAP must not look for one before resetting.
CDEFS += -DPIOS_APPS_MINIMAL

include $(ROOT_DIR)/make/apps-defs.mk
include $(ROOT_DIR)/make/common-defs.mk

# GCC 13 flags every unsuffixed double constant in the shared libraries;
# must follow common-defs.mk, which turns the warning on.
CONLYFLAGS += -Wno-unsuffixed-float-constants
