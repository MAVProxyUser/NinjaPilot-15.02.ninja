/* Measure scheduling lateness at flight-loop rates. BUILDS AND RUNS ON THE BOARD.
 *
 * The question: FreeRTOS's Posix port makes each task a pthread, so every task
 * wake-up inherits the host scheduler's latency. OpenPilot's
 * stabilizationInnerloopTask runs at PIOS_SENSOR_RATE (500 Hz = 2 ms) and its
 * own watchdog treats 2 missed gyro updates as a warning and 3 as critical.
 * So "3 periods late" is the firmware's own definition of a critical event -
 * that is the threshold reported here.
 *
 * This is C, not Python, on purpose: the flight code is C, and a Python
 * interpreter's own overhead would be indistinguishable from scheduler latency.
 *
 * clock_nanosleep(TIMER_ABSTIME) against CLOCK_MONOTONIC is what a correctly
 * written realtime loop does - it does not accumulate drift, so everything left
 * over IS the host's scheduling error.
 *
 *   cc -O2 -o rt_jitter rt_jitter.c -lpthread
 *   ./rt_jitter 500 20 0            # 500 Hz, 20 s, no extra load
 *   chrt -f 50 ./rt_jitter 500 20 0 # same under SCHED_FIFO
 *   ./rt_jitter 500 20 2            # with 2 busy cores of contention
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>
#include <sys/mman.h>
#include <sys/wait.h>

static int cmp_d(const void *a, const void *b)
{
    double x = *(const double *)a, y = *(const double *)b;
    return (x > y) - (x < y);
}

static double pct(double *sorted, int n, double p)
{
    int k = (int)(p / 100.0 * (n - 1) + 0.5);
    if (k < 0) k = 0;
    if (k >= n) k = n - 1;
    return sorted[k];
}

int main(int argc, char **argv)
{
    double hz      = argc > 1 ? atof(argv[1]) : 500.0;
    double seconds = argc > 2 ? atof(argv[2]) : 20.0;
    int    nload   = argc > 3 ? atoi(argv[3]) : 0;

    /* A page fault in the flight loop is indistinguishable from a scheduling
     * delay, and just as fatal. Real RT code locks its memory down; do the
     * same here so we measure the scheduler and not the pager. */
    int locked = (mlockall(MCL_CURRENT | MCL_FUTURE) == 0);

    pid_t kids[16];
    int nkids = 0;
    for (int i = 0; i < nload && i < 16; i++) {
        pid_t p = fork();
        if (p == 0) {
            /* fork() inherits the scheduling policy. Left alone, a busy child
             * would run at the parent's SCHED_FIFO priority and - FIFO being
             * run-to-completion - starve the very loop we are measuring until
             * the kernel's RT throttle intervened. The realistic case is flight
             * code at RT priority and everything else normal, so force that. */
            struct sched_param z = { .sched_priority = 0 };
            sched_setscheduler(0, SCHED_OTHER, &z);
            struct timespec e;
            clock_gettime(CLOCK_MONOTONIC, &e);
            double end = e.tv_sec + e.tv_nsec / 1e9 + seconds + 2;
            volatile unsigned x = 0;
            for (;;) {
                for (int j = 0; j < 200000; j++) x = x * 1103515245u + 12345u;
                clock_gettime(CLOCK_MONOTONIC, &e);
                if (e.tv_sec + e.tv_nsec / 1e9 > end) _exit(0);
            }
        }
        kids[nkids++] = p;
    }

    long period_ns = (long)(1e9 / hz);
    int  n = (int)(seconds * hz);
    double *late = malloc(sizeof(double) * n);
    if (!late) return 1;

    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    for (int i = 0; i < n; i++) {
        t.tv_nsec += period_ns;
        while (t.tv_nsec >= 1000000000L) { t.tv_nsec -= 1000000000L; t.tv_sec++; }
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        late[i] = ((now.tv_sec - t.tv_sec) * 1e9 + (now.tv_nsec - t.tv_nsec)) / 1e6;
    }

    for (int i = 0; i < nkids; i++) waitpid(kids[i], NULL, 0);

    double period_ms = period_ns / 1e6;
    double sum = 0, worst = 0;
    int over1 = 0, over3 = 0;
    for (int i = 0; i < n; i++) {
        sum += late[i];
        if (late[i] > worst) worst = late[i];
        if (late[i] > period_ms) over1++;
        if (late[i] > 3 * period_ms) over3++;
    }
    qsort(late, n, sizeof(double), cmp_d);

    int pol = sched_getscheduler(0);
    const char *pn = pol == SCHED_FIFO ? "SCHED_FIFO" :
                     pol == SCHED_RR   ? "SCHED_RR"   : "SCHED_OTHER";
    struct sched_param sp;
    sched_getparam(0, &sp);

    printf("=== %.0f Hz (%.2f ms period), %d wake-ups, %s prio %d, load=%d, mlock=%s ===\n",
           hz, period_ms, n, pn, sp.sched_priority, nload, locked ? "yes" : "NO");
    printf("  mean late   %8.3f ms\n", sum / n);
    printf("  median      %8.3f ms\n", pct(late, n, 50));
    printf("  p99         %8.3f ms\n", pct(late, n, 99));
    printf("  p99.9       %8.3f ms\n", pct(late, n, 99.9));
    printf("  WORST       %8.3f ms   = %.1f periods\n", worst, worst / period_ms);
    printf("  late by >1 period : %6d  (%.3f %%)\n", over1, 100.0 * over1 / n);
    printf("  late by >3 periods: %6d  (%.3f %%)   <- firmware calls this critical\n",
           over3, 100.0 * over3 / n);
    free(late);
    return 0;
}
