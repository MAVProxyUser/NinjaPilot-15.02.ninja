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
    @State private var sourceChoice = ""
    @State private var switching = false

    private static let dsmGroup = "DSM (MainPort)"
    private static let gcsGroup = "GCS"

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
        .onReceive(link.$objects) { _ in
            if !switching && !engaged, !source.isEmpty, sourceChoice != source { sourceChoice = source }
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

            Picker("Source", selection: $sourceChoice) {
                Text("Spektrum").tag(Self.dsmGroup)
                Text("Phone").tag(Self.gcsGroup)
            }
            .pickerStyle(.segmented)
            .disabled(engaged || switching || mcs == nil || link.state != .live)
            .onChange(of: sourceChoice) { g in
                if !g.isEmpty && g != source && !switching { switchSource(to: g) }
            }

            Button {
                engaged ? disengage() : engage()
            } label: {
                Text(engaged ? "STICKS LIVE — TAP TO DROP" : (phoneIsSource ? "ENGAGE STICKS" : "SWITCH SOURCE TO PHONE FIRST"))
                    .font(.system(size: 13, weight: .bold))
                    .frame(maxWidth: .infinity)
                    .padding(.vertical, 12)
            }
            .buttonStyle(.borderedProminent)
            .tint(engaged ? .red : .green)
            .disabled(link.state != .live || !phoneIsSource)

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
                Text("Board sees · \(phoneIsSource ? "phone" : (source.isEmpty ? "—" : "Spektrum"))")
                    .font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
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

    // MARK: - Source (Spektrum satellite vs this phone)

    /// Whatever the Throttle channel's group says the radio is.
    private var source: String { mcs?.option("ChannelGroups", 0) ?? "" }
    private var phoneIsSource: Bool { source == Self.gcsGroup }

    /// Flip the five control channels between the DSM satellite and the GCS
    /// receiver, the way tools/bench_test.py does -- and park the other four
    /// groups on None while the phone has them: an Accessory left on DSM with
    /// the transmitter off times out and invalidates the whole input.
    ///
    /// Endpoints are swapped too, because the two sources speak different
    /// units (DSM 2048 counts vs microseconds). The DSM set is stashed on the
    /// phone before it is overwritten and restored on the way back, so a
    /// measured rc_calibrate travel survives a round trip.
    private func switchSource(to group: String) {
        guard var m = mcs, !engaged, group != source else { return }
        switching = true
        let n = m.def.fields.first(where: { $0.name == "ChannelGroups" })?.count ?? 9
        let ud = UserDefaults.standard
        if group == Self.gcsGroup {
            let stash: [String: [Double]] = [
                "min": m.array("ChannelMin"), "neutral": m.array("ChannelNeutral"),
                "max": m.array("ChannelMax"), "groups": m.array("ChannelGroups"),
            ]
            if source == Self.dsmGroup { ud.set(stash, forKey: "dsmStash") }
            for i in 0..<n { m.set("ChannelGroups", option: i < 5 ? Self.gcsGroup : "None", index: i) }
            var mn = m.array("ChannelMin"), nu = m.array("ChannelNeutral"), mx = m.array("ChannelMax")
            for i in 0..<min(5, mn.count) { mn[i] = 1000; mx[i] = 2000; nu[i] = i == 0 ? 1050 : 1500 }
            m.set("ChannelMin", mn); m.set("ChannelNeutral", nu); m.set("ChannelMax", mx)
        } else {
            let stash = ud.dictionary(forKey: "dsmStash") as? [String: [Double]]
            if let st = stash, let g = st["groups"], g.count == n,
               let mn = st["min"], let nu = st["neutral"], let mx = st["max"] {
                for i in 0..<n { m.set("ChannelGroups", index: i, g[i]) }
                m.set("ChannelMin", mn); m.set("ChannelNeutral", nu); m.set("ChannelMax", mx)
            } else {
                // Textbook DSM 2048 seeds, throttle neutral above its minimum
                // so the stick at the bottom reads as "low" (armhandler.c).
                for i in 0..<n { m.set("ChannelGroups", option: i < 5 ? Self.dsmGroup : "None", index: i) }
                var mn = m.array("ChannelMin"), nu = m.array("ChannelNeutral"), mx = m.array("ChannelMax")
                for i in 0..<min(5, mn.count) { mn[i] = 342; mx[i] = 1706; nu[i] = i == 0 ? 410 : 1024 }
                m.set("ChannelMin", mn); m.set("ChannelNeutral", nu); m.set("ChannelMax", mx)
            }
        }
        var num = m.array("ChannelNumber")
        for i in 0..<num.count { num[i] = i < 5 ? Double(i + 1) : 0 }
        m.set("ChannelNumber", num)
        link.send(m, ack: true)
        link.save("ManualControlSettings")
        DispatchQueue.main.asyncAfter(deadline: .now() + 1.2) {
            link.request("ManualControlSettings")
            switching = false
        }
    }

    // MARK: - Stream

    private func engage() {
        guard phoneIsSource else { return }
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

    /// Endpoints as the board has them stored, so the sticks land wherever
    /// ManualControlSettings says min/neutral/max are, not where we assume.
    private func endpoints(_ i: Int) -> (min: Double, neutral: Double, max: Double) {
        let mn = mcs?.array("ChannelMin") ?? [], nu = mcs?.array("ChannelNeutral") ?? [], mx = mcs?.array("ChannelMax") ?? []
        guard i < mn.count, i < nu.count, i < mx.count, mx[i] > mn[i] else {
            return (1000, i == 0 ? 1050 : 1500, 2000)
        }
        return (mn[i], nu[i], mx[i])
    }

    private func centred(_ axis: Double, _ i: Int) -> UInt16 {
        let e = endpoints(i), a = max(-1, min(1, axis))
        let v = a >= 0 ? e.neutral + a * (e.max - e.neutral) : e.neutral + a * (e.neutral - e.min)
        return UInt16(max(0, min(65000, v)))
    }

    private func push() {
        let e0 = endpoints(0)
        let t = (max(-1, min(1, leftY)) + 1) / 2                // 0 at the bottom
        let thr = UInt16(max(0, min(65000, e0.min + t * (e0.max - e0.min))))
        let e4 = endpoints(4)
        let mode: UInt16 = modeCount <= 1 ? UInt16(e4.neutral)
            : UInt16(e4.min + Double(modePos - 1) * (e4.max - e4.min) / Double(modeCount - 1))
        link.sticks = [thr, centred(rightX, 1), centred(rightY, 2), centred(leftX, 3), mode,
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
