/**
 ******************************************************************************
 *
 * @file       board_hw_defs.c
 * @author     NinjaPilot, 2026
 * @brief      Hardware descriptor tables for the ESP32-WROOM-32E target.
 *
 * Everything the board physically is lives here; pios_board.c only wires it
 * together. Pin choices follow the esp32buzz reference layout.
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

#include "pios.h"
#ifdef PIOS_INCLUDE_ICM20602
#include <pios_sensors.h>
#include <pios_icm20602.h>
#endif

/* ---------------------------------------------------------------------- *
 * LED
 *
 * GPIO2 is the LED on essentially every WROOM-32 devkit. If your board has
 * none, this is harmless -- the pin just toggles.
 * ---------------------------------------------------------------------- */
#ifdef PIOS_INCLUDE_LED

static const struct pios_esp32_led board_leds[] = {
    {
        /* GPIO13 is the plain STAT LED on a Thing Plus. GPIO2 there drives a
         * WS2812 RGB LED, which will not respond to a simple level. */
        .pin        = GPIO_NUM_13,
        .active_low = false,
    },
};

const struct pios_esp32_led_cfg pios_led_cfg = {
    .leds     = board_leds,
    .num_leds = NELEMENTS(board_leds),
};

#endif /* PIOS_INCLUDE_LED */

/* ---------------------------------------------------------------------- *
 * SPI -- VSPI (SPI3), sensor bus
 *
 * CS is driven by PiOS as a plain GPIO; see pios_spi.c for why.
 * ---------------------------------------------------------------------- */
#ifdef PIOS_INCLUDE_SPI

static const struct pios_esp32_spi_slave board_spi_sensors_slaves[] = {
    /* slave 0: MPU6000 / ICM-20602
     *
     * CS is GPIO14, NOT GPIO5. On a SparkFun ESP32 Thing Plus, GPIO5 is the
     * onboard microSD card's chip select and it sits on this same SPI bus --
     * using it for the IMU would have the two devices fighting. GPIO5 is fine
     * on a bare WROOM-32 devkit with no SD slot. */
    {
        .cs_pin         = GPIO_NUM_14,
        .mode           = 3,
        /* The MPU6000 only tolerates 1MHz for register access; the burst
         * read of the sensor registers is allowed up to 20MHz. Keep the
         * fast rate conservative for a first bring-up with flying leads --
         * raise it once the wiring is short and known good. */
        .clock_speed_hz = 1000000,
        /* 2MHz, not 8. The part is rated for 20MHz reads, but this board is
         * wired with flying leads to an InvenSense UEVB, so keep a wide
         * margin. 15 bytes at 2MHz is 60us against a 2ms sample period --
         * there is nothing to buy by going faster here. */
        .fast_speed_hz  = 2000000,
    },
};

const struct pios_esp32_spi_cfg pios_spi_sensors_cfg = {
    .host       = SPI3_HOST,          /* aka VSPI */
    /* Matches the SparkFun ESP32 Thing Plus silkscreen: 5/SCK, 18/MOSI,
     * 19/MISO. NOT the ESP32 VSPI defaults (18/23/19) -- and note the USB-C
     * revision of this board uses those defaults instead, so check the
     * silkscreen rather than the part name. GPIO23 here is 23/SDA. */
    .mosi_pin   = GPIO_NUM_18,
    .miso_pin   = GPIO_NUM_19,
    .sclk_pin   = GPIO_NUM_5,
    .dma_channel = SPI_DMA_CH_AUTO,
    .slaves     = board_spi_sensors_slaves,
    .num_slaves = NELEMENTS(board_spi_sensors_slaves),
};

#endif /* PIOS_INCLUDE_SPI */

/* ---------------------------------------------------------------------- *
 * ICM-20602 data-ready
 *
 * GPIO34 is input-only on the ESP32, which makes it a good choice for an
 * interrupt input -- it cannot be accidentally driven.
 *
 * This does NOT run in interrupt context. See pios_exti.c.
 * ---------------------------------------------------------------------- */
#ifdef PIOS_INCLUDE_ICM20602

const struct pios_esp32_exti_cfg pios_exti_icm20602_cfg = {
    /* GPIO32. GPIO34 is the nicer choice where it exists (input-only, so it
     * cannot be driven by mistake) but it is not broken out on every board;
     * 32 is present on the Thing Plus headers. */
    .pin           = GPIO_NUM_32,
    .vector        = PIOS_ICM20602_IRQHandler,
    .task_stack    = 3072,
    /* Above everything except the timer/IDF internals: a late gyro sample is
     * the one thing this board cannot recover from. */
    /* MAX-1 = 24: ABOVE the ESP WiFi task (23). At MAX-2 they tied, and
     * gyro capture time-sliced against RF housekeeping -- one term in the
     * 5x jump in stabilization deadline warnings when WiFi was up. Dual-core
     * pinning separates them too; the ordering stays right regardless. */
    .task_priority = configMAX_PRIORITIES - 1,
    .task_name     = "PIOS_ICM20602_DRDY",
};

