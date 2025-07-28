# Fix Qt include path case sensitivity warnings on macOS
macx {
    # Suppress case sensitivity warnings from Qt's own headers
    QMAKE_CXXFLAGS += -Wno-nonportable-include-path
    QMAKE_CFLAGS += -Wno-nonportable-include-path
}