/**
 ******************************************************************************
 *
 * @file       pios_esp32_priv.h
 * @author     NinjaPilot, 2026
 * @brief      Private (board -> driver) interfaces for the ESP32 PiOS backend.
 *
 * The shared pios/inc/pios_*_priv.h headers describe STM32 peripherals in
 * terms of the ST standard peripheral library's types, so they cannot be
 * reused here. Every ESP32 driver's config struct and Init prototype lives
 * in this one file instead; board_hw_defs.c is its only consumer.
 *
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

#ifndef PIOS_ESP32_PRIV_H
#define PIOS_ESP32_PRIV_H

#include <stdint.h>
#include <stdbool.h>

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/uart.h"
#include "driver/i2c_master.h"

/* ---------------------------------------------------------------------- *
 * LED / GPIO
 * ---------------------------------------------------------------------- */

struct pios_esp32_led {
    gpio_num_t pin;
    bool active_low;    /* most devkit LEDs are active high; WROOM-32 boards vary */
};

struct pios_esp32_led_cfg {
    const struct pios_esp32_led *leds;
    uint8_t num_leds;
};

extern int32_t PIOS_LED_Init(const struct pios_esp32_led_cfg *cfg);

/* ---------------------------------------------------------------------- *
 * USART -> COM
 * ---------------------------------------------------------------------- */

struct pios_esp32_usart_cfg {
    uart_port_t port;
    gpio_num_t  rx_pin;
    gpio_num_t  tx_pin;
    uint32_t    init_baud;
    uint16_t    rx_buffer_size;
    uint16_t    tx_buffer_size;
    /* SBUS and some other RC protocols are inverted. The ESP32 UART can do
     * this in hardware, which is one of the nicer things about this part --
     * no external inverter needed. */
    bool        invert_rx;
};

extern int32_t PIOS_ESP32_USART_Init(uint32_t *usart_id,
                                     const struct pios_esp32_usart_cfg *cfg);

extern const struct pios_com_driver pios_esp32_usart_com_driver;

/* ---------------------------------------------------------------------- *
 * SPI
 * ---------------------------------------------------------------------- */

#define PIOS_ESP32_SPI_MAX_SLAVES 4

struct pios_esp32_spi_slave {
    gpio_num_t cs_pin;
    uint8_t    mode;            /* SPI mode 0..3 */
    int        clock_speed_hz;  /* "low" speed, used during device init */
    int        fast_speed_hz;   /* raised by the driver once configured */
};

struct pios_esp32_spi_cfg {
    spi_host_device_t host;
    gpio_num_t mosi_pin;
    gpio_num_t miso_pin;
    gpio_num_t sclk_pin;
    int        dma_channel;     /* SPI_DMA_CH_AUTO on IDF >= 5 */
    const struct pios_esp32_spi_slave *slaves;
    uint8_t    num_slaves;
};

extern int32_t PIOS_ESP32_SPI_Init(uint32_t *spi_id,
                                   const struct pios_esp32_spi_cfg *cfg);

/* ---------------------------------------------------------------------- *
 * Servo / RCOUT
 * ---------------------------------------------------------------------- */

/* MCPWM on the original ESP32 gives 2 units x 3 timers x 2 operators.
 * Six outputs is the practical comfortable limit and matches the
 * esp32buzz reference wiring. */
#define PIOS_ESP32_SERVO_MAX_CHANNELS 6

struct pios_esp32_servo_cfg {
    const gpio_num_t *pins;
    uint8_t num_pins;
    uint16_t default_rate_hz;
    /* Coreless brushed motors driven through low-side MOSFETs (LiteWing)
     * want a DUTY CYCLE, not a 1000-2000us servo pulse. Set this and the
     * backend switches from MCPWM pulse generation to LEDC, and PIOS_Servo_Set
     * takes 0..1000 per mille of full throttle instead of microseconds. */
    bool brushed;
    uint32_t brushed_freq_hz;   /* 0 -> SERVO_BRUSHED_DEFAULT_HZ */
};

extern int32_t PIOS_ESP32_Servo_Init(const struct pios_esp32_servo_cfg *cfg);

/* ---------------------------------------------------------------------- *
 * RC input (PPM sum via RMT)
 * ---------------------------------------------------------------------- */

struct pios_esp32_ppm_cfg {
    gpio_num_t pin;
};

extern int32_t PIOS_ESP32_PPM_Init(uint32_t *ppm_id,
                                   const struct pios_esp32_ppm_cfg *cfg);

extern const struct pios_rcvr_driver pios_esp32_ppm_rcvr_driver;

/* ---------------------------------------------------------------------- *
 * DSM (Spektrum satellite)
 * ---------------------------------------------------------------------- */

