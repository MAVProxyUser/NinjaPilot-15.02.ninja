#!/usr/bin/env python3
"""Feed REAL sensors into fw_simposix as UAVObjects. Runs ON THE BOARD.

This is the same seam `gazebo_bridge.py` uses: with
NINJAPILOT_EXTERNAL_PHYSICS=1 the firmware takes its sensors from UAVTalk/UDP
instead of the simulator, so real hardware is just a different producer of the
same six objects.

    DroneCAN  RM3100 mag  25 Hz  -> MagSensor        (gauss -> milligauss)
    DroneCAN  GNSS Fix2    5 Hz  -> GPSPositionSensor / GPSVelocitySensor
    USB       ADXL345    800 Hz  -> AccelSensor       (m/s^2)
    (none)                       -> GyroSensor        ** ZEROS, see below **
    (none)                       -> BaroSensor        ** not present **

TWO SENSORS ARE MISSING AND THIS CANNOT FLY:
  * No gyro. GyroSensor is published as zeros purely so the firmware's
    gyro-triggered stabilizationInnerloopTask has something to tick on. With a
    zero rate the attitude filter runs on accelerometer levelling alone.
    Fix: ICM-42688-P on mikroBUS SPI (see README).
  * No barometer anywhere in the current sensor set - BARO1/2/3_DEVID all read
    0 on the DroneCAN nodes - so the whole vertical channel has no input.

ARCHITECTURE - why processes, not threads. CLAUDE.md records two separate
occasions where a blocking call on a background THREAD stalled the sensor feed
through the GIL and flew the vehicle into the ground. dronecan's spin() and the
Klipper serial reads are both blocking, so each lives in its own process and
publishes into shared memory. The sender is a single deterministically paced
loop, and it never emits two objects back to back - that corrupts/drops one on
this transport (also recorded in CLAUDE.md).

usage (on the board):
    ./sensor_bridge.py --dry-run          # print what would be sent
    ./sensor_bridge.py --rate 200         # feed fw_simposix on 127.0.0.1:9000
"""
import argparse
import ctypes
import multiprocessing as mp
import os
import struct
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))

# uavtalk_client.default_xml_dir() resolves "../../shared/uavobjectdefinition"
# relative to itself, which only holds inside the repo layout. Deployed on the
# board that silently points outside the install, so the XML dir is passed
# explicitly instead of inherited.
for _p in (os.path.join(HERE, "pyuavtalk"),
           os.path.join(HERE, "ground", "pyuavtalk")):
    if os.path.isdir(_p):
        sys.path.insert(0, _p)
        break
DEFAULT_XML = os.path.join(HERE, "shared", "uavobjectdefinition")

STALE_S = 2.0          # older than this and we stop republishing a sensor


# ---------------------------------------------------------------- readers

def dronecan_proc(mag, gps, stop):
    """RM3100 magnetometer + GNSS Fix2 -> shared memory."""
    import dronecan
    node = dronecan.make_node("can0", node_id=127, bitrate=1000000)
    mon = dronecan.app.node_monitor.NodeMonitor(node)
    dronecan.app.dynamic_node_id.CentralizedServer(
        node, mon, database_storage="/home/root/dronecan_alloc.db")

    def on_mag(e):
        m = e.message.magnetic_field_ga
        mag[0], mag[1], mag[2], mag[3] = m[0], m[1], m[2], time.time()

    def on_fix(e):
        f = e.message
        gps[0] = f.latitude_deg_1e8 / 1e8
        gps[1] = f.longitude_deg_1e8 / 1e8
        gps[2] = f.height_msl_mm / 1000.0
        try:
            v = f.ned_velocity
            gps[3], gps[4], gps[5] = v[0], v[1], v[2]
        except Exception:
            gps[3] = gps[4] = gps[5] = 0.0
        gps[6] = float(getattr(f, "sats_used", 0))
        gps[7] = float(getattr(f, "status", 0))
        try:
            gps[8] = float(f.covariance[0]) ** 0.5
        except Exception:
            gps[8] = 99.0
        gps[9] = time.time()

    node.add_handler(dronecan.uavcan.equipment.ahrs.MagneticFieldStrength, on_mag)
    for path in ("uavcan.equipment.gnss.Fix2", "uavcan.equipment.gnss.Fix"):
        try:
            node.add_handler(dronecan.TYPENAMES[path], on_fix)
        except KeyError:
            pass
    while not stop.value:
        try:
            node.spin(0.2)
        except Exception:
            time.sleep(0.1)


