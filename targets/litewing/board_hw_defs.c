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
#ifdef PIOS_INCLUDE_BMP388
#include <pios_bmp388.h>
#endif
#ifdef PIOS_INCLUDE_BMP280
#include <pios_bmp280.h>
#endif
#ifdef PIOS_INCLUDE_HMC5X83
#include <pios_hmc5x83.h>
#endif
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
        .pin        = GPIO_NUM_7,   /* LED_BLUE on LiteWing */
        .active_low = false,
    },
    {
        /* RED, GPIO8: arming state. Was fitted but never wired up in firmware
         * -- the board has three LEDs and only ever used one. */
        .pin        = GPIO_NUM_8,
        .active_low = false,
    },
    {
        /* GREEN, GPIO9: navigation readiness. */
        .pin        = GPIO_NUM_9,
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
        .cs_pin         = GPIO_NUM_42,  /* CS on the LiteWing SPI header */
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
    .mosi_pin   = GPIO_NUM_35,
    .miso_pin   = GPIO_NUM_37,
    .sclk_pin   = GPIO_NUM_36,
    .dma_channel = SPI_DMA_CH_AUTO,
    .slaves     = board_spi_sensors_slaves,
    .num_slaves = NELEMENTS(board_spi_sensors_slaves),
};

#endif /* PIOS_INCLUDE_SPI */

/* ---------------------------------------------------------------------- *
 * I2C0 -- the MPU6050 lives here on LiteWing (schematic V2.6.C).
 * 400 kHz: a 15-byte sample burst costs ~390 us, about 19% of a 500 Hz
 * period. That is the price of an I2C IMU and it is why the Thing Plus board
 * puts its ICM-20602 on SPI instead (~15 us). Both work at 500 Hz.
 * The same bus is brought out on the expansion header for a baro/mag.
 * ---------------------------------------------------------------------- */
#ifdef PIOS_INCLUDE_I2C
const struct pios_esp32_i2c_cfg pios_i2c_sensors_cfg = {
    .port     = I2C_NUM_0,
    .sda_pin  = GPIO_NUM_11,
    .scl_pin  = GPIO_NUM_10,
    .speed_hz = 400000,
};

/* ---------------------------------------------------------------------- *
 * I2C1 -- the expansion header pads silkscreened SDA1/SCL1, alongside the
 * VL53L1X footprint. A barometer goes HERE and not on I2C0 on purpose: I2C0
 * carries the MPU6050 at 500 Hz and a 15-byte burst already costs ~19% of a
 * period. A baro sharing that bus would be stealing time from the only
 * sensor the aircraft cannot fly without.
 *
 * 400 kHz. The BMP388 is rated to 3.4 MHz, but the header is a flying-lead
 * connection on a board full of motor noise, and the baro is read at 50 Hz --
 * there is nothing to gain from going faster.
 * ---------------------------------------------------------------------- */
const struct pios_esp32_i2c_cfg pios_i2c_baro_cfg = {
    .port     = I2C_NUM_1,
    .sda_pin  = GPIO_NUM_40,
    .scl_pin  = GPIO_NUM_41,
    .speed_hz = 400000,
};
#endif /* PIOS_INCLUDE_I2C */

