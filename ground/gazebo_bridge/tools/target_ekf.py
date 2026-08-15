#!/usr/bin/env python3
"""Six-state EKF on the target, fusing position fixes with camera bearings.

WHY THIS EXISTS, and why the first vision attempt lost to no vision at all.

The first cut treated the camera as a REPLACEMENT for the position feed: when
the ball was in frame, rotate the target direction to match the pixels and
keep the last-known range. That is a substitution, and it threw away the one
thing the camera is bad at (range) while adding a 55 MB/s frame load to the
process that feeds sensors to the firmware. Measured result was a regression -
closest approach 0.41-1.03m without vision, 1.03-2.35m with it.

A filter changes the economics completely, because the two measurements are
COMPLEMENTARY rather than competing:

  - the position channel (ground truth here, GPS/radar on real hardware) is
    absolutely informative about RANGE and weakly informative about fine
    bearing
  - the camera is exquisitely informative about BEARING and says nothing
    whatsoever about range

Fused, each one covers the other's blind spot. Substituted, whichever is
active discards what the other knew.

THE BEARING UPDATE CANNOT CORRUPT RANGE, and that property is structural
rather than tuned. The measurement is the unit line-of-sight vector
u = R/|R|, whose Jacobian is

    du/dR = (I - u u^T) / |R|

a rank-2 projector whose null space is exactly u itself. Any innovation along
the sightline maps to zero, so a bearing measurement can only ever move the
estimate PERPENDICULAR to the sightline. That is the correct physics for a
camera, it needs no gate or heuristic to enforce, and it is why the update is
written against the unit vector instead of (az, el): the angle pair has a
genuine singularity at the zenith, which is precisely where cam_up spends the
entire engagement.

WHAT THE FILTER BUYS BEYOND SMOOTHING - the lag. The measured miss on the
clean baseline was a repeatable 0.57-0.59m directly BEHIND the ball with
near-zero cross-track: a pure time lag of ~0.48s through sampling, transport
and the ~130ms attitude response. Adding a constant 0.45s to the firmware's
endgame lead was tried and made it worse (0.59m -> 1.25-1.32m over three
runs), because a constant added to a horizon that is itself range-dependent
over-leads exactly when range is shrinking fastest.

predict_ahead() does the principled version: propagate the STATE forward by
the lag through the same dynamics the filter already trusts, and hand the
firmware a target position that is honest about when it will be acted upon.
The compensation is then automatically correct at every range, and it degrades
gracefully - if the filter is uncertain, the covariance says so.

los_rate() exposes what proportional navigation actually consumes. PN steers
on the ROTATION of the sightline rather than on a predicted impact point, so
it self-corrects rather than re-deriving an aim point that is always stale.

References: Kalman 1960; the bearing-only tracking formulation and its
observability caveat (a non-manoeuvring observer cannot make range observable
from bearings alone - here the position channel supplies it) follow Aidala &
Hammel 1983.
"""
import math

import numpy as np


