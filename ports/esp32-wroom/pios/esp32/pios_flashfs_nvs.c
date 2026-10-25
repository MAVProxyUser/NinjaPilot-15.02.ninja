/**
 ******************************************************************************
 * @file       pios_flashfs_nvs.c
 * @author     NinjaPilot, 2026
 * @brief      PIOS_FLASHFS settings storage, backed by ESP-IDF's NVS.
 *
 * PiOS stores settings as whole UAVObjects keyed by object id and instance.
 * NVS stores blobs keyed by string. That is close enough to a direct mapping
 * that the whole of PIOS_FLASHFS falls out of five short functions, and the
 * existing UAVObjSave()/UAVObjLoad() path then works unchanged -- no object
 * needs to know it is being persisted differently from an STM32 board.
 *
 * NVS is the right fit for SETTINGS specifically: small values, written
 * rarely, and it does its own wear levelling. It is deliberately NOT used for
 * the DebugLog flight recorder, which also sits behind this interface --
 * that writes continuously in a ring, and pushing that through NVS would mean
 * heavy write amplification for no benefit. The log wants a raw partition,
 * and stays stubbed until it gets one.
 *
 * Storage lives in the dedicated 'settings' partition rather than the default
 * 'nvs' one, so a settings-full condition can never disturb anything else and
 * PIOS_FLASHFS_Format() can erase everything it owns without collateral.
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

#include "pios.h"

#if defined(PIOS_INCLUDE_FLASH)

#include <pios_flashfs.h>
#include "nvs_flash.h"
#include "nvs.h"

#define PIOS_NVS_PARTITION "settings"
#define PIOS_NVS_NAMESPACE "uavo"

/* Non-zero so callers can use it as a validity check, which systemmod.c
 * already does before asking for stats. */
#define PIOS_NVS_FS_ID     0x4E565301u

static nvs_handle_t nvs_fs;
static bool nvs_fs_ready;

/*
 * Object id plus instance as an NVS key.
 *
 * NVS keys are at most 15 characters plus a terminator, and this produces
 * exactly 12, so there is no truncation to worry about -- which matters,
 * because two objects colliding on a truncated key would silently return
 * each other's settings.
 */
static void nvs_key_for(char *out, uint32_t obj_id, uint16_t inst_id)
{
    snprintf(out, 16, "%08lX%04X", (unsigned long)obj_id, (unsigned)inst_id);
}

static bool nvs_fs_check(uintptr_t fs_id)
{
    return nvs_fs_ready && fs_id == PIOS_NVS_FS_ID;
}

int32_t PIOS_ESP32_FLASHFS_Init(uintptr_t *fs_id)
{
    PIOS_Assert(fs_id);

    esp_err_t err = nvs_flash_init_partition(PIOS_NVS_PARTITION);

    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        /* Either the partition filled with dead entries or it was written by
         * a newer NVS format. Both are recoverable only by erasing, and
         * losing settings beats refusing to boot. */
        if (nvs_flash_erase_partition(PIOS_NVS_PARTITION) != ESP_OK) {
            return -1;
        }
        err = nvs_flash_init_partition(PIOS_NVS_PARTITION);
    }
    if (err != ESP_OK) {
        return -1;
    }

    if (nvs_open_from_partition(PIOS_NVS_PARTITION, PIOS_NVS_NAMESPACE,
                                NVS_READWRITE, &nvs_fs) != ESP_OK) {
        return -1;
    }

    nvs_fs_ready = true;
    *fs_id       = PIOS_NVS_FS_ID;
    return 0;
}

/*
 * First-boot marker.
 *
 * The target compiles in a default airframe so a freshly flashed board is
 * usable, but once settings live in NVS those defaults must stop overwriting
 * what the operator saved. This is the flag that separates the two cases.
 */
bool PIOS_ESP32_FLASHFS_IsProvisioned(void)
{
    uint8_t v = 0;

    if (!nvs_fs_ready) {
        return false;
    }
    return nvs_get_u8(nvs_fs, "provisioned", &v) == ESP_OK && v != 0;
}

