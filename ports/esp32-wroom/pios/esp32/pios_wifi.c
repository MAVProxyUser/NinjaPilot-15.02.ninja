/**
 ******************************************************************************
 * @file       pios_wifi.c
 * @author     NinjaPilot, 2026
 * @brief      Bare-minimum WiFi telemetry: UAVTalk over one TCP socket.
 *
 * BENCH FEATURE. WiFi runs only when credentials exist in NVS (default
 * partition, namespace "wifi", keys "ssid"/"pass" -- written offline by
 * tools/wifi_setup.py, erased the same way). No credentials: this file
 * costs one NVS lookup at boot and nothing else. That is also the flight
 * switch: erase the credentials before flying anything that matters --
 * the WiFi stack runs its own high-priority tasks and has NOT been
 * characterized against the control loop the way the rest of this port
 * has.
 *
 * Shape: STA join -> TCP server on :9000 -> registered as a PIOS_COM
 * device; board init points telemetry at it instead of UART0 when the
 * join succeeds. A UDP broadcast beacon on :9999 ("NINJAPILOT <ip>")
 * every 2s lets tools find the board without reading its console --
 * which lives on UART1 pins nobody has wired.
 *
 * One client at a time; a new connection replaces the old. TX that the
 * socket cannot take immediately is dropped, not blocked on -- telemetry
 * tolerates loss, and a COM driver that can block the telemetry task on
 * a dead WiFi link is how flight code acquires mystery stalls.
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

#if defined(PIOS_INCLUDE_WIFI) && defined(PIOS_INCLUDE_COM)

#include <string.h>
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "lwip/sockets.h"

#define WIFI_TCP_PORT      9000
#define WIFI_BEACON_PORT   9999
#define WIFI_JOIN_WAIT_MS  8000
#define WIFI_TASK_STACK    1024   /* words -- see the unit note in pios_esp32.h */
#define WIFI_TASK_PRIO     (tskIDLE_PRIORITY + 2)
#define WIFI_RX_CHUNK      256

static struct {
    pios_com_callback rx_in_cb;
    uint32_t rx_in_context;
    pios_com_callback tx_out_cb;
    uint32_t tx_out_context;
    volatile int client;        /* -1 = nobody connected */
    int udp;                    /* datagram telemetry socket, same port */
    struct sockaddr_in udp_peer;
    volatile bool udp_active;
    volatile TickType_t udp_last_rx;
    esp_ip4_addr_t ip;
    EventGroupHandle_t events;
    bool up;
} wifi;

#define EV_GOT_IP BIT0

static void wifi_event(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    (void)arg;
    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED) {
        esp_wifi_connect();
    } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        wifi.ip = ((ip_event_got_ip_t *)data)->ip_info.ip;
        xEventGroupSetBits(wifi.events, EV_GOT_IP);
    }
}

