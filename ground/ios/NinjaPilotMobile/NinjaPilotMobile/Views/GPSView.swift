import SwiftUI

/// Fix quality up top, per-satellite SNR bars below.
struct GPSView: View {
    @ObservedObject var link: TelemetryLink

    private var pos: UAVObjectValue? { link.object("GPSPositionSensor") }
    private var sats: UAVObjectValue? { link.object("GPSSatellites") }
    private var home: UAVObjectValue? { link.object("HomeLocation") }

    private struct Sat: Identifiable {
        let id: Int          // PRN
        let elevation: Double
        let azimuth: Double
        let snr: Double
    }

    private var satList: [Sat] {
        guard let s = sats else { return [] }
        let prn = s.array("PRN"), el = s.array("Elevation")
        let az = s.array("Azimuth"), snr = s.array("SNR")
        let n = min(Int(s.number("SatsInView") ?? 0), prn.count)
        guard n > 0 else { return [] }
        return (0..<n).map {
            Sat(id: Int(prn[$0]),
                elevation: $0 < el.count ? el[$0] : 0,
                azimuth: $0 < az.count ? az[$0] : 0,
                snr: $0 < snr.count ? snr[$0] : 0)
        }.sorted { $0.snr > $1.snr }
    }

    var body: some View {
        ScrollView {
            VStack(spacing: 12) {
                fixCard
                if !satList.isEmpty { satCard } else {
                    Text("No satellite detail yet")
                        .font(.system(size: 13)).foregroundColor(.gray)
                        .frame(maxWidth: .infinity).padding(.vertical, 20)
                }
                positionCard
            }
            .padding(12)
        }
        .background(Color.black)
    }

    private var status: String { pos?.option("Status") ?? "—" }

    private var statusColor: Color {
        switch status {
        case "Fix3D": return .green
        case "Fix2D": return .orange
        case "NoFix": return .red
        default: return .gray
        }
    }

    private var fixCard: some View {
        VStack(spacing: 10) {
            HStack {
                VStack(alignment: .leading, spacing: 2) {
                    Text("FIX").font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
                    Text(status).font(.system(size: 22, weight: .bold, design: .rounded))
                        .foregroundColor(statusColor)
                }
                Spacer()
                stat("SATS", String(Int(pos?.number("Satellites") ?? 0)))
                stat("PDOP", String(format: "%.2f", pos?.number("PDOP") ?? 0))
            }
            HStack {
                stat("HDOP", String(format: "%.2f", pos?.number("HDOP") ?? 0))
                stat("VDOP", String(format: "%.2f", pos?.number("VDOP") ?? 0))
                stat("IN VIEW", String(Int(sats?.number("SatsInView") ?? 0)))
            }
        }
        .padding(14)
        .background(Color(white: 0.11)).cornerRadius(10)
    }

    private var satCard: some View {
        VStack(alignment: .leading, spacing: 6) {
            Text("SATELLITES").font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
            ForEach(satList) { s in
                HStack(spacing: 8) {
                    Text(String(format: "%3d", s.id))
                        .font(.system(size: 12, design: .monospaced)).foregroundColor(.white)
                        .frame(width: 32, alignment: .trailing)
                    GeometryReader { geo in
                        ZStack(alignment: .leading) {
                            RoundedRectangle(cornerRadius: 3).fill(Color(white: 0.2))
                            RoundedRectangle(cornerRadius: 3)
                                .fill(snrColor(s.snr))
                                .frame(width: geo.size.width * min(s.snr / 50.0, 1.0))
                        }
                    }
                    .frame(height: 14)
                    Text(String(format: "%2.0f", s.snr))
                        .font(.system(size: 12, design: .monospaced))
                        .foregroundColor(snrColor(s.snr)).frame(width: 24)
                    Text(String(format: "e%2.0f a%3.0f", s.elevation, s.azimuth))
                        .font(.system(size: 10, design: .monospaced)).foregroundColor(.gray)
                }
            }
        }
        .padding(14)
        .background(Color(white: 0.11)).cornerRadius(10)
    }

    private func snrColor(_ snr: Double) -> Color {
        if snr >= 35 { return .green }
        if snr >= 25 { return .yellow }
        if snr > 0 { return .orange }
        return Color(white: 0.3)
    }

    private var positionCard: some View {
        VStack(alignment: .leading, spacing: 8) {
            Text("POSITION").font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
            kv("Latitude", String(format: "%.7f°", (pos?.number("Latitude") ?? 0) / 1e7))
            kv("Longitude", String(format: "%.7f°", (pos?.number("Longitude") ?? 0) / 1e7))
            kv("Altitude", String(format: "%.1f m", pos?.number("Altitude") ?? 0))
            kv("Geoid sep.", String(format: "%.1f m", pos?.number("GeoidSeparation") ?? 0))
            kv("Ground speed", String(format: "%.2f m/s", pos?.number("Groundspeed") ?? 0))
            kv("Heading", String(format: "%.1f°", pos?.number("Heading") ?? 0))
            Divider().background(Color(white: 0.25))
            kv("Home set", (home?.int("Set") ?? 0) != 0 ? "YES" : "NO")
            kv("Home lat", String(format: "%.7f°", (home?.number("Latitude") ?? 0) / 1e7))
            kv("Home lon", String(format: "%.7f°", (home?.number("Longitude") ?? 0) / 1e7))
            kv("Be", String(format: "%.0f, %.0f, %.0f mGa",
                            home?.number("Be", 0) ?? 0,
                            home?.number("Be", 1) ?? 0,
                            home?.number("Be", 2) ?? 0))
        }
        .padding(14)
        .background(Color(white: 0.11)).cornerRadius(10)
    }

    private func stat(_ l: String, _ v: String) -> some View {
        VStack(spacing: 2) {
            Text(l).font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
            Text(v).font(.system(size: 17, weight: .medium, design: .monospaced)).foregroundColor(.white)
        }
        .frame(maxWidth: .infinity)
    }

    private func kv(_ k: String, _ v: String) -> some View {
        HStack {
            Text(k).font(.system(size: 13)).foregroundColor(.gray)
            Spacer()
            Text(v).font(.system(size: 13, design: .monospaced)).foregroundColor(.white)
        }
    }
}
