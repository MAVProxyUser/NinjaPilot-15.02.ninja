//  Finding the board without typing an IP.
//
//  NOT by listening for the board's UDP beacon on :9999. The firmware does
//  broadcast "NINJAPILOT <ip> <port>" every 2 s and the desktop GCS uses it,
//  but receiving an incoming UDP broadcast is one of the things Apple's
//  multicast entitlement covers, and that entitlement needs Apple's approval
//  and is not available to a free personal team. Enforcement was loose on
//  iOS 14/15; it is real on iOS 16, which is what the test phone runs.
//
//  Unicast carries no such restriction -- only the local-network prompt. The
//  board replies to whoever sends it a datagram, so sweeping our own /24 with
//  a tiny UAVTalk request finds it just as well, in well under a second.

import Foundation
import Darwin

enum BoardDiscovery {

    struct Found: Identifiable, Equatable {
        var id: String { ip }
        let ip: String
    }

    /// Our IPv4 address and netmask on the Wi-Fi interface.
    static func localIPv4() -> (ip: UInt32, mask: UInt32)? {
        var head: UnsafeMutablePointer<ifaddrs>?
        guard getifaddrs(&head) == 0, let first = head else { return nil }
        defer { freeifaddrs(head) }

        var best: (UInt32, UInt32)?
        for ptr in sequence(first: first, next: { $0.pointee.ifa_next }) {
            let ifa = ptr.pointee
            guard let sa = ifa.ifa_addr, sa.pointee.sa_family == UInt8(AF_INET),
                  let nm = ifa.ifa_netmask else { continue }
            let name = String(cString: ifa.ifa_name)
            guard name.hasPrefix("en") else { continue }       // skip lo0, pdp_ip*
            let ip = sa.withMemoryRebound(to: sockaddr_in.self, capacity: 1) {
                UInt32(bigEndian: $0.pointee.sin_addr.s_addr)
            }
            let mask = nm.withMemoryRebound(to: sockaddr_in.self, capacity: 1) {
                UInt32(bigEndian: $0.pointee.sin_addr.s_addr)
            }
            guard ip != 0, mask != 0 else { continue }
            if best == nil { best = (ip, mask) }
        }
        return best
    }

    static func ipString(_ v: UInt32) -> String {
        "\((v >> 24) & 0xFF).\((v >> 16) & 0xFF).\((v >> 8) & 0xFF).\(v & 0xFF)"
    }

    /// Sweep the local subnet for anything that answers UAVTalk on `port`.
    ///
    /// Sends one OBJ_REQ per host and listens for a well-formed reply. Hosts
    /// that are not the board simply never answer -- no ICMP handling needed.
    ///
    /// Note this will take the board's single UDP peer latch, the same as
    /// connecting does.
    static func scan(port: UInt16 = 9000,
                     timeout: TimeInterval = 2.0,
                     completion: @escaping ([Found]) -> Void) {
        DispatchQueue.global(qos: .userInitiated).async {
            var results = [Found]()
            defer { DispatchQueue.main.async { completion(results) } }

            guard let (ip, mask) = localIPv4() else { return }
            // Refuse to sweep anything wider than a /22 -- on a large flat
            // network this would be thousands of packets for no good reason.
            let hostCount = ~mask
            guard hostCount > 0, hostCount <= 1022 else { return }

            let fd = socket(AF_INET, SOCK_DGRAM, 0)
            guard fd >= 0 else { return }
            defer { close(fd) }

            var tv = timeval(tv_sec: 0, tv_usec: 200_000)
            setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, socklen_t(MemoryLayout<timeval>.size))

            // Cheapest thing the board will answer: request FlightStatus.
            let probe: Data = {
                if let fs = uavObjectDefs.first(where: { $0.name == "FlightStatus" }) {
                    return UAVTalk.packet(type: UAVTalk.typeObjReq, objId: fs.id)
                }
                return UAVTalk.packet(type: UAVTalk.typeObjReq, objId: 0)
            }()

            let network = ip & mask
            let selfHost = ip
            // 1 ..< hostCount, not through: the last address in the subnet is
            // the directed broadcast, and sending to it is a broadcast send --
            // the exact thing the multicast entitlement gates.
            for host in 1..<hostCount {
                let target = network | host
                if target == selfHost { continue }
                var addr = sockaddr_in()
                addr.sin_len = UInt8(MemoryLayout<sockaddr_in>.size)
                addr.sin_family = sa_family_t(AF_INET)
                addr.sin_port = port.bigEndian
                addr.sin_addr.s_addr = target.bigEndian
                _ = probe.withUnsafeBytes { raw in
                    withUnsafePointer(to: &addr) { ap in
                        ap.withMemoryRebound(to: sockaddr.self, capacity: 1) { sap in
                            sendto(fd, raw.baseAddress, raw.count, 0,
                                   sap, socklen_t(MemoryLayout<sockaddr_in>.size))
                        }
                    }
                }
            }

            // Collect replies until the window closes.
            let deadline = Date().addingTimeInterval(timeout)
            var buf = [UInt8](repeating: 0, count: 2048)
            var seen = Set<String>()
            while Date() < deadline {
                var from = sockaddr_in()
                var fromLen = socklen_t(MemoryLayout<sockaddr_in>.size)
                let n = withUnsafeMutablePointer(to: &from) { fp in
                    fp.withMemoryRebound(to: sockaddr.self, capacity: 1) { sap in
                        recvfrom(fd, &buf, buf.count, 0, sap, &fromLen)
                    }
                }
                guard n > 0 else { continue }
                // Only count it if it actually parses as UAVTalk.
                let parser = UAVTalkParser()
                parser.feed(Data(buf[0..<n]))
                guard !parser.drain().isEmpty else { continue }
                let who = ipString(UInt32(bigEndian: from.sin_addr.s_addr))
                if seen.insert(who).inserted {
                    results.append(Found(ip: who))
                }
            }
        }
    }
}