def mpu_proc(imu, stop, bus_n, addr, cal_n):
    """MPU-9150 gyro + accel over I2C -> shared memory.

    Own process, like the other readers: an I2C burst is a blocking syscall,
    and CLAUDE.md records two crashes caused by a blocking call on a background
    THREAD stalling the sensor feed through the GIL.

    The part boots ASLEEP (PWR_MGMT_1 = 0x40) and every register reads 0x00
    until that is cleared - a scan finds it, WHO_AM_I answers, and the data is
    all zeros, which reads exactly like a dead sensor.
    """
    import fcntl
    I2C_SLAVE = 0x0703
    fd = os.open(f"/dev/i2c-{bus_n}", os.O_RDWR)
    fcntl.ioctl(fd, I2C_SLAVE, addr)

    def wr(reg, val):
        os.write(fd, bytes([reg, val]))

    def rd(reg, n=1):
        os.write(fd, bytes([reg]))
        return os.read(fd, n)

    wr(0x6B, 0x80); time.sleep(0.1)      # reset
    # clock = PLL with X-gyro reference, not the internal 8 MHz RC: Invensense
    # recommend it and the RC oscillator drifts noticeably with temperature.
    wr(0x6B, 0x01); time.sleep(0.05)
    wr(0x1A, 0x03)                        # DLPF ~44 Hz, 1 kHz internal rate
    wr(0x19, 0x04)                        # SMPLRT_DIV -> 200 Hz
    wr(0x1B, 0x18)                        # gyro  +/-2000 dps -> 16.4 LSB/dps
    wr(0x1C, 0x00)                        # accel +/-2 g      -> 16384 LSB/g
    time.sleep(0.05)

    GS, AS = 16.4, 16384.0

    # Startup bias removal. Measured -1.10/-0.24/-0.24 dps at rest on this
    # part, which integrates into real attitude drift. The firmware's own
    # filter also estimates gyro bias, so this only needs to remove the gross
    # offset, not be perfect.
    bias = [0.0, 0.0, 0.0]
    if cal_n > 0:
        acc = [0.0, 0.0, 0.0]
        for _ in range(cal_n):
            g = struct.unpack(">hhh", rd(0x43, 6))
            for i in range(3):
                acc[i] += g[i] / GS
            time.sleep(0.005)
        bias = [a / cal_n for a in acc]
        imu[8], imu[9], imu[10] = bias

    while not stop.value:
        try:
            b = rd(0x3B, 14)
            ax, ay, az, t, gx, gy, gz = struct.unpack(">hhhhhhh", b)
            imu[0] = gx / GS - bias[0]        # deg/s  (GyroSensor wants dps)
            imu[1] = gy / GS - bias[1]
            imu[2] = gz / GS - bias[2]
            imu[3] = ax / AS * 9.80665        # m/s^2
            imu[4] = ay / AS * 9.80665
            imu[5] = az / AS * 9.80665
            imu[6] = t / 340.0 + 36.53        # degC
            imu[7] = time.time()
        except OSError:
            time.sleep(0.01)
        time.sleep(0.004)                     # ~200 Hz
    os.close(fd)


