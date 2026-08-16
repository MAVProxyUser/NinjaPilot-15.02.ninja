import time, dronecan
node = dronecan.make_node('can0', node_id=127, bitrate=1000000)
mon = dronecan.app.node_monitor.NodeMonitor(node)
alloc = dronecan.app.dynamic_node_id.CentralizedServer(node, mon,
            database_storage='/home/root/dronecan_alloc.db')
n = {'mag': 0, 'fix': 0}
def mag(ev):
    n['mag'] += 1
    if n['mag'] % 25 == 1:
        m = ev.message.magnetic_field_ga
        print("  mag  node %-3d  [% .4f % .4f % .4f] gauss" % (
              ev.transfer.source_node_id, m[0], m[1], m[2]))
def fix(ev):
    n['fix'] += 1
    if n['fix'] % 10 == 1:
        f = ev.message
        print("  gnss node %-3d  sats=%-2d fix=%d  lat=%.7f lon=%.7f" % (
              ev.transfer.source_node_id, f.sats_used, f.status,
              f.latitude_deg_1e8/1e8, f.longitude_deg_1e8/1e8))
node.add_handler(dronecan.uavcan.equipment.ahrs.MagneticFieldStrength, mag)
node.add_handler(dronecan.uavcan.equipment.gnss.Fix2, fix)
t0 = time.time()
while time.time() - t0 < 12:
    node.spin(1)
print("  totals:", n)
