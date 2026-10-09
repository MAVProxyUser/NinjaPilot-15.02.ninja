/**
 ******************************************************************************
 * @file       tunes.h
 * @brief      Short tunes for the ESCs, up to four voices (one per motor).
 *****************************************************************************/
#ifndef TUNES_H
#define TUNES_H

#include <stdint.h>

#define TUNE_VOICES 4

/* one step: a pitch per voice (0 = that voice rests) and how long */
struct tune_step {
    uint16_t hz[TUNE_VOICES];
    uint16_t ms;
};

struct tune {
    const char *name;
    const struct tune_step *steps;
    uint8_t count;
};

/* id = TuneSettings ArmTune/DisarmTune enum value; NULL for None or unknown */
const struct tune *tune_get(uint8_t id);

#endif /* TUNES_H */
