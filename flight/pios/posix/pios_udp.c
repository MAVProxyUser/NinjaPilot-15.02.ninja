/**
 ******************************************************************************
 *
 * @file       pios_udp.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 *              Parts by Thorsten Klose (tk@midibox.org) (tk@midibox.org)
 * @brief      UDP commands. Inits UDPs, controls UDPs & Interupt handlers.
 * @see        The GNU Public License (GPL) Version 3
 * @defgroup   PIOS_UDP UDP Functions
 * @{
 *
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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


/* Project Includes */
#include "pios.h"

#if defined(PIOS_INCLUDE_UDP)

#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <pios_udp_priv.h>

/* We need a list of UDP devices */

#define PIOS_UDP_MAX_DEV 256
static int8_t pios_udp_num_devices = 0;

static pios_udp_dev pios_udp_devices[PIOS_UDP_MAX_DEV];


/* Provide a COM driver */
static void PIOS_UDP_ChangeBaud(uint32_t udp_id, uint32_t baud);
static void PIOS_UDP_RegisterRxCallback(uint32_t udp_id, pios_com_callback rx_in_cb, uint32_t context);
static void PIOS_UDP_RegisterTxCallback(uint32_t udp_id, pios_com_callback tx_out_cb, uint32_t context);
static void PIOS_UDP_TxStart(uint32_t udp_id, uint16_t tx_bytes_avail);
static void PIOS_UDP_RxStart(uint32_t udp_id, uint16_t rx_bytes_avail);

const struct pios_com_driver pios_udp_com_driver = {
    .set_baud   = PIOS_UDP_ChangeBaud,
    .tx_start   = PIOS_UDP_TxStart,
    .rx_start   = PIOS_UDP_RxStart,
    .bind_tx_cb = PIOS_UDP_RegisterTxCallback,
    .bind_rx_cb = PIOS_UDP_RegisterRxCallback,
};


static pios_udp_dev *find_udp_dev_by_id(uint8_t udp)
{
    if (udp >= pios_udp_num_devices) {
        /* Undefined UDP port for this board (see pios_board.c) */
        PIOS_Assert(0);
        return NULL;
    }

    /* Get a handle for the device configuration */
    return &(pios_udp_devices[udp]);
}

/**
 * RxThread
 */
