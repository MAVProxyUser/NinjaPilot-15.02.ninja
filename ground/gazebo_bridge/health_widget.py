#!/usr/bin/env python3
#
# health_widget.py - a small pinned-corner window replicating the GCS's
# System Health gadget (the real system-health.svg asset, same as
# board_orientation_viz.py uses) plus a live attitude readout, meant to sit
# next to the Gazebo view during a test run.
#
# This does NOT open its own UAVTalk connection to fw_simposix - it can't:
# fw_simposix's posix telemetry (flight/pios/posix/pios_udp.c) is a single
# UDP socket that remembers only the most recent sender as its reply
# target, so a second independent client sending packets to it would keep
# stealing gazebo_bridge.py's telemetry stream instead of getting its own
# (same class of bug CLAUDE.md already warns about for two threads sharing
# one socket). gazebo_bridge.py already has every value this needs -
# status_writer_loop() writes it to .fc_status.json at 10Hz - so this is
# just a tiny local HTTP server that serves the REAL system-health.svg
# asset (from the same diagrams dir board_orientation_viz.py reads) plus a
# page that polls that JSON file and recolors it with the exact same
# updateHealthSvg()/autoCropViewBox() JS board_orientation_viz.py already
# has (copied here rather than reimplemented, so it stays visually
# identical to the real GCS gadget).
#
# Run (while gazebo_bridge.py is already running):
#   /usr/bin/python3 health_widget.py
#
import http.server
import json
import os
import socket
import subprocess
import sys
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))
STATUS_FILE = os.path.join(HERE, ".fc_status.json")
# Same diagrams dir board_orientation_viz.py serves /diagrams/ from - the
# actual GCS-authored SVG assets, not a reimplementation of them.
DIAGRAM_DIR = os.path.join(HERE, "..", "openpilotgcs", "share", "openpilotgcs", "diagrams", "default")
HTTP_PORT = 8766  # board_orientation_viz.py's own dashboard defaults to 8765 - stay clear of it
WINDOW_W, WINDOW_H = 300, 560

INDEX_HTML = """<!doctype html>
<html><head><meta charset="utf-8"><title>NinjaPilot Health</title>
<style>
  html, body { margin: 0; padding: 0; background: #16181a; color: #ccc;
               font-family: Menlo, monospace; font-size: 12px; }
  #status { padding: 8px; font-weight: bold; text-align: center; }
  #healthsvg { width: 100%; background: #0b0d0e; }
  #healthsvg svg { width: 100%; height: auto; display: block; }
  #rpy { padding: 6px 8px; text-align: center; }
  #horizon { display: block; margin: 4px auto; background: #0b0d0e; border: 1px solid #333; }
</style></head>
<body>
<div id="status">connecting...</div>
<svg id="horizon" width="260" height="120" viewBox="0 0 260 120"></svg>
<div id="rpy">roll=--  pitch=--  yaw=--</div>
<div id="healthsvg">(loading system-health.svg...)</div>
<script>
// autoCropViewBox()/updateHealthSvg() copied verbatim from
// board_orientation_viz.py's own dashboard JS, not reimplemented, so this
// stays visually identical to the real GCS gadget it's replicating.
function autoCropViewBox(svg) {
  try {
    const box = svg.getBBox();
    if (box.width > 0 && box.height > 0) {
      const pad = Math.max(box.width, box.height) * 0.03;
      svg.setAttribute("viewBox",
        (box.x - pad) + " " + (box.y - pad) + " " + (box.width + pad * 2) + " " + (box.height + pad * 2));
    }
  } catch (e) { /* getBBox can throw if the svg isn't in a rendered document yet */ }
}

const ALARM_STATE_SUFFIXES = ["OK", "Warning", "Critical", "Error"];
let healthSvgRoot = null;
fetch("/diagrams/system-health.svg").then(r => r.text()).then(svgText => {
  const container = document.getElementById("healthsvg");
  container.innerHTML = svgText;
  healthSvgRoot = container.querySelector("svg");
  if (healthSvgRoot) {
    healthSvgRoot.removeAttribute("width");
    healthSvgRoot.removeAttribute("height");
    healthSvgRoot.querySelectorAll("text").forEach((t) => {
      if (t.textContent.trim() === "?") t.style.display = "none";
    });
    for (const id of ["BootFault-RebootRequired", "SystemConfiguration-BadThrottleOrCollectiveInputRange", "SystemConfiguration-FlightMode"]) {
      const el = healthSvgRoot.getElementById ? healthSvgRoot.getElementById(id) : null;
      if (el && el.parentElement) el.parentElement.style.display = "none";
    }
    autoCropViewBox(healthSvgRoot);
  }
}).catch(() => {
  document.getElementById("healthsvg").textContent = "(system-health.svg not available)";
});

function updateHealthSvg(alarmsFull) {
  if (!healthSvgRoot || !alarmsFull) return;
  for (const a of alarmsFull) {
    for (const suf of ALARM_STATE_SUFFIXES) {
      const el = healthSvgRoot.getElementById ? healthSvgRoot.getElementById(a.name + "-" + suf)
                                                : healthSvgRoot.querySelector("#" + CSS.escape(a.name + "-" + suf));
      if (el && el.parentElement) {
        el.parentElement.style.display = (suf === a.level) ? "inline" : "none";
      }
    }
  }
}

function drawHorizon(roll, pitch) {
  const svg = document.getElementById("horizon");
  const cx = 130, cy = 60;
  const py = Math.max(-40, Math.min(40, pitch * 1.5));
  const rad = roll * Math.PI / 180;
  const dx = Math.cos(rad) * 140, dy = Math.sin(rad) * 140;
  svg.innerHTML =
    '<line x1="' + (cx - dx) + '" y1="' + (cy + py + dy) + '" x2="' + (cx + dx) + '" y2="' + (cy + py - dy) +
    '" stroke="#2ecc71" stroke-width="3"/>' +
    '<circle cx="' + cx + '" cy="' + cy + '" r="3" fill="#e74c3c"/>' +
    '<line x1="' + (cx - 20) + '" y1="' + cy + '" x2="' + (cx - 8) + '" y2="' + cy + '" stroke="#e74c3c" stroke-width="2"/>' +
    '<line x1="' + (cx + 8) + '" y1="' + cy + '" x2="' + (cx + 20) + '" y2="' + cy + '" stroke="#e74c3c" stroke-width="2"/>';
}

function tick() {
  fetch("/status.json", {cache: "no-store"}).then(r => r.json()).then(s => {
    const statusEl = document.getElementById("status");
    if (s.error) {
      statusEl.textContent = s.error;
      statusEl.style.color = "#e74c3c";
      return;
    }
    statusEl.textContent = (s.armed ? "ARMED" : "disarmed") + "  mode=" + s.mode_position +
      (s.crashed ? "  CRASH: " + s.crash_reason : "");
    statusEl.style.color = s.armed ? "#e74c3c" : (s.crashed ? "#e74c3c" : "#888");
    drawHorizon(s.roll || 0, s.pitch || 0);
    document.getElementById("rpy").textContent =
      "roll=" + (s.roll || 0).toFixed(1) + "  pitch=" + (s.pitch || 0).toFixed(1) + "  yaw=" + (s.yaw || 0).toFixed(1);
    const names = s.alarm_names || [];
    const alarms = s.alarms || [];
    updateHealthSvg(names.map((n, i) => ({name: n, level: alarms[i]})));
  }).catch(() => {
    document.getElementById("status").textContent = "waiting for bridge...";
    document.getElementById("status").style.color = "#e74c3c";
  });
}
setInterval(tick, 150);
tick();
</script>
</body></html>
"""


