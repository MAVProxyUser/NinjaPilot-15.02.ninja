/**
 ******************************************************************************
 * @file       pios_rid_wifi.c
 * @brief      ASTM F3411 Broadcast Remote ID over WiFi Beacon for the ESP32.
 *
 * The RemoteID module hands us an encoded Message Pack once a second. We put
 * it in a vendor-specific information element (element 0xDD, OUI FA:0B:BC,
 * type 0x0D, one counter byte, then the pack) attached to the soft-AP's own
 * beacon and probe-response frames via esp_wifi_set_vendor_ie(). The WiFi
 * driver then repeats it in every beacon (100 ms) with no task of ours
 * involved - the cheapest possible way to broadcast from a flight board.
 *
 * Modes:
 *   - telemetry WiFi up (pios_wifi.c joined an AP as a station): we add a
 *     soft-AP alongside it (APSTA). The AP rides the station's channel.
 *   - no telemetry WiFi (no credentials): we bring WiFi up in AP-only mode on
 *     channel 6 so Remote ID works without any network configured.
 * The AP is named RID-<last 3 MAC bytes>, WPA2 with an unguessable key and one
 * allowed connection: receivers only need to hear its beacons, nobody joins.
 *
 * Receivers: the OpenDroneID app (Android), any F3411 WiFi-beacon scanner.
 * @see        The GNU Public License (GPL) Version 3
 *****************************************************************************/
#include "pios.h"

#ifdef PIOS_INCLUDE_RID_WIFI

#include <pios_rid.h>
#include <string.h>
#include <stdio.h>
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_mac.h"

static bool ap_ready;
static bool ie_set;

static int rid_ap_start(void)
{
    wifi_mode_t mode = WIFI_MODE_NULL;
    esp_err_t e = esp_wifi_get_mode(&mode);
    bool standalone = false;

    if (e == ESP_ERR_WIFI_NOT_INIT) {
        /* No telemetry WiFi: bring the stack up for the AP alone. */
        esp_netif_init();
        esp_event_loop_create_default();
        esp_netif_create_default_wifi_ap();
        wifi_init_config_t icfg = WIFI_INIT_CONFIG_DEFAULT();
        if (esp_wifi_init(&icfg) != ESP_OK) {
            printf("[RID] esp_wifi_init failed\n");
            return -1;
        }
        esp_wifi_set_storage(WIFI_STORAGE_RAM);
        standalone = true;
        mode = WIFI_MODE_NULL;
    } else if (e != ESP_OK) {
        return -1;
    } else {
        /* Station already running: give the AP side its netif before APSTA. */
        esp_netif_create_default_wifi_ap();
    }

    uint8_t mac[6] = { 0 };
    esp_read_mac(mac, ESP_MAC_WIFI_SOFTAP);

    wifi_config_t ap;
    memset(&ap, 0, sizeof(ap));
    int n = snprintf((char *)ap.ap.ssid, sizeof(ap.ap.ssid), "RID-%02X%02X%02X", mac[3], mac[4], mac[5]);
    ap.ap.ssid_len = (uint8_t)(n > 0 ? n : 0);
    snprintf((char *)ap.ap.password, sizeof(ap.ap.password), "rid-%02x%02x%02x%02x%02x%02x-nojoin",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    ap.ap.authmode        = WIFI_AUTH_WPA2_PSK;
    ap.ap.max_connection  = 1;
    ap.ap.beacon_interval = 100;         /* TU; the F3411 WiFi Beacon cadence */
    ap.ap.ssid_hidden     = 0;
    ap.ap.channel         = standalone ? 6 : 0;   /* APSTA: follows the station */

    wifi_mode_t want = (mode == WIFI_MODE_STA || mode == WIFI_MODE_APSTA) ? WIFI_MODE_APSTA : WIFI_MODE_AP;
    if (esp_wifi_set_mode(want) != ESP_OK) {
        printf("[RID] esp_wifi_set_mode(%d) failed\n", (int)want);
        return -1;
    }
    if (esp_wifi_set_config(WIFI_IF_AP, &ap) != ESP_OK) {
        printf("[RID] esp_wifi_set_config(AP) failed\n");
        return -1;
    }
    if (standalone) {
        if (esp_wifi_start() != ESP_OK) {
            printf("[RID] esp_wifi_start failed\n");
            return -1;
        }
        esp_wifi_set_ps(WIFI_PS_NONE);
    }
    printf("[RID] beacon transmitter up: SSID %s (%s)\n", (char *)ap.ap.ssid,
           standalone ? "AP only, channel 6" : "alongside telemetry station");
    return 0;
}

int32_t PIOS_RID_Broadcast(const uint8_t *pack, uint16_t len, uint8_t counter)
{
    static uint8_t ie[7 + 255];

    if (!pack || !len) {
        if (ie_set) {
            esp_wifi_set_vendor_ie(false, WIFI_VND_IE_TYPE_BEACON, WIFI_VND_IE_ID_0, NULL);
            esp_wifi_set_vendor_ie(false, WIFI_VND_IE_TYPE_PROBE_RESP, WIFI_VND_IE_ID_0, NULL);
            ie_set = false;
        }
        return 0;
    }
    if (!ap_ready) {
        if (rid_ap_start() != 0) {
            return -1;
        }
        ap_ready = true;
    }
    if (len + 5 > 255) {
        return -2;
    }
    ie[0] = 0xDD;                       /* vendor specific */
    ie[1] = (uint8_t)(5 + len);         /* OUI(3) + type(1) + counter(1) + pack */
    ie[2] = 0xFA; ie[3] = 0x0B; ie[4] = 0xBC;   /* ASD-STAN / ASTM OUI */
    ie[5] = 0x0D;                       /* Open Drone ID */
    ie[6] = counter;
    memcpy(ie + 7, pack, len);
    if (esp_wifi_set_vendor_ie(true, WIFI_VND_IE_TYPE_BEACON, WIFI_VND_IE_ID_0, ie) != ESP_OK) {
        return -3;
    }
    (void)esp_wifi_set_vendor_ie(true, WIFI_VND_IE_TYPE_PROBE_RESP, WIFI_VND_IE_ID_0, ie);
    ie_set = true;
    return 0;
}

#endif /* PIOS_INCLUDE_RID_WIFI */
