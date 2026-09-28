/**
 ******************************************************************************
 * @addtogroup OpenPilotModules OpenPilot Modules
 * @{
 * @addtogroup DroneCANModule DroneCAN Module
 * @brief DroneCAN v0 on a PIOS CAN peripheral: node census from NodeStatus,
 *        a centralized dynamic node-id allocator (the same handshake the
 *        posix sensors hub serves), our own NodeStatus once a second, and
 *        ESC telemetry (uavcan.equipment.esc.Status) into UAVObjects.
 * @{
 *
 * @file       dronecan.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2026.
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

#include <openpilot.h>
#include <pios_can.h>
#include "dronecan.h"
#include "dronecanstatus.h"
#include "dronecanescstatus.h"

#if defined(PIOS_INCLUDE_CAN)

#define STACK_SIZE_BYTES        2048
#define TASK_PRIORITY           (tskIDLE_PRIORITY + 2)

/* DroneCAN v0 wire constants (verified against pydronecan / the posix hub) */
#define DC_NODE_ID              10u      /* the flight controller on the bus */
#define DC_DTID_ALLOCATION      1u       /* uavcan.protocol.dynamic_node_id.Allocation */
#define DC_ALLOCATION_BASE_CRC  0xF258u  /* crc16-ccitt of its DSDL signature */
#define DC_DTID_NODESTATUS      341u     /* uavcan.protocol.NodeStatus */
#define DC_DTID_ESC_STATUS      1034u    /* uavcan.equipment.esc.Status */
#define DC_PRIO_LOW             30u
#define DNA_RANGE_MIN           1u
#define DNA_RANGE_MAX           125u
#define DNA_FOLLOWUP_TMO_MS     500u
#define DNA_MAX_NODES           32u
#define NODE_TABLE_SIZE         DRONECANSTATUS_NODEID_NUMELEM
#define ESC_TABLE_SIZE          DRONECANESCSTATUS_NODEID_NUMELEM
#define NODE_STALE_MS           5000u

struct node_entry {
    uint8_t  node_id;
    uint8_t  health;
    uint8_t  mode;
    uint32_t uptime;
    uint32_t last_seen;   /* ticks */
};

struct dna_entry {
    uint8_t node_id;
    uint8_t uid[16];
};

struct reasm {
    uint8_t  node_id;
    uint8_t  buf[32];
    uint8_t  len;
    uint8_t  tid;
    uint8_t  toggle;
    bool     active;
};

static xTaskHandle taskHandle;
static uint32_t can_id;

static struct node_entry nodes[NODE_TABLE_SIZE];
static struct dna_entry  dna_table[DNA_MAX_NODES];
static uint8_t  dna_table_count;
static uint8_t  dna_seen[16];
static uint8_t  dna_query[16];
static uint8_t  dna_query_len;
static uint32_t dna_query_ts;
static uint8_t  dna_tid;
static uint32_t dna_allocations;
static uint32_t anon_requests;
static uint8_t  ns_tid;
static struct reasm esc_rx[4];

static void dronecanTask(void *parameters);

int32_t DroneCANStart(void)
{
    if (!can_id) {
        return -1;
    }
    xTaskCreate(dronecanTask, "DroneCAN", STACK_SIZE_BYTES / 4, NULL, TASK_PRIORITY, &taskHandle);
    return 0;
}

int32_t DroneCANInitialize(void)
{
#if defined(PIOS_CAN_DRONECAN)
    can_id = PIOS_CAN_DRONECAN;
#endif
    if (!can_id) {
        return -1;
    }
    DroneCANStatusInitialize();
    DroneCANESCStatusInitialize();
    return 0;
}
MODULE_INITCALL(DroneCANInitialize, DroneCANStart);

/* ---- bit-level decode, libcanard semantics (as in the posix hub) ---- */
static uint64_t dc_bits(const uint8_t *buf, uint32_t bit_ofs, uint8_t nbits)
{
    uint8_t bytes[8] = { 0 };
    uint8_t nbytes   = (uint8_t)((nbits + 7u) / 8u);

    for (uint8_t i = 0; i < nbytes; i++) {
        uint8_t want = (uint8_t)((nbits - i * 8u) >= 8u ? 8u : (nbits - i * 8u));
        uint8_t v    = 0;
        for (uint8_t b = 0; b < want; b++) {
            uint32_t sbit = bit_ofs + i * 8u + b;
            uint8_t bit   = (uint8_t)((buf[sbit / 8u] >> (7u - (sbit % 8u))) & 1u);
            v = (uint8_t)((v << 1) | bit);
        }
        bytes[i] = v;
    }
    uint64_t out = 0;
    for (uint8_t i = 0; i < nbytes; i++) {
        out |= (uint64_t)bytes[i] << (8u * i);
    }
    return out;
}