#ifdef PIOS_INCLUDE_BMP388
/* Measured, not recommended. Bench sweep of 11 configs (baro_sweep.c, build
 * with BOARD_BARO_SWEEP=1), 48 samples each, scored on the RMS of successive
 * differences so that room pressure drift cancels:
 *
 *   x1  IIR off  50Hz   47.0 cm      x16 IIR 7    25Hz    2.0 cm
 *   x2  IIR 1    50Hz   17.2 cm      x16 IIR 15   25Hz    0.8 cm
 *   x4  IIR 3    50Hz    8.6 cm      x16 IIR 31   25Hz    0.4 cm
 *   x8  IIR 3    50Hz    4.6 cm      x32 IIR 15 12.5Hz    0.6 cm
 *   x8  IIR 7    50Hz    2.3 cm      x32 IIR 31 12.5Hz    0.6 cm
 *   x8  IIR 15   50Hz    1.3 cm   <- chosen
 *
 * The quietest rows are NOT the best choice, for two reasons:
 *
 * AltFilter polls at exactly 50 Hz, so an ODR below that hands it the same
 * conversion twice and the Kalman treats a repeat as independent evidence,
 * shrinking its own covariance on information it did not receive. Everything
 * slower than 50 Hz pays that until the drivers gate on data-ready.
 *
 * The IIR coefficient is group delay: the time constant is roughly
 * coefficient x ODR period, so IIR 31 at 25 Hz is ~1.2 s of lag handed to a
 * thrust loop on a 45 g airframe.
 *
 * Now x8 IIR 7 at 50 Hz: 2.3 cm on the bench, ~140 ms of group delay.
 *
 * Chosen from FLIGHT data, not bench data. A log of three altitude-hold
 * engagements shows the barometer's sample-to-sample noise in a hover is
 * 2.3-3.6 cm whatever the filter setting -- roughly four times the 0.6 cm it
 * reads sitting still -- while the altitude signal swings 1-4 m peak to peak.
 * The large movement is therefore the aircraft, not the sensor, and no amount
 * of filtering addresses it.
 *
 * What filtering does cost is phase. The same log shows a 2-second limit cycle
 * with thrust saturating every cycle; 600 ms of group delay (the x16 IIR15 at
 * 25 Hz this replaces) is about 108 degrees of phase at that period, fed
 * straight into a closed thrust loop. The earlier reasoning -- that lag on the
 * reference channel of a complementary filter is cheap -- holds only while
 * nothing is controlling on that channel. Once altitude hold could actually
 * command thrust, it stopped being true.
 *
 * Below, for the record, the bench sweep this was originally chosen from:
 *
 * The earlier choice (x8 IIR 15 at 50 Hz, 1.3 cm) avoided any ODR below the
 * consumer's 50 Hz poll, because a stale read was being fed to the Kalman as
 * if it were a fresh measurement. The drivers now gate on data-ready and
 * report "no new sample" instead, so the slower, quieter rows are safe.
 *
 * Not the quietest row, deliberately. x16 IIR 31 measured 0.4 cm but carries
 * ~1.2 s of group delay (the IIR time constant is roughly coefficient x ODR
 * period), against ~0.6 s here. Below about 1 cm the white noise is an order
 * of magnitude under the part's thermal drift, so further filtering buys
 * nothing real while the lag is paid in full by the controller.
 */
const struct pios_bmp388_cfg pios_bmp388_cfg = {
    .oversampling_pressure    = BMP388_OSR_8,
    .oversampling_temperature = BMP388_OSR_1,
    .filter                   = BMP388_FILTER_7,
    .odr                      = BMP388_ODR_50_HZ,
    /* 0 lets the driver default to 0x76; the boot scan reports which address
     * actually answered. */
    .i2c_addr                 = 0,
};
#endif /* PIOS_INCLUDE_BMP388 */

#ifdef PIOS_INCLUDE_HMC5X83
/* HMC5883L on I2C1 at 0x1E, alongside the BMP388 at 0x77 (the VL53L1X pads:
 * VIN/GND/SCL1=GPIO41/SDA1=GPIO40). Confirmed genuine by its ID registers
 * reading 'H','4','3' -- the QMC5883L widely sold under the same name answers
 * at 0x0D with a different register map and is NOT this driver's part.
 *
 * 75Hz is the part's maximum and costs nothing here: modules/Sensors polls it,
 * and a magnetometer is a slow heading correction, so the only thing rate buys
 * is a shorter worst-case age on each sample.
 *
 * Gain 1.9 Ga full scale: earth field is ~0.5 Ga, leaving better than 3x
 * headroom for the throttle-dependent field the motor leads add. Dropping to
 * 1.3 would buy resolution but risks saturating on current spikes, which
 * presents as heading that lurches with throttle rather than as a clean error. */
const struct pios_hmc5x83_cfg pios_hmc5x83_cfg = {
    .M_ODR            = PIOS_HMC5x83_ODR_75,
    .Meas_Conf        = PIOS_HMC5x83_MEASCONF_NORMAL,
    .Gain             = PIOS_HMC5x83_GAIN_1_9,
    .Mode             = PIOS_HMC5x83_MODE_CONTINUOUS,
    .TempCompensation = false,
    .Driver           = &PIOS_HMC5x83_I2C_DRIVER,
};
#endif /* PIOS_INCLUDE_HMC5X83 */

