import SwiftUI

/// Arming state, flight mode + assist, stick axes, and raw receiver channels.
struct ControllerView: View {
    @ObservedObject var link: TelemetryLink

    private var fs: UAVObjectValue? { link.object("FlightStatus") }
    private var mc: UAVObjectValue? { link.object("ManualControlCommand") }
    private var ss: UAVObjectValue? { link.object("SystemStats") }

    private var armed: String { fs?.option("Armed") ?? "—" }
    private var mode: String { fs?.option("FlightMode") ?? "—" }
    private var assist: String { fs?.option("FlightModeAssist") ?? "None" }

    private var armedColor: Color {
        switch armed {
        case "Armed": return .red
        case "Arming": return .orange
        case "Disarmed": return .green
        default: return .gray
        }
    }

    var body: some View {
        ScrollView {
            VStack(spacing: 12) {
                stateCard
                sticksCard
                channelsCard
                statsCard
            }
            .padding(12)
        }
        .background(Color.black)
    }

    private var stateCard: some View {
        VStack(spacing: 10) {
            HStack {
                VStack(alignment: .leading, spacing: 2) {
                    Text("ARMED").font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
                    Text(armed).font(.system(size: 24, weight: .bold, design: .rounded))
                        .foregroundColor(armedColor)
                }
                Spacer()
                VStack(alignment: .trailing, spacing: 2) {
                    Text("FLIGHT MODE").font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
                    Text(mode).font(.system(size: 20, weight: .semibold, design: .rounded))
                        .foregroundColor(.white)
                }
            }
            Divider().background(Color(white: 0.25))
            HStack {
                kv("Switch position", mc.map { String(($0.int("FlightModeSwitchPosition") ?? 0) + 1) } ?? "—")
                Spacer()
                kv("Receiver", mc?.option("Connected") == "True" ? "Connected" : "No signal")
            }
            HStack {
                kv("GPS assist", assist)
                Spacer()
                kv("Assist state", fs?.option("AssistedControlState") ?? "—")
            }
            HStack {
                kv("Thrust mode", fs?.option("AssistedThrottleState") ?? "—")
                Spacer()
                kv("Control chain", chainDescription)
            }
        }
        .padding(14)
        .background(Color(white: 0.11)).cornerRadius(10)
    }

    /// ControlChain is three booleans; the XML element names say which is which.
    private var chainDescription: String {
        guard let fs else { return "—" }
        let names = fs.elementNames("ControlChain")
        let on = names.enumerated().compactMap { i, n in
            fs.option("ControlChain", i) == "true" ? n : nil
        }
        return on.isEmpty ? "none" : on.joined(separator: "+")
    }

    private var sticksCard: some View {
        VStack(alignment: .leading, spacing: 10) {
            Text("STICKS").font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
            axis("Roll", mc?.number("Roll") ?? 0, bipolar: true)
            axis("Pitch", mc?.number("Pitch") ?? 0, bipolar: true)
            axis("Yaw", mc?.number("Yaw") ?? 0, bipolar: true)
            axis("Thrust", mc?.number("Thrust") ?? 0, bipolar: false)
        }
        .padding(14)
        .background(Color(white: 0.11)).cornerRadius(10)
    }

    /// Bipolar axes run -1..1 and fill out from the centre; thrust runs 0..1.
    private func axis(_ label: String, _ v: Double, bipolar: Bool) -> some View {
        HStack(spacing: 8) {
            Text(label).font(.system(size: 12)).foregroundColor(.gray)
                .frame(width: 48, alignment: .leading)
            GeometryReader { geo in
                let w = geo.size.width
                ZStack(alignment: .leading) {
                    RoundedRectangle(cornerRadius: 3).fill(Color(white: 0.2))
                    if bipolar {
                        let clamped = max(-1, min(1, v))
                        let half = w / 2
                        RoundedRectangle(cornerRadius: 3)
                            .fill(Color.cyan)
                            .frame(width: abs(clamped) * half)
                            .offset(x: clamped >= 0 ? half : half - abs(clamped) * half)
                        Rectangle().fill(Color(white: 0.45)).frame(width: 1).offset(x: half)
                    } else {
                        RoundedRectangle(cornerRadius: 3)
                            .fill(Color.cyan)
                            .frame(width: max(0, min(1, v)) * w)
                    }
                }
            }
            .frame(height: 16)
            Text(String(format: "%+.2f", v))
                .font(.system(size: 12, design: .monospaced)).foregroundColor(.white)
                .frame(width: 52, alignment: .trailing)
        }
    }

    private var channelsCard: some View {
        VStack(alignment: .leading, spacing: 6) {
            Text("RECEIVER CHANNELS (µs)").font(.system(size: 10, weight: .semibold))
                .foregroundColor(.gray)
            let ch = mc?.array("Channel") ?? []
            ForEach(Array(ch.enumerated()), id: \.offset) { i, v in
                HStack(spacing: 8) {
                    Text("\(i + 1)").font(.system(size: 11, design: .monospaced))
                        .foregroundColor(.gray).frame(width: 18, alignment: .trailing)
                    GeometryReader { geo in
                        // Typical RC band is 1000-2000 us.
                        let frac = max(0, min(1, (v - 1000) / 1000))
                        ZStack(alignment: .leading) {
                            RoundedRectangle(cornerRadius: 2).fill(Color(white: 0.2))
                            RoundedRectangle(cornerRadius: 2)
                                .fill(v > 0 ? Color.purple : Color(white: 0.25))
                                .frame(width: geo.size.width * frac)
                        }
                    }
                    .frame(height: 10)
                    Text(String(format: "%4.0f", v))
                        .font(.system(size: 11, design: .monospaced)).foregroundColor(.white)
                        .frame(width: 38, alignment: .trailing)
                }
            }
        }
        .padding(14)
        .background(Color(white: 0.11)).cornerRadius(10)
    }

    private var statsCard: some View {
        VStack(alignment: .leading, spacing: 8) {
            Text("BOARD").font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
            kvRow("CPU load", "\(Int(ss?.number("CPULoad") ?? 0)) %")
            kvRow("CPU temp", "\(Int(ss?.number("CPUTemp") ?? 0)) °C")
            kvRow("Heap free", "\(Int(ss?.number("HeapRemaining") ?? 0)) B")
            kvRow("Flight time", flightTime)
            kvRow("Link", "\(link.packetsIn) pkts · \(link.bytesIn / 1024) kB")
        }
        .padding(14)
        .background(Color(white: 0.11)).cornerRadius(10)
    }

    private var flightTime: String {
        let ms = Int(ss?.number("FlightTime") ?? 0)
        let s = ms / 1000
        return String(format: "%d:%02d:%02d", s / 3600, (s % 3600) / 60, s % 60)
    }

    private func kv(_ k: String, _ v: String) -> some View {
        VStack(alignment: .leading, spacing: 2) {
            Text(k).font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
            Text(v).font(.system(size: 14, design: .monospaced)).foregroundColor(.white)
        }
    }

    private func kvRow(_ k: String, _ v: String) -> some View {
        HStack {
            Text(k).font(.system(size: 13)).foregroundColor(.gray)
            Spacer()
            Text(v).font(.system(size: 13, design: .monospaced)).foregroundColor(.white)
        }
    }
}
