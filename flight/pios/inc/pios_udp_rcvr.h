/**
 ******************************************************************************
 *
 * @file       pios_udp_rcvr.h
 * @brief      PPM-format stick input over UDP (NinjaPilot realposix).
 *
 * A UDP receiver presenting the standard pios_rcvr driver interface, so
 * ManualControlSettings can select it like any radio. The wire format is
 * "PPM over UDP": one datagram per frame, channel values in microseconds
 * (1000..2000), exactly what a hardware PPM decoder would deliver:
 *
 *     offset  size  field
 *     0       4     magic "PPM1"
 *     4       1     sequence number (wraps; used for loss accounting)
 *     5       1     channel count N (1..PIOS_UDPRCVR_MAX_CHANNELS)
 *     6       2*N   channel values, uint16 little-endian, microseconds
 *
 * Link-health contract (drives the INPUT tile via Receiver/receiver.c):
 *     fresh frames, low loss   -> reads return values      (tile GREEN)
 *     heavy loss (<70%% seen)  -> quality degrades         (tile ORANGE)
 *     silence > 500 ms         -> reads return TIMEOUT     (failsafe;
 *                                 tile RED once the stream had been up)
 *
 * @see        The GNU Public License (GPL) Version 3
 *
 *****************************************************************************/

#ifndef PIOS_UDP_RCVR_H
#define PIOS_UDP_RCVR_H

#define PIOS_UDPRCVR_MAX_CHANNELS 12
#define PIOS_UDPRCVR_DEFAULT_PORT 9003

extern const struct pios_rcvr_driver pios_udp_rcvr_driver;

extern int32_t PIOS_UDPRCVR_Init(uint32_t *udprcvr_id, uint16_t port);

/* Stream quality over the last accounting window, 0..100 (sequence-number
 * based: received / (received + lost)). Returns 0 when no frame has
 * arrived for over a second. */
extern uint8_t PIOS_UDPRCVR_Quality(void);

/* True once at least one valid frame has EVER arrived since boot - lets
 * the alarm logic distinguish "never configured" (Warning) from "was
 * flying on this link and lost it" (Error). */
extern bool PIOS_UDPRCVR_EverActive(void);

#endif /* PIOS_UDP_RCVR_H */
