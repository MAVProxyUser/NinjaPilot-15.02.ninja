/**
 ******************************************************************************
 *
 * @file       pios_sensors_hub.c
 * @author     NinjaPilot, 2026
 * @brief      All realposix sensors, read on a DEDICATED pthread.
 * @see        The GNU Public License (GPL) Version 3
 * @defgroup   PIOS_SENSORS_HUB
 * @{
 *
 * WHY A PTHREAD AND NOT A FreeRTOS TASK - this is the whole point of the file.
 *
 * The FreeRTOS Posix port runs exactly one task at a time, and a blocking
 * syscall is not a FreeRTOS blocking point, so an i2c ioctl inside a FreeRTOS
 * task stalls EVERY task for its duration. At 400 kHz an MPU burst read is
 * ~506 us out of a 2 ms sensor period - 25 % of the budget spent frozen, and
 * it scales linearly with sensor count.
 *
 * Off the FreeRTOS scheduler entirely, it costs nothing. Measured on this
 * board, a 500 Hz RT loop at SCHED_FIFO 50:
 *
 *     quiet bus                              worst 0.200 ms, 0 critical
 *     separate process hammering I2C         worst 0.270 ms, 0 critical
 *
 * So sensor count stops being a scheduling question. The rule that follows:
 * THIS THREAD MUST NEVER TOUCH A FreeRTOS PRIMITIVE - no queues, no
 * semaphores, no vTaskDelay. It publishes through the seqlock below and
 * nothing else. Calling into FreeRTOS from a thread the kernel does not know
 * about corrupts its scheduler state.
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
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* pios.h FIRST - it pulls in pios_config.h, which is where
 * PIOS_INCLUDE_SENSORS_HUB is defined. Testing the guard before including it
 * compiles this whole file to nothing and the link fails with an undefined
 * PIOS_SENSORS_HUB_Init, which reads as a missing file rather than a missing
 * define. */
#include "pios.h"

#ifdef PIOS_INCLUDE_SENSORS_HUB

#include <pios_sensors_hub.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>

/* ------------------------------------------------------------------ i2c-dev */
/* Declared here rather than via <linux/i2c-dev.h>, which collides with
 * <linux/i2c.h> over struct i2c_msg on many toolchains. Stable kernel UAPI. */
#define LINUX_I2C_RDWR 0x0707
#define LINUX_I2C_M_RD 0x0001

struct lin_i2c_msg {
    uint16_t addr;
    uint16_t flags;
    uint16_t len;
    uint8_t *buf;
};
struct lin_i2c_rdwr {
    struct lin_i2c_msg *msgs;
    uint32_t nmsgs;
};

static int i2c_fd = -1;

/**
 * One combined transfer: the kernel issues a repeated START between messages
 * instead of STOP/START. Cheaper than two ioctls and it is what makes reading
 * several devices in one syscall possible.
 */
static int i2c_xfer(struct lin_i2c_msg *msgs, uint32_t n)
{
    struct lin_i2c_rdwr req = { .msgs = msgs, .nmsgs = n };

    return ioctl(i2c_fd, LINUX_I2C_RDWR, &req) < 0 ? -1 : 0;
}

static int i2c_wr8(uint8_t addr, uint8_t reg, uint8_t val)
{
    uint8_t b[2] = { reg, val };
    struct lin_i2c_msg m = { .addr = addr, .flags = 0, .len = 2, .buf = b };

    return i2c_xfer(&m, 1);
}

static int i2c_rd(uint8_t addr, uint8_t reg, uint8_t *dst, uint16_t len)
{
    struct lin_i2c_msg m[2] = {
        { .addr = addr, .flags = 0,              .len = 1,   .buf = &reg },
        { .addr = addr, .flags = LINUX_I2C_M_RD, .len = len, .buf = dst  },
    };

    return i2c_xfer(m, 2);
}

static void msleep(int ms)
{
    struct timespec t = { ms / 1000, (long)(ms % 1000) * 1000000L };

    nanosleep(&t, NULL);
}

