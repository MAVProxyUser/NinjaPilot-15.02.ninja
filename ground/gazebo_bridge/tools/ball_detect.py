#!/usr/bin/env python3
"""Find the target ball in a camera frame and turn it into a BEARING.

Why bearing rather than position: a camera cannot measure range, but it
measures direction extremely well, and direction is what intercept guidance
actually needs. Proportional navigation consumes the LINE-OF-SIGHT RATE -
the rotation of the sightline - which is a pure angular quantity. Feeding it
a measured bearing removes every dependency the current guidance has on
being handed the object's position and on differencing that position for
velocity. It degrades gracefully with a noisy tracker and works against a
manoeuvring object, because it never predicts anything.

The ball is bright red-orange (emissive) against sky or farm, so a plain RGB
rule separates it without needing OpenCV:

    R clearly dominant, G and B both low

usage:
    ball_detect.py                     - live, prints bearings as it sees them
    ball_detect.py --once <topic>      - single frame, for checking thresholds
"""
import math
import sys
import time


def find_ball(buf, w, h):
    """Centroid of red-dominant pixels. Returns (u, v, npix) or None.

    Deliberately simple and dependency-free: this runs in the same process
    that feeds sensors to the firmware, and CLAUDE.md records what happens
    when that thread gets starved (the vehicle flew into the ground). A
    stride-4 scan over 640x480 is ~38k samples, cheap enough not to matter.
    """
    su = sv = n = 0
    stride = 4
    for y in range(0, h, stride):
        row = y * w * 3
        for x in range(0, w, stride):
            i = row + x * 3
            r = buf[i]
            g = buf[i + 1]
            b = buf[i + 2]
            if r > 110 and r > g * 2 and r > b * 2:
                su += x
                sv += y
                n += 1
    if n < 3:
        return None
    return (su / n, sv / n, n)


def pixel_to_bearing(u, v, w, h, hfov_rad):
    """Pixel -> (azimuth, elevation) in CAMERA frame, radians.

    Uses the pinhole relation with focal length derived from the horizontal
    FOV. Real work should read fx/fy/cx/cy from the camera's own
    camera_info topic instead - each camera publishes its own now, which is
    exactly why the topics are nested. This is the quick version for
    threshold checking.
    """
    fx = (w / 2.0) / math.tan(hfov_rad / 2.0)
    fy = fx                      # square pixels
    az = math.atan2(u - w / 2.0, fx)
    el = math.atan2(-(v - h / 2.0), fy)
    return az, el


def main():
    import gz.transport13 as gzt
    from gz.msgs10.image_pb2 import Image

    topic = "/X3/cam_up/image"
    hfov = 1.9198622            # cam_up, 110 deg
    if "--once" in sys.argv:
        i = sys.argv.index("--once")
        if i + 1 < len(sys.argv):
            topic = sys.argv[i + 1]
            if "fpv45" in topic:
                hfov = 1.7453293
            elif "down" in topic:
                hfov = 1.5707963

    seen = {"n": 0, "last": None}

    def on_image(msg):
        if not msg.data:
            return
        hit = find_ball(msg.data, msg.width, msg.height)
        seen["n"] += 1
        if hit is None:
            return
        u, v, npix = hit
        az, el = pixel_to_bearing(u, v, msg.width, msg.height, hfov)
        seen["last"] = (time.time(), az, el, npix)
        print("  frame %4d: ball at px(%6.1f,%6.1f) %4d px -> az %+6.1f deg "
              "el %+6.1f deg" % (seen["n"], u, v, npix,
                                 math.degrees(az), math.degrees(el)))

    node = gzt.Node()
    node.subscribe(Image, topic, on_image)
    print("watching %s (hfov %.0f deg)" % (topic, math.degrees(hfov)))
    t0 = time.time()
    while time.time() - t0 < (8.0 if "--once" in sys.argv else 60.0):
        time.sleep(0.2)
    if seen["last"] is None:
        print("  no ball seen in %d frames" % seen["n"])
    else:
        print("  last: az %+.1f el %+.1f (%d frames scanned)"
              % (math.degrees(seen["last"][1]),
                 math.degrees(seen["last"][2]), seen["n"]))


if __name__ == "__main__":
    main()
