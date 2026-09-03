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
# submiteditorwidget.cpp does #include "submiteditorwidget.moc", so the .moc
# has to exist next to the source. Two separate hazards if the checkout path
# contains a space (e.g. "OP Revo Redux"), and building through a space-free
# symlink does NOT avoid them because qmake resolves $$PWD to the real path:
#
#   1. an unquoted expansion hands moc three filenames
#      ("Too many input files specified") -- hence $$shell_quote below;
#   2. more fundamentally, GNU make cannot express a TARGET whose path
#      contains a space, so this rule can never fire and make reports
#      "No rule to make target .../submiteditorwidget.moc".
#
# Because of (2) the generated .moc is kept in the source tree as a checked-in
# build artifact. If it goes missing, regenerate it by hand:
#
#   moc src/libs/utils/submiteditorwidget.cpp -o src/libs/utils/submiteditorwidget.moc
submiteditorwidget_moc.depends = $$quote($$PWD/submiteditorwidget.cpp)
submiteditorwidget_moc.commands = moc $$shell_quote($$PWD/submiteditorwidget.cpp) -o submiteditorwidget.moc
QMAKE_EXTRA_TARGETS += submiteditorwidget_moc
PRE_TARGETDEPS += submiteditorwidget.moc
