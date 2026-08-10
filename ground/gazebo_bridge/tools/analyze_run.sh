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
# NOT `| tail -1`: that swallowed the "flights present" line and the
# stale-merge/timestamp warnings, which is how a contaminated decode
# reached the analysis unnoticed.
"$PY" "$HERE/decode_fcwd.py" "$HOME/ninjapilot-build/fcwd" "$OUT"

# Before trusting ANY score: is the shape we are grading against the shape the
# vehicle was actually given? PathDesired is logged on change, so this is
# checkable rather than assumed.
echo "--- plan: what the follower was actually given ---"
"$PY" "$HERE/plan_check.py" "$OUT"

echo "--- score (flown vs planned, dense board samples) ---"
"$PY" "$HERE/score.py" "$LABEL" "$OUT"

# Cross-track answers "were the legs straight", which is NOT the same question
# as "did we actually touch the corners" - a run can score beautiful legs and
# still cut every waypoint by a metre.
echo "--- waypoint arrival (did it actually get ON the point, and stop there) ---"
"$PY" "$HERE/wp_arrival.py" "$OUT" 2>/dev/null

# Distinguishes a path layer that COMMANDS an orbit from a vehicle that fails
# to fly a clean command. Needs VelocityDesired in the log.
echo "--- corner: is the orbit commanded, or flown? ---"
"$PY" "$HERE/corner_probe.py" "$OUT" 2>/dev/null

echo "--- oscillation (is it porpoising/hunting, and at what frequency) ---"
"$PY" "$HERE/porpoise.py" "$OUT" 2>/dev/null | sed -n '1,7p'

echo "--- yaw: tracking error vs the bearing it was told to hold ---"
HERE="$HERE" "$PY" - "$OUT" <<'PYEOF2'
import json, sys, math
recs=[json.loads(l) for l in open(sys.argv[1])]
t0=recs[0]["t_us"]/1e6
att=[(r["t_us"]/1e6-t0, r["data"]["Yaw"]) for r in recs if r.get("object")=="AttitudeState"]
pos=[(r["t_us"]/1e6-t0, r["data"]["North"], r["data"]["East"]) for r in recs if r.get("object")=="PositionState"]
pos.sort()
def dist_to(t, tgt):
    # nearest position sample to time t, distance to tgt
    best=None; bd=1e9
    for (tp,n,e) in pos:
        d=abs(tp-t)
        if d<bd: bd=d; best=(n,e)
        elif tp>t+1.0: break
    return math.hypot(best[0]-tgt[0], best[1]-tgt[1]) if best else 1e9
wpa=[(r["t_us"]/1e6-t0, r["data"]["Index"]) for r in recs if r.get("object")=="WaypointActive"]
att.sort(); wpa.sort()
import os
sys.path.insert(0, os.environ["HERE"])
from star_geom import ORDER as STAR
allerr=[]
for i,(t,idx) in enumerate(wpa):
    if idx<1 or idx>len(STAR)-1: continue
    tend = wpa[i+1][0] if i+1<len(wpa) else (att[-1][0] if att else t)
    a,b = STAR[idx-1], STAR[idx]
    if math.hypot(b[0]-a[0], b[1]-a[1]) < 0.5: continue
    bearing = math.degrees(math.atan2(b[1]-a[1], b[0]-a[0]))
    # Measure only the SETTLED middle of the leg. Both ends are commanded
    # turns, not tracking error: the first 5s is the nose coming round onto
    # this leg, and the last stretch is the deliberate pre-turn onto the NEXT
    # leg (PRETURN_DIST in vtolflycontroller), which is a feature. Counting
    # either as error made this number meaningless - it read 66deg on a run
    # whose legs were visibly straight.
    errs=[abs((y-bearing+180)%360-180) for (ta,y) in att
          if t+5.0 <= ta <= tend and dist_to(ta, b) > 3.0]
    allerr += errs
if allerr:
    print("  settled on-leg yaw error: mean %.2f deg  max %.2f deg" % (
        sum(allerr)/len(allerr), max(allerr)))
    print("  (raw yaw RMS above includes the commanded 144deg corner turns)")
else:
    print("  (no settled leg samples)")
PYEOF2

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

echo "--- gazebo SERVER log: physics/plugin complaints ---"
GZLOG="${GZLOG:-/tmp/gzserver.log}"
if [ -f "$GZLOG" ]; then
  if grep -iE "error|warn|unable|fail|dropped|violat" "$GZLOG" | grep -viE "deprecat" | tail -5; then :; fi
  grep -ciE "error|warn|unable|fail" "$GZLOG" | xargs echo "  total complaint lines:"
else
  echo "  (no server log at $GZLOG - set GZLOG=<path>)"
fi

# The picture is not optional. Numbers say how far off; the plot says
# WHERE and in what shape - a rounded corner, a wavy leg and an altitude
# sag all score similarly but look nothing alike.
echo "--- planned vs flown + altitude profile ---"
PNG="${PNG_OUT:-${TMPDIR:-/tmp}/${LABEL}.png}"
if "$PY" "$HERE/star_plot.py" "$OUT" "$PNG" 2>/dev/null; then
  echo "  $PNG"
else
  echo "  (plot failed - is this a star mission?)"
fi

# A flight recorder that stops before the flight does is worth shouting about:
# it is exactly the run you most need it for. Two unexplained flyaways at wp3
# were both un-diagnosable because the board log ended before the event.
echo "--- recorder coverage: does the board log reach the end of the flight? ---"
"$PY" - "$BRIDGE" "$OUT" <<'PYEOFCOV'
import json, re, sys
last_t = 0.0
for line in open(sys.argv[1]):
    m = re.search(r"t\+(\d+)s ", line)
    if m:
        last_t = max(last_t, float(m.group(1)))
recs = [json.loads(l) for l in open(sys.argv[2])]
if recs and last_t:
    ts = [r["t_us"] / 1e6 for r in recs]
    span = max(ts) - min(ts)
    # the board log starts at arm, which precedes the bridge's t+0 by the
    # staging climb, so board span should EXCEED the mission clock.
    if span < last_t:
        print("  !!! BOARD LOG STOPS EARLY: %.1fs of recording for a flight that "
              "ran to t+%.0fs." % (span, last_t))
        print("      The FC's own record does not cover the end of this flight, so "
              "anything that happened there cannot be diagnosed from it.")
    else:
        print("  board log spans %.1fs, mission ran to t+%.0fs - covered" % (span, last_t))
PYEOFCOV

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
