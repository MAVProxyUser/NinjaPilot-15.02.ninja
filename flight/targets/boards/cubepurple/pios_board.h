/**
 ******************************************************************************
 * @file       pios_board.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2026.
 * @brief      CubePilot Cube Purple (FMUv3: STM32F427, 24 MHz HSE) board
 *             definitions.  The Cube boots through its stock ArduPilot
 *             bootloader; MAIN OUT, RC IN and the safety switch live on the
 *             IO co-processor (USART6).
 * @see        The GNU Public License (GPL) Version 3
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

#ifndef PIOS_BOARD_H
#define PIOS_BOARD_H

/*
 * Pins, as ArduPilot's fmuv3 hardware definition names them:
 *
 *   PE12   FMU_LED_AMBER (open drain, low = on) - the only FMU LED
 *   SPI1   PA5/PA6/PA7   MPU9250 (CS PC2, DRDY PD15), MS5611 (CS PD7)
 *   SPI2   PB13/PB14/PB15 FM25V02 FRAM (CS PD10) - settings
 *   USART2 PD5/PD6       TELEM1
 *   USART3 PD8/PD9       TELEM2
 *   UART4  PA0/PA1       GPS
 *   USART6 PC6/PC7       IO co-processor, 1.5 Mbaud
 *   I2C1   PB8/PB9       external (GPS connector)
 *   I2C2   PB10/PB11     internal (LED driver)
 *   TIM1   PE9/PE11/PE13/PE14  AUX OUT 4/3/2/1
 *   TIM4   PD13          AUX OUT 5,   PD14 AUX OUT 6 = PPM input
 *   ADC    PA2 battery V, PA3 battery I, PA4 5 V sense, PC3 RSSI
 *   PE3    VDD_3V3_SENSORS_EN (high = on), PA8 VDD_5V_PERIPH_EN (low = on)
 *   PA9    VBUS sense
 */

// ------------------------
// Timers and Channels Used
// ------------------------
/*
   Timer | Channel 1 | Channel 2 | Channel 3 | Channel 4
   ------+-----------+-----------+-----------+----------
   TIM1  | AUX OUT 4 | AUX OUT 3 | AUX OUT 2 | AUX OUT 1
   TIM4  |           | AUX OUT 5 | PPM in    |
   ------+-----------+-----------+-----------+----------
 */

// ------------------------
// DMA Channels Used
// ------------------------
/* Channel 1  - SPI1 RX (DMA2 stream 0)     */
/* Channel 2  - SPI1 TX (DMA2 stream 3)     */
/* Channel 3  - SPI2 RX (DMA1 stream 3)     */
/* Channel 4  - SPI2 TX (DMA1 stream 4)     */
/* Channel 5  - ADC1    (DMA2 stream 4)     */

// ------------------------
// BOOTLOADER_SETTINGS
// ------------------------
#define BOARD_READABLE     true
#define BOARD_WRITABLE     true
#define MAX_DEL_RETRYS     3

// ------------------------
// WATCHDOG_SETTINGS
// ------------------------
#define PIOS_WATCHDOG_TIMEOUT  250
#define PIOS_WDG_REGISTER      RTC_BKP_DR4
#define PIOS_WDG_ACTUATOR      0x0001
#define PIOS_WDG_STABILIZATION 0x0002
#define PIOS_WDG_ATTITUDE      0x0004
#define PIOS_WDG_MANUAL        0x0008
#define PIOS_WDG_SENSORS       0x0010

// ------------------------
// PIOS_LED
// ------------------------
#define PIOS_LED_HEARTBEAT 0
/* One LED on the FMU: the alarm indication shares it. */
#define PIOS_LED_ALARM     0

// ------------------------
// PIOS_SPI
// See also pios_board.c
// ------------------------
#define PIOS_SPI_MAX_DEVS          2
extern uint32_t pios_spi_sensors_id;
extern uint32_t pios_spi_fram_id;
#define CUBE_SPI1_SLAVE_IMU        0
#define CUBE_SPI1_SLAVE_MS5611     1
#define CUBE_SPI2_SLAVE_FRAM       0