static double now_s(void)
{
    struct timespec t;

    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec / 1e9;
}

/* ------------------------------------------------------------ shared state */
/*
 * A seqlock. The writer bumps seq odd, writes, bumps it even. A reader samples
 * seq, copies, re-samples: if it changed or was odd, the copy was torn and it
 * retries. Single writer, wait-free readers, no mutex - so a flight task can
 * never be blocked by the sensor thread, which is the entire point.
 */
static volatile uint32_t hub_seq;
static struct pios_sensors_hub_data hub;

static void hub_publish_begin(void)
{
    __atomic_store_n(&hub_seq, hub_seq + 1, __ATOMIC_RELAXED);
    __atomic_thread_fence(__ATOMIC_RELEASE);
}

static void hub_publish_end(void)
{
    __atomic_thread_fence(__ATOMIC_RELEASE);
    __atomic_store_n(&hub_seq, hub_seq + 1, __ATOMIC_RELAXED);
}

bool PIOS_SENSORS_HUB_Get(struct pios_sensors_hub_data *out)
{
    for (int try = 0; try < 8; try++) {
        uint32_t s0 = __atomic_load_n(&hub_seq, __ATOMIC_RELAXED);
        if (s0 & 1u) {
            continue;              /* writer mid-update */
        }
        __atomic_thread_fence(__ATOMIC_ACQUIRE);
        *out = hub;
        __atomic_thread_fence(__ATOMIC_ACQUIRE);
        if (__atomic_load_n(&hub_seq, __ATOMIC_RELAXED) == s0) {
            return true;
        }
    }
    return false;
}

/* ---------------------------------------------------------------- MPU-9150 */
#define MPU_ADDR        0x68
#define MPU_WHOAMI      0x75
#define MPU_PWR_MGMT_1  0x6B
#define MPU_SMPLRT_DIV  0x19
#define MPU_CONFIG      0x1A
#define MPU_GYRO_CONFIG 0x1B
#define MPU_ACCEL_CONF  0x1C
#define MPU_ACCEL_XOUT  0x3B

/* +/-2000 dps and +/-2 g, per the config written below */
#define MPU_GYRO_LSB_PER_DPS 16.4f
#define MPU_ACCEL_LSB_PER_G  16384.0f
#define STANDARD_G           9.80665f

static bool mpu_init(void)
{
    uint8_t who = 0;

    if (i2c_rd(MPU_ADDR, MPU_WHOAMI, &who, 1) < 0) {
        printf("[hub] MPU: no response at 0x%02X\n", MPU_ADDR);
        return false;
    }
    if (who != 0x68) {
        printf("[hub] MPU: WHO_AM_I 0x%02X, not an MPU-9150/6050\n", who);
        return false;
    }

    /* Reset, then WAIT. The part is not addressable during the reset and a
     * config written too early is silently dropped. */
    i2c_wr8(MPU_ADDR, MPU_PWR_MGMT_1, 0x80);
    msleep(100);

    /* Wake, clock from the X gyro PLL rather than the internal oscillator -
     * the datasheet recommends it and it is measurably more stable. Out of
     * reset the part is ASLEEP; skipping this reads zeros forever. */
    i2c_wr8(MPU_ADDR, MPU_PWR_MGMT_1, 0x01);
    msleep(50);

    i2c_wr8(MPU_ADDR, MPU_CONFIG, 0x03);       /* DLPF ~44 Hz, gyro rate 1 kHz */
    i2c_wr8(MPU_ADDR, MPU_SMPLRT_DIV, 0x01);   /* 1 kHz / (1+1) = 500 Hz       */
    i2c_wr8(MPU_ADDR, MPU_GYRO_CONFIG, 0x18);  /* +/-2000 dps                  */
    i2c_wr8(MPU_ADDR, MPU_ACCEL_CONF, 0x00);   /* +/-2 g                       */
    msleep(20);

    printf("[hub] MPU-9150 ok (500 Hz, +/-2000 dps, +/-2 g)\n");
    return true;
}

