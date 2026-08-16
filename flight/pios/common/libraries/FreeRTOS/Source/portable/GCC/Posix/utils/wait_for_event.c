/*
 * FreeRTOS Kernel V11.3.0
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

/*
 * NINJAPILOT LOCAL HARDENING (2026-08-16) - lost-wakeup fix, kept until
 * upstream carries an equivalent (verified absent from FreeRTOS-Kernel main,
 * which is byte-identical to this file apart from the version header).
 *
 * The port delivers the tick by pthread_kill(SIGALRM) at pxCurrentTCB's
 * pthread. Mid-switch, that thread can be INSIDE event_wait's
 * pthread_cond_wait. The handler then runs ON that thread and performs a
 * nested context switch, whose nested event_wait CONSUMES the resume signal
 * meant for the outer wait. The handler returns, the outer cond_wait resumes
 * with event_triggered already false, and the task parks FOREVER while the
 * tick keeps every other task alive - so it looks like selective task death,
 * not a crash.
 *
 * Proven on OSD32MP1 (2-core armv7, glibc 2.31): under ~500 Hz sensor
 * publishing the firmware lost its Sensors task and two callback-scheduler
 * tasks within 2-20 s, every run, under both SCHED_OTHER and SCHED_FIFO and
 * with the process pinned to one CPU. gdb: the parked tasks sat in
 * event_wait beneath xQueueSemaphoreTake(xTicksToWait=10) - a 10 ms timeout
 * frozen for ten minutes - while voluntary context-switch counters proved
 * ticks still flowed.
 *
 * Fix: make the event handshake a signal-free critical section. With every
 * signal blocked across lock..unlock, a tick aimed at this thread queues and
 * delivers AFTER the handshake completes, so a nested switch can never steal
 * a resume from inside it. A tick delayed by the handshake's few
 * microseconds is indistinguishable from ordinary jitter.
 */
static inline void prvBlockAllSignals( sigset_t * pxOld )
{
    sigset_t xAll;

    sigfillset( &xAll );
    pthread_sigmask( SIG_BLOCK, &xAll, pxOld );
}
static inline void prvRestoreSignals( sigset_t * pxOld )
{
    pthread_sigmask( SIG_SETMASK, pxOld, NULL );
}

#include "wait_for_event.h"

struct event
{
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexattr;
    pthread_cond_t cond;
    bool event_triggered;
};
/*-----------------------------------------------------------*/

struct event * event_create( void )
{
    struct event * ev = malloc( sizeof( struct event ) );

    if( ev != NULL )
    {
        ev->event_triggered = false;
        pthread_mutexattr_init( &ev->mutexattr );
        #ifndef __APPLE__
            pthread_mutexattr_setrobust( &ev->mutexattr, PTHREAD_MUTEX_ROBUST );
        #endif
        pthread_mutex_init( &ev->mutex, &ev->mutexattr );
        pthread_cond_init( &ev->cond, NULL );
    }

    return ev;
}
/*-----------------------------------------------------------*/

void event_delete( struct event * ev )
{
    pthread_mutex_destroy( &ev->mutex );
    pthread_mutexattr_destroy( &ev->mutexattr );
    pthread_cond_destroy( &ev->cond );
    free( ev );
}
/*-----------------------------------------------------------*/

bool event_wait( struct event * ev )
{
    sigset_t xOld;

    prvBlockAllSignals( &xOld );

    if( pthread_mutex_lock( &ev->mutex ) == EOWNERDEAD )
    {
        #ifndef __APPLE__
            /* If the thread owning the mutex died, make the mutex consistent. */
            pthread_mutex_consistent( &ev->mutex );
        #endif
    }

    while( ev->event_triggered == false )
    {
        pthread_cond_wait( &ev->cond, &ev->mutex );
    }

    ev->event_triggered = false;
    pthread_mutex_unlock( &ev->mutex );
    prvRestoreSignals( &xOld );
    return true;
}
/*-----------------------------------------------------------*/

bool event_wait_timed( struct event * ev,
                       time_t ms )
{
    struct timespec ts;
    int ret = 0;
    sigset_t xOld;

    prvBlockAllSignals( &xOld );

    clock_gettime( CLOCK_REALTIME, &ts );
    ts.tv_sec += ms / 1000;
    ts.tv_nsec += ( ( ms % 1000 ) * 1000000 );
    if( pthread_mutex_lock( &ev->mutex ) == EOWNERDEAD )
    {
        #ifndef __APPLE__
            /* If the thread owning the mutex died, make the mutex consistent. */
            pthread_mutex_consistent( &ev->mutex );
        #endif
    }

    while( ( ev->event_triggered == false ) && ( ret == 0 ) )
    {
        ret = pthread_cond_timedwait( &ev->cond, &ev->mutex, &ts );

        if( ( ret == -1 ) && ( errno == ETIMEDOUT ) )
        {
            prvRestoreSignals( &xOld );
            return false;
        }
    }

    ev->event_triggered = false;
    pthread_mutex_unlock( &ev->mutex );
    prvRestoreSignals( &xOld );
    return true;
}
/*-----------------------------------------------------------*/

void event_signal( struct event * ev )
{
    sigset_t xOld;

    prvBlockAllSignals( &xOld );

    if( pthread_mutex_lock( &ev->mutex ) == EOWNERDEAD )
    {
        #ifndef __APPLE__
            /* If the thread owning the mutex died, make the mutex consistent. */
            pthread_mutex_consistent( &ev->mutex );
        #endif
    }
    ev->event_triggered = true;
    pthread_cond_signal( &ev->cond );
    pthread_mutex_unlock( &ev->mutex );
    prvRestoreSignals( &xOld );
}
/*-----------------------------------------------------------*/