def accel_proc(accel, stop, rate):
    """KUSBA ADXL345 over USB -> shared memory (latest sample wins)."""
    import importlib.util
    spec = importlib.util.spec_from_file_location(
        "ka", os.path.join(HERE, "klipper_accel.py"))
    ka = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(ka)

    mcu = ka.Mcu("/dev/ttyACM0")
    SPI_OID, ACC_OID = 0, 1
    cfg = mcu.request("get_config", "config")
    if cfg is not None and not cfg["is_config"]:
        for n, kw in (("allocate_oids", dict(count=2)),
                      ("config_spi", dict(oid=SPI_OID,
                                          pin=mcu.codec.enum("pin", "CS"),
                                          cs_active_high=0)),
                      ("spi_set_bus", dict(oid=SPI_OID,
                                           spi_bus=mcu.codec.enum("spi_bus", "spi0"),
                                           mode=3, rate=5000000)),
                      ("config_adxl345", dict(oid=ACC_OID, spi_oid=SPI_OID))):
            mcu.send(n, **kw); mcu.pump(0.05)
        mcu.send("finalize_config", crc=0); mcu.pump(0.3)

    for reg, val in ((ka.REG_POWER_CTL, 0x00),
                     (ka.REG_DATA_FORMAT, ka.DATA_FORMAT_FULLRES_16G),
                     (ka.REG_FIFO_CTL, 0x00),
                     (ka.REG_BW_RATE, ka.RATES[rate]),
                     (ka.REG_FIFO_CTL, ka.FIFO_STREAM),
                     (ka.REG_POWER_CTL, ka.POWER_CTL_MEASURE)):
        ka.spi_reg_write(mcu, SPI_OID, reg, val)

    clk = mcu.request("get_clock", "clock")
    start = ((clk["clock"] if clk else 0) + mcu.clock_freq // 10) & 0xFFFFFFFF
    mcu.send("query_adxl345", oid=ACC_OID, clock=start,
             rest_ticks=max(1, int(mcu.clock_freq * 4.0 / rate)))

    while not stop.value:
        for n, v in mcu.pump(0.1):
            if n == "adxl345_data":
                s = ka.decode_samples(v["data"])
                if s:
                    accel[0], accel[1], accel[2] = s[-1]
                    accel[3] = time.time()
    try:
        mcu.send("query_adxl345", oid=ACC_OID, clock=0, rest_ticks=0)
        mcu.close()
    except Exception:
        pass


# ------------------------------------------------------------- conversions

def mag_to_uav(m):
    """RM3100 gauss -> MagSensor milligauss.

    AP_Periph publishes MagneticFieldStrength already rotated into the node's
    body frame, and ArduPilot's body frame IS FRD - the same convention the
    firmware wants - so no axis swap is needed here. What IS still missing is
    the physical MOUNTING rotation of the node relative to the airframe; that
    is identity until the node is actually bolted down, and it is the single
    most likely source of a sign error (CLAUDE.md).
    """
    return {"x": m[0] * 1000.0, "y": m[1] * 1000.0, "z": m[2] * 1000.0,
            "temperature": 25.0}


def accel_to_uav(a):
    """ADXL345 m/s^2 -> AccelSensor m/s^2, body FRD.

    Identity rotation: the KUSBA is loose on the bench. Once mounted this needs
    the board->airframe rotation, same caveat as the magnetometer.
    """
    return {"x": a[0], "y": a[1], "z": a[2], "temperature": 25.0}


def gyro_to_uav(m):
    """MPU-9150 -> GyroSensor. Units are deg/s, body FRD (see the object table
    in README). Mounting rotation is identity until the part is bolted down -
    the same caveat as the mag and accel, and the likeliest source of a sign
    error."""
    return {"x": m[0], "y": m[1], "z": m[2], "temperature": m[6]}


def mpu_accel_to_uav(m):
    """MPU-9150 -> AccelSensor, m/s^2 body FRD. Preferred over the ADXL345:
    measured |a| 0.981 g vs 0.912 g uncalibrated, because it is a 16-bit part
    (0.061 mg/LSB) against the ADXL's 13-bit full-res (3.9 mg/LSB)."""
    return {"x": m[3], "y": m[4], "z": m[5], "temperature": m[6]}


def pump_rx(client, uavtalk, seen):
    """Drain whatever the firmware sent back, through the SAME client.

    Deliberately not a second UAVTalk client: CLAUDE.md records three runs lost
    to two clients on port 9000 silently stealing each other's packets. Read
    back on the socket that is already talking.
    """
    data = client.transport.poll_recv(0.0)
    if not data:
        return
    client.parser.feed(data)
    for msg_type, obj_id, inst_id, payload in client.parser.packets():
        if msg_type in (uavtalk.TYPE_ACK, uavtalk.TYPE_NACK, uavtalk.TYPE_OBJ_REQ):
            continue
        objdef = client.db.by_id.get(obj_id)
        if objdef is None or len(payload) < objdef.size:
            continue
        try:
            seen[objdef.name] = objdef.describe(objdef.unpack(payload))
        except Exception:
            pass


# Fix2 status -> GPSPositionSensor.Status (NoGPS/NoFix/Fix2D/Fix3D)
_FIX_STATUS = {0: 1, 1: 1, 2: 2, 3: 3}


def gps_to_uav(g):
    return ({"Latitude": int(g[0] * 1e7), "Longitude": int(g[1] * 1e7),
             "Altitude": g[2], "GeoidSeparation": 0.0, "Heading": 0.0,
             "Groundspeed": (g[3] ** 2 + g[4] ** 2) ** 0.5,
             "Satellites": int(g[6]), "PDOP": min(g[8], 99.0),
             "HDOP": min(g[8], 99.0), "VDOP": min(g[8], 99.0),
             "Status": _FIX_STATUS.get(int(g[7]), 1)},
            {"North": g[3], "East": g[4], "Down": g[5]})


# ------------------------------------------------------------------- main

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--host", default="127.0.0.1")
    ap.add_argument("--port", type=int, default=9000)
    ap.add_argument("--rate", type=int, default=200, help="sender loop Hz")
    ap.add_argument("--accel-rate", type=int, default=800)
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--seconds", type=float, default=0.0)
    ap.add_argument("--no-accel", action="store_true")
    ap.add_argument("--no-can", action="store_true")
    ap.add_argument("--no-mpu", action="store_true")
    ap.add_argument("--mpu-bus", type=int, default=3)
    ap.add_argument("--mpu-addr", type=lambda x: int(x, 0), default=0x68)
    ap.add_argument("--gyro-cal", type=int, default=200,
                    help="stationary samples for startup bias removal (0=off)")
    ap.add_argument("--accel-source", choices=("mpu", "adxl"), default="mpu")
    ap.add_argument("--xml-dir", default=DEFAULT_XML)
    ap.add_argument("--verify", action="store_true",
                    help="read the sensor objects back out of the firmware")
    a = ap.parse_args()

    mag = mp.Array(ctypes.c_double, 4)
    accel = mp.Array(ctypes.c_double, 4)
    gps = mp.Array(ctypes.c_double, 10)
    imu = mp.Array(ctypes.c_double, 11)   # gx,gy,gz,ax,ay,az,T,ts,bias[3]
    stop = mp.Value(ctypes.c_int, 0)

    procs = []
    if not a.no_can:
        procs.append(mp.Process(target=dronecan_proc, args=(mag, gps, stop),
                                daemon=True))
    if not a.no_accel:
        procs.append(mp.Process(target=accel_proc, args=(accel, stop, a.accel_rate),
                                daemon=True))
    if not a.no_mpu:
        procs.append(mp.Process(target=mpu_proc,
                                args=(imu, stop, a.mpu_bus, a.mpu_addr, a.gyro_cal),
                                daemon=True))
    for p in procs:
        p.start()

    client = None
    if not a.dry_run:
        import uavtalk
        import uavtalk_client as uc
        if not os.path.isdir(a.xml_dir):
            sys.exit(f"UAVObject XML dir not found: {a.xml_dir}  (use --xml-dir)")
        db = uavtalk.UAVObjectDB(a.xml_dir)
        client = uc.UAVTalkClient(uc.UdpTransport(a.host, a.port), db)
        _uavtalk, _uc = uavtalk, uc
        print(f"[bridge] sending UAVTalk to {a.host}:{a.port} at {a.rate} Hz")
    else:
        print("[bridge] DRY RUN - printing conversions, sending nothing")

    period = 1.0 / a.rate
    gap = min(period / 4.0, 0.0008)     # never emit two objects back to back
    n = 0
    t_end = time.time() + a.seconds if a.seconds else None
    last_report = time.time()
    last_hs = 0.0
    sent = {"gyro": 0, "accel": 0, "mag": 0, "gps": 0}
    seen = {}          # object name -> last value the FIRMWARE reported

    try:
        while True:
            t0 = time.time()
            if t_end and t0 > t_end:
                break
            now = t0

            # --- GyroSensor EVERY tick: it is what triggers the inner loop.
            gyro_live = (now - imu[7]) < STALE_S
            gv = gyro_to_uav(imu) if gyro_live else {"x": 0.0, "y": 0.0,
                                                     "z": 0.0, "temperature": 25.0}
            if client:
                client.send_object("GyroSensor", gv)
            sent["gyro"] += 1
            time.sleep(gap)

            # --- AccelSensor on alternate ticks, separated from the gyro send
            use_mpu_accel = (a.accel_source == "mpu" and now - imu[7] < STALE_S)
            if n % 2 == 0 and (use_mpu_accel or now - accel[3] < STALE_S):
                v = mpu_accel_to_uav(imu) if use_mpu_accel else accel_to_uav(accel)
                if client:
                    client.send_object("AccelSensor", v)
                sent["accel"] += 1
                time.sleep(gap)

            # --- MagSensor at ~25 Hz (the RM3100's own rate)
            if n % max(1, a.rate // 25) == 0 and now - mag[3] < STALE_S:
                v = mag_to_uav(mag)
                if client:
                    client.send_object("MagSensor", v)
                sent["mag"] += 1
                time.sleep(gap)

            # --- GPS at ~5 Hz
            if n % max(1, a.rate // 5) == 0 and now - gps[9] < STALE_S:
                pos, vel = gps_to_uav(gps)
                if client:
                    client.send_object("GPSPositionSensor", pos)
                    time.sleep(gap)
                    client.send_object("GPSVelocitySensor", vel)
                sent["gps"] += 1
                time.sleep(gap)

            # keep the telemetry link up and drain anything coming back
            if client and a.verify:
                if now - last_hs > 1.0:
                    client._send_gcs_status(_uc.GCS_STATUS_CONNECTED)
                    last_hs = now
                    for o in ("MagSensor", "AccelSensor", "GyroSensor",
                              "GPSPositionSensor", "AttitudeState"):
                        try:
                            client.request_object(o)
                        except Exception:
                            pass
                pump_rx(client, _uavtalk, seen)

            if now - last_report >= 2.0:
                fresh = lambda t: "OK " if now - t < STALE_S else "STALE"
                print(f"  t={int(now-last_report)}s  "
                      f"mag[{fresh(mag[3])} {mag[0]*100:+.1f},{mag[1]*100:+.1f},"
                      f"{mag[2]*100:+.1f} uT]  "
                      f"accel[{fresh(accel[3])} {accel[0]:+.2f},{accel[1]:+.2f},"
                      f"{accel[2]:+.2f}]  "
                      f"gps[{fresh(gps[9])} sats={int(gps[6])} fix={int(gps[7])}]\n"
                      f"      gyro[{fresh(imu[7])} {imu[0]:+.2f},{imu[1]:+.2f},"
                      f"{imu[2]:+.2f} dps]  "
                      f"mpu-accel[{imu[3]:+.2f},{imu[4]:+.2f},{imu[5]:+.2f}]  "
                      f"{imu[6]:.1f}C  sent={sent}")
                if a.verify:
                    if not seen:
                        print("      firmware: nothing read back yet")
                    for nm in ("MagSensor", "AccelSensor", "AttitudeState"):
                        v = seen.get(nm)
                        if v:
                            keys = [k for k in ("x", "y", "z", "Roll", "Pitch", "Yaw")
                                    if k in v]
                            body = "  ".join(f"{k}={float(v[k]):+8.3f}" for k in keys)
                            print(f"      FW {nm:<18} {body}")
                last_report = now

            n += 1
            dt = period - (time.time() - t0)
            if dt > 0:
                time.sleep(dt)
    except KeyboardInterrupt:
        pass
    finally:
        stop.value = 1
        time.sleep(0.5)
        for p in procs:
            if p.is_alive():
                p.terminate()
    print(f"\n[bridge] stopped. totals: {sent}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
