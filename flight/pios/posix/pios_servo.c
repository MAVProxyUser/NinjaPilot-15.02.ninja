/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup   PIOS_SERVO RC Servo Functions
 * @brief Code to do set RC servo output
 * @{
 *
 * @file       pios_servo.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @brief      RC Servo routines (STM32 dependent)
 * @see        The GNU Public License (GPL) Version 3
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
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* Project Includes */
#include "pios.h"

#if defined(PIOS_INCLUDE_SERVO)

#if defined(PIOS_REALPOSIX)

/*
 * Real hardware PWM via Linux /sys/class/pwm on the OSD32MP1-RED.
 *
 * The pads were unlocked in the device tree (osd32mp1/dt-pwm-unlock.sh) and
 * every one of them has been servo-verified on the bench (2026-08-17).
 * Flight output channel -> pad map, motors first so a QuadX mixer lands on
 * the TIM8 bank plus TIM4:
 *
 *   out  timer  chip-chan  pad    where            bank
 *    0   TIM8   pwm0       PI5    RPi pin 12        0
 *    1   TIM8   pwm1       PI6    RPi pin 38        0
 *    2   TIM8   pwm2       PI7    RPi pin 35        0
 *    3   TIM4   pwm1       PD13   RPi pin 32        1
 *    4   TIM4   pwm2       PD14   mikroBUS PWM      1
 *    5   TIM5   pwm1       PH11   RPi pin 31        2
 *    6   TIM3   pwm1       PB5    RPi pin 33        3
 *    7   (none - inert)
 *
 * A bank IS a timer: channels of one timer share a single period register
 * (per-channel duty, per-timer frame rate), so bank update rates map 1:1
 * onto the hardware constraint. pwmchip numbering shifts as chips
 * appear, so chips are found BY ADDRESS via the device symlink, never by
 * pwmchipN. Lazy init from the first actuator call - nothing calls
 * PIOS_Servo_Init on posix targets. The hot path (PIOS_Servo_Set) is
 * snprintf + pwrite only: no stdio streams (see the shmlog priority-
 * inversion post-mortem), no allocation, no locks.
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <pios_shmlog.h>

#define RP_SERVO_CHANNELS 7
#define RP_SERVO_BANKS    4
#define RP_DEFAULT_PERIOD_NS 20000000 /* 50 Hz */

struct rp_servo_chan {
    uint32_t    timer_addr;
    uint8_t     chip_chan;
    uint8_t     bank;
    const char *label;
    char        dir[96];   /* /sys/class/pwm/pwmchipN/pwmM */
    int         duty_fd;   /* held open for the hot path */
    uint32_t    last_ns;
};

static struct rp_servo_chan rp_chan[RP_SERVO_CHANNELS] = {
    { 0x44001000, 0, 0, "TIM8_CH1/PI5/pin12",    "", -1, 0 },
    { 0x44001000, 1, 0, "TIM8_CH2/PI6/pin38",    "", -1, 0 },
    { 0x44001000, 2, 0, "TIM8_CH3/PI7/pin35",    "", -1, 0 },
    { 0x40002000, 1, 1, "TIM4_CH2/PD13/pin32",   "", -1, 0 },
    { 0x40002000, 2, 1, "TIM4_CH3/PD14/mikrobus","", -1, 0 },
    { 0x40003000, 1, 2, "TIM5_CH2/PH11/pin31",   "", -1, 0 },
    { 0x40001000, 1, 3, "TIM3_CH2/PB5/pin33",    "", -1, 0 },
};
static uint32_t rp_bank_period_ns[RP_SERVO_BANKS] = {
    RP_DEFAULT_PERIOD_NS, RP_DEFAULT_PERIOD_NS,
    RP_DEFAULT_PERIOD_NS, RP_DEFAULT_PERIOD_NS
};
static bool rp_initialized = false;

/* one-shot sysfs write helpers - init/rate-change paths only */
static int rp_write_file(const char *dir, const char *file, const char *val)
{
    char path[128];
    snprintf(path, sizeof(path), "%s/%s", dir, file);
    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        return -1;
    }
    int r = write(fd, val, strlen(val));
    close(fd);
    return r < 0 ? -1 : 0;
}

