#
# pyuavtalk - a minimal, dependency-free UAVTalk client.
#
# Parses the UAVObject XML definitions in shared/uavobjectdefinition/ to learn
# every object's wire layout (the same way ground/uavobjgenerator does), and
# implements the UAVTalk packet framing used by flight/uavtalk/uavtalk.c so a
# plain Python script can talk to real flight code - including the simposix
# SITL target - over UDP or serial.
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

import glob
import os
import struct
import xml.etree.ElementTree as ET

# --------------------------------------------------------------------------
# UAVTalk packet framing (mirrors flight/uavtalk/uavtalk.c / uavtalk_priv.h)
# --------------------------------------------------------------------------

SYNC_VAL = 0x3C

TYPE_VER = 0x20
TIMESTAMPED = 0x80
TYPE_OBJ = TYPE_VER | 0x00
TYPE_OBJ_REQ = TYPE_VER | 0x01
TYPE_OBJ_ACK = TYPE_VER | 0x02
TYPE_ACK = TYPE_VER | 0x03
TYPE_NACK = TYPE_VER | 0x04
TYPE_OBJ_TS = TIMESTAMPED | TYPE_OBJ
TYPE_OBJ_ACK_TS = TIMESTAMPED | TYPE_OBJ_ACK

ALL_INSTANCES = 0xFFFF

# CRC-8, poly 0x07, init 0x00, no reflect, no xorout - same table as
# flight/pios/common/pios_crc.c (PIOS_CRC_updateByte/updateCRC).
_CRC_TABLE = (
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15, 0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,
    0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65, 0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,
    0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5, 0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
    0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85, 0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
    0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2, 0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
    0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2, 0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
    0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32, 0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
    0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42, 0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
    0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c, 0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
    0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec, 0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
    0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c, 0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
    0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c, 0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
    0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b, 0x76, 0x71, 0x78, 0x7f, 0x6a, 0x6d, 0x64, 0x63,
    0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b, 0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
    0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb, 0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8d, 0x84, 0x83,
    0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb, 0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3,
)


def crc8(data, crc=0):
    for byte in data:
        crc = _CRC_TABLE[crc ^ byte]
    return crc


def build_packet(msg_type, obj_id, inst_id, payload=b"", timestamp=None):
    """Frame a UAVTalk packet. Pass timestamp (0-65535 ticks) to send a *_TS type."""
    if timestamp is not None:
        msg_type |= TIMESTAMPED
    header = struct.pack("<BBHIH", SYNC_VAL, msg_type, 0, obj_id, inst_id)
    if msg_type & TIMESTAMPED:
        header += struct.pack("<H", timestamp & 0xFFFF)
    header_and_payload = header + payload
    length = len(header_and_payload)
    header_and_payload = header_and_payload[:2] + struct.pack("<H", length) + header_and_payload[4:]
    return header_and_payload + bytes((crc8(header_and_payload),))


class UAVTalkParser(object):
    """Incremental UAVTalk packet parser fed with raw bytes as they arrive."""

    def __init__(self):
        self._buf = bytearray()

    def feed(self, data):
        self._buf += data

    def packets(self):
        """Yield (msg_type, obj_id, inst_id, payload) tuples for every complete,
        checksum-valid packet currently buffered."""
        buf = self._buf
        while True:
            sync = buf.find(bytes((SYNC_VAL,)))
            if sync < 0:
                del buf[:]
                return
            if sync > 0:
                del buf[:sync]
            if len(buf) < 4:
                return
            msg_type = buf[1]
            length = struct.unpack_from("<H", buf, 2)[0]
            header_len = 10 + (2 if (msg_type & TIMESTAMPED) else 0)
            if length < header_len:
                # Not a real UAVTalk header - resync past this byte.
                del buf[0:1]
                continue
            total_len = length + 1  # + checksum byte
            if len(buf) < total_len:
                return
            packet = bytes(buf[:total_len])
            del buf[:total_len]

            expected_cs = packet[-1]
            if crc8(packet[:-1]) != expected_cs:
                continue  # drop bad packet, resume scanning for the next SYNC

            obj_id, inst_id = struct.unpack_from("<IH", packet, 4)
            payload = packet[header_len:-1]
            yield (msg_type, obj_id, inst_id, payload)


# --------------------------------------------------------------------------
# UAVObject catalog: parsed straight from shared/uavobjectdefinition/*.xml
# --------------------------------------------------------------------------

# flight/uavobjgenerator FIELDTYPE_* order - the ID hash depends on this.
_FIELD_TYPES = ("int8", "int16", "int32", "uint8", "uint16", "uint32", "float", "enum")
_FIELD_STRUCT = {"int8": "b", "int16": "h", "int32": "i",
                  "uint8": "B", "uint16": "H", "uint32": "I",
                  "float": "f", "enum": "B"}
_FIELD_NUM_BYTES = {"int8": 1, "int16": 2, "int32": 4, "uint8": 1,
                     "uint16": 2, "uint32": 4, "float": 4, "enum": 1}


def _update_hash32(value, h):
    h &= 0xFFFFFFFF
    value &= 0xFFFFFFFF
    inner = ((h << 5) + (h >> 2) + value) & 0xFFFFFFFF
    return (h ^ inner) & 0xFFFFFFFF


def _update_hash_str(text, h):
    for byte in text.encode("latin-1"):
        h = _update_hash32(byte, h)
    return h


class Field(object):
    def __init__(self, name, ftype, count, options=None):
        self.name = name
        self.type = ftype
        self.count = count
        self.options = options or []

    @property
    def struct_char(self):
        return _FIELD_STRUCT[self.type]


