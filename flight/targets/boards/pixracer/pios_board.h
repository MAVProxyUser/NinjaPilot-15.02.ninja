/**
 ******************************************************************************
 * @file       STM32F4xx_Pixracer.h
 * @brief      Board definition for the mRo / AUAV PixRacer R12 (FMUv4).
 *
 * Hardware summary (cross-checked against ArduPilot
 * libraries/AP_HAL_ChibiOS/hwdef/Pixracer/hwdef.dat):
 *
 *   MCU        STM32F427VIT6, 100-pin LQFP, 2 MB flash, 192 KB SRAM + 64 KB CCM
 *   HSE        24 MHz          SYSCLK 168 MHz, APB1 42 MHz, APB2 84 MHz
 *   SPI1       sensor bus      MPU9250 (PC2), ICM-20608-G (PC15), HMC5983 (PE15)
 *   SPI2       storage bus     MS5611 baro (PD7), FM25V02 FRAM (PD10)
 *   I2C1       PB8/PB9         external only, brought out on the GPS connector
 *   SDIO       PC8-PC12, PD2   microSD slot
 *   USB        OTG FS PA11/PA12, VBUS sense PA9
 *
 * Note that unlike Revo, this board gates sensor power in software:
 * VDD_SENSORS_EN (PE3) and VDD_PERIPH_EN (PC5) must be driven high before any
 * sensor on either SPI bus will answer.  See pios_board.c.
 *****************************************************************************/
#ifndef STM32F4XX_PIXRACER_H_
#define STM32F4XX_PIXRACER_H_

#include <stdbool.h>

//------------------------
// Timers and Channels Used
//------------------------
/*
Timer | Channel 1 | Channel 2 | Channel 3 | Channel 4
------+-----------+-----------+-----------+----------
TIM1  | Servo 4   | Servo 3   | Servo 2   | Servo 1
TIM2  | --------------- PIOS_DELAY -----------------
TIM3  |           |           |           |
TIM4  |           | Servo 5   | Servo 6   |
TIM5  |           |           |           |
TIM6  |           |           |           |
TIM7  |           |           |           |
TIM8  |           | RC input  |           |
------+-----------+-----------+-----------+----------

  Servo 1..4 are TIM1_CH4/3/2/1 on PE14/PE13/PE11/PE9 - note the channel order
  is reversed with respect to the connector, exactly as in the ArduPilot hwdef.
  Servo 5..6 are TIM4_CH2/CH3 on PD13/PD14.
  RC input is TIM8_CH2 on PC7, which doubles as USART6_RX for serial receivers.
*/

//------------------------
// DMA Streams Used
//------------------------
/* DMA2 Stream0 Ch3 - SPI1 RX (sensors)          */
/* DMA2 Stream3 Ch3 - SPI1 TX (sensors)          */
/* DMA1 Stream3 Ch0 - SPI2 RX (baro + FRAM)      */
/* DMA1 Stream4 Ch0 - SPI2 TX (baro + FRAM)      */

//------------------------
// BOOTLOADER_SETTINGS
//------------------------
/* The stock PX4/ArduPilot bootloader owns sector 0 and this tree does not
 * build a replacement, so the OpenPilot bootloader-side flash helpers are
 * inert on this board. */
#define BOARD_READABLE	true
#define BOARD_WRITABLE	true
#define MAX_DEL_RETRYS	3

//------------------------
// PIOS_LED
//
// PixRacer has three discrete LEDs wired to sink current through the MCU pin,
// so they are ACTIVE LOW (ArduPilot's HAL_GPIO_LED_ON defaults to 0).  The
// pios_led entries set .active_high = false accordingly.
//------------------------
/*
 * Boot-stage indicator.
 *
 * PIOS_Board_Init runs inside a FreeRTOS task, so everything before the
 * scheduler starts - clock setup, heap init, task creation - is invisible to
 * the normal LED code.  This drives the three LEDs straight through their
 * registers so each stage can be seen from reset onwards, which is the only
 * way to localise a failure on a board that will not talk over USB yet.
 *
 * Active low: driving a pin low lights its LED.
 */
#define BRINGUP_LED_GREEN	(1u << 1)	/* PB1  */
#define BRINGUP_LED_BLUE	(1u << 3)	/* PB3  */
#define BRINGUP_LED_RED	(1u << 11)	/* PB11 */
#define BRINGUP_LED_ALL	(BRINGUP_LED_GREEN | BRINGUP_LED_BLUE | BRINGUP_LED_RED)

extern void PIOS_Board_boot_stage(uint32_t leds);
extern void PIOS_Board_wdg_kick(void);
extern void PIOS_Board_wdg_arm(void);
extern volatile uint32_t pios_bringup_progress;
extern volatile uint32_t pios_bringup_progress2;
/* xTaskHandle is void* underneath; this header is seen before FreeRTOS's are. */
extern void *pios_bringup_reporter_handle;
extern const char *PIOS_Board_reset_cause_str(void);
extern uint32_t pios_bringup_reset_cause;
extern void PIOS_Board_boot_blink(uint32_t led, unsigned n);
extern void PIOS_Board_debug_puts(const char *str);
extern void PIOS_Board_debug_putu(unsigned v);
extern void PIOS_Board_debug_puthex(unsigned v);