class Handler(http.server.BaseHTTPRequestHandler):
    def log_message(self, fmt, *args):
        pass  # keep the terminal quiet - this polls at ~7Hz

    def do_GET(self):
        if self.path == "/" or self.path.startswith("/?"):
            body = INDEX_HTML.encode("utf-8")
            self.send_response(200)
            self.send_header("Content-Type", "text/html; charset=utf-8")
            self.send_header("Content-Length", str(len(body)))
            self.end_headers()
            self.wfile.write(body)
        elif self.path.startswith("/status.json"):
            try:
                with open(STATUS_FILE) as f:
                    body = f.read().encode("utf-8")
            except OSError:
                body = json.dumps({"error": "waiting for bridge... (.fc_status.json not found yet)"}).encode("utf-8")
            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.send_header("Content-Length", str(len(body)))
            self.end_headers()
            self.wfile.write(body)
        elif self.path.startswith("/diagrams/"):
            safe_name = os.path.basename(self.path.split("?", 1)[0])
            path = os.path.join(DIAGRAM_DIR, safe_name)
            if not os.path.isfile(path):
                self.send_error(404)
                return
            with open(path, "rb") as f:
                body = f.read()
            self.send_response(200)
            self.send_header("Content-Type", "image/svg+xml")
            self.send_header("Content-Length", str(len(body)))
            self.end_headers()
            self.wfile.write(body)
        else:
            self.send_error(404)


def find_free_port(preferred):
    for port in range(preferred, preferred + 20):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            if s.connect_ex(("127.0.0.1", port)) != 0:
                return port
    return preferred


def main():
    port = find_free_port(HTTP_PORT)
    server = http.server.ThreadingHTTPServer(("127.0.0.1", port), Handler)
    url = f"http://127.0.0.1:{port}/"
    print(f"[health_widget] serving {url}")
    threading.Thread(target=server.serve_forever, daemon=True).start()

    # A small, positioned Chrome app-mode window is the closest thing to a
    # "pinned corner widget" available without a native GUI toolkit - it
    # has no window chrome (no tabs/address bar) so it reads as a widget,
    # not a browser tab. Falls back to whatever the default browser does
    # with a plain URL if Chrome isn't installed.
    try:
        subprocess.Popen([
            "open", "-na", "Google Chrome", "--args",
            f"--app={url}", f"--window-size={WINDOW_W},{WINDOW_H}",
            "--window-position=1100,40",
        ])
    except OSError:
        import webbrowser
        webbrowser.open(url)

    try:
        while True:
            time.sleep(3600)
    except KeyboardInterrupt:
        server.shutdown()


if __name__ == "__main__":
    main()
