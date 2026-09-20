import SwiftUI

@main
struct NinjaPilotMobileApp: App {
    @StateObject private var link = TelemetryLink()

    var body: some Scene {
        WindowGroup {
            ContentView(link: link)
                .preferredColorScheme(.dark)
        }
    }
}
