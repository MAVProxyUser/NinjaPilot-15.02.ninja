/**
 ******************************************************************************
 * @file       board_hw_defs.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2026.
 * @brief      Hardware definitions of the CubePilot Cube Purple (FMUv3),
 *             pins as ArduPilot's fmuv3 hardware definition names them.
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
/* FMU_LED_AMBER on PE12, open drain, low = on: the one FMU LED.  The big RGB
 * LED is behind a TCA62724 on the internal I2C bus (not driven yet). */
static const struct pios_gpio pios_leds[] = {
    [PIOS_LED_HEARTBEAT] = {
        .pin                =             {
            .gpio = GPIOE,
            .init =             {
                .GPIO_Pin   = GPIO_Pin_12,
                .GPIO_Speed = GPIO_Speed_50MHz,
                .GPIO_Mode  = GPIO_Mode_OUT,
                .GPIO_OType = GPIO_OType_OD,
                .GPIO_PuPd  = GPIO_PuPd_NOPULL
            },
        },
        .active_low         = true
    },
};

static const struct pios_gpio_cfg pios_led_cfg = {
    .gpios     = pios_leds,
    .num_gpios = NELEMENTS(pios_leds),
};

const struct pios_gpio_cfg *PIOS_BOARD_HW_DEFS_GetLedCfg(__attribute__((unused)) uint32_t board_revision)
{
    return &pios_led_cfg;
}

#endif /* PIOS_INCLUDE_LED */

#if defined(PIOS_INCLUDE_SPI)

#include <pios_spi_priv.h>

/*
 * SPI1: the MPU9250 (CS PC2) and the MS5611 (CS PD7).  Both are SPI mode 3.
 * 84 MHz / 16 = 5.25 MHz for bursts; the IMU's register writes drop to /128.
 */
