/**
 ******************************************************************************
 * @file       baro_sweep.c
 * @author     NinjaPilot, 2026
 * @brief      Bench sweep: measure barometer noise across oversampling and
 *             IIR settings, so the flight config is chosen from data.
 *
 * Build with BOARD_BARO_SWEEP=1 and the IDF console temporarily on UART0
 * (see sdkconfig.defaults). NEVER ship enabled: it adds a couple of minutes
 * to boot and leaves the part on whichever config it tested last.
 *
 * Two numbers per config, and the second is the one that matters:
 *
 *   sd     -- standard deviation of the raw samples. Includes real weather
 *             and the slow thermal drift of a board that has just powered up,
 *             so it flatters fast configs and punishes slow ones purely for
 *             taking longer to collect the same count.
 *   noise  -- RMS of successive differences / sqrt(2). A linear drift cancels
 *             in a first difference, so this isolates sample-to-sample noise,
 *             which is what an altitude estimator actually has to reject.
 *
 * Both are converted to centimetres using the air density computed from the
 * measured pressure and temperature, rather than a sea-level constant.
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

#ifdef BOARD_BARO_SWEEP

#include <math.h>
#include <pios_sensors.h>
#ifdef PIOS_INCLUDE_BMP388
#include <pios_bmp388.h>
#endif
#ifdef PIOS_INCLUDE_BMP280
#include <pios_bmp280.h>
#endif

#define SWEEP_SAMPLES  48
#define SWEEP_WARMUP   16   /* discarded: the IIR needs to fill before its
                             * output means anything, and a just-reset part
                             * reports its first conversions early */

struct sweep_stats {
    float mean_p, mean_t;
    float sd, noise, ptp;
};

/* Metres per pascal at the measured conditions. dP/dh = -rho*g, and
 * rho = P / (R_specific * T). Using the real numbers rather than a sea-level
 * constant matters here only for honesty of the cm column, but it is free. */
static float metres_per_pascal(float p, float t_c)
{
    const float R = 287.05f;      /* specific gas constant, dry air */
    const float g = 9.80665f;
    float rho = p / (R * (t_c + 273.15f));

    return 1.0f / (rho * g);
}

static bool collect(const PIOS_SENSORS_Driver *drv, uint32_t interval_ms,
                    struct sweep_stats *out)
{
    static float p[SWEEP_SAMPLES];
    float t_sum = 0.0f;
    unsigned n  = 0;
    unsigned attempts = 0;

    /* Warm-up, discarded. */
    for (unsigned i = 0; i < SWEEP_WARMUP; i++) {
        PIOS_DELAY_WaitmS(interval_ms);
        drv->poll(0);
    }

    while (n < SWEEP_SAMPLES && attempts < SWEEP_SAMPLES * 4) {
        PIOS_SENSORS_1Axis_SensorsWithTemp s;

        attempts++;
        PIOS_DELAY_WaitmS(interval_ms);
        if (!drv->poll(0)) {
            continue;
        }
        drv->fetch(&s, sizeof(s), 0);
        p[n] = s.sample;
        t_sum += s.temperature;
        n++;
    }
    if (n < SWEEP_SAMPLES) {
        return false;
    }

    float sum = 0.0f, min = p[0], max = p[0];
    for (unsigned i = 0; i < n; i++) {
        sum += p[i];
        if (p[i] < min) {
            min = p[i];
        }
        if (p[i] > max) {
            max = p[i];
        }
    }
    out->mean_p = sum / n;
    out->mean_t = t_sum / n;
    out->ptp    = max - min;

    float var = 0.0f;
    for (unsigned i = 0; i < n; i++) {
        float d = p[i] - out->mean_p;
        var += d * d;
    }
    out->sd = sqrtf(var / (n - 1));

    /* Successive differences: a constant drift term cancels, so what is left
     * is the sample-to-sample noise. Divided by sqrt(2) because differencing
     * two independent samples adds their variances. */
    float dsum = 0.0f;
    for (unsigned i = 1; i < n; i++) {
        float d = p[i] - p[i - 1];
        dsum += d * d;
    }
    out->noise = sqrtf(dsum / (n - 1)) / 1.41421356f;
    return true;
}

