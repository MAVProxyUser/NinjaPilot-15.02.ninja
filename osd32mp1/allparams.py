import time, dronecan
node=dronecan.make_node("can0", node_id=127, bitrate=1000000)
mon=dronecan.app.node_monitor.NodeMonitor(node)
alloc=dronecan.app.dronecan_alloc if False else dronecan.app.dynamic_node_id.CentralizedServer(node,mon,database_storage="/home/root/dronecan_alloc.db")
params={}
t0=time.time()
while time.time()-t0<6: node.spin(1)
nodes=[n for n in range(1,128) if mon.exists(n)]
def pcb(nid):
    def cb(e):
        if e is None: return
        try:
            nm=e.response.name
            nm=nm.decode() if isinstance(nm,bytes) else str(nm)
            if nm.strip():
                v=str(e.response.value).replace("uavcan.protocol.param.Value(","").rstrip(")")
                params.setdefault(nid,{})[nm.strip()]=v
        except Exception: pass
    return cb
for nid in nodes:
    for i in range(140):
        try:
            node.request(dronecan.uavcan.protocol.param.GetSet.Request(index=i), nid, pcb(nid))
            node.spin(0.03)
        except Exception: pass
t0=time.time()
while time.time()-t0<5: node.spin(1)
for nid in sorted(params):
    print(f"\n########## node {nid} : {len(params[nid])} params ##########")
    for k in sorted(params[nid]):
        print(f"  {k} = {params[nid][k]}")
