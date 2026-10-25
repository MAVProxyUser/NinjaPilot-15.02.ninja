/**
 ******************************************************************************
 * @file       pios_board.c
 * @brief      Board initialisation for the mRo / AUAV PixRacer R12 (FMUv4).
 *
 * PHASE 1 - hardware bring-up.
 *
 * Everything that is board plumbing is live here: clocks, LEDs, both SPI
 * buses, the settings filesystem in internal flash, USB, the four usable
 * serial ports, servo outputs and RC input.  The IMU / magnetometer /
 * barometer drivers are not written yet; where they will be initialised is
 * marked with PIXRACER_TODO_SENSORS below so the sequencing (in particular
 * the sensor power rail and its settling delay) is already correct when they
 * land.
 *
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

/* Pull in the board-specific static HW definitions.
 * NOTE: THIS IS THE ONLY PLACE THAT SHOULD EVER INCLUDE THIS FILE
 */
#include "../board_hw_defs.c"

#include <pios.h>
#include <openpilot.h>
#include <uavobjectsinit.h>
#include "hwsettings.h"
#include "manualcontrolsettings.h"

/* Included here rather than from board_hw_defs.c: it depends on the UAVObject
 * headers above. */
#if defined(PIOS_INCLUDE_GCSRCVR)
#include "pios_gcsrcvr_priv.h"
#endif

#if defined(PIOS_INCLUDE_ADC)
#include "pios_adc_priv.h"
void PIOS_ADC_DMC_irq_handler(void);
void DMA2_Stream4_IRQHandler(void) __attribute__((alias("PIOS_ADC_DMC_irq_handler")));
struct pios_adc_cfg pios_adc_cfg = {
	.adc_dev = ADC1,
	.dma = {
		.irq = {
			.flags   = (DMA_FLAG_TCIF4 | DMA_FLAG_TEIF4 | DMA_FLAG_HTIF4),
			.init    = {
				.NVIC_IRQChannel                   = DMA2_Stream4_IRQn,
				.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_LOW,
				.NVIC_IRQChannelSubPriority        = 0,
				.NVIC_IRQChannelCmd                = ENABLE,
			},
		},
		.rx = {
			.channel = DMA2_Stream4,
			.init    = {
				.DMA_Channel            = DMA_Channel_0,
				.DMA_PeripheralBaseAddr = (uint32_t) & ADC1->DR
			},
		}
	},
	.half_flag = DMA_IT_HTIF4,
	.full_flag = DMA_IT_TCIF4,
};

void PIOS_ADC_DMC_irq_handler(void)
{
	/* Call into the generic code to handle the IRQ for this specific device */
	PIOS_ADC_DMA_Handler();
}
#endif	/* PIOS_INCLUDE_ADC */

#if defined(PIOS_INCLUDE_FLASH_INTERNAL)
#include "pios_flash_internal_priv.h"
#include "pios_flashfs_logfs_priv.h"

static const struct pios_flash_internal_cfg flash_internal_cfg = {
};

/*
 * Settings live in internal flash sectors 10 and 11 (0x080C0000, 2 x 128 KB).
 * PixRacer has no SPI NOR part for PIOS_Flash_Jedec to talk to; its FM25V02
 * FRAM on SPI2 would be the better home but needs a driver first.
 *
 * The two sectors give the log-structured filesystem two arenas to rotate
 * between, which is what it needs to survive a power cut mid-write.
 */
static const struct flashfs_logfs_cfg flashfs_internal_cfg = {
	.fs_magic      = 0x99abcdef,
	.total_fs_size = 0x00040000,	/* 256 KB - sectors 10 and 11 */
	.arena_size    = 0x00020000,	/* 128 KB - one flash sector per arena */
	.slot_size     = 0x00000100,	/* 256 bytes */

	/*
	 * Absolute address, not an offset.  logfs_get_addr() adds start_offset
	 * straight to the address it hands the flash driver, and the internal
	 * flash driver's sector table is in STM32 address space starting at
	 * 0x08000000.  Revo can use 0 here only because its filesystem lives on
	 * an SPI NOR chip whose own address space starts at 0.
	 */
	.start_offset  = 0x080C0000,	/* flash sector 10 */
	.sector_size   = 0x00020000,	/* 128 KB erase block */
	.page_size     = 0x00000100,	/* 256 bytes */
};
#endif	/* PIOS_INCLUDE_FLASH_INTERNAL */

/* ------------------------------------------------------------------------- *
 * Sensors
 *
 * All four are on SPI: two Invensense IMUs and the magnetometer on SPI1, the
 * barometer on SPI2.  Nothing here is on I2C, unlike Revo.
 * ------------------------------------------------------------------------- */

#if defined(PIOS_INCLUDE_INVENSENSE)
pios_invensense_t pios_mpu9250_id;
pios_invensense_t pios_icm20608_id;

/* The EXTI table wants a plain bool(void); the driver is handle-based, so each
 * chip gets a one-line trampoline. */
static bool PIOS_MPU9250_IRQHandler(void)
{
	return PIOS_INVENSENSE_IRQHandler(pios_mpu9250_id);
}

static bool PIOS_ICM20608_IRQHandler(void)
{
	return PIOS_INVENSENSE_IRQHandler(pios_icm20608_id);
}