void PIOS_ESP32_FLASHFS_MarkProvisioned(void)
{
    if (!nvs_fs_ready) {
        return;
    }
    if (nvs_set_u8(nvs_fs, "provisioned", 1) == ESP_OK) {
        (void)nvs_commit(nvs_fs);
    }
}

int32_t PIOS_FLASHFS_ObjSave(uintptr_t fs_id, uint32_t obj_id, uint16_t obj_inst_id,
                             uint8_t *obj_data, uint16_t obj_size)
{
    char key[16];

    if (!nvs_fs_check(fs_id) || !obj_data) {
        return -1;
    }
    nvs_key_for(key, obj_id, obj_inst_id);

    if (nvs_set_blob(nvs_fs, key, obj_data, obj_size) != ESP_OK) {
        return -1;
    }
    /* Commit per save. Settings are written by hand from the GCS, so the
     * cost is irrelevant, and a half-written settings partition after a
     * power cut is not a trade worth making. */
    if (nvs_commit(nvs_fs) != ESP_OK) {
        return -1;
    }
    return 0;
}

int32_t PIOS_FLASHFS_ObjLoad(uintptr_t fs_id, uint32_t obj_id, uint16_t obj_inst_id,
                             uint8_t *obj_data, uint16_t obj_size)
{
    char key[16];
    size_t stored = 0;

    if (!nvs_fs_check(fs_id) || !obj_data) {
        return -1;
    }
    nvs_key_for(key, obj_id, obj_inst_id);

    if (nvs_get_blob(nvs_fs, key, NULL, &stored) != ESP_OK) {
        return -1;   /* nothing stored -- caller keeps its compiled-in defaults */
    }

    /*
     * Size mismatch means the object's layout changed since this was written
     * -- a field added, or an array resized. Loading it would quietly
     * scramble every field past the change, so refuse and let the defaults
     * stand. The stale entry is dropped so it cannot mislead a later boot.
     */
    if (stored != obj_size) {
        (void)nvs_erase_key(nvs_fs, key);
        (void)nvs_commit(nvs_fs);
        return -1;
    }

    if (nvs_get_blob(nvs_fs, key, obj_data, &stored) != ESP_OK) {
        return -1;
    }
    return 0;
}

int32_t PIOS_FLASHFS_ObjDelete(uintptr_t fs_id, uint32_t obj_id, uint16_t obj_inst_id)
{
    char key[16];

    if (!nvs_fs_check(fs_id)) {
        return -1;
    }
    nvs_key_for(key, obj_id, obj_inst_id);

    /* Already absent is success: the caller wanted it gone. */
    esp_err_t err = nvs_erase_key(nvs_fs, key);

    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) {
        return -1;
    }
    return (nvs_commit(nvs_fs) == ESP_OK) ? 0 : -1;
}

int32_t PIOS_FLASHFS_Format(uintptr_t fs_id)
{
    if (!nvs_fs_check(fs_id)) {
        return -1;
    }
    if (nvs_erase_all(nvs_fs) != ESP_OK) {
        return -1;
    }
    return (nvs_commit(nvs_fs) == ESP_OK) ? 0 : -1;
}

int32_t PIOS_FLASHFS_GetStats(uintptr_t fs_id, struct PIOS_FLASHFS_Stats *stats)
{
    nvs_stats_t st;

    if (!nvs_fs_check(fs_id) || !stats) {
        return -1;
    }
    if (nvs_get_stats(PIOS_NVS_PARTITION, &st) != ESP_OK) {
        return -1;
    }
    /* PiOS counts fixed-size slots; NVS counts entries. Neither maps exactly
     * onto the other, but "how much room is left" is the only question this
     * is ever used to answer, and entries carry that faithfully. */
    stats->num_active_slots = (uint16_t)st.used_entries;
    stats->num_free_slots   = (uint16_t)st.free_entries;
    return 0;
}

#endif /* PIOS_INCLUDE_FLASH */
