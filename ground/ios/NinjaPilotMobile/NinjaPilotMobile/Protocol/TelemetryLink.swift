//  UDP link to the board's telemetry port (pios_wifi.c: WIFI_TCP_PORT 9000,
//  same number for the datagram socket).
//
//  The board latches ONE UDP peer and only lets a new sender take over after
//  the holder has been quiet for 3 s, so this keeps a steady keepalive going.
//  Run the desktop GCS at the same time and the two will fight over the latch.
//
//  This link is also the radio. LiteWing has no RC receiver: pios_board.c maps
//  Throttle/Roll/Pitch/Yaw/FlightMode to the GCS receiver group on every boot,
//  so whoever streams the GCSReceiver object over this socket is flying it.

import Foundation
import Network
import Combine

@MainActor
final class TelemetryLink: ObservableObject {
    enum State: Equatable {
        case idle, connecting, live, failed(String)

        var label: String {
            switch self {
            case .idle: return "Not connected"
            case .connecting: return "Connecting…"
            case .live: return "Live"
            case .failed(let m): return m
            }
        }
    }

    struct PersistEvent: Equatable {
        let objectId: UInt32
        let ok: Bool
        let at: Date
    }

    @Published private(set) var state: State = .idle
    @Published private(set) var objects: [String: UAVObjectValue] = [:]
    @Published private(set) var packetsIn = 0
    @Published private(set) var bytesIn = 0
    @Published private(set) var lastRx: Date?
    @Published private(set) var persist: PersistEvent?
    @Published private(set) var sticksEngaged = false
    @Published var host: String = UserDefaults.standard.string(forKey: "boardHost") ?? "192.168.0.139"

    /// Per-object receive counter, bumped before `objects` publishes, so a
    /// view can tell "MagSensor updated" apart from "something else did".
    private(set) var updateSeq: [String: Int] = [:]

    /// Stick channels in microseconds, GCSReceiver.Channel order. Index 0-4 are
    /// Throttle/Roll/Pitch/Yaw/FlightMode per the board's ChannelNumber 1-5.
    /// Not @Published on purpose: it changes at gesture rate.
    var sticks: [UInt16] = [1000, 1500, 1500, 1500, 1000, 1000, 1000, 1000]

    private var conn: NWConnection?
    private let parser = UAVTalkParser()
    private var pump: Task<Void, Never>?
    private var stickTask: Task<Void, Never>?
    private let defsById: [UInt32: UAVObjectDef]
    private let defsByName: [String: UAVObjectDef]

    /// Telemetry periods asked for on connect, in ms. Everything not listed
    /// keeps whatever the board already had.
    private let baseRates: [String: UInt16] = [
        "AttitudeState": 50,          // 20 Hz -- enough for a smooth horizon
        "FlightStatus": 200,
        "ManualControlCommand": 100,
        "SystemAlarms": 500,
        "GPSPositionSensor": 500,
        "GPSSatellites": 2000,        // big object, slow-moving data
        "SystemStats": 1000,
        "PositionState": 500,
        "VelocityState": 500,
        "HomeLocation": 5000,
        "GPSTime": 5000,
        "MagState": 200,              // the number filtermag.c scores
        "AccelState": 100,            // level check
        "AccelSensor": 250,
        "GyroState": 200,
    ]
    /// Temporary overrides, e.g. MagSensor at 20 ms while calibrating.
    private var extraRates: [String: UInt16] = [:]
    /// Metadata as it was before we raised anything, so we can put it back.
    private var savedMeta: [UInt32: [UInt8]] = [:]

    init() {
        var byId = [UInt32: UAVObjectDef]()
        var byName = [String: UAVObjectDef]()
        for d in uavObjectDefs { byId[d.id] = d; byName[d.name] = d }
        defsById = byId
        defsByName = byName
    }

    func object(_ name: String) -> UAVObjectValue? { objects[name] }
    func def(_ name: String) -> UAVObjectDef? { defsByName[name] }

    var isStale: Bool {
        guard let t = lastRx else { return true }
        return Date().timeIntervalSince(t) > 3.0
    }

    // MARK: - Lifecycle

    func connect() {
        disconnect()
        UserDefaults.standard.set(host, forKey: "boardHost")
        state = .connecting

        let ep = NWEndpoint.hostPort(host: NWEndpoint.Host(host), port: 9000)
        let params = NWParameters.udp
        params.includePeerToPeer = true
        let c = NWConnection(to: ep, using: params)
        conn = c

        c.stateUpdateHandler = { [weak self] st in
            Task { @MainActor in
                guard let self else { return }
                switch st {
                case .ready:
                    self.state = .live
                    self.primeObjects()
                case .failed(let e):
                    self.stopSticks()
                    self.state = .failed(e.localizedDescription)
                case .cancelled:
                    if self.state != .idle { self.state = .idle }
                default:
                    break
                }
            }
        }
        c.start(queue: .global(qos: .userInitiated))
        receive(on: c)

        pump = Task { [weak self] in
            while !Task.isCancelled {
                try? await Task.sleep(nanoseconds: 1_000_000_000)
                guard let self else { return }
                await self.keepalive()
            }
        }
    }

    func disconnect() {
        stopSticks()
        pump?.cancel(); pump = nil
        restoreMetadata()
        conn?.cancel(); conn = nil
        state = .idle
    }

    // MARK: - Sending

    func request(_ name: String) {
        guard let d = defsByName[name] else { return }
        sendRaw(UAVTalk.packet(type: UAVTalk.typeObjReq, objId: d.id))
    }

