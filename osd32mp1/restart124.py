import time, dronecan
node=dronecan.make_node("can0", node_id=127, bitrate=1000000)
mon=dronecan.app.node_monitor.NodeMonitor(node)
alloc=dronecan.app.dynamic_node_id.CentralizedServer(node,mon,database_storage="/home/root/dronecan_alloc.db")
t0=time.time()
while time.time()-t0<6: node.spin(1)

def read_compass(nid, label):
    got={}
    def cb(e):
        if e is None: return
        try:
            nm=e.response.name
            nm=nm.decode() if isinstance(nm,bytes) else str(nm)
            if "COMPASS_DEV_ID" in nm: got[nm.strip()]=str(e.response.value)
        except Exception: pass
    for i in range(120):
        node.request(dronecan.uavcan.protocol.param.GetSet.Request(index=i), nid, cb)
        node.spin(0.03)
    t=time.time()
    while time.time()-t<3: node.spin(1)
    print(f"  {label}: {got if got else 'no reply'}")

print("=== BEFORE restart ===")
read_compass(124, "node124 COMPASS_DEV_ID")

print("=== restarting node 124 ===")
try:
    node.request(dronecan.uavcan.protocol.RestartNode.Request(magic_number=0xACCE551B1E),
                 124, lambda e: None)
except Exception as ex:
    print("  restart request error:", ex)
t=time.time()
while time.time()-t<3: node.spin(1)

print("=== waiting 20s for it to come back ===")
t=time.time()
while time.time()-t<20: node.spin(1)
print(f"  node124 present again: {mon.exists(124)}")

print("=== AFTER restart ===")
read_compass(124, "node124 COMPASS_DEV_ID")

mags={}
def bump(e):
    n=e.transfer.source_node_id; mags[n]=mags.get(n,0)+1
node.add_handler(dronecan.uavcan.equipment.ahrs.MagneticFieldStrength, bump)
t=time.time()
while time.time()-t<8: node.spin(1)
print("  mag publishers in 8s:", mags)