static int rp_write_u32(const char *dir, const char *file, uint32_t v)
{
    char buf[16];
    snprintf(buf, sizeof(buf), "%u", (unsigned)v);
    return rp_write_file(dir, file, buf);
}

/* map timer addresses onto whatever pwmchipN they probed as this boot */
static void rp_find_chips(char chip_dir[RP_SERVO_CHANNELS][64])
{
    DIR *d = opendir("/sys/class/pwm");
    struct dirent *e;

    for (int i = 0; i < RP_SERVO_CHANNELS; i++) {
        chip_dir[i][0] = 0;
    }
    if (!d) {
        return;
    }
    while ((e = readdir(d)) != NULL) {
        if (strncmp(e->d_name, "pwmchip", 7) != 0) {
            continue;
        }
        char link[128], target[256];
        snprintf(link, sizeof(link), "/sys/class/pwm/%s/device", e->d_name);
        ssize_t n = readlink(link, target, sizeof(target) - 1);
        if (n <= 0) {
            continue;
        }
        target[n] = 0;
        for (int i = 0; i < RP_SERVO_CHANNELS; i++) {
            char addr[16];
            snprintf(addr, sizeof(addr), "%x.timer", (unsigned)rp_chan[i].timer_addr);
            if (strstr(target, addr) != NULL) {
                snprintf(chip_dir[i], 64, "/sys/class/pwm/%s", e->d_name);
            }
        }
    }
    closedir(d);
}

static void rp_servo_lazy_init(void)
{
    char chip_dir[RP_SERVO_CHANNELS][64];

    if (rp_initialized) {
        return;
    }
    rp_initialized = true;
    rp_find_chips(chip_dir);

    for (int i = 0; i < RP_SERVO_CHANNELS; i++) {
        struct rp_servo_chan *c = &rp_chan[i];
        if (chip_dir[i][0] == 0) {
            PIOS_SHMLOG_Printf("[servo] out%d %s: pwm chip for %08x MISSING - channel inert",
                               i, c->label, (unsigned)c->timer_addr);
            continue;
        }
        /* export is idempotent-by-outcome: EBUSY just means already exported */
        rp_write_u32(chip_dir[i], "export", c->chip_chan);
        snprintf(c->dir, sizeof(c->dir), "%s/pwm%u", chip_dir[i], c->chip_chan);

        rp_write_u32(c->dir, "enable", 0);
        rp_write_u32(c->dir, "duty_cycle", 0);
        if (rp_write_u32(c->dir, "period", rp_bank_period_ns[c->bank]) < 0) {
            PIOS_SHMLOG_Printf("[servo] out%d %s: period write failed - channel inert", i, c->label);
            continue;
        }
        rp_write_u32(c->dir, "enable", 1);

        char path[128];
        snprintf(path, sizeof(path), "%s/duty_cycle", c->dir);
        c->duty_fd = open(path, O_WRONLY);
        if (c->duty_fd < 0) {
            PIOS_SHMLOG_Printf("[servo] out%d %s: duty open failed - channel inert", i, c->label);
            continue;
        }
        PIOS_SHMLOG_Printf("[servo] out%d -> %s (%s, bank %u, %u ns frame)",
                           i, c->label, c->dir, c->bank, (unsigned)rp_bank_period_ns[c->bank]);
    }
}

void PIOS_Servo_Init(void)
{
    rp_servo_lazy_init();
}

/**
 * Set the servo update rate. A bank is a timer; all channels of the bank
 * change frame rate together (hardware shares the period register).
 */
void PIOS_Servo_SetHz(const uint16_t *speeds, const uint32_t *clock, uint8_t banks)
{
    (void)clock;
    rp_servo_lazy_init();

    for (uint8_t b = 0; b < banks && b < RP_SERVO_BANKS; b++) {
        if (speeds[b] == 0) {
            continue;
        }
        uint32_t period = 1000000000u / speeds[b];
        if (period == rp_bank_period_ns[b]) {
            continue;
        }
        rp_bank_period_ns[b] = period;
        /* shared period: disable + zero every bank channel, then set, then restore */
        for (int i = 0; i < RP_SERVO_CHANNELS; i++) {
            struct rp_servo_chan *c = &rp_chan[i];
            if (c->bank != b || c->duty_fd < 0) {
                continue;
            }
            rp_write_u32(c->dir, "enable", 0);
            rp_write_u32(c->dir, "duty_cycle", 0);
        }
        for (int i = 0; i < RP_SERVO_CHANNELS; i++) {
            struct rp_servo_chan *c = &rp_chan[i];
            if (c->bank != b || c->duty_fd < 0) {
                continue;
            }
            rp_write_u32(c->dir, "period", period);
            uint32_t ns = c->last_ns > period ? period : c->last_ns;
            rp_write_u32(c->dir, "duty_cycle", ns);
            rp_write_u32(c->dir, "enable", 1);
        }
        PIOS_SHMLOG_Printf("[servo] bank %u -> %u Hz (%u ns)", b, speeds[b], (unsigned)period);
    }
}