// ------------------------
// PIOS_I2C
// See also pios_board.c
// ------------------------
#define PIOS_I2C_MAX_DEVS         2
extern uint32_t pios_i2c_external_adapter_id;
extern uint32_t pios_i2c_internal_adapter_id;
#define PIOS_I2C_MAIN_ADAPTER     (pios_i2c_external_adapter_id)
#define PIOS_I2C_FLEXI_ADAPTER    (pios_i2c_external_adapter_id)
#define PIOS_I2C_ETASV3_ADAPTER   (pios_i2c_external_adapter_id)
#define PIOS_I2C_MS4525DO_ADAPTER (pios_i2c_external_adapter_id)

// -------------------------
// PIOS_USART
// -------------------------
#define PIOS_USART_MAX_DEVS 5

// -------------------------
// PIOS_COM
// -------------------------
#define PIOS_COM_MAX_DEVS 5
extern uint32_t pios_com_telem_rf_id;
extern uint32_t pios_com_gps_id;
extern uint32_t pios_com_telem_usb_id;
extern uint32_t pios_com_bridge_id;
extern uint32_t pios_com_vcp_id;
extern uint32_t pios_com_hkosd_id;
extern uint32_t pios_com_iomcu_id;
extern uint32_t pios_iomcu_id;
#define PIOS_COM_GPS       (pios_com_gps_id)
#define PIOS_COM_TELEM_USB (pios_com_telem_usb_id)
#define PIOS_COM_TELEM_RF  (pios_com_telem_rf_id)
#define PIOS_COM_BRIDGE    (pios_com_bridge_id)
#define PIOS_COM_VCP       (pios_com_vcp_id)
#define PIOS_COM_OSDHK     (pios_com_hkosd_id)

#if defined(PIOS_INCLUDE_DEBUG_CONSOLE)
extern uint32_t pios_com_debug_id;
#define PIOS_COM_DEBUG     (pios_com_debug_id)
#endif /* PIOS_INCLUDE_DEBUG_CONSOLE */

// -------------------------
// Telemetry
// -------------------------
#define TELEM_QUEUE_SIZE        80
#define PIOS_TELEM_STACK_SIZE   2048

// -------------------------
// System Settings
//
// See also System_stm32f4xx.c
// -------------------------
#define PIOS_SYSCLK 168000000
// Peripherals that belongs to APB1 are:
// DAC			|PWR				|CAN1,2
// I2C1,2,3		|UART4,5			|USART3,2
// I2S3Ext		|SPI3/I2S3			|SPI2/I2S2
// I2S2Ext		|IWDG				|WWDG
// RTC/BKP reg
// TIM2,3,4,5,6,7,12,13,14

// Calculated as SYSCLK / APBPresc * (APBPre == 1 ? 1 : 2)
// Default APB1 Prescaler = 4
#define PIOS_PERIPHERAL_APB1_CLOCK (PIOS_SYSCLK / 2)

// Peripherals belonging to APB2
// SDIO			|EXTI				|SYSCFG			|SPI1
// ADC1,2,3
// USART1,6
// TIM1,8,9,10,11
//
// Default APB2 Prescaler = 2
//
#define PIOS_PERIPHERAL_APB2_CLOCK   PIOS_SYSCLK

// -------------------------
// Interrupt Priorities
// -------------------------
#define PIOS_IRQ_PRIO_LOW            12              // lower than RTOS
#define PIOS_IRQ_PRIO_MID            8               // higher than RTOS
#define PIOS_IRQ_PRIO_HIGH           5               // for SPI, ADC, I2C etc...
#define PIOS_IRQ_PRIO_HIGHEST        4               // for USART etc...