void *PIOS_UDP_RxThread(void *udp_dev_n)
{
    pios_udp_dev *udp_dev = (pios_udp_dev *)udp_dev_n;

    /**
     * com devices never get closed except by application "reboot"
     * we also never give up our mutex except for waiting
     */
#if defined(PIOS_INCLUDE_FREERTOS)
    /* FREERTOS + POSIX PORT CONSTRAINT (learned the hard way - a plain
     * blocking recvfrom() at HIGH task priority wedges the entire RTOS):
     * in the Posix port a task blocked in a NATIVE syscall still counts
     * as FreeRTOS's ready/running task - the scheduler keeps selecting
     * it while the pthread sits in the kernel, so nothing lower ever
     * runs. Blocking natively was only ever survivable at the old
     * bottom-of-the-system priority (everything outranked it), and that
     * exact placement is what let the kernel socket queue back up under
     * real flight load - seconds of stale-but-in-order sensor and
     * command data, surfacing as the load-dependent "estimator randomly
     * freezes" symptom.
     *
     * Port-correct real-time design instead: NON-blocking socket, drain
     * EVERY pending datagram per wakeup, then genuinely block in
     * FreeRTOS (vTaskDelay one tick) so every other task runs normally.
     * At high task priority this bounds sensor/command staleness to
     * ~one tick (1ms) regardless of system load, matching the role this
     * thread plays on real hardware (ISR+DMA: drain immediately, never
     * make sensor bytes wait on application code). */
    /* Lower bound on com-fifo free space, updated from every push's
     * headroom out-parameter. The parser only ever DRAINS between our
     * pushes, so a stale value understates the real free space - safe
     * direction for the all-or-nothing check below. */
    uint16_t fifo_headroom = 0xFFFF;
    uint32_t whole_drops   = 0;
    uint32_t datagrams     = 0;
    uint32_t bytes_total   = 0;
    uint32_t n11 = 0, n27 = 0, nOther = 0;
    struct timeval dbg_tv;
    gettimeofday(&dbg_tv, NULL);
    uint32_t dbg_last_ms   = (uint32_t)(dbg_tv.tv_sec * 1000 + dbg_tv.tv_usec / 1000);
    while (1) {
        int received;
        {
            struct timeval tv2;
            gettimeofday(&tv2, NULL);
            uint32_t now_ms = (uint32_t)(tv2.tv_sec * 1000 + tv2.tv_usec / 1000);
            if (now_ms - dbg_last_ms >= 1000) {
                dbg_last_ms = now_ms;
                printf("[SIMPOSIX-IFDEF-MARKER] pios_udp.c dev sock=%i: datagrams=%u bytes=%u drops=%u n11=%u n27=%u nOther=%u\n",
                       udp_dev->socket, (unsigned)datagrams, (unsigned)bytes_total, (unsigned)whole_drops,
                       (unsigned)n11, (unsigned)n27, (unsigned)nOther);
                fflush(stdout);
            }
        }
        do {
            udp_dev->clientLength = sizeof(udp_dev->client);
            received = recvfrom(udp_dev->socket,
                                &udp_dev->rx_buffer,
                                PIOS_UDP_RX_BUFFER_SIZE,
                                0,
                                (struct sockaddr *)&udp_dev->client,
                                (socklen_t *)&udp_dev->clientLength);
            if (received > 0) {
                datagrams++;
                bytes_total += (uint32_t)received;
                if (received == 11) {
                    n11++;
                } else if (received == 27) {
                    n27++;
                    /* Corruption-signature trap: parse-side CRC failures
                     * show a constant 0x01 where the checksum should be -
                     * if 27-byte datagrams with a 0x01 tail exist HERE, the
                     * corruption arrived off the wire; if they never do,
                     * it happens between this push and the parser's read. */
                    if (udp_dev->rx_buffer[26] == 0x01) {
                        static uint32_t tail01 = 0;
                        tail01++;
                        if ((tail01 % 200) == 1) {
                            printf("[SIMPOSIX-IFDEF-MARKER] pios_udp.c 27B datagram with 0x01 tail #%u:", (unsigned)tail01);
                            for (int b = 0; b < 27; b++) {
                                printf(" %02X", udp_dev->rx_buffer[b]);
                            }
                            printf("\n");
                            fflush(stdout);
                        }
                    }
                } else {
                    nOther++;
                }
                /* ALL-OR-NOTHING per datagram. The com layer's
                 * fifoBuf_putData() copies AS MUCH AS FITS and silently
                 * truncates the rest - fine for a USART byte stream,
                 * stream-corrupting for datagram framing: a truncated
                 * UAVTalk packet fails CRC and throws the parser into a
                 * resync scan that eats its NEIGHBORS too. Measured live
                 * before this check existed: the last-in-burst object
                 * (AccelSensor) arrived at ~3% while first-in-burst
                 * (GyroSensor) arrived at ~100% - positional, systematic
                 * loss. Dropping a WHOLE datagram when the fifo can't
                 * take all of it keeps the stream clean: the parser
                 * simply never sees that packet, and the next one parses
                 * normally. */
                if ((uint16_t)received > fifo_headroom) {
                    whole_drops++;
                    if ((whole_drops % 500) == 1) {
                        printf("[SIMPOSIX-IFDEF-MARKER] pios_udp.c: whole-datagram drops=%u (com fifo full)\n",
                               (unsigned)whole_drops);
                        fflush(stdout);
                    }
                } else {
                    bool rx_need_yield = false;
                    if (udp_dev->rx_in_cb) {
                        (void)(udp_dev->rx_in_cb)(udp_dev->rx_in_context, udp_dev->rx_buffer, received, &fifo_headroom, &rx_need_yield);
                    }
                }
            }
        } while (received > 0);
        vTaskDelay(1);
    }
#else /* PIOS_INCLUDE_FREERTOS */
    while (1) {
        /**
         * receive
         */
        int received;
        udp_dev->clientLength = sizeof(udp_dev->client);
        if ((received = recvfrom(udp_dev->socket,
                                 &udp_dev->rx_buffer,
                                 PIOS_UDP_RX_BUFFER_SIZE,
                                 0,
                                 (struct sockaddr *)&udp_dev->client,
                                 (socklen_t *)&udp_dev->clientLength)) >= 0) {
            /* copy received data to buffer if possible */
            /* we do NOT buffer data locally. If the com buffer can't receive, data is discarded! */
            /* (thats what the USART driver does too!) */
            bool rx_need_yield = false;
            if (udp_dev->rx_in_cb) {
                (void)(udp_dev->rx_in_cb)(udp_dev->rx_in_context, udp_dev->rx_buffer, received, NULL, &rx_need_yield);
            }
        }
    }
#endif /* PIOS_INCLUDE_FREERTOS */
    return NULL;
}


