/* shmlogd - consume the NinjaPilot shared-memory log ring and do the I/O the
 * flight code must never do itself. Separate process on its own core; the
 * ring in /dev/shm SURVIVES a firmware crash, so starting this daemon after
 * a wedge replays the final seconds. Build: cc -O2 -o shmlogd shmlogd.c
 * Run:   ./shmlogd            (follows, like tail -f)
 *        ./shmlogd --dump     (print backlog and exit - post-mortem mode)   */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>

#define MAGIC 0x4E4A4C47u
#define SLOTS 4096u
#define MSG   176u
struct slot { volatile uint32_t seq; uint16_t len, _p; uint64_t t_ns; char msg[MSG]; };
struct ring { uint32_t magic, nslots; volatile uint64_t head, tail, dropped;
              volatile uint32_t generation; uint32_t _pad[9]; struct slot s[SLOTS]; };

int main(int argc, char **argv)
{
    int dump = argc > 1 && !strcmp(argv[1], "--dump");
    int fd = open("/dev/shm/ninjapilot-log", O_RDWR);
    if (fd < 0) { fprintf(stderr, "no ring at /dev/shm/ninjapilot-log (firmware never started?)\n"); return 1; }
    struct ring *r = mmap(NULL, sizeof(struct ring), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    if (r == MAP_FAILED || r->magic != MAGIC) { fprintf(stderr, "bad ring\n"); return 1; }

    /* This is a DROP-ON-FULL ring, not an overwrite ring: the writer never
     * clobbers an unconsumed slot, so the oldest valid record is always at
     * r->tail. The writer's claim loop guarantees head - tail <= SLOTS; if
     * an attached ring violates that it was written by the pre-fix firmware
     * (which advanced head on dropped writes) and is unrecoverable - say so
     * loudly instead of silently printing nothing. */
    if (r->head < r->tail || r->head - r->tail > SLOTS) {
        fprintf(stderr, "!! ring wedged (head=%llu tail=%llu, pre-fix firmware?) - "
                        "restart the firmware to reinitialize it\n",
                (unsigned long long)r->head, (unsigned long long)r->tail);
        return 1;
    }

    uint64_t tail = r->tail;
    uint32_t gen  = r->generation;
    uint64_t last_drop = r->dropped;
    for (;;) {
        /* Firmware restart reinitializes the ring and bumps generation;
         * resync instead of spinning on stale sequence numbers. */
        if (r->generation != gen) {
            gen  = r->generation;
            tail = r->tail;
            last_drop = r->dropped;
            printf("!! ring reinitialized (firmware restart), resyncing\n");
        }
        int idle = 1;
        while (1) {
            struct slot *s = &r->s[tail & (SLOTS - 1u)];
            if (__atomic_load_n(&s->seq, __ATOMIC_ACQUIRE) != (uint32_t)tail + 1u) break;
            time_t sec = (time_t)(s->t_ns / 1000000000ull);
            struct tm tm; localtime_r(&sec, &tm);
            printf("%02d:%02d:%02d.%03u %.*s\n", tm.tm_hour, tm.tm_min, tm.tm_sec,
                   (unsigned)(s->t_ns % 1000000000ull / 1000000ull), (int)s->len, s->msg);
            __atomic_store_n(&s->seq, (uint32_t)(tail + SLOTS), __ATOMIC_RELEASE);
            r->tail = ++tail;
            idle = 0;
        }
        if (r->dropped != last_drop) {
            printf("!! ring dropped %llu records (ring full while unconsumed)\n",
                   (unsigned long long)(r->dropped - last_drop));
            last_drop = r->dropped;
        }
        fflush(stdout);
        if (dump && idle) return 0;
        if (idle) usleep(20000);
    }
}
