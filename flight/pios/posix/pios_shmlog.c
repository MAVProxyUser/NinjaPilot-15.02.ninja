/**
 ******************************************************************************
 * @file       pios_shmlog.c
 * @brief      MPSC shared-memory log ring. See pios_shmlog.h for the why.
 * @see        The GNU Public License (GPL) Version 3
 *****************************************************************************/
#include "pios.h"

#include <pios_shmlog.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>

/*
 * Vyukov-style bounded MPMC ring, specialised to many producers / one
 * consumer. Each slot carries a sequence number:
 *   writable  when seq == pos
 *   readable  when seq == pos + 1
 * A producer claims pos with fetch_add on head; if the slot is not writable
 * the consumer has fallen a whole lap behind and the record is DROPPED and
 * counted - producers are flight threads and must never wait on I/O.
 *
 * Plain mmap of a file in /dev/shm (tmpfs) rather than shm_open: identical
 * semantics, no librt dependency on this glibc.
 */
#define SHMLOG_MAGIC  0x4E4A4C47u  /* 'NJLG' */
#define SHMLOG_SLOTS  4096u        /* power of two */
#define SHMLOG_MSG    176u

struct shmlog_slot {
    volatile uint32_t seq;
    uint16_t len;
    uint16_t _pad;
    uint64_t t_ns;                 /* CLOCK_REALTIME, so the daemon prints wall time */
    char     msg[SHMLOG_MSG];
};                                  /* 192 bytes */

struct shmlog_ring {
    uint32_t magic;
    uint32_t nslots;
    volatile uint64_t head;        /* producers claim here   */
    volatile uint64_t tail;        /* consumer-owned         */
    volatile uint64_t dropped;
    uint32_t _pad[10];             /* keep slots cache-aligned */
    struct shmlog_slot slot[SHMLOG_SLOTS];
};

static struct shmlog_ring *ring;

void PIOS_SHMLOG_Init(const char *path)
{
    int fd = open(path ? path : "/dev/shm/ninjapilot-log", O_RDWR | O_CREAT, 0644);

    if (fd < 0) {
        return;                    /* no ring: Printf quietly drops */
    }
    if (ftruncate(fd, sizeof(struct shmlog_ring)) != 0) {
        close(fd);
        return;
    }
    void *m = mmap(NULL, sizeof(struct shmlog_ring), PROT_READ | PROT_WRITE,
                   MAP_SHARED, fd, 0);
    close(fd);
    if (m == MAP_FAILED) {
        return;
    }
    struct shmlog_ring *r = m;
    if (r->magic != SHMLOG_MAGIC || r->nslots != SHMLOG_SLOTS) {
        /* fresh ring; a daemon attaching later replays whatever is here */
        memset(r, 0, sizeof(*r));
        r->nslots = SHMLOG_SLOTS;
        for (uint32_t i = 0; i < SHMLOG_SLOTS; i++) {
            r->slot[i].seq = i;
        }
        __atomic_thread_fence(__ATOMIC_RELEASE);
        r->magic = SHMLOG_MAGIC;
    }
    ring = r;
}

void PIOS_SHMLOG_Printf(const char *fmt, ...)
{
    struct shmlog_ring *r = ring;

    if (!r) {
        return;
    }
    uint64_t pos = __atomic_fetch_add(&r->head, 1, __ATOMIC_RELAXED);
    struct shmlog_slot *s = &r->slot[pos & (SHMLOG_SLOTS - 1u)];
    if (__atomic_load_n(&s->seq, __ATOMIC_ACQUIRE) != (uint32_t)pos) {
        __atomic_fetch_add(&r->dropped, 1, __ATOMIC_RELAXED);
        return;                    /* consumer a lap behind: drop, never wait */
    }
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    s->t_ns = (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;

    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(s->msg, SHMLOG_MSG, fmt, ap);
    va_end(ap);
    if (n < 0) {
        n = 0;
    }
    if (n >= (int)SHMLOG_MSG) {
        n = SHMLOG_MSG - 1;
    }
    s->len = (uint16_t)n;
    __atomic_store_n(&s->seq, (uint32_t)pos + 1u, __ATOMIC_RELEASE);
}