void PIOS_SPI_sensors_irq_handler(void);
void DMA2_Stream0_IRQHandler(void) __attribute__((alias("PIOS_SPI_sensors_irq_handler")));
void DMA2_Stream3_IRQHandler(void) __attribute__((alias("PIOS_SPI_sensors_irq_handler")));
static const struct pios_spi_cfg pios_spi_sensors_cfg = {
    .regs  = SPI1,
    .remap = GPIO_AF_SPI1,
    .init  = {
        .SPI_Mode              = SPI_Mode_Master,
        .SPI_Direction         = SPI_Direction_2Lines_FullDuplex,
        .SPI_DataSize          = SPI_DataSize_8b,
        .SPI_NSS               = SPI_NSS_Soft,
        .SPI_FirstBit          = SPI_FirstBit_MSB,
        .SPI_CRCPolynomial     = 7,
        .SPI_CPOL              = SPI_CPOL_High,
        .SPI_CPHA              = SPI_CPHA_2Edge,
        .SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16,
    },
    .use_crc = false,
    .dma     = {
        .irq                                       = {
            .flags = (DMA_IT_TCIF0 | DMA_IT_TEIF0 | DMA_IT_HTIF0),
            .init  = {
                .NVIC_IRQChannel    = DMA2_Stream0_IRQn,
                .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
                .NVIC_IRQChannelSubPriority        = 0,
                .NVIC_IRQChannelCmd = ENABLE,
            },
        },

        .rx                                        = {
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
        .tx                                        = {
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
    .sclk                                          = {
        .gpio = GPIOA,
        .init = {
            .GPIO_Pin   = GPIO_Pin_5,
            .GPIO_Speed = GPIO_Speed_100MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd  = GPIO_PuPd_UP
        },
    },
    .miso                                          = {
        .gpio = GPIOA,
        .init = {
            .GPIO_Pin   = GPIO_Pin_6,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd  = GPIO_PuPd_UP
        },
    },
    .mosi                                          = {
        .gpio = GPIOA,
        .init = {
            .GPIO_Pin   = GPIO_Pin_7,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd  = GPIO_PuPd_UP
        },
    },
    .slave_count                                   = 2,
    .ssel                                          = {
        { /* CUBE_SPI1_SLAVE_IMU - PC2, MPU_CS */
            .gpio = GPIOC,
            .init = {
                .GPIO_Pin   = GPIO_Pin_2,
                .GPIO_Speed = GPIO_Speed_50MHz,
                .GPIO_Mode  = GPIO_Mode_OUT,
                .GPIO_OType = GPIO_OType_PP,
                .GPIO_PuPd  = GPIO_PuPd_UP
            },
        },
        { /* CUBE_SPI1_SLAVE_MS5611 - PD7, BARO_CS */
            .gpio = GPIOD,
            .init = {
                .GPIO_Pin   = GPIO_Pin_7,
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
    PIOS_SPI_IRQ_Handler(pios_spi_sensors_id);
}

/*
 * SPI2: the settings FRAM (FM25V02 on the Cube).  PB13 SCK, PB14 MISO,
 * PB15 MOSI, PD10 chip select; DMA1 stream 3 (rx) / 4 (tx), channel 0.
 * 42 MHz / 8 = 5.25 MHz, SPI mode 3.
 */
void PIOS_SPI_fram_irq_handler(void);
void DMA1_Stream3_IRQHandler(void) __attribute__((alias("PIOS_SPI_fram_irq_handler")));
void DMA1_Stream4_IRQHandler(void) __attribute__((alias("PIOS_SPI_fram_irq_handler")));
static const struct pios_spi_cfg pios_spi_fram_cfg = {
    .regs  = SPI2,
    .remap = GPIO_AF_SPI2,
    .init  = {
        .SPI_Mode              = SPI_Mode_Master,
        .SPI_Direction         = SPI_Direction_2Lines_FullDuplex,
        .SPI_DataSize          = SPI_DataSize_8b,
        .SPI_NSS               = SPI_NSS_Soft,
        .SPI_FirstBit          = SPI_FirstBit_MSB,
        .SPI_CRCPolynomial     = 7,
        .SPI_CPOL              = SPI_CPOL_High,
        .SPI_CPHA              = SPI_CPHA_2Edge,
        .SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8,
    },
    .use_crc = false,
    .dma     = {
        .irq                                       = {
            .flags = (DMA_IT_TCIF3 | DMA_IT_TEIF3 | DMA_IT_HTIF3),
            .init  = {
                .NVIC_IRQChannel    = DMA1_Stream3_IRQn,
                .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
                .NVIC_IRQChannelSubPriority        = 0,
                .NVIC_IRQChannelCmd = ENABLE,
            },
        },

        .rx                                        = {
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
        .tx                                        = {
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
    .sclk                                          = {
        .gpio = GPIOB,
        .init = {
            .GPIO_Pin   = GPIO_Pin_13,
            .GPIO_Speed = GPIO_Speed_100MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd  = GPIO_PuPd_UP
        },
    },
    .miso                                          = {
        .gpio = GPIOB,
        .init = {
            .GPIO_Pin   = GPIO_Pin_14,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd  = GPIO_PuPd_UP
        },
    },
    .mosi                                          = {
        .gpio = GPIOB,
        .init = {
            .GPIO_Pin   = GPIO_Pin_15,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd  = GPIO_PuPd_UP
        },
    },
    .slave_count                                   = 1,
    .ssel                                          = {
        { /* CUBE_SPI2_SLAVE_FRAM - PD10, FRAM_CS */
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

uint32_t pios_spi_fram_id;
void PIOS_SPI_fram_irq_handler(void)
{
    PIOS_SPI_IRQ_Handler(pios_spi_fram_id);
}

#endif /* PIOS_INCLUDE_SPI */

#if defined(PIOS_INCLUDE_FLASH)
#include "pios_flashfs_logfs_priv.h"
#include "pios_flash_internal_priv.h"

/*
 * Settings in the FRAM: the ArduPilot bootloader erases every internal flash
 * sector above itself before it programs, so settings kept in flash would
 * vanish with each firmware update.  An FRAM has no erase, so the driver
 * emulates 1 KB sectors by writing 0xFF; total/arena are filled in from the
 * part that answers (FM25V02 = 32 KB: two 16 KB arenas of 256-byte slots).
 */
#define CUBE_FRAM_SECTOR 0x400
static struct flashfs_logfs_cfg flashfs_fram_cfg = {
    .fs_magic      = 0x99ABCEEF,
    .total_fs_size = 0x8000,
    .arena_size    = 0x4000,
    .slot_size     = 0x100,
    .start_offset  = 0,
    .sector_size   = CUBE_FRAM_SECTOR,
    .page_size     = 0x100,
};

/* Fallback when no FRAM answers: flash sectors 10-11 (a flash wipes them). */
static const struct pios_flash_internal_cfg flash_internal_cfg = {};

static const struct flashfs_logfs_cfg flashfs_internal_cfg = {
    .fs_magic      = 0x99abcfef,
    .total_fs_size = FS_BANK_SIZE, /* 256 KB, two 128 KB sectors */
    .arena_size    = 0x00020000, /* one sector per arena */
    .slot_size     = 0x00000100, /* 256 bytes */
    .start_offset  = FS_BANK_BASE,
    .sector_size   = 0x00020000, /* 128 KB */
    .page_size     = 0x00000100, /* 256 bytes */
};

#endif /* PIOS_INCLUDE_FLASH */

#include <pios_usart_priv.h>

/*
 * TELEM1 - USART2 on PD5 (tx) / PD6 (rx).  HwSettings.RV_TelemetryPort.
 */
static const struct pios_usart_cfg pios_usart_telem1_cfg = {
    .regs  = USART2,
    .remap = GPIO_AF_USART2,
    .init  = {
        .USART_BaudRate            = 57600,
        .USART_WordLength          = USART_WordLength_8b,
        .USART_Parity              = USART_Parity_No,
        .USART_StopBits            = USART_StopBits_1,
        .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
        .USART_Mode                = USART_Mode_Rx | USART_Mode_Tx,
    },
    .irq   = {
        .init                                      = {
            .NVIC_IRQChannel    = USART2_IRQn,
            .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
            .NVIC_IRQChannelSubPriority        = 0,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
    .rx    = {
        .gpio = GPIOD,
        .init = {
            .GPIO_Pin   = GPIO_Pin_6,
            .GPIO_Speed = GPIO_Speed_2MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd  = GPIO_PuPd_UP
        },
    },
    .tx    = {
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
 * TELEM2 - USART3 on PD8 (tx) / PD9 (rx).  HwSettings.RV_AuxPort.
 */
static const struct pios_usart_cfg pios_usart_telem2_cfg = {
    .regs  = USART3,
    .remap = GPIO_AF_USART3,
    .init  = {
        .USART_BaudRate            = 57600,
        .USART_WordLength          = USART_WordLength_8b,
        .USART_Parity              = USART_Parity_No,
        .USART_StopBits            = USART_StopBits_1,
        .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
        .USART_Mode                = USART_Mode_Rx | USART_Mode_Tx,
    },
    .irq   = {
        .init                                      = {
            .NVIC_IRQChannel    = USART3_IRQn,
            .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
            .NVIC_IRQChannelSubPriority        = 0,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
    .rx    = {
        .gpio = GPIOD,
        .init = {
            .GPIO_Pin   = GPIO_Pin_9,
            .GPIO_Speed = GPIO_Speed_2MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd  = GPIO_PuPd_UP
        },
    },
    .tx    = {
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

/*
 * GPS connector - UART4 on PA0 (tx) / PA1 (rx).  HwSettings.RV_GPSPort.
 */
static const struct pios_usart_cfg pios_usart_gps_cfg = {
    .regs  = UART4,
    .remap = GPIO_AF_UART4,
    .init  = {
        .USART_BaudRate            = 57600,
        .USART_WordLength          = USART_WordLength_8b,
        .USART_Parity              = USART_Parity_No,
        .USART_StopBits            = USART_StopBits_1,
        .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
        .USART_Mode                = USART_Mode_Rx | USART_Mode_Tx,
    },
    .irq   = {
        .init                                      = {
            .NVIC_IRQChannel    = UART4_IRQn,
            .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
            .NVIC_IRQChannelSubPriority        = 0,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
    .rx    = {
        .gpio = GPIOA,
        .init = {
            .GPIO_Pin   = GPIO_Pin_1,
            .GPIO_Speed = GPIO_Speed_2MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd  = GPIO_PuPd_UP
        },
    },
    .tx    = {
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

#if defined(PIOS_INCLUDE_IOMCU)
/*
 * IO co-processor - USART6 on PC6 (our TX) / PC7 (our RX), 1.5 Mbaud 8N1,
 * the PX4IO register protocol of the ArduPilot IO firmware.  A byte every
 * 6.7 us: the interrupt sits above every other one that can run for long.
 */
static const struct pios_usart_cfg pios_usart_iomcu_cfg = {
    .regs  = USART6,
    .remap = GPIO_AF_USART6,
    .init  = {
        .USART_BaudRate            = 1500000,
        .USART_WordLength          = USART_WordLength_8b,
        .USART_Parity              = USART_Parity_No,
        .USART_StopBits            = USART_StopBits_1,
        .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
        .USART_Mode                = USART_Mode_Rx | USART_Mode_Tx,
    },
    .irq   = {
        .init                                      = {
            .NVIC_IRQChannel    = USART6_IRQn,
            .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
            .NVIC_IRQChannelSubPriority        = 0,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
    .rx    = {
        .gpio = GPIOC,
        .init = {
            .GPIO_Pin   = GPIO_Pin_7,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd  = GPIO_PuPd_UP
        },
    },
    .tx    = {
        .gpio = GPIOC,
        .init = {
            .GPIO_Pin   = GPIO_Pin_6,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd  = GPIO_PuPd_UP
        },
    },
};
#endif /* PIOS_INCLUDE_IOMCU */

#if defined(PIOS_INCLUDE_COM)

#include <pios_com_priv.h>

#endif /* PIOS_INCLUDE_COM */

#if defined(PIOS_INCLUDE_I2C)

#include <pios_i2c_priv.h>

/*
 * I2C1 - the external bus on the GPS connector, PB8 (scl) / PB9 (sda).
 */
void PIOS_I2C_external_adapter_ev_irq_handler(void);
void PIOS_I2C_external_adapter_er_irq_handler(void);
void I2C1_EV_IRQHandler() __attribute__((alias("PIOS_I2C_external_adapter_ev_irq_handler")));
void I2C1_ER_IRQHandler() __attribute__((alias("PIOS_I2C_external_adapter_er_irq_handler")));

static const struct pios_i2c_adapter_cfg pios_i2c_external_adapter_cfg = {
    .regs     = I2C1,
    .remap    = GPIO_AF_I2C1,
    .init     = {
        .I2C_Mode = I2C_Mode_I2C,
        .I2C_OwnAddress1 = 0,
        .I2C_Ack  = I2C_Ack_Enable,
        .I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit,
        .I2C_DutyCycle  = I2C_DutyCycle_2,
        .I2C_ClockSpeed = 400000, /* bits/s */
    },
    .transfer_timeout_ms = 50,
    .scl      = {
        .gpio = GPIOB,
        .init = {
            .GPIO_Pin   = GPIO_Pin_8,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_OD,
            .GPIO_PuPd  = GPIO_PuPd_NOPULL,
        },
    },
    .sda      = {
        .gpio = GPIOB,
        .init = {
            .GPIO_Pin   = GPIO_Pin_9,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_OD,
            .GPIO_PuPd  = GPIO_PuPd_NOPULL,
        },
    },
    .event    = {
        .flags = 0, /* FIXME: check this */
        .init  = {
            .NVIC_IRQChannel    = I2C1_EV_IRQn,
            .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGHEST,
            .NVIC_IRQChannelSubPriority        = 0,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
    .error    = {
        .flags = 0, /* FIXME: check this */
        .init  = {
            .NVIC_IRQChannel    = I2C1_ER_IRQn,
            .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGHEST,
            .NVIC_IRQChannelSubPriority        = 0,
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

/*
 * I2C2 - the internal bus (TCA62724 RGB LED driver), PB10 (scl) / PB11 (sda).
 */
void PIOS_I2C_internal_adapter_ev_irq_handler(void);
void PIOS_I2C_internal_adapter_er_irq_handler(void);
void I2C2_EV_IRQHandler() __attribute__((alias("PIOS_I2C_internal_adapter_ev_irq_handler")));
void I2C2_ER_IRQHandler() __attribute__((alias("PIOS_I2C_internal_adapter_er_irq_handler")));

static const struct pios_i2c_adapter_cfg pios_i2c_internal_adapter_cfg = {
    .regs     = I2C2,
    .remap    = GPIO_AF_I2C2,
    .init     = {
        .I2C_Mode = I2C_Mode_I2C,
        .I2C_OwnAddress1 = 0,
        .I2C_Ack  = I2C_Ack_Enable,
        .I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit,
        .I2C_DutyCycle  = I2C_DutyCycle_2,
        .I2C_ClockSpeed = 100000, /* bits/s */
    },
    .transfer_timeout_ms = 50,
    .scl      = {
        .gpio = GPIOB,
        .init = {
            .GPIO_Pin   = GPIO_Pin_10,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_OD,
            .GPIO_PuPd  = GPIO_PuPd_NOPULL,
        },
    },
    .sda      = {
        .gpio = GPIOB,
        .init = {
            .GPIO_Pin   = GPIO_Pin_11,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode  = GPIO_Mode_AF,
            .GPIO_OType = GPIO_OType_OD,
            .GPIO_PuPd  = GPIO_PuPd_NOPULL,
        },
    },
    .event    = {
        .flags = 0, /* FIXME: check this */
        .init  = {
            .NVIC_IRQChannel    = I2C2_EV_IRQn,
            .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGHEST,
            .NVIC_IRQChannelSubPriority        = 0,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
    .error    = {
        .flags = 0, /* FIXME: check this */
        .init  = {
            .NVIC_IRQChannel    = I2C2_ER_IRQn,
            .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGHEST,
            .NVIC_IRQChannelSubPriority        = 0,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
};

uint32_t pios_i2c_internal_adapter_id;
void PIOS_I2C_internal_adapter_ev_irq_handler(void)
{
    PIOS_I2C_EV_IRQ_Handler(pios_i2c_internal_adapter_id);
}

void PIOS_I2C_internal_adapter_er_irq_handler(void)
{
    PIOS_I2C_ER_IRQ_Handler(pios_i2c_internal_adapter_id);
}

#endif /* PIOS_INCLUDE_I2C */

#if defined(PIOS_INCLUDE_RTC)
/*
 * Realtime Clock (RTC)
 */
#include <pios_rtc_priv.h>

void PIOS_RTC_IRQ_Handler(void);
void RTC_WKUP_IRQHandler() __attribute__((alias("PIOS_RTC_IRQ_Handler")));
static const struct pios_rtc_cfg pios_rtc_main_cfg = {
    .clksrc    = RCC_RTCCLKSource_HSE_Div24, /* 24 MHz / 24 = 1 MHz */
    .prescaler = 100, /* Every 100 cycles = 10 kHz sampling */
    .irq                                       = {
        .init                                  = {
            .NVIC_IRQChannel    = RTC_WKUP_IRQn,
            .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
            .NVIC_IRQChannelSubPriority        = 0,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
};

void PIOS_RTC_IRQ_Handler(void)
{
    PIOS_RTC_irq_handler();
}

#endif /* if defined(PIOS_INCLUDE_RTC) */

#include "pios_tim_priv.h"

static const TIM_TimeBaseInitTypeDef tim_apb1_time_base = {
    .TIM_Prescaler         = (PIOS_PERIPHERAL_APB1_CLOCK / 1000000) - 1,
    .TIM_ClockDivision     = TIM_CKD_DIV1,
    .TIM_CounterMode       = TIM_CounterMode_Up,
    .TIM_Period            = 0xFFFF,
    .TIM_RepetitionCounter = 0x0000,
};
static const TIM_TimeBaseInitTypeDef tim_apb2_time_base = {
    .TIM_Prescaler         = (PIOS_PERIPHERAL_APB2_CLOCK / 1000000) - 1,
    .TIM_ClockDivision     = TIM_CKD_DIV1,
    .TIM_CounterMode       = TIM_CounterMode_Up,
    .TIM_Period            = 0xFFFF,
    .TIM_RepetitionCounter = 0x0000,
};

static const struct pios_tim_clock_cfg tim_1_cfg = {
    .timer = TIM1,
    .time_base_init                            = &tim_apb2_time_base,
    .irq   = {
        .init                                  = {
            .NVIC_IRQChannel    = TIM1_CC_IRQn,
            .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
            .NVIC_IRQChannelSubPriority        = 0,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
};

static const struct pios_tim_clock_cfg tim_4_cfg = {
    .timer = TIM4,
    .time_base_init                            = &tim_apb1_time_base,
    .irq   = {
        .init                                  = {
            .NVIC_IRQChannel    = TIM4_IRQn,
            .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
            .NVIC_IRQChannelSubPriority        = 0,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
};

/*
 * Servo outputs on this MCU: AUX OUT 1-5.  (MAIN OUT 1-8 belong to the IO
 * co-processor; AUX OUT 6 is the PPM input.)
 */
#include <pios_servo_priv.h>
static const struct pios_tim_channel pios_tim_servoport_all_pins[] = {
    { /* AUX OUT 1 - PE14, TIM1_CH4 */
        .timer = TIM1,
        .timer_chan = TIM_Channel_4,
        .pin   = {
            .gpio = GPIOE,
            .init = {
                .GPIO_Pin   = GPIO_Pin_14,
                .GPIO_Speed = GPIO_Speed_2MHz,
                .GPIO_Mode  = GPIO_Mode_AF,
                .GPIO_OType = GPIO_OType_PP,
                .GPIO_PuPd  = GPIO_PuPd_UP
            },
            .pin_source     = GPIO_PinSource14,
        },
        .remap = GPIO_AF_TIM1,
    },
    { /* AUX OUT 2 - PE13, TIM1_CH3 */
        .timer = TIM1,
        .timer_chan = TIM_Channel_3,
        .pin   = {
            .gpio = GPIOE,
            .init = {
                .GPIO_Pin   = GPIO_Pin_13,
                .GPIO_Speed = GPIO_Speed_2MHz,
                .GPIO_Mode  = GPIO_Mode_AF,
                .GPIO_OType = GPIO_OType_PP,
                .GPIO_PuPd  = GPIO_PuPd_UP
            },
            .pin_source     = GPIO_PinSource13,
        },
        .remap = GPIO_AF_TIM1,
    },
    { /* AUX OUT 3 - PE11, TIM1_CH2 */
        .timer = TIM1,
        .timer_chan = TIM_Channel_2,
        .pin   = {
            .gpio = GPIOE,
            .init = {
                .GPIO_Pin   = GPIO_Pin_11,
                .GPIO_Speed = GPIO_Speed_2MHz,
                .GPIO_Mode  = GPIO_Mode_AF,
                .GPIO_OType = GPIO_OType_PP,
                .GPIO_PuPd  = GPIO_PuPd_UP
            },
            .pin_source     = GPIO_PinSource11,
        },
        .remap = GPIO_AF_TIM1,
    },
    { /* AUX OUT 4 - PE9, TIM1_CH1 */
        .timer = TIM1,
        .timer_chan = TIM_Channel_1,
        .pin   = {
            .gpio = GPIOE,
            .init = {
                .GPIO_Pin   = GPIO_Pin_9,
                .GPIO_Speed = GPIO_Speed_2MHz,
                .GPIO_Mode  = GPIO_Mode_AF,
                .GPIO_OType = GPIO_OType_PP,
                .GPIO_PuPd  = GPIO_PuPd_UP
            },
            .pin_source     = GPIO_PinSource9,
        },
        .remap = GPIO_AF_TIM1,
    },
    { /* AUX OUT 5 - PD13, TIM4_CH2 */
        .timer = TIM4,
        .timer_chan = TIM_Channel_2,
        .pin   = {
            .gpio = GPIOD,
            .init = {
                .GPIO_Pin   = GPIO_Pin_13,
                .GPIO_Speed = GPIO_Speed_2MHz,
                .GPIO_Mode  = GPIO_Mode_AF,
                .GPIO_OType = GPIO_OType_PP,
                .GPIO_PuPd  = GPIO_PuPd_UP
            },
            .pin_source     = GPIO_PinSource13,
        },
        .remap = GPIO_AF_TIM4,
    },
};

const struct pios_servo_cfg pios_servo_cfg_out = {
    .tim_oc_init          = {
        .TIM_OCMode       = TIM_OCMode_PWM1,
        .TIM_OutputState  = TIM_OutputState_Enable,
        .TIM_OutputNState = TIM_OutputNState_Disable,
        .TIM_Pulse        = PIOS_SERVOS_INITIAL_POSITION,
        .TIM_OCPolarity   = TIM_OCPolarity_High,
        .TIM_OCNPolarity  = TIM_OCPolarity_High,
        .TIM_OCIdleState  = TIM_OCIdleState_Reset,
        .TIM_OCNIdleState = TIM_OCNIdleState_Reset,
    },
    .channels     = pios_tim_servoport_all_pins,
    .num_channels = NELEMENTS(pios_tim_servoport_all_pins),
};

/*
 * PPM input on AUX OUT 6 - PD14, TIM4_CH3.
 */
#if defined(PIOS_INCLUDE_PPM)
#include <pios_ppm_priv.h>
static const struct pios_tim_channel pios_tim_rcvrport_ppm[] = {
    {
        .timer = TIM4,
        .timer_chan = TIM_Channel_3,
        .pin   = {
            .gpio = GPIOD,
            .init = {
                .GPIO_Pin   = GPIO_Pin_14,
                .GPIO_Speed = GPIO_Speed_2MHz,
                .GPIO_Mode  = GPIO_Mode_AF,
                .GPIO_OType = GPIO_OType_PP,
                .GPIO_PuPd  = GPIO_PuPd_DOWN
            },
            .pin_source     = GPIO_PinSource14,
        },
        .remap = GPIO_AF_TIM4,
    },
};

static const struct pios_ppm_cfg pios_ppm_cfg = {
    .tim_ic_init         = {
        .TIM_ICPolarity  = TIM_ICPolarity_Rising,
        .TIM_ICSelection = TIM_ICSelection_DirectTI,
        .TIM_ICPrescaler = TIM_ICPSC_DIV1,
        .TIM_ICFilter    = 0x0,
        .TIM_Channel     = TIM_Channel_3,
    },
    .channels     = pios_tim_rcvrport_ppm,
    .num_channels = NELEMENTS(pios_tim_rcvrport_ppm),
};
#endif /* PIOS_INCLUDE_PPM */

#if defined(PIOS_INCLUDE_GCSRCVR)
#include "pios_gcsrcvr_priv.h"
#endif /* PIOS_INCLUDE_GCSRCVR */

#if defined(PIOS_INCLUDE_RCVR)
#include "pios_rcvr_priv.h"
#endif /* PIOS_INCLUDE_RCVR */

#if defined(PIOS_INCLUDE_USB)
#include "pios_usb_priv.h"

/* VBUS sense on PA9 (an open-drain input in the hwdef). */
static const struct pios_usb_cfg pios_usb_main_cfg = {
    .irq                                       = {
        .init                                  = {
            .NVIC_IRQChannel    = OTG_FS_IRQn,
            .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
            .NVIC_IRQChannelSubPriority        = 0,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
    .vsense                                    = {
        .gpio = GPIOA,
        .init = {
            .GPIO_Pin   = GPIO_Pin_9,
            .GPIO_Speed = GPIO_Speed_25MHz,
            .GPIO_Mode  = GPIO_Mode_IN,
            .GPIO_OType = GPIO_OType_OD,
        },
    },
    .vsense_active_low                         = false
};

const struct pios_usb_cfg *PIOS_BOARD_HW_DEFS_GetUsbCfg(__attribute__((unused)) uint32_t board_revision)
{
    return &pios_usb_main_cfg;
}

#include "pios_usb_board_data_priv.h"
#include "pios_usb_desc_hid_cdc_priv.h"
#include "pios_usb_desc_hid_only_priv.h"
#include "pios_usbhook.h"

#endif /* PIOS_INCLUDE_USB */

#if defined(PIOS_INCLUDE_COM_MSG)

#include <pios_com_msg_priv.h>

#endif /* PIOS_INCLUDE_COM_MSG */

#if defined(PIOS_INCLUDE_USB_HID) && !defined(PIOS_INCLUDE_USB_CDC)
#include <pios_usb_hid_priv.h>

const struct pios_usb_hid_cfg pios_usb_hid_cfg = {
    .data_if    = 0,
    .data_rx_ep = 1,
    .data_tx_ep = 1,
};
#endif /* PIOS_INCLUDE_USB_HID && !PIOS_INCLUDE_USB_CDC */

#if defined(PIOS_INCLUDE_USB_HID) && defined(PIOS_INCLUDE_USB_CDC)
#include <pios_usb_cdc_priv.h>

const struct pios_usb_cdc_cfg pios_usb_cdc_cfg = {
    .ctrl_if    = 0,
    .ctrl_tx_ep = 2,

    .data_if    = 1,
    .data_rx_ep = 3,
    .data_tx_ep = 3,
};

#include <pios_usb_hid_priv.h>

const struct pios_usb_hid_cfg pios_usb_hid_cfg = {
    .data_if    = 2,
    .data_rx_ep = 1,
    .data_tx_ep = 1,
};
#endif /* PIOS_INCLUDE_USB_HID && PIOS_INCLUDE_USB_CDC */

/*
 * Power rails: VDD_3V3_SENSORS_EN on PE3 (high = on), VDD_5V_PERIPH_EN on
 * PA8 (low = on).
 */
const struct stm32_gpio pios_cube_vdd_sensors_en = {
    .gpio = GPIOE,
    .init = {
        .GPIO_Pin   = GPIO_Pin_3,
        .GPIO_Speed = GPIO_Speed_2MHz,
        .GPIO_Mode  = GPIO_Mode_OUT,
        .GPIO_OType = GPIO_OType_PP,
        .GPIO_PuPd  = GPIO_PuPd_NOPULL
    },
};
const struct stm32_gpio pios_cube_vdd_periph_en_n = {
    .gpio = GPIOA,
    .init = {
        .GPIO_Pin   = GPIO_Pin_8,
        .GPIO_Speed = GPIO_Speed_2MHz,
        .GPIO_Mode  = GPIO_Mode_OUT,
        .GPIO_OType = GPIO_OType_PP,
        .GPIO_PuPd  = GPIO_PuPd_NOPULL
    },
};

/*
 * Chip selects of SPI devices this firmware does not drive, parked deselected
 * (output, high) exactly as the bootloader's hwdef does: the isolated bus
 * (unpopulated on the Purple, but the pins exist) and the SPI1 magnetometer
 * footprint.
 *
 *   PC1  MAG_CS   PC13 GYRO_EXT_CS   PC14 BARO_EXT_CS   PC15 ACCEL_EXT_CS
 *   PE4  MPU_EXT_CS
 */
const struct stm32_gpio pios_cube_parked_cs[] = {
    { .gpio = GPIOC, .init = { .GPIO_Pin = GPIO_Pin_1,  .GPIO_Speed = GPIO_Speed_2MHz, .GPIO_Mode = GPIO_Mode_OUT, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP } },
    { .gpio = GPIOC, .init = { .GPIO_Pin = GPIO_Pin_13, .GPIO_Speed = GPIO_Speed_2MHz, .GPIO_Mode = GPIO_Mode_OUT, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP } },
    { .gpio = GPIOC, .init = { .GPIO_Pin = GPIO_Pin_14, .GPIO_Speed = GPIO_Speed_2MHz, .GPIO_Mode = GPIO_Mode_OUT, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP } },
    { .gpio = GPIOC, .init = { .GPIO_Pin = GPIO_Pin_15, .GPIO_Speed = GPIO_Speed_2MHz, .GPIO_Mode = GPIO_Mode_OUT, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP } },
    { .gpio = GPIOE, .init = { .GPIO_Pin = GPIO_Pin_4,  .GPIO_Speed = GPIO_Speed_2MHz, .GPIO_Mode = GPIO_Mode_OUT, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP } },
};
const uint32_t pios_cube_parked_cs_count = NELEMENTS(pios_cube_parked_cs);
