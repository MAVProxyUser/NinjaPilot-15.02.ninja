/**
 ******************************************************************************
 * @file       board_hw_defs.c
 * @brief      Hardware definitions for the mRo / AUAV PixRacer R12 (FMUv4).
 *
 * Pin assignments are transcribed from the ArduPilot hwdef for this board,
 * libraries/AP_HAL_ChibiOS/hwdef/Pixracer/hwdef.dat, which is the reference
 * that has been flown on this hardware.  Where a line here differs from Revo
 * it is because the board genuinely differs, and the difference is commented.
 *
 * The three big departures from Revo:
 *
 *   1. Both magnetometer and barometer are on SPI, not I2C.  The single I2C
 *      bus is brought out on the GPS connector for external devices only.
 *   2. SPI1 carries three chip selects (MPU9250, ICM-20608-G, HMC5983) and
 *      SPI2 carries two (MS5611, FM25V02 FRAM).  Revo only ever had one slave
 *      per bus.
 *   3. Sensor and peripheral power are software gated - see the GPIO section
 *      at the end of this file.  Nothing on either SPI bus answers until
 *      VDD_SENSORS_EN (PE3) is driven high.
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

#include <pios_config.h>
#include <pios_board_info.h>

#if defined(PIOS_INCLUDE_LED)

#include <pios_led_priv.h>

/*
 * Three discrete LEDs.  They sink through the MCU pin, so they light when the
 * pin is driven LOW - hence active_high = false.  ArduPilot expresses the same
 * thing as HAL_GPIO_LED_ON defaulting to 0 (see AP_HAL/AP_HAL_Boards.h).
 */
