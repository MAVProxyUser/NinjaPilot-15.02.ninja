/**
 ******************************************************************************
 *
 * @file       pios_i2c.c
 * @author     NinjaPilot, 2026
 * @brief      I2C functions implemented against the Linux i2c-dev interface,
 *             so the existing PIOS sensor drivers run unmodified on a Linux
 *             host (OSD32MP1) exactly as they do on an STM32.
 * @see        The GNU Public License (GPL) Version 3
 * @defgroup   PIOS_I2C I2C Functions
 * @{
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
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "pios.h"

#ifdef PIOS_INCLUDE_I2C

#include <pios_i2c_posix.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>

/*
 * The i2c-dev ABI, declared here rather than by including <linux/i2c-dev.h>.
 * That header collides with <linux/i2c.h> over `struct i2c_msg` on a lot of
 * toolchains, and this is the entire ABI we need. These values are stable
 * kernel UAPI.
 */
#define LINUX_I2C_RDWR       0x0707
#define LINUX_I2C_M_RD       0x0001

struct linux_i2c_msg {
    uint16_t addr;
    uint16_t flags;
    uint16_t len;
    uint8_t *buf;
};

struct linux_i2c_rdwr_data {
    struct linux_i2c_msg *msgs;
    uint32_t nmsgs;
};

/*
 * PIOS transaction lists are short - a register write followed by a read is
 * the common shape, and nothing in the tree uses more than a handful. Cap it
 * low deliberately: this array lives on the caller's FreeRTOS task stack, and
 * the kernel's own ceiling (42) would put 504 bytes there.
 */
#define PIOS_I2C_MAX_TXNS    8

#define PIOS_I2C_POSIX_MAGIC 0x69326370  /* 'i2cp' */
#define PIOS_I2C_MAX_ADAPTERS 3

struct pios_i2c_posix_adapter {
    uint32_t magic;
    int      fd;
    xSemaphoreHandle lock;
    uint32_t txn_ok;
    uint32_t txn_err;
    int32_t  last_errno;
};

/* Static, so this layer has no allocator dependency. */
static struct pios_i2c_posix_adapter pios_i2c_adapters[PIOS_I2C_MAX_ADAPTERS];
static uint8_t pios_i2c_num_adapters;

static bool PIOS_I2C_validate(struct pios_i2c_posix_adapter *adapter)
{
    return adapter && adapter->magic == PIOS_I2C_POSIX_MAGIC && adapter->fd >= 0;
}

int32_t PIOS_I2C_Posix_Init(uint32_t *i2c_id, const char *devpath)
{
    if (!i2c_id || !devpath) {
        return -1;
    }
    if (pios_i2c_num_adapters >= PIOS_I2C_MAX_ADAPTERS) {
        return -1;
    }

    struct pios_i2c_posix_adapter *adapter = &pios_i2c_adapters[pios_i2c_num_adapters];

    adapter->fd = open(devpath, O_RDWR);
    if (adapter->fd < 0) {
        return -2;
    }

    /*
     * A FreeRTOS mutex, NOT a pthread one. The Posix port runs exactly one
     * task at a time, so blocking a pthread blocks the entire scheduler -
     * every other task included. Taking a FreeRTOS mutex instead yields
     * inside the port and lets other tasks run while this one waits.
     */
    adapter->lock = xSemaphoreCreateMutex();
    if (!adapter->lock) {
        close(adapter->fd);
        adapter->fd = -1;
        return -2;
    }

    adapter->txn_ok     = 0;
    adapter->txn_err    = 0;
    adapter->last_errno = 0;
    adapter->magic      = PIOS_I2C_POSIX_MAGIC;

    pios_i2c_num_adapters++;
    *i2c_id = (uint32_t)adapter;
    return 0;
}

/**
 * @brief Run a PIOS transaction list as one combined i2c-dev transfer.
 *
 * The mapping is exact: each pios_i2c_txn becomes one struct i2c_msg, and the
 * whole list goes down in a single I2C_RDWR ioctl. That matters - the kernel
 * then issues a repeated START between messages instead of STOP/START, which
 * is both what the PIOS API means by a transaction list and measurably faster
 * than doing the writes and reads as separate ioctls.
 *
 * NOTE ON BLOCKING: this ioctl does not return until the transfer completes
 * on the wire, and it is not a FreeRTOS blocking point - the Posix port cannot
 * schedule another task while it runs. So the whole firmware stalls for the
 * duration of every sensor read. That is precisely why the I2C bus clock
 * matters so much on this board: at the 100 kHz device-tree default a 14-byte
 * MPU burst stalls the scheduler for ~1.68 ms out of a 2 ms period, versus
 * ~0.5 ms at 400 kHz. See osd32mp1/CLAUDE.md.
 *
 * @return 0 on success, -1 on a bad handle or unusable list, -2 on bus error
 */
