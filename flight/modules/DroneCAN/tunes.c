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

/* the march, brisk: quarter 320 ms, about three seconds in all */
static const struct tune_note imperial_march[] = {
    { G4, 320 }, { G4, 320 }, { G4, 320 }, { Eb4, 240 }, { Bb4, 80 },
    { G4, 320 }, { Eb4, 240 }, { Bb4, 80 }, { G4, 640 },
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

uint8_t tune_count(void)
{
    return (uint8_t)(sizeof(tunes) / sizeof(tunes[0]));
}
