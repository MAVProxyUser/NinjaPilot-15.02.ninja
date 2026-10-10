/**
 ******************************************************************************
 * @file       tunes.c
 * @brief      Short tunes for the ESCs, arranged for four motors.
 *
 * Opening motifs only, a few seconds each. Voice 0 and 1 carry the melody
 * (ESC index 0 and 1), voice 2 a harmony line and voice 3 the bass, so
 * every motor sings and the tune has some body. In AllTogether mode only
 * voice 0 is sent, to every motor, as the standard BeepCommand.
 *****************************************************************************/
#include "tunes.h"

#define C3 131
#define D3 147
#define Eb3 156
#define E3 165
#define F3 175
#define G3 196
#define Ab3 208
#define A3 220
#define Bb3 233
#define B3 247
#define C4 262
#define D4 294
#define Eb4 311
#define E4 330
#define F4 349
#define Gb4 370
#define G4 392
#define Ab4 415
#define A4 440
#define Bb4 466
#define B4 494
#define C5 523
#define D5 587
#define Eb5 622
#define E5 659
#define F5 698
#define G5 784
#define Ab5 831
#define A5 880
#define Bb5 932
#define B5 988
#define C6 1047
#define Db5 554
#define Gb3 185
#define Db4 277
#define Fs5 740
#define Ds5 622
#define Cs5 554
#define Gs4 415
#define Fs4 370
#define Cs4 277
#define Ds4 311
#define Fs3 185

/* the march: melody in octaves, the fifth above as harmony, the root an octave down */
static const struct tune_step imperial_march[] = {
    { { G4, G4, D4, G3 }, 320 }, { { G4, G4, D4, G3 }, 320 }, { { G4, G4, D4, G3 }, 320 },
    { { Eb4, Eb4, Bb3, Eb3 }, 240 }, { { Bb4, Bb4, F4, Bb3 }, 80 },
    { { G4, G4, D4, G3 }, 320 }, { { Eb4, Eb4, Bb3, Eb3 }, 240 }, { { Bb4, Bb4, F4, Bb3 }, 80 },
    { { G4, G4, D4, G3 }, 640 },
};

/* the fifth: unison hammer blows, the held notes voiced as a chord */
static const struct tune_step beethoven5[] = {
    { { G4, G4, G4, G4 }, 150 }, { { G4, G4, G4, G4 }, 150 }, { { G4, G4, G4, G4 }, 150 }, { { Eb4, Eb4, G3, Eb3 }, 700 },
    { { 0, 0, 0, 0 }, 200 },
    { { F4, F4, F4, F4 }, 150 }, { { F4, F4, F4, F4 }, 150 }, { { F4, F4, F4, F4 }, 150 }, { { D4, D4, G3, G3 }, 900 },
};

/* the ode: melody, thirds below, and a bass on the chord roots */
static const struct tune_step ode_to_joy[] = {
    { { E4, E4, C4, C3 }, 300 }, { { E4, E4, C4, C3 }, 300 }, { { F4, F4, D4, G3 }, 300 }, { { G4, G4, E4, C3 }, 300 },
    { { G4, G4, E4, C3 }, 300 }, { { F4, F4, D4, G3 }, 300 }, { { E4, E4, C4, C3 }, 300 }, { { D4, D4, B3, G3 }, 300 },
    { { C4, C4, A3, F3 }, 300 }, { { C4, C4, A3, F3 }, 300 }, { { D4, D4, B3, G3 }, 300 }, { { E4, E4, C4, C3 }, 300 },
    { { E4, E4, C4, C3 }, 450 }, { { D4, D4, B3, G3 }, 150 }, { { D4, D4, B3, G3 }, 600 },
};

