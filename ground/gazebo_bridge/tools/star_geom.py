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