/* MPU9250 data-ready on PD15 */
static const struct pios_exti_cfg pios_exti_mpu9250_cfg __exti_config = {
	.vector = PIOS_MPU9250_IRQHandler,
	.line = EXTI_Line15,
	.pin = {
		.gpio = GPIOD,
		.init = {
			.GPIO_Pin = GPIO_Pin_15,
			.GPIO_Speed = GPIO_Speed_100MHz,
			.GPIO_Mode = GPIO_Mode_IN,
			.GPIO_OType = GPIO_OType_OD,
			.GPIO_PuPd = GPIO_PuPd_NOPULL,
		},
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = EXTI15_10_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.exti = {
		.init = {
			.EXTI_Line = EXTI_Line15,
			.EXTI_Mode = EXTI_Mode_Interrupt,
			.EXTI_Trigger = EXTI_Trigger_Rising,
			.EXTI_LineCmd = ENABLE,
		},
	},
};

/* ICM-20608-G data-ready on PC14.  Shares EXTI15_10_IRQn with the MPU9250
 * above; PIOS_EXTI dispatches lines 10..15 individually inside that handler. */
static const struct pios_exti_cfg pios_exti_icm20608_cfg __exti_config = {
	.vector = PIOS_ICM20608_IRQHandler,
	.line = EXTI_Line14,
	.pin = {
		.gpio = GPIOC,
		.init = {
			.GPIO_Pin = GPIO_Pin_14,
			.GPIO_Speed = GPIO_Speed_100MHz,
			.GPIO_Mode = GPIO_Mode_IN,
			.GPIO_OType = GPIO_OType_OD,
			.GPIO_PuPd = GPIO_PuPd_NOPULL,
		},
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = EXTI15_10_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.exti = {
		.init = {
			.EXTI_Line = EXTI_Line14,
			.EXTI_Mode = EXTI_Mode_Interrupt,
			.EXTI_Trigger = EXTI_Trigger_Rising,
			.EXTI_LineCmd = ENABLE,
		},
	},
};

/*
 * Orientation: ArduPilot describes both IMUs on this board as
 * ROTATION_ROLL_180_YAW_90, which maps chip (x,y,z) to body (y,x,-z).  That is
 * precisely the transform OpenPilot already applies to go from the Invensense
 * datasheet frame to its own body frame, so the two cancel and the correct
 * setting is TOP_0DEG.  Setting anything else here would double-apply it.
 *
 * Bus speeds: prescaler 128 off the 84 MHz APB2 gives 656 kHz for configuration
 * registers, which these parts limit to about 1 MHz, and prescaler 16 gives
 * 5.25 MHz for the sensor-register burst, well inside their 20 MHz limit.
 */
static const struct pios_invensense_cfg pios_mpu9250_cfg = {
	.exti_cfg = &pios_exti_mpu9250_cfg,
	.type = PIOS_INVENSENSE_MPU9250,
	/* DLPF on -> 1 kHz base rate; divider 0 keeps all 1000 samples/s */
	.smpl_rate_div = 0,
	.int_cfg = PIOS_INVENSENSE_INT_CLR_ANYRD,
	.int_en = PIOS_INVENSENSE_INTEN_DATA_RDY,
	.user_ctl = PIOS_INVENSENSE_USERCTL_DIS_I2C,
	.pwr_mgmt_clk = PIOS_INVENSENSE_PWRMGMT_PLL_BEST,
	.accel_range = PIOS_INVENSENSE_ACCEL_8G,
	.gyro_range = PIOS_INVENSENSE_SCALE_2000_DEG,
	.filter = PIOS_INVENSENSE_LOWPASS_184_HZ,
	.orientation = PIOS_INVENSENSE_TOP_0DEG,
	.slow_prescaler = SPI_BaudRatePrescaler_128,
	.fast_prescaler = SPI_BaudRatePrescaler_16,
};

static const struct pios_invensense_cfg pios_icm20608_cfg = {
	.exti_cfg = &pios_exti_icm20608_cfg,
	.type = PIOS_INVENSENSE_ICM20608,
	.smpl_rate_div = 0,
	.int_cfg = PIOS_INVENSENSE_INT_CLR_ANYRD,
	.int_en = PIOS_INVENSENSE_INTEN_DATA_RDY,
	.user_ctl = PIOS_INVENSENSE_USERCTL_DIS_I2C,
	.pwr_mgmt_clk = PIOS_INVENSENSE_PWRMGMT_PLL_BEST,
	.accel_range = PIOS_INVENSENSE_ACCEL_8G,
	.gyro_range = PIOS_INVENSENSE_SCALE_2000_DEG,
	.filter = PIOS_INVENSENSE_LOWPASS_184_HZ,
	.orientation = PIOS_INVENSENSE_TOP_0DEG,
	.slow_prescaler = SPI_BaudRatePrescaler_128,
	.fast_prescaler = SPI_BaudRatePrescaler_16,
};
#endif /* PIOS_INCLUDE_INVENSENSE */

#if defined(PIOS_INCLUDE_HMC5X83)
/*
 * HMC5983 on SPI1.  Polled rather than interrupt driven - the MAG_DRDY line on
 * PE12 is left unused, matching how this driver is normally run.
 *
 * Note the R15 and later PixRacers fit a LIS3MDL here instead, which is a
 * different part entirely and would need its own driver.  R12 is HMC5983.
 */
pios_hmc5x83_dev_t pios_hmc5983_id;

static const struct pios_hmc5x83_cfg pios_hmc5983_cfg = {
	.M_ODR = PIOS_HMC5x83_ODR_75,
	.Meas_Conf = PIOS_HMC5x83_MEASCONF_NORMAL,
	.Gain = PIOS_HMC5x83_GAIN_1_9,
	.Mode = PIOS_HMC5x83_MODE_CONTINUOUS,
	.TempCompensation = true,	/* the 5983 has the temperature sensor the 5883 lacks */
	.Driver = &PIOS_HMC5x83_SPI_DRIVER,
};
#endif /* PIOS_INCLUDE_HMC5X83 */

#if defined(PIOS_INCLUDE_MS5611)
/* MS5611 on SPI2, sharing the bus with the FRAM. */
static const struct pios_ms5611_cfg pios_ms5611_cfg = {
	.oversampling = MS5611_OSR_512,
	.spi_prescaler = SPI_BaudRatePrescaler_8,
};
#endif /* PIOS_INCLUDE_MS5611 */

/* One slot per selectable receiver group.
 * NOTE: No slot in this map for NONE.
 */
uint32_t pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_NONE];

/* Which sensors answered at boot; see PIXRACER_SENSOR_* in the board header. */
uint32_t pios_bringup_sensors_found;

#define PIOS_COM_TELEM_RF_RX_BUF_LEN 512
#define PIOS_COM_TELEM_RF_TX_BUF_LEN 512

#define PIOS_COM_GPS_RX_BUF_LEN 32

#define PIOS_COM_TELEM_USB_RX_BUF_LEN 65
#define PIOS_COM_TELEM_USB_TX_BUF_LEN 65

#define PIOS_COM_BRIDGE_RX_BUF_LEN 65
#define PIOS_COM_BRIDGE_TX_BUF_LEN 12

#define PIOS_COM_AUX_RX_BUF_LEN 512
#define PIOS_COM_AUX_TX_BUF_LEN 512

#if defined(PIOS_INCLUDE_DEBUG_CONSOLE)
#define PIOS_COM_DEBUGCONSOLE_TX_BUF_LEN 40
uint32_t pios_com_debug_id;
#endif	/* PIOS_INCLUDE_DEBUG_CONSOLE */

uint32_t pios_com_gps_id = 0;
uint32_t pios_com_telem_usb_id = 0;
uint32_t pios_com_telem_rf_id = 0;
uint32_t pios_com_bridge_id = 0;
uint32_t pios_com_vcp_id = 0;
uint32_t pios_com_aux_id = 0;
uint32_t pios_packet_handler = 0;

/*
 * Setup a com port based on the passed cfg, driver and buffer sizes.
 * A tx buffer length of 0 makes the port receive-only.
 */
static void PIOS_Board_configure_com(const struct pios_usart_cfg *usart_port_cfg, size_t rx_buf_len, size_t tx_buf_len,
		const struct pios_com_driver *com_driver, uint32_t *pios_com_id)
{
	uint32_t pios_usart_id;
	if (PIOS_USART_Init(&pios_usart_id, usart_port_cfg)) {
		PIOS_Assert(0);
	}

	uint8_t * rx_buffer = (uint8_t *) pvPortMalloc(rx_buf_len);
	PIOS_Assert(rx_buffer);
	if (tx_buf_len != 0) {
		uint8_t * tx_buffer = (uint8_t *) pvPortMalloc(tx_buf_len);
		PIOS_Assert(tx_buffer);

		if (PIOS_COM_Init(pios_com_id, com_driver, pios_usart_id,
				rx_buffer, rx_buf_len,
				tx_buffer, tx_buf_len)) {
			PIOS_Assert(0);
		}
	} else {
		if (PIOS_COM_Init(pios_com_id, com_driver, pios_usart_id,
				rx_buffer, rx_buf_len,
				NULL, 0)) {
			PIOS_Assert(0);
		}
	}
}

#if defined(PIOS_INCLUDE_DSM)
/*
 * Staged for receiver-type selection.  RC input on this board is PPM only for
 * now: choosing between PPM, PWM, DSM and S.Bus needs a HwSettings field that
 * describes this board's single RC pin, and HwSettings currently carries Revo's
 * main/flexi port pair instead.  The board_hw_defs side is already done.
 */
static void __attribute__((unused)) PIOS_Board_configure_dsm(const struct pios_usart_cfg *usart_dsm_cfg, const struct pios_dsm_cfg *dsm_cfg,
		const struct pios_com_driver *usart_com_driver, enum pios_dsm_proto *proto,
		ManualControlSettingsChannelGroupsOptions channelgroup, uint8_t *bind)
{
	uint32_t pios_usart_dsm_id;
	if (PIOS_USART_Init(&pios_usart_dsm_id, usart_dsm_cfg)) {
		PIOS_Assert(0);
	}

	uint32_t pios_dsm_id;
	if (PIOS_DSM_Init(&pios_dsm_id, dsm_cfg, usart_com_driver,
			pios_usart_dsm_id, *proto, *bind)) {
		PIOS_Assert(0);
	}

	uint32_t pios_dsm_rcvr_id;
	if (PIOS_RCVR_Init(&pios_dsm_rcvr_id, &pios_dsm_rcvr_driver, pios_dsm_id)) {
		PIOS_Assert(0);
	}
	pios_rcvr_group_map[channelgroup] = pios_dsm_rcvr_id;
}
#endif	/* PIOS_INCLUDE_DSM */

#if defined(PIOS_INCLUDE_PWM)
/* Staged alongside PIOS_Board_configure_dsm above - see that comment. */
static void __attribute__((unused)) PIOS_Board_configure_pwm(const struct pios_pwm_cfg *pwm_cfg)
{
	uint32_t pios_pwm_id;
	PIOS_PWM_Init(&pios_pwm_id, pwm_cfg);

	uint32_t pios_pwm_rcvr_id;
	if (PIOS_RCVR_Init(&pios_pwm_rcvr_id, &pios_pwm_rcvr_driver, pios_pwm_id)) {
		PIOS_Assert(0);
	}
	pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_PWM] = pios_pwm_rcvr_id;
}
#endif	/* PIOS_INCLUDE_PWM */