/* the folk song: melody doubled, a drone bass in the minor */
static const struct tune_step korobeiniki[] = {
    { { E5, E5, E4, A3 }, 250 }, { { B4, B4, E4, A3 }, 125 }, { { C5, C5, E4, A3 }, 125 }, { { D5, D5, E4, A3 }, 250 },
    { { C5, C5, E4, A3 }, 125 }, { { B4, B4, E4, A3 }, 125 }, { { A4, A4, E4, A3 }, 250 }, { { A4, A4, E4, A3 }, 125 },
    { { C5, C5, E4, A3 }, 125 }, { { E5, E5, E4, A3 }, 250 }, { { D5, D5, E4, A3 }, 125 }, { { C5, C5, E4, A3 }, 125 },
    { { B4, B4, E4, E3 }, 375 }, { { C5, C5, E4, E3 }, 125 }, { { D5, D5, E4, E3 }, 250 }, { { E5, E5, E4, E3 }, 250 },
    { { C5, C5, E4, A3 }, 250 }, { { A4, A4, E4, A3 }, 250 }, { { A4, A4, E4, A3 }, 500 },
};

/* the fanfare, in octaves with a drone */
static const struct tune_step charge[] = {
    { { G4, G4, G3, C3 }, 130 }, { { C5, C5, C4, C3 }, 130 }, { { E5, E5, E4, C3 }, 130 },
    { { G5, G5, G4, C3 }, 260 }, { { E5, E5, E4, C3 }, 130 }, { { G5, G5, G4, C3 }, 600 },
};


/* the cop theme hook: melody doubled, a fifth under it on voice 2, a bass
 * drone with a thump on voice 3 (the low end of a motor is a drum) */
static const struct tune_step axel_f[] = {
    { { F4, F4, C4, F3 }, 400 }, { { Ab4, Ab4, Eb4, F3 }, 250 }, { { F4, F4, C4, 0 }, 250 }, { { F4, F4, C4, F3 }, 125 },
    { { Bb4, Bb4, F4, 0 }, 250 }, { { F4, F4, C4, F3 }, 250 }, { { Eb4, Eb4, Bb3, 0 }, 250 },
    { { F4, F4, C4, F3 }, 400 }, { { C5, C5, G4, F3 }, 250 }, { { F4, F4, C4, 0 }, 250 }, { { F4, F4, C4, F3 }, 125 },
    { { Db5, Db5, Ab4, 0 }, 250 }, { { C5, C5, G4, F3 }, 250 }, { { Ab4, Ab4, Eb4, 0 }, 250 },
    { { F4, F4, C4, F3 }, 250 }, { { C5, C5, G4, 0 }, 250 }, { { F5, F5, C5, F3 }, 250 }, { { F4, F4, C4, 0 }, 125 },
    { { Eb4, Eb4, Bb3, F3 }, 250 }, { { Eb4, Eb4, Bb3, 0 }, 125 }, { { C4, C4, G3, F3 }, 250 }, { { G4, G4, D4, 0 }, 250 },
    { { F4, F4, C4, F3 }, 500 },
    /* the drum fill: four thumps on the bass motor */
    { { 0, 0, 0, C3 }, 120 }, { { 0, 0, 0, 0 }, 80 }, { { 0, 0, 0, C3 }, 120 }, { { 0, 0, 0, 0 }, 80 },
    { { 0, 0, 0, C3 }, 120 }, { { 0, 0, 0, 0 }, 80 }, { { 0, 0, 0, C3 }, 250 },
};

/* the boxing riff: stabs in octaves over a minor drone, a thump under each stab */
static const struct tune_step eye_of_the_tiger[] = {
    { { C5, C4, G3, C3 }, 350 }, { { 0, 0, G3, 0 }, 300 },
    { { C5, C4, G3, C3 }, 150 }, { { Bb4, Bb3, G3, 0 }, 150 }, { { C5, C4, G3, C3 }, 300 }, { { 0, 0, G3, 0 }, 250 },
    { { C5, C4, G3, C3 }, 150 }, { { Bb4, Bb3, G3, 0 }, 150 }, { { C5, C4, G3, C3 }, 300 }, { { 0, 0, G3, 0 }, 250 },
    { { C5, C4, G3, C3 }, 150 }, { { Bb4, Bb3, G3, 0 }, 150 }, { { Ab4, Ab3, Eb4, Ab3 }, 600 },
};