struct pios_esp32_dsm_cfg {
    uart_port_t port;
    gpio_num_t  rx_pin;
    /*
     * Bind pulse count. This SELECTS THE PROTOCOL the satellite will ask the
     * transmitter for, so it is not a tuning knob:
     *
     *     3  DSM2  1024  22ms
     *     5  DSM2  2048  11ms
     *     7  DSMX  2048  22ms
     *     9  DSMX  2048  11ms
     *
     * 9 for a DSMX satellite (SPM9745 and friends) with a DSMX transmitter.
     * Drop to 7 if the link binds but frames arrive at half rate, which is
     * what a transmitter negotiating 22ms looks like from here.
     *
     * 0 disables auto-bind entirely.
     */
    uint8_t     bind_pulses;
    /*
     * How long to wait for frames before deciding nothing is bound. A bound
     * satellite starts talking within a few frame times, so this only has to
     * cover a handful of 22ms frames -- and it must stay short, because the
     * satellite's bind window closes shortly after it powers up.
     */
    uint16_t    listen_ms;
    /* 0 = detect from the data (the historical behaviour), or force 10 or 11.
     *
     * Detection works by spotting a repeated channel number, which means the
     * value was read one bit too far left. That inference is sound on a clean
     * frame and wrong on a corrupted one, and it LATCHES: a single garbled
     * frame during power-up flips an 11-bit DSMX link to 10 and it never
     * recovers. The symptom is not silence, which would be obvious, but a
     * plausible-looking stream frozen at stale values, because the channel
     * numbers then decode from the wrong bit position and land in the wrong
     * slots. Force it when the satellite is known. */
    uint8_t resolution;
};

extern int32_t PIOS_ESP32_DSM_Init(uint32_t *dsm_id,
                                   const struct pios_esp32_dsm_cfg *cfg);
extern void PIOS_ESP32_DSM_GetState(uint32_t *frames, bool *bind_attempted);
extern const struct pios_rcvr_driver pios_esp32_dsm_rcvr_driver;

/* ---------------------------------------------------------------------- *
 * Settings storage (PIOS_FLASHFS on NVS)
 * ---------------------------------------------------------------------- */

/* Must run BEFORE UAVObjInitialize(): UAVObjRegister() calls UAVObjLoad() for
 * every object as it registers, so the filesystem has to exist by then or
 * every setting silently comes up on defaults. */
extern int32_t PIOS_ESP32_FLASHFS_Init(uintptr_t *fs_id);
extern bool PIOS_ESP32_FLASHFS_IsProvisioned(void);
extern void PIOS_ESP32_FLASHFS_MarkProvisioned(void);

/* ---------------------------------------------------------------------- *
 * WiFi telemetry (bench feature -- see pios_wifi.c header)
 * ---------------------------------------------------------------------- */
extern int32_t PIOS_ESP32_WIFI_Init(void);
extern const struct pios_com_driver pios_esp32_wifi_com_driver;

/* ---------------------------------------------------------------------- *
 * Sensor data-ready ("EXTI")
 *
 * NOT an interrupt vector in the STM32 sense. On this target the GPIO ISR
 * does nothing but notify a task, and the registered handler runs in that
 * task's context. Two hard constraints force this and neither is optional:
 *
 *   - IDF's spi_device_polling_transmit() must not be called from an ISR,
 *     and the MPU6000 data-ready handler reads the sensor over SPI.
 *   - The Xtensa FPU is unusable in an ISR; IDF does not save/restore FPU
 *     context there. PIOS_MPU6000_HandleData() does float math (the
 *     temperature scaling) on the data-ready path.
 *
 * Running the handler in a high-priority task satisfies both, and leaves the
 * shared pios/common/pios_mpu6000.c completely unmodified.
 * ---------------------------------------------------------------------- */

struct pios_esp32_exti_cfg {
    gpio_num_t pin;
    bool     (*vector)(void);   /* e.g. PIOS_MPU6000_IRQHandler */
    uint16_t   task_stack;
    uint8_t    task_priority;
    const char *task_name;
};

extern int32_t PIOS_ESP32_EXTI_Init(const struct pios_esp32_exti_cfg *cfg);

/* ---------------------------------------------------------------------- *
 * I2C
 * ---------------------------------------------------------------------- */

struct pios_esp32_i2c_cfg {
    i2c_port_num_t port;
    gpio_num_t     sda_pin;
    gpio_num_t     scl_pin;
    uint32_t       speed_hz;
};

extern int32_t PIOS_ESP32_I2C_Init(uint32_t *i2c_id, const struct pios_esp32_i2c_cfg *cfg);
extern bool    PIOS_ESP32_I2C_Probe(uint32_t i2c_id, uint16_t addr);

#endif /* PIOS_ESP32_PRIV_H */
