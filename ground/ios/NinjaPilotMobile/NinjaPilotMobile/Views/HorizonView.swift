import SwiftUI

/// Artificial horizon + the numbers you actually stare at on a bench test.
struct HorizonView: View {
    @ObservedObject var link: TelemetryLink

    private var att: UAVObjectValue? { link.object("AttitudeState") }
    private var roll: Double { att?.number("Roll") ?? 0 }
    private var pitch: Double { att?.number("Pitch") ?? 0 }
    private var yaw: Double { att?.number("Yaw") ?? 0 }

    var body: some View {
        VStack(spacing: 0) {
            GeometryReader { geo in
                ZStack {
                    horizon(size: geo.size)
                    rollArc(size: geo.size)
                    aircraftSymbol
                }
                .clipped()
            }
            headingTape
            readouts
            levelCheck
        }
        .background(Color.black)
    }

    // MARK: - Level check
    //
    // The filter's roll/pitch next to what the accelerometer alone says, using
    // the same formula filtercf.c uses to seed the filter (line 250/256). If
    // these two disagree on a still board, the filter is being pulled by a
    // gyro bias or an init; if they agree but the board is flat, the accel
    // calibration or a trim below is bending the sensor itself.

    private var levelCheck: some View {
        let acc = link.object("AccelState")
        let raw = link.object("AccelSensor")
        let gyr = link.object("GyroState")
        let ats = link.object("AttitudeSettings")
        let ags = link.object("AccelGyroSettings")
        let ax = acc?.number("x") ?? 0, ay = acc?.number("y") ?? 0, az = acc?.number("z") ?? 0
        let accRoll = atan2(-ay, -az) * 180 / .pi
        let accPitch = atan2(ax, -(ay * ay + az * az).squareRoot()) * 180 / .pi
        let accMag = (ax * ax + ay * ay + az * az).squareRoot()
        let rx = raw?.number("x") ?? 0, ry = raw?.number("y") ?? 0, rz = raw?.number("z") ?? 0
        let rawMag = (rx * rx + ry * ry + rz * rz).squareRoot()
        func v3(_ o: UAVObjectValue?, _ f: String, _ fmt: String = "%.2f") -> String {
            let a = o?.array(f) ?? []
            return a.count >= 3 ? String(format: "\(fmt) \(fmt) \(fmt)", a[0], a[1], a[2]) : "—"
        }
        let trim = ats?.array("BoardLevelTrim") ?? []
        let trimS = trim.count >= 2 ? String(format: "%.1f %.1f", trim[0], trim[1]) : "—"
        let fusion = link.object("RevoSettings")?.option("FusionAlgorithm") ?? "—"
        let delta = max(abs(accRoll - roll), abs(accPitch - pitch))
        return VStack(alignment: .leading, spacing: 2) {
            HStack {
                Text("LEVEL CHECK").font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
                Spacer()
                Text(fusion).font(.system(size: 10)).foregroundColor(.gray)
            }
            Text(String(format: "filter  R %+6.1f  P %+6.1f", roll, pitch))
            Text(String(format: "accel   R %+6.1f  P %+6.1f   Δ %.1f°", accRoll, accPitch, delta))
                .foregroundColor(delta > 3 ? .orange : .white)
            Text(String(format: "|acc| cal %.2f raw %.2f   gyro %+.1f %+.1f %+.1f",
                        accMag, rawMag, gyr?.number("x") ?? 0, gyr?.number("y") ?? 0, gyr?.number("z") ?? 0))
            Text("rot " + v3(ats, "BoardRotation", "%.0f") + "  trim " + trimS)
            Text("acc bias " + v3(ags, "accel_bias") + "  scale " + v3(ags, "accel_scale", "%.3f"))
            Text("gyro bias " + v3(ags, "gyro_bias"))
        }
        .font(.system(size: 10, design: .monospaced))
        .foregroundColor(.white)
        .frame(maxWidth: .infinity, alignment: .leading)
        .padding(.horizontal, 12).padding(.vertical, 6)
        .background(Color(white: 0.06))
    }

    // MARK: - Horizon ball

    private func horizon(size: CGSize) -> some View {
        // 1 degree of pitch = this many points. The ladder is drawn well
        // beyond the view so a steep attitude never shows an empty edge.
        let pxPerDeg = size.height / 60.0
        return Canvas { ctx, sz in
            let mid = CGPoint(x: sz.width / 2, y: sz.height / 2)
            ctx.translateBy(x: mid.x, y: mid.y)
            ctx.rotate(by: .degrees(-roll))
            ctx.translateBy(x: 0, y: CGFloat(pitch) * pxPerDeg)

            let span = max(sz.width, sz.height) * 2

            ctx.fill(Path(CGRect(x: -span, y: -span, width: span * 2, height: span)),
                     with: .color(Color(red: 0.16, green: 0.43, blue: 0.72)))
            ctx.fill(Path(CGRect(x: -span, y: 0, width: span * 2, height: span)),
                     with: .color(Color(red: 0.42, green: 0.28, blue: 0.13)))

            var horizonLine = Path()
            horizonLine.move(to: CGPoint(x: -span, y: 0))
            horizonLine.addLine(to: CGPoint(x: span, y: 0))
            ctx.stroke(horizonLine, with: .color(.white), lineWidth: 2)

            for deg in stride(from: -90, through: 90, by: 10) where deg != 0 {
                let y = -CGFloat(deg) * pxPerDeg
                let w: CGFloat = (deg % 30 == 0) ? 70 : 40
                var p = Path()
                p.move(to: CGPoint(x: -w, y: y))
                p.addLine(to: CGPoint(x: w, y: y))
                ctx.stroke(p, with: .color(.white.opacity(0.85)), lineWidth: 1.5)
                let t = Text("\(abs(deg))").font(.system(size: 11, weight: .medium))
                    .foregroundColor(.white.opacity(0.9))
                ctx.draw(t, at: CGPoint(x: -w - 16, y: y))
                ctx.draw(t, at: CGPoint(x: w + 16, y: y))
            }
        }
    }