/* Beethoven's bagatelle, the opening bars; melody on two motors, bass on the fourth */
static const struct tune_step fur_elise[] = {
    { { E5, E5, 0, 0 }, 180 }, { { Ds5, Ds5, 0, 0 }, 180 }, { { E5, E5, 0, 0 }, 180 }, { { Ds5, Ds5, 0, 0 }, 180 },
    { { E5, E5, 0, 0 }, 180 }, { { B4, B4, 0, 0 }, 180 }, { { D5, D5, 0, 0 }, 180 }, { { C5, C5, 0, 0 }, 180 },
    { { A4, A4, 0, A3 }, 360 }, { { 0, 0, 0, 0 }, 100 }, { { C4, C4, 0, A3 }, 180 }, { { E4, E4, 0, 0 }, 180 }, { { A4, A4, 0, 0 }, 180 },
    { { B4, B4, 0, E3 }, 360 }, { { 0, 0, 0, 0 }, 100 }, { { E4, E4, 0, E3 }, 180 }, { { Gs4, Gs4, 0, 0 }, 180 }, { { B4, B4, 0, 0 }, 180 },
    { { C5, C5, 0, A3 }, 540 },
};

/* Grieg's trolls: the creeping theme, bass on the beat */
static const struct tune_step mountain_king[] = {
    { { B3, B3, 0, B3 }, 160 }, { { Cs4, Cs4, 0, 0 }, 160 }, { { D4, D4, 0, B3 }, 160 }, { { E4, E4, 0, 0 }, 160 },
    { { Fs4, Fs4, 0, B3 }, 160 }, { { D4, D4, 0, 0 }, 160 }, { { Fs4, Fs4, 0, B3 }, 320 },
    { { F4, F4, 0, 0 }, 160 }, { { Cs4, Cs4, 0, B3 }, 160 }, { { F4, F4, 0, 0 }, 320 },
    { { E4, E4, 0, B3 }, 160 }, { { C4, C4, 0, 0 }, 160 }, { { E4, E4, 0, B3 }, 320 },
    { { B3, B3, 0, B3 }, 160 }, { { Cs4, Cs4, 0, 0 }, 160 }, { { D4, D4, 0, B3 }, 160 }, { { E4, E4, 0, 0 }, 160 },
    { { Fs4, Fs4, 0, B3 }, 160 }, { { D4, D4, 0, 0 }, 160 }, { { Fs4, Fs4, 0, B3 }, 160 }, { { B4, B4, 0, 0 }, 160 },
    { { A4, A4, 0, B3 }, 160 }, { { Fs4, Fs4, 0, 0 }, 160 }, { { D4, D4, 0, B3 }, 160 }, { { Fs4, Fs4, 0, 0 }, 160 },
    { { A4, A4, 0, B3 }, 480 },
};

/* Tarrega's Gran Vals, the four bars everyone knows as a ringtone */
static const struct tune_step gran_vals[] = {
    { { E5, E5, 0, A3 }, 125 }, { { D5, D5, 0, 0 }, 125 }, { { Fs4, Fs4, 0, A3 }, 250 }, { { Gs4, Gs4, 0, 0 }, 250 },
    { { Cs5, Cs5, 0, E3 }, 125 }, { { B4, B4, 0, 0 }, 125 }, { { D4, D4, 0, E3 }, 250 }, { { E4, E4, 0, 0 }, 250 },
    { { B4, B4, 0, A3 }, 125 }, { { A4, A4, 0, 0 }, 125 }, { { Cs4, Cs4, 0, A3 }, 250 }, { { E4, E4, 0, 0 }, 250 },
    { { A4, A4, Cs4, A3 }, 750 },
};

