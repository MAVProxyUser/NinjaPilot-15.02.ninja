//  UAVTalk framing and UAVObject decoding.
//
//  Deliberately a direct port of ground/pyuavtalk/uavtalk.py rather than a
//  fresh reading of the spec: the field order (descending element size, not
//  XML order) and the CRC-8 table are the two things that silently produce a
//  client which connects and then shows nothing.

import Foundation

enum UAVTalk {
    static let sync: UInt8 = 0x3C
    static let typeVer: UInt8 = 0x20
    static let timestamped: UInt8 = 0x80

    static let typeObj: UInt8 = typeVer | 0x00
    static let typeObjReq: UInt8 = typeVer | 0x01
    static let typeObjAck: UInt8 = typeVer | 0x02
    static let typeAck: UInt8 = typeVer | 0x03
    static let typeNack: UInt8 = typeVer | 0x04

    /// CRC-8, poly 0x07, init 0x00, no reflection -- flight/pios/common/pios_crc.c
    static let crcTable: [UInt8] = {
        var t = [UInt8](repeating: 0, count: 256)
        for i in 0..<256 {
            var c = UInt8(i)
            for _ in 0..<8 {
                c = (c & 0x80) != 0 ? (c << 1) ^ 0x07 : (c << 1)
            }
            t[i] = c
        }
        return t
    }()

    static func crc8(_ data: [UInt8], _ seed: UInt8 = 0) -> UInt8 {
        var crc = seed
        for b in data { crc = crcTable[Int(crc ^ b)] }
        return crc
    }

    /// Frame a packet. `length` counts header+payload and excludes the CRC byte.
    static func packet(type: UInt8, objId: UInt32, instId: UInt16 = 0,
                       payload: [UInt8] = []) -> Data {
        var p = [UInt8]()
        p.append(sync)
        p.append(type)
        let length = UInt16(10 + payload.count)
        p.append(UInt8(length & 0xFF))
        p.append(UInt8(length >> 8))
        p.append(UInt8(objId & 0xFF))
        p.append(UInt8((objId >> 8) & 0xFF))
        p.append(UInt8((objId >> 16) & 0xFF))
        p.append(UInt8((objId >> 24) & 0xFF))
        p.append(UInt8(instId & 0xFF))
        p.append(UInt8(instId >> 8))
        p.append(contentsOf: payload)
        p.append(crc8(p))
        return Data(p)
    }
}

struct UAVPacket {
    let type: UInt8
    let objId: UInt32
    let instId: UInt16
    let payload: [UInt8]
}

/// Incremental parser: feed it bytes as datagrams arrive, take whole packets out.
final class UAVTalkParser {
    private var buf = [UInt8]()

    func feed(_ data: Data) { buf.append(contentsOf: data) }

    func drain() -> [UAVPacket] {
        var out = [UAVPacket]()
        while true {
            guard let syncIdx = buf.firstIndex(of: UAVTalk.sync) else {
                buf.removeAll()
                return out
            }
            if syncIdx > 0 { buf.removeFirst(syncIdx) }
            guard buf.count >= 4 else { return out }

            let msgType = buf[1]
            let length = Int(buf[2]) | (Int(buf[3]) << 8)
            let headerLen = 10 + ((msgType & UAVTalk.timestamped) != 0 ? 2 : 0)
            if length < headerLen {
                buf.removeFirst()          // not a real header, resync
                continue
            }
            let total = length + 1         // + CRC
            guard buf.count >= total else { return out }

            let packet = Array(buf[0..<total])
            buf.removeFirst(total)

            guard UAVTalk.crc8(Array(packet[0..<(total - 1)])) == packet[total - 1] else {
                continue                   // bad CRC, drop and keep scanning
            }
            let objId = UInt32(packet[4]) | (UInt32(packet[5]) << 8)
                | (UInt32(packet[6]) << 16) | (UInt32(packet[7]) << 24)
            let instId = UInt16(packet[8]) | (UInt16(packet[9]) << 8)
            out.append(UAVPacket(type: msgType, objId: objId, instId: instId,
                                 payload: Array(packet[headerLen..<(total - 1)])))
        }
    }
}

// MARK: - Object model

enum UAVFieldType {
    case int8, int16, int32, uint8, uint16, uint32, float, `enum`

    var byteCount: Int {
        switch self {
        case .int8, .uint8, .enum: return 1
        case .int16, .uint16: return 2
        case .int32, .uint32, .float: return 4
        }
    }
}

struct UAVField {
    let name: String
    let type: UAVFieldType
    let count: Int
    let options: [String]
    /// Per-element labels from the XML (Alarm -> SystemConfiguration, ...).
    /// Empty when the field is a plain scalar or an unnamed array.
    var elementNames: [String] = []
}

struct UAVObjectDef {
    let name: String
    let id: UInt32
    let size: Int
    let isSingleInstance: Bool
    let fields: [UAVField]

    /// Metadata for an object lives at objId + 1.
    var metaId: UInt32 { id &+ 1 }
}

/// A decoded object: every field as [Double], plus enum option names resolved.
struct UAVObjectValue {
    let def: UAVObjectDef
    var numbers: [String: [Double]] = [:]

    func number(_ field: String, _ index: Int = 0) -> Double? {
        guard let a = numbers[field], index < a.count else { return nil }
        return a[index]
    }

    func int(_ field: String, _ index: Int = 0) -> Int? {
        number(field, index).map { Int($0) }
    }

    /// Resolve an enum slot to its option name, e.g. "Critical".
    func option(_ field: String, _ index: Int = 0) -> String? {
        guard let f = def.fields.first(where: { $0.name == field }),
              let v = int(field, index), v >= 0, v < f.options.count else { return nil }
        return f.options[v]
    }