#if defined(PIOS_INCLUDE_PPM)
static void PIOS_Board_configure_ppm(const struct pios_ppm_cfg *ppm_cfg)
{
	uint32_t pios_ppm_id;
	PIOS_PPM_Init(&pios_ppm_id, ppm_cfg);

	uint32_t pios_ppm_rcvr_id;
	if (PIOS_RCVR_Init(&pios_ppm_rcvr_id, &pios_ppm_rcvr_driver, pios_ppm_id)) {
		PIOS_Assert(0);
	}
	pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_PPM] = pios_ppm_rcvr_id;
}
#endif	/* PIOS_INCLUDE_PPM */

/* PIOS_Board_debug_puts lives in pixracer.c so the module-init loop can use it too. */
/*
 * Board-init progress, as a blink count rather than a colour.
 *
 * Colours were being misread across the bench - green+red reads as orange, and
 * "red" could mean three different stages.  A count of blue flashes is
 * unambiguous: whatever number it stops on is the step it did not get past.
 */
/*
 * Now that the CDC console works, board init narrates over it instead of
 * spending ~30 s blinking numbers.  The LED still shows progress, it just does
 * not stall to count any more.
 */
#define BRINGUP_STEP(n)	do {						\
		PIOS_Board_wdg_kick();					\
		PIOS_Board_boot_stage(((n) & 1) ? BRINGUP_LED_BLUE	\
					        : BRINGUP_LED_GREEN);	\
		PIOS_Board_debug_puts("boot step ");			\
		PIOS_Board_debug_putu(n);				\
		PIOS_Board_debug_puts("\r\n");			\
	} while (0)