#ifdef PIOS_INCLUDE_BMP280
/* Measured the same way as the BMP388 above, 9 configs:
 *
 *   x1  IIR off   27.9 cm      x8  IIR 16    2.3 cm   <- chosen
 *   x2  IIR 2     12.6 cm      x16 IIR 4     4.0 cm
 *   x4  IIR 4      4.9 cm      x16 IIR 8     1.9 cm
 *   x8  IIR 4      5.8 cm      x16 IIR 16    1.7 cm
 *   x8  IIR 8      3.1 cm
 *
 * x16 IIR 16 is quietest, and is not chosen. At x16 pressure with x2
 * temperature the part takes ~38 ms per conversion, about 26 Hz, so roughly
 * half of AltFilter's 50 Hz polls would read a conversion they have already
 * seen. x8 runs near 40 Hz and costs only 0.6 cm.
 *
 * Note these selectors are NOT the BMP388's: on the BMP280, 0 means "skip
 * this channel" and the useful values start at 1, so a config copied between
 * the two parts silently disables a channel. */
const struct pios_bmp280_cfg pios_bmp280_cfg = {
    .oversampling_pressure    = BMP280_OSR_8,
    .oversampling_temperature = BMP280_OSR_1,
    .filter                   = BMP280_FILTER_16,
    .i2c_addr                 = 0,   /* 0 -> driver default 0x76 */
};
#endif /* PIOS_INCLUDE_BMP280 */

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
    .pin           = GPIO_NUM_12,  /* MPU_INT */
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
    /* 1kHz internal / (2+1) = 333Hz, DELIBERATELY faster than the 250Hz
     * PIOS_SENSOR_RATE that modules/Sensors polls at. Matching the two exactly
     * makes every poll marginal by construction: SensorsTask waits exactly one
     * sensor period for the primary sample, so any jitter at all leaves the
     * queue empty, which it counts as a sensor failure (PIOS_SENSOR_Reset plus
     * SYSTEMALARMS_ALARM_SENSORS Critical, which in turn flaps the Attitude
     * alarm and can block arming). Running the producer ~33% ahead means a
     * sample is always already waiting. SensorsTask drains and averages
     * whatever it finds on each pass, so the surplus costs nothing. */
    .Smpl_rate_div_dlp    = 2,     /* 1kHz/(2+1) = 333Hz, ahead of the 250Hz
                                    * PIOS_SENSOR_RATE the consumer polls at. */
    .interrupt_cfg        = PIOS_ICM20602_INT_CLR_ANYRD,
    .interrupt_en         = PIOS_ICM20602_INTEN_DATA_RDY,
    /* MUST be 0 here. USERCTL_DIS_I2C is bit 4 = I2C_IF_DIS, which on the
     * SPI boards forces the part SPI-only. LiteWing's MPU6050 is ON I2C, so
     * setting it would hang up the bus mid-configuration -- and the MPU6050
     * datasheet marks that bit "always write 0" in any case. */
    .User_ctl             = 0,
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
    /* Queue depth is max_downsample + 1, so 1 gave a 2-sample buffer -- about
     * 8ms at 250Hz. This platform has documented ~4ms SMP/lwIP stalls, so a
     * single hiccup left the queue empty at modules/Sensors' next poll, which
     * counts as a primary-sensor miss: it calls PIOS_SENSOR_Reset() and raises
     * SYSTEMALARMS_ALARM_SENSORS Critical. (modules/Attitude never noticed,
     * because it read the IMU itself rather than through this queue.)
     * SensorsTask drains and averages everything waiting on each pass, so a
     * deeper queue costs nothing but ~32ms of slack to absorb the stalls. */
    .max_downsample       = 7,
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
    .rx_pin         = GPIO_NUM_44,  /* RXD0 -> CH340K */
    .tx_pin         = GPIO_NUM_43,  /* TXD0 -> CH340K */
    .init_baud      = 115200,
    .rx_buffer_size = 512,
    .tx_buffer_size = 512,
    .invert_rx      = false,
};

