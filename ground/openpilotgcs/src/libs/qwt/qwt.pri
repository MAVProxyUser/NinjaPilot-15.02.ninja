# Use Homebrew's qwt-qt5 installation
macx {
    INCLUDEPATH += /opt/homebrew/opt/qwt-qt5/lib/qwt.framework/Headers
    LIBS *= -F/opt/homebrew/opt/qwt-qt5/lib -framework qwt
    QMAKE_RPATHDIR += /opt/homebrew/opt/qwt-qt5/lib
} else {
    INCLUDEPATH += $$PWD/lib/qwt.framework/Headers
    LIBS *= -F$$PWD/lib -framework qwt
}
