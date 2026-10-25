/**
 ******************************************************************************
 * @file       pios_i2c.c
 * @author     NinjaPilot, 2026
 * @brief      ESP32 I2C master, presented through the PiOS I2C interface.
 *
 * PiOS models a bus access as a list of transactions (address + direction +
 * buffer). IDF's i2c_master API is device-oriented rather than
 * transaction-oriented, so this file bridges the two:
 *
 *   - a lone WRITE            -> i2c_master_transmit()
 *   - a lone READ             -> i2c_master_receive()
 *   - WRITE then READ to the
 *     same address            -> i2c_master_transmit_receive()
 *
 * That third case is the important one. It is the register-read pattern every
 * sensor driver uses, and it MUST be issued as a repeated START rather than
 * two separate transactions -- a STOP between the two halves lets another
 * master (or a retry) slip in and the device forgets which register was
 * selected. i2c_master_transmit_receive() does the repeated START for us.
 *
 * Device handles are created lazily per 7-bit address and cached, because
 * PiOS addresses devices per transaction while IDF wants a handle per device.
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

#ifdef PIOS_INCLUDE_I2C

#include "driver/i2c_master.h"
#include "freertos/semphr.h"

#define PIOS_ESP32_I2C_MAX_BUSES   2
#define PIOS_ESP32_I2C_MAX_DEVS    8
#define PIOS_ESP32_I2C_TIMEOUT_MS  50

struct i2c_dev_slot {
    uint16_t addr;
    i2c_master_dev_handle_t handle;
    bool in_use;
};

struct pios_esp32_i2c_bus {
    const struct pios_esp32_i2c_cfg *cfg;
    i2c_master_bus_handle_t bus;
    struct i2c_dev_slot devs[PIOS_ESP32_I2C_MAX_DEVS];
    SemaphoreHandle_t lock;
    bool in_use;
};

static struct pios_esp32_i2c_bus i2c_buses[PIOS_ESP32_I2C_MAX_BUSES];

/* Diagnostics PiOS exposes. Only a failure count is real here -- there is no
 * FSM to trace, and reporting a fabricated one would be worse than reporting
 * none. The posix backend takes the same line. */
static uint32_t i2c_txn_errors;

static struct pios_esp32_i2c_bus *i2c_bus_from_id(uint32_t id)
{
    if (id == 0 || id > PIOS_ESP32_I2C_MAX_BUSES) {
        return NULL;
    }
    struct pios_esp32_i2c_bus *b = &i2c_buses[id - 1];

    return b->in_use ? b : NULL;
}

/* Find (or create) the IDF device handle for a 7-bit address. */
static i2c_master_dev_handle_t i2c_handle_for(struct pios_esp32_i2c_bus *b, uint16_t addr)
{
    for (uint8_t i = 0; i < PIOS_ESP32_I2C_MAX_DEVS; i++) {
        if (b->devs[i].in_use && b->devs[i].addr == addr) {
            return b->devs[i].handle;
        }
    }
    for (uint8_t i = 0; i < PIOS_ESP32_I2C_MAX_DEVS; i++) {
        if (!b->devs[i].in_use) {
            i2c_device_config_t dcfg = {
                .dev_addr_length = I2C_ADDR_BIT_LEN_7,
                .device_address  = addr,
                .scl_speed_hz    = b->cfg->speed_hz,
            };
            if (i2c_master_bus_add_device(b->bus, &dcfg, &b->devs[i].handle) != ESP_OK) {
                return NULL;
            }
            b->devs[i].addr   = addr;
            b->devs[i].in_use = true;
            return b->devs[i].handle;
        }
    }
    return NULL;
}

int32_t PIOS_ESP32_I2C_Init(uint32_t *i2c_id, const struct pios_esp32_i2c_cfg *cfg)
{
    PIOS_Assert(i2c_id);
    PIOS_Assert(cfg);

    struct pios_esp32_i2c_bus *b = NULL;
    uint32_t slot = 0;

    for (uint32_t i = 0; i < PIOS_ESP32_I2C_MAX_BUSES; i++) {
        if (!i2c_buses[i].in_use) {
            b    = &i2c_buses[i];
            slot = i + 1;
            break;
        }
    }
    if (!b) {
        return -1;
    }

    i2c_master_bus_config_t bcfg = {
        .i2c_port          = cfg->port,
        .sda_io_num        = cfg->sda_pin,
        .scl_io_num        = cfg->scl_pin,
        .clk_source        = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        /* Most breakouts already carry pullups. Enabling the internal ones
         * too is harmless and rescues a board that does not. They are weak
         * (~45k), so they are not a substitute for real 2.2k-4.7k pullups at
         * 400kHz. */
        .flags.enable_internal_pullup = true,
    };

    if (i2c_new_master_bus(&bcfg, &b->bus) != ESP_OK) {
        return -1;
    }

    b->lock = xSemaphoreCreateBinary();
    if (!b->lock) {
        return -1;
    }
    xSemaphoreGive(b->lock);

    b->cfg    = cfg;
    b->in_use = true;
    *i2c_id   = slot;
    return 0;
}

