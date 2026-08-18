import dronecan, time, queue as _queue
from dronecan.driver.socketcan import SocketCAN as _SocketCAN
from dronecan.app.file_server import FileServer

def _bsf(self, frame):
    self._check_write_feedback()
    while True:
        try:
            self._write_queue.put(frame, timeout=2.0); return
        except _queue.Full:
            continue
_SocketCAN.send_frame = _bsf

stats={"n":0,"max":0,"eof":0,"last":0.0}
_orig=FileServer._read
def cread(self, e):
    stats["n"]+=1; stats["last"]=time.time()
    try: stats["max"]=max(stats["max"], int(e.request.offset))
    except Exception: pass
    r=_orig(self, e)
    try:
        if len(r.data)==0: stats["eof"]+=1
    except Exception: pass
    return r
FileServer._read=cread

node=dronecan.make_node("can0", node_id=126, bitrate=1000000)
fs=FileServer(node, lookup_paths=["/home/root/fw"])
modes=[]
def on_status(e):
    if e.transfer.source_node_id==124:
        m=e.message.mode
        if not modes or modes[-1]!=m:
            modes.append(m)
            print("  [%4.0fs] node124 mode -> %d" % (time.time()-t0, m), flush=True)
node.add_handler(dronecan.uavcan.protocol.NodeStatus, on_status)

t0=time.time()
req=dronecan.uavcan.protocol.file.BeginFirmwareUpdate.Request(source_node_id=126,
    image_file_remote_path=dronecan.uavcan.protocol.file.Path(path="AP_Periph.bin"))
try: node.request(req, 124, lambda e: None)
except Exception: pass

served_at=None; lastp=0
while time.time()-t0 < 600:
    try: node.spin(0.2)
    except Exception: pass
    if stats["max"]>=178236 and served_at is None:
        served_at=time.time(); print("  [%4.0fs] FULL IMAGE SERVED - holding server open for the EOF handshake" % (served_at-t0), flush=True)
    if time.time()-lastp>20:
        lastp=time.time()
        print("  [%4.0fs] reads=%d maxoff=%d eof=%d mode=%s" % (time.time()-t0, stats["n"], stats["max"], stats["eof"], modes[-1] if modes else "?"), flush=True)
    if modes and modes[-1]==0:
        print("  [%4.0fs] *** node124 OPERATIONAL - app booted ***" % (time.time()-t0), flush=True); break
    if served_at and time.time()-served_at > 120: 
        print("  served+120s, mode still", modes[-1] if modes else "?", flush=True); break
print("FINAL reads=%d maxoff=%d eof=%d modes=%s" % (stats["n"], stats["max"], stats["eof"], modes))