class ObjectDef(object):
    def __init__(self, name, is_settings, is_single_instance, fields):
        self.name = name
        self.is_settings = is_settings
        self.is_single_instance = is_single_instance
        self.fields = fields
        self.obj_id = self._calc_id()
        self.struct_format = "<" + "".join(
            ("%d%s" % (f.count, f.struct_char)) if f.count > 1 else f.struct_char
            for f in self.fields
        )
        self.size = struct.calcsize(self.struct_format)

    def _calc_id(self):
        h = _update_hash_str(self.name, 0)
        h = _update_hash32(1 if self.is_settings else 0, h)
        h = _update_hash32(1 if self.is_single_instance else 0, h)
        for f in self.fields:
            h = _update_hash_str(f.name, h)
            h = _update_hash32(f.count, h)
            h = _update_hash32(_FIELD_TYPES.index(f.type), h)
            if f.type == "enum":
                for opt in f.options:
                    h = _update_hash_str(opt, h)
        return h & 0xFFFFFFFE

    def pack(self, values):
        """values: dict of field name -> scalar, or list/tuple if count > 1."""
        flat = []
        for f in self.fields:
            v = values.get(f.name, [0] * f.count if f.count > 1 else 0)
            if f.count > 1:
                flat.extend(self._enum_to_int(f, x) for x in v)
            else:
                flat.append(self._enum_to_int(f, v))
        return struct.pack(self.struct_format, *flat)

    @staticmethod
    def _enum_to_int(f, v):
        """Accept an enum's NAME as well as its index.

        unpack() hands enums back as option strings, so round-tripping a
        received object straight back through pack() used to fail with a bare
        "required argument is not an integer" - the enum slot packs as a
        uint8. Callers also naturally write "Mode": "FollowVector", which is
        far more readable than the index and does not silently rot when an
        option is inserted into the middle of the enum.
        """
        if f.type == "enum" and isinstance(v, str):
            try:
                return f.options.index(v)
            except ValueError:
                raise ValueError("%s: %r is not one of %s"
                                 % (f.name, v, f.options))
        return v

    def unpack(self, data):
        flat = struct.unpack(self.struct_format, data[:self.size])
        values = {}
        idx = 0
        for f in self.fields:
            if f.count > 1:
                values[f.name] = list(flat[idx:idx + f.count])
                idx += f.count
            else:
                values[f.name] = flat[idx]
                idx += 1
        return values

    def describe(self, values):
        """Return values with enum ints resolved to option names, for display."""
        out = dict(values)
        for f in self.fields:
            if f.type == "enum" and f.options and f.name in out:
                v = out[f.name]
                if isinstance(v, list):
                    out[f.name] = [f.options[i] if 0 <= i < len(f.options) else i for i in v]
                elif 0 <= v < len(f.options):
                    out[f.name] = f.options[v]
        return out


def _field_count_and_names(field_el):
    names_attr = field_el.get("elementnames")
    if names_attr:
        names = [n.strip() for n in names_attr.split(",")]
        return len(names), names
    names_el = field_el.find("elementnames")
    if names_el is not None:
        names = [n.text for n in names_el.findall("elementname")]
        if names:
            return len(names), names
    count = int(field_el.get("elements", "1"))
    return count, [str(n) for n in range(count)]


def _parse_object_xml(path):
    root = ET.parse(path).getroot()
    obj_el = root.find("object")
    if obj_el is None:
        return None

    name = obj_el.get("name")
    is_settings = obj_el.get("settings", "false").lower() == "true"
    is_single_instance = obj_el.get("singleinstance", "false").lower() == "true"

    fields = []
    fields_by_name = {}
    for field_el in obj_el.findall("field"):
        name_attr = field_el.get("name")
        clone_of = field_el.get("cloneof")
        if clone_of:
            # <field name="X" cloneof="Y"/> - a full copy of Y's type/count/options
            # under a new name, used to avoid repeating identical mixer channels etc.
            parent = fields_by_name[clone_of]
            field = Field(name_attr, parent.type, parent.count, list(parent.options))
        else:
            ftype = field_el.get("type")
            count, _names = _field_count_and_names(field_el)
            options = []
            if ftype == "enum":
                opts_attr = field_el.get("options")
                if opts_attr:
                    options = [o.strip() for o in opts_attr.split(",")]
                else:
                    options_el = field_el.find("options")
                    if options_el is not None:
                        options = [o.text for o in options_el.findall("option")]
            field = Field(name_attr, ftype, count, options)
        fields.append(field)
        fields_by_name[name_attr] = field

    # uavobjectparser.cpp stable-sorts fields by descending per-element byte
    # size before computing the ID hash and the wire/struct layout - both
    # must use this order, not XML declaration order, to match flight code.
    fields.sort(key=lambda f: _FIELD_NUM_BYTES[f.type], reverse=True)

    return ObjectDef(name, is_settings, is_single_instance, fields)


class UAVObjectDB(object):
    """All UAVObjects known from a shared/uavobjectdefinition directory,
    indexed by both name and numeric object ID."""

    def __init__(self, xml_dir):
        self.by_name = {}
        self.by_id = {}
        for path in sorted(glob.glob(os.path.join(xml_dir, "*.xml"))):
            objdef = _parse_object_xml(path)
            if objdef is None:
                continue
            self.by_name[objdef.name] = objdef
            self.by_id[objdef.obj_id] = objdef

    def __getitem__(self, name_or_id):
        if isinstance(name_or_id, str):
            return self.by_name[name_or_id]
        return self.by_id[name_or_id]

    def __contains__(self, name_or_id):
        if isinstance(name_or_id, str):
            return name_or_id in self.by_name
        return name_or_id in self.by_id
