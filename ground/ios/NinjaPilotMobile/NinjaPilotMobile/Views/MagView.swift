import SwiftUI
import Combine

/// Magnetometer: the live number the alarm is scored on, the thresholds it is
/// scored against, and a free-rotation calibration.
///
/// The calibration is a port of the GCS MagCalibrationModel, not a new
/// method: same binning, same ellipsoid fit, same acceptance tests, same
/// 1.2 s wait for the cleared calibration to land before sampling.
struct MagView: View {
    @ObservedObject var link: TelemetryLink

    enum Phase: Equatable { case idle, clearing, collecting, done, rejected, saved }

    @State private var phase: Phase = .idle
    @State private var xs = [Double]()
    @State private var ys = [Double]()
    @State private var zs = [Double]()
    @State private var bins = Set<Int>()
    @State private var progress = 0
    @State private var lastSeq = 0
    @State private var message = ""
    @State private var memento: UAVObjectValue?
    @State private var pending: UAVObjectValue?
    @State private var warnPct = 5.0
    @State private var errPct = 15.0
    @State private var thresholdsLoaded = false
    @State private var fusionChoice = ""


    // Same constants as magcalibrationmodel.h
    private let MOTION_SPAN_MGA = 150.0
    private let MIN_SAMPLES = 2000
    private let TOTAL_BINS = 26
    private let GOOD_BINS = 20

    private var magState: UAVObjectValue? { link.object("MagState") }
    private var home: UAVObjectValue? { link.object("HomeLocation") }
    private var revo: UAVObjectValue? { link.object("RevoSettings") }
    private var cal: UAVObjectValue? { link.object("RevoCalibration") }

    private var be: Double {
        guard let h = home else { return 0 }
        let b = h.array("Be"); guard b.count == 3 else { return 0 }
        return (b[0] * b[0] + b[1] * b[1] + b[2] * b[2]).squareRoot()
    }
    private var magnitude: Double {
        guard let m = magState else { return 0 }
        let x = m.number("x") ?? 0, y = m.number("y") ?? 0, z = m.number("z") ?? 0
        return (x * x + y * y + z * z).squareRoot()
    }
    /// filtermag.c getMagError(): |(|mag| - |Be|)| / |Be|
    private var deviation: Double { be > 1 ? abs(magnitude - be) / be : 0 }

    private var alarm: String {
        link.object("SystemAlarms")?.optionFor("Alarm", element: "Magnetometer") ?? "—"
    }

    var body: some View {
        ScrollView {
            VStack(spacing: 12) {
                liveCard
                calibrationCard
                fusionCard
                thresholdCard
            }
            .padding(12)
        }
        .background(Color.black)
        .onReceive(link.$objects) { _ in
            sampleIfNew()
            loadThresholdsOnce()
        }
    }

    // MARK: - Live

    private var deviationColor: Color {
        let w = (revo?.number("MagnetometerMaxDeviation", 0) ?? 0.05)
        let e = (revo?.number("MagnetometerMaxDeviation", 1) ?? 0.15)
        if deviation >= e { return Color(red: 1.0, green: 0.35, blue: 0.2) }
        if deviation >= w { return .orange }
        return .green
    }

    private var liveCard: some View {
        VStack(spacing: 10) {
            HStack {
                VStack(alignment: .leading, spacing: 2) {
                    Text("ALARM").font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
                    Text(alarm).font(.system(size: 22, weight: .bold, design: .rounded))
                        .foregroundColor(alarm == "OK" ? .green : (alarm == "Warning" ? .orange : .red))
                }
                Spacer()
                VStack(alignment: .trailing, spacing: 2) {
                    Text("DEVIATION").font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
                    Text(String(format: "%.1f %%", deviation * 100))
                        .font(.system(size: 22, weight: .bold, design: .monospaced))
                        .foregroundColor(deviationColor)
                }
            }
            HStack {
                stat("|MAG|", String(format: "%.0f", magnitude), "mGa")
                stat("|Be|", String(format: "%.0f", be), "mGa")
                stat("WARN / ERR", String(format: "%.0f / %.0f",
                                          (revo?.number("MagnetometerMaxDeviation", 0) ?? 0) * 100,
                                          (revo?.number("MagnetometerMaxDeviation", 1) ?? 0) * 100), "%")
            }
            Text("This is the exact number filtermag.c scores: Warning above the first threshold, Critical above the second, after 5 consecutive samples. Move the board and watch it — anything magnetic nearby (this phone included) shows up here immediately.")
                .font(.caption).foregroundColor(.gray)
        }
        .padding(14)
        .background(Color(white: 0.11)).cornerRadius(10)
    }