const struct pios_icm20602_cfg pios_icm20602_cfg = {
    .exti_cfg            = NULL,   /* ESP32 uses pios_exti_icm20602_cfg above */
    .Fifo_store          = PIOS_ICM20602_FIFO_TEMP_OUT | PIOS_ICM20602_FIFO_GYRO_X_OUT |
                           PIOS_ICM20602_FIFO_GYRO_Y_OUT | PIOS_ICM20602_FIFO_GYRO_Z_OUT,
    .Smpl_rate_div_no_dlp = 0,
    .Smpl_rate_div_dlp    = 1,     /* 1kHz internal / (1+1) = 500Hz          */
    .interrupt_cfg        = PIOS_ICM20602_INT_CLR_ANYRD,
    .interrupt_en         = PIOS_ICM20602_INTEN_DATA_RDY,
    .User_ctl             = PIOS_ICM20602_USERCTL_DIS_I2C,
    .Pwr_mgmt_clk         = PIOS_ICM20602_PWRMGMT_PLL_X_CLK,
    .accel_range          = PIOS_ICM20602_ACCEL_8G,
    .gyro_range           = PIOS_ICM20602_SCALE_2000_DEG,
    /* 188Hz DLPF, NOT 256Hz.
     *
     * This one bites hard. PIOS_ICM20602_ConfigureRanges() picks the sample
     * rate divider like this:
     *
     *   SMPLRT_DIV = (filter == LOWPASS_256_HZ) ? Smpl_rate_div_no_dlp
     *                                           : Smpl_rate_div_dlp
     *
     * LOWPASS_256_HZ actually means "DLPF disabled", which puts the gyro
     * output at 8kHz AND selects Smpl_rate_div_no_dlp (0 here) -- so the part
     * interrupted at 8000/s instead of the intended 500. The data-ready task
     * runs just below the top priority, so it starved everything beneath it:
     * CPU pegged at 100%, telemetry stalled, app_main never resumed.
     *
     * With a real DLPF selected the base rate is 1kHz and Smpl_rate_div_dlp
     * applies: 1000/(1+1) = 500Hz, matching PIOS_SENSOR_RATE. */
    /* 41Hz, down from 176. The 2026-09-01 flight logs caught the attitude
     * estimate contradicting its own accelerometer by 9 degrees the moment
     * the motors spooled (accel said nose-UP +7.5, estimate said nose-DOWN
     * -5, |a| swinging 7.6-13.4 m/s^2): motor vibration on a 4-inch frame
     * lives at 200-500Hz, and at 176Hz bandwidth it walks into the gyro and
     * rectifies into phantom deg/s that the CC filter integrates. The FC
     * then tips a LEVEL vehicle to chase the phantom - both real-flight
     * flips. A CC3D on the same frame never cared because the MPU6000
     * samples at 8kHz internally; the ICM-20602 at DLPF>0 runs a 1kHz ODR.
     * 41Hz crushes the vibration band ~20dB+ while adding ~6ms of group
     * delay - well inside this loop's budget. */
    .filter               = PIOS_ICM20602_DLPF_41HZ,
    .orientation          = PIOS_ICM20602_TOP_0DEG,
    .fast_prescaler       = PIOS_SPI_PRESCALER_4,
    .std_prescaler        = PIOS_SPI_PRESCALER_64,
    .max_downsample       = 1,
};

#endif /* PIOS_INCLUDE_ICM20602 */

/* ---------------------------------------------------------------------- *
 * UARTs
 *
 * UART0 is the one wired to the USB-serial bridge on every devkit, so it is
 * both the boot console and the GCS link. Note the WROOM-32 has no native
 * USB -- unlike the S3 there is no CDC option, the bridge is the only path.
 * ---------------------------------------------------------------------- */
#ifdef PIOS_INCLUDE_USART

const struct pios_esp32_usart_cfg pios_usart_telem_cfg = {
    .port           = UART_NUM_0,
    .rx_pin         = GPIO_NUM_3,
    .tx_pin         = GPIO_NUM_1,
    .init_baud      = 115200,
    .rx_buffer_size = 512,
    .tx_buffer_size = 512,
    .invert_rx      = false,
};

/* Spare port: GPS, a second telemetry link, or serial RC.
 * For SBUS set .invert_rx = true -- the ESP32 UART inverts in hardware, so
 * no external inverter is needed. */
const struct pios_esp32_usart_cfg pios_usart_aux_cfg = {
    .port           = UART_NUM_2,
    .rx_pin         = GPIO_NUM_16,
    .tx_pin         = GPIO_NUM_17,
    .init_baud      = 57600,
    .rx_buffer_size = 512,
    .tx_buffer_size = 256,
    .invert_rx      = false,
};

#endif /* PIOS_INCLUDE_USART */

/* ---------------------------------------------------------------------- *
 * Servo outputs (MCPWM)
 *
 * Quad X order matches the mixer's expectation of channels 1-4.
 * ---------------------------------------------------------------------- */