int32_t PIOS_I2C_Transfer(uint32_t i2c_id, const struct pios_i2c_txn txn_list[], uint32_t num_txns)
{
    struct pios_i2c_posix_adapter *adapter = (struct pios_i2c_posix_adapter *)i2c_id;

    if (!PIOS_I2C_validate(adapter)) {
        return -1;
    }
    if (!txn_list || num_txns == 0 || num_txns > PIOS_I2C_MAX_TXNS) {
        return -1;
    }

    struct linux_i2c_msg msgs[PIOS_I2C_MAX_TXNS];
    for (uint32_t i = 0; i < num_txns; i++) {
        msgs[i].addr  = txn_list[i].addr;
        msgs[i].flags = (txn_list[i].rw == PIOS_I2C_TXN_READ) ? LINUX_I2C_M_RD : 0;
        msgs[i].len   = txn_list[i].len;
        msgs[i].buf   = txn_list[i].buf;
    }

    if (xSemaphoreTake(adapter->lock, portMAX_DELAY) != pdTRUE) {
        return -2;
    }

    struct linux_i2c_rdwr_data req = {
        .msgs  = msgs,
        .nmsgs = num_txns,
    };
    int rc = ioctl(adapter->fd, LINUX_I2C_RDWR, &req);
    if (rc < 0) {
        adapter->last_errno = errno;
        adapter->txn_err++;
    } else {
        adapter->txn_ok++;
    }

    xSemaphoreGive(adapter->lock);

    return (rc < 0) ? -2 : 0;
}

/**
 * @brief Synchronous stand-in for the async STM32 entry point.
 *
 * The STM32 driver completes this from an interrupt. There is no such thing
 * here - the kernel owns the controller - so the transfer is done inline and
 * the callback, if any, is invoked on return. Nothing in the tree currently
 * calls this; it exists so drivers written against the full API still link.
 */
int32_t PIOS_I2C_Transfer_Callback(uint32_t i2c_id, const struct pios_i2c_txn txn_list[], uint32_t num_txns, void *callback)
{
    int32_t rc = PIOS_I2C_Transfer(i2c_id, txn_list, num_txns);

    if (callback) {
        ((void (*)(bool))callback)(rc == 0);
    }
    return rc;
}

void PIOS_I2C_Posix_GetCounters(uint32_t i2c_id, uint32_t *ok, uint32_t *err, int32_t *last_errno)
{
    struct pios_i2c_posix_adapter *adapter = (struct pios_i2c_posix_adapter *)i2c_id;

    if (!PIOS_I2C_validate(adapter)) {
        return;
    }
    if (ok) {
        *ok = adapter->txn_ok;
    }
    if (err) {
        *err = adapter->txn_err;
    }
    if (last_errno) {
        *last_errno = adapter->last_errno;
    }
}

/*
 * The kernel driver handles interrupts and error recovery, so these exist
 * only to satisfy the PIOS API. There is nothing sensible for them to do.
 */
void PIOS_I2C_EV_IRQ_Handler(__attribute__((unused)) uint32_t i2c_id) {}
void PIOS_I2C_ER_IRQ_Handler(__attribute__((unused)) uint32_t i2c_id) {}
void PIOS_I2C_IRQ_Handler(__attribute__((unused)) uint32_t i2c_id) {}

/**
 * @brief Report bus health.
 *
 * The STM32 version dumps a ring buffer of peripheral state captured when its
 * state machine wedged. None of that exists here, so the history is zeroed and
 * only the error count is real - reporting a fabricated FSM trace would be
 * worse than reporting none.
 */
void PIOS_I2C_GetDiagnostics(struct pios_i2c_fault_history *data, uint8_t *error_counts)
{
    if (data) {
        memset(data, 0, sizeof(*data));
    }
    if (error_counts) {
        uint32_t total = 0;
        for (uint8_t i = 0; i < pios_i2c_num_adapters; i++) {
            total += pios_i2c_adapters[i].txn_err;
        }
        *error_counts = (total > 255) ? 255 : (uint8_t)total;
    }
}

#endif /* PIOS_INCLUDE_I2C */

/**
 * @}
 */
