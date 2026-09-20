import SwiftUI
import UIKit

/// Thumb sticks. Turn the phone sideways: left thumb throttle/yaw, right thumb
/// pitch/roll, exactly the mode-2 layout of a transmitter.
///
/// The board is already wired for this -- pios_board.c maps the five control
/// channels to the GCS receiver group on every boot, because LiteWing has no
/// radio receiver. Engaging streams GCSReceiver at 50 Hz; disengaging stops
/// the stream, and the board's receiver supervisor times out into failsafe.
struct FlyView: View {
    @ObservedObject var link: TelemetryLink
    @Environment(\.scenePhase) private var scenePhase

    // Normalised axes. Throttle Y is not spring-centred; it starts at the bottom.
    @State private var leftX = 0.0      // yaw
    @State private var leftY = -1.0     // throttle, starts at the bottom
    @State private var rightX = 0.0     // roll
    @State private var rightY = 0.0     // pitch
    @State private var modePos = 1

    private var fs: UAVObjectValue? { link.object("FlightStatus") }
    private var mc: UAVObjectValue? { link.object("ManualControlCommand") }
    private var mcs: UAVObjectValue? { link.object("ManualControlSettings") }
    private var fms: UAVObjectValue? { link.object("FlightModeSettings") }
    private var att: UAVObjectValue? { link.object("AttitudeState") }

    private var engaged: Bool { link.sticksEngaged }
    private var armed: String { fs?.option("Armed") ?? "—" }

    /// How many switch positions the board is configured for.
    private var modeCount: Int {
        max(1, min(6, mcs?.int("FlightModeNumber") ?? 3))
    }

    var body: some View {
        GeometryReader { geo in
            let landscape = geo.size.width > geo.size.height
            if landscape {
                HStack(spacing: 12) {
                    pad(left: true).frame(maxWidth: .infinity)
                    centre.frame(width: geo.size.width * 0.30)
                    pad(left: false).frame(maxWidth: .infinity)
                }
                .padding(12)
            } else {
                VStack(spacing: 10) {
                    centre
                    HStack(spacing: 14) {
                        pad(left: true)
                        pad(left: false)
                    }
                    .frame(height: geo.size.width / 2 - 20)
                    .padding(.horizontal, 12)
                    Text("Turn the phone sideways for bigger sticks")
                        .font(.caption).foregroundColor(.gray)
                    ControllerView(link: link)
                }
            }
        }
        .background(Color.black)
        .onChange(of: leftX) { _ in push() }
        .onChange(of: leftY) { _ in push() }
        .onChange(of: rightX) { _ in push() }
        .onChange(of: rightY) { _ in push() }
        .onChange(of: modePos) { _ in push() }
        .onChange(of: scenePhase) { phase in
            // Backgrounding the app must never leave sticks streaming.
            if phase != .active { disengage() }
        }
        .onChange(of: link.state) { st in
            if st != .live { disengage() }
        }
        .onDisappear { disengage() }
    }

    // MARK: - Centre column

    private var centre: some View {
        VStack(spacing: 8) {
            Text(armed)
                .font(.system(size: 26, weight: .bold, design: .rounded))
                .foregroundColor(armed == "Armed" ? .red : (armed == "Arming" ? .orange : .green))
            Text(fs?.option("FlightMode") ?? "—")
                .font(.system(size: 15, weight: .semibold)).foregroundColor(.white)

            Text(String(format: "R %+.0f°  P %+.0f°",
                        att?.number("Roll") ?? 0, att?.number("Pitch") ?? 0))
                .font(.system(size: 12, design: .monospaced)).foregroundColor(.gray)

            if modeCount > 1 {
                Picker("Mode", selection: $modePos) {
                    ForEach(1...modeCount, id: \.self) { p in
                        Text("\(p)").tag(p)
                    }
                }
                .pickerStyle(.segmented)
                Text(fms?.option("FlightModePosition", modePos - 1) ?? "")
                    .font(.system(size: 11)).foregroundColor(.gray)
            }

            Button {
                engaged ? disengage() : engage()
            } label: {
                Text(engaged ? "STICKS LIVE — TAP TO DROP" : "ENGAGE STICKS")
                    .font(.system(size: 13, weight: .bold))
                    .frame(maxWidth: .infinity)
                    .padding(.vertical, 12)
            }
            .buttonStyle(.borderedProminent)
            .tint(engaged ? .red : .green)
            .disabled(link.state != .live)

            echo
        }
        .padding(10)
        .background(Color(white: 0.1)).cornerRadius(12)
    }

