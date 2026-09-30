/**
 ******************************************************************************
 * @file       tunes.c
 * @brief      Short tunes for the ESCs.
 *
 * The note tables are opening motifs only: a few seconds at most, because
 * the aircraft is armed while they play.  Frequencies are equal temperament
 * (A4 = 440); the AM32 melody engine reaches roughly 150 Hz to 2.3 kHz, so
 * everything sits in octaves 4 and 5.
 *****************************************************************************/
#include "tunes.h"
#include <string.h>

#define C4 262
#define D4 294
#define Eb4 311
#define E4 330
#define F4 349
#define Gb4 370
#define G4 392
#define A4 440
#define Bb4 466
#define B4 494
#define C5 523
#define D5 587
#define Eb5 622
#define E5 659
#define F5 698
#define G5 784

/* the march: quarter 450 ms */
static const struct tune_note imperial_march[] = {
    { G4, 450 }, { G4, 450 }, { G4, 450 }, { Eb4, 340 }, { Bb4, 110 },
    { G4, 450 }, { Eb4, 340 }, { Bb4, 110 }, { G4, 900 },
};

/* the fifth: eighths at 150 ms, the held notes long */
static const struct tune_note beethoven5[] = {
    { G4, 150 }, { G4, 150 }, { G4, 150 }, { Eb4, 700 }, { 0, 200 },
    { F4, 150 }, { F4, 150 }, { F4, 150 }, { D4, 900 },
};

/* the ode: quarter 300 ms */
static const struct tune_note ode_to_joy[] = {
    { E4, 300 }, { E4, 300 }, { F4, 300 }, { G4, 300 }, { G4, 300 }, { F4, 300 }, { E4, 300 }, { D4, 300 },
    { C4, 300 }, { C4, 300 }, { D4, 300 }, { E4, 300 }, { E4, 450 }, { D4, 150 }, { D4, 600 },
};

/* the folk song from the falling-blocks game: quarter 250 ms */
static const struct tune_note korobeiniki[] = {
    { E5, 250 }, { B4, 125 }, { C5, 125 }, { D5, 250 }, { C5, 125 }, { B4, 125 },
    { A4, 250 }, { A4, 125 }, { C5, 125 }, { E5, 250 }, { D5, 125 }, { C5, 125 },
    { B4, 375 }, { C5, 125 }, { D5, 250 }, { E5, 250 }, { C5, 250 }, { A4, 250 }, { A4, 500 },
};

/* the ballpark fanfare */
static const struct tune_note charge[] = {
    { G4, 130 }, { C5, 130 }, { E5, 130 }, { G5, 260 }, { E5, 130 }, { G5, 600 },
};

static const struct tune tunes[] = {
    { "None",          NULL,           0 },
    { "ImperialMarch", imperial_march, sizeof(imperial_march) / sizeof(imperial_march[0]) },
    { "Beethoven5th",  beethoven5,     sizeof(beethoven5) / sizeof(beethoven5[0]) },
    { "OdeToJoy",      ode_to_joy,     sizeof(ode_to_joy) / sizeof(ode_to_joy[0]) },
    { "Korobeiniki",   korobeiniki,    sizeof(korobeiniki) / sizeof(korobeiniki[0]) },
    { "Charge",        charge,         sizeof(charge) / sizeof(charge[0]) },
};

const struct tune *tune_get(uint8_t id)
{
    if (id == 0 || id >= sizeof(tunes) / sizeof(tunes[0]) || !tunes[id].notes) {
        return NULL;
    }
    return &tunes[id];
}

/* AM32 plays entry (t4, t3) as t4 pulses of period t3*247+4000 (100 ns
 * units); t3 = 0 makes it a rest of t4 ms; t4 = 255 adds 255 pulses to the
 * next entry without playing.  Its duration arithmetic divides by 11000. */
uint8_t tune_to_bluejay(const struct tune *t, uint8_t out[128], uint8_t gap_ms)
{
    uint8_t n = 4;

    memset(out, 0, 128);
    out[0] = 1;                             /* anything but the erased-flash byte: melody present */
    out[3] = gap_ms ? (uint8_t)(255 - gap_ms / 10) : 0;
    for (uint8_t i = 0; t && i < t->count && n + 2 <= 126; i++) {
        uint16_t hz = t->notes[i].hz, ms = t->notes[i].ms;
        if (hz == 0) {
            while (ms && n + 2 <= 126) {
                uint8_t chunk = ms > 254 ? 254 : (uint8_t)ms;
                out[n++] = chunk; out[n++] = 0;
                ms = (uint16_t)(ms - chunk);
            }
            continue;
        }
        uint32_t t3 = (10000000u / hz + 123u - 4000u) / 247u;
        if (t3 < 1) { t3 = 1; }
        if (t3 > 254) { t3 = 254; }
        uint32_t period = t3 * 247u + 4000u;
        uint32_t pulses = ((uint32_t)ms * 11000u + period / 2) / period;
        if (pulses == 0) { pulses = 1; }
        if (pulses % 255u == 0) { pulses--; }            /* the last entry must play */
        while (pulses > 255u && n + 4 <= 126) {
            out[n++] = 255; out[n++] = (uint8_t)t3;       /* +255 pulses, carried */
            pulses -= 255u;
        }
        out[n++] = (uint8_t)pulses; out[n++] = (uint8_t)t3;
    }
    out[n++] = 0; out[n++] = 0;                           /* terminator */
    return n;
}

/* IEEE half precision, round to nearest; enough for Hz and seconds */
uint16_t f32_to_f16(float f)
{
    uint32_t u;
    memcpy(&u, &f, 4);
    uint32_t sign = (u >> 16) & 0x8000u;
    int32_t  exp  = (int32_t)((u >> 23) & 0xFFu) - 127 + 15;
    uint32_t mant = u & 0x7FFFFFu;

    if (exp <= 0) {
        if (exp < -10) { return (uint16_t)sign; }
        mant |= 0x800000u;
        uint32_t shift = (uint32_t)(14 - exp);
        uint32_t half = (mant >> shift) + ((mant >> (shift - 1)) & 1u);
        return (uint16_t)(sign | half);
    }
    if (exp >= 31) { return (uint16_t)(sign | 0x7C00u); }
    uint32_t half = ((uint32_t)exp << 10) | (mant >> 13);
    if (mant & 0x1000u) { half++; }
    return (uint16_t)(sign | half);
}
