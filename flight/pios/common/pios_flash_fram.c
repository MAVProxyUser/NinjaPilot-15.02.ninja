/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_FLASH_FRAM SPI FRAM presented as a flash device
 * @{
 *
 * @file       pios_flash_fram.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2026.
 * @brief      Cypress FM25V / Fujitsu MB85RS SPI FRAM behind pios_flash_driver
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

#if defined(PIOS_INCLUDE_FLASH_FRAM)

#include "pios_flash_fram.h"
#include <string.h>

/* Command set shared by the Cypress FM25V and Fujitsu MB85RS families. */
#define FRAM_CMD_WREN   0x06
#define FRAM_CMD_WRITE  0x02
#define FRAM_CMD_READ   0x03
#define FRAM_CMD_RDID   0x9F

/* The biggest single SPI write this driver issues; the filesystem's
 * page_size must not exceed it. */
#define FRAM_MAX_WRITE  256

enum pios_fram_dev_magic {
	PIOS_FRAM_DEV_MAGIC = 0xF2A40D01,
};

struct fram_part {
	uint8_t     id1;
	uint8_t     id2;
	uint16_t    size_kb;
	uint8_t     addrlen;
	const char *name;
};

/* Cypress parts answer RDID with six 0x7F continuation bytes, the JEDEC
 * manufacturer 0xC2, then two id bytes.  The table is the one ArduPilot
 * uses for the same sockets. */
static const struct fram_part fram_parts[] = {
	{ 0x21, 0x00,  16, 2, "FM25V01"   },
	{ 0x21, 0x08,  16, 2, "FM25V01A"  },
	{ 0x22, 0x00,  32, 2, "FM25V02"   },
	{ 0x22, 0x08,  32, 2, "FM25V02A"  },
	{ 0x22, 0x48,  32, 2, "FM25V02A"  },
	{ 0x22, 0x01,  32, 2, "FM25VN02"  },
	{ 0x23, 0x00,  64, 2, "FM25V05"   },
	{ 0x23, 0x01,  64, 2, "FM25VN05"  },
	{ 0x24, 0x00, 128, 3, "FM25V10"   },
	{ 0x24, 0x01, 128, 3, "FM25VN10"  },
	{ 0x25, 0x08, 256, 3, "FM25V20A"  },
	{ 0x26, 0x08, 512, 3, "CY15B104Q" },
};

struct fram_dev {
	enum pios_fram_dev_magic magic;
	uint32_t spi_id;
	uint32_t slave_num;
	uint32_t size;		/* bytes */
	uint32_t sector_size;	/* emulated erase block */
	const struct fram_part *part;
#if defined(PIOS_INCLUDE_FREERTOS)
	SemaphoreHandle_t transaction_lock;
#endif
};

static uint8_t fram_last_id[9];

static int32_t PIOS_Flash_Fram_Validate(struct fram_dev *dev)
{
	if (dev == NULL || dev->magic != PIOS_FRAM_DEV_MAGIC) {
		return -1;
	}
	return 0;
}

static struct fram_dev *PIOS_Flash_Fram_alloc(void)
{
	struct fram_dev *dev;

#if defined(PIOS_INCLUDE_FREERTOS)
	dev = (struct fram_dev *)pios_malloc(sizeof(*dev));
#else
	static struct fram_dev fram_devs[1];
	static uint8_t num_fram_devs;
	if (num_fram_devs >= NELEMENTS(fram_devs)) {
		return NULL;
	}
	dev = &fram_devs[num_fram_devs++];
#endif
	if (!dev) {
		return NULL;
	}
	memset(dev, 0, sizeof(*dev));
	dev->magic = PIOS_FRAM_DEV_MAGIC;
#if defined(PIOS_INCLUDE_FREERTOS)
	dev->transaction_lock = xSemaphoreCreateMutex();
#endif
	return dev;
}

static int32_t PIOS_Flash_Fram_ClaimBus(struct fram_dev *dev)
{
	if (PIOS_SPI_ClaimBus(dev->spi_id) < 0) {
		return -1;
	}
	PIOS_SPI_RC_PinSet(dev->spi_id, dev->slave_num, 0);
	return 0;
}

static void PIOS_Flash_Fram_ReleaseBus(struct fram_dev *dev)
{
	PIOS_SPI_RC_PinSet(dev->spi_id, dev->slave_num, 1);
	PIOS_SPI_ReleaseBus(dev->spi_id);
}

/* Command + address, chip select stays low for the data that follows. */
static int32_t PIOS_Flash_Fram_SendCmdAddr(struct fram_dev *dev, uint8_t cmd, uint32_t addr)
{
	uint8_t out[4];
	uint8_t n = 0;

	out[n++] = cmd;
	if (dev->part->addrlen == 3) {
		out[n++] = (addr >> 16) & 0xff;
	}
	out[n++] = (addr >> 8) & 0xff;
	out[n++] = addr & 0xff;
	if (PIOS_SPI_TransferBlock(dev->spi_id, out, NULL, n, NULL) < 0) {
		return -1;
	}
	return 0;
}

/* Every WRITE needs its own WREN: the latch clears when chip select rises. */
static int32_t PIOS_Flash_Fram_WriteEnable(struct fram_dev *dev)
{
	uint8_t out = FRAM_CMD_WREN;

	if (PIOS_Flash_Fram_ClaimBus(dev) != 0) {
		return -1;
	}
	int32_t rc = PIOS_SPI_TransferBlock(dev->spi_id, &out, NULL, 1, NULL);
	PIOS_Flash_Fram_ReleaseBus(dev);
	return rc < 0 ? -2 : 0;
}

static int32_t PIOS_Flash_Fram_ReadId(struct fram_dev *dev)
{
	uint8_t out[10];
	uint8_t in[10];

	memset(out, 0, sizeof(out));
	out[0] = FRAM_CMD_RDID;
	if (PIOS_Flash_Fram_ClaimBus(dev) != 0) {
		return -1;
	}
	int32_t rc = PIOS_SPI_TransferBlock(dev->spi_id, out, in, sizeof(out), NULL);
	PIOS_Flash_Fram_ReleaseBus(dev);
	if (rc < 0) {
		return -2;
	}
	memcpy(fram_last_id, &in[1], sizeof(fram_last_id));

	/* Cypress: 7F 7F 7F 7F 7F 7F C2 id1 id2 */
	if (in[7] == 0xC2) {
		for (uint32_t i = 0; i < NELEMENTS(fram_parts); i++) {
			if (fram_parts[i].id1 == in[8] && fram_parts[i].id2 == in[9]) {
				dev->part = &fram_parts[i];
				dev->size = (uint32_t)fram_parts[i].size_kb * 1024;
				return 0;
			}
		}
	}
	return -3;
}

int32_t PIOS_Flash_Fram_Init(uintptr_t *flash_id, uint32_t spi_id, uint32_t slave_num, uint32_t sector_size)
{
	struct fram_dev *dev = PIOS_Flash_Fram_alloc();

	if (!dev) {
		return -1;
	}
	dev->spi_id = spi_id;
	dev->slave_num = slave_num;
	dev->sector_size = sector_size;
	if (PIOS_Flash_Fram_ReadId(dev) != 0) {
		return -2;
	}
	*flash_id = (uintptr_t)dev;
	return 0;
}

uint32_t PIOS_Flash_Fram_Size(uintptr_t flash_id)
{
	struct fram_dev *dev = (struct fram_dev *)flash_id;

	if (PIOS_Flash_Fram_Validate(dev) != 0) {
		return 0;
	}
	return dev->size;
}

const char *PIOS_Flash_Fram_Name(uintptr_t flash_id)
{
	struct fram_dev *dev = (struct fram_dev *)flash_id;

	if (PIOS_Flash_Fram_Validate(dev) != 0 || !dev->part) {
		return "none";
	}
	return dev->part->name;
}

void PIOS_Flash_Fram_LastId(uint8_t id[9])
{
	memcpy(id, fram_last_id, 9);
}

/**********************************
 * pios_flash_driver interface
 **********************************/

static int32_t PIOS_Flash_Fram_StartTransaction(uintptr_t flash_id)
{
	struct fram_dev *dev = (struct fram_dev *)flash_id;

	if (PIOS_Flash_Fram_Validate(dev) != 0) {
		return -1;
	}
#if defined(PIOS_INCLUDE_FREERTOS)
	if (xSemaphoreTake(dev->transaction_lock, portMAX_DELAY) != pdTRUE) {
		return -2;
	}
#endif
	return 0;
}

static int32_t PIOS_Flash_Fram_EndTransaction(uintptr_t flash_id)
{
	struct fram_dev *dev = (struct fram_dev *)flash_id;

	if (PIOS_Flash_Fram_Validate(dev) != 0) {
		return -1;
	}
#if defined(PIOS_INCLUDE_FREERTOS)
	if (xSemaphoreGive(dev->transaction_lock) != pdTRUE) {
		return -2;
	}
#endif
	return 0;
}

/* One WRITE of up to FRAM_MAX_WRITE bytes. */
static int32_t PIOS_Flash_Fram_WriteData(uintptr_t flash_id, uint32_t addr, uint8_t *data, uint16_t len)
{
	struct fram_dev *dev = (struct fram_dev *)flash_id;

	if (PIOS_Flash_Fram_Validate(dev) != 0) {
		return -1;
	}
	if (len > FRAM_MAX_WRITE || addr + len > dev->size) {
		return -2;
	}
	if (PIOS_Flash_Fram_WriteEnable(dev) != 0) {
		return -3;
	}
	if (PIOS_Flash_Fram_ClaimBus(dev) != 0) {
		return -4;
	}
	if (PIOS_Flash_Fram_SendCmdAddr(dev, FRAM_CMD_WRITE, addr) != 0 ||
	    PIOS_SPI_TransferBlock(dev->spi_id, data, NULL, len, NULL) < 0) {
		PIOS_Flash_Fram_ReleaseBus(dev);
		return -5;
	}
	PIOS_Flash_Fram_ReleaseBus(dev);
	return 0;
}

/* Several buffers to consecutive addresses in one WRITE (the filesystem
 * writes a slot header and the object body this way). */
static int32_t PIOS_Flash_Fram_WriteChunks(uintptr_t flash_id, uint32_t addr, struct pios_flash_chunk chunks[], uint32_t num_chunks)
{
	struct fram_dev *dev = (struct fram_dev *)flash_id;
	uint32_t total = 0;

	if (PIOS_Flash_Fram_Validate(dev) != 0) {
		return -1;
	}
	for (uint32_t i = 0; i < num_chunks; i++) {
		total += chunks[i].len;
	}
	if (total > FRAM_MAX_WRITE || addr + total > dev->size) {
		return -2;
	}
	if (PIOS_Flash_Fram_WriteEnable(dev) != 0) {
		return -3;
	}
	if (PIOS_Flash_Fram_ClaimBus(dev) != 0) {
		return -4;
	}
	if (PIOS_Flash_Fram_SendCmdAddr(dev, FRAM_CMD_WRITE, addr) != 0) {
		PIOS_Flash_Fram_ReleaseBus(dev);
		return -5;
	}
	for (uint32_t i = 0; i < num_chunks; i++) {
		if (PIOS_SPI_TransferBlock(dev->spi_id, chunks[i].addr, NULL, chunks[i].len, NULL) < 0) {
			PIOS_Flash_Fram_ReleaseBus(dev);
			return -6;
		}
	}
	PIOS_Flash_Fram_ReleaseBus(dev);
	return 0;
}

static int32_t PIOS_Flash_Fram_ReadData(uintptr_t flash_id, uint32_t addr, uint8_t *data, uint16_t len)
{
	struct fram_dev *dev = (struct fram_dev *)flash_id;

	if (PIOS_Flash_Fram_Validate(dev) != 0) {
		return -1;
	}
	if (addr + len > dev->size) {
		return -2;
	}
	if (PIOS_Flash_Fram_ClaimBus(dev) != 0) {
		return -3;
	}
	if (PIOS_Flash_Fram_SendCmdAddr(dev, FRAM_CMD_READ, addr) != 0 ||
	    PIOS_SPI_TransferBlock(dev->spi_id, NULL, data, len, NULL) < 0) {
		PIOS_Flash_Fram_ReleaseBus(dev);
		return -4;
	}
	PIOS_Flash_Fram_ReleaseBus(dev);
	return 0;
}

/* Erase emulation: fill with 0xFF, which is what an erased flash reads. */
static int32_t PIOS_Flash_Fram_Fill(struct fram_dev *dev, uint32_t addr, uint32_t len)
{
	static uint8_t ones[FRAM_MAX_WRITE];

	memset(ones, 0xFF, sizeof(ones));
	while (len > 0) {
		uint16_t n = len > FRAM_MAX_WRITE ? FRAM_MAX_WRITE : len;
		int32_t rc = PIOS_Flash_Fram_WriteData((uintptr_t)dev, addr, ones, n);
		if (rc != 0) {
			return rc;
		}
		addr += n;
		len -= n;
	}
	return 0;
}

static int32_t PIOS_Flash_Fram_EraseSector(uintptr_t flash_id, uint32_t addr)
{
	struct fram_dev *dev = (struct fram_dev *)flash_id;

	if (PIOS_Flash_Fram_Validate(dev) != 0) {
		return -1;
	}
	if (dev->sector_size == 0 || addr + dev->sector_size > dev->size) {
		return -2;
	}
	return PIOS_Flash_Fram_Fill(dev, addr, dev->sector_size);
}

static int32_t PIOS_Flash_Fram_EraseChip(uintptr_t flash_id)
{
	struct fram_dev *dev = (struct fram_dev *)flash_id;

	if (PIOS_Flash_Fram_Validate(dev) != 0) {
		return -1;
	}
	return PIOS_Flash_Fram_Fill(dev, 0, dev->size);
}

const struct pios_flash_driver pios_fram_flash_driver = {
	.start_transaction = PIOS_Flash_Fram_StartTransaction,
	.end_transaction   = PIOS_Flash_Fram_EndTransaction,
	.erase_chip        = PIOS_Flash_Fram_EraseChip,
	.erase_sector      = PIOS_Flash_Fram_EraseSector,
	.write_chunks      = PIOS_Flash_Fram_WriteChunks,
	.write_data        = PIOS_Flash_Fram_WriteData,
	.read_data         = PIOS_Flash_Fram_ReadData,
};

#endif /* PIOS_INCLUDE_FLASH_FRAM */

/**
 * @}
 * @}
 */