static void PIOS_Board_report_sensor(const char *label, uint32_t present)
{
	PIOS_Board_debug_puts(label);
	PIOS_Board_debug_puts(present ? "ok\r\n" : "MISSING\r\n");
}

/**
 * Bring up the board's switched power rails.
 *
 * This has no Revo equivalent and it is the single easiest thing to leave out:
 * with VDD_SENSORS_EN low, every device on SPI1 and SPI2 is unpowered and the
 * buses read back as all-ones, which looks exactly like a wiring fault.
 *
 * Both rails are active high.  The Spektrum satellite rail on PE4 is active
 * LOW and is deliberately left off here - PIOS_Board_Init only powers it if a
 * DSM receiver is selected.
 */
/**
 * Park every SPI chip select as an output driven high, before anything is
 * powered.
 *
 * This has to happen before the sensor rail comes up, not as a side effect of
 * PIOS_SPI_Init afterwards.  The Invensense parts decide between SPI and I2C
 * from the state of their CS pin as they come out of power-on reset: bring the
 * rail up with CS floating and an MPU9250 can latch into I2C mode, after which
 * it will not answer on SPI at all and reads back as a WHO_AM_I of 0x00.
 *
 * The stock PX4 bootloader does drive these pins high - its hwdef lists all
 * five chip selects for exactly this reason - and that configuration survives
 * the jump into this firmware.  Relying on that would mean the board only
 * works when entered through that particular bootloader, so do it ourselves.
 *
 * GPIO_SetBits before GPIO_Init on each pin, so the output register is already
 * high when the pin stops being an input; the reverse order glitches CS low.
 */
static void PIOS_Board_park_chip_selects(void)
{
	const struct pios_spi_cfg * const buses[] = {
		&pios_spi_sensors_cfg,
		&pios_spi_baro_fram_cfg,
	};

	for (uint32_t b = 0; b < NELEMENTS(buses); b++) {
		for (uint32_t i = 0; i < buses[b]->slave_count; i++) {
			const struct stm32_gpio *ssel = &buses[b]->ssel[i];

			GPIO_SetBits(ssel->gpio, ssel->init.GPIO_Pin);
			GPIO_Init(ssel->gpio, (GPIO_InitTypeDef *)&ssel->init);
		}
	}
}

static void PIOS_Board_power_up_rails(void)
{
	/* Deselect everything before applying power - see above. */
	PIOS_Board_park_chip_selects();

	GPIO_Init(pios_pixracer_vdd_sensors_en.gpio,
		  (GPIO_InitTypeDef *)&pios_pixracer_vdd_sensors_en.init);
	GPIO_Init(pios_pixracer_vdd_periph_en.gpio,
		  (GPIO_InitTypeDef *)&pios_pixracer_vdd_periph_en.init);
	GPIO_Init(pios_pixracer_spektrum_pwr.gpio,
		  (GPIO_InitTypeDef *)&pios_pixracer_spektrum_pwr.init);

	GPIO_SetBits(pios_pixracer_vdd_sensors_en.gpio,
		     pios_pixracer_vdd_sensors_en.init.GPIO_Pin);
	GPIO_SetBits(pios_pixracer_vdd_periph_en.gpio,
		     pios_pixracer_vdd_periph_en.init.GPIO_Pin);
	/* Spektrum rail off (active low, so drive it high). */
	GPIO_SetBits(pios_pixracer_spektrum_pwr.gpio,
		     pios_pixracer_spektrum_pwr.init.GPIO_Pin);

	/* The MPU9250 needs ~100 ms after power-on before it will answer on SPI;
	 * the MS5611 needs far less.  Wait for the slowest part. */
	PIOS_DELAY_WaitmS(100);
}

