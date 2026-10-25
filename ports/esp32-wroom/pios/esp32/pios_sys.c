/**
 ******************************************************************************
 * @file       pios_sys.c
 * @author     NinjaPilot, 2026
 * @brief      ESP32 system startup, reset and identity.
 *
 * Most of what the STM32 PIOS_SYS_Init() does (clock tree, NVIC priority
 * grouping, GPIO clock enables) is already done by the IDF's second-stage
 * bootloader and startup code before app_main() is reached, so this is
 * mostly a reporting shim.
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

#include "pios.h"

/* Definition for the counter declared in pios_esp32.h -- see the task-stack
 * unit note there. */
uint32_t pios_esp32_task_create_failures;

#ifdef PIOS_INCLUDE_SYS

#include "esp_system.h"
#include "esp_mac.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

void PIOS_SYS_Init(void)
{
    /* Clocks, cache and the FreeRTOS scheduler are all already up. The one
     * thing worth doing here is leaving a breadcrumb on the console so a
     * boot loop is obvious from a serial capture alone. */
    esp_chip_info_t info;

    esp_chip_info(&info);

    uint32_t flash_size = 0;
    (void)esp_flash_get_size(NULL, &flash_size);

    printf("\n[PIOS] NinjaPilot on ESP32: %d core(s), silicon rev %d, %luKB flash\n",
           info.cores, info.revision, (unsigned long)(flash_size / 1024));
}

int32_t PIOS_SYS_Reset(void)
{
    esp_restart();

    /* esp_restart() does not return. */
    while (1) {
        ;
    }
    return -1;
}

uint32_t PIOS_SYS_getCPUFlashSize(void)
{
    uint32_t flash_size = 0;

    if (esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        return 0;
    }
    return flash_size;
}

int32_t PIOS_SYS_SerialNumberGetBinary(uint8_t array[PIOS_SYS_SERIAL_NUM_BINARY_LEN])
{
    uint8_t mac[6];

    /* The factory-programmed base MAC in eFuse is the only per-die unique
     * identifier the ESP32 offers. It is 6 bytes; pad the remainder so the
     * length PiOS advertises is always filled. */
    if (esp_efuse_mac_get_default(mac) != ESP_OK) {
        memset(array, 0, PIOS_SYS_SERIAL_NUM_BINARY_LEN);
        return -1;
    }

    for (uint8_t i = 0; i < PIOS_SYS_SERIAL_NUM_BINARY_LEN; i++) {
        array[i] = (i < sizeof(mac)) ? mac[i] : 0;
    }
    return 0;
}

int32_t PIOS_SYS_SerialNumberGet(char str[PIOS_SYS_SERIAL_NUM_ASCII_LEN + 1])
{
    uint8_t bin[PIOS_SYS_SERIAL_NUM_BINARY_LEN];

    if (PIOS_SYS_SerialNumberGetBinary(bin) != 0) {
        str[0] = '\0';
        return -1;
    }

    for (uint8_t i = 0; i < PIOS_SYS_SERIAL_NUM_ASCII_LEN; i++) {
        uint8_t nibble = (i & 1) ? (bin[i / 2] & 0x0F) : (bin[i / 2] >> 4);
        str[i] = "0123456789ABCDEF"[nibble];
    }
    str[PIOS_SYS_SERIAL_NUM_ASCII_LEN] = '\0';
    return 0;
}

#endif /* PIOS_INCLUDE_SYS */