static int64_t dc_sbits(const uint8_t *buf, uint32_t bit_ofs, uint8_t nbits)
{
    uint64_t u = dc_bits(buf, bit_ofs, nbits);

    if (u & (1ull << (nbits - 1u))) {
        u |= ~((1ull << nbits) - 1ull);
    }
    return (int64_t)u;
}

static float f16_to_f32(uint16_t h)
{
    uint32_t sign = (uint32_t)(h & 0x8000) << 16;
    int exp       = (h >> 10) & 0x1F;
    uint32_t man  = h & 0x3FF;
    uint32_t bits;

    if (exp == 0) {
        if (!man) {
            bits = sign;
        } else {
            exp = -1;
            do {
                exp++;
                man <<= 1;
            } while (!(man & 0x400));
            man &= 0x3FF;
            bits = sign | (uint32_t)(127 - 15 - exp) << 23 | man << 13;
        }
    } else if (exp == 0x1F) {
        bits = sign | 0x7F800000u | man << 13;
    } else {
        bits = sign | (uint32_t)(exp - 15 + 127) << 23 | man << 13;
    }
    float f;
    memcpy(&f, &bits, sizeof(f));
    return f;
}

static uint16_t crc16_ccitt(const uint8_t *data, uint32_t len, uint16_t crc)
{
    for (uint32_t i = 0; i < len; i++) {
        crc ^= (uint16_t)data[i] << 8;
        for (int b = 0; b < 8; b++) {
            crc = (crc & 0x8000) ? (uint16_t)((crc << 1) ^ 0x1021) : (uint16_t)(crc << 1);
        }
    }
    return crc;
}

/* ---- transmit helpers ---- */
static void tx_frame(uint32_t id, const uint8_t *data, uint8_t dlc)
{
    struct pios_can_frame f;

    f.id  = id;
    f.ext = true;
    f.dlc = dlc;
    memset(f.data, 0, sizeof(f.data));
    memcpy(f.data, data, dlc);
    for (int attempt = 0; attempt < 4; attempt++) {
        if (PIOS_CAN_Send(can_id, &f) == 0) {
            return;
        }
        vTaskDelay(1);
    }
}

/* Broadcast a message transfer from us: single frame, or multi-frame with
 * the transfer CRC prepended, tail bytes stamped SOT/EOT/toggle/transfer-id. */
static void dc_broadcast(uint16_t dtid, uint16_t base_crc, const uint8_t *payload, uint8_t len)
{
    uint8_t stream[2 + 16];
    uint8_t slen = 0;
    uint8_t tid  = (uint8_t)(dna_tid++ & 0x1F);

    if (len > 7) {
        uint16_t crc = crc16_ccitt(payload, len, base_crc);
        stream[slen++] = (uint8_t)(crc & 0xFF);
        stream[slen++] = (uint8_t)(crc >> 8);
    }
    memcpy(stream + slen, payload, len);
    slen = (uint8_t)(slen + len);
    uint32_t id  = (DC_PRIO_LOW << 24) | ((uint32_t)dtid << 8) | DC_NODE_ID;
    uint8_t  ofs = 0, toggle = 0, first = 1;
    do {
        uint8_t chunk = (uint8_t)((slen - ofs) > 7 ? 7 : (slen - ofs));
        uint8_t frame[8];
        memcpy(frame, stream + ofs, chunk);
        uint8_t sot = first ? 0x80u : 0u;
        uint8_t eot = ((uint8_t)(ofs + chunk) >= slen) ? 0x40u : 0u;
        frame[chunk] = (uint8_t)(sot | eot | (toggle ? 0x20u : 0u) | tid);
        tx_frame(id, frame, (uint8_t)(chunk + 1));
        ofs     = (uint8_t)(ofs + chunk);
        toggle ^= 1u;
        first   = 0;
    } while (ofs < slen);
}

/* uavcan.protocol.NodeStatus from us: uptime u32, health/mode/sub-mode byte,
 * vendor status u16 (the allocation count), single frame. */