/*
 * A reporter task that outranks everything else.
 *
 * Every stall so far has been a lower-priority task wedged behind a lock or a
 * busy loop, which takes the LEDs and the console down with it - so the board
 * goes quiet exactly when there is something to say.  This task sits above the
 * event dispatcher (3) and the telemetry tasks (2), does nothing but feed the
 * watchdog and blink a global progress code, and therefore keeps reporting no
 * matter what else is stuck.
 *
 * pios_bringup_progress is set at points of interest; the count of red
 * flashes every few seconds is its value.
 */
volatile uint32_t pios_bringup_progress;
/* Second number, blinked as two decimal digits (tens blue, ones green). */
volatile uint32_t pios_bringup_progress2;
void *pios_bringup_reporter_handle;

static void PIOS_Board_reporter_task(void *parameters)
{
	(void)parameters;

	for (;;) {
		uint32_t code = pios_bringup_progress;

		PIOS_Board_wdg_kick();

		if (code > 15) {
			code = 15;	/* keep it countable */
		}

		for (uint32_t i = 0; i < code; i++) {
			PIOS_Board_boot_stage(BRINGUP_LED_RED);
			vTaskDelay(80 / portTICK_RATE_MS);
			PIOS_Board_boot_stage(0);
			vTaskDelay(120 / portTICK_RATE_MS);
			PIOS_Board_wdg_kick();
		}

		/* Optional second number: tens on blue, then ones on green. */
		if (pios_bringup_progress2) {
			uint32_t v = pios_bringup_progress2;
			PIOS_Board_wdg_kick();
			vTaskDelay(600 / portTICK_RATE_MS);
			for (uint32_t i = 0; i < v / 10; i++) {
				PIOS_Board_boot_stage(BRINGUP_LED_BLUE);
				vTaskDelay(80 / portTICK_RATE_MS);
				PIOS_Board_boot_stage(0);
				PIOS_Board_wdg_kick();
				vTaskDelay(120 / portTICK_RATE_MS);
			}
			PIOS_Board_wdg_kick();
			vTaskDelay(400 / portTICK_RATE_MS);
			for (uint32_t i = 0; i < v % 10; i++) {
				PIOS_Board_boot_stage(BRINGUP_LED_GREEN);
				vTaskDelay(80 / portTICK_RATE_MS);
				PIOS_Board_boot_stage(0);
				PIOS_Board_wdg_kick();
				vTaskDelay(120 / portTICK_RATE_MS);
			}
		}

		for (int i = 0; i < 3; i++) {
			PIOS_Board_wdg_kick();
			vTaskDelay(500 / portTICK_RATE_MS);
		}
	}
}

/**
 * PIOS_Board_Init()
 * initializes all the core subsystems on this specific hardware
 * called from System/openpilot.c
 */