static void wifi_server_task(__attribute__((unused)) void *arg)
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    struct sockaddr_in addr = {
        .sin_family      = AF_INET,
        .sin_port        = htons(WIFI_TCP_PORT),
        .sin_addr.s_addr = htonl(INADDR_ANY),
    };
    int one = 1;

    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    bind(listener, (struct sockaddr *)&addr, sizeof(addr));
    listen(listener, 1);

    /* Same port, datagram flavor. UDP is the lighter transport on this
     * chip in a way that goes beyond header overhead: a connected TCP
     * client is what arms lwIP's 250ms tcp fast timer, whose periodic
     * work on core 0 is this platform's residual scheduler-stall source.
     * A UDP client never starts that timer. First datagram from a peer
     * claims the telemetry stream; silence for 10s releases it. */
    wifi.udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    bind(wifi.udp, (struct sockaddr *)&addr, sizeof(addr));

    int beacon = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    setsockopt(beacon, SOL_SOCKET, SO_BROADCAST, &one, sizeof(one));
    struct sockaddr_in bcast = {
        .sin_family      = AF_INET,
        .sin_port        = htons(WIFI_BEACON_PORT),
        .sin_addr.s_addr = htonl(INADDR_BROADCAST),
    };
    char note[48];
    int notelen = snprintf(note, sizeof(note), "NINJAPILOT " IPSTR " %d",
                           IP2STR(&wifi.ip), WIFI_TCP_PORT);
    TickType_t last_beacon = 0;

    for (;;) {
        /* Advertise ALWAYS, connected or not, so tools can find the IP
         * without a console.
         *
         * This used to stop the moment a peer appeared, which seemed tidy and
         * was not: the GCS ages a discovered board out of its device list
         * after 30 s of silence, so it expired the entry for the board it was
         * actively talking to, decided the device had gone away, and
         * disconnected itself mid-session -- then fell back to the manually
         * configured entry and never came back. The ground side now refuses to
         * expire a device it holds an open socket to, but the root of it was
         * here: a board that is flying is exactly the board a ground station
         * most needs to be able to find. It also means a second tool can
         * discover it, and that a reconnect after a dropped link has something
         * to aim at.
         *
         * The cost is one 30-byte broadcast every two seconds.
         *
         * udp_active is still tracked -- the UDP peer latch and its 10 s
         * idle timeout are unchanged -- it simply no longer gates the advert.
         */
        if (wifi.udp_active &&
            (xTaskGetTickCount() - wifi.udp_last_rx) > pdMS_TO_TICKS(10000)) {
            wifi.udp_active = false;
        }
        if ((xTaskGetTickCount() - last_beacon) > pdMS_TO_TICKS(2000)) {
            last_beacon = xTaskGetTickCount();
            sendto(beacon, note, notelen, 0, (struct sockaddr *)&bcast,
                   sizeof(bcast));
        }

        fd_set rf;
        FD_ZERO(&rf);
        FD_SET(listener, &rf);
        int maxfd = listener;
        FD_SET(wifi.udp, &rf);
        if (wifi.udp > maxfd) {
            maxfd = wifi.udp;
        }
        if (wifi.client >= 0) {
            FD_SET(wifi.client, &rf);
            if (wifi.client > maxfd) {
                maxfd = wifi.client;
            }
        }
        struct timeval tv = { .tv_sec = 0, .tv_usec = 500 * 1000 };
        if (select(maxfd + 1, &rf, NULL, NULL, &tv) < 0) {
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
        }

        if (FD_ISSET(listener, &rf)) {
            int c = accept(listener, NULL, NULL);
            if (c >= 0) {
                if (wifi.client >= 0) {
                    close(wifi.client);   /* newest wins */
                }
                /* NO TCP_NODELAY, deliberately. Nodelay meant one TCP
                 * segment per little telemetry write -- and every segment
                 * wakes the lwIP tcpip task, which was preempting the
                 * flight stack per packet. Nagle coalescing costs tens of
                 * milliseconds of display latency and removes most of that
                 * preemption traffic. Measured cost of nodelay: part of a
                 * 5x jump in stabilization deadline warnings. */
                wifi.client = c;
            }
        }

        if (FD_ISSET(wifi.udp, &rf)) {
            uint8_t buf[WIFI_RX_CHUNK];
            struct sockaddr_in from;
            socklen_t fromlen = sizeof(from);
            int n = recvfrom(wifi.udp, buf, sizeof(buf), MSG_DONTWAIT,
                             (struct sockaddr *)&from, &fromlen);
            if (n > 0) {
                /* Stable peer: the stream belongs to whoever holds it, not
                 * to whoever spoke last. Flipping the latch on every
                 * datagram let a single diagnostic probe steal the
                 * telemetry stream from the GCS mid-flight of use -- the
                 * artificial horizon froze until the GCS's next sparse
                 * heartbeat won it back. A new sender only takes over
                 * after the holder has been silent for 3 s (bytes from
                 * interlopers are still processed; their replies go to
                 * the holder -- diagnostics that need their own stream
                 * should use TCP or wait). */
                bool same = wifi.udp_active &&
                            from.sin_addr.s_addr == wifi.udp_peer.sin_addr.s_addr &&
                            from.sin_port == wifi.udp_peer.sin_port;
                TickType_t now = xTaskGetTickCount();
                if (same) {
                    wifi.udp_last_rx = now;
                } else if (!wifi.udp_active ||
                           (now - wifi.udp_last_rx) > pdMS_TO_TICKS(3000)) {
                    wifi.udp_peer    = from;
                    wifi.udp_last_rx = now;
                    wifi.udp_active  = true;
                }
                if (wifi.rx_in_cb) {
                    uint16_t off = 0;
                    for (int spins = 0; off < (uint16_t)n && spins < 200; spins++) {
                        bool woken = false;
                        uint16_t took = (wifi.rx_in_cb)(wifi.rx_in_context,
                                                        buf + off,
                                                        (uint16_t)(n - off),
                                                        NULL, &woken);
                        off += took;
                        if (off < (uint16_t)n) {
                            vTaskDelay(pdMS_TO_TICKS(2));
                        }
                    }
                }
            }
        }

        if (wifi.client >= 0 && FD_ISSET(wifi.client, &rf)) {
            /* Backpressure matters here. rx_in_cb returns how many bytes
             * the COM fifo actually accepted; when the telemetry RX task
             * is behind, that can be less than we handed it. Dropping the
             * remainder desyncs the UAVTalk parser mid-frame -- the next
             * frame's header gets consumed as payload continuation, its
             * CRC fails, and the following frames are eaten during resync.
             * That is not hypothetical: every GCS write of ActuatorSettings
             * (a 129-byte frame) was lost exactly this way while smaller
             * writes survived, which cost a full debugging session. So:
             * push the remainder until it is all accepted, and only then
             * recv again -- TCP's own flow control backs the socket up
             * harmlessly while we wait. */
            uint8_t buf[WIFI_RX_CHUNK];
            int n = recv(wifi.client, buf, sizeof(buf), MSG_DONTWAIT);
            if (n <= 0 && !(n < 0 && errno == EWOULDBLOCK)) {
                close(wifi.client);
                wifi.client = -1;
            } else if (n > 0 && wifi.rx_in_cb) {
                /* Brief backpressure only: the fifo is sized for a whole
                 * GCS connect burst, so a full fifo here means the
                 * telemetry RX task is genuinely behind. Blocking this
                 * task for long reads as a dead link to the client (it
                 * also serves accept and the beacon), which is worse than
                 * losing data: for TCP the kernel's own flow control
                 * already buffers unread stream upstream of us, and for
                 * UDP dropping the remainder loses at most this datagram
                 * -- UAVTalk's per-object retries own recovery. */
                uint16_t off = 0;
                for (int spins = 0; off < (uint16_t)n && spins < 10; spins++) {
                    bool woken = false;
                    uint16_t took = (wifi.rx_in_cb)(wifi.rx_in_context,
                                                    buf + off,
                                                    (uint16_t)(n - off),
                                                    NULL, &woken);
                    off += took;
                    if (off < (uint16_t)n) {
                        vTaskDelay(pdMS_TO_TICKS(2));
                    }
                }
            }
        }
    }
}

