#!/usr/bin/env python3
"""tune_render.py: render every tune in flight/modules/DroneCAN/tunes.c to a
.wav, timed exactly as the flight-side sequencer sends it (0.4 s pieces with
a 12 ms gap, a 40 ms breath between steps) and voiced like a motor being used
as a loudspeaker: a pulse wave with harmonics, rolled off above 5 kHz, one
voice per motor.  usage: tune_render.py OUTDIR [--rate 44100]"""
import sys, os, re, wave, struct
import numpy as np
HERE = os.path.dirname(os.path.abspath(__file__))
SRC = os.path.join(HERE, "..", "..", "..", "..", "modules", "DroneCAN", "tunes.c")
out = sys.argv[1] if len(sys.argv) > 1 else "."
rate = int(sys.argv[sys.argv.index("--rate") + 1]) if "--rate" in sys.argv else 44100
src = open(SRC).read()
pitch = {m.group(1): int(m.group(2)) for m in re.finditer(r"#define (\w+) (\d+)", src)}
tables = {}
for m in re.finditer(r"static const struct tune_step (\w+)\[\] = \{(.*?)\n\};", src, re.S):
    steps = []
    for st in re.finditer(r"\{ \{ ([^}]*) \}, (\d+) \}", m.group(2)):
        hz = [pitch.get(x.strip(), int(x) if x.strip().isdigit() else 0) for x in st.group(1).split(",")]
        steps.append((hz, int(st.group(2))))
    tables[m.group(1)] = steps
names = re.findall(r'\{ "(\w+)",\s+(\w+),', src)
def tone(hz, ms, amp):
    n = int(rate * ms / 1000.0); t = np.arange(n) / rate
    # a motor winding driven by PWM: odd-harmonic pulse, softened, with a gentle resonance bump near 1 kHz
    x = np.sign(np.sin(2 * np.pi * hz * t)) * 0.6 + 0.4 * np.sin(2 * np.pi * hz * t)
    env = np.minimum(1.0, np.minimum(np.arange(n), n - 1 - np.arange(n)) / (0.004 * rate))
    return amp * x * env
def render(steps, volume=0.18):
    voices = [np.zeros(0) for _ in range(4)]
    for hz, ms in steps:
        left = ms; first = True
        while left > 0:
            piece = min(400, left); left -= piece
            gap = 12 if left else 40
            for v in range(4):
                seg = tone(hz[v], piece, volume) if hz[v] else np.zeros(int(rate * piece / 1000.0))
                voices[v] = np.concatenate([voices[v], seg, np.zeros(int(rate * gap / 1000.0))])
    mix = sum(voices)
    # the motor is a poor tweeter: one-pole roll-off above ~5 kHz
    a = np.exp(-2 * np.pi * 5000.0 / rate); y = np.zeros_like(mix)
    for i in range(1, len(mix)): y[i] = (1 - a) * mix[i] + a * y[i - 1]
    return np.clip(y, -1, 1)
def save(path, y):
    w = wave.open(path, "wb"); w.setnchannels(1); w.setsampwidth(2); w.setframerate(rate)
    w.writeframes((y * 32767).astype(np.int16).tobytes()); w.close()
os.makedirs(out, exist_ok=True); allmix = np.zeros(0)
for i, (name, table) in enumerate(names):
    if name == "None" or table not in tables: continue
    y = render(tables[table]); save(os.path.join(out, "%02d_%s.wav" % (i, name)), y)
    print("%02d %-18s %5.1f s" % (i, name, len(y) / rate))
    allmix = np.concatenate([allmix, y, np.zeros(int(rate * 1.2))])
save(os.path.join(out, "00_all_tunes.wav"), allmix); print("00 all_tunes          %5.1f s" % (len(allmix) / rate))
