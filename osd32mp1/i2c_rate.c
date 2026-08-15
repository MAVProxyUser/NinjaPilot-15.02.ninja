/* What can the flight code ACTUALLY get from the gyro over raw I2C? BOARD ONLY.
 *
 * This deliberately does NOT go through Python, UDP or UAVTalk. Those exist
 * because Gazebo SITL needed an external physics producer. On real hardware
 * the gyro hangs off /dev/i2c-3 and a PIOS driver can read it directly, exactly
 * as PIOS reads an MPU over SPI/I2C on an STM32F4. So the honest question is:
 * how long does one 14-byte burst read of MPU-9150 ACCEL_XOUT..GYRO_ZOUT take,
 * and what rate does that imply?
 *
 * Reference point: OpenPilot on STM32F4 runs PIOS_SENSOR_RATE = 500 Hz (2 ms).
 * Anything comfortably under 2 ms per read means the transport is NOT the limit
 * and the FreeRTOS-on-Linux port can match the STM32 pipeline.
 *
 *   cc -O2 -o i2c_rate i2c_rate.c
 *   ./i2c_rate 3 0x68 5000
 *   chrt -f 50 ./i2c_rate 3 0x68 5000
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sched.h>

#define I2C_SLAVE 0x0703

static int cmp_d(const void *a, const void *b)
{
    double x = *(const double *)a, y = *(const double *)b;
    return (x > y) - (x < y);
}
static double pct(double *s, int n, double p)
{
    int k = (int)(p / 100.0 * (n - 1) + 0.5);
    return s[k < 0 ? 0 : (k >= n ? n - 1 : k)];
}
static double now_ms(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * 1e3 + t.tv_nsec / 1e6;
}

int main(int argc, char **argv)
{
    int bus   = argc > 1 ? atoi(argv[1]) : 3;
    int addr  = argc > 2 ? (int)strtol(argv[2], NULL, 0) : 0x68;
    int iters = argc > 3 ? atoi(argv[3]) : 5000;

    mlockall(MCL_CURRENT | MCL_FUTURE);

    char path[32];
    snprintf(path, sizeof path, "/dev/i2c-%d", bus);
    int fd = open(path, O_RDWR);
    if (fd < 0) { perror(path); return 1; }
    if (ioctl(fd, I2C_SLAVE, addr) < 0) { perror("I2C_SLAVE"); return 1; }

    /* Confirm we are really talking to an MPU before timing anything - a
     * measurement against a part that is not there is worse than none. */
    unsigned char reg = 0x75, who = 0;
    if (write(fd, &reg, 1) != 1 || read(fd, &who, 1) != 1) {
        fprintf(stderr, "no response at 0x%02X on %s\n", addr, path);
        return 1;
    }
    if (who != 0x68) {
        fprintf(stderr, "WHO_AM_I = 0x%02X, not an MPU-9150/6050\n", who);
        return 1;
    }

    double *us = malloc(sizeof(double) * iters);
    unsigned char buf[14];
    /* burst-read ACCEL_XOUT_H .. GYRO_ZOUT_L: the exact transaction a PIOS
     * driver issues once per sensor period */
    for (int i = 0; i < iters; i++) {
        unsigned char r = 0x3B;
        double t0 = now_ms();
        write(fd, &r, 1);
        read(fd, buf, 14);
        us[i] = (now_ms() - t0) * 1000.0;
    }

    double sum = 0, worst = 0;
    for (int i = 0; i < iters; i++) { sum += us[i]; if (us[i] > worst) worst = us[i]; }
    qsort(us, iters, sizeof(double), cmp_d);

    int pol = sched_getscheduler(0);
    printf("=== MPU-9150 14-byte burst read, /dev/i2c-%d @ 0x%02X, %d reads, %s ===\n",
           bus, addr, iters, pol == SCHED_FIFO ? "SCHED_FIFO" : "SCHED_OTHER");
    printf("  mean    %8.1f us\n", sum / iters);
    printf("  median  %8.1f us\n", pct(us, iters, 50));
    printf("  p99     %8.1f us\n", pct(us, iters, 99));
    printf("  p99.9   %8.1f us\n", pct(us, iters, 99.9));
    printf("  WORST   %8.1f us\n", worst);
    printf("  --> back-to-back ceiling %.0f Hz (median), %.0f Hz (worst case)\n",
           1e6 / pct(us, iters, 50), 1e6 / worst);
    printf("  --> at 500 Hz (2000 us budget) this read costs %.1f %% of the period\n",
           pct(us, iters, 50) / 2000.0 * 100.0);
    int over = 0;
    for (int i = 0; i < iters; i++) if (us[i] > 2000.0) over++;
    printf("  reads that alone blew the 2 ms budget: %d (%.3f %%)\n",
           over, 100.0 * over / iters);
    free(us);
    close(fd);
    return 0;
}