    private func rollArc(size: CGSize) -> some View {
        Canvas { ctx, sz in
            let c = CGPoint(x: sz.width / 2, y: sz.height / 2)
            let r = min(sz.width, sz.height) * 0.42
            for deg in [-60, -45, -30, -20, -10, 0, 10, 20, 30, 45, 60] {
                let a = Angle.degrees(Double(deg) - 90).radians
                let inner = (deg % 30 == 0) ? r - 14 : r - 8
                var p = Path()
                p.move(to: CGPoint(x: c.x + cos(a) * inner, y: c.y + sin(a) * inner))
                p.addLine(to: CGPoint(x: c.x + cos(a) * r, y: c.y + sin(a) * r))
                ctx.stroke(p, with: .color(.white.opacity(0.8)), lineWidth: deg == 0 ? 2.5 : 1.5)
            }
            // Roll pointer
            let a = Angle.degrees(-roll - 90).radians
            var tri = Path()
            let tip = CGPoint(x: c.x + cos(a) * (r - 18), y: c.y + sin(a) * (r - 18))
            let l = CGPoint(x: c.x + cos(a - 0.05) * (r - 32), y: c.y + sin(a - 0.05) * (r - 32))
            let rr = CGPoint(x: c.x + cos(a + 0.05) * (r - 32), y: c.y + sin(a + 0.05) * (r - 32))
            tri.move(to: tip); tri.addLine(to: l); tri.addLine(to: rr); tri.closeSubpath()
            ctx.fill(tri, with: .color(.yellow))
        }
        .allowsHitTesting(false)
    }

    private var aircraftSymbol: some View {
        GeometryReader { geo in
            let c = CGPoint(x: geo.size.width / 2, y: geo.size.height / 2)
            Path { p in
                p.move(to: CGPoint(x: c.x - 70, y: c.y))
                p.addLine(to: CGPoint(x: c.x - 24, y: c.y))
                p.addLine(to: CGPoint(x: c.x - 12, y: c.y + 12))
                p.move(to: CGPoint(x: c.x + 70, y: c.y))
                p.addLine(to: CGPoint(x: c.x + 24, y: c.y))
                p.addLine(to: CGPoint(x: c.x + 12, y: c.y + 12))
            }
            .stroke(Color.yellow, style: StrokeStyle(lineWidth: 3, lineCap: .round, lineJoin: .round))
            Circle().fill(Color.yellow).frame(width: 6, height: 6).position(c)
        }
        .allowsHitTesting(false)
    }

    // MARK: - Heading

    private var headingTape: some View {
        let hdg = (yaw < 0 ? yaw + 360 : yaw)
        return ZStack {
            Canvas { ctx, sz in
                let pxPerDeg = sz.width / 90.0
                let mid = sz.width / 2
                for deg in stride(from: -50, through: 410, by: 10) {
                    var delta = Double(deg) - hdg
                    while delta > 180 { delta -= 360 }
                    while delta < -180 { delta += 360 }
                    let x = mid + CGFloat(delta) * pxPerDeg
                    guard x > -40, x < sz.width + 40 else { continue }
                    let major = deg % 30 == 0
                    var p = Path()
                    p.move(to: CGPoint(x: x, y: sz.height - (major ? 14 : 8)))
                    p.addLine(to: CGPoint(x: x, y: sz.height))
                    ctx.stroke(p, with: .color(.white.opacity(0.7)), lineWidth: 1)
                    if major {
                        let d = ((deg % 360) + 360) % 360
                        let label = ["N", "", "", "E", "", "", "S", "", "", "W", "", ""][d / 30]
                        let text = label.isEmpty ? "\(d)" : label
                        ctx.draw(Text(text).font(.system(size: 11, weight: .semibold))
                                    .foregroundColor(.white),
                                 at: CGPoint(x: x, y: sz.height - 24))
                    }
                }
            }
            Triangle().fill(Color.yellow).frame(width: 12, height: 8)
                .offset(y: 12)
        }
        .frame(height: 44)
        .background(Color.black)
    }

    private var readouts: some View {
        HStack(spacing: 0) {
            readout("ROLL", roll, "°")
            readout("PITCH", pitch, "°")
            readout("YAW", yaw < 0 ? yaw + 360 : yaw, "°")
        }
        .padding(.vertical, 8)
        .background(Color(white: 0.08))
    }

    private func readout(_ label: String, _ value: Double, _ unit: String) -> some View {
        VStack(spacing: 2) {
            Text(label).font(.system(size: 10, weight: .semibold)).foregroundColor(.gray)
            Text(String(format: "%.1f%@", value, unit))
                .font(.system(size: 20, weight: .medium, design: .monospaced))
                .foregroundColor(link.isStale ? .gray : .white)
        }
        .frame(maxWidth: .infinity)
    }
}

struct Triangle: Shape {
    func path(in r: CGRect) -> Path {
        var p = Path()
        p.move(to: CGPoint(x: r.midX, y: r.maxY))
        p.addLine(to: CGPoint(x: r.minX, y: r.minY))
        p.addLine(to: CGPoint(x: r.maxX, y: r.minY))
        p.closeSubpath()
        return p
    }
}