/* Wagner's ride, the opening call */
static const struct tune_step valkyries[] = {
    { { Fs4, Fs4, 0, B3 }, 200 }, { { B4, B4, 0, 0 }, 100 }, { { Fs4, Fs4, 0, B3 }, 300 }, { { B4, B4, 0, 0 }, 300 },
    { { D5, D5, Fs4, B3 }, 600 }, { { B4, B4, 0, 0 }, 300 }, { { D5, D5, 0, B3 }, 100 }, { { B4, B4, 0, 0 }, 300 },
    { { D5, D5, 0, B3 }, 300 }, { { Fs5, Fs5, B4, B3 }, 600 }, { { D5, D5, 0, 0 }, 300 }, { { Fs5, Fs5, 0, B3 }, 100 },
    { { D5, D5, 0, 0 }, 300 }, { { Fs5, Fs5, 0, B3 }, 300 }, { { A5, A5, D5, D4 }, 800 },
};

/* shave and a haircut */
static const struct tune_step shave_haircut[] = {
    { { C5, C5, E4, C3 }, 250 }, { { G4, G4, 0, 0 }, 125 }, { { G4, G4, 0, 0 }, 125 }, { { A4, A4, F4, F3 }, 250 }, { { G4, G4, E4, C3 }, 250 },
    { { 0, 0, 0, 0 }, 250 }, { { B4, B4, G4, G3 }, 250 }, { { C5, C5, E4, C3 }, 400 },
};

/* reveille, the bugle call */
static const struct tune_step reveille[] = {
    { { G4, G4, 0, 0 }, 150 }, { { C5, C5, 0, 0 }, 150 }, { { E5, E5, 0, 0 }, 150 }, { { C5, C5, 0, 0 }, 150 },
    { { G4, G4, 0, 0 }, 150 }, { { C5, C5, 0, 0 }, 150 }, { { E5, E5, 0, 0 }, 150 }, { { C5, C5, 0, 0 }, 150 },
    { { G4, G4, 0, 0 }, 150 }, { { C5, C5, 0, 0 }, 150 }, { { E5, E5, 0, 0 }, 150 }, { { C5, C5, 0, 0 }, 150 },
    { { G4, G4, 0, 0 }, 150 }, { { C5, C5, 0, 0 }, 150 }, { { E5, E5, 0, 0 }, 450 },
};

/* happy birthday, the first two lines */
static const struct tune_step happy_birthday[] = {
    { { G4, G4, 0, C3 }, 200 }, { { G4, G4, 0, 0 }, 100 }, { { A4, A4, F4, F3 }, 300 }, { { G4, G4, E4, C3 }, 300 }, { { C5, C5, E4, 0 }, 300 }, { { B4, B4, D4, G3 }, 600 },
    { { G4, G4, 0, C3 }, 200 }, { { G4, G4, 0, 0 }, 100 }, { { A4, A4, F4, F3 }, 300 }, { { G4, G4, E4, C3 }, 300 }, { { D5, D5, F4, G3 }, 300 }, { { C5, C5, E4, C3 }, 600 },
};

