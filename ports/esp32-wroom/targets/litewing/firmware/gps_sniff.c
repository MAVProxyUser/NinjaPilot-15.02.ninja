/**
 ******************************************************************************
 * @file       gps_sniff.c
 * @author     NinjaPilot, 2026
 * @brief      Bench bring-up: is anything talking on the GPS UART, and at what
 *             baud?
 *
 * Build with BOARD_GPS_SNIFF=1 and the IDF console temporarily on UART0
 * (sdkconfig), because this borrows UART1 -- GPIO17/18 -- which is where the
 * console normally lives. Bench only; never ship enabled.
 *
 * Tries each candidate baud in turn and reports what arrived. A u-blox module
 * speaks one of two things: NMEA, which is ASCII lines beginning "$G", or UBX,
 * which is binary framed by 0xB5 0x62. Seeing neither, but seeing bytes, means
 * the baud is wrong. Seeing nothing at all means wiring or power.
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

#ifdef BOARD_GPS_SNIFF

#include "driver/uart.h"
#include "driver/gpio.h"

#define GPS_UART      UART_NUM_1
#define GPS_TX_PIN    GPIO_NUM_17   /* board -> GPS RX */
#define GPS_RX_PIN    GPIO_NUM_18   /* board <- GPS TX */
#define GPS_BUF       2048

/* 115200 first: that is what the board is configured for, so the common case
 * answers immediately. 38400 is next because it is the u-blox M10 default. */
static const int candidate_baud[] = { 115200, 38400, 9600, 57600, 4800 };

void PIOS_GPS_Sniff(void)
{
    static uint8_t buf[GPS_BUF];

    printf("\n[GPSSNIFF] ==== listening on UART1 (RX=GPIO%d, TX=GPIO%d) ====\n",
           (int)GPS_RX_PIN, (int)GPS_TX_PIN);

    for (unsigned b = 0; b < NELEMENTS(candidate_baud); b++) {
        int baud = candidate_baud[b];

        uart_config_t cfg = {
            .baud_rate  = baud,
            .data_bits  = UART_DATA_8_BITS,
            .parity     = UART_PARITY_DISABLE,
            .stop_bits  = UART_STOP_BITS_1,
            .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
            .source_clk = UART_SCLK_DEFAULT,
        };

        uart_driver_delete(GPS_UART);
        if (uart_driver_install(GPS_UART, GPS_BUF * 2, 0, 0, NULL, 0) != ESP_OK
            || uart_param_config(GPS_UART, &cfg) != ESP_OK
            || uart_set_pin(GPS_UART, GPS_TX_PIN, GPS_RX_PIN,
                            UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) != ESP_OK) {
            printf("[GPSSNIFF] %6d baud: could not open UART1\n", baud);
            continue;
        }

        uart_flush_input(GPS_UART);
        /* vTaskDelay, NOT PIOS_DELAY_WaitmS: the latter is a busy wait, and
         * five of them back to back starve the idle task long enough for the
         * task watchdog to reboot the board mid-sweep -- which is exactly how
         * this sniffer came to report only its first candidate, over and over. */
        vTaskDelay(pdMS_TO_TICKS(1200));

        int n = uart_read_bytes(GPS_UART, buf, sizeof(buf) - 1, 20 / portTICK_PERIOD_MS);
        if (n <= 0) {
            printf("[GPSSNIFF] %6d baud: silence\n", baud);
            continue;
        }
        buf[n] = 0;

        /* What did we get? */
        bool nmea = false, ubx = false;
        int printable = 0;
        for (int i = 0; i < n; i++) {
            if (buf[i] == '$' && i + 2 < n && buf[i + 1] == 'G') {
                nmea = true;
            }
            if (buf[i] == 0xB5 && i + 1 < n && buf[i + 1] == 0x62) {
                ubx = true;
            }
            if ((buf[i] >= 32 && buf[i] < 127) || buf[i] == '\r' || buf[i] == '\n') {
                printable++;
            }
        }
        printf("[GPSSNIFF] %6d baud: %4d bytes, %d%% printable%s%s\n",
               baud, n, (100 * printable) / n,
               nmea ? "  <-- NMEA ($G)" : "", ubx ? "  <-- UBX (b5 62)" : "");

        /* Show the first couple of lines so the sentences are readable. */
        int shown = 0;
        for (int i = 0; i < n && shown < 3; i++) {
            if (buf[i] == '$') {
                int j = i;
                printf("[GPSSNIFF]   ");
                while (j < n && buf[j] != '\r' && buf[j] != '\n' && j - i < 90) {
                    putchar(buf[j] >= 32 && buf[j] < 127 ? buf[j] : '.');
                    j++;
                }
                printf("\n");
                shown++;
                i = j;
            }
        }
        if (!shown) {
            printf("[GPSSNIFF]   first 32 bytes:");
            for (int i = 0; i < n && i < 32; i++) {
                printf(" %02X", buf[i]);
            }
            printf("\n");
        }
        if (nmea || ubx) {
            printf("[GPSSNIFF] ==== module found at %d baud ====\n", baud);
            uart_driver_delete(GPS_UART);
            return;
        }
    }
    uart_driver_delete(GPS_UART);
    printf("[GPSSNIFF] ==== nothing recognisable on any baud ====\n");
}

#endif /* BOARD_GPS_SNIFF */
