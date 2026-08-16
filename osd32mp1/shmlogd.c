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
struct ring { uint32_t magic, nslots; volatile uint64_t head, tail, dropped; uint32_t _pad[10]; struct slot s[SLOTS]; };

int main(int argc, char **argv)
{
    int dump = argc > 1 && !strcmp(argv[1], "--dump");
    int fd = open("/dev/shm/ninjapilot-log", O_RDWR);
    if (fd < 0) { fprintf(stderr, "no ring at /dev/shm/ninjapilot-log (firmware never started?)\n"); return 1; }
    struct ring *r = mmap(NULL, sizeof(struct ring), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    if (r == MAP_FAILED || r->magic != MAGIC) { fprintf(stderr, "bad ring\n"); return 1; }

    /* start a full lap back if the backlog is deeper than the ring */
    uint64_t tail = r->tail;
    if (r->head > tail + SLOTS) tail = r->head - SLOTS;

    uint64_t last_drop = r->dropped;
    for (;;) {
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
            printf("!! ring dropped %llu records (consumer too slow)\n",
                   (unsigned long long)(r->dropped - last_drop));
            last_drop = r->dropped;
        }
        fflush(stdout);
        if (dump && idle) return 0;
        if (idle) usleep(20000);
    }
}
