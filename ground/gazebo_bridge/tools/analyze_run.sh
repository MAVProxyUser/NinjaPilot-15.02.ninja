#!/usr/bin/env bash
# Full per-run analysis: BOARD log (flight controller), BRIDGE log (ground
# truth + harness), and GAZEBO state. Run this after EVERY flight - a score
# without the board log cannot tell controller error from estimator error.
#   usage: tools/analyze_run.sh <label> <bridge.log>
set -u
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PY="$HERE/../venv/bin/python3"
LABEL="$1"; BRIDGE="$2"
OUT="${TMPDIR:-/tmp}/${LABEL}_flash.jsonl"

echo "=== $LABEL ==="
echo "--- bridge log: outcome + harness ---"
grep -E "PASS|FAIL|flying AWAY|tilt-over|ground contact|ceiling" "$BRIDGE" | tail -3

echo "--- board log: decode from the FC's own flash ---"
"$PY" "$HERE/decode_fcwd.py" "$HOME/ninjapilot-build/fcwd" "$OUT" | tail -1

echo "--- score (flown vs planned, dense board samples) ---"
"$PY" "$HERE/score.py" "$LABEL" "$OUT"

echo "--- oscillation (is it porpoising/hunting, and at what frequency) ---"
"$PY" "$HERE/porpoise.py" "$OUT" 2>/dev/null | sed -n '1,7p'

echo "--- estimator health: filtered position vs its own GPS input ---"
"$PY" - "$OUT" <<'PYEOF'
import json, sys, math, bisect
recs=[json.loads(l) for l in open(sys.argv[1])]
HOME_LAT, HOME_LON, R = 37.7749, -122.4194, 6378137.0
gps=[]; pos=[]
for r in recs:
    if r.get('object')=='GPSPositionSensor':
        d=r['data']
        gps.append((r['t_us']/1e6,
                    math.radians(d['Latitude']/1e7-HOME_LAT)*R,
                    math.radians(d['Longitude']/1e7-HOME_LON)*R*math.cos(math.radians(HOME_LAT))))
    elif r.get('object')=='PositionState':
        pos.append((r['t_us']/1e6, r['data']['North'], r['data']['East']))
if gps and pos:
    pt=[p[0] for p in pos]; offs=[]
    for t,gn,ge in gps:
        i=bisect.bisect_left(pt,t); c=[j for j in (i-1,i) if 0<=j<len(pos)]
        if not c: continue
        j=min(c,key=lambda j:abs(pos[j][0]-t))
        if abs(pos[j][0]-t)<=0.6: offs.append(math.hypot(pos[j][1]-gn,pos[j][2]-ge))
    if offs:
        print("  filter vs GPS: mean %.3f m  max %.3f m -> %s" % (
            sum(offs)/len(offs), max(offs),
            "estimator OK, error is CONTROLLER" if sum(offs)/len(offs) < 0.15 else "ESTIMATOR SUSPECT"))
else:
    print("  (no GPS/position pairs)")
PYEOF

echo "--- gazebo: truth vs board (do they agree?) ---"
"$PY" - "$BRIDGE" "$OUT" <<'PYEOF'
import json, re, sys, math
tr=[]
for line in open(sys.argv[1]):
    m=re.search(r"t\+(\d+)s alt=([-\d.]+)m N=([-\d.]+) E=([-\d.]+)", line)
    if m: tr.append((float(m[2]), float(m[3]), float(m[4])))
recs=[json.loads(l) for l in open(sys.argv[2])]
fc=[(-r['data']['Down'], r['data']['North'], r['data']['East']) for r in recs if r.get('object')=='PositionState']
if tr and fc:
    print("  gazebo truth: %d samples, alt %.2f-%.2f m" % (len(tr), min(t[0] for t in tr), max(t[0] for t in tr)))
    print("  board   est : %d samples, alt %.2f-%.2f m" % (len(fc), min(f[0] for f in fc), max(f[0] for f in fc)))
PYEOF
