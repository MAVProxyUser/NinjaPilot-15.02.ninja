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
#include "dronecanesccommand.h"
#include "dronecanparam.h"
#include "flightstatus.h"
#include "dronecanlog.h"
#include "actuatorcommand.h"
#include "alarms.h"
#ifdef PIOS_INCLUDE_IOMCU
#include <pios_iomcu.h>
#include "iomcustatus.h"
extern uint32_t pios_iomcu_id;
#endif

#if defined(PIOS_INCLUDE_CAN)

#define STACK_SIZE_BYTES        2048
#define TASK_PRIORITY           (tskIDLE_PRIORITY + 2)

/* DroneCAN v0 wire constants (verified against pydronecan / the posix hub) */
#define DC_NODE_ID              10u      /* the flight controller on the bus */
#define DC_DTID_ALLOCATION      1u       /* uavcan.protocol.dynamic_node_id.Allocation */
#define DC_ALLOCATION_BASE_CRC  0xF258u  /* crc16-ccitt of its DSDL signature */
#define DC_DTID_NODESTATUS      341u     /* uavcan.protocol.NodeStatus */
#define DC_DTID_ESC_STATUS      1034u    /* uavcan.equipment.esc.Status */
#define DC_DTID_ESC_RAWCOMMAND  1030u    /* uavcan.equipment.esc.RawCommand, int14[<=20] */
#define DC_RAWCOMMAND_BASE_CRC  0x1907u  /* crc16-ccitt of signature 0x217F5C87BD91B1BB (only used past 4 ESCs) */
#define DC_PRIO_HIGH            8u
#define DC_PRIO_SVC             24u
static uint32_t svc_tx, svc_rx_count, svc_last_id; /* service frame diagnostics */
#define DC_SVC_GETNODEINFO      1u       /* uavcan.protocol.GetNodeInfo: empty request */
#define DC_DTID_LOGMESSAGE      16383u   /* uavcan.protocol.debug.LogMessage */
#define DC_SVC_EXECUTEOPCODE    10u      /* uavcan.protocol.param.ExecuteOpcode: u8 opcode, i48 argument */
#define DC_SVC_GETSET           11u      /* uavcan.protocol.param.GetSet */
#define DC_GETSET_BASE_CRC      0xFB10u  /* crc16-ccitt of signature 0xA7B622F939D1A4D5 */
#define DC_DTID_ARMINGSTATUS    1100u    /* uavcan.equipment.safety.ArmingStatus: u8 status */
#define DC_ARMING_FULLY_ARMED   255u
#define DC_ARMING_DISARMED      0u
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
    uint8_t  buf[128];
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
static uint64_t dc_bits(const uint8_t *buf, uint32_t bit_ofs, uint8_t nbits);
static int64_t dc_sbits(const uint8_t *buf, uint32_t bit_ofs, uint8_t nbits);
static struct reasm log_rx[2];
static uint8_t  log_node;
static uint8_t  log_text[DRONECANLOG_LOGTEXT_NUMELEM];
static uint32_t log_count;

/* uavcan.protocol.debug.LogMessage: level u3, source u8[<=31] (u5 length), text u8[<=90] (tail) */
static void log_decode(uint8_t node, const uint8_t *p, uint8_t n)
{
    uint32_t nbits = (uint32_t)n * 8u, ofs = 3, i = 0;
    uint8_t  slen  = (uint8_t)dc_bits(p, ofs, 5);

    ofs += 5;
    memset(log_text, 0, sizeof(log_text));
    for (uint8_t k = 0; k < slen && ofs + 8u <= nbits && i < sizeof(log_text) - 3; k++) {
        log_text[i++] = (uint8_t)dc_bits(p, ofs, 8);
        ofs += 8;
    }
    if (slen) {
        log_text[i++] = ':';
        log_text[i++] = ' ';
    }
    while (ofs + 8u <= nbits && i < sizeof(log_text) - 1) {
        log_text[i++] = (uint8_t)dc_bits(p, ofs, 8);
        ofs += 8;
    }
    log_node = node;
    log_count++;
    DroneCANLogData lg;
    lg.LogCount = log_count;
    lg.LogNode  = log_node;
    memcpy(lg.LogText, log_text, sizeof(lg.LogText));
    DroneCANLogSet(&lg);
}

