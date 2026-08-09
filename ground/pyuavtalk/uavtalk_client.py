#!/usr/bin/env python3
#
# pyuavtalk_client - a minimal ground-side UAVTalk client for talking to
# real OpenPilot/NinjaPilot flight code over UDP (e.g. the simposix SITL
# target's telemetry port), or over a serial port to real hardware.
#
# It performs the normal GCS<->flight handshake (GCSTelemetryStats /
# FlightTelemetryStats) and then prints every UAVObject the flight side
# streams back. It can also request or write a single object on demand.
#
# Examples:
#   python3 uavtalk_client.py
#   python3 uavtalk_client.py --request AttitudeState
#   python3 uavtalk_client.py --request FlightStatus --set Armed=2
#   python3 uavtalk_client.py --serial /dev/ttyUSB0 --baud 57600
#
# The OpenPilot Team, http://www.openpilot.org, Copyright (C) 2011.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

import argparse
import os
import select
import socket
import sys
import time

import uavtalk

GCS_STATUS_DISCONNECTED = 0
GCS_STATUS_HANDSHAKEREQ = 1
GCS_STATUS_HANDSHAKEACK = 2
GCS_STATUS_CONNECTED = 3


def default_xml_dir():
    here = os.path.dirname(os.path.abspath(__file__))
    return os.path.join(here, "..", "..", "shared", "uavobjectdefinition")