static void nodestatus_tx(void)
{
    uint32_t uptime = xTaskGetTickCount() / configTICK_RATE_HZ;
    uint16_t vend   = (uint16_t)dna_allocations;
    uint8_t  d[8];

    d[0] = (uint8_t)(uptime & 0xFF);
    d[1] = (uint8_t)(uptime >> 8);
    d[2] = (uint8_t)(uptime >> 16);
    d[3] = (uint8_t)(uptime >> 24);
    d[4] = 0;
    d[5] = (uint8_t)(vend & 0xFF);
    d[6] = (uint8_t)(vend >> 8);
    d[7] = (uint8_t)(0xC0u | (ns_tid++ & 0x1F));
    tx_frame((DC_PRIO_LOW << 24) | ((uint32_t)DC_DTID_NODESTATUS << 8) | DC_NODE_ID, d, 8);
}

/* ---- dynamic node-id allocation (centralized server) ---- */
static bool dna_id_taken(uint8_t id)
{
    if (id == DC_NODE_ID) {
        return true;
    }
    for (uint8_t i = 0; i < dna_table_count; i++) {
        if (dna_table[i].node_id == id) {
            return true;
        }
    }
    return (dna_seen[id >> 3] & (uint8_t)(1u << (id & 7))) != 0;
}

static uint8_t dna_assign(const uint8_t *uid, uint8_t preferred)
{
    for (uint8_t i = 0; i < dna_table_count; i++) {
        if (memcmp(dna_table[i].uid, uid, 16) == 0) {
            return dna_table[i].node_id;
        }
    }
    uint8_t alloc = 0;
    if (preferred >= DNA_RANGE_MIN && preferred <= DNA_RANGE_MAX && !dna_id_taken(preferred)) {
        alloc = preferred;
    } else {
        for (uint8_t id = DNA_RANGE_MAX; id >= DNA_RANGE_MIN; id--) {
            if (!dna_id_taken(id)) {
                alloc = id;
                break;
            }
        }
    }
    if (alloc && dna_table_count < DNA_MAX_NODES) {
        dna_table[dna_table_count].node_id = alloc;
        memcpy(dna_table[dna_table_count].uid, uid, 16);
        dna_table_count++;
    }
    return alloc;
}

static uint8_t dna_pack(uint8_t node_id, uint8_t first_part, const uint8_t *uid, uint8_t uid_len, uint8_t *out)
{
    out[0] = (uint8_t)((node_id << 1) | (first_part & 1u));
    memcpy(out + 1, uid, uid_len);
    return (uint8_t)(1 + uid_len);
}

/* One anonymous Allocation request (always a single frame). Three-stage
 * handshake: echo the first 6 uid bytes, echo 12, then assign on 16. */
static void dna_handle_request(const uint8_t *data, uint8_t dlc)
{
    if (dlc < 2) {
        return;
    }
    uint8_t tail = data[dlc - 1];
    if ((tail & 0xC0u) != 0xC0u) {
        return;
    }
    anon_requests++;
    uint8_t plen       = (uint8_t)(dlc - 1);
    uint8_t first_part = data[0] & 1u;
    uint8_t req_node   = (uint8_t)(data[0] >> 1);
    const uint8_t *uid = &data[1];
    uint8_t uid_len    = (uint8_t)(plen - 1);
    uint32_t now       = xTaskGetTickCount();

    if (dna_query_len && (now - dna_query_ts) > (DNA_FOLLOWUP_TMO_MS / portTICK_RATE_MS)) {
        dna_query_len = 0;
    }
    uint8_t pl[17], n;
    if (first_part) {
        if (uid_len > 6) {
            uid_len = 6;
        }
        memcpy(dna_query, uid, uid_len);
        dna_query_len = uid_len;
        dna_query_ts  = now;
        n = dna_pack(0, 0, dna_query, dna_query_len, pl);
        dc_broadcast(DC_DTID_ALLOCATION, DC_ALLOCATION_BASE_CRC, pl, n);
    } else if (uid_len == 6 && dna_query_len == 6) {
        memcpy(dna_query + 6, uid, 6);
        dna_query_len = 12;
        dna_query_ts  = now;
        n = dna_pack(0, 0, dna_query, 12, pl);
        dc_broadcast(DC_DTID_ALLOCATION, DC_ALLOCATION_BASE_CRC, pl, n);
    } else if (uid_len == 4 && dna_query_len == 12) {
        memcpy(dna_query + 12, uid, 4);
        uint8_t alloc = dna_assign(dna_query, req_node);
        if (alloc) {
            n = dna_pack(alloc, 0, dna_query, 16, pl);
            dc_broadcast(DC_DTID_ALLOCATION, DC_ALLOCATION_BASE_CRC, pl, n);
            dna_allocations++;
        }
        dna_query_len = 0;
    }
}