/* effects: a laser (fast downward sweep), a two-tone siren, droid chirps, and SOS */
static const struct tune_step laser[] = {
    { { 2400, 2400, 2400, 2400 }, 30 }, { { 1900, 1900, 1900, 1900 }, 30 }, { { 1500, 1500, 1500, 1500 }, 30 }, { { 1200, 1200, 1200, 1200 }, 30 },
    { { 950, 950, 950, 950 }, 30 }, { { 750, 750, 750, 750 }, 30 }, { { 600, 600, 600, 600 }, 30 }, { { 480, 480, 480, 480 }, 40 }, { { 380, 380, 380, 380 }, 60 },
};
static const struct tune_step siren[] = {
    { { 600, 600, 600, 600 }, 300 }, { { 800, 800, 800, 800 }, 300 }, { { 600, 600, 600, 600 }, 300 }, { { 800, 800, 800, 800 }, 300 },
    { { 600, 600, 600, 600 }, 300 }, { { 800, 800, 800, 800 }, 300 },
};
static const struct tune_step chirps[] = {
    { { 1800, 0, 0, 0 }, 60 }, { { 0, 2400, 0, 0 }, 50 }, { { 0, 0, 1200, 0 }, 80 }, { { 0, 0, 0, 3000 }, 40 },
    { { 2200, 0, 1600, 0 }, 70 }, { { 0, 900, 0, 0 }, 120 }, { { 2800, 0, 0, 0 }, 40 }, { { 0, 0, 0, 1400 }, 90 },
    { { 0, 2000, 0, 0 }, 60 }, { { 3200, 0, 0, 0 }, 40 }, { { 0, 0, 1000, 0 }, 150 }, { { 0, 0, 0, 2600 }, 50 },
    { { 1500, 1500, 0, 0 }, 100 }, { { 0, 0, 2200, 2200 }, 60 }, { { 700, 0, 0, 0 }, 200 },
};
static const struct tune_step sos[] = {
    { { 880, 880, 880, 880 }, 120 }, { { 0, 0, 0, 0 }, 120 }, { { 880, 880, 880, 880 }, 120 }, { { 0, 0, 0, 0 }, 120 }, { { 880, 880, 880, 880 }, 120 }, { { 0, 0, 0, 0 }, 360 },
    { { 880, 880, 880, 880 }, 360 }, { { 0, 0, 0, 0 }, 120 }, { { 880, 880, 880, 880 }, 360 }, { { 0, 0, 0, 0 }, 120 }, { { 880, 880, 880, 880 }, 360 }, { { 0, 0, 0, 0 }, 360 },
    { { 880, 880, 880, 880 }, 120 }, { { 0, 0, 0, 0 }, 120 }, { { 880, 880, 880, 880 }, 120 }, { { 0, 0, 0, 0 }, 120 }, { { 880, 880, 880, 880 }, 120 },
};

/* Shche ne vmerla Ukrainy (Verbytsky, 1863): the opening phrase, from the
 * RTTTL "UAAnthem:b=150,o=5,d=4:e,8e,8e,8d,8e,8f,g,8f,e,d,c,e,b4,e,a4,a4" */
static const struct tune_step ua_anthem[] = {
    { { 659, 659, 523, 220 }, 400 },
    { { 659, 659, 523, 220 }, 200 },
    { { 659, 659, 523, 220 }, 200 },
    { { 587, 587, 494, 220 }, 200 },
    { { 659, 659, 523, 220 }, 200 },
    { { 698, 698, 523, 175 }, 200 },
    { { 784, 784, 659, 262 }, 400 },
    { { 698, 698, 523, 175 }, 200 },
    { { 659, 659, 523, 220 }, 400 },
    { { 587, 587, 494, 220 }, 400 },
    { { 523, 523, 440, 262 }, 400 },
    { { 659, 659, 523, 220 }, 400 },
    { { 494, 494, 392, 165 }, 400 },
    { { 659, 659, 523, 220 }, 400 },
    { { 440, 440, 349, 220 }, 400 },
    { { 440, 440, 349, 220 }, 400 },
};

/* the boogie riff (Thorogood, 1982): a slow shuffle in G, the stop-time
 * figure "dun dun dun da-DUN". Up an octave from the record, because a motor
 * cannot voice a low G, with a single thump under the first hit of each
 * group; the hits are swung (long, then the hammer-on short) */
static const struct tune_step bad_to_the_bone[] = {
    { { G4, G4, 0, G3 }, 360 }, { { 0, 0, 0, 0 }, 140 },
    { { G4, G4, 0, 0 }, 360 }, { { 0, 0, 0, 0 }, 140 },
    { { G4, G4, 0, 0 }, 360 }, { { 0, 0, 0, 0 }, 60 },
    { { Bb4, Bb4, 0, 0 }, 160 }, { { G4, G4, 0, G3 }, 520 }, { { 0, 0, 0, 0 }, 420 },
    { { G4, G4, 0, G3 }, 360 }, { { 0, 0, 0, 0 }, 140 },
    { { G4, G4, 0, 0 }, 360 }, { { 0, 0, 0, 0 }, 140 },
    { { G4, G4, 0, 0 }, 360 }, { { 0, 0, 0, 0 }, 60 },
    { { Bb4, Bb4, 0, 0 }, 160 }, { { C5, C5, 0, 0 }, 160 }, { { Bb4, Bb4, 0, 0 }, 160 }, { { G4, G4, 0, G3 }, 700 },
};