class UdpTransport(object):
    def __init__(self, host, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setblocking(False)
        self.addr = (host, port)

    def send(self, data):
        self.sock.sendto(data, self.addr)

    def poll_recv(self, timeout):
        r, _, _ = select.select([self.sock], [], [], timeout)
        if not r:
            return b""
        data, _from = self.sock.recvfrom(65536)
        return data


class SerialTransport(object):
    def __init__(self, port, baud):
        import serial  # only required for --serial
        self.ser = serial.Serial(port, baud, timeout=0)

    def send(self, data):
        self.ser.write(data)

    def poll_recv(self, timeout):
        r, _, _ = select.select([self.ser.fileno()], [], [], timeout)
        if not r:
            return b""
        return self.ser.read(4096)


def parse_field_assignment(spec):
    name, sep, value = spec.partition("=")
    if not sep:
        raise ValueError("expected FIELD=VALUE, got %r" % spec)
    try:
        value = float(value) if "." in value else int(value)
    except ValueError:
        pass  # leave as a string (e.g. an enum option name)
    return name, value


class UAVTalkClient(object):
    """Drives the GCS<->flight UAVTalk handshake and dispatches decoded objects."""

    def __init__(self, transport, db):
        self.transport = transport
        self.db = db
        self.parser = uavtalk.UAVTalkParser()
        self.connected = False
        # Metaobject (objId+1) payloads received from the flight side, keyed
        # by the metaobject id. Metaobjects are not in the XML db, so run()
        # stashes their raw 8-byte payloads here instead of dispatching them.
        self.meta_payloads = {}

    def send_object(self, name, values, msg_type=uavtalk.TYPE_OBJ, inst_id=0):
        objdef = self.db[name]
        payload = objdef.pack(values)
        self.transport.send(uavtalk.build_packet(msg_type, objdef.obj_id, inst_id, payload))

    def request_object(self, name, inst_id=0):
        objdef = self.db[name]
        self.transport.send(uavtalk.build_packet(uavtalk.TYPE_OBJ_REQ, objdef.obj_id, inst_id))

    def send_raw(self, msg_type, obj_id, inst_id=0, payload=b""):
        """Send a frame for an object id not in the XML db (e.g. metaobjects,
        whose id is the parent object id + 1 and whose payload is the packed
        8-byte UAVObjMetadata struct)."""
        self.transport.send(uavtalk.build_packet(msg_type, obj_id, inst_id, payload))

    def _send_gcs_status(self, status):
        self.send_object("GCSTelemetryStats", {"Status": status})

    def run(self, duration=None, on_object=None, on_connected=None):
        """Drive the handshake and dispatch every decoded object to on_object(objdef,
        inst_id, decoded_values). Calls on_connected() once, the moment the flight
        side confirms the link. Runs until `duration` seconds pass, or forever."""
        gcs_status = GCS_STATUS_HANDSHAKEREQ
        last_handshake_send = 0.0
        start = time.time()

        while duration is None or (time.time() - start) < duration:
            now = time.time()
            if now - last_handshake_send > 1.0:
                self._send_gcs_status(gcs_status)
                last_handshake_send = now

            data = self.transport.poll_recv(0.2)
            if data:
                self.parser.feed(data)

            for msg_type, obj_id, inst_id, payload in self.parser.packets():
                # ACK/NACK/OBJ_REQ carry no payload - only OBJ(_TS)/OBJ_ACK(_TS) have data to decode.
                if msg_type in (uavtalk.TYPE_ACK, uavtalk.TYPE_NACK, uavtalk.TYPE_OBJ_REQ):
                    continue

                objdef = self.db.by_id.get(obj_id)
                if objdef is None:
                    # Metaobject reply (id = parent id + 1): stash for whoever
                    # requested it via send_raw(TYPE_OBJ_REQ, ...).
                    if (obj_id - 1) in self.db.by_id:
                        self.meta_payloads[obj_id] = bytes(payload)
                        continue
                    print("[recv] unknown object id 0x%08X (%d bytes)" % (obj_id, len(payload)))
                    continue

                if len(payload) < objdef.size:
                    continue  # short/malformed packet - drop rather than crash

                decoded = objdef.describe(objdef.unpack(payload))

                if msg_type in (uavtalk.TYPE_OBJ_ACK, uavtalk.TYPE_OBJ_ACK_TS):
                    # Most settings-category objects (HomeLocation, RevoSettings,
                    # MixerSettings, FlightModeSettings, ...) have
                    # telemetryflight acked="true" - the flight side pushes
                    # these with retries and blocks waiting for a TYPE_ACK
                    # reply. We were silently decoding the object but never
                    # sending that reply, so every acked push timed out after
                    # MAX_RETRIES: FlightTelemetryStats.TxFailures/TxRetries
                    # climbed steadily while TxBytes/TxDataRate stayed at 0
                    # (nothing ever completed), which is exactly the frozen/
                    # broken-looking Tx meter this fixes.
                    self.transport.send(uavtalk.build_packet(uavtalk.TYPE_ACK, obj_id, inst_id))

                if objdef.name == "FlightTelemetryStats":
                    status = decoded["Status"]
                    if status == "HandshakeAck" and gcs_status != GCS_STATUS_CONNECTED:
                        gcs_status = GCS_STATUS_CONNECTED
                        self._send_gcs_status(gcs_status)
                    elif status == "Connected" and not self.connected:
                        self.connected = True
                        print("[link] connected to flight side")
                        if on_connected:
                            on_connected()
                    elif status == "Disconnected":
                        self.connected = False

                if on_object:
                    on_object(objdef, inst_id, decoded)
                else:
                    print("[recv] %-24s inst=%d %s" % (objdef.name, inst_id, decoded))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--host", default="127.0.0.1", help="simposix telemetry UDP host (default 127.0.0.1)")
    ap.add_argument("--port", type=int, default=9000, help="simposix telemetry UDP port (default 9000)")
    ap.add_argument("--serial", metavar="DEVICE", help="use a serial port instead of UDP (real hardware)")
    ap.add_argument("--baud", type=int, default=57600, help="serial baud rate (default 57600)")
    ap.add_argument("--xml-dir", default=default_xml_dir(), help="path to shared/uavobjectdefinition")
    ap.add_argument("--request", metavar="OBJECT", help="request this object once connected")
    ap.add_argument("--set", nargs="+", metavar="FIELD=VALUE", help="write these fields on --request's object instead of just reading it")
    ap.add_argument("--duration", type=float, default=None, help="stop after N seconds (default: run until Ctrl+C)")
    args = ap.parse_args()

    if args.set and not args.request:
        ap.error("--set requires --request NAME to know which object to write")

    db = uavtalk.UAVObjectDB(args.xml_dir)
    print("Loaded %d UAVObject definitions from %s" % (len(db.by_name), args.xml_dir))

    if args.serial:
        transport = SerialTransport(args.serial, args.baud)
    else:
        transport = UdpTransport(args.host, args.port)
        print("Talking UDP to %s:%d (matches simposix's PIOS_COM_TELEM_RF)" % (args.host, args.port))

    client = UAVTalkClient(transport, db)

    def on_connected():
        if args.set:
            values = dict(parse_field_assignment(s) for s in args.set)
            print("[send] %s <- %s" % (args.request, values))
            client.send_object(args.request, values, msg_type=uavtalk.TYPE_OBJ_ACK)
        elif args.request:
            client.request_object(args.request)

    try:
        client.run(args.duration, on_connected=on_connected)
    except KeyboardInterrupt:
        pass


if __name__ == "__main__":
    sys.exit(main() or 0)
