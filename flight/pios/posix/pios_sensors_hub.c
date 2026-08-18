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
#include <signal.h>
#include <sched.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <poll.h>
#include <sys/prctl.h>
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
static uint64_t i2c_busy_ns;      /* hub thread only - no atomics needed */

static int i2c_xfer(struct lin_i2c_msg *msgs, uint32_t n)
{
    struct lin_i2c_rdwr req = { .msgs = msgs, .nmsgs = n };
    struct timespec a, b;

    clock_gettime(CLOCK_MONOTONIC, &a);
    int r = ioctl(i2c_fd, LINUX_I2C_RDWR, &req);
    clock_gettime(CLOCK_MONOTONIC, &b);
    i2c_busy_ns += (uint64_t)(b.tv_sec - a.tv_sec) * 1000000000ull
                   + (uint64_t)(b.tv_nsec - a.tv_nsec);
    return r < 0 ? -1 : 0;
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

/* ------------------------------------------------------------------ BMP280 */
/* The CAN baro's local twin. Registers, calibration layout and float
 * compensation are per the Bosch BMP280 datasheet - distinct from the
 * BMP388 above in every way that matters. Optional: absent is normal. */
#define B280_REG_ID     0xD0
#define B280_REG_CALIB  0x88
#define B280_REG_CONFIG 0xF5
#define B280_REG_CTRL   0xF4
#define B280_REG_DATA   0xF7

static uint8_t b280_addr;
struct b280_calib {
    float T1, T2, T3;
    float P1, P2, P3, P4, P5, P6, P7, P8, P9;
    float t_fine;
};
static struct b280_calib b2c;

static bool bmp280_init(void)
{
    static const uint8_t addrs[2] = { 0x76, 0x77 };
    uint8_t id = 0;

    b280_addr = 0;
    for (unsigned i = 0; i < 2; i++) {
        if (i2c_rd(addrs[i], B280_REG_ID, &id, 1) >= 0 && id == 0x58) {
            b280_addr = addrs[i];
            break;
        }
    }
    if (b280_addr == 0) {
        printf("[hub] BMP280: not present (optional)\n");
        return false;
    }

    uint8_t c[24];
    if (i2c_rd(b280_addr, B280_REG_CALIB, c, sizeof(c)) < 0) {
        printf("[hub] BMP280: calibration read failed\n");
        return false;
    }
    b2c.T1 = (float)(uint16_t)(c[1] << 8 | c[0]);
    b2c.T2 = (float)(int16_t)(c[3] << 8 | c[2]);
    b2c.T3 = (float)(int16_t)(c[5] << 8 | c[4]);
    b2c.P1 = (float)(uint16_t)(c[7] << 8 | c[6]);
    b2c.P2 = (float)(int16_t)(c[9] << 8 | c[8]);
    b2c.P3 = (float)(int16_t)(c[11] << 8 | c[10]);
    b2c.P4 = (float)(int16_t)(c[13] << 8 | c[12]);
    b2c.P5 = (float)(int16_t)(c[15] << 8 | c[14]);
    b2c.P6 = (float)(int16_t)(c[17] << 8 | c[16]);
    b2c.P7 = (float)(int16_t)(c[19] << 8 | c[18]);
    b2c.P8 = (float)(int16_t)(c[21] << 8 | c[20]);
    b2c.P9 = (float)(int16_t)(c[23] << 8 | c[22]);

    /* IIR x4, osrs_t x2 / osrs_p x16, normal mode: ~23 Hz of unique
     * samples, matching the bench characterization (sd 1.5 Pa). */
    i2c_wr8(b280_addr, B280_REG_CONFIG, 0x08);
    i2c_wr8(b280_addr, B280_REG_CTRL, 0x57);
    msleep(50);
    printf("[hub] BMP280 ok at 0x%02X (osrs x16, IIR 4, ~23 Hz)\n", b280_addr);
    return true;
}

static bool bmp280_read(float *press_pa, float *temp_c)
{
    uint8_t d[6];

    if (i2c_rd(b280_addr, B280_REG_DATA, d, sizeof(d)) < 0) {
        return false;
    }
    uint32_t rp = ((uint32_t)d[0] << 12) | ((uint32_t)d[1] << 4) | (d[2] >> 4);
    uint32_t rt = ((uint32_t)d[3] << 12) | ((uint32_t)d[4] << 4) | (d[5] >> 4);

    /* temperature first - pressure consumes t_fine (same rule as the 388) */
    float v1 = ((float)rt / 16384.0f - b2c.T1 / 1024.0f) * b2c.T2;
    float d1 = (float)rt / 131072.0f - b2c.T1 / 8192.0f;
    b2c.t_fine = v1 + d1 * d1 * b2c.T3;
    *temp_c = b2c.t_fine / 5120.0f;

    v1 = b2c.t_fine / 2.0f - 64000.0f;
    float v2 = v1 * v1 * b2c.P6 / 32768.0f;
    v2 = v2 + v1 * b2c.P5 * 2.0f;
    v2 = v2 / 4.0f + b2c.P4 * 65536.0f;
    v1 = (b2c.P3 * v1 * v1 / 524288.0f + b2c.P2 * v1) / 524288.0f;
    v1 = (1.0f + v1 / 32768.0f) * b2c.P1;
    if (v1 == 0.0f) {
        return false;
    }
    float pr = 1048576.0f - (float)rp;
    pr = (pr - v2 / 4096.0f) * 6250.0f / v1;
    v1 = b2c.P9 * pr * pr / 2147483648.0f;
    v2 = pr * b2c.P8 / 32768.0f;
    *press_pa = pr + (v1 + v2 + b2c.P7) / 16.0f;
    return true;
}

/* ---------------------------------------------------------------- HMC5883L */
#define HMC_ADDR   0x1E
#define HMC_CRA    0x00
#define HMC_CRB    0x01
#define HMC_MODE   0x02
#define HMC_DATA   0x03
#define HMC_IDA    0x0A

/* CRB gain 0x20 = +/-1.3 Ga full scale, 1090 LSB/Gauss */
#define HMC_LSB_PER_GAUSS 1090.0f

static bool hmc_init(void)
{
    uint8_t id[3] = { 0, 0, 0 };

    if (i2c_rd(HMC_ADDR, HMC_IDA, id, 3) < 0) {
        printf("[hub] HMC5883L: no response at 0x%02X\n", HMC_ADDR);
        return false;
    }
    /* 'H','4','3' - an address ACK alone proves nothing, and a QMC5883L (a
     * different part with different registers) sits at 0x0D and would not
     * answer here anyway. Identify positively. */
    if (id[0] != 'H' || id[1] != '4' || id[2] != '3') {
        printf("[hub] 0x%02X answered but ID=%c%c%c, not an HMC5883L\n",
               HMC_ADDR, id[0], id[1], id[2]);
        return false;
    }

    i2c_wr8(HMC_ADDR, HMC_CRA, 0x78);   /* 8-sample average, 75 Hz, normal   */
    i2c_wr8(HMC_ADDR, HMC_CRB, 0x20);   /* +/-1.3 Ga                         */
    i2c_wr8(HMC_ADDR, HMC_MODE, 0x00);  /* continuous measurement            */
    msleep(10);

    printf("[hub] HMC5883L ok (75 Hz, +/-1.3 Ga) - SECONDARY mag\n");
    return true;
}

static bool hmc_read(float ga[3])
{
    uint8_t b[6];

    if (i2c_rd(HMC_ADDR, HMC_DATA, b, sizeof(b)) < 0) {
        return false;
    }
    /*
     * REGISTER ORDER IS X, Z, Y - not X, Y, Z. This is the classic HMC5883L
     * trap: read it in the obvious order and you get a magnetometer whose Y
     * and Z are swapped, which does not look like a bug, it looks like a
     * mounting-orientation problem, and it will be "corrected" with a rotation
     * that can never be right.
     */
    int16_t x = (int16_t)((b[0] << 8) | b[1]);
    int16_t z = (int16_t)((b[2] << 8) | b[3]);
    int16_t y = (int16_t)((b[4] << 8) | b[5]);

    /* -4096 is the saturation/overflow flag, not a reading */
    if (x == -4096 || y == -4096 || z == -4096) {
        return false;
    }
    ga[0] = x / HMC_LSB_PER_GAUSS;
    ga[1] = y / HMC_LSB_PER_GAUSS;
    ga[2] = z / HMC_LSB_PER_GAUSS;
    return true;
}

/* -------------------------------------------------------- DroneCAN over CAN */
#define DC_MSG_MAGNETIC_FIELD 1001   /* determined on the wire, see below */
#define DC_MSG_FIX2           1060
#define DC_MSG_NODE_STATUS     341
#define DC_MSG_STATIC_PRESS   1028  /* float32 Pa + float16 variance      */
#define DC_MSG_STATIC_TEMP    1029  /* float16 KELVIN + float16 variance  */
#define DC_MSG_NINJA_GYRO    20500  /* RAW int16[3] LE counts, +/-2000dps FS */
#define DC_MSG_NINJA_ACCEL   20501  /* RAW int16[3] LE counts, +/-2g FS      */
#define DC_MSG_FIX2_REAL      1063  /* the DEPRECATED Fix is 1060; an earlier
                                       bus table here had the two swapped */
#define DC_MSG_GNSS_STATUS   20003  /* ardupilot.gnss.Status */

static int can_fd = -1;
static uint64_t can_bits;   /* hub thread only */
static uint64_t can_frames; /* hub thread only */

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

static float f16_to_f32(uint16_t h);   /* defined below */

/* ------------------------- DroneCAN v0 bit-level decode (per libcanard) --
 * The wire packs each field's bits MSB-first per byte into the stream; a
 * partial tail byte is right-aligned; assembled bytes are LITTLE-endian.
 * Ported from canardDecodeScalar/copyBitArray semantics (libcanard, MIT) -
 * NOT derived from reasoning, which is how the mag briefly read 17120 Ga. */
static uint64_t dc_bits(const uint8_t *buf, uint32_t bit_ofs, uint8_t nbits)
{
    uint8_t bytes[8] = { 0 };
    uint8_t nbytes = (uint8_t)((nbits + 7u) / 8u);

    for (uint8_t i = 0; i < nbytes; i++) {
        uint8_t want = (uint8_t)((nbits - i * 8u) >= 8u ? 8u : (nbits - i * 8u));
        uint8_t v = 0;
        for (uint8_t b = 0; b < want; b++) {
            uint32_t sbit = bit_ofs + i * 8u + b;
            uint8_t bit = (uint8_t)((buf[sbit / 8u] >> (7u - (sbit % 8u))) & 1u);
            v = (uint8_t)((v << 1) | bit);
        }
        bytes[i] = v;              /* tail partial byte lands right-aligned */
    }
    uint64_t out = 0;
    for (uint8_t i = 0; i < nbytes; i++) {
        out |= (uint64_t)bytes[i] << (8u * i);      /* little-endian */
    }
    return out;
}

static int64_t dc_sbits(const uint8_t *buf, uint32_t bit_ofs, uint8_t nbits)
{
    uint64_t u = dc_bits(buf, bit_ofs, nbits);

    if (u & (1ull << (nbits - 1u))) {
        u |= ~((1ull << nbits) - 1ull);             /* sign-extend */
    }
    return (int64_t)u;
}

static float dc_f32(const uint8_t *buf, uint32_t bit_ofs)
{
    uint32_t u = (uint32_t)dc_bits(buf, bit_ofs, 32);
    float f;

    memcpy(&f, &u, 4);
    return f;
}

/* ---- Fix2 multi-frame reassembly (node 124). Tail byte: bit7 start,
 * bit6 end, bit5 toggle, bits 0-4 transfer id. Multi-frame payloads carry a
 * 2-byte transfer CRC first; validating it needs the DSDL 64-bit signature,
 * so acceptance here rests on the structural field checks below instead. */
struct dc_reasm {
    uint8_t buf[128];
    uint8_t len;
    uint8_t tid;
    uint8_t toggle;
    bool    active;
};
static struct dc_reasm fix2_rx, aux_rx;

static void fix2_decode(const uint8_t *p, uint8_t n);
static void aux_decode(const uint8_t *p, uint8_t n);

/* Returns payload length (CRC prefix stripped) when a transfer completes,
 * 0 otherwise. Same tail-byte protocol for every multi-frame v0 message. */
static uint8_t dc_reasm_feed(struct dc_reasm *rx, const uint8_t *data, uint8_t dlc,
                             const uint8_t **payload)
{
    uint8_t tail = data[dlc - 1];
    uint8_t sot = (uint8_t)(tail >> 7) & 1u, eot = (uint8_t)(tail >> 6) & 1u;
    uint8_t tog = (uint8_t)(tail >> 5) & 1u, tid = tail & 0x1Fu;
    uint8_t nb = (uint8_t)(dlc - 1);

    if (sot && eot) {                              /* single-frame: no CRC */
        *payload = data;
        return nb;
    }
    if (sot) {
        rx->active = true;
        rx->len    = 0;
        rx->tid    = tid;
        rx->toggle = 0;
        if (tog != 0) {
            rx->active = false;
            hub.gps_bad++;
            return 0;
        }
    } else if (!rx->active || tid != rx->tid || tog != (rx->toggle ^ 1u)) {
        rx->active = false;                        /* lost/foreign frame */
        hub.gps_bad++;
        return 0;
    }
    if (!sot) {
        rx->toggle = tog;
    }
    if (rx->len + nb > sizeof(rx->buf)) {
        rx->active = false;
        hub.gps_bad++;
        return 0;
    }
    memcpy(&rx->buf[rx->len], data, nb);
    rx->len += nb;
    if (eot) {
        rx->active = false;
        if (rx->len > 2) {
            *payload = &rx->buf[2];
            return (uint8_t)(rx->len - 2);
        }
    }
    return 0;
}

/* uavcan.equipment.gnss.Auxiliary: 7x float16 DOPs, then sats. Byte-aligned
 * through the floats, so offsets are trivially checkable. */
static void aux_decode(const uint8_t *p, uint8_t n)
{
    if (n < 16) {
        return;
    }
    float hdop = f16_to_f32((uint16_t)dc_bits(p, 32, 16));   /* after gdop,pdop */
    float vdop = f16_to_f32((uint16_t)dc_bits(p, 48, 16));
    uint8_t vis  = (uint8_t)dc_bits(p, 112, 7);
    uint8_t used = (uint8_t)dc_bits(p, 119, 6);

    if (vis > 100) {
        return;                                    /* offset suspect: reject */
    }
    hub_publish_begin();
    hub.gps_hdop = hdop;
    hub.gps_vdop = vdop;
    hub.gps_sats_visible = vis;
    hub.gps_aux_count++;
    hub_publish_end();

    if ((hub.gps_aux_count % 25u) == 1u) {
        /* integers only - the %u-after-doubles varargs artifact is unresolved */
        PIOS_SHMLOG_Printf("[hub-aux] sats_visible=%u sats_used=%u hdop_c=%d vdop_c=%d",
                           vis, used, (int)(hdop * 100.0f), (int)(vdop * 100.0f));
    }
}

/* uavcan.equipment.gnss.Fix2, field-for-field from 1063.Fix2.uavcan */
static void fix2_decode(const uint8_t *p, uint8_t n)
{
    if (n < 48) {                                  /* fixed part = 378 bits */
        hub.gps_bad++;
        return;
    }
    uint32_t o = 0;
    o += 56;                                       /* timestamp.usec        */
    uint64_t utc_usec = dc_bits(p, o, 56); o += 56; /* gnss_timestamp.usec  */
    uint8_t tstd = (uint8_t)dc_bits(p, o, 3); o += 3;
    o += 13;                                       /* void13                */
    uint8_t leap = (uint8_t)dc_bits(p, o, 8); o += 8;
    int64_t lon8 = dc_sbits(p, o, 37); o += 37;
    int64_t lat8 = dc_sbits(p, o, 37); o += 37;
    o += 27;                                       /* height_ellipsoid_mm   */
    int64_t hmsl = dc_sbits(p, o, 27); o += 27;
    float vn = dc_f32(p, o); o += 32;
    float ve = dc_f32(p, o); o += 32;
    float vd = dc_f32(p, o); o += 32;
    uint8_t sats = (uint8_t)dc_bits(p, o, 6); o += 6;
    uint8_t fix  = (uint8_t)dc_bits(p, o, 2); o += 2;
    o += 4 + 6;                                    /* mode, sub_mode        */
    uint8_t covn = (uint8_t)dc_bits(p, o, 6); o += 6;
    float pdop = 0.0f;
    if ((o + covn * 16u + 16u) <= (uint32_t)n * 8u) {
        o += covn * 16u;
        pdop = f16_to_f32((uint16_t)dc_bits(p, o, 16));
    }

    /* Structural sanity carries the validation burden indoors (lat/lon of
     * zero cannot distinguish right offsets from wrong ones): the enums must
     * be legal, sats must be physical, leap seconds 0 or ~18. Reject rather
     * than publish plausible garbage. */
    if (tstd > 3 || sats > 40 || (leap != 0 && (leap < 10 || leap > 30))) {
        hub.gps_bad++;
        if (hub.gps_bad <= 3) {
            PIOS_SHMLOG_Printf("[hub-gps] REJECT #%lu tstd=%u sats=%u leap=%u "
                               "len=%u - bit offsets suspect",
                               (unsigned long)hub.gps_bad, tstd, sats, leap, n);
        }
        return;
    }

    hub_publish_begin();
    hub.gps_lat_1e7   = (int32_t)(lat8 / 10);
    hub.gps_lon_1e7   = (int32_t)(lon8 / 10);
    hub.gps_alt_msl_m = (float)hmsl / 1000.0f;
    hub.gps_ned_vel[0] = vn;
    hub.gps_ned_vel[1] = ve;
    hub.gps_ned_vel[2] = vd;
    hub.gps_pdop = pdop;
    hub.gps_sats = sats;
    hub.gps_fix  = fix;
    hub.gps_time = now_s();
    /* plausible UTC only: 2020-01-01..2100-01-01 in usec - the receiver
     * reports 0 (or garbage-free zeros) until it has time from the sky */
    hub.gps_utc_usec = (utc_usec > 1577836800000000ull
                        && utc_usec < 4102444800000000ull) ? utc_usec : 0;
    hub.gps_count++;
    hub_publish_end();

    if ((hub.gps_count % 25u) == 1u) {             /* one line every ~5 s */
        PIOS_SHMLOG_Printf("[hub-gps] fix=%u sats=%u lat=%ld lon=%ld alt=%.1f "
                           "pdop=%.1f tstd=%u leap=%u bad=%lu",
                           fix, sats, (long)hub.gps_lat_1e7, (long)hub.gps_lon_1e7,
                           (double)hub.gps_alt_msl_m, (double)pdop, tstd, leap,
                           (unsigned long)hub.gps_bad);
    }
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
        can_bits += 67u + 8u * f.can_dlc;   /* nominal ext-frame cost */
        can_frames++;
        if (!(f.can_id & CAN_EFF_FLAG) || f.can_dlc < 1) {
            continue;
        }
        uint32_t id = f.can_id & CAN_EFF_MASK;
        uint8_t node = id & 0x7F;
        if (node == 0) {
            continue;         /* anonymous frames use a DIFFERENT id layout */
        }
        uint16_t mt = (id >> 8) & 0xFFFF;

        /* Fix2 is a 10-frame transfer: the reassembler needs EVERY frame,
         * so dispatch it BEFORE the start-of-transfer filter below. Feeding
         * it only start frames (the first version of this code) means
         * reassembly silently never completes. */
        if (mt == DC_MSG_FIX2_REAL || mt == 1061) {
            const uint8_t *pl = NULL;
            struct dc_reasm *rx = (mt == DC_MSG_FIX2_REAL) ? &fix2_rx : &aux_rx;
            uint8_t n = dc_reasm_feed(rx, f.data, f.can_dlc, &pl);
            if (n > 0) {
                if (mt == DC_MSG_FIX2_REAL) {
                    fix2_decode(pl, n);
                } else {
                    aux_decode(pl, n);
                }
            }
            continue;
        }

        uint8_t tail = f.data[f.can_dlc - 1];
        if (!(tail & 0x80)) {
            continue;         /* not the start of a transfer */
        }

        if (mt == DC_MSG_NINJA_GYRO && f.can_dlc >= 7) {
            /* Compact IMU stream from the L431's second MPU-9150. Single
             * frame by design, so there is no reassembly to fail. The node
             * sends gyro then accel back to back; the ACCEL message is the
             * pair's completion marker and owns the counter. */
            int16_t r[3];
            memcpy(r, f.data, 6);
            hub_publish_begin();
            /* raw-proxy contract v2: the node ships the MPU's registers
             * untouched (no cal, no filter, no conversion - by design).
             * +/-2000 dps FS = 16.4 LSB/dps. WE own interpretation. */
            hub.imu2_gyro_dps[0] = (float)r[0] * (1.0f / 16.4f);
            hub.imu2_gyro_dps[1] = (float)r[1] * (1.0f / 16.4f);
            hub.imu2_gyro_dps[2] = (float)r[2] * (1.0f / 16.4f);
            hub_publish_end();
            continue;
        }

        if (mt == DC_MSG_NINJA_ACCEL && f.can_dlc >= 7) {
            int16_t r[3];
            memcpy(r, f.data, 6);
            hub_publish_begin();
            /* +/-2 g FS = 16384 LSB/g */
            hub.imu2_accel_mss[0] = (float)r[0] * (9.80665f / 16384.0f);
            hub.imu2_accel_mss[1] = (float)r[1] * (9.80665f / 16384.0f);
            hub.imu2_accel_mss[2] = (float)r[2] * (9.80665f / 16384.0f);
            hub.imu2_time  = now_s();
            hub.imu2_count++;
            hub.have_imu2  = true;
            hub_publish_end();
            continue;
        }

        if (mt == DC_MSG_STATIC_PRESS && f.can_dlc >= 5) {
            /* BMP388 now lives on the L431 (custom hwdef, declared probe);
             * byte-aligned float32 pascals, single frame. Reuses the same
             * hub fields the local-I2C baro used, so sensors.c publishes
             * BaroSensor with no changes. */
            float pa;
            memcpy(&pa, &f.data[0], 4);
            if (pa > 30000.0f && pa < 120000.0f) {      /* 3-12 km sanity */
                hub_publish_begin();
                hub.press_pa = pa;
                hub.baro_time = now_s();
                hub.baro_count++;
                hub.have_baro = true;
                hub_publish_end();
            } else {
                hub.baro_errors++;
            }
            continue;
        }

        if (mt == DC_MSG_STATIC_TEMP && f.can_dlc >= 3) {
            float k = f16_to_f32((uint16_t)(f.data[0] | (f.data[1] << 8)));
            if (k > 200.0f && k < 350.0f) {
                hub_publish_begin();
                hub.baro_temp_c = k - 273.15f;
                hub_publish_end();
            }
            continue;
        }

        if (mt == DC_MSG_NODE_STATUS && f.can_dlc >= 7) {
            /*
             * uavcan.protocol.NodeStatus, 7 bytes:
             *   uint32 uptime_sec           bytes 0-3, little endian
             *   uint2  health               byte 4, bits 0-1
             *   uint3  mode                 byte 4, bits 2-4
             *   uint3  sub_mode             byte 4, bits 5-7
             *   uint16 vendor_status_code   bytes 5-6, little endian
             *
             * This is the bus's own liveness signal and the cheapest real
             * health check available: a node that stops sending it is gone,
             * and one reporting health != OK is telling you so before its
             * data goes wrong. last_seen is what makes "gone" detectable -
             * a silent node publishes nothing at all, including nothing bad.
             */
            uint32_t up = (uint32_t)f.data[0] | ((uint32_t)f.data[1] << 8)
                        | ((uint32_t)f.data[2] << 16) | ((uint32_t)f.data[3] << 24);
            uint8_t hm = f.data[4];
            uint16_t vc = (uint16_t)(f.data[5] | (f.data[6] << 8));

            hub_publish_begin();
            struct pios_hub_node *n = NULL;
            for (uint8_t i = 0; i < hub.node_count; i++) {
                if (hub.nodes[i].node_id == node) {
                    n = &hub.nodes[i];
                    break;
                }
            }
            if (!n && hub.node_count < PIOS_HUB_MAX_NODES) {
                n = &hub.nodes[hub.node_count++];
                n->node_id = node;
            }
            if (n) {
                n->uptime_sec  = up;
                n->health      = hm & 0x03;
                n->mode        = (hm >> 2) & 0x07;
                n->sub_mode    = (hm >> 5) & 0x07;
                n->vendor_code = vc;
                n->last_seen   = now_s();
                n->count++;
            }
            hub_publish_end();
            continue;
        }

        if (mt == DC_MSG_GNSS_STATUS && f.can_dlc >= 8) {
            /*
             * ardupilot.gnss.Status, confirmed against the DSDL at
             * dronecan/DSDL ardupilot/gnss/20003.Status.uavcan:
             *
             *     uint32 error_codes      bits  0-31
             *     bool   healthy          bit   32
             *     uint23 status           bits 33-55       = 56 bits = 7 bytes
             *
             * DroneCAN packs LSB-first, so `healthy` is bit 0 of byte 4 and
             * `status` is the remaining 7 bits of byte 4 plus bytes 5-6.
             *
             * STATUS_ARMABLE is the one that matters for flight safety: the
             * GPS node's own judgement that the system is in a fit state to
             * arm. Observed indoors with no fix: error_codes=0, healthy=1,
             * ARMABLE=0 - i.e. healthy hardware correctly refusing to bless
             * an arm. Do NOT treat healthy alone as permission to fly.
             *
             * The DSDL itself says the remaining status bits are the
             * application's to interpret, and bit 6 is set here with no
             * documented meaning - so the full field is kept raw alongside
             * the two named flags rather than discarded.
             */
            uint32_t ec = (uint32_t)f.data[0] | ((uint32_t)f.data[1] << 8)
                        | ((uint32_t)f.data[2] << 16) | ((uint32_t)f.data[3] << 24);
            uint32_t st = ((uint32_t)f.data[4] >> 1)
                        | ((uint32_t)f.data[5] << 7) | ((uint32_t)f.data[6] << 15);

            hub_publish_begin();
            hub.gnss_error_codes = ec;
            hub.gnss_healthy     = (f.data[4] & 0x01) != 0;
            hub.gnss_status_raw  = st & 0x7FFFFF;
            hub.gnss_logging     = (st & 1u) != 0;   /* STATUS_LOGGING = 1 */
            hub.gnss_armable     = (st & 2u) != 0;   /* STATUS_ARMABLE = 2 */
            hub.gnss_node        = node;
            hub.gnss_time        = now_s();
            hub.gnss_count++;
            hub_publish_end();
            continue;
        }

        if (mt == DC_MSG_MAGNETIC_FIELD && f.can_dlc >= 7) {
            /* TWO nodes broadcast 1001 now: node 125's RM3100 (calibrated,
             * the flight mag) and node 124's QMC5883P (M9N module, raw).
             * They MUST stay separate - interleaving them corrupts heading. */
            float x = f16_to_f32((uint16_t)(f.data[0] | (f.data[1] << 8)));
            float y = f16_to_f32((uint16_t)(f.data[2] | (f.data[3] << 8)));
            float z = f16_to_f32((uint16_t)(f.data[4] | (f.data[5] << 8)));
            hub_publish_begin();
            if (node == 125) {
                hub.mag_ga[0] = x;             /* Gauss */
                hub.mag_ga[1] = y;
                hub.mag_ga[2] = z;
                hub.mag_node = node;
                hub.mag_time = now_s();
                hub.mag_count++;
            } else {
                hub.qmc_ga[0] = x;
                hub.qmc_ga[1] = y;
                hub.qmc_ga[2] = z;
                hub.qmc_node = node;
                hub.qmc_time = now_s();
                hub.qmc_count++;
            }
            hub_publish_end();
        }
    }
}

