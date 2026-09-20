import SwiftUI

struct ContentView: View {
    @ObservedObject var link: TelemetryLink
    @State private var showSetup = false
    @State private var scanning = false
    @State private var found: [BoardDiscovery.Found] = []
    @State private var scanned = false

    var body: some View {
        VStack(spacing: 0) {
            statusBar
            TabView {
                HorizonView(link: link)
                    .tabItem { Label("Horizon", systemImage: "airplane") }
                FlyView(link: link)
                    .tabItem { Label("Fly", systemImage: "gamecontroller.fill") }
                MagView(link: link)
                    .tabItem { Label("Mag", systemImage: "location.north.line.fill") }
                AlarmsView(link: link)
                    .tabItem { Label("Alarms", systemImage: "exclamationmark.triangle") }
                GPSView(link: link)
                    .tabItem { Label("GPS", systemImage: "antenna.radiowaves.left.and.right") }
            }
        }
        .background(Color.black)
        .sheet(isPresented: $showSetup) { setupSheet }
    }

    private var dotColor: Color {
        switch link.state {
        case .live: return link.isStale ? .orange : .green
        case .connecting: return .yellow
        case .failed: return .red
        case .idle: return .gray
        }
    }

    private var statusBar: some View {
        HStack(spacing: 10) {
            Circle().fill(dotColor).frame(width: 10, height: 10)
            VStack(alignment: .leading, spacing: 1) {
                Text(link.state == .live && link.isStale ? "No data" : link.state.label)
                    .font(.system(size: 13, weight: .semibold)).foregroundColor(.white)
                Text(link.host).font(.system(size: 10, design: .monospaced))
                    .foregroundColor(.gray)
            }
            Spacer()
            Button(link.state == .idle ? "Connect" : "Disconnect") {
                if link.state == .idle { link.connect() } else { link.disconnect() }
            }
            .font(.system(size: 13, weight: .semibold))
            .buttonStyle(.borderedProminent)
            Button { showSetup = true } label: {
                Image(systemName: "gearshape.fill").foregroundColor(.gray)
            }
        }
        .padding(.horizontal, 14)
        .padding(.vertical, 8)
        .background(Color(white: 0.12))
    }

    private var setupSheet: some View {
        NavigationView {
            Form {
                Section("Board address") {
                    TextField("192.168.0.139", text: $link.host)
                        .keyboardType(.decimalPad)
                        .font(.system(.body, design: .monospaced))
                    Text("UDP port 9000. The phone must be on the same Wi-Fi network as the board.")
                        .font(.caption).foregroundColor(.secondary)
                }

                Section("Find the board") {
                    Button {
                        scanning = true; found = []; scanned = false
                        BoardDiscovery.scan { hits in
                            found = hits; scanning = false; scanned = true
                            if hits.count == 1 { link.host = hits[0].ip }
                        }
                    } label: {
                        HStack {
                            Text(scanning ? "Scanning…" : "Scan this network")
                            Spacer()
                            if scanning { ProgressView() }
                        }
                    }
                    .disabled(scanning)

                    ForEach(found) { f in
                        Button {
                            link.host = f.ip
                        } label: {
                            HStack {
                                Text(f.ip).font(.system(.body, design: .monospaced))
                                Spacer()
                                if link.host == f.ip {
                                    Image(systemName: "checkmark").foregroundColor(.accentColor)
                                }
                            }
                        }
                    }

                    if scanned && found.isEmpty {
                        Text("Nothing answered UAVTalk on this subnet. Check the board is powered and on this Wi-Fi, then enter the IP by hand.")
                            .font(.caption).foregroundColor(.secondary)
                    }
                    Text("Sends one small request to every address on your subnet and keeps whatever answers. This takes the board's single UDP peer, the same as connecting does.")
                        .font(.caption).foregroundColor(.secondary)
                }
                Section("One client at a time") {
                    Text("The board latches a single UDP peer and only hands it over after the current holder has been silent for 3 seconds. Disconnect the desktop GCS before connecting here, or the two will trade the stream back and forth.")
                        .font(.caption)
                }
                Section("Telemetry rates") {
                    Text("Connecting raises the update rate on the objects these screens use, and puts the board's original rates back on disconnect. Force-quitting the app skips that restore.")
                        .font(.caption)
                }
            }
            .navigationTitle("Setup")
            .toolbar {
                ToolbarItem(placement: .confirmationAction) {
                    Button("Done") { showSetup = false }
                }
            }
        }
    }
}