/* which data types are on the bus: the first 8 seen, with frame counts */
#define DTID_HIST_SIZE DRONECANSTATUS_DATATYPEID_NUMELEM
static uint16_t dtid_hist_id[DTID_HIST_SIZE];
static uint32_t dtid_hist_count[DTID_HIST_SIZE];
static void dtid_count(uint16_t dtid)
{
    for (uint32_t i = 0; i < DTID_HIST_SIZE; i++) {
        if (dtid_hist_count[i] == 0 || dtid_hist_id[i] == dtid) {
            dtid_hist_id[i] = dtid;
            dtid_hist_count[i]++;
            return;
        }
    }
}

static void dronecanTask(void *parameters);
static void esccmd_updated_cb(UAVObjEvent *ev);
static void param_cb(UAVObjEvent *ev);
static void svc_handle_response(uint8_t node, uint8_t svc, const uint8_t *data, uint8_t dlc);

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
    DroneCANESCCommandInitialize();
    DroneCANESCCommandConnectCallback(esccmd_updated_cb);
    DroneCANParamInitialize();
    DroneCANLogInitialize();
#ifdef PIOS_INCLUDE_IOMCU
    IOMCUStatusInitialize();
#endif
    DroneCANParamConnectCallback(param_cb);
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

/* The mirror of dc_bits: little-endian bytes, most significant bit first
 * inside each byte, the partial last byte holding the value's top bits. */
static void dc_put_bits(uint8_t *buf, uint32_t bit_ofs, uint8_t nbits, uint64_t value)
{
    uint8_t nbytes = (uint8_t)((nbits + 7u) / 8u);

    for (uint8_t i = 0; i < nbytes; i++) {
        uint8_t want = (uint8_t)((nbits - i * 8u) >= 8u ? 8u : (nbits - i * 8u));
        uint8_t v    = (uint8_t)(value >> (8u * i));
        for (uint8_t b = 0; b < want; b++) {
            uint32_t dbit = bit_ofs + i * 8u + b;
            uint8_t  mask = (uint8_t)(1u << (7u - (dbit % 8u)));
            if ((v >> (want - 1u - b)) & 1u) {
                buf[dbit / 8u] |= mask;
            } else {
                buf[dbit / 8u] &= (uint8_t)~mask;
            }
        }
    }
}