static bool mpu_read(float gyro[3], float accel[3], float *temp_c)
{
    uint8_t b[14];

    if (i2c_rd(MPU_ADDR, MPU_ACCEL_XOUT, b, sizeof(b)) < 0) {
        return false;
    }
    int16_t ax = (int16_t)((b[0] << 8) | b[1]);
    int16_t ay = (int16_t)((b[2] << 8) | b[3]);
    int16_t az = (int16_t)((b[4] << 8) | b[5]);
    int16_t t  = (int16_t)((b[6] << 8) | b[7]);
    int16_t gx = (int16_t)((b[8] << 8) | b[9]);
    int16_t gy = (int16_t)((b[10] << 8) | b[11]);
    int16_t gz = (int16_t)((b[12] << 8) | b[13]);

    gyro[0] = gx / MPU_GYRO_LSB_PER_DPS;
    gyro[1] = gy / MPU_GYRO_LSB_PER_DPS;
    gyro[2] = gz / MPU_GYRO_LSB_PER_DPS;
    accel[0] = (ax / MPU_ACCEL_LSB_PER_G) * STANDARD_G;
    accel[1] = (ay / MPU_ACCEL_LSB_PER_G) * STANDARD_G;
    accel[2] = (az / MPU_ACCEL_LSB_PER_G) * STANDARD_G;
    *temp_c  = t / 340.0f + 35.0f;
    return true;
}

/* ------------------------------------------------------------------ BMP388 */
#define BMP_ADDR       0x77
#define BMP_CHIP_ID    0x00
#define BMP_ERR_REG    0x02
#define BMP_DATA_0     0x04
#define BMP_PWR_CTRL   0x1B
#define BMP_OSR        0x1C
#define BMP_ODR        0x1D
#define BMP_CONFIG     0x1F
#define BMP_CALIB      0x31
#define BMP_CMD        0x7E

/* Datasheet-order calibration, already scaled to float ("quantized") exactly
 * as Bosch's BMP3 API does. Getting one shift wrong here yields pressures that
 * look plausible and are wrong by tens of metres, so the divisors are written
 * as explicit powers of two rather than magic constants. */
struct bmp_calib {
    float t1, t2, t3;
    float p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11;
    float t_lin;
};
static struct bmp_calib bmpc;

