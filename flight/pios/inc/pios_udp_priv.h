/**
 ******************************************************************************
 *
 * @file       pios_udp_priv.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 *             Parts by Thorsten Klose (tk@midibox.org)
 * @brief      UDP private definitions.
 * @see        The GNU Public License (GPL) Version 3
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

#ifndef PIOS_UDP_PRIV_H
#define PIOS_UDP_PRIV_H

#include <pios.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>

struct pios_udp_cfg {
    const char *ip;
    uint16_t   port;
};

typedef struct {
    const struct pios_udp_cfg *cfg;
#if defined(PIOS_INCLUDE_FREERTOS)
    xTaskHandle rxThread;
#else
    pthread_t   rxThread;
#endif

    int socket;
    struct sockaddr_in server;
    struct sockaddr_in client;
    uint32_t clientLength;

    /* Dual-homed reply symmetry (used on Linux via IP_PKTINFO): the local
     * address the last request was ADDRESSED to, and the interface it
     * arrived on. Replies are sent FROM that address, out that interface -
     * without this, a request to the WiFi address is answered from the
     * wired address (the kernel routes the reply out the preferred link)
     * and any connect()ed client silently discards it. Written by the RX
     * thread, read by TX - same unlocked single-writer discipline as the
     * `client` field above (4-byte aligned stores are atomic on armv7). */
    struct in_addr reply_src;
    int reply_ifindex;

    pthread_cond_t     cond;
    pthread_mutex_t    mutex;

    pios_com_callback  tx_out_cb;
    uint32_t tx_out_context;
    pios_com_callback  rx_in_cb;
    uint32_t rx_in_context;

    uint8_t  rx_buffer[PIOS_UDP_RX_BUFFER_SIZE];
    uint8_t  tx_buffer[PIOS_UDP_RX_BUFFER_SIZE];
} pios_udp_dev;

extern int32_t PIOS_UDP_Init(uint32_t *udp_id, const struct pios_udp_cfg *cfg);

extern const struct pios_com_driver pios_udp_com_driver;

#endif /* PIOS_UDP_PRIV_H */
