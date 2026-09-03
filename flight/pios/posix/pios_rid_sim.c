/**
 ******************************************************************************
 * @file       pios_rid_sim.c
 * @brief      Remote ID "transmitter" for the posix twins: emits the exact
 *             vendor-specific element a WiFi beacon would carry (0xDD, len,
 *             OUI FA:0B:BC, type 0x0D, counter, Message Pack) over UDP to
 *             127.0.0.1:9020, where tools/remoteid_listen.py decodes it.
 *             Whole body guarded: every .c in pios/posix compiles into every
 *             posix target.
 * @see        The GNU Public License (GPL) Version 3
 *****************************************************************************/
#include "pios.h"

#ifdef PIOS_INCLUDE_RID_SIM

#include <pios_rid.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#ifndef PIOS_RID_SIM_PORT
#define PIOS_RID_SIM_PORT 9020
#endif

int32_t PIOS_RID_Broadcast(const uint8_t *pack, uint16_t len, uint8_t counter)
{
    static int sock = -1;
    static struct sockaddr_in dst;

    if (sock < 0) {
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0) {
            return -1;
        }
        memset(&dst, 0, sizeof(dst));
        dst.sin_family = AF_INET;
        dst.sin_port   = htons(PIOS_RID_SIM_PORT);
        dst.sin_addr.s_addr = inet_addr("127.0.0.1");
    }
    if (!pack || !len) {
        return 0;
    }
    if (len + 5 > 255) {
        return -2;
    }
    uint8_t ie[7 + 255];
    ie[0] = 0xDD;
    ie[1] = (uint8_t)(5 + len);
    ie[2] = 0xFA; ie[3] = 0x0B; ie[4] = 0xBC;
    ie[5] = 0x0D;
    ie[6] = counter;
    memcpy(ie + 7, pack, len);
    (void)sendto(sock, ie, 7 + len, 0, (struct sockaddr *)&dst, sizeof(dst));
    return 0;
}

#endif /* PIOS_INCLUDE_RID_SIM */