static int64_t dc_sbits(const uint8_t *buf, uint32_t bit_ofs, uint8_t nbits)
{
    uint64_t u = dc_bits(buf, bit_ofs, nbits);

    if (nbits < 64u && (u & (1ull << (nbits - 1u)))) {
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
static void dc_transfer(uint32_t id, uint16_t base_crc, uint8_t *tid_counter,
                        const uint8_t *payload, uint8_t len)
{
    uint8_t stream[2 + 64];
    uint8_t slen = 0;
    uint8_t tid  = (uint8_t)((*tid_counter)++ & 0x1F);

    if (len > 64) {
        return;
    }

    if (len > 7) {
        uint16_t crc = crc16_ccitt(payload, len, base_crc);
        stream[slen++] = (uint8_t)(crc & 0xFF);
        stream[slen++] = (uint8_t)(crc >> 8);
    }
    memcpy(stream + slen, payload, len);
    slen = (uint8_t)(slen + len);
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

static void dc_broadcast(uint8_t prio, uint16_t dtid, uint16_t base_crc, uint8_t *tid_counter,
                         const uint8_t *payload, uint8_t len)
{
    dc_transfer(((uint32_t)prio << 24) | ((uint32_t)dtid << 8) | DC_NODE_ID, base_crc, tid_counter, payload, len);
}

/* Service request to one node: bit 7 set, destination in 8..14, bit 15 = request. */
static void dc_service_request(uint8_t svc, uint8_t dest, uint16_t base_crc, uint8_t *tid_counter,
                               const uint8_t *payload, uint8_t len)
{
    dc_transfer(((uint32_t)DC_PRIO_SVC << 24) | ((uint32_t)svc << 16) | (1u << 15) | ((uint32_t)dest << 8) | 0x80u | DC_NODE_ID,
                base_crc, tid_counter, payload, len);
    svc_tx++;
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
        dc_broadcast(DC_PRIO_LOW, DC_DTID_ALLOCATION, DC_ALLOCATION_BASE_CRC, &dna_tid, pl, n);
    } else if (uid_len == 6 && dna_query_len == 6) {
        memcpy(dna_query + 6, uid, 6);
        dna_query_len = 12;
        dna_query_ts  = now;
        n = dna_pack(0, 0, dna_query, 12, pl);
        dc_broadcast(DC_PRIO_LOW, DC_DTID_ALLOCATION, DC_ALLOCATION_BASE_CRC, &dna_tid, pl, n);
    } else if (uid_len == 4 && dna_query_len == 12) {
        memcpy(dna_query + 12, uid, 4);
        uint8_t alloc = dna_assign(dna_query, req_node);
        if (alloc) {
            n = dna_pack(alloc, 0, dna_query, 16, pl);
            dc_broadcast(DC_PRIO_LOW, DC_DTID_ALLOCATION, DC_ALLOCATION_BASE_CRC, &dna_tid, pl, n);
            dna_allocations++;
        }
        dna_query_len = 0;
    }
}

/* ---- receive side ---- */
static struct node_entry *node_lookup(uint8_t node_id, bool create)
{
    struct node_entry *free_slot = NULL, *stalest = NULL;

    for (uint32_t i = 0; i < NODE_TABLE_SIZE; i++) {
        if (nodes[i].node_id == node_id) {
            return &nodes[i];
        }
        if (nodes[i].node_id == 0) {
            if (!free_slot) {
                free_slot = &nodes[i];
            }
        } else if (!stalest || (int32_t)(nodes[i].last_seen - stalest->last_seen) < 0) {
            stalest = &nodes[i];
        }
    }
    if (!create) {
        return NULL;
    }
    struct node_entry *e = free_slot ? free_slot : stalest;
    if (!e) {
        return NULL;
    }
    memset(e, 0, sizeof(*e));
    e->node_id = node_id;
    return e;
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
/* One row per ESC node, in the order first heard; published with the status. */
struct esc_entry {
    uint8_t  node_id, idx, power_pct;
    float    volt, cur, temp_c;
    int32_t  rpm;
    uint32_t err, updates;
};
static struct esc_entry esc_tab[ESC_TABLE_SIZE];

static void esc_status_decode(uint8_t node_id, const uint8_t *p, uint8_t n)
{
    if (n < 14) {
        return;
    }
    struct esc_entry *e = NULL;
    for (uint32_t i = 0; i < ESC_TABLE_SIZE; i++) {
        if (esc_tab[i].node_id == node_id) {
            e = &esc_tab[i];
            break;
        }
        if (esc_tab[i].node_id == 0 && !e) {
            e = &esc_tab[i];
        }
    }
    if (!e) {
        return;
    }
    e->node_id   = node_id;
    e->err       = (uint32_t)dc_bits(p, 0, 32);
    e->volt      = f16_to_f32((uint16_t)dc_bits(p, 32, 16));
    e->cur       = f16_to_f32((uint16_t)dc_bits(p, 48, 16));
    float tk     = f16_to_f32((uint16_t)dc_bits(p, 64, 16));
    e->temp_c    = tk > 0.0f ? tk - 273.15f : 0.0f;
    e->rpm       = (int32_t)dc_sbits(p, 80, 18);
    e->power_pct = (uint8_t)dc_bits(p, 98, 7);
    e->idx       = (uint8_t)dc_bits(p, 105, 5);
    e->updates++;
}

static void esc_publish(void)
{
    DroneCANESCStatusData esc;

    memset(&esc, 0, sizeof(esc));
    for (uint32_t i = 0; i < ESC_TABLE_SIZE; i++) {
        esc.NodeId[i]      = esc_tab[i].node_id;
        esc.Index[i]       = esc_tab[i].idx;
        esc.PowerPct[i]    = esc_tab[i].power_pct;
        esc.Voltage[i]     = esc_tab[i].volt;
        esc.Current[i]     = esc_tab[i].cur;
        esc.Temperature[i] = esc_tab[i].temp_c;
        esc.RPM[i]         = esc_tab[i].rpm;
        esc.ErrorCount[i]  = esc_tab[i].err;
        esc.Updates[i]     = (uint16_t)esc_tab[i].updates;
    }
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
        svc_rx_count++;
        svc_last_id = id;
        /* service frame: only responses addressed to us */
        if (((id >> 8) & 0x7Fu) == DC_NODE_ID && !((id >> 15) & 1u)) {
            svc_handle_response(node, (uint8_t)(id >> 16), f->data, f->dlc);
        }
        return;
    }
    uint16_t dtid = (id >> 8) & 0xFFFF;
    uint8_t  tail = f->data[f->dlc - 1];

    dtid_count(dtid);

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
    if (dtid == DC_DTID_LOGMESSAGE) {
        const uint8_t *pl = NULL;
        uint8_t n = reasm_feed(log_rx, NELEMENTS(log_rx), node, f->data, f->dlc, &pl);
        if (n) {
            log_decode(node, pl, n);
        }
    }
}

/* ---- ESC RawCommand from the actuator module (the flight path) ---- */
static int16_t  esc_out[DRONECANESCCOMMAND_COMMAND_NUMELEM];
static uint8_t  esc_out_count;
static uint32_t esc_out_last;                  /* tick of the last flush */
static uint8_t  rawcmd_tid;
static uint32_t esccmd_sent;

void DroneCANESCSet(uint8_t index, int16_t raw)
{
    if (index >= NELEMENTS(esc_out)) {
        return;
    }
    esc_out[index] = raw;
    if ((uint8_t)(index + 1) > esc_out_count) {
        esc_out_count = (uint8_t)(index + 1);
    }
}

/* Called from the actuator task after every update, so the stream runs at
 * the actuator rate and keeps running (zeros) while disarmed: the AM32
 * application drops back to its bootloader when the stream stops. */
void DroneCANESCFlush(void)
{
    uint8_t payload[14];

    if (!can_id || !esc_out_count) {
        return;
    }
    memset(payload, 0, sizeof(payload));
    for (uint8_t i = 0; i < esc_out_count; i++) {
        int16_t v = esc_out[i];
        if (v > 8191) {
            v = 8191;
        }
        if (v < -8192) {
            v = -8192;
        }
        dc_put_bits(payload, i * 14u, 14, (uint64_t)((uint16_t)v & 0x3FFFu));
    }
    dc_broadcast(DC_PRIO_HIGH, DC_DTID_ESC_RAWCOMMAND, DC_RAWCOMMAND_BASE_CRC, &rawcmd_tid,
                 payload, (uint8_t)((esc_out_count * 14u + 7u) / 8u));
    esc_out_last = xTaskGetTickCount();
    esccmd_sent++;
    esc_out_count = 0;
    memset(esc_out, 0, sizeof(esc_out));
}

static bool esc_actuator_active(uint32_t now)
{
    return esc_out_last && (now - esc_out_last) < (1000 / portTICK_RATE_MS);
}

/* ---- ESC RawCommand from DroneCANESCCommand (bench tool, not the flight path) ---- */
static uint32_t esccmd_updated;               /* tick of the last write from the ground */
static uint32_t esccmd_period = 20 / portTICK_RATE_MS;
static uint8_t  arming_tid;
static uint32_t esccmd_last_enabled;          /* tick the command path was last enabled */
static bool     esccmd_arm;

static void esccmd_updated_cb(__attribute__((unused)) UAVObjEvent *ev)
{
    esccmd_updated = xTaskGetTickCount();
}

/* int14[<=20] with the tail-array optimisation: no length, the count follows
 * from the payload size.  4 ESCs = 56 bits = one frame. */
static void esccmd_tx(uint32_t now)
{
    DroneCANESCCommandData cmd;
    uint8_t payload[14];

    DroneCANESCCommandGet(&cmd);
    uint8_t rate = cmd.Rate ? cmd.Rate : 50;
    if (rate > 200) {
        rate = 200;
    }
    esccmd_period = (1000u / rate) / portTICK_RATE_MS;
    if (esccmd_period == 0) {
        esccmd_period = 1;
    }
    if (cmd.Enabled != DRONECANESCCOMMAND_ENABLED_TRUE || esc_actuator_active(now)) {
        return; /* off, or the actuator owns the bus */
    }
    esccmd_last_enabled = now;
    esccmd_arm = cmd.Arm == DRONECANESCCOMMAND_ARM_TRUE;
    uint8_t count = cmd.Count;
    if (count < 1) {
        count = 1;
    }
    if (count > DRONECANESCCOMMAND_COMMAND_NUMELEM) {
        count = DRONECANESCCOMMAND_COMMAND_NUMELEM;
    }
    bool stale = (now - esccmd_updated) > (2000 / portTICK_RATE_MS);
    memset(payload, 0, sizeof(payload));
    for (uint8_t i = 0; i < count; i++) {
        int16_t v = stale ? 0 : cmd.Command[i];
        if (v > 8191) {
            v = 8191;
        }
        if (v < -8192) {
            v = -8192;
        }
        dc_put_bits(payload, i * 14u, 14, (uint64_t)((uint16_t)v & 0x3FFFu));
    }
    dc_broadcast(DC_PRIO_HIGH, DC_DTID_ESC_RAWCOMMAND, DC_RAWCOMMAND_BASE_CRC, &rawcmd_tid,
                 payload, (uint8_t)((count * 14u + 7u) / 8u));
    esccmd_sent++;
}

/* ArmingStatus at 10 Hz while the command path is enabled (what Arm says),
 * then DISARMED for another second so the ESCs let go. */
static void arming_tx(uint32_t now)
{
    uint8_t status;

    if (esc_actuator_active(now)) {
        /* Armed, or the operator has taken the outputs over (ActuatorCommand
         * read-only: the GCS Output tab and the wizard's motor test) - the
         * same carve-out the actuator makes for its own outputs, without
         * which those tests spin nothing because the ESCs refuse to run
         * unarmed. */
        FlightStatusArmedOptions armed;
        FlightStatusArmedGet(&armed);
        bool go = (armed == FLIGHTSTATUS_ARMED_ARMED) || ActuatorCommandReadOnly();
        status = go ? DC_ARMING_FULLY_ARMED : DC_ARMING_DISARMED;
    } else if (esccmd_last_enabled && (now - esccmd_last_enabled) < (100 / portTICK_RATE_MS)) {
        status = esccmd_arm ? DC_ARMING_FULLY_ARMED : DC_ARMING_DISARMED;
    } else if (esccmd_last_enabled && (now - esccmd_last_enabled) < (1000 / portTICK_RATE_MS)) {
        status = DC_ARMING_DISARMED;
    } else {
        return;
    }
    dc_broadcast(DC_PRIO_HIGH, DC_DTID_ARMINGSTATUS, 0, &arming_tid, &status, 1);
}

/* ---- DroneCAN parameter client (DroneCANParam <-> GetSet / ExecuteOpcode) ---- */
static volatile bool param_req_pending;    /* the ground wrote DroneCANParam */
static struct {
    bool     active;
    uint8_t  node, svc;
    uint32_t sent;
} svc_wait;
static uint8_t svc_tid_getset, svc_tid_opcode, svc_tid_info;
static struct reasm svc_rx[2];

static void param_cb(UAVObjEvent *ev)
{
    if (ev->event == EV_UNPACKED) {
        param_req_pending = true;
    }
}

/* uavcan.protocol.param.Value / NumericValue.  Measured against the AM32
 * ESCs: in a GetSet RESPONSE every union tag occupies a whole byte, while a
 * REQUEST is only accepted with the spec's 3-bit Value tag (a byte-wide tag
 * there gets "not found" or silence). */
struct dc_value {
    uint8_t tag;
    int64_t i;
    float   r;
};
static uint32_t dc_value_decode(const uint8_t *p, uint32_t ofs, uint8_t tagbits, struct dc_value *v)
{
    v->tag = (uint8_t)dc_bits(p, ofs, tagbits);
    v->i   = 0;
    v->r   = 0.0f;
    ofs   += tagbits;
    switch (v->tag) {
    case 1: /* int64 */
        v->i = dc_sbits(p, ofs, 64);
        ofs += 64;
        break;
    case 2: /* float32 */
    {
        uint32_t u = (uint32_t)dc_bits(p, ofs, 32);
        memcpy(&v->r, &u, 4);
        ofs += 32;
        break;
    }
    case 3: /* bool (Value only) */
        v->i = (int64_t)dc_bits(p, ofs, 8);
        ofs += 8;
        break;
    case 4: /* string (Value only): u8 length, bytes */
        ofs += 8 + 8u * (uint32_t)dc_bits(p, ofs, 8);
        break;
    default:
        break;
    }
    return ofs;
}

static void param_finish(uint8_t result, const uint8_t *p, uint8_t n)
{
    DroneCANParamData pr;

    DroneCANParamGet(&pr);
    svc_wait.active = false;
    pr.Result = result;
    pr.Op     = DRONECANPARAM_OP_NONE;
    memset(pr.ResponseName, 0, sizeof(pr.ResponseName));
    pr.ResponseType = DRONECANPARAM_RESPONSETYPE_EMPTY;
    pr.ResponseInt  = 0;
    pr.ResponseReal = 0.0f;
    pr.DefaultInt   = 0;
    pr.DefaultReal  = 0.0f;
    pr.MinInt       = 0;
    pr.MaxInt       = 0;
    pr.RawLen       = p ? (n > sizeof(pr.Raw) ? sizeof(pr.Raw) : n) : 0;
    memset(pr.Raw, 0, sizeof(pr.Raw));
    if (p) {
        memcpy(pr.Raw, p, pr.RawLen);
    }
    if (p && svc_wait.svc == DC_SVC_GETSET) {
        struct dc_value v;
        uint32_t ofs = dc_value_decode(p, 0, 8, &v);
        pr.ResponseType = v.tag <= 4 ? v.tag : 0;
        pr.ResponseInt  = (int32_t)v.i;
        pr.ResponseReal = v.r;
        ofs = dc_value_decode(p, ofs, 8, &v);
        pr.DefaultInt  = (int32_t)v.i;
        pr.DefaultReal = v.r;
        ofs = dc_value_decode(p, ofs, 8, &v);
        pr.MaxInt = v.tag == 2 ? (int32_t)v.r : (int32_t)v.i;
        ofs = dc_value_decode(p, ofs, 8, &v);
        pr.MinInt = v.tag == 2 ? (int32_t)v.r : (int32_t)v.i;
        uint32_t nbits = (uint32_t)n * 8u, i = 0;
        while (ofs + 8u <= nbits && i < sizeof(pr.ResponseName) - 1) {
            pr.ResponseName[i++] = (uint8_t)dc_bits(p, ofs, 8);
            ofs += 8;
        }
    } else if (p && svc_wait.svc == DC_SVC_EXECUTEOPCODE) {
        pr.ResponseInt = (int32_t)dc_bits(p, 48, 1); /* int48 argument, then ok */
    } else if (p && svc_wait.svc == DC_SVC_GETNODEINFO && n > 41) {
        /* NodeStatus(7) SoftwareVersion(major, minor, flags, vcs u32, crc u64)
         * HardwareVersion(major, minor, uid[16], coa[<=255] with u8 length) name (tail) */
        pr.ResponseInt = ((int32_t)p[7] << 8) | p[8];
        pr.DefaultInt  = (int32_t)((uint32_t)p[10] | ((uint32_t)p[11] << 8) | ((uint32_t)p[12] << 16) | ((uint32_t)p[13] << 24));
        uint32_t ofs = 22 + 18 + 1 + p[40];
        for (uint32_t i = 0; ofs < n && i < sizeof(pr.ResponseName) - 1; i++, ofs++) {
            pr.ResponseName[i] = p[ofs];
        }
    }
    DroneCANParamSet(&pr);
}

static void param_start(uint32_t now)
{
    DroneCANParamData pr;
    uint8_t payload[2 + 8 + 32 + 1];

    DroneCANParamGet(&pr);
    if (pr.Op == DRONECANPARAM_OP_NONE || pr.NodeId == 0 || pr.NodeId > 127) {
        return;
    }
    if (svc_wait.active) {
        param_finish(DRONECANPARAM_RESULT_ERROR, NULL, 0);
        DroneCANParamGet(&pr);
    }
    memset(payload, 0, sizeof(payload));
    svc_wait.node = pr.NodeId;
    if (pr.Op == DRONECANPARAM_OP_RAW) {
        /* Raw[0..RawLen) goes out verbatim as the GetSet request (encoding experiments) */
        svc_wait.svc = DC_SVC_GETSET;
        dc_service_request(DC_SVC_GETSET, pr.NodeId, DC_GETSET_BASE_CRC, &svc_tid_getset, pr.Raw,
                           (uint8_t)(pr.RawLen > sizeof(pr.Raw) ? sizeof(pr.Raw) : pr.RawLen));
    } else if (pr.Op == DRONECANPARAM_OP_INFO) {
        svc_wait.svc = DC_SVC_GETNODEINFO;
        dc_service_request(DC_SVC_GETNODEINFO, pr.NodeId, 0, &svc_tid_info, payload, 0);
    } else if (pr.Op == DRONECANPARAM_OP_SAVE || pr.Op == DRONECANPARAM_OP_ERASE) {
        payload[0] = (pr.Op == DRONECANPARAM_OP_SAVE) ? 0 : 1;
        svc_wait.svc = DC_SVC_EXECUTEOPCODE;
        dc_service_request(DC_SVC_EXECUTEOPCODE, pr.NodeId, 0, &svc_tid_opcode, payload, 7);
    } else {
        uint32_t ofs = 0;
        uint8_t  tag = 0;
        dc_put_bits(payload, ofs, 13, pr.Index);
        ofs += 13;
        if (pr.Op == DRONECANPARAM_OP_SET) {
            tag = pr.ValueType <= 3 ? pr.ValueType : 0;
        }
        dc_put_bits(payload, ofs, 3, tag); /* requests: 3-bit tag; responses: a whole byte (measured) */
        ofs += 3;
        if (tag == 1) {
            dc_put_bits(payload, ofs, 64, (uint64_t)(int64_t)pr.IntValue);
            ofs += 64;
        } else if (tag == 2) {
            uint32_t u;
            memcpy(&u, &pr.RealValue, 4);
            dc_put_bits(payload, ofs, 32, u);
            ofs += 32;
        } else if (tag == 3) {
            dc_put_bits(payload, ofs, 8, pr.IntValue ? 1u : 0u);
            ofs += 8;
        }
        for (uint32_t i = 0; i < sizeof(pr.Name) && pr.Name[i]; i++) {
            dc_put_bits(payload, ofs, 8, pr.Name[i]);
            ofs += 8;
        }
        svc_wait.svc = DC_SVC_GETSET;
        dc_service_request(DC_SVC_GETSET, pr.NodeId, DC_GETSET_BASE_CRC, &svc_tid_getset, payload, (uint8_t)((ofs + 7u) / 8u));
    }
    svc_wait.active = true;
    svc_wait.sent   = now;
    pr.Result = DRONECANPARAM_RESULT_PENDING;
    DroneCANParamSet(&pr);
}

static void svc_handle_response(uint8_t node, uint8_t svc, const uint8_t *data, uint8_t dlc)
{
    static uint8_t copy[128];
    const uint8_t *pl = NULL;
    uint8_t n = reasm_feed(svc_rx, NELEMENTS(svc_rx), node, data, dlc, &pl);

    if (!n || !svc_wait.active || node != svc_wait.node || svc != svc_wait.svc) {
        return;
    }
    memset(copy, 0, sizeof(copy));
    memcpy(copy, pl, n > sizeof(copy) ? sizeof(copy) : n);
    param_finish(DRONECANPARAM_RESULT_OK, copy, n);
}

#ifdef PIOS_INCLUDE_IOMCU
/* Board housekeeping that rides on this task: the IO co-processor's view,
 * once a second, so RC IN can be debugged from the ground. */
static void iomcu_publish(void)
{
    static uint32_t last;
    uint32_t now = xTaskGetTickCount();

    if (!pios_iomcu_id || (now - last) < (1000 / portTICK_RATE_MS)) {
        return;
    }
    last = now;
    struct pios_iomcu_status st;
    PIOS_IOMCU_GetStatus(pios_iomcu_id, &st);
    IOMCUStatusData o;
    memset(&o, 0, sizeof(o));
    o.State           = st.state <= PIOS_IOMCU_STATE_LOST ? st.state : IOMCUSTATUS_STATE_OFFLINE;
    o.ProtocolVersion = st.protocol_version;
    o.ProtocolVersion2 = st.protocol_version2;
    o.RcMaskAck       = st.rc_mask_ack;
    o.StatusFlags     = st.status_flags;
    o.RcCount         = st.rc_count;
    o.RcOk            = st.rc_ok;
    o.RcFailsafe      = st.rc_failsafe;
    o.RcProtocol      = st.rc_protocol;
    o.ServoRail       = st.vservo_mv;
    o.IoErrors        = st.io_errors;
    o.TxOk            = st.ok;
    o.TxFail          = st.fail;
    for (uint8_t i = 0; i < IOMCUSTATUS_RCCHANNEL_NUMELEM; i++) {
        int32_t v = PIOS_IOMCU_RcGet(pios_iomcu_id, i);
        o.RcChannel[i] = (v < 0 || v > 0xFFFF) ? 0 : (uint16_t)v;
    }
    IOMCUStatusSet(&o);
}
#endif /* PIOS_INCLUDE_IOMCU */

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
    uint8_t live = 0;
    for (uint32_t i = 0; i < NODE_TABLE_SIZE; i++) {
        if (nodes[i].node_id && (now - nodes[i].last_seen) < (3000u / portTICK_RATE_MS)) {
            live++;
        }
    }
    /* The health panel's "CAN" slot is the I2C alarm in this tree (the
     * realposix sensor hub reports its CAN link there too): red when the
     * controller is bus-off, amber when the error counters climb or nobody
     * else is on the bus, green with live nodes. */
    if (cs.bus_off) {
        AlarmsSet(SYSTEMALARMS_ALARM_I2C, SYSTEMALARMS_ALARM_ERROR);
    } else if (cs.tx_errors >= 96 || cs.rx_errors >= 96 || live == 0) {
        AlarmsSet(SYSTEMALARMS_ALARM_I2C, SYSTEMALARMS_ALARM_WARNING);
    } else {
        AlarmsClear(SYSTEMALARMS_ALARM_I2C);
    }
    st.NodeCount = count;
    st.CommandsSent = esccmd_sent;
    st.ServiceTx     = svc_tx;
    st.ServiceRx     = svc_rx_count;
    st.LastServiceId = svc_last_id;
    for (uint32_t i = 0; i < DTID_HIST_SIZE; i++) {
        st.DataTypeId[i]    = dtid_hist_id[i];
        st.DataTypeCount[i] = dtid_hist_count[i];
    }
    DroneCANStatusSet(&st);
}

static void dronecanTask(__attribute__((unused)) void *parameters)
{
    uint32_t last_ns = 0, last_pub = 0, last_cmd = 0, last_arm = 0;
    struct pios_can_frame f;

    while (1) {
        /* Drain what is queued, but a busy bus (four ESCs at 30 Hz status
         * each) must never keep the periodic work from running: wait for the
         * first frame only, take at most a batch, then do the housekeeping. */
        uint32_t drained = 0;
        while (drained < 32 && PIOS_CAN_Receive(can_id, &f, drained ? 0 : 5)) {
            handle_frame(&f);
            drained++;
        }
        uint32_t now = xTaskGetTickCount();
        if ((now - last_ns) >= (1000 / portTICK_RATE_MS)) {
            last_ns = now;
            nodestatus_tx();
        }
        if ((now - last_pub) >= (500 / portTICK_RATE_MS)) {
            last_pub = now;
            publish_status();
            esc_publish();
        }
#ifdef PIOS_INCLUDE_IOMCU
        iomcu_publish();
#endif
        if ((now - last_cmd) >= esccmd_period) {
            last_cmd = now;
            esccmd_tx(now);
        }
        if ((now - last_arm) >= (100 / portTICK_RATE_MS)) {
            last_arm = now;
            arming_tx(now);
        }
        if (param_req_pending) {
            param_req_pending = false;
            param_start(now);
        }
        if (svc_wait.active && (now - svc_wait.sent) > (1000 / portTICK_RATE_MS)) {
            param_finish(DRONECANPARAM_RESULT_TIMEOUT, NULL, 0);
        }
    }
}

#endif /* PIOS_INCLUDE_CAN */

/**
 * @}
 * @}
 */