static bool bmp_init(void)
{
    uint8_t id = 0;

    if (i2c_rd(BMP_ADDR, BMP_CHIP_ID, &id, 1) < 0) {
        printf("[hub] BMP388: no response at 0x%02X\n", BMP_ADDR);
        return false;
    }
    if (id != 0x50) {
        printf("[hub] BMP388: CHIP_ID 0x%02X (0x50 expected; 0x60=BMP390, "
               "0x58=BMP280)\n", id);
        return false;
    }

    i2c_wr8(BMP_ADDR, BMP_CMD, 0xB6);          /* soft reset */
    msleep(10);

    uint8_t c[21];
    if (i2c_rd(BMP_ADDR, BMP_CALIB, c, sizeof(c)) < 0) {
        printf("[hub] BMP388: calibration read failed\n");
        return false;
    }

    uint16_t t1 = (uint16_t)(c[1] << 8 | c[0]);
    uint16_t t2 = (uint16_t)(c[3] << 8 | c[2]);
    int8_t   t3 = (int8_t)c[4];
    int16_t  p1 = (int16_t)(c[6] << 8 | c[5]);
    int16_t  p2 = (int16_t)(c[8] << 8 | c[7]);
    int8_t   p3 = (int8_t)c[9];
    int8_t   p4 = (int8_t)c[10];
    uint16_t p5 = (uint16_t)(c[12] << 8 | c[11]);
    uint16_t p6 = (uint16_t)(c[14] << 8 | c[13]);
    int8_t   p7 = (int8_t)c[15];
    int8_t   p8 = (int8_t)c[16];
    int16_t  p9 = (int16_t)(c[18] << 8 | c[17]);
    int8_t   p10 = (int8_t)c[19];
    int8_t   p11 = (int8_t)c[20];

    bmpc.t1 = (float)t1 / 0.00390625f;          /* 2^-8  */
    bmpc.t2 = (float)t2 / 1073741824.0f;        /* 2^30  */
    bmpc.t3 = (float)t3 / 281474976710656.0f;   /* 2^48  */
    bmpc.p1 = ((float)p1 - 16384.0f) / 1048576.0f;      /* 2^14, 2^20 */
    bmpc.p2 = ((float)p2 - 16384.0f) / 536870912.0f;    /* 2^14, 2^29 */
    bmpc.p3 = (float)p3 / 4294967296.0f;        /* 2^32 */
    bmpc.p4 = (float)p4 / 137438953472.0f;      /* 2^37 */
    bmpc.p5 = (float)p5 / 0.125f;               /* 2^-3 */
    bmpc.p6 = (float)p6 / 64.0f;                /* 2^6  */
    bmpc.p7 = (float)p7 / 256.0f;               /* 2^8  */
    bmpc.p8 = (float)p8 / 32768.0f;             /* 2^15 */
    bmpc.p9 = (float)p9 / 281474976710656.0f;   /* 2^48 */
    bmpc.p10 = (float)p10 / 281474976710656.0f; /* 2^48 */
    bmpc.p11 = (float)p11 / 36893488147419103232.0f; /* 2^65 */

    /* Drone-appropriate: oversample pressure x8 for noise, temperature x1
     * (it only trims the pressure), 50 Hz ODR, IIR coefficient 3 to take the
     * edge off prop wash without adding much group delay. */
    i2c_wr8(BMP_ADDR, BMP_OSR, 0x03);          /* press x8, temp x1 */
    i2c_wr8(BMP_ADDR, BMP_ODR, 0x02);          /* 50 Hz             */
    i2c_wr8(BMP_ADDR, BMP_CONFIG, 0x04);       /* IIR coeff 3       */
    i2c_wr8(BMP_ADDR, BMP_PWR_CTRL, 0x33);     /* press+temp, NORMAL mode */
    msleep(50);

    uint8_t err = 0;
    i2c_rd(BMP_ADDR, BMP_ERR_REG, &err, 1);
    if (err & 0x07) {
        printf("[hub] BMP388: ERR_REG 0x%02X (fatal/cmd/conf)\n", err);
    }
    printf("[hub] BMP388 ok (50 Hz, press x8, IIR 3)\n");
    return true;
}

/* Bosch BMP3 float compensation. Temperature MUST be compensated first - the
 * pressure formula consumes t_lin. */
static float bmp_comp_temp(uint32_t raw)
{
    float d1 = (float)raw - bmpc.t1;
    float d2 = d1 * bmpc.t2;

    bmpc.t_lin = d2 + (d1 * d1) * bmpc.t3;
    return bmpc.t_lin;
}

static float bmp_comp_press(uint32_t raw)
{
    float t = bmpc.t_lin;
    float t2 = t * t;
    float t3 = t2 * t;
    float p = (float)raw;
    float p2 = p * p;
    float p3 = p2 * p;

    float out1 = bmpc.p5 + bmpc.p6 * t + bmpc.p7 * t2 + bmpc.p8 * t3;
    float out2 = p * (bmpc.p1 + bmpc.p2 * t + bmpc.p3 * t2 + bmpc.p4 * t3);
    float out3 = p2 * (bmpc.p9 + bmpc.p10 * t) + p3 * bmpc.p11;

    return out1 + out2 + out3;               /* Pa */
}

static bool bmp_read(float *press_pa, float *temp_c)
{
    uint8_t b[6];

    if (i2c_rd(BMP_ADDR, BMP_DATA_0, b, sizeof(b)) < 0) {
        return false;
    }
    uint32_t rp = (uint32_t)b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16);
    uint32_t rt = (uint32_t)b[3] | ((uint32_t)b[4] << 8) | ((uint32_t)b[5] << 16);

    *temp_c   = bmp_comp_temp(rt);
    *press_pa = bmp_comp_press(rp);
    return true;
}

