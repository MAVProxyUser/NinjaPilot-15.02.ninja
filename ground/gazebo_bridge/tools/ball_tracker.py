#!/usr/bin/env python3
"""Vision lock on the target, per the operator's policy:

  - ONLY the up and 45-deg-forward cameras are used (never the down camera).
  - Vision contributes ONLY while the ball is actually in frame.
  - The instant it leaves frame, guidance runs on the legacy solution alone
    (lead the last-known ground-truth / GPS location).

WHAT CHANGED, and why the first version lost. Originally this fed guidance
directly: rotate the target direction onto the measured bearing, keep the
last-known range. That is a SUBSTITUTION - while vision was up it discarded
what the position channel knew about range, and when vision dropped out the
handoff was a step change. It also subscribed to two 640x480 30Hz RGB topics
(~55 MB/s) inside the process that feeds sensors to the firmware, which is
the failure class CLAUDE.md records twice. Measured result was a regression:
0.41-1.03m closest approach without vision, 1.03-2.35m with it.

Now it emits a MEASUREMENT and nothing else - a unit line-of-sight vector in
the body frame - which tools/target_ekf.py fuses with the position channel.
Two things fall out of that:

  - the bearing update's Jacobian is a rank-2 projector orthogonal to the
    sightline, so vision can sharpen DIRECTION and is structurally incapable
    of corrupting RANGE. Fusion instead of substitution.
  - dropout is no longer a handoff. The filter simply stops getting bearing
    updates and coasts on the position channel, and its covariance says how
    much confidence that cost. The operator's in-frame-only policy is
    enforced exactly as stated, without a cliff at the boundary.

BEARING IS A FULL RAY, NOT AN ANGLE PAIR. The previous version folded the
camera's mount tilt in as a scalar added to elevation (el_body = el + tilt).
That is only correct on the optical axis; off-axis it is wrong by an amount
that grows with azimuth - and cam_up, pitched 90 deg, spends an entire
engagement off-axis. The pixel is now converted to a ray in the camera
frame, rotated by the mount pose, and converted FLU->FRD, so the result is a
true body-frame direction at any pixel.

Detection is dependency-free and stride-sampled: a blocking OpenCV call on
this thread has flown the vehicle into the ground before (see CLAUDE.md).
"""
import math
import threading
import time


# The tracker cameras are 160x120 at 20Hz - see the model SDF comment for why
# the bridge must not subscribe to the 640x480 FPV feeds. Same poses and FOVs
# as cam_up / cam_fpv45, so the geometry below is shared.
#
# `pitch` is the mount rotation from the SDF <pose> (roll and yaw are zero on
# both), in the model's FLU frame: -90 deg looks straight up, -45 deg looks
# forward and up at 45.
CAMERAS = {
    "track_up": {"topic": "/X3/cam_track_up/image", "hfov": 1.9198622,
                 "pitch": -1.5707963},
    "track_45": {"topic": "/X3/cam_track_45/image", "hfov": 1.7453293,
                 "pitch": -0.7853982},
}

# A frame older than this is "out of frame" even if the last one had a hit,
# so a stalled camera can never keep a stale lock alive.
LOCK_TIMEOUT_S = 0.30
# Margin (fraction of half-width) inside the frame edge that still counts as
# "in frame" - a ball touching the very edge is about to leave and its
# centroid is unreliable, so we release early rather than track it out.
EDGE_MARGIN = 0.08
# Minimum red pixels for a detection. At 160x120 the ball is a 44-63 px blob
# and the stride-2 scan sees a quarter of that, so 3 is still generous
# headroom while rejecting single-pixel noise.
MIN_PIXELS = 3


