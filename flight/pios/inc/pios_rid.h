/**
 ******************************************************************************
 * @file       pios_rid.h
 * @brief      Board hook for ASTM F3411 Broadcast Remote ID.
 *
 * The RemoteID module encodes a Message Pack once a second and calls
 * PIOS_RID_Broadcast(). The board decides how it leaves the aircraft:
 *   - esp32wroom: a vendor-specific element (OUI FA:0B:BC, type 0x0D) in the
 *     soft-AP's own beacon and probe-response frames (pios_rid_wifi.c)
 *   - posix twins: the identical element bytes over UDP to 127.0.0.1:9020 so
 *     tools/remoteid_listen.py can decode exactly what a receiver would see
 * @see        The GNU Public License (GPL) Version 3
 *****************************************************************************/
#ifndef PIOS_RID_H
#define PIOS_RID_H

#include <stdint.h>

/**
 * Transmit one encoded Message Pack.
 * @param pack     encoded ODID_MessagePack (3-byte header + N * 25 bytes)
 * @param len      its length in bytes; 0 (or pack == NULL) means stop broadcasting
 * @param counter  message counter for the vendor element (increments per pack)
 * @return 0 on success, nonzero when no transmitter is available
 */
int32_t PIOS_RID_Broadcast(const uint8_t *pack, uint16_t len, uint8_t counter);

#endif /* PIOS_RID_H */