/* ---------------------------------------------------------------------- *
 * pios_com_driver
 * ---------------------------------------------------------------------- */

static void PIOS_WIFI_ComInit(__attribute__((unused)) uint32_t id) {}

static void PIOS_WIFI_SetBaud(__attribute__((unused)) uint32_t id,
                              __attribute__((unused)) uint32_t baud) {}

static void PIOS_WIFI_TxStart(__attribute__((unused)) uint32_t id,
                              __attribute__((unused)) uint16_t avail)
{
    if (!wifi.tx_out_cb || (wifi.client < 0 && !wifi.udp_active)) {
        /* No client: drain and drop, so the COM buffer never fills up and
         * back-pressures telemetry because nobody is listening. */
        if (wifi.tx_out_cb) {
            uint8_t sink[64];
            bool w = false;
            while ((wifi.tx_out_cb)(wifi.tx_out_context, sink, sizeof(sink),
                                    NULL, &w) == sizeof(sink)) {
            }
        }
        return;
    }
    /* Coalesce everything the COM layer has pending into ONE send() per
     * TxStart, instead of one per 128-byte chunk. Fewer socket calls means
     * fewer tcpip-task wakeups preempting flight code. Non-blocking on
     * purpose; a stalled socket drops bytes rather than stalling the
     * telemetry task. */
    static uint8_t buf[1024];
    uint16_t fill = 0;

    for (;;) {
        bool woken = false;
        uint16_t len = (wifi.tx_out_cb)(wifi.tx_out_context, buf + fill,
                                        (uint16_t)(sizeof(buf) - fill),
                                        NULL, &woken);
        fill += len;
        if (len == 0 || fill == sizeof(buf)) {
            if (fill) {
                if (wifi.client >= 0) {
                    send(wifi.client, buf, fill, MSG_DONTWAIT);
                } else {
                    /* One datagram per drain; a torn peer update at latch
                     * time can misdirect a single datagram, which UAVTalk
                     * shrugs off. */
                    struct sockaddr_in to = wifi.udp_peer;
                    sendto(wifi.udp, buf, fill, MSG_DONTWAIT,
                           (struct sockaddr *)&to, sizeof(to));
                }
                fill = 0;
            }
            if (len == 0) {
                break;
            }
        }
    }
}

static void PIOS_WIFI_RxStart(__attribute__((unused)) uint32_t id,
                              __attribute__((unused)) uint16_t avail) {}

