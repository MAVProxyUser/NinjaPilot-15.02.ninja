TEMPLATE = lib
TARGET = Utils

QT += gui \
    network \
    xml \
    svg \
    opengl \
    qml quick \
    widgets

DEFINES += QTCREATOR_UTILS_LIB

include(../../openpilotgcslibrary.pri)

SOURCES += reloadpromptutils.cpp \
    settingsutils.cpp \
    filesearch.cpp \
    pathchooser.cpp \
    pathlisteditor.cpp \
    filewizardpage.cpp \
    filewizarddialog.cpp \
    projectintropage.cpp \
    basevalidatinglineedit.cpp \
    filenamevalidatinglineedit.cpp \
    projectnamevalidatinglineedit.cpp \
    codegeneration.cpp \
    newclasswidget.cpp \
    classnamevalidatinglineedit.cpp \
    linecolumnlabel.cpp \
    fancylineedit.cpp \
    qtcolorbutton.cpp \
    savedaction.cpp \
    submiteditorwidget.cpp \
    synchronousprocess.cpp \
    submitfieldwidget.cpp \
    consoleprocess.cpp \
    uncommentselection.cpp \
    parameteraction.cpp \
    treewidgetcolumnstretcher.cpp \
    checkablemessagebox.cpp \
    styledbar.cpp \
    stylehelper.cpp \
    welcomemodetreewidget.cpp \
    iwelcomepage.cpp \
    fancymainwindow.cpp \
    detailsbutton.cpp \
    detailswidget.cpp \
    coordinateconversions.cpp \
    pathutils.cpp \
	worldmagmodel.cpp \
	homelocationutil.cpp \
    mytabbedstackwidget.cpp \
    mytabwidget.cpp \
    cachedsvgitem.cpp \
    svgimageprovider.cpp \
    hostosinfo.cpp \
    logfile.cpp \
    crc.cpp \
    mustache.cpp

SOURCES += xmlconfig.cpp

win32 {
    SOURCES += abstractprocess_win.cpp \
        consoleprocess_win.cpp \
        winutils.cpp
    HEADERS += winutils.h
}
else:SOURCES += consoleprocess_unix.cpp

HEADERS += utils_global.h \
    reloadpromptutils.h \
    settingsutils.h \
    filesearch.h \
    listutils.h \
    pathchooser.h \
    pathlisteditor.h \
    filewizardpage.h \
    filewizarddialog.h \
    projectintropage.h \
    basevalidatinglineedit.h \
    filenamevalidatinglineedit.h \
    projectnamevalidatinglineedit.h \
    codegeneration.h \
    newclasswidget.h \
    classnamevalidatinglineedit.h \
    linecolumnlabel.h \
    fancylineedit.h \
    qtcolorbutton.h \
    savedaction.h \
    submiteditorwidget.h \
    abstractprocess.h \
    consoleprocess.h \
    synchronousprocess.h \
    submitfieldwidget.h \
    uncommentselection.h \
    parameteraction.h \
    treewidgetcolumnstretcher.h \
    checkablemessagebox.h \
    qtcassert.h \
    styledbar.h \
    stylehelper.h \
    welcomemodetreewidget.h \
    iwelcomepage.h \
    fancymainwindow.h \
    detailsbutton.h \
    detailswidget.h \
    coordinateconversions.h \
    pathutils.h \
	worldmagmodel.h \
	homelocationutil.h \
    mytabbedstackwidget.h \
    mytabwidget.h \
    cachedsvgitem.h \
    svgimageprovider.h \
    hostosinfo.h \
    logfile.h \
    crc.h \
    mustache.h


HEADERS += xmlconfig.h

FORMS += filewizardpage.ui \
    projectintropage.ui \
    newclasswidget.ui \
    submiteditorwidget.ui \
	checkablemessagebox.ui

RESOURCES += utils.qrc

# For .cpp files with Q_OBJECT classes, we need to explicitly tell qmake to generate MOC files
# This ensures proper MOC generation for classes defined in .cpp files rather than headers
CONFIG += depend_includepath

# Custom rule to generate MOC files for Q_OBJECT classes defined in .cpp files
submiteditorwidget_moc.target = submiteditorwidget.moc
# submiteditorwidget.cpp does #include "submiteditorwidget.moc", so a .moc has
# to be reachable from that translation unit. The target below is RELATIVE, so
# it lands in the build directory, which is already on the include path -- the
# .cpp finds it there and no copy in the source tree is needed.
#
# Two hazards, both handled here:
#
#   1. an unquoted expansion hands moc three filenames when the checkout path
#      contains a space (e.g. "OP Revo Redux") -- hence $$shell_quote.
#   2. `moc` is NOT on PATH when Qt comes from Homebrew, which is keg-only:
#      the rule fired and died with "make: moc: No such file or directory",
#      leaving a build that only worked because a stale .moc happened to sit
#      in the source tree. Use Qt's own binary directory instead of hoping.
#
# This was previously documented as "GNU make cannot express a TARGET whose
# path contains a space, so this rule can never fire", and the .moc was kept
# in the source tree as a checked-in build artifact to work around it. That
# diagnosis was wrong: the target is relative and has no space in it. The real
# fault was (2). Verified 2026-09-02 by deleting the source-tree .moc and
# building clean.
submiteditorwidget_moc.depends = $$quote($$PWD/submiteditorwidget.cpp)
submiteditorwidget_moc.commands = $$shell_quote($$[QT_INSTALL_BINS]/moc) $$shell_quote($$PWD/submiteditorwidget.cpp) -o submiteditorwidget.moc
QMAKE_EXTRA_TARGETS += submiteditorwidget_moc
PRE_TARGETDEPS += submiteditorwidget.moc
