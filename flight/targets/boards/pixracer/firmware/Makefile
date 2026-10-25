#
# Copyright (c) 2015-2026, The OpenPilot Team, http://www.openpilot.org
# Copyright (c) 2012-2013, The OpenPilot Team, http://www.openpilot.org
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

# PixRacer (FMUv4) was brought up through telemetry on the PixracerOpenPilot
# fork; this target carries that bring-up module set, ported onto the
# NinjaPilot tree (FreeRTOS 11.3, this tree's PiOS and UAVObject set).  The
# full Revolution flight stack (Sensors/StateEstimation/Stabilization/...) is
# a hardware-in-the-loop follow-on, exactly as it was staged for the Cube.
MODULES += FirmwareIAP
MODULES += Telemetry

OPTMODULES =

SRC += $(FLIGHTLIB)/notification.c

# Include all camera options (shared headers expect the symbols defined)
CDEFS += -DUSE_INPUT_LPF -DUSE_GIMBAL_LPF -DUSE_GIMBAL_FF

# The F427 has 192 KB of SRAM: the msheap allocator's default 15-bit block
# sizes cannot describe a heap that large (same as the Cube Purple target).
CDEFS += -DHEAP_SUPPORT_LARGE

# Fallback settings bank in internal flash (board-info.mk)
CDEFS += -DFS_BANK_BASE=$(FS_BANK_BASE) -DFS_BANK_SIZE=$(FS_BANK_SIZE)

# Misc options
CFLAGS += -ffast-math
# This code base predates GCC's strict-aliasing optimisations; GCC 13
# miscompiled the kernel's list handling under them (see FreeRTOSConfig.h).
CFLAGS += -fno-strict-aliasing
CPPFLAGS += -fno-strict-aliasing
# GCC 13 diagnostics the rest of this tree does not build under -Werror
# (identical block to the OPLink Mini / Cube Purple F4 targets).
CFLAGS += -Wno-address-of-packed-member
CPPFLAGS += -Wno-address-of-packed-member
CFLAGS += -Wno-missing-attributes -Wno-misleading-indentation -Wno-attributes
CFLAGS += -Wno-stringop-overflow -Wno-stringop-overread
CPPFLAGS += -Wno-stringop-overflow -Wno-stringop-overread
CFLAGS += -Wno-implicit-fallthrough -Wno-unused-function -Wno-unused-but-set-variable -Wno-array-bounds -Wno-maybe-uninitialized
CPPFLAGS += -Wno-implicit-fallthrough -Wno-unused-function -Wno-unused-but-set-variable -Wno-array-bounds -Wno-maybe-uninitialized

# List C source files here (C dependencies are automatically generated).
# Use file-extension c for "c-only-files"
ifndef TESTAPP
    ## Application Core
    SRC += ../pios_usb_board_data.c
    ## The board-info blob normally lives in the OpenPilot bootloader; this
    ## board boots through the PX4 one, so the firmware carries it.
    SRC += $(PIOSCOMMON)/pios_board_info.c
    SRC += $(OPMODULEDIR)/System/systemmod.c
    SRC += $(OPSYSTEM)/pixracer.c
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

    ## Sensor drivers this board carries (MPU9250 + ICM-20608-G on SPI1,
    ## HMC5983 mag on SPI1, MS5611 baro on SPI2).  No IO co-processor and no
    ## FRAM, unlike the Cube Purple.
    SRC += $(PIOSCOMMON)/pios_invensense.c
    SRC += $(PIOSCOMMON)/pios_hmc5x83.c
    SRC += $(PIOSCOMMON)/pios_ms5611.c

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

# This tree writes double constants in the shared libraries; apps-defs.mk turns
# -Wunsuffixed-float-constants on, so the override has to come after it to win.
CONLYFLAGS += -Wno-unsuffixed-float-constants

# PixRacer boots through its stock PX4 bootloader: link at FW_BANK_BASE with
# the board-info blob inline, and wrap the image in the .apj container the
# bootloader flashes (same path as the Cube Purple target).
LINKER_SCRIPTS_APP = $(PIOS_DEVLIB)link_stm32f4xx_apj_memory.ld \
		     $(PIOS_DEVLIB)link_stm32f4xx_apj_sections.ld

$(eval $(call APJ_TEMPLATE,$(OUTDIR)/$(TARGET).bin))
opfw: $(OUTDIR)/$(TARGET).apj
