/**
 ******************************************************************************
 * @file       pios_dsm.c (posix)
 * @brief      Spektrum/DSM satellite serial receiver for the realposix target.
 *
 * The bare-metal DSM driver (pios/stm32f4xx) is bound to PIOS_COM/USART and
 * cannot run here. This is a self-contained POSIX port: a reader thread opens
 * a Linux tty (e.g. /dev/ttySTM2 = USART2 = PF4 on the OSD32MP1-BRK), syncs
 * 16-byte DSM frames on the inter-frame gap, and unrolls the 7 channel words
 * exactly like PIOS_DSM_UnrollChannels (resolution auto-detect, 2nd-frame
 * mask, empty-slot skip). It exposes the standard pios_rcvr_driver so it plugs
 * straight into pios_rcvr_group_map[...DSMMAINPORT] and ManualControl reads it
 * when ChannelGroups selects "DSM (MainPort)".
 *
 * The RAW 10/11-bit channel value is returned (like the bare-metal driver);
 * the Receiver module's ChannelMin/Neutral/Max calibration does the scaling.
 * Binding (the GPIO pulse train) is a separate step - by the time this runs
 * the satellite is already bound and streaming.
 ******************************************************************************/
#include "pios.h"

#ifdef PIOS_INCLUDE_DSM

/* DSM frame constants. We deliberately do NOT include pios_dsm_priv.h here:
 * it drags in the bare-metal pios_stm32.h / pios_usart_priv.h, which don't
 * compile on POSIX. These mirror that header's values. */
#define DSM_CHANNELS_PER_FRAME 7
#define DSM_FRAME_LENGTH       (2 + DSM_CHANNELS_PER_FRAME * 2)   /* fades + system + 7x2 = 16 */
#define DSM_2ND_FRAME_MASK     0x8000
#define PIOS_DSM_NUM_INPUTS    12

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <poll.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <sys/prctl.h>

#define DSM_POSIX_FRAME_SIZE   DSM_FRAME_LENGTH   /* 16 */
#define DSM_POSIX_GAP_MS       4                  /* >4ms silence = frame boundary (frame is ~1.4ms @115200) */
#define DSM_POSIX_STALE_S      0.2                /* no fresh frame in 200ms -> TIMEOUT */
#define DSM_POSIX_BAUD         B115200            /* SPM9745 streams clean at 115200 (native 125000 also works) */

struct pios_dsm_posix_dev {
    int             fd;
    pthread_t       thread;
    volatile bool   run;
    pthread_mutex_t lock;
    uint16_t        channels[PIOS_DSM_NUM_INPUTS];
    double          last_frame_t;
    bool            have_frame;
    uint8_t         resolution;     /* 10 or 11, auto-detected */
    uint32_t        frames;         /* good frames decoded */
    char            dev[96];
};

/* One receiver on this target. */
static struct pios_dsm_posix_dev dsm_dev;

static double dsm_now_s(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (double)t.tv_sec + (double)t.tv_nsec * 1e-9;
}

/* Unroll one 16-byte frame into channels[]. Mirrors PIOS_DSM_UnrollChannels:
 * data[0]=fades, data[1]=system, data[2..15]=7 big-endian channel words. */
static void dsm_unroll(struct pios_dsm_posix_dev *d, const uint8_t *data)
{
    uint8_t  res = d->resolution;
    uint16_t staging[PIOS_DSM_NUM_INPUTS];

again:
    ;
    uint32_t channel_log = 0;
    uint16_t mask = (res == 10) ? 0x03ff : 0x07ff;
    const uint8_t *s = &data[2];

    for (int i = 0; i < DSM_CHANNELS_PER_FRAME; i++) {
        uint16_t word = ((uint16_t)s[0] << 8) | s[1];
        s += 2;

        if (word == 0xffff) {           /* empty channel slot */
            continue;
        }
        if ((i > 0) && (word & DSM_2ND_FRAME_MASK)) {
            return;                     /* malformed - drop the frame */
        }

        uint8_t ch = (word >> res) & 0x0f;
        if (ch < PIOS_DSM_NUM_INPUTS) {
            if (channel_log & (1u << ch)) {   /* duplicate => actually 10-bit data */
                if (res == 10) {
                    return;
                }
                res = 10;
                goto again;
            }
            if ((channel_log & 0xFF) == 0x55) {  /* 10-bit signature => actually 11-bit */
                if (res == 11) {
                    return;
                }
                res = 11;
                goto again;
            }
            staging[ch] = word & mask;
            channel_log |= (1u << ch);
        }
    }

    d->resolution = res;
    pthread_mutex_lock(&d->lock);
    for (int ch = 0; ch < PIOS_DSM_NUM_INPUTS; ch++) {
        if (channel_log & (1u << ch)) {
            d->channels[ch] = staging[ch];
        }
    }
    d->last_frame_t = dsm_now_s();
    d->have_frame   = true;
    d->frames++;
    pthread_mutex_unlock(&d->lock);
}