/* ---- receive side ---- */
static struct node_entry *node_lookup(uint8_t node_id, bool create)
{
    struct node_entry *oldest = NULL;

    for (uint32_t i = 0; i < NODE_TABLE_SIZE; i++) {
        if (nodes[i].node_id == node_id) {
            return &nodes[i];
        }
        if (nodes[i].node_id == 0) {
            if (!oldest) {
                oldest = &nodes[i];
            }
        } else if (!create) {
            continue;
        } else if (!oldest || (int32_t)(nodes[i].last_seen - oldest->last_seen) < 0) {
            if (oldest && oldest->node_id == 0) {
                continue; /* keep the free slot */
            }
            oldest = &nodes[i];
        }
    }
    if (!create || !oldest) {
        return NULL;
    }
    memset(oldest, 0, sizeof(*oldest));
    oldest->node_id = node_id;
    return oldest;
}

/* Multi-frame reassembly keyed by source node; returns the payload length
 * (transfer CRC stripped) once a transfer completes, else 0. */
static uint8_t reasm_feed(struct reasm *pool, uint8_t npool, uint8_t node_id,
                          const uint8_t *data, uint8_t dlc, const uint8_t **payload)
{
    uint8_t tail = data[dlc - 1];
    uint8_t sot  = (uint8_t)(tail >> 7) & 1u, eot = (uint8_t)(tail >> 6) & 1u;
    uint8_t tog  = (uint8_t)(tail >> 5) & 1u, tid = tail & 0x1Fu;
    uint8_t nb   = (uint8_t)(dlc - 1);

    if (sot && eot) {
        *payload = data;
        return nb;
    }
    struct reasm *rx = NULL;
    for (uint8_t i = 0; i < npool; i++) {
        if (pool[i].active && pool[i].node_id == node_id) {
            rx = &pool[i];
            break;
        }
    }
    if (sot) {
        if (!rx) {
            for (uint8_t i = 0; i < npool; i++) {
                if (!pool[i].active) {
                    rx = &pool[i];
                    break;
                }
            }
        }
        if (!rx || tog != 0) {
            return 0;
        }
        rx->active  = true;
        rx->node_id = node_id;
        rx->len     = 0;
        rx->tid     = tid;
        rx->toggle  = 0;
    } else {
        if (!rx || tid != rx->tid || tog != (rx->toggle ^ 1u)) {
            if (rx) {
                rx->active = false;
            }
            return 0;
        }
        rx->toggle = tog;
    }
    if (rx->len + nb > sizeof(rx->buf)) {
        rx->active = false;
        return 0;
    }
    memcpy(&rx->buf[rx->len], data, nb);
    rx->len = (uint8_t)(rx->len + nb);
    if (eot) {
        rx->active = false;
        if (rx->len > 2) {
            *payload = rx->buf + 2;
            return (uint8_t)(rx->len - 2);
        }
    }
    return 0;
}

/* uavcan.equipment.esc.Status: error_count u32, voltage f16, current f16,
 * temperature f16 (K), rpm i18, power_rating_pct u7, esc_index u5. */
static void esc_status_decode(uint8_t node_id, const uint8_t *p, uint8_t n)
{
    if (n < 14) {
        return;
    }
    uint32_t err  = (uint32_t)dc_bits(p, 0, 32);
    float    volt = f16_to_f32((uint16_t)dc_bits(p, 32, 16));
    float    cur  = f16_to_f32((uint16_t)dc_bits(p, 48, 16));
    float    tk   = f16_to_f32((uint16_t)dc_bits(p, 64, 16));
    int32_t  rpm  = (int32_t)dc_sbits(p, 80, 18);
    uint8_t  idx  = (uint8_t)dc_bits(p, 105, 5);

    if (idx >= ESC_TABLE_SIZE) {
        return;
    }
    DroneCANESCStatusData esc;
    DroneCANESCStatusGet(&esc);
    esc.NodeId[idx]      = node_id;
    esc.Voltage[idx]     = volt;
    esc.Current[idx]     = cur;
    esc.Temperature[idx] = tk > 0.0f ? tk - 273.15f : 0.0f;
    esc.RPM[idx]         = rpm;
    esc.ErrorCount[idx]  = err;
    esc.Updates[idx]++;
    DroneCANESCStatusSet(&esc);
}

