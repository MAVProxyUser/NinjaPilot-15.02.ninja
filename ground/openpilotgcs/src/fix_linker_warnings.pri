# Fix macOS linker warnings
macx {
    # Remove the obsolete -single_module flag
    QMAKE_LFLAGS_SHLIB -= -single_module
    QMAKE_LFLAGS_PLUGIN -= -single_module
    QMAKE_LFLAGS_SONAME -= -single_module
    
    # Add modern flags if needed
    QMAKE_LFLAGS_SHLIB *= -dynamiclib
}