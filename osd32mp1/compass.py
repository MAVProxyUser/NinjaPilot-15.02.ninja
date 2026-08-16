import time, dronecan
node=dronecan.make_node("can0", node_id=127, bitrate=1000000)
mon=dronecan.app.node_monitor.NodeMonitor(node)
alloc=dronecan.app.dynamic_node_id.CentralizedServer(node,mon,database_storage="/home/root/dronecan_alloc.db")
params={}; mags={}
def bump(e):
    nid=e.transfer.source_node_id
    mags[nid]=mags.get(nid,0)+1
node.add_handler(dronecan.uavcan.equipment.ahrs.MagneticFieldStrength, bump)
t0=time.time()
while time.time()-t0<8: node.spin(1)
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
    for i in range(120):
        try:
            node.request(dronecan.uavcan.protocol.param.GetSet.Request(index=i), nid, pcb(nid))
            node.spin(0.03)
        except Exception: pass
t0=time.time()
while time.time()-t0<5: node.spin(1)

DEV={0x01:"HMC5883_OLD",0x02:"LSM303D",0x04:"AK8963",0x05:"BMM150",0x06:"LSM9DS1",
     0x07:"HMC5883",0x08:"LIS3MDL",0x09:"AK09916",0x0A:"IST8310",0x0B:"ICM20948",
     0x0C:"MMC3416",0x0D:"QMC5883L",0x0E:"MAG3110",0x0F:"SITL",0x10:"IST8308",
     0x11:"RM3100",0x12:"RM3100_2",0x13:"MMC5883",0x14:"AK09918",0x15:"AK09915"}
BUS={1:"I2C",2:"SPI",3:"UAVCAN",4:"SITL",5:"MSP",6:"SERIAL",7:"WSPI"}
for nid in sorted(params):
    print(f"\n=== node {nid}   {len(params[nid])} params   mag msgs in 8s: {mags.get(nid,0)} ===")
    comp={k:v for k,v in params[nid].items() if "COMPASS" in k.upper() or "MAG" in k.upper()}
    for k in sorted(comp):
        v=comp[k]; line=f"  {k} = {v}"
        if "DEV_ID" in k.upper():
            try:
                d=int(v.split("=")[1])
                line += (f"   -> {DEV.get((d>>16)&0xFF,'?')} on {BUS.get(d&7,'?')} "
                         f"bus{(d>>3)&0x1F} addr 0x{(d>>8)&0xFF:02X}") if d else "   -> (none)"
            except Exception: pass
        print(line)
    if not comp: print("  (no COMPASS/MAG parameters)")