static void report(const char *label, uint32_t interval_ms, const struct sweep_stats *s)
{
    float mpp = metres_per_pascal(s->mean_p, s->mean_t);

    printf("[SWEEP] %-22s | %6u ms | %9.2f Pa %5.2f C | sd %6.3f Pa (%5.1f cm) | "
           "noise %6.3f Pa (%5.1f cm) | p-p %6.2f Pa\n",
           label, (unsigned)interval_ms, s->mean_p, s->mean_t,
           s->sd, s->sd * mpp * 100.0f,
           s->noise, s->noise * mpp * 100.0f,
           s->ptp);
}

#ifdef PIOS_INCLUDE_BMP388
static void sweep_bmp388(uint32_t i2c_id, uint8_t addr)
{
    static const struct {
        const char *label;
        enum pios_bmp388_osr    osr_p, osr_t;
        enum pios_bmp388_filter filt;
        enum pios_bmp388_odr    odr;
        uint32_t interval_ms;
    } tbl[] = {
        { "x1  IIR off  50Hz",  BMP388_OSR_1,  BMP388_OSR_1, BMP388_FILTER_OFF, BMP388_ODR_50_HZ,   40 },
        { "x2  IIR 1    50Hz",  BMP388_OSR_2,  BMP388_OSR_1, BMP388_FILTER_1,   BMP388_ODR_50_HZ,   40 },
        { "x4  IIR 3    50Hz",  BMP388_OSR_4,  BMP388_OSR_1, BMP388_FILTER_3,   BMP388_ODR_50_HZ,   40 },
        { "x8  IIR 3    50Hz*", BMP388_OSR_8,  BMP388_OSR_1, BMP388_FILTER_3,   BMP388_ODR_50_HZ,   40 },
        { "x8  IIR 7    50Hz",  BMP388_OSR_8,  BMP388_OSR_1, BMP388_FILTER_7,   BMP388_ODR_50_HZ,   40 },
        { "x8  IIR 15   50Hz",  BMP388_OSR_8,  BMP388_OSR_1, BMP388_FILTER_15,  BMP388_ODR_50_HZ,   40 },
        { "x16 IIR 7    25Hz",  BMP388_OSR_16, BMP388_OSR_2, BMP388_FILTER_7,   BMP388_ODR_25_HZ,   80 },
        { "x16 IIR 15   25Hz",  BMP388_OSR_16, BMP388_OSR_2, BMP388_FILTER_15,  BMP388_ODR_25_HZ,   80 },
        { "x16 IIR 31   25Hz",  BMP388_OSR_16, BMP388_OSR_2, BMP388_FILTER_31,  BMP388_ODR_25_HZ,   80 },
        { "x32 IIR 15 12.5Hz",  BMP388_OSR_32, BMP388_OSR_2, BMP388_FILTER_15,  BMP388_ODR_12_5_HZ, 160 },
        { "x32 IIR 31 12.5Hz",  BMP388_OSR_32, BMP388_OSR_2, BMP388_FILTER_31,  BMP388_ODR_12_5_HZ, 160 },
    };

    printf("[SWEEP] BMP388 at 0x%02X, %d samples per config (* = current flight config)\n",
           addr, SWEEP_SAMPLES);
    for (unsigned i = 0; i < NELEMENTS(tbl); i++) {
        struct pios_bmp388_cfg c = {
            .oversampling_pressure    = tbl[i].osr_p,
            .oversampling_temperature = tbl[i].osr_t,
            .filter                   = tbl[i].filt,
            .odr                      = tbl[i].odr,
            .i2c_addr                 = addr,
        };
        int32_t rc = PIOS_BMP388_Init(&c, i2c_id);
        if (rc != 0) {
            /* -9 is the part's own conf_err: this ODR is too fast for this
             * oversampling, and it would have repeated stale samples. */
            printf("[SWEEP] %-22s | REJECTED by the part (%d)\n", tbl[i].label, (int)rc);
            continue;
        }
        struct sweep_stats st;
        if (collect(&PIOS_BMP388_Driver, tbl[i].interval_ms, &st)) {
            report(tbl[i].label, tbl[i].interval_ms, &st);
        } else {
            printf("[SWEEP] %-22s | too few samples\n", tbl[i].label);
        }
    }
}
#endif /* PIOS_INCLUDE_BMP388 */

