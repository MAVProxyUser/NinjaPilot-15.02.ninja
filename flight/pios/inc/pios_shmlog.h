/**
 ******************************************************************************
 * @file       pios_shmlog.h
 * @author     NinjaPilot, 2026
 * @brief      Lock-free shared-memory log ring for flight-loop diagnostics
 * @see        The GNU Public License (GPL) Version 3
 *
 * WHY THIS EXISTS: printf in a flight loop on the FreeRTOS Posix port is a
 * blocking write() syscall made by whatever pthread the task runs on - the
 * port cannot schedule around it, and stdio adds a process-wide mutex shared
 * with every other printing thread. Diagnostics belong in memory: a writer
 * here costs a vsnprintf and a few atomics, never a syscall, never a lock.
 * A separate daemon (osd32mp1/shmlogd.c) consumes the ring and does the
 * actual I/O in its own process. The ring lives in /dev/shm and SURVIVES a
 * firmware crash, so the last seconds before a wedge are always readable -
 * which this project has needed badly.
 *****************************************************************************/
#ifndef PIOS_SHMLOG_H
#define PIOS_SHMLOG_H

#if defined(PIOS_TARGET_POSIX) || defined(SIMPOSIX) || defined(USE_SIM_POSIX)

extern void PIOS_SHMLOG_Init(const char *path);
/** Wait-free from ANY thread (FreeRTOS task or raw pthread). Drops on a full
 *  ring rather than ever waiting - a dropped diagnostic beats a late gyro. */
extern void PIOS_SHMLOG_Printf(const char *fmt, ...)
__attribute__((format(printf, 1, 2)));

#else /* hard targets compile shared files; markers there are ifdef'd out */
#define PIOS_SHMLOG_Init(p)        do {} while (0)
#define PIOS_SHMLOG_Printf(...)    do {} while (0)
#endif

#endif /* PIOS_SHMLOG_H */