/**
 * Open UDP socket
 */
int32_t PIOS_UDP_Init(uint32_t *udp_id, const struct pios_udp_cfg *cfg)
{
    pios_udp_dev *udp_dev = &pios_udp_devices[pios_udp_num_devices];

    pios_udp_num_devices++;


    /* initialize */
    udp_dev->rx_in_cb  = NULL;
    udp_dev->tx_out_cb = NULL;
    udp_dev->cfg    = cfg;

    /* assign socket */
    udp_dev->socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    memset(&udp_dev->server, 0, sizeof(udp_dev->server));
    memset(&udp_dev->client, 0, sizeof(udp_dev->client));
    udp_dev->server.sin_family = AF_INET;
    udp_dev->server.sin_addr.s_addr = inet_addr(udp_dev->cfg->ip);
    udp_dev->server.sin_port   = htons(udp_dev->cfg->port);
    int res = bind(udp_dev->socket, (struct sockaddr *)&udp_dev->server, sizeof(udp_dev->server));

    /* Bound the kernel receive buffer to a small, real-time-appropriate
     * size. This socket is the SimPosix stand-in for the hardware sensor/
     * telemetry links; for a real-time control feed, freshness beats
     * completeness - a deep kernel buffer (platform defaults are hundreds
     * of KB) becomes a multi-second FIFO of stale-but-in-order data the
     * moment the RX task falls behind, and every consumer downstream
     * (state estimator, receiver/ManualControl) then reads seconds-old
     * reality with no error or drop ever surfacing. Confirmed live: a
     * commanded throttle CUT arrived at ManualControlCommand ~5s late,
     * time-stretched, while the bridge-side send loop was provably
     * current - the backlog was here, in the kernel socket queue. With a
     * small buffer, transient overload drops OLD data instead of
     * delaying ALL data (UAVTalk's ACKed settings writes retry on their
     * own, so config traffic survives drops fine). */
    int rcvbuf = 16384;
    if (setsockopt(udp_dev->socket, SOL_SOCKET, SO_RCVBUF, &rcvbuf, sizeof(rcvbuf)) < 0) {
        printf("udp dev %i - warning: SO_RCVBUF set failed\n", pios_udp_num_devices - 1);
    }

#if defined(PIOS_INCLUDE_FREERTOS)
    /* Non-blocking is REQUIRED for the FreeRTOS drain-per-wakeup receive
     * loop (see PIOS_UDP_RxThread) - with a blocking socket the first
     * empty recvfrom() would block the pthread natively, which in the
     * Posix port stalls the whole RTOS when done from a high-priority
     * task. */
    int flags = fcntl(udp_dev->socket, F_GETFL, 0);
    if (flags < 0 || fcntl(udp_dev->socket, F_SETFL, flags | O_NONBLOCK) < 0) {
        printf("udp dev %i - warning: O_NONBLOCK set failed\n", pios_udp_num_devices - 1);
    }
#endif

    /* Create receive thread for this connection */
#if defined(PIOS_INCLUDE_FREERTOS)
// ( pdTASK_CODE pvTaskCode, const portCHAR * const pcName, unsigned portSHORT usStackDepth, void *pvParameters, unsigned portBASE_TYPE uxPriority, xTaskHandle *pvCreatedTask );
    /* HIGHEST task priority in the system (see pios_callbackscheduler.h's
     * DelayedCallbackPriorityTask ladder - DEVICEDRIVER sits at
     * tskIDLE_PRIORITY+7 after the STABILIZATIONOUTERLOOP bump), NOT the
     * old tskIDLE_PRIORITY+1 (the LOWEST in the system). On real hardware
     * this thread's job is done by a hardware ISR that preempts every
     * task, always - sensor bytes never wait for application code. At
     * priority 1 this task was starved for whole seconds under real
     * flight load once the estimator/control tasks (priorities 3-6)
     * started genuinely running hot, which is exactly when fresh sensor
     * data matters most - the load-dependent "estimator randomly
     * freezes" symptom was largely THIS: the estimator running fine on
     * seconds-old input. Its per-wakeup work is a recvfrom + fifo copy
     * (microseconds), so top priority costs the rest of the system
     * essentially nothing - same rate/deadline-monotonic reasoning as
     * the callback-scheduler priority ladder. */
    xTaskCreate((pdTASK_CODE)PIOS_UDP_RxThread, "UDP_Rx_Thread", 1024, (void *)udp_dev, (tskIDLE_PRIORITY + 7), &udp_dev->rxThread);
#else
    pthread_create(&udp_dev->rxThread, NULL, PIOS_UDP_RxThread, (void *)udp_dev);
#endif


    printf("udp dev %i - socket %i opened - result %i\n", pios_udp_num_devices - 1, udp_dev->socket, res);

    *udp_id = pios_udp_num_devices - 1;

    return res;
}