void PIOS_Board_Init(void) {

	/* Delay system */
	PIOS_DELAY_Init();

	const struct pios_board_info * bdinfo = &pios_board_info_blob;

#if defined(PIOS_INCLUDE_LED)
	const struct pios_led_cfg * led_cfg = PIOS_BOARD_HW_DEFS_GetLedCfg(bdinfo->board_rev);
	PIOS_Assert(led_cfg);
	PIOS_LED_Init(led_cfg);

#endif	/* PIOS_INCLUDE_LED */

	/* Stage 4: the scheduler is running and we are inside PIOS_Board_Init. */
	BRINGUP_STEP(1);	/* LED init */

	/* Power the sensor and peripheral rails before touching either SPI bus. */
	PIOS_Board_power_up_rails();

#if defined(PIOS_INCLUDE_SPI)
	/* SPI1: MPU9250, ICM-20608-G, HMC5983 */
	if (PIOS_SPI_Init(&pios_spi_sensors_id, &pios_spi_sensors_cfg)) {
		PIOS_DEBUG_Assert(0);
	}

	/* SPI2: MS5611 barometer, FM25V02 FRAM */
	if (PIOS_SPI_Init(&pios_spi_baro_fram_id, &pios_spi_baro_fram_cfg)) {
		PIOS_DEBUG_Assert(0);
	}
#endif	/* PIOS_INCLUDE_SPI */

	/* Stage 5: both SPI buses initialised. */
	BRINGUP_STEP(3);	/* SPI buses */

#if defined(PIOS_INCLUDE_FLASH_INTERNAL)
	uintptr_t flash_id;
	BRINGUP_STEP(4);	/* before settings filesystem */
	if (PIOS_Flash_Internal_Init(&flash_id, &flash_internal_cfg)) {
		PIOS_DEBUG_Assert(0);
	}
	uintptr_t fs_id;
	if (PIOS_FLASHFS_Logfs_Init(&fs_id, &flashfs_internal_cfg, &pios_internal_flash_driver, flash_id)) {
		PIOS_DEBUG_Assert(0);
	}
#endif	/* PIOS_INCLUDE_FLASH_INTERNAL */

	/* Initialize UAVObject libraries */
	EventDispatcherInitialize();
	BRINGUP_STEP(5);	/* before UAVObjects */
	UAVObjInitialize();
	HwSettingsInitialize();

#if defined(PIOS_INCLUDE_RTC)
	BRINGUP_STEP(6);	/* before RTC */
	PIOS_RTC_Init(&pios_rtc_main_cfg);
#endif

	/* Initialize the alarms library */
	AlarmsInitialize();

	/* Initialize the task monitor library */
	TaskMonitorInitialize();

	/* Set up pulse timers */
	BRINGUP_STEP(7);	/* before timers */
	PIOS_TIM_InitClock(&tim_1_cfg);
	PIOS_TIM_InitClock(&tim_4_cfg);
	PIOS_TIM_InitClock(&tim_8_cfg);

	/* IAP System Setup */
	BRINGUP_STEP(8);	/* before IAP */
	PIOS_IAP_Init();

#if defined(PIOS_INCLUDE_USB)
	/* Initialize board specific USB data */
	PIOS_USB_BOARD_DATA_Init();

	/* Flags to determine if various USB interfaces are advertised */
	bool usb_hid_present = false;
	bool __attribute__((unused)) usb_cdc_present = false;

#if defined(PIOS_INCLUDE_USB_CDC)
	if (PIOS_USB_DESC_HID_CDC_Init()) {
		PIOS_Assert(0);
	}
	usb_hid_present = true;
	usb_cdc_present = true;
#else
	if (PIOS_USB_DESC_HID_ONLY_Init()) {
		PIOS_Assert(0);
	}
	usb_hid_present = true;
#endif

	uint32_t pios_usb_id;
	BRINGUP_STEP(9);	/* before USB core */
	PIOS_USB_Init(&pios_usb_id, PIOS_BOARD_HW_DEFS_GetUsbCfg(bdinfo->board_rev));

#if defined(PIOS_INCLUDE_USB_CDC)
	uint8_t hwsettings_usb_vcpport;
	HwSettingsUSB_VCPPortGet(&hwsettings_usb_vcpport);

	if (!usb_cdc_present) {
		hwsettings_usb_vcpport = HWSETTINGS_USB_VCPPORT_DISABLED;
	}

	/*
	 * Bring-up: put the debug console on the USB CDC port.
	 *
	 * Everything this firmware has to say - the boot stages, the module
	 * indices, the free heap, the per-sensor probe result - has been going to
	 * UART7, which needs a separate 3.3 V adapter on the debug pads.  Routing
	 * it to the virtual serial port means the USB cable that is already
	 * plugged in carries it, and the board can be debugged with screen(1).
	 *
	 * This claims the CDC data interface, so the VCP cannot also be used for
	 * telemetry or the com bridge while this is in place.
	 */
	if (hwsettings_usb_vcpport != HWSETTINGS_USB_VCPPORT_USBTELEMETRY) {
		hwsettings_usb_vcpport = HWSETTINGS_USB_VCPPORT_DISABLED;
	}

#if defined(PIOS_INCLUDE_DEBUG_CONSOLE) && defined(PIOS_INCLUDE_COM)
	{
		/*
		 * Note this does NOT go through PIOS_Board_configure_com: that helper
		 * calls PIOS_USART_Init, and handing it a USB CDC config would walk a
		 * pios_usb_cdc_cfg as though it were a pios_usart_cfg.  The stock Revo
		 * target does exactly that in its VCP cases - harmless only because
		 * PIOS_INCLUDE_USB_CDC has never been enabled on an F4 board here.
		 */
	BRINGUP_STEP(10);	/* before USB CDC */
		uint32_t pios_usb_cdc_id;

		if (PIOS_USB_CDC_Init(&pios_usb_cdc_id, &pios_usb_cdc_cfg, pios_usb_id) == 0) {
			uint8_t *rx_buffer = (uint8_t *)pvPortMalloc(PIOS_COM_BRIDGE_RX_BUF_LEN);
			uint8_t *tx_buffer = (uint8_t *)pvPortMalloc(PIOS_COM_TELEM_USB_TX_BUF_LEN);

			if (rx_buffer && tx_buffer) {
				PIOS_COM_Init(&pios_com_debug_id, &pios_usb_cdc_com_driver,
					      pios_usb_cdc_id,
					      rx_buffer, PIOS_COM_BRIDGE_RX_BUF_LEN,
					      tx_buffer, PIOS_COM_TELEM_USB_TX_BUF_LEN);
			}
		}
		/* The CDC data interface is now spoken for. */
		hwsettings_usb_vcpport = HWSETTINGS_USB_VCPPORT_DISABLED;
	}
#endif

	switch (hwsettings_usb_vcpport) {
	case HWSETTINGS_USB_VCPPORT_DISABLED:
		break;
	case HWSETTINGS_USB_VCPPORT_USBTELEMETRY:
#if defined(PIOS_INCLUDE_COM)
		PIOS_Board_configure_com(&pios_usb_cdc_cfg, PIOS_COM_TELEM_USB_RX_BUF_LEN, PIOS_COM_TELEM_USB_TX_BUF_LEN,
				&pios_usb_cdc_com_driver, &pios_com_telem_usb_id);
#endif
		break;
	case HWSETTINGS_USB_VCPPORT_COMBRIDGE:
#if defined(PIOS_INCLUDE_COM)
		PIOS_Board_configure_com(&pios_usb_cdc_cfg, PIOS_COM_BRIDGE_RX_BUF_LEN, PIOS_COM_BRIDGE_TX_BUF_LEN,
				&pios_usb_cdc_com_driver, &pios_com_vcp_id);
#endif
		break;
	}
#endif	/* PIOS_INCLUDE_USB_CDC */

#if defined(PIOS_INCLUDE_USB_HID)
	uint8_t hwsettings_usb_hidport;
	HwSettingsUSB_HIDPortGet(&hwsettings_usb_hidport);

	if (!usb_hid_present) {
		hwsettings_usb_hidport = HWSETTINGS_USB_HIDPORT_DISABLED;
	} else {
		/*
		 * Force USB telemetry rather than trusting the stored setting.
		 * This is how the GCS talks to the board, and the settings
		 * filesystem on this port is new enough that a stale or empty
		 * HwSettings should not be able to leave the board mute on USB.
		 */
		hwsettings_usb_hidport = HWSETTINGS_USB_HIDPORT_USBTELEMETRY;
	}

	switch (hwsettings_usb_hidport) {
	case HWSETTINGS_USB_HIDPORT_DISABLED:
		break;
	case HWSETTINGS_USB_HIDPORT_USBTELEMETRY:
#if defined(PIOS_INCLUDE_COM)
		{
			/* No PIOS_Assert here: it expands to while(1) in a release
			 * build, so a failure would hang the board instead of just
			 * leaving USB telemetry unavailable. */
			uint32_t pios_usb_hid_id;
			if (PIOS_USB_HID_Init(&pios_usb_hid_id, &pios_usb_hid_cfg, pios_usb_id) == 0) {
				uint8_t *rx_buffer = (uint8_t *)pvPortMalloc(PIOS_COM_TELEM_USB_RX_BUF_LEN);
				uint8_t *tx_buffer = (uint8_t *)pvPortMalloc(PIOS_COM_TELEM_USB_TX_BUF_LEN);

				if (rx_buffer && tx_buffer) {
					PIOS_COM_Init(&pios_com_telem_usb_id,
						      &pios_usb_hid_com_driver, pios_usb_hid_id,
						      rx_buffer, PIOS_COM_TELEM_USB_RX_BUF_LEN,
						      tx_buffer, PIOS_COM_TELEM_USB_TX_BUF_LEN);
				}
			}
		}
#endif
		break;
	}
#endif	/* PIOS_INCLUDE_USB_HID */

	/*
	 * Start the USB device stack.
	 *
	 * This is what calls USBD_Init and pulls up D+; without it the OTG core is
	 * configured but never attaches, so the host sees nothing at all.  Missing
	 * this is why no build of this firmware has ever enumerated - the symptom
	 * is indistinguishable from a board that hung before reaching USB, which
	 * sent the search in the wrong direction for a long time.
	 */
	if (usb_hid_present || usb_cdc_present) {
		PIOS_USBHOOK_Activate();
		PIOS_Board_debug_puts("usb: device stack activated\r\n");
		PIOS_Board_debug_puts("last reset cause: ");
		PIOS_Board_debug_puts(PIOS_Board_reset_cause_str());
		PIOS_Board_debug_puts("\r\n");
	}
#endif	/* PIOS_INCLUDE_USB */

	/*
	 * Serial ports.
	 *
	 * PHASE 1 uses a fixed assignment rather than reading HwSettings: the
	 * HwSettings UAVObject carries Revo's port options (HwSettingsRM_*), which
	 * describe a main/flexi pair this board does not have.  A HwSettingsPXR_*
	 * group with TELEM1/TELEM2/GPS/AUX is the right fix and is deferred.
	 */
#if defined(PIOS_INCLUDE_COM_TELEM)
	BRINGUP_STEP(11);	/* before serial ports */
	PIOS_Board_configure_com(&pios_usart_telem1_cfg, PIOS_COM_TELEM_RF_RX_BUF_LEN, PIOS_COM_TELEM_RF_TX_BUF_LEN,
			&pios_usart_com_driver, &pios_com_telem_rf_id);
#endif

#if defined(PIOS_INCLUDE_GPS)
	PIOS_Board_configure_com(&pios_usart_gps_cfg, PIOS_COM_GPS_RX_BUF_LEN, 0,
			&pios_usart_com_driver, &pios_com_gps_id);
#endif

#if defined(PIOS_INCLUDE_COM_AUX)
	PIOS_Board_configure_com(&pios_usart_aux_cfg, PIOS_COM_AUX_RX_BUF_LEN, PIOS_COM_AUX_TX_BUF_LEN,
			&pios_usart_com_driver, &pios_com_aux_id);
#endif

#if defined(PIOS_INCLUDE_DEBUG_CONSOLE)
	/* Debug console on UART7.  Bring this up before the sensors so that a
	 * sensor that fails to probe can say so. */
	PIOS_Board_configure_com(&pios_usart_debug_cfg, 0, PIOS_COM_DEBUGCONSOLE_TX_BUF_LEN,
			&pios_usart_com_driver, &pios_com_debug_id);
#endif

#if defined(PIOS_INCLUDE_GCSRCVR)
	GCSReceiverInitialize();
	uint32_t pios_gcsrcvr_id;
	PIOS_GCSRCVR_Init(&pios_gcsrcvr_id);
	uint32_t pios_gcsrcvr_rcvr_id;
	if (PIOS_RCVR_Init(&pios_gcsrcvr_rcvr_id, &pios_gcsrcvr_rcvr_driver, pios_gcsrcvr_id)) {
		PIOS_Assert(0);
	}
	pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_GCS] = pios_gcsrcvr_rcvr_id;