/* ------------------------------------------------------------ reader thread */
static pthread_t hub_thread;
static volatile bool hub_run;
static bool have_mpu, have_bmp, have_can, have_hmc;
static bool have_b280;

static void *hub_main(void *arg)
{
    (void)arg;
    prctl(PR_SET_NAME, "sensorhub", 0, 0, 0);
    double next_imu = now_s();
    double next_baro = now_s();
    double next_hmc = now_s();
    double next_b280 = now_s();
    const double hmc_dt = 1.0 / 50.0;
    const double b280_dt = 1.0 / 25.0;
    double next_health = now_s() + 10.0;
    double next_canload = now_s() + 1.0;
    uint64_t canload_prev_bits = 0;
    struct pios_sensors_hub_data prev;
    memset(&prev, 0, sizeof(prev));
    uint64_t prev_i2c_ns = 0, prev_can_bits = 0;
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

        if (have_b280 && t >= next_b280) {
            float p, tc;
            if (bmp280_read(&p, &tc) && p > 30000.0f && p < 120000.0f) {
                hub_publish_begin();
                hub.baro2_press_pa = p;
                hub.baro2_temp_c = tc;
                hub.baro2_time = t;
                hub.baro2_count++;
                hub.have_baro2 = true;
                hub_publish_end();
            }
            next_b280 += b280_dt;
            if (next_b280 < t) {
                next_b280 = t + b280_dt;
            }
        }

        if (have_hmc && t >= next_hmc) {
            float m[3];
            if (hmc_read(m)) {
                hub_publish_begin();
                memcpy(hub.mag2_ga, m, sizeof(m));
                hub.mag2_time = t;
                hub.mag2_count++;
                hub_publish_end();
            } else {
                hub.mag2_errors++;
            }
            next_hmc += hmc_dt;
            if (next_hmc < t) {
                next_hmc = t + hmc_dt;
            }
        }

        if (have_can) {
            can_poll();
        }

        if (t >= next_canload) {
            /* rolling 1 s bus utilisation for the CAN health tile; permille
             * of the 1 Mbit wire, same frame-size accounting as the 10 s
             * hub-health print */
            next_canload += 1.0;
            if (next_canload < t) {
                next_canload = t + 1.0;
            }
            bool vbus = false, pwr_ok = false;
            {
                /* DWC2 GOTGCTL bit 19 = B-session valid = VBUS present */
                FILE *fp = fopen("/sys/kernel/debug/usb/49000000.usb-otg/regdump", "r");
                if (fp) {
                    char line[96];
                    while (fgets(line, sizeof(line), fp)) {
                        unsigned long v;
                        if (sscanf(line, "GOTGCTL = %lx", &v) == 1) {
                            vbus   = (v >> 19) & 1u;
                            pwr_ok = true;
                            break;
                        }
                    }
                    fclose(fp);
                }
            }
            hub_publish_begin();
            hub.can_load_pm  = (uint32_t)((can_bits - canload_prev_bits) / 1000u);
            hub.can_frames   = (uint32_t)can_frames;
            hub.can_seen     = can_frames > 0;
            hub.vbus_present = vbus;
            hub.have_pwr     = pwr_ok;
            hub_publish_end();
            canload_prev_bits = can_bits;
        }

        if (t >= next_health) {
            next_health += 10.0;
            /*
             * Flight-readiness checkpoint, every 10 s. Counts are DELTAS over
             * the interval, so rate = count / 10. i2c_pm / can_pm are bus
             * utilisation in PERMILLE, from measured transfer wall-time and
             * actual frame sizes - not datasheet arithmetic. Integer-only:
             * the %u-after-doubles varargs artifact is still open.
             */
            PIOS_SHMLOG_Printf("[hub-health] imu=%lu imu2=%lu baro=%lu b2=%lu hmc=%lu mag=%lu qmc=%lu "
                               "fix2=%lu aux=%lu ierr=%lu berr=%lu gbad=%lu "
                               "i2c_pm=%lu can_pm=%lu",
                               (unsigned long)(hub.imu_count - prev.imu_count),
                               (unsigned long)(hub.imu2_count - prev.imu2_count),
                               (unsigned long)(hub.baro_count - prev.baro_count),
                               (unsigned long)(hub.baro2_count - prev.baro2_count),
                               (unsigned long)(hub.mag2_count - prev.mag2_count),
                               (unsigned long)(hub.mag_count - prev.mag_count),
                               (unsigned long)(hub.qmc_count - prev.qmc_count),
                               (unsigned long)(hub.gps_count - prev.gps_count),
                               (unsigned long)(hub.gps_aux_count - prev.gps_aux_count),
                               (unsigned long)(hub.imu_errors - prev.imu_errors),
                               (unsigned long)(hub.baro_errors - prev.baro_errors),
                               (unsigned long)(hub.gps_bad - prev.gps_bad),
                               (unsigned long)((i2c_busy_ns - prev_i2c_ns) / 10000000ull),
                               (unsigned long)((can_bits - prev_can_bits) / 10000ull));
            prev = hub;
            prev_i2c_ns = i2c_busy_ns;
            prev_can_bits = can_bits;
        }

        /* Sleep to the next due event rather than spinning - this thread
         * shares two cores with the whole flight stack.
         *
         * TRAP (found burning 50% of a core): next_imu only advances inside
         * the have_mpu branch, so with the local IMU absent it froze in the
         * past, `due - now` went permanently negative, and this loop
         * busy-polled the CAN socket at ~3200 read()/s (thread shows as
         * "init" in ps - it inherits the spawning task's name).
         *
         * Now: the next due event is computed from ENABLED sources only,
         * and when CAN is up we block in poll() on the socket - woken the
         * moment a frame lands (same delivery latency as the spin, none of
         * the burn), with the schedule as timeout. */
        double due = now_s() + 0.01;                 /* 10ms housekeeping cap */
        if (have_mpu && next_imu < due) {
            due = next_imu;
        }
        if (have_bmp && next_baro < due) {
            due = next_baro;
        }
        if (have_b280 && next_b280 < due) {
            due = next_b280;
        }
        if (have_hmc && next_hmc < due) {
            due = next_hmc;
        }
        double sl = due - now_s();
        if (sl > 0.0005) {
            if (have_can && can_fd >= 0) {
                struct pollfd pfd;
                pfd.fd     = can_fd;
                pfd.events = POLLIN;
                poll(&pfd, 1, (int)(sl * 1000.0));
            } else {
                struct timespec ts = { 0, (long)((sl - 0.0002) * 1e9) };
                nanosleep(&ts, NULL);
            }
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
        have_b280 = bmp280_init();
        have_hmc = hmc_init();
    }
    have_can = can_init(can_if);

    hub.have_imu = have_mpu;
    hub.have_baro = have_bmp;
    hub.have_mag = have_can;
    hub.have_mag2 = have_hmc;

    if (!have_mpu && !have_bmp && !have_can && !have_hmc) {
        printf("[hub] NO sensors initialised - refusing to start the thread\n");
        return -1;
    }

    hub_run = true;

    /*
     * Block signals in the reader thread. The FreeRTOS Posix port is
     * signal-driven (its scheduler parks in sigtimedwait), and a
     * process-directed signal goes to ANY thread not blocking it, so a
     * non-FreeRTOS thread should never be eligible. This is hygiene rather
     * than a fix for a specific observed bug - the hang that motivated it
     * turned out to be the SCHED_FIFO inheritance handled below.
     *
     * The FreeRTOS Posix port is SIGNAL-DRIVEN: its scheduler thread parks in
     * sigtimedwait() and is woken by the tick signal. A process-directed
     * signal is delivered to ANY thread that does not block it, so a pthread
     * created here - before vTaskStartScheduler(), with an empty mask -
     * happily eats the scheduler's tick.
     *
     * Mask BEFORE pthread_create so the child inherits it, then restore.
     */
    sigset_t all_sigs, old_sigs;
    sigfillset(&all_sigs);
    pthread_sigmask(SIG_SETMASK, &all_sigs, &old_sigs);

    /*
     * SET THE SCHEDULING POLICY EXPLICITLY - inheriting it is what broke this.
     *
     * pthread_create inherits the CREATOR's policy by default. Launch the
     * firmware under `chrt -f 50` (which is exactly what makes the flight loop
     * meet its deadlines) and this reader thread silently comes up at
     * SCHED_FIFO 50 too - equal priority to every FreeRTOS thread. FIFO is
     * run-to-completion, so a thread polling I2C at 500 Hz then starves them.
     *
     * The failure does NOT look like a crash: the process stays up, this
     * thread keeps reading sensors, the socket threads and telemetry keep
     * moving, but every FreeRTOS TASK stops - IDLE included - and the
     * scheduler parks at 0 % CPU. Measured, 5 s samples:
     *
     *     simposix, FIFO 50            IDLE 385 ticks, Sensors 18, Ca 32, wd 2/s
     *     realposix, FIFO 50 inherited IDLE   0,       Sensors  0, Ca  0, wd SILENT
     *     realposix, SCHED_OTHER       IDLE   -        Sensors  2, Ca  5, wd 1.3/s
     *
     * So: PTHREAD_EXPLICIT_SCHED, and one band BELOW the flight code. The
     * reader is I/O bound and blocks on ioctl anyway, so it gets all the CPU
     * it needs whenever the flight loop is not running - and can never
     * preempt it. This is the same trap already recorded in
     * osd32mp1/CLAUDE.md for fork() and SCHED_FIFO.
     */
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    int pol = sched_getscheduler(0);
    if (pol == SCHED_FIFO || pol == SCHED_RR) {
        struct sched_param pp;
        sched_getparam(0, &pp);
        int prio = pp.sched_priority - 10;
        int lo = sched_get_priority_min(pol);
        if (prio < lo) {
            prio = lo;
        }
        struct sched_param cp = { .sched_priority = prio };
        pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
        pthread_attr_setschedpolicy(&attr, pol);
        pthread_attr_setschedparam(&attr, &cp);
        printf("[hub] reader at RT priority %d (flight code is at %d)\n",
               prio, pp.sched_priority);
    } else {
        struct sched_param cp = { .sched_priority = 0 };
        pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
        pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
        pthread_attr_setschedparam(&attr, &cp);
    }

    int rc = pthread_create(&hub_thread, &attr, hub_main, NULL);

    pthread_attr_destroy(&attr);
    pthread_sigmask(SIG_SETMASK, &old_sigs, NULL);

    if (rc != 0) {
        printf("[hub] pthread_create failed: %s\n", strerror(rc));
        hub_run = false;
        return -1;
    }
    printf("[hub] reader thread up: imu=%d baro=%d can=%d hmc=%d\n",
           have_mpu, have_bmp, have_can, have_hmc);
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
