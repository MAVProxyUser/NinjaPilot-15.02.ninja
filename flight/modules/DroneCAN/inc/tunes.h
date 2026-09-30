/**
 ******************************************************************************
 * @file       tunes.h
 * @brief      Short tunes for the ESCs: note tables, the AM32/BlueJay startup
 *             melody encoding, and the float16 the BeepCommand message wants.
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

/* AM32 startup melody (BlueJay layout): header, then (pulses, period) pairs,
 * (0,0) terminates.  gap_ms (10..150, or 0) is the silence the ESC inserts
 * after every entry.  Returns the number of bytes used, at most 128. */
uint8_t tune_to_bluejay(const struct tune *t, uint8_t out[128], uint8_t gap_ms);

uint16_t f32_to_f16(float f);

#endif /* TUNES_H */
