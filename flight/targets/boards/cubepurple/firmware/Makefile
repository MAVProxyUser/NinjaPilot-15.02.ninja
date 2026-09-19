#
# Copyright (c) 2015-2026, The OpenPilot Team, http://www.openpilot.org
# Copyright (c) 2012-2013, The OpenPilot Team, http://www.openpilot.org
# Copyright (c) 2009-2010, dRonin, http://dronin.org
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
USE_DSP_LIB ?= NO
USE_CXX = YES

# List of mandatory modules to include.  No OPLink radio, no on-board data
# flash for the Logging module, no OSD; the rest is the Revolution's set.
MODULES += Sensors
MODULES += StateEstimation
MODULES += Airspeed
MODULES += Stabilization
MODULES += ManualControl
MODULES += Receiver
MODULES += Actuator
MODULES += GPS
MODULES += TxPID
MODULES += CameraStab
MODULES += Battery
MODULES += FirmwareIAP
MODULES += PathPlanner
MODULES += PathFollower
MODULES += Telemetry
MODULES += Notify

OPTMODULES += ComUsbBridge

SRC += $(FLIGHTLIB)/notification.c

# Include all camera options
CDEFS += -DUSE_INPUT_LPF -DUSE_GIMBAL_LPF -DUSE_GIMBAL_FF

# Some diagnostics
CDEFS += -DDIAG_TASKS

# Bring-up knobs from the command line, e.g. CUBE_CDEFS=-DCUBE_BOOT_STOP=3
CDEFS += $(CUBE_CDEFS)

# The F427 has 192 KB of SRAM: the msheap allocator's default 15-bit block
# sizes (4-byte units) cannot describe a heap that large, and its "heap too
# large" assertion is silent, so the free list is corrupt from the start and
# the first allocation from the main heap bus-faults.  Widen the markers.
CDEFS += -DHEAP_SUPPORT_LARGE

# Fallback settings bank in internal flash (board-info.mk)
CDEFS += -DFS_BANK_BASE=$(FS_BANK_BASE) -DFS_BANK_SIZE=$(FS_BANK_SIZE)

# Misc options
CFLAGS += -ffast-math
# GCC 13 warns about pointers into the packed UAVObject structs, which this
# tree has always used; the ESP32/posix builds do not build with -Werror here.
CFLAGS += -Wno-address-of-packed-member
CPPFLAGS += -Wno-address-of-packed-member
# GCC 13 vs the untouched F4 PiOS/CMSIS files (noreturn aliases in startup.c,
# indentation in ST's system file)
CFLAGS += -Wno-missing-attributes -Wno-misleading-indentation -Wno-attributes
# GCC 13 sees the quaternion passed as &q1 and objects to the 16-byte access
CFLAGS += -Wno-stringop-overflow -Wno-stringop-overread
CPPFLAGS += -Wno-stringop-overflow -Wno-stringop-overread
# GCC 13 diagnostics the rest of this tree does not build under -Werror
CFLAGS += -Wno-implicit-fallthrough -Wno-unused-function -Wno-unused-but-set-variable -Wno-array-bounds -Wno-maybe-uninitialized
CPPFLAGS += -Wno-implicit-fallthrough -Wno-unused-function -Wno-unused-but-set-variable -Wno-array-bounds -Wno-maybe-uninitialized

# List C source files here (C dependencies are automatically generated).
# Use file-extension c for "c-only-files"
ifndef TESTAPP
    ## Application Core
    SRC += ../pios_usb_board_data.c
    ## The board-info blob normally lives in the OpenPilot bootloader; this
    ## board boots through the ArduPilot one, so the firmware carries it.
    SRC += $(PIOSCOMMON)/pios_board_info.c
    SRC += $(OPMODULEDIR)/System/systemmod.c
    CPPSRC += $(OPSYSTEM)/cubepurple.cpp
    SRC += $(OPSYSTEM)/pios_board.c
    SRC += $(FLIGHTLIB)/alarms.c
    SRC += $(FLIGHTLIB)/instrumentation.c
    SRC += $(FLIGHTLIB)/paths.c
    SRC += $(FLIGHTLIB)/plans.c
    SRC += $(FLIGHTLIB)/auxmagsupport.c
    SRC += $(FLIGHTLIB)/WorldMagModel.c
    SRC += $(FLIGHTLIB)/insgps13state.c
    ## newlib syscall stubs (a bare board has no OS to call)
    SRC += $(OPSYSTEM)/syscalls.c
    SRC += $(OPUAVTALK)/uavtalk.c
    SRC += $(OPUAVOBJ)/uavobjectmanager.c
    SRC += $(OPUAVOBJ)/uavobjectpersistence.c
    SRC += $(OPUAVOBJ)/eventdispatcher.c

    ## Drivers this board brought with it
    SRC += $(PIOSCOMMON)/pios_invensense.c
    SRC += $(PIOSCOMMON)/pios_flash_fram.c
    SRC += $(PIOSCOMMON)/pios_iomcu.c

    ## UAVObjects
    include ./UAVObjects.inc
    SRC += $(UAVOBJSRC)
else
    ## Test Code
    SRC += $(OPTESTS)/test_common.c
    SRC += $(OPTESTS)/$(TESTAPP).c
endif

include $(ROOT_DIR)/make/apps-defs.mk
include $(ROOT_DIR)/make/common-defs.mk

# This tree writes double constants in the shared libraries (the posix and
# ESP32 builds do not carry -Wunsuffixed-float-constants).  apps-defs.mk turns
# the warning on, so the override has to come after it to win.
CONLYFLAGS += -Wno-unsuffixed-float-constants

# The Cube boots through its ArduPilot bootloader: link at FW_BANK_BASE with
# the board-info blob inline (see link_stm32f4xx_apj_sections.ld), and wrap
# the image in the .apj container that bootloader flashes.  The linker
# variable is assigned by the F4 library after the includes above and LDFLAGS
# expands it lazily, so it is swapped here.
LINKER_SCRIPTS_APP = $(PIOS_DEVLIB)link_stm32f4xx_apj_memory.ld \
		     $(PIOS_DEVLIB)link_stm32f4xx_apj_sections.ld

$(eval $(call APJ_TEMPLATE,$(OUTDIR)/$(TARGET).bin))
opfw: $(OUTDIR)/$(TARGET).apj
