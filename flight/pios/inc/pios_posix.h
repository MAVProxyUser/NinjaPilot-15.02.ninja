/**
 ******************************************************************************
 *
 * @file       posix.h
 * @author     Corvus Corax Copyright (C) 2010.
 * @brief      Definitions to run PiOS on posix
 * @see        The GNU Public License (GPL) Version 2
 *
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef PIOS_POSIX_H
#define PIOS_POSIX_H

#include <stdint.h>

#ifndef __cplusplus
typedef enum { FALSE = 0, TRUE = !FALSE } bool;

/* MUST stay inside the !__cplusplus guard, together with the enum that
 * actually declares FALSE/TRUE.
 *
 * It used to sit outside. In C++ `false` is a KEYWORD, not a macro, so
 * `#ifndef false` is true there - the block fired and defined `false` to
 * FALSE, an identifier the enum above had just been guarded OUT of existing.
 * Every C++ translation unit then failed the moment it wrote `false`
 * (fixedwingflycontroller.cpp:592 among many), and the damage spread into
 * libstdc++ headers because the macro rewrites `false` everywhere.
 *
 * macOS never showed this: its system headers define TRUE/FALSE, so the
 * dangling reference happened to resolve. glibc does not, so the bug only
 * appears when building for Linux - which is exactly the port to the
 * OSD32MP1's Debian armv7l. Nothing arch-specific about it; it is purely
 * about which libc supplies TRUE/FALSE.
 */
#ifndef false
        #define false FALSE
        #define true  TRUE
#endif
#endif /* !__cplusplus */

// #define FILEINFO FILE*

// #define PIOS_SERVO_NUM_OUTPUTS 8
// #define PIOS_SERVO_NUM_TIMERS PIOS_SERVO_NUM_OUTPUTS

#endif /* PIOS_POSIX_H */