    func array(_ field: String) -> [Double] { numbers[field] ?? [] }

    func elementNames(_ field: String) -> [String] {
        def.fields.first(where: { $0.name == field })?.elementNames ?? []
    }

    /// Resolve one element of an enum array to its option name.
    func optionFor(_ field: String, element: String) -> String? {
        guard let f = def.fields.first(where: { $0.name == field }),
              let i = f.elementNames.firstIndex(of: element) else { return nil }
        return option(field, i)
    }
}

extension UAVObjectDef {
    func decode(_ payload: [UInt8]) -> UAVObjectValue? {
        guard payload.count >= size else { return nil }
        var v = UAVObjectValue(def: self)
        var off = 0
        for f in fields {
            var vals = [Double]()
            vals.reserveCapacity(f.count)
            for _ in 0..<f.count {
                let n = f.type.byteCount
                guard off + n <= payload.count else { return nil }
                let b = Array(payload[off..<(off + n)])
                off += n
                switch f.type {
                case .uint8, .enum: vals.append(Double(b[0]))
                case .int8:  vals.append(Double(Int8(bitPattern: b[0])))
                case .uint16: vals.append(Double(UInt16(b[0]) | (UInt16(b[1]) << 8)))
                case .int16:  vals.append(Double(Int16(bitPattern: UInt16(b[0]) | (UInt16(b[1]) << 8))))
                case .uint32: vals.append(Double(le32(b)))
                case .int32:  vals.append(Double(Int32(bitPattern: le32(b))))
                case .float:  vals.append(Double(Float(bitPattern: le32(b))))
                }
            }
            v.numbers[f.name] = vals
        }
        return v
    }

    private func le32(_ b: [UInt8]) -> UInt32 {
        UInt32(b[0]) | (UInt32(b[1]) << 8) | (UInt32(b[2]) << 16) | (UInt32(b[3]) << 24)
    }
}

/// UAVObjMetadata is 8 bytes: flags, telemetry period, GCS period, logging period.
/// Telemetry update mode lives in flags bits 4-5; 1 == periodic.
enum UAVMeta {
    static let updateModeShift: UInt16 = 4
    static let periodic: UInt16 = 1

    static func decode(_ payload: [UInt8]) -> (flags: UInt16, tp: UInt16, gp: UInt16, lp: UInt16)? {
        guard payload.count >= 8 else { return nil }
        func u16(_ i: Int) -> UInt16 { UInt16(payload[i]) | (UInt16(payload[i + 1]) << 8) }
        return (u16(0), u16(2), u16(4), u16(6))
    }

    static func encodePeriodic(flags: UInt16, periodMs: UInt16,
                               gp: UInt16, lp: UInt16) -> [UInt8] {
        let f = (flags & ~(3 << updateModeShift)) | (periodic << updateModeShift)
        var out = [UInt8]()
        for v in [f, periodMs, gp, lp] {
            out.append(UInt8(v & 0xFF)); out.append(UInt8(v >> 8))
        }
        return out
    }
}

// MARK: - Write side

extension UAVObjectValue {
    mutating func set(_ field: String, _ values: [Double]) { numbers[field] = values }
    mutating func set(_ field: String, _ v: Double) { numbers[field] = [v] }

    mutating func set(_ field: String, index: Int, _ v: Double) {
        var a = numbers[field] ?? []
        let count = def.fields.first(where: { $0.name == field })?.count ?? (index + 1)
        while a.count < count { a.append(0) }
        if index < a.count { a[index] = v }
        numbers[field] = a
    }

    /// Set an enum slot by option NAME, so "Save" never rots into a bare index.
    mutating func set(_ field: String, option: String, index: Int = 0) {
        guard let i = def.optionIndex(field, option) else { return }
        set(field, index: index, Double(i))
    }
}

extension UAVObjectDef {
    func optionIndex(_ field: String, _ option: String) -> Int? {
        fields.first(where: { $0.name == field })?.options.firstIndex(of: option)
    }

    /// Mirror of decode(): same field order, same little-endian layout.
    func encode(_ v: UAVObjectValue) -> [UInt8] {
        var out = [UInt8]()
        out.reserveCapacity(size)
        func clamped(_ d: Double) -> Int64 {
            guard d.isFinite else { return 0 }
            return Int64(max(min(d, 9.0e18), -9.0e18).rounded())
        }
        func le16(_ x: UInt16) { out.append(UInt8(x & 0xFF)); out.append(UInt8(x >> 8)) }
        func le32(_ x: UInt32) {
            out.append(UInt8(x & 0xFF)); out.append(UInt8((x >> 8) & 0xFF))
            out.append(UInt8((x >> 16) & 0xFF)); out.append(UInt8(x >> 24))
        }
        for f in fields {
            let vals = v.numbers[f.name] ?? []
            for i in 0..<f.count {
                let d = i < vals.count ? vals[i] : 0
                switch f.type {
                case .uint8, .enum: out.append(UInt8(clamping: clamped(d)))
                case .int8:   out.append(UInt8(bitPattern: Int8(clamping: clamped(d))))
                case .uint16: le16(UInt16(clamping: clamped(d)))
                case .int16:  le16(UInt16(bitPattern: Int16(clamping: clamped(d))))
                case .uint32: le32(UInt32(clamping: clamped(d)))
                case .int32:  le32(UInt32(bitPattern: Int32(clamping: clamped(d))))
                case .float:  le32(Float(d).bitPattern)
                }
            }
        }
        return out
    }
}
