#!/usr/bin/env python3
"""esc_tune.py: play a tune on the DroneCAN ESCs, one DroneCANBeep write per
note (uavcan.equipment.indication.BeepCommand on the bus).  The ESC firmware
plays a note for at most 400 ms, so longer notes are chained back to back.
usage: esc_tune.py TUNE [--tempo 1.0] [--pitch 1.0] [--gap 30]
       esc_tune.py --rtttl "name:b=150,o=5,d=4:e,8e,8e,8d,..."   any ringtone-text tune
  TUNE: march | fifth | ode | korobeiniki | charge | sweep | scale
  --pitch  multiplies every frequency (to trim the ESC's timer rounding)
  --gap    silence between notes in ms (the ESC adds its own re-arm time)
  sweep plays 100 Hz to 5 kHz in half-octave steps, announcing each, for a
  listening test of what the motors can actually voice."""
import sys, os, time
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from hidlink import open_client
import uavtalk

def opt(name, default):
    return type(default)(sys.argv[sys.argv.index(name) + 1]) if name in sys.argv else default
tempo = opt("--tempo", 1.0); pitch = opt("--pitch", 1.0); gap = opt("--gap", 30)
C4, D4, Eb4, E4, F4, Gb4, G4, A4, Bb4, B4 = 262, 294, 311, 330, 349, 370, 392, 440, 466, 494
C5, D5, Eb5, E5, F5, G5 = 523, 587, 622, 659, 698, 784
TUNES = {
    # opening motif only: a quotation, not the piece
    "march":       [(G4, 320), (G4, 320), (G4, 320), (Eb4, 240), (Bb4, 80), (G4, 320), (Eb4, 240), (Bb4, 80), (G4, 640)],
    "fifth":       [(G4, 150), (G4, 150), (G4, 150), (Eb4, 700), (0, 200), (F4, 150), (F4, 150), (F4, 150), (D4, 900)],
    "ode":         [(E4, 300), (E4, 300), (F4, 300), (G4, 300), (G4, 300), (F4, 300), (E4, 300), (D4, 300), (C4, 300), (C4, 300), (D4, 300), (E4, 300), (E4, 450), (D4, 150), (D4, 600)],
    "korobeiniki": [(E5, 250), (B4, 125), (C5, 125), (D5, 250), (C5, 125), (B4, 125), (A4, 250), (A4, 125), (C5, 125), (E5, 250), (D5, 125), (C5, 125), (B4, 375), (C5, 125), (D5, 250), (E5, 250), (C5, 250), (A4, 250), (A4, 500)],
    "charge":      [(G4, 130), (C5, 130), (E5, 130), (G5, 260), (E5, 130), (G5, 600)],
    "scale":       [(f, 300) for f in (C4, D4, E4, F4, G4, A4, B4, C5)],
    "sweep":       [(int(100 * 2 ** (i / 2)), 500) for i in range(12)],   # 100 Hz .. 4.5 kHz
}
def rtttl(text):
    """RTTTL (ringtone text) -> [(hz, ms)]: 'name:b=bpm,o=octave,d=length:notes'"""
    import re
    name, defaults, notes = text.split(":"); d = dict(kv.split("=") for kv in defaults.split(","))
    bpm, octv, dlen = int(d.get("b", 63)), int(d.get("o", 6)), int(d.get("d", 4))
    semis = {"c": 0, "c#": 1, "d": 2, "d#": 3, "e": 4, "f": 5, "f#": 6, "g": 7, "g#": 8, "a": 9, "a#": 10, "b": 11, "p": None}
    out = []
    for tok in notes.split(","):
        m = re.match(r"(\d*)([a-gp]#?)(\.?)(\d?)(\.?)", tok.strip().lower()); ln = int(m.group(1) or dlen); n = m.group(2); dot = "." in (m.group(3) + m.group(5)); o = int(m.group(4) or octv)
        ms = int(round(60000.0 / bpm * 4 / ln * (1.5 if dot else 1)))
        hz = 0 if semis[n] is None else int(round(440.0 * 2 ** ((semis[n] - 9) / 12.0 + (o - 4))))
        out.append((hz, ms))
    return name, out
if "--rtttl" in sys.argv:
    name, TUNES[name] = rtttl(sys.argv[sys.argv.index("--rtttl") + 1])
else:
    name = next((a for a in sys.argv[1:] if a in TUNES), None)
if not name: print(__doc__); sys.exit(1)
client = open_client(); st = {}
def grab(od, inst, d): st[od.name] = d
client.run(duration=1.5, on_object=grab)
print("%s: %s, %d notes, tempo x%.2f, pitch x%.3f" % (time.strftime("%H:%M:%S"), name, len(TUNES[name]), tempo, pitch))
for hz, ms in TUNES[name]:
    ms = int(ms / tempo)
    if hz == 0:
        client.run(duration=ms / 1000.0, on_object=grab); continue
    f = int(round(hz * pitch))
    if name == "sweep": print("   %5d Hz" % f, flush=True)
    left = ms
    while left > 0:                                   # the ESC plays at most 400 ms per command
        piece = min(400, left); left -= piece
        client.send_object("DroneCANBeep", {"Frequency": f, "Duration": piece, "Sent": 0})
        client.run(duration=piece / 1000.0 + 0.012, on_object=grab)   # the note, plus the ESC's turnaround
    client.run(duration=gap / 1000.0, on_object=grab)
print("%s: done" % time.strftime("%H:%M:%S"))