#endif	/* PIOS_INCLUDE_GCSRCVR */

	/* Servo outputs - all six, always. */
	BRINGUP_STEP(12);	/* before servo */
	PIOS_Servo_Init(&pios_servo_cfg_out);

	/* RC input.  PC7 is shared between the PPM/PWM capture unit and the
	 * serial receiver UART, so only one of these can be live at a time. */
#if defined(PIOS_INCLUDE_PPM)
	PIOS_Board_configure_ppm(&pios_ppm_cfg);
#endif

#if defined(PIOS_INCLUDE_I2C)
	if (PIOS_I2C_Init(&pios_i2c_external_adapter_id, &pios_i2c_external_adapter_cfg)) {
		PIOS_DEBUG_Assert(0);
	}
#endif

	PIOS_DELAY_WaitmS(50);

#if defined(PIOS_INCLUDE_ADC)
	BRINGUP_STEP(13);	/* before ADC */
	PIOS_ADC_Init(&pios_adc_cfg);
#endif

	/*
	 * Sensors.  The rails they need have been up and settled since
	 * PIOS_Board_power_up_rails() ran at the top of this function.
	 *
	 * Nothing here asserts on failure.  PIOS_DEBUG_Assert is a no-op unless
	 * DEBUG is defined, and PIOS_Assert expands to while(1) - either way it
	 * is the wrong answer this early: an assert here hangs before USB
	 * enumerates, so a board with one dead sensor looks completely dead.
	 * Instead each probe result is recorded and reported over the debug
	 * console on UART7, which is already up by this point, and the Sensors
	 * module raises the alarm when its self-test fails.
	 */
	uint32_t sensors_found = 0;

	/*
	 * PIXRACER_ENABLE_SENSORS - off for now.
	 *
	 * USB is brought up earlier in this function than the sensors are, but
	 * every hang so far has been at or after the sensor probe, and a wedged
	 * board never finishes enumerating.  With this off, PIOS_Board_Init ends
	 * with USB, the serial ports and the settings filesystem up and nothing
	 * sensor-related running or interrupting - which is the shortest path to a
	 * board that can actually talk to the host.
	 *
	 * Note this also leaves the two IMU data-ready EXTI lines unconfigured.
	 * They fire at 1 kHz each once PIOS_INVENSENSE_Init runs, and an interrupt
	 * that arrives faster than it can be serviced starves every task without
	 * ever looking like a crash - worth eliminating before blaming anything
	 * else.
	 */
