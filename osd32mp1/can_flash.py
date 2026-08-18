import dronecan, time

# TRAP (root-caused 2026-08-18, after this flasher failed 3x in a row):
# python-dronecan's SocketCAN driver treats a FULL internal TX queue as a
# FATAL error - send_frame() raises TxQueueFullError instead of applying
# backpressure. During a flash the bootloader's read requests outpace the
# writer thread's drain and the transfer dies partway through (measured
# 119-203 s in). It is NOT the wire (berr-counter tx 0 rx 0, zero TX
# errors/drops) and NOT the interface txqueuelen (10 -> 1000 changed
# nothing). Block until there is room instead of exploding; the writer
# thread already retries ENOBUFS on its own.
import queue as _queue
from dronecan.driver.socketcan import SocketCAN as _SocketCAN


def _blocking_send_frame(self, frame):
    self._check_write_feedback()
    while True:
        try:
            self._write_queue.put(frame, timeout=2.0)
            return
        except _queue.Full:
            continue


_SocketCAN.send_frame = _blocking_send_frame

node = dronecan.make_node("can0", node_id=126, bitrate=1000000)
NID = 124
t0 = time.time()
modes = []
def on_status(e):
    if e.transfer.source_node_id == NID:
        m = e.message.mode
        if not modes or modes[-1][1] != m:
            modes.append((time.time(), m))
            print("  [%3.0fs] node 124 mode -> %d (0=OK 1=INIT 2=MAINT 3=SW_UPDATE)"
                  % (time.time()-t0, m), flush=True)
node.add_handler(dronecan.uavcan.protocol.NodeStatus, on_status)

def safe_spin(dt):
    try:
        node.spin(dt)
    except Exception:
        pass                      # wire noise must never kill the file server

def nodeinfo(label):
    out = []
    try:
        node.request(dronecan.uavcan.protocol.GetNodeInfo.Request(), NID,
                     lambda e: out.append(e) if e else None)
    except Exception:
        pass
    t = time.time()
    while not out and time.time()-t < 4:
        safe_spin(0.05)
    if out:
        r = out[0].response
        nm = "".join(chr(c) for c in r.name)
        sw = r.software_version
        print("  %s %s  sw %u.%u vcs=%08x" % (label, nm, sw.major, sw.minor,
              sw.vcs_commit), flush=True)
        return sw.vcs_commit
    print("  %s NO RESPONSE" % label, flush=True)
    return None

# RECOVERY: is 124 sitting in the bootloader, the old app, or silent?
pre = nodeinfo("STATE NOW:")

# The image MUST be staged at /home/root/fw/AP_Periph.bin - this server
# serves from that directory only. Staging it in /home/root (one level up)
# silently serves a STALE file: the node dutifully re-flashes whatever old
# image is there and the operator sees "flash succeeded, still broken".
fs = dronecan.app.file_server.FileServer(node, lookup_paths=["/home/root/fw"])

# (re)issue the update request - harmless if already in bootloader
req = dronecan.uavcan.protocol.file.BeginFirmwareUpdate.Request(
    source_node_id=126,
    image_file_remote_path=dronecan.uavcan.protocol.file.Path(path="AP_Periph.bin"))
resp = []
try:
    node.request(req, NID, lambda e: resp.append(e) if e else None)
except Exception:
    pass
t = time.time()
while not resp and time.time()-t < 6:
    safe_spin(0.05)
print("  BeginFirmwareUpdate:", resp[0].response.error if resp else "no ack (ok if already in bootloader)", flush=True)

# 240 s was TOO SHORT: a complete image transfer measured 222 s of pure
# file serving (800 Read requests for 178 KB, ~800 B/s effective), so the
# old deadline killed the file server just before the end and the node was
# left parked in the bootloader. Instrumented proof in can_flash_verbose.py.
deadline = time.time() + 420
saw_update = False
while time.time() < deadline:
    safe_spin(0.5)
    if any(m == 3 for _, m in modes):
        saw_update = True
    if saw_update and modes and modes[-1][1] == 0 and time.time()-modes[-1][0] > 6:
        break
print("  SW_UPDATE observed:", saw_update, flush=True)
time.sleep(2)
post = nodeinfo("AFTER:    ")
if post is not None and pre is not None:
    print("  VERDICT: vcs %08x -> %08x  %s" % (pre, post,
          "CHANGED - FLASH SUCCEEDED" if post != pre else "unchanged"), flush=True)
