/**
 ******************************************************************************
 * @file       tunes.h
 * @brief      Short tunes for the ESCs: note tables, played as BeepCommand notes.
 *****************************************************************************/
#ifndef TUNES_H
#define TUNES_H

#include <stdint.h>

struct tune_note {
    uint16_t hz;    /* 0 = rest */
    uint16_t ms;
};

struct tune {
    const char *name;
    const struct tune_note *notes;
    uint8_t count;
};

/* id = TuneSettings ArmTune/DisarmTune enum value; NULL for None or unknown */
const struct tune *tune_get(uint8_t id);

uint8_t tune_count(void);

#endif /* TUNES_H */