    /// Send a whole object. `ack` asks the board to confirm receipt -- use it
    /// for settings and calibration, never for the 50 Hz stick stream.
    @discardableResult
    func send(_ value: UAVObjectValue, ack: Bool = false) -> Bool {
        guard state == .live else { return false }
        let payload = value.def.encode(value)
        sendRaw(UAVTalk.packet(type: ack ? UAVTalk.typeObjAck : UAVTalk.typeObj,
                               objId: value.def.id, payload: payload))
        return true
    }

    /// Ask the board to write one settings object to flash.
    func save(_ name: String) {
        guard let target = defsByName[name], let op = defsByName["ObjectPersistence"] else { return }
        var v = UAVObjectValue(def: op)
        v.set("ObjectID", Double(target.id))
        v.set("InstanceID", 0)
        v.set("Operation", option: "Save")
        v.set("Selection", option: "SingleObject")
        send(v, ack: true)
    }

    /// Raise one object's telemetry period for a while (calibration etc).
    func setRate(_ name: String, periodMs: UInt16) {
        guard let d = defsByName[name] else { return }
        extraRates[name] = periodMs
        if savedMeta[d.metaId] != nil {
            applyRate(for: d)
        } else {
            sendRaw(UAVTalk.packet(type: UAVTalk.typeObjReq, objId: d.metaId))
        }
    }

    /// Drop a temporary rate: back to the connect-time rate, or the board's own.
    func clearRate(_ name: String) {
        guard let d = defsByName[name] else { return }
        extraRates[name] = nil
        if baseRates[name] != nil {
            applyRate(for: d)
        } else if let saved = savedMeta[d.metaId] {
            sendRaw(UAVTalk.packet(type: UAVTalk.typeObj, objId: d.metaId, payload: saved))
        }
    }

    // MARK: - Sticks

    func startSticks() {
        guard state == .live, stickTask == nil else { return }
        sticksEngaged = true
        stickTask = Task { [weak self] in
            while !Task.isCancelled {
                guard let self else { return }
                self.sendSticks()
                try? await Task.sleep(nanoseconds: 20_000_000)   // 50 Hz, like the GCS
            }
        }
    }

    /// Stopping the stream is the failsafe: pios_gcsrcvr's supervisor times
    /// the channels out and ManualControl drops to its failsafe behaviour.
    func stopSticks() {
        stickTask?.cancel(); stickTask = nil
        sticksEngaged = false
    }

    private func sendSticks() {
        guard let d = defsByName["GCSReceiver"] else { return }
        var v = UAVObjectValue(def: d)
        v.set("Channel", sticks.map { Double($0) })
        send(v)
    }

    // MARK: - IO

    private func receive(on c: NWConnection) {
        c.receiveMessage { [weak self] data, _, _, error in
            if let data, !data.isEmpty {
                Task { @MainActor in self?.ingest(data) }
            }
            if error == nil {
                self?.receive(on: c)
            }
        }
    }

    private func ingest(_ data: Data) {
        bytesIn += data.count
        lastRx = Date()
        parser.feed(data)
        for p in parser.drain() {
            packetsIn += 1
            // Metadata arrives at objId+1; stash the original once.
            if let def = defsById[p.objId &- 1], p.payload.count >= 8 {
                if savedMeta[def.metaId] == nil {
                    savedMeta[def.metaId] = Array(p.payload[0..<8])
                    applyRate(for: def)
                }
                continue
            }
            guard let def = defsById[p.objId] else { continue }
            let kind = p.type & 0x07
            guard kind == 0x00 || kind == 0x02 else { continue }   // OBJ / OBJ_ACK
            guard let v = def.decode(p.payload) else { continue }
            updateSeq[def.name, default: 0] += 1
            objects[def.name] = v
            if def.name == "ObjectPersistence" {
                let op = v.option("Operation") ?? ""
                if op == "Completed" || op == "Error" {
                    persist = PersistEvent(objectId: UInt32(v.number("ObjectID") ?? 0),
                                           ok: op == "Completed", at: Date())
                }
            }
        }
    }

    private func sendRaw(_ d: Data) { conn?.send(content: d, completion: .idempotent) }

    private func primeObjects() {
        // Ask for each object once so a screen has something to show
        // immediately, and for its metadata so we can raise the rate.
        for d in uavObjectDefs {
            sendRaw(UAVTalk.packet(type: UAVTalk.typeObjReq, objId: d.id))
            if baseRates[d.name] != nil {
                sendRaw(UAVTalk.packet(type: UAVTalk.typeObjReq, objId: d.metaId))
            }
        }
    }

    private func applyRate(for def: UAVObjectDef) {
        guard let period = extraRates[def.name] ?? baseRates[def.name],
              let saved = savedMeta[def.metaId],
              let m = UAVMeta.decode(saved) else { return }
        let payload = UAVMeta.encodePeriodic(flags: m.flags, periodMs: period,
                                             gp: m.gp, lp: m.lp)
        sendRaw(UAVTalk.packet(type: UAVTalk.typeObj, objId: def.metaId, payload: payload))
    }

    private func restoreMetadata() {
        for (metaId, saved) in savedMeta {
            sendRaw(UAVTalk.packet(type: UAVTalk.typeObj, objId: metaId, payload: saved))
        }
        savedMeta.removeAll()
        extraRates.removeAll()
    }

    /// Holds the board's single-peer latch and re-primes anything that never
    /// arrived (a dropped datagram means that object just never shows up).
    private func keepalive() {
        guard state == .live else { return }
        if let fs = defsByName["FlightStatus"] {
            sendRaw(UAVTalk.packet(type: UAVTalk.typeObjReq, objId: fs.id))
        }
        for d in uavObjectDefs where objects[d.name] == nil && d.name != "ObjectPersistence" && d.name != "GCSReceiver" {
            sendRaw(UAVTalk.packet(type: UAVTalk.typeObjReq, objId: d.id))
        }
    }
}