/* the national anthem, the first line (Smith, c. 1775; public domain):
 * melody doubled, thirds under it, roots in the bass */
static const struct tune_step star_spangled[] = {
    { { G4, G4, E4, C3 }, 300 }, { { E4, E4, C4, 0 }, 100 }, { { C4, C4, G3, C3 }, 400 }, { { E4, E4, C4, 0 }, 400 }, { { G4, G4, E4, C3 }, 400 },
    { { C5, C5, E4, C3 }, 800 }, { { E5, E5, G4, C3 }, 300 }, { { D5, D5, G4, 0 }, 100 }, { { C5, C5, E4, C3 }, 400 },
    { { E4, E4, C4, 0 }, 400 }, { { Gb4, Gb4, D4, D3 }, 400 }, { { G4, G4, D4, G3 }, 800 },
};

static const struct tune tunes[] = {
    { "None",          0,              0 },
    { "ImperialMarch", imperial_march, sizeof(imperial_march) / sizeof(imperial_march[0]) },
    { "Beethoven5th",  beethoven5,     sizeof(beethoven5) / sizeof(beethoven5[0]) },
    { "OdeToJoy",      ode_to_joy,     sizeof(ode_to_joy) / sizeof(ode_to_joy[0]) },
    { "Korobeiniki",   korobeiniki,    sizeof(korobeiniki) / sizeof(korobeiniki[0]) },
    { "Charge",        charge,         sizeof(charge) / sizeof(charge[0]) },
    { "AxelF",         axel_f,         sizeof(axel_f) / sizeof(axel_f[0]) },
    { "EyeOfTheTiger", eye_of_the_tiger, sizeof(eye_of_the_tiger) / sizeof(eye_of_the_tiger[0]) },
    { "FurElise",      fur_elise,      sizeof(fur_elise) / sizeof(fur_elise[0]) },
    { "MountainKing",  mountain_king,  sizeof(mountain_king) / sizeof(mountain_king[0]) },
    { "GranVals",      gran_vals,      sizeof(gran_vals) / sizeof(gran_vals[0]) },
    { "Valkyries",     valkyries,      sizeof(valkyries) / sizeof(valkyries[0]) },
    { "ShaveAndAHaircut", shave_haircut, sizeof(shave_haircut) / sizeof(shave_haircut[0]) },
    { "Reveille",      reveille,       sizeof(reveille) / sizeof(reveille[0]) },
    { "HappyBirthday", happy_birthday, sizeof(happy_birthday) / sizeof(happy_birthday[0]) },
    { "Laser",         laser,          sizeof(laser) / sizeof(laser[0]) },
    { "Siren",         siren,          sizeof(siren) / sizeof(siren[0]) },
    { "Chirps",        chirps,         sizeof(chirps) / sizeof(chirps[0]) },
    { "SOS",           sos,            sizeof(sos) / sizeof(sos[0]) },
    { "UAAnthem",      ua_anthem,      sizeof(ua_anthem) / sizeof(ua_anthem[0]) },
    { "BadToTheBone",  bad_to_the_bone, sizeof(bad_to_the_bone) / sizeof(bad_to_the_bone[0]) },
    { "StarSpangledBanner", star_spangled, sizeof(star_spangled) / sizeof(star_spangled[0]) },
};

const struct tune *tune_get(uint8_t id)
{
    if (id == 0 || id >= sizeof(tunes) / sizeof(tunes[0]) || !tunes[id].steps) {
        return 0;
    }
    return &tunes[id];
}