// ------------------------
// PIOS_RCVR
// See also pios_board.c
// ------------------------
#define PIOS_RCVR_MAX_DEVS           4
#define PIOS_RCVR_MAX_CHANNELS       16
#define PIOS_GCSRCVR_TIMEOUT_MS      100
#define PIOS_OPLINK_RCVR_TIMEOUT_MS  100

// -------------------------
// Receiver PPM input (AUX OUT 6)
// -------------------------
#define PIOS_PPM_MAX_DEVS            1
#define PIOS_PPM_NUM_INPUTS          16

// -------------------------
// Receiver PWM input (unused on the Cube: the IO co-processor decodes RC)
// -------------------------
#define PIOS_PWM_MAX_DEVS            1
#define PIOS_PWM_NUM_INPUTS          1

// -------------------------
// Receiver SPEKTRUM input
// -------------------------
#define PIOS_SPEKTRUM_MAX_DEVS       2
#define PIOS_SPEKTRUM_NUM_INPUTS     12

// -------------------------
// Receiver S.Bus input
// -------------------------
#define PIOS_SBUS_MAX_DEVS           1
#define PIOS_SBUS_NUM_INPUTS         (16 + 2)

// -------------------------
// Receiver DSM input
// -------------------------
#define PIOS_DSM_MAX_DEVS            2
#define PIOS_DSM_NUM_INPUTS          12

// -------------------------
// Servo outputs: AUX OUT 1-5 on this MCU; MAIN OUT 1-8 through the IO
// -------------------------
#define PIOS_SERVO_UPDATE_HZ         50
#define PIOS_SERVOS_INITIAL_POSITION 0 /* dont want to start motors, have no pulse till settings loaded */
#define PIOS_SERVO_BANKS             6

// --------------------------
// Timer controller settings
// --------------------------
#define PIOS_TIM_MAX_DEVS            2

// -------------------------
// ADC
// PIOS_ADC_PinGet(0) = battery voltage (PA2)
// PIOS_ADC_PinGet(1) = battery current (PA3)
// PIOS_ADC_PinGet(2) = 5 V rail sense (PA4)
// PIOS_ADC_PinGet(3) = RSSI (PC3)
// -------------------------
#define PIOS_DMA_PIN_CONFIG                                                                 \
    {                                                                                       \
        { GPIOA, GPIO_Pin_2, ADC_Channel_2 },                                               \
        { GPIOA, GPIO_Pin_3, ADC_Channel_3 },                                               \
        { GPIOA, GPIO_Pin_4, ADC_Channel_4 },                                               \
        { GPIOC, GPIO_Pin_3, ADC_Channel_13 },                                              \
        { NULL, 0, ADC_Channel_Vrefint },           /* Voltage reference */                 \
        { NULL, 0, ADC_Channel_TempSensor },        /* Temperature sensor */                \
    }

/* we have to do all this to satisfy the PIOS_ADC_MAX_SAMPLES define in pios_adc.h */
/* which is annoying because this then determines the rate at which we generate buffer turnover events */
/* the objective here is to get enough buffer space to support 100Hz averaging rate */
#define PIOS_ADC_NUM_CHANNELS     6
#define PIOS_ADC_MAX_OVERSAMPLING 2
#define PIOS_ADC_USE_ADC2         0
#define PIOS_ADC_USE_TEMP_SENSOR
#define PIOS_ADC_TEMPERATURE_PIN  5

// -------------------------
// USB
// -------------------------
#define PIOS_USB_MAX_DEVS         1
#define PIOS_USB_ENABLED          1 /* Should remove all references to this */
#define PIOS_USB_HID_MAX_DEVS     1

/*
 * Actuator outputs: ActuatorSettings.ChannelAddr 0-7 are MAIN OUT 1-8 through
 * the IO co-processor, 8-12 are AUX OUT 1-5 on this MCU (see pios_board.c).
 */
#define CUBE_AUX_OUT_FIRST_CHANNEL 8

#endif /* PIOS_BOARD_H */