/**
 * Probe for a device. Useful during bring-up to tell "nothing on the bus"
 * apart from "device present but the driver does not like it".
 */
bool PIOS_ESP32_I2C_Probe(uint32_t i2c_id, uint16_t addr)
{
    struct pios_esp32_i2c_bus *b = i2c_bus_from_id(i2c_id);

    if (!b) {
        return false;
    }
    return i2c_master_probe(b->bus, addr, PIOS_ESP32_I2C_TIMEOUT_MS) == ESP_OK;
}

int32_t PIOS_I2C_Transfer(uint32_t i2c_id, const struct pios_i2c_txn txn_list[], uint32_t num_txns)
{
    struct pios_esp32_i2c_bus *b = i2c_bus_from_id(i2c_id);

    if (!b || num_txns == 0) {
        return -1;
    }

    if (xSemaphoreTake(b->lock, portMAX_DELAY) != pdTRUE) {
        return -1;
    }

    int32_t rc = 0;
    uint32_t i = 0;

    while (i < num_txns) {
        const struct pios_i2c_txn *t = &txn_list[i];
        i2c_master_dev_handle_t h    = i2c_handle_for(b, t->addr);

        if (!h) {
            rc = -1;
            break;
        }

        /* Fuse WRITE-then-READ to the same address into one repeated-START
         * transaction. See the file header for why this matters. */
        if (t->rw == PIOS_I2C_TXN_WRITE && (i + 1) < num_txns
            && txn_list[i + 1].rw == PIOS_I2C_TXN_READ
            && txn_list[i + 1].addr == t->addr) {
            const struct pios_i2c_txn *r = &txn_list[i + 1];
            if (i2c_master_transmit_receive(h, t->buf, t->len, r->buf, r->len,
                                            PIOS_ESP32_I2C_TIMEOUT_MS) != ESP_OK) {
                rc = -1;
                break;
            }
            i += 2;
            continue;
        }

        if (t->rw == PIOS_I2C_TXN_WRITE) {
            if (i2c_master_transmit(h, t->buf, t->len, PIOS_ESP32_I2C_TIMEOUT_MS) != ESP_OK) {
                rc = -1;
                break;
            }
        } else {
            if (i2c_master_receive(h, t->buf, t->len, PIOS_ESP32_I2C_TIMEOUT_MS) != ESP_OK) {
                rc = -1;
                break;
            }
        }
        i++;
    }

    if (rc != 0) {
        i2c_txn_errors++;
    }

    xSemaphoreGive(b->lock);
    return rc;
}

int32_t PIOS_I2C_Transfer_Callback(__attribute__((unused)) uint32_t i2c_id,
                                   __attribute__((unused)) const struct pios_i2c_txn txn_list[],
                                   __attribute__((unused)) uint32_t num_txns,
                                   __attribute__((unused)) void *callback)
{
    /* No async path on this backend; every caller in this tree uses the
     * blocking form. Refuse rather than silently running synchronously and
     * never invoking the callback. */
    return -1;
}

void PIOS_I2C_EV_IRQ_Handler(__attribute__((unused)) uint32_t i2c_id)
{}

void PIOS_I2C_ER_IRQ_Handler(__attribute__((unused)) uint32_t i2c_id)
{}

void PIOS_I2C_IRQ_Handler(__attribute__((unused)) uint32_t i2c_id)
{}

void PIOS_I2C_GetDiagnostics(struct pios_i2c_fault_history *data, uint8_t *error_counts)
{
    if (data) {
        memset(data, 0, sizeof(*data));
    }
    if (error_counts) {
        /* One byte, matching pios/posix: the caller passes a pointer into
         * the I2CStats UAVObject, not a sized array. */
        *error_counts = (i2c_txn_errors > 255) ? 255 : (uint8_t)i2c_txn_errors;
    }
}

#endif /* PIOS_INCLUDE_I2C */