#define PIOS_LED_HEARTBEAT	0	/* green, PB1  */
#define PIOS_LED_ALARM		1	/* red,   PB11 */
#define PIOS_LED_BLUE		2	/* blue,  PB3  */

//------------------------
// PIOS_SPI
// See also pios_board.c
//------------------------
#define PIOS_SPI_MAX_DEVS        2

/* Chip-select indices into the ssel[] arrays in board_hw_defs.c.  Both buses
 * carry several devices, so every driver has to be told which one it is. */
#define PIXRACER_SPI1_SLAVE_MPU9250     0
#define PIXRACER_SPI1_SLAVE_ICM20608    1
#define PIXRACER_SPI1_SLAVE_MAG         2

#define PIXRACER_SPI2_SLAVE_MS5611      0
#define PIXRACER_SPI2_SLAVE_FRAM        1

extern uint32_t pios_spi_sensors_id;
extern uint32_t pios_spi_baro_fram_id;

/*
 * Sensor handles.  Declared as uintptr_t rather than the drivers' typedefs
 * because this header is pulled in from pios.h ahead of the driver headers;
 * both typedefs resolve to uintptr_t so the declarations agree.
 *
 * The board has two interchangeable IMUs.  The Sensors module consumes one of
 * them; PIOS_SENSORS_PRIMARY_IMU says which.  The ICM-20608 is initialised and
 * sampling either way, so switching primary is a one-line change here.
 */
extern uintptr_t pios_mpu9250_id;
extern uintptr_t pios_icm20608_id;
extern uintptr_t pios_hmc5983_id;

/* Set by PIOS_Board_Init to record which sensors answered at boot.  Reported
 * on the debug console; also readable over the GCS for diagnosis. */
extern uint32_t pios_bringup_sensors_found;

#define PIXRACER_SENSOR_MPU9250		0x01
#define PIXRACER_SENSOR_ICM20608	0x02
#define PIXRACER_SENSOR_HMC5983		0x04
#define PIXRACER_SENSOR_MS5611		0x08
#define PIXRACER_SENSOR_ALL		0x0F

#define PIOS_SENSORS_PRIMARY_IMU	(pios_mpu9250_id)
#define PIOS_SENSORS_SECONDARY_IMU	(pios_icm20608_id)
#define PIOS_SENSORS_PRIMARY_MAG	(pios_hmc5983_id)

//------------------------
// PIOS_WDG
//------------------------
#define PIOS_WATCHDOG_TIMEOUT    250
#define PIOS_WDG_REGISTER        RTC_BKP_DR4
#define PIOS_WDG_ACTUATOR        0x0001
#define PIOS_WDG_STABILIZATION   0x0002
#define PIOS_WDG_ATTITUDE        0x0004
#define PIOS_WDG_MANUAL          0x0008
#define PIOS_WDG_SENSORS         0x0010

//------------------------
// PIOS_I2C
//
// Only one I2C bus is pinned out (PB8/PB9 on the GPS connector).  Everything
// that Revo reached over I2C - magnetometer and barometer - is on SPI here,
// so this bus carries external devices only.
//------------------------
#define PIOS_I2C_MAX_DEVS			1
extern uint32_t pios_i2c_external_adapter_id;
#define PIOS_I2C_MAIN_ADAPTER			(pios_i2c_external_adapter_id)
#define PIOS_I2C_FLEXI_ADAPTER			(pios_i2c_external_adapter_id)
#define PIOS_I2C_ETASV3_ADAPTER			(pios_i2c_external_adapter_id)

//-------------------------
// PIOS_USART
//
// See also pios_board.c
//-------------------------
#define PIOS_USART_MAX_DEVS             6

//-------------------------
// PIOS_COM
//
// See also pios_board.c
//-------------------------
#define PIOS_COM_MAX_DEVS               5
extern uint32_t pios_com_telem_rf_id;
extern uint32_t pios_com_gps_id;
extern uint32_t pios_com_telem_usb_id;
extern uint32_t pios_com_bridge_id;
extern uint32_t pios_com_vcp_id;
#define PIOS_COM_GPS                    (pios_com_gps_id)
#define PIOS_COM_TELEM_USB              (pios_com_telem_usb_id)
#define PIOS_COM_TELEM_RF               (pios_com_telem_rf_id)
#define PIOS_COM_BRIDGE                 (pios_com_bridge_id)
#define PIOS_COM_VCP                    (pios_com_vcp_id)

#if defined(PIOS_INCLUDE_DEBUG_CONSOLE)
extern uint32_t pios_com_debug_id;
#define PIOS_COM_DEBUG                  (pios_com_debug_id)
#endif	/* PIOS_INCLUDE_DEBUG_CONSOLE */