/* -------------------------------------------------------- DroneCAN over CAN */
#define DC_MSG_MAGNETIC_FIELD 1001   /* determined on the wire, see below */
#define DC_MSG_FIX2           1060

static int can_fd = -1;

static bool can_init(const char *ifname)
{
    struct sockaddr_can addr;
    struct ifreq ifr;

    can_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (can_fd < 0) {
        printf("[hub] CAN: socket failed: %s\n", strerror(errno));
        return false;
    }
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ - 1] = 0;
    if (ioctl(can_fd, SIOCGIFINDEX, &ifr) < 0) {
        printf("[hub] CAN: no interface %s (is it UP? it comes up DOWN after "
               "a reboot)\n", ifname);
        close(can_fd);
        can_fd = -1;
        return false;
    }
    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(can_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        printf("[hub] CAN: bind failed: %s\n", strerror(errno));
        close(can_fd);
        can_fd = -1;
        return false;
    }
    /* Non-blocking: this thread also services I2C and must never park here. */
    fcntl(can_fd, F_SETFL, O_NONBLOCK);
    printf("[hub] CAN %s ok\n", ifname);
    return true;
}

/* half-precision -> float, for DroneCAN's float16 fields */
static float f16_to_f32(uint16_t h)
{
    uint32_t sign = (uint32_t)(h & 0x8000) << 16;
    int exp = (h >> 10) & 0x1F;
    uint32_t man = h & 0x3FF;
    uint32_t bits;

    if (exp == 0) {
        if (!man) {
            bits = sign;                       /* +/-0 */
        } else {
            exp = -1;                          /* subnormal: normalise */
            do {
                exp++;
                man <<= 1;
            } while (!(man & 0x400));
            man &= 0x3FF;
            bits = sign | (uint32_t)(127 - 15 - exp) << 23 | man << 13;
        }
    } else if (exp == 0x1F) {
        bits = sign | 0x7F800000u | man << 13; /* inf / nan */
    } else {
        bits = sign | (uint32_t)(exp - 15 + 127) << 23 | man << 13;
    }
    float f;
    memcpy(&f, &bits, sizeof(f));
    return f;
}

/**
 * Drain whatever CAN has for us. Single-frame messages only - which covers
 * the magnetometer, the one CAN sensor the flight code needs at rate.
 *
 * TWO THINGS HERE ARE EMPIRICAL, NOT FROM A DSDL TABLE, because the table was
 * wrong for this bus:
 *  - the mag arrives as message type 1001
 *  - its payload is float16[3] Gauss at OFFSET 0, with NO sensor_id byte.
 *    Parsing it as uint8 sensor_id + float16[3] gives a constant +17120 Ga on
 *    X and a sensor_id that changes every message.
 * Sanity-check by magnitude: Earth's field is 0.25-0.65 Ga. Anything else
 * means the offset is wrong, not that the sensor is broken.
 */
static void can_poll(void)
{
    struct can_frame f;

    while (can_fd >= 0 && read(can_fd, &f, sizeof(f)) == (ssize_t)sizeof(f)) {
        if (!(f.can_id & CAN_EFF_FLAG) || f.can_dlc < 1) {
            continue;
        }
        uint32_t id = f.can_id & CAN_EFF_MASK;
        uint8_t node = id & 0x7F;
        if (node == 0) {
            continue;         /* anonymous frames use a DIFFERENT id layout */
        }
        uint8_t tail = f.data[f.can_dlc - 1];
        if (!(tail & 0x80)) {
            continue;         /* not the start of a transfer */
        }
        uint16_t mt = (id >> 8) & 0xFFFF;

        if (mt == DC_MSG_MAGNETIC_FIELD && f.can_dlc >= 7) {
            float x = f16_to_f32((uint16_t)(f.data[0] | (f.data[1] << 8)));
            float y = f16_to_f32((uint16_t)(f.data[2] | (f.data[3] << 8)));
            float z = f16_to_f32((uint16_t)(f.data[4] | (f.data[5] << 8)));
            hub_publish_begin();
            hub.mag_ga[0] = x;                 /* Gauss */
            hub.mag_ga[1] = y;
            hub.mag_ga[2] = z;
            hub.mag_node = node;
            hub.mag_time = now_s();
            hub.mag_count++;
            hub_publish_end();
        }
    }
}