/* GPS, on UART1 and the expansion header's GPIO17/18.
 *
 * 115200 because that is what the module actually does: a bench sniff of a
 * Sequre M10-12 (firmware/gps_sniff.c) found NMEA and UBX sync bytes there,
 * and nothing intelligible at 9600, which is what older u-blox parts default
 * to and what the wiring guides all assume.
 *
 * This is the pin pair the IDF console used to sit on. The ESP32-S3 has three
 * UARTs and all three are now spoken for -- UART0 to the CH340K and the GCS,
 * UART1 here, UART2 to the DSM satellite -- so the console has to move to
 * UART0 or go away entirely. See sdkconfig.defaults.
 */
const struct pios_esp32_usart_cfg pios_usart_gps_cfg = {
    .port           = UART_NUM_1,
    .rx_pin         = GPIO_NUM_18,  /* board RX <- GPS TX */
    .tx_pin         = GPIO_NUM_17,  /* board TX -> GPS RX */
    .init_baud      = 115200,
    .rx_buffer_size = 512,
    .tx_buffer_size = 256,
    .invert_rx      = false,
};

/* Spare port: GPS, a second telemetry link, or serial RC.
 * For SBUS set .invert_rx = true -- the ESP32 UART inverts in hardware, so
 * no external inverter is needed.
 *
 * NOTE: UART_NUM_2 is also named by pios_dsm_cfg, which is the one actually
 * initialised on this board. Nothing brings this port up; if you ever do,
 * move one of them to a different UART first. */
const struct pios_esp32_usart_cfg pios_usart_aux_cfg = {
    .port           = UART_NUM_2,
    .rx_pin         = GPIO_NUM_18,  /* free expansion pin  */
    .tx_pin         = GPIO_NUM_17,  /* free expansion pin  */
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
    GPIO_NUM_5,    /* MOT_1 */
    GPIO_NUM_6,    /* MOT_2 */
    GPIO_NUM_3,    /* MOT_3 */
    GPIO_NUM_4,    /* MOT_4 */
};

const struct pios_esp32_servo_cfg pios_servo_cfg = {
    .pins            = board_servo_pins,
    .num_pins        = NELEMENTS(board_servo_pins),
    /* Unused in brushed mode -- kept so the field is not a surprise 0. */
    .default_rate_hz = 400,
    /* LiteWing's four 720-size coreless motors hang off low-side MOSFETs with
     * no ESC in between, so the output is a duty cycle at a fixed carrier.
     * PIOS_Servo_Set() then takes 0..1000 per mille, which is exactly the
     * actuator endpoint range this board is configured with (0 / 0 / 1000). */
    .brushed         = true,
    .brushed_freq_hz = 24000,
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
    .pin = GPIO_NUM_16,  /* free expansion pin */
};

#endif /* PIOS_INCLUDE_PPM */

/* ---------------------------------------------------------------------- *
 * RC input -- Spektrum DSM satellite
 * ---------------------------------------------------------------------- */
#ifdef PIOS_INCLUDE_DSM

const struct pios_esp32_dsm_cfg pios_dsm_cfg = {
    /* IO15 on the expansion header -- the bottom pin of the right-hand
     * column, about 6mm to the right of the RESET button. Three wires from
     * the satellite: 3.3V (NOT 5V, a satellite is a 3.3V device), ground, and
     * signal to this pin.
     *
     * NOT GPIO18, which is what the ESP32 quad used: on LiteWing that pin is
     * the console UART's RX, and DSM frames would fight boot chatter.
     *
     * GPIO15 is XTAL_32K_P on the S3, so it would be spoken for if a 32 kHz
     * crystal were fitted. None is -- the board has no crystal and the RTC
     * runs from the internal RC (CONFIG_RTC_CLK_SRC_INT_RC) -- so it is a
     * plain GPIO here.
     *
     * UART2 is shared with pios_usart_aux_cfg on paper. Only one can own it,
     * and nothing initialises the aux port on this target, so DSM has it. */
    .port        = UART_NUM_2,
    .rx_pin      = GPIO_NUM_15,
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
    /* SPM9745 is DSMX and always 11-bit, so say so rather than inferring it
     * every power-up. Auto-detect latched to 10 on some boots here, which
     * decoded as a frozen but plausible-looking stream. */
    .resolution  = 11,
    .bind_pulses = 0,
    .listen_ms   = 250,
};

#endif /* PIOS_INCLUDE_DSM */