void PIOS_UDP_ChangeBaud(uint32_t udp_id, uint32_t baud)
{
    /**
     * doesn't apply!
     */
}


static void PIOS_UDP_RxStart(uint32_t udp_id, uint16_t rx_bytes_avail)
{
    /**
     * lazy!
     */
}


static void PIOS_UDP_TxStart(uint32_t udp_id, uint16_t tx_bytes_avail)
{
    pios_udp_dev *udp_dev = find_udp_dev_by_id(udp_id);

    PIOS_Assert(udp_dev);

    int32_t length, len, rem;

    /**
     * we send everything directly whenever notified of data to send (lazy!)
     */
    if (udp_dev->tx_out_cb) {
        while (tx_bytes_avail > 0) {
            bool tx_need_yield = false;
            length = (udp_dev->tx_out_cb)(udp_dev->tx_out_context, udp_dev->tx_buffer, PIOS_UDP_RX_BUFFER_SIZE, NULL, &tx_need_yield);
            rem    = length;
            while (rem > 0) {
                len = sendto(udp_dev->socket, udp_dev->tx_buffer + length - rem, rem, 0,
                             (struct sockaddr *)&udp_dev->client,
                             sizeof(udp_dev->client));
                if (len <= 0) {
                    rem = 0;
                } else {
                    rem -= len;
                }
            }
            tx_bytes_avail -= length;
        }
    }
}

static void PIOS_UDP_RegisterRxCallback(uint32_t udp_id, pios_com_callback rx_in_cb, uint32_t context)
{
    pios_udp_dev *udp_dev = find_udp_dev_by_id(udp_id);

    PIOS_Assert(udp_dev);

    /*
     * Order is important in these assignments since ISR uses _cb
     * field to determine if it's ok to dereference _cb and _context
     */
    udp_dev->rx_in_context = context;
    udp_dev->rx_in_cb = rx_in_cb;
}

static void PIOS_UDP_RegisterTxCallback(uint32_t udp_id, pios_com_callback tx_out_cb, uint32_t context)
{
    pios_udp_dev *udp_dev = find_udp_dev_by_id(udp_id);

    PIOS_Assert(udp_dev);

    /*
     * Order is important in these assignments since ISR uses _cb
     * field to determine if it's ok to dereference _cb and _context
     */
    udp_dev->tx_out_context = context;
    udp_dev->tx_out_cb = tx_out_cb;
}


#endif /* if defined(PIOS_INCLUDE_UDP) */