static const struct pios_led pios_leds[] = {
	[PIOS_LED_HEARTBEAT] = {
		.pin = {
			.gpio = GPIOB,
			.init = {
				.GPIO_Pin   = GPIO_Pin_1,	/* LED_GREEN */
				.GPIO_Speed = GPIO_Speed_50MHz,
				.GPIO_Mode  = GPIO_Mode_OUT,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
		},
		.active_high = false,
	},
	[PIOS_LED_ALARM] = {
		.pin = {
			.gpio = GPIOB,
			.init = {
				.GPIO_Pin   = GPIO_Pin_11,	/* LED_RED */
				.GPIO_Speed = GPIO_Speed_50MHz,
				.GPIO_Mode  = GPIO_Mode_OUT,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
		},
		.active_high = false,
	},
	[PIOS_LED_BLUE] = {
		.pin = {
			.gpio = GPIOB,
			.init = {
				.GPIO_Pin   = GPIO_Pin_3,	/* LED_BLUE */
				.GPIO_Speed = GPIO_Speed_50MHz,
				.GPIO_Mode  = GPIO_Mode_OUT,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
		},
		.active_high = false,
	},
};

static const struct pios_led_cfg pios_led_cfg = {
	.leds     = pios_leds,
	.num_leds = NELEMENTS(pios_leds),
};

const struct pios_led_cfg * PIOS_BOARD_HW_DEFS_GetLedCfg (uint32_t board_revision)
{
	/* Only one hardware revision is supported so far (R12). */
	(void)board_revision;
	return &pios_led_cfg;
}

#endif	/* PIOS_INCLUDE_LED */

#if defined(PIOS_INCLUDE_SPI)

#include <pios_spi_priv.h>

/*
 * SPI1 - sensor bus.  SCK PA5, MISO PA6, MOSI PA7.
 *
 * Three slaves share this bus:
 *   slave 0  MPU9250      CS PC2   DRDY PD15
 *   slave 1  ICM-20608-G  CS PC15  DRDY PC14
 *   slave 2  HMC5983      CS PE15  DRDY PE12   (LIS3MDL on R15 and later)
 *
 * PC14/PC15 are the OSC32 pins.  They are usable as plain GPIO here only
 * because nothing in this port enables the LSE oscillator: PIOS_RTC is clocked
 * from HSE (see the RTC section below).  Do not switch the RTC to LSE without
 * moving the ICM-20608 chip select.
 *
 * Prescaler 16 off an 84 MHz APB2 gives 5.25 MHz, which is inside the 1 MHz
 * limit these parts impose on register reads only if the driver slows down for
 * config; the sensor drivers drop to a slower prescaler for setup and use this
 * speed for burst sample reads.
 */
void PIOS_SPI_sensors_irq_handler(void);
void DMA2_Stream0_IRQHandler(void) __attribute__((alias("PIOS_SPI_sensors_irq_handler")));
void DMA2_Stream3_IRQHandler(void) __attribute__((alias("PIOS_SPI_sensors_irq_handler")));
static const struct pios_spi_cfg pios_spi_sensors_cfg = {
	.regs = SPI1,
	.remap = GPIO_AF_SPI1,
	.init   = {
		.SPI_Mode              = SPI_Mode_Master,
		.SPI_Direction         = SPI_Direction_2Lines_FullDuplex,
		.SPI_DataSize          = SPI_DataSize_8b,
		.SPI_NSS               = SPI_NSS_Soft,
		.SPI_FirstBit          = SPI_FirstBit_MSB,
		.SPI_CRCPolynomial     = 7,
		/* All three parts are SPI mode 3 (CPOL=1, CPHA=1). */
		.SPI_CPOL              = SPI_CPOL_High,
		.SPI_CPHA              = SPI_CPHA_2Edge,
		.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16,
	},
	.use_crc = false,
	.dma = {
		.irq = {
			.flags   = (DMA_IT_TCIF0 | DMA_IT_TEIF0 | DMA_IT_HTIF0),
			.init    = {
				.NVIC_IRQChannel                   = DMA2_Stream0_IRQn,
				.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
				.NVIC_IRQChannelSubPriority        = 0,
				.NVIC_IRQChannelCmd                = ENABLE,
			},
		},

		.rx = {
			.channel = DMA2_Stream0,
			.init    = {
				.DMA_Channel            = DMA_Channel_3,
				.DMA_PeripheralBaseAddr = (uint32_t)&(SPI1->DR),
				.DMA_DIR                = DMA_DIR_PeripheralToMemory,
				.DMA_PeripheralInc      = DMA_PeripheralInc_Disable,
				.DMA_MemoryInc          = DMA_MemoryInc_Enable,
				.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
				.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte,
				.DMA_Mode               = DMA_Mode_Normal,
				.DMA_Priority           = DMA_Priority_Medium,
				.DMA_FIFOMode           = DMA_FIFOMode_Disable,
				.DMA_MemoryBurst        = DMA_MemoryBurst_Single,
				.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single,
			},
		},
		.tx = {
			.channel = DMA2_Stream3,
			.init    = {
				.DMA_Channel            = DMA_Channel_3,
				.DMA_PeripheralBaseAddr = (uint32_t)&(SPI1->DR),
				.DMA_DIR                = DMA_DIR_MemoryToPeripheral,
				.DMA_PeripheralInc      = DMA_PeripheralInc_Disable,
				.DMA_MemoryInc          = DMA_MemoryInc_Enable,
				.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
				.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte,
				.DMA_Mode               = DMA_Mode_Normal,
				.DMA_Priority           = DMA_Priority_High,
				.DMA_FIFOMode           = DMA_FIFOMode_Disable,
				.DMA_MemoryBurst        = DMA_MemoryBurst_Single,
				.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single,
			},
		},
	},
	.sclk = {
		.gpio = GPIOA,
		.init = {
			.GPIO_Pin   = GPIO_Pin_5,
			.GPIO_Speed = GPIO_Speed_100MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
	.miso = {
		.gpio = GPIOA,
		.init = {
			.GPIO_Pin   = GPIO_Pin_6,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
	.mosi = {
		.gpio = GPIOA,
		.init = {
			.GPIO_Pin   = GPIO_Pin_7,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
	.slave_count = 3,
	.ssel = {
		{	/* PIOS_SPI_SENSORS_SLAVE_MPU9250 - PC2 */
			.gpio = GPIOC,
			.init = {
				.GPIO_Pin   = GPIO_Pin_2,
				.GPIO_Speed = GPIO_Speed_50MHz,
				.GPIO_Mode  = GPIO_Mode_OUT,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
		},
		{	/* PIOS_SPI_SENSORS_SLAVE_ICM20608 - PC15 */
			.gpio = GPIOC,
			.init = {
				.GPIO_Pin   = GPIO_Pin_15,
				.GPIO_Speed = GPIO_Speed_50MHz,
				.GPIO_Mode  = GPIO_Mode_OUT,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
		},
		{	/* PIOS_SPI_SENSORS_SLAVE_MAG - PE15 */
			.gpio = GPIOE,
			.init = {
				.GPIO_Pin   = GPIO_Pin_15,
				.GPIO_Speed = GPIO_Speed_50MHz,
				.GPIO_Mode  = GPIO_Mode_OUT,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
		},
	},
};

uint32_t pios_spi_sensors_id;
void PIOS_SPI_sensors_irq_handler(void)
{
	/* Call into the generic code to handle the IRQ for this specific device */
	PIOS_SPI_IRQ_Handler(pios_spi_sensors_id);
}

/*
 * SPI2 - barometer and FRAM.  SCK PB10, MISO PB14, MOSI PB15.
 *
 *   slave 0  MS5611 barometer  CS PD7
 *   slave 1  FM25V02 FRAM      CS PD10
 *
 * Note PB13, which would be the obvious SPI2_SCK, is CAN2_TX on production
 * boards; only the beta boards used it for SCK.  PB10 is the right pin.
 *
 * DMA1 Stream3/Stream4 channel 0 are the only SPI2 mappings on the F4 and are
 * unused elsewhere in this port.
 */
void PIOS_SPI_baro_fram_irq_handler(void);
void DMA1_Stream3_IRQHandler(void) __attribute__((alias("PIOS_SPI_baro_fram_irq_handler")));
void DMA1_Stream4_IRQHandler(void) __attribute__((alias("PIOS_SPI_baro_fram_irq_handler")));
static const struct pios_spi_cfg pios_spi_baro_fram_cfg = {
	.regs = SPI2,
	.remap = GPIO_AF_SPI2,
	.init   = {
		.SPI_Mode              = SPI_Mode_Master,
		.SPI_Direction         = SPI_Direction_2Lines_FullDuplex,
		.SPI_DataSize          = SPI_DataSize_8b,
		.SPI_NSS               = SPI_NSS_Soft,
		.SPI_FirstBit          = SPI_FirstBit_MSB,
		.SPI_CRCPolynomial     = 7,
		/* MS5611 and FM25V02 are both happy in mode 3. */
		.SPI_CPOL              = SPI_CPOL_High,
		.SPI_CPHA              = SPI_CPHA_2Edge,
		/* APB1 is 42 MHz, /8 = 5.25 MHz - well inside both parts' limits. */
		.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8,
	},
	.use_crc = false,
	.dma = {
		.irq = {
			.flags   = (DMA_IT_TCIF3 | DMA_IT_TEIF3 | DMA_IT_HTIF3),
			.init    = {
				.NVIC_IRQChannel                   = DMA1_Stream3_IRQn,
				.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
				.NVIC_IRQChannelSubPriority        = 0,
				.NVIC_IRQChannelCmd                = ENABLE,
			},
		},

		.rx = {
			.channel = DMA1_Stream3,
			.init    = {
				.DMA_Channel            = DMA_Channel_0,
				.DMA_PeripheralBaseAddr = (uint32_t)&(SPI2->DR),
				.DMA_DIR                = DMA_DIR_PeripheralToMemory,
				.DMA_PeripheralInc      = DMA_PeripheralInc_Disable,
				.DMA_MemoryInc          = DMA_MemoryInc_Enable,
				.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
				.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte,
				.DMA_Mode               = DMA_Mode_Normal,
				.DMA_Priority           = DMA_Priority_Medium,
				.DMA_FIFOMode           = DMA_FIFOMode_Disable,
				.DMA_MemoryBurst        = DMA_MemoryBurst_Single,
				.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single,
			},
		},
		.tx = {
			.channel = DMA1_Stream4,
			.init    = {
				.DMA_Channel            = DMA_Channel_0,
				.DMA_PeripheralBaseAddr = (uint32_t)&(SPI2->DR),
				.DMA_DIR                = DMA_DIR_MemoryToPeripheral,
				.DMA_PeripheralInc      = DMA_PeripheralInc_Disable,
				.DMA_MemoryInc          = DMA_MemoryInc_Enable,
				.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
				.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte,
				.DMA_Mode               = DMA_Mode_Normal,
				.DMA_Priority           = DMA_Priority_High,
				.DMA_FIFOMode           = DMA_FIFOMode_Disable,
				.DMA_MemoryBurst        = DMA_MemoryBurst_Single,
				.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single,
			},
		},
	},
	.sclk = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin   = GPIO_Pin_10,
			.GPIO_Speed = GPIO_Speed_100MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
	.miso = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin   = GPIO_Pin_14,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
	.mosi = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin   = GPIO_Pin_15,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
	.slave_count = 2,
	.ssel = {
		{	/* PIOS_SPI_BARO_FRAM_SLAVE_MS5611 - PD7 */
			.gpio = GPIOD,
			.init = {
				.GPIO_Pin   = GPIO_Pin_7,
				.GPIO_Speed = GPIO_Speed_50MHz,
				.GPIO_Mode  = GPIO_Mode_OUT,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
		},
		{	/* PIOS_SPI_BARO_FRAM_SLAVE_FRAM - PD10 */
			.gpio = GPIOD,
			.init = {
				.GPIO_Pin   = GPIO_Pin_10,
				.GPIO_Speed = GPIO_Speed_50MHz,
				.GPIO_Mode  = GPIO_Mode_OUT,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
		},
	},
};

uint32_t pios_spi_baro_fram_id;
void PIOS_SPI_baro_fram_irq_handler(void)
{
	/* Call into the generic code to handle the IRQ for this specific device */
	PIOS_SPI_IRQ_Handler(pios_spi_baro_fram_id);
}

#endif /* PIOS_INCLUDE_SPI */

#include <pios_usart_priv.h>

#ifdef PIOS_INCLUDE_COM_TELEM
/*
 * TELEM1 - USART2 on PD5/PD6.  RTS/CTS are pinned out on PD4/PD3 but PIOS has
 * no flow-control support, so they are left alone.
 */
static const struct pios_usart_cfg pios_usart_telem1_cfg = {
	.regs  = USART2,
	.remap = GPIO_AF_USART2,
	.init = {
		.USART_BaudRate = 57600,
		.USART_WordLength = USART_WordLength_8b,
		.USART_Parity = USART_Parity_No,
		.USART_StopBits = USART_StopBits_1,
		.USART_HardwareFlowControl = USART_HardwareFlowControl_None,
		.USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = USART2_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.rx = {
		.gpio = GPIOD,
		.init = {
			.GPIO_Pin   = GPIO_Pin_6,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
	.tx = {
		.gpio = GPIOD,
		.init = {
			.GPIO_Pin   = GPIO_Pin_5,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
};

/*
 * TELEM2 - USART3 on PD8/PD9.
 */
static const struct pios_usart_cfg pios_usart_telem2_cfg = {
	.regs  = USART3,
	.remap = GPIO_AF_USART3,
	.init = {
		.USART_BaudRate = 57600,
		.USART_WordLength = USART_WordLength_8b,
		.USART_Parity = USART_Parity_No,
		.USART_StopBits = USART_StopBits_1,
		.USART_HardwareFlowControl = USART_HardwareFlowControl_None,
		.USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = USART3_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.rx = {
		.gpio = GPIOD,
		.init = {
			.GPIO_Pin   = GPIO_Pin_9,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
	.tx = {
		.gpio = GPIOD,
		.init = {
			.GPIO_Pin   = GPIO_Pin_8,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
};
#endif /* PIOS_INCLUDE_COM_TELEM */

#ifdef PIOS_INCLUDE_GPS
/*
 * GPS - UART4 on PA0/PA1.  The same connector carries I2C1 for an external
 * compass, which is the usual place a GPS/compass combo unit lands.
 */
static const struct pios_usart_cfg pios_usart_gps_cfg = {
	.regs  = UART4,
	.remap = GPIO_AF_UART4,
	.init = {
		.USART_BaudRate = 57600,
		.USART_WordLength = USART_WordLength_8b,
		.USART_Parity = USART_Parity_No,
		.USART_StopBits = USART_StopBits_1,
		.USART_HardwareFlowControl = USART_HardwareFlowControl_None,
		.USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = UART4_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.rx = {
		.gpio = GPIOA,
		.init = {
			.GPIO_Pin   = GPIO_Pin_1,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
	.tx = {
		.gpio = GPIOA,
		.init = {
			.GPIO_Pin   = GPIO_Pin_0,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
};
#endif /* PIOS_INCLUDE_GPS */

#ifdef PIOS_INCLUDE_COM_AUX
/*
 * AUX / WiFi - USART1 on PB6/PB7.  On a stock PixRacer this goes to the
 * ESP8266 header.  PB4/PE2/PE5/PE6 are the ESP8266 GPIO2/GPIO0/PD/RST lines;
 * they are set up as plain GPIO in PIOS_Board_Init if the module is used.
 */
static const struct pios_usart_cfg pios_usart_aux_cfg = {
	.regs  = USART1,
	.remap = GPIO_AF_USART1,
	.init = {
		.USART_BaudRate = 57600,
		.USART_WordLength = USART_WordLength_8b,
		.USART_Parity = USART_Parity_No,
		.USART_StopBits = USART_StopBits_1,
		.USART_HardwareFlowControl = USART_HardwareFlowControl_None,
		.USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = USART1_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.rx = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin   = GPIO_Pin_7,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
	.tx = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin   = GPIO_Pin_6,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
};
#endif /* PIOS_INCLUDE_COM_AUX */

#if defined(PIOS_INCLUDE_DEBUG_CONSOLE)
/*
 * DEBUG console - UART7 on PE7/PE8, the pads marked as the debug port.
 *
 * UART7 and UART8 exist only on the F427/F429.  They were unreachable until the
 * ST peripheral library in this tree was moved off the F405-only V1.0.0, and
 * they still need the extended interrupt vector table in vectors_stm32f4xx.c
 * (UART7 is IRQ 82, past the F405's last entry at 81).
 */
static const struct pios_usart_cfg pios_usart_debug_cfg = {
	.regs  = UART7,
	.remap = GPIO_AF_UART7,
	.init = {
		.USART_BaudRate = 57600,
		.USART_WordLength = USART_WordLength_8b,
		.USART_Parity = USART_Parity_No,
		.USART_StopBits = USART_StopBits_1,
		.USART_HardwareFlowControl = USART_HardwareFlowControl_None,
		.USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = UART7_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_LOW,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.rx = {
		.gpio = GPIOE,
		.init = {
			.GPIO_Pin   = GPIO_Pin_7,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
	.tx = {
		.gpio = GPIOE,
		.init = {
			.GPIO_Pin   = GPIO_Pin_8,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
};
#endif /* PIOS_INCLUDE_DEBUG_CONSOLE */

#ifdef PIOS_INCLUDE_COM_FRSKY
/*
 * FrSky / SERIAL4 - UART8 on PE0/PE1.
 *
 * The TX line runs through an inverter controlled by PA10.  ArduPilot parks
 * that pin HIGH with POL(0), i.e. driving it LOW flips to the opposite of the
 * default polarity.  Default here is inverted, which is what S.Port wants.
 */
static const struct pios_usart_cfg pios_usart_frsky_cfg = {
	.regs  = UART8,
	.remap = GPIO_AF_UART8,
	.init = {
		.USART_BaudRate = 57600,
		.USART_WordLength = USART_WordLength_8b,
		.USART_Parity = USART_Parity_No,
		.USART_StopBits = USART_StopBits_1,
		.USART_HardwareFlowControl = USART_HardwareFlowControl_None,
		.USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = UART8_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.rx = {
		.gpio = GPIOE,
		.init = {
			.GPIO_Pin   = GPIO_Pin_0,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
	.tx = {
		.gpio = GPIOE,
		.init = {
			.GPIO_Pin   = GPIO_Pin_1,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
};

/* UART8 TX polarity control, PA10.  Driven HIGH = default (inverted) polarity. */
const struct stm32_gpio pios_pixracer_uart8_txinv = {
	.gpio = GPIOA,
	.init = {
		.GPIO_Pin   = GPIO_Pin_10,
		.GPIO_Speed = GPIO_Speed_2MHz,
		.GPIO_Mode  = GPIO_Mode_OUT,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd  = GPIO_PuPd_NOPULL
	},
};
#endif /* PIOS_INCLUDE_COM_FRSKY */

/*
 * Serial receivers (DSM / S.Bus) share the single RC input pin PC7 with the
 * PPM/PWM decoder.  PC7 is USART6_RX in AF8 and TIM8_CH2 in AF3, so the
 * receiver type chosen at runtime decides which of the two is configured -
 * exactly the way Revo shares its flexi port.
 *
 * There is no USART6_TX pin routed on this board.  PC6 would be the hardware
 * TX but the ArduPilot hwdef leaves it unassigned, so it is configured as a
 * high-impedance input here: the struct needs a tx entry, and we must not
 * drive a net whose function is unknown.
 */
#define PIXRACER_RC_TX_STUB						\
	.tx = {								\
		.gpio = GPIOC,						\
		.init = {						\
			.GPIO_Pin   = GPIO_Pin_6,			\
			.GPIO_Speed = GPIO_Speed_2MHz,			\
			.GPIO_Mode  = GPIO_Mode_IN,			\
			.GPIO_OType = GPIO_OType_PP,			\
			.GPIO_PuPd  = GPIO_PuPd_NOPULL			\
		},							\
	}

#define PIXRACER_RC_RX_PIN						\
	.rx = {								\
		.gpio = GPIOC,						\
		.init = {						\
			.GPIO_Pin   = GPIO_Pin_7,			\
			.GPIO_Speed = GPIO_Speed_2MHz,			\
			.GPIO_Mode  = GPIO_Mode_AF,			\
			.GPIO_OType = GPIO_OType_PP,			\
			.GPIO_PuPd  = GPIO_PuPd_UP			\
		},							\
	}

#ifdef PIOS_INCLUDE_DSM
#include <pios_dsm_priv.h>
static const struct pios_usart_cfg pios_usart_dsm_cfg = {
	.regs  = USART6,
	.remap = GPIO_AF_USART6,
	.init = {
		.USART_BaudRate = 115200,
		.USART_WordLength = USART_WordLength_8b,
		.USART_Parity = USART_Parity_No,
		.USART_StopBits = USART_StopBits_1,
		.USART_HardwareFlowControl = USART_HardwareFlowControl_None,
		.USART_Mode = USART_Mode_Rx,
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = USART6_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	PIXRACER_RC_RX_PIN,
	PIXRACER_RC_TX_STUB,
};

/*
 * Spektrum satellite bind.  PB0 is the satellite's signal line brought back as
 * a GPIO so the bind pulse train can be generated, and PE4 gates the
 * satellite's 3.3V supply - active LOW, per HAL_SPEKTRUM_PWR_ENABLED 0 in the
 * ArduPilot hwdef.  Power sequencing for bind lives in PIOS_Board_Init.
 */
static const struct pios_dsm_cfg pios_dsm_cfg = {
	.bind = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin   = GPIO_Pin_0,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_IN,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_NOPULL
		},
	},
};
#endif	/* PIOS_INCLUDE_DSM */

#if defined(PIOS_INCLUDE_SBUS)
#include <pios_sbus_priv.h>
static const struct pios_usart_cfg pios_usart_sbus_cfg = {
	.regs  = USART6,
	.remap = GPIO_AF_USART6,
	.init = {
		.USART_BaudRate            = 100000,
		.USART_WordLength          = USART_WordLength_8b,
		.USART_Parity              = USART_Parity_Even,
		.USART_StopBits            = USART_StopBits_2,
		.USART_HardwareFlowControl = USART_HardwareFlowControl_None,
		.USART_Mode                = USART_Mode_Rx,
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = USART6_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	PIXRACER_RC_RX_PIN,
	PIXRACER_RC_TX_STUB,
};

/*
 * S.Bus is inverted serial and this board has a hardware inverter on the RC
 * input, enabled by driving PC13 high.  The ArduPilot hwdef parks it LOW
 * (inverter bypassed) for non-inverted protocols, which matches
 * gpio_inv_disable below.
 */
static const struct pios_sbus_cfg pios_sbus_cfg = {
	.inv = {
		.gpio = GPIOC,
		.init = {
			.GPIO_Pin   = GPIO_Pin_13,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_OUT,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
	},
	.gpio_inv_enable  = Bit_SET,
	.gpio_inv_disable = Bit_RESET,
	.gpio_clk_func    = RCC_AHB1PeriphClockCmd,
	.gpio_clk_periph  = RCC_AHB1Periph_GPIOC,
};
#endif	/* PIOS_INCLUDE_SBUS */

#if defined(PIOS_INCLUDE_COM)
#include <pios_com_priv.h>
#endif /* PIOS_INCLUDE_COM */

#if defined(PIOS_INCLUDE_I2C)

#include <pios_i2c_priv.h>

/*
 * The one and only I2C bus, PB8/PB9, pinned out on the GPS connector.  Nothing
 * on-board hangs off it: unlike Revo, the magnetometer and barometer are both
 * on SPI here.
 */
void PIOS_I2C_external_adapter_ev_irq_handler(void);
void PIOS_I2C_external_adapter_er_irq_handler(void);
void I2C1_EV_IRQHandler() __attribute__ ((alias("PIOS_I2C_external_adapter_ev_irq_handler")));
void I2C1_ER_IRQHandler() __attribute__ ((alias("PIOS_I2C_external_adapter_er_irq_handler")));

static const struct pios_i2c_adapter_cfg pios_i2c_external_adapter_cfg = {
	.regs = I2C1,
	.remap = GPIO_AF_I2C1,
	.init = {
		.I2C_Mode = I2C_Mode_I2C,
		.I2C_OwnAddress1 = 0,
		.I2C_Ack = I2C_Ack_Enable,
		.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit,
		.I2C_DutyCycle = I2C_DutyCycle_2,
		.I2C_ClockSpeed = 400000,	/* bits/s */
	},
	.transfer_timeout_ms = 50,
	.scl = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin = GPIO_Pin_8,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_OType = GPIO_OType_OD,
			.GPIO_PuPd  = GPIO_PuPd_NOPULL,
		},
	},
	.sda = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin = GPIO_Pin_9,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_OType = GPIO_OType_OD,
			.GPIO_PuPd  = GPIO_PuPd_NOPULL,
		},
	},
	.event = {
		.flags = 0,
		.init = {
			.NVIC_IRQChannel = I2C1_EV_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGHEST,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.error = {
		.flags = 0,
		.init = {
			.NVIC_IRQChannel = I2C1_ER_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGHEST,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
};

uint32_t pios_i2c_external_adapter_id;
void PIOS_I2C_external_adapter_ev_irq_handler(void)
{
	PIOS_I2C_EV_IRQ_Handler(pios_i2c_external_adapter_id);
}

void PIOS_I2C_external_adapter_er_irq_handler(void)
{
	PIOS_I2C_ER_IRQ_Handler(pios_i2c_external_adapter_id);
}

#endif /* PIOS_INCLUDE_I2C */

#if defined(PIOS_INCLUDE_RTC)
/*
 * Realtime Clock (RTC)
 *
 * Clocked from HSE, NOT from LSE.  That is deliberate and load-bearing: the
 * LSE pins are PC14/PC15, and PC15 is the ICM-20608 chip select on this board.
 *
 * HSE is 24 MHz here rather than Revo's 8 MHz, so the RTC predivider is /24
 * instead of /8 to land on the same 1 MHz and keep the prescaler below valid.
 */
#include <pios_rtc_priv.h>

void PIOS_RTC_IRQ_Handler (void);
void RTC_WKUP_IRQHandler() __attribute__ ((alias ("PIOS_RTC_IRQ_Handler")));
static const struct pios_rtc_cfg pios_rtc_main_cfg = {
	.clksrc = RCC_RTCCLKSource_HSE_Div24,	/* 24 MHz / 24 = 1 MHz */
	.prescaler = 100,
	.irq = {
		.init = {
			.NVIC_IRQChannel                   = RTC_WKUP_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
			.NVIC_IRQChannelSubPriority        = 0,
			.NVIC_IRQChannelCmd                = ENABLE,
		},
	},
};

void PIOS_RTC_IRQ_Handler (void)
{
	PIOS_RTC_irq_handler ();
}

#endif

#include "pios_tim_priv.h"

/*
 * On the F4 a timer on APB1 (prescaler 4) is clocked at SYSCLK/2 and one on
 * APB2 (prescaler 2) at SYSCLK.  PIOS_PERIPHERAL_APBx_CLOCK already encode
 * that doubling, so the prescalers below give a 1 MHz tick on both buses.
 */
static const TIM_TimeBaseInitTypeDef tim_apb1_time_base = {
	.TIM_Prescaler = (PIOS_PERIPHERAL_APB1_CLOCK / 1000000) - 1,
	.TIM_ClockDivision = TIM_CKD_DIV1,
	.TIM_CounterMode = TIM_CounterMode_Up,
	.TIM_Period = 0xFFFF,
	.TIM_RepetitionCounter = 0x0000,
};

static const TIM_TimeBaseInitTypeDef tim_apb2_time_base = {
	.TIM_Prescaler = (PIOS_PERIPHERAL_APB2_CLOCK / 1000000) - 1,
	.TIM_ClockDivision = TIM_CKD_DIV1,
	.TIM_CounterMode = TIM_CounterMode_Up,
	.TIM_Period = 0xFFFF,
	.TIM_RepetitionCounter = 0x0000,
};

/* TIM1 drives servo outputs 1-4.  It is an advanced-control timer, so its
 * outputs stay disabled until TIM_CtrlPWMOutputs() runs - PIOS_Servo_Setup()
 * already does that for every channel it configures. */
static const struct pios_tim_clock_cfg tim_1_cfg = {
	.timer = TIM1,
	.time_base_init = &tim_apb2_time_base,
	.irq = {
		.init = {
			.NVIC_IRQChannel                   = TIM1_CC_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
			.NVIC_IRQChannelSubPriority        = 0,
			.NVIC_IRQChannelCmd                = ENABLE,
		},
	},
};

/* TIM4 drives servo outputs 5-6. */
static const struct pios_tim_clock_cfg tim_4_cfg = {
	.timer = TIM4,
	.time_base_init = &tim_apb1_time_base,
	.irq = {
		.init = {
			.NVIC_IRQChannel                   = TIM4_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
			.NVIC_IRQChannelSubPriority        = 0,
			.NVIC_IRQChannelCmd                = ENABLE,
		},
	},
};

/* TIM8 captures the single RC input on PC7. */
static const struct pios_tim_clock_cfg tim_8_cfg = {
	.timer = TIM8,
	.time_base_init = &tim_apb2_time_base,
	.irq = {
		.init = {
			.NVIC_IRQChannel                   = TIM8_CC_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
			.NVIC_IRQChannelSubPriority        = 0,
			.NVIC_IRQChannelCmd                = ENABLE,
		},
	},
};

/**
 * Servo outputs.
 *
 * The connector order runs 1..6 but the TIM1 channels run backwards across the
 * pins (PE14 is CH4, PE9 is CH1); this table is in connector order, matching
 * the PWM(n) numbering in the ArduPilot hwdef.
 */
#include <pios_servo_priv.h>
static const struct pios_tim_channel pios_tim_servoport_all_pins[] = {
	{	/* PWM 1 - PE14, TIM1_CH4 */
		.timer = TIM1,
		.timer_chan = TIM_Channel_4,
		.pin = {
			.gpio = GPIOE,
			.init = {
				.GPIO_Pin = GPIO_Pin_14,
				.GPIO_Speed = GPIO_Speed_2MHz,
				.GPIO_Mode  = GPIO_Mode_AF,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
			.pin_source = GPIO_PinSource14,
		},
		.remap = GPIO_AF_TIM1,
	},
	{	/* PWM 2 - PE13, TIM1_CH3 */
		.timer = TIM1,
		.timer_chan = TIM_Channel_3,
		.pin = {
			.gpio = GPIOE,
			.init = {
				.GPIO_Pin = GPIO_Pin_13,
				.GPIO_Speed = GPIO_Speed_2MHz,
				.GPIO_Mode  = GPIO_Mode_AF,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
			.pin_source = GPIO_PinSource13,
		},
		.remap = GPIO_AF_TIM1,
	},
	{	/* PWM 3 - PE11, TIM1_CH2 */
		.timer = TIM1,
		.timer_chan = TIM_Channel_2,
		.pin = {
			.gpio = GPIOE,
			.init = {
				.GPIO_Pin = GPIO_Pin_11,
				.GPIO_Speed = GPIO_Speed_2MHz,
				.GPIO_Mode  = GPIO_Mode_AF,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
			.pin_source = GPIO_PinSource11,
		},
		.remap = GPIO_AF_TIM1,
	},
	{	/* PWM 4 - PE9, TIM1_CH1 */
		.timer = TIM1,
		.timer_chan = TIM_Channel_1,
		.pin = {
			.gpio = GPIOE,
			.init = {
				.GPIO_Pin = GPIO_Pin_9,
				.GPIO_Speed = GPIO_Speed_2MHz,
				.GPIO_Mode  = GPIO_Mode_AF,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
			.pin_source = GPIO_PinSource9,
		},
		.remap = GPIO_AF_TIM1,
	},
	{	/* PWM 5 - PD13, TIM4_CH2 */
		.timer = TIM4,
		.timer_chan = TIM_Channel_2,
		.pin = {
			.gpio = GPIOD,
			.init = {
				.GPIO_Pin = GPIO_Pin_13,
				.GPIO_Speed = GPIO_Speed_2MHz,
				.GPIO_Mode  = GPIO_Mode_AF,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
			.pin_source = GPIO_PinSource13,
		},
		.remap = GPIO_AF_TIM4,
	},
	{	/* PWM 6 - PD14, TIM4_CH3 */
		.timer = TIM4,
		.timer_chan = TIM_Channel_3,
		.pin = {
			.gpio = GPIOD,
			.init = {
				.GPIO_Pin = GPIO_Pin_14,
				.GPIO_Speed = GPIO_Speed_2MHz,
				.GPIO_Mode  = GPIO_Mode_AF,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
			.pin_source = GPIO_PinSource14,
		},
		.remap = GPIO_AF_TIM4,
	},
};

const struct pios_servo_cfg pios_servo_cfg_out = {
	.tim_oc_init = {
		.TIM_OCMode = TIM_OCMode_PWM1,
		.TIM_OutputState = TIM_OutputState_Enable,
		.TIM_OutputNState = TIM_OutputNState_Disable,
		.TIM_Pulse = PIOS_SERVOS_INITIAL_POSITION,
		.TIM_OCPolarity = TIM_OCPolarity_High,
		.TIM_OCNPolarity = TIM_OCPolarity_High,
		.TIM_OCIdleState = TIM_OCIdleState_Reset,
		.TIM_OCNIdleState = TIM_OCNIdleState_Reset,
	},
	.channels = pios_tim_servoport_all_pins,
	.num_channels = NELEMENTS(pios_tim_servoport_all_pins),
};

/*
 * RC input.
 *
 * Unlike Revo there is exactly one RC input pin.  PC7 is TIM8_CH2 for PPM and
 * PWM, and USART6_RX for S.Bus/DSM - the two uses are mutually exclusive and
 * are selected by the configured receiver type at init time.
 */
#if defined(PIOS_INCLUDE_PWM) || defined(PIOS_INCLUDE_PPM)
#include <pios_pwm_priv.h>
static const struct pios_tim_channel pios_tim_rcvrport_all_channels[] = {
	{
		.timer = TIM8,
		.timer_chan = TIM_Channel_2,
		.pin = {
			.gpio = GPIOC,
			.init = {
				.GPIO_Pin = GPIO_Pin_7,
				.GPIO_Speed = GPIO_Speed_2MHz,
				.GPIO_Mode  = GPIO_Mode_AF,
				.GPIO_OType = GPIO_OType_PP,
				/* ArduPilot pulls this down; keep the idle level defined
				 * so a disconnected receiver reads as no pulses. */
				.GPIO_PuPd  = GPIO_PuPd_DOWN
			},
			.pin_source = GPIO_PinSource7,
		},
		.remap = GPIO_AF_TIM8,
	},
};

const struct pios_pwm_cfg pios_pwm_cfg = {
	.tim_ic_init = {
		.TIM_ICPolarity = TIM_ICPolarity_Rising,
		.TIM_ICSelection = TIM_ICSelection_DirectTI,
		.TIM_ICPrescaler = TIM_ICPSC_DIV1,
		.TIM_ICFilter = 0x0,
	},
	.channels = pios_tim_rcvrport_all_channels,
	.num_channels = NELEMENTS(pios_tim_rcvrport_all_channels),
};
#endif

#if defined(PIOS_INCLUDE_PPM)
#include <pios_ppm_priv.h>
static const struct pios_ppm_cfg pios_ppm_cfg = {
	.tim_ic_init = {
		.TIM_ICPolarity = TIM_ICPolarity_Rising,
		.TIM_ICSelection = TIM_ICSelection_DirectTI,
		.TIM_ICPrescaler = TIM_ICPSC_DIV1,
		.TIM_ICFilter = 0x0,
		.TIM_Channel = TIM_Channel_2,	/* PC7 is TIM8_CH2, not CH1 */
	},
	.channels = &pios_tim_rcvrport_all_channels[0],
	.num_channels = 1,
};
#endif /* PIOS_INCLUDE_PPM */

/* NOTE: pios_gcsrcvr_priv.h is deliberately NOT included here.  It pulls in the
 * generated gcsreceiver.h, which needs uavobjectmanager.h, and this file is
 * included at the very top of pios_board.c - before <openpilot.h>.  It is
 * included from pios_board.c instead, after the UAVObject headers. */

#if defined(PIOS_INCLUDE_RCVR)
#include "pios_rcvr_priv.h"
#endif /* PIOS_INCLUDE_RCVR */

#if defined(PIOS_INCLUDE_USB)
#include "pios_usb_priv.h"

/*
 * USB OTG FS on PA11/PA12.  PA9 is VBUS sense - a plain input, unlike Revo
 * where the sense pin moved between board revisions.
 */
static const struct pios_usb_cfg pios_usb_main_cfg = {
	.irq = {
		.init    = {
			.NVIC_IRQChannel                   = OTG_FS_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_LOW,
			.NVIC_IRQChannelSubPriority        = 3,
			.NVIC_IRQChannelCmd                = ENABLE,
		},
	},
	.vsense = {
		.gpio = GPIOA,
		.init = {
			.GPIO_Pin   = GPIO_Pin_9,
			.GPIO_Speed = GPIO_Speed_25MHz,
			.GPIO_Mode  = GPIO_Mode_IN,
			.GPIO_OType = GPIO_OType_OD,
		},
	},
	/*
	 * Do not let the VBUS pin gate transmits.  The OTG core's hardware VBUS
	 * sensing is disabled, so PA9 is only ever read by software, and the
	 * device having been configured by the host is a far better indication
	 * that a cable is present than a GPIO level this port has never verified.
	 * Enumeration works while every transmit is dropped otherwise, which is
	 * an unpleasant failure to diagnose.
	 */
	.vsense_ignore = true,
};

const struct pios_usb_cfg * PIOS_BOARD_HW_DEFS_GetUsbCfg (uint32_t board_revision)
{
	(void)board_revision;
	return &pios_usb_main_cfg;
}

#include "pios_usb_board_data_priv.h"
#include "pios_usb_desc_hid_cdc_priv.h"
#include "pios_usb_desc_hid_only_priv.h"
#include "pios_usbhook.h"

#endif	/* PIOS_INCLUDE_USB */

/*
 * Board power and discrete control pins.
 *
 * THIS IS THE PART THAT BITES.  On Revo every sensor is permanently powered;
 * on PixRacer the sensor and peripheral rails are switched by the MCU, and
 * both SPI buses are electrically dead until PIOS_Board_Init drives these.
 *
 *   PE3  VDD_SENSORS_EN  drive HIGH - powers the MPU9250/ICM20608/HMC5983/MS5611
 *   PC5  VDD_PERIPH_EN   drive HIGH - powers the peripheral rail
 *   PE4  SPEKTRUM_PWR    ACTIVE LOW - drive LOW to power a Spektrum satellite
 *   PC3  LED_SAFETY      safety-switch LED
 *   PC4  SAFETY_IN       safety switch input, external pull-down
 *   PB5  VDD_BRICK_VALID power brick present, external pull-down
 *   PC0  VBUS_VALID      USB power valid, external pull-down
 *   PB2  BOOT1           strap, input only
 */
const struct stm32_gpio pios_pixracer_vdd_sensors_en = {
	.gpio = GPIOE,
	.init = {
		.GPIO_Pin   = GPIO_Pin_3,
		.GPIO_Speed = GPIO_Speed_2MHz,
		.GPIO_Mode  = GPIO_Mode_OUT,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd  = GPIO_PuPd_NOPULL
	},
};

const struct stm32_gpio pios_pixracer_vdd_periph_en = {
	.gpio = GPIOC,
	.init = {
		.GPIO_Pin   = GPIO_Pin_5,
		.GPIO_Speed = GPIO_Speed_2MHz,
		.GPIO_Mode  = GPIO_Mode_OUT,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd  = GPIO_PuPd_NOPULL
	},
};

const struct stm32_gpio pios_pixracer_spektrum_pwr = {
	.gpio = GPIOE,
	.init = {
		.GPIO_Pin   = GPIO_Pin_4,
		.GPIO_Speed = GPIO_Speed_2MHz,
		.GPIO_Mode  = GPIO_Mode_OUT,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd  = GPIO_PuPd_NOPULL
	},
};

const struct stm32_gpio pios_pixracer_safety_led = {
	.gpio = GPIOC,
	.init = {
		.GPIO_Pin   = GPIO_Pin_3,
		.GPIO_Speed = GPIO_Speed_2MHz,
		.GPIO_Mode  = GPIO_Mode_OUT,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd  = GPIO_PuPd_NOPULL
	},
};

const struct stm32_gpio pios_pixracer_safety_in = {
	.gpio = GPIOC,
	.init = {
		.GPIO_Pin   = GPIO_Pin_4,
		.GPIO_Speed = GPIO_Speed_2MHz,
		.GPIO_Mode  = GPIO_Mode_IN,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd  = GPIO_PuPd_DOWN
	},
};

#if defined(PIOS_INCLUDE_COM_MSG)
#include <pios_com_msg_priv.h>
#endif /* PIOS_INCLUDE_COM_MSG */

/*
 * USB endpoint layout.  Identical to Revo - the descriptors are generated by
 * the shared pios_usb_desc_* code, so the interface and endpoint numbers must
 * match what those emit.
 */
#if defined(PIOS_INCLUDE_USB_HID)
#include <pios_usb_hid_priv.h>

/*
 * These interface numbers must match the descriptor emitted by
 * pios_usb_desc_hid_cdc.c, which lays the configuration out as:
 *
 *   interface 0  CDC control, endpoint 2 IN
 *   interface 1  CDC data,    endpoint 3 IN/OUT
 *   interface 2  HID,         endpoint 1 IN/OUT
 *
 * They were carried over from Revo, whose descriptor put HID first, and when
 * the descriptor builder was replaced the numbering stopped agreeing.  The
 * USBHOOK layer dispatches interface events by number, so the CDC driver was
 * waiting on interfaces the descriptor had given to something else and never
 * saw its data interface come up.  Enumeration is descriptor-level and worked
 * fine throughout, which made this look like the board was mute rather than
 * misconfigured.
 */
const struct pios_usb_hid_cfg pios_usb_hid_cfg = {
	/*
	 * pios_usb_desc_hid_only.c describes a single interface, number 0, with
	 * endpoint 1 in and out.  (The composite HID+CDC descriptor put HID at
	 * interface 2 instead - hence the different value when CDC was enabled.)
	 */
	.data_if = 0,
	.data_rx_ep = 1,
	.data_tx_ep = 1,
};
#endif /* PIOS_INCLUDE_USB_HID */

#if defined(PIOS_INCLUDE_USB_CDC)
#include <pios_usb_cdc_priv.h>

const struct pios_usb_cdc_cfg pios_usb_cdc_cfg = {
	.ctrl_if = 0,
	.ctrl_tx_ep = 2,

	.data_if = 1,
	.data_rx_ep = 3,
	.data_tx_ep = 3,
};
#endif	/* PIOS_INCLUDE_USB_CDC */