static void handle_frame(const struct pios_can_frame *f)
{
    if (!f->ext || f->dlc < 1) {
        return;
    }
    uint32_t id   = f->id;
    uint8_t  node = id & 0x7F;

    if (node == 0) {
        /* anonymous: (prio<<24)|(discriminator<<10)|((dtid&3)<<8), service bit clear */
        if (!(id & 0x80u) && ((id >> 8) & 0x3u) == DC_DTID_ALLOCATION) {
            dna_handle_request(f->data, f->dlc);
        }
        return;
    }
    dna_seen[node >> 3] |= (uint8_t)(1u << (node & 7));
    if (id & 0x80u) {
        return; /* service frames: not handled */
    }
    uint16_t dtid = (id >> 8) & 0xFFFF;
    uint8_t  tail = f->data[f->dlc - 1];

    struct node_entry *e = node_lookup(node, true);
    if (e) {
        e->last_seen = xTaskGetTickCount();
    }

    if (dtid == DC_DTID_NODESTATUS && f->dlc >= 8 && (tail & 0xC0u) == 0xC0u && e) {
        e->uptime = (uint32_t)f->data[0] | ((uint32_t)f->data[1] << 8) | ((uint32_t)f->data[2] << 16) | ((uint32_t)f->data[3] << 24);
        e->health = (f->data[4] >> 6) & 0x3;
        e->mode   = (f->data[4] >> 3) & 0x7;
        return;
    }
    if (dtid == DC_DTID_ESC_STATUS) {
        const uint8_t *pl = NULL;
        uint8_t n = reasm_feed(esc_rx, NELEMENTS(esc_rx), node, f->data, f->dlc, &pl);
        if (n) {
            esc_status_decode(node, pl, n);
        }
    }
}

static void publish_status(void)
{
    DroneCANStatusData st;
    struct pios_can_stats cs;

    DroneCANStatusGet(&st);
    PIOS_CAN_GetStats(can_id, &cs);
    st.RxFrames  = cs.rx_frames;
    st.TxFrames  = cs.tx_frames;
    st.RxDropped = cs.rx_dropped;
    st.TxDropped = cs.tx_dropped;
    st.TxErrorCounter    = cs.tx_errors;
    st.RxErrorCounter    = cs.rx_errors;
    st.BusOff = cs.bus_off ? DRONECANSTATUS_BUSOFF_TRUE : DRONECANSTATUS_BUSOFF_FALSE;
    st.AnonymousRequests = anon_requests;
    st.Allocations       = dna_allocations;
    uint32_t now = xTaskGetTickCount();
    uint8_t  count = 0;
    for (uint32_t i = 0; i < NODE_TABLE_SIZE; i++) {
        st.NodeId[i] = nodes[i].node_id;
        if (nodes[i].node_id) {
            count++;
            st.NodeHealth[i]   = nodes[i].health;
            st.NodeMode[i]     = nodes[i].mode >= 7 ? DRONECANSTATUS_NODEMODE_OFFLINE : (nodes[i].mode > 3 ? DRONECANSTATUS_NODEMODE_OFFLINE : nodes[i].mode);
            st.NodeUptime[i]   = nodes[i].uptime;
            uint32_t age = (now - nodes[i].last_seen) * portTICK_RATE_MS / 1000;
            st.NodeLastSeen[i] = age > 0xFFFF ? 0xFFFF : (uint16_t)age;
        } else {
            st.NodeHealth[i]   = 0;
            st.NodeMode[i]     = 0;
            st.NodeUptime[i]   = 0;
            st.NodeLastSeen[i] = 0;
        }
    }
    st.NodeCount = count;
    DroneCANStatusSet(&st);
}

static void dronecanTask(__attribute__((unused)) void *parameters)
{
    uint32_t last_ns = 0, last_pub = 0;
    struct pios_can_frame f;

    while (1) {
        while (PIOS_CAN_Receive(can_id, &f, 20)) {
            handle_frame(&f);
        }
        uint32_t now = xTaskGetTickCount();
        if ((now - last_ns) >= (1000 / portTICK_RATE_MS)) {
            last_ns = now;
            nodestatus_tx();
        }
        if ((now - last_pub) >= (500 / portTICK_RATE_MS)) {
            last_pub = now;
            publish_status();
        }
    }
}

#endif /* PIOS_INCLUDE_CAN */

/**
 * @}
 * @}
 */