#if defined(PIXRACER_ENABLE_SENSORS)
#if defined(PIOS_INCLUDE_INVENSENSE)
	if (PIOS_INVENSENSE_Init(&pios_mpu9250_id, pios_spi_sensors_id,
				 PIXRACER_SPI1_SLAVE_MPU9250, &pios_mpu9250_cfg) == 0) {
		sensors_found |= PIXRACER_SENSOR_MPU9250;
	}

	if (PIOS_INVENSENSE_Init(&pios_icm20608_id, pios_spi_sensors_id,
				 PIXRACER_SPI1_SLAVE_ICM20608, &pios_icm20608_cfg) == 0) {
		sensors_found |= PIXRACER_SENSOR_ICM20608;
	}
#endif

#if defined(PIOS_INCLUDE_HMC5X83)
	pios_hmc5983_id = PIOS_HMC5x83_Init(&pios_hmc5983_cfg, pios_spi_sensors_id,
					    PIXRACER_SPI1_SLAVE_MAG);
	if (pios_hmc5983_id != 0) {
		sensors_found |= PIXRACER_SENSOR_HMC5983;
	}
#endif

#if defined(PIOS_INCLUDE_MS5611)
	PIOS_MS5611_SPI_Init(&pios_ms5611_cfg, pios_spi_baro_fram_id,
			     PIXRACER_SPI2_SLAVE_MS5611);
	if (PIOS_MS5611_Test() == 0) {
		sensors_found |= PIXRACER_SENSOR_MS5611;
	}
#endif

#else /* !PIXRACER_ENABLE_SENSORS */
	PIOS_Board_debug_puts("sensors: probe skipped (PIXRACER_ENABLE_SENSORS off)\r\n");
#endif

	pios_bringup_sensors_found = sensors_found;

	/* Highest priority so it keeps reporting through any lower-priority hang. */
	xTaskCreate(PIOS_Board_reporter_task, (signed char *)"pxrRep",
		    configMINIMAL_STACK_SIZE, NULL,
		    tskIDLE_PRIORITY + configMAX_PRIORITIES - 1,
		    &pios_bringup_reporter_handle);
	pios_bringup_progress = 1;	/* 1 = board init finished */

	/*
	 * Report over the debug console with plain strings, not DEBUG_PRINTF.
	 * PIOS_COM_SendFormattedString goes through vsprintf, which drags
	 * newlib's stdio - and its syscall stubs - into a flight controller
	 * that otherwise has none.  Nothing here needs formatting anyway.
	 */
	PIOS_Board_report_sensor("\r\nPixRacer sensors:\r\n  MPU9250  ",
				 sensors_found & PIXRACER_SENSOR_MPU9250);
	PIOS_Board_report_sensor("  ICM20608 ", sensors_found & PIXRACER_SENSOR_ICM20608);
	PIOS_Board_report_sensor("  HMC5983  ", sensors_found & PIXRACER_SENSOR_HMC5983);
	PIOS_Board_report_sensor("  MS5611   ", sensors_found & PIXRACER_SENSOR_MS5611);

	/* Stage 6: sensor probe complete - PIOS_Board_Init is essentially done.
	 * Once the System module starts, it takes the heartbeat LED over and
	 * this pattern is replaced by a blink. */
	BRINGUP_STEP(14);	/* board init complete */

	if (sensors_found != PIXRACER_SENSOR_ALL) {
		/* Everything on this board is on SPI behind a software-switched
		 * rail, so the usual cause of a clean sweep of MISSING is that
		 * VDD_SENSORS_EN never came up, not four dead chips. */
		PIOS_Board_debug_puts("  (nothing answers on SPI if VDD_SENSORS_EN is low)\r\n");
	}
}

/**
 * @}
 * @}
 */