static void PIOS_WIFI_BindRxCb(__attribute__((unused)) uint32_t id,
                               pios_com_callback cb, uint32_t context)
{
    wifi.rx_in_context = context;
    wifi.rx_in_cb = cb;
}

static void PIOS_WIFI_BindTxCb(__attribute__((unused)) uint32_t id,
                               pios_com_callback cb, uint32_t context)
{
    wifi.tx_out_context = context;
    wifi.tx_out_cb = cb;
}

static bool PIOS_WIFI_Available(__attribute__((unused)) uint32_t id)
{
    return wifi.up;
}

const struct pios_com_driver pios_esp32_wifi_com_driver = {
    .init       = PIOS_WIFI_ComInit,
    .set_baud   = PIOS_WIFI_SetBaud,
    .tx_start   = PIOS_WIFI_TxStart,
    .rx_start   = PIOS_WIFI_RxStart,
    .bind_rx_cb = PIOS_WIFI_BindRxCb,
    .bind_tx_cb = PIOS_WIFI_BindTxCb,
    .available  = PIOS_WIFI_Available,
};

/**
 * Join WiFi using stored credentials and start the telemetry server.
 * \return 0 and the driver is live; nonzero and nothing was started
 *         (no credentials is the normal, silent case).
 */
int32_t PIOS_ESP32_WIFI_Init(void)
{
    /* Credentials live in the DEFAULT nvs partition so tools/wifi_setup.py
     * can write them offline with esptool without touching the settings
     * partition PIOS_FLASHFS owns. */
    if (nvs_flash_init() == ESP_ERR_NVS_NO_FREE_PAGES) {
        nvs_flash_erase();
        nvs_flash_init();
    }

    nvs_handle_t h;
    char ssid[33] = { 0 }, pass[65] = { 0 };
    size_t sl = sizeof(ssid), pl = sizeof(pass);

    if (nvs_open("wifi", NVS_READONLY, &h) != ESP_OK) {
        return 1;                      /* no creds: WiFi stays off */
    }
    esp_err_t e1 = nvs_get_str(h, "ssid", ssid, &sl);
    esp_err_t e2 = nvs_get_str(h, "pass", pass, &pl);
    nvs_close(h);
    if (e1 != ESP_OK || e2 != ESP_OK || !ssid[0]) {
        return 1;
    }

    printf("[WIFI] credentials found, joining '%s'...\n", ssid);
    wifi.client = -1;
    wifi.events = xEventGroupCreate();

    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t icfg = WIFI_INIT_CONFIG_DEFAULT();
    if (esp_wifi_init(&icfg) != ESP_OK) {
        return 2;
    }
    esp_wifi_set_storage(WIFI_STORAGE_RAM);
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event, NULL);

    wifi_config_t cfg = { 0 };
    strncpy((char *)cfg.sta.ssid, ssid, sizeof(cfg.sta.ssid) - 1);
    strncpy((char *)cfg.sta.password, pass, sizeof(cfg.sta.password) - 1);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &cfg);
    esp_wifi_start();
    /* Modem power-save trades multi-ms PHY sleep/wake bursts for battery.
     * A flight controller wants deterministic interrupt latency, not
     * standby current. */
    esp_wifi_set_ps(WIFI_PS_NONE);
    esp_wifi_connect();

    if (!(xEventGroupWaitBits(wifi.events, EV_GOT_IP, pdFALSE, pdFALSE,
                              pdMS_TO_TICKS(WIFI_JOIN_WAIT_MS)) & EV_GOT_IP)) {
        printf("[WIFI] no IP within %ds -- telemetry stays on UART0\n",
               WIFI_JOIN_WAIT_MS / 1000);
        /* Leave the join retrying in the background; harmless. */
        return 3;
    }

    printf("[WIFI] up: " IPSTR " tcp:%d (beacon udp:%d)\n",
           IP2STR(&wifi.ip), WIFI_TCP_PORT, WIFI_BEACON_PORT);

    /* Parenthesized to bypass the words->bytes xTaskCreate shim, which
     * also pins to the flight core. This task belongs on CORE 0 with the
     * rest of the network stack, and takes its stack in BYTES. */
    if ((xTaskCreatePinnedToCore)(wifi_server_task, "PIOS_WIFI",
                                  WIFI_TASK_STACK * 4, NULL,
                                  WIFI_TASK_PRIO, NULL, 0) != pdPASS) {
        return 4;
    }
    wifi.up = true;
    return 0;
}

#endif /* PIOS_INCLUDE_WIFI && PIOS_INCLUDE_COM */