def _find_ball(buf, w, h, stride=2):
    """Centroid of red-dominant pixels -> (u, v, npix) or None.

    The ball is emissive red-orange against sky or farm, so a plain RGB
    dominance rule separates it without OpenCV. Stride is 2 rather than 4
    because the tracker frames are already 16x smaller in area.
    """
    su = sv = n = 0
    for y in range(0, h, stride):
        base = y * w * 3
        for x in range(0, w, stride):
            i = base + x * 3
            r = buf[i]
            if r > 110 and r > buf[i + 1] * 2 and r > buf[i + 2] * 2:
                su += x
                sv += y
                n += 1
    if n < MIN_PIXELS:
        return None
    return (su / n, sv / n, n)


def _pixel_to_body_ray(u, v, w, h, hfov, pitch):
    """(u,v) pixel -> unit direction in the body FRD frame.

    Three steps, each of which was wrong or implicit in the previous version:

    1. Pixel to a ray in the CAMERA frame. Gazebo's camera convention is
       +X along the optical axis, +Y left, +Z up - so a pixel right of
       centre is -Y and a pixel below centre is -Z.
    2. Rotate by the mount pose. Both cameras are pure pitch in the model's
       FLU frame, so this is R_y(pitch).
    3. FLU -> FRD (negate Y and Z), because the vehicle attitude quaternion
       the bridge carries is FRD-body-to-NED-world.
    """
    fx = (w / 2.0) / math.tan(hfov / 2.0)      # square pixels, fy == fx
    x_c = 1.0
    y_c = -(u - w / 2.0) / fx
    z_c = -(v - h / 2.0) / fx
    n = math.sqrt(x_c * x_c + y_c * y_c + z_c * z_c)
    x_c, y_c, z_c = x_c / n, y_c / n, z_c / n

    cp, sp = math.cos(pitch), math.sin(pitch)
    # R_y(pitch) applied to the camera ray, in FLU.
    x_f = cp * x_c + sp * z_c
    y_f = y_c
    z_f = -sp * x_c + cp * z_c

    return (x_f, -y_f, -z_f)                    # FLU -> FRD


class BallTracker:
    """Subscribes to the tracker cameras and exposes the freshest in-frame
    line-of-sight ray. Thread-safe; the guidance loop just calls lock()."""

    def __init__(self, node):
        self._lock = threading.Lock()
        self._best = None      # (t, cam, ray_frd, npix)
        self.frames = 0
        self.detections = 0
        try:
            from gz.msgs10.image_pb2 import Image
        except Exception as e:
            print(f"[vision] transport unavailable ({e}); vision disabled")
            return
        for name, cfg in CAMERAS.items():
            node.subscribe(Image, cfg["topic"], self._make_cb(name, cfg))
            print(f"[vision] watching {name} ({cfg['topic']})")

    def _make_cb(self, name, cfg):
        hfov = cfg["hfov"]
        pitch = cfg["pitch"]

        def cb(msg):
            self.frames += 1
            if not msg.data or msg.width == 0:
                return
            hit = _find_ball(msg.data, msg.width, msg.height)
            if hit is None:
                return
            u, v, npix = hit
            w, h = msg.width, msg.height
            # Release early near the edge - centroid unreliable, about to exit.
            mx = EDGE_MARGIN * w
            my = EDGE_MARGIN * h
            if u < mx or u > w - mx or v < my or v > h - my:
                return
            ray = _pixel_to_body_ray(u, v, w, h, hfov, pitch)
            self.detections += 1
            rec = (time.time(), name, ray, npix)
            with self._lock:
                # Prefer the detection with more pixels (nearer / clearer),
                # unless the incumbent has gone stale.
                if (self._best is None
                        or npix >= self._best[3]
                        or time.time() - self._best[0] > LOCK_TIMEOUT_S):
                    self._best = rec
        return cb

    def lock(self):
        """Return (cam, ray_frd, npix, age_s) if the ball is in frame and
        fresh, else None. ray_frd is a unit vector in the body FRD frame."""
        with self._lock:
            b = self._best
        if b is None:
            return None
        age = time.time() - b[0]
        if age > LOCK_TIMEOUT_S:
            return None
        return (b[1], b[2], b[3], age)
