/**
 ******************************************************************************
 *
 * @file       pios_udp_rcvr.c
 * @brief      PPM-format stick input over UDP - see pios_udp_rcvr.h for the
 *             wire format and the link-health contract.
 *
 * Design notes, in the order they were learned elsewhere in this tree:
 *  - NON-blocking socket + drain-per-wakeup + vTaskDelay(1), exactly like
 *    PIOS_UDP_RxThread: a blocking syscall in a FreeRTOS Posix-port task
 *    wedges the whole scheduler at high priority.
 *  - NO stdio anywhere in the task (the stdio-convoy lesson): one-shot
 *    events go through PIOS_SHMLOG_Printf.
 *  - Single-writer/single-reader fields, 4-byte-aligned stores (atomic on
 *    armv7) - same unlocked discipline as pios_udp.c's client field.
 *
 * @see        The GNU Public License (GPL) Version 3
 *
 *****************************************************************************/

#include "pios.h"

#include <pios_shmlog.h>

#if defined(PIOS_INCLUDE_UDPRCVR)

#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#include <pios_udp_rcvr.h>

/* Frame is stale (per-channel failsafe) after this long without an update */
#define UDPRCVR_STALE_MS      500
/* Stream counts as fully LOST (quality 0) after this long */
#define UDPRCVR_LOST_MS       1000
/* Loss accounting window */
#define UDPRCVR_WINDOW_MS     1000

#define UDPRCVR_FRAME_MIN     8   /* magic + seq + count + one channel  */
#define UDPRCVR_FRAME_MAX     (6 + 2 * PIOS_UDPRCVR_MAX_CHANNELS)

static int32_t PIOS_UDPRCVR_Get(uint32_t rcvr_id, uint8_t channel);

const struct pios_rcvr_driver pios_udp_rcvr_driver = {
    .read = PIOS_UDPRCVR_Get,
};

struct udprcvr_state {
    int      socket;
    uint16_t port;

    uint16_t channels[PIOS_UDPRCVR_MAX_CHANNELS];
    uint8_t  nchannels;

    uint32_t last_rx_ms;      /* tick-derived ms of the last valid frame */
    bool     ever_active;

    /* sequence-based loss accounting, one window at a time */
    uint8_t  last_seq;
    bool     have_seq;
    uint32_t win_start_ms;
    uint32_t win_received;
    uint32_t win_lost;
    uint8_t  quality;         /* 0..100, result of the LAST closed window */

    uint32_t frames_total;
    uint32_t frames_bad;
    bool     lost_announced;

    uint8_t  rx_buffer[64];
};

static struct udprcvr_state udprcvr;

static uint32_t udprcvr_now_ms(void)
{
    return (uint32_t)(xTaskGetTickCount() * portTICK_RATE_MS);
}

static void udprcvr_frame(const uint8_t *b, int len)
{
    if (len < UDPRCVR_FRAME_MIN || b[0] != 'P' || b[1] != 'P' || b[2] != 'M' || b[3] != '1') {
        udprcvr.frames_bad++;
        return;
    }
    uint8_t seq   = b[4];
    uint8_t count = b[5];
    if (count < 1 || count > PIOS_UDPRCVR_MAX_CHANNELS || len < 6 + 2 * count) {
        udprcvr.frames_bad++;
        return;
    }

    for (uint8_t i = 0; i < count; i++) {
        uint16_t v = (uint16_t)(b[6 + 2 * i] | (b[7 + 2 * i] << 8));
        udprcvr.channels[i] = v;
    }
    udprcvr.nchannels = count;

    uint32_t now = udprcvr_now_ms();

    /* loss accounting from the sequence numbers */
    if (udprcvr.have_seq) {
        uint8_t gap = (uint8_t)(seq - udprcvr.last_seq);
        if (gap == 0) {
            /* duplicate - count as received, no loss */
        } else if (gap > 1) {
            udprcvr.win_lost += (uint32_t)(gap - 1);
        }
    }
    udprcvr.last_seq = seq;
    udprcvr.have_seq = true;
    udprcvr.win_received++;

    if (!udprcvr.ever_active) {
        udprcvr.ever_active = true;
        PIOS_SHMLOG_Printf("[udp-ppm] first stick frame: %u channels on port %u",
                           (unsigned)count, (unsigned)udprcvr.port);
    }
    if (udprcvr.lost_announced) {
        udprcvr.lost_announced = false;
        PIOS_SHMLOG_Printf("[udp-ppm] stick stream RESTORED");
    }

    udprcvr.last_rx_ms = now;
    udprcvr.frames_total++;
}