class TargetEKF:
    """Constant-velocity target in NED, measured by position and/or bearing.

    State x = [pn, pe, pd, vn, ve, vd].

    Nothing in here knows about Gazebo, the bridge, or the firmware - it takes
    measurements and returns estimates, so it can be unit-tested offline (see
    tools/test_target_ekf.py) rather than only in a 40-second flight.
    """

    def __init__(self, sigma_a=0.5, sigma_pos=0.35, sigma_ang_deg=1.2):
        # sigma_a: how hard the target might manoeuvre, m/s^2 (1-sigma). This
        # is the ONLY knob that trades tracking lag against noise. The balloon
        # flies straight, but sizing this for a real manoeuvre keeps the
        # filter honest when the target turns (TARGET_TURN_DEG exists for
        # exactly that test) - too small and the filter refuses to believe a
        # turn it is watching happen.
        #
        # 0.5 CHOSEN FROM A SWEEP, not from taste. Against a straight target
        # and against a 40 deg turn at t=6s, scoring the 0.48s-ahead
        # prediction (tools/test_target_ekf.py, GPS-grade 0.35m fixes):
        #
        #   sigma_a   straight    turn peak
        #     0.05      0.108       1.177     tracks noise-free, ignores turns
        #     0.20      0.153       0.877
        #     0.35      0.184       0.824
        #     0.50      0.211       0.792   <- knee
        #     0.80      0.258       0.788     turn no better, straight worse
        #     2.00      0.398       0.881     worse at both
        #
        # Turn error bottoms out on a 0.5-0.8 plateau, so 0.5 buys the whole
        # manoeuvre benefit at the smaller straight-line cost. 0.21m of
        # prediction error sits well inside the 0.582m contact geometry.
        # In-sim the position feed is far better than the 0.35m modelled
        # here, so these are pessimistic.
        self.sigma_a = float(sigma_a)
        self.R_pos = np.eye(3) * (float(sigma_pos) ** 2)
        self.sigma_ang = math.radians(float(sigma_ang_deg))
        self.x = None
        self.P = None
        self.t = None
        self.n_pos = 0
        self.n_brg = 0

    # ---- lifecycle ----------------------------------------------------

    def initialised(self):
        return self.x is not None

    def init(self, t, pos, vel=(0.0, 0.0, 0.0)):
        self.x = np.array([pos[0], pos[1], pos[2],
                           vel[0], vel[1], vel[2]], dtype=float)
        # Position is trusted at roughly the measurement noise; velocity is
        # NOT - it is seeded at zero (or a guess) and must be learned, so its
        # prior is deliberately loose. Seeding velocity confidently from a
        # single differenced pair is how a tracker locks onto a wrong course
        # and then rejects the fixes that would correct it.
        self.P = np.diag([1.0, 1.0, 1.0, 25.0, 25.0, 25.0])
        self.t = t

    def reset(self):
        self.x = None
        self.P = None
        self.t = None
        self.n_pos = 0
        self.n_brg = 0

    # ---- prediction ---------------------------------------------------

    @staticmethod
    def _F(dt):
        F = np.eye(6)
        F[0, 3] = F[1, 4] = F[2, 5] = dt
        return F

    def _Q(self, dt):
        # Standard piecewise-white constant-velocity process noise: an
        # unmodelled acceleration of sigma_a acting over dt.
        q = self.sigma_a ** 2
        dt2 = dt * dt
        dt3 = dt2 * dt
        dt4 = dt2 * dt2
        Q = np.zeros((6, 6))
        for i in range(3):
            Q[i, i] = q * dt4 / 4.0
            Q[i, i + 3] = Q[i + 3, i] = q * dt3 / 2.0
            Q[i + 3, i + 3] = q * dt2
        return Q

    def predict(self, t):
        """Advance the filter's own state to time t."""
        if self.x is None:
            return
        dt = t - self.t
        if dt <= 0.0:
            return
        # A long gap (dropped feed) is propagated in one step rather than
        # ignored - the covariance growth is what tells the guidance the
        # estimate has gone soft.
        F = self._F(dt)
        self.x = F @ self.x
        self.P = F @ self.P @ F.T + self._Q(dt)
        self.t = t

    # ---- measurement updates ------------------------------------------

    def update_position(self, z):
        """Linear KF update from a position fix (GPS/radar/ground truth)."""
        if self.x is None:
            return
        H = np.zeros((3, 6))
        H[0, 0] = H[1, 1] = H[2, 2] = 1.0
        self._update(np.asarray(z, dtype=float) - H @ self.x, H, self.R_pos)
        self.n_pos += 1

    def update_bearing(self, own_pos, u_meas):
        """EKF update from a measured unit LOS vector in NED.

        own_pos is where WE are; u_meas is the observed direction to the
        target. Returns the angular innovation in degrees (useful both as a
        health metric and as the thing to log when arguing that vision is
        actually contributing).
        """
        if self.x is None:
            return None
        R = self.x[0:3] - np.asarray(own_pos, dtype=float)
        r = float(np.linalg.norm(R))
        if r < 1e-3:
            return None
        u = R / r
        um = np.asarray(u_meas, dtype=float)
        nm = float(np.linalg.norm(um))
        if nm < 1e-6:
            return None
        um = um / nm

        # du/dR = (I - u u^T)/r. Rank 2, null space along u: a bearing can
        # never move the estimate along the sightline. See module docstring.
        H = np.zeros((3, 6))
        H[:, 0:3] = (np.eye(3) - np.outer(u, u)) / r

        y = um - u
        Rm = np.eye(3) * (self.sigma_ang ** 2)
        self._update(y, H, Rm)
        self.n_brg += 1
        # Angle between measured and predicted sightline.
        return math.degrees(math.acos(max(-1.0, min(1.0, float(np.dot(um, u))))))

    def _update(self, y, H, Rm):
        S = H @ self.P @ H.T + Rm
        try:
            K = self.P @ H.T @ np.linalg.inv(S)
        except np.linalg.LinAlgError:
            return
        self.x = self.x + K @ y
        # Joseph form: stays symmetric positive-definite under the repeated
        # asymmetric updates this filter gets (bearing at 20Hz, position at
        # 10Hz, both at varying rates). The naive (I-KH)P form has drifted
        # non-PSD in longer runs elsewhere in this project's filter work.
        I_KH = np.eye(6) - K @ H
        self.P = I_KH @ self.P @ I_KH.T + K @ Rm @ K.T

    # ---- outputs -------------------------------------------------------

    def state(self):
        """(pos, vel) as plain tuples at the filter's current time."""
        return (tuple(self.x[0:3]), tuple(self.x[3:6]))

    def predict_ahead(self, tau):
        """(pos, vel) tau seconds beyond the filter time - the lag comp.

        Deliberately does NOT advance the filter: this is a read-only look
        ahead for the command, so a change to the lag estimate can never
        corrupt the state itself.
        """
        p = self.x[0:3] + self.x[3:6] * tau
        return (tuple(p), tuple(self.x[3:6]))

    def pos_sigma(self):
        """1-sigma position uncertainty, m. Guidance can use this to decide
        whether the estimate deserves a commit."""
        return float(math.sqrt(max(0.0, self.P[0, 0] + self.P[1, 1] + self.P[2, 2])))

    def los_rate(self, own_pos, own_vel):
        """(omega_vec, closing_speed, range) - the inputs proportional
        navigation consumes.

        omega = (R x Rdot)/|R|^2 is the sightline's rotation vector; its
        magnitude is the LOS rate PN nulls, and closing speed scales the
        commanded acceleration. Returned rather than acted on, so the caller
        decides whether the firmware or the bridge does the steering.
        """
        R = self.x[0:3] - np.asarray(own_pos, dtype=float)
        Rd = self.x[3:6] - np.asarray(own_vel, dtype=float)
        r2 = float(np.dot(R, R))
        if r2 < 1e-6:
            return ((0.0, 0.0, 0.0), 0.0, 0.0)
        r = math.sqrt(r2)
        omega = np.cross(R, Rd) / r2
        closing = -float(np.dot(R, Rd)) / r
        return (tuple(omega), closing, r)