#ifdef PIOS_INCLUDE_BMP280
static void sweep_bmp280(uint32_t i2c_id, uint8_t addr)
{
    static const struct {
        const char *label;
        enum pios_bmp280_osr    osr_p, osr_t;
        enum pios_bmp280_filter filt;
        uint32_t interval_ms;
    } tbl[] = {
        { "x1  IIR off",  BMP280_OSR_1,  BMP280_OSR_1, BMP280_FILTER_OFF, 40  },
        { "x2  IIR 2",    BMP280_OSR_2,  BMP280_OSR_1, BMP280_FILTER_2,   40  },
        { "x4  IIR 4",    BMP280_OSR_4,  BMP280_OSR_1, BMP280_FILTER_4,   40  },
        { "x8  IIR 4",    BMP280_OSR_8,  BMP280_OSR_1, BMP280_FILTER_4,   60  },
        { "x8  IIR 8",    BMP280_OSR_8,  BMP280_OSR_1, BMP280_FILTER_8,   60  },
        { "x8  IIR 16",   BMP280_OSR_8,  BMP280_OSR_1, BMP280_FILTER_16,  60  },
        { "x16 IIR 4",    BMP280_OSR_16, BMP280_OSR_2, BMP280_FILTER_4,   80  },
        { "x16 IIR 8",    BMP280_OSR_16, BMP280_OSR_2, BMP280_FILTER_8,   80  },
        { "x16 IIR 16*",  BMP280_OSR_16, BMP280_OSR_2, BMP280_FILTER_16,  80  },
    };

    printf("[SWEEP] BMP280 at 0x%02X, %d samples per config (* = current flight config)\n",
           addr, SWEEP_SAMPLES);
    for (unsigned i = 0; i < NELEMENTS(tbl); i++) {
        struct pios_bmp280_cfg c = {
            .oversampling_pressure    = tbl[i].osr_p,
            .oversampling_temperature = tbl[i].osr_t,
            .filter                   = tbl[i].filt,
            .i2c_addr                 = addr,
        };
        int32_t rc = PIOS_BMP280_Init(&c, i2c_id);
        if (rc != 0) {
            printf("[SWEEP] %-22s | init failed (%d)\n", tbl[i].label, (int)rc);
            continue;
        }
        struct sweep_stats st;
        if (collect(&PIOS_BMP280_Driver, tbl[i].interval_ms, &st)) {
            report(tbl[i].label, tbl[i].interval_ms, &st);
        } else {
            printf("[SWEEP] %-22s | too few samples\n", tbl[i].label);
        }
    }
}
#endif /* PIOS_INCLUDE_BMP280 */

void PIOS_BaroSweep(uint32_t i2c_id, uint8_t addr, bool is_bmp388)
{
    printf("\n[SWEEP] ==== barometer configuration sweep ====\n");
    printf("[SWEEP] Keep the board STILL and the room quiet -- doors and HVAC "
           "move real pressure and land in 'sd'.\n");
#ifdef PIOS_INCLUDE_BMP388
    if (is_bmp388) {
        sweep_bmp388(i2c_id, addr);
    }
#endif
#ifdef PIOS_INCLUDE_BMP280
    if (!is_bmp388) {
        sweep_bmp280(i2c_id, addr);
    }
#endif
    printf("[SWEEP] ==== sweep complete; the part is left on the LAST config "
           "tested, so reflash before flying ====\n\n");
}

#endif /* BOARD_BARO_SWEEP */