static void udprcvr_close_window(uint32_t now)
{
    if ((now - udprcvr.win_start_ms) < UDPRCVR_WINDOW_MS) {
        return;
    }
    uint32_t seen  = udprcvr.win_received;
    uint32_t total = seen + udprcvr.win_lost;
    if (total > 0) {
        udprcvr.quality = (uint8_t)((seen * 100u) / total);
    } else if (udprcvr.ever_active) {
        udprcvr.quality = 0;
    }
    udprcvr.win_received = 0;
    udprcvr.win_lost     = 0;
    udprcvr.win_start_ms = now;

    if (udprcvr.ever_active && !udprcvr.lost_announced
        && (now - udprcvr.last_rx_ms) > UDPRCVR_LOST_MS) {
        udprcvr.lost_announced = true;
        PIOS_SHMLOG_Printf("[udp-ppm] stick stream LOST (last frame %ums ago)",
                           (unsigned)(now - udprcvr.last_rx_ms));
    }
}

static void *PIOS_UDPRCVR_Task(void *parameters)
{
    (void)parameters;
    while (1) {
        int received;
        do {
            received = recv(udprcvr.socket, udprcvr.rx_buffer,
                            sizeof(udprcvr.rx_buffer), 0);
            if (received > 0) {
                udprcvr_frame(udprcvr.rx_buffer, received);
            }
        } while (received > 0);

        udprcvr_close_window(udprcvr_now_ms());
        vTaskDelay(1);
    }
    return NULL;
}

int32_t PIOS_UDPRCVR_Init(uint32_t *udprcvr_id, uint16_t port)
{
    memset(&udprcvr, 0, sizeof(udprcvr));
    udprcvr.port = port;

    udprcvr.socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udprcvr.socket < 0) {
        return -1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(port);
    if (bind(udprcvr.socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        return -2;
    }

    /* freshness beats completeness - same reasoning as the telemetry
     * socket's small SO_RCVBUF: stale sticks are worse than dropped ones */
    int rcvbuf = 4096;
    (void)setsockopt(udprcvr.socket, SOL_SOCKET, SO_RCVBUF, &rcvbuf, sizeof(rcvbuf));

    int flags = fcntl(udprcvr.socket, F_GETFL, 0);
    if (flags < 0 || fcntl(udprcvr.socket, F_SETFL, flags | O_NONBLOCK) < 0) {
        return -3;
    }

    udprcvr.win_start_ms = udprcvr_now_ms();

    /* Telemetry-band priority: sticks arrive at 25-50 Hz and feed the
     * 25 Hz Receiver task - nothing sensor-critical rides on this. */
    xTaskHandle task;
    xTaskCreate((pdTASK_CODE)PIOS_UDPRCVR_Task, "UDP_PPM", 1024, NULL,
                (tskIDLE_PRIORITY + 2), &task);

    *udprcvr_id = 1; /* single instance */
    return 0;
}

static int32_t PIOS_UDPRCVR_Get(uint32_t rcvr_id, uint8_t channel)
{
    (void)rcvr_id;
    if (channel >= PIOS_UDPRCVR_MAX_CHANNELS) {
        return PIOS_RCVR_INVALID;
    }
    if (!udprcvr.ever_active || channel >= udprcvr.nchannels) {
        return PIOS_RCVR_TIMEOUT;
    }
    if ((udprcvr_now_ms() - udprcvr.last_rx_ms) > UDPRCVR_STALE_MS) {
        return PIOS_RCVR_TIMEOUT;
    }
    return (int32_t)udprcvr.channels[channel];
}

uint8_t PIOS_UDPRCVR_Quality(void)
{
    if (!udprcvr.ever_active) {
        return 0;
    }
    if ((udprcvr_now_ms() - udprcvr.last_rx_ms) > UDPRCVR_LOST_MS) {
        return 0;
    }
    return udprcvr.quality;
}

bool PIOS_UDPRCVR_EverActive(void)
{
    return udprcvr.ever_active;
}

#endif /* PIOS_INCLUDE_UDPRCVR */