/* Reader thread: accumulate bytes; a poll timeout (the ~9ms inter-frame gap)
 * marks a frame boundary. A complete 16-byte buffer at the gap is one frame. */
static void *dsm_reader(void *arg)
{
    struct pios_dsm_posix_dev *d = (struct pios_dsm_posix_dev *)arg;

    prctl(PR_SET_NAME, "dsm-rcvr", 0, 0, 0);

    uint8_t frame[64];
    int     len = 0;

    while (d->run) {
        struct pollfd pfd = { .fd = d->fd, .events = POLLIN };
        int pr = poll(&pfd, 1, DSM_POSIX_GAP_MS);
        if (pr > 0 && (pfd.revents & POLLIN)) {
            uint8_t tmp[64];
            int n = read(d->fd, tmp, sizeof(tmp));
            for (int i = 0; i < n; i++) {
                if (len < (int)sizeof(frame)) {
                    frame[len++] = tmp[i];
                } else {
                    len = 0;            /* overrun - resync on next gap */
                }
            }
        } else {
            /* gap: the buffer holds one frame if it is exactly 16 bytes */
            if (len == DSM_POSIX_FRAME_SIZE) {
                dsm_unroll(d, frame);
            }
            len = 0;                    /* always resync at the boundary */
        }
    }
    return NULL;
}

/* pios_rcvr_driver .read: raw channel value, or TIMEOUT/INVALID. */
static int32_t PIOS_DSM_POSIX_Get(uint32_t rcvr_id, uint8_t channel)
{
    struct pios_dsm_posix_dev *d = (struct pios_dsm_posix_dev *)rcvr_id;

    if (channel >= PIOS_DSM_NUM_INPUTS) {
        return PIOS_RCVR_INVALID;
    }
    int32_t val;
    pthread_mutex_lock(&d->lock);
    bool stale = !d->have_frame || (dsm_now_s() - d->last_frame_t) > DSM_POSIX_STALE_S;
    val = stale ? PIOS_RCVR_TIMEOUT : (int32_t)d->channels[channel];
    pthread_mutex_unlock(&d->lock);
    return val;
}

const struct pios_rcvr_driver pios_dsm_posix_rcvr_driver = {
    .read = PIOS_DSM_POSIX_Get,
};

/* Open `dev_path` at 115200 8N1 raw and start the reader thread.
 * Returns 0 on success; *dsm_id is the lower id passed to PIOS_RCVR_Init. */
int32_t PIOS_DSM_POSIX_Init(uint32_t *dsm_id, const char *dev_path)
{
    struct pios_dsm_posix_dev *d = &dsm_dev;

    memset(d, 0, sizeof(*d));
    d->resolution = 11;
    strncpy(d->dev, dev_path, sizeof(d->dev) - 1);

    d->fd = open(dev_path, O_RDONLY | O_NOCTTY | O_NONBLOCK);
    if (d->fd < 0) {
        printf("[dsm] open %s failed: %s\n", dev_path, strerror(errno));
        return -1;
    }

    struct termios tio;
    memset(&tio, 0, sizeof(tio));
    if (tcgetattr(d->fd, &tio) == 0) {
        cfmakeraw(&tio);
        cfsetispeed(&tio, DSM_POSIX_BAUD);
        cfsetospeed(&tio, DSM_POSIX_BAUD);
        tio.c_cflag &= ~(PARENB | CSTOPB | CSIZE);
        tio.c_cflag |= CS8 | CREAD | CLOCAL;   /* 8N1 */
        tio.c_cc[VMIN]  = 0;
        tio.c_cc[VTIME] = 0;
        tcsetattr(d->fd, TCSANOW, &tio);
        tcflush(d->fd, TCIFLUSH);
    }

    pthread_mutex_init(&d->lock, NULL);
    for (int ch = 0; ch < PIOS_DSM_NUM_INPUTS; ch++) {
        d->channels[ch] = PIOS_RCVR_TIMEOUT;
    }
    d->run = true;
    if (pthread_create(&d->thread, NULL, dsm_reader, d) != 0) {
        printf("[dsm] reader thread failed\n");
        close(d->fd);
        d->fd = -1;
        return -1;
    }

    *dsm_id = (uint32_t)d;
    printf("[dsm] Spektrum receiver on %s (115200 8N1), group DSM(MainPort)\n", dev_path);
    return 0;
}

#endif /* PIOS_INCLUDE_DSM */
