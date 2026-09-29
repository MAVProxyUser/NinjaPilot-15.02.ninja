import CoreGraphics
import Foundation
// print the CGWindowID of the largest on-screen window owned by NinjaPilotGCS (nothing else)
let opts = CGWindowListOption(arrayLiteral: .optionOnScreenOnly, .excludeDesktopElements)
guard let list = CGWindowListCopyWindowInfo(opts, kCGNullWindowID) as? [[String: Any]] else { exit(1) }
var best: (Int, Int) = (0, 0)
for w in list {
    guard (w[kCGWindowOwnerName as String] as? String) == "NinjaPilotGCS", let b = w[kCGWindowBounds as String] as? [String: Any], let num = w[kCGWindowNumber as String] as? Int else { continue }
    let area = Int((b["Width"] as? Double ?? 0) * (b["Height"] as? Double ?? 0))
    if area > best.1 { best = (num, area) }
}
if best.1 == 0 { exit(2) }
print(best.0)