/**
 * Set servo position - the actuator hot path. Value is the pulse width in
 * microseconds (0 = no pulse). snprintf + pwrite only: no stdio streams.
 */
void PIOS_Servo_Set(uint8_t Servo, uint16_t Position)
{
    if (Servo >= RP_SERVO_CHANNELS) {
        return;
    }
    rp_servo_lazy_init();
    struct rp_servo_chan *c = &rp_chan[Servo];
    if (c->duty_fd < 0) {
        return;
    }
    uint32_t ns = (uint32_t)Position * 1000u;
    if (ns > rp_bank_period_ns[c->bank]) {
        ns = rp_bank_period_ns[c->bank];
    }
    if (ns == c->last_ns) {
        return;
    }
    c->last_ns = ns;
    char buf[16];
    int len = snprintf(buf, sizeof(buf), "%u", (unsigned)ns);
    if (pwrite(c->duty_fd, buf, len, 0) < 0) {
        /* keep flying; the fd stays valid for the next tick */
    }
}

/**
 * Continuous PWM only - nothing pending to flush.
 */
void PIOS_Servo_Update()
{}

/**
 * Only continuous PWM is supported on the Linux pwm sysfs backend;
 * OneShot modes are ignored (the mixer keeps standard 1000-2000 us).
 */
void PIOS_Servo_SetBankMode(uint8_t bank, uint8_t mode)
{
    (void)bank;
    (void)mode;
}

uint8_t PIOS_Servo_GetPinBank(uint8_t pin)
{
    if (pin < RP_SERVO_CHANNELS) {
        return rp_chan[pin].bank;
    }
    return 0;
}

#else /* !PIOS_REALPOSIX - simposix keeps the inert stub */

/* Local Variables */
static volatile uint16_t ServoPosition[PIOS_SERVO_NUM_TIMERS];

/**
 * Initialise Servos
 */
void PIOS_Servo_Init(void)
{}
/**
 * Set the servo update rate (Max 500Hz)
 * \param[in] array of rates in Hz
 * \param[in] array of timer clocks in Hz
 * \param[in] maximum number of banks
 */
void PIOS_Servo_SetHz(const uint16_t *speeds, const uint32_t *clock, uint8_t banks)
{}

/**
 * Set servo position
 * \param[in] Servo Servo number (0-7)
 * \param[in] Position Servo position in milliseconds
 */
void PIOS_Servo_Set(uint8_t Servo, uint16_t Position)
{
#ifndef PIOS_ENABLE_DEBUG_PINS
    /* Make sure servo exists */
    if (Servo < PIOS_SERVO_NUM_OUTPUTS) {
        /* Update the position */
        ServoPosition[Servo] = Position;
    }
#endif // PIOS_ENABLE_DEBUG_PINS
}

/**
 * Flush any pending single-pulse (OneShot/PWMSync) bank updates.
 * There is no real timer hardware to service on posix, so this is a no-op.
 */
void PIOS_Servo_Update()
{}

/**
 * Configure a servo bank's update mode (continuous PWM vs single-pulse).
 * There is no real bank hardware on posix, so this is a no-op.
 */
void PIOS_Servo_SetBankMode(uint8_t bank, uint8_t mode)
{}

/**
 * There is only one simulated output bank on posix, so every pin maps to it.
 */
uint8_t PIOS_Servo_GetPinBank(uint8_t pin)
{
    return 0;
}

#endif /* PIOS_REALPOSIX */

#endif /* if defined(PIOS_INCLUDE_SERVO) */
