# Working on this repo

## RULE: every flight is judged on THREE logs, never one

Every single run compares:

1. **the flight controller's own log** (simposix DebugLog) - what the FC
   believed and commanded
2. **the bridge log** - Gazebo ground truth and what the harness did
3. **the Gazebo server log** - physics/plugin complaints

`tools/analyze_run.sh` does all three and the bridge now runs it
automatically as each flight ends, so it cannot be skipped:

```bash
NINJAPILOT_BRIDGE_LOG=/tmp/star_NN.log NINJAPILOT_RUN_LABEL=starNN \
  NINJAPILOT_TEST_MODE=mission ./venv/bin/python3 gazebo_bridge.py
```

This is not ceremony. Judging a run on one log has produced wrong
conclusions repeatedly in this project:

- a phantom "0.4m estimator bias" that was a statistics artifact of
  comparing two different sample sets, and which sent tuning down a blind
  alley until the board log's GPS-vs-filtered pairing disproved it
- a "vertical channel destabilisation" blamed on a controller constant that
  was really tilt costing lift (and, for three runs, a second telemetry
  client stealing the bridge's packets)
- corner "control bugs" that were the harness starving the sensor thread

Truth says where it flew; the board log says what the FC believed; the
server log says whether the simulator itself was unhappy. Disagreement
between them IS the diagnosis.

Note the board log does NOT come over telemetry by default - on simposix
the same slots are files on disk and decode in ~0.2s (see SKILLS.md). The
telemetry path is real-hardware-only and is exercised on request.


This is `NinjaPilot-15.02.ninja`, an OpenPilot-derived flight controller
codebase (SimPosix SITL target + a Python UAVTalk/UAVObjects ground tool
under `ground/pyuavtalk/` and `ground/gazebo_bridge/`). Rules below exist
because they were each learned the hard way in earlier sessions - read
them before making changes, not after something breaks.

## SETTLED: the corner "cursive-l" - yawing while translating corrupts position (2026-08-09, late)

The user reported a left-handed loop at every star vertex, run after run,
while every corner of this star turns RIGHT. It took ~15 runs and three
successively broken metrics to isolate, and the user's eyeball was right at
every step where the metrics were wrong.

THE MECHANISM: UpdateStabilizationDesired converted NED commands to body
frame using CURRENT yaw. The attitude loop achieves a commanded tilt ~130ms
later (relay autotune: roll 113ms / pitch 155ms), by which time the corner
pre-turn has yawed the body ~4.6 deg further right - so the achieved thrust
vector is rotated clockwise of the intended one. While BRAKING (command
anti-parallel to travel) that rotation has an error component pointing LEFT
of travel. Integrated over a ~5s braking approach: ~0.5m of leftward arrival
drift, every corner, always the same side. Partially fixed with
predicted-yaw conversion (attitudeState.Yaw + gyro.z * lag); 0.13s and
0.26s both help but neither flips the drift sign, so the lag model is
INCOMPLETE - candidates for the residual: velocity-estimate frame lag, the
measured roll/pitch response asymmetry, model-level rotor effects. Do not
blind-tune further; instrument first.

THE ISOLATION (stop corners + instant release in all three, one variable):
    star132  yaw-following ON        xtrack 0.19 / 0.78m   +570deg left mills
    star133  yaw-following OFF       xtrack 0.06 / 0.19m   cleanest run of
                                     the project by 3x; corners are points
    star134  yaw ON + 0.13s comp     0.17 / 0.50m
    star135  yaw ON + 0.26s comp     0.14 / 0.45m (no sign flip -> stop)

CONSEQUENCE, now the default: PathFollower yaw stays in AxisLock
("manual"); NINJAPILOT_YAW_MODE=pathdirection opts back into nose-following
at a measured ~3x tracking cost. Corners are FULL STOPS with a 0.20m sphere,
0.9 confirm, 0.1s dwell, and the half-plane arrival as backstop - the
complete dataset says slow-at-vertex corners are clean while carry-through
corners flip a coin on turn direction.

DEAD ENDS with measured verdicts (do not retry without new information):
  - Arc-fillet corners via CircleRight + PointingTowardsNext (stock
    primitives, first-ever use): geometry at these corner angles forces
    radii needing 2-11 m/s^2 centripetal at real arrival speeds. star131:
    6.56m mean cross-track. Parked behind NINJAPILOT_STAR_ARCS=1.
  - Rotating the follower's along-track feed-forward into the turn: near
    the vertex it points down the NEXT leg while still on the current one.
    star126: 2.22m cross-track, ground contact.
  - Sweep corners (nonzero corner speed): 0-2/6 correct handedness across
    four configs; the direction is decided by which side of the vertex the
    vehicle happens to clip.

METRIC LESSONS (three broken in a row, documented in
tools/corner_handedness.py): a cross product computed in (North,East) order
is MIRRORED vs the plot (x=East, y=North) and inverts every verdict;
path-ratio metrics are confounded by arrival quality; leg-time windows miss
corners once waypoints release early. The working metric is vertex-centred
and time-clustered.

## INTERCEPT flight mode: hitting a moving target (2026-08-10)

A firmware flight mode that flies a lead solution onto a moving object and
makes contact. First confirmed strike: icpt04, 4.00g on the vehicle's own
IMU, closing speed collapsing 3.15 -> 0.98 m/s in one 50ms sample.

DIVISION OF LABOUR, deliberately: the bridge supplies ONLY the target's
position and velocity - what an external tracker or a second GPS would give
you. Every bit of guidance is in the firmware, because it has to run at the
follower rate, not at telemetry rate.

  PATHDESIRED_MODE_INTERCEPT -> path_intercept() in paths.c
  End                = target position NOW
  ModeParameters[1..3] = target velocity NED (slot 0 left unused - it aliases
                       GOTOENDPOINT_NEXTCOMMAND and once landed the aircraft)
  EndingVelocity     = our speed cap

BARRAGE, NOT CHASE. The framing came from Phalanx dispersion: a gun does not
hit a point, it lays a pattern, and the hit is the overlap of that pattern
with the target. For a SLOW interceptor the dominant miss is TIMING, not
bearing - closing at 2.2 m/s on a 1.2 m/s target, a solution perfect in
direction still misses entirely by arriving two seconds late. So when we can
reach the crossing point before the target does, path_intercept stops
chasing and settles onto that point, arriving early with zero closing
velocity and letting the target fly into the contact radius. That trades
"hit a moving point" - dominated by our own attitude lag, the equivalent of
the gun's barrel whip - for "hold a position", which this airframe does to
0.04-0.09m against a 0.58m contact window.

### The bugs, because every one of them was silent

- **Mode not in pathfollower.cpp's dispatch.** The switch maps PathDesired
  .Mode to a controller; Intercept was missing, so it fell to default,
  activeController stayed 0, and the vehicle HOVERED while PathDesired
  updates arrived and were discarded every tick. No error, no alarm. If a
  new path mode appears to do nothing, check this switch first.
- **correction_vector zeroed.** Reasoning "an intercept has no line to hold"
  is right horizontally and catastrophic vertically: correction_vector[2] is
  the ONLY vertical position feedback the follower gets. Without it the
  vertical channel ran on feed-forward alone and sagged 28cm below the
  target while still descending - a 25mm graze at 1.40g instead of a hit.
  Restoring it: 1.40g -> 4.00g.
- **Contact geometry from the wrong dimension.** The frame's box is
  0.47x0.47, so corner-on contact happens at the half-DIAGONAL: 0.25 (ball)
  + 0.332 = 0.582m centre-to-centre, not the 0.485 the half-width implies. A
  real collision scored as a miss.
- **20Hz collision sampling aliases.** Closing at 2-3 m/s, consecutive
  samples are 10-15cm apart and step over the minimum. Detect contact with
  the physics engine, and compute true closest approach in closed form
  between samples (tools/intercept_summary.py does).
- **gz-sim Contact must be a WORLD system plugin.** Declared on the model it
  loads silently and publishes nothing - no topic, no warning.
- **gz-transport discovery race.** advertise() then publish() 50ms later
  sends into the void; the VelocityControl plugin has not connected yet and
  the target just sits there while the log cheerfully reports it underway. A
  successful publish proves nothing about delivery.

### Airframe protection

The commanded velocity is SLEWED, never stepped: 60 deg/s on direction,
1.2 m/s^2 on magnitude. A tracker feeding a moving point at 10-20Hz jitters,
and steering straight off it commands acceleration steps the attitude loop
cannot follow - star126 is the precedent for what that does. The rate
limiter's statics persist across calls by design and therefore across
ENGAGEMENTS; path_intercept_reset() (called from VtolFlyController::Activate)
clears them so a new engagement does not resume slewing from wherever the
last one ended.

### Testing

`ground/gazebo_bridge/run_intercept.sh <label>` - the only supported way, for
the same reason run_star.sh is: it kills and WAITS, removes any leftover
target, RESETS THE SCENE, purges slots, flies, then plots. Launching by hand
skipped the reset once and left an armed vehicle chasing a stale PathDesired
- it drifted 190m and the next three runs started from that state.

tools/intercept_plot.py gives both tracks, altitude, and separation with the
IMU trace. It exists to separate the two failure modes that score
identically: a CROSS-TRACK miss (guidance aiming wrong) has a rounded
separation floor, a TIMING miss (aiming right, arriving late) has a sharp V.
tools/intercept_summary.py tabulates hit rate across runs and decomposes
each miss into horizontal and vertical - a scalar "0.31m" hid a 28cm
vertical error completely.

### The endgame miss is LAG, and the fix belongs in the estimator (2026-08-10)

On the clean (loop-unblocked) baseline the miss stopped being random and
became a signature: **0.57-0.59m directly BEHIND the ball, along its own
velocity vector, with ~0.15m cross-track**, repeatable to ~2cm. That is not
an aiming error. 0.58m / 1.2 m/s = **0.48s of pure time lag** through the
bridge loop, UAVTalk transport, and the ~130ms attitude response relay
autotune measured.

**Adding the lag as a CONSTANT to the firmware's endgame lead FAILED and must
not be retried.** `INTERCEPT_LAG_COMP_S 0.45f` gave first-pass misses of
1.25m, 1.30m and 1.32m against the 0.57-0.59m it was meant to close - more
than twice as bad. The mechanism: the endgame lead is already range-dependent
(`range/vmax`), so a constant on top of it over-leads hardest exactly when
range is collapsing and a moving aim point is least affordable. This is the
same lesson as the earlier `x1.35` lead experiment (0.87m vs 0.59m) - the
endgame lead is right, and stacking more lead onto it is not the fix.

Compensation now lives in `tools/target_ekf.py`, which propagates the target
STATE forward by the lag through the dynamics it already estimates, so the
correction is automatically right at every range instead of at one.

### Tracking: an EKF fusing position fixes with camera bearings

`tools/target_ekf.py` - 6-state constant-velocity EKF on the target in NED,
replacing the raw finite-difference velocity that used to be handed to the
firmware. **The firmware interface is unchanged** (still just target position
+ velocity, still all the guidance in flight code); only the quality of what
it receives changed.

**Why the FIRST vision attempt lost to no vision at all**, and what is
different now - this matters because the measured numbers looked damning:
closest approach 0.41-1.03m with vision off versus 1.03-2.35m with it on,
identical firmware. Two independent causes, both fixed:

- **It SUBSTITUTED instead of fusing.** While the ball was in frame it
  rotated the target direction onto the measured bearing and kept the
  last-known range - discarding what the position channel knew, and creating
  a step change at every dropout. The filter fuses instead: the bearing
  update's Jacobian `(I - u u^T)/|R|` is a rank-2 projector whose null space
  is the sightline itself, so vision sharpens DIRECTION and is
  *structurally* incapable of corrupting RANGE. No gate, no heuristic - it
  falls out of the geometry. Verified offline: seeded with 5m of pure range
  error and fed bearings only, the error stays along the sightline (1.08m
  along, 0.08m cross).
- **It cost loop rate.** Subscribing to two 640x480 30Hz RGB topics pushes
  ~55 MB/s into the process that feeds sensors to the firmware - the exact
  failure class recorded twice already in this file. The model now carries
  dedicated `cam_track_up` / `cam_track_45` at **160x120 @ 20Hz (2.3 MB/s, a
  24x cut)**; the 640x480 feeds are untouched and still serve the GUI's FPV
  widgets, which render in the Gazebo GUI process and never touch the bridge.

Also fixed in `ball_tracker.py`: bearings are now a full **body-frame ray**
(pixel -> camera ray -> mount rotation -> FLU->FRD), not an angle pair with
the mount tilt folded in as a scalar added to elevation. That shortcut is
only correct on the optical axis, and cam_up - pitched 90 deg - spends an
entire engagement off it.

`sigma_a` (process noise, the one real knob) is **0.5 m/s^2**, picked from a
sweep rather than taste: turn-tracking error bottoms out on a 0.5-0.8
plateau while straight-line prediction keeps degrading above 0.5. Table in
the source.

### The miss is now ENTIRELY VERTICAL, and the budget is why (2026-08-10)

With lag compensation in the estimator, the horizontal solution is
essentially exact and the whole miss moved to one axis:

    ekfA1   horiz 0.10m   vert -1.16m   (along-track -0.095, cross 0.034)
    ekfA2   horiz 0.08m   vert -1.28m

The FC's OWN log settles what kind of vertical failure it is: through the
merge the vehicle tracked its commanded climb to within **0.10 m/s**, while
that command decayed to **0.41-0.45 m/s with 1.16-1.28m still to close**.
The airframe was never the limit - **guidance under-asks**.

**Asking harder out of the same budget is NOT the fix, and is measured
worse.** Raising the vertical cap to the time-matched rate `|vgap|/t_go`:

    before  horiz 0.10 / 0.08   vert -1.16 / -1.28   sep 1.16 / 1.29
    after   horiz 0.23 / 0.30   vert -1.41 / -1.51   sep 1.43 / 1.54

Worse on BOTH axes, which is the tell. `vmax` is a **shared budget** - the
horizontal term is `sqrt(vmax^2 - v_climb^2)` - so buying climb spends
closure: 1.32 m/s of climb instead of 0.98 drops horizontal from 1.97 to
1.76 m/s, the merge happens ~0.6s sooner, and the vehicle is therefore lower
when it gets there. Reverted, documented in paths.c.

**RESOLVED by the climb-first gate, not by the vertical law.**
`INTERCEPT_LEVEL_BAND` 1.5 -> 0.10 keeps horizontal throttled until the
vehicle is nearly level with the target, so the endgame never has to buy
altitude out of the closure budget at all:

    band 1.5   horiz 0.10 / 0.08   vert -1.16 / -1.28   sep 1.16 / 1.29
    band 0.35  horiz 0.09-0.14     vert -0.69..-0.78    sep 0.70-0.79
    band 0.10  horiz 0.35-0.43     vert -0.31..-0.41    sep 0.46-0.54

With `INTERCEPT_SPEED` 2.2 -> 2.6 (stable; only 3.0 was ever unstable), TEN
consecutive runs made contact on the FIRST pass - zero aborts, zero stern
chases, 0.45-0.58m against the 0.582m contact geometry.

### The error budget is CONSERVED - this is the ceiling, and the reason

Three separate attempts to improve on that all failed the same way:

    vertical cap = time-matched rate   worse on BOTH axes
    INTERCEPT_AIM_HIGH_M 0.35          vert -0.31 -> -0.10, horiz 0.40 -> 0.48
    INTERCEPT_CLIMB_FRAC 0.6 -> 0.9    worse and noisier (0.45-0.63)

Horizontal and vertical error trade **roughly 1:1**, and their sum sits near
0.5m regardless of how the split is chosen, because `vmax` is a SHARED
BUDGET - the horizontal term is `sqrt(vmax^2 - v_climb^2)`. Re-dividing that
budget cannot get below the floor; only more capability or more time can.
That makes the flight-envelope work (tilt/rate/speed maxima) the next real
lever, not further guidance tuning. Do not spend more runs re-splitting.

Note `INTERCEPT_AIM_HIGH_M` has now been tested TWICE: once in the 9Hz era
coupled with a gain change (invalid), and once cleanly here. The clean test
says it works exactly as intended on the vertical axis and buys nothing
overall, for the budget reason above.

### CORRECTION to "TEN consecutive first-pass" - it does NOT reproduce at 3.0 (2026-08-10, late)

The "ten consecutive first-pass contacts" above were at INTERCEPT_SPEED 2.6
and DO hold there (7-8/8 across several batches). A later push to raise speed
tried to carry that to 3.0 and it FELL APART - not into a clean failure, into
VARIANCE. At an identical, verified config on a freshly restarted server,
consecutive 3.0 runs went: strike (-0.02) / strike / MISS (+0.66) / MISS
(+0.73) / MISS high (+0.82) / strike / no-fly. Roughly 40-50% strike.

Two wrong conclusions were reached and then corrected on the way, both worth
recording so they are not re-reached:
  - "3.0 strikes repeatably" - FALSE. It was built on the first two runs
    (r30a/r30b), which were the lucky tail of a high-variance distribution.
  - "the envelope changes regressed the vertical" - ALSO FALSE. fr2 struck at
    -0.02 on the exact config that fr1 missed at +0.82, so it is variance, not
    a regression. A fresh-vs-aged-server confound was hypothesised and
    DISPROVEN the same way (fresh server produced both a strike and a miss).

THE MECHANISM (this is the durable finding). The miss is a stochastic
vertical LEVEL-OFF OVERSHOOT: the vehicle climbs to the target's altitude and
sometimes coasts +0.7m past it before settling, landing the merge at the
overshoot peak. The reason a climb-rate cap in paths.c cannot stop it:
pidcontroldown.cpp assembles the commanded down-velocity as

    velDown = progress->path_vector[2]        // guidance feed-forward (capped)
              + pid_apply(PIDpos, correction_vector[2], dt)   // position term

The position term is a P-loop on the FULL vertical gap and is added
DOWNSTREAM of guidance, so neither `cmd[2]` (capped 1.55 in path_intercept)
nor VtolPathFollowerSettings.VerticalVelMax bounds the flown climb - measured
3.5 m/s entry against a 2.0 setpoint cap. Whatever cures the 3.0 overshoot has
to live in the vertical PID (pidcontroldown), or in decelerating the climb
before level-off, NOT in the guidance feed-forward. This is the same
"downstream code owns the value" trap as the actuator slew limiter and the
corner controller.

MEASURED-AND-REVERTED at 3.0, do not retry blind:
  climb-entry cap 1.55 in paths.c   fixed +0.66 -> +0.02 ONCE (r30a), did not
                                    reproduce; reverted with the envelope push
  INTERCEPT_LEVEL_RAMP 5.0 -> 2.5   neutral (+0.78 -> +0.80)
  VerticalVelMax 3.0 -> 2.0         no effect (climb bypasses it, see above)
  envelope bundle (speed 3.0, MaxRollPitch 35, CruiseControlMaxPowerFactor
  1.45, HorizontalVelMax 4.5)       REVERTED to committed baseline; the
                                    airframe flew 4.0 m/s stably (no tumble,
                                    so the airframe is NOT the speed limit -
                                    the vertical overshoot is), but strike rate
                                    did not survive the variance. Never
                                    committed.

The settled, committed-good intercept config is the 2.6 baseline
(CruiseControlMaxPowerFactor 1.25, MaxRollPitch 25, HorizontalVelMax 3.0, no
climb cap). Raising the speed is a REAL open task (task #63) but it is gated
on fixing the vertical overshoot FIRST, in the vertical PID.

### SOLVED: the 3.0 m/s overshoot is VerticalPosP - but only against a SLOW target (2026-08-10, night)

The stochastic +0.7m level-off overshoot that made 3.0 m/s a coin-flip is
fixed by lowering `VerticalPosP` **0.25 -> 0.10** (bridge config, now
env-overridable via NINJAPILOT_VPOSP so the star keeps its committed tune).

    3.0 m/s, balloon 1.2, vP 0.25   +0.66 / +0.73 / +0.82   coin-flip, ~40-50%
    3.0 m/s, balloon 1.2, vP 0.10   -0.06 / +0.01           2/2 STOPPED (felt)
    3.0 m/s, balloon 1.2, vP 0.15   -0.10                   stopped
    2.6 m/s, balloon 1.2, vP 0.25   -0.09 / -0.18           2/2 (baseline)

WHY: velDown = guidance feed-forward + `VerticalPosP * vertical_gap`
(pidcontroldown.cpp). At an 8m gap, 0.25 alone commands 2.0 m/s ON TOP of
the feed-forward - that is the 3.5 m/s climb entry the taper then cannot
arrest. 0.10 bleeds the climb off EARLY instead of fighting it at the top.
Extra vertical-velocity D (0.08 -> 0.25) also works but arrives LOW
(-0.29/-0.35) - it damps the climb rather than shortening it. Do not stack
both; they are two different low-biases.

### THE REAL SPEED LIMIT IS THE TARGET'S SPEED, and VerticalPosP does NOT fix it

Balloon speed maps monotonically onto vertical error, and this reproduces:

    balloon 1.2   vert -0.06 / +0.01     STOPPED
    balloon 1.6   vert +0.33             barn hit
    balloon 2.0   vert +0.75 / +0.77     barn hit (vP 0.10)
    balloon 2.0   vert +0.65 / +0.83     barn hit (vP 0.05 - NO BETTER)

`VerticalPosP` 0.05 vs 0.10 at balloon 2.0 is statistically identical, so the
fast-target failure is NOT the position gain. THE MECHANISM IS UPSTREAM, in
path_intercept's own climb demand:

    float v_time = vgap / t_use;      // t_use SHRINKS as the balloon speeds up
    float v_need = (|v_gapr| > |v_time|) ? v_gapr : v_time;   // takes the GREATER

A faster target shortens time-to-intercept, so `v_time` grows, so guidance
DEMANDS a faster climb - and a faster climb overshoots more. The merge then
lands in the tail of the climb transient instead of after it settles. This
is why an absolute climb-entry cap (tried earlier and judged "did not
reproduce") looked useless: it was tested at balloon 1.2, where the
time-matched term never binds. **Re-test the climb cap against balloon
1.6-2.0, where the mechanism predicts it should matter.** That is the next
experiment, not more VerticalPosP.

### CONTACT IS NOT SPHERICAL - vertical tolerance is HALF the horizontal

The frame is a flat box: it spans +/-0.235 horizontally (+/-0.332 corner-on)
but only ~0.05 vertically. With the ball's 0.25 radius, contact needs
|vert| <~ 0.30, against ~0.58 horizontally. Measured: a run with sampled
separation **0.40m** - well inside the 0.485 "guaranteed contact" figure -
scored felt=False because vert was +0.33; it passed straight over the ball.

Consequences, both load-bearing:
  - a scalar separation CANNOT score an intercept. Only the physics contact
    sensor / IMU (felt=True) can.
  - vertical accuracy matters roughly twice as much as horizontal, which is
    why every failure mode in this whole investigation has been vertical.

### RULE: restart the gz server between comparison BATCHES, and never trust one run

A server left running for hours of spawn/remove/reset cycles eventually
produces a no-fly (the attitude estimator never initialises - "waiting for
attitude estimator... Critical" forever, vehicle sits on the pad). It was
seen twice this session (s35b, lock3, an fr3). run_intercept.sh now aborts
such a run in ~60s instead of 270s and names the cause. But the deeper
lesson: a marginal result spread across a long-lived server is not
trustworthy - the +0.02/+0.82 split that looked like a server-age effect was
actually pure run-to-run variance, and it took a fresh-server A/B to tell
them apart. For any close call, restart the server and repeat before
believing it.

### The stale target costs whole runs - re-check AFTER the reset

A knocked-down ball survived both the `/world/quadcopter/remove` service AND
the world reset. `run_intercept.sh` removed it only BEFORE the reset, so the
next two runs died on "could not spawn target" - the exact icpt07 failure
that script exists to prevent, recurring because the check was on the wrong
side of the reset. It now re-checks afterwards and aborts loudly with the
remedy (restart the Gazebo server) rather than flying a doomed run.

### RULE: the three-log rule was NOT being enforced on intercept runs

`run_intercept.sh` never set `NINJAPILOT_BRIDGE_LOG`, so `analyze_run.sh`
printed "running board-log analysis only" on every single intercept - the
flight controller's own account of itself, uncorroborated by ground truth.
`run_gazebo_bridge.sh` also never redirected the Gazebo server's output, so
the third log defaulted to a stale empty `/tmp/gzserver.log` for **star runs
too**. Both fixed.

`analyze_run.sh` now takes `NINJAPILOT_RUN_KIND`: score.py, wp_arrival.py,
corner_probe.py and star_plot.py all grade against `star_geom.py` and would
report confident nonsense on an intercept. `tools/intercept_three_log.py` is
the intercept equivalent - and its first output was the vertical diagnosis
above, which no amount of staring at bridge separation numbers had produced.

Two traps found while building it, both the classic ones: the bridge track
did not record the COMMANDED AIM POINT at all (so "planned vs flown" was
undrawable for an intercept - the target's track is where the ball went, not
what we asked for), and the first version of the vertical check scored
post-break-off samples, where a commanded descent made a run that tracked
perfectly report "did NOT track". Window on the engagement, always.

### RULE: validate filter changes OFFLINE first

`tools/test_target_ekf.py` runs the filter against a synthetic truth track in
**0.2s** and checks the three claims that matter: convergence, that bearings
cannot corrupt range, and that `predict_ahead(tau)` actually lands on the
truth tau seconds later. Measured there: at the real 0.48s lag it predicts to
**0.199m**, against the 0.58m of raw lag it replaces - inside the 0.582m
contact geometry.

This is the single biggest time saver available on this problem. Every
guidance constant tried by flying it cost a 60-90s run plus scene reset, and
several of those experiments (the x1.35 lead, the constant lag comp, the
aim-high bias) could have been rejected or predicted at a desk. Fly to
confirm, not to explore.

## OPEN: unexplained intermittent flyaway at wp3 (2026-08-09)

Twice, on otherwise unremarkable runs, the vehicle departed from waypoint 3
and hit the ground: ground truth goes 1.98,-6.09 at 7.91m -> 1.50,-10.26 at
7.46m -> -9.97,-8.10 at 2.51m, i.e. ~11.5m of horizontal travel and 5m of
altitude in two seconds. Roughly 2 occurrences in ~12 runs.

What it is NOT:
- Not a tumble. star113's "roll peak-to-peak 170 deg" was an artifact of 1045
  timestamp-outlier records; filtered, its real attitude was roll p2p 7.0 deg
  and pitch 19.7 deg - normal flight. A velocity-loop gain was reduced on the
  strength of that false reading (the reduction turned out to be right on
  other measured grounds, but the stated reason was wrong).
- Not a collision. Nothing in the farm mesh comes within 3m of any star
  waypoint; the nearest structure above 6m is 13.2m from the pad, due north,
  and the flyaway went west.
- Not visible to the flight controller. Its last logged state is a stable
  hover at 7.96m with roll/pitch inside 8 deg and thrust 0.67-0.70, and the
  estimator agrees with its own GPS input to 0.074m. Internally consistent,
  externally wrong.

The blocker is instrumentation: the board log ENDED BEFORE THE EVENT on both
occasions, so there is no FC-side record of it. analyze_run.sh now compares
the board log span against the mission clock and shouts when the recorder
stopped early - the next occurrence should be diagnosable.

First suspicion to test, given the signature (FC internally consistent while
truth diverges): the sensor feed into the firmware stalling, which is the
same class as the two harness bugs already recorded here - the second UAVTalk
client stealing packets, and marker publishing starving the sensor thread.

## SETTLED: the NE velocity loop had no damping, and that was the corner orbit

The vehicle used to circle its waypoints instead of stopping on them. It was
not the path planner, the lead term, or the acceptance logic - all of those
were tried and are documented as dead ends in vtolflycontroller.cpp. In the
braking zone the follower was commanding a median tilt of 3.4 deg and a
maximum of 9.0 deg against a 25 deg limit: roughly 2.7x the braking authority
it needed was sitting unused, so the vehicle arrived carrying speed the path
never asked for, sailed through the point and was dragged back.

HorizontalVelPID Kd was exactly 0.0. That is also why Kp could never be
raised - a P-only loop pushed past its margin tumbles, which is what 6.5 did
historically. Damping first, then gain.

WATCH THE MARGIN. Kd 1.4 with Kp 7.0 passed three consecutive runs (98s,
cross-track 0.15m, zero overshoot) and then tumbled into the ground at wp3 on
the fourth - roll peak-to-peak 170 deg, 7.25m to 0.06m in two seconds. Three
passes are not evidence of margin. At Kp 5.5 the same tune is SMOOTHER on
every axis and only slower: cross-track 0.15 -> 0.12m, commanded swing 0.67 ->
0.53 m/s, pitch RMS 4.11 -> 2.49 deg, over three consecutive clean runs at
115-123s. Kp 7.0 was buying 20s on credit.

Working values: HorizontalVelPID [5.5, 0.5, 1.4, 15], HorizontalPosP 0.35
(0.60 was tried and is worse - see the note there), MISSION_SPEED 1.5.

## RULE: purge the previous flight's slots before every run

Use `ground/gazebo_bridge/run_star.sh <label>` rather than hand-typing the
launch sequence. It kills the previous processes, WAITS for them to actually
exit, deletes `~/ninjapilot-build/fcwd/233CDC*.o*`, verifies the directory is
empty, resets the scene, flies, and analyses - and it refuses to run if any
of that fails.

The slot files persist between runs, and `decode_fcwd.py` can only tell
flights apart by the low nibble of the filename, so flight N and flight N+16
alias onto each other and merge. A merged pair does not look broken: it
decodes cleanly and reports a flight containing two missions, with a 4162s
"dwell" and a 0.3Hz sample rate (star100). decode_fcwd now warns when the
kept flight spans more than 600s, but the warning is a backstop - the purge
is the fix.

## RULE: SHOW the top-down plot after every run

Analysing the three logs is not finished until the planned-vs-flown picture
has been put in front of the user. `tools/analyze_run.sh` writes it to
`$TMPDIR/<label>.png` (top-down planned vs actual, plus the altitude profile
with waypoint transitions marked) and the path is printed at the end of the
run; send that file, every time, without being asked.

Numbers and picture answer different questions. A rounded corner, a bowed
leg, an altitude sag and a yaw-induced S all score similarly in a mean
cross-track figure and look nothing alike on the plot - and the altitude
trace is the fastest way to catch a vertical regression that a horizontal
score cannot see at all. Several conclusions this session came from the
shape, not the number.

One more trap the plot cannot save you from: the analysis tools score
against the mission geometry in `tools/star_geom.py`. If the mission changes
and that file does not, every tool keeps scoring the OLD shape and reports
confident nonsense - a mission change once read as 1.76m of cross-track
error that was purely a stale planned path. It is the single source of
truth for all of score.py, wp_arrival.py, star_plot.py and analyze_run.sh;
keep it in step with `build_mission()`.

## Lineage: OpenPilot -> NinjaPilot (NOT LibrePilot)

- **OpenPilot** was the original project; 15.02 was its final-era
  release line before the project shut down (mid-2015). **LibrePilot**
  is the community fork that continued from OpenPilot's end-state.
  **NinjaPilot (this tree)** is its own independent fork of
  OpenPilot 15.02 - it branched before/around the LibrePilot split and
  shares NO history with LibrePilot's later changes. LibrePilot docs,
  fixes, and code layout may LOOK applicable but frequently aren't:
  this tree has its own module set, its own bug surface, and (as of
  these sessions) its own heavy local modifications (FreeRTOS upgrade,
  callback-scheduler priority restructure, SimPosix revival, filter
  fixes). Treat LibrePilot strictly as an occasionally-useful reference,
  never as ground truth.
- A separate **`../OpenPilot` checkout sits alongside this repo** (same
  parent dir, "OP Revo Redux"). It's upstream reference material - e.g.
  `../OpenPilot/matlab/ins/` holds the original MATLAB/MEX validation
  harness for the same insgps EKF C code this tree carries in
  `flight/libraries/insgps13state.c`. Useful for provenance/comparison;
  do not edit it as part of NinjaPilot work.

## FreeRTOS: kernel was REPLACED (V8.0.1 -> V11.3.0), and the rule about it

- The vendored kernel under `flight/pios/common/libraries/FreeRTOS/Source/`
  is **FreeRTOS V11.3.0** (upgraded from the 2014-era V8.0.1 this tree
  shipped with; commit 30ba00007). The Posix port is V11.3.0's
  ThirdParty event-based port (`utils/wait_for_event.c`) - it replaced
  the old SIGUSR1+threadStatus port, which had a confirmed missed-wakeup
  race. ARM_CM3 (coptercontrol/oplinkmini) swapped too, compile-verified.
  The ONE deliberate local patch reapplied on top of stock V11.3.0:
  `uxTaskGetRunTime()` (read-and-clear counter for pios_task_monitor.c),
  in tasks.c + include/task.h.
- Known upgrade fallout already handled (pattern for future targets):
  `vApplicationStackOverflowHook` signature (`TaskHandle_t, char*`),
  `vPortYieldFromISR()` -> `portYIELD_FROM_ISR(x)`, plain-integer
  `configMAX_PRIORITIES` (no cast wrappers), and
  `configCHECK_HANDLER_INSTALLATION 0` where configASSERT is undefined.
  `configMAX_PRIORITIES` history: 5 (stock) -> 7 (STATEESTIMATION/
  ALTITUDEHOLD tasks) -> 8 (STABILIZATIONOUTERLOOP), across all five
  FreeRTOSConfig.h files.
- **DURABLE USER RULE - do not violate:** never patch FreeRTOS kernel
  internals as the first-choice fix for a scheduling/race symptom.
  FreeRTOS is used by a billion devices; a genuine kernel bug would
  manifest everywhere. Wrap around it at the PiOS/application layer
  (task structure, priorities, mutexes) instead. A temporary kernel
  patch is allowed ONLY as a sanity-check experiment and MUST always be
  reverted afterward - the wholesale version upgrade above was the
  sanctioned path precisely because it avoids hand-patched kernel code.

## Source of truth

- **This repo's own C source is the only source of truth for flight-code
  behavior.** Do not reason from LibrePilot documentation, general
  OpenPilot/PX4/ArduPilot community knowledge, or "how I remember this
  working elsewhere." This tree forked before/around the LibrePilot split
  and has its own module set - check `flight/targets/boards/<target>/firmware/Makefile`'s
  `MODULES` list before assuming a module (e.g. `Attitude` vs
  `StateEstimation`) is even compiled in for the target you're testing.
- When a GCS-side Python helper (`board_orientation_viz.py`,
  `gazebo_bridge.py`) needs to match a flight-code convention (mixer
  layout, sign convention, units), trace it through the actual `.c`/`.h`
  files in `flight/`, not from memory or by analogy to another project.

## Verify claims, don't just derive them

- A hand-derived formula (quaternion transform, sign convention, physics
  relationship) is a hypothesis, not a fact, until it's checked against
  either (a) the actual C source's own convention, or (b) an empirical
  test with concrete numbers. Say "verified via X" only when X actually
  happened in this session - don't imply verification that didn't occur.
- When a fix changes behavior but doesn't produce the *expected* new
  behavior, don't reach for a second, unrelated hypothesis before
  checking whether the fix and the previous investigation are still
  both true. Re-examine what you just changed first.
- **Disprove your own hypothesis out loud when the data does.** This
  session's outerloop-starvation theory was real but self-healing;
  saying so explicitly (instead of quietly pivoting) is what kept the
  investigation honest and led to the actual cause.

## Architecture facts (confirmed this session, save re-derivation time)

- **Control chain for thrust**: bridge GCSReceiver channel →
  `ManualControlCommand.Throttle` → `StabilizationDesired.Thrust` →
  (outerloop.c `stabilizationOuterloopTask`) → `RateDesired.Thrust` →
  (innerloop.c `stabilizationInnerloopTask`, CRITICAL, gyro-triggered)
  → `ActuatorDesired.Thrust` → (actuator.c mixer) → `ActuatorCommand`
  PWM 1000..2000 → bridge `publish_motor_speeds()` → Gazebo motors.
- **outerloop.c is dispatched ONLY from `AttitudeStateUpdatedCb`**
  (1 in `OUTERLOOP_SKIPCOUNT`=4 AttitudeState updates). No AttitudeState
  publishes → outerloop never runs → `RateDesired` goes stale → whatever
  thrust was last computed persists downstream. innerloop keeps running
  off gyro regardless and faithfully forwards the stale value.
- **AttitudeState is published by StateEstimationCb** only when a filter
  in the active chain sets `SENSORUPDATES_attitude` (cfmFilter for the
  Complementary+Mag chains — see filtercf.c's gyro+accel gating).
- **stabilization.c `StabilizationDesiredUpdatedCb`** maps per-axis
  StabilizationMode → StabilizationStatus.OuterLoop/InnerLoop. "Manual"
  thrust = OUTERLOOP_DIRECT + INNERLOOP_DIRECT (passthrough) — a quad CAN
  fly with Thrust=Manual here; Roll/Pitch stay Attitude-stabilized
  (this is OpenPilot's per-axis scheme, not full-vehicle "Manual" mode).
- **armhandler.c `okToArm()`** blocks arming while thrust mode is
  ALTITUDEHOLD/ALTITUDEVARIO, and any alarm ≥ Critical (except
  GPS/Telemetry) blocks arming.
- **Fusion algorithms** (`RevoSettings.FusionAlgorithm`, set from
  `board_orientation_viz.py` REVOSETTINGS_DEFAULTS): test setup uses
  Complementary+Mag+GPSOutdoor (`cfmQueue`: mag→air→lla→baro→altitude→cfm).
  Attitude = Mahony complementary filter (filtercf.c — verified by P+I
  cross-product structure, Mahony/Hamel/Pflimlin 2008). Vertical channel
  = filteraltitude.c, an alpha-beta (g-h / Benedict-Bordner 1962 family)
  accel+baro filter with BaroKp / BaroKp² gains. INS13 modes instead use
  filterekf.c → insgps13state.c (EKF per Grewal & Andrews, cited in
  source). A MATLAB/MEX validation harness for the same insgps C code
  lives in the sibling checkout `../OpenPilot/matlab/ins/`.

## THE BIG ONE - startup thrust dead-zone / snap (root cause chain, all confirmed)

Every "runaway climb past the 8m ceiling" crash this whole investigation
chased — across FOUR independently tested vertical-filter algorithms —
was dominated by this, not by estimator math:

1. There is a **~9-12s one-time gap between the 1st and 2nd AttitudeState
   publish** near boot/config/arm (exact cause of the gap NOT yet found —
   open thread; filtercf init? config-burst stall of the sensor feed?).
2. During the gap outerloop.c never runs (see dispatch fact above), so
   `RateDesired.Thrust` sits at stale -1.0 while ActuatorCommand sits at
   1000 (idle) — vehicle ignores all throttle commands, sits on ground.
3. When AttitudeState resumes, everything snaps to the live commanded
   value in ONE tick (idle → near-max instantly). Meanwhile the test
   harness / any integrator upstream has wound up during the stall.
4. Vehicle rockets, blows through the ceiling, "crash".

Verification of the chain: `[dbg]` traces of ManualControlCommand /
StabilizationDesired (correct, on time) vs ActuatorDesired/-Command
(stale then snapping); innerloop.c `rateupdates` watchdog collapsing to
-64 then recovering to -6 in one sample the instant AttitudeState
resumed; `AttitudeStateUpdatedCb` callCount trace showing the 12s gap.
NOT the cause: cchain.Stabilization gate (open from boot), arming
(Armed on time), UAVObject event queue (0 drops), scheduler priority of
outerloop (starvation was real early-boot but self-heals; see below).

Fixes landed (in main tree, ALL SYNCED TO ~/ninjapilot-build and built):
- **actuator.c: asymmetric thrust slew-rate limiter** (rising only,
  3.0/s full-range ≈0.67s, never limits a drop). Verified: ActuatorCommand
  now ramps 1007→1013→1025… instead of 1000→1939 in one tick.
- **outerloop.c moved to its own dedicated
  `CALLBACK_TASK_STABILIZATIONOUTERLOOP` (tskIDLE_PRIORITY+4)**, above
  FLIGHTCONTROL — producer-above-consumer, same pattern as
  STATEESTIMATION/ALTITUDEHOLD. `configMAX_PRIORITIES` bumped 7→8 in all
  5 FreeRTOSConfig.h files (simposix/coptercontrol/oplinkmini/osx/win32).

RESOLVED in the 2026-08-08 evening session (commits 7fb5b9ab1,
d45aa42f5, b8999ec7f carry full detail):
- The ~12s AttitudeState gap = filtercf.c's DELIBERATE calibration
  windows (4s ERROR + 6s CRITICAL, zero attitude output until init
  completes), stacked/restarted by config-driven chain re-inits. Handled
  by the bridge's wait_for_attitude_ok() arming gate (the "Always Armed"
  force-arm bypasses okToArm's alarm check, so the harness must enforce
  the contract real hardware enforces via the alarm).
- The throttle-cut lag AND "estimator randomly freezes" = UDP RX thread
  at bottom priority (kernel-queue backlog holding SECONDS of stale
  in-order data) PLUS a com-layer 16-byte-chunked-read corruption
  destroying ~99% of the last-in-burst object at ~350 pkt/s (perfectly
  framed packets failing CRC against a constant stale byte; the 65-byte
  TELEM_USB fifo was exactly one byte short of the 65-byte per-tick
  burst). Fixed: non-blocking drain-per-tick RX at top priority (a
  BLOCKING syscall at high priority wedges the whole Posix-port
  scheduler - learned the hard way), big com buffers, one-read burst
  consumption in telemetryRxTask, telemetry tasks at sensor-bus priority
  on SIMPOSIX only. Verified: rxErrors=0, gyro/accel exact 1:1 lockstep
  at ~510/s.
- **2D BARO ALTITUDE HOLD NOW PASSES** - both scripted stages (real
  AltitudeVario climb to 5ft/10ft + holds, estimator tracking truth to
  centimeters). The manual ground-truth hover foundation test also fully
  passes (45s holds at 10m and 20m, clean landing).
- The V2 sustained-gap heuristic (filteraltitude.c) and the bridge's
  AccelDriftKi=0.05 override were both REMOVED - each was a compensation
  for the broken transport that became actively harmful on clean data
  (absorbing real climb acceleration into the bias estimate within
  ~56ms-2s, blinding the velocity fast-path and causing the vario
  overshoot they were meant to prevent).

**3D GPS POSITIONHOLD: WORKING** (commit 77ac78e73, 2026-08-08 late
session). 60s dedicated hold: max lateral error 0.04m, steady-state
altitude +/-0.05m; full scripted sequence passes end-to-end genuinely
airborne (ground-truth-verified). The three fixes that got there, in
order of discovery:
- V3 Kalman vertical filter ported to main (covariance-derived baro
  gain replacing BaroKp/BaroKp^2).
- **The 90-degree yaw frame error** (the lateral-spiral root cause):
  Gazebo ENU zero-rotation spawn faces EAST; measuring HomeLocation.Be
  in the body frame at spawn defined yaw=0 as east while GPS/NED uses
  true north - PathFollower rotated every correction ~90deg (positive
  feedback, gain-independent divergence). Fixed: world SDF spawns
  facing true north AND Be now derives from the world <magnetic_field>
  ENU->NED (never trust spawn attitude for a world reference).
- VtolPathFollowerSettings.FlyawayEmergencyFallback DISABLED for sim
  (course-error criterion is numerical noise at zero-velocity hover;
  false-tripped a commanded 2.3 m/s descent after 35s of perfect hold).
  Plus: neutral thrust 0.70 (measured), VerticalVelPID 0.6/0.45,
  horizontal cascade detuned for 10Hz GPS feedback, attitude P back to
  stock 2.5.
- `NINJAPILOT_TEST_MODE=poshold` = fast (~2min) PositionHold iteration
  test with real ground-truth pass criteria.

## GPS fidelity: the sim GPS is idealized-ublox-grade, not NMEA-grade

Facts confirmed in this fork's source (relevant whenever GPS behavior is
questioned, per feedback from a former OpenPilot project founder):
- **GPSVelocitySensor is published ONLY by flight/modules/GPS/UBX.c**
  (parse_ubx_nav_velned, NAV-PVT on newer receivers). NMEA.c publishes
  no velocity objects at all - NMEA course/speed-over-ground has no
  vertical velocity. The outdoor EKF fuses GPS velocity as a measurement
  (filterekf.c vel import -> HORIZ_SENSORS|VERT_SENSORS), so on real
  hardware it REQUIRES ublox binary protocol. ubx_autoconfig.c handles
  UBX_HW_VERSION_7/8 explicitly (per-version max nav rates).
- **The SITL bridge bypasses the protocol layer entirely**: it injects
  the POST-parser UAVObjects (GPSPositionSensor with Fix3D/PDOP/sats
  passing filterlla's gates, GPSVelocitySensor with full 3D NED velocity
  from gz-navsat's velocity_north/east/up) at 10Hz. In substance the
  filters receive exactly what a ublox-8 delivers after UBX.c parses it
  - which is why sim PositionHold can hit 4cm. Gazebo itself has NO UBX
  serial-protocol emulation (navsat is protobuf-only); the only mature
  open-source simulated-UBX-byte-stream generator known is ArduPilot
  SITL's GPS backend (SIM_GPS_TYPE can emit real u-blox binary).

SIDELINED FUTURE TASK - "real UBX path" fidelity milestone: the
injection shortcut skips GPS.c/UBX.c/ubx_autoconfig.c completely
(parser timing, status transitions, DOP behavior, autoconfig dance all
unexercised). The clean implementation path already exists: the
firmware's SECOND UDP socket is the GPS port (bound at boot, currently
receiving zero traffic - "udp dev 1" in the boot log), so a small UBX
encoder in the bridge (SOL/POSLLH/VELNED/DOP set, or a single NAV-PVT,
built from the same navsat data) would exercise the REAL GPS module
end-to-end. Reference implementation: ArduPilot's sim_gps. Deliberately
sidelined on 2026-08-08 - do not start it without being asked.

**PATHPLANNER WAYPOINT MISSIONS: WORKING** (commit ba13c9b45). Full
GCS-style autonomous mission flies end-to-end: 29-waypoint star (8m) ->
octagon (18m) -> letters 'KF' (28m) -> Land action (0.6 m/s, horizontal
PH) to auto-disarm, 177s. Upload path is exactly the GCS interface:
multi-instance Waypoint/PathAction objects + PathPlan CRC-8 (poly 0x07
over packed instance bytes, waypoints then actions) validated by the
FLIGHT side before engaging. Engage sequence: upload -> arm -> vario
staging climb -> PositionHold (activates PathFollower) -> switch
position 4 = PathPlanner (FlightModeNumber is 5 now - at 4, the
position-4 channel value silently clamped into the PositionHold bin).
Key flight-code fix: pidcontroldown.cpp RateLimit() clamp was
`accel *= rateLimit/accel` == "always +rateLimit", sign discarded -
any large DOWNWARD setpoint change ramped UPWARD forever (confirmed in
exact +2 m/s^2 steps). It was upstream dead code activated by an
earlier session's smoothing fix. Translucent planned(amber)/flown(cyan)
trails render via Gazebo's /marker LINE_STRIP service.
`NINJAPILOT_TEST_MODE=mission` runs the whole thing supervised with
real ground-truth pass/fail. Known polish item: corner tracking is
loose (+/-2-4m overshoots); 5m-altitude rings clip the ground during
aggressive corners - keep shape rings >= 8m until PathFollower
horizontal tuning gets its own pass.

STILL OPEN (quality-of-life, not blockers):
- The full outdoor EKF (INS13) attitude degrades in flight on sim-clean
  sensors (covariance sanity resets; EKFConfiguration Q/R expect real
  sensor noise) - its own tuning project if ever wanted here.
- The exact defective line in the 16-byte multi-read path (com fifo
  boundary handling) was bypassed by the big single read, not isolated -
  worth a targeted dig someday.
- Extensive `[SIMPOSIX-IFDEF-MARKER]` debug prints remain scattered in
  stateestimation.c, filteraltitude.c, altitudeloop.c, innerloop.c,
  outerloop.c, uavobjectmanager.c, pios_callbackscheduler.c, uavtalk.c,
  pios_udp.c — now eligible for cleanup (3D hold is green).

## Estimator findings that ARE real (fixed earlier, keep)

- filterbaro.c unconditionally clears SENSORUPDATES_baro before
  filteraltitude.c (next in chain) could use it → filteraltitude's
  first_run never cleared → its whole body was dead code. Fixed via
  `IS_REAL(state->baro[0])` gate. VelocityState went ~3/s → thousands/s.
- Cross-thread races created by splitting modules onto own tasks:
  `updatedSensorsMutex` (stateestimation.c), `altitudeMutex`
  (altitudeloop.c). Producer-above-consumer priority ordering in
  pios_callbackscheduler.h (STATEESTIMATION > ALTITUDEHOLD > OUTERLOOP >
  FLIGHTCONTROL) — its comment block is the authoritative history.
- gazebo_bridge.py: never send two UAVTalk objects back-to-back with no
  gap (corrupts/drops one) — gyro every tick, accel alternate ticks.

## Algorithm-variant worktrees (V1-V4 comparison, all crashed pre-fix)

Context: the stock vertical channel (filteraltitude.c) is a fixed-gain
accel+baro complementary filter - alpha-beta / g-h family (canonical
critically-damped form: Benedict & Bordner 1962, "Synthesis of an
Optimal Set of Radar Track-While-Scan Smoothing Equations"), using
BaroKp on altitude and BaroKp^2 on velocity (defaults 0.04/0.0016 from
altitudefiltersettings.xml). Its structural weakness: it cannot
distinguish "accel bias drifted" from "real sustained acceleration" -
both look identical to the slow AccelDriftKi=0.0005 bias tracker, and
the fixed weak baro gain can't out-pull an accumulated integration
error. Four alternatives were implemented and tested independently,
each in its own worktree/branch/build tree so nothing pollutes main.

Branches off ede77d77b (branch `claude`), worktrees in
`../NinjaPilot-alt-*`, isolated build trees `~/ninjapilot-build-v1..v4`:

- **V1 `alt-v1-benedict-bordner`** (worktree `../NinjaPilot-alt-v1-bb`):
  one-line change in filteraltitude.c - velocity-correction gain from
  the approximate `BaroKp^2` to the canonical critically-damped
  Benedict-Bordner relation `beta = BaroKp^2/(2-BaroKp)`. Numerically
  tiny at BaroKp=0.04 (0.0016 vs 0.001633); tested to confirm rather
  than assume. Result: crashed at the same point/altitude as baseline.
- **V2 `alt-v2-sagehusa-adaptive`**: innovation-adaptive bias tracking
  (informal Sage-Husa / Mohamed & Schwarz 1999 style) in
  filteraltitude.c - when |accelState-accelBiasState| stays >1.0 m/s^2
  for >2s (a sustained divergence, not sensor noise), switch bias
  tracking to the fast InitializationAccelDriftKi rate until it
  re-converges. New struct fields gapActive/gapStartTimer +
  SUSTAINED_GAP_THRESHOLD_MPS2/SUSTAINED_GAP_DURATION_MS constants.
  Result: crashed identically.
- **V3 `alt-v3-kalman`**: full rewrite of filteraltitude.c's body into a
  real 3-state Kalman filter - state [altitude, velocity, accelBias],
  3x3 covariance P propagated per predict step (F/B strapdown model,
  accel as control input, Q from accel noise + bias random walk), scalar
  baro measurement update with gain K = P*H'/(H*P*H'+R) derived from
  live covariance instead of any fixed constant. Noise constants:
  ACCEL_NOISE_VAR 1e-2, BIAS_NOISE_VAR 1e-7/s, BARO_NOISE_VAR 0.25 m^2.
  Result: crashed identically.
- **V4 `alt-v4-ekf13i`** (branch `alt-v4-ekf13indoor`): NO C changes -
  config-only switch of RevoSettings.FusionAlgorithm to "INS13Indoor"
  (in `ground/pyuavtalk/board_orientation_viz.py` REVOSETTINGS_DEFAULTS),
  routing everything through the already-in-tree 13-state EKF
  (filterekf.c -> insgps13state.c, Grewal & Andrews; filterstationary.c
  injects the soft pos=0/vel=0 pseudo-measurement indoors). Result: no
  ceiling crash BUT the vehicle never left the ground (alt=0.055m
  through both "climbs") - the test sequence "passed" vacuously. That is
  a FAIL, not a success (per user: "sitting on the ground not climbing
  to height is a fail").

Verdict: V1-V3 failing at the nearly identical moment despite three
structurally different filters is what proved the dominant failure was
upstream of ALL filter math -> led to the manual_hover ground-truth test
-> which exposed the startup thrust dead-zone/snap (see THE BIG ONE).
**The four algorithms were never actually exercised in-flight** - re-run
this comparison after the dead-zone threads are closed to get a real
ranking. When re-running V4, note its worktree launcher needs the
VENV_PY path fix and BUILD_ROOT pointed at ~/ninjapilot-build-v4 (see
SKILLS.md).

## SimPosix / Gazebo bridge debugging patterns

- **DO NOT restart Gazebo server+GUI for every test run.** Reset the
  scene/world instead (see SKILLS.md "Reset instead of relaunch") and
  restart only fw_simposix.elf + gazebo_bridge.py. Full Gazebo restarts
  waste ~10s+ per iteration, add GUI churn, and are almost never needed.
  (Restart Gazebo only if the world SDF/model itself changed or the
  server is wedged.)
- **Stale ELF binary**: all testing/rebuilding happens against the
  rsynced copy at `~/ninjapilot-build` (repo tree does not build
  directly). `run_gazebo_bridge.sh`'s `ELF` points there. rsync changed
  files in, then `make -j4 ARM_SDK_PREFIX=arm-none-eabi- simposix`.
  A `build/` dir carried over from a different tree causes the
  `0xNone commit_hash_prefix` firmware_info error — `rm -rf build` then
  rebuild (version-info.py needs the worktree's `.git` file present,
  rsync WITHOUT `--exclude='.git'` for worktree-based build dirs).
- **`NINJAPILOT_EXTERNAL_PHYSICS=1`** disables sensors.c's own simulated
  sensors; bridge UAVTalk traffic is then the ONLY sensor source.
- **`stabilizationInnerloopTask()` is GyroState-triggered**, not timed;
  a stalled gyro feed looks like a flight-code freeze but isn't.
- **`PIOS_SENSOR_RATE`** is per-target in pios_config.h (500.0f simposix).
- **One deterministically-paced sender loop** per UDP socket; two
  GIL-scheduled threads bursting on one socket silently drop packets.
- When a fix changes the failure mode instead of fixing the problem,
  that's data - but check what else changed between runs first.
- The X3 model accelerates HARD (≈7 m/s gained in ~1s at 0.95 throttle,
  hover ≈0.68). Test controllers need velocity damping and saturation-
  aware anti-windup or they will overshoot any ceiling. Physics engine
  is gz-sim default DART (gz-physics-dartsim-plugin).

## Testing workflow

- `ground/gazebo_bridge/run_gazebo_bridge.sh` launches Gazebo server
  (headless) + GUI (separate processes - macOS can't combine), the ELF,
  and the bridge, lifetimes tied. Before any relaunch: `pkill` all four
  (`gz sim`, `fw_simposix.elf`, `gazebo_bridge.py`,
  `run_gazebo_bridge.sh`) and confirm via `ps aux` - stale processes
  cause cross-talk. But prefer scene-reset iteration (above) over full
  relaunches.
- `NINJAPILOT_TEST_MODE=manual_hover` runs `manual_hover_test()` in
  gazebo_bridge.py: raw-throttle (no hold mode) climb-and-hold at
  10m/20m using GROUND-TRUTH pose feedback only, bypassing the estimator
  entirely. This is the foundation-block test: if it fails, the problem
  is thrust/physics/transport, not estimation. Default (scripted) mode
  is the estimator-based staged test. `NINJAPILOT_VERBOSE=1` enables
  the high-rate [dbg]/[barodiag]/etc prints.
- For ground-truth verification independent of the bridge's own prints,
  subscribe directly to `/world/<world>/pose/info` with gz.transport13.
- C-side (`[SIMPOSIX-IFDEF-MARKER]`, wall-clock stamped) and Python-side
  logs land in the SAME combined logfile - correlate by `t=` wall-clock,
  never by line order.

## On-board DebugLog: the FC's own flight recorder (added 2026-08-08)

- The Logging module compiles on simposix (same code as real boards).
  The bridge enables it around EVERY test flight (OnlyWhenArmed - each
  arm..disarm span is one "flight") and pulls/decodes the log after,
  into `ground/gazebo_bridge/logs/fclog_<ts>_flight<N>.jsonl/.txt`.
  `NINJAPILOT_TEST_MODE=pull_logs` downloads without flying. Full
  recipes in SKILLS.md "On-board FC logs".
- What gets logged is driven by per-object logging METADATA written over
  UAVTalk to the metaobject (id = objid+1, 8-byte struct, logging mode
  bits 8-9) - see FC_LOG_OBJECTS in gazebo_bridge.py. Raw sensors
  (BaroSensor, GPSVelocitySensor) are logged ALONGSIDE fused states
  precisely so post-crash analysis can separate "estimator diverged
  from its sensors" from "sensors were wrong".
- Slot decode gotcha: pios_debuglog.c packs FOLLOW-ON records into a
  slot's Data (17-byte sub-headers) and only labels the slot
  MultipleUAVObjects when it overflowed - a Printf flush leaves it
  saying UAVObject with multiple records inside. Always walk the tail.
- On simposix the flashfs backend is pios_dosfs_logfs.c: slots are ALSO
  host files `233CDC00.oNN` in the firmware process CWD (we launch from
  `~/ninjapilot-build/fcwd`; `rm` them pre-session for clean flight
  numbering). The telemetry pull never touches them - it's the same
  DebugLogControl/DebugLogEntry protocol GCS uses on hardware.

## Mission corner smoothing + the estimator bugs it flushed out (2026-08-09)

- Missions 12-16 chronology matters if touching FollowVector or the
  vertical filter; the onboard log pull was the diagnostic tool for all
  of it. Final state: mission 16 PASS - star hairpin overshoot 0.00m on
  all five points (was 2-4m with GoToEndpoint@1.5m/s), yaw locked to
  +/-0.1 deg (was +/-20 deg limit cycle).
- Corner design (all in gazebo_bridge.py build_mission): FollowVector
  mode + per-waypoint arrival speed from the 3D turn angle
  (_corner_speed: 1.5 straight / 0.8 gentle / 0.6 right-angle / 0.45
  hairpin); LEVEL legs use 2D acceptance, vertical-transition legs 3D
  (a 3D sphere is unreachable when the vertical estimate wobbles >1m,
  and FollowVector projects onto the INFINITE line - a missed sphere
  sails away forever at EndingVelocity; mission supervision now has a
  flyaway guard for exactly that).
- filteraltitude.c V3 fixes (commit 1ab94cd69, flight code): (1)
  kfCorrectVel() - GPS vertical velocity was received and DISCARDED;
  without it the velocity state was inert (stale accel + tiny baro
  K[1]) and read WRONG-SIGN during real climbs. (2) process noise
  1e-2 -> 1.0 (m/s^2)^2 - at 1e-2 the covariance collapsed after ~20s
  of agreeing measurements and the filter went deaf (ignored a real
  1 m/s descent straight into the ground). Both invisible in
  PositionHold, where vertical velocity is ~0 - which is where the
  filter had been validated. Full forensics in the commit message.
- Yaw in PathFollower modes is FORCED to AXISLOCK (vtolflycontroller
  yaw_attitude=false branch). AxisLockKp 2.5 demanded 50 deg/s at 20
  deg error = exactly the MaximumRate.Yaw cap, which the X3's weak
  rotor-drag yaw torque can't track -> saturation limit cycle at ~3.7s
  period. AxisLockKp 1.0 (bridge config) kills it.
- Gazebo GUI niceties (bridge does these automatically at mission
  start): camera follow via `/gui/follow` + `/gui/follow/offset`
  services; planned/flown trails as craft-width translucent CYLINDER
  markers (gz renders LINE_STRIP at 1px - invisible; user-confirmed).
  /marker service quirks: reply type is Empty, the call often reports
  ok=False YET the marker registers (verify via /marker/list);
  DELETE_ALL per-namespace clears stale trails.

## Yaw-following waypoints, autotune, and the tuning traps (2026-08-09)

Goal: fly waypoint legs with the nose pointed along the leg. What that
took, and the traps that cost the most time:

- **`StabilizationBank` is a VOLATILE MIRROR.** stabilization.c's
  SettingsBankUpdatedCb re-copies StabilizationSettingsBank1/2/3 (per
  FlightModeMap) over it on EVERY flight-mode change. The bridge wrote
  only the mirror for months, so every stab-bank value silently reverted
  to XML defaults at the first mode switch. Caught only when an onboard
  log showed yaw slewing at ~118 deg/s under a "20 deg/s" cap. ALWAYS
  write `StabilizationSettingsBank1`. Any pre-2026-08-09 conclusion of
  the form "we tuned bank value X and it helped" is suspect.
- **Whole-object writes stomp each other.** The bridge re-sends the
  entire FlightModeSettings on every arm/disarm transition; that wiped a
  custom FlightModePosition mapping the instant the test armed (two
  autotune runs flew their whole window in the WRONG FLIGHT MODE).
  `_fms_position_override` now survives the re-send. Lesson: after
  writing any settings object, VERIFY via readback or FlightStatus, do
  not assume the write stuck.
- **`updatePathBearing()` must use the LEG direction, not
  `progress.path_vector`.** path_vector is a velocity vector that points
  from the vehicle AT the endpoint (GoToEndpoint, and FollowVector once
  past the endpoint), so it swings wildly - and spins - as the vehicle
  passes near a waypoint. Feeding it to the yaw attitude loop whipped the
  nose around at every waypoint and wrecked path tracking (leg reversals,
  32s crawls). Using `End - Start` is constant per leg. This single fix
  turned an oscillating mess into monotonic legs.
- **Point-turn**: UpdateVelocityDesired scales `path_vector` (the
  along-track feed-forward) to zero while the yaw error exceeds 30 deg,
  ramping back in by 10 deg. The vehicle holds its place on the line,
  rotates, THEN flies the leg - which also removes the yaw/translation
  coupling (the NE->body rotation used by UpdateStabilizationDesired was
  previously changing under the velocity controller mid-leg).
- **Yaw command must be SLEWED, never stepped.** A hairpin steps the leg
  bearing ~144 deg; as a step it saturates the yaw loop for seconds and
  starves the mixer of roll/pitch authority - three consecutive
  tip-overs (65-81 deg) traced to exactly this, at several MaximumRate
  caps. vtolflycontroller slews the yaw COMMAND at 20 deg/s.
- **Saturation budget is the real yaw constraint**: yaw command ~=
  RateKp * MaximumRate.Yaw. Autotune's yaw Kp of 0.0416 at 90 deg/s
  demands 3.7x full actuator range. Keep RateKp * MaxRate <~ 0.4 so the
  mixer always retains roll/pitch headroom.

### Relay Autotune (resurrected - see SKILLS.md for how to run it)

flight/modules/Autotune + relay_tuning.c were amputated upstream in
Nov 2014 (OP-1588, present in the OpenPilot checkout's history). Both are
restored and modernized for 15.02 (banks, named-field structs, plus a YAW
relay state the original never had). Findings:

- Measured X3 (reproducible across two independent flights): roll
  113ms/77.2, pitch 155ms/37.5, yaw 560ms/10.2. The roll:pitch period
  ratio 1.37 matches sqrt(Iyy/Ixx)=1.42 from the model's own inertia
  tensor - an independent physics check that the numbers are real.
- **Yaw authority is ~8x weaker than roll** and ~5x slower. This is the
  root physical reason yaw-facing flight is hard on this airframe, and it
  is a property of the MODEL (momentConstant 0.016), not of the firmware.
- **The ZN gain derivation is too aggressive to use as-is.** Applying the
  autotuned rate gains wholesale (Ki 5-8x stock) produced violent
  along-leg oscillation and leg reversals. Reverted to stock rate PIDs.
  The DIAGNOSTIC value of the tune was the win, not its gain recipe.
- **Firmware ticks != wall clock.** The autotune state machine advances
  on FreeRTOS ticks while the bridge times windows on wall clock; the sim
  runs slower than real time, so each relay axis actually ran ~24s
  starting ~4-6s later than the bridge assumed. Consequence: the YAW
  measurement never converged (its gain was still climbing when the
  bridge landed) - treat the yaw numbers as a lower bound.


## Star-mission tuning: what is settled (2026-08-09, end of session)

Verified over three consecutive clean runs (star114/115/116), score.py on
the dense 100ms board log:

    cross-track  mean 0.12-0.15 m, p95 0.48-0.58, max 0.65-0.74
    arrival      closest approach 0.10-0.12 m to EVERY waypoint
    overshoot    0.01-0.04 m (the vehicle does not pass through the points)
    attitude     roll RMS 1.0-1.1 deg, pitch RMS 2.5-2.7 deg
    mission      115-123 s

Run-to-run noise is +/-0.03 m on the mean, so a 0.05 m "improvement" is not
real until the run is repeated. That rule has caught several false wins.

| knob | value | why not higher/lower |
|---|---|---|
| MISSION_SPEED | 1.5 m/s | delivered speed; see the cruise-speed note below |
| MISSION_WP_RADIUS | 1.0 m | FLY-THROUGH waypoints only |
| MISSION_WP_RADIUS_PRECISE | 0.15 m | corners; with confirm+dwell |
| MISSION_WP_RADIUS_3D | 0.35 m | vertical legs; 1.0 started the star 1m low |
| MISSION_CONFIRM_SPEED | 0.6 m/s | 0.4 rejected the best (first) pass |
| MISSION_DWELL_S | 0.3 s | every 0.1s costs 0.8s of mission time |
| HorizontalVelPID | [5.5, 0.5, 1.4, 15] | **Kp 7.0 tumbled it - see below** |
| HorizontalPosP | 0.35 | 0.60 is worse: 24 command reversals vs 9 |
| PATH_LEG_ACCEL | 0.8 | 1.2 + fast cruise destabilised the arrival |
| PATH_ARRIVAL_GAIN | 0.85 | 0.45 crawls the last metre for 9s |
| MaxRollPitch | 25 deg | at 40 the attitude loop overshot to 61 and tipped |
| CruiseControl | 1.25 / 40 deg | tilt-lift; off = 2.5x worse altitude |

### The two findings that produced almost all of the improvement

**1. The acceptance sphere was a FLY-THROUGH rule.** The plan retired a
waypoint the instant the vehicle clipped the sphere, so at a corner it turned
away a full radius short and never visited the point at all. Measured: closest
approach to all six star points was 0.86-1.15 m with a 1.0 m radius, 0.0 s
spent inside 0.5 m, and the vehicle never once passed a point. Corners now use
a tight sphere PLUS the confirm-speed/dwell arrival test in
`conditionDistanceToTarget` - which was already implemented and simply left
switched off. Fly-through waypoints keep the old rule; demanding a slow arrival
on a waypoint whose leg velocity is 1.5 m/s stalls the plan forever.

**2. The velocity loop had no damping.** See the SETTLED section at the top.

### Leg cruise speed is a MISSION property, not an endpoint property

`cruise = max(StartingVelocity, EndingVelocity)` means a leg can never outrun
its own endpoints. In the star every vertex is a 144 deg hairpin, so both ends
carried the slow corner speed and every 11.4 m leg crawled at it: a measured
**0.53 m/s median while MISSION_SPEED said 1.5**. Missions now state a leg
cruise speed in `ModeParameters[1]`, and corners arrive at a true stop
(EndingVelocity 0) instead of a nonzero speed that guaranteed overshoot.

### TRAP: ModeParameters is a union, and slot 0 is not free

`PATHDESIRED_MODEPARAMETER_GOTOENDPOINT_NEXTCOMMAND` is index **0**, and
`FLIGHTMODESETTINGS_RETURNTOBASENEXTCOMMAND_LAND` is **1**. vtolflycontroller
compared slot 0 against that enum WITHOUT checking the path mode, so a
FollowVector leg cruise speed of 1.5 m/s cast to `(uint8_t)1` and the vehicle
flew to its first waypoint and then deliberately landed itself mid-mission.
Guarded on mode now, and the FollowVector slots are named in plans.h. Slot 0 is
left permanently unused for FollowVector.

### A leg that starts stopped at its own Start cannot begin

`accel_lim = sqrt(v0^2 + 2*a*d_gone)` is exactly zero when both terms are, so
the profile commands no speed, the vehicle does not move, and `d_gone` never
grows. Hidden for as long as every waypoint carried a nonzero arrival velocity;
it appeared the moment corners became true stops AND a vertical climb waypoint
sat directly over the pad. It hung for 93 s without leaving the ground. Floored
at 0.05 m.

### Measurement discipline (three separate false conclusions came from this)

- decode_fcwd.py: the log filename packs `flight + 16*(slot/256)` in one
  byte. Misreading it as the flight discarded 3/4 of every log; one run
  "scored" 1.92 m on a 23s fragment that actually scored 0.25 m.
- accuracy.py: comparing mean radius across two DIFFERENT sample sets
  (bridge vs board) invented a 0.4 m "estimator bias" that does not
  exist. Paired on a shared clock the filter tracks its GPS input to
  0.020 m. Remaining path error is CONTROLLER error.
- A zero-length final leg (plan ends on two identical centre waypoints)
  reported landing drift as cross-track error.
- Change ONE variable per run. Star 38 changed radius AND accel together
  and the result was uninterpretable until both were isolated.

## Corner controller, tilt-lift, and the harness bug that faked a control bug (2026-08-09, later)

(Superseded - see the settled section above. Kept for the harness bug, the
tilt-lift measurements and the Gazebo GUI trap, which all still hold.)

### The harness bug FIRST - it invalidates any run it touched

`board_orientation_viz.py` opened a second UAVTalk client on the SAME UDP
telemetry port as the bridge. The firmware answers whichever client
contacted it last, so the two silently stole each other's packets: missions
that flew fine alone failed with runaways and ground contact whenever the
viewer was open, and NOTHING in the flight logs points at it - it reads as
a control bug. Three consecutive runs were lost, and a "vertical channel
destabilisation" was wrongly blamed on a controller constant.

The viewer is DELETED. Its configuration data survives as
`ground/pyuavtalk/flight_config.py`, which opens no sockets. If anything
ever reintroduces a second UAVTalk client on port 9000, expect exactly this
signature: healthy solo runs, inexplicable failures when the other tool is
open.

Related, same class: **marker publishing is a BLOCKING gz request**. Running
the mission supervision loop at 20Hz with 0.35m trail segments starved the
thread feeding sensors to the firmware and flew the vehicle into the ground.
The trail is cosmetic; it must never compete with flight-critical threads.
Settled at 10Hz / 0.5m / 50ms marker timeout.

**SUPERSEDED by tools/trail_daemon.py (2026-08-10): draw trails from a
separate PROCESS.** Rationing the trail (10Hz/0.5m) was a compromise, not a
fix - even off the guidance loop, a background THREAD still stalls it through
the GIL while marshalling each blocking /marker call (measured: intercept
closest approach 0.58 vs 1.91/2.19m with in-process trails on). A separate
process has its own GIL and its own core, so trails draw at full rate and the
flight loop never sees them. Measured over 3 star runs each: in-process
trails gave 0.04/0.05/0.08m mean cross-track with a 0.41m worst excursion
(intermittent starvation), the daemon gave a dead-flat 0.04 / 0.09m worst -
so the load WAS costing star consistency, not just intercept hit rate. The
daemon subscribes straight to Gazebo's pose stream and needs nothing from the
bridge. NINJAPILOT_MISSION_TRAIL_INPROC=0 hands the star's trail to it;
run_intercept.sh uses it unconditionally.

Two SILENT bugs that made the daemon look broken (both invisible from
outside, which is why it now prints a heartbeat with per-trail segment
counts):
  - Gazebo publishes the model as "x3" lowercase; matching "X3" drew nothing
    at all while the process looked perfectly healthy.
  - _marker_base stamps every marker "ninjapilot_trail", the exact namespace
    the bridge DELETE_ALLs at mission start - so the bridge wiped everything
    the daemon drew. Daemon markers now use "ninjapilot_daemon".
  - Also: _marker_tube expects GAZEBO ENU (the bridge's TargetTrail converts
    NED first: pt=(ned[1],ned[0],-ned[2])). The daemon handed it NED, drawing
    every segment mirrored and UNDERGROUND - invisible in flight, briefly
    clipping the surface as the ball fell. Fixed in Trail.tick.

### The corner controller is GONE - and it never ran

There was a block in vtolflycontroller.cpp that owned the whole corner
(APPROACH braking profile, bounded ARRIVE park, TURN, DEPART). It was gated on
`pathDesired->ModeParameters[3]`, which **nothing in the firmware ever set**,
so it had never executed once - `paths.c` was flying every corner all along.
Every conclusion recorded about "tuning the corner controller" was really about
the trapezoidal profile in paths.c.

The first flight in which it did run (once the planner started publishing the
bearing) stuck at waypoint 1, drifted 4.1 m past the point and swung altitude
over a 7.6 m range. The reason is structural: `progress` is shared with
`controlDown`, so rewriting `path_vector[0]/[1]` and `correction_vector[0]/[1]`
while leaving `[2]` and `fractional_progress` as path_progress computed them
hands the vertical controller an inconsistent path. It was **removed, not
disabled** - dead code that looks like the thing doing the work is worse than
no code.

Braking into a corner is owned by the leg speed profile in paths.c; stopping ON
the point is owned by the mission's confirmed-arrival policy. Those two produced
0.11 m mean arrival accuracy with that block inert.

### Tilt costs lift - CruiseControl is the missing term

`controlDown` reads only `path_vector[2]`/`correction_vector[2]`, which the
corner controller never writes, so vertical coupling is NOT in the code. It
is physical: braking into a corner needs tilt, and tilt costs lift by
cos(angle). A wider braking window means more time tilted:

    ARRIVE 0.6, CC off : 0.26 mean xtrack, alt p2p 0.59m
    ARRIVE 1.2, CC off : 0.23 mean xtrack, alt p2p 1.53m
    ARRIVE 1.2, CC on  : 0.23 mean xtrack, alt p2p 0.20m

CruiseControl multiplies thrust by 1/cos(tilt). Bounded at MaxPowerFactor
1.25 (covers ~37 deg, above the 25 deg MaxRollPitch) and MaxAngle 40 - past
that the vehicle is tumbling, not manoeuvring, and boosting thrust into a
tumble is why it was disabled originally.

### Lookahead: now used, for HEADING ONLY

pathplanner publishes the next leg's bearing in ModeParameters[2]/[3] (it did
not before - the code that read it was reading a slot nobody wrote). The
follower uses it to blend the yaw target as a smooth function of DISTANCE
REMAINING over the last 4 m, so the nose leads the corner in and is already on
the new bearing at the point.

Keying it to distance rather than ramping at a fixed rate matters: snapping the
target and letting the slew limiter grind through it at 35 deg/s produced a
visibly jagged S into every corner, because yaw rotates the NE->body mapping
and each rate step kicks translation sideways. Smoothstep makes the rotation
rate start and end at zero.

Yaw slew is a CEILING set by the airframe, not a preference. Relay autotune
measured yaw ultimate period at 560 ms against 114 ms for roll - yaw responds
~5x slower. 60 deg/s (star80) took yaw RMS from 8.4 to 15.3 deg and stretched
the mission to 169 s. 35 deg/s, with the distance blend doing the shaping.

### Dead ends in corner control - do NOT retry these

All measured, all reverted, all commented in the code:

  lead 1.0 -> 0.25s          overshoot 0.21 -> 0.95 m, 286 s. The lead IS the
                             braking cue; removing it removes the braking.
  lead clamped to d/2        same trade, milder: 0.69 m, 198 s.
  progress ratchet           drove progress regression to exactly 0.000 at
                             every waypoint and the orbit STAYED. Unclamped it
                             records the lead point's excursion past the
                             endpoint and drove the vehicle 14 m the wrong way;
                             clamped to the leg length it zeroes the along-track
                             position error and parks the vehicle 2.4 m short,
                             indefinitely.
  HorizontalVelPID Ki -> 0   ruled integrator windup out entirely.
  HorizontalPosP 0.35 -> 0.6 command reversals per corner 9 -> 24. Cross-track
                             is a perpendicular error so a stiffer line-hold
                             looks free, but the correction vector rotates as
                             the vehicle passes a waypoint, and near the point a
                             high gain on it fights the ARRIVAL, not the line.

The lesson: the command was never the problem, so every fix that reshaped the
command only changed the shape of the swing. `VelocityDesired` was not being
logged, which is why this took so long - without the commanded signal you
cannot tell a path that asks for an orbit from a vehicle that cannot fly a
clean request.

### Gazebo GUI

Declaring `<gui>` in the world **REPLACES** Gazebo's defaults, it does not
add to them. A hand-written short list dropped MarkerManager and the flight
trails vanished; a single-plugin block left the wind panel filling the whole
window. The world now embeds gz-sim's own `gui.config` verbatim and appends
only the wind panel (anchored top-right).