    // MARK: - Calibration

    private var calibrationCard: some View {
        VStack(alignment: .leading, spacing: 10) {
            Text("FREE-ROTATION CALIBRATION").font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)

            Text("Put this phone down at least 30 cm from the board first — its magnets will corrupt the fit. Then rotate the board slowly through every orientation, like turning a dice over in your hands, edges and corners included.")
                .font(.caption).foregroundColor(.gray)

            if phase == .collecting || phase == .clearing {
                ProgressView(value: Double(progress), total: 100)
                    .tint(.cyan)
                Text("\(xs.count) samples · \(bins.count)/\(GOOD_BINS) orientations")
                    .font(.system(size: 12, design: .monospaced)).foregroundColor(.white)
            }

            if !message.isEmpty {
                Text(message).font(.system(size: 13))
                    .foregroundColor(phase == .rejected ? .orange : (phase == .saved ? .green : .white))
            }

            HStack {
                switch phase {
                case .idle, .rejected, .saved:
                    Button("Start") { start() }
                        .buttonStyle(.borderedProminent)
                        .disabled(link.state != .live || (home?.int("Set") ?? 0) == 0 || cal == nil)
                case .clearing, .collecting:
                    Button("Cancel") { cancel() }.buttonStyle(.bordered).tint(.red)
                case .done:
                    Button("Save to board") { save() }.buttonStyle(.borderedProminent).tint(.green)
                    Button("Discard") { cancel() }.buttonStyle(.bordered)
                }
            }
            if (home?.int("Set") ?? 0) == 0 {
                Text("HomeLocation is not set — the fit needs the local field |Be|.")
                    .font(.caption).foregroundColor(.orange)
            }
            if let c = cal {
                let b = c.array("mag_bias"), t = c.array("mag_transform")
                Text(String(format: "On board: bias %.0f %.0f %.0f · scale %.3f %.3f %.3f",
                            b.count > 2 ? b[0] : 0, b.count > 2 ? b[1] : 0, b.count > 2 ? b[2] : 0,
                            t.count > 8 ? t[0] : 0, t.count > 8 ? t[4] : 0, t.count > 8 ? t[8] : 0))
                    .font(.system(size: 11, design: .monospaced)).foregroundColor(.gray)
            }
        }
        .padding(14)
        .background(Color(white: 0.11)).cornerRadius(10)
    }

    private func start() {
        guard let current = cal, let sensorDef = link.def("MagSensor") else { return }
        _ = sensorDef
        memento = current
        // Start from a clean slate, exactly as the GCS does: fitting against a
        // previous correction would measure the residual of that correction.
        var zeroed = current
        zeroed.set("mag_bias", [0, 0, 0])
        zeroed.set("mag_transform", [1, 0, 0, 0, 1, 0, 0, 0, 1])
        zeroed.set("MagBiasNullingRate", 0)
        link.send(zeroed, ack: true)
        link.setRate("MagSensor", periodMs: 20)
        xs = []; ys = []; zs = []; bins = []; progress = 0
        pending = nil
        message = "Clearing the previous calibration, one moment…"
        phase = .clearing
        lastSeq = link.updateSeq["MagSensor"] ?? 0
        DispatchQueue.main.asyncAfter(deadline: .now() + 1.2) {
            guard phase == .clearing else { return }
            lastSeq = link.updateSeq["MagSensor"] ?? 0
            message = "Rotate the board now."
            phase = .collecting
        }
    }

    private func cancel() {
        if let m = memento { link.send(m, ack: true) }
        link.clearRate("MagSensor")
        phase = .idle
        message = "Cancelled. Previous calibration restored."
        pending = nil
    }

    /// Port of MagCalibrationModel::getSample, driven by MagSensor updates.
    private func sampleIfNew() {
        guard phase == .collecting else { return }
        let seq = link.updateSeq["MagSensor"] ?? 0
        guard seq != lastSeq, let m = link.object("MagSensor") else { return }
        lastSeq = seq
        let x = m.number("x") ?? 0, y = m.number("y") ?? 0, z = m.number("z") ?? 0
        if x == 0 && y == 0 && z == 0 { return }
        xs.append(x); ys.append(y); zs.append(z)

        // Bin against the bounding-box midpoint, not the running mean, and not
        // at all until there is enough spread to be rotation rather than noise.
        var minv = [xs[0], ys[0], zs[0]], maxv = minv
        for i in 1..<xs.count {
            minv[0] = min(minv[0], xs[i]); maxv[0] = max(maxv[0], xs[i])
            minv[1] = min(minv[1], ys[i]); maxv[1] = max(maxv[1], ys[i])
            minv[2] = min(minv[2], zs[i]); maxv[2] = max(maxv[2], zs[i])
        }
        let span = max(maxv[0] - minv[0], max(maxv[1] - minv[1], maxv[2] - minv[2]))
        if span > MOTION_SPAN_MGA {
            let cx = 0.5 * (minv[0] + maxv[0]), cy = 0.5 * (minv[1] + maxv[1]), cz = 0.5 * (minv[2] + maxv[2])
            let vx = x - cx, vy = y - cy, vz = z - cz
            let n = (vx * vx + vy * vy + vz * vz).squareRoot()
            if n > 0.3 * span {
                let bx = clampBin(vx / n), by = clampBin(vy / n), bz = clampBin(vz / n)
                if bx != 0 || by != 0 || bz != 0 {
                    bins.insert((bx + 1) * 9 + (by + 1) * 3 + (bz + 1))
                }
            }
        }
        let binPct = (100 * bins.count) / GOOD_BINS
        let samplePct = (100 * xs.count) / MIN_SAMPLES
        progress = max(0, min(100, min(binPct, samplePct)))
        if bins.count >= GOOD_BINS && xs.count >= MIN_SAMPLES {
            finish()
        }
    }

    private func clampBin(_ v: Double) -> Int { max(-1, min(1, Int((v * 1.5).rounded()))) }

    /// Port of MagCalibrationModel::finish, same acceptance tests.
    private func finish() {
        link.clearRate("MagSensor")
        guard let fit = fitEllipsoid() else {
            reject("Could not fit those samples. Either the board was tilted but never rolled, or the readings do not describe an ellipsoid at all.")
            return
        }
        let (centre, semi, rms) = fit
        let radius = (semi[0] + semi[1] + semi[2]) / 3.0
        let cov = coverage(centre)
        let expected = be
        let summary = String(format: "Fitted %d samples: offset %.0f %.0f %.0f mGa, axes %.0f %.0f %.0f mGa (local field %.0f), residual %.1f mGa, coverage %.0f%%.",
                             xs.count, centre[0], centre[1], centre[2], semi[0], semi[1], semi[2],
                             expected, rms, cov * 100)
        if cov < 0.5 {
            reject(summary + String(format: "\nRejected: only %.0f%% of orientations were visited.", cov * 100)); return
        }
        if rms > 0.15 * radius {
            reject(summary + String(format: "\nRejected: residual is %.0f%% of the mean axis, so something magnetic moved during the run.", 100 * rms / radius)); return
        }
        if expected > 1.0 && (radius < 0.5 * expected || radius > 2.0 * expected) {
            reject(summary + "\nRejected: fitted axes are nowhere near the local field. Something nearby is magnetic."); return
        }
        guard var out = cal else { reject("Lost RevoCalibration."); return }
        out.set("mag_bias", centre)
        if expected > 1.0 {
            out.set("mag_transform", [expected / semi[0], 0, 0,
                                      0, expected / semi[1], 0,
                                      0, 0, expected / semi[2]])
        }
        pending = out
        message = summary + String(format: "\nResidual %.1f%% of radius. Save to keep it.", 100 * rms / radius)
        phase = .done
    }

    private func reject(_ why: String) {
        if let m = memento { link.send(m, ack: true) }
        message = why
        phase = .rejected
    }

    private func save() {
        guard let p = pending else { return }
        link.send(p, ack: true)
        link.save("RevoCalibration")
        message = "Sent. Waiting for the board to confirm the flash write…"
        phase = .saved
        DispatchQueue.main.asyncAfter(deadline: .now() + 2.5) {
            if let ev = link.persist, ev.objectId == p.def.id, Date().timeIntervalSince(ev.at) < 5 {
                message = ev.ok ? "Saved to flash." : "Board reported an error writing flash."
            } else {
                message = "No flash confirmation heard — check the on-board line above matches."
            }
            link.request("RevoCalibration")
        }
    }

    /// Port of MagCalibrationModel::fitEllipsoid (mean-centred, 6x6 normal equations).
    private func fitEllipsoid() -> (centre: [Double], semi: [Double], rms: Double)? {
        let n = xs.count
        guard n >= 10 else { return nil }
        let mx = xs.reduce(0, +) / Double(n), my = ys.reduce(0, +) / Double(n), mz = zs.reduce(0, +) / Double(n)
        let N = 6
        var A = [[Double]](repeating: [Double](repeating: 0, count: N + 1), count: N)
        for i in 0..<n {
            let x = xs[i] - mx, y = ys[i] - my, z = zs[i] - mz
            let row = [x * x, y * y, z * z, x, y, z]
            for r in 0..<N {
                for c in 0..<N { A[r][c] += row[r] * row[c] }
                A[r][N] += row[r]
            }
        }
        for col in 0..<N {
            var piv = col
            for r in (col + 1)..<N where abs(A[r][col]) > abs(A[piv][col]) { piv = r }
            if abs(A[piv][col]) < 1e-12 { return nil }
            A.swapAt(col, piv)
            for r in 0..<N where r != col {
                let f = A[r][col] / A[col][col]
                for c in col...N { A[r][c] -= f * A[col][c] }
            }
        }
        var p = [Double](repeating: 0, count: N)
        for i in 0..<N { p[i] = A[i][N] / A[i][i] }
        if p[0] <= 0 || p[1] <= 0 || p[2] <= 0 { return nil }
        let centre = [-p[3] / (2 * p[0]) + mx, -p[4] / (2 * p[1]) + my, -p[5] / (2 * p[2]) + mz]
        let sx = centre[0] - mx, sy = centre[1] - my, sz = centre[2] - mz
        let S = 1.0 + p[0] * sx * sx + p[1] * sy * sy + p[2] * sz * sz
        if S <= 0 { return nil }
        let semi = [(S / p[0]).squareRoot(), (S / p[1]).squareRoot(), (S / p[2]).squareRoot()]
        var acc = 0.0
        for i in 0..<n {
            let dx = (xs[i] - centre[0]) / semi[0], dy = (ys[i] - centre[1]) / semi[1], dz = (zs[i] - centre[2]) / semi[2]
            let d = (dx * dx + dy * dy + dz * dz).squareRoot() - 1.0
            acc += d * d
        }
        let rms = (acc / Double(n)).squareRoot() * ((semi[0] + semi[1] + semi[2]) / 3.0)
        return (centre, semi, rms)
    }

    private func coverage(_ centre: [Double]) -> Double {
        var b = Set<Int>()
        for i in 0..<xs.count {
            let vx = xs[i] - centre[0], vy = ys[i] - centre[1], vz = zs[i] - centre[2]
            let n = (vx * vx + vy * vy + vz * vz).squareRoot()
            if n < 1e-6 { continue }
            let bx = clampBin(vx / n), by = clampBin(vy / n), bz = clampBin(vz / n)
            if bx != 0 || by != 0 || bz != 0 { b.insert((bx + 1) * 9 + (by + 1) * 3 + (bz + 1)) }
        }
        return Double(b.count) / Double(TOTAL_BINS)
    }

    // MARK: - Thresholds

    // MARK: - Fusion

    /// The stock lever for a basic test: Basic (Complementary) takes the mag
    /// and GPS out of the attitude chain. stateestimation.c rebuilds the filter
    /// chain live on RevoSettings change, so it applies without a reboot.
    private var fusionCard: some View {
        let options = link.def("RevoSettings")?.fields.first(where: { $0.name == "FusionAlgorithm" })?.options ?? []
        let current = revo?.option("FusionAlgorithm") ?? "—"
        return VStack(alignment: .leading, spacing: 10) {
            Text("ATTITUDE FUSION  (RevoSettings.FusionAlgorithm)")
                .font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
            Text("On board now: \(current)").font(.system(size: 13)).foregroundColor(.white)
            Picker("Fusion", selection: $fusionChoice) {
                ForEach(options, id: \.self) { Text($0).tag($0) }
            }
            .pickerStyle(.menu)
            Text("Basic (Complementary) uses only gyro + accel: the Attitude alarm clears without GPS, the Magnetometer alarm stops (it goes Uninitialised, which does not block arming), and there is no heading — so GPS assist on mode 2 cannot hold position. Fine for a stabilized bench or hover test. Put it back to Complementary+Mag+GPSOutdoor for navigation.")
                .font(.caption).foregroundColor(.gray)
            Button("Apply & save fusion") {
                guard var r = revo, !fusionChoice.isEmpty, fusionChoice != current else { return }
                r.set("FusionAlgorithm", option: fusionChoice)
                link.send(r, ack: true)
                link.save("RevoSettings")
                DispatchQueue.main.asyncAfter(deadline: .now() + 1.0) { link.request("RevoSettings") }
            }
            .buttonStyle(.bordered)
            .disabled(revo == nil || link.state != .live || fusionChoice.isEmpty || fusionChoice == current)
        }
        .padding(14)
        .background(Color(white: 0.11)).cornerRadius(10)
    }

    private func loadThresholdsOnce() {
        guard !thresholdsLoaded, let r = revo else { return }
        fusionChoice = r.option("FusionAlgorithm") ?? ""
        warnPct = (r.number("MagnetometerMaxDeviation", 0) ?? 0.05) * 100
        errPct = (r.number("MagnetometerMaxDeviation", 1) ?? 0.15) * 100
        thresholdsLoaded = true
    }

    private var thresholdCard: some View {
        VStack(alignment: .leading, spacing: 10) {
            Text("ALARM THRESHOLDS  (RevoSettings.MagnetometerMaxDeviation)")
                .font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
            Stepper(String(format: "Warning above %.0f %%", warnPct), value: $warnPct, in: 1...50, step: 1)
            Stepper(String(format: "Critical above %.0f %%", errPct), value: $errPct, in: 2...80, step: 1)
            Text("Stock is 5 / 15. Loosening this hides a bad field from the alarm; it does not make heading any better. Fine for a bench test, not a substitute for calibrating outdoors.")
                .font(.caption).foregroundColor(.gray)
            Button("Apply & save thresholds") {
                guard var r = revo else { return }
                let w = min(warnPct, errPct - 1) / 100, e = errPct / 100
                r.set("MagnetometerMaxDeviation", [w, e])
                link.send(r, ack: true)
                link.save("RevoSettings")
                DispatchQueue.main.asyncAfter(deadline: .now() + 1.0) { link.request("RevoSettings") }
            }
            .buttonStyle(.bordered)
            .disabled(revo == nil || link.state != .live)
            if let ev = link.persist, let d = link.def("RevoSettings"), ev.objectId == d.id,
               Date().timeIntervalSince(ev.at) < 10 {
                Text(ev.ok ? "Thresholds saved to flash." : "Flash write failed.")
                    .font(.caption).foregroundColor(ev.ok ? .green : .red)
            }
        }
        .padding(14)
        .background(Color(white: 0.11)).cornerRadius(10)
    }

    private func stat(_ l: String, _ v: String, _ u: String) -> some View {
        VStack(spacing: 2) {
            Text(l).font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
            Text(v).font(.system(size: 17, weight: .medium, design: .monospaced)).foregroundColor(.white)
            Text(u).font(.system(size: 9)).foregroundColor(.gray)
        }
        .frame(maxWidth: .infinity)
    }
}