    /// What the board says it received -- the proof the stream is landing.
    private var echo: some View {
        let ch = mc?.array("Channel") ?? []
        func us(_ i: Int) -> String {
            guard i < ch.count, ch[i] < 60000 else { return "  —" }
            return String(format: "%4.0f", ch[i])
        }
        return VStack(alignment: .leading, spacing: 2) {
            HStack {
                Text("Board sees").font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
                Spacer()
                Text(mc?.option("Connected") == "True" ? "RX OK" : "no RX")
                    .font(.system(size: 10, weight: .bold))
                    .foregroundColor(mc?.option("Connected") == "True" ? .green : .orange)
            }
            Text("T\(us(0)) R\(us(1)) P\(us(2)) Y\(us(3)) M\(us(4))")
                .font(.system(size: 11, design: .monospaced)).foregroundColor(.white)
            Text("Arm: throttle low + \(fms?.option("Arming") ?? "?"), hold")
                .font(.system(size: 10)).foregroundColor(.gray)
        }
        .frame(maxWidth: .infinity, alignment: .leading)
    }

    // MARK: - Pads

    private func pad(left: Bool) -> some View {
        StickPad(x: left ? $leftX : $rightX,
                 y: left ? $leftY : $rightY,
                 centreX: true,
                 centreY: !left,               // throttle holds where you leave it
                 label: left ? "THR / YAW" : "PITCH / ROLL",
                 live: engaged)
    }

    // MARK: - Stream

    private func engage() {
        leftY = -1.0                              // never engage with throttle up
        leftX = 0; rightX = 0; rightY = 0
        push()
        link.startSticks()
        UIApplication.shared.isIdleTimerDisabled = true
    }

    private func disengage() {
        link.stopSticks()
        UIApplication.shared.isIdleTimerDisabled = false
    }

    /// Microseconds, the receiver-side convention pios_board.c configures.
    private func push() {
        func centred(_ v: Double) -> UInt16 { UInt16(1500 + max(-1, min(1, v)) * 500) }
        let thr = UInt16(1000 + (max(-1, min(1, leftY)) + 1) * 500)
        let mode: UInt16 = modeCount <= 1 ? 1500
            : UInt16(1000 + Double(modePos - 1) * (1000.0 / Double(modeCount - 1)))
        link.sticks = [thr, centred(rightX), centred(rightY), centred(leftX), mode,
                       1000, 1000, 1000]
    }
}

struct StickPad: View {
    @Binding var x: Double
    @Binding var y: Double
    let centreX: Bool
    let centreY: Bool
    let label: String
    let live: Bool

    var body: some View {
        GeometryReader { geo in
            let s = min(geo.size.width, geo.size.height)
            let r = s / 2
            let knob = s * 0.30
            let travel = r - knob / 2
            ZStack {
                RoundedRectangle(cornerRadius: 18).fill(Color(white: 0.13))
                Path { p in
                    p.move(to: CGPoint(x: r, y: 8)); p.addLine(to: CGPoint(x: r, y: s - 8))
                    p.move(to: CGPoint(x: 8, y: r)); p.addLine(to: CGPoint(x: s - 8, y: r))
                }
                .stroke(Color(white: 0.25), lineWidth: 1)
                Text(label).font(.system(size: 10, weight: .semibold))
                    .foregroundColor(.gray).position(x: r, y: 14)
                Circle()
                    .fill(live ? Color.cyan : Color(white: 0.4))
                    .frame(width: knob, height: knob)
                    .position(x: r + CGFloat(x) * travel, y: r - CGFloat(y) * travel)
                    .shadow(radius: 4)
            }
            .frame(width: s, height: s)
            .position(x: geo.size.width / 2, y: geo.size.height / 2)
            .contentShape(Rectangle())
            .gesture(
                DragGesture(minimumDistance: 0)
                    .onChanged { g in
                        let ox = (geo.size.width - s) / 2, oy = (geo.size.height - s) / 2
                        x = max(-1, min(1, Double((g.location.x - ox - r) / travel)))
                        y = max(-1, min(1, Double(-(g.location.y - oy - r) / travel)))
                    }
                    .onEnded { _ in
                        if centreX { x = 0 }
                        if centreY { y = 0 }
                    }
            )
        }
        .aspectRatio(1, contentMode: .fit)
    }
}