//-------------------------
// Packet Handler
//
// No RFM22B radio on this board, but the packet handler is still referenced by
// shared telemetry code.
//-------------------------
#define RS_ECC_NPARITY 4
#define PIOS_PH_MAX_PACKET 255
#define PIOS_PH_WIN_SIZE 3
#define PIOS_PH_MAX_CONNECTIONS 1
extern uint32_t pios_packet_handler;
#define PIOS_PACKET_HANDLER (pios_packet_handler)

//------------------------
// TELEMETRY
//------------------------
#define TELEM_QUEUE_SIZE         80
#define PIOS_TELEM_STACK_SIZE    624

//-------------------------
// System Settings
//
// See also Source/pixracer/system_stm32f4xx.c.  The PLL is deliberately set
// up to land on the same 168/84/42 MHz tree as Revo so that every clock-derived
// PIOS constant below carries over unchanged despite the different crystal.
//-------------------------
#define PIOS_SYSCLK										168000000
/* APB1 prescaler 4 -> timer clock is SYSCLK/2 */
#define PIOS_PERIPHERAL_APB1_CLOCK					(PIOS_SYSCLK / 2)
/* APB2 prescaler 2 -> timer clock is SYSCLK */
#define PIOS_PERIPHERAL_APB2_CLOCK					PIOS_SYSCLK

//-------------------------
// Interrupt Priorities
//-------------------------
#define PIOS_IRQ_PRIO_LOW                       12              // lower than RTOS
#define PIOS_IRQ_PRIO_MID                       8               // higher than RTOS
#define PIOS_IRQ_PRIO_HIGH                      5               // for SPI, ADC, I2C etc...
#define PIOS_IRQ_PRIO_HIGHEST                   4               // for USART etc...

//------------------------
// PIOS_RCVR
// See also pios_board.c
//------------------------
#define PIOS_RCVR_MAX_DEVS           3
#define PIOS_RCVR_MAX_CHANNELS       12
#define PIOS_GCSRCVR_TIMEOUT_MS      100

//-------------------------
// Receiver PPM input
//-------------------------
#define PIOS_PPM_MAX_DEVS            1
#define PIOS_PPM_NUM_INPUTS          12

//-------------------------
// Receiver PWM input
//
// Only the single RC input pin (PC7) is available, so unlike Revo there is no
// bank of parallel PWM inputs.
//-------------------------
#define PIOS_PWM_MAX_DEVS            1
#define PIOS_PWM_NUM_INPUTS          1

//-------------------------
// Receiver SPEKTRUM input
//-------------------------
#define PIOS_SPEKTRUM_MAX_DEVS       1
#define PIOS_SPEKTRUM_NUM_INPUTS     12

//-------------------------
// Receiver S.Bus input
//
// PC13 drives the on-board S.Bus inverter.
//-------------------------
#define PIOS_SBUS_MAX_DEVS           1
#define PIOS_SBUS_NUM_INPUTS         (16+2)

//-------------------------
// Receiver DSM input
//-------------------------
#define PIOS_DSM_MAX_DEVS			1
#define PIOS_DSM_NUM_INPUTS			12

//-------------------------
// Servo outputs
//-------------------------
#define PIOS_SERVO_UPDATE_HZ                    50
#define PIOS_SERVOS_INITIAL_POSITION            0 /* dont want to start motors, have no pulse till settings loaded */

//--------------------------
// Timer controller settings
//--------------------------
#define PIOS_TIM_MAX_DEVS			6

//-------------------------
// ADC
//
// PIOS_ADC_PinGet(0) = battery voltage  (PA2, ADC1_IN2)
// PIOS_ADC_PinGet(1) = battery current  (PA3, ADC1_IN3)
// PIOS_ADC_PinGet(2) = 5V rail sense    (PA4, ADC1_IN4)  - divided by 2 on board
// PIOS_ADC_PinGet(3) = RSSI             (PC1, ADC1_IN11)
//-------------------------
#define PIOS_DMA_PIN_CONFIG                                                                 \
{                                                                                           \
	{GPIOA, GPIO_Pin_2,     ADC_Channel_2},                 /* BATT_VOLTAGE_SENS */         \
	{GPIOA, GPIO_Pin_3,     ADC_Channel_3},                 /* BATT_CURRENT_SENS */         \
	{GPIOA, GPIO_Pin_4,     ADC_Channel_4},                 /* VDD_5V_SENS      */          \
	{GPIOC, GPIO_Pin_1,     ADC_Channel_11},                /* RSSI_IN          */          \
	{NULL,  0,              ADC_Channel_Vrefint},           /* Voltage reference */         \
	{NULL,  0,              ADC_Channel_TempSensor},        /* Temperature sensor */        \
}

#define PIOS_ADC_NUM_CHANNELS           6
#define PIOS_ADC_MAX_OVERSAMPLING       2
#define PIOS_ADC_USE_ADC2               0

//-------------------------
// USB
//-------------------------
#define PIOS_USB_MAX_DEVS                       1
#define PIOS_USB_ENABLED                        1 /* Should remove all references to this */
#define PIOS_USB_HID_MAX_DEVS                   1

#endif /* STM32F4XX_PIXRACER_H_ */
/**
 * @}
 * @}
 */
