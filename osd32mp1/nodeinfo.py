import time, dronecan
node = dronecan.make_node('can0', node_id=127, bitrate=1000000)
mon = dronecan.app.node_monitor.NodeMonitor(node)
alloc = dronecan.app.dynamic_node_id.CentralizedServer(node, mon,
            database_storage='/home/root/dronecan_alloc.db')
info, params, mag = {}, {}, {}

def ni_cb(nid):
    def cb(e):
        if e is None: return
        r = e.response
        nm = r.name.decode() if isinstance(r.name, bytes) else str(r.name)
        info[nid] = dict(name=nm,
                         hw="%d.%d" % (r.hardware_version.major, r.hardware_version.minor),
                         sw="%d.%d" % (r.software_version.major, r.software_version.minor),
                         uid=bytes(r.hardware_version.unique_id).hex())
    return cb

def collect_mag(e):
    mag.setdefault(e.transfer.source_node_id, []).append(tuple(e.message.magnetic_field_ga))
node.add_handler(dronecan.uavcan.equipment.ahrs.MagneticFieldStrength, collect_mag)

t0=time.time()
while time.time()-t0 < 10: node.spin(1)
seen = sorted(set(list(mag.keys()) + [n for n in range(1,128) if mon.exists(n)]))
for nid in seen:
    try: node.request(dronecan.uavcan.protocol.GetNodeInfo.Request(), nid, ni_cb(nid))
    except Exception: pass
t0=time.time()
while time.time()-t0 < 6: node.spin(1)

def pcb(nid):
    def cb(e):
        if e is None: return
        try:
            nm = e.response.name
            nm = nm.decode() if isinstance(nm, bytes) else str(nm)
            if not nm.strip(): return
            params.setdefault(nid, []).append((nm.strip(), str(e.response.value).strip().replace("\n"," ")))
        except Exception: pass
    return cb
for nid in sorted(info):
    for i in range(80):
        try:
            node.request(dronecan.uavcan.protocol.param.GetSet.Request(index=i), nid, pcb(nid))
            node.spin(0.03)
        except Exception: pass
t0=time.time()
while time.time()-t0 < 5: node.spin(1)

print("=== node info ===")
for nid, d in sorted(info.items()):
    print(f"  node {nid}: {d['name']}")
    print(f"      hw {d['hw']}  sw {d['sw']}  uid {d['uid'][:24]}")
print("\n=== params matching COMPASS/MAG/GPS ===")
for nid, ps in sorted(params.items()):
    hits=[(n,v) for n,v in ps if any(k in n.upper() for k in ('COMPASS','MAG','GPS'))]
    print(f"  node {nid}: {len(ps)} params total, {len(hits)} matching")
    for n,v in hits[:20]: print(f"      {n} = {v}")
print("\n=== magnetometer statistics ===")
for nid, s in sorted(mag.items()):
    n=len(s)
    if n<20: continue
    means=[sum(a[i] for a in s)/n for i in range(3)]
    sd=[(sum((a[i]-means[i])**2 for a in s)/n)**0.5 for i in range(3)]
    magn=(sum(m*m for m in means))**0.5
    print(f"  node {nid}: n={n} over 10s -> {n/10:.0f} Hz")
    print(f"      mean  [{means[0]:+.4f} {means[1]:+.4f} {means[2]:+.4f}] gauss   |B| = {magn*100:.2f} uT")
    print(f"      sigma [{sd[0]*1e3:.4f} {sd[1]*1e3:.4f} {sd[2]*1e3:.4f}] milligauss")
    print(f"      i.e.  [{sd[0]*1e5:.1f} {sd[1]*1e5:.1f} {sd[2]*1e5:.1f}] nT rms")