/* ------------------------------------------------------------ reader thread */
static pthread_t hub_thread;
static volatile bool hub_run;
static bool have_mpu, have_bmp, have_can;

static void *hub_main(void *arg)
{
    (void)arg;
    double next_imu = now_s();
    double next_baro = now_s();
    const double imu_dt = 1.0 / 500.0;   /* matches PIOS_SENSOR_RATE */
    const double baro_dt = 1.0 / 50.0;

    while (hub_run) {
        double t = now_s();

        if (have_mpu && t >= next_imu) {
            float g[3], a[3], tc;
            if (mpu_read(g, a, &tc)) {
                hub_publish_begin();
                memcpy(hub.gyro_dps, g, sizeof(g));
                memcpy(hub.accel_mss, a, sizeof(a));
                hub.imu_temp_c = tc;
                hub.imu_time = t;
                hub.imu_count++;
                hub_publish_end();
            } else {
                hub.imu_errors++;
            }
            next_imu += imu_dt;
            if (next_imu < t) {
                next_imu = t + imu_dt;   /* fell behind: resync, do not spin */
            }
        }

        if (have_bmp && t >= next_baro) {
            float p, tc;
            if (bmp_read(&p, &tc)) {
                hub_publish_begin();
                hub.press_pa = p;
                hub.baro_temp_c = tc;
                hub.baro_time = t;
                hub.baro_count++;
                hub_publish_end();
            } else {
                hub.baro_errors++;
            }
            next_baro += baro_dt;
            if (next_baro < t) {
                next_baro = t + baro_dt;
            }
        }

        if (have_can) {
            can_poll();
        }

        /* Sleep to the next due event rather than spinning - this thread has
         * a whole core, but burning it would fight the FreeRTOS scheduler
         * thread for the other one. */
        double due = next_imu;
        if (have_bmp && next_baro < due) {
            due = next_baro;
        }
        double sl = due - now_s();
        if (sl > 0.0005) {
            struct timespec ts = { 0, (long)((sl - 0.0002) * 1e9) };
            nanosleep(&ts, NULL);
        }
    }
    return NULL;
}

int32_t PIOS_SENSORS_HUB_Init(const char *i2c_dev, const char *can_if)
{
    memset(&hub, 0, sizeof(hub));

    i2c_fd = open(i2c_dev, O_RDWR);
    if (i2c_fd < 0) {
        printf("[hub] cannot open %s: %s\n", i2c_dev, strerror(errno));
    } else {
        have_mpu = mpu_init();
        have_bmp = bmp_init();
    }
    have_can = can_init(can_if);

    hub.have_imu = have_mpu;
    hub.have_baro = have_bmp;
    hub.have_mag = have_can;

    if (!have_mpu && !have_bmp && !have_can) {
        printf("[hub] NO sensors initialised - refusing to start the thread\n");
        return -1;
    }

    hub_run = true;
    if (pthread_create(&hub_thread, NULL, hub_main, NULL) != 0) {
        printf("[hub] pthread_create failed: %s\n", strerror(errno));
        hub_run = false;
        return -1;
    }
    printf("[hub] reader thread up: imu=%d baro=%d can=%d\n",
           have_mpu, have_bmp, have_can);
    return 0;
}

void PIOS_SENSORS_HUB_Stop(void)
{
    hub_run = false;
    pthread_join(hub_thread, NULL);
    if (i2c_fd >= 0) {
        close(i2c_fd);
    }
    if (can_fd >= 0) {
        close(can_fd);
    }
}

#endif /* PIOS_INCLUDE_SENSORS_HUB */

/**
 * @}
 */
