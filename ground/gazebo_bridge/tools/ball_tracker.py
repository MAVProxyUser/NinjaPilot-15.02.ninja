#!/usr/bin/env python3
"""Vision lock on the target, per the operator's policy:

  - ONLY the up and 45-deg-forward cameras are used (never the down camera).
  - Vision drives guidance ONLY while the ball is actually in frame.
  - The instant it leaves frame, the caller falls straight back to the
    legacy solution (lead the last-known ground-truth / GPS location).

ARCHITECTURE - why this needs no firmware change. The bridge already feeds
the firmware a target POSITION (PathDesired.End) plus velocity. A camera
measures DIRECTION, not range. So when the ball is visually acquired, we
keep the last-known RANGE from the legacy estimate and rotate the target
direction to match what the camera sees - the End point the firmware chases
becomes "along the measured bearing, at the dead-reckoned range". Firmware
guidance is identical; vision only sharpens the direction while it can see.
When the ball drops out of frame, the bearing is stale, so we hand the whole
estimate back to legacy. Vision when visible, dead-reckon otherwise.

In THIS simulator the legacy path is perfect ground truth, so vision cannot
beat it here - the value is exercising the real-hardware architecture, where
legacy is noisy GPS and a direct bearing genuinely helps. The handoff is
logged loudly (VISION LOCK / lost) so it can be seen working.

Runs in the sensor-feeding process, so detection is dependency-free and
stride-sampled: a blocking OpenCV call on that thread has flown the vehicle
into the ground before (see CLAUDE.md).
"""
import math
import threading
import time


# Camera intrinsics: horizontal FOV (rad) per the model SDF. Down is
# intentionally absent - it is not part of the targeting policy.
CAMERAS = {
    "cam_up":    {"topic": "/X3/cam_up/image",    "hfov": 1.9198622},
    "cam_fpv45": {"topic": "/X3/cam_fpv45/image",  "hfov": 1.7453293,
                  "tilt": math.radians(45.0)},   # 45 deg up from body +X
}

# A frame older than this is "out of frame" even if the last one had a hit,
# so a stalled camera can never keep a stale lock alive.
LOCK_TIMEOUT_S = 0.30
# Margin (fraction of half-width) inside the frame edge that still counts as
# "in frame" - a ball touching the very edge is about to leave and its
# centroid is unreliable, so we release early rather than track it out.
EDGE_MARGIN = 0.08


def _find_ball(buf, w, h):
    """Centroid of red-dominant pixels -> (u, v, npix) or None."""
    su = sv = n = 0
    stride = 4
    for y in range(0, h, stride):
        base = y * w * 3
        for x in range(0, w, stride):
            i = base + x * 3
            r = buf[i]
            if r > 110 and r > buf[i + 1] * 2 and r > buf[i + 2] * 2:
                su += x
                sv += y
                n += 1
    if n < 3:
        return None
    return (su / n, sv / n, n)


class BallTracker:
    """Subscribes to the up/45 cameras and exposes the freshest in-frame
    bearing. Thread-safe; the guidance loop just calls lock()."""

    def __init__(self, node):
        self._lock = threading.Lock()
        self._best = None      # (t, cam, az_body, el_body, npix)
        try:
            import gz.transport13 as gzt
            from gz.msgs10.image_pb2 import Image
        except Exception as e:
            print(f"[vision] transport unavailable ({e}); vision disabled")
            return
        for name, cfg in CAMERAS.items():
            node.subscribe(Image, cfg["topic"],
                           self._make_cb(name, cfg))
            print(f"[vision] watching {name} ({cfg['topic']})")

    def _make_cb(self, name, cfg):
        hfov = cfg["hfov"]
        tilt = cfg.get("tilt", math.radians(90.0) if name == "cam_up" else 0.0)

        def cb(msg):
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
            # Pixel -> camera-frame az/el (pinhole).
            fx = (w / 2.0) / math.tan(hfov / 2.0)
            az = math.atan2(u - w / 2.0, fx)
            el = math.atan2(-(v - h / 2.0), fx)
            # Fold the camera's fixed mount tilt into an elevation relative to
            # the body: cam_up looks +90 el, fpv45 looks +45. The az stays a
            # body-relative azimuth.
            el_body = el + tilt
            rec = (time.time(), name, az, el_body, npix)
            with self._lock:
                # Prefer the detection with more pixels (nearer / clearer).
                if (self._best is None
                        or npix >= self._best[4]
                        or time.time() - self._best[0] > LOCK_TIMEOUT_S):
                    self._best = rec
        return cb

    def lock(self):
        """Return (cam, az_body, el_body, npix) if the ball is in frame and
        fresh, else None. az/el are body-relative radians."""
        with self._lock:
            b = self._best
        if b is None or (time.time() - b[0]) > LOCK_TIMEOUT_S:
            return None
        return (b[1], b[2], b[3], b[4])
