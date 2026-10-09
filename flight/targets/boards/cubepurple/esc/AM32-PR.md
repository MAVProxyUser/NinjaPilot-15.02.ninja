# DroneCAN: play notes on the motor from the bus (BeepCommand, and a per-motor Note)

Pull request against `am32-firmware/AM32`, from tag `v2.20`. Five small commits,
all in `Src/DroneCAN/DroneCAN.c`, `Src/main.c`, `Inc/sounds.h`. Tested on four
Vimdrones S50 (`VIMDRONES_S50_L431_CAN`) driven by a Cube Purple flight
controller over CAN, including updating the ESCs over CAN with the result.

## Summary

A flight controller can now make an AM32 CAN ESC play a note on its motor by
sending a message, the same way it already asks for throttle. Two messages:

* `uavcan.equipment.indication.BeepCommand` (standard, id 1080): one note,
  every ESC on the bus plays it.
* `com.ninjapilot.esc.Note` (vendor id 20400): one note for the ESCs named in
  a mask, with a loudness. Four motors can hold four different pitches.

The ESC plays a note the way it already plays its own beacon tunes: motor
stopped, input below the dead band, interrupts masked, watchdog reloaded.
Nothing is written to EEPROM, the startup melody is untouched, and a note can
never reach a turning motor. The ESC keeps no tune: it plays one note per
command and forgets it. Melodies, arming sounds, status chirps and the like
are the sender's business, which keeps the ESC side tiny (about 90 lines).

## Why

AM32 has a customisable *startup* melody and fixed beacon tones, but no way
for the controller to sound the motors at a moment of its choosing: on
arming, on a GPS fix, on a fault, for a lost-model beacon that is not
DShot's, or just for fun. BeepCommand is the standard DroneCAN message for
exactly this and other ESC firmwares answer it; AM32 ignored it. The
per-motor message is the small extra that turns four ESCs into four voices.

## Message formats

### `uavcan.equipment.indication.BeepCommand` (1080, standard)

| field       | type    | meaning                      |
|-------------|---------|------------------------------|
| `frequency` | float16 | hertz                        |
| `duration`  | float16 | seconds                      |

Broadcast; every ESC that hears it plays it. Single CAN frame.

### `com.ninjapilot.esc.Note` (20400, vendor range)

| field       | type    | meaning                                                  |
|-------------|---------|----------------------------------------------------------|
| `mask`      | uint8   | bit *i* set = the ESC whose `ESC_INDEX` is *i* plays it   |
| `volume`    | uint8   | 0..11 as `BEEP_VOLUME`, for this note only; 255 = keep   |
| `frequency` | float16 | hertz                                                    |
| `duration`  | float16 | seconds                                                  |

Broadcast, 6 bytes, single CAN frame. Data type signature
`0x4E494E4A41504931`. ESCs with an index outside the mask ignore it. The
volume is applied for the note and the ESC's own `BEEP_VOLUME` is restored
afterwards.

## What the ESC does with a note

1. Accepts it only if `100 Hz <= frequency <= 5000 Hz` and `duration > 0`;
   anything else is ignored. Duration is capped at **0.4 s**.
2. Plays it only when the motor is **not running** and the input is **below
   the dead band**. A note that arrives while the motor turns is dropped,
   not deferred: it will never fire later when the motor stops.
3. While the note sounds, interrupts are masked (as in `playBeaconTune3()`
   and `playStartupTune()`); `tenKhzRoutine()` would otherwise rewrite the
   duty cycle every 100 µs and cut the note to a click. The watchdog is
   reloaded before and after, and `signaltimeout` is cleared after, so the
   armed signal watchdog (0.5 s) cannot trip: 0.4 s is the cap for that
   reason.
4. Pitch is corrected for `playBJNote()`: it runs TIM1 at prescaler 10 (clock
   divided by 11) but sizes the period for clock divided by 10, so it sounds
   10/11 of what it is asked. The BlueJay melody path hides the same factor
   in its 11 MHz constant. The handler asks for 11/10 and the note comes out
   at the frequency on the wire, within a percent.

## Limits and timing rules for senders

* **One note at a time per ESC.** During a note the ESC processes nothing:
  no CAN, no throttle, no telemetry. Send the next command after the
  previous duration plus about 12 ms; a command that arrives mid-note is
  lost (the CAN receive FIFO is three frames deep and the throttle stream
  fills it).
* **Per command: 0.4 s maximum.** Longer notes are chained by the sender,
  back to back, same pitch.
* **Rests** are simply gaps with no command.
* **Frequency**: 100 to 5000 Hz accepted. Below about 150 Hz the motor is a
  poor loudspeaker; above 3 kHz loudness falls off and older ears give up
  (listening test on the bench: 100 Hz to 4.5 kHz in half octaves, all
  audible, the top step faint).