#ifdef PIOS_INCLUDE_SERVO

/* GPIO32 is now the IMU data-ready input, and 21/22 are the Qwiic I2C pins on
 * a Thing Plus, so the servo set is trimmed to four -- which is all a quad
 * needs. Put them back if you are on a bare devkit and want 6 channels. */
/* Motor outputs, quad X order (M1..M4), matching the mixer the GCS writes for
 * a Quad X: 1 front-left, 2 front-right, 3 rear-right, 4 rear-left.
 *
 * Every one of these is directly labelled on the Thing Plus silkscreen, which
 * matters: GPIO25/26 are only reachable as A1/A0 and are not labelled by
 * number, so they are avoided.
 *
 * !! GPIO12 (M4) REQUIRES A BURNED eFUSE !!
 *
 * GPIO12 is MTDI, sampled at reset to choose the flash voltage: high selects
 * 1.8V, and this module runs 3.3V flash, so anything holding that line high as
 * the chip leaves reset stops it booting entirely. An ESC does not drive the
 * line, but its input stage usually carries a pull-up, and the ESC's BEC
 * typically powers before the ESP32 -- which is exactly the reset window that
 * matters.
 *
 * This board is safe because the fuse has been burned on THIS CHIP:
 *
 *     espefuse.py set_flash_voltage 3.3V     -> XPD_SDIO_FORCE = True
 *
 * after which MTDI is ignored at reset. That is per-chip and irreversible.
 * Flash this firmware to a different ESP32 without that fuse and a powered ESC
 * on M4 will leave it apparently dead at power-up. Check with
 * `espefuse.py summary` before assuming. Move M4 back to GPIO17 if in doubt.
 *
 * GPIO12 is also JTAG MTDI, so using it here rules out JTAG on this board.
 */
static const gpio_num_t board_servo_pins[] = {
    GPIO_NUM_15,   /* M1 -- front-left  */
    GPIO_NUM_33,   /* M2 -- front-right */
    GPIO_NUM_27,   /* M3 -- rear-right  */
    GPIO_NUM_12,   /* M4 -- rear-left, see the eFuse note above */
};

const struct pios_esp32_servo_cfg pios_servo_cfg = {
    .pins            = board_servo_pins,
    .num_pins        = NELEMENTS(board_servo_pins),
    /* 400Hz suits multirotor ESCs. Actuator settings can change this at
     * runtime via PIOS_Servo_SetHz(). */
    .default_rate_hz = 400,
};

#endif /* PIOS_INCLUDE_SERVO */

/* ---------------------------------------------------------------------- *
 * RC input -- PPM sum, decoded by RMT
 * ---------------------------------------------------------------------- */
#ifdef PIOS_INCLUDE_PPM

const struct pios_esp32_ppm_cfg pios_ppm_cfg = {
    /* GPIO21. GPIO4 is not broken out on the Thing Plus headers.
     *
     * A receiver is a worse thing to hang off a strapping pin than an ESC --
     * it is powered by the flight controller's own BEC and can be driving the
     * line the instant rails come up -- so keep RC input off GPIO12 and GPIO15
     * regardless of the eFuse. (GPIO15 is the milder of the two: it only
     * selects whether the ROM boot log prints, which is why M1 can live there
     * safely. GPIO12 chooses the flash voltage and stops the boot outright.) */
    .pin = GPIO_NUM_21,
};

#endif /* PIOS_INCLUDE_PPM */

/* ---------------------------------------------------------------------- *
 * RC input -- Spektrum DSM satellite
 * ---------------------------------------------------------------------- */
#ifdef PIOS_INCLUDE_DSM

const struct pios_esp32_dsm_cfg pios_dsm_cfg = {
    /* GPIO16, silkscreened 16/RX1 on the Thing Plus. Three wires from the
     * satellite: 3.3V (NOT 5V -- a satellite is a 3.3V device), ground, and
     * signal to this pin. */
    .port        = UART_NUM_2,
    .rx_pin      = GPIO_NUM_16,
    /*
     * Auto-bind is OFF. The receiver on this airframe is already bound, and
     * leaving it armed is a bad trade: a bound satellite is silent when the
     * transmitter is switched off, which is indistinguishable from never
     * having been bound, so powering up with the TX off would drop a working
     * receiver into bind mode and leave it there.
     *
     * The bind code is still compiled and works -- set this to 9 (DSMX
     * 2048/11ms, right for a DSMX satellite like the SPM9745) to arm it for
     * one flash cycle, power-cycle to bind, then set it back to 0. The full
     * pulse-count table is in the config struct in pios_esp32_priv.h.
     *
     * Note it has to be a POWER CYCLE, not a reset: the satellite only opens
     * its bind window shortly after its own supply comes up, and a software
     * reset of the ESP32 never drops the 3.3V feeding it.
     */
    .bind_pulses = 0,
    .listen_ms   = 250,
};

#endif /* PIOS_INCLUDE_DSM */
