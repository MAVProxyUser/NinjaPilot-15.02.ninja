#!/usr/bin/env python3
"""The star mission's waypoint geometry, in flown order.

Single source of truth. This used to be copy-pasted into star_plot.py,
wp_arrival.py and the yaw block of analyze_run.sh, which meant any change to
the mission silently invalidated whichever copies were not updated - the
analysis would keep scoring against a shape the vehicle was no longer being
asked to fly, and would look plausible while doing it.

Must stay in step with build_mission() in gazebo_bridge.py.
"""
import math

# Outer points every 72deg from North, radius 6m.
_P = [(6.0 * math.cos(math.radians(72 * k)),
       6.0 * math.sin(math.radians(72 * k))) for k in range(5)]

# Flown order:
#   centre      - vertical climb to mission altitude before going anywhere
#   0,2,4,1,3,0 - the traversal that actually draws a star (visiting the
#                 points in ring order would draw a pentagon)
#   centre      - return, then the same point again carrying the Land action
#                 (plans wrap around, so a mission must terminate in a Land)
ORDER = [(0.0, 0.0)]
ORDER += [_P[k] for k in [0, 2, 4, 1, 3, 0]]
ORDER += [(0.0, 0.0), (0.0, 0.0)]

# The star outline alone, for plotting the planned shape.
OUTLINE = [_P[k] for k in [0, 2, 4, 1, 3, 0]]


# ---------------------------------------------------------------------------
# Fillet-corner plan: each star vertex becomes (tangent-entry, arc-centre).
#
# WHY ARCS: a point-attractor follower has no turn direction. Measured with
# yaw-following disabled (star130), identical right-hand corners split 2/6
# right vs 4/6 left (+~200 deg loops) - the handedness was decided by which
# side of the vertex the vehicle happened to clip. A CircleRight segment
# makes the direction a property of the PATH: the follower is handed a
# clockwise arc and cannot loop left around it.
#
# Conventions (read from paths.c / pathplanner.c, 2026-08-09):
#   - Circle waypoint POSITION is the arc CENTRE; the radius is the distance
#     from the PREVIOUS waypoint (our tangent-entry) to the centre.
#   - The arc ends via PointingTowardsNext: when the velocity direction is
#     within ConditionParameters[0] degrees of the bearing to the NEXT
#     waypoint - which is the next corner's tangent-entry, i.e. the new leg.
#
# MISS is how far the arc passes from the true vertex (user accepted ~0.5m:
# "overshooting a little is fine"). r and the tangent distance d follow from
# the corner's interior angle:  dist(vertex, centre) = r/sin(I/2) = r + MISS.
MISS = 0.5


def _unit(a, b):
    dn, de = b[0] - a[0], b[1] - a[1]
    L = math.hypot(dn, de)
    return (dn / L, de / L)


def fillet_plan(miss=MISS):
    """The star mission as flown with arc corners. Returns a list of dicts:
    kind in {climb, entry, arc, home, land}, pos (N,E,D), vel, and for arcs
    the direction ('CircleRight'/'CircleLeft') and radius."""
    home = (0.0, 0.0)
    route = [home] + OUTLINE + [home]
    out = [{"kind": "climb", "pos": (0.0, 0.0, -8.0), "vel": 0.35}]
    for i in range(1, len(route) - 1):
        vp, v, vn = route[i - 1], route[i], route[i + 1]
        uin = _unit(vp, v)
        uout = _unit(v, vn)
        cosI = -(uin[0] * uout[0] + uin[1] * uout[1])
        half = math.acos(max(-1.0, min(1.0, cosI))) / 2.0
        r = miss / (1.0 / math.sin(half) - 1.0)
        d = r / math.tan(half)
        t_in = (v[0] - uin[0] * d, v[1] - uin[1] * d)
        t_out = (v[0] + uout[0] * d, v[1] + uout[1] * d)
        bis = (uout[0] - uin[0], uout[1] - uin[1])
        bl = math.hypot(*bis)
        bis = (bis[0] / bl, bis[1] / bl)
        c = (v[0] + bis[0] * (r + miss), v[1] + bis[1] * (r + miss))
        # the construction must be self-consistent or everything downstream
        # is garbage: the centre is exactly r from both tangent points
        assert abs(math.hypot(c[0] - t_in[0], c[1] - t_in[1]) - r) < 1e-6
        assert abs(math.hypot(c[0] - t_out[0], c[1] - t_out[1]) - r) < 1e-6
        # handedness in the PLOT frame (x=E, y=N): + = counter-clockwise/left
        turn = math.degrees(math.atan2(uin[1] * uout[0] - uin[0] * uout[1],
                                       uin[1] * uout[1] + uin[0] * uout[0]))
        arcdir = "CircleLeft" if turn > 0 else "CircleRight"
        v_arc = min(0.45, math.sqrt(1.0 * r))
        out.append({"kind": "entry", "pos": (t_in[0], t_in[1], -8.0), "vel": v_arc})
        out.append({"kind": "arc", "pos": (c[0], c[1], -8.0), "vel": v_arc,
                    "dir": arcdir, "radius": r})
    out.append({"kind": "home", "pos": (0.0, 0.0, -8.0), "vel": 0.35})
    out.append({"kind": "land", "pos": (0.0, 0.0, -8.0), "vel": 0.35})
    return out