* **Loudness**: `BEEP_VOLUME` scale, 0..11. Do not go beyond it; it is a duty
  cycle into a stalled winding.
* **Tune length**: the ESC has no opinion, the sender does. Keep a tune to
  60 s or less and leave the motor cool between tunes; each note pushes a
  little current through the windings with no airflow.
* **Throttle wins.** Because notes never play on a running motor, a pilot
  who opens the throttle mid-tune gets thrust immediately and silence from
  then on. Senders should not assume a tune finished.

## Tone format on the sender side (reference implementation)

The reference sender is the NinjaPilot flight firmware for the Cube
(`flight/modules/DroneCAN/tunes.c`): a tune is a list of steps, each step a
pitch per voice (0 = that voice rests) and a duration in milliseconds. Four
voices map onto `ESC_INDEX` 0..3. Steps longer than 0.4 s are chained; a 40 ms
breath separates steps, 12 ms separates chained pieces. In "all together"
mode only voice 0 is sent, as BeepCommand, so stock-standard ESCs join in.

```c
struct tune_step { uint16_t hz[4]; uint16_t ms; };
/* G major chord for 300 ms, then voice 3 alone, then a rest */
{ { 392, 494, 587, 196 }, 300 },
{ {   0,   0,   0, 196 }, 150 },
{ {   0,   0,   0,   0 }, 100 },
```

## Example tones included

Opening motifs only, a few seconds each, written as note tables by us:

* Beethoven, Symphony No. 5, opening (1808; public domain).
* Beethoven, "Ode to Joy" theme (1824; public domain).
* "Korobeiniki", Russian folk song (19th century; public domain).
* "Charge!", the ballpark fanfare (traditional bugle figure).
* "The Imperial March" (Williams, 1980): the nine-note opening figure.

## On copyright and the note tables

This PR ships no audio. It ships short tables of frequencies and durations
that we typed in, which a motor turns into a buzz. Still, a melody is a
musical work, so, for the record:

* Works first published in the United States before 1930 are in the public
  domain there as of 2025 (95 years after publication); the Beethoven, folk
  and bugle material above is centuries older than that. Cornell keeps the
  reference table: <https://guides.library.cornell.edu/copyright/publicdomain>.
  A composition and a *recording* of it are separate works: a public-domain
  symphony does not make a 1990 recording of it free, and vice versa.
* The one in-copyright item, the march, is a nine-note quotation of its
  opening figure, re-rendered as timer values for a motor, non-commercial,
  and no substitute for the work. Those are the fair-use factors (purpose and
  character, nature, amount, market effect), see the Copyright Office's FAQ:
  <https://www.copyright.gov/help/faq/faq-fairuse.html> and its index of
  decisions: <https://www.copyright.gov/fair-use/>. Fair use is decided case
  by case; nothing here is legal advice, and a maintainer who would rather
  not carry that table can drop it without touching the code.
* **There is no "30-second rule"**, and never was. The Copyright Office is
  explicit that no amount of a work is automatically safe to take; Stanford's
  fair-use guide says the same: <https://fairuse.stanford.edu/overview/fair-use/four-factors/>.
  The amount used is one factor among four.

## Changes, commit by commit

1. **BeepCommand accepted, decoded, played.** `shouldAcceptTransfer()` and
   `onTransferReceived()` gain the 1080 case; the decoder is 12 lines of
   libcanard scalar reads into a pending (hz, ms); `main.c` plays it where
   the beacon tones are played. `playBJNote()` is declared in `sounds.h`.
2. **Interrupts masked around the note.** Without this every note was one
   click: `tenKhzRoutine()` zeroes the duty cycle 10 000 times a second while
   the motor is stopped.
3. **True pitch.** The 11/10 correction described above.
4. **`com.ninjapilot.esc.Note`.** Mask, volume, pitch, duration; the volume
   set for the note and restored.
5. **Drop, never defer.** A note that arrives while the motor runs is
   discarded.

## Testing

* Four Vimdrones S50, AM32 v2.20 plus this branch, updated over CAN through
  the standard DroneCAN firmware-update path (BeginFirmwareUpdate, then
  `file.Read` served by the flight controller), all four back within a
  second of the last block.
* Single notes, four-note figures, chained notes, chords (four pitches on
  four motors), a volume ramp 1..11, formant-style triads, and arming and
  disarming tunes from the flight controller, all audible and at pitch. A
  throttle opened during a tune spins the motors at once.
* Telemetry (`esc.Status`) keeps flowing between notes; no watchdog resets,
  no error counts, no bus errors across hours of bench use.

## Not in this PR

A tune format inside the ESC. We thought about it and kept it out: the ESC
has no spare flash to speak of, the controller already knows the time and
the occasion, and one note per message is enough to do anything, including
four-part arrangements. If the project wants an ESC-resident tune later,
`STARTUP_TUNE`'s BlueJay layout is the obvious container.
