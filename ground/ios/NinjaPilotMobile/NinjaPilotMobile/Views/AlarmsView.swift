import SwiftUI

/// SystemAlarms, worst-first. Severity names come straight from the XML enum
/// (Uninitialised, OK, Warning, Critical, Error) so they cannot drift.
struct AlarmsView: View {
    @ObservedObject var link: TelemetryLink

    private struct Row: Identifiable {
        let id = UUID()
        let name: String
        let severity: String
        let rank: Int
    }

    private var rows: [Row] {
        guard let sa = link.object("SystemAlarms") else { return [] }
        let names = sa.elementNames("Alarm")
        return names.enumerated().compactMap { i, n in
            guard let sev = sa.option("Alarm", i) else { return nil }
            return Row(name: n, severity: sev, rank: Self.rank(sev))
        }
        .sorted { ($0.rank, $0.name) > ($1.rank, $1.name) }
    }

    private static func rank(_ s: String) -> Int {
        switch s {
        case "Error": return 4
        case "Critical": return 3
        case "Warning": return 2
        case "OK": return 1
        default: return 0            // Uninitialised
        }
    }

    private static func color(_ s: String) -> Color {
        switch s {
        case "Error": return .red
        case "Critical": return Color(red: 1.0, green: 0.35, blue: 0.2)
        case "Warning": return .orange
        case "OK": return .green
        default: return .gray
        }
    }

    private var worst: String {
        rows.first(where: { $0.rank >= 2 })?.severity ?? (rows.isEmpty ? "—" : "OK")
    }

    var body: some View {
        VStack(spacing: 0) {
            summary
            if rows.isEmpty {
                Spacer()
                Text("Waiting for SystemAlarms…").foregroundColor(.gray)
                Spacer()
            } else {
                ScrollView {
                    LazyVStack(spacing: 1) {
                        ForEach(rows) { r in
                            HStack {
                                Circle().fill(Self.color(r.severity))
                                    .frame(width: 10, height: 10)
                                Text(r.name)
                                    .font(.system(size: 15, design: .rounded))
                                    .foregroundColor(r.rank == 0 ? .gray : .white)
                                Spacer()
                                Text(r.severity)
                                    .font(.system(size: 13, weight: .semibold, design: .monospaced))
                                    .foregroundColor(Self.color(r.severity))
                            }
                            .padding(.horizontal, 14)
                            .padding(.vertical, 9)
                            .background(Color(white: r.rank >= 2 ? 0.14 : 0.07))
                        }
                    }
                }
            }
        }
        .background(Color.black)
    }

    private var summary: some View {
        let bad = rows.filter { $0.rank >= 2 }.count
        let uninit = rows.filter { $0.rank == 0 }.count
        return VStack(spacing: 4) {
            Text(worst)
                .font(.system(size: 30, weight: .bold, design: .rounded))
                .foregroundColor(Self.color(worst))
            Text("\(bad) raised · \(rows.count - bad - uninit) OK · \(uninit) uninitialised")
                .font(.system(size: 12)).foregroundColor(.gray)
        }
        .frame(maxWidth: .infinity)
        .padding(.vertical, 14)
        .background(Color(white: 0.1))
    }
}
